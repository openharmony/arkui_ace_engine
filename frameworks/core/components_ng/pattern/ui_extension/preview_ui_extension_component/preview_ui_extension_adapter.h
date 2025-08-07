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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_PREVIEW_UI_EXTENSION_ADAPTER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_PREVIEW_UI_EXTENSION_ADAPTER_H

#include <memory>
#include <string>

#include "core/common/container.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_model.h"

namespace OHOS::Ace {
struct ModalUIExtensionCallbacks;
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
class FrameNode;
class SecurityUIExtensionProxy;

class ACE_EXPORT PreviewUIExtensionAdapter {
public:
    static inline PreviewUIExtensionAdapter* GetInstance()
    {
        if (!Container::IsCurrentUseNewPipeline()) {
            LOGE("Get PreviewUIExtension in non NewPipeline.");
        }
        static PreviewUIExtensionAdapter instance;
        return &instance;
    }
    ~PreviewUIExtensionAdapter() = default;

    void Create(const NG::UIExtensionConfig& config);
    RefPtr<FrameNode> CreatePreviewUIExtensionNode(const NG::UIExtensionConfig& config);
    void UpdatePreviewUIExtensionConfig(const RefPtr<FrameNode>& frameNode,
        const NG::UIExtensionConfig& config);
    void SetWant(const RefPtr<FrameNode>& frameNode, const RefPtr<OHOS::Ace::WantWrap>& wantWrap);
    void SetOnRemoteReady(const RefPtr<FrameNode>& frameNode,
        std::function<void(const RefPtr<NG::SecurityUIExtensionProxy>&)>&& onRemoteReady);
    void SetOnTerminated(const RefPtr<FrameNode>& frameNode,
        std::function<void(int32_t, const RefPtr<WantWrap>&)>&& onTerminated);
    void SetOnReceive(const RefPtr<FrameNode>& frameNode,
        std::function<void(const AAFwk::WantParams&)>&& onReceive);
    void SetOnError(const RefPtr<FrameNode>& frameNode,
        std::function<void(int32_t code, const std::string& name, const std::string& message)>&& onError);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_UI_EXTENSION_MODEL_NG_H
