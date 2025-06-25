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
#ifndef INTERFACES_ETS_ANI_DRAG_CONTROLLER_DRAG_CONTROLLER_UTILS_H
#define INTERFACES_ETS_ANI_DRAG_CONTROLLER_DRAG_CONTROLLER_UTILS_H

#include "core/interfaces/ani/ani_api.h"
#include "base/log/log.h"
namespace OHOS::Ace::NG {
ani_error GetErrorObject(ani_env* env, const std::string& errMsg, int32_t code);
void AniThrow(ani_env* env, const std::string& errMsg, int32_t code);
bool IsUndefinedObject(ani_env* env, ani_ref objectRef);
std::string ANIUtils_ANIStringToStdString(ani_env* env, ani_string ani_str);
bool IsFunctionObject(ani_env* env, ani_ref obj);
bool IsBigIntObject(ani_env* env, ani_ref obj);
bool IsFunctionObjectWith2Param(ani_env* env, ani_ref obj);
bool IsNumberObject(ani_env* env, ani_ref obj);
bool IsInt32Object(ani_env* env, ani_ref obj);
bool IsStringObject(ani_env* env, ani_ref obj);
bool IsArrayObject(ani_env* env, ani_ref obj);
bool IsBooleanObject(ani_env* env, ani_ref obj);
bool GetBigIntValue(ani_env* env, ani_object object, int64_t& longValue);
bool GetEnumItem([[maybe_unused]] ani_env* env, ani_size index, const char* enumName, ani_enum_item& enumItem);
bool IsDragPreviewModeEnum(ani_env *env, ani_ref obj);
} // namespace OHOS::Ace::NG
#endif // INTERFACES_ETS_ANI_DRAG_CONTROLLER_DRAG_CONTROLLER_UTILS_H