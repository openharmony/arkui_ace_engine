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

#include "flex_new_test_common.h"
#include "test/mock/frameworks/core/common/mock_container.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;

namespace {
constexpr int VERSION_TWENTY_SIX = 26;

void SetApiVersion26()
{
    PipelineContext::GetCurrentContext()->SetApiTargetVersion(VERSION_TWENTY_SIX);
    MockContainer::Current()->SetApiTargetVersion(VERSION_TWENTY_SIX);
}

struct ApiVersionGuard {
    int32_t oldVersion_ = PipelineContext::GetCurrentContext()->GetApiTargetVersion();

    ~ApiVersionGuard()
    {
        PipelineContext::GetCurrentContext()->SetApiTargetVersion(oldVersion_);
        MockContainer::Current()->SetApiTargetVersion(oldVersion_);
    }
};

void SetWrapContentPolicy()
{
    ViewAbstractModelNG parentViewModel;
    parentViewModel.UpdateLayoutPolicyProperty(LayoutCalPolicy::WRAP_CONTENT, true);
    parentViewModel.UpdateLayoutPolicyProperty(LayoutCalPolicy::WRAP_CONTENT, false);
}

void SetChildMatchParent(bool isWidth)
{
    ViewAbstractModelNG viewModel;
    viewModel.UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, isWidth);
}
} // namespace

/**
 * @tc.name: FlexMatchParent_Row_ChildrenWidthMatchParent
 * @tc.desc: Test Row with wrap_content size, child2 and child3 both have width=match_parent (main-axis match).
 *           Main-axis match_parent children should not contribute to parent's main axis wrapping.
 * @tc.type: FUNC
 */
HWTEST_F(FlexNewTestNG, FlexMatchParent_Row_ChildrenWidthMatchParent, TestSize.Level1)
{
    ApiVersionGuard apiGuard;
    SetApiVersion26();
    /**
     * corresponding ets code:
     *   Flex({ direction: FlexDirection.Row }) {
     *     Text("A").width(100).height(50)
     *     Text("B").width(LayoutPolicy.matchParent).height(60)
     *     Text("C").width(LayoutPolicy.matchParent).height(70)
     *   }.width(LayoutPolicy.wrapContent).height(LayoutPolicy.wrapContent)
     */
    auto frameNode = CreateFlexRow([this](FlexModelNG model) {
        model.SetDirection(FlexDirection::ROW);
        SetWrapContentPolicy();
        auto text1 = CreateFlexRow([this](FlexModelNG m) {
            ViewAbstract::SetWidth(CalcLength(100.0f));
            ViewAbstract::SetHeight(CalcLength(50.0f));
        });
        auto text2 = CreateFlexRow([this](FlexModelNG m) {
            SetChildMatchParent(true);
            ViewAbstract::SetHeight(CalcLength(60.0f));
        });
        auto text3 = CreateFlexRow([this](FlexModelNG m) {
            SetChildMatchParent(true);
            ViewAbstract::SetHeight(CalcLength(70.0f));
        });
    });
    ASSERT_NE(frameNode, nullptr);
    ASSERT_EQ(frameNode->GetChildren().size(), 3);
    CreateLayoutTask(frameNode);

    // Parent size: width = child1 only (child2/child3 excluded from main axis wrapping)
    auto parentSize = frameNode->GetGeometryNode()->GetFrameSize();
    EXPECT_EQ(parentSize, SizeF(100.0f, 70.0f)) << parentSize.ToString();
    // child1: offset=(0,0), size=(100,50)
    AssertChildLayout(frameNode, FIRST_CHILD, { 100.0f, 50.0f }, { 0.0f, 0.0f });
    // child2: offset=(100,0), size=(100,60) - width=match_parent = parent content width
    AssertChildLayout(frameNode, SECOND_CHILD, { 100.0f, 60.0f }, { 100.0f, 0.0f });
    // child3: offset=(200,0), size=(100,70)
    AssertChildLayout(frameNode, 2, { 100.0f, 70.0f }, { 200.0f, 0.0f });
}

/**
 * @tc.name: FlexMatchParent_Row_ChildrenHeightMatchParent
 * @tc.desc: Test Row with wrap_content size, child2 and child3 both have height=match_parent (cross-axis match).
 *           Cross-axis match_parent children should contribute to parent's main axis size via correction.
 * @tc.type: FUNC
 */
