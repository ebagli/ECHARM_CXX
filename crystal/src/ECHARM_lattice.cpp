//
//  ECHARM_lattice.cpp
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#include "ECHARM_lattice.hh"

ECHARM_lattice::ECHARM_lattice(){
    fLatticeCoordinates.clear();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_lattice::~ECHARM_lattice(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_lattice::Print(){
    std::cout << "ECHARM_lattice - Print Lattice Coordinates" << std::endl;
    std::cout << "Point       X/X_0   Y/Y_0   Z/Z_0" << std::endl;
    for(unsigned int i = 0;i<fLatticeCoordinates.size();i++) {
        fLatticeCoordinates.at(i)->Print();
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_lattice::ReadFile(std::string vFileName){
    std::ifstream File_LatticeIn;
    ECHARM_3vec *vector_old = new ECHARM_3vec();
    File_LatticeIn.open(vFileName.c_str());
    if(File_LatticeIn)
    {
        int nlines = 0;
        double temp_x,temp_y,temp_z;
        temp_x = temp_y = temp_z = 0.0;
        do
        {
            vector_old->Set(temp_x,temp_y,temp_z);
            if(!File_LatticeIn.eof()) File_LatticeIn >> temp_x;
            if(!File_LatticeIn.eof()) File_LatticeIn >> temp_y;
            if(!File_LatticeIn.eof()) File_LatticeIn >> temp_z;
            if(nlines == 0) Add(temp_x,temp_y,temp_z);
            else if(!(   (temp_x == vector_old->GetX())
                      && (temp_y == vector_old->GetY())
                      && (temp_z == vector_old->GetZ())))
            {
                Add(temp_x,temp_y,temp_z);
            }
            nlines++;
        } while (!File_LatticeIn.eof());
        std::cout << "ECHARM_lattice - " << nlines << " lines have been read" << std::endl;
    }
    else std::cout << "ECHARM_lattice ERROR - lattice & lattice file do not exist" << std::endl;
    File_LatticeIn.close();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_lattice::ReadFile(std::string vFileName, ECHARM_3vec *vSize){
    std::ifstream File_LatticeIn;
    ECHARM_3vec *vector_old = new ECHARM_3vec();
    File_LatticeIn.open(vFileName.c_str());
    if(File_LatticeIn)
    {
        int nlines = 0;
        double temp_x,temp_y,temp_z;
        temp_x = temp_y = temp_z = 0.0;
        do
        {
            vector_old->Set(temp_x,temp_y,temp_z);
            if(!File_LatticeIn.eof()) File_LatticeIn >> temp_x;
            if(!File_LatticeIn.eof()) File_LatticeIn >> temp_y;
            if(!File_LatticeIn.eof()) File_LatticeIn >> temp_z;
            if(nlines == 0) Add(temp_x/vSize->GetX(),temp_y/vSize->GetY(),temp_z/vSize->GetZ());
            else if(!(   (temp_x == vector_old->GetX())
                      && (temp_y == vector_old->GetY())
                      && (temp_z == vector_old->GetZ())))
            {
                Add(temp_x/vSize->GetX(),temp_y/vSize->GetY(),temp_z/vSize->GetZ());
            }
            nlines++;
        } while (!File_LatticeIn.eof());
        std::cout << "ECHARM_lattice - " << nlines << " lines have been read" << std::endl;
    }
    else std::cout << "ECHARM_lattice ERROR - lattice & lattice file do not exist" << std::endl;
    File_LatticeIn.close();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

std::vector<double> ECHARM_lattice::ComputeSF(int vIndex[3]){
    std::vector<double> vSF;
    double vTempDouble = 0.0;
    
    vSF.push_back(0.0);
    vSF.push_back(0.0);

    for(unsigned int i=0;i<fLatticeCoordinates.size();i++){
        vTempDouble = 0.0;
        for(unsigned int k=0;k<3;k++) {
            vTempDouble += double(vIndex[k]) * fLatticeCoordinates.at(i)->Get(k);
        }
        vSF.at(0) += cos(2 * cPi * vTempDouble);
        vSF.at(1) += sin(2 * cPi * vTempDouble);
    }
    
    return vSF;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

std::vector<double> ECHARM_lattice::ComputeSF(int vIndex00,int vIndex01,int vIndex02){
    int vIndex[3];
    vIndex[0]=vIndex00;
    vIndex[1]=vIndex01;
    vIndex[2]=vIndex02;
    return ComputeSF(vIndex);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


