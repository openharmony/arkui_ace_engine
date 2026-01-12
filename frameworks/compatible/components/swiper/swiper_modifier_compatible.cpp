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

#include "compatible/components/swiper/swiper_loader.h"
#include "compatible/components/swiper/swiper_component.h"
#include "compatible/components/swiper/swiper_element.h"
#include "ui/base/ace_type.h"
#include "compatible/components/swiper/swiper_modifier.h"
#include "compatible/components/swiper/render_swiper.h"

namespace OHOS::Ace::SwiperModifier {
namespace {

void CreateSwiperRender(
    const RefPtr<RenderNode>& renderNode, int32_t listenerId, const SwiperChangeEndListener& listener)
{
    auto swiperRender = AceType::DynamicCast<RenderSwiper>(renderNode);
    if (!swiperRender) {
        LOGE("Failed to cast to swiperRender");
        return;
    }
    swiperRender->RegisterChangeEndListener(listenerId, listener);
}

RefPtr<RenderElement> CreateSwiperElement(const RefPtr<Element>& element)
{
    CHECK_NULL_RETURN(element, nullptr);
    auto swiperElement = AceType::DynamicCast<SwiperElement>(element);
    CHECK_NULL_RETURN(swiperElement, nullptr);
    return swiperElement;
}

bool GetMoveStatus(const RefPtr<RenderNode>& renderNode)
{
    CHECK_NULL_RETURN(renderNode, 0);
    auto swiperRenderNode = AceType::DynamicCast<RenderSwiper>(renderNode);
    CHECK_NULL_RETURN(swiperRenderNode, 0);
    auto moveStatus = swiperRenderNode->GetMoveStatus();
    return moveStatus;
}

int32_t GetCurrentIndex(const RefPtr<RenderNode>& renderNode)
{
    CHECK_NULL_RETURN(renderNode, 0);
    auto swiperRenderNode = AceType::DynamicCast<RenderSwiper>(renderNode);
    CHECK_NULL_RETURN(swiperRenderNode, 0);
    auto currentIndex = swiperRenderNode->GetCurrentIndex();
    return currentIndex;
}

RefPtr<Component> CreateSwiperComponent(const std::list<RefPtr<Component>>& monthChildren)
{
    if (monthChildren.empty()) {
        return nullptr;
    }
    auto swiperComponent = AceType::MakeRefPtr<SwiperComponent>(monthChildren, false);
    CHECK_NULL_RETURN(swiperComponent, nullptr);
    return swiperComponent;
}

void SetIndex(const RefPtr<Component>& swiperContainer, uint32_t index)
{
    CHECK_NULL_VOID(swiperContainer);
    auto swiperComponent = AceType::DynamicCast<SwiperComponent>(swiperContainer);
    CHECK_NULL_VOID(swiperComponent);
    swiperComponent->SetIndex(index);
}

void SetDirection(const RefPtr<Component>& swiperContainer, TextDirection direction)
{
    CHECK_NULL_VOID(swiperContainer);
    auto swiperComponent = AceType::DynamicCast<SwiperComponent>(swiperContainer);
    CHECK_NULL_VOID(swiperComponent);
    swiperComponent->SetTextDirection(direction);
}

void SetSlideContinue(const RefPtr<Component>& swiperContainer, bool slideContinue)
{
    CHECK_NULL_VOID(swiperContainer);
    auto swiperComponent = AceType::DynamicCast<SwiperComponent>(swiperContainer);
    CHECK_NULL_VOID(swiperComponent);
    swiperComponent->SetSlideContinue(slideContinue);
}

RefPtr<SwiperController> GetSwiperController(const RefPtr<Component>& swiperContainer)
{
    CHECK_NULL_RETURN(swiperContainer, nullptr);
    auto swiperComponent = AceType::DynamicCast<SwiperComponent>(swiperContainer);
    CHECK_NULL_RETURN(swiperComponent, nullptr);
    return swiperComponent->GetSwiperController();
}

void SetMoveCallback(const RefPtr<Component>& swiperContainer, const MoveCallback& moveCallback)
{
    CHECK_NULL_VOID(swiperContainer);
    auto swiperComponent = AceType::DynamicCast<SwiperComponent>(swiperContainer);
    CHECK_NULL_VOID(swiperComponent);
    swiperComponent->SetMoveCallback(moveCallback);
}

void SetDisabledStatus(const RefPtr<Component>& swiperContainer, bool disableStatus)
{
    CHECK_NULL_VOID(swiperContainer);
    auto swiperComponent = AceType::DynamicCast<SwiperComponent>(swiperContainer);
    CHECK_NULL_VOID(swiperComponent);
    swiperComponent->SetSlideContinue(disableStatus);
}

void DisableSwipe(const RefPtr<Component>& swiperContainer, bool disableSwipe)
{
    CHECK_NULL_VOID(swiperContainer);
    auto swiperComponent = AceType::DynamicCast<SwiperComponent>(swiperContainer);
    CHECK_NULL_VOID(swiperComponent);
    swiperComponent->SetSlideContinue(disableSwipe);
}

void SetLoop(const RefPtr<Component>& swiperContainer, bool loop)
{
    CHECK_NULL_VOID(swiperContainer);
    auto swiperComponent = AceType::DynamicCast<SwiperComponent>(swiperContainer);
    CHECK_NULL_VOID(swiperComponent);
    swiperComponent->SetSlideContinue(loop);
}

void SetDisableRotation(const RefPtr<Component>& swiperContainer, bool disableRotate)
{
    CHECK_NULL_VOID(swiperContainer);
    auto swiperComponent = AceType::DynamicCast<SwiperComponent>(swiperContainer);
    CHECK_NULL_VOID(swiperComponent);
    swiperComponent->SetSlideContinue(disableRotate);
}

void SetAxis(const RefPtr<Component>& swiperContainer, Axis axis)
{
    CHECK_NULL_VOID(swiperContainer);
    auto swiperComponent = AceType::DynamicCast<SwiperComponent>(swiperContainer);
    CHECK_NULL_VOID(swiperComponent);
    swiperComponent->SetAxis(axis);
}

RefPtr<Component> UpdateSwiperComponent(const RefPtr<Component>& swiperContainer)
{
    CHECK_NULL_RETURN(swiperContainer, nullptr);
    auto swiperComponent = AceType::DynamicCast<SwiperComponent>(swiperContainer);
    CHECK_NULL_RETURN(swiperComponent, nullptr);
    return swiperComponent;
}

}
const ArkUISwiperModifierCompatible* GetSwiperModifier()
{
    static const ArkUISwiperModifierCompatible instance = {
        .createSwiperComponent = CreateSwiperComponent,
        .createSwiperElement = CreateSwiperElement,
        .getMoveStatus = GetMoveStatus,
        .getCurrentIndex = GetCurrentIndex,
        .setIndex = SetIndex,
        .setDirection = SetDirection,
        .setSlideContinue = SetSlideContinue,
        .getSwiperController = GetSwiperController,
        .setMoveCallback = SetMoveCallback,
        .setDisabledStatus = SetDisabledStatus,
        .setLoop = SetLoop,
        .disableSwipe = DisableSwipe,
        .setDisableRotation = SetDisableRotation,
        .createSwiperRender = CreateSwiperRender,
        .setAxis = SetAxis,
        .updateSwiperComponent = UpdateSwiperComponent,
    };
    return &instance;
}
} // OHOS::Ace::SwiperModifier