#pragma once
#include "yaGraphics.h"

namespace ya::graphics
{
	class ConstantBuffer :  GpuBuffer
	{
	public:
		ConstantBuffer(eCBType type);
		virtual ~ConstantBuffer();

		bool Create(size_t size);
		void Bind(void* data);
		void SetPipline(eShaderStage stage);

	private:
		const eCBType mType;
	};

}

