/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_IMAGE_IMAGE_MODEL_NG_CPP
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_IMAGE_IMAGE_MODEL_NG_CPP

#include "core/components_ng/pattern/image/image_model_ng.h"

#include "core/components/common/layout/constants.h"
#include "core/components/image/image_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/image/image_render_property.h"
#include "core/image/image_source_info.h"
#ifndef ACE_UNITTEST
#include "core/components_ng/base/view_abstract.h"
#endif
#include "interfaces/native/node/resource.h"
#include "core/components_ng/pattern/text/span_node.h"

namespace OHOS::Ace::NG {
namespace {
const std::vector<float> DEFAULT_COLOR_FILTER = { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0 };
ImageSourceInfo CreateSourceInfo(const std::shared_ptr<std::string>& src, RefPtr<PixelMap>& pixmap,
    const std::string& bundleName, const std::string& moduleName)
{
#if defined(PIXEL_MAP_SUPPORTED)
    if (pixmap) {
        return ImageSourceInfo(pixmap);
    }
#endif
    return { src, bundleName, moduleName };
}

ImageSourceInfo CreateSourceInfo(
    const std::string& src, RefPtr<PixelMap>& pixmap, const std::string& bundleName, const std::string& moduleName)
{
#if defined(PIXEL_MAP_SUPPORTED)
    if (pixmap) {
        return ImageSourceInfo(pixmap);
    }
#endif
    return { src, bundleName, moduleName };
}
} // namespace

void ImageModelNG::Create(const ImageInfoConfig& imageInfoConfig, RefPtr<PixelMap>& pixMap)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    const std::string& src = imageInfoConfig.src ? *imageInfoConfig.src : "";
    ACE_IMAGE_SCOPED_TRACE("Create[%s][self:%d] [src:%s]", V2::IMAGE_ETS_TAG, nodeId, src.c_str());
    RefPtr<FrameNode> frameNode;
    if (imageInfoConfig.isImageSpan) {
        frameNode = ImageSpanNode::GetOrCreateSpanNode(V2::IMAGE_ETS_TAG,
            nodeId, []() { return AceType::MakeRefPtr<ImagePattern>(); });
    } else {
        frameNode = FrameNode::GetOrCreateFrameNode(
            V2::IMAGE_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<ImagePattern>(); });
    }
    stack->Push(frameNode);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    CHECK_NULL_VOID(pattern);
    if (src.empty() && !pixMap && pattern->GetIsAnimation()) {
        pattern->SetSrcUndefined(true);
        return;
    }

    // set draggable for framenode
    if (!imageInfoConfig.isImageSpan) {
        auto pipeline = frameNode->GetContext();
        CHECK_NULL_VOID(pipeline);
        auto draggable = pipeline->GetDraggable<ImageTheme>();
        if (draggable && !frameNode->IsDraggable()) {
            auto gestureHub = frameNode->GetOrCreateGestureEventHub();
            CHECK_NULL_VOID(gestureHub);
            gestureHub->InitDragDropEvent();
        }
        frameNode->SetDraggable(true);
    }
    auto srcInfo =
        CreateSourceInfo(imageInfoConfig.src, pixMap, imageInfoConfig.bundleName, imageInfoConfig.moduleName);
    srcInfo.SetIsUriPureNumber(imageInfoConfig.isUriPureNumber);

    if (pattern->GetImageType() != ImagePattern::ImageType::BASE) {
        if (pattern->GetHasSizeChanged()) {
            pattern->ResetPictureSize();
        }
        pattern->StopAnimation();
        pattern->ResetImages();
        if (!frameNode->GetChildren().empty()) {
            auto imageFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
            ACE_RESET_NODE_LAYOUT_PROPERTY(ImageLayoutProperty, ImageSourceInfo, imageFrameNode);
            frameNode->RemoveChild(imageFrameNode);
        }
    }
    pattern->SetNeedLoadAlt(true);
    pattern->SetImageType(ImagePattern::ImageType::BASE);

    ACE_UPDATE_LAYOUT_PROPERTY(ImageLayoutProperty, ImageSourceInfo, srcInfo);
}

void ImageModelNG::ResetImage()
{
    auto *stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    RefPtr<FrameNode> frameNode;
    frameNode = FrameNode::GetOrCreateFrameNode(
        V2::IMAGE_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<ImagePattern>(); });
    stack->Push(frameNode);
    ImageSourceInfo sourceInfo("");
    sourceInfo.SetIsFromReset(true);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ImageLayoutProperty, ImageSourceInfo, sourceInfo, frameNode);
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetNeedLoadAlt(false);
    pattern->ResetImageAndAlt();
    if (pattern->GetImageType() == ImagePattern::ImageType::ANIMATION) {
        if (pattern->GetHasSizeChanged()) {
            pattern->ResetPictureSize();
        }
        pattern->StopAnimation();
        pattern->ResetImages();
        if (!frameNode->GetChildren().empty()) {
            auto imageFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
            ACE_RESET_NODE_LAYOUT_PROPERTY(ImageLayoutProperty, ImageSourceInfo, imageFrameNode);
            frameNode->RemoveChild(imageFrameNode);
        }
        pattern->SetImageType(ImagePattern::ImageType::BASE);
    }
}

