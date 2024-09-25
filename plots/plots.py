import uproot as ur
import mplhep as hep
import matplotlib.pyplot as plt
import numpy as np
import os

plt.style.use(hep.style.CMS)  # or ATLAS/LHCb2


def get_canvas(width_scale=1.0):
    # fig, axs = plt.subplots(1, 2, sharey="row", sharex="col")
    # width = 16 * (2 / 3)  # 7.056870070568701
    # height = 4
    # fig.set_size_inches(width, height)
    # fig.subplots_adjust(
    # left=None, bottom=None, right=None, top=None, wspace=0.02, hspace=0.02
    # )
    fig, axs = plt.subplots(1, 1, constrained_layout=True)

    # For one column
    width = 6
    height = width / 1.2
    width = width * width_scale
    fig.set_size_inches(width, height)
    return fig, axs


def save_figure(fig, outputDirectory, name):
    os.makedirs(outputDirectory, exist_ok=True)
    fig.savefig(outputDirectory + name + ".pdf", bbox_inches="tight")
    fig.savefig(outputDirectory + name + ".png", bbox_inches="tight", dpi=300)
    print(outputDirectory + name + " Has been created")


xLabel = {
    "t_diMuon_mass": r"$M_{\mu\mu}$ GeV",
    "t_diMuon_pt": r"$Pt_{\mu\mu}$ GeV",
    "t_Mu_pt": r"$Pt_{\mu}$ GeV",
}
ranges = {"t_diMuon_mass": (100, 180), "t_diMuon_pt": (0, 250), "t_Mu_pt": (0, 250)}


def draw_dimuon_variable(variable):
    # variables = ["t_diMuon_mass", "t_diMuon_pt", "t_mu1", "t_mu2", "t_Mu_pt"]
    # branches_DY = ur.open("DYSim.root")["tree"].arrays([variable], library="np")

    # branches_DY = ur.open("root://cmseos.fnal.gov//store/user/csanmart/analyzer_HiggsMuMu/DY120to200_Summer22/HiggsMuMu_2*.root")["tree"].arrays([variable], library="np")
    # branches_Higgs = ur.open("root://cmseos.fnal.gov//store/user/csanmart/analyzer_HiggsMuMu/VBF_Summer22/HiggsMuMu_*.root")["tree"].arrays([variable], library="np")

    branches_DY = ur.concatenate("/eos/uscms/store/user/csanmart/analyzer_HiggsMuMu/DY120to200_Summer22/HiggsMuMu_*.root:tree")[variable]
    branches_Higgs = ur.concatenate("/eos/uscms/store/user/csanmart/analyzer_HiggsMuMu/VBF_Summer22/HiggsMuMu_*.root:tree")[variable]

    histogram_DY, bins = np.histogram(
        # branches_DY[variable],
        branches_DY,
        bins=ranges[variable][1] - ranges[variable][0],
        range=ranges[variable],
    )
    histogram_Higgs, _ = np.histogram(
        # branches_Higgs[variable],
        branches_Higgs,
        bins=ranges[variable][1] - ranges[variable][0],
        range=ranges[variable],
    )
    hists = [histogram_DY, histogram_Higgs]
    for n, channel in enumerate(["DY", "Higgs"]):
        fig, axs = get_canvas()
        hep.histplot(hists[n], bins, yerr=True, ax=axs)
        # hep.histplot(histogram_Higgs, bins, yerr=True, ax=axs[1])

        axs.set_ylabel(r"Events/GeV", loc="center", fontsize=15)
        axs.annotate(
            channel + r" Simulation",
            xy=(0.04, 1.04),
            xycoords="axes fraction",
            fontsize=15,
        )

        axs.set_xlabel(xLabel[variable], fontsize=14)

        save_figure(fig, "./plots_test/", variable + "_" + channel)


def draw_muon_variable(variable):
    # variables = ["t_diMuon_mass", "t_diMuon_pt", "t_mu1", "t_mu2", "t_Mu_pt"]
    branches_DY = ur.open("DYSim.root")["tree"].arrays(
        [variable, "t_mu1", "t_mu2"], library="np"
    )
    branches_Higgs = ur.open("HiggsSim.root")["tree"].arrays(
        [variable, "t_mu1", "t_mu2"], library="np"
    )

    variable_DY_mu1 = np.array([])
    variable_DY_mu2 = np.array([])
    variable_Higgs_mu1 = np.array([])
    variable_Higgs_mu2 = np.array([])
    for event in range(len(branches_Higgs["t_mu1"])):
        variable_Higgs_mu1 = np.append(
            variable_Higgs_mu1,
            branches_Higgs[variable][event][branches_Higgs["t_mu1"][event]],
        )
        variable_Higgs_mu2 = np.append(
            variable_Higgs_mu2,
            branches_Higgs[variable][event][branches_Higgs["t_mu2"][event]],
        )
    for event in range(len(branches_DY["t_mu1"])):
        variable_DY_mu1 = np.append(
            variable_DY_mu1, branches_DY[variable][event][branches_DY["t_mu1"][event]]
        )
        variable_DY_mu2 = np.append(
            variable_DY_mu2, branches_DY[variable][event][branches_DY["t_mu2"][event]]
        )

    histogram_DY_mu1, bins = np.histogram(
        variable_DY_mu1,
        bins=ranges[variable][1] - ranges[variable][0],
        range=ranges[variable],
    )
    histogram_DY_mu2, _ = np.histogram(
        variable_DY_mu2,
        bins=ranges[variable][1] - ranges[variable][0],
        range=ranges[variable],
    )
    histogram_Higgs_mu1, _ = np.histogram(
        variable_Higgs_mu1,
        bins=ranges[variable][1] - ranges[variable][0],
        range=ranges[variable],
    )
    histogram_Higgs_mu2, _ = np.histogram(
        variable_Higgs_mu2,
        bins=ranges[variable][1] - ranges[variable][0],
        range=ranges[variable],
    )

    hists_mu1 = [histogram_DY_mu1, histogram_Higgs_mu1]
    hists_mu2 = [histogram_DY_mu2, histogram_Higgs_mu2]

    for n, channel in enumerate(["DY", "Higgs"]):
        fig, axs = get_canvas()
        hep.histplot(hists_mu1[n], bins, yerr=True, ax=axs, label=r"$\mu_1$")
        hep.histplot(hists_mu2[n], bins, yerr=True, ax=axs, label=r"$\mu_2$")

        axs.set_ylabel(r"Events/GeV", loc="center", fontsize=15)
        axs.annotate(
            channel + r" Simulation",
            xy=(0.04, 1.04),
            xycoords="axes fraction",
            fontsize=15,
        )

        axs.set_xlabel(xLabel[variable], fontsize=14)

        axs.legend(frameon=False, loc="upper right", fontsize=11)

        save_figure(fig, "./plots_test/", variable + "_" + channel)


draw_dimuon_variable("t_diMuon_mass")
draw_dimuon_variable("t_diMuon_pt")
# draw_muon_variable("t_Mu_pt")
