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

#include "ECHARM_distribution_gauss_cut.hh"
#include "ECHARM_distribution_gauss_cut.cpp"

#include "ECHARM_distribution_box.hh"
#include "ECHARM_distribution_box.cpp"

#include "ECHARM_distribution_const.hh"
#include "ECHARM_distribution_const.cpp"

#include "ECHARM_file_save.hh"
#include "ECHARM_file_save.cpp"

#ifdef ROOT_
#include "ECHARM_ROOT_save.hh"
#include "ECHARM_ROOT_save.cpp"
#endif

#include "ECHARM_info_save.hh"
#include "ECHARM_info_save.cpp"

#include "ECHARM_manager.hh"
#include "ECHARM_manager.cpp"



// particle & beam
#include "ECHARM_particle.hh"
#include "ECHARM_particle.cpp"

#include "ECHARM_beam.hh"
#include "ECHARM_beam.cpp"


// crystal & strip
#include "ECHARM_atom.hh"
#include "ECHARM_atom.cpp"

#include "ECHARM_miller.hh"
#include "ECHARM_miller.cpp"

#include "ECHARM_lattice.hh"
#include "ECHARM_lattice.cpp"

#include "ECHARM_cell.hh"
#include "ECHARM_cell.cpp"

#include "ECHARM_crystal.hh"
#include "ECHARM_crystal.cpp"

#include "ECHARM_strip.hh"
#include "ECHARM_strip.cpp"


// electrical characteristics
#include "ECHARM_EC.hh"
#include "ECHARM_EC.cpp"

#include "ECHARM_EC_const.hh"
#include "ECHARM_EC_const.cpp"

#include "ECHARM_EC_intrp.hh"
#include "ECHARM_EC_intrp.cpp"

#include "ECHARM_EC_direct.hh"
#include "ECHARM_EC_direct.cpp"

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

#include "ECHARM_process_ms_tikhomirov_2015.hh"
#include "ECHARM_process_ms_tikhomirov_2015.cpp"

#include "ECHARM_process_ss.hh"
#include "ECHARM_process_ss.cpp"

#include "ECHARM_displacement.hh"
#include "ECHARM_displacement.cpp"

#include "ECHARM_defect.hh"
#include "ECHARM_defect.cpp"

#include "ECHARM_defect_edge.hh"
#include "ECHARM_defect_edge.cpp"

#include "ECHARM_defect_screw.hh"
#include "ECHARM_defect_screw.cpp"

#include "ECHARM_defect_point.hh"
#include "ECHARM_defect_point.cpp"

#include "ECHARM_defect_stacking_fault.hh"
#include "ECHARM_defect_stacking_fault.cpp"

#include "ECHARM_radiation.hh"
#include "ECHARM_radiation.cpp"

#include "ECHARM_radiation_noparts.hh"
#include "ECHARM_radiation_noparts.cpp"

#include "ECHARM_undulator.hh"
#include "ECHARM_undulator.cpp"

#include "ECHARM_process_bethe_bloch.hh"
#include "ECHARM_process_bethe_bloch.cpp"

#include "ECHARM_torsion.hh"
#include "ECHARM_torsion.cpp"



// miller database
#include "ECHARM_miller_orto.hh"
#include "ECHARM_miller_orto.cpp"

#include "ECHARM_miller_cubic.hh"
#include "ECHARM_miller_cubic.cpp"

// atom database
#include "ECHARM_atom_spheric.hh"
#include "ECHARM_atom_spheric.cpp"

#include "ECHARM_atom_moliere.hh"
#include "ECHARM_atom_moliere.cpp"

#include "ECHARM_atom_lindhard.hh"
#include "ECHARM_atom_lindhard.cpp"

#include "ECHARM_atom_xray.hh"
#include "ECHARM_atom_xray.cpp"

// lattice database
#include "ECHARM_lattice_single.hh"
#include "ECHARM_lattice_single.cpp"

#include "ECHARM_lattice_bcc.hh"
#include "ECHARM_lattice_bcc.cpp"

#include "ECHARM_lattice_cubic.hh"
#include "ECHARM_lattice_cubic.cpp"

#include "ECHARM_lattice_fcc.hh"
#include "ECHARM_lattice_fcc.cpp"

#include "ECHARM_lattice_diamond.hh"
#include "ECHARM_lattice_diamond.cpp"

#include "ECHARM_lattice_zincblend_a.hh"
#include "ECHARM_lattice_zincblend_a.cpp"

#include "ECHARM_lattice_zincblend_b.hh"
#include "ECHARM_lattice_zincblend_b.cpp"

// crystal database
#include "ECHARM_crystal_Si.hh"
#include "ECHARM_crystal_Si.cpp"

#include "ECHARM_crystal_Si_singleatom.hh"
#include "ECHARM_crystal_Si_singleatom.cpp"

#include "ECHARM_crystal_Si_Defect.hh"
#include "ECHARM_crystal_Si_Defect.cpp"

#include "ECHARM_crystal_LiNbO3.hh"
#include "ECHARM_crystal_LiNbO3.cpp"

#include "ECHARM_crystal_LiNbO3_cubic.hh"
#include "ECHARM_crystal_LiNbO3_cubic.cpp"

#include "ECHARM_crystal_SiGe.hh"
#include "ECHARM_crystal_SiGe.cpp"

