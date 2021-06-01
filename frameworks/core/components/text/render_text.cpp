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

#include "core/components/text/render_text.h"

#include "base/geometry/size.h"
#include "core/common/font_manager.h"
#include "core/components/text/text_component.h"

namespace OHOS::Ace {

RenderText::~RenderText()
{
    auto context = context_.Upgrade();
    if (context) {
        context->RemoveFontNode(AceType::WeakClaim(this));
        auto fontManager = context->GetFontManager();
        if (fontManager) {
            fontManager->UnRegisterCallback(AceType::WeakClaim(this));
            fontManager->RemoveVariationNode(WeakClaim(this));
        }
    }
}

void RenderText::Update(const RefPtr<Component>& component)
{
    const RefPtr<TextComponent> text = AceType::DynamicCast<TextComponent>(component);
    if (text) {
        CheckIfNeedMeasure(text);
    }
    auto context = context_.Upgrade();
    if (!context) {
        LOGE("the context is nullptr in text update");
        return;
    }
    // Register callback for fonts.
    auto callback = [weakText = AceType::WeakClaim(this)] {
        auto text = weakText.Upgrade();
        if (text) {
            text->isCallbackCalled_ = true;
            text->MarkNeedLayout();
        }
    };
    auto fontManager = context->GetFontManager();
    if (fontManager) {
        for (const auto& familyName : textStyle_.GetFontFamilies()) {
            fontManager->RegisterCallback(AceType::WeakClaim(this), familyName, callback);
        }
        fontManager->AddVariationNode(WeakClaim(this));
    }
    if (isFocus_) {
        textStyle_.SetTextColor(focusColor_);
    }

    if (textStyle_.IsAllowScale() || textStyle_.GetFontSize().Unit() == DimensionUnit::FP) {
        context->AddFontNode(AceType::WeakClaim(this));
    }
}

void RenderText::OnPaintFinish()
{
    UpdateAccessibilityText();
}

void RenderText::UpdateAccessibilityText()
{
    const auto& context = context_.Upgrade();
    if (!context) {
        return;
    }
    auto viewScale = context->GetViewScale();
    if (NearZero(viewScale)) {
        return;
    }
    auto accessibilityNode = GetAccessibilityNode().Upgrade();
    if (!accessibilityNode) {
        return;
    }
    if (GetChildren().empty()) {
        accessibilityNode->SetText(textData_);
    } else {
        std::string accessibilityText;
        for (const auto& child : GetChildren()) {
            auto renderTextSpan = AceType::DynamicCast<RenderTextSpan>(child);
            if (renderTextSpan) {
                accessibilityText += renderTextSpan->GetSpanData();
            }
        }
        accessibilityNode->SetText(accessibilityText);
    }
    if (!accessibilityNode->GetVisible()) { // Set 0 to item when whole outside of view port.
        accessibilityNode->SetWidth(0.0);
        accessibilityNode->SetHeight(0.0);
        accessibilityNode->SetTop(0.0);
        accessibilityNode->SetLeft(0.0);
        return;
    }
    if (accessibilityNode->IsValidRect()) {
        return; // Rect already clamp by viewport, no need to set again.
    }
    Size size = GetLayoutSize();
    Offset globalOffset = GetGlobalOffset();
    PositionInfo positionInfo = { (size.Width()) * viewScale, (size.Height()) * viewScale,
        (globalOffset.GetX()) * viewScale, (globalOffset.GetY()) * viewScale };
    accessibilityNode->SetPositionInfo(positionInfo);
    accessibilityNode->SetIsMultiLine(GetTextLines() > 1);
}

void RenderText::PerformLayout()
{
    auto pipelineContext = GetContext().Upgrade();
    if ((textStyle_.IsAllowScale() || textStyle_.GetFontSize().Unit() == DimensionUnit::FP) && pipelineContext &&
        !NearEqual(fontScale_, pipelineContext->GetFontScale())) {
        needMeasure_ = true;
        fontScale_ = pipelineContext->GetFontScale();
    }
    if (pipelineContext) {
        UpdateIfChanged(dipScale_, pipelineContext->GetDipScale());
    }
    Size size = Measure();
    SetLayoutSize(GetLayoutParam().Constrain(size));
    for (const auto& spanChild : GetChildren()) {
        if (spanChild) {
            const auto& param = GetLayoutParam();
            spanChild->Layout(param);
        }
    }
}

void RenderText::OnStatusChanged(OHOS::Ace::RenderStatus renderStatus)
{
    if (renderStatus == RenderStatus::FOCUS) {
        textStyle_.SetTextColor(focusColor_);
        isFocus_ = true;
    } else {
        textStyle_.SetTextColor(lostFocusColor_);
        isFocus_ = false;
    }
    needMeasure_ = true;
    Measure();
    MarkNeedRender();
}

void RenderText::CheckIfNeedMeasure(const RefPtr<TextComponent>& text)
{
    UpdateIfChanged(textData_, text->GetData());
    UpdateIfChanged(textDirection_, text->GetTextDirection());
    UpdateIfChanged(isMaxWidthLayout_, text->GetMaxWidthLayout());
    UpdateIfChanged(textStyle_, text->GetTextStyle());
    UpdateIfChanged(focusColor_, text->GetFocusColor());
    UpdateIfChanged(lostFocusColor_, textStyle_.GetTextColor());
    if (needMeasure_) {
        MarkNeedLayout();
    }
}

void RenderText::ClearRenderObject()
{
    RenderNode::ClearRenderObject();
    LOGI("TextNode ClearRenderObject");
    textData_ = "";
    textStyle_ = TextStyle();
    textDirection_ = TextDirection::LTR;
    focusColor_ = Color();
    lostFocusColor_ = Color();
    fontScale_ = 1.0;
    dipScale_ = 1.0;
    isFocus_ = false;
    isMaxWidthLayout_ = false;
    needMeasure_ = true;
    isCallbackCalled_ = false;
}

} // namespace OHOS::Ace
