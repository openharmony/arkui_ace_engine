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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_UTILITY_REVERSE_CONVERTER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_UTILITY_REVERSE_CONVERTER_H

#pragma once

// SORTED_SECTION
#include <iterator>
#include <string>
#include <string_view>
#include <type_traits>
#include <vector>

// SORTED_SECTION
#include "base/geometry/dimension.h"
#include "core/common/ime/text_input_action.h"
#include "core/components_ng/pattern/list/list_item_group_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_event_hub.h"
#include "core/components_ng/pattern/scroll/scroll_event_hub.h"
#include "core/components_ng/pattern/scrollable/scrollable_properties.h"
#include "core/components_ng/pattern/security_component/security_component_common.h"
#include "core/components_ng/pattern/slider/slider_model.h"
#include "core/components_ng/pattern/tabs/tabs_model.h"
#include "core/components_ng/pattern/text_field/text_field_event_hub.h"
#include "core/components_v2/list/list_properties.h"
#include "interfaces/inner_api/ace/ai/image_analyzer.h"

#include "core/gestures/drag_event.h"
#include "generated/converter_generated.h"

namespace OHOS::Ace::NG::Converter {
    constexpr int32_t NUM_0 = 0;
    constexpr int32_t NUM_1 = 1;
    constexpr int32_t NUM_2 = 2;
    constexpr int32_t NUM_3 = 3;
    constexpr int32_t NUM_4 = 4;

    // Forward declaration for use in custom AssignArkValue() functions
    template<typename To, typename From = Ark_Empty>
    To ArkValue(const From& src = Ark_Empty());
    template<typename To, typename From,
        std::enable_if_t<std::is_trivially_copyable_v<From> && std::is_rvalue_reference_v<From>, bool> = true>
    To ArkValue(From&& src)
    {
        return ArkValue<To>(src);
    }
    template<typename To, typename From,
        std::enable_if_t<!std::is_trivially_copyable_v<From> && std::is_rvalue_reference_v<From>, bool> = false>
    To ArkValue(From&& src) = delete; // Constructing Ark_ values from r-value is prohibited

    // Basic types
    inline void AssignArkValue(Ark_Boolean& dst, const bool& src)
    {
        dst = static_cast<Ark_Boolean>(src);
    }

    inline void AssignArkValue(Ark_String& dst, const std::string& src)
    {
        dst.chars = src.data();
        dst.length = src.size();
    }

    inline void AssignArkValue(Ark_String& dst, const std::string_view& src)
    {
        dst.chars = src.data();
        dst.length = src.size();
    }

    inline void AssignArkValue(Ark_String& dst, const char *src)
    {
        AssignArkValue(dst, std::string_view(src));
    }

    inline void AssignArkValue(Ark_Number& dst, const int32_t& src)
    {
        dst.tag = ARK_TAG_INT32;
        dst.i32 = src;
    }

    inline void AssignArkValue(Ark_Number& dst, const uint32_t& src)
    {
        dst.tag = ARK_TAG_INT32;
        dst.i32 = src;
    }

    inline void AssignArkValue(Ark_Number& dst, const float& src)
    {
        dst.tag = ARK_TAG_FLOAT32;
        dst.f32 = src;
    }

    inline void AssignArkValue(Ark_Number& dst, const double& src)
    {
        dst.tag = ARK_TAG_FLOAT32;
        dst.f32 = static_cast<float>(src);
    }

    inline void AssignArkValue(Ark_NativePointer& dst, void *src)
    {
        dst = src;
    }

    inline void AssignArkValue(Ark_Function& dst, const int& src)
    {
        dst.id = src;
    }

    // Complex types
    inline void AssignArkValue(Ark_PreviewText& dst, const PreviewText& src)
    {
        dst = {
            .offset = ArkValue<Ark_Number>(src.offset),
            .value = ArkValue<Ark_String>(src.value)
        };
    }

    inline void AssignArkValue(Ark_Length& dst, const int& src)
    {
        dst.type = ARK_TAG_INT32;
        dst.value = src;
        dst.unit = static_cast<int32_t>(OHOS::Ace::DimensionUnit::PX);
    }

