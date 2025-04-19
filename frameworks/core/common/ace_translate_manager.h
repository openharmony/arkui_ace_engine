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

#include "interfaces/inner_api/ui_session/ui_translate_manager.h"

#include "frameworks/core/components_ng/base/frame_node.h"
namespace OHOS::Ace {
class ACE_FORCE_EXPORT UiTranslateManagerImpl : public UiTranslateManager {
public:
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
    void FindTopNavDestination(RefPtr<NG::UINode> currentNode, RefPtr<NG::FrameNode>& result);

private:
    std::map<int32_t, WeakPtr<NG::FrameNode>> listenerMap_;
    std::vector<std::pair<int32_t, std::shared_ptr<Media::PixelMap>>> pixelMap_;
    const static std::set<std::string> layoutTags_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_INTERFACE_UI_CONTENT_PROXY_H
