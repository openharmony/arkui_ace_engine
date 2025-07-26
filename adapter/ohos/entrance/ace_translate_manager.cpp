/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/common/ace_translate_manager.h"

#include "interfaces/inner_api/ui_session/ui_session_manager.h"

#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/web/web_pattern.h"

namespace OHOS::Ace {
const std::set<std::string> UiTranslateManagerImpl::layoutTags_ = { "Flex", "Stack", "Row", "Column", "WindowScene",
    "root", "__Common__", "Swiper", "Grid", "GridItem", "page", "stage", "FormComponent", "Tabs", "TabContent" };
void UiTranslateManagerImpl::AddTranslateListener(const WeakPtr<NG::FrameNode> node)
{
    auto frameNode = node.Upgrade();
    CHECK_NULL_VOID(frameNode);
    int32_t nodeId = frameNode->GetId();
    listenerMap_[nodeId] = node;
    LOGI("AddTranslateListener WebView nodeId:%{public}d", nodeId);
}
void UiTranslateManagerImpl::RemoveTranslateListener(int32_t nodeId)
{
    listenerMap_.erase(nodeId);
    LOGI("RemoveTranslateListener WebView nodeId:%{public}d", nodeId);
}

void UiTranslateManagerImpl::GetWebViewCurrentLanguage()
{
    for (auto listener : listenerMap_) {
        auto frameNode = listener.second.Upgrade();
        if (!frameNode) {
            continue;
        }
        int32_t nodeId = frameNode->GetId();
        auto pattern = frameNode->GetPattern<NG::WebPattern>();
        if (!pattern) {
            continue;
        }
        std::string currentLanguage = pattern->GetCurrentLanguage();
        auto result = JsonUtil::Create();
        result->Put("nodeId", nodeId);
        result->Put("currentLanguage", currentLanguage.c_str());
        UiSessionManager::GetInstance()->SendCurrentLanguage(result->ToString());
    }
}

void UiTranslateManagerImpl::GetTranslateText(std::string extraData, bool isContinued)
{
    if (listenerMap_.empty()) {
        UiSessionManager::GetInstance()->SendWebTextToAI(-1, "empty");
    } else {
        UiSessionManager::GetInstance()->SendWebTextToAI(-1, "non-empty");
    }
    for (auto listener : listenerMap_) {
        auto frameNode = listener.second.Upgrade();
        if (!frameNode) {
            continue;
        }
        int32_t nodeId = frameNode->GetId();
        auto cb = [nodeId](std::string res) { UiSessionManager::GetInstance()->SendWebTextToAI(nodeId, res); };
        auto pattern = frameNode->GetPattern<NG::WebPattern>();
        if (!pattern) {
            continue;
        }
        pattern->GetTranslateText(extraData, cb, isContinued);
    }
}

void UiTranslateManagerImpl::SendTranslateResult(
    int32_t nodeId, std::vector<std::string> results, std::vector<int32_t> ids)
{
    auto iter = listenerMap_.find(nodeId);
    if (iter != listenerMap_.end()) {
        auto frameNode = iter->second.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto pattern = frameNode->GetPattern<NG::WebPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->SendTranslateResult(results, ids);
    }
}

void UiTranslateManagerImpl::SendTranslateResult(int32_t nodeId, std::string res)
{
    auto iter = listenerMap_.find(nodeId);
    if (iter != listenerMap_.end()) {
        auto frameNode = iter->second.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto pattern = frameNode->GetPattern<NG::WebPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->SendTranslateResult(res);
    } else {
        LOGW("SendTranslateResult can not find WebView nodeId:%{public}d", nodeId);
    }
}

void UiTranslateManagerImpl::ResetTranslate(int32_t nodeId)
{
    if (nodeId == -1) {
        for (auto listener : listenerMap_) {
            auto frameNode = listener.second.Upgrade();
            if (!frameNode) {
                continue;
            }
            auto pattern = frameNode->GetPattern<NG::WebPattern>();
            if (!pattern) {
                continue;
            }
            pattern->EndTranslate();
        }
    } else {
        auto iter = listenerMap_.find(nodeId);
        if (iter != listenerMap_.end()) {
            auto frameNode = iter->second.Upgrade();
            CHECK_NULL_VOID(frameNode);
            auto pattern = frameNode->GetPattern<NG::WebPattern>();
            CHECK_NULL_VOID(pattern);
            pattern->EndTranslate();
        } else {
            LOGW("ResetTranslate can not find WebView nodeId:%{public}d", nodeId);
        }
    }
}

void UiTranslateManagerImpl::ClearMap()
{
    pixelMap_.clear();
}

void UiTranslateManagerImpl::SendPixelMap()
{
    LOGI("manager start sendPixelMap");
    UiSessionManager::GetInstance()->SendPixelMap(pixelMap_);
}

void UiTranslateManagerImpl::AddPixelMap(int32_t nodeId, RefPtr<PixelMap> pixelMap)
{
    CHECK_NULL_VOID(pixelMap);
    std::pair<int32_t, std::shared_ptr<Media::PixelMap>> value = { nodeId, pixelMap->GetPixelMapSharedPtr() };
    pixelMap_.push_back(value);
}

void UiTranslateManagerImpl::GetAllPixelMap(RefPtr<NG::FrameNode> pageNode)
{
    RefPtr<NG::FrameNode> result;
    FindTopNavDestination(pageNode, result);
    if (result != nullptr) {
        TravelFindPixelMap(result);
    } else {
        TravelFindPixelMap(pageNode);
    }
    SendPixelMap();
}

void UiTranslateManagerImpl::TravelFindPixelMap(RefPtr<NG::UINode> currentNode)
{
    for (const auto& item : currentNode->GetChildren()) {
        auto node = AceType::DynamicCast<NG::FrameNode>(item);
        if (node) {
            if (layoutTags_.find(node->GetTag()) != layoutTags_.end() && !node->IsActive()) {
                continue;
            }
            auto property = node->GetLayoutProperty();
            if (node->GetTag() == V2::IMAGE_ETS_TAG && property &&
                (static_cast<int32_t>(property->GetVisibility().value_or(VisibleType::VISIBLE)) == 0) &&
                node->IsActive()) {
                auto imagePattern = node->GetPattern<NG::ImagePattern>();
                CHECK_NULL_VOID(imagePattern);
                imagePattern->AddPixelMapToUiManager();
            }
        }
        TravelFindPixelMap(item);
    }
}

void UiTranslateManagerImpl::PostToUI(const std::function<void()>& task)
{
    if (taskExecutor_) {
        taskExecutor_->PostTask(task, TaskExecutor::TaskType::UI, "ArkUIHandleUiTranslateManager");
    }
}

void UiTranslateManagerImpl::FindTopNavDestination(RefPtr<NG::UINode> currentNode, RefPtr<NG::FrameNode>& result)
{
    for (const auto& item : currentNode->GetChildren()) {
        auto node = AceType::DynamicCast<NG::FrameNode>(item);
        if (node && node->GetTag() == V2::NAVIGATION_VIEW_ETS_TAG) {
            auto navigationGroupNode = AceType::DynamicCast<NG::NavigationGroupNode>(node);
            CHECK_NULL_VOID(navigationGroupNode);
            result = navigationGroupNode->GetTopDestination();
            return;
        }
        FindTopNavDestination(item, result);
    }
}
} // namespace OHOS::Ace
