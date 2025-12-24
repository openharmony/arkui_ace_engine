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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_JSI_IMAGE_GENERATOR_DIALOG_VIEW_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_JSI_IMAGE_GENERATOR_DIALOG_VIEW_H

#include <cstdint>

namespace OHOS::Ace::Framework {
class ImageGeneratorDialogView {
public:
    static bool Create(int32_t instanceId);
    static bool ExecuteImageGeneratorDialogAbc(int32_t instanceId);
    static void MinimizeDialog(int32_t instanceId, int32_t uniqueId);
    static void RecoverDialog(int32_t instanceId, int32_t uniqueId);
};
} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_JSI_IMAGE_GENERATOR_DIALOG_VIEW_H
