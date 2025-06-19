/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#pragma once

#include "core/components_ng/pattern/pattern.h"
#include "core/interfaces/native/implementation/event_target_info_peer.h"

namespace OHOS::Ace::NG::GeneratedModifier {
class ScrollableTargetInfoPeerImpl : public EventTargetInfoPeer {
    DECLARE_ACE_TYPE(ScrollableTargetInfoPeerImpl, EventTargetInfoPeer);
public:
    ScrollableTargetInfoPeerImpl() = default;
    ~ScrollableTargetInfoPeerImpl() override = default;

    void SetPattern(const WeakPtr<Pattern>& pattern)
    {
        pattern_ = pattern;
    }

    RefPtr<Pattern> GetPattern() const
    {
        return pattern_.Upgrade();
    }

private:
    WeakPtr<Pattern> pattern_;
};
} // namespace OHOS::Ace::NG::GeneratedModifier

struct ScrollableTargetInfoPeer : public OHOS::Ace::NG::GeneratedModifier::ScrollableTargetInfoPeerImpl {
    DECLARE_ACE_TYPE(ScrollableTargetInfoPeer, OHOS::Ace::NG::GeneratedModifier::ScrollableTargetInfoPeerImpl);
};
