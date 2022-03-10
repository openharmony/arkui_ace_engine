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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_JS_FRONTEND_ENGINE_JSI_BASE_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_JS_FRONTEND_ENGINE_JSI_BASE_UTILS_H

#include "frameworks/bridge/js_frontend/engine/jsi/jsi_engine.h"
#include "frameworks/bridge/js_frontend/engine/jsi/js_runtime.h"
#include "frameworks/bridge/js_frontend/engine/jsi/js_value.h"

namespace OHOS::Ace::Framework {
int32_t GetLineOffset();
RefPtr<JsAcePage> GetRunningPage(const AceType *data);

class JsiBaseUtils {
public:
    static void ReportJsErrorEvent(std::shared_ptr<JsValue> error, std::shared_ptr<JsRuntime> runtime);

private:
    static std::string GenerateSummaryBody(std::shared_ptr<JsValue> error, std::shared_ptr<JsRuntime> runtime);
    static std::string JsiDumpSourceFile(const std::string& stackStr, const RefPtr<RevSourceMap>& pageMap,
        const RefPtr<RevSourceMap>& appMap);
    static void ExtractEachInfo(const std::string& tempStack, std::vector<std::string>& res);
    static void GetPosInfo(const std::string& temp, std::string& line, std::string& column);
    static std::string GetSourceInfo(const std::string& line, const std::string& column,
        const RefPtr<RevSourceMap>& pageMap, const RefPtr<RevSourceMap>& appMap, bool isAppPage);
    static std::string GetRelativePath(const std::string& sources);
};
} // namespace OHOS::Ace::Framework

#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_JS_FRONTEND_ENGINE_JSI_BASE_UTILS_H
