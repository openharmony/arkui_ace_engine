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

#include <map>

#include "base/utils/utils.h"
#include "base/want/want_wrap.h"
#include "core/common/app_bar_helper.h"
#include "core/common/container.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/focus_hub.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/app_bar/app_bar_theme.h"
#include "core/components_ng/pattern/app_bar/atomic_service_pattern.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/divider/divider_layout_property.h"
#include "core/components_ng/pattern/divider/divider_pattern.h"
#include "core/components_ng/pattern/divider/divider_render_property.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_ng/pattern/stage/stage_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/property/border_property.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
RefPtr<AppBarTheme> GetAppBarTheme()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    return pipeline->GetTheme<AppBarTheme>();
}
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
    pattern->UpdateColor();
    pattern->UpdateRowLayout();
    return atom;
}

RefPtr<FrameNode> AppBarView::BuildMenuBarRow()
{
    auto menuBarRow = FrameNode::CreateFrameNode(V2::APP_BAR_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    // get theme
    auto appBarTheme = GetAppBarTheme();
    CHECK_NULL_RETURN(appBarTheme, nullptr);
    // add children
    auto menuBar = BuildMenuBar();
    menuBarRow->AddChild(menuBar);
    // init
    auto layoutProperty = menuBarRow->GetLayoutProperty<LinearLayoutProperty>();
    auto renderContext = menuBarRow->GetRenderContext();

    layoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(1.0, DimensionUnit::PERCENT), CalcLength(appBarTheme->GetMenuBarHeight())));

    layoutProperty->UpdateMainAxisAlign(FlexAlign::FLEX_END);
    renderContext->UpdatePosition(OffsetT<Dimension>(0.0_vp, appBarTheme->GetMenuBarTopMargin()));
    renderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    menuBarRow->SetHitTestMode(HitTestMode::HTMTRANSPARENT_SELF);
    menuBarRow->MarkModifyDone();

    return menuBarRow;
}

RefPtr<FrameNode> AppBarView::BuildMenuBar()
{
    auto menuBar = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    // get theme
    auto appBarTheme = GetAppBarTheme();
    CHECK_NULL_RETURN(appBarTheme, nullptr);
    // add child
    auto menuButton = BuildButton(true);
    BindMenuCallback(menuButton);
    menuBar->AddChild(menuButton);
    auto divider = BuildDivider();
    menuBar->AddChild(divider);
    auto closeButton = BuildButton(false);
    BindCloseCallback(closeButton);
    menuBar->AddChild(closeButton);
    // init
    auto layoutProperty = menuBar->GetLayoutProperty<LinearLayoutProperty>();
    auto renderContext = menuBar->GetRenderContext();

    layoutProperty->UpdateMainAxisAlign(FlexAlign::FLEX_START);

    BorderWidthProperty borderWidth;
    borderWidth.SetBorderWidth(appBarTheme->GetBorderWidth());
    layoutProperty->UpdateBorderWidth(borderWidth);
    renderContext->UpdateBorderWidth(borderWidth);

    auto bent = appBarTheme->GetBentRadius();
    renderContext->UpdateBorderRadius(BorderRadiusProperty(bent));

    MarginProperty margin;
    margin.left = CalcLength(appBarTheme->GetMenuBarLeftMargin());
    margin.right = CalcLength(appBarTheme->GetMenuBarRightMargin());
    layoutProperty->UpdateMargin(margin);
    menuBar->MarkModifyDone();

    return menuBar;
}

RefPtr<FrameNode> AppBarView::BuildButton(bool isMenuButton)
{
    auto appBarTheme = GetAppBarTheme();
    CHECK_NULL_RETURN(appBarTheme, nullptr);
    auto icon = BuildIcon(isMenuButton);
    // create button
    auto button = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    auto renderContext = button->GetRenderContext();
    renderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    // init
    auto layoutProperty = button->GetLayoutProperty<ButtonLayoutProperty>();
    layoutProperty->UpdateType(ButtonType::CUSTOM);
    layoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(appBarTheme->GetButtonWidth()), CalcLength(appBarTheme->GetButtonHeight())));
    auto buttonRenderContext = button->GetRenderContext();
    auto bent = appBarTheme->GetBentRadius();
    auto rightAngle = appBarTheme->GetRightAngle();
    if (isMenuButton) {
        buttonRenderContext->UpdateBorderRadius(BorderRadiusProperty(bent, rightAngle, bent, rightAngle));
    } else {
        buttonRenderContext->UpdateBorderRadius(BorderRadiusProperty(rightAngle, bent, rightAngle, bent));
    }
    auto focus = button->GetFocusHub();
    auto focusPattern = button->GetPattern<FocusPattern>();
    if (focus) {
        focus->SetFocusable(true);
    }
    if (focusPattern) {
        focusPattern->SetStyleType(FocusStyleType::INNER_BORDER);
    }
    auto buttonPattern = button->GetPattern<ButtonPattern>();
    if (buttonPattern) {
        buttonPattern->SetClickedColor(appBarTheme->GetClickEffectColor());
    }
    button->AddChild(icon);
    button->MarkModifyDone();

    return button;
}

