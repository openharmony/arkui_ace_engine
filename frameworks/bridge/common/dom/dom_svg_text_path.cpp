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

#include "frameworks/bridge/common/dom/dom_svg_text_path.h"

#include "frameworks/bridge/common/utils/utils.h"

namespace OHOS::Ace::Framework {

DOMSvgTextPath::DOMSvgTextPath(NodeId nodeId, const std::string& nodeName) : DOMSvgBase(nodeId, nodeName) {}

bool DOMSvgTextPath::SetSpecializedAttr(const std::pair<std::string, std::string>& attr)
{
    if (DOMSvgBase::SetPresentationAttr(attr)) {
        return true;
    }
    if (attr.first == DOM_VALUE) {
        textData_ = attr.second;
        return true;
    }
    if (attr.first == DOM_SVG_ATTR_PATH) {
        path_ = attr.second;
        return true;
    }
    if (attr.first == DOM_SVG_START_OFFSET) {
        startOffset_ = ParseDimension(attr.second);
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

RefPtr<Component> DOMSvgTextPath::GetSpecializedComponent()
{
    return textPathComponent_;
}

void DOMSvgTextPath::OnChildNodeAdded(const RefPtr<DOMNode>& child, int32_t slot)
{
    textPathComponent_->InsertChild(slot, child->GetSpecializedComponent());
}

void DOMSvgTextPath::OnMounted(const RefPtr<DOMNode>& parentNode)
{
    auto svgNode = AceType::DynamicCast<DOMSvgBase>(parentNode);
    if (svgNode) {
        fillState_.Inherit(svgNode->GetFillState());
        strokeState_.Inherit(svgNode->GetStrokeState());
        textStyle_.Inherit(svgNode->GetTextStyle());
        textPathComponent_->SetFillState(fillState_);
        textPathComponent_->SetStrokeState(strokeState_);
        textPathComponent_->SetTextStyle(textStyle_);
    }
}

void DOMSvgTextPath::PrepareSpecializedComponent()
{
    if (!textPathComponent_) {
        textPathComponent_ = AceType::MakeRefPtr<SvgTextPathComponent>();
    }
    textPathComponent_->SetPath(path_);
    textPathComponent_->SetStartOffset(startOffset_);
    textPathComponent_->SetTextData(textData_);
    textPathComponent_->SetTextLength(textLength_);
    textPathComponent_->SetTextStyle(textStyle_);
    textPathComponent_->SetLengthAdjust(lengthAdjust_);
    DOMSvgBase::PrepareCommonAttrs(textPathComponent_);
}

} // namespace OHOS::Ace::Framework
