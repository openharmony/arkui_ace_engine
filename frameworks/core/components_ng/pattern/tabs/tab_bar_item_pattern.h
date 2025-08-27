/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TABS_TAB_BAR_ITEM_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TABS_TAB_BAR_ITEM_PATTERN_H

#include "core/components/focus_animation/focus_animation_theme.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/tabs/tab_bar_item_accessibility_property.h"

namespace OHOS::Ace::NG {
const auto TWO = 2;

class TabBarItemPattern : public LinearLayoutPattern {
    DECLARE_ACE_TYPE(TabBarItemPattern, LinearLayoutPattern);

public:
    TabBarItemPattern() : LinearLayoutPattern(true) {}

    ~TabBarItemPattern() override = default;

    RefPtr<AccessibilityProperty> CreateAccessibilityProperty() override
    {
        return MakeRefPtr<TabBarItemAccessibilityProperty>();
    }

    FocusPattern GetFocusPattern() const override
    {
        auto host = GetHost();
        CHECK_NULL_RETURN(host, FocusPattern());
        auto pipeline = host->GetContext();
        CHECK_NULL_RETURN(pipeline, FocusPattern());
        auto focusTheme = pipeline->GetTheme<FocusAnimationTheme>();
        CHECK_NULL_RETURN(focusTheme, FocusPattern());
        auto tabTheme = pipeline->GetTheme<TabTheme>();
        CHECK_NULL_RETURN(tabTheme, FocusPattern());
        FocusPaintParam focusPaintParam;
        focusPaintParam.SetPaintWidth(tabTheme->GetActiveIndicatorWidth());
        focusPaintParam.SetPaintColor(focusTheme->GetColor());
        return { FocusType::SCOPE, true, FocusStyleType::CUSTOM_REGION, focusPaintParam };
    }

    void OnAttachToMainTree() override
    {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto focusHub = host->GetFocusHub();
        CHECK_NULL_VOID(focusHub);
        focusHub->SetFocusable(true, false);
        focusHub->SetInnerFocusPaintRectCallback([weak = WeakClaim(this)](RoundRect& paintRect) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->GetInnerFocusPaintRect(paintRect);

            auto host = pattern->GetHost();
            CHECK_NULL_VOID(host);
            auto tabBar = host->GetAncestorNodeOfFrame(false);
            CHECK_NULL_VOID(tabBar);
            auto tabBarPattern = tabBar->GetPattern<TabBarPattern>();
            CHECK_NULL_VOID(tabBarPattern);
            auto index = tabBar->GetChildFlatIndex(host->GetId()).second;
            tabBarPattern->SetFocusIndicator(index);
        });
    }

    void GetInnerFocusPaintRect(RoundRect& paintRect)
    {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto focusHub = host->GetFocusHub();
        CHECK_NULL_VOID(focusHub);
        auto tabBar = host->GetAncestorNodeOfFrame(false);
        CHECK_NULL_VOID(tabBar);
        auto tabBarFocusHub = tabBar->GetFocusHub();
        CHECK_NULL_VOID(tabBarFocusHub);
        auto renderContext = host->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        auto columnPaintRect = renderContext->GetPaintRectWithTransform();
        auto pipeline = GetContext();
        CHECK_NULL_VOID(pipeline);
        auto tabTheme = pipeline->GetTheme<TabTheme>();
        CHECK_NULL_VOID(tabTheme);
        auto padding = tabTheme->GetFocusPadding();
        BorderRadiusProperty borderRadius;
        borderRadius.SetRadius(tabTheme->GetFocusIndicatorRadius());
        auto radius = renderContext->GetBorderRadius().value_or(borderRadius);
        if (tabBarFocusHub->GetFocusBox().HasCustomStyle()) {
            auto tabBarFocusBoxStyle = tabBarFocusHub->GetFocusBox().GetStyle().value();
            focusHub->GetFocusBox().SetStyle(tabBarFocusBoxStyle);
            auto margin = tabBarFocusBoxStyle.margin.value_or(CalcDimension(0.0));
            columnPaintRect.SetOffset(OffsetF(-margin.ConvertToPx(), -margin.ConvertToPx()));
            columnPaintRect.SetSize(SizeF((columnPaintRect.GetSize().Width() + margin.ConvertToPx() * TWO),
                (columnPaintRect.GetSize().Height() + margin.ConvertToPx() * TWO)));
        } else {
            FocusBoxStyle tabBarFocusBoxStyle;
            focusHub->GetFocusBox().SetStyle(tabBarFocusBoxStyle);
            auto outLineWidth = tabTheme->GetActiveIndicatorWidth().ConvertToPx() - padding.ConvertToPx() * TWO;
            columnPaintRect.SetOffset(OffsetF(outLineWidth / TWO, outLineWidth / TWO));
            columnPaintRect.SetSize(SizeF((columnPaintRect.GetSize().Width() - outLineWidth),
                (columnPaintRect.GetSize().Height() - outLineWidth)));
        }

        paintRect.SetRect(columnPaintRect);
        SetFocusRectRadius(paintRect, radius, padding, *tabTheme);
    }

    void SetFocusRectRadius(RoundRect& paintRect, BorderRadiusProperty& radius, Dimension& padding, TabTheme& tabTheme)
    {
        auto focusBorderWidth = tabTheme.GetActiveIndicatorWidth();
        if (focusBorderWidth > 0.0_vp && padding > focusBorderWidth) {
            padding -= focusBorderWidth;
        }
        paintRect.SetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS,
            static_cast<float>(radius.radiusTopLeft->ConvertToPx() + padding.ConvertToPx()),
            static_cast<float>(radius.radiusTopLeft->ConvertToPx() + padding.ConvertToPx()));
        paintRect.SetCornerRadius(RoundRect::CornerPos::TOP_RIGHT_POS,
            static_cast<float>(radius.radiusTopRight->ConvertToPx() + padding.ConvertToPx()),
            static_cast<float>(radius.radiusTopRight->ConvertToPx() + padding.ConvertToPx()));
        paintRect.SetCornerRadius(RoundRect::CornerPos::BOTTOM_LEFT_POS,
            static_cast<float>(radius.radiusBottomLeft->ConvertToPx() + padding.ConvertToPx()),
            static_cast<float>(radius.radiusBottomLeft->ConvertToPx() + padding.ConvertToPx()));
        paintRect.SetCornerRadius(RoundRect::CornerPos::BOTTOM_RIGHT_POS,
            static_cast<float>(radius.radiusBottomRight->ConvertToPx() + padding.ConvertToPx()),
            static_cast<float>(radius.radiusBottomRight->ConvertToPx() + padding.ConvertToPx()));
    }

private:
    ACE_DISALLOW_COPY_AND_MOVE(TabBarItemPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TABS_TAB_BAR_ITEM_PATTERN_H
