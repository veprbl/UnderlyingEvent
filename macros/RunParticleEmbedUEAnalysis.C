/* 
This runs the over the jet, skim, ue trees. Fills histograms. This is a stream lined
version Reducing the number of histograms to just the sum and num towers and tracks vs jet pT.
Check out oldMacros_sumTrackpT/*.C for finding many other histograms made
 */

class StJetCandidate;
class StJetVertex;
class StJetSkimTrig;

#include <map>

void RunParticleEmbedUEAnalysis(int nentries = 1E9,
		   const char* jetfile  = "/gpfs01/star/i_bnl/gdwebb/Run9/500GeVJets/Embed_inclu/pTbin_35_45/pt35_45_10100017_10.jets.root",
		   const char* uefile = "/gpfs01/star/i_bnl/gdwebb/Run9/500GeVJets/Embed_inclu/pTbin_35_45/pt35_45_10100017_10.ue.root",
		   const char* outfile = "test_jetQAParticleEmbed500Gev_10100017.root",
		   const Int_t  mEmbed = 1)
{
  cout << "nentries = " << nentries << endl;
  cout << "jetfile  = " << jetfile  << endl;
  cout << "uefile   = " << uefile << endl;
  cout << "outfile  = " << outfile << endl;
  const float area  =  4*TMath::Pi()/3;
  const float area2 =  2*TMath::Pi()/3;

  cout << "area: " << area << endl;
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
  Float_t numparticles_transP, numparticles_transM;
  Float_t sumparticlepT_transMax, sumparticlepT_transMin,;
  Float_t numparticles_transMax, numparticles_transMin;
  Float_t sumparticlepT_away, sumparticlepT_toward;
  Float_t numparticles_away, numparticles_toward;
  Float_t leadingJetpT;

  for (int iEntry = 0; iEntry < nentries; ++iEntry) {
    if (jetChain->GetEvent(iEntry) <= 0 || ueChain->GetEvent(iEntry) <= 0) break;
    // Should not be null
    assert(jetEvent && ueEvent_transP);
    
    // Enforce event synchronization
    assert(jetEvent->runId() == ueEvent_transP->runId() && jetEvent->eventId() == ueEvent_transP->eventId());
    
    if (iEntry % 1000 == 0) cout << iEntry << endl;
    //   hrunnumber->Fill(jetEvent->runId());
 
    StJetVertex* vertex = jetEvent->vertex();
    // StJetVertex* ue_vertex = ueEvent_transP->vertex();
    // bool vertexBool = vertexPass(vertex, ue_vertex);
    // if(!vertexBool) continue;
    
    StJetCandidate *leadingjet = findLeadingJet(vertex); // Leading jet from jet tree
    // Do I need any matching of the particle level leading Jet and the detector level leading Jet? 
    if(leadingjet->pt() != ueEvent_transP->leadingJetpt()) continue;
    if(TMath::Abs(leadingjet->detEta()) > 0.5) { continue;}
  

    leadingJetpT = leadingjet->pt(); //Define the leading jet pT 
    
    hleadingjetpTJP2->Fill(leadingJetpT); 
    
    //-----------------Transverse Plus ------------------------
    sumparticlepT_transP = 0; 
    numparticles_transP  = 0; 
    
    sumparticlepT_transP = ueEvent_transP->sumParticlePt();
    numparticles_transP  = ueEvent_transP->numberOfParticles();
    //particle transP
    htransP_numParticlesVsMaxJetpTJP2->Fill(leadingJetpT,numparticles_transP/area2);
    htransP_sumParticlepTVsMaxJetpTJP2->Fill(leadingJetpT,sumparticlepT_transP/area2);

    // ------------------- End Of Trans Plus --------------------------
    
    //-----------------Transverse Minus ------------------------
    sumparticlepT_transM = 0; 
    numparticles_transM  = 0;

    sumparticlepT_transM = ueEvent_transM->sumParticlePt();
    numparticles_transM = ueEvent_transM->numberOfParticles();
    cout << "particle jet pT: " << leadingJetpT <<  "numparticles: " << numparticles_transM << "sumparticles: " << sumparticlepT_transM << endl;
    //particle transM
    htransM_numParticlesVsMaxJetpTJP2->Fill(leadingJetpT,numparticles_transM/area2);
    htransM_sumParticlepTVsMaxJetpTJP2->Fill(leadingJetpT,sumparticlepT_transM/area2);
    
    // ------------------- End Of Trans Minus --------------------------
    
    //----------------Transverse Region------------------------
    
      //track transverse
    htransverse_numParticlesVsMaxJetpTJP2->Fill(leadingJetpT,(numparticles_transP + numparticles_transM)/area);
    htransverse_sumParticlepTVsMaxJetpTJP2->Fill(leadingJetpT,(sumparticlepT_transP + sumparticlepT_transM)/area);
    
    
    //--------------End of Transverse-------------------------      
    //----------------- Away Region ------------------------
    sumparticlepT_away = 0; 
    numparticles_away  = 0; 

    sumparticlepT_away = ueEvent_away->sumParticlePt();
    numparticles_away = ueEvent_away->numberOfParticles();
       
    //track away
    haway_numParticlesVsMaxJetpTJP2->Fill(leadingJetpT,numparticles_away/area);
    haway_sumParticlepTVsMaxJetpTJP2->Fill(leadingJetpT,sumparticlepT_away/area);
    
    // ------------------- End Of Away --------------------------
    
    //----------------- Toward Region ---------------------------
    sumparticlepT_toward = 0;      
    numparticles_toward  = 0;      
    
    sumparticlepT_toward = ueEvent_toward->sumParticlePt();
    numparticles_toward = ueEvent_toward->numberOfParticles();
    
    //track toward
    htoward_numParticlesVsMaxJetpTJP2->Fill(leadingJetpT,numparticles_toward/area);
    htoward_sumParticlepTVsMaxJetpTJP2->Fill(leadingJetpT,sumparticlepT_toward/area);
   
    // ------------------- End Of Toward --------------------------
    
    
    //--------- Sum Particle pT Trans Max and Trans Min -------------
    if(sumparticlepT_transP > sumparticlepT_transM){
      ueEvent_transMax = ueEvent_transP;
      ueEvent_transMin = ueEvent_transM;
    }
    if(sumparticlepT_transP < sumparticlepT_transM){
      ueEvent_transMax = ueEvent_transM;
      ueEvent_transMin = ueEvent_transP;
    }     
    
    sumparticlepT_transMax = sumparticlepT_transMin = 0; 
    sumparticlepT_transMax =  ueEvent_transMax->sumParticlePt();
    sumparticlepT_transMin =  ueEvent_transMin->sumParticlePt();
    
    htransMax_sumParticlepTVsMaxJetpTJP2->Fill(leadingJetpT,sumparticlepT_transMax/area2);
    htransMin_sumParticlepTVsMaxJetpTJP2->Fill(leadingJetpT,sumparticlepT_transMin/area2);     
    //---------------------------------------------------      
    
    
    //--------- Num Particles Trans Max and Trans Min -------------
    if(numparticles_transP > numparticles_transM){
      ueEvent_transMax = ueEvent_transP;
      ueEvent_transMin = ueEvent_transM;
    }
    if(numparticles_transP < numparticles_transM){
      ueEvent_transMax = ueEvent_transM;
      ueEvent_transMin = ueEvent_transP;
    }
    
    numparticles_transMax = numparticles_transMin = 0;  
    numparticles_transMax = ueEvent_transMax->numberOfParticles();
    numparticles_transMin = ueEvent_transMin->numberOfParticles();
      
    htransMax_numParticlesVsMaxJetpTJP2->Fill(leadingJetpT,numparticles_transMax/area2);
    htransMin_numParticlesVsMaxJetpTJP2->Fill(leadingJetpT,numparticles_transMin/area2);
    // -----------------------------------------------------------
    
  }//End of Event Loop
  ofile->Write();
  ofile->Close();
}


