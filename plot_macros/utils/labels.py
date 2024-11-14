"""
A dictionary mapping variable names to their LaTeX-formatted x-axis labels for plotting.

Keys:
-----
Each key represents a variable name as a string, which categorizes the type of physical
quantity (e.g., DiMuon, Muon, Jet, DiJet variables).

Values:
------
Each value is a LaTeX-formatted string representing the label to be used on the x-axis
when plotting the corresponding variable.

"""

x_labels = {
    ## Event variables
    "PV": r"$PV$",
    "rho": r"$\rho$",
    ## DiMuon variables
    "diMuon_rapidity": r"$y_{\mu\mu}$",
    "diMuon_pt": r"$p_T^{\mu\mu}$ [GeV]",
    "diMuon_mass": r"$M_{\mu\mu}$ [GeV]",
    "diMuon_mass_full_range": r"$M_{\mu\mu}$ [GeV]",
    "diMuon_phi": r"$\phi_{\mu\mu}$ [rad]",
    "diMuon_eta": r"$\eta_{\mu\mu}$ ",
    ## Muon variables
    "mu1_pt_mass_ratio": r"$p_T^{\mu 1}/m_{\mu\mu}$",
    "mu2_pt_mass_ratio": r"$p_T^{\mu 2}/m_{\mu\mu}$",
    "mu1_eta": r"$\eta_{\mu_1}$",
    "mu2_eta": r"$\eta_{\mu_2}$",
    "phi_CS": r"$\phi_{CS} [rad]$",
    "cos_theta_CS": r"$cos(\theta_{CS})$",
    ## Jet variables
    "n_jet": r"$N_{jets}$",
    "leading_jet_pt": r"$p_T^{j1}$ [GeV]",
    "subleading_jet_pt": r"$p_T^{j2}$ [GeV]",
    "leading_jet_eta": r"$\eta_{j1}$ ",
    "jet_phi": r"$\phi_{jet}$ [rad]",
    "jet_mass": r"$M_{jet}$ [GeV]",
    "delta_eta_diMuon_jet": r"$\Delta\eta_{\mu\mu,j}$",
    "delta_phi_diMuon_jet": r"$\Delta\phi_{\mu\mu,j}$",
    ## DiJet variables
    "diJet_pt": r"$p_T^{jj}$ [GeV]",
    "diJet_eta": r"$\eta_{jj}$ ",
    "diJet_phi": r"$\phi_{jj}$ [rad]",
    "diJet_mass": r"$m_{jj}$ [GeV]",
    "diJet_mass_mo": r"$M_{Dijet highest mass}$ [GeV]",
    "diJet_DeltaEta": r"$\Delta\eta_{jj}$",
    "delta_eta_diJet": r"$|\Delta\eta_{jj}|$",
    "delta_phi_diJet": r"$|\Delta\phi_{jj}|$ [rad]",
    "z_zeppenfeld": r"Z^{*} Zeppenfeld",
    "min_delta_eta_diMuon_jet": r"min$\Delta\eta_{\mu\mu,j}$",
    "min_delta_phi_diMuon_jet": r"min$\Delta\phi_{\mu\mu,j}$ [rad]",
    "pt_balance": r"$R(p_T)$",
    "pt_centrality": r"$p_{T}-centrality$",
    "n_SoftJet_pt2": r"$N_{2}^{soft}$",
    "n_SoftJet_pt5": r"$N_{5}^{soft}$",
    "n_SoftJet_pt10": r"$N_{10}^{soft}$",
    "HT": r"$H_{T}(soft)$",
    "HT_pt2": r"$H_{T}^{2}(soft)$",
    "HT_pt5": r"$H_{T}^{5}(soft)$",
    "HT_pt10": r"$H_{T}^{10}(soft)$",
    ## BDT_ggh
    "BDT_ggH": "BDT Output",
}

