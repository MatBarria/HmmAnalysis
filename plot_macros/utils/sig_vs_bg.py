# import uproot as ur
import mplhep as hep
import numpy as np
import matplotlib.pyplot as plt

from .labels import x_labels, y_labels
from .helper import get_canvas, save_figure, get_histograms

y_axis_max_range = {
    "pt": 0.07,
    "phi": 0.015,
    "eta": 0.025,
}


def draw_sig_and_bg(variable, era, background_sources, signal_sources):

    plt.style.use(hep.style.CMS)

    background_histograms = get_histograms(variable, background_sources)
    signal_histograms = get_histograms(variable, signal_sources)

    total_bg_np_histogram = np.array([])
    total_sig_np_histogram = np.array([])
    bins = np.array([])

    for i, hist in enumerate(background_histograms):
        if i == 0:
            total_bg_np_histogram, bins = hist.to_numpy()
        else:
            total_bg_np_histogram = total_bg_np_histogram + hist.to_numpy()[0]

    for i, hist in enumerate(signal_histograms):
        if i == 0:
            total_sig_np_histogram = hist.to_numpy()[0]
        else:
            total_sig_np_histogram = total_sig_np_histogram + hist.to_numpy()[0]

    fig, ax = get_canvas()

    hep.histplot(
        total_bg_np_histogram/np.sum(total_bg_np_histogram),
        bins,
        yerr=True,
        histtype="fill",
        label="background",
        ax=ax,
        stack=True,
        color="blue",
        alpha=0.5,
    )

    hep.histplot(
        total_sig_np_histogram/np.sum(total_sig_np_histogram),
        bins,
        yerr=True,
        histtype="fill",
        label=" signal",
        ax=ax,
        stack=True,
        color="red",
        alpha=0.5,
    )

    hep.cms.label(
        data="True", label="Test", year="2022", com="13,6", lumi="17.4", ax=ax
    )

    ax.set_ylabel(y_labels[variable])
    ax.set_xlabel(x_labels[variable])
    ax.set_ylim(0, y_axis_max_range[variable])
    ax.set_xlim(bins[0], bins[-1])
    # ax.set_yscale("log")
    ax.legend(frameon=False, loc="upper right", ncols=2)

    save_figure(fig, "../plots/sig_vs_bg/", variable + "_" + era + "_MCData_ratio")