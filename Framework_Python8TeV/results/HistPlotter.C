#include "include/AtlasStyle.C"
#include "include/AtlasLabels.C"
#include "include/AtlasUtils.C"


void groupSamples();
void makeGroupHist();

std::map<TString, float> db;
std::map<TString, float> dy;
std::map<TString, float> w;
std::map<TString, float> z;
std::map<TString, float> stop;
std::map<TString, float> tt;
std::map<TString, float> signalmap;

TH1F *h_db;
TH1F *h_drellyan;
TH1F *h_wjets;
TH1F *h_zjets;
TH1F *h_singletop;
TH1F *h_ttbar;

std::string histname = "etmiss";
float lumi = 1000.;
//int rebin = 20; //20 - ZmInv //4 - wmt //1 - event selection
bool logy = true;
std::string signalmass = "2000";

void HistPlotter(){

  SetAtlasStyle();
  TH1::SetDefaultSumw2(true);
  gROOT->Reset();

  groupSamples();
  makeGroupHist();

  THStack *h_stack = new THStack("h_stack","");

  h_db->SetFillColor(kRed);
  h_drellyan->SetFillColor(kGreen);
  h_wjets->SetFillColor(kMagenta);
  h_zjets->SetFillColor(kBlue);
  h_singletop->SetFillColor(kOrange);
  h_ttbar->SetFillColor(kCyan);

  h_stack->Add(h_db);
  h_stack->Add(h_drellyan);
  h_stack->Add(h_wjets);
  h_stack->Add(h_zjets);
  h_stack->Add(h_singletop);
  h_stack->Add(h_ttbar);

  TH1F *h_err = (TH1F*) h_db->Clone();
  h_err->Add(h_drellyan);
  h_err->Add(h_wjets);
  h_err->Add(h_zjets);
  h_err->Add(h_singletop);
  h_err->Add(h_ttbar);
  h_err->SetFillStyle(3004);
  h_err->SetFillColor(kBlack);
  h_err->SetLineColor(0);
  h_err->SetMarkerStyle(1);


  TFile *f_sig = TFile::Open(("ZPrime" + signalmass + ".root").c_str());
  TH1F* h_signal = (TH1F*) f_sig->Get(histname.c_str());
  //h_signal->Rebin(rebin);
  //Rescale signal
  h_signal->Scale(1e3*lumi*signalmap[("ZPrime" + signalmass).c_str()]);
  h_signal->SetLineStyle(7);
  h_signal->SetLineWidth(3);
  h_signal->SetLineColor(kPink-8);


  TFile *f_egamma = TFile::Open("data_Egamma.root");
  TFile *f_muon = TFile::Open("data_Muons.root");
  TH1F *h_data_egamma = (TH1F*) f_egamma->Get(histname.c_str());
  TH1F *h_data_muon = (TH1F*) f_muon->Get(histname.c_str());
  //h_data_egamma->Rebin(rebin);
  // h_data_muon->Rebin(rebin);

  TH1F *h_data = (TH1F*) h_data_egamma->Clone();
  h_data->Add(h_data_muon);
  h_data->SetMarkerSize(1);
  h_data->SetMarkerStyle(20);
  h_data->SetMarkerColor(kBlack);

  /// Chi2
  //double chi2_test = h_data->Chi2Test(h_err, "UW,P");
  //cout<<"chi2_test  "<<chi2_test<<endl;



  ///// Plotting
  TCanvas *can = new TCanvas("can","", 600, 600);
  can->cd();
  if(logy) can->SetLogy();


  h_stack->Draw("hist");
  h_err->Draw("e2same");
  h_data->Draw("epsame");
  //  h_signal->Draw("histsame");
   h_stack->SetMaximum(20*h_stack->GetMaximum());
  if (logy && histname.find("event_selection") != std::string::npos) h_stack->SetMinimum(10000);
  //else if(logy) h_stack->SetMinimum(0.5);

  h_stack->GetXaxis()->SetTitle(h_data_egamma->GetXaxis()->GetTitle());
  h_stack->GetYaxis()->SetTitle("Events");
  h_stack->GetYaxis()->SetTitleOffset(1.60);
  if(histname.find("WtMass") != std::string::npos)h_stack->GetXaxis()->SetRangeUser(0, 500.);
  else if(histname.find("ZmInv") != std::string::npos)h_stack->GetXaxis()->SetRangeUser(0, 3775);
  else if(histname.find("ZmT") != std::string::npos)h_stack->GetXaxis()->SetRangeUser(0, 3575);
  else if(histname.find("lep_pt") != std::string::npos)h_stack->GetXaxis()->SetRangeUser(0, 1575);



  TLegend *leg = new TLegend(0.55, 0.55, 0.75, 0.9);
  leg->SetBorderSize(0);
  leg->SetTextFont(42);
  leg->SetTextSize(0.035);
  leg->SetLineColor(1);
  leg->SetLineStyle(1);
  leg->SetLineWidth(1);
  leg->SetFillColor(0);
  leg->SetFillStyle(1001);
  leg->SetHeader("     #sqrt{s} = 8 TeV, 1 fb^{-1}");
  leg->AddEntry(h_data,"Data","p");
  leg->AddEntry(h_ttbar,"t#bar{t}","f");
  leg->AddEntry(h_singletop,"Single top","f");
  leg->AddEntry(h_zjets,"Z","f");
  leg->AddEntry(h_wjets,"W","f");
  leg->AddEntry(h_drellyan,"Drell-Yan","f");
  leg->AddEntry(h_db,"Diboson","f");
  leg->AddEntry(h_err,"MC stat. uncertainty","f");
  // leg->AddEntry(h_signal,("Z'(" + signalmass + " GeV)#rightarrow t#bar{t} x 10^{3}").c_str(),"l");
  leg->Draw();

  std::string outfile = histname.substr(0, std::string::npos);
  if(logy) can->SaveAs((outfile+"_log.pdf").c_str());
  else can->SaveAs((outfile+".pdf").c_str());
}

