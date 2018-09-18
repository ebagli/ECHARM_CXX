//
//  Created by Enrico Bagli on 06/20/13.
//  Modified by Vadim Karpusenko for optimization on 06/25/13.
//  Modified by Enrico Bagli for vectorization on 10/03/13.
//  Copyright 2013 Enrico Bagli. All rights reserved.
//

#include <algorithm>
#include <iostream>
#include <ctime>
#include <chrono>
#include <omp.h>

#include <stdio.h>
#include "mkl.h"
#include "mkl_vsl.h"

#include "ECHARM_save_structure.h"
#include "ECHARM_constants.h"
#include "ECHARM_threevector.h"
#include "ECHARM_threevector.cpp"
#include "ECHARM_distribution.h"
#include "ECHARM_distribution.cpp"

#include "ECHARM_atom.h"
#include "ECHARM_atom.cpp"
#include "ECHARM_cell.h"
#include "ECHARM_cell.cpp"
#include "ECHARM_lattice.h"
#include "ECHARM_lattice.cpp"
#include "ECHARM_miller.h"
#include "ECHARM_miller.cpp"

#include "ECHARM_crystal.h"
#include "ECHARM_crystal.cpp"
#include "ECHARM_crystal_reciprocal.h"
#include "ECHARM_crystal_reciprocal.cpp"

#include "databases/ECHARM_crystal_Si.h"
#include "databases/ECHARM_crystal_Si.cpp"

#include "ECHARM_multiple_scattering_functions.h"
#include "ECHARM_multiple_scattering_functions.cpp"

#include "ECHARM_particle.h"
#include "ECHARM_particle.cpp"


#define bMultipleScattering // if commented, Multiple Scattring does not influence particle motion
//#define bTrajectory // if commented, particle trajectory is NOT rd
//#define constSaveTrajectoryMinDistance 1.E-6
#define constSecondaryCurvature 12.92 //if commented crystal is considered straight
#define constIntegrationStepNumber 8192
#define constVectorLength 2

