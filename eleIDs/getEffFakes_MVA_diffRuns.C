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
bool savePlots=0;
vector<TString> legName;
vector<TString> histNameNum,histName2;
TLatex textOnTop,intLumiE;

TString xAxisLabel;
TString name;
int col[9]={kBlue,kRed,kOrange-3,kTeal+9,kMagenta,kOrange,kGray+2,kCyan,kBlack};

int rebin=1;

void getEffFakes_MVA_diffRuns(){
  TH1::SetDefaultSumw2(1);

  int nfiles=6;
  TFile *f[nfiles];
  bool logY = 0, diffHistsToCom=0;
  TString name="EGMid";
  xAxisLabel="pT (GeV)";
  char name2[100];
  TString cmsName = "CMS #it{#bf{Simulation}}";
  textOnTop.SetTextSize(0.04);
  intLumiE.SetTextSize(0.04);
  sprintf(name2,"#bf{(13 TeV)}");
  
  vector<TString> idNames    = {"MVATightNew2","MVAVLooseFONew","MVAVLooseNew"};// names for file 0 and 1
  vector<TString> idNames2   = {"MVATightNew2","MVAVLooseFONew","MVAVLooseNew"};//names for 2 & 3
  vector<TString> idNames3   = {"MVATightSpr16","MVAVLooseFOSpr16","MVAVLooseSpr16"};//names for 4 & 5

  TH1D *h_num[2*3*idNames.size()], *h_den[2*3*idNames.size()];
  TGraphAsymmErrors *h_grRef[3*idNames.size()], *h_gr[3*idNames.size()];
  TLegend *legend[idNames.size()];

  TCanvas *cA[idNames.size()];
  TH1D *h_Num, *h_Den;  

  f[0] = new TFile("mc_eff_2016.root");   col[0] = kBlue;//kGreen+2;
  f[1] = new TFile("mc_fake_2016.root");  col[1] = kBlue;//kGreen+2;
  f[2] = new TFile("mc_eff_2017.root");   col[2] = kRed;
  f[3] = new TFile("mc_fake_2017.root");  col[3] = kRed; 
  f[4] = new TFile("mc_eff_2018.root");   col[4] = kGreen+2;
  f[5] = new TFile("mc_fake_2018.root");  col[5] = kGreen+2;
  
  TPaveText *tx1 = new TPaveText(0.4,0.5,0.6,0.6,"NDC");
  tx1->AddText("|#eta|<0.8"); tx1->SetFillColor(0); tx1->SetShadowColor(0);
  TPaveText *tx2 = new TPaveText(0.4,0.5,0.8,0.6,"NDC");
  tx2->AddText("0.8#leq|#eta|<1.479"); tx2->SetFillColor(0); tx2->SetShadowColor(0);
  TPaveText *tx3 = new TPaveText(0.4,0.5,0.8,0.6,"NDC");
  tx3->AddText("1.479#leq|#eta|<2.4"); tx3->SetFillColor(0); tx3->SetShadowColor(0);

  for(int i=0;i<idNames.size();i++){
    name = idNames[i];
    cA[i] = new TCanvas(name,name,1400,450);
    cA[i]->Divide(3,1);

    if(logY){
      cA[i]->cd(1);gPad->SetLogy();
      cA[i]->cd(2);gPad->SetLogy();
      cA[i]->cd(3);gPad->SetLogy();
    }
    
    for(int p=0;p<nfiles;p++){
      //----------------for eta1------------------
      if(diffHistsToCom){
      	if(p<=1){
      	  h_Num = (TH1D*)f[p]->Get("prbPt_Eta1_"+idNames[i]); setLastBinAsOverFlow(h_Num);
      	}
      	else if(p<=3){
      	  h_Num = (TH1D*)f[p]->Get("prbPt_Eta1_"+idNames2[i]); setLastBinAsOverFlow(h_Num);
      	}
      	else{
      	  h_Num = (TH1D*)f[p]->Get("prbPt_Eta1_"+idNames3[i]); setLastBinAsOverFlow(h_Num);
      	}
      }
      else
	h_Num = (TH1D*)f[p]->Get("prbPt_Eta1_"+idNames[i]); setLastBinAsOverFlow(h_Num);
      h_Den = (TH1D*)f[p]->Get("prbPt_Eta1");             setLastBinAsOverFlow(h_Den);
      h_gr[i]    = new TGraphAsymmErrors(h_Num,h_Den);
      
      cA[i]->cd(1);cA[i]->SetLogy();
      setGraphProp(h_gr[i],col[p]);

      if(p==0) h_gr[i]->Draw("AP");
      else h_gr[i]->Draw("sames");
      tx1->Draw();
      //----------------for eta2------------------
      if(diffHistsToCom){
      	if(p<=1){
      	  h_Num = (TH1D*)f[p]->Get("prbPt_Eta2_"+idNames[i]); setLastBinAsOverFlow(h_Num);
      	}
      	else if(p<=3){
      	  h_Num = (TH1D*)f[p]->Get("prbPt_Eta2_"+idNames2[i]); setLastBinAsOverFlow(h_Num);
      	}
      	else{
      	  h_Num = (TH1D*)f[p]->Get("prbPt_Eta2_"+idNames3[i]); setLastBinAsOverFlow(h_Num);
      	}
      }
      else
	h_Num = (TH1D*)f[p]->Get("prbPt_Eta2_"+idNames[i]); setLastBinAsOverFlow(h_Num);
      h_Den = (TH1D*)f[p]->Get("prbPt_Eta2");             setLastBinAsOverFlow(h_Den);
      h_gr[i]    = new TGraphAsymmErrors(h_Num,h_Den);
      
      cA[i]->cd(2);cA[i]->SetLogy();
      setGraphProp(h_gr[i],col[p]);

      if(p==0) h_gr[i]->Draw("AP");
      else h_gr[i]->Draw("sames");
      tx2->Draw();
      //----------------for eta3------------------
      if(diffHistsToCom){
      	if(p<=1){
      	  h_Num = (TH1D*)f[p]->Get("prbPt_Eta3_"+idNames[i]); setLastBinAsOverFlow(h_Num);
      	}
      	else if(p<=3){
      	  h_Num = (TH1D*)f[p]->Get("prbPt_Eta3_"+idNames2[i]); setLastBinAsOverFlow(h_Num);
      	}
      	else{
      	  h_Num = (TH1D*)f[p]->Get("prbPt_Eta3_"+idNames3[i]); setLastBinAsOverFlow(h_Num);
      	}
      }
      else
	h_Num = (TH1D*)f[p]->Get("prbPt_Eta3_"+idNames[i]); setLastBinAsOverFlow(h_Num);
      h_Den = (TH1D*)f[p]->Get("prbPt_Eta3");             setLastBinAsOverFlow(h_Den);
      h_gr[i]    = new TGraphAsymmErrors(h_Num,h_Den);
      
      cA[i]->cd(3);cA[i]->SetLogy();
      setGraphProp(h_gr[i],col[p]);

      if(p==0) h_gr[i]->Draw("AP");
      else h_gr[i]->Draw("sames");
      tx3->Draw();
      //----------------------------------------
      name = f[p]->GetName();
      if(!name.Contains("fake")){
	if(p==0){
	  //legend[i] = new TLegend(0.25,0.35,0.55,0.5);
	  if(logY)  legend[i] = new TLegend(0.25,0.68,0.65,0.78); 
	  else
	    legend[i] = new TLegend(0.15,0.75,0.65,0.88);
	  //    legend[i] = new TLegend(0.15,0.9,0.85,0.8)    legend[i]->SetNColumns(2);
	  legend[i]->SetTextSize(0.05);
	  legend[i]->SetBorderSize(0);
	}
	TString legName = idNames[i];
	// if(p<=1) legName = idNames[i];
	// else if(p<=3) legName = idNames2[i];
	// else legName = idNames3[i];
	legName.ReplaceAll("New2","");
	legName.ReplaceAll("New",""); 	
	name = f[p]->GetName();
	if(name.Contains("2018")) legName = legName + " (2018)";
	else if(name.Contains("2016")) legName = legName + " (2016)";
	else if(name.Contains("2017")) legName = legName + " (2017)";
	else legName = legName + name;
	legend[i]->AddEntry(h_gr[i],legName,"lpe");
      }
    }//loop over files
    cA[i]->cd(1);
    legend[i]->Draw();
    textOnTop.DrawLatexNDC(0.12,0.91,cmsName); 	intLumiE.DrawLatexNDC(0.75,0.91,name2);
    cA[i]->cd(2);
    legend[i]->Draw();
    textOnTop.DrawLatexNDC(0.12,0.91,cmsName);	intLumiE.DrawLatexNDC(0.75,0.91,name2);
    cA[i]->cd(3);
    legend[i]->Draw();
    textOnTop.DrawLatexNDC(0.12,0.91,cmsName);	intLumiE.DrawLatexNDC(0.75,0.91,name2);

    if(savePlots){name = name+".png"; cA[i]->SaveAs(name);}
  }//ids
  
}
   
void setGraphProp(TGraphAsymmErrors* h_gr, int col1){
  h_gr->SetMarkerColor(col1);
  h_gr->SetLineColor(col1);
  if(col1!=kRed)  h_gr->SetLineWidth(2);
  else  h_gr->SetLineWidth(2);
  h_gr->SetMinimum(0.007);
  h_gr->SetMaximum(1.29);
  // h_gr->SetMinimum(0.94);
  // h_gr->SetMaximum(1.02);
  // h_gr->SetMinimum(0.89);
  // h_gr->SetMaximum(1.0);
  h_gr->SetTitle(0);
  h_gr->GetYaxis()->SetTitle("#varepsilon");
  h_gr->GetYaxis()->SetTitleOffset(1.08);
  h_gr->GetYaxis()->SetTitleSize(0.06);

  h_gr->GetXaxis()->SetNdivisions(10);
  h_gr->GetXaxis()->SetTitle("e pT(GeV)");
  //  if(col1==kBlue) h_gr->SetLineWidth(3);
}

void setLastBinAsOverFlow(TH1D* h_hist){
  return;
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
