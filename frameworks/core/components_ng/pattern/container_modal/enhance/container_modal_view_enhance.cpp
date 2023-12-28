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

#include "core/components_ng/pattern/container_modal/enhance/container_modal_view_enhance.h"

#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/i18n/localization.h"
#include "base/log/event_report.h"
#include "base/memory/ace_type.h"
#include "base/subwindow/subwindow_manager.h"
#include "base/utils/system_properties.h"
#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/container_modal/container_modal_constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/gestures/pan_gesture.h"
#include "core/components_ng/gestures/tap_gesture.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/container_modal/container_modal_pattern.h"
#include "core/components_ng/pattern/container_modal/enhance/container_modal_pattern_enhance.h"
#include "core/components_ng/pattern/divider/divider_layout_property.h"
#include "core/components_ng/pattern/divider/divider_pattern.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/pattern/patternlock/patternlock_paint_property.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/event/mouse_event.h"
#include "core/image/image_source_info.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace::NG {
/**
 * The structure of container_modal enhanced is designed as follows :
 * |--container_modal(stack)
 *   |--column
 *      |--container_modal_custom_title(row)
 *          |--custom_node(js)
 *      |--stack
 *          |--container_modal_content(stage)
 *              |--page
 *          |--dialog(when show)
 *   |--container_modal_custom_floating_title(row)
 *          |--custom_node(js)
 *   |--container_modal_control_buttons(row)
 *          |--[maxRecover, minimize, close](button)
 */
namespace {
const Dimension MENU_CONTAINER_WIDTH = 240.0_vp;
const Dimension MENU_CONTAINER_HEIGHT = 209.0_vp;
const Dimension MENU_CONTAINER_HEIGHT_HIDE = 100.0_vp;
const Dimension MENU_CONTAINER_DIVIDER_HEIGHT = 9.0_vp;
const Dimension MENU_CONTAINER_DIVIDER_STROKE_HEIGHT = 1.0_vp;
const Dimension MENU_ITEM_RADIUS = 8.0_vp;
const Dimension MENU_ITEM_WIDTH = 232.0_vp;
const Dimension MENU_ITEM_HEIGHT = 48.0_vp;
const Dimension MENU_ITEM_LEFT_PADDING = 12.0_vp;
const Dimension MENU_ITEM_TEXT_WIDTH = 144.0_vp;
const Dimension MENU_ITEM_TEXT_HEIGHT = 22.0_vp;
const Dimension MENU_ITEM_TEXT_PADDING = 8.0_vp;
const Dimension MENU_FLOAT_X = 226.0_vp;
const Dimension MENU_FLOAT_Y = 28.0_vp;
const Dimension MENU_SAFETY_X = 8.0_vp;
const Dimension MENU_SAFETY_Y = 96.0_vp;
const int32_t MENU_ITEM_MAXLINES = 1;
const int32_t MENU_TASK_DELAY_TIME = 600;
const Color MENU_ITEM_HOVER_COLOR = Color(0x0c000000);
const Color MENU_ITEM_PRESS_COLOR = Color(0x1a000000);
const Color MENU_ITEM_COLOR = Color(0xffffff);

const int32_t DOUBLE_CLICK_TO_MAXIMIZE = 1;
const int32_t DOUBLE_CLICK_TO_RECOVER = 2;

const int32_t MAX_MENU_ITEM_LEFT_SPLIT = 1;
const int32_t MAX_MENU_ITEM_RIGHT_SPLIT = 2;
const int32_t MAX_MENU_ITEM_FULLSCREEN = 3;
const int32_t MAX_MENU_ITEM_MAXIMIZE = 4;

const int32_t MAX_MENU_DEFAULT_TO_FULLSCREEN = 1;
const int32_t MAX_MENU_DEFAULT_TO_MAXIMIZE = 2;
const int32_t MAX_MENU_DEFAULT_NOT_CHANGE = 3;
} // namespace
bool ContainerModalViewEnhance::sIsForbidMenuEvent_ = false;
bool ContainerModalViewEnhance::sIsMenuPending_ = false;
bool ContainerModalViewEnhance::enableSplit_ = true;
OffsetF ContainerModalViewEnhance::menuOffset_ = {};
CancelableCallback<void()> ContainerModalViewEnhance::sContextTimer_;

