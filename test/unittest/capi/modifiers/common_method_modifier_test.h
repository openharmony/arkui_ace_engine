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

#ifndef FOUNDATION_ARKUI_ACE_ENGINE_TEST_UNITTEST_CAPI_MODIFIERS_COMMON_METHOD_MODIFIER_TEST_H
#define FOUNDATION_ARKUI_ACE_ENGINE_TEST_UNITTEST_CAPI_MODIFIERS_COMMON_METHOD_MODIFIER_TEST_H

#include <utility>

#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG::Converter {
using ColorStep = std::pair<Ark_ResourceColor, double>;
inline void AssignArkValue(Ark_Tuple_ResourceColor_F64& dst, const ColorStep& src, ConvContext *ctx)
{
    dst.value0 = src.first;
    dst.value1 = ArkValue<Ark_Float64>(src.second);
}
} // namespace OHOS::Ace::NG::Converter

#endif
