/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/image/image_view.h"

#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
void ImageView::Create(const std::string& src)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ImageSourceInfo imageSourceInfo(src);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::IMAGE_ETS_TAG, nodeId, [imageSourceInfo]() { return AceType::MakeRefPtr<ImagePattern>(imageSourceInfo); });
    stack->Push(frameNode);
    ACE_UPDATE_LAYOUT_PROPERTY(ImageLayoutProperty, ImageSourceInfo, imageSourceInfo);
}

void ImageView::SetObjectFit(ImageFit imageFit)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ImageLayoutProperty, ImageFit, imageFit);
}

void ImageView::SetAutoResize(bool autoResize)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ImageLayoutProperty, AutoResize, autoResize);
}

void ImageView::SetImageRenderMode(ImageRenderMode imageRenderMode)
{
    ACE_UPDATE_PAINT_PROPERTY(ImageRenderProperty, ImageRenderMode, imageRenderMode);
}

void ImageView::SetImageInterpolation(ImageInterpolation imageInterpolation)
{
    ACE_UPDATE_PAINT_PROPERTY(ImageRenderProperty, ImageInterpolation, imageInterpolation);
}

void ImageView::SetImageRepeat(ImageRepeat imageRepeat)
{
    ACE_UPDATE_PAINT_PROPERTY(ImageRenderProperty, ImageRepeat, imageRepeat);
}

void ImageView::SetImageSourceSize(const std::pair<Dimension, Dimension>& sourceSize)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ImageLayoutProperty, SourceSize, sourceSize);
}

void ImageView::SetFitOriginalSize(bool fitOriginalSize)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ImageLayoutProperty, FitOriginalSize, fitOriginalSize);
}

void ImageView::SetAlt(const std::string& altSrc)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ImageLayoutProperty, Alt, ImageSourceInfo(altSrc));
}

void ImageView::SetOnError(ErrorEvent&& onError)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ImageEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnError(std::move(onError));
}

void ImageView::SetOnComplete(CompleteEvent&& onComplete)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ImageEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnComplete(std::move(onComplete));
}

void ImageView::SetColorFilterMatrix(const std::vector<float>& matrix)
{
    ACE_UPDATE_PAINT_PROPERTY(ImageRenderProperty, ColorFilter, matrix);
}

void ImageView::SetMatchTextDirection(bool matchTextDirection)
{
    ACE_UPDATE_PAINT_PROPERTY(ImageRenderProperty, MatchTextDirection, matchTextDirection);
}

void ImageView::SetSvgFillColor(const Color& color)
{
    ACE_UPDATE_PAINT_PROPERTY(ImageRenderProperty, SvgFillColor, color);
}

} // namespace OHOS::Ace::NG
