/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

#define NAPI_VERSION 8

#include "core/components_ng/pattern/image/image_pattern.h"

#include "base/image/image_perf.h"
#include "base/log/dump_log.h"
#include "base/network/download_manager.h"
#include "core/common/ace_engine_ext.h"
#include "core/common/ai/image_analyzer_manager.h"
#include "core/common/udmf/udmf_client.h"
#include "core/components/common/layout/constants.h"
#include "core/components/image/image_theme.h"
#include "core/components/text/text_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/image_provider/image_utils.h"
#include "core/components_ng/pattern/image/image_content_modifier.h"
#include "core/components_ng/pattern/image/image_dfx.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_paint_method.h"
#include "core/components_ng/property/border_property.h"
#include "core/components_ng/render/drawing.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t DEFAULT_DURATION = 1000; // ms
constexpr uint32_t CRITICAL_TIME = 50;     // ms. If show time of image is less than this, use more cacheImages.
constexpr int64_t MICROSEC_TO_MILLISEC = 1000;
constexpr int32_t DEFAULT_ITERATIONS = 1;
constexpr int32_t MEMORY_LEVEL_CRITICAL_STATUS = 2;

std::string GetImageInterpolation(ImageInterpolation interpolation)
{
    switch (interpolation) {
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

std::string GetDynamicModeString(DynamicRangeMode dynamicMode)
{
    switch (dynamicMode) {
        case DynamicRangeMode::HIGH:
            return "HIGH";
        case DynamicRangeMode::CONSTRAINT:
            return "CONSTRAINT";
        case DynamicRangeMode::STANDARD:
            return "STANDARD";
        default:
            return "STANDARD";
    }
}

std::string ConvertOrientationToString(ImageRotateOrientation orientation)
{
    switch (orientation) {
        case ImageRotateOrientation::UP:
            return "UP";
        case ImageRotateOrientation::RIGHT:
            return "RIGHT";
        case ImageRotateOrientation::DOWN:
            return "DOWN";
        case ImageRotateOrientation::LEFT:
            return "LEFT";
        case ImageRotateOrientation::UP_MIRRORED:
            return "UP_MIRRORED";
        case ImageRotateOrientation::RIGHT_MIRRORED:
            return "RIGHT_MIRRORED";
        case ImageRotateOrientation::DOWN_MIRRORED:
            return "DOWN_MIRRORED";
        case ImageRotateOrientation::LEFT_MIRRORED:
            return "LEFT_MIRRORED";
        case ImageRotateOrientation::AUTO:
            return "AUTO";
        default:
            return "UP";
    }
}
} // namespace

constexpr float BOX_EPSILON = 0.5f;
constexpr float IMAGE_SENSITIVE_RADIUS = 80.0f;
constexpr double IMAGE_SENSITIVE_SATURATION = 1.0;
constexpr double IMAGE_SENSITIVE_BRIGHTNESS = 1.08;
constexpr uint32_t MAX_SRC_LENGTH = 120; // prevent the Base64 image format from too long.
constexpr int32_t IMAGE_LOAD_FAIL = 0;
constexpr int32_t IMAGE_LOAD_SUCCESS = 1;

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
        pattern->isOrientationChange_ = false;
        auto imageLayoutProperty = pattern->GetLayoutProperty<ImageLayoutProperty>();
        CHECK_NULL_VOID(imageLayoutProperty);
        auto currentSourceInfo = imageLayoutProperty->GetImageSourceInfo().value_or(ImageSourceInfo(""));
        if (currentSourceInfo != sourceInfo) {
            TAG_LOGW(AceLogTag::ACE_IMAGE, "src not match, %{public}s: %{private}s - %{private}s",
                pattern->imageDfxConfig_.ToStringWithoutSrc().c_str(), currentSourceInfo.ToString().c_str(),
                sourceInfo.ToString().c_str());
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
        pattern->isOrientationChange_ = false;
        auto imageLayoutProperty = pattern->GetLayoutProperty<ImageLayoutProperty>();
        CHECK_NULL_VOID(imageLayoutProperty);
        auto currentSourceInfo = imageLayoutProperty->GetImageSourceInfo().value_or(ImageSourceInfo(""));
        if (currentSourceInfo != sourceInfo) {
            TAG_LOGW(AceLogTag::ACE_IMAGE, "src not match, %{public}s: %{private}s - %{private}s",
                pattern->imageDfxConfig_.ToStringWithoutSrc().c_str(), currentSourceInfo.ToString().c_str(),
                sourceInfo.ToString().c_str());
            return;
        }
        pattern->OnImageLoadSuccess();
    };
}

