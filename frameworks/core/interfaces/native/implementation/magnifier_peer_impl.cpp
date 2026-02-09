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

#include "core/interfaces/native/implementation/magnifier_peer_impl.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/components_ng/base/inspector.h"

void MagnifierPeer::Bind(const std::string& id)
{
    auto pipelineContext = OHOS::Ace::NG::PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    auto controller = pipelineContext->GetMagnifierController();
    if (controller) {
        controller->UpdateShowMagnifier(false);
        controller->RemoveMagnifierFrameNode();
        pipelineContext->SetMagnifierController(nullptr);
    }
    auto frameNode = OHOS::Ace::NG::Inspector::GetFrameNodeByKey(id, false, true);
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    controller = MakeRefPtr<OHOS::Ace::NG::MagnifierController>(pattern);
    CHECK_NULL_VOID(controller);
    pipelineContext->SetMagnifierController(controller);
}

void MagnifierPeer::Show(const std::optional<float>& x, const std::optional<float>& y)
{
    auto pipelineContext = OHOS::Ace::NG::PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    auto controller = pipelineContext->GetMagnifierController();
    CHECK_NULL_VOID(controller);
    float dipScale = pipelineContext->GetDipScale();
    controller->SetLocalOffset(OHOS::Ace::NG::OffsetF(x.value() * dipScale, y.value() * dipScale));
}

void MagnifierPeer::Unbind()
{
    auto pipelineContext = OHOS::Ace::NG::PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    auto controller = pipelineContext->GetMagnifierController();
    CHECK_NULL_VOID(controller);
    controller->UpdateShowMagnifier(false);
    controller->RemoveMagnifierFrameNode();
    pipelineContext->SetMagnifierController(nullptr);
}