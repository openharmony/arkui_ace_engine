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

#include "bridge/js_frontend/engine/jsi/jsi_base_utils.h"

#include "bridge/declarative_frontend/engine/jsi/jsi_declarative_engine.h"
#include "bridge/js_frontend/engine/jsi/ark_js_value.h"

namespace OHOS::Ace::Framework {
constexpr char JS_CRASH_CODE[] = "100001";
const std::string NAME = "name";
const std::string MESSAGE = "message";
const std::string STACK = "stack";

int32_t GetLineOffset(const AceType* data)
{
#ifndef PA_SUPPORT
    if (data == nullptr) {
        return 0;
    }
    if (AceType::InstanceOf<JsiDeclarativeEngineInstance>(data)) {
        return 0;
    }
#endif
    const int32_t offset = 14;
    return offset;
}

std::string GetMsgStr(const std::string& msg)
{
    auto pos = msg.find('\n');
    if (pos == std::string::npos) {
        return msg;
    }

    return msg.substr(0, pos);
}

RefPtr<JsAcePage> GetRunningPage(const AceType* data)
{
#ifndef PA_SUPPORT
    if (data == nullptr) {
        return nullptr;
    }
    if (AceType::InstanceOf<JsiDeclarativeEngineInstance>(data)) {
        auto instance = static_cast<const JsiDeclarativeEngineInstance*>(data);
        return instance->GetRunningPage();
    }
#ifndef NG_BUILD
    else if (AceType::InstanceOf<JsiEngineInstance>(data)) {
        auto instance = static_cast<const JsiEngineInstance*>(data);
        return instance->GetRunningPage();
    }
#endif
#endif
    return nullptr;
}

RefPtr<FrontendDelegate> GetDelegate(const AceType* data)
{
#ifndef PA_SUPPORT
    if (data == nullptr) {
        return nullptr;
    }
    if (AceType::InstanceOf<JsiDeclarativeEngineInstance>(data)) {
        auto instance = static_cast<const JsiDeclarativeEngineInstance*>(data);
        return instance->GetDelegate();
    }
#ifndef NG_BUILD
    else if (AceType::InstanceOf<JsiEngineInstance>(data)) {
        auto instance = static_cast<const JsiEngineInstance*>(data);
        return instance->GetDelegate();
    }
#endif
#endif
    return nullptr;
}

std::string JsiBaseUtils::GenerateErrorMsg(
    const std::shared_ptr<JsValue>& error, const std::shared_ptr<JsRuntime>& runtime)
{
    std::string errMsg;
    if (!error) {
        errMsg.append("error uncaught");
        return errMsg;
    }

    std::string messageStr;
    std::string rawStack;
    shared_ptr<JsValue> message = error->GetProperty(runtime, "message");
    if (message) {
        messageStr = message->ToString(runtime);
    }

    shared_ptr<JsValue> stack = error->GetProperty(runtime, "stack");
    if (stack) {
        rawStack = stack->ToString(runtime);
    }

    errMsg.append("{\"ErrMsg\":\"")
        .append(messageStr)
        .append("\", \"Stacktrace\": \"")
        .append(GetMsgStr(rawStack))
        .append("\"}");
    return errMsg;
}

JsErrorObject JsiBaseUtils::GenerateJsErrorObject(
    const std::shared_ptr<JsValue>& error, const std::shared_ptr<JsRuntime>& runtime)
{
    if (error == nullptr) {
        return {};
    }
    JsErrorObject errInfo;
    shared_ptr<JsValue> name = error->GetProperty(runtime, NAME);
    if (name != nullptr) {
        errInfo.name = name->ToString(runtime);
    }
    shared_ptr<JsValue> message = error->GetProperty(runtime, MESSAGE);
    if (message != nullptr) {
        errInfo.message = message->ToString(runtime);
    }
    shared_ptr<JsValue> stack = error->GetProperty(runtime, STACK);
    if (stack != nullptr) {
        errInfo.stack = stack->ToString(runtime);
    }
    return errInfo;
}

std::string JsiBaseUtils::GenerateSummaryBody(
    const std::shared_ptr<JsValue>& error, const std::shared_ptr<JsRuntime>& runtime)
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