LoadFailNotifyTask ImagePattern::CreateLoadFailCallback()
{
    return [weak = WeakClaim(this)](
               const ImageSourceInfo& sourceInfo, const std::string& errorMsg, const ImageErrorInfo& errorInfo) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->isOrientationChange_ = false;
        auto imageLayoutProperty = pattern->GetLayoutProperty<ImageLayoutProperty>();
        CHECK_NULL_VOID(imageLayoutProperty);
        auto currentSourceInfo = imageLayoutProperty->GetImageSourceInfo().value_or(ImageSourceInfo(""));
        if (currentSourceInfo != sourceInfo) {
            TAG_LOGW(AceLogTag::ACE_IMAGE, "src not match, %{public}s: %{private}s - %{private}s",
                pattern->imageDfxConfig_.ToStringWithoutSrc().c_str(), currentSourceInfo.ToString().c_str(),
                sourceInfo.ToString().c_str());
            return;
        }
        if (!currentSourceInfo.IsFromReset()) {
            pattern->OnImageLoadFail(errorMsg, errorInfo);
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
            TAG_LOGW(AceLogTag::ACE_IMAGE, "src not match, %{public}s: %{private}s - %{private}s",
                pattern->imageDfxConfig_.ToStringWithoutSrc().c_str(), currentSourceInfo.ToString().c_str(),
                sourceInfo.ToString().c_str());
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
    auto imageEventHub = GetOrCreateEventHub<ImageEventHub>();
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
    if (isComponentSnapshotNode_ || isImageAnimator_) {
        OnVisibleAreaChange(true);
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    RectF frameRect;
    RectF visibleInnerRect;
    RectF visibleRect;
    host->GetVisibleRectWithClip(visibleRect, visibleInnerRect, frameRect);
    bool visible = GreatNotEqual(visibleInnerRect.Width(), 0.0) && GreatNotEqual(visibleInnerRect.Height(), 0.0);
    ACE_SCOPED_TRACE("TriggerFirstVisibleAreaChange [%d]-%s", visible, imageDfxConfig_.ToStringWithSrc().c_str());
    if (SystemProperties::GetDebugEnabled()) {
        TAG_LOGD(AceLogTag::ACE_IMAGE, "TriggerFirstVisibleAreaChange [%{public}d]-%{public}s", visible,
            imageDfxConfig_.ToStringWithSrc().c_str());
    }
    OnVisibleAreaChange(visible);
}

void ImagePattern::PrepareAnimation(const RefPtr<CanvasImage>& image)
{
    if (image->IsStatic()) {
        return;
    }
    SetRedrawCallback(image);
    SetOnFinishCallback(image);
    RegisterVisibleAreaChange();
    TriggerFirstVisibleAreaChange();
}

void ImagePattern::SetOnFinishCallback(const RefPtr<CanvasImage>& image)
{
    CHECK_NULL_VOID(image);
    image->SetOnFinishCallback([weak = WeakPtr(GetHost())] {
        auto imageNode = weak.Upgrade();
        CHECK_NULL_VOID(imageNode);
        auto eventHub = imageNode->GetOrCreateEventHub<ImageEventHub>();
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
    std::vector<double> ratioList = { 0.0 };
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
    auto parent = host->GetAncestorNodeOfFrame(true);
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
    SizeF handleSize = { SelectHandleInfo::GetDefaultLineWidth().ConvertToPx(),
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
    return host->GetPaintRectOffset(false, true) - rootOffset;
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
    auto eventHub = host->GetOrCreateEventHub<ImageEventHub>();
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

void ImagePattern::ApplyAIModificationsToImage()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    const auto& geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    if (IsSupportImageAnalyzerFeature()) {
        if (isPixelMapChanged_) {
            UpdateAnalyzerOverlay();
        }
        UpdateAnalyzerUIConfig(geometryNode);
        auto context = host->GetContext();
        CHECK_NULL_VOID(context);
        auto uiTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
        uiTaskExecutor.PostTask(
            [weak = WeakClaim(this)] {
                auto pattern = weak.Upgrade();
                CHECK_NULL_VOID(pattern);
                ContainerScope scope(pattern->GetHostInstanceId());
                pattern->CreateAnalyzerOverlay();
            },
            "ArkUIImageCreateAnalyzerOverlay");
    }
}

void ImagePattern::ReportPerfData(const RefPtr<NG::FrameNode>& host, int32_t state)
{
    auto accessibilityId = host->GetAccessibilityId();
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto type = loadingCtx_->GetSourceInfo().GetSrcType();
    std::string srcType = GetSrcTypeToString(type);
    std::pair<int32_t, int32_t> size(geometryNode->GetFrameSize().Width(), geometryNode->GetFrameSize().Height());
    ImagePerf::GetPerfMonitor()->EndRecordImageLoadStat(accessibilityId, srcType, size, state);
}

void ImagePattern::OnImageLoadSuccess()
{
    CHECK_NULL_VOID(loadingCtx_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    const auto& geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);

    image_ = loadingCtx_->MoveCanvasImage();
    if (!image_) {
        TAG_LOGW(AceLogTag::ACE_IMAGE, "%{public}s, %{private}s image is null.",
            imageDfxConfig_.ToStringWithoutSrc().c_str(), imageDfxConfig_.GetImageSrc().c_str());
        return;
    }
    srcRect_ = loadingCtx_->GetSrcRect();
    dstRect_ = loadingCtx_->GetDstRect();
    auto srcInfo = loadingCtx_->GetSourceInfo();
    auto frameCount = loadingCtx_->GetFrameCount();

    image_->SetImageDfxConfig(imageDfxConfig_);
    RectF paintRect = CalcImageContentPaintSize(geometryNode);
    LoadImageSuccessEvent event(loadingCtx_->GetImageSize().Width(), loadingCtx_->GetImageSize().Height(),
        geometryNode->GetFrameSize().Width(), geometryNode->GetFrameSize().Height(), 1, paintRect.Width(),
        paintRect.Height(), paintRect.GetX(), paintRect.GetY());

    SetImagePaintConfig(image_, srcRect_, dstRect_, srcInfo, frameCount);
    if (srcInfo.IsSvg()) {
        UpdateSvgSmoothEdgeValue();
    }
    PrepareAnimation(image_);
    if (enableDrag_) {
        EnableDrag();
    }
    ClearAltData();
    auto eventHub = GetOrCreateEventHub<ImageEventHub>();
    if (eventHub) {
        eventHub->FireCompleteEvent(event);
    }

    ApplyAIModificationsToImage();

    ACE_SCOPED_TRACE("OnImageLoadSuccess %s", imageDfxConfig_.ToStringWithSrc().c_str());
    if (SystemProperties::GetDebugEnabled()) {
        TAG_LOGI(AceLogTag::ACE_IMAGE, "ImageLoadSuccess %{public}s", imageDfxConfig_.ToStringWithSrc().c_str());
    }
    auto context = host->GetRenderContext();
    auto pixelMap = image_->GetPixelMap();
    if (pixelMap) {
        SetPixelMapMemoryName(pixelMap);
    }
    if (context && pixelMap) {
        context->SetIsWideColorGamut(pixelMap->GetIsWideColorGamut());
    }
    ReportPerfData(host, IMAGE_LOAD_SUCCESS);
    host->MarkNeedRenderOnly();
}

bool ImagePattern::SetPixelMapMemoryName(RefPtr<PixelMap>& pixelMap)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto id = host->GetInspectorId();
    if (id.has_value()) {
        pixelMap->SetMemoryName(id.value());
        hasSetPixelMapMemoryName_ = true;
        return true;
    }
    return false;
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
    // update rotate orientation before decoding
    UpdateOrientation();

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

// Update the necessary rotate orientation for drawing and measuring.
void ImagePattern::UpdateOrientation()
{
    auto imageObj = loadingCtx_->GetImageObject();
    CHECK_NULL_VOID(imageObj);
    if (imageObj->GetFrameCount() > 1) {
        imageObj->SetOrientation(ImageRotateOrientation::UP);
        return;
    }
    imageObj->SetUserOrientation(userOrientation_);
    selfOrientation_ = imageObj->GetOrientation();
    if (userOrientation_ == ImageRotateOrientation::UP) {
        joinOrientation_ = ImageRotateOrientation::UP;
        return;
    }
    if (userOrientation_ == ImageRotateOrientation::AUTO) {
        joinOrientation_ = selfOrientation_;
    } else {
        joinOrientation_ = userOrientation_;
    }
    // update image object orientation before decoding
    imageObj->SetOrientation(joinOrientation_);
}

void ImagePattern::OnImageLoadFail(const std::string& errorMsg, const ImageErrorInfo& errorInfo)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    const auto& geometryNode = host->GetGeometryNode();
    auto imageEventHub = GetOrCreateEventHub<ImageEventHub>();
    CHECK_NULL_VOID(imageEventHub);
    LoadImageFailEvent event(
        geometryNode->GetFrameSize().Width(), geometryNode->GetFrameSize().Height(), errorMsg, errorInfo);
    ReportPerfData(host, IMAGE_LOAD_FAIL);
    imageEventHub->FireErrorEvent(event);
}

void ImagePattern::SetExternalDecodeFormat(PixelFormat externalDecodeFormat)
{
    isImageReloadNeeded_ = isImageReloadNeeded_ | (externalDecodeFormat_ != externalDecodeFormat);
    switch (externalDecodeFormat) {
        case PixelFormat::NV21:
        case PixelFormat::RGBA_8888:
        case PixelFormat::RGBA_1010102:
        case PixelFormat::YCBCR_P010:
        case PixelFormat::YCRCB_P010:
            externalDecodeFormat_ = externalDecodeFormat;
            break;
        default:
            externalDecodeFormat_ = PixelFormat::UNKNOWN;
    }
}

void ImagePattern::StartDecoding(const SizeF& dstSize)
{
    // if layout size has not decided yet, resize target can not be calculated
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (!host->GetGeometryNode()->GetContent()) {
        return;
    }

    ACE_SCOPED_TRACE("StartDecoding imageInfo: [%s]", imageDfxConfig_.ToStringWithSrc().c_str());

    const auto& props = DynamicCast<ImageLayoutProperty>(host->GetLayoutProperty());
    CHECK_NULL_VOID(props);
    bool autoResize = props->GetAutoResize().value_or(autoResizeDefault_);

    ImageFit imageFit = props->GetImageFit().value_or(ImageFit::COVER);
    const std::optional<SizeF>& sourceSize = props->GetSourceSize();
    auto renderProp = host->GetPaintProperty<ImageRenderProperty>();
    bool hasValidSlice = renderProp && (renderProp->HasImageResizableSlice() || renderProp->HasImageResizableLattice());
    bool isHdrDecoderNeed = renderProp && (renderProp->HasDynamicMode() || renderProp->HasHdrBrightness());

    if (loadingCtx_) {
        loadingCtx_->SetIsHdrDecoderNeed(isHdrDecoderNeed);
        loadingCtx_->SetImageQuality(GetImageQuality());
        loadingCtx_->SetPhotoDecodeFormat(GetExternalDecodeFormat());
        loadingCtx_->MakeCanvasImageIfNeed(dstSize, autoResize, imageFit, sourceSize, hasValidSlice);
    }
    if (altLoadingCtx_) {
        altLoadingCtx_->SetIsHdrDecoderNeed(isHdrDecoderNeed);
        altLoadingCtx_->SetImageQuality(GetImageQuality());
        altLoadingCtx_->SetPhotoDecodeFormat(GetExternalDecodeFormat());
        altLoadingCtx_->MakeCanvasImageIfNeed(dstSize, autoResize, imageFit, sourceSize, hasValidSlice);
    }
}

void ImagePattern::UpdateSvgSmoothEdgeValue()
{
    auto renderProp = GetPaintProperty<ImageRenderProperty>();
    CHECK_NULL_VOID(renderProp);
    renderProp->UpdateSmoothEdge(std::max(smoothEdge_, renderProp->GetSmoothEdge().value_or(0.0f)));
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
    if (GreatNotEqual(frameCount, 1)) {
        config.orientation_ = ImageRotateOrientation::UP;
    } else {
        config.orientation_ = joinOrientation_;
    }
    canvasImage->SetPaintConfig(config);
}

RefPtr<NodePaintMethod> ImagePattern::CreateNodePaintMethod()
{
    CreateModifier();
    bool sensitive = false;
    if (isSensitive_) {
        auto host = GetHost();
        CHECK_NULL_RETURN(host, nullptr);
        sensitive = host->IsPrivacySensitive();
    }
    ImagePaintMethodConfig imagePaintMethodConfig { .sensitive = sensitive,
        .selected = isSelected_,
        .imageOverlayModifier = overlayMod_,
        .imageContentModifier = contentMod_,
        .interpolation = interpolationDefault_ };
    // Callback function executed after the graphics rendering is complete.
    auto drawCompleteCallback = [weakPattern = WeakClaim(this)](const RenderedImageInfo& renderedImageInfo) {
        auto pattern = weakPattern.Upgrade();
        CHECK_NULL_VOID(pattern);
        // Mark the rendering as successful on the instance.
        pattern->SetRenderedImageInfo(std::move(renderedImageInfo));
    };
    if (image_) {
        image_->SetDrawCompleteCallback(std::move(drawCompleteCallback));
        imagePaintMethod_->UpdatePaintMethod(image_, imagePaintMethodConfig);
        return imagePaintMethod_;
    }
    if (altImage_ && altDstRect_ && altSrcRect_) {
        altImage_->SetDrawCompleteCallback(std::move(drawCompleteCallback));
        imagePaintMethod_->UpdatePaintMethod(altImage_, imagePaintMethodConfig);
        return imagePaintMethod_;
    }
    CreateObscuredImage();
    if (obscuredImage_) {
        obscuredImage_->SetDrawCompleteCallback(std::move(drawCompleteCallback));
        imagePaintMethod_->UpdatePaintMethod(obscuredImage_, imagePaintMethodConfig);
        return imagePaintMethod_;
    }
    imagePaintMethodConfig.imageContentModifier = nullptr;
    imagePaintMethodConfig.imageOverlayModifier = nullptr;
    imagePaintMethod_->UpdatePaintMethod(nullptr, imagePaintMethodConfig);
    return imagePaintMethod_;
}

void ImagePattern::CreateModifier()
{
    if (!contentMod_) {
        contentMod_ = MakeRefPtr<ImageContentModifier>(WeakClaim(this));
    }
    if (!overlayMod_) {
        overlayMod_ = MakeRefPtr<ImageOverlayModifier>(selectedColor_);
    }
    if (!imagePaintMethod_) {
        imagePaintMethod_ = MakeRefPtr<ImagePaintMethod>(nullptr);
    }
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

    if (imageType_ == ImageType::PIXELMAP_DRAWABLE) {
        return true;
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

ImageDfxConfig ImagePattern::CreateImageDfxConfig(const ImageSourceInfo& src)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, ImageDfxConfig());
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, ImageDfxConfig());
    return {
        { host->GetId(), host->GetAccessibilityId(), renderContext->GetNodeId() },
        static_cast<int32_t>(src.GetSrcType()),
        src.ToString().substr(0, MAX_SRC_LENGTH),
        host->IsTrimMemRecycle(),
    };
}

void ImagePattern::LoadImage(const ImageSourceInfo& src, bool needLayout)
{
    if (loadingCtx_) {
        auto srcKey = src.GetKey();
        auto loadKey = loadingCtx_->GetSourceInfo().GetKey();
        isPixelMapChanged_ = srcKey != loadKey;
    }
    LoadNotifier loadNotifier(CreateDataReadyCallback(), CreateLoadSuccessCallback(), CreateLoadFailCallback());
    loadNotifier.onDataReadyComplete_ = CreateCompleteCallBackInDataReady();

    imageDfxConfig_ = CreateImageDfxConfig(src);

    loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(src, std::move(loadNotifier), syncLoad_, imageDfxConfig_);

    if (SystemProperties::GetDebugEnabled()) {
        TAG_LOGI(AceLogTag::ACE_IMAGE, "load image, %{private}s", imageDfxConfig_.ToStringWithSrc().c_str());
    }

    if (onProgressCallback_) {
        loadingCtx_->SetOnProgressCallback(std::move(onProgressCallback_));
    }
    if (!needLayout) {
        loadingCtx_->FinishMearuse();
    }
    // Before loading new image data, reset the render success status to `false`.
    renderedImageInfo_.renderSuccess = false;
    // Reset the reload flag before loading the image to ensure a fresh state.
    isImageReloadNeeded_ = false;
    ImagePerf::GetPerfMonitor()->StartRecordImageLoadStat(imageDfxConfig_.GetAccessibilityId());
    loadingCtx_->LoadImageData();
}

void ImagePattern::LoadAltImage(const ImageSourceInfo& altImageSourceInfo)
{
    CHECK_NULL_VOID(GetNeedLoadAlt());
    LoadNotifier altLoadNotifier(CreateDataReadyCallbackForAlt(), CreateLoadSuccessCallbackForAlt(), nullptr);
    if (!altLoadingCtx_ || altLoadingCtx_->GetSourceInfo() != altImageSourceInfo ||
        (altLoadingCtx_ && altImageSourceInfo.IsSvg())) {
        auto host = GetHost();

        altImageDfxConfig_ = CreateImageDfxConfig(altImageSourceInfo);
        altLoadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(
            altImageSourceInfo, std::move(altLoadNotifier), false, altImageDfxConfig_);
        altLoadingCtx_->LoadImageData();
    }
}

void ImagePattern::LoadImageDataIfNeed()
{
    auto imageLayoutProperty = GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageLayoutProperty);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto src = imageLayoutProperty->GetImageSourceInfo().value_or(ImageSourceInfo(""));
    UpdateInternalResource(src);

    if (!loadingCtx_ || loadingCtx_->GetSourceInfo() != src || isImageReloadNeeded_ || isOrientationChange_) {
        bool needLayout = host->CheckNeedForceMeasureAndLayout() &&
                          imageLayoutProperty->GetVisibility().value_or(VisibleType::VISIBLE) != VisibleType::GONE;
        LoadImage(src, needLayout);
    } else if (IsSupportImageAnalyzerFeature()) {
        auto context = host->GetContext();
        CHECK_NULL_VOID(context);
        auto uiTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
        uiTaskExecutor.PostTask(
            [weak = WeakClaim(this)] {
                auto pattern = weak.Upgrade();
                CHECK_NULL_VOID(pattern);
                ContainerScope scope(pattern->GetHostInstanceId());
                pattern->CreateAnalyzerOverlay();
                auto host = pattern->GetHost();
                pattern->UpdateAnalyzerUIConfig(host->GetGeometryNode());
            },
            "ArkUIImageUpdateAnalyzerUIConfig");
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

    enableDrag_ = host->IsDraggable();

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
        case ImageType::ANIMATED_DRAWABLE:
            OnAnimatedModifyDone();
            break;
        case ImageType::PIXELMAP_DRAWABLE:
            OnPixelMapDrawableModifyDone();
            break;
        default:
            break;
    }

    InitOnKeyEvent();
}

void ImagePattern::InitOnKeyEvent()
{
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_FOURTEEN) || keyEventCallback_) {
        return;
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetOrCreateEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto focusHub = hub->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    keyEventCallback_ = [weak = WeakClaim(this)](const KeyEvent& event) -> bool {
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        pattern->OnKeyEvent();
        return false;
    };
    focusHub->SetOnKeyEventInternal(std::move(keyEventCallback_));
}

void ImagePattern::OnKeyEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->PaintFocusState(true);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
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
    if ((status_ == AnimatorStatus::IDLE || status_ == AnimatorStatus::STOPPED) && !firstUpdateEvent_) {
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
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (!host->IsOnMainTree()) {
        return;
    }
    if (!animator_->HasScheduler()) {
        auto context = host->GetContextRefPtr();
        if (context) {
            animator_->AttachScheduler(context);
        } else {
            TAG_LOGW(AceLogTag::ACE_IMAGE, "pipeline is null.");
        }
    }
    switch (status_) {
        case AnimatorStatus::IDLE:
            animator_->Cancel();
            ResetFormAnimationFlag();
            SetShowingIndex(index);
            break;
        case AnimatorStatus::PAUSED:
            animator_->Pause();
            ResetFormAnimationFlag();
            break;
        case AnimatorStatus::STOPPED:
            animator_->Finish();
            ResetFormAnimationFlag();
            break;
        default:
            ResetFormAnimationStartTime();
            if (isFormAnimationEnd_) {
                ResetFormAnimationFlag();
                return;
            }
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
    CHECK_EQUAL_VOID(CheckImagePrivacyForCopyOption(), true);
    CloseSelectOverlay();
    UpdateOffsetForImageAnalyzerOverlay();
    SetFrameOffsetForOverlayNode();
}

void ImagePattern::OnPixelMapDrawableModifyDone()
{
    Pattern::OnModifyDone();
    UpdateGestureAndDragWhenModify();
    CHECK_EQUAL_VOID(CheckImagePrivacyForCopyOption(), true);
    CloseSelectOverlay();
    UpdateOffsetForImageAnalyzerOverlay();
    SetFrameOffsetForOverlayNode();
    // Data loading is not managed by image. Therefore, during component
    // attribute initilizationm, the dirty node mark of image needs to
    // be registered withe Drawable. Drawable triggers drawing again after
    // data loading is complete.
    RegisterDrawableRedrawCallback();
}

void ImagePattern::RegisterDrawableRedrawCallback()
{
    if (isRegisterRedrawCallback_) {
        return;
    }
    CHECK_NULL_VOID(drawable_);
    drawable_->RegisterRedrawCallback([weak = WeakClaim(this)] {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto context = pattern->GetContext();
        CHECK_NULL_VOID(context);
        auto taskExecutor = context->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        taskExecutor->PostTask(
            [weak = weak] {
                auto pattern = weak.Upgrade();
                CHECK_NULL_VOID(pattern);
                pattern->Validate();
            },
            TaskExecutor::TaskType::UI, "ArkUIImageDrawableMarkRender");
    });
    isRegisterRedrawCallback_ = true;
}

void ImagePattern::Validate()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    ACE_SCOPED_TRACE("[Drawable][%d] validate callback", host->GetId());
    // first mark dirty render
    host->MarkNeedRenderOnly();
    CHECK_NULL_VOID(contentMod_);
    // because drawable is not a drawing attribute of the
    // content modifier, redrawing cannot be trigged when
    // drawable validates the content modifier. Therefore
    // count attribute in the modifier needs to be used to
    // forcibly refresh the content modifier.
    contentMod_->SetContentChange();
}

ImagePaintConfig ImagePattern::CreatePaintConfig()
{
    ImagePaintConfig config;
    auto lp = GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_RETURN(lp, config);
    config.imageFit_ = lp->GetImageFit().value_or(ImageFit::COVER);
    return config;
}

void ImagePattern::DrawDrawable(RSCanvas& canvas)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    ACE_SCOPED_TRACE("[Drawable][%d] draw to canvas", host->GetId());
    CHECK_NULL_VOID(drawable_);
    auto config = CreatePaintConfig();
    drawable_->Draw(canvas, config);
}

