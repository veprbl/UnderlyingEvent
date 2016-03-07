#ifndef __CINT__
#include "TCanvas.h"
#include "TChain.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TProfile.h"
#include "TArrayD.h"
#include "TCut.h"
#include "TPolyMarker.h"
#include "TVirtualFitter.h"
#include "TMath.h"
#include <Stiostream.h>
using std::cout;
using std::endl;

#include "TRandom.h"
#include "TH1D.h"

#include "RooUnfoldResponse.h"
#include "RooUnfoldBayes.h"
#endif

// Main Routine:
//void CompareDetectorParticleLevel(Int_t n, Int_t p);


//==============================================================================
// Global definitions
//==============================================================================

static const Int_t npTbins = 13; // jet pT 18% resolutions
const Double_t npTbins0[npTbins+1] = {10.0,11.8,13.9,16.4,19.4,22.9,27.0,31.9,37.6,44.4,52.3,61.8,72.9,86.0};

static const Int_t numbins = 83;

//==============================================================================
// Combining partonic pT bins
//==============================================================================

void comboALL(TFile *t[13],char pta[100],TH1F *totH,double Norm[13]){

  float MinbXsec=28.12;
  const int lowP=1;
  TH1F *pt[13];
  for (int i=lowP; i<13; i++){
    pt[i]=(TH1F*) t[i]->Get(pta);

    // pt[i]->Scale(1);
    pt[i]->Sumw2();
    pt[i]->Scale(1/Norm[i]);
    totH->Add(pt[i]);
  }
}

void comboALL2(TFile *t[12],char pta[100],TH2F *totH,double Norm[12]){
    
   
  Double_t XSEC=0.000000001447;//55
  const int lowP=1;
  TH2F *pt[13];
  for (int i=lowP; i < 13; i++){
    pt[i]=(TH2F*) t[i]->Get(pta);
    //    cout <<  "Error bin1: "  <<   pt[i]->GetBinContent(i,i) << endl;
    pt[i]->Scale(1.0/ Norm[i]);
    // pt[i]->Scale(Norm[i]);
    totH->Add(pt[i]);
  }
}


