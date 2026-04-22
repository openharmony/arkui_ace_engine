/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef INTERFACES_ETS_ANI_OVERLAYMANAGER_SRC_OVERLAY_PARAMS_H
#define INTERFACES_ETS_ANI_OVERLAYMANAGER_SRC_OVERLAY_PARAMS_H

#include <functional>

#include <ani.h>

#include "core/components_ng/pattern/overlay/overlay_options.h"

namespace OHOS::Ace {

struct OverlayAsyncContext {
    ani_vm* vm = nullptr;
    ani_resolver deferred = nullptr;
    int32_t instanceId = -1;
};

bool GetLevelMode(ani_env* env, ani_object object, LevelMode& result);
bool GetOrderOverlayOptions(ani_env* env, ani_object object, NG::OrderOverlayOptions& result);
bool GetOrderOverlayOptionsInternal(ani_env* env, ani_object object, NG::OrderOverlayOptions& result);
std::function<void(int32_t)> GetOpenOrderOverlayPromise(std::shared_ptr<OverlayAsyncContext>& asyncContext);

} // namespace OHOS::Ace

#endif // INTERFACES_ETS_ANI_OVERLAYMANAGER_SRC_OVERLAY_PARAMS_H
