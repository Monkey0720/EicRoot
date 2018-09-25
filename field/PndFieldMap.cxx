// -------------------------------------------------------------------------
// -----                      PndFieldMap source file                  -----
// -----         Created 12/01/04  by M. Al/Turany (FairField.cxx)      -----
// -------------------------------------------------------------------------


#include <iomanip>
#include <iostream>
#include <fstream>
#include "stdlib.h"

#include "TArrayF.h"
#include "TFile.h"
#include "TMath.h"

#include "PndFieldMap.h"
#include "PndFieldMapData.h"
#include "PndFieldPar.h"

using namespace std;

// -------------   Default constructor  ----------------------------------
PndFieldMap::PndFieldMap() 
  : FairField(),
	fFileName(""),
    fScale(1.0),
    funit(10.0),
    fPosX(0), fPosY(0), fPosZ(0),
    fXmin(0), fXmax(0), fXstep(0),
	fYmin(0), fYmax(0), fYstep(0),
    fZmin(0), fZmax(0), fZstep(0),
    fNx(0),fNy(0),fNz(0),
    fBx(NULL), fBy(NULL), fBz(NULL)   
{
  SetName("");
  fType = 1;
}
// ------------------------------------------------------------------------



// -------------   Standard constructor   ---------------------------------
PndFieldMap::PndFieldMap(const char* mapName, const char* fileType)
  : FairField(mapName),
    fFileName(TString("")),
    fScale(1.0),
    funit(10.0),
    fPosX(0), fPosY(0), fPosZ(0),
    fXmin(0), fXmax(0), fXstep(0),
    fYmin(0), fYmax(0), fYstep(0),
    fZmin(0), fZmax(0), fZstep(0),
    fNx(0),fNy(0),fNz(0),
    fBx(NULL), fBy(NULL), fBz(NULL)   
{
  SetName(mapName);
  TString dir = getenv("VMCWORKDIR");
  fFileName = dir + "/input/" + mapName;
  if ( fileType[0] == 'R' ) fFileName += ".root";
  else                      fFileName += ".dat";
  fType = 1;
}
// ------------------------------------------------------------------------



// ------------   Constructor from PndFieldPar   --------------------------
PndFieldMap::PndFieldMap(PndFieldPar* fieldPar) 
  : FairField(),
	fFileName(TString("")),
    fScale(1.0),
    funit(10.0),
    fPosX(0), fPosY(0), fPosZ(0),
    fXmin(0), fXmax(0), fXstep(0),
    fYmin(0), fYmax(0), fYstep(0),
    fZmin(0), fZmax(0), fZstep(0),
    fNx(0),fNy(0),fNz(0),
    fBx(NULL), fBy(NULL), fBz(NULL)   
{
  fType = 1;
  if ( ! fieldPar ) {
    gLogger->Error(MESSAGE_ORIGIN, "PndConstField::PndConstField: empty parameter container!");
    SetName("");
	fType     = -1;
  }
  else {
    TString Name=GetName();
    fieldPar->MapName(Name);
    fPosX  = fieldPar->GetPositionX();
    fPosY  = fieldPar->GetPositionY();
    fPosZ  = fieldPar->GetPositionZ();
    fScale = fieldPar->GetScale();
    TString dir = getenv("VMCWORKDIR");
    fFileName = dir + "/input/" + Name + ".root";
    fType = fieldPar->GetType();
  }
}
// ------------------------------------------------------------------------



// ------------   Destructor   --------------------------------------------
PndFieldMap::~PndFieldMap() {
	
	//printf("PndFieldMap::~PndFieldMap() \n");
  if ( fBx ) delete fBx;
  if ( fBy ) delete fBy;
  if ( fBz ) delete fBz;
}
// ------------------------------------------------------------------------



// -----------   Intialisation   ------------------------------------------
void PndFieldMap::Init() {
  if      (fFileName.EndsWith(".root")) ReadRootFile(fFileName, fName);
  else if (fFileName.EndsWith(".dat"))  ReadAsciiFile(fFileName);
  else {
    gLogger->Error(MESSAGE_ORIGIN,"-E- PndFieldMap::Init: No proper file name defined! (%s) ");
    Fatal("Init", "No proper file name");
  }
}
// ------------------------------------------------------------------------



