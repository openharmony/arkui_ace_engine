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

#include "third_party/libphonenumber/cpp/src/phonenumbers/base/logging.h"
#include "core/components_ng/pattern/image/image_event_hub.h"
#include "core/components_ng/pattern/image/image_overlay_modifier.h"
#include "core/components_ng/property/border_property.h"
#include "core/image/image_source_info.h"
#define NAPI_VERSION 8

#include <array>
#include <cstdint>
#include <memory>

#include "base/geometry/dimension_offset.h"
#include "base/geometry/matrix4.h"
#include "base/geometry/ng/rect_t.h"
#include "base/geometry/ng/vector.h"
#include "base/log/dump_log.h"
#include "base/utils/utils.h"
#include "core/common/ace_engine_ext.h"
#include "core/common/ai/image_analyzer_manager.h"
#include "core/common/container.h"
#include "core/common/frontend.h"
#include "core/common/udmf/udmf_client.h"
#include "core/components/common/layout/constants.h"
#include "core/components/image/image_theme.h"
#include "core/components/text/text_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/manager/select_overlay/select_overlay_manager.h"
#include "core/components_ng/pattern/image/image_paint_method.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/property/measure_property.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/common/ace_engine_ext.h"
#include "core/common/ai/image_analyzer_adapter.h"
#include "core/common/container.h"
#include "core/common/udmf/udmf_client.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t DEFAULT_DURATION = 1000; // ms
constexpr uint32_t CRITICAL_TIME = 50;      // ms. If show time of image is less than this, use more cacheImages.
constexpr int64_t MICROSEC_TO_MILLISEC = 1000;
constexpr int32_t DEFAULT_ITERATIONS = 1;
constexpr int32_t MEMORY_LEVEL_LOW_STATUS = 1;
} // namespace

constexpr float BOX_EPSILON = 0.5f;
constexpr float IMAGE_SENSITIVE_RADIUS = 80.0f;
constexpr double IMAGE_SENSITIVE_SATURATION = 1.0;
constexpr double IMAGE_SENSITIVE_BRIGHTNESS = 1.08;

ImagePattern::ImagePattern()
{
    InitDefaultValue();
    ImageAnimatorPattern();
}

ImagePattern::~ImagePattern()
{
    if (isEnableAnalyzer_) {
        ReleaseImageAnalyzer();
    }
}

DataReadyNotifyTask ImagePattern::CreateDataReadyCallback()
{
    return [weak = WeakClaim(this)](const ImageSourceInfo& sourceInfo) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto imageLayoutProperty = pattern->GetLayoutProperty<ImageLayoutProperty>();
        CHECK_NULL_VOID(imageLayoutProperty);
        auto currentSourceInfo = imageLayoutProperty->GetImageSourceInfo().value_or(ImageSourceInfo(""));
        if (currentSourceInfo != sourceInfo) {
            TAG_LOGW(AceLogTag::ACE_IMAGE, "sourceInfo does not match, ignore current callback. "
                 "current: %{private}s vs callback's: %{private}s",
                currentSourceInfo.ToString().c_str(), sourceInfo.ToString().c_str());
            return;
        }
        pattern->OnImageDataReady();
    };
}

LoadSuccessNotifyTask ImagePattern::CreateLoadSuccessCallback()
{
    return [weak = WeakClaim(this)](const ImageSourceInfo& sourceInfo) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto imageLayoutProperty = pattern->GetLayoutProperty<ImageLayoutProperty>();
        CHECK_NULL_VOID(imageLayoutProperty);
        auto currentSourceInfo = imageLayoutProperty->GetImageSourceInfo().value_or(ImageSourceInfo(""));
        if (currentSourceInfo != sourceInfo) {
            TAG_LOGW(AceLogTag::ACE_IMAGE, "sourceInfo does not match, ignore current callback. "
                 "current: %{private}s vs callback's: %{private}s",
                currentSourceInfo.ToString().c_str(), sourceInfo.ToString().c_str());
            return;
        }
        pattern->OnImageLoadSuccess();
    };
}

LoadFailNotifyTask ImagePattern::CreateLoadFailCallback()
{
    return [weak = WeakClaim(this)](const ImageSourceInfo& sourceInfo, const std::string& errorMsg) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto imageLayoutProperty = pattern->GetLayoutProperty<ImageLayoutProperty>();
        CHECK_NULL_VOID(imageLayoutProperty);
        auto currentSourceInfo = imageLayoutProperty->GetImageSourceInfo().value_or(ImageSourceInfo(""));
        if (currentSourceInfo != sourceInfo) {
            TAG_LOGW(AceLogTag::ACE_IMAGE, "sourceInfo does not match, ignore current callback. "
                 "current: %{private}s vs callback's: %{private}s",
                currentSourceInfo.ToString().c_str(), sourceInfo.ToString().c_str());
            return;
        }
        if (!currentSourceInfo.IsFromReset()) {
            pattern->OnImageLoadFail(errorMsg);
        }
    };
}

OnCompleteInDataReadyNotifyTask ImagePattern::CreateCompleteCallBackInDataReady()
{
    return [weak = WeakClaim(this)](const ImageSourceInfo& sourceInfo) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto imageLayoutProperty = pattern->GetLayoutProperty<ImageLayoutProperty>();
        CHECK_NULL_VOID(imageLayoutProperty);
        auto currentSourceInfo = imageLayoutProperty->GetImageSourceInfo().value_or(ImageSourceInfo(""));
        if (currentSourceInfo != sourceInfo) {
            TAG_LOGW(AceLogTag::ACE_IMAGE,
                "sourceInfo does not match, ignore current callback. "
                "current: %{private}s vs callback's: %{private}s",
                currentSourceInfo.ToString().c_str(), sourceInfo.ToString().c_str());
            return;
        }
        pattern->OnCompleteInDataReady();
    };
}

void ImagePattern::OnCompleteInDataReady()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    const auto& geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto imageEventHub = GetEventHub<ImageEventHub>();
    CHECK_NULL_VOID(imageEventHub);
    CHECK_NULL_VOID(loadingCtx_);
    LoadImageSuccessEvent event(loadingCtx_->GetImageSize().Width(), loadingCtx_->GetImageSize().Height(),
        geometryNode->GetFrameSize().Width(), geometryNode->GetFrameSize().Height(), 0,
        geometryNode->GetContentSize().Width(), geometryNode->GetContentSize().Height(),
        geometryNode->GetContentOffset().GetX(), geometryNode->GetContentOffset().GetY());
    imageEventHub->FireCompleteEvent(event);
}

void ImagePattern::TriggerFirstVisibleAreaChange()
{
    if (isComponentSnapshotNode_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    RectF frameRect;
    RectF visibleInnerRect;
    RectF visibleRect;
    host->GetVisibleRectWithClip(visibleRect, visibleInnerRect, frameRect);
    OnVisibleAreaChange(GreatNotEqual(visibleInnerRect.Width(), 0.0) && GreatNotEqual(visibleInnerRect.Height(), 0.0));
}

void ImagePattern::PrepareAnimation(const RefPtr<CanvasImage>& image)
{
    if (image->IsStatic()) {
        return;
    }
    RegisterVisibleAreaChange();
    TriggerFirstVisibleAreaChange();
    SetOnFinishCallback(image);
    SetRedrawCallback(image);
    // GIF images are not played by default, but depend on OnVisibleAreaChange callback.
    image->ControlAnimation(gifAnimation_);
}

void ImagePattern::SetOnFinishCallback(const RefPtr<CanvasImage>& image)
{
    CHECK_NULL_VOID(image);
    image->SetOnFinishCallback([weak = WeakPtr(GetHost())] {
        auto imageNode = weak.Upgrade();
        CHECK_NULL_VOID(imageNode);
        auto eventHub = imageNode->GetEventHub<ImageEventHub>();
        if (eventHub) {
            eventHub->FireFinishEvent();
        }
    });
}

void ImagePattern::SetRedrawCallback(const RefPtr<CanvasImage>& image)
{
    CHECK_NULL_VOID(image);
    // set animation flush function for svg / gif
    image->SetRedrawCallback([weak = WeakPtr(GetHost())] {
        auto imageNode = weak.Upgrade();
        CHECK_NULL_VOID(imageNode);
        imageNode->MarkNeedRenderOnly();
    });
}

void ImagePattern::RegisterVisibleAreaChange(bool isCalcClip)
{
    auto pipeline = GetContext();
    // register to onVisibleAreaChange
    CHECK_NULL_VOID(pipeline);
    auto callback = [weak = WeakClaim(this)](bool visible, double ratio) {
        auto self = weak.Upgrade();
        CHECK_NULL_VOID(self);
        self->OnVisibleAreaChange(visible, ratio);
    };
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    // add visibleAreaChangeNode(inner callback)
    std::vector<double> ratioList = {0.0};
    pipeline->AddVisibleAreaChangeNode(host, ratioList, callback, false, isCalcClip);
}

void ImagePattern::CheckHandles(SelectHandleInfo& handleInfo)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    if (!renderContext->GetClipEdge().value_or(true)) {
        return;
    }
    // use global offset.
    const auto& geometryNode = host->GetGeometryNode();
    auto contentRect = geometryNode->GetContentRect();
    RectF visibleContentRect(contentRect.GetOffset() + parentGlobalOffset_, contentRect.GetSize());
    auto parent = host->GetAncestorNodeOfFrame();
    visibleContentRect = GetVisibleContentRect(parent, visibleContentRect);
    auto paintRect = handleInfo.paintRect;
    PointF bottomPoint = { paintRect.Left(), paintRect.Bottom() - BOX_EPSILON };
    PointF topPoint = { paintRect.Left(), paintRect.Top() + BOX_EPSILON };
    handleInfo.isShow = visibleContentRect.IsInRegion(bottomPoint) && visibleContentRect.IsInRegion(topPoint);
}

void ImagePattern::CalAndUpdateSelectOverlay()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto rect = host->GetTransformRectRelativeToWindow();
    SelectOverlayInfo info;
    const auto& geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    SizeF handleSize = {
        SelectHandleInfo::GetDefaultLineWidth().ConvertToPx(),
        geometryNode->GetContentSize().Height() };
    info.firstHandle.paintRect = RectF(rect.GetOffset(), handleSize);
    CheckHandles(info.firstHandle);
    OffsetF offset(rect.Width() - handleSize.Width(), rect.Height() - handleSize.Height());
    info.secondHandle.paintRect = RectF(rect.GetOffset() + offset, handleSize);
    CheckHandles(info.secondHandle);
    selectOverlay_->UpdateFirstAndSecondHandleInfo(info.firstHandle, info.secondHandle);
}

