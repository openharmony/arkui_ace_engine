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
namespace FrameNodeAccessor {
void DestroyPeerImpl(Ark_FrameNode peer)
{
    auto peerImpl = reinterpret_cast<FrameNodePeerImpl *>(peer);
    if (peerImpl) {
        delete peerImpl;
    }
}
Ark_FrameNode ConstructImpl(Ark_UIContext uiContext)
{
    return {};
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Boolean IsModifiableImpl(Ark_FrameNode peer)
{
    return {};
}
void AppendChildImpl(Ark_FrameNode peer,
                     Ark_FrameNode node)
{
}
void InsertChildAfterImpl(Ark_FrameNode peer,
                          Ark_FrameNode child,
                          Ark_FrameNode sibling)
{
}
void RemoveChildImpl(Ark_FrameNode peer,
                     Ark_FrameNode node)
{
}
void ClearChildrenImpl(Ark_FrameNode peer)
{
}
Ark_FrameNode GetChildImpl(Ark_FrameNode peer,
                           const Ark_Number* index,
                           const Ark_Number* expandMode)
{
    return {};
}
Ark_FrameNode GetFirstChildImpl(Ark_FrameNode peer)
{
    return {};
}
Ark_FrameNode GetNextSiblingImpl(Ark_FrameNode peer)
{
    return {};
}
Ark_FrameNode GetPreviousSiblingImpl(Ark_FrameNode peer)
{
    return {};
}
Ark_FrameNode GetParentImpl(Ark_FrameNode peer)
{
    return {};
}
Ark_Int32 GetChildrenCountImpl(Ark_FrameNode peer)
{
    return {};
}
void DisposeImpl(Ark_FrameNode peer)
{
}
Ark_String GetIdImpl(Ark_FrameNode peer)
{
    return {};
}
Ark_Number GetUniqueIdImpl(Ark_FrameNode peer)
{
    return {};
}
Ark_String GetNodeTypeImpl(Ark_FrameNode peer)
{
    return {};
}
Ark_Number GetOpacityImpl(Ark_FrameNode peer)
{
    return {};
}
Ark_Boolean IsVisibleImpl(Ark_FrameNode peer)
{
    return {};
}
Ark_Boolean IsClipToFrameImpl(Ark_FrameNode peer)
{
    return {};
}
Ark_Boolean IsAttachedImpl(Ark_FrameNode peer)
{
    return {};
}
Ark_Object GetInspectorInfoImpl(Ark_FrameNode peer)
{
    return {};
}
void InvalidateImpl(Ark_FrameNode peer)
{
}
void DisposeTreeImpl(Ark_FrameNode peer)
{
}
void SetCrossLanguageOptionsImpl(Ark_FrameNode peer,
                                 const Ark_CrossLanguageOptions* options)
{
}
Ark_CrossLanguageOptions GetCrossLanguageOptionsImpl(Ark_FrameNode peer)
{
    return {};
}
void SetMeasuredSizeImpl(Ark_FrameNode peer,
                         const Ark_Size* size)
{
}
void SetLayoutPositionImpl(Ark_FrameNode peer,
                           const Ark_Position* position)
{
}
void MeasureImpl(Ark_FrameNode peer,
                 const Ark_LayoutConstraint* constraint)
{
}
void LayoutImpl(Ark_FrameNode peer,
                const Ark_Position* position)
{
}
void SetNeedsLayoutImpl(Ark_FrameNode peer)
{
}
Ark_Position GetPositionToWindowWithTransformImpl(Ark_FrameNode peer)
{
    return {};
}
Ark_FrameNode GetFrameNodeByKeyImpl(const Ark_String* name)
{
    return {};
}
Ark_Number GetIdByFrameNodeImpl(Ark_FrameNode peer,
                                Ark_FrameNode node)
{
    return {};
}
void MoveToImpl(Ark_FrameNode peer,
                Ark_FrameNode targetParent,
                const Ark_Number* index)
{
}
Ark_Number GetFirstChildIndexWithoutExpandImpl(Ark_FrameNode peer)
{
    return {};
}
Ark_Number GetLastChildIndexWithoutExpandImpl(Ark_FrameNode peer)
{
    return {};
}
Ark_FrameNode GetAttachedFrameNodeByIdImpl(const Ark_String* id)
{
    return {};
}
Ark_FrameNode GetFrameNodeByIdImpl(const Ark_Number* id)
{
    return {};
}
Ark_FrameNode GetFrameNodeByUniqueIdImpl(const Ark_Number* id)
{
    return {};
}
void ReuseImpl(Ark_FrameNode peer)
{
}
void RecycleImpl(Ark_FrameNode peer)
{
}
Ark_NativePointer GetFrameNodePtrImpl(Ark_FrameNode node)
{
    return {};
}
Ark_FrameNode CreateTypedFrameNodeImpl(const Ark_String* type)
{
    return {};
}
} // FrameNodeAccessor
const GENERATED_ArkUIFrameNodeAccessor* GetFrameNodeAccessor()
{
    static const GENERATED_ArkUIFrameNodeAccessor FrameNodeAccessorImpl {
        FrameNodeAccessor::DestroyPeerImpl,
        FrameNodeAccessor::ConstructImpl,
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
        FrameNodeAccessor::GetIdImpl,
        FrameNodeAccessor::GetUniqueIdImpl,
        FrameNodeAccessor::GetNodeTypeImpl,
        FrameNodeAccessor::GetOpacityImpl,
        FrameNodeAccessor::IsVisibleImpl,
        FrameNodeAccessor::IsClipToFrameImpl,
        FrameNodeAccessor::IsAttachedImpl,
        FrameNodeAccessor::GetInspectorInfoImpl,
        FrameNodeAccessor::InvalidateImpl,
        FrameNodeAccessor::DisposeTreeImpl,
        FrameNodeAccessor::SetCrossLanguageOptionsImpl,
        FrameNodeAccessor::GetCrossLanguageOptionsImpl,
        FrameNodeAccessor::SetMeasuredSizeImpl,
        FrameNodeAccessor::SetLayoutPositionImpl,
        FrameNodeAccessor::MeasureImpl,
        FrameNodeAccessor::LayoutImpl,
        FrameNodeAccessor::SetNeedsLayoutImpl,
        FrameNodeAccessor::GetPositionToWindowWithTransformImpl,
        FrameNodeAccessor::GetFrameNodeByKeyImpl,
        FrameNodeAccessor::GetIdByFrameNodeImpl,
        FrameNodeAccessor::MoveToImpl,
        FrameNodeAccessor::GetFirstChildIndexWithoutExpandImpl,
        FrameNodeAccessor::GetLastChildIndexWithoutExpandImpl,
        FrameNodeAccessor::GetAttachedFrameNodeByIdImpl,
        FrameNodeAccessor::GetFrameNodeByIdImpl,
        FrameNodeAccessor::GetFrameNodeByUniqueIdImpl,
        FrameNodeAccessor::ReuseImpl,
        FrameNodeAccessor::RecycleImpl,
        FrameNodeAccessor::GetFrameNodePtrImpl,
        FrameNodeAccessor::CreateTypedFrameNodeImpl,
    };
    return &FrameNodeAccessorImpl;
}

struct FrameNodePeer {
    virtual ~FrameNodePeer() = default;
};
}
