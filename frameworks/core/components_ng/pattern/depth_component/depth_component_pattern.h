/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DEPTH_COMPONENT_DEPTH_COMPONENT_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DEPTH_COMPONENT_DEPTH_COMPONENT_PATTERN_H

#include <memory>
#include <optional>
#include <vector>

#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components/common/properties/depth_option.h"
#include "core/components_ng/pattern/depth_component/depth_component_accessibility_property.h"
#include "core/components_ng/pattern/depth_component/depth_component_event_hub.h"
#include "core/components_ng/pattern/depth_component/depth_component_layout_algorithm.h"
#include "core/components_ng/pattern/depth_component/depth_component_layout_property.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/image_provider/image_loading_context.h"
#include "core/components_ng/render/canvas_image.h"
#include "core/components_ng/render/drawing_forward.h"
#include "core/pipeline/base/element_register.h"
#include "core/components_v2/inspector/inspector_constants.h"

#ifdef ENABLE_ROSEN_BACKEND
#include "render_service_client/core/ui/rs_depth_node.h"
#endif

#if defined(KIT_3D_ENABLE) && !defined(PREVIEW)
#include <surface.h>
#include "scene_adapter/intf_mrt_depth_adapter.h"
#include "render_service_client/core/ui/rs_surface_node.h"
#endif

namespace OHOS::Ace::NG {

class DepthComponentPaintMethod;

class ACE_EXPORT DepthComponentPattern : public Pattern {
    DECLARE_ACE_TYPE(DepthComponentPattern, Pattern);
    friend class DepthComponentPaintMethod;

public:
    DepthComponentPattern() = default;
    ~DepthComponentPattern() override = default;

    bool IsAtomicNode() const override
    {
        return false;
    }

    std::optional<RenderContext::ContextParam> GetContextParam() const override
    {
        return RenderContext::ContextParam { .type = RenderContext::ContextType::DEPTH, .surfaceName = std::nullopt };
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<DepthComponentLayoutProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<DepthComponentLayoutAlgorithm>();
    }

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override;

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<DepthComponentEventHub>();
    }

    RefPtr<AccessibilityProperty> CreateAccessibilityProperty() override
    {
        return MakeRefPtr<DepthComponentAccessibilityProperty>();
    }

    void OnModifyDone() override;
    void OnAttachToFrameNode() override;
    void OnDetachFromFrameNode(FrameNode* node) override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
#if defined(KIT_3D_ENABLE) && !defined(PREVIEW)
    void OnRebuildFrame() override;
#endif

    void SetBackgroundSource(const OHOS::Ace::DepthBackgroundSource& background);

    OHOS::Ace::DepthBackgroundSource GetBackgroundSource() const
    {
        auto host = GetHost();
        if (!host) {
            return {};
        }
        auto depthLayoutProperty = host->GetLayoutProperty<DepthComponentLayoutProperty>();
        if (!depthLayoutProperty) {
            return {};
        }
        return depthLayoutProperty->GetBackgroundSource().value_or(OHOS::Ace::DepthBackgroundSource());
    }

    const ImageSourceInfo GetBackgroundImageSource() const
    {
        auto backgroundSource = GetBackgroundSource();
        return backgroundSource.IsImage() ? backgroundSource.imageSourceInfo : ImageSourceInfo();
    }

    DepthBackgroundOffset GetBackgroundOffset() const
    {
        auto host = GetHost();
        if (!host) {
            return {};
        }

        auto depthLayoutProperty = host->GetLayoutProperty<DepthComponentLayoutProperty>();
        if (!depthLayoutProperty) {
            return {};
        }
        return depthLayoutProperty->GetBackgroundOffset().value_or(DepthBackgroundOffset());
    }

    std::optional<NG::VectorF> GetBackgroundScale() const
    {
        auto host = GetHost();
        if (!host) {
            return std::nullopt;
        }

        auto depthLayoutProperty = host->GetLayoutProperty<DepthComponentLayoutProperty>();
        if (!depthLayoutProperty) {
            return std::nullopt;
        }
        return depthLayoutProperty->GetBackgroundScale().value_or(std::nullopt);
    }

    bool IsGltfBackground() const
    {
        return GetBackgroundSource().IsGltf();
    }

#if defined(KIT_3D_ENABLE)  && !defined(PREVIEW)
    void UpdateTransformHintChangedCallbackId(std::optional<int32_t> id)
    {
        transformHintChangedCallbackId_ = id;
    }