void ImageModelNG::ResetImage(FrameNode* frameNode)
{
    ImageSourceInfo sourceInfo("");
    sourceInfo.SetIsFromReset(true);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ImageLayoutProperty, ImageSourceInfo, sourceInfo, frameNode);
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetNeedLoadAlt(false);
    pattern->ResetImageAndAlt();
}

void ImageModelNG::SetInitialSrc(FrameNode *frameNode, const std::string &src, const std::string &bundleName,
    const std::string &moduleName, bool isUriPureNumber)
{
    auto srcInfo = ImageSourceInfo{ src, bundleName, moduleName };
    srcInfo.SetIsUriPureNumber(isUriPureNumber);

    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ImageLayoutProperty, ImageSourceInfo, srcInfo, frameNode);
}

void ImageModelNG::SetInitialPixelMap(FrameNode* frameNode, RefPtr<PixelMap>& pixMap)
{
    auto srcInfo = ImageSourceInfo(pixMap);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ImageLayoutProperty, ImageSourceInfo, srcInfo, frameNode);
}

void ImageModelNG::CreateAnimation(const std::vector<ImageProperties>& imageList, int32_t duration, int32_t iteration)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::IMAGE_ETS_TAG, nodeId);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::IMAGE_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<ImagePattern>(); });
    CHECK_NULL_VOID(frameNode);
    if (frameNode->GetChildren().empty()) {
        auto imageNode = FrameNode::CreateFrameNode(
            V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
        CHECK_NULL_VOID(imageNode);
        auto imageLayoutProperty = AceType::DynamicCast<ImageLayoutProperty>(imageNode->GetLayoutProperty());
        CHECK_NULL_VOID(imageLayoutProperty);
        imageLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
        frameNode->GetLayoutProperty()->UpdateAlignment(Alignment::TOP_LEFT);
        frameNode->AddChild(imageNode);
    }
    stack->Push(frameNode);

    auto pattern = frameNode->GetPattern<ImagePattern>();
    CHECK_NULL_VOID(pattern);
    if (!pattern->GetIsAnimation()) {
        auto castImageLayoutProperty = frameNode->GetLayoutPropertyPtr<ImageLayoutProperty>();
        CHECK_NULL_VOID(castImageLayoutProperty);
        castImageLayoutProperty->Reset();
        auto castImageRenderProperty = frameNode->GetPaintPropertyPtr<ImageRenderProperty>();
        CHECK_NULL_VOID(castImageRenderProperty);
        castImageRenderProperty->Reset();
        pattern->ResetImageAndAlt();
        pattern->ResetImageProperties();
    }
    // set draggable for framenode
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto draggable = pipeline->GetDraggable<ImageTheme>();
    if (draggable && !frameNode->IsDraggable()) {
        auto gestureHub = frameNode->GetOrCreateGestureEventHub();
        CHECK_NULL_VOID(gestureHub);
        gestureHub->InitDragDropEvent();
    }
    frameNode->SetDraggable(draggable);
    pattern->SetSrcUndefined(false);
    pattern->StopAnimation();
    pattern->SetImageType(ImagePattern::ImageType::ANIMATION);
    std::vector<ImageProperties> images = imageList;
    pattern->SetImages(std::move(images));
    pattern->SetDuration(duration);
    pattern->SetIteration(iteration);
    pattern->StartAnimation();
}

RefPtr<FrameNode> ImageModelNG::CreateFrameNode(int32_t nodeId, const std::string& src, RefPtr<PixelMap>& pixMap,
    const std::string& bundleName, const std::string& moduleName, bool isUriPureNumber)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, nodeId, AceType::MakeRefPtr<ImagePattern>());
    CHECK_NULL_RETURN(frameNode, nullptr);
    // set draggable for framenode
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto draggable = pipeline->GetDraggable<ImageTheme>();
    if (draggable && !frameNode->IsDraggable()) {
        auto gestureHub = frameNode->GetOrCreateGestureEventHub();
        CHECK_NULL_RETURN(gestureHub, nullptr);
        gestureHub->InitDragDropEvent();
    }
    frameNode->SetDraggable(draggable);
    auto srcInfo = CreateSourceInfo(src, pixMap, bundleName, moduleName);
    srcInfo.SetIsUriPureNumber(isUriPureNumber);
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, nullptr);
    layoutProperty->UpdateImageSourceInfo(srcInfo);
    return frameNode;
}

void ImageModelNG::SetAlt(const ImageSourceInfo &src)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ImageLayoutProperty, Alt, src);
}

void ImageModelNG::SetSmoothEdge(float value)
{
    ACE_UPDATE_PAINT_PROPERTY(ImageRenderProperty, SmoothEdge, value);
}

