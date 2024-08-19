/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef TEST_UNITTEST_CORE_ACCESSIBILITY_ACCESSIBILITY_SESSION_ADAPTER_TEST_H
#define TEST_UNITTEST_CORE_ACCESSIBILITY_ACCESSIBILITY_SESSION_ADAPTER_TEST_H

#include "frameworks/core/accessibility/accessibility_session_adapter.h"
#include "frameworks/core/components_ng/pattern/pattern.h"

namespace OHOS::Ace::NG {

class MockAccessibilityTestPattern : public Pattern {
    DECLARE_ACE_TYPE(MockAccessibilityTestPattern, Pattern);

public:
    MockAccessibilityTestPattern()
    {
        accessibilitySessionAdapter_ = AceType::MakeRefPtr<AccessibilitySessionAdapter>();
    }

    ~MockAccessibilityTestPattern() override = default;

    RefPtr<AccessibilitySessionAdapter> GetAccessibilitySessionAdapter()
    {
        return accessibilitySessionAdapter_;
    }

private:
    RefPtr<AccessibilitySessionAdapter> accessibilitySessionAdapter_;
    ACE_DISALLOW_COPY_AND_MOVE(MockAccessibilityTestPattern);
};
}  // namespace OHOS::Ace::NG

#endif // TEST_UNITTEST_CORE_ACCESSIBILITY_ACCESSIBILITY_SESSION_ADAPTER_TEST_H