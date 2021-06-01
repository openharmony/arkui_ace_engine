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

#include "core/components/badge/render_badge.h"

#include "base/log/event_report.h"
#include "core/common/font_manager.h"
#include "core/components/common/properties/alignment.h"
#include "core/event/ace_event_helper.h"

namespace OHOS::Ace {

RenderBadge::RenderBadge()
{
    clickRecognizer_ = AceType::MakeRefPtr<ClickRecognizer>();
    clickRecognizer_->SetOnClick([wp = AceType::WeakClaim(this)](const ClickInfo&) {
        auto badge = wp.Upgrade();
        if (badge) {
            badge->HandleClickEvent();
        }
    });
}

RenderBadge::~RenderBadge()
{
    auto context = context_.Upgrade();
    if (context) {
        context->RemoveFontNode(WeakClaim(this));
        auto fontManager = context->GetFontManager();
        if (fontManager) {
            fontManager->RemoveVariationNode(WeakClaim(this));
        }
    }
}

void RenderBadge::HandleClickEvent()
{
    if (onClick_) {
        onClick_();
    }
}

void RenderBadge::OnTouchTestHit(
    const Offset& coordinateOffset, const TouchRestrict& touchRestrict, TouchTestResult& result)
{
    if (!clickRecognizer_) {
        return;
    }
    result.emplace_back(clickRecognizer_);
}

void RenderBadge::Update(const RefPtr<Component>& component)
{
    badge_ = AceType::DynamicCast<BadgeComponent>(component);
    if (!badge_) {
        LOGE("Update error, badge component is null");
        EventReport::SendRenderException(RenderExcepType::RENDER_COMPONENT_ERR);
        return;
    }
    badgeColor_ = badge_->GetBadgeColor();
    badgePosition_ = badge_->GetBadgePosition();
    messageCount_ = badge_->GetMessageCount();
    showMessage_ = badge_->IsShowMessage();
    countLimit_ = badge_->GetMaxCount();
    padding_ = badge_->GetPadding();
    badgeCircleSizeDefined_ = badge_->IsBadgeCircleSizeDefined();
    badgeCircleSize_ = badge_->GetBadgeCicleSize();
    badgeChildInitialOffset_ = Offset(NormalizeToPx(padding_.Left()), NormalizeToPx(padding_.Top()));
    onClick_ = AceAsyncEvent<void()>::Create(badge_->GetClickEvent(), context_);
    badgeLabel_ = badge_->GetBadgeLabel();
    if (badgeLabel_.empty()) {
        if (messageCount_ > 0) {
            if (messageCount_ > countLimit_) {
                textData_ = std::to_string(countLimit_) + '+';
            } else {
                textData_ = std::to_string(messageCount_);
            }
        }
    } else {
        textData_ = badgeLabel_;
    }
    badgeTextComponent_ = AceType::MakeRefPtr<TextComponent>(textData_);
    if (!badgeRenderText_) {
        InitialBadgeText();
    }
    UpdateBadgeText();
}

void RenderBadge::PerformLayout()
{
    if (!GetChildren().front()) {
        SetLayoutSize(Size());
        showMessage_ = false;
        return;
    }

    auto context = context_.Upgrade();
    if (context) {
        dipScale_ = context->GetDipScale();
    }

    // child layout
    LayoutParam layoutParam = GetLayoutParam();
    Size minSize = layoutParam.GetMinSize();
    Size maxSize = layoutParam.GetMaxSize();
    LayoutParam innerLayoutParam = layoutParam;
    Size paddingSize = padding_.GetLayoutSizeInPx(dipScale_);
    innerLayoutParam.SetMinSize(minSize - paddingSize);
    innerLayoutParam.SetMaxSize(maxSize - paddingSize);
    double maxWidth = minSize.Width();
    double maxHeight = minSize.Height();
    if (!GetChildren().empty()) {
        auto child = GetChildren().front();
        child->Layout(innerLayoutParam);
        maxWidth = std::max(maxWidth, child->GetLayoutSize().Width() + paddingSize.Width());
        maxHeight = std::max(maxHeight, child->GetLayoutSize().Height() + paddingSize.Height());
    }

    // calculate self layout size
    if (maxSize.IsInfinite()) {
        // same with child size
        badgeSize_ = Size(maxWidth, maxHeight);
    } else {
        badgeSize_ = maxSize;
    }
    if (!badgeSize_.IsValid()) {
        badgeSize_ = Size();
        showMessage_ = false;
    }
    SetLayoutSize(badgeSize_);
    width_ = badgeSize_.Width();
    height_ = badgeSize_.Height();
}

void RenderBadge::InitialBadgeText()
{
    badgeRenderText_ = AceType::DynamicCast<RenderText>(badgeTextComponent_->CreateRenderNode());
    LayoutParam innerLayout;
    innerLayout.SetMaxSize(Size(Size::INFINITE_SIZE, Size::INFINITE_SIZE));
    badgeRenderText_->Attach(GetContext());
    badgeRenderText_->Update(badgeTextComponent_);
    badgeRenderText_->SetLayoutParam(innerLayout);
}

void RenderBadge::UpdateBadgeText()
{
    auto context = context_.Upgrade();
    if (context) {
        auto fontManager = context->GetFontManager();
        if (fontManager) {
            fontManager->AddVariationNode(WeakClaim(this));
        }
    }
    badgeTextColor_ = badge_->GetBadgeTextColor();
    badgeFontSize_ = badge_->GetBadgeFontSize();
    textStyle_.SetTextColor(badgeTextColor_);
    textStyle_.SetFontSize(badgeFontSize_);
    textStyle_.SetAllowScale(false);
    badgeTextComponent_->SetData(textData_);
    badgeTextComponent_->SetTextStyle(textStyle_);
    badgeRenderText_->Update(badgeTextComponent_);
}

} // namespace OHOS::Ace
