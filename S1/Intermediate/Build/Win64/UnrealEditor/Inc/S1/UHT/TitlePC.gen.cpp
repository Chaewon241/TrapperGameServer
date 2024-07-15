// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "S1/TitlePC.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeTitlePC() {}
// Cross Module References
	COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
	ENGINE_API UClass* Z_Construct_UClass_APlayerController();
	S1_API UClass* Z_Construct_UClass_ATitlePC();
	S1_API UClass* Z_Construct_UClass_ATitlePC_NoRegister();
	S1_API UClass* Z_Construct_UClass_UTitleWidegetBase_NoRegister();
	UPackage* Z_Construct_UPackage__Script_S1();
// End Cross Module References
	DEFINE_FUNCTION(ATitlePC::execSendLoginPacket)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_ID);
		P_GET_PROPERTY(FStrProperty,Z_Param_Password);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SendLoginPacket(Z_Param_ID,Z_Param_Password);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ATitlePC::execConnectServer)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_ServerIP);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->ConnectServer(Z_Param_ServerIP);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ATitlePC::execStartServer)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->StartServer();
		P_NATIVE_END;
	}
	void ATitlePC::StaticRegisterNativesATitlePC()
	{
		UClass* Class = ATitlePC::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "ConnectServer", &ATitlePC::execConnectServer },
			{ "SendLoginPacket", &ATitlePC::execSendLoginPacket },
			{ "StartServer", &ATitlePC::execStartServer },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_ATitlePC_ConnectServer_Statics
	{
		struct TitlePC_eventConnectServer_Parms
		{
			FString ServerIP;
		};
		static const UECodeGen_Private::FStrPropertyParams NewProp_ServerIP;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_ATitlePC_ConnectServer_Statics::NewProp_ServerIP = { "ServerIP", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TitlePC_eventConnectServer_Parms, ServerIP), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ATitlePC_ConnectServer_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATitlePC_ConnectServer_Statics::NewProp_ServerIP,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ATitlePC_ConnectServer_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "TitlePC.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ATitlePC_ConnectServer_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ATitlePC, nullptr, "ConnectServer", nullptr, nullptr, Z_Construct_UFunction_ATitlePC_ConnectServer_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ATitlePC_ConnectServer_Statics::PropPointers), sizeof(Z_Construct_UFunction_ATitlePC_ConnectServer_Statics::TitlePC_eventConnectServer_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ATitlePC_ConnectServer_Statics::Function_MetaDataParams), Z_Construct_UFunction_ATitlePC_ConnectServer_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ATitlePC_ConnectServer_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_ATitlePC_ConnectServer_Statics::TitlePC_eventConnectServer_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_ATitlePC_ConnectServer()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ATitlePC_ConnectServer_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ATitlePC_SendLoginPacket_Statics
	{
		struct TitlePC_eventSendLoginPacket_Parms
		{
			FString ID;
			FString Password;
		};
		static const UECodeGen_Private::FStrPropertyParams NewProp_ID;
		static const UECodeGen_Private::FStrPropertyParams NewProp_Password;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_ATitlePC_SendLoginPacket_Statics::NewProp_ID = { "ID", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TitlePC_eventSendLoginPacket_Parms, ID), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_ATitlePC_SendLoginPacket_Statics::NewProp_Password = { "Password", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TitlePC_eventSendLoginPacket_Parms, Password), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ATitlePC_SendLoginPacket_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATitlePC_SendLoginPacket_Statics::NewProp_ID,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ATitlePC_SendLoginPacket_Statics::NewProp_Password,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ATitlePC_SendLoginPacket_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "TitlePC.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ATitlePC_SendLoginPacket_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ATitlePC, nullptr, "SendLoginPacket", nullptr, nullptr, Z_Construct_UFunction_ATitlePC_SendLoginPacket_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ATitlePC_SendLoginPacket_Statics::PropPointers), sizeof(Z_Construct_UFunction_ATitlePC_SendLoginPacket_Statics::TitlePC_eventSendLoginPacket_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ATitlePC_SendLoginPacket_Statics::Function_MetaDataParams), Z_Construct_UFunction_ATitlePC_SendLoginPacket_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ATitlePC_SendLoginPacket_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_ATitlePC_SendLoginPacket_Statics::TitlePC_eventSendLoginPacket_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_ATitlePC_SendLoginPacket()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ATitlePC_SendLoginPacket_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ATitlePC_StartServer_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ATitlePC_StartServer_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "TitlePC.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ATitlePC_StartServer_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ATitlePC, nullptr, "StartServer", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ATitlePC_StartServer_Statics::Function_MetaDataParams), Z_Construct_UFunction_ATitlePC_StartServer_Statics::Function_MetaDataParams) };
	UFunction* Z_Construct_UFunction_ATitlePC_StartServer()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ATitlePC_StartServer_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ATitlePC);
	UClass* Z_Construct_UClass_ATitlePC_NoRegister()
	{
		return ATitlePC::StaticClass();
	}
	struct Z_Construct_UClass_ATitlePC_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_TitleWidgetClass_MetaData[];
