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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_IMAGE_IMAGE_MODEL_STATIC_CPP
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_IMAGE_IMAGE_MODEL_STATIC_CPP

#include "core/components_ng/pattern/image/image_model_static.h"

#include "interfaces/native/node/resource.h"

#include "base/image/image_defines.h"
#include "core/components/common/layout/constants.h"
#include "core/components/image/image_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/image/image_render_property.h"
#include "core/components_ng/pattern/text/span_node.h"
#include "core/drawable/animated_drawable_descriptor.h"
#include "core/drawable/layered_drawable_descriptor.h"
#include "core/drawable/pixel_map_drawable_descriptor.h"
#include "core/image/image_source_info.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t LAYERED_TYPE = 1;
constexpr int32_t ANIMATED_TYPE = 2;
constexpr int32_t PIXELMAP_TYPE = 3;
} // namespace

void ImageModelStatic::SetSrc(FrameNode* frameNode, const std::optional<ImageSourceInfo>& info)
{
    CHECK_NULL_VOID(frameNode);
    if (info) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ImageLayoutProperty, ImageSourceInfo, info.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(ImageLayoutProperty, ImageSourceInfo, frameNode);
    }
}

void ImageModelStatic::SetSmoothEdge(FrameNode* frameNode, const std::optional<float>& value)
{
    CHECK_NULL_VOID(frameNode);
    if (value) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ImageRenderProperty, SmoothEdge, *value, frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(ImageRenderProperty, SmoothEdge, frameNode);
    }
}

void ImageModelStatic::SetDynamicRangeMode(
    FrameNode* frameNode, const std::optional<DynamicRangeMode>& dynamicRangeMode)
{
    CHECK_NULL_VOID(frameNode);
    if (dynamicRangeMode) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ImageRenderProperty, DynamicMode, dynamicRangeMode.value(), frameNode);
        ACE_UPDATE_NODE_RENDER_CONTEXT(DynamicRangeMode, dynamicRangeMode.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(ImageRenderProperty, DynamicMode, frameNode);
        ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, DynamicRangeMode, frameNode);
    }
}

void ImageModelStatic::SetCopyOption(FrameNode* frameNode, const std::optional<CopyOptions>& copyOption)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<ImagePattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->SetCopyOption(copyOption.value_or(CopyOptions::None));
}

void ImageModelStatic::SetImageRepeat(FrameNode* frameNode, const std::optional<ImageRepeat>& imageRepeat)
{
    CHECK_NULL_VOID(frameNode);
    if (imageRepeat) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ImageRenderProperty, ImageRepeat, imageRepeat.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(ImageRenderProperty, ImageRepeat, frameNode);
    }
}

void ImageModelStatic::SetImageRenderMode(FrameNode* frameNode, const std::optional<ImageRenderMode>& imageRenderMode)
{
    CHECK_NULL_VOID(frameNode);
    if (imageRenderMode) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ImageRenderProperty, ImageRenderMode, *imageRenderMode, frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(ImageRenderProperty, ImageRenderMode, frameNode);
    }
}

void ImageModelStatic::SetImageMatrix(FrameNode* frameNode, const std::optional<Matrix4>& value)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(ImageRenderProperty, ImageMatrix,
        value.value_or(Matrix4::CreateIdentity()), frameNode);
}

void ImageModelStatic::SetImageFit(FrameNode* frameNode, const std::optional<ImageFit>& value)
{
    CHECK_NULL_VOID(frameNode);
    if (value) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ImageLayoutProperty, ImageFit, value.value(), frameNode);
        ACE_UPDATE_NODE_PAINT_PROPERTY(ImageRenderProperty, ImageFit, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(ImageLayoutProperty, ImageFit, frameNode);
        ACE_RESET_NODE_PAINT_PROPERTY(ImageRenderProperty, ImageFit, frameNode);
    }
}

void ImageModelStatic::SetImageSourceSize(
    FrameNode* frameNode, const std::optional<std::pair<Dimension, Dimension>>& size)
{
    CHECK_NULL_VOID(frameNode);
    if (size) {
        SizeF sourceSize =
            SizeF(static_cast<float>(size->first.ConvertToPx()), static_cast<float>(size->second.ConvertToPx()));
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ImageLayoutProperty, SourceSize, sourceSize, frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(ImageLayoutProperty, SourceSize, frameNode);
    }
}

void ImageModelStatic::SetImageFill(FrameNode* frameNode, const std::optional<Color>& color)
{
    CHECK_NULL_VOID(frameNode);
    if (color) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ImageRenderProperty, SvgFillColor, color.value(), frameNode);
        ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColor, color.value(), frameNode);
    } else {
        auto pipelineContext = frameNode->GetContext();
        CHECK_NULL_VOID(pipelineContext);
        auto theme = pipelineContext->GetTheme<ImageTheme>();
        CHECK_NULL_VOID(theme);
        auto fillColor = theme->GetFillColor();
        ACE_UPDATE_NODE_PAINT_PROPERTY(ImageRenderProperty, SvgFillColor, fillColor, frameNode);
        ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColor, fillColor, frameNode);
    }
}

void ImageModelStatic::SetAlt(FrameNode* frameNode, const std::optional<ImageSourceInfo>& src)
{
    CHECK_NULL_VOID(frameNode);
    if (src) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ImageLayoutProperty, Alt, src.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(ImageLayoutProperty, Alt, frameNode);
    }
}

void ImageModelStatic::SetImageInterpolation(
    FrameNode* frameNode, const std::optional<ImageInterpolation>& interpolation)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_PAINT_PROPERTY(
        ImageRenderProperty, ImageInterpolation, interpolation.value_or(ImageInterpolation::NONE), frameNode);
}

