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

#include "key_event.h"
#include "pointer_event.h"

#include "adapter/ohos/entrance/ace_view_ohos.h"
#include "core/common/container.h"
#include "core/components_ng/pattern/window_scene/scene/system_window_scene.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/components_ng/pattern/search/search_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "session/host/include/session.h"

#if not defined(ACE_UNITTEST)
#if defined(ENABLE_STANDARD_INPUT)
#include "input_method_controller.h"
#endif
#endif

namespace OHOS::Ace::NG {
RefPtr<UINode> WindowSceneHelper::FindWindowScene(RefPtr<FrameNode> targetNode)
{
    CHECK_NULL_RETURN(targetNode, nullptr);

    auto container = Container::Current();
    if (!container || !container->IsScenceBoardWindow() || !container->IsSceneBoardEnabled()) {
        TAG_LOGD(AceLogTag::ACE_KEYBOARD, "Container nullptr Or not ScenceBoardWindow.");
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

sptr<Rosen::Session> GetCurSession(RefPtr<FrameNode> focusedFrameNode)
{
    RefPtr<UINode> sceneBoardWindowUINode = WindowSceneHelper::FindWindowScene(focusedFrameNode);
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

    auto window2patternSession = windowScenePattern->GetSession();
    if (window2patternSession == nullptr) {
        TAG_LOGD(AceLogTag::ACE_KEYBOARD, "The session is nullptr between window and pattern.");
        return nullptr;
    }
    sptr<Rosen::Session> session;
    session = window2patternSession;

    return session;
}

bool WindowSceneHelper::IsWindowScene(RefPtr<FrameNode> focusedFrameNode)
{
    bool isWindowSceneFlag = false;
    sptr<Rosen::Session> window2patternSession = GetCurSession(focusedFrameNode);
    if (window2patternSession == nullptr) {
        TAG_LOGD(AceLogTag::ACE_KEYBOARD, "The session between window and pattern is nullptr.");
        return isWindowSceneFlag;
    }
    isWindowSceneFlag = window2patternSession->GetSessionInfo().isSystem_;

    return isWindowSceneFlag;
}

uint32_t WindowSceneHelper::GetFocusSystemWindowId(RefPtr<FrameNode> focusedFrameNode)
{
    uint32_t focusSystemWindowId = 0;
    bool isWindowScene = IsWindowScene(focusedFrameNode);
    sptr<Rosen::Session> window2patternSession = GetCurSession(focusedFrameNode);
    if (window2patternSession == nullptr) {
        TAG_LOGD(AceLogTag::ACE_KEYBOARD, "The session between window and pattern is nullptr.");
        return focusSystemWindowId;
    }
    if (isWindowScene) {
        focusSystemWindowId = window2patternSession->GetPersistentId();
        LOGI("Get systemWindowScene id( %{public}u ) successfully.", focusSystemWindowId);
    }

    return focusSystemWindowId;
}

bool WindowSceneHelper::IsFocusWindowSceneCloseKeyboard(RefPtr<FrameNode> focusedFrameNode)
{
    bool isWindowSceneSaveKeyboardFlag = false;
    sptr<Rosen::Session> window2patternSession = GetCurSession(focusedFrameNode);
    if (window2patternSession == nullptr) {
        TAG_LOGD(AceLogTag::ACE_KEYBOARD, "The session between window and pattern is nullptr.");
        return isWindowSceneSaveKeyboardFlag;
    }
    isWindowSceneSaveKeyboardFlag = window2patternSession->GetSCBKeepKeyboardFlag();

    return isWindowSceneSaveKeyboardFlag;
}

bool WindowSceneHelper::GetNeedKeyboardOnFocusFlag(const RefPtr<FrameNode> frameNode)
{
    bool isNeed = true;
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_RETURN(pattern, true);
    if (frameNode->GetTag() == V2::TEXTAREA_ETS_TAG || frameNode->GetTag() == V2::TEXTINPUT_ETS_TAG) {
        auto curPattern = AceType::DynamicCast<TextFieldPattern>(pattern);
        isNeed = curPattern->GetNeedToRequestKeyboardOnFocus();
    } else if (frameNode->GetTag() == V2::SEARCH_ETS_TAG) {
        auto curPattern = AceType::DynamicCast<SearchPattern>(pattern);
        isNeed = curPattern->GetNeedToRequestKeyboardOnFocus();
    }
    TAG_LOGD(AceLogTag::ACE_KEYBOARD, "Need to Request Keyboard On Focus Flag:(%{public}d)", isNeed);
    return isNeed;
}

void WindowSceneHelper::IsWindowSceneCloseKeyboard(RefPtr<FrameNode> frameNode)
{
#if defined (ENABLE_STANDARD_INPUT)
    if (frameNode->GetTag() == V2::UI_EXTENSION_COMPONENT_TAG || frameNode->GetTag() ==
        V2::UI_EXTENSION_COMPONENT_ETS_TAG) {
        TAG_LOGD(AceLogTag::ACE_KEYBOARD, "UIExtension(%{public}s/%{public}d) notNeedSoftKeyboard.",
            frameNode->GetTag().c_str(), frameNode->GetId());
        return;
    }
    // If focus pattern does not need softkeyboard, close it, in windowScene.
    auto curPattern = frameNode->GetPattern<NG::Pattern>();
    CHECK_NULL_VOID(curPattern);
    bool isNeedKeyBoard = curPattern->NeedSoftKeyboard();
    auto isWindowScene = IsWindowScene(frameNode);
    auto saveKeyboard = IsFocusWindowSceneCloseKeyboard(frameNode);
    TAG_LOGD(AceLogTag::ACE_KEYBOARD, "SCB/Keep/Need(%{public}d/%{public}d/%{public}d)",
        isWindowScene, saveKeyboard, isNeedKeyBoard);
    if (isWindowScene && !saveKeyboard && !isNeedKeyBoard) {
        TAG_LOGD(AceLogTag::ACE_KEYBOARD, "scbFrameNode(%{public}s/%{public}d) notNeedSoftKeyboard.",
            frameNode->GetTag().c_str(), frameNode->GetId());
        auto inputMethod = MiscServices::InputMethodController::GetInstance();
        if (inputMethod) {
            MiscServices::PanelInfo curKeyboardPanelInfo;
            curKeyboardPanelInfo.panelType = MiscServices::PanelType::SOFT_KEYBOARD;
            curKeyboardPanelInfo.panelFlag = MiscServices::PanelFlag::FLG_FIXED;
            bool curIsShown = false;
            auto infApiRes = inputMethod->IsPanelShown(curKeyboardPanelInfo, curIsShown);
            if (infApiRes || curIsShown) {
                TAG_LOGD(AceLogTag::ACE_KEYBOARD, "SoftKeyboard Shown.");
                inputMethod->RequestHideInput();
                inputMethod->Close();
                TAG_LOGI(AceLogTag::ACE_KEYBOARD, "SoftKeyboard Closes Successfully.");
            }
        }
    }
#endif
}

void WindowSceneHelper::IsCloseKeyboard(RefPtr<FrameNode> frameNode)
{
#if defined (ENABLE_STANDARD_INPUT)
    // If focus pattern does not need softkeyboard, close it, not in windowScene.
    auto curPattern = frameNode->GetPattern<NG::Pattern>();
    CHECK_NULL_VOID(curPattern);
    bool isNeedKeyBoard = curPattern->NeedSoftKeyboard();
    auto saveKeyboard = IsFocusWindowSceneCloseKeyboard(frameNode);
    TAG_LOGD(AceLogTag::ACE_KEYBOARD, "Keep/Need(%{public}d/%{public}d)", !saveKeyboard, !isNeedKeyBoard);
    if (!saveKeyboard && !isNeedKeyBoard) {
        TAG_LOGD(AceLogTag::ACE_KEYBOARD, "FrameNode(%{public}s/%{public}d) notNeedSoftKeyboard.",
            frameNode->GetTag().c_str(), frameNode->GetId());
        auto inputMethod = MiscServices::InputMethodController::GetInstance();
        if (inputMethod) {
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
        pointerEvent->UpdatePointerItem(pointerId, item);
    }
}

void WindowSceneHelper::InjectPointerEvent(const std::string& targetNodeName,
    const std::shared_ptr<OHOS::MMI::PointerEvent>& pointerEvent)
{
    CHECK_NULL_VOID(pointerEvent);
    if (targetNodeName == "") {
        return;
    }
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);

    auto rootNode = pipelineContext->GetRootElement();
    CHECK_NULL_VOID(rootNode);
    auto targetNode = FrameNode::FindChildByName(rootNode, targetNodeName);
    if (!targetNode && pointerEvent->GetPointerAction() != MMI::PointerEvent::POINTER_ACTION_MOVE) {
        TAG_LOGW(AceLogTag::ACE_INPUTTRACKING,
            "PointerEvent Process to inject, targetNode is null. targetNodeName:%{public}s",
            targetNodeName.c_str());
    }
    InjectPointerEvent(targetNode, pointerEvent);
}

void WindowSceneHelper::InjectPointerEvent(RefPtr<FrameNode> node,
    const std::shared_ptr<OHOS::MMI::PointerEvent>& pointerEvent)
{
    CHECK_NULL_VOID(node);
    CHECK_NULL_VOID(pointerEvent);

    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    CaculatePoint(node, pointerEvent);
    if (pointerEvent->GetPointerAction() != MMI::PointerEvent::POINTER_ACTION_MOVE) {
        TAG_LOGI(AceLogTag::ACE_INPUTTRACKING,
            "PointerEvent Process to inject, eventInfo: id:%{public}d, "
            "WindowId = %{public}d, ViewWidth = %{public}d, ViewHeight = %{public}d, "
            "ViewPosX = %{public}d, ViewPosY = %{public}d. node: id:%{public}d, type:%{public}s",
            pointerEvent->GetId(), container->GetWindowId(), container->GetViewWidth(),
            container->GetViewHeight(), container->GetViewPosX(), container->GetViewPosY(),
            node->GetId(), node->GetTag().c_str());
    }
    auto aceView = static_cast<OHOS::Ace::Platform::AceViewOhos*>(container->GetView());
    CHECK_NULL_VOID(aceView);
    OHOS::Ace::Platform::AceViewOhos::DispatchTouchEvent(aceView, pointerEvent, node);
}

void WindowSceneHelper::InjectKeyEvent(const std::shared_ptr<OHOS::MMI::KeyEvent>& keyEvent)
{
    CHECK_NULL_VOID(keyEvent);
    TAG_LOGI(AceLogTag::ACE_INPUTTRACKING,
        "KeyEvent Process to inject, eventInfo: id:%{public}d, "
        "keyEvent info: keyCode is %{public}d, "
        "keyAction is %{public}d, keyActionTime is %{public}" PRId64,
        keyEvent->GetId(), keyEvent->GetKeyCode(), keyEvent->GetKeyAction(), keyEvent->GetActionTime());

    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto aceView = static_cast<OHOS::Ace::Platform::AceViewOhos*>(container->GetView());
    CHECK_NULL_VOID(aceView);
    OHOS::Ace::Platform::AceViewOhos::DispatchKeyEvent(aceView, keyEvent);
}
} // namespace OHOS::Ace::NG
