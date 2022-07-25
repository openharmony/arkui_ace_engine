/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include <string>

#include "gtest/gtest.h"

#include "base/geometry/offset.h"
#include "base/geometry/size.h"
#include "base/log/log.h"
#include "base/memory/ace_type.h"
#include "core/components/common/layout/align_declaration.h"
#include "core/components/common/layout/constants.h"
#include "core/components/flex/flex_item_component.h"
#include "core/components/flex/render_flex_item.h"
#include "core/components/indexer/indexer_component.h"
#include "core/components/relative_container/relative_container_component.h"
#include "core/components/relative_container/render_relative_container.h"
#include "core/components/test/unittest/mock/mock_render_common.h"
#include "core/components/test/unittest/relative_container/relative_container_test_utils.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {
const double CONTAINER_WIDTH = 2000.0;
const double CONTAINER_HEIGHT = 1000.0;
const double ZERO = 0.0;

const double ITEM_WIDTH = 200.0;
const double ITEM_HEIGHT = 200.0;

const Size CONTAINER_SIZE(CONTAINER_WIDTH, CONTAINER_HEIGHT);
const Size ITEM_SIZE(ITEM_WIDTH, ITEM_HEIGHT);

const Offset OFFSET_TOP_LEFT = Offset(ZERO, ZERO);
const Offset OFFSET_TOP_MIDDLE = Offset(CONTAINER_WIDTH / 2, ZERO);
const Offset OFFSET_TOP_RIGHT = Offset(CONTAINER_WIDTH, ZERO);

const Offset OFFSET_CENTER_LEFT = Offset(ZERO, CONTAINER_HEIGHT / 2);
const Offset OFFSET_CENTER_MIDDLE = Offset(CONTAINER_WIDTH / 2, CONTAINER_HEIGHT / 2);
const Offset OFFSET_CENTER_RIGHT = Offset(CONTAINER_WIDTH, CONTAINER_HEIGHT / 2);

const Offset OFFSET_BOTTOM_LEFT = Offset(ZERO, CONTAINER_HEIGHT);
const Offset OFFSET_BOTTOM_MIDDLE = Offset(CONTAINER_WIDTH / 2, CONTAINER_HEIGHT);
const Offset OFFSET_BOTTOM_RIGHT = Offset(CONTAINER_WIDTH, CONTAINER_HEIGHT);

const std::string COMPONENT_ID = "id1";
const std::string SECOND_COMPONENT_ID = "id2";
const std::string THIRD_COMPONENT_ID = "id3";
const std::string FOUTRH_COMPONENT_ID = "id4";
const std::string FIFTH_COMPONENT_ID = "id5";
const std::string SIXTH_COMPONENT_ID = "id6";
const std::string SEVENTH_COMPONENT_ID = "id7";
const std::string EIGHTH_COMPONENT_ID = "id8";
const std::string NINTH_COMPONENT_ID = "id9";
const std::string TENTH_COMPONENT_ID = "id10";

const std::string CONTAINER_ID = "__container__";
} // namespace

class RenderRelativeContainerTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void RenderRelativeContainerTest::SetUpTestCase() {}
void RenderRelativeContainerTest::TearDownTestCase() {}
void RenderRelativeContainerTest::SetUp() {}
void RenderRelativeContainerTest::TearDown() {}

/* *
 * @tc.name: ComponentWithoutId001
 * @tc.desc: Verify the location of a component without an id
 * @tc.type: FUNC
 * @
 */
HWTEST_F(RenderRelativeContainerTest, OneComponentWithoutId001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the render node tree, set align rules to the flex item,
     *                   set width and height to the render box
     */
    auto mockContext = MockRenderCommon::GetMockContext();

    /**
     * corresponding ets code:
     *   Box().width(ITEM_WIDTH).height(ITEM_HEIGHT)
     *       .alignRules({
     *         middle: { anchor: CONTAINER_ID, align: HorizontalAlign.Center },
     *         center: { anchor: CONTAINER_ID, align: VerticalAlign.Center },
     *       })
     */
    RefPtr<FlexItemComponent> flexItemComponent = AceType::MakeRefPtr<FlexItemComponent>();
    RefPtr<RenderFlexItem> renderFlexItem = AceType::MakeRefPtr<RenderFlexItem>();
    renderFlexItem->Attach(mockContext);
    std::map<AlignDirection, AlignRule> alignRules;
    RelativeContainerTestUtils::AddAlignRule(CONTAINER_ID, AlignDirection::MIDDLE, HorizontalAlign::CENTER, alignRules);
    RelativeContainerTestUtils::AddAlignRule(CONTAINER_ID, AlignDirection::CENTER, VerticalAlign::CENTER, alignRules);
    flexItemComponent->SetAlignRules(alignRules);
    renderFlexItem->Update(flexItemComponent);
    auto renderBox = RelativeContainerTestUtils::CreateRenderBox(ITEM_WIDTH, ITEM_HEIGHT, mockContext);
    renderFlexItem->AddChild(renderBox);

    RefPtr<RenderRoot> renderRoot = RelativeContainerTestUtils::CreateRenderRoot();
    auto renderRelativeContainer = RelativeContainerTestUtils::CreateRenderRelativeContainer(mockContext);
    renderRoot->AddChild(renderRelativeContainer);
    renderRelativeContainer->AddChild(renderFlexItem);
    ASSERT_TRUE(renderRelativeContainer->GetChildren().size() == 1);

    /**
     * @tc.steps: step2. call PerformLayout interface
     * @tc.expected: step2. the position of the flex item and the layout size of render box are set correctly
     */
    renderRoot->PerformLayout();
    renderRelativeContainer->PerformLayout();
    renderBox->PerformLayout();
    ASSERT_TRUE(renderRelativeContainer->GetLayoutSize() == CONTAINER_SIZE);
    const RefPtr<RenderNode>& child = renderRelativeContainer->GetChildren().front();
    const RefPtr<RenderNode>& boxNode = child->GetChildren().front();
    ASSERT_TRUE(child->GetPosition() == OFFSET_TOP_LEFT);
    ASSERT_TRUE(boxNode->GetLayoutSize() == ITEM_SIZE);
}

/* *
 * @tc.name: HorizontalAnchor001
 * @tc.desc: Verify the location of a component with a horizontal anchor rule
 * @tc.type: FUNC
 */
HWTEST_F(RenderRelativeContainerTest, HorizontalAnchor001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the render node tree, set id and a horizontal anchor rule to the flex item,
     *                   set width and height to the render box
     */
    auto mockContext = MockRenderCommon::GetMockContext();

    /**
     * corresponding ets code:
     *   Box().width(ITEM_WIDTH).height(ITEM_HEIGHT)
     *       .alignRules({
     *         left: { anchor: CONTAINER_ID, align: HorizontalAlign.Start },
     *       }).id(COMPONENT_ID)
     */
    RefPtr<FlexItemComponent> flexItemComponent = AceType::MakeRefPtr<FlexItemComponent>();
    RefPtr<RenderFlexItem> renderFlexItem = AceType::MakeRefPtr<RenderFlexItem>();
    renderFlexItem->Attach(mockContext);
    flexItemComponent->SetInspectorKey(COMPONENT_ID);
    std::map<AlignDirection, AlignRule> alignRules;
    RelativeContainerTestUtils::AddAlignRule(CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::START, alignRules);
    flexItemComponent->SetAlignRules(alignRules);
    renderFlexItem->Update(flexItemComponent);
    auto renderBox = RelativeContainerTestUtils::CreateRenderBox(ITEM_WIDTH, ITEM_HEIGHT, mockContext);
    renderFlexItem->AddChild(renderBox);

    RefPtr<RenderRoot> renderRoot = RelativeContainerTestUtils::CreateRenderRoot();
    auto renderRelativeContainer = RelativeContainerTestUtils::CreateRenderRelativeContainer(mockContext);
    renderRoot->AddChild(renderRelativeContainer);
    renderRelativeContainer->AddChild(renderFlexItem);
    ASSERT_TRUE(renderRelativeContainer->GetChildren().size() == 1);

    /**
     * @tc.steps: step2. call PerformLayout interface
     * @tc.expected: step2. the position of the flex item and the layout size of render box are set correctly
     */
    renderRoot->PerformLayout();
    renderRelativeContainer->PerformLayout();
    ASSERT_TRUE(renderRelativeContainer->GetLayoutSize() == CONTAINER_SIZE);
    const RefPtr<RenderNode>& child = renderRelativeContainer->GetChildren().front();
    const RefPtr<RenderNode>& boxNode = child->GetChildren().front();
    ASSERT_TRUE(child->GetPosition() == OFFSET_TOP_LEFT);
    ASSERT_TRUE(boxNode->GetLayoutSize() == ITEM_SIZE);
}

/* *
 * @tc.name: HorizontalAnchor002
 * @tc.desc: Verify the location of a component with a horizontal anchor rule
 * @tc.type: FUNC
 */
HWTEST_F(RenderRelativeContainerTest, HorizontalAnchor002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the render node tree, set id and a horizontal anchor rule to the flex item,
     *                   set width and height to the render box
     */
    auto mockContext = MockRenderCommon::GetMockContext();

    /**
     * corresponding ets code:
     *   Box().width(ITEM_WIDTH).height(ITEM_HEIGHT)
     *       .alignRules({
     *         right: { anchor: CONTAINER_ID, align: HorizontalAlign.Center },
     *       }).id(COMPONENT_ID)
     */
    RefPtr<FlexItemComponent> flexItemComponent = AceType::MakeRefPtr<FlexItemComponent>();
    RefPtr<RenderFlexItem> renderFlexItem = AceType::MakeRefPtr<RenderFlexItem>();
    renderFlexItem->Attach(mockContext);
    flexItemComponent->SetInspectorKey(COMPONENT_ID);
    std::map<AlignDirection, AlignRule> alignRules;
    RelativeContainerTestUtils::AddAlignRule(CONTAINER_ID, AlignDirection::RIGHT, HorizontalAlign::CENTER, alignRules);
    flexItemComponent->SetAlignRules(alignRules);
    renderFlexItem->Update(flexItemComponent);
    auto renderBox = RelativeContainerTestUtils::CreateRenderBox(ITEM_WIDTH, ITEM_HEIGHT, mockContext);
    renderFlexItem->AddChild(renderBox);

    RefPtr<RenderRoot> renderRoot = RelativeContainerTestUtils::CreateRenderRoot();
    auto renderRelativeContainer = RelativeContainerTestUtils::CreateRenderRelativeContainer(mockContext);
    renderRoot->AddChild(renderRelativeContainer);
    renderRelativeContainer->AddChild(renderFlexItem);
    ASSERT_TRUE(renderRelativeContainer->GetChildren().size() == 1);

    /**
     * @tc.steps: step2. call PerformLayout interface
     * @tc.expected: step2. the position of the flex item and the layout size of render box are set correctly
     */
    renderRoot->PerformLayout();
    renderRelativeContainer->PerformLayout();
    ASSERT_TRUE(renderRelativeContainer->GetLayoutSize() == CONTAINER_SIZE);
    const RefPtr<RenderNode>& child = renderRelativeContainer->GetChildren().front();
    const RefPtr<RenderNode>& boxNode = child->GetChildren().front();
    ASSERT_TRUE(child->GetPosition() == OFFSET_TOP_MIDDLE - Offset(ITEM_WIDTH, ZERO));
    ASSERT_TRUE(boxNode->GetLayoutSize() == ITEM_SIZE);
}

