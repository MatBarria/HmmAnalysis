#include <assert.h>
#include <fstream>
#include <iostream>
#include <sstream>
// LOCAL INCLUDES
#include "CommandLineInput.hh"

// std::string ntupleDir =
// "/Users/cmorgoth/Work/data/HggRazorRun2/Analysis13TeV/CMSSW_7_6_March15_Ntuples/";
std::string ntupleDir = "../root_io/tuples/";

int main(int argc, char *argv[]) {

    std::string inputCF = ParseCommandLine(argc, argv, "-inputCF=");
    if (inputCF == "") {
        std::cerr << "[ERROR]: please provide an input file using "
                     "--inputCF=<path_to_file>"
                  << std::endl;
        return -1;
    }

    std::ifstream ifs(inputCF.c_str(), std::ifstream::in);
    assert(ifs);

    std::string configCardName;
    int binNumber = 0;
    while (ifs.good()) {
        std::string category, MR_l, MR_h, Rsq_l, Rsq_h, SMH, Signal, Bkg_f1;
        Bkg_f1 = "singleExp";
        ifs >> configCardName;
        if (ifs.eof())
            break;
        std::cout << "[INFO]: opening configDataCard: " << configCardName
                  << std::endl;
        std::ifstream tmpF(configCardName.c_str(), std::ifstream::in);
        assert(tmpF);
        while (tmpF.good()) {
            std::stringstream SMH_sys;
            std::stringstream Signal_sys;
            tmpF >> category >> MR_l >> MR_h >> Rsq_l >> Rsq_h >> SMH;
            if (category.find("#") != std::string::npos)
                continue;
            std::string tmp1;
            SMH_sys << "\"";
            for (int i = 0; i < 68; i++) {
                tmpF >> tmp1;
                if (i < 67)
                    SMH_sys << tmp1 << " ";
                else
                    SMH_sys << tmp1 << "\"";
            }
            tmpF >> Signal;
            Signal_sys << "\"";
            for (int i = 0; i < 68; i++) {
                tmpF >> tmp1;
                if (i < 67)
                    Signal_sys << tmp1 << " ";
                else
                    Signal_sys << tmp1 << "\"";
            }

            if (tmpF.eof())
                break;
            /*std::cout << category << "\t" << MR_l << "\t" << MR_h << "\t" <<
              Rsq_l << "\t" << Rsq_h << "\t" << SMH << "\t" << SMH_sys.str()
              << "\t" << Signal << "\t"  << Signal_sys.str() << std::endl;
            */

            std::cout << "./MakeFitRun2 " << "--inputFile=" << ntupleDir
                      << "DoubleEG_Run2015_CMSSW_7_6_March15_GoodLumi.root"
                      << " --inputFileSignal=" << ntupleDir
                      << "T2bH-Hgg-sbm300-sbw1-chi2m230-chi2w0p1-chi1m100_"
                         "CMSSW_7_6_March15_1pb_weighted.root"
                      << " --inputFileSMH=" << ntupleDir
                      << "SM-Higgs_1pb_weighted.root"
                      << " --treeName=HggRazor --runPeriod=run2 "
                         "--dataMode=data+signal --fitMode=datacard --category="
                      << category << " --LowMRcut=" << MR_l
                      << " --HighMRcut=" << MR_h << " --LowRSQcut=" << Rsq_l
                      << " --HighRSQcut=" << Rsq_h << " --f1=" << Bkg_f1
                      << " --SMH_Yield=" << SMH << " --SMH_CL=" << SMH_sys.str()
                      << " --Signal_Yield=" << Signal
                      << " --Signal_CL=" << Signal_sys.str()
                      << " --binNumber=" << binNumber << std::endl;
            binNumber++;
        }
        tmpF.close();
    }
    ifs.close();

    return 0;
}