RefPtr<FrameNode> ContainerModalViewEnhance::Create(RefPtr<FrameNode>& content)
{
    auto containerModalNode = FrameNode::CreateFrameNode("ContainerModal",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ContainerModalPatternEnhance>());
    containerModalNode->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_PARENT);
    auto stack = FrameNode::CreateFrameNode(
        V2::STACK_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StackPattern>());
    auto column = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto controlButtonsRow = FrameNode::CreateFrameNode(
        V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), MakeRefPtr<LinearLayoutPattern>(false));

    column->AddChild(BuildTitle(containerModalNode));
    stack->AddChild(content);
    column->AddChild(stack);
    content->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_CONTENT);
    content->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(1.0, DimensionUnit::PERCENT), CalcLength(1.0, DimensionUnit::PERCENT)));
    containerModalNode->AddChild(column);
    containerModalNode->AddChild(BuildTitle(containerModalNode, true));
    containerModalNode->AddChild(AddControlButtons(containerModalNode, controlButtonsRow));

    CHECK_NULL_RETURN(stack->GetLayoutProperty(), nullptr);
    stack->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_PARENT);
    CHECK_NULL_RETURN(column->GetLayoutProperty(), nullptr);
    column->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_PARENT);
    CHECK_NULL_RETURN(controlButtonsRow->GetLayoutProperty(), nullptr);
    controlButtonsRow->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_PARENT);

    auto containerPattern = containerModalNode->GetPattern<ContainerModalPatternEnhance>();
    CHECK_NULL_RETURN(containerPattern, nullptr);
    containerModalNode->MarkModifyDone();
    containerPattern->Init();
    return containerModalNode;
}

RefPtr<FrameNode> ContainerModalViewEnhance::BuildTitle(RefPtr<FrameNode>& containerNode, bool isFloatingTitle)
{
    LOGI("ContainerModalViewEnhance BuildTitle called");
    auto titleRow = BuildTitleContainer(containerNode, isFloatingTitle);
    CHECK_NULL_RETURN(titleRow, nullptr);
    return SetTapGestureEvent(containerNode, titleRow);
}