/* *
 * @tc.name: HorizontalAnchor003
 * @tc.desc: Verify the location of a component with a horizontal anchor rule
 * @tc.type: FUNC
 */
HWTEST_F(RenderRelativeContainerTest, HorizontalAnchor003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the render node tree, set id and a horizontal anchor rule to the flex item,
     *                   set width and height to the render box
     */
    auto mockContext = MockRenderCommon::GetMockContext();

    /**
     * corresponding ets code:
     *   Box().width(ITEM_WIDTH).height(ITEM_HEIGHT)
     *       .alignRules({
     *         middle: { anchor: CONTAINER_ID, align: HorizontalAlign.Center },
     *       }).id(COMPONENT_ID)
     */
    RefPtr<FlexItemComponent> flexItemComponent = AceType::MakeRefPtr<FlexItemComponent>();
    RefPtr<RenderFlexItem> renderFlexItem = AceType::MakeRefPtr<RenderFlexItem>();
    renderFlexItem->Attach(mockContext);
    flexItemComponent->SetInspectorKey(COMPONENT_ID);
    std::map<AlignDirection, AlignRule> alignRules;
    RelativeContainerTestUtils::AddAlignRule(CONTAINER_ID, AlignDirection::MIDDLE, HorizontalAlign::CENTER, alignRules);
    flexItemComponent->SetAlignRules(alignRules);
    renderFlexItem->Update(flexItemComponent);
    auto renderBox = RelativeContainerTestUtils::CreateRenderBox(ITEM_WIDTH, ITEM_HEIGHT, mockContext);
    renderFlexItem->AddChild(renderBox);

    RefPtr<RenderRoot> renderRoot = RelativeContainerTestUtils::CreateRenderRoot();
    auto renderRelativeContainer = RelativeContainerTestUtils::CreateRenderRelativeContainer(mockContext);
    renderRoot->AddChild(renderRelativeContainer);
    renderRelativeContainer->AddChild(renderFlexItem);
    ASSERT_TRUE(renderRelativeContainer->GetChildren().size() == 1);

    /**
     * @tc.steps: step2. call PerformLayout interface
     * @tc.expected: step2. the position of the flex item and the layout size of render box are set correctly
     */
    renderRoot->PerformLayout();
    renderRelativeContainer->PerformLayout();
    ASSERT_TRUE(renderRelativeContainer->GetLayoutSize() == CONTAINER_SIZE);
    const RefPtr<RenderNode>& child = renderRelativeContainer->GetChildren().front();
    const RefPtr<RenderNode>& boxNode = child->GetChildren().front();
    ASSERT_TRUE(child->GetPosition() == OFFSET_TOP_MIDDLE - Offset(ITEM_WIDTH / 2, ZERO));
    ASSERT_TRUE(boxNode->GetLayoutSize() == ITEM_SIZE);
}

/* *
 * @tc.name: HorizontalAnchor004
 * @tc.desc: Verify the location of a component with a horizontal anchor rule
 * @tc.type: FUNC
 */
HWTEST_F(RenderRelativeContainerTest, HorizontalAnchor004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the render node tree, set id and a horizontal anchor rule to the flex item,
     *                   set width and height to the render box
     */
    auto mockContext = MockRenderCommon::GetMockContext();

    /**
     * corresponding ets code:
     *   Box().width(ITEM_WIDTH).height(ITEM_HEIGHT)
     *       .alignRules({
     *         left: { anchor: CONTAINER_ID, align: HorizontalAlign.Center },
     *       }).id(COMPONENT_ID)
     */
    RefPtr<FlexItemComponent> flexItemComponent = AceType::MakeRefPtr<FlexItemComponent>();
    RefPtr<RenderFlexItem> renderFlexItem = AceType::MakeRefPtr<RenderFlexItem>();
    renderFlexItem->Attach(mockContext);
    flexItemComponent->SetInspectorKey(COMPONENT_ID);
    std::map<AlignDirection, AlignRule> alignRules;
    RelativeContainerTestUtils::AddAlignRule(CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::CENTER, alignRules);
    flexItemComponent->SetAlignRules(alignRules);
    renderFlexItem->Update(flexItemComponent);
    auto renderBox = RelativeContainerTestUtils::CreateRenderBox(ITEM_WIDTH, ITEM_HEIGHT, mockContext);
    renderFlexItem->AddChild(renderBox);

    RefPtr<RenderRoot> renderRoot = RelativeContainerTestUtils::CreateRenderRoot();
    auto renderRelativeContainer = RelativeContainerTestUtils::CreateRenderRelativeContainer(mockContext);
    renderRoot->AddChild(renderRelativeContainer);
    renderRelativeContainer->AddChild(renderFlexItem);
    ASSERT_TRUE(renderRelativeContainer->GetChildren().size() == 1);

    /**
     * @tc.steps: step2. call PerformLayout interface
     * @tc.expected: step2. the position of the flex item and the layout size of render box are set correctly
     */
    renderRoot->PerformLayout();
    renderRelativeContainer->PerformLayout();
    ASSERT_TRUE(renderRelativeContainer->GetLayoutSize() == CONTAINER_SIZE);
    const RefPtr<RenderNode>& child = renderRelativeContainer->GetChildren().front();
    const RefPtr<RenderNode>& boxNode = child->GetChildren().front();
    ASSERT_TRUE(child->GetPosition() == OFFSET_TOP_MIDDLE);
    ASSERT_TRUE(boxNode->GetLayoutSize() == ITEM_SIZE);
}

/* *
 * @tc.name: HorizontalAnchor005
 * @tc.desc: Verify the location of a component with a horizontal anchor rule
 * @tc.type: FUNC
 */
HWTEST_F(RenderRelativeContainerTest, HorizontalAnchor005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the render node tree, set id and a horizontal anchor rule to the flex item,
     *                   set width and height to the render box
     */
    auto mockContext = MockRenderCommon::GetMockContext();

    /**
     * corresponding ets code:
     *   Box().width(ITEM_WIDTH).height(ITEM_HEIGHT)
     *       .alignRules({
     *         right: { anchor: CONTAINER_ID, align: HorizontalAlign.End },
     *       }).id(COMPONENT_ID)
     */
    RefPtr<FlexItemComponent> flexItemComponent = AceType::MakeRefPtr<FlexItemComponent>();
    RefPtr<RenderFlexItem> renderFlexItem = AceType::MakeRefPtr<RenderFlexItem>();
    renderFlexItem->Attach(mockContext);
    flexItemComponent->SetInspectorKey(COMPONENT_ID);
    std::map<AlignDirection, AlignRule> alignRules;
    RelativeContainerTestUtils::AddAlignRule(CONTAINER_ID, AlignDirection::RIGHT, HorizontalAlign::END, alignRules);
    flexItemComponent->SetAlignRules(alignRules);
    renderFlexItem->Update(flexItemComponent);
    auto renderBox = RelativeContainerTestUtils::CreateRenderBox(ITEM_WIDTH, ITEM_HEIGHT, mockContext);
    renderFlexItem->AddChild(renderBox);

    RefPtr<RenderRoot> renderRoot = RelativeContainerTestUtils::CreateRenderRoot();
    auto renderRelativeContainer = RelativeContainerTestUtils::CreateRenderRelativeContainer(mockContext);
    renderRoot->AddChild(renderRelativeContainer);
    renderRelativeContainer->AddChild(renderFlexItem);
    ASSERT_TRUE(renderRelativeContainer->GetChildren().size() == 1);

    /**
     * @tc.steps: step2. call PerformLayout interface
     * @tc.expected: step2. the position of the flex item and the layout size of render box are set correctly
     */
    renderRoot->PerformLayout();
    renderRelativeContainer->PerformLayout();
    ASSERT_TRUE(renderRelativeContainer->GetLayoutSize() == CONTAINER_SIZE);
    const RefPtr<RenderNode>& child = renderRelativeContainer->GetChildren().front();
    const RefPtr<RenderNode>& boxNode = child->GetChildren().front();
    ASSERT_TRUE(child->GetPosition() == OFFSET_TOP_RIGHT - Offset(ITEM_WIDTH, ZERO));
    ASSERT_TRUE(boxNode->GetLayoutSize() == ITEM_SIZE);
}

/* *
 * @tc.name: VerticalAnchor001
 * @tc.desc: Verify the location of a component with a vertical anchor rule
 * @tc.type: FUNC
 */
HWTEST_F(RenderRelativeContainerTest, VerticalAnchor001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the render node tree, set id and a vertical anchor rule to the flex item,
     *                   set width and height to the render box
     */
    auto mockContext = MockRenderCommon::GetMockContext();

    /**
     * corresponding ets code:
     *   Box().width(ITEM_WIDTH).height(ITEM_HEIGHT)
     *       .alignRules({
     *         top: { anchor: CONTAINER_ID, align: VerticalAlign.Top },
     *       }).id(COMPONENT_ID)
     */
    RefPtr<FlexItemComponent> flexItemComponent = AceType::MakeRefPtr<FlexItemComponent>();
    RefPtr<RenderFlexItem> renderFlexItem = AceType::MakeRefPtr<RenderFlexItem>();
    renderFlexItem->Attach(mockContext);
    flexItemComponent->SetInspectorKey(COMPONENT_ID);
    std::map<AlignDirection, AlignRule> alignRules;
    RelativeContainerTestUtils::AddAlignRule(CONTAINER_ID, AlignDirection::TOP, VerticalAlign::TOP, alignRules);
    flexItemComponent->SetAlignRules(alignRules);
    renderFlexItem->Update(flexItemComponent);
    auto renderBox = RelativeContainerTestUtils::CreateRenderBox(ITEM_WIDTH, ITEM_HEIGHT, mockContext);
    renderFlexItem->AddChild(renderBox);

    RefPtr<RenderRoot> renderRoot = RelativeContainerTestUtils::CreateRenderRoot();
    auto renderRelativeContainer = RelativeContainerTestUtils::CreateRenderRelativeContainer(mockContext);
    renderRoot->AddChild(renderRelativeContainer);
    renderRelativeContainer->AddChild(renderFlexItem);
    ASSERT_TRUE(renderRelativeContainer->GetChildren().size() == 1);

    /**
     * @tc.steps: step2. call PerformLayout interface
     * @tc.expected: step2. the position of the flex item and the layout size of render box are set correctly
     */
    renderRoot->PerformLayout();
    renderRelativeContainer->PerformLayout();
    ASSERT_TRUE(renderRelativeContainer->GetLayoutSize() == CONTAINER_SIZE);
    const RefPtr<RenderNode>& child = renderRelativeContainer->GetChildren().front();
    const RefPtr<RenderNode>& boxNode = child->GetChildren().front();
    ASSERT_TRUE(child->GetPosition() == OFFSET_TOP_LEFT);
    ASSERT_TRUE(boxNode->GetLayoutSize() == ITEM_SIZE);
}

/* *
 * @tc.name: VerticalAnchor002
 * @tc.desc: Verify the location of a component with a vertical anchor rule
 * @tc.type: FUNC
 */
