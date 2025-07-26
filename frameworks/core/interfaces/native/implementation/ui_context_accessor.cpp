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
namespace UIContextAccessor {
void DestroyPeerImpl(Ark_UIContext peer)
{
}
Ark_UIContext CtorImpl()
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Font GetFontImpl(Ark_UIContext peer)
{
    return {};
}
Ark_String GetFilteredInspectorTreeImpl(Ark_VMContext vmContext,
                                        Ark_UIContext peer,
                                        const Opt_Array_String* filters)
{
    return {};
}
Ark_String GetFilteredInspectorTreeByIdImpl(Ark_VMContext vmContext,
                                            Ark_UIContext peer,
                                            const Ark_String* id,
                                            const Ark_Number* depth,
                                            const Opt_Array_String* filters)
{
    return {};
}
void AnimateToImpl(Ark_UIContext peer,
                   const Ark_AnimateParam* value,
                   const Callback_Void* event)
{
}
void ShowTextPickerDialogImpl(Ark_UIContext peer,
                              const Ark_TextPickerDialogOptions* options)
{
}
void RunScopedTaskImpl(Ark_UIContext peer,
                       const Callback_Void* callback_)
{
}
void AnimateToImmediatelyImpl(Ark_UIContext peer,
                              const Ark_AnimateParam* param,
                              const Callback_Void* event)
{
}
Ark_Union_FrameNode_Undefined GetFrameNodeByIdImpl(Ark_UIContext peer,
                                                   const Ark_String* id)
{
    return {};
}
Ark_Union_FrameNode_Undefined GetAttachedFrameNodeByIdImpl(Ark_UIContext peer,
                                                           const Ark_String* id)
{
    return {};
}
Ark_Union_FrameNode_Undefined GetFrameNodeByUniqueIdImpl(Ark_UIContext peer,
                                                         const Ark_Number* id)
{
    return {};
}
Ark_Number Vp2pxImpl(Ark_UIContext peer,
                     const Ark_Number* value)
{
    return {};
}
Ark_Number Px2vpImpl(Ark_UIContext peer,
                     const Ark_Number* value)
{
    return {};
}
Ark_Number Fp2pxImpl(Ark_UIContext peer,
                     const Ark_Number* value)
{
    return {};
}
Ark_Number Px2fpImpl(Ark_UIContext peer,
                     const Ark_Number* value)
{
    return {};
}
Ark_Number Lpx2pxImpl(Ark_UIContext peer,
                      const Ark_Number* value)
{
    return {};
}
Ark_Number Px2lpxImpl(Ark_UIContext peer,
                      const Ark_Number* value)
{
    return {};
}
Ark_Union_Context_Undefined GetHostContextImpl(Ark_UIContext peer)
{
    return {};
}
void SetDynamicDimmingImpl(Ark_UIContext peer,
                           const Ark_String* id,
                           const Ark_Number* value)
{
}
Ark_Union_String_Undefined GetWindowNameImpl(Ark_UIContext peer)
{
    return {};
}
void OpenBindSheetImpl(Ark_VMContext vmContext,
                       Ark_UIContext peer,
                       Ark_ComponentContent bindSheetContent,
                       const Opt_SheetOptions* sheetOptions,
                       const Opt_Number* targetId)
{
}
void UpdateBindSheetImpl(Ark_VMContext vmContext,
                         Ark_UIContext peer,
                         Ark_ComponentContent bindSheetContent,
                         const Ark_SheetOptions* sheetOptions,
                         const Opt_Boolean* partialUpdate)
{
}
void CloseBindSheetImpl(Ark_VMContext vmContext,
                        Ark_UIContext peer,
                        Ark_ComponentContent bindSheetContent)
{
}
void ClearResourceCacheImpl(Ark_VMContext vmContext,
                            Ark_UIContext peer)
{
}
Ark_Boolean IsFollowingSystemFontScaleImpl(Ark_UIContext peer)
{
    return {};
}
Ark_Number GetMaxFontScaleImpl(Ark_UIContext peer)
{
    return {};
}
} // UIContextAccessor
const GENERATED_ArkUIUIContextAccessor* GetUIContextAccessor()
{
    static const GENERATED_ArkUIUIContextAccessor UIContextAccessorImpl {
        UIContextAccessor::DestroyPeerImpl,
        UIContextAccessor::CtorImpl,
        UIContextAccessor::GetFinalizerImpl,
        UIContextAccessor::GetFontImpl,
        UIContextAccessor::GetFilteredInspectorTreeImpl,
        UIContextAccessor::GetFilteredInspectorTreeByIdImpl,
        UIContextAccessor::AnimateToImpl,
        UIContextAccessor::ShowTextPickerDialogImpl,
        UIContextAccessor::RunScopedTaskImpl,
        UIContextAccessor::AnimateToImmediatelyImpl,
        UIContextAccessor::GetFrameNodeByIdImpl,
        UIContextAccessor::GetAttachedFrameNodeByIdImpl,
        UIContextAccessor::GetFrameNodeByUniqueIdImpl,
        UIContextAccessor::Vp2pxImpl,
        UIContextAccessor::Px2vpImpl,
        UIContextAccessor::Fp2pxImpl,
        UIContextAccessor::Px2fpImpl,
        UIContextAccessor::Lpx2pxImpl,
        UIContextAccessor::Px2lpxImpl,
        UIContextAccessor::GetHostContextImpl,
        UIContextAccessor::SetDynamicDimmingImpl,
        UIContextAccessor::GetWindowNameImpl,
        UIContextAccessor::OpenBindSheetImpl,
        UIContextAccessor::UpdateBindSheetImpl,
        UIContextAccessor::CloseBindSheetImpl,
        UIContextAccessor::ClearResourceCacheImpl,
        UIContextAccessor::IsFollowingSystemFontScaleImpl,
        UIContextAccessor::GetMaxFontScaleImpl,
    };
    return &UIContextAccessorImpl;
}

}
