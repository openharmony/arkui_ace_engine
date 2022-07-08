/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_STACK_PROCESSOR_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_STACK_PROCESSOR_H

#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {

class JSViewStackProcessor {
public:
    JSViewStackProcessor() = default;
    ~JSViewStackProcessor() = default;

    static void JSBind(BindingTarget globalObj);
    static VisualState StringToVisualState(const std::string& stateString);

    static ElementIdType JsAllocateNewElmetIdForNextComponent()
    {
        return ElementRegister::GetInstance()->MakeUniqueId();
    }

    static void JsStartGetAccessRecordingFor(ElementIdType elmtId)
    {
        return ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(elmtId);
    }

    static int32_t JsGetElmtIdToAccountFor()
    {
        return ViewStackProcessor::GetInstance()->GetElmtIdToAccountFor();
    }
    static void JsSetElmtIdToAccountFor(ElementIdType elmtId)
    {
        ViewStackProcessor::GetInstance()->SetElmtIdToAccountFor(elmtId);
    }

    static void JsStopGetAccessRecording()
    {
        return ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }

    static void JsImplicitPopBeforeContinue();

private:
    static void JSVisualState(const JSCallbackInfo& info);
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_STACK_PROCESSOR_H
