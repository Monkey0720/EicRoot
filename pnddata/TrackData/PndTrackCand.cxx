//-----------------------------------------------------------
// File and Version Information:
// $Id$
//
// Description:
//      Implementation of class PndTrackCand
//      see PndTrackCand.hh for details
//
// Environment:
//      Software developed for the PANDA Detector at FAIR.
//
// Author List:
//      Tobias Stockmanns (IKP - Juelich) during the Panda Meeting 03/09
//
//
//-----------------------------------------------------------

// Panda Headers ----------------------

// This Class' Header ------------------
#include "PndTrackCand.h"
#include "FairRootManager.h"
#include "FairEventHeader.h"

#include <algorithm>
#include "math.h"

ClassImp(PndTrackCand);

PndTrackCand::PndTrackCand():sorted(false), fMcTrackId(-1),/*fQoverPseed(0.)*/fChargeSeed(0.0),fVerbose(0){}

PndTrackCand::~PndTrackCand(){}

void
PndTrackCand::AddHit(UInt_t detId, UInt_t hitId, Double_t rho)
{
	fHitId.push_back(PndTrackCandHit(detId, hitId, rho));
	sorted = false;
	AddLink(FairLink(detId, hitId));
//	CalcTimeStamp();
}

void PndTrackCand::AddHit(TString branchName, UInt_t hitId, Double_t rho)
{
	FairRootManager* ioman = FairRootManager::Instance();
	UInt_t detId = ioman->GetBranchId(branchName);
	AddHit(detId, hitId, rho);
}

void PndTrackCand::AddHit(FairLink link, Double_t rho)
{
	fHitId.push_back(PndTrackCandHit(link.GetType(), link.GetIndex(), rho));
	sorted = false;
	AddLink(link);
}


void PndTrackCand::ResetLinks()
{
  fHitId.clear();
  FairMultiLinkedData::ResetLinks();
}

int PndTrackCand::HitInTrack(UInt_t detId, UInt_t hitId)
{
	PndTrackCandHit test(detId, hitId, 0.);
	for (UInt_t i = 0; i < fHitId.size(); i++){
		if(fHitId[i] == test)
			return i;
	}
	return -1;
}

void PndTrackCand::DeleteHit(UInt_t detId, UInt_t hitId)
{
	int ind = HitInTrack(detId, hitId);
	fHitId.erase(fHitId.begin()+ind);

	//Int_t det = detId;
	//Int_t hit = hitId;
	//DeleteLink(det, hit);
}

UInt_t PndTrackCand::GetNHitsDet(UInt_t detId)
{
  // Function to count the number of hits from the same detId
  Int_t detCounts = 0;
  
  for (Int_t ihit = 0; ihit<fHitId.size(); ihit++)
    {
      PndTrackCandHit candhit = GetSortedHit(ihit);
      if (candhit.GetDetId() == detId) detCounts++;
    }
  
  return detCounts;
}

void PndTrackCand::Sort()
{
	std::sort(fHitId.begin(), fHitId.end());
	sorted = true;
}

std::vector<PndTrackCandHit> &PndTrackCand::_GetSortedHits()
{
	if (sorted == false)
		Sort();
	return fHitId;
}

void PndTrackCand::CalcTimeStamp()
{
	Double_t timestamp = 0;
	Double_t timestamperror = 0;
	Int_t counts = 0;
	for (int i = 0; i < GetNLinks(); i++){
		FairLink myLink = GetLink(i);
		Int_t type = myLink.GetType();
		
		if (fVerbose > 1){
			std::cout << "Links: " << myLink << std::endl;
		}
		
		if (type > -1){
			TString branchName = FairRootManager::Instance()->GetBranchName(type);
			//std::cout << "BranchName: " << branchName.Data() << std::endl;

			TClonesArray* myArray = (TClonesArray*)FairRootManager::Instance()->GetObject(branchName);
			if (myArray > 0){
				FairTimeStamp* myData = (FairTimeStamp*)(FairRootManager::Instance()->GetCloneOfLinkData(myLink));
				if (myData > 0){
					Double_t var = myData->GetTimeStampError() * myData->GetTimeStampError();
					timestamp += myData->GetTimeStamp()/var;
					timestamperror += 1/var;
					counts++;
					delete myData;
				}
				else {
					std::cout << "Data not found: " << FairRootManager::Instance()->GetBranchName(myLink.GetType()) << "/" << myLink.GetIndex() << std::endl;
				}
			}
			else {
	//			std::cout << "Array not found: " << ioman->GetBranchName(myLink.GetType()) << std::endl;
			}
		}
	}
	if (timestamperror > 0){
		//std::cout << "TrackTimeStamp: " << timestamp/timestamperror << " +/- " << sqrt(timestamperror/counts) << " counts " << counts << std::endl;
		SetTimeStamp(timestamp/timestamperror);
		SetTimeStampError(sqrt(timestamperror/counts));
	}
}

bool PndTrackCand::operator== (const PndTrackCand& rhs){
  if(rhs.fHitId.size()!=fHitId.size()) return false;
  for(unsigned int i=0;i<fHitId.size();++i){
    if(fHitId.at(i) != rhs.fHitId.at(i) ) return false;
  }
  return true;
}


void PndTrackCand::Print(){
  std::cout << "=========== PndTrackCand::Print() ==========" << std::endl;
  if(fMcTrackId>=0) std::cout << "McTrackId=" << fMcTrackId << std::endl;
  std::cout << "seed values for pos,direction, and q/p: " << std::endl;
  fPosSeed.Print();
  fMomSeed.Print();
  //std::cout << "q/p=" << fQoverPseed << std::endl;
  for(unsigned int i=0;i<fHitId.size();++i){
    fHitId.at(i).Print();
  }
}
