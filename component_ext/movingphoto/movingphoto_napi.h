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

#ifndef COMPONENT_EXT_MOVING_PHOTO_MOVING_PHOTO_NAPI_H
#define COMPONENT_EXT_MOVING_PHOTO_MOVING_PHOTO_NAPI_H

#include "napi/native_api.h"
#include "napi/native_node_api.h"

namespace OHOS::Ace {
napi_value JsCreate(napi_env env, napi_callback_info info);
napi_value JsMuted(napi_env env, napi_callback_info info);
napi_value JsObjectFit(napi_env env, napi_callback_info info);
napi_value JsOnComplete(napi_env env, napi_callback_info info);
napi_value JsOnStart(napi_env env, napi_callback_info info);
napi_value JsOnStop(napi_env env, napi_callback_info info);
napi_value JsOnPause(napi_env env, napi_callback_info info);
napi_value JsOnFinish(napi_env env, napi_callback_info info);
napi_value JsOnError(napi_env env, napi_callback_info info);
napi_value StartPlayback(napi_env env, napi_callback_info info);
napi_value StopPlayback(napi_env env, napi_callback_info info);
napi_value JsAutoPlayPeriod(napi_env env, napi_callback_info info);
napi_value JsAutoPlay(napi_env env, napi_callback_info info);
napi_value JsRepeatPlay(napi_env env, napi_callback_info info);
napi_value MovingPhotoControllerConstructor(napi_env env, napi_callback_info info);
} // namespace OHOS::Ace
#endif // COMPONENT_EXT_MOVING_PHOTO_MOVING_PHOTO_NAPI_H