HWTEST_F(FlexNewTestNG, FlexMatchParent_Row_ChildrenHeightMatchParent, TestSize.Level1)
{
    ApiVersionGuard apiGuard;
    SetApiVersion26();
    /**
     * corresponding ets code:
     *   Flex({ direction: FlexDirection.Row }) {
     *     Text("A").width(100).height(50)
     *     Text("B").width(80).height(LayoutPolicy.matchParent)
     *     Text("C").width(80).height(LayoutPolicy.matchParent)
     *   }.width(LayoutPolicy.wrapContent).height(LayoutPolicy.wrapContent)
     */
    auto frameNode = CreateFlexRow([this](FlexModelNG model) {
        model.SetDirection(FlexDirection::ROW);
        SetWrapContentPolicy();
        auto text1 = CreateText(u"A", [this](TextModelNG m) {
            ViewAbstract::SetWidth(CalcLength(100.0f));
            ViewAbstract::SetHeight(CalcLength(50.0f));
        });
        auto text2 = CreateText(u"B", [this](TextModelNG m) {
            ViewAbstract::SetWidth(CalcLength(80.0f));
            SetChildMatchParent(false);
        });
        auto text3 = CreateText(u"C", [this](TextModelNG m) {
            ViewAbstract::SetWidth(CalcLength(80.0f));
            SetChildMatchParent(false);
        });
    });
    ASSERT_NE(frameNode, nullptr);
    ASSERT_EQ(frameNode->GetChildren().size(), 3);
    CreateLayoutTask(frameNode);

    // Parent size: width = 100 + 80 + 80 = 260, height = max(50) = 50
    auto parentSize = frameNode->GetGeometryNode()->GetFrameSize();
    EXPECT_EQ(parentSize, SizeF(260.0f, 50.0f)) << parentSize.ToString();
    // child1: offset=(0,0), size=(100,50)
    AssertChildLayout(frameNode, FIRST_CHILD, { 100.0f, 50.0f }, { 0.0f, 0.0f });
    // child2: offset=(100,0), size=(80,50) - height=match_parent = parent content height
    AssertChildLayout(frameNode, SECOND_CHILD, { 80.0f, 50.0f }, { 100.0f, 0.0f });
    // child3: offset=(180,0), size=(80,50)
    AssertChildLayout(frameNode, 2, { 80.0f, 50.0f }, { 180.0f, 0.0f });
}

/**
 * @tc.name: FlexMatchParent_Row_MixedMatchParent
 * @tc.desc: Test Row with wrap_content size, child2 has width=match_parent (main-axis),
 *           child3 has height=match_parent (cross-axis). The main-axis match child sets
 *           shouldCorrectMainAixsSize=false, preventing cross-match child from correcting parent size.
 * @tc.type: FUNC
 */
HWTEST_F(FlexNewTestNG, FlexMatchParent_Row_MixedMatchParent, TestSize.Level1)
{
    ApiVersionGuard apiGuard;
    SetApiVersion26();
    /**
     * corresponding ets code:
     *   Flex({ direction: FlexDirection.Row }) {
     *     Text("A").width(100).height(50)
     *     Text("B").width(LayoutPolicy.matchParent).height(60)
     *     Text("C").width(80).height(LayoutPolicy.matchParent)
     *   }.width(LayoutPolicy.wrapContent).height(LayoutPolicy.wrapContent)
     */
    auto frameNode = CreateFlexRow([this](FlexModelNG model) {
        model.SetDirection(FlexDirection::ROW);
        SetWrapContentPolicy();
        auto text1 = CreateText(u"A", [this](TextModelNG m) {
            ViewAbstract::SetWidth(CalcLength(100.0f));
            ViewAbstract::SetHeight(CalcLength(50.0f));
        });
        auto text2 = CreateText(u"B", [this](TextModelNG m) {
            SetChildMatchParent(true);
            ViewAbstract::SetHeight(CalcLength(60.0f));
        });
        auto text3 = CreateText(u"C", [this](TextModelNG m) {
            ViewAbstract::SetWidth(CalcLength(80.0f));
            SetChildMatchParent(false);
        });
    });
    ASSERT_NE(frameNode, nullptr);
    ASSERT_EQ(frameNode->GetChildren().size(), 3);
    CreateLayoutTask(frameNode);

    // Parent size: mainAxisSize not corrected (shouldCorrectMainAixsSize=false from child2)
    auto parentSize = frameNode->GetGeometryNode()->GetFrameSize();
    EXPECT_EQ(parentSize, SizeF(180.0f, 60.0f)) << parentSize.ToString();
    // child1: offset=(0,0), size=(100,50)
    AssertChildLayout(frameNode, FIRST_CHILD, { 100.0f, 50.0f }, { 0.0f, 0.0f });
    // child2: offset=(100,0), size=(180,60) - width=match_parent = parent content width
    AssertChildLayout(frameNode, SECOND_CHILD, { 180.0f, 60.0f }, { 100.0f, 0.0f });
    // child3: offset=(280,0), size=(80,60) - height=match_parent = parent content height
    AssertChildLayout(frameNode, 2, { 80.0f, 60.0f }, { 280.0f, 0.0f });
}

