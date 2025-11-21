/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#include <gtest/gtest.h>

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"

using namespace testing;
using namespace testing::ext;

HWTEST_F(DragEventAccessorTest, GetDragBehaviorTest, TestSize.Level1)
{
    for (auto& [input, value, expected] : testFixtureEnumArkDragBehaviorValues) {
        dragEvent_->SetDragBehavior(value);
        EXPECT_EQ(expected, accessor_->getDragBehavior(peer_)) <<
            "Input value is: " << input << ", method: getDragBehavior";
    }
}

HWTEST_F(WaterFlowModifierTest, setCashedCountTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    ASSERT_NE(modifier_->setCashedCount, nullptr);
    auto checkval = GetAttrValue<std::string>(node_, CASHED_COUNT_ATTRIBUTE_NAME);
    EXPECT_EQ(checkVal, CASHED_COUNT_ATTRIBUTE_DEFAULT_VALUE);
}
using namespace testing;
using namespace testing::ext;