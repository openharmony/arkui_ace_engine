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

#include "bridge/declarative_frontend/jsview/models/richeditor_model_impl.h"

namespace OHOS::Ace::Framework {
void RichEditorModelImpl::Create() {}

RefPtr<RichEditorControllerBase> RichEditorModelImpl::GetRichEditorController()
{
    return nullptr;
}

void RichEditorModelImpl::SetOnReady(std::function<void()>&& func) {}

void RichEditorModelImpl::SetOnSelect(std::function<void(const BaseEventInfo*)>&& func) {}

void RichEditorModelImpl::SetAboutToIMEInput(std::function<bool(const NG::RichEditorInsertValue&)>&& func) {}

void RichEditorModelImpl::SetOnIMEInputComplete(std::function<void(const NG::RichEditorAbstractSpanResult&)>&& func) {}

void RichEditorModelImpl::SetAboutToDelete(std::function<bool(const NG::RichEditorDeleteValue&)>&& func) {}

void RichEditorModelImpl::SetOnDeleteComplete(std::function<void()>&& func) {}

void RichEditorModelImpl::SetCustomKeyboard(std::function<void()>&& func) {}

void RichEditorModelImpl::SetCopyOption(CopyOptions& copyOptions) {}

void RichEditorModelImpl::BindSelectionMenu(RichEditorType& editorType, ResponseType& responseType,
    std::function<void()>& buildFunc, NG::MenuParam& menuParam) {}

void RichEditorModelImpl::SetOnPaste(std::function<bool()>&& func) {}
    std::function<void()>& buildFunc, SelectMenuParam& menuParam) {}
} // namespace OHOS::Ace::Framework
