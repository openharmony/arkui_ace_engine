/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/js_view_stack_processor.h"

#include "bridge/declarative_frontend/engine/bindings.h"
#include "bridge/declarative_frontend/engine/js_execution_scope_defines.h"
#include "bridge/declarative_frontend/engine/js_types.h"
#include "bridge/declarative_frontend/jsview/models/view_stack_model_impl.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/common/container.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/base/view_stack_model_ng.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "foundation/arkui/ace_engine/frameworks/core/common/ace_application_info.h"
#include "frameworks/core/common/layout_inspector.h"
#include "frameworks/core/pipeline/base/element_register.h"

namespace OHOS::Ace {

ViewStackModel* ViewStackModel::GetInstance()
{
#ifdef NG_BUILD
    static NG::ViewStackModelNG instance;
    return &instance;
#else
    if (Container::IsCurrentUseNewPipeline()) {
        static NG::ViewStackModelNG instance;
        return &instance;
    } else {
        static Framework::ViewStackModelImpl instance;
        return &instance;
    }
#endif
}

} // namespace OHOS::Ace
namespace OHOS::Ace::Framework {

void JSViewStackProcessor::JSVisualState(const JSCallbackInfo& info)
{
    if ((info.Length() < 1) || (!info[0]->IsString())) {
        ViewStackModel::GetInstance()->ClearVisualState();
        return;
    }

    std::string state = info[0]->ToString();
    VisualState visualState = JSViewStackProcessor::StringToVisualState(state);
    ViewStackModel::GetInstance()->SetVisualState(visualState);
}

// public static emthods exposed to JS
void JSViewStackProcessor::JSBind(BindingTarget globalObj)
{
    JSClass<JSViewStackProcessor>::Declare("ViewStackProcessor");
    MethodOptions opt = MethodOptions::NONE;

    JSClass<JSViewStackProcessor>::StaticMethod(
        "AllocateNewElmetIdForNextComponent", &JSViewStackProcessor::JsAllocateNewElmetIdForNextComponent, opt);
    JSClass<JSViewStackProcessor>::StaticMethod(
        "StartGetAccessRecordingFor", &JSViewStackProcessor::JsStartGetAccessRecordingFor, opt);
    JSClass<JSViewStackProcessor>::StaticMethod(
        "SetElmtIdToAccountFor", &JSViewStackProcessor::JsSetElmtIdToAccountFor, opt);
    JSClass<JSViewStackProcessor>::StaticMethod(
        "GetElmtIdToAccountFor", &JSViewStackProcessor::JsGetElmtIdToAccountFor, opt);
    JSClass<JSViewStackProcessor>::StaticMethod(
        "StopGetAccessRecording", &JSViewStackProcessor::JsStopGetAccessRecording, opt);
    JSClass<JSViewStackProcessor>::StaticMethod(
        "ImplicitPopBeforeContinue", &JSViewStackProcessor::JsImplicitPopBeforeContinue, opt);
    JSClass<JSViewStackProcessor>::StaticMethod("visualState", JSVisualState, opt);
    JSClass<JSViewStackProcessor>::StaticMethod("MakeUniqueId", &JSViewStackProcessor::JSMakeUniqueId, opt);
    JSClass<JSViewStackProcessor>::StaticMethod("UsesNewPipeline", &JSViewStackProcessor::JsUsesNewPipeline, opt);
    JSClass<JSViewStackProcessor>::StaticMethod("getApiVersion", &JSViewStackProcessor::JsGetApiVersion, opt);
    JSClass<JSViewStackProcessor>::StaticMethod("GetAndPushFrameNode", &JSViewStackProcessor::JsGetAndPushFrameNode);
    JSClass<JSViewStackProcessor>::StaticMethod("moveDeletedElmtIds", &JSViewStackProcessor::JsMoveDeletedElmtIds);
    JSClass<JSViewStackProcessor>::StaticMethod(
        "scheduleUpdateOnNextVSync", &JSViewStackProcessor::JSScheduleUpdateOnNextVSync);
    JSClass<JSViewStackProcessor>::StaticMethod("PushPrebuildCompCmd",
        &JSViewStackProcessor::JsPushPrebuildCompCmd, opt);
    JSClass<JSViewStackProcessor>::StaticMethod("CheckIsPrebuildTimeout",
        &JSViewStackProcessor::JsCheckIsPrebuildTimeout, opt);
    JSClass<JSViewStackProcessor>::StaticMethod("sendStateInfo", &JSViewStackProcessor::JsSendStateInfo);
#ifdef ACE_STATIC
    JSClass<JSViewStackProcessor>::StaticMethod("push", &JSViewStackProcessor::JsPush, opt);
    JSClass<JSViewStackProcessor>::StaticMethod("pop", &JSViewStackProcessor::JsPop, opt);
#endif
    JSClass<JSViewStackProcessor>::Bind<>(globalObj);
}

VisualState JSViewStackProcessor::StringToVisualState(const std::string& stateString)
{
    if (stateString == "normal") {
        return VisualState::NORMAL;
    }
    if (stateString == "focused") {
        return VisualState::FOCUSED;
    }
    if (stateString == "pressed" || stateString == "clicked") {
        return VisualState::PRESSED;
    }
    if (stateString == "disabled") {
        return VisualState::DISABLED;
    }
    if (stateString == "hover") {
        return VisualState::HOVER;
    }
    if (stateString == "selected") {
        return VisualState::SELECTED;
    }
    LOGE("Unknown visual state \"%{public}s\", resetting to UNDEFINED", stateString.c_str());
    return VisualState::NOTSET;
}

void JSViewStackProcessor::JsStartGetAccessRecordingFor(ElementIdType elmtId)
{
    ViewStackModel::GetInstance()->StartGetAccessRecordingFor(elmtId);
}

int32_t JSViewStackProcessor::JsGetElmtIdToAccountFor()
{
    return ViewStackModel::GetInstance()->GetElmtIdToAccountFor();
}

void JSViewStackProcessor::JsSetElmtIdToAccountFor(ElementIdType elmtId)
{
    ViewStackModel::GetInstance()->SetElmtIdToAccountFor(elmtId);
}

void JSViewStackProcessor::JsStopGetAccessRecording()
{
    return ViewStackModel::GetInstance()->StopGetAccessRecording();
}

void JSViewStackProcessor::JsImplicitPopBeforeContinue()
{
    ViewStackModel::GetInstance()->ImplicitPopBeforeContinue();
}

void JSViewStackProcessor::JSMakeUniqueId(const JSCallbackInfo& info)
{
    const auto result = ElementRegister::GetInstance()->MakeUniqueId();
    info.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(result)));
}
void JSViewStackProcessor::JsMoveDeletedElmtIds(const JSCallbackInfo& info)
{
    auto jsArrInfo = info[0];
    if (!jsArrInfo->IsArray()) {
        return;
    }
    JSRef<JSArray> jsArr = JSRef<JSArray>::Cast(jsArrInfo);

    RemovedElementsType removedElements;
    ElementRegister::GetInstance()->MoveRemovedItems(removedElements);
    size_t index = jsArr->Length();
    for (const auto& rmElmtId : removedElements) {
        jsArr->SetValueAt(index++, JSRef<JSVal>::Make(ToJSValue(rmElmtId)));
    }
}

