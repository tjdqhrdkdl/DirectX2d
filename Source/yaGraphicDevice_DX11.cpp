#include "yaGraphicDevice_DX11.h"
#include "yaApplication.h"
#include "yaRenderer.h"
extern ya::Application application;

namespace ya::graphics
{
	GraphicDevice_DX11::GraphicDevice_DX11(ValidationMode validationMode)
	{		
		/// <summary>
		/// 1. Device 와 SwapChain 생성한다.
		/// 2. 백버퍼에 실제로 렌더링할 렌더타겟 뷰를 생성해야한다.
		/// 3. 화면을 클리어 해줘야한다. 뷰포트를 생성해줘야 한다.
		/// 4. 매프레임마다 위에서 생성한 렌더타겟뷰에 렌더링해주어야한다.
		/// 5. Swapchain을 이용하여 최종 디바이스(디스플레이)에 화면을 그려줘야한다.
		/// </summary>
		HWND hwnd = application.GetHwnd();
		
		D3D_FEATURE_LEVEL FeatureLevel = (D3D_FEATURE_LEVEL)0;

		HRESULT hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE, nullptr
						, D3D11_CREATE_DEVICE_DEBUG
						, nullptr, 0
						, D3D11_SDK_VERSION
						, mDevice.GetAddressOf()
						, &FeatureLevel
						, mContext.GetAddressOf()
						);
		DXGI_SWAP_CHAIN_DESC swapChainDesc = {};

		swapChainDesc.OutputWindow = hwnd;
		swapChainDesc.Windowed = true;
		swapChainDesc.BufferCount = 2;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; // 두 버퍼 사이에서 교환이 일어나지 않는다. 버퍼를 플립하는 방식으로, 이전 프레임이 필요하지 않다면 사용한다.

		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferDesc.Width = application.GetWidth();
		swapChainDesc.BufferDesc.Height = application.GetHeight();
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT::DXGI_FORMAT_B8G8R8A8_UNORM;
		//버퍼라면 텍스쳐(텍셀(?)의 2차원 행렬구조)이고, 텍스쳐는 반드시 특정한 포맷을 따르는 자료형이다.
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 144;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
		swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER::DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;

		if (!CreateSwapChain(&swapChainDesc))
			return;

