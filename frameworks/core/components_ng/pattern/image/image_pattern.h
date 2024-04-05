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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_IMAGE_IMAGE_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_IMAGE_IMAGE_PATTERN_H

#include <memory>

#include "base/geometry/offset.h"
#include "base/memory/referenced.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/event/click_event.h"
#include "core/components_ng/manager/select_overlay/selection_host.h"
#include "core/components_ng/pattern/image/image_event_hub.h"
#include "core/components_ng/pattern/image/image_layout_algorithm.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_render_property.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/manager/select_overlay/select_overlay_client.h"
#include "core/components_ng/render/canvas_image.h"
#include "core/image/image_source_info.h"
#include "interfaces/inner_api/ace/ai/image_analyzer.h"

namespace OHOS::Ace {
class ImageAnalyzerManager;
}

namespace OHOS::Ace::NG {

class ACE_EXPORT ImagePattern : public Pattern, public SelectOverlayClient {
    DECLARE_ACE_TYPE(ImagePattern, Pattern, SelectionHost);

public:
    ImagePattern();
    ~ImagePattern() override;

    std::optional<RenderContext::ContextParam> GetContextParam() const override
    {
        return RenderContext::ContextParam { RenderContext::ContextType::CANVAS };
    }

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override;

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<ImageLayoutProperty>();
    }

    RefPtr<PaintProperty> CreatePaintProperty() override
    {
        return MakeRefPtr<ImageRenderProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<ImageLayoutAlgorithm>(loadingCtx_, altLoadingCtx_);
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<ImageEventHub>();
    }

    // Called on main thread to check if need rerender of the content.
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::NODE, false };
    }

    const RefPtr<CanvasImage>& GetCanvasImage()
    {
        return image_;
    }

    RefPtr<FrameNode> GetClientHost() const override
    {
        return GetHost();
    }

    void CreateObscuredImage();
    void LoadImageDataIfNeed();
    void OnNotifyMemoryLevel(int32_t level) override;
    void OnWindowHide() override;
    void OnWindowShow() override;
    void OnVisibleChange(bool isVisible) override;
    void OnRecycle() override;
    void OnReuse() override;

    void OnAreaChangedInner() override;
    void RemoveAreaChangeInner();
    void CalAndUpdateSelectOverlay();
    OffsetF GetParentGlobalOffset() const;
    void CheckHandles(SelectHandleInfo& handleInfo);

    void EnableDrag();
    bool BetweenSelectedPosition(const Offset& globalOffset) override;

    bool DefaultSupportDrag() override
    {
        return true;
    }

    void SetCopyOption(CopyOptions value)
    {
        copyOption_ = value;
    }

    void SetImageInterpolation(ImageInterpolation value)
    {
        interpolation_ = value;
    }

    std::string GetImageInterpolation()
    {
        switch (interpolation_) {
            case ImageInterpolation::LOW:
                return "LOW";
            case ImageInterpolation::MEDIUM:
                return "MEDIUM";
            case ImageInterpolation::HIGH:
                return "HIGH";
            default:
                return "NONE";
        }
    }

    std::string GetImageFitStr(ImageFit value);

    std::string GetImageRepeatStr(ImageRepeat value);

    std::string GetImageColorFilterStr(const std::vector<float>& colorFilter);

    void SetSyncLoad(bool value)
    {
        syncLoad_ = value;
    }

    void SetImageAnalyzerConfig(const ImageAnalyzerConfig& config);
    void SetImageAnalyzerConfig(void* config);
    void BeforeCreatePaintWrapper() override;
    void DumpInfo() override;
    void DumpLayoutInfo();
    void DumpRenderInfo();
    void DumpAdvanceInfo() override;

    WeakPtr<ImageLoadingContext> GetImageLoadingContext()
    {
        return WeakClaim(AceType::RawPtr(loadingCtx_));
    }

    WeakPtr<ImageLoadingContext> GetAltImageLoadingContext()
    {
        return WeakClaim(AceType::RawPtr(altLoadingCtx_));
    }
    void EnableAnalyzer(bool value);
    bool hasSceneChanged();

protected:
    void RegisterWindowStateChangedCallback();
    void UnregisterWindowStateChangedCallback();
    bool isShow_ = true;

