//C++ INCLUDES
#include <iostream>
#include <math.h>
//ROOT INCLUDES
//LOCAL INCLUDES
#include "HggRazorSystematics.hh"

HggRazorSystematics::HggRazorSystematics( ){ };

HggRazorSystematics::HggRazorSystematics( TTree* tree ) : HggTree( tree ), _info( false ), _debug( false )
{

};

HggRazorSystematics::HggRazorSystematics( TTree* tree, TString processName, TString boxName, bool info, bool debug ) : HggTree( tree ), _info( info ), _debug( debug )
{
  //processName
  if ( processName == "" )
    {
      this->processName = "dummy_process";
    }
  else
    {
      this->processName = processName;
    }
  //boxName
  if ( boxName == "" )
    {
      this->boxName = "dummy_box";
    }
  else
    {
      this->boxName = boxName;
    }

  /*
  h2p = NULL;
  h2p_facScaleUp = NULL;
  h2p_facScaleDown = NULL;
  h2p_renScaleUp = NULL;
  h2p_renScaleDown = NULL;
  h2p_facRenScaleUp = NULL;
  h2p_facRenScaleDown = NULL;
  
  NEvents = NULL;
  SumScaleWeights = NULL;
  SumPdfWeights = NULL;
  */
};

HggRazorSystematics::~HggRazorSystematics()
{
  if ( _debug ) std::cout << "[DEBUG]: Entering Destructor" << std::endl;
  
  if ( this->h2p != NULL ) delete h2p;
  if ( this->h2p_facScaleUp != NULL ) delete h2p_facScaleUp;
  if ( this->h2p_facScaleDown != NULL ) delete h2p_facScaleDown;
  if ( this->h2p_renScaleUp != NULL ) delete h2p_renScaleUp;
  if ( this->h2p_renScaleDown != NULL ) delete h2p_renScaleDown;
  if ( this->h2p_facRenScaleUp != NULL ) delete h2p_facRenScaleUp;
  if ( this->h2p_facRenScaleDown != NULL ) delete h2p_facRenScaleDown;
  
  if ( this->NEvents != NULL ) delete NEvents;
  if ( this->SumScaleWeights != NULL ) delete SumScaleWeights;
  if ( this->SumPdfWeights != NULL ) delete SumPdfWeights;
  
  if ( _debug ) std::cout << "[DEBUG]: Finishing Destructor" << std::endl;
};

void HggRazorSystematics::PrintBinning()
{
  if ( _debug ) std::cout << "[INFO]: this is the binning for category <" << this->boxName << ">" << std::endl;
  if ( this->binningMap.size() == 0 ) std::cerr << "[WARNING]: no binning defined yet, please use object->SetBinningMap( yourMap );" << std::endl;
  for ( auto tmp : this->binningMap )
    {
      std::cout << "MR: " << tmp.first.first << "-" << tmp.first.second << " GeV --> Rsq: ";
      for ( auto tmp2 : tmp.second ) std::cout << tmp2 << ", ";
      std::cout << "\n";
    }
}

