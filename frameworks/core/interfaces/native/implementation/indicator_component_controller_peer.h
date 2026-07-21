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
#include "base/memory/ace_type.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/indicator_controller.h"
#include "core/interfaces/native/utility/peer_utils.h"

struct IndicatorComponentControllerPeer : public virtual OHOS::Ace::AceType {
    DECLARE_ACE_TYPE(IndicatorComponentControllerPeer, OHOS::Ace::AceType);
public:
    void SetController(const OHOS::Ace::RefPtr<OHOS::Ace::NG::IndicatorController>& controller,
        OHOS::Ace::RefPtr<OHOS::Ace::NG::FrameNode>& indicatorNode)
    {
        if (auto contr = controller_.Upgrade(); contr) {
            contr->ResetIndicatorControllor(controller, indicatorNode);
        }
        controller_ = controller;
        controller->SetSwiperNode(swiperNode_.Upgrade());
    }

    std::function<void()> SetSwiperNodeBySwiper(const OHOS::Ace::RefPtr<OHOS::Ace::NG::FrameNode>& node)
    {
        if (auto contr = controller_.Upgrade(); contr) {
            contr->SetSwiperNode(node);
        }
        if (node != swiperNode_) {
            swiperNode_ = node;
        }
        return nullptr;
    }

    void ShowNext()
    {
        if (auto contr = controller_.Upgrade(); contr) {
            contr->ShowNext();
        }
    }

    void ShowPrevious()
    {
        if (auto contr = controller_.Upgrade(); contr) {
            contr->ShowPrevious();
        }
    }

    void ChangeIndex(int32_t index, bool useAnimation)
    {
        if (auto contr = controller_.Upgrade(); contr) {
            contr->ChangeIndex(index, useAnimation);
        }
    }
protected:
    IndicatorComponentControllerPeer() {}
    friend OHOS::Ace::NG::PeerUtils;
    ~IndicatorComponentControllerPeer() override = default;

    OHOS::Ace::WeakPtr<OHOS::Ace::NG::IndicatorController> controller_;
    OHOS::Ace::WeakPtr<OHOS::Ace::NG::FrameNode> swiperNode_;
};
// } // namespace OHOS::Ace::NG