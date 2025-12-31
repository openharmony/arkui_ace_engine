/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_INTERFACE_UI_CONTENT_PROXY_H
#define FOUNDATION_ACE_INTERFACE_UI_CONTENT_PROXY_H
#include <functional>
#include "interfaces/inner_api/ui_session/ui_translate_manager.h"
#include "interfaces/inner_api/ui_session/ui_content_proxy_error_code.h"
#include "frameworks/core/components_ng/base/frame_node.h"
namespace OHOS::Ace {
class ACE_FORCE_EXPORT UiTranslateManagerImpl : public UiTranslateManager,
    public std::enable_shared_from_this<UiTranslateManagerImpl> {
public:
    explicit UiTranslateManagerImpl(const RefPtr<TaskExecutor>& taskExecutor) : taskExecutor_(taskExecutor) {};
    void AddTranslateListener(const WeakPtr<NG::FrameNode> node);
    void RemoveTranslateListener(int32_t nodeId);
    void GetWebViewCurrentLanguage() override;
    void GetTranslateText(std::string extraData, bool isContinued) override;
    void SendTranslateResult(int32_t nodeId, std::vector<std::string> results, std::vector<int32_t> ids) override;
    void ResetTranslate(int32_t nodeId) override;
    void SendTranslateResult(int32_t nodeId, std::string res) override;
    void ClearMap() override;
    void SendPixelMap();
    void GetAllPixelMap(RefPtr<NG::FrameNode> pageNode);
    void TravelFindPixelMap(RefPtr<NG::UINode> currentNode);
    void AddPixelMap(int32_t nodeId, RefPtr<PixelMap> pixelMap);
    void GetMultiImagesById(uint32_t windowId, const std::vector<int32_t>& arkUIIds,
        const std::map<int32_t, std::vector<int32_t>>& arkWebs);
    void SetArkUIQueryErrorCode(MultiImageQueryErrorCode errorCode);
    void SetArkWebQueryErrorCode(MultiImageQueryErrorCode errorCode);
    MultiImageQueryErrorCode GetArkWebQueryErrorCode() const;
    void GetPixelMapFromFrameNode(int32_t frameNodeId, std::shared_ptr<Media::PixelMap>& componentPixelMap);
    bool GetHasSendArkWebQueryResult() const;
    void SendArkUIImagesById();
    void SendArkWebImagesById();
    void DoSendArkWebImagesById();
    void MarkCurrentWebImageQueryDone(int32_t currentWebId);
    void AddArkUIComponentPixelMap(int32_t componentId, std::shared_ptr<Media::PixelMap>& componentPixelMap);
    void AddArkWebImageMap(int32_t webId, const std::map<int32_t, std::shared_ptr<Media::PixelMap>>& webImageMap);
    void PostToUI(const std::function<void()>& task) override;

private:
    void TraverseAddArkUIComponentImages(const size_t componentQueryCnt, const std::vector<int32_t>& arkUIIds);
    void TraverseAddArkWebImages(const std::vector<int32_t>& webImageIds, int32_t windowId, int32_t webComponentId,
        const std::function<void(int32_t, const std::map<int32_t, std::shared_ptr<Media::PixelMap>>&,
        MultiImageQueryErrorCode)>& webQueryCallback);
    void PostArkWebQueryTasks(std::weak_ptr<UiTranslateManagerImpl> weak, int32_t windowId);
    void PostArkWebQueryTasksToSingleWeb(std::weak_ptr<UiTranslateManagerImpl> weak,
        const std::vector<int32_t>& webImageIds, int32_t webId, int32_t windowId);
    void AdjustArkWebImagesQueryCnt(size_t remainQueryCnt, const std::map<int32_t, std::vector<int32_t>>& arkWebs);
    void GetPixelMapFromImageTypeNode(RefPtr<NG::FrameNode> frameNode,
        std::shared_ptr<Media::PixelMap>& componentPixelMap);
    bool CheckAllWebQueryTaskFinish() const;
    int32_t windowId_ = 0;

    // mark if all web image queries have finished within QUERY_IMAGES_TIMEOUT_TIME.
    bool hasSendArkWebQueryResult_ = true;

    // record if a web component has finish its image query.
    std::unordered_map<int32_t, bool> arkWebQueryImageTaskDone_;

    /*
     * the origin input ArkWeb's queries may contain too many ids, so we need set a limit and record the ids after
     * adjusting the origin input map.
    */
    std::map<int32_t, std::vector<int32_t>> localArkWebQueries_;

    MultiImageQueryErrorCode arkUIQueryErrorCode_ = MultiImageQueryErrorCode::OK;
    MultiImageQueryErrorCode arkWebQueryErrorCode_ = MultiImageQueryErrorCode::OK;

    // contains the result of GetImagesById, ArkUI's part, mapping ArkUIComponentId to pixelMap.
    std::unordered_map<int32_t, std::shared_ptr<Media::PixelMap>> arkUIComponentImages_;

    /*
     * contains the result of GetImagesById, ArkWeb's part, mapping webComponentId to imageIds and
     * pixelMap in one webComponent.
    */
    std::map<int32_t, std::map<int32_t, std::shared_ptr<Media::PixelMap>>> arkWebImages_;

    static constexpr int32_t QUERY_IMAGES_TIMEOUT_TIME = 1500;
    std::map<int32_t, WeakPtr<NG::FrameNode>> listenerMap_;
    std::vector<std::pair<int32_t, std::shared_ptr<Media::PixelMap>>> pixelMap_;
    RefPtr<TaskExecutor> taskExecutor_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_INTERFACE_UI_CONTENT_PROXY_H