    inline void AssignArkValue(Ark_Length& dst, const float& src)
    {
        dst.type = ARK_TAG_FLOAT32;
        dst.value = src;
        dst.unit = static_cast<int32_t>(OHOS::Ace::DimensionUnit::VP);
    }

    inline void AssignArkValue(Ark_Length& dst, const Dimension& src)
    {
        dst.type = ARK_TAG_FLOAT32;
        dst.value = src.Unit() == DimensionUnit::PERCENT ? src.Value() * 100.f : src.Value();
        dst.unit = static_cast<int32_t>(src.Unit());
    }

    inline void AssignArkValue(Ark_Length& dst, const std::string& src)
    {
        char *suffixPtr = nullptr;
        dst.type = ARK_TAG_FLOAT32;
        dst.value = std::strtof(src.c_str(), &suffixPtr);
        dst.unit = -NUM_1;
        if (!suffixPtr || suffixPtr == src.c_str()) { return; }
        if (suffixPtr[NUM_0] == '\0' || (suffixPtr[NUM_0] == 'v' && suffixPtr[NUM_1] == 'p')) { dst.unit = NUM_1; }
        else if (suffixPtr[NUM_0] == '%') { dst.unit = NUM_3; }
        else if (suffixPtr[NUM_0] == 'p' && suffixPtr[NUM_1] == 'x') { dst.unit = NUM_0; }
        else if (suffixPtr[NUM_0] == 'l' && suffixPtr[NUM_1] == 'p' && suffixPtr[NUM_2] == 'x') { dst.unit = NUM_4; }
        else if (suffixPtr[NUM_0] == 'f' && suffixPtr[NUM_1] == 'p') { dst.unit = NUM_2; }
    }

    inline void AssignArkValue(Ark_Number& dst, const Dimension& src)
    {
        auto value = static_cast<float>(src.ConvertToVp());
        AssignArkValue(dst, value);
    }

    inline void AssignArkValue(Ark_ItemDragInfo& dst, const ItemDragInfo& src)
    {
        dst.x = ArkValue<Ark_Number>(static_cast<float>(src.GetX()));
        dst.y = ArkValue<Ark_Number>(static_cast<float>(src.GetY()));
    }

    inline void AssignArkValue(Ark_VisibleListContentInfo& dst, const ListItemIndex& src)
    {
        dst.index = ArkValue<Ark_Number>(src.index);
        dst.itemGroupArea = src.area < 0 ?
            ArkValue<Opt_ListItemGroupArea>(Ark_Empty{}) : ArkValue<Opt_ListItemGroupArea>(src.area);
        dst.itemIndexInGroup = src.indexInGroup < 0 ?
            ArkValue<Opt_Number>(Ark_Empty{}) : ArkValue<Opt_Number>(src.indexInGroup);
    }

    inline void AssignArkValue(Ark_EdgeEffectOptions& dst, const bool& src)
    {
        dst.alwaysEnabled = src;
    }