HWTEST_F(RenderRelativeContainerTest, VerticalAnchor002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the render node tree, set id and a vertical anchor rule to the flex item,
     *                   set width and height to the render box
     */
    auto mockContext = MockRenderCommon::GetMockContext();

    /**
     * corresponding ets code:
     *   Box().width(ITEM_WIDTH).height(ITEM_HEIGHT)
     *       .alignRules({
     *         bottom: { anchor: CONTAINER_ID, align: VerticalAlign.Center },
     *       }).id(COMPONENT_ID)
     */
    RefPtr<FlexItemComponent> flexItemComponent = AceType::MakeRefPtr<FlexItemComponent>();
    RefPtr<RenderFlexItem> renderFlexItem = AceType::MakeRefPtr<RenderFlexItem>();
    renderFlexItem->Attach(mockContext);
    flexItemComponent->SetInspectorKey(COMPONENT_ID);
    std::map<AlignDirection, AlignRule> alignRules;
    RelativeContainerTestUtils::AddAlignRule(CONTAINER_ID, AlignDirection::BOTTOM, VerticalAlign::CENTER, alignRules);
    flexItemComponent->SetAlignRules(alignRules);
    renderFlexItem->Update(flexItemComponent);
    auto renderBox = RelativeContainerTestUtils::CreateRenderBox(ITEM_WIDTH, ITEM_HEIGHT, mockContext);
    renderFlexItem->AddChild(renderBox);

    RefPtr<RenderRoot> renderRoot = RelativeContainerTestUtils::CreateRenderRoot();
    auto renderRelativeContainer = RelativeContainerTestUtils::CreateRenderRelativeContainer(mockContext);
    renderRoot->AddChild(renderRelativeContainer);
    renderRelativeContainer->AddChild(renderFlexItem);
    ASSERT_TRUE(renderRelativeContainer->GetChildren().size() == 1);

    /**
     * @tc.steps: step2. call PerformLayout interface
     * @tc.expected: step2. the position of the flex item and the layout size of render box are set correctly
     */
    renderRoot->PerformLayout();
    renderRelativeContainer->PerformLayout();
    ASSERT_TRUE(renderRelativeContainer->GetLayoutSize() == CONTAINER_SIZE);
    const RefPtr<RenderNode>& child = renderRelativeContainer->GetChildren().front();
    const RefPtr<RenderNode>& boxNode = child->GetChildren().front();
    ASSERT_TRUE(child->GetPosition() == OFFSET_CENTER_LEFT - Offset(ZERO, ITEM_HEIGHT));
    ASSERT_TRUE(boxNode->GetLayoutSize() == ITEM_SIZE);
}

/* *
 * @tc.name: VerticalAnchor003
 * @tc.desc: Verify the location of a component with a vertical anchor rule
 * @tc.type: FUNC
 */
HWTEST_F(RenderRelativeContainerTest, VerticalAnchor003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the render node tree, set id and a vertical anchor rule to the flex item,
     *                   set width and height to the render box
     */
    auto mockContext = MockRenderCommon::GetMockContext();

    /**
     * corresponding ets code:
     *   Box().width(ITEM_WIDTH).height(ITEM_HEIGHT)
     *       .alignRules({
     *         center: { anchor: CONTAINER_ID, align: VerticalAlign.Center },
     *       }).id(COMPONENT_ID)
     */
    RefPtr<FlexItemComponent> flexItemComponent = AceType::MakeRefPtr<FlexItemComponent>();
    RefPtr<RenderFlexItem> renderFlexItem = AceType::MakeRefPtr<RenderFlexItem>();
    renderFlexItem->Attach(mockContext);
    flexItemComponent->SetInspectorKey(COMPONENT_ID);
    std::map<AlignDirection, AlignRule> alignRules;
    RelativeContainerTestUtils::AddAlignRule(CONTAINER_ID, AlignDirection::CENTER, VerticalAlign::CENTER, alignRules);
    flexItemComponent->SetAlignRules(alignRules);
    renderFlexItem->Update(flexItemComponent);
    auto renderBox = RelativeContainerTestUtils::CreateRenderBox(ITEM_WIDTH, ITEM_HEIGHT, mockContext);
    renderFlexItem->AddChild(renderBox);

    RefPtr<RenderRoot> renderRoot = RelativeContainerTestUtils::CreateRenderRoot();
    auto renderRelativeContainer = RelativeContainerTestUtils::CreateRenderRelativeContainer(mockContext);
    renderRoot->AddChild(renderRelativeContainer);
    renderRelativeContainer->AddChild(renderFlexItem);
    ASSERT_TRUE(renderRelativeContainer->GetChildren().size() == 1);

    /**
     * @tc.steps: step2. call PerformLayout interface
     * @tc.expected: step2. the position of the flex item and the layout size of render box are set correctly
     */
    renderRoot->PerformLayout();
    renderRelativeContainer->PerformLayout();
    ASSERT_TRUE(renderRelativeContainer->GetLayoutSize() == CONTAINER_SIZE);
    const RefPtr<RenderNode>& child = renderRelativeContainer->GetChildren().front();
    const RefPtr<RenderNode>& boxNode = child->GetChildren().front();
    ASSERT_TRUE(child->GetPosition() == OFFSET_CENTER_LEFT - Offset(ZERO, ITEM_HEIGHT / 2));
    ASSERT_TRUE(boxNode->GetLayoutSize() == ITEM_SIZE);
}

/* *
 * @tc.name: VerticalAnchor004
 * @tc.desc: Verify the location of a component with a vertical anchor rule
 * @tc.type: FUNC
 */
HWTEST_F(RenderRelativeContainerTest, VerticalAnchor004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the render node tree, set id and a vertical anchor rule to the flex item,
     *                   set width and height to the render box
     */
    auto mockContext = MockRenderCommon::GetMockContext();

    /**
     * corresponding ets code:
     *   Box().width(ITEM_WIDTH).height(ITEM_HEIGHT)
     *       .alignRules({
     *         top: { anchor: CONTAINER_ID, align: VerticalAlign.Center },
     *       }).id(COMPONENT_ID)
     */
    RefPtr<FlexItemComponent> flexItemComponent = AceType::MakeRefPtr<FlexItemComponent>();
    RefPtr<RenderFlexItem> renderFlexItem = AceType::MakeRefPtr<RenderFlexItem>();
    renderFlexItem->Attach(mockContext);
    flexItemComponent->SetInspectorKey(COMPONENT_ID);
    std::map<AlignDirection, AlignRule> alignRules;
    RelativeContainerTestUtils::AddAlignRule(CONTAINER_ID, AlignDirection::TOP, VerticalAlign::CENTER, alignRules);
    flexItemComponent->SetAlignRules(alignRules);
    renderFlexItem->Update(flexItemComponent);
    auto renderBox = RelativeContainerTestUtils::CreateRenderBox(ITEM_WIDTH, ITEM_HEIGHT, mockContext);
    renderFlexItem->AddChild(renderBox);

    RefPtr<RenderRoot> renderRoot = RelativeContainerTestUtils::CreateRenderRoot();
    auto renderRelativeContainer = RelativeContainerTestUtils::CreateRenderRelativeContainer(mockContext);
    renderRoot->AddChild(renderRelativeContainer);
    renderRelativeContainer->AddChild(renderFlexItem);
    ASSERT_TRUE(renderRelativeContainer->GetChildren().size() == 1);

    /**
     * @tc.steps: step2. call PerformLayout interface
     * @tc.expected: step2. the position of the flex item and the layout size of render box are set correctly
     */
    renderRoot->PerformLayout();
    renderRelativeContainer->PerformLayout();
    ASSERT_TRUE(renderRelativeContainer->GetLayoutSize() == CONTAINER_SIZE);
    const RefPtr<RenderNode>& child = renderRelativeContainer->GetChildren().front();
    const RefPtr<RenderNode>& boxNode = child->GetChildren().front();
    ASSERT_TRUE(child->GetPosition() == OFFSET_CENTER_LEFT);
    ASSERT_TRUE(boxNode->GetLayoutSize() == ITEM_SIZE);
}

/* *
 * @tc.name: VerticalAnchor005
 * @tc.desc: Verify the location of a component with a vertical anchor rule
 * @tc.type: FUNC
 */
HWTEST_F(RenderRelativeContainerTest, VerticalAnchor005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the render node tree, set id and a vertical anchor rule to the flex item,
     *                   set width and height to the render box
     */
    auto mockContext = MockRenderCommon::GetMockContext();

    /**
     * corresponding ets code:
     *   Box().width(ITEM_WIDTH).height(ITEM_HEIGHT)
     *       .alignRules({
     *         bottom: { anchor: CONTAINER_ID, align: VerticalAlign.Bottom },
     *       }).id(COMPONENT_ID)
     */
    RefPtr<FlexItemComponent> flexItemComponent = AceType::MakeRefPtr<FlexItemComponent>();
    RefPtr<RenderFlexItem> renderFlexItem = AceType::MakeRefPtr<RenderFlexItem>();
    renderFlexItem->Attach(mockContext);
    flexItemComponent->SetInspectorKey(COMPONENT_ID);
    std::map<AlignDirection, AlignRule> alignRules;
    RelativeContainerTestUtils::AddAlignRule(CONTAINER_ID, AlignDirection::BOTTOM, VerticalAlign::BOTTOM, alignRules);
    flexItemComponent->SetAlignRules(alignRules);
    renderFlexItem->Update(flexItemComponent);
    auto renderBox = RelativeContainerTestUtils::CreateRenderBox(ITEM_WIDTH, ITEM_HEIGHT, mockContext);
    renderFlexItem->AddChild(renderBox);

    RefPtr<RenderRoot> renderRoot = RelativeContainerTestUtils::CreateRenderRoot();
    auto renderRelativeContainer = RelativeContainerTestUtils::CreateRenderRelativeContainer(mockContext);
    renderRoot->AddChild(renderRelativeContainer);
    renderRelativeContainer->AddChild(renderFlexItem);
    ASSERT_TRUE(renderRelativeContainer->GetChildren().size() == 1);

    /**
     * @tc.steps: step2. call PerformLayout interface
     * @tc.expected: step2. the position of the flex item and the layout size of render box are set correctly
     */
    renderRoot->PerformLayout();
    renderRelativeContainer->PerformLayout();
    ASSERT_TRUE(renderRelativeContainer->GetLayoutSize() == CONTAINER_SIZE);
    const RefPtr<RenderNode>& child = renderRelativeContainer->GetChildren().front();
    const RefPtr<RenderNode>& boxNode = child->GetChildren().front();
    ASSERT_TRUE(child->GetPosition() == OFFSET_BOTTOM_LEFT - Offset(ZERO, ITEM_HEIGHT));
    ASSERT_TRUE(boxNode->GetLayoutSize() == ITEM_SIZE);
}

/* *
 * @tc.name: OneComponentWithoutAnchorRule001
 * @tc.desc: Verify the location of a component without anchor rule
 * @tc.type: FUNC
 */
