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

#include "interfaces/inner_api/ace/modal_ui_extension_config.h"
#include "want.h"

#include "adapter/ohos/entrance/ace_container.h"
#include "base/log/log_wrapper.h"
#include "bridge/common/utils/engine_helper.h"
#include "core/common/ai/data_detector_mgr.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_model_ng.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace {

constexpr int32_t AI_TEXT_MAX_LENGTH = 500;
constexpr int32_t AI_TEXT_GAP = 100;
constexpr int32_t AI_DELAY_TIME = 100;
const std::pair<std::string, std::string> UI_EXTENSION_TYPE = { "ability.want.params.uiExtensionType", "sys/commonUI" };
constexpr uint32_t SECONDS_TO_MILLISECONDS = 1000;
const std::unordered_map<TextDataDetectType, std::string> TEXT_DETECT_MAP = {
    { TextDataDetectType::PHONE_NUMBER, "phoneNum" }, { TextDataDetectType::URL, "url" },
    { TextDataDetectType::EMAIL, "email" }, { TextDataDetectType::ADDRESS, "location" },
    { TextDataDetectType::DATETIME, "datetime" }
};

bool DataDetectorAdapter::ShowUIExtensionMenu(
    const AISpan& aiSpan, NG::RectF aiRect, const RefPtr<NG::FrameNode>& targetNode)
{
    ModalUIExtensionCallbacks callbacks;
    callbacks.onResult = [onClickMenu = onClickMenu_](int32_t code, const AAFwk::Want& want) {
        TAG_LOGI(AceLogTag::ACE_UIEXTENSIONCOMPONENT, "UIExtension Ability onResult, code: %{public}d", code);
        auto action = want.GetStringParam("action");
        if (!action.empty() && onClickMenu) {
            onClickMenu(action);
        }
    };
    callbacks.onDestroy = []() { TAG_LOGI(AceLogTag::ACE_UIEXTENSIONCOMPONENT, "UIExtension Ability Destroy"); };
    callbacks.onError = [](int32_t code, const std::string& name, const std::string& message) {
        TAG_LOGE(AceLogTag::ACE_UIEXTENSIONCOMPONENT,
            "UIExtension Ability Error, code: %{public}d, name: %{public}s, message: %{public}s", code, name.c_str(),
            message.c_str());
    };
    callbacks.onRelease = [](int32_t code) {
        TAG_LOGI(AceLogTag::ACE_UIEXTENSIONCOMPONENT, "UIExtension Ability Release, code: %{public}d", code);
    };
    AAFwk::Want want;
    want.SetElementName(uiExtensionBundleName_, uiExtensionAbilityName_);
    SetWantParamaters(aiSpan, want);

    uiExtNode_ = NG::UIExtensionModelNG::Create(want, callbacks);
    CHECK_NULL_RETURN(uiExtNode_, false);
    auto onReceive = GetOnReceive(aiRect, targetNode);
    auto pattern = uiExtNode_->GetPattern<NG::UIExtensionPattern>();
    CHECK_NULL_RETURN(pattern, false);
    pattern->SetOnReceiveCallback(std::move(onReceive));
    uiExtNode_->MarkModifyDone();
    return true;
}

std::function<void(const AAFwk::WantParams&)> DataDetectorAdapter::GetOnReceive(
    NG::RectF aiRect, const RefPtr<NG::FrameNode>& targetNode)
{
    return [aiRect, weak = AceType::WeakClaim(this), targetNodeWeak = AceType::WeakClaim(AceType::RawPtr(targetNode))](
               const AAFwk::WantParams& wantParams) {
        TAG_LOGI(AceLogTag::ACE_UIEXTENSIONCOMPONENT, "UIExtension Ability onReceive");
        auto dataDetectorAdapter = weak.Upgrade();
        CHECK_NULL_VOID(dataDetectorAdapter);
        CHECK_NULL_VOID(dataDetectorAdapter->uiExtNode_);
        auto targetNode = targetNodeWeak.Upgrade();
        CHECK_NULL_VOID(targetNode);
        auto pipeline = NG::PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto overlayManager = pipeline->GetOverlayManager();
        CHECK_NULL_VOID(overlayManager);
        const std::string& action = wantParams.GetStringParam("action");
        if (!action.empty() && dataDetectorAdapter->onClickMenu_) {
            dataDetectorAdapter->onClickMenu_(action);
        }
        const std::string& abilityType = wantParams.GetStringParam("abilityType");
        if (!abilityType.empty()) {
            auto abilityParams = wantParams.GetWantParams("abilityParams");
            dataDetectorAdapter->StartAbilityByType(abilityType, abilityParams);
        }
        const std::string& closeMenu = wantParams.GetStringParam("closeMenu");
        if (closeMenu == "true") {
            overlayManager->CloseUIExtensionMenu(targetNode->GetId());
            return;
        }
        const std::string& longestContent = wantParams.GetStringParam("longestContent");
        const int32_t& menuSize = wantParams.GetIntParam("menuSize", -1);
        if (longestContent.empty() || menuSize == -1) {
            return;
        }
        overlayManager->ShowUIExtensionMenu(
            dataDetectorAdapter->uiExtNode_, aiRect, longestContent, menuSize, targetNode);
    };
}

