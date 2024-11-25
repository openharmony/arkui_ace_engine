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
#include "core/animation/animator.h"
#include "core/animation/picture_animation.h"
#include "core/components/common/layout/constants.h"
#include "core/components/declaration/image/image_animator_declaration.h"
#include "core/components_ng/event/click_event.h"
#include "core/components_ng/manager/select_overlay/selection_host.h"
#include "core/components_ng/pattern/image/image_dfx.h"
#include "core/components_ng/pattern/image/image_event_hub.h"
#include "core/components_ng/pattern/image/image_layout_algorithm.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_overlay_modifier.h"
#include "core/components_ng/pattern/image/image_content_modifier.h"
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
class InspectorFilter;

class ACE_FORCE_EXPORT ImagePattern : public Pattern, public SelectOverlayClient {
    DECLARE_ACE_TYPE(ImagePattern, Pattern, SelectionHost);

public:
    enum class ImageType {
        BASE,
        ANIMATION,
        UNDEFINED,
    };

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
        if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_FOURTEEN)) {
            return { FocusType::NODE, false, FocusStyleType::OUTER_BORDER };
        } else {
            return { FocusType::NODE, false };
        }
    }

    const RefPtr<CanvasImage>& GetCanvasImage()
    {
        return image_;
    }

    const RefPtr<CanvasImage>& GetAltCanvasImage()
    {
        return altImage_;
    }

    RefPtr<FrameNode> GetClientHost() const override
    {
        return GetHost();
    }

    void CreateModifier();
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

    void SetImageQuality(AIImageQuality imageQuality)
    {
        isImageQualityChange_ = (imageQuality_ != imageQuality);
        imageQuality_ = imageQuality;
    }

    void SetOrientation(ImageRotateOrientation orientation)
    {
        isOrientationChange_ = (userOrientation_ != orientation);
        userOrientation_ = orientation;
    }

    ImageRotateOrientation GetOrientation()
    {
        return userOrientation_;
    }

    void UpdateOrientation();

    AIImageQuality GetImageQuality()
    {
        return imageQuality_;
    }

    void SetCopyOption(CopyOptions value)
    {
        copyOption_ = value;
    }

    std::string GetImageFitStr(ImageFit value);

    std::string GetImageRepeatStr(ImageRepeat value);

    std::string GetImageColorFilterStr(const std::vector<float>& colorFilter);

    void SetSyncLoad(bool value)
    {
        syncLoad_ = value;
    }

    bool GetSyncLoad() const
    {
        return syncLoad_;
    }

    void SetNeedBorderRadius(bool needBorderRadius)
    {
        needBorderRadius_ = needBorderRadius;
    }

    void SetImageAnalyzerConfig(const ImageAnalyzerConfig& config);
    void SetImageAnalyzerConfig(void* config);
    void SetImageAIOptions(void* options);
    void BeforeCreatePaintWrapper() override;
    void DumpInfo() override;
    void DumpInfo(std::unique_ptr<JsonValue>& json) override;
    void DumpSimplifyInfo(std::unique_ptr<JsonValue>& json) override;
    void DumpLayoutInfo();
    void DumpImageSourceInfo(const RefPtr<OHOS::Ace::NG::ImageLayoutProperty>& layoutProp);
    inline void DumpAltSourceInfo(const RefPtr<OHOS::Ace::NG::ImageLayoutProperty>& layoutProp);
    inline void DumpImageFit(const RefPtr<OHOS::Ace::NG::ImageLayoutProperty>& layoutProp);
    inline void DumpFitOriginalSize(const RefPtr<OHOS::Ace::NG::ImageLayoutProperty>& layoutProp);
    inline void DumpSourceSize(const RefPtr<OHOS::Ace::NG::ImageLayoutProperty>& layoutProp);
    inline void DumpAutoResize(const RefPtr<OHOS::Ace::NG::ImageLayoutProperty>& layoutProp);
    void DumpLayoutInfo(std::unique_ptr<JsonValue>& json);
    void DumpRenderInfo();
    inline void DumpRenderMode(const RefPtr<OHOS::Ace::NG::ImageRenderProperty>& renderProp);
    inline void DumpImageRepeat(const RefPtr<OHOS::Ace::NG::ImageRenderProperty>& renderProp);
    inline void DumpImageColorFilter(const RefPtr<OHOS::Ace::NG::ImageRenderProperty>& renderProp);
    inline void DumpFillColor(const RefPtr<OHOS::Ace::NG::ImageRenderProperty>& renderProp);
    inline void DumpDynamicRangeMode(const RefPtr<OHOS::Ace::NG::ImageRenderProperty>& renderProp);
    inline void DumpMatchTextDirection(const RefPtr<OHOS::Ace::NG::ImageRenderProperty>& renderProp);
    inline void DumpSmoothEdge(const RefPtr<OHOS::Ace::NG::ImageRenderProperty>& renderProp);
    inline void DumpResizable(const RefPtr<OHOS::Ace::NG::ImageRenderProperty>& renderProp);
    inline void DumpInterpolation(const RefPtr<OHOS::Ace::NG::ImageRenderProperty>& renderProp);
    void DumpBorderRadiusProperties(const RefPtr<OHOS::Ace::NG::ImageRenderProperty>& renderProp);
    inline void DumpOtherInfo();
    void DumpRenderInfo(std::unique_ptr<JsonValue>& json);
    void DumpAdvanceInfo() override;
    void DumpAdvanceInfo(std::unique_ptr<JsonValue>& json) override;
    void DumpSvgInfo();
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
    void OnSensitiveStyleChange(bool isSensitive) override;

    //animation
    struct CacheImageStruct {
        CacheImageStruct() = default;
        CacheImageStruct(const RefPtr<FrameNode>& imageNode) : imageNode(imageNode) {}
        virtual ~CacheImageStruct() = default;
        RefPtr<FrameNode> imageNode;
        int32_t index = 0;
        bool isLoaded = false;
    };

    void ImageAnimatorPattern();
    void SetImages(std::vector<ImageProperties>&& images)
    {
        CHECK_NULL_VOID(images.size());
        images_ = std::move(images);
        durationTotal_ = 0;
        for (const auto& childImage : images_) {
            if ((!childImage.src.empty() || childImage.pixelMap != nullptr) && childImage.duration > 0) {
                durationTotal_ += childImage.duration;
            }
        }
        imagesChangedFlag_ = true;
        RegisterVisibleAreaChange();
    }

    void ResetImages()
    {
        images_.clear();
    }
    void ResetImage();
    void ResetAltImage();
    void ResetImageProperties();

    void ResetImageAndAlt();

    void ResetPictureSize();

    bool GetHasSizeChanged()
    {
        return hasSizeChanged;
    }

    void StartAnimation()
    {
        status_ = Animator::Status::RUNNING;
    }

    void StopAnimation()
    {
        status_ = Animator::Status::STOPPED;
        OnAnimatedModifyDone();
    }

    void SetImageType(ImageType imageType)
    {
        imageType_ = imageType;
    }

    ImageType GetImageType()
    {
        return imageType_;
    }

    bool GetIsAnimation() const
    {
        return imageType_ == ImageType::ANIMATION;
    }

    bool IsAtomicNode() const override
    {
        return true;
    }

    bool AllowVisibleAreaCheck() const override;

    void OnInActive() override
    {
        if (status_ == Animator::Status::RUNNING) {
            animator_->Pause();
        }
    }

    void OnActive() override
    {
        if (status_ == Animator::Status::RUNNING && animator_->GetStatus() != Animator::Status::RUNNING) {
            auto host = GetHost();
            CHECK_NULL_VOID(host);
            if (!animator_->HasScheduler()) {
                auto context = host->GetContextRefPtr();
                if (context) {
                    animator_->AttachScheduler(context);
                } else {
                    TAG_LOGW(AceLogTag::ACE_IMAGE, "pipelineContext is null.");
                }
            }
            animator_->Forward();
        }
    }

    void SetDuration(int32_t duration);
    void SetIteration(int32_t iteration);

    void SetSrcUndefined(bool isUndefined)
    {
        isSrcUndefined_ = isUndefined;
    }

    void SetImageAnimator(bool isImageAnimator)
    {
        isImageAnimator_ = isImageAnimator;
    }

    bool GetNeedLoadAlt()
    {
        return needLoadAlt_;
    }

    void SetNeedLoadAlt(bool needLoadAlt)
    {
        needLoadAlt_ = needLoadAlt;
    }

    void SetOnProgressCallback(std::function<void(const uint32_t& dlNow, const uint32_t& dlTotal)>&& onProgress);

    SizeF GetRawImageSize()
    {
        if (!loadingCtx_) {
            return SizeF(-1.0, -1.0);
        }
        return loadingCtx_->GetImageSize();
    }

    void OnVisibleAreaChange(bool visible = true, double ratio = 0.0);

    bool GetDefaultAutoResize()
    {
        return autoResizeDefault_;
    }

    ImageInterpolation GetDefaultInterpolation()
    {
        return interpolationDefault_;
    }
    void InitOnKeyEvent();

    void SetIsComponentSnapshotNode(bool isComponentSnapshotNode)
    {
        isComponentSnapshotNode_ = isComponentSnapshotNode;
    }

    void SetRenderedImageInfo(const RenderedImageInfo& renderedImageInfo)
    {
        renderedImageInfo_ = renderedImageInfo;
    }