bool HggRazorSystematics::InitMrRsqTH2Poly( int mode )
{
  if ( mode == 0 )
    {
      if ( _debug ) std::cout << "[INFO]: Creating TH2Poly mode: " << mode << std::endl;
      if ( this->binningMap.size() == 0 )
	{
	  std::cerr << "[ERROR]: Imposible to create TH2Poly; no binning defined yet, please use object->SetBinningMap( yourMap );" << std::endl;
	  return false;
	}
      h2p = new TH2Poly(this->processName+"+nominal", "", 150, 10000, 0, 1);
      h2p_facScaleUp      = new TH2Poly(this->processName+"_facScaleUp", "", 150, 10000, 0, 1);
      h2p_facScaleDown    = new TH2Poly(this->processName+"_facScaleDown", "", 150, 10000, 0, 1);
      h2p_renScaleUp      = new TH2Poly(this->processName+"_renScaleUp", "", 150, 10000, 0, 1);
      h2p_renScaleDown    = new TH2Poly(this->processName+"_renScaleDown", "", 150, 10000, 0, 1);
      h2p_facRenScaleUp   = new TH2Poly(this->processName+"_facRenScaleUp", "", 150, 10000, 0, 1);
      h2p_facRenScaleDown = new TH2Poly(this->processName+"_facRenScaleDown", "", 150, 10000, 0, 1);
      h2p_JesUp           = new TH2Poly(this->processName+"_JesUp", "", 150, 10000, 0, 1);
      h2p_JesDown         = new TH2Poly(this->processName+"_JesDown", "", 150, 10000, 0, 1);
      for( int i = 0; i < n_PdfSys; i++ )
	{
	  TString PdfSysName = Form(this->processName+"_PdfEigenVect_%d",i);
	  h2p_Pdf[i] = new TH2Poly( PdfSysName, "", 150, 10000, 0, 1);
	}
      //btag
      h2p_btagUp   = new TH2Poly(this->processName+"_btagUp", "", 150, 10000, 0, 1);
      h2p_btagDown = new TH2Poly(this->processName+"_btagDown", "", 150, 10000, 0, 1);
      //misstag
      h2p_misstagUp   = new TH2Poly(this->processName+"_misstagUp", "", 150, 10000, 0, 1);
      h2p_misstagDown = new TH2Poly(this->processName+"_misstagDown", "", 150, 10000, 0, 1);
      //adding bins
      for ( auto tmp : this->binningMap )
	{
	  int RsqSize = tmp.second.size();
	  for ( int i = 0; i < RsqSize-1; i++ )
	    {
	      h2p->AddBin( tmp.first.first, tmp.second.at(i), tmp.first.second, tmp.second.at(i+1) );
	      h2p_facScaleUp->AddBin( tmp.first.first, tmp.second.at(i), tmp.first.second, tmp.second.at(i+1) );
	      h2p_facScaleDown->AddBin( tmp.first.first, tmp.second.at(i), tmp.first.second, tmp.second.at(i+1) );
	      h2p_renScaleUp->AddBin( tmp.first.first, tmp.second.at(i), tmp.first.second, tmp.second.at(i+1) );
	      h2p_renScaleDown->AddBin( tmp.first.first, tmp.second.at(i), tmp.first.second, tmp.second.at(i+1) );
	      h2p_facRenScaleUp->AddBin( tmp.first.first, tmp.second.at(i), tmp.first.second, tmp.second.at(i+1) );
	      h2p_facRenScaleDown->AddBin( tmp.first.first, tmp.second.at(i), tmp.first.second, tmp.second.at(i+1) );
	      h2p_JesUp->AddBin( tmp.first.first, tmp.second.at(i), tmp.first.second, tmp.second.at(i+1) );
	      h2p_JesDown->AddBin( tmp.first.first, tmp.second.at(i), tmp.first.second, tmp.second.at(i+1) );
	      for ( int ipdf = 0; ipdf < n_PdfSys; ipdf++ ) h2p_Pdf[ipdf]->AddBin( tmp.first.first, tmp.second.at(i), tmp.first.second, tmp.second.at(i+1) );
	      h2p_btagUp->AddBin( tmp.first.first, tmp.second.at(i), tmp.first.second, tmp.second.at(i+1) );
	      h2p_btagDown->AddBin( tmp.first.first, tmp.second.at(i), tmp.first.second, tmp.second.at(i+1) );
	      h2p_misstagUp->AddBin( tmp.first.first, tmp.second.at(i), tmp.first.second, tmp.second.at(i+1) );
	      h2p_misstagDown->AddBin( tmp.first.first, tmp.second.at(i), tmp.first.second, tmp.second.at(i+1) );
	    }
	}
      
      return true;
    }
  else if ( mode == 1 )
    {
      if ( _debug ) std::cout << "[INFO]: Creating TH2Poly mode: " << mode << std::endl;
      if ( this->binningVect.size() == 0 )
	{
	  std::cerr << "[ERROR]: Imposible to create TH2Poly; no binning defined yet, please use object->SetBinningVect( yourVect );" << std::endl;
	  return false;
	}

      
      h2p = new TH2Poly(this->processName+"+nominal", "", 150, 10000, 0, 1);

      h2p_facScaleUp      = new TH2Poly(this->processName+"_facScaleUp", "", 150, 10000, 0, 1);
      h2p_facScaleDown    = new TH2Poly(this->processName+"_facScaleDown", "", 150, 10000, 0, 1);

      h2p_renScaleUp      = new TH2Poly(this->processName+"_renScaleUp", "", 150, 10000, 0, 1);
      h2p_renScaleDown    = new TH2Poly(this->processName+"_renScaleDown", "", 150, 10000, 0, 1);

      h2p_facRenScaleUp   = new TH2Poly(this->processName+"_facRenScaleUp", "", 150, 10000, 0, 1);
      h2p_facRenScaleDown = new TH2Poly(this->processName+"_facRenScaleDown", "", 150, 10000, 0, 1);

      h2p_JesUp           = new TH2Poly(this->processName+"_JesUp", "", 150, 10000, 0, 1);
      h2p_JesDown         = new TH2Poly(this->processName+"_JesDown", "", 150, 10000, 0, 1);
      
      for( int i = 0; i < n_PdfSys; i++ )
	{
	  TString PdfSysName = Form(this->processName+"_PdfEigenVect_%d",i);
	  h2p_Pdf[i] = new TH2Poly( PdfSysName, "", 150, 10000, 0, 1);
	}
      
      h2p_btagUp           = new TH2Poly(this->processName+"_btagUp", "", 150, 10000, 0, 1);
      h2p_btagDown         = new TH2Poly(this->processName+"_btagDown", "", 150, 10000, 0, 1);
      
      h2p_misstagUp        = new TH2Poly(this->processName+"_misstagUp", "", 150, 10000, 0, 1);
      h2p_misstagDown      = new TH2Poly(this->processName+"_misstagDown", "", 150, 10000, 0, 1);
      
      for ( auto tmp : binningVect )
	{
	  if ( _debug ) std::cout << "adding bin: " << tmp[0] << "," <<  tmp[1] << "," << tmp[2] << "," << tmp[3] << std::endl;
	  h2p->AddBin(tmp[0], tmp[1], tmp[2], tmp[3]);

	  h2p_facScaleUp->AddBin(tmp[0], tmp[1], tmp[2], tmp[3]);
	  h2p_facScaleDown->AddBin(tmp[0], tmp[1], tmp[2], tmp[3]);
	  
	  h2p_renScaleUp->AddBin(tmp[0], tmp[1], tmp[2], tmp[3]);
	  h2p_renScaleDown->AddBin(tmp[0], tmp[1], tmp[2], tmp[3]);
	  
	  h2p_facRenScaleUp->AddBin(tmp[0], tmp[1], tmp[2], tmp[3]);
	  h2p_facRenScaleDown->AddBin(tmp[0], tmp[1], tmp[2], tmp[3]);
	  
	  h2p_JesUp->AddBin(tmp[0], tmp[1], tmp[2], tmp[3]);
	  h2p_JesDown->AddBin(tmp[0], tmp[1], tmp[2], tmp[3]);
	  
	  for ( int ipdf = 0; ipdf < n_PdfSys; ipdf++ ) h2p_Pdf[ipdf]->AddBin(tmp[0], tmp[1], tmp[2], tmp[3]);

	  h2p_btagUp->AddBin(tmp[0], tmp[1], tmp[2], tmp[3]);
	  h2p_btagDown->AddBin(tmp[0], tmp[1], tmp[2], tmp[3]);
	  
	  h2p_misstagUp->AddBin(tmp[0], tmp[1], tmp[2], tmp[3]);
	  h2p_misstagDown->AddBin(tmp[0], tmp[1], tmp[2], tmp[3]);
	}

      return true;
    }

  return true;
};

