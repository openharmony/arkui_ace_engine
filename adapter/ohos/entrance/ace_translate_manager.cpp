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

#include "base/error/error_code.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/web/web_pattern.h"
#include "core/components_ng/render/adapter/component_snapshot.h"

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

void UiTranslateManagerImpl::AddArkUIComponentPixelMap(
    int32_t componentId, std::shared_ptr<Media::PixelMap>& componentPixelMap)
{
    arkUIComponentImages_.emplace(componentId, componentPixelMap);
}

void UiTranslateManagerImpl::AddArkWebImageMap(
    int32_t webId, const std::map<int32_t, std::shared_ptr<Media::PixelMap>>& webImageMap)
{
    arkWebImages_.emplace(webId, webImageMap);
}

void UiTranslateManagerImpl::TraverseAddArkUIComponentImages(const size_t componentQueryCnt,
    const std::vector<int32_t>& arkUIIds)
{
    arkUIQueryErrorCode_ = MultiImageQueryErrorCode::OK;
    if (taskExecutor_ == nullptr) {
        arkUIQueryErrorCode_ = MultiImageQueryErrorCode::INVALID_ID;
        for (size_t i = 0; i < componentQueryCnt; ++i) {
            arkUIComponentImages_.emplace(arkUIIds[i], nullptr);
        }
        return;
    }
    std::weak_ptr<UiTranslateManagerImpl> weak = shared_from_this();
    bool finishInTime = taskExecutor_->PostSyncTaskTimeout(
        [weak, componentQueryCnt, arkUIIds]() {
            auto uiTranslateManagerImpl = weak.lock();
            CHECK_NULL_VOID(uiTranslateManagerImpl);
            ACE_SCOPED_TRACE("TraverseAddArkUIComponentImages GetPixelMapFromFrameNode");
            for (size_t i = 0; i < componentQueryCnt; ++i) {
                std::shared_ptr<Media::PixelMap> componentPixelMap = nullptr;
                uiTranslateManagerImpl->GetPixelMapFromFrameNode(arkUIIds[i], componentPixelMap);
                uiTranslateManagerImpl->AddArkUIComponentPixelMap(arkUIIds[i], componentPixelMap);
            }
        },
        TaskExecutor::TaskType::UI, QUERY_IMAGES_TIMEOUT_TIME, "ArkUIAddComponentImagesDuringMultiQuery");
    if (arkUIQueryErrorCode_ == MultiImageQueryErrorCode::OK && !finishInTime) {
        arkUIQueryErrorCode_ = MultiImageQueryErrorCode::TIMEOUT;
    }
    if (!finishInTime) {
        for (size_t i = arkUIComponentImages_.size(); i < componentQueryCnt; ++i) {
            arkUIComponentImages_.emplace(arkUIIds[i], nullptr);
        }
    }
}

void UiTranslateManagerImpl::TraverseAddArkWebImages(const std::vector<int32_t>& webImageIds, int32_t windowId,
    int32_t webComponentId, const std::function<void(int32_t, const std::map<int32_t,
    std::shared_ptr<Media::PixelMap>>&, MultiImageQueryErrorCode)>& webQueryCallback)
{
    auto frameNode =
        AceType::DynamicCast<NG::FrameNode>(OHOS::Ace::ElementRegister::GetInstance()->GetNodeById(webComponentId));
    if (frameNode == nullptr || frameNode->GetPattern<NG::WebPattern>() == nullptr) {
        std::map<int32_t, std::shared_ptr<Media::PixelMap>> emptyMap;
        for (auto webImageId : webImageIds) {
            emptyMap.emplace(webImageId, nullptr);
        }
        webQueryCallback(windowId, emptyMap, MultiImageQueryErrorCode::INVALID_WEBNODE);
        return;
    }
    frameNode->GetPattern<NG::WebPattern>()->GetImagesByIDs(webImageIds, windowId, webQueryCallback);
}

void UiTranslateManagerImpl::MarkCurrentWebImageQueryDone(int32_t currentWebId)
{
    if (arkWebQueryImageTaskDone_.find(currentWebId) != arkWebQueryImageTaskDone_.end()) {
        arkWebQueryImageTaskDone_[currentWebId] = true;
    }
}

MultiImageQueryErrorCode UiTranslateManagerImpl::GetArkWebQueryErrorCode() const
{
    return arkWebQueryErrorCode_;
}