/**
 * @tc.name: FlexMatchParent_Column_ChildrenHeightMatchParent
 * @tc.desc: Test Column with wrap_content size, child2 and child3 both have height=match_parent (main-axis match
 *           in Column). Main-axis match_parent children should not contribute to parent's main axis wrapping.
 * @tc.type: FUNC
 */
HWTEST_F(FlexNewTestNG, FlexMatchParent_Column_ChildrenHeightMatchParent, TestSize.Level1)
{
    ApiVersionGuard apiGuard;
    SetApiVersion26();
    /**
     * corresponding ets code:
     *   Flex({ direction: FlexDirection.Column }) {
     *     Text("A").width(50).height(100)
     *     Text("B").width(60).height(LayoutPolicy.matchParent)
     *     Text("C").width(50).height(LayoutPolicy.matchParent)
     *   }.width(LayoutPolicy.wrapContent).height(LayoutPolicy.wrapContent)
     */
    auto frameNode = CreateFlexRow([this](FlexModelNG model) {
        model.SetDirection(FlexDirection::COLUMN);
        SetWrapContentPolicy();
        auto text1 = CreateText(u"A", [this](TextModelNG m) {
            ViewAbstract::SetWidth(CalcLength(50.0f));
            ViewAbstract::SetHeight(CalcLength(100.0f));
        });
        auto text2 = CreateText(u"B", [this](TextModelNG m) {
            ViewAbstract::SetWidth(CalcLength(60.0f));
            SetChildMatchParent(false);
        });
        auto text3 = CreateText(u"C", [this](TextModelNG m) {
            ViewAbstract::SetWidth(CalcLength(50.0f));
            SetChildMatchParent(false);
        });
    });
    ASSERT_NE(frameNode, nullptr);
    ASSERT_EQ(frameNode->GetChildren().size(), 3);
    CreateLayoutTask(frameNode);

    // Parent size: height = child1 only, width = max(50, 60, 50) = 60
    auto parentSize = frameNode->GetGeometryNode()->GetFrameSize();
    EXPECT_EQ(parentSize, SizeF(60.0f, 100.0f)) << parentSize.ToString();
    // child1: offset=(0,0), size=(50,100)
    AssertChildLayout(frameNode, FIRST_CHILD, { 50.0f, 100.0f }, { 0.0f, 0.0f });
    // child2: offset=(0,100), size=(60,100) - height=match_parent = parent content height
    AssertChildLayout(frameNode, SECOND_CHILD, { 60.0f, 100.0f }, { 0.0f, 100.0f });
    // child3: offset=(0,200), size=(50,100)
    AssertChildLayout(frameNode, 2, { 50.0f, 100.0f }, { 0.0f, 200.0f });
}

/**
 * @tc.name: FlexMatchParent_Column_ChildrenWidthMatchParent
 * @tc.desc: Test Column with wrap_content size, child2 and child3 both have width=match_parent (cross-axis match
 *           in Column). Cross-axis match_parent children should contribute to parent's main axis size via correction.
 * @tc.type: FUNC
 */