void BookHists()
{
  //Book histograms
  TH1F* hleadingjetpTJP2 = new TH1F("hleadingjetpTJP2",";Leading jet p_{T} [GeV]",40,0,80);

  //Event Histograms
  TH2F* htransP_numParticlesVsMaxJetpTJP2 = new TH2F("htransP_numParticlesVsMaxJetpTJP2","transP; jet p_{T} [GeV]; <N_{ch}>/[#Delta#eta#Delta(#Delta#phi)]",40,0,80,20,0,20);
  TH2F* htransP_sumParticlepTVsMaxJetpTJP2 = new TH2F("htransP_sumParticlepTVsMaxJetpTJP2","transP;  jet p_{T} [GeV]; <#Sigmap_{T,ch}>/[#Delta#eta#Delta(#Delta#phi)]",40,0,80,20,0,20);

  TH2F* htransM_numParticlesVsMaxJetpTJP2 = new TH2F("htransM_numParticlesVsMaxJetpTJP2","transM; jet p_{T} [GeV]; <N_{ch}>/[#Delta#eta#Delta(#Delta#phi)]",40,0,80,20,0,20);
  TH2F* htransM_sumParticlepTVsMaxJetpTJP2 = new TH2F("htransM_sumParticlepTVsMaxJetpTJP2","transM;  jet p_{T} [GeV];<#Sigmap_{T,ch}>/[#Delta#eta#Delta(#Delta#phi)] ",40,0,80,20,0,20); 
 
  TH2F* htransverse_numParticlesVsMaxJetpTJP2 = new TH2F("htransverse_numParticlesVsMaxJetpTJP2","transverse; jet p_{T} [GeV]; <N_{ch}>/[#Delta#eta#Delta(#Delta#phi)]",40,0,80,20,0,20);
  TH2F* htransverse_sumParticlepTVsMaxJetpTJP2 = new TH2F("htransverse_sumParticlepTVsMaxJetpTJP2","transverse; jet p_{T} [GeV]; <#Sigmap_{T,ch}>/[#Delta#eta#Delta(#Delta#phi)]",40,0,80,20,0,20);

  TH2F* htransMax_numParticlesVsMaxJetpTJP2 = new TH2F("htransMax_numParticlesVsMaxJetpTJP2","transMax; jet p_{T} [GeV]; <N_{ch}>/[#Delta#eta#Delta(#Delta#phi)]",40,0,80,20,0,20);
  TH2F* htransMax_sumParticlepTVsMaxJetpTJP2 = new TH2F("htransMax_sumParticlepTVsMaxJetpTJP2","transMax;  jet p_{T} [GeV]; <#Sigmap_{T,ch}>/[#Delta#eta#Delta(#Delta#phi)]",40,0,80,20,0,20);
 
  TH2F* htransMin_numParticlesVsMaxJetpTJP2 = new TH2F("htransMin_numParticlesVsMaxJetpTJP2","transMin; jet p_{T} [GeV]; <N_{ch}>/[#Delta#eta#Delta(#Delta#phi)]",40,0,80,20,0,20);
  TH2F* htransMin_sumParticlepTVsMaxJetpTJP2 = new TH2F("htransMin_sumParticlepTVsMaxJetpTJP2","transMin;  jet p_{T} [GeV]; <#Sigmap_{T,ch}>/[#Delta#eta#Delta(#Delta#phi)]",40,0,80,20,0,20);
 
  TH2F* haway_numParticlesVsMaxJetpTJP2 = new TH2F("haway_numParticlesVsMaxJetpTJP2","away; jet p_{T} [GeV]; <N_{ch}>/[#Delta#eta#Delta(#Delta#phi)]",40,0,80,20,0,20);
  TH2F* haway_sumParticlepTVsMaxJetpTJP2 = new TH2F("haway_sumParticlepTVsMaxJetpTJP2","away;  jet p_{T} [GeV]; <#Sigmap_{T,ch}>/[#Delta#eta#Delta(#Delta#phi)]",40,0,80,20,0,20);
 
  TH2F* htoward_numParticlesVsMaxJetpTJP2 = new TH2F("htoward_numParticlesVsMaxJetpTJP2","toward; jet p_{T} [GeV]; <N_{ch}>/[#Delta#eta#Delta(#Delta#phi)]",40,0,80,20,0,20);
  TH2F* htoward_sumParticlepTVsMaxJetpTJP2 = new TH2F("htoward_sumParticlepTVsMaxJetpTJP2","toward;  jet p_{T} [GeV]; <#Sigmap_{T,ch}>/[#Delta#eta#Delta(#Delta#phi)]",40,0,80,20,0,20);

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

Bool_t trigPass(StJetSkimTrig* trig, Int_t mEmbed){
  if (trig){
    if (trig->didFire() || mEmbed == 1 ){
      if (trig->shouldFire() == 1) return true;
    }
  }
  return false;
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

Bool_t matchedToJetPatch(const StJetCandidate* jethold,
					       const map<int,int>& barrelJetPatches){

  for (map<int,int>::const_iterator it = barrelJetPatches.begin(); it != barrelJetPatches.end(); ++it) {
    int id = it->first;
    int adc = it->second;
    float eta, phi;
    assert(StJetCandidate::getBarrelJetPatchEtaPhi(id,eta,phi));
    float deta = jethold->detEta() - eta;
    float dphi = TVector2::Phi_mpi_pi(jethold->phi() - phi);
    if (fabs(deta) < 0.6 && fabs(dphi) < 0.6) return true;
  }
 
  return false;
}


Bool_t hightrackpT(StJetCandidate *leadingjet){
  Int_t trackThresh = 30;
  for(int iTrack = 0;  iTrack < leadingjet->numberOfTracks(); iTrack++ ){
    StJetTrack *track = leadingjet->track(iTrack);
    if(track->pt() > trackThresh){ cout << "track pT > 30 GeV " << track->pt() <<  endl; return true;}
  }
  return false;
}
void defineTransMaxMin(float value_P, float value_M){
  
  if(value_P > value_M){
  }
  if(value_P < value_M){
  }
}
