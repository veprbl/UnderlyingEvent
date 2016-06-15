/* 
This runs the over the jet, skim, ue trees. Fills histograms. This is a stream lined
version Reducing the number of histograms to just the sum and num towers and tracks vs jet pT.
Check out oldMacros_sumTrackpT/*.C for finding many other histograms made
 */

#include <algorithm>
#include <iostream>
#include <map>

#include <TMath.h>
#include <TChain.h>
#include <TH2F.h>
#include <TSystem.h>
#include <TFile.h>

#include <StSpinPool/StJetEvent/StJetTrack.h>
#include <StSpinPool/StJetEvent/StJetVertex.h>
#include <StSpinPool/StJetEvent/StJetCandidate.h>
#include <StSpinPool/StJetEvent/StJetEvent.h>
#include <StSpinPool/StJetEvent/StJetTower.h>
#include <StSpinPool/StJetEvent/StJetParticle.h>
#include <StSpinPool/StJetEvent/StUeEvent.h>
#include <StSpinPool/StJetSkimEvent/StJetSkimEvent.h>

using std::cout;
using std::endl;

Bool_t vertexPass(StJetVertex *vertex, StJetVertex *ue_vertex);
Bool_t trigPass(StJetSkimTrig* trig, Int_t mEmbed);
StJetCandidate* findLeadingJet(StJetVertex* vertex);
Bool_t matchedToJetPatch(const StJetCandidate* jethold, const map<int,int>& barrelJetPatches);
Bool_t hightrackpT(StJetCandidate *leadingjet);

