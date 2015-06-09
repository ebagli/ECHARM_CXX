//
//  ECHARM_process_ms.cpp
//  
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifdef _ECHARM_process_ms_h

#include "ECHARM_process_ms.hh"
#include "ECHARM_distribution_gauss.hh"

ECHARM_process_ms::ECHARM_process_ms():
ECHARM_process("ms"){
    fDistr = new ECHARM_distribution_gauss(0.,0.);
    fConst = double(13.6) * MeV;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_process_ms::~ECHARM_process_ms(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_process_ms::DoOnStrip(ECHARM_strip*,ECHARM_particle*,ECHARM_info_save*){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_process_ms::DoOnParticle(ECHARM_strip* strip,ECHARM_particle* part,ECHARM_info_save*){
    double vMom = part->GetMomMod();

    double vTheta = ComputeThetaScattering(strip,part);
    
    double VMomVar = vTheta * vMom;
    double vPhi = c2Pi * drand48();
    
    part->GetMom()->AddX( VMomVar * cos(vPhi) );
    part->GetMom()->AddY( VMomVar * sin(vPhi) );
    part->GetMom()->SubtractZ( VMomVar);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_process_ms::ComputeThetaScattering(ECHARM_strip* strip,ECHARM_particle* part){
    double vLength = part->GetStepLength();
    ComputeStdDev(strip,part,vLength);
    fStdDev *= ComputeAvgDen(strip,part);
    return ComputeThetaMS(strip,part);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_process_ms::ComputeThetaMin(ECHARM_strip* strip,ECHARM_particle* part){
    //  Computer Physics Communications 141 (2001) 230–246
    //  Eq. (2)
    double vA = 0.;
    vA = pow(strip->GetCrystal()->GetZ(),0.3333333333) / part->GetMomMod();
    vA *= cFineStructureConstant / 1.4 * cElectronMass;
    return vA;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_process_ms::ComputeThetaMax(ECHARM_strip* strip,ECHARM_particle* part){
    //  Computer Physics Communications 141 (2001) 230–246
    //  Eq. (2)
    double vB = 0.;
    vB = pow(strip->GetCrystal()->GetA()/amu,-0.3333333333) / part->GetMomMod();
    vB *= 274. * cElectronMass;
    return vB;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_process_ms::ComputeThetaMS(ECHARM_strip* strip,ECHARM_particle* part){
    //  Computer Physics Communications 141 (2001) 230–246
    //  Eq. (16)
    fDistr->SetPar(1,fStdDev);
    return fDistr->GenerateNumber();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_process_ms::ComputeStdDev(ECHARM_strip* strip,ECHARM_particle* part,double length){
    fStdDev = fConst * fabs(part->GetZ()) / part->GetMomVel();
    fStdDev *= fSquareRoot(length / strip->GetCrystal()->GetRadLength());
    return fStdDev;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_process_ms::DoBeforeInteraction(ECHARM_strip* strip,ECHARM_particle* part,ECHARM_info_save*){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_process_ms::PrintRMStoTH1(ECHARM_strip* strip,ECHARM_particle *particle){
    
    
    char histoname[64];
    unsigned int nbins = 100;
    double xpoint;
    double length = 0.1 * millimeter;
    double energy = 400. * GeV;
    
    sprintf(histoname,"%s_l",fName.c_str());
    TH2F* h1l = new TH2F(histoname,"",nbins,0,length/millimeter,512,-128,128);
    h1l->GetXaxis()->SetTitle("Length [mm]");
    h1l->GetYaxis()->SetTitle("rms [#murad]");

    sprintf(histoname,"%s_e",fName.c_str());
    TH2F* h1e = new TH2F(histoname,"",nbins,0,energy/GeV,512,-128,128);
    h1e->GetXaxis()->SetTitle("Energy [GeV]");
    h1e->GetYaxis()->SetTitle("rms [#murad]");

    for(unsigned int i0=0;i0<nbins;i0++){
        particle->GetMom()->Set(0.,0.,energy);
        particle->GetPos()->Set(0.,0.,length * float(i0+1.5) / float(nbins));
        particle->GetPosPre()->Set(0.,0.,0.);
        xpoint = float(i0 + 1.5) / float(nbins) * length / millimeter;
        for(unsigned int i1=0;i1<10000;i1++){
            SetStepLengthSinceLastProcess(length * float(i0+1.5) / float(nbins));
            SetAtDSinceLastProcess(1.);
            SetElDSinceLastProcess(1.);
            h1l->Fill(xpoint,ComputeThetaScattering(strip,particle)/microrad);
        }
    }

    for(unsigned int i0=0;i0<nbins;i0++){
        particle->GetMom()->Set(0.,0.,energy * float(i0+1.5) / float(nbins));
        particle->GetPos()->Set(0.,0.,length);
        particle->GetPosPre()->Set(0.,0.,0.);
        xpoint = float(i0 + 1.5) / float(nbins) * energy / GeV;
        for(unsigned int i1=0;i1<10000;i1++){
            SetStepLengthSinceLastProcess(length);
            SetAtDSinceLastProcess(1.);
            SetElDSinceLastProcess(1.);
            h1e->Fill(xpoint,ComputeThetaScattering(strip,particle)/microrad);
        }
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif