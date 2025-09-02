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
namespace LayoutPolicyAccessor {
void DestroyPeerImpl(Ark_LayoutPolicy peer)
{
}
Ark_LayoutPolicy ConstructImpl()
{
    return {};
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_LayoutPolicy GetMatchParentImpl()
{
    return {};
}
} // LayoutPolicyAccessor
const GENERATED_ArkUILayoutPolicyAccessor* GetLayoutPolicyAccessor()
{
    static const GENERATED_ArkUILayoutPolicyAccessor LayoutPolicyAccessorImpl {
        LayoutPolicyAccessor::DestroyPeerImpl,
        LayoutPolicyAccessor::ConstructImpl,
        LayoutPolicyAccessor::GetFinalizerImpl,
        LayoutPolicyAccessor::GetMatchParentImpl,
    };
    return &LayoutPolicyAccessorImpl;
}

}
