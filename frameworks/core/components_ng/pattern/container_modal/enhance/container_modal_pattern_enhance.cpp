/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/container_modal/enhance/container_modal_pattern_enhance.h"

#include "base/i18n/localization.h"
#include "base/log/event_report.h"
#include "base/subwindow/subwindow_manager.h"
#include "base/utils/measure_util.h"
#include "core/components_ng/pattern/container_modal/container_modal_theme.h"
#include "core/components_ng/pattern/container_modal/enhance/container_modal_view_enhance.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t MAX_RECOVER_BUTTON_INDEX = 0;
constexpr int32_t MINIMIZE_BUTTON_INDEX = 1;
constexpr int32_t CLOSE_BUTTON_INDEX = 2;
constexpr int32_t TITLE_POPUP_DURATION = 400;

constexpr float LIGHT_ON_INTENSITY = 1.8f;
constexpr float LIGHT_OFF_INTENSITY = 0.0f;
constexpr float LIGHT_POSITION_Z = 40.0f;
constexpr int32_t LIGHT_ILLUMINATED_TYPE = 7;
constexpr int32_t POINT_LIGHT_ANIMATION_DURATION = 500;

const Dimension MENU_ITEM_RADIUS = 12.0_vp;
const Dimension MENU_ITEM_PADDING_H = 12.0_vp;
const Dimension MENU_ITEM_PADDING_V = 8.0_vp;
const Dimension MENU_PADDING = 4.0_vp;
const Dimension MENU_GUTTER = 2.0_vp;
const Dimension MENU_SAFETY_X = 8.0_vp;
const Dimension MENU_SAFETY_Y = 96.0_vp;
const Dimension MENU_ITEM_TEXT_PADDING = 8.0_vp;
const int32_t MAX_MENU_ITEM_LEFT_SPLIT = 1;
const int32_t MAX_MENU_ITEM_RIGHT_SPLIT = 2;
const int32_t MAX_MENU_DEFAULT_NOT_CHANGE = 3;
} // namespace

