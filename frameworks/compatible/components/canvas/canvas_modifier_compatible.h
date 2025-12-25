/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_COMPATIBLE_COMPONENTS_CANVAS_CANVAS_MODIFIER_COMPATIBLE_H
#define FOUNDATION_ACE_FRAMEWORKS_COMPATIBLE_COMPONENTS_CANVAS_CANVAS_MODIFIER_COMPATIBLE_H

#include <cstdint>
#include <string>

#ifdef __cplusplus
extern "C" {
#endif

namespace OHOS::Ace {
struct CanvasBridgeParams;

struct ArkUICanvasModifierCompatible {
    void (*createCustomPaintComponent)(const std::string& content);
    void* (*createCanvasRenderingContextModel)(bool isOffscreen);
    void* (*createCanvasBridge)(CanvasBridgeParams& params);
};
} // namespace OHOS::Ace
#ifdef __cplusplus
};
#endif

#endif // FOUNDATION_ACE_FRAMEWORKS_COMPATIBLE_COMPONENTS_CANVAS_CANVAS_MODIFIER_COMPATIBLE_H