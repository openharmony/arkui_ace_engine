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
#include "base/log/log.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/common/layout/align_declaration.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/layout/position_param.h"
#include "base/utils/utils.h"
#include "core/components/button/button_component.h"
#include "core/components/flex/flex_item_component.h"
#include "core/components/flex/render_flex_item.h"
#include "core/components/relative_container/relative_container_component.h"
#include "core/components/relative_container/render_relative_container.h"
#include "core/components/root/render_root.h"
#include "core/components/test/unittest/mock/mock_render_common.h"
#include "core/pipeline/base/component.h"
#include "core/pipeline/base/constants.h"
#include "core/components/test/unittest/relative_container/relative_container_test_utils.h"
// todo

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {
    const double CONTAINER_WIDTH = 1080.0;
    const double CONTAINER_HEIGHT = 2244.0;

    const double ITEM_WIDTH = 200.0;
    const double ITEM_HEIGHT = 200.0;

    const Offset OFFSET_TOP_LEFT = Offset(0.0, 0.0);
    const Offset OFFSET_CENTER_CENTER = Offset(540.0, 1122.0);

    const std::string COMPONENT_ID = "bt1";
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


/**
 * @tc.name: ComponentWithoutId001
 * @tc.desc: Verify the location of a component without an id set
 * @tc.type: FUNC
 */
HWTEST_F(RenderRelativeContainerTest, OneComponentWithoutId001, TestSize.Level1) {
    /**
     * @tc.steps: step1. construct the render node tree, set basis property to the flex item
     */
    auto mockContext = MockRenderCommon::GetMockContext();

    std::list<RefPtr<Component>> children;
    RefPtr<OHOS::Ace::RelativeContainerComponent> relativeContainerComponent =
            AceType::MakeRefPtr<RelativeContainerComponent>(children);
    RefPtr<MockRenderRelativeContainer> renderRelativeContainer = AceType::MakeRefPtr<MockRenderRelativeContainer>();
    renderRelativeContainer->Attach(mockContext);

    RefPtr<RenderRoot> renderRoot = RelativeContainerTestUtils::CreateRenderRoot();
    renderRoot->AddChild(renderRelativeContainer);
    renderRelativeContainer->Update(relativeContainerComponent);
    renderRelativeContainer->AddChild(RelativeContainerTestUtils::CreateRenderText(mockContext));
    ASSERT_TRUE(renderRelativeContainer->GetChildren().size() == 1);

    /**
     * @tc.steps: step2. call PerformLayout interface
     * @tc.expected: step2. the positions are set correctly
     */

    renderRoot->PerformLayout();
    renderRelativeContainer->PerformLayout();
    ASSERT_TRUE(renderRelativeContainer->GetLayoutSize() == Size(CONTAINER_WIDTH, CONTAINER_HEIGHT));
    const RefPtr<RenderNode>& child = renderRelativeContainer->GetChildren().front();
    ASSERT_TRUE(child->GetPosition() == OFFSET_TOP_LEFT);
}


/**
 * @tc.name: OneComponentWithTwoAnchorRules001
 * @tc.desc: Verify the location of a component without one horizontal alignment rule and one vertical alignment rule
 * @tc.type: FUNC
 */
HWTEST_F(RenderRelativeContainerTest, OneComponentWithTwoAnchorRules001, TestSize.Level1) {
    /**
     * @tc.steps: step1. construct the render node tree, set basis property and alignrules to the flex item
     */
    auto mockContext = MockRenderCommon::GetMockContext();

    RefPtr<FlexItemComponent> flexItemComponent = AceType::MakeRefPtr<FlexItemComponent>();
    RefPtr<RenderFlexItem> renderFlexItem = AceType::MakeRefPtr<RenderFlexItem>();
    renderFlexItem->Attach(mockContext);

    flexItemComponent->SetInspectorKey(COMPONENT_ID);
    std::map<AlignDirection, AlignRule> alignRules;
    AlignRule alignRule;
    alignRule.anchor = CONTAINER_ID;
    alignRule.horizontal = HorizontalAlign::CENTER;
    alignRules[AlignDirection::LEFT] = alignRule;

    AlignRule alignRule2;
    alignRule2.anchor = CONTAINER_ID;
    alignRule2.vertical = VerticalAlign::CENTER;
    alignRules[AlignDirection::TOP] = alignRule2;
    flexItemComponent->SetAlignRules(alignRules);
    renderFlexItem->Update(flexItemComponent);
    renderFlexItem->SetLayoutSize(Size(ITEM_WIDTH, ITEM_HEIGHT));
    auto rendertext = RelativeContainerTestUtils::CreateRenderText(mockContext);
    renderFlexItem->AddChild(rendertext);

    RefPtr<RenderRoot> renderRoot = RelativeContainerTestUtils::CreateRenderRoot();

    std::list<RefPtr<Component>> children;
    RefPtr<OHOS::Ace::RelativeContainerComponent> relativeContainerComponent =
            AceType::MakeRefPtr<RelativeContainerComponent>(children);
    RefPtr<MockRenderRelativeContainer> renderRelativeContainer = AceType::MakeRefPtr<MockRenderRelativeContainer>();
    renderRelativeContainer->Attach(mockContext);
    renderRoot->AddChild(renderRelativeContainer);
    renderRelativeContainer->Update(relativeContainerComponent);

    renderRelativeContainer->AddChild(renderFlexItem);
    renderRelativeContainer->SetLayoutSize(Size(CONTAINER_WIDTH, CONTAINER_HEIGHT));
    ASSERT_TRUE(renderRelativeContainer->GetChildren().size() == 1);

    /**
     * @tc.steps: step2. call PerformLayout interface
     * @tc.expected: step2. the positions are set correctly
     */
    renderRoot->PerformLayout();
    renderRelativeContainer->PerformLayout();
    ASSERT_TRUE(renderRelativeContainer->GetLayoutSize() == Size(CONTAINER_WIDTH, CONTAINER_HEIGHT));

    const RefPtr<RenderNode>& child =renderRelativeContainer->GetChildren().front();
    ASSERT_TRUE(child->GetPosition() == OFFSET_CENTER_CENTER);
}
} // namespace OHOS::Ace
 