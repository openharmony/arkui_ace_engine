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
constexpr int32_t BIG_INT = 100000000;
constexpr int32_t NEGATIVE_BIG_INT = -100000000;
constexpr int32_t CHILD_NODE_ID = 100;
constexpr int32_t NEGATIVE_CHILD_NODE_ID = -10;
} // namespace

class LoadingProgressNodeTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();

protected:
    static RefPtr<FrameNode> CreateLoadingProgressNode(const Color& color);
};

void LoadingProgressNodeTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void LoadingProgressNodeTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

RefPtr<FrameNode> LoadingProgressNodeTestNg::CreateLoadingProgressNode(const Color& color)
{
    LoadingProgressModelNG modelNg;
    modelNg.Create();
    modelNg.SetColor(color);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    return AceType::DynamicCast<FrameNode>(element);
}

/**
 * @tc.name: LoadingProgressNodeTest001
 * @tc.desc: Test customNode
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressNodeTestNg, LoadingProgressNodeTest001, TestSize.Level1)
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
    /**
     * @tc.steps: step2. Set loadingProgressConfiguration
     */
    modelNg.SetEnableLoading(NEGATIVE_BIG_INT);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetEnabled(CHECKED);
    /**
     * @tc.steps: step3. Make builderFunc
     */
    auto node = [](LoadingProgressConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(CHECKED, config.enableloading_);
                EXPECT_EQ(CHECKED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", 1, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    loadingProgressPattern->SetBuilderFunc(node);
    loadingProgressPattern->FireBuilder();
    /**
     * @tc.steps: step5. Test customNode
     */
    auto buildNode = loadingProgressPattern->GetContentModifierNode();
    /**
     * @tc.expected: Check the LoadingProgress child id
     */
    EXPECT_EQ(1, buildNode->GetId());
}

/**
 * @tc.name: LoadingProgressNodeTest002
 * @tc.desc: Test customNode
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressNodeTestNg, LoadingProgressNodeTest002, TestSize.Level1)
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
    /**
     * @tc.steps: step2. Set loadingProgressConfiguration
     */
    modelNg.SetEnableLoading(NEGATIVE_BIG_INT);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetEnabled(CHECKED);
    /**
     * @tc.steps: step3. Make builderFunc
     */
    auto node = [](LoadingProgressConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(CHECKED, config.enableloading_);
                EXPECT_EQ(CHECKED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", NEGATIVE_CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    loadingProgressPattern->SetBuilderFunc(node);
    loadingProgressPattern->FireBuilder();
    /**
     * @tc.steps: step5. Test customNode
     */
    auto buildNode = loadingProgressPattern->GetContentModifierNode();
    /**
     * @tc.expected: Check the LoadingProgress child id
     */
    EXPECT_EQ(NEGATIVE_CHILD_NODE_ID, buildNode->GetId());
}

/**
 * @tc.name: LoadingProgressNodeTest003
 * @tc.desc: Test customNode
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressNodeTestNg, LoadingProgressNodeTest003, TestSize.Level1)
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
    /**
     * @tc.steps: step2. Set loadingProgressConfiguration
     */
    modelNg.SetEnableLoading(NEGATIVE_BIG_INT);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetEnabled(CHECKED);
    /**
     * @tc.steps: step3. Make builderFunc
     */
    auto node = [](LoadingProgressConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(CHECKED, config.enableloading_);
                EXPECT_EQ(CHECKED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", 0, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    loadingProgressPattern->SetBuilderFunc(node);
    loadingProgressPattern->FireBuilder();
    /**
     * @tc.steps: step5. Test customNode
     */
    auto buildNode = loadingProgressPattern->GetContentModifierNode();
    /**
     * @tc.expected: Check the LoadingProgress child id
     */
    EXPECT_EQ(0, buildNode->GetId());
}

/**
 * @tc.name: LoadingProgressNodeTest004
 * @tc.desc: Test customNode
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressNodeTestNg, LoadingProgressNodeTest004, TestSize.Level1)
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
    /**
     * @tc.steps: step2. Set loadingProgressConfiguration
     */
    modelNg.SetEnableLoading(NEGATIVE_BIG_INT);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetEnabled(CHECKED);
    /**
     * @tc.steps: step3. Make builderFunc
     */
    auto node = [](LoadingProgressConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(CHECKED, config.enableloading_);
                EXPECT_EQ(CHECKED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", BIG_INT, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    loadingProgressPattern->SetBuilderFunc(node);
    loadingProgressPattern->FireBuilder();
    /**
     * @tc.steps: step5. Test customNode
     */
    auto buildNode = loadingProgressPattern->GetContentModifierNode();
    /**
     * @tc.expected: Check the LoadingProgress child id
     */
    EXPECT_EQ(BIG_INT, buildNode->GetId());
}

/**
 * @tc.name: LoadingProgressNodeTest005
 * @tc.desc: Test customNode
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressNodeTestNg, LoadingProgressNodeTest005, TestSize.Level1)
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
    /**
     * @tc.steps: step2. Set loadingProgressConfiguration
     */
    modelNg.SetEnableLoading(NEGATIVE_BIG_INT);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetEnabled(CHECKED);
    /**
     * @tc.steps: step3. Make builderFunc
     */
    auto node = [](LoadingProgressConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(CHECKED, config.enableloading_);
                EXPECT_EQ(CHECKED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", NEGATIVE_BIG_INT, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    loadingProgressPattern->SetBuilderFunc(node);
    loadingProgressPattern->FireBuilder();
    /**
     * @tc.steps: step5. Test customNode
     */
    auto buildNode = loadingProgressPattern->GetContentModifierNode();
    /**
     * @tc.expected: Check the LoadingProgress child id
     */
    EXPECT_EQ(NEGATIVE_BIG_INT, buildNode->GetId());
}

/**
 * @tc.name: LoadingProgressNodeTest006
 * @tc.desc: Test customNode
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressNodeTestNg, LoadingProgressNodeTest006, TestSize.Level1)
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
    /**
     * @tc.steps: step2. Set loadingProgressConfiguration
     */
    modelNg.SetEnableLoading(NEGATIVE_BIG_INT);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetEnabled(CHECKED);
    /**
     * @tc.steps: step3. Make builderFunc
     */
    auto node = [](LoadingProgressConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(CHECKED, config.enableloading_);
                EXPECT_EQ(CHECKED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };

    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    loadingProgressPattern->SetBuilderFunc(node);
    loadingProgressPattern->FireBuilder();
    /**
     * @tc.steps: step5. Test customNode
     */
    auto buildNode = loadingProgressPattern->GetContentModifierNode();
    /**
     * @tc.expected: Check the LoadingProgress child id
     */
    EXPECT_EQ("", buildNode->GetHostTag());
}

/**
 * @tc.name: LoadingProgressNodeTest007
 * @tc.desc: Test customNode
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressNodeTestNg, LoadingProgressNodeTest007, TestSize.Level1)
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
    /**
     * @tc.steps: step2. Set loadingProgressConfiguration
     */
    modelNg.SetEnableLoading(NEGATIVE_BIG_INT);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetEnabled(CHECKED);
    /**
     * @tc.steps: step3. Make builderFunc
     */
    auto node = [](LoadingProgressConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(CHECKED, config.enableloading_);
                EXPECT_EQ(CHECKED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to loadingProgressModelNG builderFunc
     */
    modelNg.SetBuilderFunc(frameNode.GetRawPtr(), node);
    loadingProgressPattern->FireBuilder();
    /**
     * @tc.steps: step5. Test customNode
     */
    auto buildNode = loadingProgressPattern->GetContentModifierNode();
    /**
     * @tc.expected: Check the LoadingProgress child id
     */
    EXPECT_EQ("child", buildNode->GetHostTag());
}

/**
 * @tc.name: LoadingProgressNodeTest008
 * @tc.desc: Test UseContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressNodeTestNg, LoadingProgressNodeTest008, TestSize.Level1)
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
    /**
     * @tc.steps: step2. Set loadingProgressConfiguration
     */
    modelNg.SetEnableLoading(NEGATIVE_BIG_INT);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetEnabled(CHECKED);
    /**
     * @tc.steps: step3. Set parameters to loadingProgressModelNG builderFunc
     */
    modelNg.SetBuilderFunc(frameNode.GetRawPtr(), nullptr);
    loadingProgressPattern->FireBuilder();
    /**
     * @tc.steps: step4. Test customNode
     */
    auto isUsed = loadingProgressPattern->UseContentModifier();
    /**
     * @tc.expected: Check the LoadingProgress child id
     */
    EXPECT_EQ(false, isUsed);
}

/**
 * @tc.name: LoadingProgressNodeTest009
 * @tc.desc: Test UseContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressNodeTestNg, LoadingProgressNodeTest009, TestSize.Level1)
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
    /**
     * @tc.steps: step2. Set parameters to loadingProgressModelNG builderFunc
     */
    loadingProgressPattern->SetBuilderFunc(nullptr);
    loadingProgressPattern->FireBuilder();
    /**
     * @tc.steps: step3. Test UseContentModifier
     */
    auto isUsed = loadingProgressPattern->UseContentModifier();
    /**
     * @tc.expected: Check the LoadingProgress child id
     */
    EXPECT_EQ(false, isUsed);
}

/**
 * @tc.name: LoadingProgressNodeTest010
 * @tc.desc: Test UseContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressNodeTestNg, LoadingProgressNodeTest010, TestSize.Level1)
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
    /**
     * @tc.steps: step2. Set loadingProgressConfiguration
     */
    modelNg.SetEnableLoading(NEGATIVE_BIG_INT);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetEnabled(CHECKED);
    /**
     * @tc.steps: step3. Make builderFunc
     */
    auto node = [](LoadingProgressConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(CHECKED, config.enableloading_);
                EXPECT_EQ(CHECKED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to loadingProgressModelNG builderFunc
     */
    modelNg.SetBuilderFunc(frameNode.GetRawPtr(), node);
    loadingProgressPattern->FireBuilder();
    /**
     * @tc.steps: step5. Test customNode
     */
    auto buildNode = loadingProgressPattern->GetContentModifierNode();
    /**
     * @tc.expected: Check the LoadingProgress child id
     */
    EXPECT_EQ("child", buildNode->GetHostTag());
    /**
     * @tc.steps: step6. change builder func nullptr
     */
    modelNg.SetBuilderFunc(frameNode.GetRawPtr(), nullptr);
    loadingProgressPattern->FireBuilder();
    /**
     * @tc.steps: step7. Test UseContentModifier
     */
    auto isUsed = loadingProgressPattern->UseContentModifier();
    /**
     * @tc.expected: isUsed is false
     */
    EXPECT_EQ(false, isUsed);
}

/**
 * @tc.name: LoadingProgressNodeTest011
 * @tc.desc: Test UseContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressNodeTestNg, LoadingProgressNodeTest011, TestSize.Level1)
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
    /**
     * @tc.steps: step2. Set loadingProgressConfiguration
     */
    modelNg.SetEnableLoading(NEGATIVE_BIG_INT);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetEnabled(CHECKED);
    /**
     * @tc.steps: step3. Make builderFunc
     */
    auto node = [](LoadingProgressConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(CHECKED, config.enableloading_);
                EXPECT_EQ(CHECKED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to loadingProgressModelNG builderFunc
     */
    loadingProgressPattern->SetBuilderFunc(node);
    loadingProgressPattern->FireBuilder();
    /**
     * @tc.steps: step5. Test customNode
     */
    auto buildNode = loadingProgressPattern->GetContentModifierNode();
    /**
     * @tc.expected: Check the LoadingProgress child id
     */
    EXPECT_EQ("child", buildNode->GetHostTag());
    /**
     * @tc.steps: step6. change builder func nullptr
     */
    loadingProgressPattern->SetBuilderFunc(nullptr);
    loadingProgressPattern->FireBuilder();
    /**
     * @tc.steps: step7. Test UseContentModifier
     */
    auto isUsed = loadingProgressPattern->UseContentModifier();
    /**
     * @tc.expected: isUsed is false
     */
    EXPECT_EQ(false, isUsed);
}

/**
 * @tc.name: LoadingProgressNodeTest012
 * @tc.desc: Test contentModifierNode
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressNodeTestNg, LoadingProgressNodeTest012, TestSize.Level1)
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
    /**
     * @tc.steps: step2. Set loadingProgressConfiguration
     */
    modelNg.SetEnableLoading(NEGATIVE_BIG_INT);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetEnabled(CHECKED);
    /**
     * @tc.steps: step3. Make builderFunc
     */
    auto node = [](LoadingProgressConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(CHECKED, config.enableloading_);
                EXPECT_EQ(CHECKED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", 1, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    loadingProgressPattern->SetBuilderFunc(node);
    loadingProgressPattern->FireBuilder();
    /**
     * @tc.steps: step5. Test contentModifierNode
     */
    auto buildNode = loadingProgressPattern->GetContentModifierNode();
    /**
     * @tc.steps: step6. change builder func nullptr
     */
    loadingProgressPattern->SetBuilderFunc(nullptr);
    loadingProgressPattern->FireBuilder();
    /**
     * @tc.steps: step7. Test UseContentModifier
     */
    auto isUsed = loadingProgressPattern->UseContentModifier();
    /**
     * @tc.expected: isUsed is false
     */
    EXPECT_EQ(false, isUsed);
}

/**
 * @tc.name: LoadingProgressNodeTest013
 * @tc.desc: Test contentModifierNode
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressNodeTestNg, LoadingProgressNodeTest013, TestSize.Level1)
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
    /**
     * @tc.steps: step2. Set loadingProgressConfiguration
     */
    modelNg.SetEnableLoading(NEGATIVE_BIG_INT);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetEnabled(CHECKED);
    /**
     * @tc.steps: step3. Make builderFunc
     */
    auto node = [](LoadingProgressConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(CHECKED, config.enableloading_);
                EXPECT_EQ(CHECKED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", NEGATIVE_CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    loadingProgressPattern->SetBuilderFunc(node);
    loadingProgressPattern->FireBuilder();
    /**
     * @tc.steps: step5. Test contentModifierNode
     */
    auto buildNode = loadingProgressPattern->GetContentModifierNode();
    /**
     * @tc.expected: Check the LoadingProgress child id
     */
    EXPECT_EQ(NEGATIVE_CHILD_NODE_ID, buildNode->GetId());
    /**
     * @tc.steps: step6. change builder func nullptr
     */
    loadingProgressPattern->SetBuilderFunc(nullptr);
    loadingProgressPattern->FireBuilder();
    /**
     * @tc.steps: step7. Test UseContentModifier
     */
    auto isUsed = loadingProgressPattern->UseContentModifier();
    /**
     * @tc.expected: isUsed is false
     */
    EXPECT_EQ(false, isUsed);
}

/**
 * @tc.name: LoadingProgressNodeTest014
 * @tc.desc: Test contentModifierNode
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressNodeTestNg, LoadingProgressNodeTest014, TestSize.Level1)
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
    /**
     * @tc.steps: step2. Set loadingProgressConfiguration
     */
    modelNg.SetEnableLoading(NEGATIVE_BIG_INT);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetEnabled(CHECKED);
    /**
     * @tc.steps: step3. Make builderFunc
     */
    auto node = [](LoadingProgressConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(CHECKED, config.enableloading_);
                EXPECT_EQ(CHECKED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", 0, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    loadingProgressPattern->SetBuilderFunc(node);
    loadingProgressPattern->FireBuilder();
    /**
     * @tc.steps: step5. Test contentModifierNode
     */
    auto buildNode = loadingProgressPattern->GetContentModifierNode();
    /**
     * @tc.expected: Check the LoadingProgress child id
     */
    EXPECT_EQ(0, buildNode->GetId());
    /**
     * @tc.steps: step6. change builder func nullptr
     */
    loadingProgressPattern->SetBuilderFunc(nullptr);
    loadingProgressPattern->FireBuilder();
    /**
     * @tc.steps: step7. Test UseContentModifier
     */
    auto isUsed = loadingProgressPattern->UseContentModifier();
    /**
     * @tc.expected: isUsed is false
     */
    EXPECT_EQ(false, isUsed);
}

/**
 * @tc.name: LoadingProgressNodeTest015
 * @tc.desc: Test contentModifierNode
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressNodeTestNg, LoadingProgressNodeTest015, TestSize.Level1)
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
    /**
     * @tc.steps: step2. Set loadingProgressConfiguration
     */
    modelNg.SetEnableLoading(NEGATIVE_BIG_INT);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetEnabled(CHECKED);
    /**
     * @tc.steps: step3. Make builderFunc
     */
    auto node = [](LoadingProgressConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(CHECKED, config.enableloading_);
                EXPECT_EQ(CHECKED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", BIG_INT, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    loadingProgressPattern->SetBuilderFunc(node);
    loadingProgressPattern->FireBuilder();
    /**
     * @tc.steps: step5. Test contentModifierNode
     */
    auto buildNode = loadingProgressPattern->GetContentModifierNode();
    /**
     * @tc.expected: Check the LoadingProgress child id
     */
    EXPECT_EQ(BIG_INT, buildNode->GetId());
    /**
     * @tc.steps: step6. change builder func nullptr
     */
    loadingProgressPattern->SetBuilderFunc(nullptr);
    loadingProgressPattern->FireBuilder();
    /**
     * @tc.steps: step7. Test UseContentModifier
     */
    auto isUsed = loadingProgressPattern->UseContentModifier();
    /**
     * @tc.expected: isUsed is false
     */
    EXPECT_EQ(false, isUsed);
}

/**
 * @tc.name: LoadingProgressNodeTest016
 * @tc.desc: Test contentModifierNode
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressNodeTestNg, LoadingProgressNodeTest016, TestSize.Level1)
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
    /**
     * @tc.steps: step2. Set loadingProgressConfiguration
     */
    modelNg.SetEnableLoading(NEGATIVE_BIG_INT);
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetEnabled(CHECKED);
    /**
     * @tc.steps: step3. Make builderFunc
     */
    auto node = [](LoadingProgressConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(CHECKED, config.enableloading_);
                EXPECT_EQ(CHECKED, config.enabled_);
                RefPtr<FrameNode> child =
                    AceType::MakeRefPtr<FrameNode>("child", NEGATIVE_BIG_INT, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    loadingProgressPattern->SetBuilderFunc(node);
    loadingProgressPattern->FireBuilder();
    /**
     * @tc.steps: step5. Test contentModifierNode
     */
    auto buildNode = loadingProgressPattern->GetContentModifierNode();
    /**
     * @tc.expected: Check the LoadingProgress child id
     */
    EXPECT_EQ(NEGATIVE_BIG_INT, buildNode->GetId());
    /**
     * @tc.steps: step6. change builder func nullptr
     */
    loadingProgressPattern->SetBuilderFunc(nullptr);
    loadingProgressPattern->FireBuilder();
    /**
     * @tc.steps: step7. Test UseContentModifier
     */
    auto isUsed = loadingProgressPattern->UseContentModifier();
    /**
     * @tc.expected: isUsed is false
     */
    EXPECT_EQ(false, isUsed);
}
} // namespace OHOS::Ace::NG