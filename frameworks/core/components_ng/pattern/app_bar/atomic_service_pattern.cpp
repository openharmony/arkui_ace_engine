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

#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/measure_property.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
void AtomicServicePattern::BeforeCreateLayoutWrapper()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto safeArea = pipeline->GetSafeArea();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto manager = pipeline->GetSafeAreaManager();
    CHECK_NULL_VOID(manager);
    manager->SetIsAtomicService(true);
    PaddingProperty padding {
        .left = CalcLength(safeArea.left_.Length()),
        .right = CalcLength(safeArea.right_.Length()),
        .top = CalcLength(safeArea.top_.Length()),
        .bottom = CalcLength(safeArea.bottom_.Length()),
    };
    host->GetLayoutProperty()->UpdatePadding(padding);
    auto systemSafeArea = manager->GetSystemSafeArea();
    if (safeArea.top_.Length() != systemSafeArea.top_.Length()) {
        auto menuBarRow = DynamicCast<FrameNode>(host->GetChildAtIndex(1));
        auto renderContext = menuBarRow->GetRenderContext();
        auto appBarTheme = pipeline->GetTheme<AppBarTheme>();
        CHECK_NULL_VOID(appBarTheme);
        float topMargin = appBarTheme->GetMenuBarTopMargin().ConvertToPx() + systemSafeArea.top_.Length();
        renderContext->UpdatePosition(OffsetT<Dimension>(0.0_vp, Dimension(topMargin, DimensionUnit::PX)));
        menuBarRow->MarkModifyDone();
        menuBarRow->MarkDirtyNode();
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
    UpdateRowLayout();
}

void AtomicServicePattern::OnColorConfigurationUpdate()
{
    auto node = GetHost();
    CHECK_NULL_VOID(node);
    auto row = node->GetLastChild();
    CHECK_NULL_VOID(row);
    row->SetNeedCallChildrenUpdate(false);
    UpdateColor();
}

RefPtr<FrameNode> AtomicServicePattern::GetMenuBarRow()
{
    auto atom = GetHost();
    CHECK_NULL_RETURN(atom, nullptr);
    auto menuBarRow = AceType::DynamicCast<FrameNode>(atom->GetChildAtIndex(1));
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

void AtomicServicePattern::UpdateColor()
{
    // get theme
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto appBarTheme = pipeline->GetTheme<AppBarTheme>();
    CHECK_NULL_VOID(appBarTheme);
    // set icon color
    auto menuIcon = GetMenuIcon();
    CHECK_NULL_VOID(menuIcon);
    SetEachIconColor(menuIcon, appBarTheme->GetIconColor(), InternalResource::ResourceId::APP_BAR_MENU_SVG);
    auto closeIcon = GetCloseIcon();
    CHECK_NULL_VOID(closeIcon);
    SetEachIconColor(closeIcon, appBarTheme->GetIconColor(), InternalResource::ResourceId::APP_BAR_CLOSE_SVG);
    // set background color
    auto menuBar = GetMenuBar();
    CHECK_NULL_VOID(menuBar);
    auto menuBarRenderContext = menuBar->GetRenderContext();
    BlurStyleOption option;
    option.blurStyle = SystemProperties::GetColorMode() == ColorMode::DARK ? BlurStyle::COMPONENT_ULTRA_THICK
                                                                           : BlurStyle::COMPONENT_THIN;
    menuBarRenderContext->UpdateBackBlurStyle(option);
    // set border color
    BorderColorProperty borderColorProperty;
    borderColorProperty.SetColor(appBarTheme->GetBorderColor());
    menuBarRenderContext->UpdateBorderColor(borderColorProperty);
    menuBar->MarkModifyDone();
    menuBar->MarkDirtyNode();
}

void AtomicServicePattern::UpdateRowLayout()
{
    bool isRtl = AceApplicationInfo::GetInstance().IsRightToLeft();
    // get theme
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto appBarTheme = pipeline->GetTheme<AppBarTheme>();
    CHECK_NULL_VOID(appBarTheme);
    // set margin
    auto menuBar = GetMenuBar();
    CHECK_NULL_VOID(menuBar);
    MarginProperty menuBarMargin;
    if (isRtl) {
        menuBarMargin.left = CalcLength(appBarTheme->GetMenuBarRightMargin());
        menuBarMargin.right = CalcLength(appBarTheme->GetMenuBarLeftMargin());
    } else {
        menuBarMargin.left = CalcLength(appBarTheme->GetMenuBarLeftMargin());
        menuBarMargin.right = CalcLength(appBarTheme->GetMenuBarRightMargin());
    }
    menuBar->GetLayoutProperty<LinearLayoutProperty>()->UpdateMargin(menuBarMargin);
    menuBar->MarkModifyDone();
    menuBar->MarkDirtyNode();

    auto menuIcon = GetMenuIcon();
    CHECK_NULL_VOID(menuIcon);
    auto closeIcon = GetCloseIcon();
    CHECK_NULL_VOID(closeIcon);
    MarginProperty menuIconMargin;
    MarginProperty closeIconMargin;
    menuIconMargin.top = CalcLength(appBarTheme->GetIconVerticalMargin());
    menuIconMargin.bottom = CalcLength(appBarTheme->GetIconVerticalMargin());
    closeIconMargin.top = CalcLength(appBarTheme->GetIconVerticalMargin());
    closeIconMargin.bottom = CalcLength(appBarTheme->GetIconVerticalMargin());
    if (isRtl) {
        menuIconMargin.left = CalcLength(appBarTheme->GetIconInsideMargin());
        menuIconMargin.right = CalcLength(appBarTheme->GetIconOutsideMargin());
        closeIconMargin.left = CalcLength(appBarTheme->GetIconOutsideMargin());
        closeIconMargin.right = CalcLength(appBarTheme->GetIconInsideMargin());
    } else {
        menuIconMargin.left = CalcLength(appBarTheme->GetIconOutsideMargin());
        menuIconMargin.right = CalcLength(appBarTheme->GetIconInsideMargin());
        closeIconMargin.left = CalcLength(appBarTheme->GetIconInsideMargin());
        closeIconMargin.right = CalcLength(appBarTheme->GetIconOutsideMargin());
    }
    menuIcon->GetLayoutProperty<ImageLayoutProperty>()->UpdateMargin(menuIconMargin);
    closeIcon->GetLayoutProperty<ImageLayoutProperty>()->UpdateMargin(closeIconMargin);

    menuIcon->MarkModifyDone();
    menuIcon->MarkDirtyNode();
    closeIcon->MarkModifyDone();
    closeIcon->MarkDirtyNode();
}

void AtomicServicePattern::SetEachIconColor(
    RefPtr<FrameNode> icon, const std::optional<Color>& color, InternalResource::ResourceId image)
{
    CHECK_NULL_VOID(icon);
    ImageSourceInfo info;
    if (color.has_value()) {
        info.SetResourceId(image, color);
    } else {
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto appBarTheme = pipeline->GetTheme<AppBarTheme>();
        info.SetResourceId(image, appBarTheme->GetTextColor());
    }
    icon->GetLayoutProperty<ImageLayoutProperty>()->UpdateImageSourceInfo(info);
    icon->MarkModifyDone();
    icon->MarkDirtyNode();
}
} // namespace OHOS::Ace::NG
