/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/common/dom/dom_svg_rect.h"

#include "frameworks/bridge/common/utils/utils.h"

namespace OHOS::Ace::Framework {

DOMSvgRect::DOMSvgRect(NodeId nodeId, const std::string& nodeName) : DOMSvgBase(nodeId, nodeName) {}

bool DOMSvgRect::SetSpecializedAttr(const std::pair<std::string, std::string>& attr)
{
    if (DOMSvgBase::SetPresentationAttr(attr)) {
        return true;
    }
    if (attr.first == DOM_SVG_X) {
        x_ = ParseDimension(attr.second);
        return true;
    }
    if (attr.first == DOM_SVG_Y) {
        y_ = ParseDimension(attr.second);
        return true;
    }
    if (attr.first == DOM_SVG_RX) {
        rx_ = ParseDimension(attr.second);
        return true;
    }
    if (attr.first == DOM_SVG_RY) {
        ry_ = ParseDimension(attr.second);
        return true;
    }
    if (attr.first == DOM_SVG_WIDTH) {
        width_ = ParseDimension(attr.second);
        return true;
    }
    if (attr.first == DOM_SVG_HEIGHT) {
        height_ = ParseDimension(attr.second);
        return true;
    }
    return false;
}

RefPtr<Component> DOMSvgRect::GetSpecializedComponent()
{
    return rectComponent_;
}

void DOMSvgRect::OnChildNodeAdded(const RefPtr<DOMNode>& child, int32_t slot)
{
    rectComponent_->InsertChild(slot, child->GetSpecializedComponent());
}

void DOMSvgRect::OnMounted(const RefPtr<DOMNode>& parentNode)
{
    DOMSvgBase::InheritCommonAttrs(rectComponent_, parentNode);
}

void DOMSvgRect::PrepareSpecializedComponent()
{
    if (!rectComponent_) {
        rectComponent_ = AceType::MakeRefPtr<SvgRectComponent>();
    }
    rectComponent_->SetX(x_);
    rectComponent_->SetY(y_);
    rectComponent_->SetHeight(height_);
    rectComponent_->SetWidth(width_);
    rectComponent_->SetRx(rx_);
    rectComponent_->SetRy(ry_);
    DOMSvgBase::PrepareCommonAttrs(rectComponent_);
}

} // namespace OHOS::Ace::Framework
