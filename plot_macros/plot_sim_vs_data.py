from utils.sim_vs_data import draw_data_and_simul_and_ratio
import sys

if len(sys.argv) > 2:
    print("Use one argument: Category. Show only events from that category")
    exit()

use_ggH = False if sys.argv[1] != "ggH" else True
use_VBF = False if sys.argv[1] != "VBF" else True

if not use_ggH and not use_VBF:
    print("Using no category selection as default.")

# ordered from bottom to top in the plot, so order it from lower to bigger cross section
background_sources = [
    "EWK",
    "DiBoson",
    "TT",
    "DY",
]

signal_sources = [
    "ggH",
    "VBF",
    "ttH",
]

variables = [
    ## DiMuon variables
    "diMuon_mass",
    # "diMuon_mass_full_range",
    "diMuon_rapidity",
    "diMuon_eta",
    "diMuon_pt",
    "diMuon_phi",
    ## Muon variables
    "mu1_pt_mass_ratio",
    "mu2_pt_mass_ratio",
    "mu1_eta",
    "mu2_eta",
    "phi_CS",
    "cos_theta_CS",
    ## Jet variables
    "n_jet",
    "leading_jet_pt",
    "subleading_jet_pt",
    "leading_jet_eta",
    ## diJet variables
    "diJet_mass",
    "delta_eta_diJet",
    "delta_phi_diJet",
    "z_zeppenfeld",
    "min_delta_eta_diMuon_jet",
    "min_delta_phi_diMuon_jet",
    ## VBF required
    "pt_balance",
    "pt_centrality",
    "n_SoftJet_pt2",
    "n_SoftJet_pt5",
    "n_SoftJet_pt10",
    "HT",
    "HT_pt2",
    "HT_pt5",
    "HT_pt10",
]

# eras = ["2022", "2022EE", "2023", "2023BPix","2024"]
# eras = ["2022", "2022EE"]
# eras = ["2023", "2023BPix"]
eras = ["2024"]

for era in eras:
    for variable in variables:
        draw_data_and_simul_and_ratio(variable, era, background_sources,
                                      signal_sources,
                                      use_ggH_category=use_ggH,
                                      use_VBF_category=use_VBF)

    # draw_data_and_simul_and_ratio("PV", era, background_sources, signal_sources)
    # draw_data_and_simul_and_ratio("rho", era, background_sources, signal_sources)
    # draw_data_and_simul_and_ratio(
    #     "PV", era, background_sources, signal_sources, use_puweight=False
    # )
    # draw_data_and_simul_and_ratio(
    #     "rho", era, background_sources, signal_sources, use_puweight=False
    # )
