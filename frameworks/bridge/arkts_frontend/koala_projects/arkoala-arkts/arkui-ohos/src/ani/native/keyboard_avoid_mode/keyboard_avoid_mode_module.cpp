/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "load.h"
#include <memory>
#include "keyboard_avoid_mode_module.h"
#include "interfaces/inner_api/drawable_descriptor/base/log.h"

namespace OHOS::Ace::Ani {

void SetKeyboardAvoidMode(ani_env* env, [[maybe_unused]] ani_object obj, ani_enum_item mode)
{
    const auto* modifier = GetNodeAniModifier();
    if (!env || !modifier) {
        return;
    }
    auto keyboardAvoidModeAniModifier = modifier->getKeyboardAvoidModeAniModifier();
    CHECK_NULL_VOID(keyboardAvoidModeAniModifier);
    ani_int intValue;
    ani_status status = ANI_OK;
    if ((status = env->EnumItem_GetValue_Int(mode, &intValue)) != ANI_OK) {
        HILOGE("SetKeyboardAvoidMode EnumItem_GetValue_Int failed, status:%{public}d", status);
        return;
    }
    int32_t index = static_cast<int32_t>(intValue);
    keyboardAvoidModeAniModifier->setKeyboardAvoidMode(index);
}

ani_ref GetKeyboardAvoidMode(ani_env* env, [[maybe_unused]] ani_object obj)
{
    ani_ref enumItem;
    if (!GetKeyboardAvoidModeImpl(env, reinterpret_cast<ani_enum_item*>(&enumItem))) {
        if (ANI_OK != env->GetUndefined(&enumItem)) {
            HILOGE("GetKeyboardAvoidMode GetUndefined failed");
        }
        return enumItem;
    }
    return enumItem;
}
 
bool GetKeyboardAvoidModeImpl(ani_env* env, ani_enum_item* enumItem)
{
    const auto* modifier = GetNodeAniModifier();
    if (!env || !modifier) {
        return false;
    }
    ani_enum enumType;
    ani_status status = ANI_OK;
    if ((status = env->FindEnum("@ohos.arkui.UIContext.KeyboardAvoidMode", &enumType)) != ANI_OK) {
        HILOGE("GetKeyboardAvoidMode FindEnum failed, status:%{public}d", status);
        return false;
    }
    auto keyboardAvoidModeAniModifier = modifier->getKeyboardAvoidModeAniModifier();
    CHECK_NULL_RETURN(keyboardAvoidModeAniModifier, false);
    ArkUI_Int32 index = keyboardAvoidModeAniModifier->getKeyboardAvoidMode();
    if ((status = env->Enum_GetEnumItemByIndex(enumType, static_cast<ani_size>(index), enumItem)) != ANI_OK) {
        HILOGE("GetKeyboardAvoidMode GetEnumItem failed, status:%{public}d, index:%{public}d", status, index);
        return false;
    }
    return true;
}

} // namespace OHOS::Ace::Ani
