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

#include "core/components_ng/pattern/loading_progress/loading_progress_base.h"

#define private public
#define protected public
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/loading_progress/loading_progress_layout_algorithm.h"
#include "core/components_ng/pattern/loading_progress/loading_progress_layout_property.h"
#include "core/components_ng/pattern/loading_progress/loading_progress_model_ng.h"
#include "core/components_ng/pattern/loading_progress/loading_progress_paint_property.h"
#include "core/components_ng/pattern/loading_progress/loading_progress_pattern.h"
#include "core/components_ng/pattern/refresh/refresh_animation_state.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const Color COLOR_DEFAULT = Color::RED;
constexpr bool CHECKED = true;
constexpr bool UNCHECKED = false;
constexpr int32_t BIG_INT = 100000000;
constexpr int32_t NEGATIVE_BIG_INT = -100000000;
constexpr int32_t CHILD_NODE_ID = 100;
constexpr int32_t NORMAL_INT = 2;
constexpr int32_t NEGATIVE_INT = -2;
} // namespace

class LoadingProgressSetBuilderTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();

protected:
    static RefPtr<FrameNode> CreateLoadingProgressNode(const Color& color);
};

void LoadingProgressSetBuilderTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void LoadingProgressSetBuilderTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

RefPtr<FrameNode> LoadingProgressSetBuilderTestNg::CreateLoadingProgressNode(const Color& color)
{
    LoadingProgressModelNG modelNg;
    modelNg.Create();
    modelNg.SetColor(color);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    return AceType::DynamicCast<FrameNode>(element);
}

