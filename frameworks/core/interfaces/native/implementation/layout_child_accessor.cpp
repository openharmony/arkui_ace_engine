/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace LayoutChildAccessor {
void DestroyPeerImpl(Ark_LayoutChild peer)
{
}
Ark_LayoutChild ConstructImpl()
{
    return {};
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void MeasureImpl(Ark_LayoutChild peer,
                 const Ark_ConstraintSizeOptions* childConstraint)
{
}
Ark_String GetNameImpl(Ark_LayoutChild peer)
{
    return {};
}
void SetNameImpl(Ark_LayoutChild peer,
                 const Ark_String* name)
{
}
Ark_String GetIdImpl(Ark_LayoutChild peer)
{
    return {};
}
void SetIdImpl(Ark_LayoutChild peer,
               const Ark_String* id)
{
}
Ark_Position GetPositionImpl(Ark_LayoutChild peer)
{
    return {};
}
void SetPositionImpl(Ark_LayoutChild peer,
                     const Ark_Position* position)
{
}
} // LayoutChildAccessor
const GENERATED_ArkUILayoutChildAccessor* GetLayoutChildAccessor()
{
    static const GENERATED_ArkUILayoutChildAccessor LayoutChildAccessorImpl {
        LayoutChildAccessor::DestroyPeerImpl,
        LayoutChildAccessor::ConstructImpl,
        LayoutChildAccessor::GetFinalizerImpl,
        LayoutChildAccessor::MeasureImpl,
        LayoutChildAccessor::GetNameImpl,
        LayoutChildAccessor::SetNameImpl,
        LayoutChildAccessor::GetIdImpl,
        LayoutChildAccessor::SetIdImpl,
        LayoutChildAccessor::GetPositionImpl,
        LayoutChildAccessor::SetPositionImpl,
    };
    return &LayoutChildAccessorImpl;
}

}
