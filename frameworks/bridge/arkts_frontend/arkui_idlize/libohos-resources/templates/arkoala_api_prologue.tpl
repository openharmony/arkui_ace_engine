/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef GENERATED_FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_API_H
#define GENERATED_FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_API_H

/**
 * THIS FILE IS GENERATED, DO NOT MAKE CHANGES, THEY WILL BE LOST ON NEXT GENERATION!
 */

%INTEROP_TYPES_HEADER

// The only include allowed in this file! Do not add anything else ever.
#include <stdint.h>

#define %CPP_PREFIX%ARKUI_FULL_API_VERSION %ARKUI_FULL_API_VERSION_VALUE%
#define %CPP_PREFIX%ARKUI_NODE_API_VERSION %CPP_PREFIX%ARKUI_FULL_API_VERSION

#define %CPP_PREFIX%ARKUI_BASIC_NODE_API_VERSION 1
#define %CPP_PREFIX%ARKUI_EXTENDED_NODE_API_VERSION 8
#define %CPP_PREFIX%ARKUI_NODE_GRAPHICS_API_VERSION 5
#define %CPP_PREFIX%ARKUI_NODE_MODIFIERS_API_VERSION 6

#define %CPP_PREFIX%ARKUI_AUTO_GENERATE_NODE_ID (-2)

/* clang-format off */

#ifdef __cplusplus
extern "C" {
#endif

typedef InteropTag Ark_Tag;
typedef InteropRuntimeType Ark_RuntimeType;

typedef InteropFloat32 Ark_Float32;
typedef InteropFloat64 Ark_Float64;
typedef InteropInt32 Ark_Int32;
typedef InteropUInt32 Ark_UInt32;
typedef InteropInt64 Ark_Int64;
typedef InteropInt8 Ark_Int8;
typedef InteropBoolean Ark_Boolean;
typedef InteropCharPtr Ark_CharPtr;
typedef InteropNativePointer Ark_NativePointer;
typedef InteropString Ark_String;
typedef InteropCallbackResource Ark_CallbackResource;
typedef InteropNumber Ark_Number;
typedef InteropMaterialized Ark_Materialized;
typedef InteropCustomObject Ark_CustomObject;
typedef InteropUndefined Ark_Undefined;
typedef InteropVMContext Ark_VMContext;
typedef InteropBuffer Ark_Buffer;
typedef InteropNodeHandle Ark_NodeHandle;
typedef InteropPipelineContext Ark_PipelineContext;
typedef InteropCustomObject Ark_CustomObject;
typedef InteropDate Ark_Date;
typedef InteropFunction Ark_Function;
typedef InteropAsyncWork Ark_AsyncWork;
typedef InteropAsyncWorker Ark_AsyncWorker;
typedef InteropAsyncWorkerPtr Ark_AsyncWorkerPtr;
typedef InteropObject Ark_Object;

// Improve: generate!
typedef struct Opt_Ark_Callback {
  Ark_Tag tag;
  Ark_CustomObject value;
} Opt_Ark_Callback;

enum %CPP_PREFIX%Ark_APIVariantKind {
    %CPP_PREFIX%BASIC = 10,
    %CPP_PREFIX%FULL = 11,
    %CPP_PREFIX%GRAPHICS = 12,
    %CPP_PREFIX%EXTENDED = 13,
    %CPP_PREFIX%COUNT = %CPP_PREFIX%EXTENDED + 1
};

enum Ark_APINodeFlags {
    %CPP_PREFIX%CUSTOM_NONE = 0,
    %CPP_PREFIX%CUSTOM_MEASURE = 1 << 0,
    %CPP_PREFIX%CUSTOM_LAYOUT = 1 << 1,
    %CPP_PREFIX%CUSTOM_DRAW = 1 << 2,
    %CPP_PREFIX%CUSTOM_FOREGROUND_DRAW = 1 << 3,
    %CPP_PREFIX%CUSTOM_OVERLAY_DRAW = 1 << 4,
};
enum Ark_APICustomOp {
    %CPP_PREFIX%MEASURE = 1,
    %CPP_PREFIX%LAYOUT = 2,
    %CPP_PREFIX%DRAW = 3
};

struct _Ark_Canvas;
typedef struct _Ark_Canvas* Ark_CanvasHandle;