HWTEST_F(RenderRelativeContainerTest, OneComponentWithoutAnchorRule001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the render node tree, set id to the flex item,
     *                   set width and height to the render box
     */
    auto mockContext = MockRenderCommon::GetMockContext();

    /**
     * corresponding ets code:
     *   Box().width(ITEM_WIDTH).height(ITEM_HEIGHT).id(COMPONENT_ID)
     */
    RefPtr<FlexItemComponent> flexItemComponent = AceType::MakeRefPtr<FlexItemComponent>();
    RefPtr<RenderFlexItem> renderFlexItem = AceType::MakeRefPtr<RenderFlexItem>();
    renderFlexItem->Attach(mockContext);
    flexItemComponent->SetInspectorKey(COMPONENT_ID);
    renderFlexItem->Update(flexItemComponent);
    auto renderBox = RelativeContainerTestUtils::CreateRenderBox(ITEM_WIDTH, ITEM_HEIGHT, mockContext);
    renderFlexItem->AddChild(renderBox);

    RefPtr<RenderRoot> renderRoot = RelativeContainerTestUtils::CreateRenderRoot();
    auto renderRelativeContainer = RelativeContainerTestUtils::CreateRenderRelativeContainer(mockContext);
    renderRoot->AddChild(renderRelativeContainer);
    renderRelativeContainer->AddChild(renderFlexItem);
    ASSERT_TRUE(renderRelativeContainer->GetChildren().size() == 1);

    /**
     * @tc.steps: step2. call PerformLayout interface
     * @tc.expected: step2. the position of the flex item and the layout size of render box are set correctly
     */
    renderRoot->PerformLayout();
    renderRelativeContainer->PerformLayout();
    ASSERT_TRUE(renderRelativeContainer->GetLayoutSize() == CONTAINER_SIZE);
    const RefPtr<RenderNode>& child = renderRelativeContainer->GetChildren().front();
    const RefPtr<RenderNode>& boxNode = child->GetChildren().front();
    ASSERT_TRUE(child->GetPosition() == OFFSET_TOP_LEFT);
    ASSERT_TRUE(boxNode->GetLayoutSize() == ITEM_SIZE);
}

/* *
 * @tc.name: OneComponentWithTwoAnchorRules001
 * @tc.desc: Verify the location of a component with two anchor rules
 * @tc.type: FUNC
 */
HWTEST_F(RenderRelativeContainerTest, OneComponentWithTwoAnchorRules001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the render node tree, set id and anchor rules to the flex item,
     *                   set width and height to the render box
     */
    auto mockContext = MockRenderCommon::GetMockContext();

    /**
     * corresponding ets code:
     *   Box().width(ITEM_WIDTH).height(ITEM_HEIGHT)
     *       .alignRules({
     *         middle: { anchor: CONTAINER_ID, align: HorizontalAlign.Center },
     *         center: { anchor: CONTAINER_ID, align: VerticalAlign.Center },
     *       }).id(COMPONENT_ID)
     */
    RefPtr<FlexItemComponent> flexItemComponent = AceType::MakeRefPtr<FlexItemComponent>();
    RefPtr<RenderFlexItem> renderFlexItem = AceType::MakeRefPtr<RenderFlexItem>();
    renderFlexItem->Attach(mockContext);
    flexItemComponent->SetInspectorKey(COMPONENT_ID);
    std::map<AlignDirection, AlignRule> alignRules;
    RelativeContainerTestUtils::AddAlignRule(CONTAINER_ID, AlignDirection::MIDDLE, HorizontalAlign::CENTER, alignRules);
    RelativeContainerTestUtils::AddAlignRule(CONTAINER_ID, AlignDirection::CENTER, VerticalAlign::CENTER, alignRules);
    flexItemComponent->SetAlignRules(alignRules);
    renderFlexItem->Update(flexItemComponent);
    auto renderBox = RelativeContainerTestUtils::CreateRenderBox(ITEM_WIDTH, ITEM_HEIGHT, mockContext);
    renderFlexItem->AddChild(renderBox);

    RefPtr<RenderRoot> renderRoot = RelativeContainerTestUtils::CreateRenderRoot();
    auto renderRelativeContainer = RelativeContainerTestUtils::CreateRenderRelativeContainer(mockContext);
    renderRoot->AddChild(renderRelativeContainer);
    renderRelativeContainer->AddChild(renderFlexItem);
    ASSERT_TRUE(renderRelativeContainer->GetChildren().size() == 1);

    /**
     * @tc.steps: step2. call PerformLayout interface
     * @tc.expected: step2. the position of the flex item and the layout size of render box are set correctly
     */
    renderRoot->PerformLayout();
    renderRelativeContainer->PerformLayout();
    ASSERT_TRUE(renderRelativeContainer->GetLayoutSize() == CONTAINER_SIZE);
    const RefPtr<RenderNode>& child = renderRelativeContainer->GetChildren().front();
    const RefPtr<RenderNode>& boxNode = child->GetChildren().front();
    ASSERT_TRUE(child->GetPosition() == OFFSET_CENTER_MIDDLE - Offset(ITEM_WIDTH / 2, ITEM_HEIGHT / 2));
    ASSERT_TRUE(boxNode->GetLayoutSize() == ITEM_SIZE);
}

/* *
 * @tc.name: OneComponentWithTwoAnchorRules002
 * @tc.desc: Verify the location of a component with two anchor rules
 * @tc.type: FUNC
 */
HWTEST_F(RenderRelativeContainerTest, OneComponentWithTwoAnchorRules002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the render node tree, set id and anchor rules to the flex item,
     *                   set width and height to the render box
     */
    auto mockContext = MockRenderCommon::GetMockContext();

    /**
     * corresponding ets code:
     *   Box().width(ITEM_WIDTH).height(ITEM_HEIGHT)
     *       .alignRules({
     *         left: { anchor: CONTAINER_ID, align: HorizontalAlign.Center },
     *         right: { anchor: CONTAINER_ID, align: HorizontalAlign.End },
     *       }).id(COMPONENT_ID)
     */
    RefPtr<FlexItemComponent> flexItemComponent = AceType::MakeRefPtr<FlexItemComponent>();
    RefPtr<RenderFlexItem> renderFlexItem = AceType::MakeRefPtr<RenderFlexItem>();
    renderFlexItem->Attach(mockContext);
    flexItemComponent->SetInspectorKey(COMPONENT_ID);
    std::map<AlignDirection, AlignRule> alignRules;
    RelativeContainerTestUtils::AddAlignRule(CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::CENTER, alignRules);
    RelativeContainerTestUtils::AddAlignRule(CONTAINER_ID, AlignDirection::RIGHT, HorizontalAlign::END, alignRules);
    flexItemComponent->SetAlignRules(alignRules);
    renderFlexItem->Update(flexItemComponent);
    auto renderBox = RelativeContainerTestUtils::CreateRenderBox(ITEM_WIDTH, ITEM_HEIGHT, mockContext);
    renderFlexItem->AddChild(renderBox);

    RefPtr<RenderRoot> renderRoot = RelativeContainerTestUtils::CreateRenderRoot();
    auto renderRelativeContainer = RelativeContainerTestUtils::CreateRenderRelativeContainer(mockContext);
    renderRoot->AddChild(renderRelativeContainer);
    renderRelativeContainer->AddChild(renderFlexItem);
    ASSERT_TRUE(renderRelativeContainer->GetChildren().size() == 1);

    /**
     * @tc.steps: step2. call PerformLayout interface
     * @tc.expected: step2. the position of the flex item and the layout size of render box are set correctly
     */
    renderRoot->PerformLayout();
    renderRelativeContainer->PerformLayout();
    ASSERT_TRUE(renderRelativeContainer->GetLayoutSize() == CONTAINER_SIZE);
    const RefPtr<RenderNode>& child = renderRelativeContainer->GetChildren().front();
    const RefPtr<RenderNode>& boxNode = child->GetChildren().front();
    ASSERT_TRUE(child->GetPosition() == OFFSET_TOP_MIDDLE);
    ASSERT_TRUE(boxNode->GetLayoutSize() == Size(CONTAINER_WIDTH / 2, ITEM_HEIGHT));
}

/* *
 * @tc.name: OneComponentWithTwoAnchorRules003
 * @tc.desc: Verify the location of a component with two anchor rules
 * @tc.type: FUNC
 */
HWTEST_F(RenderRelativeContainerTest, OneComponentWithTwoAnchorRules003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the render node tree, set id and anchor rules to the flex item,
     *                   set width and height to the render box
     */
    auto mockContext = MockRenderCommon::GetMockContext();

    /**
     * corresponding ets code:
     *   Box().width(ITEM_WIDTH).height(ITEM_HEIGHT)
     *       .alignRules({
     *         top: { anchor: CONTAINER_ID, align: VerticalAlign.Center },
     *         bottom: { anchor: CONTAINER_ID, align: VerticalAlign.Bottom },
     *       }).id(COMPONENT_ID)
     */
    RefPtr<FlexItemComponent> flexItemComponent = AceType::MakeRefPtr<FlexItemComponent>();
    RefPtr<RenderFlexItem> renderFlexItem = AceType::MakeRefPtr<RenderFlexItem>();
    renderFlexItem->Attach(mockContext);
    flexItemComponent->SetInspectorKey(COMPONENT_ID);
    std::map<AlignDirection, AlignRule> alignRules;
    RelativeContainerTestUtils::AddAlignRule(CONTAINER_ID, AlignDirection::TOP, VerticalAlign::CENTER, alignRules);
    RelativeContainerTestUtils::AddAlignRule(CONTAINER_ID, AlignDirection::BOTTOM, VerticalAlign::BOTTOM, alignRules);
    flexItemComponent->SetAlignRules(alignRules);
    renderFlexItem->Update(flexItemComponent);
    auto renderBox = RelativeContainerTestUtils::CreateRenderBox(ITEM_WIDTH, ITEM_HEIGHT, mockContext);
    renderFlexItem->AddChild(renderBox);

    RefPtr<RenderRoot> renderRoot = RelativeContainerTestUtils::CreateRenderRoot();
    auto renderRelativeContainer = RelativeContainerTestUtils::CreateRenderRelativeContainer(mockContext);
    renderRoot->AddChild(renderRelativeContainer);
    renderRelativeContainer->AddChild(renderFlexItem);
    ASSERT_TRUE(renderRelativeContainer->GetChildren().size() == 1);

    /**
     * @tc.steps: step2. call PerformLayout interface
     * @tc.expected: step2. the position of the flex item and the layout size of render box are set correctly
     */
    renderRoot->PerformLayout();
    renderRelativeContainer->PerformLayout();
    ASSERT_TRUE(renderRelativeContainer->GetLayoutSize() == CONTAINER_SIZE);
    const RefPtr<RenderNode>& child = renderRelativeContainer->GetChildren().front();
    const RefPtr<RenderNode>& boxNode = child->GetChildren().front();
    ASSERT_TRUE(child->GetPosition() == OFFSET_CENTER_LEFT);
    ASSERT_TRUE(boxNode->GetLayoutSize() == Size(ITEM_WIDTH, CONTAINER_HEIGHT / 2));
}

/* *
 * @tc.name: OneComponentWithTwoAnchorRules004
 * @tc.desc: Verify the location of a component with two anchor rules
 * @tc.type: FUNC
 */