void ContainerModalPatternEnhance::ShowTitle(bool isShow, bool hasDeco, bool needUpdate)
{
    auto containerNode = GetHost();
    CHECK_NULL_VOID(containerNode);
    auto customTitleRow = GetCustomTitleRow();
    CHECK_NULL_VOID(customTitleRow);
    auto floatingTitleRow = GetFloatingTitleRow();
    CHECK_NULL_VOID(floatingTitleRow);
    bool isFocus_ = GetIsFocus();
    if (needUpdate) {
        TAG_LOGI(AceLogTag::ACE_APPBAR, "title is need update, isFocus_: %{public}d", isFocus_);
        ChangeCustomTitle(isFocus_);
        ChangeControlButtons(isFocus_);
        return;
    }
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<ContainerModalTheme>();
    auto stackNode = GetStackNode();
    CHECK_NULL_VOID(stackNode);
    auto windowManager = pipelineContext->GetWindowManager();
    CHECK_NULL_VOID(windowManager);
    windowMode_ = windowManager->GetWindowMode();
    isShow = isShow && hasDeco;
    // update container modal padding and border
    auto layoutProperty = containerNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateAlignment(Alignment::TOP_LEFT);
    bool isFloatingWindow = windowManager->GetWindowMode() == WindowMode::WINDOW_MODE_FLOATING;
    BorderWidthProperty borderWidth;
    borderWidth.SetBorderWidth((isFloatingWindow && isShow) ? CONTAINER_BORDER_WIDTH : 0.0_vp);
    layoutProperty->UpdateBorderWidth(borderWidth);
    auto renderContext = containerNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateBackgroundColor(GetContainerColor(isFocus_));
    // only floating window show border
    BorderRadiusProperty borderRadius;
    borderRadius.SetRadius((isFloatingWindow && isShow) ? CONTAINER_OUTER_RADIUS : 0.0_vp);
    renderContext->UpdateBorderRadius(borderRadius);
    BorderColorProperty borderColor;
    borderColor.SetColor((isFloatingWindow && isShow) ? CONTAINER_BORDER_COLOR : Color::TRANSPARENT);
    renderContext->UpdateBorderColor(borderColor);

    // update stack content border
    auto stackLayoutProperty = stackNode->GetLayoutProperty();
    CHECK_NULL_VOID(stackLayoutProperty);
    stackLayoutProperty->UpdateLayoutWeight(1.0f);
    auto stackRenderContext = stackNode->GetRenderContext();
    CHECK_NULL_VOID(stackRenderContext);
    BorderRadiusProperty stageBorderRadius;
    auto contentBorderRadius = (isFloatingWindow && isShow) ? GetStackNodeRadius() : 0.0_vp;
    stageBorderRadius.SetRadius(contentBorderRadius);
    stackRenderContext->UpdateBorderRadius(stageBorderRadius);
    stackRenderContext->SetClipToBounds(true);
    auto customTitleLayoutProperty = customTitleRow->GetLayoutProperty();
    CHECK_NULL_VOID(customTitleLayoutProperty);
    customTitleLayoutProperty->UpdateVisibility(
        (isShow && customTitleSettedShow_) ? VisibleType::VISIBLE : VisibleType::GONE);

    // set container window show state to RS
    pipelineContext->SetContainerWindow(isShow, (isFloatingWindow && isShow) ? CONTAINER_OUTER_RADIUS : 0.0_vp);

    auto floatingLayoutProperty = floatingTitleRow->GetLayoutProperty();
    CHECK_NULL_VOID(floatingLayoutProperty);
    floatingLayoutProperty->UpdateVisibility(VisibleType::GONE);
    auto controlButtonsNode = GetControlButtonRow();
    CHECK_NULL_VOID(controlButtonsNode);
    auto controlButtonsLayoutProperty = controlButtonsNode->GetLayoutProperty();
    CHECK_NULL_VOID(controlButtonsLayoutProperty);
    ChangeFloatingTitle(isFocus_);
    ChangeControlButtons(isFocus_);
    AddPointLight();
    auto controlButtonsContext = controlButtonsNode->GetRenderContext();
    CHECK_NULL_VOID(controlButtonsContext);
    controlButtonsContext->OnTransformTranslateUpdate({ 0.0f, 0.0f, 0.0f });
    controlButtonsLayoutProperty->UpdateVisibility(isShow ? VisibleType::VISIBLE : VisibleType::GONE);
    SetControlButtonVisibleBeforeAnim(isShow ? VisibleType::VISIBLE : VisibleType::GONE);
    auto gestureRow = GetGestureRow();
    CHECK_NULL_VOID(gestureRow);
    AddOrRemovePanEvent(customTitleRow);
    AddOrRemovePanEvent(gestureRow);
    UpdateGestureRowVisible();
    InitColumnTouchTestFunc();
    controlButtonsNode->SetHitTestMode(HitTestMode::HTMTRANSPARENT_SELF);
    auto stack = GetStackNode();
    CHECK_NULL_VOID(stack);
    stack->UpdateInspectorId(CONTAINER_MODAL_STACK_ID);
}

RefPtr<UINode> ContainerModalPatternEnhance::GetTitleItemByIndex(
    const RefPtr<FrameNode>& controlButtonsNode, int32_t originIndex)
{
    return controlButtonsNode->GetChildAtIndex(originIndex);
}

void ContainerModalPatternEnhance::OnWindowFocused()
{
    ContainerModalPattern::OnWindowFocused();
    ContainerModalPattern::SetIsHoveredMenu(false);
    UpdateLightIntensity();
}

