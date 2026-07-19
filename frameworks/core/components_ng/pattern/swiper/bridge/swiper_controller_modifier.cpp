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

#include "core/components_ng/pattern/swiper/bridge/swiper_controller_modifier_api.h"
#include "core/components_ng/pattern/swiper/bridge/swiper_transition_proxy_modifier_api.h"

#include <set>
#include <vector>

#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components/swiper/swiper_controller.h"
#include "core/components_ng/pattern/swiper/swiper_content_transition_proxy.h"
#include "core/interfaces/cjui/cjui_api.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#include "core/components_ng/pattern/swiper/swiper_model_ng.h"

namespace OHOS::Ace {
namespace {
constexpr int32_t DEFAULT_ANIMATION_MODE = 0;
const std::vector<SwiperAnimationMode> SWIPER_ANIMATION_MODE = { SwiperAnimationMode::NO_ANIMATION,
    SwiperAnimationMode::DEFAULT_ANIMATION, SwiperAnimationMode::FAST_ANIMATION };

SwiperController* ToSwiperController(const RefPtr<AceType>& controller)
{
    auto swiperController = AceType::DynamicCast<SwiperController>(controller);
    return AceType::RawPtr(swiperController);
}

void SwipeToModifierImpl(const RefPtr<AceType>& controller, int32_t index)
{
    auto* swiperController = ToSwiperController(controller);
    CHECK_NULL_VOID(swiperController);
    swiperController->SwipeTo(index);
}

void ShowNextImpl(const RefPtr<AceType>& controller)
{
    auto* swiperController = ToSwiperController(controller);
    CHECK_NULL_VOID(swiperController);
    swiperController->ShowNext();
}

void ShowPreviousImpl(const RefPtr<AceType>& controller)
{
    auto* swiperController = ToSwiperController(controller);
    CHECK_NULL_VOID(swiperController);
    swiperController->ShowPrevious();
}

void ChangeIndexModifierImpl(const RefPtr<AceType>& controller, int32_t index, bool useAnimation)
{
    auto* swiperController = ToSwiperController(controller);
    CHECK_NULL_VOID(swiperController);
    swiperController->ChangeIndex(index, useAnimation);
}

void ChangeIndexWithModeModifierImpl(const RefPtr<AceType>& controller, int32_t index, int32_t animationMode)
{
    auto* swiperController = ToSwiperController(controller);
    CHECK_NULL_VOID(swiperController);
    if (animationMode < 0 || animationMode >= static_cast<int32_t>(SWIPER_ANIMATION_MODE.size())) {
        animationMode = DEFAULT_ANIMATION_MODE;
    }
    swiperController->ChangeIndex(index, SWIPER_ANIMATION_MODE[animationMode]);
}

void SetFinishCallbackImpl(const RefPtr<AceType>& controller, const std::function<void()>& callback)
{
    auto* swiperController = ToSwiperController(controller);
    CHECK_NULL_VOID(swiperController);
    swiperController->SetFinishCallback(callback);
}

void FinishAnimationImpl(const RefPtr<AceType>& controller)
{
    auto* swiperController = ToSwiperController(controller);
    CHECK_NULL_VOID(swiperController);
    swiperController->FinishAnimation();
}

void PreloadItemsModifierImpl(const RefPtr<AceType>& controller, const int32_t* indices, int32_t count)
{
    auto* swiperController = ToSwiperController(controller);
    CHECK_NULL_VOID(swiperController);
    std::set<int32_t> indexSet;
    if (indices) {
        for (int32_t i = 0; i < count; ++i) {
            indexSet.emplace(indices[i]);
        }
    }
    swiperController->PreloadItems(indexSet);
}

void SetPreloadFinishCallbackImpl(
    const RefPtr<AceType>& controller, const std::function<void(int32_t, std::string)>& callback)
{
    auto* swiperController = ToSwiperController(controller);
    CHECK_NULL_VOID(swiperController);
    swiperController->SetPreloadFinishCallback(callback);
}

bool StartFakeDragImpl(const RefPtr<AceType>& controller)
{
    auto* swiperController = ToSwiperController(controller);
    CHECK_NULL_RETURN(swiperController, false);
    return swiperController->StartFakeDrag();
}

bool FakeDragByImpl(const RefPtr<AceType>& controller, float offset)
{
    auto* swiperController = ToSwiperController(controller);
    CHECK_NULL_RETURN(swiperController, false);
    return swiperController->FakeDragBy(offset);
}

bool StopFakeDragImpl(const RefPtr<AceType>& controller)
{
    auto* swiperController = ToSwiperController(controller);
    CHECK_NULL_RETURN(swiperController, false);
    return swiperController->StopFakeDrag();
}

bool IsFakeDraggingImpl(const RefPtr<AceType>& controller)
{
    auto* swiperController = ToSwiperController(controller);
    CHECK_NULL_RETURN(swiperController, false);
    return swiperController->IsFakeDragging();
}

int32_t GetSelectedIndexImpl(const RefPtr<AceType>& proxy)
{
    auto swiperProxy = AceType::DynamicCast<SwiperContentTransitionProxy>(proxy);
    return swiperProxy ? swiperProxy->GetSelectedIndex() : 0;
}

int32_t GetIndexImpl(const RefPtr<AceType>& proxy)
{
    auto swiperProxy = AceType::DynamicCast<SwiperContentTransitionProxy>(proxy);
    return swiperProxy ? swiperProxy->GetIndex() : 0;
}

float GetPositionImpl(const RefPtr<AceType>& proxy)
{
    auto swiperProxy = AceType::DynamicCast<SwiperContentTransitionProxy>(proxy);
    return swiperProxy ? swiperProxy->GetPosition() : 0.0f;
}

float GetMainAxisLengthImpl(const RefPtr<AceType>& proxy)
{
    auto swiperProxy = AceType::DynamicCast<SwiperContentTransitionProxy>(proxy);
    return swiperProxy ? swiperProxy->GetMainAxisLength() : 0.0f;
}

void FinishTransitionImpl(const RefPtr<AceType>& proxy)
{
    auto swiperProxy = AceType::DynamicCast<SwiperContentTransitionProxy>(proxy);
    CHECK_NULL_VOID(swiperProxy);
    swiperProxy->FinishTransition();
}

ArkUINodeHandle GetSwiperController(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto controller = NG::SwiperModelNG::GetOrCreateSwiperController(frameNode);
    return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(controller));
}

void ShowNext(ArkUINodeHandle controller)
{
    CHECK_NULL_VOID(controller);
    auto* swiperController = reinterpret_cast<SwiperController*>(controller);
    swiperController->ShowNext();
}

void ShowPrevious(ArkUINodeHandle controller)
{
    CHECK_NULL_VOID(controller);
    auto* swiperController = reinterpret_cast<SwiperController*>(controller);
    swiperController->ShowPrevious();
}
} // namespace