HWTEST_F(RenderRelativeContainerTest, OneComponentWithTwoAnchorRules004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the render node tree, set id and anchor rules to the flex item,
     *                   set width and height to the render box
     */
    auto mockContext = MockRenderCommon::GetMockContext();

    /**
     * corresponding ets code:
     *   Box().width(ITEM_WIDTH).height(ITEM_HEIGHT)
     *       .alignRules({
     *         right: { anchor: CONTAINER_ID, align: HorizontalAlign.Start },
     *         top: { anchor: CONTAINER_ID, align: VerticalAlign.Top },
     *       }).id(COMPONENT_ID)
     */
    RefPtr<FlexItemComponent> flexItemComponent = AceType::MakeRefPtr<FlexItemComponent>();
    RefPtr<RenderFlexItem> renderFlexItem = AceType::MakeRefPtr<RenderFlexItem>();
    renderFlexItem->Attach(mockContext);
    flexItemComponent->SetInspectorKey(COMPONENT_ID);
    std::map<AlignDirection, AlignRule> alignRules;
    RelativeContainerTestUtils::AddAlignRule(CONTAINER_ID, AlignDirection::RIGHT, HorizontalAlign::START, alignRules);
    RelativeContainerTestUtils::AddAlignRule(CONTAINER_ID, AlignDirection::TOP, VerticalAlign::TOP, alignRules);
    flexItemComponent->SetAlignRules(alignRules);
    renderFlexItem->Update(flexItemComponent);
    auto renderBox = RelativeContainerTestUtils::CreateRenderBox(ITEM_WIDTH, ITEM_HEIGHT, mockContext);
    renderFlexItem->AddChild(renderBox);

    RefPtr<RenderRoot> renderRoot = RelativeContainerTestUtils::CreateRenderRoot();
    auto renderRelativeContainer = RelativeContainerTestUtils::CreateRenderRelativeContainer(mockContext);
    renderRoot->AddChild(renderRelativeContainer);
    renderRelativeContainer->AddChild(renderFlexItem);
    ASSERT_TRUE(renderRelativeContainer->GetChildren().size() == 1);

    /**
     * @tc.steps: step2. call PerformLayout interface
     * @tc.expected: step2. the position of the flex item and the layout size of render box are set correctly
     */
    renderRoot->PerformLayout();
    renderRelativeContainer->PerformLayout();
    ASSERT_TRUE(renderRelativeContainer->GetLayoutSize() == CONTAINER_SIZE);
    const RefPtr<RenderNode>& child = renderRelativeContainer->GetChildren().front();
    const RefPtr<RenderNode>& boxNode = child->GetChildren().front();
    ASSERT_TRUE(child->GetPosition() == OFFSET_TOP_LEFT - Offset(ITEM_WIDTH, ZERO));
    ASSERT_TRUE(boxNode->GetLayoutSize() == ITEM_SIZE);
}

/* *
 * @tc.name: OneComponentWithTwoAnchorRules005
 * @tc.desc: Verify the location of a component with two anchor rules
 * @tc.type: FUNC
 */
HWTEST_F(RenderRelativeContainerTest, OneComponentWithTwoAnchorRules005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the render node tree, set id and anchor rules to the flex item,
     *                   set width and height to the render box
     */
    auto mockContext = MockRenderCommon::GetMockContext();

    /**
     * corresponding ets code:
     *   Box().width(ITEM_WIDTH).height(ITEM_HEIGHT)
     *       .alignRules({
     *         bottom: { anchor: CONTAINER_ID, align: VerticalAlign.Top },
     *         left: { anchor: CONTAINER_ID, align: HorizontalAlign.Start },
     *       }).id(COMPONENT_ID)
     */
    RefPtr<FlexItemComponent> flexItemComponent = AceType::MakeRefPtr<FlexItemComponent>();
    RefPtr<RenderFlexItem> renderFlexItem = AceType::MakeRefPtr<RenderFlexItem>();
    renderFlexItem->Attach(mockContext);
    flexItemComponent->SetInspectorKey(COMPONENT_ID);
    std::map<AlignDirection, AlignRule> alignRules;
    RelativeContainerTestUtils::AddAlignRule(CONTAINER_ID, AlignDirection::BOTTOM, VerticalAlign::TOP, alignRules);
    RelativeContainerTestUtils::AddAlignRule(CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::START, alignRules);
    flexItemComponent->SetAlignRules(alignRules);
    renderFlexItem->Update(flexItemComponent);
    auto renderBox = RelativeContainerTestUtils::CreateRenderBox(ITEM_WIDTH, ITEM_HEIGHT, mockContext);
    renderFlexItem->AddChild(renderBox);

    RefPtr<RenderRoot> renderRoot = RelativeContainerTestUtils::CreateRenderRoot();
    auto renderRelativeContainer = RelativeContainerTestUtils::CreateRenderRelativeContainer(mockContext);
    renderRoot->AddChild(renderRelativeContainer);
    renderRelativeContainer->AddChild(renderFlexItem);
    ASSERT_TRUE(renderRelativeContainer->GetChildren().size() == 1);

    /**
     * @tc.steps: step2. call PerformLayout interface
     * @tc.expected: step2. the position of the flex item and the layout size of render box are set correctly
     */
    renderRoot->PerformLayout();
    renderRelativeContainer->PerformLayout();
    ASSERT_TRUE(renderRelativeContainer->GetLayoutSize() == CONTAINER_SIZE);
    const RefPtr<RenderNode>& child = renderRelativeContainer->GetChildren().front();
    const RefPtr<RenderNode>& boxNode = child->GetChildren().front();
    ASSERT_TRUE(child->GetPosition() == OFFSET_TOP_LEFT - Offset(ZERO, ITEM_HEIGHT));
    ASSERT_TRUE(boxNode->GetLayoutSize() == ITEM_SIZE);
}

/* *
 * @tc.name: ReverseOrder001
 * @tc.desc: Verify the location of two components whose anchor rules are in reverse order
 * @tc.type: FUNC
 */
HWTEST_F(RenderRelativeContainerTest, ReverseOrder001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the render node tree, set id and anchor rules to the flex items,
     *                   set width and height to the render boxs
     */
    auto mockContext = MockRenderCommon::GetMockContext();

    /**
     * corresponding ets code:
     *   Box().width(ITEM_WIDTH).height(ITEM_HEIGHT)
     *       .alignRules({
     *         left: { anchor: CONTAINER_ID, align: HorizontalAlign.Start },
     *         top: { anchor: CONTAINER_ID, align: VerticalAlign.Center },
     *       }).id(COMPONENT_ID)
     */
    RefPtr<FlexItemComponent> flexItemComponent = AceType::MakeRefPtr<FlexItemComponent>();
    RefPtr<RenderFlexItem> renderFlexItem = AceType::MakeRefPtr<RenderFlexItem>();
    renderFlexItem->Attach(mockContext);
    flexItemComponent->SetInspectorKey(COMPONENT_ID);
    std::map<AlignDirection, AlignRule> alignRules;
    RelativeContainerTestUtils::AddAlignRule(CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::START, alignRules);
    RelativeContainerTestUtils::AddAlignRule(CONTAINER_ID, AlignDirection::TOP, VerticalAlign::CENTER, alignRules);
    flexItemComponent->SetAlignRules(alignRules);
    renderFlexItem->Update(flexItemComponent);
    auto renderBox = RelativeContainerTestUtils::CreateRenderBox(ITEM_WIDTH, ITEM_HEIGHT, mockContext);
    renderFlexItem->AddChild(renderBox);

    /**
     * corresponding ets code:
     *   Box().width(ITEM_WIDTH).height(ITEM_HEIGHT)
     *       .alignRules({
     *         left: { anchor: COMPONENT_ID, align: HorizontalAlign.End },
     *         right: { anchor: COMPONENT_ID, align: HorizontalAlign.Start },
     *       }).id(SECOND_COMPONENT_ID)
     */
    RefPtr<FlexItemComponent> secondFlexItemComponent = AceType::MakeRefPtr<FlexItemComponent>();
    RefPtr<RenderFlexItem> secondRenderFlexItem = AceType::MakeRefPtr<RenderFlexItem>();
    secondRenderFlexItem->Attach(mockContext);
    secondFlexItemComponent->SetInspectorKey(SECOND_COMPONENT_ID);
    std::map<AlignDirection, AlignRule> secondAlignRules;
    RelativeContainerTestUtils::AddAlignRule(
        COMPONENT_ID, AlignDirection::LEFT, HorizontalAlign::END, secondAlignRules);
    RelativeContainerTestUtils::AddAlignRule(
        COMPONENT_ID, AlignDirection::RIGHT, HorizontalAlign::START, secondAlignRules);
    secondFlexItemComponent->SetAlignRules(secondAlignRules);
    secondRenderFlexItem->Update(secondFlexItemComponent);
    auto secondRenderBox = RelativeContainerTestUtils::CreateRenderBox(ITEM_WIDTH, ITEM_HEIGHT, mockContext);
    secondRenderFlexItem->AddChild(secondRenderBox);

    RefPtr<RenderRoot> renderRoot = RelativeContainerTestUtils::CreateRenderRoot();
    auto renderRelativeContainer = RelativeContainerTestUtils::CreateRenderRelativeContainer(mockContext);
    renderRoot->AddChild(renderRelativeContainer);
    renderRelativeContainer->AddChild(renderFlexItem);
    renderRelativeContainer->AddChild(secondRenderFlexItem);
    ASSERT_TRUE(renderRelativeContainer->GetChildren().size() == 2);

    /**
     * @tc.steps: step2. call PerformLayout interface
     * @tc.expected: step2. the positions and layout sizes of render boxs and flex items are set correctly
     */
    renderRoot->PerformLayout();
    renderRelativeContainer->PerformLayout();
    ASSERT_TRUE(renderRelativeContainer->GetLayoutSize() == CONTAINER_SIZE);
    ASSERT_TRUE(renderFlexItem->GetPosition() == OFFSET_CENTER_LEFT);
    ASSERT_TRUE(renderFlexItem->GetLayoutSize() == ITEM_SIZE);
    ASSERT_TRUE(secondRenderFlexItem->GetPosition() == Offset(ITEM_WIDTH, ZERO));
    ASSERT_TRUE(secondRenderFlexItem->GetLayoutSize() == Size(ZERO, ZERO));
}

/* *
 * @tc.name: TwoComponents001
 * @tc.desc: Verify the location of two components with anchor rules and ids
 * @tc.type: FUNC
 */
