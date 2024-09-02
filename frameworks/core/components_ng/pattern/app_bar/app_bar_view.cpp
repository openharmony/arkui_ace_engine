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

#include "core/components_ng/pattern/app_bar/app_bar_view.h"

#include "core/common/app_bar_helper.h"
#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/focus_hub.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/app_bar/atomic_service_pattern.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/divider/divider_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"

namespace OHOS::Ace::NG {
namespace {
RefPtr<AppBarTheme> GetAppBarTheme()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    return pipeline->GetTheme<AppBarTheme>();
}

#ifndef PREVIEW
void AssembleUiExtensionParams(
    bool firstTry, std::string& appGalleryBundleName, std::map<std::string, std::string>& params)
{
    auto missionId = AceApplicationInfo::GetInstance().GetMissionId();
    params.try_emplace("bundleName", AceApplicationInfo::GetInstance().GetProcessName());
    params.try_emplace("abilityName", AceApplicationInfo::GetInstance().GetAbilityName());
    params.try_emplace("module", Container::Current()->GetModuleName());
    if (missionId != -1) {
        params.try_emplace("missionId", std::to_string(missionId));
    }

    if (firstTry) {
        params.try_emplace("ability.want.params.uiExtensionType", "sysDialog/atomicServicePanel");
        appGalleryBundleName = OHOS::Ace::SystemProperties::GetAtomicServiceBundleName();
    } else {
        params.try_emplace("ability.want.params.uiExtensionType", "sys/commonUI");
        appGalleryBundleName = OHOS::Ace::AppBarHelper::QueryAppGalleryBundleName();
    }
}
#endif
} // namespace

RefPtr<FrameNode> AppBarView::Create(const RefPtr<FrameNode>& stage)
{
    auto atom = FrameNode::CreateFrameNode(V2::ATOMIC_SERVICE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<AtomicServicePattern>());
    // add children
    auto menuBarRow = BuildMenuBarRow();
    atom->AddChild(stage);
    atom->AddChild(menuBarRow);
    // init
    atom->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_PARENT);
    stage->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_PARENT);
    atomicService_ = atom;
    auto pattern = atom->GetPattern<AtomicServicePattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    pattern->UpdateColor(std::nullopt);
    pattern->UpdateLayout();
    return atom;
}

RefPtr<FrameNode> AppBarView::BuildMenuBarRow()
{
    auto menuBarRow = FrameNode::CreateFrameNode(V2::APP_BAR_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    auto theme = GetAppBarTheme();
    CHECK_NULL_RETURN(theme, nullptr);

    auto menuBar = BuildMenuBar();
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
    return menuBarRow;
}

RefPtr<FrameNode> AppBarView::BuildMenuBar()
{
    auto menuBar = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    auto theme = GetAppBarTheme();
    CHECK_NULL_RETURN(theme, nullptr);

    auto menuButton = BuildButton(true);
    BindMenuCallback(menuButton);
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
    renderContext->UpdateBorderWidth(borderWidth);
    // border radius
    auto bent = theme->GetBentRadius();
    renderContext->UpdateBorderRadius(BorderRadiusProperty(bent));

    menuBar->MarkModifyDone();
    return menuBar;
}

RefPtr<FrameNode> AppBarView::BuildButton(bool isMenuButton)
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

RefPtr<FrameNode> AppBarView::BuildIcon(bool isMenuIcon)
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

RefPtr<FrameNode> AppBarView::BuildDivider()
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

void AppBarView::BindMenuCallback(const RefPtr<FrameNode>& menuButton)
{
    auto clickCallback = [wp = WeakClaim(this)](GestureEvent& info) {
#ifdef PREVIEW
        LOGW("[Engine Log] Unable to show the SharePanel in the Previewer. "
             "Perform this operation on the emulator or a real device instead.");
#else
        auto appbarView = wp.Upgrade();
        CHECK_NULL_VOID(appbarView);
        auto node = appbarView->atomicService_.Upgrade();
        auto pipeline = node->GetContext();
        CHECK_NULL_VOID(pipeline);
        auto theme = pipeline->GetTheme<AppBarTheme>();
        CHECK_NULL_VOID(theme);
        if (SystemProperties::GetExtSurfaceEnabled()) {
            LOGI("start panel bundleName is %{public}s, abilityName is %{public}s", theme->GetBundleName().c_str(),
                theme->GetAbilityName().c_str());
            pipeline->FireSharePanelCallback(theme->GetBundleName(), theme->GetAbilityName());
        } else {
            appbarView->CreateServicePanel(true);
        }
#endif
    };
    auto eventHub = menuButton->GetOrCreateGestureEventHub();
    if (eventHub) {
        eventHub->AddClickEvent(AceType::MakeRefPtr<ClickEvent>(std::move(clickCallback)));
    }
}

void AppBarView::BindCloseCallback(const RefPtr<FrameNode>& closeButton)
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
            windowManager->WindowMinimize();
        }
    };
    auto eventHub = closeButton->GetOrCreateGestureEventHub();
    if (eventHub) {
        eventHub->AddClickEvent(AceType::MakeRefPtr<ClickEvent>(std::move(clickCallback)));
    }
}