OffsetF ImagePattern::GetParentGlobalOffset() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, {});
    auto pipeline = host->GetContext();
    CHECK_NULL_RETURN(pipeline, {});
    auto rootOffset = pipeline->GetRootRect().GetOffset();
    return host->GetPaintRectOffset() - rootOffset;
}

void ImagePattern::OnAreaChangedInner()
{
    if (selectOverlay_ && !selectOverlay_->IsClosed()) {
        auto parentGlobalOffset = GetParentGlobalOffset();
        if (parentGlobalOffset != parentGlobalOffset_) {
            parentGlobalOffset_ = parentGlobalOffset;
            CalAndUpdateSelectOverlay();
        }
    }
}

void ImagePattern::RemoveAreaChangeInner()
{
    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<ImageEventHub>();
    CHECK_NULL_VOID(eventHub);
    if (eventHub->HasOnAreaChanged()) {
        return;
    }
    pipeline->RemoveOnAreaChangeNode(host->GetId());
}

RectF ImagePattern::CalcImageContentPaintSize(const RefPtr<GeometryNode>& geometryNode)
{
    RectF paintSize;
    auto imageRenderProperty = GetPaintProperty<ImageRenderProperty>();
    CHECK_NULL_RETURN(imageRenderProperty, paintSize);
    ImageRepeat repeat = imageRenderProperty->GetImageRepeat().value_or(ImageRepeat::NO_REPEAT);
    bool imageRepeatX = repeat == ImageRepeat::REPEAT || repeat == ImageRepeat::REPEAT_X;
    bool imageRepeatY = repeat == ImageRepeat::REPEAT || repeat == ImageRepeat::REPEAT_Y;

    if (loadingCtx_->GetSourceInfo().IsSvg()) {
        const float invalidValue = -1;
        paintSize.SetWidth(dstRect_.IsValid() ? dstRect_.Width() : invalidValue);
        paintSize.SetHeight(dstRect_.IsValid() ? dstRect_.Height() : invalidValue);
        paintSize.SetLeft(
            dstRect_.IsValid() ? dstRect_.GetX() + geometryNode->GetContentOffset().GetX() : invalidValue);
        paintSize.SetTop(dstRect_.IsValid() ? dstRect_.GetY() + geometryNode->GetContentOffset().GetY() : invalidValue);
    } else {
        paintSize.SetWidth(imageRepeatX ? geometryNode->GetContentSize().Width() : dstRect_.Width());
        paintSize.SetHeight(imageRepeatY ? geometryNode->GetContentSize().Height() : dstRect_.Height());
        paintSize.SetLeft((imageRepeatX ? 0 : dstRect_.GetX()) + geometryNode->GetContentOffset().GetX());
        paintSize.SetTop((imageRepeatY ? 0 : dstRect_.GetY()) + geometryNode->GetContentOffset().GetY());
    }
    return paintSize;
}

void ImagePattern::ClearAltData()
{
    altLoadingCtx_ = nullptr;
    altImage_ = nullptr;
    altDstRect_.reset();
    altSrcRect_.reset();
}

void ImagePattern::OnImageLoadSuccess()
{
    CHECK_NULL_VOID(loadingCtx_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    const auto& geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);

    image_ = loadingCtx_->MoveCanvasImage();
    CHECK_NULL_VOID(image_);
    srcRect_ = loadingCtx_->GetSrcRect();
    dstRect_ = loadingCtx_->GetDstRect();
    auto srcInfo = loadingCtx_->GetSourceInfo();
    auto frameCount = loadingCtx_->GetFrameCount();

    RectF paintRect = CalcImageContentPaintSize(geometryNode);
    LoadImageSuccessEvent event(loadingCtx_->GetImageSize().Width(), loadingCtx_->GetImageSize().Height(),
        geometryNode->GetFrameSize().Width(), geometryNode->GetFrameSize().Height(), 1, paintRect.Width(),
        paintRect.Height(), paintRect.GetX(), paintRect.GetY());

    SetImagePaintConfig(image_, srcRect_, dstRect_, srcInfo, frameCount);
    UpdateSvgSmoothEdgeValue();
    PrepareAnimation(image_);
    if (host->IsDraggable()) {
        EnableDrag();
    }
    ClearAltData();

    auto eventHub = GetEventHub<ImageEventHub>();
    if (eventHub) {
        eventHub->FireCompleteEvent(event);
    }

    if (IsSupportImageAnalyzerFeature()) {
        if (isPixelMapChanged_) {
            UpdateAnalyzerOverlay();
        }
        UpdateAnalyzerUIConfig(geometryNode);
        auto context = host->GetContext();
        CHECK_NULL_VOID(context);
        auto uiTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
        uiTaskExecutor.PostTask([weak = WeakClaim(this)] {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            ContainerScope scope(pattern->GetHostInstanceId());
            pattern->CreateAnalyzerOverlay();
        }, "ArkUIImageCreateAnalyzerOverlay");
    }
    ACE_LAYOUT_SCOPED_TRACE(
        "OnImageLoadSuccess[self:%d][src:%s]", host->GetId(), loadingCtx_->GetSourceInfo().ToString().c_str());
    if (SystemProperties::GetDebugEnabled()) {
        TAG_LOGD(AceLogTag::ACE_IMAGE,
            "imageLoadSuccess src=%{private}s", loadingCtx_->GetSourceInfo().ToString().c_str());
    }
    host->MarkNeedRenderOnly();
}

bool ImagePattern::CheckIfNeedLayout()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, true);
    CHECK_NULL_RETURN(host->GetGeometryNode()->GetContent(), true);
    const auto& props = DynamicCast<ImageLayoutProperty>(host->GetLayoutProperty());
    CHECK_NULL_RETURN(props, true);
    const auto& layoutConstraint = props->GetCalcLayoutConstraint();
    CHECK_NULL_RETURN(layoutConstraint, true);
    return !(layoutConstraint->selfIdealSize && layoutConstraint->selfIdealSize->IsValid());
}

void ImagePattern::OnImageDataReady()
{
    CHECK_NULL_VOID(loadingCtx_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    const auto& geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);

    if (CheckIfNeedLayout()) {
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        return;
    }

    // 1. If PropertyChangeFlag contains PROPERTY_UPDATE_MEASURE,
    //    the image will be decoded after layout.
    // 2. The image node in imageAnimator will not be decoded after layout, decode directly.
    auto layoutProp = host->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(layoutProp);
    if (!((layoutProp->GetPropertyChangeFlag() & PROPERTY_UPDATE_MEASURE) == PROPERTY_UPDATE_MEASURE) ||
        isImageAnimator_) {
        StartDecoding(geometryNode->GetContentSize());
    }
}

void ImagePattern::OnImageLoadFail(const std::string& errorMsg)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    const auto& geometryNode = host->GetGeometryNode();
    auto imageEventHub = GetEventHub<ImageEventHub>();
    CHECK_NULL_VOID(imageEventHub);
    LoadImageFailEvent event(
        geometryNode->GetFrameSize().Width(), geometryNode->GetFrameSize().Height(), errorMsg);
    imageEventHub->FireErrorEvent(event);
}

void ImagePattern::StartDecoding(const SizeF& dstSize)
{
    // if layout size has not decided yet, resize target can not be calculated
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (!host->GetGeometryNode()->GetContent()) {
        return;
    }

    const auto& props = DynamicCast<ImageLayoutProperty>(host->GetLayoutProperty());
    CHECK_NULL_VOID(props);
    bool autoResize = props->GetAutoResize().value_or(autoResizeDefault_);

    ImageFit imageFit = props->GetImageFit().value_or(ImageFit::COVER);
    const std::optional<SizeF>& sourceSize = props->GetSourceSize();
    auto renderProp = host->GetPaintProperty<ImageRenderProperty>();
    bool hasValidSlice = renderProp && (renderProp->HasImageResizableSlice() || renderProp->HasImageResizableLattice());
    DynamicRangeMode dynamicMode = DynamicRangeMode::STANDARD;
    bool isHdrDecoderNeed = false;
    if (renderProp && renderProp->HasDynamicMode()) {
        isHdrDecoderNeed = true;
        dynamicMode = renderProp->GetDynamicMode().value_or(DynamicRangeMode::STANDARD);
    }

    if (loadingCtx_) {
        loadingCtx_->SetIsHdrDecoderNeed(isHdrDecoderNeed);
        loadingCtx_->SetDynamicRangeMode(dynamicMode);
        loadingCtx_->SetImageQuality(GetImageQuality());
        loadingCtx_->MakeCanvasImageIfNeed(dstSize, autoResize, imageFit, sourceSize, hasValidSlice);
    }
    if (altLoadingCtx_) {
        altLoadingCtx_->MakeCanvasImageIfNeed(dstSize, autoResize, imageFit, sourceSize, hasValidSlice);
    }
}

void ImagePattern::UpdateSvgSmoothEdgeValue()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<ImageTheme>();
    CHECK_NULL_VOID(theme);
    auto renderProp = GetPaintProperty<ImageRenderProperty>();
    CHECK_NULL_VOID(renderProp);
    renderProp->UpdateSmoothEdge(std::max(theme->GetMinEdgeAntialiasing(), renderProp->GetSmoothEdge().value_or(0.0f)));
}

void ImagePattern::SetImagePaintConfig(const RefPtr<CanvasImage>& canvasImage, const RectF& srcRect,
    const RectF& dstRect, const ImageSourceInfo& sourceInfo, int32_t frameCount)
{
    auto layoutProps = GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(layoutProps);

    ImagePaintConfig config {
        .srcRect_ = srcRect,
        .dstRect_ = dstRect,
    };
    config.imageFit_ = layoutProps->GetImageFit().value_or(ImageFit::COVER);
    config.isSvg_ = sourceInfo.IsSvg();
    config.frameCount_ = frameCount;
    config.sourceInfo_ = sourceInfo;
    auto host = GetHost();
    if (!host) {
        canvasImage->SetPaintConfig(config);
        return;
    }
    auto renderContext = host->GetRenderContext();
    if (!renderContext || !renderContext->HasBorderRadius()) {
        canvasImage->SetPaintConfig(config);
        return;
    }

    canvasImage->SetPaintConfig(config);
}

