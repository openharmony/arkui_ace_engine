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

#include "frameworks/bridge/declarative_frontend/engine/jsi/utils/jsi_stage_utils.h"

#include <cstdint>

#include "base/log/log.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/stage/stage_manager.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::Framework {

namespace {
constexpr size_t SET_STAGE_RENDER_GROUP_PARAM_COUNT = 2;
} // namespace

panda::Local<panda::JSValueRef> JsSetStageRenderGroup(panda::JsiRuntimeCallInfo* info)
{
    // 1. Get VM instance
    auto* vm = info->GetVM();
    panda::EscapeLocalScope scope(vm);

    // 2. Validate parameter count
    if (info->GetArgsNumber() < SET_STAGE_RENDER_GROUP_PARAM_COUNT) {
        TAG_LOGE(AceLogTag::ACE_DEFAULT_DOMAIN,
            "JsSetStageRenderGroup failed: expected %{public}d parameters (instanceId, isRenderGroup), got %{public}d",
            static_cast<int32_t>(SET_STAGE_RENDER_GROUP_PARAM_COUNT), static_cast<int32_t>(info->GetArgsNumber()));
        return panda::JSValueRef::Undefined(vm);
    }

    // 3. Get instanceId parameter (first argument, number type)
    panda::Local<panda::JSValueRef> instanceIdArg = info->GetCallArgRef(0);
    if (instanceIdArg->IsUndefined() || instanceIdArg->IsNull()) {
        TAG_LOGE(AceLogTag::ACE_DEFAULT_DOMAIN,
            "JsSetStageRenderGroup failed: instanceId parameter is undefined or null");
        return panda::JSValueRef::Undefined(vm);
    }

    if (!instanceIdArg->IsNumber()) {
        TAG_LOGE(AceLogTag::ACE_DEFAULT_DOMAIN,
            "JsSetStageRenderGroup failed: instanceId parameter must be a number");
        return panda::JSValueRef::Undefined(vm);
    }

    int32_t instanceId = instanceIdArg->Int32Value(vm);

    // 4. Get isRenderGroup parameter (second argument, boolean type)
    panda::Local<panda::JSValueRef> renderGroupArg = info->GetCallArgRef(1);
    if (renderGroupArg->IsUndefined() || renderGroupArg->IsNull()) {
        TAG_LOGE(AceLogTag::ACE_DEFAULT_DOMAIN,
            "JsSetStageRenderGroup failed: isRenderGroup parameter is undefined or null");
        return panda::JSValueRef::Undefined(vm);
    }

    // 5. Convert to boolean value
    bool isRenderGroup = false;
    if (renderGroupArg->IsBoolean()) {
        isRenderGroup = renderGroupArg->ToBoolean(vm)->Value();
    } else if (renderGroupArg->IsNumber()) {
        // Support numeric type: 0 = false, non-zero = true
        isRenderGroup = renderGroupArg->Int32Value(vm) != 0;
    } else {
        TAG_LOGE(AceLogTag::ACE_DEFAULT_DOMAIN,
            "JsSetStageRenderGroup failed: isRenderGroup parameter must be a boolean or number");
        return panda::JSValueRef::Undefined(vm);
    }

    // 6. Get PipelineContext for the specified container by instanceId
    auto pipelineContext = NG::PipelineContext::GetContextByContainerId(instanceId);
    if (!pipelineContext) {
        TAG_LOGE(AceLogTag::ACE_DEFAULT_DOMAIN,
            "JsSetStageRenderGroup failed: no pipeline context for instanceId=%{public}d", instanceId);
        return panda::JSValueRef::Undefined(vm);
    }

    // 7. Get StageManager
    auto stageManager = pipelineContext->GetStageManager();
    if (!stageManager) {
        TAG_LOGE(AceLogTag::ACE_DEFAULT_DOMAIN,
            "JsSetStageRenderGroup failed: no stage manager");
        return panda::JSValueRef::Undefined(vm);
    }

    // 8. Get StageNode
    auto stageNode = stageManager->GetStageNode();
    if (!stageNode) {
        TAG_LOGE(AceLogTag::ACE_DEFAULT_DOMAIN,
            "JsSetStageRenderGroup failed: no stage node");
        return panda::JSValueRef::Undefined(vm);
    }

    // 9. Set RenderGroup
    stageNode->GetRenderContext()->UpdateRenderGroup(isRenderGroup);

    // 10. Log success
    TAG_LOGI(AceLogTag::ACE_DEFAULT_DOMAIN,
        "JsSetStageRenderGroup success: instanceId=%{public}d, isRenderGroup=%{public}s",
        instanceId, isRenderGroup ? "true" : "false");

    return panda::JSValueRef::Undefined(vm);
}

} // namespace OHOS::Ace::Framework
