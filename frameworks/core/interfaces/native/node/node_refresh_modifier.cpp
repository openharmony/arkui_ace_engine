/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/node/node_refresh_modifier.h"

#include "base/geometry/dimension.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/pipeline/base/element_register.h"
#include "bridge/common/utils/utils.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components/common/properties/alignment.h"
#include "core/interfaces/native/node/node_api.h"
#include "core/components_ng/pattern/refresh/refresh_model_ng.h"

namespace OHOS::Ace::NG {

namespace NodeModifier {

void SetRefreshOnStateChange(ArkUINodeHandle node, ArkUI_Int32 eventId) 
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [node, eventId](const int32_t value) {
        ArkUINodeEvent event;
        event.kind = ON_REFRESH_STATE_CHANGE;
        event.eventId = eventId;
        event.componentAsyncEvent.data[0].i32 = value;
        SendArkUIAsyncEvent(&event);
    };
    RefreshModelNG::SetOnStateChange(frameNode, std::move(onEvent));
}

void SetOnRefreshing(ArkUINodeHandle node, ArkUI_Int32 eventId)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [node, eventId]() {
        ArkUINodeEvent event;
        event.kind = ON_REFRESH_REFRESHING;
        event.eventId = eventId;
        SendArkUIAsyncEvent(&event);
    };
    RefreshModelNG::SetOnRefreshing(frameNode, std::move(onEvent));
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG