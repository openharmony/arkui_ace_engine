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

#include "frameworks/bridge/common/dom/dom_svg_line.h"

#include "frameworks/bridge/common/utils/utils.h"

namespace OHOS::Ace::Framework {

DOMSvgLine::DOMSvgLine(NodeId nodeId, const std::string& nodeName) : DOMSvgBase(nodeId, nodeName) {}

bool DOMSvgLine::SetSpecializedAttr(const std::pair<std::string, std::string>& attr)
{
    if (DOMSvgBase::SetPresentationAttr(attr)) {
        return true;
    }
    if (attr.first == DOM_SVG_X1) {
        x1_ = ParseDimension(attr.second);
        return true;
    }
    if (attr.first == DOM_SVG_X2) {
        x2_ = ParseDimension(attr.second);
        return true;
    }
    if (attr.first == DOM_SVG_Y1) {
        y1_ = ParseDimension(attr.second);
        return true;
    }
    if (attr.first == DOM_SVG_Y2) {
        y2_ = ParseDimension(attr.second);
        return true;
    }
    return false;
}

RefPtr<Component> DOMSvgLine::GetSpecializedComponent()
{
    return lineComponent_;
}

void DOMSvgLine::OnChildNodeAdded(const RefPtr<DOMNode>& child, int32_t slot)
{
    lineComponent_->InsertChild(slot, child->GetSpecializedComponent());
}

void DOMSvgLine::OnMounted(const RefPtr<DOMNode>& parentNode)
{
    DOMSvgBase::InheritCommonAttrs(lineComponent_, parentNode);
}

void DOMSvgLine::PrepareSpecializedComponent()
{
    if (!lineComponent_) {
        lineComponent_ = AceType::MakeRefPtr<SvgLineComponent>();
    }
    lineComponent_->SetX1(x1_);
    lineComponent_->SetX2(x2_);
    lineComponent_->SetY1(y1_);
    lineComponent_->SetY2(y2_);
    DOMSvgBase::PrepareCommonAttrs(lineComponent_);
}

} // namespace OHOS::Ace::Framework