std::optional<SizeF> ImagePattern::GetImageSizeForMeasure()
{
    if ((!loadingCtx_ || !loadingCtx_->GetImageSize().IsPositive()) &&
        (!altLoadingCtx_ || !altLoadingCtx_->GetImageSize().IsPositive())) {
        return std::nullopt;
    }
    auto rawImageSize = SizeF(-1.0, -1.0);
    if (loadingCtx_) {
        rawImageSize = loadingCtx_->GetImageSize();
    }
    if (rawImageSize.IsNegative() && altLoadingCtx_) {
        rawImageSize = altLoadingCtx_->GetImageSize();
    }
    return std::make_optional<SizeF>(rawImageSize.Width(), rawImageSize.Height());
}

void ImagePattern::FinishMeasureForOnComplete()
{
    CHECK_NULL_VOID(loadingCtx_);
    loadingCtx_->FinishMearuse();
    loadingCtx_->CallbackAfterMeasureIfNeed();
}

bool ImagePattern::CheckImagePrivacyForCopyOption()
{
    if (copyOption_ == CopyOptions::None) {
        return false;
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    bool hasObscured = false;
    if (host->GetRenderContext()->GetObscured().has_value()) {
        auto obscuredReasons = host->GetRenderContext()->GetObscured().value();
        hasObscured = std::any_of(obscuredReasons.begin(), obscuredReasons.end(),
            [](const auto& reason) { return reason == ObscuredReasons::PLACEHOLDER; });
    }
    if (!hasObscured) {
        InitCopy();
        return true;
    }
    return false;
}

void ImagePattern::UpdateOffsetForImageAnalyzerOverlay()
{
    if (imageAnalyzerManager_ && imageAnalyzerManager_->IsOverlayCreated()) {
        if (!IsSupportImageAnalyzerFeature()) {
            DestroyAnalyzerOverlay();
        } else {
            UpdateAnalyzerOverlayLayout();
        }
    }
}

// SetUsingContentRectForRenderFrame is set for image paint
void ImagePattern::SetFrameOffsetForOverlayNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto overlayNode = host->GetOverlayNode();
    if (overlayNode) {
        auto layoutProperty = host->GetLayoutProperty();
        CHECK_NULL_VOID(layoutProperty);
        auto padding = layoutProperty->CreatePaddingAndBorder();
        auto renderContext = overlayNode->GetRenderContext();
        if (renderContext) {
            renderContext->SetRenderFrameOffset({ -padding.Offset().GetX(), -padding.Offset().GetY() });
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
            TAG_LOGW(AceLogTag::ACE_IMAGE, "alt src not match, %{public}s: %{private}s - %{private}s",
                pattern->imageDfxConfig_.ToStringWithoutSrc().c_str(), currentAltSourceInfo.ToString().c_str(),
                sourceInfo.ToString().c_str());
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
            TAG_LOGW(AceLogTag::ACE_IMAGE, "alt src not match, %{public}s: %{private}s - %{private}s",
                pattern->imageDfxConfig_.ToStringWithoutSrc().c_str(), currentAltSrc.ToString().c_str(),
                sourceInfo.ToString().c_str());
            return;
        }
        pattern->altImage_ = pattern->altLoadingCtx_->MoveCanvasImage();
        CHECK_NULL_VOID(pattern->altImage_);
        pattern->altImage_->SetImageDfxConfig(pattern->altImageDfxConfig_);
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

bool ImagePattern::RecycleImageData()
{
    // when image component is [onShow] , [no cache], do not clean image data
    bool isDataNoCache = (!loadingCtx_ || (loadingCtx_->GetSourceInfo().GetSrcType() == SrcType::NETWORK &&
                                              SystemProperties::GetDownloadByNetworkEnabled() &&
                                              DownloadManager::GetInstance()->IsContains(
                                                  loadingCtx_->GetSourceInfo().GetSrc()) == false));
    if (isShow_ || isDataNoCache) {
        return false;
    }
    auto frameNode = GetHost();
    if (!frameNode) {
        return false;
    }
    frameNode->SetTrimMemRecycle(true);
    loadingCtx_ = nullptr;
    auto rsRenderContext = frameNode->GetRenderContext();
    if (!rsRenderContext) {
        return false;
    }
    TAG_LOGI(AceLogTag::ACE_IMAGE, "%{public}s, %{private}s recycleImageData.",
        imageDfxConfig_.ToStringWithoutSrc().c_str(), imageDfxConfig_.GetImageSrc().c_str());
    rsRenderContext->RemoveContentModifier(contentMod_);
    contentMod_ = nullptr;
    image_ = nullptr;
    altLoadingCtx_ = nullptr;
    altImage_ = nullptr;
    ACE_SCOPED_TRACE("OnRecycleImageData imageInfo: [%s]", imageDfxConfig_.ToStringWithSrc().c_str());
    return true;
}

void ImagePattern::OnNotifyMemoryLevel(int32_t level)
{
    // when image component is [onShow], do not clean image data
    if (isShow_ || level < MEMORY_LEVEL_CRITICAL_STATUS) {
        return;
    }
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    frameNode->SetTrimMemRecycle(false);
    auto rsRenderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(rsRenderContext);
    TAG_LOGI(AceLogTag::ACE_IMAGE, "%{public}s, %{private}s OnNotifyMemoryLevel %{public}d.",
        imageDfxConfig_.ToStringWithoutSrc().c_str(), imageDfxConfig_.GetImageSrc().c_str(), level);
    rsRenderContext->RemoveContentModifier(contentMod_);
    contentMod_ = nullptr;
    loadingCtx_ = nullptr;
    image_ = nullptr;
    altLoadingCtx_ = nullptr;
    altImage_ = nullptr;
}

// when recycle image component, release the pixelmap resource
void ImagePattern::OnRecycle()
{
    TAG_LOGI(AceLogTag::ACE_IMAGE, "OnRecycle. %{public}s", imageDfxConfig_.ToStringWithoutSrc().c_str());
    loadingCtx_ = nullptr;
    image_ = nullptr;
    altLoadingCtx_ = nullptr;
    altImage_ = nullptr;

    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    auto rsRenderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(rsRenderContext);
    rsRenderContext->RemoveContentModifier(contentMod_);
    contentMod_ = nullptr;
    UnregisterWindowStateChangedCallback();
    frameNode->SetTrimMemRecycle(false);
}

void ImagePattern::OnReuse()
{
    RegisterWindowStateChangedCallback();
    auto renderProp = GetPaintProperty<ImageRenderProperty>();
    CHECK_NULL_VOID(renderProp);
    renderProp->UpdateNeedBorderRadius(needBorderRadius_);
    auto imageLayoutProperty = GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageLayoutProperty);
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
    TAG_LOGD(AceLogTag::ACE_IMAGE, "OnWindowShow. %{public}s, isImageReloadNeeded_ = %{public}d",
        imageDfxConfig_.ToStringWithoutSrc().c_str(), isImageReloadNeeded_);
    isShow_ = true;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (!host->IsTrimMemRecycle()) {
        LoadImageDataIfNeed();
    }
}

void ImagePattern::OnVisibleChange(bool visible)
{
    if (!visible) {
        TAG_LOGD(AceLogTag::ACE_IMAGE, "OnInVisible. %{public}s", imageDfxConfig_.ToStringWithoutSrc().c_str());
        CloseSelectOverlay();
    }
}

void ImagePattern::OnVisibleAreaChange(bool visible, double ratio)
{
    ACE_SCOPED_TRACE(
        "OnVisibleAreaChange visible: [%d], imageInfo: %s", visible, imageDfxConfig_.ToStringWithSrc().c_str());
    if (SystemProperties::GetDebugEnabled()) {
        TAG_LOGI(AceLogTag::ACE_IMAGE, "OnVisibleAreaChange visible:%{public}d, %{public}s", visible,
            imageDfxConfig_.ToStringWithoutSrc().c_str());
    }
    if (!visible) {
        CloseSelectOverlay();
    }
    // control pixelMap List
    if (GetIsAnimation() && !animator_->IsStopped() && animator_->HasScheduler()) {
        if (visible) {
            animator_->Forward();
        } else {
            animator_->Pause();
        }
    }
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
    imagePaintMethod_ = MakeRefPtr<ImagePaintMethod>(nullptr);
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
    auto textTheme = pipeline->GetTheme<TextTheme>();
    CHECK_NULL_VOID(textTheme);
    selectedColor_ = textTheme->GetSelectedColor();
    overlayMod_ = MakeRefPtr<ImageOverlayModifier>(selectedColor_);
    auto imageTheme = pipeline->GetTheme<ImageTheme>();
    CHECK_NULL_VOID(imageTheme);
    smoothEdge_ = imageTheme->GetMinEdgeAntialiasing();
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

void ImagePattern::OnDetachFromMainTree()
{
    if (isNeedReset_) {
        ResetImageAndAlt();
        isNeedReset_ = false;
    }
    if (GetIsAnimation() && !animator_->IsStopped() && animator_->HasScheduler()) {
        animator_->Stop();
    }
}

void ImagePattern::EnableDrag()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto dragStart = [weak = WeakClaim(this)](const RefPtr<OHOS::Ace::DragEvent>& event, const std::string&
                         /* extraParams */) -> DragDropInfo {
        DragDropInfo info;
        auto imagePattern = weak.Upgrade();
        CHECK_NULL_RETURN(imagePattern && imagePattern->loadingCtx_, info);
        AceEngineExt::GetInstance().DragStartExt();
        imagePattern->UpdateDragEvent(event);
        info.extraInfo = imagePattern->loadingCtx_->GetSourceInfo().GetSrc();
        return info;
    };
    auto eventHub = host->GetOrCreateEventHub<EventHub>();
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
    SizeF handleSize = { SelectHandleInfo::GetDefaultLineWidth().ConvertToPx(),
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
    json->PutExtAttr("draggable", enableDrag_ ? "true" : "false", filter);
    json->PutExtAttr("enableAnalyzer", isEnableAnalyzer_ ? "true" : "false", filter);
    auto renderProp = GetPaintProperty<ImageRenderProperty>();
    CHECK_NULL_VOID(renderProp);
    DynamicRangeMode dynamicMode = DynamicRangeMode::STANDARD;
    if (renderProp->HasDynamicMode()) {
        dynamicMode = renderProp->GetDynamicMode().value_or(DynamicRangeMode::STANDARD);
    }
    json->PutExtAttr("dynamicRangeMode", GetDynamicModeString(dynamicMode).c_str(), filter);
    json->PutExtAttr("orientation", std::to_string(static_cast<int>(userOrientation_)).c_str(), filter);
    Matrix4 defaultMatrixValue = Matrix4(1.0f, 0, 0, 0, 0, 1.0f, 0, 0, 0, 0, 1.0f, 0, 0, 0, 0, 1.0f);
    Matrix4 matrixValue = renderProp->HasImageMatrix() ? renderProp->GetImageMatrixValue() : defaultMatrixValue;
    json->PutExtAttr("imageMatrix", matrixValue.ToString().c_str(), filter);
}

void ImagePattern::DumpLayoutInfo()
{
    DumpLog::GetInstance().AddDesc("---- Image Component Layout Dump ----");
    auto layoutProp = GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(layoutProp);

    DumpImageSourceInfo(layoutProp);
    DumpAltSourceInfo(layoutProp);
    DumpImageFit(layoutProp);
    DumpFitOriginalSize(layoutProp);
    DumpSourceSize(layoutProp);
    DumpAutoResize(layoutProp);
}

void ImagePattern::DumpImageSourceInfo(const RefPtr<OHOS::Ace::NG::ImageLayoutProperty>& layoutProp)
{
    auto src = layoutProp->GetImageSourceInfo().value_or(ImageSourceInfo(""));
    DumpLog::GetInstance().AddDesc(std::string("url: ").append(src.ToString()));
    DumpLog::GetInstance().AddDesc(
        std::string("SrcType: ").append(std::to_string(static_cast<int32_t>(src.GetSrcType()))));
    DumpLog::GetInstance().AddDesc(
        std::string("AbilityName: ").append(std::to_string(static_cast<int32_t>(Container::CurrentColorMode()))));
    DumpLog::GetInstance().AddDesc(std::string("BundleName: ").append(src.GetBundleName()));
    DumpLog::GetInstance().AddDesc(std::string("ModuleName: ").append(src.GetModuleName()));
    DumpLog::GetInstance().AddDesc(
        std::string("ColorMode: ").append(std::to_string(static_cast<int32_t>(Container::CurrentColorMode()))));
    DumpLog::GetInstance().AddDesc(
        std::string("LocalColorMode: ").append(std::to_string(static_cast<int32_t>(src.GetLocalColorMode()))));
}

inline void ImagePattern::DumpAltSourceInfo(const RefPtr<OHOS::Ace::NG::ImageLayoutProperty>& layoutProp)
{
    auto altSrc = layoutProp->GetAlt().value_or(ImageSourceInfo(""));
    DumpLog::GetInstance().AddDesc(std::string("altUrl: ").append(altSrc.ToString()));
}

inline void ImagePattern::DumpImageFit(const RefPtr<OHOS::Ace::NG::ImageLayoutProperty>& layoutProp)
{
    auto imageFit = layoutProp->GetImageFit().value_or(ImageFit::COVER);
    DumpLog::GetInstance().AddDesc(std::string("objectFit: ").append(GetImageFitStr(imageFit)));
}

inline void ImagePattern::DumpFitOriginalSize(const RefPtr<OHOS::Ace::NG::ImageLayoutProperty>& layoutProp)
{
    auto fitOriginalSize = layoutProp->GetFitOriginalSize().value_or(false);
    DumpLog::GetInstance().AddDesc(std::string("fitOriginalSize: ").append(fitOriginalSize ? "true" : "false"));
}

inline void ImagePattern::DumpSourceSize(const RefPtr<OHOS::Ace::NG::ImageLayoutProperty>& layoutProp)
{
    const std::optional<SizeF>& sourceSize = layoutProp->GetSourceSize();
    if (sourceSize.has_value()) {
        DumpLog::GetInstance().AddDesc(std::string("sourceSize: ").append(sourceSize.value().ToString()));
    }
}

inline void ImagePattern::DumpAutoResize(const RefPtr<OHOS::Ace::NG::ImageLayoutProperty>& layoutProp)
{
    bool autoResize = layoutProp->GetAutoResize().value_or(autoResizeDefault_);
    autoResize ? DumpLog::GetInstance().AddDesc("autoResize:true") : DumpLog::GetInstance().AddDesc("autoResize:false");
}

void ImagePattern::DumpRenderInfo()
{
    DumpLog::GetInstance().AddDesc("---- Image Component Render Dump ----");
    auto renderProp = GetPaintProperty<ImageRenderProperty>();
    CHECK_NULL_VOID(renderProp);

    DumpRenderMode(renderProp);
    DumpImageRepeat(renderProp);
    DumpImageColorFilter(renderProp);
    DumpFillColor(renderProp);
    DumpDynamicRangeMode(renderProp);
    DumpMatchTextDirection(renderProp);
    DumpSmoothEdge(renderProp);
    DumpBorderRadiusProperties(renderProp);
    DumpResizable(renderProp);
    DumpHdrBrightness(renderProp);
}

inline void ImagePattern::DumpHdrBrightness(const RefPtr<OHOS::Ace::NG::ImageRenderProperty>& renderProp)
{
    if (renderProp->HasHdrBrightness()) {
        auto hdrBrightness = renderProp->GetHdrBrightness().value();
        DumpLog::GetInstance().AddDesc(std::string("hdrBrightness: ").append(std::to_string(hdrBrightness)));
    }
}

inline void ImagePattern::DumpRenderMode(const RefPtr<OHOS::Ace::NG::ImageRenderProperty>& renderProp)
{
    auto imageRenderMode = renderProp->GetImageRenderMode().value_or(ImageRenderMode::ORIGINAL);
    DumpLog::GetInstance().AddDesc(
        std::string("renderMode: ").append((imageRenderMode == ImageRenderMode::ORIGINAL) ? "Original" : "Template"));
}

inline void ImagePattern::DumpImageRepeat(const RefPtr<OHOS::Ace::NG::ImageRenderProperty>& renderProp)
{
    auto imageRepeat = renderProp->GetImageRepeat().value_or(ImageRepeat::NO_REPEAT);
    DumpLog::GetInstance().AddDesc(std::string("objectRepeat: ").append(GetImageRepeatStr(imageRepeat)));
}

inline void ImagePattern::DumpImageColorFilter(const RefPtr<OHOS::Ace::NG::ImageRenderProperty>& renderProp)
{
    auto imageColorFilter = renderProp->GetColorFilter();
    if (imageColorFilter.has_value()) {
        auto colorFilter = imageColorFilter.value();
        DumpLog::GetInstance().AddDesc(std::string("colorFilter: ").append(GetImageColorFilterStr(colorFilter)));
    }
}

inline void ImagePattern::DumpFillColor(const RefPtr<OHOS::Ace::NG::ImageRenderProperty>& renderProp)
{
    auto fillColor = renderProp->GetSvgFillColor();
    if (fillColor.has_value()) {
        auto color = fillColor.value();
        DumpLog::GetInstance().AddDesc(std::string("fillColor_value: ").append(color.ToSvgFillColorKey()));
    }
}

inline void ImagePattern::DumpDynamicRangeMode(const RefPtr<OHOS::Ace::NG::ImageRenderProperty>& renderProp)
{
    DynamicRangeMode dynamicMode = DynamicRangeMode::STANDARD;
    if (renderProp->HasDynamicMode()) {
        dynamicMode = renderProp->GetDynamicMode().value_or(DynamicRangeMode::STANDARD);
        DumpLog::GetInstance().AddDesc(std::string("dynamicRangeMode: ").append(GetDynamicModeString(dynamicMode)));
    }
}

inline void ImagePattern::DumpMatchTextDirection(const RefPtr<OHOS::Ace::NG::ImageRenderProperty>& renderProp)
{
    auto matchTextDirection = renderProp->GetMatchTextDirection().value_or(false);
    matchTextDirection ? DumpLog::GetInstance().AddDesc("matchTextDirection:true")
                       : DumpLog::GetInstance().AddDesc("matchTextDirection:false");
}

inline void ImagePattern::DumpSmoothEdge(const RefPtr<OHOS::Ace::NG::ImageRenderProperty>& renderProp)
{
    auto smoothEdge = renderProp->GetSmoothEdge();
    if (smoothEdge.has_value()) {
        DumpLog::GetInstance().AddDesc(std::string("edgeAntialiasing: ").append(std::to_string(smoothEdge.value())));
    }
}

inline void ImagePattern::DumpResizable(const RefPtr<OHOS::Ace::NG::ImageRenderProperty>& renderProp)
{
    if (renderProp->HasImageResizableSlice() && renderProp->GetImageResizableSliceValue({}).Valid()) {
        DumpLog::GetInstance().AddDesc(
            std::string("resizable slice: ").append(renderProp->GetImageResizableSliceValue({}).ToString()));
    } else {
        DumpLog::GetInstance().AddDesc(std::string("resizableSlice: Slice is null"));
    }

    auto resizableLattice = renderProp->GetImageResizableLatticeValue(nullptr);
    DumpLog::GetInstance().AddDesc(
        "resizableLattice:" + (resizableLattice ? resizableLattice->DumpToString() : "Lattice is null"));
}

void ImagePattern::DumpBorderRadiusProperties(const RefPtr<OHOS::Ace::NG::ImageRenderProperty>& renderProp)
{
    auto needBorderRadius = renderProp->GetNeedBorderRadius().value_or(false);
    needBorderRadius ? DumpLog::GetInstance().AddDesc("needBorderRadius:true")
                     : DumpLog::GetInstance().AddDesc("needBorderRadius:false");

    auto borderRadius = renderProp->GetBorderRadius().value_or(BorderRadiusProperty());
    DumpLog::GetInstance().AddDesc("ImageBorderRadius:" + borderRadius.ToString());

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    if (renderContext->HasBorderRadius()) {
        DumpLog::GetInstance().AddDesc(
            "borderRadius:" + renderContext->GetBorderRadiusValue(BorderRadiusProperty()).ToString());
    } else {
        DumpLog::GetInstance().AddDesc("borderRadius: null");
    }
}

void ImagePattern::DumpInterpolation(const RefPtr<OHOS::Ace::NG::ImageRenderProperty>& renderProp)
{
    auto imageInterpolation = renderProp->GetImageInterpolation().value_or(interpolationDefault_);
    DumpLog::GetInstance().AddDesc("imageInterpolation:" + GetImageInterpolation(imageInterpolation));
}

void ImagePattern::DumpSvgInfo()
{
    DumpLog::GetInstance().AddDesc("---- SVG Related Dump ----");
    DumpLog::GetInstance().AddDesc("Your SVG related log description here");
    auto imageLayoutProperty = GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageLayoutProperty);
    auto imageSourceInfo = imageLayoutProperty->GetImageSourceInfo();
    CHECK_NULL_VOID(imageSourceInfo);
    if (!imageSourceInfo->IsSvg() || !loadingCtx_) {
        return;
    }
    auto imageObject = loadingCtx_->GetImageObject();
    CHECK_NULL_VOID(imageObject);
    DumpLog::GetInstance().AddDesc(std::string("Svg:").append(imageObject->GetDumpInfo()));
}

void ImagePattern::DumpOtherInfo()
{
    DumpLog::GetInstance().AddDesc("---- Image Component (Excluding Layout and Drawing) Other Info Dump ----");
    DumpLog::GetInstance().AddDesc(renderedImageInfo_.ToString());
    syncLoad_ ? DumpLog::GetInstance().AddDesc("syncLoad:true") : DumpLog::GetInstance().AddDesc("syncLoad:false");

    if (loadingCtx_) {
        auto currentLoadImageState = loadingCtx_->GetCurrentLoadingState();
        DumpLog::GetInstance().AddDesc(std::string("currentLoadImageState : ").append(currentLoadImageState));
        DumpLog::GetInstance().AddDesc(
            std::string("rawImageSize: ").append(loadingCtx_->GetOriginImageSize().ToString()));
        DumpLog::GetInstance().AddDesc(std::string("LoadErrorMsg: ").append(loadingCtx_->GetErrorMsg()));
    } else {
        DumpLog::GetInstance().AddDesc(std::string("imageLoadingContext: null"));
    }

    enableDrag_ ? DumpLog::GetInstance().AddDesc("draggable:true") : DumpLog::GetInstance().AddDesc("draggable:false");
    DumpLog::GetInstance().AddDesc(
        std::string("userOrientation: ").append(ConvertOrientationToString(userOrientation_)));
    DumpLog::GetInstance().AddDesc(
        std::string("selfOrientation: ").append(ConvertOrientationToString(selfOrientation_)));
    DumpLog::GetInstance().AddDesc(std::string("enableAnalyzer: ").append(isEnableAnalyzer_ ? "true" : "false"));
    DumpMenmoryNameId();
}

void ImagePattern::DumpMenmoryNameId()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto id = host->GetInspectorId();
    if (id.has_value() && hasSetPixelMapMemoryName_) {
        DumpLog::GetInstance().AddDesc(std::string("PixelMapMemoryName id : ").append(id.value()));
    }
}

