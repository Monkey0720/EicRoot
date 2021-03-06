
void simulation(Int_t nEvents = 1000)
{
  // Load basic libraries;
  gROOT->Macro("$VMCWORKDIR/gconfig/rootlogon.C");

  // Create the simulation run manager; 
  EicRunSim *fRun = new EicRunSim("TGeant3");

  //fRun->SetCaveFileName("cave-120m-vacuum.geo");
  fRun->SetCaveFileName("cave-120m-thin-air.geo");
  fRun->SetOutputFile("simulation.root");

  // Well, do not need secondaries in this simulation; 
  fRun->SuppressSecondaries();

  fRun->AddModule(new EicTpc (                    "TPC/tpc-v01.0-ns.root"));  
  fRun->AddModule(new EicMaps(           "VST",   "../geometry/vst-v02.0-ns.root", qVST));

  // Relevant part of the vacuum system;
#if 1//_RETURN_BACK_
  {
    fRun->AddModule(new EicDummyDetector("VP.CENTER",        "pCDR-2018/geometry/vacuum.system/vp.center.root"));
    fRun->AddModule(new EicDummyDetector("VP.H-GOING",       "pCDR-2018/geometry/vacuum.system/vp.h-going.root"));

    fRun->AddModule(new EicDummyDetector("VP.H-GOING.GHOST", "pCDR-2018/geometry/vacuum.system/vp.h-going.ghost.root"));
  }
  {
    unsigned id[] = {/*103*/106, 116/*, 188*/}, dim = sizeof(id)/sizeof(id[0]);
    for(unsigned part=0; part<dim; part++) {
      unsigned qid = id[part];
      char dname[128], fname[128];

      sprintf(dname, "VACUUM-%02d", qid); 
      sprintf(fname, "../geometry/vacuum.system/00354-000%03d-step.stl", qid);
      
      // FIXME: aluminum or stainless steel?;
      EicCadFile *cad = new EicCadFile(dname, fname, qid == 103 ? "beryllium" : "AA2219");
      cad->config()->SetUnits(eic::mm);
      cad->SwapXY(); 
      if (qid == 103 || qid == 106 || qid == 116) cad->SetKillerFlag();
      //if (qid == 188) cad->SetKillerFlag();
      fRun->AddModule(cad);
    } //for part
  }

  // B0 magnet geometry;
  {
    {
      EicCadFile *cad = new EicCadFile("B0-YOKE", "../geometry/b0magnet/yoke.mphtxt", "iron", kBlue);

      cad->config()->SetUnits(eic::m);
      cad->SetExtraStlTranslation(0.0, 0.0, 560.0);
      cad->CreateStlMirrorCopyXY();
      cad->CreateStlMirrorCopyXZ();
      fRun->AddModule(cad);
    }
    {
      EicCadFile *cad = new EicCadFile("B0-COIL", "../geometry/b0magnet/coil.mphtxt", "copper", kRed);

      cad->config()->SetUnits(eic::m);
      cad->SetExtraStlTranslation(0.0, 0.0, 560.0);
      cad->CreateStlMirrorCopyXY();
      cad->CreateStlMirrorCopyXZ();
      fRun->AddModule(cad);
    }
    // NB: may want to include HQE1 from "simple" magnetic elements instead?;
    {
      EicCadFile *cad = new EicCadFile("B0-COIL2", "../geometry/b0magnet/coil2.mphtxt", "copper");

      cad->config()->SetUnits(eic::m);
      cad->SetExtraStlTranslation(0.0, 0.0, 560.0);
      //cad->CreateStlMirrorCopyXY();
      //cad->CreateStlMirrorCopyXZ();
      //fRun->AddModule(cad);
    }
    {
      EicCadFile *cad = new EicCadFile("B0-SHIELDING", "../geometry/b0magnet/shielding.mphtxt", "iron");

      cad->config()->SetUnits(eic::m);
      cad->SetExtraStlTranslation(0.0, 0.0, 560.0);
      //cad->CreateStlMirrorCopy();
      //fRun->AddModule(cad);
    }
    {
      // Really copper?;
      EicCadFile *cad = new EicCadFile("B0-QUAD", "../geometry/b0magnet/quad.mphtxt", "copper");

      cad->config()->SetUnits(eic::m);
      cad->SetExtraStlTranslation(0.0, 0.0, 560.0);
      //cad->CreateStlMirrorCopy();
      //fRun->AddModule(cad);
    }
  } 
#endif

  // Hadron-going direction detectors;
  fRun->AddModule(new EicDetector("IPPT",      "../geometry/ip-point.root",  qDUMMY, qMergeStepsInOneHit));
  fRun->AddModule(new EicDetector("B0TRACKER", "../geometry/b0tracker.root", qDUMMY, qMergeStepsInOneHit));
  fRun->AddModule(new EicDetector("RP",        "../geometry/rp.root",        qDUMMY, qMergeStepsInOneHit));
  //{
  //EicDetector *zdc = new EicDetector("ZDC",  "../geometry/zdc.root",qDUMMY, qMergeStepsInOneHit);
  //zdc->AddKillerVolume("ZdcBox");
  //fRun->AddModule(zdc);
  //}

  // Event generator;
#if 1
  {
    // Box generator; 
    int PDG = 2212;     
    EicBoxGenerator* boxGen = new EicBoxGenerator(PDG); 

    boxGen->SetMomentum(275.);    
    boxGen->SetTheta(0.0);//Range(0.003 * TMath::RadToDeg(), 0.010 * TMath::RadToDeg()); //boxGen->SetPhi(45.0);
    //boxGen->SetTheta(0.003 * TMath::RadToDeg()); //boxGen->SetPhi(45.0);
    //boxGen->SetTheta(0.013 * TMath::RadToDeg()); //boxGen->SetPhi(45.0);
    
    boxGen->SetVertex(0.000, 0.000, -1.0); // may want to offset in Z in order to get IPPT "hit";  
    //boxGen->SetVertexSmearing(0.010, 0.002, 0.0); // H:100um and V:20um for now; 

    boxGen->SetNaiveHorizontalBeamRotation(0.022);
    fRun->AddGenerator(boxGen);
  }
#else
  {
    // Physics generator;
    TString evFile = "../../data/asc_5x41_dvcs-1M-lines.out";
    //TString evFile = "../../data/ePb_18x110_Q2_1_10_y_0.01_0.95_tau_7_noquench_kt=ptfrag=0.32_Shd3_ShdFac=1.32_Jpsidiffnodecay_fixpfUS3_seqnp_40k.a.root";
    //TString evFile = "../../data/asc_10x100_dvcs-1M-lines.out";

    EicEventGenerator* evtGen = new EicEventGenerator(evFile.Data());

    // Select primary protons only; ignore all the rest;
    evtGen->SelectPdgCode(2212);
    evtGen->SelectLeadingParticle();
    evtGen->SetNaiveHorizontalBeamRotation(0.022);

    fRun->AddGenerator(evtGen);
  }
#endif

  // Magnetic field; NB: rescale properly!;
  {
    EicMagneticField *fField = new EicMagneticField();

    fField->AddBeamLineElementGrads("IR/pCDR-2018/madx/H.H-GOING",275./275., kBlue);
    //fField->AddBeamLineElementGrads("IR/pCDR-2018/madx/H.H-GOING", 100./275., kBlue);
    //fField->AddBeamLineElementGrads("IR/pCDR-2018/madx/H.H-GOING", 275./275., kBlue);
    fField->SuppressYokeCreation("YO5_HB0");    

    fField->AddBeamLineElementGrads("IR/pCDR-2018/madx/E.H-GOING",  5./10.,  kGreen);
    //fField->AddBeamLineElementGrads("IR/pCDR-2018/madx/E.H-GOING",  10./10.,  kGreen);

    fField->CreateYokeVolumes(kTRUE);

    fRun->SetField(fField);
  }    

  // Initialize and run the simulation; exit at the end;
  fRun->Run(nEvents);
} // simulation()
