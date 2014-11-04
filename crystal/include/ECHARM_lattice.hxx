//
//  ECHARM_lattice.h
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//
//  Short class description:
//   Class ECHARM_lattice is a container of the coordinate of lattice points expressed as a ratio on the main cell size
//   It is forbidden to have a difference number of vIndexes for the three coordinate vector.
//   The coordinate are not expressed in an orthogonal base but in the cell base which will be selected in the ECHARM_crystal class.

public:
inline int GetCoordinatesNumber() {return fLatticeCoordinates.size();};
inline std::vector<ECHARM_3vec*> GetCoordinates() {return fLatticeCoordinates;};

inline void Clear() {fLatticeCoordinates.clear();};
inline void Add(double X, double Y, double Z) {
    ECHARM_3vec *vector = new ECHARM_3vec(X,Y,Z);
    fLatticeCoordinates.push_back(vector);};
inline void Delete(unsigned int vIndex) {fLatticeCoordinates.erase(fLatticeCoordinates.begin()+vIndex);};
