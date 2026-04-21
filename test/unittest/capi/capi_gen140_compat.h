/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ARKUI_ACE_ENGINE_TEST_UNITTEST_CAPI_GEN140_COMPAT_H
#define FOUNDATION_ARKUI_ACE_ENGINE_TEST_UNITTEST_CAPI_GEN140_COMPAT_H

#include "arkoala_api_generated.h"

// WRONG_GEN_140: Compatibility aliases for types from generation 140
// These types were renamed in the newer CAPI generation
// This header provides backward compatibility mapping: OLD_GEN_140_NAME -> NEW_NAME

// Font type: Ark_Font -> Ark_arkui_component_units_Font
using Ark_Font = Ark_arkui_component_units_Font;
using Opt_Font = Opt_arkui_component_units_Font;

// Color type: Ark_Color -> Ark_arkui_component_enums_Color
using Ark_Color = Ark_arkui_component_enums_Color;

// Color enum values: ARK_COLOR_* -> ARK_ARKUI_COMPONENT_ENUMS_COLOR_*
constexpr auto ARK_COLOR_WHITE = ARK_ARKUI_COMPONENT_ENUMS_COLOR_WHITE;
constexpr auto ARK_COLOR_BLACK = ARK_ARKUI_COMPONENT_ENUMS_COLOR_BLACK;
constexpr auto ARK_COLOR_BLUE = ARK_ARKUI_COMPONENT_ENUMS_COLOR_BLUE;
constexpr auto ARK_COLOR_BROWN = ARK_ARKUI_COMPONENT_ENUMS_COLOR_BROWN;
constexpr auto ARK_COLOR_GRAY = ARK_ARKUI_COMPONENT_ENUMS_COLOR_GRAY;
constexpr auto ARK_COLOR_GREEN = ARK_ARKUI_COMPONENT_ENUMS_COLOR_GREEN;
constexpr auto ARK_COLOR_GREY = ARK_ARKUI_COMPONENT_ENUMS_COLOR_GREY;
constexpr auto ARK_COLOR_ORANGE = ARK_ARKUI_COMPONENT_ENUMS_COLOR_ORANGE;
constexpr auto ARK_COLOR_PINK = ARK_ARKUI_COMPONENT_ENUMS_COLOR_PINK;
constexpr auto ARK_COLOR_RED = ARK_ARKUI_COMPONENT_ENUMS_COLOR_RED;
constexpr auto ARK_COLOR_YELLOW = ARK_ARKUI_COMPONENT_ENUMS_COLOR_YELLOW;
constexpr auto ARK_COLOR_TRANSPARENT = ARK_ARKUI_COMPONENT_ENUMS_COLOR_TRANSPARENT;

// Union types with Color
using Ark_Union_Color_String_Resource_I64 = Ark_Union_arkui_component_enums_Color_String_Resource_I64;
using Opt_Union_Color_String_Resource_I64 = Opt_Union_arkui_component_enums_Color_String_Resource_I64;

using Ark_Union_Color_I32_String_Resource = Ark_Union_arkui_component_enums_Color_I32_String_Resource;
using Opt_Union_Color_I32_String_Resource = Opt_Union_arkui_component_enums_Color_I32_String_Resource;

using Ark_Union_Color_String_Resource_ColoringStrategy =
    Ark_Union_arkui_component_enums_Color_String_Resource_ColoringStrategy;
using Opt_Union_Color_String_Resource_ColoringStrategy =
    Opt_Union_arkui_component_enums_Color_String_Resource_ColoringStrategy;

// Array types - Int32 renamed to I32
using Array_Int32 = Array_I32;

// Tuple types - Ark_Tuple_ResourceColor_Number was removed, use F64 version instead
using Ark_Tuple_ResourceColor_Number = Ark_Tuple_ResourceColor_F64;

// Union types with Bindable suffix - renamed to include full variant list
using Opt_Union_Boolean_Bindable = Opt_Union_Boolean_Bindable_Boolean;
using Ark_Union_Boolean_Bindable = Ark_Union_Boolean_Bindable_Boolean;

// Union types - CustomBuilder renamed to CustomNodeBuilder
using Opt_Union_CustomBuilder_SwipeActionItem = Opt_Union_CustomNodeBuilder_SwipeActionItem;
using Ark_Union_CustomBuilder_SwipeActionItem = Ark_Union_CustomNodeBuilder_SwipeActionItem;

using Opt_Union_CustomBuilder_ResourceColor = Opt_Union_CustomNodeBuilder_ResourceColor;
using Ark_Union_CustomBuilder_ResourceColor = Ark_Union_CustomNodeBuilder_ResourceColor;