RefPtr<NodePaintMethod> ImagePattern::CreateNodePaintMethod()
{
    bool sensitive = false;
    if (isSensitive_) {
        auto host = GetHost();
        CHECK_NULL_RETURN(host, nullptr);
        sensitive = host->IsPrivacySensitive();
    }
    if (!overlayMod_) {
        overlayMod_ = MakeRefPtr<ImageOverlayModifier>(selectedColor_);
    }
    if (image_) {
        return MakeRefPtr<ImagePaintMethod>(image_, isSelected_, overlayMod_, sensitive, interpolationDefault_);
    }
    if (altImage_ && altDstRect_ && altSrcRect_) {
        return MakeRefPtr<ImagePaintMethod>(altImage_, isSelected_, overlayMod_, sensitive, interpolationDefault_);
    }
    CreateObscuredImage();
    if (obscuredImage_) {
        return MakeRefPtr<ImagePaintMethod>(
            obscuredImage_, isSelected_, overlayMod_, sensitive, interpolationDefault_);
    }
    return MakeRefPtr<ImagePaintMethod>(nullptr, isSelected_, overlayMod_, sensitive, interpolationDefault_);
}

bool ImagePattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (!isLayouted_ && GetIsAnimation()) {
        isLayouted_ = true;
        if (images_.size()) {
            int32_t nextIndex = GetNextIndex(nowImageIndex_);
            for (auto& cacheImage : cacheImages_) {
                UpdateCacheImageInfo(cacheImage, nextIndex);
                nextIndex = GetNextIndex(nextIndex);
            }
        }
        return false;
    }

    if (config.skipMeasure || dirty->SkipMeasureContent()) {
        return false;
    }

    const auto& dstSize = dirty->GetGeometryNode()->GetContentSize();
    StartDecoding(dstSize);

    if (loadingCtx_) {
        auto renderProp = GetPaintProperty<ImageRenderProperty>();
        if (renderProp && (renderProp->HasImageResizableSlice() || renderProp->HasImageResizableLattice()) && image_) {
            loadingCtx_->ResizableCalcDstSize();
            SetImagePaintConfig(image_, loadingCtx_->GetSrcRect(), loadingCtx_->GetDstRect(), loadingCtx_->GetSrc(),
                loadingCtx_->GetFrameCount());
        }
    }

    if (altLoadingCtx_) {
        auto renderProp = GetPaintProperty<ImageRenderProperty>();
        if (renderProp && (renderProp->HasImageResizableSlice() || renderProp->HasImageResizableLattice()) &&
            altImage_) {
            altLoadingCtx_->ResizableCalcDstSize();
            SetImagePaintConfig(altImage_, altLoadingCtx_->GetSrcRect(), altLoadingCtx_->GetDstRect(),
                altLoadingCtx_->GetSrc(), altLoadingCtx_->GetFrameCount());
        }
    }

    if (IsSupportImageAnalyzerFeature()) {
        UpdateAnalyzerUIConfig(dirty->GetGeometryNode());
    }

    return image_ || altImage_;
}

void ImagePattern::CreateObscuredImage()
{
    auto props = GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(props);
    auto layoutConstraint = props->GetLayoutConstraint();
    CHECK_NULL_VOID(layoutConstraint);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto sourceInfo = props->GetImageSourceInfo().value_or(ImageSourceInfo(""));
    auto reasons = host->GetRenderContext()->GetObscured().value_or(std::vector<ObscuredReasons>());
    if (reasons.size() && layoutConstraint->selfIdealSize.IsValid()) {
        if (!obscuredImage_) {
            obscuredImage_ = MakeRefPtr<ObscuredImage>();
            SetImagePaintConfig(obscuredImage_, srcRect_, dstRect_, sourceInfo);
        }
    }
}

void ImagePattern::LoadImage(
    const ImageSourceInfo& src, const PropertyChangeFlag& propertyChangeFlag, VisibleType visibleType)
{
    if (loadingCtx_) {
        auto srcKey = src.GetKey();
        auto loadKey = loadingCtx_->GetSourceInfo().GetKey();
        isPixelMapChanged_ = srcKey != loadKey;
    }
    LoadNotifier loadNotifier(CreateDataReadyCallback(), CreateLoadSuccessCallback(), CreateLoadFailCallback());
    loadNotifier.onDataReadyComplete_ = CreateCompleteCallBackInDataReady();

    loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(src, std::move(loadNotifier), syncLoad_);
    if (SystemProperties::GetDebugEnabled()) {
        TAG_LOGD(AceLogTag::ACE_IMAGE, "start loading image %{public}s", src.ToString().c_str());
    }
    loadingCtx_->SetLoadInVipChannel(GetLoadInVipChannel());
    loadingCtx_->SetNodeId(GetHost()->GetId());
    if (onProgressCallback_) {
        loadingCtx_->SetOnProgressCallback(std::move(onProgressCallback_));
    }
    if (!((propertyChangeFlag & PROPERTY_UPDATE_MEASURE) == PROPERTY_UPDATE_MEASURE) ||
        visibleType == VisibleType::GONE) {
        loadingCtx_->FinishMearuse();
    }
    loadingCtx_->LoadImageData();
}

void ImagePattern::LoadAltImage(const ImageSourceInfo& altImageSourceInfo)
{
    CHECK_NULL_VOID(GetNeedLoadAlt());
    LoadNotifier altLoadNotifier(CreateDataReadyCallbackForAlt(), CreateLoadSuccessCallbackForAlt(), nullptr);
    if (!altLoadingCtx_ || altLoadingCtx_->GetSourceInfo() != altImageSourceInfo ||
        (altLoadingCtx_ && altImageSourceInfo.IsSvg())) {
        altLoadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(altImageSourceInfo, std::move(altLoadNotifier));
        altLoadingCtx_->LoadImageData();
    }
}

void ImagePattern::LoadImageDataIfNeed()
{
    auto imageLayoutProperty = GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageLayoutProperty);
    auto imageRenderProperty = GetPaintProperty<ImageRenderProperty>();
    CHECK_NULL_VOID(imageRenderProperty);
    auto src = imageLayoutProperty->GetImageSourceInfo().value_or(ImageSourceInfo(""));
    UpdateInternalResource(src);
    std::optional<Color> svgFillColorOpt = std::nullopt;
    if (src.IsSvg()) {
        svgFillColorOpt = src.GetFillColor();
    }

    if (!loadingCtx_ || loadingCtx_->GetSourceInfo() != src || isImageQualityChange_) {
        LoadImage(src, imageLayoutProperty->GetPropertyChangeFlag(),
            imageLayoutProperty->GetVisibility().value_or(VisibleType::VISIBLE));
    } else if (IsSupportImageAnalyzerFeature()) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto context = host->GetContext();
        CHECK_NULL_VOID(context);
        auto uiTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
        uiTaskExecutor.PostTask([weak = WeakClaim(this)] {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            ContainerScope scope(pattern->GetHostInstanceId());
            pattern->CreateAnalyzerOverlay();
            auto host = pattern->GetHost();
            pattern->UpdateAnalyzerUIConfig(host->GetGeometryNode());
        }, "ArkUIImageUpdateAnalyzerUIConfig");
    }
    if (loadingCtx_->NeedAlt() && imageLayoutProperty->GetAlt()) {
        auto altImageSourceInfo = imageLayoutProperty->GetAlt().value_or(ImageSourceInfo(""));
        LoadAltImage(altImageSourceInfo);
    }
}

void ImagePattern::UpdateGestureAndDragWhenModify()
{
    // remove long press and mouse events
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto gestureHub = host->GetOrCreateGestureEventHub();
    if (longPressEvent_) {
        gestureHub->SetLongPressEvent(nullptr);
        longPressEvent_ = nullptr;
    }

    if (clickEvent_) {
        gestureHub->RemoveClickEvent(clickEvent_);
        clickEvent_ = nullptr;
    }

    if (mouseEvent_) {
        auto inputHub = host->GetOrCreateInputEventHub();
        inputHub->RemoveOnMouseEvent(mouseEvent_);
        mouseEvent_ = nullptr;
    }

    if (host->IsDraggable()) {
        EnableDrag();
    }
}

void ImagePattern::OnModifyDone()
{
    switch (imageType_) {
        case ImageType::BASE:
            OnImageModifyDone();
            break;
        case ImageType::ANIMATION:
            OnAnimatedModifyDone();
            break;
        default:
            break;
    }
}

void ImagePattern::OnAnimatedModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    Pattern::OnModifyDone();
    auto size = static_cast<int32_t>(images_.size());
    if (size <= 0) {
        TAG_LOGW(AceLogTag::ACE_IMAGE, "image size is less than 0.");
        return;
    }
    GenerateCachedImages();
    auto index = nowImageIndex_;
    if ((status_ == Animator::Status::IDLE || status_ == Animator::Status::STOPPED) && !firstUpdateEvent_) {
        index = 0;
    }

    if (imagesChangedFlag_) {
        animator_->ClearInterpolators();
        animator_->AddInterpolator(CreatePictureAnimation(size));
        AdaptSelfSize();
        imagesChangedFlag_ = false;
    }
    if (firstUpdateEvent_) {
        firstUpdateEvent_ = false;
        auto imageFrameNode = AceType::DynamicCast<FrameNode>(host->GetChildren().front());
        AddImageLoadSuccessEvent(imageFrameNode);
    }
    UpdateFormDurationByRemainder();
    SetObscured();
    if (isSrcUndefined_) {
        return;
    }
    ControlAnimation(index);
}

void ImagePattern::ControlAnimation(int32_t index)
{
    if (!animator_->HasScheduler()) {
        auto context = PipelineContext::GetCurrentContext();
        if (context) {
            animator_->AttachScheduler(context);
        } else {
            TAG_LOGW(AceLogTag::ACE_IMAGE, "pipelineContext is null.");
        }
    }
    switch (status_) {
        case Animator::Status::IDLE:
            animator_->Cancel();
            ResetFormAnimationFlag();
            SetShowingIndex(index);
            break;
        case Animator::Status::PAUSED:
            animator_->Pause();
            ResetFormAnimationFlag();
            break;
        case Animator::Status::STOPPED:
            animator_->Finish();
            ResetFormAnimationFlag();
            break;
        default:
            ResetFormAnimationStartTime();
            if (isFormAnimationEnd_) {
                ResetFormAnimationFlag();
                return;
            }
            auto host = GetHost();
            CHECK_NULL_VOID(host);
            if (host->IsVisible()) {
                animator_->Forward();
            } else {
                animator_->Pause();
            }
    }
}