void ImagePattern::DumpInfo()
{
    DumpLayoutInfo();
    DumpRenderInfo();
    DumpSvgInfo();
    DumpOtherInfo();
}

void ImagePattern::DumpAdvanceInfo()
{
    auto layoutProp = GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(layoutProp);
    auto src = layoutProp->GetImageSourceInfo().value_or(ImageSourceInfo(""));
    DumpLog::GetInstance().AddDesc(std::string("url: ").append(src.ToString()));
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
    TAG_LOGD(AceLogTag::ACE_IMAGE, "OnConfigurationUpdate, %{public}s-%{public}d",
        imageDfxConfig_.ToStringWithoutSrc().c_str(), loadingCtx_ ? 1 : 0);
    CHECK_NULL_VOID(loadingCtx_);
    auto imageLayoutProperty = GetLayoutProperty<ImageLayoutProperty>();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto src = imageLayoutProperty->GetImageSourceInfo().value_or(ImageSourceInfo(""));
    UpdateInternalResource(src);
    bool needLayout = host->CheckNeedForceMeasureAndLayout() &&
                          imageLayoutProperty->GetVisibility().value_or(VisibleType::VISIBLE) != VisibleType::GONE;
    LoadImage(src, needLayout);
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

std::string ImagePattern::GetSrcTypeToString(SrcType srcType)
{
    static const std::unordered_map<SrcType, std::string> typeMap = { { SrcType::UNSUPPORTED, "unsupported" },
        { SrcType::FILE, "file" }, { SrcType::ASSET, "asset" }, { SrcType::NETWORK, "network" },
        { SrcType::MEMORY, "memory" }, { SrcType::BASE64, "base64" }, { SrcType::INTERNAL, "internal" },
        { SrcType::RESOURCE, "resource" }, { SrcType::DATA_ABILITY, "dataAbility" },
        { SrcType::DATA_ABILITY_DECODED, "dataAbilityDecoded" }, { SrcType::RESOURCE_ID, "resourceId" },
        { SrcType::PIXMAP, "pixmap" }, { SrcType::ASTC, "astc" } };

    auto iter = typeMap.find(srcType);
    if (iter != typeMap.end()) {
        return iter->second;
    }

    return "";
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
    RegisterVisibleAreaChange(true);
}

// As an example
void ImagePattern::SetImageAnalyzerConfig(const ImageAnalyzerConfig& config)
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
    // If the default value is set to false, the SceneBoard memory increases.
    // Therefore the default value is different in the SceneBoard.
    if (container && container->IsSceneBoardWindow()) {
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
        TAG_LOGW(AceLogTag::ACE_IMAGE, "ImageAnimator InvalidIndex-%{public}d-%{public}zu", index, images_.size());
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
    // use the size of first pixelmap when no size is set
    auto&& layoutConstraint = layoutProperty->GetCalcLayoutConstraint();
    if (!layoutConstraint || !layoutConstraint->selfIdealSize.has_value()) {
        CalcSize realSize = { CalcLength(images_[0].pixelMap->GetWidth()),
            CalcLength(images_[0].pixelMap->GetHeight()) };
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
        TAG_LOGW(AceLogTag::ACE_IMAGE, "index error: %{public}d-%{public}zu", index, images_.size());
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
    // use the size of first pixelmap when no size is set
    auto&& layoutConstraint = layoutProperty->GetCalcLayoutConstraint();
    if (!layoutConstraint || !layoutConstraint->selfIdealSize.has_value()) {
        CalcSize realSize = { CalcLength(images_[0].pixelMap->GetWidth()),
            CalcLength(images_[0].pixelMap->GetHeight()) };
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
    CalcSize realSize = { CalcLength(images_[0].pixelMap->GetWidth()), CalcLength(images_[0].pixelMap->GetHeight()) };

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
    auto eventHub = imageFrameNode->GetOrCreateEventHub<ImageEventHub>();
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
                TAG_LOGW(AceLogTag::ACE_IMAGE, "index is invalid");
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
    return imageLayoutProperty->HasImageSourceInfo() &&
           imageLayoutProperty->GetImageSourceInfoValue().GetPixmap() == src;
}

bool ImagePattern::IsFormRender()
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    return pipeline->IsFormRenderExceptDynamicComponent();
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
    isImageReloadNeeded_ = false;
    loadingCtx_.Reset();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (!altImage_) {
        auto rsRenderContext = host->GetRenderContext();
        CHECK_NULL_VOID(rsRenderContext);
        TAG_LOGI(AceLogTag::ACE_IMAGE, "%{public}s, %{private}s ResetImage.",
            imageDfxConfig_.ToStringWithoutSrc().c_str(), imageDfxConfig_.GetImageSrc().c_str());
        rsRenderContext->RemoveContentModifier(contentMod_);
        contentMod_ = nullptr;
    }
    host->SetTrimMemRecycle(false);
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
        TAG_LOGI(AceLogTag::ACE_IMAGE, "%{public}s-%{private}s ResetAltImage",
            imageDfxConfig_.ToStringWithoutSrc().c_str(), imageDfxConfig_.GetImageSrc().c_str());
        rsRenderContext->RemoveContentModifier(contentMod_);
        contentMod_ = nullptr;
    }
}

void ImagePattern::ResetImageAndAlt()
{
    TAG_LOGD(AceLogTag::ACE_IMAGE, "%{public}s-%{private}s ResetImageAlt", imageDfxConfig_.ToStringWithoutSrc().c_str(),
        imageDfxConfig_.GetImageSrc().c_str());
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    if (frameNode->IsInDestroying() && frameNode->IsOnMainTree()) {
        isNeedReset_ = true;
        return;
    }
    image_ = nullptr;
    loadingCtx_ = nullptr;
    srcRect_.Reset();
    dstRect_.Reset();
    altLoadingCtx_ = nullptr;
    altImage_ = nullptr;
    altDstRect_.reset();
    altSrcRect_.reset();
    auto rsRenderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(rsRenderContext);
    rsRenderContext->RemoveContentModifier(contentMod_);
    contentMod_ = nullptr;
    CloseSelectOverlay();
    DestroyAnalyzerOverlay();
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    frameNode->SetTrimMemRecycle(false);
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
            if (!frame || !frame->GetOrCreateEventHub<EventHub>()) {
                continue;
            }
            auto callback = frame->GetOrCreateEventHub<EventHub>()->GetVisibleAreaCallback(true).callback;
            if (callback) {
                callback(visible, ratio);
            }
        }
        TriggerVisibleAreaChangeForChild(childNode, visible, ratio);
    }
}