void ContainerModalPatternEnhance::OnWindowUnfocused()
{
    if (SubwindowManager::GetInstance()->GetCurrentWindow() &&
        SubwindowManager::GetInstance()->GetCurrentWindow()->GetShown()) {
        SetIsFocus(false);
        ContainerModalPattern::SetIsHoveredMenu(true);
        return;
    }
    ContainerModalPattern::OnWindowUnfocused();
    ContainerModalPattern::SetIsHoveredMenu(false);
    UpdateLightIntensity();
}

void ContainerModalPatternEnhance::OnWindowForceUnfocused()
{
    if (!GetIsFocus()) {
        ContainerModalPattern::OnWindowUnfocused();
    }
}

void ContainerModalPatternEnhance::ChangeCustomTitle(bool isFocus)
{
    // update custom title label
    auto customTitleNode = GetCustomTitleNode();
    CHECK_NULL_VOID(customTitleNode);
    isFocus ? customTitleNode->FireOnWindowFocusedCallback() : customTitleNode->FireOnWindowUnfocusedCallback();
}

void ContainerModalPatternEnhance::ChangeControlButtons(bool isFocus)
{
    auto controlButtonsNode = GetControlButtonRow();
    CHECK_NULL_VOID(controlButtonsNode);

    // update maximize button
    auto maximizeButton =
        AceType::DynamicCast<FrameNode>(GetTitleItemByIndex(controlButtonsNode, MAX_RECOVER_BUTTON_INDEX));
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto windowManager = pipeline->GetWindowManager();
    MaximizeMode mode = windowManager->GetCurrentWindowMaximizeMode();
    InternalResource::ResourceId maxId =
        (mode == MaximizeMode::MODE_AVOID_SYSTEM_BAR || windowMode_ == WindowMode::WINDOW_MODE_FULLSCREEN ||
            windowMode_ == WindowMode::WINDOW_MODE_SPLIT_PRIMARY ||
            windowMode_ == WindowMode::WINDOW_MODE_SPLIT_SECONDARY)
            ? InternalResource::ResourceId::IC_WINDOW_RESTORES
            : InternalResource::ResourceId::IC_WINDOW_MAX;
    ChangeTitleButtonIcon(maximizeButton, maxId, isFocus, false);

    // update minimize button
    auto minimizeButton =
        AceType::DynamicCast<FrameNode>(GetTitleItemByIndex(controlButtonsNode, MINIMIZE_BUTTON_INDEX));
    ChangeTitleButtonIcon(minimizeButton, InternalResource::ResourceId::IC_WINDOW_MIN, isFocus, false);

    // update close button
    auto closeButton = AceType::DynamicCast<FrameNode>(GetTitleItemByIndex(controlButtonsNode, CLOSE_BUTTON_INDEX));
    ChangeTitleButtonIcon(closeButton, InternalResource::ResourceId::IC_WINDOW_CLOSE, isFocus, true);
}

void ContainerModalPatternEnhance::ChangeFloatingTitle(bool isFocus)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto windowManager = pipeline->GetWindowManager();
    CHECK_NULL_VOID(windowManager);

    if (windowManager->GetWindowMode() != WindowMode::WINDOW_MODE_FLOATING &&
        windowManager->GetWindowMode() != WindowMode::WINDOW_MODE_FULLSCREEN) {
        windowManager->SetCurrentWindowMaximizeMode(MaximizeMode::MODE_RECOVER);
    }

    auto floatingTitleRow = GetFloatingTitleRow();
    CHECK_NULL_VOID(floatingTitleRow);
    auto floatingContext = floatingTitleRow->GetRenderContext();
    CHECK_NULL_VOID(floatingContext);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<ContainerModalTheme>();
    floatingContext->UpdateBackgroundColor(GetContainerColor(isFocus));
    // update floating custom title label
    auto customFloatingTitleNode = GetFloatingTitleNode();
    CHECK_NULL_VOID(customFloatingTitleNode);
    isFocus ? customFloatingTitleNode->FireOnWindowFocusedCallback()
            : customFloatingTitleNode->FireOnWindowUnfocusedCallback();
}

