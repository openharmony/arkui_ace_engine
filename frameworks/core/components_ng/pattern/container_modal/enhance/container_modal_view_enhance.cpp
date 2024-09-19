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
#include "core/common/container.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/theme/advanced_pattern_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/gestures/tap_gesture.h"
#include "core/components_ng/pattern/container_modal/container_modal_pattern.h"
#include "core/components_ng/pattern/container_modal/enhance/container_modal_pattern_enhance.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/list/list_pattern.h"
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
 *      |--gesture_row(row)
 *   |--container_modal_custom_floating_title(row)
 *          |--custom_node(js)
 *   |--container_modal_control_buttons(row)
 *          |--[maxRecover, minimize, close](button)
 */
namespace {
const int32_t MENU_TASK_DELAY_TIME = 600;
const Color MENU_ITEM_COLOR = Color(0xffffff);

const int32_t DOUBLE_CLICK_TO_MAXIMIZE = 1;
const int32_t DOUBLE_CLICK_TO_RECOVER = 2;

const int32_t MAX_BUTTON_CLICK_TO_MAXIMIZE = 1;
const int32_t MAX_BUTTON_CLICK_TO_RECOVER = 2;

const int32_t MAX_MENU_ITEM_MAXIMIZE = 3;

} // namespace
bool ContainerModalViewEnhance::sIsForbidMenuEvent_ = false;
bool ContainerModalViewEnhance::sIsMenuPending_ = false;
bool ContainerModalViewEnhance::enableSplit_ = true;
CancelableCallback<void()> ContainerModalViewEnhance::sContextTimer_;

RefPtr<FrameNode> ContainerModalViewEnhance::Create(RefPtr<FrameNode>& content)
{
    auto containerModalNode = FrameNode::CreateFrameNode("ContainerModal",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ContainerModalPatternEnhance>());
    auto stack = FrameNode::CreateFrameNode(
        V2::STACK_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StackPattern>());
    auto column = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto controlButtonsRow = FrameNode::CreateFrameNode(
        V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), MakeRefPtr<LinearLayoutPattern>(false));

    column->AddChild(BuildTitle(containerModalNode));
    stack->AddChild(content);
    column->AddChild(stack);
    column->AddChild(BuildGestureRow(containerModalNode));
    auto containerPattern = containerModalNode->GetPattern<ContainerModalPatternEnhance>();
    CHECK_NULL_RETURN(containerPattern, nullptr);
    containerModalNode->AddChild(column);
    containerModalNode->AddChild(BuildTitle(containerModalNode, true));
    containerModalNode->AddChild(AddControlButtons(containerModalNode, controlButtonsRow));
    containerPattern->Init();
    return containerModalNode;
}

RefPtr<FrameNode> ContainerModalViewEnhance::BuildTitle(RefPtr<FrameNode>& containerNode, bool isFloatingTitle)
{
    TAG_LOGI(AceLogTag::ACE_APPBAR, "ContainerModalViewEnhance BuildTitle called");
    auto titleRow = BuildTitleContainer(containerNode, isFloatingTitle);
    CHECK_NULL_RETURN(titleRow, nullptr);
    SetTapGestureEvent(containerNode, titleRow);
    return titleRow;
}

