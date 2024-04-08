/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/text/image_span_view.h"

#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/text/span_node.h"
#include "core/components_ng/pattern/image/image_model_ng.h"

namespace OHOS::Ace::NG {
void ImageSpanView::SetObjectFit(ImageFit value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ImageLayoutProperty, ImageFit, value);
}

void ImageSpanView::SetVerticalAlign(VerticalAlign verticalAlign)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ImageLayoutProperty, VerticalAlign, verticalAlign);
}

void ImageSpanView::SetVerticalAlign(FrameNode* frameNode, VerticalAlign verticalAlign)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ImageLayoutProperty, VerticalAlign, verticalAlign, frameNode);
}

void ImageSpanView::SetPlaceHolderStyle(TextBackgroundStyle& style)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    style.groupId = frameNode->GetId();
    ACE_UPDATE_LAYOUT_PROPERTY(ImageLayoutProperty, PlaceHolderStyle, style);
    ACE_UPDATE_LAYOUT_PROPERTY(ImageLayoutProperty, HasPlaceHolderStyle,
        style.backgroundColor.has_value() || style.backgroundRadius.has_value());
    auto frameNodeRef = AceType::Claim<FrameNode>(frameNode);
    SpanNode::RequestTextFlushDirty(AceType::Claim<FrameNode>(frameNode));
}

void ImageSpanView::SetPlaceHolderStyle(FrameNode* frameNode, TextBackgroundStyle& style)
{
    style.groupId = frameNode->GetId();
    ACE_UPDATE_LAYOUT_PROPERTY(ImageLayoutProperty, PlaceHolderStyle, style);
    ACE_UPDATE_LAYOUT_PROPERTY(ImageLayoutProperty, HasPlaceHolderStyle,
        style.backgroundColor.has_value() || style.backgroundRadius.has_value());
    auto frameNodeRef = AceType::Claim<FrameNode>(frameNode);
    SpanNode::RequestTextFlushDirty(AceType::Claim<FrameNode>(frameNode));
}

void ImageSpanView::Create()
{
    ACE_UPDATE_LAYOUT_PROPERTY(ImageLayoutProperty, HasPlaceHolderStyle, false);
}

RefPtr<FrameNode> ImageSpanView::CreateFrameNode(int32_t nodeId)
{
    RefPtr<PixelMap> pixmap = nullptr;
    auto imageSpanNode = ImageModelNG::CreateFrameNode(nodeId, "", pixmap, "", "");
    CHECK_NULL_RETURN(imageSpanNode, nullptr);
    auto layoutProperty = imageSpanNode->GetLayoutProperty<ImageLayoutProperty>();
    layoutProperty->UpdateHasPlaceHolderStyle(false);
    return imageSpanNode;
}

ImageSourceInfo ImageSpanView::GetImageSpanSrc(FrameNode* frameNode)
{
    ImageSourceInfo defaultImageSource;
    CHECK_NULL_RETURN(frameNode, defaultImageSource);
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, defaultImageSource);
    return layoutProperty->GetImageSourceInfo().value_or(defaultImageSource);
}

ImageFit ImageSpanView::GetObjectFit(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, ImageFit::COVER);
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, ImageFit::COVER);
    return layoutProperty->GetImageFit().value_or(ImageFit::COVER);
}

VerticalAlign ImageSpanView::GetVerticalAlign(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, VerticalAlign::BOTTOM);
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, VerticalAlign::BOTTOM);
    return layoutProperty->GetVerticalAlign().value_or(VerticalAlign::BOTTOM);
}

TextBackgroundStyle ImageSpanView::GetSpanTextBackgroundStyle(FrameNode* frameNode)
{
    TextBackgroundStyle backgroundStyle;
    CHECK_NULL_RETURN(frameNode, backgroundStyle);
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, backgroundStyle);
    return layoutProperty->GetPlaceHolderStyle().value_or(backgroundStyle);
}

} // namespace OHOS::Ace::NG