// -----------   Get x component of the field   ---------------------------
Double_t PndFieldMap::GetBx(Double_t x, Double_t y, Double_t z) {

  Int_t ix    = 0;
  Int_t iy    = 0;
  Int_t iz    = 0;
  Double_t dx = 0.;
  Double_t dy = 0.;
  Double_t dz = 0.;

  if ( IsInside(x, y, z, ix, iy, iz, dx, dy, dz) ) {

  // Get Bx field values at grid cell corners
  fHa[0][0][0] = fBx->At(ix    *fNy*fNz + iy    *fNz + iz);
  fHa[1][0][0] = fBx->At((ix+1)*fNy*fNz + iy    *fNz + iz);
  fHa[0][1][0] = fBx->At(ix    *fNy*fNz + (iy+1)*fNz + iz);
  fHa[1][1][0] = fBx->At((ix+1)*fNy*fNz + (iy+1)*fNz + iz);
  fHa[0][0][1] = fBx->At(ix    *fNy*fNz + iy    *fNz + (iz+1));
  fHa[1][0][1] = fBx->At((ix+1)*fNy*fNz + iy    *fNz + (iz+1));
  fHa[0][1][1] = fBx->At(ix    *fNy*fNz + (iy+1)*fNz + (iz+1));
  fHa[1][1][1] = fBx->At((ix+1)*fNy*fNz + (iy+1)*fNz + (iz+1));

  // Return interpolated field value
  return Interpolate(dx, dy, dz);

  }

  return 0.;
}
// ------------------------------------------------------------------------



// -----------   Get y component of the field   ---------------------------
Double_t PndFieldMap::GetBy(Double_t x, Double_t y, Double_t z) {

  Int_t ix    = 0;
  Int_t iy    = 0;
  Int_t iz    = 0;
  Double_t dx = 0.;
  Double_t dy = 0.;
  Double_t dz = 0.;

  if ( IsInside(x, y, z, ix, iy, iz, dx, dy, dz) ) {

  // Get By field values at grid cell corners
  fHa[0][0][0] = fBy->At(ix    *fNy*fNz + iy    *fNz + iz);
  fHa[1][0][0] = fBy->At((ix+1)*fNy*fNz + iy    *fNz + iz);
  fHa[0][1][0] = fBy->At(ix    *fNy*fNz + (iy+1)*fNz + iz);
  fHa[1][1][0] = fBy->At((ix+1)*fNy*fNz + (iy+1)*fNz + iz);
  fHa[0][0][1] = fBy->At(ix    *fNy*fNz + iy    *fNz + (iz+1));
  fHa[1][0][1] = fBy->At((ix+1)*fNy*fNz + iy    *fNz + (iz+1));
  fHa[0][1][1] = fBy->At(ix    *fNy*fNz + (iy+1)*fNz + (iz+1));
  fHa[1][1][1] = fBy->At((ix+1)*fNy*fNz + (iy+1)*fNz + (iz+1));

  // Return interpolated field value
  return Interpolate(dx, dy, dz);

  }

  return 0.;
}
// ------------------------------------------------------------------------



// -----------   Get z component of the field   ---------------------------
Double_t PndFieldMap::GetBz(Double_t x, Double_t y, Double_t z) {

  Int_t ix    = 0;
  Int_t iy    = 0;
  Int_t iz    = 0;
  Double_t dx = 0.;
  Double_t dy = 0.;
  Double_t dz = 0.;

  if ( IsInside(x, y, z, ix, iy, iz, dx, dy, dz) ) {

  // Get Bz field values at grid cell corners
  fHa[0][0][0] = fBz->At(ix    *fNy*fNz + iy    *fNz + iz);
  fHa[1][0][0] = fBz->At((ix+1)*fNy*fNz + iy    *fNz + iz);
  fHa[0][1][0] = fBz->At(ix    *fNy*fNz + (iy+1)*fNz + iz);
  fHa[1][1][0] = fBz->At((ix+1)*fNy*fNz + (iy+1)*fNz + iz);
  fHa[0][0][1] = fBz->At(ix    *fNy*fNz + iy    *fNz + (iz+1));
  fHa[1][0][1] = fBz->At((ix+1)*fNy*fNz + iy    *fNz + (iz+1));
  fHa[0][1][1] = fBz->At(ix    *fNy*fNz + (iy+1)*fNz + (iz+1));
  fHa[1][1][1] = fBz->At((ix+1)*fNy*fNz + (iy+1)*fNz + (iz+1));

  // Return interpolated field value
  return Interpolate(dx, dy, dz);

  }

  return 0.;
}
// ------------------------------------------------------------------------



