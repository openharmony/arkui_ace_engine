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

#include "image_common_methods_test.h"

#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {
using namespace Converter;
using namespace GeneratedModifier::ImageCommonMethods;

namespace ColorFilter {
namespace {
const std::vector<float> EMPTY_VECTOR = {};
std::vector<float> INVALID_MATRIX_LESS = {
    1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0
};
const std::vector<float> INVALID_MATRIX_MORE = {
    1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0
};
const std::vector<float> VALID_MATRIX = {
    1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0
};
const std::vector<float> VALID_MATRIX_0 = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
const std::vector<float> VALID_MATRIX_1 = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};

Converter::ConvContext s_ctx;
} // namespace

const std::vector<std::tuple<std::string, Array_F64, std::vector<float>>> floatMatrixTest = {
    { "EMPTY_VECTOR", ArkValue<Array_F64>(EMPTY_VECTOR, &s_ctx), DEFAULT_COLORFILTER_MATRIX },
    { "VALID_HOLDER_0", ArkValue<Array_F64>(VALID_MATRIX_0, &s_ctx), VALID_MATRIX_0 },
    { "INVALID_HOLDER_0", ArkValue<Array_F64>(INVALID_MATRIX_LESS, &s_ctx), DEFAULT_COLORFILTER_MATRIX },
    { "VALID_HOLDER_1", ArkValue<Array_F64>(VALID_MATRIX_1, &s_ctx), VALID_MATRIX_1 },
    { "INVALID_HOLDER_1", ArkValue<Array_F64>(INVALID_MATRIX_MORE, &s_ctx), DEFAULT_COLORFILTER_MATRIX },
    { "VALID_HOLDER_2", ArkValue<Array_F64>(VALID_MATRIX, &s_ctx), VALID_MATRIX }
};
} // namespace ColorFilter
} // namespace OHOS::Ace::NG
