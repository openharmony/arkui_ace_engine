/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "bridge/cj_frontend/frontend/cj_app_bar_utils.h"

#include <cstddef>
#include <cstdint>
#include <string>

#include "ui/base/geometry/dimension.h"
#include "ui/base/utils/utils.h"

#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/common/app_bar_helper.h"
#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "core/components_ng/base/inspector.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/focus_hub.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/app_bar/app_bar_theme.h"
#include "core/components_ng/pattern/app_bar/app_bar_utils.h"
#include "core/components_ng/pattern/app_bar/atomic_service_layout_algorithm.h"
#include "core/components_ng/pattern/app_bar/atomic_service_pattern.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/custom/custom_app_bar_node.h"
#include "core/components_ng/pattern/divider/divider_pattern.h"
#include "core/components_ng/pattern/divider/divider_render_property.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_render_property.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"

namespace OHOS::Ace::NG {
constexpr int32_t ATOMIC_SERVICE_MIN_SIZE = 2;
constexpr int32_t FIRST_OVERLAY_INDEX = 1;
constexpr double MENU_BAR_OFFSET = 8.0;

namespace {
OHOS::Ace::RefPtr<OHOS::Ace::NG::AppBarTheme> GetAppBarTheme()
{
    auto pipeline = OHOS::Ace::PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, nullptr);
    return pipeline->GetTheme<OHOS::Ace::NG::AppBarTheme>();
}

OHOS::Ace::RefPtr<FrameNode> BuildDivider()
{
    auto divider = FrameNode::CreateFrameNode(
        V2::DIVIDER_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<DividerPattern>());
    auto theme = GetAppBarTheme();
    CHECK_NULL_RETURN(theme, nullptr);

    auto layoutProperty = divider->GetLayoutProperty<DividerLayoutProperty>();
    // size
    layoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(theme->GetDividerWidth()), CalcLength(theme->GetDividerHeight())));
    // direction
    layoutProperty->UpdateVertical(true);
    // stroke width
    layoutProperty->UpdateStrokeWidth(theme->GetDividerWidth());
    // marigin
    MarginProperty margin;
    margin.left = CalcLength(-(theme->GetDividerWidth()));
    auto renderProperty = divider->GetPaintProperty<DividerRenderProperty>();
    // line cap
    renderProperty->UpdateLineCap(LineCap::ROUND);

    divider->MarkModifyDone();
    return divider;
}

RefPtr<FrameNode> BuildIcon(bool isMenuIcon)
{
    auto icon = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    auto theme = GetAppBarTheme();
    CHECK_NULL_RETURN(theme, nullptr);

    ImageSourceInfo imageSourceInfo;
    imageSourceInfo.SetResourceId(
        isMenuIcon ? InternalResource::ResourceId::APP_BAR_MENU_SVG : InternalResource::ResourceId::APP_BAR_CLOSE_SVG);
    auto layoutProperty = icon->GetLayoutProperty<ImageLayoutProperty>();
    layoutProperty->UpdateImageSourceInfo(imageSourceInfo);
    // size
    layoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(theme->GetNewIconSize()), CalcLength(theme->GetNewIconSize())));
    // focusable
    auto focusHub = icon->GetFocusHub();
    CHECK_NULL_RETURN(focusHub, nullptr);
    focusHub->SetFocusable(true);

    icon->MarkModifyDone();
    return icon;
}

OHOS::Ace::RefPtr<FrameNode> BuildButton(bool isMenuButton)
{
    auto button = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    auto renderContext = button->GetRenderContext();
    renderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    auto theme = GetAppBarTheme();
    CHECK_NULL_RETURN(theme, nullptr);

    auto icon = BuildIcon(isMenuButton);
    button->AddChild(icon);

    auto layoutProperty = button->GetLayoutProperty<ButtonLayoutProperty>();
    // type
    layoutProperty->UpdateType(ButtonType::NORMAL);
    // size
    layoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(theme->GetButtonWidth()), CalcLength(theme->GetButtonHeight())));
    // focus style type
    auto focusHub = button->GetFocusHub();
    CHECK_NULL_RETURN(focusHub, nullptr);
    focusHub->SetFocusStyleType(FocusStyleType::INNER_BORDER);
    // focus border width
    auto buttonPattern = button->GetPattern<ButtonPattern>();
    CHECK_NULL_RETURN(buttonPattern, nullptr);
    buttonPattern->SetFocusBorderWidth(theme->GetFocusedOutlineWidth());

    button->MarkModifyDone();
    return button;
}