// -----------   Check whether a point is inside the map   ----------------
Bool_t PndFieldMap::IsInside(Double_t x, Double_t y, Double_t z,
			     Int_t& ix, Int_t& iy, Int_t& iz,
			     Double_t& dx, Double_t& dy, Double_t& dz) {

  // --- Transform into local coordinate system
  Double_t xl = x - fPosX;
  Double_t yl = y - fPosY;
  Double_t zl = z - fPosZ;

  // ---  Check for being outside the map range
  if ( ! ( xl >= fXmin && xl < fXmax && yl >= fYmin && yl < fYmax &&
	   zl >= fZmin && zl < fZmax ) ) {
    ix = iy = iz = 0;
    dx = dy = dz = 0.;
    return kFALSE;
  }
 
  // --- Determine grid cell
  ix = Int_t( xl / fXstep );
  iy = Int_t( yl / fYstep );
  iz = Int_t( zl / fZstep );


  // Relative distance from grid point (in units of cell size)
  dx = xl / fXstep - Double_t(ix);
  dy = yl / fYstep - Double_t(iy);
  dz = zl / fZstep - Double_t(iz);

  return kTRUE;

}
// ------------------------------------------------------------------------



// ----------   Write the map to an ASCII file   --------------------------
void PndFieldMap::WriteAsciiFile(const char* fileName) {

  // Open file
  gLogger->Info(MESSAGE_ORIGIN, "PndFieldMap: Writing field map to ASCII file %s ",fileName);
  ofstream mapFile(fileName);
  if ( ! mapFile.is_open() ) {
    gLogger->Error(MESSAGE_ORIGIN, "PndFieldMap:ReadAsciiFile: Could not open file! ");
    return;
  }

  // Write field map grid parameters
  mapFile.precision(4);
  mapFile << showpoint;
  if ( fType == 1 ) mapFile << "nosym" << endl;
  if ( fType == 2 ) mapFile << "Solenoid" << endl;
  if ( fType == 3 ) mapFile << "Dipole" << endl;
  if ( fType == 4 ) mapFile << "Trans" << endl;
  if ( funit == 10.0  ) mapFile << "T" << endl;
  if ( funit == 0.001 ) mapFile << "G" << endl;
  if ( funit == 1.0   ) mapFile << "kG" << endl;

  mapFile << fXmin << " " << fXmax << " " << fNx << endl;
  mapFile << fYmin << " " << fYmax << " " << fNy << endl;
  mapFile << fZmin << " " << fZmax << " " << fNz << endl;

  // Write field values
  Double_t factor = funit * fScale;  // Takes out scaling 
  cout << right;
  Int_t nTot = fNx * fNy * fNz;
  cout << "-I- PndFieldMap: " << fNx*fNy*fNz << " entries to write... " 
       << setw(3) << 0 << " % ";
  Int_t index=0;
  div_t modul;
  Int_t iDiv = TMath::Nint(nTot/100.);
  for(Int_t ix=0; ix<fNx; ix++) {
    for(Int_t iy=0; iy<fNy; iy++) {
      for(Int_t iz=0; iz<fNz; iz++) {
	index =ix*fNy*fNz + iy*fNz + iz;
	if (iDiv!=0)
	  {
	    modul = div(index,iDiv);
	    if ( modul.rem == 0 ) {
	      Double_t perc = TMath::Nint(100.*index/nTot);
	      cout << "\b\b\b\b\b\b" << setw(3) << perc << " % " << flush;
	    }
	  }
	mapFile << fBx->At(index)/factor << " " << fBy->At(index)/factor 
		<< " " << fBz->At(index)/factor << endl;
      } // z-Loop
    }   // y-Loop
  }     // x-Loop
  cout << "   " << index+1 << " written" << endl;
  mapFile.close();		

}	
// ------------------------------------------------------------------------



