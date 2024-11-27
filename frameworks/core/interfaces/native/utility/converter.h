/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef GENERATED_FOUNDATION_ACE_FRAMEWORKS_CORE_UTILITY_CONVERTER_H
#define GENERATED_FOUNDATION_ACE_FRAMEWORKS_CORE_UTILITY_CONVERTER_H

#pragma once

// SORTED_SECTION
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

// SORTED_SECTION
#include "base/geometry/axis.h"
#include "base/geometry/calc_dimension.h"
#include "base/geometry/dimension.h"
#include "bridge/common/utils/utils.h"
#include "core/animation/chain_animation.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/paint_state.h"
#include "core/components/common/properties/shadow.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/scroll/scroll_controller_base.h"
#include "core/components_ng/pattern/data_panel/data_panel_model_ng.h"
#include "core/components_ng/pattern/list/list_item_group_pattern.h"
#include "core/components_ng/pattern/menu/menu_layout_property.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/pattern/scrollable/scrollable_properties.h"
#include "core/components_ng/pattern/slider/slider_model.h"
#include "core/components_ng/pattern/tabs/tabs_model.h"
#include "core/components_ng/pattern/text_field/text_field_model.h"
#include "core/components_ng/property/border_property.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/gradient_property.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_v2/list/list_properties.h"
#include "core/image/image_source_info.h"

#include "ace_engine_types.h"
#include "core/interfaces/native/node/node_api.h"
#include "core/interfaces/native/utility/generated/converter_generated.h"
#include "converter_union.h"

namespace OHOS::Ace::NG {
std::optional<double> FloatToDouble(const std::optional<float>& src);
template<typename T>
std::optional<int32_t> EnumToInt(const std::optional<T>& src)
{
    return src ? std::optional(static_cast<int32_t>(src.value())) : std::nullopt;
}

using StringArray = std::vector<std::string>;

namespace Converter {
    constexpr double PERCENT_100 = 100.0;

    template<typename To, typename From>
    To Convert(const From& src);
    template<typename To, typename From>
    std::optional<To> OptConvert(const From& value);

     //Allow conversion for Ark_Xxx type to same Ark_Xxx type
    template<typename T>
    void AssignTo(T& dst, const T& src)
    {
        dst = src;
    }

    template<typename T, typename... Types>
    void AssignTo(std::variant<Types...>& dst, const T& src)
    {
        dst = src;
    }

    template<typename To, typename From, typename = decltype(From().array), typename = decltype(From().length)>
    void AssignTo(std::vector<To>& dst, const From& src)
    {
        dst.clear();
        dst.reserve(src.length);
        for (Ark_Int32 i = 0; i < src.length; i++) {
            dst.push_back(Convert<To>(src.array[i]));
        }
    }

    template<typename To, typename From, typename = decltype(From().array), typename = decltype(From().length)>
    void AssignTo(std::vector<std::optional<To>>& dst, const From& src)
    {
        dst.clear();
        dst.reserve(src.length);
        for (Ark_Int32 i = 0; i < src.length; i++) {
            dst.push_back(OptConvert<To>(src.array[i]));
        }
    }

    template<typename To, typename From>
    To Convert(const From& src)
    {
        To result;
        AssignTo(result, src);
        return result;
    }

    class ResourceConverter {
        public:
            ResourceConverter() = delete;
            ~ResourceConverter() = default;
            ResourceConverter(const ResourceConverter&) = delete;
            ResourceConverter& operator=(const ResourceConverter&) = delete;

            explicit ResourceConverter(const Ark_Resource& resource);

            std::optional<std::string> ToString();
            std::optional<StringArray> ToStringArray();
            std::optional<StringArray> ToFontFamilies();
            std::optional<Dimension> ToDimension();
            std::optional<CalcLength> ToCalcLength();
            std::optional<float> ToFloat();
            std::optional<int32_t> ToInt();
            std::optional<uint32_t> ToSymbol();
            std::optional<Color> ToColor();