void HggRazorSystematics::Loop()
{
  if ( _debug ) std::cout << "[DEBUG]: Entering Loop" << std::endl;
  if (fChain == 0)
    {
      std::cerr << "[ERROR]: TTree is NULL;" << std::endl;
      return;
    }
  if ( h2p == NULL )
    {
      std::cerr << "[ERROR]: TH2Poly has not been created; impossible to fill TH2Poly, please use: obj->InitMrRsqTH2Poly();" << std::endl;
      return;
    }
  
  if ( (this->NEvents == NULL || this->SumScaleWeights == NULL || this->SumPdfWeights == NULL ) && this->processName != "signal" )
    {
      std::cerr << "[ERROR]: NEvents and/or SumScaleWeights and/or SumPdfWeights have not been set" << std::endl;
      return;
    }
  
  if ( _debug ) std::cout << "[DEBUG]: Setting N_events and N_facScale" << std::endl;
  
  float N_events;
  //factorization/renormalization 
  const int n_facScaleSys = 6;
  float N_facScale[n_facScaleSys];
  //PDF
  float N_Pdf[n_PdfSys];
  if ( this->processName != "signal" )
    {
      N_events= this->NEvents->GetBinContent(1);
      for ( int i = 0; i < n_facScaleSys; i++ ) N_facScale[i] = this->SumScaleWeights->GetBinContent( i+1 );
      for ( int i = 0; i < n_PdfSys; i++ ) N_Pdf[i] = this->SumPdfWeights->GetBinContent( i+1 );
    }
  
  if ( _debug ) std::cout << "[DEBUG]: Passed N_events, N_facScale, N_PDF" << std::endl;
  
  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;
  double total_in = 0, total_rm = 0;
  
  for (Long64_t jentry=0; jentry < nentries; jentry++ )
    {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      float commonW = this->Lumi*weight*pileupWeight*btagCorrFactor;//including btag weight
      
      if ( this->processName == "signal" )
	{
	  if ( t1Rsq < 1.0 ) h2p->Fill( MR, t1Rsq, this->Lumi*weight );
	  else h2p->Fill( MR, 0.999, this->Lumi*weight);
	}
      else
	{
	  if ( t1Rsq < 1.0 )
	    {
	      //std::cout << "PDF: " << weight << " " << weight*sf_pdf->at(0)*N_events/N_Pdf[0] << std::endl;
	      //std::cout << "facScale: "<<  weight << " " << weight*sf_facScaleUp*N_events/N_facScale[0] << std::endl;
	      h2p->Fill( MR, t1Rsq, commonW );
	      
	      h2p_facScaleUp->Fill( MR, t1Rsq, commonW*sf_facScaleUp*N_events/N_facScale[0] );
	      h2p_facScaleDown->Fill( MR, t1Rsq, commonW*sf_facScaleDown*N_events/N_facScale[1] );
	    
	      h2p_renScaleUp->Fill( MR, t1Rsq, commonW*sf_renScaleUp*N_events/N_facScale[2] );
	      h2p_renScaleDown->Fill( MR, t1Rsq, commonW*sf_renScaleDown*N_events/N_facScale[3] );
	      
	      h2p_facRenScaleUp->Fill( MR, t1Rsq, commonW*sf_facRenScaleUp*N_events/N_facScale[4] );
	      h2p_facRenScaleDown->Fill( MR, t1Rsq, commonW*sf_facRenScaleDown*N_events/N_facScale[5] );
	      
	      //PDF
	      for ( int ipdf = 0; ipdf < n_PdfSys; ipdf++ )
		{
		  h2p_Pdf[ipdf]->Fill( MR, t1Rsq, commonW*sf_pdf->at(ipdf)*N_events/N_Pdf[ipdf] );
		}
	      
	      h2p_btagUp->Fill( MR, t1Rsq, commonW*sf_btagUp );
	      h2p_btagDown->Fill( MR, t1Rsq, commonW*sf_btagDown );
	      
	      h2p_misstagUp->Fill( MR, t1Rsq, commonW*sf_bmistagUp );
	      h2p_misstagDown->Fill( MR, t1Rsq, commonW*sf_bmistagDown );
	      
	    }
	  else
	    {
	      h2p->Fill( MR, 0.999, commonW );
	      
	      h2p_facScaleUp->Fill( MR, 0.999, commonW*sf_facScaleUp*N_events/N_facScale[0] );
	      h2p_facScaleDown->Fill( MR, 0.999, commonW*sf_facScaleDown*N_events/N_facScale[1] );
	      
	      h2p_renScaleUp->Fill( MR, 0.999, commonW*sf_renScaleUp*N_events/N_facScale[2] );
	      h2p_renScaleDown->Fill( MR, 0.999, commonW*sf_renScaleDown*N_events/N_facScale[3] );
	      
	      h2p_facRenScaleUp->Fill( MR, 0.999, commonW*sf_facRenScaleUp*N_events/N_facScale[4] );
	      h2p_facRenScaleDown->Fill( MR, 0.999, commonW*sf_facRenScaleDown*N_events/N_facScale[5] );
	      
	      //PDF
	      for ( int ipdf = 0; ipdf < n_PdfSys; ipdf++ )
		{
		  h2p_Pdf[ipdf]->Fill( MR, 0.999, commonW*sf_pdf->at(ipdf)*N_events/N_Pdf[ipdf] );
		}
	      
	      h2p_btagUp->Fill( MR, 0.999, commonW*sf_btagUp );
	      h2p_btagDown->Fill( MR, 0.999, commonW*sf_btagDown );
	      
	      h2p_misstagUp->Fill( MR, 0.999, commonW*sf_bmistagUp );
	      h2p_misstagDown->Fill( MR, 0.999, commonW*sf_bmistagDown );
	    }
	  
	  //JES Up
	  if ( t1Rsq_JESUp < 1.0 ) h2p_JesUp->Fill( MR_JESUp, t1Rsq_JESUp, commonW );
	  else h2p_JesUp->Fill( MR_JESUp, 0.999, commonW );
	  //JES Down
	  if ( t1Rsq_JESDown < 1.0 ) h2p_JesDown->Fill( MR_JESDown, t1Rsq_JESDown, commonW );
	  else h2p_JesDown->Fill( MR_JESDown, 0.999, commonW );
	}
    }
  
  if ( _debug ) std::cout << "[DEBUG]: Finishing Loop" << std::endl;
};