#include "ECHARM_crystal_Ge.hh"
#include "ECHARM_crystal_Ge.cpp"

#include "ECHARM_crystal_Ni.hh"
#include "ECHARM_crystal_Ni.cpp"

#include "ECHARM_crystal_InSb.hh"
#include "ECHARM_crystal_InSb.cpp"

#include "ECHARM_crystal_PbWO4.hh"
#include "ECHARM_crystal_PbWO4.cpp"

#include "ECHARM_crystal_Vacuum.hh"
#include "ECHARM_crystal_Vacuum.cpp"

// strip database
#include "ECHARM_Vacuum.hh"
#include "ECHARM_Vacuum.cpp"

#include "ECHARM_STLHC.hh"
#include "ECHARM_STLHC.cpp"

#include "ECHARM_STLHC_UA9SIM.hh"
#include "ECHARM_STLHC_UA9SIM.cpp"

#include "ECHARM_STLHC_2mm.hh"
#include "ECHARM_STLHC_2mm.cpp"

#include "ECHARM_ST45.hh"
#include "ECHARM_ST45.cpp"

#include "ECHARM_STtest.hh"
#include "ECHARM_STtest.cpp"

#include "ECHARM_ST_InSb.hh"
#include "ECHARM_ST_InSb.cpp"

#include "ECHARM_SiEnhancement.hh"
#include "ECHARM_SiEnhancement.cpp"

#include "ECHARM_SiAM.hh"
#include "ECHARM_SiAM.cpp"

#include "ECHARM_SiVacancy.hh"
#include "ECHARM_SiVacancy.cpp"

#include "ECHARM_LiNbO3_1.hh"
#include "ECHARM_LiNbO3_1.cpp"

#include "ECHARM_LiNbO3_1_cubic.hh"
#include "ECHARM_LiNbO3_1_cubic.cpp"

#include "ECHARM_LiNbO3_Si_Ge.hh"
#include "ECHARM_LiNbO3_Si_Ge.cpp"

#include "ECHARM_FIG5_PRE52_2045.hh"
#include "ECHARM_FIG5_PRE52_2045.cpp"

#include "ECHARM_QM30_33.hh"
#include "ECHARM_QM30_33.cpp"

#include "ECHARM_QM60_150.hh"
#include "ECHARM_QM60_150.cpp"

#include "ECHARM_QM_CERN_H4_1mm.hh"
#include "ECHARM_QM_CERN_H4_1mm.cpp"

#include "ECHARM_FIG14_NIMB266_3835_111.hh"
#include "ECHARM_FIG14_NIMB266_3835_111.cpp"

#include "ECHARM_FIG14_NIMB266_3835_110.hh"
#include "ECHARM_FIG14_NIMB266_3835_110.cpp"

#include "ECHARM_FIG14_NIMB266_3835_100.hh"
#include "ECHARM_FIG14_NIMB266_3835_100.cpp"

#include "ECHARM_UNDO_UGG2014.hh"
#include "ECHARM_UNDO_UGG2014.cpp"

#include "ECHARM_NiCOMECER.hh"
#include "ECHARM_NiCOMECER.cpp"

#include "ECHARM_EC_CALC.hh"
#include "ECHARM_EC_CALC.cpp"

#include "ECHARM_PL01.hh"
#include "ECHARM_PL01.cpp"

#include "ECHARM_PL02.hh"
#include "ECHARM_PL02.cpp"

#include "ECHARM_StripPbWO4.hh"
#include "ECHARM_StripPbWO4.cpp"

#include "ECHARM_STAX110.hh"
#include "ECHARM_STAX110.cpp"

#include "ECHARM_STAX111.hh"
#include "ECHARM_STAX111.cpp"

// beam database
#include "ECHARM_beam_ee_discrimination.hh"
#include "ECHARM_beam_ee_discrimination.cpp"

#include "ECHARM_beam_LHC_UA9.hh"
#include "ECHARM_beam_LHC_UA9.cpp"

#include "ECHARM_beam_H4_electron.hh"
#include "ECHARM_beam_H4_electron.cpp"

#include "ECHARM_beam_H4_positron.hh"
#include "ECHARM_beam_H4_positron.cpp"

#include "ECHARM_beam_H8_2012_UA9.hh"
#include "ECHARM_beam_H8_2012_UA9.cpp"

#include "ECHARM_beam_H8_2012.hh"
#include "ECHARM_beam_H8_2012.cpp"

#include "ECHARM_beam_H8_pencil.hh"
#include "ECHARM_beam_H8_pencil.cpp"

#include "ECHARM_beam_H8_cut.hh"
#include "ECHARM_beam_H8_cut.cpp"

#include "ECHARM_beam_pencil.hh"
#include "ECHARM_beam_pencil.cpp"

#include "ECHARM_beam_COMECER.hh"
#include "ECHARM_beam_COMECER.cpp"

#include "ECHARM_beam_MAMI855.hh"
#include "ECHARM_beam_MAMI855.cpp"

#include "ECHARM_beam_MAMI600.hh"
#include "ECHARM_beam_MAMI600.cpp"

#include "ECHARM_beam_SLAC.hh"
#include "ECHARM_beam_SLAC.cpp"

#include "ECHARM_beam_FACET.hh"
#include "ECHARM_beam_FACET.cpp"
