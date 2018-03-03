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

TLatex textOnTop,intLumiE;
bool savePlots=1;
TString xAxisLabel;
TString name;
int col[9]={kBlue,kRed,kOrange-3,kTeal+9,kMagenta,kOrange,kGray+2,kCyan,kBlack};

int rebin=1;

void getEffFakes(){
  TH1::SetDefaultSumw2(1);

  int nfiles=2;
  TFile *f[nfiles];
  TString name="EGMid";
  char name2[100];
  TString cmsName = "CMS #it{#bf{Simulation}}";
  textOnTop.SetTextSize(0.04);
  intLumiE.SetTextSize(0.04);
  sprintf(name2,"#bf{(13TeV)}");
  vector<TString> idNames    = {"Loose94X","Medium94X","Tight94X","CutBasedVetoNoIso94X","CutBasedLooseNoIso94X","CutBasedMediumNoIso94X","CutBasedTightNoIso94X"};
  vector<TString> refIdNames = {"Loose80X","Medium80X","Tight80X","CutBasedVetoNoIso",   "CutBasedLooseNoIso",   "CutBasedMediumNoIso",   "CutBasedTightNoIso"   };

  // vector<TString> idNames    = {"Loose94X"};
  // vector<TString> refIdNames = {"Loose80X"};

  TH1D *h_num[2*3*idNames.size()], *h_den[2*3*idNames.size()];
  TGraphAsymmErrors *h_grRef[3*idNames.size()], *h_gr[3*idNames.size()];
  TLegend *legend[2*idNames.size()];

  TCanvas *cA[idNames.size()];
  TH1D *h_Num, *h_Den;  

  f[0] = new TFile("mc_eff_all.root");
  f[1] = new TFile("mc_fake_all.root");
  int p=0;

  for(int i=0;i<idNames.size();i++){
    name = idNames[i]+"_"+refIdNames[i];
    cA[i] = new TCanvas(name,name,1500,500);
    cA[i]->Divide(3,1);

    for(int p=0;p<nfiles;p++){
      //----------------for EB------------------
      h_Num = (TH1D*)f[p]->Get("prbPt_EB_"+idNames[i]); setLastBinAsOverFlow(h_Num);
      h_Den = (TH1D*)f[p]->Get("prbPt_EB");             setLastBinAsOverFlow(h_Den);
      h_gr[i]    = new TGraphAsymmErrors(h_Num,h_Den);
      h_Num = (TH1D*)f[p]->Get("prbPt_EB_"+refIdNames[i]); setLastBinAsOverFlow(h_Num);
      h_grRef[i] = new TGraphAsymmErrors(h_Num,h_Den);

      cA[i]->cd(1);
      setGraphProp(h_grRef[i],kBlue);
      setGraphProp(h_gr[i],kRed);
      h_grRef[i]->GetXaxis()->SetTitle("Barrel e pT(GeV)");
      h_grRef[i]->GetXaxis()->SetNdivisions(5);
      if(p==0) h_grRef[i]->Draw("AP");
      else h_grRef[i]->Draw("sames");
      h_gr[i]->Draw("sames");   
      //----------------for EE------------------
      h_Num = (TH1D*)f[p]->Get("prbPt_EE_"+idNames[i]); setLastBinAsOverFlow(h_Num);
      h_Den = (TH1D*)f[p]->Get("prbPt_EE");             setLastBinAsOverFlow(h_Den);
      h_gr[i]    = new TGraphAsymmErrors(h_Num,h_Den);
      h_Num = (TH1D*)f[p]->Get("prbPt_EE_"+refIdNames[i]); setLastBinAsOverFlow(h_Num);
      h_grRef[i] = new TGraphAsymmErrors(h_Num,h_Den);

      cA[i]->cd(2);
      setGraphProp(h_grRef[i],kBlue);
      setGraphProp(h_gr[i],kRed);
      h_grRef[i]->GetXaxis()->SetTitle("Endcap e pT(GeV)");
      h_grRef[i]->GetXaxis()->SetNdivisions(5);
      if(p==0) h_grRef[i]->Draw("AP");
      else h_grRef[i]->Draw("sames");
      h_gr[i]->Draw("sames");
      //----------------for eta------------------
      h_Num = (TH1D*)f[p]->Get("prbEta_Pt25_"+idNames[i]);
      h_Den = (TH1D*)f[p]->Get("prbEta_Pt25");
      h_gr[i]    = new TGraphAsymmErrors(h_Num,h_Den);
      h_Num = (TH1D*)f[p]->Get("prbEta_Pt25_"+refIdNames[i]);
      h_grRef[i] = new TGraphAsymmErrors(h_Num,h_Den);

      cA[i]->cd(3);
      setGraphProp(h_grRef[i],kBlue);
      setGraphProp(h_gr[i],kRed);
      h_grRef[i]->GetXaxis()->SetTitle("e |#eta|, for e pT #geq 25 GeV");
      if(p==0) h_grRef[i]->Draw("AP");
      else h_grRef[i]->Draw("sames");
      h_gr[i]->Draw("sames");
      //----------------------------------------
      if(p==0){
	//legend[i] = new TLegend(0.25,0.35,0.55,0.5);
	legend[i] = new TLegend(0.15,0.78,0.55,0.88);      
	//    legend[i] = new TLegend(0.15,0.9,0.85,0.8)    legend[i]->SetNColumns(2);
	legend[i]->SetTextSize(0.05);
	legend[i]->SetBorderSize(0);
	legend[i]->AddEntry(h_grRef[i],refIdNames[i],"lpe");
	legend[i]->AddEntry(h_gr[i],idNames[i],"lpe");
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