void UiTranslateManagerImpl::PostArkWebQueryTasksToSingleWeb(std::weak_ptr<UiTranslateManagerImpl> weak,
    const std::vector<int32_t>& webImageIds, int32_t webId, int32_t windowId)
{
    CHECK_NULL_VOID(taskExecutor_);
    taskExecutor_->PostTask(
        [weak, webImageIds, webId, windowId]() mutable {
            auto uiTranslateManagerImpl = weak.lock();
            CHECK_NULL_VOID(uiTranslateManagerImpl);
            auto getWebImagesCallback =
                [weak, webId, webImageIds](int32_t windowId, const std::map<int32_t,
                    std::shared_ptr<Media::PixelMap>>& imagesInOneWeb, MultiImageQueryErrorCode errorCode) {
                        auto uiTranslateManagerImpl = weak.lock();
                        CHECK_NULL_VOID(uiTranslateManagerImpl);
                        if (uiTranslateManagerImpl->GetHasSendArkWebQueryResult()) {
                            return;
                        }
                        uiTranslateManagerImpl->MarkCurrentWebImageQueryDone(webId);
                        if (uiTranslateManagerImpl->GetArkWebQueryErrorCode() == MultiImageQueryErrorCode::OK) {
                            uiTranslateManagerImpl->SetArkWebQueryErrorCode(errorCode);
                        }
                        uiTranslateManagerImpl->AddArkWebImageMap(webId, imagesInOneWeb);
                        uiTranslateManagerImpl->SendArkWebImagesById();
                    };
            uiTranslateManagerImpl->TraverseAddArkWebImages(webImageIds, windowId, webId, getWebImagesCallback);
        },
        TaskExecutor::TaskType::UI, "ArkWebAddImagesDuringMultiQuery");
}

bool UiTranslateManagerImpl::GetHasSendArkWebQueryResult() const
{
    return hasSendArkWebQueryResult_;
}

void UiTranslateManagerImpl::PostArkWebQueryTasks(std::weak_ptr<UiTranslateManagerImpl> weak, int32_t windowId)
{
    CHECK_NULL_VOID(taskExecutor_);
    hasSendArkWebQueryResult_ = false;
    auto setRejectTimeoutArkWebImageQuery = [weak]() {
        auto uiTranslateManagerImpl = weak.lock();
        CHECK_NULL_VOID(uiTranslateManagerImpl);
        if (uiTranslateManagerImpl->GetHasSendArkWebQueryResult()) {
            return;
        }
        uiTranslateManagerImpl->SetArkWebQueryErrorCode(MultiImageQueryErrorCode::TIMEOUT);
        uiTranslateManagerImpl->DoSendArkWebImagesById();
    };
    taskExecutor_->PostDelayedTask(setRejectTimeoutArkWebImageQuery,
        TaskExecutor::TaskType::UI, QUERY_IMAGES_TIMEOUT_TIME, "ArkUISetRejectTimeoutArkWebImageQuery");
    for (const auto& [webId, webImagesIds] : localArkWebQueries_) {
        PostArkWebQueryTasksToSingleWeb(weak, webImagesIds, webId, windowId);
    }
}

void UiTranslateManagerImpl::AdjustArkWebImagesQueryCnt(size_t remainQueryCnt,
    const std::map<int32_t, std::vector<int32_t>>& arkWebs)
{
    for (const auto& [webId, webImagesIds] : arkWebs) {
        if (remainQueryCnt == 0) {
            break;
        }
        size_t currentSize = std::min(remainQueryCnt, webImagesIds.size());
        remainQueryCnt -= currentSize;
        for (size_t i = 0; i < currentSize; ++i) {
            localArkWebQueries_[webId].emplace_back(webImagesIds[i]);
        }
        arkWebQueryImageTaskDone_.emplace(webId, false);
    }
}

void UiTranslateManagerImpl::GetMultiImagesById(uint32_t windowId, const std::vector<int32_t>& arkUIIds,
    const std::map<int32_t, std::vector<int32_t>>& arkWebs)
{
    if (!taskExecutor_) {
        LOGE("UiTranslateManagerImpl::GetMultiImagesById taskExecutor_ doesn't exist");
        return;
    }
    windowId_ = windowId;
    const size_t totalQueryCnt = 20;
    size_t componentQueryCnt = std::min(totalQueryCnt, arkUIIds.size());
    size_t webQueryCnt = totalQueryCnt - componentQueryCnt;
    std::weak_ptr<UiTranslateManagerImpl> weak = shared_from_this();
    AdjustArkWebImagesQueryCnt(webQueryCnt, arkWebs);
    if (componentQueryCnt > 0) {
        taskExecutor_->PostTask(
            [weak, componentQueryCnt, arkUIIds]() {
                auto uiTranslateManagerImpl = weak.lock();
                CHECK_NULL_VOID(uiTranslateManagerImpl);
                uiTranslateManagerImpl->TraverseAddArkUIComponentImages(componentQueryCnt, arkUIIds);
                uiTranslateManagerImpl->SendArkUIImagesById();
            },
            TaskExecutor::TaskType::UI, "ArkUIHandleTranslateManagerGetArkUIImagesByIds");
    } else {
        LOGW("UiTranslateManagerImpl::GetMultiImagesById ArkUI query count is 0");
    }
    if (!arkWebQueryImageTaskDone_.empty()) {
        PostArkWebQueryTasks(weak, windowId);
    } else {
        LOGW("UiTranslateManagerImpl::GetMultiImagesById ArkWeb query count is 0");
    }
}

void UiTranslateManagerImpl::SetArkUIQueryErrorCode(MultiImageQueryErrorCode errorCode)
{
    arkUIQueryErrorCode_ = errorCode;
}

void UiTranslateManagerImpl::SetArkWebQueryErrorCode(MultiImageQueryErrorCode errorCode)
{
    arkWebQueryErrorCode_ = errorCode;
}