void BindCloseCallback(const OHOS::Ace::RefPtr<FrameNode>& closeButton)
{
    auto clickCallback = [](GestureEvent& info) {
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto container = Container::Current();
        CHECK_NULL_VOID(container);
        if (container->IsUIExtensionWindow()) {
            container->TerminateUIExtension();
        } else {
            auto windowManager = pipeline->GetWindowManager();
            CHECK_NULL_VOID(windowManager);
            windowManager->WindowPerformBack();
        }
    };
    auto eventHub = closeButton->GetOrCreateGestureEventHub();
    if (eventHub) {
        eventHub->AddClickEvent(AceType::MakeRefPtr<ClickEvent>(std::move(clickCallback)));
    }
}

void BindMenuCallback(const RefPtr<FrameNode>& menuButton, AppBarView* appbar, const RefPtr<FrameNode>& stage)
{
    WeakPtr<FrameNode> node = stage;
    auto clickCallback = [wp = AccessibilityManager::WeakClaim(appbar), node](GestureEvent& info) {
        LOGW("[Engine Log] Unable to show the SharePanel in the Previewer. "
             "Perform this operation on the emulator or a real device instead.");
        auto appbarView = wp.Upgrade();
        CHECK_NULL_VOID(appbarView);
        auto nodeTemp = node.Upgrade();
        auto pipeline = nodeTemp->GetContext();
        CHECK_NULL_VOID(pipeline);
        auto theme = pipeline->GetTheme<AppBarTheme>();
        CHECK_NULL_VOID(theme);
        if (SystemProperties::GetExtSurfaceEnabled()) {
            LOGI("start panel bundleName is %{public}s, abilityName is %{public}s", theme->GetBundleName().c_str(),
                theme->GetAbilityName().c_str());
            pipeline->FireSharePanelCallback(theme->GetBundleName(), theme->GetAbilityName());
        } else {
            std::string abilityName;
            std::string appGalleryBundleName;
            std::map<std::string, std::string> params;
            if (theme) {
                abilityName = theme->GetStageAbilityName();
            }
            auto missionId = AceApplicationInfo::GetInstance().GetMissionId();
            params.try_emplace("bundleName", AceApplicationInfo::GetInstance().GetProcessName());
            params.try_emplace("abilityName", AceApplicationInfo::GetInstance().GetAbilityName());
            params.try_emplace("module", Container::Current()->GetModuleName());
            if (missionId != -1) {
                params.try_emplace("missionId", std::to_string(missionId));
            }
            params.try_emplace("ability.want.params.uiExtensionType", "sysDialog/atomicServicePanel");
            appGalleryBundleName = OHOS::Ace::SystemProperties::GetAtomicServiceBundleName();
            appbarView->CreateServicePanel(appGalleryBundleName, abilityName, params);
        }
    };
    auto eventHub = menuButton->GetOrCreateGestureEventHub();
    if (eventHub) {
        eventHub->AddClickEvent(AceType::MakeRefPtr<ClickEvent>(std::move(clickCallback)));
    }
}

OHOS::Ace::RefPtr<FrameNode> BuildMenuBar(AppBarView* appbar, const RefPtr<FrameNode>& stage)
{
    auto menuBar = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    auto theme = GetAppBarTheme();
    CHECK_NULL_RETURN(theme, nullptr);

    auto menuButton = BuildButton(true);
    BindMenuCallback(menuButton, appbar, stage);
    menuBar->AddChild(menuButton);
    auto divider = BuildDivider();
    menuBar->AddChild(divider);
    auto closeButton = BuildButton(false);
    BindCloseCallback(closeButton);
    menuBar->AddChild(closeButton);

    auto layoutProperty = menuBar->GetLayoutProperty<LinearLayoutProperty>();
    auto renderContext = menuBar->GetRenderContext();
    // main axis align
    layoutProperty->UpdateMainAxisAlign(FlexAlign::FLEX_START);
    // border width
    BorderWidthProperty borderWidth;
    borderWidth.SetBorderWidth(theme->GetBorderWidth());
    layoutProperty->UpdateBorderWidth(borderWidth);
    MarginProperty margin;
    margin.right = CalcLength(MENU_BAR_OFFSET, DimensionUnit::VP);
    layoutProperty->UpdateMargin(margin);
    renderContext->UpdateBorderWidth(borderWidth);
    // border radius
    auto bent = theme->GetBentRadius();
    renderContext->UpdateBorderRadius(BorderRadiusProperty(bent));

    menuBar->MarkModifyDone();
    return menuBar;
}

