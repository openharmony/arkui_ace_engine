/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include <optional>
#include "gtest/gtest.h"

#define private public
#define protected public

#include "test/mock/adapter/ohos/osal/mock_system_properties.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"

#include "base/geometry/axis.h"
#include "base/memory/ace_type.h"
#include "core/components/slider/slider_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/slider/slider_pattern.h"
#include "core/components_ng/pattern/slider/slider_layout_property.h"
#include "core/components_ng/pattern/slider/slider_paint_property.h"
#include "core/components_ng/pattern/slider/slider_layout_algorithm.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/particle/particle_pattern.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/render/render_context.h"
#include "core/components/common/properties/ui_material.h"
#include "core/components_ng/layout/layout_wrapper_node.h"

using namespace OHOS::Ace::Framework;

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

namespace {
const InspectorFilter filter;
constexpr float VALUE = 50.0f;
constexpr float STEP = 1.0f;
constexpr float MIN = 0.0f;
constexpr float MAX = 100.0f;
constexpr float DIP_SCALE = 1.5f;
constexpr float HALF = 0.5f;
constexpr int32_t DRAG_FRAME_ANIMATION_DURATION = 150;
const SizeF BLOCK_SIZE_TEST(30.0f, 30.0f);
const OffsetF CIRCLE_CENTER_TEST(100.0f, 50.0f);
const Color TEST_COLOR = Color::BLUE;
}

class SliderPatternMaterialTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
    
    RefPtr<FrameNode> CreateSliderNode();
    RefPtr<FrameNode> CreateSliderNodeWithMaterial();
};

void SliderPatternMaterialTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void SliderPatternMaterialTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void SliderPatternMaterialTestNg::SetUp()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SliderTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<SliderTheme>()));
    ScreenSystemManager::GetInstance().dipScale_ = DIP_SCALE;
}

void SliderPatternMaterialTestNg::TearDown()
{
    MockPipelineContext::TearDown();
    g_uiMaterialLevel = UiMaterialLevel::DEFAULT;
}

RefPtr<FrameNode> SliderPatternMaterialTestNg::CreateSliderNode()
{
    auto nodeId = ViewStackProcessor::GetInstance()->ClaimNodeId();
    auto frameNode = FrameNode::CreateFrameNode(
        V2::SLIDER_ETS_TAG, nodeId, AceType::MakeRefPtr<SliderPattern>());
    CHECK_NULL_RETURN(frameNode, nullptr);
    
    auto layoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, nullptr);
    layoutProperty->UpdateSliderMode(SliderModel::SliderMode::OUTSET);
    layoutProperty->UpdateDirection(Axis::HORIZONTAL);
    
    auto paintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_RETURN(paintProperty, nullptr);
    paintProperty->UpdateValue(VALUE);
    paintProperty->UpdateStep(STEP);
    paintProperty->UpdateMin(MIN);
    paintProperty->UpdateMax(MAX);
    paintProperty->UpdateBlockColor(TEST_COLOR);
    
    auto geometryNode = frameNode->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(200.0f, 40.0f));
    
    return frameNode;
}

RefPtr<FrameNode> SliderPatternMaterialTestNg::CreateSliderNodeWithMaterial()
{
    auto frameNode = CreateSliderNode();
    CHECK_NULL_RETURN(frameNode, nullptr);
    
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, nullptr);
    
    auto material = AceType::MakeRefPtr<UiMaterial>();
    renderContext->SetSystemMaterial(material);
    
    return frameNode;
}

