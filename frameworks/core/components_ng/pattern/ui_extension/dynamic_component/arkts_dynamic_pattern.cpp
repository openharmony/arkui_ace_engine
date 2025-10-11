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

ArktsDynamicPattern::ArktsDynamicPattern()
    : DynamicPattern()
{
    PLATFORM_LOGI("The ArktsDynamicPattern is created.");
}

ArktsDynamicPattern::~ArktsDynamicPattern()
{
    UIExtensionIdUtility::GetInstance().RecycleExtensionId(uiExtensionId_);
    PLATFORM_LOGI("The ArktsDynamicPattern is destroyed.");
}

void ArktsDynamicPattern::InitializeDynamicComponent()
{
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
    if (!dynamicComponentRenderer_->CheckDCMaxConstraintInWorker(workerId)) {
        HandleErrorCallback(DCResultCode::DC_EXCEED_MAX_NUM_IN_WORKER);
        return false;
    }

    if (!dynamicComponentRenderer_->CheckWorkerMaxConstraint(workerId)) {
        HandleErrorCallback(DCResultCode::DC_WORKER_EXCEED_MAX_NUM);
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

void ArktsDynamicPattern::DumpInfo()
{
    DumpLog::GetInstance().AddDesc(std::string("dynamicId: ").append(std::to_string(platformId_)));
    DumpLog::GetInstance().AddDesc(std::string("workerId: ")
        .append(std::to_string(param_.workerId)));
    DumpLog::GetInstance().AddDesc(std::string("entryPoint: ").append(param_.entryPoint));
    DumpLog::GetInstance().AddDesc(std::string("backgroundTransparent: ")
        .append(std::to_string(param_.backgroundTransparent)));

    CHECK_NULL_VOID(dynamicComponentRenderer_);
    RendererDumpInfo rendererDumpInfo;
    dynamicComponentRenderer_->Dump(rendererDumpInfo);
    std::string isReportFrameEvent = hostConfig_.isReportFrameEvent ? "true" : "false";
    DumpLog::GetInstance().AddDesc(std::string("isReportFrameEvent: ")
        .append(isReportFrameEvent));
}

void ArktsDynamicPattern::DumpInfo(std::unique_ptr<JsonValue>& json)
{
    json->Put("dynamicId", platformId_);
    json->Put("workerId", std::to_string(param_.workerId).c_str());
    json->Put("entryPoint", param_.entryPoint.c_str());
    json->Put("backgroundTransparent", std::to_string(param_.backgroundTransparent).c_str());

    CHECK_NULL_VOID(dynamicComponentRenderer_);
    RendererDumpInfo rendererDumpInfo;
    dynamicComponentRenderer_->Dump(rendererDumpInfo);
    std::string isReportFrameEvent = hostConfig_.isReportFrameEvent ? "true" : "false";
    json->Put("isReportFrameEvent", isReportFrameEvent.c_str());
}

void ArktsDynamicPattern::SetDynamicParam(const DynamicParam& param)
{
    param_ = param;
    PLATFORM_LOGI("ArktsDynamicPattern DynamicParam: %{public}s", param_.ToString().c_str());
    SetBackgroundTransparent(param_.backgroundTransparent);
}
} // namespace OHOS::Ace::NG
