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
const std::string GROUP_NAME = "radioGroup";
const std::string GROUP_NAME1 = "radioGroup1";
const std::string GROUP_NAME_CHANGE = "radioGroupChange";
constexpr bool CHECKED = true;
constexpr int BIG_INT = 100000000;
constexpr int NEGATIVE_BIG_INT = -100000000;
constexpr int CHILD_NODE_ID = 100;
const std::optional<int32_t> INDICATOR_TYPE_TICK = 0;
const std::string RADIO_VALUE = "Radio";
const std::string EMPTY_VALUE = "";
} // namespace

class RadioValueTestNg : public testing::Test {
public:
};

/**
 * @tc.name: RadioValueTest001
 * @tc.desc: SetChangeValue and get value
 * @tc.type: FUNC
 */
HWTEST_F(RadioValueTestNg, RadioValueTest001, TestSize.Level1)
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
    EXPECT_EQ(isChecked, false);
}

/**
 * @tc.name: RadioValueTest002
 * @tc.desc: SetChangeValue and get value
 * @tc.type: FUNC
 */
HWTEST_F(RadioValueTestNg, RadioValueTest002, TestSize.Level1)
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
    EXPECT_EQ(isChecked, true);
}

/**
 * @tc.name: RadioValueTest003
 * @tc.desc: SetChangeValue and get value
 * @tc.type: FUNC
 */
HWTEST_F(RadioValueTestNg, RadioValueTest003, TestSize.Level1)
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
    EXPECT_EQ(isChecked, true);
}

/**
 * @tc.name: RadioValueTest004
 * @tc.desc: SetChangeValue and get value
 * @tc.type: FUNC
 */
HWTEST_F(RadioValueTestNg, RadioValueTest004, TestSize.Level1)
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
    EXPECT_EQ(isChecked, true);
}

/**
 * @tc.name: RadioValueTest005
 * @tc.desc: SetChangeValue and get value
 * @tc.type: FUNC
 */
HWTEST_F(RadioValueTestNg, RadioValueTest005, TestSize.Level1)
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
    EXPECT_EQ(isChecked, true);
}

/**
 * @tc.name: RadioValueTest006
 * @tc.desc: SetChangeValue and get value
 * @tc.type: FUNC
 */
HWTEST_F(RadioValueTestNg, RadioValueTest006, TestSize.Level1)
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
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->FireBuilder();
    /**
     * @tc.steps: step5. Test UseContentModifier
     */
    auto isUsed = pattern->UseContentModifier();
    EXPECT_EQ(true, isUsed);
}

/**
 * @tc.name: RadioValueTest007
 * @tc.desc: SetChangeValue and get value
 * @tc.type: FUNC
 */
HWTEST_F(RadioValueTestNg, RadioValueTest007, TestSize.Level1)
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
     * @tc.steps: step4. Set parameters to pattern builderFunc,
     * do not build node
     */
    pattern->SetBuilderFunc(node);
    /**
     * @tc.steps: step5. Test UseContentModifier
     */
    auto isUsed = pattern->UseContentModifier();
    EXPECT_EQ(false, isUsed);
}

/**
 * @tc.name: RadioValueTest008
 * @tc.desc: SetChangeValue and get value
 * @tc.type: FUNC
 */
HWTEST_F(RadioValueTestNg, RadioValueTest008, TestSize.Level1)
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
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->FireBuilder();
    /**
     * @tc.steps: step5. Test customNode_
     */
    auto buildNode = pattern->customNode_;
    /**
     * @tc.expected: Check the Radio child id
     */
    EXPECT_EQ(CHILD_NODE_ID, buildNode->GetId());
}

/**
 * @tc.name: RadioValueTest009
 * @tc.desc: SetChangeValue and get value
 * @tc.type: FUNC
 */
HWTEST_F(RadioValueTestNg, RadioValueTest009, TestSize.Level1)
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
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->FireBuilder();
    /**
     * @tc.steps: step5. Test customNode_
     */
    auto buildNode = pattern->customNode_;
    /**
     * @tc.expected: Check the Radio child id
     */
    EXPECT_EQ("child", buildNode->GetHostTag());
}

