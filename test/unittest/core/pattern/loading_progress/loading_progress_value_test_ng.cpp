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
const std::string VALUE = "loadingProgress";
constexpr bool CHECKED = true;
constexpr int32_t BIG_INT = 100000000;
constexpr int32_t NEGATIVE_BIG_INT = -100000000;
constexpr int32_t CHILD_NODE_ID = 100;
constexpr int32_t NEGATIVE_CHILD_NODE_ID = -10;
} // namespace

class LoadingProgressValueTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();

protected:
    static RefPtr<FrameNode> CreateLoadingProgressNode(const Color& color);
};

void LoadingProgressValueTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void LoadingProgressValueTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

RefPtr<FrameNode> LoadingProgressValueTestNg::CreateLoadingProgressNode(const Color& color)
{
    LoadingProgressModelNG modelNg;
    modelNg.Create();
    modelNg.SetColor(color);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    return AceType::DynamicCast<FrameNode>(element);
}

/**
 * @tc.name: LoadingProgressValueTest001
 * @tc.desc: SetChangeValue and get value
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressValueTestNg, LoadingProgressValueTest001, TestSize.Level1)
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
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    loadingProgressPattern->SetBuilderFunc(node);
    loadingProgressPattern->FireBuilder();
    /**
     * @tc.steps: step5. Test UseContentModifier
     */
    auto isUsed = loadingProgressPattern->UseContentModifier();
    EXPECT_EQ(true, isUsed);
}

/**
 * @tc.name: LoadingProgressValueTest002
 * @tc.desc: SetChangeValue and get value
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressValueTestNg, LoadingProgressValueTest002, TestSize.Level1)
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
     * @tc.steps: step4. Set parameters to pattern builderFunc,
     * do not build node
     */
    loadingProgressPattern->SetBuilderFunc(node);
    /**
     * @tc.steps: step5. Test UseContentModifier
     */
    auto isUsed = loadingProgressPattern->UseContentModifier();
    EXPECT_EQ(false, isUsed);
}

/**
 * @tc.name: LoadingProgressValueTest003
 * @tc.desc: SetChangeValue and get value
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressValueTestNg, LoadingProgressValueTest003, TestSize.Level1)
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
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    loadingProgressPattern->SetBuilderFunc(node);
    loadingProgressPattern->FireBuilder();
    /**
     * @tc.steps: step5. Test contentModifierNode_
     */
    auto buildNode = loadingProgressPattern->GetContentModifierNode();
    /**
     * @tc.expected: Check the LoadingProgress child id
     */
    EXPECT_EQ(CHILD_NODE_ID, buildNode->GetId());
}

/**
 * @tc.name: LoadingProgressValueTest004
 * @tc.desc: SetChangeValue and get value
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressValueTestNg, LoadingProgressValueTest004, TestSize.Level1)
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
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    loadingProgressPattern->SetBuilderFunc(node);
    loadingProgressPattern->FireBuilder();
    /**
     * @tc.steps: step5. Test contentModifierNode_
     */
    auto buildNode = loadingProgressPattern->GetContentModifierNode();
    /**
     * @tc.expected: Check the LoadingProgress child id
     */
    EXPECT_EQ("child", buildNode->GetHostTag());
}

/**
 * @tc.name: LoadingProgressValueTest005
 * @tc.desc: Test UseContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressValueTestNg, LoadingProgressValueTest005, TestSize.Level1)
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
     * @tc.steps: step5. Test contentModifierNode_
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
 * @tc.name: LoadingProgressValueTest006
 * @tc.desc: SetChangeValue and get value
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressValueTestNg, LoadingProgressValueTest006, TestSize.Level1)
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
                    AceType::MakeRefPtr<FrameNode>(VALUE, CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    loadingProgressPattern->SetBuilderFunc(node);
    loadingProgressPattern->FireBuilder();
    /**
     * @tc.steps: step5. Test contentModifierNode_
     */
    auto buildNode = loadingProgressPattern->GetContentModifierNode();
    /**
     * @tc.expected: Check the LoadingProgress child id
     */
    EXPECT_EQ(VALUE, buildNode->GetHostTag());
    /**
     * @tc.steps: step5. Test UseContentModifier
     */
    auto isUsed = loadingProgressPattern->UseContentModifier();
    EXPECT_EQ(true, isUsed);
}

