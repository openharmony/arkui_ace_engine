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

// declarations
#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "point_light_test.h"
#include "select_modifier_test.h"
#include "slider_modifier_test.h"
#include "swiper_modifier_test.h"
#include "image_common_methods_test.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS;
using namespace OHOS::Ace;
using namespace OHOS::Ace::NG::Converter;

HWTEST_F(DragEventAccessorTest, GetDragBehaviorTest, TestSize.Level1)
{
    for (auto& [input, value, expected] : testFixtureEnumArkDragBehaviorValues) {
        dragEvent_->SetDragBehavior(value);
        EXPECT_EQ(expected, accessor_->getDragBehavior(peer_)) <<
            "Input value is: " << input << ", method: getDragBehavior";
    }
}

HWTEST_F(DragEventAccessorTest, GetResultTest, TestSize.Level1)
{
    for (auto& [input, value, expected] : testFixtureEnumArkDragResultValues) {
        dragEvent_->SetResult(value);
        EXPECT_EQ(accessor_->getResult(peer_), expected) <<
            "Input value is: " << input << ", method: SetResult";
    }
}

HWTEST_F(DimensionUnitTest, DimensionUnitFakeTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
}

HWTEST_F(DimensionUnitTest, DimensionUnitFakeTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
}

HWTEST_F(PatternLockModifierTest, setSelectedColorTestDefaultValues, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
}

HWTEST_F(WaterFlowModifierTest, setCashedCountTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    ASSERT_NE(modifier_->setCashedCount, nullptr);
    auto checkval = GetAttrValue<std::string>(node_, CASHED_COUNT_ATTRIBUTE_NAME);
    EXPECT_EQ(checkVal, CASHED_COUNT_ATTRIBUTE_DEFAULT_VALUE);
}

HWTEST_F(StateStylesOpsAccessorTest, onStateStyleChangeTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
}

HWTEST_F(DatePickerDialogTest, datePickerDialogFakeTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
}

HWTEST_F(DimensionUnitTest, DimensionUnitFakeTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
}

HWTEST_F(UIContextAtomicServiceBarAccessorTest, atomicServiceBarFakeTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
}

HWTEST_F(TextTimerModifierTest, setFormatTestFormatValidValues, TestSize.Level1)
{
    auto checkValue = [this](const std::string& input, const Ark_String& value, const std::string& expectedStr) {
        auto format = Converter::ArkValue<Opt_String>(value);
        modifier_->setFormat(node_, &format);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FORMAT_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input << ", method: setFormat, attribute: format";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureTextTimerDateFormatValidValues) {
        checkValue(input, value, expected);
    }
}

