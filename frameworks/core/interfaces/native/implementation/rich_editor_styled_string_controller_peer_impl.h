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
#include "core/interfaces/native/utility/converter.h"
#include "rich_editor_controller_structs.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
class RichEditorStyledStringControllerPeerImpl {
public:
    RichEditorStyledStringControllerPeerImpl() = default;

    void AddTargetController(const WeakPtr<RichEditorStyledStringController> &handler)
    {
        handler_ = handler;
    }

    RefPtr<SpanStringBase> GetStyledString()
    {
        if (auto controller = handler_.Upgrade(); controller) {
            return controller->GetStyledString();
        }
        RefPtr<SpanStringBase> empty;
        return empty;
    }

    void SetStyledString(const RefPtr<SpanStringBase>& spanString)
    {
        if (auto controller = handler_.Upgrade(); controller) {
            controller->SetStyledString(spanString);
        }
    }

    void SetOnWillChange(std::function<bool(const StyledStringChangeValue&)> && func)
    {
        if (auto controller = handler_.Upgrade(); controller) {
            controller->SetOnWillChange(std::move(func));
        }
    }

    void SetOnDidChange(std::function<void(const StyledStringChangeValue&)> && func)
    {
        if (auto controller = handler_.Upgrade(); controller) {
            controller->SetOnDidChange(std::move(func));
        }
    }

    void SetPattern(const WeakPtr<RichEditorPattern>& pattern)
    {
        if (auto controller = handler_.Upgrade(); controller) {
            controller->SetPattern(pattern);
        }
    }

private:
    Ace::WeakPtr<RichEditorStyledStringController> handler_;
};
} // namespace OHOS::Ace::NG::GeneratedModifier
#endif //FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_RICHEDITOR_STYLED_CONTROLLER_PEER_IMPL_H
