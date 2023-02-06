#pragma once
#include "yaGraphics.h"

namespace ya
{
	using namespace ya::graphics;
	class ConstantBuffer : public GpuBuffer
	{
	public:
		ConstantBuffer();
		~ConstantBuffer();

		bool Create(size_t size);
		void Bind(void* data);
		void SetPipline(eShaderStage stage);

	private:
		const eCBType mType;
	};

}

