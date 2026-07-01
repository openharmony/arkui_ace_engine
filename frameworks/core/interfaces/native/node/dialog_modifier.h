/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_INTERFACE_INNER_API_NATIVE_NODE_DIALOG_MODIFIER_H
#define FRAMEWORKS_INTERFACE_INNER_API_NATIVE_NODE_DIALOG_MODIFIER_H

#include "core/components_ng/pattern/dialog/action_sheet/action_sheet_model_ng.h"
#include "core/components_ng/pattern/dialog/alert_dialog/alert_dialog_model_ng.h"
#include "core/components_ng/pattern/dialog/bridge/inner_modifier/dialog_inner_modifier.h"
#include "core/components_ng/pattern/dialog/custom_dialog/custom_dialog_controller_model_ng.h"
#include "core/interfaces/cjui/cjui_api.h"

namespace OHOS::Ace::NG::NodeModifier {
const ArkUIDialogAPI* GetDialogAPI();
const CJUIDialogAPI* GetCJUIDialogAPI();
ACE_FORCE_EXPORT const ArkUIDialogInnerModifier* GetDialogInnerModifier();
ACE_FORCE_EXPORT ActionSheetModelNG* GetActionSheetModel();
ACE_FORCE_EXPORT AlertDialogModelNG* GetAlertDialogModel();
ACE_FORCE_EXPORT CustomDialogControllerModelNG* GetCustomDialogControllerModel();
} // namespace OHOS::Ace::NG::NodeModifier

#endif // FRAMEWORKS_INTERFACE_INNER_API_NATIVE_NODE_DIALOG_MODIFIER_H
