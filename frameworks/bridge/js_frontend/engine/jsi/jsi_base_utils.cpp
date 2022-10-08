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

#include "frameworks/bridge/js_frontend/engine/jsi/jsi_base_utils.h"

#include "base/log/event_report.h"
#include "base/log/exception_handler.h"
#include "core/common/ace_application_info.h"
#include "core/common/ace_engine.h"
#include "frameworks/bridge/js_frontend/engine/jsi/ark_js_runtime.h"
#include "frameworks/bridge/js_frontend/engine/jsi/ark_js_value.h"

#if defined(WINDOWS_PLATFORM) || defined(MAC_PLATFORM)
const int32_t OFFSET_PREVIEW = 9;
#endif

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
    std::string pageUrl;
    if (runningPage) {
        pageUrl = runningPage->GetUrl();
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
    std::string rawStack = stack->ToString(runtime);
    if (rawStack.empty()) {
        summaryBody.append("Stacktrace is empty!\n");
        return summaryBody;
    }

    shared_ptr<JsValue> errorFunc = error->GetProperty(runtime, "errorfunc");
    auto errorPos = GetErrorPos(rawStack);
    std::string sourceCodeInfo = GetSourceCodeInfo(runtime, errorFunc, errorPos);

    std::string runningPageTag = "app_.js";
    bool isAppPage = rawStack.find(runningPageTag, 1) != std::string::npos && appMap;
    sourceCodeInfo = isAppPage ? appMap->GetOriginalNames(sourceCodeInfo, errorPos.second)
                               : pageMap->GetOriginalNames(sourceCodeInfo, errorPos.second);

    std::string stackHead = "Stacktrace:\n";
    if (pageMap || appMap) {
        std::string showStack = TranslateStack(rawStack, pageUrl, pageMap, appMap, data);
        summaryBody.append(sourceCodeInfo).append(stackHead).append(showStack);
        // show raw stack for troubleshooting in the frame
        LOGI("JS Stack:\n%{public}s", TranslateRawStack(rawStack).c_str());
    } else {
        summaryBody.append("Cannot get SourceMap info, dump raw stack:\n");
        summaryBody.append(stackHead).append(rawStack);
    }

#if defined(WINDOWS_PLATFORM) || defined(MAC_PLATFORM)
    std::string summaryBodyInsertedWithTagStr = "";
    size_t lastPosOfNextLine = -1;
    size_t currPosOfNextLine = 0;
    while (true) {
        lastPosOfNextLine++; // Become the next position at which we start to find the target charactor.
        currPosOfNextLine = summaryBody.find_first_of("\n", lastPosOfNextLine);
        if (currPosOfNextLine == -1) {
            break;
        }
        summaryBodyInsertedWithTagStr
            .append("[Engine Log]")
            .append(summaryBody.substr(lastPosOfNextLine, (currPosOfNextLine - lastPosOfNextLine) + 1));
        lastPosOfNextLine = currPosOfNextLine;
    }
    return summaryBodyInsertedWithTagStr;
#else
    return summaryBody;
#endif
}

ErrorPos JsiBaseUtils::GetErrorPos(const std::string& rawStack)
{
    uint32_t lineEnd = rawStack.find("\n") - 1;
    if (rawStack[lineEnd - 1] == '?') {
        return std::make_pair(0, 0);
    }

    uint32_t secondPos = rawStack.rfind(':', lineEnd);
    uint32_t fristPos = rawStack.rfind(':', secondPos - 1);

    std::string lineStr = rawStack.substr(fristPos + 1, secondPos - 1 - fristPos);
    std::string columnStr = rawStack.substr(secondPos + 1, lineEnd - 1 - secondPos);

    return std::make_pair(StringToInt(lineStr), StringToInt(columnStr));
}

std::string JsiBaseUtils::GetSourceCodeInfo(std::shared_ptr<JsRuntime> runtime,
    const shared_ptr<JsValue>& errorFunc, ErrorPos pos)
{
    if (pos.first == 0) {
        return "";
    }
    shared_ptr<ArkJSRuntime> arkJsRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    LocalScope scope(arkJsRuntime->GetEcmaVm());
    uint32_t line = pos.first;
    uint32_t column = pos.second;
    Local<panda::FunctionRef> function(std::static_pointer_cast<ArkJSValue>(errorFunc)->GetValue(arkJsRuntime));
    Local<panda::StringRef> sourceCode = function->GetSourceCode(arkJsRuntime->GetEcmaVm(), line);
    std::string sourceCodeStr = sourceCode->ToString();
    if (sourceCodeStr.empty()) {
        return "";
    }
    std::string sourceCodeInfo = "SourceCode:\n";
    sourceCodeInfo.append(sourceCodeStr).append("\n");
    for (uint32_t k = 0; k < column - 1; k++) {
        sourceCodeInfo.push_back(' ');
    }
    sourceCodeInfo.append("^\n");
    return sourceCodeInfo;
}

