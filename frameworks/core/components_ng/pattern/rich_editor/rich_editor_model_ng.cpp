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

#include "core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"

#include "base/subwindow/subwindow_manager.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/common/ace_engine.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_event_hub.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_pattern.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"
#include "core/components_ng/pattern/menu/menu_view.h"
#include "core/components_ng/pattern/text/text_layout_property.h"

namespace OHOS::Ace::NG {

constexpr int32_t LONG_PRESS_DURATION = 800;
void RichEditorModelNG::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::RICH_EDITOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<RichEditorPattern>(); });
    stack->Push(frameNode);
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, TextAlign, TextAlign::START);
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, Alignment, Alignment::CENTER_LEFT);
    CHECK_NULL_VOID(frameNode);
    auto richEditorPattern = frameNode->GetPattern<RichEditorPattern>();
    richEditorPattern->SetRichEditorController(AceType::MakeRefPtr<RichEditorController>());
    richEditorPattern->GetRichEditorController()->SetPattern(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));

    richEditorPattern->InitSurfaceChangedCallback();

    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<RichEditorTheme>();
    CHECK_NULL_VOID(theme);
    SetDraggable(theme->GetDraggable());
}

void RichEditorModelNG::SetDraggable(bool draggable)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    frameNode->SetDraggable(draggable);
}

RefPtr<RichEditorControllerBase> RichEditorModelNG::GetRichEditorController()
{
    auto richEditorPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<RichEditorPattern>();
    CHECK_NULL_RETURN(richEditorPattern, nullptr);
    RefPtr<RichEditorControllerBase> controller = richEditorPattern->GetRichEditorController();
    if (!controller) {
        LOGE("RichEditorModelNG::GetRichEditorController: RichEditorControllerBase is null");
    }
    return controller;
}

void RichEditorModelNG::SetOnReady(std::function<void()>&& func)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnReady(std::move(func));
}

void RichEditorModelNG::SetOnSelect(std::function<void(const BaseEventInfo*)>&& func)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnSelect(std::move(func));
}

void RichEditorModelNG::SetAboutToIMEInput(std::function<bool(const RichEditorInsertValue&)>&& func)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetAboutToIMEInput(std::move(func));
}

void RichEditorModelNG::SetOnIMEInputComplete(std::function<void(const RichEditorAbstractSpanResult&)>&& func)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnIMEInputComplete(std::move(func));
}

void RichEditorModelNG::SetAboutToDelete(std::function<bool(const RichEditorDeleteValue&)>&& func)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetAboutToDelete(std::move(func));
}

void RichEditorModelNG::SetOnDeleteComplete(std::function<void()>&& func)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnDeleteComplete(std::move(func));
}

void RichEditorModelNG::SetCustomKeyboard(std::function<void()>&& func)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    if (pattern) {
        pattern->SetCustomKeyboard(std::move(func));
    }
}

void RichEditorModelNG::SetCopyOption(CopyOptions& copyOptions)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, CopyOption, copyOptions);
}

void RichEditorModelNG::RegisterSelectionMenuAppearCallback(ResponseType type, const MenuParam& menuParam)
{
    if (type == ResponseType::RIGHT_CLICK || type == ResponseType::LONG_PRESS) {
        SubwindowManager::GetInstance()->RegisterOnShowMenu([menuParam]() {
            if (menuParam.onAppear) {
                menuParam.onAppear();
            }
        });
    }
}

void RichEditorModelNG::RegisterSelectionMenuDisappearCallback(ResponseType type, const MenuParam& menuParam)
{
    if (type == ResponseType::RIGHT_CLICK || type == ResponseType::LONG_PRESS) {
        SubwindowManager::GetInstance()->RegisterOnHideMenu([menuParam]() {
            if (menuParam.onDisappear) {
                menuParam.onDisappear();
            }
        });
    }
}

void BindMenuWithNode(const RefPtr<UINode>& customNode, const RefPtr<FrameNode>& targetNode,
    const NG::OffsetF& offset, const MenuParam& menuParam)
{
    LOGD("RichEditorModelNG::BindMenuWithNode");
    CHECK_NULL_VOID(customNode);
    CHECK_NULL_VOID(targetNode);
    // create a new menu node
    auto menuNode = MenuView::Create(customNode, targetNode->GetId(), targetNode->GetTag(),
        MenuType::CONTEXT_MENU, menuParam);
    // mount menu node to subwindow
    SubwindowManager::GetInstance()->ShowMenuNG(menuNode, targetNode->GetId(), offset, menuParam.isAboveApps);
}

void CreateSelectionMenu(std::function<void()>& buildFunc, const RefPtr<NG::FrameNode>& targetNode, 
    const NG::OffsetF& offset, const MenuParam& menuParam = MenuParam())
{
    NG::ScopedViewStackProcessor builderViewStackProcessor;
    if (!buildFunc) {
        LOGW("buildFunc is null");
        return;
    }
    buildFunc();
    auto node = NG::ViewStackProcessor::GetInstance()->Finish();
    BindMenuWithNode(node, targetNode, offset, menuParam);
}

