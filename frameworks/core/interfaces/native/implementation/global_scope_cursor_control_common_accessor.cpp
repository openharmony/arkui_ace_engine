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
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace GlobalScope_cursorControl_commonAccessor {
void DestroyPeerImpl(Ark_GlobalScope_cursorControl_common peer)
{
}
void SetCursorImpl(Ark_PointerStyle value)
{
    int32_t intValue = static_cast<int32_t>(value);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    if (!pipelineContext->GetTaskExecutor()) {
        return;
    }
    pipelineContext->GetTaskExecutor()->PostSyncTask(
        [pipelineContext, intValue]() { pipelineContext->SetCursor(intValue); },
        TaskExecutor::TaskType::UI, "ArkUIJsSetCursor");
}
void RestoreDefaultImpl()
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    if (!pipelineContext->GetTaskExecutor()) {
        return;
    }
    pipelineContext->GetTaskExecutor()->PostSyncTask(
        [pipelineContext]() { pipelineContext->RestoreDefault(); },
        TaskExecutor::TaskType::UI, "ArkUIJsRestoreDefault");
}
} // GlobalScope_cursorControl_commonAccessor
const GENERATED_ArkUIGlobalScope_cursorControl_commonAccessor* GetGlobalScope_cursorControl_commonAccessor()
{
    static const GENERATED_ArkUIGlobalScope_cursorControl_commonAccessor GlobalScope_cursorControl_commonAccessorImpl {
        GlobalScope_cursorControl_commonAccessor::DestroyPeerImpl,
        GlobalScope_cursorControl_commonAccessor::SetCursorImpl,
        GlobalScope_cursorControl_commonAccessor::RestoreDefaultImpl,
    };
    return &GlobalScope_cursorControl_commonAccessorImpl;
}

struct GlobalScope_cursorControl_commonPeer {
    virtual ~GlobalScope_cursorControl_commonPeer() = default;
};
}
