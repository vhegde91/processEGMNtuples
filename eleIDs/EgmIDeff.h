#ifndef EgmIDeff_H
#define EgmIDeff_H

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include "NtupleVariables.h"
#include "TH1F.h"
#include "TH2.h"
#include "TH3.h"
#include <TH2Poly.h>
#include <TProfile.h>
#include "TFile.h"
#include "TLorentzVector.h"
#include "TDirectory.h"

class EgmIDeff : public NtupleVariables{

 public:
  EgmIDeff(const TString &inputFileList="foo.txt", const char *outFileName="histo.root",const char *dataset="data");
  ~EgmIDeff();
  Bool_t   FillChain(TChain *chain, const TString &inputFileList);
  Long64_t LoadTree(Long64_t entry);
  void     EventLoop(const char *,const char *);
  void     BookHistogram(const char *);
  void     printInfo(Long64_t jentry);
  //-----------------------
  vector<float> ptBins = {10, 20, 30, 40, 50, 100, 200};
  TH1D *h_ZMass;
  TH1D *h_prbPtmc;  
  TH1D *h_prbPt;
  TH1D *h_prbPt_Loose80X;
  TH1D *h_prbPt_Loose94X;
  TH1D *h_prbPtvBin;
  TH1D *h_prbPt_Loose80XvBin;
  TH1D *h_prbPt_Loose94XvBin;

  TH2D *h2_mcTrueVsdR;
  TH2D *h2_mcFlagVsdR;
  TFile *oFile;
  
};
#endif

#ifdef EgmIDeff_cxx

void EgmIDeff::BookHistogram(const char *outFileName) {

  //  char hname[200], htit[200];
  //  double xlow = 0.0,  xhigh = 2000.0;
  //  int nbins = 2000;
  char name[100],title[100];
 
  oFile = new TFile(outFileName, "recreate");
  TH1::SetDefaultSumw2(1);
  TH2::SetDefaultSumw2(1);
  h_ZMass = new TH1D("ZMass","Inv mass tag-probe",200,0,200);
  h_prbPtmc = new TH1D("prbPtmc","gen Pt of the probe",19,10,200);

  h_prbPt = new TH1D("prbPt","Pt of the probe",19,10,200);
  h_prbPt_Loose80X = new TH1D("prbPt_Loose80X","Pt of the probe passing Loose80X",19,10,200);
  h_prbPt_Loose94X = new TH1D("prbPt_Loose94X","Pt of the probe passing Loose94X",19,10,200);

  h_prbPtvBin = new TH1D("prbPtvBin","Pt of the probe",ptBins.size()-1,&(ptBins[0]));
  h_prbPt_Loose80XvBin = new TH1D("prbPt_Loose80X_vBin","Pt of the probe passing Loose80X",ptBins.size()-1,&(ptBins[0]));
  h_prbPt_Loose94XvBin = new TH1D("prbPt_Loose94X_vBin","Pt of the probe passing Loose94X",ptBins.size()-1,&(ptBins[0]));

  h2_mcTrueVsdR = new TH2D("mcTrueVsdR","x: mcTrue, y:#DetaR(mc_probe,reco probe",3,0,3, 60,0,3);
  h2_mcFlagVsdR = new TH2D("mcFlagVsdR","x: mcFlag, y:#DetaR(mc_probe,reco probe",3,0,3, 60,0,3);
}


EgmIDeff::EgmIDeff(const TString &inputFileList, const char *outFileName, const char* dataset) {
  string nameData=dataset;//vvv
  TChain *tree = new TChain("tnpEleIDs/fitter_tree");
  
  if( ! FillChain(tree, inputFileList) ) {
    std::cerr << "Cannot get the tree " << std::endl;
  } else {
    std::cout << "Initiating analysis of dataset " << dataset << std::endl;
  }

  if(nameData!="signalH") nameData="BG";
  if(nameData=="signalH") nameData="signal";
  cout<<"Treating the input files as "<<nameData<<" for setting tree branches"<<endl;
  NtupleVariables::Init(tree,nameData);

  BookHistogram(outFileName);
  
}

Bool_t EgmIDeff::FillChain(TChain *chain, const TString &inputFileList) {

  ifstream infile(inputFileList, ifstream::in);
  std::string buffer;

  if(!infile.is_open()) {
    std::cerr << "** ERROR: Can't open '" << inputFileList << "' for input" << std::endl;
    return kFALSE;
  }

  std::cout << "TreeUtilities : FillChain " << std::endl;
  while(1) {
    infile >> buffer;
    if(!infile.good()) break;
    //std::cout << "Adding tree from " << buffer.c_str() << std::endl;                                                              
    chain->Add(buffer.c_str());
  }
  std::cout << "No. of Entries in this tree : " << chain->GetEntries() << std::endl;
  return kTRUE;
}

Long64_t EgmIDeff::LoadTree(Long64_t entry) {
  // Set the environment to read one entry                                                                                          
  if (!fChain) return -5;
  Long64_t centry = fChain->LoadTree(entry);
  if (centry < 0) return centry;
  if (!fChain->InheritsFrom(TChain::Class()))  return centry;
  TChain *chain = (TChain*)fChain;
  if (chain->GetTreeNumber() != fCurrent) {
    fCurrent = chain->GetTreeNumber();
    //    Notify();
  }
  return centry;
}

EgmIDeff::~EgmIDeff() { 

  if (!fChain) return;
  delete fChain->GetCurrentFile();
  oFile->cd();
  oFile->Write();
  oFile->Close();

}

#endif

