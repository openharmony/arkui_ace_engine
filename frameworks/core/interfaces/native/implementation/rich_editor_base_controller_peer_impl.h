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
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_RICHEDITOR_BASE_CONTROLLER_PEER_IMPL_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_RICHEDITOR_BASE_CONTROLLER_PEER_IMPL_H

#include <optional>
#include "base/memory/referenced.h"
#include "base/utils/utils.h"

#include "rich_editor_controller_structs.h"
#include "core/components_ng/pattern/text/span_node.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_controller.h"

namespace OHOS::Ace::NG::GeneratedModifier {
class RichEditorBaseControllerPeerImpl {
public:
    RichEditorBaseControllerPeerImpl() = default;

    void AddTargetController(const WeakPtr<RichEditorBaseController> &handler)
    {
        handler_ = handler;
    }

    int32_t GetCaretOffset()
    {
        if (auto controller = handler_.Upgrade(); controller) {
            return controller->GetCaretOffset();
        }
        return 0;
    }

    bool SetCaretOffset(int32_t caretOffset)
    {
        if (auto controller = handler_.Upgrade(); controller) {
            return controller->SetCaretOffset(caretOffset);
        }
        return false;
    }

    void CloseSelectionMenu()
    {
        if (auto controller = handler_.Upgrade(); controller) {
            return controller->CloseSelectionMenu();
        }
    }

    std::optional<struct UpdateSpanStyle> GetTypingStyle()
    {
        if (auto controller = handler_.Upgrade(); controller) {
            return controller->GetTypingStyle();
        }
        std::optional<struct UpdateSpanStyle> empty;
        return empty;
    }

    void SetTypingStyle(std::optional<struct UpdateSpanStyle> typingStyle, std::optional<TextStyle> textStyle)
    {
        if (auto controller = handler_.Upgrade(); controller) {
            controller->SetTypingStyle(typingStyle, textStyle);
        }
    }
    void SetSelection(int32_t selectionStart, int32_t selectionEnd,
        const std::optional<SelectionOptions>& options, bool isForward)
    {
        if (auto controller = handler_.Upgrade(); controller) {
            controller->SetSelection(selectionStart, selectionEnd, options, isForward);
        }
    }

    bool IsEditing()
    {
        if (auto controller = handler_.Upgrade(); controller) {
            return controller->IsEditing();
        }
        return false;
    }

    void StopEditing()
    {
        if (auto controller = handler_.Upgrade(); controller) {
            controller->StopEditing();
        }
    }

private:
    Ace::WeakPtr<RichEditorBaseController> handler_;
};
} // namespace OHOS::Ace::NG::GeneratedModifier
#endif //FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_RICHEDITOR_BASE_CONTROLLER_PEER_IMPL_H
