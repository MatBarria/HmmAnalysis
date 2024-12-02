//C++
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
//ROOT
#include <TTree.h>
#include <TFile.h>
#include <TString.h>
#include <TCanvas.h>
#include <TLatex.h>
#include <TStyle.h>
#include <TAxis.h>
#include <TF1.h>
//RooFit
#include <RooRealVar.h>
#include <RooWorkspace.h>
#include <RooDataSet.h>
#include <RooPlot.h>
#include <RooGaussian.h>
//LOCAL
#include "PlotBias.hh"
#include "HggAux.hh"

const float lumi = 2.3;
//Axis
const float axisTitleSize = 0.06;
const float axisTitleOffset = .8;

const float axisTitleSizeRatioX   = 0.18;
const float axisLabelSizeRatioX   = 0.12;
const float axisTitleOffsetRatioX = 0.84;

const float axisTitleSizeRatioY   = 0.15;
const float axisLabelSizeRatioY   = 0.108;
const float axisTitleOffsetRatioY = 0.32;

//Margins
const float leftMargin   = 0.12;
const float rightMargin  = 0.05;
const float topMargin    = 0.07;
const float bottomMargin = 0.12;

//CMS STANDARD
TString CMSText = "CMS";
TString extraText   = "Preliminary";
TString lumiText = "2.3 fb^{-1} (13 TeV)";

float lumix = 0.955;
float lumiy = 0.945;
float lumifont = 42;

float cmsx = 0.28;
float cmsy = 0.875;
float cmsTextFont   = 61;  // default is helvetic-bold
float extrax = cmsx + 0.078;
float extray = cmsy - 0.04;
float extraTextFont = 52;  // default is helvetica-italics
// ratio of "CMS" and extra text size
float extraOverCmsTextSize  = 0.76;
float cmsSize = 0.06;

void PlotSignalModel( std::string fname = "", std::string outDir = "SignalFitPlots")
{
  //-----------------------
  //G e t t i n g   F i l e
  //-----------------------
  TFile* f = new TFile( fname.c_str() , "READ" );
  //Getting Workspace
  RooWorkspace* w = (RooWorkspace*)f->Get("w_sFit");
  //Getting bias RooRealVar
  RooRealVar* _mu1    = w->var("dGauss_signal_DGF_mu1");
  RooRealVar* _mu2    = w->var("dGauss_signal_DGF_mu2");
  RooRealVar* _sigma1 = w->var("dGauss_signal_DGF_sigma1");
  RooRealVar* _sigma2 = w->var("dGauss_signal_DGF_sigma2");
  RooRealVar* _frac   = w->var("dGauss_signal_DGF_frac");
  RooRealVar* _Ns   = w->var("dGauss_signal_DGF_Ns");

  RooRealVar* mgg = w->var("mGammaGamma");
  mgg->setRange( "signal", 103, 160. );
  RooDataSet* data = (RooDataSet*)w->obj("data");
  //Getting RooPlot
  RooPlot* plot = (RooPlot*)w->obj("dGauss_signal_DGF_ext_frame");
  //Getting individual gaussian;
  RooGaussian* g1 = (RooGaussian*)w->obj("dGauss_signal_DGF1");
  RooGaussian* g2 = (RooGaussian*)w->obj("dGauss_signal_DGF2");
  RooAbsPdf* ge = (RooAbsPdf*)w->obj("dGauss_signal_DGF_ext");
  
  //---------------------------------
  //S e t t i n g   u p   C a n v a s 
  //---------------------------------
  TCanvas* c = new TCanvas( "c", "c", 2119, 33, 800, 700 );
  c->SetHighLightColor(2);
  c->SetFillColor(0);
  c->SetBorderMode(0);
  c->SetBorderSize(2);
  c->SetLeftMargin( leftMargin );
  c->SetRightMargin( rightMargin );
  c->SetTopMargin( topMargin );
  c->SetBottomMargin( bottomMargin );
  c->SetFrameBorderMode(0);
  c->SetFrameBorderMode(0);

  gStyle->SetPaintTextFormat("4.3f");

  /*
  plot->SetTitle("");
  plot->GetXaxis()->SetTitleSize( axisTitleSize );
  plot->GetXaxis()->SetTitleOffset( axisTitleOffset );
  plot->GetYaxis()->SetTitleSize( axisTitleSize );
  plot->GetYaxis()->SetTitleOffset( axisTitleOffset );
  */
  //plot->Draw();
  
  RooPlot* frame = mgg->frame();
  frame->SetTitle("");
  frame->GetXaxis()->SetTitleSize( axisTitleSize );
  frame->GetXaxis()->SetTitleOffset( axisTitleOffset );
  frame->GetYaxis()->SetTitleSize( axisTitleSize );
  frame->GetYaxis()->SetTitleOffset( axisTitleOffset );
  data->plotOn(frame);
  ge->plotOn( frame, RooFit::LineColor( kRed ), RooFit::Components( RooArgSet(*g1) ), RooFit::Range("signal"), RooFit::NormRange("signal") );
  ge->plotOn( frame, RooFit::LineColor( kGreen ), RooFit::Components( RooArgSet(*g2) ), RooFit::Range("signal"), RooFit::NormRange("signal") );
  ge->plotOn( frame, RooFit::LineColor( kBlue ), RooFit::Range("signal"), RooFit::NormRange("signal") );
  frame->Draw();
  //------------------------------
  //P l ot  M e a n  a n d   R m s 
  //------------------------------

  TString s_mu1    = Form("#mu_{1} = %.2f GeV", _mu1->getVal() );
  TString s_mu2    = Form("#mu_{2} = %.2f GeV", _mu2->getVal() );
  TString s_sigma1 = Form("#sigma_{1} = %.2f GeV", _sigma1->getVal() );
  TString s_sigma2 = Form("#sigma_{2} = %.2f GeV", _sigma2->getVal() );
  TString s_frac   = Form("#it{f} = %.2f ", _frac->getVal() );
  
  
  
  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);    
  latex.SetTextFont(42);
  latex.SetTextAlign(31); 
  latex.SetTextSize(0.04);    
  latex.DrawLatex( 0.9, 0.87, s_mu1 );
  latex.DrawLatex( 0.865, 0.87-0.06, s_sigma1 );
  latex.DrawLatex( 0.9, 0.87-2*0.06, s_mu2 );
  latex.DrawLatex( 0.865, 0.87-3*0.06, s_sigma2 );
  latex.DrawLatex( 0.805, 0.87-4*0.06, s_frac );
  
  //-----------------------
  //S a v i n g   P l o t s
  //-----------------------
  //std::string outName = fname;
  std::string findName = "/";
  int begin_s = fname.find( findName ) + findName.size();
  //int begin_s = 0;
  int end_s   = fname.find( ".root" );
  std::cout << "outDir: " << outDir << std::endl;
  std::string outName = outDir + "/" +fname.substr( begin_s, end_s - begin_s);
  TString figName = outName;
  std::cout << "figName: " << figName << std::endl;
  c->SaveAs(figName+".pdf");
  c->SaveAs(figName+".png");
  c->SaveAs(figName+".C");
  delete c;
  return;
};