void ImagePattern::DumpInfo(std::unique_ptr<JsonValue>& json)
{
    DumpLayoutInfo(json);
    DumpRenderInfo(json);
    json->Put("syncLoad", syncLoad_);
    if (loadingCtx_) {
        auto currentLoadImageState = loadingCtx_->GetCurrentLoadingState();
        json->Put("currentLoadImageState", currentLoadImageState.c_str());
        json->Put("rawImageSize", loadingCtx_->GetImageSize().ToString().c_str());
        json->Put("LoadErrorMsg", loadingCtx_->GetErrorMsg().c_str());
    } else {
        json->Put("imageLoadingContext", "null");
    }

    json->Put("draggable", enableDrag_);
    json->Put("enableAnalyzer", isEnableAnalyzer_);
}

void ImagePattern::DumpSimplifyInfo(std::unique_ptr<JsonValue>& json)
{
    DumpInfo(json);
}

void ImagePattern::DumpLayoutInfo(std::unique_ptr<JsonValue>& json)
{
    auto layoutProp = GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(layoutProp);
    auto src = layoutProp->GetImageSourceInfo().value_or(ImageSourceInfo(""));
    json->Put("url", src.ToString().c_str());
    auto altSrc = layoutProp->GetAlt().value_or(ImageSourceInfo(""));
    json->Put("altUrl", altSrc.ToString().c_str());
    auto imageFit = layoutProp->GetImageFit().value_or(ImageFit::COVER);
    json->Put("objectFit", GetImageFitStr(imageFit).c_str());
    auto fitOriginalSize = layoutProp->GetFitOriginalSize().value_or(false);
    json->Put("fitOriginalSize", fitOriginalSize);
    const std::optional<SizeF>& sourceSize = layoutProp->GetSourceSize();
    if (sourceSize.has_value()) {
        json->Put("sourceSize", sourceSize.value().ToString().c_str());
    }
    bool autoResize = layoutProp->GetAutoResize().value_or(autoResizeDefault_);
    json->Put("autoResize", autoResize);
}

