/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_COMPATIBLE_ARKOALA_MODEFIER
#define FOUNDATION_ACE_FRAMEWORKS_COMPATIBLE_ARKOALA_MODEFIER

#include <list>
#include "base/memory/ace_type.h"

#ifdef __cplusplus
extern "C" {
#endif
namespace {
using MoveCallback = std::function<void(int32_t)>;
using SwiperChangeEndListener = std::function<void(const int32_t)>;
} // namespace
namespace OHOS::Ace {
class SwiperController;
class Component;
enum class TextDirection;
class RenderElement;
class Element;
class RenderNode;

struct ArkUISwiperModifierCompatible {
    RefPtr<Component> (*createSwiperComponent)(const std::list<RefPtr<Component>>& monthChildren);
    RefPtr<RenderElement> (*createSwiperElement)(const RefPtr<Element>& element);
    bool (*getMoveStatus)(const RefPtr<RenderNode>& renderNode);
    int32_t (*getCurrentIndex)(const RefPtr<RenderNode>& renderNode);
    void (*setIndex)(const RefPtr<Component>& swiperContainer, uint32_t index);
    void (*setDirection)(const RefPtr<Component>& swiperContainer, TextDirection direction);
    void (*setSlideContinue)(const RefPtr<Component>& swiperContainer, bool slideContinue);
    RefPtr<SwiperController> (*getSwiperController)(const RefPtr<Component>& swiperContainer);
    void (*setMoveCallback)(const RefPtr<Component>& swiperContainer, const MoveCallback& moveCallback);
    void (*setDisabledStatus)(const RefPtr<Component>& swiperContainer, bool disableStatus);
    void (*setLoop)(const RefPtr<Component>& swiperContainer, bool loop);
    void (*disableSwipe)(const RefPtr<Component>& swiperContainer, bool disableSwipe);
    void (*setDisableRotation)(const RefPtr<Component>& swiperContainer, bool disableRotate);
    void (*createSwiperRender)(
        const RefPtr<RenderNode>& renderSwiper, int32_t listenerId, const SwiperChangeEndListener& listener);
    void (*setAxis)(const RefPtr<Component>& swiperContainer, Axis axis);
    RefPtr<Component> (*updateSwiperComponent)(const RefPtr<Component>& swiperContainer);
};
} // namespace OHOS::Ace

#ifdef __cplusplus
};
#endif

#endif // FOUNDATION_ACE_FRAMEWORKS_COMPATIBLE_ARKOALA_MODEFIER