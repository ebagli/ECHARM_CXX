///////////////////// CONSTANTS
#ifndef _ECHARM_constants_h
#define _ECHARM_constants_h

////// ELECTRON
#define cElectronMass 0.510998910E6 //eV
#define cElectronRadius 2.8179402894E-15 //m
#define cElectronCharge2 14.39967436638640E-10 //eV*m
#define cElectronLengthOnCharge 1.80951286662456995E-8 //eV*m on charge evaluated in unit of electron charge

////// PARTICLE MASSES
#define cProtonMass 938.272046E6 //eV
#define cPaiMass 139.57018E6 //eV
#define cNeutronMass 939.565378E6 //eV

////// GENERAL
#define c2Pi 6.28318530717958623 //
#define cPi 3.141592653589793238 //
#define cPiHalf 1.5707963267948965 //
#define cBohrRadius 0.529177E-10 //m
#define cEs 21.E6 //eV
#define cEmsPDG 13.6E6 //eV
#define cAvogadroNumber 6.02214129E23//mol-1
#define cFineStructureConstant 0.007299270072993  //pure number
#define cLightVelocity 1.
#define cPlanckConstant 197.326968E-9 //Planck constant over 2 pi times c in MeV fm == 197.326 968
#define cBoltzmanConstant 8.617343E-5 //Boltzmann constant in eV/K 

///////////////////// UNITS 
////// ENERGY
#define eV 1.
#define KeV 1.E3
#define MeV 1.E6
#define GeV 1.E9
#define TeV 1.E12
#define gram 5.60958884974569541E32
#define Kgram 5.60958884974569541E35
#define amu 931.494061E6


////// POSITION
#define meter 1.
#define micrometer 1.E-6
#define millimeter 1.E-3
#define millimeter2 1.E-6
#define millimeter3 1.E-9
#define centimeter 1.E-2
#define centimeter2 1.E-4
#define centimeter3 1.E-6
#define nanometer 1.E-9
#define AA 1.E-10
#define micron 1.E-6

/////// TEMPERATURE
#define K 1.

/////// ANGLES
#define deg 0.0174532925
#define rad 1.
#define millirad 1.E-3
#define microrad 1.E-6
#define arcsec 4.84813681109535984E-6
#define arcmin 2.908882086657216E-4

//Constant Source: Peter J. Mohr and Barry N. Taylor, CODATA Recommended Values of the Fundamental Physical Constants: 2002,
//published in Rev. Mod. Phys. vol. 77(1) 1-107 (2005).


///////////////////////////////////////////////

#define fRound(x) ((x)>=0.0?(long)((x)+0.5):(long)((x)-0.5))
#define fSign(x) ((x)!=0.0 ? (x)/fabs(x) : 0.0)
#define fSquare(x) (x)*(x)
#define fSquareRoot(x) sqrt(x)

#define DEBUG 0

#endif