void ContainerModalViewEnhance::SetTapGestureEvent(
    RefPtr<FrameNode>& containerNode, RefPtr<FrameNode>& containerTitleRow)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto windowManager = pipeline->GetWindowManager();
    CHECK_NULL_VOID(windowManager);
    auto eventHub = containerTitleRow->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(eventHub);
    auto tapGesture = AceType::MakeRefPtr<NG::TapGesture>(2, 1);
    CHECK_NULL_VOID(tapGesture);
    tapGesture->SetOnActionId([weakContainerNode = AceType::WeakClaim(AceType::RawPtr(containerNode)),
                                  weakWindowManager = AceType::WeakClaim(AceType::RawPtr(windowManager))](
                                  GestureEvent& info) {
        TAG_LOGI(AceLogTag::ACE_APPBAR, "container window double click.");
        auto windowManager = weakWindowManager.Upgrade();
        CHECK_NULL_VOID(windowManager);
        auto containerNode = weakContainerNode.Upgrade();
        CHECK_NULL_VOID(containerNode);
        bool isMoving = windowManager->GetWindowStartMoveFlag();
        if (isMoving) {
            TAG_LOGI(AceLogTag::ACE_APPBAR, "window is moving, double-click is not supported.");
            return;
        }
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

RefPtr<FrameNode> ContainerModalViewEnhance::AddControlButtons(
    RefPtr<FrameNode>& containerNode, RefPtr<FrameNode>& containerTitleRow)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto windowManager = pipeline->GetWindowManager();
    CHECK_NULL_RETURN(windowManager, nullptr);

    RefPtr<FrameNode> maximizeBtn = BuildControlButton(InternalResource::ResourceId::IC_WINDOW_MAX,
        [weak = AceType::WeakClaim(AceType::RawPtr(containerNode)),
            wk = AceType::WeakClaim(AceType::RawPtr(windowManager))](GestureEvent& info) {
            auto containerNode = weak.Upgrade();
            CHECK_NULL_VOID(containerNode);
            auto windowManager = wk.Upgrade();
            CHECK_NULL_VOID(windowManager);
            ResetHoverTimer();
            bool isMoving = windowManager->GetWindowStartMoveFlag();
            if (isMoving) {
                TAG_LOGI(AceLogTag::ACE_APPBAR, "window is moving, maximization is not supported.");
                return;
            }
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
            containerNode->OnWindowFocused();
        });
    maximizeBtn->UpdateInspectorId("EnhanceMaximizeBtn");
    BondingMaxBtnGestureEvent(maximizeBtn, containerNode);
    BondingMaxBtnInputEvent(maximizeBtn, containerNode);
    containerTitleRow->AddChild(maximizeBtn);

    RefPtr<FrameNode> minimizeBtn = BuildControlButton(InternalResource::ResourceId::IC_WINDOW_MIN,
        [weak = AceType::WeakClaim(AceType::RawPtr(windowManager))](GestureEvent& info) {
            auto windowManager = weak.Upgrade();
            if (!windowManager) {
                TAG_LOGE(AceLogTag::ACE_APPBAR, "create minBtn callback func failed,windowManager is null!");
                return;
            }
            bool isMoving = windowManager->GetWindowStartMoveFlag();
            if (isMoving) {
                TAG_LOGI(AceLogTag::ACE_APPBAR, "window is moving, minimization is not supported.");
                return;
            }
            TAG_LOGI(AceLogTag::ACE_APPBAR, "minimize button clicked");
            windowManager->WindowMinimize();
        });
    // minimizeBtn add empty panEvent to over fater container event
    minimizeBtn->UpdateInspectorId("EnhanceMinimizeBtn");
    containerTitleRow->AddChild(minimizeBtn);

    RefPtr<FrameNode> closeBtn = BuildControlButton(
        InternalResource::ResourceId::IC_WINDOW_CLOSE,
        [weak = AceType::WeakClaim(AceType::RawPtr(windowManager))](GestureEvent& info) {
            auto windowManager = weak.Upgrade();
            if (!windowManager) {
                TAG_LOGE(AceLogTag::ACE_APPBAR, "create closeBtn callback func failed,windowManager is null!");
                return;
            }
            bool isMoving = windowManager->GetWindowStartMoveFlag();
            if (isMoving) {
                TAG_LOGI(AceLogTag::ACE_APPBAR, "window is moving, closing is not supported");
                return;
            }
            TAG_LOGI(AceLogTag::ACE_APPBAR, "close button clicked");
            windowManager->WindowClose();
        },
        true);
    // closeBtn add empty panEvent to over fater container event
    closeBtn->UpdateInspectorId("EnhanceCloseBtn");
    containerTitleRow->AddChild(closeBtn);

    return containerTitleRow;
}

void ContainerModalViewEnhance::BondingMaxBtnGestureEvent(
    RefPtr<FrameNode>& maximizeBtn, RefPtr<FrameNode>& containerNode)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    auto windowManager = pipeline->GetWindowManager();
    auto hub = maximizeBtn->GetOrCreateGestureEventHub();

    // add long press event
    auto longPressCallback = [weakMaximizeBtn = AceType::WeakClaim(AceType::RawPtr(maximizeBtn)),
                                 weakContainer = AceType::WeakClaim(AceType::RawPtr(containerNode))](
                                 GestureEvent& info) {
        auto container = weakContainer.Upgrade();
        auto maximizeBtn = weakMaximizeBtn.Upgrade();
        ShowMaxMenu(container, maximizeBtn);
    };
    // diable mouse left!
    auto longPressEvent = AceType::MakeRefPtr<LongPressEvent>(longPressCallback);
    hub->SetLongPressEvent(longPressEvent, false, true);
}

void ContainerModalViewEnhance::BondingMaxBtnInputEvent(
    RefPtr<FrameNode>& maximizeBtn, RefPtr<FrameNode>& containerNode)
{
    auto pipeline  = containerNode->GetContextRefPtr();
    auto hub = maximizeBtn->GetOrCreateInputEventHub();
    auto hoverMoveFuc = [](MouseInfo& info) {
        sIsForbidMenuEvent_ = info.GetButton() == MouseButton::LEFT_BUTTON || info.GetScreenLocation().IsZero();
    };
    hub->AddOnMouseEvent(AceType::MakeRefPtr<InputEvent>(std::move(hoverMoveFuc)));

    // add hover in out event
    auto hoverEventFuc = [weakMaximizeBtn = AceType::WeakClaim(AceType::RawPtr(maximizeBtn)),
                             weakContainer = AceType::WeakClaim(AceType::RawPtr(containerNode)),
                             weakPipeline = AceType::WeakClaim(AceType::RawPtr(pipeline))](bool hover) {
        if (!hover) {
            ResetHoverTimer();
            return;
        }
        auto container = weakContainer.Upgrade();
        CHECK_NULL_VOID(container);
        auto containerPattern = container->GetPattern<ContainerModalPattern>();
        if (sIsMenuPending_ || sIsForbidMenuEvent_ || !containerPattern->GetIsFocus()) {
            return;
        }
        auto pipeline = weakPipeline.Upgrade();
        CHECK_NULL_VOID(pipeline);
        auto&& callback = [weakMaximizeBtn, weakContainer]() {
            auto maximizeBtn = weakMaximizeBtn.Upgrade();
            auto container = weakContainer.Upgrade();
            ShowMaxMenu(container, maximizeBtn);
        };
        sContextTimer_.Reset(callback);
        ACE_SCOPED_TRACE("ContainerModalEnhance::PendingMaxMenu");
        pipeline->GetTaskExecutor()->PostDelayedTask(sContextTimer_, TaskExecutor::TaskType::UI, MENU_TASK_DELAY_TIME,
            "ArkUIContainerModalShowMaxMenu");
        sIsMenuPending_ = true;
    };
    hub->AddOnHoverEvent(AceType::MakeRefPtr<InputEvent>(std::move(hoverEventFuc)));
}