using Opt_Union_CustomBuilder_ComponentContentBase = Opt_Union_CustomNodeBuilder_ComponentContentBase;
using Ark_Union_CustomBuilder_ComponentContentBase = Ark_Union_CustomNodeBuilder_ComponentContentBase;

// NOTE:
// In this API generation there is no "...CustomNodeBuilder_ComponentContent" union.
// The available renamed union is "...CustomNodeBuilder_ComponentContentBase".
using Opt_Union_CustomBuilder_ComponentContent = Opt_Union_CustomNodeBuilder_ComponentContentBase;
using Ark_Union_CustomBuilder_ComponentContent = Ark_Union_CustomNodeBuilder_ComponentContentBase;

using Opt_Union_CustomBuilder_DragItemInfo_String = Opt_Union_CustomNodeBuilder_DragItemInfo_String;
using Ark_Union_CustomBuilder_DragItemInfo_String = Ark_Union_CustomNodeBuilder_DragItemInfo_String;

using Opt_Union_String_CustomBuilder_ComponentContent = Opt_Union_String_CustomNodeBuilder_ComponentContent;
using Ark_Union_String_CustomBuilder_ComponentContent = Ark_Union_String_CustomNodeBuilder_ComponentContent;

// Array types - Float64 renamed to F64
using Array_Float64 = Array_F64;
using Opt_Array_Float64 = Opt_Array_F64;

// Array types - Int32 renamed to I32
using Opt_Array_Int32 = Opt_Array_I32;
using Array_Int32 = Array_I32;

// Union types - added namespace prefixes
using Ark_Union_PixelMap_ResourceStr_DrawableDescriptor_ImageContent =
    Ark_Union_image_PixelMap_ResourceStr_DrawableDescriptor_ImageContent;
using Opt_Union_PixelMap_ResourceStr_DrawableDescriptor_ImageContent =
    Opt_Union_image_PixelMap_ResourceStr_DrawableDescriptor_ImageContent;

using Opt_Union_ResourceColor_ColorContent_ColorMetrics =
    Opt_Union_ResourceColor_ColorContent_ColorMetricsExt;
using Ark_Union_ResourceColor_ColorContent_ColorMetrics =
    Ark_Union_ResourceColor_ColorContent_ColorMetricsExt;

// Union types - Curve prefixes added
using Opt_Union_Curve_String_ICurve = Opt_Union_curves_Curve_String_curves_ICurve;
using Ark_Union_Curve_String_ICurve = Ark_Union_curves_Curve_String_curves_ICurve;

// Union types - ColorFilter with drawing_ prefix (DrawingColorFilter -> drawing_ColorFilter)
using Ark_Union_ColorFilter_DrawingColorFilter = Ark_Union_ColorFilter_drawing_ColorFilter;
using Opt_Union_ColorFilter_DrawingColorFilter = Opt_Union_ColorFilter_drawing_ColorFilter;

// Union types - ResourceColor without ColorContent
using Opt_Union_ResourceColor_ColorMetrics = Opt_Union_ResourceColor_ColorMetricsExt;
using Ark_Union_ResourceColor_ColorMetrics = Ark_Union_ResourceColor_ColorMetricsExt;

// Union types - Margin renamed to Padding
using Opt_Union_Margin_Length_LocalizedMargin = Opt_Union_Padding_Length_LocalizedPadding;
using Ark_Union_Margin_Length_LocalizedMargin = Ark_Union_Padding_Length_LocalizedPadding;

// Union types - ResourceStr with image prefix
using Opt_Union_ResourceStr_PixelMap = Opt_Union_ResourceStr_image_PixelMap;
using Ark_Union_ResourceStr_PixelMap = Ark_Union_ResourceStr_image_PixelMap;

// Union types - ImageBitmap with image prefix
using Opt_Union_ImageBitmap_PixelMap = Opt_Union_ImageBitmap_image_PixelMap;
using Ark_Union_ImageBitmap_PixelMap = Ark_Union_ImageBitmap_image_PixelMap;

// Union types - PixelMap_ResourceStr with image prefix
// PixelMap/String unions
using Opt_Union_PixelMap_String = Opt_Union_image_PixelMap_String;
using Ark_Union_PixelMap_String = Ark_Union_image_PixelMap_String;
using Opt_Union_PixelMap_ResourceStr = Opt_Union_image_PixelMap_ResourceStr;
using Ark_Union_PixelMap_ResourceStr = Ark_Union_image_PixelMap_ResourceStr;

// Union types - LengthMetrics_Margin renamed to LengthMetrics_LeadingMarginPlaceholder
// LengthMetrics/Margin unions - OLD had Margin, NEW split into LeadingMarginPlaceholder and Padding
using Opt_Union_LengthMetrics_Margin = Opt_Union_LengthMetrics_Padding;
using Ark_Union_LengthMetrics_Margin = Ark_Union_LengthMetrics_Padding;

