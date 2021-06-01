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

#include "frameworks/bridge/common/dom/dom_svg_polyline.h"

#include "frameworks/bridge/common/utils/utils.h"

namespace OHOS::Ace::Framework {

DOMSvgPolyline::DOMSvgPolyline(NodeId nodeId, const std::string& nodeName) : DOMSvgBase(nodeId, nodeName) {}

bool DOMSvgPolyline::SetSpecializedAttr(const std::pair<std::string, std::string>& attr)
{
    if (DOMSvgBase::SetPresentationAttr(attr)) {
        return true;
    }
    if (attr.first == DOM_SVG_POINTS) {
        points_ = attr.second;
        return true;
    }
    return false;
}

RefPtr<Component> DOMSvgPolyline::GetSpecializedComponent()
{
    return polylineComponent_;
}

void DOMSvgPolyline::OnChildNodeAdded(const RefPtr<DOMNode>& child, int32_t slot)
{
    polylineComponent_->InsertChild(slot, child->GetSpecializedComponent());
}

void DOMSvgPolyline::OnMounted(const RefPtr<DOMNode>& parentNode)
{
    DOMSvgBase::InheritCommonAttrs(polylineComponent_, parentNode);
}

void DOMSvgPolyline::PrepareSpecializedComponent()
{
    if (!polylineComponent_) {
        polylineComponent_ = AceType::MakeRefPtr<SvgPolylineComponent>();
    }
    polylineComponent_->SetPoints(points_);
    DOMSvgBase::PrepareCommonAttrs(polylineComponent_);
}

} // namespace OHOS::Ace::Framework