void ContainerModalPatternEnhance::ChangeTitleButtonIcon(
    const RefPtr<FrameNode>& buttonNode, InternalResource::ResourceId icon, bool isFocus, bool isCloseBtn)
{
    ContainerModalPattern::ChangeTitleButtonIcon(buttonNode, icon, isFocus, isCloseBtn);
}

Color ContainerModalPatternEnhance::GetContainerColor(bool isFocus)
{
    return ContainerModalPattern::GetContainerColor(isFocus);
}

void ContainerModalPatternEnhance::SetContainerButtonHide(bool hideSplit, bool hideMaximize, bool hideMinimize,
    bool hideClose)
{
    auto controlButtonsNode = GetControlButtonRow();
    CHECK_NULL_VOID(controlButtonsNode);
    ContainerModalViewEnhance::SetEnableSplit(!hideSplit);

    auto maximizeBtn =
        AceType::DynamicCast<FrameNode>(GetTitleItemByIndex(controlButtonsNode, MAX_RECOVER_BUTTON_INDEX));
    CHECK_NULL_VOID(maximizeBtn);
    maximizeBtn->GetLayoutProperty()->UpdateVisibility(hideMaximize ? VisibleType::GONE : VisibleType::VISIBLE);
    maximizeBtn->MarkDirtyNode();

    auto minimizeBtn =
        AceType::DynamicCast<FrameNode>(GetTitleItemByIndex(controlButtonsNode, MINIMIZE_BUTTON_INDEX));
    CHECK_NULL_VOID(minimizeBtn);
    minimizeBtn->GetLayoutProperty()->UpdateVisibility(hideMinimize ? VisibleType::GONE : VisibleType::VISIBLE);
    minimizeBtn->MarkDirtyNode();

    auto closeBtn = AceType::DynamicCast<FrameNode>(GetTitleItemByIndex(controlButtonsNode, CLOSE_BUTTON_INDEX));
        CHECK_NULL_VOID(closeBtn);
        closeBtn->GetLayoutProperty()->UpdateVisibility(hideClose ? VisibleType::GONE : VisibleType::VISIBLE);
        closeBtn->MarkDirtyNode();
    InitTitleRowLayoutProperty(GetCustomTitleRow());
}

