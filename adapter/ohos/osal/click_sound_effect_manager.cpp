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

#include "core/common/click_effect/click_sound_effect_manager.h"

#include <dlfcn.h>

#include "base/log/log.h"

namespace OHOS::Ace {
namespace {
#if (defined(__aarch64__) || defined(__x86_64__))
const std::string DEFAULT_CLICK_SOUND_EFFECT_SO_PATH = "/system/lib64/libdefault_click_sound_effect.z.so";
#else
const std::string DEFAULT_CLICK_SOUND_EFFECT_SO_PATH = "/system/lib/libdefault_click_sound_effect.z.so";
#endif
} // namespace

ClickSoundEffectManager& ClickSoundEffectManager::GetInstance()
{
    static ClickSoundEffectManager instance;
    return instance;
}

ClickSoundEffectManager::~ClickSoundEffectManager()
{
    UnloadProductPolicy();
}

bool ClickSoundEffectManager::LoadProductPolicy()
{
    if (defaultClickSoundEffectSoLoaded_ && libraryHandle_ != nullptr && productPolicy_ != nullptr) {
        return true;
    }
    libraryHandle_ = dlopen(DEFAULT_CLICK_SOUND_EFFECT_SO_PATH.c_str(), RTLD_LAZY);
    if (libraryHandle_ == nullptr) {
        const char* error = dlerror();
        TAG_LOGE(
            AceLogTag::ACE_UIEVENT, "Failed to open libdefault_click_sound_effect.z.so, reason: %{public}s", error);
        return false;
    }
    auto getClickSoundEffectPolicyInstance = (void* (*)())dlsym(libraryHandle_, "GetClickSoundEffectPolicyInstance");
    if (getClickSoundEffectPolicyInstance == nullptr) {
        const char* error = dlerror();
        TAG_LOGE(AceLogTag::ACE_UIEVENT,
            "Failed to get GetClickSoundEffectPolicyInstance func in libdefault_click_sound_effect.z.so, reason: "
            "%{public}s",
            error);
        Close();
        return false;
    }
    productPolicy_ = reinterpret_cast<Kit::ClickSoundEffectPolicy*>(getClickSoundEffectPolicyInstance());
    defaultClickSoundEffectSoLoaded_ = true;
    return true;
}

void ClickSoundEffectManager::UnloadProductPolicy()
{
    productPolicy_ = nullptr;
    Close();
    libraryHandle_ = nullptr;
    defaultClickSoundEffectSoLoaded_ = false;
}

void ClickSoundEffectManager::Close()
{
    if (libraryHandle_ != nullptr) {
        dlclose(libraryHandle_);
    }
}

void ClickSoundEffectManager::PlayClickSoundEffect(int32_t abscissa, int32_t ordinate)
{
    if (productPolicy_) {
        TAG_LOGD(AceLogTag::ACE_UIEVENT, "Load libdefault_click_sound_effect.z.so successfully");
        productPolicy_->InteractiveSoundEffects(0, 0, abscissa, ordinate);
    }
}
} // namespace OHOS::Ace
