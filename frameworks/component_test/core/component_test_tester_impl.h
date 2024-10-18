/*
 * Copyright (C) 2024 Huawei Device Co., Ltd.
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

#ifndef OHOS_ACE_COMPONENT_TEST_TESTER_IMPL_H
#define OHOS_ACE_COMPONENT_TEST_TESTER_IMPL_H

#include <memory>
#include <vector>

#include "component_test/core/action.h"
#include "component_test/core/component_test_component_impl.h"
#include "component_test/core/component_test_matcher_impl.h"

namespace OHOS::Ace::ComponentTest {
enum UiDirection : uint8_t {
    TO_LEFT,
    TO_RIGHT,
    TO_UP,
    TO_DOWN,
};

class ACE_FORCE_EXPORT ComponentTestTesterImpl final {
public:
    ComponentTestTesterImpl() = default;
    ~ComponentTestTesterImpl() = default;

    ComponentTestComponentImpl* FindComponentImpl(const ComponentTestMatcherImpl& matcher, ErrInfo& errInfo) const;
    std::unique_ptr<std::vector<ComponentTestComponentImpl*>> FindComponentsImpl(
        const ComponentTestMatcherImpl& matcher, ErrInfo& errInfo) const;
    void AssertComponentExistImpl(const ComponentTestMatcherImpl& matcher, ErrInfo& errInfo) const;
    ComponentTestComponentImpl* ScrollUntilExistImpl(const ComponentTestMatcherImpl& matcher, ErrInfo& errInfo) const;
    void TriggerKeyImpl(OHOS::MMI::KeyCode keyCode, ErrInfo& errInfo) const;
    void TriggerCombineKeysImpl(const std::vector<OHOS::MMI::KeyCode>& keyCodes, ErrInfo& errInfo) const;
    void TapImpl(float x, float y, ErrInfo& errInfo) const;
    void DoubleTapImpl(float x, float y, ErrInfo& errInfo) const;
    void PressImpl(float x, float y, ErrInfo& errInfo, uint32_t duration = PRESS_HOLD_MS) const;
    void ScrollImpl(float deltaX, float deltaY, ErrInfo& errInfo) const;
    void DragImpl(float startX, float startY, float endX, float endY, uint32_t speed, ErrInfo& errInfo) const;
    void FlingImpl(
        const NG::PointF& from, const NG::PointF& to, uint32_t stepLen, uint32_t speed, ErrInfo& errInfo) const;
    void FlingImpl(UiDirection direction, uint32_t speed, ErrInfo& errInfo) const;

private:
    void GenericClick(float x, float y, const TouchType touchType, uint32_t duration = PRESS_HOLD_MS) const;
};

} // namespace OHOS::Ace::ComponentTest

#endif // OHOS_NAPI_ACE_COMPONENT_TEST_TESTER_IMPL_H
