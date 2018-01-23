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

  string s_data=data;
  bool mcSample=true;
  if(s_data=="Data") mcSample=false;    
  Long64_t nbytes = 0, nb = 0;
  int decade = 0;
  bool doEff = 0; 
  int evtSurvived=0;
  double wt=0;
  if(doEff) cout<<"Getting efficiency"<<endl;
  else cout<<"Getting fakerate"<<endl;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {

    // ==============print number of events done == == == == == == == =
    double progress = 10.0 * jentry / (1.0 * nentries);
    int k = int (progress);
    if (k > decade)
      cout << 10 * k << " %" <<endl;
    decade = k;
    // cout<<"j:"<<jentry<<" fcurrent:"<<fCurrent<<endl;
    // ===============read this entry == == == == == == == == == == == 
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    wt = 1;
    // if(mcTrue!=mc_probe_flag)
    //   printInfo(jentry);
    //  if(jentry>1000000) break;
    if(wt!=1) cout<<wt<<" ";
    h_ZMass->Fill(pair_mass,wt);
    h_prbPtmc->Fill(mc_probe_et,wt);
    h2_mcTrueVsdR->Fill(mcTrue,DeltaR(mc_probe_eta,mc_probe_phi, el_eta,el_phi), weight);
    h2_mcFlagVsdR->Fill(mc_probe_flag,DeltaR(mc_probe_eta,mc_probe_phi, el_eta,el_phi), weight);

    if(doEff && !mcTrue) continue;
    if(!doEff && mcTrue) continue;

    h_prbPt->Fill(el_pt,wt);
    h_prbPtvBin->Fill(el_pt,wt);
    if(passingLoose80X){
      h_prbPt_Loose80X->Fill(el_pt,wt);
      h_prbPt_Loose80XvBin->Fill(el_pt,wt);
    }
    if(passingLoose94X){
      h_prbPt_Loose94X->Fill(el_pt,wt);
      h_prbPt_Loose94XvBin->Fill(el_pt,wt);
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