void ImageModelNG::SetSmoothEdge(FrameNode *frameNode, float value)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(ImageRenderProperty, SmoothEdge, value, frameNode);
}

void ImageModelNG::SetDynamicRangeMode(DynamicRangeMode dynamicRangeMode)
{
    ACE_UPDATE_PAINT_PROPERTY(ImageRenderProperty, DynamicMode, dynamicRangeMode);
    ACE_UPDATE_RENDER_CONTEXT(DynamicRangeMode, dynamicRangeMode);
}

void ImageModelNG::SetDynamicRangeMode(FrameNode* frameNode, DynamicRangeMode dynamicRangeMode)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(ImageRenderProperty, DynamicMode, dynamicRangeMode, frameNode);
    ACE_UPDATE_NODE_RENDER_CONTEXT(DynamicRangeMode, dynamicRangeMode, frameNode);
}

void ImageModelNG::SetEnhancedImageQuality(AIImageQuality imageQuality)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<ImagePattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetImageQuality(imageQuality);
}

void ImageModelNG::SetEnhancedImageQuality(FrameNode* frameNode, AIImageQuality imageQuality)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<ImagePattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->SetImageQuality(imageQuality);
}

void ImageModelNG::SetBorder(const Border &border) {}

void ImageModelNG::SetBorderRadius(const Dimension& value)
{
    BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(value);
    borderRadius.multiValued = false;
    ACE_UPDATE_PAINT_PROPERTY(ImageRenderProperty, NeedBorderRadius, true);
    ACE_UPDATE_PAINT_PROPERTY(ImageRenderProperty, BorderRadius, borderRadius);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetNeedBorderRadius(true);
}

void ImageModelNG::SetBorderRadius(const std::optional<Dimension>& radiusTopLeft,
    const std::optional<Dimension>& radiusTopRight, const std::optional<Dimension>& radiusBottomLeft,
    const std::optional<Dimension>& radiusBottomRight)
{
    NG::BorderRadiusProperty borderRadius;
    borderRadius.radiusTopLeft = radiusTopLeft;
    borderRadius.radiusTopRight = radiusTopRight;
    borderRadius.radiusBottomLeft = radiusBottomLeft;
    borderRadius.radiusBottomRight = radiusBottomRight;
    borderRadius.multiValued = true;
    ACE_UPDATE_PAINT_PROPERTY(ImageRenderProperty, NeedBorderRadius, true);
    ACE_UPDATE_PAINT_PROPERTY(ImageRenderProperty, BorderRadius, borderRadius);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetNeedBorderRadius(true);
}

void ImageModelNG::SetBorderRadius(const NG::BorderRadiusProperty& borderRadius)
{
    ACE_UPDATE_PAINT_PROPERTY(ImageRenderProperty, NeedBorderRadius, true);
    ACE_UPDATE_PAINT_PROPERTY(ImageRenderProperty, BorderRadius, borderRadius);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetNeedBorderRadius(true);
}

void ImageModelNG::SetBorderRadius(FrameNode *frameNode, const Dimension& value)
{
    BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(value);
    borderRadius.multiValued = false;
    ACE_UPDATE_NODE_PAINT_PROPERTY(ImageRenderProperty, BorderRadius, borderRadius, frameNode);
    ACE_UPDATE_NODE_PAINT_PROPERTY(ImageRenderProperty, NeedBorderRadius, true, frameNode);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetNeedBorderRadius(true);
}

void ImageModelNG::SetBorderRadius(FrameNode* frameNode, const std::optional<Dimension>& radiusTopLeft,
    const std::optional<Dimension>& radiusTopRight, const std::optional<Dimension>& radiusBottomLeft,
    const std::optional<Dimension>& radiusBottomRight)
{
    NG::BorderRadiusProperty borderRadius;
    borderRadius.radiusTopLeft = radiusTopLeft;
    borderRadius.radiusTopRight = radiusTopRight;
    borderRadius.radiusBottomLeft = radiusBottomLeft;
    borderRadius.radiusBottomRight = radiusBottomRight;
    borderRadius.multiValued = true;
    ACE_UPDATE_NODE_PAINT_PROPERTY(ImageRenderProperty, NeedBorderRadius, true, frameNode);
    ACE_UPDATE_NODE_PAINT_PROPERTY(ImageRenderProperty, BorderRadius, borderRadius, frameNode);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetNeedBorderRadius(true);
}

void ImageModelNG::SetBorderRadius(FrameNode* frameNode, const NG::BorderRadiusProperty& borderRadius)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(ImageRenderProperty, NeedBorderRadius, true, frameNode);
    ACE_UPDATE_NODE_PAINT_PROPERTY(ImageRenderProperty, BorderRadius, borderRadius, frameNode);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetNeedBorderRadius(true);
}

