// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "TitleGM.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef S1_TitleGM_generated_h
#error "TitleGM.generated.h already included, missing '#pragma once' in TitleGM.h"
#endif
#define S1_TitleGM_generated_h

#define FID_S1_Source_S1_TitleGM_h_15_SPARSE_DATA
#define FID_S1_Source_S1_TitleGM_h_15_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_S1_Source_S1_TitleGM_h_15_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_S1_Source_S1_TitleGM_h_15_RPC_WRAPPERS_NO_PURE_DECLS
#define FID_S1_Source_S1_TitleGM_h_15_ACCESSORS
#define FID_S1_Source_S1_TitleGM_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesATitleGM(); \
	friend struct Z_Construct_UClass_ATitleGM_Statics; \
public: \
	DECLARE_CLASS(ATitleGM, AGameModeBase, COMPILED_IN_FLAGS(0 | CLASS_Transient | CLASS_Config), CASTCLASS_None, TEXT("/Script/S1"), NO_API) \
	DECLARE_SERIALIZER(ATitleGM)


#define FID_S1_Source_S1_TitleGM_h_15_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ATitleGM(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ATitleGM(ATitleGM&&); \
	NO_API ATitleGM(const ATitleGM&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ATitleGM); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ATitleGM); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ATitleGM) \
	NO_API virtual ~ATitleGM();


#define FID_S1_Source_S1_TitleGM_h_12_PROLOG
#define FID_S1_Source_S1_TitleGM_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_S1_Source_S1_TitleGM_h_15_SPARSE_DATA \
	FID_S1_Source_S1_TitleGM_h_15_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_S1_Source_S1_TitleGM_h_15_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_S1_Source_S1_TitleGM_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_S1_Source_S1_TitleGM_h_15_ACCESSORS \
	FID_S1_Source_S1_TitleGM_h_15_INCLASS_NO_PURE_DECLS \
	FID_S1_Source_S1_TitleGM_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> S1_API UClass* StaticClass<class ATitleGM>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_S1_Source_S1_TitleGM_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
