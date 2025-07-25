/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "frameworks/bridge/declarative_frontend/jsview/js_dump_log.h"

#include "base/log/dump_log.h"
#include "base/log/log_wrapper.h"
#include "bridge/declarative_frontend/engine/js_execution_scope_defines.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "frameworks/core/components_ng/pattern/stage/page_pattern.h"

namespace OHOS::Ace::Framework {
void JSDumpLog::JSBind(BindingTarget globalObj)
{
    JSClass<JSDumpLog>::Declare("DumpLog");
    JSClass<JSDumpLog>::StaticMethod("print", &JSDumpLog::Print);
    JSClass<JSDumpLog>::Bind(globalObj);
}

void JSDumpLog::Print(const JSCallbackInfo& info)
{
    if (!info[0]->IsNumber() || !info[1]->IsString()) {
        LOGE("JSDumpLog::Print invalid arguments, expected a number and a string");
        return;
    }

    DumpLog::GetInstance().Print(info[0]->ToNumber<int32_t>(), info[1]->ToString());
}

void JSDumpRegister::JSBind(BindingTarget globalObj)
{
    JSClass<JSDumpRegister>::Declare("DumpRegister");
    JSClass<JSDumpRegister>::StaticMethod("addListener", &JSDumpRegister::AddListener);
    JSClass<JSDumpRegister>::Bind(globalObj);
}

void JSDumpRegister::AddListener(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        LOGE("JSDumpRegister::AddListener not a function!");
        return;
    }

    auto container = Container::Current();
    if (!container) {
        LOGE("JSDumpRegister::AddListener container is null!");
        return;
    }
    auto pipelineBase = container->GetPipelineContext();
    auto pipelineContext = AceType::DynamicCast<NG::PipelineContext>(pipelineBase);
    if (!pipelineContext) {
        LOGE("JSDumpRegister::AddListener pipeline context is null!");
        return;
    }
    JSRef<JSFunc> cb = JSRef<JSFunc>::Cast(info[0]);
    auto listenerWrapper = [ctx = info.GetExecutionContext(), cb](const std::vector<std::string>& params) {
        JAVASCRIPT_EXECUTION_SCOPE(ctx);
        JSRef<JSArray> arr = JSRef<JSArray>::New();
        for (size_t i = 0; i < params.size(); ++i) {
            arr->SetValueAt(i, JSRef<JSVal>::Make(ToJSValue(params.at(i))));
        }
        JSRef<JSVal> argv = arr;
        cb->Call(JSRef<JSVal>(), 1, &argv);
    };
    auto stageManager = pipelineContext->GetStageManager();
    CHECK_NULL_VOID(stageManager);
    auto pageNode = stageManager->GetLastPage();
    CHECK_NULL_VOID(pageNode);
    auto pagePattern = pageNode->GetPattern<NG::PagePattern>();
    CHECK_NULL_VOID(pagePattern);
    pagePattern->RegisterDumpInfoListener(listenerWrapper);
}
} // namespace OHOS::Ace::Framework