RefPtr<FrameNode> ContainerModalViewEnhance::SetTapGestureEvent(
    RefPtr<FrameNode>& containerNode, RefPtr<FrameNode>& containerTitleRow)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto windowManager = pipeline->GetWindowManager();
    CHECK_NULL_RETURN(windowManager, nullptr);
    auto eventHub = containerTitleRow->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(eventHub, nullptr);
    auto tapGesture = AceType::MakeRefPtr<NG::TapGesture>(2, 1);
    CHECK_NULL_RETURN(tapGesture, nullptr);
    tapGesture->SetOnActionId([weakContainerNode = AceType::WeakClaim(AceType::RawPtr(containerNode)),
                                  weakWindowManager = AceType::WeakClaim(AceType::RawPtr(windowManager))](
                                  GestureEvent& info) {
        LOGI("container window double click.");
        auto windowManager = weakWindowManager.Upgrade();
        CHECK_NULL_VOID(windowManager);
        auto containerNode = weakContainerNode.Upgrade();
        CHECK_NULL_VOID(containerNode);
        auto windowMode = windowManager->GetWindowMode();
        auto maximizeMode = windowManager->GetCurrentWindowMaximizeMode();
        if (maximizeMode == MaximizeMode::MODE_AVOID_SYSTEM_BAR || windowMode == WindowMode::WINDOW_MODE_FULLSCREEN) {
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
    return containerTitleRow;
}

RefPtr<FrameNode> ContainerModalViewEnhance::AddControlButtons(
    RefPtr<FrameNode>& containerNode, RefPtr<FrameNode>& containerTitleRow)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto windowManager = pipeline->GetWindowManager();
    CHECK_NULL_RETURN(windowManager, nullptr);
    auto controlButtonsRow = SetTapGestureEvent(containerNode, containerTitleRow);
    CHECK_NULL_RETURN(controlButtonsRow, nullptr);
    auto layoutProperty = controlButtonsRow->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, nullptr);
    layoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(1.0, DimensionUnit::PERCENT), CalcLength(CONTAINER_TITLE_HEIGHT)));
    layoutProperty->UpdateMainAxisAlign(FlexAlign::FLEX_END);
    layoutProperty->UpdateCrossAxisAlign(FlexAlign::CENTER);

    RefPtr<FrameNode> maximizeBtn = BuildControlButton(InternalResource::ResourceId::IC_WINDOW_MAX,
        [weak = AceType::WeakClaim(AceType::RawPtr(containerNode)),
            wk = AceType::WeakClaim(AceType::RawPtr(windowManager))](GestureEvent& info) {
            auto containerNode = weak.Upgrade();
            CHECK_NULL_VOID(containerNode);
            auto windowManager = wk.Upgrade();
            CHECK_NULL_VOID(windowManager);
            ResetHoverTimer();
            auto mode = windowManager->GetWindowMode();
            auto currentMode = windowManager->GetCurrentWindowMaximizeMode();
            if (mode == WindowMode::WINDOW_MODE_FULLSCREEN || currentMode == MaximizeMode::MODE_AVOID_SYSTEM_BAR) {
                windowManager->WindowRecover();
            } else {
                windowManager->WindowMaximize(true);
            }
            containerNode->OnWindowFocused();
        });
    maximizeBtn->UpdateInspectorId("EnhanceMaximizeBtn");
    BondingMaxBtnGestureEvent(maximizeBtn, containerNode);
    BondingMaxBtnInputEvent(maximizeBtn, containerNode);
    controlButtonsRow->AddChild(maximizeBtn);

    RefPtr<FrameNode> minimizeBtn = BuildControlButton(InternalResource::ResourceId::IC_WINDOW_MIN,
        [weak = AceType::WeakClaim(AceType::RawPtr(windowManager))](GestureEvent& info) {
            auto windowManager = weak.Upgrade();
            if (!windowManager) {
                LOGE("create minBtn callback func failed,windowManager is null!");
                return;
            }
            LOGI("minimize button clicked");
            windowManager->WindowMinimize();
        });
    // minimizeBtn add empty panEvent to over fater container event
    minimizeBtn->UpdateInspectorId("EnhanceMinimizeBtn");
    controlButtonsRow->AddChild(minimizeBtn);

    RefPtr<FrameNode> closeBtn = BuildControlButton(
        InternalResource::ResourceId::IC_WINDOW_CLOSE,
        [weak = AceType::WeakClaim(AceType::RawPtr(windowManager))](GestureEvent& info) {
            auto windowManager = weak.Upgrade();
            if (!windowManager) {
                LOGE("create closeBtn callback func failed,windowManager is null!");
                return;
            }
            LOGI("close button clicked");
            windowManager->WindowClose();
        },
        true);
    // closeBtn add empty panEvent to over fater container event
    closeBtn->UpdateInspectorId("EnhanceCloseBtn");
    controlButtonsRow->AddChild(closeBtn);

    return controlButtonsRow;
}

void ContainerModalViewEnhance::BondingMaxBtnGestureEvent(
    RefPtr<FrameNode>& maximizeBtn, RefPtr<FrameNode>& containerNode)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    auto windowManager = pipeline->GetWindowManager();
    auto hub = maximizeBtn->GetOrCreateGestureEventHub();

    // add long press event
    auto longPressCallback = [weakMaximizeBtn = AceType::WeakClaim(AceType::RawPtr(maximizeBtn))](GestureEvent& info) {
        auto maximizeBtn = weakMaximizeBtn.Upgrade();
        CHECK_NULL_VOID(maximizeBtn);
        auto menuPosX = info.GetScreenLocation().GetX() - info.GetLocalLocation().GetX() - MENU_FLOAT_X.ConvertToPx();
        auto menuPosY = info.GetScreenLocation().GetY() - info.GetLocalLocation().GetY() + MENU_FLOAT_Y.ConvertToPx();
        OffsetF menuPosition { menuPosX, menuPosY };
        CalculateMenuOffset(menuPosition);
        ShowMaxMenu(maximizeBtn, menuOffset_);
    };
    // diable mouse left!
    auto longPressEvent = AceType::MakeRefPtr<LongPressEvent>(longPressCallback);
    hub->SetLongPressEvent(longPressEvent, false, true);
}