void ImageModelNG::SetBackBorder()
{
    ACE_UPDATE_PAINT_PROPERTY(ImageRenderProperty, NeedBorderRadius, true);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetNeedBorderRadius(true);
}

void ImageModelNG::SetBackBorder(FrameNode *frameNode)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_PAINT_PROPERTY(ImageRenderProperty, NeedBorderRadius, true, frameNode);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetNeedBorderRadius(true);
}

void ImageModelNG::ResetBackBorder(FrameNode *frameNode)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_PAINT_PROPERTY(ImageRenderProperty, NeedBorderRadius, true, frameNode);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetNeedBorderRadius(false);
}

void ImageModelNG::SetBlur(double blur) {}

void ImageModelNG::SetImageFit(ImageFit value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ImageLayoutProperty, ImageFit, value);
    ACE_UPDATE_PAINT_PROPERTY(ImageRenderProperty, ImageFit, value);
}

void ImageModelNG::SetImageMatrix(const Matrix4 &value)
{
    ACE_UPDATE_PAINT_PROPERTY(ImageRenderProperty, ImageMatrix, value);
}

void ImageModelNG::SetMatchTextDirection(bool value)
{
    ACE_UPDATE_PAINT_PROPERTY(ImageRenderProperty, MatchTextDirection, value);
}

void ImageModelNG::SetFitOriginSize(bool value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ImageLayoutProperty, FitOriginalSize, value);
}

void ImageModelNG::SetOnComplete(std::function<void(const LoadImageSuccessEvent &info)> &&callback)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ImageEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnComplete(std::move(callback));
}

void ImageModelNG::SetOnError(std::function<void(const LoadImageFailEvent &info)> &&callback)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ImageEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnError(std::move(callback));
}

void ImageModelNG::SetSvgAnimatorFinishEvent(std::function<void()>&& callback)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ImageEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnFinish(std::move(callback));
}

void ImageModelNG::SetImageSourceSize(const std::pair<Dimension, Dimension> &size)
{
    SizeF sourceSize =
        SizeF(static_cast<float>(size.first.ConvertToPx()), static_cast<float>(size.second.ConvertToPx()));
    ACE_UPDATE_LAYOUT_PROPERTY(ImageLayoutProperty, SourceSize, sourceSize);
}

void ImageModelNG::SetImageFill(const Color &color)
{
    ACE_UPDATE_PAINT_PROPERTY(ImageRenderProperty, SvgFillColor, color);
    ACE_UPDATE_RENDER_CONTEXT(ForegroundColor, color);
}

void ImageModelNG::SetImageInterpolation(ImageInterpolation interpolation)
{
    ACE_UPDATE_PAINT_PROPERTY(ImageRenderProperty, ImageInterpolation, interpolation);
}

void ImageModelNG::SetImageRepeat(ImageRepeat imageRepeat)
{
    ACE_UPDATE_PAINT_PROPERTY(ImageRenderProperty, ImageRepeat, imageRepeat);
}

void ImageModelNG::SetImageRenderMode(ImageRenderMode imageRenderMode)
{
    ACE_UPDATE_PAINT_PROPERTY(ImageRenderProperty, ImageRenderMode, imageRenderMode);
}

bool ImageModelNG::IsSrcSvgImage()
{
    return false;
}

void ImageModelNG::SetAutoResize(bool autoResize)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ImageLayoutProperty, AutoResize, autoResize);
}

void ImageModelNG::SetSyncMode(bool syncMode)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<ImagePattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSyncLoad(syncMode);
}

void ImageModelNG::SetColorFilterMatrix(const std::vector<float> &matrix)
{
    ACE_UPDATE_PAINT_PROPERTY(ImageRenderProperty, ColorFilter, matrix);
    ACE_RESET_PAINT_PROPERTY(ImageRenderProperty, DrawingColorFilter);
}

void ImageModelNG::SetDrawingColorFilter(RefPtr<DrawingColorFilter> &colorFilter)
{
    ACE_UPDATE_PAINT_PROPERTY(ImageRenderProperty, DrawingColorFilter, colorFilter);
    ACE_RESET_PAINT_PROPERTY(ImageRenderProperty, ColorFilter);
}

void ImageModelNG::SetDraggable(bool draggable)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto gestureHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    if (draggable) {
        if (!frameNode->IsDraggable()) {
            gestureHub->InitDragDropEvent();
        }
    } else {
        gestureHub->RemoveDragEvent();
    }
    CHECK_NULL_VOID(frameNode);
    frameNode->SetCustomerDraggable(draggable);
}

void ImageModelNG::SetOnDragStart(OnDragStartFunc &&onDragStart)
{
#ifndef ACE_UNITTEST
    auto dragStart = [dragStartFunc = std::move(onDragStart)](const RefPtr<OHOS::Ace::DragEvent> &event,
        const std::string &extraParams) -> DragDropInfo {
        auto dragInfo = dragStartFunc(event, extraParams);
        DragDropInfo info;
        info.extraInfo = dragInfo.extraInfo;
        info.pixelMap = dragInfo.pixelMap;
        info.customNode = AceType::DynamicCast<UINode>(dragInfo.node);
        return info;
    };
    ViewAbstract::SetOnDragStart(std::move(dragStart));
#endif
}