void ImagePattern::DumpRenderInfo(std::unique_ptr<JsonValue>& json)
{
    auto renderProp = GetPaintProperty<ImageRenderProperty>();
    CHECK_NULL_VOID(renderProp);
    auto imageRenderMode = renderProp->GetImageRenderMode().value_or(ImageRenderMode::ORIGINAL);
    json->Put("renderMode", (imageRenderMode == ImageRenderMode::ORIGINAL) ? "Original" : "Template");
    auto imageRepeat = renderProp->GetImageRepeat().value_or(ImageRepeat::NO_REPEAT);
    json->Put("objectRepeat", GetImageRepeatStr(imageRepeat).c_str());
    auto imageColorFilter = renderProp->GetColorFilter();
    if (imageColorFilter.has_value()) {
        auto colorFilter = imageColorFilter.value();
        json->Put("colorFilter", GetImageColorFilterStr(colorFilter).c_str());
    }
    auto fillColor = renderProp->GetSvgFillColor();
    if (fillColor.has_value()) {
        auto color = fillColor.value();
        json->Put("fillColor", color.ColorToString().c_str());
    }
    DynamicRangeMode dynamicMode = DynamicRangeMode::STANDARD;
    if (renderProp->HasDynamicMode()) {
        dynamicMode = renderProp->GetDynamicMode().value_or(DynamicRangeMode::STANDARD);
        json->Put("dynamicRangeMode", GetDynamicModeString(dynamicMode).c_str());
    }
    auto matchTextDirection = renderProp->GetMatchTextDirection().value_or(false);
    json->Put("matchTextDirection", matchTextDirection);
    auto smoothEdge = renderProp->GetSmoothEdge();
    if (smoothEdge.has_value()) {
        json->Put("edgeAntialiasing", smoothEdge.value());
    }
    auto needBorderRadius = renderProp->GetNeedBorderRadius().value_or(false);
    json->Put("needBorderRadius", needBorderRadius);
    if (renderProp && renderProp->HasImageResizableSlice() && renderProp->GetImageResizableSliceValue({}).Valid()) {
        json->Put("resizable slice", renderProp->GetImageResizableSliceValue({}).ToString().c_str());
    }
    auto imageInterpolation = renderProp->GetImageInterpolation().value_or(interpolationDefault_);
    json->Put("imageInterpolation", GetImageInterpolation(imageInterpolation).c_str());
}

