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

#ifndef FRAMEWORKS_BRIDGE_CJ_FRONTEND_CPP_VIEW_SEARCH_H
#define FRAMEWORKS_BRIDGE_CJ_FRONTEND_CPP_VIEW_SEARCH_H

#include <cinttypes>

#include "bridge/cj_frontend/cppview/interactable_view.h"
#include "bridge/cj_frontend/cppview/view_abstract.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "core/components/text_field/text_field_controller.h"

namespace OHOS::Ace::Framework {

class ACE_EXPORT SearchController : public OHOS::FFI::FFIData {
    DECL_TYPE(SearchController, OHOS::FFI::FFIData)
public:
    SearchController() : FFIData()
    {
        LOGI("SearchController constructed: %{public}." PRId64, GetID());
    };
    ~SearchController() override = default;
    void CaretPosition(int32_t caretPosition);
    void StopEditing();
    void SetTextSelection(
        int32_t selectionStart, int32_t selectionEnd, const std::optional<SelectionOptions>& options = std::nullopt);
    void SetController(const RefPtr<OHOS::Ace::TextFieldControllerBase>& controller)
    {
        controller_ = controller;
    }

private:
    WeakPtr<TextFieldControllerBase> controller_;
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_CJ_FRONTEND_CPP_VIEW_SEARCH_H