void ImageModelNG::SetOnDragEnter(OnDragDropFunc &&onDragEnter) {}

void ImageModelNG::SetOnDragLeave(OnDragDropFunc &&onDragLeave) {}

void ImageModelNG::SetOnDragMove(OnDragDropFunc &&onDragMove) {}

void ImageModelNG::SetOnDrop(OnDragDropFunc &&onDrop) {}

void ImageModelNG::SetCopyOption(const CopyOptions &copyOption)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<ImagePattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetCopyOption(copyOption);
}

bool ImageModelNG::UpdateDragItemInfo(DragItemInfo &itemInfo)
{
    return false;
}

void ImageModelNG::InitImage(FrameNode *frameNode, std::string& src)
{
    std::string bundleName;
    std::string moduleName;
    RefPtr<OHOS::Ace::PixelMap> pixMapPtr;
    auto srcInfo = CreateSourceInfo(src, pixMapPtr, bundleName, moduleName);
    srcInfo.SetIsUriPureNumber(false);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ImageLayoutProperty, ImageSourceInfo, srcInfo, frameNode);
}


void ImageModelNG::SetPixelMap(FrameNode* frameNode, void* drawableDescriptor)
{
#ifndef ACE_UNITTEST
    CHECK_NULL_VOID(drawableDescriptor);
    RefPtr<PixelMap> pixelMapPtr = PixelMap::GetFromDrawable(drawableDescriptor);
    auto srcInfo = CreateSourceInfo("", pixelMapPtr, "", "");
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ImageLayoutProperty, ImageSourceInfo, srcInfo, frameNode);
#endif
}

void ImageModelNG::SetPixelMapArray(FrameNode* frameNode, void* animatedDrawableDescriptor)
{
#ifndef ACE_UNITTEST
    CHECK_NULL_VOID(animatedDrawableDescriptor);
    std::vector<RefPtr<PixelMap>> pixelMaps;
    int32_t duration = -1;
    int32_t iterations = 1;
    if (!PixelMap::GetPxielMapListFromAnimatedDrawable(animatedDrawableDescriptor, pixelMaps, duration, iterations)) {
        return;
    }
    std::vector<ImageProperties> images;
    for (int32_t i = 0; i < static_cast<int32_t>(pixelMaps.size()); i++) {
        ImageProperties image;
        image.pixelMap = pixelMaps[i];
        images.push_back(image);
    }

    if (frameNode->GetChildren().empty()) {
        auto imageNode = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, -1, AceType::MakeRefPtr<ImagePattern>());
        CHECK_NULL_VOID(imageNode);
        auto imageLayoutProperty = AceType::DynamicCast<ImageLayoutProperty>(imageNode->GetLayoutProperty());
        CHECK_NULL_VOID(imageLayoutProperty);
        imageLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
        frameNode->GetLayoutProperty()->UpdateAlignment(Alignment::TOP_LEFT);
        frameNode->AddChild(imageNode);
    }

    auto pattern = AceType::DynamicCast<ImagePattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(pattern);

    pattern->StopAnimation();
    pattern->SetImageType(ImagePattern::ImageType::ANIMATION);
    pattern->SetImages(std::move(images));
    pattern->SetDuration(duration);
    pattern->SetIteration(iterations);
    pattern->StartAnimation();
#endif
}

void ImageModelNG::SetResource(FrameNode* frameNode, void* resource)
{
    auto res = reinterpret_cast<ArkUI_Resource*>(resource);
    CHECK_NULL_VOID(res);
    RefPtr<PixelMap> pixMapPtr;
    auto srcInfo = CreateSourceInfo(res->src, pixMapPtr, res->bundleName, res->moduleName);
    srcInfo.SetIsUriPureNumber(res->resId == -1);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ImageLayoutProperty, ImageSourceInfo, srcInfo, frameNode);
}

void ImageModelNG::SetDrawingColorFilter(FrameNode *frameNode, RefPtr<DrawingColorFilter> &colorFilter)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(ImageRenderProperty, DrawingColorFilter, colorFilter, frameNode);
    ACE_RESET_NODE_PAINT_PROPERTY(ImageRenderProperty, ColorFilter, frameNode);
}

void ImageModelNG::SetCopyOption(FrameNode *frameNode, CopyOptions copyOption)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<ImagePattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->SetCopyOption(copyOption);
}

void ImageModelNG::SetAutoResize(FrameNode *frameNode, bool autoResize)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ImageLayoutProperty, AutoResize, autoResize, frameNode);
}

