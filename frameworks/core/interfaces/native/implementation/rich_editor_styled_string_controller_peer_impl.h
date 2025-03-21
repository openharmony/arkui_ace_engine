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
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_RICHEDITOR_STYLED_CONTROLLER_PEER_IMPL_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_RICHEDITOR_STYLED_CONTROLLER_PEER_IMPL_H

#include <optional>
#include "base/memory/referenced.h"
#include "base/utils/utils.h"

#include "core/components_ng/pattern/rich_editor/rich_editor_styled_string_controller.h"
#include "core/interfaces/native/implementation/rich_editor_base_controller_peer_impl.h"
#include "rich_editor_controller_structs.h"

namespace OHOS::Ace::NG::GeneratedModifier {
class RichEditorStyledStringControllerPeerImpl : public RichEditorBaseControllerPeer {
public:
    RichEditorStyledStringControllerPeerImpl() = default;
    virtual ~RichEditorStyledStringControllerPeerImpl() = default;

    RefPtr<SpanStringBase> GetStyledString()
    {
        RefPtr<SpanStringBase> empty;
        if (auto controller = handler_.Upgrade(); controller) {
            auto styledStringController = AceType::DynamicCast<RichEditorStyledStringControllerBase>(controller);
            CHECK_NULL_RETURN(styledStringController, empty);
            return styledStringController->GetStyledString();
        }
        return empty;
    }

    void SetStyledString(const RefPtr<SpanStringBase>& spanString)
    {
        if (auto controller = handler_.Upgrade(); controller) {
            auto styledStringController = AceType::DynamicCast<RichEditorStyledStringControllerBase>(controller);
            CHECK_NULL_VOID(styledStringController);
            styledStringController->SetStyledString(spanString);
        }
    }

    void SetOnWillChange(std::function<bool(const StyledStringChangeValue&)> && func)
    {
        if (auto controller = handler_.Upgrade(); controller) {
            auto styledStringController = AceType::DynamicCast<RichEditorStyledStringControllerBase>(controller);
            CHECK_NULL_VOID(styledStringController);
            styledStringController->SetOnWillChange(std::move(func));
        }
    }

    void SetOnDidChange(std::function<void(const StyledStringChangeValue&)> && func)
    {
        if (auto controller = handler_.Upgrade(); controller) {
            auto styledStringController = AceType::DynamicCast<RichEditorStyledStringControllerBase>(controller);
            CHECK_NULL_VOID(styledStringController);
            styledStringController->SetOnDidChange(std::move(func));
        }
    }
};
} // namespace OHOS::Ace::NG::GeneratedModifier

struct RichEditorStyledStringControllerPeer
    : public OHOS::Ace::NG::GeneratedModifier::RichEditorStyledStringControllerPeerImpl {};

#endif //FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_RICHEDITOR_STYLED_CONTROLLER_PEER_IMPL_H
