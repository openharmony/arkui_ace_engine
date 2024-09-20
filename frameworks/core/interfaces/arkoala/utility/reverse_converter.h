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

#include <iterator>
#include <string>
#include <string_view>
#include <type_traits>
#include <vector>

#include "base/geometry/dimension.h"
#include "core/components_ng/pattern/scrollable/scrollable_properties.h"
#include "core/gestures/drag_event.h"
#include "generated/converter_generated.h"
#include "frameworks/core/components_ng/pattern/text_field/text_field_event_hub.h"
#include "frameworks/core/common/ime/text_input_action.h"

namespace OHOS::Ace::NG::Converter {
    // Forward declaration for use in custom AssignArkValue() functions
    template<typename To, typename From = Ark_Empty>
    To ArkValue(From&& src = Ark_Empty());

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

    inline void AssignArkValue(Ark_PreviewText& dst, const PreviewText& src)
    {
        dst = {
            .offset = ArkValue<Ark_Number>(src.offset),
            .value = ArkValue<Ark_String>(src.value)
        };
    }

    inline void AssignArkValue(Ark_Int32& dst, const TextDeleteDirection& src)
    {
        dst = ArkValue<Ark_Int32>(static_cast<int32_t>(src));
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

    inline void AssignArkValue(Ark_NestedScrollMode& dst, const NestedScrollMode& src)
    {
        switch (src) {
            case NestedScrollMode::SELF_ONLY: dst = ARK_NESTED_SCROLL_MODE_SELF_ONLY; break;
            case NestedScrollMode::SELF_FIRST: dst = ARK_NESTED_SCROLL_MODE_SELF_FIRST; break;
            case NestedScrollMode::PARENT_FIRST: dst = ARK_NESTED_SCROLL_MODE_PARENT_FIRST; break;
            case NestedScrollMode::PARALLEL: dst = ARK_NESTED_SCROLL_MODE_PARALLEL; break;
            default: {
                dst = static_cast<Ark_NestedScrollMode>(-1);
                LOGE("Unexpected enum value in NestedScrollMode: %{public}d", src);
            }
        }
    }

    inline void AssignArkValue(Ark_NestedScrollOptions& dst, const NestedScrollOptions& src)
    {
        dst.scrollForward = ArkValue<Ark_NestedScrollMode>(src.forward);
        dst.scrollBackward = ArkValue<Ark_NestedScrollMode>(src.backward);
    }

    inline void AssignArkValue(Ark_EdgeEffectOptions& dst, const bool& src)
    {
        dst.alwaysEnabled = src;
    }

    inline void AssignArkValue(Ark_ScrollState& dst, const ScrollState& src)
    {
        switch (src) {
            case ScrollState::IDLE: dst = ARK_SCROLL_STATE_IDLE; break;
            case ScrollState::SCROLL: dst = ARK_SCROLL_STATE_SCROLL; break;
            case ScrollState::FLING: dst = ARK_SCROLL_STATE_FLING; break;
            default: {
                dst = static_cast<Ark_ScrollState>(-1);
                LOGE("Unexpected enum value in ScrollState: %{public}d", src);
            }
        }
    }

    void AssignArkValue(Ark_TextDeleteDirection& dst, const TextDeleteDirection& src);
    void AssignArkValue(Ark_EnterKeyType& dst, const TextInputAction& src);
    
    // ATTENTION!!! Add AssignArkValue implementations above this line!

    // Handle enum types
    template<typename T, std::enable_if_t<std::is_enum_v<T>, bool> = true>
    void AssignArkValue(Ark_Int32& dst, const T& src)
    {
        dst = static_cast<Ark_Int32>(src);
    }

    // Passthrough version
    template<typename T>
    void AssignArkValue(T &dst, const T& src)
    {
        dst = src;
    }

    // Handle optional types
    template<typename To, typename From, typename = std::void_t<decltype(To().tag), decltype(To().value)>>
    void AssignArkValue(To& dst, From&& src)
    {
        using ClearedFrom = std::remove_cv_t<std::remove_reference_t<From>>;
        if constexpr (std::is_same_v<ClearedFrom, Ark_Empty> || std::is_same_v<ClearedFrom, std::nullopt_t>) {
            dst.tag = ARK_TAG_UNDEFINED;
        } else {
            std::optional arg(std::forward<From>(src));
            if (arg.has_value()) {
                dst.tag = ARK_TAG_OBJECT;
                AssignArkValue(dst.value, arg.value());
            } else {
                dst.tag = ARK_TAG_UNDEFINED;
            }
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
    To ArkValue(From&& src)
    {
        To result;
        AssignArkValue(result, std::forward<From>(src));
        return result;
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
    template<typename T>
    class ArkArrayHolder {
        using Val = std::remove_pointer_t<decltype(T().array)>;
        std::vector<Val> data_;
    public:
        template<typename P>
        ArkArrayHolder(const std::vector<P>& data)
        {
            std::transform(data.begin(), data.end(), std::back_inserter(data_), [](const P& src) {
                return OHOS::Ace::NG::Converter::ArkValue<Val>(src);
            });
        }
        template<std::size_t N, typename P>
        ArkArrayHolder(const std::array<P, N>& data)
        {
            std::transform(data.begin(), data.end(), std::back_inserter(data_), [](const P& src) {
                return OHOS::Ace::NG::Converter::ArkValue<Val>(src);
            });
        }
        template<typename P>
        ArkArrayHolder(const P *data, std::size_t size)
        {
            std::transform(data, data + size, std::back_inserter(data_), [](const P& src) {
                return OHOS::Ace::NG::Converter::ArkValue<Val>(src);
            });
        }
        template<typename P>
        ArkArrayHolder(std::initializer_list<P> data)
        {
            std::transform(data.begin(), data.end(), std::back_inserter(data_), [](const P& src) {
                return OHOS::Ace::NG::Converter::ArkValue<Val>(src);
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
    To ArkUnion(From&& src)
    {
        return {
            .selector = SELECTOR_ID_0,
            .value0 = ArkValue<Which>(src),
        };
    }
    template<typename To, typename Which, typename From,
        std::enable_if_t<std::is_same_v<Which, decltype(To().value1)>, int> = SELECTOR_ID_1>
    To ArkUnion(From&& src)
    {
        return {
            .selector = SELECTOR_ID_1,
            .value1 = ArkValue<Which>(src),
        };
    }
    template<typename To, typename Which, typename From,
        std::enable_if_t<std::is_same_v<Which, decltype(To().value2)>, int> = SELECTOR_ID_2>
    To ArkUnion(From&& src)
    {
        return {
            .selector = SELECTOR_ID_2,
            .value2 = ArkValue<Which>(src),
        };
    }
    template<typename To, typename Which, typename From,
        std::enable_if_t<std::is_same_v<Which, decltype(To().value3)>, int> = SELECTOR_ID_3>
    To ArkUnion(From&& src)
    {
        return {
            .selector = SELECTOR_ID_3,
            .value3 = ArkValue<Which>(src),
        };
    }
    template<typename To, typename Which, typename From,
        std::enable_if_t<std::is_same_v<Which, decltype(To().value4)>, int> = SELECTOR_ID_4>
    To ArkUnion(From&& src)
    {
        return {
            .selector = SELECTOR_ID_4,
            .value4 = ArkValue<Which>(src),
        };
    }
    template<typename To, typename Which, typename From,
        std::enable_if_t<std::is_same_v<Which, decltype(To().value5)>, int> = SELECTOR_ID_5>
    To ArkUnion(From&& src)
    {
        return {
            .selector = SELECTOR_ID_5,
            .value5 = ArkValue<Which>(src),
        };
    }
    template<typename To, typename Which, typename From,
        std::enable_if_t<std::is_same_v<Which, decltype(To().value6)>, int> = SELECTOR_ID_6>
    To ArkUnion(From&& src)
    {
        return {
            .selector = SELECTOR_ID_6,
            .value6 = ArkValue<Which>(src),
        };
    }
    template<typename To, typename Which, typename From,
        std::enable_if_t<std::is_same_v<Which, decltype(To().value7)>, int> = SELECTOR_ID_7>
    To ArkUnion(From&& src)
    {
        return {
            .selector = SELECTOR_ID_7,
            .value7 = ArkValue<Which>(src),
        };
    }
    template<typename To, typename Which, typename From,
        std::enable_if_t<std::is_same_v<Which, decltype(To().value8)>, int> = SELECTOR_ID_8>
    To ArkUnion(From&& src)
    {
        return {
            .selector = SELECTOR_ID_8,
            .value8 = ArkValue<Which>(src),
        };
    }
    template<typename To, typename Which, typename From,
        std::enable_if_t<std::is_same_v<Which, decltype(To().value9)>, int> = SELECTOR_ID_9>
    To ArkUnion(From&& src)
    {
        return {
            .selector = SELECTOR_ID_9,
            .value9 = ArkValue<Which>(src),
        };
    }
    template<typename To, typename Which, typename From,
        std::enable_if_t<std::is_same_v<Which, decltype(To().value10)>, int> = SELECTOR_ID_10>
    To ArkUnion(From&& src)
    {
        return {
            .selector = SELECTOR_ID_10,
            .value10 = ArkValue<Which>(src),
        };
    }
    template<typename To, typename Which, typename From,
        std::enable_if_t<std::is_same_v<Which, decltype(To().value11)>, int> = SELECTOR_ID_11>
    To ArkUnion(From&& src)
    {
        return {
            .selector = SELECTOR_ID_11,
            .value11 = ArkValue<Which>(src),
        };
    }

    template<typename To, typename Which, typename From,
        std::enable_if_t<std::is_same_v<Ark_Tag, decltype(To().tag)>, bool> = true>
    To ArkUnion(From&& src)
    {
        return {
            .tag = ARK_TAG_OBJECT,
            .value = ArkUnion<decltype(To().value), Which>(std::forward<From>(src)),
        };
    }

    template<typename To, std::enable_if_t<std::is_same_v<Ark_Tag, decltype(To().tag)>, bool> = true>
    To ArkUnion(const Ark_Empty& src)
    {
        return {
            .tag = ARK_TAG_UNDEFINED,
        };
    }
} // namespace OHOS::Ace::NG::Converter

#endif  // FOUNDATION_ACE_FRAMEWORKS_CORE_UTILITY_REVERSE_CONVERTER_H
