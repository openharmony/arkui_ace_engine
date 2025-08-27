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
#include <type_traits>

#define ANI_CALL(env, call, onFail...)                                                                 \
    if (env) {                                                                                         \
        const char* aniErr[] = {                                                                       \
            "ANI_OK",                                                                                  \
            "ANI_ERROR",                                                                               \
            "ANI_INVALID_ARGS",                                                                        \
            "ANI_INVALID_TYPE",                                                                        \
            "ANI_INVALID_DESCRIPTOR",                                                                  \
            "ANI_INCORRECT_REF",                                                                       \
            "ANI_PENDING_ERROR",                                                                       \
            "ANI_NOT_FOUND",                                                                           \
            "ANI_ALREADY_BINDED",                                                                      \
            "ANI_OUT_OF_REF",                                                                          \
            "ANI_OUT_OF_MEMORY",                                                                       \
            "ANI_OUT_OF_RANGE",                                                                        \
            "ANI_BUFFER_TO_SMALL",                                                                     \
            "ANI_INVALID_VERSION",                                                                     \
            "ANI_AMBIGUOUS",                                                                           \
        };                                                                                             \
        ani_status ret;                                                                                \
        if ((ret = (env)->call) != ANI_OK) {                                                           \
            LOGE("ani call %{public}s failed: %{public}d, %{public}s", #call, ret,                     \
                static_cast<size_t>(ret) < std::extent_v<decltype(aniErr)> ? aniErr[ret] : "ANI_???"); \
            if (ret == ANI_PENDING_ERROR) {                                                            \
                ArktsAniUtils::ClearAniPendingError(env);                                              \
            }                                                                                          \
            onFail;                                                                                    \
        }                                                                                              \
    }

typedef struct __ani_env ani_env;
typedef class __ani_object* ani_object;
typedef class __ani_ref* ani_ref;
typedef struct __ani_vm ani_vm;

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

    /**
     * Clear ani pending error.
     */
    static void ClearAniPendingError(ani_env* env);

    /**
     * Get ani env from ani vm.
     */
    static ani_env* GetAniEnv(ani_vm* vm);
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_ARKTS_FRONTEND_ARKTS_ANI_UTILS_H