void AppBarView::DestroyServicePanel()
{
    auto node = atomicService_.Upgrade();
    auto pipeline = node->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto overlayManager = pipeline->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    ContainerScope scope(pipeline->GetInstanceId());
    overlayManager->CloseModalUIExtension(sessionId_);
    LOGI("ServicePanel release session:%{public}d", sessionId_);
}

void AppBarView::CreateServicePanel(bool firstTry)
{
#ifndef PREVIEW
    if (OHOS::Ace::SystemProperties::GetAtomicServiceBundleName().empty() &&
        OHOS::Ace::AppBarHelper::QueryAppGalleryBundleName().empty()) {
        LOGE("UIExtension BundleName is empty.");
        return;
    }

    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto overlayManager = pipeline->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);

    ModalUIExtensionCallbacks callbacks;
    callbacks.onRelease = [wp = WeakClaim(this)](int32_t releaseCode) {
        auto bar = wp.Upgrade();
        bar->DestroyServicePanel();
    };
    callbacks.onError = [wp = WeakClaim(this), firstTry](
                            int32_t code, const std::string& name, const std::string& message) {
        auto bar = wp.Upgrade();
        bar->DestroyServicePanel();
        if (firstTry) {
            bar->CreateServicePanel(false);
        }
    };
    std::string abilityName;
    auto theme = pipeline->GetTheme<AppBarTheme>();
    if (theme) {
        abilityName = theme->GetStageAbilityName();
    }
    std::string appGalleryBundleName;
    std::map<std::string, std::string> params;
    AssembleUiExtensionParams(firstTry, appGalleryBundleName, params);
    auto wantWrap = WantWrap::CreateWantWrap(appGalleryBundleName, abilityName);
    wantWrap->SetWantParam(params);
    LOGI("ServicePanel request bundle: %{public}s, ability: %{public}s. "
         "UIExtension bundle: %{public}s, ability: %{public}s, module: %{public}s",
        appGalleryBundleName.c_str(), abilityName.c_str(), params["bundleName"].c_str(), params["abilityName"].c_str(),
        params["module"].c_str());
    ModalUIExtensionConfig config;
    sessionId_ = overlayManager->CreateModalUIExtension(wantWrap, callbacks, config);
#endif
}

void AppBarView::InitUIExtensionNode(const RefPtr<FrameNode>& uiExtNode)
{
    CHECK_NULL_VOID(uiExtNode);
    // Update ideal size of UIExtension.
    auto layoutProperty = uiExtNode->GetLayoutProperty();
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(
        CalcLength(Dimension(1.0, DimensionUnit::PERCENT)), CalcLength(Dimension(1.0, DimensionUnit::PERCENT))));
    uiExtNode->MarkModifyDone();
}

std::optional<RectF> AppBarView::GetAppBarRect()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    if (!pipeline || !pipeline->GetInstallationFree()) {
        return std::nullopt;
    }
    auto theme = GetAppBarTheme();
    CHECK_NULL_RETURN(theme, std::nullopt);
    auto atom = atomicService_.Upgrade();
    CHECK_NULL_RETURN(atom, std::nullopt);
    auto pattern = atom->GetPattern<AtomicServicePattern>();
    CHECK_NULL_RETURN(pattern, std::nullopt);
    auto menuBar = pattern->GetMenuBar();
    CHECK_NULL_RETURN(menuBar, std::nullopt);
    auto size = menuBar->GetGeometryNode()->GetMarginFrameSize();
    auto offset = menuBar->GetGeometryNode()->GetMarginFrameOffset();
    auto parent = menuBar->GetParent();
    while (parent) {
        auto frameNode = AceType::DynamicCast<FrameNode>(parent);
        if (frameNode) {
            offset += frameNode->GetGeometryNode()->GetFrameOffset();
        }
        parent = parent->GetParent();
    }
    offset.AddY(theme->GetMenuBarTopMargin().ConvertToPx());
    auto manager = pipeline->GetSafeAreaManager();
    CHECK_NULL_RETURN(manager, std::nullopt);
    offset.AddY(manager->GetSystemSafeArea().top_.Length());
    return RectF(offset, size);
}

void AppBarView::SetStatusBarItemColor(bool isLight)
{
    auto atom = atomicService_.Upgrade();
    CHECK_NULL_VOID(atom);
    auto pattern = atom->GetPattern<AtomicServicePattern>();
    CHECK_NULL_VOID(pattern);
    auto theme = GetAppBarTheme();
    auto menuBar = pattern->GetMenuBar();
    pattern->settedColorMode = isLight;
    pattern->UpdateMenuBarColor(theme, menuBar, isLight);
    pattern->UpdateColor(isLight);
}
} // namespace OHOS::Ace::NG
