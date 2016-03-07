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



void unfoldDetectorToParticleUnderlyingEvent_Bayesinclu()
{
#ifdef __CINT__
  gSystem->Load("libRooUnfold");
#endif
  
  gStyle->SetPalette(1);
  gStyle->SetOptDate(0);
  gStyle->SetOptStat(0);
  TFile *datafile;
  TFile *embdfile[14];
  

  datafile = new TFile("/star/u/gdwebb/UE_CVS_Check/radius06/st_physics_AllRuns.uehist.root");
  
  // These are the files for the detector level observables
  embdfile[1]=new TFile("/star/u/gdwebb/UE_CVS_Check/radius06/st_physics_detectorparticlelevel_4_5.uehists.root");
  embdfile[2]=new TFile("/star/u/gdwebb/UE_CVS_Check/radius06/st_physics_detectorparticlelevel_5_7.uehists.root");
  embdfile[3]=new TFile("/star/u/gdwebb/UE_CVS_Check/radius06/st_physics_detectorparticlelevel_7_9.uehists.root");
  embdfile[4]=new TFile("/star/u/gdwebb/UE_CVS_Check/radius06/st_physics_detectorparticlelevel_9_11.uehists.root");
  embdfile[5]=new TFile("/star/u/gdwebb/UE_CVS_Check/radius06/st_physics_detectorparticlelevel_11_15.uehists.root");
  embdfile[6]=new TFile("/star/u/gdwebb/UE_CVS_Check/radius06/st_physics_detectorparticlelevel_15_25.uehists.root"); 
  embdfile[7]=new TFile("/star/u/gdwebb/UE_CVS_Check/radius06/st_physics_detectorparticlelevel_25_35.uehists.root");
  embdfile[8]=new TFile("/star/u/gdwebb/UE_CVS_Check/radius06/st_physics_detectorparticlelevel_35_45.uehists.root");
  embdfile[9]=new TFile("/star/u/gdwebb/UE_CVS_Check/radius06/st_physics_detectorparticlelevel_45_55.uehists.root");
  embdfile[10]=new TFile("/star/u/gdwebb/UE_CVS_Check/radius06/st_physics_detectorparticlelevel_55_65.uehists.root");
  embdfile[11]=new TFile("/star/u/gdwebb/UE_CVS_Check/radius06/st_physics_detectorparticlelevel_65_75.uehists.root");
  embdfile[12]=new TFile("/star/u/gdwebb/UE_CVS_Check/radius06/st_physics_detectorparticlelevel_75_-1.uehists.root");

  TFile *p[14];
  // These are the files for the particle level observables 
  p[1]=new TFile("/star/u/gdwebb/UE_CVS_Check/radius06/st_physics_particlelevel_4_5.uehists.root");
  p[2]=new TFile("/star/u/gdwebb/UE_CVS_Check/radius06/st_physics_particlelevel_5_7.uehists.root");
  p[3]=new TFile("/star/u/gdwebb/UE_CVS_Check/radius06/st_physics_particlelevel_7_9.uehists.root");
  p[4]=new TFile("/star/u/gdwebb/UE_CVS_Check/radius06/st_physics_particlelevel_9_11.uehists.root");
  p[5]=new TFile("/star/u/gdwebb/UE_CVS_Check/radius06/st_physics_particlelevel_11_15.uehists.root");
  p[6]=new TFile("/star/u/gdwebb/UE_CVS_Check/radius06/st_physics_particlelevel_15_25.uehists.root"); 
  p[7]=new TFile("/star/u/gdwebb/UE_CVS_Check/radius06/st_physics_particlelevel_25_35.uehists.root");
  p[8]=new TFile("/star/u/gdwebb/UE_CVS_Check/radius06/st_physics_particlelevel_35_45.uehists.root");
  p[9]=new TFile("/star/u/gdwebb/UE_CVS_Check/radius06/st_physics_particlelevel_45_55.uehists.root");
  p[10]=new TFile("/star/u/gdwebb/UE_CVS_Check/radius06/st_physics_particlelevel_55_65.uehists.root");
  p[11]=new TFile("/star/u/gdwebb/UE_CVS_Check/radius06/st_physics_particlelevel_65_75.uehists.root");
  p[12]=new TFile("/star/u/gdwebb/UE_CVS_Check/radius06/st_physics_particlelevel_75_-1.uehists.root");

 
  double Lumi[13]; double Norm[13];
  normalize(Lumi,Norm); 


  Float_t small = 1e-5; 
  TVectorD tbinEx(14);
  //  Double_t tbinEx[14];

  char datahistname[100] = "htransverse_sumPtVsMaxJetpTJP2"; // Data Histogram Name
  char detectorname[100] = "htransverse_sumPtVsMaxJetpTJP2"; // Detector Level Histogram Name
  char particlename[100] = "htransverse_sumParticlepTVsMaxJetpTJP2"; // Pythia Particle Level Histogram Name
  //  char detpartname[100] = "hdpJetpTJP2"; // Detector vs Particle Level Histogram Name ("Response" Matrix)

 
  
  TH2F *detectorlevel  = new TH2F("transverse_sumPtVsMaxJetpTJP2","transverse_sumPtVsMaxJetpTJP2",40,0,80,20,0,20); 
  TH2F *particlelevel = new TH2F("transverse_sumParticlePtVsMaxJetpTJP2","transverse_sumParticlePtVsMaxJetpTJP2",40,0,80,20,0,20);
  // TH1F *combo_pythHisto = new TH1F("hpythiajetpT","hpythiajetpT",npTbins,npTbins0);

  comboALL2(embdfile,detectorname,detectorlevel,Norm);
  comboALL2(embdfile,particlename,particlelevel,Norm);
  //  comboALL2(f,detpartname,comboJetpT,Norm); 
  // comboALL(p,pythianame,combo_pythHisto,Norm); 
  
  cout << "==================================== TRAIN ====================================" << endl;
  //  RooUnfoldResponse response (detectorlevel,combo_pythHisto,comboJetpT);
  RooUnfoldResponse response(detectorlevel,particlelevel);
  // RooUnfoldResponse response (0,combo_pythHisto,comboJetpT);
  // RooUnfoldResponse response (0,0,comboJetpT);
  
  TH2F *hData = (TH2F*)datafile->Get(datahistname);
  TCanvas *canvas =  new TCanvas(); 
  canvas->Divide(1,3);
  canvas->cd(1);
  hData->Draw("colz");
  canvas->cd(2);
  detectorlevel->Draw("colz");
  canvas->cd(3);
  particlelevel->Draw("colz");

  cout << "==================================== UNFOLD ===================================" << endl;
  //  RooUnfoldBayes   unfold (&response, hData, 13);  
 
  RooUnfoldBayes unfoldBayes(&response,hData,1); 

  TH2F* hRecoBayes = (TH2F*) unfoldBayes.Hreco();
  //   unfold2.PrintTable(cout, particlelevel,1);
  cout << "CHECK" << endl;
  // hRecoBayes->Draw("colz");
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

void normalize(double Lumi[13], double Norm[13]){
  
  double NumEvts[13];
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

  //const used to multiply each distribution by
  double Norm[13];
  for (int i=1;i<=12;i++){
    if (Xsec[i]!=0) Norm[i]=(NumEvts[i]*Xsec[12])/(Xsec[i] *NumEvts[12]);
    cout << "Norm "  << Norm[i]<< endl;
  }  

}

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
