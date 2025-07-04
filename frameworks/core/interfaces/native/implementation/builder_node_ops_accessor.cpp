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
namespace BuilderNodeOpsAccessor {
void DestroyPeerImpl(Ark_BuilderNodeOps peer)
{
}
Ark_BuilderNodeOps ConstructImpl()
{
    return {};
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void CreateImpl(Ark_BuilderNodeOps peer,
                const Callback_Void* buildFunc)
{
}
void DisposeNodeImpl(Ark_BuilderNodeOps peer)
{
}
void SetUpdateConfigurationCallbackImpl(Ark_BuilderNodeOps peer,
                                        const Callback_Void* configurationUpdateFunc)
{
}
void SetOptionsImpl(Ark_BuilderNodeOps peer,
                    const Ark_BuilderNodeOptions* options)
{
}
Ark_Boolean PostTouchEventImpl(Ark_BuilderNodeOps peer,
                               Ark_TouchEvent event)
{
    return {};
}
Ark_NativePointer SetRootFrameNodeInBuilderNodeImpl(Ark_BuilderNodeOps peer,
                                                    Ark_NativePointer node)
{
    return {};
}
} // BuilderNodeOpsAccessor
const GENERATED_ArkUIBuilderNodeOpsAccessor* GetBuilderNodeOpsAccessor()
{
    static const GENERATED_ArkUIBuilderNodeOpsAccessor BuilderNodeOpsAccessorImpl {
        BuilderNodeOpsAccessor::DestroyPeerImpl,
        BuilderNodeOpsAccessor::ConstructImpl,
        BuilderNodeOpsAccessor::GetFinalizerImpl,
        BuilderNodeOpsAccessor::CreateImpl,
        BuilderNodeOpsAccessor::DisposeNodeImpl,
        BuilderNodeOpsAccessor::SetUpdateConfigurationCallbackImpl,
        BuilderNodeOpsAccessor::SetOptionsImpl,
        BuilderNodeOpsAccessor::PostTouchEventImpl,
        BuilderNodeOpsAccessor::SetRootFrameNodeInBuilderNodeImpl,
    };
    return &BuilderNodeOpsAccessorImpl;
}

}