void groupSamples(){

  std::ifstream samples;
  samples.open("samples.txt");
  
  while(!samples.eof()){
    TString sample;
    float xsec;
    float red_eff;
    float sumw;
    float nevt;

    samples >> sample >> xsec >> red_eff >> sumw >> nevt;

    nevt=1;
    //sumw=1;
    if(sample.Contains("WW")  || sample.Contains("WZ")  || sample.Contains("ZZ")  ) db[sample] = xsec*nevt/(red_eff*sumw); 

    if(sample.Contains("DY")  ) dy[sample] = xsec*nevt/(red_eff*sumw);

    if(sample.Contains("Wenu")  || sample.Contains("Wmunu")  || sample.Contains("Wtaunu")  ) w[sample] = xsec*nevt/(red_eff*sumw); 

    if(sample.Contains("Zee")  || sample.Contains("Zmumu")  || sample.Contains("Ztautau")  ) z[sample] = xsec*nevt/(red_eff*sumw); 

    if(sample.Contains("stop")  ) stop[sample] = xsec*nevt/(red_eff*sumw);

    if(sample.Contains("ttbar")  ) tt[sample] = xsec*nevt/(red_eff*sumw);

    if(sample.Contains("ZPrime")  ) signalmap[sample] = xsec*nevt/(red_eff*sumw);


  }


  return;
}

void makeGroupHist(){

  //for(unsigned int i = 0; i < db.size(); i++){
  int i = 0;
  for(std::map<TString, float>::iterator it = db.begin(); it != db.end(); ++it){
    TFile *f = TFile::Open(Form("%s.root",(it->first).Data()));
    TH1F *h = (TH1F*) f->Get(histname.c_str());    
    //h->Rebin(rebin);
    h->Scale(it->second*lumi);
    //h->Scale(it->second*lumi/h->Integral(0, h->GetNbinsX()+1));
    if(i==0) h_db = (TH1F*) h->Clone();
    else h_db->Add(h);
    i++;
  }

  i = 0;
  for(std::map<TString, float>::iterator it = dy.begin(); it != dy.end(); ++it){
    TFile *f = TFile::Open(Form("%s.root",(it->first).Data()));
    TH1F *h = (TH1F*) f->Get(histname.c_str());    
    //h->Rebin(rebin);
    h->Scale(it->second*lumi);
    //h->Scale(it->second*lumi/h->Integral(0, h->GetNbinsX()+1));
    if(i==0) h_drellyan = (TH1F*) h->Clone();
    else h_drellyan->Add(h);
    i++;
  }

  i = 0;
  for(std::map<TString, float>::iterator it = w.begin(); it != w.end(); ++it){
    TFile *f = TFile::Open(Form("%s.root",(it->first).Data()));
    TH1F *h = (TH1F*) f->Get(histname.c_str());    
    //h->Rebin(rebin);
    h->Scale(it->second*lumi);
    //h->Scale(it->second*lumi/h->Integral(0, h->GetNbinsX()+1));
    if(i==0) h_wjets = (TH1F*) h->Clone();
    else h_wjets->Add(h);
    i++;
  }

  i = 0;
  for(std::map<TString, float>::iterator it = z.begin(); it != z.end(); ++it){
    TFile *f = TFile::Open(Form("%s.root",(it->first).Data()));
    TH1F *h = (TH1F*) f->Get(histname.c_str());    
    //h->Rebin(rebin);
    h->Scale(it->second*lumi);
    //h->Scale(it->second*lumi/h->Integral(0, h->GetNbinsX()+1));
    if(i==0) h_zjets = (TH1F*) h->Clone();
    else h_zjets->Add(h);
    i++;
  }

  i = 0;
  for(std::map<TString, float>::iterator it = stop.begin(); it != stop.end(); ++it){
    TFile *f = TFile::Open(Form("%s.root",(it->first).Data()));
    TH1F *h = (TH1F*) f->Get(histname.c_str());    
    //h->Rebin(rebin);
    h->Scale(it->second*lumi);
    //h->Scale(it->second*lumi/h->Integral(0, h->GetNbinsX()+1));
    if(i==0) h_singletop = (TH1F*) h->Clone();
    else h_singletop->Add(h);
    i++;
  }

  i = 0;
  for(std::map<TString, float>::iterator it = tt.begin(); it != tt.end(); ++it){
    TFile *f = TFile::Open(Form("%s.root",(it->first).Data()));
    TH1F *h = (TH1F*) f->Get(histname.c_str());    
    //h->Rebin(rebin);
    h->Scale(it->second*lumi);
    //h->Scale(it->second*lumi/h->Integral(0, h->GetNbinsX()+1));
    if(i==0) h_ttbar = (TH1F*) h->Clone();
    else h_ttbar->Add(h);
    i++;
  }

}
