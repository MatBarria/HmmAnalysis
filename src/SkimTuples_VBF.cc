#include <TBranch.h>
#include <TFile.h>
#include <TROOT.h>
#include <TTree.h>
#include <iostream>
// g++ -o ./bin/SkimTuples_VBF src/SkimTuples_VBF.cc $(root-config --cflags
// --libs)

int main(int argc, char *argv[]) {

    if (argc != 4) {
        std::cerr << "Please give 3 arguments: input folder, channel, era."
                  << std::endl;
        return -1;
    }

    TString input_path(argv[1]);
    TString channel(argv[2]);
    TString era(argv[3]);
    std::cout << "channel: " << channel << std::endl;
    std::cout << "era: " << era << std::endl;

    // Open the input ROOT file and get the TTree
    TString input_name = input_path + channel + "_" + era + "_tuples.root";
    TFile inputFile(input_name, "READ");
    if (inputFile.IsZombie()) {
        std::cerr << "Error opening input file!" << std::endl;
        return 0;
    }

    TTree *tree_input = (TTree *)inputFile.Get("tree_output");
    if (!tree_input) {
        std::cerr << "Tree output not found in file " << input_name << std::endl;
        return 0;
    }
    tree_input->SetBranchStatus("*", 0);

    std::vector<TString> branches = {
        "diMuon_mass",
        "diMuon_pt",
        "diMuon_rapidity",
        "mu1_pt_mass_ratio",
        "mu2_pt_mass_ratio",
        "mu1_eta",
        "mu2_eta",
        // "phi_CS",
        // "cos_theta_CS",
        "n_jet",
        "leading_jet_pt",
        "subleading_jet_pt",
        "leading_jet_eta",
        "diJet_mass",
        "delta_eta_diJet",
        "delta_phi_diJet",
        "z_zeppenfeld",
        "pt_balance",
        "min_delta_eta_diMuon_jet",
        "min_delta_phi_diMuon_jet",
        "n_SoftJet_pt2",
        "n_SoftJet_pt5",
        "n_SoftJet_pt10",
        "weight_no_lumi",
        "is_ggH_category",
        "is_VBF_category",
    };
    for (auto VBF_branch : branches)
        tree_input->SetBranchStatus(VBF_branch, 1);

    gROOT->cd();
    // Open the output ROOT file and create a new TTree
    TFile output_file("./root_io/skim_VBF/" + channel + "_" + era + "_skim.root",
                      "RECREATE");
    TTree *tree_output = tree_input->CloneTree(0); // Clone the structure only

    tree_output = tree_input->CopyTree("is_VBF_category == 1");

    // Write the selected tree to the output file
    output_file.cd();
    tree_output->Write();
    output_file.Close();
    inputFile.Close();
}
