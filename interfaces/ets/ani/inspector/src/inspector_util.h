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
 
#ifndef INTERFACES_ETS_ANI_INSPECTOR_UTILS_H
#define INTERFACES_ETS_ANI_INSPECTOR_UTILS_H
 
#include <ani.h>
#include "core/components_ng/base/inspector_filter.h"
#include <string>
 
 
namespace OHOS::Ace {
void AniThrow(ani_env *env, const std::string &errMsg);
ani_status ANIUtils_ANIStringToStdString(ani_env *env, ani_string ani_str, std::string& str);
NG::InspectorFilter GetInspectorFilter(ani_env *env, const ani_array_ref& filters, bool& isLayoutInspector);
} // namespace OHOS::Ace
#endif // #define INTERFACES_ETS_ANI_INSPECTOR_UTILS_H