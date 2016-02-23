//
// Pibero Djawotho <pibero@tamu.edu>
// Texas A&M University
// 4 Dec 2011
//

void RunJetFinder2009emb_ue(int nevents = 1e6,
			 const char* mudstfile = "/gpfs01/star/scratch/gdwebb/Embedding_inclu/10103041/pt9_11_10103041_6.MuDst.root",
			 const char* geantfile = "/gpfs01/star/scratch/gdwebb/Embedding_inclu/10103041/pt9_11_10103041_6.geant.root",
		
			 const char* jetfile   = "pt9_11_10103041_6.jets.root",
			 const char* skimfile  = "pt9_11_10103041_6.skim.root",
			 const char* uefile  = "pt9_11_10103041_6.ue.root",
			 bool useL2 = false)
{
  cout << "Read MuDst file:\t" << mudstfile << endl;
  cout << "Read geant file:\t" << geantfile << endl;
  cout << "Write jet file:\t" << jetfile << endl;
  cout << "Write skim file:\t" << skimfile << endl;
  cout << "Write ue file:\t" << uefile << endl;

  gROOT->Macro("loadMuDst.C");
  gROOT->Macro("LoadLogger.C");

  gSystem->Load("StDetectorDbMaker");
  gSystem->Load("StTpcDb");
  gSystem->Load("StDbUtilities");
  gSystem->Load("StMcEvent");
  gSystem->Load("StMcEventMaker");
  gSystem->Load("StDaqLib");
  gSystem->Load("StEmcRawMaker");
  gSystem->Load("StEmcADCtoEMaker");
  gSystem->Load("StPreEclMaker");
  gSystem->Load("StEmcSimulatorMaker");
  gSystem->Load("StDbBroker");
  gSystem->Load("St_db_Maker");
  gSystem->Load("StEEmcUtil");
  gSystem->Load("StEEmcDbMaker");
  gSystem->Load("StSpinDbMaker");
  gSystem->Load("StEmcTriggerMaker");
  gSystem->Load("StTriggerUtilities");
  gSystem->Load("StMCAsymMaker");
  gSystem->Load("StRandomSelector");
  gSystem->Load("libfastjet.so");
  gSystem->Load("libsiscone.so");
  gSystem->Load("libsiscone_spherical.so");
  gSystem->Load("libfastjetplugins.so");
  gSystem->Load("StJetFinder");
  gSystem->Load("StJetSkimEvent");
  gSystem->Load("StJets");
  gSystem->Load("StJetEvent");
  gSystem->Load("StUeEvent");
  gSystem->Load("StJetMaker");
  gSystem->Load("StEEmcSimulatorMaker");

  // Create chain
  StChain* chain = new StChain;

  // I/O maker
  StIOMaker* ioMaker = new StIOMaker;
  ioMaker->SetFile(geantfile);
  ioMaker->SetIOMode("r");
  ioMaker->SetBranch("*",0,"0");             // Deactivate all branches
  ioMaker->SetBranch("geantBranch",0,"r");   // Activate geant Branch

  // StMcEvent maker
  StMcEventMaker* mcEventMaker = new StMcEventMaker;
  mcEventMaker->doPrintEventInfo = false;
  mcEventMaker->doPrintMemoryInfo = false;

  // MuDst reader
  StMuDstMaker* muDstMaker = new StMuDstMaker(0,0,"",mudstfile,"",100000,"MuDst");

  // MuDst DB
  StMuDbReader* muDstDb = StMuDbReader::instance();

  // star database
  St_db_Maker* starDb = new St_db_Maker("StarDb","MySQL:StarDb");

  // Endcap database
  StEEmcDbMaker* eemcDb = new StEEmcDbMaker;

  // Barrel ADC to energy maker
  StEmcADCtoEMaker* adc2e = new StEmcADCtoEMaker;
  adc2e->saveAllStEvent(true);

  // Trigger simulator
  // -- StL2_2009EmulatorMaker must run before StTriggerSimuMaker?
  StL2_2009EmulatorMaker* simL2Mk = 0;
  if (useL2) {
    simL2Mk = new StL2_2009EmulatorMaker;
    simL2Mk->setSetupPath("/star/u/pibero/public/StarTrigSimuSetup/");
    simL2Mk->setOutPath("/star/institutions/uky/gdwebb/2009/500EmbedJets/L2/");
  }
  StTriggerSimuMaker* simuTrig = new StTriggerSimuMaker;
  // Pibero, I changed the next line from 2 to 1.  
  simuTrig->useOnlineDB();
  simuTrig->setMC(2); // 0=data, 1=simulation, 2=embedding
  simuTrig->useBemc();
  simuTrig->useEemc();
  simuTrig->bemc->setConfig(StBemcTriggerSimu::kOffline);
  if (useL2) simuTrig->useL2(simL2Mk);
  
  // Set trigger thresholds using run 10102039
  simuTrig->setBarrelJetPatchTh(0,32);
  simuTrig->setBarrelJetPatchTh(1,40);
  simuTrig->setBarrelJetPatchTh(2,60);
  
  simuTrig->setOverlapJetPatchTh(0,32);
  simuTrig->setOverlapJetPatchTh(1,40);
  simuTrig->setOverlapJetPatchTh(2,60);
  
  simuTrig->setEndcapJetPatchTh(0,32);
  simuTrig->setEndcapJetPatchTh(1,40);
  simuTrig->setEndcapJetPatchTh(2,60);

  simuTrig->setBarrelHighTowerTh(0,-1);
  simuTrig->setBarrelHighTowerTh(1,-1);
  simuTrig->setBarrelHighTowerTh(2,25);
  simuTrig->setBarrelHighTowerTh(3,31);
  
  simuTrig->setEndcapHighTowerTh(0,25);
  simuTrig->setEndcapHighTowerTh(1,31);
  
  // Get Pythia record
  StMCAsymMaker* asym = new StMCAsymMaker;

  // Skim event maker
  StJetSkimEventMaker* skimEventMaker = new StJetSkimEventMaker("StJetSkimEventMaker",muDstMaker,skimfile);
  skimEventMaker->addSimuTrigger(230531); // BHT3
  skimEventMaker->addSimuTrigger(230410); // JP1
  skimEventMaker->addSimuTrigger(230411); // JP2
  skimEventMaker->addSimuTrigger(230420); // AJP

  // Jet maker
  StJetMaker2009* jetmaker = new StJetMaker2009;
  jetmaker->setJetFile(jetfile);

  // UE maker
  StUEMaker2009* uemaker = new StUEMaker2009;
  uemaker->setUeFile(uefile);
  
  //------------------------------------------------------------------------------------

  // Set analysis cuts for 12-point branch
  StAnaPars* anapars12 = new StAnaPars;
  anapars12->useTpc  = true;
  anapars12->useBemc = true;
  anapars12->useEemc = false;
  anapars12->randomSelectorProb = 1.00;
  
  // The classes available for correcting tower energy for tracks are:
  // 1. StjTowerEnergyCorrectionForTracksMip
  // 2. StjTowerEnergyCorrectionForTracksFraction
  // 3. StjTowerEnergyCorrectionForTracksNull (default: no correction
  
  //The classes available for shifting track and tower parameters prior to jet reconstruction are:
  // 1. StjTrackPtFraction
  // 2. StjTowerEnergyFraction
  //    The input parameter for is the fraction which you want to increase or decrease the track/tower quantity. 
  //    i.e. If you want to decrease the track pT by 5%, you should put in -0.05 as the input parameter for StjTrackPtFraction
  
  anapars12->setTrackShift(new StjTrackPtFraction(0.0));
  anapars12->setTowerShift(new StjTowerEnergyFraction(0.0));
  anapars12->setTowerEnergyCorrection(new StjTowerEnergyCorrectionForTracksFraction(1.00));
  
  // TPC cuts
  anapars12->addTpcCut(new StjTrackCutFlag(0));
  anapars12->addTpcCut(new StjTrackCutNHits(12));
  anapars12->addTpcCut(new StjTrackCutPossibleHitRatio(0.51));
  anapars12->addTpcCut(new StjTrackCutDca(3));
  anapars12->addTpcCut(new StjTrackCutTdcaPtDependent);
  anapars12->addTpcCut(new StjTrackCutPt(0.2,200));
  anapars12->addTpcCut(new StjTrackCutEta(-2.5,2.5));
  anapars12->addTpcCut(new StjTrackCutLastPoint(125));

  // BEMC cuts
  anapars12->addBemcCut(new StjTowerEnergyCutBemcStatus(1));
  anapars12->addBemcCut(new StjTowerEnergyCutAdc(4,3));	// ADC-ped>4 AND ADC-ped>3*RMS
  anapars12->addBemcCut(new StjTowerEnergyCutEt(0.2));

  // EEMC cuts
  anapars12->addEemcCut(new StjTowerEnergyCutBemcStatus(1));
  anapars12->addEemcCut(new StjTowerEnergyCutAdc(4,3));	// ADC-ped>4 AND ADC-ped>3*RMS
  anapars12->addEemcCut(new StjTowerEnergyCutEt(0.2));

  // Jet cuts
  anapars12->addJetCut(new StProtoJetCutPt(5,200));
  anapars12->addJetCut(new StProtoJetCutEta(-100,100));

// _________________Toward Region_____________________
 // Set analysis cuts for 12-point branch
  StAnaPars* anapars12_tow = new StAnaPars;
  anapars12_tow->useTpc  = true;
  anapars12_tow->useBemc = true;
  anapars12_tow->useEemc = false;

  anapars12_tow->setTowerEnergyCorrection(new StjTowerEnergyCorrectionForTracksFraction(1.00));
  anapars12_tow->setTrackShift(new StjTrackPtFraction(0.0));
  anapars12_tow->setTowerShift(new StjTowerEnergyFraction(0.0));
  
  // TPC cuts
  anapars12_tow->addTpcCut(new StjTrackCutFlag(0));
  anapars12_tow->addTpcCut(new StjTrackCutNHits(12));
  anapars12_tow->addTpcCut(new StjTrackCutPossibleHitRatio(0.51));
  anapars12_tow->addTpcCut(new StjTrackCutDca(3));
  anapars12_tow->addTpcCut(new StjTrackCutTdcaPtDependent);
  anapars12_tow->addTpcCut(new StjTrackCutPt(0.2,200));
  anapars12_tow->addTpcCut(new StjTrackCutEta(-2.5,2.5));
  anapars12_tow->addTpcCut(new StjTrackCutLastPoint(125));
  
  // BEMC cuts
  anapars12_tow->addBemcCut(new StjTowerEnergyCutBemcStatus(1));
  anapars12_tow->addBemcCut(new StjTowerEnergyCutAdc(4,3));	// ADC-ped>4 AND ADC-ped>3*RMS
  anapars12_tow->addBemcCut(new StjTowerEnergyCutEt(0.2));
  
  // EEMC cuts
  anapars12_tow->addEemcCut(new StjTowerEnergyCutBemcStatus(1));
  anapars12_tow->addEemcCut(new StjTowerEnergyCutAdc(4,3));	// ADC-ped>4 AND ADC-ped>3*RMS
  anapars12_tow->addEemcCut(new StjTowerEnergyCutEt(0.2));
  
  // Jet cuts
  anapars12_tow->addJetCut(new StProtoJetCutPt(5,200));
  anapars12_tow->addJetCut(new StProtoJetCutEta(-100,100));
  //Region Cut
  anapars12_tow->setTrackRegion(new StjTrackRegion(60.0,-60.0,1.0));
  anapars12_tow->setTowerRegion(new StjTowerRegion(60.0,-60.0,1.0));
  
  //_____________________END TOWARDS_______________________________
  
  //*********************AWAY REGION**************************
  // Set analysis cuts for 12-point branch
  StAnaPars* anapars12_away = new StAnaPars;
  anapars12_away->useTpc  = true;
  anapars12_away->useBemc = true;
  anapars12_away->useEemc = false;
  
  anapars12_away->setTowerEnergyCorrection(new StjTowerEnergyCorrectionForTracksFraction(1.00));
  anapars12_away->setTrackShift(new StjTrackPtFraction(0.0));
  anapars12_away->setTowerShift(new StjTowerEnergyFraction(0.0));
  
  // TPC cuts
  anapars12_away->addTpcCut(new StjTrackCutFlag(0));
  anapars12_away->addTpcCut(new StjTrackCutNHits(12));
  anapars12_away->addTpcCut(new StjTrackCutPossibleHitRatio(0.51));
  anapars12_away->addTpcCut(new StjTrackCutDca(3));
  anapars12_away->addTpcCut(new StjTrackCutTdcaPtDependent);
  anapars12_away->addTpcCut(new StjTrackCutPt(0.2,200));
  anapars12_away->addTpcCut(new StjTrackCutEta(-2.5,2.5));
  anapars12_away->addTpcCut(new StjTrackCutLastPoint(125));

  // BEMC cuts
  anapars12_away->addBemcCut(new StjTowerEnergyCutBemcStatus(1));
  anapars12_away->addBemcCut(new StjTowerEnergyCutAdc(4,3));	// ADC-ped>4 AND ADC-ped>3*RMS
  anapars12_away->addBemcCut(new StjTowerEnergyCutEt(0.2));

  // EEMC cuts
  anapars12_away->addEemcCut(new StjTowerEnergyCutBemcStatus(1));
  anapars12_away->addEemcCut(new StjTowerEnergyCutAdc(4,3));	// ADC-ped>4 AND ADC-ped>3*RMS
  anapars12_away->addEemcCut(new StjTowerEnergyCutEt(0.2));

  // Jet cuts
  anapars12_away->addJetCut(new StProtoJetCutPt(5,200));
  anapars12_away->addJetCut(new StProtoJetCutEta(-100,100));
  //Region Cut
  anapars12_away->setTrackRegion(new StjTrackRegion(120.0,-120.0,1.0));
  anapars12_away->setTowerRegion(new StjTowerRegion(120.0,-120.0,1.0));
  //*********************END AWAY****************************
  
  // **********************TRANS PLUS **********************
  // Set analysis cuts for 12-point branch
  StAnaPars* anapars12_transPlus = new StAnaPars;
  anapars12_transPlus->useTpc  = true;
  anapars12_transPlus->useBemc = true;
  anapars12_transPlus->useEemc = false;
  
  anapars12_transPlus->setTowerEnergyCorrection(new StjTowerEnergyCorrectionForTracksFraction(1.00));
  anapars12_transPlus->setTrackShift(new StjTrackPtFraction(0.0));
  anapars12_transPlus->setTowerShift(new StjTowerEnergyFraction(0.0));
  
  // TPC cuts
  anapars12_transPlus->addTpcCut(new StjTrackCutFlag(0));
  anapars12_transPlus->addTpcCut(new StjTrackCutNHits(12));
  anapars12_transPlus->addTpcCut(new StjTrackCutPossibleHitRatio(0.51));
  anapars12_transPlus->addTpcCut(new StjTrackCutDca(3));
  anapars12_transPlus->addTpcCut(new StjTrackCutTdcaPtDependent);
  anapars12_transPlus->addTpcCut(new StjTrackCutPt(0.2,200));
  anapars12_transPlus->addTpcCut(new StjTrackCutEta(-2.5,2.5));
  anapars12_transPlus->addTpcCut(new StjTrackCutLastPoint(125));

  // BEMC cuts
  anapars12_transPlus->addBemcCut(new StjTowerEnergyCutBemcStatus(1));
  anapars12_transPlus->addBemcCut(new StjTowerEnergyCutAdc(4,3));	// ADC-ped>4 AND ADC-ped>3*RMS
  anapars12_transPlus->addBemcCut(new StjTowerEnergyCutEt(0.2));

  // EEMC cuts
  anapars12_transPlus->addEemcCut(new StjTowerEnergyCutBemcStatus(1));
  anapars12_transPlus->addEemcCut(new StjTowerEnergyCutAdc(4,3));	// ADC-ped>4 AND ADC-ped>3*RMS
  anapars12_transPlus->addEemcCut(new StjTowerEnergyCutEt(0.2));

  // Jet cuts
  anapars12_transPlus->addJetCut(new StProtoJetCutPt(5,200));
  anapars12_transPlus->addJetCut(new StProtoJetCutEta(-100,100));
  //Region Cut
  anapars12_transPlus->setTrackRegion(new StjTrackRegion(120.0,60.0,1.0));
  anapars12_transPlus->setTowerRegion(new StjTowerRegion(120.0,60.0,1.0));
  //***********************END TRANS PLUS ********************

  // **********************TRANS MINUS **********************
 // Set analysis cuts for 12-point branch
  StAnaPars* anapars12_transMinus = new StAnaPars;
  anapars12_transMinus->useTpc  = true;
  anapars12_transMinus->useBemc = true;
  anapars12_transMinus->useEemc = false;

  anapars12_transMinus->setTowerEnergyCorrection(new StjTowerEnergyCorrectionForTracksFraction(1.00));
  anapars12_transMinus->setTrackShift(new StjTrackPtFraction(0.0));
  anapars12_transMinus->setTowerShift(new StjTowerEnergyFraction(0.0));
  
  // TPC cuts
  anapars12_transMinus->addTpcCut(new StjTrackCutFlag(0));
  anapars12_transMinus->addTpcCut(new StjTrackCutNHits(12));
  anapars12_transMinus->addTpcCut(new StjTrackCutPossibleHitRatio(0.51));
  anapars12_transMinus->addTpcCut(new StjTrackCutDca(3));
  anapars12_transMinus->addTpcCut(new StjTrackCutTdcaPtDependent);
  anapars12_transMinus->addTpcCut(new StjTrackCutPt(0.2,200));
  anapars12_transMinus->addTpcCut(new StjTrackCutEta(-2.5,2.5));
  anapars12_transMinus->addTpcCut(new StjTrackCutLastPoint(125));

  // BEMC cuts
  anapars12_transMinus->addBemcCut(new StjTowerEnergyCutBemcStatus(1));
  anapars12_transMinus->addBemcCut(new StjTowerEnergyCutAdc(4,3));	// ADC-ped>4 AND ADC-ped>3*RMS
  anapars12_transMinus->addBemcCut(new StjTowerEnergyCutEt(0.2));

  // EEMC cuts
  anapars12_transMinus->addEemcCut(new StjTowerEnergyCutBemcStatus(1));
  anapars12_transMinus->addEemcCut(new StjTowerEnergyCutAdc(4,3));	// ADC-ped>4 AND ADC-ped>3*RMS
  anapars12_transMinus->addEemcCut(new StjTowerEnergyCutEt(0.2));

  // Jet cuts
  anapars12_transMinus->addJetCut(new StProtoJetCutPt(5,200));
  anapars12_transMinus->addJetCut(new StProtoJetCutEta(-100,100));
  //Region Cut
  anapars12_transMinus->setTrackRegion(new StjTrackRegion(-60.0,-120.0,1.0));
  anapars12_transMinus->setTowerRegion(new StjTowerRegion(-60.0,-120.0,1.0));
  //***********************END TRANS MINUS ********************


  // -----------Set analysis cuts for particle jets branch---------------------
  StAnaPars* anaparsParticle = new StAnaPars;
  anaparsParticle->useMonteCarlo = true;
  // MC cuts
  anaparsParticle->addMcCut(new StjMCParticleCutStatus(1)); // final state particles
  // Jet cuts
  anaparsParticle->addJetCut(new StProtoJetCutPt(3,200));
  anaparsParticle->addJetCut(new StProtoJetCutEta(-100,100));
  
  StAnaPars* anaparsParticle_toward = new StAnaPars;
  anaparsParticle_toward->useMonteCarlo = true;
  // MC cuts
  anaparsParticle_toward->addMcCut(new StjMCParticleCutStatus(1)); // final state particles
  // Jet cuts
  anaparsParticle_toward->addJetCut(new StProtoJetCutPt(3,200));
  anaparsParticle_toward->addJetCut(new StProtoJetCutEta(-100,100));
  //Region Cut
  anaparsParticle_toward->setParticleRegion(new StjMCParticleRegion(60.0,-60.0,1.0));

  StAnaPars* anaparsParticle_away = new StAnaPars;
  anaparsParticle_away->useMonteCarlo = true;
  // MC cuts
  anaparsParticle_away->addMcCut(new StjMCParticleCutStatus(1)); // final state particles
  // Jet cuts
  anaparsParticle_away->addJetCut(new StProtoJetCutPt(3,200));
  anaparsParticle_away->addJetCut(new StProtoJetCutEta(-100,100));
  //Region Cut
  anaparsParticle_away->setParticleRegion(new StjMCParticleRegion(120.0,-120.0,1.0));

  StAnaPars* anaparsParticle_transPlus = new StAnaPars;
  anaparsParticle_transPlus->useMonteCarlo = true;
  // MC cuts
  anaparsParticle_transPlus->addMcCut(new StjMCParticleCutStatus(1)); // final state particles
  // Jet cuts
  anaparsParticle_transPlus->addJetCut(new StProtoJetCutPt(3,200));
  anaparsParticle_transPlus->addJetCut(new StProtoJetCutEta(-100,100));
  //Region Cut
  anaparsParticle_transPlus->setParticleRegion(new StjMCParticleRegion(120.0,60.0,1.0));

 StAnaPars* anaparsParticle_transMinus = new StAnaPars;
  anaparsParticle_transMinus->useMonteCarlo = true;
  // MC cuts
  anaparsParticle_transMinus->addMcCut(new StjMCParticleCutStatus(1)); // final state particles
  // Jet cuts
  anaparsParticle_transMinus->addJetCut(new StProtoJetCutPt(3,200));
  anaparsParticle_transMinus->addJetCut(new StProtoJetCutEta(-100,100));
  //Region Cut
  anaparsParticle_transMinus->setParticleRegion(new StjMCParticleRegion(-60.0,-120.0,1.0));

  //------------------------------------------------------------------------------------
  // Set analysis cuts for parton jets branch
  StAnaPars* anaparsParton = new StAnaPars;
  anaparsParton->useMonteCarlo = true;
  // MC cuts
  anaparsParton->addMcCut(new StjMCParticleCutParton);
  // Jet cuts
  anaparsParton->addJetCut(new StProtoJetCutPt(3,200));
  anaparsParton->addJetCut(new StProtoJetCutEta(-100,100));
  
  StAnaPars* anaparsParton_toward = new StAnaPars;
  anaparsParton_toward->useMonteCarlo = true;
  // MC cuts
  anaparsParton_toward->addMcCut(new StjMCParticleCutParton);
  // Jet cuts
  anaparsParton_toward->addJetCut(new StProtoJetCutPt(3,200));
  anaparsParton_toward->addJetCut(new StProtoJetCutEta(-100,100));
 //Region Cut
  anaparsParton_toward->setParticleRegion(new StjMCParticleRegion(60.0,-60.0,1.0));
  
  StAnaPars* anaparsParton_away = new StAnaPars;
  anaparsParton_away->useMonteCarlo = true;
  // MC cuts
  anaparsParton_away->addMcCut(new StjMCParticleCutParton);
  // Jet cuts
  anaparsParton_away->addJetCut(new StProtoJetCutPt(3,200));
  anaparsParton_away->addJetCut(new StProtoJetCutEta(-100,100));
 //Region Cut
  anaparsParton_away->setParticleRegion(new StjMCParticleRegion(120.0,-120.0,1.0));

  StAnaPars* anaparsParton_transPlus = new StAnaPars;
  anaparsParton_transPlus->useMonteCarlo = true;
  // MC cuts
  anaparsParton_transPlus->addMcCut(new StjMCParticleCutParton);
  // Jet cuts
  anaparsParton_transPlus->addJetCut(new StProtoJetCutPt(3,200));
  anaparsParton_transPlus->addJetCut(new StProtoJetCutEta(-100,100));
 //Region Cut
  anaparsParton_transPlus->setParticleRegion(new StjMCParticleRegion(120.0,60.0,1.0));


  StAnaPars* anaparsParton_transMinus = new StAnaPars;
  anaparsParton_transMinus->useMonteCarlo = true;
  // MC cuts
  anaparsParton_transMinus->addMcCut(new StjMCParticleCutParton);
  // Jet cuts
  anaparsParton_transMinus->addJetCut(new StProtoJetCutPt(3,200));
  anaparsParton_transMinus->addJetCut(new StProtoJetCutEta(-100,100));
 //Region Cut
  anaparsParton_transMinus->setParticleRegion(new StjMCParticleRegion(-60.0,-120.0,1.0));
  
  //--------------------------------------------------------------------------------------------

  StFastJetAreaPars *JetAreaPars = new StFastJetAreaPars;
  JetAreaPars->setGhostArea(0.01);
  // Set anti-kt R=0.6 parameters
  StFastJetPars* AntiKtR060Pars = new StFastJetPars;
  AntiKtR060Pars->setJetAlgorithm(StFastJetPars::antikt_algorithm);
  AntiKtR060Pars->setRparam(0.6);
  AntiKtR060Pars->setRecombinationScheme(StFastJetPars::E_scheme);
  AntiKtR060Pars->setStrategy(StFastJetPars::Best);
  AntiKtR060Pars->setPtMin(5.0);
  AntiKtR060Pars->setJetArea(JetAreaPars);


  jetmaker->addBranch("AntiKtR060Particle",anaparsParticle,AntiKtR060Pars);
  jetmaker->addBranch("AntiKtR060Parton",anaparsParton,AntiKtR060Pars);
  jetmaker->addBranch("AntiKtR060NHits12",anapars12,AntiKtR060Pars);
 

  uemaker->addBranch("toward",anapars12_tow,"AntiKtR060NHits12");
  uemaker->addBranch("away",anapars12_away,"AntiKtR060NHits12");
  uemaker->addBranch("transP",anapars12_transPlus,"AntiKtR060NHits12");
  uemaker->addBranch("transM",anapars12_transMinus,"AntiKtR060NHits12");
  
  uemaker->addBranch("toward",anaparsParticle_toward,"AntiKtR060Particle");
  uemaker->addBranch("away",anaparsParticle_away,"AntiKtR060Particle");
  uemaker->addBranch("transP",anaparsParticle_transPlus,"AntiKtR060Particle");
  uemaker->addBranch("transM",anaparsParticle_transMinus,"AntiKtR060Particle");
 
  uemaker->addBranch("toward",anaparsParton_toward,"AntiKtR060Parton");
  uemaker->addBranch("away",anaparsParton_away,"AntiKtR060Parton");
  uemaker->addBranch("transP",anaparsParton_transPlus,"AntiKtR060Parton");
  uemaker->addBranch("transM",anaparsParton_transMinus,"AntiKtR060Parton");

  //------------------------------------------------------------------------------------



  chain->Init();
  chain->EventLoop(nevents);

 
}