    // SORTED_SECTION
    void AssignArkValue(Ark_AnimationMode& dst, const TabAnimateMode& src);
    void AssignArkValue(Ark_Axis& dst, const Axis& src);
    void AssignArkValue(Ark_BarMode& dst, const TabBarMode& src);
    void AssignArkValue(Ark_BarPosition& dst, const BarPosition& src);
    void AssignArkValue(Ark_BarState& dst, const DisplayMode& src);
    void AssignArkValue(Ark_BlurStyle& dst, const BlurStyle& src);
    void AssignArkValue(Ark_ClickEvent& dst, const OHOS::Ace::GestureEvent& src);
    void AssignArkValue(Ark_DecorationStyleResult& dst, const RichEditorAbstractSpanResult& src);
    void AssignArkValue(Ark_Edge& dst, const ScrollEdge& src);
    void AssignArkValue(Ark_EdgeEffect& dst, const EdgeEffect& src);
    void AssignArkValue(Ark_EnterKeyType& dst, const TextInputAction& src);
    void AssignArkValue(Ark_FoldStatus& dst, const FoldStatus& src);
    void AssignArkValue(Ark_FontStyle& dst, const OHOS::Ace::FontStyle& src);
    void AssignArkValue(Ark_ImageAnalyzerType& dst, const ImageAnalyzerType& src);
    void AssignArkValue(Ark_LayoutStyle& dst, const LayoutStyle& src);
    void AssignArkValue(Ark_ListItemAlign& dst, const V2::ListItemAlign& src);
    void AssignArkValue(Ark_ListItemGroupArea& dst, const ListItemGroupArea& src);
    void AssignArkValue(Ark_ListItemGroupStyle& dst, const V2::ListItemGroupStyle& src);
    void AssignArkValue(Ark_ListItemStyle& dst, const V2::ListItemStyle& src);
    void AssignArkValue(Ark_LocationButtonOnClickResult& dst, const SecurityComponentHandleResult& src);
    void AssignArkValue(Ark_MenuPolicy& dst, const MenuPolicy& src);
    void AssignArkValue(Ark_NavigationMode& dst, const NavigationMode& src);
    void AssignArkValue(Ark_NestedScrollMode& dst, const NestedScrollMode& src);
    void AssignArkValue(Ark_NestedScrollOptions& dst, const NestedScrollOptions& src);
    void AssignArkValue(Ark_PanelMode& dst, const PanelMode& src);
    void AssignArkValue(Ark_PasteButtonOnClickResult& dst, const SecurityComponentHandleResult& src);
    void AssignArkValue(Ark_Resource& dst, const Ark_Length& src);
    void AssignArkValue(Ark_Resource& dst, const ResourceObject& src);
    void AssignArkValue(Ark_ResourceColor& dst, const std::string& src);
    void AssignArkValue(Ark_RichEditorChangeValue& dst, const RichEditorChangeValue& src);
    void AssignArkValue(Ark_RichEditorDeleteDirection& dst, const RichEditorDeleteDirection& src);
    void AssignArkValue(Ark_RichEditorDeleteValue& dst, const RichEditorDeleteValue& src);
    void AssignArkValue(Ark_RichEditorInsertValue& dst, const RichEditorInsertValue& src);
    void AssignArkValue(Ark_RichEditorRange& dst, const BaseEventInfo& src);
    void AssignArkValue(Ark_RichEditorSelection& dst, const BaseEventInfo& src);
    void AssignArkValue(Ark_RichEditorSpanPosition& dst, const RichEditorAbstractSpanResult& src);
    void AssignArkValue(Ark_RichEditorSymbolSpanStyle& dst, const SymbolSpanStyle& src);
    void AssignArkValue(Ark_RichEditorTextSpanResult& dst, const RichEditorAbstractSpanResult& src);
    void AssignArkValue(Ark_RichEditorTextStyleResult& dst, const RichEditorAbstractSpanResult& src);
    void AssignArkValue(Ark_SaveButtonOnClickResult& dst, const SecurityComponentHandleResult& src);
    void AssignArkValue(Ark_ScrollSnapAlign& dst, const V2::ScrollSnapAlign& src);
    void AssignArkValue(Ark_ScrollState& dst, const ScrollState& src);
    void AssignArkValue(Ark_SharedTransitionEffectType& dst, const SharedTransitionEffectType& src);
    void AssignArkValue(Ark_SliderChangeMode& dst, const SliderModel::SliderChangeMode& src);
    void AssignArkValue(Ark_Sticky& dst, const V2::StickyMode& src);
    void AssignArkValue(Ark_StickyStyle& dst, const V2::StickyStyle& src);
    void AssignArkValue(Ark_String& dst, const FONT_FEATURES_LIST& src);
    void AssignArkValue(Ark_SubmitEvent& dst, const NG::TextFieldCommonEvent& src);
    void AssignArkValue(Ark_SwipeEdgeEffect& dst, const V2::SwipeEdgeEffect& src);
    void AssignArkValue(Ark_TextDecorationStyle& dst, const OHOS::Ace::TextDecorationStyle& src);
    void AssignArkValue(Ark_TextDecorationType& dst, const OHOS::Ace::TextDecoration& src);
    void AssignArkValue(Ark_TextDeleteDirection& dst, const TextDeleteDirection& src);
    void AssignArkValue(Ark_TextRange& dst, const TextRange& src);
    void AssignArkValue(Ark_TouchObject& dst, const OHOS::Ace::TouchLocationInfo& src);
    void AssignArkValue(Array_ImageAnalyzerType& dst, const std::vector<ImageAnalyzerType>& src);
    void AssignArkValue(Ark_ScrollAlign& dst, const ScrollAlign& src);
    void AssignArkValue(Array_Number& dst, const std::vector<double>& src);

