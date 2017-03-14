// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	C++ class header boilerplate exported from UnrealHeaderTool.
	This is automatically generated by the tools.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef FIGHTWITHBLOCK_MyEnums_generated_h
#error "MyEnums.generated.h already included, missing '#pragma once' in MyEnums.h"
#endif
#define FIGHTWITHBLOCK_MyEnums_generated_h

#define FightWithBlock_Source_FightWithBlock_MyEnums_h_14_RPC_WRAPPERS
#define FightWithBlock_Source_FightWithBlock_MyEnums_h_14_RPC_WRAPPERS_NO_PURE_DECLS
#define FightWithBlock_Source_FightWithBlock_MyEnums_h_14_INCLASS_NO_PURE_DECLS \
	private: \
	static void StaticRegisterNativesUMyEnums(); \
	friend FIGHTWITHBLOCK_API class UClass* Z_Construct_UClass_UMyEnums(); \
	public: \
	DECLARE_CLASS(UMyEnums, UUserDefinedEnum, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/FightWithBlock"), NO_API) \
	DECLARE_SERIALIZER(UMyEnums) \
	/** Indicates whether the class is compiled into the engine */ \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define FightWithBlock_Source_FightWithBlock_MyEnums_h_14_INCLASS \
	private: \
	static void StaticRegisterNativesUMyEnums(); \
	friend FIGHTWITHBLOCK_API class UClass* Z_Construct_UClass_UMyEnums(); \
	public: \
	DECLARE_CLASS(UMyEnums, UUserDefinedEnum, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/FightWithBlock"), NO_API) \
	DECLARE_SERIALIZER(UMyEnums) \
	/** Indicates whether the class is compiled into the engine */ \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define FightWithBlock_Source_FightWithBlock_MyEnums_h_14_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UMyEnums(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UMyEnums) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UMyEnums); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UMyEnums); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UMyEnums(UMyEnums&&); \
	NO_API UMyEnums(const UMyEnums&); \
public:


#define FightWithBlock_Source_FightWithBlock_MyEnums_h_14_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UMyEnums(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UMyEnums(UMyEnums&&); \
	NO_API UMyEnums(const UMyEnums&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UMyEnums); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UMyEnums); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UMyEnums)


#define FightWithBlock_Source_FightWithBlock_MyEnums_h_14_PRIVATE_PROPERTY_OFFSET
#define FightWithBlock_Source_FightWithBlock_MyEnums_h_11_PROLOG
#define FightWithBlock_Source_FightWithBlock_MyEnums_h_14_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FightWithBlock_Source_FightWithBlock_MyEnums_h_14_PRIVATE_PROPERTY_OFFSET \
	FightWithBlock_Source_FightWithBlock_MyEnums_h_14_RPC_WRAPPERS \
	FightWithBlock_Source_FightWithBlock_MyEnums_h_14_INCLASS \
	FightWithBlock_Source_FightWithBlock_MyEnums_h_14_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FightWithBlock_Source_FightWithBlock_MyEnums_h_14_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FightWithBlock_Source_FightWithBlock_MyEnums_h_14_PRIVATE_PROPERTY_OFFSET \
	FightWithBlock_Source_FightWithBlock_MyEnums_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	FightWithBlock_Source_FightWithBlock_MyEnums_h_14_INCLASS_NO_PURE_DECLS \
	FightWithBlock_Source_FightWithBlock_MyEnums_h_14_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FightWithBlock_Source_FightWithBlock_MyEnums_h


#define FOREACH_ENUM_ECAMP(op) \
	op(EBlue) \
	op(ERed) \
	op(EDefault) 
PRAGMA_ENABLE_DEPRECATION_WARNINGS