            const std::string& BundleName() { return bundleName_; }
            const std::string& ModuleName() { return moduleName_; }

        private:
            RefPtr<ThemeConstants> themeConstants_;
            NodeModifier::ResourceType type_;
            std::string bundleName_;
            std::string moduleName_;
            int32_t id_;
            StringArray params_;
    };

    template<typename T, typename P>
    void AssignCast(std::optional<T>& dst, const P& src)
    {
        dst = Convert<T, P>(src);
    }

    template<typename T>
    void AssignCast(std::optional<T>& dst, const Ark_Undefined&)
    {
        dst = std::nullopt;
    }

    template<typename T, typename P>
    void AssignLiteralTo(std::optional<T>& dst, const P& src)
    {
        AssignCast(dst, src);
    }

    template<typename T, typename P>
    void AssignUnionTo(std::optional<T>& dst, const P& src)
    {
        AssignCast(dst, src);
    }

    template<typename T, typename P>
    void AssignOptionalTo(std::optional<T>& dst, const P& src)
    {
        AssignUnionTo(dst, src);
    }

    template<typename T, typename P>
    void AssignTo(std::optional<T>& dst, const P& src)
    {
        AssignOptionalTo(dst, src);
    }

    template<typename To, typename From>
    std::optional<To> OptConvert(const From& value)
    {
        std::optional<To> opt;
        AssignTo(opt, value);
        return std::move(opt);
    }

    template<typename To, typename From>
    To ConvertOrDefault(const From& value, To defaultValue)
    {
        return OptConvert<To, From>(value).value_or(defaultValue);
    }

    // Base converters
    template<>
    inline bool Convert(const Ark_Boolean& src)
    {
        return static_cast<bool>(src);
    }

    template<>
    inline std::string Convert(const Ark_String& src)
    {
        return (src.chars != nullptr) ? std::string(src.chars, src.length) : "";
    }

    template<>
    inline Ark_CharPtr Convert(const Ark_String& src)
    {
        return src.chars;
    }

    template<>
    inline int Convert(const Ark_Number& src)
    {
        return src.tag == ARK_TAG_FLOAT32 ? static_cast<int>(src.f32) : src.i32;
    }

    template<>
    inline float Convert(const Ark_Number& src)
    {
        return src.tag == ARK_TAG_FLOAT32 ? src.f32 : static_cast<float>(src.i32);
    }

    // Implementation is in cpp
    void AssignGradientColors(Gradient *gradient, const Array_Tuple_ResourceColor_Number *colors);
    void AssignLinearGradientDirection(std::shared_ptr<OHOS::Ace::NG::LinearGradient> linear,
        const GradientDirection &direction);

    template<>
    inline uint32_t Convert(const Ark_Number& src)
    {
        return src.tag == ARK_TAG_FLOAT32 ? static_cast<uint32_t>(src.f32) : static_cast<uint32_t>(src.i32);
    }

    template<>
    inline uint32_t Convert(const Array_Number& src)
    {
        return src.array ? Convert<uint32_t>(src.array[0]) : 0;
    }

    template<>
    inline std::vector<uint32_t> Convert(const Ark_Number& src)
    {
        return { Convert<uint32_t>(src) };
    }

    template<>
    inline ImageSourceInfo Convert(const Ark_String& value)
    {
        return ImageSourceInfo(value.chars);
    }

    template<>
    inline ImageSourceInfo Convert(const Ark_CustomObject& value)
    {
        LOGE("Convert [Ark_CustomObject] to [ImageSourceInfo] is not supported");
        return ImageSourceInfo();
    }

    template<>
    inline ImageSourceInfo Convert(const Ark_PixelMap& value)
    {
        LOGE("Convert [Ark_PixelMap] to [ImageSourceInfo] is not supported");
        return ImageSourceInfo();
    }

    template<>
    inline ImageSourceInfo Convert(const Ark_LinearGradient& value)
    {
        LOGE("Convert [Ark_LinearGradient] to [ImageSourceInfo] is not supported");
        return ImageSourceInfo();
    }