void ImagePattern::OnImageModifyDone()
{
    Pattern::OnModifyDone();
    LoadImageDataIfNeed();
    UpdateGestureAndDragWhenModify();

    if (copyOption_ != CopyOptions::None) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        bool hasObscured = false;
        if (host->GetRenderContext()->GetObscured().has_value()) {
            auto obscuredReasons = host->GetRenderContext()->GetObscured().value();
            hasObscured = std::any_of(obscuredReasons.begin(), obscuredReasons.end(),
                [](const auto& reason) { return reason == ObscuredReasons::PLACEHOLDER; });
        }
        if (!hasObscured) {
            InitCopy();
            return;
        }
    }

    CloseSelectOverlay();

    auto host = GetHost();
    CHECK_NULL_VOID(host);

    if (imageAnalyzerManager_ && imageAnalyzerManager_->IsOverlayCreated()) {
        if (!IsSupportImageAnalyzerFeature()) {
            DestroyAnalyzerOverlay();
        } else {
            UpdateAnalyzerOverlayLayout();
        }
    }

    // SetUsingContentRectForRenderFrame is set for image paint
    auto overlayNode = host->GetOverlayNode();
    if (overlayNode) {
        auto layoutProperty = host->GetLayoutProperty();
        CHECK_NULL_VOID(layoutProperty);
        auto padding = layoutProperty->CreatePaddingAndBorder();
        auto renderContext = overlayNode->GetRenderContext();
        if (renderContext) {
            renderContext->SetRenderFrameOffset({-padding.Offset().GetX(), -padding.Offset().GetY()});
        }
    }
}

DataReadyNotifyTask ImagePattern::CreateDataReadyCallbackForAlt()
{
    return [weak = WeakClaim(this)](const ImageSourceInfo& sourceInfo) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        CHECK_NULL_VOID(pattern->altLoadingCtx_);
        auto imageLayoutProperty = pattern->GetLayoutProperty<ImageLayoutProperty>();
        CHECK_NULL_VOID(imageLayoutProperty);
        auto currentAltSourceInfo = imageLayoutProperty->GetAlt().value_or(ImageSourceInfo(""));
        if (currentAltSourceInfo != sourceInfo) {
            TAG_LOGW(AceLogTag::ACE_IMAGE, "alt image sourceInfo does not match, ignore current callback. "
                 "current: %{private}s vs callback's: %{private}s",
                currentAltSourceInfo.ToString().c_str(), sourceInfo.ToString().c_str());
            return;
        }
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        if (!host->IsActive()) {
            return;
        }
        const auto& geometryNode = host->GetGeometryNode();
        CHECK_NULL_VOID(geometryNode);
        if (!geometryNode->GetContent()) {
            host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
            return;
        }

        // calculate params for [altLoadingCtx] to do [MakeCanvasImage] if component size is already settled
        pattern->altLoadingCtx_->MakeCanvasImageIfNeed(
            geometryNode->GetContentSize(), true, imageLayoutProperty->GetImageFit().value_or(ImageFit::COVER));
    };
}

LoadSuccessNotifyTask ImagePattern::CreateLoadSuccessCallbackForAlt()
{
    return [weak = WeakClaim(this)](const ImageSourceInfo& sourceInfo) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        CHECK_NULL_VOID(pattern->altLoadingCtx_);
        auto layoutProps = pattern->GetLayoutProperty<ImageLayoutProperty>();
        auto currentAltSrc = layoutProps->GetAlt().value_or(ImageSourceInfo(""));
        if (currentAltSrc != sourceInfo) {
            TAG_LOGW(AceLogTag::ACE_IMAGE, "alt image sourceInfo does not match, ignore current callback. "
                 "current: %{private}s vs callback's: %{private}s",
                currentAltSrc.ToString().c_str(), sourceInfo.ToString().c_str());
            return;
        }
        pattern->altImage_ = pattern->altLoadingCtx_->MoveCanvasImage();
        CHECK_NULL_VOID(pattern->altImage_);
        pattern->altSrcRect_ = std::make_unique<RectF>(pattern->altLoadingCtx_->GetSrcRect());
        pattern->altDstRect_ = std::make_unique<RectF>(pattern->altLoadingCtx_->GetDstRect());
        pattern->SetImagePaintConfig(pattern->altImage_, *pattern->altSrcRect_, *pattern->altDstRect_,
            pattern->altLoadingCtx_->GetSourceInfo(), pattern->altLoadingCtx_->GetFrameCount());

        pattern->PrepareAnimation(pattern->altImage_);

        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    };
}

void ImagePattern::UpdateInternalResource(ImageSourceInfo& sourceInfo)
{
    if (!sourceInfo.IsInternalResource()) {
        return;
    }

    auto pipeline = GetHost()->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto iconTheme = pipeline->GetTheme<IconTheme>();
    CHECK_NULL_VOID(iconTheme);
    auto iconPath = iconTheme->GetIconPath(sourceInfo.GetResourceId());
    if (!iconPath.empty()) {
        sourceInfo.SetSrc(iconPath, sourceInfo.GetFillColor());
        auto imageLayoutProperty = GetLayoutProperty<ImageLayoutProperty>();
        CHECK_NULL_VOID(imageLayoutProperty);
        imageLayoutProperty->UpdateImageSourceInfo(sourceInfo);
    }
}

void ImagePattern::OnNotifyMemoryLevel(int32_t level)
{
    // when image component is [onShow], do not clean image data
    if (isShow_ || level <= static_cast<int32_t>(MEMORY_LEVEL_LOW_STATUS)) {
        return;
    }
    // clean image data
    loadingCtx_ = nullptr;
    image_ = nullptr;
    altLoadingCtx_ = nullptr;
    altImage_ = nullptr;
}

// when recycle image component, release the pixelmap resource
void ImagePattern::OnRecycle()
{
    loadingCtx_ = nullptr;
    image_ = nullptr;
    altLoadingCtx_ = nullptr;
    altImage_ = nullptr;

    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    auto rsRenderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(rsRenderContext);
    rsRenderContext->ClearDrawCommands();
    UnregisterWindowStateChangedCallback();
}

void ImagePattern::OnReuse()
{
    RegisterWindowStateChangedCallback();
    auto renderProp = GetPaintProperty<ImageRenderProperty>();
    CHECK_NULL_VOID(renderProp);
    renderProp->UpdateNeedBorderRadius(needBorderRadius_);
    LoadImageDataIfNeed();
}

void ImagePattern::RegisterWindowStateChangedCallback()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->AddWindowStateChangedCallback(host->GetId());
}

void ImagePattern::UnregisterWindowStateChangedCallback()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->RemoveWindowStateChangedCallback(host->GetId());
}

void ImagePattern::OnWindowHide()
{
    isShow_ = false;
}

void ImagePattern::OnWindowShow()
{
    isShow_ = true;
    LoadImageDataIfNeed();
}

void ImagePattern::OnVisibleChange(bool visible)
{
    if (!visible) {
        CloseSelectOverlay();
    }
}

void ImagePattern::OnVisibleAreaChange(bool visible, double ratio)
{
    if (SystemProperties::GetDebugEnabled()) {
        TAG_LOGD(AceLogTag::ACE_IMAGE, "OnVisibleAreaChange visible:%{public}d", (int)visible);
    }
    if (!visible) {
        CloseSelectOverlay();
    }
    // control pixelMap List
    if (GetIsAnimation() && !animator_->IsStopped()) {
        if (visible) {
            animator_->Forward();
        } else {
            animator_->Pause();
        }
    }
    gifAnimation_ = visible;
    // control svg / gif animation
    if (image_) {
        image_->ControlAnimation(visible);
    } else if (altImage_) {
        altImage_->ControlAnimation(visible);
    }

    if (isEnableAnalyzer_) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto overlayNode = host->GetOverlayNode();
        CHECK_NULL_VOID(overlayNode);
        TriggerVisibleAreaChangeForChild(overlayNode, visible, ratio);
    }
}

void ImagePattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderCtx = host->GetRenderContext();
    CHECK_NULL_VOID(renderCtx);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    if (GetIsAnimation()) {
        renderCtx->SetClipToFrame(true);
    } else {
        renderCtx->SetClipToBounds(false);
        renderCtx->SetUsingContentRectForRenderFrame(true);

        // register image frame node to pipeline context to receive memory level notification and window state change
        // notification
        pipeline->AddNodesToNotifyMemoryLevel(host->GetId());
        pipeline->AddWindowStateChangedCallback(host->GetId());
    }
    auto theme = pipeline->GetTheme<TextTheme>();
    CHECK_NULL_VOID(theme);
    selectedColor_ = theme->GetSelectedColor();
}

void ImagePattern::OnDetachFromFrameNode(FrameNode* frameNode)
{
    CloseSelectOverlay();

    auto id = frameNode->GetId();
    auto pipeline = AceType::DynamicCast<PipelineContext>(PipelineBase::GetCurrentContext());
    CHECK_NULL_VOID(pipeline);
    pipeline->RemoveWindowStateChangedCallback(id);
    pipeline->RemoveNodesToNotifyMemoryLevel(id);
}

void ImagePattern::EnableDrag()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto dragStart = [weak = WeakClaim(this)](const RefPtr<OHOS::Ace::DragEvent>& event,
                         const std::string& /*extraParams*/) -> DragDropInfo {
        DragDropInfo info;
        auto imagePattern = weak.Upgrade();
        CHECK_NULL_RETURN(imagePattern && imagePattern->loadingCtx_, info);
        AceEngineExt::GetInstance().DragStartExt();
        imagePattern->UpdateDragEvent(event);
        info.extraInfo = imagePattern->loadingCtx_->GetSourceInfo().GetSrc();
        return info;
    };
    auto eventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetDefaultOnDragStart(std::move(dragStart));
}

bool ImagePattern::BetweenSelectedPosition(const Offset& globalOffset)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto globalRect = host->GetTransformRectRelativeToWindow();
    return globalRect.IsInRegion(PointF { globalOffset.GetX(), globalOffset.GetY() });
}

void ImagePattern::BeforeCreatePaintWrapper()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->MarkContentChanged(true);
}

