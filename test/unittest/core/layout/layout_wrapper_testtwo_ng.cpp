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

#include <algorithm>

#include "gtest/gtest.h"

#define protected public
#define private public

#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"

#include "base/log/ace_trace.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/layout/layout_wrapper_builder.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/custom/custom_node.h"
#include "core/components_ng/pattern/flex/flex_layout_algorithm.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/property/safe_area_insets.h"
#include "core/components_ng/syntax/lazy_for_each_model.h"
#include "core/components_ng/syntax/lazy_layout_wrapper_builder.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class SyntaxNode : public UINode {
    DECLARE_ACE_TYPE(SyntaxNode, UINode);
public:
    static RefPtr<SyntaxNode> CreateNode(const std::string& tag, int32_t nodeId)
    {
        auto spanNode = MakeRefPtr<SyntaxNode>(tag, nodeId);
        return spanNode;
    }

    bool IsAtomicNode() const override
    {
        return true;
    }

    explicit SyntaxNode(const std::string& tag, int32_t nodeId) : UINode(tag, nodeId) {}
    ~SyntaxNode() override = default;
};

class TestPattern : public Pattern {
    DECLARE_ACE_TYPE(TestPattern, Pattern);
public:
    TestPattern() = default;
    ~TestPattern() override = default;
    bool ConsumeChildrenAdjustment(const OffsetF& /* offset */) override
    {
        return true;
    }
};

namespace {
constexpr int32_t NODE_ID_0 = 0;
constexpr int32_t NODE_ID_1 = 1;
constexpr int32_t NODE_ID_2 = 2;
constexpr int32_t NODE_ID_3 = 3;

constexpr float RK356_WIDTH = 720.0f;
constexpr float RK356_HEIGHT = 1136.0f;
constexpr float ROW_HEIGHT = 120.0f;

const SizeF CONTAINER_SIZE { RK356_WIDTH, RK356_HEIGHT };
SizeF SELF_IDEAL_SIZE { RK356_WIDTH, ROW_HEIGHT };
SizeF FRAME_SIZE { 0, 0 };
const SizeF TEST_FRAME_SIZE { 0, 0 };
OptionalSize IDEAL_SIZE { 0, 0 };

const std::string TEST_TAG = "";
const std::string ROW_FRAME_NODE = "rowFrameNode";
const std::string FIRST_FRAME_NODE = "TabContent";
const std::string FIRST_CHILD_FRAME_NODE = "firstChildFrameNode";
const std::string SECOND_CHILD_FRAME_NODE = "secondChildFrameNode";
const std::string THIRD_CHILD_FRAME_NODE = "thirdChildFrameNode";

std::pair<RefPtr<FrameNode>, RefPtr<LayoutWrapper>> CreateNodeAndWrapper(
    const std::string& tag,
    int32_t nodeId,
    RectF rf = RectF())
{
    auto node = FrameNode::CreateFrameNode(tag, nodeId, AceType::MakeRefPtr<Pattern>());
    auto layoutWrapper = AceType::DynamicCast<LayoutWrapper>(node);
    auto geometryNode = node->GetGeometryNode();
    geometryNode->frame_.rect_ = rf;

    return std::make_pair(node, layoutWrapper);
}

std::pair<RefPtr<FrameNode>, RefPtr<LayoutWrapper>> CreateNodeAndWrapperTestPattern(
    const std::string& tag,
    int32_t nodeId,
    RectF rf = RectF())
{
    auto node = FrameNode::CreateFrameNode(tag, nodeId, AceType::MakeRefPtr<TestPattern>());
    auto layoutWrapper = AceType::DynamicCast<LayoutWrapper>(node);
    auto geometryNode = node->GetGeometryNode();
    geometryNode->frame_.rect_ = rf;

    return std::make_pair(node, layoutWrapper);
}

std::pair<RefPtr<FrameNode>, RefPtr<LayoutWrapper>> CreateScrollableWrapper(int32_t nodeId, RectF rf = RectF())
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::SCROLL_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<ScrollPattern>(); });
    auto layoutWrapper = AceType::DynamicCast<LayoutWrapper>(frameNode);
    auto geometryNode = frameNode->GetGeometryNode();
    geometryNode->frame_.rect_ = rf;

    return std::make_pair(frameNode, layoutWrapper);
}

std::optional<LayoutConstraintF> MakeLayoutConstraintF()
{
    std::optional<LayoutConstraintF> constraint;
    constraint = std::make_optional<LayoutConstraintF>();
    constraint->minSize = SizeF{1.0f, 2.0f};
    constraint->maxSize = SizeF{100.0f, 200.0f};
    constraint->percentReference = SizeF{10.0f, 20.0f};
    constraint->parentIdealSize = OptionalSize<float>{10.0f, 20.0f};
    constraint->selfIdealSize = OptionalSize<float>{10.0f, 20.0f};
    return constraint;
}

void PresetAttributesForStrategyTest(PaddingProperty& safeAreaPadding0, PaddingProperty& safeAreaPadding1,
    PaddingProperty& margin1, MarginPropertyF& margin1_)
{
    safeAreaPadding0 = {
        .left = CalcLength(10.0f),
        .right = CalcLength(15.0f),
        .top = CalcLength(20.0f),
        .bottom = CalcLength(25.0f)
    };
    safeAreaPadding1 = {
        .left = CalcLength(10.0f),
        .right = CalcLength(15.0f),
        .top = CalcLength(10.0f),
        .bottom = CalcLength(15.0f)
    };
    margin1 = {
        .left = CalcLength(0.0f),
        .right = CalcLength(10.0f),
        .top = CalcLength(0.0f),
        .bottom = CalcLength(10.0f)
    };
    margin1_ = {
        .left = 0.0f,
        .right = 10.0f,
        .top = 0.0f,
        .bottom = 10.0f
    };
}

void PresetSceneForStrategyTest(RefPtr<LayoutWrapper> layoutWrapper0, RefPtr<LayoutWrapper> layoutWrapper1)
{
    PaddingProperty safeAreaPadding0;
    PaddingProperty safeAreaPadding1;
    PaddingProperty margin1;
    MarginPropertyF margin1_;
    PresetAttributesForStrategyTest(safeAreaPadding0, safeAreaPadding1, margin1, margin1_);
    layoutWrapper0->GetLayoutProperty()->UpdateSafeAreaPadding(safeAreaPadding0);
    layoutWrapper1->GetLayoutProperty()->UpdateSafeAreaPadding(safeAreaPadding1);
    layoutWrapper1->GetLayoutProperty()->UpdateMargin(margin1);
    layoutWrapper1->GetGeometryNode()->UpdateMargin(margin1_);
}
} // namespace

class LayoutWrapperTestTwoNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void LayoutWrapperTestTwoNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void LayoutWrapperTestTwoNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: LayoutWrapperTest001
 * @tc.desc: Test GetParentGlobalOffsetWithSafeArea.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestTwoNg, LayoutWrapperTest001, TestSize.Level0)
{
    auto parent = FrameNode::CreateFrameNode(V2::NODE_CONTAINER_ETS_TAG, NODE_ID_0, AceType::MakeRefPtr<Pattern>());
    auto child0 = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, NODE_ID_1, AceType::MakeRefPtr<Pattern>());
    auto child1 = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, NODE_ID_2, AceType::MakeRefPtr<Pattern>());
    auto child2 = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, NODE_ID_3, AceType::MakeRefPtr<Pattern>());
    child0->MountToParent(parent);
    child1->MountToParent(child0);
    child2->MountToParent(child1);
    parent->isLayoutDirtyMarked_ = true;
    parent->CreateLayoutTask();

    EXPECT_EQ(child1->GetParentGlobalOffsetWithSafeArea(false, false), OffsetF(0, 0));
    EXPECT_EQ(child1->GetParentGlobalOffsetWithSafeArea(false, true), OffsetF(0, 0));
    EXPECT_EQ(child2->GetParentGlobalOffsetWithSafeArea(false, false), OffsetF(0, 0));
    EXPECT_EQ(child2->GetParentGlobalOffsetWithSafeArea(false, true), OffsetF(0, 0));

    auto pipeline = PipelineContext::GetCurrentContext();
    auto stageManager = pipeline->stageManager_;
    pipeline->stageManager_ = AceType::MakeRefPtr<StageManager>(parent);
    auto pageRenderContext = child1->GetRenderContext();
    child1->renderContext_ = nullptr;

    EXPECT_EQ(child1->GetParentGlobalOffsetWithSafeArea(false, false), OffsetF(0, 0));
    EXPECT_EQ(child1->GetParentGlobalOffsetWithSafeArea(false, true), OffsetF(0, 0));
    EXPECT_EQ(child2->GetParentGlobalOffsetWithSafeArea(false, false), OffsetF(0, 0));
    EXPECT_EQ(child2->GetParentGlobalOffsetWithSafeArea(false, true), OffsetF(0, 0));

    pipeline->stageManager_ = stageManager;
    child1->renderContext_ = pageRenderContext;
    pageRenderContext->UpdatePaintRect(RectF{40.0f, 40.0f, 500.0f, 1100.0f});
    pageRenderContext->GetOrCreatePositionProperty();

    EXPECT_EQ(child1->GetParentGlobalOffsetWithSafeArea(false, false), OffsetF(0, 0));
    EXPECT_EQ(child1->GetParentGlobalOffsetWithSafeArea(false, true), OffsetF(0, 0));
    EXPECT_EQ(child2->GetParentGlobalOffsetWithSafeArea(false, false), OffsetF(0, 0));
    EXPECT_EQ(child2->GetParentGlobalOffsetWithSafeArea(false, true), OffsetF(0, 0));

    pageRenderContext->GetPositionProperty()->UpdatePosition(OffsetT<Dimension>(Dimension(10.0), Dimension(10.0)));

    EXPECT_EQ(child1->GetParentGlobalOffsetWithSafeArea(false, false), OffsetF(0, 0));
    EXPECT_EQ(child1->GetParentGlobalOffsetWithSafeArea(false, true), OffsetF(0, 0));
    EXPECT_EQ(child2->GetParentGlobalOffsetWithSafeArea(false, false), OffsetF(0, 0));
    EXPECT_EQ(child2->GetParentGlobalOffsetWithSafeArea(false, true), OffsetF(10, 10));

    child1->layoutProperty_->layoutConstraint_ = MakeLayoutConstraintF();

    EXPECT_EQ(child2->GetParentGlobalOffsetWithSafeArea(false, false), OffsetF(0, 0));
    EXPECT_EQ(child2->GetParentGlobalOffsetWithSafeArea(false, true), OffsetF(10, 10));
}