    inline void AssignArkValue(Ark_ListItemGroupArea& dst, const int& src)
    {
        AssignArkValue(dst, static_cast<ListItemGroupArea>(src));
    }

    // ATTENTION!!! Add AssignArkValue implementations above this line!

    // Passthrough version
    template<typename T>
    void AssignArkValue(T &dst, const T& src)
    {
        dst = src;
    }

    // Handle optional types
    template<typename To, typename From, typename = std::void_t<decltype(To().tag), decltype(To().value)>>
    void AssignArkValue(To& dst, const From& src)
    {
        if constexpr (std::is_same_v<From, Ark_Empty> || std::is_same_v<From, std::nullopt_t>) {
            dst.tag = ARK_TAG_UNDEFINED;
        } else {
            dst.tag = ARK_TAG_OBJECT;
            AssignArkValue(dst.value, src);
        }
    }

    template<typename To, typename From, typename = std::void_t<decltype(To().tag), decltype(To().value)>>
    void AssignArkValue(To& dst, const std::optional<From>& src)
    {
        if (src.has_value()) {
            dst.tag = ARK_TAG_OBJECT;
            AssignArkValue(dst.value, src.value());
        } else {
            dst.tag = ARK_TAG_UNDEFINED;
        }
    }

    /**
     * Template function used to convert Ace Engine C++ types to C-API (Ark_...) types.
     * Automatically supports optional types, by passing std::optional or Ark_Empty value.
     *
     * Usage:
     *   Ark_Type dst = Converter::ArkValue<Ark_Type>(ace_engine_value);
     *
     * Examples:
     *  Ark_String stringResult = Converter::ArkValue<Ark_String>("abcd");
     *  Ark_Number numberResult = Converter::ArkValue<Ark_Number>(123);
     *
     *  Opt_Number optNumber = Converter::ArkValue<Opt_Number>(std::optional(123));
     *  Opt_Number emptyNumber = Converter::ArkValue<Opt_Number>(Ark_Empty());
     */
    template<typename To, typename From>
    To ArkValue(const From& src)
    {
        To result;
        AssignArkValue(result, src);
        return result;
    }

