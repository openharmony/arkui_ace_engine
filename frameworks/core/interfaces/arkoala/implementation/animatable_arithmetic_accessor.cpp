/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace AnimatableArithmeticAccessor {
AnimatableArithmeticPeer* CtorImpl()
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return 0;
}
Ark_NativePointer PlusImpl(AnimatableArithmeticPeer* peer,
                           const Ark_Materialized* rhs)
{
    return 0;
}
Ark_NativePointer SubtractImpl(AnimatableArithmeticPeer* peer,
                               const Ark_Materialized* rhs)
{
    return 0;
}
Ark_NativePointer MultiplyImpl(AnimatableArithmeticPeer* peer,
                               const Ark_Number* scale)
{
    return 0;
}
Ark_Boolean EqualsImpl(AnimatableArithmeticPeer* peer,
                       const Ark_Materialized* rhs)
{
    return 0;
}
} // AnimatableArithmeticAccessor
const GENERATED_ArkUIAnimatableArithmeticAccessor* GetAnimatableArithmeticAccessor()
{
    static const GENERATED_ArkUIAnimatableArithmeticAccessor AnimatableArithmeticAccessorImpl {
        AnimatableArithmeticAccessor::CtorImpl,
        AnimatableArithmeticAccessor::GetFinalizerImpl,
        AnimatableArithmeticAccessor::PlusImpl,
        AnimatableArithmeticAccessor::SubtractImpl,
        AnimatableArithmeticAccessor::MultiplyImpl,
        AnimatableArithmeticAccessor::EqualsImpl,
    };
    return &AnimatableArithmeticAccessorImpl;
}

}
