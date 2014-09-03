//
//  ECHARM_miller.cpp
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#include "ECHARM_miller.hh"
#include <sstream>

ECHARM_miller::ECHARM_miller(){
    for(unsigned int i=1;i<3;i++){
        for(unsigned int j=0;j<3;j++) fMiller[i][j] = 0;
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_miller::ECHARM_miller(int X[3],int Y[3],int Z[3]){
    SetX(X);
    SetY(Y);
    SetZ(Z);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_miller::ECHARM_miller(int X[3],int Z[3]){
    SetX(X);
    SetZ(Z);
    ComputeMiller();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_miller::ECHARM_miller(int Z[3]){
    SetZ(Z);
    ComputeMiller();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_miller::~ECHARM_miller(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_miller::Print(){
    std::cout << "ECHARM_miller - Print Indexes" << std::endl;
    std::cout << "( " << std::setw(3) << fMiller[1][0] << " " << std::setw(3) << fMiller[1][1] << " " << std::setw(3) << fMiller[1][2] << "  )" << std::endl;
    std::cout << "( " << std::setw(3) << fMiller[2][0] << " " << std::setw(3) << fMiller[2][1] << " " << std::setw(3) << fMiller[2][2] << "  )" << std::endl;
    std::cout << "< " << std::setw(3) << fMiller[0][0] << " " << std::setw(3) << fMiller[0][1] << " " << std::setw(3) << fMiller[0][2] << "  >" << std::endl;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

std::string ECHARM_miller::GetText(int vMiller[3]){
    std::stringstream vSS;
    vSS << vMiller[0] << vMiller[1] << vMiller[2];
    std::string vBaseName = vSS.str();
    return vBaseName;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_miller::ComputeMiller(){
    //NO MILLER COMPUTATION
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//
//This function check if Miller axial vectors are orthogonal each other
//

bool ECHARM_miller::IsMainAxis(){
    if( (fMiller[0][0] == 1) && (fMiller[0][1] == 0) && (fMiller[0][2] == 0) ) return true;
    if( (fMiller[0][0] == 0) && (fMiller[0][1] == 1) && (fMiller[0][2] == 0) ) return true;
    if( (fMiller[0][0] == 0) && (fMiller[0][1] == 0) && (fMiller[0][2] == 1) ) return true;
    return false;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//
//This function check if MillerOrthogonal[0] & MillerOrthogonal[1] vIndexes can be used and, if they can  be used, the MillerOrthogonal[2] is the third vIndex of the orthogonal vector
//
bool ECHARM_miller::CheckOrthogonalityToAxis(int MillerOrthogonal[3]){
    return false;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//
//
void ECHARM_miller::ReverseMillerOrder(int MillerOrthogonal[3]){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//
//This function check if Miller axial vectors are orthogonal each other
//

bool ECHARM_miller::CheckOrthogonality(){
    return false;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_miller::GetModuleSquared(int vIndex){
    return (fSquare(double(fMiller[vIndex][0])) + fSquare(double(fMiller[vIndex][1])) + fSquare(double(fMiller[vIndex][2])));
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
