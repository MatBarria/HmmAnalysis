#ifndef LINKDEF_H_
#define LINKDEF_H_

#ifdef __CINT__
 
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclasses;

//#pragma link C++ defined_in "CustomPdfs.hh";
#pragma link C++ class RooCB+;
#pragma link C++ class RooDoubleCB+;
#pragma link C++ class RooFermi+;
#pragma link C++ class RooRelBW+;
#pragma link C++ class Triangle+;
#pragma link C++ class RooLevelledExp+;

#endif

#endif /*LINKDEF_H_*/
