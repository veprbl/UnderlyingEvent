class StJetCandidate;
class StJetVertex;
class StJetSkimTrig;

#include <map>

void RunPythiaUEAnalysis(int nentries = 1e3,
			 const char* jetfile  = "/gpfs01/star/i_bnl/gdwebb/Run9/500GeVJets/Pythia_tunestudy/perugia_pt3_-1_999.jets.root",
			 const char* uefile = "/gpfs01/star/i_bnl/gdwebb/Run9/500GeVJets/Pythia_tunestudy/perugia_pt3_-1_999.ue.root",
			 const char* outfile = "test_jetQAPythiajet500Gev_pt3_-1_perugia.root",
			 const Int_t  mEmbed = 1)
{
  cout << "nentries = " << nentries << endl;
  cout << "jetfile  = " << jetfile  << endl;
  cout << "uefile   = " << uefile << endl;
  cout << "outfile  = " << outfile << endl;

  // Load libraries
  gSystem->Load("StJetEvent");

  // Open jet & skim files
  TChain* jetChain  = new TChain("jet");
  TChain* ueChain   = new TChain("ue");

  jetChain->Add(jetfile);
  ueChain->Add(uefile);
  
  // Set jet buffer
  StJetEvent* jetEvent = 0;
  jetChain->SetBranchAddress("AntiKtR060Particle",&jetEvent);

  StUeEvent* ueEvent_transP = 0;
  ueChain->SetBranchAddress("transP_AntiKtR060Particle",&ueEvent_transP);

  StUeEvent* ueEvent_transM = 0;
  ueChain->SetBranchAddress("transM_AntiKtR060Particle",&ueEvent_transM);

  StUeEvent* ueEvent_away = 0;
  ueChain->SetBranchAddress("away_AntiKtR060Particle",&ueEvent_away);

  StUeEvent* ueEvent_toward = 0;
  ueChain->SetBranchAddress("toward_AntiKtR060Particle",&ueEvent_toward);

  StUeEvent *ueEvent_transMax = 0;
  StUeEvent *ueEvent_transMin = 0;

  // Open output file for writing
  TFile* ofile = TFile::Open(outfile,"recreate");
  assert(ofile);

  BookHists();

  Float_t sumparticlepT_transP, sumparticlepT_transM;
  Float_t sumparticlepT_transMax, sumparticlepT_transMin;
  Float_t sumparticlepT_away, sumparticlepT_toward;
  Float_t aveparticlepT_transP, aveparticlepT_transM;
  Float_t aveparticlepT_transMax, aveparticlepT_transMin;
  Float_t aveparticlepT_away, aveparticlepT_toward;
  Float_t maxparticlepT_away, maxparticlepT_toward, maxparticlepT_transP, maxparticlepT_transM, maxparticlepT_transMax, maxparticlepT_transMin;
  Float_t minparticlepT_away, minparticlepT_toward, minparticlepT_transP, minparticlepT_transM, minparticlepT_transMax, minparticlepT_transMin;

  for (int iEntry = 0; iEntry < nentries; ++iEntry) {
    if (jetChain->GetEvent(iEntry) <= 0 || ueChain->GetEvent(iEntry) <= 0) break;
    // Should not be null
    assert(jetEvent && ueEvent_transP);
  
    // Enforce event synchronization
    assert(jetEvent->runId() == ueEvent_transP->runId() && jetEvent->eventId() == ueEvent_transP->eventId());
    if (iEntry % 100 == 0) cout << "------ Event: " << iEntry << " -------"  << endl;
    //   hrunnumber->Fill(jetEvent->runId());
  
    
    StJetVertex* vertex = jetEvent->vertex();
    // StJetVertex* ue_vertex = ueEvent_transP->vertex();
    // bool vertexBool = vertexPass(vertex, ue_vertex);
    // if(!vertexBool) continue;
    
    StJetCandidate *leadingjet = findLeadingJet(vertex); // Leading jet from jet Trees
    if(leadingjet->pt() != ueEvent_transP->leadingJetpt()) continue;
    if(leadingjet->pt() == 0) continue; 
    // if(TMath::Abs(leadingjet->detEta()) > 0.5) { continue;}
    // if(leadingjet->rt() > 0.9){  continue;} 
    //  bool trackpT_high = hightrackpT(leadingjet); // large track pT cut
    // if(trackpT_high) continue;
    

    hleadingjetpT->Fill(leadingjet->pt());


      //-----------------Transverse Plus ------------------------
      sumparticlepT_transP = 0; 
      aveparticlepT_transP = 0;
      maxparticlepT_transP = 0;
      minparticlepT_transP = 100;
      for (int iParticle = 0; iParticle < ueEvent_transP->numberOfParticles(); iParticle++)
	{
	  StJetParticle* particle_transP = ueEvent_transP->particle(iParticle);
	  htransP_particlepT->Fill(particle_transP->pt());
	  htransP_particleeta->Fill(particle_transP->eta());
	  htransP_particlephi->Fill(particle_transP->phi());
	  sumparticlepT_transP = sumparticlepT_transP + particle_transP->pt();
	  if(maxparticlepT_transP < particle_transP->pt()){maxparticlepT_transP = particle_transP->pt();} 
	  if(minparticlepT_transP > particle_transP->pt()){minparticlepT_transP = particle_transP->pt();} 
	}//End of Track Loop
      

      // ------------------- End Of Trans Plus --------------------------

      //-----------------Transverse Minus ------------------------
      sumparticlepT_transM = 0; 
      aveparticlepT_transM = 0;
      maxparticlepT_transM = 0;
      minparticlepT_transM = 100;
      for (int iParticle = 0; iParticle < ueEvent_transM->numberOfParticles(); iParticle++)
      	{
      	  StJetParticle* particle_transM = ueEvent_transM->particle(iParticle);
      	  htransM_particlepT->Fill(particle_transM->pt());
      	  htransM_particleeta->Fill(particle_transM->eta());
      	  htransM_particlephi->Fill(particle_transM->phi());
      	  sumparticlepT_transM = sumparticlepT_transM + particle_transM->pt();
      	  if(maxparticlepT_transM < particle_transM->pt()){maxparticlepT_transM = particle_transM->pt();} 
      	  if(minparticlepT_transM > particle_transM->pt()){minparticlepT_transM = particle_transM->pt();} 
      	}//End of Particle Loop
      
   
      // ------------------- End Of Trans Minus --------------------------

      //----------------- Away Region ------------------------
      sumparticlepT_away = 0; 
      aveparticlepT_away = 0;
      maxparticlepT_away = 0;
      minparticlepT_away = 100;
      for (int iParticle = 0; iParticle < ueEvent_away->numberOfParticles(); iParticle++)
      	{
      	  StJetParticle* particle_away = ueEvent_away->particle(iParticle);
      	  haway_particlepT->Fill(particle_away->pt());
      	  haway_particleeta->Fill(particle_away->eta());
      	  haway_particlephi->Fill(particle_away->phi());
      	  sumparticlepT_away = sumparticlepT_away + particle_away->pt();
      	  if(maxparticlepT_away < particle_away->pt()){maxparticlepT_away = particle_away->pt();} 
      	  if(minparticlepT_away > particle_away->pt()){minparticlepT_away = particle_away->pt();} 
      	}//End of Particle Loop
      
   
      // ------------------- End Of Away --------------------------

      //----------------- Toward Region ---------------------------
      sumparticlepT_toward = 0; 
      aveparticlepT_toward = 0;
      maxparticlepT_toward = 0;
      minparticlepT_toward = 100;
      for (int iParticle = 0; iParticle < ueEvent_toward->numberOfParticles(); iParticle++)
      	{
      	  StJetParticle* particle_toward = ueEvent_toward->particle(iParticle);
      	  htoward_particlepT->Fill(particle_toward->pt());
      	  htoward_particleeta->Fill(particle_toward->eta());
      	  htoward_particlephi->Fill(particle_toward->phi());
      	  sumparticlepT_toward = sumparticlepT_toward + particle_toward->pt();
      	  if(maxparticlepT_toward < particle_toward->pt()){maxparticlepT_toward = particle_toward->pt();} 
      	  if(minparticlepT_toward > particle_toward->pt()){minparticlepT_toward = particle_toward->pt();} 
      	}//End of Particle Loop
      
    
      // ------------------- End Of Toward --------------------------


      if(sumparticlepT_transP > sumparticlepT_transM){
      	ueEvent_transMax = ueEvent_transP;
      	ueEvent_transMin = ueEvent_transM;
      }
      else{
      	ueEvent_transMax = ueEvent_transM;
      	ueEvent_transMin = ueEvent_transP;
      }
      
      
      //-----------------Transverse Max ------------------------
      sumparticlepT_transMax =  0; 
      aveparticlepT_transMax =  0;
      maxparticlepT_transMax =  0;
      minparticlepT_transMax =  100;
      for (int iParticle = 0; iParticle < ueEvent_transMax->numberOfParticles(); iParticle++)
      	{
      	  StJetParticle* particle_transMax = ueEvent_transMax->particle(iParticle);
      	  htransMax_particlepT->Fill(particle_transMax->pt());
      	  htransMax_particleeta->Fill(particle_transMax->eta());
      	  htransMax_particlephi->Fill(particle_transMax->phi());
      	  sumparticlepT_transMax = sumparticlepT_transMax + particle_transMax->pt();
      	  if(maxparticlepT_transMax < particle_transMax->pt()){maxparticlepT_transMax = particle_transMax->pt();} 
      	  if(minparticlepT_transMax > particle_transMax->pt()){minparticlepT_transMax = particle_transMax->pt();} 
      	}//End of Particle Loop
      
      // ------------------- End Of Trans Max --------------------------
      
      //-----------------Transverse Min ------------------------
      sumparticlepT_transMin = 0; 
      aveparticlepT_transMin = 0;
      maxparticlepT_transMin = 0;
      minparticlepT_transMin = 100;
      for (int iParticle = 0; iParticle < ueEvent_transMin->numberOfParticles(); iParticle++)
      	{
      	  StJetParticle* particle_transMin = ueEvent_transMin->particle(iParticle);
      	  htransMin_particlepT->Fill(particle_transMin->pt());
      	  htransMin_particleeta->Fill(particle_transMin->eta());
      	  htransMin_particlephi->Fill(particle_transMin->phi());
      	  sumparticlepT_transMin = sumparticlepT_transMin + particle_transMin->pt();
      	  if(maxparticlepT_transMin < particle_transMin->pt()){maxparticlepT_transMin = particle_transMin->pt();} 
      	  if(minparticlepT_transMin > particle_transMin->pt()){minparticlepT_transMin = particle_transMin->pt();} 
      	}//End of Particle Loop
      

      // ------------------- End Of Trans Min --------------------------


      //---------------- Fill Event Histograms--------------------
      htransP_numparticle->Fill(ueEvent_transP->numberOfParticles());
      htransM_numparticle->Fill(ueEvent_transM->numberOfParticles());
      haway_numparticle->Fill(ueEvent_away->numberOfParticles());
      htoward_numparticle->Fill(ueEvent_toward->numberOfParticles());
      htransMax_numparticle->Fill(ueEvent_transMax->numberOfParticles());
      htransMin_numparticle->Fill(ueEvent_transMin->numberOfParticles());

 


      if(ueEvent_transP->numberOfParticles() != 0) aveparticlepT_transP = sumparticlepT_transP / ueEvent_transP->numberOfParticles();

      //particle transP
      htransP_numParticleVsMaxJetpT->Fill(leadingjet->pt(),ueEvent_transP->numberOfParticles());
      htransP_sumParticlepTVsMaxJetpT->Fill(leadingjet->pt(),sumparticlepT_transP);
      htransP_aveParticlepTVsMaxJetpT->Fill(leadingjet->pt(),aveparticlepT_transP);
      htransP_maxParticlepTVsMaxJetpT->Fill(leadingjet->pt(),maxparticlepT_transP);
      htransP_minParticlepTVsMaxJetpT->Fill(leadingjet->pt(),minparticlepT_transP);     

      if(ueEvent_transM->numberOfParticles() != 0) aveparticlepT_transM = sumparticlepT_transM / ueEvent_transM->numberOfParticles();
  
      //particle transM
      htransM_numParticleVsMaxJetpT->Fill(leadingjet->pt(),ueEvent_transM->numberOfParticles());
      htransM_sumParticlepTVsMaxJetpT->Fill(leadingjet->pt(),sumparticlepT_transM);
      htransM_aveParticlepTVsMaxJetpT->Fill(leadingjet->pt(),aveparticlepT_transM);
      htransM_maxParticlepTVsMaxJetpT->Fill(leadingjet->pt(),maxparticlepT_transM);
      htransM_minParticlepTVsMaxJetpT->Fill(leadingjet->pt(),minparticlepT_transM); 
      
      if(ueEvent_transMax->numberOfParticles() != 0) aveparticlepT_transMax = sumparticlepT_transMax / ueEvent_transMax->numberOfParticles();
     
      //particle transMax
      htransMax_numParticleVsMaxJetpT->Fill(leadingjet->pt(),ueEvent_transMax->numberOfParticles());
      htransMax_sumParticlepTVsMaxJetpT->Fill(leadingjet->pt(),sumparticlepT_transMax);
      htransMax_aveParticlepTVsMaxJetpT->Fill(leadingjet->pt(),aveparticlepT_transMax);
      htransMax_maxParticlepTVsMaxJetpT->Fill(leadingjet->pt(),maxparticlepT_transMax);
      htransMax_minParticlepTVsMaxJetpT->Fill(leadingjet->pt(),minparticlepT_transMax);

     

      if(ueEvent_transMin->numberOfParticles() != 0) aveparticlepT_transMin = sumparticlepT_transMin / ueEvent_transMin->numberOfParticles();
     
      //particle transMin
      htransMin_numParticleVsMaxJetpT->Fill(leadingjet->pt(),ueEvent_transMin->numberOfParticles());
      htransMin_sumParticlepTVsMaxJetpT->Fill(leadingjet->pt(),sumparticlepT_transMin);
      htransMin_aveParticlepTVsMaxJetpT->Fill(leadingjet->pt(),aveparticlepT_transMin);
      htransMin_maxParticlepTVsMaxJetpT->Fill(leadingjet->pt(),maxparticlepT_transMin);
      htransMin_minParticlepTVsMaxJetpT->Fill(leadingjet->pt(),minparticlepT_transMin);

    

      if(ueEvent_away->numberOfParticles() != 0) aveparticlepT_away = sumparticlepT_away / ueEvent_away->numberOfParticles();
      
      //particle away
      haway_numParticleVsMaxJetpT->Fill(leadingjet->pt(),ueEvent_away->numberOfParticles());
      haway_sumParticlepTVsMaxJetpT->Fill(leadingjet->pt(),sumparticlepT_away);
      haway_aveParticlepTVsMaxJetpT->Fill(leadingjet->pt(),aveparticlepT_away);
      haway_maxParticlepTVsMaxJetpT->Fill(leadingjet->pt(),maxparticlepT_away);
      haway_minParticlepTVsMaxJetpT->Fill(leadingjet->pt(),minparticlepT_away);

      
      if(ueEvent_toward->numberOfParticles() != 0) aveparticlepT_toward = sumparticlepT_toward / ueEvent_toward->numberOfParticles();
      
      //particle toward
      htoward_numParticleVsMaxJetpT->Fill(leadingjet->pt(),ueEvent_toward->numberOfParticles());
      htoward_sumParticlepTVsMaxJetpT->Fill(leadingjet->pt(),sumparticlepT_toward);
      htoward_aveParticlepTVsMaxJetpT->Fill(leadingjet->pt(),aveparticlepT_toward);
      htoward_maxParticlepTVsMaxJetpT->Fill(leadingjet->pt(),maxparticlepT_toward);
      htoward_minParticlepTVsMaxJetpT->Fill(leadingjet->pt(),minparticlepT_toward);
     
      //--------------------------------------------------------------
  }//End of Event Loop
  ofile->Write();
  ofile->Close();
}