void RunUEAnalysis(int nentries = 1E3,
		   const char* jetfile  = "/gpfs01/star/i_bnl/gdwebb/Run9/500GeVJets/Data/10103041/st_physics_10103041_raw_*.jets.root",
		   const char* skimfile = "/gpfs01/star/i_bnl/gdwebb/Run9/500GeVJets/Data/10103041/st_physics_10103041_raw_*.skim.root",
		   const char* uefile = "/gpfs01/star/i_bnl/gdwebb/Run9/500GeVJets/Data/10103041/st_physics_10103041_raw_*.ue.root",
		   const char* outfile = "test_jetQAData500Gev_10103041.root",
		   const Int_t  mEmbed = 0)
{
  cout << "nentries = " << nentries << endl;
  cout << "jetfile  = " << jetfile  << endl;
  cout << "skimfile = " << skimfile << endl;
  cout << "uefile   = " << uefile << endl;
  cout << "outfile  = " << outfile << endl;
  const float area  =  4*TMath::Pi()/3;
  const float area2 =  2*TMath::Pi()/3;

  cout << "area: " << area << endl;

  // Open jet & skim files
  TChain* jetChain  = new TChain("jet");
  TChain* skimChain = new TChain("jetSkimTree");
  TChain* ueChain   = new TChain("ue");

  jetChain->Add(jetfile);
  skimChain->Add(skimfile);
  ueChain->Add(uefile);
  
  // Set jet buffer
  StJetEvent* jetEvent = 0;
  jetChain->SetBranchAddress("AntiKtR060NHits12",&jetEvent);

  // Set skim buffer
  StJetSkimEvent* skimEvent = 0;
  skimChain->SetBranchAddress("skimEventBranch",&skimEvent); 

  StUeEvent* ueEvent_transP = 0;
  ueChain->SetBranchAddress("transP_AntiKtR060NHits12",&ueEvent_transP);

  StUeEvent* ueEvent_transM = 0;
  ueChain->SetBranchAddress("transM_AntiKtR060NHits12",&ueEvent_transM);

  StUeEvent* ueEvent_away = 0;
  ueChain->SetBranchAddress("away_AntiKtR060NHits12",&ueEvent_away);

  StUeEvent* ueEvent_toward = 0;
  ueChain->SetBranchAddress("toward_AntiKtR060NHits12",&ueEvent_toward);

  // Open output file for writing
  TFile* ofile = TFile::Open(outfile,"recreate");
  assert(ofile);

  //Book histograms
  TH1F* hleadingjetpTJP2 = new TH1F("hleadingjetpTJP2",";Leading jet p_{T} [GeV]",40,0,80);

  //Event Histograms
  TH2F* htransP_numTracksVsMaxJetpTJP2 = new TH2F("htransP_numTracksVsMaxJetpTJP2","transP; jet p_{T} [GeV]; <N_{ch}>/[#Delta#eta#Delta(#Delta#phi)]",40,0,80,80,0.,20.);
  TH2F* htransP_sumTrackpTVsMaxJetpTJP2 = new TH2F("htransP_sumTrackpTVsMaxJetpTJP2","transP;  jet p_{T} [GeV]; <#Sigmap_{T,ch}>/[#Delta#eta#Delta(#Delta#phi)]",40,0,80,80,0.,20.);

  TH2F* htransP_numTowersVsMaxJetpTJP2 = new TH2F("htransP_numTowersVsMaxJetpTJP2","transP; jet p_{T} [GeV]; <N_{0}>/[#Delta#eta#Delta(#Delta#phi)]",40,0,80,80,0.,20.);
  TH2F* htransP_sumTowerEtVsMaxJetpTJP2 = new TH2F("htransP_sumTowerEtVsMaxJetpTJP2","transP;  jet p_{T} [GeV]; <#SigmaE_{T}>/[#Delta#eta#Delta(#Delta#phi)]",40,0,80,80,0.,20.);
  TH2F* htransP_sumPtVsMaxJetpTJP2 = new TH2F("htransP_sumPtVsMaxJetpTJP2","transP; jet p_{T} [GeV]; <#Sigmap_{T}>/[#Delta#eta#Delta(#Delta#phi)]",40,0,80,80,0.,20.);

  TH2F* htransM_numTracksVsMaxJetpTJP2 = new TH2F("htransM_numTracksVsMaxJetpTJP2","transM; jet p_{T} [GeV]; <N_{ch}>/[#Delta#eta#Delta(#Delta#phi)]",40,0,80,80,0.,20.);
  TH2F* htransM_sumTrackpTVsMaxJetpTJP2 = new TH2F("htransM_sumTrackpTVsMaxJetpTJP2","transM;  jet p_{T} [GeV]; #Sigmatrack p_{T}",40,0,80,80,0.,20.);

  TH2F* htransM_numTowersVsMaxJetpTJP2 = new TH2F("htransM_numTowersVsMaxJetpTJP2","transM; jet p_{T} [GeV]; <N_{0}>/[#Delta#eta#Delta(#Delta#phi)]",40,0,80,80,0.,20.);
  TH2F* htransM_sumTowerEtVsMaxJetpTJP2 = new TH2F("htransM_sumTowerEtVsMaxJetpTJP2","transM;  jet p_{T} [GeV]; <#SigmaE_{T}>/[#Delta#eta#Delta(#Delta#phi)]",40,0,80,80,0.,20.);
  TH2F* htransM_sumPtVsMaxJetpTJP2 = new TH2F("htransM_sumPtVsMaxJetpTJP2","transM; jet p_{T} [GeV]; <#Sigmap_{T}>/[#Delta#eta#Delta(#Delta#phi)]",40,0,80,80,0.,20.);

  TH2F* htransverse_numTracksVsMaxJetpTJP2 = new TH2F("htransverse_numTracksVsMaxJetpTJP2","transverse; jet p_{T} [GeV]; <N_{ch}>/[#Delta#eta#Delta(#Delta#phi)]",40,0,80,80,0.,20.);
  TH2F* htransverse_sumTrackpTVsMaxJetpTJP2 = new TH2F("htransverse_sumTrackpTVsMaxJetpTJP2","transverse; jet p_{T} [GeV]; #Sigmatrack p_{T}",40,0,80,80,0.,20.);

  TH2F* htransverse_numTowersVsMaxJetpTJP2 = new TH2F("htransverse_numTowersVsMaxJetpTJP2","transverse; jet p_{T} [GeV]; <N_{0}>/[#Delta#eta#Delta(#Delta#phi)]",40,0,80,80,0.,20.);
  TH2F* htransverse_sumTowerEtVsMaxJetpTJP2 = new TH2F("htransverse_sumTowerEtVsMaxJetpTJP2","transverse; jet p_{T} [GeV]; <#SigmaE_{T}>/[#Delta#eta#Delta(#Delta#phi)]",40,0,80,80,0.,20.);
  TH2F* htransverse_sumPtVsMaxJetpTJP2 = new TH2F("htransverse_sumPtVsMaxJetpTJP2","transverse; jet p_{T} [GeV]; <#Sigmap_{T}>/[#Delta#eta#Delta(#Delta#phi)]",40,0,80,80,0.,20.);

  TH2F* htransMax_numTracksVsMaxJetpTJP2 = new TH2F("htransMax_numTracksVsMaxJetpTJP2","transMax; jet p_{T} [GeV]; <N_{ch}>/[#Delta#eta#Delta(#Delta#phi)]",40,0,80,80,0.,20.);
  TH2F* htransMax_sumTrackpTVsMaxJetpTJP2 = new TH2F("htransMax_sumTrackpTVsMaxJetpTJP2","transMax;  jet p_{T} [GeV]; <#Sigmap_{T,ch}>/[#Delta#eta#Delta(#Delta#phi)]",40,0,80,80,0.,20.);

  TH2F* htransMax_numTowersVsMaxJetpTJP2 = new TH2F("htransMax_numTowersVsMaxJetpTJP2","transMax; jet p_{T} [GeV]; <N_{0}>/[#Delta#eta#Delta(#Delta#phi)]",40,0,80,80,0.,20.);
  TH2F* htransMax_sumTowerEtVsMaxJetpTJP2 = new TH2F("htransMax_sumTowerEtVsMaxJetpTJP2","transMax;  jet p_{T} [GeV]; <#SigmaE_{T}>/[#Delta#eta#Delta(#Delta#phi)]",40,0,80,80,0.,20.);

  TH2F* htransMin_numTracksVsMaxJetpTJP2 = new TH2F("htransMin_numTracksVsMaxJetpTJP2","transMin; jet p_{T} [GeV]; <N_{ch}>/[#Delta#eta#Delta(#Delta#phi)]",40,0,80,80,0.,20.);
  TH2F* htransMin_sumTrackpTVsMaxJetpTJP2 = new TH2F("htransMin_sumTrackpTVsMaxJetpTJP2","transMin;  jet p_{T} [GeV]; <#Sigmap_{T,ch}>/[#Delta#eta#Delta(#Delta#phi)]",40,0,80,80,0.,20.);

  TH2F* htransMin_numTowersVsMaxJetpTJP2 = new TH2F("htransMin_numTowersVsMaxJetpTJP2","transMin; jet p_{T} [GeV]; <N_{0}>/[#Delta#eta#Delta(#Delta#phi)]",40,0,80,80,0.,20.);
  TH2F* htransMin_sumTowerEtVsMaxJetpTJP2 = new TH2F("htransMin_sumTowerEtVsMaxJetpTJP2","transMin;  jet p_{T} [GeV]; <#SigmaE_{T}>/[#Delta#eta#Delta(#Delta#phi)]",40,0,80,80,0.,20.);

  TH2F* htransMax_sumpTVsMaxJetpTJP2 = new TH2F("htransMax_sumpTVsMaxJetpTJP2", "transMax; jet p_{T} [GeV]; <#Sigmap_{T}>/[#Delta#eta#Delta(#Delta#phi)]",40,0,80,80,0.,20.);
  TH2F* htransMin_sumpTVsMaxJetpTJP2 = new TH2F("htransMin_sumpTVsMaxJetpTJP2", "transMin; jet p_{T} [GeV]; <#Sigmap_{T}>/[#Delta#eta#Delta(#Delta#phi)]",40,0,80,80,0.,20.);

  TH2F* haway_numTracksVsMaxJetpTJP2 = new TH2F("haway_numTracksVsMaxJetpTJP2","away; jet p_{T} [GeV]; <N_{ch}>/[#Delta#eta#Delta(#Delta#phi)]",40,0,80,80,0.,20.);
  TH2F* haway_sumTrackpTVsMaxJetpTJP2 = new TH2F("haway_sumTrackpTVsMaxJetpTJP2","away;  jet p_{T} [GeV]; <#Sigmap_{T,ch}>/[#Delta#eta#Delta(#Delta#phi)]",40,0,80,80,0.,20.);

  TH2F* haway_numTowersVsMaxJetpTJP2 = new TH2F("haway_numTowersVsMaxJetpTJP2","away; jet p_{T} [GeV]; <N_{0}>/[#Delta#eta#Delta(#Delta#phi)]",40,0,80,80,0.,20.);
  TH2F* haway_sumTowerEtVsMaxJetpTJP2 = new TH2F("haway_sumTowerEtVsMaxJetpTJP2","away;  jet p_{T} [GeV]; <#SigmaE_{T}>/[#Delta#eta#Delta(#Delta#phi)]",40,0,80,80,0.,20.);
  TH2F* haway_sumPtVsMaxJetpTJP2 = new TH2F("haway_sumPtVsMaxJetpTJP2","away; jet p_{T} [GeV]; <#Sigmap_{T}>/[#Delta#eta#Delta(#Delta#phi)]",40,0,80,80,0.,20.);

  TH2F* htoward_numTracksVsMaxJetpTJP2 = new TH2F("htoward_numTracksVsMaxJetpTJP2","toward; jet p_{T} [GeV]; <N_{ch}>/[#Delta#eta#Delta(#Delta#phi)]",40,0,80,80,0.,20.);
  TH2F* htoward_sumTrackpTVsMaxJetpTJP2 = new TH2F("htoward_sumTrackpTVsMaxJetpTJP2","toward;  jet p_{T} [GeV]; <#Sigmap_{T,ch}>/[#Delta#eta#Delta(#Delta#phi)]",40,0,80,80,0.,20.);

  TH2F* htoward_numTowersVsMaxJetpTJP2 = new TH2F("htoward_numTowersVsMaxJetpTJP2","toward; jet p_{T} [GeV]; <N_{0}>/[#Delta#eta#Delta(#Delta#phi)]",40,0,80,80,0.,20.);
  TH2F* htoward_sumTowerEtVsMaxJetpTJP2 = new TH2F("htoward_sumTowerEtVsMaxJetpTJP2","toward;  jet p_{T} [GeV]; <#SigmaE_{T}>/[#Delta#eta#Delta(#Delta#phi)]",40,0,80,80,0.,20.);
  TH2F* htoward_sumPtVsMaxJetpTJP2 = new TH2F("htoward_sumPtVsMaxJetpTJP2","toward; jet p_{T} [GeV]; <#Sigmap_{T}>/[#Delta#eta#Delta(#Delta#phi)]",40,0,80,80,0.,20.);

  Float_t sumtrackpT_transP, sumtowerEt_transP, sumpT_transP, sumtrackpT_transM, sumtowerEt_transM, sumpT_transM;
  Float_t numtracks_transP, numtowers_transP, numtracks_transM, numtowers_transM;
  Float_t sumtrackpT_transMax, sumtowerEt_transMax,sumpT_transMax, sumtrackpT_transMin, sumtowerEt_transMin, sumpT_transMin;
  Float_t numtracks_transMax, numtowers_transMax, numtracks_transMin, numtowers_transMin;
  Float_t sumtowerEt_away, sumtrackpT_away, sumpT_away, sumtrackpT_toward, sumtowerEt_toward, sumpT_toward;
  Float_t numtowers_away, numtracks_away, numtracks_toward, numtowers_toward;
  Float_t leadingJetpT;

  for (int iEntry = 0; iEntry < nentries; ++iEntry) {
    if (jetChain->GetEvent(iEntry) <= 0 || skimChain->GetEvent(iEntry) <= 0 || ueChain->GetEvent(iEntry) <= 0) break;
    // Should not be null
    assert(jetEvent && skimEvent && ueEvent_transP);
    
    // Enforce event synchronization
    assert(jetEvent->runId() == skimEvent->runId() && jetEvent->eventId() == skimEvent->eventId());
    assert(jetEvent->runId() == ueEvent_transP->runId() && jetEvent->eventId() == ueEvent_transP->eventId());
    
    if (iEntry % 1000 == 0) cout << iEntry << endl;
    //   hrunnumber->Fill(jetEvent->runId());
  
    //JP2 trigger
    StJetSkimTrig* trigJP2 = skimEvent->trigger(370621);
    if (!trigJP2) trigJP2 = skimEvent->trigger(230411);
    bool flagtrigJP2 = trigPass(trigJP2, mEmbed); // hardware and software triggers
    map<int,int> barrelJetPatches = skimEvent->barrelJetPatchesAboveTh(2);
    
    StJetVertex* vertex = jetEvent->vertex();
    StJetVertex* ue_vertex = ueEvent_transP->vertex();
    bool vertexBool = vertexPass(vertex, ue_vertex);
    if(!vertexBool) continue;
    
    StJetCandidate *leadingjet = findLeadingJet(vertex); // Leading jet from jet 
    if(leadingjet->pt() != ueEvent_transP->leadingJetpt()) continue;
    if(TMath::Abs(leadingjet->detEta()) > 0.5) { continue;}
    if(leadingjet->rt() > 0.9){continue;} 
    bool trackpT_high = hightrackpT(leadingjet);
    if(trackpT_high) continue;
    
    Bool_t geoFlagJP2  = matchedToJetPatch(leadingjet,barrelJetPatches); // Geo Flag

    leadingJetpT = leadingjet->pt(); //Define the leading jet pT 
    if( flagtrigJP2 && geoFlagJP2){//did, should, and geo trigs fired 

      hleadingjetpTJP2->Fill(leadingJetpT); 
      
      //-----------------Transverse Plus ------------------------
      sumtrackpT_transP = ueEvent_transP->sumTrackPt();
      sumtowerEt_transP = ueEvent_transP->sumTowerPt();
      sumpT_transP      = ueEvent_transP->sumPt();

      numtracks_transP = ueEvent_transP->numberOfTracks();
      numtowers_transP = ueEvent_transP->numberOfTowers();

      //track transP
      htransP_numTracksVsMaxJetpTJP2->Fill(leadingJetpT,numtracks_transP/area2);
      htransP_sumTrackpTVsMaxJetpTJP2->Fill(leadingJetpT,sumtrackpT_transP/area2);

      //tower transP
      htransP_numTowersVsMaxJetpTJP2->Fill(leadingJetpT,numtowers_transP/area2);
      htransP_sumTowerEtVsMaxJetpTJP2->Fill(leadingJetpT,sumtowerEt_transP/area2);

      htransP_sumPtVsMaxJetpTJP2->Fill(leadingJetpT, sumpT_transP/area2);
      // ------------------- End Of Trans Plus --------------------------

      //-----------------Transverse Minus ------------------------
      sumtrackpT_transM = ueEvent_transM->sumTrackPt();
      sumtowerEt_transM = ueEvent_transM->sumTowerPt(); 
      sumpT_transM      = ueEvent_transM->sumPt();

      numtracks_transM = ueEvent_transM->numberOfTracks();
      numtowers_transM = ueEvent_transM->numberOfTowers();
      
      //track transM
      htransM_numTracksVsMaxJetpTJP2->Fill(leadingJetpT,numtracks_transM/area2);
      htransM_sumTrackpTVsMaxJetpTJP2->Fill(leadingJetpT,sumtrackpT_transM/area2);
      
      //tower transM
      htransM_numTowersVsMaxJetpTJP2->Fill(leadingJetpT,numtowers_transM/area2);
      htransM_sumTowerEtVsMaxJetpTJP2->Fill(leadingJetpT,sumtowerEt_transM/area2);

      htransM_sumPtVsMaxJetpTJP2->Fill(leadingJetpT, sumpT_transM/area2);
      // ------------------- End Of Trans Minus --------------------------
      
      //----------------Transverse Region------------------------

      //track transverse
      htransverse_numTracksVsMaxJetpTJP2->Fill(leadingJetpT,(numtracks_transP + numtracks_transM)/area);
      htransverse_sumTrackpTVsMaxJetpTJP2->Fill(leadingJetpT,(sumtrackpT_transP + sumtrackpT_transM)/area);
      
      //tower transverse
      htransverse_numTowersVsMaxJetpTJP2->Fill(leadingJetpT,(numtowers_transP + numtowers_transM)/area);
      htransverse_sumTowerEtVsMaxJetpTJP2->Fill(leadingJetpT,(sumtowerEt_transP + sumtowerEt_transM)/area);

      htransverse_sumPtVsMaxJetpTJP2->Fill(leadingJetpT, (sumpT_transP + sumpT_transM)/area);

      //--------------End of Transverse-------------------------      
      //----------------- Away Region ------------------------
      sumtrackpT_away = sumtowerEt_away = 0; 
      numtracks_away = numtowers_away = 0; 
      sumpT_away = 0;

      sumtrackpT_away = ueEvent_away->sumTrackPt();
      sumtowerEt_away = ueEvent_away->sumTowerPt(); 
      sumpT_away      = ueEvent_away->sumPt();
     
      numtracks_away = ueEvent_away->numberOfTracks();
      numtowers_away = ueEvent_away->numberOfTowers();
      
      //track away
      haway_numTracksVsMaxJetpTJP2->Fill(leadingJetpT,numtracks_away/area);
      haway_sumTrackpTVsMaxJetpTJP2->Fill(leadingJetpT,sumtrackpT_away/area);
      
      //tower away
      haway_numTowersVsMaxJetpTJP2->Fill(leadingJetpT,numtowers_away/area);
      haway_sumTowerEtVsMaxJetpTJP2->Fill(leadingJetpT,sumtowerEt_away/area);

      haway_sumPtVsMaxJetpTJP2->Fill(leadingJetpT,sumpT_away/area);
      // ------------------- End Of Away --------------------------

      //----------------- Toward Region ---------------------------
      sumtrackpT_toward = sumtowerEt_toward = 0;      
      numtracks_toward  = numtowers_toward  = 0;      
      sumpT_toward = 0;

      sumtrackpT_toward = ueEvent_toward->sumTrackPt();
      sumtowerEt_toward = ueEvent_toward->sumTowerPt(); 
      sumpT_toward      = ueEvent_toward->sumPt();

      numtracks_toward = ueEvent_toward->numberOfTracks();
      numtowers_toward = ueEvent_toward->numberOfTowers(); 

      //track toward
      htoward_numTracksVsMaxJetpTJP2->Fill(leadingJetpT,numtracks_toward/area);
      htoward_sumTrackpTVsMaxJetpTJP2->Fill(leadingJetpT,sumtrackpT_toward/area);
      
      //tower toward
      htoward_numTowersVsMaxJetpTJP2->Fill(leadingJetpT,numtowers_toward/area);
      htoward_sumTowerEtVsMaxJetpTJP2->Fill(leadingJetpT,sumtowerEt_toward/area);

      htoward_sumPtVsMaxJetpTJP2->Fill(leadingJetpT, sumpT_toward/area);
      // ------------------- End Of Toward --------------------------
      
    
      //--------- Sum Track pT Trans Max and Trans Min -------------
      if (sumtrackpT_transP == sumtrackpT_transM) {
         cout << "sumtrackpT_transP = " << sumtrackpT_transP << "\t"
              << "sumtrackpT_transM = " << sumtrackpT_transM << endl;
      }
      sumtrackpT_transMax =  std::max(sumtrackpT_transP, sumtrackpT_transM);
      sumtrackpT_transMin =  std::min(sumtrackpT_transP, sumtrackpT_transM);

      htransMax_sumTrackpTVsMaxJetpTJP2->Fill(leadingJetpT,sumtrackpT_transMax/area2);
      htransMin_sumTrackpTVsMaxJetpTJP2->Fill(leadingJetpT,sumtrackpT_transMin/area2);     
      //---------------------------------------------------      
      

      //--------- Num Tracks Trans Max and Trans Min -------------
      if (numtracks_transP == numtracks_transM) {
         cout << "numtracks_transP = " << numtracks_transP << "\t"
              << "numtracks_transM = " << numtracks_transM << endl;
      }
      numtracks_transMax = std::max(numtracks_transP, numtracks_transM);
      numtracks_transMin = std::min(numtracks_transP, numtracks_transM);
      
      htransMax_numTracksVsMaxJetpTJP2->Fill(leadingJetpT,numtracks_transMax/area2);
      htransMin_numTracksVsMaxJetpTJP2->Fill(leadingJetpT,numtracks_transMin/area2);
      // -----------------------------------------------------------
    
      //--------- Sum Tower Et Trans Max and Trans Min -------------
      if (sumtowerEt_transP == sumtowerEt_transM) {
         cout << "sumtowerEt_transP = " << sumtowerEt_transP << "\t"
              << "sumtowerEt_transM = " << sumtowerEt_transM << endl;
      }
      sumtowerEt_transMax = std::max(sumtowerEt_transP, sumtowerEt_transM);
      sumtowerEt_transMin = std::min(sumtowerEt_transP, sumtowerEt_transM);

      htransMax_sumTowerEtVsMaxJetpTJP2->Fill(leadingJetpT,sumtowerEt_transMax/area2);
      htransMin_sumTowerEtVsMaxJetpTJP2->Fill(leadingJetpT,sumtowerEt_transMin/area2);
      //----------------------------------------------------------

      //--------- Num Towers Trans Max and Trans Min -------------
      if (numtowers_transP == numtowers_transM) {
         cout << "numtowers_transP = " << numtowers_transP << "\t"
              << "numtowers_transM = " << numtowers_transM << endl;
      }
      numtowers_transMax = std::max(numtowers_transP, numtowers_transM);
      numtowers_transMin = std::min(numtowers_transP, numtowers_transM);

      htransMax_numTowersVsMaxJetpTJP2->Fill(leadingJetpT,numtowers_transMax/area2);
      htransMin_numTowersVsMaxJetpTJP2->Fill(leadingJetpT,numtowers_transMin/area2);
      // -------------------------------------------------------


      //--------- Sum pT Trans Max and Trans Min -------------
      if (sumpT_transP == sumpT_transM) {
         cout << "sumpT_transP = " << sumpT_transP << "\t"
              << "sumpT_transM = " << sumpT_transM << endl;
      }
      sumpT_transMax = std::max(sumpT_transP, sumpT_transM);
      sumpT_transMin = std::min(sumpT_transP, sumpT_transM);

      htransMax_sumpTVsMaxJetpTJP2->Fill(leadingJetpT,sumpT_transMax/area2);
      htransMin_sumpTVsMaxJetpTJP2->Fill(leadingJetpT,sumpT_transMin/area2);     
      //---------------------------------------------------      
      
    }// End of JP2 if statement 
  }//End of Event Loop
  ofile->Write();
  ofile->Close();
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
