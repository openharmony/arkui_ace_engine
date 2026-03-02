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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_UTILS_JSI_STAGE_UTILS_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_UTILS_JSI_STAGE_UTILS_H

#include "jsnapi_expo.h"

namespace OHOS::Ace::Framework {

/**
 * @brief Set the RenderGroup property of the StageNode for a specified container instance
 * @param info JSI runtime call information
 * @return JSValueRef returns undefined
 *
 * Parameters (in order):
 * @param instanceId number type container instance ID
 *        - Used to specify the container instance to operate on
 *        - Get the container's PipelineContext via NG::PipelineContext::GetContextByContainerId(instanceId)
 *        - Get the StageNode via PipelineContext->GetStageManager()->GetStageNode()
 *
 * @param isRenderGroup bool type indicating whether to enable render group
 *        - true: Enable render group, the node will render independently as a render group
 *        - false: Disable render group, use default rendering method
 *        - Also supports number type (0 = false, non-zero = true)
 *
 * Description:
 * - RenderGroup is a performance optimization feature that controls whether a node acts as an independent render group
 * - Enabling render group can:
 *   - Create independent off-screen buffers
 *   - Optimize complex drawing operations
 *   - Support special visual effects (such as filters, blend modes)
 * - But may increase memory overhead
 */
panda::Local<panda::JSValueRef> JsSetStageRenderGroup(panda::JsiRuntimeCallInfo* info);

} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_UTILS_JSI_STAGE_UTILS_H
