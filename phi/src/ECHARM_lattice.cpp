//
//  ECHARM_lattice.cpp
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

ECHARM_lattice::ECHARM_lattice()
{
    InitializePointersLattice();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_lattice::ECHARM_lattice(std::string LatticeType)
{
    InitializePointersLattice();
    fLatticeType = LatticeType;
    FindLatticePoints();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_lattice::~ECHARM_lattice()
{
    if (&fLatticeType)         { delete &fLatticeType; }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const ECHARM_lattice& ECHARM_lattice::operator=(const ECHARM_lattice& right)
{
    if (this != &right)
    {
        InitializePointersLattice();
        fLatticeType = right.fLatticeType;
        fLatticeCoordinates = right.fLatticeCoordinates;
        for(unsigned int i = 0;i<right.fLatticeCoordinates.size();i++) fLatticeCoordinates.push_back(right.fLatticeCoordinates.at(i));
    }
    return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_lattice::InitializePointersLattice()
{
    fLatticeType.clear();
    fLatticeCoordinates.clear();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_lattice::PrintLatticeCoordinates()
{
    std::cout << "ECHARM_lattice - Print Lattice " << fLatticeType << " Coordinates" << std::endl;
    std::cout << "Point       X/X_0   Y/Y_0   Z/Z_0" << std::endl;
    for(unsigned int i = 0;i<fLatticeCoordinates.size();i++) fLatticeCoordinates.at(i)->PrintThreeVector();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_lattice::PrintLatticeCoordinates(std::string Axis)
{
    std::cout << "ECHARM_lattice - Print Lattice " << fLatticeType << " Coordinates" << std::endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_lattice::AddThreeVector(double X,double Y,double Z)
{
    ECHARM_threevector *vector = new ECHARM_threevector(X,Y,Z);
    fLatticeCoordinates.push_back(vector);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_lattice::DeleteThreeVector(unsigned int vIndex)
{
    fLatticeCoordinates.erase(fLatticeCoordinates.begin()+vIndex);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_lattice::FindLatticePoints()
{
    if(fLatticeType == "cubic")
    {
//        std::cout << "ECHARM_lattice - Face Centered Cubic Lattice Created" << std::endl;
        AddThreeVector(0.0,0.0,0.0);
    }
    else if(fLatticeType == "cubicc")
    {
        //        std::cout << "ECHARM_lattice - Face Centered Cubic Lattice Created" << std::endl;
        AddThreeVector(0.5,0.5,0.5);
    }
    else if(fLatticeType == "bcc")
    {
//        std::cout << "ECHARM_lattice - Face Centered Cubic Lattice Created" << std::endl;
        AddThreeVector(0.0,0.0,0.0);
        AddThreeVector(0.5,0.5,0.5);
    }
    else if(fLatticeType == "fcc")
    {
//        std::cout << "ECHARM_lattice - Face Centered Cubic Lattice Created" << std::endl;
        AddThreeVector(0.0,0.0,0.0);
        AddThreeVector(0.5,0.5,0.0);
        AddThreeVector(0.0,0.5,0.5);
        AddThreeVector(0.5,0.0,0.5);
   }    
    else if(fLatticeType == "diamond")
    {
//        std::cout << "ECHARM_lattice - Diamond Lattice Created" << std::endl;
        for(unsigned int i=0;i<2;i++)
        {
            AddThreeVector(0.0+0.25*i,0.0+0.25*i,0.0+0.25*i);
            AddThreeVector(0.5+0.25*i,0.5+0.25*i,0.0+0.25*i);
            AddThreeVector(0.0+0.25*i,0.5+0.25*i,0.5+0.25*i);
            AddThreeVector(0.5+0.25*i,0.0+0.25*i,0.5+0.25*i);
        }
    }
    else
    {
        ReadCoordinatesFromFile(fLatticeType);
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_lattice::ReadCoordinatesFromFile(std::string vFileName)
{
    std::ifstream File_LatticeIn;
    ECHARM_threevector *vector_old = new ECHARM_threevector();
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
            if(nlines == 0) AddThreeVector(temp_x,temp_y,temp_z);
            else if(!(   (temp_x == vector_old->GetX())
                      && (temp_y == vector_old->GetY())
                      && (temp_z == vector_old->GetZ())))
            {
                AddThreeVector(temp_x,temp_y,temp_z);
            }
            nlines++;
        } while (!File_LatticeIn.eof());
        std::cout << "ECHARM_lattice - " << nlines << " lines have been read" << std::endl;
    }
    else std::cout << "ECHARM_lattice ERROR - lattice & lattice file do not exist" << std::endl;
    File_LatticeIn.close();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_lattice::ReadCoordinatesNotNormalizedFromFile(std::string vFileName, ECHARM_threevector *vSize)
{
    std::ifstream File_LatticeIn;
    ECHARM_threevector *vector_old = new ECHARM_threevector();
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
            if(nlines == 0) AddThreeVector(temp_x/vSize->GetX(),temp_y/vSize->GetY(),temp_z/vSize->GetZ());
            else if(!(   (temp_x == vector_old->GetX())
                      && (temp_y == vector_old->GetY())
                      && (temp_z == vector_old->GetZ())))
            {
                AddThreeVector(temp_x/vSize->GetX(),temp_y/vSize->GetY(),temp_z/vSize->GetZ());
            }
            nlines++;
        } while (!File_LatticeIn.eof());
        std::cout << "ECHARM_lattice - " << nlines << " lines have been read" << std::endl;
    }
    else std::cout << "ECHARM_lattice ERROR - lattice & lattice file do not exist" << std::endl;
    File_LatticeIn.close();
    //delete &vector_old;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_lattice::operator==(const ECHARM_lattice& right) const
{
    return (this == (ECHARM_lattice*) &right);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_lattice::operator!=(const ECHARM_lattice& right) const
{
    return (this != (ECHARM_lattice*) &right);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

std::vector<double> ECHARM_lattice::FindStructureFactor(int vIndex[3])
{
    std::vector<double> vSF;
    double vTempDouble = 0.0;
    
    vSF.push_back(0.0);
    vSF.push_back(0.0);

    for(unsigned int i=0;i<fLatticeCoordinates.size();i++)
    {
        vTempDouble = 0.0;
        for(unsigned int k=0;k<3;k++) vTempDouble += double(vIndex[k]) * fLatticeCoordinates.at(i)->GetComponent(k);
        vSF.at(0) += cos(2 * M_PI * vTempDouble);
        vSF.at(1) += sin(2 * M_PI * vTempDouble);
    }
    
    return vSF;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

std::vector<double> ECHARM_lattice::FindStructureFactor(int vIndex00,int vIndex01,int vIndex02)
{
    int vIndex[3];
    vIndex[0]=vIndex00;
    vIndex[1]=vIndex01;
    vIndex[2]=vIndex02;
    std::vector<double> vSF = FindStructureFactor(vIndex);
    return vSF;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


