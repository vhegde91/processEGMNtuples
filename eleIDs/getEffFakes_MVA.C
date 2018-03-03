#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include"TH1.h"
#include"TROOT.h"
#include"TH2.h"
#include"TFile.h"
#include"TDirectory.h"
#include"TTree.h"
#include"TBrowser.h"
#include"TF1.h"
#include<iomanip>
#include"TGraphErrors.h"
#include"TGraphAsymmErrors.h"
#include"TGraph.h"
#include"TCanvas.h"
#include"TPaveStats.h"
#include"TStyle.h"
#include"TLegend.h"

//#include"Variables.h"

using namespace std;
void setLastBinAsOverFlow(TH1D*);
void nameLegend2(const char*);
void setGraphProp(TGraphAsymmErrors*, int);
bool savePlots=1;
vector<TString> legName;
vector<TString> histNameNum,histName2;
TLatex textOnTop,intLumiE;

TString xAxisLabel;
TString name;
int col[9]={kBlue,kRed,kOrange-3,kTeal+9,kMagenta,kOrange,kGray+2,kCyan,kBlack};

int rebin=1;

void getEffFakes_MVA(){
  TH1::SetDefaultSumw2(1);

  int nfiles=2;
  TFile *f[nfiles];
  TString name="EGMid";
  xAxisLabel="pT(GeV)";
  char name2[100];
  TString cmsName = "CMS #it{#bf{Simulation}}";
  textOnTop.SetTextSize(0.04);
  intLumiE.SetTextSize(0.04);
  sprintf(name2,"#bf{(13TeV)}");

  vector<TString> idNames    = {"MVAWP80",   "MVAWP90",   "LeptonMvaM","LeptonMvaVT",
				"MVA94Xwp80iso","MVA94Xwp80noiso","MVA94Xwp90iso","MVA94Xwp90noiso",
				"LeptonMvaMIDEmuTightIP2DSIP3D8miniIso04","LeptonMvaVTIDEmuTightIP2DSIP3D8miniIso04"};

  vector<TString> refIdNames = {"MVA80Xwp80","MVA80Xwp90","LeptonMvaM","LeptonMvaVT",
				"MVA94Xwp80iso","MVA94Xwp80noiso","MVA94Xwp90iso","MVA94Xwp90noiso",
				"LeptonMvaMIDEmuTightIP2DSIP3D8miniIso04","LeptonMvaVTIDEmuTightIP2DSIP3D8miniIso04"};

  // vector<TString> idNames    = {"MVAWP80"};
  // vector<TString> refIdNames = {"MVA80Xwp80"};

  TH1D *h_num[2*3*idNames.size()], *h_den[2*3*idNames.size()];
  TGraphAsymmErrors *h_grRef[3*idNames.size()], *h_gr[3*idNames.size()];
  TLegend *legend[2*idNames.size()];

  TCanvas *cA[idNames.size()];
  TH1D *h_Num, *h_Den;  

  f[0] = new TFile("mc_eff_all.root");
  f[1] = new TFile("mc_fake_all.root");
  
  bool hasOldID = true;

  for(int i=0;i<idNames.size();i++){
    if(idNames[i]==refIdNames[i]){
      name = idNames[i];
      hasOldID = false;
    }
    else{
      name = idNames[i]+"_"+refIdNames[i];
      hasOldID = true;
    }
    cA[i] = new TCanvas(name,name,1400,450);
    cA[i]->Divide(3,1);

    for(int p=0;p<nfiles;p++){
      //----------------for eta1------------------
      h_Num = (TH1D*)f[p]->Get("prbPt_Eta1_"+idNames[i]); setLastBinAsOverFlow(h_Num);
      h_Den = (TH1D*)f[p]->Get("prbPt_Eta1");             setLastBinAsOverFlow(h_Den);
      h_gr[i]    = new TGraphAsymmErrors(h_Num,h_Den);
      
      if(hasOldID){
	h_Num = (TH1D*)f[p]->Get("prbPt_Eta1_"+refIdNames[i]); setLastBinAsOverFlow(h_Num);
	h_grRef[i] = new TGraphAsymmErrors(h_Num,h_Den);
      }

      cA[i]->cd(1);
      if(hasOldID) setGraphProp(h_grRef[i],kBlue);
      setGraphProp(h_gr[i],kRed);

      if(!hasOldID && p==0) h_gr[i]->SetLineColor(kTeal+9);

      if(hasOldID){
	if(p==0) h_grRef[i]->Draw("AP");
	else h_grRef[i]->Draw("sames");
      }
      else{
	if(p==0) h_gr[i]->Draw("AP");
      }
      h_gr[i]->Draw("sames");
      //----------------for eta2------------------
      h_Num = (TH1D*)f[p]->Get("prbPt_Eta2_"+idNames[i]); setLastBinAsOverFlow(h_Num);
      h_Den = (TH1D*)f[p]->Get("prbPt_Eta2");             setLastBinAsOverFlow(h_Den);
      h_gr[i]    = new TGraphAsymmErrors(h_Num,h_Den);
      
      if(hasOldID){
	h_Num = (TH1D*)f[p]->Get("prbPt_Eta2_"+refIdNames[i]); setLastBinAsOverFlow(h_Num);
	h_grRef[i] = new TGraphAsymmErrors(h_Num,h_Den);
      }

      cA[i]->cd(2);
      if(hasOldID) setGraphProp(h_grRef[i],kBlue);
      setGraphProp(h_gr[i],kRed);

      if(!hasOldID && p==0) h_gr[i]->SetLineColor(kTeal+9);

      if(hasOldID){
	if(p==0) h_grRef[i]->Draw("AP");
	else h_grRef[i]->Draw("sames");
      }
      else{
	if(p==0) h_gr[i]->Draw("AP");
      }
      h_gr[i]->Draw("sames");
      //----------------for eta3------------------
      h_Num = (TH1D*)f[p]->Get("prbPt_Eta3_"+idNames[i]); setLastBinAsOverFlow(h_Num);
      h_Den = (TH1D*)f[p]->Get("prbPt_Eta3");             setLastBinAsOverFlow(h_Den);
      h_gr[i]    = new TGraphAsymmErrors(h_Num,h_Den);
      
      if(hasOldID){
	h_Num = (TH1D*)f[p]->Get("prbPt_Eta3_"+refIdNames[i]); setLastBinAsOverFlow(h_Num);
	h_grRef[i] = new TGraphAsymmErrors(h_Num,h_Den);
      }

      cA[i]->cd(3);
      if(hasOldID) setGraphProp(h_grRef[i],kBlue);
      setGraphProp(h_gr[i],kRed);
      
      if(!hasOldID && p==0) h_gr[i]->SetLineColor(kTeal+9);

      if(hasOldID){
	if(p==0) h_grRef[i]->Draw("AP");
	else h_grRef[i]->Draw("sames");
      }
      else{
	if(p==0) h_gr[i]->Draw("AP");
      }
      h_gr[i]->Draw("sames");
     
      //----------------------------------------
      if(p==0){
	//legend[i] = new TLegend(0.25,0.35,0.55,0.5);
	legend[i] = new TLegend(0.15,0.78,0.55,0.88);      
	//    legend[i] = new TLegend(0.15,0.9,0.85,0.8)    legend[i]->SetNColumns(2);
	legend[i]->SetTextSize(0.05);
	legend[i]->SetBorderSize(0);

	if(hasOldID) legend[i]->AddEntry(h_grRef[i],refIdNames[i],"lpe");
	legend[i]->AddEntry(h_gr[i],idNames[i],"lpe");
	// if(hasOldID) legend[i]->AddEntry(h_grRef[i],refIdNames[i],"lpe");
	// else legend[i]->AddEntry(h_gr[i],"Eff","lpe");
	// legend[i]->AddEntry(h_gr[i],idNames[i],"lpe");

	cA[i]->cd(1);
	legend[i]->Draw();
	textOnTop.DrawLatexNDC(0.12,0.91,cmsName); 	intLumiE.DrawLatexNDC(0.75,0.91,name2);
	cA[i]->cd(2);
	legend[i]->Draw();
	textOnTop.DrawLatexNDC(0.12,0.91,cmsName);	intLumiE.DrawLatexNDC(0.75,0.91,name2);
	cA[i]->cd(3);
	legend[i]->Draw();
	textOnTop.DrawLatexNDC(0.12,0.91,cmsName);	intLumiE.DrawLatexNDC(0.75,0.91,name2);
      }//p==0
    }//loop over files
    if(savePlots){name = name+".png"; cA[i]->SaveAs(name);}
  }//ids
  
}
   
