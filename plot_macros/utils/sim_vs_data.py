import uproot as ur
import mplhep as hep
import numpy as np
import matplotlib.pyplot as plt

from .labels import (
    x_labels,
    background_labels,
    luminosity,
    x_range,
    n_bins,
    variables_type,
)  # , y_labels
from .helper import (
    get_canvas,
    save_figure,
    get_histograms_ratio,
    get_output_directory,
    clean_null_values,
)

signal_colors = {"ggH": "red", "VBF": "blue", "ttH": "lime"}

BDT_limits = {
    "ggH": {
        "BFull_SFull": [0.0, 0.06461538461538464, 0.16153846153846155, 1.0],
    },
    "VBF": {
        "BFull_SNottH": [0.0, 0.38, 0.912, 0.977, 1.0],
        "BNoDY50_SNottH": [0.0, 0.546, 0.935, 0.985, 1.0],
    },
    "": [],
}

def get_color_list(number_of_histograms):
    colors = [
        "#3f90da",
        "#ffa90e",
        "#bd1f01",
        "#94a4a2",
        "#832db6",
        "#a96b59",
        "#e76300",
        "#b9ac70",
        "#717581",
        "#92dadd",
    ]

    color_list = []
    for i in range(number_of_histograms):
        color_list.append(colors[i])

    return color_list


def get_background_label_list(background_sources):
    labels_list = []
    for source in background_sources:
        labels_list.append(background_labels[source])
    return labels_list


def get_histograms_from_tuple(
    sources,
    era,
    variables,
    is_background,
    use_puweight,
    prod_channel,
    bdt_categories=[],
    bdt_subset="",
):
    if not use_puweight:
        variables.append("pileup_weight")

    histograms_list = []
    bins_list = []

    variable_bin = variables[0]
    if variable_bin + "_" + prod_channel in x_range:
        variable_bin += "_" + prod_channel

    for source in sources:
        tuple_path = "../root_io/tuples/"
        if bdt_subset:
            tuple_path += "BDT_score/" + bdt_subset + "/"

        with ur.open(
            tuple_path + source + "_" + era + "_tuples.root:tree_output"
        ) as file:
            branches = file.arrays(variables, library="np")

            bool_list = np.ones(len(branches[variables[0]]), dtype=bool)

            if variables[0] != "diMuon_mass" and is_background:
                bool_list = (bool_list) & (
                    (branches["diMuon_mass"] > 130) | (branches["diMuon_mass"] < 120)
                )

            if prod_channel:
                br_name = "is_" + prod_channel + "_category"
                bool_list = (bool_list) & (branches[br_name] == 1)

            if len(bdt_categories) > 1:
                BDT_branch = "BDT_" + prod_channel
                bdt_bool = (branches[BDT_branch] > bdt_categories[0]) &\
                        (branches[BDT_branch] < bdt_categories[1])
                bool_list = (bool_list) & (bdt_bool)

            for var in variables:
                branches[var] = branches[var][bool_list]

            clean_null_values(branches, variables, variables_type)

            if "delta_phi" in variables[0]:
                branches[variables[0]] = np.absolute(branches[variables[0]])

            histogram, bins = np.histogram(
                branches[variables[0]],
                bins=n_bins[variable_bin],
                range=x_range[variable_bin],
                # weights=branches["weight"],
                weights=(
                    branches["weight"]
                    if use_puweight
                    else branches["weight"] / branches["pileup_weight"]
                ),
            )
            histograms_list.append(histogram)
            bins_list.append(bins)
            # histograms_list[source] = histogram
            # bins_list[source] = bins

    return histograms_list, bins_list


def get_data_histograms_from_tuple(
    era,
    variables,
    prod_channel,
    bdt_categories=[],
    bdt_subset = "",
):
    tuple_path = "../root_io/tuples/"
    if bdt_subset:
        tuple_path += "BDT_score/" + bdt_subset + "/"

    variable_bin = variables[0]
    if variable_bin + "_" + prod_channel in x_range:
        variable_bin += "_" + prod_channel

    with ur.open(
        tuple_path + "Data_" + era + "_tuples.root:tree_output"
    ) as data_file:
        branches = data_file.arrays(variables, library="np")

        bool_list = (branches["diMuon_mass"] > 130) | (branches["diMuon_mass"] < 120)

        if prod_channel:
            br_name = "is_" + prod_channel + "_category"
            bool_list = (bool_list) & (branches[br_name] == 1)

        if len(bdt_categories) > 1:
            BDT_branch = "BDT_" + prod_channel
            bdt_bool = (branches[BDT_branch] > bdt_categories[0]) &\
                       (branches[BDT_branch] < bdt_categories[1])
            bool_list = (bool_list) & (bdt_bool)

        for var in variables:
            branches[var] = branches[var][bool_list]

        if "delta_phi" in variables[0]:
            branches[variables[0]] = np.absolute(branches[variables[0]])

        data_histogram, data_bins = np.histogram(
            branches[variables[0]],
            bins=n_bins[variable_bin],
            range=x_range[variable_bin],
        )

    return data_histogram, data_bins


