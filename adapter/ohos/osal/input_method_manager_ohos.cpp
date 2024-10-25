/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/common/ime/input_method_manager.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "core/components_ng/pattern/window_scene/helper/window_scene_helper.h"
#include "core/pipeline_ng/pipeline_context.h"

#ifndef ACE_UNITTEST
#ifdef ENABLE_STANDARD_INPUT
#include "input_method_controller.h"
#endif
#endif

namespace OHOS::Ace {
std::unique_ptr<InputMethodManager> InputMethodManager::instance_ = nullptr;
std::mutex InputMethodManager::mtx_;

InputMethodManager* InputMethodManager::GetInstance()
{
    if (instance_ == nullptr) {
        std::lock_guard<std::mutex> lock(mtx_);
        if (instance_ == nullptr) {
            instance_.reset(new InputMethodManager);
        }
    }
    return instance_.get();
}

void InputMethodManager::OnFocusNodeChange(const RefPtr<NG::FrameNode>& curFocusNode)
{
    auto container = Container::Current();
    if (container && container->IsKeyboard()) {
        TAG_LOGI(AceLogTag::ACE_KEYBOARD, "focus in input method.");
        return;
    }
    TAG_LOGI(AceLogTag::ACE_KEYBOARD, "current focus node info : (%{public}s/%{public}d).",
        curFocusNode->GetTag().c_str(), curFocusNode->GetId());

    auto currentFocusNode = curFocusNode_.Upgrade();
    if (currentFocusNode && currentFocusNode->GetTag() == V2::UI_EXTENSION_COMPONENT_ETS_TAG &&
        currentFocusNode != curFocusNode) {
        curFocusNode_ = curFocusNode;
        TAG_LOGI(AceLogTag::ACE_KEYBOARD, "UIExtension switch focus");
        auto pattern = curFocusNode->GetPattern();
        if (!pattern->NeedSoftKeyboard()) {
            HideKeyboardAcrossProcesses();
        }
    }

    curFocusNode_ = curFocusNode;
#ifdef WINDOW_SCENE_SUPPORTED
    auto isWindowScene = NG::WindowSceneHelper::IsWindowScene(curFocusNode);
    if (isWindowScene) {
        ProcessKeyboardInWindowScene(curFocusNode);
    } else {
        ProcessKeyboard(curFocusNode);
    }
#else
    CloseKeyboard(curFocusNode);
#endif
}

void InputMethodManager::ProcessKeyboardInWindowScene(const RefPtr<NG::FrameNode>& curFocusNode)
{
    if (curFocusNode && NG::WindowSceneHelper::IsFocusWindowSceneCloseKeyboard(curFocusNode)) {
        lastKeep_ = true;
    } else {
        lastKeep_ = false;
    }
    // Frame other window to SCB window Or inSCB window changes,hide keyboard.
    if ((windowFocus_.has_value() && windowFocus_.value())) {
        TAG_LOGI(AceLogTag::ACE_KEYBOARD, "SCB Window focus first, ready to hide keyboard.");
        windowFocus_.reset();
        NG::WindowSceneHelper::IsWindowSceneCloseKeyboard(curFocusNode);
        return;
    }
    // In window scene, focus change, need close keyboard.
    auto pattern = curFocusNode->GetPattern();
    if (!pattern->NeedSoftKeyboard()) {
        TAG_LOGI(AceLogTag::ACE_KEYBOARD, "SCB WindowscenePage ready to close keyboard.");
        NG::WindowSceneHelper::IsCloseKeyboard(curFocusNode);
    }
}

void InputMethodManager::ProcessKeyboard(const RefPtr<NG::FrameNode>& curFocusNode)
{
    if (curFocusNode && curFocusNode->GetTag() == V2::SCREEN_ETS_TAG && lastKeep_) {
        TAG_LOGI(AceLogTag::ACE_KEYBOARD, "node is screen and last node want to save keyboard Ignore");
        lastKeep_ = false;
        return;
    }
    auto pipeline = curFocusNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    if (windowFocus_.has_value() && windowFocus_.value()) {
        TAG_LOGI(AceLogTag::ACE_KEYBOARD, "Normal Window focus first, set focus flag to window.");
        windowFocus_.reset();
        auto callback = pipeline->GetWindowFocusCallback();
        if (callback) {
            TAG_LOGI(AceLogTag::ACE_KEYBOARD, "Trigger Window Focus Callback");
            callback();
        } else {
            TAG_LOGI(AceLogTag::ACE_KEYBOARD, "No Window Focus Callback");
            if (!pipeline->NeedSoftKeyboard()) {
                HideKeyboardAcrossProcesses();
            }
        }
        return;
    }

    if (curFocusNode->GetTag() == V2::UI_EXTENSION_COMPONENT_ETS_TAG ||
        curFocusNode->GetTag() == V2::EMBEDDED_COMPONENT_ETS_TAG) {
        TAG_LOGI(AceLogTag::ACE_KEYBOARD, "UIExtension(%{public}s/%{public}d) not need process.",
            curFocusNode->GetTag().c_str(), curFocusNode->GetId());
        return;
    }

    auto container = Container::Current();
    auto isUIExtension = container && container->IsUIExtensionWindow();
    auto pattern = curFocusNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    if (isUIExtension && !pattern->NeedSoftKeyboard()) {
        HideKeyboardAcrossProcesses();
    } else {
        CloseKeyboard(curFocusNode);
    }
}

void InputMethodManager::SetWindowFocus(bool windowFocus)
{
    windowFocus_ = windowFocus;
}

bool InputMethodManager::NeedSoftKeyboard() const
{
    auto currentFocusNode = curFocusNode_.Upgrade();
    CHECK_NULL_RETURN(currentFocusNode, false);
    auto pipeline = currentFocusNode->GetContextRefPtr();
    if (pipeline) {
        auto manager = AceType::DynamicCast<NG::TextFieldManagerNG>(pipeline->GetTextFieldManager());
        if (manager && manager->GetLastRequestKeyboardId() == currentFocusNode->GetId()) {
            TAG_LOGI(AceLogTag::ACE_KEYBOARD, "Last RequestKeyboard node is current focus node, So keep");
            return true;
        }
    }
    if (currentFocusNode && (currentFocusNode->GetTag() == V2::UI_EXTENSION_COMPONENT_ETS_TAG ||
                             currentFocusNode->GetTag() == V2::EMBEDDED_COMPONENT_ETS_TAG)) {
        return true;
    }
    auto pattern = currentFocusNode->GetPattern();
    return pattern->NeedSoftKeyboard() && pattern->NeedToRequestKeyboardOnFocus();
}

void InputMethodManager::CloseKeyboard()
{
    ACE_LAYOUT_SCOPED_TRACE("CloseKeyboard");
    auto currentFocusNode = curFocusNode_.Upgrade();
    CHECK_NULL_VOID(currentFocusNode);
    auto pipeline = currentFocusNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto textFieldManager = pipeline->GetTextFieldManager();
    CHECK_NULL_VOID(textFieldManager);
    if (!textFieldManager->GetImeShow() && !textFieldManager->GetIsImeAttached()) {
        TAG_LOGI(AceLogTag::ACE_KEYBOARD, "Ime Not Shown, Ime Not Attached, No need to close keyboard");
        return;
    }
    textFieldManager->SetNeedToRequestKeyboard(false);
#if defined(ENABLE_STANDARD_INPUT)
    // If pushpage, close it
    TAG_LOGI(AceLogTag::ACE_KEYBOARD, "PageChange CloseKeyboard FrameNode notNeedSoftKeyboard.");
    auto inputMethod = MiscServices::InputMethodController::GetInstance();
    if (inputMethod) {
        inputMethod->Close();
        TAG_LOGI(AceLogTag::ACE_KEYBOARD, "PageChange CloseKeyboard SoftKeyboard Closes Successfully.");
    }
#endif
}

void InputMethodManager::CloseKeyboardInPipelineDestroy()
{
    TAG_LOGI(AceLogTag::ACE_KEYBOARD, "Pipeline Destroyed, Ready to close SoftKeyboard.");
    auto inputMethod = MiscServices::InputMethodController::GetInstance();
    if (inputMethod) {
        inputMethod->Close();
        TAG_LOGI(AceLogTag::ACE_KEYBOARD, "Pipelinne Destroyed, Close SoftKeyboard Successfully.");
    }
}

void InputMethodManager::CloseKeyboard(const RefPtr<NG::FrameNode>& focusNode)
{
#if defined(ENABLE_STANDARD_INPUT)
    // If focus pattern does not need softkeyboard, close it, not in windowScene.
    auto curPattern = focusNode->GetPattern<NG::Pattern>();
    CHECK_NULL_VOID(curPattern);
    ACE_LAYOUT_SCOPED_TRACE("CloseKeyboard[id:%d]", focusNode->GetId());
    bool isNeedKeyBoard = curPattern->NeedSoftKeyboard();
    if (!isNeedKeyBoard) {
        TAG_LOGI(AceLogTag::ACE_KEYBOARD, "FrameNode(%{public}s/%{public}d) notNeedSoftKeyboard.",
            focusNode->GetTag().c_str(), focusNode->GetId());
        CloseKeyboard();
    }
#endif
}

void InputMethodManager::HideKeyboardAcrossProcesses()
{
#if defined(ENABLE_STANDARD_INPUT)
    // If Nav, close it
    TAG_LOGI(AceLogTag::ACE_KEYBOARD, "across processes CloseKeyboard FrameNode notNeedSoftKeyboard.");
    auto inputMethod = MiscServices::InputMethodController::GetInstance();
    if (inputMethod) {
        inputMethod->RequestHideInput();
        inputMethod->Close();
        TAG_LOGI(AceLogTag::ACE_KEYBOARD, "across processes CloseKeyboard SoftKeyboard Closes Successfully.");
    }
#endif
}

void InputMethodManager::CloseKeyboardInProcess()
{
    TAG_LOGI(AceLogTag::ACE_KEYBOARD, "CloseKeyboardInProcess Ready to close SoftKeyboard.");
    auto inputMethod = MiscServices::InputMethodController::GetInstance();
    if (inputMethod) {
        inputMethod->Close();
        TAG_LOGI(AceLogTag::ACE_KEYBOARD, "CloseKeyboardInProcess Close SoftKeyboard Successfully.");
    }
}

void InputMethodManager::ProcessModalPageScene()
{
    auto currentFocusNode = curFocusNode_.Upgrade();
    TAG_LOGI(AceLogTag::ACE_KEYBOARD, "ProcessModalPageScene");
    if (currentFocusNode && currentFocusNode->GetTag() == V2::UI_EXTENSION_COMPONENT_ETS_TAG) {
        HideKeyboardAcrossProcesses();
    } else {
        CloseKeyboardInProcess();
    }
}
} // namespace OHOS::Ace