RefPtr<FrameNode> ContainerModalViewEnhance::ShowMaxMenu(
    RefPtr<FrameNode>& container, const RefPtr<FrameNode>& targetNode)
{
    CHECK_NULL_RETURN(container, nullptr);
    CHECK_NULL_RETURN(targetNode, nullptr);if (!enableSplit_) {
        TAG_LOGI(AceLogTag::ACE_APPBAR, "the app window is not support spilt menu");
        return nullptr;
    }
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto windowManager = pipeline->GetWindowManager();
    CHECK_NULL_RETURN(windowManager, nullptr);
    // menu list
    auto containerPattern = container->GetPattern<ContainerModalPatternEnhance>();
    auto menuList = containerPattern->GetOrCreateMenuList(targetNode);
    CHECK_NULL_RETURN(menuList, nullptr);
    auto subWindowManger = SubwindowManager::GetInstance();
    CHECK_NULL_RETURN(subWindowManger, nullptr);
    if ((!subWindowManger->GetSubwindow(Container::CurrentId()) ||
            !subWindowManger->GetSubwindow(Container::CurrentId())->GetShown())) {
        ACE_SCOPED_TRACE("ContainerModalViewEnhance::ShowMaxMenu");
        MenuParam menuParam {};
        menuParam.type = MenuType::CONTEXT_MENU;
        auto offset = containerPattern->GetMenuOffset();
        SubwindowManager::GetInstance()->ShowMenuNG(menuList, menuParam, targetNode, offset);
    }
    ResetHoverTimer();
    return menuList;
}

void ContainerModalViewEnhance::BondingMenuItemEvent(RefPtr<FrameNode> item)
{
    auto inputHub = item->GetOrCreateInputEventHub();
    auto hoverFunc = [item](bool isHover) {
        auto theme = item->GetContextRefPtr()->GetTheme<ListItemTheme>();
        auto renderContext = item->GetRenderContext();
        if (isHover && theme) {
            renderContext->UpdateBackgroundColor(theme->GetItemHoverColor());
        } else {
            renderContext->UpdateBackgroundColor(MENU_ITEM_COLOR);
        }
    };
    auto hoverEvent = AceType::MakeRefPtr<InputEvent>(std::move(hoverFunc));
    inputHub->AddOnHoverEvent(hoverEvent);

    auto clickFunc = [item](MouseInfo& info) -> void {
        auto theme = item->GetContextRefPtr()->GetTheme<ListItemTheme>();
        if (MouseAction::PRESS == info.GetAction() && theme) {
            auto renderContext = item->GetRenderContext();
            renderContext->UpdateBackgroundColor(theme->GetClickColor());
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
    auto theme = PipelineContext::GetCurrentContext()->GetTheme<AdvancedPatternTheme>();
    if (theme) {
        sourceInfo.SetFillColor(theme->GetPrimaryColor());
    } else {
        TAG_LOGI(AceLogTag::ACE_APPBAR, "BuildMenuItemIcon AdvancedPatternTheme is null");
    }
    iconLayoutProperty->UpdateImageSourceInfo(sourceInfo);
    iconLayoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(TITLE_BUTTON_SIZE), CalcLength(TITLE_BUTTON_SIZE)));
    icon->MarkModifyDone();
    return icon;
}

void ContainerModalViewEnhance::ResetHoverTimer()
{
    sContextTimer_.Reset(nullptr);
    sIsMenuPending_ = false;
}

RefPtr<FrameNode> ContainerModalViewEnhance::BuildGestureRow(RefPtr<FrameNode>& containerNode)
{
    auto gestureRow = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    auto renderContext = gestureRow->GetRenderContext();
    renderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    renderContext->UpdatePosition(OffsetT<Dimension>());
    SetTapGestureEvent(containerNode, gestureRow);
    auto layoutProp = gestureRow->GetLayoutProperty();
    layoutProp->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(1.0, DimensionUnit::PERCENT), CalcLength(CONTAINER_TITLE_HEIGHT)));
    return gestureRow;
}

} // namespace OHOS::Ace::NG
