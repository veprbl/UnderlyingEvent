// Grant Webb
// August 18, 2015
// Creating the data plots only 


void MakeUEPlotsTransMaxMinDataEmbed(int n=1, int p=0)
{
  TFile *datafile = new TFile("/star/u/gdwebb/Test_UEpp500/radius06/st_physics_AllRuns.uehist.root");
  TFile *embdfile[12];
  embdfile[1] = new TFile("/star/u/gdwebb/Test_UEpp500/radius06/st_physics_4_5.uehists.root");
  embdfile[2] = new TFile("/star/u/gdwebb/Test_UEpp500/radius06/st_physics_5_7.uehists.root");
  embdfile[3] = new TFile("/star/u/gdwebb/Test_UEpp500/radius06/st_physics_7_9.uehists.root");
  embdfile[4] = new TFile("/star/u/gdwebb/Test_UEpp500/radius06/st_physics_9_11.uehists.root");
  embdfile[5] = new TFile("/star/u/gdwebb/Test_UEpp500/radius06/st_physics_11_15.uehists.root");
  embdfile[6] = new TFile("/star/u/gdwebb/Test_UEpp500/radius06/st_physics_15_25.uehists.root");
  embdfile[7] = new TFile("/star/u/gdwebb/Test_UEpp500/radius06/st_physics_25_35.uehists.root");
  embdfile[8] = new TFile("/star/u/gdwebb/Test_UEpp500/radius06/st_physics_35_45.uehists.root");
  embdfile[9] = new TFile("/star/u/gdwebb/Test_UEpp500/radius06/st_physics_45_55.uehists.root");
  embdfile[10] = new TFile("/star/u/gdwebb/Test_UEpp500/radius06/st_physics_55_65.uehists.root");
  embdfile[11] = new TFile("/star/u/gdwebb/Test_UEpp500/radius06/st_physics_65_75.uehists.root");
  embdfile[12] = new TFile("/star/u/gdwebb/Test_UEpp500/radius06/st_physics_75_-1.uehists.root");
   TH1F *evt2, *evt[12];
   const Int_t nbin=100;
   const Int_t rbin=4;
   const Double_t PI = TMath::Pi();
   const char trig[10] = "JP2";
   double Lumi[13];
   normalize(Lumi);
   switch(n)
     {
    
     case 1: // Average Track Multiplicity vs Jet pT
       {
	 char name3[100]=Form("htransMax_numTracksVsMaxJetpT%s",trig);
	 char name4[100]=Form("htransMin_numTracksVsMaxJetpT%s",trig);
	 char name5[100]=Form("htransverse_numTracksVsMaxJetpT%s",trig);

	 char embdname3[100]=Form("transMax_numTracksVsMaxJetpT%s",trig);
	 char embdname4[100]=Form("transMin_numTracksVsMaxJetpT%s",trig);
	 char embdname5[100]=Form("htransverse_numTracksVsMaxJetpT%s",trig);

	 char pname[100]=Form("transMinMax_numTrackDensityVsMaxJetpT%s_pp500_akT.png",trig); 
	break;
       }
     case 2: // Average Sum Track pT vs Jet pT
       {
	 char name3[100]=Form("htransMax_sumTrackpTVsMaxJetpT%s",trig);
	 char name4[100]=Form("htransMin_sumTrackpTVsMaxJetpT%s",trig);
	 char name5[100]=Form("htransverse_sumTrackpTVsMaxJetpT%s",trig);

	 char embdname3[100]=Form("transMax_sumTrackpTVsMaxJetpT%s",trig);
	 char embdname4[100]=Form("transMin_sumTrackpTVsMaxJetpT%s",trig);
	 char embdname5[100]=Form("htransverse_sumTrackpTVsMaxJetpT%s",trig);
	 char pname[100]=Form("transMinMax_sumTrackpTDensityVsMaxJetpT%s_pp500_akT.png",trig); 
	 break;
       }
    
     case 3: // Average Tower Multiplicity vs Jet pT
       {
	 char name3[100]=Form("htransMax_numTowersVsMaxJetpT%s",trig);
	 char name4[100]=Form("htransMin_numTowersVsMaxJetpT%s",trig);
	 char name5[100]=Form("htransverse_numTowersVsMaxJetpT%s",trig);

	 char embdname3[100]=Form("transMax_numTowersVsMaxJetpT%s",trig);
	 char embdname4[100]=Form("transMin_numTowersVsMaxJetpT%s",trig);
	 char embdname5[100]=Form("transverse_numTowersVsMaxJetpT%s",trig);
	 char pname[100]=Form("transMinMax_numTowerDensityVsMaxJetpT%s_pp500_akT.png",trig); 
	 break;
       }
     case 4: // Average Sum Tower Et vs Jet pT
       {
	 char name3[100]=Form("htransMax_sumTowerEtVsMaxJetpT%s",trig);
	 char name4[100]=Form("htransMin_sumTowerEtVsMaxJetpT%s",trig);
	 char name5[100]=Form("htransverse_sumTowerEtVsMaxJetpT%s",trig);

	 char embdname3[100]=Form("transMax_sumTowerEtVsMaxJetpT%s",trig);
	 char embdname4[100]=Form("transMin_sumTowerEtVsMaxJetpT%s",trig);
	 char embdname5[100]=Form("transverse_sumTowerEtVsMaxJetpT%s",trig);
	 char pname[100]=Form("transMinMax_sumTowerEtDensityVsMaxJetpT%s_pp500_akT.png",trig); 
	 break;
       }

     case 5: // Average Sum pT vs Jet pT
       {
	 char name3[100]=Form("htransMax_sumpTVsMaxJetpT%s",trig);
	 char name4[100]=Form("htransMin_sumpTVsMaxJetpT%s",trig);
	 char name5[100]=Form("htransverse_sumPtVsMaxJetpT%s",trig);
	 
	 char embdname3[100]=Form("transMax_sumpTVsMaxJetpT%s",trig);
	 char embdname4[100]=Form("transMin_sumpTVsMaxJetpT%s",trig);
	 char embdname5[100]=Form("transverse_sumpTVsMaxJetpT%s",trig);
	 char pname[100]=Form("transMinMax_sumpTDensityVsMaxJetpT%s_pp500_akT.png",trig); 
	 break;
       }
    
     }
   if(n == 1){legend1 = new TLegend(0.12,0.62,0.52,0.89);}
   if(n == 2){legend1 = new TLegend(0.12,0.66,0.52,0.89);}
   if(n == 3){legend1 = new TLegend(0.25,0.12,0.78,0.34);}
   if(n == 4){legend1 = new TLegend(0.25,0.65,0.78,0.89);}
   if(n == 5){legend1 = new TLegend(0.25,0.65,0.78,0.89);}

   legend1->SetFillColor(0);
   legend1->SetBorderSize(0);
   gStyle->SetPalette(1);
   gStyle->SetOptStat(0);
   gStyle->SetOptDate(0);
   TCanvas *c1=new TCanvas("c1","c1",800,800);
   //--------- Data Histograms ------------------------
   TH2F *histogram_TranMax = (TH2F*)datafile->Get(name3);
   TH2F *histogram_TranMin = (TH2F*)datafile->Get(name4);
   TH2F *histogram_Trans = (TH2F*)datafile->Get(name5);
     
   //---------------Embedding Histograms------------
   
   TH2F* comboEmbdHist_TranMax = new TH2F(embdname3,embdname3,40,0,80,20,0,20); 
   TH2F* comboEmbdHist_TranMin = new TH2F(embdname4,embdname4,40,0,80,20,0,20);
   TH2F* comboEmbdHist_Trans = new TH2F(embdname5,embdname5,40,0,80,20,0,20);
   
   comboALL2(embdfile,name3,comboEmbdHist_TranMax,Lumi); 
   comboALL2(embdfile,name4,comboEmbdHist_TranMin,Lumi); 
   comboALL2(embdfile,name5,comboEmbdHist_Trans,Lumi); 

   //  -----------------------------------------------
   //TH2F* histogram_TranDiff = histogram_TranMax->Clone();
   // histogram_TranDiff->Add(histogram_TranMin);

   // TH2F *histogram_TranDiff = histogram_TranMax->Clone();
   // int nx = histogram_TranDiff->GetXaxis()->GetNbins();
   // int ny = histogram_TranDiff->GetYaxis()->GetNbins();
   // for (int i=1;i<=nx;i++) {
   //   for (int j=1;j<=ny;j++) {
   //     double v1 =histogram_TranDiff->GetBinContent(i,j);
   //     if (v1 > 0) {
   //       double v2 = histogram_TranMin->GetBinContent(i,j);
   // 	 cout << "v1: " << v1 << " v2: " << v2  << " diff: " <<  v1- v2 << endl;
   // 	 histogram_TranDiff->SetBinContent(i,j,v1-v2);
   //     }
   //   }
   // }
   // histogram_TranDiff->Draw("colz");
   //   histogram_TranDiff->Add(*histogram_TranMin, -1);
   //   histogram_Trans->Add(histogram_TranMin);
   //   TH1F *histoTrackpT_TranMax = (TH1F*)datafile->Get("htransP_trackpTJP2");
   // TH1F *histoTrackpT_TranMin = (TH1F*)datafile->Get("htransM_trackpTJP2");
   
   //   Transverse Region:	
  
   TProfile *profileTrans = new TProfile("profileTrans","profileTrans",100,0,100);
   profileTrans = histogram_Trans->ProfileX("profileTrans",1,100);
   profileTrans->SetMarkerStyle(20);
   profileTrans->SetMarkerColor(4);
   profileTrans->SetLineColor(4);
   profileTrans->SetMarkerSize(1.5);
   profileTrans->Rebin(2);

   TProfile *profileTrans_embd = new TProfile("profileTrans_embd","profileTrans_embd",100,0,100);
   profileTrans_embd = comboEmbdHist_Trans->ProfileX("profileTrans_embd",1,100);
   profileTrans_embd->SetMarkerStyle(29);
   profileTrans_embd->SetMarkerColor(4);
   profileTrans_embd->SetLineColor(4);
   profileTrans_embd->SetMarkerSize(1.5);
   profileTrans_embd->Rebin(2);

   TProfile *profileTranMax = new TProfile("profileTranMax","profileTranMax",100,0,100);
   profileTranMax = histogram_TranMax->ProfileX("profileTranMax",1,100);
   profileTranMax->SetMarkerStyle(22);
   profileTranMax->SetMarkerColor(kBlue-5);
   profileTranMax->SetLineColor(kBlue-5);
   profileTranMax->SetMarkerSize(1.5);
   profileTranMax->Rebin(2);
   
   TProfile *profileTranMax_embd = new TProfile("profileTranMax_embd","profileTranMax_embd",100,0,100);
   profileTranMax_embd = comboEmbdHist_TranMax->ProfileX("profileTranMax_embd",1,100);
   profileTranMax_embd->SetMarkerStyle(29);
   profileTranMax_embd->SetMarkerColor(kBlue-5);
   profileTranMax_embd->SetLineColor(kBlue-5);
   profileTranMax_embd->SetMarkerSize(1.5);
   profileTranMax_embd->Rebin(2);

   TProfile *profileTranMin = new TProfile("profileTranMin","profileTranMin",100,0,100);
   profileTranMin = histogram_TranMin->ProfileX("profileTranMin",1,100);
   profileTranMin->SetMarkerStyle(23);
   profileTranMin->SetMarkerColor(kCyan-5);
   profileTranMin->SetLineColor(kCyan-5);
   profileTranMin->SetMarkerSize(1.5);
   profileTranMin->Rebin(2);

   TProfile *profileTranMin_embd = new TProfile("profileTranMin_embd","profileTranMin_embd",100,0,100);
   profileTranMin_embd = comboEmbdHist_TranMin->ProfileX("profileTranMin_embd",1,100);
   profileTranMin_embd->SetMarkerStyle(29);
   profileTranMin_embd->SetMarkerColor(kCyan-5);
   profileTranMin_embd->SetLineColor(kCyan-5);
   profileTranMin_embd->SetMarkerSize(1.5);
   profileTranMin_embd->Rebin(2);

   
   legend1->AddEntry(profileTrans, "Transverse Region", "p" );
   legend1->AddEntry(profileTrans_embd, "Transverse Region MC", "p" );
   legend1->AddEntry(profileTranMax, "Trans Max Region", "p" );
   legend1->AddEntry(profileTranMax_embd, "Transverse Max Region MC", "p" );
   legend1->AddEntry(profileTranMin, "Trans Min Region", "p" );
   legend1->AddEntry(profileTranMin_embd, "Transverse Min Region MC", "p" );
   legend1->SetHeader(Form("pp 500 GeV %s Trigger: ",trig));
   profileTrans->SetTitle("");
   profileTrans->Draw();
   
   TAxis *x1 = profileTrans->GetXaxis();
   TAxis *y1 = profileTrans->GetYaxis();
   y1->CenterTitle();
   x1->SetTitle("Leading Jet p_{T} (GeV)"); x1->SetRangeUser(0,70);
  
   if(n ==1){y1->SetTitle(" <N_{ch}>/[#Delta#eta#Delta(#Delta#phi)]"); y1->SetRangeUser(0.4,2.1); TLine *line =  new TLine(13.0,0.4,13.0,2.1);}
   if(n ==2){y1->SetTitle("<#Sigmap_{T,ch}>/[#Delta#eta#Delta(#Delta#phi)]"); y1->SetRangeUser(0.4,1.4); TLine *line =  new TLine(13.0,0.4,13.0,1.4);}
  
   if(n ==3){y1->SetTitle("<N_{0}>/[#Delta#eta#Delta(#Delta#phi)]"); y1->SetRangeUser(0,2);TLine *line =  new TLine(13.0,0,13.0,2);}
   if(n ==4){y1->SetTitle("<#SigmaE_{T}>/[#Delta#eta#Delta(#Delta#phi)]"); y1->SetRangeUser(0.4,1.1);TLine *line =  new TLine(13.0,0.4,13.0,1.1);}
   if(n ==5){y1->SetTitle("<#Sigmap_{T}>/[#Delta#eta#Delta(#Delta#phi)]"); y1->SetRangeUser(0.4,2.6); TLine *line =  new TLine(13.0,0.4,13.0,2.6);}
  
   profileTrans_embd->Draw("same");
   profileTranMax->Draw("same");   
   profileTranMax_embd->Draw("same"); 
   profileTranMin->Draw("same");
   profileTranMin_embd->Draw("same");
   
   line->SetLineWidth(2); line->SetLineStyle(2);
   line->Draw();
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
