from utils.sim_vs_data import draw_data_and_simul_and_ratio
import sys

plot_variables = False
if ("--distributions" in sys.argv):
    sys.argv.remove("--distributions")
    print(" > Ploting variable's distributions too!")
    plot_variables = True

# Default values
production_channel = ""
bsubset = "Full"
ssubset = "NottH"

if len(sys.argv) == 4:
    production_channel = sys.argv[1]
    bsubset = sys.argv[2]
    ssubset = sys.argv[3]
elif len(sys.argv) == 2:
    production_channel = sys.argv[1]
elif len(sys.argv) == 1:
    print("Using no production channel selection.")
    bsubset = ""
    ssubset = ""
else:
    print("Use three arguments: Production_channel, bkg subset, signal subset.")
    print("Production_channel must be ggH or VBF! Leave empty if no selection wanted.")
    print("Subset can be skipped (default) or use BOTH, bkg and signal.")
    exit()

bdt_subset = "B" + bsubset + "_S" + ssubset if bsubset else ""

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

# eras = ["2022", "2022EE", "2023", "2023BPix"]
eras = ["Combined"]
# eras = ["2022", "2022EE"]
# eras = ["2023", "2023BPix"]

if plot_variables:
    for era in eras:
        print(" ----------- " + era + " ----------- ")
        for variable in variables:
            draw_data_and_simul_and_ratio(
                variable,
                era,
                background_sources,
                signal_sources,
                prod_channel=production_channel,
            )

        # for var in ["PV", "rho"]:
        #     draw_data_and_simul_and_ratio(var, era, background_sources,
        #                                   signal_sources)
        #     draw_data_and_simul_and_ratio(var, era, background_sources,
        #                                   signal_sources, use_puweight=False)

if bdt_subset:
    print(" ----------- DiMuon mass per BDT category ----------- ")
    draw_data_and_simul_and_ratio(
        "diMuon_mass",
        "Combined",
        background_sources,
        signal_sources,
        use_puweight=True,
        prod_channel=production_channel,
        bdt_subset=bdt_subset,
    )

    if production_channel:
        print(" ----------- BDT categories distribution ----------- ")
        draw_data_and_simul_and_ratio(
            "BDT_" + production_channel,
            "Combined",
            background_sources,
            signal_sources,
            prod_channel=production_channel,
            bdt_subset=bdt_subset,
        )
