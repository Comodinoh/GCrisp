#pragma once
#include <GCrisp/Core/Application.h>

#include "VKWindow.h"

namespace GCrisp
{
namespace Utils
{
static void GetVendorName(uint32_t vendorID, std::string_view* result)
{
	switch (vendorID) {
	case 0x1002: {
		*result = "AMD";
		return;
	}
	case 0x1010: {
		*result = "ImgTec";
		return;
	}
	case 0x10DE: {
		*result = "NVIDIA";
		return;
	}
	case 0x13B5: {
		*result = "ARM";
		return;
	}
	case 0x5143: {
		*result = "Qualcomm";
		return;
	}
	case 0x8086: {
		*result = "INTEL";
		return;
	}
	default: {
		result = nullptr; // Might be better to return a SUCCESS/FAIL result.
		return;
	}
	}
}
} // namespace Utils
} // namespace GCrisp
