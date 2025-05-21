/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_JS_FRONTEND_ENGINE_JSI_BASE_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_JS_FRONTEND_ENGINE_JSI_BASE_UTILS_H

#include "base/log/ace_trace.h"
#include "base/log/event_report.h"
#include "base/log/exception_handler.h"
#include "bridge/js_frontend/engine/common/runtime_constants.h"
#include "bridge/js_frontend/engine/jsi/js_runtime.h"
#include "bridge/js_frontend/engine/jsi/js_value.h"
#include "bridge/js_frontend/engine/jsi/jsi_engine.h"

namespace OHOS::Ace::Framework {
using ErrorPos = std::pair<uint32_t, uint32_t>;
int32_t GetLineOffset(const AceType* data);
RefPtr<JsAcePage> GetRunningPage(const AceType* data);
napi_value AppDebugLogPrint(napi_env env, napi_callback_info info);
napi_value AppInfoLogPrint(napi_env env, napi_callback_info info);
napi_value AppWarnLogPrint(napi_env env, napi_callback_info info);
napi_value AppErrorLogPrint(napi_env env, napi_callback_info info);
int PrintLog(int id, int level, const char* tag, const char* fmt, const char* message);

class JsiBaseUtils {
public:
    static void ReportJsErrorEvent(std::shared_ptr<JsValue> error, std::shared_ptr<JsRuntime> runtime);
    static std::string TransSourceStack(RefPtr<JsAcePage> runningPage, const std::string& rawStack);
    // native implementation for js function: console.debug()
    static shared_ptr<JsValue> AppDebugLogPrint(const shared_ptr<JsRuntime>& runtime,
        const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc);
    // native implementation for js function: console.info()
    static shared_ptr<JsValue> AppInfoLogPrint(const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& thisObj,
        const std::vector<shared_ptr<JsValue>>& argv, int32_t argc);
    // native implementation for js function: console.warn()
    static shared_ptr<JsValue> AppWarnLogPrint(const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& thisObj,
        const std::vector<shared_ptr<JsValue>>& argv, int32_t argc);
    // native implementation for js function: console.error()
    static shared_ptr<JsValue> AppErrorLogPrint(const shared_ptr<JsRuntime>& runtime,
        const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc);

    // native implementation for js function: aceConsole.debug()
    static shared_ptr<JsValue> JsDebugLogPrint(const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& thisObj,
        const std::vector<shared_ptr<JsValue>>& argv, int32_t argc);
    // native implementation for js function: aceConsole.info()
    static shared_ptr<JsValue> JsInfoLogPrint(const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& thisObj,
        const std::vector<shared_ptr<JsValue>>& argv, int32_t argc);
    // native implementation for js function: aceConsole.warn()
    static shared_ptr<JsValue> JsWarnLogPrint(const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& thisObj,
        const std::vector<shared_ptr<JsValue>>& argv, int32_t argc);
    // native implementation for js function: aceConsole.error()
    static shared_ptr<JsValue> JsErrorLogPrint(const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& thisObj,
        const std::vector<shared_ptr<JsValue>>& argv, int32_t argc);

    // native implementation for js function: aceTrace.begin()
    static shared_ptr<JsValue> JsTraceBegin(const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& thisObj,
        const std::vector<shared_ptr<JsValue>>& argv, int32_t argc);
    // native implementation for js function: aceTrace.end()
    static shared_ptr<JsValue> JsTraceEnd(const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& thisObj,
        const std::vector<shared_ptr<JsValue>>& argv, int32_t argc);
    static void GetStageSourceMap(
        const AceType* data, std::unordered_map<std::string, RefPtr<RevSourceMap>>& sourceMaps);
    static std::string TranslateStack(const std::string& stackStr, const std::string& pageUrl,
        const RefPtr<RevSourceMap>& pageMap, const RefPtr<RevSourceMap>& appMap, const AceType* data = nullptr);
    static std::string TranslateBySourceMap(const std::string& stackStr, const std::string& pageUrl,
        const std::unordered_map<std::string, RefPtr<RevSourceMap>>& sourceMaps, const RefPtr<RevSourceMap>& appMap,
        const AceType* data = nullptr);

private:
    static std::string GenerateErrorMsg(
        const std::shared_ptr<JsValue>& error, const std::shared_ptr<JsRuntime>& runtime);
    static std::string GenerateSummaryBody(
        const std::shared_ptr<JsValue>& error, const std::shared_ptr<JsRuntime>& runtime);
    static JsErrorObject GenerateJsErrorObject(
        const std::shared_ptr<JsValue>& error, const std::shared_ptr<JsRuntime>& runtime);
    static ErrorPos GetErrorPos(const std::string& rawStack);
    static std::string GetSourceCodeInfo(
        std::shared_ptr<JsRuntime> runtime, const shared_ptr<JsValue>& errorFunc, ErrorPos pos);
    static std::string TranslateRawStack(const std::string& rawStackStr);
    static void ExtractEachInfo(const std::string& tempStack, std::vector<std::string>& res);
    static void GetPosInfo(const std::string& temp, int32_t start, std::string& line, std::string& column);
    static std::string GetSourceInfo(const std::string& line, const std::string& column,
        const RefPtr<RevSourceMap>& pageMap, const RefPtr<RevSourceMap>& appMap, bool isAppPage, const AceType* data,
        const bool isBundle = true);
    static std::string GetRelativePath(const std::string& sources, std::string splitStr = "/\\");

    // native aceTraceObjects
    static thread_local std::stack<std::unique_ptr<AceScopedTrace>> aceScopedTrace_;
};
} // namespace OHOS::Ace::Framework

#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_JS_FRONTEND_ENGINE_JSI_BASE_UTILS_H