void ContainerModalViewEnhance::BondingMaxBtnInputEvent(
    RefPtr<FrameNode>& maximizeBtn, RefPtr<FrameNode>& containerNode)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    auto windowManager = pipeline->GetWindowManager();
    auto hub = maximizeBtn->GetOrCreateInputEventHub();
    auto hoverMoveFuc = [](MouseInfo& info) {
        sIsForbidMenuEvent_ = info.GetButton() == MouseButton::LEFT_BUTTON ||
                              info.GetAction() == MouseAction::WINDOW_ENTER || info.GetScreenLocation().IsZero();
        if (!sIsMenuPending_ && info.GetAction() == MouseAction::MOVE && !info.GetScreenLocation().IsZero()) {
            auto menuPosX =
                info.GetScreenLocation().GetX() - info.GetLocalLocation().GetX() - MENU_FLOAT_X.ConvertToPx();
            auto menuPosY =
                info.GetScreenLocation().GetY() - info.GetLocalLocation().GetY() + MENU_FLOAT_Y.ConvertToPx();
            OffsetF menuPosition { menuPosX, menuPosY };
            CalculateMenuOffset(menuPosition);
        }
    };
    hub->AddOnMouseEvent(AceType::MakeRefPtr<InputEvent>(std::move(hoverMoveFuc)));

    // add hover in out event
    auto containerPattern = containerNode->GetPattern<ContainerModalPattern>();
    auto hoverEventFuc = [weakMaximizeBtn = AceType::WeakClaim(AceType::RawPtr(maximizeBtn)),
                             weakContainerPattern = AceType::WeakClaim(AceType::RawPtr(containerPattern)),
                             weakPipeline = AceType::WeakClaim(AceType::RawPtr(pipeline))](bool hover) {
        if (!hover) {
            ResetHoverTimer();
            return;
        }
        auto pattern = weakContainerPattern.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (sIsMenuPending_ || sIsForbidMenuEvent_ || !pattern->GetIsFocus()) {
            return;
        }
        auto maximizeBtn = weakMaximizeBtn.Upgrade();
        CHECK_NULL_VOID(maximizeBtn);
        auto pipeline = weakPipeline.Upgrade();
        CHECK_NULL_VOID(pipeline);
        auto&& callback = [weakMaximizeBtn = AceType::WeakClaim(AceType::RawPtr(maximizeBtn))]() {
            auto maximizeBtn = weakMaximizeBtn.Upgrade();
            ShowMaxMenu(maximizeBtn, menuOffset_);
        };
        sContextTimer_.Reset(callback);
        ACE_SCOPED_TRACE("ContainerModalEnhance::PendingMaxMenu");
        pipeline->GetTaskExecutor()->PostDelayedTask(sContextTimer_, TaskExecutor::TaskType::UI, MENU_TASK_DELAY_TIME);
        sIsMenuPending_ = true;
    };
    hub->AddOnHoverEvent(AceType::MakeRefPtr<InputEvent>(std::move(hoverEventFuc)));
}

