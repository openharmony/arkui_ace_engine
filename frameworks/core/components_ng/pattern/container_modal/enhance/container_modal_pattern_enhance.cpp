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

const int32_t MENU_TASK_DELAY_TIME = 600;
constexpr int32_t TITLE_POPUP_DURATION = 400;
const int32_t DOUBLE_CLICK_TO_MAXIMIZE = 1;
const int32_t DOUBLE_CLICK_TO_RECOVER = 2;
const int32_t MAX_BUTTON_CLICK_TO_MAXIMIZE = 1;
const int32_t MAX_BUTTON_CLICK_TO_RECOVER = 2;
constexpr int32_t MAX_RECOVER_BUTTON_INDEX = 0;
constexpr int32_t MINIMIZE_BUTTON_INDEX = 1;
constexpr int32_t CLOSE_BUTTON_INDEX = 2;
const int32_t MAX_MENU_ITEM_LEFT_SPLIT = 1;
const int32_t MAX_MENU_ITEM_RIGHT_SPLIT = 2;
const int32_t MAX_MENU_ITEM_MAXIMIZE = 3;
const int32_t MAX_MENU_DEFAULT_NOT_CHANGE = 3;

constexpr float LIGHT_ON_INTENSITY_DARK = 2.5f;
constexpr float LIGHT_ON_INTENSITY_LIGHT = 5.5f;
constexpr float LIGHT_OFF_INTENSITY = 0.0f;
constexpr float LIGHT_POSITION_Z = 25.0f;
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
const Color MENU_ITEM_COLOR = Color(0xffffff);

RefPtr<WindowManager> GetNotMovingWindowManager(WeakPtr<FrameNode>& weak)
{
    auto node = weak.Upgrade();
    CHECK_NULL_RETURN(node, nullptr);
    auto pipeline = node->GetContextRefPtr();
    CHECK_NULL_RETURN(pipeline, nullptr);
    const auto& windowManager = pipeline->GetWindowManager();
    CHECK_NULL_RETURN(windowManager, nullptr);

    bool isMoving = windowManager->GetWindowStartMoveFlag();
    if (isMoving) {
        TAG_LOGI(AceLogTag::ACE_APPBAR, "window is moving, button click event is not supported");
        return nullptr;
    }
    return windowManager;
}

void BondingMenuItemEvent(WeakPtr<ContainerModalPatternEnhance>& weakPtn, RefPtr<FrameNode>& item, bool isLeftSplit)
{
    WeakPtr<FrameNode> weakItem = item;
    auto hoverFunc = [weakItem](bool isHover) {
        auto item = weakItem.Upgrade();
        CHECK_NULL_VOID(item);
        ContainerModalPatternEnhance::OnMenuItemHoverEvent(item, isHover);
    };
    auto clickFunc = [weakItem](MouseInfo& info) -> void {
        auto item = weakItem.Upgrade();
        CHECK_NULL_VOID(item);
        ContainerModalPatternEnhance::OnMenuItemClickEvent(item, info);
    };

    auto hoverEvent = AceType::MakeRefPtr<InputEvent>(std::move(hoverFunc));
    auto clickEvent = AceType::MakeRefPtr<InputEvent>(std::move(clickFunc));

    auto inputHub = item->GetOrCreateInputEventHub();
    inputHub->AddOnHoverEvent(hoverEvent);
    inputHub->AddOnMouseEvent(clickEvent);

    auto gestureHub = item->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    auto splitClickFunc = [weakPtn, isLeftSplit](GestureEvent& info) {
        auto pattern = weakPtn.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnMenuItemClickGesture(isLeftSplit);
    };
    auto clickGesture = AceType::MakeRefPtr<ClickEvent>(std::move(splitClickFunc));
    gestureHub->AddClickEvent(clickGesture);
}