// Initiates a frame request to RosenWindow and handles the callback from the Vsync request
void JSViewStackProcessor::JSScheduleUpdateOnNextVSync(const JSCallbackInfo& info)
{
    // Get the correct container
    int32_t containerId = -1;
    if (info.Length() > 1 && info[1]->IsNumber()) {
        containerId = info[1]->ToNumber<int32_t>();
    } else {
        LOGE("ERROR: JSScheduleUpdateOnNextVSync() no containerId provided.");
        return;
    }

    if (containerId < 0) {
        LOGE("ERROR: JSScheduleUpdateOnNextVSync() invalid containerId.");
        return;
    }

    auto container = Container::GetContainer(containerId);
    if (!container) {
        LOGE("JSScheduleUpdateOnNextVSync container is null");
        return;
    }
    auto context = container->GetPipelineContext();
    if (!context) {
        LOGE("JSScheduleUpdateOnNextVSync context is null");
        return;
    }

    if (info[0]->IsFunction()) {
        auto flushTSFunc = [execCtx = info.GetExecutionContext(),
            func = JSRef<JSFunc>::Cast(info[0])](int32_t containerId) -> bool {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, false);
            JSRef<JSVal> jsId = JSRef<JSVal>::Make(ToJSValue(containerId));
            JSRef<JSVal> retVal = func->Call(JSRef<JSObject>(), 1, &jsId);
            if (!retVal->IsBoolean()) {
                LOGE("JSScheduleUpdateOnNextVSync: flushTSFunc retVal is not boolean.");
                return false;
            }
            return retVal->ToBoolean();
        };
        context->SetFlushTSUpdates(std::move(flushTSFunc));
    } else {
        context->SetFlushTSUpdates(nullptr);
    }
}