RefPtr<FrameNode> ContainerModalViewEnhance::ShowMaxMenu(const RefPtr<FrameNode>& targetNode, OffsetF menuPosition)
{
    LOGI("ShowMaxMenu called");
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto windowManager = pipeline->GetWindowManager();
    CHECK_NULL_RETURN(windowManager, nullptr);
    // menu list
    auto menuList = FrameNode::CreateFrameNode(
        V2::LIST_COMPONENT_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ListPattern>());
    auto listLayoutProperty = menuList->GetLayoutProperty<ListLayoutProperty>();
    CHECK_NULL_RETURN(listLayoutProperty, nullptr);
    listLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(MENU_CONTAINER_WIDTH),
        CalcLength(enableSplit_ ? MENU_CONTAINER_HEIGHT : MENU_CONTAINER_HEIGHT_HIDE)));
    menuList->AddChild(BuildMaximizeMenuItem());
    menuList->AddChild(BuildFullScreenMenuItem());
    if (enableSplit_) {
        menuList->AddChild(BuildDividerMenuItem());
        menuList->AddChild(BuildLeftSplitMenuItem());
        menuList->AddChild(BuildRightSplitMenuItem());
    }
    auto subWindowManger = SubwindowManager::GetInstance();
    CHECK_NULL_RETURN(subWindowManger, nullptr);
    if ((!subWindowManger->GetSubwindow(Container::CurrentId()) ||
            !subWindowManger->GetSubwindow(Container::CurrentId())->GetShown())) {
        ACE_SCOPED_TRACE("ContainerModalViewEnhance::ShowMaxMenu");
        MenuParam menu {};
        menu.isAboveApps = true;
        menu.type = MenuType::CONTEXT_MENU;
        ViewAbstract::BindMenuWithCustomNode(menuList, targetNode, menuPosition, menu);
    }
    ResetHoverTimer();
    return menuList;
}

RefPtr<FrameNode> ContainerModalViewEnhance::BuildMaximizeMenuItem()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto windowManager = pipeline->GetWindowManager();
    CHECK_NULL_RETURN(windowManager, nullptr);
    // click maxize Item Event
    auto maximizeClickFunc = [weak = AceType::WeakClaim(AceType::RawPtr(windowManager))](GestureEvent& info) {
        auto windowManager = weak.Upgrade();
        if (!windowManager) {
            LOGE("create maxBtn callback func failed,windowManager is null");
            return;
        }
        ResetHoverTimer();
        if (MaximizeMode::MODE_AVOID_SYSTEM_BAR == windowManager->GetCurrentWindowMaximizeMode()) {
            EventReport::ReportClickTitleMaximizeMenu(MAX_MENU_ITEM_MAXIMIZE, MAX_MENU_DEFAULT_NOT_CHANGE);
            windowManager->WindowRecover();
        } else {
            ACE_SCOPED_TRACE("ContainerModalViewEnhance::SwithToMaximize");
            EventReport::ReportClickTitleMaximizeMenu(MAX_MENU_ITEM_MAXIMIZE, MAX_MENU_DEFAULT_TO_MAXIMIZE);
            windowManager->SetWindowMaximizeMode(MaximizeMode::MODE_AVOID_SYSTEM_BAR);
            windowManager->WindowMaximize(true);
        }
    };
    auto maximizeEvent = AceType::MakeRefPtr<ClickEvent>(std::move(maximizeClickFunc));
    auto curMaxMode = windowManager->GetCurrentWindowMaximizeMode();
    auto maximizeTitle = Localization::GetInstance()->GetEntryLetters(
        curMaxMode == MaximizeMode::MODE_AVOID_SYSTEM_BAR ? "window.exitMaximize" : "window.maximize");
    auto maximizeRow = BuildMenuItem(maximizeTitle, InternalResource::ResourceId::IC_WINDOW_MENU_MAXIMIZE,
        maximizeEvent, windowManager->GetWindowMaximizeMode() == MaximizeMode::MODE_AVOID_SYSTEM_BAR);
    maximizeRow->UpdateInspectorId("EnhanceMenuMaximizeRow");
    PaddingProperty pad;
    pad.left = CalcLength(CONTENT_PADDING);
    return BuildMenuItemPadding(pad, maximizeRow);
}

