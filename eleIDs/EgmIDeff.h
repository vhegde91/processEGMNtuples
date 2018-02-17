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
  TH1D *h_prbPt_EB;
  TH1D *h_prbPt_EE;
  TH1D *h_prbEta_Pt25;
  TH1D *h_prbPt_Eta1;
  TH1D *h_prbPt_Eta2;
  TH1D *h_prbPt_Eta3;
  //------------------ EGM ID ----------------
  TH1D *h_prbPt_EB_Loose80X;
  TH1D *h_prbPt_EB_Loose94X;
  TH1D *h_prbPt_EB_Medium80X;
  TH1D *h_prbPt_EB_Medium94X;
  TH1D *h_prbPt_EB_Tight80X;
  TH1D *h_prbPt_EB_Tight94X;

  TH1D *h_prbPt_EE_Loose80X;
  TH1D *h_prbPt_EE_Loose94X;
  TH1D *h_prbPt_EE_Medium80X;
  TH1D *h_prbPt_EE_Medium94X;
  TH1D *h_prbPt_EE_Tight80X;
  TH1D *h_prbPt_EE_Tight94X;

  TH1D *h_prbEta_Pt25_Loose80X;
  TH1D *h_prbEta_Pt25_Loose94X;
  TH1D *h_prbEta_Pt25_Medium80X;
  TH1D *h_prbEta_Pt25_Medium94X;
  TH1D *h_prbEta_Pt25_Tight80X;
  TH1D *h_prbEta_Pt25_Tight94X;
  //------------------ SUSY ID No Iso ----------------
  TH1D *h_prbPt_EB_CutBasedVetoNoIso;
  TH1D *h_prbPt_EB_CutBasedVetoNoIso94X;
  TH1D *h_prbPt_EB_CutBasedLooseNoIso;
  TH1D *h_prbPt_EB_CutBasedLooseNoIso94X;
  TH1D *h_prbPt_EB_CutBasedMediumNoIso;
  TH1D *h_prbPt_EB_CutBasedMediumNoIso94X;
  TH1D *h_prbPt_EB_CutBasedTightNoIso;
  TH1D *h_prbPt_EB_CutBasedTightNoIso94X;

  TH1D *h_prbPt_EE_CutBasedVetoNoIso;
  TH1D *h_prbPt_EE_CutBasedVetoNoIso94X;
  TH1D *h_prbPt_EE_CutBasedLooseNoIso;
  TH1D *h_prbPt_EE_CutBasedLooseNoIso94X;
  TH1D *h_prbPt_EE_CutBasedMediumNoIso;
  TH1D *h_prbPt_EE_CutBasedMediumNoIso94X;
  TH1D *h_prbPt_EE_CutBasedTightNoIso;
  TH1D *h_prbPt_EE_CutBasedTightNoIso94X;

  TH1D *h_prbEta_Pt25_CutBasedVetoNoIso;
  TH1D *h_prbEta_Pt25_CutBasedVetoNoIso94X;
  TH1D *h_prbEta_Pt25_CutBasedLooseNoIso;
  TH1D *h_prbEta_Pt25_CutBasedLooseNoIso94X;
  TH1D *h_prbEta_Pt25_CutBasedMediumNoIso;
  TH1D *h_prbEta_Pt25_CutBasedMediumNoIso94X;
  TH1D *h_prbEta_Pt25_CutBasedTightNoIso;
  TH1D *h_prbEta_Pt25_CutBasedTightNoIso94X;

  //------------------ MVA ID ----------------
  TH1D *h_prbPt_Eta1_MVA80Xwp80;
  TH1D *h_prbPt_Eta1_MVA80Xwp90;
  TH1D *h_prbPt_Eta1_MVAWP80;
  TH1D *h_prbPt_Eta1_MVAWP90;
  TH1D *h_prbPt_Eta1_LeptonMvaM;
  TH1D *h_prbPt_Eta1_LeptonMvaVT;
  TH1D *h_prbPt_Eta1_LeptonMvaMIDEmuTightIP2DSIP3D8miniIso04;
  TH1D *h_prbPt_Eta1_LeptonMvaVTIDEmuTightIP2DSIP3D8miniIso04;

  TH1D *h_prbPt_Eta2_MVA80Xwp80;
  TH1D *h_prbPt_Eta2_MVA80Xwp90;
  TH1D *h_prbPt_Eta2_MVAWP80;
  TH1D *h_prbPt_Eta2_MVAWP90;
  TH1D *h_prbPt_Eta2_LeptonMvaM;
  TH1D *h_prbPt_Eta2_LeptonMvaVT;
  TH1D *h_prbPt_Eta2_LeptonMvaMIDEmuTightIP2DSIP3D8miniIso04;
  TH1D *h_prbPt_Eta2_LeptonMvaVTIDEmuTightIP2DSIP3D8miniIso04;

  TH1D *h_prbPt_Eta3_MVA80Xwp80;
  TH1D *h_prbPt_Eta3_MVA80Xwp90;
  TH1D *h_prbPt_Eta3_MVAWP80;
  TH1D *h_prbPt_Eta3_MVAWP90;
  TH1D *h_prbPt_Eta3_LeptonMvaM;
  TH1D *h_prbPt_Eta3_LeptonMvaVT;
  TH1D *h_prbPt_Eta3_LeptonMvaMIDEmuTightIP2DSIP3D8miniIso04;
  TH1D *h_prbPt_Eta3_LeptonMvaVTIDEmuTightIP2DSIP3D8miniIso04;
  //-----------------------------------------------------------
  
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

  h_prbPt_EB = new TH1D("prbPt_EB","Pt of the probe EB",19,10,200);
  h_prbPt_EE = new TH1D("prbPt_EE","Pt of the probe EE",19,10,200);
  h_prbEta_Pt25 = new TH1D("prbEta_Pt25","#eta of the probe, pT probe > 25GeV",40,0,4);
  h_prbPt_Eta1 = new TH1D("prbPt_Eta1","Pt of the probe, |#eta| < 0.8",19,10,200);
  h_prbPt_Eta2 = new TH1D("prbPt_Eta2","Pt of the probe, 0.8 #leq |#eta| < 1.479",19,10,200);
  h_prbPt_Eta3 = new TH1D("prbPt_Eta3","Pt of the probe, 1.479 #leq |#eta| < 2.5",19,10,200);
  //------------------ EGM ID ----------------
  h_prbPt_EB_Loose80X = new TH1D("prbPt_EB_Loose80X","Pt of the EB probe passing Loose80X",19,10,200);
  h_prbPt_EB_Loose94X = new TH1D("prbPt_EB_Loose94X","Pt of the EB probe passing Loose94X",19,10,200);
  h_prbPt_EB_Medium80X = new TH1D("prbPt_EB_Medium80X","Pt of the EB probe passing Medium80X",19,10,200);
  h_prbPt_EB_Medium94X = new TH1D("prbPt_EB_Medium94X","Pt of the EB probe passing Medium94X",19,10,200);
  h_prbPt_EB_Tight80X = new TH1D("prbPt_EB_Tight80X","Pt of the EB probe passing Tight80X",19,10,200);
  h_prbPt_EB_Tight94X = new TH1D("prbPt_EB_Tight94X","Pt of the EB probe passing Tight94X",19,10,200);

  h_prbPt_EE_Loose80X = new TH1D("prbPt_EE_Loose80X","Pt of the EE probe passing Loose80X",19,10,200);
  h_prbPt_EE_Loose94X = new TH1D("prbPt_EE_Loose94X","Pt of the EE probe passing Loose94X",19,10,200);
  h_prbPt_EE_Medium80X = new TH1D("prbPt_EE_Medium80X","Pt of the EE probe passing Medium80X",19,10,200);
  h_prbPt_EE_Medium94X = new TH1D("prbPt_EE_Medium94X","Pt of the EE probe passing Medium94X",19,10,200);
  h_prbPt_EE_Tight80X = new TH1D("prbPt_EE_Tight80X","Pt of the EE probe passing Tight80X",19,10,200);
  h_prbPt_EE_Tight94X = new TH1D("prbPt_EE_Tight94X","Pt of the EE probe passing Tight94X",19,10,200);

  h_prbEta_Pt25_Loose80X = new TH1D("prbEta_Pt25_Loose80X","|#eta| of the #geq 25GeV Pt probe passing Loose80X",40,0,4);
  h_prbEta_Pt25_Loose94X = new TH1D("prbEta_Pt25_Loose94X","|#eta| of the #geq 25GeV Pt probe passing Loose94X",40,0,4);
  h_prbEta_Pt25_Medium80X = new TH1D("prbEta_Pt25_Medium80X","|#eta| of the #geq 25GeV Pt probe passing Medium80X",40,0,4);
  h_prbEta_Pt25_Medium94X = new TH1D("prbEta_Pt25_Medium94X","|#eta| of the #geq 25GeV Pt probe passing Medium94X",40,0,4);
  h_prbEta_Pt25_Tight80X = new TH1D("prbEta_Pt25_Tight80X","|#eta| of the #geq 25GeV Pt probe passing Tight80X",40,0,4);
  h_prbEta_Pt25_Tight94X = new TH1D("prbEta_Pt25_Tight94X","|#eta| of the #geq 25GeV Pt probe passing Tight94X",40,0,4);

  //------------------ SUSY ID No Iso ----------------
  h_prbPt_EB_CutBasedVetoNoIso = new TH1D("prbPt_EB_CutBasedVetoNoIso","Pt of the EB probe passing CutBasedVetoNoIso",19,10,200);
  h_prbPt_EB_CutBasedVetoNoIso94X = new TH1D("prbPt_EB_CutBasedVetoNoIso94X ","Pt of the EB probe passing CutBasedVetoNoIso94X",19,10,200);
  h_prbPt_EB_CutBasedLooseNoIso = new TH1D("prbPt_EB_CutBasedLooseNoIso","Pt of the EB probe passing CutBasedLooseNoIso",19,10,200);
  h_prbPt_EB_CutBasedLooseNoIso94X = new TH1D("prbPt_EB_CutBasedLooseNoIso94X","Pt of the EB probe passing CutBasedLooseNoIso94X",19,10,200);
  h_prbPt_EB_CutBasedMediumNoIso = new TH1D("prbPt_EB_CutBasedMediumNoIso","Pt of the EB probe passing CutBasedMediumNoIso",19,10,200);
  h_prbPt_EB_CutBasedMediumNoIso94X = new TH1D("prbPt_EB_CutBasedMediumNoIso94X","Pt of the EB probe passing CutBasedMediumNoIso94X",19,10,200);
  h_prbPt_EB_CutBasedTightNoIso = new TH1D("prbPt_EB_CutBasedTightNoIso","Pt of the EB probe passing CutBasedTightNoIso",19,10,200);
  h_prbPt_EB_CutBasedTightNoIso94X = new TH1D("prbPt_EB_CutBasedTightNoIso94X","Pt of the EB probe passing CutBasedTightNoIso94X",19,10,200);

  h_prbPt_EE_CutBasedVetoNoIso = new TH1D("prbPt_EE_CutBasedVetoNoIso","Pt of the EE probe passing CutBasedVetoNoIso",19,10,200);
  h_prbPt_EE_CutBasedVetoNoIso94X = new TH1D("prbPt_EE_CutBasedVetoNoIso94X ","Pt of the EE probe passing CutBasedVetoNoIso94X",19,10,200);
  h_prbPt_EE_CutBasedLooseNoIso = new TH1D("prbPt_EE_CutBasedLooseNoIso","Pt of the EE probe passing CutBasedLooseNoIso",19,10,200);
  h_prbPt_EE_CutBasedLooseNoIso94X = new TH1D("prbPt_EE_CutBasedLooseNoIso94X","Pt of the EE probe passing CutBasedLooseNoIso94X",19,10,200);
  h_prbPt_EE_CutBasedMediumNoIso = new TH1D("prbPt_EE_CutBasedMediumNoIso","Pt of the EE probe passing CutBasedMediumNoIso",19,10,200);
  h_prbPt_EE_CutBasedMediumNoIso94X = new TH1D("prbPt_EE_CutBasedMediumNoIso94X","Pt of the EE probe passing CutBasedMediumNoIso94X",19,10,200);
  h_prbPt_EE_CutBasedTightNoIso = new TH1D("prbPt_EE_CutBasedTightNoIso","Pt of the EE probe passing CutBasedTightNoIso",19,10,200);
  h_prbPt_EE_CutBasedTightNoIso94X = new TH1D("prbPt_EE_CutBasedTightNoIso94X","Pt of the EE probe passing CutBasedTightNoIso94X",19,10,200);

  h_prbEta_Pt25_CutBasedVetoNoIso = new TH1D("prbEta_Pt25_CutBasedVetoNoIso","|#eta| of the #geq 25GeV Pt probe passing CutBasedVetoNoIso",40,0,4);
  h_prbEta_Pt25_CutBasedVetoNoIso94X = new TH1D("prbEta_Pt25_CutBasedVetoNoIso94X ","|#eta| of the #geq 25GeV Pt probe passing CutBasedVetoNoIso94X",40,0,4);
  h_prbEta_Pt25_CutBasedLooseNoIso = new TH1D("prbEta_Pt25_CutBasedLooseNoIso","|#eta| of the #geq 25GeV Pt probe passing CutBasedLooseNoIso",40,0,4);
  h_prbEta_Pt25_CutBasedLooseNoIso94X = new TH1D("prbEta_Pt25_CutBasedLooseNoIso94X","|#eta| of the #geq 25GeV Pt probe passing CutBasedLooseNoIso94X",40,0,4);
  h_prbEta_Pt25_CutBasedMediumNoIso = new TH1D("prbEta_Pt25_CutBasedMediumNoIso","|#eta| of the #geq 25GeV Pt probe passing CutBasedMediumNoIso",40,0,4);
  h_prbEta_Pt25_CutBasedMediumNoIso94X = new TH1D("prbEta_Pt25_CutBasedMediumNoIso94X","|#eta| of the #geq 25GeV Pt probe passing CutBasedMediumNoIso94X",40,0,4);
  h_prbEta_Pt25_CutBasedTightNoIso = new TH1D("prbEta_Pt25_CutBasedTightNoIso","|#eta| of the #geq 25GeV Pt probe passing CutBasedTightNoIso",40,0,4);
  h_prbEta_Pt25_CutBasedTightNoIso94X = new TH1D("prbEta_Pt25_CutBasedTightNoIso94X","|#eta| of the #geq 25GeV Pt probe passing CutBasedTightNoIso94X",40,0,4);

  //------------------ MVA ID ----------------
  h_prbPt_Eta1_MVA80Xwp80 = new TH1D("prbPt_Eta1_MVA80Xwp80","Pt of the probe, |#eta| < 0.8, passing MVA80Xwp80",19,10,200);
  h_prbPt_Eta1_MVA80Xwp90 = new TH1D("prbPt_Eta1_MVA80Xwp90","Pt of the probe, |#eta| < 0.8, passing MVA80Xwp90",19,10,200);
  h_prbPt_Eta1_MVAWP80 = new TH1D("prbPt_Eta1_MVAWP80","Pt of the probe, |#eta| < 0.8, passing MVAWP80",19,10,200);
  h_prbPt_Eta1_MVAWP90 = new TH1D("prbPt_Eta1_MVAWP90","Pt of the probe, |#eta| < 0.8, passing MVAWP90",19,10,200);
  h_prbPt_Eta1_LeptonMvaM = new TH1D("prbPt_Eta1_LeptonMvaM","Pt of the probe, |#eta| < 0.8, passing LeptonMvaM",19,10,200);
  h_prbPt_Eta1_LeptonMvaVT = new TH1D("prbPt_Eta1_LeptonMvaVT","Pt of the probe, |#eta| < 0.8, passing LeptonMvaVT",19,10,200);
  h_prbPt_Eta1_LeptonMvaMIDEmuTightIP2DSIP3D8miniIso04 = new TH1D("prbPt_Eta1_LeptonMvaMIDEmuTightIP2DSIP3D8miniIso04","Pt of the probe, |#eta| < 0.8, passing LeptonMvaMIDEmuTightIP2DSIP3D8miniIso04",19,10,200);
  h_prbPt_Eta1_LeptonMvaVTIDEmuTightIP2DSIP3D8miniIso04 = new TH1D("prbPt_Eta1_LeptonMvaVTIDEmuTightIP2DSIP3D8miniIso04","Pt of the probe, |#eta| < 0.8, passing LeptonMvaVTIDEmuTightIP2DSIP3D8miniIso04",19,10,200);

  h_prbPt_Eta2_MVA80Xwp80 = new TH1D("prbPt_Eta2_MVA80Xwp80","Pt of the probe, 0.8 #leq |#eta| < 1.479, passing MVA80Xwp80",19,10,200);
  h_prbPt_Eta2_MVA80Xwp90 = new TH1D("prbPt_Eta2_MVA80Xwp90","Pt of the probe, 0.8 #leq |#eta| < 1.479, passing MVA80Xwp90",19,10,200);
  h_prbPt_Eta2_MVAWP80 = new TH1D("prbPt_Eta2_MVAWP80","Pt of the probe, 0.8 #leq |#eta| < 1.479, passing MVAWP80",19,10,200);
  h_prbPt_Eta2_MVAWP90 = new TH1D("prbPt_Eta2_MVAWP90","Pt of the probe, 0.8 #leq |#eta| < 1.479, passing MVAWP90",19,10,200);
  h_prbPt_Eta2_LeptonMvaM = new TH1D("prbPt_Eta2_LeptonMvaM","Pt of the probe, 0.8 #leq |#eta| < 1.479, passing LeptonMvaM",19,10,200);
  h_prbPt_Eta2_LeptonMvaVT = new TH1D("prbPt_Eta2_LeptonMvaVT","Pt of the probe, 0.8 #leq |#eta| < 1.479, passing LeptonMvaVT",19,10,200);
  h_prbPt_Eta2_LeptonMvaMIDEmuTightIP2DSIP3D8miniIso04 = new TH1D("prbPt_Eta2_LeptonMvaMIDEmuTightIP2DSIP3D8miniIso04","Pt of the probe, 0.8 #leq |#eta| < 1.479, passing LeptonMvaMIDEmuTightIP2DSIP3D8miniIso04",19,10,200);
  h_prbPt_Eta2_LeptonMvaVTIDEmuTightIP2DSIP3D8miniIso04 = new TH1D("prbPt_Eta2_LeptonMvaVTIDEmuTightIP2DSIP3D8miniIso04","Pt of the probe, 0.8 #leq |#eta| < 1.479, passing LeptonMvaVTIDEmuTightIP2DSIP3D8miniIso04",19,10,200);

  h_prbPt_Eta3_MVA80Xwp80 = new TH1D("prbPt_Eta3_MVA80Xwp80","Pt of the probe, 1.479 #leq |#eta| < 2.5, passing MVA80Xwp80",19,10,200);
  h_prbPt_Eta3_MVA80Xwp90 = new TH1D("prbPt_Eta3_MVA80Xwp90","Pt of the probe, 1.479 #leq |#eta| < 2.5, passing MVA80Xwp90",19,10,200);
  h_prbPt_Eta3_MVAWP80 = new TH1D("prbPt_Eta3_MVAWP80","Pt of the probe, 1.479 #leq |#eta| < 2.5, passing MVAWP80",19,10,200);
  h_prbPt_Eta3_MVAWP90 = new TH1D("prbPt_Eta3_MVAWP90","Pt of the probe, 1.479 #leq |#eta| < 2.5, passing MVAWP90",19,10,200);
  h_prbPt_Eta3_LeptonMvaM = new TH1D("prbPt_Eta3_LeptonMvaM","Pt of the probe, 1.479 #leq |#eta| < 2.5, passing LeptonMvaM",19,10,200);
  h_prbPt_Eta3_LeptonMvaVT = new TH1D("prbPt_Eta3_LeptonMvaVT","Pt of the probe, 1.479 #leq |#eta| < 2.5, passing LeptonMvaVT",19,10,200);
  h_prbPt_Eta3_LeptonMvaMIDEmuTightIP2DSIP3D8miniIso04 = new TH1D("prbPt_Eta3_LeptonMvaMIDEmuTightIP2DSIP3D8miniIso04","Pt of the probe, 1.479 #leq |#eta| < 2.5, passing LeptonMvaMIDEmuTightIP2DSIP3D8miniIso04",19,10,200);
  h_prbPt_Eta3_LeptonMvaVTIDEmuTightIP2DSIP3D8miniIso04 = new TH1D("prbPt_Eta3_LeptonMvaVTIDEmuTightIP2DSIP3D8miniIso04","Pt of the probe, 1.479 #leq |#eta| < 2.5, passing LeptonMvaVTIDEmuTightIP2DSIP3D8miniIso04",19,10,200);
  //-----------------------------------------------------------
  h_prbPtvBin = new TH1D("prbPtvBin","Pt of the probe",ptBins.size()-1,&(ptBins[0]));
 
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

