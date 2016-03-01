//
// Grant Webb
// August 18, 2015
// Creating the data comparison between the Run 9 and Run 12 sum pT densities  


void MakeUnderlyingEventPlotsDataRun9Run12(int n=1, int p=0)
{
  TFile *datafileRun9 = new TFile("/star/u/gdwebb/UE_CVS_Check/radius06/st_physics_AllRuns.uehist.root");
  TFile *datafileRun12 = new TFile("/star/u/gdwebb/UE_CVS_Check/radius06/st_physics_Run12allFiles.root");


  const Int_t nbin=100;
  const Int_t rbin=4;
  const char trig[10] = "JP2";


  char nameRun9[100]=Form("htransverse_sumPtVsMaxJetpT%s",trig);
  char nameRun12[100]=Form("hConeSumpTdensityVsleadingjetpT%s",trig);
  char pname[100]=Form("sumtrackpTdensityVsMaxJetpT%s_run9run12.png",trig); 

      
  legend1 = new TLegend(0.11,0.58,0.65,0.89);
 
  legend1->SetFillColor(0);
  legend1->SetBorderSize(0);
  gStyle->SetPalette(1);
  gStyle->SetOptStat(0);
  gStyle->SetOptDate(0);
  TCanvas *c1=new TCanvas("c1","c1",800,800);

  //--------------- Data Histograms-------------  
 
  TH2F *histogram_TransRun9 = (TH2F*)datafileRun9->Get(nameRun9);
  TH2F *histogram_TransRun12 = (TH2F*)datafileRun12->Get(nameRun12);
  // -------------------------------------------


 
 //Transverse Region:	
  
  TProfile *profileTransRun9 = new TProfile("profileTransRun9","profileTransRun9",100,0,100);
  profileTransRun9 = histogram_TransRun9->ProfileX("profileTransRun9",1,100);
  profileTransRun9->SetMarkerStyle(20);
  profileTransRun9->SetMarkerColor(kBlue);
  profileTransRun9->SetLineColor(kBlue);
  profileTransRun9->SetMarkerSize(1.5);
  legend1->AddEntry(profileTransRun9, "Transverse Region Run 9 Region", "p" );
  profileTransRun9->Rebin(2);

  TProfile *profleTransRun12 = new TProfile("profileTransRun12","profileTransRun12",100,0,100);
  profileTransRun12 = histogram_TransRun12->ProfileX("profileTranRun12",1, 100);
  profileTransRun12->SetMarkerStyle(20);
  profileTransRun12->SetMarkerColor(kRed);
  profileTransRun12->SetLineColor(kRed);
  profileTransRun12->SetMarkerSize(1.5);
  legend1->AddEntry(profileTransRun12, "Transverse Region Run 12 Off Cone", "p" );
  profileTransRun12->Rebin(2);

  //------------------ Draw Histograms --------------
  legend1->SetHeader(Form("pp 500 GeV %s Trigger Data: ",trig));
  profileTransRun9->SetTitle("");
  profileTransRun9->Draw();
  //------Axis and Labelling---------------
  TAxis *x1 = profileTransRun9->GetXaxis();
  TAxis *y1 = profileTransRun9->GetYaxis();
  y1->CenterTitle();
  x1->SetTitle("Leading Jet p_{T} (GeV)"); x1->SetRangeUser(0,70);

  y1->SetTitle("<#Sigmap_{T}>/[#Delta#eta#Delta(#Delta#phi)]"); y1->SetRangeUser(0.2,2); TLine *line =  new TLine(13.0,0.2,13.0,2);

  //-----------------------------------
  profileTransRun12->Draw("same");
  line->SetLineWidth(2); line->SetLineStyle(2);
  line->Draw();
  legend1->Draw(); 
 if(p==1){c1->Print(pname);}
}



