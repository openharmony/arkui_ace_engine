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
    content_.reset();
    parentGlobalOffset_.Reset();
    parentLayoutConstraint_.reset();
}

RefPtr<GeometryNode> GeometryNode::Clone() const
{
    auto node = MakeRefPtr<GeometryNode>();
    node->frame_ = frame_;
    if (margin_) {
        node->margin_ = std::make_unique<MarginPropertyF>(*margin_);
    }
    if (content_) {
        node->content_ = std::make_unique<GeometryProperty>(*content_);
    }
    node->parentGlobalOffset_ = parentGlobalOffset_;
    node->parentLayoutConstraint_ = parentLayoutConstraint_;
    return node;
}

} // namespace OHOS::Ace::NG