void ImageModelNG::ResetAutoResize(FrameNode *frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    CHECK_NULL_VOID(imagePattern);
    auto defaultAutoResize = imagePattern->GetDefaultAutoResize();
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ImageLayoutProperty, AutoResize, defaultAutoResize, frameNode);
}

void ImageModelNG::SetResizableSlice(const ImageResizableSlice& slice)
{
    ACE_UPDATE_PAINT_PROPERTY(ImageRenderProperty, ImageResizableSlice, slice);
}

void ImageModelNG::SetResizableSlice(FrameNode *frameNode, const ImageResizableSlice& slice)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(ImageRenderProperty, ImageResizableSlice, slice, frameNode);
}

void ImageModelNG::SetResizableLattice(const RefPtr<DrawingLattice>& lattice)
{
    ACE_UPDATE_PAINT_PROPERTY(ImageRenderProperty, ImageResizableLattice, lattice);
}

void ImageModelNG::SetResizableLattice(FrameNode* frameNode, const RefPtr<DrawingLattice>& lattice)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(ImageRenderProperty, ImageResizableLattice, lattice, frameNode);
}

void ImageModelNG::ResetResizableLattice()
{
    ACE_UPDATE_PAINT_PROPERTY(ImageRenderProperty, ImageResizableLattice, nullptr);
}

void ImageModelNG::ResetResizableLattice(FrameNode *frameNode)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(ImageRenderProperty, ImageResizableLattice, nullptr, frameNode);
}

void ImageModelNG::SetImageRepeat(FrameNode *frameNode, ImageRepeat imageRepeat)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(ImageRenderProperty, ImageRepeat, imageRepeat, frameNode);
}

void ImageModelNG::SetImageRenderMode(FrameNode *frameNode, ImageRenderMode imageRenderMode)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(ImageRenderProperty, ImageRenderMode, imageRenderMode, frameNode);
}

void ImageModelNG::SetImageMatrix(FrameNode *frameNode, const Matrix4 &value)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(ImageRenderProperty, ImageMatrix, value, frameNode);
}

void ImageModelNG::SetImageFit(FrameNode *frameNode, ImageFit value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ImageLayoutProperty, ImageFit, value, frameNode);
    ACE_UPDATE_NODE_PAINT_PROPERTY(ImageRenderProperty, ImageFit, value, frameNode);
}

void ImageModelNG::SetFitOriginSize(FrameNode *frameNode, bool value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ImageLayoutProperty, FitOriginalSize, value, frameNode);
}

void ImageModelNG::SetSyncMode(FrameNode *frameNode, bool syncMode)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<ImagePattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->SetSyncLoad(syncMode);
}

void ImageModelNG::SetImageSourceSize(FrameNode *frameNode, const std::pair<Dimension, Dimension> &size)
{
    SizeF sourceSize =
        SizeF(static_cast<float>(size.first.ConvertToPx()), static_cast<float>(size.second.ConvertToPx()));
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ImageLayoutProperty, SourceSize, sourceSize, frameNode);
}

void ImageModelNG::SetMatchTextDirection(FrameNode *frameNode, bool value)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(ImageRenderProperty, MatchTextDirection, value, frameNode);
}

void ImageModelNG::SetImageFill(FrameNode *frameNode, const Color &color)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(ImageRenderProperty, SvgFillColor, color, frameNode);
    ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColor, color, frameNode);
}

void ImageModelNG::SetAlt(FrameNode *frameNode, const ImageSourceInfo &src)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ImageLayoutProperty, Alt, src, frameNode);
}

void ImageModelNG::SetAltResource(FrameNode* frameNode, void* resource)
{
    CHECK_NULL_VOID(frameNode);
    auto res = reinterpret_cast<ArkUI_Resource*>(resource);
    CHECK_NULL_VOID(res);
    RefPtr<PixelMap> pixMapPtr = nullptr;
    auto srcInfo = CreateSourceInfo(res->src, pixMapPtr, res->bundleName, res->moduleName);
    srcInfo.SetIsUriPureNumber(res->resId == -1);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ImageLayoutProperty, Alt, srcInfo, frameNode);
}

void ImageModelNG::SetAltPixelMap(FrameNode* frameNode, void* pixelMap)
{
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(pixelMap);
    #ifndef ACE_UNITTEST
    RefPtr<PixelMap> pixelMapPtr = PixelMap::GetFromDrawable(pixelMap);
    auto srcInfo = CreateSourceInfo("", pixelMapPtr, "", "");
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ImageLayoutProperty, Alt, srcInfo, frameNode);
    #endif
}

void ImageModelNG::SetImageInterpolation(FrameNode *frameNode, ImageInterpolation interpolation)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(ImageRenderProperty, ImageInterpolation, interpolation, frameNode);
}

void ImageModelNG::ResetImageInterpolation(FrameNode *frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    CHECK_NULL_VOID(imagePattern);
    auto defaultInterpolation = imagePattern->GetDefaultInterpolation();
    ACE_UPDATE_NODE_PAINT_PROPERTY(ImageRenderProperty, ImageInterpolation, defaultInterpolation, frameNode);
}

