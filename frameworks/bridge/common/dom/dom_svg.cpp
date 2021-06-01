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

#include "frameworks/bridge/common/dom/dom_svg.h"
#include "frameworks/bridge/common/dom/dom_svg_animate.h"

#include "frameworks/bridge/common/utils/utils.h"

namespace OHOS::Ace::Framework {

DOMSvg::DOMSvg(NodeId nodeId, const std::string& nodeName) : DOMSvgBase(nodeId, nodeName)
{
    SetHasDisplayStyleFlag(true);
    transformComponent_ = AceType::MakeRefPtr<TransformComponent>();
    overflow_ = Overflow::CLIP;
}

bool DOMSvg::SetSpecializedAttr(const std::pair<std::string, std::string>& attr)
{
    if (DOMSvgBase::SetPresentationAttr(attr)) {
        return true;
    }
    if (attr.first == DOM_SVG_VIEW_BOX) {
        std::vector<std::string> viewBoxValues;
        if (!attr.second.empty()) {
            StringUtils::SplitStr(attr.second, " ", viewBoxValues);
        }
        if (viewBoxValues.size() == 4) {
            viewBox_ = Rect(ParseDouble(viewBoxValues[0]), ParseDouble(viewBoxValues[1]),
                ParseDouble(viewBoxValues[2]), ParseDouble(viewBoxValues[3]));
        }
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

RefPtr<Component> DOMSvg::GetSpecializedComponent()
{
    return svgComponent_;
}

void DOMSvg::OnChildNodeAdded(const RefPtr<DOMNode>& child, int32_t slot)
{
    if (AceType::InstanceOf<SvgAnimateComponent>(child->GetSpecializedComponent())) {
        svgComponent_->InsertChild(slot, child->GetSpecializedComponent());
    } else {
        svgComponent_->InsertChild(slot, child->GetRootComponent());
    }
}

void DOMSvg::OnMounted(const RefPtr<DOMNode>& parentNode)
{
    auto svgNode = AceType::DynamicCast<DOMSvg>(parentNode);
    if (svgNode) {
        fillState_.Inherit(svgNode->GetFillState());
        strokeState_.Inherit(svgNode->GetStrokeState());
        textStyle_.Inherit(svgNode->GetTextStyle());
        if (!NearZero(x_.Value()) || !NearZero(y_.Value())) {
            transformComponent_->Translate(x_, y_);
        }
    }
}

void DOMSvg::PrepareSpecializedComponent()
{
    if (!svgComponent_) {
        svgComponent_ = AceType::MakeRefPtr<SvgComponent>();
    }
    svgComponent_->SetX(x_);
    svgComponent_->SetY(y_);
    svgComponent_->SetHeight(height_);
    svgComponent_->SetWidth(width_);
    svgComponent_->SetViewBox(viewBox_);
    DOMSvgBase::PrepareCommonAttrs(svgComponent_);
}

} // namespace OHOS::Ace::Framework
