#include "yaMesh.h"
#include "yaRenderer.h"

using namespace ya::enums;
namespace ya
{
	Mesh::Mesh()
		: Resource(eResourceType::Mesh)
		, mVetexDesc{}
		, mIndexDesc{}
		, mIndexCount(0)
	{
	}

	Mesh::~Mesh()
	{
	}

	HRESULT Mesh::Load(const std::wstring& path)
	{

		return S_OK;
	}

	bool Mesh::CreateVertexBuffer(void* data, UINT count)
	{

		mVetexDesc.ByteWidth = sizeof(renderer::Vertex) * count;
		mVetexDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		mVetexDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		mVetexDesc.CPUAccessFlags =0;

		D3D11_SUBRESOURCE_DATA subData = {};
		subData.pSysMem = data;

		if (!GetDevice()->CreateBuffer(&mVetexDesc, &subData, mVertexBuffer.GetAddressOf()))
			return false;
		
		return true;
	}

	bool Mesh::CreateIndexBuffer(void* data, UINT count)
	{
		mIndexCount = count;
		mIndexDesc.ByteWidth = sizeof(UINT) * count;
		mIndexDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
		mIndexDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		mIndexDesc.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA idxData = {};
		idxData.pSysMem = data;

		if(!GetDevice()->CreateBuffer(&mIndexDesc, &idxData, mIndexBuffer.GetAddressOf()))
			return false;

		return true;
	}

	void Mesh::BindBuffer()
	{

		//버텍스 정보를 인풋 어셈블러에 넣어준다.
		UINT vertexSize = sizeof(renderer::Vertex);
		UINT offset = 0;
		GetDevice()->BindVertexBuffer(0, 1, mVertexBuffer.GetAddressOf(), &vertexSize, &offset);
		GetDevice()->BindIndexBuffer(mIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);


	}

	void Mesh::Render()
	{
		GetDevice()->DrawIndexed(mIndexCount, 0, 0);
	}

}