RefPtr<FrameNode> BuildMenuItem(WeakPtr<ContainerModalPatternEnhance>&& weakPattern, bool isLeftSplit)
{
    auto containerTitleRow = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));

    using StrPair = std::tuple<std::string, std::string, InternalResource::ResourceId>;
    const StrPair strs[] = {
        { "window.leftSide", "EnhanceMenuScreenLeftRow", InternalResource::ResourceId::IC_WINDOW_MENU_SCREEN_L },
        { "window.rightSide", "EnhanceMenuScreenRightRow", InternalResource::ResourceId::IC_WINDOW_MENU_SCREEN_N }};
    const auto& sideSrc = isLeftSplit ? strs[0] : strs[1];
    containerTitleRow->UpdateInspectorId(std::get<1>(sideSrc));

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

    auto icon = ContainerModalViewEnhance::BuildMenuItemIcon(std::get<2>(sideSrc));
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    auto titleLabel =
        FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), textPattern);
    auto textLayoutProperty = titleLabel->GetLayoutProperty<TextLayoutProperty>();
    textLayoutProperty->UpdateContent(Localization::GetInstance()->GetEntryLetters(std::get<0>(sideSrc)));
    textLayoutProperty->UpdateMaxLines(1);
    textLayoutProperty->UpdateFontSize(TITLE_TEXT_FONT_SIZE);
    textLayoutProperty->UpdateAlignment(Alignment::CENTER_LEFT);
    MarginProperty margin;
    margin.left = CalcLength(MENU_ITEM_TEXT_PADDING);
    margin.right = CalcLength(MENU_ITEM_TEXT_PADDING);
    textLayoutProperty->UpdateMargin(margin);

    // add icon and label
    containerTitleRow->AddChild(icon);
    containerTitleRow->AddChild(titleLabel);
    BondingMenuItemEvent(weakPattern, containerTitleRow, isLeftSplit);
    return containerTitleRow;
}
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
    isTitleShow_ = isShow;
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
    stackRenderContext->SetClipToBounds(true);
    auto customTitleLayoutProperty = customTitleRow->GetLayoutProperty();
    CHECK_NULL_VOID(customTitleLayoutProperty);
    customTitleLayoutProperty->UpdateVisibility(
        (isShow && customTitleSettedShow_) ? VisibleType::VISIBLE : VisibleType::GONE);

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
    controlButtonVisibleBeforeAnim_ = (isShow ? VisibleType::VISIBLE : VisibleType::GONE);
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
    isHoveredMenu_ = false;
    UpdateLightIntensity();
}