// -------   Write field map to a ROOT file   -----------------------------
void PndFieldMap::WriteRootFile(const char* fileName,
				const char* mapName) {

  PndFieldMapData* data = new PndFieldMapData(mapName, *this);
  TFile* oldFile = gFile;
  TFile* file = new TFile(fileName, "RECREATE");
  data->Write();
  file->Close();
  if(oldFile) oldFile->cd();

}
// ------------------------------------------------------------------------



// -----  Set the position of the field centre in global coordinates  -----
void PndFieldMap::SetPosition(Double_t x, Double_t y, Double_t z) {
  fPosX = x;
  fPosY = y;
  fPosZ = z;
}
// ------------------------------------------------------------------------



// ---------   Screen output   --------------------------------------------
void PndFieldMap::Print() {
  TString type = "Map";
  if ( fType == 2 ) type = "Soleniod Map ";
  if ( fType == 3 ) type = "Dipole Map ";
  if ( fType == 4 ) type = "Trans Map ";
  cout << "======================================================" << endl;
  cout.precision(4);
  cout << showpoint;
  cout << "----  " << fTitle << " : " << fName << endl;
  cout << "----" << endl;
  cout << "----  Field type     : " << type << endl;
  cout << "----" << endl;
  cout << "----  Field map grid : " << endl;
  cout << "----  x = " << setw(4) << fXmin << " to " << setw(4) << fXmax 
       << " cm, " << fNx << " grid points, dx = " << fXstep << " cm" << endl;
  cout << "----  y = " << setw(4) << fYmin << " to " << setw(4) << fYmax 
       << " cm, " << fNy << " grid points, dy = " << fYstep << " cm" << endl;
  cout << "----  z = " << setw(4) << fZmin << " to " << setw(4) << fZmax 
       << " cm, " << fNz << " grid points, dz = " << fZstep << " cm" << endl;
  cout << endl;
  cout << "----  Field centre position: ( " << setw(6) << fPosX << ", "
       << setw(6) << fPosY << ", " << setw(6) << fPosZ << ") cm" << endl;
  cout << "----  Field scaling factor: " << fScale << endl;
  Double_t bx = GetBx(0.,0.,0.);
  Double_t by = GetBy(0.,0.,0.);
  Double_t bz = GetBz(0.,0.,0.);
  cout << "----" << endl;
  cout << "----  Field at origin is ( " << setw(6) << bx << ", " << setw(6)
       << by << ", " << setw(6) << bz << ") kG" << endl;
 cout << "======================================================" << endl;
}
// ------------------------------------------------------------------------  



// ---------    Reset parameters and data (private)  ----------------------
void PndFieldMap::Reset() {
  fPosX = fPosY = fPosZ = 0.;
  fXmin = fYmin = fZmin = 0.;
  fXmax = fYmax = fZmax = 0.;
  fXstep = fYstep = fZstep = 0.;
  fNx = fNy = fNz = 0;
  fScale = 1.;
  funit = 10.0;
  if ( fBx ) { delete fBx; fBx = NULL; }
  if ( fBy ) { delete fBy; fBy = NULL; }
  if ( fBz ) { delete fBz; fBz = NULL; }
}
// ------------------------------------------------------------------------  



