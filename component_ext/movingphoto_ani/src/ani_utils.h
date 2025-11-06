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

#ifndef INTERFACE_ANI_BASE_HDS_ANI_UTILS_H
#define INTERFACE_ANI_BASE_HDS_ANI_UTILS_H

#include <ani.h>

namespace OHOS::Ace {

class AniAsyncEvent {
public:
    AniAsyncEvent(ani_env* env, ani_ref ref);
    ~AniAsyncEvent();
    ani_status Call(ani_size argc, ani_ref *argv);
    ani_env* GetEnv();

private:
    ani_env* env_;
    ani_ref ref_;
};

class AniUtils {
public:
    static bool GetIsUndefinedObject(ani_env *env, ani_ref objectRef);
    static bool ParseOptionalBool(ani_env *env, ani_object object, std::optional<bool> &result);
    static ani_status GetBool(ani_env *env, ani_object arg, bool &value);
    static ani_status GetBool(ani_env *env, ani_boolean arg, bool &value);
    static ani_status GetInt32(ani_env *env, ani_int arg, int32_t &value);
    static std::string AniStringToStdString(ani_env *env, ani_string ani_str);
    static bool GetIsEnum(ani_env *env, ani_ref objectRef, const char* enumName);
};
}
#endif