def draw_data_and_simul_and_ratio(
    variable,
    era,
    background_sources,
    signal_sources,
    use_puweight=True,
    prod_channel="",
    bdt_subset="",
    recursive_lvl = 0,
    bdt_categories=[],
):
    plt.style.use(hep.style.CMS)

    if recursive_lvl == 0:
        print(" > Draw " + variable)

    use_channel_cut = bool(prod_channel)
    use_bdt = bool(bdt_subset)
    if use_bdt and not bdt_categories and (variable != "BDT_" + prod_channel):
        bdt_categories = BDT_limits[prod_channel]
        if bdt_subset in bdt_categories:
            bdt_categories = bdt_categories[bdt_subset]

    variables = [variable, "weight"]
    if variable != "diMuon_mass":
        variables.append("diMuon_mass")
    if use_channel_cut:
        variables.append("is_" + prod_channel + "_category")
    if len(bdt_categories) > 1 and (variable != "BDT_" + prod_channel):
        variables.append("BDT_" + prod_channel)

    variable_bin = variable
    if variable + "_" + prod_channel in x_range:
        variable_bin += "_" + prod_channel

    data_histogram, data_bins = get_data_histograms_from_tuple(
        era, variables, prod_channel, bdt_categories, bdt_subset
    )
    if variable == "diMuon_mass":
        data_histogram[data_histogram == 0] = -100.0

    bkg_histograms_list, bkg_bins_list = get_histograms_from_tuple(
        background_sources,
        era,
        variables,
        True,
        use_puweight,
        prod_channel,
        bdt_categories,
        bdt_subset,
    )
    signal_histograms_list, signal_bins_list = get_histograms_from_tuple(
        signal_sources,
        era,
        variables,
        False,
        use_puweight,
        prod_channel,
        bdt_categories,
        bdt_subset,
    )

    fig, axs = get_canvas(True)

    hep.histplot(
        bkg_histograms_list,
        bkg_bins_list[0],
        yerr=True,
        histtype="fill",
        label=get_background_label_list(background_sources),
        ax=axs[0],
        stack=True,
        color=get_color_list(len(background_sources)),
    )

    hep.histplot(
        data_histogram,
        data_bins,
        yerr=True,
        histtype="errorbar",
        label="data",
        color="black",
        ax=axs[0],
    )

    signal_scale_factor = 10
    for source, histogram in zip(signal_sources, signal_histograms_list):
        hep.histplot(
            histogram * signal_scale_factor,
            signal_bins_list[0],
            yerr=False,
            # yerr=True,
            label=source + " (x" + str(signal_scale_factor) + ")",
            color=signal_colors[source],
            ax=axs[0],
        )

    label = ""
    if not use_puweight:
        label = "No PU weight"
    if len(bdt_categories) > 1:
        label = "Cat" + str(recursive_lvl)

    hep.cms.label(
        data="True",
        label=label,
        year=era,
        com="13.6",
        lumi=luminosity[era],
        ax=axs[0],
    )

    axs[0].set_ylabel(r"Events")
    # axs[0].set_ylim(-10000, y_axis_max_range[variable])
    # axs[0].set_ylim(0.1, y_axis_max_range[variable])
    axs[0].set_ylim(0.1, 1000 * np.max(data_histogram))
    axs[0].set_xlim(data_bins[0], data_bins[-1])
    axs[0].set_yscale("log")
    axs[0].legend(frameon=False, loc="upper right", ncols=2)
    axs[0].tick_params(axis="x", which="both", bottom=True, top=True, labelbottom=False)

    plt.axhline(y=1, color="grey", linestyle="--", alpha=0.5)

    tot_bg_numpy_hist = np.array([])
    for i, bg_hist in enumerate(bkg_histograms_list):
        if i == 0:
            tot_bg_numpy_hist = bg_hist
        else:
            tot_bg_numpy_hist = tot_bg_numpy_hist + bg_hist

    ratio_hist, ratio_error = get_histograms_ratio(data_histogram, tot_bg_numpy_hist)

    hep.histplot(
        ratio_hist,
        data_bins,
        yerr=ratio_error,
        histtype="errorbar",
        label="data",
        color="black",
        ax=axs[1],
    )

    axs[1].set_ylabel("Data/MC", loc="center")
    axs[1].set_ylim(0.5, 1.5)
    axs[1].set_xlim(data_bins[0], data_bins[-1])
    axs[1].set_xlabel(x_labels[variable])

    output_directory = "../plots/ratio/" + era + "/"
    if not use_puweight:
        output_directory += "no_puWeight/"
    elif use_channel_cut:
        output_directory += prod_channel + "_production/"
        if use_bdt:
            output_directory += bdt_subset + "/"
        if len(bdt_categories) > 1:
            output_directory += "BDT_categories/"

    if not use_bdt:
        output_directory += "variables_distributions/"
        output_directory = get_output_directory(variable, output_directory, variables_type)

    output_name = variable + "_" + era + "_MCData_ratio"
    if use_channel_cut and use_bdt and len(bdt_categories) > 1:
        output_name += "_" + label

    save_figure(fig, output_directory, output_name)
    plt.close()

    if len(bdt_categories) > 2:
        print("Iteration: ", recursive_lvl+1)
        draw_data_and_simul_and_ratio(
            variable,
            era,
            background_sources,
            signal_sources,
            use_puweight=use_puweight,
            prod_channel=prod_channel,
            bdt_subset=bdt_subset,
            recursive_lvl=recursive_lvl+1,
            bdt_categories=bdt_categories[1:],
        )
