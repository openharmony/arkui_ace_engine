/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/form_link/form_link_pattern.h"

#include "base/log/log_wrapper.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

void FormLinkPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_CONTENT);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->AddOnAreaChangeNode(GetHost()->GetId());
}

void FormLinkPattern::OnAreaChangedInner()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto linkRect = geometryNode->GetFrameRect();
    linkRect.SetOffset(GetHost()->GetTransformRelativeOffset());
    formLinkInfo_.SetFomLinkRect(linkRect);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->AddFormLinkInfo(host->GetId(), formLinkInfo_.ToString());
}

void FormLinkPattern::SetAction(const std::string& action)
{
    TAG_LOGI(AceLogTag::ACE_FORM, "SetAction:%{public}s", action.c_str());
    formLinkInfo_.SetAction(action);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->AddFormLinkInfo(host->GetId(), formLinkInfo_.ToString());
}

} // namespace OHOS::Ace::NG