namespace NG::NodeModifier {
const ArkUICustomSwiperControllerModifier* GetCustomSwiperControllerModifier()
{
    static const ArkUICustomSwiperControllerModifier modifier = {
        .swipeTo = SwipeToModifierImpl,
        .showNext = ShowNextImpl,
        .showPrevious = ShowPreviousImpl,
        .changeIndex = ChangeIndexModifierImpl,
        .changeIndexWithMode = ChangeIndexWithModeModifierImpl,
        .setFinishCallback = SetFinishCallbackImpl,
        .finishAnimation = FinishAnimationImpl,
        .preloadItems = PreloadItemsModifierImpl,
        .setPreloadFinishCallback = SetPreloadFinishCallbackImpl,
        .startFakeDrag = StartFakeDragImpl,
        .fakeDragBy = FakeDragByImpl,
        .stopFakeDrag = StopFakeDragImpl,
        .isFakeDragging = IsFakeDraggingImpl,
    };
    return &modifier;
}

const CJUISwiperControllerModifier* GetCJUISwiperControllerModifier()
{
    static const CJUISwiperControllerModifier modifier = {
        .getSwiperController = GetSwiperController,
        .showNext = ShowNext,
        .showPrevious = ShowPrevious,
    };
    return &modifier;
}

const ArkUISwiperControllerModifier* GetSwiperControllerModifier()
{
    static const ArkUISwiperControllerModifier modifier = {
        .getSwiperController = GetSwiperController,
        .showNext = ShowNext,
        .showPrevious = ShowPrevious,
    };
    return &modifier;
}

const ArkUISwiperContentTransitionModifier* GetSwiperTransitionProxyModifier()
{
    static const ArkUISwiperContentTransitionModifier modifier = {
        .getSelectedIndex = GetSelectedIndexImpl,
        .getIndex = GetIndexImpl,
        .getPosition = GetPositionImpl,
        .getMainAxisLength = GetMainAxisLengthImpl,
        .finishTransition = FinishTransitionImpl,
    };
    return &modifier;
}
} // namespace NG::NodeModifier
} // namespace OHOS::Ace
