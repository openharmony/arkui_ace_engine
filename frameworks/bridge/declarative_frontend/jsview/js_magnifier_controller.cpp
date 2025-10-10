/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "bridge/declarative_frontend/jsview/js_magnifier_controller.h"

#include "core/components_ng/base/inspector.h"
#include "core/components_ng/pattern/select_overlay/magnifier_controller.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::Framework {

void JSMagnifierController::JSBind(BindingTarget globalObj)
{
    JSClass<JSMagnifierController>::Declare("MagnifierController");
    JSClass<JSMagnifierController>::StaticMethod("bind", &JSMagnifierController::Bind);
    JSClass<JSMagnifierController>::StaticMethod("show", &JSMagnifierController::Show);
    JSClass<JSMagnifierController>::StaticMethod("unbind", &JSMagnifierController::Unbind);
    JSClass<JSMagnifierController>::Bind(
        globalObj, JSMagnifierController::Constructor, JSMagnifierController::Destructor);
}

void JSMagnifierController::Constructor(const JSCallbackInfo& args)
{
    auto magnifierController = Referenced::MakeRefPtr<JSMagnifierController>();
    magnifierController->IncRefCount();
    args.SetReturnValue(Referenced::RawPtr(magnifierController));
}

void JSMagnifierController::Destructor(JSMagnifierController* magnifierController)
{
    if (magnifierController != nullptr) {
        magnifierController->DecRefCount();
    }
}

void JSMagnifierController::Bind(const JSCallbackInfo& args)
{
    if (args.Length() < 1) {
        return;
    }
    auto pipelineContext = NG::PipelineContext::GetCurrentContextSafelyWithCheck();
    if (!pipelineContext) {
        TAG_LOGW(AceLogTag::ACE_SELECT_OVERLAY,
            "binding the magnifier and component failed because pipeline context is null.");
        return;
    }
    auto magnifierController = pipelineContext->GetMagnifierController();
    if (magnifierController) {
        magnifierController->UpdateShowMagnifier(false);
        magnifierController->RemoveMagnifierFrameNode();
        pipelineContext->SetMagnifierController(nullptr);
    }
    std::string id = "";
    if (args[0]->IsString()) {
        id = args[0]->ToString();
    }
    if (id.empty()) {
        TAG_LOGW(
            AceLogTag::ACE_SELECT_OVERLAY, "binding the magnifier and component failed because id is empty string.");
        return;
    }
    RefPtr<NG::FrameNode> frameNode = NG::Inspector::GetFrameNodeByKey(id, false, true);
    if (!frameNode) {
        TAG_LOGW(AceLogTag::ACE_SELECT_OVERLAY,
            "binding the magnifier and component failed because frame node isn't found.");
        return;
    }
    RefPtr<NG::Pattern> pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    magnifierController = MakeRefPtr<NG::MagnifierController>(pattern);
    pipelineContext->SetMagnifierController(magnifierController);
}

void JSMagnifierController::Show(const JSCallbackInfo& args)
{
    if (args.Length() <= 1) {
        return;
    }
    if (!args[0]->IsNumber() || !args[1]->IsNumber()) {
        return;
    }
    auto pipelineContext = NG::PipelineContext::GetCurrentContextSafelyWithCheck();
    if (!pipelineContext) {
        TAG_LOGW(AceLogTag::ACE_SELECT_OVERLAY, "showing the magnifier failed because pipeline context is null.");
        return;
    }
    auto magnifierController = pipelineContext->GetMagnifierController();
    if (!magnifierController) {
        TAG_LOGW(AceLogTag::ACE_SELECT_OVERLAY,
            "showing the magnifier failed because the magnifier isn't bound to a component.");
        return;
    }
    float dipScale = pipelineContext->GetDipScale();
    float x = args[0]->ToNumber<float>();
    float y = args[1]->ToNumber<float>();
    magnifierController->SetLocalOffset(NG::OffsetF(x * dipScale, y * dipScale));
}

void JSMagnifierController::Unbind()
{
    auto pipelineContext = NG::PipelineContext::GetCurrentContextSafelyWithCheck();
    if (!pipelineContext) {
        TAG_LOGW(AceLogTag::ACE_SELECT_OVERLAY, "unbinding the magnifier failed because pipeline context is null.");
        return;
    }
    auto magnifierController = pipelineContext->GetMagnifierController();
    if (!magnifierController) {
        TAG_LOGW(AceLogTag::ACE_SELECT_OVERLAY,
            "unbinding the magnifier failed because the magnifier isn't bound to a component.");
        return;
    }
    magnifierController->UpdateShowMagnifier(false);
    magnifierController->RemoveMagnifierFrameNode();
    pipelineContext->SetMagnifierController(nullptr);
}
} // namespace OHOS::Ace::Framework
