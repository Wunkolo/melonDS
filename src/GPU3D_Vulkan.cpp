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
#include <algorithm>

#include <vulkan/vulkan.hpp>
#include <vulkan/vulkan_core.h>

namespace GPU3D
{
    VulkanRenderer::VulkanRenderer()
        : Renderer3D(false)
    {

        //// Create Instance
        vk::InstanceCreateInfo InstanceCreateInfo = {};

        vk::ApplicationInfo ApplicationInfo = {};
        ApplicationInfo.pApplicationName = "melonDS " MELONDS_VERSION;
        ApplicationInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 0);
        ApplicationInfo.pEngineName = "melonDS " MELONDS_VERSION;
        ApplicationInfo.engineVersion = VK_MAKE_VERSION(0, 0, 0);
        ApplicationInfo.apiVersion = VK_API_VERSION_1_2;

        InstanceCreateInfo.pApplicationInfo = &ApplicationInfo;

        // Instance validation layers
        static const char* ValidationLayers[] = {
        #ifndef NDEBUG
            "VK_LAYER_KHRONOS_validation"
        #endif
        };
        InstanceCreateInfo.enabledLayerCount = std::extent_v<decltype(ValidationLayers)>;
        InstanceCreateInfo.ppEnabledLayerNames = ValidationLayers;

        // Instance extensions
        InstanceCreateInfo.enabledExtensionCount = 0;
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

        VULKAN_HPP_DEFAULT_DISPATCHER.init(Vk.Instance.get());
        
        //// Pick physical device
        // Todo: Make this something the user selects
        std::vector<vk::PhysicalDevice> PhysicalDevices = {};

        if (
            auto EnumerateResult = Vk.Instance->enumeratePhysicalDevices();
            EnumerateResult.result == vk::Result::eSuccess
        )
        {
            PhysicalDevices = std::move(EnumerateResult.value);
        }
        else
        {
            // Failed to enumerate physical devices
        }

        // Partition the Physical device array as much as possible to pick the best devices
        auto CurPivot = PhysicalDevices.end();

        // Discrete GPUs
        CurPivot = std::stable_partition(
            PhysicalDevices.begin(), CurPivot,
            [](const vk::PhysicalDevice& CurrentDevice) -> bool
            {
                const auto DeviceProperties = CurrentDevice.getProperties();
                return DeviceProperties.deviceType == vk::PhysicalDeviceType::eDiscreteGpu;
            }
        );

        // Supports extended image formats for storage-images
        // Mostly for R8_UINT and R8_UNORM and such
        CurPivot = std::stable_partition(
            PhysicalDevices.begin(), CurPivot,
            [](const vk::PhysicalDevice& CurrentDevice) -> bool
            {
                const auto DeviceFeatures = CurrentDevice.getFeatures();
                return DeviceFeatures.shaderStorageImageExtendedFormats == true;
            }
        );

        // At this point, the devices are now sorted from best to worst based on our criteria above
        Vk.PhysicalDevice = PhysicalDevices[0];

        //// Create device
        vk::DeviceCreateInfo DeviceInfo = {};

        // Device Layers
        DeviceInfo.enabledLayerCount = 0;
        DeviceInfo.ppEnabledLayerNames = nullptr;

        // Device Extensions
        DeviceInfo.enabledExtensionCount = 0;
        DeviceInfo.ppEnabledExtensionNames = nullptr;

        /// Queue allocation
        // We just want 1 queue for everything for now

        vk::DeviceQueueCreateInfo QueueInfo = {};

        QueueInfo.queueCount = 1;
        static constexpr float QueuePriorityMax = 1.0f; // Highest priority
        QueueInfo.pQueuePriorities = &QueuePriorityMax;

        // On all platforms, this is the "generic" queue that supports all
        // graphics/compute/transfer operations
        QueueInfo.queueFamilyIndex = 0;

        DeviceInfo.queueCreateInfoCount = 1;
        DeviceInfo.pQueueCreateInfos = &QueueInfo;

        if (
            auto DeviceResult = Vk.PhysicalDevice.createDeviceUnique(DeviceInfo);
            DeviceResult.result == vk::Result::eSuccess
        )
        {
            Vk.Device = std::move(DeviceResult.value);
        }
        else
        {
            // Error creating Logical device
        }

        Vk.Queue = Vk.Device->getQueue(0, 0);

        const vk::PhysicalDeviceProperties DeviceProperties = Vk.PhysicalDevice.getProperties();
        printf(
            "Vulkan Context created:\n"
            "\tDevice: %.256s\n"
            "\tType: %.64s\n"
            "\tID: %08X\n"
            "\tVendor: %s\n"
            "\tDriver: %u.%u.%u\n"
            "\tAPI: %u.%u.%u\n",
            DeviceProperties.deviceName.data(),
            vk::to_string(DeviceProperties.deviceType).c_str(),
            DeviceProperties.deviceID,
            Vulkan::VendorName(static_cast<Vulkan::VendorID>(DeviceProperties.vendorID)),
            VK_VERSION_MAJOR(DeviceProperties.driverVersion),
            VK_VERSION_MINOR(DeviceProperties.driverVersion),
            VK_VERSION_PATCH(DeviceProperties.driverVersion),
            VK_VERSION_MAJOR(DeviceProperties.apiVersion),
            VK_VERSION_MINOR(DeviceProperties.apiVersion),
            VK_VERSION_PATCH(DeviceProperties.apiVersion)
        );
    }

    VulkanRenderer::~VulkanRenderer()
    {
        puts("Vulkan DTOR");
    }

    bool VulkanRenderer::Init()
    {
        puts("Vulkan Renderer Init");
        return true;
    }

    void VulkanRenderer::DeInit()
    {
        puts("Vulkan Renderer DeInit");
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
        static std::array<u32, 256> PlaceHolderScanline = {};
        return PlaceHolderScanline.data();
    }
}