RefPtr<FrameNode> ContainerModalViewEnhance::BuildFullScreenMenuItem()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto windowManager = pipeline->GetWindowManager();
    CHECK_NULL_RETURN(windowManager, nullptr);
    auto fullScreenClickFunc = [weak = AceType::WeakClaim(AceType::RawPtr(windowManager))](GestureEvent& info) {
        auto windowManager = weak.Upgrade();
        if (!windowManager) {
            LOGE("create fullScreen callback func failed,windowManager is null!");
            return;
        }
        ResetHoverTimer();
        if (MaximizeMode::MODE_FULL_FILL == windowManager->GetCurrentWindowMaximizeMode()) {
            EventReport::ReportClickTitleMaximizeMenu(MAX_MENU_ITEM_FULLSCREEN, MAX_MENU_DEFAULT_NOT_CHANGE);
        } else {
            EventReport::ReportClickTitleMaximizeMenu(MAX_MENU_ITEM_FULLSCREEN, MAX_MENU_DEFAULT_TO_FULLSCREEN);
        }

        if (MaximizeMode::MODE_FULL_FILL == windowManager->GetCurrentWindowMaximizeMode() &&
            WindowMode::WINDOW_MODE_FULLSCREEN == windowManager->GetWindowMode()) {
            windowManager->WindowRecover();
        } else {
            ACE_SCOPED_TRACE("ContainerModalViewEnhance::SwithToFULLFILL");
            windowManager->SetWindowMaximizeMode(MaximizeMode::MODE_FULL_FILL);
            windowManager->WindowMaximize(true);
        }
    };
    auto fullScreenEvent = AceType::MakeRefPtr<ClickEvent>(std::move(fullScreenClickFunc));
    auto fullScreenTitle = Localization::GetInstance()->GetEntryLetters(
        WindowMode::WINDOW_MODE_FULLSCREEN == windowManager->GetWindowMode() ? "window.exitFullScreen"
                                                                             : "window.fullScreen");
    auto fullScreenRow = BuildMenuItem(fullScreenTitle, InternalResource::ResourceId::IC_WINDOW_MENU_FULLSCREEN,
        fullScreenEvent, windowManager->GetWindowMaximizeMode() == MaximizeMode::MODE_FULL_FILL);
    fullScreenRow->UpdateInspectorId("EnhanceMenuFullScreenRow");
    PaddingProperty pad;
    pad.left = CalcLength(CONTENT_PADDING);
    return BuildMenuItemPadding(pad, fullScreenRow);
}

RefPtr<FrameNode> ContainerModalViewEnhance::BuildDividerMenuItem()
{
    auto divider = FrameNode::CreateFrameNode(V2::DIVIDER_COMPONENT_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<DividerPattern>());
    auto dividerLayout = divider->GetLayoutProperty<DividerLayoutProperty>();
    dividerLayout->UpdateStrokeWidth(MENU_CONTAINER_DIVIDER_STROKE_HEIGHT);
    dividerLayout->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(MENU_CONTAINER_WIDTH), CalcLength(MENU_CONTAINER_DIVIDER_HEIGHT)));
    PaddingProperty pad;
    pad.left = CalcLength(CONTENT_PADDING);
    return BuildMenuItemPadding(pad, divider);
}

RefPtr<FrameNode> ContainerModalViewEnhance::BuildLeftSplitMenuItem()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto windowManager = pipeline->GetWindowManager();
    CHECK_NULL_RETURN(windowManager, nullptr);
    auto leftSplitClickFunc = [weak = AceType::WeakClaim(AceType::RawPtr(windowManager))](GestureEvent& info) {
        auto windowManager = weak.Upgrade();
        if (!windowManager) {
            LOGE("create leftsplit callback func failed,windowMannager is null!");
            return;
        }
        EventReport::ReportClickTitleMaximizeMenu(MAX_MENU_ITEM_LEFT_SPLIT, MAX_MENU_DEFAULT_NOT_CHANGE);
        windowManager->FireWindowSplitCallBack();
    };
    auto leftSplitEvent = AceType::MakeRefPtr<ClickEvent>(std::move(leftSplitClickFunc));
    auto screenLeftRow = BuildMenuItem(Localization::GetInstance()->GetEntryLetters("window.leftSide"),
        InternalResource::ResourceId::IC_WINDOW_MENU_SCREEN_L, leftSplitEvent, false);
    screenLeftRow->UpdateInspectorId("EnhanceMenuScreenLeftRow");
    PaddingProperty pad;
    pad.left = CalcLength(CONTENT_PADDING);
    return BuildMenuItemPadding(pad, screenLeftRow);
}

