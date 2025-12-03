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

#ifndef CAPI_UNIT_TEST_SHAPE_UTILS_H
#define CAPI_UNIT_TEST_SHAPE_UTILS_H

#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG::Converter {
inline void AssignArkValue(Ark_ShapePoint& dst, const std::pair<std::string, std::string>& src, ConvContext *ctx)
{
    dst.value0 = ArkUnion<Ark_Length, Ark_String>(std::get<0>(src), ctx);
    dst.value1 = ArkUnion<Ark_Length, Ark_String>(std::get<1>(src), ctx);
}
} // namespace OHOS::Ace::NG::Converter

#endif // CAPI_UNIT_TEST_SHAPE_UTILS_H