void ImagePattern::InitCopy()
{
    if (longPressEvent_ && mouseEvent_ && clickEvent_) {
        return;
    }
    auto longPressTask = [weak = WeakClaim(this)](GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OpenSelectOverlay();
    };
    longPressEvent_ = MakeRefPtr<LongPressEvent>(std::move(longPressTask));

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gestureHub = host->GetOrCreateGestureEventHub();
    gestureHub->SetLongPressEvent(longPressEvent_);

    auto mouseTask = [weak = WeakClaim(this)](MouseInfo& info) {
        if (info.GetButton() == MouseButton::RIGHT_BUTTON && info.GetAction() == MouseAction::PRESS) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->OpenSelectOverlay();
        }
    };
    mouseEvent_ = MakeRefPtr<InputEvent>(std::move(mouseTask));
    auto inputHub = host->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(inputHub);
    inputHub->AddOnMouseEvent(mouseEvent_);

    // close overlay on click
    clickEvent_ = MakeRefPtr<ClickEvent>([weak = WeakClaim(this)](GestureEvent& callback) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->CloseSelectOverlay();
    });
    gestureHub->AddClickEvent(clickEvent_);
}

void ImagePattern::OpenSelectOverlay()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    const auto& geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto rect = host->GetTransformRectRelativeToWindow();
    SelectOverlayInfo info;
    SizeF handleSize = {
        SelectHandleInfo::GetDefaultLineWidth().ConvertToPx(),
        geometryNode->GetContentSize().Height() };
    info.firstHandle.paintRect = RectF(rect.GetOffset(), handleSize);
    OffsetF offset(rect.Width() - handleSize.Width(), rect.Height() - handleSize.Height());
    info.secondHandle.paintRect = RectF(rect.GetOffset() + offset, handleSize);
    info.menuInfo.menuIsShow = true;
    info.menuInfo.showCut = false;
    info.menuInfo.showPaste = false;
    info.menuCallback.onCopy = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleCopy();
        pattern->CloseSelectOverlay();
    };
    info.onHandleMoveDone = [weak = WeakClaim(this), firstRect = info.firstHandle.paintRect,
                                secondRect = info.secondHandle.paintRect](const RectF&, bool isFirst) {
        // reset handle position
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern && pattern->selectOverlay_);
        SelectHandleInfo info;
        if (isFirst) {
            info.paintRect = firstRect;
            pattern->selectOverlay_->UpdateFirstSelectHandleInfo(info);
        } else {
            info.paintRect = secondRect;
            pattern->selectOverlay_->UpdateSecondSelectHandleInfo(info);
        }
    };
    info.onClose = [weak = WeakClaim(this)](bool closedByGlobalEvent) {
        if (closedByGlobalEvent) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->CloseSelectOverlay();
        }
    };

    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    selectOverlay_ = pipeline->GetSelectOverlayManager()->CreateAndShowSelectOverlay(info, WeakClaim(this));
    isSelected_ = true;
    CHECK_NULL_VOID(selectOverlay_);
    pipeline->AddOnAreaChangeNode(host->GetId());
    // paint selected mask effect
    host->MarkNeedRenderOnly();
}

void ImagePattern::CloseSelectOverlay()
{
    if (!selectOverlay_) {
        return;
    }
    if (!selectOverlay_->IsClosed()) {
        selectOverlay_->Close();
    }
    isSelected_ = false;
    // remove selected mask effect
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    RemoveAreaChangeInner();
    host->MarkNeedRenderOnly();
}

void ImagePattern::HandleCopy()
{
    CHECK_NULL_VOID(image_);
    if (!clipboard_) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto pipeline = host->GetContext();
        CHECK_NULL_VOID(pipeline);
        clipboard_ = ClipboardProxy::GetInstance()->GetClipboard(pipeline->GetTaskExecutor());
    }
    auto pixmap = image_->GetPixelMap();
    if (pixmap) {
        clipboard_->SetPixelMapData(pixmap, copyOption_);
    } else {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        clipboard_->SetData(loadingCtx_->GetSourceInfo().GetSrc());
    }
}

void ImagePattern::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    static const char* COPY_OPTIONS[] = { "CopyOptions.None", "CopyOptions.InApp", "CopyOptions.Local",
        "CopyOptions.Distributed" };
    json->PutExtAttr("copyOption", COPY_OPTIONS[static_cast<int32_t>(copyOption_)], filter);

    json->PutExtAttr("syncLoad", syncLoad_ ? "true" : "false", filter);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    json->PutExtAttr("draggable", host->IsDraggable() ? "true" : "false", filter);
    json->PutExtAttr("enableAnalyzer", isEnableAnalyzer_ ? "true" : "false", filter);
    auto renderProp = GetPaintProperty<ImageRenderProperty>();
    CHECK_NULL_VOID(renderProp);
    DynamicRangeMode dynamicMode = DynamicRangeMode::STANDARD;
    if (renderProp->HasDynamicMode()) {
        dynamicMode = renderProp->GetDynamicMode().value_or(DynamicRangeMode::STANDARD);
    }
    json->PutExtAttr("dynamicRangeMode", GetDynamicModeString(dynamicMode).c_str(), filter);
}

void ImagePattern::UpdateFillColorIfForegroundColor()
{
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    if (renderContext->HasForegroundColor() || renderContext->HasForegroundColorStrategy()) {
        auto imageLayoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
        auto imageSourceInfo = imageLayoutProperty->GetImageSourceInfo().value();
        if (imageSourceInfo.IsSvg()) {
            imageSourceInfo.SetFillColor(Color::FOREGROUND);
            imageLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);
        }
        auto imageRenderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
        CHECK_NULL_VOID(imageRenderProperty);
        imageRenderProperty->UpdateSvgFillColor(Color::FOREGROUND);
    }
}

void ImagePattern::DumpLayoutInfo()
{
    auto layoutProp = GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(layoutProp);
    auto src = layoutProp->GetImageSourceInfo().value_or(ImageSourceInfo(""));
    DumpLog::GetInstance().AddDesc(std::string("url: ").append(src.ToString()));

    auto altSrc = layoutProp->GetAlt().value_or(ImageSourceInfo(""));
    DumpLog::GetInstance().AddDesc(std::string("altUrl: ").append(altSrc.ToString()));

    auto imageFit = layoutProp->GetImageFit().value_or(ImageFit::COVER);
    DumpLog::GetInstance().AddDesc(std::string("objectFit: ").append(GetImageFitStr(imageFit)));

    auto fitOriginalSize = layoutProp->GetFitOriginalSize().value_or(false);
    DumpLog::GetInstance().AddDesc(std::string("fitOriginalSize: ").append(fitOriginalSize ? "true" : "false"));

    const std::optional<SizeF>& sourceSize = layoutProp->GetSourceSize();
    if (sourceSize.has_value()) {
        DumpLog::GetInstance().AddDesc(std::string("sourceSize: ").append(sourceSize.value().ToString()));
    }

    bool autoResize = layoutProp->GetAutoResize().value_or(autoResizeDefault_);
    autoResize ? DumpLog::GetInstance().AddDesc("autoResize:true")
                       : DumpLog::GetInstance().AddDesc("autoResize:false");
}

void ImagePattern::DumpRenderInfo()
{
    auto renderProp = GetPaintProperty<ImageRenderProperty>();
    CHECK_NULL_VOID(renderProp);

    auto imageRenderMode = renderProp->GetImageRenderMode().value_or(ImageRenderMode::ORIGINAL);
    DumpLog::GetInstance().AddDesc(
        std::string("renderMode: ").append((imageRenderMode == ImageRenderMode::ORIGINAL) ? "Original" : "Template"));

    auto imageRepeat = renderProp->GetImageRepeat().value_or(ImageRepeat::NO_REPEAT);
    DumpLog::GetInstance().AddDesc(std::string("objectRepeat: ").append(GetImageRepeatStr(imageRepeat)));

    auto imageColorFilter = renderProp->GetColorFilter();
    if (imageColorFilter.has_value()) {
        auto colorFilter = imageColorFilter.value();
        DumpLog::GetInstance().AddDesc(std::string("colorFilter: ").append(GetImageColorFilterStr(colorFilter)));
    }

    auto fillColor = renderProp->GetSvgFillColor();
    if (fillColor.has_value()) {
        auto color = fillColor.value();
        DumpLog::GetInstance().AddDesc(std::string("fillColor: ").append(color.ColorToString()));
    }

    DynamicRangeMode dynamicMode = DynamicRangeMode::STANDARD;
    if (renderProp->HasDynamicMode()) {
        dynamicMode = renderProp->GetDynamicMode().value_or(DynamicRangeMode::STANDARD);
        DumpLog::GetInstance().AddDesc(std::string("dynamicRangeMode: ").append(GetDynamicModeString(dynamicMode)));
    }

    auto matchTextDirection = renderProp->GetMatchTextDirection().value_or(false);
    matchTextDirection ? DumpLog::GetInstance().AddDesc("matchTextDirection:true")
                       : DumpLog::GetInstance().AddDesc("matchTextDirection:false");

    auto smoothEdge = renderProp->GetSmoothEdge();
    if (smoothEdge.has_value()) {
        DumpLog::GetInstance().AddDesc(std::string("edgeAntialiasing: ").append(std::to_string(smoothEdge.value())));
    }

    auto needBorderRadius = renderProp->GetNeedBorderRadius().value_or(false);
    needBorderRadius ? DumpLog::GetInstance().AddDesc("needBorderRadius:true")
                     : DumpLog::GetInstance().AddDesc("needBorderRadius:false");

    auto borderRadius = renderProp->GetBorderRadius().value_or(BorderRadiusProperty());
    DumpLog::GetInstance().AddDesc(borderRadius.ToString());

    if (renderProp && renderProp->HasImageResizableSlice() && renderProp->GetImageResizableSliceValue({}).Valid()) {
        DumpLog::GetInstance().AddDesc(
            std::string("resizable slice: ").append(renderProp->GetImageResizableSliceValue({}).ToString()));
    }
}

void ImagePattern::DumpSvgInfo()
{
    auto imageLayoutProperty = GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageLayoutProperty);
    auto imageSourceInfo = imageLayoutProperty->GetImageSourceInfo();
    CHECK_NULL_VOID(imageSourceInfo);
    if (!imageSourceInfo->IsSvg()|| !loadingCtx_) {
        return;
    }
    auto imageObject = loadingCtx_->GetImageObject();
    CHECK_NULL_VOID(imageObject);
    DumpLog::GetInstance().AddDesc(
        std::string("Svg:").append(imageObject->GetDumpInfo()));
}

