#ifndef _ECHARM_save_structure_h
#define _ECHARM_save_structure_h

struct ECHARM_Particle_Save
{
    double x;
    double y;
    double z;
    double px;
    double py;
    double pz;
};
struct ECHARM_Strip_Save
{
    double Rx;
    double Ry;
    double Rz;
    double Lx;
    double Ly;
    double Lz;
};
struct ECHARM_Miller_Save
{
    int MillerPlane0;
    int MillerPlane1;
    int MillerPlane2;
    int MillerAxis0;
    int MillerAxis1;
    int MillerAxis2;
};

void ECHARM_Particle_Save_Copy(ECHARM_Particle_Save &vInput,ECHARM_Particle_Save &vOutput)
{
    vOutput.x = vInput.x;
    vOutput.y = vInput.y;
    vOutput.z = vInput.z;
    vOutput.px = vInput.px;
    vOutput.py = vInput.py;
    vOutput.pz = vInput.pz;
}

void ECHARM_Strip_Save_Copy(ECHARM_Strip_Save &vInput,ECHARM_Strip_Save &vOutput)
{
    vOutput.Rx = vInput.Rx;
    vOutput.Ry = vInput.Ry;
    vOutput.Rz = vInput.Rz;
    vOutput.Lx = vInput.Lx;
    vOutput.Ly = vInput.Ly;
    vOutput.Lz = vInput.Lz;
}

#endif