void ContainerModalPatternEnhance::UpdateTitleInTargetPos(bool isShow, int32_t height)
{
    auto floatingTitleNode = GetFloatingTitleRow();
    CHECK_NULL_VOID(floatingTitleNode);
    auto floatingLayoutProperty = floatingTitleNode->GetLayoutProperty();
    CHECK_NULL_VOID(floatingLayoutProperty);
    auto floatingContext = floatingTitleNode->GetRenderContext();
    CHECK_NULL_VOID(floatingContext);

    auto controlButtonsNode = GetControlButtonRow();
    CHECK_NULL_VOID(controlButtonsNode);
    auto controlButtonsLayoutProperty = controlButtonsNode->GetLayoutProperty();
    CHECK_NULL_VOID(controlButtonsLayoutProperty);
    auto buttonsContext = controlButtonsNode->GetRenderContext();
    CHECK_NULL_VOID(buttonsContext);

    auto titlePopupDistance = titleHeight_.ConvertToPx();
    auto cubicBezierCurve = AceType::MakeRefPtr<CubicCurve>(0.00, 0.00, 0.20, 1.00);
    AnimationOption option;
    option.SetDuration(TITLE_POPUP_DURATION);
    option.SetCurve(cubicBezierCurve);

    if (isShow && CanShowFloatingTitle()) {
        floatingContext->OnTransformTranslateUpdate({ 0.0f, height - static_cast<float>(titlePopupDistance), 0.0f });
        floatingLayoutProperty->UpdateVisibility(floatingTitleSettedShow_ ? VisibleType::VISIBLE : VisibleType::GONE);
        AnimationUtils::Animate(option, [floatingContext, height]() {
            auto rect = floatingContext->GetPaintRectWithoutTransform();
            floatingContext->OnTransformTranslateUpdate({ 0.0f, static_cast<float>(height - rect.GetY()), 0.0f });
        });
        buttonsContext->OnTransformTranslateUpdate({ 0.0f, height - static_cast<float>(titlePopupDistance), 0.0f });
        SetControlButtonVisibleBeforeAnim(controlButtonsLayoutProperty->GetVisibilityValue());
        controlButtonsLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
        AnimationUtils::Animate(option, [buttonsContext, titlePopupDistance, height]() {
            auto rect = buttonsContext->GetPaintRectWithoutTransform();
            buttonsContext->OnTransformTranslateUpdate({ 0.0f, static_cast<float>(height -
                (titlePopupDistance - CONTAINER_TITLE_HEIGHT.ConvertToPx())/2 - rect.GetY()), 0.0f });
        });
    }

    if (!isShow && CanHideFloatingTitle()) {
        auto beforeVisible = GetControlButtonVisibleBeforeAnim();
        AnimationUtils::Animate(
            option,
            [floatingContext, buttonsContext, titlePopupDistance, beforeVisible]() {
                floatingContext->OnTransformTranslateUpdate({ 0.0f, static_cast<float>(-titlePopupDistance), 0.0f });
                buttonsContext->OnTransformTranslateUpdate({ 0.0f,
                    beforeVisible == VisibleType::VISIBLE ? 0.0f : static_cast<float>(-titlePopupDistance), 0.0f });
            },
            [floatingLayoutProperty, controlButtonsLayoutProperty, weak = WeakClaim(this)]() {
                auto containerModal = weak.Upgrade();
                CHECK_NULL_VOID(containerModal);
                floatingLayoutProperty->UpdateVisibility(VisibleType::GONE);
                controlButtonsLayoutProperty->UpdateVisibility(containerModal->GetControlButtonVisibleBeforeAnim());
            });
    }
}

void ContainerModalPatternEnhance::AddPointLight()
{
    auto controlButtonsNode = GetControlButtonRow();
    CHECK_NULL_VOID(controlButtonsNode);

    auto maximizeButton =
        AceType::DynamicCast<FrameNode>(GetTitleItemByIndex(controlButtonsNode, MAX_RECOVER_BUTTON_INDEX));
    auto minimizeButton =
        AceType::DynamicCast<FrameNode>(GetTitleItemByIndex(controlButtonsNode, MINIMIZE_BUTTON_INDEX));
    auto closeButton = AceType::DynamicCast<FrameNode>(GetTitleItemByIndex(controlButtonsNode, CLOSE_BUTTON_INDEX));

    SetPointLight(controlButtonsNode, maximizeButton, minimizeButton, closeButton);
}

