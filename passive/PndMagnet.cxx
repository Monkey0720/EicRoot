/* Generated by Together */

#include "PndMagnet.h"
#include "FairGeoLoader.h"
#include "FairGeoInterface.h"
#include "PndGeoMagnet.h"
#include "FairGeoRootBuilder.h"
#include "FairRuntimeDb.h"
#include "PndGeoPassivePar.h"
#include "TObjArray.h"
#include "FairRun.h"
#include "FairGeoVolume.h"
#include "FairGeoNode.h"

PndMagnet::~PndMagnet()
{
}
PndMagnet::PndMagnet()
{
}

PndMagnet::PndMagnet(const char * name, const char *Title)
  : FairModule(name ,Title)
{
}

void PndMagnet::ConstructGeometry(){
 
  TString fileName=GetGeometryFileName();
  if (fileName.EndsWith(".geo")) {
      ConstructASCIIGeometry();
  } else if(fileName.EndsWith(".root")) {
      ConstructRootGeometry();
  } else {
      std::cout<< "Geometry format not supported " <<std::endl;
  }
}

Bool_t PndMagnet::CheckIfSensitive(std::string name){
	// just to get rid of the warrning during run, not need this is a passive element! 
	return kFALSE;
}

void PndMagnet::ConstructASCIIGeometry(){
	FairGeoLoader *loader=FairGeoLoader::Instance();
	FairGeoInterface *GeoInterface =loader->getGeoInterface();
	PndGeoMagnet *MGeo=new PndGeoMagnet();
	MGeo->setGeomFile(GetGeometryFileName());
	GeoInterface->addGeoModule(MGeo);
	Bool_t rc = GeoInterface->readSet(MGeo);
	if ( rc ) MGeo->create(loader->getGeoBuilder());

        TList* volList = MGeo->getListOfVolumes();
        // store geo parameter
        FairRun *fRun = FairRun::Instance();
        FairRuntimeDb *rtdb= FairRun::Instance()->GetRuntimeDb();
        PndGeoPassivePar* par=(PndGeoPassivePar*)(rtdb->getContainer("PndGeoPassivePar"));
        TObjArray *fSensNodes = par->GetGeoSensitiveNodes();
        TObjArray *fPassNodes = par->GetGeoPassiveNodes();

        TListIter iter(volList);
        FairGeoNode* node   = NULL;
        FairGeoVolume *aVol=NULL;

        while( (node = (FairGeoNode*)iter.Next()) ) {
            aVol = dynamic_cast<FairGeoVolume*> ( node );
            if ( node->isSensitive()  ) {
                fSensNodes->AddLast( aVol );
            }else{
                fPassNodes->AddLast( aVol );
            }
        }
	ProcessNodes( volList );
        par->setChanged();
        par->setInputVersion(fRun->GetRunId(),1);	
}

ClassImp(PndMagnet)