    const AceType* data = static_cast<AceType*>(runtime->GetEmbedderData());
    std::string pageUrl;
    RefPtr<RevSourceMap> pageMap;
    RefPtr<RevSourceMap> appMap;
    std::unordered_map<std::string, RefPtr<RevSourceMap>> sourceMaps;
    auto vm = const_cast<EcmaVM*>(std::static_pointer_cast<ArkJSRuntime>(runtime)->GetEcmaVm());
    auto container = Container::Current();
    if (container && container->IsUseNewPipeline()) {
        auto frontEnd = container->GetFrontend();
        if (frontEnd) {
            pageUrl = frontEnd->GetCurrentPageUrl();
            if (!JSNApi::IsBundle(vm)) {
                frontEnd->GetStageSourceMap(sourceMaps);
            } else {
                pageMap = frontEnd->GetCurrentPageSourceMap();
            }
            appMap = frontEnd->GetFaAppSourceMap();
        }
    } else {
        auto runningPage = GetRunningPage(data);
        if (runningPage) {
            pageUrl = runningPage->GetUrl();
            appMap = runningPage->GetAppMap();
            if (!JSNApi::IsBundle(vm)) {
                GetStageSourceMap(data, sourceMaps);
            } else {
                pageMap = runningPage->GetPageMap();
            }
        }
    }
    if (!pageUrl.empty()) {
        summaryBody.append("page: ").append(pageUrl).append("\n");
    }
    if (!error->IsObject(runtime) || error->IsNull(runtime)) {
        std::string errorInfo = error->ToString(runtime);
        summaryBody.append(errorInfo).append("\n");
    }
    shared_ptr<JsValue> message = error->GetProperty(runtime, "message");
    std::string messageStr = message->ToString(runtime);
    summaryBody.append("Error message: ");
    summaryBody.append(messageStr).append("\n");

    if (error->HasProperty(runtime, "code")) {
        shared_ptr<JsValue> code = error->GetProperty(runtime, "code");
        std::string codeStr = code->ToString(runtime);
        summaryBody.append("Error code: ");
        summaryBody.append(codeStr).append("\n");
    }

    shared_ptr<JsValue> stack = error->GetProperty(runtime, "stack");
    std::string rawStack = stack->ToString(runtime);
    if (rawStack.empty()) {
        summaryBody.append("Stacktrace is empty!\n");
        return summaryBody;
    }

    shared_ptr<JsValue> errorFunc = error->GetProperty(runtime, "errorfunc");
    auto errorPos = GetErrorPos(rawStack);
    std::string sourceCodeInfo = GetSourceCodeInfo(runtime, errorFunc, errorPos);

    std::string stackHead = "Stacktrace:\n";
    if (pageMap || appMap || !sourceMaps.empty()) {
        std::string runningPageTag = "app_.js";
        bool isAppPage = rawStack.find(runningPageTag, 1) != std::string::npos && appMap;
        if (isAppPage) {
            sourceCodeInfo = appMap->GetOriginalNames(sourceCodeInfo, errorPos.second);
        } else if (pageMap) {
            sourceCodeInfo = pageMap->GetOriginalNames(sourceCodeInfo, errorPos.second);
        }
        std::string showStack;
        if (!JSNApi::IsBundle(vm)) {
            showStack = TranslateBySourceMap(rawStack, pageUrl, sourceMaps, appMap, data);
        } else {
            showStack = TranslateStack(rawStack, pageUrl, pageMap, appMap, data);
        }
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
        summaryBodyInsertedWithTagStr.append("[Engine Log]")
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
    size_t findLineEnd = rawStack.find("\n");
    if (findLineEnd == std::string::npos) {
        return std::make_pair(0, 0);
    }
    size_t lineEnd = findLineEnd - 1;
    if (lineEnd < 1 || rawStack[lineEnd - 1] == '?') {
        return std::make_pair(0, 0);
    }

    size_t secondPos = rawStack.rfind(':', lineEnd);
    if (secondPos == std::string::npos) {
        return std::make_pair(0, 0);
    }

    size_t firstPos = rawStack.rfind(':', secondPos - 1);
    if (firstPos == std::string::npos) {
        return std::make_pair(0, 0);
    }

    std::string lineStr = rawStack.substr(firstPos + 1, secondPos - 1 - firstPos);
    std::string columnStr = rawStack.substr(secondPos + 1, lineEnd - 1 - secondPos);

    return std::make_pair(StringToInt(lineStr), StringToInt(columnStr));
}

std::string JsiBaseUtils::GetSourceCodeInfo(
    std::shared_ptr<JsRuntime> runtime, const shared_ptr<JsValue>& errorFunc, ErrorPos pos)
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
    std::string sourceCodeStr = sourceCode->ToString(arkJsRuntime->GetEcmaVm());
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
    RefPtr<RevSourceMap> pageMap;
    RefPtr<RevSourceMap> appMap;
    std::string pageUrl;
    auto container = Container::Current();
    if (container && container->IsUseNewPipeline()) {
        auto frontEnd = container->GetFrontend();
        if (frontEnd) {
            pageUrl = frontEnd->GetCurrentPageUrl();
            pageMap = frontEnd->GetCurrentPageSourceMap();
            appMap = frontEnd->GetFaAppSourceMap();
        }
    } else {
        if (runningPage) {
            pageUrl = runningPage->GetUrl();
            pageMap = runningPage->GetPageMap();
            appMap = runningPage->GetAppMap();
        }
    }

