#ifndef RunTwoFitMgg_HH
#define RunTwoFitMgg_HH
// C++ INCLUDES
#include <sstream>
#include <string>
// ROOT INCLUDES
#include <TString.h>
#include <TTree.h>
// ROOFIT INCLUDES
#include <RooAbsPdf.h>
#include <RooDataSet.h>
#include <RooRealVar.h>
#include <RooWorkspace.h>
// LOCAL INCLUDES

RooWorkspace *DoubleGausFit(TTree *tree, float forceSigma, bool sameMu,
                            float forceMu, TString mggName);
//RooWorkspace *DoubleCBFit(TTree *tree, TString mggName, float muCB = 125.,
void DoubleCBFit(TTree *tree, RooWorkspace *ws, TString mggName, float muCB = 125.,
                          float sigmaCB = 2.);
double GetIntegral(RooWorkspace &w, TString pdfName, TString mggName);
void MakePlot(TTree *tree, RooWorkspace &w, TString pdfName, TString mggName);
RooWorkspace *MakeSideBandFit(TTree *tree, float forceSigma, bool constrainMu,
                              float forceMu, TString mggName);
RooWorkspace *MakeSignalBkgFit(TTree *tree, float forceSigma, bool constrainMu,
                               float forceMu, TString mggName);
RooWorkspace *MakeSignalBkgFit(TTree *treeData, TTree *treeSignal,
                               TTree *treeSMH, TString mggName);
RooWorkspace *MakeDataCard(TTree *treeData, TTree *treeSignal, TTree *treeSMH,
                           TString mggName, float SMH_Yield, std::string SMH_CL,
                           float Signal_Yield, std::string Signal_CL,
                           TString binNumber = "-1",
                           TString category = "category");

RooWorkspace *MakeSideBandFitAIC(TTree *tree, float forceSigma,
                                 bool constrainMu, float forceMu,
                                 TString mggName, double &AIC, TString ffName);
RooWorkspace *DoBiasTest(TTree *tree, TString mggName, TString f1, TString f2,
                         int ntoys = 1e2, int npoints = 1e4);
RooWorkspace *SelectBinning(TH1F *mggData, TString mggName, TString f1,
                            TString f2, int ntoys = 1e2, int npoints = 1e4,
                            TString outName = "dummy");
RooWorkspace *DoBiasTestSignal(TTree *tree, TString mggName, TString f1,
                               TString f2, int ntoys = 1e2, double frac = 1.0,
                               TString outName = "dummy");
RooDataSet *GenerateToys(RooAbsPdf *pdf, RooRealVar x, int ntoys);
RooWorkspace *MakeSideBandFitAIC_2(TTree *tree, float forceSigma,
                                   bool constrainMu, float forceMu,
                                   TString mggName, double *Nbkg, double &AIC,
                                   double &AIC_2, double &AIC_3,
                                   double &fitStatus_1, double &fitStatus_2,
                                   double &fitStatus_3, double &fitStatus_4,
                                   TString ffName);
#endif
