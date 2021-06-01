/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/engine/quickjs/functions/qjs_click_function.h"

#include "base/log/log.h"
#include "frameworks/bridge/declarative_frontend/engine/quickjs/qjs_declarative_engine_instance.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_register.h"
#include "frameworks/bridge/js_frontend/engine/quickjs/qjs_utils.h"

namespace OHOS::Ace::Framework {

void QJSClickFunction::execute()
{
    JSValue result = QJSFunction::executeJS();

    if (JS_IsException(result)) {
        QjsUtils::JsStdDumpErrorAce(ctx_);
    }

    // This is required to request for new frame, which eventually will call
    // FlushBuild, FlushLayout and FlushRender on the dirty elements
    auto* instance = QJSDeclarativeEngineInstance::UnWrapEngineInstance(ctx_);
    if (instance != nullptr) {
        instance->GetDelegate()->GetPipelineContext()->AddPageUpdateTask([] {});
    } else {
        LOGE("QJS context has no ref to engine instance. Failed!");
    }

    JS_FreeValue(ctx_, result);
}

void QJSClickFunction::MarkGC(JSRuntime* rt, JS_MarkFunc* markFunc)
{
    LOGD("QJSClickFunction(MarkGC): start");
    QJSFunction::MarkGC(rt, markFunc);
    JS_MarkValue(rt, jsFunction_, markFunc);
    LOGD("QJSClickFunction(MarkGC): end");
}

void QJSClickFunction::ReleaseRT(JSRuntime* rt)
{
    LOGD("QJSClickFunction(release): start");
    QJSFunction::ReleaseRT(rt);
    JS_FreeValueRT(rt, jsFunction_);
    LOGD("QJSClickFunction(release): end");
}

} // namespace OHOS::Ace::Framework
