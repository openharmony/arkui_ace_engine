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
#include "stateMgmt_module.h"
#include "base/log/log_wrapper.h"
#include "load.h"
#include "utils/ani_utils.h"

#include <memory>

namespace OHOS::Ace::Ani {
ani_string PersistentStorage_Get(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_string aniKey)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return nullptr;
    }

    auto strKey = AniUtils::ANIStringToStdString(env, aniKey);
    std::string ret = modifier->getStateMgmtAniModifier()->persistentStorageGet(strKey);
    if (!ret.empty()) {
        auto retValue = AniUtils::StdStringToANIString(env, ret);
        if (retValue) {
            return *retValue;
        }
    }
    return nullptr;
}

void PersistentStorage_Set(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_string aniKey, ani_string aniValue)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return;
    }
    auto strKey = AniUtils::ANIStringToStdString(env, aniKey);
    auto strVal = AniUtils::ANIStringToStdString(env, aniValue);
    modifier->getStateMgmtAniModifier()->persistentStorageSet(strKey, strVal);
    return;
}

ani_boolean PersistentStorage_Has(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_string aniKey)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return false;
    }
    auto strKey = AniUtils::ANIStringToStdString(env, aniKey);
    bool ret = modifier->getStateMgmtAniModifier()->persistentStorageHas(strKey);
    if (ret) {
        return true;
    }
    return false;
}

void PersistentStorage_Clear(ani_env* env, [[maybe_unused]] ani_object aniClass)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return;
    }
    modifier->getStateMgmtAniModifier()->persistentStorageClear();
    return;
}

void PersistentStorage_Delete(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_string aniKey)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return;
    }
    auto strKey = AniUtils::ANIStringToStdString(env, aniKey);
    modifier->getStateMgmtAniModifier()->persistentStorageDelete(strKey);
    return;
}

ani_int Env_GetColorMode(ani_env* env)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return 0;
    }
    auto ret = modifier->getStateMgmtAniModifier()->getColorMode();
    return ret;
}

ani_float Env_GetFontScale(ani_env* env)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return 0;
    }
    auto ret = modifier->getStateMgmtAniModifier()->getFontScale();
    return ret;
}

ani_float Env_GetFontWeightScale(ani_env* env)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return 0;
    }
    auto ret = modifier->getStateMgmtAniModifier()->getFontWeightScale();
    return ret;
}

ani_boolean Env_GetAccessibilityEnabled(ani_env* env)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return false;
    }
    auto ret = modifier->getStateMgmtAniModifier()->getAccessibilityEnabled();
    return ret;
}

ani_string Env_GetLayoutDirection(ani_env* env)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return nullptr;
    }
    auto ret = modifier->getStateMgmtAniModifier()->getLayoutDirection();
    if (!ret.empty()) {
        auto retValue = AniUtils::StdStringToANIString(env, ret);
        if (retValue) {
            return *retValue;
        }
    }
    return nullptr;
}

ani_string Env_GetLanguageCode(ani_env* env)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return nullptr;
    }
    auto ret = modifier->getStateMgmtAniModifier()->getLanguageCode();
    if (!ret.empty()) {
        auto retValue = AniUtils::StdStringToANIString(env, ret);
        if (retValue) {
            return *retValue;
        }
    }
    return nullptr;
}
} // namespace OHOS::Ace::Ani