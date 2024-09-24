#!/usr/bin/python

import os
import datetime
import time
import subprocess
import glob
import sys
from collections import OrderedDict

analyzer = "HmmAnalyzer"
analysis = "HiggsMuMu"
outputfile = analysis

all_dataset_lists = OrderedDict()
# Each entry contains [isData, max_runs_per_job, year]
#################
# 2022 Datasets
#################
all_dataset_lists["DoubleMuon_2022A.list"] = ["T", 3, "2022"]
all_dataset_lists["DoubleMuon_2022B.list"] = ["T", 3, "2022"]
all_dataset_lists["DoubleMuon_2022C.list"] = ["T", 3, "2022"]
all_dataset_lists["Muon_2022C.list"] = ["T", 3, "2022"]
all_dataset_lists["Muon_2022D.list"] = ["T", 3, "2022"]
all_dataset_lists["Muon_2022E.list"] = ["T", 3, "2022"]
all_dataset_lists["Muon_2022F.list"] = ["T", 3, "2022"]
all_dataset_lists["Muon_2022G.list"] = ["T", 3, "2022"]
################################
# 2022 Simulations Backgrounds
################################
all_dataset_lists["DY120to200_Summer22.list"] = ["F", 3, "2022"]
all_dataset_lists["DY50to150_Summer22.list"] = ["F", 3, "2022"]
all_dataset_lists["DY120to200_Summer22EE.list"] = ["F", 3, "2022"]
all_dataset_lists["DY50to150_Summer22EE.list"] = ["F", 3, "2022"]
###########################
# 2022 Simulations Signal
###########################
all_dataset_lists["ggH_Summer22.list"] = ["F", 3, "2022"]
all_dataset_lists["ggH_Summer22EE.list"] = ["F", 3, "2022"]
all_dataset_lists["VBF_Summer22.list"] = ["F", 3, "2022"]
all_dataset_lists["VBF_Summer22EE.list"] = ["F", 3, "2022"]


# cmsswReleaseVersion = "CMSSW_10_6_5"
CMSSW_BASE_DIR = os.getenv('CMSSW_BASE')
# Analyzer_DIR = CMSSW_BASE_DIR + "/src/HmmAna/HmmAna/"
Condor_BASE_DIR = os.getcwd() + "/"
Analyzer_DIR = Condor_BASE_DIR.split("condor/")[0]
# Condor_BASE_DIR = Analyzer_DIR + "condor/"
Inputfiles_DIR = Analyzer_DIR + "list/"

cmsswReleaseVersion = CMSSW_BASE_DIR.split("/")[-1]
print("Using CMSSW version " + cmsswReleaseVersion)

