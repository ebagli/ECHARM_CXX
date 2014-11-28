//
//  ECHARM_radiation_noparts.cpp
//
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCvOmpanyName__. All rights reserved.
//

#ifdef _ECHARM_radiation_noparts_h

#include "ECHARM_radiation_noparts.hh"

ECHARM_radiation_noparts::ECHARM_radiation_noparts(int anglexbins ,int angleybins):
ECHARM_process("radiation"){
    fAngColl = 0.002318303;
    fStepMaxLength = 10. * meter;
    
    fAngXbins = anglexbins;
    fAngYbins = angleybins;

    fInitialAngleX = 0.;
    fInitialAngleY = 0.;

    bSliceTraj = false;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_radiation_noparts::ECHARM_radiation_noparts():
    ECHARM_process("radiation"){
    fAngColl = 0.002318303;
    fStepMaxLength = 10. * meter;
    
    fAngXbins = 15;
    fAngYbins = 30;
    
    fInitialAngleX = 0.;
    fInitialAngleY = 0.;

    bSliceTraj = false;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_radiation_noparts::~ECHARM_radiation_noparts(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_radiation_noparts::PrintTrajToFile(std::string filename){
    std::ofstream fileout;
    fileout.open(filename.c_str());
    for(int i0=0;i0<fStepNum;i0++){
        fileout << fStep[i0]/AA << " " << fVelX[i0] << " " << fVelY[i0] << " " << fAccX[i0]*AA << " " << fAccY[i0]*AA << " " << fVelX[i0]-fVelPreSctX[i0] << " " << fVelY[i0]-fVelPreSctY[i0] << std::endl;
    }
    fileout.close();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_radiation_noparts::DoOnParticle(ECHARM_strip* strip,ECHARM_particle* part,ECHARM_info_save* info){
    
    if(fStepNum<MAX_STEP_NUM){
        fStep[fStepNum]=(part->GetStepLength());
        
        double posZ = part->GetPos()->GetZ() + strip->GetDim()->GetZ()*0.5;
        
        fVelX[fStepNum]=(part->GetAngX());
        if(strip->IsBentX()){
            fVelX[fStepNum] += (posZ / strip->GetBR()->GetX());
        }
        fVelY[fStepNum]=(part->GetAngY());
        
        if(strip->IsBentY()){
            fVelY[fStepNum] += (posZ / strip->GetBR()->GetY());
        }
        
        fAccX[fStepNum]=(part->GetZ() * 0.5 * (strip->GetEFX()->Get(part->GetPosPre()) + strip->GetEFX()->Get(part->GetPos()))/part->GetMom()->GetZ());
        if(strip->IsBentX()){
            //fAccX[fStepNum] += ( 0.5 * part->GetMomVel() * posZ / strip->GetBR()->GetX());
        }

        fAccY[fStepNum]=(part->GetZ() * 0.5 * (strip->GetEFY()->Get(part->GetPosPre()) + strip->GetEFY()->Get(part->GetPos()))/part->GetMom()->GetZ());
        if(strip->IsBentY()){
            //fAccY[fStepNum] += ( 0.5 * part->GetMomVel() * posZ / strip->GetBR()->GetY());
        }

        fVelPreSctX[fStepNum]=(part->GetAngXPre());
        if(strip->IsBentX()){
            fVelPreSctX[fStepNum] += (posZ / strip->GetBR()->GetX());
        }
        fVelPreSctY[fStepNum]=(part->GetAngYPre());
        
        if(strip->IsBentY()){
            fVelPreSctY[fStepNum] += (posZ / strip->GetBR()->GetY());
        }
        fStepNum++;
    }
    else{
        if(bSliceTraj){
            for(unsigned int i0=0;i0<(info->GetRadEmEnProb()).size();i0++){
                info->SetRadEmEnProb(i0,ComputeRadEmProb(strip,part,info->GetRadEmEn().at(i0)));
            }
        }
        else{
            DoAfterInteraction(strip,part,info);
        }
        
        fStepNum = 0;
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_radiation_noparts::DoBeforeInteraction(ECHARM_strip*,ECHARM_particle*,ECHARM_info_save*){
    fStepNum = 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_radiation_noparts::DoAfterInteraction(ECHARM_strip* strip,ECHARM_particle* part,ECHARM_info_save* info){
    for(unsigned int i0=0;i0<(info->GetRadEmEnProb()).size();i0++){
        info->AddRadEmEnProb(i0,ComputeRadEmProb(strip,part,info->GetRadEmEn().at(i0)));
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_radiation_noparts::Store(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_radiation_noparts::ComputeRadEmProb(ECHARM_strip* strip,ECHARM_particle* part,double vOm){
    
    double vEn = part->GetEnergy();
    double vGamma = part->GetGamma();
    
    double vEnPrime = vEn - vOm;
    double vOmPrime = vEn * vOm / vEnPrime;
    
    double vPhCoeff = 1. / (vGamma * vGamma);

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

            THx += fInitialAngleX;
            THy += fInitialAngleY;

            double vPhase=0.;
            
            double ss=0.;
            double sc=0.;
            double scx=0.;
            double scy=0.;
            double ssx=0.;
            double ssy=0.;
            
            for(int i0Step=0;i0Step<fStepNum;i0Step++){
                double dz = fStep[i0Step]/cPlanckConstant;
                
                double vxin = fVelX[i0Step] - THx;
                double vyin = fVelY[i0Step] - THy;
                double vxno = fVelPreSctX[i0Step] - THx;
                double vyno = fVelPreSctY[i0Step] - THy;
                
                double vPhBef = vOmPrime * 0.5 *((vPhCoeff)+(vxno*vxno)+(vyno*vyno));
                
                vPhase=vPhase+vPhBef*dz;
                double vPhase_t_average=vPhase-vPhBef*dz/2;
                
                
                //integral
                ss += sin(vPhase_t_average)*dz;//sum sin integral J della BK
                sc += cos(vPhase_t_average)*dz;//sum cos integral J della BK
                
                ssx += sin(vPhase_t_average)*(vxin+vxno)*0.5*dz;// sum sin integral Ix della BK
                scx += cos(vPhase_t_average)*(vxin+vxno)*0.5*dz;// sum sin integral Ix della BK

                ssy += sin(vPhase_t_average)*(vyin+vyno)*0.5*dz;// sum sin integral Iy della BK
                scy += cos(vPhase_t_average)*(vyin+vyno)*0.5*dz;// sum sin integral Iy della BK
            }
            
            double I2 = ssx*ssx+ssy*ssy+scx*scx+scy*scy; // eV^-2
            double J2 = ss*ss+sc*sc; // eV^-2
            
            vResult += ((I2*I2Coeff)+(J2*J2Coeff));
        }
        
    }
    
    vResult *= (fAngColl*fAngColl*cPi);
    vResult /= fAngXbins;
    vResult /= fAngYbins;
    vResult /= (8.*(cPi*cPi));
    vResult *= cFineStructureConstant;
    
    return vResult;
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif