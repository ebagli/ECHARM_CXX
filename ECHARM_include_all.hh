//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//


// general
#include "ECHARM_constants.hh"

#include "ECHARM_3vec.hh"
#include "ECHARM_3vec.cpp"

#include "ECHARM_intrp.hh"
#include "ECHARM_intrp.cpp"

#include "ECHARM_periodicvector.hh"
#include "ECHARM_periodicvector.cpp"

#include "ECHARM_distribution.hh"
#include "ECHARM_distribution.cpp"

#include "ECHARM_distribution_gauss.hh"
#include "ECHARM_distribution_gauss.cpp"

#include "ECHARM_distribution_box.hh"
#include "ECHARM_distribution_box.cpp"



// particle & beam
#include "ECHARM_particle.hh"
#include "ECHARM_particle.cpp"

#include "ECHARM_beam.hh"
#include "ECHARM_beam.cpp"



// crystal & strip
#include "ECHARM_atom.hh"
#include "ECHARM_atom.cpp"
#include "ECHARM_atom_spheric.hh"
#include "ECHARM_atom_spheric.cpp"
#include "ECHARM_atom_moliere.hh"
#include "ECHARM_atom_moliere.cpp"
#include "ECHARM_atom_lindhard.hh"
#include "ECHARM_atom_lindhard.cpp"
#include "ECHARM_atom_xray.hh"
#include "ECHARM_atom_xray.cpp"


#include "ECHARM_miller.hh"
#include "ECHARM_miller.cpp"
#include "ECHARM_miller_orto.hh"
#include "ECHARM_miller_orto.cpp"
#include "ECHARM_miller_cubic.hh"
#include "ECHARM_miller_cubic.cpp"

#include "ECHARM_lattice.hh"
#include "ECHARM_lattice.cpp"
#include "ECHARM_lattice_bcc.hh"
#include "ECHARM_lattice_bcc.cpp"
#include "ECHARM_lattice_cubic.hh"
#include "ECHARM_lattice_cubic.cpp"
#include "ECHARM_lattice_fcc.hh"
#include "ECHARM_lattice_fcc.cpp"
#include "ECHARM_lattice_diamond.hh"
#include "ECHARM_lattice_diamond.cpp"

#include "ECHARM_cell.hh"
#include "ECHARM_cell.cpp"

#include "ECHARM_crystal.hh"
#include "ECHARM_crystal.cpp"

#include "ECHARM_strip.hh"
#include "ECHARM_strip.cpp"



// crystal database
#include "ECHARM_crystal_Si.hh"
#include "ECHARM_crystal_Si.cpp"

#include "ECHARM_crystal_LiNbO3.hh"
#include "ECHARM_crystal_LiNbO3.cpp"


// electrical characteristics
#include "ECHARM_EC.hh"
#include "ECHARM_EC.cpp"

#include "ECHARM_EC_const.hh"
#include "ECHARM_EC_const.cpp"

#include "ECHARM_EC_intrp.hh"
#include "ECHARM_EC_intrp.cpp"

#include "ECHARM_EC_rec.hh"
#include "ECHARM_EC_rec.cpp"

#include "ECHARM_EC_rec_pot.hh"
#include "ECHARM_EC_rec_pot.cpp"

#include "ECHARM_EC_rec_atd.hh"
#include "ECHARM_EC_rec_atd.cpp"

#include "ECHARM_EC_rec_eld.hh"
#include "ECHARM_EC_rec_eld.cpp"

#include "ECHARM_EC_rec_efx.hh"
#include "ECHARM_EC_rec_efx.cpp"

#include "ECHARM_EC_rec_efy.hh"
#include "ECHARM_EC_rec_efy.cpp"

#include "ECHARM_EC_rec_efz.hh"
#include "ECHARM_EC_rec_efz.cpp"

#include "ECHARM_EC_rec_pot_pl.hh"
#include "ECHARM_EC_rec_pot_pl.cpp"

#include "ECHARM_EC_rec_atd_pl.hh"
#include "ECHARM_EC_rec_atd_pl.cpp"

#include "ECHARM_EC_rec_eld_pl.hh"
#include "ECHARM_EC_rec_eld_pl.cpp"

#include "ECHARM_EC_rec_efx_pl.hh"
#include "ECHARM_EC_rec_efx_pl.cpp"

#include "ECHARM_EC_rec_efy_pl.hh"
#include "ECHARM_EC_rec_efy_pl.cpp"

#include "ECHARM_EC_rec_efz_pl.hh"
#include "ECHARM_EC_rec_efz_pl.cpp"

#include "ECHARM_EC_rec_pot_ax.hh"
#include "ECHARM_EC_rec_pot_ax.cpp"

#include "ECHARM_EC_rec_atd_ax.hh"
#include "ECHARM_EC_rec_atd_ax.cpp"

#include "ECHARM_EC_rec_eld_ax.hh"
#include "ECHARM_EC_rec_eld_ax.cpp"

#include "ECHARM_EC_rec_efx_ax.hh"
#include "ECHARM_EC_rec_efx_ax.cpp"

#include "ECHARM_EC_rec_efy_ax.hh"
#include "ECHARM_EC_rec_efy_ax.cpp"

#include "ECHARM_EC_rec_efz_ax.hh"
#include "ECHARM_EC_rec_efz_ax.cpp"



// kernel & processes
#include "ECHARM_kernel.hh"
#include "ECHARM_kernel.cpp"

#include "ECHARM_process.hh"
#include "ECHARM_process.cpp"

#include "ECHARM_process_ms.hh"
#include "ECHARM_process_ms.cpp"

#include "ECHARM_process_cpc141_2001.hh"
#include "ECHARM_process_cpc141_2001.cpp"

#include "ECHARM_process_cpc141_2001_semigauss.hh"
#include "ECHARM_process_cpc141_2001_semigauss.cpp"

#include "ECHARM_process_cpc141_2001_doublegauss.hh"
#include "ECHARM_process_cpc141_2001_doublegauss.cpp"

#include "ECHARM_process_ms_tikhomirov.hh"
#include "ECHARM_process_ms_tikhomirov.cpp"

#include "ECHARM_defect.hh"
#include "ECHARM_defect.cpp"

#include "ECHARM_defect_edge.hh"
#include "ECHARM_defect_edge.cpp"

#include "ECHARM_defect_screw.hh"
#include "ECHARM_defect_screw.cpp"

#include "ECHARM_defect_stacking_fault.hh"
#include "ECHARM_defect_stacking_fault.cpp"

#include "ECHARM_radiation.hh"
#include "ECHARM_radiation.cpp"





// strip database
#include "ECHARM_ST45.hh"
#include "ECHARM_ST45.cpp"

#include "ECHARM_STtest.hh"
#include "ECHARM_STtest.cpp"

#include "ECHARM_SiAM.hh"
#include "ECHARM_SiAM.cpp"

#include "ECHARM_LiNbO3_1.hh"
#include "ECHARM_LiNbO3_1.cpp"

#include "ECHARM_FIG5_PRE52_2045.hh"
#include "ECHARM_FIG5_PRE52_2045.cpp"

// beam database
#include "ECHARM_beam_H8_2012.hh"
#include "ECHARM_beam_H8_2012.cpp"

#include "ECHARM_beam_H8_pencil.hh"
#include "ECHARM_beam_H8_pencil.cpp"

#include "ECHARM_beam_MAMI855.hh"
#include "ECHARM_beam_MAMI855.cpp"

#include "ECHARM_MAMIPRL.hh"
#include "ECHARM_MAMIPRL.cpp"
