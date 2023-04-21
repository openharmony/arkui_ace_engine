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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DIALOG_CUSTOM_DIALOG_CONTROLLER_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DIALOG_CUSTOM_DIALOG_CONTROLLER_MODEL_NG_H

#include "core/components/dialog/dialog_component.h"
#include "core/components_ng/pattern/dialog/custom_dialog_controller_model.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT CustomDialogControllerModelNG : public OHOS::Ace::CustomDialogControllerModel {
public:
    RefPtr<AceType> SetOpenDialog() override;
    void SetOpenDialog(DialogProperties& dialogProperties, std::vector<WeakPtr<AceType>>& dialogs,
        std::function<void(RefPtr<AceType>&)>&& task, bool& pending, RefPtr<AceType>& overlayManager,
        std::function<void()>&& cancelTask) override;
    void SetCloseDialog(DialogProperties& dialogProperties, std::vector<WeakPtr<AceType>>& dialogs, bool& pending,
        std::function<void()>&& task, RefPtr<AceType>& dialogComponent) override;
    void setOnCancel(std::function<void()>&& event, std::function<void()>&& onCancel) override;
};
} // namespace OHOS::Ace::NG
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_DIALOG_JS_CUSTOM_DIALOG_CONTROLLER_H