    if (!pageMap) {
        return rawStack;
    }

    std::string summaryBody;
    summaryBody.append(" Page: ").append(pageUrl).append("\n");

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
    for (const auto& temp : res) {
        const std::string sourceInfo = GetRelativePath(temp, "/");
        ans = ans + sourceInfo + "\n";
    }
    if (ans.empty()) {
        return tempStack;
    }
    return ans;
}

std::string JsiBaseUtils::TranslateStack(const std::string& stackStr, const std::string& pageUrl,
    const RefPtr<RevSourceMap>& pageMap, const RefPtr<RevSourceMap>& appMap, const AceType* data)
{
    const std::string closeBrace = ")";
    const std::string openBrace = "(";
    std::string ans;
    std::string tempStack = stackStr;
    // find per line of stack
    std::vector<std::string> res;
    ExtractEachInfo(tempStack, res);

    std::string runningPageTag = "app_.js";
    auto appFlag = static_cast<int32_t>(tempStack.find(runningPageTag));
    bool isAppPage = appFlag > 0 && appMap;
    if (!isAppPage) {
        std::string tag = std::as_const(pageUrl);
        std::string str = tag;
        if (res[0].find('/') == std::string::npos) {
            replace(str.begin(), str.end(), '/', '\\');
        }
        char* ch = strrchr((char*)str.c_str(), '.');
        if (ch != nullptr) {
            int index = ch - str.c_str();
            str.insert(index, "_");
        }
        runningPageTag = str;
    }

    // collect error info first
    for (uint32_t i = 0; i < res.size(); i++) {
        std::string temp = res[i];
        if (temp.rfind(runningPageTag) == std::string::npos) {
            continue;
        }
        auto closeBracePos = static_cast<int32_t>(temp.find(closeBrace));
        auto openBracePos = static_cast<int32_t>(temp.find(openBrace));

        std::string line;
        std::string column;
        GetPosInfo(temp, closeBracePos, line, column);
        if (line.empty() || column.empty()) {
            break;
        }

        const std::string sourceInfo = GetSourceInfo(line, column, pageMap, appMap, isAppPage, data);
        if (sourceInfo.empty()) {
            break;
        }
        temp.replace(openBracePos, closeBracePos - openBracePos + 1, sourceInfo);
        replace(temp.begin(), temp.end(), '\\', '/');
        ans = ans + temp + "\n";
    }
    if (ans.empty()) {
        return tempStack;
    }
    return ans;
}

