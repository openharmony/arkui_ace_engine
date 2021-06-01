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

#include "frameworks/bridge/common/dom/dom_svg_text.h"

#include "frameworks/bridge/common/utils/utils.h"

namespace OHOS::Ace::Framework {

DOMSvgText::DOMSvgText(NodeId nodeId, const std::string& nodeName) : DOMSvgBase(nodeId, nodeName) {}

bool DOMSvgText::SetSpecializedAttr(const std::pair<std::string, std::string>& attr)
{
    if (DOMSvgBase::SetPresentationAttr(attr)) {
        return true;
    }
    if (attr.first == DOM_VALUE) {
        textData_ = attr.second;
        return true;
    }
    if (attr.first == DOM_SVG_X) {
        hasX_ = true;
        x_ = ParseDimension(attr.second);
        return true;
    }
    if (attr.first == DOM_SVG_Y) {
        hasY_ = true;
        y_ = ParseDimension(attr.second);
        return true;
    }
    if (attr.first == DOM_SVG_DX) {
        dx_ = ParseDimension(attr.second);
        return true;
    }
    if (attr.first == DOM_SVG_DY) {
        dy_ = ParseDimension(attr.second);
        return true;
    }
    if (attr.first == DOM_SVG_ROTATE) {
        rotate_ = ParseDouble(attr.second);
        hasRotate_ = true;
        return true;
    }
    if (attr.first == DOM_SVG_TEXT_LENGTH) {
        textLength_ = ParseDimension(attr.second);
        return true;
    }
    if (attr.first == DOM_SVG_LENGTH_ADJUST) {
        lengthAdjust_ = attr.second;
        return true;
    }
    return false;
}

RefPtr<Component> DOMSvgText::GetSpecializedComponent()
{
    return textComponent_;
}

void DOMSvgText::OnChildNodeAdded(const RefPtr<DOMNode>& child, int32_t slot)
{
    textComponent_->InsertChild(slot, child->GetSpecializedComponent());
}

void DOMSvgText::OnMounted(const RefPtr<DOMNode>& parentNode)
{
    auto svgNode = AceType::DynamicCast<DOMSvgBase>(parentNode);
    if (svgNode) {
        fillState_.Inherit(svgNode->GetFillState());
        strokeState_.Inherit(svgNode->GetStrokeState());
        textStyle_.Inherit(svgNode->GetTextStyle());
        textComponent_->SetFillState(fillState_);
        textComponent_->SetStrokeState(strokeState_);
        textComponent_->SetTextStyle(textStyle_);
    }

    if (!hasRotate_) {
        auto svgTextNode = AceType::DynamicCast<DOMSvgText>(parentNode);
        if (svgTextNode) {
            rotate_ = svgTextNode->GetRotate();
            textComponent_->SetRotate(rotate_);
        }
    }
}

void DOMSvgText::PrepareSpecializedComponent()
{
    if (!textComponent_) {
        textComponent_ = AceType::MakeRefPtr<SvgTextComponent>();
    }
    textComponent_->SetX(x_);
    textComponent_->SetY(y_);
    textComponent_->SetDx(dx_);
    textComponent_->SetDy(dy_);
    textComponent_->SetHasX(hasX_);
    textComponent_->SetHasY(hasY_);
    textComponent_->SetRotate(rotate_);
    textComponent_->SetTextData(textData_);
    textComponent_->SetTextLength(textLength_);
    textComponent_->SetLengthAdjust(lengthAdjust_);
    textComponent_->SetTextStyle(textStyle_);
    DOMSvgBase::PrepareCommonAttrs(textComponent_);
}

} // namespace OHOS::Ace::Framework
