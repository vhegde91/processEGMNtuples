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

void findEqn_MVA(){
  TH1::SetDefaultSumw2(1);
  TFile *f = new TFile("mc_eff.root");
  //  TString mvaHistName1="pt10to15_Eta3_MVA94Xnoiso";
  TString mvaHistName1="pt5to10_Eta1_MVA94Xnoiso";
  TString mvaHistName2="pt25_Eta1_MVA94Xnoiso";

  TString refHistName="prbPt_Eta1_MVAVLooseFO";

  TH1D *h_ref=(TH1D*)f->Get(refHistName);
  TH1D *h_mva1=(TH1D*)f->Get(mvaHistName1);
  TH1D *h_mva2=(TH1D*)f->Get(mvaHistName2);

  double intgr1=h_ref->Integral(h_ref->FindBin(5.0001),h_ref->FindBin(9.999));
  double intgr2=h_ref->Integral(h_ref->FindBin(25.0001),h_ref->GetNbinsX()+1);

  double mvaCut1=-100,mvaCut2=-100,sum=0.;

  for(int i=h_mva1->GetNbinsX();i>0;i--){
    sum+=h_mva1->GetBinContent(i);
    if(sum>=intgr1){
      mvaCut1 = h_mva1->GetBinCenter(i);
      //mvaCut1 = h_mva1->GetBinLowEdge(i);
      break;
    }
  }
  cout<<"For pt ~10 mva value: "<<mvaCut1<<endl<<endl;
  sum=0.;
  for(int i=h_mva2->GetNbinsX();i>0;i--){
    sum+=h_mva2->GetBinContent(i);
    if(sum>=intgr2){
      mvaCut2 = h_mva2->GetBinCenter(i);
      //mvaCut2 = h_mva2->GetBinLowEdge(i);
      break;
    }
  }
  //  cout<<sum<<" mva2:"<<mvaCut2<<" intgr2:"<<intgr2<<endl;
  cout<<"For pt > 25, mva value: "<<mvaCut2<<endl;
  cout<<"--------------------Equation ("<<refHistName<<")-----------------------"<<endl;
  double slope = 0.;
  slope = (mvaCut2-mvaCut1)/(25.-10.);
  cout<<"mva = "<<mvaCut1<<" + (("<<mvaCut2<<" - ("<<mvaCut1<<"))/15)(pt-10)"<<endl;
  cout<<"if(el_pt >= 25 && el_MVA94Xnoiso > "<<mvaCut2<<")"<<endl;
  cout<<"else if(el_MVA94Xnoiso > ("<<mvaCut1<<" + ("<<mvaCut2-mvaCut1<<"/15.)*(el_pt-10.)))"<<endl<<endl;
}
