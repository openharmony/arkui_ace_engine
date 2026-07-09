/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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
// [Start xcomponent_init]
#include "ani/ani.h"
#include <array>

#include "hilog/log.h"
#include "common/common.h"
#include "manager/plugin_manager.h"

namespace NativeXComponentSample {
namespace {
// ANI native method implementations. Each receives the surfaceId as ani_long
// (int64_t) and dispatches to the shared PluginManager core logic.

static void AniSetSurfaceId([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_long surfaceId)
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "ArkTSXComponent", "AniSetSurfaceId surfaceId=%{public}lld",
                 static_cast<long long>(surfaceId));
    PluginManager::SetSurfaceIdCore(static_cast<int64_t>(surfaceId));
}

static void AniDestroySurface([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_long surfaceId)
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "ArkTSXComponent", "AniDestroySurface surfaceId=%{public}lld",
                 static_cast<long long>(surfaceId));
    PluginManager::DestroySurfaceCore(static_cast<int64_t>(surfaceId));
}

static void AniChangeSurface([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_long surfaceId)
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "ArkTSXComponent", "AniChangeSurface surfaceId=%{public}lld",
                 static_cast<long long>(surfaceId));
    PluginManager::ChangeSurfaceCore(static_cast<int64_t>(surfaceId));
}

static void AniChangeColor([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_long surfaceId)
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "ArkTSXComponent", "AniChangeColor surfaceId=%{public}lld",
                 static_cast<long long>(surfaceId));
    PluginManager::ChangeColorCore(static_cast<int64_t>(surfaceId));
}

static void AniDrawPattern([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_long surfaceId)
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "ArkTSXComponent", "AniDrawPattern surfaceId=%{public}lld",
                 static_cast<long long>(surfaceId));
    PluginManager::DrawPatternCore(static_cast<int64_t>(surfaceId));
}

// GetXComponentStatus is simplified to void for ANI static mode. The drawing
// state is reflected on screen directly, so no status object is required.
static void AniGetXComponentStatus([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object,
                                   [[maybe_unused]] ani_long surfaceId)
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "ArkTSXComponent",
        "AniGetXComponentStatus surfaceId=%{public}lld", static_cast<long long>(surfaceId));
}

static ani_status BindNativeMethods(ani_vm *vm, const char *clsName)
{
    // [StartExclude xcomponent_init]
    ani_env *env;
    if (ANI_OK != vm->GetEnv(ANI_VERSION_1, &env)) {
        return ANI_INVALID_VERSION;
    }

    ani_class cls {};
    if (ANI_OK != env->FindClass(clsName, &cls)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "ArkTSXComponent", "FindClass failed: %{public}s", clsName);
        return ANI_INVALID_ARGS;
    }
    // [EndExclude xcomponent_init]

    // "l:" -> single long parameter, void return.
    const char *sig = "l:";
    std::array<ani_native_function, 6> methods = {
        ani_native_function {"SetSurfaceId", sig, reinterpret_cast<void *>(AniSetSurfaceId)},
        ani_native_function {"DestroySurface", sig, reinterpret_cast<void *>(AniDestroySurface)},
        ani_native_function {"ChangeSurface", sig, reinterpret_cast<void *>(AniChangeSurface)},
        ani_native_function {"ChangeColor", sig, reinterpret_cast<void *>(AniChangeColor)},
        ani_native_function {"DrawPattern", sig, reinterpret_cast<void *>(AniDrawPattern)},
        ani_native_function {"GetXComponentStatus", sig, reinterpret_cast<void *>(AniGetXComponentStatus)},
    };

    if (ANI_OK != env->Class_BindStaticNativeMethods(cls, methods.data(), methods.size())) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "ArkTSXComponent",
                     "Class_BindStaticNativeMethods failed");
        return ANI_INVALID_TYPE;
    }
    return ANI_OK;
}
} // namespace
} // namespace NativeXComponentSample

ANI_EXPORT ani_status ANI_Constructor(ani_vm *vm, uint32_t *result)
{
    OH_LOG_Print(LOG_APP, LOG_INFO, NativeXComponentSample::LOG_PRINT_DOMAIN, "ArkTSXComponent",
                 "entering libentry.so's ANI_Constructor");
    NativeXComponentSample::BindNativeMethods(vm, "entry.src.main.ets.pages.Index.NativeMethods");
    *result = ANI_VERSION_1;
    return ANI_OK;
}
// [End xcomponent_init]
