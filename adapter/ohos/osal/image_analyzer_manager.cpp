/*
 * Copyright (C) 2024 Huawei Device Co., Ltd.
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

#include "core/common/ai/image_analyzer_manager.h"

#include "core/common/ai/image_analyzer_adapter.h"
#include "core/common/ai/image_analyzer_mgr.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/video/video_layout_property.h"

namespace OHOS::Ace {

ImageAnalyzerManager::ImageAnalyzerManager(const RefPtr<NG::FrameNode>& frameNode, ImageAnalyzerHolder holder)
    : frameNode_(frameNode), holder_(holder)
{
    imageAnalyzerAdapter_ = std::shared_ptr<ImageAnalyzerAdapter>(CreateImageAnalyzerAdapter());
}

void ImageAnalyzerManager::CreateAnalyzerOverlay(const RefPtr<OHOS::Ace::PixelMap>& pixelMap,
    const NG::OffsetF& offset)
{
    CHECK_NULL_VOID(imageAnalyzerAdapter_);
    void* pixelmapNapiVal = nullptr;
    if (pixelMap) {
        pixelmapNapiVal = imageAnalyzerAdapter_->ConvertPixmapNapi(pixelMap);
    }

    analyzerUIConfig_.holder = holder_;
    if (holder_ != ImageAnalyzerHolder::IMAGE && holder_ != ImageAnalyzerHolder::WEB) {
        analyzerUIConfig_.contentWidth = pixelMap->GetWidth();
        analyzerUIConfig_.contentHeight = pixelMap->GetHeight();
    }

    if (holder_ == ImageAnalyzerHolder::VIDEO_CUSTOM) {
        analyzerUIConfig_.pixelMapWidth = pixelMap->GetWidth();
        analyzerUIConfig_.pixelMapHeight = pixelMap->GetHeight();
        analyzerUIConfig_.overlayOffset = offset;
    }

    RefPtr<NG::UINode> customNode;
    {
        NG::ScopedViewStackProcessor builderViewStackProcessor;
        auto analyzerConfig = imageAnalyzerAdapter_->GetImageAnalyzerConfig();
        ImageAnalyzerMgr::GetInstance().BuildNodeFunc(
            pixelmapNapiVal, analyzerConfig, &analyzerUIConfig_, &overlayData_);
        customNode = NG::ViewStackProcessor::GetInstance()->Finish();
    }
    auto overlayNode = AceType::DynamicCast<NG::FrameNode>(customNode);
    CHECK_NULL_VOID(overlayNode);
    auto node = frameNode_.Upgrade();
    CHECK_NULL_VOID(node);
    node->SetOverlayNode(overlayNode);
    overlayNode->SetParent(AceType::WeakClaim(AceType::RawPtr(node)));
    overlayNode->SetActive(true);
    UpdateAnalyzerOverlayLayout();

    auto renderContext = overlayNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateZIndex(INT32_MAX);
    auto focusHub = overlayNode->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->SetFocusable(false);
    overlayNode->MarkDirtyNode(NG::PROPERTY_UPDATE_MEASURE_SELF);

    isAnalyzerOverlayBuild_ = true;
    CHECK_NULL_VOID(analyzerUIConfig_.onAnalyzed);
    (analyzerUIConfig_.onAnalyzed.value())(ImageAnalyzerState::FINISHED);
    analyzerUIConfig_.onAnalyzed = std::nullopt;
}

void ImageAnalyzerManager::CreateMovingPhotoAnalyzerOverlay(const RefPtr<OHOS::Ace::PixelMap>& pixelMap,
    MovingPhotoAnalyzerInfo info)
{
    CHECK_NULL_VOID(imageAnalyzerAdapter_);
    void* pixelmapNapiVal = nullptr;

    CHECK_NULL_VOID(pixelMap);
    pixelmapNapiVal = imageAnalyzerAdapter_->ConvertPixmapNapi(pixelMap);
    analyzerUIConfig_.holder = holder_;
    analyzerUIConfig_.contentWidth = info.contentWidth;
    analyzerUIConfig_.contentHeight = info.contentHeight;
    analyzerUIConfig_.pixelMapWidth = pixelMap->GetWidth();
    analyzerUIConfig_.pixelMapHeight = pixelMap->GetHeight();

    RefPtr<NG::UINode> customNode;
    {
        NG::ScopedViewStackProcessor builderViewStackProcessor;
        auto analyzerConfig = imageAnalyzerAdapter_->GetImageAnalyzerConfig();
        ImageAnalyzerMgr::GetInstance().BuildNodeFunc(info.uri, pixelmapNapiVal,
            info.frameTimestamp, analyzerConfig, &analyzerUIConfig_, &overlayData_);
        customNode = NG::ViewStackProcessor::GetInstance()->Finish();
    }
    auto overlayNode = AceType::DynamicCast<NG::FrameNode>(customNode);
    CHECK_NULL_VOID(overlayNode);
    auto node = frameNode_.Upgrade();
    CHECK_NULL_VOID(node);
    node->SetOverlayNode(overlayNode);
    overlayNode->SetParent(AceType::WeakClaim(AceType::RawPtr(node)));
    overlayNode->SetActive(true);
    UpdateAnalyzerOverlayLayout();

    auto renderContext = overlayNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateZIndex(INT32_MAX);
    overlayNode->MarkDirtyNode(NG::PROPERTY_UPDATE_MEASURE_SELF);

    isAnalyzerOverlayBuild_ = true;
    CHECK_NULL_VOID(analyzerUIConfig_.onAnalyzed);
    (analyzerUIConfig_.onAnalyzed.value())(ImageAnalyzerState::FINISHED);
    analyzerUIConfig_.onAnalyzed = std::nullopt;
}

void ImageAnalyzerManager::UpdateAnalyzerOverlay(const RefPtr<OHOS::Ace::PixelMap>& pixelMap,
    const NG::OffsetF& offset)
{
    if (!isAnalyzerOverlayBuild_) {
        return;
    }

    auto node = frameNode_.Upgrade();
    CHECK_NULL_VOID(node);
    if (holder_ == ImageAnalyzerHolder::IMAGE) {
        auto imagePattern = AceType::DynamicCast<NG::ImagePattern>(node->GetPattern());
        CHECK_NULL_VOID(imagePattern);
        if (!imagePattern->hasSceneChanged()) {
            return;
        }
    }

    CHECK_NULL_VOID(pixelMap);
    if (holder_ == ImageAnalyzerHolder::VIDEO_CUSTOM) {
        analyzerUIConfig_.pixelMapWidth = pixelMap->GetWidth();
        analyzerUIConfig_.pixelMapHeight = pixelMap->GetHeight();
        analyzerUIConfig_.overlayOffset = offset;
    }

    if (holder_ != ImageAnalyzerHolder::IMAGE) {
        analyzerUIConfig_.contentWidth = pixelMap->GetWidth();
        analyzerUIConfig_.contentHeight = pixelMap->GetHeight();
    }

    CHECK_NULL_VOID(imageAnalyzerAdapter_);
    auto pixelmapNapiVal = imageAnalyzerAdapter_->ConvertPixmapNapi(pixelMap);
    auto overlayNode = node->GetOverlayNode();
    CHECK_NULL_VOID(overlayNode);
    auto analyzerConfig = imageAnalyzerAdapter_->GetImageAnalyzerConfig();
    ImageAnalyzerMgr::GetInstance().UpdateImage(&overlayData_, pixelmapNapiVal, analyzerConfig, &analyzerUIConfig_);
    overlayNode->MarkDirtyNode(NG::PROPERTY_UPDATE_MEASURE_SELF);
}

void ImageAnalyzerManager::UpdateMovingPhotoAnalyzerOverlay(const RefPtr<OHOS::Ace::PixelMap>& pixelMap,
    MovingPhotoAnalyzerInfo info)
{
    if (!isAnalyzerOverlayBuild_) {
        return;
    }

    auto node = frameNode_.Upgrade();
    CHECK_NULL_VOID(node);
    if (holder_ == ImageAnalyzerHolder::IMAGE) {
        auto imagePattern = AceType::DynamicCast<NG::ImagePattern>(node->GetPattern());
        CHECK_NULL_VOID(imagePattern);
        if (!imagePattern->hasSceneChanged()) {
            return;
        }
    }

    CHECK_NULL_VOID(pixelMap);
    analyzerUIConfig_.holder = holder_;
    analyzerUIConfig_.contentWidth = info.contentWidth;
    analyzerUIConfig_.contentHeight = info.contentHeight;
    analyzerUIConfig_.pixelMapWidth = pixelMap->GetWidth();
    analyzerUIConfig_.pixelMapHeight = pixelMap->GetHeight();

    CHECK_NULL_VOID(imageAnalyzerAdapter_);
    auto pixelmapNapiVal = imageAnalyzerAdapter_->ConvertPixmapNapi(pixelMap);
    auto overlayNode = node->GetOverlayNode();
    CHECK_NULL_VOID(overlayNode);
    auto analyzerConfig = imageAnalyzerAdapter_->GetImageAnalyzerConfig();
    ImageAnalyzerMgr::GetInstance().UpdateImage(&overlayData_, info.uri, pixelmapNapiVal,
        info.frameTimestamp, analyzerConfig, &analyzerUIConfig_);
    overlayNode->MarkDirtyNode(NG::PROPERTY_UPDATE_MEASURE_SELF);
}

void ImageAnalyzerManager::DestroyAnalyzerOverlay()
{
    ReleaseImageAnalyzer();
    
    if (!isAnalyzerOverlayBuild_) {
        return;
    }
    auto node = frameNode_.Upgrade();
    CHECK_NULL_VOID(node);
    auto overlayNode = node->GetOverlayNode();
    CHECK_NULL_VOID(overlayNode);
    node->SetOverlayNode(RefPtr<NG::FrameNode>());

    isAnalyzerOverlayBuild_ = false;
    CHECK_NULL_VOID(analyzerUIConfig_.onAnalyzed);
    (analyzerUIConfig_.onAnalyzed.value())(ImageAnalyzerState::STOPPED);
    analyzerUIConfig_.onAnalyzed = std::nullopt;

    napi_value nullValue = nullptr;
    CHECK_NULL_VOID(imageAnalyzerAdapter_);
    imageAnalyzerAdapter_->SetImageAnalyzerConfig(nullValue);
}

bool ImageAnalyzerManager::IsSupportImageAnalyzerFeature()
{
    auto node = frameNode_.Upgrade();
    CHECK_NULL_RETURN(node, false);
    auto eventHub = node->GetOrCreateEventHub<NG::EventHub>();
    CHECK_NULL_RETURN(eventHub, false);
    if (!eventHub->IsEnabled()) {
        return false;
    }

    bool hasObscured = false;
    if (node->GetRenderContext()->GetObscured().has_value()) {
        auto obscuredReasons = node->GetRenderContext()->GetObscured().value();
        hasObscured = std::any_of(obscuredReasons.begin(), obscuredReasons.end(),
            [](const auto& reason) { return reason == ObscuredReasons::PLACEHOLDER; });
        if (hasObscured) {
            return false;
        }
    }

    if (holder_ == ImageAnalyzerHolder::IMAGE) {
        auto imageRenderProperty = node->GetPaintProperty<NG::ImageRenderProperty>();
        CHECK_NULL_RETURN(imageRenderProperty, false);
        ImageRepeat repeat = imageRenderProperty->GetImageRepeat().value_or(ImageRepeat::NO_REPEAT);
        if (repeat != ImageRepeat::NO_REPEAT) {
            return false;
        }
    }

    return ImageAnalyzerMgr::GetInstance().IsImageAnalyzerSupported();
}

bool ImageAnalyzerManager::IsOverlayCreated()
{
    return isAnalyzerOverlayBuild_;
}

void ImageAnalyzerManager::UpdateAnalyzerOverlayLayout()
{
    auto node = frameNode_.Upgrade();
    CHECK_NULL_VOID(node);
    auto layoutProperty = node->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto padding = layoutProperty->CreatePaddingAndBorder();
    auto overlayNode = node->GetOverlayNode();
    CHECK_NULL_VOID(overlayNode);
    auto overlayLayoutProperty = overlayNode->GetLayoutProperty();
    CHECK_NULL_VOID(overlayLayoutProperty);
    overlayLayoutProperty->UpdateMeasureType(NG::MeasureType::MATCH_PARENT);
    overlayLayoutProperty->UpdateAlignment(Alignment::TOP_LEFT);
    if (NeedUpdateOverlayOffset()) {
        overlayLayoutProperty->SetOverlayOffset(Dimension(padding.Offset().GetX()),
                                                Dimension(padding.Offset().GetY()));
        if (holder_ == ImageAnalyzerHolder::IMAGE) {
            auto renderContext = overlayNode->GetRenderContext();
            CHECK_NULL_VOID(renderContext);
            renderContext->SetRenderFrameOffset({ -padding.Offset().GetX(), -padding.Offset().GetY() });
        }
    }
}

void ImageAnalyzerManager::UpdateAnalyzerUIConfig(const RefPtr<NG::GeometryNode>& geometryNode,
    const PixelMapInfo& info)
{
    CHECK_NULL_VOID(geometryNode);
    auto node = frameNode_.Upgrade();
    CHECK_NULL_VOID(node);
    bool isUIConfigUpdate = false;

    auto layoutProps = node->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProps);
    if (holder_ == ImageAnalyzerHolder::IMAGE) {
        auto props = DynamicCast<NG::ImageLayoutProperty>(layoutProps);
        CHECK_NULL_VOID(props);
        if (analyzerUIConfig_.imageFit != props->GetImageFit().value_or(ImageFit::COVER)) {
            analyzerUIConfig_.imageFit = props->GetImageFit().value_or(ImageFit::COVER);
            isUIConfigUpdate = true;
        }
    }
    
    if (holder_ == ImageAnalyzerHolder::VIDEO_CUSTOM) {
        isUIConfigUpdate = UpdateVideoConfig(info);
    } else {
        auto padding = layoutProps->CreatePaddingAndBorder();
        float paddingWidth = 0.0f;
        float paddingHeight = 0.0f;
        if (holder_ == ImageAnalyzerHolder::IMAGE || holder_ == ImageAnalyzerHolder::XCOMPONENT) {
            paddingWidth = padding.left.value_or(0) + padding.right.value_or(0);
            paddingHeight = padding.top.value_or(0) + padding.bottom.value_or(0);
        }
        NG::SizeF frameSize = geometryNode->GetFrameSize();
        bool shouldUpdateSize = analyzerUIConfig_.contentWidth != frameSize.Width() - paddingWidth ||
                                analyzerUIConfig_.contentHeight != frameSize.Height() - paddingHeight;
        if (shouldUpdateSize) {
            analyzerUIConfig_.contentWidth = frameSize.Width() - paddingWidth;
            analyzerUIConfig_.contentHeight = frameSize.Height()- paddingHeight;
            isUIConfigUpdate = true;
        }
    }

    auto renderContext = node->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto transformMat = renderContext->GetTransformMatrixValue(Matrix4::CreateIdentity());
    if (!(analyzerUIConfig_.transformMat == transformMat)) {
        analyzerUIConfig_.transformMat = transformMat;
        isUIConfigUpdate = true;
    }

    if (isUIConfigUpdate) {
        ImageAnalyzerMgr::GetInstance().UpdateInnerConfig(&overlayData_, &analyzerUIConfig_);
    }
}

bool ImageAnalyzerManager::UpdateVideoConfig(const PixelMapInfo& info)
{
    bool shouldUpdateFit = false;
    auto node = frameNode_.Upgrade();
    CHECK_NULL_RETURN(node, false);
    auto layoutProps = node->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProps, false);
    auto videoProps = DynamicCast<NG::VideoLayoutProperty>(layoutProps);
    if (analyzerUIConfig_.imageFit != videoProps->GetObjectFitValue(ImageFit::COVER)) {
        analyzerUIConfig_.imageFit = videoProps->GetObjectFitValue(ImageFit::COVER);
        shouldUpdateFit = true;
    }

    bool shouldUpdateSize = analyzerUIConfig_.contentWidth != info.width ||
                            analyzerUIConfig_.contentHeight != info.height ||
                            analyzerUIConfig_.overlayOffset != info.overlayOffset;
    if (shouldUpdateSize) {
        analyzerUIConfig_.UpdateFromInfo(info);
    }
    return shouldUpdateFit || shouldUpdateSize;
}

void ImageAnalyzerManager::SetImageAnalyzerConfig(void* config)
{
    CHECK_NULL_VOID(imageAnalyzerAdapter_);
    bool hasConfig = imageAnalyzerAdapter_->HasImageAnalyzerConfig();
    if (hasConfig) {
        return;
    }
    imageAnalyzerAdapter_->SetImageAnalyzerConfig(config);
    auto analyzerConfig = imageAnalyzerAdapter_->GetImageAnalyzerConfig();
    if (isAnalyzerOverlayBuild_) {
        ImageAnalyzerMgr::GetInstance().UpdateConfig(&overlayData_, analyzerConfig);
    }
}

void ImageAnalyzerManager::SetImageAIOptions(void* options)
{
    CHECK_NULL_VOID(imageAnalyzerAdapter_);
    imageAnalyzerAdapter_->SetImageAnalyzerConfig(options, true);
    auto analyzerConfig = imageAnalyzerAdapter_->GetImageAnalyzerConfig();
    if (isAnalyzerOverlayBuild_) {
        ImageAnalyzerMgr::GetInstance().UpdateConfig(&overlayData_, analyzerConfig);
    }
}

void ImageAnalyzerManager::SetImageAnalyzerCallback(OnAnalyzedCallback& callback)
{
    analyzerUIConfig_.onAnalyzed = callback;
}

void ImageAnalyzerManager::ReleaseImageAnalyzer()
{
    if (isAnalyzerOverlayBuild_) {
        ImageAnalyzerMgr::GetInstance().Release(&overlayData_);
    }
}

void ImageAnalyzerManager::UpdatePressOverlay(const RefPtr<OHOS::Ace::PixelMap>& pixelMap, int offsetX, int offsetY,
    int rectWidth, int rectHeight, int pointX, int pointY, OnTextSelectedCallback callback)
{
    analyzerUIConfig_.overlayOffset.SetX(offsetX);
    analyzerUIConfig_.overlayOffset.SetY(offsetY);
    if (rectWidth > 0 && rectHeight > 0) {
        analyzerUIConfig_.touchInfo.touchPoint.x = 1.0 * pointX / rectWidth * pixelMap->GetWidth();
        analyzerUIConfig_.touchInfo.touchPoint.y = 1.0 * pointY / rectHeight * pixelMap->GetHeight();
    }
    analyzerUIConfig_.touchInfo.touchType = TouchType::DOWN;
    analyzerUIConfig_.selectedStatus = Status::SELECTED;
    analyzerUIConfig_.menuStatus = Status::MENU_SHOW;
    if (!analyzerUIConfig_.onTextSelected) {
        analyzerUIConfig_.onTextSelected = std::move(callback);
    }
    if (pixelMap && imageAnalyzerAdapter_) {
        analyzerUIConfig_.contentWidth = rectWidth;
        analyzerUIConfig_.contentHeight = rectHeight;
        analyzerUIConfig_.pixelMapWidth = pixelMap->GetWidth();
        analyzerUIConfig_.pixelMapHeight = pixelMap->GetHeight();
        analyzerUIConfig_.pixelmapNapiVal = imageAnalyzerAdapter_->ConvertPixmapNapi(pixelMap);
    }
    ImageAnalyzerMgr::GetInstance().UpdatePressOverlay(&overlayData_, &analyzerUIConfig_);
    analyzerUIConfig_.pixelmapNapiVal = nullptr;
}

void ImageAnalyzerManager::UpdateOverlayTouchInfo(int touchPointX, int touchPointY, TouchType touchType)
{
    analyzerUIConfig_.touchInfo.touchPoint.x = touchPointX - analyzerUIConfig_.overlayOffset.GetX();
    analyzerUIConfig_.touchInfo.touchPoint.y = touchPointY - analyzerUIConfig_.overlayOffset.GetY();
    analyzerUIConfig_.touchInfo.touchType = touchType;
    ImageAnalyzerMgr::GetInstance().UpdatePressOverlay(&overlayData_, &analyzerUIConfig_);
}

void ImageAnalyzerManager::UpdateOverlayStatus(bool status, int offsetX, int offsetY, int rectWidth, int rectHeight)
{
    if (status) {
        analyzerUIConfig_.overlayOffset.SetX(offsetX);
        analyzerUIConfig_.overlayOffset.SetY(offsetY);
        analyzerUIConfig_.contentWidth = rectWidth;
        analyzerUIConfig_.contentHeight = rectHeight;
        analyzerUIConfig_.selectedStatus = Status::SELECTED;
        analyzerUIConfig_.menuStatus = Status::MENU_SHOW;
    } else {
        analyzerUIConfig_.selectedStatus = Status::UNSELECTED;
        analyzerUIConfig_.menuStatus = Status::MENU_HIDE;
    }
    ImageAnalyzerMgr::GetInstance().UpdateOverlayStatus(&overlayData_, &analyzerUIConfig_);
}

void ImageAnalyzerManager::UpdateAIButtonConfig(AIButtonConfig config)
{
    CHECK_NULL_VOID(isAnalyzerOverlayBuild_);
    ImageAnalyzerMgr::GetInstance().UpdateAIButtonConfig(&overlayData_, &config);
}

void ImageAnalyzerManager::UpdateKeyEvent(KeyEvent keyEvent)
{
    CHECK_NULL_VOID(isAnalyzerOverlayBuild_);
    ImageAnalyzerMgr::GetInstance().UpdateKeyEvent(&overlayData_, keyEvent.rawKeyEvent.get());
}

void ImageAnalyzerManager::UpdateOverlayActiveStatus(bool status)
{
    CHECK_NULL_VOID(isAnalyzerOverlayBuild_);
    ImageAnalyzerMgr::GetInstance().UpdateOverlayActiveStatus(&overlayData_, status);
}

bool ImageAnalyzerManager::NeedUpdateOverlayOffset()
{
    return holder_ == ImageAnalyzerHolder::IMAGE ||
           holder_ == ImageAnalyzerHolder::VIDEO_CUSTOM ||
           holder_ == ImageAnalyzerHolder::XCOMPONENT;
}

void ImageAnalyzerManager::SetNotifySelectedCallback(
    OnNotifySelectedStatusCallback&& callback)
{
    analyzerUIConfig_.onNotifySelectedStatus = std::move(callback);
}

void ImageAnalyzerManager::SetOnCanPlayCallback(
    OnCanPlayCallback&& onCanPlay)
{
    analyzerUIConfig_.onCanPlay = std::move(onCanPlay);
}
} // namespace OHOS::Ace