/**
 * @tc.name: LoadingProgressSetBuilderTest001
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressSetBuilderTestNg, LoadingProgressSetBuilderTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init LoadingProgress node
     */
    LoadingProgressModelNG modelNg;
    modelNg.Create();
    RefPtr<FrameNode> frameNode = CreateLoadingProgressNode(COLOR_DEFAULT);
    ASSERT_NE(frameNode, nullptr);
    auto loadingProgressPattern = frameNode->GetPattern<LoadingProgressPattern>();
    ASSERT_NE(loadingProgressPattern, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    ASSERT_NE(eventHub, nullptr);
    /**
     * @tc.steps: step2. Set LoadingProgressConfiguration
     */
    modelNg.SetEnableLoading(CHECKED);
    eventHub->SetEnabled(CHECKED);
    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [](LoadingProgressConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(CHECKED, config.enableloading_);
                EXPECT_EQ(CHECKED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    loadingProgressPattern->SetBuilderFunc(node);
    loadingProgressPattern->BuildContentModifierNode();
}

/**
 * @tc.name: LoadingProgressSetBuilderTest002
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressSetBuilderTestNg, LoadingProgressSetBuilderTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init LoadingProgress node
     */
    LoadingProgressModelNG modelNg;
    modelNg.Create();
    RefPtr<FrameNode> frameNode = CreateLoadingProgressNode(COLOR_DEFAULT);
    ASSERT_NE(frameNode, nullptr);
    auto loadingProgressPattern = frameNode->GetPattern<LoadingProgressPattern>();
    ASSERT_NE(loadingProgressPattern, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    ASSERT_NE(eventHub, nullptr);
    /**
     * @tc.steps: step2. Set LoadingProgressConfiguration
     */
    modelNg.SetEnableLoading(CHECKED);
    eventHub->SetEnabled(UNCHECKED);
    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [](LoadingProgressConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(CHECKED, config.enableloading_);
                EXPECT_EQ(UNCHECKED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    loadingProgressPattern->SetBuilderFunc(node);
    loadingProgressPattern->BuildContentModifierNode();
}

/**
 * @tc.name: LoadingProgressSetBuilderTest003
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressSetBuilderTestNg, LoadingProgressSetBuilderTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init LoadingProgress node
     */
    LoadingProgressModelNG modelNg;
    modelNg.Create();
    RefPtr<FrameNode> frameNode = CreateLoadingProgressNode(COLOR_DEFAULT);
    ASSERT_NE(frameNode, nullptr);
    auto loadingProgressPattern = frameNode->GetPattern<LoadingProgressPattern>();
    ASSERT_NE(loadingProgressPattern, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    ASSERT_NE(eventHub, nullptr);
    /**
     * @tc.steps: step2. Set LoadingProgressConfiguration
     */
    modelNg.SetEnableLoading(CHECKED);
    eventHub->SetEnabled(0);
    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [](LoadingProgressConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(CHECKED, config.enableloading_);
                EXPECT_EQ(UNCHECKED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    loadingProgressPattern->SetBuilderFunc(node);
    loadingProgressPattern->BuildContentModifierNode();
}

/**
 * @tc.name: LoadingProgressSetBuilderTest004
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressSetBuilderTestNg, LoadingProgressSetBuilderTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init LoadingProgress node
     */
    LoadingProgressModelNG modelNg;
    modelNg.Create();
    RefPtr<FrameNode> frameNode = CreateLoadingProgressNode(COLOR_DEFAULT);
    ASSERT_NE(frameNode, nullptr);
    auto loadingProgressPattern = frameNode->GetPattern<LoadingProgressPattern>();
    ASSERT_NE(loadingProgressPattern, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    ASSERT_NE(eventHub, nullptr);
    /**
     * @tc.steps: step2. Set LoadingProgressConfiguration
     */
    modelNg.SetEnableLoading(CHECKED);
    eventHub->SetEnabled(1);
    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [](LoadingProgressConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(CHECKED, config.enableloading_);
                EXPECT_EQ(CHECKED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    loadingProgressPattern->SetBuilderFunc(node);
    loadingProgressPattern->BuildContentModifierNode();
}

/**
 * @tc.name: LoadingProgressSetBuilderTest005
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressSetBuilderTestNg, LoadingProgressSetBuilderTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init LoadingProgress node
     */
    LoadingProgressModelNG modelNg;
    modelNg.Create();
    RefPtr<FrameNode> frameNode = CreateLoadingProgressNode(COLOR_DEFAULT);
    ASSERT_NE(frameNode, nullptr);
    auto loadingProgressPattern = frameNode->GetPattern<LoadingProgressPattern>();
    ASSERT_NE(loadingProgressPattern, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    ASSERT_NE(eventHub, nullptr);
    /**
     * @tc.steps: step2. Set LoadingProgressConfiguration
     */
    modelNg.SetEnableLoading(CHECKED);
    eventHub->SetEnabled(-1);
    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [](LoadingProgressConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(CHECKED, config.enableloading_);
                EXPECT_EQ(CHECKED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    loadingProgressPattern->SetBuilderFunc(node);
    loadingProgressPattern->BuildContentModifierNode();
}

/**
 * @tc.name: LoadingProgressSetBuilderTest006
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressSetBuilderTestNg, LoadingProgressSetBuilderTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init LoadingProgress node
     */
    LoadingProgressModelNG modelNg;
    modelNg.Create();
    RefPtr<FrameNode> frameNode = CreateLoadingProgressNode(COLOR_DEFAULT);
    ASSERT_NE(frameNode, nullptr);
    auto loadingProgressPattern = frameNode->GetPattern<LoadingProgressPattern>();
    ASSERT_NE(loadingProgressPattern, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    ASSERT_NE(eventHub, nullptr);
    /**
     * @tc.steps: step2. Set LoadingProgressConfiguration
     */
    modelNg.SetEnableLoading(1);
    eventHub->SetEnabled(CHECKED);
    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [](LoadingProgressConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(CHECKED, config.enableloading_);
                EXPECT_EQ(CHECKED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    loadingProgressPattern->SetBuilderFunc(node);
    loadingProgressPattern->BuildContentModifierNode();
}

/**
 * @tc.name: LoadingProgressSetBuilderTest007
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressSetBuilderTestNg, LoadingProgressSetBuilderTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init LoadingProgress node
     */
    LoadingProgressModelNG modelNg;
    modelNg.Create();
    RefPtr<FrameNode> frameNode = CreateLoadingProgressNode(COLOR_DEFAULT);
    ASSERT_NE(frameNode, nullptr);
    auto loadingProgressPattern = frameNode->GetPattern<LoadingProgressPattern>();
    ASSERT_NE(loadingProgressPattern, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    ASSERT_NE(eventHub, nullptr);
    /**
     * @tc.steps: step2. Set LoadingProgressConfiguration
     */
    modelNg.SetEnableLoading(0);
    eventHub->SetEnabled(CHECKED);
    loadingProgressPattern->BuildContentModifierNode();
    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [](LoadingProgressConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(UNCHECKED, config.enableloading_);
                EXPECT_EQ(CHECKED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    loadingProgressPattern->SetBuilderFunc(node);
}

/**
 * @tc.name: LoadingProgressSetBuilderTest008
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressSetBuilderTestNg, LoadingProgressSetBuilderTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init LoadingProgress node
     */
    LoadingProgressModelNG modelNg;
    modelNg.Create();
    RefPtr<FrameNode> frameNode = CreateLoadingProgressNode(COLOR_DEFAULT);
    ASSERT_NE(frameNode, nullptr);
    auto loadingProgressPattern = frameNode->GetPattern<LoadingProgressPattern>();
    ASSERT_NE(loadingProgressPattern, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    ASSERT_NE(eventHub, nullptr);
    /**
     * @tc.steps: step2. Set LoadingProgressConfiguration
     */
    modelNg.SetEnableLoading(-1);
    eventHub->SetEnabled(CHECKED);
    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [](LoadingProgressConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(CHECKED, config.enableloading_);
                EXPECT_EQ(CHECKED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    loadingProgressPattern->SetBuilderFunc(node);
    loadingProgressPattern->BuildContentModifierNode();
}

/**
 * @tc.name: LoadingProgressSetBuilderTest009
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressSetBuilderTestNg, LoadingProgressSetBuilderTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init LoadingProgress node
     */
    LoadingProgressModelNG modelNg;
    modelNg.Create();
    RefPtr<FrameNode> frameNode = CreateLoadingProgressNode(COLOR_DEFAULT);
    ASSERT_NE(frameNode, nullptr);
    auto loadingProgressPattern = frameNode->GetPattern<LoadingProgressPattern>();
    ASSERT_NE(loadingProgressPattern, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    ASSERT_NE(eventHub, nullptr);
    /**
     * @tc.steps: step2. Set LoadingProgressConfiguration
     */
    modelNg.SetEnableLoading(CHECKED);
    eventHub->SetEnabled(BIG_INT);
    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [](LoadingProgressConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(CHECKED, config.enableloading_);
                EXPECT_EQ(CHECKED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    loadingProgressPattern->SetBuilderFunc(node);
    loadingProgressPattern->BuildContentModifierNode();
}

/**
 * @tc.name: LoadingProgressSetBuilderTest010
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressSetBuilderTestNg, LoadingProgressSetBuilderTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init LoadingProgress node
     */
    LoadingProgressModelNG modelNg;
    modelNg.Create();
    RefPtr<FrameNode> frameNode = CreateLoadingProgressNode(COLOR_DEFAULT);
    ASSERT_NE(frameNode, nullptr);
    auto loadingProgressPattern = frameNode->GetPattern<LoadingProgressPattern>();
    ASSERT_NE(loadingProgressPattern, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    ASSERT_NE(eventHub, nullptr);
    /**
     * @tc.steps: step2. Set LoadingProgressConfiguration
     */
    modelNg.SetEnableLoading(CHECKED);
    eventHub->SetEnabled(NEGATIVE_BIG_INT);
    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [](LoadingProgressConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(CHECKED, config.enableloading_);
                EXPECT_EQ(CHECKED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    loadingProgressPattern->SetBuilderFunc(node);
    loadingProgressPattern->BuildContentModifierNode();
}

/**
 * @tc.name: LoadingProgressSetBuilderTest011
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressSetBuilderTestNg, LoadingProgressSetBuilderTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init LoadingProgress node
     */
    LoadingProgressModelNG modelNg;
    modelNg.Create();
    RefPtr<FrameNode> frameNode = CreateLoadingProgressNode(COLOR_DEFAULT);
    ASSERT_NE(frameNode, nullptr);
    auto loadingProgressPattern = frameNode->GetPattern<LoadingProgressPattern>();
    ASSERT_NE(loadingProgressPattern, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    ASSERT_NE(eventHub, nullptr);
    /**
     * @tc.steps: step2. Set LoadingProgressConfiguration
     */
    modelNg.SetEnableLoading(BIG_INT);
    eventHub->SetEnabled(CHECKED);
    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [](LoadingProgressConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(CHECKED, config.enableloading_);
                EXPECT_EQ(CHECKED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    loadingProgressPattern->SetBuilderFunc(node);
    loadingProgressPattern->BuildContentModifierNode();
}

/**
 * @tc.name: LoadingProgressSetBuilderTest012
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressSetBuilderTestNg, LoadingProgressSetBuilderTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init LoadingProgress node
     */
    LoadingProgressModelNG modelNg;
    modelNg.Create();
    RefPtr<FrameNode> frameNode = CreateLoadingProgressNode(COLOR_DEFAULT);
    ASSERT_NE(frameNode, nullptr);
    auto loadingProgressPattern = frameNode->GetPattern<LoadingProgressPattern>();
    ASSERT_NE(loadingProgressPattern, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    ASSERT_NE(eventHub, nullptr);
    /**
     * @tc.steps: step2. Set LoadingProgressConfiguration
     */
    modelNg.SetEnableLoading(NEGATIVE_BIG_INT);
    eventHub->SetEnabled(CHECKED);
    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [](LoadingProgressConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(CHECKED, config.enableloading_);
                EXPECT_EQ(CHECKED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    loadingProgressPattern->SetBuilderFunc(node);
    loadingProgressPattern->BuildContentModifierNode();
}

/**
 * @tc.name: LoadingProgressSetBuilderTest013
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressSetBuilderTestNg, LoadingProgressSetBuilderTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init LoadingProgress node
     */
    LoadingProgressModelNG modelNg;
    modelNg.Create();
    RefPtr<FrameNode> frameNode = CreateLoadingProgressNode(COLOR_DEFAULT);
    ASSERT_NE(frameNode, nullptr);
    auto loadingProgressPattern = frameNode->GetPattern<LoadingProgressPattern>();
    ASSERT_NE(loadingProgressPattern, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    ASSERT_NE(eventHub, nullptr);
    /**
     * @tc.steps: step2. Set LoadingProgressConfiguration
     */
    modelNg.SetEnableLoading(NORMAL_INT);
    eventHub->SetEnabled(CHECKED);
    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [](LoadingProgressConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(CHECKED, config.enableloading_);
                EXPECT_EQ(CHECKED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    loadingProgressPattern->SetBuilderFunc(node);
    loadingProgressPattern->BuildContentModifierNode();
}

/**
 * @tc.name: LoadingProgressSetBuilderTest014
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressSetBuilderTestNg, LoadingProgressSetBuilderTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init LoadingProgress node
     */
    LoadingProgressModelNG modelNg;
    modelNg.Create();
    RefPtr<FrameNode> frameNode = CreateLoadingProgressNode(COLOR_DEFAULT);
    ASSERT_NE(frameNode, nullptr);
    auto loadingProgressPattern = frameNode->GetPattern<LoadingProgressPattern>();
    ASSERT_NE(loadingProgressPattern, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    ASSERT_NE(eventHub, nullptr);
    /**
     * @tc.steps: step2. Set LoadingProgressConfiguration
     */
    modelNg.SetEnableLoading(CHECKED);
    eventHub->SetEnabled(NORMAL_INT);
    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [](LoadingProgressConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(CHECKED, config.enableloading_);
                EXPECT_EQ(CHECKED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    loadingProgressPattern->SetBuilderFunc(node);
    loadingProgressPattern->BuildContentModifierNode();
}

/**
 * @tc.name: LoadingProgressSetBuilderTest015
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressSetBuilderTestNg, LoadingProgressSetBuilderTest015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init LoadingProgress node
     */
    LoadingProgressModelNG modelNg;
    modelNg.Create();
    RefPtr<FrameNode> frameNode = CreateLoadingProgressNode(COLOR_DEFAULT);
    ASSERT_NE(frameNode, nullptr);
    auto loadingProgressPattern = frameNode->GetPattern<LoadingProgressPattern>();
    ASSERT_NE(loadingProgressPattern, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    ASSERT_NE(eventHub, nullptr);
    /**
     * @tc.steps: step2. Set LoadingProgressConfiguration
     */
    modelNg.SetEnableLoading(NEGATIVE_BIG_INT);
    eventHub->SetEnabled(NEGATIVE_BIG_INT);
    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [](LoadingProgressConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(CHECKED, config.enableloading_);
                EXPECT_EQ(CHECKED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    loadingProgressPattern->SetBuilderFunc(node);
    loadingProgressPattern->BuildContentModifierNode();
}

/**
 * @tc.name: LoadingProgressSetBuilderTest016
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressSetBuilderTestNg, LoadingProgressSetBuilderTest016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init LoadingProgress node
     */
    LoadingProgressModelNG modelNg;
    modelNg.Create();
    RefPtr<FrameNode> frameNode = CreateLoadingProgressNode(COLOR_DEFAULT);
    ASSERT_NE(frameNode, nullptr);
    auto loadingProgressPattern = frameNode->GetPattern<LoadingProgressPattern>();
    ASSERT_NE(loadingProgressPattern, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    ASSERT_NE(eventHub, nullptr);
    /**
     * @tc.steps: step2. Set LoadingProgressConfiguration
     */
    modelNg.SetEnableLoading(NEGATIVE_INT);
    eventHub->SetEnabled(CHECKED);
    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [](LoadingProgressConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(CHECKED, config.enableloading_);
                EXPECT_EQ(CHECKED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    loadingProgressPattern->SetBuilderFunc(node);
    loadingProgressPattern->BuildContentModifierNode();
}

/**
 * @tc.name: LoadingProgressSetBuilderTest017
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressSetBuilderTestNg, LoadingProgressSetBuilderTest017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init LoadingProgress node
     */
    LoadingProgressModelNG modelNg;
    modelNg.Create();
    RefPtr<FrameNode> frameNode = CreateLoadingProgressNode(COLOR_DEFAULT);
    ASSERT_NE(frameNode, nullptr);
    auto loadingProgressPattern = frameNode->GetPattern<LoadingProgressPattern>();
    ASSERT_NE(loadingProgressPattern, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    ASSERT_NE(eventHub, nullptr);
    /**
     * @tc.steps: step2. Set LoadingProgressConfiguration
     */
    modelNg.SetEnableLoading(CHECKED);
    eventHub->SetEnabled(NEGATIVE_INT);
    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [](LoadingProgressConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(CHECKED, config.enableloading_);
                EXPECT_EQ(CHECKED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    loadingProgressPattern->SetBuilderFunc(node);
    loadingProgressPattern->BuildContentModifierNode();
}
} // namespace OHOS::Ace::NG