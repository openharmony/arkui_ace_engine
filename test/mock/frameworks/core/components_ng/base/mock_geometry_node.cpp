/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
RectF GeometryNode::GetFrameRect(bool withSafeArea) const
{
    (void)withSafeArea;
    return frame_.rect_;
}

SizeF GeometryNode::GetFrameSize(bool withSafeArea) const
{
    (void)withSafeArea;
    return frame_.rect_.GetSize();
}

OffsetF GeometryNode::GetFrameOffset(bool withSafeArea) const
{
    (void)withSafeArea;
    return frame_.rect_.GetOffset();
}

void GeometryNode::SetMarginFrameOffset(const OffsetF& translate)
{
    frame_.rect_.SetOffset(translate);
}

RectF GeometryNode::GetParentAdjust() const
{
    return {};
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
} // namespace OHOS::Ace::NG