HWTEST_F(RenderRelativeContainerTest, TwoComponents001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the render node tree, set id and anchor rules to the flex items,
     *                   set width and height to the render boxs
     */
    auto mockContext = MockRenderCommon::GetMockContext();

    /**
     * corresponding ets code:
     *   Box().width(ITEM_WIDTH).height(ITEM_HEIGHT)
     *       .alignRules({
     *         left: { anchor: CONTAINER_ID, align: HorizontalAlign.Start },
     *         top: { anchor: CONTAINER_ID, align: VerticalAlign.Top },
     *       }).id(COMPONENT_ID)
     */
    RefPtr<FlexItemComponent> flexItemComponent = AceType::MakeRefPtr<FlexItemComponent>();
    RefPtr<RenderFlexItem> renderFlexItem = AceType::MakeRefPtr<RenderFlexItem>();
    renderFlexItem->Attach(mockContext);
    flexItemComponent->SetInspectorKey(COMPONENT_ID);
    std::map<AlignDirection, AlignRule> alignRules;
    RelativeContainerTestUtils::AddAlignRule(CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::START, alignRules);
    RelativeContainerTestUtils::AddAlignRule(CONTAINER_ID, AlignDirection::TOP, VerticalAlign::TOP, alignRules);
    flexItemComponent->SetAlignRules(alignRules);
    renderFlexItem->Update(flexItemComponent);
    auto renderBox = RelativeContainerTestUtils::CreateRenderBox(ITEM_WIDTH, ITEM_HEIGHT, mockContext);
    renderFlexItem->AddChild(renderBox);

    /**
     * corresponding ets code:
     *   Box().width(ITEM_WIDTH).height(ITEM_HEIGHT)
     *       .alignRules({
     *         left: { anchor: COMPONENT_ID, align: HorizontalAlign.End },
     *         top: { anchor: COMPONENT_ID, align: VerticalAlign.Center },
     *       }).id(SECOND_COMPONENT_ID)
     */
    RefPtr<FlexItemComponent> secondFlexItemComponent = AceType::MakeRefPtr<FlexItemComponent>();
    RefPtr<RenderFlexItem> secondRenderFlexItem = AceType::MakeRefPtr<RenderFlexItem>();
    secondRenderFlexItem->Attach(mockContext);
    secondFlexItemComponent->SetInspectorKey(SECOND_COMPONENT_ID);
    std::map<AlignDirection, AlignRule> secondAlignRules;
    RelativeContainerTestUtils::AddAlignRule(
        COMPONENT_ID, AlignDirection::LEFT, HorizontalAlign::END, secondAlignRules);
    RelativeContainerTestUtils::AddAlignRule(
        COMPONENT_ID, AlignDirection::TOP, VerticalAlign::CENTER, secondAlignRules);
    secondFlexItemComponent->SetAlignRules(secondAlignRules);
    secondRenderFlexItem->Update(secondFlexItemComponent);
    auto secondRenderBox = RelativeContainerTestUtils::CreateRenderBox(ITEM_WIDTH, ITEM_HEIGHT, mockContext);
    secondRenderFlexItem->AddChild(secondRenderBox);

    RefPtr<RenderRoot> renderRoot = RelativeContainerTestUtils::CreateRenderRoot();
    auto renderRelativeContainer = RelativeContainerTestUtils::CreateRenderRelativeContainer(mockContext);
    renderRoot->AddChild(renderRelativeContainer);
    renderRelativeContainer->AddChild(renderFlexItem);
    renderRelativeContainer->AddChild(secondRenderFlexItem);
    ASSERT_TRUE(renderRelativeContainer->GetChildren().size() == 2);

    /**
     * @tc.steps: step2. call PerformLayout interface
     * @tc.expected: step2. the positions and layout sizes of render boxs and flex items are set correctly
     */
    renderRoot->PerformLayout();
    renderRelativeContainer->PerformLayout();
    ASSERT_TRUE(renderRelativeContainer->GetLayoutSize() == CONTAINER_SIZE);

    ASSERT_TRUE(renderFlexItem->GetPosition() == OFFSET_TOP_LEFT);
    ASSERT_TRUE(renderFlexItem->GetLayoutSize() == ITEM_SIZE);
    ASSERT_TRUE(secondRenderFlexItem->GetPosition() == OFFSET_TOP_LEFT + Offset(ITEM_WIDTH, ITEM_HEIGHT / 2));
    ASSERT_TRUE(secondRenderFlexItem->GetLayoutSize() == ITEM_SIZE);
}

/* *
 * @tc.name: TwoComponents002
 * @tc.desc: Verify the location of two components with anchor rules and ids
 * @tc.type: FUNC
 */
HWTEST_F(RenderRelativeContainerTest, TwoComponents002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the render node tree, set id and anchor rules to the flex items,
     *                   set width and height to the render boxs
     */
    auto mockContext = MockRenderCommon::GetMockContext();

    /**
     * corresponding ets code:
     *   Box().width(ITEM_WIDTH).height(ITEM_HEIGHT)
     *       .alignRules({
     *         left: { anchor: CONTAINER_ID, align: HorizontalAlign.Center },
     *       }).id(COMPONENT_ID)
     */
    RefPtr<FlexItemComponent> flexItemComponent = AceType::MakeRefPtr<FlexItemComponent>();
    RefPtr<RenderFlexItem> renderFlexItem = AceType::MakeRefPtr<RenderFlexItem>();
    renderFlexItem->Attach(mockContext);
    flexItemComponent->SetInspectorKey(COMPONENT_ID);
    std::map<AlignDirection, AlignRule> alignRules;
    RelativeContainerTestUtils::AddAlignRule(CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::CENTER, alignRules);
    flexItemComponent->SetAlignRules(alignRules);
    renderFlexItem->Update(flexItemComponent);
    auto renderBox = RelativeContainerTestUtils::CreateRenderBox(ITEM_WIDTH, ITEM_HEIGHT, mockContext);
    renderFlexItem->AddChild(renderBox);

    /**
     * corresponding ets code:
     *   Box().width(ITEM_WIDTH).height(ITEM_HEIGHT)
     *       .alignRules({
     *         left: { anchor: COMPONENT_ID, align: HorizontalAlign.Start },
     *         top: { anchor: COMPONENT_ID, align: VerticalAlign.Top },
     *       }).id(SECOND_COMPONENT_ID)
     */
    RefPtr<FlexItemComponent> secondFlexItemComponent = AceType::MakeRefPtr<FlexItemComponent>();
    RefPtr<RenderFlexItem> secondRenderFlexItem = AceType::MakeRefPtr<RenderFlexItem>();
    secondRenderFlexItem->Attach(mockContext);
    secondFlexItemComponent->SetInspectorKey(SECOND_COMPONENT_ID);
    std::map<AlignDirection, AlignRule> secondAlignRules;
    RelativeContainerTestUtils::AddAlignRule(
        COMPONENT_ID, AlignDirection::LEFT, HorizontalAlign::START, secondAlignRules);
    RelativeContainerTestUtils::AddAlignRule(COMPONENT_ID, AlignDirection::TOP, VerticalAlign::TOP, secondAlignRules);
    secondFlexItemComponent->SetAlignRules(secondAlignRules);
    secondRenderFlexItem->Update(secondFlexItemComponent);
    auto secondRenderBox = RelativeContainerTestUtils::CreateRenderBox(ITEM_WIDTH, ITEM_HEIGHT, mockContext);
    secondRenderFlexItem->AddChild(secondRenderBox);

    RefPtr<RenderRoot> renderRoot = RelativeContainerTestUtils::CreateRenderRoot();
    auto renderRelativeContainer = RelativeContainerTestUtils::CreateRenderRelativeContainer(mockContext);
    renderRoot->AddChild(renderRelativeContainer);
    renderRelativeContainer->AddChild(renderFlexItem);
    renderRelativeContainer->AddChild(secondRenderFlexItem);
    ASSERT_TRUE(renderRelativeContainer->GetChildren().size() == 2);

    /**
     * @tc.steps: step2. call PerformLayout interface
     * @tc.expected: step2. the positions and layout sizes of render boxs and flex items are set correctly
     */
    renderRoot->PerformLayout();
    renderRelativeContainer->PerformLayout();
    ASSERT_TRUE(renderRelativeContainer->GetLayoutSize() == CONTAINER_SIZE);
    ASSERT_TRUE(renderFlexItem->GetPosition() == OFFSET_TOP_MIDDLE);
    ASSERT_TRUE(renderFlexItem->GetLayoutSize() == ITEM_SIZE);
    ASSERT_TRUE(secondRenderFlexItem->GetPosition() == OFFSET_TOP_MIDDLE);
    ASSERT_TRUE(secondRenderFlexItem->GetLayoutSize() == ITEM_SIZE);
}

/* *
 * @tc.name: TwoComponents003
 * @tc.desc: Verify the location of two components with anchor rules and ids
 * @tc.type: FUNC
 */
HWTEST_F(RenderRelativeContainerTest, TwoComponents003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the render node tree, set id and anchor rules to the flex items,
     *                   set width and height to the render boxs
     */
    auto mockContext = MockRenderCommon::GetMockContext();

    /**
     * corresponding ets code:
     *   Box().width(ITEM_WIDTH).height(ITEM_HEIGHT)
     *       .alignRules({
     *         top: { anchor: CONTAINER_ID, align: VerticalAlign.Center },
     *       }).id(COMPONENT_ID)
     */
    RefPtr<FlexItemComponent> flexItemComponent = AceType::MakeRefPtr<FlexItemComponent>();
    RefPtr<RenderFlexItem> renderFlexItem = AceType::MakeRefPtr<RenderFlexItem>();
    renderFlexItem->Attach(mockContext);
    flexItemComponent->SetInspectorKey(COMPONENT_ID);
    std::map<AlignDirection, AlignRule> alignRules;
    RelativeContainerTestUtils::AddAlignRule(CONTAINER_ID, AlignDirection::TOP, VerticalAlign::CENTER, alignRules);
    flexItemComponent->SetAlignRules(alignRules);
    renderFlexItem->Update(flexItemComponent);
    auto renderBox = RelativeContainerTestUtils::CreateRenderBox(ITEM_WIDTH, ITEM_HEIGHT, mockContext);
    renderFlexItem->AddChild(renderBox);

    /**
     * corresponding ets code:
     *   Box().width(ITEM_WIDTH).height(ITEM_HEIGHT)
     *       .alignRules({
     *         left: { anchor: COMPONENT_ID, align: HorizontalAlign.Start },
     *         top: { anchor: COMPONENT_ID, align: VerticalAlign.Center },
     *       }).id(SECOND_COMPONENT_ID)
     */
    RefPtr<FlexItemComponent> secondFlexItemComponent = AceType::MakeRefPtr<FlexItemComponent>();
    RefPtr<RenderFlexItem> secondRenderFlexItem = AceType::MakeRefPtr<RenderFlexItem>();
    secondRenderFlexItem->Attach(mockContext);
    secondFlexItemComponent->SetInspectorKey(SECOND_COMPONENT_ID);
    std::map<AlignDirection, AlignRule> secondAlignRules;
    RelativeContainerTestUtils::AddAlignRule(
        COMPONENT_ID, AlignDirection::LEFT, HorizontalAlign::START, secondAlignRules);
    RelativeContainerTestUtils::AddAlignRule(
        COMPONENT_ID, AlignDirection::TOP, VerticalAlign::CENTER, secondAlignRules);
    secondFlexItemComponent->SetAlignRules(secondAlignRules);
    secondRenderFlexItem->Update(secondFlexItemComponent);
    auto secondRenderBox = RelativeContainerTestUtils::CreateRenderBox(ITEM_WIDTH, ITEM_HEIGHT, mockContext);
    secondRenderFlexItem->AddChild(secondRenderBox);

    RefPtr<RenderRoot> renderRoot = RelativeContainerTestUtils::CreateRenderRoot();
    auto renderRelativeContainer = RelativeContainerTestUtils::CreateRenderRelativeContainer(mockContext);
    renderRoot->AddChild(renderRelativeContainer);
    renderRelativeContainer->AddChild(renderFlexItem);
    renderRelativeContainer->AddChild(secondRenderFlexItem);
    ASSERT_TRUE(renderRelativeContainer->GetChildren().size() == 2);

    /**
     * @tc.steps: step2. call PerformLayout interface
     * @tc.expected: step2. the positions and layout sizes of render boxs and flex items are set correctly
     */
    renderRoot->PerformLayout();
    renderRelativeContainer->PerformLayout();
    ASSERT_TRUE(renderRelativeContainer->GetLayoutSize() == CONTAINER_SIZE);
    ASSERT_TRUE(renderFlexItem->GetPosition() == OFFSET_CENTER_LEFT);
    ASSERT_TRUE(renderFlexItem->GetLayoutSize() == ITEM_SIZE);
    ASSERT_TRUE(secondRenderFlexItem->GetPosition() == OFFSET_CENTER_LEFT + Offset(ZERO, ITEM_HEIGHT / 2));
    ASSERT_TRUE(secondRenderFlexItem->GetLayoutSize() == ITEM_SIZE);
}

