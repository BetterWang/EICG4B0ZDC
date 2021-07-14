//____________________________________________________________________________..
//
// This is a working template for the G4 Construct() method which needs to be implemented
// We wedge a method between the G4 Construct() to enable volume hierarchies on the macro
// so here it is called ConstructMe() but there is no functional difference
// Currently this installs a simple G4Box solid, creates a logical volume from it
// and places it. Put your own detector in place (just make sure all active volumes
// get inserted into the m_PhysicalVolumesSet)
//
// Rather than using hardcoded values you should consider using the parameter class
// Parameter names and defaults are set in EICG4B0ZDCSubsystem::SetDefaultParameters()
// Only parameters defined there can be used (also to override in the macro)
// to avoids typos.
// IMPORTANT: parameters have no inherent units, there is a convention (cm/deg)
// but in any case you need to multiply them here with the correct CLHEP/G4 unit
//
// The place where you put your own detector is marked with
// //begin implement your own here://
// //end implement your own here://
// Do not forget to include the G4 includes for your volumes
//____________________________________________________________________________..

#include "EICG4B0ZDCDetector.h"

#include <phparameter/PHParameters.h>

#include <g4main/PHG4Detector.h>

#include <Geant4/G4Tubs.hh>
#include <Geant4/G4Color.hh>
#include <Geant4/G4LogicalVolume.hh>
#include <Geant4/G4Material.hh>
#include <Geant4/G4PVPlacement.hh>
#include <Geant4/G4SystemOfUnits.hh>
#include <Geant4/G4VisAttributes.hh>

#include <cmath>
#include <iostream>

class G4VSolid;
class PHCompositeNode;

using namespace std;

//____________________________________________________________________________..
EICG4B0ZDCDetector::EICG4B0ZDCDetector(PHG4Subsystem *subsys,
                                         PHCompositeNode *Node,
                                         PHParameters *parameters,
                                         const std::string &dnam)
  : PHG4Detector(subsys, Node, dnam)
  , m_Params(parameters)
{
}

//_______________________________________________________________
int EICG4B0ZDCDetector::IsInDetector(G4VPhysicalVolume *volume) const
{
  set<G4VPhysicalVolume *>::const_iterator iter = m_PhysicalVolumesSet.find(volume);
  if (iter != m_PhysicalVolumesSet.end())
  {
    return 1;
  }
  return 0;
}

int EICG4B0ZDCDetector::GetDetId(G4VPhysicalVolume *volume) const
{
    if ( IsInDetector(volume) ) {
        return 1;
    }
    return -1;
}

//_______________________________________________________________
void EICG4B0ZDCDetector::ConstructMe(G4LogicalVolume *logicWorld)
{
 //begin implement your own here://
 // Do not forget to multiply the parameters with their respective CLHEP/G4 unit !
  G4VSolid *solid = new G4Tubs("EICG4B0ZDCSolid",
          0.,
          m_Params->get_double_param("outer_radius") * cm,
          m_Params->get_double_param("length")/2. * cm,
          0., 360.*degree);
  G4LogicalVolume *logical = new G4LogicalVolume(solid,
          G4Material::GetMaterial("G4_PbWO4"), //G4Material::GetMaterial(m_Params->get_string_param("material")),
          "EICG4B0ZDCLogical");

  G4VisAttributes *vis = new G4VisAttributes(G4Color(0.8, 0.2, 0.2, 0.9));
  vis->SetForceSolid(true);
  logical->SetVisAttributes(vis);
  G4RotationMatrix *rotm = new G4RotationMatrix();
  rotm->rotateY(m_Params->get_double_param("rot_y") * deg);
//  rotm->rotateY(0. * deg);

  G4VPhysicalVolume *phy = new G4PVPlacement(
      rotm,
      G4ThreeVector(m_Params->get_double_param("place_x") * cm,
                    m_Params->get_double_param("place_y") * cm,
                    m_Params->get_double_param("place_z") * cm),
//      G4ThreeVector(0. * cm,
//                    0. * cm,
//                    0. * cm),
      logical, "EICG4B0ZDC", logicWorld, 0, false, OverlapCheck());
  // add it to the list of placed volumes so the IsInDetector method
  // picks them up
  m_PhysicalVolumesSet.insert(phy);
  // hard code detector id to 1
  m_PhysicalVolumesDet.insert({phy, 1});
//  m_LogicalVolumesSet.insert(logical);
 //end implement your own here://
  return;
}

//_______________________________________________________________
void EICG4B0ZDCDetector::Print(const std::string &what) const
{
  std::cout << "EICG4B0ZDC Detector:" << std::endl;
  if (what == "ALL" || what == "VOLUME")
  {
    std::cout << "Version 0.1" << std::endl;
    std::cout << "Parameters:" << std::endl;
    m_Params->Print();
  }
  return;
}

PHParameters * EICG4B0ZDCDetector::getParams()
{ return m_Params; }
