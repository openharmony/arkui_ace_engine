/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "frameworks/compatible/components/js_command.h"

#include "base/log/event_report.h"
#include "frameworks/bridge/js_frontend/js_ace_page.h"
#include "frameworks/compatible/components/canvas/dom_canvas.h"

namespace OHOS::Ace::Framework {
namespace {

inline RefPtr<DOMNode> GetNodeFromPage(const RefPtr<JsAcePage>& page, NodeId nodeId)
{
    auto domDocument = page ? page->GetDomDocument() : nullptr;
    if (domDocument) {
        return domDocument->GetDOMNodeById(nodeId);
    }
    LOGE("Failed to get DOM document");
    EventReport::SendJsException(JsExcepType::GET_NODE_ERR);
    return nullptr;
}
} // namespace

void JsCommandContextOperation::Execute(const RefPtr<JsAcePage>& page) const
{
    if (!task_) {
        return;
    }
    auto canvas = AceType::DynamicCast<DOMCanvas>(GetNodeFromPage(page, nodeId_));
    if (!canvas) {
        LOGE("Node %{private}d not exists or not a canvas", nodeId_);
        return;
    }
    auto paintChild = AceType::DynamicCast<CustomPaintComponent>(canvas->GetSpecializedComponent());
    ACE_DCHECK(paintChild);
    auto pool = paintChild->GetTaskPool();
    if (!pool) {
        LOGE("canvas get pool failed");
        return;
    }
    task_(pool);
}

} // namespace OHOS::Ace::Framework