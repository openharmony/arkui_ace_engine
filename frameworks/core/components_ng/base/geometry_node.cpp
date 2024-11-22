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
} // namespace OHOS::Ace::NG
