class StJetCandidate;
class StJetVertex;
class StJetSkimTrig;

#include <map>
// Up,Up = 5; Down,Up = 6; Up,Down=9; Down,Down=10; Spin Bits
void RunSpinUEAnalysis(int nentries = 1e9,
		   const char* jetfile  = "/gpfs01/star/i_bnl/gdwebb/Run9/500GeVJets/Data/10101081/st_physics_10101081_raw_4020001.jets.root",
		   const char* skimfile = "/gpfs01/star/i_bnl/gdwebb/Run9/500GeVJets/Data/10101081/st_physics_10101081_raw_4020001.skim.root",
		   const char* uefile = "/gpfs01/star/i_bnl/gdwebb/Run9/500GeVJets/Data/10101081/st_physics_10101081_raw_4020001.ue.root ",
		   const char* outfile = "testspin_Datajet500Gev_10101081_raw_4020001.root",
		   const Int_t  mEmbed = 0)
{
  cout << "nentries = " << nentries << endl;
  cout << "jetfile  = " << jetfile  << endl;
  cout << "skimfile = " << skimfile << endl;
  cout << "uefile   = " << uefile << endl;
  cout << "outfile  = " << outfile << endl;

  // Load libraries
  gSystem->Load("StJetEvent");
  gSystem->Load("StJetSkimEvent");

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


  StUeEvent *ueEvent_transMax = 0;
  StUeEvent *ueEvent_transMin = 0;

  // Open output file for writing
  TFile* ofile = TFile::Open(outfile,"recreate");
  assert(ofile);

  BookHists();

  Float_t sumtrackpT_transP, sumtrackpT_transM;

  //  Float_t sumtrackpT_transP_spinbit6, sumtowerEt_transP_spinbit6, sumtrackpT_transM_spinbit6, sumtowerEt_transM_spinbit6;
  // Float_t sumtrackpT_transP_spinbit9, sumtowerEt_transP_spinbit9, sumtrackpT_transM_spinbit9, sumtowerEt_transM_spinbit9;
  //Float_t sumtrackpT_transP_spinbit10, sumtowerEt_transP_spinbit10, sumtrackpT_transM_spinbit10, sumtowerEt_transM_spinbit10;

  Float_t sumtrackpT_transMax, sumtowerEt_transMax, sumtrackpT_transMin, sumtowerEt_transMin;
  Float_t sumtrackpT_transMax_spinbit5, sumtowerEt_transMax_spinbit5, sumtrackpT_transMin_spinbit5, sumtowerEt_transMin_spinbit5;
  Float_t sumtrackpT_transMax_spinbit6, sumtowerEt_transMax_spinbit6, sumtrackpT_transMin_spinbit6, sumtowerEt_transMin_spinbit6;
  Float_t sumtrackpT_transMax_spinbit9, sumtowerEt_transMax_spinbit9, sumtrackpT_transMin_spinbit9, sumtowerEt_transMin_spinbit9;
  Float_t sumtrackpT_transMax_spinbit10, sumtowerEt_transMax_spinbit10, sumtrackpT_transMin_spinbit10, sumtowerEt_transMin_spinbit10;

  Float_t avetrackpT_transMax, avetowerEt_transMax, avetrackpT_transMin, avetowerEt_transMin;
  Float_t avetrackpT_transMax_spinbit5, avetowerEt_transMax_spinbit5, avetrackpT_transMin_spinbit5, avetowerEt_transMin_spinbit5;
  Float_t avetrackpT_transMax_spinbit6, avetowerEt_transMax_spinbit6, avetrackpT_transMin_spinbit6, avetowerEt_transMin_spinbit6;
  Float_t avetrackpT_transMax_spinbit9, avetowerEt_transMax_spinbit9, avetrackpT_transMin_spinbit9, avetowerEt_transMin_spinbit9;
  Float_t avetrackpT_transMax_spinbit10, avetowerEt_transMax_spinbit10, avetrackpT_transMin_spinbit10, avetowerEt_transMin_spinbit10;

  Float_t maxtrackpT_transMax, maxtrackpT_transMin;
  Float_t maxtrackpT_transMax_spinbit5, maxtrackpT_transMin_spinbit5;
  Float_t maxtrackpT_transMax_spinbit6, maxtrackpT_transMin_spinbit6;
  Float_t maxtrackpT_transMax_spinbit9, maxtrackpT_transMin_spinbit9;
  Float_t maxtrackpT_transMax_spinbit10, maxtrackpT_transMin_spinbit10;

  Float_t maxtowerEt_transMax, maxtowerEt_transMin;
  Float_t maxtowerEt_transMax_spinbit5, maxtowerEt_transMin_spinbit5;
  Float_t maxtowerEt_transMax_spinbit6, maxtowerEt_transMin_spinbit6;
  Float_t maxtowerEt_transMax_spinbit9, maxtowerEt_transMin_spinbit9;
  Float_t maxtowerEt_transMax_spinbit10, maxtowerEt_transMin_spinbit10;

  Float_t mintrackpT_transMax, mintrackpT_transMin;
  Float_t mintrackpT_transMax_spinbit5, mintrackpT_transMin_spinbit5;
  Float_t mintrackpT_transMax_spinbit6, mintrackpT_transMin_spinbit6;
  Float_t mintrackpT_transMax_spinbit9, mintrackpT_transMin_spinbit9;
  Float_t mintrackpT_transMax_spinbit10, mintrackpT_transMin_spinbit10;

  Float_t mintowerEt_transMax, mintowerEt_transMin;
  Float_t mintowerEt_transMax_spinbit5, mintowerEt_transMin_spinbit5;
  Float_t mintowerEt_transMax_spinbit6, mintowerEt_transMin_spinbit6;
  Float_t mintowerEt_transMax_spinbit9, mintowerEt_transMin_spinbit9;
  Float_t mintowerEt_transMax_spinbit10, mintowerEt_transMin_spinbit10;

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
    StJetSkimTrig* trigJP2 = skimEvent->trigger(230411);
    if (!trigJP2) trigJP2 = skimEvent->trigger(230411);
    bool flagtrigJP2 = trigPass(trigJP2, mEmbed); // hardware and software triggers
    
    map<int,int> barrelJetPatches = skimEvent->barrelJetPatchesAboveTh(2);
    
    StJetVertex* vertex = jetEvent->vertex();
    StJetVertex* ue_vertex = ueEvent_transP->vertex();
    bool vertexBool = vertexPass(vertex, ue_vertex);
    if(!vertexBool) continue;
    
    StJetCandidate *leadingjet = findLeadingJet(vertex); // Leading jet from jet Trees
    if(leadingjet->pt() != ueEvent_transP->leadingJetpt()) continue;
    if(TMath::Abs(leadingjet->detEta()) > 0.5) { continue;}
    if(leadingjet->rt() > 0.9){  continue;} 
    bool trackpT_high = hightrackpT(leadingjet);
    if(trackpT_high) continue;
    
    Bool_t geoFlagJP2  = matchedToJetPatch(leadingjet,barrelJetPatches); // Geo Flag
    Int_t spin4bit  =  skimEvent->spin4usingBx48();
    if( flagtrigJP2 && geoFlagJP2){//did, should, and geo trigs fired 

      hleadingjetpTJP2->Fill(leadingjet->pt());

      //-------Summing the track pT for the Plus and Minus Regions------------
      sumtrackpT_transP = 0;
      for (int iTrack = 0; iTrack < ueEvent_transP->numberOfTracks(); iTrack++){
	StJetTrack* track_transP = ueEvent_transP->track(iTrack);
	sumtrackpT_transP = sumtrackpT_transP + track_transP->pt();
      }
      sumtrackpT_transM = 0;
      for (int iTrack = 0; iTrack < ueEvent_transM->numberOfTracks(); iTrack++){
	StJetTrack* track_transM = ueEvent_transM->track(iTrack);
	sumtrackpT_transM = sumtrackpT_transM + track_transM->pt();
      }
      //---------------------------------------------------------------------

	// ------------------  Defining TransMax and TransMin --------------------
      if(sumtrackpT_transP > sumtrackpT_transM){
	ueEvent_transMax = ueEvent_transP;
	ueEvent_transMin = ueEvent_transM;
      }
      if(sumtrackpT_transP < sumtrackpT_transM){
	ueEvent_transMax = ueEvent_transM;
	ueEvent_transMin = ueEvent_transP;
      }
      // ------------------ End of TransMax/TransMin Definition ---------------   

      //-----------------Transverse Max ------------------------
      sumtrackpT_transMax = sumtowerEt_transMax = 0; 
      avetrackpT_transMax = avetowerEt_transMax = 0;
      maxtrackpT_transMax = maxtowerEt_transMax = 0;
      mintrackpT_transMax = mintowerEt_transMax = 100;
      for (int iTrack = 0; iTrack < ueEvent_transMax->numberOfTracks(); iTrack++)
	{
	  StJetTrack* track_transMax = ueEvent_transMax->track(iTrack);
	  htransMax_trackpTJP2->Fill(track_transMax->pt());
	  htransMax_tracketaJP2->Fill(track_transMax->eta());
	  htransMax_trackphiJP2->Fill(track_transMax->phi());
	  sumtrackpT_transMax = sumtrackpT_transMax + track_transMax->pt();
	  if(maxtrackpT_transMax < track_transMax->pt()){maxtrackpT_transMax = track_transMax->pt();} 
	  if(mintrackpT_transMax > track_transMax->pt()){mintrackpT_transMax = track_transMax->pt();} 
	}//End of Track Loop
      
      for(int iTower = 0; iTower <  ueEvent_transMax->numberOfTowers(); iTower++)
	{
	  StJetTower* tower_transMax = ueEvent_transMax->tower(iTower);
	  htransMax_towerETJP2->Fill(tower_transMax->pt());
	  htransMax_toweretaJP2->Fill(tower_transMax->eta());
	  htransMax_towerphiJP2->Fill(tower_transMax->phi());
	  sumtowerEt_transMax = sumtowerEt_transMax + tower_transMax->pt(); 
	  if(maxtowerEt_transMax < tower_transMax->pt()){maxtowerEt_transMax = tower_transMax->pt();} 
	  if(mintowerEt_transMax > tower_transMax->pt()){mintowerEt_transMax = tower_transMax->pt();} 
	}// End of Tower Loop
      // ------------------- End Of Trans Max --------------------------
 
     //-----------------Transverse Max Spin Bit 5 ------------------------
      sumtrackpT_transMax_spinbit5 = sumtowerEt_transMax_spinbit5 = 0; 
      avetrackpT_transMax_spinbit5 = avetowerEt_transMax_spinbit5 = 0;
      maxtrackpT_transMax_spinbit5 = maxtowerEt_transMax_spinbit5 = 0;
      mintrackpT_transMax_spinbit5 = mintowerEt_transMax_spinbit5 = 100;
      if(skimEvent->spin4usingBx48() == 5 ) {
	for (int iTrack = 0; iTrack < ueEvent_transMax->numberOfTracks(); iTrack++)
	  {
	    StJetTrack* track_transMax = ueEvent_transMax->track(iTrack);
	    htransMax_trackpTJP2_spinbit5->Fill(track_transMax->pt());
	    htransMax_tracketaJP2_spinbit5->Fill(track_transMax->eta());
	    htransMax_trackphiJP2_spinbit5->Fill(track_transMax->phi());
	    sumtrackpT_transMax_spinbit5 = sumtrackpT_transMax_spinbit5 + track_transMax->pt();
	    if(maxtrackpT_transMax_spinbit5 < track_transMax->pt()){maxtrackpT_transMax_spinbit5 = track_transMax->pt();} 
	    if(mintrackpT_transMax_spinbit5 > track_transMax->pt()){mintrackpT_transMax_spinbit5 = track_transMax->pt();} 
	  }//End of Track Loop
	
	for(int iTower = 0; iTower < ueEvent_transMax->numberOfTowers(); iTower++)
	  {
	    StJetTower* tower_transMax = ueEvent_transMax->tower(iTower);
	    htransMax_towerETJP2_spinbit5->Fill(tower_transMax->pt());
	    htransMax_toweretaJP2_spinbit5->Fill(tower_transMax->eta());
	    htransMax_towerphiJP2_spinbit5->Fill(tower_transMax->phi());
	    sumtowerEt_transMax_spinbit5 = sumtowerEt_transMax_spinbit5 + tower_transMax->pt(); 
	    if(maxtowerEt_transMax_spinbit5 < tower_transMax->pt()){maxtowerEt_transMax_spinbit5 = tower_transMax->pt();} 
	    if(mintowerEt_transMax_spinbit5 > tower_transMax->pt()){mintowerEt_transMax_spinbit5 = tower_transMax->pt();} 
	  }// End of Tower Loop
      } // End of Spin Bit 5 If Statement 
	// ------------------- End Of Trans Max Spin Bit 5 --------------------------
      
      //-----------------Transverse Max Spin Bit 6 ------------------------
      sumtrackpT_transMax_spinbit6 = sumtowerEt_transMax_spinbit6 = 0; 
      avetrackpT_transMax_spinbit6 = avetowerEt_transMax_spinbit6 = 0;
      maxtrackpT_transMax_spinbit6 = maxtowerEt_transMax_spinbit6 = 0;
      mintrackpT_transMax_spinbit6 = mintowerEt_transMax_spinbit6 = 100;
      if(skimEvent->spin4usingBx48() == 6 ) {
	for (int iTrack = 0; iTrack < ueEvent_transMax->numberOfTracks(); iTrack++)
	  {
	    StJetTrack* track_transMax = ueEvent_transMax->track(iTrack);
	    htransMax_trackpTJP2_spinbit6->Fill(track_transMax->pt());
	    htransMax_tracketaJP2_spinbit6->Fill(track_transMax->eta());
	    htransMax_trackphiJP2_spinbit6->Fill(track_transMax->phi());
	    sumtrackpT_transMax_spinbit6 = sumtrackpT_transMax_spinbit6 + track_transMax->pt();
	    if(maxtrackpT_transMax_spinbit6 < track_transMax->pt()){maxtrackpT_transMax_spinbit6 = track_transMax->pt();} 
	    if(mintrackpT_transMax_spinbit6 > track_transMax->pt()){mintrackpT_transMax_spinbit6 = track_transMax->pt();} 
	  }//End of Track Loop
	
	for(int iTower = 0; iTower < ueEvent_transMax->numberOfTowers(); iTower++)
	  {
	    StJetTower* tower_transMax = ueEvent_transMax->tower(iTower);
	    htransMax_towerETJP2_spinbit6->Fill(tower_transMax->pt());
	    htransMax_toweretaJP2_spinbit6->Fill(tower_transMax->eta());
	    htransMax_towerphiJP2_spinbit6->Fill(tower_transMax->phi());
	    sumtowerEt_transMax_spinbit6 = sumtowerEt_transMax_spinbit6 + tower_transMax->pt(); 
	    if(maxtowerEt_transMax_spinbit6 < tower_transMax->pt()){maxtowerEt_transMax_spinbit6 = tower_transMax->pt();} 
	    if(mintowerEt_transMax_spinbit6 > tower_transMax->pt()){mintowerEt_transMax_spinbit6 = tower_transMax->pt();} 
	  }// End of Tower Loop
      } // End of Spin Bit 6 If Statement 
	// ------------------- End Of Trans Max Spin Bit 6--------------------------

      //-----------------Transverse Max Spin Bit 9 ------------------------
      sumtrackpT_transMax_spinbit9 = sumtowerEt_transMax_spinbit9 = 0; 
      avetrackpT_transMax_spinbit9 = avetowerEt_transMax_spinbit9 = 0;
      maxtrackpT_transMax_spinbit9 = maxtowerEt_transMax_spinbit9 = 0;
      mintrackpT_transMax_spinbit9 = mintowerEt_transMax_spinbit9 = 100;
      if(skimEvent->spin4usingBx48() == 9 ) {
	for (int iTrack = 0; iTrack < ueEvent_transMax->numberOfTracks(); iTrack++)
	  {
	    StJetTrack* track_transMax = ueEvent_transMax->track(iTrack);
	    htransMax_trackpTJP2_spinbit9->Fill(track_transMax->pt());
	    htransMax_tracketaJP2_spinbit9->Fill(track_transMax->eta());
	    htransMax_trackphiJP2_spinbit9->Fill(track_transMax->phi());
	    sumtrackpT_transMax_spinbit9 = sumtrackpT_transMax_spinbit9 + track_transMax->pt();
	    if(maxtrackpT_transMax_spinbit9 < track_transMax->pt()){maxtrackpT_transMax_spinbit9 = track_transMax->pt();} 
	    if(mintrackpT_transMax_spinbit9 > track_transMax->pt()){mintrackpT_transMax_spinbit9 = track_transMax->pt();} 
	  }//End of Track Loop
	
	for(int iTower = 0; iTower < ueEvent_transMax->numberOfTowers(); iTower++)
	  {
	    StJetTower* tower_transMax = ueEvent_transMax->tower(iTower);
	    htransMax_towerETJP2_spinbit9->Fill(tower_transMax->pt());
	    htransMax_toweretaJP2_spinbit9->Fill(tower_transMax->eta());
	    htransMax_towerphiJP2_spinbit9->Fill(tower_transMax->phi());
	    sumtowerEt_transMax_spinbit9 = sumtowerEt_transMax_spinbit9 + tower_transMax->pt(); 
	    if(maxtowerEt_transMax_spinbit9 < tower_transMax->pt()){maxtowerEt_transMax_spinbit9 = tower_transMax->pt();} 
	    if(mintowerEt_transMax_spinbit9 > tower_transMax->pt()){mintowerEt_transMax_spinbit9 = tower_transMax->pt();} 
	  }// End of Tower Loop
      } // End of Spin Bit 9 If Statement 
	// ------------------- End Of Trans Max Spin Bit 9--------------------------

      //-----------------Transverse Max Spin Bit 10 ------------------------
      sumtrackpT_transMax_spinbit10 = sumtowerEt_transMax_spinbit10 = 0; 
      avetrackpT_transMax_spinbit10 = avetowerEt_transMax_spinbit10 = 0;
      maxtrackpT_transMax_spinbit10 = maxtowerEt_transMax_spinbit10 = 0;
      mintrackpT_transMax_spinbit10 = mintowerEt_transMax_spinbit10 = 100;
      if(skimEvent->spin4usingBx48() == 10 ) {
	for (int iTrack = 0; iTrack < ueEvent_transMax->numberOfTracks(); iTrack++)
	  {
	    StJetTrack* track_transMax = ueEvent_transMax->track(iTrack);
	    htransMax_trackpTJP2_spinbit10->Fill(track_transMax->pt());
	    htransMax_tracketaJP2_spinbit10->Fill(track_transMax->eta());
	    htransMax_trackphiJP2_spinbit10->Fill(track_transMax->phi());
	    sumtrackpT_transMax_spinbit10 = sumtrackpT_transMax_spinbit10 + track_transMax->pt();
	    if(maxtrackpT_transMax_spinbit10 < track_transMax->pt()){maxtrackpT_transMax_spinbit10 = track_transMax->pt();} 
	    if(mintrackpT_transMax_spinbit10 > track_transMax->pt()){mintrackpT_transMax_spinbit10 = track_transMax->pt();} 
	  }//End of Track Loop
	
	for(int iTower = 0; iTower < ueEvent_transMax->numberOfTowers(); iTower++)
	  {
	    StJetTower* tower_transMax = ueEvent_transMax->tower(iTower);
	    htransMax_towerETJP2_spinbit10->Fill(tower_transMax->pt());
	    htransMax_toweretaJP2_spinbit10->Fill(tower_transMax->eta());
	    htransMax_towerphiJP2_spinbit10->Fill(tower_transMax->phi());
	    sumtowerEt_transMax_spinbit10 = sumtowerEt_transMax_spinbit10 + tower_transMax->pt(); 
	    if(maxtowerEt_transMax_spinbit10 < tower_transMax->pt()){maxtowerEt_transMax_spinbit10 = tower_transMax->pt();} 
	    if(mintowerEt_transMax_spinbit10 > tower_transMax->pt()){mintowerEt_transMax_spinbit10 = tower_transMax->pt();} 
	  }// End of Tower Loop
      } // End of Spin Bit 9 If Statement 
	// ------------------- End Of Trans Max Spin Bit 10--------------------------

     
      //-----------------Transverse Min ------------------------
      sumtrackpT_transMin = sumtowerEt_transMin = 0; 
      avetrackpT_transMin = avetowerEt_transMin = 0;
      maxtrackpT_transMin = maxtowerEt_transMin = 0;
      mintrackpT_transMin = mintowerEt_transMin = 100;
      for (int iTrack = 0; iTrack < ueEvent_transMin->numberOfTracks(); iTrack++)
	{
	  StJetTrack* track_transMin = ueEvent_transMin->track(iTrack);
	  htransMin_trackpTJP2->Fill(track_transMin->pt());
	  htransMin_tracketaJP2->Fill(track_transMin->eta());
	  htransMin_trackphiJP2->Fill(track_transMin->phi());
	  sumtrackpT_transMin = sumtrackpT_transMin + track_transMin->pt();
	  if(maxtrackpT_transMin < track_transMin->pt()){maxtrackpT_transMin = track_transMin->pt();} 
	  if(mintrackpT_transMin > track_transMin->pt()){mintrackpT_transMin = track_transMin->pt();} 
	}//End of Track Loop
      
      for(int iTower = 0; iTower < ueEvent_transMin->numberOfTowers(); iTower++)
	{
	  StJetTower* tower_transMin = ueEvent_transMin->tower(iTower);
	  htransMin_towerETJP2->Fill(tower_transMin->pt());
	  htransMin_toweretaJP2->Fill(tower_transMin->eta());
	  htransMin_towerphiJP2->Fill(tower_transMin->phi());
	  sumtowerEt_transMin = sumtowerEt_transMin + tower_transMin->pt(); 
	  if(maxtowerEt_transMin < tower_transMin->pt()){maxtowerEt_transMin = tower_transMin->pt();} 
	  if(mintowerEt_transMin > tower_transMin->pt()){mintowerEt_transMin = tower_transMin->pt();} 
	}// End of Tower Loop
      // ------------------- End Of Trans Min --------------------------

      //-----------------Transverse Min Spin Bit 5 ------------------------
      sumtrackpT_transMin_spinbit5 = sumtowerEt_transMin_spinbit5 = 0; 
      avetrackpT_transMin_spinbit5 = avetowerEt_transMin_spinbit5 = 0;
      maxtrackpT_transMin_spinbit5 = maxtowerEt_transMin_spinbit5 = 0;
      mintrackpT_transMin_spinbit5 = mintowerEt_transMin_spinbit5 = 100;
      if(skimEvent->spin4usingBx48() == 5 ) {
	for (int iTrack = 0; iTrack < ueEvent_transMin->numberOfTracks(); iTrack++)
	  {
	    StJetTrack* track_transMin = ueEvent_transMin->track(iTrack);
	    htransMin_trackpTJP2_spinbit5->Fill(track_transMin->pt());
	    htransMin_tracketaJP2_spinbit5->Fill(track_transMin->eta());
	    htransMin_trackphiJP2_spinbit5->Fill(track_transMin->phi());
	    sumtrackpT_transMin_spinbit5 = sumtrackpT_transMin_spinbit5 + track_transMin->pt();
	    if(maxtrackpT_transMin_spinbit5 < track_transMin->pt()){maxtrackpT_transMin_spinbit5 = track_transMin->pt();} 
	    if(mintrackpT_transMin_spinbit5 > track_transMin->pt()){mintrackpT_transMin_spinbit5 = track_transMin->pt();} 
	  }//End of Track Loop
	
	for(int iTower = 0; iTower < ueEvent_transMin->numberOfTowers(); iTower++)
	  {
	    StJetTower* tower_transMin = ueEvent_transMin->tower(iTower);
	    htransMin_towerETJP2_spinbit5->Fill(tower_transMin->pt());
	    htransMin_toweretaJP2_spinbit5->Fill(tower_transMin->eta());
	    htransMin_towerphiJP2_spinbit5->Fill(tower_transMin->phi());
	    sumtowerEt_transMin_spinbit5 = sumtowerEt_transMin_spinbit5 + tower_transMin->pt(); 
	    if(maxtowerEt_transMin_spinbit5 < tower_transMin->pt()){maxtowerEt_transMin_spinbit5 = tower_transMin->pt();} 
	    if(mintowerEt_transMin_spinbit5 > tower_transMin->pt()){mintowerEt_transMin_spinbit5 = tower_transMin->pt();} 
	  }// End of Tower Loop
      } // End of Spin Bit 5 If Statement 
	// ------------------- End Of Trans Min Spin Bit 5 --------------------------

      //-----------------Transverse Min Spin Bit 6 ------------------------
      sumtrackpT_transMin_spinbit6 = sumtowerEt_transMin_spinbit6 = 0; 
      avetrackpT_transMin_spinbit6 = avetowerEt_transMin_spinbit6 = 0;
      maxtrackpT_transMin_spinbit6 = maxtowerEt_transMin_spinbit6 = 0;
      mintrackpT_transMin_spinbit6 = mintowerEt_transMin_spinbit6 = 100;
      if(skimEvent->spin4usingBx48() == 6 ) {
	for (int iTrack = 0; iTrack < ueEvent_transMin->numberOfTracks(); iTrack++)
	  {
	    StJetTrack* track_transMin = ueEvent_transMin->track(iTrack);
	    htransMin_trackpTJP2_spinbit6->Fill(track_transMin->pt());
	    htransMin_tracketaJP2_spinbit6->Fill(track_transMin->eta());
	    htransMin_trackphiJP2_spinbit6->Fill(track_transMin->phi());
	    sumtrackpT_transMin_spinbit6 = sumtrackpT_transMin_spinbit6 + track_transMin->pt();
	    if(maxtrackpT_transMin_spinbit6 < track_transMin->pt()){maxtrackpT_transMin_spinbit6 = track_transMin->pt();} 
	    if(mintrackpT_transMin_spinbit6 > track_transMin->pt()){mintrackpT_transMin_spinbit6 = track_transMin->pt();} 
	  }//End of Track Loop
	
	for(int iTower = 0; iTower < ueEvent_transMin->numberOfTowers(); iTower++)
	  {
	    StJetTower* tower_transMin = ueEvent_transMin->tower(iTower);
	    htransMin_towerETJP2_spinbit6->Fill(tower_transMin->pt());
	    htransMin_toweretaJP2_spinbit6->Fill(tower_transMin->eta());
	    htransMin_towerphiJP2_spinbit6->Fill(tower_transMin->phi());
	    sumtowerEt_transMin_spinbit6 = sumtowerEt_transMin_spinbit6 + tower_transMin->pt(); 
	    if(maxtowerEt_transMin_spinbit6 < tower_transMin->pt()){maxtowerEt_transMin_spinbit6 = tower_transMin->pt();} 
	    if(mintowerEt_transMin_spinbit6 > tower_transMin->pt()){mintowerEt_transMin_spinbit6 = tower_transMin->pt();} 
	  }// End of Tower Loop
      } // End of Spin Bit 6 If Statement 
	// ------------------- End Of Trans Min Spin Bit 6 --------------------------


      //-----------------Transverse Min Spin Bit 9 ------------------------
      sumtrackpT_transMin_spinbit9 = sumtowerEt_transMin_spinbit9 = 0; 
      avetrackpT_transMin_spinbit9 = avetowerEt_transMin_spinbit9 = 0;
      maxtrackpT_transMin_spinbit9 = maxtowerEt_transMin_spinbit9 = 0;
      mintrackpT_transMin_spinbit9 = mintowerEt_transMin_spinbit9 = 100;
      if(skimEvent->spin4usingBx48() == 9 ) {
	for (int iTrack = 0; iTrack < ueEvent_transMin->numberOfTracks(); iTrack++)
	  {
	    StJetTrack* track_transMin = ueEvent_transMin->track(iTrack);
	    htransMin_trackpTJP2_spinbit9->Fill(track_transMin->pt());
	    htransMin_tracketaJP2_spinbit9->Fill(track_transMin->eta());
	    htransMin_trackphiJP2_spinbit9->Fill(track_transMin->phi());
	    sumtrackpT_transMin_spinbit9 = sumtrackpT_transMin_spinbit9 + track_transMin->pt();
	    if(maxtrackpT_transMin_spinbit9 < track_transMin->pt()){maxtrackpT_transMin_spinbit9 = track_transMin->pt();} 
	    if(mintrackpT_transMin_spinbit9 > track_transMin->pt()){mintrackpT_transMin_spinbit9 = track_transMin->pt();} 
	  }//End of Track Loop
	
	for(int iTower = 0; iTower < ueEvent_transMin->numberOfTowers(); iTower++)
	  {
	    StJetTower* tower_transMin = ueEvent_transMin->tower(iTower);
	    htransMin_towerETJP2_spinbit9->Fill(tower_transMin->pt());
	    htransMin_toweretaJP2_spinbit9->Fill(tower_transMin->eta());
	    htransMin_towerphiJP2_spinbit9->Fill(tower_transMin->phi());
	    sumtowerEt_transMin_spinbit9 = sumtowerEt_transMin_spinbit9 + tower_transMin->pt(); 
	    if(maxtowerEt_transMin_spinbit9 < tower_transMin->pt()){maxtowerEt_transMin_spinbit9 = tower_transMin->pt();} 
	    if(mintowerEt_transMin_spinbit9 > tower_transMin->pt()){mintowerEt_transMin_spinbit9 = tower_transMin->pt();} 
	  }// End of Tower Loop
      } // End of Spin Bit 9 If Statement 
	// ------------------- End Of Trans Min Spin Bit 9 --------------------------


      //-----------------Transverse Min Spin Bit 10 ------------------------
      sumtrackpT_transMin_spinbit10 = sumtowerEt_transMin_spinbit10 = 0; 
      avetrackpT_transMin_spinbit10 = avetowerEt_transMin_spinbit10 = 0;
      maxtrackpT_transMin_spinbit10 = maxtowerEt_transMin_spinbit10 = 0;
      mintrackpT_transMin_spinbit10 = mintowerEt_transMin_spinbit10 = 100;
      if(skimEvent->spin4usingBx48() == 10 ) {
	for (int iTrack = 0; iTrack < ueEvent_transMin->numberOfTracks(); iTrack++)
	  {
	    StJetTrack* track_transMin = ueEvent_transMin->track(iTrack);
	    htransMin_trackpTJP2_spinbit10->Fill(track_transMin->pt());
	    htransMin_tracketaJP2_spinbit10->Fill(track_transMin->eta());
	    htransMin_trackphiJP2_spinbit10->Fill(track_transMin->phi());
	    sumtrackpT_transMin_spinbit10 = sumtrackpT_transMin_spinbit10 + track_transMin->pt();
	    if(maxtrackpT_transMin_spinbit10 < track_transMin->pt()){maxtrackpT_transMin_spinbit10 = track_transMin->pt();} 
	    if(mintrackpT_transMin_spinbit10 > track_transMin->pt()){mintrackpT_transMin_spinbit10 = track_transMin->pt();} 
	  }//End of Track Loop
	
	for(int iTower = 0; iTower < ueEvent_transMin->numberOfTowers(); iTower++)
	  {
	    StJetTower* tower_transMin = ueEvent_transMin->tower(iTower);
	    htransMin_towerETJP2_spinbit10->Fill(tower_transMin->pt());
	    htransMin_toweretaJP2_spinbit10->Fill(tower_transMin->eta());
	    htransMin_towerphiJP2_spinbit10->Fill(tower_transMin->phi());
	    sumtowerEt_transMin_spinbit10 = sumtowerEt_transMin_spinbit10 + tower_transMin->pt(); 
	    if(maxtowerEt_transMin_spinbit10 < tower_transMin->pt()){maxtowerEt_transMin_spinbit10 = tower_transMin->pt();} 
	    if(mintowerEt_transMin_spinbit10 > tower_transMin->pt()){mintowerEt_transMin_spinbit10 = tower_transMin->pt();} 
	  }// End of Tower Loop
      } // End of Spin Bit 10 If Statement 
	// ------------------- End Of Trans Min Spin Bit 10 --------------------------


      //---------------- Fill Event Histograms--------------------
      htransMax_numtrackJP2->Fill(ueEvent_transMax->numberOfTracks());
      htransMax_numtowerJP2->Fill(ueEvent_transMax->numberOfTowers()); 

      htransMin_numtrackJP2->Fill(ueEvent_transMin->numberOfTracks());
      htransMin_numtowerJP2->Fill(ueEvent_transMin->numberOfTowers());
      if(skimEvent->spin4usingBx48() == 5){
	htransMax_numtrackJP2_spinbit5->Fill(ueEvent_transMax->numberOfTracks());
	htransMax_numtowerJP2_spinbit5->Fill(ueEvent_transMax->numberOfTowers());
       	htransMin_numtrackJP2_spinbit5->Fill(ueEvent_transMin->numberOfTracks());
	htransMin_numtowerJP2_spinbit5->Fill(ueEvent_transMin->numberOfTowers());
      }
      if(skimEvent->spin4usingBx48() == 6){
	htransMax_numtrackJP2_spinbit6->Fill(ueEvent_transMax->numberOfTracks());
	htransMax_numtowerJP2_spinbit6->Fill(ueEvent_transMax->numberOfTowers());
       	htransMin_numtrackJP2_spinbit6->Fill(ueEvent_transMin->numberOfTracks());
       	htransMin_numtowerJP2_spinbit6->Fill(ueEvent_transMin->numberOfTowers());
      }
  
    if(skimEvent->spin4usingBx48() == 9){
	htransMax_numtrackJP2_spinbit9->Fill(ueEvent_transMax->numberOfTracks());
	htransMax_numtowerJP2_spinbit9->Fill(ueEvent_transMax->numberOfTowers());
       	htransMin_numtrackJP2_spinbit9->Fill(ueEvent_transMin->numberOfTracks());
       	htransMin_numtowerJP2_spinbit9->Fill(ueEvent_transMin->numberOfTowers());
      }
    if(skimEvent->spin4usingBx48() == 10){
	htransMax_numtrackJP2_spinbit10->Fill(ueEvent_transMax->numberOfTracks());
	htransMax_numtowerJP2_spinbit10->Fill(ueEvent_transMax->numberOfTowers());
	htransMin_numtrackJP2_spinbit10->Fill(ueEvent_transMin->numberOfTracks());
	htransMin_numtowerJP2_spinbit10->Fill(ueEvent_transMin->numberOfTowers());
      }
  

      //---------------------- Trans Max Event Filling  ------------------------------ 
      if(ueEvent_transMax->numberOfTracks() != 0) avetrackpT_transMax = sumtrackpT_transMax / ueEvent_transMax->numberOfTracks();
      if(ueEvent_transMax->numberOfTowers() != 0) avetowerEt_transMax = sumtowerEt_transMax / ueEvent_transMax->numberOfTowers();
      //track transMax
      htransMax_numTrackVsMaxJetpTJP2->Fill(leadingjet->pt(),ueEvent_transMax->numberOfTracks());
      htransMax_sumTrackpTVsMaxJetpTJP2->Fill(leadingjet->pt(),sumtrackpT_transMax);
      htransMax_aveTrackpTVsMaxJetpTJP2->Fill(leadingjet->pt(),avetrackpT_transMax);
      htransMax_maxTrackpTVsMaxJetpTJP2->Fill(leadingjet->pt(),maxtrackpT_transMax);
      htransMax_minTrackpTVsMaxJetpTJP2->Fill(leadingjet->pt(),mintrackpT_transMax);

      //tower transMax
      htransMax_numTowerVsMaxJetpTJP2->Fill(leadingjet->pt(),ueEvent_transMax->numberOfTowers());
      htransMax_sumTowerEtVsMaxJetpTJP2->Fill(leadingjet->pt(),sumtowerEt_transMax);
      htransMax_aveTowerEtVsMaxJetpTJP2->Fill(leadingjet->pt(),avetowerEt_transMax);
      htransMax_maxTowerEtVsMaxJetpTJP2->Fill(leadingjet->pt(),maxtowerEt_transMax);
      htransMax_minTowerEtVsMaxJetpTJP2->Fill(leadingjet->pt(),mintowerEt_transMax);
      
      if(skimEvent->spin4usingBx48() == 5){    
	if(ueEvent_transMax->numberOfTracks() != 0) avetrackpT_transMax_spinbit5 = sumtrackpT_transMax_spinbit5 / ueEvent_transMax->numberOfTracks();
	if(ueEvent_transMax->numberOfTowers() != 0) avetowerEt_transMax_spinbit5 = sumtowerEt_transMax_spinbit5 / ueEvent_transMax->numberOfTowers();
	//track transMax
	htransMax_numTrackVsMaxJetpTJP2_spinbit5->Fill(leadingjet->pt(),ueEvent_transMax->numberOfTracks());
	htransMax_sumTrackpTVsMaxJetpTJP2_spinbit5->Fill(leadingjet->pt(),sumtrackpT_transMax_spinbit5);
	htransMax_aveTrackpTVsMaxJetpTJP2_spinbit5->Fill(leadingjet->pt(),avetrackpT_transMax_spinbit5);
	htransMax_maxTrackpTVsMaxJetpTJP2_spinbit5->Fill(leadingjet->pt(),maxtrackpT_transMax_spinbit5);
	htransMax_minTrackpTVsMaxJetpTJP2_spinbit5->Fill(leadingjet->pt(),mintrackpT_transMax_spinbit5);
	
	//tower transMax
	htransMax_numTowerVsMaxJetpTJP2_spinbit5->Fill(leadingjet->pt(),ueEvent_transMax->numberOfTowers());
	htransMax_sumTowerEtVsMaxJetpTJP2_spinbit5->Fill(leadingjet->pt(),sumtowerEt_transMax_spinbit5);
	htransMax_aveTowerEtVsMaxJetpTJP2_spinbit5->Fill(leadingjet->pt(),avetowerEt_transMax_spinbit5);
	htransMax_maxTowerEtVsMaxJetpTJP2_spinbit5->Fill(leadingjet->pt(),maxtowerEt_transMax_spinbit5);
	htransMax_minTowerEtVsMaxJetpTJP2_spinbit5->Fill(leadingjet->pt(),mintowerEt_transMax_spinbit5);
      }

      if(skimEvent->spin4usingBx48() == 6){    
	if(ueEvent_transMax->numberOfTracks() != 0) avetrackpT_transMax_spinbit6 = sumtrackpT_transMax_spinbit6 / ueEvent_transMax->numberOfTracks();
	if(ueEvent_transMax->numberOfTowers() != 0) avetowerEt_transMax_spinbit6 = sumtowerEt_transMax_spinbit6 / ueEvent_transMax->numberOfTowers();
	//track transMax
	htransMax_numTrackVsMaxJetpTJP2_spinbit6->Fill(leadingjet->pt(),ueEvent_transMax->numberOfTracks());
	htransMax_sumTrackpTVsMaxJetpTJP2_spinbit6->Fill(leadingjet->pt(),sumtrackpT_transMax_spinbit6);
	htransMax_aveTrackpTVsMaxJetpTJP2_spinbit6->Fill(leadingjet->pt(),avetrackpT_transMax_spinbit6);
	htransMax_maxTrackpTVsMaxJetpTJP2_spinbit6->Fill(leadingjet->pt(),maxtrackpT_transMax_spinbit6);
	htransMax_minTrackpTVsMaxJetpTJP2_spinbit6->Fill(leadingjet->pt(),mintrackpT_transMax_spinbit6);
	
	//tower transMax
	htransMax_numTowerVsMaxJetpTJP2_spinbit6->Fill(leadingjet->pt(),ueEvent_transMax->numberOfTowers());
	htransMax_sumTowerEtVsMaxJetpTJP2_spinbit6->Fill(leadingjet->pt(),sumtowerEt_transMax_spinbit6);
	htransMax_aveTowerEtVsMaxJetpTJP2_spinbit6->Fill(leadingjet->pt(),avetowerEt_transMax_spinbit6);
	htransMax_maxTowerEtVsMaxJetpTJP2_spinbit6->Fill(leadingjet->pt(),maxtowerEt_transMax_spinbit6);
	htransMax_minTowerEtVsMaxJetpTJP2_spinbit6->Fill(leadingjet->pt(),mintowerEt_transMax_spinbit6);
      }

      if(skimEvent->spin4usingBx48() == 9){    
	if(ueEvent_transMax->numberOfTracks() != 0) avetrackpT_transMax_spinbit9 = sumtrackpT_transMax_spinbit9 / ueEvent_transMax->numberOfTracks();
	if(ueEvent_transMax->numberOfTowers() != 0) avetowerEt_transMax_spinbit9 = sumtowerEt_transMax_spinbit9 / ueEvent_transMax->numberOfTowers();
	//track transMax
	htransMax_numTrackVsMaxJetpTJP2_spinbit9->Fill(leadingjet->pt(),ueEvent_transMax->numberOfTracks());
	htransMax_sumTrackpTVsMaxJetpTJP2_spinbit9->Fill(leadingjet->pt(),sumtrackpT_transMax_spinbit9);
	htransMax_aveTrackpTVsMaxJetpTJP2_spinbit9->Fill(leadingjet->pt(),avetrackpT_transMax_spinbit9);
	htransMax_maxTrackpTVsMaxJetpTJP2_spinbit9->Fill(leadingjet->pt(),maxtrackpT_transMax_spinbit9);
	htransMax_minTrackpTVsMaxJetpTJP2_spinbit9->Fill(leadingjet->pt(),mintrackpT_transMax_spinbit9);
	
	//tower transMax
	htransMax_numTowerVsMaxJetpTJP2_spinbit9->Fill(leadingjet->pt(),ueEvent_transMax->numberOfTowers());
	htransMax_sumTowerEtVsMaxJetpTJP2_spinbit9->Fill(leadingjet->pt(),sumtowerEt_transMax_spinbit9);
	htransMax_aveTowerEtVsMaxJetpTJP2_spinbit9->Fill(leadingjet->pt(),avetowerEt_transMax_spinbit9);
	htransMax_maxTowerEtVsMaxJetpTJP2_spinbit9->Fill(leadingjet->pt(),maxtowerEt_transMax_spinbit9);
	htransMax_minTowerEtVsMaxJetpTJP2_spinbit9->Fill(leadingjet->pt(),mintowerEt_transMax_spinbit9);
      }

      if(skimEvent->spin4usingBx48() == 10){    
	if(ueEvent_transMax->numberOfTracks() != 0) avetrackpT_transMax_spinbit10 = sumtrackpT_transMax_spinbit10 / ueEvent_transMax->numberOfTracks();
	if(ueEvent_transMax->numberOfTowers() != 0) avetowerEt_transMax_spinbit10 = sumtowerEt_transMax_spinbit10 / ueEvent_transMax->numberOfTowers();
	//track transMax
	htransMax_numTrackVsMaxJetpTJP2_spinbit10->Fill(leadingjet->pt(),ueEvent_transMax->numberOfTracks());
	htransMax_sumTrackpTVsMaxJetpTJP2_spinbit10->Fill(leadingjet->pt(),sumtrackpT_transMax_spinbit10);
	htransMax_aveTrackpTVsMaxJetpTJP2_spinbit10->Fill(leadingjet->pt(),avetrackpT_transMax_spinbit10);
	htransMax_maxTrackpTVsMaxJetpTJP2_spinbit10->Fill(leadingjet->pt(),maxtrackpT_transMax_spinbit10);
	htransMax_minTrackpTVsMaxJetpTJP2_spinbit10->Fill(leadingjet->pt(),mintrackpT_transMax_spinbit10);
	
	//tower transMax
	htransMax_numTowerVsMaxJetpTJP2_spinbit10->Fill(leadingjet->pt(),ueEvent_transMax->numberOfTowers());
	htransMax_sumTowerEtVsMaxJetpTJP2_spinbit10->Fill(leadingjet->pt(),sumtowerEt_transMax_spinbit10);
	htransMax_aveTowerEtVsMaxJetpTJP2_spinbit10->Fill(leadingjet->pt(),avetowerEt_transMax_spinbit10);
	htransMax_maxTowerEtVsMaxJetpTJP2_spinbit10->Fill(leadingjet->pt(),maxtowerEt_transMax_spinbit10);
	htransMax_minTowerEtVsMaxJetpTJP2_spinbit10->Fill(leadingjet->pt(),mintowerEt_transMax_spinbit10);
      }
      //----------------------- End of Trans Max Event Filling ----------------------------
     
      //----------------------- Trans Min Event Filling ----------------------------------
      if(ueEvent_transMin->numberOfTracks() != 0) avetrackpT_transMin = sumtrackpT_transMin / ueEvent_transMin->numberOfTracks();
      if(ueEvent_transMin->numberOfTowers() != 0) avetowerEt_transMin = sumtowerEt_transMin / ueEvent_transMin->numberOfTowers();
      //track transMin
      htransMin_numTrackVsMaxJetpTJP2->Fill(leadingjet->pt(),ueEvent_transMin->numberOfTracks());
      htransMin_sumTrackpTVsMaxJetpTJP2->Fill(leadingjet->pt(),sumtrackpT_transMin);
      htransMin_aveTrackpTVsMaxJetpTJP2->Fill(leadingjet->pt(),avetrackpT_transMin);
      htransMin_maxTrackpTVsMaxJetpTJP2->Fill(leadingjet->pt(),maxtrackpT_transMin);
      htransMin_minTrackpTVsMaxJetpTJP2->Fill(leadingjet->pt(),mintrackpT_transMin);

      //tower transMin
      htransMin_numTowerVsMaxJetpTJP2->Fill(leadingjet->pt(),ueEvent_transMin->numberOfTowers());
      htransMin_sumTowerEtVsMaxJetpTJP2->Fill(leadingjet->pt(),sumtowerEt_transMin);
      htransMin_aveTowerEtVsMaxJetpTJP2->Fill(leadingjet->pt(),avetowerEt_transMin);
      htransMin_maxTowerEtVsMaxJetpTJP2->Fill(leadingjet->pt(),maxtowerEt_transMin);
      htransMin_minTowerEtVsMaxJetpTJP2->Fill(leadingjet->pt(),mintowerEt_transMin);

      if(skimEvent->spin4usingBx48() == 5){    
	if(ueEvent_transMin->numberOfTracks() != 0) avetrackpT_transMin_spinbit5 = sumtrackpT_transMin_spinbit5 / ueEvent_transMin->numberOfTracks();
	if(ueEvent_transMin->numberOfTowers() != 0) avetowerEt_transMin_spinbit5 = sumtowerEt_transMin_spinbit5 / ueEvent_transMin->numberOfTowers();
	//track transMin
	htransMin_numTrackVsMaxJetpTJP2_spinbit5->Fill(leadingjet->pt(),ueEvent_transMin->numberOfTracks());
	htransMin_sumTrackpTVsMaxJetpTJP2_spinbit5->Fill(leadingjet->pt(),sumtrackpT_transMin_spinbit5);
	htransMin_aveTrackpTVsMaxJetpTJP2_spinbit5->Fill(leadingjet->pt(),avetrackpT_transMin_spinbit5);
	htransMin_maxTrackpTVsMaxJetpTJP2_spinbit5->Fill(leadingjet->pt(),maxtrackpT_transMin_spinbit5);
	htransMin_minTrackpTVsMaxJetpTJP2_spinbit5->Fill(leadingjet->pt(),mintrackpT_transMin_spinbit5);
	
	//tower transMin
	htransMin_numTowerVsMaxJetpTJP2_spinbit5->Fill(leadingjet->pt(),ueEvent_transMin->numberOfTowers());
	htransMin_sumTowerEtVsMaxJetpTJP2_spinbit5->Fill(leadingjet->pt(),sumtowerEt_transMin_spinbit5);
	htransMin_aveTowerEtVsMaxJetpTJP2_spinbit5->Fill(leadingjet->pt(),avetowerEt_transMin_spinbit5);
	htransMin_maxTowerEtVsMaxJetpTJP2_spinbit5->Fill(leadingjet->pt(),maxtowerEt_transMin_spinbit5);
	htransMin_minTowerEtVsMaxJetpTJP2_spinbit5->Fill(leadingjet->pt(),mintowerEt_transMin_spinbit5);
      }
      if(skimEvent->spin4usingBx48() == 6){    
	if(ueEvent_transMin->numberOfTracks() != 0) avetrackpT_transMin_spinbit6 = sumtrackpT_transMin_spinbit6 / ueEvent_transMin->numberOfTracks();
	if(ueEvent_transMin->numberOfTowers() != 0) avetowerEt_transMin_spinbit6 = sumtowerEt_transMin_spinbit6 / ueEvent_transMin->numberOfTowers();
	//track transMin
	htransMin_numTrackVsMaxJetpTJP2_spinbit6->Fill(leadingjet->pt(),ueEvent_transMin->numberOfTracks());
	htransMin_sumTrackpTVsMaxJetpTJP2_spinbit6->Fill(leadingjet->pt(),sumtrackpT_transMin_spinbit6);
	htransMin_aveTrackpTVsMaxJetpTJP2_spinbit6->Fill(leadingjet->pt(),avetrackpT_transMin_spinbit6);
	htransMin_maxTrackpTVsMaxJetpTJP2_spinbit6->Fill(leadingjet->pt(),maxtrackpT_transMin_spinbit6);
	htransMin_minTrackpTVsMaxJetpTJP2_spinbit6->Fill(leadingjet->pt(),mintrackpT_transMin_spinbit6);
	
	//tower transMin
	htransMin_numTowerVsMaxJetpTJP2_spinbit6->Fill(leadingjet->pt(),ueEvent_transMin->numberOfTowers());
	htransMin_sumTowerEtVsMaxJetpTJP2_spinbit6->Fill(leadingjet->pt(),sumtowerEt_transMin_spinbit6);
	htransMin_aveTowerEtVsMaxJetpTJP2_spinbit6->Fill(leadingjet->pt(),avetowerEt_transMin_spinbit6);
	htransMin_maxTowerEtVsMaxJetpTJP2_spinbit6->Fill(leadingjet->pt(),maxtowerEt_transMin_spinbit6);
	htransMin_minTowerEtVsMaxJetpTJP2_spinbit6->Fill(leadingjet->pt(),mintowerEt_transMin_spinbit6);
      }
      if(skimEvent->spin4usingBx48() == 9){    
	if(ueEvent_transMin->numberOfTracks() != 0) avetrackpT_transMin_spinbit9 = sumtrackpT_transMin_spinbit9 / ueEvent_transMin->numberOfTracks();
	if(ueEvent_transMin->numberOfTowers() != 0) avetowerEt_transMin_spinbit9 = sumtowerEt_transMin_spinbit9 / ueEvent_transMin->numberOfTowers();
	//track transMin
	htransMin_numTrackVsMaxJetpTJP2_spinbit9->Fill(leadingjet->pt(),ueEvent_transMin->numberOfTracks());
	htransMin_sumTrackpTVsMaxJetpTJP2_spinbit9->Fill(leadingjet->pt(),sumtrackpT_transMin_spinbit9);
	htransMin_aveTrackpTVsMaxJetpTJP2_spinbit9->Fill(leadingjet->pt(),avetrackpT_transMin_spinbit9);
	htransMin_maxTrackpTVsMaxJetpTJP2_spinbit9->Fill(leadingjet->pt(),maxtrackpT_transMin_spinbit9);
	htransMin_minTrackpTVsMaxJetpTJP2_spinbit9->Fill(leadingjet->pt(),mintrackpT_transMin_spinbit9);
	
	//tower transMin
	htransMin_numTowerVsMaxJetpTJP2_spinbit9->Fill(leadingjet->pt(),ueEvent_transMin->numberOfTowers());
	htransMin_sumTowerEtVsMaxJetpTJP2_spinbit9->Fill(leadingjet->pt(),sumtowerEt_transMin_spinbit9);
	htransMin_aveTowerEtVsMaxJetpTJP2_spinbit9->Fill(leadingjet->pt(),avetowerEt_transMin_spinbit9);
	htransMin_maxTowerEtVsMaxJetpTJP2_spinbit9->Fill(leadingjet->pt(),maxtowerEt_transMin_spinbit9);
	htransMin_minTowerEtVsMaxJetpTJP2_spinbit9->Fill(leadingjet->pt(),mintowerEt_transMin_spinbit9);
      }
      if(skimEvent->spin4usingBx48() == 10){    
	if(ueEvent_transMin->numberOfTracks() != 0) avetrackpT_transMin_spinbit10 = sumtrackpT_transMin_spinbit10 / ueEvent_transMin->numberOfTracks();
	if(ueEvent_transMin->numberOfTowers() != 0) avetowerEt_transMin_spinbit10 = sumtowerEt_transMin_spinbit10 / ueEvent_transMin->numberOfTowers();
	//track transMin
	htransMin_numTrackVsMaxJetpTJP2_spinbit10->Fill(leadingjet->pt(),ueEvent_transMin->numberOfTracks());
	htransMin_sumTrackpTVsMaxJetpTJP2_spinbit10->Fill(leadingjet->pt(),sumtrackpT_transMin_spinbit10);
	htransMin_aveTrackpTVsMaxJetpTJP2_spinbit10->Fill(leadingjet->pt(),avetrackpT_transMin_spinbit10);
	htransMin_maxTrackpTVsMaxJetpTJP2_spinbit10->Fill(leadingjet->pt(),maxtrackpT_transMin_spinbit10);
	htransMin_minTrackpTVsMaxJetpTJP2_spinbit10->Fill(leadingjet->pt(),mintrackpT_transMin_spinbit10);
	
	//tower transMin
	htransMin_numTowerVsMaxJetpTJP2_spinbit10->Fill(leadingjet->pt(),ueEvent_transMin->numberOfTowers());
	htransMin_sumTowerEtVsMaxJetpTJP2_spinbit10->Fill(leadingjet->pt(),sumtowerEt_transMin_spinbit10);
	htransMin_aveTowerEtVsMaxJetpTJP2_spinbit10->Fill(leadingjet->pt(),avetowerEt_transMin_spinbit10);
	htransMin_maxTowerEtVsMaxJetpTJP2_spinbit10->Fill(leadingjet->pt(),maxtowerEt_transMin_spinbit10);
	htransMin_minTowerEtVsMaxJetpTJP2_spinbit10->Fill(leadingjet->pt(),mintowerEt_transMin_spinbit10);
      }
      // ---------------------- End of Trans Min Event Filling --------------------------

    }// End of JP2 if statement 
  }//End of Event Loop
  ofile->Write();
  ofile->Close();
}