/**
 * @tc.name: LayoutWrapperTest002
 * @tc.desc: Test GetFrameRectWithoutSafeArea.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestTwoNg, LayoutWrapperTest002, TestSize.Level0)
{
    auto node = FrameNode::CreateFrameNode(ROW_FRAME_NODE, NODE_ID_0, AceType::MakeRefPtr<Pattern>());
    auto layoutWrapper = AceType::DynamicCast<LayoutWrapper>(node);
    EXPECT_EQ(layoutWrapper->GetFrameRectWithoutSafeArea(), RectF());
    auto gn = node->GetGeometryNode();
    gn->frame_.rect_ = RectF{10.0f, 20.0f, 30.0f, 40.0f};
    EXPECT_EQ(layoutWrapper->GetFrameRectWithoutSafeArea(), gn->frame_.rect_);
}

/**
 * @tc.name: LayoutWrapperTest003
 * @tc.desc: Test OffsetNodeToSafeArea.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestTwoNg, LayoutWrapperTest003, TestSize.Level0)
{
    auto [frameNode, layoutWrapper] = CreateNodeAndWrapper(ROW_FRAME_NODE, NODE_ID_0);
    frameNode->layoutProperty_->UpdateSafeAreaInsets(
        SafeAreaInsets({}, { 0, 1 }, {}, { RK356_HEIGHT - 1, RK356_HEIGHT }));
    frameNode->geometryNode_->SetFrameSize({ RK356_WIDTH, RK356_HEIGHT - 2 });

    frameNode->geometryNode_->SetFrameOffset({ 0, 1 });
    layoutWrapper->OffsetNodeToSafeArea();
    EXPECT_EQ(frameNode->geometryNode_->GetFrameOffset(), OffsetF(0, 1));

    frameNode->geometryNode_->SetFrameOffset({ 0, 5 });
    layoutWrapper->OffsetNodeToSafeArea();
    EXPECT_EQ(frameNode->geometryNode_->GetFrameOffset(), OffsetF(0, 1));

    frameNode->geometryNode_->SetFrameOffset({ 0, 0 });
    layoutWrapper->OffsetNodeToSafeArea();
    EXPECT_EQ(frameNode->geometryNode_->GetFrameOffset(), OffsetF(0, 1));

    frameNode->layoutProperty_->UpdateSafeAreaInsets(
        SafeAreaInsets({ 0, 5 }, { 0, 1 }, {}, { RK356_HEIGHT - 1, RK356_HEIGHT }));
    frameNode->geometryNode_->SetFrameOffset({ 0, 0 });
    layoutWrapper->OffsetNodeToSafeArea();
    EXPECT_EQ(frameNode->geometryNode_->GetFrameOffset(), OffsetF(0, 1));

    // set right and bottom again
    frameNode->geometryNode_->SetFrameOffset({ 1, 1 });
    frameNode->layoutProperty_->UpdateSafeAreaInsets(
        SafeAreaInsets({ 0, 0 }, { 0, 0 }, { RK356_HEIGHT, RK356_HEIGHT + 1 }, { RK356_HEIGHT, RK356_HEIGHT + 1 }));
    layoutWrapper->OffsetNodeToSafeArea();
    EXPECT_EQ(frameNode->geometryNode_->GetFrameOffset().x_, 1);
    EXPECT_EQ(frameNode->geometryNode_->GetFrameOffset().y_, 1);

    frameNode->geometryNode_->SetFrameOffset({ 1, 1 });
    frameNode->layoutProperty_->UpdateSafeAreaInsets(
        SafeAreaInsets({ 0, 0 }, { 0, 0 }, { RK356_HEIGHT + 1, RK356_HEIGHT }, { RK356_HEIGHT + 1, RK356_HEIGHT }));
    layoutWrapper->OffsetNodeToSafeArea();
    EXPECT_EQ(frameNode->geometryNode_->GetFrameOffset().x_, 0);
    EXPECT_EQ(frameNode->geometryNode_->GetFrameOffset().y_, 1);
}

/**
 * @tc.name: LayoutWrapperTest004
 * @tc.desc: Test CreateRootConstraint.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestTwoNg, LayoutWrapperTest004, TestSize.Level0)
{
    auto context = PipelineContext::GetCurrentContext();
    context->rootHeight_ = RK356_HEIGHT;
    context->rootWidth_ = RK356_WIDTH;

    auto [node, layoutWrapper] = CreateNodeAndWrapper(ROW_FRAME_NODE, NODE_ID_0);
    node->geometryNode_->SetFrameSize({ RK356_WIDTH, RK356_HEIGHT });
    layoutWrapper->CreateRootConstraint();
    EXPECT_EQ(node->layoutProperty_->layoutConstraint_->percentReference.Height(), RK356_HEIGHT);
    node->layoutProperty_->UpdateAspectRatio(0.0001);
    layoutWrapper->CreateRootConstraint();
    EXPECT_EQ(node->layoutProperty_->layoutConstraint_->percentReference.Height(), 0);
    node->layoutProperty_->UpdateAspectRatio(2.0);
    layoutWrapper->CreateRootConstraint();
    EXPECT_EQ(node->layoutProperty_->layoutConstraint_->percentReference.Height(), RK356_HEIGHT / 2);
}

/**
 * @tc.name: LayoutWrapperTest005
 * @tc.desc: Test ApplyConstraintWithoutMeasure.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestTwoNg, LayoutWrapperTest005, TestSize.Level0)
{
    auto context = PipelineContext::GetCurrentContext();
    context->rootHeight_ = RK356_HEIGHT;
    context->rootWidth_ = RK356_WIDTH;

    auto [node, layoutWrapper] = CreateNodeAndWrapper(ROW_FRAME_NODE, NODE_ID_0);

    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);

    std::optional<LayoutConstraintF> constraint;
    layoutWrapper->ApplyConstraintWithoutMeasure(constraint);
    EXPECT_EQ(layoutProperty->layoutConstraint_, constraint);
    constraint = MakeLayoutConstraintF();
    layoutWrapper->ApplyConstraintWithoutMeasure(constraint);
    EXPECT_EQ(layoutProperty->layoutConstraint_, constraint);
}

/**
 * @tc.name: LayoutWrapperTest006
 * @tc.desc: Test GetPageCurrentOffset.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestTwoNg, LayoutWrapperTest006, TestSize.Level0)
{
    auto [parent, layoutWrapper] = CreateNodeAndWrapper(OHOS::Ace::V2::PAGE_ETS_TAG, NODE_ID_0);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    EXPECT_EQ(layoutWrapper->GetPageCurrentOffset(), 0.0f);

    auto [pageNode, layoutWrapper1] = CreateNodeAndWrapper(OHOS::Ace::V2::FLEX_ETS_TAG, NODE_ID_0);
    EXPECT_FALSE(layoutWrapper1 == nullptr);
    pipeline->stageManager_ = AceType::MakeRefPtr<StageManager>(pageNode);
    EXPECT_EQ(layoutWrapper->GetPageCurrentOffset(), 0.0f);
    auto [child, childWrapper] = CreateNodeAndWrapper(FIRST_CHILD_FRAME_NODE, NODE_ID_2);
    child->MountToParent(pageNode);
    EXPECT_EQ(layoutWrapper->GetPageCurrentOffset(), 0.0f);

    pipeline->safeAreaManager_->SetIsFullScreen(true);
    pipeline->safeAreaManager_->SetIsAtomicService(true);
    EXPECT_EQ(layoutWrapper->GetPageCurrentOffset(), 0.0f);
    EXPECT_EQ(layoutWrapper1->GetPageCurrentOffset(), 0.0f);
    pipeline->safeAreaManager_->SetIsAtomicService(false);
    pipeline->safeAreaManager_->UpdateCutoutSafeArea(
        NG::SafeAreaInsets({10.0f, 40.0f}, {20.0f, 50.0f}, {680.0f, 710.0f}, {1230.0f, 1260.0f}));
    pipeline->safeAreaManager_->UpdateSystemSafeArea(
        NG::SafeAreaInsets({0.0f, 30.0f}, {0.0f, 30.0f}, {690.0f, 720.0f}, {1250.0f, 1280.0f}));
    pipeline->safeAreaManager_->UpdateNavSafeArea(
        NG::SafeAreaInsets({20.0f, 50.0f}, {40.0f, 70.0f}, {670.0f, 700.0f}, {1210.0f, 1240.0f}));
    EXPECT_EQ(layoutWrapper->GetPageCurrentOffset(), -70.0f);
    EXPECT_EQ(layoutWrapper1->GetPageCurrentOffset(), -70.0f);
}

/**
 * @tc.name: LayoutWrapperTest007
 * @tc.desc: Test ExpandIntoKeyboard.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestTwoNg, LayoutWrapperTest007, TestSize.Level0)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    auto [parent, layoutWrapper] = CreateNodeAndWrapper(OHOS::Ace::V2::FLEX_ETS_TAG, NODE_ID_0);
    auto [child0, nodeLayoutWrapper1] = CreateNodeAndWrapper(OHOS::Ace::V2::JS_VIEW_ETS_TAG, NODE_ID_1);
    child0->MountToParent(parent);
    auto [child1, childWrapper] = CreateNodeAndWrapper(FIRST_CHILD_FRAME_NODE, NODE_ID_2);
    child1->MountToParent(child0);
    auto [child2, childWrapper2] = CreateNodeAndWrapper(FIRST_CHILD_FRAME_NODE, NODE_ID_3);
    child2->MountToParent(child1);
    pipeline->stageManager_ = AceType::MakeRefPtr<StageManager>(parent);
    auto pageRenderContext = child1->GetRenderContext();
    pageRenderContext->UpdatePaintRect(RectF{40.0f, 40.0f, 500.0f, 1100.0f});

    pipeline->safeAreaManager_->SetIsAtomicService(true);
    pipeline->safeAreaManager_->SetIsFullScreen(true);
    pipeline->safeAreaManager_->UpdateCutoutSafeArea(
        NG::SafeAreaInsets({10.0f, 40.0f}, {20.0f, 50.0f}, {680.0f, 710.0f}, {1230.0f, 1260.0f}));
    pipeline->safeAreaManager_->UpdateSystemSafeArea(
        NG::SafeAreaInsets({0.0f, 30.0f}, {0.0f, 30.0f}, {690.0f, 720.0f}, {1250.0f, 1280.0f}));
    pipeline->safeAreaManager_->UpdateNavSafeArea(
        NG::SafeAreaInsets({20.0f, 50.0f}, {40.0f, 70.0f}, {670.0f, 700.0f}, {1210.0f, 1240.0f}));
    pipeline->safeAreaManager_->UpdateKeyboardOffset(50.0f);

    EXPECT_EQ(parent->ExpandIntoKeyboard(), OffsetF(0.0f, 0.0f));
    EXPECT_EQ(child0->ExpandIntoKeyboard(), OffsetF(0.0f, 0.0f));
    EXPECT_EQ(child1->ExpandIntoKeyboard(), OffsetF(0.0f, 0.0f));
    EXPECT_EQ(child2->ExpandIntoKeyboard(), OffsetF(0.0f, 0.0f));

    pipeline->stageManager_ = AceType::MakeRefPtr<StageManager>(parent);
    pageRenderContext->GetOrCreatePositionProperty();
    pipeline->safeAreaManager_->SetIsAtomicService(false);

    EXPECT_EQ(parent->ExpandIntoKeyboard(), OffsetF(0.0f, -50.0f));
    EXPECT_EQ(child0->ExpandIntoKeyboard(), OffsetF(0.0f, -50.0f));
    EXPECT_EQ(child1->ExpandIntoKeyboard(), OffsetF(0.0f, -50.0f));
    EXPECT_EQ(child2->ExpandIntoKeyboard(), OffsetF(0.0f, -50.0f));
    parent->layoutProperty_->UpdateSafeAreaExpandOpts({ SAFE_AREA_TYPE_ALL, SAFE_AREA_EDGE_ALL });
    child0->layoutProperty_->UpdateSafeAreaExpandOpts({ SAFE_AREA_TYPE_ALL, SAFE_AREA_EDGE_ALL });
    child1->layoutProperty_->UpdateSafeAreaExpandOpts({ SAFE_AREA_TYPE_ALL, SAFE_AREA_EDGE_ALL });
    EXPECT_EQ(parent->ExpandIntoKeyboard(), OffsetF(0.0f, -50.0f));
    EXPECT_EQ(child0->ExpandIntoKeyboard(), OffsetF(0.0f, 0.0f));
    EXPECT_EQ(child1->ExpandIntoKeyboard(), OffsetF(0.0f, 0.0f));
}

/**
 * @tc.name: LayoutWrapperTest008
 * @tc.desc: Test CheckValidSafeArea.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestTwoNg, LayoutWrapperTest008, TestSize.Level0)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    auto [parent, layoutWrapper] = CreateNodeAndWrapper(OHOS::Ace::V2::FLEX_ETS_TAG, NODE_ID_0);
    auto [child0, childWrapper0] = CreateNodeAndWrapper(OHOS::Ace::V2::JS_VIEW_ETS_TAG, NODE_ID_1);
    child0->MountToParent(parent);

    auto [child1, childWrapper1] = CreateNodeAndWrapper(FIRST_CHILD_FRAME_NODE, NODE_ID_2);
    child1->MountToParent(child0);

    auto [child2, childWrapper2] = CreateNodeAndWrapper(FIRST_CHILD_FRAME_NODE, NODE_ID_3);
    child2->MountToParent(child1);

    pipeline->safeAreaManager_->UpdateCutoutSafeArea(
        NG::SafeAreaInsets({10.0f, 40.0f}, {20.0f, 50.0f}, {680.0f, 710.0f}, {1230.0f, 1260.0f}));
    pipeline->safeAreaManager_->UpdateSystemSafeArea(
        NG::SafeAreaInsets({0.0f, 30.0f}, {0.0f, 30.0f}, {690.0f, 720.0f}, {1250.0f, 1280.0f}));
    pipeline->safeAreaManager_->UpdateNavSafeArea(
        NG::SafeAreaInsets({20.0f, 50.0f}, {40.0f, 70.0f}, {670.0f, 700.0f}, {1210.0f, 1240.0f}));

    EXPECT_FALSE(layoutWrapper->CheckValidSafeArea());
    EXPECT_FALSE(childWrapper0->CheckValidSafeArea());
    EXPECT_FALSE(childWrapper1->CheckValidSafeArea());
    EXPECT_FALSE(childWrapper2->CheckValidSafeArea());
    parent->layoutProperty_->UpdateSafeAreaExpandOpts({ SAFE_AREA_TYPE_ALL, SAFE_AREA_EDGE_ALL });
    child0->layoutProperty_->UpdateSafeAreaExpandOpts({ SAFE_AREA_TYPE_ALL, SAFE_AREA_EDGE_ALL });
    child1->layoutProperty_->UpdateSafeAreaExpandOpts({ SAFE_AREA_TYPE_ALL, SAFE_AREA_EDGE_ALL });
    child2->layoutProperty_->UpdateSafeAreaExpandOpts({ SAFE_AREA_TYPE_ALL, SAFE_AREA_EDGE_ALL });
    EXPECT_TRUE(layoutWrapper->CheckValidSafeArea());
    EXPECT_TRUE(childWrapper0->CheckValidSafeArea());
    EXPECT_TRUE(childWrapper1->CheckValidSafeArea());
    EXPECT_TRUE(childWrapper2->CheckValidSafeArea());

    pipeline->stageManager_ = AceType::MakeRefPtr<StageManager>(parent);
    auto pageRenderContext = child1->GetRenderContext();
    pageRenderContext->UpdatePaintRect(RectF{40.0f, 40.0f, 500.0f, 1100.0f});
    pageRenderContext->GetOrCreatePositionProperty();

    pipeline->safeAreaManager_->SetIsAtomicService(true);
    pipeline->safeAreaManager_->SetIsFullScreen(true);
    EXPECT_TRUE(layoutWrapper->CheckValidSafeArea());
    EXPECT_TRUE(childWrapper0->CheckValidSafeArea());
    EXPECT_TRUE(childWrapper1->CheckValidSafeArea());
    EXPECT_TRUE(childWrapper2->CheckValidSafeArea());
}

/**
 * @tc.name: LayoutWrapperTest009
 * @tc.desc: Test AdjustNotExpandNode.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestTwoNg, LayoutWrapperTest009, TestSize.Level0)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    auto [parent, layoutWrapper] = CreateNodeAndWrapper(OHOS::Ace::V2::FLEX_ETS_TAG, NODE_ID_0);

    auto geometryNode = layoutWrapper->GetGeometryNode();
    geometryNode->frame_.rect_.SetRect(0, 0, 0, 0);
    geometryNode->parentAdjust_.SetRect(0, 0, 10, 10);

    pipeline->safeAreaManager_->ignoreSafeArea_ = true;

    layoutWrapper->AdjustNotExpandNode();
    EXPECT_EQ(geometryNode->GetSelfAdjust(), RectF(0, 0, 0, 0));

    pipeline->safeAreaManager_->ignoreSafeArea_ = false;
    pipeline->safeAreaManager_->isFullScreen_ = true;

    layoutWrapper->AdjustNotExpandNode();
    EXPECT_EQ(geometryNode->GetSelfAdjust(), RectF(0, 0, 10, 10));
}

/**
 * @tc.name: LayoutWrapperTest010
 * @tc.desc: Test ExpandSafeArea.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestTwoNg, LayoutWrapperTest010, TestSize.Level0)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    auto [parent, layoutWrapper] = CreateNodeAndWrapper(OHOS::Ace::V2::FLEX_ETS_TAG, NODE_ID_0);
    auto [child0, childWrapper0] = CreateNodeAndWrapper(OHOS::Ace::V2::JS_VIEW_ETS_TAG, NODE_ID_1);
    child0->geometryNode_->frame_.rect_ = RectF(0.0f, 0.0f, 100.0f, 100.0f);
    child0->MountToParent(parent);
    child0->renderContext_ = AceType::MakeRefPtr<MockRenderContext>();
    auto [child1, childWrapper1] = CreateScrollableWrapper(NODE_ID_2, RectF(30.0f, 40.0f, 40.0f, 50.0f));
    child1->MountToParent(child0);
    auto mockRender1 = AceType::MakeRefPtr<MockRenderContext>();
    child1->renderContext_ = mockRender1;
    auto [child2, childWrapper2] = CreateScrollableWrapper(NODE_ID_3, RectF(40.0f, 40.0f, 20.0f, 10.0f));
    child2->MountToParent(child1);
    child0->layoutProperty_->safeAreaExpandOpts_ = std::make_unique<SafeAreaExpandOpts>();
    child1->layoutProperty_->safeAreaExpandOpts_ = std::make_unique<SafeAreaExpandOpts>();
    child0->layoutProperty_->safeAreaExpandOpts_->switchToNone = true;
    child1->layoutProperty_->safeAreaExpandOpts_->switchToNone = true;
    childWrapper0->ExpandSafeArea();
    childWrapper1->ExpandSafeArea();
    child0->layoutProperty_->safeAreaExpandOpts_->edges |= SAFE_AREA_EDGE_BOTTOM;
    pipeline->safeAreaManager_->SetIgnoreSafeArea(true);
    childWrapper0->ExpandSafeArea();
    childWrapper1->ExpandSafeArea();
    pipeline->safeAreaManager_->SetIgnoreSafeArea(false);
    childWrapper0->ExpandSafeArea();
    childWrapper1->ExpandSafeArea();
    child0->layoutProperty_->safeAreaExpandOpts_->type |= SAFE_AREA_TYPE_KEYBOARD;
    pipeline->safeAreaManager_->SetIgnoreSafeArea(true);
    childWrapper0->ExpandSafeArea();
    childWrapper1->ExpandSafeArea();
    pipeline->safeAreaManager_->SetIgnoreSafeArea(false);
    childWrapper0->ExpandSafeArea();
    childWrapper1->ExpandSafeArea();
    child0->layoutProperty_->safeAreaExpandOpts_ = std::make_unique<SafeAreaExpandOpts>();
    child1->layoutProperty_->safeAreaExpandOpts_->type |= SAFE_AREA_TYPE_KEYBOARD;
    pipeline->safeAreaManager_->SetIgnoreSafeArea(true);
    childWrapper0->ExpandSafeArea();
    childWrapper1->ExpandSafeArea();
    pipeline->safeAreaManager_->SetIgnoreSafeArea(false);
    childWrapper0->ExpandSafeArea();
    childWrapper1->ExpandSafeArea();
    child1->GetGeometryNode()->parentAdjust_.SetRect(0, 0, 10, 10);
    pipeline->safeAreaManager_->ignoreSafeArea_ = false;
    pipeline->safeAreaManager_->isFullScreen_ = true;
    childWrapper1->ExpandSafeArea();
    EXPECT_EQ(mockRender1->paintRect_, RectF(0, 0, 10, 10));
}

/**
 * @tc.name: LayoutWrapperTest011
 * @tc.desc: Test AdjustFixedSizeNode.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestTwoNg, LayoutWrapperTest011, TestSize.Level0)
{
    RectF frame;
    auto node = FrameNode::CreateFrameNode(ROW_FRAME_NODE, NODE_ID_0, AceType::MakeRefPtr<Pattern>());
    auto layoutWrapper = AceType::DynamicCast<LayoutWrapper>(node);
    layoutWrapper->AdjustFixedSizeNode(frame);
    EXPECT_EQ(frame, RectF());

    auto gn = node->GetGeometryNode();
    gn->frame_.rect_ = RectF{10.0f, 20.0f, 1200.0f, 1200.0f};
    layoutWrapper->AdjustFixedSizeNode(frame);
    EXPECT_EQ(frame, RectF());

    node->GetLayoutProperty()->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    node->GetLayoutProperty()->calcLayoutConstraint_->selfIdealSize =
                std::make_optional<CalcSize>(CalcLength(10.0), CalcLength(20.0));
    
    node->GetLayoutProperty()->magicItemProperty_.UpdateAspectRatio(20.0f);
    layoutWrapper->AdjustFixedSizeNode(frame);
    EXPECT_EQ(frame, RectF(0.0f, 0.0f, 1200.0f, 60.0f));
}

/**
 * @tc.name: LayoutWrapperTest015
 * @tc.desc: Test AvoidKeyboard.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestTwoNg, LayoutWrapperTest015, TestSize.Level0)
{
    auto node = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, NODE_ID_0, AceType::MakeRefPtr<Pattern>());
    auto layoutWrapper = AceType::DynamicCast<LayoutWrapper>(node);
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    RefPtr<FocusHub> focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    focusHub->currentFocus_ = false;
    node->focusHub_ = focusHub;
    node->eventHub_ = eventHub;

    RefPtr<SafeAreaManager> safeAreamanager = AceType::MakeRefPtr<SafeAreaManager>();
    safeAreamanager->keyboardOffset_ = -1.0f;

    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    safeAreamanager->SetIsAtomicService(true);
    pipeline->safeAreaManager_ = safeAreamanager;

    node->SetActive(true);
    EXPECT_TRUE(layoutWrapper->AvoidKeyboard());
    EXPECT_FALSE(layoutWrapper->AvoidKeyboard(false));
    EXPECT_TRUE(node->GetFocusHub());
    EXPECT_TRUE(!node->GetFocusHub()->IsCurrentFocus());
    EXPECT_TRUE(LessNotEqual(safeAreamanager->GetKeyboardOffset(), 0.0));
}

/**
 * @tc.name: LayoutWrapperTest016
 * @tc.desc: Test GetFrameRectWithSafeArea.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestTwoNg, LayoutWrapperTest016, TestSize.Level0)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    auto [parent, layoutWrapper] = CreateNodeAndWrapper(OHOS::Ace::V2::FLEX_ETS_TAG, NODE_ID_0);
    auto [child0, childWrapper0] = CreateNodeAndWrapper(OHOS::Ace::V2::JS_VIEW_ETS_TAG, NODE_ID_1);
    child0->geometryNode_ = AceType::MakeRefPtr<GeometryNode>();
    child0->geometryNode_->frame_.rect_ = RectF{10.0f, 20.0f, 30.0f, 40.0f};
    child0->MountToParent(parent);
    auto [child1, childWrapper1] = CreateNodeAndWrapper(FIRST_CHILD_FRAME_NODE, NODE_ID_2);
    child1->geometryNode_ = AceType::MakeRefPtr<GeometryNode>();
    child1->geometryNode_->frame_.rect_ = RectF{10.0f, 20.0f, 30.0f, 40.0f};
    child1->MountToParent(child0);
    auto [child2, childWrapper2] = CreateNodeAndWrapper(FIRST_CHILD_FRAME_NODE, NODE_ID_3);
    child2->geometryNode_ = AceType::MakeRefPtr<GeometryNode>();
    child2->geometryNode_->frame_.rect_ = RectF{10.0f, 20.0f, 30.0f, 40.0f};
    child2->MountToParent(child1);

    EXPECT_EQ(childWrapper1->GetFrameRectWithSafeArea(false), RectF(10.0f, 20.0f, 30.0f, 40.0f));
    EXPECT_EQ(childWrapper1->GetFrameRectWithSafeArea(true), RectF(10.0f, 20.0f, 30.0f, 40.0f));
    EXPECT_EQ(childWrapper2->GetFrameRectWithSafeArea(false), RectF(10.0f, 20.0f, 30.0f, 40.0f));
    EXPECT_EQ(childWrapper2->GetFrameRectWithSafeArea(true), RectF(10.0f, 20.0f, 30.0f, 40.0f));
    auto pageRenderContext = child1->GetRenderContext();
    child1->renderContext_ = nullptr;
    EXPECT_EQ(childWrapper1->GetFrameRectWithSafeArea(false), RectF(10.0f, 20.0f, 30.0f, 40.0f));
    EXPECT_EQ(childWrapper1->GetFrameRectWithSafeArea(true), RectF(10.0f, 20.0f, 30.0f, 40.0f));
    EXPECT_EQ(childWrapper2->GetFrameRectWithSafeArea(false), RectF(10.0f, 20.0f, 30.0f, 40.0f));
    EXPECT_EQ(childWrapper2->GetFrameRectWithSafeArea(true), RectF(10.0f, 20.0f, 30.0f, 40.0f));
    pipeline->stageManager_ = AceType::MakeRefPtr<StageManager>(parent);
    child1->renderContext_ = pageRenderContext;
    pageRenderContext->UpdatePaintRect(RectF{40.0f, 40.0f, 500.0f, 1100.0f});
    pageRenderContext->GetOrCreatePositionProperty();
    EXPECT_EQ(childWrapper1->GetFrameRectWithSafeArea(false), RectF(10.0f, 20.0f, 30.0f, 40.0f));
    EXPECT_EQ(childWrapper1->GetFrameRectWithSafeArea(true), RectF(10.0f, 20.0f, 30.0f, 40.0f));
    EXPECT_EQ(childWrapper2->GetFrameRectWithSafeArea(false), RectF(10.0f, 20.0f, 30.0f, 40.0f));
    EXPECT_EQ(childWrapper2->GetFrameRectWithSafeArea(true), RectF(10.0f, 20.0f, 30.0f, 40.0f));
    pageRenderContext->GetPositionProperty()->UpdatePosition(OffsetT<Dimension>(Dimension(10.0), Dimension(10.0)));
    EXPECT_EQ(childWrapper1->GetFrameRectWithSafeArea(false), RectF(10.0f, 20.0f, 30.0f, 40.0f));
    EXPECT_EQ(childWrapper1->GetFrameRectWithSafeArea(true), RectF());
    EXPECT_EQ(childWrapper2->GetFrameRectWithSafeArea(false), RectF(10.0f, 20.0f, 30.0f, 40.0f));
    EXPECT_EQ(childWrapper2->GetFrameRectWithSafeArea(true), RectF(10.0f, 20.0f, 30.0f, 40.0f));
    child1->layoutProperty_->layoutConstraint_ = MakeLayoutConstraintF();
    EXPECT_EQ(childWrapper1->GetFrameRectWithSafeArea(false), RectF(10.0f, 20.0f, 30.0f, 40.0f));
    EXPECT_EQ(childWrapper1->GetFrameRectWithSafeArea(true), RectF(10.0f, 10.0f, 30.0f, 40.0f));
    EXPECT_EQ(childWrapper2->GetFrameRectWithSafeArea(false), RectF(10.0f, 20.0f, 30.0f, 40.0f));
    EXPECT_EQ(childWrapper2->GetFrameRectWithSafeArea(true), RectF(10.0f, 20.0f, 30.0f, 40.0f));
}

/**
 * @tc.name: LayoutWrapperTest018
 * @tc.desc: Test ExpandHelper.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestTwoNg, LayoutWrapperTest018, TestSize.Level0)
{
    std::unique_ptr<SafeAreaExpandOpts> opts = nullptr;
    RectF tmpFrame = RectF{20.0f, 30.0f, 670.0f, 1220.0f};
    auto pipeline = PipelineContext::GetCurrentContext();
    auto node = FrameNode::CreateFrameNode(ROW_FRAME_NODE, NODE_ID_0, AceType::MakeRefPtr<Pattern>());
    auto layoutWrapper = AceType::DynamicCast<LayoutWrapper>(node);
    auto gn = node->GetGeometryNode();
    gn->frame_.rect_ = RectF{10.0f, 20.0f, 30.0f, 40.0f};
    RectF frame = tmpFrame;
    layoutWrapper->ExpandHelper(opts, frame);
    EXPECT_EQ(frame, tmpFrame);
    frame = tmpFrame;

    opts = std::make_unique<SafeAreaExpandOpts>();
    layoutWrapper->ExpandHelper(opts, frame);
    EXPECT_EQ(frame, tmpFrame);
    frame = tmpFrame;
    opts->edges |= SAFE_AREA_EDGE_START;
    opts->edges |= SAFE_AREA_EDGE_TOP;
    opts->edges |= SAFE_AREA_EDGE_END;
    opts->edges |= SAFE_AREA_EDGE_BOTTOM;
    layoutWrapper->ExpandHelper(opts, frame);
    EXPECT_EQ(frame, tmpFrame);

    opts->type |= SAFE_AREA_TYPE_SYSTEM;
    pipeline->safeAreaManager_->SetIsFullScreen(true);
    pipeline->safeAreaManager_->UpdateSystemSafeArea(
        NG::SafeAreaInsets({10.0f, 40.0f}, {20.0f, 50.0f}, {680.0f, 710.0f}, {1230.0f, 1260.0f}));
    layoutWrapper->ExpandHelper(opts, frame);
    EXPECT_EQ(frame, RectF(10.0f, 20.0f, 700.0f, 1240.0f));
}

/**
 * @tc.name: LayoutWrapperTest019
 * @tc.desc: Test IsSyntaxNode
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestTwoNg, LayoutWrapperTest019, TestSize.Level0)
{
    auto [parent, layoutWrapper] = CreateNodeAndWrapper(V2::JS_VIEW_ETS_TAG, NODE_ID_0);

    auto node = SyntaxNode::CreateNode(V2::JS_VIEW_ETS_TAG, NODE_ID_0);
    parent->MountToParent(node);
    layoutWrapper->AdjustChild(node, OffsetF(), false);
    node = SyntaxNode::CreateNode(V2::JS_FOR_EACH_ETS_TAG, NODE_ID_0);
    layoutWrapper->AdjustChild(node, OffsetF(), false);
    node = SyntaxNode::CreateNode(V2::JS_IF_ELSE_ETS_TAG, NODE_ID_0);
    layoutWrapper->AdjustChild(node, OffsetF(), false);
    node = SyntaxNode::CreateNode(V2::JS_LAZY_FOR_EACH_ETS_TAG, NODE_ID_0);
    layoutWrapper->AdjustChild(node, OffsetF(), false);
    node = SyntaxNode::CreateNode(V2::JS_SYNTAX_ITEM_ETS_TAG, NODE_ID_0);
    layoutWrapper->AdjustChild(node, OffsetF(), false);
    node = SyntaxNode::CreateNode(V2::JS_NODE_SLOT_ETS_TAG, NODE_ID_0);
    layoutWrapper->AdjustChild(node, OffsetF(), false);
    node = SyntaxNode::CreateNode(V2::TOAST_ETS_TAG, NODE_ID_0);
    layoutWrapper->AdjustChild(node, OffsetF(), false);

    auto geometryNode = parent->GetGeometryNode();
    geometryNode->parentAdjust_.SetRect(0, 0, 10, 10);
    layoutWrapper->AdjustChild(parent, OffsetF(), false);
    EXPECT_EQ(geometryNode->parentAdjust_, RectF(0, 0, 0, 0));

    geometryNode->parentAdjust_.SetRect(0, 0, 10, 10);
    layoutWrapper->AdjustChild(parent, OffsetF(), true);
    EXPECT_EQ(geometryNode->parentAdjust_, RectF(0, 0, 10, 10));
}

/**
 * @tc.name: LayoutWrapperTest020
 * @tc.desc: Test AdjustChildren
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestTwoNg, LayoutWrapperTest020, TestSize.Level0)
{
    auto [parent0, layoutWrapper0] = CreateNodeAndWrapper(V2::JS_VIEW_ETS_TAG, NODE_ID_0);
    layoutWrapper0->hostNode_ = nullptr;
    layoutWrapper0->AdjustChildren(OffsetF(), false);

    auto [parent1, layoutWrapper1] = CreateNodeAndWrapper(V2::JS_VIEW_ETS_TAG, NODE_ID_0);
    for (const auto& childUI : parent1->GetChildren()) {
        auto child = AceType::DynamicCast<FrameNode>(childUI);
        auto geometryNode = child->GetGeometryNode();
        geometryNode->parentAdjust_.SetRect(0, 0, 10, 10);
    }
    layoutWrapper1->AdjustChildren(OffsetF(), false);
    for (const auto& childUI : parent1->GetChildren()) {
        auto child = AceType::DynamicCast<FrameNode>(childUI);
        auto geometryNode = child->GetGeometryNode();
        EXPECT_EQ(geometryNode->parentAdjust_, RectF(0, 0, 0, 0));
    }

    auto [parent2, layoutWrapper2] = CreateNodeAndWrapper(V2::JS_VIEW_ETS_TAG, NODE_ID_0);
    for (const auto& childUI : parent2->GetChildren()) {
        auto child = AceType::DynamicCast<FrameNode>(childUI);
        auto geometryNode = child->GetGeometryNode();
        geometryNode->parentAdjust_.SetRect(0, 0, 10, 10);
    }
    layoutWrapper2->AdjustChildren(OffsetF(), false);
    for (const auto& childUI : parent2->GetChildren()) {
        auto child = AceType::DynamicCast<FrameNode>(childUI);
        auto geometryNode = child->GetGeometryNode();
        EXPECT_EQ(geometryNode->parentAdjust_, RectF(0, 0, 0, 0));
    }

    auto [parent3, layoutWrapper3] = CreateNodeAndWrapperTestPattern(V2::JS_VIEW_ETS_TAG, NODE_ID_0);
    for (const auto& childUI : parent3->GetChildren()) {
        auto child = AceType::DynamicCast<FrameNode>(childUI);
        auto geometryNode = child->GetGeometryNode();
        geometryNode->parentAdjust_.SetRect(0, 0, 10, 10);
    }
    layoutWrapper3->AdjustChildren(OffsetF(), false);
    for (const auto& childUI : parent3->GetChildren()) {
        auto child = AceType::DynamicCast<FrameNode>(childUI);
        auto geometryNode = child->GetGeometryNode();
        EXPECT_EQ(geometryNode->parentAdjust_, RectF(0, 0, 0, 0));
    }
}

/**
 * @tc.name: LayoutWrapperTest021
 * @tc.desc: Test AvoidKeyboard.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestTwoNg, LayoutWrapperTest021, TestSize.Level0)
{
    auto node = FrameNode::CreateFrameNode(V2::OVERLAY_ETS_TAG, NODE_ID_0, AceType::MakeRefPtr<Pattern>());
    auto layoutWrapper = AceType::DynamicCast<LayoutWrapper>(node);
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    RefPtr<FocusHub> focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    focusHub->currentFocus_ = false;
    node->focusHub_ = focusHub;
    node->eventHub_ = eventHub;

    RefPtr<SafeAreaManager> safeAreamanager = AceType::MakeRefPtr<SafeAreaManager>();
    safeAreamanager->keyboardOffset_ = -1.0f;

    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->overlayManager_ = nullptr;
    safeAreamanager->SetIsAtomicService(true);
    pipeline->safeAreaManager_ = safeAreamanager;

    node->SetActive(true);
    EXPECT_TRUE(layoutWrapper->AvoidKeyboard());
    EXPECT_FALSE(layoutWrapper->AvoidKeyboard(false));
    EXPECT_TRUE(LessNotEqual(safeAreamanager->GetKeyboardOffset(), 0.0));
}
/**
 * @tc.name: IgnoreLayoutProcessTagFuncs
 * @tc.desc: Test Get,Set,ResetIgnoreLayoutProcess.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestTwoNg, IgnoreLayoutProcessTagFuncs, TestSize.Level0)
{
    auto node = FrameNode::CreateFrameNode(V2::OVERLAY_ETS_TAG, NODE_ID_0, AceType::MakeRefPtr<Pattern>());
    auto layoutWrapper = AceType::DynamicCast<LayoutWrapper>(node);
    EXPECT_EQ(layoutWrapper->GetIgnoreLayoutProcess(), false);
    layoutWrapper->SetIgnoreLayoutProcess(true);
    EXPECT_EQ(layoutWrapper->GetIgnoreLayoutProcess(), true);
    layoutWrapper->ResetIgnoreLayoutProcess();
    EXPECT_EQ(layoutWrapper->GetIgnoreLayoutProcess(), false);
}

/**
 * @tc.name: HasPreMeasuredTest
 * @tc.desc: Test SetHasPreMeasured, GetHasPreMeasured and CheckHasPreMeasured
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestTwoNg, HasPreMeasuredTest, TestSize.Level0)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    auto [node, layoutWrapper] = CreateNodeAndWrapper(OHOS::Ace::V2::FLEX_ETS_TAG, NODE_ID_0);
    EXPECT_EQ(layoutWrapper->CheckHasPreMeasured(), false);
    EXPECT_EQ(layoutWrapper->GetHasPreMeasured(), false);
    layoutWrapper->SetHasPreMeasured();
    EXPECT_EQ(layoutWrapper->CheckHasPreMeasured(), true);
    EXPECT_EQ(layoutWrapper->GetHasPreMeasured(), true);
    EXPECT_EQ(layoutWrapper->CheckHasPreMeasured(), false);
    EXPECT_EQ(layoutWrapper->GetHasPreMeasured(), false);
}

/**
 * @tc.name: DelaySelfLayoutForIgnoreTest
 * @tc.desc: Test SetDelaySelfLayoutForIgnore and GetDelaySelfLayoutForIgnore
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestTwoNg, DelaySelfLayoutForIgnoreTest, TestSize.Level0)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    auto [node, layoutWrapper] = CreateNodeAndWrapper(OHOS::Ace::V2::FLEX_ETS_TAG, NODE_ID_0);
    EXPECT_EQ(layoutWrapper->GetDelaySelfLayoutForIgnore(), false);
    layoutWrapper->SetDelaySelfLayoutForIgnore();
    EXPECT_EQ(layoutWrapper->GetDelaySelfLayoutForIgnore(), true);
    EXPECT_EQ(layoutWrapper->GetDelaySelfLayoutForIgnore(), false);
}

/**
 * @tc.name: EscapeDelayForIgnoreTest
 * @tc.desc: Test SetEscapeDelayForIgnore and GetEscapeDelayForIgnore
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestTwoNg, EscapeDelayForIgnoreTest, TestSize.Level0)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    auto [node, layoutWrapper] = CreateNodeAndWrapper(OHOS::Ace::V2::FLEX_ETS_TAG, NODE_ID_0);
    EXPECT_EQ(layoutWrapper->GetEscapeDelayForIgnore(), false);
    layoutWrapper->SetEscapeDelayForIgnore(true);
    EXPECT_EQ(layoutWrapper->GetEscapeDelayForIgnore(), true);
    layoutWrapper->SetEscapeDelayForIgnore(false);
    EXPECT_EQ(layoutWrapper->GetEscapeDelayForIgnore(), false);
}

/**
 * @tc.name: EdgeControlOnGetAccumulatedSafeAreaExpand
 * @tc.desc: Test GetAccumulatedSafeAreaExpand with edges options
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestTwoNg, EdgeControlOnGetAccumulatedSafeAreaExpand, TestSize.Level0)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    auto [node0, layoutWrapper0] =
        CreateNodeAndWrapper(OHOS::Ace::V2::FLEX_ETS_TAG, NODE_ID_0, RectF(0.0f, 0.0f, 100.0f, 100.0f));
    auto [child, layoutWrapper1] =
        CreateNodeAndWrapper(OHOS::Ace::V2::FLEX_ETS_TAG, NODE_ID_1, RectF(10.0f, 20.0f, 75.0f, 55.0f));
    child->MountToParent(node0);

    PaddingProperty safeAreaPadding = {
        .left = CalcLength(10.0f),
        .right = CalcLength(15.0f),
        .top = CalcLength(20.0f),
        .bottom = CalcLength(25.0f)
    };
    layoutWrapper0->GetLayoutProperty()->UpdateSafeAreaPadding(safeAreaPadding);

    ExpandEdges expectedRes = {
        .left = std::make_optional<float>(10.0f),
        .right = std::nullopt,
        .top = std::make_optional<float>(20.0f),
        .bottom = std::nullopt
    };

    EXPECT_EQ(layoutWrapper1->GetAccumulatedSafeAreaExpand(false, {
        .type = NG::LAYOUT_SAFE_AREA_TYPE_SYSTEM,
        .edges = NG::LAYOUT_SAFE_AREA_EDGE_START | NG::LAYOUT_SAFE_AREA_EDGE_TOP
    }), expectedRes);
}

/**
 * @tc.name: TypeControlOnGetAccumulatedSafeAreaExpand
 * @tc.desc: Test GetAccumulatedSafeAreaExpand with Types options
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestTwoNg, TypeControlOnGetAccumulatedSafeAreaExpand, TestSize.Level0)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    auto [parent, parentWrapper] =
        CreateNodeAndWrapper(V2::STAGE_ETS_TAG, NODE_ID_0, RectF(0.0f, 0.0f, 200.0f, 200.0f));
    auto [node0, layoutWrapper0] =
        CreateNodeAndWrapper(OHOS::Ace::V2::FLEX_ETS_TAG, NODE_ID_1, RectF(0.0f, 30.0f, 100.0f, 140.0f));
    node0->MountToParent(parent);
    auto [child, layoutWrapper1] =
        CreateNodeAndWrapper(OHOS::Ace::V2::FLEX_ETS_TAG, NODE_ID_2, RectF(10.0f, 20.0f, 75.0f, 95.0f));
    child->MountToParent(node0);
    
    pipeline->stageManager_ = AceType::MakeRefPtr<StageManager>(parent);
    pipeline->safeAreaManager_->SetIgnoreSafeArea(false);
    pipeline->safeAreaManager_->SetIsFullScreen(false);
    pipeline->safeAreaManager_->SetIsNeedAvoidWindow(true);
    pipeline->safeAreaManager_->UpdateSystemSafeArea(
        NG::SafeAreaInsets({0.0f, 0.0f}, {0.0f, 30.0f}, {0.0f, 0.0f}, {170.0f, 200.0f}));

    PaddingProperty safeAreaPadding = {
        .left = CalcLength(10.0f),
        .right = CalcLength(15.0f),
        .top = CalcLength(20.0f),
        .bottom = CalcLength(25.0f)
    };
    layoutWrapper0->GetLayoutProperty()->UpdateSafeAreaPadding(safeAreaPadding);

    ExpandEdges expectedRes = {
        .top = std::make_optional<float>(50.0f),
        .bottom = std::make_optional<float>(55.0f),
        .left = std::make_optional<float>(10.0f),
        .right = std::make_optional<float>(15.0f)
    };

    EXPECT_EQ(layoutWrapper1->GetAccumulatedSafeAreaExpand(false, {
        .type = NG::LAYOUT_SAFE_AREA_TYPE_SYSTEM,
        .edges = NG::LAYOUT_SAFE_AREA_EDGE_ALL
    }), expectedRes);

    expectedRes.top = std::make_optional<float>(20.0f);
    expectedRes.bottom = std::make_optional<float>(25.0f);
    EXPECT_EQ(layoutWrapper1->GetAccumulatedSafeAreaExpand(false, {
        .type = NG::LAYOUT_SAFE_AREA_TYPE_KEYBOARD,
        .edges = NG::LAYOUT_SAFE_AREA_EDGE_ALL
    }), expectedRes);
}

/**
 * @tc.name: StrategyControlOnGetAccumulatedSafeAreaExpand001
 * @tc.desc: Test GetAccumulatedSafeAreaExpand with Strategy options
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestTwoNg, StrategyControlOnGetAccumulatedSafeAreaExpand001, TestSize.Level0)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    auto [node0, layoutWrapper0] =
        CreateNodeAndWrapper(OHOS::Ace::V2::FLEX_ETS_TAG, NODE_ID_0, RectF(0.0f, 0.0f, 200.0f, 200.0f));
    auto [child, layoutWrapper1] =
        CreateNodeAndWrapper(OHOS::Ace::V2::FLEX_ETS_TAG, NODE_ID_1, RectF(10.0f, 20.0f, 165.0f, 145.0f));
    child->MountToParent(node0);
    PresetSceneForStrategyTest(layoutWrapper0, layoutWrapper1);

    ExpandEdges expectedRes;
    /**
     * @tc.steps: step1. base scene
     */
    expectedRes = {
        .left = std::make_optional<float>(10.0f),
        .right = std::nullopt,
        .top = std::make_optional<float>(20.0f),
        .bottom = std::nullopt
    };
    EXPECT_EQ(layoutWrapper1->GetAccumulatedSafeAreaExpand(false, {
        .type = NG::LAYOUT_SAFE_AREA_TYPE_SYSTEM,
        .edges = NG::LAYOUT_SAFE_AREA_EDGE_ALL
    }), expectedRes);

    /**
     * @tc.steps: step2. from self
     */
    expectedRes = {
        .left = std::make_optional<float>(20.0f),
        .right = std::make_optional<float>(15.0f),
        .top = std::make_optional<float>(30.0f),
        .bottom = std::make_optional<float>(15.0f)
    };
    EXPECT_EQ(layoutWrapper1->GetAccumulatedSafeAreaExpand(true, {
        .type = NG::LAYOUT_SAFE_AREA_TYPE_SYSTEM,
        .edges = NG::LAYOUT_SAFE_AREA_EDGE_ALL
    }), expectedRes);
}

