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

#ifndef FRAMEWORKS_BRIDGE_ARKTS_FRONTEND_KOALA_PROJECTS_ARKOALA_FRAMEWORK_NATIVE_SRC_RESOURCE_COLOR_HELPER_H
#define FRAMEWORKS_BRIDGE_ARKTS_FRONTEND_KOALA_PROJECTS_ARKOALA_FRAMEWORK_NATIVE_SRC_RESOURCE_COLOR_HELPER_H

#include <vector>

#include "generated/arkoala_api_generated.h"
#include "ui/base/macros.h"

class Deserializer;

namespace OHOS::Ace {
std::vector<Ark_ResourceColor> ACE_FORCE_EXPORT GetResourceColorArray(int64_t thisArray, int32_t thisLength);
Ark_ResourceColor ACE_FORCE_EXPORT DeserializerResourceColor(Deserializer& deserializer);
} // namespace OHOS::Ace

#endif