RefPtr<FrameNode> ContainerModalViewEnhance::BuildRightSplitMenuItem()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto windowManager = pipeline->GetWindowManager();
    CHECK_NULL_RETURN(windowManager, nullptr);
    auto rightSplitClickFunc = [weak = AceType::WeakClaim(AceType::RawPtr(windowManager))](GestureEvent& info) {
        auto windowManager = weak.Upgrade();
        if (!windowManager) {
            LOGE("create rightSpiltBtn callback func failed, windowManager is null!");
            return;
        }
        EventReport::ReportClickTitleMaximizeMenu(MAX_MENU_ITEM_RIGHT_SPLIT, MAX_MENU_DEFAULT_NOT_CHANGE);
        windowManager->FireWindowSplitCallBack(false);
    };
    auto rightSplitEvent = AceType::MakeRefPtr<ClickEvent>(std::move(rightSplitClickFunc));
    auto screenRightRow = BuildMenuItem(Localization::GetInstance()->GetEntryLetters("window.rightSide"),
        InternalResource::ResourceId::IC_WINDOW_MENU_SCREEN_N, rightSplitEvent, false);
    screenRightRow->UpdateInspectorId("EnhanceMenuScreenRightRow");
    PaddingProperty pad;
    pad.left = CalcLength(CONTENT_PADDING);
    return BuildMenuItemPadding(pad, screenRightRow);
}

RefPtr<FrameNode> ContainerModalViewEnhance::BuildMenuItem(
    std::string title, InternalResource::ResourceId resourceId, RefPtr<ClickEvent> event, bool chooseCurrent)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto windowManager = pipeline->GetWindowManager();
    CHECK_NULL_RETURN(windowManager, nullptr);

    // padding+pic+padding+text+padding+
    auto containerTitleRow = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    // setRadius 8vp
    auto render = containerTitleRow->GetRenderContext();
    BorderRadiusProperty borderRadiusProperty;
    borderRadiusProperty.SetRadius(MENU_ITEM_RADIUS);
    render->UpdateBorderRadius(borderRadiusProperty);
    // 232 48  leftPadding 4vp
    auto layoutProperty = containerTitleRow->GetLayoutProperty<LinearLayoutProperty>();
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(MENU_ITEM_WIDTH), CalcLength(MENU_ITEM_HEIGHT)));
    layoutProperty->UpdateMainAxisAlign(FlexAlign::FLEX_START);
    layoutProperty->UpdateCrossAxisAlign(FlexAlign::CENTER);
    PaddingProperty rowLeftPadding;
    rowLeftPadding.left = CalcLength(MENU_ITEM_LEFT_PADDING);
    layoutProperty->UpdatePadding(rowLeftPadding);

    auto leftIcon = BuildMenuItemIcon(resourceId);
    containerTitleRow->AddChild(leftIcon);

    // text 144 22  padding 8vp
    auto titleLabel = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto textLayoutProperty = titleLabel->GetLayoutProperty<TextLayoutProperty>();
    textLayoutProperty->UpdateContent(title);
    textLayoutProperty->UpdateMaxLines(MENU_ITEM_MAXLINES);
    textLayoutProperty->UpdateFontSize(TITLE_TEXT_FONT_SIZE);
    textLayoutProperty->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    textLayoutProperty->UpdateAlignment(Alignment::CENTER_LEFT);
    textLayoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(MENU_ITEM_TEXT_WIDTH), CalcLength(MENU_ITEM_TEXT_HEIGHT)));
    PaddingProperty padding;
    padding.left = CalcLength(MENU_ITEM_TEXT_PADDING);
    auto text = BuildMenuItemPadding(padding, titleLabel);

    // add icon and label
    containerTitleRow->AddChild(leftIcon);
    containerTitleRow->AddChild(text);
    if (chooseCurrent) {
        auto chooseIcon = BuildMenuItemIcon(InternalResource::ResourceId::IC_WINDOW_MENU_OK);
        auto iconLayoutProperty = chooseIcon->GetLayoutProperty<ImageLayoutProperty>();
        PaddingProperty chooseIconLeftPadding;
        chooseIconLeftPadding.left = CalcLength(MENU_ITEM_TEXT_PADDING);
        containerTitleRow->AddChild(BuildMenuItemPadding(chooseIconLeftPadding, chooseIcon));
    }
    auto hub = containerTitleRow->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(hub, nullptr);
    hub->AddClickEvent(event);
    BondingMenuItemEvent(containerTitleRow);
    return containerTitleRow;
}