// -----   Read field map from ASCII file (private)   ---------------------
void PndFieldMap::ReadAsciiFile(const char* fileName) {

  Double_t bx=0., by=0., bz=0.;
  Double_t  xx, yy, zz;
  // Open file
  cout << "-I- PndFieldMap: Reading field map from ASCII file " 
       << fileName << endl;
  ifstream mapFile(fileName);
  if ( ! mapFile.is_open() ) {
    cerr << "-E- PndFieldMap:ReadAsciiFile: Could not open file! " << endl;
    Fatal("ReadAsciiFile","Could not open file");
  }

  // Read map type
  TString type;
  mapFile >> type;

  Int_t iType = 0;
  if ( type == "nosym" ) iType = 1;
  if ( type == "Solenoid") iType = 2;
  if ( type == "Dipole"  ) iType = 3;
  if ( type == "Trans"  ) iType = 4;
  if ( fType != iType ) {
    cout << "-E- PndFieldMap::ReadAsciiFile: Incompatible map types!"
	 << endl;
    cout << "    Field map is of type " << fType 
	 << " but map on file is of type " << iType << endl;
    Fatal("ReadAsciiFile","Incompatible map types");
  }
  // Read Units
  TString unit;
  mapFile >> unit;
  if ( unit == "G" ) funit = 0.001;
  else if ( unit == "T"  ) funit = 10.0;
  else if ( unit == "kG"  ) funit=1.0;
  else {
    cout << "-E- FieldMap::ReadAsciiFile: No units!"
	 << endl;
        Fatal("ReadAsciiFile","No units defined");
  }


  // Read grid parameters
 
  mapFile >>fXmin >> fXmax >> fNx;
  mapFile >>fYmin >> fYmax >> fNy;
  mapFile >>fZmin >> fZmax >> fNz;
  fXstep = ( fXmax - fXmin ) / Double_t( fNx - 1 );
  fYstep = ( fYmax - fYmin ) / Double_t( fNy - 1 );
  fZstep = ( fZmax - fZmin ) / Double_t( fNz - 1 );
  
  // Create field arrays
  fBx = new TArrayF(fNx * fNy * fNz);
  fBy = new TArrayF(fNx * fNy * fNz);
  fBz = new TArrayF(fNx * fNy * fNz);

  // Read the field values
  Double_t factor = fScale * funit;   // Factor 1/1000 for G -> kG
  cout << right;
  Int_t nTot = fNx * fNy * fNz;
  cout << "-I- PndFieldMap: " << nTot << " entries to read... " 
       << setw(3) << 0 << " % ";
  Int_t index = 0;
  div_t modul;
  Int_t iDiv = TMath::Nint(nTot/100.);
  for (Int_t ix=0; ix<fNx; ix++) {
    for (Int_t iy = 0; iy<fNy; iy++) {
      for (Int_t iz = 0; iz<fNz; iz++) {
	if (! mapFile.good()) cerr << "-E- PndFieldMap::ReadAsciiFile: "
				   << "I/O Error at " << ix << " "
				   << iy << " " << iz << endl;
	index = ix*fNy*fNz + iy*fNz + iz;
	if (iDiv!=0)
	  {
	    modul = div(index,iDiv);
	    if ( modul.rem == 0 ) {
	      Double_t perc = TMath::Nint(100.*index/nTot);
	      cout << "\b\b\b\b\b\b" << setw(3) << perc << " % " << flush;
	    }
	  }
	//mapFile >> xx>>yy>>zz>>  bx >> by >> bz ;
	mapFile >>  bx >> by >> bz ;
	//cout  << " x= " <<xx <<" y= " << yy<<" z= " << zz<<" bx= " <<  bx <<" by= " <<by <<" bz= " << bz<< endl;
	fBx->AddAt(factor*bx, index);
	fBy->AddAt(factor*by, index);
	fBz->AddAt(factor*bz, index);
	if ( mapFile.eof() ) {
	  cerr << endl << "-E- PndFieldMap::ReadAsciiFile: EOF"
	       << " reached at " << ix << " " << iy << " " << iz << endl;
	  mapFile.close();
	  break;
	}
      }   // z-Loop
    }     // y-Loop0)
  }       // x-Loop

  cout << "   " << index+1 << " read" << endl;

  mapFile.close();

}
// ------------------------------------------------------------------------



