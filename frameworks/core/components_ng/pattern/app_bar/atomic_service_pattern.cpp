/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/app_bar/atomic_service_pattern.h"

#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/divider/divider_render_property.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_render_property.h"

namespace OHOS::Ace::NG {
constexpr int32_t ATOMIC_SERVICE_MIN_SIZE = 2;
constexpr int32_t FIRST_OVERLAY_INDEX = 1;

void AtomicServicePattern::BeforeCreateLayoutWrapper()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<AppBarTheme>();
    CHECK_NULL_VOID(theme);
    auto menuBar = GetMenuBar();
    auto safeArea = pipeline->GetSafeArea();
    auto safeAreaLeft = safeArea.left_.Length();
    auto safeAreaRight = safeArea.right_.Length();
    if (safeAreaLeft_ != safeAreaLeft || safeAreaRight_ != safeAreaRight) {
        safeAreaLeft_ = safeAreaLeft;
        safeAreaRight_ = safeAreaRight;
        bool isRtl = AceApplicationInfo::GetInstance().IsRightToLeft();
        UpdateMenuBarLayout(theme, menuBar, isRtl);
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto manager = pipeline->GetSafeAreaManager();
    CHECK_NULL_VOID(manager);
    manager->SetIsAtomicService(true);
    manager->AddGeoRestoreNode(host);
    auto systemSafeArea = manager->GetSystemSafeArea();
    float topMargin = theme->GetMenuBarTopMargin().ConvertToPx();
    topMargin += systemSafeArea.top_.Length();
    UpdateOverlayLayout();
    auto menuBarRow = GetMenuBarRow();
    CHECK_NULL_VOID(menuBarRow);
    auto renderContext = menuBarRow->GetRenderContext();
    renderContext->UpdatePosition(OffsetT<Dimension>(0.0_vp, Dimension(topMargin, DimensionUnit::PX)));
    if (settedColorMode.has_value()) {
        UpdateMenuBarColor(theme, menuBar, settedColorMode.value());
    } else {
        UpdateMenuBarColor(theme, menuBar, SystemProperties::GetColorMode() != ColorMode::DARK);
    }
    UpdateLayoutMargin();
}

void AtomicServicePattern::UpdateLayoutMargin()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto safeArea = pipeline->GetSafeArea();
    auto atom = GetHost();
    CHECK_NULL_VOID(atom);
    MarginProperty margin;
    margin.left = CalcLength(safeArea.left_.Length());
    margin.right = CalcLength(safeArea.right_.Length());
    margin.top = CalcLength(safeArea.top_.Length());
    margin.bottom = CalcLength(safeArea.bottom_.Length());
    // update stage margin
    auto stage = AceType::DynamicCast<FrameNode>(atom->GetChildAtIndex(0));
    CHECK_NULL_VOID(stage);
    auto layoutProperty = stage->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateMargin(margin);
    stage->MarkModifyDone();
    stage->MarkDirtyNode();
}

void AtomicServicePattern::UpdateOverlayLayout()
{
    auto atom = GetHost();
    CHECK_NULL_VOID(atom);
    if (atom->GetChildren().size() <= ATOMIC_SERVICE_MIN_SIZE) {
        return;
    }
    for (int index = FIRST_OVERLAY_INDEX;
        index <= static_cast<int32_t>(atom->GetChildren().size()) - ATOMIC_SERVICE_MIN_SIZE; index++) {
        auto overlay = AceType::DynamicCast<FrameNode>(atom->GetChildAtIndex(index));
        CHECK_NULL_VOID(overlay);
        auto overlayRender = overlay->GetRenderContext();
        overlayRender->UpdatePosition(OffsetT<Dimension>());
        overlay->MarkModifyDone();
        overlay->MarkDirtyNode();
    }
}

void AtomicServicePattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_PARENT);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    host->GetRenderContext()->UpdateBackgroundColor(pipeline->GetAppBgColor());
}

void AtomicServicePattern::OnLanguageConfigurationUpdate()
{
    UpdateLayout();
}

void AtomicServicePattern::OnColorConfigurationUpdate()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    host->GetRenderContext()->UpdateBackgroundColor(pipeline->GetAppBgColor());
    if (settedColorMode.has_value()) {
        UpdateColor(settedColorMode);
    } else {
        UpdateColor(SystemProperties::GetColorMode() != ColorMode::DARK);
    }
}

RefPtr<FrameNode> AtomicServicePattern::GetMenuBarRow()
{
    auto atom = GetHost();
    CHECK_NULL_RETURN(atom, nullptr);
    auto menuBarRow = AceType::DynamicCast<FrameNode>(atom->GetChildren().back());
    return menuBarRow;
}