    bool HasTransformHintChangedCallbackId() const
    {
        return transformHintChangedCallbackId_.has_value();
    }
#endif

    void SetDepthSpace(OHOS::Ace::DepthSpaceType depthSpace)
    {
        depthSpace_ = depthSpace;
    }

    OHOS::Ace::DepthSpaceType GetDepthSpace() const
    {
        return depthSpace_;
    }

    int32_t GetBackgroundImageId()
    {
        if (!backgroundImageId_.has_value()) {
            backgroundImageId_ = ElementRegister::GetInstance()->MakeUniqueId();
        }
        return backgroundImageId_.value();
    }

    bool HasBackgroundImageNode() const
    {
        return backgroundImageId_.has_value();
    }

    void SetDepthMap(const ImageSourceInfo& depthMap)
    {
        depthMap_ = depthMap;
    }

    const ImageSourceInfo& GetDepthMap() const
    {
        return depthMap_;
    }

private:
    ACE_DISALLOW_COPY_AND_MOVE(DepthComponentPattern);
    void SetupBackgroundImageNode();
    void RemoveBackgroundImageNode();
    void ApplyBackgroundOffset(const RefPtr<FrameNode>& backgroundImageNode);
    void ApplyBackgroundScale(const RefPtr<FrameNode>& backgroundImageNode);
    void OnPaint3D();

#ifdef ENABLE_ROSEN_BACKEND
    void LoadDepthMap();
    void OnDepthMapDataReady();
    void OnDepthMapLoadSuccess(const RefPtr<CanvasImage>& canvasImage);
    void TransferDataToRosen();
    std::shared_ptr<OHOS::Rosen::RSDepthNode> GetRSDepthNode() const;
    void TransferDepthSpace(const std::shared_ptr<OHOS::Rosen::RSDepthNode>& rsDepthNode);
    void TransferCameraParams(const std::shared_ptr<OHOS::Rosen::RSDepthNode>& rsDepthNode);
    void TransferLightParams(const std::shared_ptr<OHOS::Rosen::RSDepthNode>& rsDepthNode);
#endif

#if defined(KIT_3D_ENABLE)  && !defined(PREVIEW)
    void InitGltfAdapter();
    void UpdateGltfScene();
    void UpdateGltfCamera();
    void UpdateGltfWindowChange(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config);
    void CleanupGltfResources(bool clearAdapter = false);
    void CreateCustomNativeWindows(float width, float height);
    Render3D::WindowChangeInfo GetWindowChangeInfos(float width, float height) const;
    void UpdateWindowChangeSize(bool recreateWindow);
    void Update3DOffset();
    void Update3DScale();
    bool NeedUpdateWindowInfo();
    void UpdateWindowInfo();
    void MarkRender3D();
#endif

    OHOS::Ace::DepthSpaceType depthSpace_ = OHOS::Ace::DepthSpaceType::INSTANCE;
    ImageSourceInfo depthMap_;
    std::optional<int32_t> backgroundImageId_;

#if defined(KIT_3D_ENABLE) && !defined(PREVIEW)
    BASE_NS::shared_ptr<Render3D::IMrtDepthAdapter> mrtDepthAdapter_;
    std::vector<Render3D::WindowChangeInfo> windowChangeInfos_;
    std::vector<void*> nativeWindows_;
    std::vector<std::shared_ptr<OHOS::Rosen::RSSurfaceNode>> nativeSurfaceNodes_;
    std::vector<sptr<OHOS::Surface>> nativeSurfaces_;
    std::vector<RefPtr<RenderContext>> surfaceRenderContext_;
    bool gltfWindowsInitialized_ = false;
    bool gltfSceneLoaded_ = false;
    std::string lastLoadedGltfPath_;
    uint32_t rotation_ = 0;
    std::optional<int32_t> transformHintChangedCallbackId_;
    bool nativeWindowSetUp_ = false;
    float offsetX_ = 0.0;
    float offsetY_ = 0.0;
    float width3d_ = 0.0;
    float height3d_ = 0.0;
    float lastWidth3d_ = 0.0;
    float lastHeight3d_ = 0.0;
#endif

    RefPtr<ImageLoadingContext> depthMapLoadingCtx_;
    std::string lastLoadedDepthMapKey_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DEPTH_COMPONENT_DEPTH_COMPONENT_PATTERN_H
