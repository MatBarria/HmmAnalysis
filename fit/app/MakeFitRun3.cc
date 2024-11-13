// C++ INCLUDES
#include <iostream>
// ROOT INCLUDES
#include <TFile.h>
#include <TH1.h>
#include <TStopwatch.h>
#include <TString.h>
#include <TTree.h>
// LOCAL INCLUDES
#include "CommandLineInput.hh"
#include "DefinePdfs.hh"
#include "RunTwoFitMgg.hh"
#include "makeInvertedANFit_v2.hh"
#include <TSystem.h>

int main(int argc, char *argv[]) {
    std::string inputFile = ParseCommandLine(argc, argv, "-BkgFile=");
    if (inputFile == "") {
        std::cerr << "[Error]: please provide an BkgFile using "
                     "--BkgFile=<path_to_file>"
                  << std::endl;
        return -1;
    }

    std::string inputFile2 = ParseCommandLine(argc, argv, "-SigFile=");
    if (inputFile2 == "") {
        std::cerr << "[Error]: please provide Signal file using "
                     "--SigFile=<path_to_file>"
                  << std::endl;
        return -1;
    }
    TString BDT_bottom_cut = ParseCommandLine(argc, argv, "-BDTbottomCut=");
    if (BDT_bottom_cut == "") {
        std::cerr << "[Error]: please provide lower limit for BDT"
                     "--BDTbottomCut=number"
                  << std::endl;
        return -1;
    }
    TString BDT_upper_cut = ParseCommandLine(argc, argv, "-BDTupperCut=");
    if (BDT_upper_cut == "") {
        std::cerr << "[Error]: please provide upper limit for BDT"
                     "--BDTupperCut=number"
                  << std::endl;
        return -1;
    }
    TString category = ParseCommandLine(argc, argv, "-category=");
    if (category == "") {
        std::cerr << "[Error]: please provide a category"
                     "--category=Cat#$"
                  << std::endl;
        return -1;
    }
    std::string treeName = ParseCommandLine(argc, argv, "-treeName=");
    if (treeName == "") {
        std::cout << "[WARNING]: user did not provide a tree name, if you wish "
                     "to provide one use --treeName=<yourTreeName>"
                  << std::endl;
        treeName = "tree_output";
    }

    std::cout << "[INFO]: tree name is :" << treeName << std::endl;

    TStopwatch timer;
    timer.Start();

    TTree *bkg_tree;
    TFile *bkg_file;
    TTree *signal_tree;
    TFile *signal_file;

    bkg_file = new TFile(inputFile.c_str());
    bkg_tree = (TTree *)bkg_file->Get(treeName.c_str());

    signal_file = new TFile(inputFile2.c_str(), "update");
    signal_tree = (TTree *)signal_file->Get(treeName.c_str());

    // TString bkg_cuts = "((diMuon_mass>110 && diMuon_mass<120) ||
    // (diMuon_mass>130 && diMuon_mass< 150)) && (is_ggH_category==1) &&
    // (BDT_ggH > " + BDT_bottom_cut + " && BDT_ggH < " + BDT_upper_cut + ")";
    TString bkg_cuts =
        "((diMuon_mass>103 && diMuon_mass<120) || "
        "(diMuon_mass>131 && diMuon_mass< 160)) && (is_ggH_category == 1)";
    // TString bkg_cuts = "diMuon_mass>103 && diMuon_mass<160";
    TString signal_cuts = "(is_ggH_category == 1)";

    std::cout << "Main 1" << std::endl;
    TFile *file_output = new TFile("fits" + category + ".root", "recreate");
    float force_sigma = 1.5;
    bool constrain_mu = false;
    float force_mu = -1;
    TString fit_variable_name = "diMuon_mass";
    RooWorkspace *w;
    RooWorkspace *w2;
    RooWorkspace *w3;

    std::cout << "Main 2" << std::endl;
    bkg_tree->CopyTree(bkg_cuts)->Draw("diMuon_mass>>hbkg(40,110,150)");
    TH1F *hbkg = (TH1F *)gDirectory->Get("hbkg");
    signal_tree->CopyTree(signal_cuts)->Draw("diMuon_mass>>hsig(40,110,150)");
    TH1F *hsig = (TH1F *)gDirectory->Get("hsig");

    w = makeInvertedANFit(bkg_tree->CopyTree(bkg_cuts), force_sigma,
                          constrain_mu, force_mu, fit_variable_name);

    TString combineBkg = MakeSingleExpNE("my_bkg", *w->var("diMuon_mass"), *w);
    w->var("diMuon_mass")->setBins(38);
    RooRealVar Bkg_norm(combineBkg + "_norm", "", 100);
    Bkg_norm.setConstant(kFALSE);
    w->import(Bkg_norm);

    // std::cout << "Main 3" << std::endl;
    // w2 = makeMCFit(signal_tree->CopyTree(signal_cuts), force_sigma,
    // constrain_mu, force_mu, fit_variable_name);
    // w3 = DoubleCBFit(signal_tree->CopyTree(signal_cuts), fit_variable_name);

    // TFile* file_output = new TFile( "test_out.root", "recreate" );
    std::cout << "Main 4" << std::endl;
    w->var("diMuon_mass")->setBins(38);
    // w2->var("diMuon_mass")->setBins(38);
    //  w3->var("diMuon_mass")->setBins(38);
    w->var("b_sexp_alpha1")->setConstant(false);
    w->Write("w1");
    // w2->Write("w2");
    //  w3->Write("w3");
    std::cout << "Main 5" << std::endl;
    hbkg->Write();
    hsig->Write();
    file_output->Close();
    timer.Print();

    std::cout << "Main 6" << std::endl;
    return 0;
}