void ImagePattern::DumpAdvanceInfo(std::unique_ptr<JsonValue>& json)
{
    auto layoutProp = GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(layoutProp);
    auto src = layoutProp->GetImageSourceInfo().value_or(ImageSourceInfo(""));
    json->Put("url", src.ToString().c_str());
    json->Put("syncLoad", syncLoad_);
    if (loadingCtx_) {
        auto currentLoadImageState = loadingCtx_->GetCurrentLoadingState();
        json->Put("currentLoadImageState", currentLoadImageState.c_str());
    }
}

void ImagePattern::AddPixelMapToUiManager()
{
    CHECK_NULL_VOID(image_);
    auto pixmap = image_->GetPixelMap();
    CHECK_NULL_VOID(pixmap);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->AddPixelMap(host->GetId(), pixmap);
}

FocusPattern ImagePattern::GetFocusPattern() const
{
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_FOURTEEN)) {
        return { FocusType::NODE, false, FocusStyleType::OUTER_BORDER };
    } else {
        return { FocusType::NODE, false };
    }
}

void ImagePattern::OnActive()
{
    if (status_ == AnimatorStatus::RUNNING && animator_->GetStatus() != Animator::Status::RUNNING) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        if (!animator_->HasScheduler()) {
            auto context = host->GetContextRefPtr();
            if (context) {
                animator_->AttachScheduler(context);
            } else {
                TAG_LOGW(AceLogTag::ACE_IMAGE, "pipeline is null.");
            }
        }
        animator_->Forward();
    }
}

