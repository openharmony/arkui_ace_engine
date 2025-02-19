/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace GlobalScope_focusControl_commonAccessor {
void DestroyPeerImpl(Ark_GlobalScope_focusControl_common peer)
{
}
Ark_Boolean RequestFocusImpl(const Ark_String* value)
{
    bool result = false;
    CHECK_NULL_RETURN(value, Converter::ArkValue<Ark_Boolean>(result));
    std::string inspectorKey = Converter::Convert<std::string>(*value);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, Converter::ArkValue<Ark_Boolean>(result));
    if (!pipelineContext->GetTaskExecutor()) {
        return Converter::ArkValue<Ark_Boolean>(result);
    }
    pipelineContext->GetTaskExecutor()->PostSyncTask(
        [pipelineContext, inspectorKey, &result]() { result = pipelineContext->RequestFocus(inspectorKey); },
        TaskExecutor::TaskType::UI, "ArkUIJsRequestFocus");
    return Converter::ArkValue<Ark_Boolean>(result);
}
} // GlobalScope_focusControl_commonAccessor
const GENERATED_ArkUIGlobalScope_focusControl_commonAccessor* GetGlobalScope_focusControl_commonAccessor()
{
    static const GENERATED_ArkUIGlobalScope_focusControl_commonAccessor GlobalScope_focusControl_commonAccessorImpl {
        GlobalScope_focusControl_commonAccessor::DestroyPeerImpl,
        GlobalScope_focusControl_commonAccessor::RequestFocusImpl,
    };
    return &GlobalScope_focusControl_commonAccessorImpl;
}

struct GlobalScope_focusControl_commonPeer {
    virtual ~GlobalScope_focusControl_commonPeer() = default;
};
}
