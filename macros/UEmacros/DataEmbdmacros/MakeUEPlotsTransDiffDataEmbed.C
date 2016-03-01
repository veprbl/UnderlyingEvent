// Grant Webb
// August 18, 2015
// Creating the data plots only 


void MakeUEPlotsTransDiffDataEmbed(int n=1, int p=0)
{
  TFile *datafile = new TFile("/gpfs01/star/i_bnl/gdwebb/Run9/UEAnalysis/Data/st_physics_AllRuns.uehist.root");
  TFile *embdfile[12];
  embdfile[1] = new TFile("/gpfs01/star/i_bnl/gdwebb/Run9/UEAnalysis/Embed_inclu/st_physics_4_5.uehists.root");
  embdfile[2] = new TFile("/gpfs01/star/i_bnl/gdwebb/Run9/UEAnalysis/Embed_inclu/st_physics_5_7.uehists.root");
  embdfile[3] = new TFile("/gpfs01/star/i_bnl/gdwebb/Run9/UEAnalysis/Embed_inclu/st_physics_7_9.uehists.root");
  embdfile[4] = new TFile("/gpfs01/star/i_bnl/gdwebb/Run9/UEAnalysis/Embed_inclu/st_physics_9_11.uehists.root");
  embdfile[5] = new TFile("/gpfs01/star/i_bnl/gdwebb/Run9/UEAnalysis/Embed_inclu/st_physics_11_15.uehists.root");
  embdfile[6] = new TFile("/gpfs01/star/i_bnl/gdwebb/Run9/UEAnalysis/Embed_inclu/st_physics_15_25.uehists.root");
  embdfile[7] = new TFile("/gpfs01/star/i_bnl/gdwebb/Run9/UEAnalysis/Embed_inclu/st_physics_25_35.uehists.root");
  embdfile[8] = new TFile("/gpfs01/star/i_bnl/gdwebb/Run9/UEAnalysis/Embed_inclu/st_physics_35_45.uehists.root");
  embdfile[9] = new TFile("/gpfs01/star/i_bnl/gdwebb/Run9/UEAnalysis/Embed_inclu/st_physics_45_55.uehists.root");
  embdfile[10] = new TFile("/gpfs01/star/i_bnl/gdwebb/Run9/UEAnalysis/Embed_inclu/st_physics_55_65.uehists.root");
  embdfile[11] = new TFile("/gpfs01/star/i_bnl/gdwebb/Run9/UEAnalysis/Embed_inclu/st_physics_65_75.uehists.root");
  embdfile[12] = new TFile("/gpfs01/star/i_bnl/gdwebb/Run9/UEAnalysis/Embed_inclu/st_physics_75_-1.uehists.root");
   TH1F *evt2, *evt[12];
   const Int_t nbin=100;
   const Int_t rbin=4;
   const Double_t PI = TMath::Pi();
   const char trig[10] = "JP2";
   double Lumi[13];
   normalize(Lumi);
   switch(n)
     {
     case 1: // Average Track pT vs Jet pT
       {
	char name3[100]=Form("htransMax_aveTrackpTVsMaxJetpT%s",trig);
	char name4[100]=Form("htransMin_aveTrackpTVsMaxJetpT%s",trig);
	
	char embdname3[100]=Form("transMax_aveTrackpTVsMaxJetpT%s",trig);
	char embdname4[100]=Form("transMin_aveTrackpTVsMaxJetpT%s",trig);
	char pname[100]=Form("transMinMax_aveTrackpTVsMaxJetpT%s_pp500_akT.png",trig); 
	break;
      }
     case 2: // Average Track Multiplicity vs Jet pT
       {
	 char name3[100]=Form("htransMax_numTrackVsMaxJetpT%s",trig);
	 char name4[100]=Form("htransMin_numTrackVsMaxJetpT%s",trig);
	 
	 char embdname3[100]=Form("transMax_numTrackpTVsMaxJetpT%s",trig);
	 char embdname4[100]=Form("transMin_numTrackpTVsMaxJetpT%s",trig);
	 char pname[100]=Form("transMinMax_numTrackVsMaxJetpT%s_pp500_akT.png",trig); 
	break;
       }
     case 3: // Average Sum Track pT vs Jet pT
       {
	 char name3[100]=Form("htransMax_sumTrackpTVsMaxJetpT%s",trig);
	 char name4[100]=Form("htransMin_sumTrackpTVsMaxJetpT%s",trig);

	 char embdname3[100]=Form("transMax_sumTrackpTVsMaxJetpT%s",trig);
	 char embdname4[100]=Form("transMin_sumTrackpTVsMaxJetpT%s",trig);
	 char pname[100]=Form("transMinMax_sumTrackpTVsMaxJetpT%s_pp500_akT.png",trig); 
	 break;
       }
     case 4: // Average Tower Et vs Jet pT
       {
	char name3[100]=Form("htransMax_aveTowerEtVsMaxJetpT%s",trig);
	char name4[100]=Form("htransMin_aveTowerEtVsMaxJetpT%s",trig);

	char embdname3[100]=Form("transMax_aveTowerEtVsMaxJetpT%s",trig);
	char embdname4[100]=Form("transMin_aveTowerEtVsMaxJetpT%s",trig);
	char pname[100]=Form("transMinMax_aveTowerEtVsMaxJetpT%s_pp500_akT.png",trig); 
	break;
      }
     case 5: // Average Tower Multiplicity vs Jet pT
       {
	 char name3[100]=Form("htransMax_numTowerVsMaxJetpT%s",trig);
	 char name4[100]=Form("htransMin_numTowerVsMaxJetpT%s",trig);

	 char embdname3[100]=Form("transMax_numTowerEtVsMaxJetpT%s",trig);
	 char embdname4[100]=Form("transMin_numTowerEtVsMaxJetpT%s",trig);
	 char pname[100]=Form("transMinMax_numTowerVsMaxJetpT%s_pp500_akT.png",trig); 
	 break;
       }
     case 6: // Average Sum Tower Et vs Jet pT
       {
	 char name3[100]=Form("htransMax_sumTowerEtVsMaxJetpT%s",trig);
	 char name4[100]=Form("htransMin_sumTowerEtVsMaxJetpT%s",trig);

	 char embdname3[100]=Form("transMax_sumTowerEtVsMaxJetpT%s",trig);
	 char embdname4[100]=Form("transMin_sumTowerEtVsMaxJetpT%s",trig);
	 char pname[100]=Form("transMinMax_sumTowerEtVsMaxJetpT%s_pp500_akT.png",trig); 
	 break;
       }
     case 7: // Average Max Tower Et vs Jet pT
       {
	 char name3[100]=Form("htransMax_maxTowerEtVsMaxJetpT%s",trig);
	 char name4[100]=Form("htransMin_maxTowerEtVsMaxJetpT%s",trig);
	 
	 char embdname3[100]=Form("transMax_sumTowerEtVsMaxJetpT%s",trig);
	 char embdname4[100]=Form("transMin_sumTowerEtVsMaxJetpT%s",trig);
	 char pname[100]=Form("transMinMax_maxTowerEtVsMaxJetpT%s_pp500_akT.png",trig); 
	 break;
       }
 case 8: // Average Max Track pT vs Jet pT
       {
	 char name3[100]=Form("htransMax_maxTrackpTVsMaxJetpT%s",trig);
	 char name4[100]=Form("htransMin_maxTrackpTVsMaxJetpT%s",trig);

	 char embdname3[100]=Form("transMin_maxTrackpTVsMaxJetpT%s",trig);
	 char embdname4[100]=Form("transMax_maxTrackpTVsMaxJetpT%s",trig);
	 char pname[100]=Form("transMinMax_maxTrackpTVsMaxJetpT%s_pp500_akT.png",trig); 
	 break;
       }
     }
   legend1 = new TLegend(0.12,0.67,0.42,0.87);
   if( n == 0){legend1 = new TLegend(0.5,0.35,0.8,0.55);}
   legend1->SetFillColor(0);
   legend1->SetBorderSize(0);
   gStyle->SetPalette(1);
   gStyle->SetOptStat(0);
   gStyle->SetOptDate(0);
   TCanvas *c1=new TCanvas("c1","c1",800,800);
   //--------- Data Histograms ------------------------
   TH2F *histogram_TranMax = (TH2F*)datafile->Get(name3);
   cout << "data number of events trans max: " << histogram_TranMax->GetEntries() << endl;
   TH2F *histogram_TranMin = (TH2F*)datafile->Get(name4);
   cout << "data number of events trans min: " << histogram_TranMin->GetEntries() << endl;
   //TH2F* histogram_Trans = histogram_TranMax->Clone("pythiaTrans");
   // histogram_Trans->Add(histogram_TranMin);
   // cout << "data number of events trans add: " << histogram_Trans->GetEntries() << endl;
   TH2F* histogram_TranDiff = histogram_TranMax->Clone("data_transDiff");
   histogram_TranDiff->Add(histogram_TranMin, -1);

   cout << "data number of events trans sub: " << histogram_TranDiff->GetEntries() << endl;
   //---------------Embedding Histograms------------
   
   if(n == 3 || n ==6){
     TH2F* comboEmbdHist_TranMax = new TH2F(embdname3,embdname3,95,5,100,50,0,50); 
     TH2F* comboEmbdHist_TranMin = new TH2F(embdname4,embdname4,95,5,100,50,0,50);
   }
   else{
     TH2F* comboEmbdHist_TranMax = new TH2F(embdname3,embdname3,95,5,100,30,0,30); 
     TH2F* comboEmbdHist_TranMin = new TH2F(embdname4,embdname4,95,5,100,30,0,30);
   }
   comboALL2(embdfile,name3,comboEmbdHist_TranMax,Lumi); 
   comboALL2(embdfile,name4,comboEmbdHist_TranMin,Lumi); 
   cout << "embd number of events trans max: " << comboEmbdHist_TranMax->GetEntries() << endl;
   cout << "embd number of events trans min: " << comboEmbdHist_TranMin->GetEntries() << endl;
   //   TH2F* comboEmbdHist_Trans = comboEmbdHist_TranMax->Clone("perugia0Trans");
   //  comboEmbdHist_Trans->Add(comboEmbdHist_TranMin);
   // cout << "embd number of events trans add: " << comboEmbdHist_Trans->GetEntries() << endl;
   //  -----------------------------------------------


   TH2F* comboEmbdHist_TransDiff = comboEmbdHist_TranMax->Clone("MCTransDiff");
   comboEmbdHist_TransDiff->Add(comboEmbdHist_TranMin, -1);
   cout << "embd number of events trans sub: " << comboEmbdHist_TransDiff->GetEntries() << endl;
   //   Transverse Region:	
  
   // TProfile *profileTrans = new TProfile("profileTrans","profileTrans",100,0,100);
   // profileTrans = histogram_Trans->ProfileX("profileTrans",1,100);
   // // profileTrans->Scale(PI*(1.0/3.0));
   // profileTrans->SetMarkerStyle(20);
   // profileTrans->SetMarkerColor(kBlue);
   // profileTrans->SetLineColor(kBlue);
   // profileTrans->SetMarkerSize(1.5);

   // TProfile *profileTrans_embd = new TProfile("profileTrans_embd","profileTrans_embd",100,0,100);
   // profileTrans_embd = comboEmbdHist_Trans->ProfileX("profileTrans_embd",1,100);
   // //  profileTrans_embd->Scale(PI*(1.0/3.0));
   // profileTrans_embd->SetMarkerStyle(29);
   // profileTrans_embd->SetMarkerColor(kBlue);
   // profileTrans_embd->SetLineColor(kBlue);
   // profileTrans_embd->SetMarkerSize(1.5);

   TProfile *profileTranMax = new TProfile("profileTranMax","profileTranMax",100,0,100);
   profileTranMax = histogram_TranMax->ProfileX("profileTranMax",1,100);
   //  profileTranMax->Scale(PI/3);
   profileTranMax->SetMarkerStyle(22);
   profileTranMax->SetMarkerColor(kBlue-5);
   profileTranMax->SetLineColor(kBlue-5);
   profileTranMax->SetMarkerSize(1.5);
   
   TProfile *profileTranMax_embd = new TProfile("profileTranMax_embd","profileTranMax_embd",100,0,100);
   profileTranMax_embd = comboEmbdHist_TranMax->ProfileX("profileTranMax_embd",1,100);
   //   profileTranMax_embd->Scale(3.0/PI);
   profileTranMax_embd->SetMarkerStyle(29);
   profileTranMax_embd->SetMarkerColor(kBlue-5);
   profileTranMax_embd->SetLineColor(kBlue-5);
   profileTranMax_embd->SetMarkerSize(1.5);

   TProfile *profileTranMin = new TProfile("profileTranMin","profileTranMin",100,0,100);
   profileTranMin = histogram_TranMin->ProfileX("profileTranMin",1,100);
   // profileTranMin->Scale(PI/3);
   profileTranMin->SetMarkerStyle(23);
   profileTranMin->SetMarkerColor(kCyan-5);
   profileTranMin->SetLineColor(kCyan-5);
   profileTranMin->SetMarkerSize(1.5);

   TProfile *profileTranMin_embd = new TProfile("profileTranMin_embd","profileTranMin_embd",100,0,100);
   profileTranMin_embd = comboEmbdHist_TranMin->ProfileX("profileTranMin_embd",1,100);
   //  profileTranMin_embd->Scale(PI/3);
   profileTranMin_embd->SetMarkerStyle(29);
   profileTranMin_embd->SetMarkerColor(kCyan-5);
   profileTranMin_embd->SetLineColor(kCyan-5);
   profileTranMin_embd->SetMarkerSize(1.5);

   //----------------  Trans Diff (TransMax - TransMin)   --------- 
   TProfile *profileTranDiff = new TProfile("profileTranDiff","profileTranDiff",100,0,100);
   profileTranDiff = histogram_TranDiff->ProfileX("profileTranDiff",1,100);
   // profileTranDiff->Scale(PI/3);
   profileTranDiff->SetMarkerStyle(23);
   profileTranDiff->SetMarkerColor(kMagenta-2);
   profileTranDiff->SetLineColor(kMagenta-2);
   profileTranDiff->SetMarkerSize(1.5);

   TProfile *profileTranDiff_embd = new TProfile("profileTranDiff_embd","profileTranDiff_embd",100,0,100);
   profileTranDiff_embd = comboEmbdHist_TransDiff->ProfileX("profileTranDiff_embd",1,100);
   //  profileTranDiff_embd->Scale(PI/3);
   profileTranDiff_embd->SetMarkerStyle(29);
   profileTranDiff_embd->SetMarkerColor(kMagenta-2);
   profileTranDiff_embd->SetLineColor(kMagenta-2);
   profileTranDiff_embd->SetMarkerSize(1.5);
   //--------------------------------------------------------

   
   //  legend1->AddEntry(profileTrans, "Transverse Region", "p" );
   //  legend1->AddEntry(profileTrans_embd, "Transverse Region MC", "p" );
   legend1->AddEntry(profileTranMax, "Trans Max Region", "p" );
   legend1->AddEntry(profileTranMax_embd, "Transverse Max Region MC", "p" );
   legend1->AddEntry(profileTranMin, "Trans Min Region", "p" );
   legend1->AddEntry(profileTranMin_embd, "Transverse Min Region MC", "p" );
   legend1->AddEntry(profileTranDiff, "Trans Diff Region", "p" );
   legend1->AddEntry(profileTranDiff_embd, "Transverse Diff Region MC", "p" );

   legend1->SetHeader(Form("pp 500 GeV %s Trigger: ",trig));
   profileTranDiff->SetTitle("");
   profileTranDiff->Draw();
  
    TAxis *x1 = profileTranDiff->GetXaxis();
    TAxis *y1 = profileTranDiff->GetYaxis();
    y1->CenterTitle();
    x1->SetTitle("Leading Jet p_{T}"); x1->SetRangeUser(0,70);
   if(n ==1){y1->SetTitle(" <p_{T,track}> (GeV)"); y1->SetRangeUser(0.45,0.9);}
   if(n ==2){y1->SetTitle("Track Multiplicity"); y1->SetRangeUser(1.5,5);}
   if(n ==3){y1->SetTitle("#Sigmap_{T,track}"); y1->SetRangeUser(0.5,3);}
   if(n ==4){y1->SetTitle("<E_{T}>"); y1->SetRangeUser(0.4,0.6);}
   if(n ==5){y1->SetTitle("Tower Multiplicity"); y1->SetRangeUser(2,5);}
   if(n ==6){y1->SetTitle("#SigmaE_{T}"); y1->SetRangeUser(0.7,1.7);}
   if(n ==7){y1->SetTitle("E_{T,max}"); y1->SetRangeUser(0.5,0.7);}
   if(n ==8){y1->SetTitle("p_{T,max}"); y1->SetRangeUser(0.5,1.2);}
   profileTranDiff_embd->Draw("same");
   // profileTranMin->Draw("same");
   // profileTranMin_embd->Draw("same");
   // profileTranMax->Draw("same");   
   // profileTranMax_embd->Draw("same");  
   
   legend1->Draw();
   if(p==1){c1->Print(pname);}
   
}

