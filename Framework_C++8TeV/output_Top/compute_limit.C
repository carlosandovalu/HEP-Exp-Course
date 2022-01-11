#include "include/AtlasStyle.C"
#include "include/AtlasLabels.C"
#include "include/AtlasUtils.C"

#include <iostream>
#include <TRandom3.h>
#include <TFeldmanCousins.h>
#include <TH1F.h>
#include <TString.h>

using namespace std;

bool logy = true;

int compute_limit () 
{

  SetAtlasStyle();
  TH1::SetDefaultSumw2(true);
  gROOT->Reset();

  //Sample names
  string samples[11] = {"Z400","Z500","Z750","Z1000","Z1250","Z1500","Z1750","Z2000","Z2250","Z2500","Z3000"};


  //These are the number of expected and background events
  //number of signal events after WmT >30 GeV cut
  double sig[11] = {0,0,0,0,0,0,0,0,0,0,0};
  // SM MC events after WmT > 30 GeV
  double bkg[11] = {0,0,0,0,0,0,0,0,0,0,0};
  // Number of observed events
  double obs[11] = {0,0,0,0,0,0,0,0,0,0,0};


  //Signal cross sections
  double xsec[11] =  {4.2589, 3.925, 1.243, 0.3937, 0.1387, 0.0524, 0.0211, 0.00894, 0.00394, 0.0018, 0.000434};

  // Limit canculator configuration
  int n_trials = 1000;
  TRandom3 r;
  TFeldmanCousins limit_eval(0.95);
  cout << "trials " << n_trials << endl;

  TH1F *hlimit[11], *hextraction[11];
  double mean=0.;
  double  err=0;

  // arrays that would go into thee TGraph
  // 
  double mass[11] = {400, 500, 750, 1000, 1250, 1500, 1750, 2000, 2250, 2500, 3000};
  double xsec_limit[11];
  double obs_xsec_limit[11];

  /////////////  /////////////  /////////////  /////////////
  //Calculation of the limit for all samples happends here
  for(int isam=0; isam<11;isam++) 
    {
      hlimit[isam] = new TH1F((samples[isam]+"_limit").c_str(),"Upper limit histo",2000,0.,200);
      hextraction[isam] = new TH1F((samples[isam]+"_extr").c_str(),"Extraction histo",2000,0.,200);
      
      if(bkg[isam]<10)
	{
	  for (int i=0; i<n_trials; i++) 
	    {
	      if(i%100==0) cout << "trial " << i << endl;
	      double extraction = r.Poisson(bkg[isam]);
	      hextraction[isam]->Fill(extraction);
	      double limit = limit_eval.CalculateUpperLimit(extraction, bkg[isam]);
	      hlimit[isam]->Fill(limit);   
	    }//end loop over n_trials
	  mean=hlimit[isam]->GetMean();
	  err=hlimit[isam]->GetStdDev();
	}
      else 
	{
	  mean  = 1.64*sqrt(bkg[isam]);
	  //mean  = 1.64*sqrt(bkg[isam]+0.15*0.15*bkg[isam]*bkg[isam]);
	  //mean  = 1.64*sqrt(bkg[isam]+0.50*0.50*bkg[isam]*bkg[isam]);
	  err =0;
	}
      
      xsec_limit[isam] = mean/sig[isam]*xsec[isam];
      
      cout << "Upper cross section limit for sample " << samples[isam] << endl;
      //cout << " mean " << mean << " +/- " << err << endl;
      //cout << " mu " << mean/sig[isam] << " +/- " << err/sig[isam] << endl;
      cout << " xsec " << mean/sig[isam]*xsec[isam] << " +/- " << err/sig[isam]*xsec[isam] << " pb" << endl;
      cout << " ************************************************ " << endl; 
    }//end loop over isam
  /////////////  /////////////  /////////////  /////////////
  /////////////  /////////////  /////////////  /////////////

  /////////////  /////////////  /////////////  /////////////
  //Calculation of the limit for all samples happens here
  for(int isam=0; isam<11;isam++) 
    {
      hlimit[isam] = new TH1F((samples[isam]+"_obs_limit").c_str(),"Upper limit histo",2000,0.,200);
      hextraction[isam] = new TH1F((samples[isam]+"_obs_extr").c_str(),"Extraction histo",2000,0.,200);
      
      if(obs[isam]<10)
	{
	  for (int i=0; i<n_trials; i++) 
	    {
	      if(i%100==0) cout << "trial " << i << endl;
	      double extraction = r.Poisson(obs[isam]);
	      hextraction[isam]->Fill(extraction);
	      double limit = limit_eval.CalculateUpperLimit(extraction, obs[isam]);
	      hlimit[isam]->Fill(limit);   
	    }//end loop over n_trials
	  mean=hlimit[isam]->GetMean();
	  err=hlimit[isam]->GetStdDev();
	}
      else 
	{
	  mean  = 1.64*sqrt(obs[isam]);
	  //mean  = 1.64*sqrt(obs[isam]+0.15*0.15*obs[isam]*obs[isam]);
	  //mean  = 1.64*sqrt(obs[isam]+0.50*0.50*obs[isam]*obs[isam]);
	  err =0;
	}
      
      obs_xsec_limit[isam] = mean/sig[isam]*xsec[isam];
      
      cout << "Upper cross section limit for sample " << samples[isam] << endl;
      //cout << " mean " << mean << " +/- " << err << endl;
      //cout << " mu " << mean/sig[isam] << " +/- " << err/sig[isam] << endl;
      cout << " xsec " << mean/sig[isam]*xsec[isam] << " +/- " << err/sig[isam]*xsec[isam] << " pb" << endl;
      cout << " ************************************************ " << endl; 
    }//end loop over isam
  /////////////  /////////////  /////////////  /////////////
  /////////////  /////////////  /////////////  /////////////
  

  TCanvas *can = new TCanvas("can","",600,600);
  can->cd(0);
  if(logy) can->SetLogy();
  
  TMultiGraph *limit_plot = new TMultiGraph();
  limit_plot->SetTitle(";m_{Z'}   [GeV];Upper limit on #sigma(Z'#rightarrowt#bar{t}) [pb]");
  //expected limit
  TGraph *my_lim = new TGraph(11, mass, xsec_limit);
  //observed limit
  TGraph *my_lim_obs = new TGraph(11, mass, obs_xsec_limit);
  //theory cross ection
  //  TGraph *theory_xsec = new TGraph(11, mass, xsec);  
  limit_plot->Add(my_lim);
  my_lim->SetLineStyle(7);
  my_lim->SetLineWidth(2);
  my_lim->SetLineColor(kBlue);
  limit_plot->Add(my_lim_obs);
  my_lim_obs->SetLineWidth(2);
  //limit_plot->Add(theory_xsec);
  //theory_xsec->SetLineWidth(2);
  //theory_xsec->SetLineColor(kRed);
  
  limit_plot->Draw("AL");

  
  TLegend *leg = new TLegend(0.55, 0.7, 0.75, 0.9);
  leg->SetBorderSize(0);
  leg->SetTextFont(42);
  leg->SetTextSize(0.035);
  leg->SetLineColor(1);
  leg->SetLineStyle(1);
  leg->SetLineWidth(1);
  leg->SetFillColor(0);
  leg->SetFillStyle(1001);
  leg->SetHeader("     #sqrt{s} = 8 TeV, 1 fb^{-1}");
  leg->AddEntry(my_lim_obs,"Observed","l");
  leg->AddEntry(my_lim,"Expected","l");
  //leg->AddEntry(theory_xsec,"Theory #sigma(Z'#rightarrowt#bar{t})","l");
  leg->Draw();

  can->SaveAs("XsecLimit.pdf");
  
  return 0;
  
}