/**
 * @tc.name: SliderPattern_HasSystemMaterial_True_001
 * @tc.desc: Test HasSystemMaterial returns true when system material is set
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_HasSystemMaterial_True_001, TestSize.Level1)
{
    auto frameNode = CreateSliderNodeWithMaterial();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    EXPECT_TRUE(pattern->HasSystemMaterial());
}

/**
 * @tc.name: SliderPattern_HasSystemMaterial_False_001
 * @tc.desc: Test HasSystemMaterial returns false when no system material is set
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_HasSystemMaterial_False_001, TestSize.Level1)
{
    auto frameNode = CreateSliderNode();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    EXPECT_FALSE(pattern->HasSystemMaterial());
}

/**
 * @tc.name: SliderPattern_HasSystemMaterial_NullRenderContext_001
 * @tc.desc: Test HasSystemMaterial returns false when render context is null
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_HasSystemMaterial_NullRenderContext_001, TestSize.Level1)
{
    auto frameNode = CreateSliderNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->renderContext_ = nullptr;
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    EXPECT_FALSE(pattern->HasSystemMaterial());
}

/**
 * @tc.name: SliderPattern_IsHighGradeMaterial_True_001
 * @tc.desc: Test IsHighGradeMaterial returns true when UiMaterialLevel is EXQUISITE
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_IsHighGradeMaterial_True_001, TestSize.Level1)
{
    g_uiMaterialLevel = UiMaterialLevel::EXQUISITE;
    
    auto frameNode = CreateSliderNode();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    EXPECT_TRUE(pattern->IsHighGradeMaterial());
}

/**
 * @tc.name: SliderPattern_IsHighGradeMaterial_False_Gentle_001
 * @tc.desc: Test IsHighGradeMaterial returns false when UiMaterialLevel is GENTLE
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_IsHighGradeMaterial_False_Gentle_001, TestSize.Level1)
{
    g_uiMaterialLevel = UiMaterialLevel::GENTLE;
    
    auto frameNode = CreateSliderNode();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    EXPECT_FALSE(pattern->IsHighGradeMaterial());
}

/**
 * @tc.name: SliderPattern_IsHighGradeMaterial_False_None_001
 * @tc.desc: Test IsHighGradeMaterial returns false when UiMaterialLevel is NONE
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_IsHighGradeMaterial_False_None_001, TestSize.Level1)
{
    g_uiMaterialLevel = UiMaterialLevel::DEFAULT;
    
    auto frameNode = CreateSliderNode();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    EXPECT_FALSE(pattern->IsHighGradeMaterial());
}

/**
 * @tc.name: SliderPattern_IsMiddleGradeMaterial_True_001
 * @tc.desc: Test IsMiddleGradeMaterial returns true when UiMaterialLevel is GENTLE
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_IsMiddleGradeMaterial_True_001, TestSize.Level1)
{
    g_uiMaterialLevel = UiMaterialLevel::GENTLE;
    
    auto frameNode = CreateSliderNode();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    EXPECT_TRUE(pattern->IsMiddleGradeMaterial());
}

/**
 * @tc.name: SliderPattern_IsMiddleGradeMaterial_False_Exquisite_001
 * @tc.desc: Test IsMiddleGradeMaterial returns false when UiMaterialLevel is EXQUISITE
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_IsMiddleGradeMaterial_False_Exquisite_001, TestSize.Level1)
{
    g_uiMaterialLevel = UiMaterialLevel::EXQUISITE;
    
    auto frameNode = CreateSliderNode();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    EXPECT_FALSE(pattern->IsMiddleGradeMaterial());
}

/**
 * @tc.name: SliderPattern_IsMiddleGradeMaterial_False_None_001
 * @tc.desc: Test IsMiddleGradeMaterial returns false when UiMaterialLevel is NONE
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_IsMiddleGradeMaterial_False_None_001, TestSize.Level1)
{
    g_uiMaterialLevel = UiMaterialLevel::DEFAULT;
    
    auto frameNode = CreateSliderNode();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    EXPECT_FALSE(pattern->IsMiddleGradeMaterial());
}

/**
 * @tc.name: SliderPattern_GetBlockRadius_001
 * @tc.desc: Test GetBlockRadius returns correct radius based on block size
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_GetBlockRadius_001, TestSize.Level1)
{
    auto frameNode = CreateSliderNode();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->blockSize_ = BLOCK_SIZE_TEST;
    
    auto radius = pattern->GetBlockRadius();
    EXPECT_FLOAT_EQ(radius, std::min(BLOCK_SIZE_TEST.Width(), BLOCK_SIZE_TEST.Height()) * HALF);
}

/**
 * @tc.name: SliderPattern_GetDragFrameBaseScale_Outset_001
 * @tc.desc: Test GetDragFrameBaseScale returns 2.0f for OUTSET mode
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_GetDragFrameBaseScale_Outset_001, TestSize.Level1)
{
    auto frameNode = CreateSliderNode();
    ASSERT_NE(frameNode, nullptr);
    
    auto layoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateSliderMode(SliderModel::SliderMode::OUTSET);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    auto scale = pattern->GetDragFrameBaseScale();
    EXPECT_FLOAT_EQ(scale, 2.0f);
}

/**
 * @tc.name: SliderPattern_GetDragFrameBaseScale_Inset_001
 * @tc.desc: Test GetDragFrameBaseScale returns 3.0f for INSET mode
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_GetDragFrameBaseScale_Inset_001, TestSize.Level1)
{
    auto frameNode = CreateSliderNode();
    ASSERT_NE(frameNode, nullptr);
    
    auto layoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateSliderMode(SliderModel::SliderMode::INSET);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    auto scale = pattern->GetDragFrameBaseScale();
    EXPECT_FLOAT_EQ(scale, 3.0f);
}

/**
 * @tc.name: SliderPattern_GetDragFrameBaseScale_NullLayoutProperty_001
 * @tc.desc: Test GetDragFrameBaseScale returns 2.0f when layout property is null
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_GetDragFrameBaseScale_NullLayoutProperty_001, TestSize.Level1)
{
    auto frameNode = CreateSliderNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->layoutProperty_ = nullptr;
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    auto scale = pattern->GetDragFrameBaseScale();
    EXPECT_FLOAT_EQ(scale, 2.0f);
}

/**
 * @tc.name: SliderPattern_CreateDragFrameNode_New_001
 * @tc.desc: Test CreateDragFrameNode creates a new node when dragFrameNode_ is null
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_CreateDragFrameNode_New_001, TestSize.Level1)
{
    auto frameNode = CreateSliderNode();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->dragFrameNode_ = nullptr;
    pattern->blockSize_ = BLOCK_SIZE_TEST;
    
    pattern->CreateDragFrameNode();
    
    ASSERT_NE(pattern->dragFrameNode_, nullptr);
    EXPECT_EQ(pattern->dragFrameNode_->GetTag(), V2::COLUMN_ETS_TAG);
}

/**
 * @tc.name: SliderPattern_CreateDragFrameNode_Existing_001
 * @tc.desc: Test CreateDragFrameNode uses existing node when dragFrameNode_ exists
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_CreateDragFrameNode_Existing_001, TestSize.Level1)
{
    auto frameNode = CreateSliderNode();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    auto existingNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    pattern->dragFrameNode_ = existingNode;
    pattern->blockSize_ = BLOCK_SIZE_TEST;
    
    pattern->CreateDragFrameNode();
    
    EXPECT_EQ(pattern->dragFrameNode_, existingNode);
}

/**
 * @tc.name: SliderPattern_CreateDragPointNode_New_001
 * @tc.desc: Test CreateDragPointNode creates a new node when dragPointNode_ is null
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_CreateDragPointNode_New_001, TestSize.Level1)
{
    auto frameNode = CreateSliderNode();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->dragPointNode_ = nullptr;
    pattern->blockSize_ = BLOCK_SIZE_TEST;
    
    pattern->CreateDragPointNode();
    
    ASSERT_NE(pattern->dragPointNode_, nullptr);
    EXPECT_EQ(pattern->dragPointNode_->GetTag(), V2::COLUMN_ETS_TAG);
}

/**
 * @tc.name: SliderPattern_CreateDragPointNode_Existing_001
 * @tc.desc: Test CreateDragPointNode returns early when dragPointNode_ exists
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_CreateDragPointNode_Existing_001, TestSize.Level1)
{
    auto frameNode = CreateSliderNode();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    auto existingNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    pattern->dragPointNode_ = existingNode;
    
    pattern->CreateDragPointNode();
    
    EXPECT_EQ(pattern->dragPointNode_, existingNode);
}

/**
 * @tc.name: SliderPattern_CreateBlurCoverNode_New_001
 * @tc.desc: Test CreateBlurCoverNode creates a new node when blurCoverNode_ is null
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_CreateBlurCoverNode_New_001, TestSize.Level1)
{
    auto frameNode = CreateSliderNode();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->blurCoverNode_ = nullptr;
    pattern->blockSize_ = BLOCK_SIZE_TEST;
    
    pattern->CreateBlurCoverNode();
    
    ASSERT_NE(pattern->blurCoverNode_, nullptr);
    EXPECT_EQ(pattern->blurCoverNode_->GetTag(), V2::COLUMN_ETS_TAG);
}

/**
 * @tc.name: SliderPattern_CreateBlurCoverNode_Existing_001
 * @tc.desc: Test CreateBlurCoverNode returns early when blurCoverNode_ exists
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_CreateBlurCoverNode_Existing_001, TestSize.Level1)
{
    auto frameNode = CreateSliderNode();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    auto existingNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    pattern->blurCoverNode_ = existingNode;
    
    pattern->CreateBlurCoverNode();
    
    EXPECT_EQ(pattern->blurCoverNode_, existingNode);
}

/**
 * @tc.name: SliderPattern_CreateSelectedTrackFrameNode_New_001
 * @tc.desc: Test CreateSelectedTrackFrameNode creates a new node when selectedTrackFrameNode_ is null
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_CreateSelectedTrackFrameNode_New_001, TestSize.Level1)
{
    auto frameNode = CreateSliderNode();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->selectedTrackFrameNode_ = nullptr;
    pattern->blockSize_ = BLOCK_SIZE_TEST;
    
    pattern->CreateSelectedTrackFrameNode();
    
    ASSERT_NE(pattern->selectedTrackFrameNode_, nullptr);
    EXPECT_EQ(pattern->selectedTrackFrameNode_->GetTag(), V2::COLUMN_ETS_TAG);
}

/**
 * @tc.name: SliderPattern_CreateSelectedTrackFrameNode_Existing_001
 * @tc.desc: Test CreateSelectedTrackFrameNode uses existing node when selectedTrackFrameNode_ exists
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_CreateSelectedTrackFrameNode_Existing_001, TestSize.Level1)
{
    auto frameNode = CreateSliderNode();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    auto existingNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    pattern->selectedTrackFrameNode_ = existingNode;
    pattern->blockSize_ = BLOCK_SIZE_TEST;
    
    pattern->CreateSelectedTrackFrameNode();
    
    EXPECT_EQ(pattern->selectedTrackFrameNode_, existingNode);
}

/**
 * @tc.name: SliderPattern_CreateParticleFrameNode_New_001
 * @tc.desc: Test CreateParticleFrameNode creates a new particle node when particleFrameNode_ is null
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_CreateParticleFrameNode_New_001, TestSize.Level1)
{
    auto frameNode = CreateSliderNode();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->particleFrameNode_ = nullptr;
    pattern->blockSize_ = BLOCK_SIZE_TEST;
    
    auto sliderContentModifier = AceType::MakeRefPtr<SliderContentModifier>(
        SliderContentModifier::Parameters(),
        [](const PointF&) {},
        AceType::MakeRefPtr<SliderTheme>());
    pattern->sliderContentModifier_ = sliderContentModifier;
    
    pattern->CreateParticleFrameNode();
    
    ASSERT_NE(pattern->particleFrameNode_, nullptr);
    EXPECT_EQ(pattern->particleFrameNode_->GetTag(), V2::PARTICLE_ETS_TAG);
}

/**
 * @tc.name: SliderPattern_CreateParticleFrameNode_Existing_001
 * @tc.desc: Test CreateParticleFrameNode uses existing node when particleFrameNode_ exists
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_CreateParticleFrameNode_Existing_001, TestSize.Level1)
{
    auto frameNode = CreateSliderNode();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    auto existingNode = FrameNode::CreateFrameNode(
        V2::PARTICLE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<ParticlePattern>(1));
    pattern->particleFrameNode_ = existingNode;
    
    auto sliderContentModifier = AceType::MakeRefPtr<SliderContentModifier>(
        SliderContentModifier::Parameters(),
        [](const PointF&) {},
        AceType::MakeRefPtr<SliderTheme>());
    pattern->sliderContentModifier_ = sliderContentModifier;
    
    pattern->CreateParticleFrameNode();
    
    EXPECT_EQ(pattern->particleFrameNode_, existingNode);
}

/**
 * @tc.name: SliderPattern_IsContentModifierNode_True_001
 * @tc.desc: Test IsContentModifierNode returns true for content modifier node
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_IsContentModifierNode_True_001, TestSize.Level1)
{
    auto frameNode = CreateSliderNode();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    auto contentNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    pattern->contentModifierNode_ = contentNode;
    
    EXPECT_TRUE(pattern->IsContentModifierNode(contentNode));
}

/**
 * @tc.name: SliderPattern_IsContentModifierNode_False_001
 * @tc.desc: Test IsContentModifierNode returns false for other nodes
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_IsContentModifierNode_False_001, TestSize.Level1)
{
    auto frameNode = CreateSliderNode();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    auto otherNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    
    EXPECT_FALSE(pattern->IsContentModifierNode(otherNode));
}

/**
 * @tc.name: SliderPattern_IsContentModifierNode_Null_001
 * @tc.desc: Test IsContentModifierNode returns false when node is null
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_IsContentModifierNode_Null_001, TestSize.Level1)
{
    auto frameNode = CreateSliderNode();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    RefPtr<FrameNode> nullNode = nullptr;
    
    EXPECT_FALSE(pattern->IsContentModifierNode(nullNode));
}

/**
 * @tc.name: SliderPattern_IsMaterialNode_True_DragFrame_001
 * @tc.desc: Test IsMaterialNode returns true for dragFrameNode
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_IsMaterialNode_True_DragFrame_001, TestSize.Level1)
{
    auto frameNode = CreateSliderNode();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    auto dragFrameNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    pattern->dragFrameNode_ = dragFrameNode;
    
    EXPECT_TRUE(pattern->IsMaterialNode(dragFrameNode));
}

/**
 * @tc.name: SliderPattern_IsMaterialNode_True_DragPoint_001
 * @tc.desc: Test IsMaterialNode returns true for dragPointNode
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_IsMaterialNode_True_DragPoint_001, TestSize.Level1)
{
    auto frameNode = CreateSliderNode();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    auto dragPointNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    pattern->dragPointNode_ = dragPointNode;
    
    EXPECT_TRUE(pattern->IsMaterialNode(dragPointNode));
}

/**
 * @tc.name: SliderPattern_IsMaterialNode_True_BlurCover_001
 * @tc.desc: Test IsMaterialNode returns true for blurCoverNode
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_IsMaterialNode_True_BlurCover_001, TestSize.Level1)
{
    auto frameNode = CreateSliderNode();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    auto blurCoverNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    pattern->blurCoverNode_ = blurCoverNode;
    
    EXPECT_TRUE(pattern->IsMaterialNode(blurCoverNode));
}

/**
 * @tc.name: SliderPattern_IsSelectedTrackNode_True_001
 * @tc.desc: Test IsSelectedTrackNode returns true for selectedTrackFrameNode
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_IsSelectedTrackNode_True_001, TestSize.Level1)
{
    auto frameNode = CreateSliderNode();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    auto selectedTrackFrameNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    pattern->selectedTrackFrameNode_ = selectedTrackFrameNode;
    
    EXPECT_TRUE(pattern->IsSelectedTrackNode(selectedTrackFrameNode));
}

/**
 * @tc.name: SliderPattern_IsMaterialNode_False_001
 * @tc.desc: Test IsMaterialNode returns false for non-material nodes
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_IsMaterialNode_False_001, TestSize.Level1)
{
    auto frameNode = CreateSliderNode();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    auto otherNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    
    EXPECT_FALSE(pattern->IsMaterialNode(otherNode));
}

/**
 * @tc.name: SliderPattern_IsMaterialNode_Null_001
 * @tc.desc: Test IsMaterialNode returns false when node is null
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_IsMaterialNode_Null_001, TestSize.Level1)
{
    auto frameNode = CreateSliderNode();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    RefPtr<FrameNode> nullNode = nullptr;
    
    EXPECT_FALSE(pattern->IsMaterialNode(nullNode));
}

/**
 * @tc.name: SliderPattern_CreateDragAnimationOption_001
 * @tc.desc: Test CreateDragAnimationOption creates animation option with spring curve
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_CreateDragAnimationOption_001, TestSize.Level1)
{
    auto frameNode = CreateSliderNode();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    auto option = pattern->CreateDragAnimationOption();
    
    EXPECT_EQ(option.GetDuration(), DRAG_FRAME_ANIMATION_DURATION);
    EXPECT_NE(option.GetCurve(), nullptr);
}

/**
 * @tc.name: SliderPattern_CreateLowGradeSpringOption_001
 * @tc.desc: Test CreateLowGradeSpringOption creates animation option for low grade
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_CreateLowGradeSpringOption_001, TestSize.Level1)
{
    auto frameNode = CreateSliderNode();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    auto option = pattern->CreateLowGradeSpringOption();
    
    EXPECT_EQ(option.GetDuration(), DRAG_FRAME_ANIMATION_DURATION);
    EXPECT_NE(option.GetCurve(), nullptr);
}

/**
 * @tc.name: SliderPattern_StartDeformAnimation_NodeOnTree_001
 * @tc.desc: Test StartDeformAnimation executes when dragFrameNode is on main tree
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_StartDeformAnimation_NodeOnTree_001, TestSize.Level1)
{
    auto frameNode = CreateSliderNode();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    auto dragFrameNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    pattern->dragFrameNode_ = dragFrameNode;
    frameNode->AddChild(dragFrameNode);
    
    auto layoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateDirection(Axis::HORIZONTAL);
    
    pattern->StartDeformAnimation();
}

/**
 * @tc.name: SliderPattern_StartDeformAnimation_NodeNotOnTree_001
 * @tc.desc: Test StartDeformAnimation returns early when dragFrameNode is not on tree
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_StartDeformAnimation_NodeNotOnTree_001, TestSize.Level1)
{
    auto frameNode = CreateSliderNode();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    auto dragFrameNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    pattern->dragFrameNode_ = dragFrameNode;
    
    pattern->StartDeformAnimation();
}

/**
 * @tc.name: SliderPattern_StartDeformAnimation_NullNode_001
 * @tc.desc: Test StartDeformAnimation returns early when dragFrameNode is null
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_StartDeformAnimation_NullNode_001, TestSize.Level1)
{
    auto frameNode = CreateSliderNode();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->dragFrameNode_ = nullptr;
    
    pattern->StartDeformAnimation();
}

/**
 * @tc.name: SliderPattern_RestoreDeformAnimation_NodeOnTree_001
 * @tc.desc: Test RestoreDeformAnimation restores scale when dragFrameNode is on tree
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_RestoreDeformAnimation_NodeOnTree_001, TestSize.Level1)
{
    auto frameNode = CreateSliderNode();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    auto dragFrameNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    pattern->dragFrameNode_ = dragFrameNode;
    frameNode->AddChild(dragFrameNode);
    
    pattern->RestoreDeformAnimation();
}

/**
 * @tc.name: SliderPattern_RestoreDeformAnimation_NodeNotOnTree_001
 * @tc.desc: Test RestoreDeformAnimation returns early when dragFrameNode is not on tree
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_RestoreDeformAnimation_NodeNotOnTree_001, TestSize.Level1)
{
    auto frameNode = CreateSliderNode();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    auto dragFrameNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    pattern->dragFrameNode_ = dragFrameNode;
    
    pattern->RestoreDeformAnimation();
}

/**
 * @tc.name: SliderPattern_RestoreDeformAnimation_NullNode_001
 * @tc.desc: Test RestoreDeformAnimation returns early when dragFrameNode is null
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_RestoreDeformAnimation_NullNode_001, TestSize.Level1)
{
    auto frameNode = CreateSliderNode();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->dragFrameNode_ = nullptr;
    
    pattern->RestoreDeformAnimation();
}

/**
 * @tc.name: SliderPattern_StartLongPressTimer_Default_001
 * @tc.desc: Test StartLongPressTimer starts timer for DEFAULT block type
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_StartLongPressTimer_Default_001, TestSize.Level1)
{
    auto frameNode = CreateSliderNode();
    ASSERT_NE(frameNode, nullptr);
    
    auto paintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateBlockType(SliderModelNG::BlockStyleType::DEFAULT);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    pattern->StartLongPressTimer();
}

/**
 * @tc.name: SliderPattern_StartLongPressTimer_Image_001
 * @tc.desc: Test StartLongPressTimer returns early for IMAGE block type
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_StartLongPressTimer_Image_001, TestSize.Level1)
{
    auto frameNode = CreateSliderNode();
    ASSERT_NE(frameNode, nullptr);
    
    auto paintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateBlockType(SliderModelNG::BlockStyleType::IMAGE);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    pattern->StartLongPressTimer();
}

/**
 * @tc.name: SliderPattern_HandleLongPress_NoMaterial_001
 * @tc.desc: Test HandleLongPress returns early when HasSystemMaterial is false
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_HandleLongPress_NoMaterial_001, TestSize.Level1)
{
    g_uiMaterialLevel = UiMaterialLevel::EXQUISITE;
    
    auto frameNode = CreateSliderNode();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    pattern->HandleLongPress();
}

/**
 * @tc.name: SliderPattern_ShowMaterialNode_NoMaterial_001
 * @tc.desc: Test ShowMaterialNode returns early when HasSystemMaterial is false
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_ShowMaterialNode_NoMaterial_001, TestSize.Level1)
{
    auto frameNode = CreateSliderNode();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    pattern->ShowMaterialNode();
}

/**
 * @tc.name: SliderPattern_ShowMaterialNode_HighGrade_001
 * @tc.desc: Test ShowMaterialNode creates nodes for EXQUISITE level with material
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_ShowMaterialNode_HighGrade_001, TestSize.Level1)
{
    g_uiMaterialLevel = UiMaterialLevel::EXQUISITE;
    
    auto frameNode = CreateSliderNodeWithMaterial();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->circleCenter_ = CIRCLE_CENTER_TEST;
    pattern->blockSize_ = BLOCK_SIZE_TEST;
    
    pattern->ShowMaterialNode();
}

/**
 * @tc.name: SliderPattern_ShowMaterialNode_MiddleGrade_001
 * @tc.desc: Test ShowMaterialNode creates nodes for GENTLE level with material
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_ShowMaterialNode_MiddleGrade_001, TestSize.Level1)
{
    g_uiMaterialLevel = UiMaterialLevel::GENTLE;
    
    auto frameNode = CreateSliderNodeWithMaterial();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->circleCenter_ = CIRCLE_CENTER_TEST;
    pattern->blockSize_ = BLOCK_SIZE_TEST;
    
    pattern->ShowMaterialNode();
}

/**
 * @tc.name: SliderPattern_ShowMaterialNode_LowGrade_001
 * @tc.desc: Test ShowMaterialNode returns early for NONE level even with material
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_ShowMaterialNode_LowGrade_001, TestSize.Level1)
{
    g_uiMaterialLevel = UiMaterialLevel::DEFAULT;
    
    auto frameNode = CreateSliderNodeWithMaterial();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    pattern->ShowMaterialNode();
}

/**
 * @tc.name: SliderPattern_HideMaterialNode_LowGrade_001
 * @tc.desc: Test HideMaterialNode uses low grade spring animation for NONE level
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_HideMaterialNode_LowGrade_001, TestSize.Level1)
{
    g_uiMaterialLevel = UiMaterialLevel::DEFAULT;
    
    auto frameNode = CreateSliderNode();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    auto sliderContentModifier = AceType::MakeRefPtr<SliderContentModifier>(
        SliderContentModifier::Parameters(),
        [](const PointF&) {},
        AceType::MakeRefPtr<SliderTheme>());
    pattern->sliderContentModifier_ = sliderContentModifier;
    
    pattern->HideMaterialNode();
}

/**
 * @tc.name: SliderPattern_HideMaterialNode_HighGrade_001
 * @tc.desc: Test HideMaterialNode hides nodes for EXQUISITE level
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_HideMaterialNode_HighGrade_001, TestSize.Level1)
{
    g_uiMaterialLevel = UiMaterialLevel::EXQUISITE;
    
    auto frameNode = CreateSliderNodeWithMaterial();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->circleCenter_ = CIRCLE_CENTER_TEST;
    pattern->blockSize_ = BLOCK_SIZE_TEST;
    
    auto dragPointNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    pattern->dragPointNode_ = dragPointNode;
    
    auto blurCoverNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    pattern->blurCoverNode_ = blurCoverNode;
    
    frameNode->AddChild(dragPointNode);
    frameNode->AddChild(blurCoverNode);
    
    pattern->HideMaterialNode();
}

/**
 * @tc.name: SliderPattern_HideMaterialNode_MiddleGrade_001
 * @tc.desc: Test HideMaterialNode hides nodes for GENTLE level
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_HideMaterialNode_MiddleGrade_001, TestSize.Level1)
{
    g_uiMaterialLevel = UiMaterialLevel::GENTLE;
    
    auto frameNode = CreateSliderNodeWithMaterial();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->circleCenter_ = CIRCLE_CENTER_TEST;
    pattern->blockSize_ = BLOCK_SIZE_TEST;
    
    auto dragPointNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    pattern->dragPointNode_ = dragPointNode;
    
    auto blurCoverNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    pattern->blurCoverNode_ = blurCoverNode;
    
    frameNode->AddChild(dragPointNode);
    frameNode->AddChild(blurCoverNode);
    
    pattern->HideMaterialNode();
}

/**
 * @tc.name: SliderPattern_HideMaterialNodes_001
 * @tc.desc: Test HideMaterialNodes removes all material nodes from parent
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_HideMaterialNodes_001, TestSize.Level1)
{
    g_uiMaterialLevel = UiMaterialLevel::EXQUISITE;
    
    auto frameNode = CreateSliderNode();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    auto dragFrameNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    pattern->dragFrameNode_ = dragFrameNode;
    frameNode->AddChild(dragFrameNode);
    
    auto dragPointNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    pattern->dragPointNode_ = dragPointNode;
    frameNode->AddChild(dragPointNode);
    
    auto blurCoverNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    pattern->blurCoverNode_ = blurCoverNode;
    frameNode->AddChild(blurCoverNode);
    
    auto selectedTrackFrameNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    pattern->selectedTrackFrameNode_ = selectedTrackFrameNode;
    frameNode->AddChild(selectedTrackFrameNode);
    
    auto particleFrameNode = FrameNode::CreateFrameNode(
        V2::PARTICLE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<ParticlePattern>(1));
    pattern->particleFrameNode_ = particleFrameNode;
    frameNode->AddChild(particleFrameNode);
    
    pattern->HideMaterialNodes();
}

/**
 * @tc.name: SliderPattern_FireChangeEvent_HighGrade_DeformStarted_001
 * @tc.desc: Test FireChangeEvent schedules deform restore when deform already started for high grade
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_FireChangeEvent_HighGrade_DeformStarted_001, TestSize.Level1)
{
    g_uiMaterialLevel = UiMaterialLevel::EXQUISITE;
    
    auto frameNode = CreateSliderNodeWithMaterial();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    auto dragFrameNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    pattern->dragFrameNode_ = dragFrameNode;
    frameNode->AddChild(dragFrameNode);
    
    pattern->isDeformStarted_ = true;
    
    pattern->FireChangeEvent(SliderPattern::SliderChangeMode::Moving);
}

/**
 * @tc.name: SliderPattern_FireChangeEvent_HighGrade_DeformNotStarted_001
 * @tc.desc: Test FireChangeEvent starts deform animation when deform not started for high grade
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_FireChangeEvent_HighGrade_DeformNotStarted_001, TestSize.Level1)
{
    g_uiMaterialLevel = UiMaterialLevel::EXQUISITE;
    
    auto frameNode = CreateSliderNodeWithMaterial();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    auto dragFrameNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    pattern->dragFrameNode_ = dragFrameNode;
    frameNode->AddChild(dragFrameNode);
    
    pattern->isDeformStarted_ = false;
    
    pattern->FireChangeEvent(SliderPattern::SliderChangeMode::Moving);
}

/**
 * @tc.name: SliderPattern_FireChangeEvent_MiddleGrade_DeformStarted_001
 * @tc.desc: Test FireChangeEvent schedules deform restore when deform already started for middle grade
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_FireChangeEvent_MiddleGrade_DeformStarted_001, TestSize.Level1)
{
    g_uiMaterialLevel = UiMaterialLevel::GENTLE;
    
    auto frameNode = CreateSliderNodeWithMaterial();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    auto dragFrameNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    pattern->dragFrameNode_ = dragFrameNode;
    frameNode->AddChild(dragFrameNode);
    
    pattern->isDeformStarted_ = true;
    
    pattern->FireChangeEvent(SliderPattern::SliderChangeMode::Moving);
}

/**
 * @tc.name: SliderPattern_FireChangeEvent_MiddleGrade_DeformNotStarted_001
 * @tc.desc: Test FireChangeEvent starts deform animation when deform not started for middle grade
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_FireChangeEvent_MiddleGrade_DeformNotStarted_001, TestSize.Level1)
{
    g_uiMaterialLevel = UiMaterialLevel::GENTLE;
    
    auto frameNode = CreateSliderNodeWithMaterial();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    auto dragFrameNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    pattern->dragFrameNode_ = dragFrameNode;
    frameNode->AddChild(dragFrameNode);
    
    pattern->isDeformStarted_ = false;
    
    pattern->FireChangeEvent(SliderPattern::SliderChangeMode::Moving);
}

/**
 * @tc.name: SliderPattern_FireChangeEvent_LowGrade_001
 * @tc.desc: Test FireChangeEvent does not trigger deform for NONE level
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_FireChangeEvent_LowGrade_001, TestSize.Level1)
{
    g_uiMaterialLevel = UiMaterialLevel::DEFAULT;
    
    auto frameNode = CreateSliderNode();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->isDeformStarted_ = false;
    
    pattern->FireChangeEvent(SliderPattern::SliderChangeMode::Moving);
}

/**
 * @tc.name: SliderPattern_FireChangeEvent_NonMovingMode_001
 * @tc.desc: Test FireChangeEvent does not trigger deform for non-Moving mode
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_FireChangeEvent_NonMovingMode_001, TestSize.Level1)
{
    g_uiMaterialLevel = UiMaterialLevel::EXQUISITE;
    
    auto frameNode = CreateSliderNodeWithMaterial();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->isDeformStarted_ = false;
    
    pattern->FireChangeEvent(SliderPattern::SliderChangeMode::End);
}

/**
 * @tc.name: SliderPattern_FireChangeEvent_NoMaterial_001
 * @tc.desc: Test FireChangeEvent does not trigger deform when HasSystemMaterial is false
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_FireChangeEvent_NoMaterial_001, TestSize.Level1)
{
    g_uiMaterialLevel = UiMaterialLevel::EXQUISITE;
    
    auto frameNode = CreateSliderNode();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->isDeformStarted_ = false;
    
    pattern->FireChangeEvent(SliderPattern::SliderChangeMode::Moving);
}

/**
 * @tc.name: SliderPattern_IsImageBlockNode_True_001
 * @tc.desc: Test IsImageBlockNode returns true for imageFrameNode
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_IsImageBlockNode_True_001, TestSize.Level1)
{
    auto frameNode = CreateSliderNode();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    auto imageFrameNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<ImagePattern>());
    pattern->imageFrameNode_ = imageFrameNode;
    
    EXPECT_TRUE(pattern->IsImageBlockNode(imageFrameNode));
}

/**
 * @tc.name: SliderPattern_IsImageBlockNode_False_001
 * @tc.desc: Test IsImageBlockNode returns false for non-image nodes
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_IsImageBlockNode_False_001, TestSize.Level1)
{
    auto frameNode = CreateSliderNode();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    auto otherNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    
    EXPECT_FALSE(pattern->IsImageBlockNode(otherNode));
}

/**
 * @tc.name: SliderPattern_IsImageBlockNode_Null_001
 * @tc.desc: Test IsImageBlockNode returns false when node is null
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_IsImageBlockNode_Null_001, TestSize.Level1)
{
    auto frameNode = CreateSliderNode();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    RefPtr<FrameNode> nullNode = nullptr;
    
    EXPECT_FALSE(pattern->IsImageBlockNode(nullNode));
}

/**
 * @tc.name: SliderPattern_IsPrefixOrSuffixNode_True_Prefix_001
 * @tc.desc: Test IsPrefixOrSuffixNode returns true for prefixNodeStack with HasPrefix
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_IsPrefixOrSuffixNode_True_Prefix_001, TestSize.Level1)
{
    auto frameNode = CreateSliderNode();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    auto prefixNodeStack = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    pattern->prefixNodeStack_ = prefixNodeStack;
    
    RefPtr<UINode> prefixNode = AceType::MakeRefPtr<FrameNode>(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    pattern->prefix_ = prefixNode;
    
    EXPECT_TRUE(pattern->IsPrefixOrSuffixNode(prefixNodeStack));
}

/**
 * @tc.name: SliderPattern_IsPrefixOrSuffixNode_True_Suffix_001
 * @tc.desc: Test IsPrefixOrSuffixNode returns true for suffixNodeStack with HasSuffix
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_IsPrefixOrSuffixNode_True_Suffix_001, TestSize.Level1)
{
    auto frameNode = CreateSliderNode();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    auto suffixNodeStack = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    pattern->suffixNodeStack_ = suffixNodeStack;
    
    RefPtr<UINode> suffixNode = AceType::MakeRefPtr<FrameNode>(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    pattern->suffix_ = suffixNode;
    
    EXPECT_TRUE(pattern->IsPrefixOrSuffixNode(suffixNodeStack));
}

/**
 * @tc.name: SliderPattern_IsPrefixOrSuffixNode_False_001
 * @tc.desc: Test IsPrefixOrSuffixNode returns false for other nodes
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_IsPrefixOrSuffixNode_False_001, TestSize.Level1)
{
    auto frameNode = CreateSliderNode();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    auto otherNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    
    EXPECT_FALSE(pattern->IsPrefixOrSuffixNode(otherNode));
}

/**
 * @tc.name: SliderPattern_IsPrefixOrSuffixNode_Null_001
 * @tc.desc: Test IsPrefixOrSuffixNode returns false when node is null
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_IsPrefixOrSuffixNode_Null_001, TestSize.Level1)
{
    auto frameNode = CreateSliderNode();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    RefPtr<FrameNode> nullNode = nullptr;
    
    EXPECT_FALSE(pattern->IsPrefixOrSuffixNode(nullNode));
}

/**
 * @tc.name: SliderPattern_IsNeedShowMaterial_True_001
 * @tc.desc: Test IsNeedShowMaterial returns true when all conditions are met
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_IsNeedShowMaterial_True_001, TestSize.Level1)
{
    auto frameNode = CreateSliderNodeWithMaterial();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    auto layoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateSliderMode(SliderModel::SliderMode::OUTSET);
    
    auto paintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateBlockType(SliderModel::BlockStyleType::DEFAULT);
    
    EXPECT_TRUE(pattern->IsNeedShowMaterial());
}

/**
 * @tc.name: SliderPattern_IsNeedShowMaterial_False_NoSystemMaterial_001
 * @tc.desc: Test IsNeedShowMaterial returns false when no system material
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_IsNeedShowMaterial_False_NoSystemMaterial_001, TestSize.Level1)
{
    auto frameNode = CreateSliderNode();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    EXPECT_FALSE(pattern->IsNeedShowMaterial());
}

/**
 * @tc.name: SliderPattern_IsNeedShowMaterial_False_BlockTypeNotDefault_001
 * @tc.desc: Test IsNeedShowMaterial returns false when blockType is not DEFAULT
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_IsNeedShowMaterial_False_BlockTypeNotDefault_001, TestSize.Level1)
{
    auto frameNode = CreateSliderNodeWithMaterial();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    auto paintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateBlockType(SliderModel::BlockStyleType::IMAGE);
    
    EXPECT_FALSE(pattern->IsNeedShowMaterial());
}

/**
 * @tc.name: SliderPattern_IsNeedShowMaterial_False_SliderModeNone_001
 * @tc.desc: Test IsNeedShowMaterial returns false when sliderMode is NONE
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_IsNeedShowMaterial_False_SliderModeNone_001, TestSize.Level1)
{
    auto frameNode = CreateSliderNodeWithMaterial();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    auto layoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateSliderMode(SliderModel::SliderMode::NONE);
    
    EXPECT_FALSE(pattern->IsNeedShowMaterial());
}

/**
 * @tc.name: SliderPattern_IsNeedShowMaterial_True_InsetMode_001
 * @tc.desc: Test IsNeedShowMaterial returns true for INSET mode
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_IsNeedShowMaterial_True_InsetMode_001, TestSize.Level1)
{
    auto frameNode = CreateSliderNodeWithMaterial();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    auto layoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateSliderMode(SliderModel::SliderMode::INSET);
    
    EXPECT_TRUE(pattern->IsNeedShowMaterial());
}

/**
 * @tc.name: SliderPattern_HideMaterialNode_ShowMaterial_False_001
 * @tc.desc: Test HideMaterialNode returns early when IsNeedShowMaterial is false
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_HideMaterialNode_ShowMaterial_False_001, TestSize.Level1)
{
    auto frameNode = CreateSliderNode();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    pattern->dragPointNode_ = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    pattern->blurCoverNode_ = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    
    pattern->HideMaterialNode();
    
    EXPECT_FALSE(pattern->IsNeedShowMaterial());
}

/**
 * @tc.name: SliderPattern_StartLongPressTimer_ShowMaterial_False_001
 * @tc.desc: Test StartLongPressTimer returns early when IsNeedShowMaterial is false
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_StartLongPressTimer_ShowMaterial_False_001, TestSize.Level1)
{
    auto frameNode = CreateSliderNode();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    pattern->StartLongPressTimer();
    
    EXPECT_FALSE(pattern->longPressTask_);
}

/**
 * @tc.name: SliderPattern_HandleLongPress_ShowMaterial_False_001
 * @tc.desc: Test HandleLongPress returns early when IsNeedShowMaterial is false
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_HandleLongPress_ShowMaterial_False_001, TestSize.Level1)
{
    auto frameNode = CreateSliderNode();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    pattern->HandleLongPress();
    
    EXPECT_FALSE(pattern->IsNeedShowMaterial());
}

/**
 * @tc.name: SliderPattern_HandleLongPress_HighMiddleGrade_001
 * @tc.desc: Test HandleLongPress handles high/middle grade material together
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_HandleLongPress_HighMiddleGrade_001, TestSize.Level1)
{
    g_uiMaterialLevel = UiMaterialLevel::EXQUISITE;
    auto frameNode = CreateSliderNodeWithMaterial();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    auto layoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateSliderMode(SliderModel::SliderMode::INSET);
    
    EXPECT_TRUE(pattern->IsNeedShowMaterial());
    EXPECT_TRUE(pattern->IsHighGradeMaterial() || pattern->IsMiddleGradeMaterial());
}

/**
 * @tc.name: SliderPattern_HandleLongPress_LowGrade_001
 * @tc.desc: Test HandleLongPress handles low grade material
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_HandleLongPress_LowGrade_001, TestSize.Level1)
{
    g_uiMaterialLevel = UiMaterialLevel::SMOOTH;
    auto frameNode = CreateSliderNodeWithMaterial();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    auto layoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateSliderMode(SliderModel::SliderMode::INSET);
    
    EXPECT_TRUE(pattern->IsNeedShowMaterial());
    EXPECT_FALSE(pattern->IsHighGradeMaterial());
    EXPECT_FALSE(pattern->IsMiddleGradeMaterial());
}

/**
 * @tc.name: SliderPattern_CreateParticleOptions_Horizontal_001
 * @tc.desc: Test CreateParticleOptions for horizontal direction
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_CreateParticleOptions_Horizontal_001, TestSize.Level1)
{
    auto frameNode = CreateSliderNodeWithMaterial();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    float emitterLength = 50.0f;
    float trackThickness = 10.0f;
    Axis direction = Axis::HORIZONTAL;

    auto particleOptions = pattern->CreateParticleOptions(emitterLength, trackThickness, direction, 25.0f, false);

    EXPECT_EQ(particleOptions.size(), 1);
}

/**
 * @tc.name: SliderPattern_CreateParticleOptions_Vertical_001
 * @tc.desc: Test CreateParticleOptions for vertical direction
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_CreateParticleOptions_Vertical_001, TestSize.Level1)
{
    auto frameNode = CreateSliderNodeWithMaterial();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    float emitterLength = 50.0f;
    float trackThickness = 10.0f;
    Axis direction = Axis::VERTICAL;

    auto particleOptions = pattern->CreateParticleOptions(emitterLength, trackThickness, direction, 25.0f, false);

    EXPECT_EQ(particleOptions.size(), 1);
}

/**
 * @tc.name: SliderParticleNodeHierarchy_001
 * @tc.desc: Test particleFrameNode is child of selectedTrackFrameNode
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderParticleNodeHierarchy_001, TestSize.Level1)
{
    g_uiMaterialLevel = UiMaterialLevel::EXQUISITE;
    auto frameNode = CreateSliderNodeWithMaterial();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    auto layoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateSliderMode(SliderModel::SliderMode::INSET);
    
    EXPECT_TRUE(pattern->IsNeedShowMaterial());
    EXPECT_TRUE(pattern->IsHighGradeMaterial());
}

/**
 * @tc.name: SliderPattern_HideMaterialNodes_NoParticleRemove_001
 * @tc.desc: Test HideMaterialNodes does not remove particleFrameNode from host
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_HideMaterialNodes_NoParticleRemove_001, TestSize.Level1)
{
    auto frameNode = CreateSliderNodeWithMaterial();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    pattern->particleFrameNode_ = FrameNode::CreateFrameNode(
        V2::PARTICLE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<ParticlePattern>(1));
    
    pattern->HideMaterialNodes();
}

namespace {
constexpr float MAX_WIDTH = 100.0f;
constexpr float MAX_HEIGHT = 50.0f;
const SizeF CONTAINER_SIZE(200.0f, 40.0f);
}

RefPtr<LayoutWrapperNode> CreateLayoutWrapper(RefPtr<FrameNode> frameNode)
{
    auto geometryNode = frameNode->GetGeometryNode();
    geometryNode->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));
    
    auto layoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, geometryNode, layoutProperty);
    WeakPtr<FrameNode> hostNode = AceType::WeakClaim(AceType::RawPtr(frameNode));
    layoutWrapper->Update(hostNode, geometryNode, frameNode->GetLayoutProperty());
    
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.selfIdealSize.SetSize(CONTAINER_SIZE);
    layoutConstraintSize.maxSize = CONTAINER_SIZE;
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraintSize);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();
    
    return layoutWrapper;
}

RefPtr<LayoutWrapperNode> CreateChildLayoutWrapper(RefPtr<FrameNode> childNode)
{
    auto childGeometryNode = childNode->GetGeometryNode();
    auto childLayoutProperty = childNode->GetLayoutProperty<SliderLayoutProperty>();
    auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, childGeometryNode, childLayoutProperty);
    WeakPtr<FrameNode> childHostNode = AceType::WeakClaim(AceType::RawPtr(childNode));
    childWrapper->Update(childHostNode, childGeometryNode, childNode->GetLayoutProperty());
    
    return childWrapper;
}

/**
 * @tc.name: SliderLayoutAlgorithm_Measure_IsMaterialNodeTrue
 * @tc.desc: Test Measure when child is MaterialNode, verifying branch coverage for IsMaterialNode condition
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderLayoutAlgorithm_Measure_IsMaterialNodeTrue, TestSize.Level1)
{
    auto frameNode = CreateSliderNodeWithMaterial();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    pattern->dragFrameNode_ = FrameNode::CreateFrameNode(
        V2::SLIDER_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SliderPattern>());
    ASSERT_NE(pattern->dragFrameNode_, nullptr);
    
    auto geometryNode = pattern->dragFrameNode_->GetGeometryNode();
    auto layoutProperty = pattern->dragFrameNode_->GetLayoutProperty<SliderLayoutProperty>();
    
    auto layoutWrapper = CreateLayoutWrapper(frameNode);
    auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        nullptr, geometryNode, layoutProperty);
    WeakPtr<FrameNode> hostNode = AceType::WeakClaim(AceType::RawPtr(pattern->dragFrameNode_));
    childWrapper->Update(hostNode, geometryNode, layoutProperty);
    
    layoutWrapper->AppendChild(childWrapper);
    
    EXPECT_TRUE(pattern->IsMaterialNode(pattern->dragFrameNode_));
    
    SliderLayoutAlgorithm sliderLayoutAlgorithm;
    sliderLayoutAlgorithm.Measure(AceType::RawPtr(layoutWrapper));
}

/**
 * @tc.name: SliderLayoutAlgorithm_Measure_SelectedTrackNodeNeedMeasureTrue
 * @tc.desc: Test Measure when child is SelectedTrackNode and needMeasureMaterial is true, verifying branch coverage
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderLayoutAlgorithm_Measure_SelectedTrackNodeNeedMeasureTrue, TestSize.Level1)
{
    auto frameNode = CreateSliderNodeWithMaterial();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->needMeasureMaterial_ = true;
    
    pattern->selectedTrackFrameNode_ = FrameNode::CreateFrameNode(
        V2::SLIDER_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SliderPattern>());
    ASSERT_NE(pattern->selectedTrackFrameNode_, nullptr);
    
    auto geometryNode = pattern->selectedTrackFrameNode_->GetGeometryNode();
    auto layoutProperty = pattern->selectedTrackFrameNode_->GetLayoutProperty<SliderLayoutProperty>();
    
    auto layoutWrapper = CreateLayoutWrapper(frameNode);
    auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        nullptr, geometryNode, layoutProperty);
    WeakPtr<FrameNode> hostNode = AceType::WeakClaim(AceType::RawPtr(pattern->selectedTrackFrameNode_));
    childWrapper->Update(hostNode, geometryNode, layoutProperty);
    
    layoutWrapper->AppendChild(childWrapper);
    
    EXPECT_TRUE(pattern->IsSelectedTrackNode(pattern->selectedTrackFrameNode_));
    EXPECT_TRUE(pattern->IsNeedMeasureMaterial());
    
    SliderLayoutAlgorithm sliderLayoutAlgorithm;
    sliderLayoutAlgorithm.Measure(AceType::RawPtr(layoutWrapper));
}

/**
 * @tc.name: SliderLayoutAlgorithm_Measure_SelectedTrackNodeNeedMeasureFalse
 * @tc.desc: Test Measure when child is SelectedTrackNode but needMeasureMaterial is false, verifying else branch
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderLayoutAlgorithm_Measure_SelectedTrackNodeNeedMeasureFalse, TestSize.Level1)
{
    auto frameNode = CreateSliderNodeWithMaterial();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->needMeasureMaterial_ = false;
    
    pattern->selectedTrackFrameNode_ = FrameNode::CreateFrameNode(
        V2::SLIDER_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SliderPattern>());
    ASSERT_NE(pattern->selectedTrackFrameNode_, nullptr);
    
    auto geometryNode = pattern->selectedTrackFrameNode_->GetGeometryNode();
    auto layoutProperty = pattern->selectedTrackFrameNode_->GetLayoutProperty<SliderLayoutProperty>();
    
    auto layoutWrapper = CreateLayoutWrapper(frameNode);
    auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        nullptr, geometryNode, layoutProperty);
    WeakPtr<FrameNode> hostNode = AceType::WeakClaim(AceType::RawPtr(pattern->selectedTrackFrameNode_));
    childWrapper->Update(hostNode, geometryNode, layoutProperty);
    
    layoutWrapper->AppendChild(childWrapper);
    
    EXPECT_TRUE(pattern->IsSelectedTrackNode(pattern->selectedTrackFrameNode_));
    EXPECT_FALSE(pattern->IsNeedMeasureMaterial());
    
    SliderLayoutAlgorithm sliderLayoutAlgorithm;
    sliderLayoutAlgorithm.Measure(AceType::RawPtr(layoutWrapper));
}

/**
 * @tc.name: SliderLayoutAlgorithm_Measure_SelectedTrackNodeFalse
 * @tc.desc: Test Measure when child is not SelectedTrackNode or MaterialNode, verifying implicit else branch
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderLayoutAlgorithm_Measure_SelectedTrackNodeFalse, TestSize.Level1)
{
    auto frameNode = CreateSliderNodeWithMaterial();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    
    auto otherNode = FrameNode::CreateFrameNode(
        V2::SLIDER_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SliderPattern>());
    ASSERT_NE(otherNode, nullptr);
    
    auto geometryNode = otherNode->GetGeometryNode();
    auto layoutProperty = otherNode->GetLayoutProperty<SliderLayoutProperty>();
    
    auto layoutWrapper = CreateLayoutWrapper(frameNode);
    auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        nullptr, geometryNode, layoutProperty);
    WeakPtr<FrameNode> hostNode = AceType::WeakClaim(AceType::RawPtr(otherNode));
    childWrapper->Update(hostNode, geometryNode, layoutProperty);
    
    layoutWrapper->AppendChild(childWrapper);
    
    EXPECT_FALSE(pattern->IsMaterialNode(otherNode));
    EXPECT_FALSE(pattern->IsSelectedTrackNode(otherNode));
    
    SliderLayoutAlgorithm sliderLayoutAlgorithm;
    sliderLayoutAlgorithm.Measure(AceType::RawPtr(layoutWrapper));
}

/**
 * @tc.name: SliderPattern_UpdateMaterialNodePosition_AllNodesNull_001
 * @tc.desc: Test UpdateMaterialNodePosition with all material nodes null
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_UpdateMaterialNodePosition_AllNodesNull_001, TestSize.Level1)
{
    auto frameNode = CreateSliderNodeWithMaterial();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->blockSize_ = BLOCK_SIZE_TEST;
    pattern->dragFrameNode_ = nullptr;
    pattern->blurCoverNode_ = nullptr;
    pattern->dragPointNode_ = nullptr;
    
    pattern->UpdateMaterialNodePosition(100.0f, 50.0f, 15.0f, true);
    
    EXPECT_EQ(pattern->dragFrameNode_, nullptr);
    EXPECT_EQ(pattern->blurCoverNode_, nullptr);
    EXPECT_EQ(pattern->dragPointNode_, nullptr);
}

/**
 * @tc.name: SliderPattern_UpdateMaterialNodePosition_AllNodesExist_001
 * @tc.desc: Test UpdateMaterialNodePosition with all material nodes existing
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternMaterialTestNg, SliderPattern_UpdateMaterialNodePosition_AllNodesExist_001, TestSize.Level1)
{
    auto frameNode = CreateSliderNodeWithMaterial();
    ASSERT_NE(frameNode, nullptr);
    
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->blockSize_ = BLOCK_SIZE_TEST;
    
    pattern->CreateDragFrameNode();
    pattern->CreateDragPointNode();
    pattern->CreateBlurCoverNode();
    
    ASSERT_NE(pattern->dragFrameNode_, nullptr);
    ASSERT_NE(pattern->blurCoverNode_, nullptr);
    ASSERT_NE(pattern->dragPointNode_, nullptr);

    frameNode->AddChild(pattern->dragFrameNode_);
    frameNode->AddChild(pattern->blurCoverNode_);
    frameNode->AddChild(pattern->dragPointNode_);

    pattern->UpdateMaterialNodePosition(100.0f, 50.0f, 15.0f, true);
    
    auto frameRC = pattern->dragFrameNode_->GetRenderContext();
    ASSERT_NE(frameRC, nullptr);
    EXPECT_TRUE(frameRC->GetPosition().has_value());
    
    auto blurRC = pattern->blurCoverNode_->GetRenderContext();
    ASSERT_NE(blurRC, nullptr);
    EXPECT_TRUE(blurRC->GetPosition().has_value());
    
    auto pointRC = pattern->dragPointNode_->GetRenderContext();
    ASSERT_NE(pointRC, nullptr);
    EXPECT_TRUE(pointRC->GetPosition().has_value());
}
} // namespace OHOS::Ace::NG