/* *
 * @tc.name: TwoComponents004
 * @tc.desc: Verify the location of two components with anchor rules and ids
 * @tc.type: FUNC
 */
HWTEST_F(RenderRelativeContainerTest, TwoComponents004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the render node tree, set id and anchor rules to the flex items,
     *                   set width and height to the render boxs
     */
    auto mockContext = MockRenderCommon::GetMockContext();

    /**
     * corresponding ets code:
     *   Box().width(ITEM_WIDTH).height(ITEM_HEIGHT)
     *       .alignRules({
     *         middle: { anchor: CONTAINER_ID, align: HorizontalAlign.Center },
     *         center: { anchor: CONTAINER_ID, align: VerticalAlign.Center },
     *       }).id(COMPONENT_ID)
     */
    RefPtr<FlexItemComponent> flexItemComponent = AceType::MakeRefPtr<FlexItemComponent>();
    RefPtr<RenderFlexItem> renderFlexItem = AceType::MakeRefPtr<RenderFlexItem>();
    renderFlexItem->Attach(mockContext);
    flexItemComponent->SetInspectorKey(COMPONENT_ID);
    std::map<AlignDirection, AlignRule> alignRules;
    RelativeContainerTestUtils::AddAlignRule(CONTAINER_ID, AlignDirection::MIDDLE, HorizontalAlign::CENTER, alignRules);
    RelativeContainerTestUtils::AddAlignRule(CONTAINER_ID, AlignDirection::CENTER, VerticalAlign::CENTER, alignRules);
    flexItemComponent->SetAlignRules(alignRules);
    renderFlexItem->Update(flexItemComponent);
    auto renderBox = RelativeContainerTestUtils::CreateRenderBox(ITEM_WIDTH, ITEM_HEIGHT, mockContext);
    renderFlexItem->AddChild(renderBox);

    /**
     * corresponding ets code:
     *   Box().width(ITEM_WIDTH).height(ITEM_HEIGHT)
     *       .alignRules({
     *         left: { anchor: COMPONENT_ID, align: HorizontalAlign.End },
     *         top: { anchor: COMPONENT_ID, align: VerticalAlign.Bottom },
     *       }).id(SECOND_COMPONENT_ID)
     */
    RefPtr<FlexItemComponent> secondFlexItemComponent = AceType::MakeRefPtr<FlexItemComponent>();
    RefPtr<RenderFlexItem> secondRenderFlexItem = AceType::MakeRefPtr<RenderFlexItem>();
    secondRenderFlexItem->Attach(mockContext);
    secondFlexItemComponent->SetInspectorKey(SECOND_COMPONENT_ID);
    std::map<AlignDirection, AlignRule> secondAlignRules;
    RelativeContainerTestUtils::AddAlignRule(
        COMPONENT_ID, AlignDirection::LEFT, HorizontalAlign::END, secondAlignRules);
    RelativeContainerTestUtils::AddAlignRule(
        COMPONENT_ID, AlignDirection::TOP, VerticalAlign::BOTTOM, secondAlignRules);
    secondFlexItemComponent->SetAlignRules(secondAlignRules);
    secondRenderFlexItem->Update(secondFlexItemComponent);
    auto secondRenderBox = RelativeContainerTestUtils::CreateRenderBox(ITEM_WIDTH, ITEM_HEIGHT, mockContext);
    secondRenderFlexItem->AddChild(secondRenderBox);

    RefPtr<RenderRoot> renderRoot = RelativeContainerTestUtils::CreateRenderRoot();
    auto renderRelativeContainer = RelativeContainerTestUtils::CreateRenderRelativeContainer(mockContext);
    renderRoot->AddChild(renderRelativeContainer);
    renderRelativeContainer->AddChild(renderFlexItem);
    renderRelativeContainer->AddChild(secondRenderFlexItem);
    ASSERT_TRUE(renderRelativeContainer->GetChildren().size() == 2);

    /**
     * @tc.steps: step2. call PerformLayout interface
     * @tc.expected: step2. the positions and layout sizes of render boxs and flex items are set correctly
     */
    renderRoot->PerformLayout();
    renderRelativeContainer->PerformLayout();
    ASSERT_TRUE(renderRelativeContainer->GetLayoutSize() == CONTAINER_SIZE);
    ASSERT_TRUE(renderFlexItem->GetPosition() == OFFSET_CENTER_MIDDLE - Offset(ITEM_WIDTH / 2, ITEM_HEIGHT / 2));
    ASSERT_TRUE(renderFlexItem->GetLayoutSize() == ITEM_SIZE);
    ASSERT_TRUE(secondRenderFlexItem->GetPosition() == OFFSET_CENTER_MIDDLE + Offset(ITEM_WIDTH / 2, ITEM_HEIGHT / 2));
    ASSERT_TRUE(secondRenderFlexItem->GetLayoutSize() == ITEM_SIZE);
}

/* *
 * @tc.name: TwoComponents005
 * @tc.desc: Verify the location of two components with anchor rules and ids
 * @tc.type: FUNC
 */
HWTEST_F(RenderRelativeContainerTest, TwoComponents005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the render node tree, set id and anchor rules to the flex items,
     *                   set width and height to the render boxs
     */
    auto mockContext = MockRenderCommon::GetMockContext();

    /**
     * corresponding ets code:
     *   Box().width(ITEM_WIDTH).height(ITEM_HEIGHT)
     *       .alignRules({
     *         left: { anchor: CONTAINER_ID, align: HorizontalAlign.Center },
     *       }).id(COMPONENT_ID)
     */
    RefPtr<FlexItemComponent> flexItemComponent = AceType::MakeRefPtr<FlexItemComponent>();
    RefPtr<RenderFlexItem> renderFlexItem = AceType::MakeRefPtr<RenderFlexItem>();
    renderFlexItem->Attach(mockContext);
    flexItemComponent->SetInspectorKey(COMPONENT_ID);
    std::map<AlignDirection, AlignRule> alignRules;
    RelativeContainerTestUtils::AddAlignRule(CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::CENTER, alignRules);
    flexItemComponent->SetAlignRules(alignRules);
    renderFlexItem->Update(flexItemComponent);
    auto renderBox = RelativeContainerTestUtils::CreateRenderBox(ITEM_WIDTH, ITEM_HEIGHT, mockContext);
    renderFlexItem->AddChild(renderBox);

    /**
     * corresponding ets code:
     *   Box().width(ITEM_WIDTH).height(ITEM_HEIGHT)
     *       .alignRules({
     *         top: { anchor: COMPONENT_ID, align: VerticalAlign.Bottom },
     *       }).id(SECOND_COMPONENT_ID)
     */
    RefPtr<FlexItemComponent> secondFlexItemComponent = AceType::MakeRefPtr<FlexItemComponent>();
    RefPtr<RenderFlexItem> secondRenderFlexItem = AceType::MakeRefPtr<RenderFlexItem>();
    secondRenderFlexItem->Attach(mockContext);
    secondFlexItemComponent->SetInspectorKey(SECOND_COMPONENT_ID);
    std::map<AlignDirection, AlignRule> secondAlignRules;
    RelativeContainerTestUtils::AddAlignRule(
        COMPONENT_ID, AlignDirection::TOP, VerticalAlign::BOTTOM, secondAlignRules);
    secondFlexItemComponent->SetAlignRules(secondAlignRules);
    secondRenderFlexItem->Update(secondFlexItemComponent);
    auto secondRenderBox = RelativeContainerTestUtils::CreateRenderBox(ITEM_WIDTH, ITEM_HEIGHT, mockContext);
    secondRenderFlexItem->AddChild(secondRenderBox);

    RefPtr<RenderRoot> renderRoot = RelativeContainerTestUtils::CreateRenderRoot();
    auto renderRelativeContainer = RelativeContainerTestUtils::CreateRenderRelativeContainer(mockContext);
    renderRoot->AddChild(renderRelativeContainer);
    renderRelativeContainer->AddChild(renderFlexItem);
    renderRelativeContainer->AddChild(secondRenderFlexItem);
    ASSERT_TRUE(renderRelativeContainer->GetChildren().size() == 2);

    /**
     * @tc.steps: step2. call PerformLayout interface
     * @tc.expected: step2. the positions and layout sizes of render boxs and flex items are set correctly
     */
    renderRoot->PerformLayout();
    renderRelativeContainer->PerformLayout();
    ASSERT_TRUE(renderRelativeContainer->GetLayoutSize() == CONTAINER_SIZE);
    ASSERT_TRUE(renderFlexItem->GetPosition() == OFFSET_TOP_MIDDLE);
    ASSERT_TRUE(renderFlexItem->GetLayoutSize() == ITEM_SIZE);
    ASSERT_TRUE(secondRenderFlexItem->GetPosition() == OFFSET_TOP_LEFT + Size(ZERO, ITEM_HEIGHT));
    ASSERT_TRUE(secondRenderFlexItem->GetLayoutSize() == ITEM_SIZE);
}

/* *
 * @tc.name: TwoComponents006
 * @tc.desc: Verify the location of two components with anchor rules and ids
 * @tc.type: FUNC
 */
HWTEST_F(RenderRelativeContainerTest, TwoComponents006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the render node tree, set id and anchor rules to the flex items,
     *                   set width and height to the render boxs
     */
    auto mockContext = MockRenderCommon::GetMockContext();

    /**
     * corresponding ets code:
     *   Box().width(ITEM_WIDTH).height(ITEM_HEIGHT)
     *       .alignRules({
     *         top: { anchor: CONTAINER_ID, align: VerticalAlign.Center },
     *       }).id(COMPONENT_ID)
     */
    RefPtr<FlexItemComponent> flexItemComponent = AceType::MakeRefPtr<FlexItemComponent>();
    RefPtr<RenderFlexItem> renderFlexItem = AceType::MakeRefPtr<RenderFlexItem>();
    renderFlexItem->Attach(mockContext);
    flexItemComponent->SetInspectorKey(COMPONENT_ID);
    std::map<AlignDirection, AlignRule> alignRules;
    RelativeContainerTestUtils::AddAlignRule(CONTAINER_ID, AlignDirection::TOP, VerticalAlign::CENTER, alignRules);
    flexItemComponent->SetAlignRules(alignRules);
    renderFlexItem->Update(flexItemComponent);
    auto renderBox = RelativeContainerTestUtils::CreateRenderBox(ITEM_WIDTH, ITEM_HEIGHT, mockContext);
    renderFlexItem->AddChild(renderBox);

    /**
     * corresponding ets code:
     *   Box().width(ITEM_WIDTH).height(ITEM_HEIGHT)
     *       .alignRules({
     *         bottom: { anchor: COMPONENT_ID, align: VerticalAlign.Top },
     *       }).id(SECOND_COMPONENT_ID)
     */
    RefPtr<FlexItemComponent> secondFlexItemComponent = AceType::MakeRefPtr<FlexItemComponent>();
    RefPtr<RenderFlexItem> secondRenderFlexItem = AceType::MakeRefPtr<RenderFlexItem>();
    secondRenderFlexItem->Attach(mockContext);
    secondFlexItemComponent->SetInspectorKey(SECOND_COMPONENT_ID);
    std::map<AlignDirection, AlignRule> secondAlignRules;
    RelativeContainerTestUtils::AddAlignRule(
        COMPONENT_ID, AlignDirection::BOTTOM, VerticalAlign::TOP, secondAlignRules);
    secondFlexItemComponent->SetAlignRules(secondAlignRules);
    secondRenderFlexItem->Update(secondFlexItemComponent);
    auto secondRenderBox = RelativeContainerTestUtils::CreateRenderBox(ITEM_WIDTH, ITEM_HEIGHT, mockContext);
    secondRenderFlexItem->AddChild(secondRenderBox);

    RefPtr<RenderRoot> renderRoot = RelativeContainerTestUtils::CreateRenderRoot();
    auto renderRelativeContainer = RelativeContainerTestUtils::CreateRenderRelativeContainer(mockContext);
    renderRoot->AddChild(renderRelativeContainer);
    renderRelativeContainer->AddChild(renderFlexItem);
    renderRelativeContainer->AddChild(secondRenderFlexItem);
    ASSERT_TRUE(renderRelativeContainer->GetChildren().size() == 2);

    /**
     * @tc.steps: step2. call PerformLayout interface
     * @tc.expected: step2. the positions and layout sizes of render boxs and flex items are set correctly
     */
    renderRoot->PerformLayout();
    renderRelativeContainer->PerformLayout();
    ASSERT_TRUE(renderRelativeContainer->GetLayoutSize() == CONTAINER_SIZE);
    ASSERT_TRUE(renderFlexItem->GetPosition() == OFFSET_CENTER_LEFT);
    ASSERT_TRUE(renderFlexItem->GetLayoutSize() == ITEM_SIZE);
    ASSERT_TRUE(secondRenderFlexItem->GetPosition() == OFFSET_CENTER_LEFT - Offset(ZERO, ITEM_HEIGHT));
    ASSERT_TRUE(secondRenderFlexItem->GetLayoutSize() == ITEM_SIZE);
}

