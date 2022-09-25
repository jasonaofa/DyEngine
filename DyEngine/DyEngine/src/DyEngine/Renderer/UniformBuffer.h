#pragma once

#include "DyEngine/Core/Base.h"

namespace DyEngine {
	/**
	 * \brief 为了能够在新建shader的时候，不需要重复传uniform给shader（比如投影矩阵，这种几乎所有shader都是一样的东西）
	 * 于是用这个类来储存数据，在render2d中 begin scene的时候，就把数据传递给所有shader。
	 */
	class UniformBuffer
	{
	public:
		virtual ~UniformBuffer() {}
		/**
		 * \brief 
		 * \param data 
		 * \param size 
		 * \param offset 
		 */
		virtual void SetData(const void* data, uint32_t size, uint32_t offset = 0) = 0;

		/**
		 * \brief 创建UniformBuffer
		 * \param size 
		 * \param binding binding的槽位
		 * \return 
		 */
		static Ref<UniformBuffer> Create(uint32_t size, uint32_t binding);
	};

}