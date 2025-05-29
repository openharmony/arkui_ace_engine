/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_XCOMPONENT_XCOMPONENT_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_XCOMPONENT_XCOMPONENT_MODEL_NG_H

#include <optional>
#include "base/memory/referenced.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_model.h"
#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/arkoala/arkoala_api.h"

namespace OHOS::Ace::NG {
class FrameNode;

class ArkUI_XComponent_Params final : public ArkUI_Params {
public:
    std::string id;
    XComponentType type = XComponentType::SURFACE;
    std::optional<std::string> libraryName = std::nullopt;
    std::shared_ptr<InnerXComponentController> controller = nullptr;
    void* aiOptions = nullptr;
    std::optional<uint64_t> screenId = std::nullopt;
};

class ACE_EXPORT XComponentModelNG : public OHOS::Ace::XComponentModel {
public:
    void Create(XComponentType type) override;
    void Create(const std::optional<std::string>& id, XComponentType type,
        const std::optional<std::string>& libraryname,
        const std::shared_ptr<InnerXComponentController>& xcomponentController) override;
    RefPtr<AceType> Create(int32_t nodeId, float width, float height,
        const std::string& id, XComponentType type, const std::string& libraryname,
        const std::shared_ptr<InnerXComponentController>& xcomponentController) override;
    XComponentType GetType() override;
    std::optional<std::string> GetLibraryName() override;
    void SetSoPath(const std::string& soPath) override;
    void SetOnLoad(LoadEvent&& onLoad) override;
    void SetOnDestroy(DestroyEvent&& onDestroy) override;
    void RegisterOnCreate(const RefPtr<AceType>& node, LoadEvent&& onLoad) override;
    void RegisterOnDestroy(const RefPtr<AceType>& node, DestroyEvent&& onDestroy) override;
    bool IsTexture() override;
    void SetDetachCallback(DetachCallback&& onDetach) override;
    void SetControllerOnCreated(SurfaceCreatedEvent&& onCreated) override;
    void SetControllerOnChanged(SurfaceChangedEvent&& onChanged) override;
    void SetControllerOnDestroyed(SurfaceDestroyedEvent&& onDestroyed) override;
    void EnableAnalyzer(bool enable) override;
    void SetImageAIOptions(void* options) override;
    void SetRenderFit(RenderFit renderFit) override;
    void EnableSecure(bool isSecure) override;
    void HdrBrightness(float hdrBrightness) override;
    void EnableTransparentLayer(bool isTransparentLayer) override;
    void SetScreenId(uint64_t screenId) override;

    static bool IsTexture(FrameNode* frameNode);
    static XComponentType GetType(FrameNode* frameNode);
    static RefPtr<FrameNode> CreateFrameNode(
        int32_t nodeId, const std::string& id, XComponentType type, const std::optional<std::string>& libraryname);
    static RefPtr<FrameNode> CreateTypeNode(int32_t nodeId, ArkUI_XComponent_Params* params);
    static void InitXComponent(FrameNode* frameNode);
    static void SetXComponentId(FrameNode* frameNode, const std::string& id);
    static void SetXComponentType(FrameNode* frameNode, XComponentType type);
    static void SetXComponentSurfaceSize(FrameNode* frameNode, uint32_t width, uint32_t height);
    static std::string GetXComponentId(FrameNode* frameNode);
    static XComponentType GetXComponentType(FrameNode* frameNode);
    static uint32_t GetXComponentSurfaceWidth(FrameNode* frameNode);
    static uint32_t GetXComponentSurfaceHeight(FrameNode* frameNode);
    static void SetXComponentLibraryname(FrameNode* frameNode, const std::string& libraryname);
    static void SetControllerOnCreated(FrameNode* frameNode, SurfaceCreatedEvent&& onCreated);
    static void SetControllerOnChanged(FrameNode* frameNode, SurfaceChangedEvent&& onChanged);
    static void SetControllerOnDestroyed(FrameNode* frameNode, SurfaceDestroyedEvent&& onDestroyed);
    static void SetDetachCallback(FrameNode* frameNode, DetachCallback&& onDetach);
    static void SetImageAIOptions(FrameNode* frameNode, void* options);
    static void SetOnLoad(FrameNode* frameNode, LoadEvent&& onLoad);
    static void SetOnDestroy(FrameNode* frameNode, DestroyEvent&& onDestroy);
    static void EnableAnalyzer(FrameNode* frameNode, bool enable);
    static void EnableSecure(FrameNode* frameNode, bool enable);
    static void HdrBrightness(FrameNode* frameNode, float hdrBrightness);
    static void EnableTransparentLayer(FrameNode* frameNode, bool enable);
    static void SetRenderFit(FrameNode* frameNode, RenderFit renderFit);
    static RenderFit GetSurfaceRenderFit(FrameNode* frameNode);
    static void SetXComponentSurfaceRect(FrameNode* frameNode, float offsetX, float offsetY,
        float surfaceWidth, float surfaceHeight);
    static void GetXComponentSurfaceRect(FrameNode* frameNode, float& offsetX, float& offsetY,
        float& surfaceWidth, float& surfaceHeight);
    static bool GetXComponentEnableAnalyzer(FrameNode* frameNode);
    static void SetScreenId(FrameNode* frameNode, uint64_t screenId);
    static int32_t SetExpectedRateRange(FrameNode* frameNode, int32_t min, int32_t max, int32_t expected);
    static int32_t SetOnFrameCallback(FrameNode* frameNode,
        void(*callback)(void*, uint64_t, uint64_t), void* arkuiNode);
    static int32_t UnregisterOnFrameCallback(FrameNode* frameNode);
    static int32_t SetNeedSoftKeyboard(FrameNode* frameNode, bool needSoftKeyboard);
    static void* CreateAccessibilityProvider(FrameNode* frameNode);
    static void DisposeAccessibilityProvider(ArkUI_AccessibilityProvider* provider);

private:
    static XComponentType GetTypeImpl(const RefPtr<FrameNode>& frameNode);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_XCOMPONENT_XCOMPONENT_MODEL_NG_H
