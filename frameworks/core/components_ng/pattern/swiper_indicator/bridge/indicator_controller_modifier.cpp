/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/swiper_indicator/bridge/indicator_controller_modifier_api.h"

#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/indicator_controller.h"

namespace OHOS::Ace::NG {
namespace {
class IndicatorControllerHandle : public JSIndicatorControllerBase {
    DECLARE_ACE_TYPE(IndicatorControllerHandle, JSIndicatorControllerBase);

public:
    void SetController(const RefPtr<IndicatorController>& controller, const RefPtr<FrameNode>& indicatorNode)
    {
        auto resetFunc = [weak = WeakClaim(this), weakNode = WeakPtr<FrameNode>(indicatorNode)]() {
            auto handle = weak.Upgrade();
            CHECK_NULL_VOID(handle);
            auto controller = handle->controller_.Upgrade();
            CHECK_NULL_VOID(controller);
            auto host = controller->GetIndicatorNode();
            auto node = weakNode.Upgrade();
            if (node && node == host) {
                handle->controller_ = nullptr;
            }
        };
        if (controller_.Upgrade()) {
            controller_.Upgrade()->ResetIndicatorControllor(controller, indicatorNode);
        }
        controller_ = controller;
        controller->SetJSIndicatorController(resetFunc);
        controller->SetSwiperNode(swiperNode_.Upgrade());
    }

    void ShowNext()
    {
        auto controller = controller_.Upgrade();
        CHECK_NULL_VOID(controller);
        controller->ShowNext();
    }

    void ShowPrevious()
    {
        auto controller = controller_.Upgrade();
        CHECK_NULL_VOID(controller);
        controller->ShowPrevious();
    }

    void ChangeIndex(int32_t index, bool useAnimation)
    {
        auto controller = controller_.Upgrade();
        CHECK_NULL_VOID(controller);
        controller->ChangeIndex(index, useAnimation);
    }

    void ResetSwiperNode()
    {
        swiperNode_ = nullptr;
    }

    std::function<void()> SetSwiperNodeBySwiper(const RefPtr<FrameNode>& node)
    {
        if (controller_.Upgrade()) {
            controller_.Upgrade()->SetSwiperNode(node);
            controller_.Upgrade()->UpdateIndicatorNode();
        }
        if (node != swiperNode_) {
            swiperNode_ = node;
            return [weak = WeakClaim(this), weakNode = WeakPtr<FrameNode>(node)]() {
                auto handle = weak.Upgrade();
                CHECK_NULL_VOID(handle);
                auto node = weakNode.Upgrade();
                if (node && node == handle->swiperNode_) {
                    handle->swiperNode_ = nullptr;
                }
                auto controller = handle->controller_.Upgrade();
                CHECK_NULL_VOID(controller);
                controller->UpdateIndicatorNode();
            };
        }
        return nullptr;
    }

private:
    WeakPtr<IndicatorController> controller_;
    WeakPtr<FrameNode> swiperNode_;
};

IndicatorControllerHandle* ToIndicatorHandle(const RefPtr<AceType>& handle)
{
    auto indicatorHandle = AceType::DynamicCast<IndicatorControllerHandle>(handle);
    return AceType::RawPtr(indicatorHandle);
}

RefPtr<AceType> CreateControllerHandleImpl()
{
    return AceType::MakeRefPtr<IndicatorControllerHandle>();
}

void SetControllerImpl(
    const RefPtr<AceType>& handle, const RefPtr<AceType>& controller, const RefPtr<AceType>& indicatorNode)
{
    auto* indicatorHandle = ToIndicatorHandle(handle);
    CHECK_NULL_VOID(indicatorHandle);
    auto indicatorController = AceType::DynamicCast<IndicatorController>(controller);
    auto frameNode = AceType::DynamicCast<FrameNode>(indicatorNode);
    CHECK_NULL_VOID(indicatorController);
    CHECK_NULL_VOID(frameNode);
    indicatorHandle->SetController(indicatorController, frameNode);
}

void ShowNextImpl(const RefPtr<AceType>& handle)
{
    auto* indicatorHandle = ToIndicatorHandle(handle);
    CHECK_NULL_VOID(indicatorHandle);
    indicatorHandle->ShowNext();
}

void ShowPreviousImpl(const RefPtr<AceType>& handle)
{
    auto* indicatorHandle = ToIndicatorHandle(handle);
    CHECK_NULL_VOID(indicatorHandle);
    indicatorHandle->ShowPrevious();
}

void ChangeIndexImpl(const RefPtr<AceType>& handle, int32_t index, bool useAnimation)
{
    auto* indicatorHandle = ToIndicatorHandle(handle);
    CHECK_NULL_VOID(indicatorHandle);
    indicatorHandle->ChangeIndex(index, useAnimation);
}

void ResetSwiperNodeImpl(const RefPtr<AceType>& handle)
{
    auto* indicatorHandle = ToIndicatorHandle(handle);
    CHECK_NULL_VOID(indicatorHandle);
    indicatorHandle->ResetSwiperNode();
}

std::function<void()> SetSwiperNodeBySwiperImpl(const RefPtr<AceType>& handle, const RefPtr<AceType>& node)
{
    auto* indicatorHandle = ToIndicatorHandle(handle);
    CHECK_NULL_RETURN(indicatorHandle, nullptr);
    auto frameNode = AceType::DynamicCast<FrameNode>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    return indicatorHandle->SetSwiperNodeBySwiper(frameNode);
}

RefPtr<AceType> GetControllerBaseImpl(const RefPtr<AceType>& handle)
{
    return AceType::DynamicCast<JSIndicatorControllerBase>(handle);
}
} // namespace

const ArkUIIndicatorControllerModifier* GetIndicatorControllerModifier()
{
    static const ArkUIIndicatorControllerModifier modifier = {
        .createControllerHandle = CreateControllerHandleImpl,
        .setController = SetControllerImpl,
        .showNext = ShowNextImpl,
        .showPrevious = ShowPreviousImpl,
        .changeIndex = ChangeIndexImpl,
        .resetSwiperNode = ResetSwiperNodeImpl,
        .setSwiperNodeBySwiper = SetSwiperNodeBySwiperImpl,
        .getControllerBase = GetControllerBaseImpl,
    };
    return &modifier;
}
} // namespace OHOS::Ace::NG
