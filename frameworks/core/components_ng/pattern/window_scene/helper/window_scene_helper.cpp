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

#include "core/components_ng/pattern/window_scene/helper/window_scene_helper.h"

#include "input_manager.h"

#include "adapter/ohos/entrance/ace_view_ohos.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/components_ng/pattern/window_scene/scene/system_window_scene.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/components_ng/pattern/search/search_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "session/host/include/session.h"
#include "transaction/rs_transaction.h"
#include "transaction/rs_transaction_handler.h"
#include "transaction/rs_transaction_proxy.h"
#include "transaction/rs_sync_transaction_controller.h"
#include "transaction/rs_sync_transaction_handler.h"
#include "ui/rs_node.h"
#include "ui/rs_ui_context.h"
#include "ui/rs_ui_director.h"

#ifndef ACE_UNITTEST
#ifdef ENABLE_STANDARD_INPUT
#include "input_method_controller.h"
#endif
#endif

namespace OHOS::Ace::NG {
RefPtr<UINode> WindowSceneHelper::FindWindowScene(const RefPtr<FrameNode>& targetNode)
{
    CHECK_NULL_RETURN(targetNode, nullptr);

    auto container = Container::Current();
    if (!container || !container->IsSceneBoardWindow() || !container->IsSceneBoardEnabled()) {
        TAG_LOGD(AceLogTag::ACE_KEYBOARD, "Container nullptr Or not SceneBoardWindow.");
        return nullptr;
    }

    TAG_LOGD(AceLogTag::ACE_KEYBOARD, "FindWindowScene start.");
    auto parent = targetNode->GetParent();
    while (parent && parent->GetTag() != V2::WINDOW_SCENE_ETS_TAG) {
        parent = parent->GetParent();
    }
    CHECK_NULL_RETURN(parent, nullptr);
    TAG_LOGD(AceLogTag::ACE_KEYBOARD, "FindWindowScene successfully.");

    return parent;
}

sptr<Rosen::Session> GetCurSession(const RefPtr<FrameNode>& focusedFrameNode)
{
    auto sceneBoardWindowUINode = WindowSceneHelper::FindWindowScene(focusedFrameNode);
    if (sceneBoardWindowUINode == nullptr) {
        TAG_LOGD(AceLogTag::ACE_KEYBOARD, "FindWindowScene failed.");
        return nullptr;
    }

    auto windowSceneFrameNode = AceType::DynamicCast<FrameNode>(sceneBoardWindowUINode);
    if (windowSceneFrameNode == nullptr) {
        TAG_LOGD(AceLogTag::ACE_KEYBOARD, "WindowFrameNode to FrameNode failed.");
        return nullptr;
    }

    auto windowScenePattern = windowSceneFrameNode->GetPattern<SystemWindowScene>();
    if (windowScenePattern == nullptr) {
        TAG_LOGD(AceLogTag::ACE_KEYBOARD, "windowScenePattern is nullptr.");
        return nullptr;
    }

    return windowScenePattern->GetSession();
}

bool WindowSceneHelper::IsWindowScene(const RefPtr<FrameNode>& focusedFrameNode)
{
    auto window2patternSession = GetCurSession(focusedFrameNode);
    if (window2patternSession == nullptr) {
        TAG_LOGD(AceLogTag::ACE_KEYBOARD, "The session between window and pattern is nullptr.");
        return false;
    }

    return window2patternSession->GetSessionInfo().isSystem_;
}

int32_t WindowSceneHelper::GetFocusSystemWindowId(const RefPtr<FrameNode>& focusedFrameNode)
{
    int32_t focusSystemWindowId = 0;
    bool isWindowScene = IsWindowScene(focusedFrameNode);
    sptr<Rosen::Session> window2patternSession = GetCurSession(focusedFrameNode);
    if (window2patternSession == nullptr) {
        TAG_LOGD(AceLogTag::ACE_KEYBOARD, "The session between window and pattern is nullptr.");
        return focusSystemWindowId;
    }
    if (isWindowScene) {
        focusSystemWindowId = static_cast<int32_t>(window2patternSession->GetPersistentId());
        TAG_LOGI(AceLogTag::ACE_KEYBOARD, "Get systemWindowScene id:%{public}d successfully.", focusSystemWindowId);
    }

    return focusSystemWindowId;
}

int32_t WindowSceneHelper::GetWindowIdForWindowScene(const RefPtr<FrameNode>& windowSceneNode)
{
    int32_t windowId = 0;
    CHECK_NULL_RETURN(windowSceneNode, windowId);
    if (windowSceneNode->GetTag() != V2::WINDOW_SCENE_ETS_TAG) {
        return windowId;
    }
    auto windowScenePattern = windowSceneNode->GetPattern<SystemWindowScene>();
    CHECK_NULL_RETURN(windowScenePattern, windowId);

    auto window2patternSession = windowScenePattern->GetSession();
    CHECK_NULL_RETURN(window2patternSession, windowId);

    windowId = static_cast<int32_t>(window2patternSession->GetPersistentId());
    return windowId;
}

bool WindowSceneHelper::IsFocusWindowSceneCloseKeyboard(const RefPtr<FrameNode>& focusedFrameNode)
{
    sptr<Rosen::Session> window2patternSession = GetCurSession(focusedFrameNode);
    if (window2patternSession == nullptr) {
        TAG_LOGW(AceLogTag::ACE_KEYBOARD, "The session between window and pattern is nullptr.");
        return false;
    }

    return window2patternSession->GetSCBKeepKeyboardFlag();
}

void WindowSceneHelper::IsWindowSceneCloseKeyboard(const RefPtr<FrameNode>& frameNode)
{
#if defined (ENABLE_STANDARD_INPUT)
    // If focus pattern does not need softkeyboard, close it, in windowScene.
    auto curPattern = frameNode->GetPattern<NG::Pattern>();
    CHECK_NULL_VOID(curPattern);
    bool isNeedKeyBoard = curPattern->NeedSoftKeyboard();
    auto saveKeyboard = IsFocusWindowSceneCloseKeyboard(frameNode);
    TAG_LOGI(AceLogTag::ACE_KEYBOARD,
        "FrameNode(%{public}s/%{public}d) notNeedSoftKeyboard, Keep:%{public}d, Need:%{public}d)",
        frameNode->GetTag().c_str(), frameNode->GetId(), !saveKeyboard, !isNeedKeyBoard);
    if (!saveKeyboard && !isNeedKeyBoard) {
        auto inputMethod = MiscServices::InputMethodController::GetInstance();
        if (inputMethod) {
            inputMethod->RequestHideInput(true);
            inputMethod->Close();
            TAG_LOGI(AceLogTag::ACE_KEYBOARD, "scbSoftKeyboard Closes Successfully.");
        }
    }
#endif
}

void WindowSceneHelper::IsCloseKeyboard(const RefPtr<FrameNode>& frameNode)
{
#if defined (ENABLE_STANDARD_INPUT)
    // If focus pattern does not need softkeyboard, close it, not in windowScene.
    auto curPattern = frameNode->GetPattern<NG::Pattern>();
    CHECK_NULL_VOID(curPattern);
    bool isNeedKeyBoard = curPattern->NeedSoftKeyboard();
    auto saveKeyboard = IsFocusWindowSceneCloseKeyboard(frameNode);
    TAG_LOGI(AceLogTag::ACE_KEYBOARD,
        "FrameNode(%{public}s/%{public}d) notNeed SoftKeyboard, Keep:%{public}d, Need:%{public}d)",
        frameNode->GetTag().c_str(), frameNode->GetId(), !saveKeyboard, !isNeedKeyBoard);
    if (!saveKeyboard && !isNeedKeyBoard) {
        auto inputMethod = MiscServices::InputMethodController::GetInstance();
        if (inputMethod) {
            inputMethod->RequestHideInput(true);
            inputMethod->Close();
            TAG_LOGI(AceLogTag::ACE_KEYBOARD, "SoftKeyboard Closes Successfully.");
        }
    }
#endif
}

void CaculatePoint(const RefPtr<FrameNode>& node, const std::shared_ptr<OHOS::MMI::PointerEvent>& pointerEvent)
{
    CHECK_NULL_VOID(node);
    CHECK_NULL_VOID(pointerEvent);

    auto pointerId = pointerEvent->GetPointerId();
    auto renderContext = node->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto rect = renderContext->GetPaintRectWithoutTransform();
    MMI::PointerEvent::PointerItem item;
    if (pointerEvent->GetPointerItem(pointerId, item)) {
        PointF tmp(item.GetWindowX() + rect.GetX(), item.GetWindowY() + rect.GetY());
        renderContext->GetPointTransform(tmp);
        item.SetWindowX(static_cast<int32_t>(std::round(tmp.GetX())));
        item.SetWindowY(static_cast<int32_t>(std::round(tmp.GetY())));
        if (pointerEvent->GetSourceType() == OHOS::MMI::PointerEvent::SOURCE_TYPE_TOUCHSCREEN &&
            item.GetToolType() == OHOS::MMI::PointerEvent::TOOL_TYPE_PEN) {
            // CaculatePoint for double XY Position.
            PointF tmpPos(item.GetWindowXPos() + rect.GetX(), item.GetWindowYPos() + rect.GetY());
            renderContext->GetPointTransform(tmpPos);
            item.SetWindowXPos(tmpPos.GetX());
            item.SetWindowYPos(tmpPos.GetY());
        }
        pointerEvent->UpdatePointerItem(pointerId, item);
    }
}

void WindowSceneHelper::InjectPointerEvent(
    const RefPtr<FrameNode>& node, const std::shared_ptr<OHOS::MMI::PointerEvent>& pointerEvent)
{
    if (!pointerEvent) {
        TAG_LOGE(AceLogTag::ACE_INPUTTRACKING, "InjectPointerEvent pointerEvent is null return.");
        return;
    }
    if (!node) {
        MMI::InputManager::GetInstance()->MarkProcessed(
            pointerEvent->GetId(), pointerEvent->GetActionTime(), pointerEvent->IsMarkEnabled());
        TAG_LOGE(AceLogTag::ACE_INPUTTRACKING, "InjectPointerEvent eventId:%{public}d node is null return.",
            pointerEvent->GetId());
        return;
    }

    auto container = Container::Current();
    if (!container) {
        MMI::InputManager::GetInstance()->MarkProcessed(
            pointerEvent->GetId(), pointerEvent->GetActionTime(), pointerEvent->IsMarkEnabled());
        TAG_LOGE(AceLogTag::ACE_INPUTTRACKING, "InjectPointerEvent eventId:%{public}d container is null return.",
            pointerEvent->GetId());
        return;
    }
    CaculatePoint(node, pointerEvent);
    auto aceView = AceType::DynamicCast<OHOS::Ace::Platform::AceViewOhos>(container->GetAceView());
    if (!aceView) {
        MMI::InputManager::GetInstance()->MarkProcessed(
            pointerEvent->GetId(), pointerEvent->GetActionTime(), pointerEvent->IsMarkEnabled());
        TAG_LOGE(AceLogTag::ACE_INPUTTRACKING, "InjectPointerEvent eventId:%{public}d aceView is null return.",
            pointerEvent->GetId());
        return;
    }
    OHOS::Ace::Platform::AceViewOhos::DispatchTouchEvent(aceView, pointerEvent, node, nullptr, true);
}

void WindowSceneHelper::InjectPointerEventForActionCancel(const std::shared_ptr<OHOS::MMI::PointerEvent>& pointerEvent)
{
    if (!pointerEvent) {
        TAG_LOGE(AceLogTag::ACE_INPUTTRACKING, "InjectPointerEventForActionCancel pointerEvent is null return.");
        return;
    }

    if (pointerEvent->GetPointerAction() != MMI::PointerEvent::POINTER_ACTION_CANCEL) {
        MMI::InputManager::GetInstance()->MarkProcessed(
            pointerEvent->GetId(), pointerEvent->GetActionTime(), pointerEvent->IsMarkEnabled());
        TAG_LOGE(AceLogTag::ACE_INPUTTRACKING, "InjectPointerEventForActionCancel only handle cancel event.");
        return;
    }

    auto container = Container::Current();
    if (!container) {
        MMI::InputManager::GetInstance()->MarkProcessed(
            pointerEvent->GetId(), pointerEvent->GetActionTime(), pointerEvent->IsMarkEnabled());
        TAG_LOGE(AceLogTag::ACE_INPUTTRACKING,
            "InjectPointerEventForActionCancel eventId:%{public}d container is null return.", pointerEvent->GetId());
        return;
    }
    auto aceView = AceType::DynamicCast<OHOS::Ace::Platform::AceViewOhos>(container->GetAceView());
    if (!aceView) {
        MMI::InputManager::GetInstance()->MarkProcessed(
            pointerEvent->GetId(), pointerEvent->GetActionTime(), pointerEvent->IsMarkEnabled());
        TAG_LOGE(AceLogTag::ACE_INPUTTRACKING,
            "InjectPointerEventForActionCancel eventId:%{public}d aceView is null return.", pointerEvent->GetId());
        return;
    }
    OHOS::Ace::Platform::AceViewOhos::DispatchTouchEvent(aceView, pointerEvent, nullptr, nullptr, true);
}

bool WindowSceneHelper::InjectKeyEvent(const std::shared_ptr<OHOS::MMI::KeyEvent>& keyEvent, bool isPreIme)
{
    CHECK_NULL_RETURN(keyEvent, false);
    if (!SystemProperties::GetAceCommercialLogEnabled()) {
        TAG_LOGI(AceLogTag::ACE_INPUTTRACKING,
            SEC_PLD(, "KeyEvent Process to inject, eventInfo: id:%{public}d, "
            "keyEvent info: keyCode is %{public}d, "
            "keyAction is %{public}d, keyActionTime is %{public}" PRId64),
            SEC_PARAM(keyEvent->GetId(), keyEvent->GetKeyCode(),
            keyEvent->GetKeyAction(), keyEvent->GetActionTime()));
    }

    auto container = Container::Current();
    CHECK_NULL_RETURN(container, false);
    auto aceView = AceType::DynamicCast<OHOS::Ace::Platform::AceViewOhos>(container->GetAceView());
    CHECK_NULL_RETURN(aceView, false);
    return OHOS::Ace::Platform::AceViewOhos::DispatchKeyEvent(aceView, keyEvent, isPreIme);
}

bool WindowSceneHelper::IsWindowPattern(const RefPtr<FrameNode>& node)
{
    if (!node) {
        return false;
    }
    return node->GetWindowPatternType() > static_cast<uint32_t>(WindowPatternType::SCREEN_SCENE);
}

bool WindowSceneHelper::HasWindowSession(const RefPtr<FrameNode>& node)
{
    if (!node) {
        return false;
    }
    return node->GetWindowPatternType() > static_cast<uint32_t>(WindowPatternType::TRANSFORM_SCENE);
}

bool WindowSceneHelper::IsTransformScene(uint32_t type)
{
    return type == static_cast<uint32_t>(WindowPatternType::TRANSFORM_SCENE);
}

bool WindowSceneHelper::IsAppOrSubScene(uint32_t type)
{
    return type == static_cast<uint32_t>(WindowPatternType::WINDOW_SCENE);
}

bool WindowSceneHelper::IsSystemWindowScene(uint32_t type)
{
    return type == static_cast<uint32_t>(WindowPatternType::SYSTEM_WINDOW_SCENE);
}

bool WindowSceneHelper::IsPanelScene(uint32_t type)
{
    return type == static_cast<uint32_t>(WindowPatternType::PANEL_SCENE);
}

bool WindowSceneHelper::IsScreenScene(uint32_t type)
{
    return type == static_cast<uint32_t>(WindowPatternType::SCREEN_SCENE);
}

bool WindowSceneHelper::IsNodeInKeyGuardWindow(const RefPtr<FrameNode>& node)
{
    auto window2patternSession = GetCurSession(node);
    if (window2patternSession == nullptr) {
        TAG_LOGD(AceLogTag::ACE_SUB_WINDOW, "The session between window and pattern is nullptr.");
        return false;
    }
    
    auto sessionWindowType = window2patternSession->GetWindowType();
    TAG_LOGD(AceLogTag::ACE_SUB_WINDOW, "The windowtype of window scene session is %{public}d", sessionWindowType);
    return sessionWindowType == Rosen::WindowType::WINDOW_TYPE_KEYGUARD;
}

std::shared_ptr<Rosen::RSUIContext> WindowSceneHelper::GetRSUIContext(const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto window = pipeline->GetWindow();
    CHECK_NULL_RETURN(window, nullptr);
    auto rsUIDirector = window->GetRSUIDirector();
    CHECK_NULL_RETURN(rsUIDirector, nullptr);
    auto rsUIContext = rsUIDirector->GetRSUIContext();
    TAG_LOGD(AceLogTag::ACE_WINDOW, "%{public}s", RSUIContextToStr(rsUIContext).c_str());
    return rsUIContext;
}

std::shared_ptr<Rosen::RSTransaction> WindowSceneHelper::GetRSTransaction(const sptr<Rosen::Session>& session)
{
    auto rsUIContext = session->GetRSUIContext(__func__);
    if (rsUIContext) {
        if (auto rsSyncTransHandler = rsUIContext->GetSyncTransactionHandler()) {
            return rsSyncTransHandler->GetRSTransaction();
        }
    }
    TAG_LOGD(AceLogTag::ACE_WINDOW, "Use RSSyncTransactionController");
    return Rosen::RSSyncTransactionController::GetInstance()->GetRSTransaction();
}


std::shared_ptr<Rosen::RSTransactionHandler> WindowSceneHelper::GetRSTransactionHandler(
    const RefPtr<FrameNode>& frameNode)
{
    auto rsUIContext = GetRSUIContext(frameNode);
    CHECK_NULL_RETURN(rsUIContext, nullptr);
    return rsUIContext->GetRSTransaction();
}

void WindowSceneHelper::FlushImplicitTransaction(const RefPtr<FrameNode>& frameNode)
{
    if (auto transactionHandler = GetRSTransactionHandler(frameNode)) {
        transactionHandler->FlushImplicitTransaction();
    } else {
        TAG_LOGD(AceLogTag::ACE_WINDOW, "RSTransactionHandler is null, use RSTransactionProxy");
        Rosen::RSTransactionProxy::GetInstance()->FlushImplicitTransaction();
    }
}

std::string WindowSceneHelper::RSNodeToStr(const std::shared_ptr<Rosen::RSNode>& rsNode)
{
    if (!rsNode) {
        return "RSNode is null";
    }
    std::ostringstream oss;
    oss << "RSNode [id: " << rsNode->GetId() << "], "
        << RSUIContextToStr(rsNode->GetRSUIContext());
    return oss.str();
}

std::string WindowSceneHelper::RSUIContextToStr(const std::shared_ptr<Rosen::RSUIContext>& rsUIContext)
{
    if (!rsUIContext) {
        return "RSUIContext is null";
    }
    std::ostringstream oss;
    oss << "RSUIContext [token: " << rsUIContext->GetToken()
        << ", tid: "
        << static_cast<int32_t>(rsUIContext->GetToken() >> 32) // 32: tid's offset position in the token
        << "]";
    return oss.str();
}
} // namespace OHOS::Ace::NG
