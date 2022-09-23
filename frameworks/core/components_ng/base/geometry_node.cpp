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

#include <utility>

#include "core/components_ng/layout/layout_wrapper.h"

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
    node->layoutFunc_ = layoutFunc_;
    node->measureFunc_ = measureFunc_;
    return node;
}

bool GeometryNode::Measure(NG::LayoutWrapper* layoutWrapper)
{
    LOGD("%s, call geometryNode_ Measure in, %p", OHOS::Ace::DEVTAG.c_str(), this);
    if (measureFunc_) {
        LOGD("%s, call geometryNode_ Measure in ok", OHOS::Ace::DEVTAG.c_str());
        measureFunc_(layoutWrapper);
        return true;
    }
    LOGD("%s, call geometryNode_ Measure in fail", OHOS::Ace::DEVTAG.c_str());
    return false;
}

bool GeometryNode::Layout(NG::LayoutWrapper* layoutWrapper)
{
    if (layoutFunc_) {
        layoutFunc_(layoutWrapper);
        return true;
    }
    return false;
}

} // namespace OHOS::Ace::NG
