/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_UI_SCROLLABLE_EVENT_PEER_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_UI_SCROLLABLE_EVENT_PEER_H

#include "arkoala_api_generated.h"
#include "ui_common_event_peer.h"
#include "core/interfaces/native/implementation/frame_node_peer_impl.h"
#include "core/interfaces/native/utility/peer_utils.h"

struct UIScrollableCommonEventPeer : public UICommonEventPeer {
protected:
    friend OHOS::Ace::NG::PeerUtils;
};

struct UIGridEventPeer : public UIScrollableCommonEventPeer {
};

struct UIListEventPeer : public UIScrollableCommonEventPeer {
};

struct UIScrollEventPeer : public UIScrollableCommonEventPeer {
};

struct UIWaterFlowEventPeer : public UIScrollableCommonEventPeer {
};
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_UI_SCROLLABLE_EVENT_PEER_H


