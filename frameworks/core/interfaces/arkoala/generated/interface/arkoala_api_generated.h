
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

// The only include allowed in this file! Do not add anything else ever.
#include <stdint.h>

#define GENERATED_ARKUI_FULL_API_VERSION 99
#define GENERATED_ARKUI_NODE_API_VERSION GENERATED_ARKUI_FULL_API_VERSION

#define GENERATED_ARKUI_BASIC_NODE_API_VERSION 1
#define GENERATED_ARKUI_EXTENDED_NODE_API_VERSION 6
#define GENERATED_ARKUI_NODE_GRAPHICS_API_VERSION 5
#define GENERATED_ARKUI_NODE_MODIFIERS_API_VERSION 6
#define GENERATED_ARKUI_AUTO_GENERATE_NODE_ID (-2)

#ifdef __cplusplus
extern "C" {
#endif

enum Ark_Tag
{
  ARK_TAG_UNDEFINED = 101,
  ARK_TAG_INT32 = 102,
  ARK_TAG_FLOAT32 = 103,
  ARK_TAG_STRING = 104,
  ARK_TAG_LENGTH = 105,
  ARK_TAG_RESOURCE = 106,
  ARK_TAG_OBJECT = 107,
};

enum Ark_RuntimeType
{
  ARK_RUNTIME_UNEXPECTED = -1,
  ARK_RUNTIME_NUMBER = 1,
  ARK_RUNTIME_STRING = 2,
  ARK_RUNTIME_OBJECT = 3,
  ARK_RUNTIME_BOOLEAN = 4,
  ARK_RUNTIME_UNDEFINED = 5,
  ARK_RUNTIME_BIGINT = 6,
  ARK_RUNTIME_FUNCTION = 7,
  ARK_RUNTIME_SYMBOL = 8,
  ARK_RUNTIME_MATERIALIZED = 9,
};

typedef float Ark_Float32;
typedef double Ark_Float64;
typedef int32_t Ark_Int32;
typedef unsigned int Ark_UInt32; // TODO: update unsigned int
typedef int64_t Ark_Int64;
typedef int8_t Ark_Int8;
typedef int8_t Ark_Boolean;
typedef const char* Ark_CharPtr;
typedef void* Ark_NativePointer;

#ifdef FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_API_H
typedef struct _ArkUINode* Ark_NodeHandle;
typedef struct _ArkUIVMContext* Ark_VMContext;
typedef struct _ArkUIPipelineContext* Ark_PipelineContext;
#else
struct Ark_NodeHandleOpaque;
typedef struct Ark_NodeHandleOpaque* Ark_NodeHandle;

struct Ark_VMContextOpaque;
typedef struct Ark_VMContextOpaque* Ark_VMContext;

struct Ark_PipelineContextOpaque;
typedef struct Ark_PipelineContextOpaque* Ark_PipelineContext;
#endif

struct Ark_ObjectHandleOpaque;
typedef struct Ark_ObjectHandleOpaque* Ark_ObjectHandle;

// Binary layout of Ark_String must match that of KStringPtrImpl.
typedef struct Ark_String {
  const char* chars;
  Ark_Int32 length;
} Ark_String;

typedef struct Ark_Empty {
  Ark_Int32 dummy; // Empty structs are forbidden in C.
} Ark_Empty;

typedef struct Ark_Number {
  Ark_Int8 tag;
  union {
    Ark_Float32 f32;
    Ark_Int32 i32;
  };
} Ark_Number;

// Binary layout of Ark_Length must match that of KLength.
typedef struct Ark_Length
{
  Ark_Int8 type;
  Ark_Float32 value;
  Ark_Int32 unit;
  Ark_Int32 resource;
} Ark_Length;

typedef struct Ark_CustomObject {
  char kind[20];
  Ark_Int32 id;
  // Data of custom object.
  union {
    Ark_Int32 ints[4];
    Ark_Float32 floats[4];
    void* pointers[4];
    Ark_String string;
  };
} Ark_CustomObject;

typedef struct Ark_Undefined {
  Ark_Int32 dummy; // Empty structs are forbidden in C.
} Ark_Undefined;

typedef struct Ark_Function {
  Ark_Int32 id;
} Ark_Function;
typedef Ark_Function Ark_Callback;
typedef Ark_Function Ark_ErrorCallback;

typedef struct Ark_Materialized {
  Ark_NativePointer ptr;
} Ark_Materialized;

typedef Ark_CustomObject Ark_Resource;

// TODO: generate!
typedef struct Opt_Ark_Callback {
  enum Ark_Tag tag;
  Ark_CustomObject value;
} Opt_Ark_Callback;

enum GENERATED_Ark_APIVariantKind {
    GENERATED_BASIC = 10,
    GENERATED_FULL = 11,
    GENERATED_GRAPHICS = 12,
    GENERATED_EXTENDED = 13,
    GENERATED_COUNT = GENERATED_EXTENDED + 1
};

typedef struct Opt_Ark_Int32 {
    enum Ark_Tag tag;
    Ark_Int32 value;
} Opt_Ark_Int32;
typedef struct Opt_Ark_Length {
    enum Ark_Tag tag;
    Ark_Length value;
} Opt_Ark_Length;
typedef struct Opt_Ark_Resource {
    enum Ark_Tag tag;
    Ark_Resource value;
} Opt_Ark_Resource;
typedef struct Opt_Ark_Number {
    enum Ark_Tag tag;
    Ark_Number value;
} Opt_Ark_Number;
typedef Ark_Int32 Ark_ColoringStrategy;
typedef struct Opt_Ark_ColoringStrategy { enum Ark_Tag tag; Ark_ColoringStrategy value; } Opt_Ark_ColoringStrategy;
typedef struct Opt_Ark_String {
    enum Ark_Tag tag;
    Ark_String value;
} Opt_Ark_String;
typedef Ark_Int32 Ark_Color;
typedef struct Opt_Ark_Color { enum Ark_Tag tag; Ark_Color value; } Opt_Ark_Color;
typedef struct Position {
    Opt_Ark_Length x;
    Opt_Ark_Length y;
} Position;
typedef struct Opt_Position {
    enum Ark_Tag tag;
    Position value;
} Opt_Position;
typedef struct Literal_topLeft_Opt_Ark_Length_topRight_Opt_Ark_Length_bottomLeft_Opt_Ark_Length_bottomRight_Opt_Ark_Length {
    Opt_Ark_Length topLeft;
    Opt_Ark_Length topRight;
    Opt_Ark_Length bottomLeft;
    Opt_Ark_Length bottomRight;
} Literal_topLeft_Opt_Ark_Length_topRight_Opt_Ark_Length_bottomLeft_Opt_Ark_Length_bottomRight_Opt_Ark_Length;
typedef struct Opt_Literal_topLeft_Opt_Ark_Length_topRight_Opt_Ark_Length_bottomLeft_Opt_Ark_Length_bottomRight_Opt_Ark_Length {
    enum Ark_Tag tag;
    Literal_topLeft_Opt_Ark_Length_topRight_Opt_Ark_Length_bottomLeft_Opt_Ark_Length_bottomRight_Opt_Ark_Length value;
} Opt_Literal_topLeft_Opt_Ark_Length_topRight_Opt_Ark_Length_bottomLeft_Opt_Ark_Length_bottomRight_Opt_Ark_Length;
typedef struct Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length {
    Opt_Ark_Length top;
    Opt_Ark_Length right;
    Opt_Ark_Length bottom;
    Opt_Ark_Length left;
} Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length;
typedef struct Opt_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length {
    enum Ark_Tag tag;
    Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length value;
} Opt_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length;
typedef struct Tuple_Ark_Length_Ark_Length {
    Ark_Length value0;
    Ark_Length value1;
} Tuple_Ark_Length_Ark_Length;
typedef struct Opt_Tuple_Ark_Length_Ark_Length {
    enum Ark_Tag tag;
    Tuple_Ark_Length_Ark_Length value;
} Opt_Tuple_Ark_Length_Ark_Length;
typedef struct Opt_Ark_CustomObject {
    enum Ark_Tag tag;
    Ark_CustomObject value;
} Opt_Ark_CustomObject;
typedef struct Opt_Ark_Boolean {
    enum Ark_Tag tag;
    Ark_Boolean value;
} Opt_Ark_Boolean;
typedef struct Union_Ark_Number_Ark_Resource {
    Ark_Int32 selector;
    union {
        Ark_Number value0;
        Ark_Resource value1;
    };
} Union_Ark_Number_Ark_Resource;
typedef struct Opt_Union_Ark_Number_Ark_Resource {
    enum Ark_Tag tag;
    Union_Ark_Number_Ark_Resource value;
} Opt_Union_Ark_Number_Ark_Resource;
typedef struct Union_Ark_Color_Ark_String_Ark_Resource_Ark_ColoringStrategy {
    Ark_Int32 selector;
    union {
        Ark_Color value0;
        Ark_String value1;
        Ark_Resource value2;
        Ark_ColoringStrategy value3;
    };
} Union_Ark_Color_Ark_String_Ark_Resource_Ark_ColoringStrategy;
typedef struct Opt_Union_Ark_Color_Ark_String_Ark_Resource_Ark_ColoringStrategy {
    enum Ark_Tag tag;
    Union_Ark_Color_Ark_String_Ark_Resource_Ark_ColoringStrategy value;
} Opt_Union_Ark_Color_Ark_String_Ark_Resource_Ark_ColoringStrategy;
typedef Ark_Int32 Ark_ShadowType;
typedef struct Opt_Ark_ShadowType { enum Ark_Tag tag; Ark_ShadowType value; } Opt_Ark_ShadowType;
typedef Ark_Int32 Ark_FontWeight;
typedef struct Opt_Ark_FontWeight { enum Ark_Tag tag; Ark_FontWeight value; } Opt_Ark_FontWeight;
typedef struct Area {
    Ark_Length width;
    Ark_Length height;
    struct Position position;
    struct Position globalPosition;
} Area;
typedef struct Opt_Area {
    enum Ark_Tag tag;
    Area value;
} Opt_Area;
typedef struct Union_Ark_Length_Literal_topLeft_Opt_Ark_Length_topRight_Opt_Ark_Length_bottomLeft_Opt_Ark_Length_bottomRight_Opt_Ark_Length {
    Ark_Int32 selector;
    union {
        Ark_Length value0;
        struct Literal_topLeft_Opt_Ark_Length_topRight_Opt_Ark_Length_bottomLeft_Opt_Ark_Length_bottomRight_Opt_Ark_Length value1;
    };
} Union_Ark_Length_Literal_topLeft_Opt_Ark_Length_topRight_Opt_Ark_Length_bottomLeft_Opt_Ark_Length_bottomRight_Opt_Ark_Length;
typedef struct Opt_Union_Ark_Length_Literal_topLeft_Opt_Ark_Length_topRight_Opt_Ark_Length_bottomLeft_Opt_Ark_Length_bottomRight_Opt_Ark_Length {
    enum Ark_Tag tag;
    Union_Ark_Length_Literal_topLeft_Opt_Ark_Length_topRight_Opt_Ark_Length_bottomLeft_Opt_Ark_Length_bottomRight_Opt_Ark_Length value;
} Opt_Union_Ark_Length_Literal_topLeft_Opt_Ark_Length_topRight_Opt_Ark_Length_bottomLeft_Opt_Ark_Length_bottomRight_Opt_Ark_Length;
typedef struct Union_Ark_Length_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length {
    Ark_Int32 selector;
    union {
        Ark_Length value0;
        struct Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length value1;
    };
} Union_Ark_Length_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length;
typedef struct Opt_Union_Ark_Length_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length {
    enum Ark_Tag tag;
    Union_Ark_Length_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length value;
} Opt_Union_Ark_Length_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length;
typedef struct LeadingMarginPlaceholder {
    Ark_CustomObject pixelMap;
    struct Tuple_Ark_Length_Ark_Length size;
} LeadingMarginPlaceholder;
typedef struct Opt_LeadingMarginPlaceholder {
    enum Ark_Tag tag;
    LeadingMarginPlaceholder value;
} Opt_LeadingMarginPlaceholder;
typedef Ark_Int32 Ark_TextDecorationStyle;
typedef struct Opt_Ark_TextDecorationStyle { enum Ark_Tag tag; Ark_TextDecorationStyle value; } Opt_Ark_TextDecorationStyle;
typedef struct Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource {
    Ark_Int32 selector;
    union {
        Ark_Color value0;
        Ark_Number value1;
        Ark_String value2;
        Ark_Resource value3;
    };
} Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource;
typedef struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource {
    enum Ark_Tag tag;
    Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource value;
} Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource;
typedef Ark_Int32 Ark_TextDecorationType;
typedef struct Opt_Ark_TextDecorationType { enum Ark_Tag tag; Ark_TextDecorationType value; } Opt_Ark_TextDecorationType;
typedef struct Union_Ark_CustomObject_Literal_topLeft_Opt_Ark_Length_topRight_Opt_Ark_Length_bottomLeft_Opt_Ark_Length_bottomRight_Opt_Ark_Length {
    Ark_Int32 selector;
    union {
        Ark_CustomObject value0;
        struct Literal_topLeft_Opt_Ark_Length_topRight_Opt_Ark_Length_bottomLeft_Opt_Ark_Length_bottomRight_Opt_Ark_Length value1;
    };
} Union_Ark_CustomObject_Literal_topLeft_Opt_Ark_Length_topRight_Opt_Ark_Length_bottomLeft_Opt_Ark_Length_bottomRight_Opt_Ark_Length;
typedef struct Opt_Union_Ark_CustomObject_Literal_topLeft_Opt_Ark_Length_topRight_Opt_Ark_Length_bottomLeft_Opt_Ark_Length_bottomRight_Opt_Ark_Length {
    enum Ark_Tag tag;
    Union_Ark_CustomObject_Literal_topLeft_Opt_Ark_Length_topRight_Opt_Ark_Length_bottomLeft_Opt_Ark_Length_bottomRight_Opt_Ark_Length value;
} Opt_Union_Ark_CustomObject_Literal_topLeft_Opt_Ark_Length_topRight_Opt_Ark_Length_bottomLeft_Opt_Ark_Length_bottomRight_Opt_Ark_Length;
typedef struct Union_Ark_CustomObject_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length {
    Ark_Int32 selector;
    union {
        Ark_CustomObject value0;
        struct Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length value1;
    };
} Union_Ark_CustomObject_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length;
typedef struct Opt_Union_Ark_CustomObject_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length {
    enum Ark_Tag tag;
    Union_Ark_CustomObject_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length value;
} Opt_Union_Ark_CustomObject_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length;
typedef struct Array_ShadowOptions {
    struct ShadowOptions* array;
    Ark_Int32 length;
} Array_ShadowOptions;
typedef struct Opt_Array_ShadowOptions {
    enum Ark_Tag tag;
    Array_ShadowOptions value;
} Opt_Array_ShadowOptions;
typedef struct ShadowOptions {
    struct Union_Ark_Number_Ark_Resource radius;
    Opt_Ark_ShadowType type;
    struct Opt_Union_Ark_Color_Ark_String_Ark_Resource_Ark_ColoringStrategy color;
    struct Opt_Union_Ark_Number_Ark_Resource offsetX;
    struct Opt_Union_Ark_Number_Ark_Resource offsetY;
    Opt_Ark_Boolean fill;
} ShadowOptions;
typedef struct Opt_ShadowOptions {
    enum Ark_Tag tag;
    ShadowOptions value;
} Opt_ShadowOptions;
typedef struct ICurve {
} ICurve;
typedef struct Opt_ICurve {
    enum Ark_Tag tag;
    ICurve value;
} Opt_ICurve;
typedef Ark_Int32 Ark_Curve;
typedef struct Opt_Ark_Curve { enum Ark_Tag tag; Ark_Curve value; } Opt_Ark_Curve;
typedef Ark_Int32 Ark_FontStyle;
typedef struct Opt_Ark_FontStyle { enum Ark_Tag tag; Ark_FontStyle value; } Opt_Ark_FontStyle;
typedef struct Union_Ark_String_Ark_Resource {
    Ark_Int32 selector;
    union {
        Ark_String value0;
        Ark_Resource value1;
    };
} Union_Ark_String_Ark_Resource;
typedef struct Opt_Union_Ark_String_Ark_Resource {
    enum Ark_Tag tag;
    Union_Ark_String_Ark_Resource value;
} Opt_Union_Ark_String_Ark_Resource;
typedef struct Union_Ark_FontWeight_Ark_Number_Ark_String {
    Ark_Int32 selector;
    union {
        Ark_FontWeight value0;
        Ark_Number value1;
        Ark_String value2;
    };
} Union_Ark_FontWeight_Ark_Number_Ark_String;
typedef struct Opt_Union_Ark_FontWeight_Ark_Number_Ark_String {
    enum Ark_Tag tag;
    Union_Ark_FontWeight_Ark_Number_Ark_String value;
} Opt_Union_Ark_FontWeight_Ark_Number_Ark_String;
typedef struct CommonMethod {
} CommonMethod;
typedef struct Opt_CommonMethod {
    enum Ark_Tag tag;
    CommonMethod value;
} Opt_CommonMethod;
typedef Ark_Materialized TextBaseController;
typedef struct Opt_TextBaseController {
    enum Ark_Tag tag;
    TextBaseController value;
} Opt_TextBaseController;
typedef struct Opt_Ark_Undefined {
    enum Ark_Tag tag;
    Ark_Undefined value;
} Opt_Ark_Undefined;
typedef struct Opt_Ark_Function {
    enum Ark_Tag tag;
    Ark_Function value;
} Opt_Ark_Function;
typedef struct GridRowSizeOption {
    Opt_Ark_Length xs;
    Opt_Ark_Length sm;
    Opt_Ark_Length md;
    Opt_Ark_Length lg;
    Opt_Ark_Length xl;
    Opt_Ark_Length xxl;
} GridRowSizeOption;
typedef struct Opt_GridRowSizeOption {
    enum Ark_Tag tag;
    GridRowSizeOption value;
} Opt_GridRowSizeOption;
typedef Ark_Materialized CanvasPattern;
typedef struct Opt_CanvasPattern {
    enum Ark_Tag tag;
    CanvasPattern value;
} Opt_CanvasPattern;
typedef Ark_Materialized CanvasGradient;
typedef struct Opt_CanvasGradient {
    enum Ark_Tag tag;
    CanvasGradient value;
} Opt_CanvasGradient;
typedef Ark_Int32 Ark_SheetSize;
typedef struct Opt_Ark_SheetSize { enum Ark_Tag tag; Ark_SheetSize value; } Opt_Ark_SheetSize;
typedef Ark_Int32 Ark_SourceTool;
typedef struct Opt_Ark_SourceTool { enum Ark_Tag tag; Ark_SourceTool value; } Opt_Ark_SourceTool;
typedef Ark_Int32 Ark_SourceType;
typedef struct Opt_Ark_SourceType { enum Ark_Tag tag; Ark_SourceType value; } Opt_Ark_SourceType;
typedef struct EventTarget {
    struct Area area;
} EventTarget;
typedef struct Opt_EventTarget {
    enum Ark_Tag tag;
    EventTarget value;
} Opt_EventTarget;
typedef struct RichEditorLayoutStyle {
    struct Opt_Union_Ark_Length_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length margin;
    struct Opt_Union_Ark_Length_Literal_topLeft_Opt_Ark_Length_topRight_Opt_Ark_Length_bottomLeft_Opt_Ark_Length_bottomRight_Opt_Ark_Length borderRadius;
} RichEditorLayoutStyle;
typedef struct Opt_RichEditorLayoutStyle {
    enum Ark_Tag tag;
    RichEditorLayoutStyle value;
} Opt_RichEditorLayoutStyle;
typedef Ark_Int32 Ark_ImageFit;
typedef struct Opt_Ark_ImageFit { enum Ark_Tag tag; Ark_ImageFit value; } Opt_Ark_ImageFit;
typedef Ark_Int32 Ark_ImageSpanAlignment;
typedef struct Opt_Ark_ImageSpanAlignment { enum Ark_Tag tag; Ark_ImageSpanAlignment value; } Opt_Ark_ImageSpanAlignment;
typedef struct Tuple_Ark_Number_Ark_Number {
    Ark_Number value0;
    Ark_Number value1;
} Tuple_Ark_Number_Ark_Number;
typedef struct Opt_Tuple_Ark_Number_Ark_Number {
    enum Ark_Tag tag;
    Tuple_Ark_Number_Ark_Number value;
} Opt_Tuple_Ark_Number_Ark_Number;
typedef Ark_Int32 Ark_LineBreakStrategy;
typedef struct Opt_Ark_LineBreakStrategy { enum Ark_Tag tag; Ark_LineBreakStrategy value; } Opt_Ark_LineBreakStrategy;
typedef Ark_Int32 Ark_WordBreak;
typedef struct Opt_Ark_WordBreak { enum Ark_Tag tag; Ark_WordBreak value; } Opt_Ark_WordBreak;
typedef struct Union_Ark_Length_LeadingMarginPlaceholder {
    Ark_Int32 selector;
    union {
        Ark_Length value0;
        struct LeadingMarginPlaceholder value1;
    };
} Union_Ark_Length_LeadingMarginPlaceholder;
typedef struct Opt_Union_Ark_Length_LeadingMarginPlaceholder {
    enum Ark_Tag tag;
    Union_Ark_Length_LeadingMarginPlaceholder value;
} Opt_Union_Ark_Length_LeadingMarginPlaceholder;
typedef Ark_Int32 Ark_TextAlign;
typedef struct Opt_Ark_TextAlign { enum Ark_Tag tag; Ark_TextAlign value; } Opt_Ark_TextAlign;
typedef Ark_Int32 Ark_SymbolRenderingStrategy;
typedef struct Opt_Ark_SymbolRenderingStrategy { enum Ark_Tag tag; Ark_SymbolRenderingStrategy value; } Opt_Ark_SymbolRenderingStrategy;
typedef Ark_Int32 Ark_SymbolEffectStrategy;
typedef struct Opt_Ark_SymbolEffectStrategy { enum Ark_Tag tag; Ark_SymbolEffectStrategy value; } Opt_Ark_SymbolEffectStrategy;
typedef struct Union_Ark_Number_Ark_FontWeight_Ark_String {
    Ark_Int32 selector;
    union {
        Ark_Number value0;
        Ark_FontWeight value1;
        Ark_String value2;
    };
} Union_Ark_Number_Ark_FontWeight_Ark_String;
typedef struct Opt_Union_Ark_Number_Ark_FontWeight_Ark_String {
    enum Ark_Tag tag;
    Union_Ark_Number_Ark_FontWeight_Ark_String value;
} Opt_Union_Ark_Number_Ark_FontWeight_Ark_String;
typedef struct Array_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource {
    struct Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource* array;
    Ark_Int32 length;
} Array_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource;
typedef struct Opt_Array_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource {
    enum Ark_Tag tag;
    Array_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource value;
} Opt_Array_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource;
typedef struct Union_Ark_Number_Ark_String_Ark_Resource {
    Ark_Int32 selector;
    union {
        Ark_Number value0;
        Ark_String value1;
        Ark_Resource value2;
    };
} Union_Ark_Number_Ark_String_Ark_Resource;
typedef struct Opt_Union_Ark_Number_Ark_String_Ark_Resource {
    enum Ark_Tag tag;
    Union_Ark_Number_Ark_String_Ark_Resource value;
} Opt_Union_Ark_Number_Ark_String_Ark_Resource;
typedef struct DecorationStyleResult {
    Ark_TextDecorationType type;
    struct Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource color;
    Opt_Ark_TextDecorationStyle style;
} DecorationStyleResult;
typedef struct Opt_DecorationStyleResult {
    enum Ark_Tag tag;
    DecorationStyleResult value;
} Opt_DecorationStyleResult;
typedef struct Union_Ark_Number_LeadingMarginPlaceholder {
    Ark_Int32 selector;
    union {
        Ark_Number value0;
        struct LeadingMarginPlaceholder value1;
    };
} Union_Ark_Number_LeadingMarginPlaceholder;
typedef struct Opt_Union_Ark_Number_LeadingMarginPlaceholder {
    enum Ark_Tag tag;
    Union_Ark_Number_LeadingMarginPlaceholder value;
} Opt_Union_Ark_Number_LeadingMarginPlaceholder;
typedef Ark_Int32 Ark_TextOverflow;
typedef struct Opt_Ark_TextOverflow { enum Ark_Tag tag; Ark_TextOverflow value; } Opt_Ark_TextOverflow;
typedef struct ImageAttachmentLayoutStyle {
    struct Opt_Union_Ark_CustomObject_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length margin;
    struct Opt_Union_Ark_CustomObject_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length padding;
    struct Opt_Union_Ark_CustomObject_Literal_topLeft_Opt_Ark_Length_topRight_Opt_Ark_Length_bottomLeft_Opt_Ark_Length_bottomRight_Opt_Ark_Length borderRadius;
} ImageAttachmentLayoutStyle;
typedef struct Opt_ImageAttachmentLayoutStyle {
    enum Ark_Tag tag;
    ImageAttachmentLayoutStyle value;
} Opt_ImageAttachmentLayoutStyle;
typedef struct SizeOptions {
    Opt_Ark_Length width;
    Opt_Ark_Length height;
} SizeOptions;
typedef struct Opt_SizeOptions {
    enum Ark_Tag tag;
    SizeOptions value;
} Opt_SizeOptions;
typedef struct RichEditorRange {
    Opt_Ark_Number start;
    Opt_Ark_Number end;
} RichEditorRange;
typedef struct Opt_RichEditorRange {
    enum Ark_Tag tag;
    RichEditorRange value;
} Opt_RichEditorRange;
typedef struct Union_Ark_Number_Ark_String {
    Ark_Int32 selector;
    union {
        Ark_Number value0;
        Ark_String value1;
    };
} Union_Ark_Number_Ark_String;
typedef struct Opt_Union_Ark_Number_Ark_String {
    enum Ark_Tag tag;
    Union_Ark_Number_Ark_String value;
} Opt_Union_Ark_Number_Ark_String;
typedef struct Union_ShadowOptions_Array_ShadowOptions {
    Ark_Int32 selector;
    union {
        struct ShadowOptions value0;
        struct Array_ShadowOptions value1;
    };
} Union_ShadowOptions_Array_ShadowOptions;
typedef struct Opt_Union_ShadowOptions_Array_ShadowOptions {
    enum Ark_Tag tag;
    Union_ShadowOptions_Array_ShadowOptions value;
} Opt_Union_ShadowOptions_Array_ShadowOptions;
typedef struct DecorationStyleInterface {
    Ark_TextDecorationType type;
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource color;
    Opt_Ark_TextDecorationStyle style;
} DecorationStyleInterface;
typedef struct Opt_DecorationStyleInterface {
    enum Ark_Tag tag;
    DecorationStyleInterface value;
} Opt_DecorationStyleInterface;
typedef struct Union_Ark_Length_Ark_Number {
    Ark_Int32 selector;
    union {
        Ark_Length value0;
        Ark_Number value1;
    };
} Union_Ark_Length_Ark_Number;
typedef struct Opt_Union_Ark_Length_Ark_Number {
    enum Ark_Tag tag;
    Union_Ark_Length_Ark_Number value;
} Opt_Union_Ark_Length_Ark_Number;
typedef struct Union_Ark_Curve_ICurve {
    Ark_Int32 selector;
    union {
        Ark_Curve value0;
        struct ICurve value1;
    };
} Union_Ark_Curve_ICurve;
typedef struct Opt_Union_Ark_Curve_ICurve {
    enum Ark_Tag tag;
    Union_Ark_Curve_ICurve value;
} Opt_Union_Ark_Curve_ICurve;
typedef struct LocalizedPadding {
    Opt_Ark_CustomObject top;
    Opt_Ark_CustomObject end;
    Opt_Ark_CustomObject bottom;
    Opt_Ark_CustomObject start;
} LocalizedPadding;
typedef struct Opt_LocalizedPadding {
    enum Ark_Tag tag;
    LocalizedPadding value;
} Opt_LocalizedPadding;
typedef struct Font {
    Opt_Ark_Length size;
    struct Opt_Union_Ark_FontWeight_Ark_Number_Ark_String weight;
    struct Opt_Union_Ark_String_Ark_Resource family;
    Opt_Ark_FontStyle style;
} Font;
typedef struct Opt_Font {
    enum Ark_Tag tag;
    Font value;
} Opt_Font;
typedef Ark_Int32 Ark_TextHeightAdaptivePolicy;
typedef struct Opt_Ark_TextHeightAdaptivePolicy { enum Ark_Tag tag; Ark_TextHeightAdaptivePolicy value; } Opt_Ark_TextHeightAdaptivePolicy;
typedef struct Union_Ark_Number_Union_Ark_String_Ark_Resource {
    Ark_Int32 selector;
    union {
        Ark_Number value0;
        struct Union_Ark_String_Ark_Resource value1;
    };
} Union_Ark_Number_Union_Ark_String_Ark_Resource;
typedef struct Opt_Union_Ark_Number_Union_Ark_String_Ark_Resource {
    enum Ark_Tag tag;
    Union_Ark_Number_Union_Ark_String_Ark_Resource value;
} Opt_Union_Ark_Number_Union_Ark_String_Ark_Resource;
typedef struct CommonShapeMethod {
} CommonShapeMethod;
typedef struct Opt_CommonShapeMethod {
    enum Ark_Tag tag;
    CommonShapeMethod value;
} Opt_CommonShapeMethod;
typedef Ark_Materialized TextEditControllerEx;
typedef struct Opt_TextEditControllerEx {
    enum Ark_Tag tag;
    TextEditControllerEx value;
} Opt_TextEditControllerEx;
typedef struct Array_Ark_CustomObject {
    Ark_CustomObject* array;
    Ark_Int32 length;
} Array_Ark_CustomObject;
typedef struct Opt_Array_Ark_CustomObject {
    enum Ark_Tag tag;
    Array_Ark_CustomObject value;
} Opt_Array_Ark_CustomObject;
typedef Ark_Int32 Ark_TitleHeight;
typedef struct Opt_Ark_TitleHeight { enum Ark_Tag tag; Ark_TitleHeight value; } Opt_Ark_TitleHeight;
typedef struct Union_Ark_Function_Ark_Undefined {
    Ark_Int32 selector;
    union {
        struct Ark_Function value0;
        Ark_Undefined value1;
    };
} Union_Ark_Function_Ark_Undefined;
typedef struct Opt_Union_Ark_Function_Ark_Undefined {
    enum Ark_Tag tag;
    Union_Ark_Function_Ark_Undefined value;
} Opt_Union_Ark_Function_Ark_Undefined;
typedef struct Union_Ark_Length_GridRowSizeOption {
    Ark_Int32 selector;
    union {
        Ark_Length value0;
        struct GridRowSizeOption value1;
    };
} Union_Ark_Length_GridRowSizeOption;
typedef struct Opt_Union_Ark_Length_GridRowSizeOption {
    enum Ark_Tag tag;
    Union_Ark_Length_GridRowSizeOption value;
} Opt_Union_Ark_Length_GridRowSizeOption;
typedef struct Array_Tuple_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Ark_Number {
    struct Tuple_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Ark_Number* array;
    Ark_Int32 length;
} Array_Tuple_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Ark_Number;
typedef struct Opt_Array_Tuple_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Ark_Number {
    enum Ark_Tag tag;
    Array_Tuple_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Ark_Number value;
} Opt_Array_Tuple_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Ark_Number;
typedef Ark_Int32 Ark_GradientDirection;
typedef struct Opt_Ark_GradientDirection { enum Ark_Tag tag; Ark_GradientDirection value; } Opt_Ark_GradientDirection;
typedef struct Union_Ark_String_Ark_String_Ark_String_Ark_String_Ark_String_Ark_String {
    Ark_Int32 selector;
    union {
        struct Ark_String value0;
        struct Ark_String value1;
        struct Ark_String value2;
        struct Ark_String value3;
        struct Ark_String value4;
        struct Ark_String value5;
    };
} Union_Ark_String_Ark_String_Ark_String_Ark_String_Ark_String_Ark_String;
typedef struct Opt_Union_Ark_String_Ark_String_Ark_String_Ark_String_Ark_String_Ark_String {
    enum Ark_Tag tag;
    Union_Ark_String_Ark_String_Ark_String_Ark_String_Ark_String_Ark_String value;
} Opt_Union_Ark_String_Ark_String_Ark_String_Ark_String_Ark_String_Ark_String;
typedef struct Union_Ark_String_Ark_String_Ark_String_Ark_String_Ark_String {
    Ark_Int32 selector;
    union {
        struct Ark_String value0;
        struct Ark_String value1;
        struct Ark_String value2;
        struct Ark_String value3;
        struct Ark_String value4;
    };
} Union_Ark_String_Ark_String_Ark_String_Ark_String_Ark_String;
typedef struct Opt_Union_Ark_String_Ark_String_Ark_String_Ark_String_Ark_String {
    enum Ark_Tag tag;
    Union_Ark_String_Ark_String_Ark_String_Ark_String_Ark_String value;
} Opt_Union_Ark_String_Ark_String_Ark_String_Ark_String_Ark_String;
typedef struct Union_Ark_String_Ark_String_Ark_String {
    Ark_Int32 selector;
    union {
        struct Ark_String value0;
        struct Ark_String value1;
        struct Ark_String value2;
    };
} Union_Ark_String_Ark_String_Ark_String;
typedef struct Opt_Union_Ark_String_Ark_String_Ark_String {
    enum Ark_Tag tag;
    Union_Ark_String_Ark_String_Ark_String value;
} Opt_Union_Ark_String_Ark_String_Ark_String;
typedef struct Union_Ark_String_Ark_Number_CanvasGradient_CanvasPattern {
    Ark_Int32 selector;
    union {
        Ark_String value0;
        Ark_Number value1;
        CanvasGradient value2;
        CanvasPattern value3;
    };
} Union_Ark_String_Ark_Number_CanvasGradient_CanvasPattern;
typedef struct Opt_Union_Ark_String_Ark_Number_CanvasGradient_CanvasPattern {
    enum Ark_Tag tag;
    Union_Ark_String_Ark_Number_CanvasGradient_CanvasPattern value;
} Opt_Union_Ark_String_Ark_Number_CanvasGradient_CanvasPattern;
typedef Ark_Materialized CanvasPath;
typedef struct Opt_CanvasPath {
    enum Ark_Tag tag;
    CanvasPath value;
} Opt_CanvasPath;
typedef Ark_Int32 Ark_BadgePosition;
typedef struct Opt_Ark_BadgePosition { enum Ark_Tag tag; Ark_BadgePosition value; } Opt_Ark_BadgePosition;
typedef Ark_Int32 Ark_BorderStyle;
typedef struct Opt_Ark_BorderStyle { enum Ark_Tag tag; Ark_BorderStyle value; } Opt_Ark_BorderStyle;
typedef struct Union_Ark_SheetSize_Ark_Length {
    Ark_Int32 selector;
    union {
        Ark_SheetSize value0;
        Ark_Length value1;
    };
} Union_Ark_SheetSize_Ark_Length;
typedef struct Opt_Union_Ark_SheetSize_Ark_Length {
    enum Ark_Tag tag;
    Union_Ark_SheetSize_Ark_Length value;
} Opt_Union_Ark_SheetSize_Ark_Length;
typedef struct TransitionEffect {
} TransitionEffect;
typedef struct Opt_TransitionEffect {
    enum Ark_Tag tag;
    TransitionEffect value;
} Opt_TransitionEffect;
typedef Ark_Int32 Ark_MenuPreviewMode;
typedef struct Opt_Ark_MenuPreviewMode { enum Ark_Tag tag; Ark_MenuPreviewMode value; } Opt_Ark_MenuPreviewMode;
typedef Ark_Int32 Ark_ShadowStyle;
typedef struct Opt_Ark_ShadowStyle { enum Ark_Tag tag; Ark_ShadowStyle value; } Opt_Ark_ShadowStyle;
typedef struct Literal_color_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource {
    struct Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource color;
} Literal_color_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource;
typedef struct Opt_Literal_color_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource {
    enum Ark_Tag tag;
    Literal_color_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource value;
} Opt_Literal_color_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource;
typedef Ark_Int32 Ark_OutlineStyle;
typedef struct Opt_Ark_OutlineStyle { enum Ark_Tag tag; Ark_OutlineStyle value; } Opt_Ark_OutlineStyle;
typedef struct Array_TouchObject {
    struct TouchObject* array;
    Ark_Int32 length;
} Array_TouchObject;
typedef struct Opt_Array_TouchObject {
    enum Ark_Tag tag;
    Array_TouchObject value;
} Opt_Array_TouchObject;
typedef Ark_Int32 Ark_TouchType;
typedef struct Opt_Ark_TouchType { enum Ark_Tag tag; Ark_TouchType value; } Opt_Ark_TouchType;
typedef struct BaseEvent {
    struct EventTarget target;
    Ark_Number timestamp;
    Ark_SourceType source;
    Opt_Ark_Number axisHorizontal;
    Opt_Ark_Number axisVertical;
    Ark_Number pressure;
    Ark_Number tiltX;
    Ark_Number tiltY;
    Ark_SourceTool sourceTool;
} BaseEvent;
typedef struct Opt_BaseEvent {
    enum Ark_Tag tag;
    BaseEvent value;
} Opt_BaseEvent;
typedef struct Map_Ark_String_Ark_String {
    Ark_Int32 size;
    Ark_String* keys;
    Ark_String* values;
} Map_Ark_String_Ark_String;
typedef struct Opt_Map_Ark_String_Ark_String {
    enum Ark_Tag tag;
    Map_Ark_String_Ark_String value;
} Opt_Map_Ark_String_Ark_String;
typedef Ark_Materialized WebResourceRequest;
typedef struct Opt_WebResourceRequest {
    enum Ark_Tag tag;
    WebResourceRequest value;
} Opt_WebResourceRequest;
typedef struct RichEditorImageSpanStyleResult {
    struct Tuple_Ark_Number_Ark_Number size;
    Ark_ImageSpanAlignment verticalAlign;
    Ark_ImageFit objectFit;
    struct Opt_RichEditorLayoutStyle layoutStyle;
} RichEditorImageSpanStyleResult;
typedef struct Opt_RichEditorImageSpanStyleResult {
    enum Ark_Tag tag;
    RichEditorImageSpanStyleResult value;
} Opt_RichEditorImageSpanStyleResult;
typedef struct RichEditorSpanPosition {
    Ark_Number spanIndex;
    struct Tuple_Ark_Number_Ark_Number spanRange;
} RichEditorSpanPosition;
typedef struct Opt_RichEditorSpanPosition {
    enum Ark_Tag tag;
    RichEditorSpanPosition value;
} Opt_RichEditorSpanPosition;
typedef struct RichEditorParagraphStyle {
    Opt_Ark_TextAlign textAlign;
    struct Opt_Union_Ark_Length_LeadingMarginPlaceholder leadingMargin;
    Opt_Ark_WordBreak wordBreak;
    Opt_Ark_LineBreakStrategy lineBreakStrategy;
} RichEditorParagraphStyle;
typedef struct Opt_RichEditorParagraphStyle {
    enum Ark_Tag tag;
    RichEditorParagraphStyle value;
} Opt_RichEditorParagraphStyle;
typedef struct RichEditorSymbolSpanStyle {
    struct Opt_Union_Ark_Number_Ark_String_Ark_Resource fontSize;
    struct Opt_Array_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource fontColor;
    struct Opt_Union_Ark_Number_Ark_FontWeight_Ark_String fontWeight;
    Opt_Ark_SymbolEffectStrategy effectStrategy;
    Opt_Ark_SymbolRenderingStrategy renderingStrategy;
} RichEditorSymbolSpanStyle;
typedef struct Opt_RichEditorSymbolSpanStyle {
    enum Ark_Tag tag;
    RichEditorSymbolSpanStyle value;
} Opt_RichEditorSymbolSpanStyle;
typedef struct RichEditorTextStyleResult {
    struct Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource fontColor;
    Ark_Number fontSize;
    Ark_FontStyle fontStyle;
    Ark_Number fontWeight;
    Ark_String fontFamily;
    struct DecorationStyleResult decoration;
    Opt_Ark_Number letterSpacing;
    Opt_Ark_Number lineHeight;
    Opt_Ark_String fontFeature;
} RichEditorTextStyleResult;
typedef struct Opt_RichEditorTextStyleResult {
    enum Ark_Tag tag;
    RichEditorTextStyleResult value;
} Opt_RichEditorTextStyleResult;
typedef struct UserDataSpan {
} UserDataSpan;
typedef struct Opt_UserDataSpan {
    enum Ark_Tag tag;
    UserDataSpan value;
} Opt_UserDataSpan;
typedef Ark_Materialized CustomSpan;
typedef struct Opt_CustomSpan {
    enum Ark_Tag tag;
    CustomSpan value;
} Opt_CustomSpan;
typedef struct LineHeightStyle {
    Ark_Number lineHeight;
} LineHeightStyle;
typedef struct Opt_LineHeightStyle {
    enum Ark_Tag tag;
    LineHeightStyle value;
} Opt_LineHeightStyle;
typedef struct ParagraphStyle {
    Opt_Ark_TextAlign textAlign;
    Opt_Ark_Number textIndent;
    Opt_Ark_Number maxLines;
    Opt_Ark_TextOverflow overflow;
    Opt_Ark_WordBreak wordBreak;
    struct Opt_Union_Ark_Number_LeadingMarginPlaceholder leadingMargin;
} ParagraphStyle;
typedef struct Opt_ParagraphStyle {
    enum Ark_Tag tag;
    ParagraphStyle value;
} Opt_ParagraphStyle;
typedef struct ImageAttachment {
    Ark_CustomObject value;
    struct Opt_SizeOptions size;
    Opt_Ark_ImageSpanAlignment verticalAlign;
    Opt_Ark_ImageFit objectFit;
    struct Opt_ImageAttachmentLayoutStyle layoutStyle;
} ImageAttachment;
typedef struct Opt_ImageAttachment {
    enum Ark_Tag tag;
    ImageAttachment value;
} Opt_ImageAttachment;
typedef struct GestureStyle {
} GestureStyle;
typedef struct Opt_GestureStyle {
    enum Ark_Tag tag;
    GestureStyle value;
} Opt_GestureStyle;
typedef struct TextShadowStyle {
    struct Array_ShadowOptions textShadow;
} TextShadowStyle;
typedef struct Opt_TextShadowStyle {
    enum Ark_Tag tag;
    TextShadowStyle value;
} Opt_TextShadowStyle;
typedef struct LetterSpacingStyle {
    Ark_Number letterSpacing;
} LetterSpacingStyle;
typedef struct Opt_LetterSpacingStyle {
    enum Ark_Tag tag;
    LetterSpacingStyle value;
} Opt_LetterSpacingStyle;
typedef struct BaselineOffsetStyle {
    Ark_Number baselineOffset;
} BaselineOffsetStyle;
typedef struct Opt_BaselineOffsetStyle {
    enum Ark_Tag tag;
    BaselineOffsetStyle value;
} Opt_BaselineOffsetStyle;
typedef struct DecorationStyle {
    Ark_TextDecorationType type;
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource color;
    Opt_Ark_TextDecorationStyle style;
} DecorationStyle;
typedef struct Opt_DecorationStyle {
    enum Ark_Tag tag;
    DecorationStyle value;
} Opt_DecorationStyle;
typedef struct TextStyle {
    Opt_Ark_WordBreak wordBreak;
} TextStyle;
typedef struct Opt_TextStyle {
    enum Ark_Tag tag;
    TextStyle value;
} Opt_TextStyle;
typedef struct RichEditorSpanStyleOptions {
    Opt_Ark_Number start;
    Opt_Ark_Number end;
} RichEditorSpanStyleOptions;
typedef struct Opt_RichEditorSpanStyleOptions {
    enum Ark_Tag tag;
    RichEditorSpanStyleOptions value;
} Opt_RichEditorSpanStyleOptions;
typedef struct RichEditorImageSpanStyle {
    struct Opt_Tuple_Ark_Length_Ark_Length size;
    Opt_Ark_ImageSpanAlignment verticalAlign;
    Opt_Ark_ImageFit objectFit;
    struct Opt_RichEditorLayoutStyle layoutStyle;
} RichEditorImageSpanStyle;
typedef struct Opt_RichEditorImageSpanStyle {
    enum Ark_Tag tag;
    RichEditorImageSpanStyle value;
} Opt_RichEditorImageSpanStyle;
typedef struct RichEditorTextStyle {
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource fontColor;
    struct Opt_Union_Ark_Length_Ark_Number fontSize;
    Opt_Ark_FontStyle fontStyle;
    struct Opt_Union_Ark_Number_Ark_FontWeight_Ark_String fontWeight;
    struct Opt_Union_Ark_String_Ark_Resource fontFamily;
    struct Opt_DecorationStyleInterface decoration;
    struct Opt_Union_ShadowOptions_Array_ShadowOptions textShadow;
    struct Opt_Union_Ark_Number_Ark_String letterSpacing;
    struct Opt_Union_Ark_Number_Ark_String_Ark_Resource lineHeight;
    Opt_Ark_String fontFeature;
} RichEditorTextStyle;
typedef struct Opt_RichEditorTextStyle {
    enum Ark_Tag tag;
    RichEditorTextStyle value;
} Opt_RichEditorTextStyle;
typedef struct ScrollAnimationOptions {
    Opt_Ark_Number duration;
    struct Opt_Union_Ark_Curve_ICurve curve;
    Opt_Ark_Boolean canOverScroll;
} ScrollAnimationOptions;
typedef struct Opt_ScrollAnimationOptions {
    enum Ark_Tag tag;
    ScrollAnimationOptions value;
} Opt_ScrollAnimationOptions;
typedef Ark_Materialized RelativeIndexable;
typedef struct Union_Ark_String_Ark_CustomObject_Ark_Resource {
    Ark_Int32 selector;
    union {
        Ark_String value0;
        Ark_CustomObject value1;
        Ark_Resource value2;
    };
} Union_Ark_String_Ark_CustomObject_Ark_Resource;
typedef struct Opt_Union_Ark_String_Ark_CustomObject_Ark_Resource {
    enum Ark_Tag tag;
    Union_Ark_String_Ark_CustomObject_Ark_Resource value;
} Opt_Union_Ark_String_Ark_CustomObject_Ark_Resource;
typedef Ark_Materialized ImageAnalyzerController;
typedef struct Opt_ImageAnalyzerController {
    enum Ark_Tag tag;
    ImageAnalyzerController value;
} Opt_ImageAnalyzerController;
typedef int32_t Ark_ImageAnalyzerType;
typedef struct Array_Ark_ImageAnalyzerType {
    Ark_ImageAnalyzerType* array;
    Ark_Int32 length;
} Array_Ark_ImageAnalyzerType;
typedef int32_t Ark_ImageAnalyzerType;
typedef struct Opt_Array_Ark_ImageAnalyzerType {
    enum Ark_Tag tag;
    Array_Ark_ImageAnalyzerType value;
} Opt_Array_Ark_ImageAnalyzerType;
typedef Ark_Materialized WebController;
typedef struct Opt_WebController {
    enum Ark_Tag tag;
    WebController value;
} Opt_WebController;
typedef Ark_Int32 Ark_PlaybackSpeed;
typedef struct Opt_Ark_PlaybackSpeed { enum Ark_Tag tag; Ark_PlaybackSpeed value; } Opt_Ark_PlaybackSpeed;
typedef struct Array_Ark_Number {
    Ark_Number* array;
    Ark_Int32 length;
} Array_Ark_Number;
typedef struct Opt_Array_Ark_Number {
    enum Ark_Tag tag;
    Array_Ark_Number value;
} Opt_Array_Ark_Number;
typedef struct Array_Ark_String {
    Ark_String* array;
    Ark_Int32 length;
} Array_Ark_String;
typedef struct Opt_Array_Ark_String {
    enum Ark_Tag tag;
    Array_Ark_String value;
} Opt_Array_Ark_String;
typedef struct Array_TextCascadePickerRangeContent {
    struct TextCascadePickerRangeContent* array;
    Ark_Int32 length;
} Array_TextCascadePickerRangeContent;
typedef struct Opt_Array_TextCascadePickerRangeContent {
    enum Ark_Tag tag;
    Array_TextCascadePickerRangeContent value;
} Opt_Array_TextCascadePickerRangeContent;
typedef struct Array_TextPickerRangeContent {
    struct TextPickerRangeContent* array;
    Ark_Int32 length;
} Array_TextPickerRangeContent;
typedef struct Opt_Array_TextPickerRangeContent {
    enum Ark_Tag tag;
    Array_TextPickerRangeContent value;
} Opt_Array_TextPickerRangeContent;
typedef struct Array_Array_Ark_String {
    struct Array_Ark_String* array;
    Ark_Int32 length;
} Array_Array_Ark_String;
typedef struct Opt_Array_Array_Ark_String {
    enum Ark_Tag tag;
    Array_Array_Ark_String value;
} Opt_Array_Array_Ark_String;
typedef struct Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Ark_Undefined {
    Ark_Int32 selector;
    union {
        struct Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource value0;
        Ark_Undefined value1;
    };
} Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Ark_Undefined;
typedef struct Opt_Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Ark_Undefined {
    enum Ark_Tag tag;
    Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Ark_Undefined value;
} Opt_Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Ark_Undefined;
typedef Ark_Materialized TextContentControllerBase;
typedef struct Opt_TextContentControllerBase {
    enum Ark_Tag tag;
    TextContentControllerBase value;
} Opt_TextContentControllerBase;
typedef Ark_Int32 Ark_MarqueeStartPolicy;
typedef struct Opt_Ark_MarqueeStartPolicy { enum Ark_Tag tag; Ark_MarqueeStartPolicy value; } Opt_Ark_MarqueeStartPolicy;
typedef struct TabBarIconStyle {
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource selectedColor;
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource unselectedColor;
} TabBarIconStyle;
typedef struct Opt_TabBarIconStyle {
    enum Ark_Tag tag;
    TabBarIconStyle value;
} Opt_TabBarIconStyle;
typedef Ark_Int32 Ark_VerticalAlign;
typedef struct Opt_Ark_VerticalAlign { enum Ark_Tag tag; Ark_VerticalAlign value; } Opt_Ark_VerticalAlign;
typedef Ark_Int32 Ark_LayoutMode;
typedef struct Opt_Ark_LayoutMode { enum Ark_Tag tag; Ark_LayoutMode value; } Opt_Ark_LayoutMode;
typedef struct Union_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length_Ark_Length_LocalizedPadding {
    Ark_Int32 selector;
    union {
        struct Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length value0;
        Ark_Length value1;
        struct LocalizedPadding value2;
    };
} Union_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length_Ark_Length_LocalizedPadding;
typedef struct Opt_Union_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length_Ark_Length_LocalizedPadding {
    enum Ark_Tag tag;
    Union_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length_Ark_Length_LocalizedPadding value;
} Opt_Union_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length_Ark_Length_LocalizedPadding;
typedef struct LabelStyle {
    Opt_Ark_TextOverflow overflow;
    Opt_Ark_Number maxLines;
    struct Opt_Union_Ark_Number_Union_Ark_String_Ark_Resource minFontSize;
    struct Opt_Union_Ark_Number_Union_Ark_String_Ark_Resource maxFontSize;
    Opt_Ark_TextHeightAdaptivePolicy heightAdaptivePolicy;
    struct Opt_Font font;
} LabelStyle;
typedef struct Opt_LabelStyle {
    enum Ark_Tag tag;
    LabelStyle value;
} Opt_LabelStyle;
typedef struct Union_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length_Ark_Length {
    Ark_Int32 selector;
    union {
        struct Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length value0;
        Ark_Length value1;
    };
} Union_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length_Ark_Length;
typedef struct Opt_Union_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length_Ark_Length {
    enum Ark_Tag tag;
    Union_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length_Ark_Length value;
} Opt_Union_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length_Ark_Length;
typedef struct BoardStyle {
    Opt_Ark_Length borderRadius;
} BoardStyle;
typedef struct Opt_BoardStyle {
    enum Ark_Tag tag;
    BoardStyle value;
} Opt_BoardStyle;
typedef Ark_Int32 Ark_SelectedMode;
typedef struct Opt_Ark_SelectedMode { enum Ark_Tag tag; Ark_SelectedMode value; } Opt_Ark_SelectedMode;
typedef struct IndicatorStyle {
    Opt_Ark_Length left;
    Opt_Ark_Length top;
    Opt_Ark_Length right;
    Opt_Ark_Length bottom;
    Opt_Ark_Length size;
    Opt_Ark_Boolean mask;
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource color;
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource selectedColor;
} IndicatorStyle;
typedef struct Opt_IndicatorStyle {
    enum Ark_Tag tag;
    IndicatorStyle value;
} Opt_IndicatorStyle;
typedef struct Union_Ark_String_Ark_Number {
    Ark_Int32 selector;
    union {
        struct Ark_String value0;
        Ark_Number value1;
    };
} Union_Ark_String_Ark_Number;
typedef struct Opt_Union_Ark_String_Ark_Number {
    enum Ark_Tag tag;
    Union_Ark_String_Ark_Number value;
} Opt_Union_Ark_String_Ark_Number;
typedef struct Indicator {
    Opt_Ark_Length _left;
    Opt_Ark_Length _top;
    Opt_Ark_Length _right;
    Opt_Ark_Length _bottom;
    Opt_Ark_CustomObject _start;
    Opt_Ark_CustomObject _end;
} Indicator;
typedef struct Opt_Indicator {
    enum Ark_Tag tag;
    Indicator value;
} Opt_Indicator;
typedef struct RectAttribute {
} RectAttribute;
typedef struct Opt_RectAttribute {
    enum Ark_Tag tag;
    RectAttribute value;
} Opt_RectAttribute;
typedef struct PathAttribute {
} PathAttribute;
typedef struct Opt_PathAttribute {
    enum Ark_Tag tag;
    PathAttribute value;
} Opt_PathAttribute;
typedef struct EllipseAttribute {
} EllipseAttribute;
typedef struct Opt_EllipseAttribute {
    enum Ark_Tag tag;
    EllipseAttribute value;
} Opt_EllipseAttribute;
typedef struct CircleAttribute {
} CircleAttribute;
typedef struct Opt_CircleAttribute {
    enum Ark_Tag tag;
    CircleAttribute value;
} Opt_CircleAttribute;
typedef struct DividerOptions {
    Opt_Ark_Length strokeWidth;
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource color;
    Opt_Ark_Length startMargin;
    Opt_Ark_Length endMargin;
} DividerOptions;
typedef struct Opt_DividerOptions {
    enum Ark_Tag tag;
    DividerOptions value;
} Opt_DividerOptions;
typedef struct Array_Ark_Length {
    Ark_Length* array;
    Ark_Int32 length;
} Array_Ark_Length;
typedef struct Opt_Array_Ark_Length {
    enum Ark_Tag tag;
    Array_Ark_Length value;
} Opt_Array_Ark_Length;
typedef Ark_Materialized StyledStringController;
typedef struct Opt_StyledStringController {
    enum Ark_Tag tag;
    StyledStringController value;
} Opt_StyledStringController;
typedef Ark_Materialized RichEditorBaseController;
typedef struct Opt_RichEditorBaseController {
    enum Ark_Tag tag;
    RichEditorBaseController value;
} Opt_RichEditorBaseController;
typedef struct Union_Ark_Number_Ark_String_Array_Ark_CustomObject {
    Ark_Int32 selector;
    union {
        Ark_Number value0;
        Ark_String value1;
        struct Array_Ark_CustomObject value2;
    };
} Union_Ark_Number_Ark_String_Array_Ark_CustomObject;
typedef struct Opt_Union_Ark_Number_Ark_String_Array_Ark_CustomObject {
    enum Ark_Tag tag;
    Union_Ark_Number_Ark_String_Array_Ark_CustomObject value;
} Opt_Union_Ark_Number_Ark_String_Array_Ark_CustomObject;
typedef struct Union_Ark_TitleHeight_Ark_Length {
    Ark_Int32 selector;
    union {
        Ark_TitleHeight value0;
        Ark_Length value1;
    };
} Union_Ark_TitleHeight_Ark_Length;
typedef struct Opt_Union_Ark_TitleHeight_Ark_Length {
    enum Ark_Tag tag;
    Union_Ark_TitleHeight_Ark_Length value;
} Opt_Union_Ark_TitleHeight_Ark_Length;
typedef struct SwipeActionItem {
    struct Opt_Union_Ark_Function_Ark_Undefined builder;
    Opt_Ark_Length actionAreaDistance;
    struct Opt_Ark_Function onAction;
    struct Opt_Ark_Function onEnterActionArea;
    struct Opt_Ark_Function onExitActionArea;
    struct Opt_Ark_Function onStateChange;
} SwipeActionItem;
typedef struct Opt_SwipeActionItem {
    enum Ark_Tag tag;
    SwipeActionItem value;
} Opt_SwipeActionItem;
typedef Ark_Int32 Ark_BreakpointsReference;
typedef struct Opt_Ark_BreakpointsReference { enum Ark_Tag tag; Ark_BreakpointsReference value; } Opt_Ark_BreakpointsReference;
typedef struct GridRowColumnOption {
    Opt_Ark_Number xs;
    Opt_Ark_Number sm;
    Opt_Ark_Number md;
    Opt_Ark_Number lg;
    Opt_Ark_Number xl;
    Opt_Ark_Number xxl;
} GridRowColumnOption;
typedef struct Opt_GridRowColumnOption {
    enum Ark_Tag tag;
    GridRowColumnOption value;
} Opt_GridRowColumnOption;
typedef struct GutterOption {
    struct Opt_Union_Ark_Length_GridRowSizeOption x;
    struct Opt_Union_Ark_Length_GridRowSizeOption y;
} GutterOption;
typedef struct Opt_GutterOption {
    enum Ark_Tag tag;
    GutterOption value;
} Opt_GutterOption;
typedef struct GridColColumnOption {
    Opt_Ark_Number xs;
    Opt_Ark_Number sm;
    Opt_Ark_Number md;
    Opt_Ark_Number lg;
    Opt_Ark_Number xl;
    Opt_Ark_Number xxl;
} GridColColumnOption;
typedef struct Opt_GridColColumnOption {
    enum Ark_Tag tag;
    GridColColumnOption value;
} Opt_GridColColumnOption;
typedef struct LinearGradient {
    struct Opt_Union_Ark_Number_Ark_String angle;
    Opt_Ark_GradientDirection direction;
    struct Array_Tuple_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Ark_Number colors;
    Opt_Ark_Boolean repeating;
} LinearGradient;
typedef struct Opt_LinearGradient {
    enum Ark_Tag tag;
    LinearGradient value;
} Opt_LinearGradient;
typedef Ark_Materialized CanvasRenderer;
typedef struct Opt_CanvasRenderer {
    enum Ark_Tag tag;
    CanvasRenderer value;
} Opt_CanvasRenderer;
typedef struct Array_CalendarDay {
    struct CalendarDay* array;
    Ark_Int32 length;
} Array_CalendarDay;
typedef struct Opt_Array_CalendarDay {
    enum Ark_Tag tag;
    Array_CalendarDay value;
} Opt_Array_CalendarDay;
typedef struct BadgeStyle {
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource color;
    struct Opt_Union_Ark_Number_Ark_String fontSize;
    struct Opt_Union_Ark_Number_Ark_String badgeSize;
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource badgeColor;
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource borderColor;
    Opt_Ark_Length borderWidth;
    struct Opt_Union_Ark_Number_Ark_FontWeight_Ark_String fontWeight;
} BadgeStyle;
typedef struct Opt_BadgeStyle {
    enum Ark_Tag tag;
    BadgeStyle value;
} Opt_BadgeStyle;
typedef struct Union_Ark_BadgePosition_Position {
    Ark_Int32 selector;
    union {
        Ark_BadgePosition value0;
        struct Position value1;
    };
} Union_Ark_BadgePosition_Position;
typedef struct Opt_Union_Ark_BadgePosition_Position {
    enum Ark_Tag tag;
    Union_Ark_BadgePosition_Position value;
} Opt_Union_Ark_BadgePosition_Position;
typedef struct Literal_top_Opt_Ark_BorderStyle_right_Opt_Ark_BorderStyle_bottom_Opt_Ark_BorderStyle_left_Opt_Ark_BorderStyle {
    Opt_Ark_BorderStyle top;
    Opt_Ark_BorderStyle right;
    Opt_Ark_BorderStyle bottom;
    Opt_Ark_BorderStyle left;
} Literal_top_Opt_Ark_BorderStyle_right_Opt_Ark_BorderStyle_bottom_Opt_Ark_BorderStyle_left_Opt_Ark_BorderStyle;
typedef struct Opt_Literal_top_Opt_Ark_BorderStyle_right_Opt_Ark_BorderStyle_bottom_Opt_Ark_BorderStyle_left_Opt_Ark_BorderStyle {
    enum Ark_Tag tag;
    Literal_top_Opt_Ark_BorderStyle_right_Opt_Ark_BorderStyle_bottom_Opt_Ark_BorderStyle_left_Opt_Ark_BorderStyle value;
} Opt_Literal_top_Opt_Ark_BorderStyle_right_Opt_Ark_BorderStyle_bottom_Opt_Ark_BorderStyle_left_Opt_Ark_BorderStyle;
typedef struct LocalizedEdgeColors {
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource top;
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource end;
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource bottom;
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource start;
} LocalizedEdgeColors;
typedef struct Opt_LocalizedEdgeColors {
    enum Ark_Tag tag;
    LocalizedEdgeColors value;
} Opt_LocalizedEdgeColors;
typedef struct Literal_top_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_right_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_bottom_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_left_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource {
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource top;
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource right;
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource bottom;
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource left;
} Literal_top_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_right_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_bottom_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_left_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource;
typedef struct Opt_Literal_top_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_right_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_bottom_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_left_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource {
    enum Ark_Tag tag;
    Literal_top_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_right_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_bottom_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_left_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource value;
} Opt_Literal_top_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_right_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_bottom_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_left_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource;
typedef struct LocalizedEdgeWidths {
    Opt_Ark_CustomObject top;
    Opt_Ark_CustomObject end;
    Opt_Ark_CustomObject bottom;
    Opt_Ark_CustomObject start;
} LocalizedEdgeWidths;
typedef struct Opt_LocalizedEdgeWidths {
    enum Ark_Tag tag;
    LocalizedEdgeWidths value;
} Opt_LocalizedEdgeWidths;
typedef struct SheetTitleOptions {
    struct Union_Ark_String_Ark_Resource title;
    struct Opt_Union_Ark_String_Ark_Resource subtitle;
} SheetTitleOptions;
typedef struct Opt_SheetTitleOptions {
    enum Ark_Tag tag;
    SheetTitleOptions value;
} Opt_SheetTitleOptions;
typedef Ark_Int32 Ark_BlurStyle;
typedef struct Opt_Ark_BlurStyle { enum Ark_Tag tag; Ark_BlurStyle value; } Opt_Ark_BlurStyle;
typedef struct ContextMenuAnimationOptions {
    Opt_Ark_CustomObject scale;
    struct Opt_TransitionEffect transition;
    Opt_Ark_CustomObject hoverScale;
} ContextMenuAnimationOptions;
typedef struct Opt_ContextMenuAnimationOptions {
    enum Ark_Tag tag;
    ContextMenuAnimationOptions value;
} Opt_ContextMenuAnimationOptions;
typedef struct Union_Ark_MenuPreviewMode_Union_Ark_Function_Ark_Undefined {
    Ark_Int32 selector;
    union {
        Ark_MenuPreviewMode value0;
        struct Union_Ark_Function_Ark_Undefined value1;
    };
} Union_Ark_MenuPreviewMode_Union_Ark_Function_Ark_Undefined;
typedef struct Opt_Union_Ark_MenuPreviewMode_Union_Ark_Function_Ark_Undefined {
    enum Ark_Tag tag;
    Union_Ark_MenuPreviewMode_Union_Ark_Function_Ark_Undefined value;
} Opt_Union_Ark_MenuPreviewMode_Union_Ark_Function_Ark_Undefined;
typedef Ark_Int32 Ark_Placement;
typedef struct Opt_Ark_Placement { enum Ark_Tag tag; Ark_Placement value; } Opt_Ark_Placement;
typedef struct Union_Ark_Boolean_Ark_Function {
    Ark_Int32 selector;
    union {
        Ark_Boolean value0;
        struct Ark_Function value1;
    };
} Union_Ark_Boolean_Ark_Function;
typedef struct Opt_Union_Ark_Boolean_Ark_Function {
    enum Ark_Tag tag;
    Union_Ark_Boolean_Ark_Function value;
} Opt_Union_Ark_Boolean_Ark_Function;
typedef struct Union_ShadowOptions_Ark_ShadowStyle {
    Ark_Int32 selector;
    union {
        struct ShadowOptions value0;
        Ark_ShadowStyle value1;
    };
} Union_ShadowOptions_Ark_ShadowStyle;
typedef struct Opt_Union_ShadowOptions_Ark_ShadowStyle {
    enum Ark_Tag tag;
    Union_ShadowOptions_Ark_ShadowStyle value;
} Opt_Union_ShadowOptions_Ark_ShadowStyle;
typedef Ark_Int32 Ark_ArrowPointPosition;
typedef struct Opt_Ark_ArrowPointPosition { enum Ark_Tag tag; Ark_ArrowPointPosition value; } Opt_Ark_ArrowPointPosition;
typedef struct Union_Ark_Boolean_Literal_color_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource {
    Ark_Int32 selector;
    union {
        Ark_Boolean value0;
        struct Literal_color_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource value1;
    };
} Union_Ark_Boolean_Literal_color_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource;
typedef struct Opt_Union_Ark_Boolean_Literal_color_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource {
    enum Ark_Tag tag;
    Union_Ark_Boolean_Literal_color_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource value;
} Opt_Union_Ark_Boolean_Literal_color_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource;
typedef struct Union_Ark_Color_Ark_String_Ark_Resource_Ark_Number {
    Ark_Int32 selector;
    union {
        Ark_Color value0;
        Ark_String value1;
        Ark_Resource value2;
        Ark_Number value3;
    };
} Union_Ark_Color_Ark_String_Ark_Resource_Ark_Number;
typedef struct Opt_Union_Ark_Color_Ark_String_Ark_Resource_Ark_Number {
    enum Ark_Tag tag;
    Union_Ark_Color_Ark_String_Ark_Resource_Ark_Number value;
} Opt_Union_Ark_Color_Ark_String_Ark_Resource_Ark_Number;
typedef struct PopupMessageOptions {
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource textColor;
    struct Opt_Font font;
} PopupMessageOptions;
typedef struct Opt_PopupMessageOptions {
    enum Ark_Tag tag;
    PopupMessageOptions value;
} Opt_PopupMessageOptions;
typedef struct Literal_value_Ark_String_action_Ark_Function {
    Ark_String value;
    struct Ark_Function action;
} Literal_value_Ark_String_action_Ark_Function;
typedef struct Opt_Literal_value_Ark_String_action_Ark_Function {
    enum Ark_Tag tag;
    Literal_value_Ark_String_action_Ark_Function value;
} Opt_Literal_value_Ark_String_action_Ark_Function;
typedef int32_t Ark_DragPreviewMode;
typedef struct Array_Ark_DragPreviewMode {
    Ark_DragPreviewMode* array;
    Ark_Int32 length;
} Array_Ark_DragPreviewMode;
typedef int32_t Ark_DragPreviewMode;
typedef struct Opt_Array_Ark_DragPreviewMode {
    enum Ark_Tag tag;
    Array_Ark_DragPreviewMode value;
} Opt_Array_Ark_DragPreviewMode;
typedef Ark_Int32 Ark_DragPreviewMode;
typedef struct Opt_Ark_DragPreviewMode { enum Ark_Tag tag; Ark_DragPreviewMode value; } Opt_Ark_DragPreviewMode;
typedef Ark_Int32 Ark_ClickEffectLevel;
typedef struct Opt_Ark_ClickEffectLevel { enum Ark_Tag tag; Ark_ClickEffectLevel value; } Opt_Ark_ClickEffectLevel;
typedef Ark_Int32 Ark_HorizontalAlign;
typedef struct Opt_Ark_HorizontalAlign { enum Ark_Tag tag; Ark_HorizontalAlign value; } Opt_Ark_HorizontalAlign;
typedef struct Literal_span_Ark_Number_offset_Ark_Number {
    Ark_Number span;
    Ark_Number offset;
} Literal_span_Ark_Number_offset_Ark_Number;
typedef struct Opt_Literal_span_Ark_Number_offset_Ark_Number {
    enum Ark_Tag tag;
    Literal_span_Ark_Number_offset_Ark_Number value;
} Opt_Literal_span_Ark_Number_offset_Ark_Number;
typedef struct GestureInterface {
} GestureInterface;
typedef struct Opt_GestureInterface {
    enum Ark_Tag tag;
    GestureInterface value;
} Opt_GestureInterface;
typedef struct RotateOptions {
    Opt_Ark_Number x;
    Opt_Ark_Number y;
    Opt_Ark_Number z;
    struct Opt_Union_Ark_Number_Ark_String centerX;
    struct Opt_Union_Ark_Number_Ark_String centerY;
    Opt_Ark_Number centerZ;
    Opt_Ark_Number perspective;
    struct Union_Ark_Number_Ark_String angle;
} RotateOptions;
typedef struct Opt_RotateOptions {
    enum Ark_Tag tag;
    RotateOptions value;
} Opt_RotateOptions;
typedef struct ScaleOptions {
    Opt_Ark_Number x;
    Opt_Ark_Number y;
    Opt_Ark_Number z;
    struct Opt_Union_Ark_Number_Ark_String centerX;
    struct Opt_Union_Ark_Number_Ark_String centerY;
} ScaleOptions;
typedef struct Opt_ScaleOptions {
    enum Ark_Tag tag;
    ScaleOptions value;
} Opt_ScaleOptions;
typedef struct TranslateOptions {
    struct Opt_Union_Ark_Number_Ark_String x;
    struct Opt_Union_Ark_Number_Ark_String y;
    struct Opt_Union_Ark_Number_Ark_String z;
} TranslateOptions;
typedef struct Opt_TranslateOptions {
    enum Ark_Tag tag;
    TranslateOptions value;
} Opt_TranslateOptions;
typedef Ark_Int32 Ark_TransitionType;
typedef struct Opt_Ark_TransitionType { enum Ark_Tag tag; Ark_TransitionType value; } Opt_Ark_TransitionType;
typedef struct Literal_top_Opt_Ark_OutlineStyle_right_Opt_Ark_OutlineStyle_bottom_Opt_Ark_OutlineStyle_left_Opt_Ark_OutlineStyle {
    Opt_Ark_OutlineStyle top;
    Opt_Ark_OutlineStyle right;
    Opt_Ark_OutlineStyle bottom;
    Opt_Ark_OutlineStyle left;
} Literal_top_Opt_Ark_OutlineStyle_right_Opt_Ark_OutlineStyle_bottom_Opt_Ark_OutlineStyle_left_Opt_Ark_OutlineStyle;
typedef struct Opt_Literal_top_Opt_Ark_OutlineStyle_right_Opt_Ark_OutlineStyle_bottom_Opt_Ark_OutlineStyle_left_Opt_Ark_OutlineStyle {
    enum Ark_Tag tag;
    Literal_top_Opt_Ark_OutlineStyle_right_Opt_Ark_OutlineStyle_bottom_Opt_Ark_OutlineStyle_left_Opt_Ark_OutlineStyle value;
} Opt_Literal_top_Opt_Ark_OutlineStyle_right_Opt_Ark_OutlineStyle_bottom_Opt_Ark_OutlineStyle_left_Opt_Ark_OutlineStyle;
typedef struct LocalizedBorderRadiuses {
    Opt_Ark_CustomObject topStart;
    Opt_Ark_CustomObject topEnd;
    Opt_Ark_CustomObject bottomStart;
    Opt_Ark_CustomObject bottomEnd;
} LocalizedBorderRadiuses;
typedef struct Opt_LocalizedBorderRadiuses {
    enum Ark_Tag tag;
    LocalizedBorderRadiuses value;
} Opt_LocalizedBorderRadiuses;
typedef struct BlurOptions {
    struct Tuple_Ark_Number_Ark_Number grayscale;
} BlurOptions;
typedef struct Opt_BlurOptions {
    enum Ark_Tag tag;
    BlurOptions value;
} Opt_BlurOptions;
typedef Ark_Int32 Ark_AdaptiveColor;
typedef struct Opt_Ark_AdaptiveColor { enum Ark_Tag tag; Ark_AdaptiveColor value; } Opt_Ark_AdaptiveColor;
typedef Ark_Int32 Ark_ThemeColorMode;
typedef struct Opt_Ark_ThemeColorMode { enum Ark_Tag tag; Ark_ThemeColorMode value; } Opt_Ark_ThemeColorMode;
typedef Ark_Materialized WebKeyboardController;
typedef struct Opt_WebKeyboardController {
    enum Ark_Tag tag;
    WebKeyboardController value;
} Opt_WebKeyboardController;
typedef Ark_Int32 Ark_RenderProcessNotRespondingReason;
typedef struct Opt_Ark_RenderProcessNotRespondingReason { enum Ark_Tag tag; Ark_RenderProcessNotRespondingReason value; } Opt_Ark_RenderProcessNotRespondingReason;
typedef Ark_Materialized EventResult;
typedef struct Opt_EventResult {
    enum Ark_Tag tag;
    EventResult value;
} Opt_EventResult;
typedef struct TouchEvent {
    struct EventTarget target;
    Ark_Number timestamp;
    Ark_SourceType source;
    Opt_Ark_Number axisHorizontal;
    Opt_Ark_Number axisVertical;
    Ark_Number pressure;
    Ark_Number tiltX;
    Ark_Number tiltY;
    Ark_SourceTool sourceTool;
    Ark_TouchType type;
    struct Array_TouchObject touches;
    struct Array_TouchObject changedTouches;
    struct Ark_Function stopPropagation;
    struct Ark_Function preventDefault;
} TouchEvent;
typedef struct Opt_TouchEvent {
    enum Ark_Tag tag;
    TouchEvent value;
} Opt_TouchEvent;
typedef struct NativeEmbedInfo {
    Opt_Ark_String id;
    Opt_Ark_String type;
    Opt_Ark_String src;
    struct Opt_Position position;
    Opt_Ark_Number width;
    Opt_Ark_Number height;
    Opt_Ark_String url;
    Opt_Ark_String tag;
    struct Opt_Map_Ark_String_Ark_String params;
} NativeEmbedInfo;
typedef struct Opt_NativeEmbedInfo {
    enum Ark_Tag tag;
    NativeEmbedInfo value;
} Opt_NativeEmbedInfo;
typedef Ark_Int32 Ark_NativeEmbedStatus;
typedef struct Opt_Ark_NativeEmbedStatus { enum Ark_Tag tag; Ark_NativeEmbedStatus value; } Opt_Ark_NativeEmbedStatus;
typedef Ark_Int32 Ark_WebNavigationType;
typedef struct Opt_Ark_WebNavigationType { enum Ark_Tag tag; Ark_WebNavigationType value; } Opt_Ark_WebNavigationType;
typedef Ark_Materialized DataResubmissionHandler;
typedef struct Opt_DataResubmissionHandler {
    enum Ark_Tag tag;
    DataResubmissionHandler value;
} Opt_DataResubmissionHandler;
typedef Ark_Materialized ControllerHandler;
typedef struct Opt_ControllerHandler {
    enum Ark_Tag tag;
    ControllerHandler value;
} Opt_ControllerHandler;
typedef Ark_Materialized ClientAuthenticationHandler;
typedef struct Opt_ClientAuthenticationHandler {
    enum Ark_Tag tag;
    ClientAuthenticationHandler value;
} Opt_ClientAuthenticationHandler;
typedef Ark_Int32 Ark_SslError;
typedef struct Opt_Ark_SslError { enum Ark_Tag tag; Ark_SslError value; } Opt_Ark_SslError;
typedef Ark_Materialized SslErrorHandler;
typedef struct Opt_SslErrorHandler {
    enum Ark_Tag tag;
    SslErrorHandler value;
} Opt_SslErrorHandler;
typedef Ark_Materialized WebContextMenuResult;
typedef struct Opt_WebContextMenuResult {
    enum Ark_Tag tag;
    WebContextMenuResult value;
} Opt_WebContextMenuResult;
typedef Ark_Materialized WebContextMenuParam;
typedef struct Opt_WebContextMenuParam {
    enum Ark_Tag tag;
    WebContextMenuParam value;
} Opt_WebContextMenuParam;
typedef Ark_Materialized ScreenCaptureHandler;
typedef struct Opt_ScreenCaptureHandler {
    enum Ark_Tag tag;
    ScreenCaptureHandler value;
} Opt_ScreenCaptureHandler;
typedef Ark_Materialized PermissionRequest;
typedef struct Opt_PermissionRequest {
    enum Ark_Tag tag;
    PermissionRequest value;
} Opt_PermissionRequest;
typedef Ark_Materialized HttpAuthHandler;
typedef struct Opt_HttpAuthHandler {
    enum Ark_Tag tag;
    HttpAuthHandler value;
} Opt_HttpAuthHandler;
typedef Ark_Materialized FullScreenExitHandler;
typedef struct Opt_FullScreenExitHandler {
    enum Ark_Tag tag;
    FullScreenExitHandler value;
} Opt_FullScreenExitHandler;
typedef Ark_Materialized FileSelectorParam;
typedef struct Opt_FileSelectorParam {
    enum Ark_Tag tag;
    FileSelectorParam value;
} Opt_FileSelectorParam;
typedef Ark_Materialized FileSelectorResult;
typedef struct Opt_FileSelectorResult {
    enum Ark_Tag tag;
    FileSelectorResult value;
} Opt_FileSelectorResult;
typedef struct Union_Ark_String_WebResourceRequest {
    Ark_Int32 selector;
    union {
        Ark_String value0;
        WebResourceRequest value1;
    };
} Union_Ark_String_WebResourceRequest;
typedef struct Opt_Union_Ark_String_WebResourceRequest {
    enum Ark_Tag tag;
    Union_Ark_String_WebResourceRequest value;
} Opt_Union_Ark_String_WebResourceRequest;
typedef Ark_Materialized WebResourceResponse;
typedef struct Opt_WebResourceResponse {
    enum Ark_Tag tag;
    WebResourceResponse value;
} Opt_WebResourceResponse;
typedef Ark_Materialized WebResourceError;
typedef struct Opt_WebResourceError {
    enum Ark_Tag tag;
    WebResourceError value;
} Opt_WebResourceError;
typedef Ark_Materialized ConsoleMessage;
typedef struct Opt_ConsoleMessage {
    enum Ark_Tag tag;
    ConsoleMessage value;
} Opt_ConsoleMessage;
typedef Ark_Materialized JsResult;
typedef struct Opt_JsResult {
    enum Ark_Tag tag;
    JsResult value;
} Opt_JsResult;
typedef Ark_Materialized JsGeolocation;
typedef struct Opt_JsGeolocation {
    enum Ark_Tag tag;
    JsGeolocation value;
} Opt_JsGeolocation;
typedef Ark_Int32 Ark_TextDeleteDirection;
typedef struct Opt_Ark_TextDeleteDirection { enum Ark_Tag tag; Ark_TextDeleteDirection value; } Opt_Ark_TextDeleteDirection;
typedef struct Array_RichEditorTextSpanResult {
    struct RichEditorTextSpanResult* array;
    Ark_Int32 length;
} Array_RichEditorTextSpanResult;
typedef struct Opt_Array_RichEditorTextSpanResult {
    enum Ark_Tag tag;
    Array_RichEditorTextSpanResult value;
} Opt_Array_RichEditorTextSpanResult;
typedef struct Array_RichEditorImageSpanResult {
    struct RichEditorImageSpanResult* array;
    Ark_Int32 length;
} Array_RichEditorImageSpanResult;
typedef struct Opt_Array_RichEditorImageSpanResult {
    enum Ark_Tag tag;
    Array_RichEditorImageSpanResult value;
} Opt_Array_RichEditorImageSpanResult;
typedef struct TextRange {
    Opt_Ark_Number start;
    Opt_Ark_Number end;
} TextRange;
typedef struct Opt_TextRange {
    enum Ark_Tag tag;
    TextRange value;
} Opt_TextRange;
typedef struct RichEditorImageSpanResult {
    struct RichEditorSpanPosition spanPosition;
    Opt_Ark_CustomObject valuePixelMap;
    struct Opt_Union_Ark_String_Ark_Resource valueResourceStr;
    struct RichEditorImageSpanStyleResult imageStyle;
    struct Tuple_Ark_Number_Ark_Number offsetInSpan;
} RichEditorImageSpanResult;
typedef struct Opt_RichEditorImageSpanResult {
    enum Ark_Tag tag;
    RichEditorImageSpanResult value;
} Opt_RichEditorImageSpanResult;
typedef struct RichEditorTextSpanResult {
    struct RichEditorSpanPosition spanPosition;
    Ark_String value;
    struct RichEditorTextStyleResult textStyle;
    struct Tuple_Ark_Number_Ark_Number offsetInSpan;
    struct Opt_RichEditorSymbolSpanStyle symbolSpanStyle;
    Opt_Ark_Resource valueResource;
    struct Opt_RichEditorParagraphStyle paragraphStyle;
    Opt_Ark_String previewText;
} RichEditorTextSpanResult;
typedef struct Opt_RichEditorTextSpanResult {
    enum Ark_Tag tag;
    RichEditorTextSpanResult value;
} Opt_RichEditorTextSpanResult;
typedef struct Array_Union_RichEditorTextSpanResult_RichEditorImageSpanResult {
    struct Union_RichEditorTextSpanResult_RichEditorImageSpanResult* array;
    Ark_Int32 length;
} Array_Union_RichEditorTextSpanResult_RichEditorImageSpanResult;
typedef struct Opt_Array_Union_RichEditorTextSpanResult_RichEditorImageSpanResult {
    enum Ark_Tag tag;
    Array_Union_RichEditorTextSpanResult_RichEditorImageSpanResult value;
} Opt_Array_Union_RichEditorTextSpanResult_RichEditorImageSpanResult;
typedef Ark_Int32 Ark_RichEditorDeleteDirection;
typedef struct Opt_Ark_RichEditorDeleteDirection { enum Ark_Tag tag; Ark_RichEditorDeleteDirection value; } Opt_Ark_RichEditorDeleteDirection;
typedef struct Object {
} Object;
typedef struct Opt_Object {
    enum Ark_Tag tag;
    Object value;
} Opt_Object;
typedef Ark_Int32 Ark_NavDestinationMode;
typedef struct Opt_Ark_NavDestinationMode { enum Ark_Tag tag; Ark_NavDestinationMode value; } Opt_Ark_NavDestinationMode;
typedef Ark_Int32 Ark_ListItemGroupArea;
typedef struct Opt_Ark_ListItemGroupArea { enum Ark_Tag tag; Ark_ListItemGroupArea value; } Opt_Ark_ListItemGroupArea;
typedef Ark_Int32 Ark_AppRotation;
typedef struct Opt_Ark_AppRotation { enum Ark_Tag tag; Ark_AppRotation value; } Opt_Ark_AppRotation;
typedef Ark_Int32 Ark_FoldStatus;
typedef struct Opt_Ark_FoldStatus { enum Ark_Tag tag; Ark_FoldStatus value; } Opt_Ark_FoldStatus;
typedef struct Array_FingerInfo {
    struct FingerInfo* array;
    Ark_Int32 length;
} Array_FingerInfo;
typedef struct Opt_Array_FingerInfo {
    enum Ark_Tag tag;
    Array_FingerInfo value;
} Opt_Array_FingerInfo;
typedef Ark_Int32 Ark_GestureControl_GestureType;
typedef struct Opt_Ark_GestureControl_GestureType { enum Ark_Tag tag; Ark_GestureControl_GestureType value; } Opt_Ark_GestureControl_GestureType;
typedef Ark_Int32 Ark_DragBehavior;
typedef struct Opt_Ark_DragBehavior { enum Ark_Tag tag; Ark_DragBehavior value; } Opt_Ark_DragBehavior;
typedef Ark_Int32 Ark_KeySource;
typedef struct Opt_Ark_KeySource { enum Ark_Tag tag; Ark_KeySource value; } Opt_Ark_KeySource;
typedef Ark_Int32 Ark_KeyType;
typedef struct Opt_Ark_KeyType { enum Ark_Tag tag; Ark_KeyType value; } Opt_Ark_KeyType;
typedef Ark_Int32 Ark_MouseAction;
typedef struct Opt_Ark_MouseAction { enum Ark_Tag tag; Ark_MouseAction value; } Opt_Ark_MouseAction;
typedef Ark_Int32 Ark_MouseButton;
typedef struct Opt_Ark_MouseButton { enum Ark_Tag tag; Ark_MouseButton value; } Opt_Ark_MouseButton;
typedef struct RectResult {
    Ark_Number x;
    Ark_Number y;
    Ark_Number width;
    Ark_Number height;
} RectResult;
typedef struct Opt_RectResult {
    enum Ark_Tag tag;
    RectResult value;
} Opt_RectResult;
typedef Ark_Int32 Ark_SelectStatus;
typedef struct Opt_Ark_SelectStatus { enum Ark_Tag tag; Ark_SelectStatus value; } Opt_Ark_SelectStatus;
typedef Ark_Int32 Ark_WebCaptureMode;
typedef struct Opt_Ark_WebCaptureMode { enum Ark_Tag tag; Ark_WebCaptureMode value; } Opt_Ark_WebCaptureMode;
typedef struct ArrayBuffer {
} ArrayBuffer;
typedef struct Opt_ArrayBuffer {
    enum Ark_Tag tag;
    ArrayBuffer value;
} Opt_ArrayBuffer;
typedef struct Array_Header {
    struct Header* array;
    Ark_Int32 length;
} Array_Header;
typedef struct Opt_Array_Header {
    enum Ark_Tag tag;
    Array_Header value;
} Opt_Array_Header;
typedef struct Union_TextStyle_DecorationStyle_BaselineOffsetStyle_LetterSpacingStyle_TextShadowStyle_GestureStyle_ImageAttachment_ParagraphStyle_LineHeightStyle_CustomSpan_UserDataSpan {
    Ark_Int32 selector;
    union {
        struct TextStyle value0;
        struct DecorationStyle value1;
        struct BaselineOffsetStyle value2;
        struct LetterSpacingStyle value3;
        struct TextShadowStyle value4;
        struct GestureStyle value5;
        struct ImageAttachment value6;
        struct ParagraphStyle value7;
        struct LineHeightStyle value8;
        CustomSpan value9;
        struct UserDataSpan value10;
    };
} Union_TextStyle_DecorationStyle_BaselineOffsetStyle_LetterSpacingStyle_TextShadowStyle_GestureStyle_ImageAttachment_ParagraphStyle_LineHeightStyle_CustomSpan_UserDataSpan;
typedef struct Opt_Union_TextStyle_DecorationStyle_BaselineOffsetStyle_LetterSpacingStyle_TextShadowStyle_GestureStyle_ImageAttachment_ParagraphStyle_LineHeightStyle_CustomSpan_UserDataSpan {
    enum Ark_Tag tag;
    Union_TextStyle_DecorationStyle_BaselineOffsetStyle_LetterSpacingStyle_TextShadowStyle_GestureStyle_ImageAttachment_ParagraphStyle_LineHeightStyle_CustomSpan_UserDataSpan value;
} Opt_Union_TextStyle_DecorationStyle_BaselineOffsetStyle_LetterSpacingStyle_TextShadowStyle_GestureStyle_ImageAttachment_ParagraphStyle_LineHeightStyle_CustomSpan_UserDataSpan;
typedef Ark_Int32 Ark_StyledStringKey;
typedef struct Opt_Ark_StyledStringKey { enum Ark_Tag tag; Ark_StyledStringKey value; } Opt_Ark_StyledStringKey;
typedef Ark_Int32 Ark_MenuPolicy;
typedef struct Opt_Ark_MenuPolicy { enum Ark_Tag tag; Ark_MenuPolicy value; } Opt_Ark_MenuPolicy;
typedef struct RichEditorUpdateSymbolSpanStyleOptions {
    Opt_Ark_Number start;
    Opt_Ark_Number end;
    struct RichEditorSymbolSpanStyle symbolStyle;
} RichEditorUpdateSymbolSpanStyleOptions;
typedef struct Opt_RichEditorUpdateSymbolSpanStyleOptions {
    enum Ark_Tag tag;
    RichEditorUpdateSymbolSpanStyleOptions value;
} Opt_RichEditorUpdateSymbolSpanStyleOptions;
typedef struct RichEditorUpdateImageSpanStyleOptions {
    Opt_Ark_Number start;
    Opt_Ark_Number end;
    struct RichEditorImageSpanStyle imageStyle;
} RichEditorUpdateImageSpanStyleOptions;
typedef struct Opt_RichEditorUpdateImageSpanStyleOptions {
    enum Ark_Tag tag;
    RichEditorUpdateImageSpanStyleOptions value;
} Opt_RichEditorUpdateImageSpanStyleOptions;
typedef struct RichEditorUpdateTextSpanStyleOptions {
    Opt_Ark_Number start;
    Opt_Ark_Number end;
    struct RichEditorTextStyle textStyle;
} RichEditorUpdateTextSpanStyleOptions;
typedef struct Opt_RichEditorUpdateTextSpanStyleOptions {
    enum Ark_Tag tag;
    RichEditorUpdateTextSpanStyleOptions value;
} Opt_RichEditorUpdateTextSpanStyleOptions;
typedef struct RichEditorGesture {
    struct Opt_Ark_Function onClick;
    struct Opt_Ark_Function onLongPress;
} RichEditorGesture;
typedef struct Opt_RichEditorGesture {
    enum Ark_Tag tag;
    RichEditorGesture value;
} Opt_RichEditorGesture;
typedef Ark_Materialized TextMenuItemId;
typedef struct Opt_TextMenuItemId {
    enum Ark_Tag tag;
    TextMenuItemId value;
} Opt_TextMenuItemId;
typedef Ark_Int32 Ark_LaunchMode;
typedef struct Opt_Ark_LaunchMode { enum Ark_Tag tag; Ark_LaunchMode value; } Opt_Ark_LaunchMode;
typedef Ark_Int32 Ark_Axis;
typedef struct Opt_Ark_Axis { enum Ark_Tag tag; Ark_Axis value; } Opt_Ark_Axis;
typedef struct Union_ScrollAnimationOptions_Ark_Boolean {
    Ark_Int32 selector;
    union {
        struct ScrollAnimationOptions value0;
        Ark_Boolean value1;
    };
} Union_ScrollAnimationOptions_Ark_Boolean;
typedef struct Opt_Union_ScrollAnimationOptions_Ark_Boolean {
    enum Ark_Tag tag;
    Union_ScrollAnimationOptions_Ark_Boolean value;
} Opt_Union_ScrollAnimationOptions_Ark_Boolean;
typedef struct Uint8ClampedArray {
} Uint8ClampedArray;
typedef struct Opt_Uint8ClampedArray {
    enum Ark_Tag tag;
    Uint8ClampedArray value;
} Opt_Uint8ClampedArray;
typedef Ark_Materialized ImageBitmap;
typedef struct Opt_ImageBitmap {
    enum Ark_Tag tag;
    ImageBitmap value;
} Opt_ImageBitmap;
typedef Ark_Int32 Ark_PanDirection;
typedef struct Opt_Ark_PanDirection { enum Ark_Tag tag; Ark_PanDirection value; } Opt_Ark_PanDirection;
typedef struct LinearIndicatorStyle {
    Opt_Ark_CustomObject space;
    Opt_Ark_CustomObject strokeWidth;
    Opt_Ark_CustomObject strokeRadius;
    Opt_Ark_CustomObject trackBackgroundColor;
    Opt_Ark_CustomObject trackColor;
} LinearIndicatorStyle;
typedef struct Opt_LinearIndicatorStyle {
    enum Ark_Tag tag;
    LinearIndicatorStyle value;
} Opt_LinearIndicatorStyle;
typedef Ark_Int32 Ark_DpiFollowStrategy;
typedef struct Opt_Ark_DpiFollowStrategy { enum Ark_Tag tag; Ark_DpiFollowStrategy value; } Opt_Ark_DpiFollowStrategy;
typedef Ark_Int32 Ark_WaterFlowLayoutMode;
typedef struct Opt_Ark_WaterFlowLayoutMode { enum Ark_Tag tag; Ark_WaterFlowLayoutMode value; } Opt_Ark_WaterFlowLayoutMode;
typedef Ark_Materialized WaterFlowSections;
typedef struct Opt_WaterFlowSections {
    enum Ark_Tag tag;
    WaterFlowSections value;
} Opt_WaterFlowSections;
typedef Ark_Materialized Scroller;
typedef struct Opt_Scroller {
    enum Ark_Tag tag;
    Scroller value;
} Opt_Scroller;
typedef struct RRect {
    Ark_Number left;
    Ark_Number top;
    Ark_Number width;
    Ark_Number height;
    Ark_Number radius;
} RRect;
typedef struct Opt_RRect {
    enum Ark_Tag tag;
    RRect value;
} Opt_RRect;
typedef struct DividerStyle {
    Ark_Length strokeWidth;
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource color;
    Opt_Ark_Length startMargin;
    Opt_Ark_Length endMargin;
} DividerStyle;
typedef struct Opt_DividerStyle {
    enum Ark_Tag tag;
    DividerStyle value;
} Opt_DividerStyle;
typedef struct Literal_shown_Union_Ark_String_Ark_CustomObject_Ark_Resource_hidden_Union_Ark_String_Ark_CustomObject_Ark_Resource_switching_Opt_Union_Ark_String_Ark_CustomObject_Ark_Resource {
    struct Union_Ark_String_Ark_CustomObject_Ark_Resource shown;
    struct Union_Ark_String_Ark_CustomObject_Ark_Resource hidden;
    struct Opt_Union_Ark_String_Ark_CustomObject_Ark_Resource switching;
} Literal_shown_Union_Ark_String_Ark_CustomObject_Ark_Resource_hidden_Union_Ark_String_Ark_CustomObject_Ark_Resource_switching_Opt_Union_Ark_String_Ark_CustomObject_Ark_Resource;
typedef struct Opt_Literal_shown_Union_Ark_String_Ark_CustomObject_Ark_Resource_hidden_Union_Ark_String_Ark_CustomObject_Ark_Resource_switching_Opt_Union_Ark_String_Ark_CustomObject_Ark_Resource {
    enum Ark_Tag tag;
    Literal_shown_Union_Ark_String_Ark_CustomObject_Ark_Resource_hidden_Union_Ark_String_Ark_CustomObject_Ark_Resource_switching_Opt_Union_Ark_String_Ark_CustomObject_Ark_Resource value;
} Opt_Literal_shown_Union_Ark_String_Ark_CustomObject_Ark_Resource_hidden_Union_Ark_String_Ark_CustomObject_Ark_Resource_switching_Opt_Union_Ark_String_Ark_CustomObject_Ark_Resource;
typedef struct ImageAIOptions {
    struct Opt_Array_Ark_ImageAnalyzerType types;
    Opt_ImageAnalyzerController aiController;
} ImageAIOptions;
typedef struct Opt_ImageAIOptions {
    enum Ark_Tag tag;
    ImageAIOptions value;
} Opt_ImageAIOptions;
typedef Ark_Materialized XComponentController;
typedef struct Opt_XComponentController {
    enum Ark_Tag tag;
    XComponentController value;
} Opt_XComponentController;
typedef Ark_Int32 Ark_XComponentType;
typedef struct Opt_Ark_XComponentType { enum Ark_Tag tag; Ark_XComponentType value; } Opt_Ark_XComponentType;
typedef struct Union_WebController_Ark_CustomObject {
    Ark_Int32 selector;
    union {
        WebController value0;
        Ark_CustomObject value1;
    };
} Union_WebController_Ark_CustomObject;
typedef struct Opt_Union_WebController_Ark_CustomObject {
    enum Ark_Tag tag;
    Union_WebController_Ark_CustomObject value;
} Opt_Union_WebController_Ark_CustomObject;
typedef Ark_Int32 Ark_RenderMode;
typedef struct Opt_Ark_RenderMode { enum Ark_Tag tag; Ark_RenderMode value; } Opt_Ark_RenderMode;
typedef Ark_Materialized VideoController;
typedef struct Opt_VideoController {
    enum Ark_Tag tag;
    VideoController value;
} Opt_VideoController;
typedef struct Union_Ark_Number_Ark_String_Ark_PlaybackSpeed {
    Ark_Int32 selector;
    union {
        Ark_Number value0;
        Ark_String value1;
        Ark_PlaybackSpeed value2;
    };
} Union_Ark_Number_Ark_String_Ark_PlaybackSpeed;
typedef struct Opt_Union_Ark_Number_Ark_String_Ark_PlaybackSpeed {
    enum Ark_Tag tag;
    Union_Ark_Number_Ark_String_Ark_PlaybackSpeed value;
} Opt_Union_Ark_Number_Ark_String_Ark_PlaybackSpeed;
typedef Ark_Int32 Ark_ToggleType;
typedef struct Opt_Ark_ToggleType { enum Ark_Tag tag; Ark_ToggleType value; } Opt_Ark_ToggleType;
typedef Ark_Int32 Ark_TimePickerFormat;
typedef struct Opt_Ark_TimePickerFormat { enum Ark_Tag tag; Ark_TimePickerFormat value; } Opt_Ark_TimePickerFormat;
typedef Ark_Materialized TextTimerController;
typedef struct Opt_TextTimerController {
    enum Ark_Tag tag;
    TextTimerController value;
} Opt_TextTimerController;
typedef struct Union_Ark_Number_Array_Ark_Number {
    Ark_Int32 selector;
    union {
        Ark_Number value0;
        struct Array_Ark_Number value1;
    };
} Union_Ark_Number_Array_Ark_Number;
typedef struct Opt_Union_Ark_Number_Array_Ark_Number {
    enum Ark_Tag tag;
    Union_Ark_Number_Array_Ark_Number value;
} Opt_Union_Ark_Number_Array_Ark_Number;
typedef struct Union_Ark_String_Array_Ark_String {
    Ark_Int32 selector;
    union {
        Ark_String value0;
        struct Array_Ark_String value1;
    };
} Union_Ark_String_Array_Ark_String;
typedef struct Opt_Union_Ark_String_Array_Ark_String {
    enum Ark_Tag tag;
    Union_Ark_String_Array_Ark_String value;
} Opt_Union_Ark_String_Array_Ark_String;
typedef struct Union_Array_Ark_String_Array_Array_Ark_String_Ark_Resource_Array_TextPickerRangeContent_Array_TextCascadePickerRangeContent {
    Ark_Int32 selector;
    union {
        struct Array_Ark_String value0;
        struct Array_Array_Ark_String value1;
        Ark_Resource value2;
        struct Array_TextPickerRangeContent value3;
        struct Array_TextCascadePickerRangeContent value4;
    };
} Union_Array_Ark_String_Array_Array_Ark_String_Ark_Resource_Array_TextPickerRangeContent_Array_TextCascadePickerRangeContent;
typedef struct Opt_Union_Array_Ark_String_Array_Array_Ark_String_Ark_Resource_Array_TextPickerRangeContent_Array_TextCascadePickerRangeContent {
    enum Ark_Tag tag;
    Union_Array_Ark_String_Array_Array_Ark_String_Ark_Resource_Array_TextPickerRangeContent_Array_TextCascadePickerRangeContent value;
} Opt_Union_Array_Ark_String_Array_Array_Ark_String_Ark_Resource_Array_TextPickerRangeContent_Array_TextCascadePickerRangeContent;
typedef struct IconOptions {
    Opt_Ark_Length size;
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource color;
    struct Opt_Union_Ark_String_Ark_Resource src;
} IconOptions;
typedef struct Opt_IconOptions {
    enum Ark_Tag tag;
    IconOptions value;
} Opt_IconOptions;
typedef Ark_Int32 Ark_CancelButtonStyle;
typedef struct Opt_Ark_CancelButtonStyle { enum Ark_Tag tag; Ark_CancelButtonStyle value; } Opt_Ark_CancelButtonStyle;
typedef struct UnderlineColor {
    struct Opt_Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Ark_Undefined typing;
    struct Opt_Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Ark_Undefined normal;
    struct Opt_Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Ark_Undefined error;
    struct Opt_Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Ark_Undefined disable;
} UnderlineColor;
typedef struct Opt_UnderlineColor {
    enum Ark_Tag tag;
    UnderlineColor value;
} Opt_UnderlineColor;
typedef Ark_Int32 Ark_TextContentStyle;
typedef struct Opt_Ark_TextContentStyle { enum Ark_Tag tag; Ark_TextContentStyle value; } Opt_Ark_TextContentStyle;
typedef Ark_Int32 Ark_TextInputStyle;
typedef struct Opt_Ark_TextInputStyle { enum Ark_Tag tag; Ark_TextInputStyle value; } Opt_Ark_TextInputStyle;
typedef Ark_Materialized TextInputController;
typedef struct Opt_TextInputController {
    enum Ark_Tag tag;
    TextInputController value;
} Opt_TextInputController;
typedef Ark_Materialized TextClockController;
typedef struct Opt_TextClockController {
    enum Ark_Tag tag;
    TextClockController value;
} Opt_TextClockController;
typedef Ark_Materialized TextAreaController;
typedef struct Opt_TextAreaController {
    enum Ark_Tag tag;
    TextAreaController value;
} Opt_TextAreaController;
typedef struct MarqueeOptions {
    Ark_Boolean start;
    Opt_Ark_Number step;
    Opt_Ark_Number loop;
    Opt_Ark_Boolean fromStart;
    Opt_Ark_Number delay;
    Opt_Ark_Boolean fadeout;
    Opt_Ark_MarqueeStartPolicy marqueeStartPolicy;
} MarqueeOptions;
typedef struct Opt_MarqueeOptions {
    enum Ark_Tag tag;
    MarqueeOptions value;
} Opt_MarqueeOptions;
typedef Ark_Materialized TextController;
typedef struct Opt_TextController {
    enum Ark_Tag tag;
    TextController value;
} Opt_TextController;
typedef struct BottomTabBarStyle {
    struct Opt_LabelStyle _labelStyle;
    struct Opt_Union_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length_Ark_Length_LocalizedPadding _padding;
    Opt_Ark_LayoutMode _layoutMode;
    Opt_Ark_VerticalAlign _verticalAlign;
    Opt_Ark_Boolean _symmetricExtensible;
    Opt_Ark_String _id;
    struct Opt_TabBarIconStyle _iconStyle;
} BottomTabBarStyle;
typedef struct Opt_BottomTabBarStyle {
    enum Ark_Tag tag;
    BottomTabBarStyle value;
} Opt_BottomTabBarStyle;
typedef struct SubTabBarStyle {
    struct Opt_IndicatorStyle _indicator;
    Opt_Ark_SelectedMode _selectedMode;
    struct Opt_BoardStyle _board;
    struct Opt_LabelStyle _labelStyle;
    struct Opt_Union_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length_Ark_Length _padding;
    Opt_Ark_String _id;
} SubTabBarStyle;
typedef struct Opt_SubTabBarStyle {
    enum Ark_Tag tag;
    SubTabBarStyle value;
} Opt_SubTabBarStyle;
typedef struct Literal_icon_Opt_Union_Ark_String_Ark_Resource_text_Opt_Union_Ark_String_Ark_Resource {
    struct Opt_Union_Ark_String_Ark_Resource icon;
    struct Opt_Union_Ark_String_Ark_Resource text;
} Literal_icon_Opt_Union_Ark_String_Ark_Resource_text_Opt_Union_Ark_String_Ark_Resource;
typedef struct Opt_Literal_icon_Opt_Union_Ark_String_Ark_Resource_text_Opt_Union_Ark_String_Ark_Resource {
    enum Ark_Tag tag;
    Literal_icon_Opt_Union_Ark_String_Ark_Resource_text_Opt_Union_Ark_String_Ark_Resource value;
} Opt_Literal_icon_Opt_Union_Ark_String_Ark_Resource_text_Opt_Union_Ark_String_Ark_Resource;
typedef Ark_Int32 Ark_EdgeEffect;
typedef struct Opt_Ark_EdgeEffect { enum Ark_Tag tag; Ark_EdgeEffect value; } Opt_Ark_EdgeEffect;
typedef Ark_Int32 Ark_AnimationMode;
typedef struct Opt_Ark_AnimationMode { enum Ark_Tag tag; Ark_AnimationMode value; } Opt_Ark_AnimationMode;
typedef Ark_Int32 Ark_LayoutStyle;
typedef struct Opt_Ark_LayoutStyle { enum Ark_Tag tag; Ark_LayoutStyle value; } Opt_Ark_LayoutStyle;
typedef Ark_Materialized TabsController;
typedef struct Opt_TabsController {
    enum Ark_Tag tag;
    TabsController value;
} Opt_TabsController;
typedef Ark_Int32 Ark_BarPosition;
typedef struct Opt_Ark_BarPosition { enum Ark_Tag tag; Ark_BarPosition value; } Opt_Ark_BarPosition;
typedef struct Literal_minSize_Union_Ark_String_Ark_Number {
    struct Union_Ark_String_Ark_Number minSize;
} Literal_minSize_Union_Ark_String_Ark_Number;
typedef struct Opt_Literal_minSize_Union_Ark_String_Ark_Number {
    enum Ark_Tag tag;
    Literal_minSize_Union_Ark_String_Ark_Number value;
} Opt_Literal_minSize_Union_Ark_String_Ark_Number;
typedef struct ArrowStyle {
    Opt_Ark_Boolean showBackground;
    Opt_Ark_Boolean isSidebarMiddle;
    Opt_Ark_Length backgroundSize;
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource backgroundColor;
    Opt_Ark_Length arrowSize;
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource arrowColor;
} ArrowStyle;
typedef struct Opt_ArrowStyle {
    enum Ark_Tag tag;
    ArrowStyle value;
} Opt_ArrowStyle;
typedef struct DigitIndicator {
    Opt_Ark_Length _left;
    Opt_Ark_Length _top;
    Opt_Ark_Length _right;
    Opt_Ark_Length _bottom;
    Opt_Ark_CustomObject _start;
    Opt_Ark_CustomObject _end;
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource _fontColor;
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource _selectedFontColor;
    struct Opt_Font _digitFont;
    struct Opt_Font _selectedDigitFont;
} DigitIndicator;
typedef struct Opt_DigitIndicator {
    enum Ark_Tag tag;
    DigitIndicator value;
} Opt_DigitIndicator;
typedef struct DotIndicator {
    Opt_Ark_Length _left;
    Opt_Ark_Length _top;
    Opt_Ark_Length _right;
    Opt_Ark_Length _bottom;
    Opt_Ark_CustomObject _start;
    Opt_Ark_CustomObject _end;
    Opt_Ark_Length _itemWidth;
    Opt_Ark_Length _itemHeight;
    Opt_Ark_Length _selectedItemWidth;
    Opt_Ark_Length _selectedItemHeight;
    Opt_Ark_Boolean _mask;
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource _color;
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource _selectedColor;
    Opt_Ark_Number _maxDisplayCount;
} DotIndicator;
typedef struct Opt_DotIndicator {
    enum Ark_Tag tag;
    DotIndicator value;
} Opt_DotIndicator;
typedef Ark_Int32 Ark_Alignment;
typedef struct Opt_Ark_Alignment { enum Ark_Tag tag; Ark_Alignment value; } Opt_Ark_Alignment;
typedef struct Union_CircleAttribute_EllipseAttribute_PathAttribute_RectAttribute {
    Ark_Int32 selector;
    union {
        struct CircleAttribute value0;
        struct EllipseAttribute value1;
        struct PathAttribute value2;
        struct RectAttribute value3;
    };
} Union_CircleAttribute_EllipseAttribute_PathAttribute_RectAttribute;
typedef struct Opt_Union_CircleAttribute_EllipseAttribute_PathAttribute_RectAttribute {
    enum Ark_Tag tag;
    Union_CircleAttribute_EllipseAttribute_PathAttribute_RectAttribute value;
} Opt_Union_CircleAttribute_EllipseAttribute_PathAttribute_RectAttribute;
typedef Ark_Int32 Ark_SliderBlockType;
typedef struct Opt_Ark_SliderBlockType { enum Ark_Tag tag; Ark_SliderBlockType value; } Opt_Ark_SliderBlockType;
typedef Ark_Int32 Ark_SliderStyle;
typedef struct Opt_Ark_SliderStyle { enum Ark_Tag tag; Ark_SliderStyle value; } Opt_Ark_SliderStyle;
typedef Ark_Int32 Ark_OptionWidthMode;
typedef struct Opt_Ark_OptionWidthMode { enum Ark_Tag tag; Ark_OptionWidthMode value; } Opt_Ark_OptionWidthMode;
typedef Ark_Materialized SearchController;
typedef struct Opt_SearchController {
    enum Ark_Tag tag;
    SearchController value;
} Opt_SearchController;
typedef Ark_Int32 Ark_BarState;
typedef struct Opt_Ark_BarState { enum Ark_Tag tag; Ark_BarState value; } Opt_Ark_BarState;
typedef Ark_Int32 Ark_ScrollBarDirection;
typedef struct Opt_Ark_ScrollBarDirection { enum Ark_Tag tag; Ark_ScrollBarDirection value; } Opt_Ark_ScrollBarDirection;
typedef struct Union_Ark_Length_Array_Ark_Length {
    Ark_Int32 selector;
    union {
        Ark_Length value0;
        struct Array_Ark_Length value1;
    };
} Union_Ark_Length_Array_Ark_Length;
typedef struct Opt_Union_Ark_Length_Array_Ark_Length {
    enum Ark_Tag tag;
    Union_Ark_Length_Array_Ark_Length value;
} Opt_Union_Ark_Length_Array_Ark_Length;
typedef Ark_Int32 Ark_ScrollSnapAlign;
typedef struct Opt_Ark_ScrollSnapAlign { enum Ark_Tag tag; Ark_ScrollSnapAlign value; } Opt_Ark_ScrollSnapAlign;
typedef Ark_Int32 Ark_ButtonType;
typedef struct Opt_Ark_ButtonType { enum Ark_Tag tag; Ark_ButtonType value; } Opt_Ark_ButtonType;
typedef Ark_Int32 Ark_SaveDescription;
typedef struct Opt_Ark_SaveDescription { enum Ark_Tag tag; Ark_SaveDescription value; } Opt_Ark_SaveDescription;
typedef Ark_Int32 Ark_SaveIconStyle;
typedef struct Opt_Ark_SaveIconStyle { enum Ark_Tag tag; Ark_SaveIconStyle value; } Opt_Ark_SaveIconStyle;
typedef int32_t Ark_TextDataDetectorType;
typedef struct Array_Ark_TextDataDetectorType {
    Ark_TextDataDetectorType* array;
    Ark_Int32 length;
} Array_Ark_TextDataDetectorType;
typedef int32_t Ark_TextDataDetectorType;
typedef struct Opt_Array_Ark_TextDataDetectorType {
    enum Ark_Tag tag;
    Array_Ark_TextDataDetectorType value;
} Opt_Array_Ark_TextDataDetectorType;
typedef Ark_Int32 Ark_RichEditorResponseType;
typedef struct Opt_Ark_RichEditorResponseType { enum Ark_Tag tag; Ark_RichEditorResponseType value; } Opt_Ark_RichEditorResponseType;
typedef Ark_Int32 Ark_ResponseType;
typedef struct Opt_Ark_ResponseType { enum Ark_Tag tag; Ark_ResponseType value; } Opt_Ark_ResponseType;
typedef Ark_Materialized RichEditorStyledStringController;
typedef struct Opt_RichEditorStyledStringController {
    enum Ark_Tag tag;
    RichEditorStyledStringController value;
} Opt_RichEditorStyledStringController;
typedef Ark_Materialized RichEditorController;
typedef struct Opt_RichEditorController {
    enum Ark_Tag tag;
    RichEditorController value;
} Opt_RichEditorController;
typedef Ark_Int32 Ark_LocalizedBarrierDirection;
typedef struct Opt_Ark_LocalizedBarrierDirection { enum Ark_Tag tag; Ark_LocalizedBarrierDirection value; } Opt_Ark_LocalizedBarrierDirection;
typedef Ark_Int32 Ark_BarrierDirection;
typedef struct Opt_Ark_BarrierDirection { enum Ark_Tag tag; Ark_BarrierDirection value; } Opt_Ark_BarrierDirection;
typedef struct GuideLinePosition {
    Opt_Ark_Length start;
    Opt_Ark_Length end;
} GuideLinePosition;
typedef struct Opt_GuideLinePosition {
    enum Ark_Tag tag;
    GuideLinePosition value;
} Opt_GuideLinePosition;
typedef struct Literal_width_Opt_Union_Ark_Number_Ark_String_height_Opt_Union_Ark_Number_Ark_String_radiusWidth_Opt_Union_Ark_Number_Ark_String_radiusHeight_Opt_Union_Ark_Number_Ark_String {
    struct Opt_Union_Ark_Number_Ark_String width;
    struct Opt_Union_Ark_Number_Ark_String height;
    struct Opt_Union_Ark_Number_Ark_String radiusWidth;
    struct Opt_Union_Ark_Number_Ark_String radiusHeight;
} Literal_width_Opt_Union_Ark_Number_Ark_String_height_Opt_Union_Ark_Number_Ark_String_radiusWidth_Opt_Union_Ark_Number_Ark_String_radiusHeight_Opt_Union_Ark_Number_Ark_String;
typedef struct Opt_Literal_width_Opt_Union_Ark_Number_Ark_String_height_Opt_Union_Ark_Number_Ark_String_radiusWidth_Opt_Union_Ark_Number_Ark_String_radiusHeight_Opt_Union_Ark_Number_Ark_String {
    enum Ark_Tag tag;
    Literal_width_Opt_Union_Ark_Number_Ark_String_height_Opt_Union_Ark_Number_Ark_String_radiusWidth_Opt_Union_Ark_Number_Ark_String_radiusHeight_Opt_Union_Ark_Number_Ark_String value;
} Opt_Literal_width_Opt_Union_Ark_Number_Ark_String_height_Opt_Union_Ark_Number_Ark_String_radiusWidth_Opt_Union_Ark_Number_Ark_String_radiusHeight_Opt_Union_Ark_Number_Ark_String;
typedef struct Literal_width_Opt_Union_Ark_Number_Ark_String_height_Opt_Union_Ark_Number_Ark_String_radius_Opt_Union_Ark_Number_Ark_String_Array_Ark_CustomObject {
    struct Opt_Union_Ark_Number_Ark_String width;
    struct Opt_Union_Ark_Number_Ark_String height;
    struct Opt_Union_Ark_Number_Ark_String_Array_Ark_CustomObject radius;
} Literal_width_Opt_Union_Ark_Number_Ark_String_height_Opt_Union_Ark_Number_Ark_String_radius_Opt_Union_Ark_Number_Ark_String_Array_Ark_CustomObject;
typedef struct Opt_Literal_width_Opt_Union_Ark_Number_Ark_String_height_Opt_Union_Ark_Number_Ark_String_radius_Opt_Union_Ark_Number_Ark_String_Array_Ark_CustomObject {
    enum Ark_Tag tag;
    Literal_width_Opt_Union_Ark_Number_Ark_String_height_Opt_Union_Ark_Number_Ark_String_radius_Opt_Union_Ark_Number_Ark_String_Array_Ark_CustomObject value;
} Opt_Literal_width_Opt_Union_Ark_Number_Ark_String_height_Opt_Union_Ark_Number_Ark_String_radius_Opt_Union_Ark_Number_Ark_String_Array_Ark_CustomObject;
typedef Ark_Int32 Ark_RadioIndicatorType;
typedef struct Opt_Ark_RadioIndicatorType { enum Ark_Tag tag; Ark_RadioIndicatorType value; } Opt_Ark_RadioIndicatorType;
typedef struct PluginComponentTemplate {
    Ark_String source;
    Ark_String bundleName;
} PluginComponentTemplate;
typedef struct Opt_PluginComponentTemplate {
    enum Ark_Tag tag;
    PluginComponentTemplate value;
} Opt_PluginComponentTemplate;
typedef struct CircleStyleOptions {
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource color;
    Opt_Ark_CustomObject radius;
    Opt_Ark_Boolean enableWaveEffect;
} CircleStyleOptions;
typedef struct Opt_CircleStyleOptions {
    enum Ark_Tag tag;
    CircleStyleOptions value;
} Opt_CircleStyleOptions;
typedef Ark_Int32 Ark_PasteDescription;
typedef struct Opt_Ark_PasteDescription { enum Ark_Tag tag; Ark_PasteDescription value; } Opt_Ark_PasteDescription;
typedef Ark_Int32 Ark_PasteIconStyle;
typedef struct Opt_Ark_PasteIconStyle { enum Ark_Tag tag; Ark_PasteIconStyle value; } Opt_Ark_PasteIconStyle;
typedef Ark_Int32 Ark_PanelHeight;
typedef struct Opt_Ark_PanelHeight { enum Ark_Tag tag; Ark_PanelHeight value; } Opt_Ark_PanelHeight;
typedef Ark_Int32 Ark_NavigationType;
typedef struct Opt_Ark_NavigationType { enum Ark_Tag tag; Ark_NavigationType value; } Opt_Ark_NavigationType;
typedef Ark_Int32 Ark_ToolbarItemStatus;
typedef struct Opt_Ark_ToolbarItemStatus { enum Ark_Tag tag; Ark_ToolbarItemStatus value; } Opt_Ark_ToolbarItemStatus;
typedef struct Array_ToolbarItem {
    struct ToolbarItem* array;
    Ark_Int32 length;
} Array_ToolbarItem;
typedef struct Opt_Array_ToolbarItem {
    enum Ark_Tag tag;
    Array_ToolbarItem value;
} Opt_Array_ToolbarItem;
typedef struct Array_NavigationMenuItem {
    struct NavigationMenuItem* array;
    Ark_Int32 length;
} Array_NavigationMenuItem;
typedef struct Opt_Array_NavigationMenuItem {
    enum Ark_Tag tag;
    Array_NavigationMenuItem value;
} Opt_Array_NavigationMenuItem;
typedef struct NavigationCustomTitle {
    struct Union_Ark_Function_Ark_Undefined builder;
    struct Union_Ark_TitleHeight_Ark_Length height;
} NavigationCustomTitle;
typedef struct Opt_NavigationCustomTitle {
    enum Ark_Tag tag;
    NavigationCustomTitle value;
} Opt_NavigationCustomTitle;
typedef struct NavigationCommonTitle {
    Ark_String main;
    Ark_String sub;
} NavigationCommonTitle;
typedef struct Opt_NavigationCommonTitle {
    enum Ark_Tag tag;
    NavigationCommonTitle value;
} Opt_NavigationCommonTitle;
typedef Ark_Int32 Ark_BarStyle;
typedef struct Opt_Ark_BarStyle { enum Ark_Tag tag; Ark_BarStyle value; } Opt_Ark_BarStyle;
typedef struct NavDestinationCustomTitle {
    struct Union_Ark_Function_Ark_Undefined builder;
    struct Union_Ark_TitleHeight_Ark_Length height;
} NavDestinationCustomTitle;
typedef struct Opt_NavDestinationCustomTitle {
    enum Ark_Tag tag;
    NavDestinationCustomTitle value;
} Opt_NavDestinationCustomTitle;
typedef struct NavDestinationCommonTitle {
    Ark_String main;
    Ark_String sub;
} NavDestinationCommonTitle;
typedef struct Opt_NavDestinationCommonTitle {
    enum Ark_Tag tag;
    NavDestinationCommonTitle value;
} Opt_NavDestinationCommonTitle;
typedef struct Union_Union_Ark_String_Ark_Resource_Union_Ark_Function_Ark_Undefined {
    Ark_Int32 selector;
    union {
        struct Union_Ark_String_Ark_Resource value0;
        struct Union_Ark_Function_Ark_Undefined value1;
    };
} Union_Union_Ark_String_Ark_Resource_Union_Ark_Function_Ark_Undefined;
typedef struct Opt_Union_Union_Ark_String_Ark_Resource_Union_Ark_Function_Ark_Undefined {
    enum Ark_Tag tag;
    Union_Union_Ark_String_Ark_Resource_Union_Ark_Function_Ark_Undefined value;
} Opt_Union_Union_Ark_String_Ark_Resource_Union_Ark_Function_Ark_Undefined;
typedef struct MenuItemOptions {
    struct Opt_Union_Ark_String_Ark_Resource startIcon;
    Opt_Ark_CustomObject symbolStartIcon;
    struct Opt_Union_Ark_String_Ark_Resource content;
    struct Opt_Union_Ark_String_Ark_Resource endIcon;
    Opt_Ark_CustomObject symbolEndIcon;
    struct Opt_Union_Ark_String_Ark_Resource labelInfo;
    struct Opt_Union_Ark_Function_Ark_Undefined builder;
} MenuItemOptions;
typedef struct Opt_MenuItemOptions {
    enum Ark_Tag tag;
    MenuItemOptions value;
} Opt_MenuItemOptions;
typedef struct DividerStyleOptions {
    Opt_Ark_CustomObject strokeWidth;
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource color;
    Opt_Ark_CustomObject startMargin;
    Opt_Ark_CustomObject endMargin;
} DividerStyleOptions;
typedef struct Opt_DividerStyleOptions {
    enum Ark_Tag tag;
    DividerStyleOptions value;
} Opt_DividerStyleOptions;
typedef struct ASTCResource {
    struct Array_Ark_String sources;
    Ark_Number column;
} ASTCResource;
typedef struct Opt_ASTCResource {
    enum Ark_Tag tag;
    ASTCResource value;
} Opt_ASTCResource;
typedef Ark_Int32 Ark_LocationDescription;
typedef struct Opt_Ark_LocationDescription { enum Ark_Tag tag; Ark_LocationDescription value; } Opt_Ark_LocationDescription;
typedef Ark_Int32 Ark_LocationIconStyle;
typedef struct Opt_Ark_LocationIconStyle { enum Ark_Tag tag; Ark_LocationIconStyle value; } Opt_Ark_LocationIconStyle;
typedef struct LocalizedEdges {
    Opt_Ark_CustomObject top;
    Opt_Ark_CustomObject start;
    Opt_Ark_CustomObject bottom;
    Opt_Ark_CustomObject end;
} LocalizedEdges;
typedef struct Opt_LocalizedEdges {
    enum Ark_Tag tag;
    LocalizedEdges value;
} Opt_LocalizedEdges;
typedef struct Edges {
    Opt_Ark_Length top;
    Opt_Ark_Length left;
    Opt_Ark_Length bottom;
    Opt_Ark_Length right;
} Edges;
typedef struct Opt_Edges {
    enum Ark_Tag tag;
    Edges value;
} Opt_Edges;
typedef struct Literal_strokeWidth_Ark_Length_color_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_startMargin_Opt_Ark_Length_endMargin_Opt_Ark_Length {
    Ark_Length strokeWidth;
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource color;
    Opt_Ark_Length startMargin;
    Opt_Ark_Length endMargin;
} Literal_strokeWidth_Ark_Length_color_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_startMargin_Opt_Ark_Length_endMargin_Opt_Ark_Length;
typedef struct Opt_Literal_strokeWidth_Ark_Length_color_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_startMargin_Opt_Ark_Length_endMargin_Opt_Ark_Length {
    enum Ark_Tag tag;
    Literal_strokeWidth_Ark_Length_color_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_startMargin_Opt_Ark_Length_endMargin_Opt_Ark_Length value;
} Opt_Literal_strokeWidth_Ark_Length_color_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_startMargin_Opt_Ark_Length_endMargin_Opt_Ark_Length;
typedef Ark_Int32 Ark_ListItemGroupStyle;
typedef struct Opt_Ark_ListItemGroupStyle { enum Ark_Tag tag; Ark_ListItemGroupStyle value; } Opt_Ark_ListItemGroupStyle;
typedef Ark_Int32 Ark_SwipeEdgeEffect;
typedef struct Opt_Ark_SwipeEdgeEffect { enum Ark_Tag tag; Ark_SwipeEdgeEffect value; } Opt_Ark_SwipeEdgeEffect;
typedef struct Union_Union_Ark_Function_Ark_Undefined_SwipeActionItem {
    Ark_Int32 selector;
    union {
        struct Union_Ark_Function_Ark_Undefined value0;
        struct SwipeActionItem value1;
    };
} Union_Union_Ark_Function_Ark_Undefined_SwipeActionItem;
typedef struct Opt_Union_Union_Ark_Function_Ark_Undefined_SwipeActionItem {
    enum Ark_Tag tag;
    Union_Union_Ark_Function_Ark_Undefined_SwipeActionItem value;
} Opt_Union_Union_Ark_Function_Ark_Undefined_SwipeActionItem;
typedef Ark_Int32 Ark_EditMode;
typedef struct Opt_Ark_EditMode { enum Ark_Tag tag; Ark_EditMode value; } Opt_Ark_EditMode;
typedef Ark_Int32 Ark_ListItemStyle;
typedef struct Opt_Ark_ListItemStyle { enum Ark_Tag tag; Ark_ListItemStyle value; } Opt_Ark_ListItemStyle;
typedef Ark_Int32 Ark_ChainEdgeEffect;
typedef struct Opt_Ark_ChainEdgeEffect { enum Ark_Tag tag; Ark_ChainEdgeEffect value; } Opt_Ark_ChainEdgeEffect;
typedef struct Literal_minLength_Ark_Length_maxLength_Ark_Length {
    Ark_Length minLength;
    Ark_Length maxLength;
} Literal_minLength_Ark_Length_maxLength_Ark_Length;
typedef struct Opt_Literal_minLength_Ark_Length_maxLength_Ark_Length {
    enum Ark_Tag tag;
    Literal_minLength_Ark_Length_maxLength_Ark_Length value;
} Opt_Literal_minLength_Ark_Length_maxLength_Ark_Length;
typedef struct ColorFilter {
} ColorFilter;
typedef struct Opt_ColorFilter {
    enum Ark_Tag tag;
    ColorFilter value;
} Opt_ColorFilter;
typedef struct Union_Ark_String_Ark_Resource_Ark_CustomObject {
    Ark_Int32 selector;
    union {
        Ark_String value0;
        Ark_Resource value1;
        Ark_CustomObject value2;
    };
} Union_Ark_String_Ark_Resource_Ark_CustomObject;
typedef struct Opt_Union_Ark_String_Ark_Resource_Ark_CustomObject {
    enum Ark_Tag tag;
    Union_Ark_String_Ark_Resource_Ark_CustomObject value;
} Opt_Union_Ark_String_Ark_Resource_Ark_CustomObject;
typedef Ark_Int32 Ark_GridRowDirection;
typedef struct Opt_Ark_GridRowDirection { enum Ark_Tag tag; Ark_GridRowDirection value; } Opt_Ark_GridRowDirection;
typedef struct BreakPoints {
    struct Opt_Array_Ark_String value;
    Opt_Ark_BreakpointsReference reference;
} BreakPoints;
typedef struct Opt_BreakPoints {
    enum Ark_Tag tag;
    BreakPoints value;
} Opt_BreakPoints;
typedef struct Union_Ark_Number_GridRowColumnOption {
    Ark_Int32 selector;
    union {
        Ark_Number value0;
        struct GridRowColumnOption value1;
    };
} Union_Ark_Number_GridRowColumnOption;
typedef struct Opt_Union_Ark_Number_GridRowColumnOption {
    enum Ark_Tag tag;
    Union_Ark_Number_GridRowColumnOption value;
} Opt_Union_Ark_Number_GridRowColumnOption;
typedef struct Union_Ark_Length_GutterOption {
    Ark_Int32 selector;
    union {
        Ark_Length value0;
        struct GutterOption value1;
    };
} Union_Ark_Length_GutterOption;
typedef struct Opt_Union_Ark_Length_GutterOption {
    enum Ark_Tag tag;
    Union_Ark_Length_GutterOption value;
} Opt_Union_Ark_Length_GutterOption;
typedef Ark_Int32 Ark_SizeType;
typedef struct Opt_Ark_SizeType { enum Ark_Tag tag; Ark_SizeType value; } Opt_Ark_SizeType;
typedef struct Union_Ark_Number_GridColColumnOption {
    Ark_Int32 selector;
    union {
        Ark_Number value0;
        struct GridColColumnOption value1;
    };
} Union_Ark_Number_GridColColumnOption;
typedef struct Opt_Union_Ark_Number_GridColColumnOption {
    enum Ark_Tag tag;
    Union_Ark_Number_GridColColumnOption value;
} Opt_Union_Ark_Number_GridColColumnOption;
typedef Ark_Int32 Ark_GridItemStyle;
typedef struct Opt_Ark_GridItemStyle { enum Ark_Tag tag; Ark_GridItemStyle value; } Opt_Ark_GridItemStyle;
typedef Ark_Int32 Ark_NestedScrollMode;
typedef struct Opt_Ark_NestedScrollMode { enum Ark_Tag tag; Ark_NestedScrollMode value; } Opt_Ark_NestedScrollMode;
typedef struct MultiShadowOptions {
    struct Opt_Union_Ark_Number_Ark_Resource radius;
    struct Opt_Union_Ark_Number_Ark_Resource offsetX;
    struct Opt_Union_Ark_Number_Ark_Resource offsetY;
} MultiShadowOptions;
typedef struct Opt_MultiShadowOptions {
    enum Ark_Tag tag;
    MultiShadowOptions value;
} Opt_MultiShadowOptions;
typedef struct Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_LinearGradient {
    Ark_Int32 selector;
    union {
        struct Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource value0;
        struct LinearGradient value1;
    };
} Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_LinearGradient;
typedef struct Opt_Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_LinearGradient {
    enum Ark_Tag tag;
    Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_LinearGradient value;
} Opt_Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_LinearGradient;
typedef struct Array_Tuple_Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_LinearGradient_Ark_Number {
    struct Tuple_Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_LinearGradient_Ark_Number* array;
    Ark_Int32 length;
} Array_Tuple_Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_LinearGradient_Ark_Number;
typedef struct Opt_Array_Tuple_Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_LinearGradient_Ark_Number {
    enum Ark_Tag tag;
    Array_Tuple_Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_LinearGradient_Ark_Number value;
} Opt_Array_Tuple_Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_LinearGradient_Ark_Number;
typedef Ark_Int32 Ark_FormShape;
typedef struct Opt_Ark_FormShape { enum Ark_Tag tag; Ark_FormShape value; } Opt_Ark_FormShape;
typedef Ark_Int32 Ark_FormRenderingMode;
typedef struct Opt_Ark_FormRenderingMode { enum Ark_Tag tag; Ark_FormRenderingMode value; } Opt_Ark_FormRenderingMode;
typedef Ark_Int32 Ark_FormDimension;
typedef struct Opt_Ark_FormDimension { enum Ark_Tag tag; Ark_FormDimension value; } Opt_Ark_FormDimension;
typedef struct FlexSpaceOptions {
    Opt_Ark_CustomObject main;
    Opt_Ark_CustomObject cross;
} FlexSpaceOptions;
typedef struct Opt_FlexSpaceOptions {
    enum Ark_Tag tag;
    FlexSpaceOptions value;
} Opt_FlexSpaceOptions;
typedef Ark_Int32 Ark_FlexAlign;
typedef struct Opt_Ark_FlexAlign { enum Ark_Tag tag; Ark_FlexAlign value; } Opt_Ark_FlexAlign;
typedef Ark_Int32 Ark_ItemAlign;
typedef struct Opt_Ark_ItemAlign { enum Ark_Tag tag; Ark_ItemAlign value; } Opt_Ark_ItemAlign;
typedef Ark_Int32 Ark_FlexWrap;
typedef struct Opt_Ark_FlexWrap { enum Ark_Tag tag; Ark_FlexWrap value; } Opt_Ark_FlexWrap;
typedef Ark_Int32 Ark_FlexDirection;
typedef struct Opt_Ark_FlexDirection { enum Ark_Tag tag; Ark_FlexDirection value; } Opt_Ark_FlexDirection;
typedef struct Array_Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_LinearGradient {
    struct Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_LinearGradient* array;
    Ark_Int32 length;
} Array_Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_LinearGradient;
typedef struct Opt_Array_Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_LinearGradient {
    enum Ark_Tag tag;
    Array_Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_LinearGradient value;
} Opt_Array_Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_LinearGradient;
typedef Ark_Int32 Ark_DataPanelType;
typedef struct Opt_Ark_DataPanelType { enum Ark_Tag tag; Ark_DataPanelType value; } Opt_Ark_DataPanelType;
typedef Ark_Int32 Ark_ModelType;
typedef struct Opt_Ark_ModelType { enum Ark_Tag tag; Ark_ModelType value; } Opt_Ark_ModelType;
typedef struct Union_Ark_Resource_Ark_CustomObject {
    Ark_Int32 selector;
    union {
        Ark_Resource value0;
        Ark_CustomObject value1;
    };
} Union_Ark_Resource_Ark_CustomObject;
typedef struct Opt_Union_Ark_Resource_Ark_CustomObject {
    enum Ark_Tag tag;
    Union_Ark_Resource_Ark_CustomObject value;
} Opt_Union_Ark_Resource_Ark_CustomObject;
typedef struct ColumnSplitDividerStyle {
    Opt_Ark_Length startMargin;
    Opt_Ark_Length endMargin;
} ColumnSplitDividerStyle;
typedef struct Opt_ColumnSplitDividerStyle {
    enum Ark_Tag tag;
    ColumnSplitDividerStyle value;
} Opt_ColumnSplitDividerStyle;
typedef Ark_Int32 Ark_IlluminatedType;
typedef struct Opt_Ark_IlluminatedType { enum Ark_Tag tag; Ark_IlluminatedType value; } Opt_Ark_IlluminatedType;
typedef struct LightSource {
    Ark_Length positionX;
    Ark_Length positionY;
    Ark_Length positionZ;
    Ark_Number intensity;
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource color;
} LightSource;
typedef struct Opt_LightSource {
    enum Ark_Tag tag;
    LightSource value;
} Opt_LightSource;
typedef Ark_Materialized DrawingRenderingContext;
typedef struct Opt_DrawingRenderingContext {
    enum Ark_Tag tag;
    DrawingRenderingContext value;
} Opt_DrawingRenderingContext;
typedef Ark_Materialized CanvasRenderingContext2D;
typedef struct Opt_CanvasRenderingContext2D {
    enum Ark_Tag tag;
    CanvasRenderingContext2D value;
} Opt_CanvasRenderingContext2D;
typedef Ark_Materialized CalendarController;
typedef struct Opt_CalendarController {
    enum Ark_Tag tag;
    CalendarController value;
} Opt_CalendarController;
typedef struct MonthData {
    Ark_Number year;
    Ark_Number month;
    struct Array_CalendarDay data;
} MonthData;
typedef struct Opt_MonthData {
    enum Ark_Tag tag;
    MonthData value;
} Opt_MonthData;
typedef struct Literal_year_Ark_Number_month_Ark_Number_day_Ark_Number {
    Ark_Number year;
    Ark_Number month;
    Ark_Number day;
} Literal_year_Ark_Number_month_Ark_Number_day_Ark_Number;
typedef struct Opt_Literal_year_Ark_Number_month_Ark_Number_day_Ark_Number {
    enum Ark_Tag tag;
    Literal_year_Ark_Number_month_Ark_Number_day_Ark_Number value;
} Opt_Literal_year_Ark_Number_month_Ark_Number_day_Ark_Number;
typedef Ark_Int32 Ark_ButtonRole;
typedef struct Opt_Ark_ButtonRole { enum Ark_Tag tag; Ark_ButtonRole value; } Opt_Ark_ButtonRole;
typedef Ark_Int32 Ark_ControlSize;
typedef struct Opt_Ark_ControlSize { enum Ark_Tag tag; Ark_ControlSize value; } Opt_Ark_ControlSize;
typedef Ark_Int32 Ark_ButtonStyleMode;
typedef struct Opt_Ark_ButtonStyleMode { enum Ark_Tag tag; Ark_ButtonStyleMode value; } Opt_Ark_ButtonStyleMode;
typedef struct BadgeParam {
    struct Opt_Union_Ark_BadgePosition_Position position;
    struct BadgeStyle style;
} BadgeParam;
typedef struct Opt_BadgeParam {
    enum Ark_Tag tag;
    BadgeParam value;
} Opt_BadgeParam;
typedef struct ScrollMotion {
} ScrollMotion;
typedef struct Opt_ScrollMotion {
    enum Ark_Tag tag;
    ScrollMotion value;
} Opt_ScrollMotion;
typedef struct FrictionMotion {
} FrictionMotion;
typedef struct Opt_FrictionMotion {
    enum Ark_Tag tag;
    FrictionMotion value;
} Opt_FrictionMotion;
typedef struct SpringMotion {
} SpringMotion;
typedef struct Opt_SpringMotion {
    enum Ark_Tag tag;
    SpringMotion value;
} Opt_SpringMotion;
typedef Ark_Int32 Ark_FunctionKey;
typedef struct Opt_Ark_FunctionKey { enum Ark_Tag tag; Ark_FunctionKey value; } Opt_Ark_FunctionKey;
typedef Ark_Int32 Ark_ScrollSizeMode;
typedef struct Opt_Ark_ScrollSizeMode { enum Ark_Tag tag; Ark_ScrollSizeMode value; } Opt_Ark_ScrollSizeMode;
typedef Ark_Int32 Ark_SheetMode;
typedef struct Opt_Ark_SheetMode { enum Ark_Tag tag; Ark_SheetMode value; } Opt_Ark_SheetMode;
typedef struct Union_Ark_BorderStyle_Literal_top_Opt_Ark_BorderStyle_right_Opt_Ark_BorderStyle_bottom_Opt_Ark_BorderStyle_left_Opt_Ark_BorderStyle {
    Ark_Int32 selector;
    union {
        Ark_BorderStyle value0;
        struct Literal_top_Opt_Ark_BorderStyle_right_Opt_Ark_BorderStyle_bottom_Opt_Ark_BorderStyle_left_Opt_Ark_BorderStyle value1;
    };
} Union_Ark_BorderStyle_Literal_top_Opt_Ark_BorderStyle_right_Opt_Ark_BorderStyle_bottom_Opt_Ark_BorderStyle_left_Opt_Ark_BorderStyle;
typedef struct Opt_Union_Ark_BorderStyle_Literal_top_Opt_Ark_BorderStyle_right_Opt_Ark_BorderStyle_bottom_Opt_Ark_BorderStyle_left_Opt_Ark_BorderStyle {
    enum Ark_Tag tag;
    Union_Ark_BorderStyle_Literal_top_Opt_Ark_BorderStyle_right_Opt_Ark_BorderStyle_bottom_Opt_Ark_BorderStyle_left_Opt_Ark_BorderStyle value;
} Opt_Union_Ark_BorderStyle_Literal_top_Opt_Ark_BorderStyle_right_Opt_Ark_BorderStyle_bottom_Opt_Ark_BorderStyle_left_Opt_Ark_BorderStyle;
typedef struct Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Literal_top_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_right_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_bottom_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_left_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_LocalizedEdgeColors {
    Ark_Int32 selector;
    union {
        struct Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource value0;
        struct Literal_top_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_right_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_bottom_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_left_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource value1;
        struct LocalizedEdgeColors value2;
    };
} Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Literal_top_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_right_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_bottom_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_left_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_LocalizedEdgeColors;
typedef struct Opt_Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Literal_top_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_right_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_bottom_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_left_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_LocalizedEdgeColors {
    enum Ark_Tag tag;
    Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Literal_top_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_right_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_bottom_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_left_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_LocalizedEdgeColors value;
} Opt_Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Literal_top_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_right_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_bottom_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_left_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_LocalizedEdgeColors;
typedef struct Union_Ark_Length_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length_LocalizedEdgeWidths {
    Ark_Int32 selector;
    union {
        Ark_Length value0;
        struct Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length value1;
        struct LocalizedEdgeWidths value2;
    };
} Union_Ark_Length_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length_LocalizedEdgeWidths;
typedef struct Opt_Union_Ark_Length_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length_LocalizedEdgeWidths {
    enum Ark_Tag tag;
    Union_Ark_Length_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length_LocalizedEdgeWidths value;
} Opt_Union_Ark_Length_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length_LocalizedEdgeWidths;
typedef struct Union_SheetTitleOptions_Union_Ark_Function_Ark_Undefined {
    Ark_Int32 selector;
    union {
        struct SheetTitleOptions value0;
        struct Union_Ark_Function_Ark_Undefined value1;
    };
} Union_SheetTitleOptions_Union_Ark_Function_Ark_Undefined;
typedef struct Opt_Union_SheetTitleOptions_Union_Ark_Function_Ark_Undefined {
    enum Ark_Tag tag;
    Union_SheetTitleOptions_Union_Ark_Function_Ark_Undefined value;
} Opt_Union_SheetTitleOptions_Union_Ark_Function_Ark_Undefined;
typedef Ark_Int32 Ark_SheetType;
typedef struct Opt_Ark_SheetType { enum Ark_Tag tag; Ark_SheetType value; } Opt_Ark_SheetType;
typedef struct Union_Ark_Boolean_Ark_Resource {
    Ark_Int32 selector;
    union {
        Ark_Boolean value0;
        Ark_Resource value1;
    };
} Union_Ark_Boolean_Ark_Resource;
typedef struct Opt_Union_Ark_Boolean_Ark_Resource {
    enum Ark_Tag tag;
    Union_Ark_Boolean_Ark_Resource value;
} Opt_Union_Ark_Boolean_Ark_Resource;
typedef struct Tuple_Union_Ark_SheetSize_Ark_Length_Opt_Union_Ark_SheetSize_Ark_Length_Opt_Union_Ark_SheetSize_Ark_Length {
    struct Union_Ark_SheetSize_Ark_Length value0;
    struct Opt_Union_Ark_SheetSize_Ark_Length value1;
    struct Opt_Union_Ark_SheetSize_Ark_Length value2;
} Tuple_Union_Ark_SheetSize_Ark_Length_Opt_Union_Ark_SheetSize_Ark_Length_Opt_Union_Ark_SheetSize_Ark_Length;
typedef struct Opt_Tuple_Union_Ark_SheetSize_Ark_Length_Opt_Union_Ark_SheetSize_Ark_Length_Opt_Union_Ark_SheetSize_Ark_Length {
    enum Ark_Tag tag;
    Tuple_Union_Ark_SheetSize_Ark_Length_Opt_Union_Ark_SheetSize_Ark_Length_Opt_Union_Ark_SheetSize_Ark_Length value;
} Opt_Tuple_Union_Ark_SheetSize_Ark_Length_Opt_Union_Ark_SheetSize_Ark_Length_Opt_Union_Ark_SheetSize_Ark_Length;
typedef struct BindOptions {
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource backgroundColor;
    struct Opt_Ark_Function onAppear;
    struct Opt_Ark_Function onDisappear;
    struct Opt_Ark_Function onWillAppear;
    struct Opt_Ark_Function onWillDisappear;
} BindOptions;
typedef struct Opt_BindOptions {
    enum Ark_Tag tag;
    BindOptions value;
} Opt_BindOptions;
typedef Ark_Int32 Ark_ModalTransition;
typedef struct Opt_Ark_ModalTransition { enum Ark_Tag tag; Ark_ModalTransition value; } Opt_Ark_ModalTransition;
typedef struct Array_MenuElement {
    struct MenuElement* array;
    Ark_Int32 length;
} Array_MenuElement;
typedef struct Opt_Array_MenuElement {
    enum Ark_Tag tag;
    Array_MenuElement value;
} Opt_Array_MenuElement;
typedef struct ContextMenuOptions {
    struct Opt_Position offset;
    Opt_Ark_Placement placement;
    Opt_Ark_Boolean enableArrow;
    Opt_Ark_Length arrowOffset;
    struct Opt_Union_Ark_MenuPreviewMode_Union_Ark_Function_Ark_Undefined preview;
    struct Opt_Union_Ark_Length_Literal_topLeft_Opt_Ark_Length_topRight_Opt_Ark_Length_bottomLeft_Opt_Ark_Length_bottomRight_Opt_Ark_Length borderRadius;
    struct Opt_Ark_Function onAppear;
    struct Opt_Ark_Function onDisappear;
    struct Opt_Ark_Function aboutToAppear;
    struct Opt_Ark_Function aboutToDisappear;
    struct Opt_ContextMenuAnimationOptions previewAnimationOptions;
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource backgroundColor;
    Opt_Ark_BlurStyle backgroundBlurStyle;
    struct Opt_TransitionEffect transition;
} ContextMenuOptions;
typedef struct Opt_ContextMenuOptions {
    enum Ark_Tag tag;
    ContextMenuOptions value;
} Opt_ContextMenuOptions;
typedef struct CustomPopupOptions {
    struct Union_Ark_Function_Ark_Undefined builder;
    Opt_Ark_Placement placement;
    struct Opt_Union_Ark_Color_Ark_String_Ark_Resource_Ark_Number maskColor;
    struct Opt_Union_Ark_Color_Ark_String_Ark_Resource_Ark_Number popupColor;
    Opt_Ark_Boolean enableArrow;
    Opt_Ark_Boolean autoCancel;
    struct Opt_Ark_Function onStateChange;
    Opt_Ark_Length arrowOffset;
    Opt_Ark_Boolean showInSubWindow;
    struct Opt_Union_Ark_Boolean_Literal_color_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource mask;
    Opt_Ark_Length targetSpace;
    struct Opt_Position offset;
    Opt_Ark_Length width;
    Opt_Ark_ArrowPointPosition arrowPointPosition;
    Opt_Ark_Length arrowWidth;
    Opt_Ark_Length arrowHeight;
    Opt_Ark_Length radius;
    struct Opt_Union_ShadowOptions_Ark_ShadowStyle shadow;
    Opt_Ark_BlurStyle backgroundBlurStyle;
    Opt_Ark_Boolean focusable;
    struct Opt_TransitionEffect transition;
    struct Opt_Union_Ark_Boolean_Ark_Function onWillDismiss;
} CustomPopupOptions;
typedef struct Opt_CustomPopupOptions {
    enum Ark_Tag tag;
    CustomPopupOptions value;
} Opt_CustomPopupOptions;
typedef struct PopupOptions {
    Ark_String message;
    Opt_Ark_Boolean placementOnTop;
    Opt_Ark_Placement placement;
    struct Opt_Literal_value_Ark_String_action_Ark_Function primaryButton;
    struct Opt_Literal_value_Ark_String_action_Ark_Function secondaryButton;
    struct Opt_Ark_Function onStateChange;
    Opt_Ark_Length arrowOffset;
    Opt_Ark_Boolean showInSubWindow;
    struct Opt_Union_Ark_Boolean_Literal_color_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource mask;
    struct Opt_PopupMessageOptions messageOptions;
    Opt_Ark_Length targetSpace;
    Opt_Ark_Boolean enableArrow;
    struct Opt_Position offset;
    struct Opt_Union_Ark_Color_Ark_String_Ark_Resource_Ark_Number popupColor;
    Opt_Ark_Boolean autoCancel;
    Opt_Ark_Length width;
    Opt_Ark_ArrowPointPosition arrowPointPosition;
    Opt_Ark_Length arrowWidth;
    Opt_Ark_Length arrowHeight;
    Opt_Ark_Length radius;
    struct Opt_Union_ShadowOptions_Ark_ShadowStyle shadow;
    Opt_Ark_BlurStyle backgroundBlurStyle;
    struct Opt_TransitionEffect transition;
    struct Opt_Union_Ark_Boolean_Ark_Function onWillDismiss;
} PopupOptions;
typedef struct Opt_PopupOptions {
    enum Ark_Tag tag;
    PopupOptions value;
} Opt_PopupOptions;
typedef Ark_Int32 Ark_TransitionHierarchyStrategy;
typedef struct Opt_Ark_TransitionHierarchyStrategy { enum Ark_Tag tag; Ark_TransitionHierarchyStrategy value; } Opt_Ark_TransitionHierarchyStrategy;
typedef Ark_Materialized ProgressMask;
typedef struct Opt_ProgressMask {
    enum Ark_Tag tag;
    ProgressMask value;
} Opt_ProgressMask;
typedef struct OverlayOffset {
    Opt_Ark_Number x;
    Opt_Ark_Number y;
} OverlayOffset;
typedef struct Opt_OverlayOffset {
    enum Ark_Tag tag;
    OverlayOffset value;
} Opt_OverlayOffset;
typedef struct Union_Ark_Boolean_Ark_Number {
    Ark_Int32 selector;
    union {
        Ark_Boolean value0;
        Ark_Number value1;
    };
} Union_Ark_Boolean_Ark_Number;
typedef struct Opt_Union_Ark_Boolean_Ark_Number {
    enum Ark_Tag tag;
    Union_Ark_Boolean_Ark_Number value;
} Opt_Union_Ark_Boolean_Ark_Number;
typedef struct Union_Ark_DragPreviewMode_Array_Ark_DragPreviewMode {
    Ark_Int32 selector;
    union {
        Ark_DragPreviewMode value0;
        struct Array_Ark_DragPreviewMode value1;
    };
} Union_Ark_DragPreviewMode_Array_Ark_DragPreviewMode;
typedef struct Opt_Union_Ark_DragPreviewMode_Array_Ark_DragPreviewMode {
    enum Ark_Tag tag;
    Union_Ark_DragPreviewMode_Array_Ark_DragPreviewMode value;
} Opt_Union_Ark_DragPreviewMode_Array_Ark_DragPreviewMode;
typedef struct DragItemInfo {
    Opt_Ark_CustomObject pixelMap;
    struct Opt_Union_Ark_Function_Ark_Undefined builder;
    Opt_Ark_String extraInfo;
} DragItemInfo;
typedef struct Opt_DragItemInfo {
    enum Ark_Tag tag;
    DragItemInfo value;
} Opt_DragItemInfo;
typedef struct ClickEffect {
    Ark_ClickEffectLevel level;
    Opt_Ark_Number scale;
} ClickEffect;
typedef struct Opt_ClickEffect {
    enum Ark_Tag tag;
    ClickEffect value;
} Opt_ClickEffect;
typedef struct Bias {
    Opt_Ark_Number horizontal;
    Opt_Ark_Number vertical;
} Bias;
typedef struct Opt_Bias {
    enum Ark_Tag tag;
    Bias value;
} Opt_Bias;
typedef struct LocalizedVerticalAlignParam {
    Ark_String anchor;
    Ark_VerticalAlign align;
} LocalizedVerticalAlignParam;
typedef struct Opt_LocalizedVerticalAlignParam {
    enum Ark_Tag tag;
    LocalizedVerticalAlignParam value;
} Opt_LocalizedVerticalAlignParam;
typedef struct LocalizedHorizontalAlignParam {
    Ark_String anchor;
    Ark_HorizontalAlign align;
} LocalizedHorizontalAlignParam;
typedef struct Opt_LocalizedHorizontalAlignParam {
    enum Ark_Tag tag;
    LocalizedHorizontalAlignParam value;
} Opt_LocalizedHorizontalAlignParam;
typedef struct Literal_anchor_Ark_String_align_Ark_VerticalAlign {
    Ark_String anchor;
    Ark_VerticalAlign align;
} Literal_anchor_Ark_String_align_Ark_VerticalAlign;
typedef struct Opt_Literal_anchor_Ark_String_align_Ark_VerticalAlign {
    enum Ark_Tag tag;
    Literal_anchor_Ark_String_align_Ark_VerticalAlign value;
} Opt_Literal_anchor_Ark_String_align_Ark_VerticalAlign;
typedef struct Literal_anchor_Ark_String_align_Ark_HorizontalAlign {
    Ark_String anchor;
    Ark_HorizontalAlign align;
} Literal_anchor_Ark_String_align_Ark_HorizontalAlign;
typedef struct Opt_Literal_anchor_Ark_String_align_Ark_HorizontalAlign {
    enum Ark_Tag tag;
    Literal_anchor_Ark_String_align_Ark_HorizontalAlign value;
} Opt_Literal_anchor_Ark_String_align_Ark_HorizontalAlign;
typedef struct Union_Ark_Number_Literal_span_Ark_Number_offset_Ark_Number {
    Ark_Int32 selector;
    union {
        Ark_Number value0;
        struct Literal_span_Ark_Number_offset_Ark_Number value1;
    };
} Union_Ark_Number_Literal_span_Ark_Number_offset_Ark_Number;
typedef struct Opt_Union_Ark_Number_Literal_span_Ark_Number_offset_Ark_Number {
    enum Ark_Tag tag;
    Union_Ark_Number_Literal_span_Ark_Number_offset_Ark_Number value;
} Opt_Union_Ark_Number_Literal_span_Ark_Number_offset_Ark_Number;
typedef struct LocalizedPosition {
    Opt_Ark_CustomObject start;
    Opt_Ark_CustomObject top;
} LocalizedPosition;
typedef struct Opt_LocalizedPosition {
    enum Ark_Tag tag;
    LocalizedPosition value;
} Opt_LocalizedPosition;
typedef Ark_Int32 Ark_SharedTransitionEffectType;
typedef struct Opt_Ark_SharedTransitionEffectType { enum Ark_Tag tag; Ark_SharedTransitionEffectType value; } Opt_Ark_SharedTransitionEffectType;
typedef struct MotionPathOptions {
    Ark_String path;
    Opt_Ark_Number from;
    Opt_Ark_Number to;
    Opt_Ark_Boolean rotatable;
} MotionPathOptions;
typedef struct Opt_MotionPathOptions {
    enum Ark_Tag tag;
    MotionPathOptions value;
} Opt_MotionPathOptions;
typedef struct Union_Ark_Curve_Ark_String_ICurve {
    Ark_Int32 selector;
    union {
        Ark_Curve value0;
        Ark_String value1;
        struct ICurve value2;
    };
} Union_Ark_Curve_Ark_String_ICurve;
typedef struct Opt_Union_Ark_Curve_Ark_String_ICurve {
    enum Ark_Tag tag;
    Union_Ark_Curve_Ark_String_ICurve value;
} Opt_Union_Ark_Curve_Ark_String_ICurve;
typedef struct InvertOptions {
    Ark_Number low;
    Ark_Number high;
    Ark_Number threshold;
    Ark_Number thresholdRange;
} InvertOptions;
typedef struct Opt_InvertOptions {
    enum Ark_Tag tag;
    InvertOptions value;
} Opt_InvertOptions;
typedef struct MotionBlurAnchor {
    Ark_Number x;
    Ark_Number y;
} MotionBlurAnchor;
typedef struct Opt_MotionBlurAnchor {
    enum Ark_Tag tag;
    MotionBlurAnchor value;
} Opt_MotionBlurAnchor;
typedef struct Array_Tuple_Ark_Number_Ark_Number {
    struct Tuple_Ark_Number_Ark_Number* array;
    Ark_Int32 length;
} Array_Tuple_Ark_Number_Ark_Number;
typedef struct Opt_Array_Tuple_Ark_Number_Ark_Number {
    enum Ark_Tag tag;
    Array_Tuple_Ark_Number_Ark_Number value;
} Opt_Array_Tuple_Ark_Number_Ark_Number;
typedef struct GestureGroupInterface {
} GestureGroupInterface;
typedef struct Opt_GestureGroupInterface {
    enum Ark_Tag tag;
    GestureGroupInterface value;
} Opt_GestureGroupInterface;
typedef struct RotationGestureInterface {
} RotationGestureInterface;
typedef struct Opt_RotationGestureInterface {
    enum Ark_Tag tag;
    RotationGestureInterface value;
} Opt_RotationGestureInterface;
typedef struct SwipeGestureInterface {
} SwipeGestureInterface;
typedef struct Opt_SwipeGestureInterface {
    enum Ark_Tag tag;
    SwipeGestureInterface value;
} Opt_SwipeGestureInterface;
typedef struct PinchGestureInterface {
} PinchGestureInterface;
typedef struct Opt_PinchGestureInterface {
    enum Ark_Tag tag;
    PinchGestureInterface value;
} Opt_PinchGestureInterface;
typedef struct PanGestureInterface {
} PanGestureInterface;
typedef struct Opt_PanGestureInterface {
    enum Ark_Tag tag;
    PanGestureInterface value;
} Opt_PanGestureInterface;
typedef struct LongPressGestureInterface {
} LongPressGestureInterface;
typedef struct Opt_LongPressGestureInterface {
    enum Ark_Tag tag;
    LongPressGestureInterface value;
} Opt_LongPressGestureInterface;
typedef struct TapGestureInterface {
} TapGestureInterface;
typedef struct Opt_TapGestureInterface {
    enum Ark_Tag tag;
    TapGestureInterface value;
} Opt_TapGestureInterface;
typedef struct TransitionOptions {
    Opt_Ark_TransitionType type;
    Opt_Ark_Number opacity;
    struct Opt_TranslateOptions translate;
    struct Opt_ScaleOptions scale;
    struct Opt_RotateOptions rotate;
} TransitionOptions;
typedef struct Opt_TransitionOptions {
    enum Ark_Tag tag;
    TransitionOptions value;
} Opt_TransitionOptions;
typedef struct ExpectedFrameRateRange {
    Ark_Number min;
    Ark_Number max;
    Ark_Number expected;
} ExpectedFrameRateRange;
typedef struct Opt_ExpectedFrameRateRange {
    enum Ark_Tag tag;
    ExpectedFrameRateRange value;
} Opt_ExpectedFrameRateRange;
typedef Ark_Int32 Ark_FinishCallbackType;
typedef struct Opt_Ark_FinishCallbackType { enum Ark_Tag tag; Ark_FinishCallbackType value; } Opt_Ark_FinishCallbackType;
typedef Ark_Int32 Ark_PlayMode;
typedef struct Opt_Ark_PlayMode { enum Ark_Tag tag; Ark_PlayMode value; } Opt_Ark_PlayMode;
typedef struct Union_Literal_top_Opt_Ark_OutlineStyle_right_Opt_Ark_OutlineStyle_bottom_Opt_Ark_OutlineStyle_left_Opt_Ark_OutlineStyle_Ark_OutlineStyle {
    Ark_Int32 selector;
    union {
        struct Literal_top_Opt_Ark_OutlineStyle_right_Opt_Ark_OutlineStyle_bottom_Opt_Ark_OutlineStyle_left_Opt_Ark_OutlineStyle value0;
        Ark_OutlineStyle value1;
    };
} Union_Literal_top_Opt_Ark_OutlineStyle_right_Opt_Ark_OutlineStyle_bottom_Opt_Ark_OutlineStyle_left_Opt_Ark_OutlineStyle_Ark_OutlineStyle;
typedef struct Opt_Union_Literal_top_Opt_Ark_OutlineStyle_right_Opt_Ark_OutlineStyle_bottom_Opt_Ark_OutlineStyle_left_Opt_Ark_OutlineStyle_Ark_OutlineStyle {
    enum Ark_Tag tag;
    Union_Literal_top_Opt_Ark_OutlineStyle_right_Opt_Ark_OutlineStyle_bottom_Opt_Ark_OutlineStyle_left_Opt_Ark_OutlineStyle_Ark_OutlineStyle value;
} Opt_Union_Literal_top_Opt_Ark_OutlineStyle_right_Opt_Ark_OutlineStyle_bottom_Opt_Ark_OutlineStyle_left_Opt_Ark_OutlineStyle_Ark_OutlineStyle;
typedef struct Union_Literal_topLeft_Opt_Ark_Length_topRight_Opt_Ark_Length_bottomLeft_Opt_Ark_Length_bottomRight_Opt_Ark_Length_Ark_Length {
    Ark_Int32 selector;
    union {
        struct Literal_topLeft_Opt_Ark_Length_topRight_Opt_Ark_Length_bottomLeft_Opt_Ark_Length_bottomRight_Opt_Ark_Length value0;
        Ark_Length value1;
    };
} Union_Literal_topLeft_Opt_Ark_Length_topRight_Opt_Ark_Length_bottomLeft_Opt_Ark_Length_bottomRight_Opt_Ark_Length_Ark_Length;
typedef struct Opt_Union_Literal_topLeft_Opt_Ark_Length_topRight_Opt_Ark_Length_bottomLeft_Opt_Ark_Length_bottomRight_Opt_Ark_Length_Ark_Length {
    enum Ark_Tag tag;
    Union_Literal_topLeft_Opt_Ark_Length_topRight_Opt_Ark_Length_bottomLeft_Opt_Ark_Length_bottomRight_Opt_Ark_Length_Ark_Length value;
} Opt_Union_Literal_topLeft_Opt_Ark_Length_topRight_Opt_Ark_Length_bottomLeft_Opt_Ark_Length_bottomRight_Opt_Ark_Length_Ark_Length;
typedef struct Union_Literal_top_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_right_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_bottom_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_left_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_LocalizedEdgeColors {
    Ark_Int32 selector;
    union {
        struct Literal_top_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_right_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_bottom_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_left_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource value0;
        struct Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource value1;
        struct LocalizedEdgeColors value2;
    };
} Union_Literal_top_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_right_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_bottom_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_left_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_LocalizedEdgeColors;
typedef struct Opt_Union_Literal_top_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_right_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_bottom_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_left_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_LocalizedEdgeColors {
    enum Ark_Tag tag;
    Union_Literal_top_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_right_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_bottom_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_left_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_LocalizedEdgeColors value;
} Opt_Union_Literal_top_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_right_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_bottom_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_left_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_LocalizedEdgeColors;
typedef struct Union_Ark_String_Ark_Resource_LinearGradient {
    Ark_Int32 selector;
    union {
        Ark_String value0;
        Ark_Resource value1;
        struct LinearGradient value2;
    };
} Union_Ark_String_Ark_Resource_LinearGradient;
typedef struct Opt_Union_Ark_String_Ark_Resource_LinearGradient {
    enum Ark_Tag tag;
    Union_Ark_String_Ark_Resource_LinearGradient value;
} Opt_Union_Ark_String_Ark_Resource_LinearGradient;
typedef Ark_Int32 Ark_RepeatMode;
typedef struct Opt_Ark_RepeatMode { enum Ark_Tag tag; Ark_RepeatMode value; } Opt_Ark_RepeatMode;
typedef struct Union_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length_Ark_CustomObject_LocalizedEdgeWidths {
    Ark_Int32 selector;
    union {
        struct Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length value0;
        Ark_CustomObject value1;
        struct LocalizedEdgeWidths value2;
    };
} Union_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length_Ark_CustomObject_LocalizedEdgeWidths;
typedef struct Opt_Union_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length_Ark_CustomObject_LocalizedEdgeWidths {
    enum Ark_Tag tag;
    Union_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length_Ark_CustomObject_LocalizedEdgeWidths value;
} Opt_Union_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length_Ark_CustomObject_LocalizedEdgeWidths;
typedef struct Union_Literal_top_Opt_Ark_BorderStyle_right_Opt_Ark_BorderStyle_bottom_Opt_Ark_BorderStyle_left_Opt_Ark_BorderStyle_Ark_BorderStyle {
    Ark_Int32 selector;
    union {
        struct Literal_top_Opt_Ark_BorderStyle_right_Opt_Ark_BorderStyle_bottom_Opt_Ark_BorderStyle_left_Opt_Ark_BorderStyle value0;
        Ark_BorderStyle value1;
    };
} Union_Literal_top_Opt_Ark_BorderStyle_right_Opt_Ark_BorderStyle_bottom_Opt_Ark_BorderStyle_left_Opt_Ark_BorderStyle_Ark_BorderStyle;
typedef struct Opt_Union_Literal_top_Opt_Ark_BorderStyle_right_Opt_Ark_BorderStyle_bottom_Opt_Ark_BorderStyle_left_Opt_Ark_BorderStyle_Ark_BorderStyle {
    enum Ark_Tag tag;
    Union_Literal_top_Opt_Ark_BorderStyle_right_Opt_Ark_BorderStyle_bottom_Opt_Ark_BorderStyle_left_Opt_Ark_BorderStyle_Ark_BorderStyle value;
} Opt_Union_Literal_top_Opt_Ark_BorderStyle_right_Opt_Ark_BorderStyle_bottom_Opt_Ark_BorderStyle_left_Opt_Ark_BorderStyle_Ark_BorderStyle;
typedef struct Union_Literal_topLeft_Opt_Ark_Length_topRight_Opt_Ark_Length_bottomLeft_Opt_Ark_Length_bottomRight_Opt_Ark_Length_Ark_Length_LocalizedBorderRadiuses {
    Ark_Int32 selector;
    union {
        struct Literal_topLeft_Opt_Ark_Length_topRight_Opt_Ark_Length_bottomLeft_Opt_Ark_Length_bottomRight_Opt_Ark_Length value0;
        Ark_Length value1;
        struct LocalizedBorderRadiuses value2;
    };
} Union_Literal_topLeft_Opt_Ark_Length_topRight_Opt_Ark_Length_bottomLeft_Opt_Ark_Length_bottomRight_Opt_Ark_Length_Ark_Length_LocalizedBorderRadiuses;
typedef struct Opt_Union_Literal_topLeft_Opt_Ark_Length_topRight_Opt_Ark_Length_bottomLeft_Opt_Ark_Length_bottomRight_Opt_Ark_Length_Ark_Length_LocalizedBorderRadiuses {
    enum Ark_Tag tag;
    Union_Literal_topLeft_Opt_Ark_Length_topRight_Opt_Ark_Length_bottomLeft_Opt_Ark_Length_bottomRight_Opt_Ark_Length_Ark_Length_LocalizedBorderRadiuses value;
} Opt_Union_Literal_topLeft_Opt_Ark_Length_topRight_Opt_Ark_Length_bottomLeft_Opt_Ark_Length_bottomRight_Opt_Ark_Length_Ark_Length_LocalizedBorderRadiuses;
typedef struct Union_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length_Ark_Length_LocalizedEdgeWidths {
    Ark_Int32 selector;
    union {
        struct Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length value0;
        Ark_Length value1;
        struct LocalizedEdgeWidths value2;
    };
} Union_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length_Ark_Length_LocalizedEdgeWidths;
typedef struct Opt_Union_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length_Ark_Length_LocalizedEdgeWidths {
    enum Ark_Tag tag;
    Union_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length_Ark_Length_LocalizedEdgeWidths value;
} Opt_Union_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length_Ark_Length_LocalizedEdgeWidths;
typedef struct BlurStyleOptions {
    Opt_Ark_ThemeColorMode colorMode;
    Opt_Ark_AdaptiveColor adaptiveColor;
    Opt_Ark_Number scale;
    struct Opt_BlurOptions blurOptions;
} BlurStyleOptions;
typedef struct Opt_BlurStyleOptions {
    enum Ark_Tag tag;
    BlurStyleOptions value;
} Opt_BlurStyleOptions;
typedef Ark_Int32 Ark_BlurType;
typedef struct Opt_Ark_BlurType { enum Ark_Tag tag; Ark_BlurType value; } Opt_Ark_BlurType;
typedef Ark_Int32 Ark_BlurStyleActivePolicy;
typedef struct Opt_Ark_BlurStyleActivePolicy { enum Ark_Tag tag; Ark_BlurStyleActivePolicy value; } Opt_Ark_BlurStyleActivePolicy;
typedef Ark_Int32 Ark_ImageSize;
typedef struct Opt_Ark_ImageSize { enum Ark_Tag tag; Ark_ImageSize value; } Opt_Ark_ImageSize;
typedef Ark_Int32 Ark_PixelRoundCalcPolicy;
typedef struct Opt_Ark_PixelRoundCalcPolicy { enum Ark_Tag tag; Ark_PixelRoundCalcPolicy value; } Opt_Ark_PixelRoundCalcPolicy;
typedef struct Rectangle {
    Opt_Ark_Length x;
    Opt_Ark_Length y;
    Opt_Ark_Length width;
    Opt_Ark_Length height;
} Rectangle;
typedef struct Opt_Rectangle {
    enum Ark_Tag tag;
    Rectangle value;
} Opt_Rectangle;
typedef struct Array_Rectangle {
    struct Rectangle* array;
    Ark_Int32 length;
} Array_Rectangle;
typedef struct Opt_Array_Rectangle {
    enum Ark_Tag tag;
    Array_Rectangle value;
} Opt_Array_Rectangle;
typedef Ark_Materialized DrawModifier;
typedef struct Opt_DrawModifier {
    enum Ark_Tag tag;
    DrawModifier value;
} Opt_DrawModifier;
typedef struct TerminationInfo {
    Ark_Number code;
    Opt_Ark_CustomObject want;
} TerminationInfo;
typedef struct Opt_TerminationInfo {
    enum Ark_Tag tag;
    TerminationInfo value;
} Opt_TerminationInfo;
typedef struct AdsBlockedDetails {
    Ark_String url;
    struct Array_Ark_String adsBlocked;
} AdsBlockedDetails;
typedef struct Opt_AdsBlockedDetails {
    enum Ark_Tag tag;
    AdsBlockedDetails value;
} Opt_AdsBlockedDetails;
typedef struct WebKeyboardCallbackInfo {
    WebKeyboardController controller;
    struct Ark_CustomObject attributes;
} WebKeyboardCallbackInfo;
typedef struct Opt_WebKeyboardCallbackInfo {
    enum Ark_Tag tag;
    WebKeyboardCallbackInfo value;
} Opt_WebKeyboardCallbackInfo;
typedef Ark_Int32 Ark_ViewportFit;
typedef struct Opt_Ark_ViewportFit { enum Ark_Tag tag; Ark_ViewportFit value; } Opt_Ark_ViewportFit;
typedef struct RenderProcessNotRespondingData {
    Ark_String jsStack;
    Ark_Number pid;
    Ark_RenderProcessNotRespondingReason reason;
} RenderProcessNotRespondingData;
typedef struct Opt_RenderProcessNotRespondingData {
    enum Ark_Tag tag;
    RenderProcessNotRespondingData value;
} Opt_RenderProcessNotRespondingData;
typedef struct NativeEmbedTouchInfo {
    Opt_Ark_String embedId;
    struct Opt_TouchEvent touchEvent;
    Opt_EventResult result;
} NativeEmbedTouchInfo;
typedef struct Opt_NativeEmbedTouchInfo {
    enum Ark_Tag tag;
    NativeEmbedTouchInfo value;
} Opt_NativeEmbedTouchInfo;
typedef struct NativeEmbedDataInfo {
    Opt_Ark_NativeEmbedStatus status;
    Opt_Ark_String surfaceId;
    Opt_Ark_String embedId;
    struct Opt_NativeEmbedInfo info;
} NativeEmbedDataInfo;
typedef struct Opt_NativeEmbedDataInfo {
    enum Ark_Tag tag;
    NativeEmbedDataInfo value;
} Opt_NativeEmbedDataInfo;
typedef struct IntelligentTrackingPreventionDetails {
    Ark_String host;
    Ark_String trackerHost;
} IntelligentTrackingPreventionDetails;
typedef struct Opt_IntelligentTrackingPreventionDetails {
    enum Ark_Tag tag;
    IntelligentTrackingPreventionDetails value;
} Opt_IntelligentTrackingPreventionDetails;
typedef struct LoadCommittedDetails {
    Ark_Boolean isMainFrame;
    Ark_Boolean isSameDocument;
    Ark_Boolean didReplaceEntry;
    Ark_WebNavigationType navigationType;
    Ark_String url;
} LoadCommittedDetails;
typedef struct Opt_LoadCommittedDetails {
    enum Ark_Tag tag;
    LoadCommittedDetails value;
} Opt_LoadCommittedDetails;
typedef Ark_Int32 Ark_ThreatType;
typedef struct Opt_Ark_ThreatType { enum Ark_Tag tag; Ark_ThreatType value; } Opt_Ark_ThreatType;
typedef struct OnOverScrollEvent {
    Ark_Number xOffset;
    Ark_Number yOffset;
} OnOverScrollEvent;
typedef struct Opt_OnOverScrollEvent {
    enum Ark_Tag tag;
    OnOverScrollEvent value;
} Opt_OnOverScrollEvent;
typedef struct OnLoadInterceptEvent {
    WebResourceRequest data;
} OnLoadInterceptEvent;
typedef struct Opt_OnLoadInterceptEvent {
    enum Ark_Tag tag;
    OnLoadInterceptEvent value;
} Opt_OnLoadInterceptEvent;
typedef struct LargestContentfulPaint {
    Opt_Ark_Number navigationStartTime;
    Opt_Ark_Number largestImagePaintTime;
    Opt_Ark_Number largestTextPaintTime;
    Opt_Ark_Number imageBPP;
    Opt_Ark_Number largestImageLoadStartTime;
    Opt_Ark_Number largestImageLoadEndTime;
} LargestContentfulPaint;
typedef struct Opt_LargestContentfulPaint {
    enum Ark_Tag tag;
    LargestContentfulPaint value;
} Opt_LargestContentfulPaint;
typedef struct FirstMeaningfulPaint {
    Opt_Ark_Number navigationStartTime;
    Opt_Ark_Number firstMeaningfulPaintTime;
} FirstMeaningfulPaint;
typedef struct Opt_FirstMeaningfulPaint {
    enum Ark_Tag tag;
    FirstMeaningfulPaint value;
} Opt_FirstMeaningfulPaint;
typedef struct OnFirstContentfulPaintEvent {
    Ark_Number navigationStartTick;
    Ark_Number firstContentfulPaintMs;
} OnFirstContentfulPaintEvent;
typedef struct Opt_OnFirstContentfulPaintEvent {
    enum Ark_Tag tag;
    OnFirstContentfulPaintEvent value;
} Opt_OnFirstContentfulPaintEvent;
typedef struct OnAudioStateChangedEvent {
    Ark_Boolean playing;
} OnAudioStateChangedEvent;
typedef struct Opt_OnAudioStateChangedEvent {
    enum Ark_Tag tag;
    OnAudioStateChangedEvent value;
} Opt_OnAudioStateChangedEvent;
typedef struct OnDataResubmittedEvent {
    DataResubmissionHandler handler;
} OnDataResubmittedEvent;
typedef struct Opt_OnDataResubmittedEvent {
    enum Ark_Tag tag;
    OnDataResubmittedEvent value;
} Opt_OnDataResubmittedEvent;
typedef struct OnPageVisibleEvent {
    Ark_String url;
} OnPageVisibleEvent;
typedef struct Opt_OnPageVisibleEvent {
    enum Ark_Tag tag;
    OnPageVisibleEvent value;
} Opt_OnPageVisibleEvent;
typedef struct OnFaviconReceivedEvent {
    Ark_CustomObject favicon;
} OnFaviconReceivedEvent;
typedef struct Opt_OnFaviconReceivedEvent {
    enum Ark_Tag tag;
    OnFaviconReceivedEvent value;
} Opt_OnFaviconReceivedEvent;
typedef struct OnTouchIconUrlReceivedEvent {
    Ark_String url;
    Ark_Boolean precomposed;
} OnTouchIconUrlReceivedEvent;
typedef struct Opt_OnTouchIconUrlReceivedEvent {
    enum Ark_Tag tag;
    OnTouchIconUrlReceivedEvent value;
} Opt_OnTouchIconUrlReceivedEvent;
typedef struct OnWindowNewEvent {
    Ark_Boolean isAlert;
    Ark_Boolean isUserTrigger;
    Ark_String targetUrl;
    ControllerHandler handler;
} OnWindowNewEvent;
typedef struct Opt_OnWindowNewEvent {
    enum Ark_Tag tag;
    OnWindowNewEvent value;
} Opt_OnWindowNewEvent;
typedef struct OnClientAuthenticationEvent {
    ClientAuthenticationHandler handler;
    Ark_String host;
    Ark_Number port;
    struct Array_Ark_String keyTypes;
    struct Array_Ark_String issuers;
} OnClientAuthenticationEvent;
typedef struct Opt_OnClientAuthenticationEvent {
    enum Ark_Tag tag;
    OnClientAuthenticationEvent value;
} Opt_OnClientAuthenticationEvent;
typedef struct SslErrorEvent {
    SslErrorHandler handler;
    Ark_SslError error;
    Ark_String url;
    Ark_String originalUrl;
    Ark_String referrer;
    Ark_Boolean isFatalError;
    Ark_Boolean isMainFrame;
} SslErrorEvent;
typedef struct Opt_SslErrorEvent {
    enum Ark_Tag tag;
    SslErrorEvent value;
} Opt_SslErrorEvent;
typedef struct OnSslErrorEventReceiveEvent {
    SslErrorHandler handler;
    Ark_SslError error;
} OnSslErrorEventReceiveEvent;
typedef struct Opt_OnSslErrorEventReceiveEvent {
    enum Ark_Tag tag;
    OnSslErrorEventReceiveEvent value;
} Opt_OnSslErrorEventReceiveEvent;
typedef struct OnScrollEvent {
    Ark_Number xOffset;
    Ark_Number yOffset;
} OnScrollEvent;
typedef struct Opt_OnScrollEvent {
    enum Ark_Tag tag;
    OnScrollEvent value;
} Opt_OnScrollEvent;
typedef struct OnSearchResultReceiveEvent {
    Ark_Number activeMatchOrdinal;
    Ark_Number numberOfMatches;
    Ark_Boolean isDoneCounting;
} OnSearchResultReceiveEvent;
typedef struct Opt_OnSearchResultReceiveEvent {
    enum Ark_Tag tag;
    OnSearchResultReceiveEvent value;
} Opt_OnSearchResultReceiveEvent;
typedef struct OnContextMenuShowEvent {
    WebContextMenuParam param;
    WebContextMenuResult result;
} OnContextMenuShowEvent;
typedef struct Opt_OnContextMenuShowEvent {
    enum Ark_Tag tag;
    OnContextMenuShowEvent value;
} Opt_OnContextMenuShowEvent;
typedef struct OnScreenCaptureRequestEvent {
    ScreenCaptureHandler handler;
} OnScreenCaptureRequestEvent;
typedef struct Opt_OnScreenCaptureRequestEvent {
    enum Ark_Tag tag;
    OnScreenCaptureRequestEvent value;
} Opt_OnScreenCaptureRequestEvent;
typedef struct OnPermissionRequestEvent {
    PermissionRequest request;
} OnPermissionRequestEvent;
typedef struct Opt_OnPermissionRequestEvent {
    enum Ark_Tag tag;
    OnPermissionRequestEvent value;
} Opt_OnPermissionRequestEvent;
typedef struct OnInterceptRequestEvent {
    WebResourceRequest request;
} OnInterceptRequestEvent;
typedef struct Opt_OnInterceptRequestEvent {
    enum Ark_Tag tag;
    OnInterceptRequestEvent value;
} Opt_OnInterceptRequestEvent;
typedef struct OnHttpAuthRequestEvent {
    HttpAuthHandler handler;
    Ark_String host;
    Ark_String realm;
} OnHttpAuthRequestEvent;
typedef struct Opt_OnHttpAuthRequestEvent {
    enum Ark_Tag tag;
    OnHttpAuthRequestEvent value;
} Opt_OnHttpAuthRequestEvent;
typedef struct OnScaleChangeEvent {
    Ark_Number oldScale;
    Ark_Number newScale;
} OnScaleChangeEvent;
typedef struct Opt_OnScaleChangeEvent {
    enum Ark_Tag tag;
    OnScaleChangeEvent value;
} Opt_OnScaleChangeEvent;
typedef struct FullScreenEnterEvent {
    FullScreenExitHandler handler;
    Opt_Ark_Number videoWidth;
    Opt_Ark_Number videoHeight;
} FullScreenEnterEvent;
typedef struct Opt_FullScreenEnterEvent {
    enum Ark_Tag tag;
    FullScreenEnterEvent value;
} Opt_FullScreenEnterEvent;
typedef struct OnResourceLoadEvent {
    Ark_String url;
} OnResourceLoadEvent;
typedef struct Opt_OnResourceLoadEvent {
    enum Ark_Tag tag;
    OnResourceLoadEvent value;
} Opt_OnResourceLoadEvent;
typedef struct Literal_callback_Ark_Function_fileSelector_Ark_CustomObject {
    Ark_Function callback;
    Ark_CustomObject fileSelector;
} Literal_callback_Ark_Function_fileSelector_Ark_CustomObject;
typedef struct Opt_Literal_callback_Ark_Function_fileSelector_Ark_CustomObject {
    enum Ark_Tag tag;
    Literal_callback_Ark_Function_fileSelector_Ark_CustomObject value;
} Opt_Literal_callback_Ark_Function_fileSelector_Ark_CustomObject;
typedef struct OnShowFileSelectorEvent {
    FileSelectorResult result;
    FileSelectorParam fileSelector;
} OnShowFileSelectorEvent;
typedef struct Opt_OnShowFileSelectorEvent {
    enum Ark_Tag tag;
    OnShowFileSelectorEvent value;
} Opt_OnShowFileSelectorEvent;
typedef struct Literal_handler_Ark_Function_error_Ark_CustomObject {
    Ark_Function handler;
    Ark_CustomObject error;
} Literal_handler_Ark_Function_error_Ark_CustomObject;
typedef struct Opt_Literal_handler_Ark_Function_error_Ark_CustomObject {
    enum Ark_Tag tag;
    Literal_handler_Ark_Function_error_Ark_CustomObject value;
} Opt_Literal_handler_Ark_Function_error_Ark_CustomObject;
typedef struct Literal_data_Union_Ark_String_WebResourceRequest {
    struct Union_Ark_String_WebResourceRequest data;
} Literal_data_Union_Ark_String_WebResourceRequest;
typedef struct Opt_Literal_data_Union_Ark_String_WebResourceRequest {
    enum Ark_Tag tag;
    Literal_data_Union_Ark_String_WebResourceRequest value;
} Opt_Literal_data_Union_Ark_String_WebResourceRequest;
typedef struct OnRefreshAccessedHistoryEvent {
    Ark_String url;
    Ark_Boolean isRefreshed;
} OnRefreshAccessedHistoryEvent;
typedef struct Opt_OnRefreshAccessedHistoryEvent {
    enum Ark_Tag tag;
    OnRefreshAccessedHistoryEvent value;
} Opt_OnRefreshAccessedHistoryEvent;
typedef struct OnDownloadStartEvent {
    Ark_String url;
    Ark_String userAgent;
    Ark_String contentDisposition;
    Ark_String mimetype;
    Ark_Number contentLength;
} OnDownloadStartEvent;
typedef struct Opt_OnDownloadStartEvent {
    enum Ark_Tag tag;
    OnDownloadStartEvent value;
} Opt_OnDownloadStartEvent;
typedef struct OnHttpErrorReceiveEvent {
    WebResourceRequest request;
    WebResourceResponse response;
} OnHttpErrorReceiveEvent;
typedef struct Opt_OnHttpErrorReceiveEvent {
    enum Ark_Tag tag;
    OnHttpErrorReceiveEvent value;
} Opt_OnHttpErrorReceiveEvent;
typedef struct OnErrorReceiveEvent {
    WebResourceRequest request;
    WebResourceError error;
} OnErrorReceiveEvent;
typedef struct Opt_OnErrorReceiveEvent {
    enum Ark_Tag tag;
    OnErrorReceiveEvent value;
} Opt_OnErrorReceiveEvent;
typedef struct OnConsoleEvent {
    ConsoleMessage message;
} OnConsoleEvent;
typedef struct Opt_OnConsoleEvent {
    enum Ark_Tag tag;
    OnConsoleEvent value;
} Opt_OnConsoleEvent;
typedef struct OnPromptEvent {
    Ark_String url;
    Ark_String message;
    Ark_String value;
    JsResult result;
} OnPromptEvent;
typedef struct Opt_OnPromptEvent {
    enum Ark_Tag tag;
    OnPromptEvent value;
} Opt_OnPromptEvent;
typedef struct OnConfirmEvent {
    Ark_String url;
    Ark_String message;
    JsResult result;
} OnConfirmEvent;
typedef struct Opt_OnConfirmEvent {
    enum Ark_Tag tag;
    OnConfirmEvent value;
} Opt_OnConfirmEvent;
typedef struct OnBeforeUnloadEvent {
    Ark_String url;
    Ark_String message;
    JsResult result;
} OnBeforeUnloadEvent;
typedef struct Opt_OnBeforeUnloadEvent {
    enum Ark_Tag tag;
    OnBeforeUnloadEvent value;
} Opt_OnBeforeUnloadEvent;
typedef struct OnAlertEvent {
    Ark_String url;
    Ark_String message;
    JsResult result;
} OnAlertEvent;
typedef struct Opt_OnAlertEvent {
    enum Ark_Tag tag;
    OnAlertEvent value;
} Opt_OnAlertEvent;
typedef struct OnGeolocationShowEvent {
    Ark_String origin;
    JsGeolocation geolocation;
} OnGeolocationShowEvent;
typedef struct Opt_OnGeolocationShowEvent {
    enum Ark_Tag tag;
    OnGeolocationShowEvent value;
} Opt_OnGeolocationShowEvent;
typedef struct OnTitleReceiveEvent {
    Ark_String title;
} OnTitleReceiveEvent;
typedef struct Opt_OnTitleReceiveEvent {
    enum Ark_Tag tag;
    OnTitleReceiveEvent value;
} Opt_OnTitleReceiveEvent;
typedef struct OnProgressChangeEvent {
    Ark_Number newProgress;
} OnProgressChangeEvent;
typedef struct Opt_OnProgressChangeEvent {
    enum Ark_Tag tag;
    OnProgressChangeEvent value;
} Opt_OnProgressChangeEvent;
typedef struct OnPageBeginEvent {
    Ark_String url;
} OnPageBeginEvent;
typedef struct Opt_OnPageBeginEvent {
    enum Ark_Tag tag;
    OnPageBeginEvent value;
} Opt_OnPageBeginEvent;
typedef struct OnPageEndEvent {
    Ark_String url;
} OnPageEndEvent;
typedef struct Opt_OnPageEndEvent {
    enum Ark_Tag tag;
    OnPageEndEvent value;
} Opt_OnPageEndEvent;
typedef struct Literal_time_Ark_Number {
    Ark_Number time;
} Literal_time_Ark_Number;
typedef struct Opt_Literal_time_Ark_Number {
    enum Ark_Tag tag;
    Literal_time_Ark_Number value;
} Opt_Literal_time_Ark_Number;
typedef struct Literal_duration_Ark_Number {
    Ark_Number duration;
} Literal_duration_Ark_Number;
typedef struct Opt_Literal_duration_Ark_Number {
    enum Ark_Tag tag;
    Literal_duration_Ark_Number value;
} Opt_Literal_duration_Ark_Number;
typedef struct Literal_fullscreen_Ark_Boolean {
    Ark_Boolean fullscreen;
} Literal_fullscreen_Ark_Boolean;
typedef struct Opt_Literal_fullscreen_Ark_Boolean {
    enum Ark_Tag tag;
    Literal_fullscreen_Ark_Boolean value;
} Opt_Literal_fullscreen_Ark_Boolean;
typedef struct TimePickerResult {
    Ark_Number hour;
    Ark_Number minute;
    Ark_Number second;
} TimePickerResult;
typedef struct Opt_TimePickerResult {
    enum Ark_Tag tag;
    TimePickerResult value;
} Opt_TimePickerResult;
typedef Ark_Int32 Ark_MarqueeState;
typedef struct Opt_Ark_MarqueeState { enum Ark_Tag tag; Ark_MarqueeState value; } Opt_Ark_MarqueeState;
typedef struct TabsAnimationEvent {
    Ark_Number currentOffset;
    Ark_Number targetOffset;
    Ark_Number velocity;
} TabsAnimationEvent;
typedef struct Opt_TabsAnimationEvent {
    enum Ark_Tag tag;
    TabsAnimationEvent value;
} Opt_TabsAnimationEvent;
typedef struct SwiperAnimationEvent {
    Ark_Number currentOffset;
    Ark_Number targetOffset;
    Ark_Number velocity;
} SwiperAnimationEvent;
typedef struct Opt_SwiperAnimationEvent {
    enum Ark_Tag tag;
    SwiperAnimationEvent value;
} Opt_SwiperAnimationEvent;
typedef Ark_Int32 Ark_SliderChangeMode;
typedef struct Opt_Ark_SliderChangeMode { enum Ark_Tag tag; Ark_SliderChangeMode value; } Opt_Ark_SliderChangeMode;
typedef struct DeleteValue {
    Ark_Number deleteOffset;
    Ark_TextDeleteDirection direction;
    Ark_String deleteValue;
} DeleteValue;
typedef struct Opt_DeleteValue {
    enum Ark_Tag tag;
    DeleteValue value;
} Opt_DeleteValue;
typedef struct InsertValue {
    Ark_Number insertOffset;
    Ark_String insertValue;
} InsertValue;
typedef struct Opt_InsertValue {
    enum Ark_Tag tag;
    InsertValue value;
} Opt_InsertValue;
typedef Ark_Int32 Ark_SaveButtonOnClickResult;
typedef struct Opt_Ark_SaveButtonOnClickResult { enum Ark_Tag tag; Ark_SaveButtonOnClickResult value; } Opt_Ark_SaveButtonOnClickResult;
typedef struct CopyEvent {
    struct Opt_Ark_Function preventDefault;
} CopyEvent;
typedef struct Opt_CopyEvent {
    enum Ark_Tag tag;
    CopyEvent value;
} Opt_CopyEvent;
typedef struct CutEvent {
    struct Opt_Ark_Function preventDefault;
} CutEvent;
typedef struct Opt_CutEvent {
    enum Ark_Tag tag;
    CutEvent value;
} Opt_CutEvent;
typedef struct RichEditorChangeValue {
    struct TextRange rangeBefore;
    struct Array_RichEditorTextSpanResult replacedSpans;
    struct Array_RichEditorImageSpanResult replacedImageSpans;
    struct Array_RichEditorTextSpanResult replacedSymbolSpans;
} RichEditorChangeValue;
typedef struct Opt_RichEditorChangeValue {
    enum Ark_Tag tag;
    RichEditorChangeValue value;
} Opt_RichEditorChangeValue;
typedef struct SubmitEvent {
    Ark_String text;
} SubmitEvent;
typedef struct Opt_SubmitEvent {
    enum Ark_Tag tag;
    SubmitEvent value;
} Opt_SubmitEvent;
typedef struct PasteEvent {
    struct Opt_Ark_Function preventDefault;
} PasteEvent;
typedef struct Opt_PasteEvent {
    enum Ark_Tag tag;
    PasteEvent value;
} Opt_PasteEvent;
typedef struct Union_RichEditorTextSpanResult_RichEditorImageSpanResult {
    Ark_Int32 selector;
    union {
        struct RichEditorTextSpanResult value0;
        struct RichEditorImageSpanResult value1;
    };
} Union_RichEditorTextSpanResult_RichEditorImageSpanResult;
typedef struct Opt_Union_RichEditorTextSpanResult_RichEditorImageSpanResult {
    enum Ark_Tag tag;
    Union_RichEditorTextSpanResult_RichEditorImageSpanResult value;
} Opt_Union_RichEditorTextSpanResult_RichEditorImageSpanResult;
typedef struct RichEditorDeleteValue {
    Ark_Number offset;
    Ark_RichEditorDeleteDirection direction;
    Ark_Number length;
    struct Array_Union_RichEditorTextSpanResult_RichEditorImageSpanResult richEditorDeleteSpans;
} RichEditorDeleteValue;
typedef struct Opt_RichEditorDeleteValue {
    enum Ark_Tag tag;
    RichEditorDeleteValue value;
} Opt_RichEditorDeleteValue;
typedef struct RichEditorInsertValue {
    Ark_Number insertOffset;
    Ark_String insertValue;
    Opt_Ark_String previewText;
} RichEditorInsertValue;
typedef struct Opt_RichEditorInsertValue {
    enum Ark_Tag tag;
    RichEditorInsertValue value;
} Opt_RichEditorInsertValue;
typedef struct RichEditorSelection {
    struct Tuple_Ark_Number_Ark_Number selection;
    struct Array_Union_RichEditorTextSpanResult_RichEditorImageSpanResult spans;
} RichEditorSelection;
typedef struct Opt_RichEditorSelection {
    enum Ark_Tag tag;
    RichEditorSelection value;
} Opt_RichEditorSelection;
typedef Ark_Int32 Ark_RefreshStatus;
typedef struct Opt_Ark_RefreshStatus { enum Ark_Tag tag; Ark_RefreshStatus value; } Opt_Ark_RefreshStatus;
typedef struct Literal_errcode_Ark_Number_msg_Ark_String {
    Ark_Number errcode;
    Ark_String msg;
} Literal_errcode_Ark_Number_msg_Ark_String;
typedef struct Opt_Literal_errcode_Ark_Number_msg_Ark_String {
    enum Ark_Tag tag;
    Literal_errcode_Ark_Number_msg_Ark_String value;
} Opt_Literal_errcode_Ark_Number_msg_Ark_String;
typedef Ark_Int32 Ark_PasteButtonOnClickResult;
typedef struct Opt_Ark_PasteButtonOnClickResult { enum Ark_Tag tag; Ark_PasteButtonOnClickResult value; } Opt_Ark_PasteButtonOnClickResult;
typedef Ark_Int32 Ark_NavigationOperation;
typedef struct Opt_Ark_NavigationOperation { enum Ark_Tag tag; Ark_NavigationOperation value; } Opt_Ark_NavigationOperation;
typedef struct NavContentInfo {
    Opt_Ark_String name;
    Ark_Number index;
    Opt_Ark_NavDestinationMode mode;
    struct Opt_Object param;
    Opt_Ark_String navDestinationId;
} NavContentInfo;
typedef struct Opt_NavContentInfo {
    enum Ark_Tag tag;
    NavContentInfo value;
} Opt_NavContentInfo;
typedef Ark_Int32 Ark_LocationButtonOnClickResult;
typedef struct Opt_Ark_LocationButtonOnClickResult { enum Ark_Tag tag; Ark_LocationButtonOnClickResult value; } Opt_Ark_LocationButtonOnClickResult;
typedef struct VisibleListContentInfo {
    Ark_Number index;
    Opt_Ark_ListItemGroupArea itemGroupArea;
    Opt_Ark_Number itemIndexInGroup;
} VisibleListContentInfo;
typedef struct Opt_VisibleListContentInfo {
    enum Ark_Tag tag;
    VisibleListContentInfo value;
} Opt_VisibleListContentInfo;
typedef struct ImageLoadResult {
    Ark_Number width;
    Ark_Number height;
    Ark_Number componentWidth;
    Ark_Number componentHeight;
    Ark_Number loadingStatus;
    Ark_Number contentWidth;
    Ark_Number contentHeight;
    Ark_Number contentOffsetX;
    Ark_Number contentOffsetY;
} ImageLoadResult;
typedef struct Opt_ImageLoadResult {
    enum Ark_Tag tag;
    ImageLoadResult value;
} Opt_ImageLoadResult;
typedef struct ImageError {
    Ark_Number componentWidth;
    Ark_Number componentHeight;
    Ark_String message;
} ImageError;
typedef struct Opt_ImageError {
    enum Ark_Tag tag;
    ImageError value;
} Opt_ImageError;
typedef struct Literal_width_Ark_Number_height_Ark_Number_componentWidth_Ark_Number_componentHeight_Ark_Number_loadingStatus_Ark_Number_contentWidth_Ark_Number_contentHeight_Ark_Number_contentOffsetX_Ark_Number_contentOffsetY_Ark_Number {
    Ark_Number width;
    Ark_Number height;
    Ark_Number componentWidth;
    Ark_Number componentHeight;
    Ark_Number loadingStatus;
    Ark_Number contentWidth;
    Ark_Number contentHeight;
    Ark_Number contentOffsetX;
    Ark_Number contentOffsetY;
} Literal_width_Ark_Number_height_Ark_Number_componentWidth_Ark_Number_componentHeight_Ark_Number_loadingStatus_Ark_Number_contentWidth_Ark_Number_contentHeight_Ark_Number_contentOffsetX_Ark_Number_contentOffsetY_Ark_Number;
typedef struct Opt_Literal_width_Ark_Number_height_Ark_Number_componentWidth_Ark_Number_componentHeight_Ark_Number_loadingStatus_Ark_Number_contentWidth_Ark_Number_contentHeight_Ark_Number_contentOffsetX_Ark_Number_contentOffsetY_Ark_Number {
    enum Ark_Tag tag;
    Literal_width_Ark_Number_height_Ark_Number_componentWidth_Ark_Number_componentHeight_Ark_Number_loadingStatus_Ark_Number_contentWidth_Ark_Number_contentHeight_Ark_Number_contentOffsetX_Ark_Number_contentOffsetY_Ark_Number value;
} Opt_Literal_width_Ark_Number_height_Ark_Number_componentWidth_Ark_Number_componentHeight_Ark_Number_loadingStatus_Ark_Number_contentWidth_Ark_Number_contentHeight_Ark_Number_contentOffsetX_Ark_Number_contentOffsetY_Ark_Number;
typedef struct ItemDragInfo {
    Ark_Number x;
    Ark_Number y;
} ItemDragInfo;
typedef struct Opt_ItemDragInfo {
    enum Ark_Tag tag;
    ItemDragInfo value;
} Opt_ItemDragInfo;
typedef struct FormCallbackInfo {
    Ark_Number id;
    Ark_String idString;
} FormCallbackInfo;
typedef struct Opt_FormCallbackInfo {
    enum Ark_Tag tag;
    FormCallbackInfo value;
} Opt_FormCallbackInfo;
typedef struct HoverEventParam {
    Ark_FoldStatus foldStatus;
    Ark_Boolean isHoverMode;
    Ark_AppRotation appRotation;
    Ark_CustomObject windowStatusType;
} HoverEventParam;
typedef struct Opt_HoverEventParam {
    enum Ark_Tag tag;
    HoverEventParam value;
} Opt_HoverEventParam;
typedef struct Literal_foldStatus_Ark_FoldStatus {
    Ark_FoldStatus foldStatus;
} Literal_foldStatus_Ark_FoldStatus;
typedef struct Opt_Literal_foldStatus_Ark_FoldStatus {
    enum Ark_Tag tag;
    Literal_foldStatus_Ark_FoldStatus value;
} Opt_Literal_foldStatus_Ark_FoldStatus;
typedef struct DatePickerResult {
    Opt_Ark_Number year;
    Opt_Ark_Number month;
    Opt_Ark_Number day;
} DatePickerResult;
typedef struct Opt_DatePickerResult {
    enum Ark_Tag tag;
    DatePickerResult value;
} Opt_DatePickerResult;
typedef Ark_Int32 Ark_ScrollState;
typedef struct Opt_Ark_ScrollState { enum Ark_Tag tag; Ark_ScrollState value; } Opt_Ark_ScrollState;
typedef Ark_Materialized GestureRecognizer;
typedef struct Array_GestureRecognizer {
    GestureRecognizer* array;
    Ark_Int32 length;
} Array_GestureRecognizer;
typedef struct Opt_Array_GestureRecognizer {
    enum Ark_Tag tag;
    Array_GestureRecognizer value;
} Opt_Array_GestureRecognizer;
typedef Ark_Materialized GestureRecognizer;
typedef struct Opt_GestureRecognizer {
    enum Ark_Tag tag;
    GestureRecognizer value;
} Opt_GestureRecognizer;
typedef struct FingerInfo {
    Ark_Number id;
    Ark_Number globalX;
    Ark_Number globalY;
    Ark_Number localX;
    Ark_Number localY;
    Ark_Number displayX;
    Ark_Number displayY;
} FingerInfo;
typedef struct Opt_FingerInfo {
    enum Ark_Tag tag;
    FingerInfo value;
} Opt_FingerInfo;
typedef struct BaseGestureEvent {
    struct EventTarget target;
    Ark_Number timestamp;
    Ark_SourceType source;
    Opt_Ark_Number axisHorizontal;
    Opt_Ark_Number axisVertical;
    Ark_Number pressure;
    Ark_Number tiltX;
    Ark_Number tiltY;
    Ark_SourceTool sourceTool;
    struct Array_FingerInfo fingerList;
} BaseGestureEvent;
typedef struct Opt_BaseGestureEvent {
    enum Ark_Tag tag;
    BaseGestureEvent value;
} Opt_BaseGestureEvent;
typedef struct GestureInfo {
    Opt_Ark_String tag;
    Ark_GestureControl_GestureType type;
    Ark_Boolean isSystemGesture;
} GestureInfo;
typedef struct Opt_GestureInfo {
    enum Ark_Tag tag;
    GestureInfo value;
} Opt_GestureInfo;
typedef Ark_Int32 Ark_PreDragStatus;
typedef struct Opt_Ark_PreDragStatus { enum Ark_Tag tag; Ark_PreDragStatus value; } Opt_Ark_PreDragStatus;
typedef struct DragEvent {
    Ark_DragBehavior dragBehavior;
    Ark_Boolean useCustomDropAnimation;
} DragEvent;
typedef struct Opt_DragEvent {
    enum Ark_Tag tag;
    DragEvent value;
} Opt_DragEvent;
typedef struct KeyEvent {
    Ark_KeyType type;
    Ark_Number keyCode;
    Ark_String keyText;
    Ark_KeySource keySource;
    Ark_Number deviceId;
    Ark_Number metaKey;
    Ark_Number timestamp;
    struct Ark_Function stopPropagation;
    Ark_CustomObject intentionCode;
} KeyEvent;
typedef struct Opt_KeyEvent {
    enum Ark_Tag tag;
    KeyEvent value;
} Opt_KeyEvent;
typedef struct TouchObject {
    Ark_TouchType type;
    Ark_Number id;
    Ark_Number displayX;
    Ark_Number displayY;
    Ark_Number windowX;
    Ark_Number windowY;
    Ark_Number screenX;
    Ark_Number screenY;
    Ark_Number x;
    Ark_Number y;
} TouchObject;
typedef struct Opt_TouchObject {
    enum Ark_Tag tag;
    TouchObject value;
} Opt_TouchObject;
typedef struct MouseEvent {
    struct EventTarget target;
    Ark_Number timestamp;
    Ark_SourceType source;
    Opt_Ark_Number axisHorizontal;
    Opt_Ark_Number axisVertical;
    Ark_Number pressure;
    Ark_Number tiltX;
    Ark_Number tiltY;
    Ark_SourceTool sourceTool;
    Ark_MouseButton button;
    Ark_MouseAction action;
    Ark_Number displayX;
    Ark_Number displayY;
    Ark_Number windowX;
    Ark_Number windowY;
    Ark_Number screenX;
    Ark_Number screenY;
    Ark_Number x;
    Ark_Number y;
    struct Ark_Function stopPropagation;
} MouseEvent;
typedef struct Opt_MouseEvent {
    enum Ark_Tag tag;
    MouseEvent value;
} Opt_MouseEvent;
typedef struct HoverEvent {
    struct EventTarget target;
    Ark_Number timestamp;
    Ark_SourceType source;
    Opt_Ark_Number axisHorizontal;
    Opt_Ark_Number axisVertical;
    Ark_Number pressure;
    Ark_Number tiltX;
    Ark_Number tiltY;
    Ark_SourceTool sourceTool;
    struct Ark_Function stopPropagation;
} HoverEvent;
typedef struct Opt_HoverEvent {
    enum Ark_Tag tag;
    HoverEvent value;
} Opt_HoverEvent;
typedef struct ClickEvent {
    struct EventTarget target;
    Ark_Number timestamp;
    Ark_SourceType source;
    Opt_Ark_Number axisHorizontal;
    Opt_Ark_Number axisVertical;
    Ark_Number pressure;
    Ark_Number tiltX;
    Ark_Number tiltY;
    Ark_SourceTool sourceTool;
    Ark_Number displayX;
    Ark_Number displayY;
    Ark_Number windowX;
    Ark_Number windowY;
    Ark_Number screenX;
    Ark_Number screenY;
    Ark_Number x;
    Ark_Number y;
    struct Ark_Function preventDefault;
} ClickEvent;
typedef struct Opt_ClickEvent {
    enum Ark_Tag tag;
    ClickEvent value;
} Opt_ClickEvent;
typedef struct TouchTestInfo {
    Ark_Number windowX;
    Ark_Number windowY;
    Ark_Number parentX;
    Ark_Number parentY;
    Ark_Number x;
    Ark_Number y;
    struct RectResult rect;
    Ark_String id;
} TouchTestInfo;
typedef struct Opt_TouchTestInfo {
    enum Ark_Tag tag;
    TouchTestInfo value;
} Opt_TouchTestInfo;
typedef struct Array_TouchTestInfo {
    struct TouchTestInfo* array;
    Ark_Int32 length;
} Array_TouchTestInfo;
typedef struct Opt_Array_TouchTestInfo {
    enum Ark_Tag tag;
    Array_TouchTestInfo value;
} Opt_Array_TouchTestInfo;
typedef struct CheckboxGroupResult {
    struct Array_Ark_String name;
    Ark_SelectStatus status;
} CheckboxGroupResult;
typedef struct Opt_CheckboxGroupResult {
    enum Ark_Tag tag;
    CheckboxGroupResult value;
} Opt_CheckboxGroupResult;
typedef struct CalendarRequestedData {
    Ark_Number year;
    Ark_Number month;
    Ark_Number currentYear;
    Ark_Number currentMonth;
    Ark_Number monthState;
} CalendarRequestedData;
typedef struct Opt_CalendarRequestedData {
    enum Ark_Tag tag;
    CalendarRequestedData value;
} Opt_CalendarRequestedData;
typedef struct CalendarSelectedDate {
    Ark_Number year;
    Ark_Number month;
    Ark_Number day;
} CalendarSelectedDate;
typedef struct Opt_CalendarSelectedDate {
    enum Ark_Tag tag;
    CalendarSelectedDate value;
} Opt_CalendarSelectedDate;
typedef struct LinearIndicatorStartOptions {
    Opt_Ark_Number interval;
    Opt_Ark_Number duration;
} LinearIndicatorStartOptions;
typedef struct Opt_LinearIndicatorStartOptions {
    enum Ark_Tag tag;
    LinearIndicatorStartOptions value;
} Opt_LinearIndicatorStartOptions;
typedef struct SectionOptions {
    Ark_Number itemsCount;
    Opt_Ark_Number crossCount;
    struct Opt_Ark_Function onGetItemMainSizeByIndex;
    Opt_Ark_Length columnsGap;
    Opt_Ark_Length rowsGap;
    struct Opt_Union_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length_Ark_Length margin;
} SectionOptions;
typedef struct Opt_SectionOptions {
    enum Ark_Tag tag;
    SectionOptions value;
} Opt_SectionOptions;
typedef struct Array_SectionOptions {
    struct SectionOptions* array;
    Ark_Int32 length;
} Array_SectionOptions;
typedef struct Opt_Array_SectionOptions {
    enum Ark_Tag tag;
    Array_SectionOptions value;
} Opt_Array_SectionOptions;
typedef struct SurfaceRotationOptions {
    Opt_Ark_Boolean lock;
} SurfaceRotationOptions;
typedef struct Opt_SurfaceRotationOptions {
    enum Ark_Tag tag;
    SurfaceRotationOptions value;
} Opt_SurfaceRotationOptions;
typedef struct SurfaceRect {
    Opt_Ark_Number offsetX;
    Opt_Ark_Number offsetY;
    Ark_Number surfaceWidth;
    Ark_Number surfaceHeight;
} SurfaceRect;
typedef struct Opt_SurfaceRect {
    enum Ark_Tag tag;
    SurfaceRect value;
} Opt_SurfaceRect;
typedef struct Literal_surfaceWidth_Ark_Number_surfaceHeight_Ark_Number {
    Ark_Number surfaceWidth;
    Ark_Number surfaceHeight;
} Literal_surfaceWidth_Ark_Number_surfaceHeight_Ark_Number;
typedef struct Opt_Literal_surfaceWidth_Ark_Number_surfaceHeight_Ark_Number {
    enum Ark_Tag tag;
    Literal_surfaceWidth_Ark_Number_surfaceHeight_Ark_Number value;
} Opt_Literal_surfaceWidth_Ark_Number_surfaceHeight_Ark_Number;
typedef struct ScreenCaptureConfig {
    Ark_WebCaptureMode captureMode;
} ScreenCaptureConfig;
typedef struct Opt_ScreenCaptureConfig {
    enum Ark_Tag tag;
    ScreenCaptureConfig value;
} Opt_ScreenCaptureConfig;
typedef struct Union_Ark_String_Ark_Number_Ark_Resource_ArrayBuffer {
    Ark_Int32 selector;
    union {
        Ark_String value0;
        Ark_Number value1;
        Ark_Resource value2;
        struct ArrayBuffer value3;
    };
} Union_Ark_String_Ark_Number_Ark_Resource_ArrayBuffer;
typedef struct Opt_Union_Ark_String_Ark_Number_Ark_Resource_ArrayBuffer {
    enum Ark_Tag tag;
    Union_Ark_String_Ark_Number_Ark_Resource_ArrayBuffer value;
} Opt_Union_Ark_String_Ark_Number_Ark_Resource_ArrayBuffer;
typedef Ark_Int32 Ark_MessageLevel;
typedef struct Opt_Ark_MessageLevel { enum Ark_Tag tag; Ark_MessageLevel value; } Opt_Ark_MessageLevel;
typedef struct Literal_object_Ark_CustomObject_name_Ark_String_methodList_Array_Ark_String {
    Ark_CustomObject object;
    Ark_String name;
    struct Array_Ark_String methodList;
} Literal_object_Ark_CustomObject_name_Ark_String_methodList_Array_Ark_String;
typedef struct Opt_Literal_object_Ark_CustomObject_name_Ark_String_methodList_Array_Ark_String {
    enum Ark_Tag tag;
    Literal_object_Ark_CustomObject_name_Ark_String_methodList_Array_Ark_String value;
} Opt_Literal_object_Ark_CustomObject_name_Ark_String_methodList_Array_Ark_String;
typedef struct Header {
    Ark_String headerKey;
    Ark_String headerValue;
} Header;
typedef struct Opt_Header {
    enum Ark_Tag tag;
    Header value;
} Opt_Header;
typedef struct Literal_url_Union_Ark_String_Ark_Resource_headers_Opt_Array_Header {
    struct Union_Ark_String_Ark_Resource url;
    struct Opt_Array_Header headers;
} Literal_url_Union_Ark_String_Ark_Resource_headers_Opt_Array_Header;
typedef struct Opt_Literal_url_Union_Ark_String_Ark_Resource_headers_Opt_Array_Header {
    enum Ark_Tag tag;
    Literal_url_Union_Ark_String_Ark_Resource_headers_Opt_Array_Header value;
} Opt_Literal_url_Union_Ark_String_Ark_Resource_headers_Opt_Array_Header;
typedef struct Literal_data_Ark_String_mimeType_Ark_String_encoding_Ark_String_baseUrl_Opt_Ark_String_historyUrl_Opt_Ark_String {
    Ark_String data;
    Ark_String mimeType;
    Ark_String encoding;
    Opt_Ark_String baseUrl;
    Opt_Ark_String historyUrl;
} Literal_data_Ark_String_mimeType_Ark_String_encoding_Ark_String_baseUrl_Opt_Ark_String_historyUrl_Opt_Ark_String;
typedef struct Opt_Literal_data_Ark_String_mimeType_Ark_String_encoding_Ark_String_baseUrl_Opt_Ark_String_historyUrl_Opt_Ark_String {
    enum Ark_Tag tag;
    Literal_data_Ark_String_mimeType_Ark_String_encoding_Ark_String_baseUrl_Opt_Ark_String_historyUrl_Opt_Ark_String value;
} Opt_Literal_data_Ark_String_mimeType_Ark_String_encoding_Ark_String_baseUrl_Opt_Ark_String_historyUrl_Opt_Ark_String;
typedef struct Literal_script_Ark_String_callback_Opt_Ark_Function {
    Ark_String script;
    struct Opt_Ark_Function callback;
} Literal_script_Ark_String_callback_Opt_Ark_Function;
typedef struct Opt_Literal_script_Ark_String_callback_Opt_Ark_Function {
    enum Ark_Tag tag;
    Literal_script_Ark_String_callback_Opt_Ark_Function value;
} Opt_Literal_script_Ark_String_callback_Opt_Ark_Function;
typedef Ark_Int32 Ark_SeekMode;
typedef struct Opt_Ark_SeekMode { enum Ark_Tag tag; Ark_SeekMode value; } Opt_Ark_SeekMode;
typedef struct SpanStyle {
    Ark_Number start;
    Ark_Number length;
    Ark_StyledStringKey styledKey;
    struct Union_TextStyle_DecorationStyle_BaselineOffsetStyle_LetterSpacingStyle_TextShadowStyle_GestureStyle_ImageAttachment_ParagraphStyle_LineHeightStyle_CustomSpan_UserDataSpan styledValue;
} SpanStyle;
typedef struct Opt_SpanStyle {
    enum Ark_Tag tag;
    SpanStyle value;
} Opt_SpanStyle;
typedef struct StyledStringChangedListener {
    struct Opt_Ark_Function onWillChange;
    struct Opt_Ark_Function onDidChange;
} StyledStringChangedListener;
typedef struct Opt_StyledStringChangedListener {
    enum Ark_Tag tag;
    StyledStringChangedListener value;
} Opt_StyledStringChangedListener;
typedef struct CustomSpanDrawInfo {
    Ark_Number x;
    Ark_Number lineTop;
    Ark_Number lineBottom;
    Ark_Number baseline;
} CustomSpanDrawInfo;
typedef struct Opt_CustomSpanDrawInfo {
    enum Ark_Tag tag;
    CustomSpanDrawInfo value;
} Opt_CustomSpanDrawInfo;
typedef struct CustomSpanMeasureInfo {
    Ark_Number fontSize;
} CustomSpanMeasureInfo;
typedef struct Opt_CustomSpanMeasureInfo {
    enum Ark_Tag tag;
    CustomSpanMeasureInfo value;
} Opt_CustomSpanMeasureInfo;
typedef struct StyleOptions {
    Opt_Ark_Number start;
    Opt_Ark_Number length;
    Ark_StyledStringKey styledKey;
    struct Union_TextStyle_DecorationStyle_BaselineOffsetStyle_LetterSpacingStyle_TextShadowStyle_GestureStyle_ImageAttachment_ParagraphStyle_LineHeightStyle_CustomSpan_UserDataSpan styledValue;
} StyleOptions;
typedef struct Opt_StyleOptions {
    enum Ark_Tag tag;
    StyleOptions value;
} Opt_StyleOptions;
typedef struct Array_StyleOptions {
    struct StyleOptions* array;
    Ark_Int32 length;
} Array_StyleOptions;
typedef struct Opt_Array_StyleOptions {
    enum Ark_Tag tag;
    Array_StyleOptions value;
} Opt_Array_StyleOptions;
typedef struct Union_Ark_String_ImageAttachment_CustomSpan {
    Ark_Int32 selector;
    union {
        Ark_String value0;
        struct ImageAttachment value1;
        CustomSpan value2;
    };
} Union_Ark_String_ImageAttachment_CustomSpan;
typedef struct Opt_Union_Ark_String_ImageAttachment_CustomSpan {
    enum Ark_Tag tag;
    Union_Ark_String_ImageAttachment_CustomSpan value;
} Opt_Union_Ark_String_ImageAttachment_CustomSpan;
typedef struct SelectionOptions {
    Opt_Ark_MenuPolicy menuPolicy;
} SelectionOptions;
typedef struct Opt_SelectionOptions {
    enum Ark_Tag tag;
    SelectionOptions value;
} Opt_SelectionOptions;
typedef Ark_Materialized StyledString;
typedef struct Opt_StyledString {
    enum Ark_Tag tag;
    StyledString value;
} Opt_StyledString;
typedef struct RichEditorParagraphStyleOptions {
    Opt_Ark_Number start;
    Opt_Ark_Number end;
    struct RichEditorParagraphStyle style;
} RichEditorParagraphStyleOptions;
typedef struct Opt_RichEditorParagraphStyleOptions {
    enum Ark_Tag tag;
    RichEditorParagraphStyleOptions value;
} Opt_RichEditorParagraphStyleOptions;
typedef struct Union_RichEditorUpdateTextSpanStyleOptions_RichEditorUpdateImageSpanStyleOptions_RichEditorUpdateSymbolSpanStyleOptions {
    Ark_Int32 selector;
    union {
        struct RichEditorUpdateTextSpanStyleOptions value0;
        struct RichEditorUpdateImageSpanStyleOptions value1;
        struct RichEditorUpdateSymbolSpanStyleOptions value2;
    };
} Union_RichEditorUpdateTextSpanStyleOptions_RichEditorUpdateImageSpanStyleOptions_RichEditorUpdateSymbolSpanStyleOptions;
typedef struct Opt_Union_RichEditorUpdateTextSpanStyleOptions_RichEditorUpdateImageSpanStyleOptions_RichEditorUpdateSymbolSpanStyleOptions {
    enum Ark_Tag tag;
    Union_RichEditorUpdateTextSpanStyleOptions_RichEditorUpdateImageSpanStyleOptions_RichEditorUpdateSymbolSpanStyleOptions value;
} Opt_Union_RichEditorUpdateTextSpanStyleOptions_RichEditorUpdateImageSpanStyleOptions_RichEditorUpdateSymbolSpanStyleOptions;
typedef struct RichEditorSymbolSpanOptions {
    Opt_Ark_Number offset;
    struct Opt_RichEditorSymbolSpanStyle style;
} RichEditorSymbolSpanOptions;
typedef struct Opt_RichEditorSymbolSpanOptions {
    enum Ark_Tag tag;
    RichEditorSymbolSpanOptions value;
} Opt_RichEditorSymbolSpanOptions;
typedef struct RichEditorBuilderSpanOptions {
    Opt_Ark_Number offset;
} RichEditorBuilderSpanOptions;
typedef struct Opt_RichEditorBuilderSpanOptions {
    enum Ark_Tag tag;
    RichEditorBuilderSpanOptions value;
} Opt_RichEditorBuilderSpanOptions;
typedef struct RichEditorImageSpanOptions {
    Opt_Ark_Number offset;
    struct Opt_RichEditorImageSpanStyle imageStyle;
    struct Opt_RichEditorGesture gesture;
} RichEditorImageSpanOptions;
typedef struct Opt_RichEditorImageSpanOptions {
    enum Ark_Tag tag;
    RichEditorImageSpanOptions value;
} Opt_RichEditorImageSpanOptions;
typedef struct Union_Ark_CustomObject_Union_Ark_String_Ark_Resource {
    Ark_Int32 selector;
    union {
        Ark_CustomObject value0;
        struct Union_Ark_String_Ark_Resource value1;
    };
} Union_Ark_CustomObject_Union_Ark_String_Ark_Resource;
typedef struct Opt_Union_Ark_CustomObject_Union_Ark_String_Ark_Resource {
    enum Ark_Tag tag;
    Union_Ark_CustomObject_Union_Ark_String_Ark_Resource value;
} Opt_Union_Ark_CustomObject_Union_Ark_String_Ark_Resource;
typedef struct RichEditorTextSpanOptions {
    Opt_Ark_Number offset;
    struct Opt_RichEditorTextStyle style;
    struct Opt_RichEditorParagraphStyle paragraphStyle;
    struct Opt_RichEditorGesture gesture;
} RichEditorTextSpanOptions;
typedef struct Opt_RichEditorTextSpanOptions {
    enum Ark_Tag tag;
    RichEditorTextSpanOptions value;
} Opt_RichEditorTextSpanOptions;
typedef struct TextMenuItem {
    struct Union_Ark_String_Ark_Resource content;
    struct Opt_Union_Ark_String_Ark_Resource icon;
    TextMenuItemId id;
} TextMenuItem;
typedef struct Opt_TextMenuItem {
    enum Ark_Tag tag;
    TextMenuItem value;
} Opt_TextMenuItem;
typedef struct Array_TextMenuItem {
    struct TextMenuItem* array;
    Ark_Int32 length;
} Array_TextMenuItem;
typedef struct Opt_Array_TextMenuItem {
    enum Ark_Tag tag;
    Array_TextMenuItem value;
} Opt_Array_TextMenuItem;
typedef Ark_Int32 Ark_PatternLockChallengeResult;
typedef struct Opt_Ark_PatternLockChallengeResult { enum Ark_Tag tag; Ark_PatternLockChallengeResult value; } Opt_Ark_PatternLockChallengeResult;
typedef struct NavigationInterception {
    struct Opt_Ark_Function willShow;
    struct Opt_Ark_Function didShow;
    struct Opt_Ark_Function modeChange;
} NavigationInterception;
typedef struct Opt_NavigationInterception {
    enum Ark_Tag tag;
    NavigationInterception value;
} Opt_NavigationInterception;
typedef struct NavigationOptions {
    Opt_Ark_LaunchMode launchMode;
    Opt_Ark_Boolean animated;
} NavigationOptions;
typedef struct Opt_NavigationOptions {
    enum Ark_Tag tag;
    NavigationOptions value;
} Opt_NavigationOptions;
typedef struct NavPathInfo {
    Ark_String name;
    Opt_Ark_CustomObject param;
    Opt_Ark_Function onPop;
} NavPathInfo;
typedef struct Opt_NavPathInfo {
    enum Ark_Tag tag;
    NavPathInfo value;
} Opt_NavPathInfo;
typedef struct ScrollToIndexOptions {
    Opt_Ark_CustomObject extraOffset;
} ScrollToIndexOptions;
typedef struct Opt_ScrollToIndexOptions {
    enum Ark_Tag tag;
    ScrollToIndexOptions value;
} Opt_ScrollToIndexOptions;
typedef Ark_Int32 Ark_ScrollAlign;
typedef struct Opt_Ark_ScrollAlign { enum Ark_Tag tag; Ark_ScrollAlign value; } Opt_Ark_ScrollAlign;
typedef struct Literal_next_Ark_Boolean_direction_Opt_Ark_Axis {
    Ark_Boolean next;
    Opt_Ark_Axis direction;
} Literal_next_Ark_Boolean_direction_Opt_Ark_Axis;
typedef struct Opt_Literal_next_Ark_Boolean_direction_Opt_Ark_Axis {
    enum Ark_Tag tag;
    Literal_next_Ark_Boolean_direction_Opt_Ark_Axis value;
} Opt_Literal_next_Ark_Boolean_direction_Opt_Ark_Axis;
typedef struct ScrollPageOptions {
    Ark_Boolean next;
    Opt_Ark_Boolean animation;
} ScrollPageOptions;
typedef struct Opt_ScrollPageOptions {
    enum Ark_Tag tag;
    ScrollPageOptions value;
} Opt_ScrollPageOptions;
typedef struct ScrollEdgeOptions {
    Opt_Ark_Number velocity;
} ScrollEdgeOptions;
typedef struct Opt_ScrollEdgeOptions {
    enum Ark_Tag tag;
    ScrollEdgeOptions value;
} Opt_ScrollEdgeOptions;
typedef Ark_Int32 Ark_Edge;
typedef struct Opt_Ark_Edge { enum Ark_Tag tag; Ark_Edge value; } Opt_Ark_Edge;
typedef struct Literal_xOffset_Union_Ark_Number_Ark_String_yOffset_Union_Ark_Number_Ark_String_animation_Opt_Union_ScrollAnimationOptions_Ark_Boolean {
    struct Union_Ark_Number_Ark_String xOffset;
    struct Union_Ark_Number_Ark_String yOffset;
    struct Opt_Union_ScrollAnimationOptions_Ark_Boolean animation;
} Literal_xOffset_Union_Ark_Number_Ark_String_yOffset_Union_Ark_Number_Ark_String_animation_Opt_Union_ScrollAnimationOptions_Ark_Boolean;
typedef struct Opt_Literal_xOffset_Union_Ark_Number_Ark_String_yOffset_Union_Ark_Number_Ark_String_animation_Opt_Union_ScrollAnimationOptions_Ark_Boolean {
    enum Ark_Tag tag;
    Literal_xOffset_Union_Ark_Number_Ark_String_yOffset_Union_Ark_Number_Ark_String_animation_Opt_Union_ScrollAnimationOptions_Ark_Boolean value;
} Opt_Literal_xOffset_Union_Ark_Number_Ark_String_yOffset_Union_Ark_Number_Ark_String_animation_Opt_Union_ScrollAnimationOptions_Ark_Boolean;
typedef Ark_Materialized Matrix2D;
typedef struct Opt_Matrix2D {
    enum Ark_Tag tag;
    Matrix2D value;
} Opt_Matrix2D;
typedef struct ImageData {
    struct Uint8ClampedArray data;
    Ark_Number height;
    Ark_Number width;
} ImageData;
typedef struct Opt_ImageData {
    enum Ark_Tag tag;
    ImageData value;
} Opt_ImageData;
typedef struct Union_Ark_String_Ark_Undefined {
    Ark_Int32 selector;
    union {
        Ark_String value0;
        struct Ark_Undefined value1;
    };
} Union_Ark_String_Ark_Undefined;
typedef struct Opt_Union_Ark_String_Ark_Undefined {
    enum Ark_Tag tag;
    Union_Ark_String_Ark_Undefined value;
} Opt_Union_Ark_String_Ark_Undefined;
typedef Ark_Materialized Path2D;
typedef struct Opt_Path2D {
    enum Ark_Tag tag;
    Path2D value;
} Opt_Path2D;
typedef struct Union_Ark_String_Ark_String {
    Ark_Int32 selector;
    union {
        struct Ark_String value0;
        struct Ark_String value1;
    };
} Union_Ark_String_Ark_String;
typedef struct Opt_Union_Ark_String_Ark_String {
    enum Ark_Tag tag;
    Union_Ark_String_Ark_String value;
} Opt_Union_Ark_String_Ark_String;
typedef struct Union_ImageBitmap_Ark_CustomObject {
    Ark_Int32 selector;
    union {
        ImageBitmap value0;
        Ark_CustomObject value1;
    };
} Union_ImageBitmap_Ark_CustomObject;
typedef struct Opt_Union_ImageBitmap_Ark_CustomObject {
    enum Ark_Tag tag;
    Union_ImageBitmap_Ark_CustomObject value;
} Opt_Union_ImageBitmap_Ark_CustomObject;
typedef struct RenderingContextSettings {
    Opt_Ark_Boolean antialias;
} RenderingContextSettings;
typedef struct Opt_RenderingContextSettings {
    enum Ark_Tag tag;
    RenderingContextSettings value;
} Opt_RenderingContextSettings;
typedef struct UIGestureEvent {
} UIGestureEvent;
typedef struct Opt_UIGestureEvent {
    enum Ark_Tag tag;
    UIGestureEvent value;
} Opt_UIGestureEvent;
typedef struct Literal_fingers_Opt_Ark_Number_direction_Opt_Ark_PanDirection_distance_Opt_Ark_Number {
    Opt_Ark_Number fingers;
    Opt_Ark_PanDirection direction;
    Opt_Ark_Number distance;
} Literal_fingers_Opt_Ark_Number_direction_Opt_Ark_PanDirection_distance_Opt_Ark_Number;
typedef struct Opt_Literal_fingers_Opt_Ark_Number_direction_Opt_Ark_PanDirection_distance_Opt_Ark_Number {
    enum Ark_Tag tag;
    Literal_fingers_Opt_Ark_Number_direction_Opt_Ark_PanDirection_distance_Opt_Ark_Number value;
} Opt_Literal_fingers_Opt_Ark_Number_direction_Opt_Ark_PanDirection_distance_Opt_Ark_Number;
typedef Ark_Materialized LinearIndicatorController;
typedef struct Opt_LinearIndicatorController {
    enum Ark_Tag tag;
    LinearIndicatorController value;
} Opt_LinearIndicatorController;
typedef struct UIExtensionOptions {
    Opt_Ark_Boolean isTransferringCaller;
    Opt_Ark_CustomObject placeholder;
    Opt_Ark_DpiFollowStrategy dpiFollowStrategy;
} UIExtensionOptions;
typedef struct Opt_UIExtensionOptions {
    enum Ark_Tag tag;
    UIExtensionOptions value;
} Opt_UIExtensionOptions;
typedef struct WaterFlowOptions {
    struct Opt_Union_Ark_Function_Ark_Undefined footer;
    Opt_Scroller scroller;
    Opt_WaterFlowSections sections;
    Opt_Ark_WaterFlowLayoutMode layoutMode;
} WaterFlowOptions;
typedef struct Opt_WaterFlowOptions {
    enum Ark_Tag tag;
    WaterFlowOptions value;
} Opt_WaterFlowOptions;
typedef struct WindowAnimationTarget {
    Ark_String bundleName;
    Ark_String abilityName;
    struct RRect windowBounds;
    Ark_Number missionId;
} WindowAnimationTarget;
typedef struct Opt_WindowAnimationTarget {
    enum Ark_Tag tag;
    WindowAnimationTarget value;
} Opt_WindowAnimationTarget;
typedef struct Union_DividerStyle_Ark_Undefined {
    Ark_Int32 selector;
    union {
        struct DividerStyle value0;
        struct Ark_Undefined value1;
    };
} Union_DividerStyle_Ark_Undefined;
typedef struct Opt_Union_DividerStyle_Ark_Undefined {
    enum Ark_Tag tag;
    Union_DividerStyle_Ark_Undefined value;
} Opt_Union_DividerStyle_Ark_Undefined;
typedef Ark_Int32 Ark_SideBarPosition;
typedef struct Opt_Ark_SideBarPosition { enum Ark_Tag tag; Ark_SideBarPosition value; } Opt_Ark_SideBarPosition;
typedef struct ButtonStyle {
    Opt_Ark_Number left;
    Opt_Ark_Number top;
    Opt_Ark_Number width;
    Opt_Ark_Number height;
    struct Opt_Literal_shown_Union_Ark_String_Ark_CustomObject_Ark_Resource_hidden_Union_Ark_String_Ark_CustomObject_Ark_Resource_switching_Opt_Union_Ark_String_Ark_CustomObject_Ark_Resource icons;
} ButtonStyle;
typedef struct Opt_ButtonStyle {
    enum Ark_Tag tag;
    ButtonStyle value;
} Opt_ButtonStyle;
typedef Ark_Int32 Ark_SideBarContainerType;
typedef struct Opt_Ark_SideBarContainerType { enum Ark_Tag tag; Ark_SideBarContainerType value; } Opt_Ark_SideBarContainerType;
typedef struct XComponentOptions {
    Ark_XComponentType type;
    XComponentController controller;
    struct Opt_ImageAIOptions imageAIOptions;
} XComponentOptions;
typedef struct Opt_XComponentOptions {
    enum Ark_Tag tag;
    XComponentOptions value;
} Opt_XComponentOptions;
typedef struct Literal_id_Ark_String_type_Ark_XComponentType_libraryname_Opt_Ark_String_controller_Opt_XComponentController {
    Ark_String id;
    Ark_XComponentType type;
    Opt_Ark_String libraryname;
    Opt_XComponentController controller;
} Literal_id_Ark_String_type_Ark_XComponentType_libraryname_Opt_Ark_String_controller_Opt_XComponentController;
typedef struct Opt_Literal_id_Ark_String_type_Ark_XComponentType_libraryname_Opt_Ark_String_controller_Opt_XComponentController {
    enum Ark_Tag tag;
    Literal_id_Ark_String_type_Ark_XComponentType_libraryname_Opt_Ark_String_controller_Opt_XComponentController value;
} Opt_Literal_id_Ark_String_type_Ark_XComponentType_libraryname_Opt_Ark_String_controller_Opt_XComponentController;
typedef struct Literal_id_Ark_String_type_Ark_String_libraryname_Opt_Ark_String_controller_Opt_XComponentController {
    Ark_String id;
    Ark_String type;
    Opt_Ark_String libraryname;
    Opt_XComponentController controller;
} Literal_id_Ark_String_type_Ark_String_libraryname_Opt_Ark_String_controller_Opt_XComponentController;
typedef struct Opt_Literal_id_Ark_String_type_Ark_String_libraryname_Opt_Ark_String_controller_Opt_XComponentController {
    enum Ark_Tag tag;
    Literal_id_Ark_String_type_Ark_String_libraryname_Opt_Ark_String_controller_Opt_XComponentController value;
} Opt_Literal_id_Ark_String_type_Ark_String_libraryname_Opt_Ark_String_controller_Opt_XComponentController;
typedef Ark_Int32 Ark_WebKeyboardAvoidMode;
typedef struct Opt_Ark_WebKeyboardAvoidMode { enum Ark_Tag tag; Ark_WebKeyboardAvoidMode value; } Opt_Ark_WebKeyboardAvoidMode;
typedef struct ExpandedMenuItemOptions {
    struct Union_Ark_String_Ark_Resource content;
    struct Opt_Union_Ark_String_Ark_Resource startIcon;
    struct Ark_Function action;
} ExpandedMenuItemOptions;
typedef struct Opt_ExpandedMenuItemOptions {
    enum Ark_Tag tag;
    ExpandedMenuItemOptions value;
} Opt_ExpandedMenuItemOptions;
typedef struct Array_ExpandedMenuItemOptions {
    struct ExpandedMenuItemOptions* array;
    Ark_Int32 length;
} Array_ExpandedMenuItemOptions;
typedef struct Opt_Array_ExpandedMenuItemOptions {
    enum Ark_Tag tag;
    Array_ExpandedMenuItemOptions value;
} Opt_Array_ExpandedMenuItemOptions;
typedef struct NativeMediaPlayerConfig {
    Ark_Boolean enable;
    Ark_Boolean shouldOverlay;
} NativeMediaPlayerConfig;
typedef struct Opt_NativeMediaPlayerConfig {
    enum Ark_Tag tag;
    NativeMediaPlayerConfig value;
} Opt_NativeMediaPlayerConfig;
typedef Ark_Int32 Ark_WebLayoutMode;
typedef struct Opt_Ark_WebLayoutMode { enum Ark_Tag tag; Ark_WebLayoutMode value; } Opt_Ark_WebLayoutMode;
typedef struct Array_ScriptItem {
    struct ScriptItem* array;
    Ark_Int32 length;
} Array_ScriptItem;
typedef struct Opt_Array_ScriptItem {
    enum Ark_Tag tag;
    Array_ScriptItem value;
} Opt_Array_ScriptItem;
typedef struct ScriptItem {
    Ark_String script;
    struct Array_Ark_String scriptRules;
} ScriptItem;
typedef struct Opt_ScriptItem {
    enum Ark_Tag tag;
    ScriptItem value;
} Opt_ScriptItem;
typedef Ark_Int32 Ark_OverScrollMode;
typedef struct Opt_Ark_OverScrollMode { enum Ark_Tag tag; Ark_OverScrollMode value; } Opt_Ark_OverScrollMode;
typedef struct WebMediaOptions {
    Opt_Ark_Number resumeInterval;
    Opt_Ark_Boolean audioExclusive;
} WebMediaOptions;
typedef struct Opt_WebMediaOptions {
    enum Ark_Tag tag;
    WebMediaOptions value;
} Opt_WebMediaOptions;
typedef Ark_Int32 Ark_WebDarkMode;
typedef struct Opt_Ark_WebDarkMode { enum Ark_Tag tag; Ark_WebDarkMode value; } Opt_Ark_WebDarkMode;
typedef Ark_Int32 Ark_CacheMode;
typedef struct Opt_Ark_CacheMode { enum Ark_Tag tag; Ark_CacheMode value; } Opt_Ark_CacheMode;
typedef struct JavaScriptProxy {
    Ark_CustomObject object;
    Ark_String name;
    struct Array_Ark_String methodList;
    struct Union_WebController_Ark_CustomObject controller;
    struct Opt_Array_Ark_String asyncMethodList;
    Opt_Ark_String permission;
} JavaScriptProxy;
typedef struct Opt_JavaScriptProxy {
    enum Ark_Tag tag;
    JavaScriptProxy value;
} Opt_JavaScriptProxy;
typedef Ark_Int32 Ark_MixedMode;
typedef struct Opt_Ark_MixedMode { enum Ark_Tag tag; Ark_MixedMode value; } Opt_Ark_MixedMode;
typedef struct WebOptions {
    struct Union_Ark_String_Ark_Resource src;
    struct Union_WebController_Ark_CustomObject controller;
    Opt_Ark_RenderMode renderMode;
    Opt_Ark_Boolean incognitoMode;
    Opt_Ark_String sharedRenderProcessToken;
} WebOptions;
typedef struct Opt_WebOptions {
    enum Ark_Tag tag;
    WebOptions value;
} Opt_WebOptions;
typedef struct VideoOptions {
    struct Opt_Union_Ark_String_Ark_Resource src;
    struct Opt_Union_Ark_Number_Ark_String_Ark_PlaybackSpeed currentProgressRate;
    struct Opt_Union_Ark_String_Ark_CustomObject_Ark_Resource previewUri;
    Opt_VideoController controller;
    struct Opt_ImageAIOptions imageAIOptions;
} VideoOptions;
typedef struct Opt_VideoOptions {
    enum Ark_Tag tag;
    VideoOptions value;
} Opt_VideoOptions;
typedef struct SwitchStyle {
    struct Opt_Union_Ark_Number_Ark_Resource pointRadius;
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource unselectedColor;
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource pointColor;
    struct Opt_Union_Ark_Number_Ark_Resource trackBorderRadius;
} SwitchStyle;
typedef struct Opt_SwitchStyle {
    enum Ark_Tag tag;
    SwitchStyle value;
} Opt_SwitchStyle;
typedef struct Literal_type_Ark_ToggleType_isOn_Opt_Ark_Boolean {
    Ark_ToggleType type;
    Opt_Ark_Boolean isOn;
} Literal_type_Ark_ToggleType_isOn_Opt_Ark_Boolean;
typedef struct Opt_Literal_type_Ark_ToggleType_isOn_Opt_Ark_Boolean {
    enum Ark_Tag tag;
    Literal_type_Ark_ToggleType_isOn_Opt_Ark_Boolean value;
} Opt_Literal_type_Ark_ToggleType_isOn_Opt_Ark_Boolean;
typedef struct TimePickerOptions {
    Opt_Ark_CustomObject selected;
    Opt_Ark_TimePickerFormat format;
} TimePickerOptions;
typedef struct Opt_TimePickerOptions {
    enum Ark_Tag tag;
    TimePickerOptions value;
} Opt_TimePickerOptions;
typedef struct TextTimerOptions {
    Opt_Ark_Boolean isCountDown;
    Opt_Ark_Number count;
    Opt_TextTimerController controller;
} TextTimerOptions;
typedef struct Opt_TextTimerOptions {
    enum Ark_Tag tag;
    TextTimerOptions value;
} Opt_TextTimerOptions;
typedef struct Union_DividerOptions_Ark_Undefined {
    Ark_Int32 selector;
    union {
        struct DividerOptions value0;
        struct Ark_Undefined value1;
    };
} Union_DividerOptions_Ark_Undefined;
typedef struct Opt_Union_DividerOptions_Ark_Undefined {
    enum Ark_Tag tag;
    Union_DividerOptions_Ark_Undefined value;
} Opt_Union_DividerOptions_Ark_Undefined;
typedef struct TextCascadePickerRangeContent {
    struct Union_Ark_String_Ark_Resource text;
    struct Opt_Array_TextCascadePickerRangeContent children;
} TextCascadePickerRangeContent;
typedef struct Opt_TextCascadePickerRangeContent {
    enum Ark_Tag tag;
    TextCascadePickerRangeContent value;
} Opt_TextCascadePickerRangeContent;
typedef struct TextPickerRangeContent {
    struct Union_Ark_String_Ark_Resource icon;
    struct Opt_Union_Ark_String_Ark_Resource text;
} TextPickerRangeContent;
typedef struct Opt_TextPickerRangeContent {
    enum Ark_Tag tag;
    TextPickerRangeContent value;
} Opt_TextPickerRangeContent;
typedef struct TextPickerOptions {
    struct Union_Array_Ark_String_Array_Array_Ark_String_Ark_Resource_Array_TextPickerRangeContent_Array_TextCascadePickerRangeContent range;
    struct Opt_Union_Ark_String_Array_Ark_String value;
    struct Opt_Union_Ark_Number_Array_Ark_Number selected;
} TextPickerOptions;
typedef struct Opt_TextPickerOptions {
    enum Ark_Tag tag;
    TextPickerOptions value;
} Opt_TextPickerOptions;
typedef struct Literal_style_Opt_Ark_CancelButtonStyle_icon_Opt_IconOptions {
    Opt_Ark_CancelButtonStyle style;
    struct Opt_IconOptions icon;
} Literal_style_Opt_Ark_CancelButtonStyle_icon_Opt_IconOptions;
typedef struct Opt_Literal_style_Opt_Ark_CancelButtonStyle_icon_Opt_IconOptions {
    enum Ark_Tag tag;
    Literal_style_Opt_Ark_CancelButtonStyle_icon_Opt_IconOptions value;
} Opt_Literal_style_Opt_Ark_CancelButtonStyle_icon_Opt_IconOptions;
typedef struct Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_UnderlineColor_Ark_Undefined {
    Ark_Int32 selector;
    union {
        struct Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource value0;
        struct UnderlineColor value1;
        Ark_Undefined value2;
    };
} Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_UnderlineColor_Ark_Undefined;
typedef struct Opt_Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_UnderlineColor_Ark_Undefined {
    enum Ark_Tag tag;
    Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_UnderlineColor_Ark_Undefined value;
} Opt_Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_UnderlineColor_Ark_Undefined;
typedef struct Union_Union_Ark_String_Ark_Resource_Ark_Undefined {
    Ark_Int32 selector;
    union {
        struct Union_Ark_String_Ark_Resource value0;
        Ark_Undefined value1;
    };
} Union_Union_Ark_String_Ark_Resource_Ark_Undefined;
typedef struct Opt_Union_Union_Ark_String_Ark_Resource_Ark_Undefined {
    enum Ark_Tag tag;
    Union_Union_Ark_String_Ark_Resource_Ark_Undefined value;
} Opt_Union_Union_Ark_String_Ark_Resource_Ark_Undefined;
typedef struct PasswordIcon {
    struct Opt_Union_Ark_String_Ark_Resource onIconSrc;
    struct Opt_Union_Ark_String_Ark_Resource offIconSrc;
} PasswordIcon;
typedef struct Opt_PasswordIcon {
    enum Ark_Tag tag;
    PasswordIcon value;
} Opt_PasswordIcon;
typedef struct Union_Ark_TextInputStyle_Ark_TextContentStyle {
    Ark_Int32 selector;
    union {
        Ark_TextInputStyle value0;
        Ark_TextContentStyle value1;
    };
} Union_Ark_TextInputStyle_Ark_TextContentStyle;
typedef struct Opt_Union_Ark_TextInputStyle_Ark_TextContentStyle {
    enum Ark_Tag tag;
    Union_Ark_TextInputStyle_Ark_TextContentStyle value;
} Opt_Union_Ark_TextInputStyle_Ark_TextContentStyle;
typedef Ark_Int32 Ark_InputType;
typedef struct Opt_Ark_InputType { enum Ark_Tag tag; Ark_InputType value; } Opt_Ark_InputType;
typedef struct TextInputOptions {
    struct Opt_Union_Ark_String_Ark_Resource placeholder;
    struct Opt_Union_Ark_String_Ark_Resource text;
    Opt_TextInputController controller;
} TextInputOptions;
typedef struct Opt_TextInputOptions {
    enum Ark_Tag tag;
    TextInputOptions value;
} Opt_TextInputOptions;
typedef struct Literal_timeZoneOffset_Opt_Ark_Number_controller_Opt_TextClockController {
    Opt_Ark_Number timeZoneOffset;
    Opt_TextClockController controller;
} Literal_timeZoneOffset_Opt_Ark_Number_controller_Opt_TextClockController;
typedef struct Opt_Literal_timeZoneOffset_Opt_Ark_Number_controller_Opt_TextClockController {
    enum Ark_Tag tag;
    Literal_timeZoneOffset_Opt_Ark_Number_controller_Opt_TextClockController value;
} Opt_Literal_timeZoneOffset_Opt_Ark_Number_controller_Opt_TextClockController;
typedef Ark_Int32 Ark_ContentType;
typedef struct Opt_Ark_ContentType { enum Ark_Tag tag; Ark_ContentType value; } Opt_Ark_ContentType;
typedef Ark_Int32 Ark_TextAreaType;
typedef struct Opt_Ark_TextAreaType { enum Ark_Tag tag; Ark_TextAreaType value; } Opt_Ark_TextAreaType;
typedef struct InputCounterOptions {
    Opt_Ark_Number thresholdPercentage;
    Opt_Ark_Boolean highlightBorder;
} InputCounterOptions;
typedef struct Opt_InputCounterOptions {
    enum Ark_Tag tag;
    InputCounterOptions value;
} Opt_InputCounterOptions;
typedef struct TextAreaOptions {
    struct Opt_Union_Ark_String_Ark_Resource placeholder;
    struct Opt_Union_Ark_String_Ark_Resource text;
    Opt_TextAreaController controller;
} TextAreaOptions;
typedef struct Opt_TextAreaOptions {
    enum Ark_Tag tag;
    TextAreaOptions value;
} Opt_TextAreaOptions;
typedef Ark_Int32 Ark_TextSelectableMode;
typedef struct Opt_Ark_TextSelectableMode { enum Ark_Tag tag; Ark_TextSelectableMode value; } Opt_Ark_TextSelectableMode;
typedef Ark_Int32 Ark_TextResponseType;
typedef struct Opt_Ark_TextResponseType { enum Ark_Tag tag; Ark_TextResponseType value; } Opt_Ark_TextResponseType;
typedef Ark_Int32 Ark_TextSpanType;
typedef struct Opt_Ark_TextSpanType { enum Ark_Tag tag; Ark_TextSpanType value; } Opt_Ark_TextSpanType;
typedef Ark_Int32 Ark_EllipsisMode;
typedef struct Opt_Ark_EllipsisMode { enum Ark_Tag tag; Ark_EllipsisMode value; } Opt_Ark_EllipsisMode;
typedef struct Literal_overflow_Ark_TextOverflow {
    Ark_TextOverflow overflow;
} Literal_overflow_Ark_TextOverflow;
typedef struct Opt_Literal_overflow_Ark_TextOverflow {
    enum Ark_Tag tag;
    Literal_overflow_Ark_TextOverflow value;
} Opt_Literal_overflow_Ark_TextOverflow;
typedef struct TextOptions {
    TextController controller;
} TextOptions;
typedef struct Opt_TextOptions {
    enum Ark_Tag tag;
    TextOptions value;
} Opt_TextOptions;
typedef struct Union_SubTabBarStyle_BottomTabBarStyle {
    Ark_Int32 selector;
    union {
        struct SubTabBarStyle value0;
        struct BottomTabBarStyle value1;
    };
} Union_SubTabBarStyle_BottomTabBarStyle;
typedef struct Opt_Union_SubTabBarStyle_BottomTabBarStyle {
    enum Ark_Tag tag;
    Union_SubTabBarStyle_BottomTabBarStyle value;
} Opt_Union_SubTabBarStyle_BottomTabBarStyle;
typedef struct Union_Ark_String_Ark_Resource_Union_Ark_Function_Ark_Undefined_Literal_icon_Opt_Union_Ark_String_Ark_Resource_text_Opt_Union_Ark_String_Ark_Resource {
    Ark_Int32 selector;
    union {
        Ark_String value0;
        Ark_Resource value1;
        struct Union_Ark_Function_Ark_Undefined value2;
        struct Literal_icon_Opt_Union_Ark_String_Ark_Resource_text_Opt_Union_Ark_String_Ark_Resource value3;
    };
} Union_Ark_String_Ark_Resource_Union_Ark_Function_Ark_Undefined_Literal_icon_Opt_Union_Ark_String_Ark_Resource_text_Opt_Union_Ark_String_Ark_Resource;
typedef struct Opt_Union_Ark_String_Ark_Resource_Union_Ark_Function_Ark_Undefined_Literal_icon_Opt_Union_Ark_String_Ark_Resource_text_Opt_Union_Ark_String_Ark_Resource {
    enum Ark_Tag tag;
    Union_Ark_String_Ark_Resource_Union_Ark_Function_Ark_Undefined_Literal_icon_Opt_Union_Ark_String_Ark_Resource_text_Opt_Union_Ark_String_Ark_Resource value;
} Opt_Union_Ark_String_Ark_Resource_Union_Ark_Function_Ark_Undefined_Literal_icon_Opt_Union_Ark_String_Ark_Resource_text_Opt_Union_Ark_String_Ark_Resource;
typedef struct BarGridColumnOptions {
    Opt_Ark_Number sm;
    Opt_Ark_Number md;
    Opt_Ark_Number lg;
    Opt_Ark_Length margin;
    Opt_Ark_Length gutter;
} BarGridColumnOptions;
typedef struct Opt_BarGridColumnOptions {
    enum Ark_Tag tag;
    BarGridColumnOptions value;
} Opt_BarGridColumnOptions;
typedef struct ScrollableBarModeOptions {
    Opt_Ark_Length margin;
    Opt_Ark_LayoutStyle nonScrollableLayoutStyle;
} ScrollableBarModeOptions;
typedef struct Opt_ScrollableBarModeOptions {
    enum Ark_Tag tag;
    ScrollableBarModeOptions value;
} Opt_ScrollableBarModeOptions;
typedef Ark_Int32 Ark_BarMode;
typedef struct Opt_Ark_BarMode { enum Ark_Tag tag; Ark_BarMode value; } Opt_Ark_BarMode;
typedef struct Literal_barPosition_Opt_Ark_BarPosition_index_Opt_Ark_Number_controller_Opt_TabsController {
    Opt_Ark_BarPosition barPosition;
    Opt_Ark_Number index;
    Opt_TabsController controller;
} Literal_barPosition_Opt_Ark_BarPosition_index_Opt_Ark_Number_controller_Opt_TabsController;
typedef struct Opt_Literal_barPosition_Opt_Ark_BarPosition_index_Opt_Ark_Number_controller_Opt_TabsController {
    enum Ark_Tag tag;
    Literal_barPosition_Opt_Ark_BarPosition_index_Opt_Ark_Number_controller_Opt_TabsController value;
} Opt_Literal_barPosition_Opt_Ark_BarPosition_index_Opt_Ark_Number_controller_Opt_TabsController;
typedef struct SymbolEffect {
} SymbolEffect;
typedef struct Opt_SymbolEffect {
    enum Ark_Tag tag;
    SymbolEffect value;
} Opt_SymbolEffect;
typedef struct SwiperContentAnimatedTransition {
    Opt_Ark_Number timeout;
    struct Ark_Function transition;
} SwiperContentAnimatedTransition;
typedef struct Opt_SwiperContentAnimatedTransition {
    enum Ark_Tag tag;
    SwiperContentAnimatedTransition value;
} Opt_SwiperContentAnimatedTransition;
typedef Ark_Int32 Ark_SwiperNestedScrollMode;
typedef struct Opt_Ark_SwiperNestedScrollMode { enum Ark_Tag tag; Ark_SwiperNestedScrollMode value; } Opt_Ark_SwiperNestedScrollMode;
typedef struct Union_Ark_Number_Ark_String_Literal_minSize_Union_Ark_String_Ark_Number {
    Ark_Int32 selector;
    union {
        Ark_Number value0;
        Ark_String value1;
        struct Literal_minSize_Union_Ark_String_Ark_Number value2;
    };
} Union_Ark_Number_Ark_String_Literal_minSize_Union_Ark_String_Ark_Number;
typedef struct Opt_Union_Ark_Number_Ark_String_Literal_minSize_Union_Ark_String_Ark_Number {
    enum Ark_Tag tag;
    Union_Ark_Number_Ark_String_Literal_minSize_Union_Ark_String_Ark_Number value;
} Opt_Union_Ark_Number_Ark_String_Literal_minSize_Union_Ark_String_Ark_Number;
typedef Ark_Int32 Ark_SwiperDisplayMode;
typedef struct Opt_Ark_SwiperDisplayMode { enum Ark_Tag tag; Ark_SwiperDisplayMode value; } Opt_Ark_SwiperDisplayMode;
typedef struct Union_ArrowStyle_Ark_Boolean {
    Ark_Int32 selector;
    union {
        struct ArrowStyle value0;
        Ark_Boolean value1;
    };
} Union_ArrowStyle_Ark_Boolean;
typedef struct Opt_Union_ArrowStyle_Ark_Boolean {
    enum Ark_Tag tag;
    Union_ArrowStyle_Ark_Boolean value;
} Opt_Union_ArrowStyle_Ark_Boolean;
typedef struct Union_DotIndicator_DigitIndicator_Ark_Boolean {
    Ark_Int32 selector;
    union {
        struct DotIndicator value0;
        struct DigitIndicator value1;
        Ark_Boolean value2;
    };
} Union_DotIndicator_DigitIndicator_Ark_Boolean;
typedef struct Opt_Union_DotIndicator_DigitIndicator_Ark_Boolean {
    enum Ark_Tag tag;
    Union_DotIndicator_DigitIndicator_Ark_Boolean value;
} Opt_Union_DotIndicator_DigitIndicator_Ark_Boolean;
typedef Ark_Materialized SwiperController;
typedef struct Opt_SwiperController {
    enum Ark_Tag tag;
    SwiperController value;
} Opt_SwiperController;
typedef Ark_Int32 Ark_ItemState;
typedef struct Opt_Ark_ItemState { enum Ark_Tag tag; Ark_ItemState value; } Opt_Ark_ItemState;
typedef struct Literal_index_Opt_Ark_Number {
    Opt_Ark_Number index;
} Literal_index_Opt_Ark_Number;
typedef struct Opt_Literal_index_Opt_Ark_Number {
    enum Ark_Tag tag;
    Literal_index_Opt_Ark_Number value;
} Opt_Literal_index_Opt_Ark_Number;
typedef struct Literal_alignContent_Opt_Ark_Alignment {
    Opt_Ark_Alignment alignContent;
} Literal_alignContent_Opt_Ark_Alignment;
typedef struct Opt_Literal_alignContent_Opt_Ark_Alignment {
    enum Ark_Tag tag;
    Literal_alignContent_Opt_Ark_Alignment value;
} Opt_Literal_alignContent_Opt_Ark_Alignment;
typedef Ark_Int32 Ark_TextCase;
typedef struct Opt_Ark_TextCase { enum Ark_Tag tag; Ark_TextCase value; } Opt_Ark_TextCase;
typedef struct SlideRange {
    Opt_Ark_Number from;
    Opt_Ark_Number to;
} SlideRange;
typedef struct Opt_SlideRange {
    enum Ark_Tag tag;
    SlideRange value;
} Opt_SlideRange;
typedef Ark_Int32 Ark_SliderInteraction;
typedef struct Opt_Ark_SliderInteraction { enum Ark_Tag tag; Ark_SliderInteraction value; } Opt_Ark_SliderInteraction;
typedef struct SliderBlockStyle {
    Ark_SliderBlockType type;
    struct Opt_Union_Ark_String_Ark_Resource image;
    struct Opt_Union_CircleAttribute_EllipseAttribute_PathAttribute_RectAttribute shape;
} SliderBlockStyle;
typedef struct Opt_SliderBlockStyle {
    enum Ark_Tag tag;
    SliderBlockStyle value;
} Opt_SliderBlockStyle;
typedef struct SliderOptions {
    Opt_Ark_Number value;
    Opt_Ark_Number min;
    Opt_Ark_Number max;
    Opt_Ark_Number step;
    Opt_Ark_SliderStyle style;
    Opt_Ark_Axis direction;
    Opt_Ark_Boolean reverse;
} SliderOptions;
typedef struct Opt_SliderOptions {
    enum Ark_Tag tag;
    SliderOptions value;
} Opt_SliderOptions;
typedef struct Literal_x_Opt_Union_Ark_Number_Ark_String_y_Opt_Union_Ark_Number_Ark_String_width_Opt_Union_Ark_Number_Ark_String_height_Opt_Union_Ark_Number_Ark_String {
    struct Opt_Union_Ark_Number_Ark_String x;
    struct Opt_Union_Ark_Number_Ark_String y;
    struct Opt_Union_Ark_Number_Ark_String width;
    struct Opt_Union_Ark_Number_Ark_String height;
} Literal_x_Opt_Union_Ark_Number_Ark_String_y_Opt_Union_Ark_Number_Ark_String_width_Opt_Union_Ark_Number_Ark_String_height_Opt_Union_Ark_Number_Ark_String;
typedef struct Opt_Literal_x_Opt_Union_Ark_Number_Ark_String_y_Opt_Union_Ark_Number_Ark_String_width_Opt_Union_Ark_Number_Ark_String_height_Opt_Union_Ark_Number_Ark_String {
    enum Ark_Tag tag;
    Literal_x_Opt_Union_Ark_Number_Ark_String_y_Opt_Union_Ark_Number_Ark_String_width_Opt_Union_Ark_Number_Ark_String_height_Opt_Union_Ark_Number_Ark_String value;
} Opt_Literal_x_Opt_Union_Ark_Number_Ark_String_y_Opt_Union_Ark_Number_Ark_String_width_Opt_Union_Ark_Number_Ark_String_height_Opt_Union_Ark_Number_Ark_String;
typedef struct Union_Opt_DividerOptions_Ark_Undefined {
    Ark_Int32 selector;
    union {
        struct Opt_DividerOptions value0;
        struct Ark_Undefined value1;
    };
} Union_Opt_DividerOptions_Ark_Undefined;
typedef struct Opt_Union_Opt_DividerOptions_Ark_Undefined {
    enum Ark_Tag tag;
    Union_Opt_DividerOptions_Ark_Undefined value;
} Opt_Union_Opt_DividerOptions_Ark_Undefined;
typedef struct Union_Ark_Length_Ark_OptionWidthMode {
    Ark_Int32 selector;
    union {
        Ark_Length value0;
        Ark_OptionWidthMode value1;
    };
} Union_Ark_Length_Ark_OptionWidthMode;
typedef struct Opt_Union_Ark_Length_Ark_OptionWidthMode {
    enum Ark_Tag tag;
    Union_Ark_Length_Ark_OptionWidthMode value;
} Opt_Union_Ark_Length_Ark_OptionWidthMode;
typedef Ark_Int32 Ark_MenuAlignType;
typedef struct Opt_Ark_MenuAlignType { enum Ark_Tag tag; Ark_MenuAlignType value; } Opt_Ark_MenuAlignType;
typedef Ark_Int32 Ark_ArrowPosition;
typedef struct Opt_Ark_ArrowPosition { enum Ark_Tag tag; Ark_ArrowPosition value; } Opt_Ark_ArrowPosition;
typedef struct SelectOption {
    struct Union_Ark_String_Ark_Resource value;
    struct Opt_Union_Ark_String_Ark_Resource icon;
    Opt_Ark_CustomObject symbolIcon;
} SelectOption;
typedef struct Opt_SelectOption {
    enum Ark_Tag tag;
    SelectOption value;
} Opt_SelectOption;
typedef struct Array_SelectOption {
    struct SelectOption* array;
    Ark_Int32 length;
} Array_SelectOption;
typedef struct Opt_Array_SelectOption {
    enum Ark_Tag tag;
    Array_SelectOption value;
} Opt_Array_SelectOption;
typedef Ark_Int32 Ark_SearchType;
typedef struct Opt_Ark_SearchType { enum Ark_Tag tag; Ark_SearchType value; } Opt_Ark_SearchType;
typedef struct TextDecorationOptions {
    Ark_TextDecorationType type;
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource color;
    Opt_Ark_TextDecorationStyle style;
} TextDecorationOptions;
typedef struct Opt_TextDecorationOptions {
    enum Ark_Tag tag;
    TextDecorationOptions value;
} Opt_TextDecorationOptions;
typedef struct CaretStyle {
    Opt_Ark_Length width;
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource color;
} CaretStyle;
typedef struct Opt_CaretStyle {
    enum Ark_Tag tag;
    CaretStyle value;
} Opt_CaretStyle;
typedef struct SearchButtonOptions {
    Opt_Ark_Length fontSize;
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource fontColor;
} SearchButtonOptions;
typedef struct Opt_SearchButtonOptions {
    enum Ark_Tag tag;
    SearchButtonOptions value;
} Opt_SearchButtonOptions;
typedef struct Literal_value_Opt_Ark_String_placeholder_Opt_Union_Ark_String_Ark_Resource_icon_Opt_Ark_String_controller_Opt_SearchController {
    Opt_Ark_String value;
    struct Opt_Union_Ark_String_Ark_Resource placeholder;
    Opt_Ark_String icon;
    Opt_SearchController controller;
} Literal_value_Opt_Ark_String_placeholder_Opt_Union_Ark_String_Ark_Resource_icon_Opt_Ark_String_controller_Opt_SearchController;
typedef struct Opt_Literal_value_Opt_Ark_String_placeholder_Opt_Union_Ark_String_Ark_Resource_icon_Opt_Ark_String_controller_Opt_SearchController {
    enum Ark_Tag tag;
    Literal_value_Opt_Ark_String_placeholder_Opt_Union_Ark_String_Ark_Resource_icon_Opt_Ark_String_controller_Opt_SearchController value;
} Opt_Literal_value_Opt_Ark_String_placeholder_Opt_Union_Ark_String_Ark_Resource_icon_Opt_Ark_String_controller_Opt_SearchController;
typedef struct ScrollBarOptions {
    Scroller scroller;
    Opt_Ark_ScrollBarDirection direction;
    Opt_Ark_BarState state;
} ScrollBarOptions;
typedef struct Opt_ScrollBarOptions {
    enum Ark_Tag tag;
    ScrollBarOptions value;
} Opt_ScrollBarOptions;
typedef struct OffsetOptions {
    Opt_Ark_Length xOffset;
    Opt_Ark_Length yOffset;
} OffsetOptions;
typedef struct Opt_OffsetOptions {
    enum Ark_Tag tag;
    OffsetOptions value;
} Opt_OffsetOptions;
typedef struct ScrollSnapOptions {
    Ark_ScrollSnapAlign snapAlign;
    struct Opt_Union_Ark_Length_Array_Ark_Length snapPagination;
    Opt_Ark_Boolean enableSnapToStart;
    Opt_Ark_Boolean enableSnapToEnd;
} ScrollSnapOptions;
typedef struct Opt_ScrollSnapOptions {
    enum Ark_Tag tag;
    ScrollSnapOptions value;
} Opt_ScrollSnapOptions;
typedef struct Union_Ark_Color_Ark_Number_Ark_String {
    Ark_Int32 selector;
    union {
        Ark_Color value0;
        Ark_Number value1;
        Ark_String value2;
    };
} Union_Ark_Color_Ark_Number_Ark_String;
typedef struct Opt_Union_Ark_Color_Ark_Number_Ark_String {
    enum Ark_Tag tag;
    Union_Ark_Color_Ark_Number_Ark_String value;
} Opt_Union_Ark_Color_Ark_Number_Ark_String;
typedef Ark_Int32 Ark_ScrollDirection;
typedef struct Opt_Ark_ScrollDirection { enum Ark_Tag tag; Ark_ScrollDirection value; } Opt_Ark_ScrollDirection;
typedef struct SaveButtonOptions {
    Opt_Ark_SaveIconStyle icon;
    Opt_Ark_SaveDescription text;
    Opt_Ark_ButtonType buttonType;
} SaveButtonOptions;
typedef struct Opt_SaveButtonOptions {
    enum Ark_Tag tag;
    SaveButtonOptions value;
} Opt_SaveButtonOptions;
typedef struct Literal_space_Opt_Union_Ark_String_Ark_Number {
    struct Opt_Union_Ark_String_Ark_Number space;
} Literal_space_Opt_Union_Ark_String_Ark_Number;
typedef struct Opt_Literal_space_Opt_Union_Ark_String_Ark_Number {
    enum Ark_Tag tag;
    Literal_space_Opt_Union_Ark_String_Ark_Number value;
} Opt_Literal_space_Opt_Union_Ark_String_Ark_Number;
typedef struct RootSceneSession {
} RootSceneSession;
typedef struct Opt_RootSceneSession {
    enum Ark_Tag tag;
    RootSceneSession value;
} Opt_RootSceneSession;
typedef Ark_Materialized EditMenuOptions;
typedef struct Opt_EditMenuOptions {
    enum Ark_Tag tag;
    EditMenuOptions value;
} Opt_EditMenuOptions;
typedef Ark_Int32 Ark_EnterKeyType;
typedef struct Opt_Ark_EnterKeyType { enum Ark_Tag tag; Ark_EnterKeyType value; } Opt_Ark_EnterKeyType;
typedef struct PlaceholderStyle {
    struct Opt_Font font;
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource fontColor;
} PlaceholderStyle;
typedef struct Opt_PlaceholderStyle {
    enum Ark_Tag tag;
    PlaceholderStyle value;
} Opt_PlaceholderStyle;
typedef Ark_Int32 Ark_TextDataDetectorType;
typedef struct Opt_Ark_TextDataDetectorType { enum Ark_Tag tag; Ark_TextDataDetectorType value; } Opt_Ark_TextDataDetectorType;
typedef struct TextDataDetectorConfig {
    struct Array_Ark_TextDataDetectorType types;
    struct Opt_Ark_Function onDetectResultUpdate;
} TextDataDetectorConfig;
typedef struct Opt_TextDataDetectorConfig {
    enum Ark_Tag tag;
    TextDataDetectorConfig value;
} Opt_TextDataDetectorConfig;
typedef struct KeyboardOptions {
    Opt_Ark_Boolean supportAvoidance;
} KeyboardOptions;
typedef struct Opt_KeyboardOptions {
    enum Ark_Tag tag;
    KeyboardOptions value;
} Opt_KeyboardOptions;
typedef struct SelectionMenuOptions {
    struct Opt_Ark_Function onAppear;
    struct Opt_Ark_Function onDisappear;
} SelectionMenuOptions;
typedef struct Opt_SelectionMenuOptions {
    enum Ark_Tag tag;
    SelectionMenuOptions value;
} Opt_SelectionMenuOptions;
typedef struct Union_Ark_ResponseType_Ark_RichEditorResponseType {
    Ark_Int32 selector;
    union {
        Ark_ResponseType value0;
        Ark_RichEditorResponseType value1;
    };
} Union_Ark_ResponseType_Ark_RichEditorResponseType;
typedef struct Opt_Union_Ark_ResponseType_Ark_RichEditorResponseType {
    enum Ark_Tag tag;
    Union_Ark_ResponseType_Ark_RichEditorResponseType value;
} Opt_Union_Ark_ResponseType_Ark_RichEditorResponseType;
typedef Ark_Int32 Ark_RichEditorSpanType;
typedef struct Opt_Ark_RichEditorSpanType { enum Ark_Tag tag; Ark_RichEditorSpanType value; } Opt_Ark_RichEditorSpanType;
typedef struct RichEditorStyledStringOptions {
    RichEditorStyledStringController controller;
} RichEditorStyledStringOptions;
typedef struct Opt_RichEditorStyledStringOptions {
    enum Ark_Tag tag;
    RichEditorStyledStringOptions value;
} Opt_RichEditorStyledStringOptions;
typedef struct RichEditorOptions {
    RichEditorController controller;
} RichEditorOptions;
typedef struct Opt_RichEditorOptions {
    enum Ark_Tag tag;
    RichEditorOptions value;
} Opt_RichEditorOptions;
typedef struct LocalizedBarrierStyle {
    Ark_String id;
    Ark_LocalizedBarrierDirection localizedDirection;
    struct Array_Ark_String referencedId;
} LocalizedBarrierStyle;
typedef struct Opt_LocalizedBarrierStyle {
    enum Ark_Tag tag;
    LocalizedBarrierStyle value;
} Opt_LocalizedBarrierStyle;
typedef struct Array_LocalizedBarrierStyle {
    struct LocalizedBarrierStyle* array;
    Ark_Int32 length;
} Array_LocalizedBarrierStyle;
typedef struct Opt_Array_LocalizedBarrierStyle {
    enum Ark_Tag tag;
    Array_LocalizedBarrierStyle value;
} Opt_Array_LocalizedBarrierStyle;
typedef struct BarrierStyle {
    Ark_String id;
    Ark_BarrierDirection direction;
    struct Array_Ark_String referencedId;
} BarrierStyle;
typedef struct Opt_BarrierStyle {
    enum Ark_Tag tag;
    BarrierStyle value;
} Opt_BarrierStyle;
typedef struct Array_BarrierStyle {
    struct BarrierStyle* array;
    Ark_Int32 length;
} Array_BarrierStyle;
typedef struct Opt_Array_BarrierStyle {
    enum Ark_Tag tag;
    Array_BarrierStyle value;
} Opt_Array_BarrierStyle;
typedef struct GuideLineStyle {
    Ark_String id;
    Ark_Axis direction;
    struct GuideLinePosition position;
} GuideLineStyle;
typedef struct Opt_GuideLineStyle {
    enum Ark_Tag tag;
    GuideLineStyle value;
} Opt_GuideLineStyle;
typedef struct Array_GuideLineStyle {
    struct GuideLineStyle* array;
    Ark_Int32 length;
} Array_GuideLineStyle;
typedef struct Opt_Array_GuideLineStyle {
    enum Ark_Tag tag;
    Array_GuideLineStyle value;
} Opt_Array_GuideLineStyle;
typedef struct RefreshOptions {
    Ark_Boolean refreshing;
    struct Opt_Union_Ark_Number_Ark_String offset;
    struct Opt_Union_Ark_Number_Ark_String friction;
    struct Opt_Union_Ark_String_Ark_Resource promptText;
    struct Opt_Union_Ark_Function_Ark_Undefined builder;
} RefreshOptions;
typedef struct Opt_RefreshOptions {
    enum Ark_Tag tag;
    RefreshOptions value;
} Opt_RefreshOptions;
typedef struct Union_Literal_width_Opt_Union_Ark_Number_Ark_String_height_Opt_Union_Ark_Number_Ark_String_radius_Opt_Union_Ark_Number_Ark_String_Array_Ark_CustomObject_Literal_width_Opt_Union_Ark_Number_Ark_String_height_Opt_Union_Ark_Number_Ark_String_radiusWidth_Opt_Union_Ark_Number_Ark_String_radiusHeight_Opt_Union_Ark_Number_Ark_String {
    Ark_Int32 selector;
    union {
        struct Literal_width_Opt_Union_Ark_Number_Ark_String_height_Opt_Union_Ark_Number_Ark_String_radius_Opt_Union_Ark_Number_Ark_String_Array_Ark_CustomObject value0;
        struct Literal_width_Opt_Union_Ark_Number_Ark_String_height_Opt_Union_Ark_Number_Ark_String_radiusWidth_Opt_Union_Ark_Number_Ark_String_radiusHeight_Opt_Union_Ark_Number_Ark_String value1;
    };
} Union_Literal_width_Opt_Union_Ark_Number_Ark_String_height_Opt_Union_Ark_Number_Ark_String_radius_Opt_Union_Ark_Number_Ark_String_Array_Ark_CustomObject_Literal_width_Opt_Union_Ark_Number_Ark_String_height_Opt_Union_Ark_Number_Ark_String_radiusWidth_Opt_Union_Ark_Number_Ark_String_radiusHeight_Opt_Union_Ark_Number_Ark_String;
typedef struct Opt_Union_Literal_width_Opt_Union_Ark_Number_Ark_String_height_Opt_Union_Ark_Number_Ark_String_radius_Opt_Union_Ark_Number_Ark_String_Array_Ark_CustomObject_Literal_width_Opt_Union_Ark_Number_Ark_String_height_Opt_Union_Ark_Number_Ark_String_radiusWidth_Opt_Union_Ark_Number_Ark_String_radiusHeight_Opt_Union_Ark_Number_Ark_String {
    enum Ark_Tag tag;
    Union_Literal_width_Opt_Union_Ark_Number_Ark_String_height_Opt_Union_Ark_Number_Ark_String_radius_Opt_Union_Ark_Number_Ark_String_Array_Ark_CustomObject_Literal_width_Opt_Union_Ark_Number_Ark_String_height_Opt_Union_Ark_Number_Ark_String_radiusWidth_Opt_Union_Ark_Number_Ark_String_radiusHeight_Opt_Union_Ark_Number_Ark_String value;
} Opt_Union_Literal_width_Opt_Union_Ark_Number_Ark_String_height_Opt_Union_Ark_Number_Ark_String_radius_Opt_Union_Ark_Number_Ark_String_Array_Ark_CustomObject_Literal_width_Opt_Union_Ark_Number_Ark_String_height_Opt_Union_Ark_Number_Ark_String_radiusWidth_Opt_Union_Ark_Number_Ark_String_radiusHeight_Opt_Union_Ark_Number_Ark_String;
typedef struct Literal_backgroundUri_Ark_String_foregroundUri_Ark_String_secondaryUri_Opt_Ark_String {
    Ark_String backgroundUri;
    Ark_String foregroundUri;
    Opt_Ark_String secondaryUri;
} Literal_backgroundUri_Ark_String_foregroundUri_Ark_String_secondaryUri_Opt_Ark_String;
typedef struct Opt_Literal_backgroundUri_Ark_String_foregroundUri_Ark_String_secondaryUri_Opt_Ark_String {
    enum Ark_Tag tag;
    Literal_backgroundUri_Ark_String_foregroundUri_Ark_String_secondaryUri_Opt_Ark_String value;
} Opt_Literal_backgroundUri_Ark_String_foregroundUri_Ark_String_secondaryUri_Opt_Ark_String;
typedef struct Literal_rating_Ark_Number_indicator_Opt_Ark_Boolean {
    Ark_Number rating;
    Opt_Ark_Boolean indicator;
} Literal_rating_Ark_Number_indicator_Opt_Ark_Boolean;
typedef struct Opt_Literal_rating_Ark_Number_indicator_Opt_Ark_Boolean {
    enum Ark_Tag tag;
    Literal_rating_Ark_Number_indicator_Opt_Ark_Boolean value;
} Opt_Literal_rating_Ark_Number_indicator_Opt_Ark_Boolean;
typedef struct RadioStyle {
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource checkedBackgroundColor;
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource uncheckedBorderColor;
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource indicatorColor;
} RadioStyle;
typedef struct Opt_RadioStyle {
    enum Ark_Tag tag;
    RadioStyle value;
} Opt_RadioStyle;
typedef struct RadioOptions {
    Ark_String group;
    Ark_String value;
    Opt_Ark_RadioIndicatorType indicatorType;
    struct Opt_Union_Ark_Function_Ark_Undefined indicatorBuilder;
} RadioOptions;
typedef struct Opt_RadioOptions {
    enum Ark_Tag tag;
    RadioOptions value;
} Opt_RadioOptions;
typedef struct Literal_width_Opt_Union_Ark_String_Ark_Number_height_Opt_Union_Ark_String_Ark_Number {
    struct Opt_Union_Ark_String_Ark_Number width;
    struct Opt_Union_Ark_String_Ark_Number height;
} Literal_width_Opt_Union_Ark_String_Ark_Number_height_Opt_Union_Ark_String_Ark_Number;
typedef struct Opt_Literal_width_Opt_Union_Ark_String_Ark_Number_height_Opt_Union_Ark_String_Ark_Number {
    enum Ark_Tag tag;
    Literal_width_Opt_Union_Ark_String_Ark_Number_height_Opt_Union_Ark_String_Ark_Number value;
} Opt_Literal_width_Opt_Union_Ark_String_Ark_Number_height_Opt_Union_Ark_String_Ark_Number;
typedef struct Literal_template_PluginComponentTemplate_data_Ark_CustomObject {
    struct PluginComponentTemplate template_;
    Ark_CustomObject data;
} Literal_template_PluginComponentTemplate_data_Ark_CustomObject;
typedef struct Opt_Literal_template_PluginComponentTemplate_data_Ark_CustomObject {
    enum Ark_Tag tag;
    Literal_template_PluginComponentTemplate_data_Ark_CustomObject value;
} Opt_Literal_template_PluginComponentTemplate_data_Ark_CustomObject;
typedef Ark_Materialized PatternLockController;
typedef struct Opt_PatternLockController {
    enum Ark_Tag tag;
    PatternLockController value;
} Opt_PatternLockController;
typedef struct Literal_width_Opt_Union_Ark_Number_Ark_String_height_Opt_Union_Ark_Number_Ark_String_commands_Opt_Ark_String {
    struct Opt_Union_Ark_Number_Ark_String width;
    struct Opt_Union_Ark_Number_Ark_String height;
    Opt_Ark_String commands;
} Literal_width_Opt_Union_Ark_Number_Ark_String_height_Opt_Union_Ark_Number_Ark_String_commands_Opt_Ark_String;
typedef struct Opt_Literal_width_Opt_Union_Ark_Number_Ark_String_height_Opt_Union_Ark_Number_Ark_String_commands_Opt_Ark_String {
    enum Ark_Tag tag;
    Literal_width_Opt_Union_Ark_Number_Ark_String_height_Opt_Union_Ark_Number_Ark_String_commands_Opt_Ark_String value;
} Opt_Literal_width_Opt_Union_Ark_Number_Ark_String_height_Opt_Union_Ark_Number_Ark_String_commands_Opt_Ark_String;
typedef struct PasteButtonOptions {
    Opt_Ark_PasteIconStyle icon;
    Opt_Ark_PasteDescription text;
    Opt_Ark_ButtonType buttonType;
} PasteButtonOptions;
typedef struct Opt_PasteButtonOptions {
    enum Ark_Tag tag;
    PasteButtonOptions value;
} Opt_PasteButtonOptions;
typedef struct Union_Ark_Length_Ark_PanelHeight {
    Ark_Int32 selector;
    union {
        Ark_Length value0;
        Ark_PanelHeight value1;
    };
} Union_Ark_Length_Ark_PanelHeight;
typedef struct Opt_Union_Ark_Length_Ark_PanelHeight {
    enum Ark_Tag tag;
    Union_Ark_Length_Ark_PanelHeight value;
} Opt_Union_Ark_Length_Ark_PanelHeight;
typedef Ark_Int32 Ark_PanelType;
typedef struct Opt_Ark_PanelType { enum Ark_Tag tag; Ark_PanelType value; } Opt_Ark_PanelType;
typedef Ark_Int32 Ark_PanelMode;
typedef struct Opt_Ark_PanelMode { enum Ark_Tag tag; Ark_PanelMode value; } Opt_Ark_PanelMode;
typedef struct Literal_target_Ark_String_type_Opt_Ark_NavigationType {
    Ark_String target;
    Opt_Ark_NavigationType type;
} Literal_target_Ark_String_type_Opt_Ark_NavigationType;
typedef struct Opt_Literal_target_Ark_String_type_Opt_Ark_NavigationType {
    enum Ark_Tag tag;
    Literal_target_Ark_String_type_Opt_Ark_NavigationType value;
} Opt_Literal_target_Ark_String_type_Opt_Ark_NavigationType;
typedef int32_t Ark_LayoutSafeAreaEdge;
typedef struct Array_Ark_LayoutSafeAreaEdge {
    Ark_LayoutSafeAreaEdge* array;
    Ark_Int32 length;
} Array_Ark_LayoutSafeAreaEdge;
typedef int32_t Ark_LayoutSafeAreaEdge;
typedef struct Opt_Array_Ark_LayoutSafeAreaEdge {
    enum Ark_Tag tag;
    Array_Ark_LayoutSafeAreaEdge value;
} Opt_Array_Ark_LayoutSafeAreaEdge;
typedef int32_t Ark_LayoutSafeAreaType;
typedef struct Array_Ark_LayoutSafeAreaType {
    Ark_LayoutSafeAreaType* array;
    Ark_Int32 length;
} Array_Ark_LayoutSafeAreaType;
typedef int32_t Ark_LayoutSafeAreaType;
typedef struct Opt_Array_Ark_LayoutSafeAreaType {
    enum Ark_Tag tag;
    Array_Ark_LayoutSafeAreaType value;
} Opt_Array_Ark_LayoutSafeAreaType;
typedef struct NavigationToolbarOptions {
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource backgroundColor;
    Opt_Ark_BlurStyle backgroundBlurStyle;
} NavigationToolbarOptions;
typedef struct Opt_NavigationToolbarOptions {
    enum Ark_Tag tag;
    NavigationToolbarOptions value;
} Opt_NavigationToolbarOptions;
typedef struct ToolbarItem {
    struct Union_Ark_String_Ark_Resource value;
    struct Opt_Union_Ark_String_Ark_Resource icon;
    Opt_Ark_CustomObject symbolIcon;
    struct Opt_Ark_Function action;
    Opt_Ark_ToolbarItemStatus status;
    struct Opt_Union_Ark_String_Ark_Resource activeIcon;
    Opt_Ark_CustomObject activeSymbolIcon;
} ToolbarItem;
typedef struct Opt_ToolbarItem {
    enum Ark_Tag tag;
    ToolbarItem value;
} Opt_ToolbarItem;
typedef struct Union_Array_ToolbarItem_Union_Ark_Function_Ark_Undefined {
    Ark_Int32 selector;
    union {
        struct Array_ToolbarItem value0;
        struct Union_Ark_Function_Ark_Undefined value1;
    };
} Union_Array_ToolbarItem_Union_Ark_Function_Ark_Undefined;
typedef struct Opt_Union_Array_ToolbarItem_Union_Ark_Function_Ark_Undefined {
    enum Ark_Tag tag;
    Union_Array_ToolbarItem_Union_Ark_Function_Ark_Undefined value;
} Opt_Union_Array_ToolbarItem_Union_Ark_Function_Ark_Undefined;
typedef struct Union_Ark_CustomObject_Union_Ark_Function_Ark_Undefined {
    Ark_Int32 selector;
    union {
        Ark_CustomObject value0;
        struct Union_Ark_Function_Ark_Undefined value1;
    };
} Union_Ark_CustomObject_Union_Ark_Function_Ark_Undefined;
typedef struct Opt_Union_Ark_CustomObject_Union_Ark_Function_Ark_Undefined {
    enum Ark_Tag tag;
    Union_Ark_CustomObject_Union_Ark_Function_Ark_Undefined value;
} Opt_Union_Ark_CustomObject_Union_Ark_Function_Ark_Undefined;
typedef struct Union_Array_NavigationMenuItem_Union_Ark_Function_Ark_Undefined {
    Ark_Int32 selector;
    union {
        struct Array_NavigationMenuItem value0;
        struct Union_Ark_Function_Ark_Undefined value1;
    };
} Union_Array_NavigationMenuItem_Union_Ark_Function_Ark_Undefined;
typedef struct Opt_Union_Array_NavigationMenuItem_Union_Ark_Function_Ark_Undefined {
    enum Ark_Tag tag;
    Union_Array_NavigationMenuItem_Union_Ark_Function_Ark_Undefined value;
} Opt_Union_Array_NavigationMenuItem_Union_Ark_Function_Ark_Undefined;
typedef Ark_Int32 Ark_NavigationTitleMode;
typedef struct Opt_Ark_NavigationTitleMode { enum Ark_Tag tag; Ark_NavigationTitleMode value; } Opt_Ark_NavigationTitleMode;
typedef struct Union_Union_Ark_String_Ark_Resource_Union_Ark_Function_Ark_Undefined_NavigationCommonTitle_NavigationCustomTitle {
    Ark_Int32 selector;
    union {
        struct Union_Ark_String_Ark_Resource value0;
        struct Union_Ark_Function_Ark_Undefined value1;
        struct NavigationCommonTitle value2;
        struct NavigationCustomTitle value3;
    };
} Union_Union_Ark_String_Ark_Resource_Union_Ark_Function_Ark_Undefined_NavigationCommonTitle_NavigationCustomTitle;
typedef struct Opt_Union_Union_Ark_String_Ark_Resource_Union_Ark_Function_Ark_Undefined_NavigationCommonTitle_NavigationCustomTitle {
    enum Ark_Tag tag;
    Union_Union_Ark_String_Ark_Resource_Union_Ark_Function_Ark_Undefined_NavigationCommonTitle_NavigationCustomTitle value;
} Opt_Union_Union_Ark_String_Ark_Resource_Union_Ark_Function_Ark_Undefined_NavigationCommonTitle_NavigationCustomTitle;
typedef struct Union_Ark_String_Ark_CustomObject_Ark_Resource_Ark_CustomObject {
    Ark_Int32 selector;
    union {
        Ark_String value0;
        Ark_CustomObject value1;
        Ark_Resource value2;
        Ark_CustomObject value3;
    };
} Union_Ark_String_Ark_CustomObject_Ark_Resource_Ark_CustomObject;
typedef struct Opt_Union_Ark_String_Ark_CustomObject_Ark_Resource_Ark_CustomObject {
    enum Ark_Tag tag;
    Union_Ark_String_Ark_CustomObject_Ark_Resource_Ark_CustomObject value;
} Opt_Union_Ark_String_Ark_CustomObject_Ark_Resource_Ark_CustomObject;
typedef Ark_Int32 Ark_NavigationMode;
typedef struct Opt_Ark_NavigationMode { enum Ark_Tag tag; Ark_NavigationMode value; } Opt_Ark_NavigationMode;
typedef Ark_Int32 Ark_NavBarPosition;
typedef struct Opt_Ark_NavBarPosition { enum Ark_Tag tag; Ark_NavBarPosition value; } Opt_Ark_NavBarPosition;
typedef Ark_Materialized NavPathStack;
typedef struct Opt_NavPathStack {
    enum Ark_Tag tag;
    NavPathStack value;
} Opt_NavPathStack;
typedef Ark_Int32 Ark_NavRouteMode;
typedef struct Opt_Ark_NavRouteMode { enum Ark_Tag tag; Ark_NavRouteMode value; } Opt_Ark_NavRouteMode;
typedef struct RouteInfo {
    Ark_String name;
    Opt_Ark_CustomObject param;
} RouteInfo;
typedef struct Opt_RouteInfo {
    enum Ark_Tag tag;
    RouteInfo value;
} Opt_RouteInfo;
typedef Ark_Int32 Ark_LayoutSafeAreaEdge;
typedef struct Opt_Ark_LayoutSafeAreaEdge { enum Ark_Tag tag; Ark_LayoutSafeAreaEdge value; } Opt_Ark_LayoutSafeAreaEdge;
typedef Ark_Int32 Ark_LayoutSafeAreaType;
typedef struct Opt_Ark_LayoutSafeAreaType { enum Ark_Tag tag; Ark_LayoutSafeAreaType value; } Opt_Ark_LayoutSafeAreaType;
typedef struct NavigationMenuItem {
    Ark_String value;
    Opt_Ark_String icon;
    Opt_Ark_CustomObject symbolIcon;
    Opt_Ark_Boolean isEnabled;
    struct Opt_Ark_Function action;
} NavigationMenuItem;
typedef struct Opt_NavigationMenuItem {
    enum Ark_Tag tag;
    NavigationMenuItem value;
} Opt_NavigationMenuItem;
typedef struct Union_Union_Ark_String_Ark_Resource_Ark_CustomObject_Ark_CustomObject {
    Ark_Int32 selector;
    union {
        struct Union_Ark_String_Ark_Resource value0;
        Ark_CustomObject value1;
        Ark_CustomObject value2;
    };
} Union_Union_Ark_String_Ark_Resource_Ark_CustomObject_Ark_CustomObject;
typedef struct Opt_Union_Union_Ark_String_Ark_Resource_Ark_CustomObject_Ark_CustomObject {
    enum Ark_Tag tag;
    Union_Union_Ark_String_Ark_Resource_Ark_CustomObject_Ark_CustomObject value;
} Opt_Union_Union_Ark_String_Ark_Resource_Ark_CustomObject_Ark_CustomObject;
typedef struct NavigationTitleOptions {
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource backgroundColor;
    Opt_Ark_BlurStyle backgroundBlurStyle;
    Opt_Ark_BarStyle barStyle;
    Opt_Ark_CustomObject paddingStart;
    Opt_Ark_CustomObject paddingEnd;
} NavigationTitleOptions;
typedef struct Opt_NavigationTitleOptions {
    enum Ark_Tag tag;
    NavigationTitleOptions value;
} Opt_NavigationTitleOptions;
typedef struct Union_Ark_String_Union_Ark_Function_Ark_Undefined_NavDestinationCommonTitle_NavDestinationCustomTitle {
    Ark_Int32 selector;
    union {
        Ark_String value0;
        struct Union_Ark_Function_Ark_Undefined value1;
        struct NavDestinationCommonTitle value2;
        struct NavDestinationCustomTitle value3;
    };
} Union_Ark_String_Union_Ark_Function_Ark_Undefined_NavDestinationCommonTitle_NavDestinationCustomTitle;
typedef struct Opt_Union_Ark_String_Union_Ark_Function_Ark_Undefined_NavDestinationCommonTitle_NavDestinationCustomTitle {
    enum Ark_Tag tag;
    Union_Ark_String_Union_Ark_Function_Ark_Undefined_NavDestinationCommonTitle_NavDestinationCustomTitle value;
} Opt_Union_Ark_String_Union_Ark_Function_Ark_Undefined_NavDestinationCommonTitle_NavDestinationCustomTitle;
typedef struct MenuItemGroupOptions {
    struct Opt_Union_Union_Ark_String_Ark_Resource_Union_Ark_Function_Ark_Undefined header;
    struct Opt_Union_Union_Ark_String_Ark_Resource_Union_Ark_Function_Ark_Undefined footer;
} MenuItemGroupOptions;
typedef struct Opt_MenuItemGroupOptions {
    enum Ark_Tag tag;
    MenuItemGroupOptions value;
} Opt_MenuItemGroupOptions;
typedef struct Union_Ark_Boolean_Union_Ark_String_Ark_Resource_Ark_CustomObject {
    Ark_Int32 selector;
    union {
        Ark_Boolean value0;
        struct Union_Ark_String_Ark_Resource value1;
        Ark_CustomObject value2;
    };
} Union_Ark_Boolean_Union_Ark_String_Ark_Resource_Ark_CustomObject;
typedef struct Opt_Union_Ark_Boolean_Union_Ark_String_Ark_Resource_Ark_CustomObject {
    enum Ark_Tag tag;
    Union_Ark_Boolean_Union_Ark_String_Ark_Resource_Ark_CustomObject value;
} Opt_Union_Ark_Boolean_Union_Ark_String_Ark_Resource_Ark_CustomObject;
typedef struct Union_MenuItemOptions_Union_Ark_Function_Ark_Undefined {
    Ark_Int32 selector;
    union {
        struct MenuItemOptions value0;
        struct Union_Ark_Function_Ark_Undefined value1;
    };
} Union_MenuItemOptions_Union_Ark_Function_Ark_Undefined;
typedef struct Opt_Union_MenuItemOptions_Union_Ark_Function_Ark_Undefined {
    enum Ark_Tag tag;
    Union_MenuItemOptions_Union_Ark_Function_Ark_Undefined value;
} Opt_Union_MenuItemOptions_Union_Ark_Function_Ark_Undefined;
typedef Ark_Int32 Ark_SubMenuExpandingMode;
typedef struct Opt_Ark_SubMenuExpandingMode { enum Ark_Tag tag; Ark_SubMenuExpandingMode value; } Opt_Ark_SubMenuExpandingMode;
typedef struct Union_DividerStyleOptions_Ark_Undefined {
    Ark_Int32 selector;
    union {
        struct DividerStyleOptions value0;
        Ark_Undefined value1;
    };
} Union_DividerStyleOptions_Ark_Undefined;
typedef struct Opt_Union_DividerStyleOptions_Ark_Undefined {
    enum Ark_Tag tag;
    Union_DividerStyleOptions_Ark_Undefined value;
} Opt_Union_DividerStyleOptions_Ark_Undefined;
typedef struct Union_Ark_CustomObject_Union_Ark_String_Ark_Resource_Ark_CustomObject_ASTCResource {
    Ark_Int32 selector;
    union {
        Ark_CustomObject value0;
        struct Union_Ark_String_Ark_Resource value1;
        Ark_CustomObject value2;
        struct ASTCResource value3;
    };
} Union_Ark_CustomObject_Union_Ark_String_Ark_Resource_Ark_CustomObject_ASTCResource;
typedef struct Opt_Union_Ark_CustomObject_Union_Ark_String_Ark_Resource_Ark_CustomObject_ASTCResource {
    enum Ark_Tag tag;
    Union_Ark_CustomObject_Union_Ark_String_Ark_Resource_Ark_CustomObject_ASTCResource value;
} Opt_Union_Ark_CustomObject_Union_Ark_String_Ark_Resource_Ark_CustomObject_ASTCResource;
typedef Ark_Int32 Ark_MarqueeUpdateStrategy;
typedef struct Opt_Ark_MarqueeUpdateStrategy { enum Ark_Tag tag; Ark_MarqueeUpdateStrategy value; } Opt_Ark_MarqueeUpdateStrategy;
typedef struct Literal_start_Ark_Boolean_step_Opt_Ark_Number_loop_Opt_Ark_Number_fromStart_Opt_Ark_Boolean_src_Ark_String {
    Ark_Boolean start;
    Opt_Ark_Number step;
    Opt_Ark_Number loop;
    Opt_Ark_Boolean fromStart;
    Ark_String src;
} Literal_start_Ark_Boolean_step_Opt_Ark_Number_loop_Opt_Ark_Number_fromStart_Opt_Ark_Boolean_src_Ark_String;
typedef struct Opt_Literal_start_Ark_Boolean_step_Opt_Ark_Number_loop_Opt_Ark_Number_fromStart_Opt_Ark_Boolean_src_Ark_String {
    enum Ark_Tag tag;
    Literal_start_Ark_Boolean_step_Opt_Ark_Number_loop_Opt_Ark_Number_fromStart_Opt_Ark_Boolean_src_Ark_String value;
} Opt_Literal_start_Ark_Boolean_step_Opt_Ark_Number_loop_Opt_Ark_Number_fromStart_Opt_Ark_Boolean_src_Ark_String;
typedef struct LocationButtonOptions {
    Opt_Ark_LocationIconStyle icon;
    Opt_Ark_LocationDescription text;
    Opt_Ark_ButtonType buttonType;
} LocationButtonOptions;
typedef struct Opt_LocationButtonOptions {
    enum Ark_Tag tag;
    LocationButtonOptions value;
} Opt_LocationButtonOptions;
typedef struct Union_Position_Edges_LocalizedEdges {
    Ark_Int32 selector;
    union {
        struct Position value0;
        struct Edges value1;
        struct LocalizedEdges value2;
    };
} Union_Position_Edges_LocalizedEdges;
typedef struct Opt_Union_Position_Edges_LocalizedEdges {
    enum Ark_Tag tag;
    Union_Position_Edges_LocalizedEdges value;
} Opt_Union_Position_Edges_LocalizedEdges;
typedef Ark_Int32 Ark_SecurityComponentLayoutDirection;
typedef struct Opt_Ark_SecurityComponentLayoutDirection { enum Ark_Tag tag; Ark_SecurityComponentLayoutDirection value; } Opt_Ark_SecurityComponentLayoutDirection;
typedef struct Union_Literal_strokeWidth_Ark_Length_color_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_startMargin_Opt_Ark_Length_endMargin_Opt_Ark_Length_Ark_Undefined {
    Ark_Int32 selector;
    union {
        struct Literal_strokeWidth_Ark_Length_color_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_startMargin_Opt_Ark_Length_endMargin_Opt_Ark_Length value0;
        struct Ark_Undefined value1;
    };
} Union_Literal_strokeWidth_Ark_Length_color_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_startMargin_Opt_Ark_Length_endMargin_Opt_Ark_Length_Ark_Undefined;
typedef struct Opt_Union_Literal_strokeWidth_Ark_Length_color_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_startMargin_Opt_Ark_Length_endMargin_Opt_Ark_Length_Ark_Undefined {
    enum Ark_Tag tag;
    Union_Literal_strokeWidth_Ark_Length_color_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_startMargin_Opt_Ark_Length_endMargin_Opt_Ark_Length_Ark_Undefined value;
} Opt_Union_Literal_strokeWidth_Ark_Length_color_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_startMargin_Opt_Ark_Length_endMargin_Opt_Ark_Length_Ark_Undefined;
typedef struct ListItemGroupOptions {
    struct Opt_Union_Ark_Function_Ark_Undefined header;
    struct Opt_Union_Ark_Function_Ark_Undefined footer;
    struct Opt_Union_Ark_Number_Ark_String space;
    Opt_Ark_ListItemGroupStyle style;
} ListItemGroupOptions;
typedef struct Opt_ListItemGroupOptions {
    enum Ark_Tag tag;
    ListItemGroupOptions value;
} Opt_ListItemGroupOptions;
typedef struct SwipeActionOptions {
    struct Opt_Union_Union_Ark_Function_Ark_Undefined_SwipeActionItem start;
    struct Opt_Union_Union_Ark_Function_Ark_Undefined_SwipeActionItem end;
    Opt_Ark_SwipeEdgeEffect edgeEffect;
    struct Opt_Ark_Function onOffsetChange;
} SwipeActionOptions;
typedef struct Opt_SwipeActionOptions {
    enum Ark_Tag tag;
    SwipeActionOptions value;
} Opt_SwipeActionOptions;
typedef struct Union_Ark_Boolean_Ark_EditMode {
    Ark_Int32 selector;
    union {
        Ark_Boolean value0;
        Ark_EditMode value1;
    };
} Union_Ark_Boolean_Ark_EditMode;
typedef struct Opt_Union_Ark_Boolean_Ark_EditMode {
    enum Ark_Tag tag;
    Union_Ark_Boolean_Ark_EditMode value;
} Opt_Union_Ark_Boolean_Ark_EditMode;
typedef Ark_Int32 Ark_Sticky;
typedef struct Opt_Ark_Sticky { enum Ark_Tag tag; Ark_Sticky value; } Opt_Ark_Sticky;
typedef struct ListItemOptions {
    Opt_Ark_ListItemStyle style;
} ListItemOptions;
typedef struct Opt_ListItemOptions {
    enum Ark_Tag tag;
    ListItemOptions value;
} Opt_ListItemOptions;
typedef Ark_Materialized ChildrenMainSize;
typedef struct Opt_ChildrenMainSize {
    enum Ark_Tag tag;
    ChildrenMainSize value;
} Opt_ChildrenMainSize;
typedef Ark_Int32 Ark_StickyStyle;
typedef struct Opt_Ark_StickyStyle { enum Ark_Tag tag; Ark_StickyStyle value; } Opt_Ark_StickyStyle;
typedef struct ChainAnimationOptions {
    Ark_Length minSpace;
    Ark_Length maxSpace;
    Opt_Ark_Number conductivity;
    Opt_Ark_Number intensity;
    Opt_Ark_ChainEdgeEffect edgeEffect;
    Opt_Ark_Number stiffness;
    Opt_Ark_Number damping;
} ChainAnimationOptions;
typedef struct Opt_ChainAnimationOptions {
    enum Ark_Tag tag;
    ChainAnimationOptions value;
} Opt_ChainAnimationOptions;
typedef Ark_Int32 Ark_ListItemAlign;
typedef struct Opt_Ark_ListItemAlign { enum Ark_Tag tag; Ark_ListItemAlign value; } Opt_Ark_ListItemAlign;
typedef struct Union_Ark_Number_Literal_minLength_Ark_Length_maxLength_Ark_Length {
    Ark_Int32 selector;
    union {
        Ark_Number value0;
        struct Literal_minLength_Ark_Length_maxLength_Ark_Length value1;
    };
} Union_Ark_Number_Literal_minLength_Ark_Length_maxLength_Ark_Length;
typedef struct Opt_Union_Ark_Number_Literal_minLength_Ark_Length_maxLength_Ark_Length {
    enum Ark_Tag tag;
    Union_Ark_Number_Literal_minLength_Ark_Length_maxLength_Ark_Length value;
} Opt_Union_Ark_Number_Literal_minLength_Ark_Length_maxLength_Ark_Length;
typedef struct Literal_initialIndex_Opt_Ark_Number_space_Opt_Union_Ark_Number_Ark_String_scroller_Opt_Scroller {
    Opt_Ark_Number initialIndex;
    struct Opt_Union_Ark_Number_Ark_String space;
    Opt_Scroller scroller;
} Literal_initialIndex_Opt_Ark_Number_space_Opt_Union_Ark_Number_Ark_String_scroller_Opt_Scroller;
typedef struct Opt_Literal_initialIndex_Opt_Ark_Number_space_Opt_Union_Ark_Number_Ark_String_scroller_Opt_Scroller {
    enum Ark_Tag tag;
    Literal_initialIndex_Opt_Ark_Number_space_Opt_Union_Ark_Number_Ark_String_scroller_Opt_Scroller value;
} Opt_Literal_initialIndex_Opt_Ark_Number_space_Opt_Union_Ark_Number_Ark_String_scroller_Opt_Scroller;
typedef struct Union_ColorFilter_Ark_CustomObject {
    Ark_Int32 selector;
    union {
        struct ColorFilter value0;
        Ark_CustomObject value1;
    };
} Union_ColorFilter_Ark_CustomObject;
typedef struct Opt_Union_ColorFilter_Ark_CustomObject {
    enum Ark_Tag tag;
    Union_ColorFilter_Ark_CustomObject value;
} Opt_Union_ColorFilter_Ark_CustomObject;
typedef struct Union_Union_Ark_String_Ark_Resource_Ark_CustomObject {
    Ark_Int32 selector;
    union {
        struct Union_Ark_String_Ark_Resource value0;
        Ark_CustomObject value1;
    };
} Union_Union_Ark_String_Ark_Resource_Ark_CustomObject;
typedef struct Opt_Union_Union_Ark_String_Ark_Resource_Ark_CustomObject {
    enum Ark_Tag tag;
    Union_Union_Ark_String_Ark_Resource_Ark_CustomObject value;
} Opt_Union_Union_Ark_String_Ark_Resource_Ark_CustomObject;
typedef struct ImageFrameInfo {
    struct Union_Ark_String_Ark_Resource_Ark_CustomObject src;
    struct Opt_Union_Ark_Number_Ark_String width;
    struct Opt_Union_Ark_Number_Ark_String height;
    struct Opt_Union_Ark_Number_Ark_String top;
    struct Opt_Union_Ark_Number_Ark_String left;
    Opt_Ark_Number duration;
} ImageFrameInfo;
typedef struct Opt_ImageFrameInfo {
    enum Ark_Tag tag;
    ImageFrameInfo value;
} Opt_ImageFrameInfo;
typedef struct Array_ImageFrameInfo {
    struct ImageFrameInfo* array;
    Ark_Int32 length;
} Array_ImageFrameInfo;
typedef struct Opt_Array_ImageFrameInfo {
    enum Ark_Tag tag;
    Array_ImageFrameInfo value;
} Opt_Array_ImageFrameInfo;
typedef struct ImageAnalyzerConfig {
    struct Array_Ark_ImageAnalyzerType types;
} ImageAnalyzerConfig;
typedef struct Opt_ImageAnalyzerConfig {
    enum Ark_Tag tag;
    ImageAnalyzerConfig value;
} Opt_ImageAnalyzerConfig;
typedef Ark_Int32 Ark_CopyOptions;
typedef struct Opt_Ark_CopyOptions { enum Ark_Tag tag; Ark_CopyOptions value; } Opt_Ark_CopyOptions;
typedef struct Literal_width_Ark_Number_height_Ark_Number {
    Ark_Number width;
    Ark_Number height;
} Literal_width_Ark_Number_height_Ark_Number;
typedef struct Opt_Literal_width_Ark_Number_height_Ark_Number {
    enum Ark_Tag tag;
    Literal_width_Ark_Number_height_Ark_Number value;
} Opt_Literal_width_Ark_Number_height_Ark_Number;
typedef Ark_Int32 Ark_ImageInterpolation;
typedef struct Opt_Ark_ImageInterpolation { enum Ark_Tag tag; Ark_ImageInterpolation value; } Opt_Ark_ImageInterpolation;
typedef Ark_Int32 Ark_DynamicRangeMode;
typedef struct Opt_Ark_DynamicRangeMode { enum Ark_Tag tag; Ark_DynamicRangeMode value; } Opt_Ark_DynamicRangeMode;
typedef Ark_Int32 Ark_ImageRenderMode;
typedef struct Opt_Ark_ImageRenderMode { enum Ark_Tag tag; Ark_ImageRenderMode value; } Opt_Ark_ImageRenderMode;
typedef struct Union_Ark_CustomObject_Union_Ark_String_Ark_Resource_Ark_CustomObject {
    Ark_Int32 selector;
    union {
        Ark_CustomObject value0;
        struct Union_Ark_String_Ark_Resource value1;
        Ark_CustomObject value2;
    };
} Union_Ark_CustomObject_Union_Ark_String_Ark_Resource_Ark_CustomObject;
typedef struct Opt_Union_Ark_CustomObject_Union_Ark_String_Ark_Resource_Ark_CustomObject {
    enum Ark_Tag tag;
    Union_Ark_CustomObject_Union_Ark_String_Ark_Resource_Ark_CustomObject value;
} Opt_Union_Ark_CustomObject_Union_Ark_String_Ark_Resource_Ark_CustomObject;
typedef struct GridRowOptions {
    struct Opt_Union_Ark_Length_GutterOption gutter;
    struct Opt_Union_Ark_Number_GridRowColumnOption columns;
    struct Opt_BreakPoints breakpoints;
    Opt_Ark_GridRowDirection direction;
} GridRowOptions;
typedef struct Opt_GridRowOptions {
    enum Ark_Tag tag;
    GridRowOptions value;
} Opt_GridRowOptions;
typedef struct GridContainerOptions {
    struct Opt_Union_Ark_Number_Ark_String columns;
    Opt_Ark_SizeType sizeType;
    struct Opt_Union_Ark_Number_Ark_String gutter;
    struct Opt_Union_Ark_Number_Ark_String margin;
} GridContainerOptions;
typedef struct Opt_GridContainerOptions {
    enum Ark_Tag tag;
    GridContainerOptions value;
} Opt_GridContainerOptions;
typedef struct GridColOptions {
    struct Opt_Union_Ark_Number_GridColColumnOption span;
    struct Opt_Union_Ark_Number_GridColColumnOption offset;
    struct Opt_Union_Ark_Number_GridColColumnOption order;
} GridColOptions;
typedef struct Opt_GridColOptions {
    enum Ark_Tag tag;
    GridColOptions value;
} Opt_GridColOptions;
typedef struct GridItemOptions {
    Opt_Ark_GridItemStyle style;
} GridItemOptions;
typedef struct Opt_GridItemOptions {
    enum Ark_Tag tag;
    GridItemOptions value;
} Opt_GridItemOptions;
typedef Ark_Int32 Ark_GridDirection;
typedef struct Opt_Ark_GridDirection { enum Ark_Tag tag; Ark_GridDirection value; } Opt_Ark_GridDirection;
typedef struct GridLayoutOptions {
    struct Tuple_Ark_Number_Ark_Number regularSize;
    struct Opt_Array_Ark_Number irregularIndexes;
    struct Opt_Ark_Function onGetIrregularSizeByIndex;
    struct Opt_Ark_Function onGetRectByIndex;
} GridLayoutOptions;
typedef struct Opt_GridLayoutOptions {
    enum Ark_Tag tag;
    GridLayoutOptions value;
} Opt_GridLayoutOptions;
typedef struct NestedScrollOptions {
    Ark_NestedScrollMode scrollForward;
    Ark_NestedScrollMode scrollBackward;
} NestedScrollOptions;
typedef struct Opt_NestedScrollOptions {
    enum Ark_Tag tag;
    NestedScrollOptions value;
} Opt_NestedScrollOptions;
typedef struct EdgeEffectOptions {
    Ark_Boolean alwaysEnabled;
} EdgeEffectOptions;
typedef struct Opt_EdgeEffectOptions {
    enum Ark_Tag tag;
    EdgeEffectOptions value;
} Opt_EdgeEffectOptions;
typedef struct GaugeIndicatorOptions {
    struct Opt_Union_Ark_String_Ark_Resource icon;
    Opt_Ark_Length space;
} GaugeIndicatorOptions;
typedef struct Opt_GaugeIndicatorOptions {
    enum Ark_Tag tag;
    GaugeIndicatorOptions value;
} Opt_GaugeIndicatorOptions;
typedef struct GaugeShadowOptions {
    struct Opt_Union_Ark_Number_Ark_Resource radius;
    struct Opt_Union_Ark_Number_Ark_Resource offsetX;
    struct Opt_Union_Ark_Number_Ark_Resource offsetY;
} GaugeShadowOptions;
typedef struct Opt_GaugeShadowOptions {
    enum Ark_Tag tag;
    GaugeShadowOptions value;
} Opt_GaugeShadowOptions;
typedef struct Tuple_Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_LinearGradient_Ark_Number {
    struct Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_LinearGradient value0;
    Ark_Number value1;
} Tuple_Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_LinearGradient_Ark_Number;
typedef struct Opt_Tuple_Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_LinearGradient_Ark_Number {
    enum Ark_Tag tag;
    Tuple_Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_LinearGradient_Ark_Number value;
} Opt_Tuple_Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_LinearGradient_Ark_Number;
typedef struct Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_LinearGradient_Array_Tuple_Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_LinearGradient_Ark_Number {
    Ark_Int32 selector;
    union {
        struct Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource value0;
        struct LinearGradient value1;
        struct Array_Tuple_Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_LinearGradient_Ark_Number value2;
    };
} Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_LinearGradient_Array_Tuple_Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_LinearGradient_Ark_Number;
typedef struct Opt_Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_LinearGradient_Array_Tuple_Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_LinearGradient_Ark_Number {
    enum Ark_Tag tag;
    Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_LinearGradient_Array_Tuple_Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_LinearGradient_Ark_Number value;
} Opt_Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_LinearGradient_Array_Tuple_Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_LinearGradient_Ark_Number;
typedef struct Literal_value_Ark_Number_min_Opt_Ark_Number_max_Opt_Ark_Number {
    Ark_Number value;
    Opt_Ark_Number min;
    Opt_Ark_Number max;
} Literal_value_Ark_Number_min_Opt_Ark_Number_max_Opt_Ark_Number;
typedef struct Opt_Literal_value_Ark_Number_min_Opt_Ark_Number_max_Opt_Ark_Number {
    enum Ark_Tag tag;
    Literal_value_Ark_Number_min_Opt_Ark_Number_max_Opt_Ark_Number value;
} Opt_Literal_value_Ark_Number_min_Opt_Ark_Number_max_Opt_Ark_Number;
typedef struct FormLinkOptions {
    Ark_String action;
    Opt_Ark_String moduleName;
    Opt_Ark_String bundleName;
    Opt_Ark_String abilityName;
    Opt_Ark_String uri;
    struct Opt_Object params;
} FormLinkOptions;
typedef struct Opt_FormLinkOptions {
    enum Ark_Tag tag;
    FormLinkOptions value;
} Opt_FormLinkOptions;
typedef struct FormInfo {
    struct Union_Ark_Number_Ark_String id;
    Ark_String name;
    Ark_String bundle;
    Ark_String ability;
    Ark_String module;
    Opt_Ark_FormDimension dimension;
    Opt_Ark_Boolean temporary;
    Opt_Ark_CustomObject want;
    Opt_Ark_FormRenderingMode renderingMode;
    Opt_Ark_FormShape shape;
} FormInfo;
typedef struct Opt_FormInfo {
    enum Ark_Tag tag;
    FormInfo value;
} Opt_FormInfo;
typedef struct Literal_upperItems_Opt_Array_Ark_String {
    struct Opt_Array_Ark_String upperItems;
} Literal_upperItems_Opt_Array_Ark_String;
typedef struct Opt_Literal_upperItems_Opt_Array_Ark_String {
    enum Ark_Tag tag;
    Literal_upperItems_Opt_Array_Ark_String value;
} Opt_Literal_upperItems_Opt_Array_Ark_String;
typedef struct FlexOptions {
    Opt_Ark_FlexDirection direction;
    Opt_Ark_FlexWrap wrap;
    Opt_Ark_FlexAlign justifyContent;
    Opt_Ark_ItemAlign alignItems;
    Opt_Ark_FlexAlign alignContent;
    struct Opt_FlexSpaceOptions space;
} FlexOptions;
typedef struct Opt_FlexOptions {
    enum Ark_Tag tag;
    FlexOptions value;
} Opt_FlexOptions;
typedef Ark_Int32 Ark_EmbeddedType;
typedef struct Opt_Ark_EmbeddedType { enum Ark_Tag tag; Ark_EmbeddedType value; } Opt_Ark_EmbeddedType;
typedef struct DatePickerOptions {
    Opt_Ark_CustomObject start;
    Opt_Ark_CustomObject end;
    Opt_Ark_CustomObject selected;
} DatePickerOptions;
typedef struct Opt_DatePickerOptions {
    enum Ark_Tag tag;
    DatePickerOptions value;
} Opt_DatePickerOptions;
typedef struct DataPanelShadowOptions {
    struct Opt_Union_Ark_Number_Ark_Resource radius;
    struct Opt_Union_Ark_Number_Ark_Resource offsetX;
    struct Opt_Union_Ark_Number_Ark_Resource offsetY;
    struct Opt_Array_Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_LinearGradient colors;
} DataPanelShadowOptions;
typedef struct Opt_DataPanelShadowOptions {
    enum Ark_Tag tag;
    DataPanelShadowOptions value;
} Opt_DataPanelShadowOptions;
typedef struct DataPanelOptions {
    struct Array_Ark_Number values;
    Opt_Ark_Number max;
    Opt_Ark_DataPanelType type;
} DataPanelOptions;
typedef struct Opt_DataPanelOptions {
    enum Ark_Tag tag;
    DataPanelOptions value;
} Opt_DataPanelOptions;
typedef struct TextBackgroundStyle {
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource color;
    struct Opt_Union_Ark_Length_Literal_topLeft_Opt_Ark_Length_topRight_Opt_Ark_Length_bottomLeft_Opt_Ark_Length_bottomRight_Opt_Ark_Length radius;
} TextBackgroundStyle;
typedef struct Opt_TextBackgroundStyle {
    enum Ark_Tag tag;
    TextBackgroundStyle value;
} Opt_TextBackgroundStyle;
typedef struct SceneOptions {
    struct Opt_Union_Ark_Resource_Ark_CustomObject scene;
    Opt_Ark_ModelType modelType;
} SceneOptions;
typedef struct Opt_SceneOptions {
    enum Ark_Tag tag;
    SceneOptions value;
} Opt_SceneOptions;
typedef struct Union_ColumnSplitDividerStyle_Ark_Undefined {
    Ark_Int32 selector;
    union {
        struct ColumnSplitDividerStyle value0;
        struct Ark_Undefined value1;
    };
} Union_ColumnSplitDividerStyle_Ark_Undefined;
typedef struct Opt_Union_ColumnSplitDividerStyle_Ark_Undefined {
    enum Ark_Tag tag;
    Union_ColumnSplitDividerStyle_Ark_Undefined value;
} Opt_Union_ColumnSplitDividerStyle_Ark_Undefined;
typedef struct PointLightStyle {
    struct Opt_LightSource lightSource;
    Opt_Ark_IlluminatedType illuminated;
    Opt_Ark_Number bloom;
} PointLightStyle;
typedef struct Opt_PointLightStyle {
    enum Ark_Tag tag;
    PointLightStyle value;
} Opt_PointLightStyle;
typedef struct CircleOptions {
    struct Opt_Union_Ark_String_Ark_Number width;
    struct Opt_Union_Ark_String_Ark_Number height;
} CircleOptions;
typedef struct Opt_CircleOptions {
    enum Ark_Tag tag;
    CircleOptions value;
} Opt_CircleOptions;
typedef Ark_Int32 Ark_LineJoinStyle;
typedef struct Opt_Ark_LineJoinStyle { enum Ark_Tag tag; Ark_LineJoinStyle value; } Opt_Ark_LineJoinStyle;
typedef Ark_Int32 Ark_LineCapStyle;
typedef struct Opt_Ark_LineCapStyle { enum Ark_Tag tag; Ark_LineCapStyle value; } Opt_Ark_LineCapStyle;
typedef struct CheckboxGroupOptions {
    Opt_Ark_String group;
} CheckboxGroupOptions;
typedef struct Opt_CheckboxGroupOptions {
    enum Ark_Tag tag;
    CheckboxGroupOptions value;
} Opt_CheckboxGroupOptions;
typedef struct MarkStyle {
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource strokeColor;
    Opt_Ark_Length size;
    Opt_Ark_Length strokeWidth;
} MarkStyle;
typedef struct Opt_MarkStyle {
    enum Ark_Tag tag;
    MarkStyle value;
} Opt_MarkStyle;
typedef Ark_Int32 Ark_CheckBoxShape;
typedef struct Opt_Ark_CheckBoxShape { enum Ark_Tag tag; Ark_CheckBoxShape value; } Opt_Ark_CheckBoxShape;
typedef struct CheckboxOptions {
    Opt_Ark_String name;
    Opt_Ark_String group;
    struct Opt_Union_Ark_Function_Ark_Undefined indicatorBuilder;
} CheckboxOptions;
typedef struct Opt_CheckboxOptions {
    enum Ark_Tag tag;
    CheckboxOptions value;
} Opt_CheckboxOptions;
typedef Ark_Int32 Ark_ImageAnalyzerType;
typedef struct Opt_Ark_ImageAnalyzerType { enum Ark_Tag tag; Ark_ImageAnalyzerType value; } Opt_Ark_ImageAnalyzerType;
typedef struct Union_CanvasRenderingContext2D_DrawingRenderingContext {
    Ark_Int32 selector;
    union {
        CanvasRenderingContext2D value0;
        DrawingRenderingContext value1;
    };
} Union_CanvasRenderingContext2D_DrawingRenderingContext;
typedef struct Opt_Union_CanvasRenderingContext2D_DrawingRenderingContext {
    enum Ark_Tag tag;
    Union_CanvasRenderingContext2D_DrawingRenderingContext value;
} Opt_Union_CanvasRenderingContext2D_DrawingRenderingContext;
typedef struct PickerTextStyle {
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource color;
    struct Opt_Font font;
} PickerTextStyle;
typedef struct Opt_PickerTextStyle {
    enum Ark_Tag tag;
    PickerTextStyle value;
} Opt_PickerTextStyle;
typedef struct Literal_dx_Ark_Length_dy_Ark_Length {
    Ark_Length dx;
    Ark_Length dy;
} Literal_dx_Ark_Length_dy_Ark_Length;
typedef struct Opt_Literal_dx_Ark_Length_dy_Ark_Length {
    enum Ark_Tag tag;
    Literal_dx_Ark_Length_dy_Ark_Length value;
} Opt_Literal_dx_Ark_Length_dy_Ark_Length;
typedef Ark_Int32 Ark_CalendarAlign;
typedef struct Opt_Ark_CalendarAlign { enum Ark_Tag tag; Ark_CalendarAlign value; } Opt_Ark_CalendarAlign;
typedef struct CalendarOptions {
    struct Opt_Union_Ark_Number_Ark_Resource hintRadius;
    Opt_Ark_CustomObject selected;
} CalendarOptions;
typedef struct Opt_CalendarOptions {
    enum Ark_Tag tag;
    CalendarOptions value;
} Opt_CalendarOptions;
typedef struct WorkStateStyle {
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource workDayMarkColor;
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource offDayMarkColor;
    Opt_Ark_Number workDayMarkSize;
    Opt_Ark_Number offDayMarkSize;
    Opt_Ark_Number workStateWidth;
    Opt_Ark_Number workStateHorizontalMovingDistance;
    Opt_Ark_Number workStateVerticalMovingDistance;
} WorkStateStyle;
typedef struct Opt_WorkStateStyle {
    enum Ark_Tag tag;
    WorkStateStyle value;
} Opt_WorkStateStyle;
typedef struct WeekStyle {
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource weekColor;
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource weekendDayColor;
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource weekendLunarColor;
    Opt_Ark_Number weekFontSize;
    Opt_Ark_Number weekHeight;
    Opt_Ark_Number weekWidth;
    Opt_Ark_Number weekAndDayRowSpace;
} WeekStyle;
typedef struct Opt_WeekStyle {
    enum Ark_Tag tag;
    WeekStyle value;
} Opt_WeekStyle;
typedef struct TodayStyle {
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource focusedDayColor;
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource focusedLunarColor;
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource focusedAreaBackgroundColor;
    Opt_Ark_Number focusedAreaRadius;
} TodayStyle;
typedef struct Opt_TodayStyle {
    enum Ark_Tag tag;
    TodayStyle value;
} Opt_TodayStyle;
typedef struct NonCurrentDayStyle {
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource nonCurrentMonthDayColor;
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource nonCurrentMonthLunarColor;
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource nonCurrentMonthWorkDayMarkColor;
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource nonCurrentMonthOffDayMarkColor;
} NonCurrentDayStyle;
typedef struct Opt_NonCurrentDayStyle {
    enum Ark_Tag tag;
    NonCurrentDayStyle value;
} Opt_NonCurrentDayStyle;
typedef struct CurrentDayStyle {
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource dayColor;
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource lunarColor;
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource markLunarColor;
    Opt_Ark_Number dayFontSize;
    Opt_Ark_Number lunarDayFontSize;
    Opt_Ark_Number dayHeight;
    Opt_Ark_Number dayWidth;
    Opt_Ark_Number gregorianCalendarHeight;
    Opt_Ark_Number dayYAxisOffset;
    Opt_Ark_Number lunarDayYAxisOffset;
    Opt_Ark_Number underscoreXAxisOffset;
    Opt_Ark_Number underscoreYAxisOffset;
    Opt_Ark_Number scheduleMarkerXAxisOffset;
    Opt_Ark_Number scheduleMarkerYAxisOffset;
    Opt_Ark_Number colSpace;
    Opt_Ark_Number dailyFiveRowSpace;
    Opt_Ark_Number dailySixRowSpace;
    Opt_Ark_Number lunarHeight;
    Opt_Ark_Number underscoreWidth;
    Opt_Ark_Number underscoreLength;
    Opt_Ark_Number scheduleMarkerRadius;
    Opt_Ark_Number boundaryRowOffset;
    Opt_Ark_Number boundaryColOffset;
} CurrentDayStyle;
typedef struct Opt_CurrentDayStyle {
    enum Ark_Tag tag;
    CurrentDayStyle value;
} Opt_CurrentDayStyle;
typedef struct CalendarDay {
    Ark_Number index;
    Ark_String lunarMonth;
    Ark_String lunarDay;
    Ark_String dayMark;
    Ark_String dayMarkValue;
    Ark_Number year;
    Ark_Number month;
    Ark_Number day;
    Ark_Boolean isFirstOfLunar;
    Ark_Boolean hasSchedule;
    Ark_Boolean markLunarDay;
} CalendarDay;
typedef struct Opt_CalendarDay {
    enum Ark_Tag tag;
    CalendarDay value;
} Opt_CalendarDay;
typedef struct Literal_date_Literal_year_Ark_Number_month_Ark_Number_day_Ark_Number_currentData_MonthData_preData_MonthData_nextData_MonthData_controller_Opt_CalendarController {
    struct Literal_year_Ark_Number_month_Ark_Number_day_Ark_Number date;
    struct MonthData currentData;
    struct MonthData preData;
    struct MonthData nextData;
    Opt_CalendarController controller;
} Literal_date_Literal_year_Ark_Number_month_Ark_Number_day_Ark_Number_currentData_MonthData_preData_MonthData_nextData_MonthData_controller_Opt_CalendarController;
typedef struct Opt_Literal_date_Literal_year_Ark_Number_month_Ark_Number_day_Ark_Number_currentData_MonthData_preData_MonthData_nextData_MonthData_controller_Opt_CalendarController {
    enum Ark_Tag tag;
    Literal_date_Literal_year_Ark_Number_month_Ark_Number_day_Ark_Number_currentData_MonthData_preData_MonthData_nextData_MonthData_controller_Opt_CalendarController value;
} Opt_Literal_date_Literal_year_Ark_Number_month_Ark_Number_day_Ark_Number_currentData_MonthData_preData_MonthData_nextData_MonthData_controller_Opt_CalendarController;
typedef struct ButtonOptions {
    Opt_Ark_ButtonType type;
    Opt_Ark_Boolean stateEffect;
    Opt_Ark_ButtonStyleMode buttonStyle;
    Opt_Ark_ControlSize controlSize;
    Opt_Ark_ButtonRole role;
} ButtonOptions;
typedef struct Opt_ButtonOptions {
    enum Ark_Tag tag;
    ButtonOptions value;
} Opt_ButtonOptions;
typedef struct BadgeParamWithString {
    struct Opt_Union_Ark_BadgePosition_Position position;
    struct BadgeStyle style;
    Ark_String value;
} BadgeParamWithString;
typedef struct Opt_BadgeParamWithString {
    enum Ark_Tag tag;
    BadgeParamWithString value;
} Opt_BadgeParamWithString;
typedef struct BadgeParamWithNumber {
    struct Opt_Union_Ark_BadgePosition_Position position;
    struct BadgeStyle style;
    Ark_Number count;
    Opt_Ark_Number maxCount;
} BadgeParamWithNumber;
typedef struct Opt_BadgeParamWithNumber {
    enum Ark_Tag tag;
    BadgeParamWithNumber value;
} Opt_BadgeParamWithNumber;
typedef struct Union_SpringMotion_FrictionMotion_ScrollMotion {
    Ark_Int32 selector;
    union {
        struct SpringMotion value0;
        struct FrictionMotion value1;
        struct ScrollMotion value2;
    };
} Union_SpringMotion_FrictionMotion_ScrollMotion;
typedef struct Opt_Union_SpringMotion_FrictionMotion_ScrollMotion {
    enum Ark_Tag tag;
    Union_SpringMotion_FrictionMotion_ScrollMotion value;
} Opt_Union_SpringMotion_FrictionMotion_ScrollMotion;
typedef Ark_Int32 Ark_FillMode;
typedef struct Opt_Ark_FillMode { enum Ark_Tag tag; Ark_FillMode value; } Opt_Ark_FillMode;
typedef Ark_Int32 Ark_AnimationStatus;
typedef struct Opt_Ark_AnimationStatus { enum Ark_Tag tag; Ark_AnimationStatus value; } Opt_Ark_AnimationStatus;
typedef Ark_Int32 Ark_IndexerAlign;
typedef struct Opt_Ark_IndexerAlign { enum Ark_Tag tag; Ark_IndexerAlign value; } Opt_Ark_IndexerAlign;
typedef struct Literal_arrayValue_Array_Ark_String_selected_Ark_Number {
    struct Array_Ark_String arrayValue;
    Ark_Number selected;
} Literal_arrayValue_Array_Ark_String_selected_Ark_Number;
typedef struct Opt_Literal_arrayValue_Array_Ark_String_selected_Ark_Number {
    enum Ark_Tag tag;
    Literal_arrayValue_Array_Ark_String_selected_Ark_Number value;
} Opt_Literal_arrayValue_Array_Ark_String_selected_Ark_Number;
typedef struct Literal_want_Ark_CustomObject {
    Ark_CustomObject want;
} Literal_want_Ark_CustomObject;
typedef struct Opt_Literal_want_Ark_CustomObject {
    enum Ark_Tag tag;
    Literal_want_Ark_CustomObject value;
} Opt_Literal_want_Ark_CustomObject;
typedef struct BackgroundBrightnessOptions {
    Ark_Number rate;
    Ark_Number lightUpDegree;
} BackgroundBrightnessOptions;
typedef struct Opt_BackgroundBrightnessOptions {
    enum Ark_Tag tag;
    BackgroundBrightnessOptions value;
} Opt_BackgroundBrightnessOptions;
typedef Ark_Materialized GestureModifier;
typedef struct Opt_GestureModifier {
    enum Ark_Tag tag;
    GestureModifier value;
} Opt_GestureModifier;
typedef Ark_Int32 Ark_RenderFit;
typedef struct Opt_Ark_RenderFit { enum Ark_Tag tag; Ark_RenderFit value; } Opt_Ark_RenderFit;
typedef Ark_Int32 Ark_ObscuredReasons;
typedef struct Opt_Ark_ObscuredReasons { enum Ark_Tag tag; Ark_ObscuredReasons value; } Opt_Ark_ObscuredReasons;
typedef int32_t Ark_ObscuredReasons;
typedef struct Array_Ark_ObscuredReasons {
    Ark_ObscuredReasons* array;
    Ark_Int32 length;
} Array_Ark_ObscuredReasons;
typedef int32_t Ark_ObscuredReasons;
typedef struct Opt_Array_Ark_ObscuredReasons {
    enum Ark_Tag tag;
    Array_Ark_ObscuredReasons value;
} Opt_Array_Ark_ObscuredReasons;
typedef Ark_Int32 Ark_ModifierKey;
typedef struct Opt_Ark_ModifierKey { enum Ark_Tag tag; Ark_ModifierKey value; } Opt_Ark_ModifierKey;
typedef int32_t Ark_ModifierKey;
typedef struct Array_Ark_ModifierKey {
    Ark_ModifierKey* array;
    Ark_Int32 length;
} Array_Ark_ModifierKey;
typedef int32_t Ark_ModifierKey;
typedef struct Opt_Array_Ark_ModifierKey {
    enum Ark_Tag tag;
    Array_Ark_ModifierKey value;
} Opt_Array_Ark_ModifierKey;
typedef struct Union_Ark_String_Ark_FunctionKey {
    Ark_Int32 selector;
    union {
        Ark_String value0;
        Ark_FunctionKey value1;
    };
} Union_Ark_String_Ark_FunctionKey;
typedef struct Opt_Union_Ark_String_Ark_FunctionKey {
    enum Ark_Tag tag;
    Union_Ark_String_Ark_FunctionKey value;
} Opt_Union_Ark_String_Ark_FunctionKey;
typedef struct PixelStretchEffectOptions {
    Opt_Ark_Length top;
    Opt_Ark_Length bottom;
    Opt_Ark_Length left;
    Opt_Ark_Length right;
} PixelStretchEffectOptions;
typedef struct Opt_PixelStretchEffectOptions {
    enum Ark_Tag tag;
    PixelStretchEffectOptions value;
} Opt_PixelStretchEffectOptions;
typedef struct StateStyles {
    Opt_Ark_CustomObject normal;
    Opt_Ark_CustomObject pressed;
    Opt_Ark_CustomObject disabled;
    Opt_Ark_CustomObject focused;
    Opt_Ark_CustomObject clicked;
    Opt_Ark_CustomObject selected;
} StateStyles;
typedef struct Opt_StateStyles {
    enum Ark_Tag tag;
    StateStyles value;
} Opt_StateStyles;
typedef struct SheetOptions {
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource backgroundColor;
    struct Opt_Ark_Function onAppear;
    struct Opt_Ark_Function onDisappear;
    struct Opt_Ark_Function onWillAppear;
    struct Opt_Ark_Function onWillDisappear;
    struct Opt_Union_Ark_SheetSize_Ark_Length height;
    Opt_Ark_Boolean dragBar;
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource maskColor;
    struct Opt_Tuple_Union_Ark_SheetSize_Ark_Length_Opt_Union_Ark_SheetSize_Ark_Length_Opt_Union_Ark_SheetSize_Ark_Length detents;
    Opt_Ark_BlurStyle blurStyle;
    struct Opt_Union_Ark_Boolean_Ark_Resource showClose;
    Opt_Ark_SheetType preferType;
    struct Opt_Union_SheetTitleOptions_Union_Ark_Function_Ark_Undefined title;
    struct Opt_Ark_Function shouldDismiss;
    struct Opt_Ark_Function onWillDismiss;
    struct Opt_Ark_Function onWillSpringBackWhenDismiss;
    Opt_Ark_Boolean enableOutsideInteractive;
    Opt_Ark_Length width;
    struct Opt_Union_Ark_Length_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length_LocalizedEdgeWidths borderWidth;
    struct Opt_Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Literal_top_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_right_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_bottom_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_left_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_LocalizedEdgeColors borderColor;
    struct Opt_Union_Ark_BorderStyle_Literal_top_Opt_Ark_BorderStyle_right_Opt_Ark_BorderStyle_bottom_Opt_Ark_BorderStyle_left_Opt_Ark_BorderStyle borderStyle;
    struct Opt_Union_ShadowOptions_Ark_ShadowStyle shadow;
    struct Opt_Ark_Function onHeightDidChange;
    Opt_Ark_SheetMode mode;
    Opt_Ark_ScrollSizeMode scrollSizeMode;
    struct Opt_Ark_Function onDetentsDidChange;
    struct Opt_Ark_Function onWidthDidChange;
    struct Opt_Ark_Function onTypeDidChange;
    Opt_Ark_CustomObject uiContext;
} SheetOptions;
typedef struct Opt_SheetOptions {
    enum Ark_Tag tag;
    SheetOptions value;
} Opt_SheetOptions;
typedef struct ContentCoverOptions {
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource backgroundColor;
    struct Opt_Ark_Function onAppear;
    struct Opt_Ark_Function onDisappear;
    struct Opt_Ark_Function onWillAppear;
    struct Opt_Ark_Function onWillDisappear;
    Opt_Ark_ModalTransition modalTransition;
    struct Opt_Ark_Function onWillDismiss;
    struct Opt_TransitionEffect transition;
} ContentCoverOptions;
typedef struct Opt_ContentCoverOptions {
    enum Ark_Tag tag;
    ContentCoverOptions value;
} Opt_ContentCoverOptions;
typedef struct Union_Array_MenuElement_Union_Ark_Function_Ark_Undefined {
    Ark_Int32 selector;
    union {
        struct Array_MenuElement value0;
        struct Union_Ark_Function_Ark_Undefined value1;
    };
} Union_Array_MenuElement_Union_Ark_Function_Ark_Undefined;
typedef struct Opt_Union_Array_MenuElement_Union_Ark_Function_Ark_Undefined {
    enum Ark_Tag tag;
    Union_Array_MenuElement_Union_Ark_Function_Ark_Undefined value;
} Opt_Union_Array_MenuElement_Union_Ark_Function_Ark_Undefined;
typedef struct MenuOptions {
    struct Opt_Position offset;
    Opt_Ark_Placement placement;
    Opt_Ark_Boolean enableArrow;
    Opt_Ark_Length arrowOffset;
    struct Opt_Union_Ark_MenuPreviewMode_Union_Ark_Function_Ark_Undefined preview;
    struct Opt_Union_Ark_Length_Literal_topLeft_Opt_Ark_Length_topRight_Opt_Ark_Length_bottomLeft_Opt_Ark_Length_bottomRight_Opt_Ark_Length borderRadius;
    struct Opt_Ark_Function onAppear;
    struct Opt_Ark_Function onDisappear;
    struct Opt_Ark_Function aboutToAppear;
    struct Opt_Ark_Function aboutToDisappear;
    struct Opt_ContextMenuAnimationOptions previewAnimationOptions;
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource backgroundColor;
    Opt_Ark_BlurStyle backgroundBlurStyle;
    struct Opt_TransitionEffect transition;
    struct Opt_Union_Ark_String_Ark_Resource title;
    Opt_Ark_Boolean showInSubWindow;
} MenuOptions;
typedef struct Opt_MenuOptions {
    enum Ark_Tag tag;
    MenuOptions value;
} Opt_MenuOptions;
typedef struct MenuElement {
    struct Union_Ark_String_Ark_Resource value;
    struct Opt_Union_Ark_String_Ark_Resource icon;
    Opt_Ark_CustomObject symbolIcon;
    Opt_Ark_Boolean enabled;
    struct Ark_Function action;
} MenuElement;
typedef struct Opt_MenuElement {
    enum Ark_Tag tag;
    MenuElement value;
} Opt_MenuElement;
typedef struct Union_PopupOptions_CustomPopupOptions {
    Ark_Int32 selector;
    union {
        struct PopupOptions value0;
        struct CustomPopupOptions value1;
    };
} Union_PopupOptions_CustomPopupOptions;
typedef struct Opt_Union_PopupOptions_CustomPopupOptions {
    enum Ark_Tag tag;
    Union_PopupOptions_CustomPopupOptions value;
} Opt_Union_PopupOptions_CustomPopupOptions;
typedef struct GeometryTransitionOptions {
    Opt_Ark_Boolean follow;
    Opt_Ark_TransitionHierarchyStrategy hierarchyStrategy;
} GeometryTransitionOptions;
typedef struct Opt_GeometryTransitionOptions {
    enum Ark_Tag tag;
    GeometryTransitionOptions value;
} Opt_GeometryTransitionOptions;
typedef struct Union_Ark_CustomObject_Ark_CustomObject_Ark_CustomObject_Ark_CustomObject {
    Ark_Int32 selector;
    union {
        Ark_CustomObject value0;
        Ark_CustomObject value1;
        Ark_CustomObject value2;
        Ark_CustomObject value3;
    };
} Union_Ark_CustomObject_Ark_CustomObject_Ark_CustomObject_Ark_CustomObject;
typedef struct Opt_Union_Ark_CustomObject_Ark_CustomObject_Ark_CustomObject_Ark_CustomObject {
    enum Ark_Tag tag;
    Union_Ark_CustomObject_Ark_CustomObject_Ark_CustomObject_Ark_CustomObject value;
} Opt_Union_Ark_CustomObject_Ark_CustomObject_Ark_CustomObject_Ark_CustomObject;
typedef struct Union_CircleAttribute_EllipseAttribute_PathAttribute_RectAttribute_ProgressMask {
    Ark_Int32 selector;
    union {
        struct CircleAttribute value0;
        struct EllipseAttribute value1;
        struct PathAttribute value2;
        struct RectAttribute value3;
        ProgressMask value4;
    };
} Union_CircleAttribute_EllipseAttribute_PathAttribute_RectAttribute_ProgressMask;
typedef struct Opt_Union_CircleAttribute_EllipseAttribute_PathAttribute_RectAttribute_ProgressMask {
    enum Ark_Tag tag;
    Union_CircleAttribute_EllipseAttribute_PathAttribute_RectAttribute_ProgressMask value;
} Opt_Union_CircleAttribute_EllipseAttribute_PathAttribute_RectAttribute_ProgressMask;
typedef struct Union_Ark_Boolean_CircleAttribute_EllipseAttribute_PathAttribute_RectAttribute {
    Ark_Int32 selector;
    union {
        Ark_Boolean value0;
        struct CircleAttribute value1;
        struct EllipseAttribute value2;
        struct PathAttribute value3;
        struct RectAttribute value4;
    };
} Union_Ark_Boolean_CircleAttribute_EllipseAttribute_PathAttribute_RectAttribute;
typedef struct Opt_Union_Ark_Boolean_CircleAttribute_EllipseAttribute_PathAttribute_RectAttribute {
    enum Ark_Tag tag;
    Union_Ark_Boolean_CircleAttribute_EllipseAttribute_PathAttribute_RectAttribute value;
} Opt_Union_Ark_Boolean_CircleAttribute_EllipseAttribute_PathAttribute_RectAttribute;
typedef Ark_Int32 Ark_BlendApplyType;
typedef struct Opt_Ark_BlendApplyType { enum Ark_Tag tag; Ark_BlendApplyType value; } Opt_Ark_BlendApplyType;
typedef Ark_Int32 Ark_BlendMode;
typedef struct Opt_Ark_BlendMode { enum Ark_Tag tag; Ark_BlendMode value; } Opt_Ark_BlendMode;
typedef struct Tuple_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Ark_Number {
    struct Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource value0;
    Ark_Number value1;
} Tuple_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Ark_Number;
typedef struct Opt_Tuple_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Ark_Number {
    enum Ark_Tag tag;
    Tuple_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Ark_Number value;
} Opt_Tuple_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Ark_Number;
typedef struct Literal_center_Tuple_Ark_Length_Ark_Length_radius_Union_Ark_Number_Ark_String_colors_Array_Tuple_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Ark_Number_repeating_Opt_Ark_Boolean {
    struct Tuple_Ark_Length_Ark_Length center;
    struct Union_Ark_Number_Ark_String radius;
    struct Array_Tuple_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Ark_Number colors;
    Opt_Ark_Boolean repeating;
} Literal_center_Tuple_Ark_Length_Ark_Length_radius_Union_Ark_Number_Ark_String_colors_Array_Tuple_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Ark_Number_repeating_Opt_Ark_Boolean;
typedef struct Opt_Literal_center_Tuple_Ark_Length_Ark_Length_radius_Union_Ark_Number_Ark_String_colors_Array_Tuple_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Ark_Number_repeating_Opt_Ark_Boolean {
    enum Ark_Tag tag;
    Literal_center_Tuple_Ark_Length_Ark_Length_radius_Union_Ark_Number_Ark_String_colors_Array_Tuple_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Ark_Number_repeating_Opt_Ark_Boolean value;
} Opt_Literal_center_Tuple_Ark_Length_Ark_Length_radius_Union_Ark_Number_Ark_String_colors_Array_Tuple_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Ark_Number_repeating_Opt_Ark_Boolean;
typedef struct Literal_center_Tuple_Ark_Length_Ark_Length_start_Opt_Union_Ark_Number_Ark_String_end_Opt_Union_Ark_Number_Ark_String_rotation_Opt_Union_Ark_Number_Ark_String_colors_Array_Tuple_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Ark_Number_repeating_Opt_Ark_Boolean {
    struct Tuple_Ark_Length_Ark_Length center;
    struct Opt_Union_Ark_Number_Ark_String start;
    struct Opt_Union_Ark_Number_Ark_String end;
    struct Opt_Union_Ark_Number_Ark_String rotation;
    struct Array_Tuple_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Ark_Number colors;
    Opt_Ark_Boolean repeating;
} Literal_center_Tuple_Ark_Length_Ark_Length_start_Opt_Union_Ark_Number_Ark_String_end_Opt_Union_Ark_Number_Ark_String_rotation_Opt_Union_Ark_Number_Ark_String_colors_Array_Tuple_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Ark_Number_repeating_Opt_Ark_Boolean;
typedef struct Opt_Literal_center_Tuple_Ark_Length_Ark_Length_start_Opt_Union_Ark_Number_Ark_String_end_Opt_Union_Ark_Number_Ark_String_rotation_Opt_Union_Ark_Number_Ark_String_colors_Array_Tuple_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Ark_Number_repeating_Opt_Ark_Boolean {
    enum Ark_Tag tag;
    Literal_center_Tuple_Ark_Length_Ark_Length_start_Opt_Union_Ark_Number_Ark_String_end_Opt_Union_Ark_Number_Ark_String_rotation_Opt_Union_Ark_Number_Ark_String_colors_Array_Tuple_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Ark_Number_repeating_Opt_Ark_Boolean value;
} Opt_Literal_center_Tuple_Ark_Length_Ark_Length_start_Opt_Union_Ark_Number_Ark_String_end_Opt_Union_Ark_Number_Ark_String_rotation_Opt_Union_Ark_Number_Ark_String_colors_Array_Tuple_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Ark_Number_repeating_Opt_Ark_Boolean;
typedef struct Literal_angle_Opt_Union_Ark_Number_Ark_String_direction_Opt_Ark_GradientDirection_colors_Array_Tuple_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Ark_Number_repeating_Opt_Ark_Boolean {
    struct Opt_Union_Ark_Number_Ark_String angle;
    Opt_Ark_GradientDirection direction;
    struct Array_Tuple_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Ark_Number colors;
    Opt_Ark_Boolean repeating;
} Literal_angle_Opt_Union_Ark_Number_Ark_String_direction_Opt_Ark_GradientDirection_colors_Array_Tuple_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Ark_Number_repeating_Opt_Ark_Boolean;
typedef struct Opt_Literal_angle_Opt_Union_Ark_Number_Ark_String_direction_Opt_Ark_GradientDirection_colors_Array_Tuple_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Ark_Number_repeating_Opt_Ark_Boolean {
    enum Ark_Tag tag;
    Literal_angle_Opt_Union_Ark_Number_Ark_String_direction_Opt_Ark_GradientDirection_colors_Array_Tuple_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Ark_Number_repeating_Opt_Ark_Boolean value;
} Opt_Literal_angle_Opt_Union_Ark_Number_Ark_String_direction_Opt_Ark_GradientDirection_colors_Array_Tuple_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Ark_Number_repeating_Opt_Ark_Boolean;
typedef struct OverlayOptions {
    Opt_Ark_Alignment align;
    struct Opt_OverlayOffset offset;
} OverlayOptions;
typedef struct Opt_OverlayOptions {
    enum Ark_Tag tag;
    OverlayOptions value;
} Opt_OverlayOptions;
typedef struct Union_Ark_String_Union_Ark_Function_Ark_Undefined_Ark_CustomObject {
    Ark_Int32 selector;
    union {
        Ark_String value0;
        struct Union_Ark_Function_Ark_Undefined value1;
        Ark_CustomObject value2;
    };
} Union_Ark_String_Union_Ark_Function_Ark_Undefined_Ark_CustomObject;
typedef struct Opt_Union_Ark_String_Union_Ark_Function_Ark_Undefined_Ark_CustomObject {
    enum Ark_Tag tag;
    Union_Ark_String_Union_Ark_Function_Ark_Undefined_Ark_CustomObject value;
} Opt_Union_Ark_String_Union_Ark_Function_Ark_Undefined_Ark_CustomObject;
typedef struct DragInteractionOptions {
    Opt_Ark_Boolean isMultiSelectionEnabled;
    Opt_Ark_Boolean defaultAnimationBeforeLifting;
} DragInteractionOptions;
typedef struct Opt_DragInteractionOptions {
    enum Ark_Tag tag;
    DragInteractionOptions value;
} Opt_DragInteractionOptions;
typedef struct DragPreviewOptions {
    struct Opt_Union_Ark_DragPreviewMode_Array_Ark_DragPreviewMode mode;
    Opt_Ark_CustomObject modifier;
    struct Opt_Union_Ark_Boolean_Ark_Number numberBadge;
} DragPreviewOptions;
typedef struct Opt_DragPreviewOptions {
    enum Ark_Tag tag;
    DragPreviewOptions value;
} Opt_DragPreviewOptions;
typedef struct Union_Union_Ark_Function_Ark_Undefined_DragItemInfo_Ark_String {
    Ark_Int32 selector;
    union {
        struct Union_Ark_Function_Ark_Undefined value0;
        struct DragItemInfo value1;
        Ark_String value2;
    };
} Union_Union_Ark_Function_Ark_Undefined_DragItemInfo_Ark_String;
typedef struct Opt_Union_Union_Ark_Function_Ark_Undefined_DragItemInfo_Ark_String {
    enum Ark_Tag tag;
    Union_Union_Ark_Function_Ark_Undefined_DragItemInfo_Ark_String value;
} Opt_Union_Union_Ark_Function_Ark_Undefined_DragItemInfo_Ark_String;
typedef struct Union_Array_Ark_CustomObject_Ark_Undefined {
    Ark_Int32 selector;
    union {
        struct Array_Ark_CustomObject value0;
        struct Ark_Undefined value1;
    };
} Union_Array_Ark_CustomObject_Ark_Undefined;
typedef struct Opt_Union_Array_Ark_CustomObject_Ark_Undefined {
    enum Ark_Tag tag;
    Union_Array_Ark_CustomObject_Ark_Undefined value;
} Opt_Union_Array_Ark_CustomObject_Ark_Undefined;
typedef struct Union_ClickEffect_Ark_Undefined {
    Ark_Int32 selector;
    union {
        struct ClickEffect value0;
        struct Ark_Undefined value1;
    };
} Union_ClickEffect_Ark_Undefined;
typedef struct Opt_Union_ClickEffect_Ark_Undefined {
    enum Ark_Tag tag;
    Union_ClickEffect_Ark_Undefined value;
} Opt_Union_ClickEffect_Ark_Undefined;
typedef Ark_Int32 Ark_ChainStyle;
typedef struct Opt_Ark_ChainStyle { enum Ark_Tag tag; Ark_ChainStyle value; } Opt_Ark_ChainStyle;
typedef struct LocalizedAlignRuleOptions {
    struct Opt_LocalizedHorizontalAlignParam start;
    struct Opt_LocalizedHorizontalAlignParam end;
    struct Opt_LocalizedHorizontalAlignParam middle;
    struct Opt_LocalizedVerticalAlignParam top;
    struct Opt_LocalizedVerticalAlignParam bottom;
    struct Opt_LocalizedVerticalAlignParam center;
    struct Opt_Bias bias;
} LocalizedAlignRuleOptions;
typedef struct Opt_LocalizedAlignRuleOptions {
    enum Ark_Tag tag;
    LocalizedAlignRuleOptions value;
} Opt_LocalizedAlignRuleOptions;
typedef struct AlignRuleOption {
    struct Opt_Literal_anchor_Ark_String_align_Ark_HorizontalAlign left;
    struct Opt_Literal_anchor_Ark_String_align_Ark_HorizontalAlign right;
    struct Opt_Literal_anchor_Ark_String_align_Ark_HorizontalAlign middle;
    struct Opt_Literal_anchor_Ark_String_align_Ark_VerticalAlign top;
    struct Opt_Literal_anchor_Ark_String_align_Ark_VerticalAlign bottom;
    struct Opt_Literal_anchor_Ark_String_align_Ark_VerticalAlign center;
    struct Opt_Bias bias;
} AlignRuleOption;
typedef struct Opt_AlignRuleOption {
    enum Ark_Tag tag;
    AlignRuleOption value;
} Opt_AlignRuleOption;
typedef struct Literal_xs_Opt_Union_Ark_Number_Literal_span_Ark_Number_offset_Ark_Number_sm_Opt_Union_Ark_Number_Literal_span_Ark_Number_offset_Ark_Number_md_Opt_Union_Ark_Number_Literal_span_Ark_Number_offset_Ark_Number_lg_Opt_Union_Ark_Number_Literal_span_Ark_Number_offset_Ark_Number {
    struct Opt_Union_Ark_Number_Literal_span_Ark_Number_offset_Ark_Number xs;
    struct Opt_Union_Ark_Number_Literal_span_Ark_Number_offset_Ark_Number sm;
    struct Opt_Union_Ark_Number_Literal_span_Ark_Number_offset_Ark_Number md;
    struct Opt_Union_Ark_Number_Literal_span_Ark_Number_offset_Ark_Number lg;
} Literal_xs_Opt_Union_Ark_Number_Literal_span_Ark_Number_offset_Ark_Number_sm_Opt_Union_Ark_Number_Literal_span_Ark_Number_offset_Ark_Number_md_Opt_Union_Ark_Number_Literal_span_Ark_Number_offset_Ark_Number_lg_Opt_Union_Ark_Number_Literal_span_Ark_Number_offset_Ark_Number;
typedef struct Opt_Literal_xs_Opt_Union_Ark_Number_Literal_span_Ark_Number_offset_Ark_Number_sm_Opt_Union_Ark_Number_Literal_span_Ark_Number_offset_Ark_Number_md_Opt_Union_Ark_Number_Literal_span_Ark_Number_offset_Ark_Number_lg_Opt_Union_Ark_Number_Literal_span_Ark_Number_offset_Ark_Number {
    enum Ark_Tag tag;
    Literal_xs_Opt_Union_Ark_Number_Literal_span_Ark_Number_offset_Ark_Number_sm_Opt_Union_Ark_Number_Literal_span_Ark_Number_offset_Ark_Number_md_Opt_Union_Ark_Number_Literal_span_Ark_Number_offset_Ark_Number_lg_Opt_Union_Ark_Number_Literal_span_Ark_Number_offset_Ark_Number value;
} Opt_Literal_xs_Opt_Union_Ark_Number_Literal_span_Ark_Number_offset_Ark_Number_sm_Opt_Union_Ark_Number_Literal_span_Ark_Number_offset_Ark_Number_md_Opt_Union_Ark_Number_Literal_span_Ark_Number_offset_Ark_Number_lg_Opt_Union_Ark_Number_Literal_span_Ark_Number_offset_Ark_Number;
typedef struct Union_Position_LocalizedPosition {
    Ark_Int32 selector;
    union {
        struct Position value0;
        struct LocalizedPosition value1;
    };
} Union_Position_LocalizedPosition;
typedef struct Opt_Union_Position_LocalizedPosition {
    enum Ark_Tag tag;
    Union_Position_LocalizedPosition value;
} Opt_Union_Position_LocalizedPosition;
typedef Ark_Int32 Ark_Direction;
typedef struct Opt_Ark_Direction { enum Ark_Tag tag; Ark_Direction value; } Opt_Ark_Direction;
typedef struct sharedTransitionOptions {
    Opt_Ark_Number duration;
    struct Opt_Union_Ark_Curve_Ark_String_ICurve curve;
    Opt_Ark_Number delay;
    struct Opt_MotionPathOptions motionPath;
    Opt_Ark_Number zIndex;
    Opt_Ark_SharedTransitionEffectType type;
} sharedTransitionOptions;
typedef struct Opt_sharedTransitionOptions {
    enum Ark_Tag tag;
    sharedTransitionOptions value;
} Opt_sharedTransitionOptions;
typedef Ark_Int32 Ark_Visibility;
typedef struct Opt_Ark_Visibility { enum Ark_Tag tag; Ark_Visibility value; } Opt_Ark_Visibility;
typedef struct Union_Ark_Number_InvertOptions {
    Ark_Int32 selector;
    union {
        Ark_Number value0;
        struct InvertOptions value1;
    };
} Union_Ark_Number_InvertOptions;
typedef struct Opt_Union_Ark_Number_InvertOptions {
    enum Ark_Tag tag;
    Union_Ark_Number_InvertOptions value;
} Opt_Union_Ark_Number_InvertOptions;
typedef struct Union_Ark_Color_Ark_String_Ark_Resource {
    Ark_Int32 selector;
    union {
        Ark_Color value0;
        Ark_String value1;
        Ark_Resource value2;
    };
} Union_Ark_Color_Ark_String_Ark_Resource;
typedef struct Opt_Union_Ark_Color_Ark_String_Ark_Resource {
    enum Ark_Tag tag;
    Union_Ark_Color_Ark_String_Ark_Resource value;
} Opt_Union_Ark_Color_Ark_String_Ark_Resource;
typedef struct MotionBlurOptions {
    Ark_Number radius;
    struct MotionBlurAnchor anchor;
} MotionBlurOptions;
typedef struct Opt_MotionBlurOptions {
    enum Ark_Tag tag;
    MotionBlurOptions value;
} Opt_MotionBlurOptions;
typedef struct LinearGradientBlurOptions {
    struct Array_Tuple_Ark_Number_Ark_Number fractionStops;
    Ark_GradientDirection direction;
} LinearGradientBlurOptions;
typedef struct Opt_LinearGradientBlurOptions {
    enum Ark_Tag tag;
    LinearGradientBlurOptions value;
} Opt_LinearGradientBlurOptions;
typedef Ark_Int32 Ark_GestureMask;
typedef struct Opt_Ark_GestureMask { enum Ark_Tag tag; Ark_GestureMask value; } Opt_Ark_GestureMask;
typedef struct Union_TapGestureInterface_LongPressGestureInterface_PanGestureInterface_PinchGestureInterface_SwipeGestureInterface_RotationGestureInterface_GestureGroupInterface {
    Ark_Int32 selector;
    union {
        struct TapGestureInterface value0;
        struct LongPressGestureInterface value1;
        struct PanGestureInterface value2;
        struct PinchGestureInterface value3;
        struct SwipeGestureInterface value4;
        struct RotationGestureInterface value5;
        struct GestureGroupInterface value6;
    };
} Union_TapGestureInterface_LongPressGestureInterface_PanGestureInterface_PinchGestureInterface_SwipeGestureInterface_RotationGestureInterface_GestureGroupInterface;
typedef struct Opt_Union_TapGestureInterface_LongPressGestureInterface_PanGestureInterface_PinchGestureInterface_SwipeGestureInterface_RotationGestureInterface_GestureGroupInterface {
    enum Ark_Tag tag;
    Union_TapGestureInterface_LongPressGestureInterface_PanGestureInterface_PinchGestureInterface_SwipeGestureInterface_RotationGestureInterface_GestureGroupInterface value;
} Opt_Union_TapGestureInterface_LongPressGestureInterface_PanGestureInterface_PinchGestureInterface_SwipeGestureInterface_RotationGestureInterface_GestureGroupInterface;
typedef struct Union_TransitionOptions_TransitionEffect {
    Ark_Int32 selector;
    union {
        struct TransitionOptions value0;
        struct TransitionEffect value1;
    };
} Union_TransitionOptions_TransitionEffect;
typedef struct Opt_Union_TransitionOptions_TransitionEffect {
    enum Ark_Tag tag;
    Union_TransitionOptions_TransitionEffect value;
} Opt_Union_TransitionOptions_TransitionEffect;
typedef struct AnimateParam {
    Opt_Ark_Number duration;
    Opt_Ark_Number tempo;
    struct Opt_Union_Ark_Curve_Ark_String_ICurve curve;
    Opt_Ark_Number delay;
    Opt_Ark_Number iterations;
    Opt_Ark_PlayMode playMode;
    struct Opt_Ark_Function onFinish;
    Opt_Ark_FinishCallbackType finishCallbackType;
    struct Opt_ExpectedFrameRateRange expectedFrameRateRange;
} AnimateParam;
typedef struct Opt_AnimateParam {
    enum Ark_Tag tag;
    AnimateParam value;
} Opt_AnimateParam;
typedef Ark_Int32 Ark_FocusPriority;
typedef struct Opt_Ark_FocusPriority { enum Ark_Tag tag; Ark_FocusPriority value; } Opt_Ark_FocusPriority;
typedef struct FocusBoxStyle {
    Opt_Ark_CustomObject margin;
    Opt_Ark_CustomObject strokeColor;
    Opt_Ark_CustomObject strokeWidth;
} FocusBoxStyle;
typedef struct Opt_FocusBoxStyle {
    enum Ark_Tag tag;
    FocusBoxStyle value;
} Opt_FocusBoxStyle;
typedef Ark_Int32 Ark_HoverEffect;
typedef struct Opt_Ark_HoverEffect { enum Ark_Tag tag; Ark_HoverEffect value; } Opt_Ark_HoverEffect;
typedef struct Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Ark_ColoringStrategy {
    Ark_Int32 selector;
    union {
        struct Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource value0;
        Ark_ColoringStrategy value1;
    };
} Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Ark_ColoringStrategy;
typedef struct Opt_Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Ark_ColoringStrategy {
    enum Ark_Tag tag;
    Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Ark_ColoringStrategy value;
} Opt_Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Ark_ColoringStrategy;
typedef struct Union_Ark_OutlineStyle_Literal_top_Opt_Ark_OutlineStyle_right_Opt_Ark_OutlineStyle_bottom_Opt_Ark_OutlineStyle_left_Opt_Ark_OutlineStyle {
    Ark_Int32 selector;
    union {
        Ark_OutlineStyle value0;
        struct Literal_top_Opt_Ark_OutlineStyle_right_Opt_Ark_OutlineStyle_bottom_Opt_Ark_OutlineStyle_left_Opt_Ark_OutlineStyle value1;
    };
} Union_Ark_OutlineStyle_Literal_top_Opt_Ark_OutlineStyle_right_Opt_Ark_OutlineStyle_bottom_Opt_Ark_OutlineStyle_left_Opt_Ark_OutlineStyle;
typedef struct Opt_Union_Ark_OutlineStyle_Literal_top_Opt_Ark_OutlineStyle_right_Opt_Ark_OutlineStyle_bottom_Opt_Ark_OutlineStyle_left_Opt_Ark_OutlineStyle {
    enum Ark_Tag tag;
    Union_Ark_OutlineStyle_Literal_top_Opt_Ark_OutlineStyle_right_Opt_Ark_OutlineStyle_bottom_Opt_Ark_OutlineStyle_left_Opt_Ark_OutlineStyle value;
} Opt_Union_Ark_OutlineStyle_Literal_top_Opt_Ark_OutlineStyle_right_Opt_Ark_OutlineStyle_bottom_Opt_Ark_OutlineStyle_left_Opt_Ark_OutlineStyle;
typedef struct OutlineOptions {
    struct Opt_Union_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length_Ark_Length width;
    struct Opt_Union_Literal_top_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_right_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_bottom_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_left_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_LocalizedEdgeColors color;
    struct Opt_Union_Literal_topLeft_Opt_Ark_Length_topRight_Opt_Ark_Length_bottomLeft_Opt_Ark_Length_bottomRight_Opt_Ark_Length_Ark_Length radius;
    struct Opt_Union_Literal_top_Opt_Ark_OutlineStyle_right_Opt_Ark_OutlineStyle_bottom_Opt_Ark_OutlineStyle_left_Opt_Ark_OutlineStyle_Ark_OutlineStyle style;
} OutlineOptions;
typedef struct Opt_OutlineOptions {
    enum Ark_Tag tag;
    OutlineOptions value;
} Opt_OutlineOptions;
typedef struct BorderImageOption {
    struct Opt_Union_Ark_Length_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length_LocalizedEdgeWidths slice;
    Opt_Ark_RepeatMode repeat;
    struct Opt_Union_Ark_String_Ark_Resource_LinearGradient source;
    struct Opt_Union_Ark_Length_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length_LocalizedEdgeWidths width;
    struct Opt_Union_Ark_Length_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length_LocalizedEdgeWidths outset;
    Opt_Ark_Boolean fill;
} BorderImageOption;
typedef struct Opt_BorderImageOption {
    enum Ark_Tag tag;
    BorderImageOption value;
} Opt_BorderImageOption;
typedef struct Union_Ark_Length_Literal_topLeft_Opt_Ark_Length_topRight_Opt_Ark_Length_bottomLeft_Opt_Ark_Length_bottomRight_Opt_Ark_Length_LocalizedBorderRadiuses {
    Ark_Int32 selector;
    union {
        Ark_Length value0;
        struct Literal_topLeft_Opt_Ark_Length_topRight_Opt_Ark_Length_bottomLeft_Opt_Ark_Length_bottomRight_Opt_Ark_Length value1;
        struct LocalizedBorderRadiuses value2;
    };
} Union_Ark_Length_Literal_topLeft_Opt_Ark_Length_topRight_Opt_Ark_Length_bottomLeft_Opt_Ark_Length_bottomRight_Opt_Ark_Length_LocalizedBorderRadiuses;
typedef struct Opt_Union_Ark_Length_Literal_topLeft_Opt_Ark_Length_topRight_Opt_Ark_Length_bottomLeft_Opt_Ark_Length_bottomRight_Opt_Ark_Length_LocalizedBorderRadiuses {
    enum Ark_Tag tag;
    Union_Ark_Length_Literal_topLeft_Opt_Ark_Length_topRight_Opt_Ark_Length_bottomLeft_Opt_Ark_Length_bottomRight_Opt_Ark_Length_LocalizedBorderRadiuses value;
} Opt_Union_Ark_Length_Literal_topLeft_Opt_Ark_Length_topRight_Opt_Ark_Length_bottomLeft_Opt_Ark_Length_bottomRight_Opt_Ark_Length_LocalizedBorderRadiuses;
typedef struct BorderOptions {
    struct Opt_Union_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length_Ark_Length_LocalizedEdgeWidths width;
    struct Opt_Union_Literal_top_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_right_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_bottom_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_left_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_LocalizedEdgeColors color;
    struct Opt_Union_Literal_topLeft_Opt_Ark_Length_topRight_Opt_Ark_Length_bottomLeft_Opt_Ark_Length_bottomRight_Opt_Ark_Length_Ark_Length_LocalizedBorderRadiuses radius;
    struct Opt_Union_Literal_top_Opt_Ark_BorderStyle_right_Opt_Ark_BorderStyle_bottom_Opt_Ark_BorderStyle_left_Opt_Ark_BorderStyle_Ark_BorderStyle style;
    struct Opt_Union_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length_Ark_CustomObject_LocalizedEdgeWidths dashGap;
    struct Opt_Union_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length_Ark_CustomObject_LocalizedEdgeWidths dashWidth;
} BorderOptions;
typedef struct Opt_BorderOptions {
    enum Ark_Tag tag;
    BorderOptions value;
} Opt_BorderOptions;
typedef struct ForegroundBlurStyleOptions {
    Opt_Ark_ThemeColorMode colorMode;
    Opt_Ark_AdaptiveColor adaptiveColor;
    Opt_Ark_Number scale;
    struct Opt_BlurOptions blurOptions;
} ForegroundBlurStyleOptions;
typedef struct Opt_ForegroundBlurStyleOptions {
    enum Ark_Tag tag;
    ForegroundBlurStyleOptions value;
} Opt_ForegroundBlurStyleOptions;
typedef struct ForegroundEffectOptions {
    Ark_Number radius;
} ForegroundEffectOptions;
typedef struct Opt_ForegroundEffectOptions {
    enum Ark_Tag tag;
    ForegroundEffectOptions value;
} Opt_ForegroundEffectOptions;
typedef struct ResizableOptions {
    struct Opt_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length slice;
} ResizableOptions;
typedef struct Opt_ResizableOptions {
    enum Ark_Tag tag;
    ResizableOptions value;
} Opt_ResizableOptions;
typedef struct BackgroundEffectOptions {
    Ark_Number radius;
    Opt_Ark_Number saturation;
    Opt_Ark_Number brightness;
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource color;
    Opt_Ark_AdaptiveColor adaptiveColor;
    struct Opt_BlurOptions blurOptions;
    Opt_Ark_BlurStyleActivePolicy policy;
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource inactiveColor;
    Opt_Ark_BlurType type;
} BackgroundEffectOptions;
typedef struct Opt_BackgroundEffectOptions {
    enum Ark_Tag tag;
    BackgroundEffectOptions value;
} Opt_BackgroundEffectOptions;
typedef struct BackgroundBlurStyleOptions {
    Opt_Ark_ThemeColorMode colorMode;
    Opt_Ark_AdaptiveColor adaptiveColor;
    Opt_Ark_Number scale;
    struct Opt_BlurOptions blurOptions;
    Opt_Ark_BlurStyleActivePolicy policy;
    struct Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource inactiveColor;
    Opt_Ark_BlurType type;
} BackgroundBlurStyleOptions;
typedef struct Opt_BackgroundBlurStyleOptions {
    enum Ark_Tag tag;
    BackgroundBlurStyleOptions value;
} Opt_BackgroundBlurStyleOptions;
typedef struct Union_Position_Ark_Alignment {
    Ark_Int32 selector;
    union {
        struct Position value0;
        Ark_Alignment value1;
    };
} Union_Position_Ark_Alignment;
typedef struct Opt_Union_Position_Ark_Alignment {
    enum Ark_Tag tag;
    Union_Position_Ark_Alignment value;
} Opt_Union_Position_Ark_Alignment;
typedef struct Union_SizeOptions_Ark_ImageSize {
    Ark_Int32 selector;
    union {
        struct SizeOptions value0;
        Ark_ImageSize value1;
    };
} Union_SizeOptions_Ark_ImageSize;
typedef struct Opt_Union_SizeOptions_Ark_ImageSize {
    enum Ark_Tag tag;
    Union_SizeOptions_Ark_ImageSize value;
} Opt_Union_SizeOptions_Ark_ImageSize;
typedef Ark_Int32 Ark_ImageRepeat;
typedef struct Opt_Ark_ImageRepeat { enum Ark_Tag tag; Ark_ImageRepeat value; } Opt_Ark_ImageRepeat;
typedef struct PixelRoundPolicy {
    Opt_Ark_PixelRoundCalcPolicy start;
    Opt_Ark_PixelRoundCalcPolicy top;
    Opt_Ark_PixelRoundCalcPolicy end;
    Opt_Ark_PixelRoundCalcPolicy bottom;
} PixelRoundPolicy;
typedef struct Opt_PixelRoundPolicy {
    enum Ark_Tag tag;
    PixelRoundPolicy value;
} Opt_PixelRoundPolicy;
typedef struct Literal_align_Opt_Ark_Alignment {
    Opt_Ark_Alignment align;
} Literal_align_Opt_Ark_Alignment;
typedef struct Opt_Literal_align_Opt_Ark_Alignment {
    enum Ark_Tag tag;
    Literal_align_Opt_Ark_Alignment value;
} Opt_Literal_align_Opt_Ark_Alignment;
typedef Ark_Int32 Ark_HitTestMode;
typedef struct Opt_Ark_HitTestMode { enum Ark_Tag tag; Ark_HitTestMode value; } Opt_Ark_HitTestMode;
typedef struct ConstraintSizeOptions {
    Opt_Ark_Length minWidth;
    Opt_Ark_Length maxWidth;
    Opt_Ark_Length minHeight;
    Opt_Ark_Length maxHeight;
} ConstraintSizeOptions;
typedef struct Opt_ConstraintSizeOptions {
    enum Ark_Tag tag;
    ConstraintSizeOptions value;
} Opt_ConstraintSizeOptions;
typedef struct Union_Array_Rectangle_Rectangle {
    Ark_Int32 selector;
    union {
        struct Array_Rectangle value0;
        struct Rectangle value1;
    };
} Union_Array_Rectangle_Rectangle;
typedef struct Opt_Union_Array_Rectangle_Rectangle {
    enum Ark_Tag tag;
    Union_Array_Rectangle_Rectangle value;
} Opt_Union_Array_Rectangle_Rectangle;
typedef Ark_Int32 Ark_SafeAreaEdge;
typedef struct Opt_Ark_SafeAreaEdge { enum Ark_Tag tag; Ark_SafeAreaEdge value; } Opt_Ark_SafeAreaEdge;
typedef int32_t Ark_SafeAreaEdge;
typedef struct Array_Ark_SafeAreaEdge {
    Ark_SafeAreaEdge* array;
    Ark_Int32 length;
} Array_Ark_SafeAreaEdge;
typedef int32_t Ark_SafeAreaEdge;
typedef struct Opt_Array_Ark_SafeAreaEdge {
    enum Ark_Tag tag;
    Array_Ark_SafeAreaEdge value;
} Opt_Array_Ark_SafeAreaEdge;
typedef Ark_Int32 Ark_SafeAreaType;
typedef struct Opt_Ark_SafeAreaType { enum Ark_Tag tag; Ark_SafeAreaType value; } Opt_Ark_SafeAreaType;
typedef int32_t Ark_SafeAreaType;
typedef struct Array_Ark_SafeAreaType {
    Ark_SafeAreaType* array;
    Ark_Int32 length;
} Array_Ark_SafeAreaType;
typedef int32_t Ark_SafeAreaType;
typedef struct Opt_Array_Ark_SafeAreaType {
    enum Ark_Tag tag;
    Array_Ark_SafeAreaType value;
} Opt_Array_Ark_SafeAreaType;
typedef struct Union_DrawModifier_Ark_Undefined {
    Ark_Int32 selector;
    union {
        DrawModifier value0;
        Ark_Undefined value1;
    };
} Union_DrawModifier_Ark_Undefined;
typedef struct Opt_Union_DrawModifier_Ark_Undefined {
    enum Ark_Tag tag;
    Union_DrawModifier_Ark_Undefined value;
} Opt_Union_DrawModifier_Ark_Undefined;

typedef Union_DrawModifier_Ark_Undefined Type_CommonMethod_drawModifier_Arg0;
typedef Opt_Union_DrawModifier_Ark_Undefined Opt_Type_CommonMethod_drawModifier_Arg0;
typedef Opt_Object Optional;
typedef Union_Array_Rectangle_Rectangle Type_CommonMethod_responseRegion_Arg0;
typedef Opt_Union_Array_Rectangle_Rectangle Opt_Type_CommonMethod_responseRegion_Arg0;
typedef Union_Array_Rectangle_Rectangle Type_CommonMethod_mouseResponseRegion_Arg0;
typedef Opt_Union_Array_Rectangle_Rectangle Opt_Type_CommonMethod_mouseResponseRegion_Arg0;
typedef Union_Ark_Number_Ark_String Type_CommonMethod_layoutWeight_Arg0;
typedef Opt_Union_Ark_Number_Ark_String Opt_Type_CommonMethod_layoutWeight_Arg0;
typedef Union_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length_Ark_Length_LocalizedPadding Type_CommonMethod_padding_Arg0;
typedef Opt_Union_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length_Ark_Length_LocalizedPadding Opt_Type_CommonMethod_padding_Arg0;
typedef Ark_CustomObject LengthMetrics;
typedef Opt_Ark_CustomObject Opt_LengthMetrics;
typedef Union_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length_Ark_Length_LocalizedPadding Type_CommonMethod_margin_Arg0;
typedef Opt_Union_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length_Ark_Length_LocalizedPadding Opt_Type_CommonMethod_margin_Arg0;
typedef Union_Ark_Function_Ark_Undefined CustomBuilder;
typedef Opt_Union_Ark_Function_Ark_Undefined Opt_CustomBuilder;
typedef Literal_align_Opt_Ark_Alignment Type_CommonMethod_background_Arg1;
typedef Opt_Literal_align_Opt_Ark_Alignment Opt_Type_CommonMethod_background_Arg1;
typedef Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource ResourceColor;
typedef Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource Opt_ResourceColor;
typedef Union_Union_Ark_String_Ark_Resource_Ark_CustomObject Type_CommonMethod_backgroundImage_Arg0;
typedef Opt_Union_Union_Ark_String_Ark_Resource_Ark_CustomObject Opt_Type_CommonMethod_backgroundImage_Arg0;
typedef Union_SizeOptions_Ark_ImageSize Type_CommonMethod_backgroundImageSize_Arg0;
typedef Opt_Union_SizeOptions_Ark_ImageSize Opt_Type_CommonMethod_backgroundImageSize_Arg0;
typedef Union_Position_Ark_Alignment Type_CommonMethod_backgroundImagePosition_Arg0;
typedef Opt_Union_Position_Ark_Alignment Opt_Type_CommonMethod_backgroundImagePosition_Arg0;
typedef Ark_CustomObject VisualEffect;
typedef Opt_Ark_CustomObject Opt_VisualEffect;
typedef Ark_CustomObject Filter;
typedef Opt_Ark_CustomObject Opt_Filter;
typedef Union_Ark_Number_Ark_Resource Type_CommonMethod_opacity_Arg0;
typedef Opt_Union_Ark_Number_Ark_Resource Opt_Type_CommonMethod_opacity_Arg0;
typedef Union_Ark_BorderStyle_Literal_top_Opt_Ark_BorderStyle_right_Opt_Ark_BorderStyle_bottom_Opt_Ark_BorderStyle_left_Opt_Ark_BorderStyle Type_CommonMethod_borderStyle_Arg0;
typedef Opt_Union_Ark_BorderStyle_Literal_top_Opt_Ark_BorderStyle_right_Opt_Ark_BorderStyle_bottom_Opt_Ark_BorderStyle_left_Opt_Ark_BorderStyle Opt_Type_CommonMethod_borderStyle_Arg0;
typedef Union_Ark_Length_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length_LocalizedEdgeWidths Type_CommonMethod_borderWidth_Arg0;
typedef Opt_Union_Ark_Length_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length_LocalizedEdgeWidths Opt_Type_CommonMethod_borderWidth_Arg0;
typedef Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Literal_top_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_right_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_bottom_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_left_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_LocalizedEdgeColors Type_CommonMethod_borderColor_Arg0;
typedef Opt_Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Literal_top_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_right_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_bottom_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_left_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_LocalizedEdgeColors Opt_Type_CommonMethod_borderColor_Arg0;
typedef Union_Ark_Length_Literal_topLeft_Opt_Ark_Length_topRight_Opt_Ark_Length_bottomLeft_Opt_Ark_Length_bottomRight_Opt_Ark_Length_LocalizedBorderRadiuses Type_CommonMethod_borderRadius_Arg0;
typedef Opt_Union_Ark_Length_Literal_topLeft_Opt_Ark_Length_topRight_Opt_Ark_Length_bottomLeft_Opt_Ark_Length_bottomRight_Opt_Ark_Length_LocalizedBorderRadiuses Opt_Type_CommonMethod_borderRadius_Arg0;
typedef Union_Ark_OutlineStyle_Literal_top_Opt_Ark_OutlineStyle_right_Opt_Ark_OutlineStyle_bottom_Opt_Ark_OutlineStyle_left_Opt_Ark_OutlineStyle Type_CommonMethod_outlineStyle_Arg0;
typedef Opt_Union_Ark_OutlineStyle_Literal_top_Opt_Ark_OutlineStyle_right_Opt_Ark_OutlineStyle_bottom_Opt_Ark_OutlineStyle_left_Opt_Ark_OutlineStyle Opt_Type_CommonMethod_outlineStyle_Arg0;
typedef Union_Ark_Length_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length Type_CommonMethod_outlineWidth_Arg0;
typedef Opt_Union_Ark_Length_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length Opt_Type_CommonMethod_outlineWidth_Arg0;
typedef Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Literal_top_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_right_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_bottom_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_left_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_LocalizedEdgeColors Type_CommonMethod_outlineColor_Arg0;
typedef Opt_Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Literal_top_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_right_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_bottom_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_left_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_LocalizedEdgeColors Opt_Type_CommonMethod_outlineColor_Arg0;
typedef Union_Ark_Length_Literal_topLeft_Opt_Ark_Length_topRight_Opt_Ark_Length_bottomLeft_Opt_Ark_Length_bottomRight_Opt_Ark_Length Type_CommonMethod_outlineRadius_Arg0;
typedef Opt_Union_Ark_Length_Literal_topLeft_Opt_Ark_Length_topRight_Opt_Ark_Length_bottomLeft_Opt_Ark_Length_bottomRight_Opt_Ark_Length Opt_Type_CommonMethod_outlineRadius_Arg0;
typedef Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Ark_ColoringStrategy Type_CommonMethod_foregroundColor_Arg0;
typedef Opt_Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Ark_ColoringStrategy Opt_Type_CommonMethod_foregroundColor_Arg0;
typedef Ark_Function Callback;
typedef Opt_Ark_Function Opt_Callback;
typedef Union_TransitionOptions_TransitionEffect Type_CommonMethod_transition_Arg0;
typedef Opt_Union_TransitionOptions_TransitionEffect Opt_Type_CommonMethod_transition_Arg0;
typedef Union_TapGestureInterface_LongPressGestureInterface_PanGestureInterface_PinchGestureInterface_SwipeGestureInterface_RotationGestureInterface_GestureGroupInterface GestureType;
typedef Opt_Union_TapGestureInterface_LongPressGestureInterface_PanGestureInterface_PinchGestureInterface_SwipeGestureInterface_RotationGestureInterface_GestureGroupInterface Opt_GestureType;
typedef Union_Ark_Color_Ark_String_Ark_Resource Type_CommonMethod_colorBlend_Arg0;
typedef Opt_Union_Ark_Color_Ark_String_Ark_Resource Opt_Type_CommonMethod_colorBlend_Arg0;
typedef Union_Ark_Number_InvertOptions Type_CommonMethod_invert_Arg0;
typedef Opt_Union_Ark_Number_InvertOptions Opt_Type_CommonMethod_invert_Arg0;
typedef Union_Ark_Number_Ark_String Type_CommonMethod_hueRotate_Arg0;
typedef Opt_Union_Ark_Number_Ark_String Opt_Type_CommonMethod_hueRotate_Arg0;
typedef Union_Ark_Number_Ark_String Type_CommonMethod_flexBasis_Arg0;
typedef Opt_Union_Ark_Number_Ark_String Opt_Type_CommonMethod_flexBasis_Arg0;
typedef Union_Position_Edges_LocalizedEdges Type_CommonMethod_position_Arg0;
typedef Opt_Union_Position_Edges_LocalizedEdges Opt_Type_CommonMethod_position_Arg0;
typedef Union_Position_LocalizedPosition Type_CommonMethod_markAnchor_Arg0;
typedef Opt_Union_Position_LocalizedPosition Opt_Type_CommonMethod_markAnchor_Arg0;
typedef Union_Position_Edges_LocalizedEdges Type_CommonMethod_offset_Arg0;
typedef Opt_Union_Position_Edges_LocalizedEdges Opt_Type_CommonMethod_offset_Arg0;
typedef Literal_xs_Opt_Union_Ark_Number_Literal_span_Ark_Number_offset_Ark_Number_sm_Opt_Union_Ark_Number_Literal_span_Ark_Number_offset_Ark_Number_md_Opt_Union_Ark_Number_Literal_span_Ark_Number_offset_Ark_Number_lg_Opt_Union_Ark_Number_Literal_span_Ark_Number_offset_Ark_Number Type_CommonMethod_useSizeType_Arg0;
typedef Opt_Literal_xs_Opt_Union_Ark_Number_Literal_span_Ark_Number_offset_Ark_Number_sm_Opt_Union_Ark_Number_Literal_span_Ark_Number_offset_Ark_Number_md_Opt_Union_Ark_Number_Literal_span_Ark_Number_offset_Ark_Number_lg_Opt_Union_Ark_Number_Literal_span_Ark_Number_offset_Ark_Number Opt_Type_CommonMethod_useSizeType_Arg0;
typedef Union_ClickEffect_Ark_Undefined Type_CommonMethod_clickEffect_Arg0;
typedef Opt_Union_ClickEffect_Ark_Undefined Opt_Type_CommonMethod_clickEffect_Arg0;
typedef Union_Array_Ark_CustomObject_Ark_Undefined Type_CommonMethod_allowDrop_Arg0;
typedef Opt_Union_Array_Ark_CustomObject_Ark_Undefined Opt_Type_CommonMethod_allowDrop_Arg0;
typedef Union_Union_Ark_Function_Ark_Undefined_DragItemInfo_Ark_String Type_CommonMethod_dragPreview_Arg0;
typedef Opt_Union_Union_Ark_Function_Ark_Undefined_DragItemInfo_Ark_String Opt_Type_CommonMethod_dragPreview_Arg0;
typedef Union_Ark_String_Union_Ark_Function_Ark_Undefined_Ark_CustomObject Type_CommonMethod_overlay_Arg0;
typedef Opt_Union_Ark_String_Union_Ark_Function_Ark_Undefined_Ark_CustomObject Opt_Type_CommonMethod_overlay_Arg0;
typedef Literal_angle_Opt_Union_Ark_Number_Ark_String_direction_Opt_Ark_GradientDirection_colors_Array_Tuple_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Ark_Number_repeating_Opt_Ark_Boolean Type_CommonMethod_linearGradient_Arg0;
typedef Opt_Literal_angle_Opt_Union_Ark_Number_Ark_String_direction_Opt_Ark_GradientDirection_colors_Array_Tuple_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Ark_Number_repeating_Opt_Ark_Boolean Opt_Type_CommonMethod_linearGradient_Arg0;
typedef Literal_center_Tuple_Ark_Length_Ark_Length_start_Opt_Union_Ark_Number_Ark_String_end_Opt_Union_Ark_Number_Ark_String_rotation_Opt_Union_Ark_Number_Ark_String_colors_Array_Tuple_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Ark_Number_repeating_Opt_Ark_Boolean Type_CommonMethod_sweepGradient_Arg0;
typedef Opt_Literal_center_Tuple_Ark_Length_Ark_Length_start_Opt_Union_Ark_Number_Ark_String_end_Opt_Union_Ark_Number_Ark_String_rotation_Opt_Union_Ark_Number_Ark_String_colors_Array_Tuple_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Ark_Number_repeating_Opt_Ark_Boolean Opt_Type_CommonMethod_sweepGradient_Arg0;
typedef Literal_center_Tuple_Ark_Length_Ark_Length_radius_Union_Ark_Number_Ark_String_colors_Array_Tuple_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Ark_Number_repeating_Opt_Ark_Boolean Type_CommonMethod_radialGradient_Arg0;
typedef Opt_Literal_center_Tuple_Ark_Length_Ark_Length_radius_Union_Ark_Number_Ark_String_colors_Array_Tuple_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_Ark_Number_repeating_Opt_Ark_Boolean Opt_Type_CommonMethod_radialGradient_Arg0;
typedef Union_ShadowOptions_Ark_ShadowStyle Type_CommonMethod_shadow_Arg0;
typedef Opt_Union_ShadowOptions_Ark_ShadowStyle Opt_Type_CommonMethod_shadow_Arg0;
typedef Union_Ark_Boolean_CircleAttribute_EllipseAttribute_PathAttribute_RectAttribute Type_CommonMethod_clip1_Arg0;
typedef Opt_Union_Ark_Boolean_CircleAttribute_EllipseAttribute_PathAttribute_RectAttribute Opt_Type_CommonMethod_clip1_Arg0;
typedef Union_Ark_CustomObject_Ark_CustomObject_Ark_CustomObject_Ark_CustomObject Type_CommonMethod_clipShape_Arg0;
typedef Opt_Union_Ark_CustomObject_Ark_CustomObject_Ark_CustomObject_Ark_CustomObject Opt_Type_CommonMethod_clipShape_Arg0;
typedef Union_CircleAttribute_EllipseAttribute_PathAttribute_RectAttribute_ProgressMask Type_CommonMethod_mask1_Arg0;
typedef Opt_Union_CircleAttribute_EllipseAttribute_PathAttribute_RectAttribute_ProgressMask Opt_Type_CommonMethod_mask1_Arg0;
typedef Union_Ark_CustomObject_Ark_CustomObject_Ark_CustomObject_Ark_CustomObject Type_CommonMethod_maskShape_Arg0;
typedef Opt_Union_Ark_CustomObject_Ark_CustomObject_Ark_CustomObject_Ark_CustomObject Opt_Type_CommonMethod_maskShape_Arg0;
typedef Union_PopupOptions_CustomPopupOptions Type_CommonMethod_bindPopup_Arg1;
typedef Opt_Union_PopupOptions_CustomPopupOptions Opt_Type_CommonMethod_bindPopup_Arg1;
typedef Union_Array_MenuElement_Union_Ark_Function_Ark_Undefined Type_CommonMethod_bindMenu_Arg0;
typedef Opt_Union_Array_MenuElement_Union_Ark_Function_Ark_Undefined Opt_Type_CommonMethod_bindMenu_Arg0;
typedef Union_Array_MenuElement_Union_Ark_Function_Ark_Undefined Type_CommonMethod_bindMenu1_Arg1;
typedef Opt_Union_Array_MenuElement_Union_Ark_Function_Ark_Undefined Opt_Type_CommonMethod_bindMenu1_Arg1;
typedef Union_Ark_String_Ark_FunctionKey Type_CommonMethod_keyboardShortcut_Arg0;
typedef Opt_Union_Ark_String_Ark_FunctionKey Opt_Type_CommonMethod_keyboardShortcut_Arg0;
typedef Literal_want_Ark_CustomObject Type_AbilityComponentInterface__setAbilityComponentOptions_Arg0;
typedef Opt_Literal_want_Ark_CustomObject Opt_Type_AbilityComponentInterface__setAbilityComponentOptions_Arg0;
typedef Literal_arrayValue_Array_Ark_String_selected_Ark_Number Type_AlphabetIndexerInterface__setAlphabetIndexerOptions_Arg0;
typedef Opt_Literal_arrayValue_Array_Ark_String_selected_Ark_Number Opt_Type_AlphabetIndexerInterface__setAlphabetIndexerOptions_Arg0;
typedef Union_Ark_String_Ark_Number Type_AlphabetIndexerAttribute_itemSize_Arg0;
typedef Opt_Union_Ark_String_Ark_Number Opt_Type_AlphabetIndexerAttribute_itemSize_Arg0;
typedef Union_SpringMotion_FrictionMotion_ScrollMotion Type_AnimatorAttribute_motion_Arg0;
typedef Opt_Union_SpringMotion_FrictionMotion_ScrollMotion Opt_Type_AnimatorAttribute_motion_Arg0;
typedef Union_Ark_Number_Ark_String Type_BlankInterface__setBlankOptions_Arg0;
typedef Opt_Union_Ark_Number_Ark_String Opt_Type_BlankInterface__setBlankOptions_Arg0;
typedef Union_Ark_String_Ark_Resource ResourceStr;
typedef Opt_Union_Ark_String_Ark_Resource Opt_ResourceStr;
typedef Union_Ark_Number_Ark_FontWeight_Ark_String Type_ButtonAttribute_fontWeight_Arg0;
typedef Opt_Union_Ark_Number_Ark_FontWeight_Ark_String Opt_Type_ButtonAttribute_fontWeight_Arg0;
typedef Union_Ark_String_Ark_Resource Type_ButtonAttribute_fontFamily_Arg0;
typedef Opt_Union_Ark_String_Ark_Resource Opt_Type_ButtonAttribute_fontFamily_Arg0;
typedef Ark_CustomObject ContentModifier;
typedef Opt_Ark_CustomObject Opt_ContentModifier;
typedef Literal_date_Literal_year_Ark_Number_month_Ark_Number_day_Ark_Number_currentData_MonthData_preData_MonthData_nextData_MonthData_controller_Opt_CalendarController Type_CalendarInterface__setCalendarOptions_Arg0;
typedef Opt_Literal_date_Literal_year_Ark_Number_month_Ark_Number_day_Ark_Number_currentData_MonthData_preData_MonthData_nextData_MonthData_controller_Opt_CalendarController Opt_Type_CalendarInterface__setCalendarOptions_Arg0;
typedef Literal_dx_Ark_Length_dy_Ark_Length Offset;
typedef Opt_Literal_dx_Ark_Length_dy_Ark_Length Opt_Offset;
typedef Union_CanvasRenderingContext2D_DrawingRenderingContext Type_CanvasInterface__setCanvasOptions_Arg0;
typedef Opt_Union_CanvasRenderingContext2D_DrawingRenderingContext Opt_Type_CanvasInterface__setCanvasOptions_Arg0;
typedef Union_CanvasRenderingContext2D_DrawingRenderingContext Type_CanvasInterface__setCanvasOptions1_Arg0;
typedef Opt_Union_CanvasRenderingContext2D_DrawingRenderingContext Opt_Type_CanvasInterface__setCanvasOptions1_Arg0;
typedef Union_Ark_Number_Ark_String Type_CommonShapeMethod_strokeDashOffset_Arg0;
typedef Opt_Union_Ark_Number_Ark_String Opt_Type_CommonShapeMethod_strokeDashOffset_Arg0;
typedef Union_Ark_Number_Ark_String Type_CommonShapeMethod_strokeMiterLimit_Arg0;
typedef Opt_Union_Ark_Number_Ark_String Opt_Type_CommonShapeMethod_strokeMiterLimit_Arg0;
typedef Union_Ark_Number_Ark_String_Ark_Resource Type_CommonShapeMethod_strokeOpacity_Arg0;
typedef Opt_Union_Ark_Number_Ark_String_Ark_Resource Opt_Type_CommonShapeMethod_strokeOpacity_Arg0;
typedef Union_Ark_Number_Ark_String_Ark_Resource Type_CommonShapeMethod_fillOpacity_Arg0;
typedef Opt_Union_Ark_Number_Ark_String_Ark_Resource Opt_Type_CommonShapeMethod_fillOpacity_Arg0;
typedef Literal_space_Opt_Union_Ark_String_Ark_Number Type_ColumnInterface__setColumnOptions_Arg0;
typedef Opt_Literal_space_Opt_Union_Ark_String_Ark_Number Opt_Type_ColumnInterface__setColumnOptions_Arg0;
typedef Union_ColumnSplitDividerStyle_Ark_Undefined Type_ColumnSplitAttribute_divider_Arg0;
typedef Opt_Union_ColumnSplitDividerStyle_Ark_Undefined Opt_Type_ColumnSplitAttribute_divider_Arg0;
typedef Array_Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_LinearGradient Array_Union_ResourceColor_LinearGradient;
typedef Opt_Array_Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_LinearGradient Opt_Array_Union_ResourceColor_LinearGradient;
typedef Union_Ark_Number_Ark_String Type_DividerAttribute_strokeWidth_Arg0;
typedef Opt_Union_Ark_Number_Ark_String Opt_Type_DividerAttribute_strokeWidth_Arg0;
typedef Literal_width_Opt_Union_Ark_String_Ark_Number_height_Opt_Union_Ark_String_Ark_Number Type_EllipseInterface__setEllipseOptions_Arg0;
typedef Opt_Literal_width_Opt_Union_Ark_String_Ark_Number_height_Opt_Union_Ark_String_Ark_Number Opt_Type_EllipseInterface__setEllipseOptions_Arg0;
typedef Literal_upperItems_Opt_Array_Ark_String Type_FolderStackInterface__setFolderStackOptions_Arg0;
typedef Opt_Literal_upperItems_Opt_Array_Ark_String Opt_Type_FolderStackInterface__setFolderStackOptions_Arg0;
typedef Literal_width_Ark_Number_height_Ark_Number Type_FormComponentAttribute_size_Arg0;
typedef Opt_Literal_width_Ark_Number_height_Ark_Number Opt_Type_FormComponentAttribute_size_Arg0;
typedef Literal_value_Ark_Number_min_Opt_Ark_Number_max_Opt_Ark_Number Type_GaugeInterface__setGaugeOptions_Arg0;
typedef Opt_Literal_value_Ark_Number_min_Opt_Ark_Number_max_Opt_Ark_Number Opt_Type_GaugeInterface__setGaugeOptions_Arg0;
typedef Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_LinearGradient_Array_Tuple_Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_LinearGradient_Ark_Number Type_GaugeAttribute_colors_Arg0;
typedef Opt_Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_LinearGradient_Array_Tuple_Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_LinearGradient_Ark_Number Opt_Type_GaugeAttribute_colors_Arg0;
typedef Union_Ark_Color_Ark_Number_Ark_String Type_ScrollableCommonMethod_scrollBarColor_Arg0;
typedef Opt_Union_Ark_Color_Ark_Number_Ark_String Opt_Type_ScrollableCommonMethod_scrollBarColor_Arg0;
typedef Union_Ark_Number_Ark_String Type_ScrollableCommonMethod_scrollBarWidth_Arg0;
typedef Opt_Union_Ark_Number_Ark_String Opt_Type_ScrollableCommonMethod_scrollBarWidth_Arg0;
typedef Union_Ark_Number_Ark_Resource Type_ScrollableCommonMethod_friction_Arg0;
typedef Opt_Union_Ark_Number_Ark_Resource Opt_Type_ScrollableCommonMethod_friction_Arg0;
typedef Union_Ark_Number_Ark_String Type_GridAttribute_scrollBarWidth_Arg0;
typedef Opt_Union_Ark_Number_Ark_String Opt_Type_GridAttribute_scrollBarWidth_Arg0;
typedef Union_Ark_Color_Ark_Number_Ark_String Type_GridAttribute_scrollBarColor_Arg0;
typedef Opt_Union_Ark_Color_Ark_Number_Ark_String Opt_Type_GridAttribute_scrollBarColor_Arg0;
typedef Union_Ark_Number_Ark_Resource Type_GridAttribute_friction_Arg0;
typedef Opt_Union_Ark_Number_Ark_Resource Opt_Type_GridAttribute_friction_Arg0;
typedef Union_Ark_Number_GridColColumnOption Type_GridColAttribute_span_Arg0;
typedef Opt_Union_Ark_Number_GridColColumnOption Opt_Type_GridColAttribute_span_Arg0;
typedef Union_Ark_Number_GridColColumnOption Type_GridColAttribute_gridColOffset_Arg0;
typedef Opt_Union_Ark_Number_GridColColumnOption Opt_Type_GridColAttribute_gridColOffset_Arg0;
typedef Union_Ark_Number_GridColColumnOption Type_GridColAttribute_order_Arg0;
typedef Opt_Union_Ark_Number_GridColColumnOption Opt_Type_GridColAttribute_order_Arg0;
typedef Union_Ark_String_Ark_Resource Type_HyperlinkInterface__setHyperlinkOptions_Arg0;
typedef Opt_Union_Ark_String_Ark_Resource Opt_Type_HyperlinkInterface__setHyperlinkOptions_Arg0;
typedef Union_Ark_String_Ark_Resource Type_HyperlinkInterface__setHyperlinkOptions_Arg1;
typedef Opt_Union_Ark_String_Ark_Resource Opt_Type_HyperlinkInterface__setHyperlinkOptions_Arg1;
typedef Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource Type_HyperlinkAttribute_color_Arg0;
typedef Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource Opt_Type_HyperlinkAttribute_color_Arg0;
typedef Union_Ark_CustomObject_Union_Ark_String_Ark_Resource_Ark_CustomObject Type_ImageInterface__setImageOptions_Arg0;
typedef Opt_Union_Ark_CustomObject_Union_Ark_String_Ark_Resource_Ark_CustomObject Opt_Type_ImageInterface__setImageOptions_Arg0;
typedef Union_Ark_CustomObject_Union_Ark_String_Ark_Resource_Ark_CustomObject Type_ImageInterface__setImageOptions1_Arg0;
typedef Opt_Union_Ark_CustomObject_Union_Ark_String_Ark_Resource_Ark_CustomObject Opt_Type_ImageInterface__setImageOptions1_Arg0;
typedef Union_Ark_String_Ark_Resource_Ark_CustomObject Type_ImageAttribute_alt_Arg0;
typedef Opt_Union_Ark_String_Ark_Resource_Ark_CustomObject Opt_Type_ImageAttribute_alt_Arg0;
typedef Literal_width_Ark_Number_height_Ark_Number Type_ImageAttribute_sourceSize_Arg0;
typedef Opt_Literal_width_Ark_Number_height_Ark_Number Opt_Type_ImageAttribute_sourceSize_Arg0;
typedef Union_ColorFilter_Ark_CustomObject Type_ImageAttribute_colorFilter_Arg0;
typedef Opt_Union_ColorFilter_Ark_CustomObject Opt_Type_ImageAttribute_colorFilter_Arg0;
typedef Ark_CustomObject ResolutionQuality;
typedef Opt_Ark_CustomObject Opt_ResolutionQuality;
typedef Union_Union_Ark_String_Ark_Resource_Ark_CustomObject Type_ImageSpanInterface__setImageSpanOptions_Arg0;
typedef Opt_Union_Union_Ark_String_Ark_Resource_Ark_CustomObject Opt_Type_ImageSpanInterface__setImageSpanOptions_Arg0;
typedef Union_ColorFilter_Ark_CustomObject Type_ImageSpanAttribute_colorFilter_Arg0;
typedef Opt_Union_ColorFilter_Ark_CustomObject Opt_Type_ImageSpanAttribute_colorFilter_Arg0;
typedef Ark_CustomObject PixelMap;
typedef Opt_Ark_CustomObject Opt_PixelMap;
typedef Literal_width_Opt_Union_Ark_String_Ark_Number_height_Opt_Union_Ark_String_Ark_Number Type_LineInterface__setLineOptions_Arg0;
typedef Opt_Literal_width_Opt_Union_Ark_String_Ark_Number_height_Opt_Union_Ark_String_Ark_Number Opt_Type_LineInterface__setLineOptions_Arg0;
typedef Literal_initialIndex_Opt_Ark_Number_space_Opt_Union_Ark_Number_Ark_String_scroller_Opt_Scroller Type_ListInterface__setListOptions_Arg0;
typedef Opt_Literal_initialIndex_Opt_Ark_Number_space_Opt_Union_Ark_Number_Ark_String_scroller_Opt_Scroller Opt_Type_ListInterface__setListOptions_Arg0;
typedef Union_Ark_Number_Literal_minLength_Ark_Length_maxLength_Ark_Length Type_ListAttribute_lanes_Arg0;
typedef Opt_Union_Ark_Number_Literal_minLength_Ark_Length_maxLength_Ark_Length Opt_Type_ListAttribute_lanes_Arg0;
typedef Union_Literal_strokeWidth_Ark_Length_color_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_startMargin_Opt_Ark_Length_endMargin_Opt_Ark_Length_Ark_Undefined Type_ListAttribute_divider_Arg0;
typedef Opt_Union_Literal_strokeWidth_Ark_Length_color_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_startMargin_Opt_Ark_Length_endMargin_Opt_Ark_Length_Ark_Undefined Opt_Type_ListAttribute_divider_Arg0;
typedef Union_Ark_Number_Ark_Resource Type_ListAttribute_friction_Arg0;
typedef Opt_Union_Ark_Number_Ark_Resource Opt_Type_ListAttribute_friction_Arg0;
typedef Union_Ark_Boolean_Ark_EditMode Type_ListItemAttribute_editable_Arg0;
typedef Opt_Union_Ark_Boolean_Ark_EditMode Opt_Type_ListItemAttribute_editable_Arg0;
typedef Union_Literal_strokeWidth_Ark_Length_color_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_startMargin_Opt_Ark_Length_endMargin_Opt_Ark_Length_Ark_Undefined Type_ListItemGroupAttribute_divider_Arg0;
typedef Opt_Union_Literal_strokeWidth_Ark_Length_color_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_startMargin_Opt_Ark_Length_endMargin_Opt_Ark_Length_Ark_Undefined Opt_Type_ListItemGroupAttribute_divider_Arg0;
typedef Union_Position_Edges_LocalizedEdges Type_SecurityComponentMethod_offset_Arg0;
typedef Opt_Union_Position_Edges_LocalizedEdges Opt_Type_SecurityComponentMethod_offset_Arg0;
typedef Union_Ark_Number_Ark_FontWeight_Ark_String Type_SecurityComponentMethod_fontWeight_Arg0;
typedef Opt_Union_Ark_Number_Ark_FontWeight_Ark_String Opt_Type_SecurityComponentMethod_fontWeight_Arg0;
typedef Union_Ark_String_Ark_Resource Type_SecurityComponentMethod_fontFamily_Arg0;
typedef Opt_Union_Ark_String_Ark_Resource Opt_Type_SecurityComponentMethod_fontFamily_Arg0;
typedef Union_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length_Ark_Length Type_SecurityComponentMethod_padding_Arg0;
typedef Opt_Union_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length_Ark_Length Opt_Type_SecurityComponentMethod_padding_Arg0;
typedef Literal_start_Ark_Boolean_step_Opt_Ark_Number_loop_Opt_Ark_Number_fromStart_Opt_Ark_Boolean_src_Ark_String Type_MarqueeInterface__setMarqueeOptions_Arg0;
typedef Opt_Literal_start_Ark_Boolean_step_Opt_Ark_Number_loop_Opt_Ark_Number_fromStart_Opt_Ark_Boolean_src_Ark_String Opt_Type_MarqueeInterface__setMarqueeOptions_Arg0;
typedef Union_Ark_Number_Ark_FontWeight_Ark_String Type_MarqueeAttribute_fontWeight_Arg0;
typedef Opt_Union_Ark_Number_Ark_FontWeight_Ark_String Opt_Type_MarqueeAttribute_fontWeight_Arg0;
typedef Union_Ark_String_Ark_Resource Type_MarqueeAttribute_fontFamily_Arg0;
typedef Opt_Union_Ark_String_Ark_Resource Opt_Type_MarqueeAttribute_fontFamily_Arg0;
typedef Union_Ark_CustomObject_Union_Ark_String_Ark_Resource_Ark_CustomObject_ASTCResource Type_MediaCachedImageInterface__setMediaCachedImageOptions_Arg0;
typedef Opt_Union_Ark_CustomObject_Union_Ark_String_Ark_Resource_Ark_CustomObject_ASTCResource Opt_Type_MediaCachedImageInterface__setMediaCachedImageOptions_Arg0;
typedef Union_Ark_Length_Literal_topLeft_Opt_Ark_Length_topRight_Opt_Ark_Length_bottomLeft_Opt_Ark_Length_bottomRight_Opt_Ark_Length Type_MenuAttribute_radius_Arg0;
typedef Opt_Union_Ark_Length_Literal_topLeft_Opt_Ark_Length_topRight_Opt_Ark_Length_bottomLeft_Opt_Ark_Length_bottomRight_Opt_Ark_Length Opt_Type_MenuAttribute_radius_Arg0;
typedef Union_DividerStyleOptions_Ark_Undefined Type_MenuAttribute_menuItemDivider_Arg0;
typedef Opt_Union_DividerStyleOptions_Ark_Undefined Opt_Type_MenuAttribute_menuItemDivider_Arg0;
typedef Union_DividerStyleOptions_Ark_Undefined Type_MenuAttribute_menuItemGroupDivider_Arg0;
typedef Opt_Union_DividerStyleOptions_Ark_Undefined Opt_Type_MenuAttribute_menuItemGroupDivider_Arg0;
typedef Union_MenuItemOptions_Union_Ark_Function_Ark_Undefined Type_MenuItemInterface__setMenuItemOptions_Arg0;
typedef Opt_Union_MenuItemOptions_Union_Ark_Function_Ark_Undefined Opt_Type_MenuItemInterface__setMenuItemOptions_Arg0;
typedef Union_Ark_Boolean_Union_Ark_String_Ark_Resource_Ark_CustomObject Type_MenuItemAttribute_selectIcon_Arg0;
typedef Opt_Union_Ark_Boolean_Union_Ark_String_Ark_Resource_Ark_CustomObject Opt_Type_MenuItemAttribute_selectIcon_Arg0;
typedef Union_Ark_String_Union_Ark_Function_Ark_Undefined_NavDestinationCommonTitle_NavDestinationCustomTitle Type_NavDestinationAttribute_title_Arg0;
typedef Opt_Union_Ark_String_Union_Ark_Function_Ark_Undefined_NavDestinationCommonTitle_NavDestinationCustomTitle Opt_Type_NavDestinationAttribute_title_Arg0;
typedef Union_Union_Ark_String_Ark_Resource_Ark_CustomObject_Ark_CustomObject Type_NavDestinationAttribute_backButtonIcon_Arg0;
typedef Opt_Union_Union_Ark_String_Ark_Resource_Ark_CustomObject_Ark_CustomObject Opt_Type_NavDestinationAttribute_backButtonIcon_Arg0;
typedef Union_Array_NavigationMenuItem_Union_Ark_Function_Ark_Undefined Type_NavDestinationAttribute_menus_Arg0;
typedef Opt_Union_Array_NavigationMenuItem_Union_Ark_Function_Ark_Undefined Opt_Type_NavDestinationAttribute_menus_Arg0;
typedef Tuple_Ark_Length_Ark_Length Type_NavigationAttribute_navBarWidthRange_Arg0;
typedef Opt_Tuple_Ark_Length_Ark_Length Opt_Type_NavigationAttribute_navBarWidthRange_Arg0;
typedef Union_Ark_String_Ark_CustomObject_Ark_Resource_Ark_CustomObject Type_NavigationAttribute_backButtonIcon_Arg0;
typedef Opt_Union_Ark_String_Ark_CustomObject_Ark_Resource_Ark_CustomObject Opt_Type_NavigationAttribute_backButtonIcon_Arg0;
typedef Union_Union_Ark_String_Ark_Resource_Union_Ark_Function_Ark_Undefined_NavigationCommonTitle_NavigationCustomTitle Type_NavigationAttribute_title_Arg0;
typedef Opt_Union_Union_Ark_String_Ark_Resource_Union_Ark_Function_Ark_Undefined_NavigationCommonTitle_NavigationCustomTitle Opt_Type_NavigationAttribute_title_Arg0;
typedef Union_Array_NavigationMenuItem_Union_Ark_Function_Ark_Undefined Type_NavigationAttribute_menus_Arg0;
typedef Opt_Union_Array_NavigationMenuItem_Union_Ark_Function_Ark_Undefined Opt_Type_NavigationAttribute_menus_Arg0;
typedef Union_Ark_CustomObject_Union_Ark_Function_Ark_Undefined Type_NavigationAttribute_toolBar_Arg0;
typedef Opt_Union_Ark_CustomObject_Union_Ark_Function_Ark_Undefined Opt_Type_NavigationAttribute_toolBar_Arg0;
typedef Union_Array_ToolbarItem_Union_Ark_Function_Ark_Undefined Type_NavigationAttribute_toolbarConfiguration_Arg0;
typedef Opt_Union_Array_ToolbarItem_Union_Ark_Function_Ark_Undefined Opt_Type_NavigationAttribute_toolbarConfiguration_Arg0;
typedef Literal_target_Ark_String_type_Opt_Ark_NavigationType Type_NavigatorInterface__setNavigatorOptions_Arg0;
typedef Opt_Literal_target_Ark_String_type_Opt_Ark_NavigationType Opt_Type_NavigatorInterface__setNavigatorOptions_Arg0;
typedef Union_Ark_Length_Ark_PanelHeight Type_PanelAttribute_customHeight_Arg0;
typedef Opt_Union_Ark_Length_Ark_PanelHeight Opt_Type_PanelAttribute_customHeight_Arg0;
typedef Union_Ark_Number_Ark_String Type_PanelAttribute_fullHeight_Arg0;
typedef Opt_Union_Ark_Number_Ark_String Opt_Type_PanelAttribute_fullHeight_Arg0;
typedef Union_Ark_Number_Ark_String Type_PanelAttribute_halfHeight_Arg0;
typedef Opt_Union_Ark_Number_Ark_String Opt_Type_PanelAttribute_halfHeight_Arg0;
typedef Union_Ark_Number_Ark_String Type_PanelAttribute_miniHeight_Arg0;
typedef Opt_Union_Ark_Number_Ark_String Opt_Type_PanelAttribute_miniHeight_Arg0;
typedef Literal_width_Opt_Union_Ark_Number_Ark_String_height_Opt_Union_Ark_Number_Ark_String_commands_Opt_Ark_String Type_PathInterface__setPathOptions_Arg0;
typedef Opt_Literal_width_Opt_Union_Ark_Number_Ark_String_height_Opt_Union_Ark_Number_Ark_String_commands_Opt_Ark_String Opt_Type_PathInterface__setPathOptions_Arg0;
typedef Union_Ark_Number_Ark_String Type_PatternLockAttribute_pathStrokeWidth_Arg0;
typedef Opt_Union_Ark_Number_Ark_String Opt_Type_PatternLockAttribute_pathStrokeWidth_Arg0;
typedef Literal_template_PluginComponentTemplate_data_Ark_CustomObject Type_PluginComponentInterface__setPluginComponentOptions_Arg0;
typedef Opt_Literal_template_PluginComponentTemplate_data_Ark_CustomObject Opt_Type_PluginComponentInterface__setPluginComponentOptions_Arg0;
typedef Literal_width_Opt_Union_Ark_String_Ark_Number_height_Opt_Union_Ark_String_Ark_Number Type_PolygonInterface__setPolygonOptions_Arg0;
typedef Opt_Literal_width_Opt_Union_Ark_String_Ark_Number_height_Opt_Union_Ark_String_Ark_Number Opt_Type_PolygonInterface__setPolygonOptions_Arg0;
typedef Literal_width_Opt_Union_Ark_String_Ark_Number_height_Opt_Union_Ark_String_Ark_Number Type_PolylineInterface__setPolylineOptions_Arg0;
typedef Opt_Literal_width_Opt_Union_Ark_String_Ark_Number_height_Opt_Union_Ark_String_Ark_Number Opt_Type_PolylineInterface__setPolylineOptions_Arg0;
typedef Union_Ark_Number_Ark_Resource Type_QRCodeAttribute_contentOpacity_Arg0;
typedef Opt_Union_Ark_Number_Ark_Resource Opt_Type_QRCodeAttribute_contentOpacity_Arg0;
typedef Literal_rating_Ark_Number_indicator_Opt_Ark_Boolean Type_RatingInterface__setRatingOptions_Arg0;
typedef Opt_Literal_rating_Ark_Number_indicator_Opt_Ark_Boolean Opt_Type_RatingInterface__setRatingOptions_Arg0;
typedef Literal_backgroundUri_Ark_String_foregroundUri_Ark_String_secondaryUri_Opt_Ark_String Type_RatingAttribute_starStyle_Arg0;
typedef Opt_Literal_backgroundUri_Ark_String_foregroundUri_Ark_String_secondaryUri_Opt_Ark_String Opt_Type_RatingAttribute_starStyle_Arg0;
typedef Union_Literal_width_Opt_Union_Ark_Number_Ark_String_height_Opt_Union_Ark_Number_Ark_String_radius_Opt_Union_Ark_Number_Ark_String_Array_Ark_CustomObject_Literal_width_Opt_Union_Ark_Number_Ark_String_height_Opt_Union_Ark_Number_Ark_String_radiusWidth_Opt_Union_Ark_Number_Ark_String_radiusHeight_Opt_Union_Ark_Number_Ark_String Type_RectInterface__setRectOptions_Arg0;
typedef Opt_Union_Literal_width_Opt_Union_Ark_Number_Ark_String_height_Opt_Union_Ark_Number_Ark_String_radius_Opt_Union_Ark_Number_Ark_String_Array_Ark_CustomObject_Literal_width_Opt_Union_Ark_Number_Ark_String_height_Opt_Union_Ark_Number_Ark_String_radiusWidth_Opt_Union_Ark_Number_Ark_String_radiusHeight_Opt_Union_Ark_Number_Ark_String Opt_Type_RectInterface__setRectOptions_Arg0;
typedef Union_Ark_Number_Ark_String Type_RectAttribute_radiusWidth_Arg0;
typedef Opt_Union_Ark_Number_Ark_String Opt_Type_RectAttribute_radiusWidth_Arg0;
typedef Union_Ark_Number_Ark_String Type_RectAttribute_radiusHeight_Arg0;
typedef Opt_Union_Ark_Number_Ark_String Opt_Type_RectAttribute_radiusHeight_Arg0;
typedef Union_Ark_Number_Ark_String_Array_Ark_CustomObject Type_RectAttribute_radius_Arg0;
typedef Opt_Union_Ark_Number_Ark_String_Array_Ark_CustomObject Opt_Type_RectAttribute_radius_Arg0;
typedef Union_Ark_ResponseType_Ark_RichEditorResponseType Type_RichEditorAttribute_bindSelectionMenu_Arg2;
typedef Opt_Union_Ark_ResponseType_Ark_RichEditorResponseType Opt_Type_RichEditorAttribute_bindSelectionMenu_Arg2;
typedef Literal_space_Opt_Union_Ark_String_Ark_Number Type_RowInterface__setRowOptions_Arg0;
typedef Opt_Literal_space_Opt_Union_Ark_String_Ark_Number Opt_Type_RowInterface__setRowOptions_Arg0;
typedef Union_Ark_Color_Ark_Number_Ark_String Type_ScrollAttribute_scrollBarColor_Arg0;
typedef Opt_Union_Ark_Color_Ark_Number_Ark_String Opt_Type_ScrollAttribute_scrollBarColor_Arg0;
typedef Union_Ark_Number_Ark_String Type_ScrollAttribute_scrollBarWidth_Arg0;
typedef Opt_Union_Ark_Number_Ark_String Opt_Type_ScrollAttribute_scrollBarWidth_Arg0;
typedef Union_Ark_Number_Ark_Resource Type_ScrollAttribute_friction_Arg0;
typedef Opt_Union_Ark_Number_Ark_Resource Opt_Type_ScrollAttribute_friction_Arg0;
typedef Literal_value_Opt_Ark_String_placeholder_Opt_Union_Ark_String_Ark_Resource_icon_Opt_Ark_String_controller_Opt_SearchController Type_SearchInterface__setSearchOptions_Arg0;
typedef Opt_Literal_value_Opt_Ark_String_placeholder_Opt_Union_Ark_String_Ark_Resource_icon_Opt_Ark_String_controller_Opt_SearchController Opt_Type_SearchInterface__setSearchOptions_Arg0;
typedef Literal_style_Opt_Ark_CancelButtonStyle_icon_Opt_IconOptions Type_SearchAttribute_cancelButton_Arg0;
typedef Opt_Literal_style_Opt_Ark_CancelButtonStyle_icon_Opt_IconOptions Opt_Type_SearchAttribute_cancelButton_Arg0;
typedef Union_Ark_Number_Ark_String_Ark_Resource Type_SearchAttribute_minFontSize_Arg0;
typedef Opt_Union_Ark_Number_Ark_String_Ark_Resource Opt_Type_SearchAttribute_minFontSize_Arg0;
typedef Union_Ark_Number_Ark_String_Ark_Resource Type_SearchAttribute_maxFontSize_Arg0;
typedef Opt_Union_Ark_Number_Ark_String_Ark_Resource Opt_Type_SearchAttribute_maxFontSize_Arg0;
typedef Union_Ark_Number_Ark_String_Ark_Resource Type_SearchAttribute_letterSpacing_Arg0;
typedef Opt_Union_Ark_Number_Ark_String_Ark_Resource Opt_Type_SearchAttribute_letterSpacing_Arg0;
typedef Union_Ark_Number_Ark_String_Ark_Resource Type_SearchAttribute_lineHeight_Arg0;
typedef Opt_Union_Ark_Number_Ark_String_Ark_Resource Opt_Type_SearchAttribute_lineHeight_Arg0;
typedef Union_Ark_Number_Ark_Resource Type_SelectAttribute_selected_Arg0;
typedef Opt_Union_Ark_Number_Ark_Resource Opt_Type_SelectAttribute_selected_Arg0;
typedef Union_Ark_Length_Ark_OptionWidthMode Type_SelectAttribute_optionWidth_Arg0;
typedef Opt_Union_Ark_Length_Ark_OptionWidthMode Opt_Type_SelectAttribute_optionWidth_Arg0;
typedef Union_Opt_DividerOptions_Ark_Undefined Type_SelectAttribute_divider_Arg0;
typedef Opt_Union_Opt_DividerOptions_Ark_Undefined Opt_Type_SelectAttribute_divider_Arg0;
typedef Literal_x_Opt_Union_Ark_Number_Ark_String_y_Opt_Union_Ark_Number_Ark_String_width_Opt_Union_Ark_Number_Ark_String_height_Opt_Union_Ark_Number_Ark_String Type_ShapeAttribute_viewPort_Arg0;
typedef Opt_Literal_x_Opt_Union_Ark_Number_Ark_String_y_Opt_Union_Ark_Number_Ark_String_width_Opt_Union_Ark_Number_Ark_String_height_Opt_Union_Ark_Number_Ark_String Opt_Type_ShapeAttribute_viewPort_Arg0;
typedef Union_Ark_Number_Ark_String Type_ShapeAttribute_strokeDashOffset_Arg0;
typedef Opt_Union_Ark_Number_Ark_String Opt_Type_ShapeAttribute_strokeDashOffset_Arg0;
typedef Union_Ark_Number_Ark_String Type_ShapeAttribute_strokeMiterLimit_Arg0;
typedef Opt_Union_Ark_Number_Ark_String Opt_Type_ShapeAttribute_strokeMiterLimit_Arg0;
typedef Union_Ark_Number_Ark_String_Ark_Resource Type_ShapeAttribute_strokeOpacity_Arg0;
typedef Opt_Union_Ark_Number_Ark_String_Ark_Resource Opt_Type_ShapeAttribute_strokeOpacity_Arg0;
typedef Union_Ark_Number_Ark_String_Ark_Resource Type_ShapeAttribute_fillOpacity_Arg0;
typedef Opt_Union_Ark_Number_Ark_String_Ark_Resource Opt_Type_ShapeAttribute_fillOpacity_Arg0;
typedef Union_Ark_Number_Ark_String Type_ShapeAttribute_strokeWidth_Arg0;
typedef Opt_Union_Ark_Number_Ark_String Opt_Type_ShapeAttribute_strokeWidth_Arg0;
typedef Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_LinearGradient Type_SliderAttribute_trackColor_Arg0;
typedef Opt_Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_LinearGradient Opt_Type_SliderAttribute_trackColor_Arg0;
typedef Union_Ark_String_Ark_Resource Type_SpanInterface__setSpanOptions_Arg0;
typedef Opt_Union_Ark_String_Ark_Resource Opt_Type_SpanInterface__setSpanOptions_Arg0;
typedef Union_Ark_Number_Ark_String_Ark_Resource Type_SpanAttribute_fontSize_Arg0;
typedef Opt_Union_Ark_Number_Ark_String_Ark_Resource Opt_Type_SpanAttribute_fontSize_Arg0;
typedef Union_Ark_Number_Ark_FontWeight_Ark_String Type_SpanAttribute_fontWeight_Arg0;
typedef Opt_Union_Ark_Number_Ark_FontWeight_Ark_String Opt_Type_SpanAttribute_fontWeight_Arg0;
typedef Union_Ark_String_Ark_Resource Type_SpanAttribute_fontFamily_Arg0;
typedef Opt_Union_Ark_String_Ark_Resource Opt_Type_SpanAttribute_fontFamily_Arg0;
typedef Union_Ark_Number_Ark_String Type_SpanAttribute_letterSpacing_Arg0;
typedef Opt_Union_Ark_Number_Ark_String Opt_Type_SpanAttribute_letterSpacing_Arg0;
typedef Union_ShadowOptions_Array_ShadowOptions Type_SpanAttribute_textShadow_Arg0;
typedef Opt_Union_ShadowOptions_Array_ShadowOptions Opt_Type_SpanAttribute_textShadow_Arg0;
typedef Literal_alignContent_Opt_Ark_Alignment Type_StackInterface__setStackOptions_Arg0;
typedef Opt_Literal_alignContent_Opt_Ark_Alignment Opt_Type_StackInterface__setStackOptions_Arg0;
typedef Literal_index_Opt_Ark_Number Type_StepperInterface__setStepperOptions_Arg0;
typedef Opt_Literal_index_Opt_Ark_Number Opt_Type_StepperInterface__setStepperOptions_Arg0;
typedef Union_DotIndicator_DigitIndicator_Ark_Boolean Type_SwiperAttribute_indicator_Arg0;
typedef Opt_Union_DotIndicator_DigitIndicator_Ark_Boolean Opt_Type_SwiperAttribute_indicator_Arg0;
typedef Union_ArrowStyle_Ark_Boolean Type_SwiperAttribute_displayArrow_Arg0;
typedef Opt_Union_ArrowStyle_Ark_Boolean Opt_Type_SwiperAttribute_displayArrow_Arg0;
typedef Union_Ark_Number_Ark_String Type_SwiperAttribute_itemSpace_Arg0;
typedef Opt_Union_Ark_Number_Ark_String Opt_Type_SwiperAttribute_itemSpace_Arg0;
typedef Union_Ark_Number_Ark_String_Literal_minSize_Union_Ark_String_Ark_Number Type_SwiperAttribute_displayCount_Arg0;
typedef Opt_Union_Ark_Number_Ark_String_Literal_minSize_Union_Ark_String_Ark_Number Opt_Type_SwiperAttribute_displayCount_Arg0;
typedef Union_Ark_Curve_Ark_String_ICurve Type_SwiperAttribute_curve_Arg0;
typedef Opt_Union_Ark_Curve_Ark_String_ICurve Opt_Type_SwiperAttribute_curve_Arg0;
typedef Union_Ark_Number_Ark_String_Ark_Resource Type_SymbolGlyphAttribute_fontSize_Arg0;
typedef Opt_Union_Ark_Number_Ark_String_Ark_Resource Opt_Type_SymbolGlyphAttribute_fontSize_Arg0;
typedef Array_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource Array_ResourceColor;
typedef Opt_Array_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource Opt_Array_ResourceColor;
typedef Union_Ark_Number_Ark_FontWeight_Ark_String Type_SymbolGlyphAttribute_fontWeight_Arg0;
typedef Opt_Union_Ark_Number_Ark_FontWeight_Ark_String Opt_Type_SymbolGlyphAttribute_fontWeight_Arg0;
typedef Union_Ark_Number_Ark_String_Ark_Resource Type_SymbolSpanAttribute_fontSize_Arg0;
typedef Opt_Union_Ark_Number_Ark_String_Ark_Resource Opt_Type_SymbolSpanAttribute_fontSize_Arg0;
typedef Union_Ark_Number_Ark_FontWeight_Ark_String Type_SymbolSpanAttribute_fontWeight_Arg0;
typedef Opt_Union_Ark_Number_Ark_FontWeight_Ark_String Opt_Type_SymbolSpanAttribute_fontWeight_Arg0;
typedef Literal_barPosition_Opt_Ark_BarPosition_index_Opt_Ark_Number_controller_Opt_TabsController Type_TabsInterface__setTabsOptions_Arg0;
typedef Opt_Literal_barPosition_Opt_Ark_BarPosition_index_Opt_Ark_Number_controller_Opt_TabsController Opt_Type_TabsInterface__setTabsOptions_Arg0;
typedef Union_DividerStyle_Ark_Undefined Type_TabsAttribute_divider_Arg0;
typedef Opt_Union_DividerStyle_Ark_Undefined Opt_Type_TabsAttribute_divider_Arg0;
typedef Union_Ark_String_Ark_Resource_Union_Ark_Function_Ark_Undefined_Literal_icon_Opt_Union_Ark_String_Ark_Resource_text_Opt_Union_Ark_String_Ark_Resource Type_TabContentAttribute_tabBar_Arg0;
typedef Opt_Union_Ark_String_Ark_Resource_Union_Ark_Function_Ark_Undefined_Literal_icon_Opt_Union_Ark_String_Ark_Resource_text_Opt_Union_Ark_String_Ark_Resource Opt_Type_TabContentAttribute_tabBar_Arg0;
typedef Union_SubTabBarStyle_BottomTabBarStyle Type_TabContentAttribute_tabBar1_Arg0;
typedef Opt_Union_SubTabBarStyle_BottomTabBarStyle Opt_Type_TabContentAttribute_tabBar1_Arg0;
typedef Union_Ark_String_Ark_Resource Type_TextInterface__setTextOptions_Arg0;
typedef Opt_Union_Ark_String_Ark_Resource Opt_Type_TextInterface__setTextOptions_Arg0;
typedef Union_Ark_Number_Ark_String_Ark_Resource Type_TextAttribute_fontSize_Arg0;
typedef Opt_Union_Ark_Number_Ark_String_Ark_Resource Opt_Type_TextAttribute_fontSize_Arg0;
typedef Union_Ark_Number_Ark_String_Ark_Resource Type_TextAttribute_minFontSize_Arg0;
typedef Opt_Union_Ark_Number_Ark_String_Ark_Resource Opt_Type_TextAttribute_minFontSize_Arg0;
typedef Union_Ark_Number_Ark_String_Ark_Resource Type_TextAttribute_maxFontSize_Arg0;
typedef Opt_Union_Ark_Number_Ark_String_Ark_Resource Opt_Type_TextAttribute_maxFontSize_Arg0;
typedef Union_Ark_Number_Ark_FontWeight_Ark_String Type_TextAttribute_fontWeight_Arg0;
typedef Opt_Union_Ark_Number_Ark_FontWeight_Ark_String Opt_Type_TextAttribute_fontWeight_Arg0;
typedef Union_Ark_Number_Ark_String_Ark_Resource Type_TextAttribute_lineHeight_Arg0;
typedef Opt_Union_Ark_Number_Ark_String_Ark_Resource Opt_Type_TextAttribute_lineHeight_Arg0;
typedef Literal_overflow_Ark_TextOverflow Type_TextAttribute_textOverflow_Arg0;
typedef Opt_Literal_overflow_Ark_TextOverflow Opt_Type_TextAttribute_textOverflow_Arg0;
typedef Union_Ark_String_Ark_Resource Type_TextAttribute_fontFamily_Arg0;
typedef Opt_Union_Ark_String_Ark_Resource Opt_Type_TextAttribute_fontFamily_Arg0;
typedef Union_Ark_Number_Ark_String Type_TextAttribute_letterSpacing_Arg0;
typedef Opt_Union_Ark_Number_Ark_String Opt_Type_TextAttribute_letterSpacing_Arg0;
typedef Union_Ark_Number_Ark_String Type_TextAttribute_baselineOffset_Arg0;
typedef Opt_Union_Ark_Number_Ark_String Opt_Type_TextAttribute_baselineOffset_Arg0;
typedef Union_ShadowOptions_Array_ShadowOptions Type_TextAttribute_textShadow_Arg0;
typedef Opt_Union_ShadowOptions_Array_ShadowOptions Opt_Type_TextAttribute_textShadow_Arg0;
typedef Union_Ark_Number_Ark_FontWeight_Ark_String Type_TextAreaAttribute_fontWeight_Arg0;
typedef Opt_Union_Ark_Number_Ark_FontWeight_Ark_String Opt_Type_TextAreaAttribute_fontWeight_Arg0;
typedef Union_Ark_Number_Ark_String_Ark_Resource Type_TextAreaAttribute_minFontSize_Arg0;
typedef Opt_Union_Ark_Number_Ark_String_Ark_Resource Opt_Type_TextAreaAttribute_minFontSize_Arg0;
typedef Union_Ark_Number_Ark_String_Ark_Resource Type_TextAreaAttribute_maxFontSize_Arg0;
typedef Opt_Union_Ark_Number_Ark_String_Ark_Resource Opt_Type_TextAreaAttribute_maxFontSize_Arg0;
typedef Union_Ark_Number_Ark_String_Ark_Resource Type_TextAreaAttribute_letterSpacing_Arg0;
typedef Opt_Union_Ark_Number_Ark_String_Ark_Resource Opt_Type_TextAreaAttribute_letterSpacing_Arg0;
typedef Union_Ark_Number_Ark_String_Ark_Resource Type_TextAreaAttribute_lineHeight_Arg0;
typedef Opt_Union_Ark_Number_Ark_String_Ark_Resource Opt_Type_TextAreaAttribute_lineHeight_Arg0;
typedef Literal_timeZoneOffset_Opt_Ark_Number_controller_Opt_TextClockController Type_TextClockInterface__setTextClockOptions_Arg0;
typedef Opt_Literal_timeZoneOffset_Opt_Ark_Number_controller_Opt_TextClockController Opt_Type_TextClockInterface__setTextClockOptions_Arg0;
typedef Union_Ark_Number_Ark_FontWeight_Ark_String Type_TextClockAttribute_fontWeight_Arg0;
typedef Opt_Union_Ark_Number_Ark_FontWeight_Ark_String Opt_Type_TextClockAttribute_fontWeight_Arg0;
typedef Union_ShadowOptions_Array_ShadowOptions Type_TextClockAttribute_textShadow_Arg0;
typedef Opt_Union_ShadowOptions_Array_ShadowOptions Opt_Type_TextClockAttribute_textShadow_Arg0;
typedef Union_Ark_Number_Ark_FontWeight_Ark_String Type_TextInputAttribute_fontWeight_Arg0;
typedef Opt_Union_Ark_Number_Ark_FontWeight_Ark_String Opt_Type_TextInputAttribute_fontWeight_Arg0;
typedef Union_Ark_TextInputStyle_Ark_TextContentStyle Type_TextInputAttribute_style_Arg0;
typedef Opt_Union_Ark_TextInputStyle_Ark_TextContentStyle Opt_Type_TextInputAttribute_style_Arg0;
typedef Union_Union_Ark_String_Ark_Resource_Ark_Undefined Type_TextInputAttribute_showError_Arg0;
typedef Opt_Union_Union_Ark_String_Ark_Resource_Ark_Undefined Opt_Type_TextInputAttribute_showError_Arg0;
typedef Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_UnderlineColor_Ark_Undefined Type_TextInputAttribute_underlineColor_Arg0;
typedef Opt_Union_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_UnderlineColor_Ark_Undefined Opt_Type_TextInputAttribute_underlineColor_Arg0;
typedef Literal_style_Opt_Ark_CancelButtonStyle_icon_Opt_IconOptions Type_TextInputAttribute_cancelButton_Arg0;
typedef Opt_Literal_style_Opt_Ark_CancelButtonStyle_icon_Opt_IconOptions Opt_Type_TextInputAttribute_cancelButton_Arg0;
typedef Union_Ark_Number_Ark_String_Ark_Resource Type_TextInputAttribute_minFontSize_Arg0;
typedef Opt_Union_Ark_Number_Ark_String_Ark_Resource Opt_Type_TextInputAttribute_minFontSize_Arg0;
typedef Union_Ark_Number_Ark_String_Ark_Resource Type_TextInputAttribute_maxFontSize_Arg0;
typedef Opt_Union_Ark_Number_Ark_String_Ark_Resource Opt_Type_TextInputAttribute_maxFontSize_Arg0;
typedef Union_Ark_Number_Ark_String_Ark_Resource Type_TextInputAttribute_letterSpacing_Arg0;
typedef Opt_Union_Ark_Number_Ark_String_Ark_Resource Opt_Type_TextInputAttribute_letterSpacing_Arg0;
typedef Union_Ark_Number_Ark_String_Ark_Resource Type_TextInputAttribute_lineHeight_Arg0;
typedef Opt_Union_Ark_Number_Ark_String_Ark_Resource Opt_Type_TextInputAttribute_lineHeight_Arg0;
typedef Union_Ark_Number_Ark_String Type_TextPickerAttribute_defaultPickerItemHeight_Arg0;
typedef Opt_Union_Ark_Number_Ark_String Opt_Type_TextPickerAttribute_defaultPickerItemHeight_Arg0;
typedef Union_Ark_Number_Array_Ark_Number Type_TextPickerAttribute_selectedIndex_Arg0;
typedef Opt_Union_Ark_Number_Array_Ark_Number Opt_Type_TextPickerAttribute_selectedIndex_Arg0;
typedef Union_DividerOptions_Ark_Undefined Type_TextPickerAttribute_divider_Arg0;
typedef Opt_Union_DividerOptions_Ark_Undefined Opt_Type_TextPickerAttribute_divider_Arg0;
typedef Union_Ark_Number_Ark_FontWeight_Ark_String Type_TextTimerAttribute_fontWeight_Arg0;
typedef Opt_Union_Ark_Number_Ark_FontWeight_Ark_String Opt_Type_TextTimerAttribute_fontWeight_Arg0;
typedef Union_ShadowOptions_Array_ShadowOptions Type_TextTimerAttribute_textShadow_Arg0;
typedef Opt_Union_ShadowOptions_Array_ShadowOptions Opt_Type_TextTimerAttribute_textShadow_Arg0;
typedef Ark_CustomObject DateTimeOptions;
typedef Opt_Ark_CustomObject Opt_DateTimeOptions;
typedef Literal_type_Ark_ToggleType_isOn_Opt_Ark_Boolean Type_ToggleInterface__setToggleOptions_Arg0;
typedef Opt_Literal_type_Ark_ToggleType_isOn_Opt_Ark_Boolean Opt_Type_ToggleInterface__setToggleOptions_Arg0;
typedef Literal_id_Ark_String_type_Ark_String_libraryname_Opt_Ark_String_controller_Opt_XComponentController Type_XComponentInterface__setXComponentOptions_Arg0;
typedef Opt_Literal_id_Ark_String_type_Ark_String_libraryname_Opt_Ark_String_controller_Opt_XComponentController Opt_Type_XComponentInterface__setXComponentOptions_Arg0;
typedef Literal_id_Ark_String_type_Ark_XComponentType_libraryname_Opt_Ark_String_controller_Opt_XComponentController Type_XComponentInterface__setXComponentOptions1_Arg0;
typedef Opt_Literal_id_Ark_String_type_Ark_XComponentType_libraryname_Opt_Ark_String_controller_Opt_XComponentController Opt_Type_XComponentInterface__setXComponentOptions1_Arg0;
typedef Union_DividerStyle_Ark_Undefined Type_SideBarContainerAttribute_divider_Arg0;
typedef Opt_Union_DividerStyle_Ark_Undefined Opt_Type_SideBarContainerAttribute_divider_Arg0;
typedef Union_Ark_Number_Ark_Resource Type_WaterFlowAttribute_friction_Arg0;
typedef Opt_Union_Ark_Number_Ark_Resource Opt_Type_WaterFlowAttribute_friction_Arg0;
typedef Ark_CustomObject DrawContext;
typedef Opt_Ark_CustomObject Opt_DrawContext;
typedef Literal_fingers_Opt_Ark_Number_direction_Opt_Ark_PanDirection_distance_Opt_Ark_Number Literal_fingers_Opt_Ark_Number_direction_Ark_PanDirection_distance_Opt_Ark_Number;
typedef Opt_Literal_fingers_Opt_Ark_Number_direction_Opt_Ark_PanDirection_distance_Opt_Ark_Number Opt_Literal_fingers_Opt_Ark_Number_direction_Ark_PanDirection_distance_Opt_Ark_Number;
typedef Ark_CustomObject T;
typedef Opt_Ark_CustomObject Opt_T;
typedef Union_Ark_String_Ark_String_Ark_String ImageSmoothingQuality;
typedef Opt_Union_Ark_String_Ark_String_Ark_String Opt_ImageSmoothingQuality;
typedef Union_Ark_String_Ark_String_Ark_String CanvasLineCap;
typedef Opt_Union_Ark_String_Ark_String_Ark_String Opt_CanvasLineCap;
typedef Union_Ark_String_Ark_String_Ark_String CanvasLineJoin;
typedef Opt_Union_Ark_String_Ark_String_Ark_String Opt_CanvasLineJoin;
typedef Union_Ark_String_Ark_String_Ark_String CanvasDirection;
typedef Opt_Union_Ark_String_Ark_String_Ark_String Opt_CanvasDirection;
typedef Union_Ark_String_Ark_String_Ark_String_Ark_String_Ark_String CanvasTextAlign;
typedef Opt_Union_Ark_String_Ark_String_Ark_String_Ark_String_Ark_String Opt_CanvasTextAlign;
typedef Union_Ark_String_Ark_String_Ark_String_Ark_String_Ark_String_Ark_String CanvasTextBaseline;
typedef Opt_Union_Ark_String_Ark_String_Ark_String_Ark_String_Ark_String_Ark_String Opt_CanvasTextBaseline;
typedef Union_ImageBitmap_Ark_CustomObject Union_ImageBitmap_PixelMap;
typedef Opt_Union_ImageBitmap_Ark_CustomObject Opt_Union_ImageBitmap_PixelMap;
typedef Union_Ark_String_Ark_String CanvasFillRule;
typedef Opt_Union_Ark_String_Ark_String Opt_CanvasFillRule;
typedef Ark_CustomObject LengthMetricsUnit;
typedef Opt_Ark_CustomObject Opt_LengthMetricsUnit;
typedef Literal_xOffset_Union_Ark_Number_Ark_String_yOffset_Union_Ark_Number_Ark_String_animation_Opt_Union_ScrollAnimationOptions_Ark_Boolean Literal_xOffset_Union_Ark_Number_Ark_String_yOffset_Union_Ark_Number_Ark_String_animation_Opt_Union_Opt_ScrollAnimationOptions_Opt_Ark_Boolean;
typedef Opt_Literal_xOffset_Union_Ark_Number_Ark_String_yOffset_Union_Ark_Number_Ark_String_animation_Opt_Union_ScrollAnimationOptions_Ark_Boolean Opt_Literal_xOffset_Union_Ark_Number_Ark_String_yOffset_Union_Ark_Number_Ark_String_animation_Opt_Union_Opt_ScrollAnimationOptions_Opt_Ark_Boolean;
typedef Literal_next_Ark_Boolean_direction_Opt_Ark_Axis Literal_next_Ark_Boolean_direction_Ark_Axis;
typedef Opt_Literal_next_Ark_Boolean_direction_Opt_Ark_Axis Opt_Literal_next_Ark_Boolean_direction_Ark_Axis;
typedef Union_Ark_CustomObject_Union_Ark_String_Ark_Resource Union_PixelMap_ResourceStr;
typedef Opt_Union_Ark_CustomObject_Union_Ark_String_Ark_Resource Opt_Union_PixelMap_ResourceStr;
typedef Ark_CustomObject WebviewController;
typedef Opt_Ark_CustomObject Opt_WebviewController;
typedef Ark_CustomObject Date;
typedef Opt_Ark_CustomObject Opt_Date;
typedef Literal_handler_Ark_Function_error_Ark_CustomObject Literal_handler_Function_error_Ark_CustomObject;
typedef Opt_Literal_handler_Ark_Function_error_Ark_CustomObject Opt_Literal_handler_Function_error_Ark_CustomObject;
typedef Literal_callback_Ark_Function_fileSelector_Ark_CustomObject Literal_callback_Function_fileSelector_Ark_CustomObject;
typedef Opt_Literal_callback_Ark_Function_fileSelector_Ark_CustomObject Opt_Literal_callback_Function_fileSelector_Ark_CustomObject;
typedef Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length Padding;
typedef Opt_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length Opt_Padding;
typedef Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length Margin;
typedef Opt_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length Opt_Margin;
typedef LocalizedPadding LocalizedMargin;
typedef Opt_LocalizedPadding Opt_LocalizedMargin;
typedef Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length EdgeWidths;
typedef Opt_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length Opt_EdgeWidths;
typedef Literal_top_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_right_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_bottom_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_left_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource EdgeColors;
typedef Opt_Literal_top_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_right_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_bottom_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource_left_Opt_Union_Ark_Color_Ark_Number_Ark_String_Ark_Resource Opt_EdgeColors;
typedef Literal_topLeft_Opt_Ark_Length_topRight_Opt_Ark_Length_bottomLeft_Opt_Ark_Length_bottomRight_Opt_Ark_Length BorderRadiuses;
typedef Opt_Literal_topLeft_Opt_Ark_Length_topRight_Opt_Ark_Length_bottomLeft_Opt_Ark_Length_bottomRight_Opt_Ark_Length Opt_BorderRadiuses;
typedef Literal_top_Opt_Ark_BorderStyle_right_Opt_Ark_BorderStyle_bottom_Opt_Ark_BorderStyle_left_Opt_Ark_BorderStyle EdgeStyles;
typedef Opt_Literal_top_Opt_Ark_BorderStyle_right_Opt_Ark_BorderStyle_bottom_Opt_Ark_BorderStyle_left_Opt_Ark_BorderStyle Opt_EdgeStyles;
typedef Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length EdgeOutlineWidths;
typedef Opt_Literal_top_Opt_Ark_Length_right_Opt_Ark_Length_bottom_Opt_Ark_Length_left_Opt_Ark_Length Opt_EdgeOutlineWidths;
typedef Literal_topLeft_Opt_Ark_Length_topRight_Opt_Ark_Length_bottomLeft_Opt_Ark_Length_bottomRight_Opt_Ark_Length OutlineRadiuses;
typedef Opt_Literal_topLeft_Opt_Ark_Length_topRight_Opt_Ark_Length_bottomLeft_Opt_Ark_Length_bottomRight_Opt_Ark_Length Opt_OutlineRadiuses;
typedef Literal_top_Opt_Ark_OutlineStyle_right_Opt_Ark_OutlineStyle_bottom_Opt_Ark_OutlineStyle_left_Opt_Ark_OutlineStyle EdgeOutlineStyles;
typedef Opt_Literal_top_Opt_Ark_OutlineStyle_right_Opt_Ark_OutlineStyle_bottom_Opt_Ark_OutlineStyle_left_Opt_Ark_OutlineStyle Opt_EdgeOutlineStyles;
typedef Ark_CustomObject ColorMetrics;
typedef Opt_Ark_CustomObject Opt_ColorMetrics;
typedef Tuple_Ark_Number_Ark_Number FractionStop;
typedef Opt_Tuple_Ark_Number_Ark_Number Opt_FractionStop;
typedef Ark_CustomObject UniformDataType;
typedef Opt_Ark_CustomObject Opt_UniformDataType;
typedef Ark_CustomObject ImageModifier;
typedef Opt_Ark_CustomObject Opt_ImageModifier;
typedef Ark_CustomObject ComponentContent;
typedef Opt_Ark_CustomObject Opt_ComponentContent;
typedef Ark_CustomObject CircleShape;
typedef Opt_Ark_CustomObject Opt_CircleShape;
typedef Ark_CustomObject EllipseShape;
typedef Opt_Ark_CustomObject Opt_EllipseShape;
typedef Ark_CustomObject PathShape;
typedef Opt_Ark_CustomObject Opt_PathShape;
typedef Ark_CustomObject RectShape;
typedef Opt_Ark_CustomObject Opt_RectShape;
typedef Ark_CustomObject SymbolGlyphModifier;
typedef Opt_Ark_CustomObject Opt_SymbolGlyphModifier;
typedef Ark_CustomObject UIContext;
typedef Opt_Ark_CustomObject Opt_UIContext;
typedef Ark_CustomObject Scene;
typedef Opt_Ark_CustomObject Opt_Scene;
typedef Ark_CustomObject DrawableDescriptor;
typedef Opt_Ark_CustomObject Opt_DrawableDescriptor;
typedef Ark_CustomObject DrawingColorFilter;
typedef Opt_Ark_CustomObject Opt_DrawingColorFilter;
typedef Literal_minLength_Ark_Length_maxLength_Ark_Length LengthConstrain;
typedef Opt_Literal_minLength_Ark_Length_maxLength_Ark_Length Opt_LengthConstrain;
typedef Ark_CustomObject SystemBarStyle;
typedef Opt_Ark_CustomObject Opt_SystemBarStyle;
typedef Literal_minSize_Union_Ark_String_Ark_Number SwiperAutoFill;
typedef Opt_Literal_minSize_Union_Ark_String_Ark_Number Opt_SwiperAutoFill;
typedef Union_Ark_String_Ark_Number VP;
typedef Opt_Union_Ark_String_Ark_Number Opt_VP;
typedef Union_TextStyle_DecorationStyle_BaselineOffsetStyle_LetterSpacingStyle_TextShadowStyle_GestureStyle_ImageAttachment_ParagraphStyle_LineHeightStyle_CustomSpan_UserDataSpan StyledStringValue;
typedef Opt_Union_TextStyle_DecorationStyle_BaselineOffsetStyle_LetterSpacingStyle_TextShadowStyle_GestureStyle_ImageAttachment_ParagraphStyle_LineHeightStyle_CustomSpan_UserDataSpan Opt_StyledStringValue;
typedef Ark_CustomObject IntentionCode;
typedef Opt_Ark_CustomObject Opt_IntentionCode;
typedef Ark_CustomObject WindowStatusType;
typedef Opt_Ark_CustomObject Opt_WindowStatusType;
typedef Opt_Ark_Length Opt_Dimension;
typedef Opt_Ark_Length Opt_Length;



typedef struct GENERATED_ArkUIAbilityComponentModifier {
    void (*_setAbilityComponentOptions)(Ark_NativePointer node, const Type_AbilityComponentInterface__setAbilityComponentOptions_Arg0* value);
    void (*setOnConnect)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnDisconnect)(Ark_NativePointer node, Ark_Function callback);
} GENERATED_ArkUIAbilityComponentModifier;

typedef struct GENERATED_ArkUIAlphabetIndexerModifier {
    void (*_setAlphabetIndexerOptions)(Ark_NativePointer node, const Type_AlphabetIndexerInterface__setAlphabetIndexerOptions_Arg0* value);
    void (*setOnSelected)(Ark_NativePointer node, Ark_Function callback);
    void (*setColor)(Ark_NativePointer node, const ResourceColor* value);
    void (*setSelectedColor)(Ark_NativePointer node, const ResourceColor* value);
    void (*setPopupColor)(Ark_NativePointer node, const ResourceColor* value);
    void (*setSelectedBackgroundColor)(Ark_NativePointer node, const ResourceColor* value);
    void (*setPopupBackground)(Ark_NativePointer node, const ResourceColor* value);
    void (*setPopupSelectedColor)(Ark_NativePointer node, const ResourceColor* value);
    void (*setPopupUnselectedColor)(Ark_NativePointer node, const ResourceColor* value);
    void (*setPopupItemBackgroundColor)(Ark_NativePointer node, const ResourceColor* value);
    void (*setUsingPopup)(Ark_NativePointer node, Ark_Boolean value);
    void (*setSelectedFont)(Ark_NativePointer node, const Font* value);
    void (*setPopupFont)(Ark_NativePointer node, const Font* value);
    void (*setPopupItemFont)(Ark_NativePointer node, const Font* value);
    void (*setItemSize)(Ark_NativePointer node, const Type_AlphabetIndexerAttribute_itemSize_Arg0* value);
    void (*setFont)(Ark_NativePointer node, const Font* value);
    void (*setAlignStyle)(Ark_NativePointer node, Ark_Int32 value, const Opt_Length* offset);
    void (*setOnSelect)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnRequestPopupData)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnPopupSelect)(Ark_NativePointer node, Ark_Function callback);
    void (*setSelected)(Ark_NativePointer node, const Ark_Number* index);
    void (*setPopupPosition)(Ark_NativePointer node, const Position* value);
    void (*setAutoCollapse)(Ark_NativePointer node, Ark_Boolean value);
    void (*setPopupItemBorderRadius)(Ark_NativePointer node, const Ark_Number* value);
    void (*setItemBorderRadius)(Ark_NativePointer node, const Ark_Number* value);
    void (*setPopupBackgroundBlurStyle)(Ark_NativePointer node, Ark_Int32 value);
    void (*setPopupTitleBackground)(Ark_NativePointer node, const ResourceColor* value);
    void (*setEnableHapticFeedback)(Ark_NativePointer node, Ark_Boolean value);
} GENERATED_ArkUIAlphabetIndexerModifier;

typedef struct GENERATED_ArkUIAnimatorModifier {
    void (*_setAnimatorOptions)(Ark_NativePointer node, const Ark_String* value);
    void (*setState)(Ark_NativePointer node, Ark_Int32 value);
    void (*setDuration)(Ark_NativePointer node, const Ark_Number* value);
    void (*setCurve)(Ark_NativePointer node, Ark_Int32 value);
    void (*setDelay)(Ark_NativePointer node, const Ark_Number* value);
    void (*setFillMode)(Ark_NativePointer node, Ark_Int32 value);
    void (*setIterations)(Ark_NativePointer node, const Ark_Number* value);
    void (*setPlayMode)(Ark_NativePointer node, Ark_Int32 value);
    void (*setMotion)(Ark_NativePointer node, const Type_AnimatorAttribute_motion_Arg0* value);
    void (*setOnStart)(Ark_NativePointer node, Ark_Function event);
    void (*setOnPause)(Ark_NativePointer node, Ark_Function event);
    void (*setOnRepeat)(Ark_NativePointer node, Ark_Function event);
    void (*setOnCancel)(Ark_NativePointer node, Ark_Function event);
    void (*setOnFinish)(Ark_NativePointer node, Ark_Function event);
    void (*setOnFrame)(Ark_NativePointer node, Ark_Function event);
} GENERATED_ArkUIAnimatorModifier;

typedef struct GENERATED_ArkUIBadgeModifier {
    void (*_setBadgeOptions_BadgeParamWithNumber)(Ark_NativePointer node, const BadgeParamWithNumber* value);
    void (*_setBadgeOptions_BadgeParamWithString)(Ark_NativePointer node, const BadgeParamWithString* value);
} GENERATED_ArkUIBadgeModifier;

typedef struct GENERATED_ArkUIBlankModifier {
    void (*_setBlankOptions)(Ark_NativePointer node, const Opt_Type_BlankInterface__setBlankOptions_Arg0* min);
    void (*setColor)(Ark_NativePointer node, const ResourceColor* value);
} GENERATED_ArkUIBlankModifier;

typedef struct GENERATED_ArkUIButtonModifier {
    void (*_setButtonOptions_)(Ark_NativePointer node);
    void (*_setButtonOptions_ButtonOptions)(Ark_NativePointer node, const ButtonOptions* options);
    void (*_setButtonOptions_ResourceStr_ButtonOptions)(Ark_NativePointer node, const ResourceStr* label, const Opt_ButtonOptions* options);
    void (*setType)(Ark_NativePointer node, Ark_Int32 value);
    void (*setStateEffect)(Ark_NativePointer node, Ark_Boolean value);
    void (*setButtonStyle)(Ark_NativePointer node, Ark_Int32 value);
    void (*setControlSize)(Ark_NativePointer node, Ark_Int32 value);
    void (*setRole)(Ark_NativePointer node, Ark_Int32 value);
    void (*setFontColor)(Ark_NativePointer node, const ResourceColor* value);
    void (*setFontSize)(Ark_NativePointer node, const Ark_Length* value);
    void (*setFontWeight)(Ark_NativePointer node, const Type_ButtonAttribute_fontWeight_Arg0* value);
    void (*setFontStyle)(Ark_NativePointer node, Ark_Int32 value);
    void (*setFontFamily)(Ark_NativePointer node, const Type_ButtonAttribute_fontFamily_Arg0* value);
    void (*setContentModifier)(Ark_NativePointer node, const Ark_CustomObject* modifier);
    void (*setLabelStyle)(Ark_NativePointer node, const LabelStyle* value);
} GENERATED_ArkUIButtonModifier;

typedef struct GENERATED_ArkUICalendarModifier {
    void (*_setCalendarOptions)(Ark_NativePointer node, const Type_CalendarInterface__setCalendarOptions_Arg0* value);
    void (*setShowLunar)(Ark_NativePointer node, Ark_Boolean value);
    void (*setShowHoliday)(Ark_NativePointer node, Ark_Boolean value);
    void (*setNeedSlide)(Ark_NativePointer node, Ark_Boolean value);
    void (*setStartOfWeek)(Ark_NativePointer node, const Ark_Number* value);
    void (*setOffDays)(Ark_NativePointer node, const Ark_Number* value);
    void (*setDirection)(Ark_NativePointer node, Ark_Int32 value);
    void (*setCurrentDayStyle)(Ark_NativePointer node, const CurrentDayStyle* value);
    void (*setNonCurrentDayStyle)(Ark_NativePointer node, const NonCurrentDayStyle* value);
    void (*setTodayStyle)(Ark_NativePointer node, const TodayStyle* value);
    void (*setWeekStyle)(Ark_NativePointer node, const WeekStyle* value);
    void (*setWorkStateStyle)(Ark_NativePointer node, const WorkStateStyle* value);
    void (*setOnSelectChange)(Ark_NativePointer node, Ark_Function event);
    void (*setOnRequestData)(Ark_NativePointer node, Ark_Function event);
} GENERATED_ArkUICalendarModifier;

typedef struct GENERATED_ArkUICalendarPickerModifier {
    void (*_setCalendarPickerOptions)(Ark_NativePointer node, const Opt_CalendarOptions* options);
    void (*setEdgeAlign)(Ark_NativePointer node, Ark_Int32 alignType, const Opt_Offset* offset);
    void (*setTextStyle)(Ark_NativePointer node, const PickerTextStyle* value);
    void (*setOnChange)(Ark_NativePointer node, Ark_Function callback);
} GENERATED_ArkUICalendarPickerModifier;

typedef struct GENERATED_ArkUICanvasModifier {
    void (*_setCanvasOptions_CanvasRenderingContextDDrawingRenderingContext)(Ark_NativePointer node, const Opt_Type_CanvasInterface__setCanvasOptions_Arg0* context);
    void (*_setCanvasOptions_CanvasRenderingContextDDrawingRenderingContext_ImageAIOptions)(Ark_NativePointer node, const Type_CanvasInterface__setCanvasOptions1_Arg0* context, const ImageAIOptions* imageAIOptions);
    void (*setOnReady)(Ark_NativePointer node, Ark_Function event);
    void (*setEnableAnalyzer)(Ark_NativePointer node, Ark_Boolean enable);
} GENERATED_ArkUICanvasModifier;

typedef struct GENERATED_ArkUICheckboxModifier {
    void (*_setCheckboxOptions)(Ark_NativePointer node, const Opt_CheckboxOptions* options);
    void (*setSelect)(Ark_NativePointer node, Ark_Boolean value);
    void (*setSelectedColor)(Ark_NativePointer node, const ResourceColor* value);
    void (*setShape)(Ark_NativePointer node, Ark_Int32 value);
    void (*setUnselectedColor)(Ark_NativePointer node, const ResourceColor* value);
    void (*setMark)(Ark_NativePointer node, const MarkStyle* value);
    void (*setOnChange)(Ark_NativePointer node, Ark_Function callback);
    void (*setContentModifier)(Ark_NativePointer node, const Ark_CustomObject* modifier);
} GENERATED_ArkUICheckboxModifier;

typedef struct GENERATED_ArkUICheckboxGroupModifier {
    void (*_setCheckboxGroupOptions)(Ark_NativePointer node, const Opt_CheckboxGroupOptions* options);
    void (*setSelectAll)(Ark_NativePointer node, Ark_Boolean value);
    void (*setSelectedColor)(Ark_NativePointer node, const ResourceColor* value);
    void (*setUnselectedColor)(Ark_NativePointer node, const ResourceColor* value);
    void (*setMark)(Ark_NativePointer node, const MarkStyle* value);
    void (*setOnChange)(Ark_NativePointer node, Ark_Function callback);
    void (*setCheckboxShape)(Ark_NativePointer node, Ark_Int32 value);
} GENERATED_ArkUICheckboxGroupModifier;

typedef struct GENERATED_ArkUICircleModifier {
    void (*_setCircleOptions)(Ark_NativePointer node, const Opt_CircleOptions* value);
} GENERATED_ArkUICircleModifier;

typedef struct GENERATED_ArkUIColumnModifier {
    void (*_setColumnOptions)(Ark_NativePointer node, const Opt_Type_ColumnInterface__setColumnOptions_Arg0* value);
    void (*setAlignItems)(Ark_NativePointer node, Ark_Int32 value);
    void (*setJustifyContent)(Ark_NativePointer node, Ark_Int32 value);
    void (*setPointLight)(Ark_NativePointer node, const PointLightStyle* value);
} GENERATED_ArkUIColumnModifier;

typedef struct GENERATED_ArkUIColumnSplitModifier {
    void (*_setColumnSplitOptions)(Ark_NativePointer node);
    void (*setResizeable)(Ark_NativePointer node, Ark_Boolean value);
    void (*setDivider)(Ark_NativePointer node, const Type_ColumnSplitAttribute_divider_Arg0* value);
} GENERATED_ArkUIColumnSplitModifier;

typedef struct GENERATED_ArkUICommonMethodModifier {
    void (*setWidth)(Ark_NativePointer node, const Ark_Length* value);
    void (*setHeight)(Ark_NativePointer node, const Ark_Length* value);
    void (*setDrawModifier)(Ark_NativePointer node, const Type_CommonMethod_drawModifier_Arg0* modifier);
    void (*setCustomProperty)(Ark_NativePointer node, const Ark_String* name, const Opt_Object* value);
    void (*setExpandSafeArea)(Ark_NativePointer node, const Opt_Array_Ark_SafeAreaType* types, const Opt_Array_Ark_SafeAreaEdge* edges);
    void (*setResponseRegion)(Ark_NativePointer node, const Type_CommonMethod_responseRegion_Arg0* value);
    void (*setMouseResponseRegion)(Ark_NativePointer node, const Type_CommonMethod_mouseResponseRegion_Arg0* value);
    void (*setSize)(Ark_NativePointer node, const SizeOptions* value);
    void (*setConstraintSize)(Ark_NativePointer node, const ConstraintSizeOptions* value);
    void (*setTouchable)(Ark_NativePointer node, Ark_Boolean value);
    void (*setHitTestBehavior)(Ark_NativePointer node, Ark_Int32 value);
    void (*setOnChildTouchTest)(Ark_NativePointer node, Ark_Function event);
    void (*setLayoutWeight)(Ark_NativePointer node, const Type_CommonMethod_layoutWeight_Arg0* value);
    void (*setPadding)(Ark_NativePointer node, const Type_CommonMethod_padding_Arg0* value);
    void (*setMargin)(Ark_NativePointer node, const Type_CommonMethod_margin_Arg0* value);
    void (*setBackground)(Ark_NativePointer node, const CustomBuilder* builder, const Opt_Type_CommonMethod_background_Arg1* options);
    void (*setBackgroundColor)(Ark_NativePointer node, const ResourceColor* value);
    void (*setPixelRound)(Ark_NativePointer node, const PixelRoundPolicy* value);
    void (*setBackgroundImage)(Ark_NativePointer node, const Type_CommonMethod_backgroundImage_Arg0* src, const Opt_Ark_ImageRepeat* repeat);
    void (*setBackgroundImageSize)(Ark_NativePointer node, const Type_CommonMethod_backgroundImageSize_Arg0* value);
    void (*setBackgroundImagePosition)(Ark_NativePointer node, const Type_CommonMethod_backgroundImagePosition_Arg0* value);
    void (*setBackgroundBlurStyle)(Ark_NativePointer node, Ark_Int32 value, const Opt_BackgroundBlurStyleOptions* options);
    void (*setBackgroundEffect)(Ark_NativePointer node, const BackgroundEffectOptions* options);
    void (*setBackgroundImageResizable)(Ark_NativePointer node, const ResizableOptions* value);
    void (*setForegroundEffect)(Ark_NativePointer node, const ForegroundEffectOptions* options);
    void (*setVisualEffect)(Ark_NativePointer node, const Ark_CustomObject* effect);
    void (*setBackgroundFilter)(Ark_NativePointer node, const Ark_CustomObject* filter);
    void (*setForegroundFilter)(Ark_NativePointer node, const Ark_CustomObject* filter);
    void (*setCompositingFilter)(Ark_NativePointer node, const Ark_CustomObject* filter);
    void (*setForegroundBlurStyle)(Ark_NativePointer node, Ark_Int32 value, const Opt_ForegroundBlurStyleOptions* options);
    void (*setOpacity)(Ark_NativePointer node, const Type_CommonMethod_opacity_Arg0* value);
    void (*setBorder)(Ark_NativePointer node, const BorderOptions* value);
    void (*setBorderStyle)(Ark_NativePointer node, const Type_CommonMethod_borderStyle_Arg0* value);
    void (*setBorderWidth)(Ark_NativePointer node, const Type_CommonMethod_borderWidth_Arg0* value);
    void (*setBorderColor)(Ark_NativePointer node, const Type_CommonMethod_borderColor_Arg0* value);
    void (*setBorderRadius)(Ark_NativePointer node, const Type_CommonMethod_borderRadius_Arg0* value);
    void (*setBorderImage)(Ark_NativePointer node, const BorderImageOption* value);
    void (*setOutline)(Ark_NativePointer node, const OutlineOptions* value);
    void (*setOutlineStyle)(Ark_NativePointer node, const Type_CommonMethod_outlineStyle_Arg0* value);
    void (*setOutlineWidth)(Ark_NativePointer node, const Type_CommonMethod_outlineWidth_Arg0* value);
    void (*setOutlineColor)(Ark_NativePointer node, const Type_CommonMethod_outlineColor_Arg0* value);
    void (*setOutlineRadius)(Ark_NativePointer node, const Type_CommonMethod_outlineRadius_Arg0* value);
    void (*setForegroundColor)(Ark_NativePointer node, const Type_CommonMethod_foregroundColor_Arg0* value);
    void (*setOnClick)(Ark_NativePointer node, Ark_Function event);
    void (*setOnHover)(Ark_NativePointer node, Ark_Function event);
    void (*setHoverEffect)(Ark_NativePointer node, Ark_Int32 value);
    void (*setOnMouse)(Ark_NativePointer node, Ark_Function event);
    void (*setOnTouch)(Ark_NativePointer node, Ark_Function event);
    void (*setOnKeyEvent)(Ark_NativePointer node, Ark_Function event);
    void (*setOnKeyPreIme)(Ark_NativePointer node, Ark_Function event);
    void (*setFocusable)(Ark_NativePointer node, Ark_Boolean value);
    void (*setOnFocus)(Ark_NativePointer node, Ark_Function event);
    void (*setOnBlur)(Ark_NativePointer node, Ark_Function event);
    void (*setTabIndex)(Ark_NativePointer node, const Ark_Number* index);
    void (*setDefaultFocus)(Ark_NativePointer node, Ark_Boolean value);
    void (*setGroupDefaultFocus)(Ark_NativePointer node, Ark_Boolean value);
    void (*setFocusOnTouch)(Ark_NativePointer node, Ark_Boolean value);
    void (*setFocusBox)(Ark_NativePointer node, const FocusBoxStyle* style);
    void (*setFocusScopeId)(Ark_NativePointer node, const Ark_String* id, const Opt_Ark_Boolean* isGroup);
    void (*setFocusScopePriority)(Ark_NativePointer node, const Ark_String* scopeId, const Opt_Ark_FocusPriority* priority);
    void (*setAnimation)(Ark_NativePointer node, const AnimateParam* value);
    void (*setTransition_TransitionOptionsTransitionEffect)(Ark_NativePointer node, const Type_CommonMethod_transition_Arg0* value);
    void (*setTransition_TransitionEffect_TransitionFinishCallbackundefined)(Ark_NativePointer node, const TransitionEffect* effect, const Opt_Ark_Function* onFinish);
    void (*setGesture)(Ark_NativePointer node, const GestureType* gesture, const Opt_Ark_GestureMask* mask);
    void (*setPriorityGesture)(Ark_NativePointer node, const GestureType* gesture, const Opt_Ark_GestureMask* mask);
    void (*setParallelGesture)(Ark_NativePointer node, const GestureType* gesture, const Opt_Ark_GestureMask* mask);
    void (*setBlur)(Ark_NativePointer node, const Ark_Number* value, const Opt_BlurOptions* options);
    void (*setLinearGradientBlur)(Ark_NativePointer node, const Ark_Number* value, const LinearGradientBlurOptions* options);
    void (*setMotionBlur)(Ark_NativePointer node, const MotionBlurOptions* value);
    void (*setBrightness)(Ark_NativePointer node, const Ark_Number* value);
    void (*setContrast)(Ark_NativePointer node, const Ark_Number* value);
    void (*setGrayscale)(Ark_NativePointer node, const Ark_Number* value);
    void (*setColorBlend)(Ark_NativePointer node, const Type_CommonMethod_colorBlend_Arg0* value);
    void (*setSaturate)(Ark_NativePointer node, const Ark_Number* value);
    void (*setSepia)(Ark_NativePointer node, const Ark_Number* value);
    void (*setInvert)(Ark_NativePointer node, const Type_CommonMethod_invert_Arg0* value);
    void (*setSystemBarEffect)(Ark_NativePointer node);
    void (*setHueRotate)(Ark_NativePointer node, const Type_CommonMethod_hueRotate_Arg0* value);
    void (*setUseShadowBatching)(Ark_NativePointer node, Ark_Boolean value);
    void (*setUseEffect)(Ark_NativePointer node, Ark_Boolean value);
    void (*setBackdropBlur)(Ark_NativePointer node, const Ark_Number* value, const Opt_BlurOptions* options);
    void (*setRenderGroup)(Ark_NativePointer node, Ark_Boolean value);
    void (*setFreeze)(Ark_NativePointer node, Ark_Boolean value);
    void (*setTranslate)(Ark_NativePointer node, const TranslateOptions* value);
    void (*setScale)(Ark_NativePointer node, const ScaleOptions* value);
    void (*setGridSpan)(Ark_NativePointer node, const Ark_Number* value);
    void (*setGridOffset)(Ark_NativePointer node, const Ark_Number* value);
    void (*setRotate)(Ark_NativePointer node, const RotateOptions* value);
    void (*setTransform)(Ark_NativePointer node, const Ark_CustomObject* value);
    void (*setOnAppear)(Ark_NativePointer node, Ark_Function event);
    void (*setOnDisAppear)(Ark_NativePointer node, Ark_Function event);
    void (*setOnAttach)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnDetach)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnAreaChange)(Ark_NativePointer node, Ark_Function event);
    void (*setVisibility)(Ark_NativePointer node, Ark_Int32 value);
    void (*setFlexGrow)(Ark_NativePointer node, const Ark_Number* value);
    void (*setFlexShrink)(Ark_NativePointer node, const Ark_Number* value);
    void (*setFlexBasis)(Ark_NativePointer node, const Type_CommonMethod_flexBasis_Arg0* value);
    void (*setAlignSelf)(Ark_NativePointer node, Ark_Int32 value);
    void (*setDisplayPriority)(Ark_NativePointer node, const Ark_Number* value);
    void (*setZIndex)(Ark_NativePointer node, const Ark_Number* value);
    void (*setSharedTransition)(Ark_NativePointer node, const Ark_String* id, const Opt_sharedTransitionOptions* options);
    void (*setDirection)(Ark_NativePointer node, Ark_Int32 value);
    void (*setAlign)(Ark_NativePointer node, Ark_Int32 value);
    void (*setPosition)(Ark_NativePointer node, const Type_CommonMethod_position_Arg0* value);
    void (*setMarkAnchor)(Ark_NativePointer node, const Type_CommonMethod_markAnchor_Arg0* value);
    void (*setOffset)(Ark_NativePointer node, const Type_CommonMethod_offset_Arg0* value);
    void (*setEnabled)(Ark_NativePointer node, Ark_Boolean value);
    void (*setUseSizeType)(Ark_NativePointer node, const Type_CommonMethod_useSizeType_Arg0* value);
    void (*setAlignRules_AlignRuleOption)(Ark_NativePointer node, const AlignRuleOption* value);
    void (*setAlignRules_LocalizedAlignRuleOptions)(Ark_NativePointer node, const LocalizedAlignRuleOptions* alignRule);
    void (*setChainMode)(Ark_NativePointer node, Ark_Int32 direction, Ark_Int32 style);
    void (*setAspectRatio)(Ark_NativePointer node, const Ark_Number* value);
    void (*setClickEffect)(Ark_NativePointer node, const Type_CommonMethod_clickEffect_Arg0* value);
    void (*setOnDragStart)(Ark_NativePointer node, Ark_Function event);
    void (*setOnDragEnter)(Ark_NativePointer node, Ark_Function event);
    void (*setOnDragMove)(Ark_NativePointer node, Ark_Function event);
    void (*setOnDragLeave)(Ark_NativePointer node, Ark_Function event);
    void (*setOnDrop)(Ark_NativePointer node, Ark_Function event);
    void (*setOnDragEnd)(Ark_NativePointer node, Ark_Function event);
    void (*setAllowDrop)(Ark_NativePointer node, const Type_CommonMethod_allowDrop_Arg0* value);
    void (*setDraggable)(Ark_NativePointer node, Ark_Boolean value);
    void (*setDragPreview)(Ark_NativePointer node, const Type_CommonMethod_dragPreview_Arg0* value);
    void (*setDragPreviewOptions)(Ark_NativePointer node, const DragPreviewOptions* value, const Opt_DragInteractionOptions* options);
    void (*setOnPreDrag)(Ark_NativePointer node, Ark_Function callback);
    void (*setOverlay)(Ark_NativePointer node, const Type_CommonMethod_overlay_Arg0* value, const Opt_OverlayOptions* options);
    void (*setLinearGradient)(Ark_NativePointer node, const Type_CommonMethod_linearGradient_Arg0* value);
    void (*setSweepGradient)(Ark_NativePointer node, const Type_CommonMethod_sweepGradient_Arg0* value);
    void (*setRadialGradient)(Ark_NativePointer node, const Type_CommonMethod_radialGradient_Arg0* value);
    void (*setMotionPath)(Ark_NativePointer node, const MotionPathOptions* value);
    void (*setShadow)(Ark_NativePointer node, const Type_CommonMethod_shadow_Arg0* value);
    void (*setBlendMode)(Ark_NativePointer node, Ark_Int32 value, const Opt_Ark_BlendApplyType* type);
    void (*setClip_boolean)(Ark_NativePointer node, Ark_Boolean value);
    void (*setClip_booleanCircleAttributeEllipseAttributePathAttributeRectAttribute)(Ark_NativePointer node, const Type_CommonMethod_clip1_Arg0* value);
    void (*setClipShape)(Ark_NativePointer node, const Type_CommonMethod_clipShape_Arg0* value);
    void (*setMask_ProgressMask)(Ark_NativePointer node, const Ark_Materialized* value);
    void (*setMask_CircleAttributeEllipseAttributePathAttributeRectAttributeProgressMask)(Ark_NativePointer node, const Type_CommonMethod_mask1_Arg0* value);
    void (*setMaskShape)(Ark_NativePointer node, const Type_CommonMethod_maskShape_Arg0* value);
    void (*setKey)(Ark_NativePointer node, const Ark_String* value);
    void (*setId)(Ark_NativePointer node, const Ark_String* value);
    void (*setGeometryTransition_string)(Ark_NativePointer node, const Ark_String* id);
    void (*setGeometryTransition_string_GeometryTransitionOptions)(Ark_NativePointer node, const Ark_String* id, const Opt_GeometryTransitionOptions* options);
    void (*setBindPopup)(Ark_NativePointer node, Ark_Boolean show, const Type_CommonMethod_bindPopup_Arg1* popup);
    void (*setBindMenu_ArrayMenuElementCustomBuilder_MenuOptions)(Ark_NativePointer node, const Type_CommonMethod_bindMenu_Arg0* content, const Opt_MenuOptions* options);
    void (*setBindMenu_boolean_ArrayMenuElementCustomBuilder_MenuOptions)(Ark_NativePointer node, Ark_Boolean isShow, const Type_CommonMethod_bindMenu1_Arg1* content, const Opt_MenuOptions* options);
    void (*setBindContextMenu_CustomBuilder_ResponseType_ContextMenuOptions)(Ark_NativePointer node, const CustomBuilder* content, Ark_Int32 responseType, const Opt_ContextMenuOptions* options);
    void (*setBindContextMenu_boolean_CustomBuilder_ContextMenuOptions)(Ark_NativePointer node, Ark_Boolean isShown, const CustomBuilder* content, const Opt_ContextMenuOptions* options);
    void (*setBindContentCover_booleanundefined_CustomBuilder_ModalTransition)(Ark_NativePointer node, const Opt_Ark_Boolean* isShow, const CustomBuilder* builder, const Opt_Ark_ModalTransition* type);
    void (*setBindContentCover_booleanundefined_CustomBuilder_ContentCoverOptions)(Ark_NativePointer node, const Opt_Ark_Boolean* isShow, const CustomBuilder* builder, const Opt_ContentCoverOptions* options);
    void (*setBindSheet)(Ark_NativePointer node, const Opt_Ark_Boolean* isShow, const CustomBuilder* builder, const Opt_SheetOptions* options);
    void (*setStateStyles)(Ark_NativePointer node, const StateStyles* value);
    void (*setRestoreId)(Ark_NativePointer node, const Ark_Number* value);
    void (*setOnVisibleAreaChange)(Ark_NativePointer node, const Array_Ark_Number* ratios, Ark_Function event);
    void (*setSphericalEffect)(Ark_NativePointer node, const Ark_Number* value);
    void (*setLightUpEffect)(Ark_NativePointer node, const Ark_Number* value);
    void (*setPixelStretchEffect)(Ark_NativePointer node, const PixelStretchEffectOptions* options);
    void (*setKeyboardShortcut)(Ark_NativePointer node, const Type_CommonMethod_keyboardShortcut_Arg0* value, const Array_Ark_ModifierKey* keys, const Opt_Ark_Function* action);
    void (*setAccessibilityGroup)(Ark_NativePointer node, Ark_Boolean value);
    void (*setAccessibilityText_string)(Ark_NativePointer node, const Ark_String* value);
    void (*setAccessibilityText_Resource)(Ark_NativePointer node, const Ark_CustomObject* text);
    void (*setAccessibilityTextHint)(Ark_NativePointer node, const Ark_String* value);
    void (*setAccessibilityDescription_string)(Ark_NativePointer node, const Ark_String* value);
    void (*setAccessibilityDescription_Resource)(Ark_NativePointer node, const Ark_CustomObject* description);
    void (*setAccessibilityLevel)(Ark_NativePointer node, const Ark_String* value);
    void (*setAccessibilityVirtualNode)(Ark_NativePointer node, const CustomBuilder* builder);
    void (*setObscured)(Ark_NativePointer node, const Array_Ark_ObscuredReasons* reasons);
    void (*setReuseId)(Ark_NativePointer node, const Ark_String* id);
    void (*setRenderFit)(Ark_NativePointer node, Ark_Int32 fitMode);
    void (*setGestureModifier)(Ark_NativePointer node, const Ark_Materialized* modifier);
    void (*setBackgroundBrightness)(Ark_NativePointer node, const BackgroundBrightnessOptions* params);
    void (*setOnGestureJudgeBegin)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnGestureRecognizerJudgeBegin)(Ark_NativePointer node, Ark_Function callback);
    void (*setShouldBuiltInRecognizerParallelWith)(Ark_NativePointer node, Ark_Function callback);
    void (*setMonopolizeEvents)(Ark_NativePointer node, Ark_Boolean monopolize);
    void (*setOnTouchIntercept)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnSizeChange)(Ark_NativePointer node, Ark_Function event);
} GENERATED_ArkUICommonMethodModifier;

typedef struct GENERATED_ArkUICommonShapeMethodModifier {
    void (*setStroke)(Ark_NativePointer node, const ResourceColor* value);
    void (*setFill)(Ark_NativePointer node, const ResourceColor* value);
    void (*setStrokeDashOffset)(Ark_NativePointer node, const Type_CommonShapeMethod_strokeDashOffset_Arg0* value);
    void (*setStrokeLineCap)(Ark_NativePointer node, Ark_Int32 value);
    void (*setStrokeLineJoin)(Ark_NativePointer node, Ark_Int32 value);
    void (*setStrokeMiterLimit)(Ark_NativePointer node, const Type_CommonShapeMethod_strokeMiterLimit_Arg0* value);
    void (*setStrokeOpacity)(Ark_NativePointer node, const Type_CommonShapeMethod_strokeOpacity_Arg0* value);
    void (*setFillOpacity)(Ark_NativePointer node, const Type_CommonShapeMethod_fillOpacity_Arg0* value);
    void (*setStrokeWidth)(Ark_NativePointer node, const Ark_Length* value);
    void (*setAntiAlias)(Ark_NativePointer node, Ark_Boolean value);
    void (*setStrokeDashArray)(Ark_NativePointer node, const Array_Ark_CustomObject* value);
} GENERATED_ArkUICommonShapeMethodModifier;

typedef struct GENERATED_ArkUICommonModifier {
    void (*_setCommonOptions)(Ark_NativePointer node);
} GENERATED_ArkUICommonModifier;

typedef struct GENERATED_ArkUIScrollableCommonMethodModifier {
    void (*setScrollBar)(Ark_NativePointer node, Ark_Int32 barState);
    void (*setScrollBarColor)(Ark_NativePointer node, const Type_ScrollableCommonMethod_scrollBarColor_Arg0* color);
    void (*setScrollBarWidth)(Ark_NativePointer node, const Type_ScrollableCommonMethod_scrollBarWidth_Arg0* value);
    void (*setEdgeEffect)(Ark_NativePointer node, Ark_Int32 edgeEffect, const Opt_EdgeEffectOptions* options);
    void (*setNestedScroll)(Ark_NativePointer node, const NestedScrollOptions* value);
    void (*setEnableScrollInteraction)(Ark_NativePointer node, Ark_Boolean value);
    void (*setFriction)(Ark_NativePointer node, const Type_ScrollableCommonMethod_friction_Arg0* value);
    void (*setOnScroll)(Ark_NativePointer node, Ark_Function event);
    void (*setOnWillScroll)(Ark_NativePointer node, const Ark_CustomObject* stub_for_onWillScroll);
    void (*setOnDidScroll)(Ark_NativePointer node, Ark_Function handler);
    void (*setOnReachStart)(Ark_NativePointer node, Ark_Function event);
    void (*setOnReachEnd)(Ark_NativePointer node, Ark_Function event);
    void (*setOnScrollStart)(Ark_NativePointer node, Ark_Function event);
    void (*setOnScrollStop)(Ark_NativePointer node, Ark_Function event);
    void (*setFlingSpeedLimit)(Ark_NativePointer node, const Ark_Number* speedLimit);
} GENERATED_ArkUIScrollableCommonMethodModifier;

typedef struct GENERATED_ArkUIComponent3DModifier {
    void (*_setComponent3DOptions)(Ark_NativePointer node, const Opt_SceneOptions* sceneOptions);
    void (*setEnvironment)(Ark_NativePointer node, const Ark_CustomObject* uri);
    void (*setCustomRender)(Ark_NativePointer node, const Ark_CustomObject* uri, Ark_Boolean selfRenderUpdate);
    void (*setShader)(Ark_NativePointer node, const Ark_CustomObject* uri);
    void (*setShaderImageTexture)(Ark_NativePointer node, const Ark_CustomObject* uri);
    void (*setShaderInputBuffer)(Ark_NativePointer node, const Array_Ark_Number* buffer);
    void (*setRenderWidth)(Ark_NativePointer node, const Ark_Length* value);
    void (*setRenderHeight)(Ark_NativePointer node, const Ark_Length* value);
} GENERATED_ArkUIComponent3DModifier;

typedef struct GENERATED_ArkUIContainerSpanModifier {
    void (*_setContainerSpanOptions)(Ark_NativePointer node);
    void (*setTextBackgroundStyle)(Ark_NativePointer node, const TextBackgroundStyle* style);
} GENERATED_ArkUIContainerSpanModifier;

typedef struct GENERATED_ArkUICounterModifier {
    void (*_setCounterOptions)(Ark_NativePointer node);
    void (*setOnInc)(Ark_NativePointer node, Ark_Function event);
    void (*setOnDec)(Ark_NativePointer node, Ark_Function event);
    void (*setEnableDec)(Ark_NativePointer node, Ark_Boolean value);
    void (*setEnableInc)(Ark_NativePointer node, Ark_Boolean value);
} GENERATED_ArkUICounterModifier;

typedef struct GENERATED_ArkUIDataPanelModifier {
    void (*_setDataPanelOptions)(Ark_NativePointer node, const DataPanelOptions* options);
    void (*setCloseEffect)(Ark_NativePointer node, Ark_Boolean value);
    void (*setValueColors)(Ark_NativePointer node, const Array_Union_ResourceColor_LinearGradient* value);
    void (*setTrackBackgroundColor)(Ark_NativePointer node, const ResourceColor* value);
    void (*setStrokeWidth)(Ark_NativePointer node, const Ark_Length* value);
    void (*setTrackShadow)(Ark_NativePointer node, const DataPanelShadowOptions* value);
    void (*setContentModifier)(Ark_NativePointer node, const Ark_CustomObject* modifier);
} GENERATED_ArkUIDataPanelModifier;

typedef struct GENERATED_ArkUIDatePickerModifier {
    void (*_setDatePickerOptions)(Ark_NativePointer node, const Opt_DatePickerOptions* options);
    void (*setLunar)(Ark_NativePointer node, Ark_Boolean value);
    void (*setDisappearTextStyle)(Ark_NativePointer node, const PickerTextStyle* value);
    void (*setTextStyle)(Ark_NativePointer node, const PickerTextStyle* value);
    void (*setSelectedTextStyle)(Ark_NativePointer node, const PickerTextStyle* value);
    void (*setOnChange)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnDateChange)(Ark_NativePointer node, Ark_Function callback);
} GENERATED_ArkUIDatePickerModifier;

typedef struct GENERATED_ArkUIDividerModifier {
    void (*_setDividerOptions)(Ark_NativePointer node);
    void (*setVertical)(Ark_NativePointer node, Ark_Boolean value);
    void (*setColor)(Ark_NativePointer node, const ResourceColor* value);
    void (*setStrokeWidth)(Ark_NativePointer node, const Type_DividerAttribute_strokeWidth_Arg0* value);
    void (*setLineCap)(Ark_NativePointer node, Ark_Int32 value);
} GENERATED_ArkUIDividerModifier;

typedef struct GENERATED_ArkUIEffectComponentModifier {
    void (*_setEffectComponentOptions)(Ark_NativePointer node);
} GENERATED_ArkUIEffectComponentModifier;

typedef struct GENERATED_ArkUIEllipseModifier {
    void (*_setEllipseOptions)(Ark_NativePointer node, const Opt_Type_EllipseInterface__setEllipseOptions_Arg0* value);
} GENERATED_ArkUIEllipseModifier;

typedef struct GENERATED_ArkUIEmbeddedComponentModifier {
    void (*_setEmbeddedComponentOptions)(Ark_NativePointer node, const Ark_CustomObject* loader, Ark_Int32 type);
    void (*setOnTerminated)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnError)(Ark_NativePointer node, const Ark_CustomObject* callback);
} GENERATED_ArkUIEmbeddedComponentModifier;

typedef struct GENERATED_ArkUIFlexModifier {
    void (*_setFlexOptions)(Ark_NativePointer node, const Opt_FlexOptions* value);
    void (*setPointLight)(Ark_NativePointer node, const PointLightStyle* value);
} GENERATED_ArkUIFlexModifier;

typedef struct GENERATED_ArkUIFlowItemModifier {
    void (*_setFlowItemOptions)(Ark_NativePointer node);
} GENERATED_ArkUIFlowItemModifier;

typedef struct GENERATED_ArkUIFolderStackModifier {
    void (*_setFolderStackOptions)(Ark_NativePointer node, const Opt_Type_FolderStackInterface__setFolderStackOptions_Arg0* value);
    void (*setAlignContent)(Ark_NativePointer node, Ark_Int32 value);
    void (*setOnFolderStateChange)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnHoverStatusChange)(Ark_NativePointer node, Ark_Function handler);
    void (*setEnableAnimation)(Ark_NativePointer node, Ark_Boolean value);
    void (*setAutoHalfFold)(Ark_NativePointer node, Ark_Boolean value);
} GENERATED_ArkUIFolderStackModifier;

typedef struct GENERATED_ArkUIFormComponentModifier {
    void (*_setFormComponentOptions)(Ark_NativePointer node, const FormInfo* value);
    void (*setSize)(Ark_NativePointer node, const Type_FormComponentAttribute_size_Arg0* value);
    void (*setModuleName)(Ark_NativePointer node, const Ark_String* value);
    void (*setDimension)(Ark_NativePointer node, Ark_Int32 value);
    void (*setAllowUpdate)(Ark_NativePointer node, Ark_Boolean value);
    void (*setVisibility)(Ark_NativePointer node, Ark_Int32 value);
    void (*setOnAcquired)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnError)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnRouter)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnUninstall)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnLoad)(Ark_NativePointer node, Ark_Function callback);
} GENERATED_ArkUIFormComponentModifier;

typedef struct GENERATED_ArkUIFormLinkModifier {
    void (*_setFormLinkOptions)(Ark_NativePointer node, const FormLinkOptions* options);
} GENERATED_ArkUIFormLinkModifier;

typedef struct GENERATED_ArkUIGaugeModifier {
    void (*_setGaugeOptions)(Ark_NativePointer node, const Type_GaugeInterface__setGaugeOptions_Arg0* options);
    void (*setValue)(Ark_NativePointer node, const Ark_Number* value);
    void (*setStartAngle)(Ark_NativePointer node, const Ark_Number* angle);
    void (*setEndAngle)(Ark_NativePointer node, const Ark_Number* angle);
    void (*setColors)(Ark_NativePointer node, const Type_GaugeAttribute_colors_Arg0* colors);
    void (*setStrokeWidth)(Ark_NativePointer node, const Ark_Length* length);
    void (*setDescription)(Ark_NativePointer node, const CustomBuilder* value);
    void (*setTrackShadow)(Ark_NativePointer node, const GaugeShadowOptions* value);
    void (*setIndicator)(Ark_NativePointer node, const GaugeIndicatorOptions* value);
    void (*setPrivacySensitive)(Ark_NativePointer node, const Opt_Ark_Boolean* isPrivacySensitiveMode);
    void (*setContentModifier)(Ark_NativePointer node, const Ark_CustomObject* modifier);
} GENERATED_ArkUIGaugeModifier;

typedef struct GENERATED_ArkUIGridModifier {
    void (*_setGridOptions)(Ark_NativePointer node, const Opt_Scroller* scroller, const Opt_GridLayoutOptions* layoutOptions);
    void (*setColumnsTemplate)(Ark_NativePointer node, const Ark_String* value);
    void (*setRowsTemplate)(Ark_NativePointer node, const Ark_String* value);
    void (*setColumnsGap)(Ark_NativePointer node, const Ark_Length* value);
    void (*setRowsGap)(Ark_NativePointer node, const Ark_Length* value);
    void (*setScrollBarWidth)(Ark_NativePointer node, const Type_GridAttribute_scrollBarWidth_Arg0* value);
    void (*setScrollBarColor)(Ark_NativePointer node, const Type_GridAttribute_scrollBarColor_Arg0* value);
    void (*setScrollBar)(Ark_NativePointer node, Ark_Int32 value);
    void (*setOnScrollBarUpdate)(Ark_NativePointer node, Ark_Function event);
    void (*setOnScrollIndex)(Ark_NativePointer node, Ark_Function event);
    void (*setCachedCount)(Ark_NativePointer node, const Ark_Number* value);
    void (*setEditMode)(Ark_NativePointer node, Ark_Boolean value);
    void (*setMultiSelectable)(Ark_NativePointer node, Ark_Boolean value);
    void (*setMaxCount)(Ark_NativePointer node, const Ark_Number* value);
    void (*setMinCount)(Ark_NativePointer node, const Ark_Number* value);
    void (*setCellLength)(Ark_NativePointer node, const Ark_Number* value);
    void (*setLayoutDirection)(Ark_NativePointer node, Ark_Int32 value);
    void (*setSupportAnimation)(Ark_NativePointer node, Ark_Boolean value);
    void (*setOnItemDragStart)(Ark_NativePointer node, Ark_Function event);
    void (*setOnItemDragEnter)(Ark_NativePointer node, Ark_Function event);
    void (*setOnItemDragMove)(Ark_NativePointer node, Ark_Function event);
    void (*setOnItemDragLeave)(Ark_NativePointer node, Ark_Function event);
    void (*setOnItemDrop)(Ark_NativePointer node, Ark_Function event);
    void (*setEdgeEffect)(Ark_NativePointer node, Ark_Int32 value, const Opt_EdgeEffectOptions* options);
    void (*setNestedScroll)(Ark_NativePointer node, const NestedScrollOptions* value);
    void (*setEnableScrollInteraction)(Ark_NativePointer node, Ark_Boolean value);
    void (*setFriction)(Ark_NativePointer node, const Type_GridAttribute_friction_Arg0* value);
    void (*setOnScroll)(Ark_NativePointer node, Ark_Function event);
    void (*setOnReachStart)(Ark_NativePointer node, Ark_Function event);
    void (*setOnReachEnd)(Ark_NativePointer node, Ark_Function event);
    void (*setOnScrollStart)(Ark_NativePointer node, Ark_Function event);
    void (*setOnScrollStop)(Ark_NativePointer node, Ark_Function event);
    void (*setOnScrollFrameBegin)(Ark_NativePointer node, Ark_Function event);
} GENERATED_ArkUIGridModifier;

typedef struct GENERATED_ArkUIGridItemModifier {
    void (*_setGridItemOptions)(Ark_NativePointer node, const Opt_GridItemOptions* value);
    void (*setRowStart)(Ark_NativePointer node, const Ark_Number* value);
    void (*setRowEnd)(Ark_NativePointer node, const Ark_Number* value);
    void (*setColumnStart)(Ark_NativePointer node, const Ark_Number* value);
    void (*setColumnEnd)(Ark_NativePointer node, const Ark_Number* value);
    void (*setForceRebuild)(Ark_NativePointer node, Ark_Boolean value);
    void (*setSelectable)(Ark_NativePointer node, Ark_Boolean value);
    void (*setSelected)(Ark_NativePointer node, Ark_Boolean value);
    void (*setOnSelect)(Ark_NativePointer node, Ark_Function event);
} GENERATED_ArkUIGridItemModifier;

typedef struct GENERATED_ArkUIGridColModifier {
    void (*_setGridColOptions)(Ark_NativePointer node, const Opt_GridColOptions* option);
    void (*setSpan)(Ark_NativePointer node, const Type_GridColAttribute_span_Arg0* value);
    void (*setGridColOffset)(Ark_NativePointer node, const Type_GridColAttribute_gridColOffset_Arg0* value);
    void (*setOrder)(Ark_NativePointer node, const Type_GridColAttribute_order_Arg0* value);
} GENERATED_ArkUIGridColModifier;

typedef struct GENERATED_ArkUIGridContainerModifier {
    void (*_setGridContainerOptions)(Ark_NativePointer node, const Opt_GridContainerOptions* value);
} GENERATED_ArkUIGridContainerModifier;

typedef struct GENERATED_ArkUIGridRowModifier {
    void (*_setGridRowOptions)(Ark_NativePointer node, const Opt_GridRowOptions* option);
    void (*setOnBreakpointChange)(Ark_NativePointer node, Ark_Function callback);
    void (*setAlignItems)(Ark_NativePointer node, Ark_Int32 value);
} GENERATED_ArkUIGridRowModifier;

typedef struct GENERATED_ArkUIHyperlinkModifier {
    void (*_setHyperlinkOptions)(Ark_NativePointer node, const Type_HyperlinkInterface__setHyperlinkOptions_Arg0* address, const Opt_Type_HyperlinkInterface__setHyperlinkOptions_Arg1* content);
    void (*setColor)(Ark_NativePointer node, const Type_HyperlinkAttribute_color_Arg0* value);
} GENERATED_ArkUIHyperlinkModifier;

typedef struct GENERATED_ArkUIImageModifier {
    void (*_setImageOptions_PixelMapResourceStrDrawableDescriptor)(Ark_NativePointer node, const Type_ImageInterface__setImageOptions_Arg0* src);
    void (*_setImageOptions_PixelMapResourceStrDrawableDescriptor_ImageAIOptions)(Ark_NativePointer node, const Type_ImageInterface__setImageOptions1_Arg0* src, const ImageAIOptions* imageAIOptions);
    void (*setAlt)(Ark_NativePointer node, const Type_ImageAttribute_alt_Arg0* value);
    void (*setMatchTextDirection)(Ark_NativePointer node, Ark_Boolean value);
    void (*setFitOriginalSize)(Ark_NativePointer node, Ark_Boolean value);
    void (*setFillColor)(Ark_NativePointer node, const ResourceColor* value);
    void (*setObjectFit)(Ark_NativePointer node, Ark_Int32 value);
    void (*setObjectRepeat)(Ark_NativePointer node, Ark_Int32 value);
    void (*setAutoResize)(Ark_NativePointer node, Ark_Boolean value);
    void (*setRenderMode)(Ark_NativePointer node, Ark_Int32 value);
    void (*setDynamicRangeMode)(Ark_NativePointer node, Ark_Int32 value);
    void (*setInterpolation)(Ark_NativePointer node, Ark_Int32 value);
    void (*setSourceSize)(Ark_NativePointer node, const Type_ImageAttribute_sourceSize_Arg0* value);
    void (*setSyncLoad)(Ark_NativePointer node, Ark_Boolean value);
    void (*setColorFilter)(Ark_NativePointer node, const Type_ImageAttribute_colorFilter_Arg0* value);
    void (*setCopyOption)(Ark_NativePointer node, Ark_Int32 value);
    void (*setDraggable)(Ark_NativePointer node, Ark_Boolean value);
    void (*setPointLight)(Ark_NativePointer node, const PointLightStyle* value);
    void (*setEdgeAntialiasing)(Ark_NativePointer node, const Ark_Number* value);
    void (*setOnComplete)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnError)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnFinish)(Ark_NativePointer node, Ark_Function event);
    void (*setEnableAnalyzer)(Ark_NativePointer node, Ark_Boolean enable);
    void (*setAnalyzerConfig)(Ark_NativePointer node, const ImageAnalyzerConfig* config);
    void (*setResizable)(Ark_NativePointer node, const ResizableOptions* value);
    void (*setPrivacySensitive)(Ark_NativePointer node, Ark_Boolean supported);
    void (*setEnhancedImageQuality)(Ark_NativePointer node, const Ark_CustomObject* imageQuality);
} GENERATED_ArkUIImageModifier;

typedef struct GENERATED_ArkUIImageAnimatorModifier {
    void (*_setImageAnimatorOptions)(Ark_NativePointer node);
    void (*setImages)(Ark_NativePointer node, const Array_ImageFrameInfo* value);
    void (*setState)(Ark_NativePointer node, Ark_Int32 value);
    void (*setDuration)(Ark_NativePointer node, const Ark_Number* value);
    void (*setReverse)(Ark_NativePointer node, Ark_Boolean value);
    void (*setFixedSize)(Ark_NativePointer node, Ark_Boolean value);
    void (*setPreDecode)(Ark_NativePointer node, const Ark_Number* value);
    void (*setFillMode)(Ark_NativePointer node, Ark_Int32 value);
    void (*setIterations)(Ark_NativePointer node, const Ark_Number* value);
    void (*setOnStart)(Ark_NativePointer node, Ark_Function event);
    void (*setOnPause)(Ark_NativePointer node, Ark_Function event);
    void (*setOnRepeat)(Ark_NativePointer node, Ark_Function event);
    void (*setOnCancel)(Ark_NativePointer node, Ark_Function event);
    void (*setOnFinish)(Ark_NativePointer node, Ark_Function event);
} GENERATED_ArkUIImageAnimatorModifier;

typedef struct GENERATED_ArkUIImageSpanModifier {
    void (*_setImageSpanOptions)(Ark_NativePointer node, const Type_ImageSpanInterface__setImageSpanOptions_Arg0* value);
    void (*setVerticalAlign)(Ark_NativePointer node, Ark_Int32 value);
    void (*setColorFilter)(Ark_NativePointer node, const Type_ImageSpanAttribute_colorFilter_Arg0* filter);
    void (*setObjectFit)(Ark_NativePointer node, Ark_Int32 value);
    void (*setOnComplete)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnError)(Ark_NativePointer node, Ark_Function callback);
    void (*setAlt)(Ark_NativePointer node, const Ark_CustomObject* value);
} GENERATED_ArkUIImageSpanModifier;

typedef struct GENERATED_ArkUILineModifier {
    void (*_setLineOptions)(Ark_NativePointer node, const Opt_Type_LineInterface__setLineOptions_Arg0* value);
    void (*setStartPoint)(Ark_NativePointer node, const Array_Ark_CustomObject* value);
    void (*setEndPoint)(Ark_NativePointer node, const Array_Ark_CustomObject* value);
} GENERATED_ArkUILineModifier;

typedef struct GENERATED_ArkUIListModifier {
    void (*_setListOptions)(Ark_NativePointer node, const Opt_Type_ListInterface__setListOptions_Arg0* value);
    void (*setLanes)(Ark_NativePointer node, const Type_ListAttribute_lanes_Arg0* value, const Opt_Dimension* gutter);
    void (*setAlignListItem)(Ark_NativePointer node, Ark_Int32 value);
    void (*setListDirection)(Ark_NativePointer node, Ark_Int32 value);
    void (*setScrollBar)(Ark_NativePointer node, Ark_Int32 value);
    void (*setEdgeEffect)(Ark_NativePointer node, Ark_Int32 value, const Opt_EdgeEffectOptions* options);
    void (*setFadingEdge)(Ark_NativePointer node, const Opt_Ark_Boolean* value);
    void (*setContentStartOffset)(Ark_NativePointer node, const Ark_Number* value);
    void (*setContentEndOffset)(Ark_NativePointer node, const Ark_Number* value);
    void (*setDivider)(Ark_NativePointer node, const Type_ListAttribute_divider_Arg0* value);
    void (*setEditMode)(Ark_NativePointer node, Ark_Boolean value);
    void (*setMultiSelectable)(Ark_NativePointer node, Ark_Boolean value);
    void (*setCachedCount)(Ark_NativePointer node, const Ark_Number* value);
    void (*setChainAnimation)(Ark_NativePointer node, Ark_Boolean value);
    void (*setChainAnimationOptions)(Ark_NativePointer node, const ChainAnimationOptions* value);
    void (*setSticky)(Ark_NativePointer node, Ark_Int32 value);
    void (*setScrollSnapAlign)(Ark_NativePointer node, Ark_Int32 value);
    void (*setNestedScroll)(Ark_NativePointer node, const NestedScrollOptions* value);
    void (*setEnableScrollInteraction)(Ark_NativePointer node, Ark_Boolean value);
    void (*setFriction)(Ark_NativePointer node, const Type_ListAttribute_friction_Arg0* value);
    void (*setChildrenMainSize)(Ark_NativePointer node, const Ark_Materialized* value);
    void (*setOnScroll)(Ark_NativePointer node, Ark_Function event);
    void (*setOnScrollIndex)(Ark_NativePointer node, Ark_Function event);
    void (*setOnScrollVisibleContentChange)(Ark_NativePointer node, Ark_Function handler);
    void (*setOnReachStart)(Ark_NativePointer node, Ark_Function event);
    void (*setOnReachEnd)(Ark_NativePointer node, Ark_Function event);
    void (*setOnScrollStart)(Ark_NativePointer node, Ark_Function event);
    void (*setOnScrollStop)(Ark_NativePointer node, Ark_Function event);
    void (*setOnItemDelete)(Ark_NativePointer node, Ark_Function event);
    void (*setOnItemMove)(Ark_NativePointer node, Ark_Function event);
    void (*setOnItemDragStart)(Ark_NativePointer node, Ark_Function event);
    void (*setOnItemDragEnter)(Ark_NativePointer node, Ark_Function event);
    void (*setOnItemDragMove)(Ark_NativePointer node, Ark_Function event);
    void (*setOnItemDragLeave)(Ark_NativePointer node, Ark_Function event);
    void (*setOnItemDrop)(Ark_NativePointer node, Ark_Function event);
    void (*setOnScrollFrameBegin)(Ark_NativePointer node, Ark_Function event);
} GENERATED_ArkUIListModifier;

typedef struct GENERATED_ArkUIListItemModifier {
    void (*_setListItemOptions_ListItemOptions)(Ark_NativePointer node, const Opt_ListItemOptions* value);
    void (*_setListItemOptions_string)(Ark_NativePointer node, const Opt_Ark_String* value);
    void (*setSticky)(Ark_NativePointer node, Ark_Int32 value);
    void (*setEditable)(Ark_NativePointer node, const Type_ListItemAttribute_editable_Arg0* value);
    void (*setSelectable)(Ark_NativePointer node, Ark_Boolean value);
    void (*setSelected)(Ark_NativePointer node, Ark_Boolean value);
    void (*setSwipeAction)(Ark_NativePointer node, const SwipeActionOptions* value);
    void (*setOnSelect)(Ark_NativePointer node, Ark_Function event);
} GENERATED_ArkUIListItemModifier;

typedef struct GENERATED_ArkUIListItemGroupModifier {
    void (*_setListItemGroupOptions)(Ark_NativePointer node, const Opt_ListItemGroupOptions* options);
    void (*setDivider)(Ark_NativePointer node, const Type_ListItemGroupAttribute_divider_Arg0* value);
    void (*setChildrenMainSize)(Ark_NativePointer node, const Ark_Materialized* value);
} GENERATED_ArkUIListItemGroupModifier;

typedef struct GENERATED_ArkUILoadingProgressModifier {
    void (*_setLoadingProgressOptions)(Ark_NativePointer node);
    void (*setColor)(Ark_NativePointer node, const ResourceColor* value);
    void (*setEnableLoading)(Ark_NativePointer node, Ark_Boolean value);
    void (*setContentModifier)(Ark_NativePointer node, const Ark_CustomObject* modifier);
} GENERATED_ArkUILoadingProgressModifier;

typedef struct GENERATED_ArkUILocationButtonModifier {
    void (*_setLocationButtonOptions_)(Ark_NativePointer node);
    void (*_setLocationButtonOptions_LocationButtonOptions)(Ark_NativePointer node, const LocationButtonOptions* options);
    void (*setOnClick)(Ark_NativePointer node, Ark_Function event);
} GENERATED_ArkUILocationButtonModifier;

typedef struct GENERATED_ArkUIMarqueeModifier {
    void (*_setMarqueeOptions)(Ark_NativePointer node, const Type_MarqueeInterface__setMarqueeOptions_Arg0* value);
    void (*setFontColor)(Ark_NativePointer node, const ResourceColor* value);
    void (*setFontSize)(Ark_NativePointer node, const Ark_Length* value);
    void (*setAllowScale)(Ark_NativePointer node, Ark_Boolean value);
    void (*setFontWeight)(Ark_NativePointer node, const Type_MarqueeAttribute_fontWeight_Arg0* value);
    void (*setFontFamily)(Ark_NativePointer node, const Type_MarqueeAttribute_fontFamily_Arg0* value);
    void (*setMarqueeUpdateStrategy)(Ark_NativePointer node, Ark_Int32 value);
    void (*setOnStart)(Ark_NativePointer node, Ark_Function event);
    void (*setOnBounce)(Ark_NativePointer node, Ark_Function event);
    void (*setOnFinish)(Ark_NativePointer node, Ark_Function event);
} GENERATED_ArkUIMarqueeModifier;

typedef struct GENERATED_ArkUIMediaCachedImageModifier {
    void (*_setMediaCachedImageOptions)(Ark_NativePointer node, const Type_MediaCachedImageInterface__setMediaCachedImageOptions_Arg0* src);
} GENERATED_ArkUIMediaCachedImageModifier;

typedef struct GENERATED_ArkUIMenuModifier {
    void (*_setMenuOptions)(Ark_NativePointer node);
    void (*setFontSize)(Ark_NativePointer node, const Ark_Length* value);
    void (*setFont)(Ark_NativePointer node, const Font* value);
    void (*setFontColor)(Ark_NativePointer node, const ResourceColor* value);
    void (*setRadius)(Ark_NativePointer node, const Type_MenuAttribute_radius_Arg0* value);
    void (*setMenuItemDivider)(Ark_NativePointer node, const Type_MenuAttribute_menuItemDivider_Arg0* options);
    void (*setMenuItemGroupDivider)(Ark_NativePointer node, const Type_MenuAttribute_menuItemGroupDivider_Arg0* options);
    void (*setSubMenuExpandingMode)(Ark_NativePointer node, Ark_Int32 mode);
} GENERATED_ArkUIMenuModifier;

typedef struct GENERATED_ArkUIMenuItemModifier {
    void (*_setMenuItemOptions)(Ark_NativePointer node, const Opt_Type_MenuItemInterface__setMenuItemOptions_Arg0* value);
    void (*setSelected)(Ark_NativePointer node, Ark_Boolean value);
    void (*setSelectIcon)(Ark_NativePointer node, const Type_MenuItemAttribute_selectIcon_Arg0* value);
    void (*setOnChange)(Ark_NativePointer node, Ark_Function callback);
    void (*setContentFont)(Ark_NativePointer node, const Font* value);
    void (*setContentFontColor)(Ark_NativePointer node, const ResourceColor* value);
    void (*setLabelFont)(Ark_NativePointer node, const Font* value);
    void (*setLabelFontColor)(Ark_NativePointer node, const ResourceColor* value);
} GENERATED_ArkUIMenuItemModifier;

typedef struct GENERATED_ArkUIMenuItemGroupModifier {
    void (*_setMenuItemGroupOptions)(Ark_NativePointer node, const Opt_MenuItemGroupOptions* value);
} GENERATED_ArkUIMenuItemGroupModifier;

typedef struct GENERATED_ArkUINavDestinationModifier {
    void (*_setNavDestinationOptions)(Ark_NativePointer node);
    void (*setTitle)(Ark_NativePointer node, const Type_NavDestinationAttribute_title_Arg0* value, const Opt_NavigationTitleOptions* options);
    void (*setHideTitleBar)(Ark_NativePointer node, Ark_Boolean value);
    void (*setOnShown)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnHidden)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnBackPressed)(Ark_NativePointer node, Ark_Function callback);
    void (*setMode)(Ark_NativePointer node, Ark_Int32 value);
    void (*setBackButtonIcon)(Ark_NativePointer node, const Type_NavDestinationAttribute_backButtonIcon_Arg0* value);
    void (*setMenus)(Ark_NativePointer node, const Type_NavDestinationAttribute_menus_Arg0* value);
    void (*setOnReady)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnWillAppear)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnWillDisappear)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnWillShow)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnWillHide)(Ark_NativePointer node, Ark_Function callback);
    void (*setIgnoreLayoutSafeArea)(Ark_NativePointer node, const Opt_Array_Ark_LayoutSafeAreaType* types, const Opt_Array_Ark_LayoutSafeAreaEdge* edges);
    void (*setSystemBarStyle)(Ark_NativePointer node, const Opt_Ark_CustomObject* style);
} GENERATED_ArkUINavDestinationModifier;

typedef struct GENERATED_ArkUINavRouterModifier {
    void (*_setNavRouterOptions_)(Ark_NativePointer node);
    void (*_setNavRouterOptions_RouteInfo)(Ark_NativePointer node, const RouteInfo* value);
    void (*setOnStateChange)(Ark_NativePointer node, Ark_Function callback);
    void (*setMode)(Ark_NativePointer node, Ark_Int32 mode);
} GENERATED_ArkUINavRouterModifier;

typedef struct GENERATED_ArkUINavigationModifier {
    void (*_setNavigationOptions_)(Ark_NativePointer node);
    void (*_setNavigationOptions_NavPathStack)(Ark_NativePointer node, const Ark_Materialized* pathInfos);
    void (*setNavBarWidth)(Ark_NativePointer node, const Ark_Length* value);
    void (*setNavBarPosition)(Ark_NativePointer node, Ark_Int32 value);
    void (*setNavBarWidthRange)(Ark_NativePointer node, const Type_NavigationAttribute_navBarWidthRange_Arg0* value);
    void (*setMinContentWidth)(Ark_NativePointer node, const Ark_Length* value);
    void (*setMode)(Ark_NativePointer node, Ark_Int32 value);
    void (*setBackButtonIcon)(Ark_NativePointer node, const Type_NavigationAttribute_backButtonIcon_Arg0* value);
    void (*setHideNavBar)(Ark_NativePointer node, Ark_Boolean value);
    void (*setTitle)(Ark_NativePointer node, const Type_NavigationAttribute_title_Arg0* value, const Opt_NavigationTitleOptions* options);
    void (*setSubTitle)(Ark_NativePointer node, const Ark_String* value);
    void (*setHideTitleBar)(Ark_NativePointer node, Ark_Boolean value);
    void (*setHideBackButton)(Ark_NativePointer node, Ark_Boolean value);
    void (*setTitleMode)(Ark_NativePointer node, Ark_Int32 value);
    void (*setMenus)(Ark_NativePointer node, const Type_NavigationAttribute_menus_Arg0* value);
    void (*setToolBar)(Ark_NativePointer node, const Type_NavigationAttribute_toolBar_Arg0* value);
    void (*setToolbarConfiguration)(Ark_NativePointer node, const Type_NavigationAttribute_toolbarConfiguration_Arg0* value, const Opt_NavigationToolbarOptions* options);
    void (*setHideToolBar)(Ark_NativePointer node, Ark_Boolean value);
    void (*setOnTitleModeChange)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnNavBarStateChange)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnNavigationModeChange)(Ark_NativePointer node, Ark_Function callback);
    void (*setNavDestination)(Ark_NativePointer node, Ark_Function builder);
    void (*setCustomNavContentTransition)(Ark_NativePointer node, Ark_Function delegate);
    void (*setIgnoreLayoutSafeArea)(Ark_NativePointer node, const Opt_Array_Ark_LayoutSafeAreaType* types, const Opt_Array_Ark_LayoutSafeAreaEdge* edges);
    void (*setSystemBarStyle)(Ark_NativePointer node, const Opt_Ark_CustomObject* style);
} GENERATED_ArkUINavigationModifier;

typedef struct GENERATED_ArkUINavigatorModifier {
    void (*_setNavigatorOptions_targetstringtypeNavigationType)(Ark_NativePointer node, const Opt_Type_NavigatorInterface__setNavigatorOptions_Arg0* value);
    void (*_setNavigatorOptions_)(Ark_NativePointer node);
    void (*setActive)(Ark_NativePointer node, Ark_Boolean value);
    void (*setType)(Ark_NativePointer node, Ark_Int32 value);
    void (*setTarget)(Ark_NativePointer node, const Ark_String* value);
    void (*setParams)(Ark_NativePointer node, const Ark_CustomObject* value);
} GENERATED_ArkUINavigatorModifier;

typedef struct GENERATED_ArkUINodeContainerModifier {
    void (*_setNodeContainerOptions)(Ark_NativePointer node, const Ark_CustomObject* controller);
} GENERATED_ArkUINodeContainerModifier;

typedef struct GENERATED_ArkUIPanelModifier {
    void (*_setPanelOptions)(Ark_NativePointer node, Ark_Boolean show);
    void (*setMode)(Ark_NativePointer node, Ark_Int32 value);
    void (*setType)(Ark_NativePointer node, Ark_Int32 value);
    void (*setDragBar)(Ark_NativePointer node, Ark_Boolean value);
    void (*setCustomHeight)(Ark_NativePointer node, const Type_PanelAttribute_customHeight_Arg0* value);
    void (*setFullHeight)(Ark_NativePointer node, const Type_PanelAttribute_fullHeight_Arg0* value);
    void (*setHalfHeight)(Ark_NativePointer node, const Type_PanelAttribute_halfHeight_Arg0* value);
    void (*setMiniHeight)(Ark_NativePointer node, const Type_PanelAttribute_miniHeight_Arg0* value);
    void (*setShow)(Ark_NativePointer node, Ark_Boolean value);
    void (*setBackgroundMask)(Ark_NativePointer node, const ResourceColor* color);
    void (*setShowCloseIcon)(Ark_NativePointer node, Ark_Boolean value);
    void (*setOnChange)(Ark_NativePointer node, Ark_Function event);
    void (*setOnHeightChange)(Ark_NativePointer node, Ark_Function callback);
} GENERATED_ArkUIPanelModifier;

typedef struct GENERATED_ArkUIPasteButtonModifier {
    void (*_setPasteButtonOptions_)(Ark_NativePointer node);
    void (*_setPasteButtonOptions_PasteButtonOptions)(Ark_NativePointer node, const PasteButtonOptions* options);
    void (*setOnClick)(Ark_NativePointer node, Ark_Function event);
} GENERATED_ArkUIPasteButtonModifier;

typedef struct GENERATED_ArkUIPathModifier {
    void (*_setPathOptions)(Ark_NativePointer node, const Opt_Type_PathInterface__setPathOptions_Arg0* value);
    void (*setCommands)(Ark_NativePointer node, const Ark_String* value);
} GENERATED_ArkUIPathModifier;

typedef struct GENERATED_ArkUIPatternLockModifier {
    void (*_setPatternLockOptions)(Ark_NativePointer node, const Opt_PatternLockController* controller);
    void (*setSideLength)(Ark_NativePointer node, const Ark_Length* value);
    void (*setCircleRadius)(Ark_NativePointer node, const Ark_Length* value);
    void (*setBackgroundColor)(Ark_NativePointer node, const ResourceColor* value);
    void (*setRegularColor)(Ark_NativePointer node, const ResourceColor* value);
    void (*setSelectedColor)(Ark_NativePointer node, const ResourceColor* value);
    void (*setActiveColor)(Ark_NativePointer node, const ResourceColor* value);
    void (*setPathColor)(Ark_NativePointer node, const ResourceColor* value);
    void (*setPathStrokeWidth)(Ark_NativePointer node, const Type_PatternLockAttribute_pathStrokeWidth_Arg0* value);
    void (*setOnPatternComplete)(Ark_NativePointer node, Ark_Function callback);
    void (*setAutoReset)(Ark_NativePointer node, Ark_Boolean value);
    void (*setOnDotConnect)(Ark_NativePointer node, Ark_Function callback);
    void (*setActivateCircleStyle)(Ark_NativePointer node, const Opt_CircleStyleOptions* options);
} GENERATED_ArkUIPatternLockModifier;

typedef struct GENERATED_ArkUIPluginComponentModifier {
    void (*_setPluginComponentOptions)(Ark_NativePointer node, const Type_PluginComponentInterface__setPluginComponentOptions_Arg0* value);
    void (*setOnComplete)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnError)(Ark_NativePointer node, Ark_Function callback);
} GENERATED_ArkUIPluginComponentModifier;

typedef struct GENERATED_ArkUIPolygonModifier {
    void (*_setPolygonOptions)(Ark_NativePointer node, const Opt_Type_PolygonInterface__setPolygonOptions_Arg0* value);
    void (*setPoints)(Ark_NativePointer node, const Array_Ark_CustomObject* value);
} GENERATED_ArkUIPolygonModifier;

typedef struct GENERATED_ArkUIPolylineModifier {
    void (*_setPolylineOptions)(Ark_NativePointer node, const Opt_Type_PolylineInterface__setPolylineOptions_Arg0* value);
    void (*setPoints)(Ark_NativePointer node, const Array_Ark_CustomObject* value);
} GENERATED_ArkUIPolylineModifier;

typedef struct GENERATED_ArkUIQRCodeModifier {
    void (*_setQRCodeOptions)(Ark_NativePointer node, const Ark_String* value);
    void (*setColor)(Ark_NativePointer node, const ResourceColor* value);
    void (*setBackgroundColor)(Ark_NativePointer node, const ResourceColor* value);
    void (*setContentOpacity)(Ark_NativePointer node, const Type_QRCodeAttribute_contentOpacity_Arg0* value);
} GENERATED_ArkUIQRCodeModifier;

typedef struct GENERATED_ArkUIRadioModifier {
    void (*_setRadioOptions)(Ark_NativePointer node, const RadioOptions* options);
    void (*setChecked)(Ark_NativePointer node, Ark_Boolean value);
    void (*setOnChange)(Ark_NativePointer node, Ark_Function callback);
    void (*setRadioStyle)(Ark_NativePointer node, const Opt_RadioStyle* value);
    void (*setContentModifier)(Ark_NativePointer node, const Ark_CustomObject* modifier);
} GENERATED_ArkUIRadioModifier;

typedef struct GENERATED_ArkUIRatingModifier {
    void (*_setRatingOptions)(Ark_NativePointer node, const Opt_Type_RatingInterface__setRatingOptions_Arg0* options);
    void (*setStars)(Ark_NativePointer node, const Ark_Number* value);
    void (*setStepSize)(Ark_NativePointer node, const Ark_Number* value);
    void (*setStarStyle)(Ark_NativePointer node, const Type_RatingAttribute_starStyle_Arg0* value);
    void (*setOnChange)(Ark_NativePointer node, Ark_Function callback);
    void (*setContentModifier)(Ark_NativePointer node, const Ark_CustomObject* modifier);
} GENERATED_ArkUIRatingModifier;

typedef struct GENERATED_ArkUIRectModifier {
    void (*_setRectOptions)(Ark_NativePointer node, const Opt_Type_RectInterface__setRectOptions_Arg0* value);
    void (*setRadiusWidth)(Ark_NativePointer node, const Type_RectAttribute_radiusWidth_Arg0* value);
    void (*setRadiusHeight)(Ark_NativePointer node, const Type_RectAttribute_radiusHeight_Arg0* value);
    void (*setRadius)(Ark_NativePointer node, const Type_RectAttribute_radius_Arg0* value);
} GENERATED_ArkUIRectModifier;

typedef struct GENERATED_ArkUIRefreshModifier {
    void (*_setRefreshOptions)(Ark_NativePointer node, const RefreshOptions* value);
    void (*setOnStateChange)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnRefreshing)(Ark_NativePointer node, Ark_Function callback);
    void (*setRefreshOffset)(Ark_NativePointer node, const Ark_Number* value);
    void (*setPullToRefresh)(Ark_NativePointer node, Ark_Boolean value);
    void (*setOnOffsetChange)(Ark_NativePointer node, Ark_Function callback);
    void (*setPullDownRatio)(Ark_NativePointer node, const Opt_Ark_Number* ratio);
} GENERATED_ArkUIRefreshModifier;

typedef struct GENERATED_ArkUIRelativeContainerModifier {
    void (*_setRelativeContainerOptions)(Ark_NativePointer node);
    void (*setGuideLine)(Ark_NativePointer node, const Array_GuideLineStyle* value);
    void (*setBarrier_ArrayBarrierStyle)(Ark_NativePointer node, const Array_BarrierStyle* value);
    void (*setBarrier_ArrayLocalizedBarrierStyle)(Ark_NativePointer node, const Array_LocalizedBarrierStyle* barrierStyle);
} GENERATED_ArkUIRelativeContainerModifier;

typedef struct GENERATED_ArkUIRichEditorModifier {
    void (*_setRichEditorOptions_RichEditorOptions)(Ark_NativePointer node, const RichEditorOptions* value);
    void (*_setRichEditorOptions_RichEditorStyledStringOptions)(Ark_NativePointer node, const RichEditorStyledStringOptions* options);
    void (*setOnReady)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnSelect)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnSelectionChange)(Ark_NativePointer node, Ark_Function callback);
    void (*setAboutToIMEInput)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnIMEInputComplete)(Ark_NativePointer node, Ark_Function callback);
    void (*setAboutToDelete)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnDeleteComplete)(Ark_NativePointer node, Ark_Function callback);
    void (*setCopyOptions)(Ark_NativePointer node, Ark_Int32 value);
    void (*setBindSelectionMenu)(Ark_NativePointer node, Ark_Int32 spanType, const CustomBuilder* content, const Type_RichEditorAttribute_bindSelectionMenu_Arg2* responseType, const Opt_SelectionMenuOptions* options);
    void (*setCustomKeyboard)(Ark_NativePointer node, const CustomBuilder* value, const Opt_KeyboardOptions* options);
    void (*setOnPaste)(Ark_NativePointer node, Ark_Function callback);
    void (*setEnableDataDetector)(Ark_NativePointer node, Ark_Boolean enable);
    void (*setEnablePreviewText)(Ark_NativePointer node, Ark_Boolean enable);
    void (*setDataDetectorConfig)(Ark_NativePointer node, const TextDataDetectorConfig* config);
    void (*setPlaceholder)(Ark_NativePointer node, const ResourceStr* value, const Opt_PlaceholderStyle* style);
    void (*setCaretColor)(Ark_NativePointer node, const ResourceColor* value);
    void (*setSelectedBackgroundColor)(Ark_NativePointer node, const ResourceColor* value);
    void (*setOnEditingChange)(Ark_NativePointer node, Ark_Function callback);
    void (*setEnterKeyType)(Ark_NativePointer node, Ark_Int32 value);
    void (*setOnSubmit)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnWillChange)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnDidChange)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnCut)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnCopy)(Ark_NativePointer node, Ark_Function callback);
    void (*setEditMenuOptions)(Ark_NativePointer node, const Ark_Materialized* editMenu);
} GENERATED_ArkUIRichEditorModifier;

typedef struct GENERATED_ArkUIRichTextModifier {
    void (*_setRichTextOptions)(Ark_NativePointer node, const Ark_String* content);
    void (*setOnStart)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnComplete)(Ark_NativePointer node, Ark_Function callback);
} GENERATED_ArkUIRichTextModifier;

typedef struct GENERATED_ArkUIRootSceneModifier {
    void (*_setRootSceneOptions)(Ark_NativePointer node, const RootSceneSession* session);
} GENERATED_ArkUIRootSceneModifier;

typedef struct GENERATED_ArkUIRowModifier {
    void (*_setRowOptions)(Ark_NativePointer node, const Opt_Type_RowInterface__setRowOptions_Arg0* value);
    void (*setAlignItems)(Ark_NativePointer node, Ark_Int32 value);
    void (*setJustifyContent)(Ark_NativePointer node, Ark_Int32 value);
    void (*setPointLight)(Ark_NativePointer node, const PointLightStyle* value);
} GENERATED_ArkUIRowModifier;

typedef struct GENERATED_ArkUIRowSplitModifier {
    void (*_setRowSplitOptions)(Ark_NativePointer node);
    void (*setResizeable)(Ark_NativePointer node, Ark_Boolean value);
} GENERATED_ArkUIRowSplitModifier;

typedef struct GENERATED_ArkUISaveButtonModifier {
    void (*_setSaveButtonOptions_)(Ark_NativePointer node);
    void (*_setSaveButtonOptions_SaveButtonOptions)(Ark_NativePointer node, const SaveButtonOptions* options);
    void (*setOnClick)(Ark_NativePointer node, Ark_Function event);
} GENERATED_ArkUISaveButtonModifier;

typedef struct GENERATED_ArkUIScreenModifier {
    void (*_setScreenOptions)(Ark_NativePointer node, const Ark_Number* screenId);
} GENERATED_ArkUIScreenModifier;

typedef struct GENERATED_ArkUIScrollModifier {
    void (*_setScrollOptions)(Ark_NativePointer node, const Opt_Scroller* scroller);
    void (*setScrollable)(Ark_NativePointer node, Ark_Int32 value);
    void (*setOnScroll)(Ark_NativePointer node, Ark_Function event);
    void (*setOnWillScroll)(Ark_NativePointer node, const Ark_CustomObject* stub_for_onWillScroll);
    void (*setOnDidScroll)(Ark_NativePointer node, Ark_Function handler);
    void (*setOnScrollEdge)(Ark_NativePointer node, Ark_Function event);
    void (*setOnScrollStart)(Ark_NativePointer node, Ark_Function event);
    void (*setOnScrollEnd)(Ark_NativePointer node, Ark_Function event);
    void (*setOnScrollStop)(Ark_NativePointer node, Ark_Function event);
    void (*setScrollBar)(Ark_NativePointer node, Ark_Int32 barState);
    void (*setScrollBarColor)(Ark_NativePointer node, const Type_ScrollAttribute_scrollBarColor_Arg0* color);
    void (*setScrollBarWidth)(Ark_NativePointer node, const Type_ScrollAttribute_scrollBarWidth_Arg0* value);
    void (*setEdgeEffect)(Ark_NativePointer node, Ark_Int32 edgeEffect, const Opt_EdgeEffectOptions* options);
    void (*setOnScrollFrameBegin)(Ark_NativePointer node, Ark_Function event);
    void (*setNestedScroll)(Ark_NativePointer node, const NestedScrollOptions* value);
    void (*setEnableScrollInteraction)(Ark_NativePointer node, Ark_Boolean value);
    void (*setFriction)(Ark_NativePointer node, const Type_ScrollAttribute_friction_Arg0* value);
    void (*setScrollSnap)(Ark_NativePointer node, const ScrollSnapOptions* value);
    void (*setEnablePaging)(Ark_NativePointer node, Ark_Boolean value);
    void (*setInitialOffset)(Ark_NativePointer node, const OffsetOptions* value);
} GENERATED_ArkUIScrollModifier;

typedef struct GENERATED_ArkUIScrollBarModifier {
    void (*_setScrollBarOptions)(Ark_NativePointer node, const ScrollBarOptions* value);
} GENERATED_ArkUIScrollBarModifier;

typedef struct GENERATED_ArkUISearchModifier {
    void (*_setSearchOptions)(Ark_NativePointer node, const Opt_Type_SearchInterface__setSearchOptions_Arg0* options);
    void (*setSearchButton)(Ark_NativePointer node, const Ark_String* value, const Opt_SearchButtonOptions* option);
    void (*setFontColor)(Ark_NativePointer node, const ResourceColor* value);
    void (*setSearchIcon)(Ark_NativePointer node, const IconOptions* value);
    void (*setCancelButton)(Ark_NativePointer node, const Type_SearchAttribute_cancelButton_Arg0* value);
    void (*setTextIndent)(Ark_NativePointer node, const Ark_Length* value);
    void (*setInputFilter)(Ark_NativePointer node, const ResourceStr* value, const Opt_Callback* error);
    void (*setOnEditChange)(Ark_NativePointer node, Ark_Function callback);
    void (*setSelectedBackgroundColor)(Ark_NativePointer node, const ResourceColor* value);
    void (*setCaretStyle)(Ark_NativePointer node, const CaretStyle* value);
    void (*setPlaceholderColor)(Ark_NativePointer node, const ResourceColor* value);
    void (*setPlaceholderFont)(Ark_NativePointer node, const Opt_Font* value);
    void (*setTextFont)(Ark_NativePointer node, const Opt_Font* value);
    void (*setEnterKeyType)(Ark_NativePointer node, Ark_Int32 value);
    void (*setOnSubmit)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnChange)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnTextSelectionChange)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnContentScroll)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnCopy)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnCut)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnPaste)(Ark_NativePointer node, Ark_Function callback);
    void (*setCopyOption)(Ark_NativePointer node, Ark_Int32 value);
    void (*setMaxLength)(Ark_NativePointer node, const Ark_Number* value);
    void (*setTextAlign)(Ark_NativePointer node, Ark_Int32 value);
    void (*setEnableKeyboardOnFocus)(Ark_NativePointer node, Ark_Boolean value);
    void (*setSelectionMenuHidden)(Ark_NativePointer node, Ark_Boolean value);
    void (*setMinFontSize)(Ark_NativePointer node, const Type_SearchAttribute_minFontSize_Arg0* value);
    void (*setMaxFontSize)(Ark_NativePointer node, const Type_SearchAttribute_maxFontSize_Arg0* value);
    void (*setCustomKeyboard)(Ark_NativePointer node, const CustomBuilder* value, const Opt_KeyboardOptions* options);
    void (*setDecoration)(Ark_NativePointer node, const TextDecorationOptions* value);
    void (*setLetterSpacing)(Ark_NativePointer node, const Type_SearchAttribute_letterSpacing_Arg0* value);
    void (*setLineHeight)(Ark_NativePointer node, const Type_SearchAttribute_lineHeight_Arg0* value);
    void (*setType)(Ark_NativePointer node, Ark_Int32 value);
    void (*setFontFeature)(Ark_NativePointer node, const Ark_String* value);
    void (*setOnWillInsert)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnDidInsert)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnWillDelete)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnDidDelete)(Ark_NativePointer node, Ark_Function callback);
    void (*setEditMenuOptions)(Ark_NativePointer node, const Ark_Materialized* editMenu);
    void (*setEnablePreviewText)(Ark_NativePointer node, Ark_Boolean enable);
} GENERATED_ArkUISearchModifier;

typedef struct GENERATED_ArkUISecurityComponentMethodModifier {
    void (*setIconSize)(Ark_NativePointer node, const Ark_Length* value);
    void (*setLayoutDirection)(Ark_NativePointer node, Ark_Int32 value);
    void (*setPosition)(Ark_NativePointer node, const Position* value);
    void (*setMarkAnchor)(Ark_NativePointer node, const Position* value);
    void (*setOffset)(Ark_NativePointer node, const Type_SecurityComponentMethod_offset_Arg0* value);
    void (*setFontSize)(Ark_NativePointer node, const Ark_Length* value);
    void (*setFontStyle)(Ark_NativePointer node, Ark_Int32 value);
    void (*setFontWeight)(Ark_NativePointer node, const Type_SecurityComponentMethod_fontWeight_Arg0* value);
    void (*setFontFamily)(Ark_NativePointer node, const Type_SecurityComponentMethod_fontFamily_Arg0* value);
    void (*setFontColor)(Ark_NativePointer node, const ResourceColor* value);
    void (*setIconColor)(Ark_NativePointer node, const ResourceColor* value);
    void (*setBackgroundColor)(Ark_NativePointer node, const ResourceColor* value);
    void (*setBorderStyle)(Ark_NativePointer node, Ark_Int32 value);
    void (*setBorderWidth)(Ark_NativePointer node, const Ark_Length* value);
    void (*setBorderColor)(Ark_NativePointer node, const ResourceColor* value);
    void (*setBorderRadius)(Ark_NativePointer node, const Ark_Length* value);
    void (*setPadding)(Ark_NativePointer node, const Type_SecurityComponentMethod_padding_Arg0* value);
    void (*setTextIconSpace)(Ark_NativePointer node, const Ark_Length* value);
    void (*setKey)(Ark_NativePointer node, const Ark_String* value);
    void (*setWidth)(Ark_NativePointer node, const Ark_Length* value);
    void (*setHeight)(Ark_NativePointer node, const Ark_Length* value);
    void (*setSize)(Ark_NativePointer node, const SizeOptions* value);
    void (*setConstraintSize)(Ark_NativePointer node, const ConstraintSizeOptions* value);
} GENERATED_ArkUISecurityComponentMethodModifier;

typedef struct GENERATED_ArkUISelectModifier {
    void (*_setSelectOptions)(Ark_NativePointer node, const Array_SelectOption* options);
    void (*setSelected)(Ark_NativePointer node, const Type_SelectAttribute_selected_Arg0* value);
    void (*setValue)(Ark_NativePointer node, const ResourceStr* value);
    void (*setFont)(Ark_NativePointer node, const Font* value);
    void (*setFontColor)(Ark_NativePointer node, const ResourceColor* value);
    void (*setSelectedOptionBgColor)(Ark_NativePointer node, const ResourceColor* value);
    void (*setSelectedOptionFont)(Ark_NativePointer node, const Font* value);
    void (*setSelectedOptionFontColor)(Ark_NativePointer node, const ResourceColor* value);
    void (*setOptionBgColor)(Ark_NativePointer node, const ResourceColor* value);
    void (*setOptionFont)(Ark_NativePointer node, const Font* value);
    void (*setOptionFontColor)(Ark_NativePointer node, const ResourceColor* value);
    void (*setOnSelect)(Ark_NativePointer node, Ark_Function callback);
    void (*setSpace)(Ark_NativePointer node, const Ark_Length* value);
    void (*setArrowPosition)(Ark_NativePointer node, Ark_Int32 value);
    void (*setMenuAlign)(Ark_NativePointer node, Ark_Int32 alignType, const Opt_Offset* offset);
    void (*setOptionWidth)(Ark_NativePointer node, const Type_SelectAttribute_optionWidth_Arg0* value);
    void (*setOptionHeight)(Ark_NativePointer node, const Ark_Length* value);
    void (*setMenuBackgroundColor)(Ark_NativePointer node, const ResourceColor* value);
    void (*setMenuBackgroundBlurStyle)(Ark_NativePointer node, Ark_Int32 value);
    void (*setControlSize)(Ark_NativePointer node, Ark_Int32 value);
    void (*setMenuItemContentModifier)(Ark_NativePointer node, const Ark_CustomObject* modifier);
    void (*setDivider)(Ark_NativePointer node, const Type_SelectAttribute_divider_Arg0* options);
} GENERATED_ArkUISelectModifier;

typedef struct GENERATED_ArkUIShapeModifier {
    void (*_setShapeOptions_PixelMap)(Ark_NativePointer node, const Ark_CustomObject* value);
    void (*_setShapeOptions_)(Ark_NativePointer node);
    void (*setViewPort)(Ark_NativePointer node, const Type_ShapeAttribute_viewPort_Arg0* value);
    void (*setStroke)(Ark_NativePointer node, const ResourceColor* value);
    void (*setFill)(Ark_NativePointer node, const ResourceColor* value);
    void (*setStrokeDashOffset)(Ark_NativePointer node, const Type_ShapeAttribute_strokeDashOffset_Arg0* value);
    void (*setStrokeDashArray)(Ark_NativePointer node, const Array_Ark_CustomObject* value);
    void (*setStrokeLineCap)(Ark_NativePointer node, Ark_Int32 value);
    void (*setStrokeLineJoin)(Ark_NativePointer node, Ark_Int32 value);
    void (*setStrokeMiterLimit)(Ark_NativePointer node, const Type_ShapeAttribute_strokeMiterLimit_Arg0* value);
    void (*setStrokeOpacity)(Ark_NativePointer node, const Type_ShapeAttribute_strokeOpacity_Arg0* value);
    void (*setFillOpacity)(Ark_NativePointer node, const Type_ShapeAttribute_fillOpacity_Arg0* value);
    void (*setStrokeWidth)(Ark_NativePointer node, const Type_ShapeAttribute_strokeWidth_Arg0* value);
    void (*setAntiAlias)(Ark_NativePointer node, Ark_Boolean value);
    void (*setMesh)(Ark_NativePointer node, const Array_Ark_CustomObject* value, const Ark_Number* column, const Ark_Number* row);
} GENERATED_ArkUIShapeModifier;

typedef struct GENERATED_ArkUISliderModifier {
    void (*_setSliderOptions)(Ark_NativePointer node, const Opt_SliderOptions* options);
    void (*setBlockColor)(Ark_NativePointer node, const ResourceColor* value);
    void (*setTrackColor)(Ark_NativePointer node, const Type_SliderAttribute_trackColor_Arg0* value);
    void (*setSelectedColor)(Ark_NativePointer node, const ResourceColor* value);
    void (*setMinLabel)(Ark_NativePointer node, const Ark_String* value);
    void (*setMaxLabel)(Ark_NativePointer node, const Ark_String* value);
    void (*setShowSteps)(Ark_NativePointer node, Ark_Boolean value);
    void (*setShowTips)(Ark_NativePointer node, Ark_Boolean value, const Opt_ResourceStr* content);
    void (*setTrackThickness)(Ark_NativePointer node, const Ark_Length* value);
    void (*setOnChange)(Ark_NativePointer node, Ark_Function callback);
    void (*setBlockBorderColor)(Ark_NativePointer node, const ResourceColor* value);
    void (*setBlockBorderWidth)(Ark_NativePointer node, const Ark_Length* value);
    void (*setStepColor)(Ark_NativePointer node, const ResourceColor* value);
    void (*setTrackBorderRadius)(Ark_NativePointer node, const Ark_Length* value);
    void (*setSelectedBorderRadius)(Ark_NativePointer node, const Ark_Length* value);
    void (*setBlockSize)(Ark_NativePointer node, const SizeOptions* value);
    void (*setBlockStyle)(Ark_NativePointer node, const SliderBlockStyle* value);
    void (*setStepSize)(Ark_NativePointer node, const Ark_Length* value);
    void (*setSliderInteractionMode)(Ark_NativePointer node, Ark_Int32 value);
    void (*setMinResponsiveDistance)(Ark_NativePointer node, const Ark_Number* value);
    void (*setContentModifier)(Ark_NativePointer node, const Ark_CustomObject* modifier);
    void (*setSlideRange)(Ark_NativePointer node, const SlideRange* value);
} GENERATED_ArkUISliderModifier;

typedef struct GENERATED_ArkUIBaseSpanModifier {
    void (*setTextBackgroundStyle)(Ark_NativePointer node, const TextBackgroundStyle* style);
    void (*setBaselineOffset)(Ark_NativePointer node, const Ark_CustomObject* value);
} GENERATED_ArkUIBaseSpanModifier;

typedef struct GENERATED_ArkUISpanModifier {
    void (*_setSpanOptions)(Ark_NativePointer node, const Type_SpanInterface__setSpanOptions_Arg0* value);
    void (*setFont)(Ark_NativePointer node, const Font* value);
    void (*setFontColor)(Ark_NativePointer node, const ResourceColor* value);
    void (*setFontSize)(Ark_NativePointer node, const Type_SpanAttribute_fontSize_Arg0* value);
    void (*setFontStyle)(Ark_NativePointer node, Ark_Int32 value);
    void (*setFontWeight)(Ark_NativePointer node, const Type_SpanAttribute_fontWeight_Arg0* value);
    void (*setFontFamily)(Ark_NativePointer node, const Type_SpanAttribute_fontFamily_Arg0* value);
    void (*setDecoration)(Ark_NativePointer node, const DecorationStyleInterface* value);
    void (*setLetterSpacing)(Ark_NativePointer node, const Type_SpanAttribute_letterSpacing_Arg0* value);
    void (*setTextCase)(Ark_NativePointer node, Ark_Int32 value);
    void (*setLineHeight)(Ark_NativePointer node, const Ark_Length* value);
    void (*setTextShadow)(Ark_NativePointer node, const Type_SpanAttribute_textShadow_Arg0* value);
} GENERATED_ArkUISpanModifier;

typedef struct GENERATED_ArkUIStackModifier {
    void (*_setStackOptions)(Ark_NativePointer node, const Opt_Type_StackInterface__setStackOptions_Arg0* value);
    void (*setAlignContent)(Ark_NativePointer node, Ark_Int32 value);
    void (*setPointLight)(Ark_NativePointer node, const PointLightStyle* value);
} GENERATED_ArkUIStackModifier;

typedef struct GENERATED_ArkUIStepperModifier {
    void (*_setStepperOptions)(Ark_NativePointer node, const Opt_Type_StepperInterface__setStepperOptions_Arg0* value);
    void (*setOnFinish)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnSkip)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnChange)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnNext)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnPrevious)(Ark_NativePointer node, Ark_Function callback);
} GENERATED_ArkUIStepperModifier;

typedef struct GENERATED_ArkUIStepperItemModifier {
    void (*_setStepperItemOptions)(Ark_NativePointer node);
    void (*setPrevLabel)(Ark_NativePointer node, const Ark_String* value);
    void (*setNextLabel)(Ark_NativePointer node, const Ark_String* value);
    void (*setStatus)(Ark_NativePointer node, const Opt_Ark_ItemState* value);
} GENERATED_ArkUIStepperItemModifier;

typedef struct GENERATED_ArkUISwiperModifier {
    void (*_setSwiperOptions)(Ark_NativePointer node, const Opt_SwiperController* controller);
    void (*setIndex)(Ark_NativePointer node, const Ark_Number* value);
    void (*setAutoPlay)(Ark_NativePointer node, Ark_Boolean value);
    void (*setInterval)(Ark_NativePointer node, const Ark_Number* value);
    void (*setIndicator)(Ark_NativePointer node, const Type_SwiperAttribute_indicator_Arg0* value);
    void (*setDisplayArrow)(Ark_NativePointer node, const Type_SwiperAttribute_displayArrow_Arg0* value, const Opt_Ark_Boolean* isHoverShow);
    void (*setLoop)(Ark_NativePointer node, Ark_Boolean value);
    void (*setDuration)(Ark_NativePointer node, const Ark_Number* value);
    void (*setVertical)(Ark_NativePointer node, Ark_Boolean value);
    void (*setItemSpace)(Ark_NativePointer node, const Type_SwiperAttribute_itemSpace_Arg0* value);
    void (*setDisplayMode)(Ark_NativePointer node, Ark_Int32 value);
    void (*setCachedCount)(Ark_NativePointer node, const Ark_Number* value);
    void (*setDisplayCount)(Ark_NativePointer node, const Type_SwiperAttribute_displayCount_Arg0* value, const Opt_Ark_Boolean* swipeByGroup);
    void (*setEffectMode)(Ark_NativePointer node, Ark_Int32 value);
    void (*setDisableSwipe)(Ark_NativePointer node, Ark_Boolean value);
    void (*setCurve)(Ark_NativePointer node, const Type_SwiperAttribute_curve_Arg0* value);
    void (*setOnChange)(Ark_NativePointer node, Ark_Function event);
    void (*setIndicatorStyle)(Ark_NativePointer node, const Opt_IndicatorStyle* value);
    void (*setPrevMargin)(Ark_NativePointer node, const Ark_Length* value, const Opt_Ark_Boolean* ignoreBlank);
    void (*setNextMargin)(Ark_NativePointer node, const Ark_Length* value, const Opt_Ark_Boolean* ignoreBlank);
    void (*setOnAnimationStart)(Ark_NativePointer node, Ark_Function event);
    void (*setOnAnimationEnd)(Ark_NativePointer node, Ark_Function event);
    void (*setOnGestureSwipe)(Ark_NativePointer node, Ark_Function event);
    void (*setNestedScroll)(Ark_NativePointer node, Ark_Int32 value);
    void (*setCustomContentTransition)(Ark_NativePointer node, const SwiperContentAnimatedTransition* transition);
    void (*setOnContentDidScroll)(Ark_NativePointer node, Ark_Function handler);
    void (*setIndicatorInteractive)(Ark_NativePointer node, Ark_Boolean value);
} GENERATED_ArkUISwiperModifier;

typedef struct GENERATED_ArkUISymbolGlyphModifier {
    void (*_setSymbolGlyphOptions)(Ark_NativePointer node, const Opt_Ark_Resource* value);
    void (*setFontSize)(Ark_NativePointer node, const Type_SymbolGlyphAttribute_fontSize_Arg0* value);
    void (*setFontColor)(Ark_NativePointer node, const Array_ResourceColor* value);
    void (*setFontWeight)(Ark_NativePointer node, const Type_SymbolGlyphAttribute_fontWeight_Arg0* value);
    void (*setEffectStrategy)(Ark_NativePointer node, Ark_Int32 value);
    void (*setRenderingStrategy)(Ark_NativePointer node, Ark_Int32 value);
    void (*setSymbolEffect_SymbolEffect_boolean)(Ark_NativePointer node, const SymbolEffect* symbolEffect, const Opt_Ark_Boolean* isActive);
    void (*setSymbolEffect_SymbolEffect_number)(Ark_NativePointer node, const SymbolEffect* symbolEffect, const Opt_Ark_Number* triggerValue);
} GENERATED_ArkUISymbolGlyphModifier;

typedef struct GENERATED_ArkUISymbolSpanModifier {
    void (*_setSymbolSpanOptions)(Ark_NativePointer node, const Ark_CustomObject* value);
    void (*setFontSize)(Ark_NativePointer node, const Type_SymbolSpanAttribute_fontSize_Arg0* value);
    void (*setFontColor)(Ark_NativePointer node, const Array_ResourceColor* value);
    void (*setFontWeight)(Ark_NativePointer node, const Type_SymbolSpanAttribute_fontWeight_Arg0* value);
    void (*setEffectStrategy)(Ark_NativePointer node, Ark_Int32 value);
    void (*setRenderingStrategy)(Ark_NativePointer node, Ark_Int32 value);
} GENERATED_ArkUISymbolSpanModifier;

typedef struct GENERATED_ArkUITabsModifier {
    void (*_setTabsOptions)(Ark_NativePointer node, const Opt_Type_TabsInterface__setTabsOptions_Arg0* value);
    void (*setVertical)(Ark_NativePointer node, Ark_Boolean value);
    void (*setBarPosition)(Ark_NativePointer node, Ark_Int32 value);
    void (*setScrollable)(Ark_NativePointer node, Ark_Boolean value);
    void (*setBarMode_BarModeFixed)(Ark_NativePointer node, Ark_Int32 value);
    void (*setBarMode_BarModeScrollable_ScrollableBarModeOptions)(Ark_NativePointer node, Ark_Int32 value, const ScrollableBarModeOptions* options);
    void (*setBarMode_BarMode_ScrollableBarModeOptions)(Ark_NativePointer node, Ark_Int32 value, const Opt_ScrollableBarModeOptions* options);
    void (*setBarWidth)(Ark_NativePointer node, const Ark_Length* value);
    void (*setBarHeight)(Ark_NativePointer node, const Ark_Length* value);
    void (*setAnimationDuration)(Ark_NativePointer node, const Ark_Number* value);
    void (*setAnimationMode)(Ark_NativePointer node, const Opt_Ark_AnimationMode* mode);
    void (*setEdgeEffect)(Ark_NativePointer node, const Opt_Ark_EdgeEffect* edgeEffect);
    void (*setOnChange)(Ark_NativePointer node, Ark_Function event);
    void (*setOnTabBarClick)(Ark_NativePointer node, Ark_Function event);
    void (*setOnAnimationStart)(Ark_NativePointer node, Ark_Function handler);
    void (*setOnAnimationEnd)(Ark_NativePointer node, Ark_Function handler);
    void (*setOnGestureSwipe)(Ark_NativePointer node, Ark_Function handler);
    void (*setFadingEdge)(Ark_NativePointer node, Ark_Boolean value);
    void (*setDivider)(Ark_NativePointer node, const Type_TabsAttribute_divider_Arg0* value);
    void (*setBarOverlap)(Ark_NativePointer node, Ark_Boolean value);
    void (*setBarBackgroundColor)(Ark_NativePointer node, const ResourceColor* value);
    void (*setBarGridAlign)(Ark_NativePointer node, const BarGridColumnOptions* value);
    void (*setCustomContentTransition)(Ark_NativePointer node, Ark_Function delegate);
    void (*setBarBackgroundBlurStyle)(Ark_NativePointer node, Ark_Int32 value);
    void (*setOnContentWillChange)(Ark_NativePointer node, Ark_Function handler);
} GENERATED_ArkUITabsModifier;

typedef struct GENERATED_ArkUITabContentModifier {
    void (*_setTabContentOptions)(Ark_NativePointer node);
    void (*setTabBar_stringResourceCustomBuildericonstringResourcetextstringResource)(Ark_NativePointer node, const Type_TabContentAttribute_tabBar_Arg0* value);
    void (*setTabBar_SubTabBarStyleBottomTabBarStyle)(Ark_NativePointer node, const Type_TabContentAttribute_tabBar1_Arg0* value);
    void (*setOnWillShow)(Ark_NativePointer node, Ark_Function event);
    void (*setOnWillHide)(Ark_NativePointer node, Ark_Function event);
} GENERATED_ArkUITabContentModifier;

typedef struct GENERATED_ArkUITextModifier {
    void (*_setTextOptions)(Ark_NativePointer node, const Opt_Type_TextInterface__setTextOptions_Arg0* content, const Opt_TextOptions* value);
    void (*setFont)(Ark_NativePointer node, const Font* value);
    void (*setFontColor)(Ark_NativePointer node, const ResourceColor* value);
    void (*setFontSize)(Ark_NativePointer node, const Type_TextAttribute_fontSize_Arg0* value);
    void (*setMinFontSize)(Ark_NativePointer node, const Type_TextAttribute_minFontSize_Arg0* value);
    void (*setMaxFontSize)(Ark_NativePointer node, const Type_TextAttribute_maxFontSize_Arg0* value);
    void (*setFontStyle)(Ark_NativePointer node, Ark_Int32 value);
    void (*setFontWeight)(Ark_NativePointer node, const Type_TextAttribute_fontWeight_Arg0* value);
    void (*setLineSpacing)(Ark_NativePointer node, const Ark_CustomObject* value);
    void (*setTextAlign)(Ark_NativePointer node, Ark_Int32 value);
    void (*setLineHeight)(Ark_NativePointer node, const Type_TextAttribute_lineHeight_Arg0* value);
    void (*setTextOverflow)(Ark_NativePointer node, const Type_TextAttribute_textOverflow_Arg0* value);
    void (*setFontFamily)(Ark_NativePointer node, const Type_TextAttribute_fontFamily_Arg0* value);
    void (*setMaxLines)(Ark_NativePointer node, const Ark_Number* value);
    void (*setDecoration)(Ark_NativePointer node, const DecorationStyleInterface* value);
    void (*setLetterSpacing)(Ark_NativePointer node, const Type_TextAttribute_letterSpacing_Arg0* value);
    void (*setTextCase)(Ark_NativePointer node, Ark_Int32 value);
    void (*setBaselineOffset)(Ark_NativePointer node, const Type_TextAttribute_baselineOffset_Arg0* value);
    void (*setCopyOption)(Ark_NativePointer node, Ark_Int32 value);
    void (*setDraggable)(Ark_NativePointer node, Ark_Boolean value);
    void (*setTextShadow)(Ark_NativePointer node, const Type_TextAttribute_textShadow_Arg0* value);
    void (*setHeightAdaptivePolicy)(Ark_NativePointer node, Ark_Int32 value);
    void (*setTextIndent)(Ark_NativePointer node, const Ark_Length* value);
    void (*setWordBreak)(Ark_NativePointer node, Ark_Int32 value);
    void (*setLineBreakStrategy)(Ark_NativePointer node, Ark_Int32 strategy);
    void (*setOnCopy)(Ark_NativePointer node, Ark_Function callback);
    void (*setSelection)(Ark_NativePointer node, const Ark_Number* selectionStart, const Ark_Number* selectionEnd);
    void (*setEllipsisMode)(Ark_NativePointer node, Ark_Int32 value);
    void (*setEnableDataDetector)(Ark_NativePointer node, Ark_Boolean enable);
    void (*setDataDetectorConfig)(Ark_NativePointer node, const TextDataDetectorConfig* config);
    void (*setBindSelectionMenu)(Ark_NativePointer node, Ark_Int32 spanType, const CustomBuilder* content, Ark_Int32 responseType, const Opt_SelectionMenuOptions* options);
    void (*setOnTextSelectionChange)(Ark_NativePointer node, Ark_Function callback);
    void (*setFontFeature)(Ark_NativePointer node, const Ark_String* value);
    void (*setMarqueeOptions)(Ark_NativePointer node, const Opt_MarqueeOptions* value);
    void (*setOnMarqueeStateChange)(Ark_NativePointer node, Ark_Function callback);
    void (*setPrivacySensitive)(Ark_NativePointer node, Ark_Boolean supported);
    void (*setTextSelectable)(Ark_NativePointer node, Ark_Int32 mode);
    void (*setEditMenuOptions)(Ark_NativePointer node, const Ark_Materialized* editMenu);
} GENERATED_ArkUITextModifier;

typedef struct GENERATED_ArkUITextAreaModifier {
    void (*_setTextAreaOptions)(Ark_NativePointer node, const Opt_TextAreaOptions* value);
    void (*setPlaceholderColor)(Ark_NativePointer node, const ResourceColor* value);
    void (*setPlaceholderFont)(Ark_NativePointer node, const Font* value);
    void (*setEnterKeyType)(Ark_NativePointer node, Ark_Int32 value);
    void (*setTextAlign)(Ark_NativePointer node, Ark_Int32 value);
    void (*setCaretColor)(Ark_NativePointer node, const ResourceColor* value);
    void (*setFontColor)(Ark_NativePointer node, const ResourceColor* value);
    void (*setFontSize)(Ark_NativePointer node, const Ark_Length* value);
    void (*setFontStyle)(Ark_NativePointer node, Ark_Int32 value);
    void (*setFontWeight)(Ark_NativePointer node, const Type_TextAreaAttribute_fontWeight_Arg0* value);
    void (*setFontFamily)(Ark_NativePointer node, const ResourceStr* value);
    void (*setTextOverflow)(Ark_NativePointer node, Ark_Int32 value);
    void (*setTextIndent)(Ark_NativePointer node, const Ark_Length* value);
    void (*setInputFilter)(Ark_NativePointer node, const ResourceStr* value, const Opt_Ark_Function* error);
    void (*setCaretStyle)(Ark_NativePointer node, const CaretStyle* value);
    void (*setSelectedBackgroundColor)(Ark_NativePointer node, const ResourceColor* value);
    void (*setOnSubmit)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnChange)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnTextSelectionChange)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnContentScroll)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnEditChange)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnCopy)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnCut)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnPaste)(Ark_NativePointer node, Ark_Function callback);
    void (*setCopyOption)(Ark_NativePointer node, Ark_Int32 value);
    void (*setEnableKeyboardOnFocus)(Ark_NativePointer node, Ark_Boolean value);
    void (*setMaxLength)(Ark_NativePointer node, const Ark_Number* value);
    void (*setShowCounter)(Ark_NativePointer node, Ark_Boolean value, const Opt_InputCounterOptions* options);
    void (*setStyle)(Ark_NativePointer node, Ark_Int32 value);
    void (*setBarState)(Ark_NativePointer node, Ark_Int32 value);
    void (*setSelectionMenuHidden)(Ark_NativePointer node, Ark_Boolean value);
    void (*setMinFontSize)(Ark_NativePointer node, const Type_TextAreaAttribute_minFontSize_Arg0* value);
    void (*setMaxFontSize)(Ark_NativePointer node, const Type_TextAreaAttribute_maxFontSize_Arg0* value);
    void (*setHeightAdaptivePolicy)(Ark_NativePointer node, Ark_Int32 value);
    void (*setMaxLines)(Ark_NativePointer node, const Ark_Number* value);
    void (*setWordBreak)(Ark_NativePointer node, Ark_Int32 value);
    void (*setLineBreakStrategy)(Ark_NativePointer node, Ark_Int32 strategy);
    void (*setCustomKeyboard)(Ark_NativePointer node, const CustomBuilder* value, const Opt_KeyboardOptions* options);
    void (*setDecoration)(Ark_NativePointer node, const TextDecorationOptions* value);
    void (*setLetterSpacing)(Ark_NativePointer node, const Type_TextAreaAttribute_letterSpacing_Arg0* value);
    void (*setLineSpacing)(Ark_NativePointer node, const Ark_CustomObject* value);
    void (*setLineHeight)(Ark_NativePointer node, const Type_TextAreaAttribute_lineHeight_Arg0* value);
    void (*setType)(Ark_NativePointer node, Ark_Int32 value);
    void (*setEnableAutoFill)(Ark_NativePointer node, Ark_Boolean value);
    void (*setContentType)(Ark_NativePointer node, Ark_Int32 contentType);
    void (*setFontFeature)(Ark_NativePointer node, const Ark_String* value);
    void (*setOnWillInsert)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnDidInsert)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnWillDelete)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnDidDelete)(Ark_NativePointer node, Ark_Function callback);
    void (*setEditMenuOptions)(Ark_NativePointer node, const Ark_Materialized* editMenu);
    void (*setEnablePreviewText)(Ark_NativePointer node, Ark_Boolean enable);
} GENERATED_ArkUITextAreaModifier;

typedef struct GENERATED_ArkUITextClockModifier {
    void (*_setTextClockOptions)(Ark_NativePointer node, const Opt_Type_TextClockInterface__setTextClockOptions_Arg0* options);
    void (*setFormat)(Ark_NativePointer node, const Ark_String* value);
    void (*setOnDateChange)(Ark_NativePointer node, Ark_Function event);
    void (*setFontColor)(Ark_NativePointer node, const ResourceColor* value);
    void (*setFontSize)(Ark_NativePointer node, const Ark_Length* value);
    void (*setFontStyle)(Ark_NativePointer node, Ark_Int32 value);
    void (*setFontWeight)(Ark_NativePointer node, const Type_TextClockAttribute_fontWeight_Arg0* value);
    void (*setFontFamily)(Ark_NativePointer node, const ResourceStr* value);
    void (*setTextShadow)(Ark_NativePointer node, const Type_TextClockAttribute_textShadow_Arg0* value);
    void (*setFontFeature)(Ark_NativePointer node, const Ark_String* value);
    void (*setContentModifier)(Ark_NativePointer node, const Ark_CustomObject* modifier);
    void (*setDateTimeOptions)(Ark_NativePointer node, const Opt_Ark_CustomObject* dateTimeOptions);
} GENERATED_ArkUITextClockModifier;

typedef struct GENERATED_ArkUITextInputModifier {
    void (*_setTextInputOptions)(Ark_NativePointer node, const Opt_TextInputOptions* value);
    void (*setType)(Ark_NativePointer node, Ark_Int32 value);
    void (*setContentType)(Ark_NativePointer node, Ark_Int32 value);
    void (*setPlaceholderColor)(Ark_NativePointer node, const ResourceColor* value);
    void (*setTextOverflow)(Ark_NativePointer node, Ark_Int32 value);
    void (*setTextIndent)(Ark_NativePointer node, const Ark_Length* value);
    void (*setPlaceholderFont)(Ark_NativePointer node, const Opt_Font* value);
    void (*setEnterKeyType)(Ark_NativePointer node, Ark_Int32 value);
    void (*setCaretColor)(Ark_NativePointer node, const ResourceColor* value);
    void (*setOnEditChanged)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnEditChange)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnSubmit)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnChange)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnTextSelectionChange)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnContentScroll)(Ark_NativePointer node, Ark_Function callback);
    void (*setMaxLength)(Ark_NativePointer node, const Ark_Number* value);
    void (*setFontColor)(Ark_NativePointer node, const ResourceColor* value);
    void (*setFontSize)(Ark_NativePointer node, const Ark_Length* value);
    void (*setFontStyle)(Ark_NativePointer node, Ark_Int32 value);
    void (*setFontWeight)(Ark_NativePointer node, const Type_TextInputAttribute_fontWeight_Arg0* value);
    void (*setFontFamily)(Ark_NativePointer node, const ResourceStr* value);
    void (*setInputFilter)(Ark_NativePointer node, const ResourceStr* value, const Opt_Ark_Function* error);
    void (*setOnCopy)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnCut)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnPaste)(Ark_NativePointer node, Ark_Function callback);
    void (*setCopyOption)(Ark_NativePointer node, Ark_Int32 value);
    void (*setShowPasswordIcon)(Ark_NativePointer node, Ark_Boolean value);
    void (*setTextAlign)(Ark_NativePointer node, Ark_Int32 value);
    void (*setStyle)(Ark_NativePointer node, const Type_TextInputAttribute_style_Arg0* value);
    void (*setCaretStyle)(Ark_NativePointer node, const CaretStyle* value);
    void (*setSelectedBackgroundColor)(Ark_NativePointer node, const ResourceColor* value);
    void (*setCaretPosition)(Ark_NativePointer node, const Ark_Number* value);
    void (*setEnableKeyboardOnFocus)(Ark_NativePointer node, Ark_Boolean value);
    void (*setPasswordIcon)(Ark_NativePointer node, const PasswordIcon* value);
    void (*setShowError)(Ark_NativePointer node, const Opt_Type_TextInputAttribute_showError_Arg0* value);
    void (*setShowUnit)(Ark_NativePointer node, const CustomBuilder* value);
    void (*setShowUnderline)(Ark_NativePointer node, Ark_Boolean value);
    void (*setUnderlineColor)(Ark_NativePointer node, const Type_TextInputAttribute_underlineColor_Arg0* value);
    void (*setSelectionMenuHidden)(Ark_NativePointer node, Ark_Boolean value);
    void (*setBarState)(Ark_NativePointer node, Ark_Int32 value);
    void (*setMaxLines)(Ark_NativePointer node, const Ark_Number* value);
    void (*setWordBreak)(Ark_NativePointer node, Ark_Int32 value);
    void (*setLineBreakStrategy)(Ark_NativePointer node, Ark_Int32 strategy);
    void (*setCustomKeyboard)(Ark_NativePointer node, const CustomBuilder* value, const Opt_KeyboardOptions* options);
    void (*setShowCounter)(Ark_NativePointer node, Ark_Boolean value, const Opt_InputCounterOptions* options);
    void (*setCancelButton)(Ark_NativePointer node, const Type_TextInputAttribute_cancelButton_Arg0* value);
    void (*setSelectAll)(Ark_NativePointer node, Ark_Boolean value);
    void (*setMinFontSize)(Ark_NativePointer node, const Type_TextInputAttribute_minFontSize_Arg0* value);
    void (*setMaxFontSize)(Ark_NativePointer node, const Type_TextInputAttribute_maxFontSize_Arg0* value);
    void (*setHeightAdaptivePolicy)(Ark_NativePointer node, Ark_Int32 value);
    void (*setEnableAutoFill)(Ark_NativePointer node, Ark_Boolean value);
    void (*setDecoration)(Ark_NativePointer node, const TextDecorationOptions* value);
    void (*setLetterSpacing)(Ark_NativePointer node, const Type_TextInputAttribute_letterSpacing_Arg0* value);
    void (*setLineHeight)(Ark_NativePointer node, const Type_TextInputAttribute_lineHeight_Arg0* value);
    void (*setPasswordRules)(Ark_NativePointer node, const Ark_String* value);
    void (*setFontFeature)(Ark_NativePointer node, const Ark_String* value);
    void (*setShowPassword)(Ark_NativePointer node, Ark_Boolean visible);
    void (*setOnSecurityStateChange)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnWillInsert)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnDidInsert)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnWillDelete)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnDidDelete)(Ark_NativePointer node, Ark_Function callback);
    void (*setEditMenuOptions)(Ark_NativePointer node, const Ark_Materialized* editMenu);
    void (*setEnablePreviewText)(Ark_NativePointer node, Ark_Boolean enable);
} GENERATED_ArkUITextInputModifier;

typedef struct GENERATED_ArkUITextPickerModifier {
    void (*_setTextPickerOptions)(Ark_NativePointer node, const Opt_TextPickerOptions* options);
    void (*setDefaultPickerItemHeight)(Ark_NativePointer node, const Type_TextPickerAttribute_defaultPickerItemHeight_Arg0* value);
    void (*setCanLoop)(Ark_NativePointer node, Ark_Boolean value);
    void (*setDisappearTextStyle)(Ark_NativePointer node, const PickerTextStyle* value);
    void (*setTextStyle)(Ark_NativePointer node, const PickerTextStyle* value);
    void (*setSelectedTextStyle)(Ark_NativePointer node, const PickerTextStyle* value);
    void (*setOnAccept)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnCancel)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnChange)(Ark_NativePointer node, Ark_Function callback);
    void (*setSelectedIndex)(Ark_NativePointer node, const Type_TextPickerAttribute_selectedIndex_Arg0* value);
    void (*setDivider)(Ark_NativePointer node, const Type_TextPickerAttribute_divider_Arg0* value);
    void (*setGradientHeight)(Ark_NativePointer node, const Ark_Length* value);
} GENERATED_ArkUITextPickerModifier;

typedef struct GENERATED_ArkUITextTimerModifier {
    void (*_setTextTimerOptions)(Ark_NativePointer node, const Opt_TextTimerOptions* options);
    void (*setFormat)(Ark_NativePointer node, const Ark_String* value);
    void (*setFontColor)(Ark_NativePointer node, const ResourceColor* value);
    void (*setFontSize)(Ark_NativePointer node, const Ark_Length* value);
    void (*setFontStyle)(Ark_NativePointer node, Ark_Int32 value);
    void (*setFontWeight)(Ark_NativePointer node, const Type_TextTimerAttribute_fontWeight_Arg0* value);
    void (*setFontFamily)(Ark_NativePointer node, const ResourceStr* value);
    void (*setOnTimer)(Ark_NativePointer node, Ark_Function event);
    void (*setTextShadow)(Ark_NativePointer node, const Type_TextTimerAttribute_textShadow_Arg0* value);
    void (*setContentModifier)(Ark_NativePointer node, const Ark_CustomObject* modifier);
} GENERATED_ArkUITextTimerModifier;

typedef struct GENERATED_ArkUITimePickerModifier {
    void (*_setTimePickerOptions)(Ark_NativePointer node, const Opt_TimePickerOptions* options);
    void (*setUseMilitaryTime)(Ark_NativePointer node, Ark_Boolean value);
    void (*setLoop)(Ark_NativePointer node, Ark_Boolean value);
    void (*setDisappearTextStyle)(Ark_NativePointer node, const PickerTextStyle* value);
    void (*setTextStyle)(Ark_NativePointer node, const PickerTextStyle* value);
    void (*setSelectedTextStyle)(Ark_NativePointer node, const PickerTextStyle* value);
    void (*setDateTimeOptions)(Ark_NativePointer node, const Ark_CustomObject* value);
    void (*setOnChange)(Ark_NativePointer node, Ark_Function callback);
    void (*setEnableHapticFeedback)(Ark_NativePointer node, Ark_Boolean enable);
} GENERATED_ArkUITimePickerModifier;

typedef struct GENERATED_ArkUIToggleModifier {
    void (*_setToggleOptions)(Ark_NativePointer node, const Type_ToggleInterface__setToggleOptions_Arg0* options);
    void (*setOnChange)(Ark_NativePointer node, Ark_Function callback);
    void (*setContentModifier)(Ark_NativePointer node, const Ark_CustomObject* modifier);
    void (*setSelectedColor)(Ark_NativePointer node, const ResourceColor* value);
    void (*setSwitchPointColor)(Ark_NativePointer node, const ResourceColor* color);
    void (*setSwitchStyle)(Ark_NativePointer node, const SwitchStyle* value);
} GENERATED_ArkUIToggleModifier;

typedef struct GENERATED_ArkUIVideoModifier {
    void (*_setVideoOptions)(Ark_NativePointer node, const VideoOptions* value);
    void (*setMuted)(Ark_NativePointer node, Ark_Boolean value);
    void (*setAutoPlay)(Ark_NativePointer node, Ark_Boolean value);
    void (*setControls)(Ark_NativePointer node, Ark_Boolean value);
    void (*setLoop)(Ark_NativePointer node, Ark_Boolean value);
    void (*setObjectFit)(Ark_NativePointer node, Ark_Int32 value);
    void (*setOnStart)(Ark_NativePointer node, Ark_Function event);
    void (*setOnPause)(Ark_NativePointer node, Ark_Function event);
    void (*setOnFinish)(Ark_NativePointer node, Ark_Function event);
    void (*setOnFullscreenChange)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnPrepared)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnSeeking)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnSeeked)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnUpdate)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnError)(Ark_NativePointer node, Ark_Function event);
    void (*setOnStop)(Ark_NativePointer node, Ark_Function event);
    void (*setEnableAnalyzer)(Ark_NativePointer node, Ark_Boolean enable);
    void (*setAnalyzerConfig)(Ark_NativePointer node, const ImageAnalyzerConfig* config);
} GENERATED_ArkUIVideoModifier;

typedef struct GENERATED_ArkUIWebModifier {
    void (*_setWebOptions)(Ark_NativePointer node, const WebOptions* value);
    void (*setJavaScriptAccess)(Ark_NativePointer node, Ark_Boolean javaScriptAccess);
    void (*setFileAccess)(Ark_NativePointer node, Ark_Boolean fileAccess);
    void (*setOnlineImageAccess)(Ark_NativePointer node, Ark_Boolean onlineImageAccess);
    void (*setDomStorageAccess)(Ark_NativePointer node, Ark_Boolean domStorageAccess);
    void (*setImageAccess)(Ark_NativePointer node, Ark_Boolean imageAccess);
    void (*setMixedMode)(Ark_NativePointer node, Ark_Int32 mixedMode);
    void (*setZoomAccess)(Ark_NativePointer node, Ark_Boolean zoomAccess);
    void (*setGeolocationAccess)(Ark_NativePointer node, Ark_Boolean geolocationAccess);
    void (*setJavaScriptProxy)(Ark_NativePointer node, const JavaScriptProxy* javaScriptProxy);
    void (*setPassword)(Ark_NativePointer node, Ark_Boolean password);
    void (*setCacheMode)(Ark_NativePointer node, Ark_Int32 cacheMode);
    void (*setDarkMode)(Ark_NativePointer node, Ark_Int32 mode);
    void (*setForceDarkAccess)(Ark_NativePointer node, Ark_Boolean access);
    void (*setMediaOptions)(Ark_NativePointer node, const WebMediaOptions* options);
    void (*setTableData)(Ark_NativePointer node, Ark_Boolean tableData);
    void (*setWideViewModeAccess)(Ark_NativePointer node, Ark_Boolean wideViewModeAccess);
    void (*setOverviewModeAccess)(Ark_NativePointer node, Ark_Boolean overviewModeAccess);
    void (*setOverScrollMode)(Ark_NativePointer node, Ark_Int32 mode);
    void (*setTextZoomAtio)(Ark_NativePointer node, const Ark_Number* textZoomAtio);
    void (*setTextZoomRatio)(Ark_NativePointer node, const Ark_Number* textZoomRatio);
    void (*setDatabaseAccess)(Ark_NativePointer node, Ark_Boolean databaseAccess);
    void (*setInitialScale)(Ark_NativePointer node, const Ark_Number* percent);
    void (*setUserAgent)(Ark_NativePointer node, const Ark_String* userAgent);
    void (*setMetaViewport)(Ark_NativePointer node, Ark_Boolean enabled);
    void (*setOnPageEnd)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnPageBegin)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnProgressChange)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnTitleReceive)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnGeolocationHide)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnGeolocationShow)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnRequestSelected)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnAlert)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnBeforeUnload)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnConfirm)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnPrompt)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnConsole)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnErrorReceive)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnHttpErrorReceive)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnDownloadStart)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnRefreshAccessedHistory)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnUrlLoadIntercept)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnSslErrorReceive)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnRenderExited_CallbackOnRenderExitedEvent)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnShowFileSelector)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnRenderExited_eventdetailObjectboolean)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnFileSelectorShow)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnResourceLoad)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnFullScreenExit)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnFullScreenEnter)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnScaleChange)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnHttpAuthRequest)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnInterceptRequest)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnPermissionRequest)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnScreenCaptureRequest)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnContextMenuShow)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnContextMenuHide)(Ark_NativePointer node, Ark_Function callback);
    void (*setMediaPlayGestureAccess)(Ark_NativePointer node, Ark_Boolean access);
    void (*setOnSearchResultReceive)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnScroll)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnSslErrorEventReceive)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnSslErrorEvent)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnClientAuthenticationRequest)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnWindowNew)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnWindowExit)(Ark_NativePointer node, Ark_Function callback);
    void (*setMultiWindowAccess)(Ark_NativePointer node, Ark_Boolean multiWindow);
    void (*setOnInterceptKeyEvent)(Ark_NativePointer node, Ark_Function callback);
    void (*setWebStandardFont)(Ark_NativePointer node, const Ark_String* family);
    void (*setWebSerifFont)(Ark_NativePointer node, const Ark_String* family);
    void (*setWebSansSerifFont)(Ark_NativePointer node, const Ark_String* family);
    void (*setWebFixedFont)(Ark_NativePointer node, const Ark_String* family);
    void (*setWebFantasyFont)(Ark_NativePointer node, const Ark_String* family);
    void (*setWebCursiveFont)(Ark_NativePointer node, const Ark_String* family);
    void (*setDefaultFixedFontSize)(Ark_NativePointer node, const Ark_Number* size);
    void (*setDefaultFontSize)(Ark_NativePointer node, const Ark_Number* size);
    void (*setMinFontSize)(Ark_NativePointer node, const Ark_Number* size);
    void (*setMinLogicalFontSize)(Ark_NativePointer node, const Ark_Number* size);
    void (*setDefaultTextEncodingFormat)(Ark_NativePointer node, const Ark_String* textEncodingFormat);
    void (*setForceDisplayScrollBar)(Ark_NativePointer node, Ark_Boolean enabled);
    void (*setBlockNetwork)(Ark_NativePointer node, Ark_Boolean block);
    void (*setHorizontalScrollBarAccess)(Ark_NativePointer node, Ark_Boolean horizontalScrollBar);
    void (*setVerticalScrollBarAccess)(Ark_NativePointer node, Ark_Boolean verticalScrollBar);
    void (*setOnTouchIconUrlReceived)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnFaviconReceived)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnPageVisible)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnDataResubmitted)(Ark_NativePointer node, Ark_Function callback);
    void (*setPinchSmooth)(Ark_NativePointer node, Ark_Boolean isEnabled);
    void (*setAllowWindowOpenMethod)(Ark_NativePointer node, Ark_Boolean flag);
    void (*setOnAudioStateChanged)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnFirstContentfulPaint)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnFirstMeaningfulPaint)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnLargestContentfulPaint)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnLoadIntercept)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnControllerAttached)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnOverScroll)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnSafeBrowsingCheckResult)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnNavigationEntryCommitted)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnIntelligentTrackingPreventionResult)(Ark_NativePointer node, Ark_Function callback);
    void (*setJavaScriptOnDocumentStart)(Ark_NativePointer node, const Array_ScriptItem* scripts);
    void (*setJavaScriptOnDocumentEnd)(Ark_NativePointer node, const Array_ScriptItem* scripts);
    void (*setLayoutMode)(Ark_NativePointer node, Ark_Int32 mode);
    void (*setNestedScroll)(Ark_NativePointer node, const NestedScrollOptions* value);
    void (*setEnableNativeEmbedMode)(Ark_NativePointer node, Ark_Boolean mode);
    void (*setRegisterNativeEmbedRule)(Ark_NativePointer node, const Ark_String* tag, const Ark_String* type);
    void (*setOnNativeEmbedLifecycleChange)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnNativeEmbedGestureEvent)(Ark_NativePointer node, Ark_Function callback);
    void (*setCopyOptions)(Ark_NativePointer node, Ark_Int32 value);
    void (*setOnOverrideUrlLoading)(Ark_NativePointer node, Ark_Function callback);
    void (*setTextAutosizing)(Ark_NativePointer node, Ark_Boolean textAutosizing);
    void (*setEnableNativeMediaPlayer)(Ark_NativePointer node, const NativeMediaPlayerConfig* config);
    void (*setEnableSmoothDragResize)(Ark_NativePointer node, Ark_Boolean mode);
    void (*setOnRenderProcessNotResponding)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnRenderProcessResponding)(Ark_NativePointer node, Ark_Function callback);
    void (*setSelectionMenuOptions)(Ark_NativePointer node, const Array_ExpandedMenuItemOptions* expandedMenuOptions);
    void (*setOnViewportFitChanged)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnInterceptKeyboardAttach)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnAdsBlocked)(Ark_NativePointer node, Ark_Function callback);
    void (*setKeyboardAvoidMode)(Ark_NativePointer node, Ark_Int32 mode);
} GENERATED_ArkUIWebModifier;

typedef struct GENERATED_ArkUIWindowSceneModifier {
    void (*_setWindowSceneOptions)(Ark_NativePointer node, const Ark_Number* persistentId);
    void (*setAttractionEffect)(Ark_NativePointer node, const Position* destination, const Ark_Number* fraction);
} GENERATED_ArkUIWindowSceneModifier;

typedef struct GENERATED_ArkUIXComponentModifier {
    void (*_setXComponentOptions_idstringtypestringlibrarynamestringcontrollerXComponentController)(Ark_NativePointer node, const Type_XComponentInterface__setXComponentOptions_Arg0* value);
    void (*_setXComponentOptions_idstringtypeXComponentTypelibrarynamestringcontrollerXComponentController)(Ark_NativePointer node, const Type_XComponentInterface__setXComponentOptions1_Arg0* value);
    void (*_setXComponentOptions_XComponentOptions)(Ark_NativePointer node, const XComponentOptions* options);
    void (*setOnLoad)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnDestroy)(Ark_NativePointer node, Ark_Function event);
    void (*setEnableAnalyzer)(Ark_NativePointer node, Ark_Boolean enable);
} GENERATED_ArkUIXComponentModifier;

typedef struct GENERATED_ArkUISideBarContainerModifier {
    void (*_setSideBarContainerOptions)(Ark_NativePointer node, const Opt_Ark_SideBarContainerType* type);
    void (*setShowSideBar)(Ark_NativePointer node, Ark_Boolean value);
    void (*setControlButton)(Ark_NativePointer node, const ButtonStyle* value);
    void (*setShowControlButton)(Ark_NativePointer node, Ark_Boolean value);
    void (*setOnChange)(Ark_NativePointer node, Ark_Function callback);
    void (*setSideBarWidth_number)(Ark_NativePointer node, const Ark_Number* value);
    void (*setMinSideBarWidth_number)(Ark_NativePointer node, const Ark_Number* value);
    void (*setMaxSideBarWidth_number)(Ark_NativePointer node, const Ark_Number* value);
    void (*setSideBarWidth_Length)(Ark_NativePointer node, const Ark_Length* value);
    void (*setMinSideBarWidth_Length)(Ark_NativePointer node, const Ark_Length* value);
    void (*setMaxSideBarWidth_Length)(Ark_NativePointer node, const Ark_Length* value);
    void (*setAutoHide)(Ark_NativePointer node, Ark_Boolean value);
    void (*setSideBarPosition)(Ark_NativePointer node, Ark_Int32 value);
    void (*setDivider)(Ark_NativePointer node, const Type_SideBarContainerAttribute_divider_Arg0* value);
    void (*setMinContentWidth)(Ark_NativePointer node, const Ark_Length* value);
} GENERATED_ArkUISideBarContainerModifier;

typedef struct GENERATED_ArkUIRemoteWindowModifier {
    void (*_setRemoteWindowOptions)(Ark_NativePointer node, const WindowAnimationTarget* target);
} GENERATED_ArkUIRemoteWindowModifier;

typedef struct GENERATED_ArkUIWaterFlowModifier {
    void (*_setWaterFlowOptions)(Ark_NativePointer node, const Opt_WaterFlowOptions* options);
    void (*setColumnsTemplate)(Ark_NativePointer node, const Ark_String* value);
    void (*setItemConstraintSize)(Ark_NativePointer node, const ConstraintSizeOptions* value);
    void (*setRowsTemplate)(Ark_NativePointer node, const Ark_String* value);
    void (*setColumnsGap)(Ark_NativePointer node, const Ark_Length* value);
    void (*setRowsGap)(Ark_NativePointer node, const Ark_Length* value);
    void (*setLayoutDirection)(Ark_NativePointer node, Ark_Int32 value);
    void (*setNestedScroll)(Ark_NativePointer node, const NestedScrollOptions* value);
    void (*setEnableScrollInteraction)(Ark_NativePointer node, Ark_Boolean value);
    void (*setFriction)(Ark_NativePointer node, const Type_WaterFlowAttribute_friction_Arg0* value);
    void (*setCachedCount)(Ark_NativePointer node, const Ark_Number* value);
    void (*setOnReachStart)(Ark_NativePointer node, Ark_Function event);
    void (*setOnReachEnd)(Ark_NativePointer node, Ark_Function event);
    void (*setOnScrollFrameBegin)(Ark_NativePointer node, Ark_Function event);
    void (*setOnScrollIndex)(Ark_NativePointer node, Ark_Function event);
} GENERATED_ArkUIWaterFlowModifier;

typedef struct GENERATED_ArkUIUIExtensionComponentModifier {
    void (*_setUIExtensionComponentOptions)(Ark_NativePointer node, const Ark_CustomObject* want, const Opt_UIExtensionOptions* options);
    void (*setOnRemoteReady)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnReceive)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnResult)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnRelease)(Ark_NativePointer node, Ark_Function callback);
    void (*setOnError)(Ark_NativePointer node, const Ark_CustomObject* callback);
    void (*setOnTerminated)(Ark_NativePointer node, Ark_Function callback);
} GENERATED_ArkUIUIExtensionComponentModifier;

typedef struct GENERATED_ArkUILinearIndicatorModifier {
    void (*_setLinearIndicatorOptions)(Ark_NativePointer node, const Opt_Ark_Number* count, const Opt_LinearIndicatorController* controller);
    void (*setIndicatorStyle)(Ark_NativePointer node, const Opt_LinearIndicatorStyle* style);
    void (*setIndicatorLoop)(Ark_NativePointer node, const Opt_Ark_Boolean* loop);
    void (*setOnChange)(Ark_NativePointer node, const Opt_Ark_Function* callback);
} GENERATED_ArkUILinearIndicatorModifier;

// Accessors

typedef struct DrawModifierPeer DrawModifierPeer;
typedef struct GENERATED_ArkUIDrawModifierAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    void (*drawBehind)(DrawModifierPeer* peer, const Ark_CustomObject* drawContext);
    void (*drawContent)(DrawModifierPeer* peer, const Ark_CustomObject* drawContext);
    void (*drawFront)(DrawModifierPeer* peer, const Ark_CustomObject* drawContext);
    void (*invalidate)(DrawModifierPeer* peer);
} GENERATED_ArkUIDrawModifierAccessor;

typedef struct PanGestureOptionsPeer PanGestureOptionsPeer;
typedef struct GENERATED_ArkUIPanGestureOptionsAccessor {
    Ark_NativePointer (*ctor)(const Opt_Literal_fingers_Opt_Ark_Number_direction_Ark_PanDirection_distance_Opt_Ark_Number* value);
    Ark_NativePointer (*getFinalizer)();
    void (*setDirection)(PanGestureOptionsPeer* peer, Ark_Int32 value);
    void (*setDistance)(PanGestureOptionsPeer* peer, const Ark_Number* value);
    void (*setFingers)(PanGestureOptionsPeer* peer, const Ark_Number* value);
    Ark_NativePointer (*getDirection)(PanGestureOptionsPeer* peer);
} GENERATED_ArkUIPanGestureOptionsAccessor;

typedef struct ProgressMaskPeer ProgressMaskPeer;
typedef struct GENERATED_ArkUIProgressMaskAccessor {
    Ark_NativePointer (*ctor)(const Ark_Number* value, const Ark_Number* total, const ResourceColor* color);
    Ark_NativePointer (*getFinalizer)();
    void (*updateProgress)(ProgressMaskPeer* peer, const Ark_Number* value);
    void (*updateColor)(ProgressMaskPeer* peer, const ResourceColor* value);
    void (*enableBreathingAnimation)(ProgressMaskPeer* peer, Ark_Boolean value);
} GENERATED_ArkUIProgressMaskAccessor;

typedef struct AttributeModifierPeer AttributeModifierPeer;
typedef struct GENERATED_ArkUIAttributeModifierAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    void (*applyNormalAttribute)(AttributeModifierPeer* peer, const Ark_CustomObject* instance);
    void (*applyPressedAttribute)(AttributeModifierPeer* peer, const Ark_CustomObject* instance);
    void (*applyFocusedAttribute)(AttributeModifierPeer* peer, const Ark_CustomObject* instance);
    void (*applyDisabledAttribute)(AttributeModifierPeer* peer, const Ark_CustomObject* instance);
    void (*applySelectedAttribute)(AttributeModifierPeer* peer, const Ark_CustomObject* instance);
} GENERATED_ArkUIAttributeModifierAccessor;

typedef struct GestureModifierPeer GestureModifierPeer;
typedef struct GENERATED_ArkUIGestureModifierAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    void (*applyGesture)(GestureModifierPeer* peer, const UIGestureEvent* event);
} GENERATED_ArkUIGestureModifierAccessor;

typedef struct GestureRecognizerPeer GestureRecognizerPeer;
typedef struct GENERATED_ArkUIGestureRecognizerAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    void (*getTag)(GestureRecognizerPeer* peer);
    Ark_NativePointer (*getType)(GestureRecognizerPeer* peer);
    Ark_Boolean (*isBuiltIn)(GestureRecognizerPeer* peer);
    void (*setEnabled)(GestureRecognizerPeer* peer, Ark_Boolean isEnabled);
    Ark_Boolean (*isEnabled)(GestureRecognizerPeer* peer);
    Ark_NativePointer (*getState)(GestureRecognizerPeer* peer);
    Ark_NativePointer (*getEventTargetInfo)(GestureRecognizerPeer* peer);
} GENERATED_ArkUIGestureRecognizerAccessor;

typedef struct EventTargetInfoPeer EventTargetInfoPeer;
typedef struct GENERATED_ArkUIEventTargetInfoAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    void (*getId)(EventTargetInfoPeer* peer);
} GENERATED_ArkUIEventTargetInfoAccessor;

typedef struct ContentModifierPeer ContentModifierPeer;
typedef struct GENERATED_ArkUIContentModifierAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    Ark_NativePointer (*applyContent)(ContentModifierPeer* peer);
} GENERATED_ArkUIContentModifierAccessor;

typedef struct CalendarControllerPeer CalendarControllerPeer;
typedef struct GENERATED_ArkUICalendarControllerAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    void (*backToToday)(CalendarControllerPeer* peer);
    void (*goTo)(CalendarControllerPeer* peer, const Literal_year_Ark_Number_month_Ark_Number_day_Ark_Number* value);
} GENERATED_ArkUICalendarControllerAccessor;

typedef struct CanvasRenderingContext2DPeer CanvasRenderingContext2DPeer;
typedef struct GENERATED_ArkUICanvasRenderingContext2DAccessor {
    Ark_NativePointer (*ctor)(const Opt_RenderingContextSettings* settings);
    Ark_NativePointer (*getFinalizer)();
    void (*toDataURL)(CanvasRenderingContext2DPeer* peer, const Opt_Ark_String* type, const Opt_Ark_CustomObject* quality);
    Ark_NativePointer (*startImageAnalyzer)(CanvasRenderingContext2DPeer* peer, const ImageAnalyzerConfig* config);
    void (*stopImageAnalyzer)(CanvasRenderingContext2DPeer* peer);
} GENERATED_ArkUICanvasRenderingContext2DAccessor;

typedef struct CanvasRendererPeer CanvasRendererPeer;
typedef struct GENERATED_ArkUICanvasRendererAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    void (*drawImage_ImageBitmapPixelMap_number_number)(CanvasRendererPeer* peer, const Union_ImageBitmap_PixelMap* image, const Ark_Number* dx, const Ark_Number* dy);
    void (*drawImage_ImageBitmapPixelMap_number_number_number_number)(CanvasRendererPeer* peer, const Union_ImageBitmap_PixelMap* image, const Ark_Number* dx, const Ark_Number* dy, const Ark_Number* dw, const Ark_Number* dh);
    void (*drawImage_ImageBitmapPixelMap_number_number_number_number_number_number_number_number)(CanvasRendererPeer* peer, const Union_ImageBitmap_PixelMap* image, const Ark_Number* sx, const Ark_Number* sy, const Ark_Number* sw, const Ark_Number* sh, const Ark_Number* dx, const Ark_Number* dy, const Ark_Number* dw, const Ark_Number* dh);
    void (*beginPath)(CanvasRendererPeer* peer);
    void (*clip_CanvasFillRule)(CanvasRendererPeer* peer, const Opt_CanvasFillRule* fillRule);
    void (*clip_PathD_CanvasFillRule)(CanvasRendererPeer* peer, const Ark_Materialized* path, const Opt_CanvasFillRule* fillRule);
    void (*fill_CanvasFillRule)(CanvasRendererPeer* peer, const Opt_CanvasFillRule* fillRule);
    void (*fill_PathD_CanvasFillRule)(CanvasRendererPeer* peer, const Ark_Materialized* path, const Opt_CanvasFillRule* fillRule);
    void (*stroke_)(CanvasRendererPeer* peer);
    void (*stroke_PathD)(CanvasRendererPeer* peer, const Ark_Materialized* path);
    Ark_NativePointer (*createLinearGradient)(CanvasRendererPeer* peer, const Ark_Number* x0, const Ark_Number* y0, const Ark_Number* x1, const Ark_Number* y1);
    Ark_NativePointer (*createPattern)(CanvasRendererPeer* peer, const Ark_Materialized* image, const Union_Ark_String_Ark_Undefined* repetition);
    Ark_NativePointer (*createRadialGradient)(CanvasRendererPeer* peer, const Ark_Number* x0, const Ark_Number* y0, const Ark_Number* r0, const Ark_Number* x1, const Ark_Number* y1, const Ark_Number* r1);
    Ark_NativePointer (*createConicGradient)(CanvasRendererPeer* peer, const Ark_Number* startAngle, const Ark_Number* x, const Ark_Number* y);
    Ark_NativePointer (*createImageData_number_number)(CanvasRendererPeer* peer, const Ark_Number* sw, const Ark_Number* sh);
    Ark_NativePointer (*createImageData_ImageData)(CanvasRendererPeer* peer, const ImageData* imagedata);
    Ark_NativePointer (*getImageData)(CanvasRendererPeer* peer, const Ark_Number* sx, const Ark_Number* sy, const Ark_Number* sw, const Ark_Number* sh);
    Ark_NativePointer (*getPixelMap)(CanvasRendererPeer* peer, const Ark_Number* sx, const Ark_Number* sy, const Ark_Number* sw, const Ark_Number* sh);
    void (*putImageData_ImageData_numberstring_numberstring)(CanvasRendererPeer* peer, const ImageData* imagedata, const Union_Ark_Number_Ark_String* dx, const Union_Ark_Number_Ark_String* dy);
    void (*putImageData_ImageData_numberstring_numberstring_numberstring_numberstring_numberstring_numberstring)(CanvasRendererPeer* peer, const ImageData* imagedata, const Union_Ark_Number_Ark_String* dx, const Union_Ark_Number_Ark_String* dy, const Union_Ark_Number_Ark_String* dirtyX, const Union_Ark_Number_Ark_String* dirtyY, const Union_Ark_Number_Ark_String* dirtyWidth, const Union_Ark_Number_Ark_String* dirtyHeight);
    void (*getLineDash)(CanvasRendererPeer* peer);
    void (*setLineDash)(CanvasRendererPeer* peer, const Array_Ark_Number* segments);
    void (*clearRect)(CanvasRendererPeer* peer, const Ark_Number* x, const Ark_Number* y, const Ark_Number* w, const Ark_Number* h);
    void (*fillRect)(CanvasRendererPeer* peer, const Ark_Number* x, const Ark_Number* y, const Ark_Number* w, const Ark_Number* h);
    void (*strokeRect)(CanvasRendererPeer* peer, const Ark_Number* x, const Ark_Number* y, const Ark_Number* w, const Ark_Number* h);
    void (*restore)(CanvasRendererPeer* peer);
    void (*save)(CanvasRendererPeer* peer);
    void (*fillText)(CanvasRendererPeer* peer, const Ark_String* text, const Ark_Number* x, const Ark_Number* y, const Opt_Ark_Number* maxWidth);
    Ark_NativePointer (*measureText)(CanvasRendererPeer* peer, const Ark_String* text);
    void (*strokeText)(CanvasRendererPeer* peer, const Ark_String* text, const Ark_Number* x, const Ark_Number* y, const Opt_Ark_Number* maxWidth);
    Ark_NativePointer (*getTransform)(CanvasRendererPeer* peer);
    void (*resetTransform)(CanvasRendererPeer* peer);
    void (*rotate)(CanvasRendererPeer* peer, const Ark_Number* angle);
    void (*scale)(CanvasRendererPeer* peer, const Ark_Number* x, const Ark_Number* y);
    void (*setTransform_number_number_number_number_number_number)(CanvasRendererPeer* peer, const Ark_Number* a, const Ark_Number* b, const Ark_Number* c, const Ark_Number* d, const Ark_Number* e, const Ark_Number* f);
    void (*setTransform_MatrixD)(CanvasRendererPeer* peer, const Opt_Matrix2D* transform);
    void (*transform)(CanvasRendererPeer* peer, const Ark_Number* a, const Ark_Number* b, const Ark_Number* c, const Ark_Number* d, const Ark_Number* e, const Ark_Number* f);
    void (*translate)(CanvasRendererPeer* peer, const Ark_Number* x, const Ark_Number* y);
    void (*setPixelMap)(CanvasRendererPeer* peer, const Opt_PixelMap* value);
    void (*transferFromImageBitmap)(CanvasRendererPeer* peer, const Ark_Materialized* bitmap);
    void (*saveLayer)(CanvasRendererPeer* peer);
    void (*restoreLayer)(CanvasRendererPeer* peer);
    void (*reset)(CanvasRendererPeer* peer);
} GENERATED_ArkUICanvasRendererAccessor;

typedef struct CanvasPathPeer CanvasPathPeer;
typedef struct GENERATED_ArkUICanvasPathAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    void (*arc)(CanvasPathPeer* peer, const Ark_Number* x, const Ark_Number* y, const Ark_Number* radius, const Ark_Number* startAngle, const Ark_Number* endAngle, const Opt_Ark_Boolean* counterclockwise);
    void (*arcTo)(CanvasPathPeer* peer, const Ark_Number* x1, const Ark_Number* y1, const Ark_Number* x2, const Ark_Number* y2, const Ark_Number* radius);
    void (*bezierCurveTo)(CanvasPathPeer* peer, const Ark_Number* cp1x, const Ark_Number* cp1y, const Ark_Number* cp2x, const Ark_Number* cp2y, const Ark_Number* x, const Ark_Number* y);
    void (*closePath)(CanvasPathPeer* peer);
    void (*ellipse)(CanvasPathPeer* peer, const Ark_Number* x, const Ark_Number* y, const Ark_Number* radiusX, const Ark_Number* radiusY, const Ark_Number* rotation, const Ark_Number* startAngle, const Ark_Number* endAngle, const Opt_Ark_Boolean* counterclockwise);
    void (*lineTo)(CanvasPathPeer* peer, const Ark_Number* x, const Ark_Number* y);
    void (*moveTo)(CanvasPathPeer* peer, const Ark_Number* x, const Ark_Number* y);
    void (*quadraticCurveTo)(CanvasPathPeer* peer, const Ark_Number* cpx, const Ark_Number* cpy, const Ark_Number* x, const Ark_Number* y);
    void (*rect)(CanvasPathPeer* peer, const Ark_Number* x, const Ark_Number* y, const Ark_Number* w, const Ark_Number* h);
} GENERATED_ArkUICanvasPathAccessor;

typedef struct ImageBitmapPeer ImageBitmapPeer;
typedef struct GENERATED_ArkUIImageBitmapAccessor {
    Ark_NativePointer (*ctor)(const Ark_String* src);
    Ark_NativePointer (*getFinalizer)();
    void (*close)(ImageBitmapPeer* peer);
} GENERATED_ArkUIImageBitmapAccessor;

typedef struct Path2DPeer Path2DPeer;
typedef struct GENERATED_ArkUIPath2DAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    void (*addPath)(Path2DPeer* peer, const Ark_Materialized* path, const Opt_Matrix2D* transform);
} GENERATED_ArkUIPath2DAccessor;

typedef struct Matrix2DPeer Matrix2DPeer;
typedef struct GENERATED_ArkUIMatrix2DAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    Ark_NativePointer (*identity)(Matrix2DPeer* peer);
    Ark_NativePointer (*invert)(Matrix2DPeer* peer);
    Ark_NativePointer (*multiply)(Matrix2DPeer* peer, const Opt_Matrix2D* other);
    Ark_NativePointer (*rotate_number_number)(Matrix2DPeer* peer, const Opt_Ark_Number* rx, const Opt_Ark_Number* ry);
    Ark_NativePointer (*rotate_number_number_number)(Matrix2DPeer* peer, const Ark_Number* degree, const Opt_Ark_Number* rx, const Opt_Ark_Number* ry);
    Ark_NativePointer (*translate)(Matrix2DPeer* peer, const Opt_Ark_Number* tx, const Opt_Ark_Number* ty);
    Ark_NativePointer (*scale)(Matrix2DPeer* peer, const Opt_Ark_Number* sx, const Opt_Ark_Number* sy);
} GENERATED_ArkUIMatrix2DAccessor;

typedef struct CanvasGradientPeer CanvasGradientPeer;
typedef struct GENERATED_ArkUICanvasGradientAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    void (*addColorStop)(CanvasGradientPeer* peer, const Ark_Number* offset, const Ark_String* color);
} GENERATED_ArkUICanvasGradientAccessor;

typedef struct CanvasPatternPeer CanvasPatternPeer;
typedef struct GENERATED_ArkUICanvasPatternAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    void (*setTransform)(CanvasPatternPeer* peer, const Opt_Matrix2D* transform);
} GENERATED_ArkUICanvasPatternAccessor;

typedef struct DrawingRenderingContextPeer DrawingRenderingContextPeer;
typedef struct GENERATED_ArkUIDrawingRenderingContextAccessor {
    Ark_NativePointer (*ctor)(const Opt_LengthMetricsUnit* unit);
    Ark_NativePointer (*getFinalizer)();
    void (*invalidate)(DrawingRenderingContextPeer* peer);
} GENERATED_ArkUIDrawingRenderingContextAccessor;

typedef struct ImageAnalyzerControllerPeer ImageAnalyzerControllerPeer;
typedef struct GENERATED_ArkUIImageAnalyzerControllerAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    void (*getImageAnalyzerSupportTypes)(ImageAnalyzerControllerPeer* peer);
} GENERATED_ArkUIImageAnalyzerControllerAccessor;

typedef struct ScrollerPeer ScrollerPeer;
typedef struct GENERATED_ArkUIScrollerAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    void (*scrollTo)(ScrollerPeer* peer, const Literal_xOffset_Union_Ark_Number_Ark_String_yOffset_Union_Ark_Number_Ark_String_animation_Opt_Union_Opt_ScrollAnimationOptions_Opt_Ark_Boolean* value);
    void (*scrollEdge)(ScrollerPeer* peer, Ark_Int32 value, const Opt_ScrollEdgeOptions* options);
    void (*fling)(ScrollerPeer* peer, const Ark_Number* velocity);
    void (*scrollPage_ScrollPageOptions)(ScrollerPeer* peer, const ScrollPageOptions* value);
    void (*scrollPage_nextbooleandirectionAxis)(ScrollerPeer* peer, const Literal_next_Ark_Boolean_direction_Ark_Axis* value);
    Ark_NativePointer (*currentOffset)(ScrollerPeer* peer);
    void (*scrollToIndex)(ScrollerPeer* peer, const Ark_Number* value, const Opt_Ark_Boolean* smooth, const Opt_Ark_ScrollAlign* align, const Opt_ScrollToIndexOptions* options);
    void (*scrollBy)(ScrollerPeer* peer, const Ark_Length* dx, const Ark_Length* dy);
    Ark_Boolean (*isAtEnd)(ScrollerPeer* peer);
    Ark_NativePointer (*getItemRect)(ScrollerPeer* peer, const Ark_Number* index);
} GENERATED_ArkUIScrollerAccessor;

typedef struct ChildrenMainSizePeer ChildrenMainSizePeer;
typedef struct GENERATED_ArkUIChildrenMainSizeAccessor {
    Ark_NativePointer (*ctor)(const Ark_Number* childDefaultSize);
    Ark_NativePointer (*getFinalizer)();
    void (*splice)(ChildrenMainSizePeer* peer, const Ark_Number* start, const Opt_Ark_Number* deleteCount, const Opt_Array_Ark_Number* childrenSize);
    void (*update)(ChildrenMainSizePeer* peer, const Ark_Number* index, const Ark_Number* childSize);
} GENERATED_ArkUIChildrenMainSizeAccessor;

typedef struct NavigationTransitionProxyPeer NavigationTransitionProxyPeer;
typedef struct GENERATED_ArkUINavigationTransitionProxyAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    void (*finishTransition)(NavigationTransitionProxyPeer* peer);
    void (*cancelTransition)(NavigationTransitionProxyPeer* peer);
    void (*updateTransition)(NavigationTransitionProxyPeer* peer, const Ark_Number* progress);
} GENERATED_ArkUINavigationTransitionProxyAccessor;

typedef struct NavPathStackPeer NavPathStackPeer;
typedef struct GENERATED_ArkUINavPathStackAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    void (*pushPath_NavPathInfo_boolean)(NavPathStackPeer* peer, const NavPathInfo* info, const Opt_Ark_Boolean* animated);
    void (*pushPath_NavPathInfo_NavigationOptions)(NavPathStackPeer* peer, const NavPathInfo* info, const Opt_NavigationOptions* options);
    Ark_NativePointer (*pushDestination_NavPathInfo_boolean)(NavPathStackPeer* peer, const NavPathInfo* info, const Opt_Ark_Boolean* animated);
    Ark_NativePointer (*pushDestination_NavPathInfo_NavigationOptions)(NavPathStackPeer* peer, const NavPathInfo* info, const Opt_NavigationOptions* options);
    void (*pushPathByName_string_unknown_boolean)(NavPathStackPeer* peer, const Ark_String* name, const Ark_CustomObject* param, const Opt_Ark_Boolean* animated);
    void (*pushPathByName_string_Object_IMPORTCallbackPopInfoFROMapiohosbase_boolean)(NavPathStackPeer* peer, const Ark_String* name, const Object* param, Ark_Function onPop, const Opt_Ark_Boolean* animated);
    Ark_NativePointer (*pushDestinationByName_string_Object_boolean)(NavPathStackPeer* peer, const Ark_String* name, const Object* param, const Opt_Ark_Boolean* animated);
    Ark_NativePointer (*pushDestinationByName_string_Object_IMPORTCallbackPopInfoFROMapiohosbase_boolean)(NavPathStackPeer* peer, const Ark_String* name, const Object* param, Ark_Function onPop, const Opt_Ark_Boolean* animated);
    void (*replacePath_NavPathInfo_boolean)(NavPathStackPeer* peer, const NavPathInfo* info, const Opt_Ark_Boolean* animated);
    void (*replacePath_NavPathInfo_NavigationOptions)(NavPathStackPeer* peer, const NavPathInfo* info, const Opt_NavigationOptions* options);
    void (*replacePathByName)(NavPathStackPeer* peer, const Ark_String* name, const Object* param, const Opt_Ark_Boolean* animated);
    Ark_Int32 (*removeByIndexes)(NavPathStackPeer* peer, const Array_Ark_Number* indexes);
    Ark_Int32 (*removeByName)(NavPathStackPeer* peer, const Ark_String* name);
    void (*pop_boolean)(NavPathStackPeer* peer, const Opt_Ark_Boolean* animated);
    void (*pop_Object_boolean)(NavPathStackPeer* peer, const Object* result, const Opt_Ark_Boolean* animated);
    Ark_Int32 (*popToName_string_boolean)(NavPathStackPeer* peer, const Ark_String* name, const Opt_Ark_Boolean* animated);
    Ark_Int32 (*popToName_string_Object_boolean)(NavPathStackPeer* peer, const Ark_String* name, const Object* result, const Opt_Ark_Boolean* animated);
    void (*popToIndex_number_boolean)(NavPathStackPeer* peer, const Ark_Number* index, const Opt_Ark_Boolean* animated);
    void (*popToIndex_number_Object_boolean)(NavPathStackPeer* peer, const Ark_Number* index, const Object* result, const Opt_Ark_Boolean* animated);
    Ark_Int32 (*moveToTop)(NavPathStackPeer* peer, const Ark_String* name, const Opt_Ark_Boolean* animated);
    void (*moveIndexToTop)(NavPathStackPeer* peer, const Ark_Number* index, const Opt_Ark_Boolean* animated);
    void (*clear)(NavPathStackPeer* peer, const Opt_Ark_Boolean* animated);
    Ark_NativePointer (*getAllPathName)(NavPathStackPeer* peer);
    void (*getParamByIndex)(NavPathStackPeer* peer, const Ark_Number* index);
    Ark_NativePointer (*getParamByName)(NavPathStackPeer* peer, const Ark_String* name);
    Ark_NativePointer (*getIndexByName)(NavPathStackPeer* peer, const Ark_String* name);
    Ark_NativePointer (*getParent)(NavPathStackPeer* peer);
    Ark_Int32 (*size)(NavPathStackPeer* peer);
    void (*disableAnimation)(NavPathStackPeer* peer, Ark_Boolean value);
    void (*setInterception)(NavPathStackPeer* peer, const NavigationInterception* interception);
} GENERATED_ArkUINavPathStackAccessor;

typedef struct NavDestinationContextPeer NavDestinationContextPeer;
typedef struct GENERATED_ArkUINavDestinationContextAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    void (*getConfigInRouteMap)(NavDestinationContextPeer* peer);
} GENERATED_ArkUINavDestinationContextAccessor;

typedef struct PatternLockControllerPeer PatternLockControllerPeer;
typedef struct GENERATED_ArkUIPatternLockControllerAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    void (*reset)(PatternLockControllerPeer* peer);
    void (*setChallengeResult)(PatternLockControllerPeer* peer, Ark_Int32 result);
} GENERATED_ArkUIPatternLockControllerAccessor;

typedef struct EditMenuOptionsPeer EditMenuOptionsPeer;
typedef struct GENERATED_ArkUIEditMenuOptionsAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    Ark_NativePointer (*onCreateMenu)(EditMenuOptionsPeer* peer, const Array_TextMenuItem* menuItems);
    Ark_Boolean (*onMenuItemClick)(EditMenuOptionsPeer* peer, const TextMenuItem* menuItem, const TextRange* range);
} GENERATED_ArkUIEditMenuOptionsAccessor;

typedef struct TextMenuItemIdPeer TextMenuItemIdPeer;
typedef struct GENERATED_ArkUITextMenuItemIdAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    Ark_NativePointer (*of)(const ResourceStr* id);
    Ark_Boolean (*equals)(TextMenuItemIdPeer* peer, const Ark_Materialized* id);
} GENERATED_ArkUITextMenuItemIdAccessor;

typedef struct RichEditorControllerPeer RichEditorControllerPeer;
typedef struct GENERATED_ArkUIRichEditorControllerAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    Ark_Int32 (*addTextSpan)(RichEditorControllerPeer* peer, const Ark_String* value, const Opt_RichEditorTextSpanOptions* options);
    Ark_Int32 (*addImageSpan)(RichEditorControllerPeer* peer, const Union_PixelMap_ResourceStr* value, const Opt_RichEditorImageSpanOptions* options);
    Ark_Int32 (*addBuilderSpan)(RichEditorControllerPeer* peer, const CustomBuilder* value, const Opt_RichEditorBuilderSpanOptions* options);
    Ark_Int32 (*addSymbolSpan)(RichEditorControllerPeer* peer, const Ark_CustomObject* value, const Opt_RichEditorSymbolSpanOptions* options);
    void (*updateSpanStyle)(RichEditorControllerPeer* peer, const Union_RichEditorUpdateTextSpanStyleOptions_RichEditorUpdateImageSpanStyleOptions_RichEditorUpdateSymbolSpanStyleOptions* value);
    void (*updateParagraphStyle)(RichEditorControllerPeer* peer, const RichEditorParagraphStyleOptions* value);
    void (*deleteSpans)(RichEditorControllerPeer* peer, const Opt_RichEditorRange* value);
    Ark_NativePointer (*getSpans)(RichEditorControllerPeer* peer, const Opt_RichEditorRange* value);
    Ark_NativePointer (*getParagraphs)(RichEditorControllerPeer* peer, const Opt_RichEditorRange* value);
    Ark_NativePointer (*getSelection)(RichEditorControllerPeer* peer);
    Ark_NativePointer (*fromStyledString)(RichEditorControllerPeer* peer, const Ark_Materialized* value);
    Ark_NativePointer (*toStyledString)(RichEditorControllerPeer* peer, const RichEditorRange* value);
} GENERATED_ArkUIRichEditorControllerAccessor;

typedef struct RichEditorBaseControllerPeer RichEditorBaseControllerPeer;
typedef struct GENERATED_ArkUIRichEditorBaseControllerAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    Ark_Int32 (*getCaretOffset)(RichEditorBaseControllerPeer* peer);
    Ark_Boolean (*setCaretOffset)(RichEditorBaseControllerPeer* peer, const Ark_Number* offset);
    void (*closeSelectionMenu)(RichEditorBaseControllerPeer* peer);
    Ark_NativePointer (*getTypingStyle)(RichEditorBaseControllerPeer* peer);
    void (*setTypingStyle)(RichEditorBaseControllerPeer* peer, const RichEditorTextStyle* value);
    void (*setSelection)(RichEditorBaseControllerPeer* peer, const Ark_Number* selectionStart, const Ark_Number* selectionEnd, const Opt_SelectionOptions* options);
    Ark_Boolean (*isEditing)(RichEditorBaseControllerPeer* peer);
    void (*stopEditing)(RichEditorBaseControllerPeer* peer);
    Ark_NativePointer (*getLayoutManager)(RichEditorBaseControllerPeer* peer);
} GENERATED_ArkUIRichEditorBaseControllerAccessor;

typedef struct TextEditControllerExPeer TextEditControllerExPeer;
typedef struct GENERATED_ArkUITextEditControllerExAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    Ark_Boolean (*isEditing)(TextEditControllerExPeer* peer);
    void (*stopEditing)(TextEditControllerExPeer* peer);
    Ark_Boolean (*setCaretOffset)(TextEditControllerExPeer* peer, const Ark_Number* offset);
    Ark_Int32 (*getCaretOffset)(TextEditControllerExPeer* peer);
} GENERATED_ArkUITextEditControllerExAccessor;

typedef struct TextBaseControllerPeer TextBaseControllerPeer;
typedef struct GENERATED_ArkUITextBaseControllerAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    void (*setSelection)(TextBaseControllerPeer* peer, const Ark_Number* selectionStart, const Ark_Number* selectionEnd, const Opt_SelectionOptions* options);
    void (*closeSelectionMenu)(TextBaseControllerPeer* peer);
    Ark_NativePointer (*getLayoutManager)(TextBaseControllerPeer* peer);
} GENERATED_ArkUITextBaseControllerAccessor;

typedef struct LayoutManagerPeer LayoutManagerPeer;
typedef struct GENERATED_ArkUILayoutManagerAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    Ark_Int32 (*getLineCount)(LayoutManagerPeer* peer);
    Ark_NativePointer (*getGlyphPositionAtCoordinate)(LayoutManagerPeer* peer, const Ark_Number* x, const Ark_Number* y);
    Ark_NativePointer (*getLineMetrics)(LayoutManagerPeer* peer, const Ark_Number* lineNumber);
} GENERATED_ArkUILayoutManagerAccessor;

typedef struct StyledStringPeer StyledStringPeer;
typedef struct GENERATED_ArkUIStyledStringAccessor {
    Ark_NativePointer (*ctor)(const Union_Ark_String_ImageAttachment_CustomSpan* value, const Opt_Array_StyleOptions* styles);
    Ark_NativePointer (*getFinalizer)();
    void (*getString)(StyledStringPeer* peer);
    Ark_NativePointer (*getStyles)(StyledStringPeer* peer, const Ark_Number* start, const Ark_Number* length, const Opt_Ark_StyledStringKey* styledKey);
    Ark_Boolean (*equals)(StyledStringPeer* peer, const Ark_Materialized* other);
    Ark_NativePointer (*subStyledString)(StyledStringPeer* peer, const Ark_Number* start, const Opt_Ark_Number* length);
} GENERATED_ArkUIStyledStringAccessor;

typedef struct CustomSpanPeer CustomSpanPeer;
typedef struct GENERATED_ArkUICustomSpanAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    Ark_NativePointer (*onMeasure)(CustomSpanPeer* peer, const CustomSpanMeasureInfo* measureInfo);
    void (*onDraw)(CustomSpanPeer* peer, const Ark_CustomObject* context, const CustomSpanDrawInfo* drawInfo);
} GENERATED_ArkUICustomSpanAccessor;

typedef struct RichEditorStyledStringControllerPeer RichEditorStyledStringControllerPeer;
typedef struct GENERATED_ArkUIRichEditorStyledStringControllerAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    void (*setStyledString)(RichEditorStyledStringControllerPeer* peer, const Ark_Materialized* styledString);
    Ark_NativePointer (*getStyledString)(RichEditorStyledStringControllerPeer* peer);
    Ark_NativePointer (*getSelection)(RichEditorStyledStringControllerPeer* peer);
    void (*onContentChanged)(RichEditorStyledStringControllerPeer* peer, const StyledStringChangedListener* listener);
} GENERATED_ArkUIRichEditorStyledStringControllerAccessor;

typedef struct StyledStringControllerPeer StyledStringControllerPeer;
typedef struct GENERATED_ArkUIStyledStringControllerAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    void (*setStyledString)(StyledStringControllerPeer* peer, const Ark_Materialized* styledString);
    Ark_NativePointer (*getStyledString)(StyledStringControllerPeer* peer);
} GENERATED_ArkUIStyledStringControllerAccessor;

typedef struct MutableStyledStringPeer MutableStyledStringPeer;
typedef struct GENERATED_ArkUIMutableStyledStringAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    void (*replaceString)(MutableStyledStringPeer* peer, const Ark_Number* start, const Ark_Number* length, const Ark_String* other);
    void (*insertString)(MutableStyledStringPeer* peer, const Ark_Number* start, const Ark_String* other);
    void (*removeString)(MutableStyledStringPeer* peer, const Ark_Number* start, const Ark_Number* length);
    void (*replaceStyle)(MutableStyledStringPeer* peer, const SpanStyle* spanStyle);
    void (*setStyle)(MutableStyledStringPeer* peer, const SpanStyle* spanStyle);
    void (*removeStyle)(MutableStyledStringPeer* peer, const Ark_Number* start, const Ark_Number* length, Ark_Int32 styledKey);
    void (*removeStyles)(MutableStyledStringPeer* peer, const Ark_Number* start, const Ark_Number* length);
    void (*clearStyles)(MutableStyledStringPeer* peer);
    void (*replaceStyledString)(MutableStyledStringPeer* peer, const Ark_Number* start, const Ark_Number* length, const Ark_Materialized* other);
    void (*insertStyledString)(MutableStyledStringPeer* peer, const Ark_Number* start, const Ark_Materialized* other);
    void (*appendStyledString)(MutableStyledStringPeer* peer, const Ark_Materialized* other);
} GENERATED_ArkUIMutableStyledStringAccessor;

typedef struct SearchControllerPeer SearchControllerPeer;
typedef struct GENERATED_ArkUISearchControllerAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    void (*caretPosition)(SearchControllerPeer* peer, const Ark_Number* value);
    void (*stopEditing)(SearchControllerPeer* peer);
    void (*setTextSelection)(SearchControllerPeer* peer, const Ark_Number* selectionStart, const Ark_Number* selectionEnd, const Opt_SelectionOptions* options);
} GENERATED_ArkUISearchControllerAccessor;

typedef struct TextContentControllerBasePeer TextContentControllerBasePeer;
typedef struct GENERATED_ArkUITextContentControllerBaseAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    Ark_NativePointer (*getCaretOffset)(TextContentControllerBasePeer* peer);
    Ark_NativePointer (*getTextContentRect)(TextContentControllerBasePeer* peer);
    Ark_Int32 (*getTextContentLineCount)(TextContentControllerBasePeer* peer);
} GENERATED_ArkUITextContentControllerBaseAccessor;

typedef struct SwiperContentTransitionProxyPeer SwiperContentTransitionProxyPeer;
typedef struct GENERATED_ArkUISwiperContentTransitionProxyAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    void (*finishTransition)(SwiperContentTransitionProxyPeer* peer);
} GENERATED_ArkUISwiperContentTransitionProxyAccessor;

typedef struct SwiperControllerPeer SwiperControllerPeer;
typedef struct GENERATED_ArkUISwiperControllerAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    void (*showNext)(SwiperControllerPeer* peer);
    void (*showPrevious)(SwiperControllerPeer* peer);
    void (*changeIndex)(SwiperControllerPeer* peer, const Ark_Number* index, const Opt_Ark_Boolean* useAnimation);
    void (*finishAnimation)(SwiperControllerPeer* peer, const Opt_Ark_Function* callback);
} GENERATED_ArkUISwiperControllerAccessor;

typedef struct TabContentTransitionProxyPeer TabContentTransitionProxyPeer;
typedef struct GENERATED_ArkUITabContentTransitionProxyAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    void (*finishTransition)(TabContentTransitionProxyPeer* peer);
} GENERATED_ArkUITabContentTransitionProxyAccessor;

typedef struct TabsControllerPeer TabsControllerPeer;
typedef struct GENERATED_ArkUITabsControllerAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    void (*changeIndex)(TabsControllerPeer* peer, const Ark_Number* value);
    Ark_NativePointer (*preloadItems)(TabsControllerPeer* peer, const Opt_Array_Ark_Number* indices);
} GENERATED_ArkUITabsControllerAccessor;

typedef struct TextControllerPeer TextControllerPeer;
typedef struct GENERATED_ArkUITextControllerAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    void (*closeSelectionMenu)(TextControllerPeer* peer);
    void (*setStyledString)(TextControllerPeer* peer, const Ark_Materialized* value);
    Ark_NativePointer (*getLayoutManager)(TextControllerPeer* peer);
} GENERATED_ArkUITextControllerAccessor;

typedef struct TextAreaControllerPeer TextAreaControllerPeer;
typedef struct GENERATED_ArkUITextAreaControllerAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    void (*caretPosition)(TextAreaControllerPeer* peer, const Ark_Number* value);
    void (*setTextSelection)(TextAreaControllerPeer* peer, const Ark_Number* selectionStart, const Ark_Number* selectionEnd, const Opt_SelectionOptions* options);
    void (*stopEditing)(TextAreaControllerPeer* peer);
} GENERATED_ArkUITextAreaControllerAccessor;

typedef struct TextClockControllerPeer TextClockControllerPeer;
typedef struct GENERATED_ArkUITextClockControllerAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    void (*start)(TextClockControllerPeer* peer);
    void (*stop)(TextClockControllerPeer* peer);
} GENERATED_ArkUITextClockControllerAccessor;

typedef struct TextInputControllerPeer TextInputControllerPeer;
typedef struct GENERATED_ArkUITextInputControllerAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    void (*caretPosition)(TextInputControllerPeer* peer, const Ark_Number* value);
    void (*setTextSelection)(TextInputControllerPeer* peer, const Ark_Number* selectionStart, const Ark_Number* selectionEnd, const Opt_SelectionOptions* options);
    void (*stopEditing)(TextInputControllerPeer* peer);
} GENERATED_ArkUITextInputControllerAccessor;

typedef struct TextTimerControllerPeer TextTimerControllerPeer;
typedef struct GENERATED_ArkUITextTimerControllerAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    void (*start)(TextTimerControllerPeer* peer);
    void (*pause)(TextTimerControllerPeer* peer);
    void (*reset)(TextTimerControllerPeer* peer);
} GENERATED_ArkUITextTimerControllerAccessor;

typedef struct VideoControllerPeer VideoControllerPeer;
typedef struct GENERATED_ArkUIVideoControllerAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    void (*start)(VideoControllerPeer* peer);
    void (*pause)(VideoControllerPeer* peer);
    void (*stop)(VideoControllerPeer* peer);
    void (*setCurrentTime_number)(VideoControllerPeer* peer, const Ark_Number* value);
    void (*requestFullscreen)(VideoControllerPeer* peer, Ark_Boolean value);
    void (*exitFullscreen)(VideoControllerPeer* peer);
    void (*setCurrentTime_number_SeekMode)(VideoControllerPeer* peer, const Ark_Number* value, Ark_Int32 seekMode);
    void (*reset)(VideoControllerPeer* peer);
} GENERATED_ArkUIVideoControllerAccessor;

typedef struct WebControllerPeer WebControllerPeer;
typedef struct GENERATED_ArkUIWebControllerAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    void (*onInactive)(WebControllerPeer* peer);
    void (*onActive)(WebControllerPeer* peer);
    void (*zoom)(WebControllerPeer* peer, const Ark_Number* factor);
    void (*clearHistory)(WebControllerPeer* peer);
    void (*runJavaScript)(WebControllerPeer* peer, const Literal_script_Ark_String_callback_Opt_Ark_Function* options);
    void (*loadData)(WebControllerPeer* peer, const Literal_data_Ark_String_mimeType_Ark_String_encoding_Ark_String_baseUrl_Opt_Ark_String_historyUrl_Opt_Ark_String* options);
    void (*loadUrl)(WebControllerPeer* peer, const Literal_url_Union_Ark_String_Ark_Resource_headers_Opt_Array_Header* options);
    void (*refresh)(WebControllerPeer* peer);
    void (*stop)(WebControllerPeer* peer);
    void (*registerJavaScriptProxy)(WebControllerPeer* peer, const Literal_object_Ark_CustomObject_name_Ark_String_methodList_Array_Ark_String* options);
    void (*deleteJavaScriptRegister)(WebControllerPeer* peer, const Ark_String* name);
    Ark_NativePointer (*getHitTest)(WebControllerPeer* peer);
    void (*requestFocus)(WebControllerPeer* peer);
    Ark_Boolean (*accessBackward)(WebControllerPeer* peer);
    Ark_Boolean (*accessForward)(WebControllerPeer* peer);
    Ark_Boolean (*accessStep)(WebControllerPeer* peer, const Ark_Number* step);
    void (*backward)(WebControllerPeer* peer);
    void (*forward)(WebControllerPeer* peer);
    Ark_NativePointer (*getCookieManager)(WebControllerPeer* peer);
} GENERATED_ArkUIWebControllerAccessor;

typedef struct WebCookiePeer WebCookiePeer;
typedef struct GENERATED_ArkUIWebCookieAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    void (*setCookie)(WebCookiePeer* peer);
    void (*saveCookie)(WebCookiePeer* peer);
} GENERATED_ArkUIWebCookieAccessor;

typedef struct JsGeolocationPeer JsGeolocationPeer;
typedef struct GENERATED_ArkUIJsGeolocationAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    void (*invoke)(JsGeolocationPeer* peer, const Ark_String* origin, Ark_Boolean allow, Ark_Boolean retain);
} GENERATED_ArkUIJsGeolocationAccessor;

typedef struct JsResultPeer JsResultPeer;
typedef struct GENERATED_ArkUIJsResultAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    void (*handleCancel)(JsResultPeer* peer);
    void (*handleConfirm)(JsResultPeer* peer);
    void (*handlePromptConfirm)(JsResultPeer* peer, const Ark_String* result);
} GENERATED_ArkUIJsResultAccessor;

typedef struct ConsoleMessagePeer ConsoleMessagePeer;
typedef struct GENERATED_ArkUIConsoleMessageAccessor {
    Ark_NativePointer (*ctor)(const Ark_String* message, const Ark_String* sourceId, const Ark_Number* lineNumber, Ark_Int32 messageLevel);
    Ark_NativePointer (*getFinalizer)();
    void (*getMessage)(ConsoleMessagePeer* peer);
    void (*getSourceId)(ConsoleMessagePeer* peer);
    Ark_Int32 (*getLineNumber)(ConsoleMessagePeer* peer);
    Ark_NativePointer (*getMessageLevel)(ConsoleMessagePeer* peer);
} GENERATED_ArkUIConsoleMessageAccessor;

typedef struct WebResourceRequestPeer WebResourceRequestPeer;
typedef struct GENERATED_ArkUIWebResourceRequestAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    Ark_NativePointer (*getRequestHeader)(WebResourceRequestPeer* peer);
    void (*getRequestUrl)(WebResourceRequestPeer* peer);
    Ark_Boolean (*isRequestGesture)(WebResourceRequestPeer* peer);
    Ark_Boolean (*isMainFrame)(WebResourceRequestPeer* peer);
    Ark_Boolean (*isRedirect)(WebResourceRequestPeer* peer);
    void (*getRequestMethod)(WebResourceRequestPeer* peer);
} GENERATED_ArkUIWebResourceRequestAccessor;

typedef struct WebResourceErrorPeer WebResourceErrorPeer;
typedef struct GENERATED_ArkUIWebResourceErrorAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    void (*getErrorInfo)(WebResourceErrorPeer* peer);
    Ark_Int32 (*getErrorCode)(WebResourceErrorPeer* peer);
} GENERATED_ArkUIWebResourceErrorAccessor;

typedef struct WebResourceResponsePeer WebResourceResponsePeer;
typedef struct GENERATED_ArkUIWebResourceResponseAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    void (*getResponseData)(WebResourceResponsePeer* peer);
    void (*getResponseEncoding)(WebResourceResponsePeer* peer);
    void (*getResponseMimeType)(WebResourceResponsePeer* peer);
    void (*getReasonMessage)(WebResourceResponsePeer* peer);
    Ark_NativePointer (*getResponseHeader)(WebResourceResponsePeer* peer);
    Ark_Int32 (*getResponseCode)(WebResourceResponsePeer* peer);
    void (*setResponseData)(WebResourceResponsePeer* peer, const Union_Ark_String_Ark_Number_Ark_Resource_ArrayBuffer* data);
    void (*setResponseEncoding)(WebResourceResponsePeer* peer, const Ark_String* encoding);
    void (*setResponseMimeType)(WebResourceResponsePeer* peer, const Ark_String* mimeType);
    void (*setReasonMessage)(WebResourceResponsePeer* peer, const Ark_String* reason);
    void (*setResponseHeader)(WebResourceResponsePeer* peer, const Array_Header* header);
    void (*setResponseCode)(WebResourceResponsePeer* peer, const Ark_Number* code);
    void (*setResponseIsReady)(WebResourceResponsePeer* peer, Ark_Boolean IsReady);
} GENERATED_ArkUIWebResourceResponseAccessor;

typedef struct FileSelectorResultPeer FileSelectorResultPeer;
typedef struct GENERATED_ArkUIFileSelectorResultAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    void (*handleFileList)(FileSelectorResultPeer* peer, const Array_Ark_String* fileList);
} GENERATED_ArkUIFileSelectorResultAccessor;

typedef struct FileSelectorParamPeer FileSelectorParamPeer;
typedef struct GENERATED_ArkUIFileSelectorParamAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    void (*getTitle)(FileSelectorParamPeer* peer);
    Ark_NativePointer (*getMode)(FileSelectorParamPeer* peer);
    Ark_NativePointer (*getAcceptType)(FileSelectorParamPeer* peer);
    Ark_Boolean (*isCapture)(FileSelectorParamPeer* peer);
} GENERATED_ArkUIFileSelectorParamAccessor;

typedef struct FullScreenExitHandlerPeer FullScreenExitHandlerPeer;
typedef struct GENERATED_ArkUIFullScreenExitHandlerAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    void (*exitFullScreen)(FullScreenExitHandlerPeer* peer);
} GENERATED_ArkUIFullScreenExitHandlerAccessor;

typedef struct HttpAuthHandlerPeer HttpAuthHandlerPeer;
typedef struct GENERATED_ArkUIHttpAuthHandlerAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    Ark_Boolean (*confirm)(HttpAuthHandlerPeer* peer, const Ark_String* userName, const Ark_String* password);
    void (*cancel)(HttpAuthHandlerPeer* peer);
    Ark_Boolean (*isHttpAuthInfoSaved)(HttpAuthHandlerPeer* peer);
} GENERATED_ArkUIHttpAuthHandlerAccessor;

typedef struct PermissionRequestPeer PermissionRequestPeer;
typedef struct GENERATED_ArkUIPermissionRequestAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    void (*deny)(PermissionRequestPeer* peer);
    void (*getOrigin)(PermissionRequestPeer* peer);
    Ark_NativePointer (*getAccessibleResource)(PermissionRequestPeer* peer);
    void (*grant)(PermissionRequestPeer* peer, const Array_Ark_String* resources);
} GENERATED_ArkUIPermissionRequestAccessor;

typedef struct ScreenCaptureHandlerPeer ScreenCaptureHandlerPeer;
typedef struct GENERATED_ArkUIScreenCaptureHandlerAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    void (*getOrigin)(ScreenCaptureHandlerPeer* peer);
    void (*grant)(ScreenCaptureHandlerPeer* peer, const ScreenCaptureConfig* config);
    void (*deny)(ScreenCaptureHandlerPeer* peer);
} GENERATED_ArkUIScreenCaptureHandlerAccessor;

typedef struct WebContextMenuParamPeer WebContextMenuParamPeer;
typedef struct GENERATED_ArkUIWebContextMenuParamAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    Ark_Int32 (*x)(WebContextMenuParamPeer* peer);
    Ark_Int32 (*y)(WebContextMenuParamPeer* peer);
    void (*getLinkUrl)(WebContextMenuParamPeer* peer);
    void (*getUnfilteredLinkUrl)(WebContextMenuParamPeer* peer);
    void (*getSourceUrl)(WebContextMenuParamPeer* peer);
    Ark_Boolean (*existsImageContents)(WebContextMenuParamPeer* peer);
    Ark_NativePointer (*getMediaType)(WebContextMenuParamPeer* peer);
    void (*getSelectionText)(WebContextMenuParamPeer* peer);
    Ark_NativePointer (*getSourceType)(WebContextMenuParamPeer* peer);
    Ark_NativePointer (*getInputFieldType)(WebContextMenuParamPeer* peer);
    Ark_Boolean (*isEditable)(WebContextMenuParamPeer* peer);
    Ark_Int32 (*getEditStateFlags)(WebContextMenuParamPeer* peer);
} GENERATED_ArkUIWebContextMenuParamAccessor;

typedef struct WebContextMenuResultPeer WebContextMenuResultPeer;
typedef struct GENERATED_ArkUIWebContextMenuResultAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    void (*closeContextMenu)(WebContextMenuResultPeer* peer);
    void (*copyImage)(WebContextMenuResultPeer* peer);
    void (*copy)(WebContextMenuResultPeer* peer);
    void (*paste)(WebContextMenuResultPeer* peer);
    void (*cut)(WebContextMenuResultPeer* peer);
    void (*selectAll)(WebContextMenuResultPeer* peer);
} GENERATED_ArkUIWebContextMenuResultAccessor;

typedef struct SslErrorHandlerPeer SslErrorHandlerPeer;
typedef struct GENERATED_ArkUISslErrorHandlerAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    void (*handleConfirm)(SslErrorHandlerPeer* peer);
    void (*handleCancel)(SslErrorHandlerPeer* peer);
} GENERATED_ArkUISslErrorHandlerAccessor;

typedef struct ClientAuthenticationHandlerPeer ClientAuthenticationHandlerPeer;
typedef struct GENERATED_ArkUIClientAuthenticationHandlerAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    void (*confirm_string_string)(ClientAuthenticationHandlerPeer* peer, const Ark_String* priKeyFile, const Ark_String* certChainFile);
    void (*confirm_string)(ClientAuthenticationHandlerPeer* peer, const Ark_String* authUri);
    void (*cancel)(ClientAuthenticationHandlerPeer* peer);
    void (*ignore)(ClientAuthenticationHandlerPeer* peer);
} GENERATED_ArkUIClientAuthenticationHandlerAccessor;

typedef struct ControllerHandlerPeer ControllerHandlerPeer;
typedef struct GENERATED_ArkUIControllerHandlerAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    void (*setWebController)(ControllerHandlerPeer* peer, const Ark_CustomObject* controller);
} GENERATED_ArkUIControllerHandlerAccessor;

typedef struct DataResubmissionHandlerPeer DataResubmissionHandlerPeer;
typedef struct GENERATED_ArkUIDataResubmissionHandlerAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    void (*resend)(DataResubmissionHandlerPeer* peer);
    void (*cancel)(DataResubmissionHandlerPeer* peer);
} GENERATED_ArkUIDataResubmissionHandlerAccessor;

typedef struct EventResultPeer EventResultPeer;
typedef struct GENERATED_ArkUIEventResultAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    void (*setGestureEventResult)(EventResultPeer* peer, Ark_Boolean result);
} GENERATED_ArkUIEventResultAccessor;

typedef struct WebKeyboardControllerPeer WebKeyboardControllerPeer;
typedef struct GENERATED_ArkUIWebKeyboardControllerAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    void (*insertText)(WebKeyboardControllerPeer* peer, const Ark_String* text);
    void (*deleteForward)(WebKeyboardControllerPeer* peer, const Ark_Number* length);
    void (*deleteBackward)(WebKeyboardControllerPeer* peer, const Ark_Number* length);
    void (*sendFunctionKey)(WebKeyboardControllerPeer* peer, const Ark_Number* key);
    void (*close)(WebKeyboardControllerPeer* peer);
} GENERATED_ArkUIWebKeyboardControllerAccessor;

typedef struct XComponentControllerPeer XComponentControllerPeer;
typedef struct GENERATED_ArkUIXComponentControllerAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    void (*getXComponentSurfaceId)(XComponentControllerPeer* peer);
    Ark_NativePointer (*getXComponentContext)(XComponentControllerPeer* peer);
    void (*setXComponentSurfaceSize)(XComponentControllerPeer* peer, const Literal_surfaceWidth_Ark_Number_surfaceHeight_Ark_Number* value);
    void (*setXComponentSurfaceRect)(XComponentControllerPeer* peer, const SurfaceRect* rect);
    Ark_NativePointer (*getXComponentSurfaceRect)(XComponentControllerPeer* peer);
    void (*setXComponentSurfaceRotation)(XComponentControllerPeer* peer, const SurfaceRotationOptions* rotationOptions);
    Ark_NativePointer (*getXComponentSurfaceRotation)(XComponentControllerPeer* peer);
    void (*onSurfaceCreated)(XComponentControllerPeer* peer, const Ark_String* surfaceId);
    void (*onSurfaceChanged)(XComponentControllerPeer* peer, const Ark_String* surfaceId, const SurfaceRect* rect);
    void (*onSurfaceDestroyed)(XComponentControllerPeer* peer, const Ark_String* surfaceId);
    Ark_NativePointer (*startImageAnalyzer)(XComponentControllerPeer* peer, const ImageAnalyzerConfig* config);
    void (*stopImageAnalyzer)(XComponentControllerPeer* peer);
} GENERATED_ArkUIXComponentControllerAccessor;

typedef struct WaterFlowSectionsPeer WaterFlowSectionsPeer;
typedef struct GENERATED_ArkUIWaterFlowSectionsAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    Ark_Boolean (*splice)(WaterFlowSectionsPeer* peer, const Ark_Number* start, const Opt_Ark_Number* deleteCount, const Opt_Array_SectionOptions* sections);
    Ark_Boolean (*push)(WaterFlowSectionsPeer* peer, const SectionOptions* section);
    Ark_Boolean (*update)(WaterFlowSectionsPeer* peer, const Ark_Number* sectionIndex, const SectionOptions* section);
    Ark_NativePointer (*values)(WaterFlowSectionsPeer* peer);
    Ark_Int32 (*length)(WaterFlowSectionsPeer* peer);
} GENERATED_ArkUIWaterFlowSectionsAccessor;

typedef struct LinearIndicatorControllerPeer LinearIndicatorControllerPeer;
typedef struct GENERATED_ArkUILinearIndicatorControllerAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    void (*setProgress)(LinearIndicatorControllerPeer* peer, const Ark_Number* index, const Ark_Number* progress);
    void (*start)(LinearIndicatorControllerPeer* peer, const Opt_LinearIndicatorStartOptions* options);
    void (*pause)(LinearIndicatorControllerPeer* peer);
    void (*stop)(LinearIndicatorControllerPeer* peer);
} GENERATED_ArkUILinearIndicatorControllerAccessor;

typedef struct GENERATED_ArkUIAbilityComponentEventsReceiver {
    void (*onConnect)(Ark_Int32 nodeId);
    void (*onDisconnect)(Ark_Int32 nodeId);
} GENERATED_ArkUIAbilityComponentEventsReceiver;

typedef struct GENERATED_ArkUIAlphabetIndexerEventsReceiver {
    void (*onSelected)(Ark_Int32 nodeId, const Ark_Number index);
    void (*onSelect)(Ark_Int32 nodeId, const Ark_Number index);
    void (*onRequestPopupData)(Ark_Int32 nodeId, const Ark_Number index);
    void (*onPopupSelect)(Ark_Int32 nodeId, const Ark_Number index);
} GENERATED_ArkUIAlphabetIndexerEventsReceiver;

typedef struct GENERATED_ArkUIAnimatorEventsReceiver {
    void (*onStart)(Ark_Int32 nodeId);
    void (*onPause)(Ark_Int32 nodeId);
    void (*onRepeat)(Ark_Int32 nodeId);
    void (*onCancel)(Ark_Int32 nodeId);
    void (*onFinish)(Ark_Int32 nodeId);
    void (*onFrame)(Ark_Int32 nodeId, const Ark_Number value);
} GENERATED_ArkUIAnimatorEventsReceiver;

typedef struct GENERATED_ArkUICalendarEventsReceiver {
    void (*onSelectChange)(Ark_Int32 nodeId, const CalendarSelectedDate event);
    void (*onRequestData)(Ark_Int32 nodeId, const CalendarRequestedData event);
} GENERATED_ArkUICalendarEventsReceiver;

typedef struct GENERATED_ArkUICalendarPickerEventsReceiver {
    void (*onChange)(Ark_Int32 nodeId, const Ark_CustomObject value);
} GENERATED_ArkUICalendarPickerEventsReceiver;

typedef struct GENERATED_ArkUICanvasEventsReceiver {
    void (*onReady)(Ark_Int32 nodeId);
} GENERATED_ArkUICanvasEventsReceiver;

typedef struct GENERATED_ArkUICheckboxEventsReceiver {
    void (*onChange)(Ark_Int32 nodeId, const Ark_Boolean value);
} GENERATED_ArkUICheckboxEventsReceiver;

typedef struct GENERATED_ArkUICheckboxGroupEventsReceiver {
    void (*onChange)(Ark_Int32 nodeId, const CheckboxGroupResult event);
} GENERATED_ArkUICheckboxGroupEventsReceiver;

typedef struct GENERATED_ArkUICommonMethodEventsReceiver {
    void (*onChildTouchTest)(Ark_Int32 nodeId, const Array_TouchTestInfo value);
    void (*onClick)(Ark_Int32 nodeId, const ClickEvent event);
    void (*onHover)(Ark_Int32 nodeId, const Ark_Boolean isHover, const HoverEvent event);
    void (*onMouse)(Ark_Int32 nodeId, const MouseEvent event);
    void (*onTouch)(Ark_Int32 nodeId, const TouchEvent event);
    void (*onKeyEvent)(Ark_Int32 nodeId, const KeyEvent event);
    void (*onKeyPreIme)(Ark_Int32 nodeId, const KeyEvent data);
    void (*onFocus)(Ark_Int32 nodeId);
    void (*onBlur)(Ark_Int32 nodeId);
    void (*onAppear)(Ark_Int32 nodeId);
    void (*onDisAppear)(Ark_Int32 nodeId);
    void (*onAttach)(Ark_Int32 nodeId);
    void (*onDetach)(Ark_Int32 nodeId);
    void (*onAreaChange)(Ark_Int32 nodeId, const Area oldValue, const Area newValue);
    void (*onDragStart)(Ark_Int32 nodeId, const DragEvent event, const Opt_Ark_String extraParams);
    void (*onDragEnter)(Ark_Int32 nodeId, const DragEvent event, const Opt_Ark_String extraParams);
    void (*onDragMove)(Ark_Int32 nodeId, const DragEvent event, const Opt_Ark_String extraParams);
    void (*onDragLeave)(Ark_Int32 nodeId, const DragEvent event, const Opt_Ark_String extraParams);
    void (*onDrop)(Ark_Int32 nodeId, const DragEvent event, const Opt_Ark_String extraParams);
    void (*onDragEnd)(Ark_Int32 nodeId, const DragEvent event, const Opt_Ark_String extraParams);
    void (*onPreDrag)(Ark_Int32 nodeId, const Ark_Int32 data);
    void (*onVisibleAreaChange)(Ark_Int32 nodeId, const Ark_Boolean isVisible, const Ark_Number currentRatio);
    void (*keyboardShortcut)(Ark_Int32 nodeId);
    void (*onGestureJudgeBegin)(Ark_Int32 nodeId, const GestureInfo gestureInfo, const BaseGestureEvent event);
    void (*onGestureRecognizerJudgeBegin)(Ark_Int32 nodeId, const BaseGestureEvent event, const Ark_Materialized current, const Array_GestureRecognizer recognizers);
    void (*shouldBuiltInRecognizerParallelWith)(Ark_Int32 nodeId, const Ark_Materialized current, const Array_GestureRecognizer others);
    void (*onTouchIntercept)(Ark_Int32 nodeId, const TouchEvent data);
    void (*onSizeChange)(Ark_Int32 nodeId, const SizeOptions oldValue, const SizeOptions newValue);
} GENERATED_ArkUICommonMethodEventsReceiver;

typedef struct GENERATED_ArkUIScrollableCommonMethodEventsReceiver {
    void (*onScroll)(Ark_Int32 nodeId, const Ark_Number scrollOffset, const Ark_Int32 scrollState);
    void (*onDidScroll)(Ark_Int32 nodeId, const Ark_Number scrollOffset, const Ark_Int32 scrollState);
    void (*onReachStart)(Ark_Int32 nodeId);
    void (*onReachEnd)(Ark_Int32 nodeId);
    void (*onScrollStart)(Ark_Int32 nodeId);
    void (*onScrollStop)(Ark_Int32 nodeId);
} GENERATED_ArkUIScrollableCommonMethodEventsReceiver;

typedef struct GENERATED_ArkUICounterEventsReceiver {
    void (*onInc)(Ark_Int32 nodeId);
    void (*onDec)(Ark_Int32 nodeId);
} GENERATED_ArkUICounterEventsReceiver;

typedef struct GENERATED_ArkUIDatePickerEventsReceiver {
    void (*onChange)(Ark_Int32 nodeId, const DatePickerResult value);
    void (*onDateChange)(Ark_Int32 nodeId, const Ark_CustomObject value);
} GENERATED_ArkUIDatePickerEventsReceiver;

typedef struct GENERATED_ArkUIFolderStackEventsReceiver {
    void (*onFolderStateChange)(Ark_Int32 nodeId, const Literal_foldStatus_Ark_FoldStatus event);
    void (*onHoverStatusChange)(Ark_Int32 nodeId, const HoverEventParam param);
} GENERATED_ArkUIFolderStackEventsReceiver;

typedef struct GENERATED_ArkUIFormComponentEventsReceiver {
    void (*onAcquired)(Ark_Int32 nodeId, const FormCallbackInfo data);
    void (*onError)(Ark_Int32 nodeId, const Literal_errcode_Ark_Number_msg_Ark_String info);
    void (*onRouter)(Ark_Int32 nodeId, const Ark_CustomObject info);
    void (*onUninstall)(Ark_Int32 nodeId, const FormCallbackInfo data);
    void (*onLoad)(Ark_Int32 nodeId);
} GENERATED_ArkUIFormComponentEventsReceiver;

typedef struct GENERATED_ArkUIGridEventsReceiver {
    void (*onScrollBarUpdate)(Ark_Int32 nodeId, const Ark_Number index, const Ark_Number offset);
    void (*onScrollIndex)(Ark_Int32 nodeId, const Ark_Number first, const Ark_Number last);
    void (*onItemDragStart)(Ark_Int32 nodeId, const ItemDragInfo event, const Ark_Number itemIndex);
    void (*onItemDragEnter)(Ark_Int32 nodeId, const ItemDragInfo event);
    void (*onItemDragMove)(Ark_Int32 nodeId, const ItemDragInfo event, const Ark_Number itemIndex, const Ark_Number insertIndex);
    void (*onItemDragLeave)(Ark_Int32 nodeId, const ItemDragInfo event, const Ark_Number itemIndex);
    void (*onItemDrop)(Ark_Int32 nodeId, const ItemDragInfo event, const Ark_Number itemIndex, const Ark_Number insertIndex, const Ark_Boolean isSuccess);
    void (*onScroll)(Ark_Int32 nodeId, const Ark_Number scrollOffset, const Ark_Int32 scrollState);
    void (*onReachStart)(Ark_Int32 nodeId);
    void (*onReachEnd)(Ark_Int32 nodeId);
    void (*onScrollStart)(Ark_Int32 nodeId);
    void (*onScrollStop)(Ark_Int32 nodeId);
    void (*onScrollFrameBegin)(Ark_Int32 nodeId, const Ark_Number offset, const Ark_Int32 state);
} GENERATED_ArkUIGridEventsReceiver;

typedef struct GENERATED_ArkUIGridItemEventsReceiver {
    void (*onSelect)(Ark_Int32 nodeId, const Ark_Boolean isSelected);
} GENERATED_ArkUIGridItemEventsReceiver;

typedef struct GENERATED_ArkUIGridRowEventsReceiver {
    void (*onBreakpointChange)(Ark_Int32 nodeId, const Ark_String breakpoints);
} GENERATED_ArkUIGridRowEventsReceiver;

typedef struct GENERATED_ArkUIImageEventsReceiver {
    void (*onComplete)(Ark_Int32 nodeId, const Opt_Literal_width_Ark_Number_height_Ark_Number_componentWidth_Ark_Number_componentHeight_Ark_Number_loadingStatus_Ark_Number_contentWidth_Ark_Number_contentHeight_Ark_Number_contentOffsetX_Ark_Number_contentOffsetY_Ark_Number event);
    void (*onError)(Ark_Int32 nodeId, const ImageError error);
    void (*onFinish)(Ark_Int32 nodeId);
} GENERATED_ArkUIImageEventsReceiver;

typedef struct GENERATED_ArkUIImageAnimatorEventsReceiver {
    void (*onStart)(Ark_Int32 nodeId);
    void (*onPause)(Ark_Int32 nodeId);
    void (*onRepeat)(Ark_Int32 nodeId);
    void (*onCancel)(Ark_Int32 nodeId);
    void (*onFinish)(Ark_Int32 nodeId);
} GENERATED_ArkUIImageAnimatorEventsReceiver;

typedef struct GENERATED_ArkUIImageSpanEventsReceiver {
    void (*onComplete)(Ark_Int32 nodeId, const ImageLoadResult result);
    void (*onError)(Ark_Int32 nodeId, const ImageError error);
} GENERATED_ArkUIImageSpanEventsReceiver;

typedef struct GENERATED_ArkUIListEventsReceiver {
    void (*onScroll)(Ark_Int32 nodeId, const Ark_Number scrollOffset, const Ark_Int32 scrollState);
    void (*onScrollIndex)(Ark_Int32 nodeId, const Ark_Number start, const Ark_Number end, const Ark_Number center);
    void (*onScrollVisibleContentChange)(Ark_Int32 nodeId, const VisibleListContentInfo start, const VisibleListContentInfo end);
    void (*onReachStart)(Ark_Int32 nodeId);
    void (*onReachEnd)(Ark_Int32 nodeId);
    void (*onScrollStart)(Ark_Int32 nodeId);
    void (*onScrollStop)(Ark_Int32 nodeId);
    void (*onItemDelete)(Ark_Int32 nodeId, const Ark_Number index);
    void (*onItemMove)(Ark_Int32 nodeId, const Ark_Number from, const Ark_Number to);
    void (*onItemDragStart)(Ark_Int32 nodeId, const ItemDragInfo event, const Ark_Number itemIndex);
    void (*onItemDragEnter)(Ark_Int32 nodeId, const ItemDragInfo event);
    void (*onItemDragMove)(Ark_Int32 nodeId, const ItemDragInfo event, const Ark_Number itemIndex, const Ark_Number insertIndex);
    void (*onItemDragLeave)(Ark_Int32 nodeId, const ItemDragInfo event, const Ark_Number itemIndex);
    void (*onItemDrop)(Ark_Int32 nodeId, const ItemDragInfo event, const Ark_Number itemIndex, const Ark_Number insertIndex, const Ark_Boolean isSuccess);
    void (*onScrollFrameBegin)(Ark_Int32 nodeId, const Ark_Number offset, const Ark_Int32 state);
} GENERATED_ArkUIListEventsReceiver;

typedef struct GENERATED_ArkUIListItemEventsReceiver {
    void (*onSelect)(Ark_Int32 nodeId, const Ark_Boolean isSelected);
} GENERATED_ArkUIListItemEventsReceiver;

typedef struct GENERATED_ArkUILocationButtonEventsReceiver {
    void (*onClick)(Ark_Int32 nodeId, const ClickEvent event, const Ark_Int32 result);
} GENERATED_ArkUILocationButtonEventsReceiver;

typedef struct GENERATED_ArkUIMarqueeEventsReceiver {
    void (*onStart)(Ark_Int32 nodeId);
    void (*onBounce)(Ark_Int32 nodeId);
    void (*onFinish)(Ark_Int32 nodeId);
} GENERATED_ArkUIMarqueeEventsReceiver;

typedef struct GENERATED_ArkUIMenuItemEventsReceiver {
    void (*onChange)(Ark_Int32 nodeId, const Ark_Boolean selected);
} GENERATED_ArkUIMenuItemEventsReceiver;

typedef struct GENERATED_ArkUINavDestinationEventsReceiver {
    void (*onShown)(Ark_Int32 nodeId);
    void (*onHidden)(Ark_Int32 nodeId);
    void (*onBackPressed)(Ark_Int32 nodeId);
    void (*onWillAppear)(Ark_Int32 nodeId);
    void (*onWillDisappear)(Ark_Int32 nodeId);
    void (*onWillShow)(Ark_Int32 nodeId);
    void (*onWillHide)(Ark_Int32 nodeId);
} GENERATED_ArkUINavDestinationEventsReceiver;

typedef struct GENERATED_ArkUINavRouterEventsReceiver {
    void (*onStateChange)(Ark_Int32 nodeId, const Ark_Boolean isActivated);
} GENERATED_ArkUINavRouterEventsReceiver;

typedef struct GENERATED_ArkUINavigationEventsReceiver {
    void (*onTitleModeChange)(Ark_Int32 nodeId, const Ark_Int32 titleMode);
    void (*onNavBarStateChange)(Ark_Int32 nodeId, const Ark_Boolean isVisible);
    void (*onNavigationModeChange)(Ark_Int32 nodeId, const Ark_Int32 mode);
    void (*navDestination)(Ark_Int32 nodeId, const Ark_String name, const Ark_CustomObject param);
    void (*customNavContentTransition)(Ark_Int32 nodeId, const NavContentInfo from, const NavContentInfo to, const Ark_Int32 operation);
} GENERATED_ArkUINavigationEventsReceiver;

typedef struct GENERATED_ArkUIPanelEventsReceiver {
    void (*onChange)(Ark_Int32 nodeId, const Ark_Number width, const Ark_Number height, const Ark_Int32 mode);
    void (*onHeightChange)(Ark_Int32 nodeId, const Ark_Number value);
} GENERATED_ArkUIPanelEventsReceiver;

typedef struct GENERATED_ArkUIPasteButtonEventsReceiver {
    void (*onClick)(Ark_Int32 nodeId, const ClickEvent event, const Ark_Int32 result);
} GENERATED_ArkUIPasteButtonEventsReceiver;

typedef struct GENERATED_ArkUIPatternLockEventsReceiver {
    void (*onPatternComplete)(Ark_Int32 nodeId, const Array_Ark_Number input);
} GENERATED_ArkUIPatternLockEventsReceiver;

typedef struct GENERATED_ArkUIPluginComponentEventsReceiver {
    void (*onComplete)(Ark_Int32 nodeId);
    void (*onError)(Ark_Int32 nodeId, const Literal_errcode_Ark_Number_msg_Ark_String info);
} GENERATED_ArkUIPluginComponentEventsReceiver;

typedef struct GENERATED_ArkUIRadioEventsReceiver {
    void (*onChange)(Ark_Int32 nodeId, const Ark_Boolean isChecked);
} GENERATED_ArkUIRadioEventsReceiver;

typedef struct GENERATED_ArkUIRatingEventsReceiver {
    void (*onChange)(Ark_Int32 nodeId, const Ark_Number value);
} GENERATED_ArkUIRatingEventsReceiver;

typedef struct GENERATED_ArkUIRefreshEventsReceiver {
    void (*onStateChange)(Ark_Int32 nodeId, const Ark_Int32 state);
    void (*onRefreshing)(Ark_Int32 nodeId);
    void (*onOffsetChange)(Ark_Int32 nodeId, const Ark_Number data);
} GENERATED_ArkUIRefreshEventsReceiver;

typedef struct GENERATED_ArkUIRichEditorEventsReceiver {
    void (*onReady)(Ark_Int32 nodeId);
    void (*onSelect)(Ark_Int32 nodeId, const RichEditorSelection data);
    void (*onSelectionChange)(Ark_Int32 nodeId, const RichEditorRange data);
    void (*aboutToIMEInput)(Ark_Int32 nodeId, const RichEditorInsertValue data);
    void (*onIMEInputComplete)(Ark_Int32 nodeId, const RichEditorTextSpanResult data);
    void (*aboutToDelete)(Ark_Int32 nodeId, const RichEditorDeleteValue data);
    void (*onDeleteComplete)(Ark_Int32 nodeId);
    void (*onPaste)(Ark_Int32 nodeId, const Opt_PasteEvent event);
    void (*onEditingChange)(Ark_Int32 nodeId, const Ark_Boolean data);
    void (*onSubmit)(Ark_Int32 nodeId, const Ark_Int32 enterKey, const SubmitEvent event);
    void (*onWillChange)(Ark_Int32 nodeId, const RichEditorChangeValue data);
    void (*onDidChange)(Ark_Int32 nodeId, const TextRange rangeBefore, const TextRange rangeAfter);
    void (*onCut)(Ark_Int32 nodeId, const CutEvent data);
    void (*onCopy)(Ark_Int32 nodeId, const CopyEvent data);
} GENERATED_ArkUIRichEditorEventsReceiver;

typedef struct GENERATED_ArkUIRichTextEventsReceiver {
    void (*onStart)(Ark_Int32 nodeId);
    void (*onComplete)(Ark_Int32 nodeId);
} GENERATED_ArkUIRichTextEventsReceiver;

typedef struct GENERATED_ArkUISaveButtonEventsReceiver {
    void (*onClick)(Ark_Int32 nodeId, const ClickEvent event, const Ark_Int32 result);
} GENERATED_ArkUISaveButtonEventsReceiver;

typedef struct GENERATED_ArkUIScrollEventsReceiver {
    void (*onScroll)(Ark_Int32 nodeId, const Ark_Number xOffset, const Ark_Number yOffset);
    void (*onDidScroll)(Ark_Int32 nodeId, const Ark_Number xOffset, const Ark_Number yOffset, const Ark_Int32 scrollState);
    void (*onScrollEdge)(Ark_Int32 nodeId, const Ark_Int32 side);
    void (*onScrollStart)(Ark_Int32 nodeId);
    void (*onScrollEnd)(Ark_Int32 nodeId);
    void (*onScrollStop)(Ark_Int32 nodeId);
    void (*onScrollFrameBegin)(Ark_Int32 nodeId, const Ark_Number offset, const Ark_Int32 state);
} GENERATED_ArkUIScrollEventsReceiver;

typedef struct GENERATED_ArkUISearchEventsReceiver {
    void (*inputFilter)(Ark_Int32 nodeId, const Ark_String data);
    void (*onEditChange)(Ark_Int32 nodeId, const Ark_Boolean data);
    void (*onSubmit)(Ark_Int32 nodeId, const Ark_String value);
    void (*onChange)(Ark_Int32 nodeId, const Ark_String value, const Opt_TextRange previewRange);
    void (*onTextSelectionChange)(Ark_Int32 nodeId, const Ark_Number selectionStart, const Ark_Number selectionEnd);
    void (*onContentScroll)(Ark_Int32 nodeId, const Ark_Number totalOffsetX, const Ark_Number totalOffsetY);
    void (*onCopy)(Ark_Int32 nodeId, const Ark_String value);
    void (*onCut)(Ark_Int32 nodeId, const Ark_String value);
    void (*onPaste)(Ark_Int32 nodeId, const Ark_String value, const PasteEvent event);
    void (*onWillInsert)(Ark_Int32 nodeId, const InsertValue data);
    void (*onDidInsert)(Ark_Int32 nodeId, const InsertValue data);
    void (*onWillDelete)(Ark_Int32 nodeId, const DeleteValue data);
    void (*onDidDelete)(Ark_Int32 nodeId, const DeleteValue data);
} GENERATED_ArkUISearchEventsReceiver;

typedef struct GENERATED_ArkUISelectEventsReceiver {
    void (*onSelect)(Ark_Int32 nodeId, const Ark_Number index, const Ark_String value);
} GENERATED_ArkUISelectEventsReceiver;

typedef struct GENERATED_ArkUISliderEventsReceiver {
    void (*onChange)(Ark_Int32 nodeId, const Ark_Number value, const Ark_Int32 mode);
} GENERATED_ArkUISliderEventsReceiver;

typedef struct GENERATED_ArkUIStepperEventsReceiver {
    void (*onFinish)(Ark_Int32 nodeId);
    void (*onSkip)(Ark_Int32 nodeId);
    void (*onChange)(Ark_Int32 nodeId, const Ark_Number prevIndex, const Ark_Number index);
    void (*onNext)(Ark_Int32 nodeId, const Ark_Number index, const Ark_Number pendingIndex);
    void (*onPrevious)(Ark_Int32 nodeId, const Ark_Number index, const Ark_Number pendingIndex);
} GENERATED_ArkUIStepperEventsReceiver;

typedef struct GENERATED_ArkUISwiperEventsReceiver {
    void (*onChange)(Ark_Int32 nodeId, const Ark_Number index);
    void (*onAnimationStart)(Ark_Int32 nodeId, const Ark_Number index, const Ark_Number targetIndex, const SwiperAnimationEvent extraInfo);
    void (*onAnimationEnd)(Ark_Int32 nodeId, const Ark_Number index, const SwiperAnimationEvent extraInfo);
    void (*onGestureSwipe)(Ark_Int32 nodeId, const Ark_Number index, const SwiperAnimationEvent extraInfo);
    void (*onContentDidScroll)(Ark_Int32 nodeId, const Ark_Number selectedIndex, const Ark_Number index, const Ark_Number position, const Ark_Number mainAxisLength);
} GENERATED_ArkUISwiperEventsReceiver;

typedef struct GENERATED_ArkUITabsEventsReceiver {
    void (*onChange)(Ark_Int32 nodeId, const Ark_Number index);
    void (*onTabBarClick)(Ark_Int32 nodeId, const Ark_Number index);
    void (*onAnimationStart)(Ark_Int32 nodeId, const Ark_Number index, const Ark_Number targetIndex, const TabsAnimationEvent event);
    void (*onAnimationEnd)(Ark_Int32 nodeId, const Ark_Number index, const TabsAnimationEvent event);
    void (*onGestureSwipe)(Ark_Int32 nodeId, const Ark_Number index, const TabsAnimationEvent event);
    void (*customContentTransition)(Ark_Int32 nodeId, const Ark_Number from, const Ark_Number to);
    void (*onContentWillChange)(Ark_Int32 nodeId, const Ark_Number currentIndex, const Ark_Number comingIndex);
} GENERATED_ArkUITabsEventsReceiver;

typedef struct GENERATED_ArkUITabContentEventsReceiver {
    void (*onWillShow)(Ark_Int32 nodeId);
    void (*onWillHide)(Ark_Int32 nodeId);
} GENERATED_ArkUITabContentEventsReceiver;

typedef struct GENERATED_ArkUITextEventsReceiver {
    void (*onCopy)(Ark_Int32 nodeId, const Ark_String value);
    void (*onTextSelectionChange)(Ark_Int32 nodeId, const Ark_Number selectionStart, const Ark_Number selectionEnd);
    void (*onMarqueeStateChange)(Ark_Int32 nodeId, const Ark_Int32 data);
} GENERATED_ArkUITextEventsReceiver;

typedef struct GENERATED_ArkUITextAreaEventsReceiver {
    void (*inputFilter)(Ark_Int32 nodeId, const Ark_String value);
    void (*onSubmit)(Ark_Int32 nodeId, const Ark_Int32 enterKey);
    void (*onChange)(Ark_Int32 nodeId, const Ark_String value, const Opt_TextRange previewRange);
    void (*onTextSelectionChange)(Ark_Int32 nodeId, const Ark_Number selectionStart, const Ark_Number selectionEnd);
    void (*onContentScroll)(Ark_Int32 nodeId, const Ark_Number totalOffsetX, const Ark_Number totalOffsetY);
    void (*onEditChange)(Ark_Int32 nodeId, const Ark_Boolean isEditing);
    void (*onCopy)(Ark_Int32 nodeId, const Ark_String value);
    void (*onCut)(Ark_Int32 nodeId, const Ark_String value);
    void (*onPaste)(Ark_Int32 nodeId, const Ark_String value, const PasteEvent event);
    void (*onWillInsert)(Ark_Int32 nodeId, const InsertValue data);
    void (*onDidInsert)(Ark_Int32 nodeId, const InsertValue data);
    void (*onWillDelete)(Ark_Int32 nodeId, const DeleteValue data);
    void (*onDidDelete)(Ark_Int32 nodeId, const DeleteValue data);
} GENERATED_ArkUITextAreaEventsReceiver;

typedef struct GENERATED_ArkUITextClockEventsReceiver {
    void (*onDateChange)(Ark_Int32 nodeId, const Ark_Number value);
} GENERATED_ArkUITextClockEventsReceiver;

typedef struct GENERATED_ArkUITextInputEventsReceiver {
    void (*onEditChanged)(Ark_Int32 nodeId, const Ark_Boolean isEditing);
    void (*onEditChange)(Ark_Int32 nodeId, const Ark_Boolean isEditing);
    void (*onSubmit)(Ark_Int32 nodeId, const Ark_Int32 enterKey, const SubmitEvent event);
    void (*onChange)(Ark_Int32 nodeId, const Ark_String value, const Opt_TextRange previewRange);
    void (*onTextSelectionChange)(Ark_Int32 nodeId, const Ark_Number selectionStart, const Ark_Number selectionEnd);
    void (*onContentScroll)(Ark_Int32 nodeId, const Ark_Number totalOffsetX, const Ark_Number totalOffsetY);
    void (*inputFilter)(Ark_Int32 nodeId, const Ark_String value);
    void (*onCopy)(Ark_Int32 nodeId, const Ark_String value);
    void (*onCut)(Ark_Int32 nodeId, const Ark_String value);
    void (*onPaste)(Ark_Int32 nodeId, const Ark_String value, const PasteEvent event);
    void (*onSecurityStateChange)(Ark_Int32 nodeId, const Ark_Boolean data);
    void (*onWillInsert)(Ark_Int32 nodeId, const InsertValue data);
    void (*onDidInsert)(Ark_Int32 nodeId, const InsertValue data);
    void (*onWillDelete)(Ark_Int32 nodeId, const DeleteValue data);
    void (*onDidDelete)(Ark_Int32 nodeId, const DeleteValue data);
} GENERATED_ArkUITextInputEventsReceiver;

typedef struct GENERATED_ArkUITextPickerEventsReceiver {
    void (*onAccept)(Ark_Int32 nodeId, const Ark_String value, const Ark_Number index);
    void (*onCancel)(Ark_Int32 nodeId);
    void (*onChange)(Ark_Int32 nodeId, const Union_Ark_String_Array_Ark_String value, const Union_Ark_Number_Array_Ark_Number index);
} GENERATED_ArkUITextPickerEventsReceiver;

typedef struct GENERATED_ArkUITextTimerEventsReceiver {
    void (*onTimer)(Ark_Int32 nodeId, const Ark_Number utc, const Ark_Number elapsedTime);
} GENERATED_ArkUITextTimerEventsReceiver;

typedef struct GENERATED_ArkUITimePickerEventsReceiver {
    void (*onChange)(Ark_Int32 nodeId, const TimePickerResult value);
} GENERATED_ArkUITimePickerEventsReceiver;

typedef struct GENERATED_ArkUIToggleEventsReceiver {
    void (*onChange)(Ark_Int32 nodeId, const Ark_Boolean isOn);
} GENERATED_ArkUIToggleEventsReceiver;

typedef struct GENERATED_ArkUIVideoEventsReceiver {
    void (*onStart)(Ark_Int32 nodeId);
    void (*onPause)(Ark_Int32 nodeId);
    void (*onFinish)(Ark_Int32 nodeId);
    void (*onFullscreenChange)(Ark_Int32 nodeId, const Literal_fullscreen_Ark_Boolean event);
    void (*onPrepared)(Ark_Int32 nodeId, const Literal_duration_Ark_Number event);
    void (*onSeeking)(Ark_Int32 nodeId, const Literal_time_Ark_Number event);
    void (*onSeeked)(Ark_Int32 nodeId, const Literal_time_Ark_Number event);
    void (*onUpdate)(Ark_Int32 nodeId, const Literal_time_Ark_Number event);
    void (*onError)(Ark_Int32 nodeId);
    void (*onStop)(Ark_Int32 nodeId);
} GENERATED_ArkUIVideoEventsReceiver;

typedef struct GENERATED_ArkUIWebEventsReceiver {
    void (*onPageEnd)(Ark_Int32 nodeId, const OnPageEndEvent data);
    void (*onPageBegin)(Ark_Int32 nodeId, const OnPageBeginEvent data);
    void (*onProgressChange)(Ark_Int32 nodeId, const OnProgressChangeEvent data);
    void (*onTitleReceive)(Ark_Int32 nodeId, const OnTitleReceiveEvent data);
    void (*onGeolocationHide)(Ark_Int32 nodeId);
    void (*onGeolocationShow)(Ark_Int32 nodeId, const OnGeolocationShowEvent data);
    void (*onRequestSelected)(Ark_Int32 nodeId);
    void (*onAlert)(Ark_Int32 nodeId, const OnAlertEvent data);
    void (*onBeforeUnload)(Ark_Int32 nodeId, const OnBeforeUnloadEvent data);
    void (*onConfirm)(Ark_Int32 nodeId, const OnConfirmEvent data);
    void (*onPrompt)(Ark_Int32 nodeId, const OnPromptEvent data);
    void (*onConsole)(Ark_Int32 nodeId, const OnConsoleEvent data);
    void (*onErrorReceive)(Ark_Int32 nodeId, const OnErrorReceiveEvent data);
    void (*onHttpErrorReceive)(Ark_Int32 nodeId, const OnHttpErrorReceiveEvent data);
    void (*onDownloadStart)(Ark_Int32 nodeId, const OnDownloadStartEvent data);
    void (*onRefreshAccessedHistory)(Ark_Int32 nodeId, const OnRefreshAccessedHistoryEvent data);
    void (*onUrlLoadIntercept)(Ark_Int32 nodeId, const Opt_Literal_data_Union_Ark_String_WebResourceRequest event);
    void (*onSslErrorReceive)(Ark_Int32 nodeId, const Opt_Literal_handler_Function_error_Ark_CustomObject event);
    void (*onShowFileSelector)(Ark_Int32 nodeId, const OnShowFileSelectorEvent data);
    void (*onFileSelectorShow)(Ark_Int32 nodeId, const Opt_Literal_callback_Function_fileSelector_Ark_CustomObject event);
    void (*onResourceLoad)(Ark_Int32 nodeId, const OnResourceLoadEvent data);
    void (*onFullScreenExit)(Ark_Int32 nodeId);
    void (*onFullScreenEnter)(Ark_Int32 nodeId, const FullScreenEnterEvent event);
    void (*onScaleChange)(Ark_Int32 nodeId, const OnScaleChangeEvent data);
    void (*onHttpAuthRequest)(Ark_Int32 nodeId, const OnHttpAuthRequestEvent data);
    void (*onInterceptRequest)(Ark_Int32 nodeId, const OnInterceptRequestEvent data);
    void (*onPermissionRequest)(Ark_Int32 nodeId, const OnPermissionRequestEvent data);
    void (*onScreenCaptureRequest)(Ark_Int32 nodeId, const OnScreenCaptureRequestEvent data);
    void (*onContextMenuShow)(Ark_Int32 nodeId, const OnContextMenuShowEvent data);
    void (*onContextMenuHide)(Ark_Int32 nodeId);
    void (*onSearchResultReceive)(Ark_Int32 nodeId, const OnSearchResultReceiveEvent data);
    void (*onScroll)(Ark_Int32 nodeId, const OnScrollEvent data);
    void (*onSslErrorEventReceive)(Ark_Int32 nodeId, const OnSslErrorEventReceiveEvent data);
    void (*onSslErrorEvent)(Ark_Int32 nodeId, const SslErrorEvent sslErrorEvent);
    void (*onClientAuthenticationRequest)(Ark_Int32 nodeId, const OnClientAuthenticationEvent data);
    void (*onWindowNew)(Ark_Int32 nodeId, const OnWindowNewEvent data);
    void (*onWindowExit)(Ark_Int32 nodeId);
    void (*onInterceptKeyEvent)(Ark_Int32 nodeId, const KeyEvent event);
    void (*onTouchIconUrlReceived)(Ark_Int32 nodeId, const OnTouchIconUrlReceivedEvent data);
    void (*onFaviconReceived)(Ark_Int32 nodeId, const OnFaviconReceivedEvent data);
    void (*onPageVisible)(Ark_Int32 nodeId, const OnPageVisibleEvent data);
    void (*onDataResubmitted)(Ark_Int32 nodeId, const OnDataResubmittedEvent data);
    void (*onAudioStateChanged)(Ark_Int32 nodeId, const OnAudioStateChangedEvent data);
    void (*onFirstContentfulPaint)(Ark_Int32 nodeId, const OnFirstContentfulPaintEvent data);
    void (*onFirstMeaningfulPaint)(Ark_Int32 nodeId, const FirstMeaningfulPaint firstMeaningfulPaint);
    void (*onLargestContentfulPaint)(Ark_Int32 nodeId, const LargestContentfulPaint largestContentfulPaint);
    void (*onLoadIntercept)(Ark_Int32 nodeId, const OnLoadInterceptEvent data);
    void (*onControllerAttached)(Ark_Int32 nodeId);
    void (*onOverScroll)(Ark_Int32 nodeId, const OnOverScrollEvent data);
    void (*onSafeBrowsingCheckResult)(Ark_Int32 nodeId, const Ark_Int32 threatType);
    void (*onNavigationEntryCommitted)(Ark_Int32 nodeId, const LoadCommittedDetails loadCommittedDetails);
    void (*onIntelligentTrackingPreventionResult)(Ark_Int32 nodeId, const IntelligentTrackingPreventionDetails details);
    void (*onNativeEmbedLifecycleChange)(Ark_Int32 nodeId, const NativeEmbedDataInfo event);
    void (*onNativeEmbedGestureEvent)(Ark_Int32 nodeId, const NativeEmbedTouchInfo event);
    void (*onOverrideUrlLoading)(Ark_Int32 nodeId, const Ark_Materialized webResourceRequest);
    void (*onRenderProcessNotResponding)(Ark_Int32 nodeId, const RenderProcessNotRespondingData data);
    void (*onRenderProcessResponding)(Ark_Int32 nodeId);
    void (*onViewportFitChanged)(Ark_Int32 nodeId, const Ark_Int32 viewportFit);
    void (*onInterceptKeyboardAttach)(Ark_Int32 nodeId, const WebKeyboardCallbackInfo keyboardCallbackInfo);
    void (*onAdsBlocked)(Ark_Int32 nodeId, const AdsBlockedDetails details);
} GENERATED_ArkUIWebEventsReceiver;

typedef struct GENERATED_ArkUIXComponentEventsReceiver {
    void (*onLoad)(Ark_Int32 nodeId, const Opt_Ark_CustomObject event);
    void (*onDestroy)(Ark_Int32 nodeId);
} GENERATED_ArkUIXComponentEventsReceiver;

typedef struct GENERATED_ArkUISideBarContainerEventsReceiver {
    void (*onChange)(Ark_Int32 nodeId, const Ark_Boolean value);
} GENERATED_ArkUISideBarContainerEventsReceiver;

typedef struct GENERATED_ArkUIWaterFlowEventsReceiver {
    void (*onReachStart)(Ark_Int32 nodeId);
    void (*onReachEnd)(Ark_Int32 nodeId);
    void (*onScrollFrameBegin)(Ark_Int32 nodeId, const Ark_Number offset, const Ark_Int32 state);
    void (*onScrollIndex)(Ark_Int32 nodeId, const Ark_Number first, const Ark_Number last);
} GENERATED_ArkUIWaterFlowEventsReceiver;

typedef struct GENERATED_ArkUIUIExtensionComponentEventsReceiver {
    void (*onTerminated)(Ark_Int32 nodeId, const TerminationInfo data);
} GENERATED_ArkUIUIExtensionComponentEventsReceiver;




/**
 * An API to control an implementation. When making changes modifying binary
 * layout, i.e. adding new events - increase ARKUI_API_VERSION above for binary
 * layout checks.
 */
typedef struct GENERATED_ArkUINodeModifiers {
    const GENERATED_ArkUIAbilityComponentModifier* (*getAbilityComponentModifier)();
    const GENERATED_ArkUIAlphabetIndexerModifier* (*getAlphabetIndexerModifier)();
    const GENERATED_ArkUIAnimatorModifier* (*getAnimatorModifier)();
    const GENERATED_ArkUIBadgeModifier* (*getBadgeModifier)();
    const GENERATED_ArkUIBlankModifier* (*getBlankModifier)();
    const GENERATED_ArkUIButtonModifier* (*getButtonModifier)();
    const GENERATED_ArkUICalendarModifier* (*getCalendarModifier)();
    const GENERATED_ArkUICalendarPickerModifier* (*getCalendarPickerModifier)();
    const GENERATED_ArkUICanvasModifier* (*getCanvasModifier)();
    const GENERATED_ArkUICheckboxModifier* (*getCheckboxModifier)();
    const GENERATED_ArkUICheckboxGroupModifier* (*getCheckboxGroupModifier)();
    const GENERATED_ArkUICircleModifier* (*getCircleModifier)();
    const GENERATED_ArkUIColumnModifier* (*getColumnModifier)();
    const GENERATED_ArkUIColumnSplitModifier* (*getColumnSplitModifier)();
    const GENERATED_ArkUICommonMethodModifier* (*getCommonMethodModifier)();
    const GENERATED_ArkUICommonShapeMethodModifier* (*getCommonShapeMethodModifier)();
    const GENERATED_ArkUICommonModifier* (*getCommonModifier)();
    const GENERATED_ArkUIScrollableCommonMethodModifier* (*getScrollableCommonMethodModifier)();
    const GENERATED_ArkUIComponent3DModifier* (*getComponent3DModifier)();
    const GENERATED_ArkUIContainerSpanModifier* (*getContainerSpanModifier)();
    const GENERATED_ArkUICounterModifier* (*getCounterModifier)();
    const GENERATED_ArkUIDataPanelModifier* (*getDataPanelModifier)();
    const GENERATED_ArkUIDatePickerModifier* (*getDatePickerModifier)();
    const GENERATED_ArkUIDividerModifier* (*getDividerModifier)();
    const GENERATED_ArkUIEffectComponentModifier* (*getEffectComponentModifier)();
    const GENERATED_ArkUIEllipseModifier* (*getEllipseModifier)();
    const GENERATED_ArkUIEmbeddedComponentModifier* (*getEmbeddedComponentModifier)();
    const GENERATED_ArkUIFlexModifier* (*getFlexModifier)();
    const GENERATED_ArkUIFlowItemModifier* (*getFlowItemModifier)();
    const GENERATED_ArkUIFolderStackModifier* (*getFolderStackModifier)();
    const GENERATED_ArkUIFormComponentModifier* (*getFormComponentModifier)();
    const GENERATED_ArkUIFormLinkModifier* (*getFormLinkModifier)();
    const GENERATED_ArkUIGaugeModifier* (*getGaugeModifier)();
    const GENERATED_ArkUIGridModifier* (*getGridModifier)();
    const GENERATED_ArkUIGridItemModifier* (*getGridItemModifier)();
    const GENERATED_ArkUIGridColModifier* (*getGridColModifier)();
    const GENERATED_ArkUIGridContainerModifier* (*getGridContainerModifier)();
    const GENERATED_ArkUIGridRowModifier* (*getGridRowModifier)();
    const GENERATED_ArkUIHyperlinkModifier* (*getHyperlinkModifier)();
    const GENERATED_ArkUIImageModifier* (*getImageModifier)();
    const GENERATED_ArkUIImageAnimatorModifier* (*getImageAnimatorModifier)();
    const GENERATED_ArkUIImageSpanModifier* (*getImageSpanModifier)();
    const GENERATED_ArkUILineModifier* (*getLineModifier)();
    const GENERATED_ArkUIListModifier* (*getListModifier)();
    const GENERATED_ArkUIListItemModifier* (*getListItemModifier)();
    const GENERATED_ArkUIListItemGroupModifier* (*getListItemGroupModifier)();
    const GENERATED_ArkUILoadingProgressModifier* (*getLoadingProgressModifier)();
    const GENERATED_ArkUILocationButtonModifier* (*getLocationButtonModifier)();
    const GENERATED_ArkUIMarqueeModifier* (*getMarqueeModifier)();
    const GENERATED_ArkUIMediaCachedImageModifier* (*getMediaCachedImageModifier)();
    const GENERATED_ArkUIMenuModifier* (*getMenuModifier)();
    const GENERATED_ArkUIMenuItemModifier* (*getMenuItemModifier)();
    const GENERATED_ArkUIMenuItemGroupModifier* (*getMenuItemGroupModifier)();
    const GENERATED_ArkUINavDestinationModifier* (*getNavDestinationModifier)();
    const GENERATED_ArkUINavRouterModifier* (*getNavRouterModifier)();
    const GENERATED_ArkUINavigationModifier* (*getNavigationModifier)();
    const GENERATED_ArkUINavigatorModifier* (*getNavigatorModifier)();
    const GENERATED_ArkUINodeContainerModifier* (*getNodeContainerModifier)();
    const GENERATED_ArkUIPanelModifier* (*getPanelModifier)();
    const GENERATED_ArkUIPasteButtonModifier* (*getPasteButtonModifier)();
    const GENERATED_ArkUIPathModifier* (*getPathModifier)();
    const GENERATED_ArkUIPatternLockModifier* (*getPatternLockModifier)();
    const GENERATED_ArkUIPluginComponentModifier* (*getPluginComponentModifier)();
    const GENERATED_ArkUIPolygonModifier* (*getPolygonModifier)();
    const GENERATED_ArkUIPolylineModifier* (*getPolylineModifier)();
    const GENERATED_ArkUIQRCodeModifier* (*getQRCodeModifier)();
    const GENERATED_ArkUIRadioModifier* (*getRadioModifier)();
    const GENERATED_ArkUIRatingModifier* (*getRatingModifier)();
    const GENERATED_ArkUIRectModifier* (*getRectModifier)();
    const GENERATED_ArkUIRefreshModifier* (*getRefreshModifier)();
    const GENERATED_ArkUIRelativeContainerModifier* (*getRelativeContainerModifier)();
    const GENERATED_ArkUIRichEditorModifier* (*getRichEditorModifier)();
    const GENERATED_ArkUIRichTextModifier* (*getRichTextModifier)();
    const GENERATED_ArkUIRootSceneModifier* (*getRootSceneModifier)();
    const GENERATED_ArkUIRowModifier* (*getRowModifier)();
    const GENERATED_ArkUIRowSplitModifier* (*getRowSplitModifier)();
    const GENERATED_ArkUISaveButtonModifier* (*getSaveButtonModifier)();
    const GENERATED_ArkUIScreenModifier* (*getScreenModifier)();
    const GENERATED_ArkUIScrollModifier* (*getScrollModifier)();
    const GENERATED_ArkUIScrollBarModifier* (*getScrollBarModifier)();
    const GENERATED_ArkUISearchModifier* (*getSearchModifier)();
    const GENERATED_ArkUISecurityComponentMethodModifier* (*getSecurityComponentMethodModifier)();
    const GENERATED_ArkUISelectModifier* (*getSelectModifier)();
    const GENERATED_ArkUIShapeModifier* (*getShapeModifier)();
    const GENERATED_ArkUISliderModifier* (*getSliderModifier)();
    const GENERATED_ArkUIBaseSpanModifier* (*getBaseSpanModifier)();
    const GENERATED_ArkUISpanModifier* (*getSpanModifier)();
    const GENERATED_ArkUIStackModifier* (*getStackModifier)();
    const GENERATED_ArkUIStepperModifier* (*getStepperModifier)();
    const GENERATED_ArkUIStepperItemModifier* (*getStepperItemModifier)();
    const GENERATED_ArkUISwiperModifier* (*getSwiperModifier)();
    const GENERATED_ArkUISymbolGlyphModifier* (*getSymbolGlyphModifier)();
    const GENERATED_ArkUISymbolSpanModifier* (*getSymbolSpanModifier)();
    const GENERATED_ArkUITabsModifier* (*getTabsModifier)();
    const GENERATED_ArkUITabContentModifier* (*getTabContentModifier)();
    const GENERATED_ArkUITextModifier* (*getTextModifier)();
    const GENERATED_ArkUITextAreaModifier* (*getTextAreaModifier)();
    const GENERATED_ArkUITextClockModifier* (*getTextClockModifier)();
    const GENERATED_ArkUITextInputModifier* (*getTextInputModifier)();
    const GENERATED_ArkUITextPickerModifier* (*getTextPickerModifier)();
    const GENERATED_ArkUITextTimerModifier* (*getTextTimerModifier)();
    const GENERATED_ArkUITimePickerModifier* (*getTimePickerModifier)();
    const GENERATED_ArkUIToggleModifier* (*getToggleModifier)();
    const GENERATED_ArkUIVideoModifier* (*getVideoModifier)();
    const GENERATED_ArkUIWebModifier* (*getWebModifier)();
    const GENERATED_ArkUIWindowSceneModifier* (*getWindowSceneModifier)();
    const GENERATED_ArkUIXComponentModifier* (*getXComponentModifier)();
    const GENERATED_ArkUISideBarContainerModifier* (*getSideBarContainerModifier)();
    const GENERATED_ArkUIRemoteWindowModifier* (*getRemoteWindowModifier)();
    const GENERATED_ArkUIWaterFlowModifier* (*getWaterFlowModifier)();
    const GENERATED_ArkUIUIExtensionComponentModifier* (*getUIExtensionComponentModifier)();
    const GENERATED_ArkUILinearIndicatorModifier* (*getLinearIndicatorModifier)();
} GENERATED_ArkUINodeModifiers;

typedef struct GENERATED_ArkUIAccessors {
    const GENERATED_ArkUIDrawModifierAccessor* (*getDrawModifierAccessor)();
    const GENERATED_ArkUIPanGestureOptionsAccessor* (*getPanGestureOptionsAccessor)();
    const GENERATED_ArkUIProgressMaskAccessor* (*getProgressMaskAccessor)();
    const GENERATED_ArkUIAttributeModifierAccessor* (*getAttributeModifierAccessor)();
    const GENERATED_ArkUIGestureModifierAccessor* (*getGestureModifierAccessor)();
    const GENERATED_ArkUIGestureRecognizerAccessor* (*getGestureRecognizerAccessor)();
    const GENERATED_ArkUIEventTargetInfoAccessor* (*getEventTargetInfoAccessor)();
    const GENERATED_ArkUIContentModifierAccessor* (*getContentModifierAccessor)();
    const GENERATED_ArkUICalendarControllerAccessor* (*getCalendarControllerAccessor)();
    const GENERATED_ArkUICanvasRenderingContext2DAccessor* (*getCanvasRenderingContext2DAccessor)();
    const GENERATED_ArkUICanvasRendererAccessor* (*getCanvasRendererAccessor)();
    const GENERATED_ArkUICanvasPathAccessor* (*getCanvasPathAccessor)();
    const GENERATED_ArkUIImageBitmapAccessor* (*getImageBitmapAccessor)();
    const GENERATED_ArkUIPath2DAccessor* (*getPath2DAccessor)();
    const GENERATED_ArkUIMatrix2DAccessor* (*getMatrix2DAccessor)();
    const GENERATED_ArkUICanvasGradientAccessor* (*getCanvasGradientAccessor)();
    const GENERATED_ArkUICanvasPatternAccessor* (*getCanvasPatternAccessor)();
    const GENERATED_ArkUIDrawingRenderingContextAccessor* (*getDrawingRenderingContextAccessor)();
    const GENERATED_ArkUIImageAnalyzerControllerAccessor* (*getImageAnalyzerControllerAccessor)();
    const GENERATED_ArkUIScrollerAccessor* (*getScrollerAccessor)();
    const GENERATED_ArkUIChildrenMainSizeAccessor* (*getChildrenMainSizeAccessor)();
    const GENERATED_ArkUINavigationTransitionProxyAccessor* (*getNavigationTransitionProxyAccessor)();
    const GENERATED_ArkUINavPathStackAccessor* (*getNavPathStackAccessor)();
    const GENERATED_ArkUINavDestinationContextAccessor* (*getNavDestinationContextAccessor)();
    const GENERATED_ArkUIPatternLockControllerAccessor* (*getPatternLockControllerAccessor)();
    const GENERATED_ArkUIEditMenuOptionsAccessor* (*getEditMenuOptionsAccessor)();
    const GENERATED_ArkUITextMenuItemIdAccessor* (*getTextMenuItemIdAccessor)();
    const GENERATED_ArkUIRichEditorControllerAccessor* (*getRichEditorControllerAccessor)();
    const GENERATED_ArkUIRichEditorBaseControllerAccessor* (*getRichEditorBaseControllerAccessor)();
    const GENERATED_ArkUITextEditControllerExAccessor* (*getTextEditControllerExAccessor)();
    const GENERATED_ArkUITextBaseControllerAccessor* (*getTextBaseControllerAccessor)();
    const GENERATED_ArkUILayoutManagerAccessor* (*getLayoutManagerAccessor)();
    const GENERATED_ArkUIStyledStringAccessor* (*getStyledStringAccessor)();
    const GENERATED_ArkUICustomSpanAccessor* (*getCustomSpanAccessor)();
    const GENERATED_ArkUIRichEditorStyledStringControllerAccessor* (*getRichEditorStyledStringControllerAccessor)();
    const GENERATED_ArkUIStyledStringControllerAccessor* (*getStyledStringControllerAccessor)();
    const GENERATED_ArkUIMutableStyledStringAccessor* (*getMutableStyledStringAccessor)();
    const GENERATED_ArkUISearchControllerAccessor* (*getSearchControllerAccessor)();
    const GENERATED_ArkUITextContentControllerBaseAccessor* (*getTextContentControllerBaseAccessor)();
    const GENERATED_ArkUISwiperContentTransitionProxyAccessor* (*getSwiperContentTransitionProxyAccessor)();
    const GENERATED_ArkUISwiperControllerAccessor* (*getSwiperControllerAccessor)();
    const GENERATED_ArkUITabContentTransitionProxyAccessor* (*getTabContentTransitionProxyAccessor)();
    const GENERATED_ArkUITabsControllerAccessor* (*getTabsControllerAccessor)();
    const GENERATED_ArkUITextControllerAccessor* (*getTextControllerAccessor)();
    const GENERATED_ArkUITextAreaControllerAccessor* (*getTextAreaControllerAccessor)();
    const GENERATED_ArkUITextClockControllerAccessor* (*getTextClockControllerAccessor)();
    const GENERATED_ArkUITextInputControllerAccessor* (*getTextInputControllerAccessor)();
    const GENERATED_ArkUITextTimerControllerAccessor* (*getTextTimerControllerAccessor)();
    const GENERATED_ArkUIVideoControllerAccessor* (*getVideoControllerAccessor)();
    const GENERATED_ArkUIWebControllerAccessor* (*getWebControllerAccessor)();
    const GENERATED_ArkUIWebCookieAccessor* (*getWebCookieAccessor)();
    const GENERATED_ArkUIJsGeolocationAccessor* (*getJsGeolocationAccessor)();
    const GENERATED_ArkUIJsResultAccessor* (*getJsResultAccessor)();
    const GENERATED_ArkUIConsoleMessageAccessor* (*getConsoleMessageAccessor)();
    const GENERATED_ArkUIWebResourceRequestAccessor* (*getWebResourceRequestAccessor)();
    const GENERATED_ArkUIWebResourceErrorAccessor* (*getWebResourceErrorAccessor)();
    const GENERATED_ArkUIWebResourceResponseAccessor* (*getWebResourceResponseAccessor)();
    const GENERATED_ArkUIFileSelectorResultAccessor* (*getFileSelectorResultAccessor)();
    const GENERATED_ArkUIFileSelectorParamAccessor* (*getFileSelectorParamAccessor)();
    const GENERATED_ArkUIFullScreenExitHandlerAccessor* (*getFullScreenExitHandlerAccessor)();
    const GENERATED_ArkUIHttpAuthHandlerAccessor* (*getHttpAuthHandlerAccessor)();
    const GENERATED_ArkUIPermissionRequestAccessor* (*getPermissionRequestAccessor)();
    const GENERATED_ArkUIScreenCaptureHandlerAccessor* (*getScreenCaptureHandlerAccessor)();
    const GENERATED_ArkUIWebContextMenuParamAccessor* (*getWebContextMenuParamAccessor)();
    const GENERATED_ArkUIWebContextMenuResultAccessor* (*getWebContextMenuResultAccessor)();
    const GENERATED_ArkUISslErrorHandlerAccessor* (*getSslErrorHandlerAccessor)();
    const GENERATED_ArkUIClientAuthenticationHandlerAccessor* (*getClientAuthenticationHandlerAccessor)();
    const GENERATED_ArkUIControllerHandlerAccessor* (*getControllerHandlerAccessor)();
    const GENERATED_ArkUIDataResubmissionHandlerAccessor* (*getDataResubmissionHandlerAccessor)();
    const GENERATED_ArkUIEventResultAccessor* (*getEventResultAccessor)();
    const GENERATED_ArkUIWebKeyboardControllerAccessor* (*getWebKeyboardControllerAccessor)();
    const GENERATED_ArkUIXComponentControllerAccessor* (*getXComponentControllerAccessor)();
    const GENERATED_ArkUIWaterFlowSectionsAccessor* (*getWaterFlowSectionsAccessor)();
    const GENERATED_ArkUILinearIndicatorControllerAccessor* (*getLinearIndicatorControllerAccessor)();
} GENERATED_ArkUIAccessors;

typedef struct GENERATED_ArkUIAnimation {
} GENERATED_ArkUIAnimation;

typedef struct GENERATED_ArkUINavigation {
} GENERATED_ArkUINavigation;

typedef struct GENERATED_ArkUIGraphicsAPI {
    Ark_Int32 version;
} GENERATED_ArkUIGraphicsAPI;

typedef struct GENERATED_ArkUIEventsAPI {
    const GENERATED_ArkUIAbilityComponentEventsReceiver* (*getAbilityComponentEventsReceiver)();
    const GENERATED_ArkUIAlphabetIndexerEventsReceiver* (*getAlphabetIndexerEventsReceiver)();
    const GENERATED_ArkUIAnimatorEventsReceiver* (*getAnimatorEventsReceiver)();
    const GENERATED_ArkUICalendarEventsReceiver* (*getCalendarEventsReceiver)();
    const GENERATED_ArkUICalendarPickerEventsReceiver* (*getCalendarPickerEventsReceiver)();
    const GENERATED_ArkUICanvasEventsReceiver* (*getCanvasEventsReceiver)();
    const GENERATED_ArkUICheckboxEventsReceiver* (*getCheckboxEventsReceiver)();
    const GENERATED_ArkUICheckboxGroupEventsReceiver* (*getCheckboxGroupEventsReceiver)();
    const GENERATED_ArkUICommonMethodEventsReceiver* (*getCommonMethodEventsReceiver)();
    const GENERATED_ArkUIScrollableCommonMethodEventsReceiver* (*getScrollableCommonMethodEventsReceiver)();
    const GENERATED_ArkUICounterEventsReceiver* (*getCounterEventsReceiver)();
    const GENERATED_ArkUIDatePickerEventsReceiver* (*getDatePickerEventsReceiver)();
    const GENERATED_ArkUIFolderStackEventsReceiver* (*getFolderStackEventsReceiver)();
    const GENERATED_ArkUIFormComponentEventsReceiver* (*getFormComponentEventsReceiver)();
    const GENERATED_ArkUIGridEventsReceiver* (*getGridEventsReceiver)();
    const GENERATED_ArkUIGridItemEventsReceiver* (*getGridItemEventsReceiver)();
    const GENERATED_ArkUIGridRowEventsReceiver* (*getGridRowEventsReceiver)();
    const GENERATED_ArkUIImageEventsReceiver* (*getImageEventsReceiver)();
    const GENERATED_ArkUIImageAnimatorEventsReceiver* (*getImageAnimatorEventsReceiver)();
    const GENERATED_ArkUIImageSpanEventsReceiver* (*getImageSpanEventsReceiver)();
    const GENERATED_ArkUIListEventsReceiver* (*getListEventsReceiver)();
    const GENERATED_ArkUIListItemEventsReceiver* (*getListItemEventsReceiver)();
    const GENERATED_ArkUILocationButtonEventsReceiver* (*getLocationButtonEventsReceiver)();
    const GENERATED_ArkUIMarqueeEventsReceiver* (*getMarqueeEventsReceiver)();
    const GENERATED_ArkUIMenuItemEventsReceiver* (*getMenuItemEventsReceiver)();
    const GENERATED_ArkUINavDestinationEventsReceiver* (*getNavDestinationEventsReceiver)();
    const GENERATED_ArkUINavRouterEventsReceiver* (*getNavRouterEventsReceiver)();
    const GENERATED_ArkUINavigationEventsReceiver* (*getNavigationEventsReceiver)();
    const GENERATED_ArkUIPanelEventsReceiver* (*getPanelEventsReceiver)();
    const GENERATED_ArkUIPasteButtonEventsReceiver* (*getPasteButtonEventsReceiver)();
    const GENERATED_ArkUIPatternLockEventsReceiver* (*getPatternLockEventsReceiver)();
    const GENERATED_ArkUIPluginComponentEventsReceiver* (*getPluginComponentEventsReceiver)();
    const GENERATED_ArkUIRadioEventsReceiver* (*getRadioEventsReceiver)();
    const GENERATED_ArkUIRatingEventsReceiver* (*getRatingEventsReceiver)();
    const GENERATED_ArkUIRefreshEventsReceiver* (*getRefreshEventsReceiver)();
    const GENERATED_ArkUIRichEditorEventsReceiver* (*getRichEditorEventsReceiver)();
    const GENERATED_ArkUIRichTextEventsReceiver* (*getRichTextEventsReceiver)();
    const GENERATED_ArkUISaveButtonEventsReceiver* (*getSaveButtonEventsReceiver)();
    const GENERATED_ArkUIScrollEventsReceiver* (*getScrollEventsReceiver)();
    const GENERATED_ArkUISearchEventsReceiver* (*getSearchEventsReceiver)();
    const GENERATED_ArkUISelectEventsReceiver* (*getSelectEventsReceiver)();
    const GENERATED_ArkUISliderEventsReceiver* (*getSliderEventsReceiver)();
    const GENERATED_ArkUIStepperEventsReceiver* (*getStepperEventsReceiver)();
    const GENERATED_ArkUISwiperEventsReceiver* (*getSwiperEventsReceiver)();
    const GENERATED_ArkUITabsEventsReceiver* (*getTabsEventsReceiver)();
    const GENERATED_ArkUITabContentEventsReceiver* (*getTabContentEventsReceiver)();
    const GENERATED_ArkUITextEventsReceiver* (*getTextEventsReceiver)();
    const GENERATED_ArkUITextAreaEventsReceiver* (*getTextAreaEventsReceiver)();
    const GENERATED_ArkUITextClockEventsReceiver* (*getTextClockEventsReceiver)();
    const GENERATED_ArkUITextInputEventsReceiver* (*getTextInputEventsReceiver)();
    const GENERATED_ArkUITextPickerEventsReceiver* (*getTextPickerEventsReceiver)();
    const GENERATED_ArkUITextTimerEventsReceiver* (*getTextTimerEventsReceiver)();
    const GENERATED_ArkUITimePickerEventsReceiver* (*getTimePickerEventsReceiver)();
    const GENERATED_ArkUIToggleEventsReceiver* (*getToggleEventsReceiver)();
    const GENERATED_ArkUIVideoEventsReceiver* (*getVideoEventsReceiver)();
    const GENERATED_ArkUIWebEventsReceiver* (*getWebEventsReceiver)();
    const GENERATED_ArkUIXComponentEventsReceiver* (*getXComponentEventsReceiver)();
    const GENERATED_ArkUISideBarContainerEventsReceiver* (*getSideBarContainerEventsReceiver)();
    const GENERATED_ArkUIWaterFlowEventsReceiver* (*getWaterFlowEventsReceiver)();
    const GENERATED_ArkUIUIExtensionComponentEventsReceiver* (*getUIExtensionComponentEventsReceiver)();
} GENERATED_ArkUIEventsAPI;


typedef enum GENERATED_Ark_NodeType {
    GENERATED_ARKUI_TEXT = 1,
    GENERATED_ARKUI_SPAN,
    GENERATED_ARKUI_IMAGE_SPAN,
    GENERATED_ARKUI_IMAGE,
    GENERATED_ARKUI_TOGGLE,
    GENERATED_ARKUI_LOADING_PROGRESS,
    GENERATED_ARKUI_TEXT_INPUT,
    GENERATED_ARKUI_STACK,
    GENERATED_ARKUI_SCROLL,
    GENERATED_ARKUI_LIST,
    GENERATED_ARKUI_SWIPER,
    GENERATED_ARKUI_TEXTAREA,
    GENERATED_ARKUI_BUTTON,
    GENERATED_ARKUI_PROGRESS,
    GENERATED_ARKUI_CHECKBOX,
    GENERATED_ARKUI_COLUMN,
    GENERATED_ARKUI_ROW,
    GENERATED_ARKUI_FLEX,
    GENERATED_ARKUI_LIST_ITEM,
    GENERATED_ARKUI_TABS,
    GENERATED_ARKUI_NAVIGATOR,
    GENERATED_ARKUI_WEB,
    GENERATED_ARKUI_SLIDER,
    GENERATED_ARKUI_CANVAS,
    GENERATED_ARKUI_RADIO,
    GENERATED_ARKUI_GRID,
    GENERATED_ARKUI_XCOMPONENT,
    GENERATED_ARKUI_SIDEBAR,
    GENERATED_ARKUI_REFRESH,
    GENERATED_ARKUI_ROOT,
    GENERATED_ARKUI_COMPONENT_ROOT,
    GENERATED_ARKUI_LIST_ITEM_GROUP,
    GENERATED_ARKUI_DATE_PICKER,
    GENERATED_ARKUI_TIME_PICKER,
    GENERATED_ARKUI_TEXT_PICKER,
    GENERATED_ARKUI_CALENDAR_PICKER,
    GENERATED_ARKUI_GRID_ITEM,
    GENERATED_ARKUI_CUSTOM,
    GENERATED_ARKUI_NAVIGATION,
    GENERATED_ARKUI_WATER_FLOW,
    GENERATED_ARKUI_FLOW_ITEM,
    GENERATED_ARKUI_RELATIVE_CONTAINER,
    GENERATED_ARKUI_BLANK,
    GENERATED_ARKUI_DIVIDER,
    GENERATED_ARKUI_ALPHABET_INDEXER,
    GENERATED_ARKUI_SEARCH,
    GENERATED_ARKUI_GRID_ROW,
    GENERATED_ARKUI_GRID_COL,
    GENERATED_ARKUI_SELECT,
    GENERATED_ARKUI_IMAGE_ANIMATOR,
    GENERATED_ARKUI_CIRCLE,
    GENERATED_ARKUI_TABCONTENT
} GENERATED_Ark_NodeType;

#define GENERATED_ARKUI_MAX_EVENT_NUM 1000

typedef enum GENERATED_Ark_EventSubKind {
    // common events
    GENERATED_ON_APPEAR = 0,
    GENERATED_ON_DISAPPEAR = 1,
    GENERATED_ON_TOUCH = 2,
    GENERATED_ON_CLICK = 3,
    GENERATED_ON_HOVER = 4,
    GENERATED_ON_BLUR = 5,
    GENERATED_ON_KEY_EVENT = 6,
    GENERATED_ON_MOUSE = 7,
    GENERATED_ON_AREA_CHANGE = 8,
    GENERATED_ON_VISIBLE_AREA_CHANGE = 9,
    GENERATED_ON_GESTURE = 10,
    GENERATED_ON_FOCUS = 11,
    GENERATED_ON_TOUCH_INTERCEPT = 12,
    GENERATED_ON_DETECT_RESULT_UPDATE = GENERATED_ARKUI_MAX_EVENT_NUM * GENERATED_ARKUI_TEXT,
    GENERATED_ON_IMAGE_COMPLETE = GENERATED_ARKUI_MAX_EVENT_NUM * GENERATED_ARKUI_IMAGE,
    GENERATED_ON_IMAGE_ERROR,
    GENERATED_ON_IMAGE_SVG_PLAY_FINISH,
    // components events
    GENERATED_ON_LIST_SCROLL = GENERATED_ARKUI_MAX_EVENT_NUM * GENERATED_ARKUI_LIST,
    GENERATED_ON_LIST_SCROLL_INDEX,
    GENERATED_ON_LIST_SCROLL_START,
    GENERATED_ON_LIST_SCROLL_STOP,
    GENERATED_ON_LIST_SCROLL_FRAME_BEGIN,
    GENERATED_ON_LIST_WILL_SCROLL,
    GENERATED_ON_LIST_DID_SCROLL,
    GENERATED_ON_LIST_REACH_START,
    GENERATED_ON_LIST_REACH_END,

    GENERATED_ON_TOGGLE_CHANGE = GENERATED_ARKUI_MAX_EVENT_NUM * GENERATED_ARKUI_TOGGLE,

    GENERATED_ON_CHECKBOX_CHANGE = GENERATED_ARKUI_MAX_EVENT_NUM * GENERATED_ARKUI_CHECKBOX,

    GENERATED_ON_TEXT_INPUT_EDIT_CHANGE = GENERATED_ARKUI_MAX_EVENT_NUM * GENERATED_ARKUI_TEXT_INPUT,
    GENERATED_ON_TEXT_INPUT_SUBMIT,
    GENERATED_ON_TEXT_INPUT_CHANGE,
    GENERATED_ON_TEXT_INPUT_CUT,
    GENERATED_ON_TEXT_INPUT_PASTE,
    GENERATED_ON_TEXT_INPUT_TEXT_SELECTION_CHANGE,
    GENERATED_ON_TEXT_INPUT_CONTENT_SIZE_CHANGE,
    GENERATED_ON_TEXT_INPUT_INPUT_FILTER_ERROR,
    GENERATED_ON_TEXT_INPUT_CONTENT_SCROLL,

    GENERATED_ON_TEXTAREA_EDIT_CHANGE = GENERATED_ARKUI_MAX_EVENT_NUM * GENERATED_ARKUI_TEXTAREA,
    GENERATED_ON_TEXTAREA_SUBMIT,
    GENERATED_ON_TEXTAREA_CHANGE,
    GENERATED_ON_TEXTAREA_PASTE,
    GENERATED_ON_TEXTAREA_TEXT_SELECTION_CHANGE,
    GENERATED_ON_TEXTAREA_ON_SUBMIT,
    GENERATED_ON_TEXTAREA_CONTENT_SIZE_CHANGE,
    GENERATED_ON_TEXT_AREA_INPUT_FILTER_ERROR,
    GENERATED_ON_TEXT_AREA_CONTENT_SCROLL,

    GENERATED_ON_SWIPER_CHANGE = GENERATED_ARKUI_MAX_EVENT_NUM * GENERATED_ARKUI_SWIPER,
    GENERATED_ON_SWIPER_ANIMATION_START,
    GENERATED_ON_SWIPER_ANIMATION_END,
    GENERATED_ON_SWIPER_GESTURE_SWIPE,

    GENERATED_ON_SCROLL = GENERATED_ARKUI_MAX_EVENT_NUM * GENERATED_ARKUI_SCROLL,
    GENERATED_ON_SCROLL_FRAME_BEGIN,
    GENERATED_ON_SCROLL_WILL_SCROLL,
    GENERATED_ON_SCROLL_DID_SCROLL,
    GENERATED_ON_SCROLL_START,
    GENERATED_ON_SCROLL_STOP,
    GENERATED_ON_SCROLL_EDGE,
    GENERATED_ON_SCROLL_REACH_START,
    GENERATED_ON_SCROLL_REACH_END,

    GENERATED_ON_TABS_CHANGE = GENERATED_ARKUI_MAX_EVENT_NUM * GENERATED_ARKUI_TABS,
    GENERATED_ON_NAVIGATOR_CLICK = GENERATED_ARKUI_MAX_EVENT_NUM * GENERATED_ARKUI_NAVIGATOR,
    GENERATED_ON_WEB_INTERCEPT = GENERATED_ARKUI_MAX_EVENT_NUM * GENERATED_ARKUI_WEB,
    GENERATED_ON_SLIDER_CHANGE = GENERATED_ARKUI_MAX_EVENT_NUM * GENERATED_ARKUI_SLIDER,
    GENERATED_ON_CANVAS_READY = GENERATED_ARKUI_MAX_EVENT_NUM * GENERATED_ARKUI_CANVAS,

    GENERATED_ON_RADIO_CHANGE = GENERATED_ARKUI_MAX_EVENT_NUM * GENERATED_ARKUI_RADIO,

    GENERATED_ON_GRID_SCROLL = GENERATED_ARKUI_MAX_EVENT_NUM * GENERATED_ARKUI_GRID,
    GENERATED_ON_GRID_START,
    GENERATED_ON_GRID_STOP,
    GENERATED_ON_GRID_SCROLL_TO_INDEX,

    GENERATED_ON_SIDEBAR_CHANGE = GENERATED_ARKUI_MAX_EVENT_NUM * GENERATED_ARKUI_SIDEBAR,

    GENERATED_ON_XCOMPONENT_LOAD = GENERATED_ARKUI_MAX_EVENT_NUM * GENERATED_ARKUI_XCOMPONENT,
    GENERATED_ON_XCOMPONENT_DESTROY,

    GENERATED_ON_REFRESH_STATE_CHANGE = GENERATED_ARKUI_MAX_EVENT_NUM * GENERATED_ARKUI_REFRESH,
    GENERATED_ON_REFRESH_REFRESHING,
    GENERATED_ON_DATE_PICKER_DATE_CHANGE = GENERATED_ARKUI_MAX_EVENT_NUM * GENERATED_ARKUI_DATE_PICKER,
    GENERATED_ON_TIME_PICKER_CHANGE = GENERATED_ARKUI_MAX_EVENT_NUM * GENERATED_ARKUI_TIME_PICKER,
    GENERATED_ON_TEXT_PICKER_CHANGE = GENERATED_ARKUI_MAX_EVENT_NUM * GENERATED_ARKUI_TEXT_PICKER,
    GENERATED_ON_CALENDAR_PICKER_CHANGE = GENERATED_ARKUI_MAX_EVENT_NUM * GENERATED_ARKUI_CALENDAR_PICKER,
    GENERATED_ON_WATER_FLOW_WILL_SCROLL = GENERATED_ARKUI_MAX_EVENT_NUM * GENERATED_ARKUI_WATER_FLOW,
    GENERATED_ON_WATER_FLOW_REACH_END,
    GENERATED_ON_WATER_FLOW_DID_SCROLL,
    GENERATED_ON_WATER_FLOW_SCROLL_START,
    GENERATED_ON_WATER_FLOW_SCROLL_STOP,
    GENERATED_ON_WATER_FLOW_SCROLL_FRAME_BEGIN,
    GENERATED_ON_WATER_FLOW_SCROLL_INDEX,
    GENERATED_ON_WATER_FLOW_REACH_START,

    GENERATED_ON_ALPHABET_INDEXER_SELECTED = GENERATED_ARKUI_MAX_EVENT_NUM * GENERATED_ARKUI_ALPHABET_INDEXER,
    GENERATED_ON_ALPHABET_INDEXER_REQUEST_POPUP_DATA,
    GENERATED_ON_ALPHABET_INDEXER_POPUP_SELECTED,
    GENERATED_ON_ALPHABET_INDEXER_CHANGE_EVENT,
    GENERATED_ON_ALPHABET_INDEXER_CREAT_CHANGE_EVENT,

    GENERATED_ON_SEARCH_SUBMIT = GENERATED_ARKUI_MAX_EVENT_NUM * GENERATED_ARKUI_SEARCH,
    GENERATED_ON_SEARCH_CHANGE,
    GENERATED_ON_SEARCH_COPY,
    GENERATED_ON_SEARCH_CUT,
    GENERATED_ON_SEARCH_PASTE,
} GENERATED_Ark_EventSubKind;

typedef enum {
    GENERATED_ARKUI_DIRTY_FLAG_MEASURE = 0b1,
    GENERATED_ARKUI_DIRTY_FLAG_LAYOUT = 0b10,
    // mark the node need to do attribute diff to drive update.
    GENERATED_ARKUI_DIRTY_FLAG_ATTRIBUTE_DIFF = 0b100,
    GENERATED_ARKUI_DIRTY_FLAG_MEASURE_SELF = 0b1000,
    GENERATED_ARKUI_DIRTY_FLAG_MEASURE_SELF_AND_PARENT = 0b10000,
    GENERATED_ARKUI_DIRTY_FLAG_MEASURE_BY_CHILD_REQUEST = 0b100000,
    GENERATED_ARKUI_DIRTY_FLAG_RENDER = 0b1000000,
    GENERATED_ARKUI_DIRTY_FLAG_MEASURE_SELF_AND_CHILD = 0b1000000000,
} GENERATED_ArkUIDirtyFlag;

union GENERATED_Ark_EventCallbackArg {
    Ark_Int32 i32;
    Ark_Int32 u32;
    Ark_Int32 f32;
};

typedef union GENERATED_Ark_EventCallbackArg GENERATED_Ark_EventCallbackArg;

typedef struct GENERATED_Ark_APICallbackMethod {
    Ark_Int32 (*CallInt) (Ark_VMContext vmContext, Ark_Int32 methodId, Ark_Int32 numArgs, GENERATED_Ark_EventCallbackArg* args);
} GENERATED_Ark_APICallbackMethod;

typedef struct GENERATED_Ark_UtilsModifier {
    Ark_Float32 (*getDensity) (Ark_Int32 deviceId);
    Ark_Float32 (*getFontScale) (Ark_Int32 deviceId);
    Ark_Float32 (*getDesignWidthScale) (Ark_Int32 deviceId);

} GENERATED_Ark_UtilsModifier;

typedef struct GENERATED_Ark_CustomNodeEvent {
    Ark_Int32 kind;
    Ark_Int32 extraParam;
    Ark_NativePointer canvas;
    Ark_Int32 data[8];
} GENERATED_Ark_CustomNodeEvent;


typedef struct GENERATED_Ark_APIEventSinglePointer {
    Ark_Int32 x;
    Ark_Int32 y;
    Ark_Int32 state; // 0 - down, 1 - up, 2 - move
} GENERATED_Ark_APIEventSinglePointer;

#define GENERATED_ARK_MULTIPOINTER_ARGS_COUNT 10

typedef struct GENERATED_Ark_APIEventMultiPointer {
    Ark_Int32 count;
    Ark_Int32 xs[GENERATED_ARK_MULTIPOINTER_ARGS_COUNT];
    Ark_Int32 ys[GENERATED_ARK_MULTIPOINTER_ARGS_COUNT];
    Ark_Int32 state[GENERATED_ARK_MULTIPOINTER_ARGS_COUNT];
} GENERATED_Ark_APIEventMultiPointer;


#define GENERATED_ARK_CALLBACK_ARGS_COUNT 12

typedef struct GENERATED_Ark_APIEventCallback {
    Ark_Int32 id;
    Ark_Int32 numArgs;
    Ark_Int32 continuationId;
    GENERATED_Ark_EventCallbackArg args[GENERATED_ARK_CALLBACK_ARGS_COUNT];
} GENERATED_Ark_APIEventCallback;

#define GENERATED_ARK_ASYNC_EVENT_COUNT 12

typedef struct GENERATED_Ark_APINodeAsyncEvent {
    /// used by c-api, sould be the first place.
    GENERATED_Ark_EventCallbackArg data[GENERATED_ARK_ASYNC_EVENT_COUNT];
    Ark_Int32 subKind; // Ark_EventSubKind actually
} GENERATED_Ark_APINodeAsyncEvent;

typedef struct GENERATED_Ark_APIEventTextInput {
    // used by c-api, should be the first place.
    Ark_Int64 nativeStringPtr;
    Ark_Int32 subKind; // Ark_EventSubKind actually
} GENERATED_Ark_APIEventTextInput;

typedef struct GENERATED_Ark_APIEventGestureAsyncEvent {
    Ark_Int32 subKind;
    Ark_Int32 repeat;
    Ark_Float32 x;
    Ark_Float32 y;
    Ark_Float32 angle;
    Ark_Float32 scale;
    Ark_Float32 pinchCenterX;
    Ark_Float32 pinchCenterY;
    Ark_Int32 speed;
    Ark_Int32 timestamp;
    Ark_Int32 source;
    Ark_Int32 pressure;
    Ark_Int32 tiltX;
    Ark_Int32 tiltY;
    Ark_Int32 sourceTool;
    Ark_Float32 velocityX;
    Ark_Float32 velocityY;
    Ark_Float32 velocity;
    void *rawPinterEvent;
} GENERATED_Ark_APIEventGestureAsyncEvent;

typedef struct GENERATED_Ark_TouchPoint {
    Ark_Int32 id;
    Ark_Int64 pressedTime;
    Ark_Float32 screenX;
    Ark_Float32 screenY;
    Ark_Float32 windowX;
    Ark_Float32 windowY;
    Ark_Float32 nodeX;
    Ark_Float32 nodeY;
    Ark_Float64 pressure;
    Ark_Float32 contactAreaWidth;
    Ark_Float32 contactAreaHeight;
    Ark_Float64 tiltX;
    Ark_Float64 tiltY;
    Ark_Float32 toolX;
    Ark_Float32 toolY;
    Ark_Float32 toolWidth;
    Ark_Float32 toolHeight;
    Ark_Float32 rawX;
    Ark_Float32 rawY;
    Ark_Int32 toolType;
} GENERATED_Ark_TouchPoint;

typedef enum {
    GENERATED_ARK_GESTURE_EVENT_ACTION_ACCEPT = 0x01,
    GENERATED_ARK_GESTURE_EVENT_ACTION_UPDATE = 0x02,
    GENERATED_ARK_GESTURE_EVENT_ACTION_END = 0x04,
    GENERATED_ARK_GESTURE_EVENT_ACTION_CANCEL = 0x08,
} GENERATED_Ark_GestureEventActionType;

typedef struct GENERATED_Ark_HistoryTouchEvent {
    Ark_Int32 action;
    Ark_Int32 sourceType;
    Ark_Int64 timeStamp;
    GENERATED_Ark_TouchPoint actionTouchPoint;
    GENERATED_Ark_TouchPoint* touchPointes;
    Ark_UInt32 touchPointSize;
} GENERATED_Ark_HistoryTouchEvent;

typedef struct GENERATED_Ark_TouchEvent {
    Ark_Int32 action;
    /** Time stamp of the current event */
    Ark_Int64 timeStamp;
    GENERATED_Ark_TouchPoint actionTouchPoint;
    GENERATED_Ark_TouchPoint* touchPoints;
    Ark_Int32 touchPointSize;
    GENERATED_Ark_HistoryTouchEvent* historyEvents;
    Ark_Int32 historySize;
    Ark_Int32 sourceType;

    /**
     * @brief Prevents events from bubbling further to the parent node for processing
     */

    Ark_Boolean stopPropagation;

    /**
     * @brief Block the current node's default event handling behavior, allowing events
     * to bubble up further.
     */
    Ark_Boolean preventDefault;

    Ark_Int32 subKind; // Ark_EventSubKind actually
    Ark_Int32 interceptResult;
} GENERATED_Ark_TouchEvent;

typedef struct GENERATED_Ark_MouseEvent {
    Ark_Int32 action;
    Ark_Int32 button;
    Ark_Int64 timeStamp;
    GENERATED_Ark_TouchPoint actionTouchPoint;
    Ark_Int32 subKind;
} GENERATED_Ark_MouseEvent;

typedef struct GENERATED_Ark_NodeEvent
{
    Ark_Int32 kind; // Actually GENERATED_Ark_EventCategory
    Ark_Int32 nodeId;
    Ark_Int64 extraParam;
    union {
        GENERATED_Ark_APIEventSinglePointer singlePointer;
        GENERATED_Ark_APIEventMultiPointer multiPointer;
        GENERATED_Ark_APIEventCallback callback;
        GENERATED_Ark_APINodeAsyncEvent componentAsyncEvent;
        GENERATED_Ark_APIEventTextInput textInputEvent;
        GENERATED_Ark_APIEventGestureAsyncEvent gestureAsyncEvent;
        GENERATED_Ark_TouchEvent touchEvent;
        GENERATED_Ark_MouseEvent mouseEvent;
    };
} GENERATED_Ark_NodeEvent;

typedef void (*GENERATED_EventReceiver)(GENERATED_Ark_NodeEvent* event);

typedef struct GENERATED_ArkUIBasicNodeAPI {
    Ark_Int32 version;

    /// Tree operations.
    Ark_NodeHandle (*createNode)(GENERATED_Ark_NodeType type, Ark_Int32 id, Ark_Int32 flags);

    Ark_NodeHandle (*getNodeByViewStack)();
    void (*disposeNode)(Ark_NodeHandle node);

    Ark_Int32 (*addChild)(Ark_NodeHandle parent, Ark_NodeHandle child);
    void (*removeChild)(Ark_NodeHandle parent, Ark_NodeHandle child);
    Ark_Int32 (*insertChildAfter)(Ark_NodeHandle parent, Ark_NodeHandle child, Ark_NodeHandle sibling);
    Ark_Int32 (*insertChildBefore)(Ark_NodeHandle parent, Ark_NodeHandle child, Ark_NodeHandle sibling);
    Ark_Int32 (*insertChildAt)(Ark_NodeHandle parent, Ark_NodeHandle child, Ark_Int32 position);

    // Commit attributes updates for node.
    void (*applyModifierFinish)(Ark_NodeHandle nodePtr);
    // the flag can combine different flag like Ark_DIRTY_FLAG_MEASURE | Ark_DIRTY_FLAG_RENDER
    void (*markDirty)(Ark_NodeHandle nodePtr, Ark_UInt32 dirtyFlag);
    Ark_Boolean (*isBuilderNode)(Ark_NodeHandle node);

    Ark_Float32 (*convertLengthMetricsUnit)(Ark_Float32 value, Ark_Int32 originUnit, Ark_Int32 targetUnit);
} GENERATED_ArkUIBasicNodeAPI;

typedef void (*GENERATED_CustomEventReceiver)(GENERATED_Ark_CustomNodeEvent* event);

typedef struct GENERATED_ArkUIExtendedNodeAPI {
    Ark_Int32 version;

    void (*setAppendGroupedLog)(void* pFunc);

    const GENERATED_Ark_UtilsModifier* (*getUtilsModifier)();

    void (*setCallbackMethod)(GENERATED_Ark_APICallbackMethod* method);

    // for ndk side, the custom node is not set in create.
    void (*setCustomMethodFlag)(Ark_NodeHandle node, Ark_Int32 flag);
    Ark_Int32 (*getCustomMethodFlag)(Ark_NodeHandle node);

    void (*registerCustomNodeAsyncEvent)(Ark_NodeHandle nodePtr, Ark_Int32 kind, void* extraParam);
    Ark_Int32(*unregisterCustomNodeAsyncEvent)(Ark_NodeHandle nodePtr, Ark_Int32 kind);
    void (*registerCustomNodeAsyncEventReceiver)(GENERATED_CustomEventReceiver eventReceiver);

    // setCustomCallback is without the context
    void (*setCustomCallback) (Ark_VMContext  vmContext, Ark_NodeHandle node, Ark_Int32 callbackId);
    // make void instead return type Ark_Int32
    Ark_Int32 (*measureLayoutAndDraw) (Ark_VMContext  vmContext, Ark_NodeHandle node);
    Ark_Int32 (*measureNode) (Ark_VMContext  vmContext, Ark_NodeHandle node, Ark_Float32* data);
    Ark_Int32 (*layoutNode) (Ark_VMContext  vmContext, Ark_NodeHandle node, Ark_Float32* data);
    Ark_Int32 (*drawNode) (Ark_VMContext  vmContext, Ark_NodeHandle node, Ark_Float32* data);
    void (*setAttachNodePtr) (Ark_NodeHandle node, void* value);
    void* (*getAttachNodePtr) (Ark_NodeHandle node);

    // may be better to use int in px unit
    void (*setMeasureWidth)(Ark_NodeHandle node, Ark_Int32 value);
    Ark_Int32 (*getMeasureWidth)(Ark_NodeHandle node);
    void (*setMeasureHeight)(Ark_NodeHandle node, Ark_Int32 value);
    Ark_Int32 (*getMeasureHeight)(Ark_NodeHandle node);
    void (*setX)(Ark_NodeHandle node, Ark_Int32 value);
    Ark_Int32 (*getX)(Ark_NodeHandle node);
    void (*setY)(Ark_NodeHandle node, Ark_Int32 value);
    Ark_Int32 (*getY)(Ark_NodeHandle node);

    void (*getLayoutConstraint)(Ark_NodeHandle node, Ark_Int32* value);
    void (*setAlignment)(Ark_NodeHandle node, Ark_Int32 value);
    Ark_Int32 (*getAlignment)(Ark_NodeHandle node);

    Ark_Int32 (*indexerChecker) (Ark_VMContext  vmContext, Ark_NodeHandle node);
    void (*setRangeUpdater)(Ark_NodeHandle node, Ark_Int32 updatedId);
    void (*setLazyItemIndexer) (Ark_VMContext  vmContext, Ark_NodeHandle node, Ark_Int32 indexerId);

    /// Vsync support
    Ark_PipelineContext (*getPipelineContext)(Ark_NodeHandle node);
    void (*setVsyncCallback)(Ark_VMContext  vmContext, Ark_PipelineContext pipelineContext, Ark_Int32 callbackId);
    void (*unblockVsyncWait)(Ark_VMContext  vmContext, Ark_PipelineContext pipelineContext);

    /// Events
    /**
     * Returns != 0 if an event was received,
     * fills in supplied buffer in such a case
     * Must not block, blocking is performed by
     * ArkoalaHostApi.waitForVsync().
    */
   Ark_Int32 (*checkEvent)(GENERATED_Ark_NodeEvent* event);
   /**
    * Add an event to the event queue, so that
    * it will be picked up later by checkEvent().
   */
  void (*sendEvent)(GENERATED_Ark_NodeEvent* event);
  void (*callContinuation)(Ark_Int32 continuationId, Ark_Int32 argCount, GENERATED_Ark_EventCallbackArg* args);
  void (*setChildTotalCount)(Ark_NodeHandle node, Ark_Int32 totalCount);

  /// Error reporting.
  void (*showCrash)(Ark_CharPtr message);

} GENERATED_ArkUIExtendedNodeAPI;


/**
 * An API to control an implementation. When making changes modifying binary
 * layout, i.e. adding new events - increase ARKUI_NODE_API_VERSION above for binary
 * layout checks.
 */
typedef struct GENERATED_ArkUIFullNodeAPI {
    Ark_Int32 version;
    const GENERATED_ArkUINodeModifiers* (*getNodeModifiers)();
    const GENERATED_ArkUIAccessors* (*getAccessors)();
    const GENERATED_ArkUIAnimation* (*getAnimation)();
    const GENERATED_ArkUINavigation* (*getNavigation)();
    const GENERATED_ArkUIGraphicsAPI* (*getGraphicsAPI)();
    const GENERATED_ArkUIEventsAPI* (*getEventsAPI)();
    const GENERATED_ArkUIExtendedNodeAPI* (*getExtendedAPI)();
    void (*setArkUIEventsAPI)(const GENERATED_ArkUIEventsAPI* api);
} GENERATED_ArkUIFullNodeAPI;

typedef struct GENERATED_ArkUIAnyAPI {
    Ark_Int32 version;
} GENERATED_ArkUIAnyAPI;



struct Ark_AnyAPI {
    Ark_Int32 version;
};

#ifdef __cplusplus
};
#endif

#endif  // GENERATED_FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_API_H

