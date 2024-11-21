/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_MOCK_PATTERN_SCROLLABLE_MOCK_NESTABLE_SCROLL_CONTAINER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_MOCK_PATTERN_SCROLLABLE_MOCK_NESTABLE_SCROLL_CONTAINER_H

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/scrollable/nestable_scroll_container.h"

namespace OHOS::Ace::NG {
class MockNestableScrollContainer : public NestableScrollContainer {
    DECLARE_ACE_TYPE(MockNestableScrollContainer, NestableScrollContainer);

public:
    MOCK_METHOD(OHOS::Ace::Axis, GetAxis, (), (const, override));
    MOCK_METHOD(ScrollResult, HandleScroll, (float, int32_t, NestedState, float), (override));
    MOCK_METHOD(bool, HandleScrollVelocity, (float, const RefPtr<NestableScrollContainer>&), (override));
    MOCK_METHOD(void, OnScrollStartRecursive, (WeakPtr<NestableScrollContainer>, float, float), (override));
    MOCK_METHOD(void, OnScrollEndRecursive, (const std::optional<float>&), (override));
    MOCK_METHOD(void, OnScrollDragEndRecursive, (), (override));
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_MOCK_PATTERN_SCROLLABLE_MOCK_NESTABLE_SCROLL_CONTAINER_H
