/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef INTERFACES_ETS_ANI_PROMPTACTION_SRC_DIALOG_PARAMS_H
#define INTERFACES_ETS_ANI_PROMPTACTION_SRC_DIALOG_PARAMS_H

#include <ani.h>
#include <cmath>
#include <regex>
#include <vector>
#include <string>
#include <iostream>
#include <array>

#include "prompt_action_params.h"

#include "core/common/container.h"
#include "core/common/resource/resource_wrapper.h"
#include "core/components/common/properties/color.h"
#include "core/components/theme/shadow_theme.h"
#include "core/common/resource/resource_manager.h"
#include "frameworks/base/log/log_wrapper.h"

constexpr float DEFAULT_AVOID_DISTANCE = 16.0f;

bool GetButtonInfo(ani_env* env, ani_ref resultRef, OHOS::Ace::ButtonInfo& result);
bool GetButtonInfo(ani_env* env, ani_object object, OHOS::Ace::ButtonInfo& result);
bool GetButtonArray(ani_env *env, ani_object object, const char *name, std::vector<OHOS::Ace::ButtonInfo>& result);
bool GetMaskRect(ani_env *env, ani_object object, std::optional<OHOS::Ace::DimensionRect>& result);
bool GetDialogAlignment(ani_env* env, ani_object object, OHOS::Ace::DialogAlignment& result);
bool GetThemeColorMode(ani_env* env, ani_object object, OHOS::Ace::ThemeColorMode& result);
bool GetAdaptiveColor(ani_env* env, ani_object object, OHOS::Ace::AdaptiveColor& result);
bool GetGrayscale(ani_env* env, ani_object object, std::vector<float>& result);
bool GetBlurOptions(ani_env* env, ani_object object, OHOS::Ace::BlurOption& result);
bool GetBlurStyleActivePolicy(ani_env* env, ani_object object, OHOS::Ace::BlurStyleActivePolicy& result);
bool GetBackgroundBlurStyleOptions(ani_env* env, ani_object object, std::optional<OHOS::Ace::BlurStyleOption>& result);
bool GetBackgroundEffectOptions(ani_env* env, ani_object object, std::optional<OHOS::Ace::EffectOption>& result);
bool GetLevelMode(ani_env* env, ani_object object, OHOS::Ace::LevelMode& result);
bool GetImmersiveMode(ani_env* env, ani_object object, OHOS::Ace::ImmersiveMode& result);
void UpdateDialogAlignment(OHOS::Ace::DialogAlignment& alignment);
bool GetOnLanguageChange(OHOS::Ace::DialogProperties& dialogProps);
bool GetShowDialogOptions(ani_env* env, ani_object object, OHOS::Ace::DialogProperties& dialogProps);
bool GetShowDialogOptionsInternal(ani_env* env, ani_object object, OHOS::Ace::DialogProperties& dialogProps);
ani_ref CreateShowDialogSuccessResponse(ani_env* env, int32_t index);
std::function<void(int32_t, int32_t)> GetShowDialogCallback(std::shared_ptr<PromptActionAsyncContext>& asyncContext);
std::function<void(int32_t, int32_t)> GetShowDialogPromise(std::shared_ptr<PromptActionAsyncContext>& asyncContext);
bool GetActionMenuButtons(ani_env *env, ani_object object, std::vector<OHOS::Ace::ButtonInfo>& result);
bool GetActionMenuOptions(ani_env* env, ani_object object, OHOS::Ace::DialogProperties& dialogProps);
ani_ref CreateActionMenuSuccessResponse(ani_env* env, int32_t index);
std::function<void(int32_t, int32_t)> GetShowActionMenuCallback(
    std::shared_ptr<PromptActionAsyncContext>& asyncContext);
std::function<void(int32_t, int32_t)> GetShowActionMenuPromise(
    std::shared_ptr<PromptActionAsyncContext>& asyncContext);
bool GetOnWillDismiss(ani_env* env, ani_object object,
    std::function<void(const int32_t& reason, const int32_t& instanceId)>& result);
bool GetKeyboardAvoidMode(ani_env* env, ani_object object, OHOS::Ace::KeyboardAvoidMode& result);
bool GetKeyboardAvoidDistance(ani_env *env, ani_object object, std::optional<OHOS::Ace::Dimension>& result);
bool GetBaseDialogOptions(ani_env* env, ani_object object, OHOS::Ace::DialogProperties& dialogProps);
bool GetTransitionEffectParam(ani_env* env, ani_object object, const char *name,
    OHOS::Ace::RefPtr<OHOS::Ace::NG::ChainedTransitionEffect>& result);
bool GetDialogOptionsInternal(ani_env* env, ani_object object, OHOS::Ace::DialogProperties& dialogProps);
std::function<void()> GetCustomBuilder(ani_env *env, ani_long builder);
bool GetCornerRadius(ani_env *env, ani_object object, std::optional<OHOS::Ace::NG::BorderRadiusProperty>& result);
bool GetBorderWidth(ani_env *env, ani_object object, std::optional<OHOS::Ace::NG::BorderWidthProperty>& result);
bool GetBorderColor(ani_env *env, ani_object object, std::optional<OHOS::Ace::NG::BorderColorProperty>& result);
bool GetBorderStyle(ani_env* env, ani_object object, OHOS::Ace::BorderStyle& result);
bool GetBorderStyle(ani_env* env, ani_object object, const char *name, OHOS::Ace::BorderStyle& result);
bool GetBorderStyle(ani_env *env, ani_object object, std::optional<OHOS::Ace::NG::BorderStyleProperty>& result);
bool GetCustomDialogOptions(ani_env* env, ani_object object, OHOS::Ace::DialogProperties& dialogProps);
std::function<void(int32_t)> GetOpenCustomDialogPromise(std::shared_ptr<PromptActionAsyncContext>& asyncContext);
std::function<void(int32_t)> GetCustomDialogContentPromise(std::shared_ptr<PromptActionAsyncContext>& asyncContext);
bool GetDialogOptions(ani_env* env, ani_object object, OHOS::Ace::DialogProperties& dialogProps);

#endif // INTERFACES_ETS_ANI_PROMPTACTION_SRC_DIALOG_PARAMS_H