void ImagePattern::DumpInfo()
{
    DumpLayoutInfo();
    DumpRenderInfo();

    syncLoad_ ? DumpLog::GetInstance().AddDesc("syncLoad:true") : DumpLog::GetInstance().AddDesc("syncLoad:false");

    DumpLog::GetInstance().AddDesc("imageInterpolation:" + GetImageInterpolation());
    if (loadingCtx_) {
        auto currentLoadImageState = loadingCtx_->GetCurrentLoadingState();
        DumpLog::GetInstance().AddDesc(std::string("currentLoadImageState : ").append(currentLoadImageState));
        DumpLog::GetInstance().AddDesc(std::string("rawImageSize: ").append(loadingCtx_->GetImageSize().ToString()));
        DumpLog::GetInstance().AddDesc(std::string("LoadErrorMsg: ").append(loadingCtx_->GetErrorMsg()));
    } else {
        DumpLog::GetInstance().AddDesc(std::string("imageLoadingContext: null"));
    }

    auto host = GetHost();
    if (host) {
        auto enDrage = host->IsDraggable();
        enDrage ? DumpLog::GetInstance().AddDesc("draggable:true") : DumpLog::GetInstance().AddDesc("draggable:false");
    }

    DumpLog::GetInstance().AddDesc(std::string("enableAnalyzer: ").append(isEnableAnalyzer_ ? "true" : "false"));
    DumpSvgInfo();
}

void ImagePattern::DumpAdvanceInfo()
{
    auto layoutProp = GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(layoutProp);
    auto src = layoutProp->GetImageSourceInfo().value_or(ImageSourceInfo(""));
    DumpLog::GetInstance().AddDesc(std::string("url: ").append(layoutProp->GetImageSourceInfo()->ToString()));
    syncLoad_ ? DumpLog::GetInstance().AddDesc("syncLoad:true") : DumpLog::GetInstance().AddDesc("syncLoad:false");
    if (loadingCtx_) {
        auto currentLoadImageState = loadingCtx_->GetCurrentLoadingState();
        DumpLog::GetInstance().AddDesc(std::string("currentLoadImageState : ").append(currentLoadImageState));
    }
}

void ImagePattern::UpdateDragEvent(const RefPtr<OHOS::Ace::DragEvent>& event)
{
    RefPtr<UnifiedData> unifiedData = UdmfClient::GetInstance()->CreateUnifiedData();
    if (loadingCtx_ && image_ && loadingCtx_->GetSourceInfo().IsPixmap()) {
        auto pixelMap = image_->GetPixelMap();
        CHECK_NULL_VOID(pixelMap);
        std::vector<uint8_t> data;
        if (!pixelMap->GetPixelsVec(data)) {
            return;
        }
        PixelMapRecordDetails details = { pixelMap->GetWidth(), pixelMap->GetHeight(), pixelMap->GetPixelFormat(),
            pixelMap->GetAlphaType() };
        UdmfClient::GetInstance()->AddPixelMapRecord(unifiedData, data, details);
    } else if (loadingCtx_) {
        UdmfClient::GetInstance()->AddImageRecord(unifiedData, loadingCtx_->GetSourceInfo().GetSrc());
    }
    event->SetData(unifiedData);
}

void ImagePattern::OnLanguageConfigurationUpdate()
{
    CHECK_NULL_VOID(loadingCtx_);
    auto&& src = loadingCtx_->GetSourceInfo();
    // Resource image needs to reload when Language changes
    if (src.GetSrcType() == SrcType::RESOURCE) {
        loadingCtx_.Reset();
    }
    OnConfigurationUpdate();
}

void ImagePattern::OnColorConfigurationUpdate()
{
    OnConfigurationUpdate();
}

void ImagePattern::OnDirectionConfigurationUpdate()
{
    OnConfigurationUpdate();
}

void ImagePattern::OnIconConfigurationUpdate()
{
    OnConfigurationUpdate();
}

void ImagePattern::OnConfigurationUpdate()
{
    CHECK_NULL_VOID(loadingCtx_);
    auto imageLayoutProperty = GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageLayoutProperty);
    auto src = imageLayoutProperty->GetImageSourceInfo().value_or(ImageSourceInfo(""));
    UpdateInternalResource(src);

    LoadImage(src, imageLayoutProperty->GetPropertyChangeFlag(),
        imageLayoutProperty->GetVisibility().value_or(VisibleType::VISIBLE));
    if (loadingCtx_->NeedAlt() && imageLayoutProperty->GetAlt()) {
        auto altImageSourceInfo = imageLayoutProperty->GetAlt().value_or(ImageSourceInfo(""));
        if (altLoadingCtx_ && altLoadingCtx_->GetSourceInfo() == altImageSourceInfo) {
            altLoadingCtx_.Reset();
        }
        LoadAltImage(altImageSourceInfo);
    }
}

std::string ImagePattern::GetImageFitStr(ImageFit value)
{
    switch (value) {
        case ImageFit::CONTAIN:
            return "CONTAIN";
        case ImageFit::COVER:
            return "COVER";
        case ImageFit::FILL:
            return "FILL";
        case ImageFit::FITWIDTH:
            return "FITWIDTH";
        case ImageFit::FITHEIGHT:
            return "FITHEIGHT";
        case ImageFit::NONE:
            return "NONE";
        case ImageFit::SCALE_DOWN:
            return "SCALE_DOWN";
        case ImageFit::TOP_LEFT:
            return "TOP_LEFT";
        default:
            return "COVER";
    }
}

std::string ImagePattern::GetImageRepeatStr(ImageRepeat value)
{
    switch (value) {
        case ImageRepeat::NO_REPEAT:
            return "NO_REPEAT";
        case ImageRepeat::REPEAT:
            return "REPEAT_XY";
        case ImageRepeat::REPEAT_X:
            return "REPEAT_X";
        case ImageRepeat::REPEAT_Y:
            return "REPEAT_Y";
        default:
            return "NO_REPEAT";
    }
}

std::string ImagePattern::GetImageColorFilterStr(const std::vector<float>& colorFilter)
{
    if (colorFilter.empty()) {
        return "";
    }
    std::string result = "[" + std::to_string(colorFilter[0]);
    for (uint32_t idx = 1; idx < colorFilter.size(); ++idx) {
        result += ", " + std::to_string(colorFilter[idx]);
    }
    return result + "]";
}

void ImagePattern::EnableAnalyzer(bool value)
{
    isEnableAnalyzer_ = value;
    if (!isEnableAnalyzer_) {
        DestroyAnalyzerOverlay();
        return;
    }

    if (!imageAnalyzerManager_) {
        imageAnalyzerManager_ = std::make_shared<ImageAnalyzerManager>(GetHost(), ImageAnalyzerHolder::IMAGE);
    }
    RegisterVisibleAreaChange(false);
}

// As an example
void ImagePattern::SetImageAnalyzerConfig(const ImageAnalyzerConfig &config)
{
    if (!isEnableAnalyzer_) {
        return;
    }
}

void ImagePattern::SetImageAnalyzerConfig(void* config)
{
    if (isEnableAnalyzer_) {
        CHECK_NULL_VOID(imageAnalyzerManager_);
        imageAnalyzerManager_->SetImageAnalyzerConfig(config);
    }
}

void ImagePattern::SetImageAIOptions(void* options)
{
    if (!imageAnalyzerManager_) {
        imageAnalyzerManager_ = std::make_shared<ImageAnalyzerManager>(GetHost(), ImageAnalyzerHolder::IMAGE);
    }
    CHECK_NULL_VOID(imageAnalyzerManager_);
    imageAnalyzerManager_->SetImageAIOptions(options);
}

bool ImagePattern::IsSupportImageAnalyzerFeature()
{
    CHECK_NULL_RETURN(imageAnalyzerManager_, false);
    return isEnableAnalyzer_ && image_ && !loadingCtx_->GetSourceInfo().IsSvg() && loadingCtx_->GetFrameCount() <= 1 &&
        imageAnalyzerManager_->IsSupportImageAnalyzerFeature();
}

void ImagePattern::CreateAnalyzerOverlay()
{
    CHECK_NULL_VOID(imageAnalyzerManager_);
    if (imageAnalyzerManager_->IsOverlayCreated()) {
        return;
    }

    CHECK_NULL_VOID(image_);
    auto pixelMap = image_->GetPixelMap();
    CHECK_NULL_VOID(pixelMap);
    imageAnalyzerManager_->CreateAnalyzerOverlay(pixelMap);
}

void ImagePattern::UpdateAnalyzerOverlay()
{
    CHECK_NULL_VOID(imageAnalyzerManager_);
    if (!IsSupportImageAnalyzerFeature() || !imageAnalyzerManager_->IsOverlayCreated()) {
        return;
    }

    CHECK_NULL_VOID(image_);
    auto pixelMap = image_->GetPixelMap();
    CHECK_NULL_VOID(pixelMap);
    imageAnalyzerManager_->UpdateAnalyzerOverlay(pixelMap);
}

void ImagePattern::UpdateAnalyzerOverlayLayout()
{
    CHECK_NULL_VOID(imageAnalyzerManager_);
    imageAnalyzerManager_->UpdateAnalyzerOverlayLayout();
}

void ImagePattern::DestroyAnalyzerOverlay()
{
    CHECK_NULL_VOID(imageAnalyzerManager_);
    imageAnalyzerManager_->DestroyAnalyzerOverlay();
}

void ImagePattern::ReleaseImageAnalyzer()
{
    CHECK_NULL_VOID(imageAnalyzerManager_);
    imageAnalyzerManager_->ReleaseImageAnalyzer();
}

void ImagePattern::UpdateAnalyzerUIConfig(const RefPtr<NG::GeometryNode>& geometryNode)
{
    CHECK_NULL_VOID(imageAnalyzerManager_);
    imageAnalyzerManager_->UpdateAnalyzerUIConfig(geometryNode);
}

bool ImagePattern::AllowVisibleAreaCheck() const
{
    auto frameNode = GetHost();
    CHECK_NULL_RETURN(frameNode, false);
    RefPtr<FrameNode> parentUi = frameNode->GetAncestorNodeOfFrame(true);
    while (parentUi) {
        auto layoutProperty = parentUi->GetLayoutProperty();
        if (layoutProperty && layoutProperty->IsOverlayNode()) {
            return true;
        }
        parentUi = parentUi->GetAncestorNodeOfFrame(true);
    }
    return false;
}

