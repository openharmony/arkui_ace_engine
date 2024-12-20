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
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

struct FrameNodePeer {
    explicit FrameNodePeer(const Ark_UIContext* uiContext) {}
    virtual ~FrameNodePeer() = default;
};

namespace OHOS::Ace::NG::GeneratedModifier {
namespace FrameNodeAccessor {
void DestroyPeerImpl(FrameNodePeer* peer)
{
    delete peer;
}
Ark_NativePointer CtorImpl(const Ark_UIContext* uiContext)
{
    return new FrameNodePeer(uiContext);
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Boolean IsModifiableImpl(FrameNodePeer* peer)
{
    return 0;
}
void AppendChildImpl(FrameNodePeer* peer,
                     const Ark_FrameNode* node)
{
}
void InsertChildAfterImpl(FrameNodePeer* peer,
                          const Ark_FrameNode* child,
                          const Ark_FrameNode* sibling)
{
}
void RemoveChildImpl(FrameNodePeer* peer,
                     const Ark_FrameNode* node)
{
}
void ClearChildrenImpl(FrameNodePeer* peer)
{
}
Ark_NativePointer GetChildImpl(FrameNodePeer* peer,
                               const Ark_Number* index)
{
    return nullptr;
}
Ark_NativePointer GetFirstChildImpl(FrameNodePeer* peer)
{
    return nullptr;
}
Ark_NativePointer GetNextSiblingImpl(FrameNodePeer* peer)
{
    return nullptr;
}
Ark_NativePointer GetPreviousSiblingImpl(FrameNodePeer* peer)
{
    return nullptr;
}
Ark_NativePointer GetParentImpl(FrameNodePeer* peer)
{
    return nullptr;
}
Ark_Int32 GetChildrenCountImpl(FrameNodePeer* peer)
{
    return 0;
}
void DisposeImpl(FrameNodePeer* peer)
{
}
} // FrameNodeAccessor
const GENERATED_ArkUIFrameNodeAccessor* GetFrameNodeAccessor()
{
    static const GENERATED_ArkUIFrameNodeAccessor FrameNodeAccessorImpl {
        FrameNodeAccessor::DestroyPeerImpl,
        FrameNodeAccessor::CtorImpl,
        FrameNodeAccessor::GetFinalizerImpl,
        FrameNodeAccessor::IsModifiableImpl,
        FrameNodeAccessor::AppendChildImpl,
        FrameNodeAccessor::InsertChildAfterImpl,
        FrameNodeAccessor::RemoveChildImpl,
        FrameNodeAccessor::ClearChildrenImpl,
        FrameNodeAccessor::GetChildImpl,
        FrameNodeAccessor::GetFirstChildImpl,
        FrameNodeAccessor::GetNextSiblingImpl,
        FrameNodeAccessor::GetPreviousSiblingImpl,
        FrameNodeAccessor::GetParentImpl,
        FrameNodeAccessor::GetChildrenCountImpl,
        FrameNodeAccessor::DisposeImpl,
    };
    return &FrameNodeAccessorImpl;
}

}
