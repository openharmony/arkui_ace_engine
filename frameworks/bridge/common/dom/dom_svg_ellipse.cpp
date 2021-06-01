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

#include "frameworks/bridge/common/dom/dom_svg_ellipse.h"

#include "frameworks/bridge/common/utils/utils.h"

namespace OHOS::Ace::Framework {

DOMSvgEllipse::DOMSvgEllipse(NodeId nodeId, const std::string& nodeName) : DOMSvgBase(nodeId, nodeName) {}

bool DOMSvgEllipse::SetSpecializedAttr(const std::pair<std::string, std::string>& attr)
{
    if (DOMSvgBase::SetPresentationAttr(attr)) {
        return true;
    }
    if (attr.first == DOM_SVG_CX) {
        cx_ = ParseDimension(attr.second);
        return true;
    }
    if (attr.first == DOM_SVG_CY) {
        cy_ = ParseDimension(attr.second);
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
    return false;
}

RefPtr<Component> DOMSvgEllipse::GetSpecializedComponent()
{
    return ellipseComponent_;
}

void DOMSvgEllipse::OnChildNodeAdded(const RefPtr<DOMNode>& child, int32_t slot)
{
    ellipseComponent_->InsertChild(slot, child->GetSpecializedComponent());
}

void DOMSvgEllipse::OnMounted(const RefPtr<DOMNode>& parentNode)
{
    DOMSvgBase::InheritCommonAttrs(ellipseComponent_, parentNode);
}

void DOMSvgEllipse::PrepareSpecializedComponent()
{
    if (!ellipseComponent_) {
        ellipseComponent_ = AceType::MakeRefPtr<SvgEllipseComponent>();
    }
    ellipseComponent_->SetCx(cx_);
    ellipseComponent_->SetCy(cy_);
    ellipseComponent_->SetRx(rx_);
    ellipseComponent_->SetRy(ry_);
    DOMSvgBase::PrepareCommonAttrs(ellipseComponent_);
}

} // namespace OHOS::Ace::Framework