std::string JsiBaseUtils::TransSourceStack(RefPtr<JsAcePage> runningPage, const std::string& rawStack)
{
    if (!runningPage) {
        return rawStack;
    }
    std::string summaryBody;
    RefPtr<RevSourceMap> pageMap;
    RefPtr<RevSourceMap> appMap;
    std::string pageUrl;
    if (runningPage) {
        pageUrl = runningPage->GetUrl();
        summaryBody.append(" Page: ").append(pageUrl).append("\n");
        pageMap = runningPage->GetPageMap();
        appMap = runningPage->GetAppMap();
    }

    std::string stackHead = "Stacktrace:\n";
    if (pageMap || appMap) {
        std::string tempStack = JsiBaseUtils::TranslateStack(rawStack, pageUrl, pageMap, appMap);
        summaryBody.append(stackHead).append(tempStack);
    } else {
        summaryBody.append("Cannot get SourceMap info, dump raw stack:\n");
        summaryBody.append(stackHead).append(rawStack);
    }

    return summaryBody;
}

std::string JsiBaseUtils::TranslateRawStack(const std::string& rawStackStr)
{
    std::string ans;
    std::string tempStack = rawStackStr;

    // find per line of stack
    std::vector<std::string> res;
    ExtractEachInfo(tempStack, res);

    // collect error info first
    for (uint32_t i = 0; i < res.size(); i++) {
        std::string temp = res[i];
        const std::string sourceInfo = GetRelativePath(temp, "/");
        ans = ans + sourceInfo + "\n";
    }
    if (ans.empty()) {
        return tempStack;
    }
    return ans;
}