void JSViewStackProcessor::JsSendStateInfo(const std::string& stateInfo)
{
#if defined(PREVIEW) || !defined(OHOS_PLATFORM)
    return;
#else
    if (!LayoutInspector::GetStateProfilerStatus()) {
        return;
    }
    auto container = Container::CurrentSafely();
    CHECK_NULL_VOID(container);
    auto pipeline = container->GetPipelineContext();
    CHECK_NULL_VOID(pipeline);
    auto info = JsonUtil::ParseJsonString(stateInfo);
    info->Put("timeStamp", GetCurrentTimestampMicroSecond());
    info->Put("vsyncID", (int32_t)pipeline->GetFrameCount());
    info->Put("processID", getpid());
    info->Put("windowID", (int32_t)pipeline->GetWindowId());
    TAG_LOGD(AceLogTag::ACE_STATE_MGMT, "ArkUI SendStateInfo %{public}s", info->ToString().c_str());
    LayoutInspector::SendMessage(info->ToString());
#endif
}

/**
 * return true of current Container uses new Pipeline
 */
bool JSViewStackProcessor::JsUsesNewPipeline()
{
    auto container = Container::Current();
    return container ? container->IsUseNewPipeline() : AceApplicationInfo::GetInstance().IsUseNewPipeline();
}

/**
 * return the API version specified in the manifest.json
 */
int32_t JSViewStackProcessor::JsGetApiVersion()
{
    return AceApplicationInfo::GetInstance().GetApiTargetVersion();
}

void JSViewStackProcessor::JsGetAndPushFrameNode(const JSCallbackInfo& info)
{
    if (info.Length() < 2) {
        return;
    }
    if (!info[0]->IsString() || !info[1]->IsNumber()) {
        return;
    }
    ViewStackModel::GetInstance()->GetAndPushFrameNode(info[0]->ToString(), info[1]->ToNumber<int32_t>());
}

void JSViewStackProcessor::JsPushPrebuildCompCmd(const JSCallbackInfo& info)
{
    ViewStackModel::GetInstance()->PushPrebuildCompCmd();
}

bool JSViewStackProcessor::JsCheckIsPrebuildTimeout()
{
    return ViewStackModel::GetInstance()->CheckIsPrebuildTimeout();
}

#ifdef ACE_STATIC
void JSViewStackProcessor::JsPush(const JSCallbackInfo &info)
{
    if (info.Length() < 1) {
        return;
    }
    if (!info[0]->IsNumber()) {
        return;
    }

    return ViewStackModel::GetInstance()->PushPtr(info[0]->ToNumber<int64_t>());
}

void JSViewStackProcessor::JsPop()
{
    return ViewStackModel::GetInstance()->Pop();
}
#endif
} // namespace OHOS::Ace::Framework