void ContainerModalPatternEnhance::SetPointLight(RefPtr<FrameNode>& containerTitleRow, RefPtr<FrameNode>& maximizeBtn,
    RefPtr<FrameNode>& minimizeBtn, RefPtr<FrameNode>& closeBtn)
{
    auto inputHub = containerTitleRow->GetOrCreateInputEventHub();
    RefPtr<RenderContext> maximizeBtnRenderContext_ = maximizeBtn->GetRenderContext();
    RefPtr<RenderContext> minimizeBtnRenderContext_ = minimizeBtn->GetRenderContext();
    closeBtnRenderContext_ = closeBtn->GetRenderContext();

    maximizeBtnRenderContext_->UpdateLightIlluminated(LIGHT_ILLUMINATED_TYPE);
    minimizeBtnRenderContext_->UpdateLightIlluminated(LIGHT_ILLUMINATED_TYPE);
    closeBtnRenderContext_->UpdateLightIlluminated(LIGHT_ILLUMINATED_TYPE);

    auto mouseTask = [this, weakCloseBtn = AceType::WeakClaim(AceType::RawPtr(closeBtn))](MouseInfo& info) {
        auto closeBtn = weakCloseBtn.Upgrade();
        CHECK_NULL_VOID(closeBtn);
        auto closeBntFrameRect = closeBtn->GetGeometryNode()->GetFrameRect();
        TranslateOptions closeTranslate = TranslateOptions(info.GetLocalLocation().GetX() - closeBntFrameRect.Left(),
            info.GetLocalLocation().GetY() - closeBntFrameRect.Top(), LIGHT_POSITION_Z);
        auto closeBtnContext = closeBtn->GetRenderContext();
        closeBtnContext->UpdateLightPosition(closeTranslate);
    };
    auto mouseEvent = MakeRefPtr<InputEvent>(std::move(mouseTask));
    inputHub->AddOnMouseEvent(mouseEvent);

    auto hoverEventFucRow = [this](bool hover) {
        isTitleRowHovered_ = hover;
        UpdateLightColor();
        UpdateLightIntensity();
    };
    inputHub->AddOnHoverEvent(AceType::MakeRefPtr<InputEvent>(std::move(hoverEventFucRow)));
}

void ContainerModalPatternEnhance::UpdateLightColor()
{
    auto colorMode = SystemProperties::GetColorMode();
    bool isDarkMode = colorMode == ColorMode::LIGHT;
    if (isDarkMode) {
        closeBtnRenderContext_->UpdateLightColor(Color(0xa0000000));
    } else {
        closeBtnRenderContext_->UpdateLightColor(Color::WHITE);
    }
}

void ContainerModalPatternEnhance::UpdateLightIntensity()
{
    if (!closeBtnRenderContext_) {
        return;
    }
    AnimationOption option;
    option.SetDuration(POINT_LIGHT_ANIMATION_DURATION);
    option.SetCurve(Curves::SMOOTH);
    AnimationUtils::Animate(option, [this]() {
        if (GetIsFocus() && isTitleRowHovered_) {
            closeBtnRenderContext_->UpdateLightIntensity(LIGHT_ON_INTENSITY);
        } else {
            closeBtnRenderContext_->UpdateLightIntensity(LIGHT_OFF_INTENSITY);
        }
    });
}

RefPtr<FrameNode> ContainerModalPatternEnhance::GetOrCreateMenuList(const RefPtr<FrameNode>& targetNode)
{
    MeasureContext textCtx;
    textCtx.textContent = Localization::GetInstance()->GetEntryLetters("window.leftSide");
    textCtx.fontSize = TITLE_TEXT_FONT_SIZE;
    auto textSize = MeasureUtil::MeasureTextSize(textCtx);
    textWidth_ = textSize.Width();

    if (!menuList_) {
        auto menuList = FrameNode::CreateFrameNode(
            V2::LIST_COMPONENT_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ListPattern>());
        auto listLayoutProperty = menuList->GetLayoutProperty<ListLayoutProperty>();
        CHECK_NULL_RETURN(listLayoutProperty, nullptr);
        listLayoutProperty->UpdateMeasureType(MeasureType::MATCH_CONTENT);
        listLayoutProperty->UpdateLaneGutter(MENU_GUTTER);
        menuList->AddChild(BuildLeftSplitMenuItem());
        menuList->AddChild(BuildRightSplitMenuItem());
        menuList_ = menuList;
    }
    auto menuLayoutProperty = menuList_->GetLayoutProperty<ListLayoutProperty>();
    menuLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(GetMenuWidth()), std::nullopt));
    CalculateMenuOffset(targetNode);

    return menuList_;
}

