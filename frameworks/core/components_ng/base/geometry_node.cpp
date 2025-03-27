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

#include "core/components_ng/base/geometry_node.h"

#include "core/components_ng/property/measure_utils.h"
namespace OHOS::Ace::NG {

void GeometryNode::Reset()
{
    frame_.Reset();
    margin_.reset();
    padding_.reset();
    content_.reset();
    parentGlobalOffset_.Reset();
    parentAbsoluteOffset_.Reset();
    parentLayoutConstraint_.reset();
    resolvedSingleSafeAreaPadding_.reset();
    accumulatedSafeAreaExpand_.reset();
}

RefPtr<GeometryNode> GeometryNode::Clone() const
{
    auto node = MakeRefPtr<GeometryNode>();
    node->frame_ = frame_;
    if (margin_) {
        node->margin_ = std::make_unique<MarginPropertyF>(*margin_);
    }
    if (padding_) {
        node->padding_ = std::make_unique<MarginPropertyF>(*padding_);
    }
    if (content_) {
        node->content_ = std::make_unique<GeometryProperty>(*content_);
    }
    if (accumulatedSafeAreaExpand_) {
        node->accumulatedSafeAreaExpand_ = std::make_unique<PaddingPropertyF>(*accumulatedSafeAreaExpand_);
    }
    if (resolvedSingleSafeAreaPadding_) {
        node->resolvedSingleSafeAreaPadding_ = std::make_unique<PaddingPropertyF>(*resolvedSingleSafeAreaPadding_);
    }
    node->parentGlobalOffset_ = parentGlobalOffset_;
    node->parentLayoutConstraint_ = parentLayoutConstraint_;
    node->parentAbsoluteOffset_ = parentAbsoluteOffset_;
    node->selfAdjust_ = selfAdjust_;
    return node;
}

void GeometryNode::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
#if defined(PREVIEW)
    auto frameSize = frame_.rect_.GetSize();
    json->Put("width", std::to_string(frameSize.Width()).c_str());
    json->Put("height", std::to_string(frameSize.Height()).c_str());

    auto jsonSize = JsonUtil::Create(true);
    jsonSize->Put("width", std::to_string(frameSize.Width()).c_str());
    jsonSize->Put("height", std::to_string(frameSize.Height()).c_str());
    json->Put("size", jsonSize);
#endif
}

void GeometryNode::SetAccumulatedSafeAreaEdges(const ExpandEdges& safeAreaPadding)
{
    if (!accumulatedSafeAreaExpand_) {
        accumulatedSafeAreaExpand_ = std::make_unique<ExpandEdges>(safeAreaPadding);
        return;
    }
    if (safeAreaPadding.left) {
        accumulatedSafeAreaExpand_->left = safeAreaPadding.left;
    }
    if (safeAreaPadding.right) {
        accumulatedSafeAreaExpand_->right = safeAreaPadding.right;
    }
    if (safeAreaPadding.top) {
        accumulatedSafeAreaExpand_->top = safeAreaPadding.top;
    }
    if (safeAreaPadding.bottom) {
        accumulatedSafeAreaExpand_->bottom = safeAreaPadding.bottom;
    }
}

const std::unique_ptr<ExpandEdges>& GeometryNode::GetAccumulatedSafeAreaExpand() const
{
    return accumulatedSafeAreaExpand_;
}

void GeometryNode::ResetAccumulatedSafeAreaPadding()
{
    CHECK_NULL_VOID(accumulatedSafeAreaExpand_);
    accumulatedSafeAreaExpand_.reset();
}

void GeometryNode::SetResolvedSingleSafeAreaPadding(const PaddingPropertyF& safeAreaPadding)
{
    resolvedSingleSafeAreaPadding_ = std::make_unique<PaddingPropertyF>(safeAreaPadding);
}

const std::unique_ptr<PaddingPropertyF>& GeometryNode::GetResolvedSingleSafeAreaPadding() const
{
    return resolvedSingleSafeAreaPadding_;
}

void GeometryNode::ResetResolvedSelfSafeAreaPadding()
{
    resolvedSingleSafeAreaPadding_.reset();
}

RectF GeometryNode::GetParentAdjust() const
{
    return parentAdjust_;
}

void GeometryNode::SetParentAdjust(RectF parentAdjust)
{
    parentAdjust_ = parentAdjust;
}

RectF GeometryNode::GetSelfAdjust() const
{
    return selfAdjust_;
}

void GeometryNode::SetSelfAdjust(RectF selfAdjust)
{
    selfAdjust_ = selfAdjust;
}

SizeF GeometryNode::GetMarginFrameSize(bool withSafeArea) const
{
    auto size = frame_.rect_.GetSize();
    if (withSafeArea) {
        size += selfAdjust_.GetSize();
    }
    if (margin_) {
        AddPaddingToSize(*margin_, size);
    }
    return size;
}

