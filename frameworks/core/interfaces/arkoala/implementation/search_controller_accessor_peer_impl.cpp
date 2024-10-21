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

#include "search_controller_accessor_peer_impl.h"

namespace OHOS::Ace::NG::GeneratedModifier {
    const WeakPtr<TextFieldControllerBase>& SearchControllerPeerImpl::GetController() const
    {
        return controllerWeak_;
    }

    void SearchControllerPeerImpl::SetController(const RefPtr<TextFieldControllerBase>& controller)
    {
        controllerWeak_ = controller;
    }

    void SearchControllerPeerImpl::TriggerCaretPosition(int32_t caretPosition)
    {
        auto controller = controllerWeak_.Upgrade();
        if (controller) {
            controller->CaretPosition(caretPosition);
        } else {
            LOGE("SearchControllerPeerImpl::TriggerCaretPosition: controller is NULL");
        }
    }

    void SearchControllerPeerImpl::TriggerStopEditing()
    {
        auto controller = controllerWeak_.Upgrade();
        if (controller) {
            controller->StopEditing();
        } else {
            LOGE("SearchControllerPeerImpl::TriggerStopEditing: controller is NULL");
        }
    }

    void SearchControllerPeerImpl::TriggerSetTextSelection(int32_t selectionStart,
        int32_t selectionEnd,
        const std::optional<SelectionOptions>& options)
    {
        auto controller = controllerWeak_.Upgrade();
        if (controller) {
            controller->SetTextSelection(selectionStart, selectionEnd, options);
        } else {
            LOGE("SearchControllerPeerImpl::TriggerSetTextSelection: controller is NULL");
        }
    }
} // namespace OHOS::Ace::NG::GeneratedModifier