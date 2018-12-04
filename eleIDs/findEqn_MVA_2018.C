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

double getBinCenterWithRightIntgrFrac(TH1D*,double);
void findEqn_MVA_2018(){
  TH1::SetDefaultSumw2(1);
  TFile *fRef = new TFile("mc_eff_2017.root");
  TFile *f = new TFile("mc_eff_2018.root");
  
  string IDtype = "MVAVLooseFONew";
  TString name;
  
  double refEff1=0, refEff2=0, refEff3=0;
  double mvaCuts[3];

  TH1D *h_ptRef,*h_mvaRef,*h_mva;

  for(int i=1;i<=3;i++){
    TString mvaHistName1="pt5to10_Eta"+to_string(i)+"_MVA94Xnoiso";
    TString mvaHistName2="pt10to15_Eta"+to_string(i)+"_MVA94Xnoiso";
    TString mvaHistName3="pt25_Eta"+to_string(i)+"_MVA94Xnoiso";

    name = "prbPt_Eta"+to_string(i)+"_"+IDtype;
    h_ptRef = (TH1D*)fRef->Get(name);
    h_mvaRef= (TH1D*)fRef->Get(mvaHistName1);
    h_mva   = (TH1D*)f->Get(mvaHistName1);

    refEff1 = h_ptRef->Integral(h_ptRef->FindBin(5.0001), h_ptRef->FindBin(9.9999));
    refEff1 = refEff1/(h_mvaRef->Integral());
    mvaCuts[0] = getBinCenterWithRightIntgrFrac(h_mva, refEff1);
    //---------------------------
    name = "prbPt_Eta"+to_string(i)+"_"+IDtype;
    h_ptRef = (TH1D*)fRef->Get(name);
    h_mvaRef= (TH1D*)fRef->Get(mvaHistName2);
    h_mva   = (TH1D*)f->Get(mvaHistName2);

    refEff1 = h_ptRef->Integral(h_ptRef->FindBin(10.0001), h_ptRef->FindBin(14.9999));
    //    cout<<"\n\nRef: "<<refEff1<<" denom:"<<(h_mvaRef->Integral())<<" ";
    refEff1 = refEff1/(h_mvaRef->Integral());
    mvaCuts[1] = getBinCenterWithRightIntgrFrac(h_mva, refEff1);
    //    cout<<mvaCuts[1]<<" ,,,,,"<<endl;
    //---------------------------
    name = "prbPt_Eta"+to_string(i)+"_"+IDtype;
    h_ptRef = (TH1D*)fRef->Get(name);
    h_mvaRef= (TH1D*)fRef->Get(mvaHistName3);
    h_mva   = (TH1D*)f->Get(mvaHistName3);

    refEff1 = h_ptRef->Integral(h_ptRef->FindBin(25.0001), h_ptRef->GetNbinsX()+1);
    refEff1 = refEff1/(h_mvaRef->Integral());
    mvaCuts[2] = getBinCenterWithRightIntgrFrac(h_mva, refEff1);

    // cout<<IDtype<<endl;
    //    if(!IDtype.Contains("Tight")) printf("MVA_Cut_5-10GeV: %0.3f\n",mvaCuts[0]);
    // printf("MVA_Cut_10-25GeV: %0.3f + (%0.3f/15.0)*(el_pt - 10.0)\n",mvaCuts[1],mvaCuts[2]-mvaCuts[1]);
    // printf("MVA_Cut_>25GeV: %0.3f\n",mvaCuts[2]);
    // printf("---------------------------\n");
    // //    printf("MVA_Cut_5-10GeV: %0.3f\n",mvaCuts[0]);
    // printf("mvaEta%d_%s[0] = %0.3f;\n",i,IDtype.c_str(),mvaCuts[0]);
    // printf("mvaEta%d_%s[1] = %0.3f;\n",i,IDtype.c_str(),mvaCuts[1]);
    // printf("mvaEta%d_%s[2] = %0.3f;\n",i,IDtype.c_str(),mvaCuts[2]);
    //    printf("mva2m1Eta%d_%s = %0.3f;\n",i,IDtype.c_str(),mvaCuts[2]-mvaCuts[1]);
    //    printf("\n");
    if(i==1) cout<<"Eqn: y = [1] + [2] * (el_pt - 25.0)\n";
    printf("mvaEta%d_%s[0] = %0.3f;\n",i,IDtype.c_str(),mvaCuts[0]);
    printf("mvaEta%d_%s[1] = %0.3f;\n",i,IDtype.c_str(),mvaCuts[2]);
    printf("mvaEta%d_%s[2] = %0.3f;\n",i,IDtype.c_str(),(mvaCuts[2]-mvaCuts[1])/12.5);
    cout<<endl;
    
  }
  //  cout<<sum<<" mva2:"<<mvaCut2<<" intgr2:"<<intgr2<<endl;
  // cout<<"For pt > 25, mva value: "<<mvaCut2<<endl;
  // cout<<"--------------------Equation ("<<refHistName<<")-----------------------"<<endl;
  // double slope = 0.;
  // slope = (mvaCut2-mvaCut1)/(25.-10.);
  // cout<<"mva = "<<mvaCut1<<" + (("<<mvaCut2<<" - ("<<mvaCut1<<"))/15)(pt-10)"<<endl;
  // cout<<"if(el_pt >= 25 && el_MVA94Xnoiso > "<<mvaCut2<<")"<<endl;
  // cout<<"else if(el_MVA94Xnoiso > ("<<mvaCut1<<" + ("<<mvaCut2-mvaCut1<<"/15.)*(el_pt-10.)))"<<endl<<endl;
}


double getBinCenterWithRightIntgrFrac(TH1D* h1,double frac){
  double sum = 0.;
  double totInt = h1->Integral()+h1->GetBinContent(h1->GetNbinsX()+1);
  for(int i=h1->GetNbinsX()+1;i>0;i--){
    if(h1->GetBinContent(i)<0.00001) continue;
    sum+=h1->GetBinContent(i);
    if((sum/totInt) >= frac){
      //      cout<<" sum:"<<sum<<" Intgr:"<<totInt<<" BinCenter:"<<h1->GetBinCenter(i)<<" ";
      return h1->GetBinCenter(i);
    }
  }
  return h1->GetBinCenter(1);
}
