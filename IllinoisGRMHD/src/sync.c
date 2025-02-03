#include "IllinoisGRMHD.h"

void IllinoisGRMHD_sync(CCTK_ARGUMENTS) {
}

void IllinoisGRMHD_symmetry(CCTK_ARGUMENTS) {
  DECLARE_CCTK_PARAMETERS;
  DECLARE_CCTK_ARGUMENTS;

  // impose b/c if needed (this assumes, that all refined levels also touch the
  // symmetry boundary)
  if(zsymmetry && cctk_bbox[(3-1)*2+0]) {
    for(int k = 0 ; k < cctk_nghostzones[2] ; k++) {
      for(int j = 0 ; j < cctk_lsh[1] ; j++) {
        for(int i = 0 ; i < cctk_lsh[0] ; i++) {
          int idx = CCTK_GFINDEX3D(cctkGH, i,j,k);
          int idx_mirror = CCTK_GFINDEX3D(cctkGH, i,j,2*cctk_nghostzones[2] - k);
          rho_star[idx] = +rho_star[idx_mirror];
          tau     [idx] = +tau     [idx_mirror];
          Stildex[idx] = +Stildex[idx_mirror];
          Stildey[idx] = +Stildey[idx_mirror];
          Stildez[idx] = -Stildez[idx_mirror];
          Ax[idx] = Ay[idx] = Az[idx] = 0.;
          phitilde[idx] = 0.;
        }
      }
    }
  }
}
