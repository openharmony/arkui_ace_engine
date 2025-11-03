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
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "core/components_ng/pattern/container_picker/container_picker_event_hub.h"
#include "core/components_ng/pattern/container_picker/container_picker_layout_property.h"
#include "core/components_ng/pattern/container_picker/container_picker_model.h"
#include "core/components_ng/pattern/container_picker/container_picker_pattern.h"
#include "core/components_ng/pattern/container_picker/container_picker_theme.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class ContainerPickerEventHubTest : public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    RefPtr<FrameNode> CreateContainerPickerNode();
};

void ContainerPickerEventHubTest::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<ContainerPickerTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
}

void ContainerPickerEventHubTest::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    TestNG::TearDownTestSuite();
}

void ContainerPickerEventHubTest::SetUp() {}

void ContainerPickerEventHubTest::TearDown() {}

RefPtr<FrameNode> ContainerPickerEventHubTest::CreateContainerPickerNode()
{
    ContainerPickerModel picker;
    picker.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    EXPECT_NE(frameNode, nullptr);
    return frameNode;
}

/**
 * @tc.name: ContainerPickerEventHubTest_SetOnChange001
 * @tc.desc: Test SetOnChange function
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerEventHubTest, ContainerPickerEventHubTest_SetOnChange001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get event hub.
     */
    auto frameNode = CreateContainerPickerNode();
    auto eventHub = frameNode->GetEventHub<ContainerPickerEventHub>();
    ASSERT_NE(eventHub, nullptr);

    /**
     * @tc.steps: step2. set OnChange event and test FireChangeEvent.
     * @tc.expected: step2. the event is triggered with correct index.
     */
    int32_t testIndex = -1;
    eventHub->SetOnChange([&testIndex](const double& index) { testIndex = static_cast<int32_t>(index); });

    eventHub->FireChangeEvent(5.0);
    EXPECT_EQ(testIndex, 5);

    eventHub->FireChangeEvent(10.0);
    EXPECT_EQ(testIndex, 10);
}

/**
 * @tc.name: ContainerPickerEventHubTest_SetOnScrollStop001
 * @tc.desc: Test SetOnScrollStop function
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerEventHubTest, ContainerPickerEventHubTest_SetOnScrollStop001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get event hub.
     */
    auto frameNode = CreateContainerPickerNode();
    auto eventHub = frameNode->GetEventHub<ContainerPickerEventHub>();
    ASSERT_NE(eventHub, nullptr);

    /**
     * @tc.steps: step2. set OnScrollStop event and test FireScrollStopEvent.
     * @tc.expected: step2. the event is triggered with correct index.
     */
    int32_t testIndex = -1;
    eventHub->SetOnScrollStop([&testIndex](const double& index) { testIndex = static_cast<int32_t>(index); });

    eventHub->FireScrollStopEvent(5.0);
    EXPECT_EQ(testIndex, 5);

    eventHub->FireScrollStopEvent(10.0);
    EXPECT_EQ(testIndex, 10);
}

/**
 * @tc.name: ContainerPickerEventHubTest_NoEventCallback001
 * @tc.desc: Test FireChangeEvent with no event callback set
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerEventHubTest, ContainerPickerEventHubTest_NoEventCallback001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get event hub.
     */
    auto frameNode = CreateContainerPickerNode();
    auto eventHub = frameNode->GetEventHub<ContainerPickerEventHub>();
    ASSERT_NE(eventHub, nullptr);

    /**
     * @tc.steps: step2. test FireChangeEvent with no callback set.
     * @tc.expected: step2. no crash and returns normally.
     */
    eventHub->FireChangeEvent(5.0);
    // Just verify no crash occurs
    EXPECT_TRUE(true);
}

/**
 * @tc.name: ContainerPickerEventHubTest_NoScrollStopCallback001
 * @tc.desc: Test FireScrollStopEvent with no event callback set
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerEventHubTest, ContainerPickerEventHubTest_NoScrollStopCallback001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get event hub.
     */
    auto frameNode = CreateContainerPickerNode();
    auto eventHub = frameNode->GetEventHub<ContainerPickerEventHub>();
    ASSERT_NE(eventHub, nullptr);

    /**
     * @tc.steps: step2. test FireScrollStopEvent with no callback set.
     * @tc.expected: step2. no crash and returns normally.
     */
    eventHub->FireScrollStopEvent(5.0);
    // Just verify no crash occurs
    EXPECT_TRUE(true);
}

} // namespace OHOS::Ace::NG
