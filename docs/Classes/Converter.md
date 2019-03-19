# `Converter.h`

Utility to convert from SI to GeV and back

```cpp
// 1 eV = 1.60217653e-19 Joules
CONVERT::EnergyEVtoSI(1); // 1.60217653e-19

// 0.938272 GeV/c² (mass of the proton) = 1.67262e-27 kg
CONVERT::MassGeVtoSI(CONSTANTS::M_PROTON);
// 9.10938e-31 kg (mass of the electron) = 5.10999e-4 GeV/c²
CONVERT::MassSItoGeV(9.10938e-31);
// 9.10938e-31 kg (mass of the electron) = 510999 eV/c²
CONVERT::MassSItoEV(9.10938e-31);

// (1, 2, -1) GeV/c (momentum) = (5.34429e-19, 1.06886e-18, -5.34429e-19) kg*m/s
CONVERT::MomentumGeVtoSI(Vector3D(1, 2, -1));
```

Available functions:

- Mass (Argument: `double`, Returns: `double`)
	- `MassEVtoSI`
	- `MassGeVtoSI`
	- `MassSItoEV`
	- `MassSItoGeV`
- Energy (Argument: `double`, Returns: `double`)
	- `EnergyEVtoSI`
	- `EnergyGeVtoSI`
	- `EnergySItoEV`
	- `EnergySItoGeV`
- Momentum (Argument: `Vector3D`, Returns: `Vector3D`)
	- `MomentumEVtoSI`
	- `MomentumGeVtoSI`
	- `MomentumSItoEV`
	- `MomentumSItoGeV`