RefPtr<FrameNode> AppBarView::BuildIcon(bool isMenuIcon)
{
    // create image
    auto icon = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    // set icon
    ImageSourceInfo imageSourceInfo;
    imageSourceInfo.SetResourceId(
        isMenuIcon ? InternalResource::ResourceId::APP_BAR_MENU_SVG : InternalResource::ResourceId::APP_BAR_CLOSE_SVG);
    auto layoutProperty = icon->GetLayoutProperty<ImageLayoutProperty>();
    layoutProperty->UpdateImageSourceInfo(imageSourceInfo);
    // set size
    auto appBarTheme = GetAppBarTheme();
    CHECK_NULL_RETURN(appBarTheme, nullptr);
    layoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(appBarTheme->GetNewIconSize()), CalcLength(appBarTheme->GetNewIconSize())));
    // set margin
    MarginProperty margin;
    margin.top = CalcLength(appBarTheme->GetIconVerticalMargin());
    margin.bottom = CalcLength(appBarTheme->GetIconVerticalMargin());
    if (isMenuIcon) {
        margin.left = CalcLength(appBarTheme->GetIconOutsideMargin());
        margin.right = CalcLength(appBarTheme->GetIconInsideMargin());
    } else {
        margin.left = CalcLength(appBarTheme->GetIconInsideMargin());
        margin.right = CalcLength(appBarTheme->GetIconOutsideMargin());
    }
    auto focus = icon->GetFocusHub();
    if (focus) {
        focus->SetFocusable(false);
    }
    layoutProperty->UpdateMargin(margin);
    icon->MarkModifyDone();

    return icon;
}

RefPtr<FrameNode> AppBarView::BuildDivider()
{
    auto divider = FrameNode::CreateFrameNode(
        V2::DIVIDER_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<DividerPattern>());
    // get theme
    auto appBarTheme = GetAppBarTheme();
    CHECK_NULL_RETURN(appBarTheme, nullptr);
    // init
    auto layoutProperty = divider->GetLayoutProperty<DividerLayoutProperty>();
    layoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(appBarTheme->GetDividerWidth()), CalcLength(appBarTheme->GetDividerHeight())));
    layoutProperty->UpdateVertical(true);
    layoutProperty->UpdateStrokeWidth(appBarTheme->GetDividerWidth());

    auto renderProperty = divider->GetPaintProperty<DividerRenderProperty>();
    renderProperty->UpdateDividerColor(appBarTheme->GetDividerColor());
    renderProperty->UpdateLineCap(LineCap::ROUND);

    return divider;
}

void AppBarView::BindMenuCallback(const RefPtr<FrameNode>& menuButton)
{
    auto clickCallback = [weakButton = WeakClaim(RawPtr(menuButton))](GestureEvent& info) {
#ifdef PREVIEW
        LOGW("[Engine Log] Unable to show the SharePanel in the Previewer. "
             "Perform this operation on the emulator or a real device instead.");
#else
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto appBarTheme = pipeline->GetTheme<AppBarTheme>();
        CHECK_NULL_VOID(appBarTheme);
        if (SystemProperties::GetExtSurfaceEnabled()) {
            LOGI("start panel bundleName is %{public}s, abilityName is %{public}s",
                appBarTheme->GetBundleName().c_str(), appBarTheme->GetAbilityName().c_str());
            pipeline->FireSharePanelCallback(appBarTheme->GetBundleName(), appBarTheme->GetAbilityName());
        } else {
            auto menuButton = weakButton.Upgrade();
            CHECK_NULL_VOID(menuButton);
            BindContentCover(menuButton);
        }
#endif
    };
    auto buttonEventHub = menuButton->GetOrCreateGestureEventHub();
    if (buttonEventHub) {
        buttonEventHub->AddClickEvent(AceType::MakeRefPtr<ClickEvent>(std::move(clickCallback)));
    }
}

void AppBarView::BindCloseCallback(const RefPtr<FrameNode>& closeButton)
{
    auto clickCallback = [](GestureEvent& info) {
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto windowManager = pipeline->GetWindowManager();
        CHECK_NULL_VOID(windowManager);
        windowManager->WindowMinimize();
    };
    auto buttonEventHub = closeButton->GetOrCreateGestureEventHub();
    if (buttonEventHub) {
        buttonEventHub->AddClickEvent(AceType::MakeRefPtr<ClickEvent>(std::move(clickCallback)));
    }
}