void BookHists()
{
  //Book histograms
  TH1F* hleadingjetpT = new TH1F("hleadingjetpT",";Leading jet p_{T} [GeV]",95,5,100);

  //Particle Histograms
  TH1F* htransP_particlepT = new TH1F("htransP_particlepT","transP; particle p_{T} [GeV]",1000,0,50);
  TH1F* htransP_particleeta = new TH1F("htransP_particleeta","transP; particle #eta",66,-1.5,1.5);
  TH1F* htransP_particlephi = new TH1F("htransP_particlephi","transP; particle #phi",120,-3.14159,3.14159);
  TH1F* htransP_numparticle = new TH1F("htransP_numparticle","transP; particle multiplicity",20,0,20);

  TH1F* htransM_particlepT = new TH1F("htransM_particlepT","transM; particle p_{T} [GeV]",1000,0,50);
  TH1F* htransM_particleeta = new TH1F("htransM_particleeta","transM; particle #eta",66,-1.5,1.5);
  TH1F* htransM_particlephi = new TH1F("htransM_particlephi","transM; particle #phi",120,-3.14159,3.14159);
  TH1F* htransM_numparticle = new TH1F("htransM_numparticle","transM; particle multiplicity",20,0,20);

  TH1F* htransMax_particlepT = new TH1F("htransMax_particlepT","transMax; particle p_{T} [GeV]",1000,0,50);
  TH1F* htransMax_particleeta = new TH1F("htransMax_particleeta","transMax; particle #eta",66,-1.5,1.5);
  TH1F* htransMax_particlephi = new TH1F("htransMax_particlephi","transMax; particle #phi",120,-3.14159,3.14159);
  TH1F* htransMax_numparticle = new TH1F("htransMax_numparticle","transMax; particle multiplicity",20,0,20);

  TH1F* htransMin_particlepT = new TH1F("htransMin_particlepT","transMin; particle p_{T} [GeV]",1000,0,50);
  TH1F* htransMin_particleeta = new TH1F("htransMin_particleeta","transMin; particle #eta",66,-1.5,1.5);
  TH1F* htransMin_particlephi = new TH1F("htransMin_particlephi","transMin; particle #phi",120,-3.14159,3.14159);
  TH1F* htransMin_numparticle = new TH1F("htransMin_numparticle","transMin; particle multiplicity",20,0,20);

  TH1F* haway_particlepT = new TH1F("haway_particlepT","away; particle p_{T} [GeV]",1000,0,50);
  TH1F* haway_particleeta = new TH1F("haway_particleeta","away; particle #eta",66,-1.5,1.5);
  TH1F* haway_particlephi = new TH1F("haway_particlephi","away; particle #phi",120,-3.14159,3.14159);
  TH1F* haway_numparticle = new TH1F("haway_numparticle","away; particle multiplicity",20,0,20);

  TH1F* htoward_particlepT = new TH1F("htoward_particlepT","toward; particle p_{T} [GeV]",1000,0,50);
  TH1F* htoward_particleeta = new TH1F("htoward_particleeta","toward; particle #eta",66,-1.5,1.5);
  TH1F* htoward_particlephi = new TH1F("htoward_particlephi","toward; particle #phi",120,-3.14159,3.14159);
  TH1F* htoward_numparticle = new TH1F("htoward_numparticle","away; particle multiplicity",20,0,20);
  
  //Event Histograms
  TH2F* htransP_numParticleVsMaxJetpT = new TH2F("htransP_numParticleVsMaxJetpT","transP; jet p_{T} [GeV]; particle multiplicity",95,5,100,30,0,30);
  TH2F* htransP_sumParticlepTVsMaxJetpT = new TH2F("htransP_sumParticlepTVsMaxJetpT","transP;  jet p_{T} [GeV]; #Sigmaparticle p_{T}",95,5,100,50,0,50);
  TH2F* htransP_aveParticlepTVsMaxJetpT = new TH2F("htransP_aveParticlepTVsMaxJetpT","transP;  jet p_{T} [GeV]; <particle p_{T}> ",95,5,100,30,0,30);
  TH2F* htransP_maxParticlepTVsMaxJetpT = new TH2F("htransP_maxParticlepTVsMaxJetpT","transP;  jet p_{T} [GeV]; max particle p_{T} ",95,5,100,30,0,30);
  TH2F* htransP_minParticlepTVsMaxJetpT = new TH2F("htransP_minParticlepTVsMaxJetpT","transP;  jet p_{T} [GeV]; min particle p_{T} ",95,5,100,30,0,30);

  TH2F* htransMax_numParticleVsMaxJetpT = new TH2F("htransMax_numParticleVsMaxJetpT","transMax; jet p_{T} [GeV]; particle multiplicity",95,5,100,30,0,30);
  TH2F* htransMax_sumParticlepTVsMaxJetpT = new TH2F("htransMax_sumParticlepTVsMaxJetpT","transMax;  jet p_{T} [GeV]; #Sigmaparticle p_{T}",95,5,100,50,0,50);
  TH2F* htransMax_aveParticlepTVsMaxJetpT = new TH2F("htransMax_aveParticlepTVsMaxJetpT","transMax;  jet p_{T} [GeV]; <particle p_{T}> ",95,5,100,30,0,30);
  TH2F* htransMax_maxParticlepTVsMaxJetpT = new TH2F("htransMax_maxParticlepTVsMaxJetpT","transMax;  jet p_{T} [GeV]; max particle p_{T} ",95,5,100,30,0,30);
  TH2F* htransMax_minParticlepTVsMaxJetpT = new TH2F("htransMax_minParticlepTVsMaxJetpT","transMax;  jet p_{T} [GeV]; min particle p_{T} ",95,5,100,30,0,30);


  TH2F* htransM_numParticleVsMaxJetpT = new TH2F("htransM_numParticleVsMaxJetpT","transM; jet p_{T} [GeV]; particle multiplicity",95,5,100,30,0,30);
  TH2F* htransM_sumParticlepTVsMaxJetpT = new TH2F("htransM_sumParticlepTVsMaxJetpT","transM;  jet p_{T} [GeV]; #Sigmaparticle p_{T}",95,5,100,50,0,50);
  TH2F* htransM_aveParticlepTVsMaxJetpT = new TH2F("htransM_aveParticlepTVsMaxJetpT","transM;  jet p_{T} [GeV]; <particle p_{T}> ",95,5,100,30,0,30);
  TH2F* htransM_maxParticlepTVsMaxJetpT = new TH2F("htransM_maxParticlepTVsMaxJetpT","transM;  jet p_{T} [GeV]; max particle p_{T} ",95,5,100,30,0,30);
  TH2F* htransM_minParticlepTVsMaxJetpT = new TH2F("htransM_minParticlepTVsMaxJetpT","transM;  jet p_{T} [GeV]; min particle p_{T} ",95,5,100,30,0,30);



  TH2F* htransMin_numParticleVsMaxJetpT = new TH2F("htransMin_numParticleVsMaxJetpT","transMin; jet p_{T} [GeV]; particle multiplicity",95,5,100,30,0,30);
  TH2F* htransMin_sumParticlepTVsMaxJetpT = new TH2F("htransMin_sumParticlepTVsMaxJetpT","transMin;  jet p_{T} [GeV]; #Sigmaparticle p_{T}",95,5,100,50,0,50);
  TH2F* htransMin_aveParticlepTVsMaxJetpT = new TH2F("htransMin_aveParticlepTVsMaxJetpT","transMin;  jet p_{T} [GeV]; <particle p_{T}> ",95,5,100,30,0,30);
  TH2F* htransMin_maxParticlepTVsMaxJetpT = new TH2F("htransMin_maxParticlepTVsMaxJetpT","transMin;  jet p_{T} [GeV]; max particle p_{T} ",95,5,100,30,0,30);
  TH2F* htransMin_minParticlepTVsMaxJetpT = new TH2F("htransMin_minParticlepTVsMaxJetpT","transMin;  jet p_{T} [GeV]; min particle p_{T} ",95,5,100,30,0,30);


  TH2F* haway_numParticleVsMaxJetpT = new TH2F("haway_numParticleVsMaxJetpT","away; jet p_{T} [GeV]; particle multiplicity",95,5,100,30,0,30);
  TH2F* haway_sumParticlepTVsMaxJetpT = new TH2F("haway_sumParticlepTVsMaxJetpT","away;  jet p_{T} [GeV]; #Sigmaparticle p_{T}",95,5,100,50,0,50);
  TH2F* haway_aveParticlepTVsMaxJetpT = new TH2F("haway_aveParticlepTVsMaxJetpT","away;  jet p_{T} [GeV]; <particle p_{T}> ",95,5,100,30,0,30);
  TH2F* haway_maxParticlepTVsMaxJetpT = new TH2F("haway_maxParticlepTVsMaxJetpT","away;  jet p_{T} [GeV]; max particle p_{T} ",95,5,100,30,0,30);
  TH2F* haway_minParticlepTVsMaxJetpT = new TH2F("haway_minParticlepTVsMaxJetpT","away;  jet p_{T} [GeV]; min particle p_{T} ",95,5,100,30,0,30);
 

  TH2F* htoward_numParticleVsMaxJetpT = new TH2F("htoward_numParticleVsMaxJetpT","toward; jet p_{T} [GeV]; particle multiplicity",95,5,100,30,0,30);
  TH2F* htoward_sumParticlepTVsMaxJetpT = new TH2F("htoward_sumParticlepTVsMaxJetpT","toward;  jet p_{T} [GeV]; #Sigmaparticle p_{T}",95,5,100,50,0,50);
  TH2F* htoward_aveParticlepTVsMaxJetpT = new TH2F("htoward_aveParticlepTVsMaxJetpT","toward;  jet p_{T} [GeV]; <particle p_{T}> ",95,5,100,30,0,30);
  TH2F* htoward_maxParticlepTVsMaxJetpT = new TH2F("htoward_maxParticlepTVsMaxJetpT","toward;  jet p_{T} [GeV]; max particle p_{T} ",95,5,100,30,0,30);
  TH2F* htoward_minParticlepTVsMaxJetpT = new TH2F("htoward_minParticlepTVsMaxJetpT","toward;  jet p_{T} [GeV]; min particle p_{T} ",95,5,100,30,0,30);
  
 




}

Bool_t vertexPass(StJetVertex *vertex, StJetVertex *ue_vertex)
{
  if (!vertex) return false;
  if(!ue_vertex) return false;
  if(vertex->ranking() < 0) return false;
  // if( vertex->position().z() !=  ue_vertex->position().z()) return false;
  if(fabs(vertex->position().z()) > 80.0) return false;
  return true;
}



StJetCandidate* findLeadingJet(StJetVertex* vertex){
  
  StJetCandidate * leadingjet = new StJetCandidate(); 
  StJetCandidate * jets = new StJetCandidate();
  for (int iJet = 0; iJet < vertex->numberOfJets(); ++iJet){
    jets = (StJetCandidate*) vertex->jet(iJet);
    if(leadingjet->pt() < jets->pt()){
      leadingjet = jets;
    } 
  } // End of loop over jets
  
  return leadingjet;
}



