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
}
Ark_FrameNode CtorImpl(const Ark_UIContext* uiContext)
{
    return nullptr;
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
                           const Ark_Number* index)
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
Ark_Number GetOpacityImpl(Ark_FrameNode peer)
{
    return {};
}
Ark_Position GetPositionToWindowWithTransformImpl(Ark_FrameNode peer)
{
    return {};
}
Ark_FrameNode GetFrameNodeByKeyImpl(const Ark_String* name)
{
    return {};
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
        FrameNodeAccessor::GetOpacityImpl,
        FrameNodeAccessor::GetPositionToWindowWithTransformImpl,
        FrameNodeAccessor::GetFrameNodeByKeyImpl,
    };
    return &FrameNodeAccessorImpl;
}

}
