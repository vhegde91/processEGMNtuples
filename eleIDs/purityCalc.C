void purityCalc(){
  vector<double> den;
  vector<double> num;

  vector<double> denErr;
  vector<double> numErr;
  
  TFile *f1=new TFile("data.root");
  TH1D *hP,*hF;
  TString passName,failName;
  double val=0,err=0;
  int k=0;
  for(int i=20;i<=29;i++){
    passName="ZMass_Mini4P_bin"+to_string(i);
    failName="ZMass_Mini4F_bin"+to_string(i);
    hP=(TH1D*)f1->Get(passName);
    hF=(TH1D*)f1->Get(failName);
    val=hP->IntegralAndError(hP->FindBin(80.001),hP->FindBin(99.99),err);
    num.push_back(val);
    numErr.push_back(err);
    val=num[i-20]+hF->IntegralAndError(hF->FindBin(80.001),hF->FindBin(99.99),err);
    den.push_back(val);
    denErr.push_back(sqrt(val));
  }
  
  TH1D *hNum=new TH1D("hNum","hNum",20,0.5,20.5);
  TH1D *hDen=new TH1D("hDen","hDen",20,0.5,20.5);
  for(int i=0;i<den.size();i++){
    hNum->SetBinContent(i+1,num[i]);
    hNum->SetBinError(i+1,numErr[i]);
    hDen->SetBinContent(i+1,den[i]);
    hDen->SetBinError(i+1,denErr[i]);
  }

  TGraphAsymmErrors *gr = new TGraphAsymmErrors(hNum,hDen);
  gr->Draw();
  gr->Print("ALL");
  cout<<"================"<<endl;

  for(int i=0;i<den.size();i++){
    cout<<"bin_"<<i+20<<" "<<(gr->GetY())[i]<<" +/- "<<0.5*(gr->GetErrorYhigh(i)+gr->GetErrorYlow(i))<<endl;
    //    cout<<gr->GetXaxis()->GetBinCenter(i)<<endl;
    //cout<<"Den: "<<den[i]<<" Num: "<<num[i]<<endl;
  }
  
}
