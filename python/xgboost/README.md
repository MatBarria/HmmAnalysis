This code does the BDT training for the ggH and/or VBF Categorization.

## First time only

Go to https://uscms.org/uscms_at_work/computing/setup/gpu.shtml and follow the EAF instructions.

Once you have access to the cluster and the grid, go to https://analytics-hub.fnal.gov, create a server (you can request a 20GB workspace in CMS CERN, for instance).

When you are in, do
```
"${SHELL}" <(curl -L micro.mamba.pm/install.sh)
micromamba create -n xgboost_env xgboost python=3.10 krb5  curl cfitsio root tensorflow keras -c conda-forge
pip3 install pandas 
pip3 install uproot
pip3 install matplotlib
pip3 install graphviz
pip3 install mplhep

```

## How to run

Pick your node https://analytics-hub.fnal.gov/hub/home and activate the environment
```
eval "$(micromamba shell hook --shell bash)"
micromamba activate xgboost_env
```

Go to the xgboost directory
```
cd /your_path/HmmAnalysis/python/xgboost
```

Run the training (Make sure you generated the skim tuples first)
```
python3 train.py era
```
