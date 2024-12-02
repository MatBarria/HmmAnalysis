## Notes
### Skim files
- These files are used by BDT training, BDT categories, and "Signal vs background"
- Make sure you merged the skim files using [hadd for VBF](../root_io/skim/VBF/hadd_skim.sh), for instance, before running plot_sig_vs_bg.py
- Remember to append the [BDT branch](../python/xgboost/append_xgboost_discriminator_to_tree.py) (using `--skim` option in macro. This is already done when running [training bash script](../python/xgboost/run_train.sh))
- **Remember** to update `BDT_limits` [here](../plot_macros/utils/sim_vs_data.py) with the plot_BDT_Categories.py output before plotting signal vs data (if BDT selection is required)

### Tuples files
- These files are used by "Signal vs data" 
- Make sure you have the correct tuples files. You can copy them from EOS [here](../root_io/tuples/hadd_tuples_EOS.sh).
- Remember to append the [BDT branch](../python/xgboost/append_xgboost_discriminator_to_tree.py) (already done when running [training bash script](../python/xgboost/run_train.sh))
