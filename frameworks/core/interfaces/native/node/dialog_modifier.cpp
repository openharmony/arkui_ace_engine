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
#include "core/interfaces/native/node/dialog_modifier.h"

#include "base/log/log_wrapper.h"
#include "core/common/dynamic_module_helper.h"

namespace OHOS::Ace::NG {
namespace NodeModifier {
const ArkUIDialogAPI* GetDialogAPI()
{
    static const ArkUIDialogAPI* modifier = nullptr;
    if (modifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Dialog");
        if (module == nullptr) {
            LOGF_ABORT("Can't find dialog dynamic module");
        }
        modifier = reinterpret_cast<const ArkUIDialogAPI*>(module->GetCustomModifier("dialogCAPI"));
    }
    return modifier;
}

const CJUIDialogAPI* GetCJUIDialogAPI()
{
    static const CJUIDialogAPI* modifier = nullptr;
    if (modifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Dialog");
        if (module == nullptr) {
            LOGF_ABORT("Can't find dialog dynamic module");
        }
        modifier = reinterpret_cast<const CJUIDialogAPI*>(module->GetCjModifier());
    }
    return modifier;
}

const ArkUIDialogInnerModifier* GetDialogInnerModifier()
{
    static const ArkUIDialogInnerModifier* modifier = nullptr;
    if (modifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Dialog");
        if (module == nullptr) {
            LOGF_ABORT("Can't find dialog dynamic module");
        }
        modifier = reinterpret_cast<const ArkUIDialogInnerModifier*>(module->GetCustomModifier("dialogInnerModifier"));
    }
    return modifier;
}

ActionSheetModelNG* GetActionSheetModel()
{
    static ActionSheetModelNG* cachedModel = nullptr;
    if (cachedModel == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Dialog");
        if (module == nullptr) {
            LOGF_ABORT("Can't find dialog dynamic module");
        }
        cachedModel = reinterpret_cast<ActionSheetModelNG*>(module->GetModel("actionSheetModelNG"));
    }
    return cachedModel;
}

AlertDialogModelNG* GetAlertDialogModel()
{
    static AlertDialogModelNG* cachedModel = nullptr;
    if (cachedModel == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Dialog");
        if (module == nullptr) {
            LOGF_ABORT("Can't find dialog dynamic module");
        }
        cachedModel = reinterpret_cast<AlertDialogModelNG*>(module->GetModel("alertDialogModelNG"));
    }
    return cachedModel;
}

CustomDialogControllerModelNG* GetCustomDialogControllerModel()
{
    static CustomDialogControllerModelNG* cachedModel = nullptr;
    if (cachedModel == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Dialog");
        if (module == nullptr) {
            LOGF_ABORT("Can't find dialog dynamic module");
        }
        cachedModel =
            reinterpret_cast<CustomDialogControllerModelNG*>(module->GetModel("customDialogControllerModelNG"));
    }
    return cachedModel;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
