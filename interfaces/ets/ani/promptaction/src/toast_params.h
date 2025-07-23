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

#ifndef INTERFACES_ETS_ANI_PROMPTACTION_SRC_TOAST_PARAMS_H
#define INTERFACES_ETS_ANI_PROMPTACTION_SRC_TOAST_PARAMS_H

#include <ani.h>
#include <array>
#include <cmath>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "prompt_action_params.h"

#include "core/common/container.h"
#include "core/common/resource/resource_manager.h"
#include "core/common/resource/resource_wrapper.h"
#include "core/components/common/properties/color.h"
#include "core/components/theme/shadow_theme.h"
#include "core/components_ng/pattern/toast/toast_layout_property.h"
#include "frameworks/base/log/log_wrapper.h"

bool GetToastBottom(ani_env* env, ani_object object, std::string& result);
bool GetToastShowMode(ani_env* env, ani_object object, OHOS::Ace::NG::ToastShowMode& result);
bool GetToastAlignment(ani_env* env, ani_object object, int32_t& result);
bool GetToastShadow(ani_env* env, ani_object object, std::optional<OHOS::Ace::Shadow>& result, bool& isTypeStyleShadow);
bool GetShowToastOptions(ani_env* env, ani_object object, OHOS::Ace::NG::ToastInfo& result);
std::function<void(int32_t)> GetToastPromise(std::shared_ptr<PromptActionAsyncContext>& asyncContext);

#endif // INTERFACES_ETS_ANI_PROMPTACTION_SRC_TOAST_PARAMS_H