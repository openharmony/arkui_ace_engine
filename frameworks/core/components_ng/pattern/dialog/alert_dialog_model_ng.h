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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_DIALOG_FORM_FORM_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_DIALOG_FORM_FORM_MODEL_NG_H

#include "core/components_ng/pattern/dialog/alert_dialog_model.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT AlertDialogModelNG : public OHOS::Ace::AlertDialogModel {
public:
    void SetParseButtonObj(std::function<void()>&& eventFuncImpl, ButtonInfo& buttonInfo, DialogProperties& arg,
        const std::string& property) override;
    void SetOnCancel(std::function<void()>&& eventFunc, DialogProperties& arg) override;
    void SetShowDialog(const DialogProperties& arg) override;
    void SetOnWillDismiss(std::function<void(const int32_t& info, const int32_t& instanceId)>&& onWillDismissFunc,
        DialogProperties& arg) override;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_DIALOG_FORM_FORM_MODEL_NG_H