void unfoldDetectorToParticleSVD_inclu()
{
#ifdef __CINT__
  gSystem->Load("libRooUnfold");
#endif
  
  gStyle->SetPalette(1);
  gStyle->SetOptDate(0);
  gStyle->SetOptStat(0);
  TFile *g;
  TFile *f[14];
  

  g = new TFile("/star/u/gdwebb/InclusiveJet/radius06/dataInclujetsR060_noJetpTCut.root");
  
  f[1]=new TFile("/star/u/gdwebb/InclusiveJet/radius06/embedInclujet500GeVpTBin4_5.root");
  f[2]=new TFile("/star/u/gdwebb/InclusiveJet/radius06/embedInclujet500GeVpTBin5_7.root");
  f[3]=new TFile("/star/u/gdwebb/InclusiveJet/radius06/embedInclujet500GeVpTBin7_9.root");
  f[4]=new TFile("/star/u/gdwebb/InclusiveJet/radius06/embedInclujet500GeVpTBin9_11.root");
  f[5]=new TFile("/star/u/gdwebb/InclusiveJet/radius06/embedInclujet500GeVpTBin11_15.root");
  f[6]=new TFile("/star/u/gdwebb/InclusiveJet/radius06/embedInclujet500GeVpTBin15_25.root"); 
  f[7]=new TFile("/star/u/gdwebb/InclusiveJet/radius06/embedInclujet500GeVpTBin25_35.root");
  f[8]=new TFile("/star/u/gdwebb/InclusiveJet/radius06/embedInclujet500GeVpTBin35_45.root");
  f[9]=new TFile("/star/u/gdwebb/InclusiveJet/radius06/embedInclujet500GeVpTBin45_55.root");
  f[10]=new TFile("/star/u/gdwebb/InclusiveJet/radius06/embedInclujet500GeVpTBin55_65.root");
  f[11]=new TFile("/star/u/gdwebb/InclusiveJet/radius06/embedInclujet500GeVpTBin65_75.root");
  f[12]=new TFile("/star/u/gdwebb/InclusiveJet/radius06/embedInclujet500GeVpTBin75_-1.root");

  TFile *p[14];

  p[1]=new TFile("/star/u/gdwebb/InclusiveJet/radius06/pythiaInclujet500GeVpTBin4_5.root");
  p[2]=new TFile("/star/u/gdwebb/InclusiveJet/radius06/pythiaInclujet500GeVpTBin5_7.root");
  p[3]=new TFile("/star/u/gdwebb/InclusiveJet/radius06/pythiaInclujet500GeVpTBin7_9.root");
  p[4]=new TFile("/star/u/gdwebb/InclusiveJet/radius06/pythiaInclujet500GeVpTBin9_11.root");
  p[5]=new TFile("/star/u/gdwebb/InclusiveJet/radius06/pythiaInclujet500GeVpTBin11_15.root");
  p[6]=new TFile("/star/u/gdwebb/InclusiveJet/radius06/pythiaInclujet500GeVpTBin15_25.root"); 
  //  p[7]=new TFile("/star/u/gdwebb/InclusiveJet/radius06/temp_pythiaInclujet500GeVpTBin25_35_MissingRuns.root");
  p[7]=new TFile("/star/u/gdwebb/InclusiveJet/radius06/pythiaInclujet500GeVpTBin25_35.root");
  p[8]=new TFile("/star/u/gdwebb/InclusiveJet/radius06/pythiaInclujet500GeVpTBin35_45.root");
  p[9]=new TFile("/star/u/gdwebb/InclusiveJet/radius06/pythiaInclujet500GeVpTBin45_55.root");
  p[10]=new TFile("/star/u/gdwebb/InclusiveJet/radius06/pythiaInclujet500GeVpTBin55_65.root");
  p[11]=new TFile("/star/u/gdwebb/InclusiveJet/radius06/pythiaInclujet500GeVpTBin65_75.root");
  p[12]=new TFile("/star/u/gdwebb/InclusiveJet/radius06/pythiaInclujet500GeVpTBin75_-1.root");

  double NumEvts[13];
  double Lumi[13];
  
  NumEvts[1] =981735; //4-5
  NumEvts[2] =492293; // 5-7
  NumEvts[3] =492293; // 7-9
  NumEvts[4] =492293; // 9-11
  NumEvts[5] = 443057;  // 11-15
  NumEvts[6] = 393837;  // 15-25
  //  NumEvts[7] = 245374;  // 25-35 
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

  //const used to multiply each distribution by
  double Norm[13];
  for (int i=1;i<=12;i++){
    if (Xsec[i]!=0) Norm[i]=(NumEvts[i]*Xsec[12])/(Xsec[i] *NumEvts[12]);
    cout << "Norm "  << Norm[i]<< endl;
  }  

  Float_t small = 1e-5; 

  //Particle - Parton (UE and Had Correction)
  // Double_t ue_had[11] = {-0.0565357, 0.0376609, 0.0176575,0.00564398, 0.00158016, 0.000472275, 0.000133434, 3.65685e-05, 1.69252e-05, 5.58701e-06, 0.0};

  Double_t ue_had[11] = {-0.0479559, 0.0320943, 0.014994, 0.00485374, 0.00147753, 0.000455902, 0.000118317, 3.05778e-05, 1.40753e-05,4.765e-06
};

  cout << "AKKKK!!" << endl;
  TVectorD tbinEx(14);
  //  Double_t tbinEx[14];
  cout << "BLEK!!" << endl;
  for( int iter =0; iter < 14; iter++)
    {
      cout << "iter: " << iter << "npTbins0: " << npTbins0[iter]  <<  endl;
      tbinEx[iter]=(npTbins0[iter+1]-npTbins0[iter])/2.0;
      cout << "iter: " << iter << "tbinEx: " << tbinEx[iter]  <<  endl;
    }
  char datahistname[100] = "hjetptJP2"; // Data Histogram Name
  char detectorname[100] = "hmatchedjetptJP2"; // Detector Level Histogram Name
  char pythianame[100] = "hjetpt_afCut"; // Pythia Particle Level Histogram Name
  char detpartname[100] = "hdpJetpTJP2"; // Detector vs Particle Level Histogram Name ("Response" Matrix)

  cout << "CHECK!!!" << endl;
  
  TH1F *detectorlevel  = new TH1F("hmatchedjetpT","hmatchedjetpT",npTbins,npTbins0); 
  TH2F *comboJetpT = new TH2F("hdpJetpTJP2","hdpJetpTJP2",npTbins,npTbins0,npTbins,npTbins0);
  TH1F *combo_pythHisto = new TH1F("hpythiajetpT","hpythiajetpT",npTbins,npTbins0);

  comboALL(f,detectorname,detectorlevel,Norm);
  //comboALL(f,particlename,particlelevel,Norm);
  comboALL2(f,detpartname,comboJetpT,Norm); 
  comboALL(p,pythianame,combo_pythHisto,Norm); 
  
  cout << "==================================== TRAIN ====================================" << endl;
  RooUnfoldResponse response (detectorlevel,combo_pythHisto,comboJetpT);
  // RooUnfoldResponse response (0,combo_pythHisto,comboJetpT);
  // RooUnfoldResponse response (0,0,comboJetpT);
  
  TH1F *hData = (TH1F*)g->Get(datahistname);
  
  cout << "==================================== UNFOLD ===================================" << endl;
  //  RooUnfoldBayes   unfold (&response, hData, 13);  
 
  RooUnfoldSvd unfoldSVD(&response,hData); 

  TH1F* hRecoSVD= (TH1F*) unfoldSVD.Hreco();
  //   unfold2.PrintTable(cout, particlelevel,1);
  
  //  TH2F* plothisto = new TH2F("ph","ph",1,30.0,127,1,1E-5,0.8);
  // TH2F* plothisto = new TH2F("ph","ph",1,30.0,152,1,1E-5,0.3);
  TH2F* plothisto = new TH2F("ph","ph",1,8.0,90,1,1E-6,5); 
  TGraphErrors *grSvd = new TGraphErrors();
  TVectorD part(14);


  TVectorD dM(14), phase_space(14), xSecSVD(14), xSecSVDError(14), sysErrorDataThe(14); 
  Double_t xSecBHT3 = 434E-09; // barns 434  +13% = 490.42   -13% = 377.58
  
  //  Double_t numEventsBHT3 = 3681813; 
  Double_t numEventsBHT3 = 3787534; 
  Double_t numEventsBBCMB_Cat2 = 854931;
  Double_t numEventsBBCMB_Cat3 = 827881;
  Double_t ratioBBC= 0;
  ratioBBC = numEventsBBCMB_Cat2/numEventsBBCMB_Cat3;
  //  Double_t lumi = (numEventsBHT3 / xSecBHT3) *1E-12 ; // 1 / barn  * 10^-12 barn / 1 pb 
  Double_t lumi_Wana = 8.0948; // pb^-1
  Double_t lumi_BHT3_Wruns = 3739733/ xSecBHT3 *1E-12; // pb^-1
  Double_t frac_W = lumi_Wana/lumi_BHT3_Wruns;

  cout << "lumi BHT3 W runs: " << lumi_BHT3_Wruns <<  " frac: " << frac_W << endl;
  Double_t lumi = (numEventsBHT3 / xSecBHT3)* ratioBBC *1E-6 *frac_W; // 1 / barn  * 10^-6 barn / 1 micro barns 
  //lumi = lumi + lumi*0.13; 
  cout << "Luminosity: " << lumi << endl;   
  cout << "Cross-Section Values:" << endl;
  for(int ib =0; ib < hRecoSVD->GetNbinsX()+1; ib++){
    dM[ib] =  npTbins0[ib+1] - npTbins0[ib];
    //    dM[ib] = 10.0; 
    phase_space[ib] = 0.8 * dM[ib] * lumi;
    part[ib] = comboJetpT->GetYaxis()->GetBinCenter(ib+1);
    cout << "binCenter" << i << " " << part[ib] <<  endl;    
    xSecSVD[ib] = hRecoSVD->GetBinContent(ib+1)* 1.0/phase_space[ib];
    xSecSVDError[ib] = hRecoSVD->GetBinError(ib+1) * 1.0/phase_space[ib]; 
    grSvd->SetPoint(ib, part[ib],xSecSVD[ib]);
    //     grSvd->SetPointError (ib,tbinEx[ib], xSecSVDError[ib]);
    grSvd->SetPointError (ib,tbinEx[ib], 0.0);
    cout << xSecSVD[ib] << endl;
   
  }

  //  Double_t sys_ErrorPlus[11] = {0.015824684, 0.020507009, 0.011152291, 0.005922431, 0.002598831, 0.000936492, 0.000296086, 9.44368E-05, 3.15618E-05, 9.40743E-06,0.0};
  Double_t sys_ErrorPlus[11] = {0.035806479, 0.028813195, 0.007498814, 0.003539183, 0.001427696, 0.000536058, 0.000192324, 7.17959E-05, 2.65246E-05, 8.36405E-06,0.0};
  //  Double_t sys_ErrorMinus[11] = {0.014856491, 0.021077871, 0.012176705, 0.006075181, 0.002709548, 0.000963537, 0.000300584, 9.7385E-05, 3.36057E-05, 1.0259E-05,0.0};
  Double_t sys_ErrorMinus[11] = {0.048244351, 0.031049151, 0.008509211, 0.003523281, 0.001388714, 0.000541343, 0.000201471, 7.64976E-05, 2.86248E-05, 9.1016E-06,0.0};
  TVectorD sysHigh(11), sysLow(11), xsecSysHigh(11),xsecSysLow(11);
  // for(int j =0; j < hRecoSVD->GetNbinsX()+1; j++){
  //   sysHigh[j] =  sys_ErrorPlus[j];
  //   sysLow[j] = sys_ErrorMinus[j];
  //   xsecSysHigh[j] = xSecSVD[j] + sysHigh[j];
  //   xsecSysLow[j] = xSecSVD[j] - sysLow[j];
  //   //    cout << "Xesc :" << j << " " << xsecSysLow[j] << endl;
  // }
  // TGraphAsymmErrors *grSysBand = new TGraphAsymmErrors(tbinX, xSecSVD, tErrorxL, tErrorxH, sysLow,sysHigh); 
  TCanvas *c1 = new TCanvas("canvas","canvas",800,900);
  //  TCanvas *c1 = new TCanvas("c1","Example 2 pads (20,80)",200,10,300,500);
  TPad *pad1 = new TPad("pad1", "The pad 80% of the height",0.0,0.0,1.0,1.0,21);
  TPad *pad2 = new TPad("pad2", "The pad 20% of the height",0.0,0.0,1.0,0.345,22);
  pad1->SetFillColor(0);
  pad1->SetLogy();
  pad1->SetGrid(0,0);
  pad2->SetFillColor(0);
  pad2->SetGrid(0,0);
  pad1->Draw();
  // pad2->Draw();

  //  grSvd->SetMarkerColor(kBlack);
  // grSvd->SetMarkerStyle(20);

  plothisto->SetTitle("");
  plothisto->GetXaxis()->SetTitle("p_{T} [GeV]");
  plothisto->GetYaxis()->SetTitle("d^{2}#sigma/dp_{T}d|y|_{max} [#mub]");
  plothisto->GetXaxis()->SetTitleSize(0.04); plothisto->GetXaxis()->SetTitleOffset(0.92);
  plothisto->GetYaxis()->SetTitleSize(0.05); plothisto->GetYaxis()->SetTitleOffset(0.92);
  plothisto->GetXaxis()->CenterTitle(true);  plothisto->GetYaxis()->CenterTitle(true);
  
  plothisto->GetXaxis()->SetLabelSize(0.035); plothisto->GetYaxis()->SetLabelOffset(0.001);
  plothisto->GetYaxis()->SetLabelSize(0.04); plothisto->GetYaxis()->SetLabelOffset(0.001);

  //  grByB->GetYaxis()->SetRangeUser(2e-5,0.7);  

  //  c1->Divide(1,2);
  // c1->cd(1);
  pad1->cd();
  // pad1->SetBottomMargin(small);
  pad1->SetTopMargin(1e-2);
  //gPad->SetLogy();
  // gPad->SetGrid(0,0);
  plothisto->Draw();
  // grTheory_sys->SetFillColor(kOrange+7);
  // grTheory_sys->SetFillStyle(1001);
  // grTheory_sys_corr->SetFillColor(kAzure-3);
  // grTheory_sys_corr->SetFillStyle(3001);
  // //  grSysBand->SetFillColor(kGray);
  // grSysBand->SetFillStyle(3444);

  // grTheory_sys->Draw("2");
  // grTheory_sys_corr->Draw("2");
  // grSysBand->Draw("2");
  grSvd->Draw("][");  
  //  grTheory->Draw("2");
  
  TLegend *leg = new TLegend(0.45,0.95,0.85,0.6); // upper right
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->AddEntry("","STAR Inclusive Jet Cross Section  ","");
  leg->AddEntry(""," pp @  #sqrt{s} = 500GeV","");
  leg->AddEntry("","Anti-k_{T}, R = 0.6,  |y|_{max} < 0.8","");
  //  leg->AddEntry(grBay,"Bayesian","p");
  // leg->AddEntry(grSvd,"SVD","p");
  //leg->AddEntry(grTheory_sys,"pQCD MRST 2004 (de Florian)","f");
  // leg->AddEntry(grTheory_sys_corr,"pQCD MRST 2004 + HAD + UE","f");
  //  leg->AddEntry("","by DeFlorian","");
  leg->Draw();
  TLegend *leg1 = new TLegend(0.55,0.55,0.85,0.4); // upper right
  leg1->SetFillColor(0);
  leg1->SetBorderSize(0);
  leg1->AddEntry("","#int L dt  = 8.7 pb^{-1} #pm 13%","");
  leg1->AddEntry("","","");
  // leg1->AddEntry("","#pm 13%","");
  //   TCanvas *c2 = new TCanvas("c2","c2");
  leg1->Draw();

  TLegend *leg2 = new TLegend(0.13,0.15,0.43,0.35); // lower left
  leg2->SetFillColor(0);
  leg2->SetBorderSize(0);
  leg2->AddEntry("","STAR Preliminary","");
  leg2->AddEntry("","","");
  // leg2->AddEntry("","#int L dt  = 8.7 pb^{-1}","");
  leg2->AddEntry("","","");
 
  c1->Update();
  
   
  c1->Print("inclusivexSectionResultSVD_JP2.png");
}

Double_t errorCalc(Double_t A, Double_t C){
  //C is the numberator and A is the denominator
  // R = C / A =  (A + B) / A
  // cout << "A " << A << " C "  << C << endl;
  Double_t R, B, err;
  R = B = err =0;
  B =  C - A; 
  R = C / A; 
  
  // cout << " R " << R << " B " << B << endl; 
  
  
  err =  TMath::Sqrt((B*(A+B))/(A*A*A));
  // cout << "errTest " <<  err <<   endl;
  return err ;
}
