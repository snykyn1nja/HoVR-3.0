// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "HoVR/ActuateMotionComponent.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeActuateMotionComponent() {}
// Cross Module References
	HOVR_API UClass* Z_Construct_UClass_UActuateMotionComponent_NoRegister();
	HOVR_API UClass* Z_Construct_UClass_UActuateMotionComponent();
	ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
	UPackage* Z_Construct_UPackage__Script_HoVR();
// End Cross Module References
	void UActuateMotionComponent::StaticRegisterNativesUActuateMotionComponent()
	{
	}
	UClass* Z_Construct_UClass_UActuateMotionComponent_NoRegister()
	{
		return UActuateMotionComponent::StaticClass();
	}
	struct Z_Construct_UClass_UActuateMotionComponent_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UActuateMotionComponent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UActorComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_HoVR,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UActuateMotionComponent_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Custom" },
		{ "IncludePath", "ActuateMotionComponent.h" },
		{ "ModuleRelativePath", "ActuateMotionComponent.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UActuateMotionComponent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UActuateMotionComponent>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UActuateMotionComponent_Statics::ClassParams = {
		&UActuateMotionComponent::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x00B000A4u,
		METADATA_PARAMS(Z_Construct_UClass_UActuateMotionComponent_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UActuateMotionComponent_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UActuateMotionComponent()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UActuateMotionComponent_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UActuateMotionComponent, 1669419655);
	template<> HOVR_API UClass* StaticClass<UActuateMotionComponent>()
	{
		return UActuateMotionComponent::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UActuateMotionComponent(Z_Construct_UClass_UActuateMotionComponent, &UActuateMotionComponent::StaticClass, TEXT("/Script/HoVR"), TEXT("UActuateMotionComponent"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UActuateMotionComponent);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
