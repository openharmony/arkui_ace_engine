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

#include "core/interfaces/native/node/node_api.h"

#include <array>
#include <deque>

#include "base/log/log_wrapper.h"
#include "base/utils/macros.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/interfaces/native/node/node_scroll_modifier.h"
#include "core/interfaces/native/node/node_text_input_modifier.h"
#include "core/interfaces/native/node/view_model.h"

namespace OHOS::Ace::NG {

namespace NodeEvent {
std::deque<ArkUINodeEvent> g_eventQueue;
int CheckEvent(ArkUINodeEvent* event)
{
    if (!g_eventQueue.empty()) {
        *event = g_eventQueue.front();
        g_eventQueue.pop_front();
        return 1;
    }
    return 0;
}

void (*g_fliter)(ArkUINodeEvent* event) = nullptr;
void SendArkUIAsyncEvent(ArkUINodeEvent* event)
{
    if (g_fliter) {
        g_fliter(event);
    } else {
        g_eventQueue.push_back(*event);
    }
}
} // namespace NodeEvent

namespace {

ArkUINodeHandle CreateNode(ArkUINodeType type, int peerId, ArkUI_Int32 /*flags*/)
{
    return ViewModel::CreateNode(type, peerId);
}

void DisposeNode(ArkUINodeHandle node)
{
    ViewModel::DisposeNode(node);
}

void AddChild(ArkUINodeHandle parent, ArkUINodeHandle child)
{
    ViewModel::AddChild(parent, child);
}

void RemoveChild(ArkUINodeHandle parent, ArkUINodeHandle child)
{
    ViewModel::RemoveChild(parent, child);
}

void InsertChildAfter(ArkUINodeHandle parent, ArkUINodeHandle child, ArkUINodeHandle sibling)
{
    ViewModel::InsertChildAfter(parent, child, sibling);
}

typedef void (*ComponentAsyncEventHandler)(ArkUINodeHandle node, ArkUI_Int32 eventId);

/**
 * IMPORTANT!!!
 * the order of declaring the handler must be same as the ArkUIAPIComponentAsyncEventSubKind did
 */
/* clang-format off */
const ComponentAsyncEventHandler commonNodeAsyncEventHandlers[] = {
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
};

const ComponentAsyncEventHandler scrollNodeAsyncEventHandlers[] = {
    NodeModifier::SetOnScroll,
    NodeModifier::SetOnScrollFrameBegin,
    NodeModifier::SetOnScrollStart,
    NodeModifier::SetOnScrollStop
};

const ComponentAsyncEventHandler textInputNodeAsyncEventHandlers[] = {
    nullptr,
    nullptr,
    NodeModifier::SetOnTextInputChange,
};

/* clang-format on */
void NotifyComponentAsyncEvent(ArkUINodeHandle node, ArkUIAsyncEventKind kind, ArkUI_Int32 eventId)
{
    unsigned int subClassType = kind / ARKUI_MAX_EVENT_NUM;
    unsigned int subKind = kind % ARKUI_MAX_EVENT_NUM;
    ComponentAsyncEventHandler eventHandle = nullptr;
    switch (subClassType) {
        case 0: {
            // common event type.
            if (subKind >= sizeof(commonNodeAsyncEventHandlers) / sizeof(ComponentAsyncEventHandler)) {
                TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "NotifyComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
                return;
            }
            eventHandle = commonNodeAsyncEventHandlers[subKind];
            break;
        }
        case ARKUI_SCROLL: {
            // scroll event type.
            if (subKind >= sizeof(scrollNodeAsyncEventHandlers) / sizeof(ComponentAsyncEventHandler)) {
                TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "NotifyComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
                return;
            }
            eventHandle = scrollNodeAsyncEventHandlers[subKind];
            break;
        }
        case ARKUI_TEXTINPUT: {
            // textinput event type.
            if (subKind >= sizeof(textInputNodeAsyncEventHandlers) / sizeof(ComponentAsyncEventHandler)) {
                TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "NotifyComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
                return;
            }
            eventHandle = textInputNodeAsyncEventHandlers[subKind];
            break;
        }
        default: {
            TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "NotifyComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
        }
    }
    if (eventHandle) {
        eventHandle(node, eventId);
    } else {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "NotifyComponentAsyncEvent kind:%{public}d EMPTY IMPLEMENT", kind);
    }
}

void NotifyResetComponentAsyncEvent(ArkUINodeHandle node, ArkUIAsyncEventKind subKind)
{
    // TODO
}

void RegisterNodeAsyncEventReceiver(void (*eventReceiver)(ArkUINodeEvent* event))
{
    NodeEvent::g_fliter = eventReceiver;
}

void ApplyModifierFinish(ArkUINodeHandle nodePtr)
{
    auto* uiNode = reinterpret_cast<UINode*>(nodePtr);
    auto* frameNode = AceType::DynamicCast<FrameNode>(uiNode);
    if (frameNode) {
        frameNode->MarkModifyDone();
    }
}

/* clang-format off */
const struct ArkUIBasicAPI basicImpl = {
    CreateNode,
    DisposeNode,
    nullptr,
    nullptr,
    AddChild,
    RemoveChild,
    InsertChildAfter,
    nullptr,
    nullptr,
    nullptr,
    NotifyComponentAsyncEvent,
    NotifyResetComponentAsyncEvent,
    RegisterNodeAsyncEventReceiver,
    nullptr,
    nullptr,
    ApplyModifierFinish,
    nullptr,
};
/* clang-format on */

const ArkUIBasicAPI* GetBasicAPI()
{
    return &basicImpl;
}

/* clang-format off */
ArkUIFullNodeAPI impl = {
    ARKUI_NODE_API_VERSION,
    GetBasicAPI,
    GetArkUINodeModifiers,
    nullptr,
};
/* clang-format on */
} // namespace

} // namespace OHOS::Ace::NG

extern "C" {
ACE_FORCE_EXPORT ArkUIAnyNodeAPI* GetArkUIAnyFullNodeAPI(int version)
{
    switch (version) {
        case ARKUI_NODE_API_VERSION:
            return reinterpret_cast<ArkUIAnyNodeAPI*>(&OHOS::Ace::NG::impl);
        default: {
            TAG_LOGE(OHOS::Ace::AceLogTag::ACE_NATIVE_NODE,
                "Requested version %{public}d is not supported, we're version %{public}d", version,
                ARKUI_NODE_API_VERSION);
            return nullptr;
        }
    }
}

const ArkUIFullNodeAPI* GetArkUIFullNodeAPI()
{
    return &OHOS::Ace::NG::impl;
}

void SendArkUIAsyncEvent(ArkUINodeEvent* event)
{
    OHOS::Ace::NG::NodeEvent::SendArkUIAsyncEvent(event);
}
}
