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
#include "core/components/scroll/scrollable.h"

namespace OHOS::Ace::NG {
class NestableScrollContainer : public virtual AceType {
    DECLARE_ACE_TYPE(NestableScrollContainer, AceType)
public:
    NestableScrollContainer() = default;
    ~NestableScrollContainer() override = default;

    virtual Axis GetAxis() const = 0;

    // regular scroll motion
    virtual ScrollResult HandleScroll(float offset, int32_t source, NestedState state) = 0;
    // triggered by drag end velocity
    virtual bool HandleScrollVelocity(float velocity) = 0;

    virtual void OnScrollStartRecursive(float position) = 0;
    virtual void OnScrollEndRecursive() = 0;

    ACE_DISALLOW_COPY_AND_MOVE(NestableScrollContainer);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLLABLE_NESTABLE_SCROLL_CONTAINER_H
