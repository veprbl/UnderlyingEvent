/* 
This runs the over the jet, skim, ue trees. Fills histograms. This is a stream lined
version Reducing the number of histograms to just the sum and num towers and tracks vs jet pT.
Check out oldMacros_sumTrackpT/*.C for finding many other histograms made
 */

class StJetCandidate;
class StJetVertex;
class StJetSkimTrig;

#include <map>

void RunOffAxisConeUEAnalysis(int nentries = 1E8,
			      const char* jetfile  = "/gpfs01/star/scratch/zchang/Run12Jets_final/13078014/st_physics_13078014_raw_4020001.jets.root",
			      const char* skimfile = "/gpfs01/star/scratch/zchang/Run12Jets_final/13078014/st_physics_13078014_raw_4020001.skim.root",
			      const char* outfile = "testOffAxis_jetQAData500Gev_13078014.root",
			      const Int_t  mEmbed = 0)
{
  cout << "nentries = " << nentries << endl;
  cout << "jetfile  = " << jetfile  << endl;
  cout << "skimfile = " << skimfile << endl;
  cout << "outfile  = " << outfile << endl;
  const float area  =  4*TMath::Pi()/3;
  const float area2 =  2*TMath::Pi()/3;
  
  
  // Load libraries
  gSystem->Load("StJetEvent");
  gSystem->Load("StJetSkimEvent");
  // Open jet & skim files
  TChain* jetChain  = new TChain("jet");
  TChain* skimChain = new TChain("jetSkimTree");
  
  jetChain->Add(jetfile);
  skimChain->Add(skimfile);
  
  // Set jet buffer
  StJetEvent* jetEvent = new StJetEvent();
  jetChain->SetBranchAddress("AntiKtR060NHits12",&jetEvent);

  // Set skim buffer
  StJetSkimEvent* skimEvent = new StJetSkimEvent();
  skimChain->SetBranchAddress("skimEventBranch",&skimEvent); 
  
  // Open output file for writing
  TFile* ofile = TFile::Open(outfile,"recreate");
  assert(ofile);
  
  BookHists();
  
  for (int iEntry = 0; iEntry < nentries; ++iEntry) {
    
    if (jetChain->GetEvent(iEntry) <= 0 || skimChain->GetEvent(iEntry) <= 0) break;
    // Should not be null
    
    assert(jetEvent && skimEvent);
    
    // Enforce event synchronization
    assert(jetEvent->runId() == skimEvent->runId() && jetEvent->eventId() == skimEvent->eventId());
    
    if (iEntry % 1000 == 0) cout << iEntry << endl;
    //   hrunnumber->Fill(jetEvent->runId());
    
    //JP2 trigger
    StJetSkimTrig* trigJP2 = skimEvent->trigger(380403);
    if (!trigJP2) trigJP2 = skimEvent->trigger(380403);
    bool flagtrigJP2 = trigPass(trigJP2, mEmbed); // hardware and software triggers
    map<int,int> barrelJetPatches = skimEvent->barrelJetPatchesAboveTh(2);

    StJetVertex* vertex = jetEvent->vertex();
    bool vertexBool = vertexPass(vertex);
    if(!vertexBool) continue;    

    StJetCandidate *leadingjet = findLeadingJet(vertex); // Leading jet from jet 
    float pt = leadingjet->pt();
    map<string, float> ue = leadingjet->ueDensity();
    float conesumpTdensity = ue["OffAxisConesR050"];
    //    float dpt = ue["OffAxisConesR050"]*area;
   
    if(TMath::Abs(leadingjet->detEta()) > 0.5) { continue;}
    if(leadingjet->rt() > 0.9){continue;} 
    bool trackpT_high = hightrackpT(leadingjet);
    if(trackpT_high) continue;    
    Bool_t geoFlagJP2  = matchedToJetPatch(leadingjet,barrelJetPatches); // Geo Flag

    //    leadingJetpT = leadingjet->pt(); //Define the leading jet pT 
    if( flagtrigJP2 && geoFlagJP2){//did, should, and geo trigs fired 

      hleadingjetpTJP2->Fill(pt);
      hConesumpTdensity->Fill(conesumpTdensity);
      hConeSumpTdensityVsleadingjetpTJP2->Fill(pt,conesumpTdensity);
      
    }// End of JP2 if statement 
  }//End of Event Loop
  ofile->Write();
  ofile->Close();
}


void BookHists()
{
  //Book histograms
  TH1F* hleadingjetpTJP2 = new TH1F("hleadingjetpTJP2",";Leading jet p_{T} [GeV]",40,0,80);
  TH1F* hConesumpTdensity = new TH1F("hConesumpTdensity", ";cone sum density", 50,0,5);
  TH2F* hConeSumpTdensityVsleadingjetpTJP2 = new TH2F("hConeSumpTdensityVsleadingjetpTJP2",";Leading jet p_{T} [GeV]",40,0,80,50,0,5);



}

Bool_t vertexPass(StJetVertex *vertex)
{
  if (!vertex) return false;
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