OffsetF GeometryNode::GetMarginFrameOffset(bool withSafeArea) const
{
    auto offset = frame_.rect_.GetOffset();
    if (withSafeArea) {
        offset += selfAdjust_.GetOffset();
    }
    if (margin_) {
        offset -= OffsetF(margin_->left.value_or(0), margin_->top.value_or(0));
    }
    return offset;
}

RectF GeometryNode::GetMarginFrameRect(bool withSafeArea) const
{
    auto offset = frame_.rect_.GetOffset();
    auto size = frame_.rect_.GetSize();
    if (withSafeArea) {
        offset += selfAdjust_.GetOffset();
        size += selfAdjust_.GetSize();
    }
    if (margin_) {
        offset -= OffsetF(margin_->left.value_or(0), margin_->top.value_or(0));
        AddPaddingToSize(*margin_, size);
    }
    return RectF(offset, size);
}

void GeometryNode::SetMarginFrameOffset(const OffsetF& translate)
{
    OffsetF offset;
    if (margin_) {
        offset += OffsetF(margin_->left.value_or(0), margin_->top.value_or(0));
    }
    frame_.rect_.SetOffset(translate + offset);
}

RectF GeometryNode::GetFrameRect(bool withSafeArea) const
{
    auto result = frame_.rect_;
    if (withSafeArea) {
        result += selfAdjust_;
    }
    return result;
}

SizeF GeometryNode::GetFrameSize(bool withSafeArea) const
{
    auto result = frame_.rect_.GetSize();
    if (withSafeArea) {
        result += selfAdjust_.GetSize();
    }
    return result;
}

OffsetF GeometryNode::GetFrameOffset(bool withSafeArea) const
{
    auto result = frame_.rect_.GetOffset();
    if (withSafeArea) {
        result += selfAdjust_.GetOffset();
    }
    return result;
}

void GeometryNode::SetMarginFrameOffsetX(int32_t offsetX)
{
    float offset = offsetX;
    if (margin_) {
        offset += margin_->left.value_or(0);
    }
    frame_.rect_.SetLeft(offset);
}

void GeometryNode::SetMarginFrameOffsetY(int32_t offsetY)
{
    float offset = offsetY;
    if (margin_) {
        offset += margin_->top.value_or(0);
    }
    frame_.rect_.SetTop(offset);
}

SizeF GeometryNode::GetPaddingSize(bool withSafeArea) const
{
    auto size = frame_.rect_.GetSize();
    if (withSafeArea) {
        size += selfAdjust_.GetSize();
    }
    if (padding_) {
        MinusPaddingToSize(*padding_, size);
    }
    return size;
}

OffsetF GeometryNode::GetPaddingOffset(bool withSafeArea) const
{
    auto offset = frame_.rect_.GetOffset();
    if (withSafeArea) {
        offset += selfAdjust_.GetOffset();
    }
    if (padding_) {
        offset += OffsetF(padding_->left.value_or(0), padding_->top.value_or(0));
    }
    return offset;
}

RectF GeometryNode::GetPaddingRect(bool withSafeArea) const
{
    auto rect = frame_.rect_;
    if (withSafeArea) {
        rect += selfAdjust_;
    }
    if (padding_) {
        auto size = rect.GetSize();
        MinusPaddingToSize(*padding_, size);
        rect.SetSize(size);
        auto offset = rect.GetOffset();
        offset += OffsetF(padding_->left.value_or(0), padding_->top.value_or(0));
        rect.SetOffset(offset);
    }
    return rect;
}

void GeometryNode::SetContentSize(const SizeF& size)
{
    if (!content_) {
        content_ = std::make_unique<GeometryProperty>();
    }
    content_->rect_.SetSize(size);
}

void GeometryNode::SetContentOffset(const OffsetF& translate)
{
    if (!content_) {
        content_ = std::make_unique<GeometryProperty>();
    }
    content_->rect_.SetOffset(translate);
}

void GeometryNode::UpdateMargin(const MarginPropertyF& margin)
{
    if (!margin_) {
        margin_ = std::make_unique<MarginPropertyF>(margin);
        return;
    }
    margin_->Reset();
    if (margin.left) {
        margin_->left = margin.left;
    }
    if (margin.right) {
        margin_->right = margin.right;
    }
    if (margin.top) {
        margin_->top = margin.top;
    }
    if (margin.bottom) {
        margin_->bottom = margin.bottom;
    }
}

void GeometryNode::UpdatePaddingWithBorder(const PaddingPropertyF& padding)
{
    if (!padding_) {
        padding_ = std::make_unique<PaddingPropertyF>(padding);
        return;
    }
    padding_->Reset();
    if (padding.left) {
        padding_->left = padding.left;
    }
    if (padding.right) {
        padding_->right = padding.right;
    }
    if (padding.top) {
        padding_->top = padding.top;
    }
    if (padding.bottom) {
        padding_->bottom = padding.bottom;
    }
}
} // namespace OHOS::Ace::NG