void comboALL2(TFile *t[12],char pta[100],TH2F *totH,double Norm[12]){
    
   
  Double_t XSEC=0.000000001447;//55
  const int lowP=1;
  TH2F *pt[13];
  for (int i=lowP;i<13;i++){
    pt[i]=(TH2F*) t[i]->Get(pta);
    pt[i]->Sumw2();
    pt[i]->Scale(1.0/ Norm[i]);
    // pt[i]->Scale(Norm[i]);
    totH->Add(pt[i]);
  }
}

void normalize(double Lumi[13]){
  double NumEvts[13]; 
  // Number of events for the inclusive jet embedding
  NumEvts[1] =981735; //4-5
  NumEvts[2] =492293; // 5-7
  NumEvts[3] =492293; // 7-9
  NumEvts[4] =492293; // 9-11
  NumEvts[5] = 443057;  // 11-15
  NumEvts[6] = 393837;  // 15-25
  NumEvts[7] = 389429;  // 25-35
  NumEvts[8] = 389128;  // 35-45
  NumEvts[9] = 98209;  // 45-55
  NumEvts[10] =24131;   // 55-65 
  NumEvts[11] =5906;    // 65-75
  NumEvts[12] =2957;    // 75--1
  
  Double_t Xsec[13];
  Double_t MinbXsec=31.42;
  Xsec[1]=1.482;//4
  Xsec[2]=0.7490;//5 
  Xsec[3]=0.1551;//7
  Xsec[4]=0.0450;//9
  Xsec[5]=0.02211;//11
  Xsec[6]=0.005710;//15
  Xsec[7]=0.0003425;//25
  Xsec[8]=0.00004323;//35
  Xsec[9]=0.0000079240;//45
  Xsec[10]=0.0000018090;//55
  Xsec[11]=0.00000047350;//65
  Xsec[12]=0.00000019520;//75
  for(int j = 1; j <= 12; j++)
    {
      Lumi[j] = NumEvts[j]/Xsec[j];
      cout << "Lumi: " << Lumi[j] << endl;
    }
}