RefPtr<FrameNode> ContainerModalPatternEnhance::BuildLeftSplitMenuItem()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto windowManager = pipeline->GetWindowManager();
    CHECK_NULL_RETURN(windowManager, nullptr);
    auto leftSplitClickFunc = [weak = AceType::WeakClaim(AceType::RawPtr(windowManager))](GestureEvent& info) {
        auto windowManager = weak.Upgrade();
        if (!windowManager) {
            TAG_LOGE(AceLogTag::ACE_APPBAR, "create leftsplit callback func failed,windowMannager is null!");
            return;
        }
        EventReport::ReportClickTitleMaximizeMenu(MAX_MENU_ITEM_LEFT_SPLIT, MAX_MENU_DEFAULT_NOT_CHANGE);
        windowManager->FireWindowSplitCallBack();
    };
    auto leftSplitEvent = AceType::MakeRefPtr<ClickEvent>(std::move(leftSplitClickFunc));
    auto screenLeftRow = BuildMenuItem(Localization::GetInstance()->GetEntryLetters("window.leftSide"),
        InternalResource::ResourceId::IC_WINDOW_MENU_SCREEN_L, leftSplitEvent, false);
    screenLeftRow->UpdateInspectorId("EnhanceMenuScreenLeftRow");
    return screenLeftRow;
}

RefPtr<FrameNode> ContainerModalPatternEnhance::BuildRightSplitMenuItem()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto windowManager = pipeline->GetWindowManager();
    CHECK_NULL_RETURN(windowManager, nullptr);
    auto rightSplitClickFunc = [weak = AceType::WeakClaim(AceType::RawPtr(windowManager))](GestureEvent& info) {
        auto windowManager = weak.Upgrade();
        if (!windowManager) {
            TAG_LOGE(AceLogTag::ACE_APPBAR, "create rightSpiltBtn callback func failed, windowManager is null!");
            return;
        }
        EventReport::ReportClickTitleMaximizeMenu(MAX_MENU_ITEM_RIGHT_SPLIT, MAX_MENU_DEFAULT_NOT_CHANGE);
        windowManager->FireWindowSplitCallBack(false);
    };
    auto rightSplitEvent = AceType::MakeRefPtr<ClickEvent>(std::move(rightSplitClickFunc));
    auto screenRightRow = BuildMenuItem(Localization::GetInstance()->GetEntryLetters("window.rightSide"),
        InternalResource::ResourceId::IC_WINDOW_MENU_SCREEN_N, rightSplitEvent, false);
    screenRightRow->UpdateInspectorId("EnhanceMenuScreenRightRow");
    return screenRightRow;
}

RefPtr<FrameNode> ContainerModalPatternEnhance::BuildMenuItem(
    std::string title, InternalResource::ResourceId resourceId, RefPtr<ClickEvent> event, bool chooseCurrent)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto windowManager = pipeline->GetWindowManager();
    CHECK_NULL_RETURN(windowManager, nullptr);

    auto containerTitleRow = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    // setRadius 8vp
    auto render = containerTitleRow->GetRenderContext();
    BorderRadiusProperty borderRadiusProperty;
    borderRadiusProperty.SetRadius(MENU_ITEM_RADIUS);
    render->UpdateBorderRadius(borderRadiusProperty);

    auto layoutProperty = containerTitleRow->GetLayoutProperty<LinearLayoutProperty>();
    layoutProperty->UpdateMeasureType(MeasureType::MATCH_CONTENT);
    
    layoutProperty->UpdateMainAxisAlign(FlexAlign::FLEX_START);
    layoutProperty->UpdateCrossAxisAlign(FlexAlign::CENTER);
    PaddingProperty padding;
    padding.SetEdges(CalcLength(MENU_ITEM_PADDING_H), CalcLength(MENU_ITEM_PADDING_H), CalcLength(MENU_ITEM_PADDING_V),
        CalcLength(MENU_ITEM_PADDING_V));
    layoutProperty->UpdatePadding(padding);

    auto leftIcon = ContainerModalViewEnhance::BuildMenuItemIcon(resourceId);

    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    auto titleLabel = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), textPattern);
    auto textLayoutProperty = titleLabel->GetLayoutProperty<TextLayoutProperty>();
    textLayoutProperty->UpdateContent(title);
    textLayoutProperty->UpdateMaxLines(1);
    textLayoutProperty->UpdateFontSize(TITLE_TEXT_FONT_SIZE);
    textLayoutProperty->UpdateAlignment(Alignment::CENTER_LEFT);
    MarginProperty margin;
    margin.left = CalcLength(MENU_ITEM_TEXT_PADDING);
    margin.right = CalcLength(MENU_ITEM_TEXT_PADDING);
    textLayoutProperty->UpdateMargin(margin);

    // add icon and label
    containerTitleRow->AddChild(leftIcon);
    containerTitleRow->AddChild(titleLabel);
    auto hub = containerTitleRow->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(hub, nullptr);
    hub->AddClickEvent(event);
    ContainerModalViewEnhance::BondingMenuItemEvent(containerTitleRow);
    return containerTitleRow;
}

