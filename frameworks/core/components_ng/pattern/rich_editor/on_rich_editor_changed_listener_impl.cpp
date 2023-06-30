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

#include "core/components_ng/pattern/rich_editor/on_rich_editor_changed_listener_impl.h"

namespace OHOS::Ace::NG {
void OnRichEditorChangedListenerImpl::InsertText(const std::u16string& text) {}

void OnRichEditorChangedListenerImpl::DeleteBackward(int32_t length) {}

void OnRichEditorChangedListenerImpl::DeleteForward(int32_t length) {}

void OnRichEditorChangedListenerImpl::SendKeyEventFromInputMethod(const MiscServices::KeyEvent& event) {}

void OnRichEditorChangedListenerImpl::SendKeyboardStatus(const MiscServices::KeyboardStatus& keyboardStatus) {}

void OnRichEditorChangedListenerImpl::HandleKeyboardStatus(MiscServices::KeyboardStatus status) {}

void OnRichEditorChangedListenerImpl::SendFunctionKey(const MiscServices::FunctionKey& functionKey) {}

void OnRichEditorChangedListenerImpl::SetKeyboardStatus(bool status) {}

void OnRichEditorChangedListenerImpl::HandleFunctionKey(MiscServices::FunctionKey functionKey) {}

void OnRichEditorChangedListenerImpl::MoveCursor(MiscServices::Direction direction) {}

void OnRichEditorChangedListenerImpl::HandleSetSelection(int32_t start, int32_t end) {}

void OnRichEditorChangedListenerImpl::HandleExtendAction(int32_t action) {}

void OnRichEditorChangedListenerImpl::HandleSelect(int32_t keyCode, int32_t cursorMoveSkip) {}

void OnRichEditorChangedListenerImpl::PostTaskToUI(const std::function<void()>& task) {}
} // namespace OHOS::Ace::NG