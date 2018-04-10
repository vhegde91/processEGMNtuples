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

void getEffFakes_MVA(){
  TH1::SetDefaultSumw2(1);

  int nfiles=2;
  TFile *f[nfiles];
  bool logY = 0;
  TString name="EGMid";
  xAxisLabel="pT(GeV)";
  char name2[100];
  TString cmsName = "CMS #it{#bf{Simulation}}";
  textOnTop.SetTextSize(0.04);
  intLumiE.SetTextSize(0.04);
  sprintf(name2,"#bf{(13TeV)}");

  // vector<TString> idNames    = {"MVA94Xwp80noiso","MVA94Xwp90noiso"};
  // vector<TString> refIdNames = {"MVA94Xwp80iso","MVA94Xwp90iso"};
  
  // vector<TString> idNames    = {"MVATight","MVATight","MVAVLooseFONew","MVAVLooseNew"};
  // vector<TString> refIdNames = {"MVATightNew","MVATightNew2","MVAVLooseFO","MVAVLoose"};

  vector<TString> idNames    = {"MVATightNew2","MVAVLooseFONew","MVAVLooseNew"};
  vector<TString> refIdNames = {"MVATight","MVAVLooseFO","MVAVLoose"};

  // vector<TString> idNames    = {"MVA94Xwp80noiso","MVA94Xwp80noiso","MVA94Xwp90noiso","MVA94Xwp90noiso"};
  // vector<TString> refIdNames = {"MVA80Xwp80","MVA94Xwp80iso","MVA80Xwp90","MVA94Xwp90iso"};
  // vector<TString> idNames    = {"MVAVLoose","MVAVLooseFO","MVATight"};
  // vector<TString> refIdNames = {"MVA94Xwp98noiso","MVA94Xwp98noiso","MVA94Xwp98noiso"};

  TH1D *h_num[2*3*idNames.size()], *h_den[2*3*idNames.size()];
  TGraphAsymmErrors *h_grRef[3*idNames.size()], *h_gr[3*idNames.size()];
  TLegend *legend[2*idNames.size()];

  TCanvas *cA[idNames.size()];
  TH1D *h_Num, *h_Den;  

  f[0] = new TFile("mc_eff.root");//mc_eff_all.root");
  f[1] = new TFile("mc_fake.root");//mc_fake_all.root");
  //f[0] = new TFile("mc_eff_all.root");
  //f[1] = new TFile("mc_fake_all.root");
 
  // f[0] = new TFile("a.root");  
  // f[1] = new TFile("b.root");
  bool hasOldID = true;

  TPaveText *tx1 = new TPaveText(0.4,0.5,0.6,0.6,"NDC");
  tx1->AddText("|#eta|<0.8"); tx1->SetFillColor(0); tx1->SetShadowColor(0);
  TPaveText *tx2 = new TPaveText(0.4,0.5,0.8,0.6,"NDC");
  tx2->AddText("0.8#leq|#eta|<1.479"); tx2->SetFillColor(0); tx2->SetShadowColor(0);
  TPaveText *tx3 = new TPaveText(0.4,0.5,0.8,0.6,"NDC");
  tx3->AddText("1.479#leq|#eta|<2.4"); tx3->SetFillColor(0); tx3->SetShadowColor(0);

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

    if(logY){
      cA[i]->cd(1);gPad->SetLogy();
      cA[i]->cd(2);gPad->SetLogy();
      cA[i]->cd(3);gPad->SetLogy();
    }
    
    for(int p=0;p<nfiles;p++){
      //----------------for eta1------------------
      h_Num = (TH1D*)f[p]->Get("prbPt_Eta1_"+idNames[i]); setLastBinAsOverFlow(h_Num);
      h_Den = (TH1D*)f[p]->Get("prbPt_Eta1");             setLastBinAsOverFlow(h_Den);
      h_gr[i]    = new TGraphAsymmErrors(h_Num,h_Den);
      
      if(hasOldID){
	h_Num = (TH1D*)f[p]->Get("prbPt_Eta1_"+refIdNames[i]); setLastBinAsOverFlow(h_Num);
	h_grRef[i] = new TGraphAsymmErrors(h_Num,h_Den);
      }

      cA[i]->cd(1);cA[i]->SetLogy();
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
      tx1->Draw();
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
      tx2->Draw();
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
      tx3->Draw();
      //----------------------------------------
      if(p==0){
	//legend[i] = new TLegend(0.25,0.35,0.55,0.5);
	if(logY)  legend[i] = new TLegend(0.25,0.68,0.65,0.78); 
	else
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