/* *
 * @tc.name: TwoComponents007
 * @tc.desc: Verify the location of two components with anchor rules and ids
 * @tc.type: FUNC
 */
HWTEST_F(RenderRelativeContainerTest, TwoComponents007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the render node tree, set id and anchor rules to the flex items,
     *                   set width and height to the render boxs
     */
    auto mockContext = MockRenderCommon::GetMockContext();

    /**
     * corresponding ets code:
     *   Box().width(ITEM_WIDTH).height(ITEM_HEIGHT)
     *       .alignRules({
     *         middle: { anchor: CONTAINER_ID, align: HorizontalAlign.Center },
     *         center: { anchor: CONTAINER_ID, align: VerticalAlign.Center },
     *       }).id(COMPONENT_ID)
     */
    RefPtr<FlexItemComponent> flexItemComponent = AceType::MakeRefPtr<FlexItemComponent>();
    RefPtr<RenderFlexItem> renderFlexItem = AceType::MakeRefPtr<RenderFlexItem>();
    renderFlexItem->Attach(mockContext);
    flexItemComponent->SetInspectorKey(COMPONENT_ID);
    std::map<AlignDirection, AlignRule> alignRules;
    RelativeContainerTestUtils::AddAlignRule(CONTAINER_ID, AlignDirection::MIDDLE, HorizontalAlign::CENTER, alignRules);
    RelativeContainerTestUtils::AddAlignRule(CONTAINER_ID, AlignDirection::CENTER, VerticalAlign::CENTER, alignRules);
    flexItemComponent->SetAlignRules(alignRules);
    renderFlexItem->Update(flexItemComponent);
    auto renderBox = RelativeContainerTestUtils::CreateRenderBox(ITEM_WIDTH, ITEM_HEIGHT, mockContext);
    renderFlexItem->AddChild(renderBox);

    /**
     * corresponding ets code:
     *   Box().width(ITEM_WIDTH).height(ITEM_HEIGHT)
     *       .alignRules({
     *         middle: { anchor: CONTAINER_ID, align: HorizontalAlign.Center },
     *         bottom: { anchor: COMPONENT_ID, align: VerticalAlign.Bottom },
     *       }).id(SECOND_COMPONENT_ID)
     */
    RefPtr<FlexItemComponent> secondFlexItemComponent = AceType::MakeRefPtr<FlexItemComponent>();
    RefPtr<RenderFlexItem> secondRenderFlexItem = AceType::MakeRefPtr<RenderFlexItem>();
    secondRenderFlexItem->Attach(mockContext);
    secondFlexItemComponent->SetInspectorKey(SECOND_COMPONENT_ID);
    std::map<AlignDirection, AlignRule> secondAlignRules;
    RelativeContainerTestUtils::AddAlignRule(
        CONTAINER_ID, AlignDirection::MIDDLE, HorizontalAlign::CENTER, secondAlignRules);
    RelativeContainerTestUtils::AddAlignRule(
        COMPONENT_ID, AlignDirection::BOTTOM, VerticalAlign::BOTTOM, secondAlignRules);
    secondFlexItemComponent->SetAlignRules(secondAlignRules);
    secondRenderFlexItem->Update(secondFlexItemComponent);
    auto secondRenderBox = RelativeContainerTestUtils::CreateRenderBox(ITEM_WIDTH, ITEM_HEIGHT, mockContext);
    secondRenderFlexItem->AddChild(secondRenderBox);

    RefPtr<RenderRoot> renderRoot = RelativeContainerTestUtils::CreateRenderRoot();
    auto renderRelativeContainer = RelativeContainerTestUtils::CreateRenderRelativeContainer(mockContext);
    renderRoot->AddChild(renderRelativeContainer);
    renderRelativeContainer->AddChild(renderFlexItem);
    renderRelativeContainer->AddChild(secondRenderFlexItem);
    ASSERT_TRUE(renderRelativeContainer->GetChildren().size() == 2);

    /**
     * @tc.steps: step2. call PerformLayout interface
     * @tc.expected: step2. the positions and layout sizes of render boxs and flex items are set correctly
     */
    renderRoot->PerformLayout();
    renderRelativeContainer->PerformLayout();
    ASSERT_TRUE(renderRelativeContainer->GetLayoutSize() == CONTAINER_SIZE);
    ASSERT_TRUE(renderFlexItem->GetPosition() == OFFSET_CENTER_MIDDLE - Offset(ITEM_WIDTH / 2, ITEM_HEIGHT / 2));
    ASSERT_TRUE(renderFlexItem->GetLayoutSize() == ITEM_SIZE);
    ASSERT_TRUE(secondRenderFlexItem->GetPosition() == OFFSET_CENTER_MIDDLE - Offset(ITEM_WIDTH / 2, ITEM_HEIGHT / 2));
    ASSERT_TRUE(secondRenderFlexItem->GetLayoutSize() == ITEM_SIZE);
}

/* *
 * @tc.name: TwoComponents008
 * @tc.desc: Verify the location of two components with anchor rules and ids
 * @tc.type: FUNC
 */
HWTEST_F(RenderRelativeContainerTest, TwoComponents008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct the render node tree, set id and anchor rules to the flex items,
     *                   set width and height to the render boxs
     */
    auto mockContext = MockRenderCommon::GetMockContext();

    /**
     * corresponding ets code:
     *   Box().width(ITEM_WIDTH).height(ITEM_HEIGHT)
     *       .alignRules({
     *         middle: { anchor: CONTAINER_ID, align: HorizontalAlign.Center },
     *         center: { anchor: CONTAINER_ID, align: VerticalAlign.Center },
     *       }).id(COMPONENT_ID)
     */
    RefPtr<FlexItemComponent> flexItemComponent = AceType::MakeRefPtr<FlexItemComponent>();
    RefPtr<RenderFlexItem> renderFlexItem = AceType::MakeRefPtr<RenderFlexItem>();
    renderFlexItem->Attach(mockContext);
    flexItemComponent->SetInspectorKey(COMPONENT_ID);
    std::map<AlignDirection, AlignRule> alignRules;
    RelativeContainerTestUtils::AddAlignRule(CONTAINER_ID, AlignDirection::MIDDLE, HorizontalAlign::CENTER, alignRules);
    RelativeContainerTestUtils::AddAlignRule(CONTAINER_ID, AlignDirection::CENTER, VerticalAlign::CENTER, alignRules);
    flexItemComponent->SetAlignRules(alignRules);
    renderFlexItem->Update(flexItemComponent);
    auto renderBox = RelativeContainerTestUtils::CreateRenderBox(ITEM_WIDTH, ITEM_HEIGHT, mockContext);
    renderFlexItem->AddChild(renderBox);

    /**
     * corresponding ets code:
     *   Box().width(ITEM_WIDTH).height(ITEM_HEIGHT)
     *       .alignRules({
     *         left: { anchor: COMPONENT_ID, align: HorizontalAlign.Center },
     *         top: { anchor: CONTAINER_ID, align: VerticalAlign.Center },
     *       }).id(SECOND_COMPONENT_ID)
     */
    RefPtr<FlexItemComponent> secondFlexItemComponent = AceType::MakeRefPtr<FlexItemComponent>();
    RefPtr<RenderFlexItem> secondRenderFlexItem = AceType::MakeRefPtr<RenderFlexItem>();
    secondRenderFlexItem->Attach(mockContext);
    secondFlexItemComponent->SetInspectorKey(SECOND_COMPONENT_ID);
    std::map<AlignDirection, AlignRule> secondAlignRules;
    RelativeContainerTestUtils::AddAlignRule(
        COMPONENT_ID, AlignDirection::LEFT, HorizontalAlign::CENTER, secondAlignRules);
    RelativeContainerTestUtils::AddAlignRule(
        CONTAINER_ID, AlignDirection::TOP, VerticalAlign::CENTER, secondAlignRules);
    secondFlexItemComponent->SetAlignRules(secondAlignRules);
    secondRenderFlexItem->Update(secondFlexItemComponent);
    auto secondRenderBox = RelativeContainerTestUtils::CreateRenderBox(ITEM_WIDTH, ITEM_HEIGHT, mockContext);
    secondRenderFlexItem->AddChild(secondRenderBox);

    RefPtr<RenderRoot> renderRoot = RelativeContainerTestUtils::CreateRenderRoot();
    auto renderRelativeContainer = RelativeContainerTestUtils::CreateRenderRelativeContainer(mockContext);
    renderRoot->AddChild(renderRelativeContainer);
    renderRelativeContainer->AddChild(renderFlexItem);
    renderRelativeContainer->AddChild(secondRenderFlexItem);
    ASSERT_TRUE(renderRelativeContainer->GetChildren().size() == 2);

    /**
     * @tc.steps: step2. call PerformLayout interface
     * @tc.expected: step2. the positions and layout sizes of render boxs and flex items are set correctly
     */
    renderRoot->PerformLayout();
    renderRelativeContainer->PerformLayout();
    ASSERT_TRUE(renderRelativeContainer->GetLayoutSize() == CONTAINER_SIZE);
    ASSERT_TRUE(renderFlexItem->GetPosition() == OFFSET_CENTER_MIDDLE - Offset(ITEM_WIDTH / 2, ITEM_HEIGHT / 2));
    ASSERT_TRUE(renderFlexItem->GetLayoutSize() == ITEM_SIZE);
    ASSERT_TRUE(secondRenderFlexItem->GetPosition() == OFFSET_CENTER_MIDDLE);
    ASSERT_TRUE(secondRenderFlexItem->GetLayoutSize() == ITEM_SIZE);
}
} // namespace OHOS::Ace