    template<>
    inline void AssignCast(std::optional<StringArray>& dst, const Ark_Resource& value)
    {
        ResourceConverter converter(value);
        dst = converter.ToStringArray();
    }

    template<>
    inline void AssignCast(std::optional<std::string>& dst, const Ark_Resource& value)
    {
        ResourceConverter converter(value);
        dst = converter.ToString();
    }

    template<>
    inline void AssignCast(std::optional<ImageSourceInfo>& dst, const Ark_Resource& value)
    {
        ResourceConverter converter(value);
        auto resourceString = converter.ToString();
        if (resourceString) {
            dst = ImageSourceInfo(resourceString.value(), converter.BundleName(), converter.ModuleName());
        } else {
            LOGE("Not a string resource: %{public}s:%{public}s\n", converter.BundleName().c_str(),
                converter.ModuleName().c_str());
        }
    }

    template<>
    inline void AssignCast(std::optional<Dimension>& dst, const Ark_Resource& src)
    {
        ResourceConverter converter(src);
        dst = converter.ToDimension();
    }

    template<>
    inline void AssignCast(std::optional<Color>& dst, const Ark_Resource& src)
    {
        ResourceConverter converter(src);
        dst = converter.ToColor();
    }

    template<>
    inline void AssignCast(std::optional<Dimension>& dst, const Ark_CustomObject& src)
    {
        LOGE("ARKOALA Converter Ark_CustomObject -> Dimension is not implemented.");
    }

    template<>
    inline void AssignCast(std::optional<Ark_CharPtr>& dst, const Ark_Resource& src)
    {
        LOGE("ARKOALA Converter -> Resource support (String) is not implemented.");
    }

    template<>
    inline void AssignCast(std::optional<Color>& dst, const Ark_ColoringStrategy& src)
    {
        LOGE("ARKOALA Converter Ark_ColoringStrategy -> Color is not implemented.");
    }

    template<>
    inline void AssignCast(std::optional<float>& dst, const Ark_Resource& src)
    {
        ResourceConverter converter(src);
        dst = converter.ToFloat();
    }

    template<>
    inline void AssignCast(std::optional<int32_t>& dst, const Ark_Resource& src)
    {
        ResourceConverter converter(src);
        dst = converter.ToInt();
    }

    template<>
    void AssignTo(std::optional<BorderColorProperty> &dst, const Ark_ResourceColor& src);