/**
 * @tc.name: RadioValueTest010
 * @tc.desc: Test UseContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(RadioValueTestNg, RadioValueTest010, TestSize.Level1)
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
     * @tc.steps: step5. Test customNode_
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
 * @tc.name: RadioValueTest011
 * @tc.desc: Test SetChangeValue
 * @tc.type: FUNC
 */
HWTEST_F(RadioValueTestNg, RadioValueTest011, TestSize.Level1)
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
    auto eventHub = frameNode->GetEventHub<NG::RadioEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetValue(VALUE);
    eventHub->SetEnabled(CHECKED);
    /**
     * @tc.steps: step3. Make builderFunc
     */
    auto node = [](RadioConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(VALUE, config.value_);
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
     * @tc.steps: step5. Test customNode_
     */
    auto buildNode = pattern->customNode_;
    /**
     * @tc.expected: Check the Radio child id
     */
    EXPECT_EQ("child", buildNode->GetHostTag());
    /**
     * @tc.steps: step6. Test SetChangeValue
     */
    radioModelNG.SetChangeValue(frameNode.GetRawPtr(), false);
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
 * @tc.name: RadioValueTest012
 * @tc.desc: Test SetChangeValue
 * @tc.type: FUNC
 */
HWTEST_F(RadioValueTestNg, RadioValueTest012, TestSize.Level1)
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
    auto eventHub = frameNode->GetEventHub<NG::RadioEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetValue(VALUE);
    eventHub->SetEnabled(CHECKED);
    /**
     * @tc.steps: step3. Make builderFunc
     */
    auto node = [](RadioConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(VALUE, config.value_);
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
     * @tc.steps: step5. Test customNode_
     */
    auto buildNode = pattern->customNode_;
    /**
     * @tc.expected: Check the Radio child id
     */
    EXPECT_EQ("child", buildNode->GetHostTag());
    /**
     * @tc.steps: step6. Test SetChangeValue
     */
    radioModelNG.SetChangeValue(frameNode.GetRawPtr(), true);
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
 * @tc.name: RadioValueTest013
 * @tc.desc: Test SetChangeValue
 * @tc.type: FUNC
 */
HWTEST_F(RadioValueTestNg, RadioValueTest013, TestSize.Level1)
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
    auto eventHub = frameNode->GetEventHub<NG::RadioEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetValue(VALUE);
    eventHub->SetEnabled(CHECKED);
    /**
     * @tc.steps: step3. Make builderFunc
     */
    auto node = [](RadioConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(VALUE, config.value_);
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
     * @tc.steps: step5. Test customNode_
     */
    auto buildNode = pattern->customNode_;
    /**
     * @tc.expected: Check the Radio child id
     */
    EXPECT_EQ("child", buildNode->GetHostTag());
    /**
     * @tc.steps: step6. Test SetChangeValue
     */
    radioModelNG.SetChangeValue(frameNode.GetRawPtr(), BIG_INT);
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
 * @tc.name: RadioValueTest014
 * @tc.desc: Test SetChangeValue
 * @tc.type: FUNC
 */
HWTEST_F(RadioValueTestNg, RadioValueTest014, TestSize.Level1)
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
    auto eventHub = frameNode->GetEventHub<NG::RadioEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetValue(VALUE);
    eventHub->SetEnabled(CHECKED);
    /**
     * @tc.steps: step3. Make builderFunc
     */
    auto node = [](RadioConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(VALUE, config.value_);
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
     * @tc.steps: step5. Test customNode_
     */
    auto buildNode = pattern->customNode_;
    /**
     * @tc.expected: Check the Radio child id
     */
    EXPECT_EQ("child", buildNode->GetHostTag());
    /**
     * @tc.steps: step6. Test SetChangeValue
     */
    radioModelNG.SetChangeValue(frameNode.GetRawPtr(), NEGATIVE_BIG_INT);
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
 * @tc.name: RadioValueTest015
 * @tc.desc: Test SetChangeValue
 * @tc.type: FUNC
 */
HWTEST_F(RadioValueTestNg, RadioValueTest015, TestSize.Level1)
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
    auto eventHub = frameNode->GetEventHub<NG::RadioEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetValue(VALUE);
    eventHub->SetEnabled(CHECKED);
    /**
     * @tc.steps: step3. Make builderFunc
     */
    auto node = [](RadioConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(VALUE, config.value_);
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
     * @tc.steps: step5. Test customNode_
     */
    auto buildNode = pattern->customNode_;
    /**
     * @tc.expected: Check the Radio child id
     */
    EXPECT_EQ("child", buildNode->GetHostTag());
    /**
     * @tc.steps: step6. Test SetChangeValue
     */
    radioModelNG.SetChangeValue(frameNode.GetRawPtr(), 0);
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
 * @tc.name: RadioValueTest016
 * @tc.desc: Test SetChangeValue
 * @tc.type: FUNC
 */
HWTEST_F(RadioValueTestNg, RadioValueTest016, TestSize.Level1)
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
    auto eventHub = frameNode->GetEventHub<NG::RadioEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetValue(VALUE);
    eventHub->SetEnabled(CHECKED);
    /**
     * @tc.steps: step3. Make builderFunc
     */
    auto node = [](RadioConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(VALUE, config.value_);
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
     * @tc.steps: step5. Test customNode_
     */
    auto buildNode = pattern->customNode_;
    /**
     * @tc.expected: Check the Radio child id
     */
    EXPECT_EQ("child", buildNode->GetHostTag());
    /**
     * @tc.steps: step6. Test SetChangeValue
     */
    radioModelNG.SetChangeValue(frameNode.GetRawPtr(), 1);
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
 * @tc.name: RadioValueTest017
 * @tc.desc: Test SetChangeValue
 * @tc.type: FUNC
 */
HWTEST_F(RadioValueTestNg, RadioValueTest017, TestSize.Level1)
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
    auto eventHub = frameNode->GetEventHub<NG::RadioEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetValue(VALUE);
    eventHub->SetEnabled(CHECKED);
    /**
     * @tc.steps: step3. Make builderFunc
     */
    auto node = [](RadioConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(VALUE, config.value_);
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
     * @tc.steps: step5. Test customNode_
     */
    auto buildNode = pattern->customNode_;
    /**
     * @tc.expected: Check the Radio child id
     */
    EXPECT_EQ("child", buildNode->GetHostTag());
    /**
     * @tc.steps: step6. Test SetChangeValue
     */
    radioModelNG.SetChangeValue(frameNode.GetRawPtr(), -1);
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
 * @tc.name: RadioValueTest018
 * @tc.desc: Test RadioModelNG::SetRadioValue & SetRadioGroup
 * @tc.type: FUNC
 */
HWTEST_F(RadioValueTestNg, RadioValueTest018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Radio node and set Model.
     */
    auto radioNode = FrameNode::CreateFrameNode(V2::RADIO_ETS_TAG, 1, AceType::MakeRefPtr<RadioPattern>());
    RadioModelNG radioModelNG;
    radioModelNG.SetRadioValue(AceType::RawPtr(radioNode), RADIO_VALUE);
    radioModelNG.SetRadioGroup(AceType::RawPtr(radioNode), RADIO_VALUE);
    auto radioPattern = radioNode->GetPattern<RadioPattern>();
    ASSERT_NE(radioPattern, nullptr);
    /**
     * @tc.steps: step1+. create Radio node and set Model not
     */
    auto radioNodeEx = FrameNode::CreateFrameNode(V2::RADIO_ETS_TAG, 1, AceType::MakeRefPtr<RadioPattern>());
    RadioModelNG radioModelNGEx;
    radioModelNGEx.SetRadioValue(AceType::RawPtr(radioNode), EMPTY_VALUE);
    radioModelNGEx.SetRadioGroup(AceType::RawPtr(radioNode), EMPTY_VALUE);
    auto radioPatternEx = radioNodeEx->GetPattern<RadioPattern>();
    ASSERT_NE(radioPatternEx, nullptr);
    auto eventHub = radioNodeEx->GetEventHub<NG::RadioEventHub>();
    ASSERT_NE(eventHub, nullptr);
    EXPECT_TRUE(eventHub->GetGroup().empty());
    EXPECT_TRUE(eventHub->GetValue().empty());
}
}