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
#include <cstdint>

#include "core/components_ng/pattern/text/span_node.h"
#include "core/components_ng/pattern/image/image_model_ng.h"
#include "core/components_ng/base/view_abstract.h"

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

void ImageSpanView::SetBaselineOffset(const Dimension& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ImageLayoutProperty, BaselineOffset, value);
}

void ImageSpanView::SetBaselineOffset(FrameNode* frameNode, const Dimension& value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ImageLayoutProperty, BaselineOffset, value, frameNode);
}

float ImageSpanView::GetBaselineOffset(FrameNode* frameNode, int32_t unit)
{
    Dimension value;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(ImageLayoutProperty, BaselineOffset,
        value, frameNode, value);
    return value.GetNativeValue(static_cast<DimensionUnit>(unit));
}

void ImageSpanView::SetAlt(FrameNode* frameNode, RefPtr<PixelMap>& pixMap)
{
    auto srcInfo = ImageSourceInfo(pixMap);
    ImageModelNG::SetAlt(frameNode, srcInfo);
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
    const auto& frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    const auto& layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    const auto& src = layoutProperty->GetImageSourceInfo().value_or(ImageSourceInfo(""));
    if (src.IsPixmap()) {
        const auto& pattern = frameNode->GetPattern<ImagePattern>();
        CHECK_NULL_VOID(pattern);
        pattern->SetSyncLoad(true);
    }
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

void ImageSpanView::SetOnComplete(
    FrameNode* frameNode, std::function<void(const LoadImageSuccessEvent& info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ImageEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnComplete(std::move(callback));
}

void ImageSpanView::SetOnError(FrameNode* frameNode, std::function<void(const LoadImageFailEvent& info)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ImageEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnError(std::move(callback));
}

void ImageSpanView::SetBorderRadius(FrameNode* frameNode, NG::BorderRadiusProperty borderRadius)
{
    ViewAbstract::SetBorderRadius(frameNode, borderRadius);
    ImageModelNG::SetBackBorder(frameNode);
}

void ImageSpanView::ResetBorderRadius(FrameNode* frameNode)
{
    BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(Dimension(0));
    ViewAbstract::SetBorderRadius(frameNode, borderRadius);
    ImageModelNG::ResetBackBorder(frameNode);
}
} // namespace OHOS::Ace::NG