void ImageModelNG::SetColorFilterMatrix(FrameNode *frameNode, const std::vector<float> &matrix)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(ImageRenderProperty, ColorFilter, matrix, frameNode);
    ACE_RESET_NODE_PAINT_PROPERTY(ImageRenderProperty, DrawingColorFilter, frameNode);
}

void ImageModelNG::SetDraggable(FrameNode *frameNode, bool draggable)
{
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    if (draggable) {
        if (!frameNode->IsDraggable()) {
            gestureHub->InitDragDropEvent();
        }
    } else {
        gestureHub->RemoveDragEvent();
    }
    frameNode->SetCustomerDraggable(draggable);
}

void ImageModelNG::EnableAnalyzer(bool isEnableAnalyzer)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<ImagePattern>();
    CHECK_NULL_VOID(pattern);
    pattern->EnableAnalyzer(isEnableAnalyzer);
}

void ImageModelNG::SetImageAnalyzerConfig(const ImageAnalyzerConfig& config)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<ImagePattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetImageAnalyzerConfig(config);
}

void ImageModelNG::SetImageAnalyzerConfig(void* config)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<ImagePattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetImageAnalyzerConfig(config);
}

void ImageModelNG::SetImageAIOptions(void* options)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<ImagePattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetImageAIOptions(options);
}

bool ImageModelNG::IsSrcSvgImage(FrameNode* frameNode)
{
    return false;
}

void ImageModelNG::SetOnComplete(
    FrameNode* frameNode, std::function<void(const LoadImageSuccessEvent& info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ImageEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnComplete(std::move(callback));
}

void ImageModelNG::SetOnError(FrameNode* frameNode, std::function<void(const LoadImageFailEvent& info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ImageEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnError(std::move(callback));
}

void ImageModelNG::SetOnSvgPlayFinish(FrameNode* frameNode, std::function<void()>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ImageEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnFinish(std::move(callback));
}

void ImageModelNG::SetOnDownloadProgress(FrameNode* frameNode,
    std::function<void(const uint32_t& dlNow, const uint32_t& dlTotal)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    CHECK_NULL_VOID(imagePattern);
    imagePattern->SetOnProgressCallback(std::move(callback));
}

ImageSourceInfo ImageModelNG::GetSrc(FrameNode* frameNode)
{
    ImageSourceInfo defaultImageSourceInfo;
    CHECK_NULL_RETURN(frameNode, defaultImageSourceInfo);
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, defaultImageSourceInfo);
    return layoutProperty->GetImageSourceInfo().value_or(defaultImageSourceInfo);
}

ImageFit ImageModelNG::GetObjectFit(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, ImageFit::COVER);
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, ImageFit::COVER);
    return layoutProperty->GetImageFit().value_or(ImageFit::COVER);
}

ImageInterpolation ImageModelNG::GetInterpolation(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, ImageInterpolation::NONE);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    CHECK_NULL_RETURN(imagePattern, ImageInterpolation::NONE);
    auto defaultInterpolation = imagePattern->GetDefaultInterpolation();
    auto paintProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    CHECK_NULL_RETURN(paintProperty, defaultInterpolation);
    CHECK_NULL_RETURN(paintProperty->GetImagePaintStyle(), defaultInterpolation);
    return paintProperty->GetImagePaintStyle()->GetImageInterpolation().value_or(defaultInterpolation);
}

ImageRepeat ImageModelNG::GetObjectRepeat(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, ImageRepeat::NO_REPEAT);
    auto paintProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    CHECK_NULL_RETURN(paintProperty, ImageRepeat::NO_REPEAT);
    CHECK_NULL_RETURN(paintProperty->GetImagePaintStyle(), ImageRepeat::NO_REPEAT);
    return paintProperty->GetImagePaintStyle()->GetImageRepeat().value_or(ImageRepeat::NO_REPEAT);
}

std::vector<float> ImageModelNG::GetColorFilter(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, DEFAULT_COLOR_FILTER);
    auto paintProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    CHECK_NULL_RETURN(paintProperty, DEFAULT_COLOR_FILTER);
    CHECK_NULL_RETURN(paintProperty->GetImagePaintStyle(), DEFAULT_COLOR_FILTER);
    return paintProperty->GetImagePaintStyle()->GetColorFilter().value_or(DEFAULT_COLOR_FILTER);
}

RefPtr<DrawingColorFilter> ImageModelNG::GetDrawingColorFilter(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    CHECK_NULL_RETURN(paintProperty, nullptr);
    CHECK_NULL_RETURN(paintProperty->GetImagePaintStyle(), nullptr);
    return paintProperty->GetImagePaintStyle()->GetDrawingColorFilter().value_or(nullptr);
}