//#define constVectorLengthHalf 16
//#define writeOnFile

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void GetValueInterpolation(double vX[constVectorLength],double vVector[constIntegrationStepNumber],double vPeriod,double out[constVectorLength])
{
    double x[constVectorLength]; 
    double vStepX[constVectorLength];
    int vInt[constVectorLength];
    
    double a0[constVectorLength];
    double a1[constVectorLength];
    double a2[constVectorLength];
    double a3[constVectorLength];
    double x2[constVectorLength];
    
    for(unsigned int jvec=0;jvec<constVectorLength;jvec++){
        x[jvec] = vX[jvec];
        if (x[jvec] < 0.0) x[jvec] += ((fabs(int(vX[jvec] / vPeriod)) + 1.0) * vPeriod);
        else if(x[jvec] > vPeriod) x[jvec] -= (fabs(int(vX[jvec] / vPeriod)) * vPeriod );
    }
    for(unsigned int jvec=0;jvec<constVectorLength;jvec++){
        vStepX[jvec] = vPeriod / ( constIntegrationStepNumber - 1 );
    }
    for(unsigned int jvec=0;jvec<constVectorLength;jvec++){
        vInt[jvec] = int(x[jvec] / vStepX[jvec]) + 1; // +1 because of we moved the vector +1 to avoid exceptions
    }
    for(unsigned int jvec=0;jvec<constVectorLength;jvec++){
        x[jvec] -= vInt[jvec] * vStepX[jvec];        
    }
    for(unsigned int jvec=0;jvec<constVectorLength;jvec++){
        x[jvec] /= vStepX[jvec];
    }
    for(unsigned int jvec=0;jvec<constVectorLength;jvec++){
        x2[jvec] = x[jvec] * x[jvec];
    }
    for(unsigned int jvec=0;jvec<constVectorLength;jvec++){
        a0[jvec] = -0.5 * vVector[vInt[jvec] - 1] + 1.5 * vVector[vInt[jvec]] - 1.5 * vVector[vInt[jvec] + 1] + 0.5 * vVector[vInt[jvec] + 2];
        a1[jvec] = vVector[vInt[jvec] - 1] - 2.5 * vVector[vInt[jvec]] + 2.0 * vVector[vInt[jvec] + 1] - 0.5 * vVector[vInt[jvec] + 2];
        a2[jvec] = -0.5 * vVector[vInt[jvec] - 1] + 0.5 * vVector[vInt[jvec] + 1];
        a3[jvec] = vVector[vInt[jvec]];
    }
    for(unsigned int jvec=0;jvec<constVectorLength;jvec++){
        out[jvec] = (a0[jvec] * x[jvec] * x2[jvec] + a1[jvec] * x2[jvec] + a2[jvec] * x[jvec] + a3[jvec]);
        
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc, char *argv[constVectorLength])
{
    
    //*************************************************
    //******************* VARIABLES *******************
    //*************************************************
    
    /////////********* Calculation Variables
    
    unsigned int vNumberOfParticles = 100;
    
    if(argv[1]){
        if(atoi(argv[1]) != 0){
            vNumberOfParticles = atoi(argv[1]);
        }
    }
    if(vNumberOfParticles <1){
        std::cout << "Number of particles is zero" << std::endl;
        return 0;
    }
    
    vNumberOfParticles = int(float(vNumberOfParticles)/float(constVectorLength));
    
    int vOMP_THREAD_NUMS = 4;
    if(argv[2]){
        if(atoi(argv[2]) > 0){
            vOMP_THREAD_NUMS = atoi(argv[2]);
        }
    }
    const int OMP_THREAD_NUMS = vOMP_THREAD_NUMS;

    
    
    std::string vFileName = "output_sim.txt";  // name of the output file
    std::string vFileNameTime = "output_time.txt";  //
    
#ifdef bTrajectory
    std::string vFileNameTrajectory = "output_traj.txt";  //
#endif
    
    const double constStepLengthMin = 2.E-10; // m
    const double constTransverseVariationMax = 2.E-12; // m
    
    /////////********* Beam Variables
    const double constMomentumZ = 150. * GeV;
    
    const double constParticleMass = cPaiMass;
    const double constParticleCharge = -1.;
    const double constParticleGamma = constMomentumZ/constParticleMass;
    
    const double constMeanIncomingAngleX = +60. * microrad;
    const double constVarianceIncomingAngleX = +120. * microrad;
    
    /////////********* Crystal Variables
    const float constCrystalLenght = 0.84 * millimeter;
    
    int vMillerPl[3] = {1,1,1};
    int vMillerAx[3] = {1,1,1};
    
    const int constIntegrationEnd = int(constCrystalLenght / constStepLengthMin);
    const double constStepLengthMinHalf = constStepLengthMin * 0.5;
    
    //*************************************************
    //*************************************************
    //*************************************************
    
    
    
    /////////////////////////////////////////////////////
    //////////////////****start****//////////////////////
    /////////////////////////////////////////////////////
    
    
    /////////********* Save Structures Inizialization
    
    /////////********* Crystal Inizialization
    ECHARM_crystal_Si *rCrystalBase = new ECHARM_crystal_Si(vMillerPl,vMillerAx);
    ECHARM_crystal_reciprocal *rCrystal = new ECHARM_crystal_reciprocal(rCrystalBase);
    rCrystal->SetIntegrationStepNumberPlanar(constIntegrationStepNumber);
    rCrystal->FindPlanarFourierCoefficient();
    
    double constElectricField[constIntegrationStepNumber+4];
    double constNucleiDensity[constIntegrationStepNumber+4];
    double constElectronDensity[constIntegrationStepNumber+4];
    double constPotential[constIntegrationStepNumber+4];

    std::vector<double> vVector = rCrystal->FindPlanarElectricCharacteristic(3);
    for(int i=1;i < constIntegrationStepNumber+1;i++) {
        constElectricField[i]=vVector.at(i-1);
    }
    constElectricField[0]=vVector.at(constIntegrationStepNumber-1);
    constElectricField[constIntegrationStepNumber+1]=vVector.at(0);
    constElectricField[constIntegrationStepNumber+2]=vVector.at(1);
    constElectricField[constIntegrationStepNumber+3]=vVector.at(2);
    
    vVector = rCrystal->FindPlanarElectricCharacteristic(1);
    for(int i=1;i < constIntegrationStepNumber+1;i++) {
        constNucleiDensity[i]=vVector.at(i-1);
    }
    constNucleiDensity[0]=vVector.at(constIntegrationStepNumber-1);
    constNucleiDensity[constIntegrationStepNumber+1]=vVector.at(0);
    constNucleiDensity[constIntegrationStepNumber+2]=vVector.at(1);
    constNucleiDensity[constIntegrationStepNumber+3]=vVector.at(2);
    
    vVector = rCrystal->FindPlanarElectricCharacteristic(2);
    for(int i=1;i < constIntegrationStepNumber+1;i++) {
        constElectronDensity[i]=vVector.at(i-1);
    }
    constElectronDensity[0]=vVector.at(constIntegrationStepNumber-1);
    constElectronDensity[constIntegrationStepNumber+1]=vVector.at(0);
    constElectronDensity[constIntegrationStepNumber+2]=vVector.at(1);
    constElectronDensity[constIntegrationStepNumber+3]=vVector.at(2);
    
    vVector = rCrystal->FindPlanarElectricCharacteristic(0);
    for(int i=1;i < constIntegrationStepNumber+1;i++) {
        constPotential[i]=vVector.at(i-1);
    }
    constPotential[0]=vVector.at(constIntegrationStepNumber-1);
    constPotential[constIntegrationStepNumber+1]=vVector.at(0);
    constPotential[constIntegrationStepNumber+2]=vVector.at(1);
    constPotential[constIntegrationStepNumber+3]=vVector.at(2);
  
    const double constInterplanarPeriod = rCrystal->GetDirectPeriodPlanar();
    const double constStepLengthMax = sqrt(constTransverseVariationMax * constMomentumZ / rCrystal->GetElectricFieldMaximum());
    
    
    /////////********* Output Inizialization
#ifdef writeOnFile
    std::ofstream fOutput;
    fOutput.open(vFileName.c_str());
    
#ifdef bTrajectory
    std::ofstream fOutputTrajectory;
    fOutputTrajectory.open(vFileNameTrajectory.c_str());
#endif
#endif
    
#ifdef bMultipleScattering
    ECHARM_threevector* rPositionVector = new ECHARM_threevector(0.0,0.0,0.);;
    ECHARM_threevector* rMomentumVector = new ECHARM_threevector(0.0,0.0,constMomentumZ);
    ECHARM_particle* rParticle = new ECHARM_particle(constParticleCharge,constParticleMass,rMomentumVector,rPositionVector);
    
    ECHARM_multiple_scattering_functions* rMultipleScattering = new ECHARM_multiple_scattering_functions(rCrystal,rParticle);
    rMultipleScattering->SetCrossedMaterialLength(1.* meter);
    rMultipleScattering->SetRadiationLength("tsai");
    const double constRadiationLength = rMultipleScattering->GetRadiationLength();
    const double constElectronScattering = rMultipleScattering->EvaluateBetheBlochMeanEnergyLoss() * cElectronMass;
    const double constNucleiScattering = double(21.) * MeV * fabs(constParticleCharge);
#endif
    
    ///////// Vector for calculation
    double vectorZero[constVectorLength];
    double vectorMomentumMean[constVectorLength];
    double vectorMomentumSigma[constVectorLength];
    double vectorPositionMean[constVectorLength];
    double vectorPositionSigma[constVectorLength];
    double vectorMomentumZ[constVectorLength];
    double vectorParticleCharge[constVectorLength];
#ifdef constSecondaryCurvature
    double vectorSecondaryCurvature[constVectorLength];
#endif
#ifdef bMultipleScattering
    double vectorLengthOverRadiationLength[constVectorLength];
    double vectorVarianceNuclearScattering[constVectorLength];
    double vectorVarianceElectronScattering[constVectorLength];
#endif
    
    for(unsigned int jvec=0;jvec<constVectorLength;jvec++){
        vectorZero[jvec] = 0.;
        vectorMomentumZ[jvec] = constMomentumZ;
        vectorParticleCharge[jvec] = constParticleCharge;
#ifdef constSecondaryCurvature
        vectorSecondaryCurvature[jvec] = constSecondaryCurvature;
#endif
    }

    const double constMomentumMean = constMeanIncomingAngleX * constMomentumZ;
    const double constMomentumSigma = constVarianceIncomingAngleX * constMomentumZ;
    const double constPositionMean = constInterplanarPeriod * 0.5;
    const double constPositionSigma = constInterplanarPeriod * 0.5;

    
    std::time_t vRawTimeInitial;
    std::time_t vRawTimeFinal;
    
    std::time(&vRawTimeInitial);
    std::cout << std::endl << "Start time " << ctime(&vRawTimeInitial) << std::endl;
    std::clock_t vNumberOfClocks = clock();

    std::chrono::time_point<std::chrono::system_clock> vStartChrono, vEndChrono;
    vStartChrono = std::chrono::system_clock::now();

    omp_set_num_threads(OMP_THREAD_NUMS);
    
#pragma omp parallel
    {
        VSLStreamStatePtr stream;
        vslNewStream(&stream,VSL_BRNG_SFMT19937,omp_get_thread_num());
        
        /////////********* Loop on particles
        double rStepLength[constVectorLength];
        double rStepLengthHalf[constVectorLength];
        
        double rPositionXin[constVectorLength];
        double rMomentumXin[constVectorLength];
        
        double rPositionX[constVectorLength];
        double rPositionY[constVectorLength];
        double rPositionZ[constVectorLength];
        
        double rMomentumX[constVectorLength];
        double rMomentumY[constVectorLength];
        
        double rPositionXHalf[constVectorLength];
        double rMomentumXHalf[constVectorLength];
        
        double rTempVector[constVectorLength];
        
        double rTransversePotential[constVectorLength];
        
        double bContinueIntegration[constVectorLength];
        bool bContinueIntegrationBool[constVectorLength];
        bool bContinueIntegrationTot;
        
#ifdef writeOnFile
#ifdef bTrajectory
        std::vector<double> rTrajectoryPosX[constVectorLength];
        std::vector<double> rTrajectoryPosY[constVectorLength];
        std::vector<double> rTrajectoryPosZ[constVectorLength];
        std::vector<double> rTrajectoryMomX[constVectorLength];
        std::vector<double> rTrajectoryMomY[constVectorLength];
        std::vector<double> rTrajectoryMomZ[constVectorLength];
        std::vector<double> rTrajectoryPot[constVectorLength];
        int rTrajectoryPoint[constVectorLength];
#endif
        
        std::vector<int> rSaveIndex[constVectorLength];
        std::vector<double> rSavePosXin[constVectorLength];
        std::vector<double> rSaveAngXin[constVectorLength];
        std::vector<double> rSaveAngXout[constVectorLength];
        std::vector<double> rSaveAngYin[constVectorLength];
        std::vector<double> rSaveAngYout[constVectorLength];
#endif
        
#ifdef bMultipleScattering
        double msEnergyVariation[constVectorLength];
        double msEnergyVariationNuclei[constVectorLength];
        double msEnergyVariationElectron[constVectorLength];
        double msRandomAngle[constVectorLength];
#endif
        
        // Loop on particles/number of threads   /////////////////
        // ////-= MAIN LOOP STARTS HERE =- ///////////////////////
#pragma omp for schedule(dynamic)
        for(int i=0;i<vNumberOfParticles;i++){
            // Generate random position and momentum for the vector of particles
            bContinueIntegrationTot = false;
            
            vdRngUniform(VSL_RNG_METHOD_UNIFORM_STD,stream,constVectorLength,rPositionX,constPositionMean-constPositionSigma,constPositionMean+constPositionSigma);
            vdRngUniform(VSL_RNG_METHOD_UNIFORM_STD,stream,constVectorLength,rMomentumX,constMomentumMean-constMomentumSigma,constMomentumMean+constMomentumSigma);
            
            for(unsigned int jvec=0;jvec<constVectorLength;jvec++){
                rPositionX[jvec] = (double(i) * constVectorLength + double(jvec)) / (double(vNumberOfParticles) * double(constVectorLength)) * constInterplanarPeriod;
            }
            
            for(unsigned int jvec=0;jvec<constVectorLength;jvec++){
                rPositionZ[jvec] = 0.;
                rMomentumY[jvec] = 0.;
                
                rMomentumXin[jvec] = rMomentumX[jvec];
                rPositionXin[jvec] = rPositionX[jvec];
                
                bContinueIntegration[jvec] = 1.;
                bContinueIntegrationBool[jvec] = true;
                
#ifdef writeOnFile
#ifdef bTrajectory
                rTrajectoryPosX[jvec].clear();
                rTrajectoryPosY[jvec].clear();
                rTrajectoryPosZ[jvec].clear();
                rTrajectoryMomX[jvec].clear();
                rTrajectoryMomY[jvec].clear();
                rTrajectoryMomZ[jvec].clear();
                rTrajectoryPot[jvec].clear();
                rTrajectoryPoint[jvec]=0;
#endif
#endif
            }
            
            
            // Integrate particle motion until the end of the crystal
            do{    
                for(unsigned int jvec=0;jvec<constVectorLength;jvec++){
                    if( rMomentumX[jvec] != 0.0){
                        rStepLength[jvec] = fabs(constTransverseVariationMax / rMomentumX[jvec] * constMomentumZ);
                    }
                    else{
                        rStepLength[jvec] = constStepLengthMin;
                    }
                    
                    if( rStepLength[jvec] < constStepLengthMin ) {
                        rStepLength[jvec] = constStepLengthMin;
                    }
                    else if( rStepLength[jvec] > constStepLengthMax ) {
                        rStepLength[jvec] = constStepLengthMax;
                    }
                    if( ((rPositionZ[jvec] + rStepLength[jvec]) > constCrystalLenght) && (bContinueIntegrationBool[jvec] == true)){
                        rStepLength[jvec] = constCrystalLenght - rPositionZ[jvec];
                        bContinueIntegrationBool[jvec] = false;
                    }
                    rStepLengthHalf[jvec] = rStepLength[jvec] * 0.5;
                }
                
#ifdef bMultipleScattering
                for(unsigned int jvec=0;jvec<constVectorLength;jvec++){
                    vectorLengthOverRadiationLength[jvec] = rStepLength[jvec] / constRadiationLength;
                }
                for(unsigned int jvec=0;jvec<constVectorLength;jvec++){
                    vectorVarianceNuclearScattering[jvec] = (1.0 + 0.038 * log(vectorLengthOverRadiationLength[jvec]));
                }
                for(unsigned int jvec=0;jvec<constVectorLength;jvec++){
                    vectorVarianceNuclearScattering[jvec] = constNucleiScattering * sqrt(vectorLengthOverRadiationLength[jvec]);
                }
                for(unsigned int jvec=0;jvec<constVectorLength;jvec++){
                    vectorVarianceElectronScattering[jvec] = sqrt(constElectronScattering * rStepLength[jvec]);
                } // at this point because length can be zero -> log(zero) -> error
#endif
                
                for(unsigned int jvec=0;jvec<constVectorLength;jvec++){
                    rStepLength[jvec] *= bContinueIntegration[jvec];
                    rStepLengthHalf[jvec] *= bContinueIntegration[jvec];
                }
                
                for(unsigned int jvec=0;jvec<constVectorLength;jvec++){
                    rPositionXHalf[jvec] = rPositionX[jvec] + rMomentumX[jvec] / vectorMomentumZ[jvec] * rStepLengthHalf[jvec];
                }
                GetValueInterpolation(rPositionX,constElectricField,constInterplanarPeriod,rTempVector);
                for(unsigned int jvec=0;jvec<constVectorLength;jvec++){
                    rMomentumXHalf[jvec] = rMomentumX[jvec];
                    rTempVector[jvec] *= rStepLengthHalf[jvec];
                    rTempVector[jvec] *= vectorParticleCharge[jvec];
                    rMomentumXHalf[jvec] +=  rTempVector[jvec];
                }
#ifdef constSecondaryCurvature
                for(unsigned int jvec=0;jvec<constVectorLength;jvec++){
                    rMomentumXHalf[jvec] -= ( vectorMomentumZ[jvec] * rStepLengthHalf[jvec] / vectorSecondaryCurvature[jvec]);
                }
#endif
                for(unsigned int jvec=0;jvec<constVectorLength;jvec++){
                    rPositionX[jvec] += rMomentumXHalf[jvec] / vectorMomentumZ[jvec] * rStepLength[jvec];
                }
                
                GetValueInterpolation(rPositionXHalf,constElectricField,constInterplanarPeriod,rTempVector);
                for(unsigned int jvec=0;jvec<constVectorLength;jvec++){
                    rTempVector[jvec] *= rStepLength[jvec];
                    rTempVector[jvec] *= vectorParticleCharge[jvec];
                    rMomentumX[jvec] +=  rTempVector[jvec] * bContinueIntegration[jvec];
                }
#ifdef constSecondaryCurvature
                for(unsigned int jvec=0;jvec<constVectorLength;jvec++){
                    rMomentumX[jvec] -= (vectorMomentumZ[jvec] * rStepLength[jvec] / vectorSecondaryCurvature[jvec] );
                }
#endif
                for(unsigned int jvec=0;jvec<constVectorLength;jvec++){
                    rPositionY[jvec] += rMomentumY[jvec] / vectorMomentumZ[jvec] * rStepLength[jvec];
                }                    
                for(unsigned int jvec=0;jvec<constVectorLength;jvec++){
                    rPositionZ[jvec] += rStepLength[jvec];
                }                    
#ifdef bMultipleScattering
                // Update the step length for multiple scattering calculation                    
                GetValueInterpolation(rPositionX,constNucleiDensity,constInterplanarPeriod,rTempVector);
                for(unsigned int jvec=0;jvec<constVectorLength;jvec++){
                    double rTemp = rTempVector[jvec];
                    if(rTemp<0.01){rTemp=0.01;}
                    rTemp *= vectorVarianceNuclearScattering[jvec];
                    if(vdRngGaussian(VSL_RNG_METHOD_GAUSSIAN_BOXMULLER,stream,1,&msEnergyVariationNuclei[jvec],0.,rTemp) < VSL_ERROR_OK){
                        std::cout << msEnergyVariationNuclei[jvec] << " " << rTemp << std::endl;
                        while(!getchar());
                    }
               }

                GetValueInterpolation(rPositionX,constElectronDensity,constInterplanarPeriod,rTempVector);
                for(unsigned int jvec=0;jvec<constVectorLength;jvec++){
                    double rTemp = rTempVector[jvec];
                    if(rTemp<0.01){rTemp=0.01;}
                    rTemp *= vectorVarianceElectronScattering[jvec];
                    if(vdRngGaussian(VSL_RNG_METHOD_GAUSSIAN_BOXMULLER,stream,1,&msEnergyVariationElectron[jvec],0.,rTemp) < VSL_ERROR_OK){
                        std::cout << msEnergyVariationElectron[jvec] << " " << rTemp << std::endl;
                        while(!getchar());
                    }
                }

                for(unsigned int jvec=0;jvec<constVectorLength;jvec++){
                    msEnergyVariation[jvec] = msEnergyVariationElectron[jvec] + msEnergyVariationNuclei[jvec];
                }
                
                vdRngUniform(VSL_RNG_METHOD_UNIFORM_STD,stream,constVectorLength,msRandomAngle,0.,1.);

                for(unsigned int jvec=0;jvec<constVectorLength;jvec++){
                    rMomentumX[jvec] += msEnergyVariation[jvec] * cos(msRandomAngle[jvec]) * bContinueIntegration[jvec];
                    rMomentumY[jvec] += msEnergyVariation[jvec] * cos(msRandomAngle[jvec]) * bContinueIntegration[jvec];
                }
#endif
                
                GetValueInterpolation(rPositionX,constPotential,constInterplanarPeriod,rTempVector);
                
#ifdef writeOnFile
#ifdef bTrajectory
                
                for(unsigned int jvec=0;jvec<constVectorLength;jvec++){

                if(rPositionZ[jvec] > rTrajectoryPoint[jvec]*constSaveTrajectoryMinDistance){

                    rTrajectoryPosX[jvec].push_back(rPositionX[jvec]);
                    rTrajectoryPosY[jvec].push_back(rPositionY[jvec]);
                    rTrajectoryPosZ[jvec].push_back(rPositionZ[jvec]);
                    rTrajectoryMomX[jvec].push_back(rMomentumX[jvec]);
                    rTrajectoryMomY[jvec].push_back(rMomentumY[jvec]);
                    rTrajectoryMomZ[jvec].push_back(constMomentumZ);
                    rTrajectoryPot[jvec].push_back(rTempVector[jvec]);//potential step by step
                    rTrajectoryPoint[jvec]++;
                }
                }
#endif
#endif
                for(unsigned int jvec=0;jvec<constVectorLength;jvec++){
                    if(bContinueIntegrationBool[jvec] ==  false){
                        bContinueIntegration[jvec] = 0.;
                        bContinueIntegrationTot = false;
                    }
                    if(bContinueIntegrationBool[jvec]==true){
                        bContinueIntegrationTot = true;
                    }
                }
            } while(bContinueIntegrationTot == true); // do loop
            
#ifdef writeOnFile
            for(unsigned int jvec=0;jvec<constVectorLength;jvec++){
#ifdef constSecondaryCurvature
                rSaveIndex[jvec].push_back(i*constVectorLength + jvec);
                rSavePosXin[jvec].push_back(rPositionXin[jvec]*1.E10);
                rSaveAngXin[jvec].push_back(rMomentumXin[jvec]/constMomentumZ*1.E6);
                rSaveAngXout[jvec].push_back((rMomentumX[jvec]/constMomentumZ + constCrystalLenght/constSecondaryCurvature)*1.E6);
                rSaveAngYout[jvec].push_back(rMomentumY[jvec]/constMomentumZ*1.E6);
#else
                rSaveIndex[jvec].push_back(i*constVectorLength + jvec);
                rSavePosXin[jvec].push_back(rPositionXin[jvec]*1.E10);
                rSaveAngXin[jvec].push_back(rMomentumXin[jvec]/constMomentumZ*1.E6);
                rSaveAngXout[jvec].push_back(rMomentumX[jvec]/constMomentumZ*1.E6);
                rSaveAngYout[jvec].push_back(rMomentumY[jvec]/constMomentumZ*1.E6);
#endif
            } //particle save
#endif
            
#ifdef writeOnFile
#ifdef bTrajectory
#pragma omp critical
            {
                for(unsigned int jvec=0;jvec<constVectorLength;jvec++){
                    
                    for(unsigned int l=0;l<rTrajectoryPosX[jvec].size();l++)
                    {
                        fOutputTrajectory << i*constVectorLength + jvec << " ";
                        fOutputTrajectory << rTrajectoryPosX[jvec].at(l)*1.E3 << " ";
                        fOutputTrajectory << rTrajectoryPosY[jvec].at(l)*1.E3 << " ";
                        fOutputTrajectory << rTrajectoryPosZ[jvec].at(l)*1.E3 << " ";
                        fOutputTrajectory << rTrajectoryMomX[jvec].at(l) << " ";
                        fOutputTrajectory << rTrajectoryMomY[jvec].at(l) << " ";
                        fOutputTrajectory << rTrajectoryMomZ[jvec].at(l) << " ";
                        fOutputTrajectory << rTrajectoryPot[jvec].at(l) << std::endl;
                    }
                }
            } // pragma omp critical
#endif           
#endif
            
        } //loop on particles
        
#ifdef writeOnFile
#pragma omp single
        {
            
            for(unsigned int jvec=0;jvec<constVectorLength;jvec++){
                for(int i=0;i<rSaveIndex[jvec].size();i++){
                    fOutput << rSaveIndex[jvec].at(i) << " ";
                    fOutput << rSaveAngXin[jvec].at(i) << " ";
                    fOutput << rSaveAngXout[jvec].at(i) << " ";
                    fOutput << rSaveAngYout[jvec].at(i) << " ";
                    fOutput << rSavePosXin[jvec].at(i) << " ";
                    fOutput << 0. << " ";
                    fOutput << std::endl;
                }
            } 
        } // save on file
#endif
        
#pragma omp single
        {
            vNumberOfClocks = (clock() - vNumberOfClocks)/1000.;
            time(&vRawTimeFinal);
            
            vEndChrono = std::chrono::system_clock::now();
            std::chrono::duration<double> vElapsedSeconds = vEndChrono-vStartChrono;
        
            std::ofstream fOutputTime;
            fOutputTime.open(vFileNameTime.c_str(),std::fstream::app);
            fOutputTime << omp_get_num_threads() << " " << constVectorLength << " " << vNumberOfParticles << " " << vNumberOfClocks << " " << vElapsedSeconds.count() << std::endl;
            fOutputTime.close();

            std::cout << "End time   " << ctime(&vRawTimeFinal) << std::endl;
            std::cout << "Elapsed time [clocks] = " << vNumberOfClocks << std::endl;
            std::cout << "Elapsed time [s] = " << vElapsedSeconds.count() << std::endl;
            std::cout << "Particles Processed " << vNumberOfParticles * constVectorLength << std::endl << std::endl;
        }
    } // pragma parallel
    
#ifdef writeOnFile
    fOutput.close();
#ifdef bTrajectory
    fOutputTrajectory.close();
#endif
#endif
    return 0;
}

/////////////////////////////////////////////////////
//////////////////*****end*****//////////////////////
/////////////////////////////////////////////////////
