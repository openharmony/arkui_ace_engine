/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_UI_EXTENSION_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_UI_EXTENSION_MODEL_NG_H

#include <memory>
#include <string>

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_model.h"

namespace OHOS::Ace {
struct ModalUIExtensionCallbacks;
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
const SessionType DEFAULT_EMBEDDED_SESSION_TYPE = SessionType::EMBEDDED_UI_EXTENSION;
const CalcDimension EMBEDDED_COMPONENT_MIN_WIDTH(10.0f, DimensionUnit::VP);
const CalcDimension EMBEDDED_COMPONENT_MIN_HEIGHT(10.0f, DimensionUnit::VP);

class ACE_EXPORT UIExtensionModelNG : public UIExtensionModel {
public:
    static RefPtr<FrameNode> Create(const std::string& bundleName, const std::string& abilityName,
        const std::map<std::string, std::string>& params, std::function<void(int32_t)>&& onRelease,
        std::function<void(int32_t, const std::string&, const std::string&)>&& onError);
    static RefPtr<FrameNode> Create(const AAFwk::Want& want, const ModalUIExtensionCallbacks& callbacks,
        const InnerModalUIExtensionConfig& config);

    void Create(const RefPtr<OHOS::Ace::WantWrap>& wantWrap,
        const std::map<NG::PlaceholderType, RefPtr<NG::FrameNode>>& placeholderMap,
        bool transferringCaller = false, bool densityDpi = true, bool isWindowModeFollowHost = false) override;
    // for Embedded Component
    void Create(const RefPtr<OHOS::Ace::WantWrap>& wantWrap, SessionType sessionType) override;
    static RefPtr<FrameNode> CreateEmbeddedFrameNode(int32_t nodeId);
    static void UpdateEmbeddedFrameNode(FrameNode* frameNode,
        const AAFwk::Want& wantWrap, SessionType sessionType);
    // for dynamic component
    void Create(const UIExtensionConfig& config) override;
    void InitializeDynamicComponent(const RefPtr<FrameNode>& frameNode, const std::string& hapPath,
        const std::string& abcPath, const std::string& entryPoint, void* runtime) override;
    void InitializeIsolatedComponent(const RefPtr<NG::FrameNode>& frameNode,
        const RefPtr<OHOS::Ace::WantWrap>& wantWrap, void* runtime) override;
    void SetPlatformOnError(std::function<void(
        int32_t code, const std::string& name, const std::string& message)>&& onError) override;
    void SetAdaptiveWidth(bool state) override;
    void SetAdaptiveHeight(bool state) override;
    std::string GetUiExtensionType(NG::SessionType sessionType) override;

    void SetOnRemoteReady(std::function<void(const RefPtr<UIExtensionProxy>&)>&& onRemoteReady) override;
    void SetOnRelease(std::function<void(int32_t)>&& onRelease) override;
    void SetOnResult(std::function<void(int32_t, const AAFwk::Want&)>&& onResult) override;
    void SetOnTerminated(std::function<void(int32_t, const RefPtr<WantWrap>&)>&& onTerminated,
        NG::SessionType sessionType = NG::SessionType::UI_EXTENSION_ABILITY) override;
    void SetOnDrawReady(std::function<void()>&& onDrawReady) override;
    void SetOnReceive(std::function<void(const AAFwk::WantParams&)>&& onReceive,
        NG::SessionType sessionType = NG::SessionType::UI_EXTENSION_ABILITY) override;
    void SetSecurityOnRemoteReady(
        std::function<void(const RefPtr<NG::SecurityUIExtensionProxy>&)>&& onRemoteReady) override;
    void SetOnError(
        std::function<void(int32_t code, const std::string& name, const std::string& message)>&& onError,
        NG::SessionType sessionType = NG::SessionType::UI_EXTENSION_ABILITY) override;

    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static void UpdateWant(FrameNode* frameNode, const AAFwk::Want& want, bool isTransferringCaller, bool densityDpi);
    static void SetOnError(FrameNode* frameNode,
        std::function<void(int32_t code, const std::string& name, const std::string& message)>&& onError,
        NG::SessionType sessionType = NG::SessionType::UI_EXTENSION_ABILITY);
    static void SetOnReceive(FrameNode* frameNode,
        std::function<void(const AAFwk::WantParams&)>&& onReceive,
        NG::SessionType sessionType = NG::SessionType::UI_EXTENSION_ABILITY);
    static void SetOnRelease(FrameNode* frameNode, std::function<void(int32_t)>&& onRelease);
    static void SetOnRemoteReady(FrameNode* frameNode,
        std::function<void(const RefPtr<UIExtensionProxy>&)>&& onRemoteReady);
    static void SetOnResult(FrameNode* frameNode, std::function<void(int32_t, const AAFwk::Want&)>&& onResult);
    static void SetOnTerminated(FrameNode* frameNode,
        std::function<void(int32_t, const RefPtr<WantWrap>&)>&& onTerminated,
        NG::SessionType sessionType = NG::SessionType::UI_EXTENSION_ABILITY);
private:
    void CreateSecurityUIExtension(const UIExtensionConfig& config);
    void CreateDynamicComponent(const UIExtensionConfig& config);
    void CreateIsolatedComponent(const UIExtensionConfig& config);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_UI_EXTENSION_MODEL_NG_H
