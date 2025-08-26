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

#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/rosen/mock_canvas.h"

#include "core/components/checkable/checkable_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/linear_layout/column_model_ng.h"
#include "core/components_ng/pattern/radio/radio_model_ng.h"
#include "core/components_ng/pattern/radio/radio_paint_property.h"
#include "core/components_ng/pattern/radio/radio_pattern.h"
#include "core/components_ng/pattern/stage/stage_manager.h"
#include "core/components_ng/pattern/stage/stage_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;
using RadioBuilderFunc = std::function<void()>;
namespace OHOS::Ace::NG {
namespace {
const std::string NAME = "radio";
const std::string VALUE = "radio";
const std::string NAME1 = "radio1";
const std::string EMPTY_VALUE = "";
const std::string GROUP_NAME = "radioGroup";
const std::string GROUP_NAME1 = "radioGroup1";
const std::string GROUP_NAME_CHANGE = "radioGroupChange";

constexpr bool CHECKED = true;
constexpr bool UNCHECKED = false;
constexpr int BIG_INT = 100000000;
constexpr int NEGATIVE_BIG_INT = -100000000;
constexpr int NEGATIVE_NNORMAL_INT = -10;
constexpr int CHILD_NODE_ID = 100;
const std::optional<int32_t> INDICATOR_TYPE_TICK = 0;
} // namespace

class RadioSetBuilderTestNg : public testing::Test {
public:
};

/**
 * @tc.name: RadioSetBuilderTest001
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(RadioSetBuilderTestNg, RadioSetBuilderTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Radio node
     */
    RadioModelNG radioModelNG;
    radioModelNG.Create(VALUE, GROUP_NAME, INDICATOR_TYPE_TICK);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. Set radioConfiguration
     */
    pattern->SetRadioChecked(CHECKED);
    auto eventHub = frameNode->GetEventHub<NG::RadioEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetValue(VALUE);
    eventHub->SetEnabled(CHECKED);
    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [](RadioConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(VALUE, config.value_);
                EXPECT_EQ(CHECKED, config.checked_);
                EXPECT_EQ(CHECKED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: RadioSetBuilderTest002
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(RadioSetBuilderTestNg, RadioSetBuilderTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Radio node
     */
    RadioModelNG radioModelNG;
    radioModelNG.Create(VALUE, GROUP_NAME, INDICATOR_TYPE_TICK);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. Set radioConfiguration
     */
    pattern->SetRadioChecked(CHECKED);
    auto eventHub = frameNode->GetEventHub<NG::RadioEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetValue(VALUE);
    eventHub->SetEnabled(UNCHECKED);
    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [](RadioConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(VALUE, config.value_);
                EXPECT_EQ(CHECKED, config.checked_);
                EXPECT_EQ(UNCHECKED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: RadioSetBuilderTest003
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(RadioSetBuilderTestNg, RadioSetBuilderTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Radio node
     */
    RadioModelNG radioModelNG;
    radioModelNG.Create(VALUE, GROUP_NAME, INDICATOR_TYPE_TICK);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. Set radioConfiguration
     */
    pattern->SetRadioChecked(CHECKED);
    auto eventHub = frameNode->GetEventHub<NG::RadioEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetValue(VALUE);
    eventHub->SetEnabled(0);
    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [](RadioConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(VALUE, config.value_);
                EXPECT_EQ(CHECKED, config.checked_);
                EXPECT_EQ(UNCHECKED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: RadioSetBuilderTest004
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(RadioSetBuilderTestNg, RadioSetBuilderTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Radio node
     */
    RadioModelNG radioModelNG;
    radioModelNG.Create(VALUE, GROUP_NAME, INDICATOR_TYPE_TICK);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. Set radioConfiguration
     */
    pattern->SetRadioChecked(CHECKED);
    auto eventHub = frameNode->GetEventHub<NG::RadioEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetValue(VALUE);
    eventHub->SetEnabled(1);
    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [](RadioConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(VALUE, config.value_);
                EXPECT_EQ(CHECKED, config.checked_);
                EXPECT_EQ(CHECKED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: RadioSetBuilderTest005
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(RadioSetBuilderTestNg, RadioSetBuilderTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Radio node
     */
    RadioModelNG radioModelNG;
    radioModelNG.Create(VALUE, GROUP_NAME, INDICATOR_TYPE_TICK);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. Set radioConfiguration
     */
    pattern->SetRadioChecked(CHECKED);
    auto eventHub = frameNode->GetEventHub<NG::RadioEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetValue(VALUE);
    eventHub->SetEnabled(-1);
    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [](RadioConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(VALUE, config.value_);
                EXPECT_EQ(CHECKED, config.checked_);
                EXPECT_EQ(CHECKED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: RadioSetBuilderTest006
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(RadioSetBuilderTestNg, RadioSetBuilderTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Radio node
     */
    RadioModelNG radioModelNG;
    radioModelNG.Create(VALUE, GROUP_NAME, INDICATOR_TYPE_TICK);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. Set radioConfiguration
     */
    pattern->SetRadioChecked(1);
    auto eventHub = frameNode->GetEventHub<NG::RadioEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetValue(VALUE);
    eventHub->SetEnabled(CHECKED);
    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [](RadioConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(VALUE, config.value_);
                EXPECT_EQ(CHECKED, config.checked_);
                EXPECT_EQ(CHECKED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: RadioSetBuilderTest007
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(RadioSetBuilderTestNg, RadioSetBuilderTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Radio node
     */
    RadioModelNG radioModelNG;
    radioModelNG.Create(VALUE, GROUP_NAME, INDICATOR_TYPE_TICK);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. Set radioConfiguration
     */
    pattern->SetRadioChecked(0);
    auto eventHub = frameNode->GetEventHub<NG::RadioEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetValue(VALUE);
    eventHub->SetEnabled(CHECKED);
    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [](RadioConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(VALUE, config.value_);
                EXPECT_EQ(UNCHECKED, config.checked_);
                EXPECT_EQ(CHECKED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: RadioSetBuilderTest008
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(RadioSetBuilderTestNg, RadioSetBuilderTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Radio node
     */
    RadioModelNG radioModelNG;
    radioModelNG.Create(VALUE, GROUP_NAME, INDICATOR_TYPE_TICK);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. Set radioConfiguration
     */
    pattern->SetRadioChecked(-1);
    auto eventHub = frameNode->GetEventHub<NG::RadioEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetValue(VALUE);
    eventHub->SetEnabled(CHECKED);
    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [](RadioConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(VALUE, config.value_);
                EXPECT_EQ(CHECKED, config.checked_);
                EXPECT_EQ(CHECKED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: RadioSetBuilderTest009
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(RadioSetBuilderTestNg, RadioSetBuilderTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Radio node
     */
    RadioModelNG radioModelNG;
    radioModelNG.Create(VALUE, GROUP_NAME, INDICATOR_TYPE_TICK);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. Set radioConfiguration
     */
    pattern->SetRadioChecked(CHECKED);
    auto eventHub = frameNode->GetEventHub<NG::RadioEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetValue(VALUE);
    eventHub->SetEnabled(BIG_INT);
    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [](RadioConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(VALUE, config.value_);
                EXPECT_EQ(CHECKED, config.checked_);
                EXPECT_EQ(CHECKED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: RadioSetBuilderTest010
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(RadioSetBuilderTestNg, RadioSetBuilderTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Radio node
     */
    RadioModelNG radioModelNG;
    radioModelNG.Create(VALUE, GROUP_NAME, INDICATOR_TYPE_TICK);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. Set radioConfiguration
     */
    pattern->SetRadioChecked(CHECKED);
    auto eventHub = frameNode->GetEventHub<NG::RadioEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetValue(VALUE);
    eventHub->SetEnabled(NEGATIVE_BIG_INT);
    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [](RadioConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(VALUE, config.value_);
                EXPECT_EQ(CHECKED, config.checked_);
                EXPECT_EQ(CHECKED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: RadioSetBuilderTest011
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(RadioSetBuilderTestNg, RadioSetBuilderTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Radio node
     */
    RadioModelNG radioModelNG;
    radioModelNG.Create(VALUE, GROUP_NAME, INDICATOR_TYPE_TICK);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. Set radioConfiguration
     */
    pattern->SetRadioChecked(BIG_INT);
    auto eventHub = frameNode->GetEventHub<NG::RadioEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetValue(VALUE);
    eventHub->SetEnabled(CHECKED);
    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [](RadioConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(VALUE, config.value_);
                EXPECT_EQ(CHECKED, config.checked_);
                EXPECT_EQ(CHECKED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: RadioSetBuilderTest012
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(RadioSetBuilderTestNg, RadioSetBuilderTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Radio node
     */
    RadioModelNG radioModelNG;
    radioModelNG.Create(VALUE, GROUP_NAME, INDICATOR_TYPE_TICK);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. Set radioConfiguration
     */
    pattern->SetRadioChecked(NEGATIVE_BIG_INT);
    auto eventHub = frameNode->GetEventHub<NG::RadioEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetValue(VALUE);
    eventHub->SetEnabled(CHECKED);
    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [](RadioConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(VALUE, config.value_);
                EXPECT_EQ(CHECKED, config.checked_);
                EXPECT_EQ(CHECKED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: RadioSetBuilderTest013
 * @tc.desc: Test SetRadioChecked and get value
 * @tc.type: FUNC
 */
HWTEST_F(RadioSetBuilderTestNg, RadioSetBuilderTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Radio node
     */
    RadioModelNG radioModelNG;
    radioModelNG.Create(VALUE, GROUP_NAME, INDICATOR_TYPE_TICK);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. Set parameters to pattern radioSelect
     */
    pattern->SetRadioChecked(-1);
    /**
     * @tc.steps: step3. Get paint property
     * @tc.expected: Check the Radio property value
     */
    auto radioPaintProperty = frameNode->GetPaintProperty<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty, nullptr);
    bool isChecked = false;
    if (radioPaintProperty->HasRadioCheck()) {
        isChecked = radioPaintProperty->GetRadioCheckValue();
    } else {
        isChecked = false;
    }
    EXPECT_EQ(isChecked, CHECKED);
}

/**
 * @tc.name: RadioSetBuilderTest014
 * @tc.desc: Test SetRadioChecked and get value
 * @tc.type: FUNC
 */
HWTEST_F(RadioSetBuilderTestNg, RadioSetBuilderTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Radio node
     */
    RadioModelNG radioModelNG;
    radioModelNG.Create(VALUE, GROUP_NAME, INDICATOR_TYPE_TICK);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. Set parameters to pattern radioSelect
     */
    pattern->SetRadioChecked(BIG_INT);
    /**
     * @tc.steps: step3. Get paint property
     * @tc.expected: Check the Radio property value
     */
    auto radioPaintProperty = frameNode->GetPaintProperty<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty, nullptr);
    bool isChecked = false;
    if (radioPaintProperty->HasRadioCheck()) {
        isChecked = radioPaintProperty->GetRadioCheckValue();
    } else {
        isChecked = false;
    }
    EXPECT_EQ(isChecked, CHECKED);
}

/**
 * @tc.name: RadioSetBuilderTest015
 * @tc.desc: Test SetRadioChecked and get value
 * @tc.type: FUNC
 */
HWTEST_F(RadioSetBuilderTestNg, RadioSetBuilderTest015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Radio node
     */
    RadioModelNG radioModelNG;
    radioModelNG.Create(VALUE, GROUP_NAME, INDICATOR_TYPE_TICK);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. Set parameters to pattern radioSelect
     */
    pattern->SetRadioChecked(NEGATIVE_BIG_INT);
    /**
     * @tc.steps: step3. Get paint property
     * @tc.expected: Check the Radio property value
     */
    auto radioPaintProperty = frameNode->GetPaintProperty<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty, nullptr);
    bool isChecked = false;
    if (radioPaintProperty->HasRadioCheck()) {
        isChecked = radioPaintProperty->GetRadioCheckValue();
    } else {
        isChecked = false;
    }
    EXPECT_EQ(isChecked, CHECKED);
}

/**
 * @tc.name: RadioSetBuilderTest016
 * @tc.desc: Test SetRadioChecked and get value
 * @tc.type: FUNC
 */
HWTEST_F(RadioSetBuilderTestNg, RadioSetBuilderTest016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Radio node
     */
    RadioModelNG radioModelNG;
    radioModelNG.Create(VALUE, GROUP_NAME, INDICATOR_TYPE_TICK);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. Set parameters to pattern radioSelect
     */
    pattern->SetRadioChecked(0);
    /**
     * @tc.steps: step3. Get paint property
     * @tc.expected: Check the Radio property value
     */
    auto radioPaintProperty = frameNode->GetPaintProperty<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty, nullptr);
    bool isChecked = false;
    if (radioPaintProperty->HasRadioCheck()) {
        isChecked = radioPaintProperty->GetRadioCheckValue();
    } else {
        isChecked = false;
    }
    EXPECT_EQ(isChecked, UNCHECKED);
}

/**
 * @tc.name: RadioSetBuilderTest017
 * @tc.desc: Test SetRadioChecked and get value
 * @tc.type: FUNC
 */
HWTEST_F(RadioSetBuilderTestNg, RadioSetBuilderTest017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Radio node
     */
    RadioModelNG radioModelNG;
    radioModelNG.Create(VALUE, GROUP_NAME, INDICATOR_TYPE_TICK);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. Set parameters to pattern radioSelect
     */
    pattern->SetRadioChecked(1);
    /**
     * @tc.steps: step3. Get paint property
     * @tc.expected: Check the Radio property value
     */
    auto radioPaintProperty = frameNode->GetPaintProperty<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty, nullptr);
    bool isChecked = false;
    if (radioPaintProperty->HasRadioCheck()) {
        isChecked = radioPaintProperty->GetRadioCheckValue();
    } else {
        isChecked = false;
    }
    EXPECT_EQ(isChecked, CHECKED);
}

/**
 * @tc.name: RadioSetBuilderTest018
 * @tc.desc: Test SetRadioChecked and get value
 * @tc.type: FUNC
 */
HWTEST_F(RadioSetBuilderTestNg, RadioSetBuilderTest018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Radio node
     */
    RadioModelNG radioModelNG;
    radioModelNG.Create(VALUE, GROUP_NAME, INDICATOR_TYPE_TICK);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. Set parameters to pattern radioSelect
     */
    pattern->SetRadioChecked(NEGATIVE_NNORMAL_INT);
    /**
     * @tc.steps: step3. Get paint property
     * @tc.expected: Check the Radio property value
     */
    auto radioPaintProperty = frameNode->GetPaintProperty<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty, nullptr);
    bool isChecked = false;
    if (radioPaintProperty->HasRadioCheck()) {
        isChecked = radioPaintProperty->GetRadioCheckValue();
    } else {
        isChecked = false;
    }
    EXPECT_EQ(isChecked, CHECKED);
}

/**
 * @tc.name: RadioSetBuilderTest019
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(RadioSetBuilderTestNg, RadioSetBuilderTest019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Radio node
     */
    RadioModelNG radioModelNG;
    radioModelNG.Create(VALUE, GROUP_NAME, INDICATOR_TYPE_TICK);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. Set radioConfiguration
     */
    pattern->SetRadioChecked(CHECKED);
    auto eventHub = frameNode->GetEventHub<NG::RadioEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetValue(EMPTY_VALUE);
    eventHub->SetEnabled(CHECKED);
    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [](RadioConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(EMPTY_VALUE, config.value_);
                EXPECT_EQ(CHECKED, config.checked_);
                EXPECT_EQ(CHECKED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: RadioSetBuilderTest020
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(RadioSetBuilderTestNg, RadioSetBuilderTest020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Radio node
     */
    RadioModelNG radioModelNG;
    radioModelNG.Create(VALUE, GROUP_NAME, INDICATOR_TYPE_TICK);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. Set radioConfiguration
     */
    pattern->SetRadioChecked(NEGATIVE_NNORMAL_INT);
    auto eventHub = frameNode->GetEventHub<NG::RadioEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetValue(VALUE);
    eventHub->SetEnabled(CHECKED);
    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [](RadioConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(VALUE, config.value_);
                EXPECT_EQ(CHECKED, config.checked_);
                EXPECT_EQ(CHECKED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: RadioSetBuilderTest021
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(RadioSetBuilderTestNg, RadioSetBuilderTest021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Radio node
     */
    RadioModelNG radioModelNG;
    radioModelNG.Create(VALUE, GROUP_NAME, INDICATOR_TYPE_TICK);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. Set radioConfiguration
     */
    pattern->SetRadioChecked(CHECKED);
    auto eventHub = frameNode->GetEventHub<NG::RadioEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetValue(VALUE);
    eventHub->SetEnabled(NEGATIVE_NNORMAL_INT);
    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [](RadioConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(VALUE, config.value_);
                EXPECT_EQ(CHECKED, config.checked_);
                EXPECT_EQ(CHECKED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: RadioSetBuilderTest022
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(RadioSetBuilderTestNg, RadioSetBuilderTest022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Radio node
     */
    RadioModelNG radioModelNG;
    radioModelNG.Create(VALUE, GROUP_NAME, INDICATOR_TYPE_TICK);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. Set radioConfiguration
     */
    pattern->SetRadioChecked(NEGATIVE_NNORMAL_INT);
    auto eventHub = frameNode->GetEventHub<NG::RadioEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetValue(EMPTY_VALUE);
    eventHub->SetEnabled(NEGATIVE_NNORMAL_INT);
    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [](RadioConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(EMPTY_VALUE, config.value_);
                EXPECT_EQ(CHECKED, config.checked_);
                EXPECT_EQ(CHECKED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}
} // namespace OHOS::Ace::NG