private:
    class ObscuredImage : public CanvasImage {
        void DrawToRSCanvas(
            RSCanvas& canvas, const RSRect& srcRect, const RSRect& dstRect, const BorderRadiusArray& radiusXY) override
        {}
        int32_t GetWidth() const override
        {
            return 0;
        }
        int32_t GetHeight() const override
        {
            return 0;
        }
    };

    void OnAttachToFrameNode() override;
    void OnDetachFromFrameNode(FrameNode* frameNode) override;

    void OnModifyDone() override;
    void UpdateGestureAndDragWhenModify();

    bool IsNeedInitClickEventRecorder() const override
    {
        return true;
    }

    void OnLanguageConfigurationUpdate() override;

    /**
     * @brief Start decoding image after ImageData is ready and dstSize is determined.
     *
     * @param dstSize The size of the image to be decoded.
     */
    void StartDecoding(const SizeF& dstSize);
    void OnImageDataReady();
    void OnImageLoadFail(const std::string& errorMsg);
    void OnImageLoadSuccess();
    void SetImagePaintConfig(const RefPtr<CanvasImage>& canvasImage, const RectF& srcRect, const RectF& dstRect,
        const ImageSourceInfo& sourceInfo, int32_t frameCount = 1);
    void UpdateInternalResource(ImageSourceInfo& sourceInfo);

    void PrepareAnimation(const RefPtr<CanvasImage>& image);
    void SetRedrawCallback(const RefPtr<CanvasImage>& image);
    void SetOnFinishCallback(const RefPtr<CanvasImage>& image);
    void RegisterVisibleAreaChange();

    void InitCopy();
    void HandleCopy();
    void OpenSelectOverlay();
    void CloseSelectOverlay();

    void UpdateFillColorIfForegroundColor();
    void UpdateDragEvent(const RefPtr<OHOS::Ace::DragEvent>& event);

    void ToJsonValue(std::unique_ptr<JsonValue>& json) const override;

    RectF CalcImageContentPaintSize(const RefPtr<GeometryNode>& geometryNode);

    DataReadyNotifyTask CreateDataReadyCallback();
    LoadSuccessNotifyTask CreateLoadSuccessCallback();
    LoadFailNotifyTask CreateLoadFailCallback();

    DataReadyNotifyTask CreateDataReadyCallbackForAlt();
    LoadSuccessNotifyTask CreateLoadSuccessCallbackForAlt();
    LoadFailNotifyTask CreateLoadFailCallbackForAlt();

    void OnColorConfigurationUpdate() override;
    void OnDirectionConfigurationUpdate() override;
    void OnIconConfigurationUpdate() override;
    void OnConfigurationUpdate();
    void ClearImageCache();
    void LoadImage(const ImageSourceInfo& src);
    void LoadAltImage(const ImageSourceInfo& altImageSourceInfo);

    void CreateAnalyzerOverlay();
    void UpdateAnalyzerOverlay();
    void UpdateAnalyzerOverlayLayout();
    void UpdateAnalyzerUIConfig(const RefPtr<NG::GeometryNode>& geometryNode);
    void DestroyAnalyzerOverlay();
    void ReleaseImageAnalyzer();
    bool IsSupportImageAnalyzerFeature();
    void InitDefaultValue();

    CopyOptions copyOption_ = CopyOptions::None;
    ImageInterpolation interpolation_ = ImageInterpolation::NONE;

    RefPtr<ImageLoadingContext> loadingCtx_;
    RefPtr<CanvasImage> image_;
    RectF dstRect_;
    RectF srcRect_;

    RefPtr<CanvasImage> obscuredImage_;

    // clear alt data after [OnImageLoadSuccess] being called
    RefPtr<ImageLoadingContext> altLoadingCtx_;
    RefPtr<CanvasImage> altImage_;
    std::unique_ptr<RectF> altDstRect_;
    std::unique_ptr<RectF> altSrcRect_;

    RefPtr<LongPressEvent> longPressEvent_;
    RefPtr<ClickEvent> clickEvent_;
    RefPtr<InputEvent> mouseEvent_;
    RefPtr<Clipboard> clipboard_;
    RefPtr<SelectOverlayProxy> selectOverlay_;
    std::shared_ptr<ImageAnalyzerManager> imageAnalyzerManager_;

    bool syncLoad_ = false;
    bool isEnableAnalyzer_ = false;
    bool autoResizeDefault_ = true;
    ImageInterpolation interpolationDefault_ = ImageInterpolation::NONE;
    OffsetF parentGlobalOffset_;

    ACE_DISALLOW_COPY_AND_MOVE(ImagePattern);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_IMAGE_IMAGE_PATTERN_H