void RichEditorModelNG::RegisterSelectionMenuKeyEvent(
    const RefPtr<FrameNode>& targetNode, std::function<void()>& buildFunc, const MenuParam& menuParam)
{
    auto focusHub = targetNode->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    auto onKeyEvent = [wp = AceType::WeakClaim(AceType::RawPtr(targetNode)), builder = buildFunc,
                          param = menuParam](const KeyEvent& event) mutable -> bool {
        if (event.action != KeyAction::DOWN) {
            return false;
        }
        if (event.code == KeyCode::KEY_MENU || event.keyIntention == KeyIntention::INTENTION_MENU) {
            auto targetNode = wp.Upgrade();
            CHECK_NULL_RETURN_NOLOG(targetNode, false);
            if (!param.placement.has_value()) {
                param.placement = Placement::BOTTOM_LEFT;
            }
            CreateSelectionMenu(builder, targetNode, OffsetF(), param);
            return true;
        }
        return false;
    };
    focusHub->SetOnKeyEventInternal(std::move(onKeyEvent), OnKeyEventType::CONTEXT_MENU);
}

void RichEditorModelNG::BindSelectionMenu(RichEditorType& editorType, ResponseType& type, std::function<void()>& buildFunc,
    MenuParam& menuParam) {
    // root node
    auto targetNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(targetNode);
    auto pattern = targetNode->GetPattern<RichEditorPattern>();
    if (pattern) {
        LOGW("RichEditorModelNG::BindSelectionMenu");
        pattern->BindSelectionMenu();
    }
    // appear callback
    RegisterSelectionMenuAppearCallback(type, menuParam);
    auto hub = targetNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(hub);
    auto weakTarget = AceType::WeakClaim(AceType::RawPtr(targetNode));
    if (type == ResponseType::RIGHT_CLICK) {
        OnMouseEventFunc event = [builder = buildFunc, weakTarget, menuParam](MouseInfo& info) mutable {
            auto targetNode = weakTarget.Upgrade();
            CHECK_NULL_VOID(targetNode);
            NG::OffsetF menuPosition { info.GetGlobalLocation().GetX() + menuParam.positionOffset.GetX(),
                info.GetGlobalLocation().GetY() + menuParam.positionOffset.GetY() };
            auto pipelineContext = NG::PipelineContext::GetCurrentContext();
            CHECK_NULL_VOID(pipelineContext);
            auto windowRect = pipelineContext->GetDisplayWindowRectInfo();
            menuPosition += NG::OffsetF { windowRect.Left(), windowRect.Top() };
            if (info.GetButton() == MouseButton::RIGHT_BUTTON && info.GetAction() == MouseAction::RELEASE) {
                // builder
                CreateSelectionMenu(builder, targetNode, menuPosition, menuParam);
                info.SetStopPropagation(true);
            }
        };
        auto inputHub = targetNode->GetOrCreateInputEventHub();
        CHECK_NULL_VOID(inputHub);
        inputHub->BindContextMenu(std::move(event));
    } else if (type == ResponseType::LONG_PRESS) {
        // create or show menu on long press
        auto event = [builder = buildFunc, weakTarget, menuParam](const GestureEvent& info) mutable {
            auto targetNode = weakTarget.Upgrade();
            CHECK_NULL_VOID(targetNode);
            NG::OffsetF menuPosition { info.GetGlobalLocation().GetX() + menuParam.positionOffset.GetX(),
                info.GetGlobalLocation().GetY() + menuParam.positionOffset.GetY() };
            auto pipelineContext = NG::PipelineContext::GetCurrentContext();
            CHECK_NULL_VOID(pipelineContext);
            auto windowRect = pipelineContext->GetDisplayWindowRectInfo();
            menuPosition += NG::OffsetF { windowRect.Left(), windowRect.Top() };
            CreateSelectionMenu(builder, targetNode, menuPosition, menuParam);
        };
        auto longPress = AceType::MakeRefPtr<NG::LongPressEvent>(std::move(event));
#ifdef ENABLE_DRAG_FRAMEWORK
        ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, IsBindOverlay, true);
#endif // ENABLE_DRAG_FRAMEWORK
        hub->SetLongPressEvent(longPress, false, true, LONG_PRESS_DURATION);
    } else {
        LOGE("The arg responseType is invalid.");
        return;
    }
    RegisterSelectionMenuKeyEvent(targetNode, buildFunc, menuParam);
    RegisterSelectionMenuDisappearCallback(type, menuParam);
    // delete menu when target node destroy
    auto destructor = [id = targetNode->GetId(), containerId = Container::CurrentId()]() {
        LOGI("BindSelectionMenu delete menu node from map");
        auto subwindow = SubwindowManager::GetInstance()->GetSubwindow(containerId);
        CHECK_NULL_VOID(subwindow);
        auto childContainerId = subwindow->GetChildContainerId();
        auto childContainer = AceEngine::Get().GetContainer(childContainerId);
        CHECK_NULL_VOID(childContainer);
        auto pipeline = AceType::DynamicCast<NG::PipelineContext>(childContainer->GetPipelineContext());
        CHECK_NULL_VOID(pipeline);
        auto overlayManager = pipeline->GetOverlayManager();
        CHECK_NULL_VOID(overlayManager);
        overlayManager->DeleteMenu(id);
    };
    targetNode->PushDestroyCallback(destructor);
}
} // namespace OHOS::Ace::NG