std::string JsiBaseUtils::TranslateBySourceMap(const std::string& stackStr, const std::string& pageUrl,
    const std::unordered_map<std::string, RefPtr<RevSourceMap>>& sourceMaps, const RefPtr<RevSourceMap>& appMap,
    const AceType* data)
{
    const std::string closeBrace = ")";
    const std::string openBrace = "(";
    std::string ans;
    std::string tempStack = stackStr;
    std::string runningPageTag = "app_.js";
    bool isAppPage = static_cast<int32_t>(tempStack.find(runningPageTag)) > 0 && appMap;
    if (!isAppPage) {
        std::string tag = std::as_const(pageUrl);
        char* ch = strrchr((char*)tag.c_str(), '.');
        if (ch != nullptr) {
            tag.insert(static_cast<int>(ch - tag.c_str()), "_");
        }
        runningPageTag = tag;
    }
    // find per line of stack
    std::vector<std::string> res;
    ExtractEachInfo(tempStack, res);

    // collect error info first
    for (uint32_t i = 0; i < res.size(); i++) {
        std::string temp = res[i];
        uint32_t start = temp.find(openBrace);
        uint32_t end = temp.find(":");
        if (temp.empty() || end < start + 1) {
            break;
        }
        std::string key = temp.substr(start + 1, end - start - 1);
        auto closeBracePos = static_cast<int32_t>(temp.find(closeBrace));
        auto openBracePos = static_cast<int32_t>(temp.find(openBrace));
        std::string line;
        std::string column;
        GetPosInfo(temp, closeBracePos, line, column);
        if (line.empty() || column.empty()) {
            break;
        }
        std::string sourceInfo;
        auto iter = sourceMaps.find(key);
        if (iter != sourceMaps.end()) {
            sourceInfo = GetSourceInfo(line, column, iter->second, appMap, isAppPage, data, false);
        }
        if (sourceInfo.empty()) {
            break;
        }
        temp.replace(openBracePos, closeBracePos - openBracePos + 1, sourceInfo);
        replace(temp.begin(), temp.end(), '\\', '/');
        ans = ans + temp + "\n";
    }
    if (ans.empty()) {
        return tempStack;
    }
    return ans;
}

void JsiBaseUtils::ExtractEachInfo(const std::string& tempStack, std::vector<std::string>& res)
{
    std::string tempStr;
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
    const RefPtr<RevSourceMap>& pageMap, const RefPtr<RevSourceMap>& appMap, bool isAppPage, const AceType* data,
    const bool isBundle)
{
    int32_t offSet = GetLineOffset(data);
    std::string sourceInfo;
    MappingInfo mapInfo;
    if (isAppPage) {
        CHECK_NULL_RETURN(appMap, "");
        mapInfo = appMap->Find(StringToInt(line) - offSet, StringToInt(column));
    } else {
        CHECK_NULL_RETURN(pageMap, "");
        mapInfo = pageMap->Find(StringToInt(line) - offSet, StringToInt(column));
    }
    if (mapInfo.row == 0 || mapInfo.col == 0) {
        return "";
    }

    std::string sources = isBundle ? GetRelativePath(mapInfo.sources) : mapInfo.sources;
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
    return sources;
}

void JsiBaseUtils::ReportJsErrorEvent(std::shared_ptr<JsValue> error, std::shared_ptr<JsRuntime> runtime)
{
    if (!runtime) {
        LOGI("ReportJsErrorEvent: jsi engine has been destroyed");
        return;
    }

    auto arkJSRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    if (arkJSRuntime && arkJSRuntime->GetErrorEventHandler()) {
        std::string msg = GenerateErrorMsg(error, runtime);
        LOGI("Handle error event, errMsg: \n%{public}s", msg.c_str());
        arkJSRuntime->GetErrorEventHandler()(JS_CRASH_CODE, msg);
        return;
    }
    auto errorInfo = GenerateJsErrorObject(error, runtime);

    std::string summaryBody = GenerateSummaryBody(error, runtime);
    LOGE("summaryBody: \n%{public}s", summaryBody.c_str());
    EventReport::JsErrReport(AceApplicationInfo::GetInstance().GetPackageName(), errorInfo.name, summaryBody);
#if !defined(ANDROID_PLATFORM) && !defined(IOS_PLATFORM)
    ExceptionHandler::HandleJsException(summaryBody, errorInfo);
#endif
}