// Dimension/Margin unions - same pattern as LengthMetrics
using Opt_Union_Dimension_Margin = Opt_Union_Dimension_Padding;
using Ark_Union_Dimension_Margin = Ark_Union_Dimension_Padding;

// Union types - Color_String_Resource with arkui_component_enums prefix
using Opt_Union_Color_String_Resource = Opt_Union_arkui_component_enums_Color_String_Resource;
using Ark_Union_Color_String_Resource = Ark_Union_arkui_component_enums_Color_String_Resource;

// Union types - Canvas style with Color enum prefix
using Opt_Union_String_Color_I32_CanvasGradient_CanvasPattern =
    Opt_Union_String_arkui_component_enums_Color_I32_CanvasGradient_CanvasPattern;
using Ark_Union_String_Color_I32_CanvasGradient_CanvasPattern =
    Ark_Union_String_arkui_component_enums_Color_I32_CanvasGradient_CanvasPattern;

// Union types - String_Resource_PixelMap with image prefix
using Opt_Union_String_Resource_PixelMap = Opt_Union_String_Resource_image_PixelMap;
using Ark_Union_String_Resource_PixelMap = Ark_Union_String_Resource_image_PixelMap;

// Union types - String_Resource_PixelMap_ImageAlt with image prefix
using Opt_Union_String_Resource_PixelMap_ImageAlt = Opt_Union_String_Resource_image_PixelMap_ImageAlt;
using Ark_Union_String_Resource_PixelMap_ImageAlt = Ark_Union_String_Resource_image_PixelMap_ImageAlt;

// Union types - I32_Bindable with variant suffix
using Opt_Union_I32_Bindable = Opt_Union_I32_Bindable_I32;
using Ark_Union_I32_Bindable = Ark_Union_I32_Bindable_I32;

// Union types - F64_Bindable with variant suffix
using Opt_Union_F64_Bindable = Opt_Union_F64_Bindable_F64;
using Ark_Union_F64_Bindable = Ark_Union_F64_Bindable_F64;

// KeyboardAvoidMode - common variant with full path
using Opt_KeyboardAvoidMode = Opt_arkui_component_common_KeyboardAvoidMode;
using Ark_KeyboardAvoidMode = Ark_arkui_component_common_KeyboardAvoidMode;

// Union String_PixelMap_Resource with image prefix
using Opt_Union_String_PixelMap_Resource = Opt_Union_String_image_PixelMap_Resource;
using Ark_Union_String_PixelMap_Resource = Ark_Union_String_image_PixelMap_Resource;

// Union String_Bindable with variant suffix
using Opt_Union_String_Bindable = Opt_Union_String_Bindable_String;
using Ark_Union_String_Bindable = Ark_Union_String_Bindable_String;

// Union types - Date_Bindable with full variant names
using Opt_Union_Date_Bindable = Opt_Union_Date_Bindable_Date;
using Ark_Union_Date_Bindable = Ark_Union_Date_Bindable_Date;

// Union types - I32_Resource_Bindable_Bindable with full variant names
using Opt_Union_I32_Resource_Bindable_Bindable = Opt_Union_I32_Resource_Bindable_I32_Bindable_Resource;
using Ark_Union_I32_Resource_Bindable_Bindable = Ark_Union_I32_Resource_Bindable_I32_Bindable_Resource;

// Union types - ResourceStr_Bindable_Bindable with full variant names
using Opt_Union_ResourceStr_Bindable_Bindable = Opt_Union_ResourceStr_Bindable_String_Bindable_Resource;
using Ark_Union_ResourceStr_Bindable_Bindable = Ark_Union_ResourceStr_Bindable_String_Bindable_Resource;

// Union types - ResourceStr_Bindable with triple Bindable suffix
using Opt_Union_ResourceStr_Bindable_Bindable_Bindable =
    Opt_Union_ResourceStr_Bindable_ResourceStr_Bindable_Resource_Bindable_String;
using Ark_Union_ResourceStr_Bindable_Bindable_Bindable =
    Ark_Union_ResourceStr_Bindable_ResourceStr_Bindable_Resource_Bindable_String;

// Union types - ResourceStr with Array - renamed to BindableResourceStr_BindableResourceStrArray
using Opt_Union_ResourceStr_Array_ResourceStr_Bindable_Bindable =
    Opt_Union_BindableResourceStr_BindableResourceStrArray;
using Ark_Union_ResourceStr_Array_ResourceStr_Bindable_Bindable =
    Ark_Union_BindableResourceStr_BindableResourceStrArray;

