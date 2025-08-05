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

#include "ani_animatable_arithmetic.h"

namespace OHOS::Ace::NG {
ArkUIAniArithmeticAddFunction AniAnimatableArithmetic::ADD_FUNC = nullptr;
ArkUIAniArithmeticMinusFunction AniAnimatableArithmetic::MINUS_FUNC = nullptr;
ArkUIAniArithmeticMultiplyFunction AniAnimatableArithmetic::MULTIPLY_FUNC = nullptr;
ArkUIAniArithmeticEqualFunction AniAnimatableArithmetic::EQUAL_FUNC = nullptr;
ArkUIAniCreateObjectFunction AniAnimatableArithmetic::CREATE_GLOBAL_REFERENCE_FUNC = nullptr;
ArkUIAniDeleteObjectFunction AniAnimatableArithmetic::DELETE_GLOBAL_REFERENCE_FUNC = nullptr;
bool AniAnimatableArithmetic::initialized_ = false;
} // namespace OHOS::Ace::NG