RefPtr<FrameNode> AtomicServicePattern::GetMenuBar()
{
    auto menuBarRow = GetMenuBarRow();
    CHECK_NULL_RETURN(menuBarRow, nullptr);
    auto menuBar = AceType::DynamicCast<FrameNode>(menuBarRow->GetChildAtIndex(0));
    return menuBar;
}

RefPtr<FrameNode> AtomicServicePattern::GetMenuButton()
{
    auto menuBar = GetMenuBar();
    CHECK_NULL_RETURN(menuBar, nullptr);
    auto menuButton = AceType::DynamicCast<FrameNode>(menuBar->GetChildAtIndex(0));
    return menuButton;
}

RefPtr<FrameNode> AtomicServicePattern::GetDivider()
{
    auto menuBar = GetMenuBar();
    CHECK_NULL_RETURN(menuBar, nullptr);
    auto divider = AceType::DynamicCast<FrameNode>(menuBar->GetChildAtIndex(1));
    return divider;
}

RefPtr<FrameNode> AtomicServicePattern::GetCloseButton()
{
    auto menuBar = GetMenuBar();
    CHECK_NULL_RETURN(menuBar, nullptr);
    auto closeButton = AceType::DynamicCast<FrameNode>(menuBar->GetChildAtIndex(2));
    return closeButton;
}

RefPtr<FrameNode> AtomicServicePattern::GetMenuIcon()
{
    auto menuButton = GetMenuButton();
    CHECK_NULL_RETURN(menuButton, nullptr);
    auto menuIcon = AceType::DynamicCast<FrameNode>(menuButton->GetChildAtIndex(0));
    return menuIcon;
}

RefPtr<FrameNode> AtomicServicePattern::GetCloseIcon()
{
    auto closeButton = GetCloseButton();
    CHECK_NULL_RETURN(closeButton, nullptr);
    auto closeIcon = AceType::DynamicCast<FrameNode>(closeButton->GetChildAtIndex(0));
    return closeIcon;
}

void AtomicServicePattern::UpdateColor(std::optional<bool> isLight)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<AppBarTheme>();
    if (!(isLight.has_value())) {
        isLight = SystemProperties::GetColorMode() != ColorMode::DARK;
    }
    auto menuButton = GetMenuButton();
    UpdateButtonColor(theme, menuButton, isLight.value());
    auto divider = GetDivider();
    UpdateDividerColor(theme, divider, isLight.value());
    auto closeButton = GetCloseButton();
    UpdateButtonColor(theme, closeButton, isLight.value());

    auto menuIcon = GetMenuIcon();
    UpdateIconColor(theme, menuIcon, isLight.value());
    auto closeIcon = GetCloseIcon();
    UpdateIconColor(theme, closeIcon, isLight.value());
}

void AtomicServicePattern::UpdateMenuBarColor(RefPtr<AppBarTheme>& theme, RefPtr<FrameNode>& menuBar, bool isLight)
{
    CHECK_NULL_VOID(theme);
    CHECK_NULL_VOID(menuBar);
    auto renderContext = menuBar->GetRenderContext();
    // background effect、border color
    EffectOption option;
    BorderColorProperty borderColor;
    option.radius = theme->GetBlurRadius();
    if (isLight) {
        option.color = theme->GetBlurColorLight();
        borderColor.SetColor(theme->GetBorderColorLight());
    } else {
        option.color = theme->GetBlurColorDark();
        borderColor.SetColor(theme->GetBorderColorDark());
    }
    renderContext->UpdateBackgroundEffect(option);
    renderContext->UpdateBorderColor(borderColor);

    menuBar->MarkModifyDone();
    menuBar->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
}

void AtomicServicePattern::UpdateButtonColor(RefPtr<AppBarTheme>& theme, RefPtr<FrameNode>& button, bool isLight)
{
    CHECK_NULL_VOID(theme);
    CHECK_NULL_VOID(button);
    // pressed color
    auto buttonPattern = button->GetPattern<ButtonPattern>();
    CHECK_NULL_VOID(buttonPattern);
    if (isLight) {
        buttonPattern->SetClickedColor(theme->GetClickEffectColorLight());
    } else {
        buttonPattern->SetClickedColor(theme->GetClickEffectColorDark());
    }
    // focus border color
    if (isLight) {
        buttonPattern->SetFocusBorderColor(theme->GetFocusedOutlineColorLight());
    } else {
        buttonPattern->SetFocusBorderColor(theme->GetFocusedOutlineColorDark());
    }

    button->MarkModifyDone();
    button->MarkDirtyNode();
}

