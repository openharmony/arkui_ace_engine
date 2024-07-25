/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/node/drag_adapter_impl.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/interfaces/arkoala/arkoala_api.h"

namespace OHOS::Ace::DragAdapter {
namespace {

void SetDragPreview(ArkUINodeHandle node, void* dragPreview)
{
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::DragDropInfo dragPreviewInfo;
    dragPreviewInfo.pixelMap = PixelMap::CreatePixelMap(dragPreview);
    NG::ViewAbstract::SetDragPreview(frameNode, dragPreviewInfo);
}

void SetDragEventStrictReportingEnabledWithNode(bool enabled)
{
    NG::ViewAbstract::SetDragEventStrictReportingEnabled(enabled);
}

void SetDragEventStrictReportingEnabledWithContext(ArkUI_Int32 instanceId, bool enabled)
{
    NG::ViewAbstract::SetDragEventStrictReportingEnabled(instanceId, enabled);
}

} // namespace
const ArkUIDragAdapterAPI* GetDragAdapterAPI()
{
    static const ArkUIDragAdapterAPI impl {
        SetDragPreview,
        SetDragEventStrictReportingEnabledWithNode,
        SetDragEventStrictReportingEnabledWithContext
    };
    return &impl;
}
} // namespace OHOS::Ace::DragAdapter