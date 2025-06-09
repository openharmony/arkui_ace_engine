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

std::pair<RefPtr<FrameNode>, RefPtr<LayoutWrapperNode>> CreateNodeAndWrapper(
    const std::string& tag,
    int32_t nodeId,
    RectF rf = RectF())
{
    auto node = FrameNode::CreateFrameNode(tag, nodeId, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->frame_.rect_ = rf;
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(node, geometryNode, node->GetLayoutProperty());

    return std::make_pair(node, layoutWrapper);
}

std::pair<RefPtr<FrameNode>, RefPtr<LayoutWrapperNode>> CreateNodeAndWrapperTestPattern(
    const std::string& tag,
    int32_t nodeId,
    RectF rf = RectF())
{
    auto node = FrameNode::CreateFrameNode(tag, nodeId, AceType::MakeRefPtr<TestPattern>());
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->frame_.rect_ = rf;
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(node, geometryNode, node->GetLayoutProperty());

    return std::make_pair(node, layoutWrapper);
}

RefPtr<LayoutWrapperNode> CreateLayoutWrapper(const std::string& tag, int32_t nodeId)
{
    auto rowFrameNode = FrameNode::CreateFrameNode(tag, nodeId, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    return layoutWrapper;
}

std::pair<RefPtr<FrameNode>, RefPtr<LayoutWrapperNode>> CreateScrollableWrapper(int32_t nodeId, RectF rf = RectF())
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::SCROLL_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<ScrollPattern>(); });
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->frame_.rect_ = rf;
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());

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
HWTEST_F(LayoutWrapperTestTwoNg, LayoutWrapperTest001, TestSize.Level1)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    auto [parent, layoutWrapper] = CreateNodeAndWrapper(OHOS::Ace::V2::FLEX_ETS_TAG, NODE_ID_0);
    auto [child0, nodeLayoutWrapper1] = CreateNodeAndWrapper(OHOS::Ace::V2::JS_VIEW_ETS_TAG, NODE_ID_1);
    child0->MountToParent(parent);
    auto [child1, childWrapper] = CreateNodeAndWrapper(FIRST_CHILD_FRAME_NODE, NODE_ID_2);
    child1->MountToParent(child0);
    auto [child2, childWrapper2] = CreateNodeAndWrapper(FIRST_CHILD_FRAME_NODE, NODE_ID_3);
    child2->MountToParent(child1);

    EXPECT_EQ(child1->GetParentGlobalOffsetWithSafeArea(false, false), OffsetF(0, 0));
    EXPECT_EQ(child1->GetParentGlobalOffsetWithSafeArea(false, true), OffsetF(0, 0));
    EXPECT_EQ(child2->GetParentGlobalOffsetWithSafeArea(false, false), OffsetF(0, 0));
    EXPECT_EQ(child2->GetParentGlobalOffsetWithSafeArea(false, true), OffsetF(0, 0));

    pipeline->stageManager_ = AceType::MakeRefPtr<StageManager>(parent);
    auto pageRenderContext = child1->GetRenderContext();

    child1->renderContext_ = nullptr;
    EXPECT_EQ(child1->GetParentGlobalOffsetWithSafeArea(false, false), OffsetF(0, 0));
    EXPECT_EQ(child1->GetParentGlobalOffsetWithSafeArea(false, true), OffsetF(0, 0));
    EXPECT_EQ(child2->GetParentGlobalOffsetWithSafeArea(false, false), OffsetF(0, 0));
    EXPECT_EQ(child2->GetParentGlobalOffsetWithSafeArea(false, true), OffsetF(0, 0));

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
    EXPECT_EQ(child2->GetParentGlobalOffsetWithSafeArea(false, true), OffsetF(0, 0));

    child1->layoutProperty_->layoutConstraint_ = MakeLayoutConstraintF();
    EXPECT_EQ(child2->GetParentGlobalOffsetWithSafeArea(false, false), OffsetF(0, 0));
    EXPECT_EQ(child2->GetParentGlobalOffsetWithSafeArea(false, true), OffsetF(10.0f, 10.0f));
}

/**
 * @tc.name: LayoutWrapperTest002
 * @tc.desc: Test GetFrameRectWithoutSafeArea.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestTwoNg, LayoutWrapperTest002, TestSize.Level1)
{
    auto node = FrameNode::CreateFrameNode(ROW_FRAME_NODE, NODE_ID_0, AceType::MakeRefPtr<Pattern>());
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(node, nullptr, node->GetLayoutProperty());
    EXPECT_EQ(layoutWrapper->GetFrameRectWithoutSafeArea(), RectF());
    RefPtr<GeometryNode> gn = AceType::MakeRefPtr<GeometryNode>();
    gn->frame_.rect_ = RectF{10.0f, 20.0f, 30.0f, 40.0f};
    layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(node, gn, node->GetLayoutProperty());
    EXPECT_EQ(layoutWrapper->GetFrameRectWithoutSafeArea(), gn->frame_.rect_);
}

/**
 * @tc.name: LayoutWrapperTest003
 * @tc.desc: Test OffsetNodeToSafeArea.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestTwoNg, LayoutWrapperTest003, TestSize.Level1)
{
    auto layoutWrapper = CreateLayoutWrapper(ROW_FRAME_NODE, NODE_ID_0);
    layoutWrapper->layoutProperty_->UpdateSafeAreaInsets(
        SafeAreaInsets({}, { 0, 1 }, {}, { RK356_HEIGHT - 1, RK356_HEIGHT }));
    layoutWrapper->geometryNode_->SetFrameSize({ RK356_WIDTH, RK356_HEIGHT - 2 });

    layoutWrapper->geometryNode_->SetFrameOffset({ 0, 1 });
    layoutWrapper->OffsetNodeToSafeArea();
    EXPECT_EQ(layoutWrapper->geometryNode_->GetFrameOffset(), OffsetF(0, 1));

    layoutWrapper->geometryNode_->SetFrameOffset({ 0, 5 });
    layoutWrapper->OffsetNodeToSafeArea();
    EXPECT_EQ(layoutWrapper->geometryNode_->GetFrameOffset(), OffsetF(0, 1));

    layoutWrapper->geometryNode_->SetFrameOffset({ 0, 0 });
    layoutWrapper->OffsetNodeToSafeArea();
    EXPECT_EQ(layoutWrapper->geometryNode_->GetFrameOffset(), OffsetF(0, 1));

    layoutWrapper->layoutProperty_->UpdateSafeAreaInsets(
        SafeAreaInsets({ 0, 5 }, { 0, 1 }, {}, { RK356_HEIGHT - 1, RK356_HEIGHT }));
    layoutWrapper->geometryNode_->SetFrameOffset({ 0, 0 });
    layoutWrapper->OffsetNodeToSafeArea();
    EXPECT_EQ(layoutWrapper->geometryNode_->GetFrameOffset(), OffsetF(0, 1));

    // set right and bottom again
    layoutWrapper->geometryNode_->SetFrameOffset({ 1, 1 });
    layoutWrapper->layoutProperty_->UpdateSafeAreaInsets(
        SafeAreaInsets({ 0, 0 }, { 0, 0 }, { RK356_HEIGHT, RK356_HEIGHT + 1 }, { RK356_HEIGHT, RK356_HEIGHT + 1 }));
    layoutWrapper->OffsetNodeToSafeArea();
    EXPECT_EQ(layoutWrapper->geometryNode_->GetFrameOffset().x_, 1);
    EXPECT_EQ(layoutWrapper->geometryNode_->GetFrameOffset().y_, 1);

    layoutWrapper->geometryNode_->SetFrameOffset({ 1, 1 });
    layoutWrapper->layoutProperty_->UpdateSafeAreaInsets(
        SafeAreaInsets({ 0, 0 }, { 0, 0 }, { RK356_HEIGHT + 1, RK356_HEIGHT }, { RK356_HEIGHT + 1, RK356_HEIGHT }));
    layoutWrapper->OffsetNodeToSafeArea();
    EXPECT_EQ(layoutWrapper->geometryNode_->GetFrameOffset().x_, 0);
    EXPECT_EQ(layoutWrapper->geometryNode_->GetFrameOffset().y_, 1);
}

/**
 * @tc.name: LayoutWrapperTest004
 * @tc.desc: Test CreateRootConstraint.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestTwoNg, LayoutWrapperTest004, TestSize.Level1)
{
    auto context = PipelineContext::GetCurrentContext();
    context->rootHeight_ = RK356_HEIGHT;
    context->rootWidth_ = RK356_WIDTH;

    auto [node, layoutWrapper] = CreateNodeAndWrapper(ROW_FRAME_NODE, NODE_ID_0);
    layoutWrapper->geometryNode_->SetFrameSize({ RK356_WIDTH, RK356_HEIGHT });
    layoutWrapper->CreateRootConstraint();
    EXPECT_EQ(layoutWrapper->layoutProperty_->layoutConstraint_->percentReference.Height(), RK356_HEIGHT);
    layoutWrapper->layoutProperty_->UpdateAspectRatio(0.0001);
    layoutWrapper->CreateRootConstraint();
    EXPECT_EQ(layoutWrapper->layoutProperty_->layoutConstraint_->percentReference.Height(), 0);
    layoutWrapper->layoutProperty_->UpdateAspectRatio(2.0);
    layoutWrapper->CreateRootConstraint();
    EXPECT_EQ(layoutWrapper->layoutProperty_->layoutConstraint_->percentReference.Height(), RK356_HEIGHT / 2);
}

/**
 * @tc.name: LayoutWrapperTest005
 * @tc.desc: Test ApplyConstraintWithoutMeasure.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestTwoNg, LayoutWrapperTest005, TestSize.Level1)
{
    auto context = PipelineContext::GetCurrentContext();
    context->rootHeight_ = RK356_HEIGHT;
    context->rootWidth_ = RK356_WIDTH;

    auto [node, layoutWrapper] = CreateNodeAndWrapper(ROW_FRAME_NODE, NODE_ID_0);
    std::optional<LayoutConstraintF> constraint;
    layoutWrapper->ApplyConstraintWithoutMeasure(constraint);
    constraint = MakeLayoutConstraintF();
    layoutWrapper->ApplyConstraintWithoutMeasure(constraint);
}

/**
 * @tc.name: LayoutWrapperTest006
 * @tc.desc: Test GetPageCurrentOffset.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestTwoNg, LayoutWrapperTest006, TestSize.Level1)
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
HWTEST_F(LayoutWrapperTestTwoNg, LayoutWrapperTest007, TestSize.Level1)
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
    layoutWrapper->layoutProperty_->UpdateSafeAreaExpandOpts({ SAFE_AREA_TYPE_ALL, SAFE_AREA_EDGE_ALL });
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
HWTEST_F(LayoutWrapperTestTwoNg, LayoutWrapperTest008, TestSize.Level1)
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
    layoutWrapper->layoutProperty_->UpdateSafeAreaExpandOpts({ SAFE_AREA_TYPE_ALL, SAFE_AREA_EDGE_ALL });
    childWrapper0->layoutProperty_->UpdateSafeAreaExpandOpts({ SAFE_AREA_TYPE_ALL, SAFE_AREA_EDGE_ALL });
    childWrapper1->layoutProperty_->UpdateSafeAreaExpandOpts({ SAFE_AREA_TYPE_ALL, SAFE_AREA_EDGE_ALL });
    childWrapper2->layoutProperty_->UpdateSafeAreaExpandOpts({ SAFE_AREA_TYPE_ALL, SAFE_AREA_EDGE_ALL });
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
HWTEST_F(LayoutWrapperTestTwoNg, LayoutWrapperTest009, TestSize.Level1)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    auto [parent, layoutWrapper] = CreateNodeAndWrapper(OHOS::Ace::V2::FLEX_ETS_TAG, NODE_ID_0);

    layoutWrapper->AdjustNotExpandNode();

    pipeline->safeAreaManager_->UpdateCutoutSafeArea(
        NG::SafeAreaInsets({10.0f, 40.0f}, {20.0f, 50.0f}, {680.0f, 710.0f}, {1230.0f, 1260.0f}));
    pipeline->safeAreaManager_->UpdateSystemSafeArea(
        NG::SafeAreaInsets({0.0f, 30.0f}, {0.0f, 30.0f}, {690.0f, 720.0f}, {1250.0f, 1280.0f}));
    pipeline->safeAreaManager_->UpdateNavSafeArea(
        NG::SafeAreaInsets({20.0f, 50.0f}, {40.0f, 70.0f}, {670.0f, 700.0f}, {1210.0f, 1240.0f}));
    pipeline->safeAreaManager_->SetIgnoreSafeArea(true);
    layoutWrapper->AdjustNotExpandNode();
    pipeline->safeAreaManager_->SetIgnoreSafeArea(false);
    layoutWrapper->AdjustNotExpandNode();
    pipeline->safeAreaManager_->UpdateCutoutSafeArea(
        NG::SafeAreaInsets({40.0f, 10.0f}, {50.0f, 20.0f}, {710.0f, 680.0f}, {1260.0f, 1230.0f}));
    pipeline->safeAreaManager_->UpdateSystemSafeArea(
        NG::SafeAreaInsets({30.0f, 0.0f}, {30.0f, 0.0f}, {720.0f, 690.0f}, {1280.0f, 1250.0f}));
    pipeline->safeAreaManager_->UpdateNavSafeArea(
        NG::SafeAreaInsets({50.0f, 20.0f}, {70.0f, 40.0f}, {700.0f, 670.0f}, {1240.0f, 1210.0f}));
    pipeline->safeAreaManager_->SetIgnoreSafeArea(true);
    layoutWrapper->AdjustNotExpandNode();
    pipeline->safeAreaManager_->SetIgnoreSafeArea(false);
    layoutWrapper->AdjustNotExpandNode();
}

/**
 * @tc.name: LayoutWrapperTest010
 * @tc.desc: Test ExpandSafeArea.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestTwoNg, LayoutWrapperTest010, TestSize.Level1)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    auto [parent, layoutWrapper] = CreateNodeAndWrapper(OHOS::Ace::V2::FLEX_ETS_TAG, NODE_ID_0);
    auto [child0, childWrapper0] = CreateNodeAndWrapper(OHOS::Ace::V2::JS_VIEW_ETS_TAG, NODE_ID_1);
    childWrapper0->geometryNode_->frame_.rect_ = RectF(0.0f, 0.0f, 100.0f, 100.0f);
    child0->MountToParent(parent);
    auto render0 = child0->GetRenderContext();

    auto [child1, childWrapper1] = CreateScrollableWrapper(NODE_ID_2, RectF(30.0f, 40.0f, 40.0f, 50.0f));
    child1->MountToParent(child0);
    auto render1 = child1->GetRenderContext();

    auto [child2, childWrapper2] = CreateScrollableWrapper(NODE_ID_3, RectF(40.0f, 40.0f, 20.0f, 10.0f));
    child2->MountToParent(child1);

    childWrapper0->layoutProperty_->safeAreaExpandOpts_ = std::make_unique<SafeAreaExpandOpts>();
    childWrapper1->layoutProperty_->safeAreaExpandOpts_ = std::make_unique<SafeAreaExpandOpts>();
    childWrapper0->layoutProperty_->safeAreaExpandOpts_->switchToNone = true;
    childWrapper1->layoutProperty_->safeAreaExpandOpts_->switchToNone = true;
    childWrapper0->ExpandSafeArea();
    childWrapper1->ExpandSafeArea();
    childWrapper0->layoutProperty_->safeAreaExpandOpts_->edges |= SAFE_AREA_EDGE_BOTTOM;
    pipeline->safeAreaManager_->SetIgnoreSafeArea(true);
    childWrapper0->ExpandSafeArea();
    childWrapper1->ExpandSafeArea();
    pipeline->safeAreaManager_->SetIgnoreSafeArea(false);
    childWrapper0->ExpandSafeArea();
    childWrapper1->ExpandSafeArea();

    childWrapper0->layoutProperty_->safeAreaExpandOpts_->type |= SAFE_AREA_TYPE_KEYBOARD;
    pipeline->safeAreaManager_->SetIgnoreSafeArea(true);
    childWrapper0->ExpandSafeArea();
    childWrapper1->ExpandSafeArea();
    pipeline->safeAreaManager_->SetIgnoreSafeArea(false);
    childWrapper0->ExpandSafeArea();
    childWrapper1->ExpandSafeArea();

    childWrapper0->layoutProperty_->safeAreaExpandOpts_ = std::make_unique<SafeAreaExpandOpts>();
    childWrapper1->layoutProperty_->safeAreaExpandOpts_->type |= SAFE_AREA_TYPE_KEYBOARD;
    pipeline->safeAreaManager_->SetIgnoreSafeArea(true);
    childWrapper0->ExpandSafeArea();
    childWrapper1->ExpandSafeArea();
    pipeline->safeAreaManager_->SetIgnoreSafeArea(false);
    childWrapper0->ExpandSafeArea();
    childWrapper1->ExpandSafeArea();
}

/**
 * @tc.name: LayoutWrapperTest011
 * @tc.desc: Test AdjustFixedSizeNode.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestTwoNg, LayoutWrapperTest011, TestSize.Level1)
{
    RectF frame;
    auto node = FrameNode::CreateFrameNode(ROW_FRAME_NODE, NODE_ID_0, AceType::MakeRefPtr<Pattern>());
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(node, nullptr, nullptr);
    layoutWrapper->AdjustFixedSizeNode(frame);
    EXPECT_EQ(frame, RectF());

    layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(node, nullptr, node->GetLayoutProperty());
    layoutWrapper->AdjustFixedSizeNode(frame);
    EXPECT_EQ(frame, RectF());

    RefPtr<GeometryNode> gn = AceType::MakeRefPtr<GeometryNode>();
    gn->frame_.rect_ = RectF{10.0f, 20.0f, 1200.0f, 1200.0f};
    layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(node, gn, node->GetLayoutProperty());
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
 * @tc.name: LayoutWrapperTest012
 * @tc.desc: Test AccumulateExpandCacheHit.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestTwoNg, LayoutWrapperTest012, TestSize.Level1)
{
    ExpandEdges totalExpand;
    PaddingPropertyF innerSpace;
    auto node = FrameNode::CreateFrameNode(ROW_FRAME_NODE, NODE_ID_0, AceType::MakeRefPtr<Pattern>());

    RefPtr<LayoutWrapperNode> layoutWrapper =
            AceType::MakeRefPtr<LayoutWrapperNode>(node, nullptr, node->GetLayoutProperty());
    EXPECT_FALSE(layoutWrapper->AccumulateExpandCacheHit(totalExpand, innerSpace));
    EXPECT_EQ(totalExpand, ExpandEdges());

    RefPtr<GeometryNode> gn = AceType::MakeRefPtr<GeometryNode>();
    gn->frame_.rect_ = RectF{10.0f, 20.0f, 30.0f, 40.0f};
    layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(node, gn, node->GetLayoutProperty());
    EXPECT_FALSE(layoutWrapper->AccumulateExpandCacheHit(totalExpand, innerSpace));
    EXPECT_EQ(totalExpand, ExpandEdges());

    ExpandEdges safeAreaPadding;
    safeAreaPadding.left = std::make_optional<float>(10.0f);
    safeAreaPadding.right = std::make_optional<float>(20.0f);
    safeAreaPadding.top = std::make_optional<float>(30.0f);
    safeAreaPadding.bottom = std::make_optional<float>(40.0f);
    EXPECT_FALSE(layoutWrapper->AccumulateExpandCacheHit(totalExpand, innerSpace));
    EXPECT_EQ(totalExpand, ExpandEdges());
    layoutWrapper->geometryNode_->SetAccumulatedSafeAreaEdges(safeAreaPadding);
    EXPECT_TRUE(layoutWrapper->AccumulateExpandCacheHit(totalExpand, innerSpace));
    EXPECT_EQ(totalExpand, ExpandEdges());
    totalExpand.left = std::make_optional<float>(100.0f);
    totalExpand.right = std::make_optional<float>(200.0f);
    totalExpand.top = std::make_optional<float>(300.0f);
    totalExpand.bottom = std::make_optional<float>(400.0f);

    EXPECT_TRUE(layoutWrapper->AccumulateExpandCacheHit(totalExpand, innerSpace));
    ExpandEdges safeAreaPadding1;
    safeAreaPadding1.left = std::make_optional<float>(110.0f);
    safeAreaPadding1.right = std::make_optional<float>(220.0f);
    safeAreaPadding1.top = std::make_optional<float>(330.0f);
    safeAreaPadding1.bottom = std::make_optional<float>(440.0f);
    EXPECT_EQ(totalExpand, safeAreaPadding1);
}

/**
 * @tc.name: LayoutWrapperTest014
 * @tc.desc: Test GetAccumulatedSafeAreaExpandHelper.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestTwoNg, LayoutWrapperTest014, TestSize.Level1)
{
    RectF adjustingRect;
    ExpandEdges totalExpand;
    auto pipeline = PipelineContext::GetCurrentContext();
    auto [parent, layoutWrapper] =
            CreateNodeAndWrapper(OHOS::Ace::V2::FLEX_ETS_TAG, NODE_ID_0, RectF(0.0f, 0.0f, 100.0f, 100.0f));
    auto [child0, nodeLayoutWrapper1] =
            CreateNodeAndWrapper(OHOS::Ace::V2::JS_VIEW_ETS_TAG, NODE_ID_1, RectF(10.0f, 20.0f, 50.0f, 40.0f));
    child0->MountToParent(parent);
    auto [child1, childWrapper] =
            CreateNodeAndWrapper(V2::STAGE_ETS_TAG, NODE_ID_2, RectF(20.0f, 30.0f, 30.0f, 25.0f));
    child1->MountToParent(child0);
    auto [child2, childWrapper2] =
            CreateNodeAndWrapper(FIRST_CHILD_FRAME_NODE, NODE_ID_3, RectF(25.0f, 32.0f, 10.0f, 10.0f));
    child2->MountToParent(child1);

    child1->GetAccumulatedSafeAreaExpandHelper(adjustingRect, totalExpand);
    EXPECT_EQ(adjustingRect, RectF(0.0f, 0.0f, 0.0f, 0.0f));
    child2->GetAccumulatedSafeAreaExpandHelper(adjustingRect, totalExpand);
    EXPECT_EQ(adjustingRect, RectF(0.0f, 0.0f, 0.0f, 0.0f));

    pipeline->stageManager_ = AceType::MakeRefPtr<StageManager>(parent);
    auto pageRenderContext = child1->GetRenderContext();
    pageRenderContext->UpdatePaintRect(RectF{40.0f, 40.0f, 500.0f, 1100.0f});
    pageRenderContext->GetOrCreatePositionProperty();

    pipeline->safeAreaManager_->SetIsAtomicService(true);
    pipeline->safeAreaManager_->SetIsFullScreen(true);
    pipeline->safeAreaManager_->UpdateSystemSafeArea(
        NG::SafeAreaInsets({0.0f, 30.0f}, {0.0f, 30.0f}, {690.0f, 720.0f}, {1250.0f, 1280.0f}));

    child1->GetAccumulatedSafeAreaExpandHelper(adjustingRect, totalExpand);
    EXPECT_EQ(adjustingRect, RectF(0.0f, 0.0f, 0.0f, 0.0f));
    child2->GetAccumulatedSafeAreaExpandHelper(adjustingRect, totalExpand);
    EXPECT_EQ(adjustingRect, RectF(0.0f, 0.0f, 0.0f, 0.0f));
}

/**
 * @tc.name: LayoutWrapperTest015
 * @tc.desc: Test AvoidKeyboard.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestTwoNg, LayoutWrapperTest015, TestSize.Level1)
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
HWTEST_F(LayoutWrapperTestTwoNg, LayoutWrapperTest016, TestSize.Level1)
{
    auto node = FrameNode::CreateFrameNode(ROW_FRAME_NODE, NODE_ID_0, AceType::MakeRefPtr<Pattern>());
    RefPtr<LayoutWrapperNode> tmoWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(node, nullptr, node->GetLayoutProperty());
    EXPECT_EQ(tmoWrapper->GetFrameRectWithSafeArea(), RectF());
    auto pipeline = PipelineContext::GetCurrentContext();
    auto [parent, layoutWrapper] = CreateNodeAndWrapper(OHOS::Ace::V2::FLEX_ETS_TAG, NODE_ID_0);
    auto [child0, childWrapper0] = CreateNodeAndWrapper(OHOS::Ace::V2::JS_VIEW_ETS_TAG, NODE_ID_1);
    childWrapper0->geometryNode_ = AceType::MakeRefPtr<GeometryNode>();
    childWrapper0->geometryNode_->frame_.rect_ = RectF{10.0f, 20.0f, 30.0f, 40.0f};
    child0->MountToParent(parent);
    auto [child1, childWrapper1] = CreateNodeAndWrapper(FIRST_CHILD_FRAME_NODE, NODE_ID_2);
    childWrapper1->geometryNode_ = AceType::MakeRefPtr<GeometryNode>();
    childWrapper1->geometryNode_->frame_.rect_ = RectF{10.0f, 20.0f, 30.0f, 40.0f};
    child1->MountToParent(child0);
    auto [child2, childWrapper2] = CreateNodeAndWrapper(FIRST_CHILD_FRAME_NODE, NODE_ID_3);
    childWrapper2->geometryNode_ = AceType::MakeRefPtr<GeometryNode>();
    childWrapper2->geometryNode_->frame_.rect_ = RectF{10.0f, 20.0f, 30.0f, 40.0f};
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
 * @tc.name: LayoutWrapperTest017
 * @tc.desc: Test ResetSafeAreaPadding.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestTwoNg, LayoutWrapperTest017, TestSize.Level1)
{
    auto node = FrameNode::CreateFrameNode(ROW_FRAME_NODE, NODE_ID_0, AceType::MakeRefPtr<Pattern>());
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(node, nullptr, nullptr);
    layoutWrapper->ResetSafeAreaPadding();

    layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(node, nullptr, node->GetLayoutProperty());
    layoutWrapper->ResetSafeAreaPadding();

    RefPtr<GeometryNode> gn = AceType::MakeRefPtr<GeometryNode>();
    gn->frame_.rect_ = RectF{10.0f, 20.0f, 30.0f, 40.0f};
    layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(node, gn, node->GetLayoutProperty());
    layoutWrapper->ResetSafeAreaPadding();
}

/**
 * @tc.name: LayoutWrapperTest018
 * @tc.desc: Test ExpandHelper.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestTwoNg, LayoutWrapperTest018, TestSize.Level1)
{
    std::unique_ptr<SafeAreaExpandOpts> opts = nullptr;
    RectF tmpFrame = RectF{20.0f, 30.0f, 670.0f, 1220.0f};
    auto pipeline = PipelineContext::GetCurrentContext();
    auto node = FrameNode::CreateFrameNode(ROW_FRAME_NODE, NODE_ID_0, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> gn = AceType::MakeRefPtr<GeometryNode>();
    gn->frame_.rect_ = RectF{10.0f, 20.0f, 30.0f, 40.0f};
    RefPtr<LayoutWrapperNode> layoutWrapper =
            AceType::MakeRefPtr<LayoutWrapperNode>(node, gn, node->GetLayoutProperty());
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
HWTEST_F(LayoutWrapperTestTwoNg, LayoutWrapperTest019, TestSize.Level1)
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

    layoutWrapper->AdjustChild(parent, OffsetF(), false);
    layoutWrapper->AdjustChild(parent, OffsetF(), true);
}

/**
 * @tc.name: LayoutWrapperTest020
 * @tc.desc: Test AdjustChildren
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestTwoNg, LayoutWrapperTest020, TestSize.Level1)
{
    auto [parent0, layoutWrapper0] = CreateNodeAndWrapper(V2::JS_VIEW_ETS_TAG, NODE_ID_0);
    layoutWrapper0->hostNode_ = nullptr;
    layoutWrapper0->AdjustChildren(OffsetF(), false);
    auto [parent1, layoutWrapper1] = CreateNodeAndWrapper(V2::JS_VIEW_ETS_TAG, NODE_ID_0);
    layoutWrapper1->AdjustChildren(OffsetF(), false);
    auto [parent2, layoutWrapper2] = CreateNodeAndWrapper(V2::JS_VIEW_ETS_TAG, NODE_ID_0);
    layoutWrapper2->AdjustChildren(OffsetF(), false);
    auto [parent3, layoutWrapper3] = CreateNodeAndWrapperTestPattern(V2::JS_VIEW_ETS_TAG, NODE_ID_0);
    layoutWrapper3->AdjustChildren(OffsetF(), false);
}

/**
 * @tc.name: LayoutWrapperTest021
 * @tc.desc: Test AvoidKeyboard.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestTwoNg, LayoutWrapperTest021, TestSize.Level1)
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

}