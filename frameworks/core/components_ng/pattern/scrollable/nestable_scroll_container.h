/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLLABLE_NESTABLE_SCROLL_CONTAINER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLLABLE_NESTABLE_SCROLL_CONTAINER_H

#include "base/memory/ace_type.h"
#include "base/utils/noncopyable.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable.h"

namespace OHOS::Ace::NG {
class NestableScrollContainer : public virtual Pattern {
    DECLARE_ACE_TYPE(NestableScrollContainer, Pattern)
public:
    NestableScrollContainer() = default;
    ~NestableScrollContainer() override = default;

    virtual Axis GetAxis() const = 0;

    /**
     * @brief Handle regular scroll motion.
     *
     * @param offset delta on the main axis.
     * @param source scroll source type defined in scrollable_properties.h.
     * @param state current nested state. Defines how this function is triggered.
     * @return remaining offset and whether the edge is reached
     */
    virtual ScrollResult HandleScroll(float offset, int32_t source, NestedState state) = 0;

    /**
     * @brief Handle drag end velocity, triggering a scroll animation or a bounce animation on overScroll.
     *
     * @param velocity drag end velocity.
     * @return true if velocity is consumed
     */
    virtual bool HandleScrollVelocity(float velocity) = 0;

    /**
     * @brief Called when the scroll starts, recursively pass upwards.
     *
     * @param position The global position of the first touch point.
     */
    virtual void OnScrollStartRecursive(float position) = 0;

    /**
     * @brief This function is called when the scrolling ends, recursively pass upwards.
     *
     * @param velocity The velocity of the DragEnd event. Optionally passed to parent when the child won't call
     * HandleScrollVelocity.
     */
    virtual void OnScrollEndRecursive(const std::optional<float>& velocity) = 0;

protected:
    /**
     * @brief Helper function. Searches for the parent NestableScrollContainer of the current instance.
     *
     * @return RefPtr<NestableScrollContainer> A reference to the parent NestableScrollContainer.
     */
    RefPtr<NestableScrollContainer> SearchParent();

    ACE_DISALLOW_COPY_AND_MOVE(NestableScrollContainer);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLLABLE_NESTABLE_SCROLL_CONTAINER_H
