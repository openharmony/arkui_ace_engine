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

#include "arkoala_api_generated.h"
#include "base/memory/ace_type.h"
#include "core/components/common/properties/paint_state.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/inspector.h"
#include "core/components_ng/pattern/select_overlay/magnifier_controller.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/pipeline/pipeline_base.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace MagnifierExtenderAccessor {
void BindImpl(const Ark_String* id)
{
    auto pipelineContext = OHOS::Ace::NG::PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    auto controller = pipelineContext->GetMagnifierController();
    if (controller) {
        controller->UpdateShowMagnifier(false);
        controller->RemoveMagnifierFrameNode();
        pipelineContext->SetMagnifierController(nullptr);
    }
    auto idStr = Converter::Convert<std::string>(*id);
    auto frameNode = OHOS::Ace::NG::Inspector::GetFrameNodeByKey(idStr, false, true);
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    controller = AceType::MakeRefPtr<OHOS::Ace::NG::MagnifierController>(pattern);
    CHECK_NULL_VOID(controller);
    pipelineContext->SetMagnifierController(controller);
}
void ShowImpl(Ark_Float64 x,
              Ark_Float64 y)
{
    auto pipelineContext = OHOS::Ace::NG::PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    auto controller = pipelineContext->GetMagnifierController();
    CHECK_NULL_VOID(controller);
    float dipScale = pipelineContext->GetDipScale();
    auto optX = Converter::OptConvert<float>(x);
    auto optY = Converter::OptConvert<float>(y);
    controller->SetLocalOffset(OHOS::Ace::NG::OffsetF(optX.value() * dipScale, optY.value() * dipScale));
}
void UnbindImpl()
{
    auto pipelineContext = OHOS::Ace::NG::PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    auto controller = pipelineContext->GetMagnifierController();
    CHECK_NULL_VOID(controller);
    controller->UpdateShowMagnifier(false);
    controller->RemoveMagnifierFrameNode();
    pipelineContext->SetMagnifierController(nullptr);
}
} // MagnifierExtenderAccessor
const GENERATED_ArkUIMagnifierExtenderAccessor* GetMagnifierExtenderAccessor()
{
    static const GENERATED_ArkUIMagnifierExtenderAccessor MagnifierExtenderAccessorImpl {
        MagnifierExtenderAccessor::BindImpl,
        MagnifierExtenderAccessor::ShowImpl,
        MagnifierExtenderAccessor::UnbindImpl,
    };
    return &MagnifierExtenderAccessorImpl;
}

}