void AppBarView::BindContentCover(const RefPtr<FrameNode>& targetNode)
{
    if (OHOS::Ace::AppBarHelper::QueryAppGalleryBundleName().empty()) {
        LOGE("UIExtension BundleName is empty.");
        return;
    }

    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto overlayManager = pipeline->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);

    std::string stageAbilityName = "";
    auto appBarTheme = pipeline->GetTheme<AppBarTheme>();
    if (appBarTheme) {
        stageAbilityName = appBarTheme->GetStageAbilityName();
    }
    NG::ModalStyle modalStyle;
    modalStyle.modalTransition = NG::ModalTransition::NONE;
    auto buildNodeFunc = [targetNode, overlayManager, &modalStyle, &stageAbilityName]() -> RefPtr<UINode> {
        auto onRelease = [overlayManager, &modalStyle, targetNode](int32_t releaseCode) {
            overlayManager->BindContentCover(
                false, nullptr, nullptr, modalStyle, nullptr, nullptr, nullptr, nullptr, targetNode);
        };
        auto onError = [overlayManager, &modalStyle, targetNode](
                           int32_t code, const std::string& name, const std::string& message) {
            overlayManager->BindContentCover(
                false, nullptr, nullptr, modalStyle, nullptr, nullptr, nullptr, nullptr, targetNode);
        };

        // Create parameters of UIExtension.
        std::map<std::string, std::string> params = CreateUIExtensionParams();

        // Create UIExtension node.
        auto appGalleryBundleName = OHOS::Ace::AppBarHelper::QueryAppGalleryBundleName();
        auto uiExtNode = OHOS::Ace::AppBarHelper::CreateUIExtensionNode(
            appGalleryBundleName, stageAbilityName, params, std::move(onRelease), std::move(onError));
        LOGI("UIExtension BundleName: %{public}s, AbilityName: %{public}s", appGalleryBundleName.c_str(),
            stageAbilityName.c_str());

        // Update ideal size of UIExtension.
        auto layoutProperty = uiExtNode->GetLayoutProperty();
        CHECK_NULL_RETURN(layoutProperty, uiExtNode);
        layoutProperty->UpdateUserDefinedIdealSize(CalcSize(
            CalcLength(Dimension(1.0, DimensionUnit::PERCENT)), CalcLength(Dimension(1.0, DimensionUnit::PERCENT))));
        uiExtNode->MarkModifyDone();
        return uiExtNode;
    };
    overlayManager->BindContentCover(
        true, nullptr, std::move(buildNodeFunc), modalStyle, nullptr, nullptr, nullptr, nullptr, targetNode);
}

std::map<std::string, std::string> AppBarView::CreateUIExtensionParams()
{
    auto missionId = AceApplicationInfo::GetInstance().GetMissionId();
    std::map<std::string, std::string> params;
    params.try_emplace("bundleName", AceApplicationInfo::GetInstance().GetProcessName());
    params.try_emplace("abilityName", AceApplicationInfo::GetInstance().GetAbilityName());
    params.try_emplace("module", Container::Current()->GetModuleName());
    if (missionId != -1) {
        params.try_emplace("missionId", std::to_string(missionId));
    }
    params.try_emplace("ability.want.params.uiExtensionType", "sys/commonUI");
    LOGI("BundleName: %{public}s, AbilityName: %{public}s, Module: %{public}s",
        AceApplicationInfo::GetInstance().GetProcessName().c_str(),
        AceApplicationInfo::GetInstance().GetAbilityName().c_str(), Container::Current()->GetModuleName().c_str());
    return params;
}

std::optional<RectF> AppBarView::GetAppBarRect()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    if (!pipeline || !pipeline->GetInstallationFree()) {
        return std::nullopt;
    }
    auto theme = GetAppBarTheme();
    CHECK_NULL_RETURN(theme, std::nullopt);
    SizeF size(theme->GetMenuBarWidth().ConvertToPx(), theme->GetMenuBarHeight().ConvertToPx());
    auto atom = atomicService_.Upgrade();
    CHECK_NULL_RETURN(atom, std::nullopt);
    auto pattern = atom->GetPattern<AtomicServicePattern>();
    CHECK_NULL_RETURN(pattern, std::nullopt);
    auto menuBar = pattern->GetMenuBar();
    CHECK_NULL_RETURN(menuBar, std::nullopt);
    auto offset = menuBar->GetParentGlobalOffsetDuringLayout();
    return RectF(offset, size);
}
} // namespace OHOS::Ace::NG
