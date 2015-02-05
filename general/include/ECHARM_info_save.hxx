//
//  ECHARM_ROOT_save.hh
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

///
///   Class ECHARM_ROOT_save is a class derived from ECHARM_atom because it has all its characteristics averaged over the all the atom kind of the crystal.
///   It is really important to check that the ECHARM_ROOT_save is ok before procede with any calculation method of this class.
///   The crystal is formed by a single ECHARM_cell, a single ECHARM_miller class, and many ECHARM_atoms and ECHARM_lattice classes.
///   Each ECHARM_atom has a linked ECHARM_lattice which describe the position of the atom in the cell and the numer of the that atom kind in a unit cell.
///   ECHARM_cell descirbes the fundamental cell properties and affect the ECHARM_lattice class because ECHARM_lattice point coordinates are expressed in terms of the ECHARM_cell base three vectors.
///   ECHARM_miller describes the planar and axial Miller vIndexes on which the calculation are going to be made.
///   Planar electric characteristics can be evaluated for any kind of crystal structures.
///   At the present time any axial characteristic can be evaluated only for cubic structures. For general orthorhombic structures only main axes can be evaluated.
///   has to be filled with Miller vIndexes of the plane and axis on which the ECHARM_ROOT_save class will average electric characteristic.
///   The class automatically evaluete Miller vIndexes of two axes orthogonal to the selected axis. This evaluation is valid ONLY for CUBIC structure.
///

public:
void SetRadEmEn(std::vector<double> num) {fRadEmEn = num;};
inline std::vector<double> GetRadEmEn() {return fRadEmEn;};

inline std::vector<double> GetRadEmEnProb() {return fRadEmProb;};

void AddRadEmEnProb(int i0,double val){fRadEmProb.at(i0)+=val;};
void SetRadEmEnProb(int i0,double val){fRadEmProb.at(i0)=val;};

inline std::vector<double> GetEmittedPhEn() {return fEmittedPhEn;};

inline void SetPartIn(ECHARM_Particle_Save part) {fPartIn = part;};
inline ECHARM_Particle_Save GetPartIn() {return fPartIn;};

inline void SetPartOut(ECHARM_Particle_Save part) {fPartOut = part;};
inline ECHARM_Particle_Save GetPartOut() {return fPartOut;};

inline void SetPart(ECHARM_Particle_Save part) {fPart = part;};
inline ECHARM_Particle_Save GetPart() {return fPart;};
inline std::vector<ECHARM_Particle_Save> GetPartVec() {return fPartVec;};

inline std::vector<double> GetPot() {return fPot;};
inline std::vector<double> GetEFX() {return fEFX;};
inline std::vector<double> GetKin() {return fKin;};

inline void SetDispl(ECHARM_3vec* num) {fDispl->Set(num);};
inline ECHARM_3vec* GetDispl() {return fDispl;};
inline std::vector<double> GetDisplX() {return fDisplX;};
inline std::vector<double> GetDisplY() {return fDisplY;};
inline std::vector<double> GetDisplZ() {return fDisplZ;};

inline void SetBR(ECHARM_3vec* num) {fBR->Set(num);};
inline ECHARM_3vec* GetBR() {return fBR;};

inline void SetBeamSize(ECHARM_3vec* num) {fBeamSize->Set(num);};
inline ECHARM_3vec* GetBeamSize() {return fBeamSize;};

inline std::vector<double> GetAtD() {return fAtD;};
inline std::vector<double> GetElD() {return fElD;};

inline void AddAvgAtD(double num) {fAvgAtD += num;};
inline void DivideAvgAtD(double num) {fAvgAtD /= num;};

inline void SetAvgAtD(double num) {fAvgAtD = num;};
inline double GetAvgAtD() {return fAvgAtD;};

inline void AddAvgElD(double num) {fAvgElD += num;};
inline void DivideAvgElD(double num) {fAvgElD /= num;};

inline void SetAvgElD(double num) {fAvgElD = num;};
inline double GetAvgElD() {return fAvgElD;};

inline void SetChInitial(int val) {fChInitial = val;};
inline int GetChInitial() {return fChInitial;};

inline void AddChTimes() {fChTimes++;};
inline int GetChTimes() {return fChTimes;};

inline void AddDechTimes() {fDechTimes++;};
inline int GetDechTimes() {return fDechTimes;};

inline void SetPartNum(int part) {fPartNum = part;};
inline int GetPartNum() {return fPartNum;};

inline void SetCharge(double num) {fCharge = num;};
inline double GetCharge() {return fCharge;};

inline void SetMass(double num) {fMass = num;};
inline double GetMass() {return fMass;};