void HggRazorSystematics::LoopNominal()
  {
    if ( _debug ) std::cout << "[DEBUG]: Entering Loop" << std::endl;
  if (fChain == 0)
    {
      std::cerr << "[ERROR]: TTree is NULL;" << std::endl;
      return;
    }
  if ( h2p == NULL )
    {
      std::cerr << "[ERROR]: TH2Poly has not been created; impossible to fill TH2Poly, please use: obj->InitMrRsqTH2Poly();" << std::endl;
      return;
    }
  
  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;
  double total_in = 0, total_rm = 0;
  
  for (Long64_t jentry=0; jentry < nentries; jentry++ )
    {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      
      if ( t1Rsq < 1.0 )
	{
	  if( processName == "NR" )
	    {
	      h2p->Fill( MR, t1Rsq, this->NR_kf*this->Lumi*weight*pileupWeight );
	    }
	  else if( processName == "signal" )
	    {
	      h2p->Fill( MR, t1Rsq, this->Lumi*weight );
	    }
	  else
	    {
	      h2p->Fill( MR, t1Rsq, this->Lumi*weight*pileupWeight );
	    }
	}
      else
	{
	  if( processName == "NR" )
	    {
	      h2p->Fill( MR, 0.999, this->NR_kf*this->Lumi*weight*pileupWeight );
	    }
	  else if ( processName == "signal" )
	    {
	      h2p->Fill( MR, 0.999, this->Lumi*weight );
	    }
	  else
	    {
	      h2p->Fill( MR, 0.999, this->Lumi*weight*pileupWeight );
	    }
	}
    }

  if ( _debug ) std::cout << "[DEBUG]: Finishing Loop" << std::endl;
};

