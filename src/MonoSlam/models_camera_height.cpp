/*  MonoSLAM: Real-Time Single Camera SLAM

    MonoSLAM/models_camera_height.cpp
    Copyright (C) 2005 University of Oxford

    Author
    Andrew Davison
    ajd@robots.ox.ac.uk
    Scene home page: http://www.robots.ox.ac.uk/~ajd/Scene/

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include <VNL/sample.h>
#include "models_camera_height.h"

Camera_Height_Internal_Measurement_Model::
Camera_Height_Internal_Measurement_Model(Motion_Model *motion_model)
  : Internal_Measurement_Model(1, motion_model, "THREED_CAMERA_HEIGHT"),
    SD_meas_filter(0.02),
    SD_meas_simulation(0.02)
{
}

Camera_Height_Internal_Measurement_Model::
~Camera_Height_Internal_Measurement_Model()
{

}


void Camera_Height_Internal_Measurement_Model::
func_hv_and_dhv_by_dxv(const VNL::Vector<double> &xv)
{
  assert(xv.Size() == motion_model->STATE_SIZE);

  // Just pull out z part of state
  hvRES.Update(xv.Extract(1, 2));

  // dhv_by_dxv = (dhv_by_dr dhv_by_dq dhv_by_dv dhv_by_domega)
  dhv_by_dxvRES.Fill(0.0);
  VNL::Matrix<double> I11(1, 1);
  I11.SetIdentity();
  dhv_by_dxvRES.Update(I11, 0, 2);
}

void Camera_Height_Internal_Measurement_Model::
func_Rv(const VNL::Vector<double> &hv)
{
  // Diagonal measurement covariance
  double measurement_noise_variance = SD_meas_filter * SD_meas_filter;

  RvRES.SetIdentity();

  RvRES *= measurement_noise_variance;
}

void Camera_Height_Internal_Measurement_Model::
func_nuv(const VNL::Vector<double> &hv, const VNL::Vector<double> &zv)
{
  // Straightforward
  nuvRES.Update(zv - hv);
}

void Camera_Height_Internal_Measurement_Model::
func_hv_noisy(const VNL::Vector<double> &xv_true)
{
  func_hv_and_dhv_by_dxv(xv_true);

  hv_noisyRES.Put(0, VNL::SampleNormal(hvRES(0), SD_meas_simulation));
}

bool Camera_Height_Internal_Measurement_Model::
feasibility_test(const VNL::Vector<double> &xv, const VNL::Vector<double> &hv)
{
  // Always feasible
  return true;
}

