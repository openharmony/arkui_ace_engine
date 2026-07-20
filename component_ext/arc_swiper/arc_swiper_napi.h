/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef COMPONENT_EXT_ARC_SWIPER_ARC_SWIPER_NAPI_H
#define COMPONENT_EXT_ARC_SWIPER_ARC_SWIPER_NAPI_H

#include "napi/native_api.h"
#include "napi/native_node_api.h"

#include "core/components_ng/pattern/swiper/swiper_model.h"

namespace OHOS::Ace {

// Type tags for napi_wrap_s/napi_unwrap_s type safety
constexpr napi_type_tag ARC_SWIPER_CONTROLLER_TYPE_TAG = {
    .lower = 0x7D3E8B2C9F5A1E4D,
    .upper = 0x8B4F2C9E3D6A7F1B,
};

constexpr napi_type_tag ARC_SWIPER_INDICATOR_TYPE_TAG = {
    .lower = 0x3A9F5E2D8B1C4A7E,
    .upper = 0x6C7D3E9F2B5A8D1F,
};

napi_value JsCreate(napi_env env, napi_callback_info info);
napi_value JsIndex(napi_env env, napi_callback_info info);
napi_value JsIndicator(napi_env env, napi_callback_info info);
napi_value JsDuration(napi_env env, napi_callback_info info);
napi_value JsVertical(napi_env env, napi_callback_info info);
napi_value JsDisableSwipe(napi_env env, napi_callback_info info);
napi_value JsOnChange(napi_env env, napi_callback_info info);
napi_value JsOnAnimationStart(napi_env env, napi_callback_info info);
napi_value JsOnAnimationEnd(napi_env env, napi_callback_info info);
napi_value JsOnGestureSwipe(napi_env env, napi_callback_info info);
napi_value JsSetDigitalCrownSensitivity(napi_env env, napi_callback_info info);
napi_value JsSetEffectMode(napi_env env, napi_callback_info info);
napi_value JsSetCustomContentTransition(napi_env env, napi_callback_info info);
napi_value JsSetDisableTransitionAnimation(napi_env env, napi_callback_info info);
napi_value ShowNext(napi_env env, napi_callback_info info);
napi_value ShowPrevious(napi_env env, napi_callback_info info);
napi_value FinishAnimation(napi_env env, napi_callback_info info);
} // namespace OHOS::Ace
#endif // COMPONENT_EXT_ARC_SWIPER_ARC_SWIPER_NAPI_H
