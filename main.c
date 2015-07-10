//
//  Created by Enrico Bagli on 10/07/15.
//  Copyright 2015 Enrico Bagli. All rights reserved.
//

#define ROOT_
#define OPENMP_

#include <ctime>
#include "ECHARM_include_all.hh"

int main(int argc, char *argv[])
{
    time_t vInitialTime = time (NULL);
    int vNumberOfParticles = 100;

    // Create ECHARM_file_save object
    ECHARM_file_save* file_save = new ECHARM_ROOT_save("test.root");
    // Open ECHARM_file_save object
    file_save->Open();

#pragma omp parallel
    {
        // Create ECHARM_strip object
        ECHARM_strip* strip = new ECHARM_STLHC_2mm();
        
        // Create ECHARM_kernel object with the ECHARM_strip object as parameter
        ECHARM_kernel* kernel = new ECHARM_kernel(strip);

        // Let ECHARM_kernel save the particle incoming and outgoing angles
        kernel->SavePartIn(true);
        kernel->SavePartOut(true);

        // Modify ECHARM_kernel parameters (not mandatory)
        kernel->SetSaveTrajStatus(false);
        kernel->SetSaveTrajStep(0.5 * micrometer);
        kernel->SetTimeStepMin(2.E1 * AA);
        kernel->SetTransverseVariationMax(2.E-3 * AA);

        // Add other processes
        // 1. Create the object of the process
        // 2. Add the process to the kernel
        ECHARM_process_ms *ms = new ECHARM_process_ms();
        kernel->AddProcess(ms);

        // Create ECHARM_beam object and inizialize it
        ECHARM_beam* beam = new ECHARM_beam_H8_2012();
        beam->DistrPosFromStrip(strip);

        // Create ECHARM_manager object with the ECHARM_beam object as parameter
        ECHARM_manager* manager = new ECHARM_manager(beam);
        manager->SetNumberOfParticlesPrint(2);
        // Add the kernel object to the ECHARM_manager
        manager->AddKernel(kernel);
        // Run DYNECHARM and save inf the ECHARM_file_save object
        manager->RunDYNECHARM(file_save,vNumberOfParticles);
    }
    // Analyse ECHARM_file_save object
    file_save->Analysis();
    // Close ECHARM_file_save object
    file_save->Close();

    std::cout << "Time [m] = " <<  float(time(NULL) - vInitialTime)/60. << std::endl;
    std::cout << "       END CALCULATION      " << std::endl;
    std::cout << "........oooOO00OOooo........" << std::endl;

    return 0;
}

/////////////////////////////////////////////////////
//////////////////*****end*****//////////////////////
/////////////////////////////////////////////////////