void ImagePattern::OnInActive()
{
    if (status_ == AnimatorStatus::RUNNING) {
        animator_->Pause();
    }
}

void ImagePattern::UpdateImageSourceinfo(const ImageSourceInfo& sourceInfo)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    if (pipelineContext->IsSystmColorChange()) {
        auto imageLayoutProperty = GetLayoutProperty<ImageLayoutProperty>();
        CHECK_NULL_VOID(imageLayoutProperty);
        imageLayoutProperty->UpdateImageSourceInfo(sourceInfo);
    }
}

void ImagePattern::UpdateImageFill(const Color& color)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    if (pipelineContext->IsSystmColorChange()) {
        auto renderProperty = GetPaintProperty<ImageRenderProperty>();
        CHECK_NULL_VOID(renderProperty);
        renderProperty->UpdateSvgFillColor(color);
        auto renderContext = host->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        renderContext->UpdateForegroundColor(color);
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}

void ImagePattern::UpdateImageAlt(const ImageSourceInfo& sourceInfo)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    if (pipelineContext->IsSystmColorChange()) {
        auto imageLayoutProperty = GetLayoutProperty<ImageLayoutProperty>();
        CHECK_NULL_VOID(imageLayoutProperty);
        imageLayoutProperty->UpdateAlt(sourceInfo);
    }
}

void ImagePattern::OnColorModeChange(uint32_t colorMode)
{
    Pattern::OnColorModeChange(colorMode);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    if (host->GetRerenderable()) {
        host->MarkModifyDone();
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }
}
} // namespace OHOS::Ace::NG