/**
 * @tc.name: StrategyControlOnGetAccumulatedSafeAreaExpand002
 * @tc.desc: Test GetAccumulatedSafeAreaExpand with Strategy options
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestTwoNg, StrategyControlOnGetAccumulatedSafeAreaExpand002, TestSize.Level0)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    auto [node0, layoutWrapper0] =
        CreateNodeAndWrapper(OHOS::Ace::V2::FLEX_ETS_TAG, NODE_ID_0, RectF(0.0f, 0.0f, 200.0f, 200.0f));
    auto [child, layoutWrapper1] =
        CreateNodeAndWrapper(OHOS::Ace::V2::FLEX_ETS_TAG, NODE_ID_1, RectF(10.0f, 20.0f, 165.0f, 145.0f));
    child->MountToParent(node0);
    PresetSceneForStrategyTest(layoutWrapper0, layoutWrapper1);

    ExpandEdges expectedRes = {
        .left = std::make_optional<float>(10.0f),
        .right = std::make_optional<float>(15.0f),
        .top = std::make_optional<float>(20.0f),
        .bottom = std::make_optional<float>(25.0f)
    };
    /**
     * @tc.steps: step3. from margin
     */
    EXPECT_EQ(layoutWrapper1->GetAccumulatedSafeAreaExpand(false, {
        .type = NG::LAYOUT_SAFE_AREA_TYPE_SYSTEM,
        .edges = NG::LAYOUT_SAFE_AREA_EDGE_ALL
    }, IgnoreStrategy::FROM_MARGIN), expectedRes);

    /**
     * @tc.steps: step4. from margin, with invalid fromSelf
     */
    EXPECT_EQ(layoutWrapper1->GetAccumulatedSafeAreaExpand(true, {
        .type = NG::LAYOUT_SAFE_AREA_TYPE_SYSTEM,
        .edges = NG::LAYOUT_SAFE_AREA_EDGE_ALL
    }, IgnoreStrategy::FROM_MARGIN), expectedRes);
}