float HggRazorSystematics::GetHighPtGB( double mr, double r2 )
{
  int mr_bin = -1;
  int r2_bin = -1;
  return 0;
};

float HggRazorSystematics::GetHighResGB( double mr, double r2 )
{
  int mr_bin = -1;
  int r2_bin = -1;
  return 0;
};



float HggRazorSystematics::GetYields( float mr, float rsq, float mgg_l, float mgg_h )
{
  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;
  float sel_events = .0;
  
  for (Long64_t jentry=0; jentry < nentries; jentry++ )
    {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      if (  MR > mr && Rsq > rsq
	    && mGammaGamma > mgg_l && mGammaGamma < mgg_h
	    && fabs( pho1Eta ) < 1.48 && fabs( pho2Eta ) < 1.48 && pho1Pt > 25. && pho2Pt > 25.
	    && ( pho1Pt > 40. || pho2Pt > 40. ) && pTGammaGamma > 20. )
	{
	  sel_events += weight*this->Lumi;
	}
    }
  if ( _debug ) std::cout << "[DEBUG]: Finishing Loop" << std::endl;
  return sel_events;
};

float HggRazorSystematics::GetYields( float mr, float rsq, float mgg_l, float mgg_h, double& err )
{
  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;
  float sel_events = .0;
  err = .0;
  for (Long64_t jentry=0; jentry < nentries; jentry++ )
    {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      if (  MR > mr && Rsq > rsq
	    && mGammaGamma > mgg_l && mGammaGamma < mgg_h
	    && fabs( pho1Eta ) < 1.48 && fabs( pho2Eta ) < 1.48 && pho1Pt > 25. && pho2Pt > 25.
	    && ( pho1Pt > 40. || pho2Pt > 40. ) && pTGammaGamma > 20. )
	{
	  sel_events += weight*this->Lumi;
	  err += weight*this->Lumi*weight*this->Lumi;
	}
    }
  if ( _debug ) std::cout << "[DEBUG]: Finishing Loop" << std::endl;
  err = sqrt(err);
  return sel_events;
};

