//
//  ECHARM_miller_orto.cpp
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#include "ECHARM_miller_orto.hh"
#include <sstream>

ECHARM_miller_orto::ECHARM_miller_orto(int X[3],int Y[3],int Z[3]){
    SetX(X);
    SetY(Y);
    SetZ(Z);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_miller_orto::ECHARM_miller_orto(int X[3],int Z[3]){
    SetX(X);
    SetZ(Z);
    ComputeMiller();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_miller_orto::ECHARM_miller_orto(int Z[3]){
    SetZ(Z);
    ComputeMiller();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_miller_orto::~ECHARM_miller_orto(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_miller_orto::ComputeMiller(){
    if((fMiller[0][0]!=0) && (fMiller[0][1]==0) && (fMiller[0][2]==0))
    {
        fMiller[1][0] = 0; fMiller[1][1] = 1; fMiller[1][2] = 0;
		fMiller[2][0] = 0; fMiller[2][1] = 0; fMiller[2][2] = 1;
    }
    else if((fMiller[0][0]==0) && (fMiller[0][1]!=0) && (fMiller[0][2]==0))
    {
		fMiller[1][0] = 0; fMiller[1][1] = 0; fMiller[1][2] = 1;
		fMiller[2][0] = 1; fMiller[2][1] = 0; fMiller[2][2] = 0;
    }
    else if((fMiller[0][0]==0) && (fMiller[0][1]==0) && (fMiller[0][2]!=0))
    {
		fMiller[1][0] = 1; fMiller[1][1] = 0; fMiller[1][2] = 0;
		fMiller[2][0] = 0; fMiller[2][1] = 1; fMiller[2][2] = 0;
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//
//This function check if MillerOrthogonal[0] & MillerOrthogonal[1] vIndexes can be used and, if they can  be used, the MillerOrthogonal[2] is the third vIndex of the orthogonal vector
//
bool ECHARM_miller_orto::CheckOrthogonalityToAxis(int MillerOrthogonal[3]){
    return false;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//
//This function check if Miller axial vectors are orthogonal each other
//

bool ECHARM_miller_orto::CheckOrthogonality(){
    int vIndexesSum = 0;
    for(unsigned int i=0;i<3;i++)
        for(unsigned int j=i+1;j<3;j++)
            for(unsigned int k=0;k<3;k++)
                vIndexesSum += (fMiller[i][k]*fMiller[j][k]);
    
    if(vIndexesSum==0) return true;
    
    std::cout << "ECHARM_miller_orto - Axial Indexes are not orthogonal" << std::endl;
    
    return false;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

