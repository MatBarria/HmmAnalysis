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
    use_ggH_category,
    use_VBF_category,
    ggH_bdt_selections=[],
):
    if not use_puweight:
        variables.append("pileup_weight")

    histograms_list = []
    bins_list = []

    variable_bin = variables[0]
    if use_ggH_category and (variable_bin + "_ggH" in x_range):
        variable_bin += "_ggH"
    if use_VBF_category and (variable_bin + "_VBF" in x_range):
        variable_bin += "_VBF"

    for source in sources:
        with ur.open(
            "../root_io/tuples/" + source + "_" + era + "_tuples.root:tree_output"
        ) as file:
            branches = file.arrays(variables, library="np")

            bool_list = np.ones(len(branches[variables[0]]), dtype=bool)

            if variables[0] != "diMuon_mass" and is_background:
                bool_list = (bool_list) & (
                    (branches["diMuon_mass"] > 130) | (branches["diMuon_mass"] < 120)
                )
            if use_ggH_category:
                bool_list = (bool_list) & (branches["is_ggH_category"] == 1)

            if use_VBF_category:
                bool_list = (bool_list) & (branches["is_VBF_category"] == 1)

            if len(ggH_bdt_selections) > 1:
                bdt_ggh_bool = (branches["BDT_ggH"] > ggH_bdt_selections[0]) & (
                    branches["BDT_ggH"] < ggH_bdt_selections[1]
                )
                bool_list = (bool_list) & (bdt_ggh_bool)

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
    use_ggH_category,
    use_VBF_category,
    ggH_bdt_selections=[],
):
    with ur.open(
        "../root_io/tuples/Data_" + era + "_tuples.root:tree_output"
    ) as data_file:
        branches = data_file.arrays(variables, library="np")

        bool_list = (branches["diMuon_mass"] > 130) | (branches["diMuon_mass"] < 120)

        if use_ggH_category:
            bool_list = (bool_list) & (branches["is_ggH_category"] == 1)
        if use_VBF_category:
            bool_list = (bool_list) & (branches["is_VBF_category"] == 1)

        if len(ggH_bdt_selections) > 1:
            bdt_ggh_bool = (branches["BDT_ggH"] > ggH_bdt_selections[0]) & (
                branches["BDT_ggH"] < ggH_bdt_selections[1]
            )
            bool_list = (bool_list) & (bdt_ggh_bool)

        for var in variables:
            branches[var] = branches[var][bool_list]

        if "delta_phi" in variables[0]:
            branches[variables[0]] = np.absolute(branches[variables[0]])

        data_histogram, data_bins = np.histogram(
            branches[variables[0]],
            bins=n_bins[variables[0]],
            range=x_range[variables[0]],
        )

    return data_histogram, data_bins


def draw_data_and_simul_and_ratio(
    variable,
    era,
    background_sources,
    signal_sources,
    use_puweight=True,
    use_ggH_category=False,
    use_VBF_category=False,
    ggH_bdt_selections=[],
):
    plt.style.use(hep.style.CMS)

    print("*" * len("****** PLOTTING " + variable + " *****"))
    print("****** PLOTTING " + variable + " *****")
    print("*" * len("****** PLOTTING " + variable + " *****"))

    variables = [variable, "weight"]
    if variable != "diMuon_mass":
        variables.append("diMuon_mass")
    if use_ggH_category:
        variables.append("is_ggH_category")
    elif use_VBF_category:
        variables.append("is_VBF_category")
    if len(ggH_bdt_selections) > 1 and variable != "BDT_ggH":
        variables.append("BDT_ggH")

    variable_bin = variable
    if use_ggH_category and (variable + "_ggH" in x_range):
        variable_bin += "_ggH"
    if use_VBF_category and (variable + "_VBF" in x_range):
        variable_bin += "_VBF"

    data_histogram, data_bins = get_data_histograms_from_tuple(
        era, variables, use_ggH_category, use_VBF_category, ggH_bdt_selections
    )
    if variable == "diMuon_mass":
        data_histogram[data_histogram == 0] = -100.0

    bkg_histograms_list, bkg_bins_list = get_histograms_from_tuple(
        background_sources,
        era,
        variables,
        True,
        use_puweight,
        use_ggH_category,
        use_VBF_category,
        ggH_bdt_selections,
    )
    signal_histograms_list, signal_bins_list = get_histograms_from_tuple(
        signal_sources,
        era,
        variables,
        False,
        use_puweight,
        use_ggH_category,
        use_VBF_category,
        ggH_bdt_selections,
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
    if len(ggH_bdt_selections) > 1:
        label = "Cat" + str(4 - len(ggH_bdt_selections))

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
    output_name = variable + "_" + era + "_MCData_ratio"
    if not use_puweight:
        output_directory = "../plots/ratio/" + era + "/no_puWeight/"
    if use_ggH_category:
        output_directory = "../plots/ratio/ggH_category/" + era + "/"
    elif use_VBF_category:
        output_directory = "../plots/ratio/VBF_category/" + era + "/"
    if len(ggH_bdt_selections) > 1:
        output_directory = "../plots/ratio/ggH_category/bdt_selections/" + era + "/"
        output_name += label

    output_directory = get_output_directory(variable, output_directory, variables_type)
    save_figure(fig, output_directory, output_name)
    plt.close()

    if len(ggH_bdt_selections) > 2:
        draw_data_and_simul_and_ratio(
            variable,
            era,
            background_sources,
            signal_sources,
            use_puweight=use_puweight,
            use_ggH_category=use_ggH_category,
            use_VBF_category=use_VBF_category,
            ggH_bdt_selections=ggH_bdt_selections[1:],
        )