std::string JsiBaseUtils::TranslateStack(const std::string& stackStr, const std::string& pageUrl,
    const RefPtr<RevSourceMap>& pageMap, const RefPtr<RevSourceMap>& appMap, const AceType *data)
{
    const std::string closeBrace = ")";
    const std::string openBrace = "(";
    std::string ans = "";
    std::string tempStack = stackStr;
    std::string runningPageTag = "app_.js";
    int32_t appFlag = static_cast<int32_t>(tempStack.find(runningPageTag));
    bool isAppPage = appFlag > 0 && appMap;
    if (!isAppPage) {
        std::string tag = std::as_const(pageUrl);
        char* ch = strrchr((char*)tag.c_str(), '.');
        int index = ch - tag.c_str();
        tag.insert(index, "_");
        runningPageTag = tag;
    }
    // find per line of stack
    std::vector<std::string> res;
    ExtractEachInfo(tempStack, res);

    // collect error info first
    for (uint32_t i = 0; i < res.size(); i++) {
        std::string temp = res[i];
        if (temp.rfind(runningPageTag) == std::string::npos) {
            continue;
        }
        int32_t closeBracePos = static_cast<int32_t>(temp.find(closeBrace));
        int32_t openBracePos = static_cast<int32_t>(temp.find(openBrace));

        std::string line = "";
        std::string column = "";
        GetPosInfo(temp, closeBracePos, line, column);
        if (line.empty() || column.empty()) {
            LOGI("the stack without line info");
            break;
        }

        const std::string sourceInfo = GetSourceInfo(line, column, pageMap, appMap, isAppPage, data);
        if (sourceInfo.empty()) {
            break;
        }
        temp.replace(openBracePos, closeBracePos - openBracePos + 1, sourceInfo);
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
    if (!tempStr.empty()) {
        res.push_back(tempStr);
    }
}

void JsiBaseUtils::GetPosInfo(const std::string& temp, int32_t start, std::string& line, std::string& column)
{
    // 0 for colum, 1 for row
    int32_t flag = 0;
    // find line, column
    for (int32_t i = start - 1; i > 0; i--) {
        if (temp[i] == ':') {
            flag += 1;
            continue;
        }
        if (flag == 0) {
            column = temp[i] + column;
        } else if (flag == 1) {
            line = temp[i] + line;
        } else {
            break;
        }
    }
}

std::string JsiBaseUtils::GetSourceInfo(const std::string& line, const std::string& column,
    const RefPtr<RevSourceMap>& pageMap, const RefPtr<RevSourceMap>& appMap, bool isAppPage, const AceType *data)
{
    int32_t offSet = GetLineOffset(data);
    std::string sourceInfo;
    MappingInfo mapInfo;
    if (isAppPage) {
        mapInfo = appMap->Find(StringToInt(line) - offSet, StringToInt(column));
    } else {
#if defined(WINDOWS_PLATFORM) || defined(MAC_PLATFORM)
        mapInfo = pageMap->Find(StringToInt(line) - offSet + OFFSET_PREVIEW, StringToInt(column));
#else
        mapInfo = pageMap->Find(StringToInt(line) - offSet, StringToInt(column));
#endif
    }
    if (mapInfo.row == 0 || mapInfo.col == 0) {
        return "";
    }

    std::string sources = GetRelativePath(mapInfo.sources);
    sourceInfo = "(" + sources + ":" + std::to_string(mapInfo.row) + ":" + std::to_string(mapInfo.col) + ")";
    return sourceInfo;
}

std::string JsiBaseUtils::GetRelativePath(const std::string& sources, std::string splitStr)
{
    std::string temp = sources;
    std::size_t splitPos = std::string::npos;
    const static int pathLevel = 3;
    int i = 0;
    while (i < pathLevel) {
        splitPos = temp.find_last_of(splitStr);
        if (splitPos != std::string::npos) {
            temp = temp.substr(0, splitPos - 1);
        } else {
            break;
        }
        i++;
    }
    if (i == pathLevel) {
        return sources.substr(splitPos);
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
    ExceptionHandler::HandleJsException(summaryBody);
}

std::string ParseLogContent(const std::vector<std::string>& params)
{
    std::string ret;
    if (params.empty()) {
        return ret;
    }
    std::string formatStr = params[0];
    int32_t size = static_cast<int32_t>(params.size());
    int32_t len = static_cast<int32_t>(formatStr.size());
    int32_t pos = 0;
    int32_t count = 1;
    for (; pos < len; ++pos) {
        if (count >= size) {
            break;
        }
        if (formatStr[pos] == '%') {
            if (pos + 1 >= len) {
                break;
            }
            switch (formatStr[pos + 1]) {
                case 's':
                case 'j':
                case 'd':
                case 'O':
                case 'o':
                case 'i':
                case 'f':
                case 'c':
                    ret += params[count++];
                    ++pos;
                    break;
                case '%':
                    ret += formatStr[pos];
                    ++pos;
                    break;
                default:
                    ret += formatStr[pos];
                    break;
            }
        } else {
            ret += formatStr[pos];
        }
    }
    if (pos < len) {
        ret += formatStr.substr(pos, len - pos);
    }
    return ret;
}

std::string GetLogContent(
    const shared_ptr<JsRuntime>& runtime, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    if (argc == 1) {
        return argv[0]->ToString(runtime);
    }
    std::vector<std::string> params;
    for (int32_t i = 0; i < argc; ++i) {
        params.emplace_back(argv[i]->ToString(runtime));
    }
    return ParseLogContent(params);
}

shared_ptr<JsValue> AppLogPrint(
    const shared_ptr<JsRuntime>& runtime, JsLogLevel level, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    // Should have at least 1 parameters.
    if (argc == 0) {
        LOGE("the arg is error");
        return runtime->NewUndefined();
    }
    std::string content = GetLogContent(runtime, argv, argc);
    switch (level) {
        case JsLogLevel::DEBUG:
            APP_LOGD("app Log: %{public}s", content.c_str());
            break;
        case JsLogLevel::INFO:
            APP_LOGI("app Log: %{public}s", content.c_str());
            break;
        case JsLogLevel::WARNING:
            APP_LOGW("app Log: %{public}s", content.c_str());
            break;
        case JsLogLevel::ERROR:
            APP_LOGE("app Log: %{public}s", content.c_str());
            break;
    }

    return runtime->NewUndefined();
}

// native implementation for js function: console.debug()
shared_ptr<JsValue> JsiBaseUtils::AppDebugLogPrint(const shared_ptr<JsRuntime>& runtime,
    const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    return AppLogPrint(runtime, JsLogLevel::DEBUG, argv, argc);
}

// native implementation for js function: console.info()
shared_ptr<JsValue> JsiBaseUtils::AppInfoLogPrint(const shared_ptr<JsRuntime>& runtime,
    const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    return AppLogPrint(runtime, JsLogLevel::INFO, argv, argc);
}

// native implementation for js function: console.warn()
shared_ptr<JsValue> JsiBaseUtils::AppWarnLogPrint(const shared_ptr<JsRuntime>& runtime,
    const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    return AppLogPrint(runtime, JsLogLevel::WARNING, argv, argc);
}

// native implementation for js function: console.error()
shared_ptr<JsValue> JsiBaseUtils::AppErrorLogPrint(const shared_ptr<JsRuntime>& runtime,
    const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    return AppLogPrint(runtime, JsLogLevel::ERROR, argv, argc);
}

shared_ptr<JsValue> JsLogPrint(
    const shared_ptr<JsRuntime>& runtime, JsLogLevel level, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    // Should have 1 parameters.
    if (argc == 0) {
        LOGE("the arg is error");
        return runtime->NewUndefined();
    }

    std::string content = GetLogContent(runtime, argv, argc);
    switch (level) {
        case JsLogLevel::DEBUG:
            LOGD("ace Log: %{public}s", content.c_str());
            break;
        case JsLogLevel::INFO:
            LOGI("ace Log: %{public}s", content.c_str());
            break;
        case JsLogLevel::WARNING:
            LOGW("ace Log: %{public}s", content.c_str());
            break;
        case JsLogLevel::ERROR:
            LOGE("ace Log: %{public}s", content.c_str());
            break;
    }

    shared_ptr<JsValue> ret = runtime->NewUndefined();
    return ret;
}

int PrintLog(int id, int level, const char* tag, const char* fmt, const char* message)
{
    switch (JsLogLevel(level - 3)) {
        case JsLogLevel::INFO:
            LOGI("%{public}s::%{public}s", tag, message);
            break;
        case JsLogLevel::WARNING:
            LOGW("%{public}s::%{public}s", tag, message);
            break;
        case JsLogLevel::ERROR:
            LOGE("%{public}s::%{public}s", tag, message);
            break;
        case JsLogLevel::DEBUG:
            LOGD("%{public}s::%{public}s", tag, message);
            break;
        default:
            LOGF("%{public}s::%{public}s", tag, message);
            break;
    }
    return 0;
}

shared_ptr<JsValue> JsiBaseUtils::JsDebugLogPrint(const shared_ptr<JsRuntime>& runtime,
    const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    return JsLogPrint(runtime, JsLogLevel::DEBUG, std::move(argv), argc);
}

shared_ptr<JsValue> JsiBaseUtils::JsInfoLogPrint(const shared_ptr<JsRuntime>& runtime,
    const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    return JsLogPrint(runtime, JsLogLevel::INFO, std::move(argv), argc);
}

shared_ptr<JsValue> JsiBaseUtils::JsWarnLogPrint(const shared_ptr<JsRuntime>& runtime,
    const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    return JsLogPrint(runtime, JsLogLevel::WARNING, std::move(argv), argc);
}

shared_ptr<JsValue> JsiBaseUtils::JsErrorLogPrint(const shared_ptr<JsRuntime>& runtime,
    const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    return JsLogPrint(runtime, JsLogLevel::ERROR, std::move(argv), argc);
}

std::string GetLogContent(NativeEngine* nativeEngine, NativeCallbackInfo* info)
{
    std::string content;
    for (size_t i = 0; i < info->argc; ++i) {
        if (info->argv[i]->TypeOf() != NATIVE_STRING) {
            LOGE("argv is not NativeString");
            continue;
        }
        auto nativeString = reinterpret_cast<NativeString*>(info->argv[i]->GetInterface(NativeString::INTERFACE_ID));
        size_t bufferSize = nativeString->GetLength();
        size_t strLength = 0;
        char* buffer = new char[bufferSize + 1] { 0 };
        nativeString->GetCString(buffer, bufferSize + 1, &strLength);
        content.append(buffer);
        delete[] buffer;
    }
    return content;
}

NativeValue* AppLogPrint(NativeEngine* nativeEngine, NativeCallbackInfo* info, JsLogLevel level)
{
    // Should have at least 1 parameters.
    if (info->argc == 0) {
        LOGE("the arg is error");
        return nativeEngine->CreateUndefined();
    }
    std::string content = GetLogContent(nativeEngine, info);
    switch (level) {
        case JsLogLevel::DEBUG:
            APP_LOGD("app Log: %{public}s", content.c_str());
            break;
        case JsLogLevel::INFO:
            APP_LOGI("app Log: %{public}s", content.c_str());
            break;
        case JsLogLevel::WARNING:
            APP_LOGW("app Log: %{public}s", content.c_str());
            break;
        case JsLogLevel::ERROR:
            APP_LOGE("app Log: %{public}s", content.c_str());
            break;
    }

    return nativeEngine->CreateUndefined();
}

NativeValue* AppDebugLogPrint(NativeEngine* nativeEngine, NativeCallbackInfo* info)
{
    return AppLogPrint(nativeEngine, info, JsLogLevel::DEBUG);
}

NativeValue* AppInfoLogPrint(NativeEngine* nativeEngine, NativeCallbackInfo* info)
{
    return AppLogPrint(nativeEngine, info, JsLogLevel::INFO);
}

NativeValue* AppWarnLogPrint(NativeEngine* nativeEngine, NativeCallbackInfo* info)
{
    return AppLogPrint(nativeEngine, info, JsLogLevel::WARNING);
}

NativeValue* AppErrorLogPrint(NativeEngine* nativeEngine, NativeCallbackInfo* info)
{
    return AppLogPrint(nativeEngine, info, JsLogLevel::ERROR);
}
} // namespace OHOS::Ace::Framework
