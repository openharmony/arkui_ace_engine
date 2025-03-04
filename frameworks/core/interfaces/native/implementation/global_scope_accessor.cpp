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
namespace GlobalScopeAccessor {
Ark_Context GetContextImpl(const Opt_CustomObject* component)
{
    return {};
}
void PostCardActionImpl(const Ark_CustomObject* component,
                        const Ark_CustomObject* action)
{
}
Ark_Resource Dollar_rImpl(const Ark_String* value,
                          const Array_CustomObject* params)
{
    return {};
}
Ark_Resource Dollar_rawfileImpl(const Ark_String* value)
{
    return {};
}
void AnimateToImpl(const Ark_AnimateParam* value,
                   const Callback_Void* event)
{
}
void AnimateToImmediatelyImpl(const Ark_AnimateParam* value,
                              const Callback_Void* event)
{
}
Ark_Number Vp2pxImpl(const Ark_Number* value)
{
    return {};
}
Ark_Number Px2vpImpl(const Ark_Number* value)
{
    return {};
}
Ark_Number Fp2pxImpl(const Ark_Number* value)
{
    return {};
}
Ark_Number Px2fpImpl(const Ark_Number* value)
{
    return {};
}
Ark_Number Lpx2pxImpl(const Ark_Number* value)
{
    return {};
}
Ark_Number Px2lpxImpl(const Ark_Number* value)
{
    return {};
}
Ark_CustomObject GetInspectorNodesImpl()
{
    return {};
}
Ark_CustomObject GetInspectorNodeByIdImpl(const Ark_Number* id)
{
    return {};
}
void SetAppBgColorImpl(const Ark_String* value)
{
}
void Profiler_registerVsyncCallbackImpl(const Callback_String_Void* callback_)
{
}
void Profiler_unregisterVsyncCallbackImpl()
{
}
void CursorControl_setCursorImpl(Ark_PointerStyle value)
{
}
void CursorControl_restoreDefaultImpl()
{
}
Ark_Boolean FocusControl_requestFocusImpl(const Ark_String* value)
{
    return {};
}
} // GlobalScopeAccessor
const GENERATED_ArkUIGlobalScopeAccessor* GetGlobalScopeAccessor()
{
    static const GENERATED_ArkUIGlobalScopeAccessor GlobalScopeAccessorImpl {
        GlobalScopeAccessor::GetContextImpl,
        GlobalScopeAccessor::PostCardActionImpl,
        GlobalScopeAccessor::Dollar_rImpl,
        GlobalScopeAccessor::Dollar_rawfileImpl,
        GlobalScopeAccessor::AnimateToImpl,
        GlobalScopeAccessor::AnimateToImmediatelyImpl,
        GlobalScopeAccessor::Vp2pxImpl,
        GlobalScopeAccessor::Px2vpImpl,
        GlobalScopeAccessor::Fp2pxImpl,
        GlobalScopeAccessor::Px2fpImpl,
        GlobalScopeAccessor::Lpx2pxImpl,
        GlobalScopeAccessor::Px2lpxImpl,
        GlobalScopeAccessor::GetInspectorNodesImpl,
        GlobalScopeAccessor::GetInspectorNodeByIdImpl,
        GlobalScopeAccessor::SetAppBgColorImpl,
        GlobalScopeAccessor::Profiler_registerVsyncCallbackImpl,
        GlobalScopeAccessor::Profiler_unregisterVsyncCallbackImpl,
        GlobalScopeAccessor::CursorControl_setCursorImpl,
        GlobalScopeAccessor::CursorControl_restoreDefaultImpl,
        GlobalScopeAccessor::FocusControl_requestFocusImpl,
    };
    return &GlobalScopeAccessorImpl;
}

}