// -------------   Read field map from ROOT file (private)  ---------------
void PndFieldMap::ReadRootFile(const char* fileName, 
			       const char* mapName) {

  // Store gFile pointer
  TFile* oldFile = gFile;

  // Open root file
  gLogger->Info(MESSAGE_ORIGIN, "PndFieldMap: Reading field map from ROOT file  %s ",fileName); 
  TFile* file = new TFile(fileName, "READ");		
  if (file->IsZombie()) {
    gLogger->Error(MESSAGE_ORIGIN, "-E- PndFieldMap::ReadRootfile: Cannot read from file! ");
    Fatal("ReadRootFile","Cannot read from file");
  }

  // Get the field data object
  PndFieldMapData* data = NULL;
  file->GetObject(mapName, data);
  if ( ! data ) {
     gLogger->Error(MESSAGE_ORIGIN,"PndFieldMap::ReadRootFile: data object %s not found in file! ", fileName);
     exit(-1);
  }

  // Get the field parameters
  SetField(data);

  // Close the root file and delete the data object
  file->Close();
  delete data;
  delete file;	
  if ( oldFile ) oldFile->cd();

}
// ------------------------------------------------------------------------



// ------------   Set field parameters and data (private)  ----------------
void PndFieldMap::SetField(const PndFieldMapData* data) {

  // Check compatibility
  if ( data->GetType() != fType ) {
    gLogger->Error(MESSAGE_ORIGIN,"PndFieldMap::SetField: Incompatible map types Field map is of type %s \n but map on file is of type %s ",fType,data->GetType());
    Fatal("SetField","Incompatible map types");
  }
  
  
  fXmin = data->GetXmin();
  fYmin = data->GetYmin();
  fZmin = data->GetZmin();
  fXmax = data->GetXmax();
  fYmax = data->GetYmax();
  fZmax = data->GetZmax();
  fNx = data->GetNx();
  fNy = data->GetNy();
  fNz = data->GetNz();
  fXstep = ( fXmax - fXmin ) / Double_t( fNx - 1 );
  fYstep = ( fYmax - fYmin ) / Double_t( fNy - 1 );
  fZstep = ( fZmax - fZmin ) / Double_t( fNz - 1 );
  if ( fBx ) delete fBx;
  if ( fBy ) delete fBy;
  if ( fBz ) delete fBz;
  fBx = new TArrayF(*(data->GetBx()));
  fBy = new TArrayF(*(data->GetBy()));
  fBz = new TArrayF(*(data->GetBz()));

  // Scale and convert from G(or T) to kG
  Double_t factor = fScale * funit;
  Int_t index = 0;
  for (Int_t ix=0; ix<fNx; ix++) {
    for (Int_t iy=0; iy<fNy; iy++) {
      for (Int_t iz=0; iz<fNz; iz++) {
	index = ix*fNy*fNz + iy*fNz + iz;
	if ( fBx ) (*fBx)[index] = (*fBx)[index] * factor;
	if ( fBy ) (*fBy)[index] = (*fBy)[index] * factor;
	if ( fBz ) (*fBz)[index] = (*fBz)[index] * factor;
      }
    }
  }

}
// ------------------------------------------------------------------------  



// ------------   Interpolation in a grid cell (private)  -----------------
Double_t PndFieldMap::Interpolate(Double_t dx, Double_t dy, Double_t dz) {

  // Interpolate in x coordinate
  fHb[0][0] = fHa[0][0][0] + ( fHa[1][0][0]-fHa[0][0][0] ) * dx;
  fHb[1][0] = fHa[0][1][0] + ( fHa[1][1][0]-fHa[0][1][0] ) * dx;
  fHb[0][1] = fHa[0][0][1] + ( fHa[1][0][1]-fHa[0][0][1] ) * dx;
  fHb[1][1] = fHa[0][1][1] + ( fHa[1][1][1]-fHa[0][1][1] ) * dx;

  // Interpolate in y coordinate
  fHc[0] = fHb[0][0] + ( fHb[1][0] - fHb[0][0] ) * dy;
  fHc[1] = fHb[0][1] + ( fHb[1][1] - fHb[0][1] ) * dy;

  // Interpolate in z coordinate
  return fHc[0] + ( fHc[1] - fHc[0] ) * dz;

}
// ------------------------------------------------------------------------



ClassImp(PndFieldMap)