void UpdateMenuBarLayout(RefPtr<AppBarTheme>& theme, RefPtr<FrameNode>& menuBar, bool isRtl)
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

void UpdateOverlayLayout(RefPtr<FrameNode> atom)
{
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

RefPtr<FrameNode> GetMenuBarRow(RefPtr<FrameNode> host)
{
    return AceType::DynamicCast<FrameNode>(host->GetChildren().back());
}

RefPtr<FrameNode> GetMenuBar(RefPtr<FrameNode> host)
{
    auto menuBarRow = GetMenuBarRow(host);
    CHECK_NULL_RETURN(menuBarRow, nullptr);
    return AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(0));
}

void UpdateLayoutMargin(RefPtr<FrameNode> atom)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto safeArea = pipeline->GetSafeArea();

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

void UpdateMenuBarColor(RefPtr<AppBarTheme>& theme, RefPtr<FrameNode>& menuBar, bool isLight)
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

} // namespace

RefPtr<FrameNode> BuildMenuBarRow(AppBarView* appbar, const RefPtr<FrameNode>& stage)
{
    auto atom = FrameNode::CreateFrameNode(V2::ATOMIC_SERVICE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<AtomicServicePattern>());
    atom->AddChild(stage);

    auto menuBarRow = FrameNode::CreateFrameNode(V2::APP_BAR_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    auto theme = GetAppBarTheme();
    CHECK_NULL_RETURN(theme, nullptr);

    auto menuBar = BuildMenuBar(appbar, stage);
    menuBarRow->AddChild(menuBar);
    auto layoutProperty = menuBarRow->GetLayoutProperty<LinearLayoutProperty>();
    auto renderContext = menuBarRow->GetRenderContext();
    // size
    layoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(1.0, DimensionUnit::PERCENT), CalcLength(theme->GetMenuBarHeight())));
    // main axis align
    layoutProperty->UpdateMainAxisAlign(FlexAlign::FLEX_END);
    // position
    renderContext->UpdatePosition(OffsetT<Dimension>(0.0_vp, theme->GetMenuBarTopMargin()));
    // background color
    renderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    // hit test mode
    menuBarRow->SetHitTestMode(HitTestMode::HTMTRANSPARENT_SELF);

    menuBarRow->MarkModifyDone();
    atom->AddChild(menuBarRow);

    atom->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_PARENT);
    stage->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_PARENT);
    auto pattern = atom->GetPattern<AtomicServicePattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    return atom;
}

void SetRegisterBeforeCreateLayoutBuilder(RefPtr<FrameNode> host, std::optional<bool> settedColorMode)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<AppBarTheme>(host);
    CHECK_NULL_VOID(theme);
    auto menuBar = GetMenuBar(host);
    auto safeArea = pipeline->GetSafeArea();
    auto safeAreaLeft = safeArea.left_.Length();
    auto safeAreaRight = safeArea.right_.Length();
    uint32_t safeAreaLeftDefault = 0;
    uint32_t safeAreaRightDefault = 0;
    if (safeAreaLeftDefault != safeAreaLeft || safeAreaRightDefault != safeAreaRight) {
        if (safeAreaLeftDefault != safeAreaLeft || safeAreaRightDefault != safeAreaRight) {
            safeAreaLeftDefault = safeAreaLeft;
            safeAreaRightDefault = safeAreaRight;
            bool isRtl = AceApplicationInfo::GetInstance().IsRightToLeft();
            UpdateMenuBarLayout(theme, menuBar, isRtl);
        }

        auto manager = pipeline->GetSafeAreaManager();

        manager->SetIsAtomicService(true);
        manager->AddGeoRestoreNode(host);
        auto systemSafeArea = manager->GetSystemSafeArea();
        float topMargin = theme->GetMenuBarTopMargin().ConvertToPx();
        topMargin += systemSafeArea.top_.Length();
        UpdateOverlayLayout(host);
        auto menuBarRow = GetMenuBarRow(host);
        CHECK_NULL_VOID(menuBarRow);
        auto renderContext = menuBarRow->GetRenderContext();
        renderContext->UpdatePosition(OffsetT<Dimension>(0.0_vp, Dimension(topMargin, DimensionUnit::PX)));
        if (settedColorMode.has_value()) {
            UpdateMenuBarColor(theme, menuBar, settedColorMode.value());
        }
        UpdateLayoutMargin(host);
    }
}

} // namespace OHOS::Ace::NG
