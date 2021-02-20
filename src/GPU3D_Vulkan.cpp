/*
    Copyright 2016-2020 Arisotura

    This file is part of melonDS.

    melonDS is free software: you can redistribute it and/or modify it under
    the terms of the GNU General Public License as published by the Free
    Software Foundation, either version 3 of the License, or (at your option)
    any later version.

    melonDS is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with melonDS. If not, see http://www.gnu.org/licenses/.
*/

#include "GPU3D_Vulkan.h"

#include <array>
#include <vulkan/vulkan.hpp>
#include <vulkan/vulkan_core.h>

namespace GPU3D
{
	VulkanRenderer::VulkanRenderer()
		: Renderer3D(false)
	{
		vk::InstanceCreateInfo InstanceCreateInfo = {};

		vk::ApplicationInfo ApplicationInfo = {};
		ApplicationInfo.pApplicationName = "melonDS " MELONDS_VERSION;
		ApplicationInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 0);
		ApplicationInfo.pEngineName = "melonDS " MELONDS_VERSION;
		ApplicationInfo.engineVersion = VK_MAKE_VERSION(0, 0, 0);
		ApplicationInfo.apiVersion = VK_VERSION_1_1;

		InstanceCreateInfo.pApplicationInfo = &ApplicationInfo;

		InstanceCreateInfo.enabledExtensionCount = 0;
		InstanceCreateInfo.ppEnabledExtensionNames = nullptr;

		InstanceCreateInfo.enabledLayerCount = 0;
		InstanceCreateInfo.ppEnabledExtensionNames = nullptr;

		if (
			auto InstanceResult = vk::createInstanceUnique(InstanceCreateInfo);
			InstanceResult.result == vk::Result::eSuccess
		)
		{
			Vk.Instance = std::move(InstanceResult.value);
		}
		else
		{
			// Failed to create instance
		}
	}

	VulkanRenderer::~VulkanRenderer()
	{
	}

    bool VulkanRenderer::Init()
    {
        return true;
    }
    void VulkanRenderer::DeInit()
    {

    }
    void VulkanRenderer::Reset()
    {

    }
    void VulkanRenderer::SetRenderSettings(GPU::RenderSettings& settings)
    {

    }
    void VulkanRenderer::RenderFrame()
    {

    }
    u32* VulkanRenderer::GetLine(int line)
    {
        return nullptr;
    }
}
