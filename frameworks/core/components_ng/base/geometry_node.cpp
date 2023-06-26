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

#include <string>
#include <utility>

#include "core/components_ng/layout/layout_wrapper.h"

namespace OHOS::Ace::NG {

void GeometryNode::Reset()
{
    frame_.Reset();
    margin_.reset();
    padding_.reset();
    content_.reset();
    parentGlobalOffset_.Reset();
    parentLayoutConstraint_.reset();
    previousState_.reset();
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
    node->parentGlobalOffset_ = parentGlobalOffset_;
    node->parentLayoutConstraint_ = parentLayoutConstraint_;
    node->previousState_ = previousState_ ? std::make_unique<RectF>(*previousState_) : nullptr;
    return node;
}

void GeometryNode::ToJsonValue(std::unique_ptr<JsonValue>& json) const
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

void GeometryNode::Restore()
{
    CHECK_NULL_VOID(previousState_);
    frame_.rect_ = *previousState_;
    previousState_ = nullptr;
}

void GeometryNode::Save()
{
    // INVARIANT: previousState_ is null when Save() is called (only allow 1 layer of save/restore)
    CHECK_NULL_VOID(!previousState_);
    previousState_ = std::make_unique<RectF>(frame_.rect_);
}
} // namespace OHOS::Ace::NG