void ImageModelStatic::SetOrientation(FrameNode* frameNode, const std::optional<ImageRotateOrientation>& orientation)
{
    const auto orientationValue = orientation.value_or(ImageRotateOrientation::UP);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ImageLayoutProperty, ImageRotateOrientation, orientationValue, frameNode);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetOrientation(orientationValue);
}

void ImageModelStatic::SetEnhancedImageQuality(FrameNode* frameNode, const std::optional<AIImageQuality>& imageQuality)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetImageQuality(imageQuality.value_or(AIImageQuality::NONE));
}

void ImageModelStatic::SetResizableLattice(FrameNode* frameNode, const RefPtr<DrawingLattice>& lattice)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_PAINT_PROPERTY(ImageRenderProperty, ImageResizableLattice, lattice, frameNode);
}

void ImageModelStatic::SetPixelMap(FrameNode* frameNode, const RefPtr<PixelMap>& pixelMap)
{
    CHECK_NULL_VOID(frameNode);
    auto srcInfo = ImageSourceInfo(pixelMap);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ImageLayoutProperty, ImageSourceInfo, srcInfo, frameNode);
}

void ImageModelStatic::SetDrawableDescriptor(FrameNode* frameNode, void* drawable, int type)
{
    CHECK_NULL_VOID(frameNode);
    if (type == LAYERED_TYPE) {
        // layered
        auto layeredDrawable = reinterpret_cast<LayeredDrawableDescriptor*>(drawable);
        CHECK_NULL_VOID(layeredDrawable);
        auto pixelMap = layeredDrawable->GetPixelMap();
        SetPixelMap(frameNode, pixelMap);
    } else if (type == ANIMATED_TYPE) {
        // animated
        auto animatedDrawable = reinterpret_cast<AnimatedDrawableDescriptor*>(drawable);
        CHECK_NULL_VOID(animatedDrawable);
        auto pixelMaps = animatedDrawable->GetPixelMapList();
        auto duration = animatedDrawable->GetTotalDuration();
        auto iterations = animatedDrawable->GetIterations();
        SetPixelMapList(frameNode, pixelMaps, duration, iterations);
    } else if (type == PIXELMAP_TYPE) {
        // pixelmap
        auto pixelmapDrawable = reinterpret_cast<PixelMapDrawableDescriptor*>(drawable);
        CHECK_NULL_VOID(pixelmapDrawable);
        auto pixelMap = pixelmapDrawable->GetPixelMap();
        SetPixelMap(frameNode, pixelMap);
    }
}

void ImageModelStatic::SetPixelMapList(
    FrameNode* frameNode, const std::vector<RefPtr<PixelMap>>& pixelMaps, int32_t duration, int32_t iteration)
{
    // std::vector<ImageProperties> imageList;
    // for (int i = 0; i < static_cast<int32_t>(pixelMaps.size()); i++) {
    //     ImageProperties image;
    //     image.pixelMap = pixelMaps[i];
    //     imageList.push_back(image);
    // }
    // if (frameNode->GetChildren().empty()) {
    //     auto imageNode = FrameNode::CreateFrameNode(
    //         V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    //     CHECK_NULL_VOID(imageNode);
    //     auto imageLayoutProperty = AceType::DynamicCast<ImageLayoutProperty>(imageNode->GetLayoutProperty());
    //     CHECK_NULL_VOID(imageLayoutProperty);
    //     imageLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
    //     frameNode->GetLayoutProperty()->UpdateAlignment(Alignment::TOP_LEFT);
    //     frameNode->AddChild(imageNode);
    // }
    // auto pattern = frameNode->GetPattern<ImagePattern>();
    // CHECK_NULL_VOID(pattern);
    // if (!pattern->GetIsAnimation()) {
    //     auto castImageLayoutProperty = frameNode->GetLayoutPropertyPtr<ImageLayoutProperty>();
    //     CHECK_NULL_VOID(castImageLayoutProperty);
    //     castImageLayoutProperty->Reset();
    //     auto castImageRenderProperty = frameNode->GetPaintPropertyPtr<ImageRenderProperty>();
    //     CHECK_NULL_VOID(castImageRenderProperty);
    //     castImageRenderProperty->Reset();
    //     pattern->ResetImageAndAlt();
    //     pattern->ResetImageProperties();
    // }
    // auto pipeline = frameNode->GetContext();
    // CHECK_NULL_VOID(pipeline);
    // auto draggable = pipeline->GetDraggable<ImageTheme>();
    // if (draggable && !frameNode->IsDraggable()) {
    //     auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    //     CHECK_NULL_VOID(gestureHub);
    //     gestureHub->InitDragDropEvent();
    // }
    // pattern->SetSrcUndefined(false);
    // pattern->StopAnimation();
    // pattern->SetImageType(ImageType::ANIMATED_DRAWABLE);
    // pattern->SetImages(std::move(imageList));
    // pattern->SetDuration(duration);
    // pattern->SetIteration(iteration);
    // pattern->StartAnimation();
}

void ImageModelStatic::SetDrawingColorFilter(FrameNode* frameNode, const RefPtr<DrawingColorFilter>& colorFilter)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(ImageRenderProperty, DrawingColorFilter, colorFilter, frameNode);
    ACE_RESET_NODE_PAINT_PROPERTY(ImageRenderProperty, ColorFilter, frameNode);
}
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_IMAGE_IMAGE_MODEL_STATIC_CPP
