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
#include "core/interfaces/native/implementation/text_edit_controller_ex_peer.h"

namespace OHOS::Ace::NG::GeneratedModifier {
class RichEditorBaseControllerPeerImpl : public TextEditControllerExPeer {
public:
    RichEditorBaseControllerPeerImpl() = default;
    ~RichEditorBaseControllerPeerImpl() override {};

    void AddTargetController(const RefPtr<RichEditorBaseControllerBase>& handler)
    {
        handler_ = WeakPtr(handler);
    }

    int32_t GetCaretOffset() override
    {
        if (auto controller = handler_.Upgrade(); controller) {
            return controller->GetCaretOffset();
        }
        return 0;
    }

    bool SetCaretOffset(int32_t caretOffset) override
    {
        if (auto controller = handler_.Upgrade(); controller) {
            return controller->SetCaretOffset(caretOffset);
        }
        return false;
    }

    void CloseSelectionMenu() override
    {
        if (auto controller = handler_.Upgrade(); controller) {
            return controller->CloseSelectionMenu();
        }
    }

    std::optional<UpdateSpanStyle> GetTypingStyle()
    {
        if (auto controller = handler_.Upgrade(); controller) {
            return controller->GetTypingStyle();
        }
        std::optional<UpdateSpanStyle> empty;
        return empty;
    }

    void SetTypingStyle(std::optional<UpdateSpanStyle> typingStyle, std::optional<TextStyle> textStyle)
    {
        if (auto controller = handler_.Upgrade(); controller) {
            controller->SetTypingStyle(typingStyle, textStyle);
        }
    }

    void SetSelection(int32_t selectionStart, int32_t selectionEnd,
        const std::optional<SelectionOptions>& options, bool isForward) override
    {
        if (auto controller = handler_.Upgrade(); controller) {
            controller->SetSelection(selectionStart, selectionEnd, options, isForward);
        }
    }

    bool IsEditing() override
    {
        if (auto controller = handler_.Upgrade(); controller) {
            return controller->IsEditing();
        }
        return false;
    }

    void StopEditing() override
    {
        if (auto controller = handler_.Upgrade(); controller) {
            controller->StopEditing();
        }
    }

    OHOS::Ace::PreviewTextInfo GetPreviewText() override
    {
        OHOS::Ace::PreviewTextInfo retVal;
        if (auto controller = handler_.Upgrade(); controller) {
            auto ret = controller->GetPreviewTextInfo();
            retVal.value = ret.value;
            retVal.offset = ret.offset;
        }
        return retVal;
    }

    WeakPtr<NG::LayoutInfoInterface> GetLayoutInfoInterface() override
    {
        if (auto controller = handler_.Upgrade(); controller) {
            return controller->GetLayoutInfoInterface();
        }
        return nullptr;
    }

    void SetPattern(const WeakPtr<RichEditorPattern>& pattern)
    {
        if (auto controller = handler_.Upgrade(); controller) {
            auto richEditorController = AceType::DynamicCast<RichEditorController>(controller);
            CHECK_NULL_VOID(richEditorController);
            richEditorController->SetPattern(pattern);
        }
    }

    WeakPtr<RichEditorPattern> GetPattern()
    {
        if (auto controller = handler_.Upgrade(); controller) {
            auto richEditorController = AceType::DynamicCast<RichEditorController>(controller);
            CHECK_NULL_RETURN(richEditorController, nullptr);
            // need check
            // return richEditorController->GetPattern();
        }
        return nullptr;
    }

protected:
    WeakPtr<RichEditorBaseControllerBase> handler_;
};
} // namespace OHOS::Ace::NG::GeneratedModifier

struct RichEditorBaseControllerPeer : public OHOS::Ace::NG::GeneratedModifier::RichEditorBaseControllerPeerImpl {};
#endif //FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_RICHEDITOR_BASE_CONTROLLER_PEER_IMPL_H