    // Converter declarations should be here, because they can be used in other converters!
    // SORTED_SECTION: Converter's specializations. No multiline declarations, please!
    template<> AnimateParam Convert(const Ark_AnimateParam& src);
    template<> BorderColorProperty Convert(const Ark_EdgeColors& src);
    template<> BorderRadiusProperty Convert(const Ark_BorderRadiuses& src);
    template<> BorderRadiusProperty Convert(const Ark_Length& src);
    template<> BorderStyleProperty Convert(const Ark_EdgeStyles& src);
    template<> BorderWidthProperty Convert(const Ark_EdgeWidths& src);
    template<> BorderWidthProperty Convert(const Ark_Length& src);
    template<> BorderWidthProperty Convert(const Ark_LengthMetrics& src);
    template<> CalcLength Convert(const Ark_Length& src);
    template<> CalcLength Convert(const Ark_LengthMetrics& src);
    template<> CaretStyle Convert(const Ark_CaretStyle& src);
    template<> Dimension Convert(const Ark_Length& src);
    template<> Dimension Convert(const Ark_LengthMetrics& src);
    template<> DimensionRect Convert(const Ark_Rectangle &src);
    template<> Font Convert(const Ark_Font& src);
    template<> FontFamilies Convert(const Ark_String& src);
    template<> Gradient Convert(const Ark_LinearGradient& value);
    template<> GradientColor Convert(const Ark_Tuple_ResourceColor_Number& value);
    template<> ItemDragInfo Convert(const Ark_ItemDragInfo& src);
    template<> LightSource Convert(const Ark_LightSource& src);
    template<> ListItemIndex Convert(const Ark_VisibleListContentInfo& src);
    template<> NestedScrollOptions Convert(const Ark_NestedScrollOptions& src);
    template<> PaddingProperty Convert(const Ark_LocalizedPadding& src);
    template<> PaddingProperty Convert(const Ark_Padding& src);
    template<> PickerSelectedType Convert(const Ark_Number& src);
    template<> PickerSelectedType Convert(const Array_Number& src);
    template<> PickerTextStyle Convert(const Ark_PickerTextStyle& src);
    template<> PickerValueType Convert(const Ark_String& src);
    template<> PickerValueType Convert(const Array_String& src);
    template<> PointLightStyle Convert(const Ark_PointLightStyle& src);
    template<> RefPtr<Curve> Convert(const Ark_Curve& src);
    template<> RefPtr<Curve> Convert(const Ark_ICurve& src);
    template<> RefPtr<Curve> Convert(const Ark_String& src);
    template<> RefPtr<FrameRateRange> Convert(const Ark_ExpectedFrameRateRange& src);
    template<> SelectionOptions Convert(const Ark_SelectionOptions& options);
    template<> Shadow Convert(const Ark_ShadowOptions& src);
    template<> TextBackgroundStyle Convert(const Ark_TextBackgroundStyle& src);
    template<> TextDecorationOptions Convert(const Ark_TextDecorationOptions& src);
    template<> bool Convert(const Ark_EdgeEffectOptions& src);
    template<> std::pair<Color, Dimension> Convert(const Ark_Tuple_ResourceColor_Number& src);
    template<> std::pair<Dimension, Dimension> Convert(const Ark_LengthConstrain& src);
    template<> std::pair<Dimension, Dimension> Convert(const Ark_Position& src);
    template<> std::vector<Shadow> Convert(const Ark_ShadowOptions& src);

    // NOT_SORTED_SECTION: Changing ordering can lead to build problem!
    template<> Dimension Convert(const Ark_String& src);
    template<> CalcDimension Convert(const Ark_Length& src);
    template<> CalcDimension Convert(const Ark_String& src);
    template<> CalcDimension Convert(const Ark_Number& src);
    template<> std::pair<Dimension, Dimension> Convert(const Ark_Tuple_Dimension_Dimension& src);
    template<> Dimension Convert(const Ark_Number& src);
    template<> int Convert(const Ark_IlluminatedType& src);
    template<> StringArray Convert(const Ark_CustomObject& src);
    template<> Color Convert(const Ark_Number& src);
    template<> Color Convert(const Ark_String& src);
    template<> CalcLength Convert(const Ark_Length& src);
    template<> std::tuple<Ark_Float32, Ark_Int32> Convert(const Ark_String& src);
    template<> Ark_CharPtr Convert(const Ark_Undefined& src);
    template<> Ark_CharPtr Convert(const Ark_Function& src);
    template<> Ark_CharPtr Convert(const Ark_CustomObject& src);
    template<> int Convert(const Ark_String& src);
    template<> float Convert(const Ark_String& src);
    template<> float Convert(const Ark_Float32& src);
    template<> Shadow Convert(const Ark_Int32& src);
    template<> EdgesParam Convert(const Ark_Edges& src);
    template<> PaddingProperty Convert(const Ark_Length& src);
    template<> RadioStyle Convert(const Ark_RadioStyle& src);
    template<> BorderRadiusProperty Convert(const Ark_LocalizedBorderRadiuses& src);
    template<> BorderStyleProperty Convert(const Ark_BorderStyle& src);
    template<> Dimension Convert(const Ark_CustomObject& src);
    template<> DimensionOffset Convert(const Ark_Offset& src);
    template<> FontMetaData Convert(const Ark_Font& src);
    template<> Ark_NativePointer Convert(const Ark_Materialized& src);
    template<> ShadowType Convert(const Ark_ShadowType& src);
    template<> ShadowColorStrategy Convert(const Ark_Color& src);
    template<> ShadowColorStrategy Convert(const Ark_String& src);
    template<> ShadowColorStrategy Convert(const Ark_Resource& src);