std::string ParseLogContent(const std::vector<std::string>& params)
{
    std::string ret;
    int32_t flag = 0;
    if (params.empty()) {
        return ret;
    }
    std::string formatStr = params[0];
    auto size = static_cast<int32_t>(params.size());
    auto len = static_cast<int32_t>(formatStr.size());
    int32_t pos = 0;
    int32_t count = 1;
    for (; pos < len; ++pos) {
        if (count >= size) {
            break;
        }
        if (formatStr[pos] == '%') {
            flag = 1;
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
    switch (flag) {
        case 0:
            ret += " ";
            for (int32_t i = 1; i < size; ++i) {
                ret += params[i];
                if (i != size - 1) {
                    ret += " ";
                }
            }
            break;
        case 1:
            for (int32_t i = 2; i < size; ++i) {
                ret += params[i];
            }
            break;
        default:
            break;
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
    params.reserve(argc);
    for (int32_t i = 0; i < argc; ++i) {
        params.emplace_back(argv[i]->ToString(runtime));
    }
    return ParseLogContent(params);
}

// parse log content from startIndex to end
std::string GetLogContentFromStartIndex(
    const shared_ptr<JsRuntime>& runtime, const std::vector<shared_ptr<JsValue>>& argv,
    int32_t argc, int32_t startIndex)
{
    if (argc < startIndex + 1) {
        return "";
    } else if (argc == startIndex + 1) {
        return argv[startIndex]->ToString(runtime);
    }
    std::vector<std::string> params;
    params.reserve(argc);
    for (int32_t i = startIndex; i < argc; ++i) {
        params.emplace_back(argv[i]->ToString(runtime));
    }
    return ParseLogContent(params);
}

// parse log tag when the first arg is tag
bool GetLogTag(
    const shared_ptr<JsRuntime>& runtime, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc, AceLogTag& tag)
{
    if (argc < 1) {
        return false;
    }
    auto tagNum = argv[0]->ToInt32(runtime);
    switch (tagNum) {
        case 0:
            tag = AceLogTag::ACE_STATE_MGMT;
            break;
        case 1:
            tag = AceLogTag::ACE_ARK_COMPONENT;
            break;
        default:
            tag = AceLogTag::ACE_DEFAULT_DOMAIN;
            break;
    }
    return true;
}

shared_ptr<JsValue> AppLogPrint(
    const shared_ptr<JsRuntime>& runtime, JsLogLevel level, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    // Should have at least 1 parameters.
    if (argc == 0) {
        return runtime->NewUndefined();
    }
    std::string content = GetLogContent(runtime, argv, argc);
    switch (level) {
        case JsLogLevel::DEBUG:
            APP_LOGD("%{public}s", content.c_str());
            break;
        case JsLogLevel::INFO:
            APP_LOGI("%{public}s", content.c_str());
            break;
        case JsLogLevel::WARNING:
            APP_LOGW("%{public}s", content.c_str());
            break;
        case JsLogLevel::ERROR:
            APP_LOGE("%{public}s", content.c_str());
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
        return runtime->NewUndefined();
    }

    AceLogTag tag;
    std::string content;
    auto getTagSuccess = GetLogTag(runtime, argv, argc, tag);
    if (getTagSuccess) {
        content = GetLogContentFromStartIndex(runtime, argv, argc, 1);
    }
    switch (level) {
        case JsLogLevel::DEBUG:
            TAG_LOGD(tag, "%{public}s", content.c_str());
            break;
        case JsLogLevel::INFO:
            TAG_LOGI(tag, "%{public}s", content.c_str());
            break;
        case JsLogLevel::WARNING:
            TAG_LOGW(tag, "%{public}s", content.c_str());
            break;
        case JsLogLevel::ERROR:
            TAG_LOGE(tag, "%{public}s", content.c_str());
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
    return JsLogPrint(runtime, JsLogLevel::DEBUG, argv, argc);
}

shared_ptr<JsValue> JsiBaseUtils::JsInfoLogPrint(const shared_ptr<JsRuntime>& runtime,
    const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    return JsLogPrint(runtime, JsLogLevel::INFO, argv, argc);
}

shared_ptr<JsValue> JsiBaseUtils::JsWarnLogPrint(const shared_ptr<JsRuntime>& runtime,
    const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    return JsLogPrint(runtime, JsLogLevel::WARNING, argv, argc);
}

shared_ptr<JsValue> JsiBaseUtils::JsErrorLogPrint(const shared_ptr<JsRuntime>& runtime,
    const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    return JsLogPrint(runtime, JsLogLevel::ERROR, argv, argc);
}

thread_local std::stack<std::unique_ptr<AceScopedTrace>> JsiBaseUtils::aceScopedTrace_;

shared_ptr<JsValue> JsiBaseUtils::JsTraceBegin(const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& thisObj,
    const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    if (SystemProperties::GetDebugEnabled()) {
        std::string traceName = GetLogContent(runtime, argv, argc);
        aceScopedTrace_.emplace(std::make_unique<AceScopedTrace>(traceName.c_str()));
    }
    return runtime->NewUndefined();
}

shared_ptr<JsValue> JsiBaseUtils::JsTraceEnd(const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& thisObj,
    const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    if (!aceScopedTrace_.empty() && SystemProperties::GetDebugEnabled()) {
        aceScopedTrace_.pop();
    }
    return runtime->NewUndefined();
}

std::string GetLogContent(napi_env env, napi_callback_info info)
{
    size_t argc = 0;
    napi_value* argv = nullptr;
    napi_value thisVar = nullptr;
    void* data = nullptr;
    napi_get_cb_info(env, info, &argc, nullptr, nullptr, nullptr);
    if (argc > 0) {
        argv = new napi_value[argc];
    }
    napi_get_cb_info(env, info, &argc, argv, &thisVar, &data);

    std::string content;
    napi_valuetype valueType = napi_undefined;
    for (size_t i = 0; i < argc; ++i) {
        napi_typeof(env, argv[i], &valueType);
        if (valueType != napi_string) {
            continue;
        }
        size_t buffSize = 0;
        napi_status status = napi_get_value_string_utf8(env, argv[i], nullptr, 0, &buffSize);
        if (status != napi_ok || buffSize == 0) {
            continue;
        }
        std::unique_ptr<char[]> paramsChar = std::make_unique<char[]>(buffSize + 1);
        size_t ret = 0;
        napi_get_value_string_utf8(env, argv[i], paramsChar.get(), buffSize + 1, &ret);
        content.append(paramsChar.get());
    }
    delete[] argv;
    return content;
}

napi_value AppLogPrint(napi_env env, napi_callback_info info, JsLogLevel level)
{
    // Should have at least 1 parameters.
    napi_value result = nullptr;
    std::string content = GetLogContent(env, info);
    switch (level) {
        case JsLogLevel::DEBUG:
            APP_LOGD("%{public}s", content.c_str());
            break;
        case JsLogLevel::INFO:
            APP_LOGI("%{public}s", content.c_str());
            break;
        case JsLogLevel::WARNING:
            APP_LOGW("%{public}s", content.c_str());
            break;
        case JsLogLevel::ERROR:
            APP_LOGE("%{public}s", content.c_str());
            break;
    }

    return result;
}

napi_value AppDebugLogPrint(napi_env env, napi_callback_info info)
{
    return AppLogPrint(env, info, JsLogLevel::DEBUG);
}

napi_value AppInfoLogPrint(napi_env env, napi_callback_info info)
{
    return AppLogPrint(env, info, JsLogLevel::INFO);
}

napi_value AppWarnLogPrint(napi_env env, napi_callback_info info)
{
    return AppLogPrint(env, info, JsLogLevel::WARNING);
}

napi_value AppErrorLogPrint(napi_env env, napi_callback_info info)
{
    return AppLogPrint(env, info, JsLogLevel::ERROR);
}

void JsiBaseUtils::GetStageSourceMap(
    const AceType* data, std::unordered_map<std::string, RefPtr<Framework::RevSourceMap>>& sourceMaps)
{
    auto delegate = GetDelegate(data);
    std::string maps;
    if (delegate != nullptr && delegate->GetAssetContent(MERGE_SOURCEMAPS_PATH, maps)) {
        auto SourceMap = AceType::MakeRefPtr<RevSourceMap>();
        SourceMap->StageModeSourceMapSplit(maps, sourceMaps);
    } else {
        LOGW("GetRunningPage SourceMap load failed!");
    }
}
} // namespace OHOS::Ace::Framework