void ContainerModalPatternEnhance::OnWindowUnfocused()
{
    if (SubwindowManager::GetInstance()->GetCurrentWindow() &&
        SubwindowManager::GetInstance()->GetCurrentWindow()->GetShown()) {
        isFocus_ = false;
        isHoveredMenu_ = true;
        return;
    }
    ContainerModalPattern::OnWindowUnfocused();
    isHoveredMenu_ = false;
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
            ? InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_RECOVER
            : InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_MAXIMIZE;
    ChangeTitleButtonIcon(maximizeButton, maxId, isFocus, false);

    // update minimize button
    auto minimizeButton =
        AceType::DynamicCast<FrameNode>(GetTitleItemByIndex(controlButtonsNode, MINIMIZE_BUTTON_INDEX));
    ChangeTitleButtonIcon(
        minimizeButton, InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_MINIMIZE, isFocus, false);

    // update close button
    auto closeButton = AceType::DynamicCast<FrameNode>(GetTitleItemByIndex(controlButtonsNode, CLOSE_BUTTON_INDEX));
    ChangeTitleButtonIcon(closeButton, InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_CLOSE, isFocus, true);
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

void ContainerModalPatternEnhance::SetContainerButtonHide(
    bool hideSplit, bool hideMaximize, bool hideMinimize, bool hideClose)
{
    auto controlButtonsNode = GetControlButtonRow();
    CHECK_NULL_VOID(controlButtonsNode);
    enableSplit_ = !hideSplit;

    auto maximizeBtn =
        AceType::DynamicCast<FrameNode>(GetTitleItemByIndex(controlButtonsNode, MAX_RECOVER_BUTTON_INDEX));
    CHECK_NULL_VOID(maximizeBtn);
    maximizeBtn->GetLayoutProperty()->UpdateVisibility(hideMaximize ? VisibleType::GONE : VisibleType::VISIBLE);
    maximizeBtn->MarkDirtyNode();

    auto minimizeBtn = AceType::DynamicCast<FrameNode>(GetTitleItemByIndex(controlButtonsNode, MINIMIZE_BUTTON_INDEX));
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
        controlButtonVisibleBeforeAnim_ = controlButtonsLayoutProperty->GetVisibilityValue();
        controlButtonsLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
        AnimationUtils::Animate(option, [buttonsContext, titlePopupDistance, height]() {
            auto rect = buttonsContext->GetPaintRectWithoutTransform();
            buttonsContext->OnTransformTranslateUpdate({ 0.0f,
                static_cast<float>(
                    height - (titlePopupDistance - CONTAINER_TITLE_HEIGHT.ConvertToPx()) / 2 - rect.GetY()),
                0.0f });
        });
    }

    if (!isShow && CanHideFloatingTitle()) {
        auto beforeVisible = controlButtonVisibleBeforeAnim_;
        AnimationUtils::Animate(
            option,
            [floatingContext, buttonsContext, titlePopupDistance, beforeVisible]() {
                floatingContext->OnTransformTranslateUpdate({ 0.0f, static_cast<float>(-titlePopupDistance), 0.0f });
                buttonsContext->OnTransformTranslateUpdate({ 0.0f,
                    beforeVisible == VisibleType::VISIBLE ? 0.0f : static_cast<float>(-titlePopupDistance), 0.0f });
            },
            [floatingLayoutProperty, controlButtonsLayoutProperty, weak = WeakClaim(this)]() {
                auto pattern = weak.Upgrade();
                CHECK_NULL_VOID(pattern);
                floatingLayoutProperty->UpdateVisibility(VisibleType::GONE);
                controlButtonsLayoutProperty->UpdateVisibility(pattern->controlButtonVisibleBeforeAnim_);
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
    if (colorMode == ColorMode::LIGHT) {
        closeBtnRenderContext_->UpdateLightColor(Color::BLACK);
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
            auto colorMode = SystemProperties::GetColorMode();
            closeBtnRenderContext_->UpdateLightIntensity(
                colorMode == ColorMode::LIGHT ? LIGHT_ON_INTENSITY_LIGHT : LIGHT_ON_INTENSITY_DARK);
        } else {
            closeBtnRenderContext_->UpdateLightIntensity(LIGHT_OFF_INTENSITY);
        }
    });
}

RefPtr<FrameNode> ContainerModalPatternEnhance::GetOrCreateMenuList(const RefPtr<FrameNode>& targetNode)
{
    MeasureContext textCtx;
    textCtx.textContent = Localization::GetInstance()->GetEntryLetters("window.rightSide");
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
        menuList->AddChild(BuildMenuItem(WeakClaim(this), true));
        menuList->AddChild(BuildMenuItem(WeakClaim(this), false));
        menuList_ = menuList;
    }
    auto menuLayoutProperty = menuList_->GetLayoutProperty<ListLayoutProperty>();
    menuLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(GetMenuWidth()), std::nullopt));
    CalculateMenuOffset(targetNode);

    return menuList_;
}

Dimension ContainerModalPatternEnhance::GetMenuWidth()
{
    auto noneTextWidth = TITLE_ICON_SIZE + MENU_ITEM_PADDING_H * 2 + MENU_ITEM_TEXT_PADDING;
    auto menuWidth = Dimension(textWidth_ + noneTextWidth.ConvertToPx());
    return menuWidth;
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
    TAG_LOGI(AceLogTag::ACE_APPBAR, "ContainerModal ShowMaxMenu called menuOffset_ = %{public}s",
        menuOffset_.ToString().c_str());
}

void ContainerModalPatternEnhance::SetTapGestureEvent(RefPtr<FrameNode>& containerTitleRow)
{
    auto eventHub = containerTitleRow->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(eventHub);
    auto tapGesture = AceType::MakeRefPtr<NG::TapGesture>(2, 1);
    CHECK_NULL_VOID(tapGesture);
    WeakPtr<FrameNode> weakNode = frameNode_;
    tapGesture->SetOnActionId([weakNode](GestureEvent& info) mutable {
        TAG_LOGI(AceLogTag::ACE_APPBAR, "container window double click.");
        auto containerNode = weakNode.Upgrade();
        CHECK_NULL_VOID(containerNode);
        auto windowManager = GetNotMovingWindowManager(weakNode);
        CHECK_NULL_VOID(windowManager);
        auto windowMode = windowManager->GetWindowMode();
        auto maximizeMode = windowManager->GetCurrentWindowMaximizeMode();
        if (maximizeMode == MaximizeMode::MODE_AVOID_SYSTEM_BAR || windowMode == WindowMode::WINDOW_MODE_FULLSCREEN ||
            windowMode == WindowMode::WINDOW_MODE_SPLIT_PRIMARY ||
            windowMode == WindowMode::WINDOW_MODE_SPLIT_SECONDARY) {
            EventReport::ReportDoubleClickTitle(DOUBLE_CLICK_TO_RECOVER);
            windowManager->WindowRecover();
        } else if (windowMode == WindowMode::WINDOW_MODE_FLOATING) {
            EventReport::ReportDoubleClickTitle(DOUBLE_CLICK_TO_MAXIMIZE);
            windowManager->WindowMaximize(true);
        }
        containerNode->OnWindowFocused();
    });
    eventHub->AddGesture(tapGesture);
    eventHub->OnModifyDone();
}

