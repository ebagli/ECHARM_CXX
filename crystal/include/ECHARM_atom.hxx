//
//  ECHARM_atom.h
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

///
///   This class has to be filled with atomic parameters only.
///   Thermal vibration amplitude is automatically evaluated.
///   No input from standard databases are implemented right now.
///

public:
inline std::string  GetAtomName()   {return fAtomName;} //!< Get name.
inline void SetAtomName(std::string AtomName)    {fAtomName=AtomName;} //!< Set name.

inline double GetZ() {return fZ;}      //!< Get atomic number Z.
inline void SetZ(double Z) {fZ=Z;}         //!< Set atomic number Z.

inline double GetA() {return fA;}    //!< Get atomic A in amu.
inline void SetA(double A) {fA=A;}     //!< Set atomic weight in amu.

inline double GetDebyeTemperature() {return fDebyeTemperature;}   //!< Get Debye Temperature in K.
inline void SetDebyeTemperature(double DebyeTemperature) {fDebyeTemperature=DebyeTemperature; ComputeThermalVibration();}    //!< Set Debye Temperature in K.

inline double GetAverageIonizationConstant() {return fAverageIonizationConstant;}    //!< Get Ionization Constant in eV.
inline void SetAverageIonizationConstant(double AverageIonizationConstant) {fAverageIonizationConstant=AverageIonizationConstant;}      //!< Set Ionization Constant in eV.

inline double GetTemperature() {return fTemperature;}   //!< Get Temperature in K.
inline void SetTemperature(double Temperature) {fTemperature=Temperature;}     //!< Set Temperature in K.

inline double GetThermalVibrationConstant()      {return fThermalVibrationConstant;}     //!< Get Thermal Vibration Amplitude in meter.
inline void SetThermalVibrationConstant(double ThermalVibrationConstant) {fThermalVibrationConstant=ThermalVibrationConstant;}     //!< Set Thermal Vibration Amplitude in meter.

inline double GetThomasFermiRadius()      {return fThomasFermiRadius;}     //!< Get Thomas Fermi Radius in meter.
inline void SetThomasFermiRadius(double ThomasFermiRadius) {fThomasFermiRadius=ThomasFermiRadius;}     //!< Set Thomas Fermi Radius in meter.