bool HggRazorSystematics::WriteOutput( TString outName )
{
  if ( _debug ) std::cout << "[DEBUG]: Entering WriteOutput" << std::endl;
  this->fout = new TFile( outName + "_" + this->processName + ".root", "recreate");
  if ( h2p != NULL ) h2p->Write( this->boxName + "_histo" );
  if ( h2p_facScaleUp != NULL ) h2p_facScaleUp->Write( this->boxName + "_histo_facScaleUp" );
  if ( h2p_facScaleDown != NULL ) h2p_facScaleDown->Write( this->boxName + "_histo_facScaleDown" );
  if ( h2p_renScaleUp != NULL ) h2p_renScaleUp->Write( this->boxName + "_histo_renScaleUp" );
  if ( h2p_renScaleDown != NULL ) h2p_renScaleDown->Write( this->boxName + "_histo_renScaleDown" );
  if ( h2p_facRenScaleUp != NULL ) h2p_facRenScaleUp->Write( this->boxName + "_histo_facRenScaleUp" );
  if ( h2p_facRenScaleDown != NULL ) h2p_facRenScaleDown->Write( this->boxName + "_histo_facRenScaleDown" );
  if ( h2p_JesUp != NULL ) h2p_JesUp->Write( this->boxName + "_histo_JesUp" );
  if ( h2p_JesDown != NULL ) h2p_JesDown->Write( this->boxName + "_histo_JesDown" );
  for ( int ipdf = 0; ipdf < n_PdfSys; ipdf++ )
    {
      TString PdfTH2PName = Form("histo_PdfEigenVector%d", ipdf );
      if ( h2p_Pdf[ipdf] != NULL ) h2p_Pdf[ipdf]->Write( this->boxName + "_"  + PdfTH2PName );
    }
  if ( h2p_JesUp != NULL ) h2p_btagUp->Write( this->boxName + "_histo_btagUp" );
  if ( h2p_JesDown != NULL ) h2p_btagDown->Write( this->boxName + "_histo_btagDown" );
  if ( h2p_JesUp != NULL ) h2p_misstagUp->Write( this->boxName + "_histo_misstagUp" );
  if ( h2p_JesDown != NULL ) h2p_misstagDown->Write( this->boxName + "_histo_misstagDown" );
   
  fout->Close();
  if ( _debug ) std::cout << "[DEBUG]: Finishing WriteOutput" << std::endl;
  return true;
};

float HggRazorSystematics::GetHggBF( )
{
  return hggBF;
};

bool HggRazorSystematics::SetNeventsHisto( TH1F* histo )
{
  this->NEvents = NULL;
  if ( histo == NULL )
    {
      std::cerr << "[ERROR]: Nevents histogram provided is equal to NULL" << std::endl;
      return false;
    }
  this->NEvents = new TH1F( *histo );
  return true;
};

