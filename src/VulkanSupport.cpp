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

#include "VulkanSupport.h"

VULKAN_HPP_DEFAULT_DISPATCH_LOADER_DYNAMIC_STORAGE;

static const bool VulkanLoader = []() -> bool
{
    static vk::DynamicLoader dl;
    VULKAN_HPP_DEFAULT_DISPATCHER.init(
        dl.getProcAddress<PFN_vkGetInstanceProcAddr>("vkGetInstanceProcAddr")
    );
    return true;
}();

namespace Vulkan
{
const char* VendorName(VendorID Vendor)
{
    switch( Vendor )
    {
    case VendorID::AMD:
    {
        return "AMD";
    }
    case VendorID::ImgTec:
    {
        return "ImgTec";
    }
    case VendorID::Nvidia:
    {
        return "Nvidia";
    }
    case VendorID::ARM:
    {
        return "ARM";
    }
    case VendorID::Qualcomm:
    {
        return "Qualcomm";
    }
    case VendorID::Intel:
    {
        return "Intel";
    }
    }
    return "Unknown";
}
}