void UiTranslateManagerImpl::GetPixelMapFromImageTypeNode(RefPtr<NG::FrameNode> frameNode,
    std::shared_ptr<Media::PixelMap>& componentPixelMap)
{
    CHECK_NULL_VOID(frameNode);
    auto frameNodeId = frameNode->GetId();
    NG::SnapshotOptions options;
    if (frameNode->GetTag() == V2::IMAGE_ETS_TAG) {
        auto imagePattern = frameNode->GetPattern<NG::ImagePattern>();
        if (imagePattern == nullptr) {
            const auto& result = NG::ComponentSnapshot::GetSyncByUniqueId(frameNodeId, options);
            componentPixelMap = result.first == OHOS::Ace::ERROR_CODE_NO_ERROR ? result.second : nullptr;
            return;
        }
        imagePattern->AddPixelMapToUiManager();
        auto canvasImage = imagePattern->GetCanvasImage();
        if (canvasImage == nullptr) {
            const auto& result = NG::ComponentSnapshot::GetSyncByUniqueId(frameNodeId, options);
            componentPixelMap = result.first == OHOS::Ace::ERROR_CODE_NO_ERROR ? result.second : nullptr;
            return;
        }
        auto canvasImagePixelMap = canvasImage->GetPixelMap();
        if (canvasImagePixelMap == nullptr) {
            const auto& result = NG::ComponentSnapshot::GetSyncByUniqueId(frameNodeId, options);
            componentPixelMap = result.first == OHOS::Ace::ERROR_CODE_NO_ERROR ? result.second : nullptr;
            return;
        }
        componentPixelMap = canvasImagePixelMap->GetPixelMapSharedPtr();
        if (componentPixelMap == nullptr) {
            const auto& result = NG::ComponentSnapshot::GetSyncByUniqueId(frameNodeId, options);
            componentPixelMap = result.first == OHOS::Ace::ERROR_CODE_NO_ERROR ? result.second : nullptr;
            return;
        }
    } else {
        const auto& result = NG::ComponentSnapshot::GetSyncByUniqueId(frameNodeId, options);
        componentPixelMap = result.first == OHOS::Ace::ERROR_CODE_NO_ERROR ? result.second : nullptr;
        return;
    }
}

void UiTranslateManagerImpl::GetPixelMapFromFrameNode(int32_t frameNodeId,
    std::shared_ptr<Media::PixelMap>& componentPixelMap)
{
    auto frameNode =
        AceType::DynamicCast<NG::FrameNode>(OHOS::Ace::ElementRegister::GetInstance()->GetNodeById(frameNodeId));
    if (frameNode == nullptr) {
        LOGW("UiTranslateManagerImpl::GetPixelMapFromFrameNode Node%{public}d doesn't exist", frameNodeId);
        arkUIQueryErrorCode_ = MultiImageQueryErrorCode::INVALID_ID;
        return;
    }
    GetPixelMapFromImageTypeNode(frameNode, componentPixelMap);
    if (componentPixelMap == nullptr && arkUIQueryErrorCode_ == MultiImageQueryErrorCode::OK) {
        arkUIQueryErrorCode_ = MultiImageQueryErrorCode::INVALID_ID;
    }
}

void UiTranslateManagerImpl::SendArkUIImagesById()
{
    UiSessionManager::GetInstance()->SendArkUIImagesById(windowId_, arkUIComponentImages_, arkUIQueryErrorCode_);
    arkUIComponentImages_.clear();
    arkUIQueryErrorCode_ = MultiImageQueryErrorCode::OK;
}

void UiTranslateManagerImpl::DoSendArkWebImagesById()
{
    if (hasSendArkWebQueryResult_) {
        return;
    }
    for (const auto& [webId, taskHasDone] : arkWebQueryImageTaskDone_) {
        if (!taskHasDone) {
            for (const auto& webImageId : localArkWebQueries_[webId]) {
                arkWebImages_[webId].emplace(webImageId, nullptr);
            }
        }
    }
    UiSessionManager::GetInstance()->SendArkWebImagesById(windowId_, arkWebImages_, arkWebQueryErrorCode_);
    arkWebImages_.clear();
    arkWebQueryImageTaskDone_.clear();
    localArkWebQueries_.clear();
    arkWebQueryErrorCode_ = MultiImageQueryErrorCode::OK;
    hasSendArkWebQueryResult_ = true;
}

bool UiTranslateManagerImpl::CheckAllWebQueryTaskFinish() const
{
    for (const auto& [_, taskIsDone] : arkWebQueryImageTaskDone_) {
        if (!taskIsDone) {
            return false;
        }
    }
    return true;
}

void UiTranslateManagerImpl::SendArkWebImagesById()
{
    bool allWebQueryTasksFinish = CheckAllWebQueryTaskFinish();
    if (allWebQueryTasksFinish) {
        DoSendArkWebImagesById();
    }
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
    pageNode->FindTopNavDestination(result);
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
            if (!node->CheckVisibleOrActive()) {
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
} // namespace OHOS::Ace
