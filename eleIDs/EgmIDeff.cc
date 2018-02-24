#define EgmIDeff_cxx
#include "EgmIDeff.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char* argv[])
{

  if (argc < 2) {
    cerr << "Please give 3 arguments " << "runList " << " " << "outputFileName" << " " << "dataset" << endl;
    return -1;
  }
  const char *inputFileList = argv[1];
  const char *outFileName   = argv[2];
  const char *data          = argv[3];

  EgmIDeff ana(inputFileList, outFileName, data);
  cout << "dataset " << data << " " << endl;

  ana.EventLoop(data,inputFileList);

  return 0;
}

void EgmIDeff::EventLoop(const char *data,const char *inputFileList) {
  if (fChain == 0) return;

  Long64_t nentries = fChain->GetEntriesFast();
  cout << "nentries " << nentries << endl;
  cout << "Analyzing dataset " << data << " " << endl;
  Long64_t nbytes = 0, nb = 0;
  int decade = 0;

  TString s_data=data;
  bool mcSample=true, mcTruth=true, do_fakes=1;
  if(s_data.Contains("Data") || s_data.Contains("Run201") || s_data.Contains("data")) mcSample=false;    
  Long64_t evtSurvived=0;
  double wt=0;
  if(mcSample){
    cout<<"Taking it as MC........................."<<endl;
    if(do_fakes) cout<<"Calulating fakes.............."<<endl;
    else cout<<"Calculating eff......................"<<endl;
  }
  else cout<<"Taking it as data..................."<<endl;

  for (Long64_t jentry=0; jentry<nentries;jentry++) {

    // ==============print number of events done == == == == == == == =
    double progress = 10.0 * jentry / (1.0 * nentries);
    int k = int (progress);
    if (k > decade)
      cout << 10 * k << " %" <<endl;
    decade = k;
    // ===============read this entry == == == == == == == == == == == 

    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    wt = 1;
    if(wt!=1) cout<<wt<<" ";
    // if(mcTrue!=mc_probe_flag)
    //   printInfo(jentry);
    h_ZMass->Fill(pair_mass,wt);
    if(mcSample){
      if(do_fakes && mcTrue) continue;
      if(!do_fakes && !mcTrue) continue;
      mcTruth = mcTrue;
      h_prbPtmc->Fill(mc_probe_et,wt);
      h2_mcTrueVsdR->Fill(mcTrue,DeltaR(mc_probe_eta,mc_probe_phi, el_eta,el_phi), weight);
      h2_mcFlagVsdR->Fill(mc_probe_flag,DeltaR(mc_probe_eta,mc_probe_phi, el_eta,el_phi), weight);
    }
    h_prbPtvBin->Fill(el_pt,wt);

    bool isEB = (abs(el_eta) < 1.4442) ? true : false;
    
    if(isEB){
      h_prbPt_EB->Fill(el_pt,wt);
      //------------------ EGM ID ----------------
      if(passingLoose80X)	h_prbPt_EB_Loose80X->Fill(el_pt,wt);
      if(passingLoose94X)	h_prbPt_EB_Loose94X->Fill(el_pt,wt);
      if(passingMedium80X)	h_prbPt_EB_Medium80X->Fill(el_pt,wt);
      if(passingMedium94X)	h_prbPt_EB_Medium94X->Fill(el_pt,wt);
      if(passingTight80X)	h_prbPt_EB_Tight80X->Fill(el_pt,wt);
      if(passingTight94X)	h_prbPt_EB_Tight94X->Fill(el_pt,wt);
      //------------------ SUSY ID No Iso ----------------
      if(passingCutBasedVetoNoIso)    h_prbPt_EB_CutBasedVetoNoIso->Fill(el_pt,wt);
      if(passingCutBasedVetoNoIso94X)    h_prbPt_EB_CutBasedVetoNoIso94X->Fill(el_pt,wt);
      if(passingCutBasedLooseNoIso)    h_prbPt_EB_CutBasedLooseNoIso->Fill(el_pt,wt);
      if(passingCutBasedLooseNoIso94X)    h_prbPt_EB_CutBasedLooseNoIso94X->Fill(el_pt,wt);
      if(passingCutBasedMediumNoIso)    h_prbPt_EB_CutBasedMediumNoIso->Fill(el_pt,wt);
      if(passingCutBasedMediumNoIso94X)    h_prbPt_EB_CutBasedMediumNoIso94X->Fill(el_pt,wt);
      if(passingCutBasedTightNoIso)    h_prbPt_EB_CutBasedTightNoIso->Fill(el_pt,wt);
      if(passingCutBasedTightNoIso94X)    h_prbPt_EB_CutBasedTightNoIso94X->Fill(el_pt,wt);
    }
    else{
      h_prbPt_EE->Fill(el_pt,wt);
      //------------------ EGM ID ----------------
      if(passingLoose80X)	h_prbPt_EE_Loose80X->Fill(el_pt,wt);
      if(passingLoose94X)	h_prbPt_EE_Loose94X->Fill(el_pt,wt);
      if(passingMedium80X)	h_prbPt_EE_Medium80X->Fill(el_pt,wt);
      if(passingMedium94X)	h_prbPt_EE_Medium94X->Fill(el_pt,wt);
      if(passingTight80X)	h_prbPt_EE_Tight80X->Fill(el_pt,wt);
      if(passingTight94X)	h_prbPt_EE_Tight94X->Fill(el_pt,wt);
      //------------------ SUSY ID No Iso ----------------
      if(passingCutBasedVetoNoIso)    h_prbPt_EE_CutBasedVetoNoIso->Fill(el_pt,wt);
      if(passingCutBasedVetoNoIso94X)    h_prbPt_EE_CutBasedVetoNoIso94X->Fill(el_pt,wt);
      if(passingCutBasedLooseNoIso)    h_prbPt_EE_CutBasedLooseNoIso->Fill(el_pt,wt);
      if(passingCutBasedLooseNoIso94X)    h_prbPt_EE_CutBasedLooseNoIso94X->Fill(el_pt,wt);
      if(passingCutBasedMediumNoIso)    h_prbPt_EE_CutBasedMediumNoIso->Fill(el_pt,wt);
      if(passingCutBasedMediumNoIso94X)    h_prbPt_EE_CutBasedMediumNoIso94X->Fill(el_pt,wt);
      if(passingCutBasedTightNoIso)    h_prbPt_EE_CutBasedTightNoIso->Fill(el_pt,wt);
      if(passingCutBasedTightNoIso94X)    h_prbPt_EE_CutBasedTightNoIso94X->Fill(el_pt,wt);
    }
    
    if(el_pt >= 25){
      h_prbEta_Pt25->Fill(abs(el_eta),wt);
      //------------------ EGM ID ----------------
      if(passingLoose80X)  h_prbEta_Pt25_Loose80X->Fill(abs(el_eta),wt);
      if(passingLoose94X)  h_prbEta_Pt25_Loose94X->Fill(abs(el_eta),wt);
      if(passingMedium80X) h_prbEta_Pt25_Medium80X->Fill(abs(el_eta),wt);
      if(passingMedium94X) h_prbEta_Pt25_Medium94X->Fill(abs(el_eta),wt);
      if(passingTight80X)  h_prbEta_Pt25_Tight80X->Fill(abs(el_eta),wt);
      if(passingTight94X)  h_prbEta_Pt25_Tight94X->Fill(abs(el_eta),wt);
      //------------------ SUSY ID No Iso ----------------
      if(passingCutBasedVetoNoIso)     h_prbEta_Pt25_CutBasedVetoNoIso->Fill(abs(el_eta),wt);
      if(passingCutBasedVetoNoIso94X)  h_prbEta_Pt25_CutBasedVetoNoIso94X->Fill(abs(el_eta),wt);
      if(passingCutBasedLooseNoIso)    h_prbEta_Pt25_CutBasedLooseNoIso->Fill(abs(el_eta),wt);
      if(passingCutBasedLooseNoIso94X) h_prbEta_Pt25_CutBasedLooseNoIso94X->Fill(abs(el_eta),wt);
      if(passingCutBasedMediumNoIso)   h_prbEta_Pt25_CutBasedMediumNoIso->Fill(abs(el_eta),wt);
      if(passingCutBasedMediumNoIso94X)h_prbEta_Pt25_CutBasedMediumNoIso94X->Fill(abs(el_eta),wt);
      if(passingCutBasedTightNoIso)    h_prbEta_Pt25_CutBasedTightNoIso->Fill(abs(el_eta),wt);
      if(passingCutBasedTightNoIso94X) h_prbEta_Pt25_CutBasedTightNoIso94X->Fill(abs(el_eta),wt);
    }
    
    //----------------------- MVA IDs ----------------------
    if(abs(el_eta) < 0.8){
      h_prbPt_Eta1->Fill(el_pt,wt);
      if(passingMVA80Xwp80)   h_prbPt_Eta1_MVA80Xwp80->Fill(el_pt,wt);
      if(passingMVA80Xwp90)   h_prbPt_Eta1_MVA80Xwp90->Fill(el_pt,wt);
      if(passingMVAWP80)      h_prbPt_Eta1_MVAWP80->Fill(el_pt,wt);
      if(passingMVAWP90)      h_prbPt_Eta1_MVAWP90->Fill(el_pt,wt);
      if(passingLeptonMvaM)   h_prbPt_Eta1_LeptonMvaM->Fill(el_pt,wt);
      if(passingLeptonMvaVT)  h_prbPt_Eta1_LeptonMvaVT->Fill(el_pt,wt);
      if(passingLeptonMvaMIDEmuTightIP2DSIP3D8miniIso04)   h_prbPt_Eta1_LeptonMvaMIDEmuTightIP2DSIP3D8miniIso04->Fill(el_pt,wt);
      if(passingLeptonMvaVTIDEmuTightIP2DSIP3D8miniIso04)  h_prbPt_Eta1_LeptonMvaVTIDEmuTightIP2DSIP3D8miniIso04->Fill(el_pt,wt);
    }
    else if(abs(el_eta) >= 0.8 && abs(el_eta) < 1.479){
      h_prbPt_Eta2->Fill(el_pt,wt);
      if(passingMVA80Xwp80)   h_prbPt_Eta2_MVA80Xwp80->Fill(el_pt,wt);
      if(passingMVA80Xwp90)   h_prbPt_Eta2_MVA80Xwp90->Fill(el_pt,wt);
      if(passingMVAWP80)      h_prbPt_Eta2_MVAWP80->Fill(el_pt,wt);
      if(passingMVAWP90)      h_prbPt_Eta2_MVAWP90->Fill(el_pt,wt);
      if(passingLeptonMvaM)   h_prbPt_Eta2_LeptonMvaM->Fill(el_pt,wt);
      if(passingLeptonMvaVT)  h_prbPt_Eta2_LeptonMvaVT->Fill(el_pt,wt);
      if(passingLeptonMvaMIDEmuTightIP2DSIP3D8miniIso04)   h_prbPt_Eta2_LeptonMvaMIDEmuTightIP2DSIP3D8miniIso04->Fill(el_pt,wt);
      if(passingLeptonMvaVTIDEmuTightIP2DSIP3D8miniIso04)  h_prbPt_Eta2_LeptonMvaVTIDEmuTightIP2DSIP3D8miniIso04->Fill(el_pt,wt);
    }
    else if(abs(el_eta) >= 1.479 && abs(el_eta) < 2.4){
      h_prbPt_Eta3->Fill(el_pt,wt);
      if(passingMVA80Xwp80)   h_prbPt_Eta3_MVA80Xwp80->Fill(el_pt,wt);
      if(passingMVA80Xwp90)   h_prbPt_Eta3_MVA80Xwp90->Fill(el_pt,wt);
      if(passingMVAWP80)      h_prbPt_Eta3_MVAWP80->Fill(el_pt,wt);
      if(passingMVAWP90)      h_prbPt_Eta3_MVAWP90->Fill(el_pt,wt);
      if(passingLeptonMvaM)   h_prbPt_Eta3_LeptonMvaM->Fill(el_pt,wt);
      if(passingLeptonMvaVT)  h_prbPt_Eta3_LeptonMvaVT->Fill(el_pt,wt);
      if(passingLeptonMvaMIDEmuTightIP2DSIP3D8miniIso04)   h_prbPt_Eta3_LeptonMvaMIDEmuTightIP2DSIP3D8miniIso04->Fill(el_pt,wt);
      if(passingLeptonMvaVTIDEmuTightIP2DSIP3D8miniIso04)  h_prbPt_Eta3_LeptonMvaVTIDEmuTightIP2DSIP3D8miniIso04->Fill(el_pt,wt);
    }
    
    evtSurvived++;
  } // loop over entries
  cout<<"Events Survied:"<<evtSurvived<<endl;
}

void EgmIDeff::printInfo(Long64_t jentry){
  cout<<"-------------------------------------------------------"<<endl;
  cout<<"run: "<<run<<" lumi: "<<lumi<<" event: "<<event<<endl;
  cout<<"el_pt: "<<el_pt<<" el_eta: "<<el_eta<<" el_phi: "<<el_phi<<" el_e: "<<el_e<<endl;
  cout<<"tag_Ele_pt: "<<tag_Ele_pt<<" tag_Ele_eta: "<<tag_Ele_eta<<" tag_Ele_phi: "<<tag_Ele_phi<<" tag_Ele_e: "<<tag_Ele_e<<endl;
  cout<<"mc_probe_flag "<<mc_probe_flag<<" mc_probe_et: "<<mc_probe_et<<" mc_probe_eta: "<<mc_probe_eta<<" mc_probe_phi: "<<mc_probe_phi<<" mc_probe_e: "<<mc_probe_e<<endl;
  cout<<endl;
  cout<<"mcTrue: "<<mcTrue<<" mcMass: "<<mcMass<<" pair_mass: "<<pair_mass<<" mass: "<<mass<<endl;  
}
