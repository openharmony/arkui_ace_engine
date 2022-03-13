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

#include "frameworks/bridge/js_frontend/engine/jsi/jsi_base_utils.h"

#include "base/log/event_report.h"
#include "core/common/ace_application_info.h"
#include "core/common/ace_engine.h"

namespace OHOS::Ace::Framework {
std::string JsiBaseUtils::GenerateSummaryBody(std::shared_ptr<JsValue> error, std::shared_ptr<JsRuntime> runtime)
{
    std::string summaryBody;
    summaryBody.append("Lifetime: ")
        .append(std::to_string(OHOS::Ace::AceApplicationInfo::GetInstance().GetLifeTime()))
        .append("s")
        .append("\n");

    summaryBody.append("Js-Engine: ark\n");

    if (!error) {
        summaryBody.append("error uncaught: error is null");
        return summaryBody;
    }

    const AceType *data = static_cast<AceType *>(runtime->GetEmbedderData());
    auto runningPage = GetRunningPage(data);

    RefPtr<RevSourceMap> pageMap;
    RefPtr<RevSourceMap> appMap;
    if (runningPage) {
        auto pageUrl = runningPage->GetUrl();
        summaryBody.append("page: ").append(pageUrl).append("\n");

        pageMap = runningPage->GetPageMap();
        appMap = runningPage->GetAppMap();
    }

    if (!error->IsObject(runtime) || error->IsNull(runtime)) {
        std::string errorInfo = error->ToString(runtime);
        summaryBody.append(errorInfo).append("\n");
    }
    shared_ptr<JsValue> message = error->GetProperty(runtime, "message");
    std::string messageStr = message->ToString(runtime);
    summaryBody.append("Error message: ");
    summaryBody.append(messageStr).append("\n");

    shared_ptr<JsValue> stack = error->GetProperty(runtime, "stack");
    std::string stackStr = stack->ToString(runtime);
    summaryBody.append("Stacktrace:\n");

    if (pageMap || appMap) {
        std::string tempStack = JsiDumpSourceFile(stackStr, pageMap, appMap);
        summaryBody.append(tempStack);
    } else {
        summaryBody.append("Cannot get SourceMap info, dump raw stack:\n");
        summaryBody.append(stackStr);
    }

    return summaryBody;
}

std::string JsiBaseUtils::JsiDumpSourceFile(const std::string& stackStr, const RefPtr<RevSourceMap>& pageMap,
    const RefPtr<RevSourceMap>& appMap)
{
    std::string ans = "";
    std::string tempStack = stackStr;
    int32_t appFlag = tempStack.find("app_.js");
    bool isAppPage = appFlag > 0 && appMap;

    // find per line of stack
    std::vector<std::string> res;
    ExtractEachInfo(tempStack, res);

    // collect error info first
    ans = ans + res[0] + "\n";
    for (uint32_t i = 1; i < res.size(); i++) {
        std::string temp = res[i];
        std::string line = "";
        std::string column = "";
        GetPosInfo(temp, line, column);
        if (line.empty() || column.empty()) {
            LOGI("the stack without line info");
            break;
        }

        const std::string sourceInfo = GetSourceInfo(line, column, pageMap, appMap, isAppPage);
        if (sourceInfo.empty()) {
            break;
        }
        temp = "at " + sourceInfo;
        ans = ans + temp + "\n";
    }
    if (ans.empty()) {
        return tempStack;
    }
    return ans;
}

void JsiBaseUtils::ExtractEachInfo(const std::string& tempStack, std::vector<std::string>& res)
{
    std::string tempStr = "";
    for (uint32_t i = 0; i < tempStack.length(); i++) {
        if (tempStack[i] == '\n') {
            res.push_back(tempStr);
            tempStr = "";
        } else {
            tempStr += tempStack[i];
        }
    }
    res.push_back(tempStr);
}

void JsiBaseUtils::GetPosInfo(const std::string& temp, std::string& line, std::string& column)
{
    // 0 for colum, 1 for row
    int32_t flag = 0;
    // find line, column
    for (int32_t i = temp.length() - 1; i > 0; i--) {
        if (temp[i] == ':') {
            flag += 1;
            continue;
        }
        // some stack line may end with ")"
        if (flag == 0) {
            if (temp[i] >= '0' && temp[i] <= '9') {
                column = temp[i] + column;
            }
        } else if (flag == 1) {
            line = temp[i] + line;
        } else {
            break;
        }
    }
}

std::string JsiBaseUtils::GetSourceInfo(const std::string& line, const std::string& column,
    const RefPtr<RevSourceMap>& pageMap, const RefPtr<RevSourceMap>& appMap, bool isAppPage)
{
    int32_t offSet = GetLineOffset();
    std::string sourceInfo;
    MappingInfo mapInfo;
    if (isAppPage) {
        mapInfo = appMap->Find(StringToInt(line) - offSet, StringToInt(column));
    } else {
        mapInfo = pageMap->Find(StringToInt(line) - offSet, StringToInt(column));
    }
    if (mapInfo.row == 0 || mapInfo.col == 0) {
        return "";
    }

    std::string sources = GetRelativePath(mapInfo.sources);
    sourceInfo = "(" + sources + ":" + std::to_string(mapInfo.row) + ":" + std::to_string(mapInfo.col) + ")";
    return sourceInfo;
}

std::string JsiBaseUtils::GetRelativePath(const std::string& sources)
{
    std::size_t pos = sources.find_last_of("/\\");
    if (pos != std::string::npos) {
        std::size_t splitPos = sources.substr(0, pos - 1).find_last_of("/\\");
        if (splitPos != std::string::npos) {
            std::string shortUrl = "pages" + sources.substr(splitPos);
            return shortUrl;
        }
    }
    LOGI("The stack path error!");
    return sources;
}

void JsiBaseUtils::ReportJsErrorEvent(std::shared_ptr<JsValue> error, std::shared_ptr<JsRuntime> runtime)
{
    if (!runtime) {
        LOGI("ReportJsErrorEvent: jsi engine has been destroyed");
        return;
    }
    LOGI("ReportJsErrorEvent");
    std::string summaryBody = GenerateSummaryBody(error, runtime);
    LOGE("summaryBody: \n%{public}s", summaryBody.c_str());
    EventReport::JsErrReport(AceApplicationInfo::GetInstance().GetPackageName(), "", summaryBody);
}
} // namespace OHOS::Ace::Framework