void DataDetectorAdapter::StartAbilityByType(const std::string& type, AAFwk::WantParams& wantParams)
{
    auto pipeline = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto runtimeContext = Platform::AceContainer::GetRuntimeContext(pipeline->GetInstanceId());
    CHECK_NULL_VOID(runtimeContext);
    auto abilityContext = OHOS::AbilityRuntime::Context::ConvertTo<OHOS::AbilityRuntime::AbilityContext>(
        runtimeContext->shared_from_this());
    CHECK_NULL_VOID(abilityContext);

    auto engine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_VOID(engine);
    NativeEngine* nativaEngine = engine->GetNativeEngine();
    auto env = reinterpret_cast<napi_env>(nativaEngine);
    CHECK_NULL_VOID(env);
    std::shared_ptr<OHOS::AbilityRuntime::JsUIExtensionCallback> callback =
        std::make_shared<OHOS::AbilityRuntime::JsUIExtensionCallback>(env);
    abilityContext->StartAbilityByType(type, wantParams, callback);
}

void DataDetectorAdapter::ResponseBestMatchItem(const AISpan& aiSpan)
{
    ModalUIExtensionCallbacks callbacks;
    AAFwk::Want want;
    want.SetElementName(uiExtensionBundleName_, uiExtensionAbilityName_);
    SetWantParamaters(aiSpan, want);
    want.SetParam(std::string("clickType"), std::string("leftMouse"));
    auto uiExtNode = NG::UIExtensionModelNG::Create(want, callbacks);
    CHECK_NULL_VOID(uiExtNode);

    // Extend the lifecycle of the uiExtNode with callback
    auto onReceive = [uiExtNode] (const AAFwk::WantParams& wantParams) {};
    auto pattern = uiExtNode->GetPattern<NG::UIExtensionPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetOnReceiveCallback(std::move(onReceive));
}

void DataDetectorAdapter::SetWantParamaters(const AISpan& aiSpan, AAFwk::Want& want)
{
    want.SetParam("entityType", TEXT_DETECT_MAP.at(aiSpan.type));
    want.SetParam("entityText", aiSpan.content);
    want.SetParam(UI_EXTENSION_TYPE.first, UI_EXTENSION_TYPE.second);
    if (entityJson_.find(aiSpan.start) != entityJson_.end()) {
        want.SetParam("entityJson", entityJson_[aiSpan.start]);
    }
    if (aiSpan.type == TextDataDetectType::DATETIME) {
        want.SetParam("fullText", textForAI_);
        want.SetParam("offset", aiSpan.start);
    }
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

void DataDetectorAdapter::InitTextDetect(int32_t startPos, std::string detectText)
{
    TextDataDetectInfo info;
    info.text = detectText;
    info.module = textDetectTypes_;

    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    int32_t instanceID = context->GetInstanceId();
    auto textFunc = [weak = WeakClaim(this), instanceID, startPos, info](const TextDataDetectResult result) {
        ContainerScope scope(instanceID);
        auto dataDetectorAdapter = weak.Upgrade();
        CHECK_NULL_VOID(dataDetectorAdapter);
        auto host = dataDetectorAdapter->GetHost();
        CHECK_NULL_VOID(host);
        auto context = host->GetContext();
        CHECK_NULL_VOID(context);
        auto uiTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
        uiTaskExecutor.PostTask([result, weak, instanceID, startPos, info] {
            ContainerScope scope(instanceID);
            auto dataDetectorAdapter = weak.Upgrade();
            CHECK_NULL_VOID(dataDetectorAdapter);
            if (info.module != dataDetectorAdapter->textDetectTypes_) {
                return;
            }
            dataDetectorAdapter->SetTextDetectResult(result);
            dataDetectorAdapter->FireOnResult(result);
            if (result.code != 0) {
                TAG_LOGE(AceLogTag::ACE_TEXT, "Data detect error, error code: %{public}d", result.code);
                return;
            }
            dataDetectorAdapter->ParseAIResult(result, startPos);
            auto host = dataDetectorAdapter->GetHost();
            CHECK_NULL_VOID(host);
            host->MarkDirtyNode(NG::PROPERTY_UPDATE_MEASURE);
        }, "ArkUITextParseAIResult");
    };

    auto uiTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::BACKGROUND);
    uiTaskExecutor.PostTask([info, textFunc] {
        TAG_LOGI(AceLogTag::ACE_TEXT, "Start entity detect using AI");
        DataDetectorMgr::GetInstance().DataDetect(info, textFunc);
    }, "ArkUITextInitDataDetect");
}

