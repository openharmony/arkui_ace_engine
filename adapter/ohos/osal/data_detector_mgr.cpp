/*
 * Copyright (C) 2023 Huawei Device Co., Ltd.
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

#include "core/common/ai/data_detector_mgr.h"

#include "interfaces/inner_api/ace/modal_ui_extension_config.h"
#include "want.h"

#include "base/log/log_wrapper.h"
#include "core/common/ai/data_detector_default.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_model_ng.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace {
namespace {
#ifdef __aarch64__
const std::string AI_ADAPTER_SO_PATH = "system/lib64/libai_text_analyzer_innerapi.z.so";
#else
const std::string AI_ADAPTER_SO_PATH = "system/lib/libai_text_analyzer_innerapi.z.so";
#endif
} // namespace

DataDetectorMgr& DataDetectorMgr::GetInstance()
{
    static DataDetectorMgr instance;
    return instance;
}

DataDetectorMgr::DataDetectorMgr()
{
    auto lib = DataDetectorLoader::Load(AI_ADAPTER_SO_PATH);
    if (lib == nullptr || (engine_ = lib->CreateDataDetector()) == nullptr) {
        engine_ = DataDetectorInstance(new DataDetectorDefault, [](DataDetectorInterface* e) {
            auto* p = reinterpret_cast<DataDetectorDefault*>(e);
            delete p;
        });
    }
}

bool DataDetectorMgr::IsDataDetectorSupported()
{
    if (engine_) {
        return engine_->IsDataDetectorSupported();
    }
    return false;
}

void DataDetectorMgr::DataDetect(const TextDataDetectInfo& info, const TextDetectResultFunc& resultFunc)
{
    if (engine_) {
        engine_->DataDetect(info, resultFunc);
    }
}

bool DataDetectorMgr::ShowUIExtensionMenu(const std::map<std::string, std::string>& paramaters, NG::RectF aiRect,
    std::function<void(const std::string&)> onClickMenu, const RefPtr<NG::FrameNode>& targetNode)
{
    ModalUIExtensionCallbacks callbacks;
    callbacks.onResult = [onClickMenu](int32_t code, const AAFwk::Want& want) {
        TAG_LOGI(AceLogTag::ACE_UIEXTENSIONCOMPONENT, "UIExtension Ability onResult, code: %{public}d", code);
        auto action = want.GetStringParam("action");
        if (!action.empty() && onClickMenu) {
            onClickMenu(action);
        }
    };
    callbacks.onDestroy = []() { TAG_LOGI(AceLogTag::ACE_UIEXTENSIONCOMPONENT, "UIExtension Ability Destroy"); };
    callbacks.onError = [](int32_t code, const std::string& name, const std::string& message) {
        TAG_LOGI(AceLogTag::ACE_UIEXTENSIONCOMPONENT,
            "UIExtension Ability Error, code: %{public}d, name: %{public}s, message: %{public}s", code, name.c_str(),
            message.c_str());
    };
    callbacks.onRelease  = [](int32_t code) {
        TAG_LOGI(AceLogTag::ACE_UIEXTENSIONCOMPONENT, "UIExtension Ability Release, code: %{public}d", code);
    };
    AAFwk::Want want;
    want.SetElementName(bundleName_, abilityName_);
    for (const auto& param : paramaters) {
        want.SetParam(param.first, param.second);
    }

    auto uiExtNode = NG::UIExtensionModelNG::Create(want, callbacks);
    CHECK_NULL_RETURN(uiExtNode, false);
    auto onReceive = GetOnReceive(uiExtNode, aiRect, onClickMenu, targetNode);
    auto pattern = uiExtNode->GetPattern<NG::UIExtensionPattern>();
    CHECK_NULL_RETURN(pattern, false);
    pattern->SetOnReceiveCallback(std::move(onReceive));
    uiExtNode->MarkModifyDone();
    return true;
}

std::function<void(const AAFwk::WantParams&)> DataDetectorMgr::GetOnReceive(const RefPtr<NG::FrameNode>& uiExtNode,
    NG::RectF aiRect, std::function<void(const std::string&)> onClickMenu, const RefPtr<NG::FrameNode>& targetNode)
{
    return [uiExtNode, aiRect, onClickMenu, targetNode](const AAFwk::WantParams& wantParams) {
        TAG_LOGI(AceLogTag::ACE_UIEXTENSIONCOMPONENT, "UIExtension Ability onReceive");
        CHECK_NULL_VOID(uiExtNode);
        CHECK_NULL_VOID(targetNode);
        auto pipeline = NG::PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto overlayManager = pipeline->GetOverlayManager();
        CHECK_NULL_VOID(overlayManager);
        std::string action = wantParams.GetStringParam("action");
        if (!action.empty() && onClickMenu) {
            onClickMenu(action);
        }
        std::string closeMenu = wantParams.GetStringParam("closeMenu");
        if (closeMenu == "true") {
            int32_t targetId = targetNode->GetId();
            auto menuNode = overlayManager->GetMenuNode(targetId);
            CHECK_NULL_VOID(menuNode);
            overlayManager->HideMenu(menuNode, targetId);
            return;
        }
        std::string longestContent = wantParams.GetStringParam("longestContent");
        std::string menuSizeString = wantParams.GetStringParam("menuSize");
        if (longestContent.empty() || menuSizeString.empty()) {
            return;
        }
        int32_t menuSize = static_cast<int32_t>(atoi(menuSizeString.c_str()));
        overlayManager->ShowUIExtensionMenu(uiExtNode, aiRect, longestContent, menuSize, targetNode);
    };
}

void DataDetectorMgr::ResponseBestMatchItem(const std::map<std::string, std::string>& paramaters, const AISpan& aiSpan)
{
    ModalUIExtensionCallbacks callbacks;
    AAFwk::Want want;
    want.SetElementName(bundleName_, abilityName_);
    for (const auto& param : paramaters) {
        want.SetParam(param.first, param.second);
    }
    NG::UIExtensionModelNG::Create(want, callbacks);
}

void DataDetectorMgr::AdjustCursorPosition(
    int32_t& caretPos, const std::string& content, TimeStamp& lastAiPosTimeStamp, const TimeStamp& lastClickTimeStamp)
{
    if (engine_) {
        int32_t aiPos = GetCursorPosition(content, caretPos);
        TAG_LOGI(AceLogTag::ACE_TEXTINPUT, "TryGetAiCursorPosition,aiPos is %{public}d", aiPos);

        if (aiPos < 0) {
            return;
        }
        // aiPos should above zero;
        caretPos = aiPos;
        // record the ai position time
        lastAiPosTimeStamp = lastClickTimeStamp;
    }
}

void DataDetectorMgr::AdjustWordSelection(int32_t& caretPos, const std::string& content, int32_t& start, int32_t& end)
{
    if (engine_) {
        std::vector<int8_t> ret = GetWordSelection(content, caretPos);
        start = ret[0];
        end = ret[1];

        TAG_LOGI(AceLogTag::ACE_TEXTINPUT, "get ai selection:%{public}d--%{public}d", start, end);
        if (start < 0 || end < 0) {
            return;
        }
        caretPos = start;
    }
}

std::vector<int8_t> DataDetectorMgr::GetWordSelection(const std::string& text, int8_t offset)
{
    if (engine_) {
        return engine_->GetWordSelection(text, offset);
    }

    return std::vector<int8_t> { -1, -1 };
}

int8_t DataDetectorMgr::GetCursorPosition(const std::string& text, int8_t offset)
{
    if (engine_) {
        return engine_->GetCursorPosition(text, offset);
    }

    return -1;
}
} // namespace OHOS::Ace