Dimension ContainerModalPatternEnhance::GetMenuWidth()
{
    auto noneTextWidth = TITLE_ICON_SIZE + MENU_ITEM_PADDING_H * 2 + MENU_ITEM_TEXT_PADDING;
    auto menuWidth = Dimension(textWidth_ + noneTextWidth.ConvertToPx());
    return menuWidth;
}

OffsetF ContainerModalPatternEnhance::GetMenuOffset()
{
    return menuOffset_;
}

void ContainerModalPatternEnhance::CalculateMenuOffset(const RefPtr<FrameNode>& targetNode)
{
    auto pipeline = targetNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    auto windowOffset = pipeline->GetCurrentWindowRect().GetOffset();
    auto nodeOffset = targetNode->GetPositionToWindowWithTransform();
    float menuWidth = GetMenuWidth().ConvertToPx() + MENU_PADDING.ConvertToPx() * 2;
    float buttonSize = TITLE_ICON_SIZE.ConvertToPx();
    float offsetX = nodeOffset.GetX() + windowOffset.GetX() - menuWidth + buttonSize;
    float offsetY = nodeOffset.GetY() + windowOffset.GetY() + buttonSize;

    float screenWidth = SystemProperties::GetDevicePhysicalWidth();
    float screenHeight = SystemProperties::GetDevicePhysicalHeight();
    float titleHeight = GetCustomTitleHeight().ConvertToPx();
    const Dimension MENU_CONTAINER_HEIGHT = 96.0_vp; // need to calculate from text, to be delete
    float menuHeight = MENU_CONTAINER_HEIGHT.ConvertToPx() + 2 * CONTENT_PADDING.ConvertToPx();
    if (offsetX < MENU_SAFETY_X.ConvertToPx()) {
        TAG_LOGI(AceLogTag::ACE_APPBAR, "ContainerModalViewEnhance::RecalculateMenuOffset OffsetX cover screen left");
        offsetX = offsetX + menuWidth - buttonSize;
    }
    if (offsetX > screenWidth - menuWidth - MENU_SAFETY_X.ConvertToPx()) {
        TAG_LOGI(AceLogTag::ACE_APPBAR, "ContainerModalViewEnhance::RecalculateMenuOffset OffsetX cover screen right");
        offsetX = screenWidth - menuWidth - MENU_SAFETY_X.ConvertToPx();
    }
    if (offsetY > screenHeight - menuHeight - MENU_SAFETY_Y.ConvertToPx()) {
        TAG_LOGI(AceLogTag::ACE_APPBAR, "ContainerModalViewEnhance::RecalculateMenuOffset OffsetX cover screen bottom");
        offsetY = offsetY - menuHeight - titleHeight;
    }
    menuOffset_ = { offsetX, offsetY };
    TAG_LOGI(AceLogTag::ACE_APPBAR,
        "ContainerModal ShowMaxMenu called menuOffset_ = %{public}s", menuOffset_.ToString().c_str());
}
} // namespace OHOS::Ace::NG
