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

#include "frameworks/bridge/common/dom/dom_span.h"

#include "core/common/ace_application_info.h"
#include "frameworks/bridge/common/utils/utils.h"

namespace OHOS::Ace::Framework {

DOMSpan::DOMSpan(NodeId nodeId, const std::string& nodeName) : DOMNode(nodeId, nodeName)
{
    textSpanChild_ = AceType::MakeRefPtr<TextSpanComponent>("");
    // span has no box component.
    boxComponent_.Reset();
}

bool DOMSpan::SetSpecializedAttr(const std::pair<std::string, std::string>& attr)
{
    if (attr.first == DOM_VALUE) {
        textSpanChild_->SetSpanData(attr.second);
        return true;
    }
    if (attr.first == DOM_SHOW) {
        textSpanChild_->SetIsShow(StringToBool(attr.second));
        return true;
    }
    return false;
}

bool DOMSpan::SetSpecializedStyle(const std::pair<std::string, std::string>& style)
{
    static const LinearMapNode<void (*)(const std::string&, DOMSpan&)> spanStyleOperators[] = {
        { DOM_TEXT_ALLOW_SCALE,
            [](const std::string& val, DOMSpan& span) {
                span.spanStyle_.SetAllowScale(StringToBool(val));
                span.isSetAllowScale_ = true;
            } },
        { DOM_TEXT_COLOR,
            [](const std::string& val, DOMSpan& span) {
                span.spanStyle_.SetTextColor(span.ParseColor(val));
                span.isSetFontColor_ = true;
            } },
        { DOM_TEXT_FONT_FAMILY,
            [](const std::string& val, DOMSpan& span) {
                span.spanStyle_.SetFontFamilies(span.ParseFontFamilies(val));
                span.isSetFontFamily_ = true;
            } },
        { DOM_TEXT_FONT_SIZE,
            [](const std::string& val, DOMSpan& span) {
                span.spanStyle_.SetFontSize(span.ParseDimension(val));
                span.isSetFontSize_ = true;
            } },
        { DOM_TEXT_FONT_STYLE,
            [](const std::string& val, DOMSpan& span) {
                span.spanStyle_.SetFontStyle(ConvertStrToFontStyle(val));
                span.isSetFontStyle_ = true;
            } },
        { DOM_TEXT_FONT_WEIGHT,
            [](const std::string& val, DOMSpan& span) {
                span.spanStyle_.SetFontWeight(ConvertStrToFontWeight(val));
                span.isSetFontWeight_ = true;
            } },
        { DOM_TEXT_DECORATION,
            [](const std::string& val, DOMSpan& span) {
                span.spanStyle_.SetTextDecoration(ConvertStrToTextDecoration(val));
                span.isSetTextDecoration_ = true;
            } },
    };
    auto spanStyleIter = BinarySearchFindIndex(spanStyleOperators, ArraySize(spanStyleOperators), style.first.c_str());
    if (spanStyleIter != -1) {
        spanStyleOperators[spanStyleIter].value(style.second, *this);
    }

    // span has no box component, set true to prevent setting style to box (empty object).
    return true;
}

void DOMSpan::CheckAndSetCurrentSpanStyle(
    const RefPtr<DOMSpan>& domSpan, TextStyle& currentStyle, const TextStyle& parentStyle)
{
    if (!domSpan->HasSetFontColor()) {
        currentStyle.SetTextColor(parentStyle.GetTextColor());
    }
    if (!domSpan->HasSetFontSize()) {
        currentStyle.SetFontSize(parentStyle.GetFontSize());
    }
    if (!domSpan->HasSetFontStyle()) {
        currentStyle.SetFontStyle(parentStyle.GetFontStyle());
    }
    if (!domSpan->HasSetFontWeight()) {
        currentStyle.SetFontWeight(parentStyle.GetFontWeight());
    }
    if (!domSpan->HasSetTextDecoration()) {
        currentStyle.SetTextDecoration(parentStyle.GetTextDecoration());
    }
    if (!domSpan->HasSetFontFamily()) {
        currentStyle.SetFontFamilies(parentStyle.GetFontFamilies());
    }
    if (!domSpan->HasSetAllowScale()) {
        currentStyle.SetAllowScale(parentStyle.IsAllowScale());
    }
    currentStyle.SetLetterSpacing(parentStyle.GetLetterSpacing());
    currentStyle.SetLineHeight(parentStyle.GetLineHeight(), parentStyle.HasHeightOverride());
}

void DOMSpan::OnChildNodeAdded(const RefPtr<DOMNode>& child, int32_t slot)
{
    if (!child) {
        return;
    }

    if (child->GetTag() == DOM_NODE_TAG_SPAN) {
        // Get current span's parent (also span) styles, if no user setting styles
        // on this span, use its parent styles.
        TextStyle parentSpanStyle = textSpanChild_->GetTextStyle();
        auto spanComponent = AceType::DynamicCast<TextSpanComponent>(child->GetSpecializedComponent());
        if (!spanComponent) {
            LOGE("DOMSpan: span is null");
            return;
        }

        // Get current span's styles to compare with its parent span.
        TextStyle currentSpanStyle = spanComponent->GetTextStyle();
        auto domSpan = AceType::DynamicCast<DOMSpan>(child);
        CheckAndSetCurrentSpanStyle(domSpan, currentSpanStyle, parentSpanStyle);
        domSpan->SetTextStyle(currentSpanStyle);
        spanComponent->SetTextStyle(currentSpanStyle);
        textSpanChild_->InsertChild(slot, child->GetRootComponent());
    }
}

void DOMSpan::OnChildNodeRemoved(const RefPtr<DOMNode>& child)
{
    if (!child) {
        return;
    }

    textSpanChild_->RemoveChild(child->GetRootComponent());
}

void DOMSpan::PrepareSpecializedComponent()
{
    bool isCard = AceApplicationInfo::GetInstance().GetIsCardType();
    if (isCard) {
        spanStyle_.SetAllowScale(false);
        if (spanStyle_.GetFontSize().Unit() == DimensionUnit::FP) {
            spanStyle_.SetAllowScale(true);
        }
    }
    textSpanChild_->SetTextStyle(spanStyle_);
}

} // namespace OHOS::Ace::Framework