bool ImageModelNG::GetAutoResize(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, true);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    CHECK_NULL_RETURN(imagePattern, true);
    auto defaultAutoResize = imagePattern->GetDefaultAutoResize();
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, defaultAutoResize);
    CHECK_NULL_RETURN(layoutProperty->GetImageSizeStyle(), defaultAutoResize);
    return layoutProperty->GetImageSizeStyle()->GetAutoResize().value_or(defaultAutoResize);
}

ImageSourceInfo ImageModelNG::GetAlt(FrameNode* frameNode)
{
    ImageSourceInfo defaultImageSourceInfo;
    CHECK_NULL_RETURN(frameNode, defaultImageSourceInfo);
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, defaultImageSourceInfo);
    return layoutProperty->GetAlt().value_or(defaultImageSourceInfo);
}

bool ImageModelNG::GetFitOriginalSize(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    return layoutProperty->GetImageSizeStyle()->GetFitOriginalSize().value_or(false);
}

uint32_t ImageModelNG::GetFillColor(FrameNode *frameNode)
{
    uint32_t errorCode = -1;
    CHECK_NULL_RETURN(frameNode, errorCode);
    auto paintProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    CHECK_NULL_RETURN(paintProperty, errorCode);
    CHECK_NULL_RETURN(paintProperty->GetImagePaintStyle(), errorCode);
    Color color = paintProperty->GetImagePaintStyle()->GetSvgFillColor().value_or(Color());
    return color.GetValue();
}

bool ImageModelNG::GetDraggable(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, false);
    return frameNode->IsDraggable();
}

ImageRenderMode ImageModelNG::GetImageRenderMode(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, ImageRenderMode::ORIGINAL);
    auto paintProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    CHECK_NULL_RETURN(paintProperty, ImageRenderMode::ORIGINAL);
    CHECK_NULL_RETURN(paintProperty->GetImagePaintStyle(), ImageRenderMode::ORIGINAL);
    return paintProperty->GetImagePaintStyle()->GetImageRenderMode().value_or(ImageRenderMode::ORIGINAL);
}

bool ImageModelNG::GetIsAnimation()
{
    auto pattern = GetImagePattern();
    CHECK_NULL_RETURN(pattern, false);
    return pattern->GetIsAnimation();
}

ImagePattern* ImageModelNG::GetImagePattern()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_RETURN(frameNode, nullptr);
    return frameNode->GetPatternPtr<ImagePattern>();
}

ImageResizableSlice ImageModelNG::GetResizableSlice(FrameNode *frameNode)
{
    ImageResizableSlice resizable;
    CHECK_NULL_RETURN(frameNode, resizable);
    auto renderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    CHECK_NULL_RETURN(renderProperty, resizable);
    return renderProperty->GetImageResizableSlice().value_or(resizable);
}

void ImageModelNG::EnableAnalyzer(FrameNode* frameNode, bool isEnableAnalyzer)
{
    CHECK_NULL_VOID(frameNode);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    CHECK_NULL_VOID(imagePattern);
    imagePattern->EnableAnalyzer(isEnableAnalyzer);
}

void ImageModelNG::SetImageAnalyzerConfig(FrameNode* frameNode, void* config)
{
    CHECK_NULL_VOID(frameNode);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    CHECK_NULL_VOID(imagePattern);
    imagePattern->SetImageAnalyzerConfig(config);
}

void ImageModelNG::ResetImageSrc(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    ImageSourceInfo sourceInfo("");
    sourceInfo.SetIsFromReset(true);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ImageLayoutProperty, ImageSourceInfo, sourceInfo, frameNode);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    CHECK_NULL_VOID(pattern);
    pattern->ResetImage();
    if (pattern->GetImageType() == ImagePattern::ImageType::ANIMATION) {
        if (pattern->GetHasSizeChanged()) {
            pattern->ResetPictureSize();
        }
        pattern->StopAnimation();
        pattern->ResetImages();
        if (!frameNode->GetChildren().empty()) {
            auto imageFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
            ACE_RESET_NODE_LAYOUT_PROPERTY(ImageLayoutProperty, ImageSourceInfo, imageFrameNode);
            frameNode->RemoveChild(imageFrameNode);
        }
        pattern->SetImageType(ImagePattern::ImageType::BASE);
    }
}

void ImageModelNG::ResetImageAlt(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    ImageSourceInfo sourceInfo("");
    sourceInfo.SetIsFromReset(true);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ImageLayoutProperty, Alt, sourceInfo, frameNode);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    CHECK_NULL_VOID(pattern);
    pattern->ResetAltImage();
}

void ImageModelNG::SetOrientation(ImageRotateOrientation orientation)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ImageLayoutProperty, ImageRotateOrientation, orientation);
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<ImagePattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetOrientation(orientation);
}

void ImageModelNG::SetOrientation(FrameNode *frameNode, ImageRotateOrientation orientation)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ImageLayoutProperty, ImageRotateOrientation, orientation, frameNode);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetOrientation(orientation);
}
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_IMAGE_IMAGE_MODEL_NG_CPP
