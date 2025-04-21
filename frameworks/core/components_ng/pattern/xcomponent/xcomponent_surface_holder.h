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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_XCOMPONENT_XCOMPONENT_SURFACE_HOLDER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_XCOMPONENT_XCOMPONENT_SURFACE_HOLDER_H

#include <future>
#include <list>
#include "interfaces/native/native_interface_xcomponent.h"

struct OH_ArkUI_SurfaceCallback {
    /** Called when the surface is created. */
    void (*OnSurfaceCreated)(OH_ArkUI_SurfaceHolder* holder);
    /** Called when the surface is changed. */
    void (*OnSurfaceChanged)(OH_ArkUI_SurfaceHolder* holder, uint64_t width, uint64_t height);
    /** Called when the surface is destroyed. */
    void (*OnSurfaceDestroyed)(OH_ArkUI_SurfaceHolder* holder);
};

struct OH_ArkUI_SurfaceHolder {
    OH_ArkUI_SurfaceHolder() {}
    ~OH_ArkUI_SurfaceHolder() {}
    int32_t AddSurfaceCallback(OH_ArkUI_SurfaceCallback* callback)
    {
        auto iter = std::find(surfaceCallbackList_.begin(), surfaceCallbackList_.end(), callback);
        if (iter != surfaceCallbackList_.end()) {
            return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
        }
        surfaceCallbackList_.emplace_back(callback);
        return OHOS::Ace::ERROR_CODE_NO_ERROR;
    }

    int32_t RemoveSurfaceCallback(OH_ArkUI_SurfaceCallback* callback)
    {
        auto iter = std::find(surfaceCallbackList_.begin(), surfaceCallbackList_.end(), callback);
        if (iter == surfaceCallbackList_.end()) {
            return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
        }
        surfaceCallbackList_.erase(iter);
        return OHOS::Ace::ERROR_CODE_NO_ERROR;
    }
    void* userData_ = nullptr;
    OHNativeWindow* nativeWindow_ = nullptr;
    std::list<OH_ArkUI_SurfaceCallback*> surfaceCallbackList_;
    ArkUI_NodeHandle node_ = nullptr;
};
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_XCOMPONENT_XCOMPONENT_SURFACE_HOLDER_H
