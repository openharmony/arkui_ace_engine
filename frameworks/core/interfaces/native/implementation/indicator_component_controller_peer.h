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

#pragma once

#include "arkoala_api_generated.h"
#include "base/image/pixel_map.h"
#include "base/memory/ace_type.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/indicator_controller.h"
#include "core/interfaces/native/utility/peer_utils.h"

struct IndicatorComponentControllerPeer : public virtual OHOS::Ace::AceType {
    DECLARE_ACE_TYPE(IndicatorComponentControllerPeer, OHOS::Ace::AceType);
public:
    std::function<void()> SetSwiperNodeBySwiper(const OHOS::Ace::RefPtr<OHOS::Ace::NG::FrameNode>& node)
    {
        LOGE("IndicatorComponentControllerPeer::SetSwiperNodeBySwiper is not implemented");
        return nullptr;
    }
protected:
    IndicatorComponentControllerPeer() {}
    friend OHOS::Ace::NG::PeerUtils;
    ~IndicatorComponentControllerPeer() override = default;
};
