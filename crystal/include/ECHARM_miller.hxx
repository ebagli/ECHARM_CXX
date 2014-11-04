//
//  ECHARM_miller.h
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//
//  Short class description:
//   Class ECHARM_miller has to be filled with Miller vIndexes of the plane and axis on which the ECHARM_crystal class will average electric characteristic.
//   The class automatically evaluete Miller vIndexes of two axes orthogonal to the selected axis. This evaluation is valid ONLY for CUBIC structure.

public:
inline int* Get(int vIndex) {return fMiller[vIndex];};
inline int* GetX() {return fMiller[1];};
inline int* GetY() {return fMiller[2];};
inline int* GetZ() {return fMiller[0];};

inline int GetX(int vIndex) {return fMiller[1][vIndex];};
inline int GetY(int vIndex) {return fMiller[2][vIndex];};
inline int GetZ(int vIndex) {return fMiller[0][vIndex];};

inline double GetModule(int vIndex) {return fSquareRoot(fSquare(GetModuleSquared(vIndex)));};
inline double GetModuleX() {return GetModule(1);};
inline double GetModuleY() {return GetModule(2);};
inline double GetModuleZ() {return GetModule(0);};

inline double GetModuleSquaredX() {return GetModuleSquared(1);};
inline double GetModuleSquaredY() {return GetModuleSquared(2);};
inline double GetModuleSquaredZ() {return GetModuleSquared(0);};

inline std::string GetTextX() {return GetText(fMiller[1]);};
inline std::string GetTextY() {return GetText(fMiller[2]);};
inline std::string GetTextZ() {return GetText(fMiller[0]);};

inline void Set(int vIndex,int Miller[3]) {
    for(unsigned int i=0;i<3;i++) {
        fMiller[vIndex][i] = Miller[i];};
    }
inline void SetX(int Miller[3]) {Set(1,Miller);};
inline void SetY(int Miller[3]) {Set(2,Miller);};
inline void SetZ(int Miller[3]) {Set(0,Miller);};
