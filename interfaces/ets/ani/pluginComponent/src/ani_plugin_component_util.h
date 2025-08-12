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
#ifndef OHOS_ANI_ACE_PLUGIN_UTIL_H
#define OHOS_ANI_ACE_PLUGIN_UTIL_H
#include <string>
#include <ani.h>
#include "ani_plugin_component_data.h"

ACEAsyncJSCallbackInfo* AceCreateAsyncJSCallbackInfo(ani_env* env);
bool AceIsSameFuncFromANI(ACECallbackInfo& left, ACECallbackInfo& right);
ani_ref CreateInt(ani_env* env, ani_int value);
ani_string AceWrapStringToAni(ani_env* env, std::string str);
ani_ref AceWrapStringToObject(ani_env* env, std::string str);
std::string AniStringToNativeString(ani_env* env, ani_string ani_str);
ani_status GetAniKVObjectPropertyByName(ani_env* env, ani_object parameters, std::string propertyName,
    std::string &propertyValue);
ani_status GetAniStringPropertyByName(ani_env* env, ani_object parameters, std::string propertyName,
    std::string &propertyValue);
void AceFreeAsyncJSCallbackInfo(ACEAsyncJSCallbackInfo** asyncCallbackInfo);
#endif // OHOS_ANI_ACE_PLUGIN_UTIL_H