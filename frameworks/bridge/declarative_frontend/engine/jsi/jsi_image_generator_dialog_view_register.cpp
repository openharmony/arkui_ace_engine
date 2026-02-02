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
#include "frameworks/bridge/declarative_frontend/engine/jsi/jsi_image_generator_dialog_view_register.h"

#include "core/pipeline_ng/pipeline_context.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/jsi_object_template.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/jsi_value_conversions.h"

namespace OHOS::Ace::Framework {
int32_t ParseInstanceId(const panda::Local<panda::ObjectRef>& obj)
{
    const auto uiContext = JSRef<JSObject>::Make(obj);
    auto jsInstanceId = uiContext->GetProperty("instanceId_");
    if (!jsInstanceId->IsNumber()) {
        return -1;
    }
    return jsInstanceId->ToNumber<int32_t>();
}

panda::Local<panda::JSValueRef> JsOnXIconClicked(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    uint32_t argc = runtimeCallInfo->GetArgsNumber();
    if (argc != 1) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (!firstArg->IsObject(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::ObjectRef> obj = firstArg->ToObject(vm);
    auto instanceId = ParseInstanceId(obj);
    if (instanceId == -1) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto pipeline = NG::PipelineContext::GetContextByContainerId(instanceId);
    CHECK_NULL_RETURN(pipeline, panda::JSValueRef::Undefined(vm));
    auto overlayManager = pipeline->GetOverlayManager();
    CHECK_NULL_RETURN(overlayManager, panda::JSValueRef::Undefined(vm));
    auto isCloseSuccess = overlayManager->CloseImageGeneratorSheet();
    TAG_LOGI(AceLogTag::ACE_SIDEBAR, "image generator close %{public}s", isCloseSuccess ? "success" : "failed");
    return panda::JSValueRef::Undefined(vm);
}

void AddImageGeneratorDialogNode(const panda::Local<panda::ObjectRef>& obj)
{
    const auto object = JSRef<JSObject>::Make(obj);
    const EcmaVM* vm = object->GetEcmaVM();
    auto* view = JsiObjectTemplate::GetNativeView(obj, vm);
    if (!view && !static_cast<JSViewPartialUpdate*>(view) && !static_cast<JSViewFullUpdate*>(view)) {
        return;
    }
    auto uiNode = AceType::DynamicCast<NG::UINode>(view->CreateViewNode(true));
    CHECK_NULL_VOID(uiNode);
    auto customNode = AceType::DynamicCast<NG::CustomNode>(uiNode);
    CHECK_NULL_VOID(customNode);
    NG::ViewStackProcessor::GetInstance()->SetImageGeneratorDialogNode(customNode);
}

panda::Local<panda::JSValueRef> JsLoadImageGeneratorDialog(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    uint32_t argc = runtimeCallInfo->GetArgsNumber();
    if (argc != 1) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (!firstArg->IsObject(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::ObjectRef> obj = firstArg->ToObject(vm);
    AddImageGeneratorDialogNode(obj);

    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::Framework
