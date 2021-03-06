#ifndef _UTBuilder_Results_h__
#define _UTBuilder_Results_h__

#include <string>
#include <set>
#include <map>

#include "FuncParamsStructure.h"

namespace clang {
   class FunctionDecl;
   class RecordDecl;
   class TypedefNameDecl;
   class Type;
}


typedef std::set<const clang::FunctionDecl*> FunctionDeclSet;
typedef std::map<const clang::FunctionDecl*, FunctionDeclSet > FunctionDeclKeySetMap;

typedef std::map< std::string, const clang::FunctionDecl* > FunctionNameDeclMap;
   

template <typename T>
class Singleton
{
protected:
   Singleton() {};
   ~Singleton() {};
   
public:
   
   static T& get(void) 
   {
      static T instance;
      return instance;
   }
   
   
   
};

class FunctionsToUnitTest : public Singleton<FunctionsToUnitTest>
{
   
//    FunctionsToUnitTest(void) {};
//    ~FunctionsToUnitTest(void) {};
   
public:
   
//    static FunctionsToUnitTest& get(void);
   
   void clear();
   
   /**
    * each key is a FunctionDecl* of functions ro unit test 
    * each set stores the FunctionDecl* of the mock functions called inside the function to unit test
    *
    * this map is filled in two steps
    * 
    * 1st step: in FuncUTDefVisitor::VisitDecl
    * the map is filled with keys of FunctionDecl* to unit test and with empty set value
    * 
    * 2nd step: the mockVisitor::VisitCallExpr function
    * for each key of FunctionDecl* to unit test the set is filled with the FunctionDecl* of functions to mock
    */
   FunctionDeclKeySetMap      declKeySetMap; //functionsToUnitTestMap;
   
   // only for C: no overloaded and overriden functions
   FunctionNameDeclMap nameDeclMap; //functionsToUnitTestName;
   
};



class FunctionsToMock : public Singleton<FunctionsToMock>
{
//    FunctionsToMock(void) {};
//    ~FunctionsToMock(void) {};
   
public:
   
//    static FunctionsToMock& get(void);
   
   void clear();
   
   /**
    * each key is a FunctionDecl* of mock functions
    * each set stores the FunctionDecl* of the caller ( all the functions to unit test that call the mock function of the key 
    * this map is filled in the mockVisitor::VisitCallExpr function
    */
   FunctionDeclKeySetMap      declKeySetMap; // functionsToMockMap;
   
   // only for C: no overloaded and overriden functions
   FunctionNameDeclMap nameDeclMap;
   
};



class results {
  
   results(void) {};
   ~results(void) {};
   
public:
  
   static results& get(void);
   
   
   void clear();
   
   
   std::set<const clang::RecordDecl*>        structDecls;
 
   std::set<const clang::TypedefNameDecl*>   typedefNameDecls;
   std::set<std::string>                     includesForUnitTest;
   
   std::set<const clang::Type*>              functionDeclTypes;
   
//    std::vector<FuncParamsStruct> funcParamsStructures;
   
};



#endif // _UTBuilder_Results_h__