void ImagePattern::InitDefaultValue()
{
    // add API version protection
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        autoResizeDefault_ = false;
        interpolationDefault_ = ImageInterpolation::LOW;
    }
    auto container = Container::Current();
    // If the default value is set to false, the ScenceBoard memory increases.
    // Therefore the default value is different in the ScenceBoard.
    if (container && container->IsScenceBoardWindow()) {
        autoResizeDefault_ = true;
        interpolationDefault_ = ImageInterpolation::NONE;
    }
}

bool ImagePattern::hasSceneChanged()
{
    auto imageLayoutProperty = GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_RETURN(imageLayoutProperty, false);
    auto src = imageLayoutProperty->GetImageSourceInfo().value_or(ImageSourceInfo(""));
    UpdateInternalResource(src);
    if (loadingCtx_ && loadingCtx_->GetSourceInfo() == src && srcRect_ == dstRect_) {
        return false;
    }
    return true;
}

void ImagePattern::ImageAnimatorPattern()
{
    animator_ = CREATE_ANIMATOR();
    animator_->SetFillMode(FillMode::BACKWARDS);
    animator_->SetDuration(DEFAULT_DURATION);
    ResetFormAnimationFlag();
}

RefPtr<PictureAnimation<int32_t>> ImagePattern::CreatePictureAnimation(int32_t size)
{
    auto pictureAnimation = MakeRefPtr<PictureAnimation<int32_t>>();
    if (durationTotal_ > 0) {
        for (int32_t index = 0; index < size; ++index) {
            pictureAnimation->AddPicture(images_[index].duration / static_cast<float>(durationTotal_), index);
        }
        animator_->SetDuration(durationTotal_);
    } else {
        for (int32_t index = 0; index < size; ++index) {
            pictureAnimation->AddPicture(NORMALIZED_DURATION_MAX / static_cast<float>(size), index);
        }
    }

    pictureAnimation->AddListener([weak = WeakClaim(this)](int32_t index) {
        auto imageAnimator = weak.Upgrade();
        CHECK_NULL_VOID(imageAnimator);
        imageAnimator->SetShowingIndex(index);
    });
    return pictureAnimation;
}

void ImagePattern::SetShowingIndex(int32_t index)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto imageFrameNode = AceType::DynamicCast<FrameNode>(host->GetChildren().front());
    CHECK_NULL_VOID(imageFrameNode);
    auto imageLayoutProperty = imageFrameNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageLayoutProperty);
    if (index >= static_cast<int32_t>(images_.size())) {
        TAG_LOGW(AceLogTag::ACE_IMAGE, "ImageAnimator update index error, index: %{public}d, size: %{public}zu",
            index, images_.size());
        return;
    }
    CHECK_NULL_VOID(images_[index].pixelMap);
    nowImageIndex_ = index;
    auto cacheImageIter = FindCacheImageNode(images_[index].pixelMap);
    if (IsShowingSrc(imageFrameNode, images_[index].pixelMap)) {
        ACE_SCOPED_TRACE("ImageAnimator same src %s, index %d", "PixelMap", index);
        UpdateShowingImageInfo(imageFrameNode, index);
    } else if (cacheImageIter == cacheImages_.end()) {
        ACE_SCOPED_TRACE("ImageAnimator no cache found, src %s, index %d", "PixelMap", index);
        UpdateShowingImageInfo(imageFrameNode, index);
    } else if (cacheImageIter->isLoaded) {
        ACE_SCOPED_TRACE("ImageAnimator useCache src %s, index %d", "PixelMap", index);
        auto cacheImageNode = cacheImageIter->imageNode;
        host->RemoveChild(imageFrameNode);
        host->AddChild(cacheImageNode, DEFAULT_NODE_SLOT, true);
        host->RebuildRenderContextTree();
        cacheImages_.erase(cacheImageIter);
        CacheImageStruct newCacheImageStruct(imageFrameNode);
        newCacheImageStruct.isLoaded = true;
        cacheImages_.emplace_back(newCacheImageStruct);
        UpdateShowingImageInfo(cacheImageNode, index);
    } else {
        UpdateShowingImageInfo(imageFrameNode, index);
        // wait for cache image loading
        ACE_SCOPED_TRACE("ImageAnimator waitForCache src %s, index %d", "PixelMap", index);
    }
    // update cache images
    CHECK_NULL_VOID(cacheImages_.size());
    int32_t nextIndex = GetNextIndex(index);
    for (auto& cacheImage : cacheImages_) {
        UpdateCacheImageInfo(cacheImage, nextIndex);
        nextIndex = GetNextIndex(nextIndex);
    }
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void ImagePattern::UpdateShowingImageInfo(const RefPtr<FrameNode>& imageFrameNode, int32_t index)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto imageLayoutProperty = imageFrameNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageLayoutProperty);

    imageLayoutProperty->UpdateImageSourceInfo(ImageSourceInfo(images_[index].pixelMap));
    SetColorFilter(imageFrameNode);
    SetImageFit(imageFrameNode);
    //use the size of first pixelmap when no size is set
    auto &&layoutConstraint = layoutProperty->GetCalcLayoutConstraint();
    if (!layoutConstraint || !layoutConstraint->selfIdealSize.has_value()) {
        CalcSize realSize = {
            CalcLength(images_[0].pixelMap->GetWidth()), CalcLength(images_[0].pixelMap->GetHeight()) };
        imageLayoutProperty->UpdateUserDefinedIdealSize(realSize);
        imageLayoutProperty->UpdateMeasureType(MeasureType::MATCH_CONTENT);
        imageFrameNode->MarkModifyDone();
        imageFrameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        return;
    }
    MarginProperty margin;
    margin.SetEdges(CalcLength(0.0));
    imageLayoutProperty->UpdateMargin(margin);
    imageLayoutProperty->ClearUserDefinedIdealSize(true, true);
    imageLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
    imageFrameNode->MarkModifyDone();
    imageFrameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void ImagePattern::UpdateCacheImageInfo(CacheImageStruct& cacheImage, int32_t index)
{
    if (index >= static_cast<int32_t>(images_.size())) {
        TAG_LOGW(AceLogTag::ACE_IMAGE, "PrepareImageInfo index error, index: %{public}d, size: %{public}zu",
            index, images_.size());
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto imageLayoutProperty = cacheImage.imageNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageLayoutProperty);
    CHECK_NULL_VOID(images_[index].pixelMap);
    // pixelmap
    if (imageLayoutProperty->HasImageSourceInfo()) {
        auto preSrc = imageLayoutProperty->GetImageSourceInfoValue().GetPixmap();
        if (preSrc != images_[index].pixelMap) {
            // need to cache newImage
            imageLayoutProperty->UpdateImageSourceInfo(ImageSourceInfo(images_[index].pixelMap));
            cacheImage.index = index;
            cacheImage.isLoaded = false;
        }
    }
    SetColorFilter(cacheImage.imageNode);
    SetImageFit(cacheImage.imageNode);
    //use the size of first pixelmap when no size is set
    auto &&layoutConstraint = layoutProperty->GetCalcLayoutConstraint();
    if (!layoutConstraint || !layoutConstraint->selfIdealSize.has_value()) {
        CalcSize realSize = {
            CalcLength(images_[0].pixelMap->GetWidth()), CalcLength(images_[0].pixelMap->GetHeight()) };
        imageLayoutProperty->UpdateUserDefinedIdealSize(realSize);
        cacheImage.imageNode->MarkModifyDone();
        return;
    }
    auto hostSize = host->GetGeometryNode()->GetPaddingSize();
    if (!hostSize.IsPositive()) {
        // if imageNode size is nonPositive, no pixelMap will be generated. Wait for size.
        return;
    }
    imageLayoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(hostSize.Width()), CalcLength(hostSize.Height())));
    cacheImage.imageNode->MarkModifyDone();
}

std::list<ImagePattern::CacheImageStruct>::iterator ImagePattern::FindCacheImageNode(const RefPtr<PixelMap>& src)
{
    for (auto iter = cacheImages_.begin(); iter != cacheImages_.end(); ++iter) {
        if (IsShowingSrc(iter->imageNode, src)) {
            return iter;
        }
    }
    return cacheImages_.end();
}

void ImagePattern::GenerateCachedImages()
{
    CHECK_NULL_VOID(images_.size());
    auto averageShowTime = static_cast<uint32_t>(animator_->GetDuration()) / images_.size();
    size_t cacheImageNum = averageShowTime >= CRITICAL_TIME ? 1 : 2;
    cacheImageNum = std::min(images_.size() - 1, cacheImageNum);
    if (cacheImages_.size() > cacheImageNum) {
        cacheImages_.resize(cacheImageNum);
        return;
    }
    while (cacheImages_.size() < cacheImageNum) {
        auto imageNode = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, -1, AceType::MakeRefPtr<ImagePattern>());
        auto imageLayoutProperty = imageNode->GetLayoutProperty();
        imageLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
        imageLayoutProperty->UpdateAlignment(Alignment::TOP_LEFT);
        AddImageLoadSuccessEvent(imageNode);
        cacheImages_.emplace_back(CacheImageStruct(imageNode));
    }
}

void ImagePattern::AdaptSelfSize()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    const auto& layoutProperty = host->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    if (layoutProperty->GetCalcLayoutConstraint() && layoutProperty->GetCalcLayoutConstraint()->selfIdealSize &&
        layoutProperty->GetCalcLayoutConstraint()->selfIdealSize->IsValid()) {
        return;
    }
    if (images_.empty()) {
        return;
    }
    CHECK_NULL_VOID(images_[0].pixelMap);
    hasSizeChanged = true;
    CalcSize realSize = {
        CalcLength(images_[0].pixelMap->GetWidth()), CalcLength(images_[0].pixelMap->GetHeight()) };

    const auto& layoutConstraint = layoutProperty->GetCalcLayoutConstraint();
    if (!layoutConstraint || !layoutConstraint->selfIdealSize) {
        layoutProperty->UpdateUserDefinedIdealSize(realSize);
        return;
    }
    if (!layoutConstraint->selfIdealSize->Width()) {
        layoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(images_[0].pixelMap->GetWidth()), std::nullopt));
        return;
    }
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(images_[0].pixelMap->GetHeight())));
}