#endif
		static const UECodeGen_Private::FClassPropertyParams NewProp_TitleWidgetClass;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_TitleWidgetObject_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_TitleWidgetObject;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ATitlePC_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_APlayerController,
		(UObject* (*)())Z_Construct_UPackage__Script_S1,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ATitlePC_Statics::DependentSingletons) < 16);
	const FClassFunctionLinkInfo Z_Construct_UClass_ATitlePC_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ATitlePC_ConnectServer, "ConnectServer" }, // 4211345583
		{ &Z_Construct_UFunction_ATitlePC_SendLoginPacket, "SendLoginPacket" }, // 2485783631
		{ &Z_Construct_UFunction_ATitlePC_StartServer, "StartServer" }, // 912320082
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ATitlePC_Statics::FuncInfo) < 2048);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATitlePC_Statics::Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "Collision Rendering Transformation" },
		{ "IncludePath", "TitlePC.h" },
		{ "ModuleRelativePath", "TitlePC.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATitlePC_Statics::NewProp_TitleWidgetClass_MetaData[] = {
		{ "Category", "UI" },
		{ "ModuleRelativePath", "TitlePC.h" },
	};
#endif
	const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_ATitlePC_Statics::NewProp_TitleWidgetClass = { "TitleWidgetClass", nullptr, (EPropertyFlags)0x0014000000000015, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATitlePC, TitleWidgetClass), Z_Construct_UClass_UClass, Z_Construct_UClass_UTitleWidegetBase_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ATitlePC_Statics::NewProp_TitleWidgetClass_MetaData), Z_Construct_UClass_ATitlePC_Statics::NewProp_TitleWidgetClass_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATitlePC_Statics::NewProp_TitleWidgetObject_MetaData[] = {
		{ "Category", "UI" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "TitlePC.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ATitlePC_Statics::NewProp_TitleWidgetObject = { "TitleWidgetObject", nullptr, (EPropertyFlags)0x00100000000a000d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ATitlePC, TitleWidgetObject), Z_Construct_UClass_UTitleWidegetBase_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ATitlePC_Statics::NewProp_TitleWidgetObject_MetaData), Z_Construct_UClass_ATitlePC_Statics::NewProp_TitleWidgetObject_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ATitlePC_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATitlePC_Statics::NewProp_TitleWidgetClass,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ATitlePC_Statics::NewProp_TitleWidgetObject,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ATitlePC_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ATitlePC>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ATitlePC_Statics::ClassParams = {
		&ATitlePC::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_ATitlePC_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_ATitlePC_Statics::PropPointers),
		0,
		0x009002A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ATitlePC_Statics::Class_MetaDataParams), Z_Construct_UClass_ATitlePC_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ATitlePC_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_ATitlePC()
	{
		if (!Z_Registration_Info_UClass_ATitlePC.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ATitlePC.OuterSingleton, Z_Construct_UClass_ATitlePC_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ATitlePC.OuterSingleton;
	}
	template<> S1_API UClass* StaticClass<ATitlePC>()
	{
		return ATitlePC::StaticClass();
	}
	ATitlePC::ATitlePC(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ATitlePC);
	ATitlePC::~ATitlePC() {}
	struct Z_CompiledInDeferFile_FID_S1_Source_S1_TitlePC_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_S1_Source_S1_TitlePC_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ATitlePC, ATitlePC::StaticClass, TEXT("ATitlePC"), &Z_Registration_Info_UClass_ATitlePC, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ATitlePC), 950378131U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_S1_Source_S1_TitlePC_h_3792958142(TEXT("/Script/S1"),
		Z_CompiledInDeferFile_FID_S1_Source_S1_TitlePC_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_S1_Source_S1_TitlePC_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
