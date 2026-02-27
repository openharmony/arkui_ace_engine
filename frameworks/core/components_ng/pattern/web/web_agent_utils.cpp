/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/web/web_agent_utils.h"

#include <algorithm>

#include "nweb_hisysevent.h"

#include "base/log/event_report.h"
#include "base/log/log.h"
#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/components_ng/pattern/web/web_dom_document.h"

namespace OHOS::Ace::NG {

bool WebAgentUtils::IsNumber(const std::string& str)
{
    if (str.empty()) {
        return false;
    }
    return std::all_of(str.begin(), str.end(), [](char c) { return std::isdigit(static_cast<unsigned char>(c)); });
}

std::unique_ptr<JsonValue> WebAgentUtils::ValidateHighlightResultJson(const std::string& resultJson)
{
    if (resultJson.empty()) {
        return nullptr;
    }

    auto sourceJson = JsonUtil::ParseJsonString(resultJson);
    auto arrayJson = JsonUtil::ParseJsonString(sourceJson->GetString());
    if (arrayJson && arrayJson->IsArray() && arrayJson->GetArraySize()) {
        return arrayJson;
    }

    return nullptr;
}

WebAgentUtils::HighlightErrorItem WebAgentUtils::ParseHighlightErrorItem(const std::unique_ptr<JsonValue>& item)
{
    WebAgentUtils::HighlightErrorItem result;

    auto typeValue = item->GetValue("type");
    if (typeValue && typeValue->IsNumber()) {
        int32_t typeValueInt = typeValue->GetInt();
        if (IsValidHighlightErrorType(typeValueInt)) {
            result.type = static_cast<HighlightErrorType>(typeValueInt);
        }
    }

    auto indexValue = item->GetValue("index");
    if (indexValue && indexValue->IsNumber()) {
        int64_t indexValueInt64 = indexValue->GetInt64();
        if (indexValueInt64 >= INT32_MIN && indexValueInt64 <= INT32_MAX) {
            result.index = static_cast<int32_t>(indexValueInt64);
        }
    }

    auto contentValue = item->GetValue("content");
    if (contentValue && contentValue->IsString()) {
        result.content = contentValue->GetString();
    }

    auto messageValue = item->GetValue("message");
    if (messageValue && messageValue->IsString()) {
        result.message = messageValue->GetString();
    }

    return result;
}

std::string WebAgentUtils::GetErrorNodeFromIndex(int32_t index, const std::vector<std::string>& Xpaths)
{
    std::string errorNode;
    if (index >= 0 && index < static_cast<int32_t>(Xpaths.size())) {
        const std::string& Xpath = Xpaths[index];
        errorNode = Xpath;
    }
    return errorNode;
}

std::string WebAgentUtils::ConvertErrorTypeToString(HighlightErrorType typeError)
{
    switch (typeError) {
        case HighlightErrorType::SUCCESS:
            return "SUCCESS";
        case HighlightErrorType::XPATH_ERROR:
            return "XPATH_ERROR";
        case HighlightErrorType::NODE_NOT_FOUND:
            return "NODE_NOT_FOUND";
        case HighlightErrorType::TEXT_NOT_MATCH:
            return "TEXT_NOT_MATCH";
        case HighlightErrorType::UNKNOWN:
        default:
            return "UNKNOWN";
    }
}

void WebAgentUtils::ReportHighlightErrorEvent(
    const WebAgentUtils::HighlightErrorItem& item, const std::string& errorNode)
{
    std::string eventType = "HIGHLIGHT_SPECIFIED_CONTENT";
    std::string errorType = ConvertErrorTypeToString(item.type);

    TAG_LOGI(AceLogTag::ACE_WEB,
        "HighlightSpecifiedContent Report: errorType=%{public}s, content='%{public}s', message='%{public}s'",
        errorType.c_str(), item.content.c_str(), errorNode.c_str());
    NWeb::EventReport::ReportHighlightSpecifiedContentEvent(eventType, errorType, item.content, errorNode);
}

bool WebAgentUtils::ParseHighlightResult(const std::string& resultJson, const std::vector<std::string>& Xpaths)
{
    auto sourceJson = ValidateHighlightResultJson(resultJson);
    if (!sourceJson) {
        return false;
    }

    int32_t arraySize = sourceJson->GetArraySize();
    for (int32_t i = 0; i < arraySize; i++) {
        auto item = sourceJson->GetArrayItem(i);
        if (!item || item->IsNull()) {
            TAG_LOGE(AceLogTag::ACE_WEB, "HighlightSpecifiedContent: Failed to get array item at index %{public}d", i);
            continue;
        }

        WebAgentUtils::HighlightErrorItem errorItem = ParseHighlightErrorItem(item);

        std::string errorNode = GetErrorNodeFromIndex(errorItem.index, Xpaths);

        ReportHighlightErrorEvent(errorItem, errorNode);
    }

    return true;
}

} // namespace OHOS::Ace::NG
