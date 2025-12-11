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

#ifndef FOUNDATION_ARKUI_ACE_ENGINE_TEST_UNITTEST_CAPI_MODIFIERS_SWIPER_MODIFIER_TEST_H
#define FOUNDATION_ARKUI_ACE_ENGINE_TEST_UNITTEST_CAPI_MODIFIERS_SWIPER_MODIFIER_TEST_H

#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::Converter {
inline void AssignArkValue(Ark_CustomObject& dst, const float& src)
{
    *dst.floats = src;
}

inline void AssignArkValue(Ark_CustomObject& dst, const int& src)
{
    *dst.ints = src;
}

inline void AssignArkValue(Ark_SwiperAutoFill& dst, const Ark_VP& src)
{
    dst.minSize = src;
}

inline void AssignArkValue(Ark_Materialized &dst, const Ark_NativePointer &src)
{
    dst.ptr = src;
}
} // namespace OHOS::Ace::NG::Converter

#endif