void ContainerModalPatternEnhance::OnMaxButtonClick(GestureEvent& info)
{
    TAG_LOGI(AceLogTag::ACE_APPBAR, "maxmize button clicked");
    auto windowManager = GetNotMovingWindowManager(frameNode_);
    if (!windowManager) {
        ResetHoverTimer();
        return;
    }
    TAG_LOGI(AceLogTag::ACE_APPBAR, "maxmize button click event triggerd");
    auto mode = windowManager->GetWindowMode();
    auto currentMode = windowManager->GetCurrentWindowMaximizeMode();
    if (mode == WindowMode::WINDOW_MODE_FULLSCREEN || currentMode == MaximizeMode::MODE_AVOID_SYSTEM_BAR ||
        mode == WindowMode::WINDOW_MODE_SPLIT_PRIMARY || mode == WindowMode::WINDOW_MODE_SPLIT_SECONDARY) {
        EventReport::ReportClickTitleMaximizeMenu(MAX_MENU_ITEM_MAXIMIZE, MAX_BUTTON_CLICK_TO_RECOVER);
        windowManager->WindowRecover();
    } else {
        EventReport::ReportClickTitleMaximizeMenu(MAX_MENU_ITEM_MAXIMIZE, MAX_BUTTON_CLICK_TO_MAXIMIZE);
        windowManager->WindowMaximize(true);
    }
    GetHost()->OnWindowFocused();
}

void ContainerModalPatternEnhance::OnMinButtonClick(GestureEvent& info)
{
    TAG_LOGI(AceLogTag::ACE_APPBAR, "minimize button clicked");
    auto windowManager = GetNotMovingWindowManager(frameNode_);
    CHECK_NULL_VOID(windowManager);
    TAG_LOGI(AceLogTag::ACE_APPBAR, "minimize button click event triggerd");
    windowManager->WindowMinimize();
}

void ContainerModalPatternEnhance::OnCloseButtonClick(GestureEvent& info)
{
    TAG_LOGI(AceLogTag::ACE_APPBAR, "close button clicked");
    auto windowManager = GetNotMovingWindowManager(frameNode_);
    CHECK_NULL_VOID(windowManager);
    TAG_LOGI(AceLogTag::ACE_APPBAR, "close button click event triggerd");
    windowManager->WindowClose();
}

RefPtr<FrameNode> ContainerModalPatternEnhance::ShowMaxMenu(const RefPtr<FrameNode>& targetNode)
{
    CHECK_NULL_RETURN(targetNode, nullptr);
    if (!enableSplit_) {
        TAG_LOGI(AceLogTag::ACE_APPBAR, "the app window is not support spilt menu");
        return nullptr;
    }
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto windowManager = pipeline->GetWindowManager();
    CHECK_NULL_RETURN(windowManager, nullptr);
    // menu list
    auto menuList = GetOrCreateMenuList(targetNode);
    CHECK_NULL_RETURN(menuList, nullptr);
    auto subWindowManger = SubwindowManager::GetInstance();
    CHECK_NULL_RETURN(subWindowManger, nullptr);
    if ((!subWindowManger->GetSubwindow(Container::CurrentId()) ||
            !subWindowManger->GetSubwindow(Container::CurrentId())->GetShown())) {
        ACE_SCOPED_TRACE("ContainerModalViewEnhance::ShowMaxMenu");
        MenuParam menuParam {};
        menuParam.type = MenuType::CONTEXT_MENU;
        SubwindowManager::GetInstance()->ShowMenuNG(menuList, menuParam, targetNode, menuOffset_);
    }
    ResetHoverTimer();
    return menuList;
}