bool HggRazorSystematics::SetFacScaleWeightsHisto( TH1F* histo )
{
  this->SumScaleWeights = NULL;
  if ( histo == NULL )
    {
      std::cerr << "[ERROR]: Scale histogram provided is equal to NULL" << std::endl;
      return false;
    }
  this->SumScaleWeights = new TH1F( *histo );
  return true;
};

bool HggRazorSystematics::SetPdfWeightsHisto( TH1F* histo )
{
  this->SumPdfWeights = NULL;
  if ( histo == NULL )
    {
      std::cerr << "[ERROR]: PDF histogram provided is equal to NULL" << std::endl;
      return false;
    }
  this->SumPdfWeights = new TH1F( *histo );
  return true;
};

float HggRazorSystematics::GetNominalYield( float mr, float rsq )
{
  int bin = h2p->FindBin( mr+10, rsq+0.0001 );
  return h2p->GetBinContent( bin );
};

std::pair<float, float> HggRazorSystematics::GetFacScaleSystematic( float mr, float rsq )
{
  int bin = h2p->FindBin( mr+10, rsq+0.0001 );
  float smhY      = h2p->GetBinContent( bin );
  float smhY_Up   = h2p_facScaleUp->GetBinContent( bin )-smhY;
  float smhY_Down = h2p_facScaleDown->GetBinContent( bin )-smhY;
  //std::cout << "mr: " << mr << " rsq: " << rsq << "; up: " << smhY_Up << ", down: " << smhY_Down << std::endl;
  return std::make_pair( smhY_Up, smhY_Down );
};

std::pair<float, float> HggRazorSystematics::GetRenScaleSystematic( float mr, float rsq )
{
  int bin = h2p->FindBin( mr+10, rsq+0.0001 );
  float smhY      = h2p->GetBinContent( bin );
  float smhY_Up   = h2p_renScaleUp->GetBinContent( bin ) - smhY;
  float smhY_Down = h2p_renScaleDown->GetBinContent( bin ) - smhY;
  return std::make_pair( smhY_Up, smhY_Down );
};

std::pair<float, float> HggRazorSystematics::GetFacRenScaleSystematic( float mr, float rsq )
{
  int bin = h2p->FindBin( mr+10, rsq+0.0001 );
  float smhY      = h2p->GetBinContent( bin );
  float smhY_Up   = h2p_facRenScaleUp->GetBinContent( bin ) - smhY;
  float smhY_Down = h2p_facRenScaleDown->GetBinContent( bin ) - smhY;
  return std::make_pair( smhY_Up, smhY_Down );
};

std::pair<float, float> HggRazorSystematics::GetJesSystematic( float mr, float rsq )
{
  int bin = h2p->FindBin( mr+10, rsq+0.0001 );
  float smhY      = h2p->GetBinContent( bin );
  float smhY_Up   = h2p_JesUp->GetBinContent( bin ) - smhY;
  float smhY_Down = h2p_JesDown->GetBinContent( bin ) - smhY;
  return std::make_pair( smhY_Up, smhY_Down );
};

std::pair<float, float> HggRazorSystematics::GetBtagSystematic( float mr, float rsq )
{
  int bin = h2p->FindBin( mr+10, rsq+0.0001 );
  float smhY      = h2p->GetBinContent( bin );
  float smhY_Up   = h2p_btagUp->GetBinContent( bin ) - smhY;
  float smhY_Down = h2p_btagDown->GetBinContent( bin ) - smhY;
  return std::make_pair( smhY_Up, smhY_Down );
};

std::pair<float, float> HggRazorSystematics::GetMisstagSystematic( float mr, float rsq )
{
  int bin = h2p->FindBin( mr+10, rsq+0.0001 );
  float smhY      = h2p->GetBinContent( bin );
  float smhY_Up   = h2p_misstagUp->GetBinContent( bin ) - smhY;
  float smhY_Down = h2p_misstagDown->GetBinContent( bin ) - smhY;
  return std::make_pair( smhY_Up, smhY_Down );
};

float HggRazorSystematics::GetPdfSystematic( int i, float mr, float rsq )
{
  int bin = h2p->FindBin( mr+10, rsq+0.0001 );
  float smhY      = h2p->GetBinContent( bin );
  float smhY_Un   = h2p_Pdf[i]->GetBinContent( bin ) - smhY;
  return smhY_Un;
};