		//스왑체인으로부터 버퍼를 가져온다.
		hr = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)mRenderTarget.GetAddressOf());
		
		//디바이스에서 버퍼뷰를 create한다.
		hr = mDevice->CreateRenderTargetView(mRenderTarget.Get(), nullptr, mRenderTargetView.GetAddressOf());

		D3D11_TEXTURE2D_DESC depthBufferDesc = {};
		depthBufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;
		depthBufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		depthBufferDesc.CPUAccessFlags = 0;

		depthBufferDesc.Format = DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthBufferDesc.Width = application.GetWidth();
		depthBufferDesc.Height = application.GetHeight();
		depthBufferDesc.ArraySize = 1;
		
		depthBufferDesc.SampleDesc.Count = 1;
		depthBufferDesc.SampleDesc.Quality = 0;

		//밈맵은 1/4사이즈 - 1/4 사이즈  ... 1x1까지(?) 이미지를 저장하는 것
		//렌더링을 크게 줄일 수 있으며 계산을 해보면 원본 파일의 1/3정도의 메모리만 사용한다.
		depthBufferDesc.MipLevels = 0;
		depthBufferDesc.MiscFlags = 0;

		if (!CreateTexture(&depthBufferDesc, mDepthStencilBuffer.GetAddressOf()))
			return;

		// Depth Stencil Buffer View
		if (FAILED(mDevice->CreateDepthStencilView(mDepthStencilBuffer.Get(), nullptr, mDepthStencilView.GetAddressOf())))
			return;

		RECT winRect;
		GetClientRect(application.GetHwnd(), &winRect);

		mViewPort = {0.0f, 0.0f, FLOAT(winRect.right - winRect.left), FLOAT(winRect.bottom - winRect.top), 0.0f, 1.0f};
		BindViewports(&mViewPort);
		mContext->OMSetRenderTargets(1, mRenderTargetView.GetAddressOf(), mDepthStencilView.Get());
		
	}

	GraphicDevice_DX11::~GraphicDevice_DX11()
	{
		renderer::Release();
	}

	bool GraphicDevice_DX11::CreateSwapChain(DXGI_SWAP_CHAIN_DESC* desc)
	{
		//스왑 체인을 만드는 주체는 dxgi의 factory다.
		//근데 device를 create한 주체도 factory였다.
		//때문에 거슬러 올라가서 factory를 가져와서 스왑 체인을 만든다.
		//팩토리를 찾기위해서 dxgi 인터페이스를 가져오고, 부모를 찾고 하는 것.
		Microsoft::WRL::ComPtr<IDXGIDevice> pDXGIDevice = nullptr;
		Microsoft::WRL::ComPtr<IDXGIAdapter> pDXGIAdapter = nullptr;
		Microsoft::WRL::ComPtr<IDXGIFactory> pDXGIFactory = nullptr;

		if(FAILED(mDevice->QueryInterface(__uuidof(IDXGIDevice),(void**)pDXGIDevice.GetAddressOf())))
			return false;

		if (FAILED(pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)pDXGIAdapter.GetAddressOf())))
			return false;
		if (FAILED(pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), (void**)pDXGIFactory.GetAddressOf())))
			return false;

		if(FAILED(pDXGIFactory->CreateSwapChain(mDevice.Get(), desc, mSwapChain.GetAddressOf())))
			return false;

		return true;
	}

	bool GraphicDevice_DX11::CreateTexture(D3D11_TEXTURE2D_DESC* pDesc, ID3D11Texture2D** ppTexture2D)
	{
		if(FAILED(mDevice->CreateTexture2D(pDesc, nullptr,ppTexture2D)))
			return false;

		return true;

	}

	void GraphicDevice_DX11::BindViewports(D3D11_VIEWPORT* pViewport)
	{
		mContext->RSSetViewports(1, pViewport);
	}

	bool GraphicDevice_DX11::CreateInputLayout(D3D11_INPUT_ELEMENT_DESC* desc, UINT NumElements, const void* byteCode, SIZE_T bytecodeLength, ID3D11InputLayout** ppInputLayout)
	{
		if(FAILED(mDevice->CreateInputLayout(desc,NumElements,byteCode,bytecodeLength,ppInputLayout)))
			return false;

		return true;
	}

	bool GraphicDevice_DX11::CreateBuffer(D3D11_BUFFER_DESC* pDesc, D3D11_SUBRESOURCE_DATA* pInitialData, ID3D11Buffer** ppBuffer)
	{
		if (FAILED(mDevice->CreateBuffer(pDesc, pInitialData, ppBuffer)))
			return false;
		return true;
	}

	bool GraphicDevice_DX11::CreateShader()
	{
		//ID3DBlob* errorBlob = nullptr;

		//std::filesystem::path shaderPath = std::filesystem::current_path().parent_path();
		//shaderPath += "\\SHADER_SOURCE\\";

		////vertex shader
		//std::wstring vsPath(shaderPath.c_str());
		//vsPath += L"TriangleVS.hlsl";
		//D3DCompileFromFile(vsPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
		//	, "VS_Test", "vs_5_0", 0, 0, renderer::triangleVSBlob.GetAddressOf(), &errorBlob);

		//if (errorBlob)
		//{
		//	OutputDebugStringA((char*)errorBlob->GetBufferPointer());
		//	errorBlob->Release();
		//	errorBlob = nullptr;
		//}

		//mDevice->CreateVertexShader(renderer::triangleVSBlob->GetBufferPointer()
		//	, renderer::triangleVSBlob->GetBufferSize()
		//	, nullptr, renderer::triangleVS.GetAddressOf());

		////pixel shader
		//std::wstring psPath(shaderPath.c_str());
		//psPath += L"TrianglePS.hlsl";
		//D3DCompileFromFile(psPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
		//	, "PS_Test", "ps_5_0", 0, 0, renderer::trianglePSBlob.GetAddressOf(), &errorBlob);
		//if (errorBlob)
		//{
		//	OutputDebugStringA((char*)errorBlob->GetBufferPointer());
		//	errorBlob->Release();
		//	errorBlob = nullptr;
		//}

		//mDevice->CreatePixelShader(renderer::trianglePSBlob->GetBufferPointer()
		//	, renderer::trianglePSBlob->GetBufferSize()
		//	, nullptr, renderer::trianglePS.GetAddressOf());


		return false;
	}

	void GraphicDevice_DX11::BindVertexBuffer(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppVertexBuffers, const UINT* pStrides, const UINT* pOffsets)
	{
		mContext->IASetVertexBuffers(StartSlot, NumBuffers, ppVertexBuffers, pStrides, pOffsets);
	}

	void GraphicDevice_DX11::BindIndexBuffer(ID3D11Buffer* pIndexBuffer, DXGI_FORMAT Format, UINT Offset)
	{
		mContext->IASetIndexBuffer(pIndexBuffer, Format, Offset);
	}

	void GraphicDevice_DX11::BindConstantBuffer(ID3D11Buffer* buffer, void* data, UINT size)
	{
		D3D11_MAPPED_SUBRESOURCE sub = {};
		mContext->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &sub);
		memcpy(sub.pData, data, size);
		mContext->Unmap(buffer, 0);
	}

	void GraphicDevice_DX11::SetConstantBuffer(eShaderStage stage, eCBType type, ID3D11Buffer* buffer)
	{
		switch (stage)
		{
		case ya::graphics::eShaderStage::VS:
			mContext->VSSetConstantBuffers((UINT)type, 1, &buffer);
			break;
		case ya::graphics::eShaderStage::HS:
			mContext->HSSetConstantBuffers((UINT)type, 1, &buffer);
			break;
		case ya::graphics::eShaderStage::DS:
			mContext->DSSetConstantBuffers((UINT)type, 1, &buffer);
			break;
		case ya::graphics::eShaderStage::GS:
			mContext->GSSetConstantBuffers((UINT)type, 1, &buffer);
			break;
		case ya::graphics::eShaderStage::PS:
			mContext->PSSetConstantBuffers((UINT)type, 1, &buffer);
			break;
		case ya::graphics::eShaderStage::CS:
			mContext->CSSetConstantBuffers((UINT)type, 1, &buffer);
			break;
		default:
			break;
		}
	}

	void GraphicDevice_DX11::SetShaderResource(eShaderStage stage, UINT slot, ID3D11ShaderResourceView* const* ppShaderResourceView)
	{
		switch (stage)
		{
		case eShaderStage::VS:
			mContext->VSSetShaderResources(slot, 1, ppShaderResourceView);
			break;
		case eShaderStage::HS:
			mContext->HSSetShaderResources(slot, 1, ppShaderResourceView);
			break;
		case eShaderStage::DS:
			mContext->DSSetShaderResources(slot, 1, ppShaderResourceView);
			break;
		case eShaderStage::GS:
			mContext->GSSetShaderResources(slot, 1, ppShaderResourceView);
			break;
		case eShaderStage::PS:
			mContext->PSSetShaderResources(slot, 1, ppShaderResourceView);
			break;
		case eShaderStage::CS:
			mContext->CSSetShaderResources(slot, 1, ppShaderResourceView);
			break;
		default:
			break;
		}
	}

	void GraphicDevice_DX11::BindsSamplers(UINT startSlot, UINT numSamplers, ID3D11SamplerState* const* ppSamplers)
	{
		mContext->VSSetSamplers(startSlot, numSamplers, ppSamplers);
		mContext->HSSetSamplers(startSlot, numSamplers, ppSamplers);
		mContext->DSSetSamplers(startSlot, numSamplers, ppSamplers);
		mContext->GSSetSamplers(startSlot, numSamplers, ppSamplers);
		mContext->PSSetSamplers(startSlot, numSamplers, ppSamplers);
	}

	void GraphicDevice_DX11::Clear()
	{
		//화면 지워주기
		FLOAT backgroundFloat[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
		mContext->ClearRenderTargetView(mRenderTargetView.Get(), backgroundFloat);
		mContext->ClearDepthStencilView(mDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, (UINT8)0);
	}

	void GraphicDevice_DX11::AdjustViewPorts()
	{//뷰포트 설정 , 렌더타겟 설정
		
		RECT winRect = {};
		GetClientRect(application.GetHwnd(), &winRect);
		mViewPort = { 0.0f, 0.0f, FLOAT(winRect.right - winRect.left), FLOAT(winRect.bottom - winRect.top), 0.0f,1.0f };
		BindViewports(&mViewPort);
		mContext->OMSetRenderTargets(1, mRenderTargetView.GetAddressOf(), mDepthStencilView.Get());
	}

	bool GraphicDevice_DX11::CreateVertexShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11VertexShader** ppVertexShader)
	{
		if(FAILED(mDevice->CreateVertexShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppVertexShader)))
			return false;
		return true;
	}

	bool GraphicDevice_DX11::CreatePixelShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11PixelShader** ppPixelShader)
	{
		if (FAILED(mDevice->CreatePixelShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppPixelShader)))
			return false;
		return true;
	}

	bool GraphicDevice_DX11::CreateSamplerState(D3D11_SAMPLER_DESC* pSamplerDesc, ID3D11SamplerState** ppSamplerState)
	{
		if(FAILED(mDevice->CreateSamplerState(pSamplerDesc, ppSamplerState)))
			return false;
		
		return true;

	}

	void GraphicDevice_DX11::BindPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY topology)
	{
		mContext->IASetPrimitiveTopology(topology);
	}

	void GraphicDevice_DX11::BindInputLayout(ID3D11InputLayout* pInputLayout)
	{
		mContext->IASetInputLayout(pInputLayout);
	}

	void GraphicDevice_DX11::BindVertexShader(ID3D11VertexShader* pVertexShader, ID3D11ClassInstance* const* ppClassInstances, UINT NumClassInstances)
	{
		mContext->VSSetShader(pVertexShader, ppClassInstances, NumClassInstances);
	}

	void GraphicDevice_DX11::BindPixelShader(ID3D11PixelShader* pPixelShader, ID3D11ClassInstance* const* ppClassInstances, UINT NumClassInstances)
	{
		mContext->PSSetShader(pPixelShader, ppClassInstances, NumClassInstances);
	}

	void GraphicDevice_DX11::Draw()
	{
		mContext->Draw(0, 0);
	}

	void GraphicDevice_DX11::DrawIndexed(UINT indexCount, UINT StartIndexLocation, UINT BaseVertexLocation)
	{
		mContext->DrawIndexed(indexCount, StartIndexLocation, BaseVertexLocation);
	}

	void GraphicDevice_DX11::Present()
	{
		mSwapChain->Present(0, 0);
	}

}

