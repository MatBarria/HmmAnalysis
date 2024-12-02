import ROOT

f = ROOT.TFile("fit.root")
w = f.Get("w")
w.Print("v")

n_bins = 38
binning = ROOT.RooFit.Binning(n_bins,110,150)

w.var("Diphoton_Mass").setRange("Low",110,120)
w.var("Diphoton_Mass").setRange("High",130,150)
w.var("Diphoton_Mass").setRange("Full",110,150)
fit_range = "Low,High"

can = ROOT.TCanvas()
plot = w.var("diMuon_mass").frame()
w.data("data_obs").plotOn( plot, binning)

# Load the S+B model
#sb_model = w.pdf("model_s").getPdf("Cat1")
sb_model = w.pdf("model_s").getPdf("Cat3")
#Diphoton_Masssb_model = w.pdf("model_s").getPdf("Cat3")


# Prefit
sb_model.plotOn( plot, ROOT.RooFit.LineColor(2), ROOT.RooFit.Name("prefit") )

# Postfit
w.loadSnapshot("MultiDimFit")
sb_model.plotOn( plot, ROOT.RooFit.LineColor(4), ROOT.RooFit.Name("postfit"), ROOT.RooFit.Range("Full"),ROOT.RooFit.NormRange(fit_range))


#w.data("data_obs").plotOn( plot, ROOT.RooFit.CutRange(fit_range), binning )


r_bestfit = w.var("r").getVal()

plot.Draw()

leg = ROOT.TLegend(0.55,0.6,0.85,0.85)
leg.AddEntry("prefit", "Prefit S+B model (r=1.00)", "L")
leg.AddEntry("postfit", "Postfit S+B model (r=%.2f)"%r_bestfit, "L")
leg.Draw("Same")

can.Update()
can.SaveAs("part_cat3.png")