"""
A dictionary specifying the number of histogram bins for each variable in the analysis.

Keys:
-----
Variable name as a string.

Values:
------
Integer values specifying the number of bins use to create a histogram.
"""
n_bins = {
    ## Event variables
    "PV": 70,
    "rho": 100,
    ## DiMuon variables
    "diMuon_rapidity": 50,
    "diMuon_pt": 80,
    "diMuon_mass": 80,
    "diMuon_mass_full_range": 200,
    "diMuon_phi": 80,
    "diMuon_eta": 50,
    ## Muon variables
    "mu1_pt_mass_ratio": 50,
    "mu2_pt_mass_ratio": 50,
    "mu1_eta": 50,
    "mu2_eta": 50,
    "phi_CS": 50,
    "cos_theta_CS": 50,
    ## Jet variables
    "n_jet": 8,
    "leading_jet_pt": 50,
    "subleading_jet_pt": 50,
    "leading_jet_eta": 50,
    "jet_phi": 50,
    "jet_mass": 50,
    "delta_eta_diMuon_jet": 50,
    "delta_phi_diMuon_jet": 50,
    ## DiJet variables
    "diJet_pt": 50,
    "diJet_eta": 50,
    "diJet_phi": 50,
    "diJet_mass": 50,
    "diJet_mass_VBF": 50,
    "diJet_mass_mo": 50,
    "diJet_DeltaEta": 50,
    "delta_eta_diJet": 50,
    "delta_eta_diJet_ggH": 50,
    "delta_eta_diJet_VBF": 50,
    "delta_phi_diJet": 50,
    "z_zeppenfeld": 50,
    "z_zeppenfeld_VBF": 50,
    "min_delta_eta_diMuon_jet": 50,
    "min_delta_phi_diMuon_jet": 50,
    "pt_balance": 40,
    "pt_centrality": 30,
    "n_SoftJet_pt2": 40,
    "n_SoftJet_pt5": 40,
    "n_SoftJet_pt10": 40,
    "HT": 20,
    "HT_pt2": 20,
    "HT_pt5": 20,
    "HT_pt10": 20,
    ## BDT_ggh
    "BDT_ggH": 50,
}

"""
A dictionary defining the x-axis range for plotting each variable.

Keys:
-----
Variable name as a string
Values:
------
Tuple of two floats specifying the minimum and maximum range for the x-axis.
"""
x_range = {
    ## Event variables
    "PV": (0, 70),
    "rho": (0, 70),
    ## DiMuon variables
    "diMuon_pt": (0, 250),
    "diMuon_mass": (110, 150),
    "diMuon_phi": (-3.1415, 3.1415),
    "diMuon_eta": (-10, 10),
    "diMuon_rapidity": (-2.5, 2.5),
    "diMuon_mass_full_range": (50, 150),
    ## Muon variables
    "mu1_pt_mass_ratio": (0.19, 1.6),
    "mu2_pt_mass_ratio": (0.19, 1.6),
    "mu1_eta": (-2.4, 2.4),
    "mu2_eta": (-2.4, 2.4),
    "phi_CS": (-3.1415, 3.1415),
    "cos_theta_CS": (-1, 1),
    ## Jet variables
    "n_jet": (0, 8),
    "leading_jet_pt": (25, 400),
    "subleading_jet_pt": (25, 200),
    "leading_jet_eta": (-5, 5),
    "jet_phi": (-3.1415, 3.1415),
    "jet_mass": (0, 120),
    "delta_eta_diMuon_jet": (-10, 10),
    "delta_phi_diMuon_jet": (-5, 5),
    ## DiJetvariables
    "diJet_pt": (0, 800),
    "diJet_eta": (-10, 10),
    "diJet_phi": (-3.1415, 3.1415),
    "diJet_mass": (0, 500),
    "diJet_mass_VBF": (400, 900),
    "diJet_mass_mo": (0, 800),
    "diJet_DeltaEta": (-12, 12),
    "delta_eta_diJet": (0, 8.0),
    "delta_eta_diJet_ggH": (0, 5.5),
    "delta_eta_diJet_VBF": (2.5, 8.0),
    "delta_phi_diJet": (0, 3.14),
    "z_zeppenfeld": (-7, 7),
    "z_zeppenfeld_VBF": (-5, 5),
    "min_delta_eta_diMuon_jet": (0, 5),
    "min_delta_phi_diMuon_jet": (0, 3.14),
    "pt_balance": (0, 1),
    "pt_centrality": (0, 12),
    "n_SoftJet_pt2": (0, 40),
    "n_SoftJet_pt5": (0, 40),
    "n_SoftJet_pt10": (0, 40),
    "HT": (0, 60),
    "HT_pt2": (0, 60),
    "HT_pt5": (0, 60),
    "HT_pt10": (0, 60),
    ## BDT_ggh
    "BDT_ggH": (0, 1),
}

