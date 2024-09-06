
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

/* clang-format off */

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

typedef struct Opt_Int32 {
    enum Ark_Tag tag;
    Ark_Int32 value;
} Opt_Int32;
typedef struct Array_String {
    Ark_String* array;
    Ark_Int32 length;
} Array_String;
typedef struct Opt_Array_String {
    enum Ark_Tag tag;
    Array_String value;
} Opt_Array_String;
typedef struct Opt_String {
    enum Ark_Tag tag;
    Ark_String value;
} Opt_String;
typedef struct Opt_Number {
    enum Ark_Tag tag;
    Ark_Number value;
} Opt_Number;
typedef struct Opt_Length {
    enum Ark_Tag tag;
    Ark_Length value;
} Opt_Length;
typedef struct Ark_Resource {
    Ark_Number id;
    Ark_Number type;
    Ark_String moduleName;
    Ark_String bundleName;
    struct Opt_Array_String params;
} Ark_Resource;
typedef struct Opt_Resource {
    enum Ark_Tag tag;
    Ark_Resource value;
} Opt_Resource;
typedef Ark_Int32 Ark_ColoringStrategy;
typedef struct Opt_ColoringStrategy {
    enum Ark_Tag tag;
    Ark_ColoringStrategy value;
} Opt_ColoringStrategy;
typedef Ark_Int32 Ark_Color;
typedef struct Opt_Color {
    enum Ark_Tag tag;
    Ark_Color value;
} Opt_Color;
typedef struct Ark_Position {
    Opt_Length x;
    Opt_Length y;
} Ark_Position;
typedef struct Opt_Position {
    enum Ark_Tag tag;
    Ark_Position value;
} Opt_Position;
typedef struct Ark_BorderRadiuses {
    Opt_Length topLeft;
    Opt_Length topRight;
    Opt_Length bottomLeft;
    Opt_Length bottomRight;
} Ark_BorderRadiuses;
typedef struct Opt_BorderRadiuses {
    enum Ark_Tag tag;
    Ark_BorderRadiuses value;
} Opt_BorderRadiuses;
typedef struct Ark_Padding {
    Opt_Length top;
    Opt_Length right;
    Opt_Length bottom;
    Opt_Length left;
} Ark_Padding;
typedef struct Opt_Padding {
    enum Ark_Tag tag;
    Ark_Padding value;
} Opt_Padding;
typedef struct Tuple_Length_Length {
    Ark_Length value0;
    Ark_Length value1;
} Tuple_Length_Length;
typedef struct Opt_Tuple_Length_Length {
    enum Ark_Tag tag;
    Tuple_Length_Length value;
} Opt_Tuple_Length_Length;
typedef struct Opt_CustomObject {
    enum Ark_Tag tag;
    Ark_CustomObject value;
} Opt_CustomObject;
typedef struct Opt_Boolean {
    enum Ark_Tag tag;
    Ark_Boolean value;
} Opt_Boolean;
typedef struct Union_Number_Resource {
    Ark_Int32 selector;
    union {
        Ark_Number value0;
        struct Ark_Resource value1;
    };
} Union_Number_Resource;
typedef struct Opt_Union_Number_Resource {
    enum Ark_Tag tag;
    Union_Number_Resource value;
} Opt_Union_Number_Resource;
typedef struct Union_Color_String_Resource_ColoringStrategy {
    Ark_Int32 selector;
    union {
        Ark_Color value0;
        Ark_String value1;
        struct Ark_Resource value2;
        Ark_ColoringStrategy value3;
    };
} Union_Color_String_Resource_ColoringStrategy;
typedef struct Opt_Union_Color_String_Resource_ColoringStrategy {
    enum Ark_Tag tag;
    Union_Color_String_Resource_ColoringStrategy value;
} Opt_Union_Color_String_Resource_ColoringStrategy;
typedef Ark_Int32 Ark_ShadowType;
typedef struct Opt_ShadowType {
    enum Ark_Tag tag;
    Ark_ShadowType value;
} Opt_ShadowType;
typedef Ark_Int32 Ark_FontWeight;
typedef struct Opt_FontWeight {
    enum Ark_Tag tag;
    Ark_FontWeight value;
} Opt_FontWeight;
typedef struct Ark_Area {
    Ark_Length width;
    Ark_Length height;
    struct Ark_Position position;
    struct Ark_Position globalPosition;
} Ark_Area;
typedef struct Opt_Area {
    enum Ark_Tag tag;
    Ark_Area value;
} Opt_Area;
typedef struct Union_Length_Ark_BorderRadiuses {
    Ark_Int32 selector;
    union {
        Ark_Length value0;
        struct Ark_BorderRadiuses value1;
    };
} Union_Length_Ark_BorderRadiuses;
typedef struct Opt_Union_Length_BorderRadiuses {
    enum Ark_Tag tag;
    Union_Length_Ark_BorderRadiuses value;
} Opt_Union_Length_BorderRadiuses;
typedef struct Union_Length_Ark_Padding {
    Ark_Int32 selector;
    union {
        Ark_Length value0;
        struct Ark_Padding value1;
    };
} Union_Length_Ark_Padding;
typedef struct Opt_Union_Length_Padding {
    enum Ark_Tag tag;
    Union_Length_Ark_Padding value;
} Opt_Union_Length_Padding;
typedef struct Ark_LeadingMarginPlaceholder {
    Ark_CustomObject pixelMap;
    struct Tuple_Length_Length size;
} Ark_LeadingMarginPlaceholder;
typedef struct Opt_LeadingMarginPlaceholder {
    enum Ark_Tag tag;
    Ark_LeadingMarginPlaceholder value;
} Opt_LeadingMarginPlaceholder;
typedef Ark_Int32 Ark_TextDecorationStyle;
typedef struct Opt_TextDecorationStyle {
    enum Ark_Tag tag;
    Ark_TextDecorationStyle value;
} Opt_TextDecorationStyle;
typedef struct Ark_ResourceColor {
    Ark_Int32 selector;
    union {
        Ark_Color value0;
        Ark_Number value1;
        Ark_String value2;
        struct Ark_Resource value3;
    };
} Ark_ResourceColor;
typedef struct Opt_ResourceColor {
    enum Ark_Tag tag;
    Ark_ResourceColor value;
} Opt_ResourceColor;
typedef Ark_Int32 Ark_TextDecorationType;
typedef struct Opt_TextDecorationType {
    enum Ark_Tag tag;
    Ark_TextDecorationType value;
} Opt_TextDecorationType;
typedef struct Union_CustomObject_Ark_BorderRadiuses {
    Ark_Int32 selector;
    union {
        Ark_CustomObject value0;
        struct Ark_BorderRadiuses value1;
    };
} Union_CustomObject_Ark_BorderRadiuses;
typedef struct Opt_Union_CustomObject_BorderRadiuses {
    enum Ark_Tag tag;
    Union_CustomObject_Ark_BorderRadiuses value;
} Opt_Union_CustomObject_BorderRadiuses;
typedef struct Union_CustomObject_Ark_Padding {
    Ark_Int32 selector;
    union {
        Ark_CustomObject value0;
        struct Ark_Padding value1;
    };
} Union_CustomObject_Ark_Padding;
typedef struct Opt_Union_CustomObject_Padding {
    enum Ark_Tag tag;
    Union_CustomObject_Ark_Padding value;
} Opt_Union_CustomObject_Padding;
typedef struct Array_ShadowOptions {
    struct Ark_ShadowOptions* array;
    Ark_Int32 length;
} Array_ShadowOptions;
typedef struct Opt_Array_ShadowOptions {
    enum Ark_Tag tag;
    Array_ShadowOptions value;
} Opt_Array_ShadowOptions;
typedef struct Ark_ShadowOptions {
    struct Union_Number_Resource radius;
    Opt_ShadowType type;
    struct Opt_Union_Color_String_Resource_ColoringStrategy color;
    struct Opt_Union_Number_Resource offsetX;
    struct Opt_Union_Number_Resource offsetY;
    Opt_Boolean fill;
} Ark_ShadowOptions;
typedef struct Opt_ShadowOptions {
    enum Ark_Tag tag;
    Ark_ShadowOptions value;
} Opt_ShadowOptions;
typedef Ark_Materialized Ark_ICurve;
typedef struct Opt_ICurve {
    enum Ark_Tag tag;
    Ark_ICurve value;
} Opt_ICurve;
typedef Ark_Int32 Ark_Curve;
typedef struct Opt_Curve {
    enum Ark_Tag tag;
    Ark_Curve value;
} Opt_Curve;
typedef Ark_Int32 Ark_FontStyle;
typedef struct Opt_FontStyle {
    enum Ark_Tag tag;
    Ark_FontStyle value;
} Opt_FontStyle;
typedef struct Union_String_Resource {
    Ark_Int32 selector;
    union {
        Ark_String value0;
        struct Ark_Resource value1;
    };
} Union_String_Resource;
typedef struct Opt_Union_String_Resource {
    enum Ark_Tag tag;
    Union_String_Resource value;
} Opt_Union_String_Resource;
typedef struct Union_FontWeight_Number_String {
    Ark_Int32 selector;
    union {
        Ark_FontWeight value0;
        Ark_Number value1;
        Ark_String value2;
    };
} Union_FontWeight_Number_String;
typedef struct Opt_Union_FontWeight_Number_String {
    enum Ark_Tag tag;
    Union_FontWeight_Number_String value;
} Opt_Union_FontWeight_Number_String;
typedef struct Ark_ResourceStr {
    Ark_Int32 selector;
    union {
        Ark_String value0;
        struct Ark_Resource value1;
    };
} Ark_ResourceStr;
typedef struct Opt_ResourceStr {
    enum Ark_Tag tag;
    Ark_ResourceStr value;
} Opt_ResourceStr;
typedef struct Ark_CommonMethod {
    void *handle;
} Ark_CommonMethod;
typedef struct Opt_CommonMethod {
    enum Ark_Tag tag;
    Ark_CommonMethod value;
} Opt_CommonMethod;
typedef Ark_Materialized Ark_TextBaseController;
typedef struct Opt_TextBaseController {
    enum Ark_Tag tag;
    Ark_TextBaseController value;
} Opt_TextBaseController;
typedef struct Opt_Undefined {
    enum Ark_Tag tag;
    Ark_Undefined value;
} Opt_Undefined;
typedef struct Opt_Function {
    enum Ark_Tag tag;
    Ark_Function value;
} Opt_Function;
typedef struct Ark_GridRowSizeOption {
    Opt_Length xs;
    Opt_Length sm;
    Opt_Length md;
    Opt_Length lg;
    Opt_Length xl;
    Opt_Length xxl;
} Ark_GridRowSizeOption;
typedef struct Opt_GridRowSizeOption {
    enum Ark_Tag tag;
    Ark_GridRowSizeOption value;
} Opt_GridRowSizeOption;
typedef Ark_Materialized Ark_CanvasPattern;
typedef struct Opt_CanvasPattern {
    enum Ark_Tag tag;
    Ark_CanvasPattern value;
} Opt_CanvasPattern;
typedef Ark_Materialized Ark_CanvasGradient;
typedef struct Opt_CanvasGradient {
    enum Ark_Tag tag;
    Ark_CanvasGradient value;
} Opt_CanvasGradient;
typedef Ark_Int32 Ark_SheetSize;
typedef struct Opt_SheetSize {
    enum Ark_Tag tag;
    Ark_SheetSize value;
} Opt_SheetSize;
typedef Ark_Int32 Ark_SourceTool;
typedef struct Opt_SourceTool {
    enum Ark_Tag tag;
    Ark_SourceTool value;
} Opt_SourceTool;
typedef Ark_Int32 Ark_SourceType;
typedef struct Opt_SourceType {
    enum Ark_Tag tag;
    Ark_SourceType value;
} Opt_SourceType;
typedef struct Ark_EventTarget {
    struct Ark_Area area;
} Ark_EventTarget;
typedef struct Opt_EventTarget {
    enum Ark_Tag tag;
    Ark_EventTarget value;
} Opt_EventTarget;
typedef struct Ark_RichEditorLayoutStyle {
    struct Opt_Union_Length_Padding margin;
    struct Opt_Union_Length_BorderRadiuses borderRadius;
} Ark_RichEditorLayoutStyle;
typedef struct Opt_RichEditorLayoutStyle {
    enum Ark_Tag tag;
    Ark_RichEditorLayoutStyle value;
} Opt_RichEditorLayoutStyle;
typedef Ark_Int32 Ark_ImageFit;
typedef struct Opt_ImageFit {
    enum Ark_Tag tag;
    Ark_ImageFit value;
} Opt_ImageFit;
typedef Ark_Int32 Ark_ImageSpanAlignment;
typedef struct Opt_ImageSpanAlignment {
    enum Ark_Tag tag;
    Ark_ImageSpanAlignment value;
} Opt_ImageSpanAlignment;
typedef struct Tuple_Number_Number {
    Ark_Number value0;
    Ark_Number value1;
} Tuple_Number_Number;
typedef struct Opt_Tuple_Number_Number {
    enum Ark_Tag tag;
    Tuple_Number_Number value;
} Opt_Tuple_Number_Number;
typedef Ark_Int32 Ark_LineBreakStrategy;
typedef struct Opt_LineBreakStrategy {
    enum Ark_Tag tag;
    Ark_LineBreakStrategy value;
} Opt_LineBreakStrategy;
typedef Ark_Int32 Ark_WordBreak;
typedef struct Opt_WordBreak {
    enum Ark_Tag tag;
    Ark_WordBreak value;
} Opt_WordBreak;
typedef struct Union_Length_LeadingMarginPlaceholder {
    Ark_Int32 selector;
    union {
        Ark_Length value0;
        struct Ark_LeadingMarginPlaceholder value1;
    };
} Union_Length_LeadingMarginPlaceholder;
typedef struct Opt_Union_Length_LeadingMarginPlaceholder {
    enum Ark_Tag tag;
    Union_Length_LeadingMarginPlaceholder value;
} Opt_Union_Length_LeadingMarginPlaceholder;
typedef Ark_Int32 Ark_TextAlign;
typedef struct Opt_TextAlign {
    enum Ark_Tag tag;
    Ark_TextAlign value;
} Opt_TextAlign;
typedef Ark_Int32 Ark_SymbolRenderingStrategy;
typedef struct Opt_SymbolRenderingStrategy {
    enum Ark_Tag tag;
    Ark_SymbolRenderingStrategy value;
} Opt_SymbolRenderingStrategy;
typedef Ark_Int32 Ark_SymbolEffectStrategy;
typedef struct Opt_SymbolEffectStrategy {
    enum Ark_Tag tag;
    Ark_SymbolEffectStrategy value;
} Opt_SymbolEffectStrategy;
typedef struct Union_Number_FontWeight_String {
    Ark_Int32 selector;
    union {
        Ark_Number value0;
        Ark_FontWeight value1;
        Ark_String value2;
    };
} Union_Number_FontWeight_String;
typedef struct Opt_Union_Number_FontWeight_String {
    enum Ark_Tag tag;
    Union_Number_FontWeight_String value;
} Opt_Union_Number_FontWeight_String;
typedef struct Array_Ark_ResourceColor {
    struct Ark_ResourceColor* array;
    Ark_Int32 length;
} Array_Ark_ResourceColor;
typedef struct Opt_Array_ResourceColor {
    enum Ark_Tag tag;
    Array_Ark_ResourceColor value;
} Opt_Array_ResourceColor;
typedef struct Union_Number_String_Resource {
    Ark_Int32 selector;
    union {
        Ark_Number value0;
        Ark_String value1;
        struct Ark_Resource value2;
    };
} Union_Number_String_Resource;
typedef struct Opt_Union_Number_String_Resource {
    enum Ark_Tag tag;
    Union_Number_String_Resource value;
} Opt_Union_Number_String_Resource;
typedef struct Ark_DecorationStyleResult {
    Ark_TextDecorationType type;
    struct Ark_ResourceColor color;
    Opt_TextDecorationStyle style;
} Ark_DecorationStyleResult;
typedef struct Opt_DecorationStyleResult {
    enum Ark_Tag tag;
    Ark_DecorationStyleResult value;
} Opt_DecorationStyleResult;
typedef struct Ark_TextBackgroundStyle {
    struct Opt_ResourceColor color;
    struct Opt_Union_Length_BorderRadiuses radius;
} Ark_TextBackgroundStyle;
typedef struct Opt_TextBackgroundStyle {
    enum Ark_Tag tag;
    Ark_TextBackgroundStyle value;
} Opt_TextBackgroundStyle;
typedef struct Union_Number_LeadingMarginPlaceholder {
    Ark_Int32 selector;
    union {
        Ark_Number value0;
        struct Ark_LeadingMarginPlaceholder value1;
    };
} Union_Number_LeadingMarginPlaceholder;
typedef struct Opt_Union_Number_LeadingMarginPlaceholder {
    enum Ark_Tag tag;
    Union_Number_LeadingMarginPlaceholder value;
} Opt_Union_Number_LeadingMarginPlaceholder;
typedef Ark_Int32 Ark_TextOverflow;
typedef struct Opt_TextOverflow {
    enum Ark_Tag tag;
    Ark_TextOverflow value;
} Opt_TextOverflow;
typedef struct Ark_ImageAttachmentLayoutStyle {
    struct Opt_Union_CustomObject_Padding margin;
    struct Opt_Union_CustomObject_Padding padding;
    struct Opt_Union_CustomObject_BorderRadiuses borderRadius;
} Ark_ImageAttachmentLayoutStyle;
typedef struct Opt_ImageAttachmentLayoutStyle {
    enum Ark_Tag tag;
    Ark_ImageAttachmentLayoutStyle value;
} Opt_ImageAttachmentLayoutStyle;
typedef struct Ark_SizeOptions {
    Opt_Length width;
    Opt_Length height;
} Ark_SizeOptions;
typedef struct Opt_SizeOptions {
    enum Ark_Tag tag;
    Ark_SizeOptions value;
} Opt_SizeOptions;
typedef struct Ark_RichEditorRange {
    Opt_Number start;
    Opt_Number end;
} Ark_RichEditorRange;
typedef struct Opt_RichEditorRange {
    enum Ark_Tag tag;
    Ark_RichEditorRange value;
} Opt_RichEditorRange;
typedef struct Union_Number_String {
    Ark_Int32 selector;
    union {
        Ark_Number value0;
        Ark_String value1;
    };
} Union_Number_String;
typedef struct Opt_Union_Number_String {
    enum Ark_Tag tag;
    Union_Number_String value;
} Opt_Union_Number_String;
typedef struct Union_ShadowOptions_Array_ShadowOptions {
    Ark_Int32 selector;
    union {
        struct Ark_ShadowOptions value0;
        struct Array_ShadowOptions value1;
    };
} Union_ShadowOptions_Array_ShadowOptions;
typedef struct Opt_Union_ShadowOptions_Array_ShadowOptions {
    enum Ark_Tag tag;
    Union_ShadowOptions_Array_ShadowOptions value;
} Opt_Union_ShadowOptions_Array_ShadowOptions;
typedef struct Ark_DecorationStyleInterface {
    Ark_TextDecorationType type;
    struct Opt_ResourceColor color;
    Opt_TextDecorationStyle style;
} Ark_DecorationStyleInterface;
typedef struct Opt_DecorationStyleInterface {
    enum Ark_Tag tag;
    Ark_DecorationStyleInterface value;
} Opt_DecorationStyleInterface;
typedef struct Union_Length_Number {
    Ark_Int32 selector;
    union {
        Ark_Length value0;
        Ark_Number value1;
    };
} Union_Length_Number;
typedef struct Opt_Union_Length_Number {
    enum Ark_Tag tag;
    Union_Length_Number value;
} Opt_Union_Length_Number;
typedef struct Union_Curve_ICurve {
    Ark_Int32 selector;
    union {
        Ark_Curve value0;
        Ark_ICurve value1;
    };
} Union_Curve_ICurve;
typedef struct Opt_Union_Curve_ICurve {
    enum Ark_Tag tag;
    Union_Curve_ICurve value;
} Opt_Union_Curve_ICurve;
typedef struct Ark_LocalizedPadding {
    Opt_CustomObject top;
    Opt_CustomObject end;
    Opt_CustomObject bottom;
    Opt_CustomObject start;
} Ark_LocalizedPadding;
typedef struct Opt_LocalizedPadding {
    enum Ark_Tag tag;
    Ark_LocalizedPadding value;
} Opt_LocalizedPadding;
typedef struct Ark_Font {
    Opt_Length size;
    struct Opt_Union_FontWeight_Number_String weight;
    struct Opt_Union_String_Resource family;
    Opt_FontStyle style;
} Ark_Font;
typedef struct Opt_Font {
    enum Ark_Tag tag;
    Ark_Font value;
} Opt_Font;
typedef Ark_Int32 Ark_TextHeightAdaptivePolicy;
typedef struct Opt_TextHeightAdaptivePolicy {
    enum Ark_Tag tag;
    Ark_TextHeightAdaptivePolicy value;
} Opt_TextHeightAdaptivePolicy;
typedef struct Union_Number_Ark_ResourceStr {
    Ark_Int32 selector;
    union {
        Ark_Number value0;
        struct Ark_ResourceStr value1;
    };
} Union_Number_Ark_ResourceStr;
typedef struct Opt_Union_Number_ResourceStr {
    enum Ark_Tag tag;
    Union_Number_Ark_ResourceStr value;
} Opt_Union_Number_ResourceStr;
typedef struct Ark_CommonShapeMethod {
    void *handle;
} Ark_CommonShapeMethod;
typedef struct Opt_CommonShapeMethod {
    enum Ark_Tag tag;
    Ark_CommonShapeMethod value;
} Opt_CommonShapeMethod;
typedef Ark_Materialized Ark_TextEditControllerEx;
typedef struct Opt_TextEditControllerEx {
    enum Ark_Tag tag;
    Ark_TextEditControllerEx value;
} Opt_TextEditControllerEx;
typedef struct Array_CustomObject {
    Ark_CustomObject* array;
    Ark_Int32 length;
} Array_CustomObject;
typedef struct Opt_Array_CustomObject {
    enum Ark_Tag tag;
    Array_CustomObject value;
} Opt_Array_CustomObject;
typedef Ark_Int32 Ark_TitleHeight;
typedef struct Opt_TitleHeight {
    enum Ark_Tag tag;
    Ark_TitleHeight value;
} Opt_TitleHeight;
typedef struct Ark_CustomBuilder {
    Ark_Int32 selector;
    union {
        struct Ark_Function value0;
        Ark_Undefined value1;
    };
} Ark_CustomBuilder;
typedef struct Opt_CustomBuilder {
    enum Ark_Tag tag;
    Ark_CustomBuilder value;
} Opt_CustomBuilder;
typedef struct Union_Length_GridRowSizeOption {
    Ark_Int32 selector;
    union {
        Ark_Length value0;
        struct Ark_GridRowSizeOption value1;
    };
} Union_Length_GridRowSizeOption;
typedef struct Opt_Union_Length_GridRowSizeOption {
    enum Ark_Tag tag;
    Union_Length_GridRowSizeOption value;
} Opt_Union_Length_GridRowSizeOption;
typedef struct Array_Tuple_Ark_ResourceColor_Number {
    struct Tuple_Ark_ResourceColor_Number* array;
    Ark_Int32 length;
} Array_Tuple_Ark_ResourceColor_Number;
typedef struct Opt_Array_Tuple_ResourceColor_Number {
    enum Ark_Tag tag;
    Array_Tuple_Ark_ResourceColor_Number value;
} Opt_Array_Tuple_ResourceColor_Number;
typedef Ark_Int32 Ark_GradientDirection;
typedef struct Opt_GradientDirection {
    enum Ark_Tag tag;
    Ark_GradientDirection value;
} Opt_GradientDirection;
typedef struct Ark_CanvasTextBaseline {
    Ark_Int32 selector;
    union {
        struct Ark_String value0;
        struct Ark_String value1;
        struct Ark_String value2;
        struct Ark_String value3;
        struct Ark_String value4;
        struct Ark_String value5;
    };
} Ark_CanvasTextBaseline;
typedef struct Opt_CanvasTextBaseline {
    enum Ark_Tag tag;
    Ark_CanvasTextBaseline value;
} Opt_CanvasTextBaseline;
typedef struct Ark_CanvasTextAlign {
    Ark_Int32 selector;
    union {
        struct Ark_String value0;
        struct Ark_String value1;
        struct Ark_String value2;
        struct Ark_String value3;
        struct Ark_String value4;
    };
} Ark_CanvasTextAlign;
typedef struct Opt_CanvasTextAlign {
    enum Ark_Tag tag;
    Ark_CanvasTextAlign value;
} Opt_CanvasTextAlign;
typedef struct Ark_CanvasDirection {
    Ark_Int32 selector;
    union {
        struct Ark_String value0;
        struct Ark_String value1;
        struct Ark_String value2;
    };
} Ark_CanvasDirection;
typedef struct Opt_CanvasDirection {
    enum Ark_Tag tag;
    Ark_CanvasDirection value;
} Opt_CanvasDirection;
typedef struct Ark_CanvasLineJoin {
    Ark_Int32 selector;
    union {
        struct Ark_String value0;
        struct Ark_String value1;
        struct Ark_String value2;
    };
} Ark_CanvasLineJoin;
typedef struct Opt_CanvasLineJoin {
    enum Ark_Tag tag;
    Ark_CanvasLineJoin value;
} Opt_CanvasLineJoin;
typedef struct Ark_CanvasLineCap {
    Ark_Int32 selector;
    union {
        struct Ark_String value0;
        struct Ark_String value1;
        struct Ark_String value2;
    };
} Ark_CanvasLineCap;
typedef struct Opt_CanvasLineCap {
    enum Ark_Tag tag;
    Ark_CanvasLineCap value;
} Opt_CanvasLineCap;
typedef struct Ark_ImageSmoothingQuality {
    Ark_Int32 selector;
    union {
        struct Ark_String value0;
        struct Ark_String value1;
        struct Ark_String value2;
    };
} Ark_ImageSmoothingQuality;
typedef struct Opt_ImageSmoothingQuality {
    enum Ark_Tag tag;
    Ark_ImageSmoothingQuality value;
} Opt_ImageSmoothingQuality;
typedef struct Union_String_Number_CanvasGradient_CanvasPattern {
    Ark_Int32 selector;
    union {
        Ark_String value0;
        Ark_Number value1;
        Ark_CanvasGradient value2;
        Ark_CanvasPattern value3;
    };
} Union_String_Number_CanvasGradient_CanvasPattern;
typedef struct Opt_Union_String_Number_CanvasGradient_CanvasPattern {
    enum Ark_Tag tag;
    Union_String_Number_CanvasGradient_CanvasPattern value;
} Opt_Union_String_Number_CanvasGradient_CanvasPattern;
typedef Ark_Materialized Ark_CanvasPath;
typedef struct Opt_CanvasPath {
    enum Ark_Tag tag;
    Ark_CanvasPath value;
} Opt_CanvasPath;
typedef Ark_Int32 Ark_BadgePosition;
typedef struct Opt_BadgePosition {
    enum Ark_Tag tag;
    Ark_BadgePosition value;
} Opt_BadgePosition;
typedef Ark_Int32 Ark_BorderStyle;
typedef struct Opt_BorderStyle {
    enum Ark_Tag tag;
    Ark_BorderStyle value;
} Opt_BorderStyle;
typedef struct Union_SheetSize_Length {
    Ark_Int32 selector;
    union {
        Ark_SheetSize value0;
        Ark_Length value1;
    };
} Union_SheetSize_Length;
typedef struct Opt_Union_SheetSize_Length {
    enum Ark_Tag tag;
    Union_SheetSize_Length value;
} Opt_Union_SheetSize_Length;
typedef struct Ark_TransitionEffect {
    void *handle;
} Ark_TransitionEffect;
typedef struct Opt_TransitionEffect {
    enum Ark_Tag tag;
    Ark_TransitionEffect value;
} Opt_TransitionEffect;
typedef struct Ark_LocalizedBorderRadiuses {
    Opt_CustomObject topStart;
    Opt_CustomObject topEnd;
    Opt_CustomObject bottomStart;
    Opt_CustomObject bottomEnd;
} Ark_LocalizedBorderRadiuses;
typedef struct Opt_LocalizedBorderRadiuses {
    enum Ark_Tag tag;
    Ark_LocalizedBorderRadiuses value;
} Opt_LocalizedBorderRadiuses;
typedef Ark_Int32 Ark_MenuPreviewMode;
typedef struct Opt_MenuPreviewMode {
    enum Ark_Tag tag;
    Ark_MenuPreviewMode value;
} Opt_MenuPreviewMode;
typedef Ark_Int32 Ark_ShadowStyle;
typedef struct Opt_ShadowStyle {
    enum Ark_Tag tag;
    Ark_ShadowStyle value;
} Opt_ShadowStyle;
typedef struct Literal_Ark_ResourceColor_color {
    struct Ark_ResourceColor color;
} Literal_Ark_ResourceColor_color;
typedef struct Opt_Literal_ResourceColor_color {
    enum Ark_Tag tag;
    Literal_Ark_ResourceColor_color value;
} Opt_Literal_ResourceColor_color;
typedef Ark_Int32 Ark_OutlineStyle;
typedef struct Opt_OutlineStyle {
    enum Ark_Tag tag;
    Ark_OutlineStyle value;
} Opt_OutlineStyle;
typedef struct Array_TouchObject {
    struct Ark_TouchObject* array;
    Ark_Int32 length;
} Array_TouchObject;
typedef struct Opt_Array_TouchObject {
    enum Ark_Tag tag;
    Array_TouchObject value;
} Opt_Array_TouchObject;
typedef Ark_Int32 Ark_TouchType;
typedef struct Opt_TouchType {
    enum Ark_Tag tag;
    Ark_TouchType value;
} Opt_TouchType;
typedef struct Ark_BaseEvent {
    struct Ark_EventTarget target;
    Ark_Number timestamp;
    Ark_SourceType source;
    Opt_Number axisHorizontal;
    Opt_Number axisVertical;
    Ark_Number pressure;
    Ark_Number tiltX;
    Ark_Number tiltY;
    Ark_SourceTool sourceTool;
    Opt_Number deviceId;
} Ark_BaseEvent;
typedef struct Opt_BaseEvent {
    enum Ark_Tag tag;
    Ark_BaseEvent value;
} Opt_BaseEvent;
typedef struct Map_String_String {
    Ark_Int32 size;
    Ark_String* keys;
    Ark_String* values;
} Map_String_String;
typedef struct Opt_Map_String_String {
    enum Ark_Tag tag;
    Map_String_String value;
} Opt_Map_String_String;
typedef Ark_Materialized Ark_WebResourceRequest;
typedef struct Opt_WebResourceRequest {
    enum Ark_Tag tag;
    Ark_WebResourceRequest value;
} Opt_WebResourceRequest;
typedef struct Ark_RichEditorImageSpanStyleResult {
    struct Tuple_Number_Number size;
    Ark_ImageSpanAlignment verticalAlign;
    Ark_ImageFit objectFit;
    struct Opt_RichEditorLayoutStyle layoutStyle;
} Ark_RichEditorImageSpanStyleResult;
typedef struct Opt_RichEditorImageSpanStyleResult {
    enum Ark_Tag tag;
    Ark_RichEditorImageSpanStyleResult value;
} Opt_RichEditorImageSpanStyleResult;
typedef struct Ark_RichEditorSpanPosition {
    Ark_Number spanIndex;
    struct Tuple_Number_Number spanRange;
} Ark_RichEditorSpanPosition;
typedef struct Opt_RichEditorSpanPosition {
    enum Ark_Tag tag;
    Ark_RichEditorSpanPosition value;
} Opt_RichEditorSpanPosition;
typedef struct Ark_RichEditorParagraphStyle {
    Opt_TextAlign textAlign;
    struct Opt_Union_Length_LeadingMarginPlaceholder leadingMargin;
    Opt_WordBreak wordBreak;
    Opt_LineBreakStrategy lineBreakStrategy;
} Ark_RichEditorParagraphStyle;
typedef struct Opt_RichEditorParagraphStyle {
    enum Ark_Tag tag;
    Ark_RichEditorParagraphStyle value;
} Opt_RichEditorParagraphStyle;
typedef struct Ark_RichEditorSymbolSpanStyle {
    struct Opt_Union_Number_String_Resource fontSize;
    struct Opt_Array_ResourceColor fontColor;
    struct Opt_Union_Number_FontWeight_String fontWeight;
    Opt_SymbolEffectStrategy effectStrategy;
    Opt_SymbolRenderingStrategy renderingStrategy;
} Ark_RichEditorSymbolSpanStyle;
typedef struct Opt_RichEditorSymbolSpanStyle {
    enum Ark_Tag tag;
    Ark_RichEditorSymbolSpanStyle value;
} Opt_RichEditorSymbolSpanStyle;
typedef struct Ark_RichEditorTextStyleResult {
    struct Ark_ResourceColor fontColor;
    Ark_Number fontSize;
    Ark_FontStyle fontStyle;
    Ark_Number fontWeight;
    Ark_String fontFamily;
    struct Ark_DecorationStyleResult decoration;
    struct Opt_Array_ShadowOptions textShadow;
    Opt_Number letterSpacing;
    Opt_Number lineHeight;
    Opt_String fontFeature;
} Ark_RichEditorTextStyleResult;
typedef struct Opt_RichEditorTextStyleResult {
    enum Ark_Tag tag;
    Ark_RichEditorTextStyleResult value;
} Opt_RichEditorTextStyleResult;
typedef struct Ark_BackgroundColorStyle {
    struct Ark_TextBackgroundStyle textBackgroundStyle;
} Ark_BackgroundColorStyle;
typedef struct Opt_BackgroundColorStyle {
    enum Ark_Tag tag;
    Ark_BackgroundColorStyle value;
} Opt_BackgroundColorStyle;
typedef struct Ark_UserDataSpan {
    void *handle;
} Ark_UserDataSpan;
typedef struct Opt_UserDataSpan {
    enum Ark_Tag tag;
    Ark_UserDataSpan value;
} Opt_UserDataSpan;
typedef Ark_Materialized Ark_CustomSpan;
typedef struct Opt_CustomSpan {
    enum Ark_Tag tag;
    Ark_CustomSpan value;
} Opt_CustomSpan;
typedef struct Ark_UrlStyle {
    Ark_String url;
} Ark_UrlStyle;
typedef struct Opt_UrlStyle {
    enum Ark_Tag tag;
    Ark_UrlStyle value;
} Opt_UrlStyle;
typedef struct Ark_LineHeightStyle {
    Ark_Number lineHeight;
} Ark_LineHeightStyle;
typedef struct Opt_LineHeightStyle {
    enum Ark_Tag tag;
    Ark_LineHeightStyle value;
} Opt_LineHeightStyle;
typedef struct Ark_ParagraphStyle {
    Opt_TextAlign textAlign;
    Opt_Number textIndent;
    Opt_Number maxLines;
    Opt_TextOverflow overflow;
    Opt_WordBreak wordBreak;
    struct Opt_Union_Number_LeadingMarginPlaceholder leadingMargin;
} Ark_ParagraphStyle;
typedef struct Opt_ParagraphStyle {
    enum Ark_Tag tag;
    Ark_ParagraphStyle value;
} Opt_ParagraphStyle;
typedef struct Ark_ImageAttachment {
    Ark_CustomObject value;
    struct Opt_SizeOptions size;
    Opt_ImageSpanAlignment verticalAlign;
    Opt_ImageFit objectFit;
    struct Opt_ImageAttachmentLayoutStyle layoutStyle;
} Ark_ImageAttachment;
typedef struct Opt_ImageAttachment {
    enum Ark_Tag tag;
    Ark_ImageAttachment value;
} Opt_ImageAttachment;
typedef struct Ark_GestureStyle {
    void *handle;
} Ark_GestureStyle;
typedef struct Opt_GestureStyle {
    enum Ark_Tag tag;
    Ark_GestureStyle value;
} Opt_GestureStyle;
typedef struct Ark_TextShadowStyle {
    struct Array_ShadowOptions textShadow;
} Ark_TextShadowStyle;
typedef struct Opt_TextShadowStyle {
    enum Ark_Tag tag;
    Ark_TextShadowStyle value;
} Opt_TextShadowStyle;
typedef struct Ark_LetterSpacingStyle {
    Ark_Number letterSpacing;
} Ark_LetterSpacingStyle;
typedef struct Opt_LetterSpacingStyle {
    enum Ark_Tag tag;
    Ark_LetterSpacingStyle value;
} Opt_LetterSpacingStyle;
typedef struct Ark_BaselineOffsetStyle {
    Ark_Number baselineOffset;
} Ark_BaselineOffsetStyle;
typedef struct Opt_BaselineOffsetStyle {
    enum Ark_Tag tag;
    Ark_BaselineOffsetStyle value;
} Opt_BaselineOffsetStyle;
typedef struct Ark_DecorationStyle {
    Ark_TextDecorationType type;
    struct Opt_ResourceColor color;
    Opt_TextDecorationStyle style;
} Ark_DecorationStyle;
typedef struct Opt_DecorationStyle {
    enum Ark_Tag tag;
    Ark_DecorationStyle value;
} Opt_DecorationStyle;
typedef struct Ark_TextStyle {
    Opt_WordBreak wordBreak;
} Ark_TextStyle;
typedef struct Opt_TextStyle {
    enum Ark_Tag tag;
    Ark_TextStyle value;
} Opt_TextStyle;
typedef struct Ark_RichEditorSpanStyleOptions {
    Opt_Number start;
    Opt_Number end;
} Ark_RichEditorSpanStyleOptions;
typedef struct Opt_RichEditorSpanStyleOptions {
    enum Ark_Tag tag;
    Ark_RichEditorSpanStyleOptions value;
} Opt_RichEditorSpanStyleOptions;
typedef struct Ark_RichEditorImageSpanStyle {
    struct Opt_Tuple_Length_Length size;
    Opt_ImageSpanAlignment verticalAlign;
    Opt_ImageFit objectFit;
    struct Opt_RichEditorLayoutStyle layoutStyle;
} Ark_RichEditorImageSpanStyle;
typedef struct Opt_RichEditorImageSpanStyle {
    enum Ark_Tag tag;
    Ark_RichEditorImageSpanStyle value;
} Opt_RichEditorImageSpanStyle;
typedef struct Ark_RichEditorTextStyle {
    struct Opt_ResourceColor fontColor;
    struct Opt_Union_Length_Number fontSize;
    Opt_FontStyle fontStyle;
    struct Opt_Union_Number_FontWeight_String fontWeight;
    struct Opt_ResourceStr fontFamily;
    struct Opt_DecorationStyleInterface decoration;
    struct Opt_Union_ShadowOptions_Array_ShadowOptions textShadow;
    struct Opt_Union_Number_String letterSpacing;
    struct Opt_Union_Number_String_Resource lineHeight;
    Opt_String fontFeature;
} Ark_RichEditorTextStyle;
typedef struct Opt_RichEditorTextStyle {
    enum Ark_Tag tag;
    Ark_RichEditorTextStyle value;
} Opt_RichEditorTextStyle;
typedef struct Ark_ScrollAnimationOptions {
    Opt_Number duration;
    struct Opt_Union_Curve_ICurve curve;
    Opt_Boolean canOverScroll;
} Ark_ScrollAnimationOptions;
typedef struct Opt_ScrollAnimationOptions {
    enum Ark_Tag tag;
    Ark_ScrollAnimationOptions value;
} Opt_ScrollAnimationOptions;
typedef Ark_Materialized Ark_RelativeIndexable;
typedef struct Opt_RelativeIndexable {
    enum Ark_Tag tag;
    Ark_RelativeIndexable value;
} Opt_RelativeIndexable;
typedef struct Union_String_CustomObject_Resource {
    Ark_Int32 selector;
    union {
        Ark_String value0;
        Ark_CustomObject value1;
        struct Ark_Resource value2;
    };
} Union_String_CustomObject_Resource;
typedef struct Opt_Union_String_CustomObject_Resource {
    enum Ark_Tag tag;
    Union_String_CustomObject_Resource value;
} Opt_Union_String_CustomObject_Resource;
typedef Ark_Materialized Ark_ImageAnalyzerController;
typedef struct Opt_ImageAnalyzerController {
    enum Ark_Tag tag;
    Ark_ImageAnalyzerController value;
} Opt_ImageAnalyzerController;
typedef int32_t Ark_ImageAnalyzerType;
typedef struct Array_ImageAnalyzerType {
    Ark_ImageAnalyzerType* array;
    Ark_Int32 length;
} Array_ImageAnalyzerType;
typedef int32_t Ark_ImageAnalyzerType;
typedef struct Opt_Array_ImageAnalyzerType {
    enum Ark_Tag tag;
    Array_ImageAnalyzerType value;
} Opt_Array_ImageAnalyzerType;
typedef Ark_Int32 Ark_NestedScrollMode;
typedef struct Opt_NestedScrollMode {
    enum Ark_Tag tag;
    Ark_NestedScrollMode value;
} Opt_NestedScrollMode;
typedef Ark_Materialized Ark_WebController;
typedef struct Opt_WebController {
    enum Ark_Tag tag;
    Ark_WebController value;
} Opt_WebController;
typedef Ark_Int32 Ark_PlaybackSpeed;
typedef struct Opt_PlaybackSpeed {
    enum Ark_Tag tag;
    Ark_PlaybackSpeed value;
} Opt_PlaybackSpeed;
typedef struct Array_Number {
    Ark_Number* array;
    Ark_Int32 length;
} Array_Number;
typedef struct Opt_Array_Number {
    enum Ark_Tag tag;
    Array_Number value;
} Opt_Array_Number;
typedef struct Array_TextCascadePickerRangeContent {
    struct Ark_TextCascadePickerRangeContent* array;
    Ark_Int32 length;
} Array_TextCascadePickerRangeContent;
typedef struct Opt_Array_TextCascadePickerRangeContent {
    enum Ark_Tag tag;
    Array_TextCascadePickerRangeContent value;
} Opt_Array_TextCascadePickerRangeContent;
typedef struct Array_TextPickerRangeContent {
    struct Ark_TextPickerRangeContent* array;
    Ark_Int32 length;
} Array_TextPickerRangeContent;
typedef struct Opt_Array_TextPickerRangeContent {
    enum Ark_Tag tag;
    Array_TextPickerRangeContent value;
} Opt_Array_TextPickerRangeContent;
typedef struct Array_Array_String {
    struct Array_String* array;
    Ark_Int32 length;
} Array_Array_String;
typedef struct Opt_Array_Array_String {
    enum Ark_Tag tag;
    Array_Array_String value;
} Opt_Array_Array_String;
typedef struct Union_Ark_ResourceColor_Undefined {
    Ark_Int32 selector;
    union {
        struct Ark_ResourceColor value0;
        Ark_Undefined value1;
    };
} Union_Ark_ResourceColor_Undefined;
typedef struct Opt_Union_ResourceColor_Undefined {
    enum Ark_Tag tag;
    Union_Ark_ResourceColor_Undefined value;
} Opt_Union_ResourceColor_Undefined;
typedef Ark_Materialized Ark_TextContentControllerBase;
typedef struct Opt_TextContentControllerBase {
    enum Ark_Tag tag;
    Ark_TextContentControllerBase value;
} Opt_TextContentControllerBase;
typedef struct Ark_TabBarIconStyle {
    struct Opt_ResourceColor selectedColor;
    struct Opt_ResourceColor unselectedColor;
} Ark_TabBarIconStyle;
typedef struct Opt_TabBarIconStyle {
    enum Ark_Tag tag;
    Ark_TabBarIconStyle value;
} Opt_TabBarIconStyle;
typedef Ark_Int32 Ark_VerticalAlign;
typedef struct Opt_VerticalAlign {
    enum Ark_Tag tag;
    Ark_VerticalAlign value;
} Opt_VerticalAlign;
typedef Ark_Int32 Ark_LayoutMode;
typedef struct Opt_LayoutMode {
    enum Ark_Tag tag;
    Ark_LayoutMode value;
} Opt_LayoutMode;
typedef struct Union_Ark_Padding_Length_LocalizedPadding {
    Ark_Int32 selector;
    union {
        struct Ark_Padding value0;
        Ark_Length value1;
        struct Ark_LocalizedPadding value2;
    };
} Union_Ark_Padding_Length_LocalizedPadding;
typedef struct Opt_Union_Padding_Length_LocalizedPadding {
    enum Ark_Tag tag;
    Union_Ark_Padding_Length_LocalizedPadding value;
} Opt_Union_Padding_Length_LocalizedPadding;
typedef struct Ark_LabelStyle {
    Opt_TextOverflow overflow;
    Opt_Number maxLines;
    struct Opt_Union_Number_ResourceStr minFontSize;
    struct Opt_Union_Number_ResourceStr maxFontSize;
    Opt_TextHeightAdaptivePolicy heightAdaptivePolicy;
    struct Opt_Font font;
} Ark_LabelStyle;
typedef struct Opt_LabelStyle {
    enum Ark_Tag tag;
    Ark_LabelStyle value;
} Opt_LabelStyle;
typedef struct Union_Ark_Padding_Length {
    Ark_Int32 selector;
    union {
        struct Ark_Padding value0;
        Ark_Length value1;
    };
} Union_Ark_Padding_Length;
typedef struct Opt_Union_Padding_Length {
    enum Ark_Tag tag;
    Union_Ark_Padding_Length value;
} Opt_Union_Padding_Length;
typedef struct Ark_BoardStyle {
    Opt_Length borderRadius;
} Ark_BoardStyle;
typedef struct Opt_BoardStyle {
    enum Ark_Tag tag;
    Ark_BoardStyle value;
} Opt_BoardStyle;
typedef Ark_Int32 Ark_SelectedMode;
typedef struct Opt_SelectedMode {
    enum Ark_Tag tag;
    Ark_SelectedMode value;
} Opt_SelectedMode;
typedef struct Ark_IndicatorStyle {
    Opt_Length left;
    Opt_Length top;
    Opt_Length right;
    Opt_Length bottom;
    Opt_Length size;
    Opt_Boolean mask;
    struct Opt_ResourceColor color;
    struct Opt_ResourceColor selectedColor;
} Ark_IndicatorStyle;
typedef struct Opt_IndicatorStyle {
    enum Ark_Tag tag;
    Ark_IndicatorStyle value;
} Opt_IndicatorStyle;
typedef struct Ark_VP {
    Ark_Int32 selector;
    union {
        struct Ark_String value0;
        Ark_Number value1;
    };
} Ark_VP;
typedef struct Opt_VP {
    enum Ark_Tag tag;
    Ark_VP value;
} Opt_VP;
typedef struct Ark_Indicator {
    Opt_Length _left;
    Opt_Length _top;
    Opt_Length _right;
    Opt_Length _bottom;
    Opt_CustomObject _start;
    Opt_CustomObject _end;
} Ark_Indicator;
typedef struct Opt_Indicator {
    enum Ark_Tag tag;
    Ark_Indicator value;
} Opt_Indicator;
typedef struct Ark_RectAttribute {
    void *handle;
} Ark_RectAttribute;
typedef struct Opt_RectAttribute {
    enum Ark_Tag tag;
    Ark_RectAttribute value;
} Opt_RectAttribute;
typedef struct Ark_PathAttribute {
    void *handle;
} Ark_PathAttribute;
typedef struct Opt_PathAttribute {
    enum Ark_Tag tag;
    Ark_PathAttribute value;
} Opt_PathAttribute;
typedef struct Ark_EllipseAttribute {
    void *handle;
} Ark_EllipseAttribute;
typedef struct Opt_EllipseAttribute {
    enum Ark_Tag tag;
    Ark_EllipseAttribute value;
} Opt_EllipseAttribute;
typedef struct Ark_CircleAttribute {
    void *handle;
} Ark_CircleAttribute;
typedef struct Opt_CircleAttribute {
    enum Ark_Tag tag;
    Ark_CircleAttribute value;
} Opt_CircleAttribute;
typedef struct Ark_DividerOptions {
    Opt_Length strokeWidth;
    struct Opt_ResourceColor color;
    Opt_Length startMargin;
    Opt_Length endMargin;
} Ark_DividerOptions;
typedef struct Opt_DividerOptions {
    enum Ark_Tag tag;
    Ark_DividerOptions value;
} Opt_DividerOptions;
typedef Ark_Int32 Ark_CancelButtonStyle;
typedef struct Opt_CancelButtonStyle {
    enum Ark_Tag tag;
    Ark_CancelButtonStyle value;
} Opt_CancelButtonStyle;
typedef struct Ark_IconOptions {
    Opt_Length size;
    struct Opt_ResourceColor color;
    struct Opt_ResourceStr src;
} Ark_IconOptions;
typedef struct Opt_IconOptions {
    enum Ark_Tag tag;
    Ark_IconOptions value;
} Opt_IconOptions;
typedef struct Array_Length {
    Ark_Length* array;
    Ark_Int32 length;
} Array_Length;
typedef struct Opt_Array_Length {
    enum Ark_Tag tag;
    Array_Length value;
} Opt_Array_Length;
typedef Ark_Materialized Ark_StyledStringController;
typedef struct Opt_StyledStringController {
    enum Ark_Tag tag;
    Ark_StyledStringController value;
} Opt_StyledStringController;
typedef Ark_Materialized Ark_RichEditorBaseController;
typedef struct Opt_RichEditorBaseController {
    enum Ark_Tag tag;
    Ark_RichEditorBaseController value;
} Opt_RichEditorBaseController;
typedef struct Union_Number_String_Array_CustomObject {
    Ark_Int32 selector;
    union {
        Ark_Number value0;
        Ark_String value1;
        struct Array_CustomObject value2;
    };
} Union_Number_String_Array_CustomObject;
typedef struct Opt_Union_Number_String_Array_CustomObject {
    enum Ark_Tag tag;
    Union_Number_String_Array_CustomObject value;
} Opt_Union_Number_String_Array_CustomObject;
typedef struct Union_TitleHeight_Length {
    Ark_Int32 selector;
    union {
        Ark_TitleHeight value0;
        Ark_Length value1;
    };
} Union_TitleHeight_Length;
typedef struct Opt_Union_TitleHeight_Length {
    enum Ark_Tag tag;
    Union_TitleHeight_Length value;
} Opt_Union_TitleHeight_Length;
typedef struct Ark_SwipeActionItem {
    struct Opt_CustomBuilder builder;
    Opt_Length actionAreaDistance;
    struct Opt_Function onAction;
    struct Opt_Function onEnterActionArea;
    struct Opt_Function onExitActionArea;
    struct Opt_Function onStateChange;
} Ark_SwipeActionItem;
typedef struct Opt_SwipeActionItem {
    enum Ark_Tag tag;
    Ark_SwipeActionItem value;
} Opt_SwipeActionItem;
typedef Ark_Int32 Ark_BreakpointsReference;
typedef struct Opt_BreakpointsReference {
    enum Ark_Tag tag;
    Ark_BreakpointsReference value;
} Opt_BreakpointsReference;
typedef struct Ark_GridRowColumnOption {
    Opt_Number xs;
    Opt_Number sm;
    Opt_Number md;
    Opt_Number lg;
    Opt_Number xl;
    Opt_Number xxl;
} Ark_GridRowColumnOption;
typedef struct Opt_GridRowColumnOption {
    enum Ark_Tag tag;
    Ark_GridRowColumnOption value;
} Opt_GridRowColumnOption;
typedef struct Ark_GutterOption {
    struct Opt_Union_Length_GridRowSizeOption x;
    struct Opt_Union_Length_GridRowSizeOption y;
} Ark_GutterOption;
typedef struct Opt_GutterOption {
    enum Ark_Tag tag;
    Ark_GutterOption value;
} Opt_GutterOption;
typedef struct Ark_GridColColumnOption {
    Opt_Number xs;
    Opt_Number sm;
    Opt_Number md;
    Opt_Number lg;
    Opt_Number xl;
    Opt_Number xxl;
} Ark_GridColColumnOption;
typedef struct Opt_GridColColumnOption {
    enum Ark_Tag tag;
    Ark_GridColColumnOption value;
} Opt_GridColColumnOption;
typedef struct Ark_LinearGradient {
    struct Opt_Union_Number_String angle;
    Opt_GradientDirection direction;
    struct Array_Tuple_Ark_ResourceColor_Number colors;
    Opt_Boolean repeating;
} Ark_LinearGradient;
typedef struct Opt_LinearGradient {
    enum Ark_Tag tag;
    Ark_LinearGradient value;
} Opt_LinearGradient;
typedef Ark_Materialized Ark_CanvasRenderer;
typedef struct Opt_CanvasRenderer {
    enum Ark_Tag tag;
    Ark_CanvasRenderer value;
} Opt_CanvasRenderer;
typedef struct Array_CalendarDay {
    struct Ark_CalendarDay* array;
    Ark_Int32 length;
} Array_CalendarDay;
typedef struct Opt_Array_CalendarDay {
    enum Ark_Tag tag;
    Array_CalendarDay value;
} Opt_Array_CalendarDay;
typedef struct Ark_BadgeStyle {
    struct Opt_ResourceColor color;
    struct Opt_Union_Number_String fontSize;
    struct Opt_Union_Number_String badgeSize;
    struct Opt_ResourceColor badgeColor;
    struct Opt_ResourceColor borderColor;
    Opt_Length borderWidth;
    struct Opt_Union_Number_FontWeight_String fontWeight;
} Ark_BadgeStyle;
typedef struct Opt_BadgeStyle {
    enum Ark_Tag tag;
    Ark_BadgeStyle value;
} Opt_BadgeStyle;
typedef struct Union_BadgePosition_Position {
    Ark_Int32 selector;
    union {
        Ark_BadgePosition value0;
        struct Ark_Position value1;
    };
} Union_BadgePosition_Position;
typedef struct Opt_Union_BadgePosition_Position {
    enum Ark_Tag tag;
    Union_BadgePosition_Position value;
} Opt_Union_BadgePosition_Position;
typedef struct Ark_EdgeStyles {
    Opt_BorderStyle top;
    Opt_BorderStyle right;
    Opt_BorderStyle bottom;
    Opt_BorderStyle left;
} Ark_EdgeStyles;
typedef struct Opt_EdgeStyles {
    enum Ark_Tag tag;
    Ark_EdgeStyles value;
} Opt_EdgeStyles;
typedef struct Ark_LocalizedEdgeColors {
    struct Opt_ResourceColor top;
    struct Opt_ResourceColor end;
    struct Opt_ResourceColor bottom;
    struct Opt_ResourceColor start;
} Ark_LocalizedEdgeColors;
typedef struct Opt_LocalizedEdgeColors {
    enum Ark_Tag tag;
    Ark_LocalizedEdgeColors value;
} Opt_LocalizedEdgeColors;
typedef struct Ark_EdgeColors {
    struct Opt_ResourceColor top;
    struct Opt_ResourceColor right;
    struct Opt_ResourceColor bottom;
    struct Opt_ResourceColor left;
} Ark_EdgeColors;
typedef struct Opt_EdgeColors {
    enum Ark_Tag tag;
    Ark_EdgeColors value;
} Opt_EdgeColors;
typedef struct Ark_LocalizedEdgeWidths {
    Opt_CustomObject top;
    Opt_CustomObject end;
    Opt_CustomObject bottom;
    Opt_CustomObject start;
} Ark_LocalizedEdgeWidths;
typedef struct Opt_LocalizedEdgeWidths {
    enum Ark_Tag tag;
    Ark_LocalizedEdgeWidths value;
} Opt_LocalizedEdgeWidths;
typedef struct Ark_EdgeWidths {
    Opt_Length top;
    Opt_Length right;
    Opt_Length bottom;
    Opt_Length left;
} Ark_EdgeWidths;
typedef struct Opt_EdgeWidths {
    enum Ark_Tag tag;
    Ark_EdgeWidths value;
} Opt_EdgeWidths;
typedef struct Ark_SheetTitleOptions {
    struct Ark_ResourceStr title;
    struct Opt_ResourceStr subtitle;
} Ark_SheetTitleOptions;
typedef struct Opt_SheetTitleOptions {
    enum Ark_Tag tag;
    Ark_SheetTitleOptions value;
} Opt_SheetTitleOptions;
typedef Ark_Int32 Ark_BlurStyle;
typedef struct Opt_BlurStyle {
    enum Ark_Tag tag;
    Ark_BlurStyle value;
} Opt_BlurStyle;
typedef struct Ark_ContextMenuAnimationOptions {
    Opt_CustomObject scale;
    struct Opt_TransitionEffect transition;
    Opt_CustomObject hoverScale;
} Ark_ContextMenuAnimationOptions;
typedef struct Opt_ContextMenuAnimationOptions {
    enum Ark_Tag tag;
    Ark_ContextMenuAnimationOptions value;
} Opt_ContextMenuAnimationOptions;
typedef struct Union_Length_Ark_BorderRadiuses_LocalizedBorderRadiuses {
    Ark_Int32 selector;
    union {
        Ark_Length value0;
        struct Ark_BorderRadiuses value1;
        struct Ark_LocalizedBorderRadiuses value2;
    };
} Union_Length_Ark_BorderRadiuses_LocalizedBorderRadiuses;
typedef struct Opt_Union_Length_BorderRadiuses_LocalizedBorderRadiuses {
    enum Ark_Tag tag;
    Union_Length_Ark_BorderRadiuses_LocalizedBorderRadiuses value;
} Opt_Union_Length_BorderRadiuses_LocalizedBorderRadiuses;
typedef struct Union_MenuPreviewMode_Ark_CustomBuilder {
    Ark_Int32 selector;
    union {
        Ark_MenuPreviewMode value0;
        struct Ark_CustomBuilder value1;
    };
} Union_MenuPreviewMode_Ark_CustomBuilder;
typedef struct Opt_Union_MenuPreviewMode_CustomBuilder {
    enum Ark_Tag tag;
    Union_MenuPreviewMode_Ark_CustomBuilder value;
} Opt_Union_MenuPreviewMode_CustomBuilder;
typedef Ark_Int32 Ark_Placement;
typedef struct Opt_Placement {
    enum Ark_Tag tag;
    Ark_Placement value;
} Opt_Placement;
typedef struct Union_Boolean_Ark_Function {
    Ark_Int32 selector;
    union {
        Ark_Boolean value0;
        struct Ark_Function value1;
    };
} Union_Boolean_Ark_Function;
typedef struct Opt_Union_Boolean_Function {
    enum Ark_Tag tag;
    Union_Boolean_Ark_Function value;
} Opt_Union_Boolean_Function;
typedef struct Union_ShadowOptions_ShadowStyle {
    Ark_Int32 selector;
    union {
        struct Ark_ShadowOptions value0;
        Ark_ShadowStyle value1;
    };
} Union_ShadowOptions_ShadowStyle;
typedef struct Opt_Union_ShadowOptions_ShadowStyle {
    enum Ark_Tag tag;
    Union_ShadowOptions_ShadowStyle value;
} Opt_Union_ShadowOptions_ShadowStyle;
typedef Ark_Int32 Ark_ArrowPointPosition;
typedef struct Opt_ArrowPointPosition {
    enum Ark_Tag tag;
    Ark_ArrowPointPosition value;
} Opt_ArrowPointPosition;
typedef struct Union_Boolean_Literal_Ark_ResourceColor_color {
    Ark_Int32 selector;
    union {
        Ark_Boolean value0;
        struct Literal_Ark_ResourceColor_color value1;
    };
} Union_Boolean_Literal_Ark_ResourceColor_color;
typedef struct Opt_Union_Boolean_Literal_ResourceColor_color {
    enum Ark_Tag tag;
    Union_Boolean_Literal_Ark_ResourceColor_color value;
} Opt_Union_Boolean_Literal_ResourceColor_color;
typedef struct Union_Color_String_Resource_Number {
    Ark_Int32 selector;
    union {
        Ark_Color value0;
        Ark_String value1;
        struct Ark_Resource value2;
        Ark_Number value3;
    };
} Union_Color_String_Resource_Number;
typedef struct Opt_Union_Color_String_Resource_Number {
    enum Ark_Tag tag;
    Union_Color_String_Resource_Number value;
} Opt_Union_Color_String_Resource_Number;
typedef struct Ark_PopupMessageOptions {
    struct Opt_ResourceColor textColor;
    struct Opt_Font font;
} Ark_PopupMessageOptions;
typedef struct Opt_PopupMessageOptions {
    enum Ark_Tag tag;
    Ark_PopupMessageOptions value;
} Opt_PopupMessageOptions;
typedef struct Literal_String_value_Function_action {
    Ark_String value;
    struct Ark_Function action;
} Literal_String_value_Function_action;
typedef struct Opt_Literal_String_value_Function_action {
    enum Ark_Tag tag;
    Literal_String_value_Function_action value;
} Opt_Literal_String_value_Function_action;
typedef int32_t Ark_DragPreviewMode;
typedef struct Array_DragPreviewMode {
    Ark_DragPreviewMode* array;
    Ark_Int32 length;
} Array_DragPreviewMode;
typedef int32_t Ark_DragPreviewMode;
typedef struct Opt_Array_DragPreviewMode {
    enum Ark_Tag tag;
    Array_DragPreviewMode value;
} Opt_Array_DragPreviewMode;
typedef Ark_Int32 Ark_DragPreviewMode;
typedef struct Opt_DragPreviewMode {
    enum Ark_Tag tag;
    Ark_DragPreviewMode value;
} Opt_DragPreviewMode;
typedef Ark_Int32 Ark_ClickEffectLevel;
typedef struct Opt_ClickEffectLevel {
    enum Ark_Tag tag;
    Ark_ClickEffectLevel value;
} Opt_ClickEffectLevel;
typedef Ark_Int32 Ark_HorizontalAlign;
typedef struct Opt_HorizontalAlign {
    enum Ark_Tag tag;
    Ark_HorizontalAlign value;
} Opt_HorizontalAlign;
typedef struct Literal_Number_span_offset {
    Ark_Number span;
    Ark_Number offset;
} Literal_Number_span_offset;
typedef struct Opt_Literal_Number_span_offset {
    enum Ark_Tag tag;
    Literal_Number_span_offset value;
} Opt_Literal_Number_span_offset;
typedef struct Ark_GestureInterface {
    void *handle;
} Ark_GestureInterface;
typedef struct Opt_GestureInterface {
    enum Ark_Tag tag;
    Ark_GestureInterface value;
} Opt_GestureInterface;
typedef struct Ark_RotateOptions {
    Opt_Number x;
    Opt_Number y;
    Opt_Number z;
    struct Opt_Union_Number_String centerX;
    struct Opt_Union_Number_String centerY;
    Opt_Number centerZ;
    Opt_Number perspective;
    struct Union_Number_String angle;
} Ark_RotateOptions;
typedef struct Opt_RotateOptions {
    enum Ark_Tag tag;
    Ark_RotateOptions value;
} Opt_RotateOptions;
typedef struct Ark_ScaleOptions {
    Opt_Number x;
    Opt_Number y;
    Opt_Number z;
    struct Opt_Union_Number_String centerX;
    struct Opt_Union_Number_String centerY;
} Ark_ScaleOptions;
typedef struct Opt_ScaleOptions {
    enum Ark_Tag tag;
    Ark_ScaleOptions value;
} Opt_ScaleOptions;
typedef struct Ark_TranslateOptions {
    struct Opt_Union_Number_String x;
    struct Opt_Union_Number_String y;
    struct Opt_Union_Number_String z;
} Ark_TranslateOptions;
typedef struct Opt_TranslateOptions {
    enum Ark_Tag tag;
    Ark_TranslateOptions value;
} Opt_TranslateOptions;
typedef Ark_Int32 Ark_TransitionType;
typedef struct Opt_TransitionType {
    enum Ark_Tag tag;
    Ark_TransitionType value;
} Opt_TransitionType;
typedef struct Ark_EdgeOutlineStyles {
    Opt_OutlineStyle top;
    Opt_OutlineStyle right;
    Opt_OutlineStyle bottom;
    Opt_OutlineStyle left;
} Ark_EdgeOutlineStyles;
typedef struct Opt_EdgeOutlineStyles {
    enum Ark_Tag tag;
    Ark_EdgeOutlineStyles value;
} Opt_EdgeOutlineStyles;
typedef struct Ark_OutlineRadiuses {
    Opt_Length topLeft;
    Opt_Length topRight;
    Opt_Length bottomLeft;
    Opt_Length bottomRight;
} Ark_OutlineRadiuses;
typedef struct Opt_OutlineRadiuses {
    enum Ark_Tag tag;
    Ark_OutlineRadiuses value;
} Opt_OutlineRadiuses;
typedef struct Ark_EdgeOutlineWidths {
    Opt_Length top;
    Opt_Length right;
    Opt_Length bottom;
    Opt_Length left;
} Ark_EdgeOutlineWidths;
typedef struct Opt_EdgeOutlineWidths {
    enum Ark_Tag tag;
    Ark_EdgeOutlineWidths value;
} Opt_EdgeOutlineWidths;
typedef struct Ark_BlurOptions {
    struct Tuple_Number_Number grayscale;
} Ark_BlurOptions;
typedef struct Opt_BlurOptions {
    enum Ark_Tag tag;
    Ark_BlurOptions value;
} Opt_BlurOptions;
typedef Ark_Int32 Ark_AdaptiveColor;
typedef struct Opt_AdaptiveColor {
    enum Ark_Tag tag;
    Ark_AdaptiveColor value;
} Opt_AdaptiveColor;
typedef Ark_Int32 Ark_ThemeColorMode;
typedef struct Opt_ThemeColorMode {
    enum Ark_Tag tag;
    Ark_ThemeColorMode value;
} Opt_ThemeColorMode;
typedef Ark_Materialized Ark_WebKeyboardController;
typedef struct Opt_WebKeyboardController {
    enum Ark_Tag tag;
    Ark_WebKeyboardController value;
} Opt_WebKeyboardController;
typedef Ark_Int32 Ark_RenderProcessNotRespondingReason;
typedef struct Opt_RenderProcessNotRespondingReason {
    enum Ark_Tag tag;
    Ark_RenderProcessNotRespondingReason value;
} Opt_RenderProcessNotRespondingReason;
typedef Ark_Materialized Ark_EventResult;
typedef struct Opt_EventResult {
    enum Ark_Tag tag;
    Ark_EventResult value;
} Opt_EventResult;
typedef struct Ark_TouchEvent {
    struct Ark_EventTarget target;
    Ark_Number timestamp;
    Ark_SourceType source;
    Opt_Number axisHorizontal;
    Opt_Number axisVertical;
    Ark_Number pressure;
    Ark_Number tiltX;
    Ark_Number tiltY;
    Ark_SourceTool sourceTool;
    Opt_Number deviceId;
    Ark_TouchType type;
    struct Array_TouchObject touches;
    struct Array_TouchObject changedTouches;
    struct Ark_Function stopPropagation;
    struct Ark_Function preventDefault;
} Ark_TouchEvent;
typedef struct Opt_TouchEvent {
    enum Ark_Tag tag;
    Ark_TouchEvent value;
} Opt_TouchEvent;
typedef struct Ark_NativeEmbedInfo {
    Opt_String id;
    Opt_String type;
    Opt_String src;
    struct Opt_Position position;
    Opt_Number width;
    Opt_Number height;
    Opt_String url;
    Opt_String tag;
    struct Opt_Map_String_String params;
} Ark_NativeEmbedInfo;
typedef struct Opt_NativeEmbedInfo {
    enum Ark_Tag tag;
    Ark_NativeEmbedInfo value;
} Opt_NativeEmbedInfo;
typedef Ark_Int32 Ark_NativeEmbedStatus;
typedef struct Opt_NativeEmbedStatus {
    enum Ark_Tag tag;
    Ark_NativeEmbedStatus value;
} Opt_NativeEmbedStatus;
typedef Ark_Int32 Ark_WebNavigationType;
typedef struct Opt_WebNavigationType {
    enum Ark_Tag tag;
    Ark_WebNavigationType value;
} Opt_WebNavigationType;
typedef Ark_Materialized Ark_DataResubmissionHandler;
typedef struct Opt_DataResubmissionHandler {
    enum Ark_Tag tag;
    Ark_DataResubmissionHandler value;
} Opt_DataResubmissionHandler;
typedef Ark_Materialized Ark_ControllerHandler;
typedef struct Opt_ControllerHandler {
    enum Ark_Tag tag;
    Ark_ControllerHandler value;
} Opt_ControllerHandler;
typedef Ark_Materialized Ark_ClientAuthenticationHandler;
typedef struct Opt_ClientAuthenticationHandler {
    enum Ark_Tag tag;
    Ark_ClientAuthenticationHandler value;
} Opt_ClientAuthenticationHandler;
typedef Ark_Int32 Ark_SslError;
typedef struct Opt_SslError {
    enum Ark_Tag tag;
    Ark_SslError value;
} Opt_SslError;
typedef Ark_Materialized Ark_SslErrorHandler;
typedef struct Opt_SslErrorHandler {
    enum Ark_Tag tag;
    Ark_SslErrorHandler value;
} Opt_SslErrorHandler;
typedef Ark_Materialized Ark_WebContextMenuResult;
typedef struct Opt_WebContextMenuResult {
    enum Ark_Tag tag;
    Ark_WebContextMenuResult value;
} Opt_WebContextMenuResult;
typedef Ark_Materialized Ark_WebContextMenuParam;
typedef struct Opt_WebContextMenuParam {
    enum Ark_Tag tag;
    Ark_WebContextMenuParam value;
} Opt_WebContextMenuParam;
typedef Ark_Materialized Ark_ScreenCaptureHandler;
typedef struct Opt_ScreenCaptureHandler {
    enum Ark_Tag tag;
    Ark_ScreenCaptureHandler value;
} Opt_ScreenCaptureHandler;
typedef Ark_Materialized Ark_PermissionRequest;
typedef struct Opt_PermissionRequest {
    enum Ark_Tag tag;
    Ark_PermissionRequest value;
} Opt_PermissionRequest;
typedef Ark_Materialized Ark_HttpAuthHandler;
typedef struct Opt_HttpAuthHandler {
    enum Ark_Tag tag;
    Ark_HttpAuthHandler value;
} Opt_HttpAuthHandler;
typedef Ark_Materialized Ark_FullScreenExitHandler;
typedef struct Opt_FullScreenExitHandler {
    enum Ark_Tag tag;
    Ark_FullScreenExitHandler value;
} Opt_FullScreenExitHandler;
typedef Ark_Materialized Ark_FileSelectorParam;
typedef struct Opt_FileSelectorParam {
    enum Ark_Tag tag;
    Ark_FileSelectorParam value;
} Opt_FileSelectorParam;
typedef Ark_Materialized Ark_FileSelectorResult;
typedef struct Opt_FileSelectorResult {
    enum Ark_Tag tag;
    Ark_FileSelectorResult value;
} Opt_FileSelectorResult;
typedef Ark_Int32 Ark_RenderExitReason;
typedef struct Opt_RenderExitReason {
    enum Ark_Tag tag;
    Ark_RenderExitReason value;
} Opt_RenderExitReason;
typedef struct Union_String_WebResourceRequest {
    Ark_Int32 selector;
    union {
        Ark_String value0;
        Ark_WebResourceRequest value1;
    };
} Union_String_WebResourceRequest;
typedef struct Opt_Union_String_WebResourceRequest {
    enum Ark_Tag tag;
    Union_String_WebResourceRequest value;
} Opt_Union_String_WebResourceRequest;
typedef Ark_Materialized Ark_WebResourceResponse;
typedef struct Opt_WebResourceResponse {
    enum Ark_Tag tag;
    Ark_WebResourceResponse value;
} Opt_WebResourceResponse;
typedef Ark_Materialized Ark_WebResourceError;
typedef struct Opt_WebResourceError {
    enum Ark_Tag tag;
    Ark_WebResourceError value;
} Opt_WebResourceError;
typedef Ark_Materialized Ark_ConsoleMessage;
typedef struct Opt_ConsoleMessage {
    enum Ark_Tag tag;
    Ark_ConsoleMessage value;
} Opt_ConsoleMessage;
typedef Ark_Materialized Ark_JsResult;
typedef struct Opt_JsResult {
    enum Ark_Tag tag;
    Ark_JsResult value;
} Opt_JsResult;
typedef Ark_Materialized Ark_JsGeolocation;
typedef struct Opt_JsGeolocation {
    enum Ark_Tag tag;
    Ark_JsGeolocation value;
} Opt_JsGeolocation;
typedef Ark_Int32 Ark_TextDeleteDirection;
typedef struct Opt_TextDeleteDirection {
    enum Ark_Tag tag;
    Ark_TextDeleteDirection value;
} Opt_TextDeleteDirection;
typedef struct Array_RichEditorTextSpanResult {
    struct Ark_RichEditorTextSpanResult* array;
    Ark_Int32 length;
} Array_RichEditorTextSpanResult;
typedef struct Opt_Array_RichEditorTextSpanResult {
    enum Ark_Tag tag;
    Array_RichEditorTextSpanResult value;
} Opt_Array_RichEditorTextSpanResult;
typedef struct Array_RichEditorImageSpanResult {
    struct Ark_RichEditorImageSpanResult* array;
    Ark_Int32 length;
} Array_RichEditorImageSpanResult;
typedef struct Opt_Array_RichEditorImageSpanResult {
    enum Ark_Tag tag;
    Array_RichEditorImageSpanResult value;
} Opt_Array_RichEditorImageSpanResult;
typedef struct Ark_TextRange {
    Opt_Number start;
    Opt_Number end;
} Ark_TextRange;
typedef struct Opt_TextRange {
    enum Ark_Tag tag;
    Ark_TextRange value;
} Opt_TextRange;
typedef struct Ark_RichEditorImageSpanResult {
    struct Ark_RichEditorSpanPosition spanPosition;
    Opt_CustomObject valuePixelMap;
    struct Opt_ResourceStr valueResourceStr;
    struct Ark_RichEditorImageSpanStyleResult imageStyle;
    struct Tuple_Number_Number offsetInSpan;
} Ark_RichEditorImageSpanResult;
typedef struct Opt_RichEditorImageSpanResult {
    enum Ark_Tag tag;
    Ark_RichEditorImageSpanResult value;
} Opt_RichEditorImageSpanResult;
typedef struct Ark_RichEditorTextSpanResult {
    struct Ark_RichEditorSpanPosition spanPosition;
    Ark_String value;
    struct Ark_RichEditorTextStyleResult textStyle;
    struct Tuple_Number_Number offsetInSpan;
    struct Opt_RichEditorSymbolSpanStyle symbolSpanStyle;
    struct Opt_Resource valueResource;
    struct Opt_RichEditorParagraphStyle paragraphStyle;
    Opt_String previewText;
} Ark_RichEditorTextSpanResult;
typedef struct Opt_RichEditorTextSpanResult {
    enum Ark_Tag tag;
    Ark_RichEditorTextSpanResult value;
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
typedef struct Opt_RichEditorDeleteDirection {
    enum Ark_Tag tag;
    Ark_RichEditorDeleteDirection value;
} Opt_RichEditorDeleteDirection;
typedef struct Ark_Object {
    void *handle;
} Ark_Object;
typedef struct Opt_Object {
    enum Ark_Tag tag;
    Ark_Object value;
} Opt_Object;
typedef Ark_Int32 Ark_NavDestinationMode;
typedef struct Opt_NavDestinationMode {
    enum Ark_Tag tag;
    Ark_NavDestinationMode value;
} Opt_NavDestinationMode;
typedef Ark_Int32 Ark_ListItemGroupArea;
typedef struct Opt_ListItemGroupArea {
    enum Ark_Tag tag;
    Ark_ListItemGroupArea value;
} Opt_ListItemGroupArea;
typedef Ark_Int32 Ark_AppRotation;
typedef struct Opt_AppRotation {
    enum Ark_Tag tag;
    Ark_AppRotation value;
} Opt_AppRotation;
typedef Ark_Int32 Ark_FoldStatus;
typedef struct Opt_FoldStatus {
    enum Ark_Tag tag;
    Ark_FoldStatus value;
} Opt_FoldStatus;
typedef struct Array_FingerInfo {
    struct Ark_FingerInfo* array;
    Ark_Int32 length;
} Array_FingerInfo;
typedef struct Opt_Array_FingerInfo {
    enum Ark_Tag tag;
    Array_FingerInfo value;
} Opt_Array_FingerInfo;
typedef Ark_Int32 Ark_GestureControl_GestureType;
typedef struct Opt_GestureControl_GestureType {
    enum Ark_Tag tag;
    Ark_GestureControl_GestureType value;
} Opt_GestureControl_GestureType;
typedef Ark_Int32 Ark_DragBehavior;
typedef struct Opt_DragBehavior {
    enum Ark_Tag tag;
    Ark_DragBehavior value;
} Opt_DragBehavior;
typedef Ark_Int32 Ark_KeySource;
typedef struct Opt_KeySource {
    enum Ark_Tag tag;
    Ark_KeySource value;
} Opt_KeySource;
typedef Ark_Int32 Ark_KeyType;
typedef struct Opt_KeyType {
    enum Ark_Tag tag;
    Ark_KeyType value;
} Opt_KeyType;
typedef Ark_Int32 Ark_MouseAction;
typedef struct Opt_MouseAction {
    enum Ark_Tag tag;
    Ark_MouseAction value;
} Opt_MouseAction;
typedef Ark_Int32 Ark_MouseButton;
typedef struct Opt_MouseButton {
    enum Ark_Tag tag;
    Ark_MouseButton value;
} Opt_MouseButton;
typedef Ark_Int32 Ark_AccessibilityHoverType;
typedef struct Opt_AccessibilityHoverType {
    enum Ark_Tag tag;
    Ark_AccessibilityHoverType value;
} Opt_AccessibilityHoverType;
typedef struct Ark_RectResult {
    Ark_Number x;
    Ark_Number y;
    Ark_Number width;
    Ark_Number height;
} Ark_RectResult;
typedef struct Opt_RectResult {
    enum Ark_Tag tag;
    Ark_RectResult value;
} Opt_RectResult;
typedef Ark_Int32 Ark_SelectStatus;
typedef struct Opt_SelectStatus {
    enum Ark_Tag tag;
    Ark_SelectStatus value;
} Opt_SelectStatus;
typedef Ark_Int32 Ark_WebCaptureMode;
typedef struct Opt_WebCaptureMode {
    enum Ark_Tag tag;
    Ark_WebCaptureMode value;
} Opt_WebCaptureMode;
typedef struct Ark_ArrayBuffer {
    void *handle;
} Ark_ArrayBuffer;
typedef struct Opt_ArrayBuffer {
    enum Ark_Tag tag;
    Ark_ArrayBuffer value;
} Opt_ArrayBuffer;
typedef struct Array_Header {
    struct Ark_Header* array;
    Ark_Int32 length;
} Array_Header;
typedef struct Opt_Array_Header {
    enum Ark_Tag tag;
    Array_Header value;
} Opt_Array_Header;
typedef struct Ark_StyledStringValue {
    Ark_Int32 selector;
    union {
        struct Ark_TextStyle value0;
        struct Ark_DecorationStyle value1;
        struct Ark_BaselineOffsetStyle value2;
        struct Ark_LetterSpacingStyle value3;
        struct Ark_TextShadowStyle value4;
        struct Ark_GestureStyle value5;
        struct Ark_ImageAttachment value6;
        struct Ark_ParagraphStyle value7;
        struct Ark_LineHeightStyle value8;
        struct Ark_UrlStyle value9;
        Ark_CustomSpan value10;
        struct Ark_UserDataSpan value11;
        struct Ark_BackgroundColorStyle value12;
    };
} Ark_StyledStringValue;
typedef struct Opt_StyledStringValue {
    enum Ark_Tag tag;
    Ark_StyledStringValue value;
} Opt_StyledStringValue;
typedef Ark_Int32 Ark_StyledStringKey;
typedef struct Opt_StyledStringKey {
    enum Ark_Tag tag;
    Ark_StyledStringKey value;
} Opt_StyledStringKey;
typedef Ark_Int32 Ark_MenuPolicy;
typedef struct Opt_MenuPolicy {
    enum Ark_Tag tag;
    Ark_MenuPolicy value;
} Opt_MenuPolicy;
typedef struct Ark_RichEditorUpdateSymbolSpanStyleOptions {
    Opt_Number start;
    Opt_Number end;
    struct Ark_RichEditorSymbolSpanStyle symbolStyle;
} Ark_RichEditorUpdateSymbolSpanStyleOptions;
typedef struct Opt_RichEditorUpdateSymbolSpanStyleOptions {
    enum Ark_Tag tag;
    Ark_RichEditorUpdateSymbolSpanStyleOptions value;
} Opt_RichEditorUpdateSymbolSpanStyleOptions;
typedef struct Ark_RichEditorUpdateImageSpanStyleOptions {
    Opt_Number start;
    Opt_Number end;
    struct Ark_RichEditorImageSpanStyle imageStyle;
} Ark_RichEditorUpdateImageSpanStyleOptions;
typedef struct Opt_RichEditorUpdateImageSpanStyleOptions {
    enum Ark_Tag tag;
    Ark_RichEditorUpdateImageSpanStyleOptions value;
} Opt_RichEditorUpdateImageSpanStyleOptions;
typedef struct Ark_RichEditorUpdateTextSpanStyleOptions {
    Opt_Number start;
    Opt_Number end;
    struct Ark_RichEditorTextStyle textStyle;
} Ark_RichEditorUpdateTextSpanStyleOptions;
typedef struct Opt_RichEditorUpdateTextSpanStyleOptions {
    enum Ark_Tag tag;
    Ark_RichEditorUpdateTextSpanStyleOptions value;
} Opt_RichEditorUpdateTextSpanStyleOptions;
typedef struct Ark_RichEditorGesture {
    struct Opt_Function onClick;
    struct Opt_Function onLongPress;
} Ark_RichEditorGesture;
typedef struct Opt_RichEditorGesture {
    enum Ark_Tag tag;
    Ark_RichEditorGesture value;
} Opt_RichEditorGesture;
typedef struct Ark_TextMenuItemId {
    void *handle;
} Ark_TextMenuItemId;
typedef struct Opt_TextMenuItemId {
    enum Ark_Tag tag;
    Ark_TextMenuItemId value;
} Opt_TextMenuItemId;
typedef Ark_Int32 Ark_LaunchMode;
typedef struct Opt_LaunchMode {
    enum Ark_Tag tag;
    Ark_LaunchMode value;
} Opt_LaunchMode;
typedef Ark_Int32 Ark_Axis;
typedef struct Opt_Axis {
    enum Ark_Tag tag;
    Ark_Axis value;
} Opt_Axis;
typedef struct Union_ScrollAnimationOptions_Boolean {
    Ark_Int32 selector;
    union {
        struct Ark_ScrollAnimationOptions value0;
        Ark_Boolean value1;
    };
} Union_ScrollAnimationOptions_Boolean;
typedef struct Opt_Union_ScrollAnimationOptions_Boolean {
    enum Ark_Tag tag;
    Union_ScrollAnimationOptions_Boolean value;
} Opt_Union_ScrollAnimationOptions_Boolean;
typedef struct Ark_Uint8ClampedArray {
    void *handle;
} Ark_Uint8ClampedArray;
typedef struct Opt_Uint8ClampedArray {
    enum Ark_Tag tag;
    Ark_Uint8ClampedArray value;
} Opt_Uint8ClampedArray;
typedef Ark_Materialized Ark_ImageBitmap;
typedef struct Opt_ImageBitmap {
    enum Ark_Tag tag;
    Ark_ImageBitmap value;
} Opt_ImageBitmap;
typedef Ark_Int32 Ark_PanDirection;
typedef struct Opt_PanDirection {
    enum Ark_Tag tag;
    Ark_PanDirection value;
} Opt_PanDirection;
typedef struct Ark_LinearIndicatorStyle {
    Opt_CustomObject space;
    Opt_CustomObject strokeWidth;
    Opt_CustomObject strokeRadius;
    Opt_CustomObject trackBackgroundColor;
    Opt_CustomObject trackColor;
} Ark_LinearIndicatorStyle;
typedef struct Opt_LinearIndicatorStyle {
    enum Ark_Tag tag;
    Ark_LinearIndicatorStyle value;
} Opt_LinearIndicatorStyle;
typedef Ark_Int32 Ark_DpiFollowStrategy;
typedef struct Opt_DpiFollowStrategy {
    enum Ark_Tag tag;
    Ark_DpiFollowStrategy value;
} Opt_DpiFollowStrategy;
typedef Ark_Int32 Ark_WaterFlowLayoutMode;
typedef struct Opt_WaterFlowLayoutMode {
    enum Ark_Tag tag;
    Ark_WaterFlowLayoutMode value;
} Opt_WaterFlowLayoutMode;
typedef Ark_Materialized Ark_WaterFlowSections;
typedef struct Opt_WaterFlowSections {
    enum Ark_Tag tag;
    Ark_WaterFlowSections value;
} Opt_WaterFlowSections;
typedef Ark_Materialized Ark_Scroller;
typedef struct Opt_Scroller {
    enum Ark_Tag tag;
    Ark_Scroller value;
} Opt_Scroller;
typedef struct Ark_RRect {
    Ark_Number left;
    Ark_Number top;
    Ark_Number width;
    Ark_Number height;
    Ark_Number radius;
} Ark_RRect;
typedef struct Opt_RRect {
    enum Ark_Tag tag;
    Ark_RRect value;
} Opt_RRect;
typedef struct Ark_DividerStyle {
    Ark_Length strokeWidth;
    struct Opt_ResourceColor color;
    Opt_Length startMargin;
    Opt_Length endMargin;
} Ark_DividerStyle;
typedef struct Opt_DividerStyle {
    enum Ark_Tag tag;
    Ark_DividerStyle value;
} Opt_DividerStyle;
typedef struct Literal_Union_String_CustomObject_Resource_shown_hidden_Opt_Union_String_CustomObject_Resource_switching {
    struct Union_String_CustomObject_Resource shown;
    struct Union_String_CustomObject_Resource hidden;
    struct Opt_Union_String_CustomObject_Resource switching;
} Literal_Union_String_CustomObject_Resource_shown_hidden_Opt_Union_String_CustomObject_Resource_switching;
typedef struct Opt_Literal_Union_String_CustomObject_Resource_shown_hidden_Opt_Union_String_CustomObject_Resource_switching {
    enum Ark_Tag tag;
    Literal_Union_String_CustomObject_Resource_shown_hidden_Opt_Union_String_CustomObject_Resource_switching value;
} Opt_Literal_Union_String_CustomObject_Resource_shown_hidden_Opt_Union_String_CustomObject_Resource_switching;
typedef struct Ark_ImageAIOptions {
    struct Opt_Array_ImageAnalyzerType types;
    Opt_ImageAnalyzerController aiController;
} Ark_ImageAIOptions;
typedef struct Opt_ImageAIOptions {
    enum Ark_Tag tag;
    Ark_ImageAIOptions value;
} Opt_ImageAIOptions;
typedef Ark_Materialized Ark_XComponentController;
typedef struct Opt_XComponentController {
    enum Ark_Tag tag;
    Ark_XComponentController value;
} Opt_XComponentController;
typedef Ark_Int32 Ark_XComponentType;
typedef struct Opt_XComponentType {
    enum Ark_Tag tag;
    Ark_XComponentType value;
} Opt_XComponentType;
typedef struct Ark_NestedScrollOptionsExt {
    Opt_NestedScrollMode scrollUp;
    Opt_NestedScrollMode scrollDown;
    Opt_NestedScrollMode scrollRight;
    Opt_NestedScrollMode scrollLeft;
} Ark_NestedScrollOptionsExt;
typedef struct Opt_NestedScrollOptionsExt {
    enum Ark_Tag tag;
    Ark_NestedScrollOptionsExt value;
} Opt_NestedScrollOptionsExt;
typedef struct Ark_NestedScrollOptions {
    Ark_NestedScrollMode scrollForward;
    Ark_NestedScrollMode scrollBackward;
} Ark_NestedScrollOptions;
typedef struct Opt_NestedScrollOptions {
    enum Ark_Tag tag;
    Ark_NestedScrollOptions value;
} Opt_NestedScrollOptions;
typedef struct Union_WebController_CustomObject {
    Ark_Int32 selector;
    union {
        Ark_WebController value0;
        Ark_CustomObject value1;
    };
} Union_WebController_CustomObject;
typedef struct Opt_Union_WebController_CustomObject {
    enum Ark_Tag tag;
    Union_WebController_CustomObject value;
} Opt_Union_WebController_CustomObject;
typedef Ark_Int32 Ark_RenderMode;
typedef struct Opt_RenderMode {
    enum Ark_Tag tag;
    Ark_RenderMode value;
} Opt_RenderMode;
typedef Ark_Materialized Ark_VideoController;
typedef struct Opt_VideoController {
    enum Ark_Tag tag;
    Ark_VideoController value;
} Opt_VideoController;
typedef struct Union_Number_String_PlaybackSpeed {
    Ark_Int32 selector;
    union {
        Ark_Number value0;
        Ark_String value1;
        Ark_PlaybackSpeed value2;
    };
} Union_Number_String_PlaybackSpeed;
typedef struct Opt_Union_Number_String_PlaybackSpeed {
    enum Ark_Tag tag;
    Union_Number_String_PlaybackSpeed value;
} Opt_Union_Number_String_PlaybackSpeed;
typedef Ark_Int32 Ark_ToggleType;
typedef struct Opt_ToggleType {
    enum Ark_Tag tag;
    Ark_ToggleType value;
} Opt_ToggleType;
typedef Ark_Int32 Ark_TimePickerFormat;
typedef struct Opt_TimePickerFormat {
    enum Ark_Tag tag;
    Ark_TimePickerFormat value;
} Opt_TimePickerFormat;
typedef Ark_Materialized Ark_TextTimerController;
typedef struct Opt_TextTimerController {
    enum Ark_Tag tag;
    Ark_TextTimerController value;
} Opt_TextTimerController;
typedef struct Union_Number_Array_Number {
    Ark_Int32 selector;
    union {
        Ark_Number value0;
        struct Array_Number value1;
    };
} Union_Number_Array_Number;
typedef struct Opt_Union_Number_Array_Number {
    enum Ark_Tag tag;
    Union_Number_Array_Number value;
} Opt_Union_Number_Array_Number;
typedef struct Union_String_Array_String {
    Ark_Int32 selector;
    union {
        Ark_String value0;
        struct Array_String value1;
    };
} Union_String_Array_String;
typedef struct Opt_Union_String_Array_String {
    enum Ark_Tag tag;
    Union_String_Array_String value;
} Opt_Union_String_Array_String;
typedef struct Union_Array_String_Array_Array_String_Resource_Array_TextPickerRangeContent_Array_TextCascadePickerRangeContent {
    Ark_Int32 selector;
    union {
        struct Array_String value0;
        struct Array_Array_String value1;
        struct Ark_Resource value2;
        struct Array_TextPickerRangeContent value3;
        struct Array_TextCascadePickerRangeContent value4;
    };
} Union_Array_String_Array_Array_String_Resource_Array_TextPickerRangeContent_Array_TextCascadePickerRangeContent;
typedef struct Opt_Union_Array_String_Array_Array_String_Resource_Array_TextPickerRangeContent_Array_TextCascadePickerRangeContent {
    enum Ark_Tag tag;
    Union_Array_String_Array_Array_String_Resource_Array_TextPickerRangeContent_Array_TextCascadePickerRangeContent value;
} Opt_Union_Array_String_Array_Array_String_Resource_Array_TextPickerRangeContent_Array_TextCascadePickerRangeContent;
typedef struct Ark_UnderlineColor {
    struct Opt_Union_ResourceColor_Undefined typing;
    struct Opt_Union_ResourceColor_Undefined normal;
    struct Opt_Union_ResourceColor_Undefined error;
    struct Opt_Union_ResourceColor_Undefined disable;
} Ark_UnderlineColor;
typedef struct Opt_UnderlineColor {
    enum Ark_Tag tag;
    Ark_UnderlineColor value;
} Opt_UnderlineColor;
typedef Ark_Int32 Ark_TextContentStyle;
typedef struct Opt_TextContentStyle {
    enum Ark_Tag tag;
    Ark_TextContentStyle value;
} Opt_TextContentStyle;
typedef Ark_Int32 Ark_TextInputStyle;
typedef struct Opt_TextInputStyle {
    enum Ark_Tag tag;
    Ark_TextInputStyle value;
} Opt_TextInputStyle;
typedef Ark_Materialized Ark_TextInputController;
typedef struct Opt_TextInputController {
    enum Ark_Tag tag;
    Ark_TextInputController value;
} Opt_TextInputController;
typedef Ark_Materialized Ark_TextClockController;
typedef struct Opt_TextClockController {
    enum Ark_Tag tag;
    Ark_TextClockController value;
} Opt_TextClockController;
typedef Ark_Materialized Ark_TextAreaController;
typedef struct Opt_TextAreaController {
    enum Ark_Tag tag;
    Ark_TextAreaController value;
} Opt_TextAreaController;
typedef Ark_Materialized Ark_TextController;
typedef struct Opt_TextController {
    enum Ark_Tag tag;
    Ark_TextController value;
} Opt_TextController;
typedef struct Ark_BottomTabBarStyle {
    struct Opt_LabelStyle _labelStyle;
    struct Opt_Union_Padding_Length_LocalizedPadding _padding;
    Opt_LayoutMode _layoutMode;
    Opt_VerticalAlign _verticalAlign;
    Opt_Boolean _symmetricExtensible;
    Opt_String _id;
    struct Opt_TabBarIconStyle _iconStyle;
} Ark_BottomTabBarStyle;
typedef struct Opt_BottomTabBarStyle {
    enum Ark_Tag tag;
    Ark_BottomTabBarStyle value;
} Opt_BottomTabBarStyle;
typedef struct Ark_SubTabBarStyle {
    struct Opt_IndicatorStyle _indicator;
    Opt_SelectedMode _selectedMode;
    struct Opt_BoardStyle _board;
    struct Opt_LabelStyle _labelStyle;
    struct Opt_Union_Padding_Length _padding;
    Opt_String _id;
} Ark_SubTabBarStyle;
typedef struct Opt_SubTabBarStyle {
    enum Ark_Tag tag;
    Ark_SubTabBarStyle value;
} Opt_SubTabBarStyle;
typedef struct Literal_Opt_Union_String_Resource_icon_text {
    struct Opt_Union_String_Resource icon;
    struct Opt_Union_String_Resource text;
} Literal_Opt_Union_String_Resource_icon_text;
typedef struct Opt_Literal_Opt_Union_String_Resource_icon_text {
    enum Ark_Tag tag;
    Literal_Opt_Union_String_Resource_icon_text value;
} Opt_Literal_Opt_Union_String_Resource_icon_text;
typedef Ark_Int32 Ark_EdgeEffect;
typedef struct Opt_EdgeEffect {
    enum Ark_Tag tag;
    Ark_EdgeEffect value;
} Opt_EdgeEffect;
typedef Ark_Int32 Ark_AnimationMode;
typedef struct Opt_AnimationMode {
    enum Ark_Tag tag;
    Ark_AnimationMode value;
} Opt_AnimationMode;
typedef Ark_Int32 Ark_LayoutStyle;
typedef struct Opt_LayoutStyle {
    enum Ark_Tag tag;
    Ark_LayoutStyle value;
} Opt_LayoutStyle;
typedef Ark_Materialized Ark_TabsController;
typedef struct Opt_TabsController {
    enum Ark_Tag tag;
    Ark_TabsController value;
} Opt_TabsController;
typedef Ark_Int32 Ark_BarPosition;
typedef struct Opt_BarPosition {
    enum Ark_Tag tag;
    Ark_BarPosition value;
} Opt_BarPosition;
typedef struct Ark_SwiperAutoFill {
    struct Ark_VP minSize;
} Ark_SwiperAutoFill;
typedef struct Opt_SwiperAutoFill {
    enum Ark_Tag tag;
    Ark_SwiperAutoFill value;
} Opt_SwiperAutoFill;
typedef struct Ark_ArrowStyle {
    Opt_Boolean showBackground;
    Opt_Boolean isSidebarMiddle;
    Opt_Length backgroundSize;
    struct Opt_ResourceColor backgroundColor;
    Opt_Length arrowSize;
    struct Opt_ResourceColor arrowColor;
} Ark_ArrowStyle;
typedef struct Opt_ArrowStyle {
    enum Ark_Tag tag;
    Ark_ArrowStyle value;
} Opt_ArrowStyle;
typedef struct Ark_DigitIndicator {
    Opt_Length _left;
    Opt_Length _top;
    Opt_Length _right;
    Opt_Length _bottom;
    Opt_CustomObject _start;
    Opt_CustomObject _end;
    struct Opt_ResourceColor _fontColor;
    struct Opt_ResourceColor _selectedFontColor;
    struct Opt_Font _digitFont;
    struct Opt_Font _selectedDigitFont;
} Ark_DigitIndicator;
typedef struct Opt_DigitIndicator {
    enum Ark_Tag tag;
    Ark_DigitIndicator value;
} Opt_DigitIndicator;
typedef struct Ark_DotIndicator {
    Opt_Length _left;
    Opt_Length _top;
    Opt_Length _right;
    Opt_Length _bottom;
    Opt_CustomObject _start;
    Opt_CustomObject _end;
    Opt_Length _itemWidth;
    Opt_Length _itemHeight;
    Opt_Length _selectedItemWidth;
    Opt_Length _selectedItemHeight;
    Opt_Boolean _mask;
    struct Opt_ResourceColor _color;
    struct Opt_ResourceColor _selectedColor;
    Opt_Number _maxDisplayCount;
} Ark_DotIndicator;
typedef struct Opt_DotIndicator {
    enum Ark_Tag tag;
    Ark_DotIndicator value;
} Opt_DotIndicator;
typedef Ark_Int32 Ark_Alignment;
typedef struct Opt_Alignment {
    enum Ark_Tag tag;
    Ark_Alignment value;
} Opt_Alignment;
typedef struct Union_CircleAttribute_EllipseAttribute_PathAttribute_RectAttribute {
    Ark_Int32 selector;
    union {
        struct Ark_CircleAttribute value0;
        struct Ark_EllipseAttribute value1;
        struct Ark_PathAttribute value2;
        struct Ark_RectAttribute value3;
    };
} Union_CircleAttribute_EllipseAttribute_PathAttribute_RectAttribute;
typedef struct Opt_Union_CircleAttribute_EllipseAttribute_PathAttribute_RectAttribute {
    enum Ark_Tag tag;
    Union_CircleAttribute_EllipseAttribute_PathAttribute_RectAttribute value;
} Opt_Union_CircleAttribute_EllipseAttribute_PathAttribute_RectAttribute;
typedef Ark_Int32 Ark_SliderBlockType;
typedef struct Opt_SliderBlockType {
    enum Ark_Tag tag;
    Ark_SliderBlockType value;
} Opt_SliderBlockType;
typedef Ark_Int32 Ark_SliderStyle;
typedef struct Opt_SliderStyle {
    enum Ark_Tag tag;
    Ark_SliderStyle value;
} Opt_SliderStyle;
typedef Ark_Int32 Ark_OptionWidthMode;
typedef struct Opt_OptionWidthMode {
    enum Ark_Tag tag;
    Ark_OptionWidthMode value;
} Opt_OptionWidthMode;
typedef struct Ark_CancelButtonSymbolOptions {
    Opt_CancelButtonStyle style;
    Opt_CustomObject icon;
} Ark_CancelButtonSymbolOptions;
typedef struct Opt_CancelButtonSymbolOptions {
    enum Ark_Tag tag;
    Ark_CancelButtonSymbolOptions value;
} Opt_CancelButtonSymbolOptions;
typedef struct Ark_CancelButtonOptions {
    Opt_CancelButtonStyle style;
    struct Opt_IconOptions icon;
} Ark_CancelButtonOptions;
typedef struct Opt_CancelButtonOptions {
    enum Ark_Tag tag;
    Ark_CancelButtonOptions value;
} Opt_CancelButtonOptions;
typedef Ark_Materialized Ark_SearchController;
typedef struct Opt_SearchController {
    enum Ark_Tag tag;
    Ark_SearchController value;
} Opt_SearchController;
typedef Ark_Int32 Ark_BarState;
typedef struct Opt_BarState {
    enum Ark_Tag tag;
    Ark_BarState value;
} Opt_BarState;
typedef Ark_Int32 Ark_ScrollBarDirection;
typedef struct Opt_ScrollBarDirection {
    enum Ark_Tag tag;
    Ark_ScrollBarDirection value;
} Opt_ScrollBarDirection;
typedef struct Union_Length_Array_Length {
    Ark_Int32 selector;
    union {
        Ark_Length value0;
        struct Array_Length value1;
    };
} Union_Length_Array_Length;
typedef struct Opt_Union_Length_Array_Length {
    enum Ark_Tag tag;
    Union_Length_Array_Length value;
} Opt_Union_Length_Array_Length;
typedef Ark_Int32 Ark_ScrollSnapAlign;
typedef struct Opt_ScrollSnapAlign {
    enum Ark_Tag tag;
    Ark_ScrollSnapAlign value;
} Opt_ScrollSnapAlign;
typedef Ark_Int32 Ark_ButtonType;
typedef struct Opt_ButtonType {
    enum Ark_Tag tag;
    Ark_ButtonType value;
} Opt_ButtonType;
typedef Ark_Int32 Ark_SaveDescription;
typedef struct Opt_SaveDescription {
    enum Ark_Tag tag;
    Ark_SaveDescription value;
} Opt_SaveDescription;
typedef Ark_Int32 Ark_SaveIconStyle;
typedef struct Opt_SaveIconStyle {
    enum Ark_Tag tag;
    Ark_SaveIconStyle value;
} Opt_SaveIconStyle;
typedef struct Union_String_Number {
    Ark_Int32 selector;
    union {
        Ark_String value0;
        Ark_Number value1;
    };
} Union_String_Number;
typedef struct Opt_Union_String_Number {
    enum Ark_Tag tag;
    Union_String_Number value;
} Opt_Union_String_Number;
typedef int32_t Ark_TextDataDetectorType;
typedef struct Array_TextDataDetectorType {
    Ark_TextDataDetectorType* array;
    Ark_Int32 length;
} Array_TextDataDetectorType;
typedef int32_t Ark_TextDataDetectorType;
typedef struct Opt_Array_TextDataDetectorType {
    enum Ark_Tag tag;
    Array_TextDataDetectorType value;
} Opt_Array_TextDataDetectorType;
typedef Ark_Int32 Ark_RichEditorResponseType;
typedef struct Opt_RichEditorResponseType {
    enum Ark_Tag tag;
    Ark_RichEditorResponseType value;
} Opt_RichEditorResponseType;
typedef Ark_Int32 Ark_ResponseType;
typedef struct Opt_ResponseType {
    enum Ark_Tag tag;
    Ark_ResponseType value;
} Opt_ResponseType;
typedef Ark_Materialized Ark_RichEditorStyledStringController;
typedef struct Opt_RichEditorStyledStringController {
    enum Ark_Tag tag;
    Ark_RichEditorStyledStringController value;
} Opt_RichEditorStyledStringController;
typedef Ark_Materialized Ark_RichEditorController;
typedef struct Opt_RichEditorController {
    enum Ark_Tag tag;
    Ark_RichEditorController value;
} Opt_RichEditorController;
typedef Ark_Int32 Ark_LocalizedBarrierDirection;
typedef struct Opt_LocalizedBarrierDirection {
    enum Ark_Tag tag;
    Ark_LocalizedBarrierDirection value;
} Opt_LocalizedBarrierDirection;
typedef Ark_Int32 Ark_BarrierDirection;
typedef struct Opt_BarrierDirection {
    enum Ark_Tag tag;
    Ark_BarrierDirection value;
} Opt_BarrierDirection;
typedef struct Ark_GuideLinePosition {
    Opt_Length start;
    Opt_Length end;
} Ark_GuideLinePosition;
typedef struct Opt_GuideLinePosition {
    enum Ark_Tag tag;
    Ark_GuideLinePosition value;
} Opt_GuideLinePosition;
typedef struct Literal_Opt_Union_Number_String_width_height_radiusWidth_radiusHeight {
    struct Opt_Union_Number_String width;
    struct Opt_Union_Number_String height;
    struct Opt_Union_Number_String radiusWidth;
    struct Opt_Union_Number_String radiusHeight;
} Literal_Opt_Union_Number_String_width_height_radiusWidth_radiusHeight;
typedef struct Opt_Literal_Opt_Union_Number_String_width_height_radiusWidth_radiusHeight {
    enum Ark_Tag tag;
    Literal_Opt_Union_Number_String_width_height_radiusWidth_radiusHeight value;
} Opt_Literal_Opt_Union_Number_String_width_height_radiusWidth_radiusHeight;
typedef struct Literal_Opt_Union_Number_String_width_height_Opt_Union_Number_String_Array_CustomObject_radius {
    struct Opt_Union_Number_String width;
    struct Opt_Union_Number_String height;
    struct Opt_Union_Number_String_Array_CustomObject radius;
} Literal_Opt_Union_Number_String_width_height_Opt_Union_Number_String_Array_CustomObject_radius;
typedef struct Opt_Literal_Opt_Union_Number_String_width_height_Opt_Union_Number_String_Array_CustomObject_radius {
    enum Ark_Tag tag;
    Literal_Opt_Union_Number_String_width_height_Opt_Union_Number_String_Array_CustomObject_radius value;
} Opt_Literal_Opt_Union_Number_String_width_height_Opt_Union_Number_String_Array_CustomObject_radius;
typedef Ark_Int32 Ark_RadioIndicatorType;
typedef struct Opt_RadioIndicatorType {
    enum Ark_Tag tag;
    Ark_RadioIndicatorType value;
} Opt_RadioIndicatorType;
typedef struct Ark_PluginComponentTemplate {
    Ark_String source;
    Ark_String bundleName;
} Ark_PluginComponentTemplate;
typedef struct Opt_PluginComponentTemplate {
    enum Ark_Tag tag;
    Ark_PluginComponentTemplate value;
} Opt_PluginComponentTemplate;
typedef struct Ark_CircleStyleOptions {
    struct Opt_ResourceColor color;
    Opt_CustomObject radius;
    Opt_Boolean enableWaveEffect;
} Ark_CircleStyleOptions;
typedef struct Opt_CircleStyleOptions {
    enum Ark_Tag tag;
    Ark_CircleStyleOptions value;
} Opt_CircleStyleOptions;
typedef Ark_Int32 Ark_PasteDescription;
typedef struct Opt_PasteDescription {
    enum Ark_Tag tag;
    Ark_PasteDescription value;
} Opt_PasteDescription;
typedef Ark_Int32 Ark_PasteIconStyle;
typedef struct Opt_PasteIconStyle {
    enum Ark_Tag tag;
    Ark_PasteIconStyle value;
} Opt_PasteIconStyle;
typedef Ark_Int32 Ark_PanelHeight;
typedef struct Opt_PanelHeight {
    enum Ark_Tag tag;
    Ark_PanelHeight value;
} Opt_PanelHeight;
typedef Ark_Int32 Ark_NavigationType;
typedef struct Opt_NavigationType {
    enum Ark_Tag tag;
    Ark_NavigationType value;
} Opt_NavigationType;
typedef Ark_Int32 Ark_ToolbarItemStatus;
typedef struct Opt_ToolbarItemStatus {
    enum Ark_Tag tag;
    Ark_ToolbarItemStatus value;
} Opt_ToolbarItemStatus;
typedef struct Array_ToolbarItem {
    struct Ark_ToolbarItem* array;
    Ark_Int32 length;
} Array_ToolbarItem;
typedef struct Opt_Array_ToolbarItem {
    enum Ark_Tag tag;
    Array_ToolbarItem value;
} Opt_Array_ToolbarItem;
typedef struct Array_NavigationMenuItem {
    struct Ark_NavigationMenuItem* array;
    Ark_Int32 length;
} Array_NavigationMenuItem;
typedef struct Opt_Array_NavigationMenuItem {
    enum Ark_Tag tag;
    Array_NavigationMenuItem value;
} Opt_Array_NavigationMenuItem;
typedef struct Ark_NavigationCustomTitle {
    struct Ark_CustomBuilder builder;
    struct Union_TitleHeight_Length height;
} Ark_NavigationCustomTitle;
typedef struct Opt_NavigationCustomTitle {
    enum Ark_Tag tag;
    Ark_NavigationCustomTitle value;
} Opt_NavigationCustomTitle;
typedef struct Ark_NavigationCommonTitle {
    Ark_String main;
    Ark_String sub;
} Ark_NavigationCommonTitle;
typedef struct Opt_NavigationCommonTitle {
    enum Ark_Tag tag;
    Ark_NavigationCommonTitle value;
} Opt_NavigationCommonTitle;
typedef Ark_Int32 Ark_BarStyle;
typedef struct Opt_BarStyle {
    enum Ark_Tag tag;
    Ark_BarStyle value;
} Opt_BarStyle;
typedef struct Ark_NavDestinationCustomTitle {
    struct Ark_CustomBuilder builder;
    struct Union_TitleHeight_Length height;
} Ark_NavDestinationCustomTitle;
typedef struct Opt_NavDestinationCustomTitle {
    enum Ark_Tag tag;
    Ark_NavDestinationCustomTitle value;
} Opt_NavDestinationCustomTitle;
typedef struct Ark_NavDestinationCommonTitle {
    Ark_String main;
    Ark_String sub;
} Ark_NavDestinationCommonTitle;
typedef struct Opt_NavDestinationCommonTitle {
    enum Ark_Tag tag;
    Ark_NavDestinationCommonTitle value;
} Opt_NavDestinationCommonTitle;
typedef struct Union_Ark_ResourceStr_Ark_CustomBuilder {
    Ark_Int32 selector;
    union {
        struct Ark_ResourceStr value0;
        struct Ark_CustomBuilder value1;
    };
} Union_Ark_ResourceStr_Ark_CustomBuilder;
typedef struct Opt_Union_ResourceStr_Ark_CustomBuilder {
    enum Ark_Tag tag;
    Union_Ark_ResourceStr_Ark_CustomBuilder value;
} Opt_Union_ResourceStr_Ark_CustomBuilder;
typedef struct Ark_MenuItemOptions {
    struct Opt_ResourceStr startIcon;
    Opt_CustomObject symbolStartIcon;
    struct Opt_ResourceStr content;
    struct Opt_ResourceStr endIcon;
    Opt_CustomObject symbolEndIcon;
    struct Opt_ResourceStr labelInfo;
    struct Opt_CustomBuilder builder;
} Ark_MenuItemOptions;
typedef struct Opt_MenuItemOptions {
    enum Ark_Tag tag;
    Ark_MenuItemOptions value;
} Opt_MenuItemOptions;
typedef struct Ark_DividerStyleOptions {
    Opt_CustomObject strokeWidth;
    struct Opt_ResourceColor color;
    Opt_CustomObject startMargin;
    Opt_CustomObject endMargin;
} Ark_DividerStyleOptions;
typedef struct Opt_DividerStyleOptions {
    enum Ark_Tag tag;
    Ark_DividerStyleOptions value;
} Opt_DividerStyleOptions;
typedef struct Ark_ASTCResource {
    struct Array_String sources;
    Ark_Number column;
} Ark_ASTCResource;
typedef struct Opt_ASTCResource {
    enum Ark_Tag tag;
    Ark_ASTCResource value;
} Opt_ASTCResource;
typedef Ark_Int32 Ark_LocationDescription;
typedef struct Opt_LocationDescription {
    enum Ark_Tag tag;
    Ark_LocationDescription value;
} Opt_LocationDescription;
typedef Ark_Int32 Ark_LocationIconStyle;
typedef struct Opt_LocationIconStyle {
    enum Ark_Tag tag;
    Ark_LocationIconStyle value;
} Opt_LocationIconStyle;
typedef struct Ark_LocalizedEdges {
    Opt_CustomObject top;
    Opt_CustomObject start;
    Opt_CustomObject bottom;
    Opt_CustomObject end;
} Ark_LocalizedEdges;
typedef struct Opt_LocalizedEdges {
    enum Ark_Tag tag;
    Ark_LocalizedEdges value;
} Opt_LocalizedEdges;
typedef struct Ark_Edges {
    Opt_Length top;
    Opt_Length left;
    Opt_Length bottom;
    Opt_Length right;
} Ark_Edges;
typedef struct Opt_Edges {
    enum Ark_Tag tag;
    Ark_Edges value;
} Opt_Edges;
typedef struct Ark_ListDividerOptions {
    Ark_Length strokeWidth;
    struct Opt_ResourceColor color;
    Opt_Length startMargin;
    Opt_Length endMargin;
} Ark_ListDividerOptions;
typedef struct Opt_ListDividerOptions {
    enum Ark_Tag tag;
    Ark_ListDividerOptions value;
} Opt_ListDividerOptions;
typedef Ark_Int32 Ark_ListItemGroupStyle;
typedef struct Opt_ListItemGroupStyle {
    enum Ark_Tag tag;
    Ark_ListItemGroupStyle value;
} Opt_ListItemGroupStyle;
typedef Ark_Int32 Ark_SwipeEdgeEffect;
typedef struct Opt_SwipeEdgeEffect {
    enum Ark_Tag tag;
    Ark_SwipeEdgeEffect value;
} Opt_SwipeEdgeEffect;
typedef struct Union_Ark_CustomBuilder_SwipeActionItem {
    Ark_Int32 selector;
    union {
        struct Ark_CustomBuilder value0;
        struct Ark_SwipeActionItem value1;
    };
} Union_Ark_CustomBuilder_SwipeActionItem;
typedef struct Opt_Union_CustomBuilder_SwipeActionItem {
    enum Ark_Tag tag;
    Union_Ark_CustomBuilder_SwipeActionItem value;
} Opt_Union_CustomBuilder_SwipeActionItem;
typedef Ark_Int32 Ark_EditMode;
typedef struct Opt_EditMode {
    enum Ark_Tag tag;
    Ark_EditMode value;
} Opt_EditMode;
typedef Ark_Int32 Ark_ListItemStyle;
typedef struct Opt_ListItemStyle {
    enum Ark_Tag tag;
    Ark_ListItemStyle value;
} Opt_ListItemStyle;
typedef Ark_Int32 Ark_ChainEdgeEffect;
typedef struct Opt_ChainEdgeEffect {
    enum Ark_Tag tag;
    Ark_ChainEdgeEffect value;
} Opt_ChainEdgeEffect;
typedef struct Ark_LengthConstrain {
    Ark_Length minLength;
    Ark_Length maxLength;
} Ark_LengthConstrain;
typedef struct Opt_LengthConstrain {
    enum Ark_Tag tag;
    Ark_LengthConstrain value;
} Opt_LengthConstrain;
typedef struct Ark_ColorFilter {
    void *handle;
} Ark_ColorFilter;
typedef struct Opt_ColorFilter {
    enum Ark_Tag tag;
    Ark_ColorFilter value;
} Opt_ColorFilter;
typedef struct Union_String_Resource_CustomObject {
    Ark_Int32 selector;
    union {
        Ark_String value0;
        struct Ark_Resource value1;
        Ark_CustomObject value2;
    };
} Union_String_Resource_CustomObject;
typedef struct Opt_Union_String_Resource_CustomObject {
    enum Ark_Tag tag;
    Union_String_Resource_CustomObject value;
} Opt_Union_String_Resource_CustomObject;
typedef Ark_Int32 Ark_ImageContent;
typedef struct Opt_ImageContent {
    enum Ark_Tag tag;
    Ark_ImageContent value;
} Opt_ImageContent;
typedef Ark_Int32 Ark_GridRowDirection;
typedef struct Opt_GridRowDirection {
    enum Ark_Tag tag;
    Ark_GridRowDirection value;
} Opt_GridRowDirection;
typedef struct Ark_BreakPoints {
    struct Opt_Array_String value;
    Opt_BreakpointsReference reference;
} Ark_BreakPoints;
typedef struct Opt_BreakPoints {
    enum Ark_Tag tag;
    Ark_BreakPoints value;
} Opt_BreakPoints;
typedef struct Union_Number_GridRowColumnOption {
    Ark_Int32 selector;
    union {
        Ark_Number value0;
        struct Ark_GridRowColumnOption value1;
    };
} Union_Number_GridRowColumnOption;
typedef struct Opt_Union_Number_GridRowColumnOption {
    enum Ark_Tag tag;
    Union_Number_GridRowColumnOption value;
} Opt_Union_Number_GridRowColumnOption;
typedef struct Union_Length_GutterOption {
    Ark_Int32 selector;
    union {
        Ark_Length value0;
        struct Ark_GutterOption value1;
    };
} Union_Length_GutterOption;
typedef struct Opt_Union_Length_GutterOption {
    enum Ark_Tag tag;
    Union_Length_GutterOption value;
} Opt_Union_Length_GutterOption;
typedef Ark_Int32 Ark_SizeType;
typedef struct Opt_SizeType {
    enum Ark_Tag tag;
    Ark_SizeType value;
} Opt_SizeType;
typedef struct Union_Number_GridColColumnOption {
    Ark_Int32 selector;
    union {
        Ark_Number value0;
        struct Ark_GridColColumnOption value1;
    };
} Union_Number_GridColColumnOption;
typedef struct Opt_Union_Number_GridColColumnOption {
    enum Ark_Tag tag;
    Union_Number_GridColColumnOption value;
} Opt_Union_Number_GridColColumnOption;
typedef Ark_Int32 Ark_GridItemStyle;
typedef struct Opt_GridItemStyle {
    enum Ark_Tag tag;
    Ark_GridItemStyle value;
} Opt_GridItemStyle;
typedef Ark_Int32 Ark_GridItemAlignment;
typedef struct Opt_GridItemAlignment {
    enum Ark_Tag tag;
    Ark_GridItemAlignment value;
} Opt_GridItemAlignment;
typedef struct Ark_MultiShadowOptions {
    struct Opt_Union_Number_Resource radius;
    struct Opt_Union_Number_Resource offsetX;
    struct Opt_Union_Number_Resource offsetY;
} Ark_MultiShadowOptions;
typedef struct Opt_MultiShadowOptions {
    enum Ark_Tag tag;
    Ark_MultiShadowOptions value;
} Opt_MultiShadowOptions;
typedef struct Union_Ark_ResourceColor_LinearGradient {
    Ark_Int32 selector;
    union {
        struct Ark_ResourceColor value0;
        struct Ark_LinearGradient value1;
    };
} Union_Ark_ResourceColor_LinearGradient;
typedef struct Opt_Union_ResourceColor_LinearGradient {
    enum Ark_Tag tag;
    Union_Ark_ResourceColor_LinearGradient value;
} Opt_Union_ResourceColor_LinearGradient;
typedef struct Array_Tuple_Union_Ark_ResourceColor_LinearGradient_Number {
    struct Tuple_Union_Ark_ResourceColor_LinearGradient_Number* array;
    Ark_Int32 length;
} Array_Tuple_Union_Ark_ResourceColor_LinearGradient_Number;
typedef struct Opt_Array_Tuple_Union_ResourceColor_LinearGradient_Number {
    enum Ark_Tag tag;
    Array_Tuple_Union_Ark_ResourceColor_LinearGradient_Number value;
} Opt_Array_Tuple_Union_ResourceColor_LinearGradient_Number;
typedef Ark_Int32 Ark_FormShape;
typedef struct Opt_FormShape {
    enum Ark_Tag tag;
    Ark_FormShape value;
} Opt_FormShape;
typedef Ark_Int32 Ark_FormRenderingMode;
typedef struct Opt_FormRenderingMode {
    enum Ark_Tag tag;
    Ark_FormRenderingMode value;
} Opt_FormRenderingMode;
typedef Ark_Int32 Ark_FormDimension;
typedef struct Opt_FormDimension {
    enum Ark_Tag tag;
    Ark_FormDimension value;
} Opt_FormDimension;
typedef struct Ark_FlexSpaceOptions {
    Opt_CustomObject main;
    Opt_CustomObject cross;
} Ark_FlexSpaceOptions;
typedef struct Opt_FlexSpaceOptions {
    enum Ark_Tag tag;
    Ark_FlexSpaceOptions value;
} Opt_FlexSpaceOptions;
typedef Ark_Int32 Ark_FlexAlign;
typedef struct Opt_FlexAlign {
    enum Ark_Tag tag;
    Ark_FlexAlign value;
} Opt_FlexAlign;
typedef Ark_Int32 Ark_ItemAlign;
typedef struct Opt_ItemAlign {
    enum Ark_Tag tag;
    Ark_ItemAlign value;
} Opt_ItemAlign;
typedef Ark_Int32 Ark_FlexWrap;
typedef struct Opt_FlexWrap {
    enum Ark_Tag tag;
    Ark_FlexWrap value;
} Opt_FlexWrap;
typedef Ark_Int32 Ark_FlexDirection;
typedef struct Opt_FlexDirection {
    enum Ark_Tag tag;
    Ark_FlexDirection value;
} Opt_FlexDirection;
typedef struct Array_Union_Ark_ResourceColor_LinearGradient {
    struct Union_Ark_ResourceColor_LinearGradient* array;
    Ark_Int32 length;
} Array_Union_Ark_ResourceColor_LinearGradient;
typedef struct Opt_Array_Union_ResourceColor_LinearGradient {
    enum Ark_Tag tag;
    Array_Union_Ark_ResourceColor_LinearGradient value;
} Opt_Array_Union_ResourceColor_LinearGradient;
typedef Ark_Int32 Ark_DataPanelType;
typedef struct Opt_DataPanelType {
    enum Ark_Tag tag;
    Ark_DataPanelType value;
} Opt_DataPanelType;
typedef Ark_Int32 Ark_ModelType;
typedef struct Opt_ModelType {
    enum Ark_Tag tag;
    Ark_ModelType value;
} Opt_ModelType;
typedef struct Union_Ark_ResourceStr_CustomObject {
    Ark_Int32 selector;
    union {
        struct Ark_ResourceStr value0;
        Ark_CustomObject value1;
    };
} Union_Ark_ResourceStr_CustomObject;
typedef struct Opt_Union_ResourceStr_CustomObject {
    enum Ark_Tag tag;
    Union_Ark_ResourceStr_CustomObject value;
} Opt_Union_ResourceStr_CustomObject;
typedef struct Ark_ColumnSplitDividerStyle {
    Opt_Length startMargin;
    Opt_Length endMargin;
} Ark_ColumnSplitDividerStyle;
typedef struct Opt_ColumnSplitDividerStyle {
    enum Ark_Tag tag;
    Ark_ColumnSplitDividerStyle value;
} Opt_ColumnSplitDividerStyle;
typedef Ark_Int32 Ark_IlluminatedType;
typedef struct Opt_IlluminatedType {
    enum Ark_Tag tag;
    Ark_IlluminatedType value;
} Opt_IlluminatedType;
typedef struct Ark_LightSource {
    Ark_Length positionX;
    Ark_Length positionY;
    Ark_Length positionZ;
    Ark_Number intensity;
    struct Opt_ResourceColor color;
} Ark_LightSource;
typedef struct Opt_LightSource {
    enum Ark_Tag tag;
    Ark_LightSource value;
} Opt_LightSource;
typedef Ark_Materialized Ark_DrawingRenderingContext;
typedef struct Opt_DrawingRenderingContext {
    enum Ark_Tag tag;
    Ark_DrawingRenderingContext value;
} Opt_DrawingRenderingContext;
typedef Ark_Materialized Ark_CanvasRenderingContext2D;
typedef struct Opt_CanvasRenderingContext2D {
    enum Ark_Tag tag;
    Ark_CanvasRenderingContext2D value;
} Opt_CanvasRenderingContext2D;
typedef Ark_Materialized Ark_CalendarController;
typedef struct Opt_CalendarController {
    enum Ark_Tag tag;
    Ark_CalendarController value;
} Opt_CalendarController;
typedef struct Ark_MonthData {
    Ark_Number year;
    Ark_Number month;
    struct Array_CalendarDay data;
} Ark_MonthData;
typedef struct Opt_MonthData {
    enum Ark_Tag tag;
    Ark_MonthData value;
} Opt_MonthData;
typedef struct Literal_Number_year_month_day {
    Ark_Number year;
    Ark_Number month;
    Ark_Number day;
} Literal_Number_year_month_day;
typedef struct Opt_Literal_Number_year_month_day {
    enum Ark_Tag tag;
    Literal_Number_year_month_day value;
} Opt_Literal_Number_year_month_day;
typedef Ark_Int32 Ark_ButtonRole;
typedef struct Opt_ButtonRole {
    enum Ark_Tag tag;
    Ark_ButtonRole value;
} Opt_ButtonRole;
typedef Ark_Int32 Ark_ControlSize;
typedef struct Opt_ControlSize {
    enum Ark_Tag tag;
    Ark_ControlSize value;
} Opt_ControlSize;
typedef Ark_Int32 Ark_ButtonStyleMode;
typedef struct Opt_ButtonStyleMode {
    enum Ark_Tag tag;
    Ark_ButtonStyleMode value;
} Opt_ButtonStyleMode;
typedef struct Ark_BadgeParam {
    struct Opt_Union_BadgePosition_Position position;
    struct Ark_BadgeStyle style;
} Ark_BadgeParam;
typedef struct Opt_BadgeParam {
    enum Ark_Tag tag;
    Ark_BadgeParam value;
} Opt_BadgeParam;
typedef struct Ark_ScrollMotion {
    void *handle;
} Ark_ScrollMotion;
typedef struct Opt_ScrollMotion {
    enum Ark_Tag tag;
    Ark_ScrollMotion value;
} Opt_ScrollMotion;
typedef struct Ark_FrictionMotion {
    void *handle;
} Ark_FrictionMotion;
typedef struct Opt_FrictionMotion {
    enum Ark_Tag tag;
    Ark_FrictionMotion value;
} Opt_FrictionMotion;
typedef struct Ark_SpringMotion {
    void *handle;
} Ark_SpringMotion;
typedef struct Opt_SpringMotion {
    enum Ark_Tag tag;
    Ark_SpringMotion value;
} Opt_SpringMotion;
typedef Ark_Int32 Ark_FunctionKey;
typedef struct Opt_FunctionKey {
    enum Ark_Tag tag;
    Ark_FunctionKey value;
} Opt_FunctionKey;
typedef Ark_Int32 Ark_ScrollSizeMode;
typedef struct Opt_ScrollSizeMode {
    enum Ark_Tag tag;
    Ark_ScrollSizeMode value;
} Opt_ScrollSizeMode;
typedef Ark_Int32 Ark_SheetMode;
typedef struct Opt_SheetMode {
    enum Ark_Tag tag;
    Ark_SheetMode value;
} Opt_SheetMode;
typedef struct Union_BorderStyle_Ark_EdgeStyles {
    Ark_Int32 selector;
    union {
        Ark_BorderStyle value0;
        struct Ark_EdgeStyles value1;
    };
} Union_BorderStyle_Ark_EdgeStyles;
typedef struct Opt_Union_BorderStyle_EdgeStyles {
    enum Ark_Tag tag;
    Union_BorderStyle_Ark_EdgeStyles value;
} Opt_Union_BorderStyle_EdgeStyles;
typedef struct Union_Ark_ResourceColor_Ark_EdgeColors_LocalizedEdgeColors {
    Ark_Int32 selector;
    union {
        struct Ark_ResourceColor value0;
        struct Ark_EdgeColors value1;
        struct Ark_LocalizedEdgeColors value2;
    };
} Union_Ark_ResourceColor_Ark_EdgeColors_LocalizedEdgeColors;
typedef struct Opt_Union_ResourceColor_Ark_EdgeColors_LocalizedEdgeColors {
    enum Ark_Tag tag;
    Union_Ark_ResourceColor_Ark_EdgeColors_LocalizedEdgeColors value;
} Opt_Union_ResourceColor_Ark_EdgeColors_LocalizedEdgeColors;
typedef struct Union_Length_Ark_EdgeWidths_LocalizedEdgeWidths {
    Ark_Int32 selector;
    union {
        Ark_Length value0;
        struct Ark_EdgeWidths value1;
        struct Ark_LocalizedEdgeWidths value2;
    };
} Union_Length_Ark_EdgeWidths_LocalizedEdgeWidths;
typedef struct Opt_Union_Length_EdgeWidths_LocalizedEdgeWidths {
    enum Ark_Tag tag;
    Union_Length_Ark_EdgeWidths_LocalizedEdgeWidths value;
} Opt_Union_Length_EdgeWidths_LocalizedEdgeWidths;
typedef struct Union_SheetTitleOptions_Ark_CustomBuilder {
    Ark_Int32 selector;
    union {
        struct Ark_SheetTitleOptions value0;
        struct Ark_CustomBuilder value1;
    };
} Union_SheetTitleOptions_Ark_CustomBuilder;
typedef struct Opt_Union_SheetTitleOptions_CustomBuilder {
    enum Ark_Tag tag;
    Union_SheetTitleOptions_Ark_CustomBuilder value;
} Opt_Union_SheetTitleOptions_CustomBuilder;
typedef Ark_Int32 Ark_SheetType;
typedef struct Opt_SheetType {
    enum Ark_Tag tag;
    Ark_SheetType value;
} Opt_SheetType;
typedef struct Union_Boolean_Resource {
    Ark_Int32 selector;
    union {
        Ark_Boolean value0;
        struct Ark_Resource value1;
    };
} Union_Boolean_Resource;
typedef struct Opt_Union_Boolean_Resource {
    enum Ark_Tag tag;
    Union_Boolean_Resource value;
} Opt_Union_Boolean_Resource;
typedef struct Tuple_Union_SheetSize_Length_Opt_Union_SheetSize_Length_Opt_Union_SheetSize_Length {
    struct Union_SheetSize_Length value0;
    struct Opt_Union_SheetSize_Length value1;
    struct Opt_Union_SheetSize_Length value2;
} Tuple_Union_SheetSize_Length_Opt_Union_SheetSize_Length_Opt_Union_SheetSize_Length;
typedef struct Opt_Tuple_Union_SheetSize_Length_Opt_Union_SheetSize_Length_Opt_Union_SheetSize_Length {
    enum Ark_Tag tag;
    Tuple_Union_SheetSize_Length_Opt_Union_SheetSize_Length_Opt_Union_SheetSize_Length value;
} Opt_Tuple_Union_SheetSize_Length_Opt_Union_SheetSize_Length_Opt_Union_SheetSize_Length;
typedef struct Ark_BindOptions {
    struct Opt_ResourceColor backgroundColor;
    struct Opt_Function onAppear;
    struct Opt_Function onDisappear;
    struct Opt_Function onWillAppear;
    struct Opt_Function onWillDisappear;
} Ark_BindOptions;
typedef struct Opt_BindOptions {
    enum Ark_Tag tag;
    Ark_BindOptions value;
} Opt_BindOptions;
typedef Ark_Int32 Ark_ModalTransition;
typedef struct Opt_ModalTransition {
    enum Ark_Tag tag;
    Ark_ModalTransition value;
} Opt_ModalTransition;
typedef struct Array_MenuElement {
    struct Ark_MenuElement* array;
    Ark_Int32 length;
} Array_MenuElement;
typedef struct Opt_Array_MenuElement {
    enum Ark_Tag tag;
    Array_MenuElement value;
} Opt_Array_MenuElement;
typedef struct Ark_ContextMenuOptions {
    struct Opt_Position offset;
    Opt_Placement placement;
    Opt_Boolean enableArrow;
    Opt_Length arrowOffset;
    struct Opt_Union_MenuPreviewMode_CustomBuilder preview;
    struct Opt_Union_Length_BorderRadiuses_LocalizedBorderRadiuses borderRadius;
    struct Opt_Function onAppear;
    struct Opt_Function onDisappear;
    struct Opt_Function aboutToAppear;
    struct Opt_Function aboutToDisappear;
    struct Opt_ContextMenuAnimationOptions previewAnimationOptions;
    struct Opt_ResourceColor backgroundColor;
    Opt_BlurStyle backgroundBlurStyle;
    struct Opt_TransitionEffect transition;
    Opt_Boolean enableHoverMode;
} Ark_ContextMenuOptions;
typedef struct Opt_ContextMenuOptions {
    enum Ark_Tag tag;
    Ark_ContextMenuOptions value;
} Opt_ContextMenuOptions;
typedef struct Ark_CustomPopupOptions {
    struct Ark_CustomBuilder builder;
    Opt_Placement placement;
    struct Opt_Union_Color_String_Resource_Number maskColor;
    struct Opt_Union_Color_String_Resource_Number popupColor;
    Opt_Boolean enableArrow;
    Opt_Boolean autoCancel;
    struct Opt_Function onStateChange;
    Opt_Length arrowOffset;
    Opt_Boolean showInSubWindow;
    struct Opt_Union_Boolean_Literal_ResourceColor_color mask;
    Opt_Length targetSpace;
    struct Opt_Position offset;
    Opt_Length width;
    Opt_ArrowPointPosition arrowPointPosition;
    Opt_Length arrowWidth;
    Opt_Length arrowHeight;
    Opt_Length radius;
    struct Opt_Union_ShadowOptions_ShadowStyle shadow;
    Opt_BlurStyle backgroundBlurStyle;
    Opt_Boolean focusable;
    struct Opt_TransitionEffect transition;
    struct Opt_Union_Boolean_Function onWillDismiss;
    Opt_Boolean enableHoverMode;
} Ark_CustomPopupOptions;
typedef struct Opt_CustomPopupOptions {
    enum Ark_Tag tag;
    Ark_CustomPopupOptions value;
} Opt_CustomPopupOptions;
typedef struct Ark_PopupOptions {
    Ark_String message;
    Opt_Boolean placementOnTop;
    Opt_Placement placement;
    struct Opt_Literal_String_value_Function_action primaryButton;
    struct Opt_Literal_String_value_Function_action secondaryButton;
    struct Opt_Function onStateChange;
    Opt_Length arrowOffset;
    Opt_Boolean showInSubWindow;
    struct Opt_Union_Boolean_Literal_ResourceColor_color mask;
    struct Opt_PopupMessageOptions messageOptions;
    Opt_Length targetSpace;
    Opt_Boolean enableArrow;
    struct Opt_Position offset;
    struct Opt_Union_Color_String_Resource_Number popupColor;
    Opt_Boolean autoCancel;
    Opt_Length width;
    Opt_ArrowPointPosition arrowPointPosition;
    Opt_Length arrowWidth;
    Opt_Length arrowHeight;
    Opt_Length radius;
    struct Opt_Union_ShadowOptions_ShadowStyle shadow;
    Opt_BlurStyle backgroundBlurStyle;
    struct Opt_TransitionEffect transition;
    struct Opt_Union_Boolean_Function onWillDismiss;
    Opt_Boolean enableHoverMode;
} Ark_PopupOptions;
typedef struct Opt_PopupOptions {
    enum Ark_Tag tag;
    Ark_PopupOptions value;
} Opt_PopupOptions;
typedef Ark_Int32 Ark_TransitionHierarchyStrategy;
typedef struct Opt_TransitionHierarchyStrategy {
    enum Ark_Tag tag;
    Ark_TransitionHierarchyStrategy value;
} Opt_TransitionHierarchyStrategy;
typedef Ark_Materialized Ark_ProgressMask;
typedef struct Opt_ProgressMask {
    enum Ark_Tag tag;
    Ark_ProgressMask value;
} Opt_ProgressMask;
typedef Ark_Int32 Ark_BlendMode;
typedef struct Opt_BlendMode {
    enum Ark_Tag tag;
    Ark_BlendMode value;
} Opt_BlendMode;
typedef struct Ark_OverlayOffset {
    Opt_Number x;
    Opt_Number y;
} Ark_OverlayOffset;
typedef struct Opt_OverlayOffset {
    enum Ark_Tag tag;
    Ark_OverlayOffset value;
} Opt_OverlayOffset;
typedef struct Union_Boolean_Number {
    Ark_Int32 selector;
    union {
        Ark_Boolean value0;
        Ark_Number value1;
    };
} Union_Boolean_Number;
typedef struct Opt_Union_Boolean_Number {
    enum Ark_Tag tag;
    Union_Boolean_Number value;
} Opt_Union_Boolean_Number;
typedef struct Union_DragPreviewMode_Array_DragPreviewMode {
    Ark_Int32 selector;
    union {
        Ark_DragPreviewMode value0;
        struct Array_DragPreviewMode value1;
    };
} Union_DragPreviewMode_Array_DragPreviewMode;
typedef struct Opt_Union_DragPreviewMode_Array_DragPreviewMode {
    enum Ark_Tag tag;
    Union_DragPreviewMode_Array_DragPreviewMode value;
} Opt_Union_DragPreviewMode_Array_DragPreviewMode;
typedef struct Ark_DragItemInfo {
    Opt_CustomObject pixelMap;
    struct Opt_CustomBuilder builder;
    Opt_String extraInfo;
} Ark_DragItemInfo;
typedef struct Opt_DragItemInfo {
    enum Ark_Tag tag;
    Ark_DragItemInfo value;
} Opt_DragItemInfo;
typedef struct Ark_ClickEffect {
    Ark_ClickEffectLevel level;
    Opt_Number scale;
} Ark_ClickEffect;
typedef struct Opt_ClickEffect {
    enum Ark_Tag tag;
    Ark_ClickEffect value;
} Opt_ClickEffect;
typedef struct Ark_Bias {
    Opt_Number horizontal;
    Opt_Number vertical;
} Ark_Bias;
typedef struct Opt_Bias {
    enum Ark_Tag tag;
    Ark_Bias value;
} Opt_Bias;
typedef struct Ark_LocalizedVerticalAlignParam {
    Ark_String anchor;
    Ark_VerticalAlign align;
} Ark_LocalizedVerticalAlignParam;
typedef struct Opt_LocalizedVerticalAlignParam {
    enum Ark_Tag tag;
    Ark_LocalizedVerticalAlignParam value;
} Opt_LocalizedVerticalAlignParam;
typedef struct Ark_LocalizedHorizontalAlignParam {
    Ark_String anchor;
    Ark_HorizontalAlign align;
} Ark_LocalizedHorizontalAlignParam;
typedef struct Opt_LocalizedHorizontalAlignParam {
    enum Ark_Tag tag;
    Ark_LocalizedHorizontalAlignParam value;
} Opt_LocalizedHorizontalAlignParam;
typedef struct Literal_String_anchor_VerticalAlign_align {
    Ark_String anchor;
    Ark_VerticalAlign align;
} Literal_String_anchor_VerticalAlign_align;
typedef struct Opt_Literal_String_anchor_VerticalAlign_align {
    enum Ark_Tag tag;
    Literal_String_anchor_VerticalAlign_align value;
} Opt_Literal_String_anchor_VerticalAlign_align;
typedef struct Literal_String_anchor_HorizontalAlign_align {
    Ark_String anchor;
    Ark_HorizontalAlign align;
} Literal_String_anchor_HorizontalAlign_align;
typedef struct Opt_Literal_String_anchor_HorizontalAlign_align {
    enum Ark_Tag tag;
    Literal_String_anchor_HorizontalAlign_align value;
} Opt_Literal_String_anchor_HorizontalAlign_align;
typedef struct Union_Number_Literal_Number_span_offset {
    Ark_Int32 selector;
    union {
        Ark_Number value0;
        struct Literal_Number_span_offset value1;
    };
} Union_Number_Literal_Number_span_offset;
typedef struct Opt_Union_Number_Literal_Number_span_offset {
    enum Ark_Tag tag;
    Union_Number_Literal_Number_span_offset value;
} Opt_Union_Number_Literal_Number_span_offset;
typedef struct Ark_LocalizedPosition {
    Opt_CustomObject start;
    Opt_CustomObject top;
} Ark_LocalizedPosition;
typedef struct Opt_LocalizedPosition {
    enum Ark_Tag tag;
    Ark_LocalizedPosition value;
} Opt_LocalizedPosition;
typedef Ark_Int32 Ark_SharedTransitionEffectType;
typedef struct Opt_SharedTransitionEffectType {
    enum Ark_Tag tag;
    Ark_SharedTransitionEffectType value;
} Opt_SharedTransitionEffectType;
typedef struct Ark_MotionPathOptions {
    Ark_String path;
    Opt_Number from;
    Opt_Number to;
    Opt_Boolean rotatable;
} Ark_MotionPathOptions;
typedef struct Opt_MotionPathOptions {
    enum Ark_Tag tag;
    Ark_MotionPathOptions value;
} Opt_MotionPathOptions;
typedef struct Union_Curve_String_ICurve {
    Ark_Int32 selector;
    union {
        Ark_Curve value0;
        Ark_String value1;
        Ark_ICurve value2;
    };
} Union_Curve_String_ICurve;
typedef struct Opt_Union_Curve_String_ICurve {
    enum Ark_Tag tag;
    Union_Curve_String_ICurve value;
} Opt_Union_Curve_String_ICurve;
typedef struct Ark_InvertOptions {
    Ark_Number low;
    Ark_Number high;
    Ark_Number threshold;
    Ark_Number thresholdRange;
} Ark_InvertOptions;
typedef struct Opt_InvertOptions {
    enum Ark_Tag tag;
    Ark_InvertOptions value;
} Opt_InvertOptions;
typedef struct Ark_MotionBlurAnchor {
    Ark_Number x;
    Ark_Number y;
} Ark_MotionBlurAnchor;
typedef struct Opt_MotionBlurAnchor {
    enum Ark_Tag tag;
    Ark_MotionBlurAnchor value;
} Opt_MotionBlurAnchor;
typedef struct Array_Tuple_Number_Number {
    struct Tuple_Number_Number* array;
    Ark_Int32 length;
} Array_Tuple_Number_Number;
typedef struct Opt_Array_Tuple_Number_Number {
    enum Ark_Tag tag;
    Array_Tuple_Number_Number value;
} Opt_Array_Tuple_Number_Number;
typedef struct Ark_GestureGroupInterface {
    void *handle;
} Ark_GestureGroupInterface;
typedef struct Opt_GestureGroupInterface {
    enum Ark_Tag tag;
    Ark_GestureGroupInterface value;
} Opt_GestureGroupInterface;
typedef struct Ark_RotationGestureInterface {
    void *handle;
} Ark_RotationGestureInterface;
typedef struct Opt_RotationGestureInterface {
    enum Ark_Tag tag;
    Ark_RotationGestureInterface value;
} Opt_RotationGestureInterface;
typedef struct Ark_SwipeGestureInterface {
    void *handle;
} Ark_SwipeGestureInterface;
typedef struct Opt_SwipeGestureInterface {
    enum Ark_Tag tag;
    Ark_SwipeGestureInterface value;
} Opt_SwipeGestureInterface;
typedef struct Ark_PinchGestureInterface {
    void *handle;
} Ark_PinchGestureInterface;
typedef struct Opt_PinchGestureInterface {
    enum Ark_Tag tag;
    Ark_PinchGestureInterface value;
} Opt_PinchGestureInterface;
typedef struct Ark_PanGestureInterface {
    void *handle;
} Ark_PanGestureInterface;
typedef struct Opt_PanGestureInterface {
    enum Ark_Tag tag;
    Ark_PanGestureInterface value;
} Opt_PanGestureInterface;
typedef struct Ark_LongPressGestureInterface {
    void *handle;
} Ark_LongPressGestureInterface;
typedef struct Opt_LongPressGestureInterface {
    enum Ark_Tag tag;
    Ark_LongPressGestureInterface value;
} Opt_LongPressGestureInterface;
typedef struct Ark_TapGestureInterface {
    void *handle;
} Ark_TapGestureInterface;
typedef struct Opt_TapGestureInterface {
    enum Ark_Tag tag;
    Ark_TapGestureInterface value;
} Opt_TapGestureInterface;
typedef struct Ark_TransitionOptions {
    Opt_TransitionType type;
    Opt_Number opacity;
    struct Opt_TranslateOptions translate;
    struct Opt_ScaleOptions scale;
    struct Opt_RotateOptions rotate;
} Ark_TransitionOptions;
typedef struct Opt_TransitionOptions {
    enum Ark_Tag tag;
    Ark_TransitionOptions value;
} Opt_TransitionOptions;
typedef struct Ark_ExpectedFrameRateRange {
    Ark_Number min;
    Ark_Number max;
    Ark_Number expected;
} Ark_ExpectedFrameRateRange;
typedef struct Opt_ExpectedFrameRateRange {
    enum Ark_Tag tag;
    Ark_ExpectedFrameRateRange value;
} Opt_ExpectedFrameRateRange;
typedef Ark_Int32 Ark_FinishCallbackType;
typedef struct Opt_FinishCallbackType {
    enum Ark_Tag tag;
    Ark_FinishCallbackType value;
} Opt_FinishCallbackType;
typedef Ark_Int32 Ark_PlayMode;
typedef struct Opt_PlayMode {
    enum Ark_Tag tag;
    Ark_PlayMode value;
} Opt_PlayMode;
typedef struct Union_Ark_EdgeOutlineStyles_OutlineStyle {
    Ark_Int32 selector;
    union {
        struct Ark_EdgeOutlineStyles value0;
        Ark_OutlineStyle value1;
    };
} Union_Ark_EdgeOutlineStyles_OutlineStyle;
typedef struct Opt_Union_EdgeOutlineStyles_OutlineStyle {
    enum Ark_Tag tag;
    Union_Ark_EdgeOutlineStyles_OutlineStyle value;
} Opt_Union_EdgeOutlineStyles_OutlineStyle;
typedef struct Union_Ark_OutlineRadiuses_Length {
    Ark_Int32 selector;
    union {
        struct Ark_OutlineRadiuses value0;
        Ark_Length value1;
    };
} Union_Ark_OutlineRadiuses_Length;
typedef struct Opt_Union_OutlineRadiuses_Length {
    enum Ark_Tag tag;
    Union_Ark_OutlineRadiuses_Length value;
} Opt_Union_OutlineRadiuses_Length;
typedef struct Union_Ark_EdgeColors_Ark_ResourceColor_LocalizedEdgeColors {
    Ark_Int32 selector;
    union {
        struct Ark_EdgeColors value0;
        struct Ark_ResourceColor value1;
        struct Ark_LocalizedEdgeColors value2;
    };
} Union_Ark_EdgeColors_Ark_ResourceColor_LocalizedEdgeColors;
typedef struct Opt_Union_EdgeColors_Ark_ResourceColor_LocalizedEdgeColors {
    enum Ark_Tag tag;
    Union_Ark_EdgeColors_Ark_ResourceColor_LocalizedEdgeColors value;
} Opt_Union_EdgeColors_Ark_ResourceColor_LocalizedEdgeColors;
typedef struct Union_Ark_EdgeOutlineWidths_Length {
    Ark_Int32 selector;
    union {
        struct Ark_EdgeOutlineWidths value0;
        Ark_Length value1;
    };
} Union_Ark_EdgeOutlineWidths_Length;
typedef struct Opt_Union_EdgeOutlineWidths_Length {
    enum Ark_Tag tag;
    Union_Ark_EdgeOutlineWidths_Length value;
} Opt_Union_EdgeOutlineWidths_Length;
typedef struct Union_String_Resource_LinearGradient {
    Ark_Int32 selector;
    union {
        Ark_String value0;
        struct Ark_Resource value1;
        struct Ark_LinearGradient value2;
    };
} Union_String_Resource_LinearGradient;
typedef struct Opt_Union_String_Resource_LinearGradient {
    enum Ark_Tag tag;
    Union_String_Resource_LinearGradient value;
} Opt_Union_String_Resource_LinearGradient;
typedef Ark_Int32 Ark_RepeatMode;
typedef struct Opt_RepeatMode {
    enum Ark_Tag tag;
    Ark_RepeatMode value;
} Opt_RepeatMode;
typedef struct Union_Ark_EdgeWidths_CustomObject_LocalizedEdgeWidths {
    Ark_Int32 selector;
    union {
        struct Ark_EdgeWidths value0;
        Ark_CustomObject value1;
        struct Ark_LocalizedEdgeWidths value2;
    };
} Union_Ark_EdgeWidths_CustomObject_LocalizedEdgeWidths;
typedef struct Opt_Union_EdgeWidths_CustomObject_LocalizedEdgeWidths {
    enum Ark_Tag tag;
    Union_Ark_EdgeWidths_CustomObject_LocalizedEdgeWidths value;
} Opt_Union_EdgeWidths_CustomObject_LocalizedEdgeWidths;
typedef struct Union_Ark_EdgeStyles_BorderStyle {
    Ark_Int32 selector;
    union {
        struct Ark_EdgeStyles value0;
        Ark_BorderStyle value1;
    };
} Union_Ark_EdgeStyles_BorderStyle;
typedef struct Opt_Union_EdgeStyles_BorderStyle {
    enum Ark_Tag tag;
    Union_Ark_EdgeStyles_BorderStyle value;
} Opt_Union_EdgeStyles_BorderStyle;
typedef struct Union_Ark_BorderRadiuses_Length_LocalizedBorderRadiuses {
    Ark_Int32 selector;
    union {
        struct Ark_BorderRadiuses value0;
        Ark_Length value1;
        struct Ark_LocalizedBorderRadiuses value2;
    };
} Union_Ark_BorderRadiuses_Length_LocalizedBorderRadiuses;
typedef struct Opt_Union_BorderRadiuses_Length_LocalizedBorderRadiuses {
    enum Ark_Tag tag;
    Union_Ark_BorderRadiuses_Length_LocalizedBorderRadiuses value;
} Opt_Union_BorderRadiuses_Length_LocalizedBorderRadiuses;
typedef struct Union_Ark_EdgeWidths_Length_LocalizedEdgeWidths {
    Ark_Int32 selector;
    union {
        struct Ark_EdgeWidths value0;
        Ark_Length value1;
        struct Ark_LocalizedEdgeWidths value2;
    };
} Union_Ark_EdgeWidths_Length_LocalizedEdgeWidths;
typedef struct Opt_Union_EdgeWidths_Length_LocalizedEdgeWidths {
    enum Ark_Tag tag;
    Union_Ark_EdgeWidths_Length_LocalizedEdgeWidths value;
} Opt_Union_EdgeWidths_Length_LocalizedEdgeWidths;
typedef struct Ark_BlurStyleOptions {
    Opt_ThemeColorMode colorMode;
    Opt_AdaptiveColor adaptiveColor;
    Opt_Number scale;
    struct Opt_BlurOptions blurOptions;
} Ark_BlurStyleOptions;
typedef struct Opt_BlurStyleOptions {
    enum Ark_Tag tag;
    Ark_BlurStyleOptions value;
} Opt_BlurStyleOptions;
typedef Ark_Int32 Ark_BlurType;
typedef struct Opt_BlurType {
    enum Ark_Tag tag;
    Ark_BlurType value;
} Opt_BlurType;
typedef Ark_Int32 Ark_BlurStyleActivePolicy;
typedef struct Opt_BlurStyleActivePolicy {
    enum Ark_Tag tag;
    Ark_BlurStyleActivePolicy value;
} Opt_BlurStyleActivePolicy;
typedef Ark_Int32 Ark_ImageSize;
typedef struct Opt_ImageSize {
    enum Ark_Tag tag;
    Ark_ImageSize value;
} Opt_ImageSize;
typedef Ark_Int32 Ark_PixelRoundCalcPolicy;
typedef struct Opt_PixelRoundCalcPolicy {
    enum Ark_Tag tag;
    Ark_PixelRoundCalcPolicy value;
} Opt_PixelRoundCalcPolicy;
typedef struct Ark_Rectangle {
    Opt_Length x;
    Opt_Length y;
    Opt_Length width;
    Opt_Length height;
} Ark_Rectangle;
typedef struct Opt_Rectangle {
    enum Ark_Tag tag;
    Ark_Rectangle value;
} Opt_Rectangle;
typedef struct Array_Rectangle {
    struct Ark_Rectangle* array;
    Ark_Int32 length;
} Array_Rectangle;
typedef struct Opt_Array_Rectangle {
    enum Ark_Tag tag;
    Array_Rectangle value;
} Opt_Array_Rectangle;
typedef Ark_Materialized Ark_DrawModifier;
typedef struct Opt_DrawModifier {
    enum Ark_Tag tag;
    Ark_DrawModifier value;
} Opt_DrawModifier;
typedef struct Ark_TerminationInfo {
    Ark_Number code;
    Opt_CustomObject want;
} Ark_TerminationInfo;
typedef struct Opt_TerminationInfo {
    enum Ark_Tag tag;
    Ark_TerminationInfo value;
} Opt_TerminationInfo;
typedef struct Ark_AdsBlockedDetails {
    Ark_String url;
    struct Array_String adsBlocked;
} Ark_AdsBlockedDetails;
typedef struct Opt_AdsBlockedDetails {
    enum Ark_Tag tag;
    Ark_AdsBlockedDetails value;
} Opt_AdsBlockedDetails;
typedef struct Ark_WebKeyboardCallbackInfo {
    Ark_WebKeyboardController controller;
    struct Ark_CustomObject attributes;
} Ark_WebKeyboardCallbackInfo;
typedef struct Opt_WebKeyboardCallbackInfo {
    enum Ark_Tag tag;
    Ark_WebKeyboardCallbackInfo value;
} Opt_WebKeyboardCallbackInfo;
typedef Ark_Int32 Ark_ViewportFit;
typedef struct Opt_ViewportFit {
    enum Ark_Tag tag;
    Ark_ViewportFit value;
} Opt_ViewportFit;
typedef struct Ark_RenderProcessNotRespondingData {
    Ark_String jsStack;
    Ark_Number pid;
    Ark_RenderProcessNotRespondingReason reason;
} Ark_RenderProcessNotRespondingData;
typedef struct Opt_RenderProcessNotRespondingData {
    enum Ark_Tag tag;
    Ark_RenderProcessNotRespondingData value;
} Opt_RenderProcessNotRespondingData;
typedef struct Ark_NativeEmbedTouchInfo {
    Opt_String embedId;
    struct Opt_TouchEvent touchEvent;
    Opt_EventResult result;
} Ark_NativeEmbedTouchInfo;
typedef struct Opt_NativeEmbedTouchInfo {
    enum Ark_Tag tag;
    Ark_NativeEmbedTouchInfo value;
} Opt_NativeEmbedTouchInfo;
typedef struct Ark_NativeEmbedVisibilityInfo {
    Ark_Boolean visibility;
    Ark_String embedId;
} Ark_NativeEmbedVisibilityInfo;
typedef struct Opt_NativeEmbedVisibilityInfo {
    enum Ark_Tag tag;
    Ark_NativeEmbedVisibilityInfo value;
} Opt_NativeEmbedVisibilityInfo;
typedef struct Ark_NativeEmbedDataInfo {
    Opt_NativeEmbedStatus status;
    Opt_String surfaceId;
    Opt_String embedId;
    struct Opt_NativeEmbedInfo info;
} Ark_NativeEmbedDataInfo;
typedef struct Opt_NativeEmbedDataInfo {
    enum Ark_Tag tag;
    Ark_NativeEmbedDataInfo value;
} Opt_NativeEmbedDataInfo;
typedef struct Ark_IntelligentTrackingPreventionDetails {
    Ark_String host;
    Ark_String trackerHost;
} Ark_IntelligentTrackingPreventionDetails;
typedef struct Opt_IntelligentTrackingPreventionDetails {
    enum Ark_Tag tag;
    Ark_IntelligentTrackingPreventionDetails value;
} Opt_IntelligentTrackingPreventionDetails;
typedef struct Ark_LoadCommittedDetails {
    Ark_Boolean isMainFrame;
    Ark_Boolean isSameDocument;
    Ark_Boolean didReplaceEntry;
    Ark_WebNavigationType navigationType;
    Ark_String url;
} Ark_LoadCommittedDetails;
typedef struct Opt_LoadCommittedDetails {
    enum Ark_Tag tag;
    Ark_LoadCommittedDetails value;
} Opt_LoadCommittedDetails;
typedef Ark_Int32 Ark_ThreatType;
typedef struct Opt_ThreatType {
    enum Ark_Tag tag;
    Ark_ThreatType value;
} Opt_ThreatType;
typedef struct Ark_OnOverScrollEvent {
    Ark_Number xOffset;
    Ark_Number yOffset;
} Ark_OnOverScrollEvent;
typedef struct Opt_OnOverScrollEvent {
    enum Ark_Tag tag;
    Ark_OnOverScrollEvent value;
} Opt_OnOverScrollEvent;
typedef struct Ark_OnLoadInterceptEvent {
    Ark_WebResourceRequest data;
} Ark_OnLoadInterceptEvent;
typedef struct Opt_OnLoadInterceptEvent {
    enum Ark_Tag tag;
    Ark_OnLoadInterceptEvent value;
} Opt_OnLoadInterceptEvent;
typedef struct Ark_LargestContentfulPaint {
    Opt_Number navigationStartTime;
    Opt_Number largestImagePaintTime;
    Opt_Number largestTextPaintTime;
    Opt_Number imageBPP;
    Opt_Number largestImageLoadStartTime;
    Opt_Number largestImageLoadEndTime;
} Ark_LargestContentfulPaint;
typedef struct Opt_LargestContentfulPaint {
    enum Ark_Tag tag;
    Ark_LargestContentfulPaint value;
} Opt_LargestContentfulPaint;
typedef struct Ark_FirstMeaningfulPaint {
    Opt_Number navigationStartTime;
    Opt_Number firstMeaningfulPaintTime;
} Ark_FirstMeaningfulPaint;
typedef struct Opt_FirstMeaningfulPaint {
    enum Ark_Tag tag;
    Ark_FirstMeaningfulPaint value;
} Opt_FirstMeaningfulPaint;
typedef struct Ark_OnFirstContentfulPaintEvent {
    Ark_Number navigationStartTick;
    Ark_Number firstContentfulPaintMs;
} Ark_OnFirstContentfulPaintEvent;
typedef struct Opt_OnFirstContentfulPaintEvent {
    enum Ark_Tag tag;
    Ark_OnFirstContentfulPaintEvent value;
} Opt_OnFirstContentfulPaintEvent;
typedef struct Ark_OnAudioStateChangedEvent {
    Ark_Boolean playing;
} Ark_OnAudioStateChangedEvent;
typedef struct Opt_OnAudioStateChangedEvent {
    enum Ark_Tag tag;
    Ark_OnAudioStateChangedEvent value;
} Opt_OnAudioStateChangedEvent;
typedef struct Ark_OnDataResubmittedEvent {
    Ark_DataResubmissionHandler handler;
} Ark_OnDataResubmittedEvent;
typedef struct Opt_OnDataResubmittedEvent {
    enum Ark_Tag tag;
    Ark_OnDataResubmittedEvent value;
} Opt_OnDataResubmittedEvent;
typedef struct Ark_OnPageVisibleEvent {
    Ark_String url;
} Ark_OnPageVisibleEvent;
typedef struct Opt_OnPageVisibleEvent {
    enum Ark_Tag tag;
    Ark_OnPageVisibleEvent value;
} Opt_OnPageVisibleEvent;
typedef struct Ark_OnFaviconReceivedEvent {
    Ark_CustomObject favicon;
} Ark_OnFaviconReceivedEvent;
typedef struct Opt_OnFaviconReceivedEvent {
    enum Ark_Tag tag;
    Ark_OnFaviconReceivedEvent value;
} Opt_OnFaviconReceivedEvent;
typedef struct Ark_OnTouchIconUrlReceivedEvent {
    Ark_String url;
    Ark_Boolean precomposed;
} Ark_OnTouchIconUrlReceivedEvent;
typedef struct Opt_OnTouchIconUrlReceivedEvent {
    enum Ark_Tag tag;
    Ark_OnTouchIconUrlReceivedEvent value;
} Opt_OnTouchIconUrlReceivedEvent;
typedef struct Ark_OnWindowNewEvent {
    Ark_Boolean isAlert;
    Ark_Boolean isUserTrigger;
    Ark_String targetUrl;
    Ark_ControllerHandler handler;
} Ark_OnWindowNewEvent;
typedef struct Opt_OnWindowNewEvent {
    enum Ark_Tag tag;
    Ark_OnWindowNewEvent value;
} Opt_OnWindowNewEvent;
typedef struct Ark_OnClientAuthenticationEvent {
    Ark_ClientAuthenticationHandler handler;
    Ark_String host;
    Ark_Number port;
    struct Array_String keyTypes;
    struct Array_String issuers;
} Ark_OnClientAuthenticationEvent;
typedef struct Opt_OnClientAuthenticationEvent {
    enum Ark_Tag tag;
    Ark_OnClientAuthenticationEvent value;
} Opt_OnClientAuthenticationEvent;
typedef struct Ark_SslErrorEvent {
    Ark_SslErrorHandler handler;
    Ark_SslError error;
    Ark_String url;
    Ark_String originalUrl;
    Ark_String referrer;
    Ark_Boolean isFatalError;
    Ark_Boolean isMainFrame;
} Ark_SslErrorEvent;
typedef struct Opt_SslErrorEvent {
    enum Ark_Tag tag;
    Ark_SslErrorEvent value;
} Opt_SslErrorEvent;
typedef struct Ark_OnSslErrorEventReceiveEvent {
    Ark_SslErrorHandler handler;
    Ark_SslError error;
} Ark_OnSslErrorEventReceiveEvent;
typedef struct Opt_OnSslErrorEventReceiveEvent {
    enum Ark_Tag tag;
    Ark_OnSslErrorEventReceiveEvent value;
} Opt_OnSslErrorEventReceiveEvent;
typedef struct Ark_OnScrollEvent {
    Ark_Number xOffset;
    Ark_Number yOffset;
} Ark_OnScrollEvent;
typedef struct Opt_OnScrollEvent {
    enum Ark_Tag tag;
    Ark_OnScrollEvent value;
} Opt_OnScrollEvent;
typedef struct Ark_OnSearchResultReceiveEvent {
    Ark_Number activeMatchOrdinal;
    Ark_Number numberOfMatches;
    Ark_Boolean isDoneCounting;
} Ark_OnSearchResultReceiveEvent;
typedef struct Opt_OnSearchResultReceiveEvent {
    enum Ark_Tag tag;
    Ark_OnSearchResultReceiveEvent value;
} Opt_OnSearchResultReceiveEvent;
typedef struct Ark_OnContextMenuShowEvent {
    Ark_WebContextMenuParam param;
    Ark_WebContextMenuResult result;
} Ark_OnContextMenuShowEvent;
typedef struct Opt_OnContextMenuShowEvent {
    enum Ark_Tag tag;
    Ark_OnContextMenuShowEvent value;
} Opt_OnContextMenuShowEvent;
typedef struct Ark_OnScreenCaptureRequestEvent {
    Ark_ScreenCaptureHandler handler;
} Ark_OnScreenCaptureRequestEvent;
typedef struct Opt_OnScreenCaptureRequestEvent {
    enum Ark_Tag tag;
    Ark_OnScreenCaptureRequestEvent value;
} Opt_OnScreenCaptureRequestEvent;
typedef struct Ark_OnPermissionRequestEvent {
    Ark_PermissionRequest request;
} Ark_OnPermissionRequestEvent;
typedef struct Opt_OnPermissionRequestEvent {
    enum Ark_Tag tag;
    Ark_OnPermissionRequestEvent value;
} Opt_OnPermissionRequestEvent;
typedef struct Ark_OnInterceptRequestEvent {
    Ark_WebResourceRequest request;
} Ark_OnInterceptRequestEvent;
typedef struct Opt_OnInterceptRequestEvent {
    enum Ark_Tag tag;
    Ark_OnInterceptRequestEvent value;
} Opt_OnInterceptRequestEvent;
typedef struct Ark_OnHttpAuthRequestEvent {
    Ark_HttpAuthHandler handler;
    Ark_String host;
    Ark_String realm;
} Ark_OnHttpAuthRequestEvent;
typedef struct Opt_OnHttpAuthRequestEvent {
    enum Ark_Tag tag;
    Ark_OnHttpAuthRequestEvent value;
} Opt_OnHttpAuthRequestEvent;
typedef struct Ark_OnScaleChangeEvent {
    Ark_Number oldScale;
    Ark_Number newScale;
} Ark_OnScaleChangeEvent;
typedef struct Opt_OnScaleChangeEvent {
    enum Ark_Tag tag;
    Ark_OnScaleChangeEvent value;
} Opt_OnScaleChangeEvent;
typedef struct Ark_FullScreenEnterEvent {
    Ark_FullScreenExitHandler handler;
    Opt_Number videoWidth;
    Opt_Number videoHeight;
} Ark_FullScreenEnterEvent;
typedef struct Opt_FullScreenEnterEvent {
    enum Ark_Tag tag;
    Ark_FullScreenEnterEvent value;
} Opt_FullScreenEnterEvent;
typedef struct Ark_OnResourceLoadEvent {
    Ark_String url;
} Ark_OnResourceLoadEvent;
typedef struct Opt_OnResourceLoadEvent {
    enum Ark_Tag tag;
    Ark_OnResourceLoadEvent value;
} Opt_OnResourceLoadEvent;
typedef struct Literal_Function_callback_CustomObject_fileSelector {
    Ark_Function callback;
    Ark_CustomObject fileSelector;
} Literal_Function_callback_CustomObject_fileSelector;
typedef struct Opt_Literal_Function_callback_CustomObject_fileSelector {
    enum Ark_Tag tag;
    Literal_Function_callback_CustomObject_fileSelector value;
} Opt_Literal_Function_callback_CustomObject_fileSelector;
typedef struct Literal_CustomObject_detail {
    Ark_CustomObject detail;
} Literal_CustomObject_detail;
typedef struct Opt_Literal_CustomObject_detail {
    enum Ark_Tag tag;
    Literal_CustomObject_detail value;
} Opt_Literal_CustomObject_detail;
typedef struct Ark_OnShowFileSelectorEvent {
    Ark_FileSelectorResult result;
    Ark_FileSelectorParam fileSelector;
} Ark_OnShowFileSelectorEvent;
typedef struct Opt_OnShowFileSelectorEvent {
    enum Ark_Tag tag;
    Ark_OnShowFileSelectorEvent value;
} Opt_OnShowFileSelectorEvent;
typedef struct Ark_OnRenderExitedEvent {
    Ark_RenderExitReason renderExitReason;
} Ark_OnRenderExitedEvent;
typedef struct Opt_OnRenderExitedEvent {
    enum Ark_Tag tag;
    Ark_OnRenderExitedEvent value;
} Opt_OnRenderExitedEvent;
typedef struct Literal_Function_handler_CustomObject_error {
    Ark_Function handler;
    Ark_CustomObject error;
} Literal_Function_handler_CustomObject_error;
typedef struct Opt_Literal_Function_handler_CustomObject_error {
    enum Ark_Tag tag;
    Literal_Function_handler_CustomObject_error value;
} Opt_Literal_Function_handler_CustomObject_error;
typedef struct Literal_Union_String_WebResourceRequest_data {
    struct Union_String_WebResourceRequest data;
} Literal_Union_String_WebResourceRequest_data;
typedef struct Opt_Literal_Union_String_WebResourceRequest_data {
    enum Ark_Tag tag;
    Literal_Union_String_WebResourceRequest_data value;
} Opt_Literal_Union_String_WebResourceRequest_data;
typedef struct Ark_OnRefreshAccessedHistoryEvent {
    Ark_String url;
    Ark_Boolean isRefreshed;
} Ark_OnRefreshAccessedHistoryEvent;
typedef struct Opt_OnRefreshAccessedHistoryEvent {
    enum Ark_Tag tag;
    Ark_OnRefreshAccessedHistoryEvent value;
} Opt_OnRefreshAccessedHistoryEvent;
typedef struct Ark_OnDownloadStartEvent {
    Ark_String url;
    Ark_String userAgent;
    Ark_String contentDisposition;
    Ark_String mimetype;
    Ark_Number contentLength;
} Ark_OnDownloadStartEvent;
typedef struct Opt_OnDownloadStartEvent {
    enum Ark_Tag tag;
    Ark_OnDownloadStartEvent value;
} Opt_OnDownloadStartEvent;
typedef struct Ark_OnHttpErrorReceiveEvent {
    Ark_WebResourceRequest request;
    Ark_WebResourceResponse response;
} Ark_OnHttpErrorReceiveEvent;
typedef struct Opt_OnHttpErrorReceiveEvent {
    enum Ark_Tag tag;
    Ark_OnHttpErrorReceiveEvent value;
} Opt_OnHttpErrorReceiveEvent;
typedef struct Ark_OnErrorReceiveEvent {
    Ark_WebResourceRequest request;
    Ark_WebResourceError error;
} Ark_OnErrorReceiveEvent;
typedef struct Opt_OnErrorReceiveEvent {
    enum Ark_Tag tag;
    Ark_OnErrorReceiveEvent value;
} Opt_OnErrorReceiveEvent;
typedef struct Ark_OnConsoleEvent {
    Ark_ConsoleMessage message;
} Ark_OnConsoleEvent;
typedef struct Opt_OnConsoleEvent {
    enum Ark_Tag tag;
    Ark_OnConsoleEvent value;
} Opt_OnConsoleEvent;
typedef struct Ark_OnPromptEvent {
    Ark_String url;
    Ark_String message;
    Ark_String value;
    Ark_JsResult result;
} Ark_OnPromptEvent;
typedef struct Opt_OnPromptEvent {
    enum Ark_Tag tag;
    Ark_OnPromptEvent value;
} Opt_OnPromptEvent;
typedef struct Ark_OnConfirmEvent {
    Ark_String url;
    Ark_String message;
    Ark_JsResult result;
} Ark_OnConfirmEvent;
typedef struct Opt_OnConfirmEvent {
    enum Ark_Tag tag;
    Ark_OnConfirmEvent value;
} Opt_OnConfirmEvent;
typedef struct Ark_OnBeforeUnloadEvent {
    Ark_String url;
    Ark_String message;
    Ark_JsResult result;
} Ark_OnBeforeUnloadEvent;
typedef struct Opt_OnBeforeUnloadEvent {
    enum Ark_Tag tag;
    Ark_OnBeforeUnloadEvent value;
} Opt_OnBeforeUnloadEvent;
typedef struct Ark_OnAlertEvent {
    Ark_String url;
    Ark_String message;
    Ark_JsResult result;
} Ark_OnAlertEvent;
typedef struct Opt_OnAlertEvent {
    enum Ark_Tag tag;
    Ark_OnAlertEvent value;
} Opt_OnAlertEvent;
typedef struct Ark_OnGeolocationShowEvent {
    Ark_String origin;
    Ark_JsGeolocation geolocation;
} Ark_OnGeolocationShowEvent;
typedef struct Opt_OnGeolocationShowEvent {
    enum Ark_Tag tag;
    Ark_OnGeolocationShowEvent value;
} Opt_OnGeolocationShowEvent;
typedef struct Ark_OnTitleReceiveEvent {
    Ark_String title;
} Ark_OnTitleReceiveEvent;
typedef struct Opt_OnTitleReceiveEvent {
    enum Ark_Tag tag;
    Ark_OnTitleReceiveEvent value;
} Opt_OnTitleReceiveEvent;
typedef struct Ark_OnProgressChangeEvent {
    Ark_Number newProgress;
} Ark_OnProgressChangeEvent;
typedef struct Opt_OnProgressChangeEvent {
    enum Ark_Tag tag;
    Ark_OnProgressChangeEvent value;
} Opt_OnProgressChangeEvent;
typedef struct Ark_OnPageBeginEvent {
    Ark_String url;
} Ark_OnPageBeginEvent;
typedef struct Opt_OnPageBeginEvent {
    enum Ark_Tag tag;
    Ark_OnPageBeginEvent value;
} Opt_OnPageBeginEvent;
typedef struct Ark_OnPageEndEvent {
    Ark_String url;
} Ark_OnPageEndEvent;
typedef struct Opt_OnPageEndEvent {
    enum Ark_Tag tag;
    Ark_OnPageEndEvent value;
} Opt_OnPageEndEvent;
typedef struct Literal_Number_time {
    Ark_Number time;
} Literal_Number_time;
typedef struct Opt_Literal_Number_time {
    enum Ark_Tag tag;
    Literal_Number_time value;
} Opt_Literal_Number_time;
typedef struct Literal_Number_duration {
    Ark_Number duration;
} Literal_Number_duration;
typedef struct Opt_Literal_Number_duration {
    enum Ark_Tag tag;
    Literal_Number_duration value;
} Opt_Literal_Number_duration;
typedef struct Literal_Boolean_fullscreen {
    Ark_Boolean fullscreen;
} Literal_Boolean_fullscreen;
typedef struct Opt_Literal_Boolean_fullscreen {
    enum Ark_Tag tag;
    Literal_Boolean_fullscreen value;
} Opt_Literal_Boolean_fullscreen;
typedef struct Ark_TimePickerResult {
    Ark_Number hour;
    Ark_Number minute;
    Ark_Number second;
} Ark_TimePickerResult;
typedef struct Opt_TimePickerResult {
    enum Ark_Tag tag;
    Ark_TimePickerResult value;
} Opt_TimePickerResult;
typedef struct Ark_TabsAnimationEvent {
    Ark_Number currentOffset;
    Ark_Number targetOffset;
    Ark_Number velocity;
} Ark_TabsAnimationEvent;
typedef struct Opt_TabsAnimationEvent {
    enum Ark_Tag tag;
    Ark_TabsAnimationEvent value;
} Opt_TabsAnimationEvent;
typedef struct Ark_SwiperAnimationEvent {
    Ark_Number currentOffset;
    Ark_Number targetOffset;
    Ark_Number velocity;
} Ark_SwiperAnimationEvent;
typedef struct Opt_SwiperAnimationEvent {
    enum Ark_Tag tag;
    Ark_SwiperAnimationEvent value;
} Opt_SwiperAnimationEvent;
typedef Ark_Int32 Ark_SliderChangeMode;
typedef struct Opt_SliderChangeMode {
    enum Ark_Tag tag;
    Ark_SliderChangeMode value;
} Opt_SliderChangeMode;
typedef struct Ark_DeleteValue {
    Ark_Number deleteOffset;
    Ark_TextDeleteDirection direction;
    Ark_String deleteValue;
} Ark_DeleteValue;
typedef struct Opt_DeleteValue {
    enum Ark_Tag tag;
    Ark_DeleteValue value;
} Opt_DeleteValue;
typedef struct Ark_InsertValue {
    Ark_Number insertOffset;
    Ark_String insertValue;
} Ark_InsertValue;
typedef struct Opt_InsertValue {
    enum Ark_Tag tag;
    Ark_InsertValue value;
} Opt_InsertValue;
typedef struct Ark_PreviewText {
    Ark_Number offset;
    Ark_String value;
} Ark_PreviewText;
typedef struct Opt_PreviewText {
    enum Ark_Tag tag;
    Ark_PreviewText value;
} Opt_PreviewText;
typedef Ark_Int32 Ark_SaveButtonOnClickResult;
typedef struct Opt_SaveButtonOnClickResult {
    enum Ark_Tag tag;
    Ark_SaveButtonOnClickResult value;
} Opt_SaveButtonOnClickResult;
typedef struct Ark_CopyEvent {
    struct Opt_Function preventDefault;
} Ark_CopyEvent;
typedef struct Opt_CopyEvent {
    enum Ark_Tag tag;
    Ark_CopyEvent value;
} Opt_CopyEvent;
typedef struct Ark_CutEvent {
    struct Opt_Function preventDefault;
} Ark_CutEvent;
typedef struct Opt_CutEvent {
    enum Ark_Tag tag;
    Ark_CutEvent value;
} Opt_CutEvent;
typedef struct Ark_RichEditorChangeValue {
    struct Ark_TextRange rangeBefore;
    struct Array_RichEditorTextSpanResult replacedSpans;
    struct Array_RichEditorImageSpanResult replacedImageSpans;
    struct Array_RichEditorTextSpanResult replacedSymbolSpans;
} Ark_RichEditorChangeValue;
typedef struct Opt_RichEditorChangeValue {
    enum Ark_Tag tag;
    Ark_RichEditorChangeValue value;
} Opt_RichEditorChangeValue;
typedef struct Ark_SubmitEvent {
    Ark_String text;
} Ark_SubmitEvent;
typedef struct Opt_SubmitEvent {
    enum Ark_Tag tag;
    Ark_SubmitEvent value;
} Opt_SubmitEvent;
typedef struct Ark_PasteEvent {
    struct Opt_Function preventDefault;
} Ark_PasteEvent;
typedef struct Opt_PasteEvent {
    enum Ark_Tag tag;
    Ark_PasteEvent value;
} Opt_PasteEvent;
typedef struct Union_RichEditorTextSpanResult_RichEditorImageSpanResult {
    Ark_Int32 selector;
    union {
        struct Ark_RichEditorTextSpanResult value0;
        struct Ark_RichEditorImageSpanResult value1;
    };
} Union_RichEditorTextSpanResult_RichEditorImageSpanResult;
typedef struct Opt_Union_RichEditorTextSpanResult_RichEditorImageSpanResult {
    enum Ark_Tag tag;
    Union_RichEditorTextSpanResult_RichEditorImageSpanResult value;
} Opt_Union_RichEditorTextSpanResult_RichEditorImageSpanResult;
typedef struct Ark_RichEditorDeleteValue {
    Ark_Number offset;
    Ark_RichEditorDeleteDirection direction;
    Ark_Number length;
    struct Array_Union_RichEditorTextSpanResult_RichEditorImageSpanResult richEditorDeleteSpans;
} Ark_RichEditorDeleteValue;
typedef struct Opt_RichEditorDeleteValue {
    enum Ark_Tag tag;
    Ark_RichEditorDeleteValue value;
} Opt_RichEditorDeleteValue;
typedef struct Ark_RichEditorInsertValue {
    Ark_Number insertOffset;
    Ark_String insertValue;
    Opt_String previewText;
} Ark_RichEditorInsertValue;
typedef struct Opt_RichEditorInsertValue {
    enum Ark_Tag tag;
    Ark_RichEditorInsertValue value;
} Opt_RichEditorInsertValue;
typedef struct Ark_RichEditorSelection {
    struct Tuple_Number_Number selection;
    struct Array_Union_RichEditorTextSpanResult_RichEditorImageSpanResult spans;
} Ark_RichEditorSelection;
typedef struct Opt_RichEditorSelection {
    enum Ark_Tag tag;
    Ark_RichEditorSelection value;
} Opt_RichEditorSelection;
typedef Ark_Int32 Ark_RefreshStatus;
typedef struct Opt_RefreshStatus {
    enum Ark_Tag tag;
    Ark_RefreshStatus value;
} Opt_RefreshStatus;
typedef struct Literal_Number_errcode_String_msg {
    Ark_Number errcode;
    Ark_String msg;
} Literal_Number_errcode_String_msg;
typedef struct Opt_Literal_Number_errcode_String_msg {
    enum Ark_Tag tag;
    Literal_Number_errcode_String_msg value;
} Opt_Literal_Number_errcode_String_msg;
typedef Ark_Int32 Ark_PasteButtonOnClickResult;
typedef struct Opt_PasteButtonOnClickResult {
    enum Ark_Tag tag;
    Ark_PasteButtonOnClickResult value;
} Opt_PasteButtonOnClickResult;
typedef Ark_Int32 Ark_NavigationOperation;
typedef struct Opt_NavigationOperation {
    enum Ark_Tag tag;
    Ark_NavigationOperation value;
} Opt_NavigationOperation;
typedef struct Ark_NavContentInfo {
    Opt_String name;
    Ark_Number index;
    Opt_NavDestinationMode mode;
    struct Opt_Object param;
    Opt_String navDestinationId;
} Ark_NavContentInfo;
typedef struct Opt_NavContentInfo {
    enum Ark_Tag tag;
    Ark_NavContentInfo value;
} Opt_NavContentInfo;
typedef Ark_Int32 Ark_LocationButtonOnClickResult;
typedef struct Opt_LocationButtonOnClickResult {
    enum Ark_Tag tag;
    Ark_LocationButtonOnClickResult value;
} Opt_LocationButtonOnClickResult;
typedef struct Ark_VisibleListContentInfo {
    Ark_Number index;
    Opt_ListItemGroupArea itemGroupArea;
    Opt_Number itemIndexInGroup;
} Ark_VisibleListContentInfo;
typedef struct Opt_VisibleListContentInfo {
    enum Ark_Tag tag;
    Ark_VisibleListContentInfo value;
} Opt_VisibleListContentInfo;
typedef struct Ark_ImageLoadResult {
    Ark_Number width;
    Ark_Number height;
    Ark_Number componentWidth;
    Ark_Number componentHeight;
    Ark_Number loadingStatus;
    Ark_Number contentWidth;
    Ark_Number contentHeight;
    Ark_Number contentOffsetX;
    Ark_Number contentOffsetY;
} Ark_ImageLoadResult;
typedef struct Opt_ImageLoadResult {
    enum Ark_Tag tag;
    Ark_ImageLoadResult value;
} Opt_ImageLoadResult;
typedef struct Ark_ImageError {
    Ark_Number componentWidth;
    Ark_Number componentHeight;
    Ark_String message;
} Ark_ImageError;
typedef struct Opt_ImageError {
    enum Ark_Tag tag;
    Ark_ImageError value;
} Opt_ImageError;
typedef struct Literal_Number_width_height_componentWidth_componentHeight_loadingStatus_contentWidth_contentHeight_contentOffsetX_contentOffsetY {
    Ark_Number width;
    Ark_Number height;
    Ark_Number componentWidth;
    Ark_Number componentHeight;
    Ark_Number loadingStatus;
    Ark_Number contentWidth;
    Ark_Number contentHeight;
    Ark_Number contentOffsetX;
    Ark_Number contentOffsetY;
} Literal_Number_width_height_componentWidth_componentHeight_loadingStatus_contentWidth_contentHeight_contentOffsetX_contentOffsetY;
typedef struct Opt_Literal_Number_width_height_componentWidth_componentHeight_loadingStatus_contentWidth_contentHeight_contentOffsetX_contentOffsetY {
    enum Ark_Tag tag;
    Literal_Number_width_height_componentWidth_componentHeight_loadingStatus_contentWidth_contentHeight_contentOffsetX_contentOffsetY value;
} Opt_Literal_Number_width_height_componentWidth_componentHeight_loadingStatus_contentWidth_contentHeight_contentOffsetX_contentOffsetY;
typedef struct Ark_ItemDragInfo {
    Ark_Number x;
    Ark_Number y;
} Ark_ItemDragInfo;
typedef struct Opt_ItemDragInfo {
    enum Ark_Tag tag;
    Ark_ItemDragInfo value;
} Opt_ItemDragInfo;
typedef struct Ark_FormCallbackInfo {
    Ark_Number id;
    Ark_String idString;
} Ark_FormCallbackInfo;
typedef struct Opt_FormCallbackInfo {
    enum Ark_Tag tag;
    Ark_FormCallbackInfo value;
} Opt_FormCallbackInfo;
typedef struct Ark_HoverEventParam {
    Ark_FoldStatus foldStatus;
    Ark_Boolean isHoverMode;
    Ark_AppRotation appRotation;
    Ark_CustomObject windowStatusType;
} Ark_HoverEventParam;
typedef struct Opt_HoverEventParam {
    enum Ark_Tag tag;
    Ark_HoverEventParam value;
} Opt_HoverEventParam;
typedef struct Ark_OnFoldStatusChangeInfo {
    Ark_FoldStatus foldStatus;
} Ark_OnFoldStatusChangeInfo;
typedef struct Opt_OnFoldStatusChangeInfo {
    enum Ark_Tag tag;
    Ark_OnFoldStatusChangeInfo value;
} Opt_OnFoldStatusChangeInfo;
typedef struct Ark_DatePickerResult {
    Opt_Number year;
    Opt_Number month;
    Opt_Number day;
} Ark_DatePickerResult;
typedef struct Opt_DatePickerResult {
    enum Ark_Tag tag;
    Ark_DatePickerResult value;
} Opt_DatePickerResult;
typedef Ark_Int32 Ark_ScrollState;
typedef struct Opt_ScrollState {
    enum Ark_Tag tag;
    Ark_ScrollState value;
} Opt_ScrollState;
typedef Ark_Materialized Ark_GestureRecognizer;
typedef struct Array_GestureRecognizer {
    Ark_GestureRecognizer* array;
    Ark_Int32 length;
} Array_GestureRecognizer;
typedef struct Opt_Array_GestureRecognizer {
    enum Ark_Tag tag;
    Array_GestureRecognizer value;
} Opt_Array_GestureRecognizer;
typedef Ark_Materialized Ark_GestureRecognizer;
typedef struct Opt_GestureRecognizer {
    enum Ark_Tag tag;
    Ark_GestureRecognizer value;
} Opt_GestureRecognizer;
typedef struct Ark_FingerInfo {
    Ark_Number id;
    Ark_Number globalX;
    Ark_Number globalY;
    Ark_Number localX;
    Ark_Number localY;
    Ark_Number displayX;
    Ark_Number displayY;
} Ark_FingerInfo;
typedef struct Opt_FingerInfo {
    enum Ark_Tag tag;
    Ark_FingerInfo value;
} Opt_FingerInfo;
typedef struct Ark_BaseGestureEvent {
    struct Ark_EventTarget target;
    Ark_Number timestamp;
    Ark_SourceType source;
    Opt_Number axisHorizontal;
    Opt_Number axisVertical;
    Ark_Number pressure;
    Ark_Number tiltX;
    Ark_Number tiltY;
    Ark_SourceTool sourceTool;
    Opt_Number deviceId;
    struct Array_FingerInfo fingerList;
} Ark_BaseGestureEvent;
typedef struct Opt_BaseGestureEvent {
    enum Ark_Tag tag;
    Ark_BaseGestureEvent value;
} Opt_BaseGestureEvent;
typedef struct Ark_GestureInfo {
    Opt_String tag;
    Ark_GestureControl_GestureType type;
    Ark_Boolean isSystemGesture;
} Ark_GestureInfo;
typedef struct Opt_GestureInfo {
    enum Ark_Tag tag;
    Ark_GestureInfo value;
} Opt_GestureInfo;
typedef Ark_Int32 Ark_PreDragStatus;
typedef struct Opt_PreDragStatus {
    enum Ark_Tag tag;
    Ark_PreDragStatus value;
} Opt_PreDragStatus;
typedef struct Ark_DragEvent {
    Ark_DragBehavior dragBehavior;
    Ark_Boolean useCustomDropAnimation;
} Ark_DragEvent;
typedef struct Opt_DragEvent {
    enum Ark_Tag tag;
    Ark_DragEvent value;
} Opt_DragEvent;
typedef struct Ark_KeyEvent {
    Ark_KeyType type;
    Ark_Number keyCode;
    Ark_String keyText;
    Ark_KeySource keySource;
    Ark_Number deviceId;
    Ark_Number metaKey;
    Ark_Number timestamp;
    struct Ark_Function stopPropagation;
    Ark_CustomObject intentionCode;
    Opt_Number unicode;
} Ark_KeyEvent;
typedef struct Opt_KeyEvent {
    enum Ark_Tag tag;
    Ark_KeyEvent value;
} Opt_KeyEvent;
typedef struct Ark_TouchObject {
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
} Ark_TouchObject;
typedef struct Opt_TouchObject {
    enum Ark_Tag tag;
    Ark_TouchObject value;
} Opt_TouchObject;
typedef struct Ark_MouseEvent {
    struct Ark_EventTarget target;
    Ark_Number timestamp;
    Ark_SourceType source;
    Opt_Number axisHorizontal;
    Opt_Number axisVertical;
    Ark_Number pressure;
    Ark_Number tiltX;
    Ark_Number tiltY;
    Ark_SourceTool sourceTool;
    Opt_Number deviceId;
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
} Ark_MouseEvent;
typedef struct Opt_MouseEvent {
    enum Ark_Tag tag;
    Ark_MouseEvent value;
} Opt_MouseEvent;
typedef struct Ark_AccessibilityHoverEvent {
    struct Ark_EventTarget target;
    Ark_Number timestamp;
    Ark_SourceType source;
    Opt_Number axisHorizontal;
    Opt_Number axisVertical;
    Ark_Number pressure;
    Ark_Number tiltX;
    Ark_Number tiltY;
    Ark_SourceTool sourceTool;
    Opt_Number deviceId;
    Ark_AccessibilityHoverType type;
    Ark_Number x;
    Ark_Number y;
    Ark_Number displayX;
    Ark_Number displayY;
    Ark_Number windowX;
    Ark_Number windowY;
} Ark_AccessibilityHoverEvent;
typedef struct Opt_AccessibilityHoverEvent {
    enum Ark_Tag tag;
    Ark_AccessibilityHoverEvent value;
} Opt_AccessibilityHoverEvent;
typedef struct Ark_HoverEvent {
    struct Ark_EventTarget target;
    Ark_Number timestamp;
    Ark_SourceType source;
    Opt_Number axisHorizontal;
    Opt_Number axisVertical;
    Ark_Number pressure;
    Ark_Number tiltX;
    Ark_Number tiltY;
    Ark_SourceTool sourceTool;
    Opt_Number deviceId;
    struct Ark_Function stopPropagation;
} Ark_HoverEvent;
typedef struct Opt_HoverEvent {
    enum Ark_Tag tag;
    Ark_HoverEvent value;
} Opt_HoverEvent;
typedef struct Ark_ClickEvent {
    struct Ark_EventTarget target;
    Ark_Number timestamp;
    Ark_SourceType source;
    Opt_Number axisHorizontal;
    Opt_Number axisVertical;
    Ark_Number pressure;
    Ark_Number tiltX;
    Ark_Number tiltY;
    Ark_SourceTool sourceTool;
    Opt_Number deviceId;
    Ark_Number displayX;
    Ark_Number displayY;
    Ark_Number windowX;
    Ark_Number windowY;
    Ark_Number screenX;
    Ark_Number screenY;
    Ark_Number x;
    Ark_Number y;
    struct Ark_Function preventDefault;
} Ark_ClickEvent;
typedef struct Opt_ClickEvent {
    enum Ark_Tag tag;
    Ark_ClickEvent value;
} Opt_ClickEvent;
typedef struct Ark_TouchTestInfo {
    Ark_Number windowX;
    Ark_Number windowY;
    Ark_Number parentX;
    Ark_Number parentY;
    Ark_Number x;
    Ark_Number y;
    struct Ark_RectResult rect;
    Ark_String id;
} Ark_TouchTestInfo;
typedef struct Opt_TouchTestInfo {
    enum Ark_Tag tag;
    Ark_TouchTestInfo value;
} Opt_TouchTestInfo;
typedef struct Array_TouchTestInfo {
    struct Ark_TouchTestInfo* array;
    Ark_Int32 length;
} Array_TouchTestInfo;
typedef struct Opt_Array_TouchTestInfo {
    enum Ark_Tag tag;
    Array_TouchTestInfo value;
} Opt_Array_TouchTestInfo;
typedef struct Ark_CheckboxGroupResult {
    struct Array_String name;
    Ark_SelectStatus status;
} Ark_CheckboxGroupResult;
typedef struct Opt_CheckboxGroupResult {
    enum Ark_Tag tag;
    Ark_CheckboxGroupResult value;
} Opt_CheckboxGroupResult;
typedef struct Ark_CalendarRequestedData {
    Ark_Number year;
    Ark_Number month;
    Ark_Number currentYear;
    Ark_Number currentMonth;
    Ark_Number monthState;
} Ark_CalendarRequestedData;
typedef struct Opt_CalendarRequestedData {
    enum Ark_Tag tag;
    Ark_CalendarRequestedData value;
} Opt_CalendarRequestedData;
typedef struct Ark_CalendarSelectedDate {
    Ark_Number year;
    Ark_Number month;
    Ark_Number day;
} Ark_CalendarSelectedDate;
typedef struct Opt_CalendarSelectedDate {
    enum Ark_Tag tag;
    Ark_CalendarSelectedDate value;
} Opt_CalendarSelectedDate;
typedef struct Ark_LinearIndicatorStartOptions {
    Opt_Number interval;
    Opt_Number duration;
} Ark_LinearIndicatorStartOptions;
typedef struct Opt_LinearIndicatorStartOptions {
    enum Ark_Tag tag;
    Ark_LinearIndicatorStartOptions value;
} Opt_LinearIndicatorStartOptions;
typedef struct Ark_SectionOptions {
    Ark_Number itemsCount;
    Opt_Number crossCount;
    struct Opt_Function onGetItemMainSizeByIndex;
    Opt_Length columnsGap;
    Opt_Length rowsGap;
    struct Opt_Union_Padding_Length margin;
} Ark_SectionOptions;
typedef struct Opt_SectionOptions {
    enum Ark_Tag tag;
    Ark_SectionOptions value;
} Opt_SectionOptions;
typedef struct Array_SectionOptions {
    struct Ark_SectionOptions* array;
    Ark_Int32 length;
} Array_SectionOptions;
typedef struct Opt_Array_SectionOptions {
    enum Ark_Tag tag;
    Array_SectionOptions value;
} Opt_Array_SectionOptions;
typedef struct Ark_SurfaceRotationOptions {
    Opt_Boolean lock;
} Ark_SurfaceRotationOptions;
typedef struct Opt_SurfaceRotationOptions {
    enum Ark_Tag tag;
    Ark_SurfaceRotationOptions value;
} Opt_SurfaceRotationOptions;
typedef struct Ark_SurfaceRect {
    Opt_Number offsetX;
    Opt_Number offsetY;
    Ark_Number surfaceWidth;
    Ark_Number surfaceHeight;
} Ark_SurfaceRect;
typedef struct Opt_SurfaceRect {
    enum Ark_Tag tag;
    Ark_SurfaceRect value;
} Opt_SurfaceRect;
typedef struct Literal_Number_surfaceWidth_surfaceHeight {
    Ark_Number surfaceWidth;
    Ark_Number surfaceHeight;
} Literal_Number_surfaceWidth_surfaceHeight;
typedef struct Opt_Literal_Number_surfaceWidth_surfaceHeight {
    enum Ark_Tag tag;
    Literal_Number_surfaceWidth_surfaceHeight value;
} Opt_Literal_Number_surfaceWidth_surfaceHeight;
typedef struct Ark_ScreenCaptureConfig {
    Ark_WebCaptureMode captureMode;
} Ark_ScreenCaptureConfig;
typedef struct Opt_ScreenCaptureConfig {
    enum Ark_Tag tag;
    Ark_ScreenCaptureConfig value;
} Opt_ScreenCaptureConfig;
typedef struct Union_String_Number_Resource_ArrayBuffer {
    Ark_Int32 selector;
    union {
        Ark_String value0;
        Ark_Number value1;
        struct Ark_Resource value2;
        struct Ark_ArrayBuffer value3;
    };
} Union_String_Number_Resource_ArrayBuffer;
typedef struct Opt_Union_String_Number_Resource_ArrayBuffer {
    enum Ark_Tag tag;
    Union_String_Number_Resource_ArrayBuffer value;
} Opt_Union_String_Number_Resource_ArrayBuffer;
typedef Ark_Int32 Ark_MessageLevel;
typedef struct Opt_MessageLevel {
    enum Ark_Tag tag;
    Ark_MessageLevel value;
} Opt_MessageLevel;
typedef struct Literal_CustomObject_object_String_name_Array_String_methodList {
    Ark_CustomObject object;
    Ark_String name;
    struct Array_String methodList;
} Literal_CustomObject_object_String_name_Array_String_methodList;
typedef struct Opt_Literal_CustomObject_object_String_name_Array_String_methodList {
    enum Ark_Tag tag;
    Literal_CustomObject_object_String_name_Array_String_methodList value;
} Opt_Literal_CustomObject_object_String_name_Array_String_methodList;
typedef struct Ark_Header {
    Ark_String headerKey;
    Ark_String headerValue;
} Ark_Header;
typedef struct Opt_Header {
    enum Ark_Tag tag;
    Ark_Header value;
} Opt_Header;
typedef struct Literal_Union_String_Resource_url_Opt_Array_Header_headers {
    struct Union_String_Resource url;
    struct Opt_Array_Header headers;
} Literal_Union_String_Resource_url_Opt_Array_Header_headers;
typedef struct Opt_Literal_Union_String_Resource_url_Opt_Array_Header_headers {
    enum Ark_Tag tag;
    Literal_Union_String_Resource_url_Opt_Array_Header_headers value;
} Opt_Literal_Union_String_Resource_url_Opt_Array_Header_headers;
typedef struct Literal_String_data_mimeType_encoding_Opt_String_baseUrl_historyUrl {
    Ark_String data;
    Ark_String mimeType;
    Ark_String encoding;
    Opt_String baseUrl;
    Opt_String historyUrl;
} Literal_String_data_mimeType_encoding_Opt_String_baseUrl_historyUrl;
typedef struct Opt_Literal_String_data_mimeType_encoding_Opt_String_baseUrl_historyUrl {
    enum Ark_Tag tag;
    Literal_String_data_mimeType_encoding_Opt_String_baseUrl_historyUrl value;
} Opt_Literal_String_data_mimeType_encoding_Opt_String_baseUrl_historyUrl;
typedef struct Literal_String_script_Opt_Function_callback {
    Ark_String script;
    struct Opt_Function callback;
} Literal_String_script_Opt_Function_callback;
typedef struct Opt_Literal_String_script_Opt_Function_callback {
    enum Ark_Tag tag;
    Literal_String_script_Opt_Function_callback value;
} Opt_Literal_String_script_Opt_Function_callback;
typedef Ark_Int32 Ark_SeekMode;
typedef struct Opt_SeekMode {
    enum Ark_Tag tag;
    Ark_SeekMode value;
} Opt_SeekMode;
typedef struct Ark_SpanStyle {
    Ark_Number start;
    Ark_Number length;
    Ark_StyledStringKey styledKey;
    struct Ark_StyledStringValue styledValue;
} Ark_SpanStyle;
typedef struct Opt_SpanStyle {
    enum Ark_Tag tag;
    Ark_SpanStyle value;
} Opt_SpanStyle;
typedef struct Ark_StyledStringChangedListener {
    struct Opt_Function onWillChange;
    struct Opt_Function onDidChange;
} Ark_StyledStringChangedListener;
typedef struct Opt_StyledStringChangedListener {
    enum Ark_Tag tag;
    Ark_StyledStringChangedListener value;
} Opt_StyledStringChangedListener;
typedef struct Ark_CustomSpanDrawInfo {
    Ark_Number x;
    Ark_Number lineTop;
    Ark_Number lineBottom;
    Ark_Number baseline;
} Ark_CustomSpanDrawInfo;
typedef struct Opt_CustomSpanDrawInfo {
    enum Ark_Tag tag;
    Ark_CustomSpanDrawInfo value;
} Opt_CustomSpanDrawInfo;
typedef struct Ark_CustomSpanMeasureInfo {
    Ark_Number fontSize;
} Ark_CustomSpanMeasureInfo;
typedef struct Opt_CustomSpanMeasureInfo {
    enum Ark_Tag tag;
    Ark_CustomSpanMeasureInfo value;
} Opt_CustomSpanMeasureInfo;
typedef struct Ark_StyleOptions {
    Opt_Number start;
    Opt_Number length;
    Ark_StyledStringKey styledKey;
    struct Ark_StyledStringValue styledValue;
} Ark_StyleOptions;
typedef struct Opt_StyleOptions {
    enum Ark_Tag tag;
    Ark_StyleOptions value;
} Opt_StyleOptions;
typedef struct Array_StyleOptions {
    struct Ark_StyleOptions* array;
    Ark_Int32 length;
} Array_StyleOptions;
typedef struct Opt_Array_StyleOptions {
    enum Ark_Tag tag;
    Array_StyleOptions value;
} Opt_Array_StyleOptions;
typedef struct Union_String_ImageAttachment_CustomSpan {
    Ark_Int32 selector;
    union {
        Ark_String value0;
        struct Ark_ImageAttachment value1;
        Ark_CustomSpan value2;
    };
} Union_String_ImageAttachment_CustomSpan;
typedef struct Opt_Union_String_ImageAttachment_CustomSpan {
    enum Ark_Tag tag;
    Union_String_ImageAttachment_CustomSpan value;
} Opt_Union_String_ImageAttachment_CustomSpan;
typedef struct Ark_SelectionOptions {
    Opt_MenuPolicy menuPolicy;
} Ark_SelectionOptions;
typedef struct Opt_SelectionOptions {
    enum Ark_Tag tag;
    Ark_SelectionOptions value;
} Opt_SelectionOptions;
typedef Ark_Materialized Ark_StyledString;
typedef struct Opt_StyledString {
    enum Ark_Tag tag;
    Ark_StyledString value;
} Opt_StyledString;
typedef struct Ark_RichEditorParagraphStyleOptions {
    Opt_Number start;
    Opt_Number end;
    struct Ark_RichEditorParagraphStyle style;
} Ark_RichEditorParagraphStyleOptions;
typedef struct Opt_RichEditorParagraphStyleOptions {
    enum Ark_Tag tag;
    Ark_RichEditorParagraphStyleOptions value;
} Opt_RichEditorParagraphStyleOptions;
typedef struct Union_RichEditorUpdateTextSpanStyleOptions_RichEditorUpdateImageSpanStyleOptions_RichEditorUpdateSymbolSpanStyleOptions {
    Ark_Int32 selector;
    union {
        struct Ark_RichEditorUpdateTextSpanStyleOptions value0;
        struct Ark_RichEditorUpdateImageSpanStyleOptions value1;
        struct Ark_RichEditorUpdateSymbolSpanStyleOptions value2;
    };
} Union_RichEditorUpdateTextSpanStyleOptions_RichEditorUpdateImageSpanStyleOptions_RichEditorUpdateSymbolSpanStyleOptions;
typedef struct Opt_Union_RichEditorUpdateTextSpanStyleOptions_RichEditorUpdateImageSpanStyleOptions_RichEditorUpdateSymbolSpanStyleOptions {
    enum Ark_Tag tag;
    Union_RichEditorUpdateTextSpanStyleOptions_RichEditorUpdateImageSpanStyleOptions_RichEditorUpdateSymbolSpanStyleOptions value;
} Opt_Union_RichEditorUpdateTextSpanStyleOptions_RichEditorUpdateImageSpanStyleOptions_RichEditorUpdateSymbolSpanStyleOptions;
typedef struct Ark_RichEditorSymbolSpanOptions {
    Opt_Number offset;
    struct Opt_RichEditorSymbolSpanStyle style;
} Ark_RichEditorSymbolSpanOptions;
typedef struct Opt_RichEditorSymbolSpanOptions {
    enum Ark_Tag tag;
    Ark_RichEditorSymbolSpanOptions value;
} Opt_RichEditorSymbolSpanOptions;
typedef struct Ark_RichEditorBuilderSpanOptions {
    Opt_Number offset;
} Ark_RichEditorBuilderSpanOptions;
typedef struct Opt_RichEditorBuilderSpanOptions {
    enum Ark_Tag tag;
    Ark_RichEditorBuilderSpanOptions value;
} Opt_RichEditorBuilderSpanOptions;
typedef struct Ark_RichEditorImageSpanOptions {
    Opt_Number offset;
    struct Opt_RichEditorImageSpanStyle imageStyle;
    struct Opt_RichEditorGesture gesture;
} Ark_RichEditorImageSpanOptions;
typedef struct Opt_RichEditorImageSpanOptions {
    enum Ark_Tag tag;
    Ark_RichEditorImageSpanOptions value;
} Opt_RichEditorImageSpanOptions;
typedef struct Union_CustomObject_Ark_ResourceStr {
    Ark_Int32 selector;
    union {
        Ark_CustomObject value0;
        struct Ark_ResourceStr value1;
    };
} Union_CustomObject_Ark_ResourceStr;
typedef struct Opt_Union_CustomObject_ResourceStr {
    enum Ark_Tag tag;
    Union_CustomObject_Ark_ResourceStr value;
} Opt_Union_CustomObject_ResourceStr;
typedef struct Ark_RichEditorTextSpanOptions {
    Opt_Number offset;
    struct Opt_RichEditorTextStyle style;
    struct Opt_RichEditorParagraphStyle paragraphStyle;
    struct Opt_RichEditorGesture gesture;
} Ark_RichEditorTextSpanOptions;
typedef struct Opt_RichEditorTextSpanOptions {
    enum Ark_Tag tag;
    Ark_RichEditorTextSpanOptions value;
} Opt_RichEditorTextSpanOptions;
typedef struct Ark_TextMenuItem {
    struct Ark_ResourceStr content;
    struct Opt_ResourceStr icon;
    struct Ark_TextMenuItemId id;
} Ark_TextMenuItem;
typedef struct Opt_TextMenuItem {
    enum Ark_Tag tag;
    Ark_TextMenuItem value;
} Opt_TextMenuItem;
typedef struct Array_TextMenuItem {
    struct Ark_TextMenuItem* array;
    Ark_Int32 length;
} Array_TextMenuItem;
typedef struct Opt_Array_TextMenuItem {
    enum Ark_Tag tag;
    Array_TextMenuItem value;
} Opt_Array_TextMenuItem;
typedef Ark_Int32 Ark_PatternLockChallengeResult;
typedef struct Opt_PatternLockChallengeResult {
    enum Ark_Tag tag;
    Ark_PatternLockChallengeResult value;
} Opt_PatternLockChallengeResult;
typedef struct Ark_NavigationInterception {
    struct Opt_Function willShow;
    struct Opt_Function didShow;
    struct Opt_Function modeChange;
} Ark_NavigationInterception;
typedef struct Opt_NavigationInterception {
    enum Ark_Tag tag;
    Ark_NavigationInterception value;
} Opt_NavigationInterception;
typedef struct Ark_NavigationOptions {
    Opt_LaunchMode launchMode;
    Opt_Boolean animated;
} Ark_NavigationOptions;
typedef struct Opt_NavigationOptions {
    enum Ark_Tag tag;
    Ark_NavigationOptions value;
} Opt_NavigationOptions;
typedef struct Ark_NavPathInfo {
    Ark_String name;
    Opt_CustomObject param;
    Opt_Function onPop;
    Opt_Boolean isEntry;
} Ark_NavPathInfo;
typedef struct Opt_NavPathInfo {
    enum Ark_Tag tag;
    Ark_NavPathInfo value;
} Opt_NavPathInfo;
typedef struct Ark_ScrollToIndexOptions {
    Opt_CustomObject extraOffset;
} Ark_ScrollToIndexOptions;
typedef struct Opt_ScrollToIndexOptions {
    enum Ark_Tag tag;
    Ark_ScrollToIndexOptions value;
} Opt_ScrollToIndexOptions;
typedef Ark_Int32 Ark_ScrollAlign;
typedef struct Opt_ScrollAlign {
    enum Ark_Tag tag;
    Ark_ScrollAlign value;
} Opt_ScrollAlign;
typedef struct Literal_Boolean_next_Opt_Axis_direction {
    Ark_Boolean next;
    Opt_Axis direction;
} Literal_Boolean_next_Opt_Axis_direction;
typedef struct Opt_Literal_Boolean_next_Opt_Axis_direction {
    enum Ark_Tag tag;
    Literal_Boolean_next_Opt_Axis_direction value;
} Opt_Literal_Boolean_next_Opt_Axis_direction;
typedef struct Ark_ScrollPageOptions {
    Ark_Boolean next;
    Opt_Boolean animation;
} Ark_ScrollPageOptions;
typedef struct Opt_ScrollPageOptions {
    enum Ark_Tag tag;
    Ark_ScrollPageOptions value;
} Opt_ScrollPageOptions;
typedef struct Ark_ScrollEdgeOptions {
    Opt_Number velocity;
} Ark_ScrollEdgeOptions;
typedef struct Opt_ScrollEdgeOptions {
    enum Ark_Tag tag;
    Ark_ScrollEdgeOptions value;
} Opt_ScrollEdgeOptions;
typedef Ark_Int32 Ark_Edge;
typedef struct Opt_Edge {
    enum Ark_Tag tag;
    Ark_Edge value;
} Opt_Edge;
typedef struct Ark_ScrollOptions {
    struct Union_Number_String xOffset;
    struct Union_Number_String yOffset;
    struct Opt_Union_ScrollAnimationOptions_Boolean animation;
} Ark_ScrollOptions;
typedef struct Opt_ScrollOptions {
    enum Ark_Tag tag;
    Ark_ScrollOptions value;
} Opt_ScrollOptions;
typedef Ark_Materialized Ark_Matrix2D;
typedef struct Opt_Matrix2D {
    enum Ark_Tag tag;
    Ark_Matrix2D value;
} Opt_Matrix2D;
typedef struct Ark_ImageData {
    struct Ark_Uint8ClampedArray data;
    Ark_Number height;
    Ark_Number width;
} Ark_ImageData;
typedef struct Opt_ImageData {
    enum Ark_Tag tag;
    Ark_ImageData value;
} Opt_ImageData;
typedef struct Union_String_Ark_Undefined {
    Ark_Int32 selector;
    union {
        Ark_String value0;
        struct Ark_Undefined value1;
    };
} Union_String_Ark_Undefined;
typedef struct Opt_Union_String_Undefined {
    enum Ark_Tag tag;
    Union_String_Ark_Undefined value;
} Opt_Union_String_Undefined;
typedef Ark_Materialized Ark_Path2D;
typedef struct Opt_Path2D {
    enum Ark_Tag tag;
    Ark_Path2D value;
} Opt_Path2D;
typedef struct Ark_CanvasFillRule {
    Ark_Int32 selector;
    union {
        struct Ark_String value0;
        struct Ark_String value1;
    };
} Ark_CanvasFillRule;
typedef struct Opt_CanvasFillRule {
    enum Ark_Tag tag;
    Ark_CanvasFillRule value;
} Opt_CanvasFillRule;
typedef struct Union_ImageBitmap_CustomObject {
    Ark_Int32 selector;
    union {
        Ark_ImageBitmap value0;
        Ark_CustomObject value1;
    };
} Union_ImageBitmap_CustomObject;
typedef struct Opt_Union_ImageBitmap_CustomObject {
    enum Ark_Tag tag;
    Union_ImageBitmap_CustomObject value;
} Opt_Union_ImageBitmap_CustomObject;
typedef struct Ark_RenderingContextSettings {
    Opt_Boolean antialias;
} Ark_RenderingContextSettings;
typedef struct Opt_RenderingContextSettings {
    enum Ark_Tag tag;
    Ark_RenderingContextSettings value;
} Opt_RenderingContextSettings;
typedef struct Ark_UIGestureEvent {
    void *handle;
} Ark_UIGestureEvent;
typedef struct Opt_UIGestureEvent {
    enum Ark_Tag tag;
    Ark_UIGestureEvent value;
} Opt_UIGestureEvent;
typedef struct Literal_Opt_Number_fingers_distance_Opt_PanDirection_direction {
    Opt_Number fingers;
    Opt_PanDirection direction;
    Opt_Number distance;
} Literal_Opt_Number_fingers_distance_Opt_PanDirection_direction;
typedef struct Opt_Literal_Opt_Number_fingers_distance_Opt_PanDirection_direction {
    enum Ark_Tag tag;
    Literal_Opt_Number_fingers_distance_Opt_PanDirection_direction value;
} Opt_Literal_Opt_Number_fingers_distance_Opt_PanDirection_direction;
typedef Ark_Materialized Ark_LinearIndicatorController;
typedef struct Opt_LinearIndicatorController {
    enum Ark_Tag tag;
    Ark_LinearIndicatorController value;
} Opt_LinearIndicatorController;
typedef struct Ark_UIExtensionOptions {
    Opt_Boolean isTransferringCaller;
    Opt_CustomObject placeholder;
    Opt_DpiFollowStrategy dpiFollowStrategy;
} Ark_UIExtensionOptions;
typedef struct Opt_UIExtensionOptions {
    enum Ark_Tag tag;
    Ark_UIExtensionOptions value;
} Opt_UIExtensionOptions;
typedef struct Ark_WaterFlowOptions {
    struct Opt_CustomBuilder footer;
    Opt_Scroller scroller;
    Opt_WaterFlowSections sections;
    Opt_WaterFlowLayoutMode layoutMode;
} Ark_WaterFlowOptions;
typedef struct Opt_WaterFlowOptions {
    enum Ark_Tag tag;
    Ark_WaterFlowOptions value;
} Opt_WaterFlowOptions;
typedef struct Ark_WindowAnimationTarget {
    Ark_String bundleName;
    Ark_String abilityName;
    struct Ark_RRect windowBounds;
    Ark_Number missionId;
} Ark_WindowAnimationTarget;
typedef struct Opt_WindowAnimationTarget {
    enum Ark_Tag tag;
    Ark_WindowAnimationTarget value;
} Opt_WindowAnimationTarget;
typedef struct Union_DividerStyle_Ark_Undefined {
    Ark_Int32 selector;
    union {
        struct Ark_DividerStyle value0;
        struct Ark_Undefined value1;
    };
} Union_DividerStyle_Ark_Undefined;
typedef struct Opt_Union_DividerStyle_Undefined {
    enum Ark_Tag tag;
    Union_DividerStyle_Ark_Undefined value;
} Opt_Union_DividerStyle_Undefined;
typedef Ark_Int32 Ark_SideBarPosition;
typedef struct Opt_SideBarPosition {
    enum Ark_Tag tag;
    Ark_SideBarPosition value;
} Opt_SideBarPosition;
typedef struct Ark_ButtonStyle {
    Opt_Number left;
    Opt_Number top;
    Opt_Number width;
    Opt_Number height;
    struct Opt_Literal_Union_String_CustomObject_Resource_shown_hidden_Opt_Union_String_CustomObject_Resource_switching icons;
} Ark_ButtonStyle;
typedef struct Opt_ButtonStyle {
    enum Ark_Tag tag;
    Ark_ButtonStyle value;
} Opt_ButtonStyle;
typedef Ark_Int32 Ark_SideBarContainerType;
typedef struct Opt_SideBarContainerType {
    enum Ark_Tag tag;
    Ark_SideBarContainerType value;
} Opt_SideBarContainerType;
typedef struct Ark_XComponentOptions {
    Ark_XComponentType type;
    Ark_XComponentController controller;
    struct Opt_ImageAIOptions imageAIOptions;
} Ark_XComponentOptions;
typedef struct Opt_XComponentOptions {
    enum Ark_Tag tag;
    Ark_XComponentOptions value;
} Opt_XComponentOptions;
typedef struct Literal_String_id_XComponentType_type_Opt_String_libraryname_Opt_XComponentController_controller {
    Ark_String id;
    Ark_XComponentType type;
    Opt_String libraryname;
    Opt_XComponentController controller;
} Literal_String_id_XComponentType_type_Opt_String_libraryname_Opt_XComponentController_controller;
typedef struct Opt_Literal_String_id_XComponentType_type_Opt_String_libraryname_Opt_XComponentController_controller {
    enum Ark_Tag tag;
    Literal_String_id_XComponentType_type_Opt_String_libraryname_Opt_XComponentController_controller value;
} Opt_Literal_String_id_XComponentType_type_Opt_String_libraryname_Opt_XComponentController_controller;
typedef struct Literal_String_id_type_Opt_String_libraryname_Opt_XComponentController_controller {
    Ark_String id;
    Ark_String type;
    Opt_String libraryname;
    Opt_XComponentController controller;
} Literal_String_id_type_Opt_String_libraryname_Opt_XComponentController_controller;
typedef struct Opt_Literal_String_id_type_Opt_String_libraryname_Opt_XComponentController_controller {
    enum Ark_Tag tag;
    Literal_String_id_type_Opt_String_libraryname_Opt_XComponentController_controller value;
} Opt_Literal_String_id_type_Opt_String_libraryname_Opt_XComponentController_controller;
typedef Ark_Int32 Ark_WebKeyboardAvoidMode;
typedef struct Opt_WebKeyboardAvoidMode {
    enum Ark_Tag tag;
    Ark_WebKeyboardAvoidMode value;
} Opt_WebKeyboardAvoidMode;
typedef struct Ark_ExpandedMenuItemOptions {
    struct Ark_ResourceStr content;
    struct Opt_ResourceStr startIcon;
    struct Ark_Function action;
} Ark_ExpandedMenuItemOptions;
typedef struct Opt_ExpandedMenuItemOptions {
    enum Ark_Tag tag;
    Ark_ExpandedMenuItemOptions value;
} Opt_ExpandedMenuItemOptions;
typedef struct Array_ExpandedMenuItemOptions {
    struct Ark_ExpandedMenuItemOptions* array;
    Ark_Int32 length;
} Array_ExpandedMenuItemOptions;
typedef struct Opt_Array_ExpandedMenuItemOptions {
    enum Ark_Tag tag;
    Array_ExpandedMenuItemOptions value;
} Opt_Array_ExpandedMenuItemOptions;
typedef struct Ark_NativeMediaPlayerConfig {
    Ark_Boolean enable;
    Ark_Boolean shouldOverlay;
} Ark_NativeMediaPlayerConfig;
typedef struct Opt_NativeMediaPlayerConfig {
    enum Ark_Tag tag;
    Ark_NativeMediaPlayerConfig value;
} Opt_NativeMediaPlayerConfig;
typedef struct Union_NestedScrollOptions_NestedScrollOptionsExt {
    Ark_Int32 selector;
    union {
        struct Ark_NestedScrollOptions value0;
        struct Ark_NestedScrollOptionsExt value1;
    };
} Union_NestedScrollOptions_NestedScrollOptionsExt;
typedef struct Opt_Union_NestedScrollOptions_NestedScrollOptionsExt {
    enum Ark_Tag tag;
    Union_NestedScrollOptions_NestedScrollOptionsExt value;
} Opt_Union_NestedScrollOptions_NestedScrollOptionsExt;
typedef Ark_Int32 Ark_WebLayoutMode;
typedef struct Opt_WebLayoutMode {
    enum Ark_Tag tag;
    Ark_WebLayoutMode value;
} Opt_WebLayoutMode;
typedef struct Array_ScriptItem {
    struct Ark_ScriptItem* array;
    Ark_Int32 length;
} Array_ScriptItem;
typedef struct Opt_Array_ScriptItem {
    enum Ark_Tag tag;
    Array_ScriptItem value;
} Opt_Array_ScriptItem;
typedef struct Ark_ScriptItem {
    Ark_String script;
    struct Array_String scriptRules;
} Ark_ScriptItem;
typedef struct Opt_ScriptItem {
    enum Ark_Tag tag;
    Ark_ScriptItem value;
} Opt_ScriptItem;
typedef Ark_Int32 Ark_OverScrollMode;
typedef struct Opt_OverScrollMode {
    enum Ark_Tag tag;
    Ark_OverScrollMode value;
} Opt_OverScrollMode;
typedef struct Ark_WebMediaOptions {
    Opt_Number resumeInterval;
    Opt_Boolean audioExclusive;
} Ark_WebMediaOptions;
typedef struct Opt_WebMediaOptions {
    enum Ark_Tag tag;
    Ark_WebMediaOptions value;
} Opt_WebMediaOptions;
typedef Ark_Int32 Ark_WebDarkMode;
typedef struct Opt_WebDarkMode {
    enum Ark_Tag tag;
    Ark_WebDarkMode value;
} Opt_WebDarkMode;
typedef Ark_Int32 Ark_CacheMode;
typedef struct Opt_CacheMode {
    enum Ark_Tag tag;
    Ark_CacheMode value;
} Opt_CacheMode;
typedef struct Ark_JavaScriptProxy {
    Ark_CustomObject object;
    Ark_String name;
    struct Array_String methodList;
    struct Union_WebController_CustomObject controller;
    struct Opt_Array_String asyncMethodList;
    Opt_String permission;
} Ark_JavaScriptProxy;
typedef struct Opt_JavaScriptProxy {
    enum Ark_Tag tag;
    Ark_JavaScriptProxy value;
} Opt_JavaScriptProxy;
typedef Ark_Int32 Ark_MixedMode;
typedef struct Opt_MixedMode {
    enum Ark_Tag tag;
    Ark_MixedMode value;
} Opt_MixedMode;
typedef struct Ark_WebOptions {
    struct Union_String_Resource src;
    struct Union_WebController_CustomObject controller;
    Opt_RenderMode renderMode;
    Opt_Boolean incognitoMode;
    Opt_String sharedRenderProcessToken;
} Ark_WebOptions;
typedef struct Opt_WebOptions {
    enum Ark_Tag tag;
    Ark_WebOptions value;
} Opt_WebOptions;
typedef struct Ark_VideoOptions {
    struct Opt_Union_String_Resource src;
    struct Opt_Union_Number_String_PlaybackSpeed currentProgressRate;
    struct Opt_Union_String_CustomObject_Resource previewUri;
    Opt_VideoController controller;
    struct Opt_ImageAIOptions imageAIOptions;
} Ark_VideoOptions;
typedef struct Opt_VideoOptions {
    enum Ark_Tag tag;
    Ark_VideoOptions value;
} Opt_VideoOptions;
typedef struct Ark_SwitchStyle {
    struct Opt_Union_Number_Resource pointRadius;
    struct Opt_ResourceColor unselectedColor;
    struct Opt_ResourceColor pointColor;
    struct Opt_Union_Number_Resource trackBorderRadius;
} Ark_SwitchStyle;
typedef struct Opt_SwitchStyle {
    enum Ark_Tag tag;
    Ark_SwitchStyle value;
} Opt_SwitchStyle;
typedef struct Ark_ToggleOptions {
    Ark_ToggleType type;
    Opt_Boolean isOn;
} Ark_ToggleOptions;
typedef struct Opt_ToggleOptions {
    enum Ark_Tag tag;
    Ark_ToggleOptions value;
} Opt_ToggleOptions;
typedef struct Ark_TimePickerOptions {
    Opt_CustomObject selected;
    Opt_TimePickerFormat format;
} Ark_TimePickerOptions;
typedef struct Opt_TimePickerOptions {
    enum Ark_Tag tag;
    Ark_TimePickerOptions value;
} Opt_TimePickerOptions;
typedef struct Ark_TextTimerOptions {
    Opt_Boolean isCountDown;
    Opt_Number count;
    Opt_TextTimerController controller;
} Ark_TextTimerOptions;
typedef struct Opt_TextTimerOptions {
    enum Ark_Tag tag;
    Ark_TextTimerOptions value;
} Opt_TextTimerOptions;
typedef struct Union_DividerOptions_Ark_Undefined {
    Ark_Int32 selector;
    union {
        struct Ark_DividerOptions value0;
        struct Ark_Undefined value1;
    };
} Union_DividerOptions_Ark_Undefined;
typedef struct Opt_Union_DividerOptions_Undefined {
    enum Ark_Tag tag;
    Union_DividerOptions_Ark_Undefined value;
} Opt_Union_DividerOptions_Undefined;
typedef struct Ark_TextCascadePickerRangeContent {
    struct Union_String_Resource text;
    struct Opt_Array_TextCascadePickerRangeContent children;
} Ark_TextCascadePickerRangeContent;
typedef struct Opt_TextCascadePickerRangeContent {
    enum Ark_Tag tag;
    Ark_TextCascadePickerRangeContent value;
} Opt_TextCascadePickerRangeContent;
typedef struct Ark_TextPickerRangeContent {
    struct Union_String_Resource icon;
    struct Opt_Union_String_Resource text;
} Ark_TextPickerRangeContent;
typedef struct Opt_TextPickerRangeContent {
    enum Ark_Tag tag;
    Ark_TextPickerRangeContent value;
} Opt_TextPickerRangeContent;
typedef struct Ark_TextPickerOptions {
    struct Union_Array_String_Array_Array_String_Resource_Array_TextPickerRangeContent_Array_TextCascadePickerRangeContent range;
    struct Opt_Union_String_Array_String value;
    struct Opt_Union_Number_Array_Number selected;
} Ark_TextPickerOptions;
typedef struct Opt_TextPickerOptions {
    enum Ark_Tag tag;
    Ark_TextPickerOptions value;
} Opt_TextPickerOptions;
typedef struct Literal_Opt_CancelButtonStyle_style_Opt_IconOptions_icon {
    Opt_CancelButtonStyle style;
    struct Opt_IconOptions icon;
} Literal_Opt_CancelButtonStyle_style_Opt_IconOptions_icon;
typedef struct Opt_Literal_Opt_CancelButtonStyle_style_Opt_IconOptions_icon {
    enum Ark_Tag tag;
    Literal_Opt_CancelButtonStyle_style_Opt_IconOptions_icon value;
} Opt_Literal_Opt_CancelButtonStyle_style_Opt_IconOptions_icon;
typedef struct Union_Ark_ResourceColor_UnderlineColor_Undefined {
    Ark_Int32 selector;
    union {
        struct Ark_ResourceColor value0;
        struct Ark_UnderlineColor value1;
        Ark_Undefined value2;
    };
} Union_Ark_ResourceColor_UnderlineColor_Undefined;
typedef struct Opt_Union_ResourceColor_UnderlineColor_Undefined {
    enum Ark_Tag tag;
    Union_Ark_ResourceColor_UnderlineColor_Undefined value;
} Opt_Union_ResourceColor_UnderlineColor_Undefined;
typedef struct Union_Ark_ResourceStr_Undefined {
    Ark_Int32 selector;
    union {
        struct Ark_ResourceStr value0;
        Ark_Undefined value1;
    };
} Union_Ark_ResourceStr_Undefined;
typedef struct Opt_Union_ResourceStr_Undefined {
    enum Ark_Tag tag;
    Union_Ark_ResourceStr_Undefined value;
} Opt_Union_ResourceStr_Undefined;
typedef struct Ark_PasswordIcon {
    struct Opt_Union_String_Resource onIconSrc;
    struct Opt_Union_String_Resource offIconSrc;
} Ark_PasswordIcon;
typedef struct Opt_PasswordIcon {
    enum Ark_Tag tag;
    Ark_PasswordIcon value;
} Opt_PasswordIcon;
typedef struct Union_TextInputStyle_TextContentStyle {
    Ark_Int32 selector;
    union {
        Ark_TextInputStyle value0;
        Ark_TextContentStyle value1;
    };
} Union_TextInputStyle_TextContentStyle;
typedef struct Opt_Union_TextInputStyle_TextContentStyle {
    enum Ark_Tag tag;
    Union_TextInputStyle_TextContentStyle value;
} Opt_Union_TextInputStyle_TextContentStyle;
typedef Ark_Int32 Ark_InputType;
typedef struct Opt_InputType {
    enum Ark_Tag tag;
    Ark_InputType value;
} Opt_InputType;
typedef struct Ark_TextInputOptions {
    struct Opt_ResourceStr placeholder;
    struct Opt_ResourceStr text;
    Opt_TextInputController controller;
} Ark_TextInputOptions;
typedef struct Opt_TextInputOptions {
    enum Ark_Tag tag;
    Ark_TextInputOptions value;
} Opt_TextInputOptions;
typedef struct Literal_Opt_Number_timeZoneOffset_Opt_TextClockController_controller {
    Opt_Number timeZoneOffset;
    Opt_TextClockController controller;
} Literal_Opt_Number_timeZoneOffset_Opt_TextClockController_controller;
typedef struct Opt_Literal_Opt_Number_timeZoneOffset_Opt_TextClockController_controller {
    enum Ark_Tag tag;
    Literal_Opt_Number_timeZoneOffset_Opt_TextClockController_controller value;
} Opt_Literal_Opt_Number_timeZoneOffset_Opt_TextClockController_controller;
typedef Ark_Int32 Ark_ContentType;
typedef struct Opt_ContentType {
    enum Ark_Tag tag;
    Ark_ContentType value;
} Opt_ContentType;
typedef Ark_Int32 Ark_TextAreaType;
typedef struct Opt_TextAreaType {
    enum Ark_Tag tag;
    Ark_TextAreaType value;
} Opt_TextAreaType;
typedef struct Ark_InputCounterOptions {
    Opt_Number thresholdPercentage;
    Opt_Boolean highlightBorder;
} Ark_InputCounterOptions;
typedef struct Opt_InputCounterOptions {
    enum Ark_Tag tag;
    Ark_InputCounterOptions value;
} Opt_InputCounterOptions;
typedef struct Ark_TextAreaOptions {
    struct Opt_ResourceStr placeholder;
    struct Opt_ResourceStr text;
    Opt_TextAreaController controller;
} Ark_TextAreaOptions;
typedef struct Opt_TextAreaOptions {
    enum Ark_Tag tag;
    Ark_TextAreaOptions value;
} Opt_TextAreaOptions;
typedef Ark_Int32 Ark_TextSelectableMode;
typedef struct Opt_TextSelectableMode {
    enum Ark_Tag tag;
    Ark_TextSelectableMode value;
} Opt_TextSelectableMode;
typedef Ark_Int32 Ark_TextResponseType;
typedef struct Opt_TextResponseType {
    enum Ark_Tag tag;
    Ark_TextResponseType value;
} Opt_TextResponseType;
typedef Ark_Int32 Ark_TextSpanType;
typedef struct Opt_TextSpanType {
    enum Ark_Tag tag;
    Ark_TextSpanType value;
} Opt_TextSpanType;
typedef Ark_Int32 Ark_EllipsisMode;
typedef struct Opt_EllipsisMode {
    enum Ark_Tag tag;
    Ark_EllipsisMode value;
} Opt_EllipsisMode;
typedef struct Literal_TextOverflow_overflow {
    Ark_TextOverflow overflow;
} Literal_TextOverflow_overflow;
typedef struct Opt_Literal_TextOverflow_overflow {
    enum Ark_Tag tag;
    Literal_TextOverflow_overflow value;
} Opt_Literal_TextOverflow_overflow;
typedef struct Ark_FontSettingOptions {
    Opt_Boolean enableVariableFontWeight;
} Ark_FontSettingOptions;
typedef struct Opt_FontSettingOptions {
    enum Ark_Tag tag;
    Ark_FontSettingOptions value;
} Opt_FontSettingOptions;
typedef struct Ark_TextOptions {
    Ark_TextController controller;
} Ark_TextOptions;
typedef struct Opt_TextOptions {
    enum Ark_Tag tag;
    Ark_TextOptions value;
} Opt_TextOptions;
typedef struct Union_SubTabBarStyle_BottomTabBarStyle {
    Ark_Int32 selector;
    union {
        struct Ark_SubTabBarStyle value0;
        struct Ark_BottomTabBarStyle value1;
    };
} Union_SubTabBarStyle_BottomTabBarStyle;
typedef struct Opt_Union_SubTabBarStyle_BottomTabBarStyle {
    enum Ark_Tag tag;
    Union_SubTabBarStyle_BottomTabBarStyle value;
} Opt_Union_SubTabBarStyle_BottomTabBarStyle;
typedef struct Union_String_Resource_Ark_CustomBuilder_Literal_Opt_Union_String_Resource_icon_text {
    Ark_Int32 selector;
    union {
        Ark_String value0;
        struct Ark_Resource value1;
        struct Ark_CustomBuilder value2;
        struct Literal_Opt_Union_String_Resource_icon_text value3;
    };
} Union_String_Resource_Ark_CustomBuilder_Literal_Opt_Union_String_Resource_icon_text;
typedef struct Opt_Union_String_Resource_CustomBuilder_Literal_Opt_Union_String_Resource_icon_text {
    enum Ark_Tag tag;
    Union_String_Resource_Ark_CustomBuilder_Literal_Opt_Union_String_Resource_icon_text value;
} Opt_Union_String_Resource_CustomBuilder_Literal_Opt_Union_String_Resource_icon_text;
typedef struct Ark_BarGridColumnOptions {
    Opt_Number sm;
    Opt_Number md;
    Opt_Number lg;
    Opt_Length margin;
    Opt_Length gutter;
} Ark_BarGridColumnOptions;
typedef struct Opt_BarGridColumnOptions {
    enum Ark_Tag tag;
    Ark_BarGridColumnOptions value;
} Opt_BarGridColumnOptions;
typedef struct Ark_ScrollableBarModeOptions {
    Opt_Length margin;
    Opt_LayoutStyle nonScrollableLayoutStyle;
} Ark_ScrollableBarModeOptions;
typedef struct Opt_ScrollableBarModeOptions {
    enum Ark_Tag tag;
    Ark_ScrollableBarModeOptions value;
} Opt_ScrollableBarModeOptions;
typedef Ark_Int32 Ark_BarMode;
typedef struct Opt_BarMode {
    enum Ark_Tag tag;
    Ark_BarMode value;
} Opt_BarMode;
typedef struct Literal_Opt_BarPosition_barPosition_Opt_Number_index_Opt_TabsController_controller {
    Opt_BarPosition barPosition;
    Opt_Number index;
    Opt_TabsController controller;
} Literal_Opt_BarPosition_barPosition_Opt_Number_index_Opt_TabsController_controller;
typedef struct Opt_Literal_Opt_BarPosition_barPosition_Opt_Number_index_Opt_TabsController_controller {
    enum Ark_Tag tag;
    Literal_Opt_BarPosition_barPosition_Opt_Number_index_Opt_TabsController_controller value;
} Opt_Literal_Opt_BarPosition_barPosition_Opt_Number_index_Opt_TabsController_controller;
typedef struct Ark_SymbolEffect {
    void *handle;
} Ark_SymbolEffect;
typedef struct Opt_SymbolEffect {
    enum Ark_Tag tag;
    Ark_SymbolEffect value;
} Opt_SymbolEffect;
typedef struct Ark_SwiperContentAnimatedTransition {
    Opt_Number timeout;
    struct Ark_Function transition;
} Ark_SwiperContentAnimatedTransition;
typedef struct Opt_SwiperContentAnimatedTransition {
    enum Ark_Tag tag;
    Ark_SwiperContentAnimatedTransition value;
} Opt_SwiperContentAnimatedTransition;
typedef Ark_Int32 Ark_SwiperNestedScrollMode;
typedef struct Opt_SwiperNestedScrollMode {
    enum Ark_Tag tag;
    Ark_SwiperNestedScrollMode value;
} Opt_SwiperNestedScrollMode;
typedef struct Union_Number_String_Ark_SwiperAutoFill {
    Ark_Int32 selector;
    union {
        Ark_Number value0;
        Ark_String value1;
        struct Ark_SwiperAutoFill value2;
    };
} Union_Number_String_Ark_SwiperAutoFill;
typedef struct Opt_Union_Number_String_SwiperAutoFill {
    enum Ark_Tag tag;
    Union_Number_String_Ark_SwiperAutoFill value;
} Opt_Union_Number_String_SwiperAutoFill;
typedef Ark_Int32 Ark_SwiperDisplayMode;
typedef struct Opt_SwiperDisplayMode {
    enum Ark_Tag tag;
    Ark_SwiperDisplayMode value;
} Opt_SwiperDisplayMode;
typedef struct Union_ArrowStyle_Boolean {
    Ark_Int32 selector;
    union {
        struct Ark_ArrowStyle value0;
        Ark_Boolean value1;
    };
} Union_ArrowStyle_Boolean;
typedef struct Opt_Union_ArrowStyle_Boolean {
    enum Ark_Tag tag;
    Union_ArrowStyle_Boolean value;
} Opt_Union_ArrowStyle_Boolean;
typedef struct Union_DotIndicator_DigitIndicator_Boolean {
    Ark_Int32 selector;
    union {
        struct Ark_DotIndicator value0;
        struct Ark_DigitIndicator value1;
        Ark_Boolean value2;
    };
} Union_DotIndicator_DigitIndicator_Boolean;
typedef struct Opt_Union_DotIndicator_DigitIndicator_Boolean {
    enum Ark_Tag tag;
    Union_DotIndicator_DigitIndicator_Boolean value;
} Opt_Union_DotIndicator_DigitIndicator_Boolean;
typedef Ark_Materialized Ark_SwiperController;
typedef struct Opt_SwiperController {
    enum Ark_Tag tag;
    Ark_SwiperController value;
} Opt_SwiperController;
typedef Ark_Int32 Ark_ItemState;
typedef struct Opt_ItemState {
    enum Ark_Tag tag;
    Ark_ItemState value;
} Opt_ItemState;
typedef struct Literal_Opt_Number_index {
    Opt_Number index;
} Literal_Opt_Number_index;
typedef struct Opt_Literal_Opt_Number_index {
    enum Ark_Tag tag;
    Literal_Opt_Number_index value;
} Opt_Literal_Opt_Number_index;
typedef struct Ark_StackOptions {
    Opt_Alignment alignContent;
} Ark_StackOptions;
typedef struct Opt_StackOptions {
    enum Ark_Tag tag;
    Ark_StackOptions value;
} Opt_StackOptions;
typedef Ark_Int32 Ark_TextCase;
typedef struct Opt_TextCase {
    enum Ark_Tag tag;
    Ark_TextCase value;
} Opt_TextCase;
typedef struct Ark_SlideRange {
    Opt_Number from;
    Opt_Number to;
} Ark_SlideRange;
typedef struct Opt_SlideRange {
    enum Ark_Tag tag;
    Ark_SlideRange value;
} Opt_SlideRange;
typedef Ark_Int32 Ark_SliderInteraction;
typedef struct Opt_SliderInteraction {
    enum Ark_Tag tag;
    Ark_SliderInteraction value;
} Opt_SliderInteraction;
typedef struct Ark_SliderBlockStyle {
    Ark_SliderBlockType type;
    struct Opt_ResourceStr image;
    struct Opt_Union_CircleAttribute_EllipseAttribute_PathAttribute_RectAttribute shape;
} Ark_SliderBlockStyle;
typedef struct Opt_SliderBlockStyle {
    enum Ark_Tag tag;
    Ark_SliderBlockStyle value;
} Opt_SliderBlockStyle;
typedef struct Ark_SliderOptions {
    Opt_Number value;
    Opt_Number min;
    Opt_Number max;
    Opt_Number step;
    Opt_SliderStyle style;
    Opt_Axis direction;
    Opt_Boolean reverse;
} Ark_SliderOptions;
typedef struct Opt_SliderOptions {
    enum Ark_Tag tag;
    Ark_SliderOptions value;
} Opt_SliderOptions;
typedef struct Literal_Opt_Union_Number_String_x_y_width_height {
    struct Opt_Union_Number_String x;
    struct Opt_Union_Number_String y;
    struct Opt_Union_Number_String width;
    struct Opt_Union_Number_String height;
} Literal_Opt_Union_Number_String_x_y_width_height;
typedef struct Opt_Literal_Opt_Union_Number_String_x_y_width_height {
    enum Ark_Tag tag;
    Literal_Opt_Union_Number_String_x_y_width_height value;
} Opt_Literal_Opt_Union_Number_String_x_y_width_height;
typedef struct Union_Opt_DividerOptions_Ark_Undefined {
    Ark_Int32 selector;
    union {
        struct Opt_DividerOptions value0;
        struct Ark_Undefined value1;
    };
} Union_Opt_DividerOptions_Ark_Undefined;
typedef struct Opt_Union_Opt_DividerOptions_Undefined {
    enum Ark_Tag tag;
    Union_Opt_DividerOptions_Ark_Undefined value;
} Opt_Union_Opt_DividerOptions_Undefined;
typedef struct Union_Length_OptionWidthMode {
    Ark_Int32 selector;
    union {
        Ark_Length value0;
        Ark_OptionWidthMode value1;
    };
} Union_Length_OptionWidthMode;
typedef struct Opt_Union_Length_OptionWidthMode {
    enum Ark_Tag tag;
    Union_Length_OptionWidthMode value;
} Opt_Union_Length_OptionWidthMode;
typedef Ark_Int32 Ark_MenuAlignType;
typedef struct Opt_MenuAlignType {
    enum Ark_Tag tag;
    Ark_MenuAlignType value;
} Opt_MenuAlignType;
typedef Ark_Int32 Ark_ArrowPosition;
typedef struct Opt_ArrowPosition {
    enum Ark_Tag tag;
    Ark_ArrowPosition value;
} Opt_ArrowPosition;
typedef struct Ark_SelectOption {
    struct Ark_ResourceStr value;
    struct Opt_ResourceStr icon;
    Opt_CustomObject symbolIcon;
} Ark_SelectOption;
typedef struct Opt_SelectOption {
    enum Ark_Tag tag;
    Ark_SelectOption value;
} Opt_SelectOption;
typedef struct Array_SelectOption {
    struct Ark_SelectOption* array;
    Ark_Int32 length;
} Array_SelectOption;
typedef struct Opt_Array_SelectOption {
    enum Ark_Tag tag;
    Array_SelectOption value;
} Opt_Array_SelectOption;
typedef Ark_Int32 Ark_SearchType;
typedef struct Opt_SearchType {
    enum Ark_Tag tag;
    Ark_SearchType value;
} Opt_SearchType;
typedef struct Ark_TextDecorationOptions {
    Ark_TextDecorationType type;
    struct Opt_ResourceColor color;
    Opt_TextDecorationStyle style;
} Ark_TextDecorationOptions;
typedef struct Opt_TextDecorationOptions {
    enum Ark_Tag tag;
    Ark_TextDecorationOptions value;
} Opt_TextDecorationOptions;
typedef struct Ark_CaretStyle {
    Opt_Length width;
    struct Opt_ResourceColor color;
} Ark_CaretStyle;
typedef struct Opt_CaretStyle {
    enum Ark_Tag tag;
    Ark_CaretStyle value;
} Opt_CaretStyle;
typedef struct Union_CancelButtonOptions_CancelButtonSymbolOptions {
    Ark_Int32 selector;
    union {
        struct Ark_CancelButtonOptions value0;
        struct Ark_CancelButtonSymbolOptions value1;
    };
} Union_CancelButtonOptions_CancelButtonSymbolOptions;
typedef struct Opt_Union_CancelButtonOptions_CancelButtonSymbolOptions {
    enum Ark_Tag tag;
    Union_CancelButtonOptions_CancelButtonSymbolOptions value;
} Opt_Union_CancelButtonOptions_CancelButtonSymbolOptions;
typedef struct Union_IconOptions_CustomObject {
    Ark_Int32 selector;
    union {
        struct Ark_IconOptions value0;
        Ark_CustomObject value1;
    };
} Union_IconOptions_CustomObject;
typedef struct Opt_Union_IconOptions_CustomObject {
    enum Ark_Tag tag;
    Union_IconOptions_CustomObject value;
} Opt_Union_IconOptions_CustomObject;
typedef struct Ark_SearchButtonOptions {
    Opt_Length fontSize;
    struct Opt_ResourceColor fontColor;
} Ark_SearchButtonOptions;
typedef struct Opt_SearchButtonOptions {
    enum Ark_Tag tag;
    Ark_SearchButtonOptions value;
} Opt_SearchButtonOptions;
typedef struct Literal_Opt_String_value_icon_Ark_ResourceStr_placeholder_Opt_SearchController_controller {
    Opt_String value;
    struct Opt_ResourceStr placeholder;
    Opt_String icon;
    Opt_SearchController controller;
} Literal_Opt_String_value_icon_Ark_ResourceStr_placeholder_Opt_SearchController_controller;
typedef struct Opt_Literal_Opt_String_value_icon_ResourceStr_placeholder_Opt_SearchController_controller {
    enum Ark_Tag tag;
    Literal_Opt_String_value_icon_Ark_ResourceStr_placeholder_Opt_SearchController_controller value;
} Opt_Literal_Opt_String_value_icon_ResourceStr_placeholder_Opt_SearchController_controller;
typedef struct Ark_ScrollBarOptions {
    Ark_Scroller scroller;
    Opt_ScrollBarDirection direction;
    Opt_BarState state;
} Ark_ScrollBarOptions;
typedef struct Opt_ScrollBarOptions {
    enum Ark_Tag tag;
    Ark_ScrollBarOptions value;
} Opt_ScrollBarOptions;
typedef struct Ark_OffsetOptions {
    Opt_Length xOffset;
    Opt_Length yOffset;
} Ark_OffsetOptions;
typedef struct Opt_OffsetOptions {
    enum Ark_Tag tag;
    Ark_OffsetOptions value;
} Opt_OffsetOptions;
typedef struct Ark_ScrollSnapOptions {
    Ark_ScrollSnapAlign snapAlign;
    struct Opt_Union_Length_Array_Length snapPagination;
    Opt_Boolean enableSnapToStart;
    Opt_Boolean enableSnapToEnd;
} Ark_ScrollSnapOptions;
typedef struct Opt_ScrollSnapOptions {
    enum Ark_Tag tag;
    Ark_ScrollSnapOptions value;
} Opt_ScrollSnapOptions;
typedef struct Union_Color_Number_String {
    Ark_Int32 selector;
    union {
        Ark_Color value0;
        Ark_Number value1;
        Ark_String value2;
    };
} Union_Color_Number_String;
typedef struct Opt_Union_Color_Number_String {
    enum Ark_Tag tag;
    Union_Color_Number_String value;
} Opt_Union_Color_Number_String;
typedef Ark_Int32 Ark_ScrollDirection;
typedef struct Opt_ScrollDirection {
    enum Ark_Tag tag;
    Ark_ScrollDirection value;
} Opt_ScrollDirection;
typedef struct Ark_SaveButtonOptions {
    Opt_SaveIconStyle icon;
    Opt_SaveDescription text;
    Opt_ButtonType buttonType;
} Ark_SaveButtonOptions;
typedef struct Opt_SaveButtonOptions {
    enum Ark_Tag tag;
    Ark_SaveButtonOptions value;
} Opt_SaveButtonOptions;
typedef struct Ark_RowOptions {
    struct Opt_Union_String_Number space;
} Ark_RowOptions;
typedef struct Opt_RowOptions {
    enum Ark_Tag tag;
    Ark_RowOptions value;
} Opt_RowOptions;
typedef struct Ark_RootSceneSession {
    void *handle;
} Ark_RootSceneSession;
typedef struct Opt_RootSceneSession {
    enum Ark_Tag tag;
    Ark_RootSceneSession value;
} Opt_RootSceneSession;
typedef Ark_Materialized Ark_EditMenuOptions;
typedef struct Opt_EditMenuOptions {
    enum Ark_Tag tag;
    Ark_EditMenuOptions value;
} Opt_EditMenuOptions;
typedef Ark_Int32 Ark_EnterKeyType;
typedef struct Opt_EnterKeyType {
    enum Ark_Tag tag;
    Ark_EnterKeyType value;
} Opt_EnterKeyType;
typedef struct Ark_PlaceholderStyle {
    struct Opt_Font font;
    struct Opt_ResourceColor fontColor;
} Ark_PlaceholderStyle;
typedef struct Opt_PlaceholderStyle {
    enum Ark_Tag tag;
    Ark_PlaceholderStyle value;
} Opt_PlaceholderStyle;
typedef Ark_Int32 Ark_TextDataDetectorType;
typedef struct Opt_TextDataDetectorType {
    enum Ark_Tag tag;
    Ark_TextDataDetectorType value;
} Opt_TextDataDetectorType;
typedef struct Ark_TextDataDetectorConfig {
    struct Array_TextDataDetectorType types;
    struct Opt_Function onDetectResultUpdate;
    struct Opt_ResourceColor color;
    struct Opt_DecorationStyleInterface decoration;
} Ark_TextDataDetectorConfig;
typedef struct Opt_TextDataDetectorConfig {
    enum Ark_Tag tag;
    Ark_TextDataDetectorConfig value;
} Opt_TextDataDetectorConfig;
typedef struct Ark_KeyboardOptions {
    Opt_Boolean supportAvoidance;
} Ark_KeyboardOptions;
typedef struct Opt_KeyboardOptions {
    enum Ark_Tag tag;
    Ark_KeyboardOptions value;
} Opt_KeyboardOptions;
typedef struct Ark_SelectionMenuOptions {
    struct Opt_Function onAppear;
    struct Opt_Function onDisappear;
} Ark_SelectionMenuOptions;
typedef struct Opt_SelectionMenuOptions {
    enum Ark_Tag tag;
    Ark_SelectionMenuOptions value;
} Opt_SelectionMenuOptions;
typedef struct Union_ResponseType_RichEditorResponseType {
    Ark_Int32 selector;
    union {
        Ark_ResponseType value0;
        Ark_RichEditorResponseType value1;
    };
} Union_ResponseType_RichEditorResponseType;
typedef struct Opt_Union_ResponseType_RichEditorResponseType {
    enum Ark_Tag tag;
    Union_ResponseType_RichEditorResponseType value;
} Opt_Union_ResponseType_RichEditorResponseType;
typedef Ark_Int32 Ark_RichEditorSpanType;
typedef struct Opt_RichEditorSpanType {
    enum Ark_Tag tag;
    Ark_RichEditorSpanType value;
} Opt_RichEditorSpanType;
typedef struct Ark_RichEditorStyledStringOptions {
    Ark_RichEditorStyledStringController controller;
} Ark_RichEditorStyledStringOptions;
typedef struct Opt_RichEditorStyledStringOptions {
    enum Ark_Tag tag;
    Ark_RichEditorStyledStringOptions value;
} Opt_RichEditorStyledStringOptions;
typedef struct Ark_RichEditorOptions {
    Ark_RichEditorController controller;
} Ark_RichEditorOptions;
typedef struct Opt_RichEditorOptions {
    enum Ark_Tag tag;
    Ark_RichEditorOptions value;
} Opt_RichEditorOptions;
typedef struct Ark_LocalizedBarrierStyle {
    Ark_String id;
    Ark_LocalizedBarrierDirection localizedDirection;
    struct Array_String referencedId;
} Ark_LocalizedBarrierStyle;
typedef struct Opt_LocalizedBarrierStyle {
    enum Ark_Tag tag;
    Ark_LocalizedBarrierStyle value;
} Opt_LocalizedBarrierStyle;
typedef struct Array_LocalizedBarrierStyle {
    struct Ark_LocalizedBarrierStyle* array;
    Ark_Int32 length;
} Array_LocalizedBarrierStyle;
typedef struct Opt_Array_LocalizedBarrierStyle {
    enum Ark_Tag tag;
    Array_LocalizedBarrierStyle value;
} Opt_Array_LocalizedBarrierStyle;
typedef struct Ark_BarrierStyle {
    Ark_String id;
    Ark_BarrierDirection direction;
    struct Array_String referencedId;
} Ark_BarrierStyle;
typedef struct Opt_BarrierStyle {
    enum Ark_Tag tag;
    Ark_BarrierStyle value;
} Opt_BarrierStyle;
typedef struct Array_BarrierStyle {
    struct Ark_BarrierStyle* array;
    Ark_Int32 length;
} Array_BarrierStyle;
typedef struct Opt_Array_BarrierStyle {
    enum Ark_Tag tag;
    Array_BarrierStyle value;
} Opt_Array_BarrierStyle;
typedef struct Ark_GuideLineStyle {
    Ark_String id;
    Ark_Axis direction;
    struct Ark_GuideLinePosition position;
} Ark_GuideLineStyle;
typedef struct Opt_GuideLineStyle {
    enum Ark_Tag tag;
    Ark_GuideLineStyle value;
} Opt_GuideLineStyle;
typedef struct Array_GuideLineStyle {
    struct Ark_GuideLineStyle* array;
    Ark_Int32 length;
} Array_GuideLineStyle;
typedef struct Opt_Array_GuideLineStyle {
    enum Ark_Tag tag;
    Array_GuideLineStyle value;
} Opt_Array_GuideLineStyle;
typedef struct Ark_RefreshOptions {
    Ark_Boolean refreshing;
    struct Opt_Union_Number_String offset;
    struct Opt_Union_Number_String friction;
    struct Opt_ResourceStr promptText;
    struct Opt_CustomBuilder builder;
    Opt_CustomObject refreshingContent;
} Ark_RefreshOptions;
typedef struct Opt_RefreshOptions {
    enum Ark_Tag tag;
    Ark_RefreshOptions value;
} Opt_RefreshOptions;
typedef struct Union_Literal_Opt_Union_Number_String_width_height_Opt_Union_Number_String_Array_CustomObject_radius_Literal_Opt_Union_Number_String_width_height_radiusWidth_radiusHeight {
    Ark_Int32 selector;
    union {
        struct Literal_Opt_Union_Number_String_width_height_Opt_Union_Number_String_Array_CustomObject_radius value0;
        struct Literal_Opt_Union_Number_String_width_height_radiusWidth_radiusHeight value1;
    };
} Union_Literal_Opt_Union_Number_String_width_height_Opt_Union_Number_String_Array_CustomObject_radius_Literal_Opt_Union_Number_String_width_height_radiusWidth_radiusHeight;
typedef struct Opt_Union_Literal_Opt_Union_Number_String_width_height_Opt_Union_Number_String_Array_CustomObject_radius_Literal_Opt_Union_Number_String_width_height_radiusWidth_radiusHeight {
    enum Ark_Tag tag;
    Union_Literal_Opt_Union_Number_String_width_height_Opt_Union_Number_String_Array_CustomObject_radius_Literal_Opt_Union_Number_String_width_height_radiusWidth_radiusHeight value;
} Opt_Union_Literal_Opt_Union_Number_String_width_height_Opt_Union_Number_String_Array_CustomObject_radius_Literal_Opt_Union_Number_String_width_height_radiusWidth_radiusHeight;
typedef struct Ark_StarStyleOptions {
    Ark_String backgroundUri;
    Ark_String foregroundUri;
    Opt_String secondaryUri;
} Ark_StarStyleOptions;
typedef struct Opt_StarStyleOptions {
    enum Ark_Tag tag;
    Ark_StarStyleOptions value;
} Opt_StarStyleOptions;
typedef struct Ark_RatingOptions {
    Ark_Number rating;
    Opt_Boolean indicator;
} Ark_RatingOptions;
typedef struct Opt_RatingOptions {
    enum Ark_Tag tag;
    Ark_RatingOptions value;
} Opt_RatingOptions;
typedef struct Ark_RadioStyle {
    struct Opt_ResourceColor checkedBackgroundColor;
    struct Opt_ResourceColor uncheckedBorderColor;
    struct Opt_ResourceColor indicatorColor;
} Ark_RadioStyle;
typedef struct Opt_RadioStyle {
    enum Ark_Tag tag;
    Ark_RadioStyle value;
} Opt_RadioStyle;
typedef struct Ark_RadioOptions {
    Ark_String group;
    Ark_String value;
    Opt_RadioIndicatorType indicatorType;
    struct Opt_CustomBuilder indicatorBuilder;
} Ark_RadioOptions;
typedef struct Opt_RadioOptions {
    enum Ark_Tag tag;
    Ark_RadioOptions value;
} Opt_RadioOptions;
typedef struct Literal_Opt_Union_String_Number_width_height {
    struct Opt_Union_String_Number width;
    struct Opt_Union_String_Number height;
} Literal_Opt_Union_String_Number_width_height;
typedef struct Opt_Literal_Opt_Union_String_Number_width_height {
    enum Ark_Tag tag;
    Literal_Opt_Union_String_Number_width_height value;
} Opt_Literal_Opt_Union_String_Number_width_height;
typedef struct Literal_PluginComponentTemplate_template_CustomObject_data {
    struct Ark_PluginComponentTemplate template_;
    Ark_CustomObject data;
} Literal_PluginComponentTemplate_template_CustomObject_data;
typedef struct Opt_Literal_PluginComponentTemplate_template_CustomObject_data {
    enum Ark_Tag tag;
    Literal_PluginComponentTemplate_template_CustomObject_data value;
} Opt_Literal_PluginComponentTemplate_template_CustomObject_data;
typedef Ark_Materialized Ark_PatternLockController;
typedef struct Opt_PatternLockController {
    enum Ark_Tag tag;
    Ark_PatternLockController value;
} Opt_PatternLockController;
typedef struct Literal_Opt_Union_Number_String_width_height_Opt_String_commands {
    struct Opt_Union_Number_String width;
    struct Opt_Union_Number_String height;
    Opt_String commands;
} Literal_Opt_Union_Number_String_width_height_Opt_String_commands;
typedef struct Opt_Literal_Opt_Union_Number_String_width_height_Opt_String_commands {
    enum Ark_Tag tag;
    Literal_Opt_Union_Number_String_width_height_Opt_String_commands value;
} Opt_Literal_Opt_Union_Number_String_width_height_Opt_String_commands;
typedef struct Ark_PasteButtonOptions {
    Opt_PasteIconStyle icon;
    Opt_PasteDescription text;
    Opt_ButtonType buttonType;
} Ark_PasteButtonOptions;
typedef struct Opt_PasteButtonOptions {
    enum Ark_Tag tag;
    Ark_PasteButtonOptions value;
} Opt_PasteButtonOptions;
typedef struct Union_Length_PanelHeight {
    Ark_Int32 selector;
    union {
        Ark_Length value0;
        Ark_PanelHeight value1;
    };
} Union_Length_PanelHeight;
typedef struct Opt_Union_Length_PanelHeight {
    enum Ark_Tag tag;
    Union_Length_PanelHeight value;
} Opt_Union_Length_PanelHeight;
typedef Ark_Int32 Ark_PanelType;
typedef struct Opt_PanelType {
    enum Ark_Tag tag;
    Ark_PanelType value;
} Opt_PanelType;
typedef Ark_Int32 Ark_PanelMode;
typedef struct Opt_PanelMode {
    enum Ark_Tag tag;
    Ark_PanelMode value;
} Opt_PanelMode;
typedef struct Literal_String_target_Opt_NavigationType_type {
    Ark_String target;
    Opt_NavigationType type;
} Literal_String_target_Opt_NavigationType_type;
typedef struct Opt_Literal_String_target_Opt_NavigationType_type {
    enum Ark_Tag tag;
    Literal_String_target_Opt_NavigationType_type value;
} Opt_Literal_String_target_Opt_NavigationType_type;
typedef int32_t Ark_LayoutSafeAreaEdge;
typedef struct Array_LayoutSafeAreaEdge {
    Ark_LayoutSafeAreaEdge* array;
    Ark_Int32 length;
} Array_LayoutSafeAreaEdge;
typedef int32_t Ark_LayoutSafeAreaEdge;
typedef struct Opt_Array_LayoutSafeAreaEdge {
    enum Ark_Tag tag;
    Array_LayoutSafeAreaEdge value;
} Opt_Array_LayoutSafeAreaEdge;
typedef int32_t Ark_LayoutSafeAreaType;
typedef struct Array_LayoutSafeAreaType {
    Ark_LayoutSafeAreaType* array;
    Ark_Int32 length;
} Array_LayoutSafeAreaType;
typedef int32_t Ark_LayoutSafeAreaType;
typedef struct Opt_Array_LayoutSafeAreaType {
    enum Ark_Tag tag;
    Array_LayoutSafeAreaType value;
} Opt_Array_LayoutSafeAreaType;
typedef struct Ark_NavigationToolbarOptions {
    struct Opt_ResourceColor backgroundColor;
    Opt_BlurStyle backgroundBlurStyle;
} Ark_NavigationToolbarOptions;
typedef struct Opt_NavigationToolbarOptions {
    enum Ark_Tag tag;
    Ark_NavigationToolbarOptions value;
} Opt_NavigationToolbarOptions;
typedef struct Ark_ToolbarItem {
    struct Ark_ResourceStr value;
    struct Opt_ResourceStr icon;
    Opt_CustomObject symbolIcon;
    struct Opt_Function action;
    Opt_ToolbarItemStatus status;
    struct Opt_ResourceStr activeIcon;
    Opt_CustomObject activeSymbolIcon;
} Ark_ToolbarItem;
typedef struct Opt_ToolbarItem {
    enum Ark_Tag tag;
    Ark_ToolbarItem value;
} Opt_ToolbarItem;
typedef struct Union_Array_ToolbarItem_Ark_CustomBuilder {
    Ark_Int32 selector;
    union {
        struct Array_ToolbarItem value0;
        struct Ark_CustomBuilder value1;
    };
} Union_Array_ToolbarItem_Ark_CustomBuilder;
typedef struct Opt_Union_Array_ToolbarItem_CustomBuilder {
    enum Ark_Tag tag;
    Union_Array_ToolbarItem_Ark_CustomBuilder value;
} Opt_Union_Array_ToolbarItem_CustomBuilder;
typedef struct Union_CustomObject_Ark_CustomBuilder {
    Ark_Int32 selector;
    union {
        Ark_CustomObject value0;
        struct Ark_CustomBuilder value1;
    };
} Union_CustomObject_Ark_CustomBuilder;
typedef struct Opt_Union_CustomObject_CustomBuilder {
    enum Ark_Tag tag;
    Union_CustomObject_Ark_CustomBuilder value;
} Opt_Union_CustomObject_CustomBuilder;
typedef struct Union_Array_NavigationMenuItem_Ark_CustomBuilder {
    Ark_Int32 selector;
    union {
        struct Array_NavigationMenuItem value0;
        struct Ark_CustomBuilder value1;
    };
} Union_Array_NavigationMenuItem_Ark_CustomBuilder;
typedef struct Opt_Union_Array_NavigationMenuItem_CustomBuilder {
    enum Ark_Tag tag;
    Union_Array_NavigationMenuItem_Ark_CustomBuilder value;
} Opt_Union_Array_NavigationMenuItem_CustomBuilder;
typedef Ark_Int32 Ark_NavigationTitleMode;
typedef struct Opt_NavigationTitleMode {
    enum Ark_Tag tag;
    Ark_NavigationTitleMode value;
} Opt_NavigationTitleMode;
typedef struct Union_Ark_ResourceStr_Ark_CustomBuilder_NavigationCommonTitle_NavigationCustomTitle {
    Ark_Int32 selector;
    union {
        struct Ark_ResourceStr value0;
        struct Ark_CustomBuilder value1;
        struct Ark_NavigationCommonTitle value2;
        struct Ark_NavigationCustomTitle value3;
    };
} Union_Ark_ResourceStr_Ark_CustomBuilder_NavigationCommonTitle_NavigationCustomTitle;
typedef struct Opt_Union_ResourceStr_Ark_CustomBuilder_NavigationCommonTitle_NavigationCustomTitle {
    enum Ark_Tag tag;
    Union_Ark_ResourceStr_Ark_CustomBuilder_NavigationCommonTitle_NavigationCustomTitle value;
} Opt_Union_ResourceStr_Ark_CustomBuilder_NavigationCommonTitle_NavigationCustomTitle;
typedef struct Union_String_CustomObject_Resource_CustomObject {
    Ark_Int32 selector;
    union {
        Ark_String value0;
        Ark_CustomObject value1;
        struct Ark_Resource value2;
        Ark_CustomObject value3;
    };
} Union_String_CustomObject_Resource_CustomObject;
typedef struct Opt_Union_String_CustomObject_Resource_CustomObject {
    enum Ark_Tag tag;
    Union_String_CustomObject_Resource_CustomObject value;
} Opt_Union_String_CustomObject_Resource_CustomObject;
typedef Ark_Int32 Ark_NavigationMode;
typedef struct Opt_NavigationMode {
    enum Ark_Tag tag;
    Ark_NavigationMode value;
} Opt_NavigationMode;
typedef Ark_Int32 Ark_NavBarPosition;
typedef struct Opt_NavBarPosition {
    enum Ark_Tag tag;
    Ark_NavBarPosition value;
} Opt_NavBarPosition;
typedef Ark_Materialized Ark_NavPathStack;
typedef struct Opt_NavPathStack {
    enum Ark_Tag tag;
    Ark_NavPathStack value;
} Opt_NavPathStack;
typedef Ark_Int32 Ark_NavRouteMode;
typedef struct Opt_NavRouteMode {
    enum Ark_Tag tag;
    Ark_NavRouteMode value;
} Opt_NavRouteMode;
typedef struct Ark_RouteInfo {
    Ark_String name;
    Opt_CustomObject param;
} Ark_RouteInfo;
typedef struct Opt_RouteInfo {
    enum Ark_Tag tag;
    Ark_RouteInfo value;
} Opt_RouteInfo;
typedef Ark_Int32 Ark_LayoutSafeAreaEdge;
typedef struct Opt_LayoutSafeAreaEdge {
    enum Ark_Tag tag;
    Ark_LayoutSafeAreaEdge value;
} Opt_LayoutSafeAreaEdge;
typedef Ark_Int32 Ark_LayoutSafeAreaType;
typedef struct Opt_LayoutSafeAreaType {
    enum Ark_Tag tag;
    Ark_LayoutSafeAreaType value;
} Opt_LayoutSafeAreaType;
typedef struct Ark_NavigationMenuItem {
    Ark_String value;
    Opt_String icon;
    Opt_CustomObject symbolIcon;
    Opt_Boolean isEnabled;
    struct Opt_Function action;
} Ark_NavigationMenuItem;
typedef struct Opt_NavigationMenuItem {
    enum Ark_Tag tag;
    Ark_NavigationMenuItem value;
} Opt_NavigationMenuItem;
typedef struct Union_Ark_ResourceStr_CustomObject_CustomObject {
    Ark_Int32 selector;
    union {
        struct Ark_ResourceStr value0;
        Ark_CustomObject value1;
        Ark_CustomObject value2;
    };
} Union_Ark_ResourceStr_CustomObject_CustomObject;
typedef struct Opt_Union_ResourceStr_CustomObject_CustomObject {
    enum Ark_Tag tag;
    Union_Ark_ResourceStr_CustomObject_CustomObject value;
} Opt_Union_ResourceStr_CustomObject_CustomObject;
typedef struct Ark_NavigationTitleOptions {
    struct Opt_ResourceColor backgroundColor;
    Opt_BlurStyle backgroundBlurStyle;
    Opt_BarStyle barStyle;
    Opt_CustomObject paddingStart;
    Opt_CustomObject paddingEnd;
    Opt_CustomObject mainTitleModifier;
    Opt_CustomObject subTitleModifier;
} Ark_NavigationTitleOptions;
typedef struct Opt_NavigationTitleOptions {
    enum Ark_Tag tag;
    Ark_NavigationTitleOptions value;
} Opt_NavigationTitleOptions;
typedef struct Union_String_Ark_CustomBuilder_NavDestinationCommonTitle_NavDestinationCustomTitle {
    Ark_Int32 selector;
    union {
        Ark_String value0;
        struct Ark_CustomBuilder value1;
        struct Ark_NavDestinationCommonTitle value2;
        struct Ark_NavDestinationCustomTitle value3;
    };
} Union_String_Ark_CustomBuilder_NavDestinationCommonTitle_NavDestinationCustomTitle;
typedef struct Opt_Union_String_CustomBuilder_NavDestinationCommonTitle_NavDestinationCustomTitle {
    enum Ark_Tag tag;
    Union_String_Ark_CustomBuilder_NavDestinationCommonTitle_NavDestinationCustomTitle value;
} Opt_Union_String_CustomBuilder_NavDestinationCommonTitle_NavDestinationCustomTitle;
typedef struct Ark_MenuItemGroupOptions {
    struct Opt_Union_ResourceStr_Ark_CustomBuilder header;
    struct Opt_Union_ResourceStr_Ark_CustomBuilder footer;
} Ark_MenuItemGroupOptions;
typedef struct Opt_MenuItemGroupOptions {
    enum Ark_Tag tag;
    Ark_MenuItemGroupOptions value;
} Opt_MenuItemGroupOptions;
typedef struct Union_Boolean_Ark_ResourceStr_CustomObject {
    Ark_Int32 selector;
    union {
        Ark_Boolean value0;
        struct Ark_ResourceStr value1;
        Ark_CustomObject value2;
    };
} Union_Boolean_Ark_ResourceStr_CustomObject;
typedef struct Opt_Union_Boolean_ResourceStr_CustomObject {
    enum Ark_Tag tag;
    Union_Boolean_Ark_ResourceStr_CustomObject value;
} Opt_Union_Boolean_ResourceStr_CustomObject;
typedef struct Union_MenuItemOptions_Ark_CustomBuilder {
    Ark_Int32 selector;
    union {
        struct Ark_MenuItemOptions value0;
        struct Ark_CustomBuilder value1;
    };
} Union_MenuItemOptions_Ark_CustomBuilder;
typedef struct Opt_Union_MenuItemOptions_CustomBuilder {
    enum Ark_Tag tag;
    Union_MenuItemOptions_Ark_CustomBuilder value;
} Opt_Union_MenuItemOptions_CustomBuilder;
typedef Ark_Int32 Ark_SubMenuExpandingMode;
typedef struct Opt_SubMenuExpandingMode {
    enum Ark_Tag tag;
    Ark_SubMenuExpandingMode value;
} Opt_SubMenuExpandingMode;
typedef struct Union_DividerStyleOptions_Undefined {
    Ark_Int32 selector;
    union {
        struct Ark_DividerStyleOptions value0;
        Ark_Undefined value1;
    };
} Union_DividerStyleOptions_Undefined;
typedef struct Opt_Union_DividerStyleOptions_Undefined {
    enum Ark_Tag tag;
    Union_DividerStyleOptions_Undefined value;
} Opt_Union_DividerStyleOptions_Undefined;
typedef struct Union_CustomObject_Ark_ResourceStr_CustomObject_ASTCResource {
    Ark_Int32 selector;
    union {
        Ark_CustomObject value0;
        struct Ark_ResourceStr value1;
        Ark_CustomObject value2;
        struct Ark_ASTCResource value3;
    };
} Union_CustomObject_Ark_ResourceStr_CustomObject_ASTCResource;
typedef struct Opt_Union_CustomObject_ResourceStr_CustomObject_ASTCResource {
    enum Ark_Tag tag;
    Union_CustomObject_Ark_ResourceStr_CustomObject_ASTCResource value;
} Opt_Union_CustomObject_ResourceStr_CustomObject_ASTCResource;
typedef Ark_Int32 Ark_MarqueeUpdateStrategy;
typedef struct Opt_MarqueeUpdateStrategy {
    enum Ark_Tag tag;
    Ark_MarqueeUpdateStrategy value;
} Opt_MarqueeUpdateStrategy;
typedef struct Literal_Boolean_start_Opt_Number_step_loop_Opt_Boolean_fromStart_String_src {
    Ark_Boolean start;
    Opt_Number step;
    Opt_Number loop;
    Opt_Boolean fromStart;
    Ark_String src;
} Literal_Boolean_start_Opt_Number_step_loop_Opt_Boolean_fromStart_String_src;
typedef struct Opt_Literal_Boolean_start_Opt_Number_step_loop_Opt_Boolean_fromStart_String_src {
    enum Ark_Tag tag;
    Literal_Boolean_start_Opt_Number_step_loop_Opt_Boolean_fromStart_String_src value;
} Opt_Literal_Boolean_start_Opt_Number_step_loop_Opt_Boolean_fromStart_String_src;
typedef struct Ark_LocationButtonOptions {
    Opt_LocationIconStyle icon;
    Opt_LocationDescription text;
    Opt_ButtonType buttonType;
} Ark_LocationButtonOptions;
typedef struct Opt_LocationButtonOptions {
    enum Ark_Tag tag;
    Ark_LocationButtonOptions value;
} Opt_LocationButtonOptions;
typedef struct Union_Position_Edges_LocalizedEdges {
    Ark_Int32 selector;
    union {
        struct Ark_Position value0;
        struct Ark_Edges value1;
        struct Ark_LocalizedEdges value2;
    };
} Union_Position_Edges_LocalizedEdges;
typedef struct Opt_Union_Position_Edges_LocalizedEdges {
    enum Ark_Tag tag;
    Union_Position_Edges_LocalizedEdges value;
} Opt_Union_Position_Edges_LocalizedEdges;
typedef Ark_Int32 Ark_SecurityComponentLayoutDirection;
typedef struct Opt_SecurityComponentLayoutDirection {
    enum Ark_Tag tag;
    Ark_SecurityComponentLayoutDirection value;
} Opt_SecurityComponentLayoutDirection;
typedef struct Union_ListDividerOptions_Ark_Undefined {
    Ark_Int32 selector;
    union {
        struct Ark_ListDividerOptions value0;
        struct Ark_Undefined value1;
    };
} Union_ListDividerOptions_Ark_Undefined;
typedef struct Opt_Union_ListDividerOptions_Undefined {
    enum Ark_Tag tag;
    Union_ListDividerOptions_Ark_Undefined value;
} Opt_Union_ListDividerOptions_Undefined;
typedef struct Ark_ListItemGroupOptions {
    struct Opt_CustomBuilder header;
    Opt_CustomObject headerComponent;
    struct Opt_CustomBuilder footer;
    Opt_CustomObject footerComponent;
    struct Opt_Union_Number_String space;
    Opt_ListItemGroupStyle style;
} Ark_ListItemGroupOptions;
typedef struct Opt_ListItemGroupOptions {
    enum Ark_Tag tag;
    Ark_ListItemGroupOptions value;
} Opt_ListItemGroupOptions;
typedef struct Ark_SwipeActionOptions {
    struct Opt_Union_CustomBuilder_SwipeActionItem start;
    struct Opt_Union_CustomBuilder_SwipeActionItem end;
    Opt_SwipeEdgeEffect edgeEffect;
    struct Opt_Function onOffsetChange;
} Ark_SwipeActionOptions;
typedef struct Opt_SwipeActionOptions {
    enum Ark_Tag tag;
    Ark_SwipeActionOptions value;
} Opt_SwipeActionOptions;
typedef struct Union_Boolean_EditMode {
    Ark_Int32 selector;
    union {
        Ark_Boolean value0;
        Ark_EditMode value1;
    };
} Union_Boolean_EditMode;
typedef struct Opt_Union_Boolean_EditMode {
    enum Ark_Tag tag;
    Union_Boolean_EditMode value;
} Opt_Union_Boolean_EditMode;
typedef Ark_Int32 Ark_Sticky;
typedef struct Opt_Sticky {
    enum Ark_Tag tag;
    Ark_Sticky value;
} Opt_Sticky;
typedef struct Ark_ListItemOptions {
    Opt_ListItemStyle style;
} Ark_ListItemOptions;
typedef struct Opt_ListItemOptions {
    enum Ark_Tag tag;
    Ark_ListItemOptions value;
} Opt_ListItemOptions;
typedef Ark_Materialized Ark_ChildrenMainSize;
typedef struct Opt_ChildrenMainSize {
    enum Ark_Tag tag;
    Ark_ChildrenMainSize value;
} Opt_ChildrenMainSize;
typedef Ark_Int32 Ark_StickyStyle;
typedef struct Opt_StickyStyle {
    enum Ark_Tag tag;
    Ark_StickyStyle value;
} Opt_StickyStyle;
typedef struct Ark_ChainAnimationOptions {
    Ark_Length minSpace;
    Ark_Length maxSpace;
    Opt_Number conductivity;
    Opt_Number intensity;
    Opt_ChainEdgeEffect edgeEffect;
    Opt_Number stiffness;
    Opt_Number damping;
} Ark_ChainAnimationOptions;
typedef struct Opt_ChainAnimationOptions {
    enum Ark_Tag tag;
    Ark_ChainAnimationOptions value;
} Opt_ChainAnimationOptions;
typedef Ark_Int32 Ark_ListItemAlign;
typedef struct Opt_ListItemAlign {
    enum Ark_Tag tag;
    Ark_ListItemAlign value;
} Opt_ListItemAlign;
typedef struct Union_Number_Ark_LengthConstrain {
    Ark_Int32 selector;
    union {
        Ark_Number value0;
        struct Ark_LengthConstrain value1;
    };
} Union_Number_Ark_LengthConstrain;
typedef struct Opt_Union_Number_LengthConstrain {
    enum Ark_Tag tag;
    Union_Number_Ark_LengthConstrain value;
} Opt_Union_Number_LengthConstrain;
typedef struct Ark_ListOptions {
    Opt_Number initialIndex;
    struct Opt_Union_Number_String space;
    Opt_Scroller scroller;
} Ark_ListOptions;
typedef struct Opt_ListOptions {
    enum Ark_Tag tag;
    Ark_ListOptions value;
} Opt_ListOptions;
typedef struct Union_ColorFilter_CustomObject {
    Ark_Int32 selector;
    union {
        struct Ark_ColorFilter value0;
        Ark_CustomObject value1;
    };
} Union_ColorFilter_CustomObject;
typedef struct Opt_Union_ColorFilter_CustomObject {
    enum Ark_Tag tag;
    Union_ColorFilter_CustomObject value;
} Opt_Union_ColorFilter_CustomObject;
typedef struct Ark_ImageFrameInfo {
    struct Union_String_Resource_CustomObject src;
    struct Opt_Union_Number_String width;
    struct Opt_Union_Number_String height;
    struct Opt_Union_Number_String top;
    struct Opt_Union_Number_String left;
    Opt_Number duration;
} Ark_ImageFrameInfo;
typedef struct Opt_ImageFrameInfo {
    enum Ark_Tag tag;
    Ark_ImageFrameInfo value;
} Opt_ImageFrameInfo;
typedef struct Array_ImageFrameInfo {
    struct Ark_ImageFrameInfo* array;
    Ark_Int32 length;
} Array_ImageFrameInfo;
typedef struct Opt_Array_ImageFrameInfo {
    enum Ark_Tag tag;
    Array_ImageFrameInfo value;
} Opt_Array_ImageFrameInfo;
typedef struct Ark_ImageAnalyzerConfig {
    struct Array_ImageAnalyzerType types;
} Ark_ImageAnalyzerConfig;
typedef struct Opt_ImageAnalyzerConfig {
    enum Ark_Tag tag;
    Ark_ImageAnalyzerConfig value;
} Opt_ImageAnalyzerConfig;
typedef Ark_Int32 Ark_CopyOptions;
typedef struct Opt_CopyOptions {
    enum Ark_Tag tag;
    Ark_CopyOptions value;
} Opt_CopyOptions;
typedef struct Literal_Number_width_height {
    Ark_Number width;
    Ark_Number height;
} Literal_Number_width_height;
typedef struct Opt_Literal_Number_width_height {
    enum Ark_Tag tag;
    Literal_Number_width_height value;
} Opt_Literal_Number_width_height;
typedef Ark_Int32 Ark_ImageInterpolation;
typedef struct Opt_ImageInterpolation {
    enum Ark_Tag tag;
    Ark_ImageInterpolation value;
} Opt_ImageInterpolation;
typedef Ark_Int32 Ark_DynamicRangeMode;
typedef struct Opt_DynamicRangeMode {
    enum Ark_Tag tag;
    Ark_DynamicRangeMode value;
} Opt_DynamicRangeMode;
typedef Ark_Int32 Ark_ImageRenderMode;
typedef struct Opt_ImageRenderMode {
    enum Ark_Tag tag;
    Ark_ImageRenderMode value;
} Opt_ImageRenderMode;
typedef struct Union_CustomObject_Ark_ResourceStr_CustomObject {
    Ark_Int32 selector;
    union {
        Ark_CustomObject value0;
        struct Ark_ResourceStr value1;
        Ark_CustomObject value2;
    };
} Union_CustomObject_Ark_ResourceStr_CustomObject;
typedef struct Opt_Union_CustomObject_ResourceStr_CustomObject {
    enum Ark_Tag tag;
    Union_CustomObject_Ark_ResourceStr_CustomObject value;
} Opt_Union_CustomObject_ResourceStr_CustomObject;
typedef struct Union_CustomObject_Ark_ResourceStr_CustomObject_ImageContent {
    Ark_Int32 selector;
    union {
        Ark_CustomObject value0;
        struct Ark_ResourceStr value1;
        Ark_CustomObject value2;
        Ark_ImageContent value3;
    };
} Union_CustomObject_Ark_ResourceStr_CustomObject_ImageContent;
typedef struct Opt_Union_CustomObject_ResourceStr_CustomObject_ImageContent {
    enum Ark_Tag tag;
    Union_CustomObject_Ark_ResourceStr_CustomObject_ImageContent value;
} Opt_Union_CustomObject_ResourceStr_CustomObject_ImageContent;
typedef struct Union_Color_Number_String_Resource {
    Ark_Int32 selector;
    union {
        Ark_Color value0;
        Ark_Number value1;
        Ark_String value2;
        struct Ark_Resource value3;
    };
} Union_Color_Number_String_Resource;
typedef struct Opt_Union_Color_Number_String_Resource {
    enum Ark_Tag tag;
    Union_Color_Number_String_Resource value;
} Opt_Union_Color_Number_String_Resource;
typedef struct Ark_GridRowOptions {
    struct Opt_Union_Length_GutterOption gutter;
    struct Opt_Union_Number_GridRowColumnOption columns;
    struct Opt_BreakPoints breakpoints;
    Opt_GridRowDirection direction;
} Ark_GridRowOptions;
typedef struct Opt_GridRowOptions {
    enum Ark_Tag tag;
    Ark_GridRowOptions value;
} Opt_GridRowOptions;
typedef struct Ark_GridContainerOptions {
    struct Opt_Union_Number_String columns;
    Opt_SizeType sizeType;
    struct Opt_Union_Number_String gutter;
    struct Opt_Union_Number_String margin;
} Ark_GridContainerOptions;
typedef struct Opt_GridContainerOptions {
    enum Ark_Tag tag;
    Ark_GridContainerOptions value;
} Opt_GridContainerOptions;
typedef struct Ark_GridColOptions {
    struct Opt_Union_Number_GridColColumnOption span;
    struct Opt_Union_Number_GridColColumnOption offset;
    struct Opt_Union_Number_GridColColumnOption order;
} Ark_GridColOptions;
typedef struct Opt_GridColOptions {
    enum Ark_Tag tag;
    Ark_GridColOptions value;
} Opt_GridColOptions;
typedef struct Ark_GridItemOptions {
    Opt_GridItemStyle style;
} Ark_GridItemOptions;
typedef struct Opt_GridItemOptions {
    enum Ark_Tag tag;
    Ark_GridItemOptions value;
} Opt_GridItemOptions;
typedef Ark_Int32 Ark_GridDirection;
typedef struct Opt_GridDirection {
    enum Ark_Tag tag;
    Ark_GridDirection value;
} Opt_GridDirection;
typedef struct Ark_GridLayoutOptions {
    struct Tuple_Number_Number regularSize;
    struct Opt_Array_Number irregularIndexes;
    struct Opt_Function onGetIrregularSizeByIndex;
    struct Opt_Function onGetRectByIndex;
} Ark_GridLayoutOptions;
typedef struct Opt_GridLayoutOptions {
    enum Ark_Tag tag;
    Ark_GridLayoutOptions value;
} Opt_GridLayoutOptions;
typedef struct Ark_FadingEdgeOptions {
    Opt_CustomObject fadingEdgeLength;
} Ark_FadingEdgeOptions;
typedef struct Opt_FadingEdgeOptions {
    enum Ark_Tag tag;
    Ark_FadingEdgeOptions value;
} Opt_FadingEdgeOptions;
typedef struct Ark_EdgeEffectOptions {
    Ark_Boolean alwaysEnabled;
} Ark_EdgeEffectOptions;
typedef struct Opt_EdgeEffectOptions {
    enum Ark_Tag tag;
    Ark_EdgeEffectOptions value;
} Opt_EdgeEffectOptions;
typedef struct Ark_GaugeIndicatorOptions {
    struct Opt_ResourceStr icon;
    Opt_Length space;
} Ark_GaugeIndicatorOptions;
typedef struct Opt_GaugeIndicatorOptions {
    enum Ark_Tag tag;
    Ark_GaugeIndicatorOptions value;
} Opt_GaugeIndicatorOptions;
typedef struct Ark_GaugeShadowOptions {
    struct Opt_Union_Number_Resource radius;
    struct Opt_Union_Number_Resource offsetX;
    struct Opt_Union_Number_Resource offsetY;
} Ark_GaugeShadowOptions;
typedef struct Opt_GaugeShadowOptions {
    enum Ark_Tag tag;
    Ark_GaugeShadowOptions value;
} Opt_GaugeShadowOptions;
typedef struct Tuple_Union_Ark_ResourceColor_LinearGradient_Number {
    struct Union_Ark_ResourceColor_LinearGradient value0;
    Ark_Number value1;
} Tuple_Union_Ark_ResourceColor_LinearGradient_Number;
typedef struct Opt_Tuple_Union_ResourceColor_LinearGradient_Number {
    enum Ark_Tag tag;
    Tuple_Union_Ark_ResourceColor_LinearGradient_Number value;
} Opt_Tuple_Union_ResourceColor_LinearGradient_Number;
typedef struct Union_Ark_ResourceColor_LinearGradient_Array_Tuple_Union_Ark_ResourceColor_LinearGradient_Number {
    Ark_Int32 selector;
    union {
        struct Ark_ResourceColor value0;
        struct Ark_LinearGradient value1;
        struct Array_Tuple_Union_Ark_ResourceColor_LinearGradient_Number value2;
    };
} Union_Ark_ResourceColor_LinearGradient_Array_Tuple_Union_Ark_ResourceColor_LinearGradient_Number;
typedef struct Opt_Union_ResourceColor_LinearGradient_Array_Tuple_Union_Ark_ResourceColor_LinearGradient_Number {
    enum Ark_Tag tag;
    Union_Ark_ResourceColor_LinearGradient_Array_Tuple_Union_Ark_ResourceColor_LinearGradient_Number value;
} Opt_Union_ResourceColor_LinearGradient_Array_Tuple_Union_Ark_ResourceColor_LinearGradient_Number;
typedef struct Literal_Number_value_Opt_Number_min_max {
    Ark_Number value;
    Opt_Number min;
    Opt_Number max;
} Literal_Number_value_Opt_Number_min_max;
typedef struct Opt_Literal_Number_value_Opt_Number_min_max {
    enum Ark_Tag tag;
    Literal_Number_value_Opt_Number_min_max value;
} Opt_Literal_Number_value_Opt_Number_min_max;
typedef struct Ark_FormLinkOptions {
    Ark_String action;
    Opt_String moduleName;
    Opt_String bundleName;
    Opt_String abilityName;
    Opt_String uri;
    struct Opt_Object params;
} Ark_FormLinkOptions;
typedef struct Opt_FormLinkOptions {
    enum Ark_Tag tag;
    Ark_FormLinkOptions value;
} Opt_FormLinkOptions;
typedef struct Ark_FormInfo {
    struct Union_Number_String id;
    Ark_String name;
    Ark_String bundle;
    Ark_String ability;
    Ark_String module;
    Opt_FormDimension dimension;
    Opt_Boolean temporary;
    Opt_CustomObject want;
    Opt_FormRenderingMode renderingMode;
    Opt_FormShape shape;
} Ark_FormInfo;
typedef struct Opt_FormInfo {
    enum Ark_Tag tag;
    Ark_FormInfo value;
} Opt_FormInfo;
typedef struct Ark_FolderStackOptions {
    struct Opt_Array_String upperItems;
} Ark_FolderStackOptions;
typedef struct Opt_FolderStackOptions {
    enum Ark_Tag tag;
    Ark_FolderStackOptions value;
} Opt_FolderStackOptions;
typedef struct Ark_FlexOptions {
    Opt_FlexDirection direction;
    Opt_FlexWrap wrap;
    Opt_FlexAlign justifyContent;
    Opt_ItemAlign alignItems;
    Opt_FlexAlign alignContent;
    struct Opt_FlexSpaceOptions space;
} Ark_FlexOptions;
typedef struct Opt_FlexOptions {
    enum Ark_Tag tag;
    Ark_FlexOptions value;
} Opt_FlexOptions;
typedef Ark_Int32 Ark_EmbeddedType;
typedef struct Opt_EmbeddedType {
    enum Ark_Tag tag;
    Ark_EmbeddedType value;
} Opt_EmbeddedType;
typedef struct Ark_DatePickerOptions {
    Opt_CustomObject start;
    Opt_CustomObject end;
    Opt_CustomObject selected;
} Ark_DatePickerOptions;
typedef struct Opt_DatePickerOptions {
    enum Ark_Tag tag;
    Ark_DatePickerOptions value;
} Opt_DatePickerOptions;
typedef struct Ark_DataPanelShadowOptions {
    struct Opt_Union_Number_Resource radius;
    struct Opt_Union_Number_Resource offsetX;
    struct Opt_Union_Number_Resource offsetY;
    struct Opt_Array_Union_ResourceColor_LinearGradient colors;
} Ark_DataPanelShadowOptions;
typedef struct Opt_DataPanelShadowOptions {
    enum Ark_Tag tag;
    Ark_DataPanelShadowOptions value;
} Opt_DataPanelShadowOptions;
typedef struct Ark_DataPanelOptions {
    struct Array_Number values;
    Opt_Number max;
    Opt_DataPanelType type;
} Ark_DataPanelOptions;
typedef struct Opt_DataPanelOptions {
    enum Ark_Tag tag;
    Ark_DataPanelOptions value;
} Opt_DataPanelOptions;
typedef struct Ark_SceneOptions {
    struct Opt_Union_ResourceStr_CustomObject scene;
    Opt_ModelType modelType;
} Ark_SceneOptions;
typedef struct Opt_SceneOptions {
    enum Ark_Tag tag;
    Ark_SceneOptions value;
} Opt_SceneOptions;
typedef struct Union_ColumnSplitDividerStyle_Ark_Undefined {
    Ark_Int32 selector;
    union {
        struct Ark_ColumnSplitDividerStyle value0;
        struct Ark_Undefined value1;
    };
} Union_ColumnSplitDividerStyle_Ark_Undefined;
typedef struct Opt_Union_ColumnSplitDividerStyle_Undefined {
    enum Ark_Tag tag;
    Union_ColumnSplitDividerStyle_Ark_Undefined value;
} Opt_Union_ColumnSplitDividerStyle_Undefined;
typedef struct Ark_PointLightStyle {
    struct Opt_LightSource lightSource;
    Opt_IlluminatedType illuminated;
    Opt_Number bloom;
} Ark_PointLightStyle;
typedef struct Opt_PointLightStyle {
    enum Ark_Tag tag;
    Ark_PointLightStyle value;
} Opt_PointLightStyle;
typedef struct Ark_ColumnOptions {
    struct Opt_Union_String_Number space;
} Ark_ColumnOptions;
typedef struct Opt_ColumnOptions {
    enum Ark_Tag tag;
    Ark_ColumnOptions value;
} Opt_ColumnOptions;
typedef struct Ark_CircleOptions {
    struct Opt_Union_String_Number width;
    struct Opt_Union_String_Number height;
} Ark_CircleOptions;
typedef struct Opt_CircleOptions {
    enum Ark_Tag tag;
    Ark_CircleOptions value;
} Opt_CircleOptions;
typedef Ark_Int32 Ark_LineJoinStyle;
typedef struct Opt_LineJoinStyle {
    enum Ark_Tag tag;
    Ark_LineJoinStyle value;
} Opt_LineJoinStyle;
typedef Ark_Int32 Ark_LineCapStyle;
typedef struct Opt_LineCapStyle {
    enum Ark_Tag tag;
    Ark_LineCapStyle value;
} Opt_LineCapStyle;
typedef struct Ark_CheckboxGroupOptions {
    Opt_String group;
} Ark_CheckboxGroupOptions;
typedef struct Opt_CheckboxGroupOptions {
    enum Ark_Tag tag;
    Ark_CheckboxGroupOptions value;
} Opt_CheckboxGroupOptions;
typedef struct Ark_MarkStyle {
    struct Opt_ResourceColor strokeColor;
    Opt_Length size;
    Opt_Length strokeWidth;
} Ark_MarkStyle;
typedef struct Opt_MarkStyle {
    enum Ark_Tag tag;
    Ark_MarkStyle value;
} Opt_MarkStyle;
typedef Ark_Int32 Ark_CheckBoxShape;
typedef struct Opt_CheckBoxShape {
    enum Ark_Tag tag;
    Ark_CheckBoxShape value;
} Opt_CheckBoxShape;
typedef struct Ark_CheckboxOptions {
    Opt_String name;
    Opt_String group;
    struct Opt_CustomBuilder indicatorBuilder;
} Ark_CheckboxOptions;
typedef struct Opt_CheckboxOptions {
    enum Ark_Tag tag;
    Ark_CheckboxOptions value;
} Opt_CheckboxOptions;
typedef Ark_Int32 Ark_ImageAnalyzerType;
typedef struct Opt_ImageAnalyzerType {
    enum Ark_Tag tag;
    Ark_ImageAnalyzerType value;
} Opt_ImageAnalyzerType;
typedef struct Union_CanvasRenderingContext2D_DrawingRenderingContext {
    Ark_Int32 selector;
    union {
        Ark_CanvasRenderingContext2D value0;
        Ark_DrawingRenderingContext value1;
    };
} Union_CanvasRenderingContext2D_DrawingRenderingContext;
typedef struct Opt_Union_CanvasRenderingContext2D_DrawingRenderingContext {
    enum Ark_Tag tag;
    Union_CanvasRenderingContext2D_DrawingRenderingContext value;
} Opt_Union_CanvasRenderingContext2D_DrawingRenderingContext;
typedef struct Ark_PickerTextStyle {
    struct Opt_ResourceColor color;
    struct Opt_Font font;
} Ark_PickerTextStyle;
typedef struct Opt_PickerTextStyle {
    enum Ark_Tag tag;
    Ark_PickerTextStyle value;
} Opt_PickerTextStyle;
typedef struct Ark_Offset {
    Ark_Length dx;
    Ark_Length dy;
} Ark_Offset;
typedef struct Opt_Offset {
    enum Ark_Tag tag;
    Ark_Offset value;
} Opt_Offset;
typedef Ark_Int32 Ark_CalendarAlign;
typedef struct Opt_CalendarAlign {
    enum Ark_Tag tag;
    Ark_CalendarAlign value;
} Opt_CalendarAlign;
typedef struct Ark_CalendarOptions {
    struct Opt_Union_Number_Resource hintRadius;
    Opt_CustomObject selected;
} Ark_CalendarOptions;
typedef struct Opt_CalendarOptions {
    enum Ark_Tag tag;
    Ark_CalendarOptions value;
} Opt_CalendarOptions;
typedef struct Ark_WorkStateStyle {
    struct Opt_ResourceColor workDayMarkColor;
    struct Opt_ResourceColor offDayMarkColor;
    Opt_Number workDayMarkSize;
    Opt_Number offDayMarkSize;
    Opt_Number workStateWidth;
    Opt_Number workStateHorizontalMovingDistance;
    Opt_Number workStateVerticalMovingDistance;
} Ark_WorkStateStyle;
typedef struct Opt_WorkStateStyle {
    enum Ark_Tag tag;
    Ark_WorkStateStyle value;
} Opt_WorkStateStyle;
typedef struct Ark_WeekStyle {
    struct Opt_ResourceColor weekColor;
    struct Opt_ResourceColor weekendDayColor;
    struct Opt_ResourceColor weekendLunarColor;
    Opt_Number weekFontSize;
    Opt_Number weekHeight;
    Opt_Number weekWidth;
    Opt_Number weekAndDayRowSpace;
} Ark_WeekStyle;
typedef struct Opt_WeekStyle {
    enum Ark_Tag tag;
    Ark_WeekStyle value;
} Opt_WeekStyle;
typedef struct Ark_TodayStyle {
    struct Opt_ResourceColor focusedDayColor;
    struct Opt_ResourceColor focusedLunarColor;
    struct Opt_ResourceColor focusedAreaBackgroundColor;
    Opt_Number focusedAreaRadius;
} Ark_TodayStyle;
typedef struct Opt_TodayStyle {
    enum Ark_Tag tag;
    Ark_TodayStyle value;
} Opt_TodayStyle;
typedef struct Ark_NonCurrentDayStyle {
    struct Opt_ResourceColor nonCurrentMonthDayColor;
    struct Opt_ResourceColor nonCurrentMonthLunarColor;
    struct Opt_ResourceColor nonCurrentMonthWorkDayMarkColor;
    struct Opt_ResourceColor nonCurrentMonthOffDayMarkColor;
} Ark_NonCurrentDayStyle;
typedef struct Opt_NonCurrentDayStyle {
    enum Ark_Tag tag;
    Ark_NonCurrentDayStyle value;
} Opt_NonCurrentDayStyle;
typedef struct Ark_CurrentDayStyle {
    struct Opt_ResourceColor dayColor;
    struct Opt_ResourceColor lunarColor;
    struct Opt_ResourceColor markLunarColor;
    Opt_Number dayFontSize;
    Opt_Number lunarDayFontSize;
    Opt_Number dayHeight;
    Opt_Number dayWidth;
    Opt_Number gregorianCalendarHeight;
    Opt_Number dayYAxisOffset;
    Opt_Number lunarDayYAxisOffset;
    Opt_Number underscoreXAxisOffset;
    Opt_Number underscoreYAxisOffset;
    Opt_Number scheduleMarkerXAxisOffset;
    Opt_Number scheduleMarkerYAxisOffset;
    Opt_Number colSpace;
    Opt_Number dailyFiveRowSpace;
    Opt_Number dailySixRowSpace;
    Opt_Number lunarHeight;
    Opt_Number underscoreWidth;
    Opt_Number underscoreLength;
    Opt_Number scheduleMarkerRadius;
    Opt_Number boundaryRowOffset;
    Opt_Number boundaryColOffset;
} Ark_CurrentDayStyle;
typedef struct Opt_CurrentDayStyle {
    enum Ark_Tag tag;
    Ark_CurrentDayStyle value;
} Opt_CurrentDayStyle;
typedef struct Ark_CalendarDay {
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
} Ark_CalendarDay;
typedef struct Opt_CalendarDay {
    enum Ark_Tag tag;
    Ark_CalendarDay value;
} Opt_CalendarDay;
typedef struct Literal_Literal_Number_year_month_day_date_MonthData_currentData_preData_nextData_Opt_CalendarController_controller {
    struct Literal_Number_year_month_day date;
    struct Ark_MonthData currentData;
    struct Ark_MonthData preData;
    struct Ark_MonthData nextData;
    Opt_CalendarController controller;
} Literal_Literal_Number_year_month_day_date_MonthData_currentData_preData_nextData_Opt_CalendarController_controller;
typedef struct Opt_Literal_Literal_Number_year_month_day_date_MonthData_currentData_preData_nextData_Opt_CalendarController_controller {
    enum Ark_Tag tag;
    Literal_Literal_Number_year_month_day_date_MonthData_currentData_preData_nextData_Opt_CalendarController_controller value;
} Opt_Literal_Literal_Number_year_month_day_date_MonthData_currentData_preData_nextData_Opt_CalendarController_controller;
typedef struct Ark_ButtonOptions {
    Opt_ButtonType type;
    Opt_Boolean stateEffect;
    Opt_ButtonStyleMode buttonStyle;
    Opt_ControlSize controlSize;
    Opt_ButtonRole role;
} Ark_ButtonOptions;
typedef struct Opt_ButtonOptions {
    enum Ark_Tag tag;
    Ark_ButtonOptions value;
} Opt_ButtonOptions;
typedef struct Ark_BadgeParamWithString {
    struct Opt_Union_BadgePosition_Position position;
    struct Ark_BadgeStyle style;
    Ark_String value;
} Ark_BadgeParamWithString;
typedef struct Opt_BadgeParamWithString {
    enum Ark_Tag tag;
    Ark_BadgeParamWithString value;
} Opt_BadgeParamWithString;
typedef struct Ark_BadgeParamWithNumber {
    struct Opt_Union_BadgePosition_Position position;
    struct Ark_BadgeStyle style;
    Ark_Number count;
    Opt_Number maxCount;
} Ark_BadgeParamWithNumber;
typedef struct Opt_BadgeParamWithNumber {
    enum Ark_Tag tag;
    Ark_BadgeParamWithNumber value;
} Opt_BadgeParamWithNumber;
typedef struct Union_SpringMotion_FrictionMotion_ScrollMotion {
    Ark_Int32 selector;
    union {
        struct Ark_SpringMotion value0;
        struct Ark_FrictionMotion value1;
        struct Ark_ScrollMotion value2;
    };
} Union_SpringMotion_FrictionMotion_ScrollMotion;
typedef struct Opt_Union_SpringMotion_FrictionMotion_ScrollMotion {
    enum Ark_Tag tag;
    Union_SpringMotion_FrictionMotion_ScrollMotion value;
} Opt_Union_SpringMotion_FrictionMotion_ScrollMotion;
typedef Ark_Int32 Ark_FillMode;
typedef struct Opt_FillMode {
    enum Ark_Tag tag;
    Ark_FillMode value;
} Opt_FillMode;
typedef Ark_Int32 Ark_AnimationStatus;
typedef struct Opt_AnimationStatus {
    enum Ark_Tag tag;
    Ark_AnimationStatus value;
} Opt_AnimationStatus;
typedef Ark_Int32 Ark_IndexerAlign;
typedef struct Opt_IndexerAlign {
    enum Ark_Tag tag;
    Ark_IndexerAlign value;
} Opt_IndexerAlign;
typedef struct Ark_AlphabetIndexerOptions {
    struct Array_String arrayValue;
    Ark_Number selected;
} Ark_AlphabetIndexerOptions;
typedef struct Opt_AlphabetIndexerOptions {
    enum Ark_Tag tag;
    Ark_AlphabetIndexerOptions value;
} Opt_AlphabetIndexerOptions;
typedef struct Literal_CustomObject_want {
    Ark_CustomObject want;
} Literal_CustomObject_want;
typedef struct Opt_Literal_CustomObject_want {
    enum Ark_Tag tag;
    Literal_CustomObject_want value;
} Opt_Literal_CustomObject_want;
typedef struct Ark_BackgroundBrightnessOptions {
    Ark_Number rate;
    Ark_Number lightUpDegree;
} Ark_BackgroundBrightnessOptions;
typedef struct Opt_BackgroundBrightnessOptions {
    enum Ark_Tag tag;
    Ark_BackgroundBrightnessOptions value;
} Opt_BackgroundBrightnessOptions;
typedef Ark_Materialized Ark_GestureModifier;
typedef struct Opt_GestureModifier {
    enum Ark_Tag tag;
    Ark_GestureModifier value;
} Opt_GestureModifier;
typedef Ark_Int32 Ark_RenderFit;
typedef struct Opt_RenderFit {
    enum Ark_Tag tag;
    Ark_RenderFit value;
} Opt_RenderFit;
typedef Ark_Int32 Ark_ObscuredReasons;
typedef struct Opt_ObscuredReasons {
    enum Ark_Tag tag;
    Ark_ObscuredReasons value;
} Opt_ObscuredReasons;
typedef int32_t Ark_ObscuredReasons;
typedef struct Array_ObscuredReasons {
    Ark_ObscuredReasons* array;
    Ark_Int32 length;
} Array_ObscuredReasons;
typedef int32_t Ark_ObscuredReasons;
typedef struct Opt_Array_ObscuredReasons {
    enum Ark_Tag tag;
    Array_ObscuredReasons value;
} Opt_Array_ObscuredReasons;
typedef Ark_Int32 Ark_ModifierKey;
typedef struct Opt_ModifierKey {
    enum Ark_Tag tag;
    Ark_ModifierKey value;
} Opt_ModifierKey;
typedef int32_t Ark_ModifierKey;
typedef struct Array_ModifierKey {
    Ark_ModifierKey* array;
    Ark_Int32 length;
} Array_ModifierKey;
typedef int32_t Ark_ModifierKey;
typedef struct Opt_Array_ModifierKey {
    enum Ark_Tag tag;
    Array_ModifierKey value;
} Opt_Array_ModifierKey;
typedef struct Union_String_FunctionKey {
    Ark_Int32 selector;
    union {
        Ark_String value0;
        Ark_FunctionKey value1;
    };
} Union_String_FunctionKey;
typedef struct Opt_Union_String_FunctionKey {
    enum Ark_Tag tag;
    Union_String_FunctionKey value;
} Opt_Union_String_FunctionKey;
typedef struct Ark_PixelStretchEffectOptions {
    Opt_Length top;
    Opt_Length bottom;
    Opt_Length left;
    Opt_Length right;
} Ark_PixelStretchEffectOptions;
typedef struct Opt_PixelStretchEffectOptions {
    enum Ark_Tag tag;
    Ark_PixelStretchEffectOptions value;
} Opt_PixelStretchEffectOptions;
typedef struct Ark_StateStyles {
    Opt_CustomObject normal;
    Opt_CustomObject pressed;
    Opt_CustomObject disabled;
    Opt_CustomObject focused;
    Opt_CustomObject clicked;
    Opt_CustomObject selected;
} Ark_StateStyles;
typedef struct Opt_StateStyles {
    enum Ark_Tag tag;
    Ark_StateStyles value;
} Opt_StateStyles;
typedef struct Ark_SheetOptions {
    struct Opt_ResourceColor backgroundColor;
    struct Opt_Function onAppear;
    struct Opt_Function onDisappear;
    struct Opt_Function onWillAppear;
    struct Opt_Function onWillDisappear;
    struct Opt_Union_SheetSize_Length height;
    Opt_Boolean dragBar;
    struct Opt_ResourceColor maskColor;
    struct Opt_Tuple_Union_SheetSize_Length_Opt_Union_SheetSize_Length_Opt_Union_SheetSize_Length detents;
    Opt_BlurStyle blurStyle;
    struct Opt_Union_Boolean_Resource showClose;
    Opt_SheetType preferType;
    struct Opt_Union_SheetTitleOptions_CustomBuilder title;
    struct Opt_Function shouldDismiss;
    struct Opt_Function onWillDismiss;
    struct Opt_Function onWillSpringBackWhenDismiss;
    Opt_Boolean enableOutsideInteractive;
    Opt_Length width;
    struct Opt_Union_Length_EdgeWidths_LocalizedEdgeWidths borderWidth;
    struct Opt_Union_ResourceColor_Ark_EdgeColors_LocalizedEdgeColors borderColor;
    struct Opt_Union_BorderStyle_EdgeStyles borderStyle;
    struct Opt_Union_ShadowOptions_ShadowStyle shadow;
    struct Opt_Function onHeightDidChange;
    Opt_SheetMode mode;
    Opt_ScrollSizeMode scrollSizeMode;
    struct Opt_Function onDetentsDidChange;
    struct Opt_Function onWidthDidChange;
    struct Opt_Function onTypeDidChange;
    Opt_Boolean expandSafeAreaInEmbeddedMode;
    Opt_CustomObject uiContext;
} Ark_SheetOptions;
typedef struct Opt_SheetOptions {
    enum Ark_Tag tag;
    Ark_SheetOptions value;
} Opt_SheetOptions;
typedef struct Ark_ContentCoverOptions {
    struct Opt_ResourceColor backgroundColor;
    struct Opt_Function onAppear;
    struct Opt_Function onDisappear;
    struct Opt_Function onWillAppear;
    struct Opt_Function onWillDisappear;
    Opt_ModalTransition modalTransition;
    struct Opt_Function onWillDismiss;
    struct Opt_TransitionEffect transition;
} Ark_ContentCoverOptions;
typedef struct Opt_ContentCoverOptions {
    enum Ark_Tag tag;
    Ark_ContentCoverOptions value;
} Opt_ContentCoverOptions;
typedef struct Union_Array_MenuElement_Ark_CustomBuilder {
    Ark_Int32 selector;
    union {
        struct Array_MenuElement value0;
        struct Ark_CustomBuilder value1;
    };
} Union_Array_MenuElement_Ark_CustomBuilder;
typedef struct Opt_Union_Array_MenuElement_CustomBuilder {
    enum Ark_Tag tag;
    Union_Array_MenuElement_Ark_CustomBuilder value;
} Opt_Union_Array_MenuElement_CustomBuilder;
typedef struct Ark_MenuOptions {
    struct Opt_Position offset;
    Opt_Placement placement;
    Opt_Boolean enableArrow;
    Opt_Length arrowOffset;
    struct Opt_Union_MenuPreviewMode_CustomBuilder preview;
    struct Opt_Union_Length_BorderRadiuses_LocalizedBorderRadiuses borderRadius;
    struct Opt_Function onAppear;
    struct Opt_Function onDisappear;
    struct Opt_Function aboutToAppear;
    struct Opt_Function aboutToDisappear;
    struct Opt_ContextMenuAnimationOptions previewAnimationOptions;
    struct Opt_ResourceColor backgroundColor;
    Opt_BlurStyle backgroundBlurStyle;
    struct Opt_TransitionEffect transition;
    Opt_Boolean enableHoverMode;
    struct Opt_ResourceStr title;
    Opt_Boolean showInSubWindow;
} Ark_MenuOptions;
typedef struct Opt_MenuOptions {
    enum Ark_Tag tag;
    Ark_MenuOptions value;
} Opt_MenuOptions;
typedef struct Ark_MenuElement {
    struct Ark_ResourceStr value;
    struct Opt_ResourceStr icon;
    Opt_CustomObject symbolIcon;
    Opt_Boolean enabled;
    struct Ark_Function action;
} Ark_MenuElement;
typedef struct Opt_MenuElement {
    enum Ark_Tag tag;
    Ark_MenuElement value;
} Opt_MenuElement;
typedef struct Union_PopupOptions_CustomPopupOptions {
    Ark_Int32 selector;
    union {
        struct Ark_PopupOptions value0;
        struct Ark_CustomPopupOptions value1;
    };
} Union_PopupOptions_CustomPopupOptions;
typedef struct Opt_Union_PopupOptions_CustomPopupOptions {
    enum Ark_Tag tag;
    Union_PopupOptions_CustomPopupOptions value;
} Opt_Union_PopupOptions_CustomPopupOptions;
typedef struct Ark_GeometryTransitionOptions {
    Opt_Boolean follow;
    Opt_TransitionHierarchyStrategy hierarchyStrategy;
} Ark_GeometryTransitionOptions;
typedef struct Opt_GeometryTransitionOptions {
    enum Ark_Tag tag;
    Ark_GeometryTransitionOptions value;
} Opt_GeometryTransitionOptions;
typedef struct Union_CustomObject_CustomObject_CustomObject_CustomObject {
    Ark_Int32 selector;
    union {
        Ark_CustomObject value0;
        Ark_CustomObject value1;
        Ark_CustomObject value2;
        Ark_CustomObject value3;
    };
} Union_CustomObject_CustomObject_CustomObject_CustomObject;
typedef struct Opt_Union_CustomObject_CustomObject_CustomObject_CustomObject {
    enum Ark_Tag tag;
    Union_CustomObject_CustomObject_CustomObject_CustomObject value;
} Opt_Union_CustomObject_CustomObject_CustomObject_CustomObject;
typedef struct Union_CircleAttribute_EllipseAttribute_PathAttribute_RectAttribute_ProgressMask {
    Ark_Int32 selector;
    union {
        struct Ark_CircleAttribute value0;
        struct Ark_EllipseAttribute value1;
        struct Ark_PathAttribute value2;
        struct Ark_RectAttribute value3;
        Ark_ProgressMask value4;
    };
} Union_CircleAttribute_EllipseAttribute_PathAttribute_RectAttribute_ProgressMask;
typedef struct Opt_Union_CircleAttribute_EllipseAttribute_PathAttribute_RectAttribute_ProgressMask {
    enum Ark_Tag tag;
    Union_CircleAttribute_EllipseAttribute_PathAttribute_RectAttribute_ProgressMask value;
} Opt_Union_CircleAttribute_EllipseAttribute_PathAttribute_RectAttribute_ProgressMask;
typedef struct Union_Boolean_CircleAttribute_EllipseAttribute_PathAttribute_RectAttribute {
    Ark_Int32 selector;
    union {
        Ark_Boolean value0;
        struct Ark_CircleAttribute value1;
        struct Ark_EllipseAttribute value2;
        struct Ark_PathAttribute value3;
        struct Ark_RectAttribute value4;
    };
} Union_Boolean_CircleAttribute_EllipseAttribute_PathAttribute_RectAttribute;
typedef struct Opt_Union_Boolean_CircleAttribute_EllipseAttribute_PathAttribute_RectAttribute {
    enum Ark_Tag tag;
    Union_Boolean_CircleAttribute_EllipseAttribute_PathAttribute_RectAttribute value;
} Opt_Union_Boolean_CircleAttribute_EllipseAttribute_PathAttribute_RectAttribute;
typedef struct Union_BlendMode_CustomObject {
    Ark_Int32 selector;
    union {
        Ark_BlendMode value0;
        Ark_CustomObject value1;
    };
} Union_BlendMode_CustomObject;
typedef struct Opt_Union_BlendMode_CustomObject {
    enum Ark_Tag tag;
    Union_BlendMode_CustomObject value;
} Opt_Union_BlendMode_CustomObject;
typedef Ark_Int32 Ark_BlendApplyType;
typedef struct Opt_BlendApplyType {
    enum Ark_Tag tag;
    Ark_BlendApplyType value;
} Opt_BlendApplyType;
typedef struct Tuple_Ark_ResourceColor_Number {
    struct Ark_ResourceColor value0;
    Ark_Number value1;
} Tuple_Ark_ResourceColor_Number;
typedef struct Opt_Tuple_ResourceColor_Number {
    enum Ark_Tag tag;
    Tuple_Ark_ResourceColor_Number value;
} Opt_Tuple_ResourceColor_Number;
typedef struct Literal_Tuple_Length_Length_center_Union_Number_String_radius_Array_Tuple_Ark_ResourceColor_Number_colors_Opt_Boolean_repeating {
    struct Tuple_Length_Length center;
    struct Union_Number_String radius;
    struct Array_Tuple_Ark_ResourceColor_Number colors;
    Opt_Boolean repeating;
} Literal_Tuple_Length_Length_center_Union_Number_String_radius_Array_Tuple_Ark_ResourceColor_Number_colors_Opt_Boolean_repeating;
typedef struct Opt_Literal_Tuple_Length_Length_center_Union_Number_String_radius_Array_Tuple_ResourceColor_Number_colors_Opt_Boolean_repeating {
    enum Ark_Tag tag;
    Literal_Tuple_Length_Length_center_Union_Number_String_radius_Array_Tuple_Ark_ResourceColor_Number_colors_Opt_Boolean_repeating value;
} Opt_Literal_Tuple_Length_Length_center_Union_Number_String_radius_Array_Tuple_ResourceColor_Number_colors_Opt_Boolean_repeating;
typedef struct Literal_Tuple_Length_Length_center_Opt_Union_Number_String_start_end_rotation_Array_Tuple_Ark_ResourceColor_Number_colors_Opt_Boolean_repeating {
    struct Tuple_Length_Length center;
    struct Opt_Union_Number_String start;
    struct Opt_Union_Number_String end;
    struct Opt_Union_Number_String rotation;
    struct Array_Tuple_Ark_ResourceColor_Number colors;
    Opt_Boolean repeating;
} Literal_Tuple_Length_Length_center_Opt_Union_Number_String_start_end_rotation_Array_Tuple_Ark_ResourceColor_Number_colors_Opt_Boolean_repeating;
typedef struct Opt_Literal_Tuple_Length_Length_center_Opt_Union_Number_String_start_end_rotation_Array_Tuple_ResourceColor_Number_colors_Opt_Boolean_repeating {
    enum Ark_Tag tag;
    Literal_Tuple_Length_Length_center_Opt_Union_Number_String_start_end_rotation_Array_Tuple_Ark_ResourceColor_Number_colors_Opt_Boolean_repeating value;
} Opt_Literal_Tuple_Length_Length_center_Opt_Union_Number_String_start_end_rotation_Array_Tuple_ResourceColor_Number_colors_Opt_Boolean_repeating;
typedef struct Literal_Opt_Union_Number_String_angle_Opt_GradientDirection_direction_Array_Tuple_Ark_ResourceColor_Number_colors_Opt_Boolean_repeating {
    struct Opt_Union_Number_String angle;
    Opt_GradientDirection direction;
    struct Array_Tuple_Ark_ResourceColor_Number colors;
    Opt_Boolean repeating;
} Literal_Opt_Union_Number_String_angle_Opt_GradientDirection_direction_Array_Tuple_Ark_ResourceColor_Number_colors_Opt_Boolean_repeating;
typedef struct Opt_Literal_Opt_Union_Number_String_angle_Opt_GradientDirection_direction_Array_Tuple_ResourceColor_Number_colors_Opt_Boolean_repeating {
    enum Ark_Tag tag;
    Literal_Opt_Union_Number_String_angle_Opt_GradientDirection_direction_Array_Tuple_Ark_ResourceColor_Number_colors_Opt_Boolean_repeating value;
} Opt_Literal_Opt_Union_Number_String_angle_Opt_GradientDirection_direction_Array_Tuple_ResourceColor_Number_colors_Opt_Boolean_repeating;
typedef struct Ark_OverlayOptions {
    Opt_Alignment align;
    struct Opt_OverlayOffset offset;
} Ark_OverlayOptions;
typedef struct Opt_OverlayOptions {
    enum Ark_Tag tag;
    Ark_OverlayOptions value;
} Opt_OverlayOptions;
typedef struct Union_String_Ark_CustomBuilder_CustomObject {
    Ark_Int32 selector;
    union {
        Ark_String value0;
        struct Ark_CustomBuilder value1;
        Ark_CustomObject value2;
    };
} Union_String_Ark_CustomBuilder_CustomObject;
typedef struct Opt_Union_String_CustomBuilder_CustomObject {
    enum Ark_Tag tag;
    Union_String_Ark_CustomBuilder_CustomObject value;
} Opt_Union_String_CustomBuilder_CustomObject;
typedef struct Ark_DragInteractionOptions {
    Opt_Boolean isMultiSelectionEnabled;
    Opt_Boolean defaultAnimationBeforeLifting;
} Ark_DragInteractionOptions;
typedef struct Opt_DragInteractionOptions {
    enum Ark_Tag tag;
    Ark_DragInteractionOptions value;
} Opt_DragInteractionOptions;
typedef struct Ark_DragPreviewOptions {
    struct Opt_Union_DragPreviewMode_Array_DragPreviewMode mode;
    Opt_CustomObject modifier;
    struct Opt_Union_Boolean_Number numberBadge;
} Ark_DragPreviewOptions;
typedef struct Opt_DragPreviewOptions {
    enum Ark_Tag tag;
    Ark_DragPreviewOptions value;
} Opt_DragPreviewOptions;
typedef struct Union_Ark_CustomBuilder_DragItemInfo_String {
    Ark_Int32 selector;
    union {
        struct Ark_CustomBuilder value0;
        struct Ark_DragItemInfo value1;
        Ark_String value2;
    };
} Union_Ark_CustomBuilder_DragItemInfo_String;
typedef struct Opt_Union_CustomBuilder_DragItemInfo_String {
    enum Ark_Tag tag;
    Union_Ark_CustomBuilder_DragItemInfo_String value;
} Opt_Union_CustomBuilder_DragItemInfo_String;
typedef struct Union_Array_CustomObject_Ark_Undefined {
    Ark_Int32 selector;
    union {
        struct Array_CustomObject value0;
        struct Ark_Undefined value1;
    };
} Union_Array_CustomObject_Ark_Undefined;
typedef struct Opt_Union_Array_CustomObject_Undefined {
    enum Ark_Tag tag;
    Union_Array_CustomObject_Ark_Undefined value;
} Opt_Union_Array_CustomObject_Undefined;
typedef struct Union_ClickEffect_Ark_Undefined {
    Ark_Int32 selector;
    union {
        struct Ark_ClickEffect value0;
        struct Ark_Undefined value1;
    };
} Union_ClickEffect_Ark_Undefined;
typedef struct Opt_Union_ClickEffect_Undefined {
    enum Ark_Tag tag;
    Union_ClickEffect_Ark_Undefined value;
} Opt_Union_ClickEffect_Undefined;
typedef Ark_Int32 Ark_ChainStyle;
typedef struct Opt_ChainStyle {
    enum Ark_Tag tag;
    Ark_ChainStyle value;
} Opt_ChainStyle;
typedef struct Ark_LocalizedAlignRuleOptions {
    struct Opt_LocalizedHorizontalAlignParam start;
    struct Opt_LocalizedHorizontalAlignParam end;
    struct Opt_LocalizedHorizontalAlignParam middle;
    struct Opt_LocalizedVerticalAlignParam top;
    struct Opt_LocalizedVerticalAlignParam bottom;
    struct Opt_LocalizedVerticalAlignParam center;
    struct Opt_Bias bias;
} Ark_LocalizedAlignRuleOptions;
typedef struct Opt_LocalizedAlignRuleOptions {
    enum Ark_Tag tag;
    Ark_LocalizedAlignRuleOptions value;
} Opt_LocalizedAlignRuleOptions;
typedef struct Ark_AlignRuleOption {
    struct Opt_Literal_String_anchor_HorizontalAlign_align left;
    struct Opt_Literal_String_anchor_HorizontalAlign_align right;
    struct Opt_Literal_String_anchor_HorizontalAlign_align middle;
    struct Opt_Literal_String_anchor_VerticalAlign_align top;
    struct Opt_Literal_String_anchor_VerticalAlign_align bottom;
    struct Opt_Literal_String_anchor_VerticalAlign_align center;
    struct Opt_Bias bias;
} Ark_AlignRuleOption;
typedef struct Opt_AlignRuleOption {
    enum Ark_Tag tag;
    Ark_AlignRuleOption value;
} Opt_AlignRuleOption;
typedef struct Literal_Opt_Union_Number_Literal_Number_span_offset_xs_sm_md_lg {
    struct Opt_Union_Number_Literal_Number_span_offset xs;
    struct Opt_Union_Number_Literal_Number_span_offset sm;
    struct Opt_Union_Number_Literal_Number_span_offset md;
    struct Opt_Union_Number_Literal_Number_span_offset lg;
} Literal_Opt_Union_Number_Literal_Number_span_offset_xs_sm_md_lg;
typedef struct Opt_Literal_Opt_Union_Number_Literal_Number_span_offset_xs_sm_md_lg {
    enum Ark_Tag tag;
    Literal_Opt_Union_Number_Literal_Number_span_offset_xs_sm_md_lg value;
} Opt_Literal_Opt_Union_Number_Literal_Number_span_offset_xs_sm_md_lg;
typedef struct Union_Position_LocalizedPosition {
    Ark_Int32 selector;
    union {
        struct Ark_Position value0;
        struct Ark_LocalizedPosition value1;
    };
} Union_Position_LocalizedPosition;
typedef struct Opt_Union_Position_LocalizedPosition {
    enum Ark_Tag tag;
    Union_Position_LocalizedPosition value;
} Opt_Union_Position_LocalizedPosition;
typedef Ark_Int32 Ark_Direction;
typedef struct Opt_Direction {
    enum Ark_Tag tag;
    Ark_Direction value;
} Opt_Direction;
typedef struct Ark_sharedTransitionOptions {
    Opt_Number duration;
    struct Opt_Union_Curve_String_ICurve curve;
    Opt_Number delay;
    struct Opt_MotionPathOptions motionPath;
    Opt_Number zIndex;
    Opt_SharedTransitionEffectType type;
} Ark_sharedTransitionOptions;
typedef struct Opt_sharedTransitionOptions {
    enum Ark_Tag tag;
    Ark_sharedTransitionOptions value;
} Opt_sharedTransitionOptions;
typedef Ark_Int32 Ark_Visibility;
typedef struct Opt_Visibility {
    enum Ark_Tag tag;
    Ark_Visibility value;
} Opt_Visibility;
typedef struct Union_Number_InvertOptions {
    Ark_Int32 selector;
    union {
        Ark_Number value0;
        struct Ark_InvertOptions value1;
    };
} Union_Number_InvertOptions;
typedef struct Opt_Union_Number_InvertOptions {
    enum Ark_Tag tag;
    Union_Number_InvertOptions value;
} Opt_Union_Number_InvertOptions;
typedef struct Union_Color_String_Resource {
    Ark_Int32 selector;
    union {
        Ark_Color value0;
        Ark_String value1;
        struct Ark_Resource value2;
    };
} Union_Color_String_Resource;
typedef struct Opt_Union_Color_String_Resource {
    enum Ark_Tag tag;
    Union_Color_String_Resource value;
} Opt_Union_Color_String_Resource;
typedef struct Ark_MotionBlurOptions {
    Ark_Number radius;
    struct Ark_MotionBlurAnchor anchor;
} Ark_MotionBlurOptions;
typedef struct Opt_MotionBlurOptions {
    enum Ark_Tag tag;
    Ark_MotionBlurOptions value;
} Opt_MotionBlurOptions;
typedef struct Ark_LinearGradientBlurOptions {
    struct Array_Tuple_Number_Number fractionStops;
    Ark_GradientDirection direction;
} Ark_LinearGradientBlurOptions;
typedef struct Opt_LinearGradientBlurOptions {
    enum Ark_Tag tag;
    Ark_LinearGradientBlurOptions value;
} Opt_LinearGradientBlurOptions;
typedef Ark_Int32 Ark_GestureMask;
typedef struct Opt_GestureMask {
    enum Ark_Tag tag;
    Ark_GestureMask value;
} Opt_GestureMask;
typedef struct Ark_GestureType {
    Ark_Int32 selector;
    union {
        struct Ark_TapGestureInterface value0;
        struct Ark_LongPressGestureInterface value1;
        struct Ark_PanGestureInterface value2;
        struct Ark_PinchGestureInterface value3;
        struct Ark_SwipeGestureInterface value4;
        struct Ark_RotationGestureInterface value5;
        struct Ark_GestureGroupInterface value6;
    };
} Ark_GestureType;
typedef struct Opt_GestureType {
    enum Ark_Tag tag;
    Ark_GestureType value;
} Opt_GestureType;
typedef struct Union_TransitionOptions_TransitionEffect {
    Ark_Int32 selector;
    union {
        struct Ark_TransitionOptions value0;
        struct Ark_TransitionEffect value1;
    };
} Union_TransitionOptions_TransitionEffect;
typedef struct Opt_Union_TransitionOptions_TransitionEffect {
    enum Ark_Tag tag;
    Union_TransitionOptions_TransitionEffect value;
} Opt_Union_TransitionOptions_TransitionEffect;
typedef struct Ark_AnimateParam {
    Opt_Number duration;
    Opt_Number tempo;
    struct Opt_Union_Curve_String_ICurve curve;
    Opt_Number delay;
    Opt_Number iterations;
    Opt_PlayMode playMode;
    struct Opt_Function onFinish;
    Opt_FinishCallbackType finishCallbackType;
    struct Opt_ExpectedFrameRateRange expectedFrameRateRange;
} Ark_AnimateParam;
typedef struct Opt_AnimateParam {
    enum Ark_Tag tag;
    Ark_AnimateParam value;
} Opt_AnimateParam;
typedef Ark_Int32 Ark_FocusPriority;
typedef struct Opt_FocusPriority {
    enum Ark_Tag tag;
    Ark_FocusPriority value;
} Opt_FocusPriority;
typedef struct Ark_FocusBoxStyle {
    Opt_CustomObject margin;
    Opt_CustomObject strokeColor;
    Opt_CustomObject strokeWidth;
} Ark_FocusBoxStyle;
typedef struct Opt_FocusBoxStyle {
    enum Ark_Tag tag;
    Ark_FocusBoxStyle value;
} Opt_FocusBoxStyle;
typedef Ark_Int32 Ark_HoverEffect;
typedef struct Opt_HoverEffect {
    enum Ark_Tag tag;
    Ark_HoverEffect value;
} Opt_HoverEffect;
typedef struct Union_Ark_ResourceColor_ColoringStrategy {
    Ark_Int32 selector;
    union {
        struct Ark_ResourceColor value0;
        Ark_ColoringStrategy value1;
    };
} Union_Ark_ResourceColor_ColoringStrategy;
typedef struct Opt_Union_ResourceColor_ColoringStrategy {
    enum Ark_Tag tag;
    Union_Ark_ResourceColor_ColoringStrategy value;
} Opt_Union_ResourceColor_ColoringStrategy;
typedef struct Union_Length_Ark_OutlineRadiuses {
    Ark_Int32 selector;
    union {
        Ark_Length value0;
        struct Ark_OutlineRadiuses value1;
    };
} Union_Length_Ark_OutlineRadiuses;
typedef struct Opt_Union_Length_OutlineRadiuses {
    enum Ark_Tag tag;
    Union_Length_Ark_OutlineRadiuses value;
} Opt_Union_Length_OutlineRadiuses;
typedef struct Union_Length_Ark_EdgeOutlineWidths {
    Ark_Int32 selector;
    union {
        Ark_Length value0;
        struct Ark_EdgeOutlineWidths value1;
    };
} Union_Length_Ark_EdgeOutlineWidths;
typedef struct Opt_Union_Length_EdgeOutlineWidths {
    enum Ark_Tag tag;
    Union_Length_Ark_EdgeOutlineWidths value;
} Opt_Union_Length_EdgeOutlineWidths;
typedef struct Union_OutlineStyle_Ark_EdgeOutlineStyles {
    Ark_Int32 selector;
    union {
        Ark_OutlineStyle value0;
        struct Ark_EdgeOutlineStyles value1;
    };
} Union_OutlineStyle_Ark_EdgeOutlineStyles;
typedef struct Opt_Union_OutlineStyle_EdgeOutlineStyles {
    enum Ark_Tag tag;
    Union_OutlineStyle_Ark_EdgeOutlineStyles value;
} Opt_Union_OutlineStyle_EdgeOutlineStyles;
typedef struct Ark_OutlineOptions {
    struct Opt_Union_EdgeOutlineWidths_Length width;
    struct Opt_Union_EdgeColors_Ark_ResourceColor_LocalizedEdgeColors color;
    struct Opt_Union_OutlineRadiuses_Length radius;
    struct Opt_Union_EdgeOutlineStyles_OutlineStyle style;
} Ark_OutlineOptions;
typedef struct Opt_OutlineOptions {
    enum Ark_Tag tag;
    Ark_OutlineOptions value;
} Opt_OutlineOptions;
typedef struct Ark_BorderImageOption {
    struct Opt_Union_Length_EdgeWidths_LocalizedEdgeWidths slice;
    Opt_RepeatMode repeat;
    struct Opt_Union_String_Resource_LinearGradient source;
    struct Opt_Union_Length_EdgeWidths_LocalizedEdgeWidths width;
    struct Opt_Union_Length_EdgeWidths_LocalizedEdgeWidths outset;
    Opt_Boolean fill;
} Ark_BorderImageOption;
typedef struct Opt_BorderImageOption {
    enum Ark_Tag tag;
    Ark_BorderImageOption value;
} Opt_BorderImageOption;
typedef struct Ark_BorderOptions {
    struct Opt_Union_EdgeWidths_Length_LocalizedEdgeWidths width;
    struct Opt_Union_EdgeColors_Ark_ResourceColor_LocalizedEdgeColors color;
    struct Opt_Union_BorderRadiuses_Length_LocalizedBorderRadiuses radius;
    struct Opt_Union_EdgeStyles_BorderStyle style;
    struct Opt_Union_EdgeWidths_CustomObject_LocalizedEdgeWidths dashGap;
    struct Opt_Union_EdgeWidths_CustomObject_LocalizedEdgeWidths dashWidth;
} Ark_BorderOptions;
typedef struct Opt_BorderOptions {
    enum Ark_Tag tag;
    Ark_BorderOptions value;
} Opt_BorderOptions;
typedef struct Ark_ForegroundBlurStyleOptions {
    Opt_ThemeColorMode colorMode;
    Opt_AdaptiveColor adaptiveColor;
    Opt_Number scale;
    struct Opt_BlurOptions blurOptions;
} Ark_ForegroundBlurStyleOptions;
typedef struct Opt_ForegroundBlurStyleOptions {
    enum Ark_Tag tag;
    Ark_ForegroundBlurStyleOptions value;
} Opt_ForegroundBlurStyleOptions;
typedef struct Ark_ForegroundEffectOptions {
    Ark_Number radius;
} Ark_ForegroundEffectOptions;
typedef struct Opt_ForegroundEffectOptions {
    enum Ark_Tag tag;
    Ark_ForegroundEffectOptions value;
} Opt_ForegroundEffectOptions;
typedef struct Ark_ResizableOptions {
    struct Opt_EdgeWidths slice;
    Opt_CustomObject lattice;
} Ark_ResizableOptions;
typedef struct Opt_ResizableOptions {
    enum Ark_Tag tag;
    Ark_ResizableOptions value;
} Opt_ResizableOptions;
typedef struct Ark_BackgroundEffectOptions {
    Ark_Number radius;
    Opt_Number saturation;
    Opt_Number brightness;
    struct Opt_ResourceColor color;
    Opt_AdaptiveColor adaptiveColor;
    struct Opt_BlurOptions blurOptions;
    Opt_BlurStyleActivePolicy policy;
    struct Opt_ResourceColor inactiveColor;
    Opt_BlurType type;
} Ark_BackgroundEffectOptions;
typedef struct Opt_BackgroundEffectOptions {
    enum Ark_Tag tag;
    Ark_BackgroundEffectOptions value;
} Opt_BackgroundEffectOptions;
typedef struct Ark_BackgroundBlurStyleOptions {
    Opt_ThemeColorMode colorMode;
    Opt_AdaptiveColor adaptiveColor;
    Opt_Number scale;
    struct Opt_BlurOptions blurOptions;
    Opt_BlurStyleActivePolicy policy;
    struct Opt_ResourceColor inactiveColor;
    Opt_BlurType type;
} Ark_BackgroundBlurStyleOptions;
typedef struct Opt_BackgroundBlurStyleOptions {
    enum Ark_Tag tag;
    Ark_BackgroundBlurStyleOptions value;
} Opt_BackgroundBlurStyleOptions;
typedef struct Union_Position_Alignment {
    Ark_Int32 selector;
    union {
        struct Ark_Position value0;
        Ark_Alignment value1;
    };
} Union_Position_Alignment;
typedef struct Opt_Union_Position_Alignment {
    enum Ark_Tag tag;
    Union_Position_Alignment value;
} Opt_Union_Position_Alignment;
typedef struct Union_SizeOptions_ImageSize {
    Ark_Int32 selector;
    union {
        struct Ark_SizeOptions value0;
        Ark_ImageSize value1;
    };
} Union_SizeOptions_ImageSize;
typedef struct Opt_Union_SizeOptions_ImageSize {
    enum Ark_Tag tag;
    Union_SizeOptions_ImageSize value;
} Opt_Union_SizeOptions_ImageSize;
typedef Ark_Int32 Ark_ImageRepeat;
typedef struct Opt_ImageRepeat {
    enum Ark_Tag tag;
    Ark_ImageRepeat value;
} Opt_ImageRepeat;
typedef struct Ark_PixelRoundPolicy {
    Opt_PixelRoundCalcPolicy start;
    Opt_PixelRoundCalcPolicy top;
    Opt_PixelRoundCalcPolicy end;
    Opt_PixelRoundCalcPolicy bottom;
} Ark_PixelRoundPolicy;
typedef struct Opt_PixelRoundPolicy {
    enum Ark_Tag tag;
    Ark_PixelRoundPolicy value;
} Opt_PixelRoundPolicy;
typedef struct Literal_Opt_Alignment_align {
    Opt_Alignment align;
} Literal_Opt_Alignment_align;
typedef struct Opt_Literal_Opt_Alignment_align {
    enum Ark_Tag tag;
    Literal_Opt_Alignment_align value;
} Opt_Literal_Opt_Alignment_align;
typedef Ark_Int32 Ark_HitTestMode;
typedef struct Opt_HitTestMode {
    enum Ark_Tag tag;
    Ark_HitTestMode value;
} Opt_HitTestMode;
typedef struct Ark_ConstraintSizeOptions {
    Opt_Length minWidth;
    Opt_Length maxWidth;
    Opt_Length minHeight;
    Opt_Length maxHeight;
} Ark_ConstraintSizeOptions;
typedef struct Opt_ConstraintSizeOptions {
    enum Ark_Tag tag;
    Ark_ConstraintSizeOptions value;
} Opt_ConstraintSizeOptions;
typedef struct Union_Array_Rectangle_Rectangle {
    Ark_Int32 selector;
    union {
        struct Array_Rectangle value0;
        struct Ark_Rectangle value1;
    };
} Union_Array_Rectangle_Rectangle;
typedef struct Opt_Union_Array_Rectangle_Rectangle {
    enum Ark_Tag tag;
    Union_Array_Rectangle_Rectangle value;
} Opt_Union_Array_Rectangle_Rectangle;
typedef Ark_Int32 Ark_SafeAreaEdge;
typedef struct Opt_SafeAreaEdge {
    enum Ark_Tag tag;
    Ark_SafeAreaEdge value;
} Opt_SafeAreaEdge;
typedef int32_t Ark_SafeAreaEdge;
typedef struct Array_SafeAreaEdge {
    Ark_SafeAreaEdge* array;
    Ark_Int32 length;
} Array_SafeAreaEdge;
typedef int32_t Ark_SafeAreaEdge;
typedef struct Opt_Array_SafeAreaEdge {
    enum Ark_Tag tag;
    Array_SafeAreaEdge value;
} Opt_Array_SafeAreaEdge;
typedef Ark_Int32 Ark_SafeAreaType;
typedef struct Opt_SafeAreaType {
    enum Ark_Tag tag;
    Ark_SafeAreaType value;
} Opt_SafeAreaType;
typedef int32_t Ark_SafeAreaType;
typedef struct Array_SafeAreaType {
    Ark_SafeAreaType* array;
    Ark_Int32 length;
} Array_SafeAreaType;
typedef int32_t Ark_SafeAreaType;
typedef struct Opt_Array_SafeAreaType {
    enum Ark_Tag tag;
    Array_SafeAreaType value;
} Opt_Array_SafeAreaType;
typedef struct Union_DrawModifier_Undefined {
    Ark_Int32 selector;
    union {
        Ark_DrawModifier value0;
        Ark_Undefined value1;
    };
} Union_DrawModifier_Undefined;
typedef struct Opt_Union_DrawModifier_Undefined {
    enum Ark_Tag tag;
    Union_DrawModifier_Undefined value;
} Opt_Union_DrawModifier_Undefined;

typedef Union_DrawModifier_Undefined Type_CommonMethod_drawModifier_Arg0;
typedef Opt_Union_DrawModifier_Undefined Opt_Type_CommonMethod_drawModifier_Arg0;
typedef Opt_Object Optional;
typedef Union_Array_Rectangle_Rectangle Type_CommonMethod_responseRegion_Arg0;
typedef Opt_Union_Array_Rectangle_Rectangle Opt_Type_CommonMethod_responseRegion_Arg0;
typedef Union_Array_Rectangle_Rectangle Type_CommonMethod_mouseResponseRegion_Arg0;
typedef Opt_Union_Array_Rectangle_Rectangle Opt_Type_CommonMethod_mouseResponseRegion_Arg0;
typedef Union_Number_String Type_CommonMethod_layoutWeight_Arg0;
typedef Opt_Union_Number_String Opt_Type_CommonMethod_layoutWeight_Arg0;
typedef Union_Ark_Padding_Length_LocalizedPadding Type_CommonMethod_padding_Arg0;
typedef Opt_Union_Padding_Length_LocalizedPadding Opt_Type_CommonMethod_padding_Arg0;
typedef Ark_CustomObject LengthMetrics;
typedef Opt_CustomObject Opt_LengthMetrics;
typedef Union_Ark_Padding_Length_LocalizedPadding Type_CommonMethod_margin_Arg0;
typedef Opt_Union_Padding_Length_LocalizedPadding Opt_Type_CommonMethod_margin_Arg0;
typedef Ark_CustomBuilder CustomBuilder;
typedef Literal_Opt_Alignment_align Type_CommonMethod_background_Arg1;
typedef Opt_Literal_Opt_Alignment_align Opt_Type_CommonMethod_background_Arg1;
typedef Ark_ResourceColor ResourceColor;
typedef Union_Ark_ResourceStr_CustomObject Type_CommonMethod_backgroundImage_Arg0;
typedef Opt_Union_ResourceStr_CustomObject Opt_Type_CommonMethod_backgroundImage_Arg0;
typedef Union_SizeOptions_ImageSize Type_CommonMethod_backgroundImageSize_Arg0;
typedef Opt_Union_SizeOptions_ImageSize Opt_Type_CommonMethod_backgroundImageSize_Arg0;
typedef Union_Position_Alignment Type_CommonMethod_backgroundImagePosition_Arg0;
typedef Opt_Union_Position_Alignment Opt_Type_CommonMethod_backgroundImagePosition_Arg0;
typedef Ark_CustomObject VisualEffect;
typedef Opt_CustomObject Opt_VisualEffect;
typedef Ark_CustomObject Filter;
typedef Opt_CustomObject Opt_Filter;
typedef Union_Number_Resource Type_CommonMethod_opacity_Arg0;
typedef Opt_Union_Number_Resource Opt_Type_CommonMethod_opacity_Arg0;
typedef Union_BorderStyle_Ark_EdgeStyles Type_CommonMethod_borderStyle_Arg0;
typedef Opt_Union_BorderStyle_EdgeStyles Opt_Type_CommonMethod_borderStyle_Arg0;
typedef Union_Length_Ark_EdgeWidths_LocalizedEdgeWidths Type_CommonMethod_borderWidth_Arg0;
typedef Opt_Union_Length_EdgeWidths_LocalizedEdgeWidths Opt_Type_CommonMethod_borderWidth_Arg0;
typedef Union_Ark_ResourceColor_Ark_EdgeColors_LocalizedEdgeColors Type_CommonMethod_borderColor_Arg0;
typedef Opt_Union_ResourceColor_Ark_EdgeColors_LocalizedEdgeColors Opt_Type_CommonMethod_borderColor_Arg0;
typedef Union_Length_Ark_BorderRadiuses_LocalizedBorderRadiuses Type_CommonMethod_borderRadius_Arg0;
typedef Opt_Union_Length_BorderRadiuses_LocalizedBorderRadiuses Opt_Type_CommonMethod_borderRadius_Arg0;
typedef Union_OutlineStyle_Ark_EdgeOutlineStyles Type_CommonMethod_outlineStyle_Arg0;
typedef Opt_Union_OutlineStyle_EdgeOutlineStyles Opt_Type_CommonMethod_outlineStyle_Arg0;
typedef Union_Length_Ark_EdgeOutlineWidths Type_CommonMethod_outlineWidth_Arg0;
typedef Opt_Union_Length_EdgeOutlineWidths Opt_Type_CommonMethod_outlineWidth_Arg0;
typedef Union_Ark_ResourceColor_Ark_EdgeColors_LocalizedEdgeColors Type_CommonMethod_outlineColor_Arg0;
typedef Opt_Union_ResourceColor_Ark_EdgeColors_LocalizedEdgeColors Opt_Type_CommonMethod_outlineColor_Arg0;
typedef Union_Length_Ark_OutlineRadiuses Type_CommonMethod_outlineRadius_Arg0;
typedef Opt_Union_Length_OutlineRadiuses Opt_Type_CommonMethod_outlineRadius_Arg0;
typedef Union_Ark_ResourceColor_ColoringStrategy Type_CommonMethod_foregroundColor_Arg0;
typedef Opt_Union_ResourceColor_ColoringStrategy Opt_Type_CommonMethod_foregroundColor_Arg0;
typedef Ark_Function Callback;
typedef Opt_Function Opt_Callback;
typedef Union_TransitionOptions_TransitionEffect Type_CommonMethod_transition_Arg0;
typedef Opt_Union_TransitionOptions_TransitionEffect Opt_Type_CommonMethod_transition_Arg0;
typedef Union_Color_String_Resource Type_CommonMethod_colorBlend_Arg0;
typedef Opt_Union_Color_String_Resource Opt_Type_CommonMethod_colorBlend_Arg0;
typedef Union_Number_InvertOptions Type_CommonMethod_invert_Arg0;
typedef Opt_Union_Number_InvertOptions Opt_Type_CommonMethod_invert_Arg0;
typedef Union_Number_String Type_CommonMethod_hueRotate_Arg0;
typedef Opt_Union_Number_String Opt_Type_CommonMethod_hueRotate_Arg0;
typedef Union_Number_String Type_CommonMethod_flexBasis_Arg0;
typedef Opt_Union_Number_String Opt_Type_CommonMethod_flexBasis_Arg0;
typedef Union_Position_Edges_LocalizedEdges Type_CommonMethod_position_Arg0;
typedef Opt_Union_Position_Edges_LocalizedEdges Opt_Type_CommonMethod_position_Arg0;
typedef Union_Position_LocalizedPosition Type_CommonMethod_markAnchor_Arg0;
typedef Opt_Union_Position_LocalizedPosition Opt_Type_CommonMethod_markAnchor_Arg0;
typedef Union_Position_Edges_LocalizedEdges Type_CommonMethod_offset_Arg0;
typedef Opt_Union_Position_Edges_LocalizedEdges Opt_Type_CommonMethod_offset_Arg0;
typedef Literal_Opt_Union_Number_Literal_Number_span_offset_xs_sm_md_lg Type_CommonMethod_useSizeType_Arg0;
typedef Opt_Literal_Opt_Union_Number_Literal_Number_span_offset_xs_sm_md_lg Opt_Type_CommonMethod_useSizeType_Arg0;
typedef Union_ClickEffect_Ark_Undefined Type_CommonMethod_clickEffect_Arg0;
typedef Opt_Union_ClickEffect_Undefined Opt_Type_CommonMethod_clickEffect_Arg0;
typedef Union_Array_CustomObject_Ark_Undefined Type_CommonMethod_allowDrop_Arg0;
typedef Opt_Union_Array_CustomObject_Undefined Opt_Type_CommonMethod_allowDrop_Arg0;
typedef Union_Ark_CustomBuilder_DragItemInfo_String Type_CommonMethod_dragPreview_Arg0;
typedef Opt_Union_CustomBuilder_DragItemInfo_String Opt_Type_CommonMethod_dragPreview_Arg0;
typedef Union_String_Ark_CustomBuilder_CustomObject Type_CommonMethod_overlay_Arg0;
typedef Opt_Union_String_CustomBuilder_CustomObject Opt_Type_CommonMethod_overlay_Arg0;
typedef Literal_Opt_Union_Number_String_angle_Opt_GradientDirection_direction_Array_Tuple_Ark_ResourceColor_Number_colors_Opt_Boolean_repeating Type_CommonMethod_linearGradient_Arg0;
typedef Opt_Literal_Opt_Union_Number_String_angle_Opt_GradientDirection_direction_Array_Tuple_ResourceColor_Number_colors_Opt_Boolean_repeating Opt_Type_CommonMethod_linearGradient_Arg0;
typedef Literal_Tuple_Length_Length_center_Opt_Union_Number_String_start_end_rotation_Array_Tuple_Ark_ResourceColor_Number_colors_Opt_Boolean_repeating Type_CommonMethod_sweepGradient_Arg0;
typedef Opt_Literal_Tuple_Length_Length_center_Opt_Union_Number_String_start_end_rotation_Array_Tuple_ResourceColor_Number_colors_Opt_Boolean_repeating Opt_Type_CommonMethod_sweepGradient_Arg0;
typedef Literal_Tuple_Length_Length_center_Union_Number_String_radius_Array_Tuple_Ark_ResourceColor_Number_colors_Opt_Boolean_repeating Type_CommonMethod_radialGradient_Arg0;
typedef Opt_Literal_Tuple_Length_Length_center_Union_Number_String_radius_Array_Tuple_ResourceColor_Number_colors_Opt_Boolean_repeating Opt_Type_CommonMethod_radialGradient_Arg0;
typedef Union_ShadowOptions_ShadowStyle Type_CommonMethod_shadow_Arg0;
typedef Opt_Union_ShadowOptions_ShadowStyle Opt_Type_CommonMethod_shadow_Arg0;
typedef Union_BlendMode_CustomObject Type_CommonMethod_advancedBlendMode_Arg0;
typedef Opt_Union_BlendMode_CustomObject Opt_Type_CommonMethod_advancedBlendMode_Arg0;
typedef Union_Boolean_CircleAttribute_EllipseAttribute_PathAttribute_RectAttribute Type_CommonMethod_clip1_Arg0;
typedef Opt_Union_Boolean_CircleAttribute_EllipseAttribute_PathAttribute_RectAttribute Opt_Type_CommonMethod_clip1_Arg0;
typedef Union_CustomObject_CustomObject_CustomObject_CustomObject Type_CommonMethod_clipShape_Arg0;
typedef Opt_Union_CustomObject_CustomObject_CustomObject_CustomObject Opt_Type_CommonMethod_clipShape_Arg0;
typedef Union_CircleAttribute_EllipseAttribute_PathAttribute_RectAttribute_ProgressMask Type_CommonMethod_mask1_Arg0;
typedef Opt_Union_CircleAttribute_EllipseAttribute_PathAttribute_RectAttribute_ProgressMask Opt_Type_CommonMethod_mask1_Arg0;
typedef Union_CustomObject_CustomObject_CustomObject_CustomObject Type_CommonMethod_maskShape_Arg0;
typedef Opt_Union_CustomObject_CustomObject_CustomObject_CustomObject Opt_Type_CommonMethod_maskShape_Arg0;
typedef Union_PopupOptions_CustomPopupOptions Type_CommonMethod_bindPopup_Arg1;
typedef Opt_Union_PopupOptions_CustomPopupOptions Opt_Type_CommonMethod_bindPopup_Arg1;
typedef Union_Array_MenuElement_Ark_CustomBuilder Type_CommonMethod_bindMenu_Arg0;
typedef Opt_Union_Array_MenuElement_CustomBuilder Opt_Type_CommonMethod_bindMenu_Arg0;
typedef Union_Array_MenuElement_Ark_CustomBuilder Type_CommonMethod_bindMenu1_Arg1;
typedef Opt_Union_Array_MenuElement_CustomBuilder Opt_Type_CommonMethod_bindMenu1_Arg1;
typedef Union_String_FunctionKey Type_CommonMethod_keyboardShortcut_Arg0;
typedef Opt_Union_String_FunctionKey Opt_Type_CommonMethod_keyboardShortcut_Arg0;
typedef Ark_Resource Resource;
typedef Literal_CustomObject_want Type_AbilityComponentInterface_setAbilityComponentOptions_Arg0;
typedef Opt_Literal_CustomObject_want Opt_Type_AbilityComponentInterface_setAbilityComponentOptions_Arg0;
typedef Union_String_Number Type_AlphabetIndexerAttribute_itemSize_Arg0;
typedef Opt_Union_String_Number Opt_Type_AlphabetIndexerAttribute_itemSize_Arg0;
typedef Union_SpringMotion_FrictionMotion_ScrollMotion Type_AnimatorAttribute_motion_Arg0;
typedef Opt_Union_SpringMotion_FrictionMotion_ScrollMotion Opt_Type_AnimatorAttribute_motion_Arg0;
typedef Union_Number_String Type_BlankInterface_setBlankOptions_Arg0;
typedef Opt_Union_Number_String Opt_Type_BlankInterface_setBlankOptions_Arg0;
typedef Ark_ResourceStr ResourceStr;
typedef Union_Number_FontWeight_String Type_ButtonAttribute_fontWeight_Arg0;
typedef Opt_Union_Number_FontWeight_String Opt_Type_ButtonAttribute_fontWeight_Arg0;
typedef Union_String_Resource Type_ButtonAttribute_fontFamily_Arg0;
typedef Opt_Union_String_Resource Opt_Type_ButtonAttribute_fontFamily_Arg0;
typedef Ark_CustomObject ContentModifier;
typedef Opt_CustomObject Opt_ContentModifier;
typedef Literal_Literal_Number_year_month_day_date_MonthData_currentData_preData_nextData_Opt_CalendarController_controller Type_CalendarInterface_setCalendarOptions_Arg0;
typedef Opt_Literal_Literal_Number_year_month_day_date_MonthData_currentData_preData_nextData_Opt_CalendarController_controller Opt_Type_CalendarInterface_setCalendarOptions_Arg0;
typedef Ark_Offset Offset;
typedef Union_CanvasRenderingContext2D_DrawingRenderingContext Type_CanvasInterface_setCanvasOptions_Arg0;
typedef Opt_Union_CanvasRenderingContext2D_DrawingRenderingContext Opt_Type_CanvasInterface_setCanvasOptions_Arg0;
typedef Union_CanvasRenderingContext2D_DrawingRenderingContext Type_CanvasInterface_setCanvasOptions1_Arg0;
typedef Opt_Union_CanvasRenderingContext2D_DrawingRenderingContext Opt_Type_CanvasInterface_setCanvasOptions1_Arg0;
typedef Union_Number_String Type_CommonShapeMethod_strokeDashOffset_Arg0;
typedef Opt_Union_Number_String Opt_Type_CommonShapeMethod_strokeDashOffset_Arg0;
typedef Union_Number_String Type_CommonShapeMethod_strokeMiterLimit_Arg0;
typedef Opt_Union_Number_String Opt_Type_CommonShapeMethod_strokeMiterLimit_Arg0;
typedef Union_Number_String_Resource Type_CommonShapeMethod_strokeOpacity_Arg0;
typedef Opt_Union_Number_String_Resource Opt_Type_CommonShapeMethod_strokeOpacity_Arg0;
typedef Union_Number_String_Resource Type_CommonShapeMethod_fillOpacity_Arg0;
typedef Opt_Union_Number_String_Resource Opt_Type_CommonShapeMethod_fillOpacity_Arg0;
typedef Union_ColumnSplitDividerStyle_Ark_Undefined Type_ColumnSplitAttribute_divider_Arg0;
typedef Opt_Union_ColumnSplitDividerStyle_Undefined Opt_Type_ColumnSplitAttribute_divider_Arg0;
typedef Array_Union_Ark_ResourceColor_LinearGradient Array_Union_ResourceColor_LinearGradient;
typedef Union_Number_String Type_DividerAttribute_strokeWidth_Arg0;
typedef Opt_Union_Number_String Opt_Type_DividerAttribute_strokeWidth_Arg0;
typedef Literal_Opt_Union_String_Number_width_height Type_EllipseInterface_setEllipseOptions_Arg0;
typedef Opt_Literal_Opt_Union_String_Number_width_height Opt_Type_EllipseInterface_setEllipseOptions_Arg0;
typedef Literal_Number_width_height Type_FormComponentAttribute_size_Arg0;
typedef Opt_Literal_Number_width_height Opt_Type_FormComponentAttribute_size_Arg0;
typedef Literal_Number_value_Opt_Number_min_max Type_GaugeInterface_setGaugeOptions_Arg0;
typedef Opt_Literal_Number_value_Opt_Number_min_max Opt_Type_GaugeInterface_setGaugeOptions_Arg0;
typedef Union_Ark_ResourceColor_LinearGradient_Array_Tuple_Union_Ark_ResourceColor_LinearGradient_Number Type_GaugeAttribute_colors_Arg0;
typedef Opt_Union_ResourceColor_LinearGradient_Array_Tuple_Union_Ark_ResourceColor_LinearGradient_Number Opt_Type_GaugeAttribute_colors_Arg0;
typedef Union_Color_Number_String Type_ScrollableCommonMethod_scrollBarColor_Arg0;
typedef Opt_Union_Color_Number_String Opt_Type_ScrollableCommonMethod_scrollBarColor_Arg0;
typedef Union_Number_String Type_ScrollableCommonMethod_scrollBarWidth_Arg0;
typedef Opt_Union_Number_String Opt_Type_ScrollableCommonMethod_scrollBarWidth_Arg0;
typedef Union_Number_Resource Type_ScrollableCommonMethod_friction_Arg0;
typedef Opt_Union_Number_Resource Opt_Type_ScrollableCommonMethod_friction_Arg0;
typedef Union_Number_String Type_GridAttribute_scrollBarWidth_Arg0;
typedef Opt_Union_Number_String Opt_Type_GridAttribute_scrollBarWidth_Arg0;
typedef Union_Color_Number_String Type_GridAttribute_scrollBarColor_Arg0;
typedef Opt_Union_Color_Number_String Opt_Type_GridAttribute_scrollBarColor_Arg0;
typedef Union_Number_Resource Type_GridAttribute_friction_Arg0;
typedef Opt_Union_Number_Resource Opt_Type_GridAttribute_friction_Arg0;
typedef Union_Number_GridColColumnOption Type_GridColAttribute_span_Arg0;
typedef Opt_Union_Number_GridColColumnOption Opt_Type_GridColAttribute_span_Arg0;
typedef Union_Number_GridColColumnOption Type_GridColAttribute_gridColOffset_Arg0;
typedef Opt_Union_Number_GridColColumnOption Opt_Type_GridColAttribute_gridColOffset_Arg0;
typedef Union_Number_GridColColumnOption Type_GridColAttribute_order_Arg0;
typedef Opt_Union_Number_GridColColumnOption Opt_Type_GridColAttribute_order_Arg0;
typedef Union_String_Resource Type_HyperlinkInterface_setHyperlinkOptions_Arg0;
typedef Opt_Union_String_Resource Opt_Type_HyperlinkInterface_setHyperlinkOptions_Arg0;
typedef Union_String_Resource Type_HyperlinkInterface_setHyperlinkOptions_Arg1;
typedef Opt_Union_String_Resource Opt_Type_HyperlinkInterface_setHyperlinkOptions_Arg1;
typedef Union_Color_Number_String_Resource Type_HyperlinkAttribute_color_Arg0;
typedef Opt_Union_Color_Number_String_Resource Opt_Type_HyperlinkAttribute_color_Arg0;
typedef Union_CustomObject_Ark_ResourceStr_CustomObject Type_ImageInterface_setImageOptions_Arg0;
typedef Opt_Union_CustomObject_ResourceStr_CustomObject Opt_Type_ImageInterface_setImageOptions_Arg0;
typedef Union_CustomObject_Ark_ResourceStr_CustomObject_ImageContent Type_ImageInterface_setImageOptions1_Arg0;
typedef Opt_Union_CustomObject_ResourceStr_CustomObject_ImageContent Opt_Type_ImageInterface_setImageOptions1_Arg0;
typedef Union_CustomObject_Ark_ResourceStr_CustomObject Type_ImageInterface_setImageOptions2_Arg0;
typedef Opt_Union_CustomObject_ResourceStr_CustomObject Opt_Type_ImageInterface_setImageOptions2_Arg0;
typedef Union_String_Resource_CustomObject Type_ImageAttribute_alt_Arg0;
typedef Opt_Union_String_Resource_CustomObject Opt_Type_ImageAttribute_alt_Arg0;
typedef Literal_Number_width_height Type_ImageAttribute_sourceSize_Arg0;
typedef Opt_Literal_Number_width_height Opt_Type_ImageAttribute_sourceSize_Arg0;
typedef Union_ColorFilter_CustomObject Type_ImageAttribute_colorFilter_Arg0;
typedef Opt_Union_ColorFilter_CustomObject Opt_Type_ImageAttribute_colorFilter_Arg0;
typedef Ark_CustomObject ResolutionQuality;
typedef Opt_CustomObject Opt_ResolutionQuality;
typedef Union_Ark_ResourceStr_CustomObject Type_ImageSpanInterface_setImageSpanOptions_Arg0;
typedef Opt_Union_ResourceStr_CustomObject Opt_Type_ImageSpanInterface_setImageSpanOptions_Arg0;
typedef Union_ColorFilter_CustomObject Type_ImageSpanAttribute_colorFilter_Arg0;
typedef Opt_Union_ColorFilter_CustomObject Opt_Type_ImageSpanAttribute_colorFilter_Arg0;
typedef Ark_CustomObject PixelMap;
typedef Opt_CustomObject Opt_PixelMap;
typedef Literal_Opt_Union_String_Number_width_height Type_LineInterface_setLineOptions_Arg0;
typedef Opt_Literal_Opt_Union_String_Number_width_height Opt_Type_LineInterface_setLineOptions_Arg0;
typedef Union_Number_Ark_LengthConstrain Type_ListAttribute_lanes_Arg0;
typedef Opt_Union_Number_LengthConstrain Opt_Type_ListAttribute_lanes_Arg0;
typedef Union_ListDividerOptions_Ark_Undefined Type_ListAttribute_divider_Arg0;
typedef Opt_Union_ListDividerOptions_Undefined Opt_Type_ListAttribute_divider_Arg0;
typedef Union_Number_Resource Type_ListAttribute_friction_Arg0;
typedef Opt_Union_Number_Resource Opt_Type_ListAttribute_friction_Arg0;
typedef Union_Boolean_EditMode Type_ListItemAttribute_editable_Arg0;
typedef Opt_Union_Boolean_EditMode Opt_Type_ListItemAttribute_editable_Arg0;
typedef Union_ListDividerOptions_Ark_Undefined Type_ListItemGroupAttribute_divider_Arg0;
typedef Opt_Union_ListDividerOptions_Undefined Opt_Type_ListItemGroupAttribute_divider_Arg0;
typedef Union_Position_Edges_LocalizedEdges Type_SecurityComponentMethod_offset_Arg0;
typedef Opt_Union_Position_Edges_LocalizedEdges Opt_Type_SecurityComponentMethod_offset_Arg0;
typedef Union_Number_FontWeight_String Type_SecurityComponentMethod_fontWeight_Arg0;
typedef Opt_Union_Number_FontWeight_String Opt_Type_SecurityComponentMethod_fontWeight_Arg0;
typedef Union_String_Resource Type_SecurityComponentMethod_fontFamily_Arg0;
typedef Opt_Union_String_Resource Opt_Type_SecurityComponentMethod_fontFamily_Arg0;
typedef Union_Ark_Padding_Length Type_SecurityComponentMethod_padding_Arg0;
typedef Opt_Union_Padding_Length Opt_Type_SecurityComponentMethod_padding_Arg0;
typedef Literal_Boolean_start_Opt_Number_step_loop_Opt_Boolean_fromStart_String_src Type_MarqueeInterface_setMarqueeOptions_Arg0;
typedef Opt_Literal_Boolean_start_Opt_Number_step_loop_Opt_Boolean_fromStart_String_src Opt_Type_MarqueeInterface_setMarqueeOptions_Arg0;
typedef Union_Number_FontWeight_String Type_MarqueeAttribute_fontWeight_Arg0;
typedef Opt_Union_Number_FontWeight_String Opt_Type_MarqueeAttribute_fontWeight_Arg0;
typedef Union_String_Resource Type_MarqueeAttribute_fontFamily_Arg0;
typedef Opt_Union_String_Resource Opt_Type_MarqueeAttribute_fontFamily_Arg0;
typedef Union_CustomObject_Ark_ResourceStr_CustomObject_ASTCResource Type_MediaCachedImageInterface_setMediaCachedImageOptions_Arg0;
typedef Opt_Union_CustomObject_ResourceStr_CustomObject_ASTCResource Opt_Type_MediaCachedImageInterface_setMediaCachedImageOptions_Arg0;
typedef Union_Length_Ark_BorderRadiuses Type_MenuAttribute_radius_Arg0;
typedef Opt_Union_Length_BorderRadiuses Opt_Type_MenuAttribute_radius_Arg0;
typedef Union_DividerStyleOptions_Undefined Type_MenuAttribute_menuItemDivider_Arg0;
typedef Opt_Union_DividerStyleOptions_Undefined Opt_Type_MenuAttribute_menuItemDivider_Arg0;
typedef Union_DividerStyleOptions_Undefined Type_MenuAttribute_menuItemGroupDivider_Arg0;
typedef Opt_Union_DividerStyleOptions_Undefined Opt_Type_MenuAttribute_menuItemGroupDivider_Arg0;
typedef Union_MenuItemOptions_Ark_CustomBuilder Type_MenuItemInterface_setMenuItemOptions_Arg0;
typedef Opt_Union_MenuItemOptions_CustomBuilder Opt_Type_MenuItemInterface_setMenuItemOptions_Arg0;
typedef Union_Boolean_Ark_ResourceStr_CustomObject Type_MenuItemAttribute_selectIcon_Arg0;
typedef Opt_Union_Boolean_ResourceStr_CustomObject Opt_Type_MenuItemAttribute_selectIcon_Arg0;
typedef Union_String_Ark_CustomBuilder_NavDestinationCommonTitle_NavDestinationCustomTitle Type_NavDestinationAttribute_title_Arg0;
typedef Opt_Union_String_CustomBuilder_NavDestinationCommonTitle_NavDestinationCustomTitle Opt_Type_NavDestinationAttribute_title_Arg0;
typedef Union_Ark_ResourceStr_CustomObject_CustomObject Type_NavDestinationAttribute_backButtonIcon_Arg0;
typedef Opt_Union_ResourceStr_CustomObject_CustomObject Opt_Type_NavDestinationAttribute_backButtonIcon_Arg0;
typedef Union_Array_NavigationMenuItem_Ark_CustomBuilder Type_NavDestinationAttribute_menus_Arg0;
typedef Opt_Union_Array_NavigationMenuItem_CustomBuilder Opt_Type_NavDestinationAttribute_menus_Arg0;
typedef Tuple_Length_Length Type_NavigationAttribute_navBarWidthRange_Arg0;
typedef Opt_Tuple_Length_Length Opt_Type_NavigationAttribute_navBarWidthRange_Arg0;
typedef Union_String_CustomObject_Resource_CustomObject Type_NavigationAttribute_backButtonIcon_Arg0;
typedef Opt_Union_String_CustomObject_Resource_CustomObject Opt_Type_NavigationAttribute_backButtonIcon_Arg0;
typedef Union_Ark_ResourceStr_Ark_CustomBuilder_NavigationCommonTitle_NavigationCustomTitle Type_NavigationAttribute_title_Arg0;
typedef Opt_Union_ResourceStr_Ark_CustomBuilder_NavigationCommonTitle_NavigationCustomTitle Opt_Type_NavigationAttribute_title_Arg0;
typedef Union_Array_NavigationMenuItem_Ark_CustomBuilder Type_NavigationAttribute_menus_Arg0;
typedef Opt_Union_Array_NavigationMenuItem_CustomBuilder Opt_Type_NavigationAttribute_menus_Arg0;
typedef Union_CustomObject_Ark_CustomBuilder Type_NavigationAttribute_toolBar_Arg0;
typedef Opt_Union_CustomObject_CustomBuilder Opt_Type_NavigationAttribute_toolBar_Arg0;
typedef Union_Array_ToolbarItem_Ark_CustomBuilder Type_NavigationAttribute_toolbarConfiguration_Arg0;
typedef Opt_Union_Array_ToolbarItem_CustomBuilder Opt_Type_NavigationAttribute_toolbarConfiguration_Arg0;
typedef Literal_String_target_Opt_NavigationType_type Type_NavigatorInterface_setNavigatorOptions_Arg0;
typedef Opt_Literal_String_target_Opt_NavigationType_type Opt_Type_NavigatorInterface_setNavigatorOptions_Arg0;
typedef Union_Length_PanelHeight Type_PanelAttribute_customHeight_Arg0;
typedef Opt_Union_Length_PanelHeight Opt_Type_PanelAttribute_customHeight_Arg0;
typedef Union_Number_String Type_PanelAttribute_fullHeight_Arg0;
typedef Opt_Union_Number_String Opt_Type_PanelAttribute_fullHeight_Arg0;
typedef Union_Number_String Type_PanelAttribute_halfHeight_Arg0;
typedef Opt_Union_Number_String Opt_Type_PanelAttribute_halfHeight_Arg0;
typedef Union_Number_String Type_PanelAttribute_miniHeight_Arg0;
typedef Opt_Union_Number_String Opt_Type_PanelAttribute_miniHeight_Arg0;
typedef Literal_Opt_Union_Number_String_width_height_Opt_String_commands Type_PathInterface_setPathOptions_Arg0;
typedef Opt_Literal_Opt_Union_Number_String_width_height_Opt_String_commands Opt_Type_PathInterface_setPathOptions_Arg0;
typedef Union_Number_String Type_PatternLockAttribute_pathStrokeWidth_Arg0;
typedef Opt_Union_Number_String Opt_Type_PatternLockAttribute_pathStrokeWidth_Arg0;
typedef Literal_PluginComponentTemplate_template_CustomObject_data Type_PluginComponentInterface_setPluginComponentOptions_Arg0;
typedef Opt_Literal_PluginComponentTemplate_template_CustomObject_data Opt_Type_PluginComponentInterface_setPluginComponentOptions_Arg0;
typedef Literal_Opt_Union_String_Number_width_height Type_PolygonInterface_setPolygonOptions_Arg0;
typedef Opt_Literal_Opt_Union_String_Number_width_height Opt_Type_PolygonInterface_setPolygonOptions_Arg0;
typedef Literal_Opt_Union_String_Number_width_height Type_PolylineInterface_setPolylineOptions_Arg0;
typedef Opt_Literal_Opt_Union_String_Number_width_height Opt_Type_PolylineInterface_setPolylineOptions_Arg0;
typedef Union_Number_Resource Type_QRCodeAttribute_contentOpacity_Arg0;
typedef Opt_Union_Number_Resource Opt_Type_QRCodeAttribute_contentOpacity_Arg0;
typedef Union_Literal_Opt_Union_Number_String_width_height_Opt_Union_Number_String_Array_CustomObject_radius_Literal_Opt_Union_Number_String_width_height_radiusWidth_radiusHeight Type_RectInterface_setRectOptions_Arg0;
typedef Opt_Union_Literal_Opt_Union_Number_String_width_height_Opt_Union_Number_String_Array_CustomObject_radius_Literal_Opt_Union_Number_String_width_height_radiusWidth_radiusHeight Opt_Type_RectInterface_setRectOptions_Arg0;
typedef Union_Number_String Type_RectAttribute_radiusWidth_Arg0;
typedef Opt_Union_Number_String Opt_Type_RectAttribute_radiusWidth_Arg0;
typedef Union_Number_String Type_RectAttribute_radiusHeight_Arg0;
typedef Opt_Union_Number_String Opt_Type_RectAttribute_radiusHeight_Arg0;
typedef Union_Number_String_Array_CustomObject Type_RectAttribute_radius_Arg0;
typedef Opt_Union_Number_String_Array_CustomObject Opt_Type_RectAttribute_radius_Arg0;
typedef Union_ResponseType_RichEditorResponseType Type_RichEditorAttribute_bindSelectionMenu_Arg2;
typedef Opt_Union_ResponseType_RichEditorResponseType Opt_Type_RichEditorAttribute_bindSelectionMenu_Arg2;
typedef Union_Color_Number_String Type_ScrollAttribute_scrollBarColor_Arg0;
typedef Opt_Union_Color_Number_String Opt_Type_ScrollAttribute_scrollBarColor_Arg0;
typedef Union_Number_String Type_ScrollAttribute_scrollBarWidth_Arg0;
typedef Opt_Union_Number_String Opt_Type_ScrollAttribute_scrollBarWidth_Arg0;
typedef Union_Number_Resource Type_ScrollAttribute_friction_Arg0;
typedef Opt_Union_Number_Resource Opt_Type_ScrollAttribute_friction_Arg0;
typedef Literal_Opt_String_value_icon_Ark_ResourceStr_placeholder_Opt_SearchController_controller Type_SearchInterface_setSearchOptions_Arg0;
typedef Opt_Literal_Opt_String_value_icon_ResourceStr_placeholder_Opt_SearchController_controller Opt_Type_SearchInterface_setSearchOptions_Arg0;
typedef Union_IconOptions_CustomObject Type_SearchAttribute_searchIcon_Arg0;
typedef Opt_Union_IconOptions_CustomObject Opt_Type_SearchAttribute_searchIcon_Arg0;
typedef Union_CancelButtonOptions_CancelButtonSymbolOptions Type_SearchAttribute_cancelButton_Arg0;
typedef Opt_Union_CancelButtonOptions_CancelButtonSymbolOptions Opt_Type_SearchAttribute_cancelButton_Arg0;
typedef Ark_CustomObject SymbolGlyphModifier;
typedef Opt_CustomObject Opt_SymbolGlyphModifier;
typedef Union_Number_String_Resource Type_SearchAttribute_minFontSize_Arg0;
typedef Opt_Union_Number_String_Resource Opt_Type_SearchAttribute_minFontSize_Arg0;
typedef Union_Number_String_Resource Type_SearchAttribute_maxFontSize_Arg0;
typedef Opt_Union_Number_String_Resource Opt_Type_SearchAttribute_maxFontSize_Arg0;
typedef Union_Number_String_Resource Type_SearchAttribute_letterSpacing_Arg0;
typedef Opt_Union_Number_String_Resource Opt_Type_SearchAttribute_letterSpacing_Arg0;
typedef Union_Number_String_Resource Type_SearchAttribute_lineHeight_Arg0;
typedef Opt_Union_Number_String_Resource Opt_Type_SearchAttribute_lineHeight_Arg0;
typedef Union_Number_Resource Type_SelectAttribute_selected_Arg0;
typedef Opt_Union_Number_Resource Opt_Type_SelectAttribute_selected_Arg0;
typedef Union_Length_OptionWidthMode Type_SelectAttribute_optionWidth_Arg0;
typedef Opt_Union_Length_OptionWidthMode Opt_Type_SelectAttribute_optionWidth_Arg0;
typedef Union_Opt_DividerOptions_Ark_Undefined Type_SelectAttribute_divider_Arg0;
typedef Opt_Union_Opt_DividerOptions_Undefined Opt_Type_SelectAttribute_divider_Arg0;
typedef Literal_Opt_Union_Number_String_x_y_width_height Type_ShapeAttribute_viewPort_Arg0;
typedef Opt_Literal_Opt_Union_Number_String_x_y_width_height Opt_Type_ShapeAttribute_viewPort_Arg0;
typedef Union_Number_String Type_ShapeAttribute_strokeDashOffset_Arg0;
typedef Opt_Union_Number_String Opt_Type_ShapeAttribute_strokeDashOffset_Arg0;
typedef Union_Number_String Type_ShapeAttribute_strokeMiterLimit_Arg0;
typedef Opt_Union_Number_String Opt_Type_ShapeAttribute_strokeMiterLimit_Arg0;
typedef Union_Number_String_Resource Type_ShapeAttribute_strokeOpacity_Arg0;
typedef Opt_Union_Number_String_Resource Opt_Type_ShapeAttribute_strokeOpacity_Arg0;
typedef Union_Number_String_Resource Type_ShapeAttribute_fillOpacity_Arg0;
typedef Opt_Union_Number_String_Resource Opt_Type_ShapeAttribute_fillOpacity_Arg0;
typedef Union_Number_String Type_ShapeAttribute_strokeWidth_Arg0;
typedef Opt_Union_Number_String Opt_Type_ShapeAttribute_strokeWidth_Arg0;
typedef Union_Ark_ResourceColor_LinearGradient Type_SliderAttribute_trackColor_Arg0;
typedef Opt_Union_ResourceColor_LinearGradient Opt_Type_SliderAttribute_trackColor_Arg0;
typedef Union_String_Resource Type_SpanInterface_setSpanOptions_Arg0;
typedef Opt_Union_String_Resource Opt_Type_SpanInterface_setSpanOptions_Arg0;
typedef Union_Number_String_Resource Type_SpanAttribute_fontSize_Arg0;
typedef Opt_Union_Number_String_Resource Opt_Type_SpanAttribute_fontSize_Arg0;
typedef Union_Number_FontWeight_String Type_SpanAttribute_fontWeight_Arg0;
typedef Opt_Union_Number_FontWeight_String Opt_Type_SpanAttribute_fontWeight_Arg0;
typedef Union_String_Resource Type_SpanAttribute_fontFamily_Arg0;
typedef Opt_Union_String_Resource Opt_Type_SpanAttribute_fontFamily_Arg0;
typedef Union_Number_String Type_SpanAttribute_letterSpacing_Arg0;
typedef Opt_Union_Number_String Opt_Type_SpanAttribute_letterSpacing_Arg0;
typedef Union_ShadowOptions_Array_ShadowOptions Type_SpanAttribute_textShadow_Arg0;
typedef Opt_Union_ShadowOptions_Array_ShadowOptions Opt_Type_SpanAttribute_textShadow_Arg0;
typedef Literal_Opt_Number_index Type_StepperInterface_setStepperOptions_Arg0;
typedef Opt_Literal_Opt_Number_index Opt_Type_StepperInterface_setStepperOptions_Arg0;
typedef Union_DotIndicator_DigitIndicator_Boolean Type_SwiperAttribute_indicator_Arg0;
typedef Opt_Union_DotIndicator_DigitIndicator_Boolean Opt_Type_SwiperAttribute_indicator_Arg0;
typedef Union_ArrowStyle_Boolean Type_SwiperAttribute_displayArrow_Arg0;
typedef Opt_Union_ArrowStyle_Boolean Opt_Type_SwiperAttribute_displayArrow_Arg0;
typedef Union_Number_String Type_SwiperAttribute_itemSpace_Arg0;
typedef Opt_Union_Number_String Opt_Type_SwiperAttribute_itemSpace_Arg0;
typedef Union_Number_String_Ark_SwiperAutoFill Type_SwiperAttribute_displayCount_Arg0;
typedef Opt_Union_Number_String_SwiperAutoFill Opt_Type_SwiperAttribute_displayCount_Arg0;
typedef Union_Curve_String_ICurve Type_SwiperAttribute_curve_Arg0;
typedef Opt_Union_Curve_String_ICurve Opt_Type_SwiperAttribute_curve_Arg0;
typedef Union_Number_String_Resource Type_SymbolGlyphAttribute_fontSize_Arg0;
typedef Opt_Union_Number_String_Resource Opt_Type_SymbolGlyphAttribute_fontSize_Arg0;
typedef Array_Ark_ResourceColor Array_ResourceColor;
typedef Union_Number_FontWeight_String Type_SymbolGlyphAttribute_fontWeight_Arg0;
typedef Opt_Union_Number_FontWeight_String Opt_Type_SymbolGlyphAttribute_fontWeight_Arg0;
typedef Union_Number_String_Resource Type_SymbolSpanAttribute_fontSize_Arg0;
typedef Opt_Union_Number_String_Resource Opt_Type_SymbolSpanAttribute_fontSize_Arg0;
typedef Union_Number_FontWeight_String Type_SymbolSpanAttribute_fontWeight_Arg0;
typedef Opt_Union_Number_FontWeight_String Opt_Type_SymbolSpanAttribute_fontWeight_Arg0;
typedef Literal_Opt_BarPosition_barPosition_Opt_Number_index_Opt_TabsController_controller Type_TabsInterface_setTabsOptions_Arg0;
typedef Opt_Literal_Opt_BarPosition_barPosition_Opt_Number_index_Opt_TabsController_controller Opt_Type_TabsInterface_setTabsOptions_Arg0;
typedef Union_DividerStyle_Ark_Undefined Type_TabsAttribute_divider_Arg0;
typedef Opt_Union_DividerStyle_Undefined Opt_Type_TabsAttribute_divider_Arg0;
typedef Union_String_Resource_Ark_CustomBuilder_Literal_Opt_Union_String_Resource_icon_text Type_TabContentAttribute_tabBar_Arg0;
typedef Opt_Union_String_Resource_CustomBuilder_Literal_Opt_Union_String_Resource_icon_text Opt_Type_TabContentAttribute_tabBar_Arg0;
typedef Union_SubTabBarStyle_BottomTabBarStyle Type_TabContentAttribute_tabBar1_Arg0;
typedef Opt_Union_SubTabBarStyle_BottomTabBarStyle Opt_Type_TabContentAttribute_tabBar1_Arg0;
typedef Union_String_Resource Type_TextInterface_setTextOptions_Arg0;
typedef Opt_Union_String_Resource Opt_Type_TextInterface_setTextOptions_Arg0;
typedef Union_Number_String_Resource Type_TextAttribute_fontSize_Arg0;
typedef Opt_Union_Number_String_Resource Opt_Type_TextAttribute_fontSize_Arg0;
typedef Union_Number_String_Resource Type_TextAttribute_minFontSize_Arg0;
typedef Opt_Union_Number_String_Resource Opt_Type_TextAttribute_minFontSize_Arg0;
typedef Union_Number_String_Resource Type_TextAttribute_maxFontSize_Arg0;
typedef Opt_Union_Number_String_Resource Opt_Type_TextAttribute_maxFontSize_Arg0;
typedef Union_Number_Resource Type_TextAttribute_minFontScale_Arg0;
typedef Opt_Union_Number_Resource Opt_Type_TextAttribute_minFontScale_Arg0;
typedef Union_Number_Resource Type_TextAttribute_maxFontScale_Arg0;
typedef Opt_Union_Number_Resource Opt_Type_TextAttribute_maxFontScale_Arg0;
typedef Union_Number_FontWeight_String Type_TextAttribute_fontWeight_Arg0;
typedef Opt_Union_Number_FontWeight_String Opt_Type_TextAttribute_fontWeight_Arg0;
typedef Union_Number_FontWeight_String Type_TextAttribute_fontWeight1_Arg0;
typedef Opt_Union_Number_FontWeight_String Opt_Type_TextAttribute_fontWeight1_Arg0;
typedef Union_Number_String_Resource Type_TextAttribute_lineHeight_Arg0;
typedef Opt_Union_Number_String_Resource Opt_Type_TextAttribute_lineHeight_Arg0;
typedef Literal_TextOverflow_overflow Type_TextAttribute_textOverflow_Arg0;
typedef Opt_Literal_TextOverflow_overflow Opt_Type_TextAttribute_textOverflow_Arg0;
typedef Union_String_Resource Type_TextAttribute_fontFamily_Arg0;
typedef Opt_Union_String_Resource Opt_Type_TextAttribute_fontFamily_Arg0;
typedef Union_Number_String Type_TextAttribute_letterSpacing_Arg0;
typedef Opt_Union_Number_String Opt_Type_TextAttribute_letterSpacing_Arg0;
typedef Union_Number_String Type_TextAttribute_baselineOffset_Arg0;
typedef Opt_Union_Number_String Opt_Type_TextAttribute_baselineOffset_Arg0;
typedef Union_ShadowOptions_Array_ShadowOptions Type_TextAttribute_textShadow_Arg0;
typedef Opt_Union_ShadowOptions_Array_ShadowOptions Opt_Type_TextAttribute_textShadow_Arg0;
typedef Union_Number_FontWeight_String Type_TextAreaAttribute_fontWeight_Arg0;
typedef Opt_Union_Number_FontWeight_String Opt_Type_TextAreaAttribute_fontWeight_Arg0;
typedef Union_Number_String_Resource Type_TextAreaAttribute_minFontSize_Arg0;
typedef Opt_Union_Number_String_Resource Opt_Type_TextAreaAttribute_minFontSize_Arg0;
typedef Union_Number_String_Resource Type_TextAreaAttribute_maxFontSize_Arg0;
typedef Opt_Union_Number_String_Resource Opt_Type_TextAreaAttribute_maxFontSize_Arg0;
typedef Union_Number_String_Resource Type_TextAreaAttribute_letterSpacing_Arg0;
typedef Opt_Union_Number_String_Resource Opt_Type_TextAreaAttribute_letterSpacing_Arg0;
typedef Union_Number_String_Resource Type_TextAreaAttribute_lineHeight_Arg0;
typedef Opt_Union_Number_String_Resource Opt_Type_TextAreaAttribute_lineHeight_Arg0;
typedef Literal_Opt_Number_timeZoneOffset_Opt_TextClockController_controller Type_TextClockInterface_setTextClockOptions_Arg0;
typedef Opt_Literal_Opt_Number_timeZoneOffset_Opt_TextClockController_controller Opt_Type_TextClockInterface_setTextClockOptions_Arg0;
typedef Union_Number_FontWeight_String Type_TextClockAttribute_fontWeight_Arg0;
typedef Opt_Union_Number_FontWeight_String Opt_Type_TextClockAttribute_fontWeight_Arg0;
typedef Union_ShadowOptions_Array_ShadowOptions Type_TextClockAttribute_textShadow_Arg0;
typedef Opt_Union_ShadowOptions_Array_ShadowOptions Opt_Type_TextClockAttribute_textShadow_Arg0;
typedef Union_Number_FontWeight_String Type_TextInputAttribute_fontWeight_Arg0;
typedef Opt_Union_Number_FontWeight_String Opt_Type_TextInputAttribute_fontWeight_Arg0;
typedef Union_TextInputStyle_TextContentStyle Type_TextInputAttribute_style_Arg0;
typedef Opt_Union_TextInputStyle_TextContentStyle Opt_Type_TextInputAttribute_style_Arg0;
typedef Union_Ark_ResourceStr_Undefined Type_TextInputAttribute_showError_Arg0;
typedef Opt_Union_ResourceStr_Undefined Opt_Type_TextInputAttribute_showError_Arg0;
typedef Union_Ark_ResourceColor_UnderlineColor_Undefined Type_TextInputAttribute_underlineColor_Arg0;
typedef Opt_Union_ResourceColor_UnderlineColor_Undefined Opt_Type_TextInputAttribute_underlineColor_Arg0;
typedef Literal_Opt_CancelButtonStyle_style_Opt_IconOptions_icon Type_TextInputAttribute_cancelButton_Arg0;
typedef Opt_Literal_Opt_CancelButtonStyle_style_Opt_IconOptions_icon Opt_Type_TextInputAttribute_cancelButton_Arg0;
typedef Union_Number_String_Resource Type_TextInputAttribute_minFontSize_Arg0;
typedef Opt_Union_Number_String_Resource Opt_Type_TextInputAttribute_minFontSize_Arg0;
typedef Union_Number_String_Resource Type_TextInputAttribute_maxFontSize_Arg0;
typedef Opt_Union_Number_String_Resource Opt_Type_TextInputAttribute_maxFontSize_Arg0;
typedef Union_Number_String_Resource Type_TextInputAttribute_letterSpacing_Arg0;
typedef Opt_Union_Number_String_Resource Opt_Type_TextInputAttribute_letterSpacing_Arg0;
typedef Union_Number_String_Resource Type_TextInputAttribute_lineHeight_Arg0;
typedef Opt_Union_Number_String_Resource Opt_Type_TextInputAttribute_lineHeight_Arg0;
typedef Union_Number_String Type_TextPickerAttribute_defaultPickerItemHeight_Arg0;
typedef Opt_Union_Number_String Opt_Type_TextPickerAttribute_defaultPickerItemHeight_Arg0;
typedef Union_Number_Array_Number Type_TextPickerAttribute_selectedIndex_Arg0;
typedef Opt_Union_Number_Array_Number Opt_Type_TextPickerAttribute_selectedIndex_Arg0;
typedef Union_DividerOptions_Ark_Undefined Type_TextPickerAttribute_divider_Arg0;
typedef Opt_Union_DividerOptions_Undefined Opt_Type_TextPickerAttribute_divider_Arg0;
typedef Union_Number_FontWeight_String Type_TextTimerAttribute_fontWeight_Arg0;
typedef Opt_Union_Number_FontWeight_String Opt_Type_TextTimerAttribute_fontWeight_Arg0;
typedef Union_ShadowOptions_Array_ShadowOptions Type_TextTimerAttribute_textShadow_Arg0;
typedef Opt_Union_ShadowOptions_Array_ShadowOptions Opt_Type_TextTimerAttribute_textShadow_Arg0;
typedef Ark_CustomObject DateTimeOptions;
typedef Opt_CustomObject Opt_DateTimeOptions;
typedef Union_NestedScrollOptions_NestedScrollOptionsExt Type_WebAttribute_nestedScroll_Arg0;
typedef Opt_Union_NestedScrollOptions_NestedScrollOptionsExt Opt_Type_WebAttribute_nestedScroll_Arg0;
typedef Literal_String_id_type_Opt_String_libraryname_Opt_XComponentController_controller Type_XComponentInterface_setXComponentOptions_Arg0;
typedef Opt_Literal_String_id_type_Opt_String_libraryname_Opt_XComponentController_controller Opt_Type_XComponentInterface_setXComponentOptions_Arg0;
typedef Literal_String_id_XComponentType_type_Opt_String_libraryname_Opt_XComponentController_controller Type_XComponentInterface_setXComponentOptions1_Arg0;
typedef Opt_Literal_String_id_XComponentType_type_Opt_String_libraryname_Opt_XComponentController_controller Opt_Type_XComponentInterface_setXComponentOptions1_Arg0;
typedef Union_DividerStyle_Ark_Undefined Type_SideBarContainerAttribute_divider_Arg0;
typedef Opt_Union_DividerStyle_Undefined Opt_Type_SideBarContainerAttribute_divider_Arg0;
typedef Union_Number_Resource Type_WaterFlowAttribute_friction_Arg0;
typedef Opt_Union_Number_Resource Opt_Type_WaterFlowAttribute_friction_Arg0;
typedef Ark_CustomObject DrawContext;
typedef Opt_CustomObject Opt_DrawContext;
typedef Ark_CustomObject T;
typedef Opt_CustomObject Opt_T;
typedef Ark_ImageSmoothingQuality ImageSmoothingQuality;
typedef Ark_CanvasLineCap CanvasLineCap;
typedef Ark_CanvasLineJoin CanvasLineJoin;
typedef Ark_CanvasDirection CanvasDirection;
typedef Ark_CanvasTextAlign CanvasTextAlign;
typedef Ark_CanvasTextBaseline CanvasTextBaseline;
typedef Union_ImageBitmap_CustomObject Union_ImageBitmap_PixelMap;
typedef Opt_Union_ImageBitmap_CustomObject Opt_Union_ImageBitmap_PixelMap;
typedef Ark_CanvasFillRule CanvasFillRule;
typedef Ark_CustomObject LengthMetricsUnit;
typedef Opt_CustomObject Opt_LengthMetricsUnit;
typedef Union_CustomObject_Ark_ResourceStr Union_PixelMap_ResourceStr;
typedef Opt_Union_CustomObject_ResourceStr Opt_Union_PixelMap_ResourceStr;
typedef Ark_CustomObject RectWidthStyle;
typedef Opt_CustomObject Opt_RectWidthStyle;
typedef Ark_CustomObject RectHeightStyle;
typedef Opt_CustomObject Opt_RectHeightStyle;
typedef Ark_CustomObject WebviewController;
typedef Opt_CustomObject Opt_WebviewController;
typedef Ark_CustomObject Date;
typedef Opt_CustomObject Opt_Date;
typedef Ark_Padding Padding;
typedef Ark_Padding Margin;
typedef Opt_Padding Opt_Margin;
typedef Ark_LocalizedPadding LocalizedMargin;
typedef Opt_LocalizedPadding Opt_LocalizedMargin;
typedef Ark_EdgeWidths EdgeWidths;
typedef Ark_CustomObject DrawingLattice;
typedef Opt_CustomObject Opt_DrawingLattice;
typedef Ark_EdgeColors EdgeColors;
typedef Ark_BorderRadiuses BorderRadiuses;
typedef Ark_EdgeStyles EdgeStyles;
typedef Ark_EdgeOutlineWidths EdgeOutlineWidths;
typedef Ark_OutlineRadiuses OutlineRadiuses;
typedef Ark_EdgeOutlineStyles EdgeOutlineStyles;
typedef Ark_CustomObject ColorMetrics;
typedef Opt_CustomObject Opt_ColorMetrics;
typedef Tuple_Number_Number FractionStop;
typedef Opt_Tuple_Number_Number Opt_FractionStop;
typedef Ark_CustomObject UniformDataType;
typedef Opt_CustomObject Opt_UniformDataType;
typedef Ark_CustomObject ImageModifier;
typedef Opt_CustomObject Opt_ImageModifier;
typedef Ark_CustomObject ComponentContent;
typedef Opt_CustomObject Opt_ComponentContent;
typedef Ark_CustomObject Blender;
typedef Opt_CustomObject Opt_Blender;
typedef Ark_CustomObject CircleShape;
typedef Opt_CustomObject Opt_CircleShape;
typedef Ark_CustomObject EllipseShape;
typedef Opt_CustomObject Opt_EllipseShape;
typedef Ark_CustomObject PathShape;
typedef Opt_CustomObject Opt_PathShape;
typedef Ark_CustomObject RectShape;
typedef Opt_CustomObject Opt_RectShape;
typedef Ark_CustomObject UIContext;
typedef Opt_CustomObject Opt_UIContext;
typedef Ark_CustomObject Scene;
typedef Opt_CustomObject Opt_Scene;
typedef Ark_CustomObject DrawableDescriptor;
typedef Opt_CustomObject Opt_DrawableDescriptor;
typedef Ark_CustomObject DrawingColorFilter;
typedef Opt_CustomObject Opt_DrawingColorFilter;
typedef Ark_LengthConstrain LengthConstrain;
typedef Ark_CustomObject TextModifier;
typedef Opt_CustomObject Opt_TextModifier;
typedef Ark_CustomObject SystemBarStyle;
typedef Opt_CustomObject Opt_SystemBarStyle;
typedef Ark_SwiperAutoFill SwiperAutoFill;
typedef Ark_VP VP;
typedef Ark_StyledStringValue StyledStringValue;
typedef Ark_CustomObject IntentionCode;
typedef Opt_CustomObject Opt_IntentionCode;
typedef Ark_CustomObject WindowStatusType;
typedef Opt_CustomObject Opt_WindowStatusType;
typedef Opt_Length Opt_Dimension;



typedef struct GENERATED_ArkUIAbilityComponentModifier {
    void (*setAbilityComponentOptions)(Ark_NativePointer node,
                                       const Type_AbilityComponentInterface_setAbilityComponentOptions_Arg0* value);
    void (*setOnConnect)(Ark_NativePointer node,
                         Ark_Function callback);
    void (*setOnDisconnect)(Ark_NativePointer node,
                            Ark_Function callback);
} GENERATED_ArkUIAbilityComponentModifier;

typedef struct GENERATED_ArkUIAlphabetIndexerModifier {
    void (*setAlphabetIndexerOptions)(Ark_NativePointer node,
                                      const Ark_AlphabetIndexerOptions* options);
    void (*setOnSelected)(Ark_NativePointer node,
                          Ark_Function callback);
    void (*setColor)(Ark_NativePointer node,
                     const ResourceColor* value);
    void (*setSelectedColor)(Ark_NativePointer node,
                             const ResourceColor* value);
    void (*setPopupColor)(Ark_NativePointer node,
                          const ResourceColor* value);
    void (*setSelectedBackgroundColor)(Ark_NativePointer node,
                                       const ResourceColor* value);
    void (*setPopupBackground)(Ark_NativePointer node,
                               const ResourceColor* value);
    void (*setPopupSelectedColor)(Ark_NativePointer node,
                                  const ResourceColor* value);
    void (*setPopupUnselectedColor)(Ark_NativePointer node,
                                    const ResourceColor* value);
    void (*setPopupItemBackgroundColor)(Ark_NativePointer node,
                                        const ResourceColor* value);
    void (*setUsingPopup)(Ark_NativePointer node,
                          Ark_Boolean value);
    void (*setSelectedFont)(Ark_NativePointer node,
                            const Ark_Font* value);
    void (*setPopupFont)(Ark_NativePointer node,
                         const Ark_Font* value);
    void (*setPopupItemFont)(Ark_NativePointer node,
                             const Ark_Font* value);
    void (*setItemSize)(Ark_NativePointer node,
                        const Type_AlphabetIndexerAttribute_itemSize_Arg0* value);
    void (*setFont)(Ark_NativePointer node,
                    const Ark_Font* value);
    void (*setAlignStyle)(Ark_NativePointer node,
                          Ark_Int32 value,
                          const Opt_Length* offset);
    void (*setOnSelect)(Ark_NativePointer node,
                        Ark_Function callback);
    void (*setOnRequestPopupData)(Ark_NativePointer node,
                                  Ark_Function callback);
    void (*setOnPopupSelect)(Ark_NativePointer node,
                             Ark_Function callback);
    void (*setSelected)(Ark_NativePointer node,
                        const Ark_Number* index);
    void (*setPopupPosition)(Ark_NativePointer node,
                             const Ark_Position* value);
    void (*setAutoCollapse)(Ark_NativePointer node,
                            Ark_Boolean value);
    void (*setPopupItemBorderRadius)(Ark_NativePointer node,
                                     const Ark_Number* value);
    void (*setItemBorderRadius)(Ark_NativePointer node,
                                const Ark_Number* value);
    void (*setPopupBackgroundBlurStyle)(Ark_NativePointer node,
                                        Ark_Int32 value);
    void (*setPopupTitleBackground)(Ark_NativePointer node,
                                    const ResourceColor* value);
    void (*setEnableHapticFeedback)(Ark_NativePointer node,
                                    Ark_Boolean value);
} GENERATED_ArkUIAlphabetIndexerModifier;

typedef struct GENERATED_ArkUIAnimatorModifier {
    void (*setAnimatorOptions)(Ark_NativePointer node,
                               const Ark_String* value);
    void (*setState)(Ark_NativePointer node,
                     Ark_Int32 value);
    void (*setDuration)(Ark_NativePointer node,
                        const Ark_Number* value);
    void (*setCurve)(Ark_NativePointer node,
                     Ark_Int32 value);
    void (*setDelay)(Ark_NativePointer node,
                     const Ark_Number* value);
    void (*setFillMode)(Ark_NativePointer node,
                        Ark_Int32 value);
    void (*setIterations)(Ark_NativePointer node,
                          const Ark_Number* value);
    void (*setPlayMode)(Ark_NativePointer node,
                        Ark_Int32 value);
    void (*setMotion)(Ark_NativePointer node,
                      const Type_AnimatorAttribute_motion_Arg0* value);
    void (*setOnStart)(Ark_NativePointer node,
                       Ark_Function event);
    void (*setOnPause)(Ark_NativePointer node,
                       Ark_Function event);
    void (*setOnRepeat)(Ark_NativePointer node,
                        Ark_Function event);
    void (*setOnCancel)(Ark_NativePointer node,
                        Ark_Function event);
    void (*setOnFinish)(Ark_NativePointer node,
                        Ark_Function event);
    void (*setOnFrame)(Ark_NativePointer node,
                       Ark_Function event);
} GENERATED_ArkUIAnimatorModifier;

typedef struct GENERATED_ArkUIBadgeModifier {
    void (*setBadgeOptions0)(Ark_NativePointer node,
                             const Ark_BadgeParamWithNumber* value);
    void (*setBadgeOptions1)(Ark_NativePointer node,
                             const Ark_BadgeParamWithString* value);
} GENERATED_ArkUIBadgeModifier;

typedef struct GENERATED_ArkUIBlankModifier {
    void (*setBlankOptions)(Ark_NativePointer node,
                            const Opt_Type_BlankInterface_setBlankOptions_Arg0* min);
    void (*setColor)(Ark_NativePointer node,
                     const ResourceColor* value);
} GENERATED_ArkUIBlankModifier;

typedef struct GENERATED_ArkUIButtonModifier {
    void (*setButtonOptions0)(Ark_NativePointer node);
    void (*setButtonOptions1)(Ark_NativePointer node,
                              const Ark_ButtonOptions* options);
    void (*setButtonOptions2)(Ark_NativePointer node,
                              const ResourceStr* label,
                              const Opt_ButtonOptions* options);
    void (*setType)(Ark_NativePointer node,
                    Ark_Int32 value);
    void (*setStateEffect)(Ark_NativePointer node,
                           Ark_Boolean value);
    void (*setButtonStyle)(Ark_NativePointer node,
                           Ark_Int32 value);
    void (*setControlSize)(Ark_NativePointer node,
                           Ark_Int32 value);
    void (*setRole)(Ark_NativePointer node,
                    Ark_Int32 value);
    void (*setFontColor)(Ark_NativePointer node,
                         const ResourceColor* value);
    void (*setFontSize)(Ark_NativePointer node,
                        const Ark_Length* value);
    void (*setFontWeight)(Ark_NativePointer node,
                          const Type_ButtonAttribute_fontWeight_Arg0* value);
    void (*setFontStyle)(Ark_NativePointer node,
                         Ark_Int32 value);
    void (*setFontFamily)(Ark_NativePointer node,
                          const Type_ButtonAttribute_fontFamily_Arg0* value);
    void (*setContentModifier)(Ark_NativePointer node,
                               const Ark_CustomObject* modifier);
    void (*setLabelStyle)(Ark_NativePointer node,
                          const Ark_LabelStyle* value);
} GENERATED_ArkUIButtonModifier;

typedef struct GENERATED_ArkUICalendarModifier {
    void (*setCalendarOptions)(Ark_NativePointer node,
                               const Type_CalendarInterface_setCalendarOptions_Arg0* value);
    void (*setShowLunar)(Ark_NativePointer node,
                         Ark_Boolean value);
    void (*setShowHoliday)(Ark_NativePointer node,
                           Ark_Boolean value);
    void (*setNeedSlide)(Ark_NativePointer node,
                         Ark_Boolean value);
    void (*setStartOfWeek)(Ark_NativePointer node,
                           const Ark_Number* value);
    void (*setOffDays)(Ark_NativePointer node,
                       const Ark_Number* value);
    void (*setDirection)(Ark_NativePointer node,
                         Ark_Int32 value);
    void (*setCurrentDayStyle)(Ark_NativePointer node,
                               const Ark_CurrentDayStyle* value);
    void (*setNonCurrentDayStyle)(Ark_NativePointer node,
                                  const Ark_NonCurrentDayStyle* value);
    void (*setTodayStyle)(Ark_NativePointer node,
                          const Ark_TodayStyle* value);
    void (*setWeekStyle)(Ark_NativePointer node,
                         const Ark_WeekStyle* value);
    void (*setWorkStateStyle)(Ark_NativePointer node,
                              const Ark_WorkStateStyle* value);
    void (*setOnSelectChange)(Ark_NativePointer node,
                              Ark_Function event);
    void (*setOnRequestData)(Ark_NativePointer node,
                             Ark_Function event);
} GENERATED_ArkUICalendarModifier;

typedef struct GENERATED_ArkUICalendarPickerModifier {
    void (*setCalendarPickerOptions)(Ark_NativePointer node,
                                     const Opt_CalendarOptions* options);
    void (*setEdgeAlign)(Ark_NativePointer node,
                         Ark_Int32 alignType,
                         const Opt_Offset* offset);
    void (*setTextStyle)(Ark_NativePointer node,
                         const Ark_PickerTextStyle* value);
    void (*setOnChange)(Ark_NativePointer node,
                        Ark_Function callback);
} GENERATED_ArkUICalendarPickerModifier;

typedef struct GENERATED_ArkUICanvasModifier {
    void (*setCanvasOptions0)(Ark_NativePointer node,
                              const Opt_Type_CanvasInterface_setCanvasOptions_Arg0* context);
    void (*setCanvasOptions1)(Ark_NativePointer node,
                              const Type_CanvasInterface_setCanvasOptions1_Arg0* context,
                              const Ark_ImageAIOptions* imageAIOptions);
    void (*setOnReady)(Ark_NativePointer node,
                       Ark_Function event);
    void (*setEnableAnalyzer)(Ark_NativePointer node,
                              Ark_Boolean enable);
} GENERATED_ArkUICanvasModifier;

typedef struct GENERATED_ArkUICheckboxModifier {
    void (*setCheckboxOptions)(Ark_NativePointer node,
                               const Opt_CheckboxOptions* options);
    void (*setSelect)(Ark_NativePointer node,
                      Ark_Boolean value);
    void (*setSelectedColor)(Ark_NativePointer node,
                             const ResourceColor* value);
    void (*setShape)(Ark_NativePointer node,
                     Ark_Int32 value);
    void (*setUnselectedColor)(Ark_NativePointer node,
                               const ResourceColor* value);
    void (*setMark)(Ark_NativePointer node,
                    const Ark_MarkStyle* value);
    void (*setOnChange)(Ark_NativePointer node,
                        Ark_Function callback);
    void (*setContentModifier)(Ark_NativePointer node,
                               const Ark_CustomObject* modifier);
} GENERATED_ArkUICheckboxModifier;

typedef struct GENERATED_ArkUICheckboxGroupModifier {
    void (*setCheckboxGroupOptions)(Ark_NativePointer node,
                                    const Opt_CheckboxGroupOptions* options);
    void (*setSelectAll)(Ark_NativePointer node,
                         Ark_Boolean value);
    void (*setSelectedColor)(Ark_NativePointer node,
                             const ResourceColor* value);
    void (*setUnselectedColor)(Ark_NativePointer node,
                               const ResourceColor* value);
    void (*setMark)(Ark_NativePointer node,
                    const Ark_MarkStyle* value);
    void (*setOnChange)(Ark_NativePointer node,
                        Ark_Function callback);
    void (*setCheckboxShape)(Ark_NativePointer node,
                             Ark_Int32 value);
} GENERATED_ArkUICheckboxGroupModifier;

typedef struct GENERATED_ArkUICircleModifier {
    void (*setCircleOptions)(Ark_NativePointer node,
                             const Opt_CircleOptions* value);
} GENERATED_ArkUICircleModifier;

typedef struct GENERATED_ArkUIColumnModifier {
    void (*setColumnOptions)(Ark_NativePointer node,
                             const Opt_ColumnOptions* options);
    void (*setAlignItems)(Ark_NativePointer node,
                          Ark_Int32 value);
    void (*setJustifyContent)(Ark_NativePointer node,
                              Ark_Int32 value);
    void (*setPointLight)(Ark_NativePointer node,
                          const Ark_PointLightStyle* value);
    void (*setReverse)(Ark_NativePointer node,
                       const Opt_Boolean* isReversed);
} GENERATED_ArkUIColumnModifier;

typedef struct GENERATED_ArkUIColumnSplitModifier {
    void (*setColumnSplitOptions)(Ark_NativePointer node);
    void (*setResizeable)(Ark_NativePointer node,
                          Ark_Boolean value);
    void (*setDivider)(Ark_NativePointer node,
                       const Type_ColumnSplitAttribute_divider_Arg0* value);
} GENERATED_ArkUIColumnSplitModifier;

typedef struct GENERATED_ArkUICommonMethodModifier {
    void (*setWidth)(Ark_NativePointer node,
                     const Ark_Length* value);
    void (*setHeight)(Ark_NativePointer node,
                      const Ark_Length* value);
    void (*setDrawModifier)(Ark_NativePointer node,
                            const Type_CommonMethod_drawModifier_Arg0* modifier);
    void (*setCustomProperty)(Ark_NativePointer node,
                              const Ark_String* name,
                              const Opt_Object* value);
    void (*setExpandSafeArea)(Ark_NativePointer node,
                              const Opt_Array_SafeAreaType* types,
                              const Opt_Array_SafeAreaEdge* edges);
    void (*setResponseRegion)(Ark_NativePointer node,
                              const Type_CommonMethod_responseRegion_Arg0* value);
    void (*setMouseResponseRegion)(Ark_NativePointer node,
                                   const Type_CommonMethod_mouseResponseRegion_Arg0* value);
    void (*setSize)(Ark_NativePointer node,
                    const Ark_SizeOptions* value);
    void (*setConstraintSize)(Ark_NativePointer node,
                              const Ark_ConstraintSizeOptions* value);
    void (*setTouchable)(Ark_NativePointer node,
                         Ark_Boolean value);
    void (*setHitTestBehavior)(Ark_NativePointer node,
                               Ark_Int32 value);
    void (*setOnChildTouchTest)(Ark_NativePointer node,
                                Ark_Function event);
    void (*setLayoutWeight)(Ark_NativePointer node,
                            const Type_CommonMethod_layoutWeight_Arg0* value);
    void (*setPadding)(Ark_NativePointer node,
                       const Type_CommonMethod_padding_Arg0* value);
    void (*setMargin)(Ark_NativePointer node,
                      const Type_CommonMethod_margin_Arg0* value);
    void (*setBackground)(Ark_NativePointer node,
                          const CustomBuilder* builder,
                          const Opt_Type_CommonMethod_background_Arg1* options);
    void (*setBackgroundColor)(Ark_NativePointer node,
                               const ResourceColor* value);
    void (*setPixelRound)(Ark_NativePointer node,
                          const Ark_PixelRoundPolicy* value);
    void (*setBackgroundImage)(Ark_NativePointer node,
                               const Type_CommonMethod_backgroundImage_Arg0* src,
                               const Opt_ImageRepeat* repeat);
    void (*setBackgroundImageSize)(Ark_NativePointer node,
                                   const Type_CommonMethod_backgroundImageSize_Arg0* value);
    void (*setBackgroundImagePosition)(Ark_NativePointer node,
                                       const Type_CommonMethod_backgroundImagePosition_Arg0* value);
    void (*setBackgroundBlurStyle)(Ark_NativePointer node,
                                   Ark_Int32 value,
                                   const Opt_BackgroundBlurStyleOptions* options);
    void (*setBackgroundEffect)(Ark_NativePointer node,
                                const Ark_BackgroundEffectOptions* options);
    void (*setBackgroundImageResizable)(Ark_NativePointer node,
                                        const Ark_ResizableOptions* value);
    void (*setForegroundEffect)(Ark_NativePointer node,
                                const Ark_ForegroundEffectOptions* options);
    void (*setVisualEffect)(Ark_NativePointer node,
                            const Ark_CustomObject* effect);
    void (*setBackgroundFilter)(Ark_NativePointer node,
                                const Ark_CustomObject* filter);
    void (*setForegroundFilter)(Ark_NativePointer node,
                                const Ark_CustomObject* filter);
    void (*setCompositingFilter)(Ark_NativePointer node,
                                 const Ark_CustomObject* filter);
    void (*setForegroundBlurStyle)(Ark_NativePointer node,
                                   Ark_Int32 value,
                                   const Opt_ForegroundBlurStyleOptions* options);
    void (*setOpacity)(Ark_NativePointer node,
                       const Type_CommonMethod_opacity_Arg0* value);
    void (*setBorder)(Ark_NativePointer node,
                      const Ark_BorderOptions* value);
    void (*setBorderStyle)(Ark_NativePointer node,
                           const Type_CommonMethod_borderStyle_Arg0* value);
    void (*setBorderWidth)(Ark_NativePointer node,
                           const Type_CommonMethod_borderWidth_Arg0* value);
    void (*setBorderColor)(Ark_NativePointer node,
                           const Type_CommonMethod_borderColor_Arg0* value);
    void (*setBorderRadius)(Ark_NativePointer node,
                            const Type_CommonMethod_borderRadius_Arg0* value);
    void (*setBorderImage)(Ark_NativePointer node,
                           const Ark_BorderImageOption* value);
    void (*setOutline)(Ark_NativePointer node,
                       const Ark_OutlineOptions* value);
    void (*setOutlineStyle)(Ark_NativePointer node,
                            const Type_CommonMethod_outlineStyle_Arg0* value);
    void (*setOutlineWidth)(Ark_NativePointer node,
                            const Type_CommonMethod_outlineWidth_Arg0* value);
    void (*setOutlineColor)(Ark_NativePointer node,
                            const Type_CommonMethod_outlineColor_Arg0* value);
    void (*setOutlineRadius)(Ark_NativePointer node,
                             const Type_CommonMethod_outlineRadius_Arg0* value);
    void (*setForegroundColor)(Ark_NativePointer node,
                               const Type_CommonMethod_foregroundColor_Arg0* value);
    void (*setOnClick0)(Ark_NativePointer node,
                        Ark_Function event);
    void (*setOnClick1)(Ark_NativePointer node,
                        Ark_Function event,
                        const Ark_Number* distanceThreshold);
    void (*setOnHover)(Ark_NativePointer node,
                       Ark_Function event);
    void (*setOnAccessibilityHover)(Ark_NativePointer node,
                                    Ark_Function callback);
    void (*setHoverEffect)(Ark_NativePointer node,
                           Ark_Int32 value);
    void (*setOnMouse)(Ark_NativePointer node,
                       Ark_Function event);
    void (*setOnTouch)(Ark_NativePointer node,
                       Ark_Function event);
    void (*setOnKeyEvent)(Ark_NativePointer node,
                          Ark_Function event);
    void (*setOnKeyPreIme)(Ark_NativePointer node,
                           Ark_Function event);
    void (*setFocusable)(Ark_NativePointer node,
                         Ark_Boolean value);
    void (*setOnFocus)(Ark_NativePointer node,
                       Ark_Function event);
    void (*setOnBlur)(Ark_NativePointer node,
                      Ark_Function event);
    void (*setTabIndex)(Ark_NativePointer node,
                        const Ark_Number* index);
    void (*setDefaultFocus)(Ark_NativePointer node,
                            Ark_Boolean value);
    void (*setGroupDefaultFocus)(Ark_NativePointer node,
                                 Ark_Boolean value);
    void (*setFocusOnTouch)(Ark_NativePointer node,
                            Ark_Boolean value);
    void (*setFocusBox)(Ark_NativePointer node,
                        const Ark_FocusBoxStyle* style);
    void (*setFocusScopeId)(Ark_NativePointer node,
                            const Ark_String* id,
                            const Opt_Boolean* isGroup);
    void (*setFocusScopePriority)(Ark_NativePointer node,
                                  const Ark_String* scopeId,
                                  const Opt_FocusPriority* priority);
    void (*setAnimation)(Ark_NativePointer node,
                         const Ark_AnimateParam* value);
    void (*setTransition0)(Ark_NativePointer node,
                           const Type_CommonMethod_transition_Arg0* value);
    void (*setTransition1)(Ark_NativePointer node,
                           const Ark_TransitionEffect* effect,
                           const Opt_Function* onFinish);
    void (*setGesture)(Ark_NativePointer node,
                       const Ark_GestureType* gesture,
                       const Opt_GestureMask* mask);
    void (*setPriorityGesture)(Ark_NativePointer node,
                               const Ark_GestureType* gesture,
                               const Opt_GestureMask* mask);
    void (*setParallelGesture)(Ark_NativePointer node,
                               const Ark_GestureType* gesture,
                               const Opt_GestureMask* mask);
    void (*setBlur)(Ark_NativePointer node,
                    const Ark_Number* value,
                    const Opt_BlurOptions* options);
    void (*setLinearGradientBlur)(Ark_NativePointer node,
                                  const Ark_Number* value,
                                  const Ark_LinearGradientBlurOptions* options);
    void (*setMotionBlur)(Ark_NativePointer node,
                          const Ark_MotionBlurOptions* value);
    void (*setBrightness)(Ark_NativePointer node,
                          const Ark_Number* value);
    void (*setContrast)(Ark_NativePointer node,
                        const Ark_Number* value);
    void (*setGrayscale)(Ark_NativePointer node,
                         const Ark_Number* value);
    void (*setColorBlend)(Ark_NativePointer node,
                          const Type_CommonMethod_colorBlend_Arg0* value);
    void (*setSaturate)(Ark_NativePointer node,
                        const Ark_Number* value);
    void (*setSepia)(Ark_NativePointer node,
                     const Ark_Number* value);
    void (*setInvert)(Ark_NativePointer node,
                      const Type_CommonMethod_invert_Arg0* value);
    void (*setSystemBarEffect)(Ark_NativePointer node);
    void (*setHueRotate)(Ark_NativePointer node,
                         const Type_CommonMethod_hueRotate_Arg0* value);
    void (*setUseShadowBatching)(Ark_NativePointer node,
                                 Ark_Boolean value);
    void (*setUseEffect)(Ark_NativePointer node,
                         Ark_Boolean value);
    void (*setBackdropBlur)(Ark_NativePointer node,
                            const Ark_Number* value,
                            const Opt_BlurOptions* options);
    void (*setRenderGroup)(Ark_NativePointer node,
                           Ark_Boolean value);
    void (*setFreeze)(Ark_NativePointer node,
                      Ark_Boolean value);
    void (*setTranslate)(Ark_NativePointer node,
                         const Ark_TranslateOptions* value);
    void (*setScale)(Ark_NativePointer node,
                     const Ark_ScaleOptions* value);
    void (*setGridSpan)(Ark_NativePointer node,
                        const Ark_Number* value);
    void (*setGridOffset)(Ark_NativePointer node,
                          const Ark_Number* value);
    void (*setRotate)(Ark_NativePointer node,
                      const Ark_RotateOptions* value);
    void (*setTransform)(Ark_NativePointer node,
                         const Ark_CustomObject* value);
    void (*setOnAppear)(Ark_NativePointer node,
                        Ark_Function event);
    void (*setOnDisAppear)(Ark_NativePointer node,
                           Ark_Function event);
    void (*setOnAttach)(Ark_NativePointer node,
                        Ark_Function callback);
    void (*setOnDetach)(Ark_NativePointer node,
                        Ark_Function callback);
    void (*setOnAreaChange)(Ark_NativePointer node,
                            Ark_Function event);
    void (*setVisibility)(Ark_NativePointer node,
                          Ark_Int32 value);
    void (*setFlexGrow)(Ark_NativePointer node,
                        const Ark_Number* value);
    void (*setFlexShrink)(Ark_NativePointer node,
                          const Ark_Number* value);
    void (*setFlexBasis)(Ark_NativePointer node,
                         const Type_CommonMethod_flexBasis_Arg0* value);
    void (*setAlignSelf)(Ark_NativePointer node,
                         Ark_Int32 value);
    void (*setDisplayPriority)(Ark_NativePointer node,
                               const Ark_Number* value);
    void (*setZIndex)(Ark_NativePointer node,
                      const Ark_Number* value);
    void (*setSharedTransition)(Ark_NativePointer node,
                                const Ark_String* id,
                                const Opt_sharedTransitionOptions* options);
    void (*setDirection)(Ark_NativePointer node,
                         Ark_Int32 value);
    void (*setAlign)(Ark_NativePointer node,
                     Ark_Int32 value);
    void (*setPosition)(Ark_NativePointer node,
                        const Type_CommonMethod_position_Arg0* value);
    void (*setMarkAnchor)(Ark_NativePointer node,
                          const Type_CommonMethod_markAnchor_Arg0* value);
    void (*setOffset)(Ark_NativePointer node,
                      const Type_CommonMethod_offset_Arg0* value);
    void (*setEnabled)(Ark_NativePointer node,
                       Ark_Boolean value);
    void (*setUseSizeType)(Ark_NativePointer node,
                           const Type_CommonMethod_useSizeType_Arg0* value);
    void (*setAlignRules0)(Ark_NativePointer node,
                           const Ark_AlignRuleOption* value);
    void (*setAlignRules1)(Ark_NativePointer node,
                           const Ark_LocalizedAlignRuleOptions* alignRule);
    void (*setChainMode)(Ark_NativePointer node,
                         Ark_Int32 direction,
                         Ark_Int32 style);
    void (*setAspectRatio)(Ark_NativePointer node,
                           const Ark_Number* value);
    void (*setClickEffect)(Ark_NativePointer node,
                           const Type_CommonMethod_clickEffect_Arg0* value);
    void (*setOnDragStart)(Ark_NativePointer node,
                           Ark_Function event);
    void (*setOnDragEnter)(Ark_NativePointer node,
                           Ark_Function event);
    void (*setOnDragMove)(Ark_NativePointer node,
                          Ark_Function event);
    void (*setOnDragLeave)(Ark_NativePointer node,
                           Ark_Function event);
    void (*setOnDrop)(Ark_NativePointer node,
                      Ark_Function event);
    void (*setOnDragEnd)(Ark_NativePointer node,
                         Ark_Function event);
    void (*setAllowDrop)(Ark_NativePointer node,
                         const Type_CommonMethod_allowDrop_Arg0* value);
    void (*setDraggable)(Ark_NativePointer node,
                         Ark_Boolean value);
    void (*setDragPreview)(Ark_NativePointer node,
                           const Type_CommonMethod_dragPreview_Arg0* value);
    void (*setDragPreviewOptions)(Ark_NativePointer node,
                                  const Ark_DragPreviewOptions* value,
                                  const Opt_DragInteractionOptions* options);
    void (*setOnPreDrag)(Ark_NativePointer node,
                         Ark_Function callback);
    void (*setOverlay)(Ark_NativePointer node,
                       const Type_CommonMethod_overlay_Arg0* value,
                       const Opt_OverlayOptions* options);
    void (*setLinearGradient)(Ark_NativePointer node,
                              const Type_CommonMethod_linearGradient_Arg0* value);
    void (*setSweepGradient)(Ark_NativePointer node,
                             const Type_CommonMethod_sweepGradient_Arg0* value);
    void (*setRadialGradient)(Ark_NativePointer node,
                              const Type_CommonMethod_radialGradient_Arg0* value);
    void (*setMotionPath)(Ark_NativePointer node,
                          const Ark_MotionPathOptions* value);
    void (*setShadow)(Ark_NativePointer node,
                      const Type_CommonMethod_shadow_Arg0* value);
    void (*setBlendMode)(Ark_NativePointer node,
                         Ark_Int32 value,
                         const Opt_BlendApplyType* type);
    void (*setAdvancedBlendMode)(Ark_NativePointer node,
                                 const Type_CommonMethod_advancedBlendMode_Arg0* effect,
                                 const Opt_BlendApplyType* type);
    void (*setClip0)(Ark_NativePointer node,
                     Ark_Boolean value);
    void (*setClip1)(Ark_NativePointer node,
                     const Type_CommonMethod_clip1_Arg0* value);
    void (*setClipShape)(Ark_NativePointer node,
                         const Type_CommonMethod_clipShape_Arg0* value);
    void (*setMask0)(Ark_NativePointer node,
                     const Ark_Materialized* value);
    void (*setMask1)(Ark_NativePointer node,
                     const Type_CommonMethod_mask1_Arg0* value);
    void (*setMaskShape)(Ark_NativePointer node,
                         const Type_CommonMethod_maskShape_Arg0* value);
    void (*setKey)(Ark_NativePointer node,
                   const Ark_String* value);
    void (*setId)(Ark_NativePointer node,
                  const Ark_String* value);
    void (*setGeometryTransition0)(Ark_NativePointer node,
                                   const Ark_String* id);
    void (*setGeometryTransition1)(Ark_NativePointer node,
                                   const Ark_String* id,
                                   const Opt_GeometryTransitionOptions* options);
    void (*setBindPopup)(Ark_NativePointer node,
                         Ark_Boolean show,
                         const Type_CommonMethod_bindPopup_Arg1* popup);
    void (*setBindMenu0)(Ark_NativePointer node,
                         const Type_CommonMethod_bindMenu_Arg0* content,
                         const Opt_MenuOptions* options);
    void (*setBindMenu1)(Ark_NativePointer node,
                         Ark_Boolean isShow,
                         const Type_CommonMethod_bindMenu1_Arg1* content,
                         const Opt_MenuOptions* options);
    void (*setBindContextMenu0)(Ark_NativePointer node,
                                const CustomBuilder* content,
                                Ark_Int32 responseType,
                                const Opt_ContextMenuOptions* options);
    void (*setBindContextMenu1)(Ark_NativePointer node,
                                Ark_Boolean isShown,
                                const CustomBuilder* content,
                                const Opt_ContextMenuOptions* options);
    void (*setBindContentCover0)(Ark_NativePointer node,
                                 const Opt_Boolean* isShow,
                                 const CustomBuilder* builder,
                                 const Opt_ModalTransition* type);
    void (*setBindContentCover1)(Ark_NativePointer node,
                                 const Opt_Boolean* isShow,
                                 const CustomBuilder* builder,
                                 const Opt_ContentCoverOptions* options);
    void (*setBindSheet)(Ark_NativePointer node,
                         const Opt_Boolean* isShow,
                         const CustomBuilder* builder,
                         const Opt_SheetOptions* options);
    void (*setStateStyles)(Ark_NativePointer node,
                           const Ark_StateStyles* value);
    void (*setRestoreId)(Ark_NativePointer node,
                         const Ark_Number* value);
    void (*setOnVisibleAreaChange)(Ark_NativePointer node,
                                   const Array_Number* ratios,
                                   Ark_Function event);
    void (*setSphericalEffect)(Ark_NativePointer node,
                               const Ark_Number* value);
    void (*setLightUpEffect)(Ark_NativePointer node,
                             const Ark_Number* value);
    void (*setPixelStretchEffect)(Ark_NativePointer node,
                                  const Ark_PixelStretchEffectOptions* options);
    void (*setKeyboardShortcut)(Ark_NativePointer node,
                                const Type_CommonMethod_keyboardShortcut_Arg0* value,
                                const Array_ModifierKey* keys,
                                const Opt_Function* action);
    void (*setAccessibilityGroup)(Ark_NativePointer node,
                                  Ark_Boolean value);
    void (*setAccessibilityText0)(Ark_NativePointer node,
                                  const Ark_String* value);
    void (*setAccessibilityText1)(Ark_NativePointer node,
                                  const Ark_Resource* text);
    void (*setAccessibilityTextHint)(Ark_NativePointer node,
                                     const Ark_String* value);
    void (*setAccessibilityDescription0)(Ark_NativePointer node,
                                         const Ark_String* value);
    void (*setAccessibilityDescription1)(Ark_NativePointer node,
                                         const Ark_Resource* description);
    void (*setAccessibilityLevel)(Ark_NativePointer node,
                                  const Ark_String* value);
    void (*setAccessibilityVirtualNode)(Ark_NativePointer node,
                                        const CustomBuilder* builder);
    void (*setObscured)(Ark_NativePointer node,
                        const Array_ObscuredReasons* reasons);
    void (*setReuseId)(Ark_NativePointer node,
                       const Ark_String* id);
    void (*setRenderFit)(Ark_NativePointer node,
                         Ark_Int32 fitMode);
    void (*setGestureModifier)(Ark_NativePointer node,
                               const Ark_Materialized* modifier);
    void (*setBackgroundBrightness)(Ark_NativePointer node,
                                    const Ark_BackgroundBrightnessOptions* params);
    void (*setOnGestureJudgeBegin)(Ark_NativePointer node,
                                   Ark_Function callback);
    void (*setOnGestureRecognizerJudgeBegin)(Ark_NativePointer node,
                                             Ark_Function callback);
    void (*setShouldBuiltInRecognizerParallelWith)(Ark_NativePointer node,
                                                   Ark_Function callback);
    void (*setMonopolizeEvents)(Ark_NativePointer node,
                                Ark_Boolean monopolize);
    void (*setOnTouchIntercept)(Ark_NativePointer node,
                                Ark_Function callback);
    void (*setOnSizeChange)(Ark_NativePointer node,
                            Ark_Function event);
} GENERATED_ArkUICommonMethodModifier;

typedef struct GENERATED_ArkUICommonShapeMethodModifier {
    void (*setStroke)(Ark_NativePointer node,
                      const ResourceColor* value);
    void (*setFill)(Ark_NativePointer node,
                    const ResourceColor* value);
    void (*setStrokeDashOffset)(Ark_NativePointer node,
                                const Type_CommonShapeMethod_strokeDashOffset_Arg0* value);
    void (*setStrokeLineCap)(Ark_NativePointer node,
                             Ark_Int32 value);
    void (*setStrokeLineJoin)(Ark_NativePointer node,
                              Ark_Int32 value);
    void (*setStrokeMiterLimit)(Ark_NativePointer node,
                                const Type_CommonShapeMethod_strokeMiterLimit_Arg0* value);
    void (*setStrokeOpacity)(Ark_NativePointer node,
                             const Type_CommonShapeMethod_strokeOpacity_Arg0* value);
    void (*setFillOpacity)(Ark_NativePointer node,
                           const Type_CommonShapeMethod_fillOpacity_Arg0* value);
    void (*setStrokeWidth)(Ark_NativePointer node,
                           const Ark_Length* value);
    void (*setAntiAlias)(Ark_NativePointer node,
                         Ark_Boolean value);
    void (*setStrokeDashArray)(Ark_NativePointer node,
                               const Array_CustomObject* value);
} GENERATED_ArkUICommonShapeMethodModifier;

typedef struct GENERATED_ArkUICommonModifier {
    void (*setCommonOptions)(Ark_NativePointer node);
} GENERATED_ArkUICommonModifier;

typedef struct GENERATED_ArkUIScrollableCommonMethodModifier {
    void (*setScrollBar)(Ark_NativePointer node,
                         Ark_Int32 barState);
    void (*setScrollBarColor)(Ark_NativePointer node,
                              const Type_ScrollableCommonMethod_scrollBarColor_Arg0* color);
    void (*setScrollBarWidth)(Ark_NativePointer node,
                              const Type_ScrollableCommonMethod_scrollBarWidth_Arg0* value);
    void (*setEdgeEffect)(Ark_NativePointer node,
                          Ark_Int32 edgeEffect,
                          const Opt_EdgeEffectOptions* options);
    void (*setFadingEdge)(Ark_NativePointer node,
                          const Opt_Boolean* enabled,
                          const Opt_FadingEdgeOptions* options);
    void (*setNestedScroll)(Ark_NativePointer node,
                            const Ark_NestedScrollOptions* value);
    void (*setEnableScrollInteraction)(Ark_NativePointer node,
                                       Ark_Boolean value);
    void (*setFriction)(Ark_NativePointer node,
                        const Type_ScrollableCommonMethod_friction_Arg0* value);
    void (*setOnScroll)(Ark_NativePointer node,
                        Ark_Function event);
    void (*setOnWillScroll)(Ark_NativePointer node,
                            const Ark_CustomObject* stub_for_onWillScroll);
    void (*setOnDidScroll)(Ark_NativePointer node,
                           Ark_Function handler);
    void (*setOnReachStart)(Ark_NativePointer node,
                            Ark_Function event);
    void (*setOnReachEnd)(Ark_NativePointer node,
                          Ark_Function event);
    void (*setOnScrollStart)(Ark_NativePointer node,
                             Ark_Function event);
    void (*setOnScrollStop)(Ark_NativePointer node,
                            Ark_Function event);
    void (*setFlingSpeedLimit)(Ark_NativePointer node,
                               const Ark_Number* speedLimit);
} GENERATED_ArkUIScrollableCommonMethodModifier;

typedef struct GENERATED_ArkUIComponent3DModifier {
    void (*setComponent3DOptions)(Ark_NativePointer node,
                                  const Opt_SceneOptions* sceneOptions);
    void (*setEnvironment)(Ark_NativePointer node,
                           const ResourceStr* uri);
    void (*setCustomRender)(Ark_NativePointer node,
                            const ResourceStr* uri,
                            Ark_Boolean selfRenderUpdate);
    void (*setShader)(Ark_NativePointer node,
                      const ResourceStr* uri);
    void (*setShaderImageTexture)(Ark_NativePointer node,
                                  const ResourceStr* uri);
    void (*setShaderInputBuffer)(Ark_NativePointer node,
                                 const Array_Number* buffer);
    void (*setRenderWidth)(Ark_NativePointer node,
                           const Ark_Length* value);
    void (*setRenderHeight)(Ark_NativePointer node,
                            const Ark_Length* value);
} GENERATED_ArkUIComponent3DModifier;

typedef struct GENERATED_ArkUIContainerSpanModifier {
    void (*setContainerSpanOptions)(Ark_NativePointer node);
    void (*setTextBackgroundStyle)(Ark_NativePointer node,
                                   const Ark_TextBackgroundStyle* style);
} GENERATED_ArkUIContainerSpanModifier;

typedef struct GENERATED_ArkUICounterModifier {
    void (*setCounterOptions)(Ark_NativePointer node);
    void (*setOnInc)(Ark_NativePointer node,
                     Ark_Function event);
    void (*setOnDec)(Ark_NativePointer node,
                     Ark_Function event);
    void (*setEnableDec)(Ark_NativePointer node,
                         Ark_Boolean value);
    void (*setEnableInc)(Ark_NativePointer node,
                         Ark_Boolean value);
} GENERATED_ArkUICounterModifier;

typedef struct GENERATED_ArkUIDataPanelModifier {
    void (*setDataPanelOptions)(Ark_NativePointer node,
                                const Ark_DataPanelOptions* options);
    void (*setCloseEffect)(Ark_NativePointer node,
                           Ark_Boolean value);
    void (*setValueColors)(Ark_NativePointer node,
                           const Array_Union_ResourceColor_LinearGradient* value);
    void (*setTrackBackgroundColor)(Ark_NativePointer node,
                                    const ResourceColor* value);
    void (*setStrokeWidth)(Ark_NativePointer node,
                           const Ark_Length* value);
    void (*setTrackShadow)(Ark_NativePointer node,
                           const Ark_DataPanelShadowOptions* value);
    void (*setContentModifier)(Ark_NativePointer node,
                               const Ark_CustomObject* modifier);
} GENERATED_ArkUIDataPanelModifier;

typedef struct GENERATED_ArkUIDatePickerModifier {
    void (*setDatePickerOptions)(Ark_NativePointer node,
                                 const Opt_DatePickerOptions* options);
    void (*setLunar)(Ark_NativePointer node,
                     Ark_Boolean value);
    void (*setDisappearTextStyle)(Ark_NativePointer node,
                                  const Ark_PickerTextStyle* value);
    void (*setTextStyle)(Ark_NativePointer node,
                         const Ark_PickerTextStyle* value);
    void (*setSelectedTextStyle)(Ark_NativePointer node,
                                 const Ark_PickerTextStyle* value);
    void (*setOnChange)(Ark_NativePointer node,
                        Ark_Function callback);
    void (*setOnDateChange)(Ark_NativePointer node,
                            Ark_Function callback);
} GENERATED_ArkUIDatePickerModifier;

typedef struct GENERATED_ArkUIDividerModifier {
    void (*setDividerOptions)(Ark_NativePointer node);
    void (*setVertical)(Ark_NativePointer node,
                        Ark_Boolean value);
    void (*setColor)(Ark_NativePointer node,
                     const ResourceColor* value);
    void (*setStrokeWidth)(Ark_NativePointer node,
                           const Type_DividerAttribute_strokeWidth_Arg0* value);
    void (*setLineCap)(Ark_NativePointer node,
                       Ark_Int32 value);
} GENERATED_ArkUIDividerModifier;

typedef struct GENERATED_ArkUIEffectComponentModifier {
    void (*setEffectComponentOptions)(Ark_NativePointer node);
} GENERATED_ArkUIEffectComponentModifier;

typedef struct GENERATED_ArkUIEllipseModifier {
    void (*setEllipseOptions)(Ark_NativePointer node,
                              const Opt_Type_EllipseInterface_setEllipseOptions_Arg0* value);
} GENERATED_ArkUIEllipseModifier;

typedef struct GENERATED_ArkUIEmbeddedComponentModifier {
    void (*setEmbeddedComponentOptions)(Ark_NativePointer node,
                                        const Ark_CustomObject* loader,
                                        Ark_Int32 type);
    void (*setOnTerminated)(Ark_NativePointer node,
                            Ark_Function callback);
    void (*setOnError)(Ark_NativePointer node,
                       const Ark_CustomObject* callback);
} GENERATED_ArkUIEmbeddedComponentModifier;

typedef struct GENERATED_ArkUIFlexModifier {
    void (*setFlexOptions)(Ark_NativePointer node,
                           const Opt_FlexOptions* value);
    void (*setPointLight)(Ark_NativePointer node,
                          const Ark_PointLightStyle* value);
} GENERATED_ArkUIFlexModifier;

typedef struct GENERATED_ArkUIFlowItemModifier {
    void (*setFlowItemOptions)(Ark_NativePointer node);
} GENERATED_ArkUIFlowItemModifier;

typedef struct GENERATED_ArkUIFolderStackModifier {
    void (*setFolderStackOptions)(Ark_NativePointer node,
                                  const Opt_FolderStackOptions* options);
    void (*setAlignContent)(Ark_NativePointer node,
                            Ark_Int32 value);
    void (*setOnFolderStateChange)(Ark_NativePointer node,
                                   Ark_Function callback);
    void (*setOnHoverStatusChange)(Ark_NativePointer node,
                                   Ark_Function handler);
    void (*setEnableAnimation)(Ark_NativePointer node,
                               Ark_Boolean value);
    void (*setAutoHalfFold)(Ark_NativePointer node,
                            Ark_Boolean value);
} GENERATED_ArkUIFolderStackModifier;

typedef struct GENERATED_ArkUIFormComponentModifier {
    void (*setFormComponentOptions)(Ark_NativePointer node,
                                    const Ark_FormInfo* value);
    void (*setSize)(Ark_NativePointer node,
                    const Type_FormComponentAttribute_size_Arg0* value);
    void (*setModuleName)(Ark_NativePointer node,
                          const Ark_String* value);
    void (*setDimension)(Ark_NativePointer node,
                         Ark_Int32 value);
    void (*setAllowUpdate)(Ark_NativePointer node,
                           Ark_Boolean value);
    void (*setVisibility)(Ark_NativePointer node,
                          Ark_Int32 value);
    void (*setOnAcquired)(Ark_NativePointer node,
                          Ark_Function callback);
    void (*setOnError)(Ark_NativePointer node,
                       Ark_Function callback);
    void (*setOnRouter)(Ark_NativePointer node,
                        Ark_Function callback);
    void (*setOnUninstall)(Ark_NativePointer node,
                           Ark_Function callback);
    void (*setOnLoad)(Ark_NativePointer node,
                      Ark_Function callback);
} GENERATED_ArkUIFormComponentModifier;

typedef struct GENERATED_ArkUIFormLinkModifier {
    void (*setFormLinkOptions)(Ark_NativePointer node,
                               const Ark_FormLinkOptions* options);
} GENERATED_ArkUIFormLinkModifier;

typedef struct GENERATED_ArkUIGaugeModifier {
    void (*setGaugeOptions)(Ark_NativePointer node,
                            const Type_GaugeInterface_setGaugeOptions_Arg0* options);
    void (*setValue)(Ark_NativePointer node,
                     const Ark_Number* value);
    void (*setStartAngle)(Ark_NativePointer node,
                          const Ark_Number* angle);
    void (*setEndAngle)(Ark_NativePointer node,
                        const Ark_Number* angle);
    void (*setColors)(Ark_NativePointer node,
                      const Type_GaugeAttribute_colors_Arg0* colors);
    void (*setStrokeWidth)(Ark_NativePointer node,
                           const Ark_Length* length);
    void (*setDescription)(Ark_NativePointer node,
                           const CustomBuilder* value);
    void (*setTrackShadow)(Ark_NativePointer node,
                           const Ark_GaugeShadowOptions* value);
    void (*setIndicator)(Ark_NativePointer node,
                         const Ark_GaugeIndicatorOptions* value);
    void (*setPrivacySensitive)(Ark_NativePointer node,
                                const Opt_Boolean* isPrivacySensitiveMode);
    void (*setContentModifier)(Ark_NativePointer node,
                               const Ark_CustomObject* modifier);
} GENERATED_ArkUIGaugeModifier;

typedef struct GENERATED_ArkUIGridModifier {
    void (*setGridOptions)(Ark_NativePointer node,
                           const Opt_Scroller* scroller,
                           const Opt_GridLayoutOptions* layoutOptions);
    void (*setColumnsTemplate)(Ark_NativePointer node,
                               const Ark_String* value);
    void (*setRowsTemplate)(Ark_NativePointer node,
                            const Ark_String* value);
    void (*setColumnsGap)(Ark_NativePointer node,
                          const Ark_Length* value);
    void (*setRowsGap)(Ark_NativePointer node,
                       const Ark_Length* value);
    void (*setScrollBarWidth)(Ark_NativePointer node,
                              const Type_GridAttribute_scrollBarWidth_Arg0* value);
    void (*setScrollBarColor)(Ark_NativePointer node,
                              const Type_GridAttribute_scrollBarColor_Arg0* value);
    void (*setScrollBar)(Ark_NativePointer node,
                         Ark_Int32 value);
    void (*setOnScrollBarUpdate)(Ark_NativePointer node,
                                 Ark_Function event);
    void (*setOnScrollIndex)(Ark_NativePointer node,
                             Ark_Function event);
    void (*setCachedCount)(Ark_NativePointer node,
                           const Ark_Number* value);
    void (*setEditMode)(Ark_NativePointer node,
                        Ark_Boolean value);
    void (*setMultiSelectable)(Ark_NativePointer node,
                               Ark_Boolean value);
    void (*setMaxCount)(Ark_NativePointer node,
                        const Ark_Number* value);
    void (*setMinCount)(Ark_NativePointer node,
                        const Ark_Number* value);
    void (*setCellLength)(Ark_NativePointer node,
                          const Ark_Number* value);
    void (*setLayoutDirection)(Ark_NativePointer node,
                               Ark_Int32 value);
    void (*setSupportAnimation)(Ark_NativePointer node,
                                Ark_Boolean value);
    void (*setOnItemDragStart)(Ark_NativePointer node,
                               Ark_Function event);
    void (*setOnItemDragEnter)(Ark_NativePointer node,
                               Ark_Function event);
    void (*setOnItemDragMove)(Ark_NativePointer node,
                              Ark_Function event);
    void (*setOnItemDragLeave)(Ark_NativePointer node,
                               Ark_Function event);
    void (*setOnItemDrop)(Ark_NativePointer node,
                          Ark_Function event);
    void (*setEdgeEffect)(Ark_NativePointer node,
                          Ark_Int32 value,
                          const Opt_EdgeEffectOptions* options);
    void (*setNestedScroll)(Ark_NativePointer node,
                            const Ark_NestedScrollOptions* value);
    void (*setEnableScrollInteraction)(Ark_NativePointer node,
                                       Ark_Boolean value);
    void (*setFriction)(Ark_NativePointer node,
                        const Type_GridAttribute_friction_Arg0* value);
    void (*setAlignItems)(Ark_NativePointer node,
                          const Opt_GridItemAlignment* alignment);
    void (*setOnScroll)(Ark_NativePointer node,
                        Ark_Function event);
    void (*setOnReachStart)(Ark_NativePointer node,
                            Ark_Function event);
    void (*setOnReachEnd)(Ark_NativePointer node,
                          Ark_Function event);
    void (*setOnScrollStart)(Ark_NativePointer node,
                             Ark_Function event);
    void (*setOnScrollStop)(Ark_NativePointer node,
                            Ark_Function event);
    void (*setOnScrollFrameBegin)(Ark_NativePointer node,
                                  Ark_Function event);
} GENERATED_ArkUIGridModifier;

typedef struct GENERATED_ArkUIGridItemModifier {
    void (*setGridItemOptions)(Ark_NativePointer node,
                               const Opt_GridItemOptions* value);
    void (*setRowStart)(Ark_NativePointer node,
                        const Ark_Number* value);
    void (*setRowEnd)(Ark_NativePointer node,
                      const Ark_Number* value);
    void (*setColumnStart)(Ark_NativePointer node,
                           const Ark_Number* value);
    void (*setColumnEnd)(Ark_NativePointer node,
                         const Ark_Number* value);
    void (*setForceRebuild)(Ark_NativePointer node,
                            Ark_Boolean value);
    void (*setSelectable)(Ark_NativePointer node,
                          Ark_Boolean value);
    void (*setSelected)(Ark_NativePointer node,
                        Ark_Boolean value);
    void (*setOnSelect)(Ark_NativePointer node,
                        Ark_Function event);
} GENERATED_ArkUIGridItemModifier;

typedef struct GENERATED_ArkUIGridColModifier {
    void (*setGridColOptions)(Ark_NativePointer node,
                              const Opt_GridColOptions* option);
    void (*setSpan)(Ark_NativePointer node,
                    const Type_GridColAttribute_span_Arg0* value);
    void (*setGridColOffset)(Ark_NativePointer node,
                             const Type_GridColAttribute_gridColOffset_Arg0* value);
    void (*setOrder)(Ark_NativePointer node,
                     const Type_GridColAttribute_order_Arg0* value);
} GENERATED_ArkUIGridColModifier;

typedef struct GENERATED_ArkUIGridContainerModifier {
    void (*setGridContainerOptions)(Ark_NativePointer node,
                                    const Opt_GridContainerOptions* value);
} GENERATED_ArkUIGridContainerModifier;

typedef struct GENERATED_ArkUIGridRowModifier {
    void (*setGridRowOptions)(Ark_NativePointer node,
                              const Opt_GridRowOptions* option);
    void (*setOnBreakpointChange)(Ark_NativePointer node,
                                  Ark_Function callback);
    void (*setAlignItems)(Ark_NativePointer node,
                          Ark_Int32 value);
} GENERATED_ArkUIGridRowModifier;

typedef struct GENERATED_ArkUIHyperlinkModifier {
    void (*setHyperlinkOptions)(Ark_NativePointer node,
                                const Type_HyperlinkInterface_setHyperlinkOptions_Arg0* address,
                                const Opt_Type_HyperlinkInterface_setHyperlinkOptions_Arg1* content);
    void (*setColor)(Ark_NativePointer node,
                     const Type_HyperlinkAttribute_color_Arg0* value);
} GENERATED_ArkUIHyperlinkModifier;

typedef struct GENERATED_ArkUIImageModifier {
    void (*setImageOptions0)(Ark_NativePointer node,
                             const Type_ImageInterface_setImageOptions_Arg0* src);
    void (*setImageOptions1)(Ark_NativePointer node,
                             const Type_ImageInterface_setImageOptions1_Arg0* src);
    void (*setImageOptions2)(Ark_NativePointer node,
                             const Type_ImageInterface_setImageOptions2_Arg0* src,
                             const Ark_ImageAIOptions* imageAIOptions);
    void (*setAlt)(Ark_NativePointer node,
                   const Type_ImageAttribute_alt_Arg0* value);
    void (*setMatchTextDirection)(Ark_NativePointer node,
                                  Ark_Boolean value);
    void (*setFitOriginalSize)(Ark_NativePointer node,
                               Ark_Boolean value);
    void (*setFillColor)(Ark_NativePointer node,
                         const ResourceColor* value);
    void (*setObjectFit)(Ark_NativePointer node,
                         Ark_Int32 value);
    void (*setObjectRepeat)(Ark_NativePointer node,
                            Ark_Int32 value);
    void (*setAutoResize)(Ark_NativePointer node,
                          Ark_Boolean value);
    void (*setRenderMode)(Ark_NativePointer node,
                          Ark_Int32 value);
    void (*setDynamicRangeMode)(Ark_NativePointer node,
                                Ark_Int32 value);
    void (*setInterpolation)(Ark_NativePointer node,
                             Ark_Int32 value);
    void (*setSourceSize)(Ark_NativePointer node,
                          const Type_ImageAttribute_sourceSize_Arg0* value);
    void (*setSyncLoad)(Ark_NativePointer node,
                        Ark_Boolean value);
    void (*setColorFilter)(Ark_NativePointer node,
                           const Type_ImageAttribute_colorFilter_Arg0* value);
    void (*setCopyOption)(Ark_NativePointer node,
                          Ark_Int32 value);
    void (*setDraggable)(Ark_NativePointer node,
                         Ark_Boolean value);
    void (*setPointLight)(Ark_NativePointer node,
                          const Ark_PointLightStyle* value);
    void (*setEdgeAntialiasing)(Ark_NativePointer node,
                                const Ark_Number* value);
    void (*setOnComplete)(Ark_NativePointer node,
                          Ark_Function callback);
    void (*setOnError)(Ark_NativePointer node,
                       Ark_Function callback);
    void (*setOnFinish)(Ark_NativePointer node,
                        Ark_Function event);
    void (*setEnableAnalyzer)(Ark_NativePointer node,
                              Ark_Boolean enable);
    void (*setAnalyzerConfig)(Ark_NativePointer node,
                              const Ark_ImageAnalyzerConfig* config);
    void (*setResizable)(Ark_NativePointer node,
                         const Ark_ResizableOptions* value);
    void (*setPrivacySensitive)(Ark_NativePointer node,
                                Ark_Boolean supported);
    void (*setEnhancedImageQuality)(Ark_NativePointer node,
                                    const Ark_CustomObject* imageQuality);
} GENERATED_ArkUIImageModifier;

typedef struct GENERATED_ArkUIImageAnimatorModifier {
    void (*setImageAnimatorOptions)(Ark_NativePointer node);
    void (*setImages)(Ark_NativePointer node,
                      const Array_ImageFrameInfo* value);
    void (*setState)(Ark_NativePointer node,
                     Ark_Int32 value);
    void (*setDuration)(Ark_NativePointer node,
                        const Ark_Number* value);
    void (*setReverse)(Ark_NativePointer node,
                       Ark_Boolean value);
    void (*setFixedSize)(Ark_NativePointer node,
                         Ark_Boolean value);
    void (*setPreDecode)(Ark_NativePointer node,
                         const Ark_Number* value);
    void (*setFillMode)(Ark_NativePointer node,
                        Ark_Int32 value);
    void (*setIterations)(Ark_NativePointer node,
                          const Ark_Number* value);
    void (*setOnStart)(Ark_NativePointer node,
                       Ark_Function event);
    void (*setOnPause)(Ark_NativePointer node,
                       Ark_Function event);
    void (*setOnRepeat)(Ark_NativePointer node,
                        Ark_Function event);
    void (*setOnCancel)(Ark_NativePointer node,
                        Ark_Function event);
    void (*setOnFinish)(Ark_NativePointer node,
                        Ark_Function event);
} GENERATED_ArkUIImageAnimatorModifier;

typedef struct GENERATED_ArkUIImageSpanModifier {
    void (*setImageSpanOptions)(Ark_NativePointer node,
                                const Type_ImageSpanInterface_setImageSpanOptions_Arg0* value);
    void (*setVerticalAlign)(Ark_NativePointer node,
                             Ark_Int32 value);
    void (*setColorFilter)(Ark_NativePointer node,
                           const Type_ImageSpanAttribute_colorFilter_Arg0* filter);
    void (*setObjectFit)(Ark_NativePointer node,
                         Ark_Int32 value);
    void (*setOnComplete)(Ark_NativePointer node,
                          Ark_Function callback);
    void (*setOnError)(Ark_NativePointer node,
                       Ark_Function callback);
    void (*setAlt)(Ark_NativePointer node,
                   const Ark_CustomObject* value);
} GENERATED_ArkUIImageSpanModifier;

typedef struct GENERATED_ArkUILineModifier {
    void (*setLineOptions)(Ark_NativePointer node,
                           const Opt_Type_LineInterface_setLineOptions_Arg0* value);
    void (*setStartPoint)(Ark_NativePointer node,
                          const Array_CustomObject* value);
    void (*setEndPoint)(Ark_NativePointer node,
                        const Array_CustomObject* value);
} GENERATED_ArkUILineModifier;

typedef struct GENERATED_ArkUIListModifier {
    void (*setListOptions)(Ark_NativePointer node,
                           const Opt_ListOptions* options);
    void (*setLanes)(Ark_NativePointer node,
                     const Type_ListAttribute_lanes_Arg0* value,
                     const Opt_Dimension* gutter);
    void (*setAlignListItem)(Ark_NativePointer node,
                             Ark_Int32 value);
    void (*setListDirection)(Ark_NativePointer node,
                             Ark_Int32 value);
    void (*setScrollBar)(Ark_NativePointer node,
                         Ark_Int32 value);
    void (*setEdgeEffect)(Ark_NativePointer node,
                          Ark_Int32 value,
                          const Opt_EdgeEffectOptions* options);
    void (*setContentStartOffset)(Ark_NativePointer node,
                                  const Ark_Number* value);
    void (*setContentEndOffset)(Ark_NativePointer node,
                                const Ark_Number* value);
    void (*setDivider)(Ark_NativePointer node,
                       const Type_ListAttribute_divider_Arg0* value);
    void (*setEditMode)(Ark_NativePointer node,
                        Ark_Boolean value);
    void (*setMultiSelectable)(Ark_NativePointer node,
                               Ark_Boolean value);
    void (*setCachedCount)(Ark_NativePointer node,
                           const Ark_Number* value);
    void (*setChainAnimation)(Ark_NativePointer node,
                              Ark_Boolean value);
    void (*setChainAnimationOptions)(Ark_NativePointer node,
                                     const Ark_ChainAnimationOptions* value);
    void (*setSticky)(Ark_NativePointer node,
                      Ark_Int32 value);
    void (*setScrollSnapAlign)(Ark_NativePointer node,
                               Ark_Int32 value);
    void (*setNestedScroll)(Ark_NativePointer node,
                            const Ark_NestedScrollOptions* value);
    void (*setEnableScrollInteraction)(Ark_NativePointer node,
                                       Ark_Boolean value);
    void (*setFriction)(Ark_NativePointer node,
                        const Type_ListAttribute_friction_Arg0* value);
    void (*setChildrenMainSize)(Ark_NativePointer node,
                                const Ark_Materialized* value);
    void (*setMaintainVisibleContentPosition)(Ark_NativePointer node,
                                              Ark_Boolean enabled);
    void (*setOnScroll)(Ark_NativePointer node,
                        Ark_Function event);
    void (*setOnScrollIndex)(Ark_NativePointer node,
                             Ark_Function event);
    void (*setOnScrollVisibleContentChange)(Ark_NativePointer node,
                                            Ark_Function handler);
    void (*setOnReachStart)(Ark_NativePointer node,
                            Ark_Function event);
    void (*setOnReachEnd)(Ark_NativePointer node,
                          Ark_Function event);
    void (*setOnScrollStart)(Ark_NativePointer node,
                             Ark_Function event);
    void (*setOnScrollStop)(Ark_NativePointer node,
                            Ark_Function event);
    void (*setOnItemDelete)(Ark_NativePointer node,
                            Ark_Function event);
    void (*setOnItemMove)(Ark_NativePointer node,
                          Ark_Function event);
    void (*setOnItemDragStart)(Ark_NativePointer node,
                               Ark_Function event);
    void (*setOnItemDragEnter)(Ark_NativePointer node,
                               Ark_Function event);
    void (*setOnItemDragMove)(Ark_NativePointer node,
                              Ark_Function event);
    void (*setOnItemDragLeave)(Ark_NativePointer node,
                               Ark_Function event);
    void (*setOnItemDrop)(Ark_NativePointer node,
                          Ark_Function event);
    void (*setOnScrollFrameBegin)(Ark_NativePointer node,
                                  Ark_Function event);
} GENERATED_ArkUIListModifier;

typedef struct GENERATED_ArkUIListItemModifier {
    void (*setListItemOptions0)(Ark_NativePointer node,
                                const Opt_ListItemOptions* value);
    void (*setListItemOptions1)(Ark_NativePointer node,
                                const Opt_String* value);
    void (*setSticky)(Ark_NativePointer node,
                      Ark_Int32 value);
    void (*setEditable)(Ark_NativePointer node,
                        const Type_ListItemAttribute_editable_Arg0* value);
    void (*setSelectable)(Ark_NativePointer node,
                          Ark_Boolean value);
    void (*setSelected)(Ark_NativePointer node,
                        Ark_Boolean value);
    void (*setSwipeAction)(Ark_NativePointer node,
                           const Ark_SwipeActionOptions* value);
    void (*setOnSelect)(Ark_NativePointer node,
                        Ark_Function event);
} GENERATED_ArkUIListItemModifier;

typedef struct GENERATED_ArkUIListItemGroupModifier {
    void (*setListItemGroupOptions)(Ark_NativePointer node,
                                    const Opt_ListItemGroupOptions* options);
    void (*setDivider)(Ark_NativePointer node,
                       const Type_ListItemGroupAttribute_divider_Arg0* value);
    void (*setChildrenMainSize)(Ark_NativePointer node,
                                const Ark_Materialized* value);
} GENERATED_ArkUIListItemGroupModifier;

typedef struct GENERATED_ArkUILoadingProgressModifier {
    void (*setLoadingProgressOptions)(Ark_NativePointer node);
    void (*setColor)(Ark_NativePointer node,
                     const ResourceColor* value);
    void (*setEnableLoading)(Ark_NativePointer node,
                             Ark_Boolean value);
    void (*setContentModifier)(Ark_NativePointer node,
                               const Ark_CustomObject* modifier);
} GENERATED_ArkUILoadingProgressModifier;

typedef struct GENERATED_ArkUILocationButtonModifier {
    void (*setLocationButtonOptions0)(Ark_NativePointer node);
    void (*setLocationButtonOptions1)(Ark_NativePointer node,
                                      const Ark_LocationButtonOptions* options);
    void (*setOnClick)(Ark_NativePointer node,
                       Ark_Function event);
} GENERATED_ArkUILocationButtonModifier;

typedef struct GENERATED_ArkUIMarqueeModifier {
    void (*setMarqueeOptions)(Ark_NativePointer node,
                              const Type_MarqueeInterface_setMarqueeOptions_Arg0* value);
    void (*setFontColor)(Ark_NativePointer node,
                         const ResourceColor* value);
    void (*setFontSize)(Ark_NativePointer node,
                        const Ark_Length* value);
    void (*setAllowScale)(Ark_NativePointer node,
                          Ark_Boolean value);
    void (*setFontWeight)(Ark_NativePointer node,
                          const Type_MarqueeAttribute_fontWeight_Arg0* value);
    void (*setFontFamily)(Ark_NativePointer node,
                          const Type_MarqueeAttribute_fontFamily_Arg0* value);
    void (*setMarqueeUpdateStrategy)(Ark_NativePointer node,
                                     Ark_Int32 value);
    void (*setOnStart)(Ark_NativePointer node,
                       Ark_Function event);
    void (*setOnBounce)(Ark_NativePointer node,
                        Ark_Function event);
    void (*setOnFinish)(Ark_NativePointer node,
                        Ark_Function event);
} GENERATED_ArkUIMarqueeModifier;

typedef struct GENERATED_ArkUIMediaCachedImageModifier {
    void (*setMediaCachedImageOptions)(Ark_NativePointer node,
                                       const Type_MediaCachedImageInterface_setMediaCachedImageOptions_Arg0* src);
} GENERATED_ArkUIMediaCachedImageModifier;

typedef struct GENERATED_ArkUIMenuModifier {
    void (*setMenuOptions)(Ark_NativePointer node);
    void (*setFontSize)(Ark_NativePointer node,
                        const Ark_Length* value);
    void (*setFont)(Ark_NativePointer node,
                    const Ark_Font* value);
    void (*setFontColor)(Ark_NativePointer node,
                         const ResourceColor* value);
    void (*setRadius)(Ark_NativePointer node,
                      const Type_MenuAttribute_radius_Arg0* value);
    void (*setMenuItemDivider)(Ark_NativePointer node,
                               const Type_MenuAttribute_menuItemDivider_Arg0* options);
    void (*setMenuItemGroupDivider)(Ark_NativePointer node,
                                    const Type_MenuAttribute_menuItemGroupDivider_Arg0* options);
    void (*setSubMenuExpandingMode)(Ark_NativePointer node,
                                    Ark_Int32 mode);
} GENERATED_ArkUIMenuModifier;

typedef struct GENERATED_ArkUIMenuItemModifier {
    void (*setMenuItemOptions)(Ark_NativePointer node,
                               const Opt_Type_MenuItemInterface_setMenuItemOptions_Arg0* value);
    void (*setSelected)(Ark_NativePointer node,
                        Ark_Boolean value);
    void (*setSelectIcon)(Ark_NativePointer node,
                          const Type_MenuItemAttribute_selectIcon_Arg0* value);
    void (*setOnChange)(Ark_NativePointer node,
                        Ark_Function callback);
    void (*setContentFont)(Ark_NativePointer node,
                           const Ark_Font* value);
    void (*setContentFontColor)(Ark_NativePointer node,
                                const ResourceColor* value);
    void (*setLabelFont)(Ark_NativePointer node,
                         const Ark_Font* value);
    void (*setLabelFontColor)(Ark_NativePointer node,
                              const ResourceColor* value);
} GENERATED_ArkUIMenuItemModifier;

typedef struct GENERATED_ArkUIMenuItemGroupModifier {
    void (*setMenuItemGroupOptions)(Ark_NativePointer node,
                                    const Opt_MenuItemGroupOptions* value);
} GENERATED_ArkUIMenuItemGroupModifier;

typedef struct GENERATED_ArkUINavDestinationModifier {
    void (*setNavDestinationOptions)(Ark_NativePointer node);
    void (*setTitle)(Ark_NativePointer node,
                     const Type_NavDestinationAttribute_title_Arg0* value,
                     const Opt_NavigationTitleOptions* options);
    void (*setHideTitleBar0)(Ark_NativePointer node,
                             Ark_Boolean value);
    void (*setHideTitleBar1)(Ark_NativePointer node,
                             Ark_Boolean hide,
                             Ark_Boolean animated);
    void (*setOnShown)(Ark_NativePointer node,
                       Ark_Function callback);
    void (*setOnHidden)(Ark_NativePointer node,
                        Ark_Function callback);
    void (*setOnBackPressed)(Ark_NativePointer node,
                             Ark_Function callback);
    void (*setMode)(Ark_NativePointer node,
                    Ark_Int32 value);
    void (*setBackButtonIcon)(Ark_NativePointer node,
                              const Type_NavDestinationAttribute_backButtonIcon_Arg0* value);
    void (*setMenus)(Ark_NativePointer node,
                     const Type_NavDestinationAttribute_menus_Arg0* value);
    void (*setOnReady)(Ark_NativePointer node,
                       Ark_Function callback);
    void (*setOnWillAppear)(Ark_NativePointer node,
                            Ark_Function callback);
    void (*setOnWillDisappear)(Ark_NativePointer node,
                               Ark_Function callback);
    void (*setOnWillShow)(Ark_NativePointer node,
                          Ark_Function callback);
    void (*setOnWillHide)(Ark_NativePointer node,
                          Ark_Function callback);
    void (*setIgnoreLayoutSafeArea)(Ark_NativePointer node,
                                    const Opt_Array_LayoutSafeAreaType* types,
                                    const Opt_Array_LayoutSafeAreaEdge* edges);
    void (*setSystemBarStyle)(Ark_NativePointer node,
                              const Opt_CustomObject* style);
} GENERATED_ArkUINavDestinationModifier;

typedef struct GENERATED_ArkUINavRouterModifier {
    void (*setNavRouterOptions0)(Ark_NativePointer node);
    void (*setNavRouterOptions1)(Ark_NativePointer node,
                                 const Ark_RouteInfo* value);
    void (*setOnStateChange)(Ark_NativePointer node,
                             Ark_Function callback);
    void (*setMode)(Ark_NativePointer node,
                    Ark_Int32 mode);
} GENERATED_ArkUINavRouterModifier;

typedef struct GENERATED_ArkUINavigationModifier {
    void (*setNavigationOptions0)(Ark_NativePointer node);
    void (*setNavigationOptions1)(Ark_NativePointer node,
                                  const Ark_Materialized* pathInfos);
    void (*setNavBarWidth)(Ark_NativePointer node,
                           const Ark_Length* value);
    void (*setNavBarPosition)(Ark_NativePointer node,
                              Ark_Int32 value);
    void (*setNavBarWidthRange)(Ark_NativePointer node,
                                const Type_NavigationAttribute_navBarWidthRange_Arg0* value);
    void (*setMinContentWidth)(Ark_NativePointer node,
                               const Ark_Length* value);
    void (*setMode)(Ark_NativePointer node,
                    Ark_Int32 value);
    void (*setBackButtonIcon)(Ark_NativePointer node,
                              const Type_NavigationAttribute_backButtonIcon_Arg0* value);
    void (*setHideNavBar)(Ark_NativePointer node,
                          Ark_Boolean value);
    void (*setTitle)(Ark_NativePointer node,
                     const Type_NavigationAttribute_title_Arg0* value,
                     const Opt_NavigationTitleOptions* options);
    void (*setSubTitle)(Ark_NativePointer node,
                        const Ark_String* value);
    void (*setHideTitleBar0)(Ark_NativePointer node,
                             Ark_Boolean value);
    void (*setHideTitleBar1)(Ark_NativePointer node,
                             Ark_Boolean hide,
                             Ark_Boolean animated);
    void (*setHideBackButton)(Ark_NativePointer node,
                              Ark_Boolean value);
    void (*setTitleMode)(Ark_NativePointer node,
                         Ark_Int32 value);
    void (*setMenus)(Ark_NativePointer node,
                     const Type_NavigationAttribute_menus_Arg0* value);
    void (*setToolBar)(Ark_NativePointer node,
                       const Type_NavigationAttribute_toolBar_Arg0* value);
    void (*setToolbarConfiguration)(Ark_NativePointer node,
                                    const Type_NavigationAttribute_toolbarConfiguration_Arg0* value,
                                    const Opt_NavigationToolbarOptions* options);
    void (*setHideToolBar0)(Ark_NativePointer node,
                            Ark_Boolean value);
    void (*setHideToolBar1)(Ark_NativePointer node,
                            Ark_Boolean hide,
                            Ark_Boolean animated);
    void (*setOnTitleModeChange)(Ark_NativePointer node,
                                 Ark_Function callback);
    void (*setOnNavBarStateChange)(Ark_NativePointer node,
                                   Ark_Function callback);
    void (*setOnNavigationModeChange)(Ark_NativePointer node,
                                      Ark_Function callback);
    void (*setNavDestination)(Ark_NativePointer node,
                              Ark_Function builder);
    void (*setCustomNavContentTransition)(Ark_NativePointer node,
                                          Ark_Function delegate);
    void (*setIgnoreLayoutSafeArea)(Ark_NativePointer node,
                                    const Opt_Array_LayoutSafeAreaType* types,
                                    const Opt_Array_LayoutSafeAreaEdge* edges);
    void (*setSystemBarStyle)(Ark_NativePointer node,
                              const Opt_CustomObject* style);
} GENERATED_ArkUINavigationModifier;

typedef struct GENERATED_ArkUINavigatorModifier {
    void (*setNavigatorOptions0)(Ark_NativePointer node,
                                 const Opt_Type_NavigatorInterface_setNavigatorOptions_Arg0* value);
    void (*setNavigatorOptions1)(Ark_NativePointer node);
    void (*setActive)(Ark_NativePointer node,
                      Ark_Boolean value);
    void (*setType)(Ark_NativePointer node,
                    Ark_Int32 value);
    void (*setTarget)(Ark_NativePointer node,
                      const Ark_String* value);
    void (*setParams)(Ark_NativePointer node,
                      const Ark_CustomObject* value);
} GENERATED_ArkUINavigatorModifier;

typedef struct GENERATED_ArkUINodeContainerModifier {
    void (*setNodeContainerOptions)(Ark_NativePointer node,
                                    const Ark_CustomObject* controller);
} GENERATED_ArkUINodeContainerModifier;

typedef struct GENERATED_ArkUIPanelModifier {
    void (*setPanelOptions)(Ark_NativePointer node,
                            Ark_Boolean show);
    void (*setMode)(Ark_NativePointer node,
                    Ark_Int32 value);
    void (*setType)(Ark_NativePointer node,
                    Ark_Int32 value);
    void (*setDragBar)(Ark_NativePointer node,
                       Ark_Boolean value);
    void (*setCustomHeight)(Ark_NativePointer node,
                            const Type_PanelAttribute_customHeight_Arg0* value);
    void (*setFullHeight)(Ark_NativePointer node,
                          const Type_PanelAttribute_fullHeight_Arg0* value);
    void (*setHalfHeight)(Ark_NativePointer node,
                          const Type_PanelAttribute_halfHeight_Arg0* value);
    void (*setMiniHeight)(Ark_NativePointer node,
                          const Type_PanelAttribute_miniHeight_Arg0* value);
    void (*setShow)(Ark_NativePointer node,
                    Ark_Boolean value);
    void (*setBackgroundMask)(Ark_NativePointer node,
                              const ResourceColor* color);
    void (*setShowCloseIcon)(Ark_NativePointer node,
                             Ark_Boolean value);
    void (*setOnChange)(Ark_NativePointer node,
                        Ark_Function event);
    void (*setOnHeightChange)(Ark_NativePointer node,
                              Ark_Function callback);
} GENERATED_ArkUIPanelModifier;

typedef struct GENERATED_ArkUIPasteButtonModifier {
    void (*setPasteButtonOptions0)(Ark_NativePointer node);
    void (*setPasteButtonOptions1)(Ark_NativePointer node,
                                   const Ark_PasteButtonOptions* options);
    void (*setOnClick)(Ark_NativePointer node,
                       Ark_Function event);
} GENERATED_ArkUIPasteButtonModifier;

typedef struct GENERATED_ArkUIPathModifier {
    void (*setPathOptions)(Ark_NativePointer node,
                           const Opt_Type_PathInterface_setPathOptions_Arg0* value);
    void (*setCommands)(Ark_NativePointer node,
                        const Ark_String* value);
} GENERATED_ArkUIPathModifier;

typedef struct GENERATED_ArkUIPatternLockModifier {
    void (*setPatternLockOptions)(Ark_NativePointer node,
                                  const Opt_PatternLockController* controller);
    void (*setSideLength)(Ark_NativePointer node,
                          const Ark_Length* value);
    void (*setCircleRadius)(Ark_NativePointer node,
                            const Ark_Length* value);
    void (*setBackgroundColor)(Ark_NativePointer node,
                               const ResourceColor* value);
    void (*setRegularColor)(Ark_NativePointer node,
                            const ResourceColor* value);
    void (*setSelectedColor)(Ark_NativePointer node,
                             const ResourceColor* value);
    void (*setActiveColor)(Ark_NativePointer node,
                           const ResourceColor* value);
    void (*setPathColor)(Ark_NativePointer node,
                         const ResourceColor* value);
    void (*setPathStrokeWidth)(Ark_NativePointer node,
                               const Type_PatternLockAttribute_pathStrokeWidth_Arg0* value);
    void (*setOnPatternComplete)(Ark_NativePointer node,
                                 Ark_Function callback);
    void (*setAutoReset)(Ark_NativePointer node,
                         Ark_Boolean value);
    void (*setOnDotConnect)(Ark_NativePointer node,
                            Ark_Function callback);
    void (*setActivateCircleStyle)(Ark_NativePointer node,
                                   const Opt_CircleStyleOptions* options);
} GENERATED_ArkUIPatternLockModifier;

typedef struct GENERATED_ArkUIPluginComponentModifier {
    void (*setPluginComponentOptions)(Ark_NativePointer node,
                                      const Type_PluginComponentInterface_setPluginComponentOptions_Arg0* value);
    void (*setOnComplete)(Ark_NativePointer node,
                          Ark_Function callback);
    void (*setOnError)(Ark_NativePointer node,
                       Ark_Function callback);
} GENERATED_ArkUIPluginComponentModifier;

typedef struct GENERATED_ArkUIPolygonModifier {
    void (*setPolygonOptions)(Ark_NativePointer node,
                              const Opt_Type_PolygonInterface_setPolygonOptions_Arg0* value);
    void (*setPoints)(Ark_NativePointer node,
                      const Array_CustomObject* value);
} GENERATED_ArkUIPolygonModifier;

typedef struct GENERATED_ArkUIPolylineModifier {
    void (*setPolylineOptions)(Ark_NativePointer node,
                               const Opt_Type_PolylineInterface_setPolylineOptions_Arg0* value);
    void (*setPoints)(Ark_NativePointer node,
                      const Array_CustomObject* value);
} GENERATED_ArkUIPolylineModifier;

typedef struct GENERATED_ArkUIQRCodeModifier {
    void (*setQRCodeOptions)(Ark_NativePointer node,
                             const Ark_String* value);
    void (*setColor)(Ark_NativePointer node,
                     const ResourceColor* value);
    void (*setBackgroundColor)(Ark_NativePointer node,
                               const ResourceColor* value);
    void (*setContentOpacity)(Ark_NativePointer node,
                              const Type_QRCodeAttribute_contentOpacity_Arg0* value);
} GENERATED_ArkUIQRCodeModifier;

typedef struct GENERATED_ArkUIRadioModifier {
    void (*setRadioOptions)(Ark_NativePointer node,
                            const Ark_RadioOptions* options);
    void (*setChecked)(Ark_NativePointer node,
                       Ark_Boolean value);
    void (*setOnChange)(Ark_NativePointer node,
                        Ark_Function callback);
    void (*setRadioStyle)(Ark_NativePointer node,
                          const Opt_RadioStyle* value);
    void (*setContentModifier)(Ark_NativePointer node,
                               const Ark_CustomObject* modifier);
} GENERATED_ArkUIRadioModifier;

typedef struct GENERATED_ArkUIRatingModifier {
    void (*setRatingOptions)(Ark_NativePointer node,
                             const Opt_RatingOptions* options);
    void (*setStars)(Ark_NativePointer node,
                     const Ark_Number* value);
    void (*setStepSize)(Ark_NativePointer node,
                        const Ark_Number* value);
    void (*setStarStyle)(Ark_NativePointer node,
                         const Ark_StarStyleOptions* options);
    void (*setOnChange)(Ark_NativePointer node,
                        Ark_Function callback);
    void (*setContentModifier)(Ark_NativePointer node,
                               const Ark_CustomObject* modifier);
} GENERATED_ArkUIRatingModifier;

typedef struct GENERATED_ArkUIRectModifier {
    void (*setRectOptions)(Ark_NativePointer node,
                           const Opt_Type_RectInterface_setRectOptions_Arg0* value);
    void (*setRadiusWidth)(Ark_NativePointer node,
                           const Type_RectAttribute_radiusWidth_Arg0* value);
    void (*setRadiusHeight)(Ark_NativePointer node,
                            const Type_RectAttribute_radiusHeight_Arg0* value);
    void (*setRadius)(Ark_NativePointer node,
                      const Type_RectAttribute_radius_Arg0* value);
} GENERATED_ArkUIRectModifier;

typedef struct GENERATED_ArkUIRefreshModifier {
    void (*setRefreshOptions)(Ark_NativePointer node,
                              const Ark_RefreshOptions* value);
    void (*setOnStateChange)(Ark_NativePointer node,
                             Ark_Function callback);
    void (*setOnRefreshing)(Ark_NativePointer node,
                            Ark_Function callback);
    void (*setRefreshOffset)(Ark_NativePointer node,
                             const Ark_Number* value);
    void (*setPullToRefresh)(Ark_NativePointer node,
                             Ark_Boolean value);
    void (*setOnOffsetChange)(Ark_NativePointer node,
                              Ark_Function callback);
    void (*setPullDownRatio)(Ark_NativePointer node,
                             const Opt_Number* ratio);
} GENERATED_ArkUIRefreshModifier;

typedef struct GENERATED_ArkUIRelativeContainerModifier {
    void (*setRelativeContainerOptions)(Ark_NativePointer node);
    void (*setGuideLine)(Ark_NativePointer node,
                         const Array_GuideLineStyle* value);
    void (*setBarrier0)(Ark_NativePointer node,
                        const Array_BarrierStyle* value);
    void (*setBarrier1)(Ark_NativePointer node,
                        const Array_LocalizedBarrierStyle* barrierStyle);
} GENERATED_ArkUIRelativeContainerModifier;

typedef struct GENERATED_ArkUIRichEditorModifier {
    void (*setRichEditorOptions0)(Ark_NativePointer node,
                                  const Ark_RichEditorOptions* value);
    void (*setRichEditorOptions1)(Ark_NativePointer node,
                                  const Ark_RichEditorStyledStringOptions* options);
    void (*setOnReady)(Ark_NativePointer node,
                       Ark_Function callback);
    void (*setOnSelect)(Ark_NativePointer node,
                        Ark_Function callback);
    void (*setOnSelectionChange)(Ark_NativePointer node,
                                 Ark_Function callback);
    void (*setAboutToIMEInput)(Ark_NativePointer node,
                               Ark_Function callback);
    void (*setOnIMEInputComplete)(Ark_NativePointer node,
                                  Ark_Function callback);
    void (*setOnDidIMEInput)(Ark_NativePointer node,
                             Ark_Function callback);
    void (*setAboutToDelete)(Ark_NativePointer node,
                             Ark_Function callback);
    void (*setOnDeleteComplete)(Ark_NativePointer node,
                                Ark_Function callback);
    void (*setCopyOptions)(Ark_NativePointer node,
                           Ark_Int32 value);
    void (*setBindSelectionMenu)(Ark_NativePointer node,
                                 Ark_Int32 spanType,
                                 const CustomBuilder* content,
                                 const Type_RichEditorAttribute_bindSelectionMenu_Arg2* responseType,
                                 const Opt_SelectionMenuOptions* options);
    void (*setCustomKeyboard)(Ark_NativePointer node,
                              const CustomBuilder* value,
                              const Opt_KeyboardOptions* options);
    void (*setOnPaste)(Ark_NativePointer node,
                       Ark_Function callback);
    void (*setEnableDataDetector)(Ark_NativePointer node,
                                  Ark_Boolean enable);
    void (*setEnablePreviewText)(Ark_NativePointer node,
                                 Ark_Boolean enable);
    void (*setDataDetectorConfig)(Ark_NativePointer node,
                                  const Ark_TextDataDetectorConfig* config);
    void (*setPlaceholder)(Ark_NativePointer node,
                           const ResourceStr* value,
                           const Opt_PlaceholderStyle* style);
    void (*setCaretColor)(Ark_NativePointer node,
                          const ResourceColor* value);
    void (*setSelectedBackgroundColor)(Ark_NativePointer node,
                                       const ResourceColor* value);
    void (*setOnEditingChange)(Ark_NativePointer node,
                               Ark_Function callback);
    void (*setEnterKeyType)(Ark_NativePointer node,
                            Ark_Int32 value);
    void (*setOnSubmit)(Ark_NativePointer node,
                        Ark_Function callback);
    void (*setOnWillChange)(Ark_NativePointer node,
                            Ark_Function callback);
    void (*setOnDidChange)(Ark_NativePointer node,
                           Ark_Function callback);
    void (*setOnCut)(Ark_NativePointer node,
                     Ark_Function callback);
    void (*setOnCopy)(Ark_NativePointer node,
                      Ark_Function callback);
    void (*setEditMenuOptions)(Ark_NativePointer node,
                               const Ark_Materialized* editMenu);
    void (*setEnableKeyboardOnFocus)(Ark_NativePointer node,
                                     Ark_Boolean isEnabled);
    void (*setEnableHapticFeedback)(Ark_NativePointer node,
                                    Ark_Boolean isEnabled);
} GENERATED_ArkUIRichEditorModifier;

typedef struct GENERATED_ArkUIRichTextModifier {
    void (*setRichTextOptions)(Ark_NativePointer node,
                               const Ark_String* content);
    void (*setOnStart)(Ark_NativePointer node,
                       Ark_Function callback);
    void (*setOnComplete)(Ark_NativePointer node,
                          Ark_Function callback);
} GENERATED_ArkUIRichTextModifier;

typedef struct GENERATED_ArkUIRootSceneModifier {
    void (*setRootSceneOptions)(Ark_NativePointer node,
                                const Ark_RootSceneSession* session);
} GENERATED_ArkUIRootSceneModifier;

typedef struct GENERATED_ArkUIRowModifier {
    void (*setRowOptions)(Ark_NativePointer node,
                          const Opt_RowOptions* options);
    void (*setAlignItems)(Ark_NativePointer node,
                          Ark_Int32 value);
    void (*setJustifyContent)(Ark_NativePointer node,
                              Ark_Int32 value);
    void (*setPointLight)(Ark_NativePointer node,
                          const Ark_PointLightStyle* value);
    void (*setReverse)(Ark_NativePointer node,
                       const Opt_Boolean* isReversed);
} GENERATED_ArkUIRowModifier;

typedef struct GENERATED_ArkUIRowSplitModifier {
    void (*setRowSplitOptions)(Ark_NativePointer node);
    void (*setResizeable)(Ark_NativePointer node,
                          Ark_Boolean value);
} GENERATED_ArkUIRowSplitModifier;

typedef struct GENERATED_ArkUISaveButtonModifier {
    void (*setSaveButtonOptions0)(Ark_NativePointer node);
    void (*setSaveButtonOptions1)(Ark_NativePointer node,
                                  const Ark_SaveButtonOptions* options);
    void (*setOnClick)(Ark_NativePointer node,
                       Ark_Function event);
} GENERATED_ArkUISaveButtonModifier;

typedef struct GENERATED_ArkUIScreenModifier {
    void (*setScreenOptions)(Ark_NativePointer node,
                             const Ark_Number* screenId);
} GENERATED_ArkUIScreenModifier;

typedef struct GENERATED_ArkUIScrollModifier {
    void (*setScrollOptions)(Ark_NativePointer node,
                             const Opt_Scroller* scroller);
    void (*setScrollable)(Ark_NativePointer node,
                          Ark_Int32 value);
    void (*setOnScroll)(Ark_NativePointer node,
                        Ark_Function event);
    void (*setOnWillScroll)(Ark_NativePointer node,
                            const Ark_CustomObject* stub_for_onWillScroll);
    void (*setOnDidScroll)(Ark_NativePointer node,
                           Ark_Function handler);
    void (*setOnScrollEdge)(Ark_NativePointer node,
                            Ark_Function event);
    void (*setOnScrollStart)(Ark_NativePointer node,
                             Ark_Function event);
    void (*setOnScrollEnd)(Ark_NativePointer node,
                           Ark_Function event);
    void (*setOnScrollStop)(Ark_NativePointer node,
                            Ark_Function event);
    void (*setScrollBar)(Ark_NativePointer node,
                         Ark_Int32 barState);
    void (*setScrollBarColor)(Ark_NativePointer node,
                              const Type_ScrollAttribute_scrollBarColor_Arg0* color);
    void (*setScrollBarWidth)(Ark_NativePointer node,
                              const Type_ScrollAttribute_scrollBarWidth_Arg0* value);
    void (*setEdgeEffect)(Ark_NativePointer node,
                          Ark_Int32 edgeEffect,
                          const Opt_EdgeEffectOptions* options);
    void (*setOnScrollFrameBegin)(Ark_NativePointer node,
                                  Ark_Function event);
    void (*setNestedScroll)(Ark_NativePointer node,
                            const Ark_NestedScrollOptions* value);
    void (*setEnableScrollInteraction)(Ark_NativePointer node,
                                       Ark_Boolean value);
    void (*setFriction)(Ark_NativePointer node,
                        const Type_ScrollAttribute_friction_Arg0* value);
    void (*setScrollSnap)(Ark_NativePointer node,
                          const Ark_ScrollSnapOptions* value);
    void (*setEnablePaging)(Ark_NativePointer node,
                            Ark_Boolean value);
    void (*setInitialOffset)(Ark_NativePointer node,
                             const Ark_OffsetOptions* value);
} GENERATED_ArkUIScrollModifier;

typedef struct GENERATED_ArkUIScrollBarModifier {
    void (*setScrollBarOptions)(Ark_NativePointer node,
                                const Ark_ScrollBarOptions* value);
    void (*setEnableNestedScroll)(Ark_NativePointer node,
                                  const Opt_Boolean* enabled);
} GENERATED_ArkUIScrollBarModifier;

typedef struct GENERATED_ArkUISearchModifier {
    void (*setSearchOptions)(Ark_NativePointer node,
                             const Opt_Type_SearchInterface_setSearchOptions_Arg0* options);
    void (*setSearchButton)(Ark_NativePointer node,
                            const Ark_String* value,
                            const Opt_SearchButtonOptions* option);
    void (*setFontColor)(Ark_NativePointer node,
                         const ResourceColor* value);
    void (*setSearchIcon)(Ark_NativePointer node,
                          const Type_SearchAttribute_searchIcon_Arg0* value);
    void (*setCancelButton)(Ark_NativePointer node,
                            const Type_SearchAttribute_cancelButton_Arg0* value);
    void (*setTextIndent)(Ark_NativePointer node,
                          const Ark_Length* value);
    void (*setInputFilter)(Ark_NativePointer node,
                           const ResourceStr* value,
                           const Opt_Callback* error);
    void (*setOnEditChange)(Ark_NativePointer node,
                            Ark_Function callback);
    void (*setSelectedBackgroundColor)(Ark_NativePointer node,
                                       const ResourceColor* value);
    void (*setCaretStyle)(Ark_NativePointer node,
                          const Ark_CaretStyle* value);
    void (*setPlaceholderColor)(Ark_NativePointer node,
                                const ResourceColor* value);
    void (*setPlaceholderFont)(Ark_NativePointer node,
                               const Opt_Font* value);
    void (*setTextFont)(Ark_NativePointer node,
                        const Opt_Font* value);
    void (*setEnterKeyType)(Ark_NativePointer node,
                            Ark_Int32 value);
    void (*setOnSubmit)(Ark_NativePointer node,
                        Ark_Function callback);
    void (*setOnChange)(Ark_NativePointer node,
                        Ark_Function callback);
    void (*setOnTextSelectionChange)(Ark_NativePointer node,
                                     Ark_Function callback);
    void (*setOnContentScroll)(Ark_NativePointer node,
                               Ark_Function callback);
    void (*setOnCopy)(Ark_NativePointer node,
                      Ark_Function callback);
    void (*setOnCut)(Ark_NativePointer node,
                     Ark_Function callback);
    void (*setOnPaste)(Ark_NativePointer node,
                       Ark_Function callback);
    void (*setCopyOption)(Ark_NativePointer node,
                          Ark_Int32 value);
    void (*setMaxLength)(Ark_NativePointer node,
                         const Ark_Number* value);
    void (*setTextAlign)(Ark_NativePointer node,
                         Ark_Int32 value);
    void (*setEnableKeyboardOnFocus)(Ark_NativePointer node,
                                     Ark_Boolean value);
    void (*setSelectionMenuHidden)(Ark_NativePointer node,
                                   Ark_Boolean value);
    void (*setMinFontSize)(Ark_NativePointer node,
                           const Type_SearchAttribute_minFontSize_Arg0* value);
    void (*setMaxFontSize)(Ark_NativePointer node,
                           const Type_SearchAttribute_maxFontSize_Arg0* value);
    void (*setCustomKeyboard)(Ark_NativePointer node,
                              const CustomBuilder* value,
                              const Opt_KeyboardOptions* options);
    void (*setDecoration)(Ark_NativePointer node,
                          const Ark_TextDecorationOptions* value);
    void (*setLetterSpacing)(Ark_NativePointer node,
                             const Type_SearchAttribute_letterSpacing_Arg0* value);
    void (*setLineHeight)(Ark_NativePointer node,
                          const Type_SearchAttribute_lineHeight_Arg0* value);
    void (*setType)(Ark_NativePointer node,
                    Ark_Int32 value);
    void (*setFontFeature)(Ark_NativePointer node,
                           const Ark_String* value);
    void (*setOnWillInsert)(Ark_NativePointer node,
                            Ark_Function callback);
    void (*setOnDidInsert)(Ark_NativePointer node,
                           Ark_Function callback);
    void (*setOnWillDelete)(Ark_NativePointer node,
                            Ark_Function callback);
    void (*setOnDidDelete)(Ark_NativePointer node,
                           Ark_Function callback);
    void (*setEditMenuOptions)(Ark_NativePointer node,
                               const Ark_Materialized* editMenu);
    void (*setEnablePreviewText)(Ark_NativePointer node,
                                 Ark_Boolean enable);
} GENERATED_ArkUISearchModifier;

typedef struct GENERATED_ArkUISecurityComponentMethodModifier {
    void (*setIconSize)(Ark_NativePointer node,
                        const Ark_Length* value);
    void (*setLayoutDirection)(Ark_NativePointer node,
                               Ark_Int32 value);
    void (*setPosition)(Ark_NativePointer node,
                        const Ark_Position* value);
    void (*setMarkAnchor)(Ark_NativePointer node,
                          const Ark_Position* value);
    void (*setOffset)(Ark_NativePointer node,
                      const Type_SecurityComponentMethod_offset_Arg0* value);
    void (*setFontSize)(Ark_NativePointer node,
                        const Ark_Length* value);
    void (*setFontStyle)(Ark_NativePointer node,
                         Ark_Int32 value);
    void (*setFontWeight)(Ark_NativePointer node,
                          const Type_SecurityComponentMethod_fontWeight_Arg0* value);
    void (*setFontFamily)(Ark_NativePointer node,
                          const Type_SecurityComponentMethod_fontFamily_Arg0* value);
    void (*setFontColor)(Ark_NativePointer node,
                         const ResourceColor* value);
    void (*setIconColor)(Ark_NativePointer node,
                         const ResourceColor* value);
    void (*setBackgroundColor)(Ark_NativePointer node,
                               const ResourceColor* value);
    void (*setBorderStyle)(Ark_NativePointer node,
                           Ark_Int32 value);
    void (*setBorderWidth)(Ark_NativePointer node,
                           const Ark_Length* value);
    void (*setBorderColor)(Ark_NativePointer node,
                           const ResourceColor* value);
    void (*setBorderRadius)(Ark_NativePointer node,
                            const Ark_Length* value);
    void (*setPadding)(Ark_NativePointer node,
                       const Type_SecurityComponentMethod_padding_Arg0* value);
    void (*setTextIconSpace)(Ark_NativePointer node,
                             const Ark_Length* value);
    void (*setKey)(Ark_NativePointer node,
                   const Ark_String* value);
    void (*setWidth)(Ark_NativePointer node,
                     const Ark_Length* value);
    void (*setHeight)(Ark_NativePointer node,
                      const Ark_Length* value);
    void (*setSize)(Ark_NativePointer node,
                    const Ark_SizeOptions* value);
    void (*setConstraintSize)(Ark_NativePointer node,
                              const Ark_ConstraintSizeOptions* value);
} GENERATED_ArkUISecurityComponentMethodModifier;

typedef struct GENERATED_ArkUISelectModifier {
    void (*setSelectOptions)(Ark_NativePointer node,
                             const Array_SelectOption* options);
    void (*setSelected)(Ark_NativePointer node,
                        const Type_SelectAttribute_selected_Arg0* value);
    void (*setValue)(Ark_NativePointer node,
                     const ResourceStr* value);
    void (*setFont)(Ark_NativePointer node,
                    const Ark_Font* value);
    void (*setFontColor)(Ark_NativePointer node,
                         const ResourceColor* value);
    void (*setSelectedOptionBgColor)(Ark_NativePointer node,
                                     const ResourceColor* value);
    void (*setSelectedOptionFont)(Ark_NativePointer node,
                                  const Ark_Font* value);
    void (*setSelectedOptionFontColor)(Ark_NativePointer node,
                                       const ResourceColor* value);
    void (*setOptionBgColor)(Ark_NativePointer node,
                             const ResourceColor* value);
    void (*setOptionFont)(Ark_NativePointer node,
                          const Ark_Font* value);
    void (*setOptionFontColor)(Ark_NativePointer node,
                               const ResourceColor* value);
    void (*setOnSelect)(Ark_NativePointer node,
                        Ark_Function callback);
    void (*setSpace)(Ark_NativePointer node,
                     const Ark_Length* value);
    void (*setArrowPosition)(Ark_NativePointer node,
                             Ark_Int32 value);
    void (*setMenuAlign)(Ark_NativePointer node,
                         Ark_Int32 alignType,
                         const Opt_Offset* offset);
    void (*setOptionWidth)(Ark_NativePointer node,
                           const Type_SelectAttribute_optionWidth_Arg0* value);
    void (*setOptionHeight)(Ark_NativePointer node,
                            const Ark_Length* value);
    void (*setMenuBackgroundColor)(Ark_NativePointer node,
                                   const ResourceColor* value);
    void (*setMenuBackgroundBlurStyle)(Ark_NativePointer node,
                                       Ark_Int32 value);
    void (*setControlSize)(Ark_NativePointer node,
                           Ark_Int32 value);
    void (*setMenuItemContentModifier)(Ark_NativePointer node,
                                       const Ark_CustomObject* modifier);
    void (*setDivider)(Ark_NativePointer node,
                       const Type_SelectAttribute_divider_Arg0* options);
} GENERATED_ArkUISelectModifier;

typedef struct GENERATED_ArkUIShapeModifier {
    void (*setShapeOptions0)(Ark_NativePointer node,
                             const Ark_CustomObject* value);
    void (*setShapeOptions1)(Ark_NativePointer node);
    void (*setViewPort)(Ark_NativePointer node,
                        const Type_ShapeAttribute_viewPort_Arg0* value);
    void (*setStroke)(Ark_NativePointer node,
                      const ResourceColor* value);
    void (*setFill)(Ark_NativePointer node,
                    const ResourceColor* value);
    void (*setStrokeDashOffset)(Ark_NativePointer node,
                                const Type_ShapeAttribute_strokeDashOffset_Arg0* value);
    void (*setStrokeDashArray)(Ark_NativePointer node,
                               const Array_CustomObject* value);
    void (*setStrokeLineCap)(Ark_NativePointer node,
                             Ark_Int32 value);
    void (*setStrokeLineJoin)(Ark_NativePointer node,
                              Ark_Int32 value);
    void (*setStrokeMiterLimit)(Ark_NativePointer node,
                                const Type_ShapeAttribute_strokeMiterLimit_Arg0* value);
    void (*setStrokeOpacity)(Ark_NativePointer node,
                             const Type_ShapeAttribute_strokeOpacity_Arg0* value);
    void (*setFillOpacity)(Ark_NativePointer node,
                           const Type_ShapeAttribute_fillOpacity_Arg0* value);
    void (*setStrokeWidth)(Ark_NativePointer node,
                           const Type_ShapeAttribute_strokeWidth_Arg0* value);
    void (*setAntiAlias)(Ark_NativePointer node,
                         Ark_Boolean value);
    void (*setMesh)(Ark_NativePointer node,
                    const Array_CustomObject* value,
                    const Ark_Number* column,
                    const Ark_Number* row);
} GENERATED_ArkUIShapeModifier;

typedef struct GENERATED_ArkUISliderModifier {
    void (*setSliderOptions)(Ark_NativePointer node,
                             const Opt_SliderOptions* options);
    void (*setBlockColor)(Ark_NativePointer node,
                          const ResourceColor* value);
    void (*setTrackColor)(Ark_NativePointer node,
                          const Type_SliderAttribute_trackColor_Arg0* value);
    void (*setSelectedColor)(Ark_NativePointer node,
                             const ResourceColor* value);
    void (*setMinLabel)(Ark_NativePointer node,
                        const Ark_String* value);
    void (*setMaxLabel)(Ark_NativePointer node,
                        const Ark_String* value);
    void (*setShowSteps)(Ark_NativePointer node,
                         Ark_Boolean value);
    void (*setShowTips)(Ark_NativePointer node,
                        Ark_Boolean value,
                        const Opt_ResourceStr* content);
    void (*setTrackThickness)(Ark_NativePointer node,
                              const Ark_Length* value);
    void (*setOnChange)(Ark_NativePointer node,
                        Ark_Function callback);
    void (*setBlockBorderColor)(Ark_NativePointer node,
                                const ResourceColor* value);
    void (*setBlockBorderWidth)(Ark_NativePointer node,
                                const Ark_Length* value);
    void (*setStepColor)(Ark_NativePointer node,
                         const ResourceColor* value);
    void (*setTrackBorderRadius)(Ark_NativePointer node,
                                 const Ark_Length* value);
    void (*setSelectedBorderRadius)(Ark_NativePointer node,
                                    const Ark_Length* value);
    void (*setBlockSize)(Ark_NativePointer node,
                         const Ark_SizeOptions* value);
    void (*setBlockStyle)(Ark_NativePointer node,
                          const Ark_SliderBlockStyle* value);
    void (*setStepSize)(Ark_NativePointer node,
                        const Ark_Length* value);
    void (*setSliderInteractionMode)(Ark_NativePointer node,
                                     Ark_Int32 value);
    void (*setMinResponsiveDistance)(Ark_NativePointer node,
                                     const Ark_Number* value);
    void (*setContentModifier)(Ark_NativePointer node,
                               const Ark_CustomObject* modifier);
    void (*setSlideRange)(Ark_NativePointer node,
                          const Ark_SlideRange* value);
} GENERATED_ArkUISliderModifier;

typedef struct GENERATED_ArkUIBaseSpanModifier {
    void (*setTextBackgroundStyle)(Ark_NativePointer node,
                                   const Ark_TextBackgroundStyle* style);
    void (*setBaselineOffset)(Ark_NativePointer node,
                              const Ark_CustomObject* value);
} GENERATED_ArkUIBaseSpanModifier;

typedef struct GENERATED_ArkUISpanModifier {
    void (*setSpanOptions)(Ark_NativePointer node,
                           const Type_SpanInterface_setSpanOptions_Arg0* value);
    void (*setFont)(Ark_NativePointer node,
                    const Ark_Font* value);
    void (*setFontColor)(Ark_NativePointer node,
                         const ResourceColor* value);
    void (*setFontSize)(Ark_NativePointer node,
                        const Type_SpanAttribute_fontSize_Arg0* value);
    void (*setFontStyle)(Ark_NativePointer node,
                         Ark_Int32 value);
    void (*setFontWeight)(Ark_NativePointer node,
                          const Type_SpanAttribute_fontWeight_Arg0* value);
    void (*setFontFamily)(Ark_NativePointer node,
                          const Type_SpanAttribute_fontFamily_Arg0* value);
    void (*setDecoration)(Ark_NativePointer node,
                          const Ark_DecorationStyleInterface* value);
    void (*setLetterSpacing)(Ark_NativePointer node,
                             const Type_SpanAttribute_letterSpacing_Arg0* value);
    void (*setTextCase)(Ark_NativePointer node,
                        Ark_Int32 value);
    void (*setLineHeight)(Ark_NativePointer node,
                          const Ark_Length* value);
    void (*setTextShadow)(Ark_NativePointer node,
                          const Type_SpanAttribute_textShadow_Arg0* value);
} GENERATED_ArkUISpanModifier;

typedef struct GENERATED_ArkUIStackModifier {
    void (*setStackOptions)(Ark_NativePointer node,
                            const Opt_StackOptions* options);
    void (*setAlignContent)(Ark_NativePointer node,
                            Ark_Int32 value);
    void (*setPointLight)(Ark_NativePointer node,
                          const Ark_PointLightStyle* value);
} GENERATED_ArkUIStackModifier;

typedef struct GENERATED_ArkUIStepperModifier {
    void (*setStepperOptions)(Ark_NativePointer node,
                              const Opt_Type_StepperInterface_setStepperOptions_Arg0* value);
    void (*setOnFinish)(Ark_NativePointer node,
                        Ark_Function callback);
    void (*setOnSkip)(Ark_NativePointer node,
                      Ark_Function callback);
    void (*setOnChange)(Ark_NativePointer node,
                        Ark_Function callback);
    void (*setOnNext)(Ark_NativePointer node,
                      Ark_Function callback);
    void (*setOnPrevious)(Ark_NativePointer node,
                          Ark_Function callback);
} GENERATED_ArkUIStepperModifier;

typedef struct GENERATED_ArkUIStepperItemModifier {
    void (*setStepperItemOptions)(Ark_NativePointer node);
    void (*setPrevLabel)(Ark_NativePointer node,
                         const Ark_String* value);
    void (*setNextLabel)(Ark_NativePointer node,
                         const Ark_String* value);
    void (*setStatus)(Ark_NativePointer node,
                      const Opt_ItemState* value);
} GENERATED_ArkUIStepperItemModifier;

typedef struct GENERATED_ArkUISwiperModifier {
    void (*setSwiperOptions)(Ark_NativePointer node,
                             const Opt_SwiperController* controller);
    void (*setIndex)(Ark_NativePointer node,
                     const Ark_Number* value);
    void (*setAutoPlay)(Ark_NativePointer node,
                        Ark_Boolean value);
    void (*setInterval)(Ark_NativePointer node,
                        const Ark_Number* value);
    void (*setIndicator)(Ark_NativePointer node,
                         const Type_SwiperAttribute_indicator_Arg0* value);
    void (*setDisplayArrow)(Ark_NativePointer node,
                            const Type_SwiperAttribute_displayArrow_Arg0* value,
                            const Opt_Boolean* isHoverShow);
    void (*setLoop)(Ark_NativePointer node,
                    Ark_Boolean value);
    void (*setDuration)(Ark_NativePointer node,
                        const Ark_Number* value);
    void (*setVertical)(Ark_NativePointer node,
                        Ark_Boolean value);
    void (*setItemSpace)(Ark_NativePointer node,
                         const Type_SwiperAttribute_itemSpace_Arg0* value);
    void (*setDisplayMode)(Ark_NativePointer node,
                           Ark_Int32 value);
    void (*setCachedCount)(Ark_NativePointer node,
                           const Ark_Number* value);
    void (*setDisplayCount)(Ark_NativePointer node,
                            const Type_SwiperAttribute_displayCount_Arg0* value,
                            const Opt_Boolean* swipeByGroup);
    void (*setEffectMode)(Ark_NativePointer node,
                          Ark_Int32 value);
    void (*setDisableSwipe)(Ark_NativePointer node,
                            Ark_Boolean value);
    void (*setCurve)(Ark_NativePointer node,
                     const Type_SwiperAttribute_curve_Arg0* value);
    void (*setOnChange)(Ark_NativePointer node,
                        Ark_Function event);
    void (*setIndicatorStyle)(Ark_NativePointer node,
                              const Opt_IndicatorStyle* value);
    void (*setPrevMargin)(Ark_NativePointer node,
                          const Ark_Length* value,
                          const Opt_Boolean* ignoreBlank);
    void (*setNextMargin)(Ark_NativePointer node,
                          const Ark_Length* value,
                          const Opt_Boolean* ignoreBlank);
    void (*setOnAnimationStart)(Ark_NativePointer node,
                                Ark_Function event);
    void (*setOnAnimationEnd)(Ark_NativePointer node,
                              Ark_Function event);
    void (*setOnGestureSwipe)(Ark_NativePointer node,
                              Ark_Function event);
    void (*setNestedScroll)(Ark_NativePointer node,
                            Ark_Int32 value);
    void (*setCustomContentTransition)(Ark_NativePointer node,
                                       const Ark_SwiperContentAnimatedTransition* transition);
    void (*setOnContentDidScroll)(Ark_NativePointer node,
                                  Ark_Function handler);
    void (*setIndicatorInteractive)(Ark_NativePointer node,
                                    Ark_Boolean value);
} GENERATED_ArkUISwiperModifier;

typedef struct GENERATED_ArkUISymbolGlyphModifier {
    void (*setSymbolGlyphOptions)(Ark_NativePointer node,
                                  const Opt_Resource* value);
    void (*setFontSize)(Ark_NativePointer node,
                        const Type_SymbolGlyphAttribute_fontSize_Arg0* value);
    void (*setFontColor)(Ark_NativePointer node,
                         const Array_ResourceColor* value);
    void (*setFontWeight)(Ark_NativePointer node,
                          const Type_SymbolGlyphAttribute_fontWeight_Arg0* value);
    void (*setEffectStrategy)(Ark_NativePointer node,
                              Ark_Int32 value);
    void (*setRenderingStrategy)(Ark_NativePointer node,
                                 Ark_Int32 value);
    void (*setSymbolEffect0)(Ark_NativePointer node,
                             const Ark_SymbolEffect* symbolEffect,
                             const Opt_Boolean* isActive);
    void (*setSymbolEffect1)(Ark_NativePointer node,
                             const Ark_SymbolEffect* symbolEffect,
                             const Opt_Number* triggerValue);
} GENERATED_ArkUISymbolGlyphModifier;

typedef struct GENERATED_ArkUISymbolSpanModifier {
    void (*setSymbolSpanOptions)(Ark_NativePointer node,
                                 const Ark_Resource* value);
    void (*setFontSize)(Ark_NativePointer node,
                        const Type_SymbolSpanAttribute_fontSize_Arg0* value);
    void (*setFontColor)(Ark_NativePointer node,
                         const Array_ResourceColor* value);
    void (*setFontWeight)(Ark_NativePointer node,
                          const Type_SymbolSpanAttribute_fontWeight_Arg0* value);
    void (*setEffectStrategy)(Ark_NativePointer node,
                              Ark_Int32 value);
    void (*setRenderingStrategy)(Ark_NativePointer node,
                                 Ark_Int32 value);
} GENERATED_ArkUISymbolSpanModifier;

typedef struct GENERATED_ArkUITabsModifier {
    void (*setTabsOptions)(Ark_NativePointer node,
                           const Opt_Type_TabsInterface_setTabsOptions_Arg0* value);
    void (*setVertical)(Ark_NativePointer node,
                        Ark_Boolean value);
    void (*setBarPosition)(Ark_NativePointer node,
                           Ark_Int32 value);
    void (*setScrollable)(Ark_NativePointer node,
                          Ark_Boolean value);
    void (*setBarMode0)(Ark_NativePointer node,
                        Ark_Int32 value);
    void (*setBarMode1)(Ark_NativePointer node,
                        Ark_Int32 value,
                        const Ark_ScrollableBarModeOptions* options);
    void (*setBarMode2)(Ark_NativePointer node,
                        Ark_Int32 value,
                        const Opt_ScrollableBarModeOptions* options);
    void (*setBarWidth)(Ark_NativePointer node,
                        const Ark_Length* value);
    void (*setBarHeight)(Ark_NativePointer node,
                         const Ark_Length* value);
    void (*setAnimationDuration)(Ark_NativePointer node,
                                 const Ark_Number* value);
    void (*setAnimationMode)(Ark_NativePointer node,
                             const Opt_AnimationMode* mode);
    void (*setEdgeEffect)(Ark_NativePointer node,
                          const Opt_EdgeEffect* edgeEffect);
    void (*setOnChange)(Ark_NativePointer node,
                        Ark_Function event);
    void (*setOnTabBarClick)(Ark_NativePointer node,
                             Ark_Function event);
    void (*setOnAnimationStart)(Ark_NativePointer node,
                                Ark_Function handler);
    void (*setOnAnimationEnd)(Ark_NativePointer node,
                              Ark_Function handler);
    void (*setOnGestureSwipe)(Ark_NativePointer node,
                              Ark_Function handler);
    void (*setFadingEdge)(Ark_NativePointer node,
                          Ark_Boolean value);
    void (*setDivider)(Ark_NativePointer node,
                       const Type_TabsAttribute_divider_Arg0* value);
    void (*setBarOverlap)(Ark_NativePointer node,
                          Ark_Boolean value);
    void (*setBarBackgroundColor)(Ark_NativePointer node,
                                  const ResourceColor* value);
    void (*setBarGridAlign)(Ark_NativePointer node,
                            const Ark_BarGridColumnOptions* value);
    void (*setCustomContentTransition)(Ark_NativePointer node,
                                       Ark_Function delegate);
    void (*setBarBackgroundBlurStyle)(Ark_NativePointer node,
                                      Ark_Int32 value);
    void (*setOnContentWillChange)(Ark_NativePointer node,
                                   Ark_Function handler);
} GENERATED_ArkUITabsModifier;

typedef struct GENERATED_ArkUITabContentModifier {
    void (*setTabContentOptions)(Ark_NativePointer node);
    void (*setTabBar0)(Ark_NativePointer node,
                       const Type_TabContentAttribute_tabBar_Arg0* value);
    void (*setTabBar1)(Ark_NativePointer node,
                       const Type_TabContentAttribute_tabBar1_Arg0* value);
    void (*setOnWillShow)(Ark_NativePointer node,
                          Ark_Function event);
    void (*setOnWillHide)(Ark_NativePointer node,
                          Ark_Function event);
} GENERATED_ArkUITabContentModifier;

typedef struct GENERATED_ArkUITextModifier {
    void (*setTextOptions)(Ark_NativePointer node,
                           const Opt_Type_TextInterface_setTextOptions_Arg0* content,
                           const Opt_TextOptions* value);
    void (*setFont0)(Ark_NativePointer node,
                     const Ark_Font* value);
    void (*setFont1)(Ark_NativePointer node,
                     const Ark_Font* fontValue,
                     const Opt_FontSettingOptions* options);
    void (*setFontColor)(Ark_NativePointer node,
                         const ResourceColor* value);
    void (*setFontSize)(Ark_NativePointer node,
                        const Type_TextAttribute_fontSize_Arg0* value);
    void (*setMinFontSize)(Ark_NativePointer node,
                           const Type_TextAttribute_minFontSize_Arg0* value);
    void (*setMaxFontSize)(Ark_NativePointer node,
                           const Type_TextAttribute_maxFontSize_Arg0* value);
    void (*setMinFontScale)(Ark_NativePointer node,
                            const Type_TextAttribute_minFontScale_Arg0* scale);
    void (*setMaxFontScale)(Ark_NativePointer node,
                            const Type_TextAttribute_maxFontScale_Arg0* scale);
    void (*setFontStyle)(Ark_NativePointer node,
                         Ark_Int32 value);
    void (*setFontWeight0)(Ark_NativePointer node,
                           const Type_TextAttribute_fontWeight_Arg0* value);
    void (*setFontWeight1)(Ark_NativePointer node,
                           const Type_TextAttribute_fontWeight1_Arg0* weight,
                           const Opt_FontSettingOptions* options);
    void (*setLineSpacing)(Ark_NativePointer node,
                           const Ark_CustomObject* value);
    void (*setTextAlign)(Ark_NativePointer node,
                         Ark_Int32 value);
    void (*setLineHeight)(Ark_NativePointer node,
                          const Type_TextAttribute_lineHeight_Arg0* value);
    void (*setTextOverflow)(Ark_NativePointer node,
                            const Type_TextAttribute_textOverflow_Arg0* value);
    void (*setFontFamily)(Ark_NativePointer node,
                          const Type_TextAttribute_fontFamily_Arg0* value);
    void (*setMaxLines)(Ark_NativePointer node,
                        const Ark_Number* value);
    void (*setDecoration)(Ark_NativePointer node,
                          const Ark_DecorationStyleInterface* value);
    void (*setLetterSpacing)(Ark_NativePointer node,
                             const Type_TextAttribute_letterSpacing_Arg0* value);
    void (*setTextCase)(Ark_NativePointer node,
                        Ark_Int32 value);
    void (*setBaselineOffset)(Ark_NativePointer node,
                              const Type_TextAttribute_baselineOffset_Arg0* value);
    void (*setCopyOption)(Ark_NativePointer node,
                          Ark_Int32 value);
    void (*setDraggable)(Ark_NativePointer node,
                         Ark_Boolean value);
    void (*setTextShadow)(Ark_NativePointer node,
                          const Type_TextAttribute_textShadow_Arg0* value);
    void (*setHeightAdaptivePolicy)(Ark_NativePointer node,
                                    Ark_Int32 value);
    void (*setTextIndent)(Ark_NativePointer node,
                          const Ark_Length* value);
    void (*setWordBreak)(Ark_NativePointer node,
                         Ark_Int32 value);
    void (*setLineBreakStrategy)(Ark_NativePointer node,
                                 Ark_Int32 strategy);
    void (*setOnCopy)(Ark_NativePointer node,
                      Ark_Function callback);
    void (*setSelection)(Ark_NativePointer node,
                         const Ark_Number* selectionStart,
                         const Ark_Number* selectionEnd);
    void (*setEllipsisMode)(Ark_NativePointer node,
                            Ark_Int32 value);
    void (*setEnableDataDetector)(Ark_NativePointer node,
                                  Ark_Boolean enable);
    void (*setDataDetectorConfig)(Ark_NativePointer node,
                                  const Ark_TextDataDetectorConfig* config);
    void (*setBindSelectionMenu)(Ark_NativePointer node,
                                 Ark_Int32 spanType,
                                 const CustomBuilder* content,
                                 Ark_Int32 responseType,
                                 const Opt_SelectionMenuOptions* options);
    void (*setOnTextSelectionChange)(Ark_NativePointer node,
                                     Ark_Function callback);
    void (*setFontFeature)(Ark_NativePointer node,
                           const Ark_String* value);
    void (*setPrivacySensitive)(Ark_NativePointer node,
                                Ark_Boolean supported);
    void (*setTextSelectable)(Ark_NativePointer node,
                              Ark_Int32 mode);
    void (*setEditMenuOptions)(Ark_NativePointer node,
                               const Ark_Materialized* editMenu);
    void (*setHalfLeading)(Ark_NativePointer node,
                           Ark_Boolean halfLeading);
} GENERATED_ArkUITextModifier;

typedef struct GENERATED_ArkUITextAreaModifier {
    void (*setTextAreaOptions)(Ark_NativePointer node,
                               const Opt_TextAreaOptions* value);
    void (*setPlaceholderColor)(Ark_NativePointer node,
                                const ResourceColor* value);
    void (*setPlaceholderFont)(Ark_NativePointer node,
                               const Ark_Font* value);
    void (*setEnterKeyType)(Ark_NativePointer node,
                            Ark_Int32 value);
    void (*setTextAlign)(Ark_NativePointer node,
                         Ark_Int32 value);
    void (*setCaretColor)(Ark_NativePointer node,
                          const ResourceColor* value);
    void (*setFontColor)(Ark_NativePointer node,
                         const ResourceColor* value);
    void (*setFontSize)(Ark_NativePointer node,
                        const Ark_Length* value);
    void (*setFontStyle)(Ark_NativePointer node,
                         Ark_Int32 value);
    void (*setFontWeight)(Ark_NativePointer node,
                          const Type_TextAreaAttribute_fontWeight_Arg0* value);
    void (*setFontFamily)(Ark_NativePointer node,
                          const ResourceStr* value);
    void (*setTextOverflow)(Ark_NativePointer node,
                            Ark_Int32 value);
    void (*setTextIndent)(Ark_NativePointer node,
                          const Ark_Length* value);
    void (*setInputFilter)(Ark_NativePointer node,
                           const ResourceStr* value,
                           const Opt_Function* error);
    void (*setCaretStyle)(Ark_NativePointer node,
                          const Ark_CaretStyle* value);
    void (*setSelectedBackgroundColor)(Ark_NativePointer node,
                                       const ResourceColor* value);
    void (*setOnSubmit)(Ark_NativePointer node,
                        Ark_Function callback);
    void (*setOnChange)(Ark_NativePointer node,
                        Ark_Function callback);
    void (*setOnTextSelectionChange)(Ark_NativePointer node,
                                     Ark_Function callback);
    void (*setOnContentScroll)(Ark_NativePointer node,
                               Ark_Function callback);
    void (*setOnEditChange)(Ark_NativePointer node,
                            Ark_Function callback);
    void (*setOnCopy)(Ark_NativePointer node,
                      Ark_Function callback);
    void (*setOnCut)(Ark_NativePointer node,
                     Ark_Function callback);
    void (*setOnPaste)(Ark_NativePointer node,
                       Ark_Function callback);
    void (*setCopyOption)(Ark_NativePointer node,
                          Ark_Int32 value);
    void (*setEnableKeyboardOnFocus)(Ark_NativePointer node,
                                     Ark_Boolean value);
    void (*setMaxLength)(Ark_NativePointer node,
                         const Ark_Number* value);
    void (*setShowCounter)(Ark_NativePointer node,
                           Ark_Boolean value,
                           const Opt_InputCounterOptions* options);
    void (*setStyle)(Ark_NativePointer node,
                     Ark_Int32 value);
    void (*setBarState)(Ark_NativePointer node,
                        Ark_Int32 value);
    void (*setSelectionMenuHidden)(Ark_NativePointer node,
                                   Ark_Boolean value);
    void (*setMinFontSize)(Ark_NativePointer node,
                           const Type_TextAreaAttribute_minFontSize_Arg0* value);
    void (*setMaxFontSize)(Ark_NativePointer node,
                           const Type_TextAreaAttribute_maxFontSize_Arg0* value);
    void (*setHeightAdaptivePolicy)(Ark_NativePointer node,
                                    Ark_Int32 value);
    void (*setMaxLines)(Ark_NativePointer node,
                        const Ark_Number* value);
    void (*setWordBreak)(Ark_NativePointer node,
                         Ark_Int32 value);
    void (*setLineBreakStrategy)(Ark_NativePointer node,
                                 Ark_Int32 strategy);
    void (*setCustomKeyboard)(Ark_NativePointer node,
                              const CustomBuilder* value,
                              const Opt_KeyboardOptions* options);
    void (*setDecoration)(Ark_NativePointer node,
                          const Ark_TextDecorationOptions* value);
    void (*setLetterSpacing)(Ark_NativePointer node,
                             const Type_TextAreaAttribute_letterSpacing_Arg0* value);
    void (*setLineSpacing)(Ark_NativePointer node,
                           const Ark_CustomObject* value);
    void (*setLineHeight)(Ark_NativePointer node,
                          const Type_TextAreaAttribute_lineHeight_Arg0* value);
    void (*setType)(Ark_NativePointer node,
                    Ark_Int32 value);
    void (*setEnableAutoFill)(Ark_NativePointer node,
                              Ark_Boolean value);
    void (*setContentType)(Ark_NativePointer node,
                           Ark_Int32 contentType);
    void (*setFontFeature)(Ark_NativePointer node,
                           const Ark_String* value);
    void (*setOnWillInsert)(Ark_NativePointer node,
                            Ark_Function callback);
    void (*setOnDidInsert)(Ark_NativePointer node,
                           Ark_Function callback);
    void (*setOnWillDelete)(Ark_NativePointer node,
                            Ark_Function callback);
    void (*setOnDidDelete)(Ark_NativePointer node,
                           Ark_Function callback);
    void (*setEditMenuOptions)(Ark_NativePointer node,
                               const Ark_Materialized* editMenu);
    void (*setEnablePreviewText)(Ark_NativePointer node,
                                 Ark_Boolean enable);
} GENERATED_ArkUITextAreaModifier;

typedef struct GENERATED_ArkUITextClockModifier {
    void (*setTextClockOptions)(Ark_NativePointer node,
                                const Opt_Type_TextClockInterface_setTextClockOptions_Arg0* options);
    void (*setFormat)(Ark_NativePointer node,
                      const Ark_String* value);
    void (*setOnDateChange)(Ark_NativePointer node,
                            Ark_Function event);
    void (*setFontColor)(Ark_NativePointer node,
                         const ResourceColor* value);
    void (*setFontSize)(Ark_NativePointer node,
                        const Ark_Length* value);
    void (*setFontStyle)(Ark_NativePointer node,
                         Ark_Int32 value);
    void (*setFontWeight)(Ark_NativePointer node,
                          const Type_TextClockAttribute_fontWeight_Arg0* value);
    void (*setFontFamily)(Ark_NativePointer node,
                          const ResourceStr* value);
    void (*setTextShadow)(Ark_NativePointer node,
                          const Type_TextClockAttribute_textShadow_Arg0* value);
    void (*setFontFeature)(Ark_NativePointer node,
                           const Ark_String* value);
    void (*setContentModifier)(Ark_NativePointer node,
                               const Ark_CustomObject* modifier);
    void (*setDateTimeOptions)(Ark_NativePointer node,
                               const Opt_CustomObject* dateTimeOptions);
} GENERATED_ArkUITextClockModifier;

typedef struct GENERATED_ArkUITextInputModifier {
    void (*setTextInputOptions)(Ark_NativePointer node,
                                const Opt_TextInputOptions* value);
    void (*setType)(Ark_NativePointer node,
                    Ark_Int32 value);
    void (*setContentType)(Ark_NativePointer node,
                           Ark_Int32 value);
    void (*setPlaceholderColor)(Ark_NativePointer node,
                                const ResourceColor* value);
    void (*setTextOverflow)(Ark_NativePointer node,
                            Ark_Int32 value);
    void (*setTextIndent)(Ark_NativePointer node,
                          const Ark_Length* value);
    void (*setPlaceholderFont)(Ark_NativePointer node,
                               const Opt_Font* value);
    void (*setEnterKeyType)(Ark_NativePointer node,
                            Ark_Int32 value);
    void (*setCaretColor)(Ark_NativePointer node,
                          const ResourceColor* value);
    void (*setOnEditChanged)(Ark_NativePointer node,
                             Ark_Function callback);
    void (*setOnEditChange)(Ark_NativePointer node,
                            Ark_Function callback);
    void (*setOnSubmit)(Ark_NativePointer node,
                        Ark_Function callback);
    void (*setOnChange)(Ark_NativePointer node,
                        Ark_Function callback);
    void (*setOnTextSelectionChange)(Ark_NativePointer node,
                                     Ark_Function callback);
    void (*setOnContentScroll)(Ark_NativePointer node,
                               Ark_Function callback);
    void (*setMaxLength)(Ark_NativePointer node,
                         const Ark_Number* value);
    void (*setFontColor)(Ark_NativePointer node,
                         const ResourceColor* value);
    void (*setFontSize)(Ark_NativePointer node,
                        const Ark_Length* value);
    void (*setFontStyle)(Ark_NativePointer node,
                         Ark_Int32 value);
    void (*setFontWeight)(Ark_NativePointer node,
                          const Type_TextInputAttribute_fontWeight_Arg0* value);
    void (*setFontFamily)(Ark_NativePointer node,
                          const ResourceStr* value);
    void (*setInputFilter)(Ark_NativePointer node,
                           const ResourceStr* value,
                           const Opt_Function* error);
    void (*setOnCopy)(Ark_NativePointer node,
                      Ark_Function callback);
    void (*setOnCut)(Ark_NativePointer node,
                     Ark_Function callback);
    void (*setOnPaste)(Ark_NativePointer node,
                       Ark_Function callback);
    void (*setCopyOption)(Ark_NativePointer node,
                          Ark_Int32 value);
    void (*setShowPasswordIcon)(Ark_NativePointer node,
                                Ark_Boolean value);
    void (*setTextAlign)(Ark_NativePointer node,
                         Ark_Int32 value);
    void (*setStyle)(Ark_NativePointer node,
                     const Type_TextInputAttribute_style_Arg0* value);
    void (*setCaretStyle)(Ark_NativePointer node,
                          const Ark_CaretStyle* value);
    void (*setSelectedBackgroundColor)(Ark_NativePointer node,
                                       const ResourceColor* value);
    void (*setCaretPosition)(Ark_NativePointer node,
                             const Ark_Number* value);
    void (*setEnableKeyboardOnFocus)(Ark_NativePointer node,
                                     Ark_Boolean value);
    void (*setPasswordIcon)(Ark_NativePointer node,
                            const Ark_PasswordIcon* value);
    void (*setShowError)(Ark_NativePointer node,
                         const Opt_Type_TextInputAttribute_showError_Arg0* value);
    void (*setShowUnit)(Ark_NativePointer node,
                        const CustomBuilder* value);
    void (*setShowUnderline)(Ark_NativePointer node,
                             Ark_Boolean value);
    void (*setUnderlineColor)(Ark_NativePointer node,
                              const Type_TextInputAttribute_underlineColor_Arg0* value);
    void (*setSelectionMenuHidden)(Ark_NativePointer node,
                                   Ark_Boolean value);
    void (*setBarState)(Ark_NativePointer node,
                        Ark_Int32 value);
    void (*setMaxLines)(Ark_NativePointer node,
                        const Ark_Number* value);
    void (*setWordBreak)(Ark_NativePointer node,
                         Ark_Int32 value);
    void (*setLineBreakStrategy)(Ark_NativePointer node,
                                 Ark_Int32 strategy);
    void (*setCustomKeyboard)(Ark_NativePointer node,
                              const CustomBuilder* value,
                              const Opt_KeyboardOptions* options);
    void (*setShowCounter)(Ark_NativePointer node,
                           Ark_Boolean value,
                           const Opt_InputCounterOptions* options);
    void (*setCancelButton)(Ark_NativePointer node,
                            const Type_TextInputAttribute_cancelButton_Arg0* value);
    void (*setSelectAll)(Ark_NativePointer node,
                         Ark_Boolean value);
    void (*setMinFontSize)(Ark_NativePointer node,
                           const Type_TextInputAttribute_minFontSize_Arg0* value);
    void (*setMaxFontSize)(Ark_NativePointer node,
                           const Type_TextInputAttribute_maxFontSize_Arg0* value);
    void (*setHeightAdaptivePolicy)(Ark_NativePointer node,
                                    Ark_Int32 value);
    void (*setEnableAutoFill)(Ark_NativePointer node,
                              Ark_Boolean value);
    void (*setDecoration)(Ark_NativePointer node,
                          const Ark_TextDecorationOptions* value);
    void (*setLetterSpacing)(Ark_NativePointer node,
                             const Type_TextInputAttribute_letterSpacing_Arg0* value);
    void (*setLineHeight)(Ark_NativePointer node,
                          const Type_TextInputAttribute_lineHeight_Arg0* value);
    void (*setPasswordRules)(Ark_NativePointer node,
                             const Ark_String* value);
    void (*setFontFeature)(Ark_NativePointer node,
                           const Ark_String* value);
    void (*setShowPassword)(Ark_NativePointer node,
                            Ark_Boolean visible);
    void (*setOnSecurityStateChange)(Ark_NativePointer node,
                                     Ark_Function callback);
    void (*setOnWillInsert)(Ark_NativePointer node,
                            Ark_Function callback);
    void (*setOnDidInsert)(Ark_NativePointer node,
                           Ark_Function callback);
    void (*setOnWillDelete)(Ark_NativePointer node,
                            Ark_Function callback);
    void (*setOnDidDelete)(Ark_NativePointer node,
                           Ark_Function callback);
    void (*setEditMenuOptions)(Ark_NativePointer node,
                               const Ark_Materialized* editMenu);
    void (*setEnablePreviewText)(Ark_NativePointer node,
                                 Ark_Boolean enable);
} GENERATED_ArkUITextInputModifier;

typedef struct GENERATED_ArkUITextPickerModifier {
    void (*setTextPickerOptions)(Ark_NativePointer node,
                                 const Opt_TextPickerOptions* options);
    void (*setDefaultPickerItemHeight)(Ark_NativePointer node,
                                       const Type_TextPickerAttribute_defaultPickerItemHeight_Arg0* value);
    void (*setCanLoop)(Ark_NativePointer node,
                       Ark_Boolean value);
    void (*setDisappearTextStyle)(Ark_NativePointer node,
                                  const Ark_PickerTextStyle* value);
    void (*setTextStyle)(Ark_NativePointer node,
                         const Ark_PickerTextStyle* value);
    void (*setSelectedTextStyle)(Ark_NativePointer node,
                                 const Ark_PickerTextStyle* value);
    void (*setOnAccept)(Ark_NativePointer node,
                        Ark_Function callback);
    void (*setOnCancel)(Ark_NativePointer node,
                        Ark_Function callback);
    void (*setOnChange)(Ark_NativePointer node,
                        Ark_Function callback);
    void (*setSelectedIndex)(Ark_NativePointer node,
                             const Type_TextPickerAttribute_selectedIndex_Arg0* value);
    void (*setDivider)(Ark_NativePointer node,
                       const Type_TextPickerAttribute_divider_Arg0* value);
    void (*setGradientHeight)(Ark_NativePointer node,
                              const Ark_Length* value);
} GENERATED_ArkUITextPickerModifier;

typedef struct GENERATED_ArkUITextTimerModifier {
    void (*setTextTimerOptions)(Ark_NativePointer node,
                                const Opt_TextTimerOptions* options);
    void (*setFormat)(Ark_NativePointer node,
                      const Ark_String* value);
    void (*setFontColor)(Ark_NativePointer node,
                         const ResourceColor* value);
    void (*setFontSize)(Ark_NativePointer node,
                        const Ark_Length* value);
    void (*setFontStyle)(Ark_NativePointer node,
                         Ark_Int32 value);
    void (*setFontWeight)(Ark_NativePointer node,
                          const Type_TextTimerAttribute_fontWeight_Arg0* value);
    void (*setFontFamily)(Ark_NativePointer node,
                          const ResourceStr* value);
    void (*setOnTimer)(Ark_NativePointer node,
                       Ark_Function event);
    void (*setTextShadow)(Ark_NativePointer node,
                          const Type_TextTimerAttribute_textShadow_Arg0* value);
    void (*setContentModifier)(Ark_NativePointer node,
                               const Ark_CustomObject* modifier);
} GENERATED_ArkUITextTimerModifier;

typedef struct GENERATED_ArkUITimePickerModifier {
    void (*setTimePickerOptions)(Ark_NativePointer node,
                                 const Opt_TimePickerOptions* options);
    void (*setUseMilitaryTime)(Ark_NativePointer node,
                               Ark_Boolean value);
    void (*setLoop)(Ark_NativePointer node,
                    Ark_Boolean value);
    void (*setDisappearTextStyle)(Ark_NativePointer node,
                                  const Ark_PickerTextStyle* value);
    void (*setTextStyle)(Ark_NativePointer node,
                         const Ark_PickerTextStyle* value);
    void (*setSelectedTextStyle)(Ark_NativePointer node,
                                 const Ark_PickerTextStyle* value);
    void (*setDateTimeOptions)(Ark_NativePointer node,
                               const Ark_CustomObject* value);
    void (*setOnChange)(Ark_NativePointer node,
                        Ark_Function callback);
    void (*setEnableHapticFeedback)(Ark_NativePointer node,
                                    Ark_Boolean enable);
} GENERATED_ArkUITimePickerModifier;

typedef struct GENERATED_ArkUIToggleModifier {
    void (*setToggleOptions)(Ark_NativePointer node,
                             const Ark_ToggleOptions* options);
    void (*setOnChange)(Ark_NativePointer node,
                        Ark_Function callback);
    void (*setContentModifier)(Ark_NativePointer node,
                               const Ark_CustomObject* modifier);
    void (*setSelectedColor)(Ark_NativePointer node,
                             const ResourceColor* value);
    void (*setSwitchPointColor)(Ark_NativePointer node,
                                const ResourceColor* color);
    void (*setSwitchStyle)(Ark_NativePointer node,
                           const Ark_SwitchStyle* value);
} GENERATED_ArkUIToggleModifier;

typedef struct GENERATED_ArkUIVideoModifier {
    void (*setVideoOptions)(Ark_NativePointer node,
                            const Ark_VideoOptions* value);
    void (*setMuted)(Ark_NativePointer node,
                     Ark_Boolean value);
    void (*setAutoPlay)(Ark_NativePointer node,
                        Ark_Boolean value);
    void (*setControls)(Ark_NativePointer node,
                        Ark_Boolean value);
    void (*setLoop)(Ark_NativePointer node,
                    Ark_Boolean value);
    void (*setObjectFit)(Ark_NativePointer node,
                         Ark_Int32 value);
    void (*setOnStart)(Ark_NativePointer node,
                       Ark_Function event);
    void (*setOnPause)(Ark_NativePointer node,
                       Ark_Function event);
    void (*setOnFinish)(Ark_NativePointer node,
                        Ark_Function event);
    void (*setOnFullscreenChange)(Ark_NativePointer node,
                                  Ark_Function callback);
    void (*setOnPrepared)(Ark_NativePointer node,
                          Ark_Function callback);
    void (*setOnSeeking)(Ark_NativePointer node,
                         Ark_Function callback);
    void (*setOnSeeked)(Ark_NativePointer node,
                        Ark_Function callback);
    void (*setOnUpdate)(Ark_NativePointer node,
                        Ark_Function callback);
    void (*setOnError)(Ark_NativePointer node,
                       Ark_Function event);
    void (*setOnStop)(Ark_NativePointer node,
                      Ark_Function event);
    void (*setEnableAnalyzer)(Ark_NativePointer node,
                              Ark_Boolean enable);
    void (*setAnalyzerConfig)(Ark_NativePointer node,
                              const Ark_ImageAnalyzerConfig* config);
} GENERATED_ArkUIVideoModifier;

typedef struct GENERATED_ArkUIWebModifier {
    void (*setWebOptions)(Ark_NativePointer node,
                          const Ark_WebOptions* value);
    void (*setJavaScriptAccess)(Ark_NativePointer node,
                                Ark_Boolean javaScriptAccess);
    void (*setFileAccess)(Ark_NativePointer node,
                          Ark_Boolean fileAccess);
    void (*setOnlineImageAccess)(Ark_NativePointer node,
                                 Ark_Boolean onlineImageAccess);
    void (*setDomStorageAccess)(Ark_NativePointer node,
                                Ark_Boolean domStorageAccess);
    void (*setImageAccess)(Ark_NativePointer node,
                           Ark_Boolean imageAccess);
    void (*setMixedMode)(Ark_NativePointer node,
                         Ark_Int32 mixedMode);
    void (*setZoomAccess)(Ark_NativePointer node,
                          Ark_Boolean zoomAccess);
    void (*setGeolocationAccess)(Ark_NativePointer node,
                                 Ark_Boolean geolocationAccess);
    void (*setJavaScriptProxy)(Ark_NativePointer node,
                               const Ark_JavaScriptProxy* javaScriptProxy);
    void (*setPassword)(Ark_NativePointer node,
                        Ark_Boolean password);
    void (*setCacheMode)(Ark_NativePointer node,
                         Ark_Int32 cacheMode);
    void (*setDarkMode)(Ark_NativePointer node,
                        Ark_Int32 mode);
    void (*setForceDarkAccess)(Ark_NativePointer node,
                               Ark_Boolean access);
    void (*setMediaOptions)(Ark_NativePointer node,
                            const Ark_WebMediaOptions* options);
    void (*setTableData)(Ark_NativePointer node,
                         Ark_Boolean tableData);
    void (*setWideViewModeAccess)(Ark_NativePointer node,
                                  Ark_Boolean wideViewModeAccess);
    void (*setOverviewModeAccess)(Ark_NativePointer node,
                                  Ark_Boolean overviewModeAccess);
    void (*setOverScrollMode)(Ark_NativePointer node,
                              Ark_Int32 mode);
    void (*setTextZoomAtio)(Ark_NativePointer node,
                            const Ark_Number* textZoomAtio);
    void (*setTextZoomRatio)(Ark_NativePointer node,
                             const Ark_Number* textZoomRatio);
    void (*setDatabaseAccess)(Ark_NativePointer node,
                              Ark_Boolean databaseAccess);
    void (*setInitialScale)(Ark_NativePointer node,
                            const Ark_Number* percent);
    void (*setUserAgent)(Ark_NativePointer node,
                         const Ark_String* userAgent);
    void (*setMetaViewport)(Ark_NativePointer node,
                            Ark_Boolean enabled);
    void (*setOnPageEnd)(Ark_NativePointer node,
                         Ark_Function callback);
    void (*setOnPageBegin)(Ark_NativePointer node,
                           Ark_Function callback);
    void (*setOnProgressChange)(Ark_NativePointer node,
                                Ark_Function callback);
    void (*setOnTitleReceive)(Ark_NativePointer node,
                              Ark_Function callback);
    void (*setOnGeolocationHide)(Ark_NativePointer node,
                                 Ark_Function callback);
    void (*setOnGeolocationShow)(Ark_NativePointer node,
                                 Ark_Function callback);
    void (*setOnRequestSelected)(Ark_NativePointer node,
                                 Ark_Function callback);
    void (*setOnAlert)(Ark_NativePointer node,
                       Ark_Function callback);
    void (*setOnBeforeUnload)(Ark_NativePointer node,
                              Ark_Function callback);
    void (*setOnConfirm)(Ark_NativePointer node,
                         Ark_Function callback);
    void (*setOnPrompt)(Ark_NativePointer node,
                        Ark_Function callback);
    void (*setOnConsole)(Ark_NativePointer node,
                         Ark_Function callback);
    void (*setOnErrorReceive)(Ark_NativePointer node,
                              Ark_Function callback);
    void (*setOnHttpErrorReceive)(Ark_NativePointer node,
                                  Ark_Function callback);
    void (*setOnDownloadStart)(Ark_NativePointer node,
                               Ark_Function callback);
    void (*setOnRefreshAccessedHistory)(Ark_NativePointer node,
                                        Ark_Function callback);
    void (*setOnUrlLoadIntercept)(Ark_NativePointer node,
                                  Ark_Function callback);
    void (*setOnSslErrorReceive)(Ark_NativePointer node,
                                 Ark_Function callback);
    void (*setOnRenderExited0)(Ark_NativePointer node,
                               Ark_Function callback);
    void (*setOnShowFileSelector)(Ark_NativePointer node,
                                  Ark_Function callback);
    void (*setOnRenderExited1)(Ark_NativePointer node,
                               Ark_Function callback);
    void (*setOnFileSelectorShow)(Ark_NativePointer node,
                                  Ark_Function callback);
    void (*setOnResourceLoad)(Ark_NativePointer node,
                              Ark_Function callback);
    void (*setOnFullScreenExit)(Ark_NativePointer node,
                                Ark_Function callback);
    void (*setOnFullScreenEnter)(Ark_NativePointer node,
                                 Ark_Function callback);
    void (*setOnScaleChange)(Ark_NativePointer node,
                             Ark_Function callback);
    void (*setOnHttpAuthRequest)(Ark_NativePointer node,
                                 Ark_Function callback);
    void (*setOnInterceptRequest)(Ark_NativePointer node,
                                  Ark_Function callback);
    void (*setOnPermissionRequest)(Ark_NativePointer node,
                                   Ark_Function callback);
    void (*setOnScreenCaptureRequest)(Ark_NativePointer node,
                                      Ark_Function callback);
    void (*setOnContextMenuShow)(Ark_NativePointer node,
                                 Ark_Function callback);
    void (*setOnContextMenuHide)(Ark_NativePointer node,
                                 Ark_Function callback);
    void (*setMediaPlayGestureAccess)(Ark_NativePointer node,
                                      Ark_Boolean access);
    void (*setOnSearchResultReceive)(Ark_NativePointer node,
                                     Ark_Function callback);
    void (*setOnScroll)(Ark_NativePointer node,
                        Ark_Function callback);
    void (*setOnSslErrorEventReceive)(Ark_NativePointer node,
                                      Ark_Function callback);
    void (*setOnSslErrorEvent)(Ark_NativePointer node,
                               Ark_Function callback);
    void (*setOnClientAuthenticationRequest)(Ark_NativePointer node,
                                             Ark_Function callback);
    void (*setOnWindowNew)(Ark_NativePointer node,
                           Ark_Function callback);
    void (*setOnWindowExit)(Ark_NativePointer node,
                            Ark_Function callback);
    void (*setMultiWindowAccess)(Ark_NativePointer node,
                                 Ark_Boolean multiWindow);
    void (*setOnInterceptKeyEvent)(Ark_NativePointer node,
                                   Ark_Function callback);
    void (*setWebStandardFont)(Ark_NativePointer node,
                               const Ark_String* family);
    void (*setWebSerifFont)(Ark_NativePointer node,
                            const Ark_String* family);
    void (*setWebSansSerifFont)(Ark_NativePointer node,
                                const Ark_String* family);
    void (*setWebFixedFont)(Ark_NativePointer node,
                            const Ark_String* family);
    void (*setWebFantasyFont)(Ark_NativePointer node,
                              const Ark_String* family);
    void (*setWebCursiveFont)(Ark_NativePointer node,
                              const Ark_String* family);
    void (*setDefaultFixedFontSize)(Ark_NativePointer node,
                                    const Ark_Number* size);
    void (*setDefaultFontSize)(Ark_NativePointer node,
                               const Ark_Number* size);
    void (*setMinFontSize)(Ark_NativePointer node,
                           const Ark_Number* size);
    void (*setMinLogicalFontSize)(Ark_NativePointer node,
                                  const Ark_Number* size);
    void (*setDefaultTextEncodingFormat)(Ark_NativePointer node,
                                         const Ark_String* textEncodingFormat);
    void (*setForceDisplayScrollBar)(Ark_NativePointer node,
                                     Ark_Boolean enabled);
    void (*setBlockNetwork)(Ark_NativePointer node,
                            Ark_Boolean block);
    void (*setHorizontalScrollBarAccess)(Ark_NativePointer node,
                                         Ark_Boolean horizontalScrollBar);
    void (*setVerticalScrollBarAccess)(Ark_NativePointer node,
                                       Ark_Boolean verticalScrollBar);
    void (*setOnTouchIconUrlReceived)(Ark_NativePointer node,
                                      Ark_Function callback);
    void (*setOnFaviconReceived)(Ark_NativePointer node,
                                 Ark_Function callback);
    void (*setOnPageVisible)(Ark_NativePointer node,
                             Ark_Function callback);
    void (*setOnDataResubmitted)(Ark_NativePointer node,
                                 Ark_Function callback);
    void (*setPinchSmooth)(Ark_NativePointer node,
                           Ark_Boolean isEnabled);
    void (*setAllowWindowOpenMethod)(Ark_NativePointer node,
                                     Ark_Boolean flag);
    void (*setOnAudioStateChanged)(Ark_NativePointer node,
                                   Ark_Function callback);
    void (*setOnFirstContentfulPaint)(Ark_NativePointer node,
                                      Ark_Function callback);
    void (*setOnFirstMeaningfulPaint)(Ark_NativePointer node,
                                      Ark_Function callback);
    void (*setOnLargestContentfulPaint)(Ark_NativePointer node,
                                        Ark_Function callback);
    void (*setOnLoadIntercept)(Ark_NativePointer node,
                               Ark_Function callback);
    void (*setOnControllerAttached)(Ark_NativePointer node,
                                    Ark_Function callback);
    void (*setOnOverScroll)(Ark_NativePointer node,
                            Ark_Function callback);
    void (*setOnSafeBrowsingCheckResult)(Ark_NativePointer node,
                                         Ark_Function callback);
    void (*setOnNavigationEntryCommitted)(Ark_NativePointer node,
                                          Ark_Function callback);
    void (*setOnIntelligentTrackingPreventionResult)(Ark_NativePointer node,
                                                     Ark_Function callback);
    void (*setJavaScriptOnDocumentStart)(Ark_NativePointer node,
                                         const Array_ScriptItem* scripts);
    void (*setJavaScriptOnDocumentEnd)(Ark_NativePointer node,
                                       const Array_ScriptItem* scripts);
    void (*setLayoutMode)(Ark_NativePointer node,
                          Ark_Int32 mode);
    void (*setNestedScroll)(Ark_NativePointer node,
                            const Type_WebAttribute_nestedScroll_Arg0* value);
    void (*setEnableNativeEmbedMode)(Ark_NativePointer node,
                                     Ark_Boolean mode);
    void (*setRegisterNativeEmbedRule)(Ark_NativePointer node,
                                       const Ark_String* tag,
                                       const Ark_String* type);
    void (*setOnNativeEmbedLifecycleChange)(Ark_NativePointer node,
                                            Ark_Function callback);
    void (*setOnNativeEmbedVisibilityChange)(Ark_NativePointer node,
                                             Ark_Function callback);
    void (*setOnNativeEmbedGestureEvent)(Ark_NativePointer node,
                                         Ark_Function callback);
    void (*setCopyOptions)(Ark_NativePointer node,
                           Ark_Int32 value);
    void (*setOnOverrideUrlLoading)(Ark_NativePointer node,
                                    Ark_Function callback);
    void (*setTextAutosizing)(Ark_NativePointer node,
                              Ark_Boolean textAutosizing);
    void (*setEnableNativeMediaPlayer)(Ark_NativePointer node,
                                       const Ark_NativeMediaPlayerConfig* config);
    void (*setEnableSmoothDragResize)(Ark_NativePointer node,
                                      Ark_Boolean mode);
    void (*setOnRenderProcessNotResponding)(Ark_NativePointer node,
                                            Ark_Function callback);
    void (*setOnRenderProcessResponding)(Ark_NativePointer node,
                                         Ark_Function callback);
    void (*setSelectionMenuOptions)(Ark_NativePointer node,
                                    const Array_ExpandedMenuItemOptions* expandedMenuOptions);
    void (*setOnViewportFitChanged)(Ark_NativePointer node,
                                    Ark_Function callback);
    void (*setOnInterceptKeyboardAttach)(Ark_NativePointer node,
                                         Ark_Function callback);
    void (*setOnAdsBlocked)(Ark_NativePointer node,
                            Ark_Function callback);
    void (*setKeyboardAvoidMode)(Ark_NativePointer node,
                                 Ark_Int32 mode);
    void (*setEditMenuOptions)(Ark_NativePointer node,
                               const Ark_Materialized* editMenu);
} GENERATED_ArkUIWebModifier;

typedef struct GENERATED_ArkUIWindowSceneModifier {
    void (*setWindowSceneOptions)(Ark_NativePointer node,
                                  const Ark_Number* persistentId);
    void (*setAttractionEffect)(Ark_NativePointer node,
                                const Ark_Position* destination,
                                const Ark_Number* fraction);
} GENERATED_ArkUIWindowSceneModifier;

typedef struct GENERATED_ArkUIXComponentModifier {
    void (*setXComponentOptions0)(Ark_NativePointer node,
                                  const Type_XComponentInterface_setXComponentOptions_Arg0* value);
    void (*setXComponentOptions1)(Ark_NativePointer node,
                                  const Type_XComponentInterface_setXComponentOptions1_Arg0* value);
    void (*setXComponentOptions2)(Ark_NativePointer node,
                                  const Ark_XComponentOptions* options);
    void (*setOnLoad)(Ark_NativePointer node,
                      Ark_Function callback);
    void (*setOnDestroy)(Ark_NativePointer node,
                         Ark_Function event);
    void (*setEnableAnalyzer)(Ark_NativePointer node,
                              Ark_Boolean enable);
} GENERATED_ArkUIXComponentModifier;

typedef struct GENERATED_ArkUISideBarContainerModifier {
    void (*setSideBarContainerOptions)(Ark_NativePointer node,
                                       const Opt_SideBarContainerType* type);
    void (*setShowSideBar)(Ark_NativePointer node,
                           Ark_Boolean value);
    void (*setControlButton)(Ark_NativePointer node,
                             const Ark_ButtonStyle* value);
    void (*setShowControlButton)(Ark_NativePointer node,
                                 Ark_Boolean value);
    void (*setOnChange)(Ark_NativePointer node,
                        Ark_Function callback);
    void (*setSideBarWidth0)(Ark_NativePointer node,
                             const Ark_Number* value);
    void (*setMinSideBarWidth0)(Ark_NativePointer node,
                                const Ark_Number* value);
    void (*setMaxSideBarWidth0)(Ark_NativePointer node,
                                const Ark_Number* value);
    void (*setSideBarWidth1)(Ark_NativePointer node,
                             const Ark_Length* value);
    void (*setMinSideBarWidth1)(Ark_NativePointer node,
                                const Ark_Length* value);
    void (*setMaxSideBarWidth1)(Ark_NativePointer node,
                                const Ark_Length* value);
    void (*setAutoHide)(Ark_NativePointer node,
                        Ark_Boolean value);
    void (*setSideBarPosition)(Ark_NativePointer node,
                               Ark_Int32 value);
    void (*setDivider)(Ark_NativePointer node,
                       const Type_SideBarContainerAttribute_divider_Arg0* value);
    void (*setMinContentWidth)(Ark_NativePointer node,
                               const Ark_Length* value);
} GENERATED_ArkUISideBarContainerModifier;

typedef struct GENERATED_ArkUIRemoteWindowModifier {
    void (*setRemoteWindowOptions)(Ark_NativePointer node,
                                   const Ark_WindowAnimationTarget* target);
} GENERATED_ArkUIRemoteWindowModifier;

typedef struct GENERATED_ArkUIWaterFlowModifier {
    void (*setWaterFlowOptions)(Ark_NativePointer node,
                                const Opt_WaterFlowOptions* options);
    void (*setColumnsTemplate)(Ark_NativePointer node,
                               const Ark_String* value);
    void (*setItemConstraintSize)(Ark_NativePointer node,
                                  const Ark_ConstraintSizeOptions* value);
    void (*setRowsTemplate)(Ark_NativePointer node,
                            const Ark_String* value);
    void (*setColumnsGap)(Ark_NativePointer node,
                          const Ark_Length* value);
    void (*setRowsGap)(Ark_NativePointer node,
                       const Ark_Length* value);
    void (*setLayoutDirection)(Ark_NativePointer node,
                               Ark_Int32 value);
    void (*setNestedScroll)(Ark_NativePointer node,
                            const Ark_NestedScrollOptions* value);
    void (*setEnableScrollInteraction)(Ark_NativePointer node,
                                       Ark_Boolean value);
    void (*setFriction)(Ark_NativePointer node,
                        const Type_WaterFlowAttribute_friction_Arg0* value);
    void (*setCachedCount)(Ark_NativePointer node,
                           const Ark_Number* value);
    void (*setOnReachStart)(Ark_NativePointer node,
                            Ark_Function event);
    void (*setOnReachEnd)(Ark_NativePointer node,
                          Ark_Function event);
    void (*setOnScrollFrameBegin)(Ark_NativePointer node,
                                  Ark_Function event);
    void (*setOnScrollIndex)(Ark_NativePointer node,
                             Ark_Function event);
} GENERATED_ArkUIWaterFlowModifier;

typedef struct GENERATED_ArkUIUIExtensionComponentModifier {
    void (*setUIExtensionComponentOptions)(Ark_NativePointer node,
                                           const Ark_CustomObject* want,
                                           const Opt_UIExtensionOptions* options);
    void (*setOnRemoteReady)(Ark_NativePointer node,
                             Ark_Function callback);
    void (*setOnReceive)(Ark_NativePointer node,
                         Ark_Function callback);
    void (*setOnResult)(Ark_NativePointer node,
                        Ark_Function callback);
    void (*setOnRelease)(Ark_NativePointer node,
                         Ark_Function callback);
    void (*setOnError)(Ark_NativePointer node,
                       const Ark_CustomObject* callback);
    void (*setOnTerminated)(Ark_NativePointer node,
                            Ark_Function callback);
} GENERATED_ArkUIUIExtensionComponentModifier;

typedef struct GENERATED_ArkUILinearIndicatorModifier {
    void (*setLinearIndicatorOptions)(Ark_NativePointer node,
                                      const Opt_Number* count,
                                      const Opt_LinearIndicatorController* controller);
    void (*setIndicatorStyle)(Ark_NativePointer node,
                              const Opt_LinearIndicatorStyle* style);
    void (*setIndicatorLoop)(Ark_NativePointer node,
                             const Opt_Boolean* loop);
    void (*setOnChange)(Ark_NativePointer node,
                        const Opt_Function* callback);
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

typedef struct ICurvePeer ICurvePeer;
typedef struct GENERATED_ArkUIICurveAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    Ark_Int32 (*interpolate)(ICurvePeer* peer, const Ark_Number* fraction);
} GENERATED_ArkUIICurveAccessor;

typedef struct PanGestureOptionsPeer PanGestureOptionsPeer;
typedef struct GENERATED_ArkUIPanGestureOptionsAccessor {
    Ark_NativePointer (*ctor)(const Opt_Literal_Opt_Number_fingers_distance_Opt_PanDirection_direction* value);
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
    void (*applyGesture)(GestureModifierPeer* peer, const Ark_UIGestureEvent* event);
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
    Ark_Boolean (*isValid)(GestureRecognizerPeer* peer);
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
    void (*goTo)(CalendarControllerPeer* peer, const Literal_Number_year_month_day* value);
} GENERATED_ArkUICalendarControllerAccessor;

typedef struct CanvasRenderingContext2DPeer CanvasRenderingContext2DPeer;
typedef struct GENERATED_ArkUICanvasRenderingContext2DAccessor {
    Ark_NativePointer (*ctor)(const Opt_RenderingContextSettings* settings);
    Ark_NativePointer (*getFinalizer)();
    void (*toDataURL)(CanvasRenderingContext2DPeer* peer, const Opt_String* type, const Opt_CustomObject* quality);
    Ark_NativePointer (*startImageAnalyzer)(CanvasRenderingContext2DPeer* peer, const Ark_ImageAnalyzerConfig* config);
    void (*stopImageAnalyzer)(CanvasRenderingContext2DPeer* peer);
    Ark_Int32 (*getHeight)(CanvasRenderingContext2DPeer* peer);
    Ark_Int32 (*getWidth)(CanvasRenderingContext2DPeer* peer);
} GENERATED_ArkUICanvasRenderingContext2DAccessor;

typedef struct CanvasRendererPeer CanvasRendererPeer;
typedef struct GENERATED_ArkUICanvasRendererAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    void (*drawImage0)(CanvasRendererPeer* peer, const Union_ImageBitmap_PixelMap* image, const Ark_Number* dx, const Ark_Number* dy);
    void (*drawImage1)(CanvasRendererPeer* peer, const Union_ImageBitmap_PixelMap* image, const Ark_Number* dx, const Ark_Number* dy, const Ark_Number* dw, const Ark_Number* dh);
    void (*drawImage2)(CanvasRendererPeer* peer, const Union_ImageBitmap_PixelMap* image, const Ark_Number* sx, const Ark_Number* sy, const Ark_Number* sw, const Ark_Number* sh, const Ark_Number* dx, const Ark_Number* dy, const Ark_Number* dw, const Ark_Number* dh);
    void (*beginPath)(CanvasRendererPeer* peer);
    void (*clip0)(CanvasRendererPeer* peer, const Opt_CanvasFillRule* fillRule);
    void (*clip1)(CanvasRendererPeer* peer, const Ark_Materialized* path, const Opt_CanvasFillRule* fillRule);
    void (*fill0)(CanvasRendererPeer* peer, const Opt_CanvasFillRule* fillRule);
    void (*fill1)(CanvasRendererPeer* peer, const Ark_Materialized* path, const Opt_CanvasFillRule* fillRule);
    void (*stroke0)(CanvasRendererPeer* peer);
    void (*stroke1)(CanvasRendererPeer* peer, const Ark_Materialized* path);
    Ark_NativePointer (*createLinearGradient)(CanvasRendererPeer* peer, const Ark_Number* x0, const Ark_Number* y0, const Ark_Number* x1, const Ark_Number* y1);
    Ark_NativePointer (*createPattern)(CanvasRendererPeer* peer, const Ark_Materialized* image, const Union_String_Ark_Undefined* repetition);
    Ark_NativePointer (*createRadialGradient)(CanvasRendererPeer* peer, const Ark_Number* x0, const Ark_Number* y0, const Ark_Number* r0, const Ark_Number* x1, const Ark_Number* y1, const Ark_Number* r1);
    Ark_NativePointer (*createConicGradient)(CanvasRendererPeer* peer, const Ark_Number* startAngle, const Ark_Number* x, const Ark_Number* y);
    Ark_NativePointer (*createImageData0)(CanvasRendererPeer* peer, const Ark_Number* sw, const Ark_Number* sh);
    Ark_NativePointer (*createImageData1)(CanvasRendererPeer* peer, const Ark_ImageData* imagedata);
    Ark_NativePointer (*getImageData)(CanvasRendererPeer* peer, const Ark_Number* sx, const Ark_Number* sy, const Ark_Number* sw, const Ark_Number* sh);
    Ark_NativePointer (*getPixelMap)(CanvasRendererPeer* peer, const Ark_Number* sx, const Ark_Number* sy, const Ark_Number* sw, const Ark_Number* sh);
    void (*putImageData0)(CanvasRendererPeer* peer, const Ark_ImageData* imagedata, const Union_Number_String* dx, const Union_Number_String* dy);
    void (*putImageData1)(CanvasRendererPeer* peer, const Ark_ImageData* imagedata, const Union_Number_String* dx, const Union_Number_String* dy, const Union_Number_String* dirtyX, const Union_Number_String* dirtyY, const Union_Number_String* dirtyWidth, const Union_Number_String* dirtyHeight);
    void (*getLineDash)(CanvasRendererPeer* peer);
    void (*setLineDash)(CanvasRendererPeer* peer, const Array_Number* segments);
    void (*clearRect)(CanvasRendererPeer* peer, const Ark_Number* x, const Ark_Number* y, const Ark_Number* w, const Ark_Number* h);
    void (*fillRect)(CanvasRendererPeer* peer, const Ark_Number* x, const Ark_Number* y, const Ark_Number* w, const Ark_Number* h);
    void (*strokeRect)(CanvasRendererPeer* peer, const Ark_Number* x, const Ark_Number* y, const Ark_Number* w, const Ark_Number* h);
    void (*restore)(CanvasRendererPeer* peer);
    void (*save)(CanvasRendererPeer* peer);
    void (*fillText)(CanvasRendererPeer* peer, const Ark_String* text, const Ark_Number* x, const Ark_Number* y, const Opt_Number* maxWidth);
    Ark_NativePointer (*measureText)(CanvasRendererPeer* peer, const Ark_String* text);
    void (*strokeText)(CanvasRendererPeer* peer, const Ark_String* text, const Ark_Number* x, const Ark_Number* y, const Opt_Number* maxWidth);
    Ark_NativePointer (*getTransform)(CanvasRendererPeer* peer);
    void (*resetTransform)(CanvasRendererPeer* peer);
    void (*rotate)(CanvasRendererPeer* peer, const Ark_Number* angle);
    void (*scale)(CanvasRendererPeer* peer, const Ark_Number* x, const Ark_Number* y);
    void (*setTransform0)(CanvasRendererPeer* peer, const Ark_Number* a, const Ark_Number* b, const Ark_Number* c, const Ark_Number* d, const Ark_Number* e, const Ark_Number* f);
    void (*setTransform1)(CanvasRendererPeer* peer, const Opt_Matrix2D* transform);
    void (*transform)(CanvasRendererPeer* peer, const Ark_Number* a, const Ark_Number* b, const Ark_Number* c, const Ark_Number* d, const Ark_Number* e, const Ark_Number* f);
    void (*translate)(CanvasRendererPeer* peer, const Ark_Number* x, const Ark_Number* y);
    void (*setPixelMap)(CanvasRendererPeer* peer, const Opt_PixelMap* value);
    void (*transferFromImageBitmap)(CanvasRendererPeer* peer, const Ark_Materialized* bitmap);
    void (*saveLayer)(CanvasRendererPeer* peer);
    void (*restoreLayer)(CanvasRendererPeer* peer);
    void (*reset)(CanvasRendererPeer* peer);
    Ark_Int32 (*getGlobalAlpha)(CanvasRendererPeer* peer);
    void (*setGlobalAlpha)(CanvasRendererPeer* peer, const Ark_Number* globalAlpha);
    void (*getGlobalCompositeOperation)(CanvasRendererPeer* peer);
    void (*setGlobalCompositeOperation)(CanvasRendererPeer* peer, const Ark_String* globalCompositeOperation);
    void (*setFillStyle)(CanvasRendererPeer* peer, const Union_String_Number_CanvasGradient_CanvasPattern* fillStyle);
    void (*setStrokeStyle)(CanvasRendererPeer* peer, const Union_String_Number_CanvasGradient_CanvasPattern* strokeStyle);
    void (*getFilter)(CanvasRendererPeer* peer);
    void (*setFilter)(CanvasRendererPeer* peer, const Ark_String* filter);
    Ark_Boolean (*getImageSmoothingEnabled)(CanvasRendererPeer* peer);
    void (*setImageSmoothingEnabled)(CanvasRendererPeer* peer, Ark_Boolean imageSmoothingEnabled);
    void (*setImageSmoothingQuality)(CanvasRendererPeer* peer, const ImageSmoothingQuality* imageSmoothingQuality);
    void (*setLineCap)(CanvasRendererPeer* peer, const CanvasLineCap* lineCap);
    Ark_Int32 (*getLineDashOffset)(CanvasRendererPeer* peer);
    void (*setLineDashOffset)(CanvasRendererPeer* peer, const Ark_Number* lineDashOffset);
    void (*setLineJoin)(CanvasRendererPeer* peer, const CanvasLineJoin* lineJoin);
    Ark_Int32 (*getLineWidth)(CanvasRendererPeer* peer);
    void (*setLineWidth)(CanvasRendererPeer* peer, const Ark_Number* lineWidth);
    Ark_Int32 (*getMiterLimit)(CanvasRendererPeer* peer);
    void (*setMiterLimit)(CanvasRendererPeer* peer, const Ark_Number* miterLimit);
    Ark_Int32 (*getShadowBlur)(CanvasRendererPeer* peer);
    void (*setShadowBlur)(CanvasRendererPeer* peer, const Ark_Number* shadowBlur);
    void (*getShadowColor)(CanvasRendererPeer* peer);
    void (*setShadowColor)(CanvasRendererPeer* peer, const Ark_String* shadowColor);
    Ark_Int32 (*getShadowOffsetX)(CanvasRendererPeer* peer);
    void (*setShadowOffsetX)(CanvasRendererPeer* peer, const Ark_Number* shadowOffsetX);
    Ark_Int32 (*getShadowOffsetY)(CanvasRendererPeer* peer);
    void (*setShadowOffsetY)(CanvasRendererPeer* peer, const Ark_Number* shadowOffsetY);
    void (*setDirection)(CanvasRendererPeer* peer, const CanvasDirection* direction);
    void (*getFont)(CanvasRendererPeer* peer);
    void (*setFont)(CanvasRendererPeer* peer, const Ark_String* font);
    void (*setTextAlign)(CanvasRendererPeer* peer, const CanvasTextAlign* textAlign);
    void (*setTextBaseline)(CanvasRendererPeer* peer, const CanvasTextBaseline* textBaseline);
} GENERATED_ArkUICanvasRendererAccessor;

typedef struct CanvasPathPeer CanvasPathPeer;
typedef struct GENERATED_ArkUICanvasPathAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    void (*arc)(CanvasPathPeer* peer, const Ark_Number* x, const Ark_Number* y, const Ark_Number* radius, const Ark_Number* startAngle, const Ark_Number* endAngle, const Opt_Boolean* counterclockwise);
    void (*arcTo)(CanvasPathPeer* peer, const Ark_Number* x1, const Ark_Number* y1, const Ark_Number* x2, const Ark_Number* y2, const Ark_Number* radius);
    void (*bezierCurveTo)(CanvasPathPeer* peer, const Ark_Number* cp1x, const Ark_Number* cp1y, const Ark_Number* cp2x, const Ark_Number* cp2y, const Ark_Number* x, const Ark_Number* y);
    void (*closePath)(CanvasPathPeer* peer);
    void (*ellipse)(CanvasPathPeer* peer, const Ark_Number* x, const Ark_Number* y, const Ark_Number* radiusX, const Ark_Number* radiusY, const Ark_Number* rotation, const Ark_Number* startAngle, const Ark_Number* endAngle, const Opt_Boolean* counterclockwise);
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
    Ark_Int32 (*getHeight)(ImageBitmapPeer* peer);
    Ark_Int32 (*getWidth)(ImageBitmapPeer* peer);
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
    Ark_NativePointer (*rotate0)(Matrix2DPeer* peer, const Opt_Number* rx, const Opt_Number* ry);
    Ark_NativePointer (*rotate1)(Matrix2DPeer* peer, const Ark_Number* degree, const Opt_Number* rx, const Opt_Number* ry);
    Ark_NativePointer (*translate)(Matrix2DPeer* peer, const Opt_Number* tx, const Opt_Number* ty);
    Ark_NativePointer (*scale)(Matrix2DPeer* peer, const Opt_Number* sx, const Opt_Number* sy);
    Ark_Int32 (*getScaleX)(Matrix2DPeer* peer);
    void (*setScaleX)(Matrix2DPeer* peer, const Ark_Number* scaleX);
    Ark_Int32 (*getRotateY)(Matrix2DPeer* peer);
    void (*setRotateY)(Matrix2DPeer* peer, const Ark_Number* rotateY);
    Ark_Int32 (*getRotateX)(Matrix2DPeer* peer);
    void (*setRotateX)(Matrix2DPeer* peer, const Ark_Number* rotateX);
    Ark_Int32 (*getScaleY)(Matrix2DPeer* peer);
    void (*setScaleY)(Matrix2DPeer* peer, const Ark_Number* scaleY);
    Ark_Int32 (*getTranslateX)(Matrix2DPeer* peer);
    void (*setTranslateX)(Matrix2DPeer* peer, const Ark_Number* translateX);
    Ark_Int32 (*getTranslateY)(Matrix2DPeer* peer);
    void (*setTranslateY)(Matrix2DPeer* peer, const Ark_Number* translateY);
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
    void (*scrollTo)(ScrollerPeer* peer, const Ark_ScrollOptions* options);
    void (*scrollEdge)(ScrollerPeer* peer, Ark_Int32 value, const Opt_ScrollEdgeOptions* options);
    void (*fling)(ScrollerPeer* peer, const Ark_Number* velocity);
    void (*scrollPage0)(ScrollerPeer* peer, const Ark_ScrollPageOptions* value);
    void (*scrollPage1)(ScrollerPeer* peer, const Literal_Boolean_next_Opt_Axis_direction* value);
    Ark_NativePointer (*currentOffset)(ScrollerPeer* peer);
    void (*scrollToIndex)(ScrollerPeer* peer, const Ark_Number* value, const Opt_Boolean* smooth, const Opt_ScrollAlign* align, const Opt_ScrollToIndexOptions* options);
    void (*scrollBy)(ScrollerPeer* peer, const Ark_Length* dx, const Ark_Length* dy);
    Ark_Boolean (*isAtEnd)(ScrollerPeer* peer);
    Ark_NativePointer (*getItemRect)(ScrollerPeer* peer, const Ark_Number* index);
    Ark_Int32 (*getItemIndex)(ScrollerPeer* peer, const Ark_Number* x, const Ark_Number* y);
} GENERATED_ArkUIScrollerAccessor;

typedef struct ChildrenMainSizePeer ChildrenMainSizePeer;
typedef struct GENERATED_ArkUIChildrenMainSizeAccessor {
    Ark_NativePointer (*ctor)(const Ark_Number* childDefaultSize);
    Ark_NativePointer (*getFinalizer)();
    void (*splice)(ChildrenMainSizePeer* peer, const Ark_Number* start, const Opt_Number* deleteCount, const Opt_Array_Number* childrenSize);
    void (*update)(ChildrenMainSizePeer* peer, const Ark_Number* index, const Ark_Number* childSize);
} GENERATED_ArkUIChildrenMainSizeAccessor;

typedef struct NavigationTransitionProxyPeer NavigationTransitionProxyPeer;
typedef struct GENERATED_ArkUINavigationTransitionProxyAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    void (*finishTransition)(NavigationTransitionProxyPeer* peer);
    void (*cancelTransition)(NavigationTransitionProxyPeer* peer);
    void (*updateTransition)(NavigationTransitionProxyPeer* peer, const Ark_Number* progress);
    void (*setFrom)(NavigationTransitionProxyPeer* peer, const Ark_NavContentInfo* from);
    void (*setTo)(NavigationTransitionProxyPeer* peer, const Ark_NavContentInfo* to);
    Ark_Boolean (*getIsInteractive)(NavigationTransitionProxyPeer* peer);
    void (*setIsInteractive)(NavigationTransitionProxyPeer* peer, Ark_Boolean isInteractive);
} GENERATED_ArkUINavigationTransitionProxyAccessor;

typedef struct NavPathStackPeer NavPathStackPeer;
typedef struct GENERATED_ArkUINavPathStackAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    void (*pushPath0)(NavPathStackPeer* peer, const Ark_NavPathInfo* info, const Opt_Boolean* animated);
    void (*pushPath1)(NavPathStackPeer* peer, const Ark_NavPathInfo* info, const Opt_NavigationOptions* options);
    Ark_NativePointer (*pushDestination0)(NavPathStackPeer* peer, const Ark_NavPathInfo* info, const Opt_Boolean* animated);
    Ark_NativePointer (*pushDestination1)(NavPathStackPeer* peer, const Ark_NavPathInfo* info, const Opt_NavigationOptions* options);
    void (*pushPathByName0)(NavPathStackPeer* peer, const Ark_String* name, const Ark_CustomObject* param, const Opt_Boolean* animated);
    void (*pushPathByName1)(NavPathStackPeer* peer, const Ark_String* name, const Ark_Object* param, Ark_Function onPop, const Opt_Boolean* animated);
    Ark_NativePointer (*pushDestinationByName0)(NavPathStackPeer* peer, const Ark_String* name, const Ark_Object* param, const Opt_Boolean* animated);
    Ark_NativePointer (*pushDestinationByName1)(NavPathStackPeer* peer, const Ark_String* name, const Ark_Object* param, Ark_Function onPop, const Opt_Boolean* animated);
    void (*replacePath0)(NavPathStackPeer* peer, const Ark_NavPathInfo* info, const Opt_Boolean* animated);
    void (*replacePath1)(NavPathStackPeer* peer, const Ark_NavPathInfo* info, const Opt_NavigationOptions* options);
    void (*replacePathByName)(NavPathStackPeer* peer, const Ark_String* name, const Ark_Object* param, const Opt_Boolean* animated);
    Ark_Int32 (*removeByIndexes)(NavPathStackPeer* peer, const Array_Number* indexes);
    Ark_Int32 (*removeByName)(NavPathStackPeer* peer, const Ark_String* name);
    Ark_Boolean (*removeByNavDestinationId)(NavPathStackPeer* peer, const Ark_String* navDestinationId);
    void (*pop0)(NavPathStackPeer* peer, const Opt_Boolean* animated);
    void (*pop1)(NavPathStackPeer* peer, const Ark_Object* result, const Opt_Boolean* animated);
    Ark_Int32 (*popToName0)(NavPathStackPeer* peer, const Ark_String* name, const Opt_Boolean* animated);
    Ark_Int32 (*popToName1)(NavPathStackPeer* peer, const Ark_String* name, const Ark_Object* result, const Opt_Boolean* animated);
    void (*popToIndex0)(NavPathStackPeer* peer, const Ark_Number* index, const Opt_Boolean* animated);
    void (*popToIndex1)(NavPathStackPeer* peer, const Ark_Number* index, const Ark_Object* result, const Opt_Boolean* animated);
    Ark_Int32 (*moveToTop)(NavPathStackPeer* peer, const Ark_String* name, const Opt_Boolean* animated);
    void (*moveIndexToTop)(NavPathStackPeer* peer, const Ark_Number* index, const Opt_Boolean* animated);
    void (*clear)(NavPathStackPeer* peer, const Opt_Boolean* animated);
    Ark_NativePointer (*getAllPathName)(NavPathStackPeer* peer);
    void (*getParamByIndex)(NavPathStackPeer* peer, const Ark_Number* index);
    Ark_NativePointer (*getParamByName)(NavPathStackPeer* peer, const Ark_String* name);
    Ark_NativePointer (*getIndexByName)(NavPathStackPeer* peer, const Ark_String* name);
    Ark_NativePointer (*getParent)(NavPathStackPeer* peer);
    Ark_Int32 (*size)(NavPathStackPeer* peer);
    void (*disableAnimation)(NavPathStackPeer* peer, Ark_Boolean value);
    void (*setInterception)(NavPathStackPeer* peer, const Ark_NavigationInterception* interception);
} GENERATED_ArkUINavPathStackAccessor;

typedef struct NavDestinationContextPeer NavDestinationContextPeer;
typedef struct GENERATED_ArkUINavDestinationContextAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    void (*getConfigInRouteMap)(NavDestinationContextPeer* peer);
    void (*setPathInfo)(NavDestinationContextPeer* peer, const Ark_NavPathInfo* pathInfo);
    void (*setPathStack)(NavDestinationContextPeer* peer, const Ark_Materialized* pathStack);
    void (*getNavDestinationId)(NavDestinationContextPeer* peer);
    void (*setNavDestinationId)(NavDestinationContextPeer* peer, const Ark_String* navDestinationId);
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
    Ark_Boolean (*onMenuItemClick)(EditMenuOptionsPeer* peer, const Ark_TextMenuItem* menuItem, const Ark_TextRange* range);
} GENERATED_ArkUIEditMenuOptionsAccessor;

typedef struct RichEditorControllerPeer RichEditorControllerPeer;
typedef struct GENERATED_ArkUIRichEditorControllerAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    Ark_Int32 (*addTextSpan)(RichEditorControllerPeer* peer, const Ark_String* value, const Opt_RichEditorTextSpanOptions* options);
    Ark_Int32 (*addImageSpan)(RichEditorControllerPeer* peer, const Union_PixelMap_ResourceStr* value, const Opt_RichEditorImageSpanOptions* options);
    Ark_Int32 (*addBuilderSpan)(RichEditorControllerPeer* peer, const CustomBuilder* value, const Opt_RichEditorBuilderSpanOptions* options);
    Ark_Int32 (*addSymbolSpan)(RichEditorControllerPeer* peer, const Ark_Resource* value, const Opt_RichEditorSymbolSpanOptions* options);
    void (*updateSpanStyle)(RichEditorControllerPeer* peer, const Union_RichEditorUpdateTextSpanStyleOptions_RichEditorUpdateImageSpanStyleOptions_RichEditorUpdateSymbolSpanStyleOptions* value);
    void (*updateParagraphStyle)(RichEditorControllerPeer* peer, const Ark_RichEditorParagraphStyleOptions* value);
    void (*deleteSpans)(RichEditorControllerPeer* peer, const Opt_RichEditorRange* value);
    Ark_NativePointer (*getSpans)(RichEditorControllerPeer* peer, const Opt_RichEditorRange* value);
    Ark_NativePointer (*getParagraphs)(RichEditorControllerPeer* peer, const Opt_RichEditorRange* value);
    Ark_NativePointer (*getSelection)(RichEditorControllerPeer* peer);
    Ark_NativePointer (*fromStyledString)(RichEditorControllerPeer* peer, const Ark_Materialized* value);
    Ark_NativePointer (*toStyledString)(RichEditorControllerPeer* peer, const Ark_RichEditorRange* value);
} GENERATED_ArkUIRichEditorControllerAccessor;

typedef struct RichEditorBaseControllerPeer RichEditorBaseControllerPeer;
typedef struct GENERATED_ArkUIRichEditorBaseControllerAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    Ark_Int32 (*getCaretOffset)(RichEditorBaseControllerPeer* peer);
    Ark_Boolean (*setCaretOffset)(RichEditorBaseControllerPeer* peer, const Ark_Number* offset);
    void (*closeSelectionMenu)(RichEditorBaseControllerPeer* peer);
    Ark_NativePointer (*getTypingStyle)(RichEditorBaseControllerPeer* peer);
    void (*setTypingStyle)(RichEditorBaseControllerPeer* peer, const Ark_RichEditorTextStyle* value);
    void (*setSelection)(RichEditorBaseControllerPeer* peer, const Ark_Number* selectionStart, const Ark_Number* selectionEnd, const Opt_SelectionOptions* options);
    Ark_Boolean (*isEditing)(RichEditorBaseControllerPeer* peer);
    void (*stopEditing)(RichEditorBaseControllerPeer* peer);
    Ark_NativePointer (*getLayoutManager)(RichEditorBaseControllerPeer* peer);
    Ark_NativePointer (*getPreviewText)(RichEditorBaseControllerPeer* peer);
} GENERATED_ArkUIRichEditorBaseControllerAccessor;

typedef struct TextEditControllerExPeer TextEditControllerExPeer;
typedef struct GENERATED_ArkUITextEditControllerExAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    Ark_Boolean (*isEditing)(TextEditControllerExPeer* peer);
    void (*stopEditing)(TextEditControllerExPeer* peer);
    Ark_Boolean (*setCaretOffset)(TextEditControllerExPeer* peer, const Ark_Number* offset);
    Ark_Int32 (*getCaretOffset)(TextEditControllerExPeer* peer);
    Ark_NativePointer (*getPreviewText)(TextEditControllerExPeer* peer);
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
    Ark_NativePointer (*getRectsForRange)(LayoutManagerPeer* peer, const Ark_TextRange* range, const Ark_CustomObject* widthStyle, const Ark_CustomObject* heightStyle);
} GENERATED_ArkUILayoutManagerAccessor;

typedef struct StyledStringPeer StyledStringPeer;
typedef struct GENERATED_ArkUIStyledStringAccessor {
    Ark_NativePointer (*ctor)(const Union_String_ImageAttachment_CustomSpan* value, const Opt_Array_StyleOptions* styles);
    Ark_NativePointer (*getFinalizer)();
    void (*getString)(StyledStringPeer* peer);
    Ark_NativePointer (*getStyles)(StyledStringPeer* peer, const Ark_Number* start, const Ark_Number* length, const Opt_StyledStringKey* styledKey);
    Ark_Boolean (*equals)(StyledStringPeer* peer, const Ark_Materialized* other);
    Ark_NativePointer (*subStyledString)(StyledStringPeer* peer, const Ark_Number* start, const Opt_Number* length);
    Ark_NativePointer (*fromHtml)(const Ark_String* html);
    Ark_NativePointer (*marshalling)(const Ark_Materialized* styledString);
    Ark_NativePointer (*unmarshalling)(const Ark_ArrayBuffer* buffer);
    Ark_Int32 (*getLength)(StyledStringPeer* peer);
} GENERATED_ArkUIStyledStringAccessor;

typedef struct CustomSpanPeer CustomSpanPeer;
typedef struct GENERATED_ArkUICustomSpanAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    Ark_NativePointer (*onMeasure)(CustomSpanPeer* peer, const Ark_CustomSpanMeasureInfo* measureInfo);
    void (*onDraw)(CustomSpanPeer* peer, const Ark_CustomObject* context, const Ark_CustomSpanDrawInfo* drawInfo);
} GENERATED_ArkUICustomSpanAccessor;

typedef struct RichEditorStyledStringControllerPeer RichEditorStyledStringControllerPeer;
typedef struct GENERATED_ArkUIRichEditorStyledStringControllerAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    void (*setStyledString)(RichEditorStyledStringControllerPeer* peer, const Ark_Materialized* styledString);
    Ark_NativePointer (*getStyledString)(RichEditorStyledStringControllerPeer* peer);
    Ark_NativePointer (*getSelection)(RichEditorStyledStringControllerPeer* peer);
    void (*onContentChanged)(RichEditorStyledStringControllerPeer* peer, const Ark_StyledStringChangedListener* listener);
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
    void (*replaceStyle)(MutableStyledStringPeer* peer, const Ark_SpanStyle* spanStyle);
    void (*setStyle)(MutableStyledStringPeer* peer, const Ark_SpanStyle* spanStyle);
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
    Ark_Int32 (*getSelectedIndex)(SwiperContentTransitionProxyPeer* peer);
    void (*setSelectedIndex)(SwiperContentTransitionProxyPeer* peer, const Ark_Number* selectedIndex);
    Ark_Int32 (*getIndex)(SwiperContentTransitionProxyPeer* peer);
    void (*setIndex)(SwiperContentTransitionProxyPeer* peer, const Ark_Number* index);
    Ark_Int32 (*getPosition)(SwiperContentTransitionProxyPeer* peer);
    void (*setPosition)(SwiperContentTransitionProxyPeer* peer, const Ark_Number* position);
    Ark_Int32 (*getMainAxisLength)(SwiperContentTransitionProxyPeer* peer);
    void (*setMainAxisLength)(SwiperContentTransitionProxyPeer* peer, const Ark_Number* mainAxisLength);
} GENERATED_ArkUISwiperContentTransitionProxyAccessor;

typedef struct SwiperControllerPeer SwiperControllerPeer;
typedef struct GENERATED_ArkUISwiperControllerAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    void (*showNext)(SwiperControllerPeer* peer);
    void (*showPrevious)(SwiperControllerPeer* peer);
    void (*changeIndex)(SwiperControllerPeer* peer, const Ark_Number* index, const Opt_Boolean* useAnimation);
    void (*finishAnimation)(SwiperControllerPeer* peer, const Opt_Function* callback);
} GENERATED_ArkUISwiperControllerAccessor;

typedef struct TabContentTransitionProxyPeer TabContentTransitionProxyPeer;
typedef struct GENERATED_ArkUITabContentTransitionProxyAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    void (*finishTransition)(TabContentTransitionProxyPeer* peer);
    Ark_Int32 (*getFrom)(TabContentTransitionProxyPeer* peer);
    void (*setFrom)(TabContentTransitionProxyPeer* peer, const Ark_Number* from);
    Ark_Int32 (*getTo)(TabContentTransitionProxyPeer* peer);
    void (*setTo)(TabContentTransitionProxyPeer* peer, const Ark_Number* to);
} GENERATED_ArkUITabContentTransitionProxyAccessor;

typedef struct TabsControllerPeer TabsControllerPeer;
typedef struct GENERATED_ArkUITabsControllerAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    void (*changeIndex)(TabsControllerPeer* peer, const Ark_Number* value);
    Ark_NativePointer (*preloadItems)(TabsControllerPeer* peer, const Opt_Array_Number* indices);
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
    void (*setCurrentTime0)(VideoControllerPeer* peer, const Ark_Number* value);
    void (*requestFullscreen)(VideoControllerPeer* peer, Ark_Boolean value);
    void (*exitFullscreen)(VideoControllerPeer* peer);
    void (*setCurrentTime1)(VideoControllerPeer* peer, const Ark_Number* value, Ark_Int32 seekMode);
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
    void (*runJavaScript)(WebControllerPeer* peer, const Literal_String_script_Opt_Function_callback* options);
    void (*loadData)(WebControllerPeer* peer, const Literal_String_data_mimeType_encoding_Opt_String_baseUrl_historyUrl* options);
    void (*loadUrl)(WebControllerPeer* peer, const Literal_Union_String_Resource_url_Opt_Array_Header_headers* options);
    void (*refresh)(WebControllerPeer* peer);
    void (*stop)(WebControllerPeer* peer);
    void (*registerJavaScriptProxy)(WebControllerPeer* peer, const Literal_CustomObject_object_String_name_Array_String_methodList* options);
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
    void (*setResponseData)(WebResourceResponsePeer* peer, const Union_String_Number_Resource_ArrayBuffer* data);
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
    void (*handleFileList)(FileSelectorResultPeer* peer, const Array_String* fileList);
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
    void (*grant)(PermissionRequestPeer* peer, const Array_String* resources);
} GENERATED_ArkUIPermissionRequestAccessor;

typedef struct ScreenCaptureHandlerPeer ScreenCaptureHandlerPeer;
typedef struct GENERATED_ArkUIScreenCaptureHandlerAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    void (*getOrigin)(ScreenCaptureHandlerPeer* peer);
    void (*grant)(ScreenCaptureHandlerPeer* peer, const Ark_ScreenCaptureConfig* config);
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
    void (*confirm0)(ClientAuthenticationHandlerPeer* peer, const Ark_String* priKeyFile, const Ark_String* certChainFile);
    void (*confirm1)(ClientAuthenticationHandlerPeer* peer, const Ark_String* authUri);
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
    void (*setXComponentSurfaceSize)(XComponentControllerPeer* peer, const Literal_Number_surfaceWidth_surfaceHeight* value);
    void (*setXComponentSurfaceRect)(XComponentControllerPeer* peer, const Ark_SurfaceRect* rect);
    Ark_NativePointer (*getXComponentSurfaceRect)(XComponentControllerPeer* peer);
    void (*setXComponentSurfaceRotation)(XComponentControllerPeer* peer, const Ark_SurfaceRotationOptions* rotationOptions);
    Ark_NativePointer (*getXComponentSurfaceRotation)(XComponentControllerPeer* peer);
    void (*onSurfaceCreated)(XComponentControllerPeer* peer, const Ark_String* surfaceId);
    void (*onSurfaceChanged)(XComponentControllerPeer* peer, const Ark_String* surfaceId, const Ark_SurfaceRect* rect);
    void (*onSurfaceDestroyed)(XComponentControllerPeer* peer, const Ark_String* surfaceId);
    Ark_NativePointer (*startImageAnalyzer)(XComponentControllerPeer* peer, const Ark_ImageAnalyzerConfig* config);
    void (*stopImageAnalyzer)(XComponentControllerPeer* peer);
} GENERATED_ArkUIXComponentControllerAccessor;

typedef struct WaterFlowSectionsPeer WaterFlowSectionsPeer;
typedef struct GENERATED_ArkUIWaterFlowSectionsAccessor {
    Ark_NativePointer (*ctor)();
    Ark_NativePointer (*getFinalizer)();
    Ark_Boolean (*splice)(WaterFlowSectionsPeer* peer, const Ark_Number* start, const Opt_Number* deleteCount, const Opt_Array_SectionOptions* sections);
    Ark_Boolean (*push)(WaterFlowSectionsPeer* peer, const Ark_SectionOptions* section);
    Ark_Boolean (*update)(WaterFlowSectionsPeer* peer, const Ark_Number* sectionIndex, const Ark_SectionOptions* section);
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
    void (*onSelected)(Ark_Int32 nodeId,
                       const Ark_Number index);
    void (*onSelect)(Ark_Int32 nodeId,
                     const Ark_Number index);
    void (*onRequestPopupData)(Ark_Int32 nodeId,
                               const Ark_Number index);
    void (*onPopupSelect)(Ark_Int32 nodeId,
                          const Ark_Number index);
} GENERATED_ArkUIAlphabetIndexerEventsReceiver;

typedef struct GENERATED_ArkUIAnimatorEventsReceiver {
    void (*onStart)(Ark_Int32 nodeId);
    void (*onPause)(Ark_Int32 nodeId);
    void (*onRepeat)(Ark_Int32 nodeId);
    void (*onCancel)(Ark_Int32 nodeId);
    void (*onFinish)(Ark_Int32 nodeId);
    void (*onFrame)(Ark_Int32 nodeId,
                    const Ark_Number value);
} GENERATED_ArkUIAnimatorEventsReceiver;

typedef struct GENERATED_ArkUICalendarEventsReceiver {
    void (*onSelectChange)(Ark_Int32 nodeId,
                           const Ark_CalendarSelectedDate event);
    void (*onRequestData)(Ark_Int32 nodeId,
                          const Ark_CalendarRequestedData event);
} GENERATED_ArkUICalendarEventsReceiver;

typedef struct GENERATED_ArkUICalendarPickerEventsReceiver {
    void (*onChange)(Ark_Int32 nodeId,
                     const Ark_CustomObject data);
} GENERATED_ArkUICalendarPickerEventsReceiver;

typedef struct GENERATED_ArkUICanvasEventsReceiver {
    void (*onReady)(Ark_Int32 nodeId);
} GENERATED_ArkUICanvasEventsReceiver;

typedef struct GENERATED_ArkUICheckboxEventsReceiver {
    void (*onChange)(Ark_Int32 nodeId,
                     const Ark_Boolean value);
} GENERATED_ArkUICheckboxEventsReceiver;

typedef struct GENERATED_ArkUICheckboxGroupEventsReceiver {
    void (*onChange)(Ark_Int32 nodeId,
                     const Ark_CheckboxGroupResult value);
} GENERATED_ArkUICheckboxGroupEventsReceiver;

typedef struct GENERATED_ArkUICommonMethodEventsReceiver {
    void (*onChildTouchTest)(Ark_Int32 nodeId,
                             const Array_TouchTestInfo value);
    void (*onClick0)(Ark_Int32 nodeId,
                     const Ark_ClickEvent event);
    void (*onClick1)(Ark_Int32 nodeId,
                     const Ark_ClickEvent data);
    void (*onHover)(Ark_Int32 nodeId,
                    const Ark_Boolean isHover,
                    const Ark_HoverEvent event);
    void (*onAccessibilityHover)(Ark_Int32 nodeId,
                                 const Ark_Boolean isHover,
                                 const Ark_AccessibilityHoverEvent event);
    void (*onMouse)(Ark_Int32 nodeId,
                    const Ark_MouseEvent event);
    void (*onTouch)(Ark_Int32 nodeId,
                    const Ark_TouchEvent event);
    void (*onKeyEvent)(Ark_Int32 nodeId,
                       const Ark_KeyEvent event);
    void (*onKeyPreIme)(Ark_Int32 nodeId,
                        const Ark_KeyEvent data);
    void (*onFocus)(Ark_Int32 nodeId);
    void (*onBlur)(Ark_Int32 nodeId);
    void (*onAppear)(Ark_Int32 nodeId);
    void (*onDisAppear)(Ark_Int32 nodeId);
    void (*onAttach)(Ark_Int32 nodeId);
    void (*onDetach)(Ark_Int32 nodeId);
    void (*onAreaChange)(Ark_Int32 nodeId,
                         const Ark_Area oldValue,
                         const Ark_Area newValue);
    void (*onDragStart)(Ark_Int32 nodeId,
                        const Ark_DragEvent event,
                        const Opt_String extraParams);
    void (*onDragEnter)(Ark_Int32 nodeId,
                        const Ark_DragEvent event,
                        const Opt_String extraParams);
    void (*onDragMove)(Ark_Int32 nodeId,
                       const Ark_DragEvent event,
                       const Opt_String extraParams);
    void (*onDragLeave)(Ark_Int32 nodeId,
                        const Ark_DragEvent event,
                        const Opt_String extraParams);
    void (*onDrop)(Ark_Int32 nodeId,
                   const Ark_DragEvent event,
                   const Opt_String extraParams);
    void (*onDragEnd)(Ark_Int32 nodeId,
                      const Ark_DragEvent event,
                      const Opt_String extraParams);
    void (*onPreDrag)(Ark_Int32 nodeId,
                      const Ark_Int32 data);
    void (*onVisibleAreaChange)(Ark_Int32 nodeId,
                                const Ark_Boolean isVisible,
                                const Ark_Number currentRatio);
    void (*keyboardShortcut)(Ark_Int32 nodeId);
    void (*onGestureJudgeBegin)(Ark_Int32 nodeId,
                                const Ark_GestureInfo gestureInfo,
                                const Ark_BaseGestureEvent event);
    void (*onGestureRecognizerJudgeBegin)(Ark_Int32 nodeId,
                                          const Ark_BaseGestureEvent event,
                                          const Ark_Materialized current,
                                          const Array_GestureRecognizer recognizers);
    void (*shouldBuiltInRecognizerParallelWith)(Ark_Int32 nodeId,
                                                const Ark_Materialized current,
                                                const Array_GestureRecognizer others);
    void (*onTouchIntercept)(Ark_Int32 nodeId,
                             const Ark_TouchEvent data);
    void (*onSizeChange)(Ark_Int32 nodeId,
                         const Ark_SizeOptions oldValue,
                         const Ark_SizeOptions newValue);
} GENERATED_ArkUICommonMethodEventsReceiver;

typedef struct GENERATED_ArkUIScrollableCommonMethodEventsReceiver {
    void (*onScroll)(Ark_Int32 nodeId,
                     const Ark_Number scrollOffset,
                     const Ark_Int32 scrollState);
    void (*onDidScroll)(Ark_Int32 nodeId,
                        const Ark_Number scrollOffset,
                        const Ark_Int32 scrollState);
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
    void (*onChange)(Ark_Int32 nodeId,
                     const Ark_DatePickerResult value);
    void (*onDateChange)(Ark_Int32 nodeId,
                         const Ark_CustomObject data);
} GENERATED_ArkUIDatePickerEventsReceiver;

typedef struct GENERATED_ArkUIFolderStackEventsReceiver {
    void (*onFolderStateChange)(Ark_Int32 nodeId,
                                const Ark_OnFoldStatusChangeInfo event);
    void (*onHoverStatusChange)(Ark_Int32 nodeId,
                                const Ark_HoverEventParam param);
} GENERATED_ArkUIFolderStackEventsReceiver;

typedef struct GENERATED_ArkUIFormComponentEventsReceiver {
    void (*onAcquired)(Ark_Int32 nodeId,
                       const Ark_FormCallbackInfo data);
    void (*onError)(Ark_Int32 nodeId,
                    const Literal_Number_errcode_String_msg info);
    void (*onRouter)(Ark_Int32 nodeId,
                     const Ark_CustomObject info);
    void (*onUninstall)(Ark_Int32 nodeId,
                        const Ark_FormCallbackInfo data);
    void (*onLoad)(Ark_Int32 nodeId);
} GENERATED_ArkUIFormComponentEventsReceiver;

typedef struct GENERATED_ArkUIGridEventsReceiver {
    void (*onScrollBarUpdate)(Ark_Int32 nodeId,
                              const Ark_Number index,
                              const Ark_Number offset);
    void (*onScrollIndex)(Ark_Int32 nodeId,
                          const Ark_Number first,
                          const Ark_Number last);
    void (*onItemDragStart)(Ark_Int32 nodeId,
                            const Ark_ItemDragInfo event,
                            const Ark_Number itemIndex);
    void (*onItemDragEnter)(Ark_Int32 nodeId,
                            const Ark_ItemDragInfo event);
    void (*onItemDragMove)(Ark_Int32 nodeId,
                           const Ark_ItemDragInfo event,
                           const Ark_Number itemIndex,
                           const Ark_Number insertIndex);
    void (*onItemDragLeave)(Ark_Int32 nodeId,
                            const Ark_ItemDragInfo event,
                            const Ark_Number itemIndex);
    void (*onItemDrop)(Ark_Int32 nodeId,
                       const Ark_ItemDragInfo event,
                       const Ark_Number itemIndex,
                       const Ark_Number insertIndex,
                       const Ark_Boolean isSuccess);
    void (*onScroll)(Ark_Int32 nodeId,
                     const Ark_Number scrollOffset,
                     const Ark_Int32 scrollState);
    void (*onReachStart)(Ark_Int32 nodeId);
    void (*onReachEnd)(Ark_Int32 nodeId);
    void (*onScrollStart)(Ark_Int32 nodeId);
    void (*onScrollStop)(Ark_Int32 nodeId);
    void (*onScrollFrameBegin)(Ark_Int32 nodeId,
                               const Ark_Number offset,
                               const Ark_Int32 state);
} GENERATED_ArkUIGridEventsReceiver;

typedef struct GENERATED_ArkUIGridItemEventsReceiver {
    void (*onSelect)(Ark_Int32 nodeId,
                     const Ark_Boolean isSelected);
} GENERATED_ArkUIGridItemEventsReceiver;

typedef struct GENERATED_ArkUIGridRowEventsReceiver {
    void (*onBreakpointChange)(Ark_Int32 nodeId,
                               const Ark_String breakpoints);
} GENERATED_ArkUIGridRowEventsReceiver;

typedef struct GENERATED_ArkUIImageEventsReceiver {
    void (*onComplete)(Ark_Int32 nodeId,
                       const Opt_Literal_Number_width_height_componentWidth_componentHeight_loadingStatus_contentWidth_contentHeight_contentOffsetX_contentOffsetY event);
    void (*onError)(Ark_Int32 nodeId,
                    const Ark_ImageError error);
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
    void (*onComplete)(Ark_Int32 nodeId,
                       const Ark_ImageLoadResult result);
    void (*onError)(Ark_Int32 nodeId,
                    const Ark_ImageError error);
} GENERATED_ArkUIImageSpanEventsReceiver;

typedef struct GENERATED_ArkUIListEventsReceiver {
    void (*onScroll)(Ark_Int32 nodeId,
                     const Ark_Number scrollOffset,
                     const Ark_Int32 scrollState);
    void (*onScrollIndex)(Ark_Int32 nodeId,
                          const Ark_Number start,
                          const Ark_Number end,
                          const Ark_Number center);
    void (*onScrollVisibleContentChange)(Ark_Int32 nodeId,
                                         const Ark_VisibleListContentInfo start,
                                         const Ark_VisibleListContentInfo end);
    void (*onReachStart)(Ark_Int32 nodeId);
    void (*onReachEnd)(Ark_Int32 nodeId);
    void (*onScrollStart)(Ark_Int32 nodeId);
    void (*onScrollStop)(Ark_Int32 nodeId);
    void (*onItemDelete)(Ark_Int32 nodeId,
                         const Ark_Number index);
    void (*onItemMove)(Ark_Int32 nodeId,
                       const Ark_Number from,
                       const Ark_Number to);
    void (*onItemDragStart)(Ark_Int32 nodeId,
                            const Ark_ItemDragInfo event,
                            const Ark_Number itemIndex);
    void (*onItemDragEnter)(Ark_Int32 nodeId,
                            const Ark_ItemDragInfo event);
    void (*onItemDragMove)(Ark_Int32 nodeId,
                           const Ark_ItemDragInfo event,
                           const Ark_Number itemIndex,
                           const Ark_Number insertIndex);
    void (*onItemDragLeave)(Ark_Int32 nodeId,
                            const Ark_ItemDragInfo event,
                            const Ark_Number itemIndex);
    void (*onItemDrop)(Ark_Int32 nodeId,
                       const Ark_ItemDragInfo event,
                       const Ark_Number itemIndex,
                       const Ark_Number insertIndex,
                       const Ark_Boolean isSuccess);
    void (*onScrollFrameBegin)(Ark_Int32 nodeId,
                               const Ark_Number offset,
                               const Ark_Int32 state);
} GENERATED_ArkUIListEventsReceiver;

typedef struct GENERATED_ArkUIListItemEventsReceiver {
    void (*onSelect)(Ark_Int32 nodeId,
                     const Ark_Boolean isSelected);
} GENERATED_ArkUIListItemEventsReceiver;

typedef struct GENERATED_ArkUILocationButtonEventsReceiver {
    void (*onClick)(Ark_Int32 nodeId,
                    const Ark_ClickEvent event,
                    const Ark_Int32 result);
} GENERATED_ArkUILocationButtonEventsReceiver;

typedef struct GENERATED_ArkUIMarqueeEventsReceiver {
    void (*onStart)(Ark_Int32 nodeId);
    void (*onBounce)(Ark_Int32 nodeId);
    void (*onFinish)(Ark_Int32 nodeId);
} GENERATED_ArkUIMarqueeEventsReceiver;

typedef struct GENERATED_ArkUIMenuItemEventsReceiver {
    void (*onChange)(Ark_Int32 nodeId,
                     const Ark_Boolean selected);
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
    void (*onStateChange)(Ark_Int32 nodeId,
                          const Ark_Boolean isActivated);
} GENERATED_ArkUINavRouterEventsReceiver;

typedef struct GENERATED_ArkUINavigationEventsReceiver {
    void (*onTitleModeChange)(Ark_Int32 nodeId,
                              const Ark_Int32 titleMode);
    void (*onNavBarStateChange)(Ark_Int32 nodeId,
                                const Ark_Boolean isVisible);
    void (*onNavigationModeChange)(Ark_Int32 nodeId,
                                   const Ark_Int32 mode);
    void (*navDestination)(Ark_Int32 nodeId,
                           const Ark_String name,
                           const Ark_CustomObject param);
    void (*customNavContentTransition)(Ark_Int32 nodeId,
                                       const Ark_NavContentInfo from,
                                       const Ark_NavContentInfo to,
                                       const Ark_Int32 operation);
} GENERATED_ArkUINavigationEventsReceiver;

typedef struct GENERATED_ArkUIPanelEventsReceiver {
    void (*onChange)(Ark_Int32 nodeId,
                     const Ark_Number width,
                     const Ark_Number height,
                     const Ark_Int32 mode);
    void (*onHeightChange)(Ark_Int32 nodeId,
                           const Ark_Number value);
} GENERATED_ArkUIPanelEventsReceiver;

typedef struct GENERATED_ArkUIPasteButtonEventsReceiver {
    void (*onClick)(Ark_Int32 nodeId,
                    const Ark_ClickEvent event,
                    const Ark_Int32 result);
} GENERATED_ArkUIPasteButtonEventsReceiver;

typedef struct GENERATED_ArkUIPatternLockEventsReceiver {
    void (*onPatternComplete)(Ark_Int32 nodeId,
                              const Array_Number input);
} GENERATED_ArkUIPatternLockEventsReceiver;

typedef struct GENERATED_ArkUIPluginComponentEventsReceiver {
    void (*onComplete)(Ark_Int32 nodeId);
    void (*onError)(Ark_Int32 nodeId,
                    const Literal_Number_errcode_String_msg info);
} GENERATED_ArkUIPluginComponentEventsReceiver;

typedef struct GENERATED_ArkUIRadioEventsReceiver {
    void (*onChange)(Ark_Int32 nodeId,
                     const Ark_Boolean isChecked);
} GENERATED_ArkUIRadioEventsReceiver;

typedef struct GENERATED_ArkUIRatingEventsReceiver {
    void (*onChange)(Ark_Int32 nodeId,
                     const Ark_Number value);
} GENERATED_ArkUIRatingEventsReceiver;

typedef struct GENERATED_ArkUIRefreshEventsReceiver {
    void (*onStateChange)(Ark_Int32 nodeId,
                          const Ark_Int32 state);
    void (*onRefreshing)(Ark_Int32 nodeId);
    void (*onOffsetChange)(Ark_Int32 nodeId,
                           const Ark_Number data);
} GENERATED_ArkUIRefreshEventsReceiver;

typedef struct GENERATED_ArkUIRichEditorEventsReceiver {
    void (*onReady)(Ark_Int32 nodeId);
    void (*onSelect)(Ark_Int32 nodeId,
                     const Ark_RichEditorSelection data);
    void (*onSelectionChange)(Ark_Int32 nodeId,
                              const Ark_RichEditorRange data);
    void (*aboutToIMEInput)(Ark_Int32 nodeId,
                            const Ark_RichEditorInsertValue data);
    void (*onIMEInputComplete)(Ark_Int32 nodeId,
                               const Ark_RichEditorTextSpanResult data);
    void (*onDidIMEInput)(Ark_Int32 nodeId,
                          const Ark_TextRange data);
    void (*aboutToDelete)(Ark_Int32 nodeId,
                          const Ark_RichEditorDeleteValue data);
    void (*onDeleteComplete)(Ark_Int32 nodeId);
    void (*onPaste)(Ark_Int32 nodeId,
                    const Opt_PasteEvent event);
    void (*onEditingChange)(Ark_Int32 nodeId,
                            const Ark_Boolean data);
    void (*onSubmit)(Ark_Int32 nodeId,
                     const Ark_Int32 enterKey,
                     const Ark_SubmitEvent event);
    void (*onWillChange)(Ark_Int32 nodeId,
                         const Ark_RichEditorChangeValue data);
    void (*onDidChange)(Ark_Int32 nodeId,
                        const Ark_TextRange rangeBefore,
                        const Ark_TextRange rangeAfter);
    void (*onCut)(Ark_Int32 nodeId,
                  const Ark_CutEvent data);
    void (*onCopy)(Ark_Int32 nodeId,
                   const Ark_CopyEvent data);
} GENERATED_ArkUIRichEditorEventsReceiver;

typedef struct GENERATED_ArkUIRichTextEventsReceiver {
    void (*onStart)(Ark_Int32 nodeId);
    void (*onComplete)(Ark_Int32 nodeId);
} GENERATED_ArkUIRichTextEventsReceiver;

typedef struct GENERATED_ArkUISaveButtonEventsReceiver {
    void (*onClick)(Ark_Int32 nodeId,
                    const Ark_ClickEvent event,
                    const Ark_Int32 result);
} GENERATED_ArkUISaveButtonEventsReceiver;

typedef struct GENERATED_ArkUIScrollEventsReceiver {
    void (*onScroll)(Ark_Int32 nodeId,
                     const Ark_Number xOffset,
                     const Ark_Number yOffset);
    void (*onDidScroll)(Ark_Int32 nodeId,
                        const Ark_Number xOffset,
                        const Ark_Number yOffset,
                        const Ark_Int32 scrollState);
    void (*onScrollEdge)(Ark_Int32 nodeId,
                         const Ark_Int32 side);
    void (*onScrollStart)(Ark_Int32 nodeId);
    void (*onScrollEnd)(Ark_Int32 nodeId);
    void (*onScrollStop)(Ark_Int32 nodeId);
    void (*onScrollFrameBegin)(Ark_Int32 nodeId,
                               const Ark_Number offset,
                               const Ark_Int32 state);
} GENERATED_ArkUIScrollEventsReceiver;

typedef struct GENERATED_ArkUISearchEventsReceiver {
    void (*inputFilter)(Ark_Int32 nodeId,
                        const Ark_String data);
    void (*onEditChange)(Ark_Int32 nodeId,
                         const Ark_Boolean data);
    void (*onSubmit)(Ark_Int32 nodeId,
                     const Ark_String value);
    void (*onChange)(Ark_Int32 nodeId,
                     const Ark_String value,
                     const Opt_PreviewText previewText);
    void (*onTextSelectionChange)(Ark_Int32 nodeId,
                                  const Ark_Number selectionStart,
                                  const Ark_Number selectionEnd);
    void (*onContentScroll)(Ark_Int32 nodeId,
                            const Ark_Number totalOffsetX,
                            const Ark_Number totalOffsetY);
    void (*onCopy)(Ark_Int32 nodeId,
                   const Ark_String value);
    void (*onCut)(Ark_Int32 nodeId,
                  const Ark_String value);
    void (*onPaste)(Ark_Int32 nodeId,
                    const Ark_String value,
                    const Ark_PasteEvent event);
    void (*onWillInsert)(Ark_Int32 nodeId,
                         const Ark_InsertValue data);
    void (*onDidInsert)(Ark_Int32 nodeId,
                        const Ark_InsertValue data);
    void (*onWillDelete)(Ark_Int32 nodeId,
                         const Ark_DeleteValue data);
    void (*onDidDelete)(Ark_Int32 nodeId,
                        const Ark_DeleteValue data);
} GENERATED_ArkUISearchEventsReceiver;

typedef struct GENERATED_ArkUISelectEventsReceiver {
    void (*onSelect)(Ark_Int32 nodeId,
                     const Ark_Number index,
                     const Ark_String value);
} GENERATED_ArkUISelectEventsReceiver;

typedef struct GENERATED_ArkUISliderEventsReceiver {
    void (*onChange)(Ark_Int32 nodeId,
                     const Ark_Number value,
                     const Ark_Int32 mode);
} GENERATED_ArkUISliderEventsReceiver;

typedef struct GENERATED_ArkUIStepperEventsReceiver {
    void (*onFinish)(Ark_Int32 nodeId);
    void (*onSkip)(Ark_Int32 nodeId);
    void (*onChange)(Ark_Int32 nodeId,
                     const Ark_Number prevIndex,
                     const Ark_Number index);
    void (*onNext)(Ark_Int32 nodeId,
                   const Ark_Number index,
                   const Ark_Number pendingIndex);
    void (*onPrevious)(Ark_Int32 nodeId,
                       const Ark_Number index,
                       const Ark_Number pendingIndex);
} GENERATED_ArkUIStepperEventsReceiver;

typedef struct GENERATED_ArkUISwiperEventsReceiver {
    void (*onChange)(Ark_Int32 nodeId,
                     const Ark_Number index);
    void (*onAnimationStart)(Ark_Int32 nodeId,
                             const Ark_Number index,
                             const Ark_Number targetIndex,
                             const Ark_SwiperAnimationEvent extraInfo);
    void (*onAnimationEnd)(Ark_Int32 nodeId,
                           const Ark_Number index,
                           const Ark_SwiperAnimationEvent extraInfo);
    void (*onGestureSwipe)(Ark_Int32 nodeId,
                           const Ark_Number index,
                           const Ark_SwiperAnimationEvent extraInfo);
    void (*onContentDidScroll)(Ark_Int32 nodeId,
                               const Ark_Number selectedIndex,
                               const Ark_Number index,
                               const Ark_Number position,
                               const Ark_Number mainAxisLength);
} GENERATED_ArkUISwiperEventsReceiver;

typedef struct GENERATED_ArkUITabsEventsReceiver {
    void (*onChange)(Ark_Int32 nodeId,
                     const Ark_Number index);
    void (*onTabBarClick)(Ark_Int32 nodeId,
                          const Ark_Number index);
    void (*onAnimationStart)(Ark_Int32 nodeId,
                             const Ark_Number index,
                             const Ark_Number targetIndex,
                             const Ark_TabsAnimationEvent event);
    void (*onAnimationEnd)(Ark_Int32 nodeId,
                           const Ark_Number index,
                           const Ark_TabsAnimationEvent event);
    void (*onGestureSwipe)(Ark_Int32 nodeId,
                           const Ark_Number index,
                           const Ark_TabsAnimationEvent event);
    void (*customContentTransition)(Ark_Int32 nodeId,
                                    const Ark_Number from,
                                    const Ark_Number to);
    void (*onContentWillChange)(Ark_Int32 nodeId,
                                const Ark_Number currentIndex,
                                const Ark_Number comingIndex);
} GENERATED_ArkUITabsEventsReceiver;

typedef struct GENERATED_ArkUITabContentEventsReceiver {
    void (*onWillShow)(Ark_Int32 nodeId);
    void (*onWillHide)(Ark_Int32 nodeId);
} GENERATED_ArkUITabContentEventsReceiver;

typedef struct GENERATED_ArkUITextEventsReceiver {
    void (*onCopy)(Ark_Int32 nodeId,
                   const Ark_String value);
    void (*onTextSelectionChange)(Ark_Int32 nodeId,
                                  const Ark_Number selectionStart,
                                  const Ark_Number selectionEnd);
} GENERATED_ArkUITextEventsReceiver;

typedef struct GENERATED_ArkUITextAreaEventsReceiver {
    void (*inputFilter)(Ark_Int32 nodeId,
                        const Ark_String value);
    void (*onSubmit)(Ark_Int32 nodeId,
                     const Ark_Int32 enterKey);
    void (*onChange)(Ark_Int32 nodeId,
                     const Ark_String value,
                     const Opt_PreviewText previewText);
    void (*onTextSelectionChange)(Ark_Int32 nodeId,
                                  const Ark_Number selectionStart,
                                  const Ark_Number selectionEnd);
    void (*onContentScroll)(Ark_Int32 nodeId,
                            const Ark_Number totalOffsetX,
                            const Ark_Number totalOffsetY);
    void (*onEditChange)(Ark_Int32 nodeId,
                         const Ark_Boolean isEditing);
    void (*onCopy)(Ark_Int32 nodeId,
                   const Ark_String value);
    void (*onCut)(Ark_Int32 nodeId,
                  const Ark_String value);
    void (*onPaste)(Ark_Int32 nodeId,
                    const Ark_String value,
                    const Ark_PasteEvent event);
    void (*onWillInsert)(Ark_Int32 nodeId,
                         const Ark_InsertValue data);
    void (*onDidInsert)(Ark_Int32 nodeId,
                        const Ark_InsertValue data);
    void (*onWillDelete)(Ark_Int32 nodeId,
                         const Ark_DeleteValue data);
    void (*onDidDelete)(Ark_Int32 nodeId,
                        const Ark_DeleteValue data);
} GENERATED_ArkUITextAreaEventsReceiver;

typedef struct GENERATED_ArkUITextClockEventsReceiver {
    void (*onDateChange)(Ark_Int32 nodeId,
                         const Ark_Number value);
} GENERATED_ArkUITextClockEventsReceiver;

typedef struct GENERATED_ArkUITextInputEventsReceiver {
    void (*onEditChanged)(Ark_Int32 nodeId,
                          const Ark_Boolean isEditing);
    void (*onEditChange)(Ark_Int32 nodeId,
                         const Ark_Boolean isEditing);
    void (*onSubmit)(Ark_Int32 nodeId,
                     const Ark_Int32 enterKey,
                     const Ark_SubmitEvent event);
    void (*onChange)(Ark_Int32 nodeId,
                     const Ark_String value,
                     const Opt_PreviewText previewText);
    void (*onTextSelectionChange)(Ark_Int32 nodeId,
                                  const Ark_Number selectionStart,
                                  const Ark_Number selectionEnd);
    void (*onContentScroll)(Ark_Int32 nodeId,
                            const Ark_Number totalOffsetX,
                            const Ark_Number totalOffsetY);
    void (*inputFilter)(Ark_Int32 nodeId,
                        const Ark_String value);
    void (*onCopy)(Ark_Int32 nodeId,
                   const Ark_String value);
    void (*onCut)(Ark_Int32 nodeId,
                  const Ark_String value);
    void (*onPaste)(Ark_Int32 nodeId,
                    const Ark_String value,
                    const Ark_PasteEvent event);
    void (*onSecurityStateChange)(Ark_Int32 nodeId,
                                  const Ark_Boolean data);
    void (*onWillInsert)(Ark_Int32 nodeId,
                         const Ark_InsertValue data);
    void (*onDidInsert)(Ark_Int32 nodeId,
                        const Ark_InsertValue data);
    void (*onWillDelete)(Ark_Int32 nodeId,
                         const Ark_DeleteValue data);
    void (*onDidDelete)(Ark_Int32 nodeId,
                        const Ark_DeleteValue data);
} GENERATED_ArkUITextInputEventsReceiver;

typedef struct GENERATED_ArkUITextPickerEventsReceiver {
    void (*onAccept)(Ark_Int32 nodeId,
                     const Ark_String value,
                     const Ark_Number index);
    void (*onCancel)(Ark_Int32 nodeId);
    void (*onChange)(Ark_Int32 nodeId,
                     const Union_String_Array_String value,
                     const Union_Number_Array_Number index);
} GENERATED_ArkUITextPickerEventsReceiver;

typedef struct GENERATED_ArkUITextTimerEventsReceiver {
    void (*onTimer)(Ark_Int32 nodeId,
                    const Ark_Number utc,
                    const Ark_Number elapsedTime);
} GENERATED_ArkUITextTimerEventsReceiver;

typedef struct GENERATED_ArkUITimePickerEventsReceiver {
    void (*onChange)(Ark_Int32 nodeId,
                     const Ark_TimePickerResult value);
} GENERATED_ArkUITimePickerEventsReceiver;

typedef struct GENERATED_ArkUIToggleEventsReceiver {
    void (*onChange)(Ark_Int32 nodeId,
                     const Ark_Boolean isOn);
} GENERATED_ArkUIToggleEventsReceiver;

typedef struct GENERATED_ArkUIVideoEventsReceiver {
    void (*onStart)(Ark_Int32 nodeId);
    void (*onPause)(Ark_Int32 nodeId);
    void (*onFinish)(Ark_Int32 nodeId);
    void (*onFullscreenChange)(Ark_Int32 nodeId,
                               const Literal_Boolean_fullscreen event);
    void (*onPrepared)(Ark_Int32 nodeId,
                       const Literal_Number_duration event);
    void (*onSeeking)(Ark_Int32 nodeId,
                      const Literal_Number_time event);
    void (*onSeeked)(Ark_Int32 nodeId,
                     const Literal_Number_time event);
    void (*onUpdate)(Ark_Int32 nodeId,
                     const Literal_Number_time event);
    void (*onError)(Ark_Int32 nodeId);
    void (*onStop)(Ark_Int32 nodeId);
} GENERATED_ArkUIVideoEventsReceiver;

typedef struct GENERATED_ArkUIWebEventsReceiver {
    void (*onPageEnd)(Ark_Int32 nodeId,
                      const Ark_OnPageEndEvent data);
    void (*onPageBegin)(Ark_Int32 nodeId,
                        const Ark_OnPageBeginEvent data);
    void (*onProgressChange)(Ark_Int32 nodeId,
                             const Ark_OnProgressChangeEvent data);
    void (*onTitleReceive)(Ark_Int32 nodeId,
                           const Ark_OnTitleReceiveEvent data);
    void (*onGeolocationHide)(Ark_Int32 nodeId);
    void (*onGeolocationShow)(Ark_Int32 nodeId,
                              const Ark_OnGeolocationShowEvent data);
    void (*onRequestSelected)(Ark_Int32 nodeId);
    void (*onAlert)(Ark_Int32 nodeId,
                    const Ark_OnAlertEvent data);
    void (*onBeforeUnload)(Ark_Int32 nodeId,
                           const Ark_OnBeforeUnloadEvent data);
    void (*onConfirm)(Ark_Int32 nodeId,
                      const Ark_OnConfirmEvent data);
    void (*onPrompt)(Ark_Int32 nodeId,
                     const Ark_OnPromptEvent data);
    void (*onConsole)(Ark_Int32 nodeId,
                      const Ark_OnConsoleEvent data);
    void (*onErrorReceive)(Ark_Int32 nodeId,
                           const Ark_OnErrorReceiveEvent data);
    void (*onHttpErrorReceive)(Ark_Int32 nodeId,
                               const Ark_OnHttpErrorReceiveEvent data);
    void (*onDownloadStart)(Ark_Int32 nodeId,
                            const Ark_OnDownloadStartEvent data);
    void (*onRefreshAccessedHistory)(Ark_Int32 nodeId,
                                     const Ark_OnRefreshAccessedHistoryEvent data);
    void (*onUrlLoadIntercept)(Ark_Int32 nodeId,
                               const Opt_Literal_Union_String_WebResourceRequest_data event);
    void (*onSslErrorReceive)(Ark_Int32 nodeId,
                              const Opt_Literal_Function_handler_CustomObject_error event);
    void (*onRenderExited0)(Ark_Int32 nodeId,
                            const Ark_OnRenderExitedEvent data);
    void (*onShowFileSelector)(Ark_Int32 nodeId,
                               const Ark_OnShowFileSelectorEvent data);
    void (*onRenderExited1)(Ark_Int32 nodeId,
                            const Opt_Literal_CustomObject_detail event);
    void (*onFileSelectorShow)(Ark_Int32 nodeId,
                               const Opt_Literal_Function_callback_CustomObject_fileSelector event);
    void (*onResourceLoad)(Ark_Int32 nodeId,
                           const Ark_OnResourceLoadEvent data);
    void (*onFullScreenExit)(Ark_Int32 nodeId);
    void (*onFullScreenEnter)(Ark_Int32 nodeId,
                              const Ark_FullScreenEnterEvent event);
    void (*onScaleChange)(Ark_Int32 nodeId,
                          const Ark_OnScaleChangeEvent data);
    void (*onHttpAuthRequest)(Ark_Int32 nodeId,
                              const Ark_OnHttpAuthRequestEvent data);
    void (*onInterceptRequest)(Ark_Int32 nodeId,
                               const Ark_OnInterceptRequestEvent data);
    void (*onPermissionRequest)(Ark_Int32 nodeId,
                                const Ark_OnPermissionRequestEvent data);
    void (*onScreenCaptureRequest)(Ark_Int32 nodeId,
                                   const Ark_OnScreenCaptureRequestEvent data);
    void (*onContextMenuShow)(Ark_Int32 nodeId,
                              const Ark_OnContextMenuShowEvent data);
    void (*onContextMenuHide)(Ark_Int32 nodeId);
    void (*onSearchResultReceive)(Ark_Int32 nodeId,
                                  const Ark_OnSearchResultReceiveEvent data);
    void (*onScroll)(Ark_Int32 nodeId,
                     const Ark_OnScrollEvent data);
    void (*onSslErrorEventReceive)(Ark_Int32 nodeId,
                                   const Ark_OnSslErrorEventReceiveEvent data);
    void (*onSslErrorEvent)(Ark_Int32 nodeId,
                            const Ark_SslErrorEvent sslErrorEvent);
    void (*onClientAuthenticationRequest)(Ark_Int32 nodeId,
                                          const Ark_OnClientAuthenticationEvent data);
    void (*onWindowNew)(Ark_Int32 nodeId,
                        const Ark_OnWindowNewEvent data);
    void (*onWindowExit)(Ark_Int32 nodeId);
    void (*onInterceptKeyEvent)(Ark_Int32 nodeId,
                                const Ark_KeyEvent event);
    void (*onTouchIconUrlReceived)(Ark_Int32 nodeId,
                                   const Ark_OnTouchIconUrlReceivedEvent data);
    void (*onFaviconReceived)(Ark_Int32 nodeId,
                              const Ark_OnFaviconReceivedEvent data);
    void (*onPageVisible)(Ark_Int32 nodeId,
                          const Ark_OnPageVisibleEvent data);
    void (*onDataResubmitted)(Ark_Int32 nodeId,
                              const Ark_OnDataResubmittedEvent data);
    void (*onAudioStateChanged)(Ark_Int32 nodeId,
                                const Ark_OnAudioStateChangedEvent data);
    void (*onFirstContentfulPaint)(Ark_Int32 nodeId,
                                   const Ark_OnFirstContentfulPaintEvent data);
    void (*onFirstMeaningfulPaint)(Ark_Int32 nodeId,
                                   const Ark_FirstMeaningfulPaint firstMeaningfulPaint);
    void (*onLargestContentfulPaint)(Ark_Int32 nodeId,
                                     const Ark_LargestContentfulPaint largestContentfulPaint);
    void (*onLoadIntercept)(Ark_Int32 nodeId,
                            const Ark_OnLoadInterceptEvent data);
    void (*onControllerAttached)(Ark_Int32 nodeId);
    void (*onOverScroll)(Ark_Int32 nodeId,
                         const Ark_OnOverScrollEvent data);
    void (*onSafeBrowsingCheckResult)(Ark_Int32 nodeId,
                                      const Ark_Int32 threatType);
    void (*onNavigationEntryCommitted)(Ark_Int32 nodeId,
                                       const Ark_LoadCommittedDetails loadCommittedDetails);
    void (*onIntelligentTrackingPreventionResult)(Ark_Int32 nodeId,
                                                  const Ark_IntelligentTrackingPreventionDetails details);
    void (*onNativeEmbedLifecycleChange)(Ark_Int32 nodeId,
                                         const Ark_NativeEmbedDataInfo event);
    void (*onNativeEmbedVisibilityChange)(Ark_Int32 nodeId,
                                          const Ark_NativeEmbedVisibilityInfo nativeEmbedVisibilityInfo);
    void (*onNativeEmbedGestureEvent)(Ark_Int32 nodeId,
                                      const Ark_NativeEmbedTouchInfo event);
    void (*onOverrideUrlLoading)(Ark_Int32 nodeId,
                                 const Ark_Materialized webResourceRequest);
    void (*onRenderProcessNotResponding)(Ark_Int32 nodeId,
                                         const Ark_RenderProcessNotRespondingData data);
    void (*onRenderProcessResponding)(Ark_Int32 nodeId);
    void (*onViewportFitChanged)(Ark_Int32 nodeId,
                                 const Ark_Int32 viewportFit);
    void (*onInterceptKeyboardAttach)(Ark_Int32 nodeId,
                                      const Ark_WebKeyboardCallbackInfo keyboardCallbackInfo);
    void (*onAdsBlocked)(Ark_Int32 nodeId,
                         const Ark_AdsBlockedDetails details);
} GENERATED_ArkUIWebEventsReceiver;

typedef struct GENERATED_ArkUIXComponentEventsReceiver {
    void (*onLoad)(Ark_Int32 nodeId,
                   const Opt_CustomObject event);
    void (*onDestroy)(Ark_Int32 nodeId);
} GENERATED_ArkUIXComponentEventsReceiver;

typedef struct GENERATED_ArkUISideBarContainerEventsReceiver {
    void (*onChange)(Ark_Int32 nodeId,
                     const Ark_Boolean value);
} GENERATED_ArkUISideBarContainerEventsReceiver;

typedef struct GENERATED_ArkUIWaterFlowEventsReceiver {
    void (*onReachStart)(Ark_Int32 nodeId);
    void (*onReachEnd)(Ark_Int32 nodeId);
    void (*onScrollFrameBegin)(Ark_Int32 nodeId,
                               const Ark_Number offset,
                               const Ark_Int32 state);
    void (*onScrollIndex)(Ark_Int32 nodeId,
                          const Ark_Number first,
                          const Ark_Number last);
} GENERATED_ArkUIWaterFlowEventsReceiver;

typedef struct GENERATED_ArkUIUIExtensionComponentEventsReceiver {
    void (*onTerminated)(Ark_Int32 nodeId,
                         const Ark_TerminationInfo data);
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
    const GENERATED_ArkUIICurveAccessor* (*getICurveAccessor)();
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
    GENERATED_ARKUI_ABILITY_COMPONENT,
    GENERATED_ARKUI_ALPHABET_INDEXER,
    GENERATED_ARKUI_ANIMATOR,
    GENERATED_ARKUI_BADGE,
    GENERATED_ARKUI_BLANK,
    GENERATED_ARKUI_BUTTON,
    GENERATED_ARKUI_CALENDAR,
    GENERATED_ARKUI_CALENDAR_PICKER,
    GENERATED_ARKUI_CANVAS,
    GENERATED_ARKUI_CHECKBOX,
    GENERATED_ARKUI_CHECKBOX_GROUP,
    GENERATED_ARKUI_CIRCLE,
    GENERATED_ARKUI_COLUMN,
    GENERATED_ARKUI_COLUMN_SPLIT,
    GENERATED_ARKUI_COMMON_METHOD,
    GENERATED_ARKUI_COMMON_SHAPE_METHOD,
    GENERATED_ARKUI_COMMON,
    GENERATED_ARKUI_SCROLLABLE_COMMON_METHOD,
    GENERATED_ARKUI_COMPONENT_3D,
    GENERATED_ARKUI_CONTAINER_SPAN,
    GENERATED_ARKUI_COUNTER,
    GENERATED_ARKUI_DATA_PANEL,
    GENERATED_ARKUI_DATE_PICKER,
    GENERATED_ARKUI_DIVIDER,
    GENERATED_ARKUI_EFFECT_COMPONENT,
    GENERATED_ARKUI_ELLIPSE,
    GENERATED_ARKUI_EMBEDDED_COMPONENT,
    GENERATED_ARKUI_FLEX,
    GENERATED_ARKUI_FLOW_ITEM,
    GENERATED_ARKUI_FOLDER_STACK,
    GENERATED_ARKUI_FORM_COMPONENT,
    GENERATED_ARKUI_FORM_LINK,
    GENERATED_ARKUI_GAUGE,
    GENERATED_ARKUI_GRID,
    GENERATED_ARKUI_GRID_ITEM,
    GENERATED_ARKUI_GRID_COL,
    GENERATED_ARKUI_GRID_CONTAINER,
    GENERATED_ARKUI_GRID_ROW,
    GENERATED_ARKUI_HYPERLINK,
    GENERATED_ARKUI_IMAGE,
    GENERATED_ARKUI_IMAGE_ANIMATOR,
    GENERATED_ARKUI_IMAGE_SPAN,
    GENERATED_ARKUI_LINE,
    GENERATED_ARKUI_LIST,
    GENERATED_ARKUI_LIST_ITEM,
    GENERATED_ARKUI_LIST_ITEM_GROUP,
    GENERATED_ARKUI_LOADING_PROGRESS,
    GENERATED_ARKUI_LOCATION_BUTTON,
    GENERATED_ARKUI_MARQUEE,
    GENERATED_ARKUI_MEDIA_CACHED_IMAGE,
    GENERATED_ARKUI_MENU,
    GENERATED_ARKUI_MENU_ITEM,
    GENERATED_ARKUI_MENU_ITEM_GROUP,
    GENERATED_ARKUI_NAV_DESTINATION,
    GENERATED_ARKUI_NAV_ROUTER,
    GENERATED_ARKUI_NAVIGATION,
    GENERATED_ARKUI_NAVIGATOR,
    GENERATED_ARKUI_NODE_CONTAINER,
    GENERATED_ARKUI_PANEL,
    GENERATED_ARKUI_PASTE_BUTTON,
    GENERATED_ARKUI_PATH,
    GENERATED_ARKUI_PATTERN_LOCK,
    GENERATED_ARKUI_PLUGIN_COMPONENT,
    GENERATED_ARKUI_POLYGON,
    GENERATED_ARKUI_POLYLINE,
    GENERATED_ARKUI_QRCODE,
    GENERATED_ARKUI_RADIO,
    GENERATED_ARKUI_RATING,
    GENERATED_ARKUI_RECT,
    GENERATED_ARKUI_REFRESH,
    GENERATED_ARKUI_RELATIVE_CONTAINER,
    GENERATED_ARKUI_RICH_EDITOR,
    GENERATED_ARKUI_RICH_TEXT,
    GENERATED_ARKUI_ROOT_SCENE,
    GENERATED_ARKUI_ROW,
    GENERATED_ARKUI_ROW_SPLIT,
    GENERATED_ARKUI_SAVE_BUTTON,
    GENERATED_ARKUI_SCREEN,
    GENERATED_ARKUI_SCROLL,
    GENERATED_ARKUI_SCROLL_BAR,
    GENERATED_ARKUI_SEARCH,
    GENERATED_ARKUI_SECURITY_COMPONENT_METHOD,
    GENERATED_ARKUI_SELECT,
    GENERATED_ARKUI_SHAPE,
    GENERATED_ARKUI_SLIDER,
    GENERATED_ARKUI_BASE_SPAN,
    GENERATED_ARKUI_SPAN,
    GENERATED_ARKUI_STACK,
    GENERATED_ARKUI_STEPPER,
    GENERATED_ARKUI_STEPPER_ITEM,
    GENERATED_ARKUI_SWIPER,
    GENERATED_ARKUI_SYMBOL_GLYPH,
    GENERATED_ARKUI_SYMBOL_SPAN,
    GENERATED_ARKUI_TABS,
    GENERATED_ARKUI_TAB_CONTENT,
    GENERATED_ARKUI_TEXT,
    GENERATED_ARKUI_TEXT_AREA,
    GENERATED_ARKUI_TEXT_CLOCK,
    GENERATED_ARKUI_TEXT_INPUT,
    GENERATED_ARKUI_TEXT_PICKER,
    GENERATED_ARKUI_TEXT_TIMER,
    GENERATED_ARKUI_TIME_PICKER,
    GENERATED_ARKUI_TOGGLE,
    GENERATED_ARKUI_VIDEO,
    GENERATED_ARKUI_WEB,
    GENERATED_ARKUI_WINDOW_SCENE,
    GENERATED_ARKUI_XCOMPONENT,
    GENERATED_ARKUI_SIDE_BAR_CONTAINER,
    GENERATED_ARKUI_REMOTE_WINDOW,
    GENERATED_ARKUI_WATER_FLOW,
    GENERATED_ARKUI_UIEXTENSION_COMPONENT,
    GENERATED_ARKUI_LINEAR_INDICATOR
} GENERATED_Ark_NodeType;

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

typedef struct GENERATED_ArkUIBasicNodeAPI {
    Ark_Int32 version;

    /// Tree operations.
    Ark_NodeHandle (*createNode)(GENERATED_Ark_NodeType type,
                                 Ark_Int32 id, Ark_Int32 flags);

    Ark_NodeHandle (*getNodeByViewStack)();
    void (*disposeNode)(Ark_NodeHandle node);

    void (*dumpTreeNode)(Ark_NodeHandle node);

    Ark_Int32 (*addChild)(Ark_NodeHandle parent,
                          Ark_NodeHandle child);
    void (*removeChild)(Ark_NodeHandle parent,
                        Ark_NodeHandle child);
    Ark_Int32 (*insertChildAfter)(Ark_NodeHandle parent,
                                  Ark_NodeHandle child, Ark_NodeHandle sibling);
    Ark_Int32 (*insertChildBefore)(Ark_NodeHandle parent,
                                   Ark_NodeHandle child,
                                   Ark_NodeHandle sibling);
    Ark_Int32 (*insertChildAt)(Ark_NodeHandle parent,
                               Ark_NodeHandle child,
                               Ark_Int32 position);

    // Commit attributes updates for node.
    void (*applyModifierFinish)(Ark_NodeHandle nodePtr);
    // the flag can combine different flag like Ark_DIRTY_FLAG_MEASURE | Ark_DIRTY_FLAG_RENDER
    void (*markDirty)(Ark_NodeHandle nodePtr,
                      Ark_UInt32 dirtyFlag);
    Ark_Boolean (*isBuilderNode)(Ark_NodeHandle node);

    Ark_Float32 (*convertLengthMetricsUnit)(Ark_Float32 value,
                                            Ark_Int32 originUnit,
                                            Ark_Int32 targetUnit);
} GENERATED_ArkUIBasicNodeAPI;

typedef struct GENERATED_ArkUIExtendedNodeAPI {
    Ark_Int32 version;

    void (*setAppendGroupedLog)(void* pFunc);

    const GENERATED_Ark_UtilsModifier* (*getUtilsModifier)();

    void (*setCallbackMethod)(GENERATED_Ark_APICallbackMethod* method);

    // the custom node is not set in create.
    void (*setCustomMethodFlag)(Ark_NodeHandle node,
                                Ark_Int32 flag);
    Ark_Int32 (*getCustomMethodFlag)(Ark_NodeHandle node);

    // setCustomCallback is without the context
    void (*setCustomCallback) (Ark_VMContext  vmContext,
                               Ark_NodeHandle node,
                               Ark_Int32 callbackId);
    // make void instead return type Ark_Int32
    Ark_Int32 (*measureLayoutAndDraw) (Ark_VMContext  vmContext,
                                       Ark_NodeHandle node);
    Ark_Int32 (*measureNode) (Ark_VMContext  vmContext,
                              Ark_NodeHandle node,
                              Ark_Float32* data);
    Ark_Int32 (*layoutNode) (Ark_VMContext  vmContext,
                             Ark_NodeHandle node,
                             Ark_Float32 (*data)[2]);
    Ark_Int32 (*drawNode) (Ark_VMContext  vmContext,
                           Ark_NodeHandle node,
                           Ark_Float32* data);
    void (*setAttachNodePtr) (Ark_NodeHandle node,
                              void* value);
    void* (*getAttachNodePtr) (Ark_NodeHandle node);

    // may be better to use int in px unit
    void (*setMeasureWidth)(Ark_NodeHandle node,
                            Ark_Int32 value);
    Ark_Int32 (*getMeasureWidth)(Ark_NodeHandle node);
    void (*setMeasureHeight)(Ark_NodeHandle node,
                             Ark_Int32 value);
    Ark_Int32 (*getMeasureHeight)(Ark_NodeHandle node);
    void (*setX)(Ark_NodeHandle node, Ark_Int32 value);
    Ark_Int32 (*getX)(Ark_NodeHandle node);
    void (*setY)(Ark_NodeHandle node,
                 Ark_Int32 value);
    Ark_Int32 (*getY)(Ark_NodeHandle node);

    void (*getLayoutConstraint)(Ark_NodeHandle node,
                                Ark_Int32* value);
    void (*setAlignment)(Ark_NodeHandle node,
                         Ark_Int32 value);
    Ark_Int32 (*getAlignment)(Ark_NodeHandle node);

    Ark_Int32 (*indexerChecker) (Ark_VMContext  vmContext,
                                 Ark_NodeHandle node);
    void (*setRangeUpdater)(Ark_NodeHandle node,
                            Ark_Int32 updatedId);
    void (*setLazyItemIndexer) (Ark_VMContext  vmContext,
                                Ark_NodeHandle node,
                                Ark_Int32 indexerId);

    /// Vsync support
    Ark_PipelineContext (*getPipelineContext)(Ark_NodeHandle node);
    void (*setVsyncCallback)(Ark_VMContext  vmContext,
                             Ark_PipelineContext pipelineContext,
                             Ark_Int32 callbackId);
    void (*unblockVsyncWait)(Ark_VMContext  vmContext,
                             Ark_PipelineContext pipelineContext);

  void (*setChildTotalCount)(Ark_NodeHandle node,
                             Ark_Int32 totalCount);

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

/* clang-format on */

#endif  // GENERATED_FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_API_H
