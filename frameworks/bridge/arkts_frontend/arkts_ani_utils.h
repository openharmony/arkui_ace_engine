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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_ARKTS_FRONTEND_ARKTS_ANI_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_ARKTS_FRONTEND_ARKTS_ANI_UTILS_H

#include <cstdint>

typedef struct __ani_env ani_env;
typedef class __ani_object* ani_object;
typedef class __ani_ref* ani_ref;

namespace OHOS::Ace {
class ArktsAniUtils final {
public:
    /**
     * Create std/core/Boolean.
     */
    static int32_t CreateAniBoolean(ani_env* env, bool value, ani_object& result);

    /**
     * Get AbcRuntimeLinkder to load application class.
     */
    static int32_t GetNearestNonBootRuntimeLinker(ani_env*, ani_ref& result);
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_ARKTS_FRONTEND_ARKTS_ANI_UTILS_H
