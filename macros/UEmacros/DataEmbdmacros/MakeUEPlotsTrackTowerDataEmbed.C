//
// Grant Webb
// August 18, 2015
// Creating the data plots for Track and tower information 


void MakeUEPlotsTrackTowerDataEmbed(int n=1, int p=0)
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
  const char trig[10] = "JP2";
  double Lumi[13];
  normalize(Lumi);
  switch(n)
    {
    case 1: // Track pT
      {
	 char name[100]=Form("htoward_trackpT%s",trig);
	 char name2[100]=Form("haway_trackpT%s",trig);
	 char name3[100]=Form("htransP_trackpT%s",trig);
	 char name4[100]=Form("htransM_trackpT%s",trig);

	 char embdname[100]=Form("etoward_trackpT%s",trig);
	 char embdname2[100]=Form("eaway_trackpT%s",trig);
	 char embdname3[100]=Form("etransP_trackpT%s",trig);
	 char embdname4[100]=Form("etransM_trackpT%s",trig);

	 char pname[100]=Form("trackpTAllRegions%s_pp500_akT_dataembd.png",trig);
	 break;
       }
     case 2: // Track eta
       {
	 char name[100]=Form("htoward_tracketa%s",trig);
	 char name2[100]=Form("haway_tracketa%s",trig);
	 char name3[100]=Form("htransP_tracketa%s",trig);
	 char name4[100]=Form("htransM_tracketa%s",trig);

	 char embdname[100]=Form("etoward_tracketa%s",trig);
	 char embdname2[100]=Form("eaway_tracketa%s",trig);
	 char embdname3[100]=Form("etransP_tracketa%s",trig);
	 char embdname4[100]=Form("etransM_tracketa%s",trig);
	 char pname[100]=Form("tracketaAllRegions%s_pp500_akT_dataembd.png",trig);
	 break;       
       }
     case 3: // Track phi
       {
	 char name[100]=Form("htoward_trackphi%s",trig);
	 char name2[100]=Form("haway_trackphi%s",trig);
	 char name3[100]=Form("htransP_trackphi%s",trig);
	 char name4[100]=Form("htransM_trackphi%s",trig);

	 char embdname[100]=Form("etoward_trackphi%s",trig);
	 char embdname2[100]=Form("eaway_trackphi%s",trig);
	 char embdname3[100]=Form("etransP_trackphi%s",trig);
	 char embdname4[100]=Form("etransM_trackphi%s",trig);
	 char pname[100]=Form("trackphiAllRegions%s_pp500_akT_dataembd.png",trig);
	 break;
       }
     case 4: // Tower Et
       {
	 char name[100]=Form("htoward_towerET%s",trig);
	 char name2[100]=Form("haway_towerET%s",trig);
	 char name3[100]=Form("htransP_towerET%s",trig);
	 char name4[100]=Form("htransM_towerET%s",trig);

	 char embdname[100]=Form("etoward_towerET%s",trig);
	 char embdname2[100]=Form("eaway_towerET%s",trig);
	 char embdname3[100]=Form("etransP_towerET%s",trig);
	 char embdname4[100]=Form("etransM_towerET%s",trig);
	 char pname[100]=Form("towerEtAllRegions%s_pp500_akT_dataembd.png",trig);
	 break;
       }
     case 5: // Tower eta
       {
	 char name[100]=Form("htoward_towereta%s",trig);
	 char name2[100]=Form("haway_towereta%s",trig);
	 char name3[100]=Form("htransP_towereta%s",trig);
	 char name4[100]=Form("htransM_towereta%s",trig);

	 char embdname[100]=Form("etoward_towereta%s",trig);
	 char embdname2[100]=Form("eaway_towereta%s",trig);
	 char embdname3[100]=Form("etransP_towereta%s",trig);
	 char embdname4[100]=Form("etransM_towereta%s",trig);
	 char pname[100]=Form("toweretaAllRegions%s_pp500_akT_dataembd.png",trig);
	 break;       
       }
     case 6: // Tower phi
       {
	 char name[100]=Form("htoward_towerphi%s",trig);
	 char name2[100]=Form("haway_towerphi%s",trig);
	 char name3[100]=Form("htransP_towerphi%s",trig);
	 char name4[100]=Form("htransM_towerphi%s",trig);

	 char embdname[100]=Form("etoward_towerphi%s",trig);
	 char embdname2[100]=Form("eaway_towerphi%s",trig);
	 char embdname3[100]=Form("etransP_towerphi%s",trig);
	 char embdname4[100]=Form("etransM_towerphi%s",trig);
	 char pname[100]=Form("towerphiAllRegions%s_pp500_akT_dataembd.png",trig);
	 break;
       }


     }
   legend1 = new TLegend(0.12,0.67,0.42,0.87);
   if(n == 1 || n ==4){legend1 = new TLegend(0.5,0.45,0.8,0.65);}
   gStyle->SetPalette(1);
   gStyle->SetOptStat(0);
   gStyle->SetOptDate(0);
   TCanvas *c1=new TCanvas("c1","c1",800,800);
   //--------Data Histograms-------------
   TH1F *histogram_Tow = (TH1F*)datafile->Get(name);
   TH1F *histogram_Awa = (TH1F*)datafile->Get(name2);
   TH1F *histogram_TranP = (TH1F*)datafile->Get(name3);
   TH1F *histogram_TranM = (TH1F*)datafile->Get(name4);
   TH1F *histogram_Trans = histogram_TranP->Clone("dataTrans");
   histogram_Trans->Add(histogram_TranM);
   //--------------------------------------------

   // --------Embd Histograms---------------------
   if(n == 1 || n ==4){ //Track and tower pT
     TH1F* comboEmbdHist_Tow = new TH1F(embdname,embdname,1000,0,50);  
     TH1F* comboEmbdHist_Awa = new TH1F(embdname2,embdname2,1000,0,50);  
     TH1F* comboEmbdHist_TranP = new TH1F(embdname3,embdname3,1000,0,50); 
     TH1F* comboEmbdHist_TranM = new TH1F(embdname4,embdname4,1000,0,50);
   }
   else if(n ==2 || n ==5){ // Track and tower eta
     TH1F* comboEmbdHist_Tow = new TH1F(embdname,embdname,66,-1.5,1.5);  
     TH1F* comboEmbdHist_Awa = new TH1F(embdname2,embdname2,66,-1.5,1.5);  
     TH1F* comboEmbdHist_TranP = new TH1F(embdname3,embdname3,66,-1.5,1.5); 
     TH1F* comboEmbdHist_TranM = new TH1F(embdname4,embdname4,66,-1.5,1.5);
   }
   else{ // Track and tower phi
     TH1F* comboEmbdHist_Tow = new TH1F(embdname,embdname,120,-3.14159,3.14159);  
     TH1F* comboEmbdHist_Awa = new TH1F(embdname2,embdname2,120,-3.14159,3.14159);  
     TH1F* comboEmbdHist_TranP = new TH1F(embdname3,embdname3,120,-3.14159,3.14159); 
     TH1F* comboEmbdHist_TranM = new TH1F(embdname4,embdname4,120,-3.14159,3.14159);
   }
   comboALL(embdfile,name,comboEmbdHist_Tow,Lumi);
   comboALL(embdfile,name2,comboEmbdHist_Awa,Lumi); 
   comboALL(embdfile,name3,comboEmbdHist_TranP,Lumi); 
   comboALL(embdfile,name4,comboEmbdHist_TranM,Lumi); 
   TH1F* comboEmbdHist_Trans = comboEmbdHist_TranP->Clone("embedTrans");
   comboEmbdHist_Trans->Add(comboEmbdHist_TranM);
   
   //---------------------------------------------
   

   //------- Normalization -----
   Double_t normdata[3], normembd[3];
   normdata[0] = histogram_Tow->Integral();
   normdata[1] = histogram_Awa->Integral();
   normdata[2] = histogram_Trans->Integral();
   histogram_Tow->Sumw2(); histogram_Awa->Sumw2();histogram_Trans->Sumw2();
   histogram_Tow->Scale(1.0/normdata[0]); histogram_Awa->Scale(1.0/normdata[1]); histogram_Trans->Scale(1.0/normdata[2]);

   normembd[0] = comboEmbdHist_Tow->Integral();
   normembd[1] = comboEmbdHist_Awa->Integral();
   normembd[2] = comboEmbdHist_Trans->Integral();
   comboEmbdHist_Tow->Scale(1.0/normembd[0]);comboEmbdHist_Awa->Scale(1.0/normembd[1]); comboEmbdHist_Trans->Scale(1.0/normembd[2]);
   // -------------------

   //Rebin Histograms
   if(n ==1 || n ==4){
     histogram_Tow->Rebin(2);   histogram_Awa->Rebin(2);   histogram_Trans->Rebin(2);
     comboEmbdHist_Tow->Rebin(2);comboEmbdHist_Awa->Rebin(2);   comboEmbdHist_Trans->Rebin(2);
   }
   // 
   histogram_Tow->SetMarkerColor(2);
   histogram_Tow->SetMarkerStyle(20);
   legend1->AddEntry(histogram_Tow, "Toward Region", "p" );

   comboEmbdHist_Tow->SetMarkerColor(2);
   comboEmbdHist_Tow->SetMarkerStyle(24);
   legend1->AddEntry(comboEmbdHist_Tow, "MC Toward Region", "p" );

   histogram_Awa->SetMarkerColor(kGreen+2);
   histogram_Awa->SetMarkerStyle(20);
   legend1->AddEntry(histogram_Awa, "Away Region", "p" );

   comboEmbdHist_Awa->SetMarkerColor(kGreen+2);
   comboEmbdHist_Awa->SetMarkerStyle(24);
   legend1->AddEntry(comboEmbdHist_Awa, "MC Away Region", "p" );

   histogram_Trans->SetMarkerColor(4);
   histogram_Trans->SetMarkerStyle(20);
   legend1->AddEntry(histogram_Trans, "Transverse Region", "p" );

   comboEmbdHist_Trans->SetMarkerColor(4);
   comboEmbdHist_Trans->SetMarkerStyle(24);
   legend1->AddEntry(comboEmbdHist_Trans, "MC Transvere Region", "p" );
   
   legend1->SetHeader(Form("pp 500 GeV %s Trigger: ",trig));
   histogram_Tow->SetTitle("");
   histogram_Tow->Draw();

   TAxis *x1 = histogram_Tow->GetXaxis();
   TAxis *y1 = histogram_Tow->GetYaxis();
   if(n==1){x1->SetTitle("track p_{T}"); x1->SetRangeUser(0,15);c1->SetLogy();}
   if(n==2){x1->SetTitle("track #eta");}
   if(n==3){x1->SetTitle("track #phi");}//y1->SetRangeUser(50E3,200E3); }//c1->SetLogy();}
   if(n==4){x1->SetTitle("tower E_{T}"); x1->SetRangeUser(0,15);c1->SetLogy();}
   if(n==5){x1->SetTitle("tower #eta");}
   if(n==6){x1->SetTitle("tower #phi");}//y1->SetRangeUser(60E3,530E3); }//c1->SetLogy();}
   comboEmbdHist_Tow->Draw("same");
   histogram_Awa->Draw("same");
   comboEmbdHist_Awa->Draw("same");
   histogram_Trans->Draw("same");
   comboEmbdHist_Trans->Draw("same");
   legend1->Draw();
   if(p==1){c1->Print(pname);}
   
}
void comboALL(TFile *t[12],char pta[100],TH1F *totH,double Norm[12]){
    
   
  Double_t XSEC=0.000000001447;//55
  const int lowP=1;
  TH1F *pt[13];
  for (int i=lowP;i<13;i++){
    pt[i]=(TH1F*) t[i]->Get(pta);
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
