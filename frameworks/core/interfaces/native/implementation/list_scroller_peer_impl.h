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
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_LIST_SCROLLER_PEER_IMPL_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_LIST_SCROLLER_PEER_IMPL_H

#include "scroller_peer_impl.h"

struct ListScrollerPeer : public OHOS::Ace::NG::GeneratedModifier::ScrollerPeerImpl {
public:
    ListScrollerPeer() = default;
    ~ListScrollerPeer() override = default;

private:
    ACE_DISALLOW_COPY_AND_MOVE(ListScrollerPeer);
};

#endif //FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_LIST_SCROLLER_PEER_IMPL_H