    // Handle Union types
    /**
     * Template function used to convert Ace Engine C++ types to C-API union (Union_...) types.
     * Automatically supports optional types, by passing value or Ark_Empty value.
     *
     * Usage:
     *      Union_Type result = Converter::ArkUnion<Union_Type, Which_Type>(ace_engine_value);
     * Where:
     *      Union_Type - type of resulting union (can be optional, Opt_Union_... type)
     *      Which_Type - type which will be assigned to union, should be one of possible types in Union_Type
     *
     * Examples:
     *  Union_Number_String unionResult = Converter::ArkUnion<Union_Number_String, Ark_Number>(123);
     *  Opt_Union_Number_String optUnionResult = Converter::ArkUnion<Opt_Union_Number_String, Ark_String>("abc");
     *  Opt_Union_Number_String emptyUnionResult = Converter::ArkUnion<Opt_Union_Number_String>(Ark_Empty());
     *
     */
    template<typename To, typename Which, typename From,
        std::enable_if_t<std::is_same_v<Which, decltype(To().value0)>, int> = SELECTOR_ID_0>
    To ArkUnion(const From& src)
    {
        return {
            .selector = SELECTOR_ID_0,
            .value0 = ArkValue<Which>(src),
        };
    }
    template<typename To, typename Which, typename From,
        std::enable_if_t<std::is_same_v<Which, decltype(To().value1)>, int> = SELECTOR_ID_1>
    To ArkUnion(const From& src)
    {
        return {
            .selector = SELECTOR_ID_1,
            .value1 = ArkValue<Which>(src),
        };
    }
    template<typename To, typename Which, typename From,
        std::enable_if_t<std::is_same_v<Which, decltype(To().value2)>, int> = SELECTOR_ID_2>
    To ArkUnion(const From& src)
    {
        return {
            .selector = SELECTOR_ID_2,
            .value2 = ArkValue<Which>(src),
        };
    }
    template<typename To, typename Which, typename From,
        std::enable_if_t<std::is_same_v<Which, decltype(To().value3)>, int> = SELECTOR_ID_3>
    To ArkUnion(const From& src)
    {
        return {
            .selector = SELECTOR_ID_3,
            .value3 = ArkValue<Which>(src),
        };
    }
    template<typename To, typename Which, typename From,
        std::enable_if_t<std::is_same_v<Which, decltype(To().value4)>, int> = SELECTOR_ID_4>
    To ArkUnion(const From& src)
    {
        return {
            .selector = SELECTOR_ID_4,
            .value4 = ArkValue<Which>(src),
        };
    }
    template<typename To, typename Which, typename From,
        std::enable_if_t<std::is_same_v<Which, decltype(To().value5)>, int> = SELECTOR_ID_5>
    To ArkUnion(const From& src)
    {
        return {
            .selector = SELECTOR_ID_5,
            .value5 = ArkValue<Which>(src),
        };
    }
    template<typename To, typename Which, typename From,
        std::enable_if_t<std::is_same_v<Which, decltype(To().value6)>, int> = SELECTOR_ID_6>
    To ArkUnion(const From& src)
    {
        return {
            .selector = SELECTOR_ID_6,
            .value6 = ArkValue<Which>(src),
        };
    }
    template<typename To, typename Which, typename From,
        std::enable_if_t<std::is_same_v<Which, decltype(To().value7)>, int> = SELECTOR_ID_7>
    To ArkUnion(const From& src)
    {
        return {
            .selector = SELECTOR_ID_7,
            .value7 = ArkValue<Which>(src),
        };
    }
    template<typename To, typename Which, typename From,
        std::enable_if_t<std::is_same_v<Which, decltype(To().value8)>, int> = SELECTOR_ID_8>
    To ArkUnion(const From& src)
    {
        return {
            .selector = SELECTOR_ID_8,
            .value8 = ArkValue<Which>(src),
        };
    }
    template<typename To, typename Which, typename From,
        std::enable_if_t<std::is_same_v<Which, decltype(To().value9)>, int> = SELECTOR_ID_9>
    To ArkUnion(const From& src)
    {
        return {
            .selector = SELECTOR_ID_9,
            .value9 = ArkValue<Which>(src),
        };
    }
    template<typename To, typename Which, typename From,
        std::enable_if_t<std::is_same_v<Which, decltype(To().value10)>, int> = SELECTOR_ID_10>
    To ArkUnion(const From& src)
    {
        return {
            .selector = SELECTOR_ID_10,
            .value10 = ArkValue<Which>(src),
        };
    }
    template<typename To, typename Which, typename From,
        std::enable_if_t<std::is_same_v<Which, decltype(To().value11)>, int> = SELECTOR_ID_11>
    To ArkUnion(const From& src)
    {
        return {
            .selector = SELECTOR_ID_11,
            .value11 = ArkValue<Which>(src),
        };
    }
    template<typename To, typename Which,
        std::enable_if_t<std::is_same_v<Which, Ark_Empty> && std::is_same_v<Ark_Int32, decltype(To().selector)>,
            int> = -1>
    To ArkUnion(const std::nullptr_t& src)
    {
        return {
            .selector = -1,
        };
    }

    template<typename To, typename Which, typename From,
        std::enable_if_t<std::is_same_v<Ark_Tag, decltype(To().tag)>, bool> = true>
    To ArkUnion(const From& src)
    {
        return {
            .tag = ARK_TAG_OBJECT,
            .value = ArkUnion<decltype(To().value), Which>(src),
        };
    }

    template<typename To, std::enable_if_t<std::is_same_v<Ark_Tag, decltype(To().tag)>, bool> = true>
    To ArkUnion(const Ark_Empty& src)
    {
        return {
            .tag = ARK_TAG_UNDEFINED,
        };
    }