void BookHists()
{
  //Book histograms
  TH1F* hleadingjetpTJP2 = new TH1F("hleadingjetpTJP2",";Leading jet p_{T} [GeV]",95,5,100);

  //Track Histograms
 
  TH1F* htransMax_trackpTJP2 = new TH1F("htransMax_trackpTJP2","transMax; track p_{T} [GeV]",1000,0,50);
  TH1F* htransMax_tracketaJP2 = new TH1F("htransMax_tracketaJP2","transMax; track #eta",66,-1.5,1.5);
  TH1F* htransMax_trackphiJP2 = new TH1F("htransMax_trackphiJP2","transMax; track #phi",120,-3.14159,3.14159);
  TH1F* htransMax_numtrackJP2 = new TH1F("htransMax_numtrackJP2","transMax; track multiplicity",20,0,20);

  TH1F* htransMax_trackpTJP2_spinbit5 = new TH1F("htransMax_trackpTJP2_spinbit5","transMax; track p_{T} [GeV]",1000,0,50);
  TH1F* htransMax_tracketaJP2_spinbit5 = new TH1F("htransMax_tracketaJP2_spinbit5","transMax; track #eta",66,-1.5,1.5);
  TH1F* htransMax_trackphiJP2_spinbit5 = new TH1F("htransMax_trackphiJP2_spinbit5","transMax; track #phi",120,-3.14159,3.14159);
  TH1F* htransMax_numtrackJP2_spinbit5 = new TH1F("htransMax_numtrackJP2_spinbit5","transMax; track multiplicity",20,0,20);

  TH1F* htransMax_trackpTJP2_spinbit6 = new TH1F("htransMax_trackpTJP2_spinbit6","transMax; track p_{T} [GeV]",1000,0,50);
  TH1F* htransMax_tracketaJP2_spinbit6 = new TH1F("htransMax_tracketaJP2_spinbit6","transMax; track #eta",66,-1.5,1.5);
  TH1F* htransMax_trackphiJP2_spinbit6 = new TH1F("htransMax_trackphiJP2_spinbit6","transMax; track #phi",120,-3.14159,3.14159);
  TH1F* htransMax_numtrackJP2_spinbit6 = new TH1F("htransMax_numtrackJP2_spinbit6","transMax; track multiplicity",20,0,20);
  
  TH1F* htransMax_trackpTJP2_spinbit9 = new TH1F("htransMax_trackpTJP2_spinbit9","transMax; track p_{T} [GeV]",1000,0,50);
  TH1F* htransMax_tracketaJP2_spinbit9 = new TH1F("htransMax_tracketaJP2_spinbit9","transMax; track #eta",66,-1.5,1.5);
  TH1F* htransMax_trackphiJP2_spinbit9 = new TH1F("htransMax_trackphiJP2_spinbit9","transMax; track #phi",120,-3.14159,3.14159);
  TH1F* htransMax_numtrackJP2_spinbit9 = new TH1F("htransMax_numtrackJP2_spinbit9","transMax; track multiplicity",20,0,20);

  TH1F* htransMax_trackpTJP2_spinbit10 = new TH1F("htransMax_trackpTJP2_spinbit10","transMax; track p_{T} [GeV]",1000,0,50);
  TH1F* htransMax_tracketaJP2_spinbit10 = new TH1F("htransMax_tracketaJP2_spinbit10","transMax; track #eta",66,-1.5,1.5);
  TH1F* htransMax_trackphiJP2_spinbit10 = new TH1F("htransMax_trackphiJP2_spinbit10","transMax; track #phi",120,-3.14159,3.14159);
  TH1F* htransMax_numtrackJP2_spinbit10 = new TH1F("htransMax_numtrackJP2_spinbit10","transMax; track multiplicity",20,0,20);

  TH1F* htransMin_trackpTJP2 = new TH1F("htransMin_trackpTJP2","transMin; track p_{T} [GeV]",1000,0,50);
  TH1F* htransMin_tracketaJP2 = new TH1F("htransMin_tracketaJP2","transMin; track #eta",66,-1.5,1.5);
  TH1F* htransMin_trackphiJP2 = new TH1F("htransMin_trackphiJP2","transMin; track #phi",120,-3.14159,3.14159);
  TH1F* htransMin_numtrackJP2 = new TH1F("htransMin_numtrackJP2","transMin; track multiplicity",20,0,20);
  
  TH1F* htransMin_trackpTJP2_spinbit5 = new TH1F("htransMin_trackpTJP2_spinbit5","transMin; track p_{T} [GeV]",1000,0,50);
  TH1F* htransMin_tracketaJP2_spinbit5 = new TH1F("htransMin_tracketaJP2_spinbit5","transMin; track #eta",66,-1.5,1.5);
  TH1F* htransMin_trackphiJP2_spinbit5 = new TH1F("htransMin_trackphiJP2_spinbit5","transMin; track #phi",120,-3.14159,3.14159);
  TH1F* htransMin_numtrackJP2_spinbit5 = new TH1F("htransMin_numtrackJP2_spinbit5","transMin; track multiplicity",20,0,20);

  TH1F* htransMin_trackpTJP2_spinbit6 = new TH1F("htransMin_trackpTJP2_spinbit6","transMin; track p_{T} [GeV]",1000,0,50);
  TH1F* htransMin_tracketaJP2_spinbit6 = new TH1F("htransMin_tracketaJP2_spinbit6","transMin; track #eta",66,-1.5,1.5);
  TH1F* htransMin_trackphiJP2_spinbit6 = new TH1F("htransMin_trackphiJP2_spinbit6","transMin; track #phi",120,-3.14159,3.14159);
  TH1F* htransMin_numtrackJP2_spinbit6 = new TH1F("htransMin_numtrackJP2_spinbit6","transMin; track multiplicity",20,0,20);

  TH1F* htransMin_trackpTJP2_spinbit9 = new TH1F("htransMin_trackpTJP2_spinbit9","transMin; track p_{T} [GeV]",1000,0,50);
  TH1F* htransMin_tracketaJP2_spinbit9 = new TH1F("htransMin_tracketaJP2_spinbit9","transMin; track #eta",66,-1.5,1.5);
  TH1F* htransMin_trackphiJP2_spinbit9 = new TH1F("htransMin_trackphiJP2_spinbit9","transMin; track #phi",120,-3.14159,3.14159);
  TH1F* htransMin_numtrackJP2_spinbit9 = new TH1F("htransMin_numtrackJP2_spinbit9","transMin; track multiplicity",20,0,20);
  
  TH1F* htransMin_trackpTJP2_spinbit10 = new TH1F("htransMin_trackpTJP2_spinbit10","transMin; track p_{T} [GeV]",1000,0,50);
  TH1F* htransMin_tracketaJP2_spinbit10 = new TH1F("htransMin_tracketaJP2_spinbit10","transMin; track #eta",66,-1.5,1.5);
  TH1F* htransMin_trackphiJP2_spinbit10 = new TH1F("htransMin_trackphiJP2_spinbit10","transMin; track #phi",120,-3.14159,3.14159);
  TH1F* htransMin_numtrackJP2_spinbit10 = new TH1F("htransMin_numtrackJP2_spinbit10","transMin; track multiplicity",20,0,20);
  
  //Tower Histograms


  TH1F* htransMax_towerETJP2 = new TH1F("htransMax_towerETJP2","transMax; tower E_{T} [GeV]",1000,0,50);
  TH1F* htransMax_toweretaJP2 = new TH1F("htransMax_toweretaJP2","transMax; tower #eta",66,-1.5,1.5);
  TH1F* htransMax_towerphiJP2 = new TH1F("htransMax_towerphiJP2","transMax; tower #phi",120,-3.14159,3.14159);
  TH1F* htransMax_numtowerJP2 = new TH1F("htransMax_numtowerJP2","transMax; tower multiplicity",50,0,50);

  TH1F* htransMax_towerETJP2_spinbit5 = new TH1F("htransMax_towerETJP2_spinbit5","transMax; tower E_{T} [GeV]",1000,0,50);
  TH1F* htransMax_toweretaJP2_spinbit5 = new TH1F("htransMax_toweretaJP2_spinbit5","transMax; tower #eta",66,-1.5,1.5);
  TH1F* htransMax_towerphiJP2_spinbit5 = new TH1F("htransMax_towerphiJP2_spinbit5","transMax; tower #phi",120,-3.14159,3.14159);
  TH1F* htransMax_numtowerJP2_spinbit5 = new TH1F("htransMax_numtowerJP2_spinbit5","transMax; tower multiplicity",50,0,50);

  TH1F* htransMax_towerETJP2_spinbit6 = new TH1F("htransMax_towerETJP2_spinbit6","transMax; tower E_{T} [GeV]",1000,0,50);
  TH1F* htransMax_toweretaJP2_spinbit6 = new TH1F("htransMax_toweretaJP2_spinbit6","transMax; tower #eta",66,-1.5,1.5);
  TH1F* htransMax_towerphiJP2_spinbit6 = new TH1F("htransMax_towerphiJP2_spinbit6","transMax; tower #phi",120,-3.14159,3.14159);
  TH1F* htransMax_numtowerJP2_spinbit6 = new TH1F("htransMax_numtowerJP2_spinbit6","transMax; tower multiplicity",50,0,50);

  TH1F* htransMax_towerETJP2_spinbit9 = new TH1F("htransMax_towerETJP2_spinbit9","transMax; tower E_{T} [GeV]",1000,0,50);
  TH1F* htransMax_toweretaJP2_spinbit9 = new TH1F("htransMax_toweretaJP2_spinbit9","transMax; tower #eta",66,-1.5,1.5);
  TH1F* htransMax_towerphiJP2_spinbit9 = new TH1F("htransMax_towerphiJP2_spinbit9","transMax; tower #phi",120,-3.14159,3.14159);
  TH1F* htransMax_numtowerJP2_spinbit9 = new TH1F("htransMax_numtowerJP2_spinbit9","transMax; tower multiplicity",50,0,50);

  TH1F* htransMax_towerETJP2_spinbit10 = new TH1F("htransMax_towerETJP2_spinbit10","transMax; tower E_{T} [GeV]",1000,0,50);
  TH1F* htransMax_toweretaJP2_spinbit10 = new TH1F("htransMax_toweretaJP2_spinbit10","transMax; tower #eta",66,-1.5,1.5);
  TH1F* htransMax_towerphiJP2_spinbit10 = new TH1F("htransMax_towerphiJP2_spinbit10","transMax; tower #phi",120,-3.14159,3.14159);
  TH1F* htransMax_numtowerJP2_spinbit10 = new TH1F("htransMax_numtowerJP2_spinbit10","transMax; tower multiplicity",50,0,50);

  TH1F* htransMin_towerETJP2 = new TH1F("htransMin_towerETJP2","transMin; tower E_{T} [GeV]",1000,0,50);
  TH1F* htransMin_toweretaJP2 = new TH1F("htransMin_toweretaJP2","transMin; tower #eta",66,-1.5,1.5);
  TH1F* htransMin_towerphiJP2 = new TH1F("htransMin_towerphiJP2","transMin; tower #phi",120,-3.14159,3.14159);
  TH1F* htransMin_numtowerJP2 = new TH1F("htransMin_numtowerJP2","transMin; tower multiplicity",50,0,50);

  TH1F* htransMin_towerETJP2_spinbit5 = new TH1F("htransMin_towerETJP2_spinbit5","transMin; tower E_{T} [GeV]",1000,0,50);
  TH1F* htransMin_toweretaJP2_spinbit5 = new TH1F("htransMin_toweretaJP2_spinbit5","transMin; tower #eta",66,-1.5,1.5);
  TH1F* htransMin_towerphiJP2_spinbit5 = new TH1F("htransMin_towerphiJP2_spinbit5","transMin; tower #phi",120,-3.14159,3.14159);
  TH1F* htransMin_numtowerJP2_spinbit5 = new TH1F("htransMin_numtowerJP2_spinbit5","transMin; tower multiplicity",50,0,50);

  TH1F* htransMin_towerETJP2_spinbit6 = new TH1F("htransMin_towerETJP2_spinbit6","transMin; tower E_{T} [GeV]",1000,0,50);
  TH1F* htransMin_toweretaJP2_spinbit6 = new TH1F("htransMin_toweretaJP2_spinbit6","transMin; tower #eta",66,-1.5,1.5);
  TH1F* htransMin_towerphiJP2_spinbit6 = new TH1F("htransMin_towerphiJP2_spinbit6","transMin; tower #phi",120,-3.14159,3.14159);
  TH1F* htransMin_numtowerJP2_spinbit6 = new TH1F("htransMin_numtowerJP2_spinbit6","transMin; tower multiplicity",50,0,50);

  TH1F* htransMin_towerETJP2_spinbit9 = new TH1F("htransMin_towerETJP2_spinbit9","transMin; tower E_{T} [GeV]",1000,0,50);
  TH1F* htransMin_toweretaJP2_spinbit9 = new TH1F("htransMin_toweretaJP2_spinbit9","transMin; tower #eta",66,-1.5,1.5);
  TH1F* htransMin_towerphiJP2_spinbit9 = new TH1F("htransMin_towerphiJP2_spinbit9","transMin; tower #phi",120,-3.14159,3.14159);
  TH1F* htransMin_numtowerJP2_spinbit9 = new TH1F("htransMin_numtowerJP2_spinbit9","transMin; tower multiplicity",50,0,50);

  TH1F* htransMin_towerETJP2_spinbit10 = new TH1F("htransMin_towerETJP2_spinbit10","transMin; tower E_{T} [GeV]",1000,0,50);
  TH1F* htransMin_toweretaJP2_spinbit10 = new TH1F("htransMin_toweretaJP2_spinbit10","transMin; tower #eta",66,-1.5,1.5);
  TH1F* htransMin_towerphiJP2_spinbit10 = new TH1F("htransMin_towerphiJP2_spinbit10","transMin; tower #phi",120,-3.14159,3.14159);
  TH1F* htransMin_numtowerJP2_spinbit10 = new TH1F("htransMin_numtowerJP2_spinbit10","transMin; tower multiplicity",50,0,50);

  //Event Histograms 
  TH2F* htransMax_numTrackVsMaxJetpTJP2 = new TH2F("htransMax_numTrackVsMaxJetpTJP2","transMax; jet p_{T} [GeV]; track multiplicity",95,5,100,30,0,30);
  TH2F* htransMax_sumTrackpTVsMaxJetpTJP2 = new TH2F("htransMax_sumTrackpTVsMaxJetpTJP2","transMax;  jet p_{T} [GeV]; #Sigmatrack p_{T}",95,5,100,50,0,50);
  TH2F* htransMax_aveTrackpTVsMaxJetpTJP2 = new TH2F("htransMax_aveTrackpTVsMaxJetpTJP2","transMax;  jet p_{T} [GeV]; <track p_{T}> ",95,5,100,30,0,30);
  TH2F* htransMax_maxTrackpTVsMaxJetpTJP2 = new TH2F("htransMax_maxTrackpTVsMaxJetpTJP2","transMax;  jet p_{T} [GeV]; max track p_{T} ",95,5,100,30,0,30);
  TH2F* htransMax_minTrackpTVsMaxJetpTJP2 = new TH2F("htransMax_minTrackpTVsMaxJetpTJP2","transMax;  jet p_{T} [GeV]; min track p_{T} ",95,5,100,30,0,30);

  TH2F* htransMax_numTowerVsMaxJetpTJP2 = new TH2F("htransMax_numTowerVsMaxJetpTJP2","transMax; jet p_{T} [GeV]; tower multiplicity",95,5,100,30,0,30);
  TH2F* htransMax_sumTowerEtVsMaxJetpTJP2 = new TH2F("htransMax_sumTowerEtVsMaxJetpTJP2","transMax;  jet p_{T} [GeV]; #Sigmatower E_{T}",95,5,100,50,0,50);
  TH2F* htransMax_aveTowerEtVsMaxJetpTJP2 = new TH2F("htransMax_aveTowerEtVsMaxJetpTJP2","transMax;  jet p_{T} [GeV]; <tower E_{T}> ",95,5,100,30,0,30);
  TH2F* htransMax_maxTowerEtVsMaxJetpTJP2 = new TH2F("htransMax_maxTowerEtVsMaxJetpTJP2","transMax;  jet p_{T} [GeV]; max tower E_{T} ",95,5,100,30,0,30);
  TH2F* htransMax_minTowerEtVsMaxJetpTJP2 = new TH2F("htransMax_minTowerEtVsMaxJetpTJP2","transMax;  jet p_{T} [GeV]; min tower E_{T} ",95,5,100,30,0,30);
  
  TH2F* htransMax_numTrackVsMaxJetpTJP2_spinbit5 = new TH2F("htransMax_numTrackVsMaxJetpTJP2_spinbit5","transMax; jet p_{T} [GeV]; track multiplicity",95,5,100,30,0,30);
  TH2F* htransMax_sumTrackpTVsMaxJetpTJP2_spinbit5 = new TH2F("htransMax_sumTrackpTVsMaxJetpTJP2_spinbit5","transMax;  jet p_{T} [GeV]; #Sigmatrack p_{T}",95,5,100,50,0,50);
  TH2F* htransMax_aveTrackpTVsMaxJetpTJP2_spinbit5 = new TH2F("htransMax_aveTrackpTVsMaxJetpTJP2_spinbit5","transMax;  jet p_{T} [GeV]; <track p_{T}> ",95,5,100,30,0,30);
  TH2F* htransMax_maxTrackpTVsMaxJetpTJP2_spinbit5 = new TH2F("htransMax_maxTrackpTVsMaxJetpTJP2_spinbit5","transMax;  jet p_{T} [GeV]; max track p_{T} ",95,5,100,30,0,30);
  TH2F* htransMax_minTrackpTVsMaxJetpTJP2_spinbit5 = new TH2F("htransMax_minTrackpTVsMaxJetpTJP2_spinbit5","transMax;  jet p_{T} [GeV]; min track p_{T} ",95,5,100,30,0,30);

  TH2F* htransMax_numTowerVsMaxJetpTJP2_spinbit5 = new TH2F("htransMax_numTowerVsMaxJetpTJP2_spinbit5","transMax; jet p_{T} [GeV]; tower multiplicity",95,5,100,30,0,30);
  TH2F* htransMax_sumTowerEtVsMaxJetpTJP2_spinbit5 = new TH2F("htransMax_sumTowerEtVsMaxJetpTJP2_spinbit5","transMax;  jet p_{T} [GeV]; #Sigmatower E_{T}",95,5,100,50,0,50);
  TH2F* htransMax_aveTowerEtVsMaxJetpTJP2_spinbit5 = new TH2F("htransMax_aveTowerEtVsMaxJetpTJP2_spinbit5","transMax;  jet p_{T} [GeV]; <tower E_{T}> ",95,5,100,30,0,30);
  TH2F* htransMax_maxTowerEtVsMaxJetpTJP2_spinbit5 = new TH2F("htransMax_maxTowerEtVsMaxJetpTJP2_spinbit5","transMax;  jet p_{T} [GeV]; max tower E_{T} ",95,5,100,30,0,30);
  TH2F* htransMax_minTowerEtVsMaxJetpTJP2_spinbit5 = new TH2F("htransMax_minTowerEtVsMaxJetpTJP2_spinbit5","transMax;  jet p_{T} [GeV]; min tower E_{T} ",95,5,100,30,0,30);

  TH2F* htransMax_numTrackVsMaxJetpTJP2_spinbit6 = new TH2F("htransMax_numTrackVsMaxJetpTJP2_spinbit6","transMax; jet p_{T} [GeV]; track multiplicity",95,5,100,30,0,30);
  TH2F* htransMax_sumTrackpTVsMaxJetpTJP2_spinbit6 = new TH2F("htransMax_sumTrackpTVsMaxJetpTJP2_spinbit6","transMax;  jet p_{T} [GeV]; #Sigmatrack p_{T}",95,5,100,50,0,50);
  TH2F* htransMax_aveTrackpTVsMaxJetpTJP2_spinbit6 = new TH2F("htransMax_aveTrackpTVsMaxJetpTJP2_spinbit6","transMax;  jet p_{T} [GeV]; <track p_{T}> ",95,5,100,30,0,30);
  TH2F* htransMax_maxTrackpTVsMaxJetpTJP2_spinbit6 = new TH2F("htransMax_maxTrackpTVsMaxJetpTJP2_spinbit6","transMax;  jet p_{T} [GeV]; max track p_{T} ",95,5,100,30,0,30);
  TH2F* htransMax_minTrackpTVsMaxJetpTJP2_spinbit6 = new TH2F("htransMax_minTrackpTVsMaxJetpTJP2_spinbit6","transMax;  jet p_{T} [GeV]; min track p_{T} ",95,5,100,30,0,30);

  TH2F* htransMax_numTowerVsMaxJetpTJP2_spinbit6 = new TH2F("htransMax_numTowerVsMaxJetpTJP2_spinbit6","transMax; jet p_{T} [GeV]; tower multiplicity",95,5,100,30,0,30);
  TH2F* htransMax_sumTowerEtVsMaxJetpTJP2_spinbit6 = new TH2F("htransMax_sumTowerEtVsMaxJetpTJP2_spinbit6","transMax;  jet p_{T} [GeV]; #Sigmatower E_{T}",95,5,100,50,0,50);
  TH2F* htransMax_aveTowerEtVsMaxJetpTJP2_spinbit6 = new TH2F("htransMax_aveTowerEtVsMaxJetpTJP2_spinbit6","transMax;  jet p_{T} [GeV]; <tower E_{T}> ",95,5,100,30,0,30);
  TH2F* htransMax_maxTowerEtVsMaxJetpTJP2_spinbit6 = new TH2F("htransMax_maxTowerEtVsMaxJetpTJP2_spinbit6","transMax;  jet p_{T} [GeV]; max tower E_{T} ",95,5,100,30,0,30);
  TH2F* htransMax_minTowerEtVsMaxJetpTJP2_spinbit6 = new TH2F("htransMax_minTowerEtVsMaxJetpTJP2_spinbit6","transMax;  jet p_{T} [GeV]; min tower E_{T} ",95,5,100,30,0,30);

  TH2F* htransMax_numTrackVsMaxJetpTJP2_spinbit9 = new TH2F("htransMax_numTrackVsMaxJetpTJP2_spinbit9","transMax; jet p_{T} [GeV]; track multiplicity",95,5,100,30,0,30);
  TH2F* htransMax_sumTrackpTVsMaxJetpTJP2_spinbit9 = new TH2F("htransMax_sumTrackpTVsMaxJetpTJP2_spinbit9","transMax;  jet p_{T} [GeV]; #Sigmatrack p_{T}",95,5,100,50,0,50);
  TH2F* htransMax_aveTrackpTVsMaxJetpTJP2_spinbit9 = new TH2F("htransMax_aveTrackpTVsMaxJetpTJP2_spinbit9","transMax;  jet p_{T} [GeV]; <track p_{T}> ",95,5,100,30,0,30);
  TH2F* htransMax_maxTrackpTVsMaxJetpTJP2_spinbit9 = new TH2F("htransMax_maxTrackpTVsMaxJetpTJP2_spinbit9","transMax;  jet p_{T} [GeV]; max track p_{T} ",95,5,100,30,0,30);
  TH2F* htransMax_minTrackpTVsMaxJetpTJP2_spinbit9 = new TH2F("htransMax_minTrackpTVsMaxJetpTJP2_spinbit9","transMax;  jet p_{T} [GeV]; min track p_{T} ",95,5,100,30,0,30);

  TH2F* htransMax_numTowerVsMaxJetpTJP2_spinbit9 = new TH2F("htransMax_numTowerVsMaxJetpTJP2_spinbit9","transMax; jet p_{T} [GeV]; tower multiplicity",95,5,100,30,0,30);
  TH2F* htransMax_sumTowerEtVsMaxJetpTJP2_spinbit9 = new TH2F("htransMax_sumTowerEtVsMaxJetpTJP2_spinbit9","transMax;  jet p_{T} [GeV]; #Sigmatower E_{T}",95,5,100,50,0,50);
  TH2F* htransMax_aveTowerEtVsMaxJetpTJP2_spinbit9 = new TH2F("htransMax_aveTowerEtVsMaxJetpTJP2_spinbit9","transMax;  jet p_{T} [GeV]; <tower E_{T}> ",95,5,100,30,0,30);
  TH2F* htransMax_maxTowerEtVsMaxJetpTJP2_spinbit9 = new TH2F("htransMax_maxTowerEtVsMaxJetpTJP2_spinbit9","transMax;  jet p_{T} [GeV]; max tower E_{T} ",95,5,100,30,0,30);
  TH2F* htransMax_minTowerEtVsMaxJetpTJP2_spinbit9 = new TH2F("htransMax_minTowerEtVsMaxJetpTJP2_spinbit9","transMax;  jet p_{T} [GeV]; min tower E_{T} ",95,5,100,30,0,30);

  TH2F* htransMax_numTrackVsMaxJetpTJP2_spinbit10 = new TH2F("htransMax_numTrackVsMaxJetpTJP2_spinbit10","transMax; jet p_{T} [GeV]; track multiplicity",95,5,100,30,0,30);
  TH2F* htransMax_sumTrackpTVsMaxJetpTJP2_spinbit10 = new TH2F("htransMax_sumTrackpTVsMaxJetpTJP2_spinbit10","transMax;  jet p_{T} [GeV]; #Sigmatrack p_{T}",95,5,100,50,0,50);
  TH2F* htransMax_aveTrackpTVsMaxJetpTJP2_spinbit10 = new TH2F("htransMax_aveTrackpTVsMaxJetpTJP2_spinbit10","transMax;  jet p_{T} [GeV]; <track p_{T}> ",95,5,100,30,0,30);
  TH2F* htransMax_maxTrackpTVsMaxJetpTJP2_spinbit10 = new TH2F("htransMax_maxTrackpTVsMaxJetpTJP2_spinbit10","transMax;  jet p_{T} [GeV]; max track p_{T} ",95,5,100,30,0,30);
  TH2F* htransMax_minTrackpTVsMaxJetpTJP2_spinbit10 = new TH2F("htransMax_minTrackpTVsMaxJetpTJP2_spinbit10","transMax;  jet p_{T} [GeV]; min track p_{T} ",95,5,100,30,0,30);

  TH2F* htransMax_numTowerVsMaxJetpTJP2_spinbit10 = new TH2F("htransMax_numTowerVsMaxJetpTJP2_spinbit10","transMax; jet p_{T} [GeV]; tower multiplicity",95,5,100,30,0,30);
  TH2F* htransMax_sumTowerEtVsMaxJetpTJP2_spinbit10 = new TH2F("htransMax_sumTowerEtVsMaxJetpTJP2_spinbit10","transMax;  jet p_{T} [GeV]; #Sigmatower E_{T}",95,5,100,50,0,50);
  TH2F* htransMax_aveTowerEtVsMaxJetpTJP2_spinbit10 = new TH2F("htransMax_aveTowerEtVsMaxJetpTJP2_spinbit10","transMax;  jet p_{T} [GeV]; <tower E_{T}> ",95,5,100,30,0,30);
  TH2F* htransMax_maxTowerEtVsMaxJetpTJP2_spinbit10 = new TH2F("htransMax_maxTowerEtVsMaxJetpTJP2_spinbit10","transMax;  jet p_{T} [GeV]; max tower E_{T} ",95,5,100,30,0,30);
  TH2F* htransMax_minTowerEtVsMaxJetpTJP2_spinbit10 = new TH2F("htransMax_minTowerEtVsMaxJetpTJP2_spinbit10","transMax;  jet p_{T} [GeV]; min tower E_{T} ",95,5,100,30,0,30);

  TH2F* htransMin_numTrackVsMaxJetpTJP2 = new TH2F("htransMin_numTrackVsMaxJetpTJP2","transMin; jet p_{T} [GeV]; track multiplicity",95,5,100,30,0,30);
  TH2F* htransMin_sumTrackpTVsMaxJetpTJP2 = new TH2F("htransMin_sumTrackpTVsMaxJetpTJP2","transMin;  jet p_{T} [GeV]; #Sigmatrack p_{T}",95,5,100,50,0,50);
  TH2F* htransMin_aveTrackpTVsMaxJetpTJP2 = new TH2F("htransMin_aveTrackpTVsMaxJetpTJP2","transMin;  jet p_{T} [GeV]; <track p_{T}> ",95,5,100,30,0,30);
  TH2F* htransMin_maxTrackpTVsMaxJetpTJP2 = new TH2F("htransMin_maxTrackpTVsMaxJetpTJP2","transMin;  jet p_{T} [GeV]; max track p_{T} ",95,5,100,30,0,30);
  TH2F* htransMin_minTrackpTVsMaxJetpTJP2 = new TH2F("htransMin_minTrackpTVsMaxJetpTJP2","transMin;  jet p_{T} [GeV]; min track p_{T} ",95,5,100,30,0,30);

  TH2F* htransMin_numTowerVsMaxJetpTJP2 = new TH2F("htransMin_numTowerVsMaxJetpTJP2","transMin; jet p_{T} [GeV]; tower multiplicity",95,5,100,30,0,30);
  TH2F* htransMin_sumTowerEtVsMaxJetpTJP2 = new TH2F("htransMin_sumTowerEtVsMaxJetpTJP2","transMin;  jet p_{T} [GeV]; #Sigmatower E_{T}",95,5,100,50,0,50);
  TH2F* htransMin_aveTowerEtVsMaxJetpTJP2 = new TH2F("htransMin_aveTowerEtVsMaxJetpTJP2","transMin;  jet p_{T} [GeV]; <tower E_{T}> ",95,5,100,30,0,30);
  TH2F* htransMin_maxTowerEtVsMaxJetpTJP2 = new TH2F("htransMin_maxTowerEtVsMaxJetpTJP2","transMin;  jet p_{T} [GeV]; max tower E_{T} ",95,5,100,30,0,30);
  TH2F* htransMin_minTowerEtVsMaxJetpTJP2 = new TH2F("htransMin_minTowerEtVsMaxJetpTJP2","transMin;  jet p_{T} [GeV]; min tower E_{T} ",95,5,100,30,0,30);

  TH2F* htransMin_numTrackVsMaxJetpTJP2_spinbit5 = new TH2F("htransMin_numTrackVsMaxJetpTJP2_spinbit5","transMin; jet p_{T} [GeV]; track multiplicity",95,5,100,30,0,30);
  TH2F* htransMin_sumTrackpTVsMaxJetpTJP2_spinbit5 = new TH2F("htransMin_sumTrackpTVsMaxJetpTJP2_spinbit5","transMin;  jet p_{T} [GeV]; #Sigmatrack p_{T}",95,5,100,50,0,50);
  TH2F* htransMin_aveTrackpTVsMaxJetpTJP2_spinbit5 = new TH2F("htransMin_aveTrackpTVsMaxJetpTJP2_spinbit5","transMin;  jet p_{T} [GeV]; <track p_{T}> ",95,5,100,30,0,30);
  TH2F* htransMin_maxTrackpTVsMaxJetpTJP2_spinbit5 = new TH2F("htransMin_maxTrackpTVsMaxJetpTJP2_spinbit5","transMin;  jet p_{T} [GeV]; max track p_{T} ",95,5,100,30,0,30);
  TH2F* htransMin_minTrackpTVsMaxJetpTJP2_spinbit5 = new TH2F("htransMin_minTrackpTVsMaxJetpTJP2_spinbit5","transMin;  jet p_{T} [GeV]; min track p_{T} ",95,5,100,30,0,30);

  TH2F* htransMin_numTowerVsMaxJetpTJP2_spinbit5 = new TH2F("htransMin_numTowerVsMaxJetpTJP2_spinbit5","transMin; jet p_{T} [GeV]; tower multiplicity",95,5,100,30,0,30);
  TH2F* htransMin_sumTowerEtVsMaxJetpTJP2_spinbit5 = new TH2F("htransMin_sumTowerEtVsMaxJetpTJP2_spinbit5","transMin;  jet p_{T} [GeV]; #Sigmatower E_{T}",95,5,100,50,0,50);
  TH2F* htransMin_aveTowerEtVsMaxJetpTJP2_spinbit5 = new TH2F("htransMin_aveTowerEtVsMaxJetpTJP2_spinbit5","transMin;  jet p_{T} [GeV]; <tower E_{T}> ",95,5,100,30,0,30);
  TH2F* htransMin_maxTowerEtVsMaxJetpTJP2_spinbit5 = new TH2F("htransMin_maxTowerEtVsMaxJetpTJP2_spinbit5","transMin;  jet p_{T} [GeV]; max tower E_{T} ",95,5,100,30,0,30);
  TH2F* htransMin_minTowerEtVsMaxJetpTJP2_spinbit5 = new TH2F("htransMin_minTowerEtVsMaxJetpTJP2_spinbit5","transMin;  jet p_{T} [GeV]; min tower E_{T} ",95,5,100,30,0,30);

  TH2F* htransMin_numTrackVsMaxJetpTJP2_spinbit6 = new TH2F("htransMin_numTrackVsMaxJetpTJP2_spinbit6","transMin; jet p_{T} [GeV]; track multiplicity",95,5,100,30,0,30);
  TH2F* htransMin_sumTrackpTVsMaxJetpTJP2_spinbit6 = new TH2F("htransMin_sumTrackpTVsMaxJetpTJP2_spinbit6","transMin;  jet p_{T} [GeV]; #Sigmatrack p_{T}",95,5,100,50,0,50);
  TH2F* htransMin_aveTrackpTVsMaxJetpTJP2_spinbit6 = new TH2F("htransMin_aveTrackpTVsMaxJetpTJP2_spinbit6","transMin;  jet p_{T} [GeV]; <track p_{T}> ",95,5,100,30,0,30);
  TH2F* htransMin_maxTrackpTVsMaxJetpTJP2_spinbit6 = new TH2F("htransMin_maxTrackpTVsMaxJetpTJP2_spinbit6","transMin;  jet p_{T} [GeV]; max track p_{T} ",95,5,100,30,0,30);
  TH2F* htransMin_minTrackpTVsMaxJetpTJP2_spinbit6 = new TH2F("htransMin_minTrackpTVsMaxJetpTJP2_spinbit6","transMin;  jet p_{T} [GeV]; min track p_{T} ",95,5,100,30,0,30);

  TH2F* htransMin_numTowerVsMaxJetpTJP2_spinbit6 = new TH2F("htransMin_numTowerVsMaxJetpTJP2_spinbit6","transMin; jet p_{T} [GeV]; tower multiplicity",95,5,100,30,0,30);
  TH2F* htransMin_sumTowerEtVsMaxJetpTJP2_spinbit6 = new TH2F("htransMin_sumTowerEtVsMaxJetpTJP2_spinbit6","transMin;  jet p_{T} [GeV]; #Sigmatower E_{T}",95,5,100,50,0,50);
  TH2F* htransMin_aveTowerEtVsMaxJetpTJP2_spinbit6 = new TH2F("htransMin_aveTowerEtVsMaxJetpTJP2_spinbit6","transMin;  jet p_{T} [GeV]; <tower E_{T}> ",95,5,100,30,0,30);
  TH2F* htransMin_maxTowerEtVsMaxJetpTJP2_spinbit6 = new TH2F("htransMin_maxTowerEtVsMaxJetpTJP2_spinbit6","transMin;  jet p_{T} [GeV]; max tower E_{T} ",95,5,100,30,0,30);
  TH2F* htransMin_minTowerEtVsMaxJetpTJP2_spinbit6 = new TH2F("htransMin_minTowerEtVsMaxJetpTJP2_spinbit6","transMin;  jet p_{T} [GeV]; min tower E_{T} ",95,5,100,30,0,30);

  TH2F* htransMin_numTrackVsMaxJetpTJP2_spinbit9 = new TH2F("htransMin_numTrackVsMaxJetpTJP2_spinbit9","transMin; jet p_{T} [GeV]; track multiplicity",95,5,100,30,0,30);
  TH2F* htransMin_sumTrackpTVsMaxJetpTJP2_spinbit9 = new TH2F("htransMin_sumTrackpTVsMaxJetpTJP2_spinbit9","transMin;  jet p_{T} [GeV]; #Sigmatrack p_{T}",95,5,100,50,0,50);
  TH2F* htransMin_aveTrackpTVsMaxJetpTJP2_spinbit9 = new TH2F("htransMin_aveTrackpTVsMaxJetpTJP2_spinbit9","transMin;  jet p_{T} [GeV]; <track p_{T}> ",95,5,100,30,0,30);
  TH2F* htransMin_maxTrackpTVsMaxJetpTJP2_spinbit9 = new TH2F("htransMin_maxTrackpTVsMaxJetpTJP2_spinbit9","transMin;  jet p_{T} [GeV]; max track p_{T} ",95,5,100,30,0,30);
  TH2F* htransMin_minTrackpTVsMaxJetpTJP2_spinbit9 = new TH2F("htransMin_minTrackpTVsMaxJetpTJP2_spinbit9","transMin;  jet p_{T} [GeV]; min track p_{T} ",95,5,100,30,0,30);

  TH2F* htransMin_numTowerVsMaxJetpTJP2_spinbit9 = new TH2F("htransMin_numTowerVsMaxJetpTJP2_spinbit9","transMin; jet p_{T} [GeV]; tower multiplicity",95,5,100,30,0,30);
  TH2F* htransMin_sumTowerEtVsMaxJetpTJP2_spinbit9 = new TH2F("htransMin_sumTowerEtVsMaxJetpTJP2_spinbit9","transMin;  jet p_{T} [GeV]; #Sigmatower E_{T}",95,5,100,50,0,50);
  TH2F* htransMin_aveTowerEtVsMaxJetpTJP2_spinbit9 = new TH2F("htransMin_aveTowerEtVsMaxJetpTJP2_spinbit9","transMin;  jet p_{T} [GeV]; <tower E_{T}> ",95,5,100,30,0,30);
  TH2F* htransMin_maxTowerEtVsMaxJetpTJP2_spinbit9 = new TH2F("htransMin_maxTowerEtVsMaxJetpTJP2_spinbit9","transMin;  jet p_{T} [GeV]; max tower E_{T} ",95,5,100,30,0,30);
  TH2F* htransMin_minTowerEtVsMaxJetpTJP2_spinbit9 = new TH2F("htransMin_minTowerEtVsMaxJetpTJP2_spinbit9","transMin;  jet p_{T} [GeV]; min tower E_{T} ",95,5,100,30,0,30);

  TH2F* htransMin_numTrackVsMaxJetpTJP2_spinbit10 = new TH2F("htransMin_numTrackVsMaxJetpTJP2_spinbit10","transMin; jet p_{T} [GeV]; track multiplicity",95,5,100,30,0,30);
  TH2F* htransMin_sumTrackpTVsMaxJetpTJP2_spinbit10 = new TH2F("htransMin_sumTrackpTVsMaxJetpTJP2_spinbit10","transMin;  jet p_{T} [GeV]; #Sigmatrack p_{T}",95,5,100,50,0,50);
  TH2F* htransMin_aveTrackpTVsMaxJetpTJP2_spinbit10 = new TH2F("htransMin_aveTrackpTVsMaxJetpTJP2_spinbit10","transMin;  jet p_{T} [GeV]; <track p_{T}> ",95,5,100,30,0,30);
  TH2F* htransMin_maxTrackpTVsMaxJetpTJP2_spinbit10 = new TH2F("htransMin_maxTrackpTVsMaxJetpTJP2_spinbit10","transMin;  jet p_{T} [GeV]; max track p_{T} ",95,5,100,30,0,30);
  TH2F* htransMin_minTrackpTVsMaxJetpTJP2_spinbit10 = new TH2F("htransMin_minTrackpTVsMaxJetpTJP2_spinbit10","transMin;  jet p_{T} [GeV]; min track p_{T} ",95,5,100,30,0,30);

  TH2F* htransMin_numTowerVsMaxJetpTJP2_spinbit10 = new TH2F("htransMin_numTowerVsMaxJetpTJP2_spinbit10","transMin; jet p_{T} [GeV]; tower multiplicity",95,5,100,30,0,30);
  TH2F* htransMin_sumTowerEtVsMaxJetpTJP2_spinbit10 = new TH2F("htransMin_sumTowerEtVsMaxJetpTJP2_spinbit10","transMin;  jet p_{T} [GeV]; #Sigmatower E_{T}",95,5,100,50,0,50);
  TH2F* htransMin_aveTowerEtVsMaxJetpTJP2_spinbit10 = new TH2F("htransMin_aveTowerEtVsMaxJetpTJP2_spinbit10","transMin;  jet p_{T} [GeV]; <tower E_{T}> ",95,5,100,30,0,30);
  TH2F* htransMin_maxTowerEtVsMaxJetpTJP2_spinbit10 = new TH2F("htransMin_maxTowerEtVsMaxJetpTJP2_spinbit10","transMin;  jet p_{T} [GeV]; max tower E_{T} ",95,5,100,30,0,30);
  TH2F* htransMin_minTowerEtVsMaxJetpTJP2_spinbit10 = new TH2F("htransMin_minTowerEtVsMaxJetpTJP2_spinbit10","transMin;  jet p_{T} [GeV]; min tower E_{T} ",95,5,100,30,0,30);
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
    if(track->pt() > trackThresh){ cout << "track pT > 30 GeV" << track->pt() <<  endl; return true;}
  }
  return false;
}
