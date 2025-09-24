/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include <algorithm>
#include <cstddef>
#include <optional>

#include "gtest/gtest.h"

#define protected public
#define private public
#include "test/mock/base/mock_system_properties.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "core/components_ng/pattern/container_picker/container_picker_layout_property.h"
#include "core/components_ng/pattern/container_picker/container_picker_model.h"
#include "core/components_ng/pattern/container_picker/container_picker_pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class ContainerPickerTest : public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
};

void ContainerPickerTest::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
}

void ContainerPickerTest::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void ContainerPickerTest::SetUp() {}

void ContainerPickerTest::TearDown() {}

/**
 * @tc.name: ContainerPickerLayoutPropertyTest001
 * @tc.desc: Test ContainerPickerModel SetCanLoop
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerTest, ContainerPickerLayoutPropertyTest001, TestSize.Level0)
{
    /**
    * @tc.steps: step1. create picker and get frameNode.
    */
    ContainerPickerModel picker;
    picker.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    EXPECT_NE(frameNode, nullptr);

    /**
    * @tc.steps: step2. set canLoop and get value from ContainerPickerLayoutProperty.
    * @tc.expected: step2. the value is the same with setting.
    */
    auto layoutProperty = frameNode->GetLayoutProperty<ContainerPickerLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    picker.SetCanLoop(false);
    EXPECT_EQ(layoutProperty->GetCanLoopValue(), false);
}

/**
 * @tc.name: ContainerPickerLayoutPropertyTest002
 * @tc.desc: Test ContainerPickerModel SetEnableHapticFeedback
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerTest, ContainerPickerLayoutPropertyTest002, TestSize.Level0)
{
    /**
    * @tc.steps: step1. create picker and get frameNode.
    */
    ContainerPickerModel picker;
    picker.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    EXPECT_NE(frameNode, nullptr);

    /**
    * @tc.steps: step2. set enableHapticFeedback and get value from ContainerPickerLayoutProperty.
    * @tc.expected: step2. the value is the same with setting.
    */
    auto layoutProperty = frameNode->GetLayoutProperty<ContainerPickerLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    picker.SetEnableHapticFeedback(false);
    EXPECT_EQ(layoutProperty->GetEnableHapticFeedbackValue(), false);
}

/**
 * @tc.name: ContainerPickerCreateAnimation001
 * @tc.desc: Test ContainerPicker CreateAnimation
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerTest, ContainerPickerCreateAnimation001, TestSize.Level0)
{
    /**
    * @tc.steps: step1. create picker and get frameNode.
    * @tc.expected: step2. When creating the node，animationCreated_ will be set to true.
    */
    ContainerPickerModel picker;
    picker.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    EXPECT_NE(frameNode, nullptr);

    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->animationCreated_, true);
}

}
