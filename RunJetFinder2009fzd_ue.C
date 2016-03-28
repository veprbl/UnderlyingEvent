//
// Pibero Djawotho <pibero@tamu.edu>
// Texas A&M
// 19 Jan 2012
//
// Run jet finder on Zebra file
// Add UE addition: 11 Aug 2015, Grant Webb, BNL
//

void RunJetFinder2009fzd_ue(int nevents = 1000,
			    const char* fzdfile = "/gpfs01/star/scratch/gdwebb/Embedding_inclu/10103041/pt4_5_10103041_88.fzd",
			    const char* jetfile = "jets_pythiatest_fzd.jets.root",
			    const char* uefile  = "ue_pythiatest_fzd.ue.root" )
{
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
  gSystem->Load("StTriggerFilterMaker");
 
  gSystem->Load("St_g2t");
  gSystem->Load("St_geant_Maker");

  StChain* chain = new StChain;

  St_geant_Maker* geant = new St_geant_Maker;
  geant->SetInputFile(fzdfile);

  // StMcEvent maker
  StMcEventMaker* mcEventMaker = new StMcEventMaker;
  mcEventMaker->doPrintEventInfo = false;
  mcEventMaker->doPrintMemoryInfo = false;

  // star database
  St_db_Maker* starDb = new St_db_Maker("StarDb","MySQL:StarDb");
  starDb->SetDateTime(20090413,145430); // Run 10179006

  // Endcap database
  StEEmcDbMaker* eemcDb = new StEEmcDbMaker;

  // Jet maker
  StJetMaker2009* jetmaker = new StJetMaker2009;
  jetmaker->setJetFile(jetfile);
  // UE maker
  StUEMaker2009* uemaker = new StUEMaker2009;
  uemaker->setUeFile(uefile);
  


  //------------------------------------------------------------------------------------

  // Set analysis cuts for particle jets branch
  StAnaPars* anaparsParticle = new StAnaPars;
  anaparsParticle->useMonteCarlo = true;

  // MC cuts
  anaparsParticle->addMcCut(new StjMCParticleCutStatus(1)); // final state particles

  // Jet cuts
  anaparsParticle->addJetCut(new StProtoJetCutPt(3,200));
  anaparsParticle->addJetCut(new StProtoJetCutEta(-100,100));

  //------------------------------------------------------------------------------------

  // Set analysis cuts for parton jets branch
  StAnaPars* anaparsParton = new StAnaPars;
  anaparsParton->useMonteCarlo = true;

  // MC cuts
  anaparsParton->addMcCut(new StjMCParticleCutParton);

  // Jet cuts
  anaparsParton->addJetCut(new StProtoJetCutPt(3,200));
  anaparsParton->addJetCut(new StProtoJetCutEta(-100,100));
  //------------------------------------------------------------------------------------
 
 //**********************************
 // Set analysis cuts for particle ue branches
  anaparsParticle_tow = anaparsParticle; 
  anaparsParticle_tow->setParticleRegion(new StjMCParticleRegion(60.0,-60.0,1.0));

  anaparsParticle_away = anaparsParticle;
  anaparsParticle_away->setParticleRegion(new StjMCParticleRegion(120.0,-120.0,1.0));

  anaparsParticle_transP = anaparsParticle;
  anaparsParticle_transP->setParticleRegion(new StjMCParticleRegion(120.0,60.0,1.0));

  anaparsParticle_transM = anaparsParticle;
  anaparsParticle_transM->setParticleRegion(new StjMCParticleRegion(-60.0,-120.0,1.0));

  //*********************************
  
  //++++++++ Set Analysis Cuts for parton ue branches+++++++++++++
  anaparsParton_tow = anaparsParton;
  anaparsParton_tow->setParticleRegion(new StjMCParticleRegion(60.0,-60.0,1.0));

  anaparsParton_away = anaparsParton;
  anaparsParton_away->setParticleRegion(new StjMCParticleRegion(120.0,-120.0,1.0));

  anaparsParton_transP = anaparsParton;
  anaparsParton_transP->setParticleRegion(new StjMCParticleRegion(120.0,60.0,1.0));

  anaparsParton_transM = anaparsParton;
  anaparsParton_transM->setParticleRegion(new StjMCParticleRegion(-60.0,-120.0,1.0));

  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 //Jet Area 
  StFastJetAreaPars *JetAreaPars = new StFastJetAreaPars;
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
 
  //------------------------------------------------------------------------------------

  uemaker->addBranch("toward",anaparsParticle_tow,"AntiKtR060Particle");
  uemaker->addBranch("away",anaparsParticle_away,"AntiKtR060Particle");
  uemaker->addBranch("transP",anaparsParticle_transP,"AntiKtR060Particle");
  uemaker->addBranch("transM",anaparsParticle_transM,"AntiKtR060Particle");

  uemaker->addBranch("toward",anaparsParton_tow,"AntiKtR060Parton");
  uemaker->addBranch("away",anaparsParton_away,"AntiKtR060Parton");
  uemaker->addBranch("transP",anaparsParton_transP,"AntiKtR060Parton");
  uemaker->addBranch("transM",anaparsParton_transM,"AntiKtR060Parton");
  // Run
  chain->Init();
  chain->EventLoop(nevents);
}
