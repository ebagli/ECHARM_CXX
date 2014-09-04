//
//  ECHARM_radiation.cpp
//
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCvOmpanyName__. All rights reserved.
//

#include "ECHARM_radiation.hh"
#include "TH2D.h"
ECHARM_radiation::ECHARM_radiation(int vEnBin,double vEnMin,double vEnStep,int anglexbins = 30 ,int angleybins = 15):
ECHARM_process("radiation"){
    fAngColl = 0.002318303;
    fStepMaxLength = 10. * meter;
    
    fAngXbins = anglexbins;
    fAngYbins = angleybins;
    fEnBins = vEnBin;
    
    fEnMin = vEnMin;
    fEnStep = vEnStep;
    fEnMax = vEnMin + vEnStep*vEnBin;
    
    for(int i0=0;i0<fEnBins;i0++){
        fRadEmProb.push_back(0.);
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_radiation::~ECHARM_radiation(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_radiation::DoOnStrip(ECHARM_strip* strip,ECHARM_particle* part){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_radiation::PrintTrajToFile(std::string filename){
    std::ofstream fileout;
    fileout.open(filename.c_str());
    for(int i0=0;i0<fStepNum;i0++){
        fileout << fStep[i0]/AA << " " << fVelX[i0] << " " << fVelY[i0] << " " << fAccX[i0]*AA << " " << fAccY[i0]*AA << " " << fVelX[i0]-fVelPreSctX[i0] << " " << fVelY[i0]-fVelPreSctY[i0] << std::endl;
    }
    fileout.close();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_radiation::DoOnParticle(ECHARM_strip* strip,ECHARM_particle* part){
    
    if(fStepNum<MAX_STEP_NUM){
        fStep[fStepNum]=(part->GetStepLength());
        
        fVelX[fStepNum]=(part->GetAngX());
        if(strip->IsBentX()){
            fVelX[fStepNum]+= (part->GetPos()->GetZ() / strip->GetBR()->GetX());
        }
        fVelY[fStepNum]=(part->GetAngY());
        
        if(strip->IsBentY()){
            fVelY[fStepNum]+= (part->GetPos()->GetZ() / strip->GetBR()->GetY());
        }
        
        fAccX[fStepNum]=(part->GetZ() * 0.5 * (strip->GetEFX()->Get(part->GetPosPre()) + strip->GetEFX()->Get(part->GetPos()))/part->GetMom()->GetZ());
        fAccY[fStepNum]=(part->GetZ() * 0.5 * (strip->GetEFY()->Get(part->GetPosPre()) + strip->GetEFY()->Get(part->GetPos()))/part->GetMom()->GetZ());
        
        fVelPreSctX[fStepNum]=(0.);
        fVelPreSctY[fStepNum]=(0.);

        fVelPreSctX[fStepNum]=(part->GetAngXPre());
        if(strip->IsBentX()){
            fVelPreSctX[fStepNum]+= (part->GetPos()->GetZ() / strip->GetBR()->GetX());
        }
        fVelPreSctY[fStepNum]=(part->GetAngYPre());
        
        if(strip->IsBentY()){
            fVelPreSctY[fStepNum]+= (part->GetPos()->GetZ() / strip->GetBR()->GetY());
        }

        
        fStepNum++;
    }
    else{
        DoAfterInteraction(strip,part);
        Init(strip,part);
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_radiation::DoAfterInteraction(ECHARM_strip* strip,ECHARM_particle* part){
    
    PrintTrajToFile("traj.txt");
    for(int i0=0;i0<fEnBins;i0++){
        double vEn = fEnMin + fEnStep*i0;
        fRadEmProb.at(i0) = ComputeRadEmProb(strip,part,vEn);
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_radiation::Init(ECHARM_strip* strip,ECHARM_particle* part){
    
    for(int i0=0;i0<fEnBins;i0++){
        fRadEmProb.at(i0) = 0.;
    }
    fStepNum = 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_radiation::Store(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_radiation::ComputeRadEmProb(ECHARM_strip* strip,ECHARM_particle* part,double vOm){
    
    double vEn = part->GetEnergy();
    double vGamma = part->GetGamma();
    
    double vEnPrime = vEn - vOm;
    double vOmPrime = vEn * vOm / vEnPrime;
    
    double vOmPL = 0.;
    
    if(part->GetMom()->GetZ() == 855. * MeV){
        //vOmPL = 0.052 * MeV / vGamma ;
    }
    
    double vPhCoeff = 1. / (vGamma * vGamma);
    vPhCoeff += (fSquare(vOmPL) / fSquare(vOm));
    
    double I2Coeff = vOm * (fSquare(vEn)+fSquare(vEnPrime))/(fSquare(vEnPrime));
    double J2Coeff = vPhCoeff * (fSquare(vOm))/(fSquare(vEnPrime));
    
    double vResult = 0.;
    
    for (int i0X=0;i0X<fAngXbins;i0X++)
    {
        for (int i0Y=0;i0Y<fAngYbins;i0Y++)
        {
            double r=drand48();
            double phi=drand48()*c2Pi;
            double THx=fAngColl*fSquareRoot(r)*sin(phi);
            double THy=fAngColl*fSquareRoot(r)*cos(phi);
            
            double fa=0.;
            
            double ss=0.;
            double sc=0.;
            double ssx=0.;
            double ssy=0.;
            double scx=0.;
            double scy=0.;
            
            for(int i0Step=0;i0Step<fStepNum;i0Step++){
                double dz = fStep[i0Step]/cPlanckConstant;
                double axt = fAccX[i0Step]*cPlanckConstant;
                double ayt = fAccY[i0Step]*cPlanckConstant;
                
                double vxin = fVelX[i0Step] - THx;
                double vyin = fVelY[i0Step] - THy;
                double vxno = fVelPreSctX[i0Step] - THx;
                double vyno = fVelPreSctY[i0Step] - THy;
                
                double vPhBef = vOmPrime * 0.5 *((vPhCoeff)+(vxno*vxno)+(vyno*vyno));
                double vPhAft = vOmPrime * 0.5 *((vPhCoeff)+(vxin*vxin)+(vyin*vyin));
                
                fa=fa+vPhBef*dz;
                double fa1=fa-vPhBef*dz/2;
                
                fa1 += vPhBef*dz/2;
                double fa2 = vOmPrime*(axt*vxno+ayt*vyno);
                double dzmod = 2.*sin(vPhBef*dz/2)/vPhBef;
                
                //dzmod = 0.;
                
                
                double skJ=1/vPhAft-1/vPhBef;
                skJ -= (fa2/(vPhBef*vPhBef))*dzmod;
                
                double skIx=vxin/vPhAft-vxno/vPhBef;
                skIx += dzmod*(axt/vPhBef-vxno*fa2/(vPhBef*vPhBef));
                
                double skIy=vyin/vPhAft-vyno/vPhBef;
                skIy += dzmod*(ayt/vPhBef-vyno*fa2/(vPhBef*vPhBef));
                
                //integral
                ss += sin(fa1)*skJ;//sum sin integral J della BK
                sc += cos(fa1)*skJ;//sum cos integral J della BK
                ssx += sin(fa1)*skIx;// sum sin integral Ix della BK
                ssy += sin(fa1)*skIy;// sum sin integral Iy della BK
                scx += cos(fa1)*skIx;// sum cos integral Ix della BK
                scy += cos(fa1)*skIy;// sum cos integral Iy della BK
                
            }
            
            double I2 = ssx*ssx+scx*scx+ssy*ssy+scy*scy; //MeV^-2
            double J2 = ss*ss+sc*sc; //MeV^-2
            
            vResult += ((I2*I2Coeff)+(J2*J2Coeff));
        }
        
    }
    
    vResult *= (fAngColl*fAngColl*cPi); // angle
    vResult /= fAngXbins;
    vResult /= fAngYbins;
    vResult /= (8.*(cPi*cPi)); // angle
    vResult *= cFineStructureConstant;
    
    return vResult;
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......