// Union types - I32 with Array - full variant names
using Opt_Union_I32_Array_I32_Bindable_Bindable = Opt_Union_I32_Array_I32_Bindable_I32_Bindable_Array_I32;
using Ark_Union_I32_Array_I32_Bindable_Bindable = Ark_Union_I32_Array_I32_Bindable_I32_Bindable_Array_I32;

// Union types - Number_Resource renamed to F64_Resource
using Opt_Union_Number_Resource = Opt_Union_F64_Resource;
using Ark_Union_Number_Resource = Ark_Union_F64_Resource;

// Union types - Number_String renamed to F64_String
using Opt_Union_Number_String = Opt_Union_F64_String;
using Ark_Union_Number_String = Ark_Union_F64_String;

// Union types - Number_String_Resource renamed to F64_String_Resource
using Opt_Union_Number_String_Resource = Opt_Union_F64_String_Resource;
using Ark_Union_Number_String_Resource = Ark_Union_F64_String_Resource;

// Union types - Swiper display count gained ItemFillPolicy variant suffix
using Opt_Union_I32_String_SwiperAutoFill = Opt_Union_I32_String_SwiperAutoFill_ItemFillPolicy;
using Ark_Union_I32_String_SwiperAutoFill = Ark_Union_I32_String_SwiperAutoFill_ItemFillPolicy;

// Callback/Union - CustomBuilder_DragItemInfo renamed to CustomNodeBuilder_DragItemInfo
using Callback_Union_CustomBuilder_DragItemInfo_Void = Callback_Union_CustomNodeBuilder_DragItemInfo_Void;
using Ark_Union_CustomBuilder_DragItemInfo = Ark_Union_CustomNodeBuilder_DragItemInfo;

// Callback - Opt_CustomBuilder_Void renamed to Opt_CustomNodeBuilder_Void
using Callback_Opt_CustomBuilder_Void = Callback_Opt_CustomNodeBuilder_Void;
using Opt_Callback_Opt_CustomBuilder_Void = Opt_Callback_Opt_CustomNodeBuilder_Void;

// Union types - ResourceStr_CustomBuilder renamed to ResourceStr_CustomNodeBuilder
using Opt_Union_ResourceStr_CustomBuilder = Opt_Union_ResourceStr_CustomNodeBuilder;
using Ark_Union_ResourceStr_CustomBuilder = Ark_Union_ResourceStr_CustomNodeBuilder;

// Union types - Array_MenuElement_CustomBuilder renamed to Array_MenuElement_CustomNodeBuilder
using Opt_Union_Array_MenuElement_CustomBuilder = Opt_Union_Array_MenuElement_CustomNodeBuilder;
using Ark_Union_Array_MenuElement_CustomBuilder = Ark_Union_Array_MenuElement_CustomNodeBuilder;

// Union types - Length_Bindable with full variant suffix
using Opt_Union_Length_Bindable = Opt_Union_Length_Bindable_Length;
using Ark_Union_Length_Bindable = Ark_Union_Length_Bindable_Length;

// Union types - MenuPreviewMode_CustomBuilder renamed to MenuPreviewMode_CustomNodeBuilder
using Opt_Union_MenuPreviewMode_CustomBuilder = Opt_Union_MenuPreviewMode_CustomNodeBuilder;
using Ark_Union_MenuPreviewMode_CustomBuilder = Ark_Union_MenuPreviewMode_CustomNodeBuilder;

// Union types - MenuItemOptions_CustomBuilder renamed to MenuItemOptions_CustomNodeBuilder
using Opt_Union_MenuItemOptions_CustomBuilder = Opt_Union_MenuItemOptions_CustomNodeBuilder;
using Ark_Union_MenuItemOptions_CustomBuilder = Ark_Union_MenuItemOptions_CustomNodeBuilder;

// Union types - TabContent setTabBar (CustomBuilder -> CustomNodeBuilder in union name)
using Opt_Union_ComponentContentBase_SubTabBarStyle_BottomTabBarStyle_String_Resource_CustomBuilder_TabBarOptions =
    Opt_Union_ComponentContentBase_SubTabBarStyle_BottomTabBarStyle_String_Resource_CustomNodeBuilder_TabBarOptions;
using Ark_Union_ComponentContentBase_SubTabBarStyle_BottomTabBarStyle_String_Resource_CustomBuilder_TabBarOptions =
    Ark_Union_ComponentContentBase_SubTabBarStyle_BottomTabBarStyle_String_Resource_CustomNodeBuilder_TabBarOptions;

#endif // FOUNDATION_ARKUI_ACE_ENGINE_TEST_UNITTEST_CAPI_GEN140_COMPAT_H
