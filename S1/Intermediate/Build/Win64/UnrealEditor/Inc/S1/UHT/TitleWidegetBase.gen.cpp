// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "S1/TitleWidegetBase.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeTitleWidegetBase() {}
// Cross Module References
	S1_API UClass* Z_Construct_UClass_UTitleWidegetBase();
	S1_API UClass* Z_Construct_UClass_UTitleWidegetBase_NoRegister();
	UMG_API UClass* Z_Construct_UClass_UButton_NoRegister();
	UMG_API UClass* Z_Construct_UClass_UEditableTextBox_NoRegister();
	UMG_API UClass* Z_Construct_UClass_UUserWidget();
	UPackage* Z_Construct_UPackage__Script_S1();
// End Cross Module References
	DEFINE_FUNCTION(UTitleWidegetBase::execOnJoinButton)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnJoinButton();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UTitleWidegetBase::execOnLoginButton)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnLoginButton();
		P_NATIVE_END;
	}
	void UTitleWidegetBase::StaticRegisterNativesUTitleWidegetBase()
	{
		UClass* Class = UTitleWidegetBase::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "OnJoinButton", &UTitleWidegetBase::execOnJoinButton },
			{ "OnLoginButton", &UTitleWidegetBase::execOnLoginButton },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UTitleWidegetBase_OnJoinButton_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UTitleWidegetBase_OnJoinButton_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "TitleWidegetBase.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UTitleWidegetBase_OnJoinButton_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UTitleWidegetBase, nullptr, "OnJoinButton", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UTitleWidegetBase_OnJoinButton_Statics::Function_MetaDataParams), Z_Construct_UFunction_UTitleWidegetBase_OnJoinButton_Statics::Function_MetaDataParams) };
	UFunction* Z_Construct_UFunction_UTitleWidegetBase_OnJoinButton()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UTitleWidegetBase_OnJoinButton_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UTitleWidegetBase_OnLoginButton_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UTitleWidegetBase_OnLoginButton_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "TitleWidegetBase.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UTitleWidegetBase_OnLoginButton_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UTitleWidegetBase, nullptr, "OnLoginButton", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UTitleWidegetBase_OnLoginButton_Statics::Function_MetaDataParams), Z_Construct_UFunction_UTitleWidegetBase_OnLoginButton_Statics::Function_MetaDataParams) };
	UFunction* Z_Construct_UFunction_UTitleWidegetBase_OnLoginButton()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UTitleWidegetBase_OnLoginButton_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UTitleWidegetBase);
	UClass* Z_Construct_UClass_UTitleWidegetBase_NoRegister()
	{
		return UTitleWidegetBase::StaticClass();
	}
	struct Z_Construct_UClass_UTitleWidegetBase_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_UserID_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_UserID;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Password_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_Password;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_LoginButton_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_LoginButton;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_JoinButton_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_JoinButton;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UTitleWidegetBase_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UUserWidget,
		(UObject* (*)())Z_Construct_UPackage__Script_S1,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UTitleWidegetBase_Statics::DependentSingletons) < 16);
	const FClassFunctionLinkInfo Z_Construct_UClass_UTitleWidegetBase_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UTitleWidegetBase_OnJoinButton, "OnJoinButton" }, // 2960449872
		{ &Z_Construct_UFunction_UTitleWidegetBase_OnLoginButton, "OnLoginButton" }, // 3821212491
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UTitleWidegetBase_Statics::FuncInfo) < 2048);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UTitleWidegetBase_Statics::Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "TitleWidegetBase.h" },
		{ "ModuleRelativePath", "TitleWidegetBase.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UTitleWidegetBase_Statics::NewProp_UserID_MetaData[] = {
		{ "Category", "Control" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "TitleWidegetBase.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UTitleWidegetBase_Statics::NewProp_UserID = { "UserID", nullptr, (EPropertyFlags)0x001000000008001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UTitleWidegetBase, UserID), Z_Construct_UClass_UEditableTextBox_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UTitleWidegetBase_Statics::NewProp_UserID_MetaData), Z_Construct_UClass_UTitleWidegetBase_Statics::NewProp_UserID_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UTitleWidegetBase_Statics::NewProp_Password_MetaData[] = {
		{ "Category", "Control" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "TitleWidegetBase.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UTitleWidegetBase_Statics::NewProp_Password = { "Password", nullptr, (EPropertyFlags)0x001000000008001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UTitleWidegetBase, Password), Z_Construct_UClass_UEditableTextBox_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UTitleWidegetBase_Statics::NewProp_Password_MetaData), Z_Construct_UClass_UTitleWidegetBase_Statics::NewProp_Password_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UTitleWidegetBase_Statics::NewProp_LoginButton_MetaData[] = {
		{ "Category", "Control" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "TitleWidegetBase.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UTitleWidegetBase_Statics::NewProp_LoginButton = { "LoginButton", nullptr, (EPropertyFlags)0x001000000008001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UTitleWidegetBase, LoginButton), Z_Construct_UClass_UButton_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UTitleWidegetBase_Statics::NewProp_LoginButton_MetaData), Z_Construct_UClass_UTitleWidegetBase_Statics::NewProp_LoginButton_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UTitleWidegetBase_Statics::NewProp_JoinButton_MetaData[] = {
		{ "Category", "Control" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "TitleWidegetBase.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UTitleWidegetBase_Statics::NewProp_JoinButton = { "JoinButton", nullptr, (EPropertyFlags)0x001000000008001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UTitleWidegetBase, JoinButton), Z_Construct_UClass_UButton_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UTitleWidegetBase_Statics::NewProp_JoinButton_MetaData), Z_Construct_UClass_UTitleWidegetBase_Statics::NewProp_JoinButton_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UTitleWidegetBase_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UTitleWidegetBase_Statics::NewProp_UserID,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UTitleWidegetBase_Statics::NewProp_Password,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UTitleWidegetBase_Statics::NewProp_LoginButton,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UTitleWidegetBase_Statics::NewProp_JoinButton,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UTitleWidegetBase_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UTitleWidegetBase>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UTitleWidegetBase_Statics::ClassParams = {
		&UTitleWidegetBase::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UTitleWidegetBase_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UTitleWidegetBase_Statics::PropPointers),
		0,
		0x00B010A0u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UTitleWidegetBase_Statics::Class_MetaDataParams), Z_Construct_UClass_UTitleWidegetBase_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UTitleWidegetBase_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_UTitleWidegetBase()
	{
		if (!Z_Registration_Info_UClass_UTitleWidegetBase.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UTitleWidegetBase.OuterSingleton, Z_Construct_UClass_UTitleWidegetBase_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UTitleWidegetBase.OuterSingleton;
	}
	template<> S1_API UClass* StaticClass<UTitleWidegetBase>()
	{
		return UTitleWidegetBase::StaticClass();
	}
	UTitleWidegetBase::UTitleWidegetBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UTitleWidegetBase);
	UTitleWidegetBase::~UTitleWidegetBase() {}
	struct Z_CompiledInDeferFile_FID_S1_Source_S1_TitleWidegetBase_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_S1_Source_S1_TitleWidegetBase_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UTitleWidegetBase, UTitleWidegetBase::StaticClass, TEXT("UTitleWidegetBase"), &Z_Registration_Info_UClass_UTitleWidegetBase, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UTitleWidegetBase), 4039882771U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_S1_Source_S1_TitleWidegetBase_h_4140832212(TEXT("/Script/S1"),
		Z_CompiledInDeferFile_FID_S1_Source_S1_TitleWidegetBase_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_S1_Source_S1_TitleWidegetBase_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
