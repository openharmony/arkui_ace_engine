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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_ACTION_SHEET_ACTION_SHEET_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_ACTION_SHEET_ACTION_SHEET_MODEL_NG_H

#include "core/components_ng/pattern/action_sheet/action_sheet_model.h"
#include "frameworks/base/utils/macros.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT ActionSheetModelNG : public OHOS::Ace::ActionSheetModel {
public:
    void ShowActionSheet(const DialogProperties& arg) override;
    void SetAction(GestureEventFunc&& eventFunc, ActionSheetInfo& sheetInfo) override;
    void SetCancel(std::function<void()>&& eventFunc, DialogProperties& arg) override;
    void SetConfirm(GestureEventFunc&& gestureEvent, std::function<void()>&& eventFunc,
        ButtonInfo& buttonInfo, DialogProperties& arg) override;
    void SetOnWillDismiss(std::function<void(const int32_t& info)>&& onWillDismissFunc,
        DialogProperties& arg) override;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_ACTION_SHEET_ACTION_SHEET_MODEL_NG_H
