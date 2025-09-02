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
namespace FrameNodeExtenderAccessor {
void DestroyPeerImpl(Ark_FrameNodeExtender peer)
{
}
Ark_FrameNodeExtender ConstructImpl()
{
    return {};
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Boolean IsModifiableImpl(Ark_FrameNodeExtender peer)
{
    return {};
}
void AppendChildImpl(Ark_FrameNodeExtender peer,
                     Ark_FrameNode node)
{
}
void InsertChildAfterImpl(Ark_FrameNodeExtender peer,
                          Ark_FrameNode child,
                          Ark_FrameNode sibling)
{
}
void RemoveChildImpl(Ark_FrameNodeExtender peer,
                     Ark_FrameNode node)
{
}
void ClearChildrenImpl(Ark_FrameNodeExtender peer)
{
}
Ark_FrameNode GetChildImpl(Ark_FrameNodeExtender peer,
                           const Ark_Number* index,
                           const Ark_Number* expandMode)
{
    return {};
}
Ark_FrameNode GetFirstChildImpl(Ark_FrameNodeExtender peer)
{
    return {};
}
Ark_FrameNode GetNextSiblingImpl(Ark_FrameNodeExtender peer)
{
    return {};
}
Ark_FrameNode GetPreviousSiblingImpl(Ark_FrameNodeExtender peer)
{
    return {};
}
Ark_FrameNode GetParentImpl(Ark_FrameNodeExtender peer)
{
    return {};
}
Ark_Int32 GetChildrenCountImpl(Ark_FrameNodeExtender peer)
{
    return {};
}
void DisposeImpl(Ark_FrameNodeExtender peer)
{
}
Ark_Position GetPositionToWindowImpl(Ark_FrameNodeExtender peer)
{
    return {};
}
Ark_Position GetPositionToParentImpl(Ark_FrameNodeExtender peer)
{
    return {};
}
Ark_Size GetMeasuredSizeImpl(Ark_FrameNodeExtender peer)
{
    return {};
}
Ark_Position GetLayoutPositionImpl(Ark_FrameNodeExtender peer)
{
    return {};
}
Ark_String GetIdImpl(Ark_FrameNodeExtender peer)
{
    return {};
}
Ark_Number GetUniqueIdImpl(Ark_FrameNodeExtender peer)
{
    return {};
}
Ark_String GetNodeTypeImpl(Ark_FrameNodeExtender peer)
{
    return {};
}
Ark_Number GetOpacityImpl(Ark_FrameNodeExtender peer)
{
    return {};
}
Ark_Boolean IsVisibleImpl(Ark_FrameNodeExtender peer)
{
    return {};
}
Ark_Boolean IsClipToFrameImpl(Ark_FrameNodeExtender peer)
{
    return {};
}
Ark_Boolean IsAttachedImpl(Ark_FrameNodeExtender peer)
{
    return {};
}
Ark_Object GetInspectorInfoImpl(Ark_FrameNodeExtender peer)
{
    return {};
}
void InvalidateImpl(Ark_FrameNodeExtender peer)
{
}
void DisposeTreeImpl(Ark_FrameNodeExtender peer)
{
}
void SetCrossLanguageOptionsImpl(Ark_FrameNodeExtender peer,
                                 const Ark_CrossLanguageOptions* options)
{
}
Ark_CrossLanguageOptions GetCrossLanguageOptionsImpl(Ark_FrameNodeExtender peer)
{
    return {};
}
void SetMeasuredSizeImpl(Ark_FrameNodeExtender peer,
                         const Ark_Size* size)
{
}
void SetLayoutPositionImpl(Ark_FrameNodeExtender peer,
                           const Ark_Position* position)
{
}
void MeasureImpl(Ark_FrameNodeExtender peer,
                 const Ark_LayoutConstraint* constraint)
{
}
void LayoutImpl(Ark_FrameNodeExtender peer,
                const Ark_Position* position)
{
}
void SetNeedsLayoutImpl(Ark_FrameNodeExtender peer)
{
}
Ark_Position GetPositionToScreenImpl(Ark_FrameNodeExtender peer)
{
    return {};
}
Ark_Position GetPositionToWindowWithTransformImpl(Ark_FrameNodeExtender peer)
{
    return {};
}
Ark_Position GetPositionToParentWithTransformImpl(Ark_FrameNodeExtender peer)
{
    return {};
}
Ark_Position GetPositionToScreenWithTransformImpl(Ark_FrameNodeExtender peer)
{
    return {};
}
Ark_FrameNode GetFrameNodeByKeyImpl(const Ark_String* name)
{
    return {};
}
Ark_Number GetIdByFrameNodeImpl(Ark_FrameNodeExtender peer,
                                Ark_FrameNode node)
{
    return {};
}
void MoveToImpl(Ark_FrameNodeExtender peer,
                Ark_FrameNode targetParent,
                const Ark_Number* index)
{
}
Ark_Number GetFirstChildIndexWithoutExpandImpl(Ark_FrameNodeExtender peer)
{
    return {};
}
Ark_Number GetLastChildIndexWithoutExpandImpl(Ark_FrameNodeExtender peer)
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
void ReuseImpl(Ark_FrameNodeExtender peer)
{
}
void RecycleImpl(Ark_FrameNodeExtender peer)
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
Ark_NativePointer CreateByRawPtrImpl(Ark_FrameNodeExtender peer,
                                     Ark_FrameNode pointer)
{
    return {};
}
Ark_FrameNode UnWrapRawPtrImpl(Ark_FrameNodeExtender peer,
                               Ark_NativePointer pointer)
{
    return {};
}
Ark_NativePointer GetCommonEventImpl(Ark_FrameNodeExtender peer)
{
    return {};
}
} // FrameNodeExtenderAccessor
const GENERATED_ArkUIFrameNodeExtenderAccessor* GetFrameNodeExtenderAccessor()
{
    static const GENERATED_ArkUIFrameNodeExtenderAccessor FrameNodeExtenderAccessorImpl {
        FrameNodeExtenderAccessor::DestroyPeerImpl,
        FrameNodeExtenderAccessor::ConstructImpl,
        FrameNodeExtenderAccessor::GetFinalizerImpl,
        FrameNodeExtenderAccessor::IsModifiableImpl,
        FrameNodeExtenderAccessor::AppendChildImpl,
        FrameNodeExtenderAccessor::InsertChildAfterImpl,
        FrameNodeExtenderAccessor::RemoveChildImpl,
        FrameNodeExtenderAccessor::ClearChildrenImpl,
        FrameNodeExtenderAccessor::GetChildImpl,
        FrameNodeExtenderAccessor::GetFirstChildImpl,
        FrameNodeExtenderAccessor::GetNextSiblingImpl,
        FrameNodeExtenderAccessor::GetPreviousSiblingImpl,
        FrameNodeExtenderAccessor::GetParentImpl,
        FrameNodeExtenderAccessor::GetChildrenCountImpl,
        FrameNodeExtenderAccessor::DisposeImpl,
        FrameNodeExtenderAccessor::GetPositionToWindowImpl,
        FrameNodeExtenderAccessor::GetPositionToParentImpl,
        FrameNodeExtenderAccessor::GetMeasuredSizeImpl,
        FrameNodeExtenderAccessor::GetLayoutPositionImpl,
        FrameNodeExtenderAccessor::GetIdImpl,
        FrameNodeExtenderAccessor::GetUniqueIdImpl,
        FrameNodeExtenderAccessor::GetNodeTypeImpl,
        FrameNodeExtenderAccessor::GetOpacityImpl,
        FrameNodeExtenderAccessor::IsVisibleImpl,
        FrameNodeExtenderAccessor::IsClipToFrameImpl,
        FrameNodeExtenderAccessor::IsAttachedImpl,
        FrameNodeExtenderAccessor::GetInspectorInfoImpl,
        FrameNodeExtenderAccessor::InvalidateImpl,
        FrameNodeExtenderAccessor::DisposeTreeImpl,
        FrameNodeExtenderAccessor::SetCrossLanguageOptionsImpl,
        FrameNodeExtenderAccessor::GetCrossLanguageOptionsImpl,
        FrameNodeExtenderAccessor::SetMeasuredSizeImpl,
        FrameNodeExtenderAccessor::SetLayoutPositionImpl,
        FrameNodeExtenderAccessor::MeasureImpl,
        FrameNodeExtenderAccessor::LayoutImpl,
        FrameNodeExtenderAccessor::SetNeedsLayoutImpl,
        FrameNodeExtenderAccessor::GetPositionToScreenImpl,
        FrameNodeExtenderAccessor::GetPositionToWindowWithTransformImpl,
        FrameNodeExtenderAccessor::GetPositionToParentWithTransformImpl,
        FrameNodeExtenderAccessor::GetPositionToScreenWithTransformImpl,
        FrameNodeExtenderAccessor::GetFrameNodeByKeyImpl,
        FrameNodeExtenderAccessor::GetIdByFrameNodeImpl,
        FrameNodeExtenderAccessor::MoveToImpl,
        FrameNodeExtenderAccessor::GetFirstChildIndexWithoutExpandImpl,
        FrameNodeExtenderAccessor::GetLastChildIndexWithoutExpandImpl,
        FrameNodeExtenderAccessor::GetAttachedFrameNodeByIdImpl,
        FrameNodeExtenderAccessor::GetFrameNodeByIdImpl,
        FrameNodeExtenderAccessor::GetFrameNodeByUniqueIdImpl,
        FrameNodeExtenderAccessor::ReuseImpl,
        FrameNodeExtenderAccessor::RecycleImpl,
        FrameNodeExtenderAccessor::GetFrameNodePtrImpl,
        FrameNodeExtenderAccessor::CreateTypedFrameNodeImpl,
        FrameNodeExtenderAccessor::CreateByRawPtrImpl,
        FrameNodeExtenderAccessor::UnWrapRawPtrImpl,
        FrameNodeExtenderAccessor::GetCommonEventImpl,
    };
    return &FrameNodeExtenderAccessorImpl;
}

struct FrameNodeExtenderPeer {
    virtual ~FrameNodeExtenderPeer() = default;
};
}
