//
// Grant Webb
// August 18, 2015
// Creating the data and MC comparisons 


void MakeUnderlyingEventPlotsDataEmbed(int n=1, int p=0)
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

  const Int_t nbin=100;
  const Int_t rbin=4;
  const char trig[10] = "JP2";
  double Lumi[13];
  normalize(Lumi);
  switch(n)
    {
  
    case 1: // Number of Tracks
      {
	char name[100]=Form("htoward_numTracksVsMaxJetpT%s",trig);
	char name2[100]=Form("haway_numTracksVsMaxJetpT%s",trig);
	char name3[100]=Form("htransverse_numTracksVsMaxJetpT%s",trig);

	char embdname[100]=Form("toward_numTracksVsMaxJetpT%s",trig);
	char embdname2[100]=Form("away_numTracksVsMaxJetpT%s",trig);
	char embdname3[100]=Form("transverse_numTracksVsMaxJetpT%s",trig);

	char pname[100]=Form("numTrackDensityVsMaxJetpT%s_pp500_akT_dataembd.png",trig); 
	break;
      }
    case 2: // Sum Track pT
      {
	char name[100]=Form("htoward_sumTrackpTVsMaxJetpT%s",trig);
	char name2[100]=Form("haway_sumTrackpTVsMaxJetpT%s",trig);
	char name3[100]=Form("htransverse_sumTrackpTVsMaxJetpT%s",trig);

	char embdname[100]=Form("toward_sumTrackpTVsMaxJetpT%s",trig);
	char embdname2[100]=Form("away_sumTrackpTVsMaxJetpT%s",trig);
	char embdname3[100]=Form("transverse_sumTrackpTVsMaxJetpT%s",trig);
	cout << "CHECK! " << endl;
	char pname[100]=Form("sumTrackpTDensityVsMaxJetpT%s_pp500_akT_dataembd.png",trig); 
	break;
      }
    case 3: // Number of Towers
      {
	char name[100]=Form("htoward_numTowersVsMaxJetpT%s",trig);
	char name2[100]=Form("haway_numTowersVsMaxJetpT%s",trig);
	char name3[100]=Form("htransverse_numTowersVsMaxJetpT%s",trig);

	char embdname[100]=Form("toward_numTowersVsMaxJetpT%s",trig);
	char embdname2[100]=Form("away_numTowersVsMaxJetpT%s",trig);
	char embdname3[100]=Form("transverse_numTowersVsMaxJetpT%s",trig);
	
	char pname[100]=Form("numTowerDensityVsMaxJetpT%s_pp500_akT_dataembd.png",trig); 
	break;
      }
    case 4: // Sum Tower Et
      {
	char name[100]=Form("htoward_sumTowerEtVsMaxJetpT%s",trig);
	char name2[100]=Form("haway_sumTowerEtVsMaxJetpT%s",trig);
	char name3[100]=Form("htransverse_sumTowerEtVsMaxJetpT%s",trig);
	
	char embdname[100]=Form("toward_sumTowerEtVsMaxJetpT%s",trig);
	char embdname2[100]=Form("away_sumTowerEtVsMaxJetpT%s",trig);
	char embdname3[100]=Form("transverse_sumTowerEtVsMaxJetpT%s",trig);


	char pname[100]=Form("sumTowerEtDensityVsMaxJetpT%s_pp500_akT_dataembd.png",trig); 
	break;
      }
   case 5: // Sum pT (track pT + tower Et) 
      {
	char name[100]=Form("htoward_sumPtVsMaxJetpT%s",trig);
	char name2[100]=Form("haway_sumPtVsMaxJetpT%s",trig);
	char name3[100]=Form("htransverse_sumPtVsMaxJetpT%s",trig);
	
	char embdname[100]=Form("toward_sumPtVsMaxJetpT%s",trig);
	char embdname2[100]=Form("away_sumPtVsMaxJetpT%s",trig);
	char embdname3[100]=Form("transverse_sumPtVsMaxJetpT%s",trig);


	char pname[100]=Form("sumPtDensityVsMaxJetpT%s_pp500_akT_dataembd.png",trig); 
	break;
      }
    }  
  if(n == 1){legend1 = new TLegend(0.11,0.58,0.46,0.89);}
  if(n == 2){legend1 = new TLegend(0.11,0.58,0.46,0.89);}
  if(n == 3){legend1 = new TLegend(0.11,0.58,0.46,0.89);}
  if(n == 4){legend1 = new TLegend(0.11,0.55,0.5,0.89);}
  if(n == 5){legend1 = new TLegend(0.11,0.55,0.5,0.89);}
  legend1->SetFillColor(0);
  legend1->SetBorderSize(0);
  gStyle->SetPalette(1);
  gStyle->SetOptStat(0);
  gStyle->SetOptDate(0);
  TCanvas *c1=new TCanvas("c1","c1",800,800);

  //--------------- Data Histograms-------------  
  TH2F *histogram_Tow = (TH2F*)datafile->Get(name);
  TH2F *histogram_Awa = (TH2F*)datafile->Get(name2);
  TH2F *histogram_Trans = (TH2F*)datafile->Get(name3);
  // -------------------------------------------

  //---------------Embedding Histograms------------
  
  
  TH2F* comboEmbdHist_Tow = new TH2F(embdname,embdname,40,0,80,20,0,20);  
  TH2F* comboEmbdHist_Awa = new TH2F(embdname2,embdname2,40,0,80,20,0,20);  
  TH2F* comboEmbdHist_Trans = new TH2F(embdname3,embdname3,40,0,80,20,0,20); 
  
  comboALL2(embdfile,name,comboEmbdHist_Tow,Lumi);
  comboALL2(embdfile,name2,comboEmbdHist_Awa,Lumi); 
  comboALL2(embdfile,name3,comboEmbdHist_Trans,Lumi); 

  //  -----------------------------------------------
  cout << " Toward Number of Events: (matched) " << comboEmbdHist_Tow->GetEntries() <<  endl;  
  cout <<" Away Number of Events: (matched) " << comboEmbdHist_Awa->GetEntries() <<  endl;  
  cout << " Trans Number of Events: (matched) " << comboEmbdHist_Trans->GetEntries() <<  endl;
  //Toward Region:
  
  TProfile *profileTow = new TProfile("profileTow","profileTow",100,0,100);
  profileTow = histogram_Tow->ProfileX("profileTow",1, 100); 
  profileTow->SetMarkerStyle(20);
  profileTow->SetMarkerColor(2);
  profileTow->SetLineColor(2);
  profileTow->SetMarkerSize(1.5);
  legend1->AddEntry(profileTow, "Toward Region", "p" );
  profileTow->Rebin(2);
  
  TProfile *profleTow_embd = new TProfile("profileTow_embd","profileToe_embd",100,0,100);
  profileTow_embd = comboEmbdHist_Tow->ProfileX("profileTow_embd",1, 100);
  profileTow_embd->SetMarkerStyle(29);
  profileTow_embd->SetMarkerColor(2);
  profileTow_embd->SetLineColor(2);
  profileTow_embd->SetMarkerSize(1.5);
  legend1->AddEntry(profileTow_embd, "MC Toward Region", "p" );
  profileTow_embd->Rebin(2);
  //Away Region:
  
  TProfile *profileAwa = new TProfile("profileAwa","profileAwa",100,0,100); 
  profileAwa = histogram_Awa->ProfileX("profileAwa",1,100);
  profileAwa->SetMarkerStyle(20);
  profileAwa->SetMarkerColor(3);
  profileAwa->SetLineColor(3);
  profileAwa->SetMarkerSize(1.5);
  legend1->AddEntry(profileAwa, "Away Region", "p" );
  profileAwa->Rebin(2);

  TProfile *profleAwa_embd = new TProfile("profileAwa_embd","profileToe_embd",100,0,100);
  profileAwa_embd = comboEmbdHist_Awa->ProfileX("profileAwa_embd",1, 100);
  profileAwa_embd->SetMarkerStyle(29);
  profileAwa_embd->SetMarkerColor(3);
  profileAwa_embd->SetLineColor(3);
  profileAwa_embd->SetMarkerSize(1.5);
  legend1->AddEntry(profileAwa_embd, "MC Away Region", "p" );
  profileAwa_embd->Rebin(2);
 //Transverse Region:	
  
  TProfile *profileTrans = new TProfile("profileTrans","profileTrans",100,0,100);
  profileTrans = histogram_Trans->ProfileX("profileTrans",1,100);
  profileTrans->SetMarkerStyle(20);
  profileTrans->SetMarkerColor(4);
  profileTrans->SetLineColor(4);
  profileTrans->SetMarkerSize(1.5);
  legend1->AddEntry(profileTrans, "Transverse Region", "p" );
  profileTrans->Rebin(2);

  TProfile *profleTrans_embd = new TProfile("profileTrans_embd","profileTrans_embd",100,0,100);
  profileTrans_embd = comboEmbdHist_Trans->ProfileX("profileTran_embd",1, 100);
  profileTrans_embd->SetMarkerStyle(29);
  profileTrans_embd->SetMarkerColor(4);
  profileTrans_embd->SetLineColor(4);
  profileTrans_embd->SetMarkerSize(1.5);
  legend1->AddEntry(profileTrans_embd, "MC Transverse Region", "p" );
  profileTrans_embd->Rebin(2);

  //------------------ Draw Histograms --------------
  legend1->SetHeader(Form("pp 500 GeV %s Trigger: ",trig));
  profileTow->SetTitle("");
  profileTow->Draw();
  //------Axis and Labelling---------------
  TAxis *x1 = profileTow->GetXaxis();
  TAxis *y1 = profileTow->GetYaxis();
  y1->CenterTitle();
  x1->SetTitle("Leading Jet p_{T} (GeV)"); x1->SetRangeUser(0,70);
  if(n ==1){y1->SetTitle("<N_{ch}>/[#Delta#eta#Delta(#Delta#phi)]"); y1->SetRangeUser(0,4); TLine *line =  new TLine(13.0,0,13.0,4);}
  if(n ==2){y1->SetTitle("<#Sigmap_{T,ch}>/[#Delta#eta#Delta(#Delta#phi)]"); y1->SetRangeUser(0,10); TLine *line =  new TLine(13.0,0,13.0,10);}
  if(n ==3){y1->SetTitle("<#SigmaE_{T}>/[#Delta#eta#Delta(#Delta#phi)]"); y1->SetRangeUser(0,10); TLine *line =  new TLine(13.0,0,13.0,10);}
  if(n ==4){y1->SetTitle("<N_{0}>/[#Delta#eta#Delta(#Delta#phi)]"); y1->SetRangeUser(0,10); TLine *line =  new TLine(13.0,0,13.0,10);}
  if(n ==5){y1->SetTitle("<#Sigmap_{T}>/[#Delta#eta#Delta(#Delta#phi)]"); y1->SetRangeUser(0,20); TLine *line =  new TLine(13.0,0,13.0,20);}
  //-----------------------------------
  profileTow_embd->Draw("same");
  profileAwa->Draw("same");
  profileAwa_embd->Draw("same");
  profileTrans->Draw("same");
  profileTrans_embd->Draw("same");
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
    cout << "pt bin: " << i << " numEntries: "  <<  pt[i]->GetEntries() << endl;
    pt[i]->Scale(1.0/ Norm[i]);
    pt[i]->Scale(Norm[i]);
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
