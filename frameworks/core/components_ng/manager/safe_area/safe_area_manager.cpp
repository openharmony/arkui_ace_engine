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
#include "safe_area_manager.h"

#include "core/components_ng/property/safe_area_insets.h"
namespace OHOS::Ace::NG {
bool SafeAreaManager::UpdateCutoutSafeArea(const SafeAreaInsets& safeArea)
{
    if (cutoutSafeArea_ == safeArea) {
        return false;
    }
    cutoutSafeArea_ = safeArea;
    return true;
}

bool SafeAreaManager::UpdateSystemSafeArea(const SafeAreaInsets& safeArea)
{
    if (systemSafeArea_ == safeArea) {
        return false;
    }
    systemSafeArea_ = safeArea;
    return true;
}

bool SafeAreaManager::UpdateKeyboardSafeArea(float keyboardHeight)
{
    auto bottom = systemSafeArea_.bottom_.start;
    SafeAreaInsets::Inset inset { .start = bottom - keyboardHeight, .end = bottom };
    if (inset == keyboardInset_) {
        return false;
    }
    keyboardInset_ = inset;
    return true;
}

SafeAreaInsets SafeAreaManager::GetCombinedSafeArea(const SafeAreaExpandOpts& opts) const
{
    SafeAreaInsets res;
    if (opts.type & SAFE_AREA_TYPE_CUTOUT) {
        res = res.Combine(cutoutSafeArea_);
    }
    if (opts.type & SAFE_AREA_TYPE_SYSTEM) {
        res = res.Combine(systemSafeArea_);
    }
    return res;
}
} // namespace OHOS::Ace::NG