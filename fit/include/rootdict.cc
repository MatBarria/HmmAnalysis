// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME rootdict
#define R__NO_DEPRECATION

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "ROOT/RConfig.hxx"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Header files passed as explicit arguments
#include "CustomPdfs.hh"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static void *new_RooCB(void *p = nullptr);
   static void *newArray_RooCB(Long_t size, void *p);
   static void delete_RooCB(void *p);
   static void deleteArray_RooCB(void *p);
   static void destruct_RooCB(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RooCB*)
   {
      ::RooCB *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RooCB >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("RooCB", ::RooCB::Class_Version(), "CustomPdfs.hh", 8,
                  typeid(::RooCB), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::RooCB::Dictionary, isa_proxy, 4,
                  sizeof(::RooCB) );
      instance.SetNew(&new_RooCB);
      instance.SetNewArray(&newArray_RooCB);
      instance.SetDelete(&delete_RooCB);
      instance.SetDeleteArray(&deleteArray_RooCB);
      instance.SetDestructor(&destruct_RooCB);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RooCB*)
   {
      return GenerateInitInstanceLocal(static_cast<::RooCB*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::RooCB*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_RooDoubleCB(void *p = nullptr);
   static void *newArray_RooDoubleCB(Long_t size, void *p);
   static void delete_RooDoubleCB(void *p);
   static void deleteArray_RooDoubleCB(void *p);
   static void destruct_RooDoubleCB(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RooDoubleCB*)
   {
      ::RooDoubleCB *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RooDoubleCB >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("RooDoubleCB", ::RooDoubleCB::Class_Version(), "CustomPdfs.hh", 40,
                  typeid(::RooDoubleCB), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::RooDoubleCB::Dictionary, isa_proxy, 4,
                  sizeof(::RooDoubleCB) );
      instance.SetNew(&new_RooDoubleCB);
      instance.SetNewArray(&newArray_RooDoubleCB);
      instance.SetDelete(&delete_RooDoubleCB);
      instance.SetDeleteArray(&deleteArray_RooDoubleCB);
      instance.SetDestructor(&destruct_RooDoubleCB);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RooDoubleCB*)
   {
      return GenerateInitInstanceLocal(static_cast<::RooDoubleCB*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::RooDoubleCB*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_RooFermi(void *p = nullptr);
   static void *newArray_RooFermi(Long_t size, void *p);
   static void delete_RooFermi(void *p);
   static void deleteArray_RooFermi(void *p);
   static void destruct_RooFermi(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RooFermi*)
   {
      ::RooFermi *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RooFermi >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("RooFermi", ::RooFermi::Class_Version(), "CustomPdfs.hh", 75,
                  typeid(::RooFermi), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::RooFermi::Dictionary, isa_proxy, 4,
                  sizeof(::RooFermi) );
      instance.SetNew(&new_RooFermi);
      instance.SetNewArray(&newArray_RooFermi);
      instance.SetDelete(&delete_RooFermi);
      instance.SetDeleteArray(&deleteArray_RooFermi);
      instance.SetDestructor(&destruct_RooFermi);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RooFermi*)
   {
      return GenerateInitInstanceLocal(static_cast<::RooFermi*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::RooFermi*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_RooRelBW(void *p = nullptr);
   static void *newArray_RooRelBW(Long_t size, void *p);
   static void delete_RooRelBW(void *p);
   static void deleteArray_RooRelBW(void *p);
   static void destruct_RooRelBW(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RooRelBW*)
   {
      ::RooRelBW *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RooRelBW >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("RooRelBW", ::RooRelBW::Class_Version(), "CustomPdfs.hh", 100,
                  typeid(::RooRelBW), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::RooRelBW::Dictionary, isa_proxy, 4,
                  sizeof(::RooRelBW) );
      instance.SetNew(&new_RooRelBW);
      instance.SetNewArray(&newArray_RooRelBW);
      instance.SetDelete(&delete_RooRelBW);
      instance.SetDeleteArray(&deleteArray_RooRelBW);
      instance.SetDestructor(&destruct_RooRelBW);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RooRelBW*)
   {
      return GenerateInitInstanceLocal(static_cast<::RooRelBW*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::RooRelBW*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_Triangle(void *p = nullptr);
   static void *newArray_Triangle(Long_t size, void *p);
   static void delete_Triangle(void *p);
   static void deleteArray_Triangle(void *p);
   static void destruct_Triangle(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Triangle*)
   {
      ::Triangle *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Triangle >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("Triangle", ::Triangle::Class_Version(), "CustomPdfs.hh", 128,
                  typeid(::Triangle), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Triangle::Dictionary, isa_proxy, 4,
                  sizeof(::Triangle) );
      instance.SetNew(&new_Triangle);
      instance.SetNewArray(&newArray_Triangle);
      instance.SetDelete(&delete_Triangle);
      instance.SetDeleteArray(&deleteArray_Triangle);
      instance.SetDestructor(&destruct_Triangle);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Triangle*)
   {
      return GenerateInitInstanceLocal(static_cast<::Triangle*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::Triangle*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_RooLevelledExp(void *p = nullptr);
   static void *newArray_RooLevelledExp(Long_t size, void *p);
   static void delete_RooLevelledExp(void *p);
   static void deleteArray_RooLevelledExp(void *p);
   static void destruct_RooLevelledExp(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RooLevelledExp*)
   {
      ::RooLevelledExp *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RooLevelledExp >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("RooLevelledExp", ::RooLevelledExp::Class_Version(), "CustomPdfs.hh", 161,
                  typeid(::RooLevelledExp), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::RooLevelledExp::Dictionary, isa_proxy, 4,
                  sizeof(::RooLevelledExp) );
      instance.SetNew(&new_RooLevelledExp);
      instance.SetNewArray(&newArray_RooLevelledExp);
      instance.SetDelete(&delete_RooLevelledExp);
      instance.SetDeleteArray(&deleteArray_RooLevelledExp);
      instance.SetDestructor(&destruct_RooLevelledExp);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RooLevelledExp*)
   {
      return GenerateInitInstanceLocal(static_cast<::RooLevelledExp*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::RooLevelledExp*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr RooCB::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *RooCB::Class_Name()
{
   return "RooCB";
}

//______________________________________________________________________________
const char *RooCB::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooCB*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int RooCB::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooCB*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *RooCB::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooCB*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *RooCB::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooCB*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr RooDoubleCB::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *RooDoubleCB::Class_Name()
{
   return "RooDoubleCB";
}

//______________________________________________________________________________
const char *RooDoubleCB::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooDoubleCB*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int RooDoubleCB::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooDoubleCB*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *RooDoubleCB::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooDoubleCB*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *RooDoubleCB::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooDoubleCB*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr RooFermi::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *RooFermi::Class_Name()
{
   return "RooFermi";
}

//______________________________________________________________________________
const char *RooFermi::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooFermi*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int RooFermi::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooFermi*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *RooFermi::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooFermi*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *RooFermi::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooFermi*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr RooRelBW::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *RooRelBW::Class_Name()
{
   return "RooRelBW";
}

//______________________________________________________________________________
const char *RooRelBW::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooRelBW*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int RooRelBW::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooRelBW*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *RooRelBW::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooRelBW*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *RooRelBW::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooRelBW*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr Triangle::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *Triangle::Class_Name()
{
   return "Triangle";
}

//______________________________________________________________________________
const char *Triangle::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Triangle*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int Triangle::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Triangle*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Triangle::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Triangle*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Triangle::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Triangle*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr RooLevelledExp::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *RooLevelledExp::Class_Name()
{
   return "RooLevelledExp";
}

//______________________________________________________________________________
const char *RooLevelledExp::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooLevelledExp*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int RooLevelledExp::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooLevelledExp*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *RooLevelledExp::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooLevelledExp*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *RooLevelledExp::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooLevelledExp*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void RooCB::Streamer(TBuffer &R__b)
{
   // Stream an object of class RooCB.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(RooCB::Class(),this);
   } else {
      R__b.WriteClassBuffer(RooCB::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_RooCB(void *p) {
      return  p ? new(p) ::RooCB : new ::RooCB;
   }
   static void *newArray_RooCB(Long_t nElements, void *p) {
      return p ? new(p) ::RooCB[nElements] : new ::RooCB[nElements];
   }
   // Wrapper around operator delete
   static void delete_RooCB(void *p) {
      delete (static_cast<::RooCB*>(p));
   }
   static void deleteArray_RooCB(void *p) {
      delete [] (static_cast<::RooCB*>(p));
   }
   static void destruct_RooCB(void *p) {
      typedef ::RooCB current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::RooCB

//______________________________________________________________________________
void RooDoubleCB::Streamer(TBuffer &R__b)
{
   // Stream an object of class RooDoubleCB.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(RooDoubleCB::Class(),this);
   } else {
      R__b.WriteClassBuffer(RooDoubleCB::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_RooDoubleCB(void *p) {
      return  p ? new(p) ::RooDoubleCB : new ::RooDoubleCB;
   }
   static void *newArray_RooDoubleCB(Long_t nElements, void *p) {
      return p ? new(p) ::RooDoubleCB[nElements] : new ::RooDoubleCB[nElements];
   }
   // Wrapper around operator delete
   static void delete_RooDoubleCB(void *p) {
      delete (static_cast<::RooDoubleCB*>(p));
   }
   static void deleteArray_RooDoubleCB(void *p) {
      delete [] (static_cast<::RooDoubleCB*>(p));
   }
   static void destruct_RooDoubleCB(void *p) {
      typedef ::RooDoubleCB current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::RooDoubleCB

//______________________________________________________________________________
void RooFermi::Streamer(TBuffer &R__b)
{
   // Stream an object of class RooFermi.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(RooFermi::Class(),this);
   } else {
      R__b.WriteClassBuffer(RooFermi::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_RooFermi(void *p) {
      return  p ? new(p) ::RooFermi : new ::RooFermi;
   }
   static void *newArray_RooFermi(Long_t nElements, void *p) {
      return p ? new(p) ::RooFermi[nElements] : new ::RooFermi[nElements];
   }
   // Wrapper around operator delete
   static void delete_RooFermi(void *p) {
      delete (static_cast<::RooFermi*>(p));
   }
   static void deleteArray_RooFermi(void *p) {
      delete [] (static_cast<::RooFermi*>(p));
   }
   static void destruct_RooFermi(void *p) {
      typedef ::RooFermi current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::RooFermi

//______________________________________________________________________________
void RooRelBW::Streamer(TBuffer &R__b)
{
   // Stream an object of class RooRelBW.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(RooRelBW::Class(),this);
   } else {
      R__b.WriteClassBuffer(RooRelBW::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_RooRelBW(void *p) {
      return  p ? new(p) ::RooRelBW : new ::RooRelBW;
   }
   static void *newArray_RooRelBW(Long_t nElements, void *p) {
      return p ? new(p) ::RooRelBW[nElements] : new ::RooRelBW[nElements];
   }
   // Wrapper around operator delete
   static void delete_RooRelBW(void *p) {
      delete (static_cast<::RooRelBW*>(p));
   }
   static void deleteArray_RooRelBW(void *p) {
      delete [] (static_cast<::RooRelBW*>(p));
   }
   static void destruct_RooRelBW(void *p) {
      typedef ::RooRelBW current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::RooRelBW

//______________________________________________________________________________
void Triangle::Streamer(TBuffer &R__b)
{
   // Stream an object of class Triangle.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Triangle::Class(),this);
   } else {
      R__b.WriteClassBuffer(Triangle::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_Triangle(void *p) {
      return  p ? new(p) ::Triangle : new ::Triangle;
   }
   static void *newArray_Triangle(Long_t nElements, void *p) {
      return p ? new(p) ::Triangle[nElements] : new ::Triangle[nElements];
   }
   // Wrapper around operator delete
   static void delete_Triangle(void *p) {
      delete (static_cast<::Triangle*>(p));
   }
   static void deleteArray_Triangle(void *p) {
      delete [] (static_cast<::Triangle*>(p));
   }
   static void destruct_Triangle(void *p) {
      typedef ::Triangle current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::Triangle

//______________________________________________________________________________
void RooLevelledExp::Streamer(TBuffer &R__b)
{
   // Stream an object of class RooLevelledExp.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(RooLevelledExp::Class(),this);
   } else {
      R__b.WriteClassBuffer(RooLevelledExp::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_RooLevelledExp(void *p) {
      return  p ? new(p) ::RooLevelledExp : new ::RooLevelledExp;
   }
   static void *newArray_RooLevelledExp(Long_t nElements, void *p) {
      return p ? new(p) ::RooLevelledExp[nElements] : new ::RooLevelledExp[nElements];
   }
   // Wrapper around operator delete
   static void delete_RooLevelledExp(void *p) {
      delete (static_cast<::RooLevelledExp*>(p));
   }
   static void deleteArray_RooLevelledExp(void *p) {
      delete [] (static_cast<::RooLevelledExp*>(p));
   }
   static void destruct_RooLevelledExp(void *p) {
      typedef ::RooLevelledExp current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::RooLevelledExp

namespace {
  void TriggerDictionaryInitialization_rootdict_Impl() {
    static const char* headers[] = {
"CustomPdfs.hh",
nullptr
    };
    static const char* includePaths[] = {
"/uscms_data/d3/mbarrial/higgsAnalysis/CMSSW_14_0_14/src/HmmAnalysis_actual/fit/include",
"/cvmfs/cms.cern.ch/el9_amd64_gcc12/lcg/root/6.30.03-ca7ca986842b225f6fc22ae84d705ed8/include/",
"/uscms_data/d3/mbarrial/higgsAnalysis/CMSSW_14_0_14/src/HmmAnalysis_actual/fit/include/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "rootdict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$CustomPdfs.hh")))  RooCB;
class __attribute__((annotate("$clingAutoload$CustomPdfs.hh")))  RooDoubleCB;
class __attribute__((annotate("$clingAutoload$CustomPdfs.hh")))  RooFermi;
class __attribute__((annotate("$clingAutoload$CustomPdfs.hh")))  RooRelBW;
class __attribute__((annotate("$clingAutoload$CustomPdfs.hh")))  Triangle;
class __attribute__((annotate("$clingAutoload$CustomPdfs.hh")))  RooLevelledExp;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "rootdict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "CustomPdfs.hh"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"RooCB", payloadCode, "@",
"RooDoubleCB", payloadCode, "@",
"RooFermi", payloadCode, "@",
"RooLevelledExp", payloadCode, "@",
"RooRelBW", payloadCode, "@",
"Triangle", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("rootdict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_rootdict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_rootdict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_rootdict() {
  TriggerDictionaryInitialization_rootdict_Impl();
}
