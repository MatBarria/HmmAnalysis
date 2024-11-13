#include <iostream>
#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TF1.h>
#include <TLatex.h>
#include <TDirectory.h>
#include <TCanvas.h>

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

void PlotSigInt( TString fname )
{
  TFile* f = new TFile( fname, "READ");
  assert( f );
  TTree* tree = (TTree*)f->Get("biasTree");
  tree->Draw("sigInt_hat>>tmp1(100, 0., 7.)", "", "goff");
  TH1F* h = (TH1F*)gDirectory->Get("tmp1");
  TF1* myF = new TF1("myF", "[0]*( [4]*exp( -(x-[1])*(x-[1])/(2*[2]*[2]) ) + (1-[4])*exp( -(x-[1])*(x-[1])/(2*[3]*[3]) ) )", 1.5, 6.);
  myF->SetParameter(0, 300 );
  myF->SetParameter(1, h->GetMean() );
  myF->SetParameter(2, h->GetStdDev() );
  myF->SetParameter(3, 3*h->GetStdDev() );
  myF->SetParameter(4, 0.9 );
  
  h->Fit( myF, "LR");
  h->Draw();
  return;
};

void PlotSigIntBias( TString fname , float ntrue = 1.)
{
  TFile* f = new TFile( fname, "READ");
  assert( f );
  std::cout << "ntrue: " << ntrue << std::endl;
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

  TTree* tree = (TTree*)f->Get("biasTree");
  TString drawCommand = Form("sigInt_hat/(%f*sigInt_true/n_true) - 1.0 >>tmp1(32, -2, 2)", ntrue);
  tree->Draw( drawCommand, "", "goff");
  TH1F* h = (TH1F*)gDirectory->Get("tmp1");
  /*
  TF1* myF = new TF1("myF", "[0]*exp( -(x-[1])*(x-[1])/(2*[2]*[2]) ) + [4]*exp( -(x-[5])*(x-[5])/(2*[3]*[3]) )", -2., 2.);
  myF->SetParameter(0, 300 );
  myF->SetParameter(1, h->GetMean() );
  myF->SetParameter(5, h->GetMean() );
  myF->SetParameter(2, h->GetStdDev() );
  myF->SetParameter(3, 3*h->GetStdDev() );
  myF->SetParameter(4, 50 );
  
  myF->SetParLimits(2, 0.0, 999);
  myF->SetParLimits(3, 0.0, 999);
  */
  
  TF1* myF = new TF1("myF", "[0]*exp( -(x-[1])*(x-[1])/(2*[2]*[2]) )", -2., 2.);
  myF->SetParameter(0, 300 );
  myF->SetParameter(1, h->GetMean() );
  myF->SetParameter(2, h->GetStdDev() );
  
  h->Fit( myF, "LR");
  h->SetMarkerStyle(20);
  h->SetMarkerSize(1.);
  h->SetMarkerColor(kBlack);
  h->SetLineColor(kBlack);

  //cosmetics
  h->SetStats(0);
  h->SetTitle("");
  h->GetXaxis()->SetTitleSize(0.05);
  h->GetXaxis()->SetTitleOffset(0.8);
  h->GetXaxis()->SetTitleSize( axisTitleSize );
  h->GetXaxis()->SetTitleOffset( axisTitleOffset );
  h->GetYaxis()->SetTitleSize( axisTitleSize );
  h->GetYaxis()->SetTitleOffset( axisTitleOffset );
  h->SetXTitle("Int/Int_{0} - 1");

  h->Draw("E");
  
  TString _mu    = Form("%.1f", 100.0*myF->GetParameter(1) );
  TString _sigma = Form("%.1f", 100.0*myF->GetParameter(2) );
  TLatex tex2;
  tex2.SetNDC();
  tex2.SetTextFont(52);
  tex2.SetTextAlign(31);
  tex2.SetTextSize(0.05);
  tex2.DrawLatex( 0.89, 0.88, "#mu = " + _mu + " %");
  tex2.DrawLatex( 0.90, 0.80, "#sigma = " + _sigma + " %");

  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);    
  float extraTextSize = extraOverCmsTextSize*cmsSize;
  latex.SetTextFont(lumifont);
  latex.SetTextAlign(31); 
  latex.SetTextSize(cmsSize);    
  latex.DrawLatex(lumix, lumiy,lumiText);

  latex.SetTextFont(cmsTextFont);
  latex.SetTextAlign(31); 
  latex.SetTextSize(cmsSize);
  latex.DrawLatex(cmsx, cmsy, CMSText);
   
  latex.SetTextFont(extraTextFont);
  latex.SetTextAlign(31); 
  latex.SetTextSize(extraTextSize);
  latex.DrawLatex(extrax, extray, extraText);
  
  TString outName = Form( "IntegralBias_FullFit_n%d", (int)ntrue );
  c->SaveAs(outName + ".pdf");
  c->SaveAs(outName + ".png");
  c->SaveAs(outName + ".C");
  return;
};