void DataDetectorAdapter::ParseAIResult(const TextDataDetectResult& result, int32_t startPos)
{
    auto entityMenuServiceInfoJson = JsonUtil::ParseJsonString(result.entityMenuServiceInfo);
    CHECK_NULL_VOID(entityMenuServiceInfoJson);
    if (uiExtensionBundleName_.empty()) {
        uiExtensionBundleName_ = entityMenuServiceInfoJson->GetString("bundlename");
    }
    if (uiExtensionAbilityName_.empty()) {
        uiExtensionAbilityName_ = entityMenuServiceInfoJson->GetString("abilityname");
    }
    auto entityJson = JsonUtil::ParseJsonString(result.entity);
    CHECK_NULL_VOID(entityJson);
    for (const auto& type : TEXT_DETECT_MAP) {
        auto jsonValue = entityJson->GetValue(type.second);
        ParseAIJson(jsonValue, type.first, startPos);
    }

    if (startPos + AI_TEXT_MAX_LENGTH >= static_cast<int32_t>(StringUtils::ToWstring(textForAI_).length())) {
        aiDetectInitialized_ = true;
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
            }
        }
    }
}

void DataDetectorAdapter::ParseAIJson(
    const std::unique_ptr<JsonValue>& jsonValue, TextDataDetectType type, int32_t startPos)
{
    if (!jsonValue || !jsonValue->IsArray()) {
        TAG_LOGW(AceLogTag::ACE_TEXT, "Error AI Result.");
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
            TAG_LOGW(AceLogTag::ACE_TEXT, "The result of AI is error");
            continue;
        }
        if (oriText !=
            StringUtils::ToString(wTextForAI.substr(startPos + charOffset, static_cast<int32_t>(wOriText.length())))) {
            TAG_LOGW(AceLogTag::ACE_TEXT, "The charOffset is error");
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
        item->Put("resultCode", textDetectResult_->code);
        entityJson_[start] = item->ToString();
        TAG_LOGD(AceLogTag::ACE_TEXT, "The json of the entity is: %{public}s", entityJson_[start].c_str());

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
            bool isSameDetectText = detectTextIdx < dataDetectorAdapter->detectTexts.size() &&
                                    detectText == dataDetectorAdapter->detectTexts[detectTextIdx];
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
                if (detectTextIdx < dataDetectorAdapter->detectTexts.size()) {
                    dataDetectorAdapter->detectTexts[detectTextIdx] = detectText;
                } else {
                    dataDetectorAdapter->detectTexts.emplace_back(detectText);
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
    }
    aiSpanMap_.clear();
    typeChanged_ = false;
    lastTextForAI_ = textForAI_;
    startDetectorTimeStamp_ = std::chrono::high_resolution_clock::now();
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto taskExecutor = context->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    aiDetectDelayTask_.Cancel();
    aiDetectDelayTask_.Reset(GetDetectDelayTask(aiSpanMapCopy));
    taskExecutor->PostDelayedTask(
        aiDetectDelayTask_, TaskExecutor::TaskType::UI, AI_DELAY_TIME, "ArkUITextStartAIDetect");
}
} // namespace OHOS::Ace
