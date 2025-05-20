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
 
 #include "core/components/common/layout/constants.h"
 #include "core/components/image/image_theme.h"
 #include "core/components_ng/base/frame_node.h"
 #include "core/components_ng/pattern/image/image_render_property.h"
 #include "core/image/image_source_info.h"
 #ifndef ACE_UNITTEST
 #include "core/components_ng/base/view_abstract.h"
 #endif
 #include "interfaces/native/node/resource.h"
 
 #include "core/components_ng/pattern/text/span_node.h"
 
 namespace OHOS::Ace::NG {
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
         ACE_RESET_NODE_PAINT_PROPERTY(ImageRenderProperty, SvgFillColor, frameNode);
         ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, ForegroundColor, frameNode);
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
     if (interpolation) {
         ACE_UPDATE_NODE_PAINT_PROPERTY(ImageRenderProperty, ImageInterpolation, interpolation.value(), frameNode);
     } else {
         ACE_RESET_NODE_PAINT_PROPERTY(ImageRenderProperty, ImageInterpolation, frameNode);
     }
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
 } // namespace OHOS::Ace::NG
 #endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_IMAGE_IMAGE_MODEL_STATIC_CPP
 