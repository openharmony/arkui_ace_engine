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
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_SEARCH_CONTROLLER_PEER_IMPL_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_SEARCH_CONTROLLER_PEER_IMPL_H

#include <optional>

#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/interfaces/arkoala/utility/converter.h"

#include "core/components_ng/pattern/text_field/text_field_model.h"

namespace OHOS::Ace::NG::Converter {
    template<>
    inline SelectionOptions Convert(const Ark_SelectionOptions& options) {
        SelectionOptions selectionOptions;
        //auto menuPolicy = OptConvert<MenuPolicy>(options.menuPolicy);
        //if (menuPolicy) {
            //selectionOptions.menuPolicy = *menuPolicy;
        //}
        return selectionOptions;
    }
} // namespace OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
class SearchControllerPeerImpl : public Referenced {
public:
    SearchControllerPeerImpl() = default;

    const WeakPtr<TextFieldControllerBase>& GetController() const
    {
        return controllerWeak_;
    }

    void SetController(const RefPtr<TextFieldControllerBase>& controller)
    {
        controllerWeak_ = controller;
    }

    void TriggerCaretPosition(const Ark_Number* value)
    {
        CHECK_NULL_VOID(value);
        auto caretPosition = Converter::Convert<int32_t>(*value);
        auto controller = controllerWeak_.Upgrade();
        if (controller) {
            if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
                caretPosition = caretPosition < 0 ? 0 : caretPosition;
            } else {
                // do nothing
            }
            controller->CaretPosition(caretPosition);
        } else {
            TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "CaretPosition: The JSTextEditableController is NULL");
        }
    }
    void TriggerStopEditing()
    {
        auto controller = controllerWeak_.Upgrade();
        if (controller) {
            controller->StopEditing();
        } else {
            TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "StopEditing: The JSTextEditableController is NULL");
        }
    }

    void TriggerSetTextSelection(const Ark_Number* selectionStart,
                          const Ark_Number* selectionEnd,
                          const Opt_SelectionOptions* options)
    {
        auto controller = controllerWeak_.Upgrade();
        if (controller) {
            std::optional<SelectionOptions> selectionOptions = std::nullopt;
            int32_t start = 0;
            int32_t end = 0;
            if (!selectionStart || !selectionEnd) {
                TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "SetTextSelection: The selectionStart or selectionEnd is NULL");
            }
            if (selectionStart != nullptr) {
                start = Converter::Convert<int32_t>(*selectionStart);
            }
            if (selectionEnd != nullptr) {
                end = Converter::Convert<int32_t>(*selectionEnd);
            }
            if (options != nullptr) {
                selectionOptions = Converter::OptConvert<SelectionOptions>(*options);
            }
            controller->SetTextSelection(start, end, selectionOptions);
        } else {
            TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "SetTextSelection: The controller is NULL");
        }
    }

private:
    WeakPtr<TextFieldControllerBase> controllerWeak_;
};
} // namespace OHOS::Ace::NG::GeneratedModifier
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_SEARCH_CONTROLLER_PEER_IMPL_H