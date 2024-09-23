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
#include "core/event/touch_event.h"
using namespace testing;
using namespace testing::ext;
using RadioBuilderFunc = std::function<void()>;
namespace OHOS::Ace::NG {
namespace {
const std::string NAME = "radio";
const std::string VALUE = "radio";
const std::string NAME1 = "radio1";
const std::string GROUP_NAME = "radioGroup";
const std::string GROUP_NAME1 = "radioGroup1";
const std::string GROUP_NAME_CHANGE = "radioGroupChange";

constexpr bool CHECKED = true;
constexpr int BIG_INT = 100000000;
constexpr int NEGATIVE_BIG_INT = -100000000;
constexpr int CHILD_NODE_ID = 100;
constexpr int NEGATIVE_CHILD_NODE_ID = -10;
const std::optional<int32_t> INDICATOR_TYPE_TICK = 0;
} // namespace

class RadioNodeTestNg : public testing::Test {
public:
};

/**
 * @tc.name: RadioNodeTest001
 * @tc.desc: Test customNode
 * @tc.type: FUNC
 */
HWTEST_F(RadioNodeTestNg, RadioNodeTest001, TestSize.Level1)
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
     * @tc.steps: step3. Make builderFunc
     */
    auto node = [](RadioConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(VALUE, config.value_);
                EXPECT_EQ(CHECKED, config.checked_);
                EXPECT_EQ(CHECKED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", 1, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->FireBuilder();
    /**
     * @tc.steps: step5. Test customNode
     */
    auto buildNode = pattern->customNode_;
    /**
     * @tc.expected: Check the Radio child id
     */
    EXPECT_EQ(1, buildNode->GetId());
}

/**
 * @tc.name: RadioNodeTest002
 * @tc.desc: Test customNode
 * @tc.type: FUNC
 */
HWTEST_F(RadioNodeTestNg, RadioNodeTest002, TestSize.Level1)
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
     * @tc.steps: step3. Make builderFunc
     */
    auto node = [](RadioConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(VALUE, config.value_);
                EXPECT_EQ(CHECKED, config.checked_);
                EXPECT_EQ(CHECKED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", NEGATIVE_CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->FireBuilder();
    /**
     * @tc.steps: step5. Test customNode
     */
    auto buildNode = pattern->customNode_;
    /**
     * @tc.expected: Check the Radio child id
     */
    EXPECT_EQ(NEGATIVE_CHILD_NODE_ID, buildNode->GetId());
}

/**
 * @tc.name: RadioNodeTest003
 * @tc.desc: Test customNode
 * @tc.type: FUNC
 */
HWTEST_F(RadioNodeTestNg, RadioNodeTest003, TestSize.Level1)
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
     * @tc.steps: step3. Make builderFunc
     */
    auto node = [](RadioConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(VALUE, config.value_);
                EXPECT_EQ(CHECKED, config.checked_);
                EXPECT_EQ(CHECKED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", 0, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->FireBuilder();
    /**
     * @tc.steps: step5. Test customNode
     */
    auto buildNode = pattern->customNode_;
    /**
     * @tc.expected: Check the Radio child id
     */
    EXPECT_EQ(0, buildNode->GetId());
}

/**
 * @tc.name: RadioNodeTest004
 * @tc.desc: Test customNode
 * @tc.type: FUNC
 */
HWTEST_F(RadioNodeTestNg, RadioNodeTest004, TestSize.Level1)
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
     * @tc.steps: step3. Make builderFunc
     */
    auto node = [](RadioConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(VALUE, config.value_);
                EXPECT_EQ(CHECKED, config.checked_);
                EXPECT_EQ(CHECKED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", BIG_INT, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->FireBuilder();
    /**
     * @tc.steps: step5. Test customNode
     */
    auto buildNode = pattern->customNode_;
    /**
     * @tc.expected: Check the Radio child id
     */
    EXPECT_EQ(BIG_INT, buildNode->GetId());
}

/**
 * @tc.name: RadioNodeTest005
 * @tc.desc: Test customNode
 * @tc.type: FUNC
 */
HWTEST_F(RadioNodeTestNg, RadioNodeTest005, TestSize.Level1)
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
     * @tc.steps: step3. Make builderFunc
     */
    auto node = [](RadioConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(VALUE, config.value_);
                EXPECT_EQ(CHECKED, config.checked_);
                EXPECT_EQ(CHECKED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", NEGATIVE_BIG_INT, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->FireBuilder();
    /**
     * @tc.steps: step5. Test customNode
     */
    auto buildNode = pattern->customNode_;
    /**
     * @tc.expected: Check the Radio child id
     */
    EXPECT_EQ(NEGATIVE_BIG_INT, buildNode->GetId());
}

/**
 * @tc.name: RadioNodeTest006
 * @tc.desc: Test customNode
 * @tc.type: FUNC
 */
HWTEST_F(RadioNodeTestNg, RadioNodeTest006, TestSize.Level1)
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
     * @tc.steps: step3. Make builderFunc
     */
    auto node = [](RadioConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(VALUE, config.value_);
                EXPECT_EQ(CHECKED, config.checked_);
                EXPECT_EQ(CHECKED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };

    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->FireBuilder();
    /**
     * @tc.steps: step5. Test customNode
     */
    auto buildNode = pattern->customNode_;
    /**
     * @tc.expected: Check the Radio child id
     */
    EXPECT_EQ("", buildNode->GetHostTag());
}

/**
 * @tc.name: RadioNodeTest007
 * @tc.desc: Test customNode
 * @tc.type: FUNC
 */
HWTEST_F(RadioNodeTestNg, RadioNodeTest007, TestSize.Level1)
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
     * @tc.steps: step3. Make builderFunc
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
     * @tc.steps: step4. Set parameters to radioModelNG builderFunc
     */
    radioModelNG.SetBuilderFunc(frameNode.GetRawPtr(), node);
    pattern->FireBuilder();
    /**
     * @tc.steps: step5. Test customNode
     */
    auto buildNode = pattern->customNode_;
    /**
     * @tc.expected: Check the Radio child id
     */
    EXPECT_EQ("child", buildNode->GetHostTag());
}

/**
 * @tc.name: RadioNodeTest008
 * @tc.desc: Test UseContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(RadioNodeTestNg, RadioNodeTest008, TestSize.Level1)
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
     * @tc.steps: step3. Set parameters to radioModelNG builderFunc
     */
    radioModelNG.SetBuilderFunc(frameNode.GetRawPtr(), nullptr);
    pattern->FireBuilder();
    /**
     * @tc.steps: step4. Test customNode
     */
    auto isUsed = pattern->UseContentModifier();
    /**
     * @tc.expected: Check the Radio child id
     */
    EXPECT_EQ(false, isUsed);
}

/**
 * @tc.name: RadioNodeTest009
 * @tc.desc: Test UseContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(RadioNodeTestNg, RadioNodeTest009, TestSize.Level1)
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
     * @tc.steps: step2. Set parameters to radioModelNG builderFunc
     */
    pattern->SetBuilderFunc(nullptr);
    pattern->FireBuilder();
    /**
     * @tc.steps: step3. Test UseContentModifier
     */
    auto isUsed = pattern->UseContentModifier();
    /**
     * @tc.expected: Check the Radio child id
     */
    EXPECT_EQ(false, isUsed);
}

/**
 * @tc.name: RadioNodeTest010
 * @tc.desc: Test UseContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(RadioNodeTestNg, RadioNodeTest010, TestSize.Level1)
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
     * @tc.steps: step3. Make builderFunc
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
     * @tc.steps: step4. Set parameters to radioModelNG builderFunc
     */
    radioModelNG.SetBuilderFunc(frameNode.GetRawPtr(), node);
    pattern->FireBuilder();
    /**
     * @tc.steps: step5. Test customNode
     */
    auto buildNode = pattern->customNode_;
    /**
     * @tc.expected: Check the Radio child id
     */
    EXPECT_EQ("child", buildNode->GetHostTag());
    /**
     * @tc.steps: step6. change builder func nullptr
     */
    radioModelNG.SetBuilderFunc(frameNode.GetRawPtr(), nullptr);
    pattern->FireBuilder();
    /**
     * @tc.steps: step7. Test UseContentModifier
     */
    auto isUsed = pattern->UseContentModifier();
    /**
     * @tc.expected: isUsed is false
     */
    EXPECT_EQ(false, isUsed);
}

/**
 * @tc.name: RadioNodeTest011
 * @tc.desc: Test UseContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(RadioNodeTestNg, RadioNodeTest011, TestSize.Level1)
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
     * @tc.steps: step3. Make builderFunc
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
     * @tc.steps: step4. Set parameters to radioModelNG builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->FireBuilder();
    /**
     * @tc.steps: step5. Test customNode
     */
    auto buildNode = pattern->customNode_;
    /**
     * @tc.expected: Check the Radio child id
     */
    EXPECT_EQ("child", buildNode->GetHostTag());
    /**
     * @tc.steps: step6. change builder func nullptr
     */
    pattern->SetBuilderFunc(nullptr);
    pattern->FireBuilder();
    /**
     * @tc.steps: step7. Test UseContentModifier
     */
    auto isUsed = pattern->UseContentModifier();
    /**
     * @tc.expected: isUsed is false
     */
    EXPECT_EQ(false, isUsed);
}

/**
 * @tc.name: RadioNodeTest012
 * @tc.desc: Test SetChangeValue
 * @tc.type: FUNC
 */
HWTEST_F(RadioNodeTestNg, RadioNodeTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Radio node
     */
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. Set radioConfiguration
     */
    auto eventHub = frameNode->GetEventHub<NG::RadioEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetValue(NAME);
    eventHub->SetEnabled(CHECKED);
    /**
     * @tc.steps: step3. Make builderFunc
     */
    auto node = [](RadioConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(NAME, config.value_);
                EXPECT_EQ(CHECKED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to radioModelNG builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->FireBuilder();
    /**
     * @tc.steps: step5. Test customNode
     */
    auto buildNode = pattern->customNode_;
    /**
     * @tc.expected: Check the Radio child id
     */
    EXPECT_EQ("child", buildNode->GetHostTag());
    /**
     * @tc.steps: step6. Test SetChangeValue
     */
    pattern->SetRadioChecked(true);
    /**
     * @tc.steps: step7. Get isChecked
     */
    auto radioPaintProperty = frameNode->GetPaintProperty<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty, nullptr);
    bool isChecked = false;
    if (radioPaintProperty->HasRadioCheck()) {
        isChecked = radioPaintProperty->GetRadioCheckValue();
    } else {
        isChecked = false;
    }
    /**
     * @tc.expected: Check the Radio isChecked
     */
    EXPECT_EQ(isChecked, true);
}

/**
 * @tc.name: RadioNodeTest013
 * @tc.desc: Test SetChangeValue
 * @tc.type: FUNC
 */
HWTEST_F(RadioNodeTestNg, RadioNodeTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Radio node
     */
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. Set radioConfiguration
     */
    auto eventHub = frameNode->GetEventHub<NG::RadioEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetValue(NAME);
    eventHub->SetEnabled(CHECKED);
    /**
     * @tc.steps: step3. Make builderFunc
     */
    auto node = [](RadioConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(NAME, config.value_);
                EXPECT_EQ(CHECKED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to radioModelNG builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->FireBuilder();
    /**
     * @tc.steps: step5. Test customNode
     */
    auto buildNode = pattern->customNode_;
    /**
     * @tc.expected: Check the Radio child id
     */
    EXPECT_EQ("child", buildNode->GetHostTag());
    /**
     * @tc.steps: step6. Test SetChangeValue
     */
    pattern->SetRadioChecked(false);
    /**
     * @tc.steps: step7. Get isChecked
     */
    auto radioPaintProperty = frameNode->GetPaintProperty<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty, nullptr);
    bool isChecked = false;
    if (radioPaintProperty->HasRadioCheck()) {
        isChecked = radioPaintProperty->GetRadioCheckValue();
    } else {
        isChecked = false;
    }
    /**
     * @tc.expected: Check the Radio isChecked
     */
    EXPECT_EQ(isChecked, false);
}

/**
 * @tc.name: RadioNodeTest014
 * @tc.desc: Test SetChangeValue
 * @tc.type: FUNC
 */
HWTEST_F(RadioNodeTestNg, RadioNodeTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Radio node
     */
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. Set radioConfiguration
     */
    auto eventHub = frameNode->GetEventHub<NG::RadioEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetValue(NAME);
    eventHub->SetEnabled(CHECKED);
    /**
     * @tc.steps: step3. Make builderFunc
     */
    auto node = [](RadioConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(NAME, config.value_);
                EXPECT_EQ(CHECKED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to radioModelNG builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->FireBuilder();
    /**
     * @tc.steps: step5. Test customNode
     */
    auto buildNode = pattern->customNode_;
    /**
     * @tc.expected: Check the Radio child id
     */
    EXPECT_EQ("child", buildNode->GetHostTag());
    /**
     * @tc.steps: step6. Test SetChangeValue
     */
    pattern->SetRadioChecked(0);
    /**
     * @tc.steps: step7. Get isChecked
     */
    auto radioPaintProperty = frameNode->GetPaintProperty<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty, nullptr);
    bool isChecked = false;
    if (radioPaintProperty->HasRadioCheck()) {
        isChecked = radioPaintProperty->GetRadioCheckValue();
    } else {
        isChecked = false;
    }
    /**
     * @tc.expected: Check the Radio isChecked
     */
    EXPECT_EQ(isChecked, false);
}

/**
 * @tc.name: RadioNodeTest015
 * @tc.desc: Test SetChangeValue
 * @tc.type: FUNC
 */
HWTEST_F(RadioNodeTestNg, RadioNodeTest015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Radio node
     */
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. Set radioConfiguration
     */
    auto eventHub = frameNode->GetEventHub<NG::RadioEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetValue(NAME);
    eventHub->SetEnabled(CHECKED);
    /**
     * @tc.steps: step3. Make builderFunc
     */
    auto node = [](RadioConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(NAME, config.value_);
                EXPECT_EQ(CHECKED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to radioModelNG builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->FireBuilder();
    /**
     * @tc.steps: step5. Test customNode
     */
    auto buildNode = pattern->customNode_;
    /**
     * @tc.expected: Check the Radio child id
     */
    EXPECT_EQ("child", buildNode->GetHostTag());
    /**
     * @tc.steps: step6. Test SetChangeValue
     */
    pattern->SetRadioChecked(1);
    /**
     * @tc.steps: step7. Get isChecked
     */
    auto radioPaintProperty = frameNode->GetPaintProperty<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty, nullptr);
    bool isChecked = false;
    if (radioPaintProperty->HasRadioCheck()) {
        isChecked = radioPaintProperty->GetRadioCheckValue();
    } else {
        isChecked = false;
    }
    /**
     * @tc.expected: Check the Radio isChecked
     */
    EXPECT_EQ(isChecked, true);
}

/**
 * @tc.name: RadioNodeTest016
 * @tc.desc: Test SetChangeValue
 * @tc.type: FUNC
 */
HWTEST_F(RadioNodeTestNg, RadioNodeTest016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Radio node
     */
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. Set radioConfiguration
     */
    auto eventHub = frameNode->GetEventHub<NG::RadioEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetValue(NAME);
    eventHub->SetEnabled(CHECKED);
    /**
     * @tc.steps: step3. Make builderFunc
     */
    auto node = [](RadioConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(NAME, config.value_);
                EXPECT_EQ(CHECKED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to radioModelNG builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->FireBuilder();
    /**
     * @tc.steps: step5. Test customNode
     */
    auto buildNode = pattern->customNode_;
    /**
     * @tc.expected: Check the Radio child id
     */
    EXPECT_EQ("child", buildNode->GetHostTag());
    /**
     * @tc.steps: step6. Test SetChangeValue
     */
    pattern->SetRadioChecked(BIG_INT);
    /**
     * @tc.steps: step7. Get isChecked
     */
    auto radioPaintProperty = frameNode->GetPaintProperty<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty, nullptr);
    bool isChecked = false;
    if (radioPaintProperty->HasRadioCheck()) {
        isChecked = radioPaintProperty->GetRadioCheckValue();
    } else {
        isChecked = false;
    }
    /**
     * @tc.expected: Check the Radio isChecked
     */
    EXPECT_EQ(isChecked, true);
}

/**
 * @tc.name: RadioNodeTest017
 * @tc.desc: Test SetChangeValue
 * @tc.type: FUNC
 */
HWTEST_F(RadioNodeTestNg, RadioNodeTest017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Radio node
     */
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. Set radioConfiguration
     */
    auto eventHub = frameNode->GetEventHub<NG::RadioEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetValue(NAME);
    eventHub->SetEnabled(CHECKED);
    /**
     * @tc.steps: step3. Make builderFunc
     */
    auto node = [](RadioConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(NAME, config.value_);
                EXPECT_EQ(CHECKED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to radioModelNG builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->FireBuilder();
    /**
     * @tc.steps: step5. Test customNode
     */
    auto buildNode = pattern->customNode_;
    /**
     * @tc.expected: Check the Radio child id
     */
    EXPECT_EQ("child", buildNode->GetHostTag());
    /**
     * @tc.steps: step6. Test SetChangeValue
     */
    pattern->SetRadioChecked(NEGATIVE_BIG_INT);
    /**
     * @tc.steps: step7. Get isChecked
     */
    auto radioPaintProperty = frameNode->GetPaintProperty<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty, nullptr);
    bool isChecked = false;
    if (radioPaintProperty->HasRadioCheck()) {
        isChecked = radioPaintProperty->GetRadioCheckValue();
    } else {
        isChecked = false;
    }
    /**
     * @tc.expected: Check the Radio isChecked
     */
    EXPECT_EQ(isChecked, true);
}

/**
 * @tc.name: RadioNodeTest018
 * @tc.desc: Test SetChangeValue
 * @tc.type: FUNC
 */
HWTEST_F(RadioNodeTestNg, RadioNodeTest018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Radio node.
     */
    auto frameNode = RadioModelNG::CreateFrameNode(0);
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. SetRadioIndicatorType.
     */
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);
    std::string testName = "testName";
    std::string testGroup = "testGroup";
    int32_t indicator = 2;
    RadioModelNG::SetRadioOptions(node, testName, testGroup, indicator);

    /**
     * @tc.steps: step3. Get RadioEventHub and assert the name and group.
     */
    auto eventHub = frameNode->GetEventHub<NG::RadioEventHub>();
    CHECK_NULL_VOID(eventHub);
    EXPECT_EQ(eventHub->GetValue(), testName);
    EXPECT_EQ(eventHub->GetGroup(), testGroup);

    /**
     * @tc.steps: step4. Get paintProperty and assert the indicator.
     */
    auto paintProperty = frameNode->GetPaintProperty<RadioPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_EQ(paintProperty->GetRadioIndicatorValue(), indicator);
}

/**
 * @tc.name: PreventDefault001
 * @tc.desc: test InitTouchEvent and InitClickEvent
 * @tc.type: FUNC
 */
HWTEST_F(RadioNodeTestNg, PreventDefault001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Radio node
     */
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);

    /**
     * @tc.steps: step2. Mock TouchEventInfo info and set preventDefault to true
     * @tc.expected: Check the param value
     */
    pattern->InitTouchEvent();
    TouchEventInfo touchInfo("onTouch");
    TouchLocationInfo touchDownInfo(1);
    touchDownInfo.SetTouchType(TouchType::DOWN);
    touchInfo.SetPreventDefault(true);
    touchInfo.SetSourceDevice(SourceType::TOUCH);
    touchInfo.AddTouchLocationInfo(std::move(touchDownInfo));
    pattern->touchListener_->callback_(touchInfo);
    EXPECT_TRUE(pattern->isTouchPreventDefault_);
    EXPECT_EQ(pattern->touchHoverType_, TouchHoverAnimationType::PRESS);
    /**
     * @tc.steps: step3.Mock GestureEvent info and set preventDefault to true
     * @tc.expected: Check the param value
     */
    pattern->InitClickEvent();
    GestureEvent clickInfo;
    clickInfo.SetPreventDefault(true);
    clickInfo.SetSourceDevice(SourceType::TOUCH);
    pattern->clickListener_->operator()(clickInfo);
    EXPECT_FALSE(pattern->isTouchPreventDefault_);
}

/**
 * @tc.name: PreventDefault002
 * @tc.desc: test InitTouchEvent and InitClickEvent
 * @tc.type: FUNC
 */
HWTEST_F(RadioNodeTestNg, PreventDefault002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Radio node
     */
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);

    /**
     * @tc.steps: step2. Mock TouchEvent info and set preventDefault to false
     * @tc.expected: Check the param value
     */
    pattern->InitTouchEvent();
    TouchEventInfo touchInfo("onTouch");
    TouchLocationInfo touchDownInfo(1);
    touchDownInfo.SetTouchType(TouchType::CANCEL);
    touchInfo.SetPreventDefault(false);
    touchInfo.SetSourceDevice(SourceType::TOUCH);
    touchInfo.AddTouchLocationInfo(std::move(touchDownInfo));
    pattern->touchListener_->callback_(touchInfo);
    EXPECT_FALSE(pattern->isTouchPreventDefault_);
    EXPECT_EQ(pattern->touchHoverType_, TouchHoverAnimationType::NONE);
    /**
     * @tc.steps: step3. Mock GestureEvent info and set preventDefault to false
     * @tc.expected: Check the param value
     */
    pattern->InitClickEvent();
    GestureEvent clickInfo;
    clickInfo.SetPreventDefault(false);
    clickInfo.SetSourceDevice(SourceType::TOUCH);
    pattern->clickListener_->operator()(clickInfo);
    EXPECT_FALSE(pattern->isTouchPreventDefault_);
}

/**
 * @tc.name: PreventDefault003
 * @tc.desc: test InitTouchEvent and InitClickEvent
 * @tc.type: FUNC
 */
HWTEST_F(RadioNodeTestNg, PreventDefault003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Radio node
     */
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    /**
     * @tc.steps: step2. Mock TouchEvent info and set preventDefault to false
     * @tc.expected: Check the param value
     */
    pattern->InitTouchEvent();
    TouchEventInfo touchInfo("onTouch");
    TouchLocationInfo touchDownInfo(1);
    touchDownInfo.SetTouchType(TouchType::UP);
    touchInfo.SetPreventDefault(true);
    touchInfo.SetSourceDevice(SourceType::MOUSE);
    touchInfo.AddTouchLocationInfo(std::move(touchDownInfo));
    pattern->touchListener_->callback_(touchInfo);
    EXPECT_FALSE(pattern->isTouchPreventDefault_);
    EXPECT_EQ(pattern->touchHoverType_, TouchHoverAnimationType::NONE);
    /**
     * @tc.steps: step3. Mock GestureEvent info and set preventDefault to false
     * @tc.expected: Check the param value
     */
    pattern->InitClickEvent();
    GestureEvent clickInfo;
    clickInfo.SetPreventDefault(false);
    clickInfo.SetSourceDevice(SourceType::MOUSE);
    pattern->clickListener_->operator()(clickInfo);
    EXPECT_FALSE(pattern->isTouchPreventDefault_);
}
}