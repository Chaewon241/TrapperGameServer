// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "S1/TitleGM.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeTitleGM() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	S1_API UClass* Z_Construct_UClass_ATitleGM();
	S1_API UClass* Z_Construct_UClass_ATitleGM_NoRegister();
	UPackage* Z_Construct_UPackage__Script_S1();
// End Cross Module References
	void ATitleGM::StaticRegisterNativesATitleGM()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ATitleGM);
	UClass* Z_Construct_UClass_ATitleGM_NoRegister()
	{
		return ATitleGM::StaticClass();
	}
	struct Z_Construct_UClass_ATitleGM_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ATitleGM_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_S1,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ATitleGM_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATitleGM_Statics::Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "TitleGM.h" },
		{ "ModuleRelativePath", "TitleGM.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ATitleGM_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ATitleGM>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ATitleGM_Statics::ClassParams = {
		&ATitleGM::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009002ACu,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ATitleGM_Statics::Class_MetaDataParams), Z_Construct_UClass_ATitleGM_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_ATitleGM()
	{
		if (!Z_Registration_Info_UClass_ATitleGM.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ATitleGM.OuterSingleton, Z_Construct_UClass_ATitleGM_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ATitleGM.OuterSingleton;
	}
	template<> S1_API UClass* StaticClass<ATitleGM>()
	{
		return ATitleGM::StaticClass();
	}
	ATitleGM::ATitleGM(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ATitleGM);
	ATitleGM::~ATitleGM() {}
	struct Z_CompiledInDeferFile_FID_S1_Source_S1_TitleGM_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_S1_Source_S1_TitleGM_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ATitleGM, ATitleGM::StaticClass, TEXT("ATitleGM"), &Z_Registration_Info_UClass_ATitleGM, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ATitleGM), 3309281297U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_S1_Source_S1_TitleGM_h_1984313812(TEXT("/Script/S1"),
		Z_CompiledInDeferFile_FID_S1_Source_S1_TitleGM_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_S1_Source_S1_TitleGM_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
