/*
 * Copyright (C) 2024 Huawei Device Co., Ltd.
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

#include "core/common/ai/data_detector_adapter.h"

#include "adapter/ohos/entrance/ace_container.h"
#include "core/common/ai/data_detector_mgr.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace {

constexpr int32_t AI_TEXT_MAX_LENGTH = 500;
constexpr int32_t AI_TEXT_GAP = 100;
constexpr int32_t AI_DELAY_TIME = 100;
constexpr uint32_t SECONDS_TO_MILLISECONDS = 1000;

const std::unordered_map<TextDataDetectType, std::string> TEXT_DETECT_MAP = {
    { TextDataDetectType::PHONE_NUMBER, "phoneNum" }, { TextDataDetectType::URL, "url" },
    { TextDataDetectType::EMAIL, "email" }, { TextDataDetectType::ADDRESS, "location" },
    { TextDataDetectType::DATE_TIME, "datetime" }
};
const std::unordered_map<std::string, TextDataDetectType> TEXT_DETECT_MAP_REVERSE = {
    { "phoneNum", TextDataDetectType::PHONE_NUMBER }, { "url", TextDataDetectType::URL },
    { "email", TextDataDetectType::EMAIL }, { "location", TextDataDetectType::ADDRESS },
    { "datetime", TextDataDetectType::DATE_TIME }
};

void DataDetectorAdapter::GetAIEntityMenu()
{
    auto context = PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_VOID(context);
    auto uiTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
    uiTaskExecutor.PostTask(
        [weak = AceType::WeakClaim(this), instanceId = context->GetInstanceId()] {
            ContainerScope scope(instanceId);
            auto dataDetectorAdapter = weak.Upgrade();
            CHECK_NULL_VOID(dataDetectorAdapter);
            TAG_LOGI(AceLogTag::ACE_TEXT, "Get AI entity menu from ai_engine");
            DataDetectorMgr::GetInstance().GetAIEntityMenu(dataDetectorAdapter->textDetectResult_);
        },
        "ArkUITextInitDataDetect");
}

bool DataDetectorAdapter::ShowAIEntityMenu(const AISpan& aiSpan, const NG::RectF& aiRect,
    const RefPtr<NG::FrameNode>& targetNode, bool isShowCopy, bool isShowSelectText)
{
    if (textDetectResult_.menuOptionAndAction.empty()) {
        TAG_LOGW(AceLogTag::ACE_TEXT, "menu option is empty, please try again");
        GetAIEntityMenu();
        return false;
    }

    mainContainerId_ = Container::CurrentId();
    std::vector<std::pair<std::string, std::function<void()>>> menuOptions;
    auto menuOptionAndAction = textDetectResult_.menuOptionAndAction[TEXT_DETECT_MAP.at(aiSpan.type)];
    if (menuOptionAndAction.empty()) {
        return false;
    }
    if (!isShowSelectText) {
        // delete the last option: selectText.
        menuOptionAndAction.pop_back();
        if (!isShowCopy) {
        // delete the last option: copy.
            menuOptionAndAction.pop_back();
        }
    }

    for (auto menuOption : menuOptionAndAction) {
        std::function<void()> onClickEvent = [aiSpan, menuOption, weak = AceType::WeakClaim(this),
                                                 targetNodeWeak = AceType::WeakClaim(AceType::RawPtr(targetNode))]() {
            auto dataDetectorAdapter = weak.Upgrade();
            CHECK_NULL_VOID(dataDetectorAdapter);
            auto targetNode = targetNodeWeak.Upgrade();
            CHECK_NULL_VOID(targetNode);
            dataDetectorAdapter->OnClickAIMenuOption(aiSpan, menuOption, targetNode);
        };
        menuOptions.push_back(std::make_pair(menuOption.first, onClickEvent));
    }
    auto pipeline = NG::PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_RETURN(pipeline, false);
    auto overlayManager = pipeline->GetOverlayManager();
    CHECK_NULL_RETURN(overlayManager, false);
    return overlayManager->ShowAIEntityMenu(menuOptions, aiRect, targetNode);
}

void DataDetectorAdapter::OnClickAIMenuOption(const AISpan& aiSpan,
    const std::pair<std::string, FuncVariant>& menuOption, const RefPtr<NG::FrameNode>& targetNode)
{
    TAG_LOGI(AceLogTag::ACE_TEXT, "Click AI menu option: %{public}s", menuOption.first.c_str());
    auto pipeline = NG::PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_VOID(pipeline);
    auto overlayManager = pipeline->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    if (targetNode) {
        overlayManager->CloseAIEntityMenu(targetNode->GetId());
    }
    Container::UpdateCurrent(mainContainerId_);

    auto runtimeContext = Platform::AceContainer::GetRuntimeContext(pipeline->GetInstanceId());
    CHECK_NULL_VOID(runtimeContext);
    auto token = runtimeContext->GetToken();
    auto bundleName = runtimeContext->GetBundleName();

    hasClickedMenuOption_ = true;
    if (onClickMenu_ && std::holds_alternative<std::function<std::string()>>(menuOption.second)) {
        onClickMenu_(std::get<std::function<std::string()>>(menuOption.second)());
    } else if (std::holds_alternative<std::function<void(sptr<IRemoteObject>, std::string)>>(menuOption.second)) {
        std::get<std::function<void(sptr<IRemoteObject>, std::string)>>(menuOption.second)(token, aiSpan.content);
    } else if (std::holds_alternative<std::function<void(int32_t, std::string)>>(menuOption.second)) {
        std::get<std::function<void(int32_t, std::string)>>(menuOption.second)(mainContainerId_, aiSpan.content);
    } else if (std::holds_alternative<std::function<void(int32_t, std::string, std::string, int32_t, std::string)>>(
                   menuOption.second)) {
        std::get<std::function<void(int32_t, std::string, std::string, int32_t, std::string)>>(menuOption.second)(
            mainContainerId_, textForAI_, bundleName, aiSpan.start, aiSpan.content);
    } else {
        TAG_LOGW(AceLogTag::ACE_TEXT, "No matching menu option");
    }
    hasClickedMenuOption_ = false;
}

void DataDetectorAdapter::ResponseBestMatchItem(const AISpan& aiSpan)
{
    if (textDetectResult_.menuOptionAndAction.empty()) {
        TAG_LOGW(AceLogTag::ACE_TEXT, "menu option is empty, please try again");
        GetAIEntityMenu();
        return;
    }
    auto menuOptions = textDetectResult_.menuOptionAndAction[TEXT_DETECT_MAP.at(aiSpan.type)];
    if (menuOptions.empty()) {
        TAG_LOGW(AceLogTag::ACE_TEXT, "menu option is empty");
        return;
    }
    OnClickAIMenuOption(aiSpan, menuOptions[0]);
}

void DataDetectorAdapter::SetTextDetectTypes(const std::string& types)
{
    textDetectTypes_ = types;

    std::set<std::string> newTypesSet;
    std::istringstream iss(types);
    std::string type;
    while (std::getline(iss, type, ',')) {
        newTypesSet.insert(type);
    }
    if (newTypesSet != textDetectTypesSet_) {
        textDetectTypesSet_ = newTypesSet;
        typeChanged_ = true;
        aiDetectInitialized_ = false;
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        host->MarkDirtyNode(NG::PROPERTY_UPDATE_MEASURE);
    }
}

bool DataDetectorAdapter::ParseOriText(const std::unique_ptr<JsonValue>& entityJson, std::string& text)
{
    TAG_LOGI(AceLogTag::ACE_TEXT, "Parse origin text entry");
    auto runtimeContext = Platform::AceContainer::GetRuntimeContext(Container::CurrentId());
    CHECK_NULL_RETURN(runtimeContext, false);
    if (runtimeContext->GetBundleName() != entityJson->GetString("bundleName")) {
        TAG_LOGW(AceLogTag::ACE_TEXT,
            "Wrong bundleName, the context bundleName is: %{public}s, but your bundleName is: %{public}s",
            runtimeContext->GetBundleName().c_str(), entityJson->GetString("bundleName").c_str());
        return false;
    }
    auto aiSpanArray = entityJson->GetValue("entity");
    if (aiSpanArray->IsNull() || !aiSpanArray->IsArray()) {
        TAG_LOGW(AceLogTag::ACE_TEXT, "Wrong AI entity");
        return false;
    }

    aiSpanMap_.clear();
    aiSpanRects_.clear();
    detectTexts_.clear();
    AISpan aiSpan;
    for (int32_t i = 0; i < aiSpanArray->GetArraySize(); ++i) {
        auto item = aiSpanArray->GetArrayItem(i);
        aiSpan.content = item->GetString("entityContent");
        aiSpan.type = TEXT_DETECT_MAP_REVERSE.at(item->GetString("entityType"));
        aiSpan.start = item->GetInt("start");
        aiSpan.end = item->GetInt("end");
        aiSpanMap_[aiSpan.start] = aiSpan;
    }
    aiDetectInitialized_ = true;
    text = entityJson->GetString("content");
    textForAI_ = text;
    lastTextForAI_ = textForAI_;
    if (textDetectResult_.menuOptionAndAction.empty()) {
        GetAIEntityMenu();
    }

    TAG_LOGI(AceLogTag::ACE_TEXT, "Parse origin text successful");
    return true;
}

void DataDetectorAdapter::InitTextDetect(int32_t startPos, std::string detectText)
{
    TextDataDetectInfo info;
    info.text = detectText;
    info.module = textDetectTypes_;

    auto context = PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_VOID(context);
    int32_t instanceID = context->GetInstanceId();
    auto textFunc = [weak = WeakClaim(this), instanceID, startPos, info](const TextDataDetectResult result) {
        ContainerScope scope(instanceID);
        auto context = PipelineContext::GetCurrentContextSafely();
        CHECK_NULL_VOID(context);
        auto uiTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
        uiTaskExecutor.PostTask(
            [result, weak, instanceID, startPos, info] {
                ContainerScope scope(instanceID);
                auto dataDetectorAdapter = weak.Upgrade();
                CHECK_NULL_VOID(dataDetectorAdapter);
                if (info.module != dataDetectorAdapter->textDetectTypes_) {
                    return;
                }
                dataDetectorAdapter->ParseAIResult(result, startPos);
                auto host = dataDetectorAdapter->GetHost();
                CHECK_NULL_VOID(host);
                host->MarkDirtyNode(NG::PROPERTY_UPDATE_MEASURE);
            },
            "ArkUITextParseAIResult");
    };

    auto uiTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::BACKGROUND);
    uiTaskExecutor.PostTask(
        [info, textFunc] {
            TAG_LOGI(AceLogTag::ACE_TEXT, "Start entity detect using AI");
            DataDetectorMgr::GetInstance().DataDetect(info, textFunc);
        },
        "ArkUITextInitDataDetect");
}

void DataDetectorAdapter::ParseAIResult(const TextDataDetectResult& result, int32_t startPos)
{
    auto entityJson = JsonUtil::ParseJsonString(result.entity);
    CHECK_NULL_VOID(entityJson);
    for (const auto& type : TEXT_DETECT_MAP) {
        auto jsonValue = entityJson->GetValue(type.second);
        ParseAIJson(jsonValue, type.first, startPos);
    }

    if (startPos + AI_TEXT_MAX_LENGTH >= static_cast<int32_t>(StringUtils::ToWstring(textForAI_).length())) {
        aiDetectInitialized_ = true;
        auto entityJsonArray = JsonUtil::CreateArray(true);
        // process with overlapping entities, leaving only the earlier ones
        int32_t preEnd = 0;
        auto aiSpanIterator = aiSpanMap_.begin();
        while (aiSpanIterator != aiSpanMap_.end()) {
            auto aiSpan = aiSpanIterator->second;
            if (aiSpan.start < preEnd) {
                aiSpanIterator = aiSpanMap_.erase(aiSpanIterator);
            } else {
                preEnd = aiSpan.end;
                ++aiSpanIterator;
                auto aiSpanJson = JsonUtil::Create(true);
                aiSpanJson->Put("start", aiSpan.start);
                aiSpanJson->Put("end", aiSpan.end);
                aiSpanJson->Put("entityContent", aiSpan.content.c_str());
                aiSpanJson->Put("entityType", TEXT_DETECT_MAP.at(aiSpan.type).c_str());
                entityJsonArray->Put(aiSpanJson);
            }
        }
        auto resultJson = JsonUtil::Create(true);
        resultJson->Put("entity", entityJsonArray);
        resultJson->Put("code", result.code);
        SetTextDetectResult(result);
        FireOnResult(resultJson->ToString());
    }
}

void DataDetectorAdapter::ParseAIJson(
    const std::unique_ptr<JsonValue>& jsonValue, TextDataDetectType type, int32_t startPos)
{
    if (!jsonValue || !jsonValue->IsArray()) {
        TAG_LOGW(AceLogTag::ACE_TEXT, "Wrong AI result");
        return;
    }

    for (int32_t i = 0; i < jsonValue->GetArraySize(); ++i) {
        auto item = jsonValue->GetArrayItem(i);
        auto charOffset = item->GetInt("charOffset");
        auto oriText = item->GetString("oriText");
        auto wTextForAI = StringUtils::ToWstring(textForAI_);
        auto wOriText = StringUtils::ToWstring(oriText);
        int32_t end = startPos + charOffset + static_cast<int32_t>(wOriText.length());
        if (charOffset < 0 || startPos + charOffset >= static_cast<int32_t>(wTextForAI.length()) ||
            end >= startPos + AI_TEXT_MAX_LENGTH || oriText.empty()) {
            TAG_LOGW(AceLogTag::ACE_TEXT, "The result of AI is wrong");
            continue;
        }
        if (oriText !=
            StringUtils::ToString(wTextForAI.substr(startPos + charOffset, static_cast<int32_t>(wOriText.length())))) {
            TAG_LOGW(AceLogTag::ACE_TEXT, "The charOffset is wrong");
            continue;
        }
        int32_t start = startPos + charOffset;
        auto iter = aiSpanMap_.find(start);
        if (iter != aiSpanMap_.end() && iter->second.content.length() >= oriText.length()) {
            // both entities start at the same position, leaving the longer one
            continue;
        }

        TimeStamp currentDetectorTimeStamp = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float, std::ratio<1, SECONDS_TO_MILLISECONDS>> costTime =
            currentDetectorTimeStamp - startDetectorTimeStamp_;
        item->Put("costTime", costTime.count());
        item->Put("resultCode", textDetectResult_.code);
        entityJson_[start] = item->ToString();
        TAG_LOGI(AceLogTag::ACE_TEXT, "The json of the entity is: %{private}s", entityJson_[start].c_str());

        AISpan aiSpan;
        aiSpan.start = start;
        aiSpan.end = end;
        aiSpan.content = oriText;
        aiSpan.type = type;
        aiSpanMap_[aiSpan.start] = aiSpan;
    }
}

std::function<void()> DataDetectorAdapter::GetDetectDelayTask(const std::map<int32_t, AISpan>& aiSpanMap)
{
    return [aiSpanMap, weak = WeakClaim(this)]() {
        auto dataDetectorAdapter = weak.Upgrade();
        CHECK_NULL_VOID(dataDetectorAdapter);
        if (dataDetectorAdapter->textForAI_.empty()) {
            return;
        }

        size_t detectTextIdx = 0;
        auto aiSpanMapIt = aiSpanMap.begin();
        int32_t startPos = 0;
        bool hasSame = false;
        auto wTextForAI = StringUtils::ToWstring(dataDetectorAdapter->textForAI_);
        auto wTextForAILength = static_cast<int32_t>(wTextForAI.length());
        do {
            std::string detectText = StringUtils::ToString(
                wTextForAI.substr(startPos, std::min(AI_TEXT_MAX_LENGTH, wTextForAILength - startPos)));
            bool isSameDetectText = detectTextIdx < dataDetectorAdapter->detectTexts_.size() &&
                                    detectText == dataDetectorAdapter->detectTexts_[detectTextIdx];
            while (!aiSpanMap.empty() && aiSpanMapIt != aiSpanMap.end() && aiSpanMapIt->first >= 0 &&
                   aiSpanMapIt->first < std::min(wTextForAILength, startPos + AI_TEXT_MAX_LENGTH - AI_TEXT_GAP)) {
                auto aiContent = aiSpanMapIt->second.content;
                auto wAIContent = StringUtils::ToWstring(aiContent);
                if (isSameDetectText || aiContent == StringUtils::ToString(wTextForAI.substr(aiSpanMapIt->first,
                    std::min(static_cast<int32_t>(wAIContent.length()), wTextForAILength - aiSpanMapIt->first)))) {
                    dataDetectorAdapter->aiSpanMap_[aiSpanMapIt->first] = aiSpanMapIt->second;
                    hasSame = true;
                }
                ++aiSpanMapIt;
            }
            if (!isSameDetectText) {
                dataDetectorAdapter->InitTextDetect(startPos, detectText);
                if (detectTextIdx < dataDetectorAdapter->detectTexts_.size()) {
                    dataDetectorAdapter->detectTexts_[detectTextIdx] = detectText;
                } else {
                    dataDetectorAdapter->detectTexts_.emplace_back(detectText);
                }
            }
            ++detectTextIdx;
            startPos += AI_TEXT_MAX_LENGTH - AI_TEXT_GAP;
        } while (startPos + AI_TEXT_GAP < wTextForAILength);
        if (hasSame) {
            auto host = dataDetectorAdapter->GetHost();
            CHECK_NULL_VOID(host);
            host->MarkDirtyNode(NG::PROPERTY_UPDATE_MEASURE);
        }
    };
}

void DataDetectorAdapter::StartAITask()
{
    if (textForAI_.empty() || (!typeChanged_ && lastTextForAI_ == textForAI_)) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        host->MarkDirtyNode(NG::PROPERTY_UPDATE_MEASURE);
        return;
    }
    std::map<int32_t, AISpan> aiSpanMapCopy;
    if (!typeChanged_) {
        aiSpanMapCopy = aiSpanMap_;
    } else {
        detectTexts_.clear();
    }
    aiSpanMap_.clear();
    typeChanged_ = false;
    lastTextForAI_ = textForAI_;
    startDetectorTimeStamp_ = std::chrono::high_resolution_clock::now();
    auto context = PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_VOID(context);
    auto taskExecutor = context->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    aiDetectDelayTask_.Cancel();
    aiDetectDelayTask_.Reset(GetDetectDelayTask(aiSpanMapCopy));
    taskExecutor->PostDelayedTask(
        aiDetectDelayTask_, TaskExecutor::TaskType::UI, AI_DELAY_TIME, "ArkUITextStartAIDetect");
}
} // namespace OHOS::Ace