void AtomicServicePattern::UpdateDividerColor(RefPtr<AppBarTheme>& theme, RefPtr<FrameNode>& divider, bool isLight)
{
    CHECK_NULL_VOID(theme);
    CHECK_NULL_VOID(divider);

    auto renderProperty = divider->GetPaintProperty<DividerRenderProperty>();
    if (isLight) {
        renderProperty->UpdateDividerColor(theme->GetDividerColorLight());
    } else {
        renderProperty->UpdateDividerColor(theme->GetDividerColorDark());
    }

    divider->MarkModifyDone();
    divider->MarkDirtyNode();
}

void AtomicServicePattern::UpdateIconColor(RefPtr<AppBarTheme>& theme, RefPtr<FrameNode>& icon, bool isLight)
{
    CHECK_NULL_VOID(theme);
    CHECK_NULL_VOID(icon);
    // fill color
    auto color = isLight ? theme->GetIconColorLight() : theme->GetIconColorDark();
    ACE_UPDATE_NODE_PAINT_PROPERTY(ImageRenderProperty, SvgFillColor, color, icon);
    ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColor, color, icon);
    icon->MarkModifyDone();
    icon->MarkDirtyNode();
}

void AtomicServicePattern::UpdateLayout()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<AppBarTheme>();
    CHECK_NULL_VOID(theme);
    bool isRtl = AceApplicationInfo::GetInstance().IsRightToLeft();

    auto menuBar = GetMenuBar();
    UpdateMenuBarLayout(theme, menuBar, isRtl);

    auto menuButton = GetMenuButton();
    UpdateButtonLayout(theme, menuButton, !isRtl);
    auto closeButton = GetCloseButton();
    UpdateButtonLayout(theme, closeButton, isRtl);

    auto menuIcon = GetMenuIcon();
    UpdateIconLayout(theme, menuIcon, !isRtl);
    auto closeIcon = GetCloseIcon();
    UpdateIconLayout(theme, closeIcon, isRtl);
}

void AtomicServicePattern::UpdateMenuBarLayout(RefPtr<AppBarTheme>& theme, RefPtr<FrameNode>& menuBar, bool isRtl)
{
    CHECK_NULL_VOID(theme);
    CHECK_NULL_VOID(menuBar);

    MarginProperty margin;
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto safeArea = pipeline->GetSafeArea();

    Dimension safeAreaLeft(pipeline->Px2VpWithCurrentDensity(safeArea.left_.Length()), DimensionUnit::VP);
    Dimension safeAreaRight(pipeline->Px2VpWithCurrentDensity(safeArea.right_.Length()), DimensionUnit::VP);

    if (isRtl) {
        margin.left = CalcLength(theme->GetMenuBarRightMargin() + safeAreaLeft);
        margin.right = CalcLength(theme->GetMenuBarLeftMargin() + safeAreaRight);
    } else {
        margin.left = CalcLength(theme->GetMenuBarLeftMargin() + safeAreaLeft);
        margin.right = CalcLength(theme->GetMenuBarRightMargin() + safeAreaRight);
    }
    menuBar->GetLayoutProperty<LinearLayoutProperty>()->UpdateMargin(margin);

    menuBar->MarkModifyDone();
    menuBar->MarkDirtyNode();
}

void AtomicServicePattern::UpdateButtonLayout(RefPtr<AppBarTheme>& theme, RefPtr<FrameNode>& button, bool isLeft)
{
    CHECK_NULL_VOID(theme);
    CHECK_NULL_VOID(button);

    auto bent = theme->GetBentRadius();
    auto rightAngle = theme->GetRightAngle();
    auto leftBorderRadius = BorderRadiusProperty(bent, rightAngle, rightAngle, bent);
    auto rightBorderRadius = BorderRadiusProperty(rightAngle, bent, bent, rightAngle);

    auto layoutProperty = button->GetLayoutProperty<ButtonLayoutProperty>();
    layoutProperty->UpdateBorderRadius(isLeft ? leftBorderRadius : rightBorderRadius);

    button->MarkModifyDone();
    button->MarkDirtyNode();
}

void AtomicServicePattern::UpdateIconLayout(RefPtr<AppBarTheme>& theme, RefPtr<FrameNode>& icon, bool isLeft)
{
    CHECK_NULL_VOID(theme);
    CHECK_NULL_VOID(icon);

    MarginProperty margin;
    margin.top = CalcLength(theme->GetIconVerticalMargin());
    margin.bottom = CalcLength(theme->GetIconVerticalMargin());
    if (isLeft) {
        margin.left = CalcLength(theme->GetIconOutsideMargin());
        margin.right = CalcLength(theme->GetIconInsideMargin());
    } else {
        margin.left = CalcLength(theme->GetIconInsideMargin());
        margin.right = CalcLength(theme->GetIconOutsideMargin());
    }
    auto layoutProperty = icon->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateMargin(margin);

    icon->MarkModifyDone();
    icon->MarkDirtyNode();
}
} // namespace OHOS::Ace::NG
