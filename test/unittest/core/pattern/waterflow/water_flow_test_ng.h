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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_PATTERN_WATER_FLOW_TEST_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_PATTERN_WATER_FLOW_TEST_NG_H

#include <cstdint>
#include <map>
#include <memory>

#include "gtest/gtest.h"

#define protected public
#define private public
#include "test/unittest/core/pattern/test_ng.h"

#include "base/geometry/offset.h"
#include "core/components_ng/pattern/waterflow/water_flow_accessibility_property.h"
#include "core/components_ng/pattern/waterflow/water_flow_event_hub.h"
#include "core/components_ng/pattern/waterflow/water_flow_layout_property.h"
#include "core/components_ng/pattern/waterflow/water_flow_model_ng.h"
#include "core/components_ng/pattern/waterflow/water_flow_pattern.h"
#undef private
#undef protected

namespace OHOS::Ace::NG {
class WaterFlowTestNg : public TestNG {
protected:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void GetInstance();

    void Create(const std::function<void(WaterFlowModelNG)>& callback = nullptr, bool flushLayout = true);
    void CreateWithItem(const std::function<void(WaterFlowModelNG)>& callback = nullptr);
    static void CreateItem(int32_t number = 10);
    static void CreateItemWithHeight(float height);
    void UpdateCurrentOffset(float offset, int32_t source = SCROLL_FROM_UPDATE);
    void MouseSelect(Offset start, Offset end);
    void MouseSelectRelease();
    static std::function<void()> GetDefaultHeaderBuilder();

    void AddItems(int32_t number);

    AssertionResult IsEqualTotalOffset(float expectOffset);
    void HandleDrag(float offset);

    RefPtr<FrameNode> frameNode_;
    RefPtr<WaterFlowPattern> pattern_;
    RefPtr<WaterFlowEventHub> eventHub_;
    RefPtr<WaterFlowLayoutProperty> layoutProperty_;
    RefPtr<WaterFlowAccessibilityProperty> accessibilityProperty_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_PATTERN_WATER_FLOW_TEST_NG_H
