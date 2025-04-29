/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#pragma once

#include "core/interfaces/native/implementation/image_common_methods.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {
namespace GeneratedModifier {
    const GENERATED_ArkUIColorFilterAccessor* GetColorFilterAccessor();
} // namespace GeneratedModifier
namespace ColorFilter {
    using namespace Converter;
    using namespace GeneratedModifier::ImageCommonMethods;

    constexpr auto ATTRIBUTE_COLOR_FILTER_NAME = "colorFilter";
    constexpr auto ATTRIBUTE_COLOR_FILTER_DEFAULT_VALUE = "";

    inline const std::vector<float> EMPTY_VECTOR = {};
    inline std::vector<float> INVALID_MATRIX_LESS = {
        1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0
    };
    inline const std::vector<float> INVALID_MATRIX_MORE = {
        1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0
    };
    inline const std::vector<float> VALID_MATRIX = {
        1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0
    };
    inline const std::vector<float> VALID_MATRIX_0 = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };
    inline const std::vector<float> VALID_MATRIX_1 = {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
    };

    inline ArkArrayHolder<Array_Number> EMPTY_HOLDER(EMPTY_VECTOR);
    inline ArkArrayHolder<Array_Number> INVALID_HOLDER_0(INVALID_MATRIX_LESS);
    inline ArkArrayHolder<Array_Number> INVALID_HOLDER_1(INVALID_MATRIX_MORE);
    inline ArkArrayHolder<Array_Number> VALID_HOLDER_0(VALID_MATRIX_0);
    inline ArkArrayHolder<Array_Number> VALID_HOLDER_1(VALID_MATRIX_1);
    inline ArkArrayHolder<Array_Number> VALID_HOLDER_2(VALID_MATRIX);

    const std::vector<std::tuple<std::string, Array_Number, std::vector<float>>> floatMatrixTest {
        { "EMPTY_VECTOR", ArkValue<Array_Number>(EMPTY_HOLDER.ArkValue()), DEFAULT_COLORFILTER_MATRIX },
        { "VALID_HOLDER_0", ArkValue<Array_Number>(VALID_HOLDER_0.ArkValue()), VALID_MATRIX_0 },
        { "INVALID_HOLDER_0", ArkValue<Array_Number>(INVALID_HOLDER_0.ArkValue()), DEFAULT_COLORFILTER_MATRIX },
        { "VALID_HOLDER_1", ArkValue<Array_Number>(VALID_HOLDER_1.ArkValue()), VALID_MATRIX_1 },
        { "INVALID_HOLDER_1", ArkValue<Array_Number>(INVALID_HOLDER_1.ArkValue()), DEFAULT_COLORFILTER_MATRIX },
        { "VALID_HOLDER_2", ArkValue<Array_Number>(VALID_HOLDER_2.ArkValue()), VALID_MATRIX }
    };
} // namespace ColorFilter
} // namespace OHOS::Ace::NG