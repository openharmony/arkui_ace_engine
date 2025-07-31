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

#include "core/components_ng/pattern/ui_extension/dynamic_component/arkts_dynamic_pattern.h"

#include "adapter/ohos/entrance/ace_container.h"
#include "base/log/dump_log.h"
#include "base/log/log_wrapper.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "parameters.h"

namespace OHOS::Ace::NG {
namespace {
const char ENABLE_DEBUG_DC_KEY[] = "persist.ace.debug.dc.enabled";

bool IsDebugDCEnabled()
{
    return OHOS::system::GetParameter(ENABLE_DEBUG_DC_KEY, "false") == "true";
}
}

ArktsDynamicPattern::ArktsDynamicPattern()
    : DynamicPattern()
{
    PLATFORM_LOGI("The ArktsDynamicPattern is created.");
}

ArktsDynamicPattern::~ArktsDynamicPattern()
{
    DynamicPattern::~DynamicPattern();
    PLATFORM_LOGI("The ArktsDynamicPattern is destroyed.");
}

void ArktsDynamicPattern::InitializeDynamicComponent()
{
    IsDebugDCEnabled();
    if (dynamicComponentRenderer_ != nullptr) {
        PLATFORM_LOGI("dynamicComponentRenderer has create.");
        return;
    }

    if (param_.entryPoint.empty() || param_.workerId <= 0) {
        PLATFORM_LOGE("The param empty.");
        HandleErrorCallback(DCResultCode::DC_PARAM_ERROE);
        return;
    }

#if defined(PREVIEW)
    PLATFORM_LOGE("DynamicComponent not support preview.");
#else
    InitializeArktsDcRender();
#endif
}

bool ArktsDynamicPattern::CheckDynamicRendererConstraint(int32_t workerId)
{
    CHECK_NULL_RETURN(dynamicComponentRenderer_, false);
    if (dynamicComponentRenderer_->HasWorkerUsingByWorkerId(workerId)) {
        HandleErrorCallback(DCResultCode::DC_WORKER_HAS_USED_ERROR);
        return false;
    }

    return true;
}

void ArktsDynamicPattern::InitializeArktsDcRender()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    dynamicDumpInfo_.createLimitedWorkerTime = GetCurrentTimestamp();
    auto code = CheckConstraint();
    if (code != DCResultCode::DC_NO_ERRORS) {
        HandleErrorCallback(code);
        PLATFORM_LOGE("CheckConstraint faield, code: %{public}d.", code);
        return;
    }

    ContainerScope scope(instanceId_);
    SetHostNode(host);
    dynamicComponentRenderer_ =
        DynamicComponentRenderer::Create(GetHost(), param_);
    if (!CheckDynamicRendererConstraint(param_.workerId)) {
        return;
    }

    dynamicComponentRenderer_->SetUIContentType(UIContentType::DYNAMIC_COMPONENT);
    dynamicComponentRenderer_->SetAdaptiveSize(adaptiveWidth_, adaptiveHeight_);
    dynamicComponentRenderer_->SetBackgroundTransparent(backgroundTransparent_);
    dynamicComponentRenderer_->CreateContent();
    accessibilitySessionAdapter_ =
        AceType::MakeRefPtr<AccessibilitySessionAdapterIsolatedComponent>(dynamicComponentRenderer_);
    SetContainerHostPattern(WeakClaim(this));
    auto eventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    OnAreaChangedFunc onAreaChangedFunc = [renderer = dynamicComponentRenderer_](
        const RectF& oldRect,
        const OffsetF& oldOrigin,
        const RectF& rect,
        const OffsetF& origin) {
            CHECK_NULL_VOID(renderer);
            renderer->UpdateParentOffsetToWindow(origin + rect.GetOffset());
    };
    eventHub->AddInnerOnAreaChangedCallback(host->GetId(), std::move(onAreaChangedFunc));
}

void ArktsDynamicPattern::OnAttachContext(PipelineContext *context)
{
    DynamicPattern::OnAttachContext(context);
    InitializeDynamicComponent();
}

void ArktsDynamicPattern::OnDetachContext(PipelineContext *context)
{
    DynamicPattern::OnDetachContext(context);
}

void ArktsDynamicPattern::SetDynamicParam(const DynamicParam& param)
{
    param_ = param;
    PLATFORM_LOGI("ArktsDynamicPattern DynamicParam: %{public}s", param_.ToString().c_str());
}
} // namespace OHOS::Ace::NG