# Create directory for condor jobs
for list_file in all_dataset_lists.keys():
    dataset_name = list_file.replace(".list","")
    print("Preparing analyzer workflow for dataset: " + dataset_name + "\n")
    if not os.path.exists(Inputfiles_DIR + list_file):
        print(" (!) List file: " + list_file + " does not exist. Skipping!")
        continue

    list_all_runs = open(Inputfiles_DIR + list_file, "r")

    isData, max_runs_per_job, year = all_dataset_lists[list_file]

    Output_DIR = "analyzer_%s/"%(outputfile) + "%s/"%(dataset_name)
    Job_DIR = Condor_BASE_DIR + Output_DIR
    if os.path.exists(Job_DIR + "input_list.tgz"):
        print(" (!) Warning: condor directory " + Job_DIR + " is not empty. Skipping.")
        continue

    # Create condor directories
    os.system("mkdir -p " + Job_DIR)
    os.system("mkdir -p " + Job_DIR + "/log/")
    os.system("mkdir -p " + Job_DIR + "/out/")
    os.system("mkdir -p " + Job_DIR + "/err/")

    #####################################
    # Job splitting
    #####################################
    n_runs_in_job = 0
    n_jobs = 1
    list_runs_in_job = open(Job_DIR + "input_list_%i.txt"%(n_jobs), "w")
    for run in list_all_runs:
        # Close current list of runs and open the next one
        if n_runs_in_job >= max_runs_per_job:
            list_runs_in_job.close()
            n_runs_in_job = 0
            n_jobs += 1
            list_runs_in_job = open(Job_DIR + "input_list_%i.txt"%(n_jobs), "w")

        # Save run path in list
        list_runs_in_job.write(run)
        n_runs_in_job += 1
    list_runs_in_job.close()
    # Pack all txt files in a single tar file
    os.system("cd " + Job_DIR + "; tar czf input_list.tgz input_list_*.txt")
    os.system("cd " + Job_DIR + "; rm input_list_*.txt")

    ###################################################
    # Copy run script, executable, and required files
    ###################################################
    os.system("cp " + "%s/condor/run_job_LPC.sh"%(Analyzer_DIR) + " " + Job_DIR)
    os.system("cp " + "%s/bin/%s"%(Analyzer_DIR, analyzer) + " " + Job_DIR)
    Analyzer_Data_DIR = Analyzer_DIR + "data/"
    Job_Data_DIR = Job_DIR + "/data/"
    os.system("mkdir -p " + Job_Data_DIR)
    os.system("mkdir -p " + Job_Data_DIR + "Rocco/")
    os.system("cp " + "%s/Rocco/RoccoR%s.txt"%(Analyzer_Data_DIR, year) + " " + "%s/Rocco/"%(Job_Data_DIR))
    os.system("mkdir -p " + Job_Data_DIR + "btagSF/")
    os.system("cp " + "%s/btagSF/DeepCSV_94XSF_V3_B_F.csv"%(Analyzer_Data_DIR) + " " + "%s/btagSF/"%(Job_Data_DIR))
    # os.system("mkdir -p " + Job_Data_DIR + "leptonSF/%s"%(year))
    # os.system("cp " + "%s/leptonSF/%s/*.root"%(Analyzer_Data_DIR, year) + " " + "%s/leptonSF/%s/"%(Job_Data_DIR, year))
    os.system("mkdir -p " + Job_Data_DIR + "leptonSF/2016/")
    os.system("cp " + "%s/leptonSF/2016/*.root"%(Analyzer_Data_DIR) + " " + "%s/leptonSF/2016/"%(Job_Data_DIR))
    os.system("mkdir -p " + Job_Data_DIR + "pileup")
    pileup_file = "RunII_2016_data" if "2016" in year else "PileupReweight_Summer22"
    if "EE" in year: pileup_file += "EE"
    os.system("cp " + "%s/pileup/%s.root"%(Analyzer_Data_DIR, pileup_file) + " " + "%s/pileup/"%(Job_Data_DIR))

    #####################################
    # Create Condor JDL file
    #####################################
    jobfile_JDL = open(Job_DIR + "/task.jdl", "w+")
    jobfile_JDL.write("Universe  = vanilla" + "\n")
    jobfile_JDL.write("Executable = ./run_job_LPC.sh" + "\n")

    EOS_SUBPATH = os.getenv('LOGNAME') + "/" + Output_DIR
    args = outputfile + " $(I) " + isData + " " + year + " " + EOS_SUBPATH + " " + cmsswReleaseVersion
    jobfile_JDL.write("Arguments = " + args + "\n")

    jobfile_JDL.write("Log = log/job.$(Cluster).$(Process).log" + "\n")
    jobfile_JDL.write("Output = out/job.$(Cluster).$(Process).out" + "\n")
    jobfile_JDL.write("Error = err/job.$(Cluster).$(Process).err" + "\n")
    jobfile_JDL.write("x509userproxy = $ENV(X509_USER_PROXY)" + "\n")

    transfer_files = Job_DIR + "/run_job_LPC.sh, "
    transfer_files += Job_DIR + "/input_list.tgz, "
    transfer_files += Job_DIR + "/" + analyzer + ", "
    transfer_files += Job_Data_DIR + "/Rocco/RoccoR" + year + ".txt, "
    transfer_files += Job_Data_DIR + "/btagSF/DeepCSV_94XSF_V3_B_F.csv, "

    transfer_files += Job_Data_DIR + "/leptonSF/2016/EfficienciesAndSF_RunBtoF.root, "
    transfer_files += Job_Data_DIR + "/leptonSF/2016/EfficienciesAndSF_RunGtoH.root, "
    transfer_files += Job_Data_DIR + "/leptonSF/2016/RunBCDEF_SF_ID.root, "
    transfer_files += Job_Data_DIR + "/leptonSF/2016/RunBCDEF_SF_ISO.root, "
    transfer_files += Job_Data_DIR + "/leptonSF/2016/RunGH_SF_ID.root, "
    transfer_files += Job_Data_DIR + "/leptonSF/2016/RunGH_SF_ISO.root, "

    transfer_files += Job_Data_DIR + "/pileup/" + pileup_file + ".root"
    jobfile_JDL.write("transfer_input_files = " + transfer_files + "\n")

    jobfile_JDL.write("should_transfer_files = YES" + "\n")
    jobfile_JDL.write("when_to_transfer_output = ON_EXIT" + "\n\n# Resources request\n")
    jobfile_JDL.write("RequestMemory = 2000 \n\n# Jobs selection\n")

    jobfile_JDL.write("Queue I from (")
    for i in range(1, n_jobs+1):
        jobfile_JDL.write(str(i)+"\n")
    jobfile_JDL.write(")\n")
    jobfile_JDL.close()
