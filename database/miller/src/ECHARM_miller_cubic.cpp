//
//  ECHARM_miller_cubic.cpp
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifdef _ECHARM_miller_cubic_h

#include "ECHARM_miller_cubic.hh"
#include <sstream>

ECHARM_miller_cubic::ECHARM_miller_cubic(int X[3],int Y[3],int Z[3]){
    SetX(X);
    SetY(Y);
    SetZ(Z);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_miller_cubic::ECHARM_miller_cubic(int X[3],int Z[3]){
    SetZ(Z);
    ComputeMiller();
    SetX(X);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_miller_cubic::ECHARM_miller_cubic(int Z[3]){
    SetZ(Z);
    ComputeMiller();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_miller_cubic::~ECHARM_miller_cubic(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_miller_cubic::ComputeMiller(){
    int i,j,k,l;
    
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
    else
    {
        if((fMiller[0][0]!=0) && (fMiller[0][1]!=0))
        {
            k = 1;
            do
            {
                for(i=k;i>=-k;i--)
                    if(i!=0)
                        for(j=k;j>=-k;j--)
                            if(j!=0)
                                if(fMiller[0][0]*i==-fMiller[0][1]*j)
                                {fMiller[1][0] = i;fMiller[1][1] = j;fMiller[1][2] = 0;}
                k++;
            }
            while((fMiller[1][0] == 0) && (fMiller[1][1] == 0) && (fMiller[1][2] == 0));
        }
        
        if((fMiller[0][1]!=0) && (fMiller[0][2]!=0))
        {
            k = 1;
            do
            {
                for(i=k;i>=-k;i--)
                    if(i!=0)
                        for(j=k;j>=-k;j--)
                            if(j!=0)
                                if(fMiller[0][2]*i==-fMiller[0][1]*j)
                                {fMiller[1][2] = i;fMiller[1][1] = j;fMiller[1][0] = 0;}
                k++;
            }
            while((fMiller[1][0] == 0) && (fMiller[1][1] == 0) && (fMiller[1][2] == 0));
        }
        
        if((fMiller[0][0]!=0) && (fMiller[0][1]==0) && (fMiller[0][2]!=0))
        {
            k = 1;
            do
            {
                for(i=k;i>=-k;i--)
                    if(i!=0)
                        for(j=k;j>=-k;j--)
                            if(j!=0)
                                if(fMiller[0][2]*i==-fMiller[0][0]*j)
                                {fMiller[2][0] = j;fMiller[2][1] = 0;fMiller[2][2] = i;}
                k++;
            }
            while((fMiller[2][0] == 0) && (fMiller[2][1] == 0) && (fMiller[2][2] == 0));
        }
        
        if((fMiller[0][0]!=0) && (fMiller[0][1]!=0) && (fMiller[0][2]==0))
        {
            k = 1;
            do
            {
                for(i=k;i>=-k;i--)
                    if(i!=0)
                        for(j=k;j>=-k;j--)
                            if(j!=0)
                                if(fMiller[0][1]*i==-fMiller[0][0]*j)
                                {fMiller[2][0] = j;fMiller[2][1] = i;fMiller[2][2] = 0;}
                k++;
            }
            while((fMiller[2][0] == 0) && (fMiller[2][1] == 0) && (fMiller[2][2] == 0));
        }
        
        if((fMiller[0][0]==0) && (fMiller[0][1]!=0) && (fMiller[0][2]!=0))
        {
            k = 1;
            do
            {
                for(i=k;i>=-k;i--)
                    if(i!=0)
                        for(j=k;j>=-k;j--)
                            if(j!=0)
                                if(fMiller[0][2]*i==-fMiller[0][1]*j)
                                {fMiller[2][0] = 0;fMiller[2][1] = j;fMiller[2][2] = i;}
                k++;
            }
            while((fMiller[2][0] == 0) && (fMiller[2][1] == 0) && (fMiller[2][2] == 0));
        }
        
        if((fMiller[0][0]!=0) && (fMiller[0][1]!=0) && (fMiller[0][2]!=0))
        {
            k = 1;
            do
            {
                for(i=k;i>=-k;i--)
                    if(i!=0)
                        for(j=k;j>=-k;j--)
                            if(j!=0)
                                for(l=k;l>=-k;l--)
                                    if(l!=0)
                                        if(((fMiller[0][0]*i + fMiller[0][1]*j + fMiller[0][2]*l)==0) && ((fMiller[1][0]*i + fMiller[1][1]*j + fMiller[1][2]*l)==0))
                                        {fMiller[2][0] = i;fMiller[2][1] = j;fMiller[2][2] = l;}
                k++;
            }
            while((fMiller[2][0] == 0) && (fMiller[2][1] == 0) && (fMiller[2][2] == 0));
        }
        
        if((fMiller[0][0]==0) && (fMiller[0][1]!=0) && (fMiller[0][2]!=0)) {fMiller[1][0] = 1; fMiller[1][1] = 0; fMiller[1][2] = 0;}
        else if((fMiller[0][0]!=0) && (fMiller[0][1]==0) && (fMiller[0][2]!=0)) {fMiller[1][0] = 0; fMiller[1][1] = 1; fMiller[1][2] = 0;}
        else if((fMiller[0][0]!=0) && (fMiller[0][1]!=0) && (fMiller[0][2]==0)) {fMiller[1][0] = 0; fMiller[1][1] = 0; fMiller[1][2] = 1;}
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_miller_cubic::ReverseMillerOrderForCubicAxialCalculations(int MillerReversed[3]){
    if(fMiller[0][2]!=0)
    {
        MillerReversed[0]=fMiller[0][0];
        MillerReversed[1]=fMiller[0][1];
        MillerReversed[2]=fMiller[0][2];
    }
    else if(fMiller[0][1]!=0)
    {
        MillerReversed[0]=fMiller[0][2];
        MillerReversed[1]=fMiller[0][0];
        MillerReversed[2]=fMiller[0][1];
    }
    else if(fMiller[0][0]!=0) 
    {
        MillerReversed[0]=fMiller[0][1];
        MillerReversed[1]=fMiller[0][2];
        MillerReversed[2]=fMiller[0][0];
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_miller_cubic::ReverseMillerOrder(int MillerReversed[3])
{
    int MillerTemp[3];
    for(unsigned int i = 0;i<3;i++) MillerTemp[i]=MillerReversed[i];
    
    if(fMiller[0][2]!=0)
    {
        MillerReversed[0]=MillerTemp[0];
        MillerReversed[1]=MillerTemp[1];
        MillerReversed[2]=MillerTemp[2];
    }
    else if(fMiller[0][1]!=0)
    {
        MillerReversed[0]=MillerTemp[1];
        MillerReversed[1]=MillerTemp[2];
        MillerReversed[2]=MillerTemp[0];
    }
    else if(fMiller[0][0]!=0) 
    {
        MillerReversed[0]=MillerTemp[2];
        MillerReversed[1]=MillerTemp[0];
        MillerReversed[2]=MillerTemp[1];
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//
//This function check if MillerOrthogonal[0] & MillerOrthogonal[1] vIndexes can be used and, if they can  be used, the MillerOrthogonal[2] is the third vIndex of the orthogonal vector
//
bool ECHARM_miller_cubic::CheckOrthogonalityToAxis(int MillerOrthogonal[3]){
    double tempF[2];
    int MillerTemp[3] = {0,0,0};
    ReverseMillerOrderForCubicAxialCalculations(MillerTemp);
    
    tempF[0] = -(MillerOrthogonal[0] * MillerTemp[0] + MillerOrthogonal[1] * MillerTemp[1]) / MillerTemp[2];
    tempF[1] = (MillerOrthogonal[0] * MillerTemp[0] + MillerOrthogonal[1] * MillerTemp[1] + tempF[0] * MillerTemp[2]);
    MillerOrthogonal[2] = int(tempF[0]);
    
    if((fabs(tempF[1]) < 1.E-7) && (fabs(double(MillerOrthogonal[2])-tempF[0]) < 1.E-7))
        if((fSquare(MillerOrthogonal[0]) + fSquare(MillerOrthogonal[1]) + fSquare(MillerOrthogonal[2])) != 0) return true;
    
    return false;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//
//This function check if Miller axial vectors are orthogonal each other
//

bool ECHARM_miller_cubic::CheckOrthogonality(){
    int vIndexesSum = 0;
    for(unsigned int i=0;i<3;i++)
        for(unsigned int j=i+1;j<3;j++)
            for(unsigned int k=0;k<3;k++)
                    vIndexesSum += (fMiller[i][k]*fMiller[j][k]);
                
    if(vIndexesSum==0) return true;
    
    std::cout << "ECHARM_miller_cubic - Axial Indexes are not orthogonal" << std::endl;
    
    return false;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