/**
 * @tc.name: LoadingProgressValueTest007
 * @tc.desc: SetChangeValue and get value
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressValueTestNg, LoadingProgressValueTest007, TestSize.Level1)
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
     * @tc.steps: step5. Test contentModifierNode_
     */
    auto buildNode = loadingProgressPattern->GetContentModifierNode();
    /**
     * @tc.expected: Check the LoadingProgress child id
     */
    EXPECT_EQ("", buildNode->GetHostTag());
    /**
     * @tc.steps: step6. Test UseContentModifier
     */
    auto isUsed = loadingProgressPattern->UseContentModifier();
    EXPECT_EQ(true, isUsed);
}

/**
 * @tc.name: LoadingProgressValueTest008
 * @tc.desc: Test UseContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressValueTestNg, LoadingProgressValueTest008, TestSize.Level1)
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
                    AceType::MakeRefPtr<FrameNode>(VALUE, CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
                return child;
            };
    /**
     * @tc.steps: step4. Set parameters to loadingProgressModelNG builderFunc
     */
    loadingProgressPattern->SetBuilderFunc(node);
    loadingProgressPattern->FireBuilder();
    /**
     * @tc.steps: step5. Test contentModifierNode_
     */
    auto buildNode = loadingProgressPattern->GetContentModifierNode();
    /**
     * @tc.expected: Check the LoadingProgress child id
     */
    EXPECT_EQ(VALUE, buildNode->GetHostTag());
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
 * @tc.name: LoadingProgressValueTest009
 * @tc.desc: Test UseContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressValueTestNg, LoadingProgressValueTest009, TestSize.Level1)
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
     * @tc.steps: step4. Set parameters to loadingProgressModelNG builderFunc
     */
    loadingProgressPattern->SetBuilderFunc(node);
    loadingProgressPattern->FireBuilder();
    /**
     * @tc.steps: step5. Test contentModifierNode_
     */
    auto buildNode = loadingProgressPattern->GetContentModifierNode();
    /**
     * @tc.expected: Check the LoadingProgress child id
     */
    EXPECT_EQ("", buildNode->GetHostTag());
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
 * @tc.name: LoadingProgressValueTest010
 * @tc.desc: Test contentModifierNode
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressValueTestNg, LoadingProgressValueTest010, TestSize.Level1)
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
     * @tc.expected: Check the LoadingProgress child id
     */
    EXPECT_EQ(1, buildNode->GetId());
    /**
     * @tc.steps: step6. Test UseContentModifier
     */
    auto isUsed = loadingProgressPattern->UseContentModifier();
    EXPECT_EQ(true, isUsed);
}

/**
 * @tc.name: LoadingProgressValueTest011
 * @tc.desc: Test contentModifierNode
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressValueTestNg, LoadingProgressValueTest011, TestSize.Level1)
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
     * @tc.steps: step6. Test UseContentModifier
     */
    auto isUsed = loadingProgressPattern->UseContentModifier();
    EXPECT_EQ(true, isUsed);
}

/**
 * @tc.name: LoadingProgressValueTest012
 * @tc.desc: Test contentModifierNode
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressValueTestNg, LoadingProgressValueTest012, TestSize.Level1)
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
     * @tc.steps: step6. Test UseContentModifier
     */
    auto isUsed = loadingProgressPattern->UseContentModifier();
    EXPECT_EQ(true, isUsed);
}

/**
 * @tc.name: LoadingProgressValueTest013
 * @tc.desc: Test contentModifierNode
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressValueTestNg, LoadingProgressValueTest013, TestSize.Level1)
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
     * @tc.steps: step6. Test UseContentModifier
     */
    auto isUsed = loadingProgressPattern->UseContentModifier();
    EXPECT_EQ(true, isUsed);
}

/**
 * @tc.name: LoadingProgressValueTest014
 * @tc.desc: Test contentModifierNode
 * @tc.type: FUNC
 */
HWTEST_F(LoadingProgressValueTestNg, LoadingProgressValueTest014, TestSize.Level1)
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
     * @tc.steps: step6. Test UseContentModifier
     */
    auto isUsed = loadingProgressPattern->UseContentModifier();
    EXPECT_EQ(true, isUsed);
}
} // namespace OHOS::Ace::NG