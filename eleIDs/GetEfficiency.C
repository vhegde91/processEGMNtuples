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
void decorate(TH1D*,int);
TList *FileList;
vector<TString> legName;
vector<TString> histName1,histName2;
TLatex textOnTop,intLumiE;

TLegend *legend1=new TLegend(0.25,0.4,0.45,0.6);
TString xAxisLabel;
char name[100];
int col[9]={kBlue,kRed,kOrange-3,kTeal+9,kMagenta,kOrange,kGray+2,kCyan,kBlack};

int rebin=1;

void GetEfficiency(){
  TH1::SetDefaultSumw2(1);

  FileList = new TList();
  int nfiles=1;
  TFile *f[nfiles];
  TString name="EGMid";
  xAxisLabel="pT(GeV)";

  f[0] = new TFile("eff.root");
  for(int i=0;i<nfiles;i++){
    histName1.push_back("prbPt_Loose80X");
    histName2.push_back("prbPt");
    histName1.push_back("prbPt_Loose94X");
    histName2.push_back("prbPt");
    // histName1.push_back("prbPt_Loose94X_vBin");
    // histName2.push_back("prbPtvBin");
  }

  rebin=1;
  legName.push_back("Loose80X");
  legName.push_back("Loose94X");
  //  legName.push_back("Loose94X");

  TCanvas *cA = new TCanvas("IDEff","ID efficiency",1500,850);
  TCanvas *cB = new TCanvas("his","hist",1500,850);
  cA->SetTickx();cA->SetTicky();
  TGraphAsymmErrors *h_grAE[nfiles];
  TH1D *h1,*h2,*h1r,*h2r;

  //  for(int i=0;i<nfiles;i++){
  for(int i=0;i<histName2.size();i++){
    h1 = (TH1D*)f[0]->FindObjectAny(histName1[i]);
    h2 = (TH1D*)f[0]->FindObjectAny(histName2[i]);
    setLastBinAsOverFlow(h1);
    setLastBinAsOverFlow(h2);
    h1->Rebin(rebin);
    h2->Rebin(rebin);
    h_grAE[i] = new TGraphAsymmErrors(h1,h2);
    
    //   h_grAE[i]->SetMarkerStyle(20+i);
    h_grAE[i]->SetMarkerColor(col[i]);
    h_grAE[i]->SetLineColor(col[i]);
    h_grAE[i]->SetLineWidth(2);
    h_grAE[i]->SetMinimum(0.);
    h_grAE[i]->SetMaximum(1.1);
    
    cA->cd();
    cA->SetGridx();
    cA->SetGridy();
    if(i==0) {
      h_grAE[i]->Draw("AP");
      h_grAE[i]->SetTitle(0);
      h_grAE[i]->GetXaxis()->SetTitle(xAxisLabel);
      h_grAE[i]->GetYaxis()->SetTitle("#varepsilon");
      h_grAE[i]->GetYaxis()->SetTitleOffset(0.5);
      h_grAE[i]->GetYaxis()->SetTitleSize(0.06);
    }
    else h_grAE[i]->Draw("sames");
    legend1->AddEntry(h_grAE[i],legName[i],"lpe");
    gPad->Update();
  }

  legend1->Draw();
  cB->cd();
  h1->Draw();
  h2->Draw("sames");

  cA->cd();

  char name2[100];  
  textOnTop.SetTextSize(0.04);
  intLumiE.SetTextSize(0.04);
  textOnTop.DrawLatexNDC(0.12,0.91,"CMS #it{#bf{Simulation}}");
  sprintf(name2,"#bf{(13TeV)}");
  intLumiE.DrawLatexNDC(0.75,0.91,name2);

  TFile *fout=new TFile("Eff_"+histName2[0]+f[0]->GetName(),"RECREATE");
  fout->cd();
  for(int i=0;i<nfiles;i++){
     h_grAE[i]->Write();
  }
}
   
void decorate(TH1D* h,int i){
  h->SetLineColor(col[i]);
  h->SetLineWidth(2);
  //  h->SetFillColor(h->GetLineColor());
  h->SetMarkerStyle(20+i);
  h->SetMarkerColor(col[i]);
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