    /**
     * Template class ArkArrayHolder should be used to prepare values of Array_... types.
     *
     * Arrays can be automatically converted from std::vector, std::array, C style array and initialization list.
     *
     * Examples:
     *  std::vector<std::string> vec{"abc", "1234"};
     *  Converter::ArkArrayHolder<Array_String> vecHolder(vec);
     *  Array_String stringArrayResult = vecHolder.ArkValue();
     *
     *  Converter::ArkArrayHolder<Array_String> listHolder({"def", "5678"});
     *  Array_String stringArrayResult = listHolder.ArkValue();
     *
     *  std::string_view svArray[] = {"ghi", "9012"};
     *  Converter::ArkArrayHolder<Array_String> cArrayHolder(svArray, 2);
     *  Array_String stringArrayResult = cArrayHolder.ArkValue();
     *
     *  auto asArray = std::array{Converter::ArkValue<Ark_String>("jkl"), Converter::ArkValue<Ark_String>("3456")};
     *  Converter::ArkArrayHolder<Array_String> arrayHolder1(asArray);
     *  Array_String stringArrayResult = arrayHolder1.ArkValue();
     *
     * ATTENTION!!! It is impossible to use temporary object of this type.
     * Always store data in variable while it is used!
     * Following is invalid and will not compile:
     *
     * Array_String stringArrayResult = Converter::ArkArrayHolder<Array_String>({"Error!"}).ArkValue()
     */
    template<typename T, typename U = void>
    class ArkArrayHolder {
        using Val = std::remove_pointer_t<decltype(T().array)>;
        std::vector<Val> data_;
    public:
        template<typename P>
        explicit ArkArrayHolder(const std::vector<P>& data)
        {
            std::transform(data.begin(), data.end(), std::back_inserter(data_), [](const P& src) {
                if constexpr (std::is_void_v<U>) {
                    return OHOS::Ace::NG::Converter::ArkValue<Val>(src);
                } else {
                    return OHOS::Ace::NG::Converter::ArkUnion<Val, U>(src);
                }
            });
        }
        template<std::size_t N, typename P>
        explicit ArkArrayHolder(const std::array<P, N>& data)
        {
            std::transform(data.begin(), data.end(), std::back_inserter(data_), [](const P& src) {
                if constexpr (std::is_void_v<U>) {
                    return OHOS::Ace::NG::Converter::ArkValue<Val>(src);
                } else {
                    return OHOS::Ace::NG::Converter::ArkUnion<Val, U>(src);
                }
            });
        }
        template<typename P>
        ArkArrayHolder(const P *data, std::size_t size)
        {
            std::transform(data, data + size, std::back_inserter(data_), [](const P& src) {
                if constexpr (std::is_void_v<U>) {
                    return OHOS::Ace::NG::Converter::ArkValue<Val>(src);
                } else {
                    return OHOS::Ace::NG::Converter::ArkUnion<Val, U>(src);
                }
            });
        }
        template<typename P>
        explicit ArkArrayHolder(std::initializer_list<P> data)
        {
            std::transform(data.begin(), data.end(), std::back_inserter(data_), [](const P& src) {
                if constexpr (std::is_void_v<U>) {
                    return OHOS::Ace::NG::Converter::ArkValue<Val>(src);
                } else {
                    return OHOS::Ace::NG::Converter::ArkUnion<Val, U>(src);
                }
            });
        }

        T ArkValue() &
        {
            return {
                .array = data_.data(),
                .length = data_.size(),
            };
        }

        void ArkValue() &&
        {
        }

        template<typename O>
        O OptValue() &
        {
            static_assert(std::is_same_v<T, decltype(O().value)>, "Opt_Array_XXX type should be same as Array_XXX");
            T value = {
                .array = data_.data(),
                .length = data_.size(),
            };
            return {
                .tag = ARK_TAG_OBJECT,
                .value = value,
            };
        }

        template<typename O>
        void OptValue() &&
        {
            static_assert(std::is_same_v<T, decltype(O().value)>, "Opt_Array_XXX type should be same as Array_XXX");
        }
    };

    // Create Ark_CallbackResource
    template <typename T, typename F,
        std::enable_if_t<std::is_same_v<decltype(T().resource), Ark_CallbackResource>, bool> = true
    >
    T ArkValue(F callbackFunc, Ark_Int32 resId = 0)
    {
        return T {
            .resource = {
                .resourceId = resId,
                .hold = nullptr,
                .release = nullptr
            },
            .call = callbackFunc
        };
    }
} // namespace OHOS::Ace::NG::Converter

#endif  // FOUNDATION_ACE_FRAMEWORKS_CORE_UTILITY_REVERSE_CONVERTER_H