void setGraphProp(TGraphAsymmErrors* h_gr, int col1){
  h_gr->SetMarkerColor(col1);
  h_gr->SetLineColor(col1);
  h_gr->SetLineWidth(2);
  h_gr->SetMinimum(0.);
  h_gr->SetMaximum(1.29);
  h_gr->SetTitle(0);
  h_gr->GetYaxis()->SetTitle("#varepsilon");
  h_gr->GetYaxis()->SetTitleOffset(1.08);
  h_gr->GetYaxis()->SetTitleSize(0.06);

  h_gr->GetXaxis()->SetNdivisions(5);
  h_gr->GetXaxis()->SetTitle("e pT(GeV)");
  //  if(col1==kBlue) h_gr->SetLineWidth(3);
}

void setLastBinAsOverFlow(TH1D* h_hist){
  double lastBinCt =h_hist->GetBinContent(h_hist->GetNbinsX()),overflCt =h_hist->GetBinContent(h_hist->GetNbinsX()+1);
  double lastBinErr=h_hist->GetBinError(h_hist->GetNbinsX()),  overflErr=h_hist->GetBinError(h_hist->GetNbinsX()+1);

  if(lastBinCt!=0 && overflCt!=0)
    lastBinErr = (lastBinCt+overflCt)* (sqrt( ((lastBinErr/lastBinCt)*(lastBinErr/lastBinCt)) + ((overflErr/overflCt)*(overflErr/overflCt)) ) );

  else if(lastBinCt==0 && overflCt!=0)
    lastBinErr = overflErr;
  else if(lastBinCt!=0 && overflCt==0)
    lastBinErr = lastBinErr;
  else lastBinErr=0;

  lastBinCt = lastBinCt+overflCt;
  h_hist->SetBinContent(h_hist->GetNbinsX(),lastBinCt);
  h_hist->SetBinError(h_hist->GetNbinsX(),lastBinErr);
  
  h_hist->SetBinContent(h_hist->GetNbinsX()+1,0);
  h_hist->SetBinError(h_hist->GetNbinsX()+1,0);
}