HWTEST_F(FlexNewTestNG, FlexMatchParent_Column_ChildrenWidthMatchParent, TestSize.Level1)
{
    ApiVersionGuard apiGuard;
    SetApiVersion26();
    /**
     * corresponding ets code:
     *   Flex({ direction: FlexDirection.Column }) {
     *     Text("A").width(50).height(100)
     *     Text("B").width(LayoutPolicy.matchParent).height(80)
     *     Text("C").width(LayoutPolicy.matchParent).height(80)
     *   }.width(LayoutPolicy.wrapContent).height(LayoutPolicy.wrapContent)
     */
    auto frameNode = CreateFlexRow([this](FlexModelNG model) {
        model.SetDirection(FlexDirection::COLUMN);
        SetWrapContentPolicy();
        auto text1 = CreateText(u"A", [this](TextModelNG m) {
            ViewAbstract::SetWidth(CalcLength(50.0f));
            ViewAbstract::SetHeight(CalcLength(100.0f));
        });
        auto text2 = CreateText(u"B", [this](TextModelNG m) {
            SetChildMatchParent(true);
            ViewAbstract::SetHeight(CalcLength(80.0f));
        });
        auto text3 = CreateText(u"C", [this](TextModelNG m) {
            SetChildMatchParent(true);
            ViewAbstract::SetHeight(CalcLength(80.0f));
        });
    });
    ASSERT_NE(frameNode, nullptr);
    ASSERT_EQ(frameNode->GetChildren().size(), 3);
    CreateLayoutTask(frameNode);

    // Parent size: height = 100 + 80 + 80 = 260, width = max(50) = 50
    auto parentSize = frameNode->GetGeometryNode()->GetFrameSize();
    EXPECT_EQ(parentSize, SizeF(50.0f, 260.0f)) << parentSize.ToString();
    // child1: offset=(0,0), size=(50,100)
    AssertChildLayout(frameNode, FIRST_CHILD, { 50.0f, 100.0f }, { 0.0f, 0.0f });
    // child2: offset=(0,100), size=(50,80) - width=match_parent = parent content width
    AssertChildLayout(frameNode, SECOND_CHILD, { 50.0f, 80.0f }, { 0.0f, 100.0f });
    // child3: offset=(0,180), size=(50,80)
    AssertChildLayout(frameNode, 2, { 50.0f, 80.0f }, { 0.0f, 180.0f });
}

/**
 * @tc.name: FlexMatchParent_Row_ChildBothAxesMatchParent
 * @tc.desc: Test Row with wrap_content size, child2 has both width+height=match_parent.
 *           The child is treated as cross-axis match (height) in HandleExpandAndNonCrossMatchChildren,
 *           and since it's also main-axis match, shouldCorrectMainAixsSize becomes false.
 * @tc.type: FUNC
 */
HWTEST_F(FlexNewTestNG, FlexMatchParent_Row_ChildBothAxesMatchParent, TestSize.Level1)
{
    ApiVersionGuard apiGuard;
    SetApiVersion26();
    /**
     * corresponding ets code:
     *   Flex({ direction: FlexDirection.Row }) {
     *     Text("A").width(100).height(50)
     *     Text("B").width(LayoutPolicy.matchParent).height(LayoutPolicy.matchParent)
     *     Text("C").width(100).height(50)
     *   }.width(LayoutPolicy.wrapContent).height(LayoutPolicy.wrapContent)
     */
    auto frameNode = CreateFlexRow([this](FlexModelNG model) {
        model.SetDirection(FlexDirection::ROW);
        SetWrapContentPolicy();
        auto text1 = CreateText(u"A", [this](TextModelNG m) {
            ViewAbstract::SetWidth(CalcLength(100.0f));
            ViewAbstract::SetHeight(CalcLength(50.0f));
        });
        auto text2 = CreateText(u"B", [this](TextModelNG m) {
            SetChildMatchParent(true);
            SetChildMatchParent(false);
        });
        auto text3 = CreateText(u"C", [this](TextModelNG m) {
            ViewAbstract::SetWidth(CalcLength(100.0f));
            ViewAbstract::SetHeight(CalcLength(50.0f));
        });
    });
    ASSERT_NE(frameNode, nullptr);
    ASSERT_EQ(frameNode->GetChildren().size(), 3);
    CreateLayoutTask(frameNode);

    // Parent size: width = child1 + child3 = 200, height = max(50,50) = 50
    auto parentSize = frameNode->GetGeometryNode()->GetFrameSize();
    EXPECT_EQ(parentSize, SizeF(200.0f, 50.0f)) << parentSize.ToString();
    // child1: offset=(0,0), size=(100,50)
    AssertChildLayout(frameNode, FIRST_CHILD, { 100.0f, 50.0f }, { 0.0f, 0.0f });
    // child2: offset=(100,0), size=(200,50) - both axes match parent content size
    AssertChildLayout(frameNode, SECOND_CHILD, { 200.0f, 50.0f }, { 100.0f, 0.0f });
    // child3: offset=(300,0), size=(100,50)
    AssertChildLayout(frameNode, 2, { 100.0f, 50.0f }, { 300.0f, 0.0f });
}
} // namespace OHOS::Ace::NG
