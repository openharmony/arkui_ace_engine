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
#include "core/common/dynamic_module_helper.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/swiper_indicator/bridge/indicator_controller_modifier_api.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/indicator_controller.h"
#include "core/interfaces/native/utility/peer_utils.h"

struct IndicatorComponentControllerPeer : public virtual OHOS::Ace::AceType {
    DECLARE_ACE_TYPE(IndicatorComponentControllerPeer, OHOS::Ace::AceType);
public:
    void SetController(const OHOS::Ace::RefPtr<OHOS::Ace::NG::IndicatorController>& controller,
        OHOS::Ace::RefPtr<OHOS::Ace::NG::FrameNode>& indicatorNode)
    {
        auto modifier = GetIndicatorControllerModifier();
        CHECK_NULL_VOID(modifier);
        auto handle = GetControllerHandle(modifier);
        CHECK_NULL_VOID(handle);
        modifier->setController(handle, controller, indicatorNode);
    }

    std::function<void()> SetSwiperNodeBySwiper(const OHOS::Ace::RefPtr<OHOS::Ace::NG::FrameNode>& node)
    {
        auto modifier = GetIndicatorControllerModifier();
        CHECK_NULL_RETURN(modifier, nullptr);
        auto handle = GetControllerHandle(modifier);
        CHECK_NULL_RETURN(handle, nullptr);
        return modifier->setSwiperNodeBySwiper(handle, node);
    }

    void ShowNext()
    {
        auto modifier = GetIndicatorControllerModifier();
        CHECK_NULL_VOID(modifier);
        auto handle = GetControllerHandle(modifier);
        CHECK_NULL_VOID(handle);
        modifier->showNext(handle);
    }

    void ShowPrevious()
    {
        auto modifier = GetIndicatorControllerModifier();
        CHECK_NULL_VOID(modifier);
        auto handle = GetControllerHandle(modifier);
        CHECK_NULL_VOID(handle);
        modifier->showPrevious(handle);
    }

    void ChangeIndex(int32_t index, bool useAnimation)
    {
        auto modifier = GetIndicatorControllerModifier();
        CHECK_NULL_VOID(modifier);
        auto handle = GetControllerHandle(modifier);
        CHECK_NULL_VOID(handle);
        modifier->changeIndex(handle, index, useAnimation);
    }
protected:
    IndicatorComponentControllerPeer() {}
    friend OHOS::Ace::NG::PeerUtils;
    ~IndicatorComponentControllerPeer() override = default;

private:
    static const OHOS::Ace::NG::ArkUIIndicatorControllerModifier* GetIndicatorControllerModifier()
    {
        static const OHOS::Ace::NG::ArkUIIndicatorControllerModifier* cachedModifier = nullptr;
        if (cachedModifier == nullptr) {
            auto* module = OHOS::Ace::DynamicModuleHelper::GetInstance().GetDynamicModule("IndicatorComponent");
            CHECK_NULL_RETURN(module, nullptr);
            cachedModifier = reinterpret_cast<const OHOS::Ace::NG::ArkUIIndicatorControllerModifier*>(
                module->GetCustomModifier("indicator_controller"));
        }
        return cachedModifier;
    }

    OHOS::Ace::RefPtr<OHOS::Ace::AceType> GetControllerHandle(
        const OHOS::Ace::NG::ArkUIIndicatorControllerModifier* modifier)
    {
        CHECK_NULL_RETURN(modifier, nullptr);
        if (!controllerHandle_) {
            controllerHandle_ = modifier->createControllerHandle();
        }
        return controllerHandle_;
    }

    OHOS::Ace::RefPtr<OHOS::Ace::AceType> controllerHandle_;
};
// } // namespace OHOS::Ace::NG