void ContainerModalViewEnhance::BondingMenuItemEvent(RefPtr<FrameNode> item)
{
    auto inputHub = item->GetOrCreateInputEventHub();
    auto hoverFunc = [item](bool isHover) {
        auto renderContext = item->GetRenderContext();
        if (isHover) {
            renderContext->UpdateBackgroundColor(MENU_ITEM_HOVER_COLOR);
        } else {
            renderContext->UpdateBackgroundColor(MENU_ITEM_COLOR);
        }
    };
    auto hoverEvent = AceType::MakeRefPtr<InputEvent>(std::move(hoverFunc));
    inputHub->AddOnHoverEvent(hoverEvent);

    auto clickFunc = [item](MouseInfo& info) -> void {
        if (MouseAction::PRESS == info.GetAction()) {
            auto renderContext = item->GetRenderContext();
            renderContext->UpdateBackgroundColor(MENU_ITEM_PRESS_COLOR);
        }
    };
    auto clickEvent = AceType::MakeRefPtr<InputEvent>(std::move(clickFunc));
    inputHub->AddOnMouseEvent(clickEvent);
}

RefPtr<FrameNode> ContainerModalViewEnhance::BuildMenuItemIcon(InternalResource::ResourceId resourceId)
{
    auto icon = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    auto iconLayoutProperty = icon->GetLayoutProperty<ImageLayoutProperty>();
    ImageSourceInfo sourceInfo;
    sourceInfo.SetResourceId(resourceId);
    iconLayoutProperty->UpdateImageSourceInfo(sourceInfo);
    iconLayoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(TITLE_BUTTON_SIZE), CalcLength(TITLE_BUTTON_SIZE)));
    icon->MarkModifyDone();
    return icon;
}

RefPtr<FrameNode> ContainerModalViewEnhance::BuildMenuItemPadding(PaddingProperty padding, RefPtr<FrameNode> node)
{
    auto row = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));

    auto rowLayoutProperty = row->GetLayoutProperty<LinearLayoutProperty>();
    rowLayoutProperty->UpdatePadding(padding);
    row->AddChild(node);

    return row;
}

void ContainerModalViewEnhance::ResetHoverTimer()
{
    sContextTimer_.Reset(nullptr);
    sIsMenuPending_ = false;
}

void ContainerModalViewEnhance::CalculateMenuOffset(OffsetF currentOffset)
{
    auto screenWidth = SystemProperties::GetDevicePhysicalWidth();
    auto screenHeight = SystemProperties::GetDevicePhysicalHeight();
    auto offsetX = currentOffset.GetX();
    auto offsetY = currentOffset.GetY();
    auto menuWidth = MENU_CONTAINER_WIDTH.ConvertToPx() + CONTENT_PADDING.ConvertToPx() * 2;
    auto menuHeight = MENU_CONTAINER_HEIGHT.ConvertToPx() + CONTENT_PADDING.ConvertToPx() * 2;
    auto buttonWidth = TITLE_ICON_SIZE.ConvertToPx() + CONTENT_PADDING.ConvertToPx() * 2;
    if (offsetX < MENU_SAFETY_X.ConvertToPx()) {
        LOGI("ContainerModalViewEnhance::RecalculateMenuOffset OffsetX cover screen left");
        offsetX = offsetX + menuWidth - buttonWidth;
    }
    if (offsetX > screenWidth - menuWidth - MENU_SAFETY_X.ConvertToPx()) {
        LOGI("ContainerModalViewEnhance::RecalculateMenuOffset OffsetX cover screen right");
        offsetX = screenWidth - menuWidth - MENU_SAFETY_X.ConvertToPx();
    }
    if (offsetY > screenHeight - menuHeight - MENU_SAFETY_Y.ConvertToPx()) {
        LOGI("ContainerModalViewEnhance::RecalculateMenuOffset OffsetX cover screen bottom");
        offsetY = offsetY - menuHeight - CONTAINER_TITLE_HEIGHT.ConvertToPx();
    }
    menuOffset_ = { offsetX, offsetY };
}
} // namespace OHOS::Ace::NG