y_labels = {
    "diMuon_mass": r"events",
    "diMuon_mass_full_range": r"events",
    "diMuon_rapidity": r"events",
    "diMuon_pt": r"events",
    "diMuon_phi": r"events",
    "diMuon_eta": r"events",
}

background_labels = {
    ## DY
    "DY50-120": "DY MLL50-120 Bg",
    "DY120-200": "DY MLL120-200 Bg",
    "DY": "DY Background",
    "DYJetstoLL": "DY Background",
    "DYto2L-2Jets": "DY Background",
    "DYNew": "DY Background",
    ## TT
    "TT": "TT Background",
    ## DiBoson
    "DiBoson": "DiBoson Background",
    "ZZto2L2Nu": "ZZto2L2Nu",
    "ZZto4L": "ZZto4L",
    "WWto2L2Nu": "WWto2L2Nu",
    "ZZto2L2QNu": "ZZto2L2QNu",
    "WZto2L2QNu": "WZto2L2QNu",
    ## EWK
    "EWK": "EWK Background",
}

"""
A dictionary storing the integrated luminosity values for different data-taking periods.

Keys:
-----
Year or era as a string(e.g., "2022", "2022EE", "2022Combined".)

Values:
------
String representing the integrated luminosity value for each period in inverse femtobarns.
"""
luminosity = {
    ## LUMINOSITIES
    "2022": "7.98",
    "2022EE": "26.67",
    "2022Combined": "34.65",
    "2023": "17.8",
    "2023BPix": "9.5",
    "2023Combined": "27.3",
}

variables_type = {
    ## Event variables
    "event": [
        "PV",
        "rho",
        "n_SoftJet_pt2",
        "n_SoftJet_pt5",
        "n_SoftJet_pt10",
        "HT",
        "HT_pt2",
        "HT_pt5",
        "HT_pt10",
    ],
    ## DiMuon variables
    "diMuon": [
        "diMuon_rapidity",
        "diMuon_pt",
        "diMuon_mass",
        "diMuon_mass_full_range",
        "diMuon_phi",
        "diMuon_eta",
    ],
    ## Muon variables
    "muon": [
        "mu1_pt_mass_ratio",
        "mu2_pt_mass_ratio",
        "mu1_eta",
        "mu2_eta",
        "phi_CS",
        "cos_theta_CS",
    ],
    ## Jet variables
    "jet": [
        "n_jet",
        "leading_jet_pt",
        "subleading_jet_pt",
        "leading_jet_eta",
        "jet_phi",
        "jet_mass",
        "delta_eta_diMuon_jet",
        "delta_phi_diMuon_jet",
    ],
    ## DiJet variables
    "diJet": [
        "diJet_pt",
        "diJet_eta",
        "diJet_phi",
        "diJet_mass",
        "diJet_mass_mo",
        "diJet_DeltaEta",
        "delta_eta_diJet",
        "delta_phi_diJet",
        "z_zeppenfeld",
        "pt_balance",
        "pt_centrality",
        "min_delta_eta_diMuon_jet",
        "min_delta_phi_diMuon_jet",
    ],
    ## BDT_ggh
    "ggH_category": [
        "BDT_ggH",
    ],
}
