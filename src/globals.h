#pragma once

#ifndef GLOBALS_H
#define GLOBALS_H

#include <string>

struct PhysicalConstant {
	double value;
	std::string unit;
};

namespace GLOBALS {
	inline constexpr double EPSILON(1e-6);
	inline const PhysicalConstant EV({ 1.60217653e-19, "C" });
	inline const PhysicalConstant C({ 299792458, "m/s" });
	inline const PhysicalConstant M_PROTON({ 0.938272, "GeV/c^2" });
	inline const PhysicalConstant M_ELECTRON({ 5.10999e-4, "GeV/c^2" });
};

#endif
