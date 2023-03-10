#include "yaRenderer.h"
#include "yaResources.h"
#include "yaMaterial.h"
#include "yaSceneManager.h"
namespace ya::renderer
{
	using namespace std;
	Vertex vertexes[4] = {};

	ConstantBuffer* constantBuffers[(UINT)eCBType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerStates[(UINT)eSamplerType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[(UINT)eRSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthstencilStates[(UINT)eDSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[(UINT)eBSType::End] = {};
	
	std::vector<Camera*> cameras[(UINT)eSceneType::End];

	Camera* mainCamera = nullptr;
	Camera* orthographicCamera = nullptr;
	std::vector<DebugMesh> debugMeshes;

	void SetUpState()
	{
#pragma region InputLayout

		D3D11_INPUT_ELEMENT_DESC arrLayoutDesc[3] = {};

		arrLayoutDesc[0].AlignedByteOffset = 0;
		arrLayoutDesc[0].Format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT;
		arrLayoutDesc[0].InputSlot = 0;
		arrLayoutDesc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayoutDesc[0].SemanticName = "POSITION";
		arrLayoutDesc[0].SemanticIndex = 0;

		arrLayoutDesc[1].AlignedByteOffset = 16;
		arrLayoutDesc[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		arrLayoutDesc[1].InputSlot = 0;
		arrLayoutDesc[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayoutDesc[1].SemanticName = "COLOR";
		arrLayoutDesc[1].SemanticIndex = 0;

		arrLayoutDesc[2].AlignedByteOffset = 32;
		arrLayoutDesc[2].Format = DXGI_FORMAT_R32G32_FLOAT;
		arrLayoutDesc[2].InputSlot = 0;
		arrLayoutDesc[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayoutDesc[2].SemanticName = "TEXCOORD";
		arrLayoutDesc[2].SemanticIndex = 0;

		std::shared_ptr<Shader> shader = Resources::Find<Shader>(L"RectShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, shader->GetVSBlobBufferPointer()
			, shader->GetVSBlobBufferSize()
			, shader->GetInputLayoutAddressOf());

		std::shared_ptr<Shader> spriteShader = Resources::Find<Shader>(L"SpriteShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, spriteShader->GetVSBlobBufferPointer()
			, spriteShader->GetVSBlobBufferSize()
			, spriteShader->GetInputLayoutAddressOf());

		std::shared_ptr<Shader> UIShader = Resources::Find<Shader>(L"UIShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, UIShader->GetVSBlobBufferPointer()
			, UIShader->GetVSBlobBufferSize()
			, UIShader->GetInputLayoutAddressOf());

		std::shared_ptr<Shader> GridShader = Resources::Find<Shader>(L"GridShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, GridShader->GetVSBlobBufferPointer()
			, GridShader->GetVSBlobBufferSize()
			, GridShader->GetInputLayoutAddressOf());

		std::shared_ptr<Shader> CamEffectShader = Resources::Find<Shader>(L"CamEffectShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, CamEffectShader->GetVSBlobBufferPointer()
			, CamEffectShader->GetVSBlobBufferSize()
			, CamEffectShader->GetInputLayoutAddressOf());

		std::shared_ptr<Shader> DebugShader = Resources::Find<Shader>(L"DebugShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, DebugShader->GetVSBlobBufferPointer()
			, DebugShader->GetVSBlobBufferSize()
			, DebugShader->GetInputLayoutAddressOf());
#pragma endregion

#pragma region SamplerState

		D3D11_SAMPLER_DESC samplerDesc = {};
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		//D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR = 0x5,
		//D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT = 0x10,
		samplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT;

		GetDevice()->CreateSamplerState(&samplerDesc, samplerStates[(UINT)eSamplerType::Point].GetAddressOf());

		samplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR;
		GetDevice()->CreateSamplerState(&samplerDesc, samplerStates[(UINT)eSamplerType::Linear].GetAddressOf());

		samplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_ANISOTROPIC;
		GetDevice()->CreateSamplerState(&samplerDesc, samplerStates[(UINT)eSamplerType::Anisotropic].GetAddressOf());

		GetDevice()->BindsSamplers((UINT)eSamplerType::Point
			, 1, samplerStates[(UINT)eSamplerType::Point].GetAddressOf());

		GetDevice()->BindsSamplers((UINT)eSamplerType::Linear
			, 1, samplerStates[(UINT)eSamplerType::Linear].GetAddressOf());

		GetDevice()->BindsSamplers((UINT)eSamplerType::Anisotropic
			, 1, samplerStates[(UINT)eSamplerType::Anisotropic].GetAddressOf());

#pragma endregion

#pragma region RasterizerState
		D3D11_RASTERIZER_DESC rsDesc = {};
		rsDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rsDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;

		GetDevice()->CreateRasterizerState(&rsDesc
			, rasterizerStates[(UINT)eRSType::SolidBack].GetAddressOf());

		rsDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rsDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_FRONT;

		GetDevice()->CreateRasterizerState(&rsDesc
			, rasterizerStates[(UINT)eRSType::SolidFront].GetAddressOf());

		rsDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rsDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;

		GetDevice()->CreateRasterizerState(&rsDesc
			, rasterizerStates[(UINT)eRSType::SolidNone].GetAddressOf());

		rsDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
		rsDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;

		GetDevice()->CreateRasterizerState(&rsDesc
			, rasterizerStates[(UINT)eRSType::WireframeNone].GetAddressOf());
#pragma endregion

#pragma region Depth Stencil State
		D3D11_DEPTH_STENCIL_DESC dsDesc = {};
		dsDesc.DepthEnable = true;
		dsDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
		dsDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&dsDesc
			, depthstencilStates[(UINT)eDSType::Less].GetAddressOf());

		dsDesc.DepthEnable = true;
		dsDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_GREATER;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
		dsDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&dsDesc
			, depthstencilStates[(UINT)eDSType::Greater].GetAddressOf());

		dsDesc.DepthEnable = true;
		dsDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ZERO;
		dsDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&dsDesc
			, depthstencilStates[(UINT)eDSType::NoWrite].GetAddressOf());

		dsDesc.DepthEnable = false;
		dsDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ZERO;
		dsDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&dsDesc
			, depthstencilStates[(UINT)eDSType::None].GetAddressOf());

#pragma endregion

#pragma region Blend State

		blendStates[(UINT)eBSType::Default] = nullptr;

		D3D11_BLEND_DESC bsDesc = {};
		bsDesc.AlphaToCoverageEnable = false;
		bsDesc.IndependentBlendEnable = false;
		bsDesc.RenderTarget[0].BlendEnable = true;
		bsDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		bsDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		bsDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		bsDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		bsDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		bsDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;

		bsDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		GetDevice()->CreateBlendState(&bsDesc, blendStates[(UINT)eBSType::AlphaBlend].GetAddressOf());

		bsDesc.AlphaToCoverageEnable = false;
		bsDesc.IndependentBlendEnable = false;

		bsDesc.RenderTarget[0].BlendEnable = true;
		bsDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		bsDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		bsDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		bsDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		GetDevice()->CreateBlendState(&bsDesc, blendStates[(UINT)eBSType::OneOne].GetAddressOf());

#pragma endregion

	}

	void LoadMesh()
	{
		//RectMesh
		vertexes[0].pos = Vector4(-0.5f, 0.5f, -0.0f, 1.0f);
		vertexes[0].color = Vector4(0.f, 1.f, 0.f, 1.f);
		vertexes[0].uv = Vector2(0.f, 0.f);

		vertexes[1].pos = Vector4(0.5f, 0.5f, -0.0f, 1.0f);
		vertexes[1].color = Vector4(1.f, 1.f, 1.f, 1.f);
		vertexes[1].uv = Vector2(1.0f, 0.0f);

		vertexes[2].pos = Vector4(0.5f, -0.5f, -0.0f, 1.0f);
		vertexes[2].color = Vector4(1.f, 0.f, 0.f, 1.f);
		vertexes[2].uv = Vector2(1.0f, 1.0f);

		vertexes[3].pos = Vector4(-0.5f, -0.5f, -0.0f, 1.0f);
		vertexes[3].color = Vector4(0.f, 0.f, 1.f, 1.f);
		vertexes[3].uv = Vector2(0.0f, 1.0f);

		shared_ptr<Mesh> mesh = make_shared<Mesh>();
		Resources::Insert<Mesh>(L"RectMesh", mesh);
		mesh->CreateVertexBuffer(vertexes, 4);

		std::vector<UINT> indexes;
		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);

		indexes.push_back(0);
		indexes.push_back(2);
		indexes.push_back(3);

		mesh->CreateIndexBuffer(indexes.data(), indexes.size());

		//Debug Rect Mesh (Line Only)
		shared_ptr<Mesh> debugMesh = make_shared<Mesh>();
		Resources::Insert<Mesh>(L"DebugRectMesh", debugMesh);
		debugMesh->CreateVertexBuffer(vertexes, 4);
		indexes.clear();
		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);
		indexes.push_back(3);
		debugMesh->CreateIndexBuffer(indexes.data(), indexes.size());


		//Cirle Rect
		shared_ptr<Mesh> circleMesh = make_shared<Mesh>();
		Resources::Insert<Mesh>(L"CircleMesh", circleMesh);

		std::vector<Vertex> circleVtxes;
		Vertex center = {};
		center.pos = Vector4(0.0f, 0.0f, -0.0f, 1.0f);
		center.color = Vector4(0.0f, 1.0f, -0.0f, 1.0f);
		center.uv = Vector2(0.5f, 0.5f);

		circleVtxes.push_back(center);

		int iSlice = 40;
		float fRadius = 0.5;
		float fTheta = XM_2PI / iSlice;
		
		for (size_t i = 0; i < iSlice; i++)
		{
			Vertex vtx = {};
			vtx.pos = Vector4(
				fRadius * cosf(fTheta * i)
				, fRadius * sinf(fTheta * i)
				, -0.0f
				, 1
			);
			vtx.uv = Vector2(
				0.5 * cosf(fTheta * i) + 0.5 
				, 0.5 - 0.5 * sinf(fTheta * i) 
			);
			circleVtxes.push_back(vtx);
		}
		indexes.clear();
		for (size_t i = 0; i < iSlice -2; i++)
		{
			indexes.push_back(0);
			indexes.push_back(i + 2);
			indexes.push_back(i + 1);
		}
		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(iSlice-1);
		circleMesh->CreateVertexBuffer(circleVtxes.data(), circleVtxes.size());
		circleMesh->CreateIndexBuffer(indexes.data(), indexes.size());

		//Debug Circle Mesh
		shared_ptr<Mesh> DebugCircleMesh = make_shared<Mesh>();
		Resources::Insert<Mesh>(L"DebugCircleMesh", DebugCircleMesh);
		indexes.clear();
		for (size_t i = 0; i < iSlice - 1; i++)
		{
			indexes.push_back(i + 1);
		}
		indexes.push_back(1);
		DebugCircleMesh->CreateVertexBuffer(circleVtxes.data(), circleVtxes.size());
		DebugCircleMesh->CreateIndexBuffer(indexes.data(), indexes.size());


	}
	void LoadBuffer()
	{

		constantBuffers[(UINT)eCBType::Transform] = new ConstantBuffer(eCBType::Transform);
		constantBuffers[(UINT)eCBType::Transform]->Create(sizeof(TransformCB));

		constantBuffers[(UINT)eCBType::Material] = new ConstantBuffer(eCBType::Material);
		constantBuffers[(UINT)eCBType::Material]->Create(sizeof(MaterialCB));

	}
	;
	void LoadShader()
	{
		std::shared_ptr<Shader> shader = std::make_shared<Shader>();
		Resources::Insert<Shader>(L"RectShader", shader);
		shader->Create(eShaderStage::VS, L"SpriteVS.hlsl", "Main");
		shader->Create(eShaderStage::PS, L"SpritePS.hlsl", "Main");

		// Sprite
		std::shared_ptr<Shader> spriteShader = std::make_shared<Shader>();
		spriteShader->Create(eShaderStage::VS, L"SpriteVS.hlsl", "Main");
		spriteShader->Create(eShaderStage::PS, L"SpritePS.hlsl", "Main");

		Resources::Insert<Shader>(L"SpriteShader", spriteShader);

		// UI
		std::shared_ptr<Shader> UIShader = std::make_shared<Shader>();
		UIShader->Create(eShaderStage::VS, L"SpriteVS.hlsl", "Main");
		UIShader->Create(eShaderStage::PS, L"SpritePS.hlsl", "Main");

		Resources::Insert<Shader>(L"UIShader", UIShader);

		// Grid
		std::shared_ptr<Shader> GridShader = std::make_shared<Shader>();
		GridShader->Create(eShaderStage::VS, L"GridVS.hlsl", "Main");
		GridShader->Create(eShaderStage::PS, L"GridPS.hlsl", "Main");

		Resources::Insert<Shader>(L"GridShader", GridShader);

		// CamEffect
		std::shared_ptr<Shader> CamEffectShader = std::make_shared<Shader>();
		CamEffectShader->Create(eShaderStage::VS, L"FadeVS.hlsl", "main");
		CamEffectShader->Create(eShaderStage::PS, L"FadePS.hlsl", "main");

		Resources::Insert<Shader>(L"CamEffectShader", CamEffectShader);

		// Debug
		std::shared_ptr<Shader> debugShader = std::make_shared<Shader>();
		debugShader->Create(eShaderStage::VS, L"DebugVS.hlsl", "main");
		debugShader->Create(eShaderStage::PS, L"DebugPS.hlsl", "main");

		Resources::Insert<Shader>(L"DebugShader", debugShader);


	}

	void LoadMaterial()
	{
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"SmileTexture", L"Smile.png");
		// Default
		std::shared_ptr<Shader> shader = Resources::Find<Shader>(L"RectShader");
		std::shared_ptr<Material> material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		Resources::Insert<Material>(L"RectMaterial", material);



		// Sprite
		std::shared_ptr <Texture> spriteTexture = Resources::Load<Texture>(L"LightSprite", L"Light.png");
		std::shared_ptr<Shader> spriteShader = Resources::Find<Shader>(L"SpriteShader");
		std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
		spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
		spriteMaterial->SetShader(spriteShader);
		spriteMaterial->SetTexture(spriteTexture);
		Resources::Insert<Material>(L"SpriteMaterial", spriteMaterial);
		
		// UI
		std::shared_ptr <Texture> UITexture = Resources::Load<Texture>(L"HPSprite", L"HPBar.png");
		std::shared_ptr<Shader> UIShader = Resources::Find<Shader>(L"UIShader");
		std::shared_ptr<Material> UIMaterial = std::make_shared<Material>();
		UIMaterial->SetRenderingMode(eRenderingMode::Opaque);
		UIMaterial->SetShader(UIShader);
		UIMaterial->SetTexture(UITexture);
		Resources::Insert<Material>(L"UIMaterial", UIMaterial);

		// Grid
		std::shared_ptr<Shader> GridShader = Resources::Find<Shader>(L"GridShader");
		std::shared_ptr<Material> GridMaterial = std::make_shared<Material>();
		GridMaterial->SetRenderingMode(eRenderingMode::Opaque);
		GridMaterial->SetShader(GridShader);
		Resources::Insert<Material>(L"GridMaterial", GridMaterial);

		// CamEffect
		std::shared_ptr<Shader> CamEffectShader = Resources::Find<Shader>(L"CamEffectShader");
		std::shared_ptr<Material> CamEffectMaterial = std::make_shared<Material>();
		CamEffectMaterial->SetRenderingMode(eRenderingMode::Transparent);
		CamEffectMaterial->SetShader(CamEffectShader);
		Resources::Insert<Material>(L"CamEffectMaterial", CamEffectMaterial);

		// Debug
		std::shared_ptr<Shader> debugShader = Resources::Find<Shader>(L"DebugShader");
		std::shared_ptr<Material> debugMaterial = std::make_shared<Material>();
		debugMaterial->SetRenderingMode(eRenderingMode::Transparent);
		debugMaterial->SetShader(debugShader);
		Resources::Insert<Material>(L"DebugMaterial", debugMaterial);

	}

	void Initialize()
	{
		LoadMesh();
		LoadShader();
		SetUpState();
		LoadBuffer();
		LoadMaterial();

	}

	void Render()
	{
		eSceneType type = SceneManager::GetPlayScene()->GetSceneType();

		for (Camera* cam : cameras[(UINT)type])
		{
			if (cam == nullptr)
				continue;

			cam->Render();
		}
		cameras[(UINT)type].clear();
	}




	void Release()
	{
		for (size_t i = 0; i < (UINT)eCBType::End; i++)
		{
			delete constantBuffers[i];
			constantBuffers[i] = nullptr;
		}
	}

}