/**
 * @tc.name: StrategyControlOnGetAccumulatedSafeAreaExpand003
 * @tc.desc: Test GetAccumulatedSafeAreaExpand with Strategy options
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestTwoNg, StrategyControlOnGetAccumulatedSafeAreaExpand003, TestSize.Level0)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    auto [node0, layoutWrapper0] =
        CreateNodeAndWrapper(OHOS::Ace::V2::FLEX_ETS_TAG, NODE_ID_0, RectF(0.0f, 0.0f, 200.0f, 200.0f));
    auto [child, layoutWrapper1] =
        CreateNodeAndWrapper(OHOS::Ace::V2::FLEX_ETS_TAG, NODE_ID_1, RectF(10.0f, 20.0f, 165.0f, 145.0f));
    child->MountToParent(node0);
    PresetSceneForStrategyTest(layoutWrapper0, layoutWrapper1);
    PaddingProperty margin1 = {
        .left = CalcLength(10.0f),
        .right = CalcLength(10.0f),
        .top = CalcLength(10.0f),
        .bottom = CalcLength(10.0f)
    };
    layoutWrapper1->GetLayoutProperty()->UpdateMargin(margin1);
    MarginPropertyF margin1_ = {
        .left = 10.0f,
        .right = 10.0f,
        .top = 10.0f,
        .bottom = 10.0f
    };
    layoutWrapper1->GetGeometryNode()->UpdateMargin(margin1_);
    layoutWrapper1->GetLayoutProperty()->marginResult_ = margin1_;

    ExpandEdges expectedRes = {
        .left = std::nullopt,
        .right = std::nullopt,
        .top = std::nullopt,
        .bottom = std::nullopt
    };
    /**
     * @tc.steps: step5. overlay whole margin
     */
    EXPECT_EQ(layoutWrapper1->GetAccumulatedSafeAreaExpand(false, {
        .type = NG::LAYOUT_SAFE_AREA_TYPE_SYSTEM,
        .edges = NG::LAYOUT_SAFE_AREA_EDGE_ALL
    }), expectedRes);

    /**
     * @tc.steps: step6. overlay whole margin, with fromMargin
     */
    expectedRes.left = 0.0f;
    expectedRes.right = 15.0f;
    expectedRes.bottom = 25.0f;
    expectedRes.top = 10.0f;
    auto res = layoutWrapper1->GetAccumulatedSafeAreaExpand(false, {
        .type = NG::LAYOUT_SAFE_AREA_TYPE_SYSTEM,
        .edges = NG::LAYOUT_SAFE_AREA_EDGE_ALL
    }, IgnoreStrategy::FROM_MARGIN);
    EXPECT_EQ(res, expectedRes) << res.ToString().c_str();
}
/**
 * @tc.name: OverBorderPaddingOnGetAccumulatedSafeAreaExpand
 * @tc.desc: Test GetAccumulatedSafeAreaExpand over borderPadding
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestTwoNg, OverBorderPaddingOnGetAccumulatedSafeAreaExpand, TestSize.Level0)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    auto [parent, parentWrapper] =
        CreateNodeAndWrapper(OHOS::Ace::V2::FLEX_ETS_TAG, NODE_ID_0, RectF(0.0f, 0.0f, 200.0f, 200.0f));
    auto [node0, layoutWrapper0] =
        CreateNodeAndWrapper(OHOS::Ace::V2::FLEX_ETS_TAG, NODE_ID_1, RectF(25.0f, 25.0f, 150.0f, 150.0f));
    node0->MountToParent(parent);
    auto [child, layoutWrapper1] =
        CreateNodeAndWrapper(OHOS::Ace::V2::FLEX_ETS_TAG, NODE_ID_2, RectF(25.0f, 25.0f, 100.0f, 100.0f));
    child->MountToParent(node0);

    PaddingProperty safeAreaPadding = {
        .left = CalcLength(30.0f),
        .right = CalcLength(30.0f),
        .top = CalcLength(30.0f),
        .bottom = CalcLength(30.0f)
    };
    parentWrapper->GetLayoutProperty()->UpdateSafeAreaPadding(safeAreaPadding);
    layoutWrapper0->GetLayoutProperty()->UpdateSafeAreaPadding(safeAreaPadding);

    PaddingProperty padding0 = {
        .left = CalcLength(1.0f),
        .right = CalcLength(1.0f),
        .top = CalcLength(1.0f),
        .bottom = CalcLength(1.0f)
    };
    layoutWrapper0->GetLayoutProperty()->UpdatePadding(padding0);

    ExpandEdges expectedRes;
    /**
     * @tc.steps: step1. overlay with whole borderPadding
     */
    expectedRes = {
        .left = std::make_optional<float>(24.0f),
        .right = std::make_optional<float>(24.0f),
        .top = std::make_optional<float>(24.0f),
        .bottom = std::make_optional<float>(24.0f)
    };
    EXPECT_EQ(layoutWrapper1->GetAccumulatedSafeAreaExpand(false, {
        .type = NG::LAYOUT_SAFE_AREA_TYPE_SYSTEM,
        .edges = NG::LAYOUT_SAFE_AREA_EDGE_ALL
    }), expectedRes);

    /**
     * @tc.steps: step2. overlay without whole borderPadding
     */
    padding0.left = CalcLength(0.0f);
    layoutWrapper0->GetLayoutProperty()->UpdatePadding(padding0);
    expectedRes = {
        .left = std::make_optional<float>(50.0f),
        .right = std::make_optional<float>(50.0f),
        .top = std::make_optional<float>(50.0f),
        .bottom = std::make_optional<float>(50.0f)
    };
    EXPECT_EQ(layoutWrapper1->GetAccumulatedSafeAreaExpand(false, {
        .type = NG::LAYOUT_SAFE_AREA_TYPE_SYSTEM,
        .edges = NG::LAYOUT_SAFE_AREA_EDGE_ALL
    }), expectedRes);
}
}