void ContainerModalPatternEnhance::OnMaxBtnGestureEvent(RefPtr<FrameNode>& maximizeBtn)
{
    // add long press event
    auto longPressCallback = [weakPattern = AceType::WeakClaim(this),
                                 weakMaximizeBtn = AceType::WeakClaim(AceType::RawPtr(maximizeBtn))](
                                 GestureEvent& info) {
        auto pattern = weakPattern.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto maximizeBtn = weakMaximizeBtn.Upgrade();
        CHECK_NULL_VOID(maximizeBtn);
        pattern->ShowMaxMenu(maximizeBtn);
    };
    // diable mouse left!
    auto longPressEvent = AceType::MakeRefPtr<LongPressEvent>(longPressCallback);
    auto hub = maximizeBtn->GetOrCreateGestureEventHub();
    hub->SetLongPressEvent(longPressEvent, false, true);
}

void ContainerModalPatternEnhance::OnMaxBtnInputEvent(MouseInfo& info)
{
    isForbidMenuEvent_ = (info.GetButton() == MouseButton::LEFT_BUTTON || info.GetScreenLocation().IsZero());
}

void ContainerModalPatternEnhance::OnMaxBtnHoverEvent(bool hover, WeakPtr<FrameNode>& weakBtn)
{
    if (!hover) {
        ResetHoverTimer();
        isHoveredMenu_ = false;
        return;
    }
    if (isMenuPending_ || isForbidMenuEvent_ || !GetIsFocus()) { // whether can show menu
        return;
    }
    auto&& callback = [weakPattern = WeakClaim(this), weakBtn]() {
        auto maximizeBtn = weakBtn.Upgrade();
        CHECK_NULL_VOID(maximizeBtn);
        auto pattern = weakPattern.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->ShowMaxMenu(maximizeBtn);
    };
    auto pipeline = GetHost()->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    contextTimer_.Reset(callback);
    pipeline->GetTaskExecutor()->PostDelayedTask(
        contextTimer_, TaskExecutor::TaskType::UI, MENU_TASK_DELAY_TIME, "ArkUIContainerModalShowMaxMenu");
    isMenuPending_ = true;
}

void ContainerModalPatternEnhance::OnMenuItemHoverEvent(RefPtr<FrameNode> item, bool isHover)
{
    auto theme = item->GetContextRefPtr()->GetTheme<ListItemTheme>();
    auto renderContext = item->GetRenderContext();
    if (isHover && theme) {
        renderContext->UpdateBackgroundColor(theme->GetItemHoverColor());
    } else {
        renderContext->UpdateBackgroundColor(MENU_ITEM_COLOR);
    }
}

void ContainerModalPatternEnhance::OnMenuItemClickEvent(RefPtr<FrameNode> item, MouseInfo& info)
{
    auto theme = item->GetContextRefPtr()->GetTheme<ListItemTheme>();
    if (MouseAction::PRESS == info.GetAction() && theme) {
        auto renderContext = item->GetRenderContext();
        renderContext->UpdateBackgroundColor(theme->GetClickColor());
    }
}

void ContainerModalPatternEnhance::OnMenuItemClickGesture(bool isSplistLeft)
{
    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    const auto& windowManager = pipeline->GetWindowManager();
    CHECK_NULL_VOID(windowManager);
    int32_t splitSide = isSplistLeft ? MAX_MENU_ITEM_LEFT_SPLIT : MAX_MENU_ITEM_RIGHT_SPLIT;
    EventReport::ReportClickTitleMaximizeMenu(splitSide, MAX_MENU_DEFAULT_NOT_CHANGE);
    windowManager->FireWindowSplitCallBack(isSplistLeft);
}

void ContainerModalPatternEnhance::ResetHoverTimer()
{
    contextTimer_.Reset(nullptr);
    isMenuPending_ = false;
}

bool ContainerModalPatternEnhance::OnDirtyLayoutWrapperSwap(
    const RefPtr<LayoutWrapper>& dirty,
    const DirtySwapConfig& config)
{
    CallButtonsRectChange();

    auto considerFloatingWindow = true;
    CallSetContainerWindow(considerFloatingWindow);
    
    return false;
}
} // namespace OHOS::Ace::NG
