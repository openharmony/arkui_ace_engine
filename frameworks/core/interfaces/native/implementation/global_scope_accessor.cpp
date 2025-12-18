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

#include "core/components/container_modal/container_modal_constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"
#include "global_scope_animation_helper.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace GlobalScopeAccessor {
Ark_Resource $rImpl(const Ark_String* value,
                    const Array_Opt_Object* params)
{
    return {};
}
Ark_Resource $rawfileImpl(const Ark_String* value)
{
    return {};
}
void AnimateToImpl(const Ark_AnimateParam* value,
                   const synthetic_Callback_Void* event)
{
    AnimateToInner(value, event, false);
}
void AnimateToImmediatelyImpl(const Ark_AnimateParam* value,
                              const synthetic_Callback_Void* event)
{
    AnimateToInner(value, event, true);
}
void CursorControl_restoreDefaultImpl()
{
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    if (!pipelineContext->GetTaskExecutor()) {
        return;
    }
    pipelineContext->GetTaskExecutor()->PostSyncTask(
        [pipelineContext]() { pipelineContext->RestoreDefault(0, MouseStyleChangeReason::USER_SET_MOUSESTYLE); },
        TaskExecutor::TaskType::UI, "ArkUIJsRestoreDefault");
}
void CursorControl_setCursorImpl(Ark_pointer_PointerStyle value)
{
    int32_t intValue = static_cast<int32_t>(value);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    if (!pipelineContext->GetTaskExecutor()) {
        return;
    }
    pipelineContext->GetTaskExecutor()->PostSyncTask(
        [pipelineContext, intValue]() { pipelineContext->SetCursor(intValue); },
        TaskExecutor::TaskType::UI, "ArkUIJsSetCursor");
}
Ark_Boolean FocusControl_requestFocusImpl(const Ark_String* value)
{
    bool result = false;
    CHECK_NULL_RETURN(value, Converter::ArkValue<Ark_Boolean>(result));
    std::string inspectorKey = Converter::Convert<std::string>(*value);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, Converter::ArkValue<Ark_Boolean>(result));
    if (!pipelineContext->GetTaskExecutor()) {
        return Converter::ArkValue<Ark_Boolean>(result);
    }
    pipelineContext->GetTaskExecutor()->PostSyncTask(
        [pipelineContext, inspectorKey, &result]() { result = pipelineContext->RequestFocus(inspectorKey); },
        TaskExecutor::TaskType::UI, "ArkUIJsRequestFocus");
    return Converter::ArkValue<Ark_Boolean>(result);
}
Ark_ComponentInfo GetRectangleByIdImpl(const Ark_String* id)
{
    return {};
}
void PostCardActionImpl(const Ark_Object* component,
                        const Ark_Object* action)
{
}
void Profiler_registerVsyncCallbackImpl(const Callback_String* callback_)
{
    CHECK_NULL_VOID(callback_);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    auto onVsyncFunc = [arkCallback = CallbackHelper(*callback_)](const std::string& value) {
        auto arkStringValue = Converter::ArkValue<Ark_String>(value);
        arkCallback.Invoke(arkStringValue);
    };
    pipelineContext->SetOnVsyncProfiler(onVsyncFunc);
}
void Profiler_unregisterVsyncCallbackImpl()
{
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->ResetOnVsyncProfiler();
}
void SetAppBgColorImpl(const Ark_String* value)
{
    CHECK_NULL_VOID(value);
    auto backgroundColorStr = Converter::Convert<std::string>(*value);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->SetAppBgColor(Color::ColorFromString(backgroundColorStr));
}
} // GlobalScopeAccessor
const GENERATED_ArkUIGlobalScopeAccessor* GetGlobalScopeAccessor()
{
    static const GENERATED_ArkUIGlobalScopeAccessor GlobalScopeAccessorImpl {
        GlobalScopeAccessor::$rImpl,
        GlobalScopeAccessor::$rawfileImpl,
        GlobalScopeAccessor::AnimateToImpl,
        GlobalScopeAccessor::AnimateToImmediatelyImpl,
        GlobalScopeAccessor::CursorControl_restoreDefaultImpl,
        GlobalScopeAccessor::CursorControl_setCursorImpl,
        GlobalScopeAccessor::FocusControl_requestFocusImpl,
        GlobalScopeAccessor::GetRectangleByIdImpl,
        GlobalScopeAccessor::PostCardActionImpl,
        GlobalScopeAccessor::Profiler_registerVsyncCallbackImpl,
        GlobalScopeAccessor::Profiler_unregisterVsyncCallbackImpl,
        GlobalScopeAccessor::SetAppBgColorImpl,
    };
    return &GlobalScopeAccessorImpl;
}

}
