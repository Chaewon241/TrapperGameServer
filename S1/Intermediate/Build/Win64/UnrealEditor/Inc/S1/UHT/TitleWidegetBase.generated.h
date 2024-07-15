// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "TitleWidegetBase.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef S1_TitleWidegetBase_generated_h
#error "TitleWidegetBase.generated.h already included, missing '#pragma once' in TitleWidegetBase.h"
#endif
#define S1_TitleWidegetBase_generated_h

#define FID_S1_Source_S1_TitleWidegetBase_h_15_SPARSE_DATA
#define FID_S1_Source_S1_TitleWidegetBase_h_15_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_S1_Source_S1_TitleWidegetBase_h_15_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_S1_Source_S1_TitleWidegetBase_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execOnJoinButton); \
	DECLARE_FUNCTION(execOnLoginButton);


#define FID_S1_Source_S1_TitleWidegetBase_h_15_ACCESSORS
#define FID_S1_Source_S1_TitleWidegetBase_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUTitleWidegetBase(); \
	friend struct Z_Construct_UClass_UTitleWidegetBase_Statics; \
public: \
	DECLARE_CLASS(UTitleWidegetBase, UUserWidget, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/S1"), NO_API) \
	DECLARE_SERIALIZER(UTitleWidegetBase)


#define FID_S1_Source_S1_TitleWidegetBase_h_15_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UTitleWidegetBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UTitleWidegetBase(UTitleWidegetBase&&); \
	NO_API UTitleWidegetBase(const UTitleWidegetBase&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UTitleWidegetBase); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UTitleWidegetBase); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UTitleWidegetBase) \
	NO_API virtual ~UTitleWidegetBase();


#define FID_S1_Source_S1_TitleWidegetBase_h_12_PROLOG
#define FID_S1_Source_S1_TitleWidegetBase_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_S1_Source_S1_TitleWidegetBase_h_15_SPARSE_DATA \
	FID_S1_Source_S1_TitleWidegetBase_h_15_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_S1_Source_S1_TitleWidegetBase_h_15_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_S1_Source_S1_TitleWidegetBase_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_S1_Source_S1_TitleWidegetBase_h_15_ACCESSORS \
	FID_S1_Source_S1_TitleWidegetBase_h_15_INCLASS_NO_PURE_DECLS \
	FID_S1_Source_S1_TitleWidegetBase_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> S1_API UClass* StaticClass<class UTitleWidegetBase>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_S1_Source_S1_TitleWidegetBase_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