protected:
    void RegisterWindowStateChangedCallback();
    void UnregisterWindowStateChangedCallback();
    bool isShow_ = true;
    RefPtr<ImageOverlayModifier> overlayMod_;
    RefPtr<ImageContentModifier> contentMod_;

private:
    class ObscuredImage : public CanvasImage {
        void DrawToRSCanvas(
            RSCanvas& canvas, const RSRect& srcRect, const RSRect& dstRect, const BorderRadiusArray& radiusXY) override
        {}
        void DrawRect(RSCanvas& canvas, const RSRect& srcRect, const RSRect& dstRect) override
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
    bool CheckIfNeedLayout();
    void OnImageDataReady();
    void OnCompleteInDataReady();
    void OnImageLoadFail(const std::string& errorMsg);
    void OnImageLoadSuccess();
    void ApplyAIModificationsToImage();
    void SetImagePaintConfig(const RefPtr<CanvasImage>& canvasImage, const RectF& srcRect, const RectF& dstRect,
        const ImageSourceInfo& sourceInfo, int32_t frameCount = 1);
    void UpdateInternalResource(ImageSourceInfo& sourceInfo);

    void PrepareAnimation(const RefPtr<CanvasImage>& image);
    void SetRedrawCallback(const RefPtr<CanvasImage>& image);
    void SetOnFinishCallback(const RefPtr<CanvasImage>& image);
    void RegisterVisibleAreaChange(bool isCalcClip = true);
    void TriggerVisibleAreaChangeForChild(const RefPtr<UINode>& node, bool visible, double ratio);

    void InitCopy();
    void HandleCopy();
    void OpenSelectOverlay();
    void CloseSelectOverlay();

    void TriggerFirstVisibleAreaChange();

    void UpdateDragEvent(const RefPtr<OHOS::Ace::DragEvent>& event);

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override;

    RectF CalcImageContentPaintSize(const RefPtr<GeometryNode>& geometryNode);

    DataReadyNotifyTask CreateDataReadyCallback();
    LoadSuccessNotifyTask CreateLoadSuccessCallback();
    LoadFailNotifyTask CreateLoadFailCallback();
    OnCompleteInDataReadyNotifyTask CreateCompleteCallBackInDataReady();

    DataReadyNotifyTask CreateDataReadyCallbackForAlt();
    LoadSuccessNotifyTask CreateLoadSuccessCallbackForAlt();
    LoadFailNotifyTask CreateLoadFailCallbackForAlt();

    void OnColorConfigurationUpdate() override;
    void OnDirectionConfigurationUpdate() override;
    void OnIconConfigurationUpdate() override;
    void OnConfigurationUpdate();
    void LoadImage(const ImageSourceInfo& src, const PropertyChangeFlag& propertyChangeFlag, VisibleType visibleType);
    void LoadAltImage(const ImageSourceInfo& altImageSourceInfo);

    void CreateAnalyzerOverlay();
    void UpdateAnalyzerOverlay();
    void UpdateAnalyzerOverlayLayout();
    void UpdateAnalyzerUIConfig(const RefPtr<NG::GeometryNode>& geometryNode);
    void DestroyAnalyzerOverlay();
    void ReleaseImageAnalyzer();
    bool IsSupportImageAnalyzerFeature();
    void InitDefaultValue();
    void ClearAltData();
    void UpdateSvgSmoothEdgeValue();

    //animation
    RefPtr<PictureAnimation<int32_t>> CreatePictureAnimation(int32_t size);
    void AdaptSelfSize();
    void SetShowingIndex(int32_t index);
    void UpdateShowingImageInfo(const RefPtr<FrameNode>& imageFrameNode, int32_t index);
    void UpdateCacheImageInfo(CacheImageStruct& cacheImage, int32_t index);
    std::list<CacheImageStruct>::iterator FindCacheImageNode(const RefPtr<PixelMap>& src);
    int32_t GetNextIndex(int32_t preIndex);
    void GenerateCachedImages();
    void AddImageLoadSuccessEvent(const RefPtr<FrameNode>& imageFrameNode);
    static bool IsShowingSrc(const RefPtr<FrameNode>& imageFrameNode, const RefPtr<PixelMap>& src);
    bool IsFormRender();
    void UpdateFormDurationByRemainder();
    void ResetFormAnimationStartTime();
    void ResetFormAnimationFlag();
    void OnAnimatedModifyDone();
    void OnImageModifyDone();
    void SetColorFilter(const RefPtr<FrameNode>& imageFrameNode);
    void SetImageFit(const RefPtr<FrameNode>& imageFrameNode);
    void ControlAnimation(int32_t index);
    void SetObscured();
    void OnKeyEvent();

    CopyOptions copyOption_ = CopyOptions::None;
    ImageInterpolation interpolation_ = ImageInterpolation::LOW;
    bool needLoadAlt_ = true;
    RenderedImageInfo renderedImageInfo_;

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
    ImageDfxConfig imageDfxConfig_;
    ImageDfxConfig altImageDfxConfig_;
    bool enableDrag_ = false;

    std::function<bool(const KeyEvent& event)> keyEventCallback_ = nullptr;
    bool syncLoad_ = false;
    bool needBorderRadius_ = false;
    AIImageQuality imageQuality_ = AIImageQuality::NONE;
    bool isImageQualityChange_ = false;
    bool isEnableAnalyzer_ = false;
    bool autoResizeDefault_ = true;
    bool isSensitive_ = false;
    ImageInterpolation interpolationDefault_ = ImageInterpolation::NONE;
    ImageRotateOrientation userOrientation_ = ImageRotateOrientation::UP;
    ImageRotateOrientation selfOrientation_ = ImageRotateOrientation::UP;
    ImageRotateOrientation joinOrientation_ = ImageRotateOrientation::UP;
    Color selectedColor_;
    float smoothEdge_ = 0.0f;
    OffsetF parentGlobalOffset_;
    bool isSelected_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(ImagePattern);

    //animation
    ImageType imageType_ = ImageType::BASE;
    RefPtr<Animator> animator_;
    std::vector<ImageProperties> images_;
    std::list<CacheImageStruct> cacheImages_;
    Animator::Status status_ = Animator::Status::IDLE;
    int32_t durationTotal_ = 0;
    int32_t nowImageIndex_ = 0;
    uint64_t repeatCallbackId_ = 0;
    bool imagesChangedFlag_ = false;
    bool firstUpdateEvent_ = true;
    bool isLayouted_ = false;
    int64_t formAnimationStartTime_ = 0;
    int32_t formAnimationRemainder_ = 0;
    bool isOrientationChange_ = false;
    bool isFormAnimationStart_ = true;
    bool isFormAnimationEnd_ = false;
    bool isImageAnimator_ = false;
    bool hasSizeChanged = false;
    bool isPixelMapChanged_ = false;
    bool isSrcUndefined_ = false;
    bool isComponentSnapshotNode_ = false;

    std::function<void(const uint32_t& dlNow, const uint32_t& dlTotal)> onProgressCallback_ = nullptr;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_IMAGE_IMAGE_PATTERN_H