int32_t ImagePattern::GetNextIndex(int32_t preIndex)
{
    return (preIndex + 1) % static_cast<int32_t>(images_.size());
}

void ImagePattern::AddImageLoadSuccessEvent(const RefPtr<FrameNode>& imageFrameNode)
{
    CHECK_NULL_VOID(imageFrameNode);
    auto eventHub = imageFrameNode->GetEventHub<ImageEventHub>();
    eventHub->SetOnComplete(
        [weakImage = WeakPtr<FrameNode>(imageFrameNode), weak = WeakClaim(this)](const LoadImageSuccessEvent& info) {
            if (info.GetLoadingStatus() != 1) {
                // status 1 means load success. Only need loadSuccess event.
                return;
            }
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            auto cacheImageNode = weakImage.Upgrade();
            CHECK_NULL_VOID(cacheImageNode);
            auto imageAnimator = pattern->GetHost();
            CHECK_NULL_VOID(imageAnimator);
            auto cacheLayoutProperty = cacheImageNode->GetLayoutProperty<ImageLayoutProperty>();
            auto cacheSrc = cacheLayoutProperty->GetImageSourceInfoValue(ImageSourceInfo()).GetSrc();
            ACE_SCOPED_TRACE("ImageAnimator cache succeed. src %s", cacheSrc.c_str());
            auto iter = std::find_if(pattern->cacheImages_.begin(), pattern->cacheImages_.end(),
                [&cacheImageNode](const CacheImageStruct& other) { return other.imageNode == cacheImageNode; });
            if (iter == pattern->cacheImages_.end()) {
                return;
            }
            iter->isLoaded = true;
            if (pattern->nowImageIndex_ >= static_cast<int32_t>(pattern->images_.size())) {
                TAG_LOGW(AceLogTag::ACE_IMAGE, "ImageAnimator showImage index is invalid");
                return;
            }
            if (pattern->nowImageIndex_ == iter->index &&
                IsShowingSrc(cacheImageNode, pattern->images_[pattern->nowImageIndex_].pixelMap)) {
                pattern->SetShowingIndex(pattern->nowImageIndex_);
            }
        });
}

bool ImagePattern::IsShowingSrc(const RefPtr<FrameNode>& imageFrameNode, const RefPtr<PixelMap>& src)
{
    auto imageLayoutProperty = imageFrameNode->GetLayoutProperty<ImageLayoutProperty>();
    return imageLayoutProperty->HasImageSourceInfo()
        && imageLayoutProperty->GetImageSourceInfoValue().GetPixmap() == src;
}

bool ImagePattern::IsFormRender()
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    return pipeline->IsFormRender();
}

void ImagePattern::UpdateFormDurationByRemainder()
{
    if (IsFormRender()) {
        if (!isFormAnimationStart_) {
            formAnimationRemainder_ =
                DEFAULT_DURATION - (GetMicroTickCount() - formAnimationStartTime_) / MICROSEC_TO_MILLISEC;
        }
        if ((formAnimationRemainder_ > 0) && (animator_->GetDuration() > formAnimationRemainder_)) {
            animator_->SetDuration(formAnimationRemainder_);
        }
        if (formAnimationRemainder_ <= 0) {
            isFormAnimationEnd_ = true;
        }
    }
}

void ImagePattern::ResetFormAnimationStartTime()
{
    if (isFormAnimationStart_) {
        isFormAnimationStart_ = false;
        formAnimationStartTime_ = GetMicroTickCount();
    }
}

void ImagePattern::ResetFormAnimationFlag()
{
    if (IsFormRender()) {
        formAnimationRemainder_ = DEFAULT_DURATION;
        isFormAnimationStart_ = true;
        isFormAnimationEnd_ = false;
    }
}

void ImagePattern::SetIteration(int32_t iteration)
{
    if (iteration < -1) {
        return;
    }
    if (IsFormRender()) {
        iteration = DEFAULT_ITERATIONS;
    }
    animator_->SetIteration(iteration);
}

void ImagePattern::SetDuration(int32_t duration)
{
    if (duration < 0) {
        return;
    }
    int32_t finalDuration = durationTotal_ > 0 ? durationTotal_ : duration;
    if (IsFormRender()) {
        finalDuration = finalDuration < DEFAULT_DURATION ? finalDuration : DEFAULT_DURATION;
    }
    if (animator_->GetDuration() == finalDuration) {
        animator_->RemoveRepeatListener(repeatCallbackId_);
        return;
    }
    if (animator_->GetStatus() == Animator::Status::IDLE || animator_->GetStatus() == Animator::Status::STOPPED) {
        animator_->SetDuration(finalDuration);
        animator_->RemoveRepeatListener(repeatCallbackId_);
        return;
    }
    // if animator is running or paused, duration will work next time
    animator_->RemoveRepeatListener(repeatCallbackId_);
    repeatCallbackId_ = animator_->AddRepeatListener([weak = WeakClaim(this), finalDuration]() {
        auto imageAnimator = weak.Upgrade();
        CHECK_NULL_VOID(imageAnimator);
        imageAnimator->animator_->SetDuration(finalDuration);
    });
}

void ImagePattern::SetOnProgressCallback(
    std::function<void(const uint32_t& dlNow, const uint32_t& dlTotal)>&& onProgress)
{
    onProgressCallback_ = onProgress;
}

void ImagePattern::OnSensitiveStyleChange(bool isSensitive)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto privacySensitive = host->IsPrivacySensitive();
    if (isSensitive && privacySensitive) {
        isSensitive_ = true;
        auto renderContext = host->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        CalcDimension radius;
        radius.SetValue(IMAGE_SENSITIVE_RADIUS);
        Color color = Color::FromARGB(13, 255, 255, 255);
        EffectOption option = { radius, IMAGE_SENSITIVE_SATURATION, IMAGE_SENSITIVE_BRIGHTNESS, color };
        if (renderContext->GetBackBlurRadius().has_value()) {
            renderContext->UpdateBackBlurRadius(Dimension());
        }
        if (renderContext->GetBackBlurStyle().has_value()) {
            renderContext->UpdateBackBlurStyle(std::nullopt);
        }
        renderContext->UpdateBackgroundEffect(option);
    } else {
        isSensitive_ = false;
    }
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void ImagePattern::ResetImageProperties()
{
    SetCopyOption(CopyOptions::None);
    OnImageModifyDone();
}

void ImagePattern::ResetImage()
{
    image_ = nullptr;
    imageQuality_ = AIImageQuality::NONE;
    isImageQualityChange_ = false;
    loadingCtx_.Reset();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (!altImage_) {
        auto rsRenderContext = host->GetRenderContext();
        CHECK_NULL_VOID(rsRenderContext);
        rsRenderContext->ClearDrawCommands();
    }
}

void ImagePattern::ResetAltImage()
{
    altImage_ = nullptr;
    altLoadingCtx_.Reset();
    if (!image_) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto rsRenderContext = host->GetRenderContext();
        CHECK_NULL_VOID(rsRenderContext);
        rsRenderContext->ClearDrawCommands();
    }
}

void ImagePattern::ResetImageAndAlt()
{
    image_ = nullptr;
    loadingCtx_ = nullptr;
    srcRect_.Reset();
    dstRect_.Reset();
    altLoadingCtx_ = nullptr;
    altImage_ = nullptr;
    altDstRect_.reset();
    altSrcRect_.reset();
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    auto rsRenderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(rsRenderContext);
    rsRenderContext->ClearDrawCommands();
    CloseSelectOverlay();
    DestroyAnalyzerOverlay();
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void ImagePattern::ResetPictureSize()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    const auto& layoutProperty = host->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->ClearUserDefinedIdealSize(true, true);
    hasSizeChanged = false;
}

void ImagePattern::SetColorFilter(const RefPtr<FrameNode>& imageFrameNode)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderProperty = host->GetPaintProperty<ImageRenderProperty>();
    CHECK_NULL_VOID(renderProperty);
    auto imageRenderProperty = imageFrameNode->GetPaintProperty<ImageRenderProperty>();
    CHECK_NULL_VOID(imageRenderProperty);
    if (renderProperty->HasColorFilter()) {
        imageRenderProperty->UpdateColorFilter(renderProperty->GetColorFilter().value());
    }
    if (renderProperty->HasDrawingColorFilter()) {
        imageRenderProperty->UpdateDrawingColorFilter(renderProperty->GetDrawingColorFilter().value());
    }
}

void ImagePattern::SetImageFit(const RefPtr<FrameNode>& imageFrameNode)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto renderProperty = host->GetPaintProperty<ImageRenderProperty>();
    CHECK_NULL_VOID(renderProperty);
    auto imageLayoutProperty = imageFrameNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageLayoutProperty);
    auto imageRenderProperty = imageFrameNode->GetPaintProperty<ImageRenderProperty>();
    CHECK_NULL_VOID(imageRenderProperty);
    if (renderProperty->HasImageFit()) {
        imageRenderProperty->UpdateImageFit(renderProperty->GetImageFit().value());
    }
    if (layoutProperty->HasImageFit()) {
        imageLayoutProperty->UpdateImageFit(layoutProperty->GetImageFit().value());
    }
}

void ImagePattern::SetObscured()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto imageFrameNode = AceType::DynamicCast<FrameNode>(host->GetChildren().front());
    CHECK_NULL_VOID(imageFrameNode);
    auto obscuredReasons = host->GetRenderContext()->GetObscured().value_or(std::vector<ObscuredReasons>());
    const auto& castRenderContext = imageFrameNode->GetRenderContext();
    if (castRenderContext) {
        castRenderContext->UpdateObscured(obscuredReasons);
    }
    imageFrameNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    host->GetRenderContext()->ResetObscured();
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void ImagePattern::TriggerVisibleAreaChangeForChild(const RefPtr<UINode>& node, bool visible, double ratio)
{
    for (const auto& childNode : node->GetChildren()) {
        if (AceType::InstanceOf<FrameNode>(childNode)) {
            auto frame = AceType::DynamicCast<FrameNode>(childNode);
            if (!frame || !frame->GetEventHub<EventHub>()) {
                continue;
            }
            auto callback = frame->GetEventHub<EventHub>()->GetVisibleAreaCallback(true).callback;
            if (callback) {
                callback(visible, ratio);
            }
        }
        TriggerVisibleAreaChangeForChild(childNode, visible, ratio);
    }
}
} // namespace OHOS::Ace::NG