    // SORTED_SECTION: Non-enum specializations. No multiline declarations, please!
    template<> void AssignCast(std::optional<Color>& dst, const Ark_String& src);
    template<> void AssignCast(std::optional<FontFamilies>& dst, const Ark_Resource& value);
    template<> void AssignCast(std::optional<FontWeight>& dst, const Ark_Number& src);
    template<> void AssignCast(std::optional<FontWeight>& dst, const Ark_String& src);
    template<> void AssignCast(std::optional<Shadow>& dst, const Ark_ShadowStyle& src);
    template<> void AssignCast(std::optional<float>& dst, const Ark_String& src);

    // SORTED_SECTION: Enums specializations. No multiline declarations, please!
    template<> void AssignCast(std::optional<AdaptiveColor>& dst, const Ark_AdaptiveColor& src);
    template<> void AssignCast(std::optional<Alignment>& dst, const Ark_Alignment& src);
    template<> void AssignCast(std::optional<AnimationDirection>& dst, const Ark_PlayMode& src);
    template<> void AssignCast(std::optional<Axis>& dst, const Ark_Axis& src);
    template<> void AssignCast(std::optional<Axis>& dst, const Ark_ScrollDirection& src);
    template<> void AssignCast(std::optional<BarPosition>& dst, const Ark_BarPosition& src);
    template<> void AssignCast(std::optional<BlurStyle>& dst, const Ark_BlurStyle& src);
    template<> void AssignCast(std::optional<BorderImageRepeat>& dst, const Ark_RepeatMode& src);
    template<> void AssignCast(std::optional<BorderStyle>& dst, const Ark_BorderStyle& src);
    template<> void AssignCast(std::optional<ButtonRole>& dst, const Ark_ButtonRole& src);
    template<> void AssignCast(std::optional<ButtonStyleMode>& dst, const Ark_ButtonStyleMode& src);
    template<> void AssignCast(std::optional<ButtonType>& dst, const Ark_ButtonType& src);
    template<> void AssignCast(std::optional<CancelButtonStyle>& dst, const Ark_CancelButtonStyle& src);
    template<> void AssignCast(std::optional<ChainEdgeEffect>& dst, const Ark_ChainEdgeEffect& src);
    template<> void AssignCast(std::optional<ChainStyle>& dst, const Ark_ChainStyle& src);
    template<> void AssignCast(std::optional<CleanNodeStyle>& dst, const Ark_CancelButtonStyle& src);
    template<> void AssignCast(std::optional<Color>& dst, const enum Ark_Color& src);
    template<> void AssignCast(std::optional<ControlSize>& dst, const Ark_ControlSize& src);
    template<> void AssignCast(std::optional<CopyOptions>& dst, const Ark_CopyOptions& src);
    template<> void AssignCast(std::optional<DataPanelType>& dst, const Ark_DataPanelType& src);
    template<> void AssignCast(std::optional<DimensionUnit>& dst, const Ark_LengthUnit& src);
    template<> void AssignCast(std::optional<DisplayMode>& dst, const Ark_BarState& src);
    template<> void AssignCast(std::optional<DynamicRangeMode>& dst, const Ark_DynamicRangeMode& src);
    template<> void AssignCast(std::optional<EdgeEffect>& dst, const Ark_EdgeEffect& src);
    template<> void AssignCast(std::optional<EllipsisMode>& dst, const Ark_EllipsisMode& src);
    template<> void AssignCast(std::optional<FinishCallbackType>& dst, const Ark_FinishCallbackType& src);
    template<> void AssignCast(std::optional<FlexAlign>& dst, const Ark_FlexAlign& src);
    template<> void AssignCast(std::optional<FlexAlign>& dst, const Ark_HorizontalAlign& src);
    template<> void AssignCast(std::optional<FlexAlign>& dst, const Ark_ItemAlign& src);
    template<> void AssignCast(std::optional<FlexDirection>& dst, const Ark_FlexDirection& src);
    template<> void AssignCast(std::optional<FlexDirection>& dst, const Ark_GridDirection& src);
    template<> void AssignCast(std::optional<FontWeight>& dst, const Ark_FontWeight& src);
    template<> void AssignCast(std::optional<ForegroundColorStrategy>& dst, const Ark_ColoringStrategy& src);
    template<> void AssignCast(std::optional<GradientDirection>& dst, const Ark_GradientDirection& src);
    template<> void AssignCast(std::optional<HoverEffectType>& dst, const Ark_HoverEffect& src);
    template<> void AssignCast(std::optional<ImageFit>& dst, const Ark_ImageAnalyzerType& src);
    template<> void AssignCast(std::optional<ImageFit>& dst, const Ark_ImageFit& src);
    template<> void AssignCast(std::optional<ImageInterpolation>& dst, const Ark_ImageInterpolation& src);
    template<> void AssignCast(std::optional<ImageRenderMode>& dst, const Ark_ImageRenderMode& src);
    template<> void AssignCast(std::optional<ImageRepeat>& dst, const Ark_ImageRepeat& src);
    template<> void AssignCast(std::optional<InputStyle>& dst, const Ark_TextContentStyle& src);
    template<> void AssignCast(std::optional<InputStyle>& dst, const Ark_TextInputStyle& src);
    template<> void AssignCast(std::optional<LayoutStyle>& dst, const Ark_LayoutStyle& src);
    template<> void AssignCast(std::optional<LineBreakStrategy>& dst, const Ark_LineBreakStrategy& src);
    template<> void AssignCast(std::optional<LineCap>& dst, const Ark_LineCapStyle& src);
    template<> void AssignCast(std::optional<LineCapStyle>& dst, const Ark_LineCapStyle& src);
    template<> void AssignCast(std::optional<LineDirection>& dst, const Ark_Axis& src);
    template<> void AssignCast(std::optional<LineJoinStyle>& dst, const Ark_LineJoinStyle& src);
    template<> void AssignCast(std::optional<ListItemGroupArea>& dst, const Ark_ListItemGroupArea& src);
    template<> void AssignCast(std::optional<MenuPolicy>& dst, const Ark_MenuPolicy& src);
    template<> void AssignCast(std::optional<MessageLevel>& dst, const Ark_MessageLevel& src);
    template<> void AssignCast(std::optional<NavDestinationMode>& dst, const Ark_NavDestinationMode& src);
    template<> void AssignCast(std::optional<NavRouteMode>& dst, const Ark_NavRouteMode& src);
    template<> void AssignCast(std::optional<NestedScrollMode>& dst, const Ark_NestedScrollMode& src);
    template<> void AssignCast(std::optional<OHOS::Ace::FontStyle>& dst, const Ark_FontStyle& src);
    template<> void AssignCast(std::optional<OHOS::Ace::SymbolEffectType>& dst, const Ark_SymbolEffectStrategy& src);
    template<> void AssignCast(std::optional<PickerDate>& dst, const Ark_Date& src);
    template<> void AssignCast(std::optional<ScrollAlign>& dst, const Ark_ScrollAlign& src);
    template<> void AssignCast(std::optional<ScrollSnapAlign>& dst, const Ark_ScrollSnapAlign& src);
    template<> void AssignCast(std::optional<ScrollState>& dst, const Ark_ScrollState& src);
    template<> void AssignCast(std::optional<ShadowColorStrategy>& dst, const Ark_ColoringStrategy& src);
    template<> void AssignCast(std::optional<ShadowStyle>& dst, const Ark_ShadowStyle& src);
    template<> void AssignCast(std::optional<SliderModel::BlockStyleType>& dst, const Ark_SliderBlockType& src);
    template<> void AssignCast(std::optional<SliderModel::SliderChangeMode>& dst, const Ark_SliderChangeMode& src);
    template<> void AssignCast(std::optional<SliderModel::SliderInteraction>& dst, const Ark_SliderInteraction& src);
    template<> void AssignCast(std::optional<SliderModel::SliderMode>& dst, const Ark_SliderStyle& src);
    template<> void AssignCast(std::optional<SubMenuExpandingMode>& dst, const Ark_SubMenuExpandingMode& src);
    template<> void AssignCast(std::optional<SymbolData>& dst, const Ark_Resource& src);
    template<> void AssignCast(std::optional<TabAnimateMode>& dst, const Ark_AnimationMode& src);
    template<> void AssignCast(std::optional<TabBarMode>& dst, const Ark_BarMode& src);
    template<> void AssignCast(std::optional<TextAlign>& dst, const Ark_TextAlign& src);
    template<> void AssignCast(std::optional<TextCase>& dst, const Ark_TextCase& src);
    template<> void AssignCast(std::optional<TextContentType>& dst, const Ark_ContentType& src);
    template<> void AssignCast(std::optional<TextDecoration>& dst, const Ark_TextDecorationType& src);
    template<> void AssignCast(std::optional<TextDecorationStyle>& dst, const Ark_TextDecorationStyle& src);
    template<> void AssignCast(std::optional<TextDeleteDirection>& dst, const Ark_TextDeleteDirection& src);
    template<> void AssignCast(std::optional<TextDirection>& dst, const Ark_Direction& src);
    template<> void AssignCast(std::optional<TextHeightAdaptivePolicy>& dst, const Ark_TextHeightAdaptivePolicy& src);
    template<> void AssignCast(std::optional<TextInputAction>& dst, const Ark_EnterKeyType& src);
    template<> void AssignCast(std::optional<TextInputType>& dst, const Ark_InputType& src);
    template<> void AssignCast(std::optional<TextInputType>& dst, const Ark_SearchType& src);
    template<> void AssignCast(std::optional<TextInputType>& dst, const Ark_TextAreaType& src);
    template<> void AssignCast(std::optional<TextOverflow>& dst, const Ark_TextOverflow& src);
    template<> void AssignCast(std::optional<ThemeColorMode>& dst, const Ark_ThemeColorMode& src);
    template<> void AssignCast(std::optional<UserUnderlineColor>& dst, const Ark_UnderlineColor& src);
    template<> void AssignCast(std::optional<V2::EditMode>& dst, const Ark_EditMode& src);
    template<> void AssignCast(std::optional<V2::ListItemAlign>& dst, const Ark_ListItemAlign& src);
    template<> void AssignCast(std::optional<V2::ListItemGroupStyle>& dst, const Ark_ListItemGroupStyle& src);
    template<> void AssignCast(std::optional<V2::ListItemStyle>& dst, const Ark_ListItemStyle& src);
    template<> void AssignCast(std::optional<V2::ScrollSnapAlign>& dst, const Ark_ScrollSnapAlign& src);
    template<> void AssignCast(std::optional<V2::StickyMode>& dst, const Ark_Sticky& src);
    template<> void AssignCast(std::optional<V2::StickyStyle>& dst, const Ark_StickyStyle& src);
    template<> void AssignCast(std::optional<V2::SwipeEdgeEffect>& dst, const Ark_SwipeEdgeEffect& src);
    template<> void AssignCast(std::optional<FlexAlign>& dst, const Ark_VerticalAlign& src);
    template<> void AssignCast(std::optional<WordBreak>& dst, const Ark_WordBreak& src);

    template<>
    void AssignCast(std::optional<SharedTransitionEffectType>& dst, const Ark_SharedTransitionEffectType& src);
    template<>
    void AssignCast(std::optional<OHOS::Ace::RenderingStrategy>& dst, const Ark_SymbolRenderingStrategy& src);
} // namespace OHOS::Ace::NG::Converter
} // namespace OHOS::Ace::NG

#endif  // GENERATED_FOUNDATION_ACE_FRAMEWORKS_CORE_UTILITY_CONVERTER_H
