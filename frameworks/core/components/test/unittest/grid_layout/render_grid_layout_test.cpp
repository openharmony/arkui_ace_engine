/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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
#define private public
#define protected public
#include "core/components/grid_layout/grid_layout_component.h"
#include "core/components/grid_layout/render_grid_layout.h"
#include "core/components/test/unittest/grid_layout/grid_layout_test_utils.h"
#include "core/components/test/unittest/mock/mock_render_common.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {

class RenderGridLayoutTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;

    RefPtr<PipelineContext> mockContext_;
    RefPtr<RenderGridLayout> renderNode_;
    int32_t index_ = 0;
};

void RenderGridLayoutTest::SetUpTestCase() {}
void RenderGridLayoutTest::TearDownTestCase() {}

void RenderGridLayoutTest::SetUp()
{
    mockContext_ = MockRenderCommon::GetMockContext();
    renderNode_ = AceType::MakeRefPtr<RenderGridLayout>();
    renderNode_->Attach(mockContext_);
}

void RenderGridLayoutTest::TearDown()
{
    mockContext_ = nullptr;
    renderNode_ = nullptr;
}

/**
 * @tc.name: RenderGridLayoutTest001
 * @tc.desc: Verify Grid Layout PerformLayout can calculate four children with row direction.
 * @tc.type: FUNC
 */
HWTEST_F(RenderGridLayoutTest, RenderGridLayoutTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct component and render with 4 child by row direction.
     * @tc.expected: step1. properties and children are set correctly.
     */
    std::string rowArgs = "1fr 50%";
    std::string colArgs = "50% 1fr";
    renderNode_->Update(GridLayoutTestUtils::CreateComponent(FlexDirection::ROW, rowArgs, colArgs));
    int32_t count = 4;
    for (int32_t i = 0; i < count; ++i) {
        RefPtr<RenderNode> item = GridLayoutTestUtils::CreateRenderItem(-1, -1, 1, 1);
        item->GetChildren().front()->Attach(mockContext_);
        item->Attach(mockContext_);
        renderNode_->AddChild(item);
    }
    ASSERT_TRUE(renderNode_->GetChildren().size() == 4);

    /**
     * @tc.steps: step2. Verify that the properties are calculated correctly.
     * @tc.expected: step2. Properties and children are calculated correctly.
     */
    renderNode_->PerformLayout();
    ASSERT_TRUE(renderNode_->GetLayoutSize() == Size(1080.0, 1080.0));
    const std::list<RefPtr<RenderNode>>& items = renderNode_->GetChildren();
    ASSERT_TRUE(items.size() == 4);
    int32_t index = 0;
    for (const auto& item : items) {
        GridLayoutTestUtils::PrintNodeInfo(item);
        ASSERT_TRUE(item->GetPosition() == Offset(index / 2 * 540.0, index % 2 * 540.0));
        ASSERT_TRUE(item->GetLayoutSize() == Size(540.0, 540.0));
        index++;
    }
}

/**
 * @tc.name: RenderGridLayoutTest002
 * @tc.desc: Verify Grid Layout PerformLayout can calculate four children with column direction.
 * @tc.type: FUNC
 */
HWTEST_F(RenderGridLayoutTest, RenderGridLayoutTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct component and render with 4 child by column direction.
     * @tc.expected: step1. properties and children are set correctly.
     */
    std::string rowArgs = "1fr 1fr";
    std::string colArgs = "50% 50%";
    renderNode_->Update(GridLayoutTestUtils::CreateComponent(FlexDirection::COLUMN, rowArgs, colArgs));
    int32_t count = 4;
    for (int32_t i = 0; i < count; ++i) {
        RefPtr<RenderNode> item = GridLayoutTestUtils::CreateRenderItem(0, 0, 1, 1);
        item->GetChildren().front()->Attach(mockContext_);
        item->Attach(mockContext_);
        renderNode_->AddChild(item);
    }
    ASSERT_TRUE(renderNode_->GetChildren().size() == 4);

    /**
     * @tc.steps: step2. Verify that the properties are calculated correctly.
     * @tc.expected: step2. Properties and children are calculated correctly.
     */
    LayoutParam layoutParam;
    layoutParam.SetMinSize(Size(0.0, 0.0));
    layoutParam.SetMaxSize(Size(800.0, 800.0));
    renderNode_->SetLayoutParam(layoutParam);
    renderNode_->PerformLayout();
    ASSERT_TRUE(renderNode_->GetLayoutSize() == Size(800.0, 800.0));
    const std::list<RefPtr<RenderNode>>& items = renderNode_->GetChildren();
    ASSERT_TRUE(items.size() == 4);
    int32_t index = 0;
    for (const auto& item : items) {
        GridLayoutTestUtils::PrintNodeInfo(item);
        ASSERT_TRUE(item->GetPosition() == Offset(index % 2 * 400.0, index / 2 * 400.0));
        ASSERT_TRUE(item->GetLayoutSize() == Size(400.0, 400.0));
        index++;
    }
}

/**
 * @tc.name: RenderGridLayoutTest003
 * @tc.desc: Verify Grid Layout can Dynamic adjustment row count.
 * @tc.type: FUNC
 */
HWTEST_F(RenderGridLayoutTest, RenderGridLayoutTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct component and render with 4 child by row direction.
     * @tc.expected: step1. properties and children are set correctly.
     */
    std::string rowArgs = "1fr 540px";
    std::string colArgs = "540px 50%";
    renderNode_->Update(GridLayoutTestUtils::CreateComponent(FlexDirection::ROW, rowArgs, colArgs));
    int32_t count = 4;
    for (int32_t i = 0; i < count; ++i) {
        RefPtr<RenderNode> item = GridLayoutTestUtils::CreateRenderItem(0, 0, 1, 1);
        item->GetChildren().front()->Attach(mockContext_);
        item->Attach(mockContext_);
        renderNode_->AddChild(item);
    }
    ASSERT_TRUE(renderNode_->GetChildren().size() == 4);

    /**
     * @tc.steps: step2. Verify that the properties are calculated correctly.
     * @tc.expected: step2. Properties and children are calculated correctly.
     */
    renderNode_->PerformLayout();
    ASSERT_TRUE(renderNode_->GetLayoutSize() == Size(1080.0, 1080.0));
    const std::list<RefPtr<RenderNode>>& items = renderNode_->GetChildren();
    ASSERT_TRUE(items.size() == 4);
    int32_t index = 0;
    for (const auto& item : items) {
        GridLayoutTestUtils::PrintNodeInfo(item);
        ASSERT_TRUE(item->GetPosition() == Offset(index / 2 * 540.0, index % 2 * 540.0));
        ASSERT_TRUE(item->GetLayoutSize() == Size(540.0, 540.0));
        index++;
    }

    /**
     * @tc.steps: step3. adjustment row count and trigger the relayout.
     * @tc.expected: step2. Properties and children are calculated correctly.
     */
    rowArgs = "";
    colArgs = "540px 540px";
    renderNode_->Update(GridLayoutTestUtils::CreateComponent(FlexDirection::ROW, rowArgs, colArgs));
    renderNode_->PerformLayout();
    ASSERT_TRUE(renderNode_->GetLayoutSize() == Size(1080.0, 1080.0));
    index = 0;
    for (const auto& item : renderNode_->GetChildren()) {
        GridLayoutTestUtils::PrintNodeInfo(item);
        if (index < 2) {
            ASSERT_TRUE(item->GetPosition() == Offset(index % 2 * 540.0, 270.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(540.0, 540.0));
        } else {
            ASSERT_TRUE(item->GetPosition() == Offset(0.0, 0.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(0.0, 0.0));
        }
        index++;
    }
}

/**
 * @tc.name: RenderGridLayoutTest004
 * @tc.desc: Verify Grid Layout can Dynamic adjustment column count.
 * @tc.type: FUNC
 */
HWTEST_F(RenderGridLayoutTest, RenderGridLayoutTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct component and render with 9 child by column direction.
     * @tc.expected: step1. properties and children are set correctly.
     */
    std::string rowArgs = "1fr 360px 1fr";
    std::string colArgs = "360px 1fr 360px";
    renderNode_->Update(GridLayoutTestUtils::CreateComponent(FlexDirection::COLUMN, rowArgs, colArgs));
    int32_t count = 9;
    for (int32_t i = 0; i < count; ++i) {
        RefPtr<RenderNode> item = GridLayoutTestUtils::CreateRenderItem(-1, -1, 1, 1);
        item->GetChildren().front()->Attach(mockContext_);
        item->Attach(mockContext_);
        renderNode_->AddChild(item);
    }
    ASSERT_TRUE(renderNode_->GetChildren().size() == 9);

    /**
     * @tc.steps: step2. Verify that the properties are calculated correctly.
     * @tc.expected: step2. Properties and children are calculated correctly.
     */
    renderNode_->PerformLayout();
    ASSERT_TRUE(renderNode_->GetLayoutSize() == Size(1080.0, 1080.0));
    const std::list<RefPtr<RenderNode>>& items = renderNode_->GetChildren();
    ASSERT_TRUE(items.size() == 9);
    int32_t index = 0;
    for (const auto& item : items) {
        GridLayoutTestUtils::PrintNodeInfo(item);
        ASSERT_TRUE(item->GetPosition() == Offset(index % 3 * 360.0, index / 3 * 360.0));
        ASSERT_TRUE(item->GetLayoutSize() == Size(360.0, 360.0));
        index++;
    }

    /**
     * @tc.steps: step3. adjustment column count and trigger the relayout.
     * @tc.expected: step2. Properties and children are calculated correctly.
     */
    rowArgs = "1fr 1fr";
    colArgs = "216px 216px 216px 216px 216px";
    renderNode_->Update(GridLayoutTestUtils::CreateComponent(FlexDirection::ROW, rowArgs, colArgs));
    renderNode_->PerformLayout();
    ASSERT_TRUE(renderNode_->GetLayoutSize() == Size(1080.0, 1080.0));
    index = 0;
    for (const auto& item : renderNode_->GetChildren()) {
        GridLayoutTestUtils::PrintNodeInfo(item);
        ASSERT_TRUE(item->GetPosition() == Offset(index / 2 * 216.0, index % 2 * 540.0));
        ASSERT_TRUE(item->GetLayoutSize() == Size(216.0, 540.0));
        index++;
    }
}

/**
 * @tc.name: RenderGridLayoutTest005
 * @tc.desc: Verify Grid Layout can layout item with index and span when row.
 * @tc.type: FUNC
 */
HWTEST_F(RenderGridLayoutTest, RenderGridLayoutTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct component and render with 3 child by row direction.
     * @tc.expected: step1. properties and children are set correctly.
     */
    std::string rowArgs = "1fr 1fr 1fr";
    std::string colArgs = "1fr 1fr 1fr";
    renderNode_->Update(GridLayoutTestUtils::CreateComponent(FlexDirection::ROW, rowArgs, colArgs));
    RefPtr<RenderNode> item1 = GridLayoutTestUtils::CreateRenderItem(0, 0, 3, 1);
    item1->GetChildren().front()->Attach(mockContext_);
    item1->Attach(mockContext_);
    renderNode_->AddChild(item1);
    RefPtr<RenderNode> item2 = GridLayoutTestUtils::CreateRenderItem(1, 1, 2, 2);
    item2->GetChildren().front()->Attach(mockContext_);
    item2->Attach(mockContext_);
    renderNode_->AddChild(item2);
    RefPtr<RenderNode> item3 = GridLayoutTestUtils::CreateRenderItem(0, 1, 1, 2);
    item3->GetChildren().front()->Attach(mockContext_);
    item3->Attach(mockContext_);
    renderNode_->AddChild(item3);

    /**
     * @tc.steps: step2. Verify that the properties are calculated correctly.
     * @tc.expected: step2. Properties and children are calculated correctly.
     */
    renderNode_->PerformLayout();
    ASSERT_TRUE(renderNode_->GetLayoutSize() == Size(1080.0, 1080.0));
    const std::list<RefPtr<RenderNode>>& items = renderNode_->GetChildren();
    ASSERT_TRUE(items.size() == 3);
    int32_t index = 0;
    for (const auto& item : items) {
        GridLayoutTestUtils::PrintNodeInfo(item);
        if (index == 0) {
            ASSERT_TRUE(item->GetPosition() == Offset(0.0, 270.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(360.0, 540.0));
        }
        if (index == 1) {
            ASSERT_TRUE(item->GetPosition() == Offset(450.0, 450.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(540.0, 540.0));
        }
        if (index == 2) {
            ASSERT_TRUE(item->GetPosition() == Offset(450.0, 0.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(540.0, 360.0));
        }
        index++;
    }
}

/**
 * @tc.name: RenderGridLayoutTest006
 * @tc.desc: Verify Grid Layout can layout item with index and span when column.
 * @tc.type: FUNC
 */
HWTEST_F(RenderGridLayoutTest, RenderGridLayoutTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct component and render with 7 child by column direction.
     * @tc.expected: step1. properties and children are set correctly.
     */
    std::string rowArgs = "1fr 1fr 1fr 1fr";
    std::string colArgs = "1fr 1fr 1fr 1fr";
    renderNode_->Update(GridLayoutTestUtils::CreateComponent(FlexDirection::COLUMN, rowArgs, colArgs));
    RefPtr<RenderNode> item1 = GridLayoutTestUtils::CreateRenderItem(2, 0, 2, 4);
    item1->GetChildren().front()->Attach(mockContext_);
    item1->Attach(mockContext_);
    renderNode_->AddChild(item1);
    RefPtr<RenderNode> item2 = GridLayoutTestUtils::CreateRenderItem(0, 2, 4, 2);
    item2->GetChildren().front()->Attach(mockContext_);
    item2->Attach(mockContext_);
    renderNode_->AddChild(item2);
    int32_t count = 5;
    for (int32_t i = 0; i < count; ++i) {
        RefPtr<RenderNode> item = GridLayoutTestUtils::CreateRenderItem(-1, -1, 1, 1);
        item->GetChildren().front()->Attach(mockContext_);
        item->Attach(mockContext_);
        renderNode_->AddChild(item);
    }

    /**
     * @tc.steps: step2. Verify that the properties are calculated correctly.
     * @tc.expected: step2. Properties and children are calculated correctly.
     */
    renderNode_->PerformLayout();
    ASSERT_TRUE(renderNode_->GetLayoutSize() == Size(1080.0, 1080.0));
    const std::list<RefPtr<RenderNode>>& items = renderNode_->GetChildren();
    ASSERT_TRUE(items.size() == 7);
    int32_t index = 0;
    for (const auto& item : items) {
        GridLayoutTestUtils::PrintNodeInfo(item);
        if (index == 0) {
            ASSERT_TRUE(item->GetPosition() == Offset(270.0, 540.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(540.0, 540.0));
        } else if (index == 1) {
            ASSERT_TRUE(item->GetPosition() == Offset(540.0, 0.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(540.0, 540.0));
        } else if (index > 5) {
            ASSERT_TRUE(item->GetPosition() == Offset(0.0, 0.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(0.0, 0.0));
        } else {
            ASSERT_TRUE(item->GetPosition() == Offset((index - 2) % 2 * 270.0, (index - 2) / 2 * 270.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(270.0, 270.0));
        }
        index++;
    }
}

/**
 * @tc.name: RenderGridLayoutTest007
 * @tc.desc: Verify Grid Layout can layout item with index and span.
 * @tc.type: FUNC
 */
HWTEST_F(RenderGridLayoutTest, RenderGridLayoutTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct component and render with 4 child by column direction.
     * @tc.expected: step1. properties and children are set correctly.
     */
    std::string rowArgs = "50% 50%";
    std::string colArgs = "1fr 1fr 1fr";
    renderNode_->Update(GridLayoutTestUtils::CreateComponent(FlexDirection::COLUMN, rowArgs, colArgs));
    RefPtr<RenderNode> item1 = GridLayoutTestUtils::CreateRenderItem(1, 0, 1, 2);
    item1->GetChildren().front()->Attach(mockContext_);
    item1->Attach(mockContext_);
    renderNode_->AddChild(item1);
    RefPtr<RenderNode> item2 = GridLayoutTestUtils::CreateRenderItem(0, 1, 1, 2);
    item2->GetChildren().front()->Attach(mockContext_);
    item2->Attach(mockContext_);
    renderNode_->AddChild(item2);
    int32_t count = 2;
    for (int32_t i = 0; i < count; ++i) {
        RefPtr<RenderNode> item = GridLayoutTestUtils::CreateRenderItem(-1, -1, 2, 2);
        item->GetChildren().front()->Attach(mockContext_);
        item->Attach(mockContext_);
        renderNode_->AddChild(item);
    }

    /**
     * @tc.steps: step2. Verify that the properties are calculated correctly.
     * @tc.expected: step2. Properties and children are calculated correctly.
     */
    renderNode_->PerformLayout();
    ASSERT_TRUE(renderNode_->GetLayoutSize() == Size(1080.0, 1080.0));
    const std::list<RefPtr<RenderNode>>& items = renderNode_->GetChildren();
    ASSERT_TRUE(items.size() == 4);
    int32_t index = 0;
    for (const auto& item : items) {
        GridLayoutTestUtils::PrintNodeInfo(item);
        if (index == 0) {
            ASSERT_TRUE(item->GetPosition() == Offset(90.0, 540.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(540.0, 540.0));
        }
        if (index == 1) {
            ASSERT_TRUE(item->GetPosition() == Offset(450.0, 0.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(540.0, 540.0));
        }
        if (index == 2) {
            ASSERT_TRUE(item->GetPosition() == Offset(0.0, 0.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(360.0, 540.0));
        }
        if (index == 3) {
            ASSERT_TRUE(item->GetPosition() == Offset(720.0, 540.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(360.0, 540.0));
        }
        index++;
    }
}

/**
 * @tc.name: RenderGridLayoutTest008
 * @tc.desc: Verify Grid Layout can support focus obtain.
 * @tc.type: FUNC
 */
HWTEST_F(RenderGridLayoutTest, RenderGridLayoutTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct component and render with 9 child by row direction.
     * @tc.expected: step1. properties and children are set correctly.
     */
    std::string rowArgs = "1fr 1fr 1fr";
    std::string colArgs = "1fr 1fr 1fr";
    renderNode_->Update(GridLayoutTestUtils::CreateComponent(FlexDirection::ROW, rowArgs, colArgs));
    int32_t count = 9;
    for (int32_t i = 0; i < count; ++i) {
        RefPtr<RenderNode> item = GridLayoutTestUtils::CreateRenderItem(-1, -1, 1, 1);
        item->GetChildren().front()->Attach(mockContext_);
        item->Attach(mockContext_);
        renderNode_->AddChild(item);
    }
    renderNode_->PerformLayout();
    ASSERT_TRUE(renderNode_->GetLayoutSize() == Size(1080.0, 1080.0));

    /**
     * @tc.steps: step2. trigger focus event.
     * @tc.expected: step2. grid layout can obtain focus.
     */
    ASSERT_TRUE(renderNode_->RequestNextFocus(false, false) == 3); // RIGHT
    ASSERT_TRUE(renderNode_->RequestNextFocus(true, false) == 4); // DOWN
    ASSERT_TRUE(renderNode_->RequestNextFocus(false, true) == 1); // LEFT
    ASSERT_TRUE(renderNode_->RequestNextFocus(true, true) == 0); // UP
    ASSERT_TRUE(renderNode_->RequestNextFocus(false, false) == 3); // RIGHT
    ASSERT_TRUE(renderNode_->RequestNextFocus(true, false) == 4); // DOWN
    ASSERT_TRUE(renderNode_->RequestNextFocus(true, false) == 5); // DOWN
    ASSERT_TRUE(renderNode_->RequestNextFocus(true, false) == -1); // DOWN
    ASSERT_TRUE(renderNode_->RequestNextFocus(false, false) == 8); // RIGHT
    ASSERT_TRUE(renderNode_->RequestNextFocus(false, false) == -1); // RIGHT
}

/**
 * @tc.name: RenderGridLayoutTest009
 * @tc.desc: Verify Grid Layout can support focus lost.
 * @tc.type: FUNC
 */
HWTEST_F(RenderGridLayoutTest, RenderGridLayoutTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct component and render with 9 child by column direction.
     * @tc.expected: step1. properties and children are set correctly.
     */
    std::string rowArgs = "360px 360px 360px";
    std::string colArgs = "1fr 1fr 1fr";
    renderNode_->Update(GridLayoutTestUtils::CreateComponent(FlexDirection::COLUMN, rowArgs, colArgs));
    int32_t count = 9;
    for (int32_t i = 0; i < count; ++i) {
        RefPtr<RenderNode> item = GridLayoutTestUtils::CreateRenderItem(-1, -1, 1, 1);
        item->GetChildren().front()->Attach(mockContext_);
        item->Attach(mockContext_);
        renderNode_->AddChild(item);
    }
    renderNode_->PerformLayout();
    ASSERT_TRUE(renderNode_->GetLayoutSize() == Size(1080.0, 1080.0));

    /**
     * @tc.steps: step2. trigger focus event.
     * @tc.expected: step2. grid layout can obtain focus.
     */
    ASSERT_TRUE(renderNode_->RequestNextFocus(false, false) == 1); // RIGHT
    ASSERT_TRUE(renderNode_->RequestNextFocus(true, false) == 4); // DOWN
    ASSERT_TRUE(renderNode_->RequestNextFocus(false, true) == 3); // LEFT
    ASSERT_TRUE(renderNode_->RequestNextFocus(true, true) == 0); // UP
    ASSERT_TRUE(renderNode_->RequestNextFocus(false, false) == 1); // RIGHT
    ASSERT_TRUE(renderNode_->RequestNextFocus(true, false) == 4); // DOWN
    ASSERT_TRUE(renderNode_->RequestNextFocus(true, false) == 7); // DOWN
    ASSERT_TRUE(renderNode_->RequestNextFocus(true, false) == -1); // DOWN
    ASSERT_TRUE(renderNode_->RequestNextFocus(false, false) == 8); // RIGHT
    ASSERT_TRUE(renderNode_->RequestNextFocus(false, false) == -1); // RIGHT
}

/**
 * @tc.name: RenderGridLayoutTest010
 * @tc.desc: Verify Grid Layout can support focus move.
 * @tc.type: FUNC
 */
HWTEST_F(RenderGridLayoutTest, RenderGridLayoutTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct component and render with 3 child by row direction.
     * @tc.expected: step1. properties and children are set correctly.
     */
    std::string rowArgs = "1fr 1fr 1fr";
    std::string colArgs = "360px 360px 360px";
    renderNode_->Update(GridLayoutTestUtils::CreateComponent(FlexDirection::ROW, rowArgs, colArgs));
    RefPtr<RenderNode> item1 = GridLayoutTestUtils::CreateRenderItem(1, 0, 1, 3);
    item1->GetChildren().front()->Attach(mockContext_);
    item1->Attach(mockContext_);
    renderNode_->AddChild(item1);
    RefPtr<RenderNode> item2 = GridLayoutTestUtils::CreateRenderItem(0, 0, 1, 2);
    item2->GetChildren().front()->Attach(mockContext_);
    item2->Attach(mockContext_);
    renderNode_->AddChild(item2);
    RefPtr<RenderNode> item3 = GridLayoutTestUtils::CreateRenderItem(2, 1, 1, 2);
    item3->GetChildren().front()->Attach(mockContext_);
    item3->Attach(mockContext_);
    renderNode_->AddChild(item3);
    int32_t count = 2;
    for (int32_t i = 0; i < count; ++i) {
        RefPtr<RenderNode> item = GridLayoutTestUtils::CreateRenderItem(-1, -1, 2, 2);
        item->GetChildren().front()->Attach(mockContext_);
        item->Attach(mockContext_);
        renderNode_->AddChild(item);
    }
    renderNode_->PerformLayout();
    ASSERT_TRUE(renderNode_->GetLayoutSize() == Size(1080.0, 1080.0));

    /**
     * @tc.steps: step2. trigger focus event.
     * @tc.expected: step2. grid layout can obtain focus.
     */
    ASSERT_TRUE(renderNode_->RequestNextFocus(false, false) == -1); // RIGHT
    ASSERT_TRUE(renderNode_->RequestNextFocus(true, false) == 3); // DOWN
    ASSERT_TRUE(renderNode_->RequestNextFocus(false, true) == -1); // LEFT
    ASSERT_TRUE(renderNode_->RequestNextFocus(true, true) == 0); // UP
    ASSERT_TRUE(renderNode_->RequestNextFocus(true, true) == 1); // UP
    ASSERT_TRUE(renderNode_->RequestNextFocus(false, false) == 4); // RIGHT
    ASSERT_TRUE(renderNode_->RequestNextFocus(true, false) == 0); // DOWN
    ASSERT_TRUE(renderNode_->RequestNextFocus(true, false) == 2); // DOWN
    ASSERT_TRUE(renderNode_->RequestNextFocus(false, false) == -1); // RIGHT
    ASSERT_TRUE(renderNode_->RequestNextFocus(false, true) == 3); // LEFT
}

/**
 * @tc.name: RenderGridLayoutTest011
 * @tc.desc: Verify Grid Layout can support focus move with empty grid.
 * @tc.type: FUNC
 */
HWTEST_F(RenderGridLayoutTest, RenderGridLayoutTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct component and render with 3 child by row direction.
     * @tc.expected: step1. properties and children are set correctly.
     */
    std::string rowArgs = "1fr 1fr 1fr";
    std::string colArgs = "25% 25% 25% 25%";
    renderNode_->Update(GridLayoutTestUtils::CreateComponent(FlexDirection::COLUMN, rowArgs, colArgs));
    RefPtr<RenderNode> item1 = GridLayoutTestUtils::CreateRenderItem(0, 0, 1, 3);
    item1->GetChildren().front()->Attach(mockContext_);
    item1->Attach(mockContext_);
    renderNode_->AddChild(item1);
    RefPtr<RenderNode> item2 = GridLayoutTestUtils::CreateRenderItem(1, 0, 2, 1);
    item2->GetChildren().front()->Attach(mockContext_);
    item2->Attach(mockContext_);
    renderNode_->AddChild(item2);
    RefPtr<RenderNode> item3 = GridLayoutTestUtils::CreateRenderItem(1, 2, 2, 1);
    item3->GetChildren().front()->Attach(mockContext_);
    item3->Attach(mockContext_);
    renderNode_->AddChild(item3);
    RefPtr<RenderNode> item4 = GridLayoutTestUtils::CreateRenderItem(2, 1, 1, 2);
    item4->GetChildren().front()->Attach(mockContext_);
    item4->Attach(mockContext_);
    renderNode_->AddChild(item4);
    renderNode_->PerformLayout();
    ASSERT_TRUE(renderNode_->GetLayoutSize() == Size(1080.0, 1080.0));

    /**
     * @tc.steps: step2. trigger focus event.
     * @tc.expected: step2. grid layout can obtain focus.
     */
    ASSERT_TRUE(renderNode_->RequestNextFocus(false, false) == -1); // RIGHT
    ASSERT_TRUE(renderNode_->RequestNextFocus(true, false) == 1); // DOWN
    ASSERT_TRUE(renderNode_->RequestNextFocus(false, true) == -1); // LEFT
    ASSERT_TRUE(renderNode_->RequestNextFocus(true, true) == 0); // UP
    ASSERT_TRUE(renderNode_->RequestNextFocus(true, false) == 1); // DOWN
    ASSERT_TRUE(renderNode_->RequestNextFocus(false, false) == 2); // RIGHT
    ASSERT_TRUE(renderNode_->RequestNextFocus(false, false) == -1); // RIGHT
    ASSERT_TRUE(renderNode_->RequestNextFocus(true, true) == 0); // UP
}

/**
 * @tc.name: RenderGridLayoutTest012
 * @tc.desc: Verify Grid Layout PerformLayout can calculate children with gap
 * @tc.type: FUNC
 */
HWTEST_F(RenderGridLayoutTest, RenderGridLayoutTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct component and render with 4 child by row direction.
     * @tc.expected: step1. properties and children are set correctly.
     */
    std::string rowArgs = "30% 70%";
    std::string colArgs = "1fr 2fr";
    auto component = GridLayoutTestUtils::CreateComponent(FlexDirection::ROW, rowArgs, colArgs);
    auto gridcomponent = AceType::DynamicCast<GridLayoutComponent>(component);
    gridcomponent->SetRowGap(80.0_px);
    gridcomponent->SetColumnGap(60.0_px);
    renderNode_->Update(component);
    int32_t count = 4;
    for (int32_t i = 0; i < count; ++i) {
        RefPtr<RenderNode> item = GridLayoutTestUtils::CreateRenderItem(-1, -1, 1, 1);
        item->GetChildren().front()->Attach(mockContext_);
        item->Attach(mockContext_);
        renderNode_->AddChild(item);
    }
    ASSERT_TRUE(renderNode_->GetChildren().size() == 4);

    /**
     * @tc.steps: step2. Verify that the properties are calculated correctly.
     * @tc.expected: step2. Properties and children are calculated correctly.
     */
    renderNode_->PerformLayout();
    ASSERT_TRUE(renderNode_->GetLayoutSize() == Size(1080.0, 1080.0));
    const std::list<RefPtr<RenderNode>>& items = renderNode_->GetChildren();
    ASSERT_TRUE(items.size() == 4);
    int32_t index = 0;
    for (const auto& item : items) {
        GridLayoutTestUtils::PrintNodeInfo(item);
        if (index == 0) {
            ASSERT_TRUE(item->GetPosition() == Offset(0.0, 0.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(340.0, 324.0));
        }
        if (index == 1) {
            ASSERT_TRUE(item->GetPosition() == Offset(0.0, 512.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(340.0, 540.0));
        }
        if (index == 2) {
            ASSERT_TRUE(item->GetPosition() == Offset(470.0, 0.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(540.0, 324.0));
        }
        if (index == 3) {
            ASSERT_TRUE(item->GetPosition() == Offset(470.0, 512.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(540.0, 540.0));
        }
        index++;
    }
}

/**
 * @tc.name: RenderGridLayoutTest013
 * @tc.desc: Verify Grid Layout PerformLayout can calculate children with gap
 * @tc.type: FUNC
 */
HWTEST_F(RenderGridLayoutTest, RenderGridLayoutTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct component and render with 4 child by row direction.
     * @tc.expected: step1. properties and children are set correctly.
     */
    std::string rowArgs = "20% 30% 70%";
    std::string colArgs = "600px 700px";
    auto component = GridLayoutTestUtils::CreateComponent(FlexDirection::COLUMN, rowArgs, colArgs);
    auto gridcomponent = AceType::DynamicCast<GridLayoutComponent>(component);
    gridcomponent->SetRowGap(60.0_px);
    gridcomponent->SetColumnGap(80.0_px);
    renderNode_->Update(component);
    int32_t count = 6;
    for (int32_t i = 0; i < count; ++i) {
        RefPtr<RenderNode> item = GridLayoutTestUtils::CreateRenderItem(-1, -1, 1, 1);
        item->GetChildren().front()->Attach(mockContext_);
        item->Attach(mockContext_);
        renderNode_->AddChild(item);
    }
    ASSERT_TRUE(renderNode_->GetChildren().size() == 6);

    /**
     * @tc.steps: step2. Verify that the properties are calculated correctly.
     * @tc.expected: step2. Properties and children are calculated correctly.
     */
    renderNode_->PerformLayout();
    ASSERT_TRUE(renderNode_->GetLayoutSize() == Size(1080.0, 1080.0));
    const std::list<RefPtr<RenderNode>>& items = renderNode_->GetChildren();
    ASSERT_TRUE(items.size() == 6);
    int32_t index = 0;
    for (const auto& item : items) {
        GridLayoutTestUtils::PrintNodeInfo(item);
        if (index == 0) {
            ASSERT_TRUE(item->GetPosition() == Offset(30.0, 0.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(540.0, 216.0));
        }
        if (index == 1) {
            ASSERT_TRUE(item->GetPosition() == Offset(680.0, 0.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(400.0, 216.0));
        }
        if (index == 2) {
            ASSERT_TRUE(item->GetPosition() == Offset(30.0, 276.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(540.0, 324.0));
        }
        if (index == 3) {
            ASSERT_TRUE(item->GetPosition() == Offset(680.0, 276.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(400.0, 324.0));
        }
        if (index == 4) {
            ASSERT_TRUE(item->GetPosition() == Offset(30.0, 660.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(540.0, 540.0));
        }
        if (index == 5) {
            ASSERT_TRUE(item->GetPosition() == Offset(680.0, 660.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(400.0, 540.0));
        }
        index++;
    }
}

/**
 * @tc.name: RenderGridLayoutTest014
 * @tc.desc: Verify Grid Layout PerformLayout can calculate children when RTL
 * @tc.type: FUNC
 */
HWTEST_F(RenderGridLayoutTest, RenderGridLayoutTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct component and render with 4 child by RTL.
     * @tc.expected: step1. properties and children are set correctly.
     */
    std::string rowArgs = "20% 30% 70%";
    std::string colArgs = "600px 700px";
    auto component = GridLayoutTestUtils::CreateComponent(FlexDirection::COLUMN, rowArgs, colArgs);
    auto gridcomponent = AceType::DynamicCast<GridLayoutComponent>(component);
    gridcomponent->SetRowGap(60.0_px);
    gridcomponent->SetColumnGap(80.0_px);
    gridcomponent->SetRightToLeft(true);
    renderNode_->Update(component);
    int32_t count = 4;
    for (int32_t i = 0; i < count; ++i) {
        RefPtr<RenderNode> item = GridLayoutTestUtils::CreateRenderItem(-1, -1, 1, 1);
        item->GetChildren().front()->Attach(mockContext_);
        item->Attach(mockContext_);
        renderNode_->AddChild(item);
    }
    ASSERT_TRUE(renderNode_->GetChildren().size() == 4);

    /**
     * @tc.steps: step2. Verify that the properties are calculated correctly.
     * @tc.expected: step2. Properties and children are calculated correctly.
     */
    renderNode_->PerformLayout();
    ASSERT_TRUE(renderNode_->GetLayoutSize() == Size(1080.0, 1080.0));
    const std::list<RefPtr<RenderNode>>& items = renderNode_->GetChildren();
    ASSERT_TRUE(items.size() == 4);
    int32_t index = 0;
    for (const auto& item : items) {
        GridLayoutTestUtils::PrintNodeInfo(item);
        if (index == 0) {
            ASSERT_TRUE(item->GetPosition() == Offset(30.0, 0.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(540.0, 216.0));
        }
        if (index == 1) {
            ASSERT_TRUE(item->GetPosition() == Offset(680.0, 0.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(400.0, 216.0));
        }
        if (index == 2) {
            ASSERT_TRUE(item->GetPosition() == Offset(30.0, 276.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(540.0, 324.0));
        }
        if (index == 3) {
            ASSERT_TRUE(item->GetPosition() == Offset(680.0, 276.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(400.0, 324.0));
        }
        index++;
    }
}

/**
 * @tc.name: RenderGridLayoutTest015
 * @tc.desc: Verify Grid Layout can support focus move when RTL.
 * @tc.type: FUNC
 */
HWTEST_F(RenderGridLayoutTest, RenderGridLayoutTest015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct component and render with 3 child when RTL.
     * @tc.expected: step1. properties and children are set correctly.
     */
    std::string rowArgs = "1fr 1fr 1fr";
    std::string colArgs = "360px 360px 360px";
    auto component = GridLayoutTestUtils::CreateComponent(FlexDirection::ROW, rowArgs, colArgs);
    auto gridcomponent = AceType::DynamicCast<GridLayoutComponent>(component);
    gridcomponent->SetRightToLeft(true);
    renderNode_->Update(gridcomponent);
    RefPtr<RenderNode> item1 = GridLayoutTestUtils::CreateRenderItem(1, 0, 1, 3);
    item1->GetChildren().front()->Attach(mockContext_);
    item1->Attach(mockContext_);
    renderNode_->AddChild(item1);
    RefPtr<RenderNode> item2 = GridLayoutTestUtils::CreateRenderItem(0, 0, 1, 2);
    item2->GetChildren().front()->Attach(mockContext_);
    item2->Attach(mockContext_);
    renderNode_->AddChild(item2);
    RefPtr<RenderNode> item3 = GridLayoutTestUtils::CreateRenderItem(2, 1, 1, 2);
    item3->GetChildren().front()->Attach(mockContext_);
    item3->Attach(mockContext_);
    renderNode_->AddChild(item3);
    int32_t count = 2;
    for (int32_t i = 0; i < count; ++i) {
        RefPtr<RenderNode> item = GridLayoutTestUtils::CreateRenderItem(-1, -1, 2, 2);
        item->GetChildren().front()->Attach(mockContext_);
        item->Attach(mockContext_);
        renderNode_->AddChild(item);
    }
    renderNode_->PerformLayout();
    ASSERT_TRUE(renderNode_->GetLayoutSize() == Size(1080.0, 1080.0));

    /**
     * @tc.steps: step2. trigger focus event.
     * @tc.expected: step2. grid layout can obtain focus.
     */
    ASSERT_TRUE(renderNode_->RequestNextFocus(false, true) == -1); // LEFT
    ASSERT_TRUE(renderNode_->RequestNextFocus(true, false) == 3); // DOWN
    ASSERT_TRUE(renderNode_->RequestNextFocus(false, false) == 2); // RIGHT
    ASSERT_TRUE(renderNode_->RequestNextFocus(true, true) == 0); // UP
    ASSERT_TRUE(renderNode_->RequestNextFocus(true, true) == 1); // UP
    ASSERT_TRUE(renderNode_->RequestNextFocus(false, true) == -1); // LEFT
    ASSERT_TRUE(renderNode_->RequestNextFocus(true, false) == 0); // DOWN
    ASSERT_TRUE(renderNode_->RequestNextFocus(true, false) == 2); // DOWN
    ASSERT_TRUE(renderNode_->RequestNextFocus(false, true) == 3); // LEFT
    ASSERT_TRUE(renderNode_->RequestNextFocus(false, false) == 2); // RIGHT
}

/**
 * @tc.name: RenderGridLayoutTest016
 * @tc.desc: Verify Grid Layout PerformLayout can calculate children with invalid index.
 * @tc.type: FUNC
 */
HWTEST_F(RenderGridLayoutTest, RenderGridLayoutTest016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct component and render with two children with invalid index.
     * @tc.expected: step1. properties and children are set correctly.
     */
    std::string rowArgs = "50% 50%";
    std::string colArgs = "600px 700px";
    auto component = GridLayoutTestUtils::CreateComponent(FlexDirection::COLUMN, rowArgs, colArgs);
    auto gridcomponent = AceType::DynamicCast<GridLayoutComponent>(component);
    gridcomponent->SetRowGap(60.0_px);
    gridcomponent->SetColumnGap(80.0_px);
    renderNode_->Update(component);
    RefPtr<RenderNode> item1 = GridLayoutTestUtils::CreateRenderItem(2, 0, 1, 1);
    item1->GetChildren().front()->Attach(mockContext_);
    item1->Attach(mockContext_);
    renderNode_->AddChild(item1);
    RefPtr<RenderNode> item2 = GridLayoutTestUtils::CreateRenderItem(0, 3, 1, 1);
    item2->GetChildren().front()->Attach(mockContext_);
    item2->Attach(mockContext_);
    renderNode_->AddChild(item2);
    ASSERT_TRUE(renderNode_->GetChildren().size() == 2);

    /**
     * @tc.steps: step2. Verify that the properties are calculated correctly.
     * @tc.expected: step2. Properties and children are calculated correctly.
     */
    renderNode_->PerformLayout();
    ASSERT_TRUE(renderNode_->GetLayoutSize() == Size(1080.0, 1080.0));
    const std::list<RefPtr<RenderNode>>& items = renderNode_->GetChildren();
    ASSERT_TRUE(items.size() == 2);
    int32_t index = 0;
    for (const auto& item : items) {
        GridLayoutTestUtils::PrintNodeInfo(item);
        if (index == 0) {
            ASSERT_TRUE(item->GetPosition() == Offset(30.0, 0.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(540.0, 540.0));
        }
        if (index == 1) {
            ASSERT_TRUE(item->GetPosition() == Offset(680.0, 0.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(400.0, 540.0));
        }
        index++;
    }
}

/**
 * @tc.name: RenderGridLayoutTest017
 * @tc.desc: Verify Grid Layout can layout items with auto params.
 * @tc.type: FUNC
 */
HWTEST_F(RenderGridLayoutTest, RenderGridLayoutTest017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct component and render with 3 child by column direction.
     * @tc.expected: step1. properties and children are set correctly.
     */
    std::string colArgs = "1fr auto 1fr";
    renderNode_->Update(GridLayoutTestUtils::CreateComponent(FlexDirection::COLUMN, "", colArgs));
    RefPtr<RenderNode> item1 = GridLayoutTestUtils::CreateRenderItem(-1, -1, 1, 1);
    item1->GetChildren().front()->Attach(mockContext_);
    item1->Attach(mockContext_);
    renderNode_->AddChild(item1);
    RefPtr<RenderNode> item2 = GridLayoutTestUtils::CreateRenderItem(-1, -1, 1, 1);
    item2->GetChildren().front()->Attach(mockContext_);
    item2->Attach(mockContext_);
    renderNode_->AddChild(item2);
    RefPtr<RenderNode> item3 = GridLayoutTestUtils::CreateRenderItem(-1, -1, 1, 1);
    item3->GetChildren().front()->Attach(mockContext_);
    item3->Attach(mockContext_);
    renderNode_->AddChild(item3);

    /**
     * @tc.steps: step2. Verify that the properties are calculated correctly.
     * @tc.expected: step2. Properties and children are calculated correctly.
     */
    renderNode_->PerformLayout();
    ASSERT_TRUE(renderNode_->GetLayoutSize() == Size(1080.0, 1080.0));
    const std::list<RefPtr<RenderNode>>& items = renderNode_->GetChildren();
    ASSERT_TRUE(items.size() == 3);
    int32_t index = 0;
    for (const auto& item : items) {
        GridLayoutTestUtils::PrintNodeInfo(item);
        if (index == 0) {
            ASSERT_TRUE(item->GetPosition() == Offset(0.0, 270.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(540.0, 540.0));
        }
        if (index == 1) {
            ASSERT_TRUE(item->GetPosition() == Offset(540.0, 270.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(0.0, 540.0));
        }
        if (index == 2) {
            ASSERT_TRUE(item->GetPosition() == Offset(540.0, 270.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(540.0, 540.0));
        }
        index++;
    }
}

/**
 * @tc.name: RenderGridLayoutTest018
 * @tc.desc: Verify Grid Layout can layout items with auto params.
 * @tc.type: FUNC
 */
HWTEST_F(RenderGridLayoutTest, RenderGridLayoutTest018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct component and render with 9 child by row direction.
     * @tc.expected: step1. properties and children are set correctly.
     */
    std::string rowArgs = "auto 1fr 200px";
    std::string colArgs = "270px 50% auto";
    renderNode_->Update(GridLayoutTestUtils::CreateComponent(FlexDirection::ROW, rowArgs, colArgs));
    int32_t count = 9;
    for (int32_t i = 0; i < count; ++i) {
        RefPtr<RenderNode> item = GridLayoutTestUtils::CreateRenderItem(-1, -1, 1, 1);
        item->GetChildren().front()->Attach(mockContext_);
        item->Attach(mockContext_);
        renderNode_->AddChild(item);
    }
    ASSERT_TRUE(renderNode_->GetChildren().size() == 9);

    /**
     * @tc.steps: step2. Verify that the properties are calculated correctly.
     * @tc.expected: step2. Properties and children are calculated correctly.
     */
    renderNode_->PerformLayout();
    ASSERT_TRUE(renderNode_->GetLayoutSize() == Size(1080.0, 1080.0));
    const std::list<RefPtr<RenderNode>>& items = renderNode_->GetChildren();
    ASSERT_TRUE(items.size() == 9);
    int32_t index = 0;
    for (const auto& item : items) {
        GridLayoutTestUtils::PrintNodeInfo(item);
        if (index == 0) {
            ASSERT_TRUE(item->GetPosition() == Offset(0.0, 0.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(270.0, 540.0));
        }
        if (index == 3) {
            ASSERT_TRUE(item->GetPosition() == Offset(270.0, 0.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(540.0, 540.0));
        }
        if (index == 6) {
            ASSERT_TRUE(item->GetPosition() == Offset(810.0, 0.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(270.0, 540.0));
        }
        if (index == 1) {
            ASSERT_TRUE(item->GetPosition() == Offset(0.0, 540.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(270.0, 340.0));
        }
        if (index == 4) {
            ASSERT_TRUE(item->GetPosition() == Offset(270.0, 540.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(540.0, 340.0));
        }
        if (index == 7) {
            ASSERT_TRUE(item->GetPosition() == Offset(810.0, 540.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(270.0, 340.0));
        }
        if (index == 2) {
            ASSERT_TRUE(item->GetPosition() == Offset(0.0, 880.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(270.0, 200.0));
        }
        if (index == 5) {
            ASSERT_TRUE(item->GetPosition() == Offset(270.0, 880.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(540.0, 200.0));
        }
        if (index == 8) {
            ASSERT_TRUE(item->GetPosition() == Offset(810.0, 880.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(270.0, 200.0));
        }
        index++;
    }
}

/**
 * @tc.name: RenderGridLayoutTest019
 * @tc.desc: Verify Grid Layout is useful for auto-fill in px mode.
 * @tc.type: FUNC
 */
HWTEST_F(RenderGridLayoutTest, RenderGridLayoutTest019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct component and render with 9 child by column direction.
     * @tc.expected: step1. properties and children are set correctly.
     */
    std::string rowArgs = "repeat(auto-fill, 360px 180px)";
    std::string colArgs = "360px 1fr 360px";
    renderNode_->Update(GridLayoutTestUtils::CreateComponent(FlexDirection::ROW, rowArgs, colArgs));
    int32_t count = 9;
    for (int32_t i = 0; i < count; ++i) {
        RefPtr<RenderNode> item = GridLayoutTestUtils::CreateRenderItem(-1, -1, 1, 1);
        item->GetChildren().front()->Attach(mockContext_);
        item->Attach(mockContext_);
        renderNode_->AddChild(item);
    }
    ASSERT_TRUE(renderNode_->GetChildren().size() == 9);

    /**
     * @tc.steps: step2. Verify that the properties are calculated correctly.
     * @tc.expected: step2. Properties and children are calculated correctly.
     */
    renderNode_->PerformLayout();
    ASSERT_TRUE(renderNode_->GetLayoutSize() == Size(1080.0, 1080.0));
    const std::list<RefPtr<RenderNode>>& items = renderNode_->GetChildren();
    ASSERT_TRUE(items.size() == 9);
    int32_t index = 0;
    for (const auto& item : items) {
        GridLayoutTestUtils::PrintNodeInfo(item);
        if (index == 0) {
            ASSERT_TRUE(item->GetPosition() == Offset(0.0, 0.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(360.0, 360.0));
        }
        if (index == 1) {
            ASSERT_TRUE(item->GetPosition() == Offset(0.0, 360.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(360.0, 180.0));
        }
        if (index == 2) {
            ASSERT_TRUE(item->GetPosition() == Offset(0.0, 540.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(360.0, 360.0));
        }
        if (index == 3) {
            ASSERT_TRUE(item->GetPosition() == Offset(0.0, 900.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(360.0, 180.0));
        }
        if (index == 4) {
            ASSERT_TRUE(item->GetPosition() == Offset(360.0, 0.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(360.0, 360.0));
        }
        if (index == 5) {
            ASSERT_TRUE(item->GetPosition() == Offset(360.0, 360.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(360.0, 180.0));
        }
        if (index == 6) {
            ASSERT_TRUE(item->GetPosition() == Offset(360.0, 540.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(360.0, 360.0));
        }
        if (index == 7) {
            ASSERT_TRUE(item->GetPosition() == Offset(360.0, 900.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(360.0, 180.0));
        }
        if (index == 8) {
            ASSERT_TRUE(item->GetPosition() == Offset(720.0, 0.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(360.0, 360.0));
        }
        index++;
    }
}

/**
 * @tc.name: RenderGridLayoutTest020
 * @tc.desc: Verify Grid Layout is useful for auto-fill in percent mode.
 * @tc.type: FUNC
 */
HWTEST_F(RenderGridLayoutTest, RenderGridLayoutTest020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct component and render with 9 child by column direction.
     * @tc.expected: step1. properties and children are set correctly.
     */
    std::string rowArgs = "repeat(auto-fill, 30% 25%)";
    std::string colArgs = "repeat(auto-fill, 10% 30%)";
    renderNode_->Update(GridLayoutTestUtils::CreateComponent(FlexDirection::COLUMN, rowArgs, colArgs));
    int32_t count = 9;
    for (int32_t i = 0; i < count; ++i) {
        RefPtr<RenderNode> item = GridLayoutTestUtils::CreateRenderItem(-1, -1, 1, 1);
        item->GetChildren().front()->Attach(mockContext_);
        item->Attach(mockContext_);
        renderNode_->AddChild(item);
    }
    ASSERT_TRUE(renderNode_->GetChildren().size() == 9);

    /**
     * @tc.steps: step2. Verify that the properties are calculated correctly.
     * @tc.expected: step2. Properties and children are calculated correctly.
     */
    LayoutParam layoutParam;
    layoutParam.SetMinSize(Size(0.0, 0.0));
    layoutParam.SetMaxSize(Size(1080.0, 1080.0));
    renderNode_->SetLayoutParam(layoutParam);
    renderNode_->PerformLayout();
    ASSERT_TRUE(renderNode_->GetLayoutSize() == Size(1080.0, 1080.0));
    const std::list<RefPtr<RenderNode>>& items = renderNode_->GetChildren();
    ASSERT_TRUE(items.size() == 9);
    int32_t index = 0;
    for (const auto& item : items) {
        GridLayoutTestUtils::PrintNodeInfo(item);
        if (index == 0) {
            ASSERT_TRUE(item->GetPosition() == Offset(0.0, 0.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(108.0, 324.0));
        }
        if (index == 1) {
            ASSERT_TRUE(item->GetPosition() == Offset(108.0, 0.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(324.0, 324.0));
        }
        if (index == 2) {
            ASSERT_TRUE(item->GetPosition() == Offset(432.0, 0.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(108.0, 324.0));
        }
        if (index == 3) {
            ASSERT_TRUE(item->GetPosition() == Offset(540.0, 0.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(324.0, 324.0));
        }
        if (index == 4) {
            ASSERT_TRUE(item->GetPosition() == Offset(0.0, 324.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(108.0, 270.0));
        }
        if (index == 5) {
            ASSERT_TRUE(item->GetPosition() == Offset(108.0, 324.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(324.0, 270.0));
        }
        if (index == 6) {
            ASSERT_TRUE(item->GetPosition() == Offset(432.0, 324.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(108.0, 270.0));
        }
        if (index == 7) {
            ASSERT_TRUE(item->GetPosition() == Offset(540.0, 324.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(324.0, 270.0));
        }
        if (index == 8) {
            ASSERT_TRUE(item->GetPosition() == Offset(0.0, 0.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(0.0, 0.0));
        }
        index++;
    }
}

/**
 * @tc.name: RenderGridLayoutTest021
 * @tc.desc: Verify Grid Layout is useful for auto-fill in percent mode when percent and px is mixed.
 * @tc.type: FUNC
 */
HWTEST_F(RenderGridLayoutTest, RenderGridLayoutTest021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct component and render with 7 child by column direction.
     * @tc.expected: step1. properties and children are set correctly.
     */
    std::string rowArgs = "repeat(auto-fill, 30% 200px)";
    std::string colArgs = "repeat(auto-fill, 400px 10%)";
    renderNode_->Update(GridLayoutTestUtils::CreateComponent(FlexDirection::ROW, rowArgs, colArgs));
    int32_t count = 7;
    for (int32_t i = 0; i < count; ++i) {
        RefPtr<RenderNode> item = GridLayoutTestUtils::CreateRenderItem(-1, -1, 1, 1);
        item->GetChildren().front()->Attach(mockContext_);
        item->Attach(mockContext_);
        renderNode_->AddChild(item);
    }
    ASSERT_TRUE(renderNode_->GetChildren().size() == 7);

    /**
     * @tc.steps: step2. Verify that the properties are calculated correctly.
     * @tc.expected: step2. Properties and children are calculated correctly.
     */
    LayoutParam layoutParam;
    layoutParam.SetMinSize(Size(0.0, 0.0));
    layoutParam.SetMaxSize(Size(1080.0, 1080.0));
    renderNode_->SetLayoutParam(layoutParam);
    renderNode_->PerformLayout();
    ASSERT_TRUE(renderNode_->GetLayoutSize() == Size(1080.0, 1080.0));
    const std::list<RefPtr<RenderNode>>& items = renderNode_->GetChildren();
    ASSERT_TRUE(items.size() == 7);
    int32_t index = 0;
    for (const auto& item : items) {
        GridLayoutTestUtils::PrintNodeInfo(item);
        if (index == 0) {
            ASSERT_TRUE(item->GetPosition() == Offset(0.0, 0.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(400.0, 324.0));
        }
        if (index == 1) {
            ASSERT_TRUE(item->GetPosition() == Offset(0.0, 324.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(400.0, 200.0));
        }
        if (index == 2) {
            ASSERT_TRUE(item->GetPosition() == Offset(0.0, 524.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(400.0, 324.0));
        }
        if (index == 3) {
            ASSERT_TRUE(item->GetPosition() == Offset(0.0, 848.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(400.0, 200.0));
        }
        if (index == 4) {
            ASSERT_TRUE(item->GetPosition() == Offset(400.0, 0.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(108.0, 324.0));
        }
        if (index == 5) {
            ASSERT_TRUE(item->GetPosition() == Offset(400.0, 324.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(108.0, 200.0));
        }
        if (index == 6) {
            ASSERT_TRUE(item->GetPosition() == Offset(400.0, 524.0));
            ASSERT_TRUE(item->GetLayoutSize() == Size(108.0, 324.0));
        }
        index++;
    }
}

/**
 * @tc.name: RenderGridLayoutTest022
 * @tc.desc: Verify the function that trim the space(left, right) of input string.
 * @tc.type: FUNC
 * @tc.require: issueI5NC8W
 */
HWTEST_F(RenderGridLayoutTest, RenderGridLayoutTest022, TestSize.Level1)
{
// TrimTemplate(std::string& str)
    std::string strAllSpace = "   ";
    std::string strLeftSpace = "   abc";
    std::string strRightSpace = "abc   ";
    std::string strMidRightSpace = "a bc   ";
    std::string strLeftMidSpace = "   a bc";
    std::string strLeftMidRightSpace = "   a bc  ";

    std::string strExpect = "abc";
    std::string strMidExpect = "a bc";

    ASSERT_TRUE(renderNode_->TrimTemplate(strAllSpace) == "");
    ASSERT_TRUE(renderNode_->TrimTemplate(strLeftSpace) == strExpect);
    ASSERT_TRUE(renderNode_->TrimTemplate(strRightSpace) == strExpect);
    ASSERT_TRUE(renderNode_->TrimTemplate(strMidRightSpace) == strMidExpect);
    ASSERT_TRUE(renderNode_->TrimTemplate(strLeftMidSpace) == strMidExpect);
    ASSERT_TRUE(renderNode_->TrimTemplate(strLeftMidRightSpace) == strMidExpect);
}

// SplitTemplate
/**
 * @tc.name: RenderGridLayoutTest023
 * @tc.desc: Verify the function that split the string and reture the result.
 * @tc.type: FUNC
 * @tc.require: issueI5NC8W
 */
HWTEST_F(RenderGridLayoutTest, RenderGridLayoutTest023, TestSize.Level1)
{
    std::string number = "10";
    std::vector<RenderGridLayout::Value> out;
    std::string numWithPX = "10px";
    std::string numWithVP = "10px";
    std::string numWithPer = "10%";
    std::string numWithPXLeftSpace = " 10px";
    std::string numWithPXMidSpace = "10 px";
    std::string numWithMultiPXVPPer = "10px 10vp 10%";

    EXPECT_EQ(renderNode_->SplitTemplate(numWithPX, out, false), true);
    EXPECT_EQ(out.size(), 1);
    EXPECT_TRUE(out[0].isRepeat == false);
    out.clear();

    EXPECT_EQ(renderNode_->SplitTemplate(numWithVP, out, false), true);
    EXPECT_EQ(out.size(), 1);
    EXPECT_TRUE(out[0].isRepeat == false);
    out.clear();

    EXPECT_EQ(renderNode_->SplitTemplate(numWithPer, out, false), true);
    EXPECT_EQ(out.size(), 1);
    EXPECT_TRUE(out[0].isRepeat == false);
    out.clear();

    EXPECT_EQ(renderNode_->SplitTemplate(numWithPXLeftSpace, out, false), true);
    EXPECT_EQ(out.size(), 1);
    EXPECT_TRUE(out[0].isRepeat == false);
    out.clear();

    EXPECT_EQ(renderNode_->SplitTemplate(numWithPXMidSpace, out, false), false);
    EXPECT_EQ(out.size(), 1);
    EXPECT_EQ(out[0].isRepeat, false);
    out.clear();

    EXPECT_EQ(renderNode_->SplitTemplate(numWithMultiPXVPPer, out, false), true);
    EXPECT_EQ(out.size(), 3);
    EXPECT_TRUE(out[0].isRepeat == false);
    out.clear();

    EXPECT_EQ(renderNode_->SplitTemplate(number, out, false), true);
    EXPECT_EQ(out.size(), 1);
    EXPECT_TRUE(out[0].isRepeat == false);
    out.clear();
}

/**
 * @tc.name: RenderGridLayoutTest024
 * @tc.desc: Verify the function that verify the validity.
 * @tc.type: FUNC
 * @tc.require: issueI5NC8W
 */
HWTEST_F(RenderGridLayoutTest, RenderGridLayoutTest024, TestSize.Level1)
{
    std::string strEmpty = "";
    std::string strSpace = " ";
    std::string strPrefixError = " 20pxrepeat(auto-fill, 10px)";
    std::string strRepeat = " 20px repeat(auto-fill, 10px)";
    std::vector<double> out;
    std::vector<RenderGridLayout::Value> result;

    EXPECT_FALSE(renderNode_->CheckAutoFillParameter(strEmpty, 0, out, result));
    EXPECT_TRUE(out.size() == 0);
    EXPECT_TRUE(result.size() == 0);

    EXPECT_FALSE(renderNode_->CheckAutoFillParameter(strPrefixError, 100, out, result));
    EXPECT_TRUE(out[0] == 100);
    EXPECT_TRUE(out.size() == 1);
    EXPECT_TRUE(result.size() == 0);

    EXPECT_FALSE(renderNode_->CheckAutoFillParameter(strSpace, 100, out, result));
    EXPECT_TRUE(out.size() == 1);
    EXPECT_TRUE(result.size() == 0);

    EXPECT_TRUE(renderNode_->CheckAutoFillParameter(strRepeat, 100, out, result));
    EXPECT_TRUE(out.size() == 0);
    EXPECT_TRUE(result.size() == 2);
}

/**
 * @tc.name: RenderGridLayoutTest025
 * @tc.desc: Verify the function that parse the unit value of auto-fill.
 * @tc.type: FUNC
 * @tc.require: issueI5NC8W
 */
HWTEST_F(RenderGridLayoutTest, RenderGridLayoutTest025, TestSize.Level1)
{
    RenderGridLayout::Value valueNth = {"", -1};
    RenderGridLayout::Value valuePX = {"10px", true};
    RenderGridLayout::Value valuePXE = {"px10", true};
    RenderGridLayout::Value valuePer = {"10%", false};
    RenderGridLayout::Value valuePerE = {"%10", false};
    RenderGridLayout::Value valueVP = {"10vp", true};
    RenderGridLayout::Value valueVPE = {"vp10", true};
    LayoutParam layoutParam;

    EXPECT_EQ(renderNode_->ParseUnit(valueNth), 0.0);
    EXPECT_EQ(renderNode_->ParseUnit(valuePX), 10.0);
    EXPECT_EQ(renderNode_->ParseUnit(valuePXE), 0.0);

    RefPtr<RenderBox> renderBox = GridLayoutTestUtils::CreateRenderBox(BOXDEFAULT, BOXDEFAULT);
    layoutParam.SetMaxSize(Size(BOXDEFAULT, BOXDEFAULT));
    renderBox->SetLayoutParam(layoutParam);
    renderBox->AddChild(renderNode_);

    EXPECT_EQ(renderNode_->ParseUnit(valuePer), 10.0);
    EXPECT_EQ(renderNode_->ParseUnit(valuePerE), 0.0);
    EXPECT_EQ(renderNode_->ParseUnit(valueVP), 10.0);
    EXPECT_EQ(renderNode_->ParseUnit(valueVPE), 0.0);
}

// ConvertVirtualSize
/**
 * @tc.name: RenderGridLayoutTest026
 * @tc.desc: Verify the function that parse the unit value of auto-fill.
 * @tc.type: FUNC
 * @tc.require: issueI5NC8W
 */
HWTEST_F(RenderGridLayoutTest, RenderGridLayoutTest026, TestSize.Level1)
{
    std::string valueNth = "";
    std::string valuePX = "10px";
    std::string valuePXE = "px10";
    std::string valuePer = "10%";
    std::string valuePerE = "%10";
    std::string valueVP = "10vp";
    std::string valueVPE = "vp10";
    LayoutParam layoutParam;

    EXPECT_EQ(renderNode_->ConvertVirtualSize(valueNth, DimensionUnit::PX), 0.0);
    EXPECT_EQ(renderNode_->ConvertVirtualSize(valuePX, DimensionUnit::PX), 10.0);
    EXPECT_EQ(renderNode_->ConvertVirtualSize(valuePXE, DimensionUnit::PX), 0.0);

    RefPtr<RenderBox> renderBox = GridLayoutTestUtils::CreateRenderBox(BOXDEFAULT, BOXDEFAULT);
    layoutParam.SetMaxSize(Size(BOXDEFAULT, BOXDEFAULT));
    renderBox->SetLayoutParam(layoutParam);
    renderBox->AddChild(renderNode_);

    EXPECT_EQ(renderNode_->ConvertVirtualSize(valuePer, DimensionUnit::PERCENT), 10.0);
    EXPECT_EQ(renderNode_->ConvertVirtualSize(valuePerE, DimensionUnit::PERCENT), 0.0);
    EXPECT_EQ(renderNode_->ConvertVirtualSize(valueVP, DimensionUnit::VP), 10.0);
    EXPECT_EQ(renderNode_->ConvertVirtualSize(valueVPE, DimensionUnit::VP), 0.0);
    EXPECT_EQ(renderNode_->ConvertVirtualSize("10.0", DimensionUnit::CALC), 0.0);
}

// CheckRepeatAndSplitString
/**
 * @tc.name: RenderGridLayoutTest027
 * @tc.desc: Verify the function that parse the unit value of auto-fill.
 * @tc.type: FUNC
 * @tc.require: issueI5NC8W
 */
HWTEST_F(RenderGridLayoutTest, RenderGridLayoutTest027, TestSize.Level1)
{
    std::vector<std::string> vec;
    std::vector<RenderGridLayout::Value> result;
    std::string value;

    value = "";
    EXPECT_EQ(renderNode_->CheckRepeatAndSplitString(vec, value, result), false);
    vec.clear();
    result.clear();

    value = "repeat(auto-fill, 10px)";
    vec.push_back("");
    EXPECT_EQ(renderNode_->CheckRepeatAndSplitString(vec, value, result), true);
    EXPECT_EQ(result.size(), 1);
    if (result.size() == 1) {
        EXPECT_TRUE(result[0].str == "10px");
    }
    vec.clear();
    result.clear();

    value = "repeat(auto-fill, 10px)";
    vec.push_back("20px");
    EXPECT_EQ(renderNode_->CheckRepeatAndSplitString(vec, value, result), true);
    EXPECT_EQ(result.size(), 2);
    if (result.size() == 2) {
        EXPECT_TRUE(result[0].str == "20px");
        EXPECT_TRUE(result[1].str == "10px");
    }
    vec.clear();
    result.clear();

    value = "repeat(auto-fill, 10px)";
    vec.push_back(" ");
    EXPECT_EQ(renderNode_->CheckRepeatAndSplitString(vec, value, result), true);
    vec.clear();
    result.clear();
}
// GetRepeat
/**
 * @tc.name: RenderGridLayoutTest028
 * @tc.desc: Verify the function that parse the unit value of auto-fill.
 * @tc.type: FUNC
 * @tc.require: issueI5NC8W
 */
HWTEST_F(RenderGridLayoutTest, RenderGridLayoutTest028, TestSize.Level1)
{
    std::string param = "repeat(auto-fill, 100px)";
    std::string retVal = param;
    EXPECT_TRUE(renderNode_->GetRepeat(param) == retVal);

    param = "repeat(2, 100px 200px) repeat(auto-fill, 100px)";
    EXPECT_TRUE(renderNode_->GetRepeat(param) == retVal);

    param = "repeat(2, 100px 200px)";
    EXPECT_TRUE(renderNode_->GetRepeat(param) == "");
}

// ParseArgsWithAutoFill
/**
 * @tc.name: RenderGridLayoutTest029
 * @tc.desc: Verify the function that parse the unit value of auto-fill.
 * @tc.type: FUNC
 * @tc.require: issueI5NC8W
 */
HWTEST_F(RenderGridLayoutTest, RenderGridLayoutTest029, TestSize.Level1)
{
    std::vector<double> retVal;
    std::string param = "";

    param = "1fr 1fr";
    retVal = renderNode_->ParseArgsWithAutoFill(param, 100, 0);
    EXPECT_EQ(retVal.size(), 2);
    if (retVal.size() == 2) {
        EXPECT_EQ(retVal[0], 50.0);
        EXPECT_EQ(retVal[1], 50.0);
    }

    param = "20pxrepeat(auto-fill, 50px)";
    retVal = renderNode_->ParseArgsWithAutoFill(param, 100, 0);
    EXPECT_EQ(retVal.size(), 1);
    if (retVal.size() == 1) {
        EXPECT_EQ(retVal[0], 100.0);
    }

    param = "20px repeat(auto-fill, 50px)";
    retVal = renderNode_->ParseArgsWithAutoFill(param, 100, 0);
    EXPECT_EQ(retVal.size(), 2);
    if (retVal.size() == 2) {
        EXPECT_EQ(retVal[0], 20.0);
        EXPECT_EQ(retVal[1], 50.0);
    }

    param = "20px repeat(auto-fill, 30px)";
    retVal = renderNode_->ParseArgsWithAutoFill(param, 100, 0);
    EXPECT_EQ(retVal.size(), 3);
    if (retVal.size() == 3) {
        EXPECT_EQ(retVal[0], 20.0);
        EXPECT_EQ(retVal[1], 30.0);
        EXPECT_EQ(retVal[2], 30.0);
    }

    param = "20px repeat(auto-fill, 15px 10px)";
    retVal = renderNode_->ParseArgsWithAutoFill(param, 100, 0);
    EXPECT_EQ(retVal.size(), 7);
    if (retVal.size() == 7) {
        EXPECT_EQ(retVal[0], 20.0);
        EXPECT_EQ(retVal[1], 15.0);
        EXPECT_EQ(retVal[2], 10.0);
        EXPECT_EQ(retVal[3], 15.0);
        EXPECT_EQ(retVal[4], 10.0);
        EXPECT_EQ(retVal[5], 15.0);
        EXPECT_EQ(retVal[6], 10.0);
    }

    param = "20px repeat(auto-fill, 5px 10px) 40px";
    retVal = renderNode_->ParseArgsWithAutoFill(param, 100, 0);
    EXPECT_EQ(retVal.size(), 6);
    if (retVal.size() == 6) {
        EXPECT_EQ(retVal[0], 20.0);
        EXPECT_EQ(retVal[1], 5.0);
        EXPECT_EQ(retVal[2], 10.0);
        EXPECT_EQ(retVal[3], 5.0);
        EXPECT_EQ(retVal[4], 10.0);
        EXPECT_EQ(retVal[5], 40.0);
    }

    param = "20px repeat(auto-fill)";
    retVal = renderNode_->ParseArgsWithAutoFill(param, 100, 0);
    EXPECT_EQ(retVal.size(), 1);
    if (retVal.size() == 1) {
        EXPECT_EQ(retVal[0], 100.0);
    }
}

 * @tc.name: RenderGridLayoutTestRTL001
 * @tc.desc: Test RTL of layout component
 * @tc.type: FUNC
 * @tc.require: issueI5NC7M
 */
HWTEST_F(RenderGridLayoutTest, RenderGridLayoutTestRTL001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RenderGridLayoutTest rtl001 start";

    /**
     * @tc.steps: step1. construct GridLayoutComponent and set direction.
     * @tc.expected: step1. The text direction is correct.
     */
    std::string rowArgs = "1fr 540px";
    std::string colArgs = "540px 50%";
    std::list<RefPtr<Component>> children;
    RefPtr<GridLayoutComponent> component = AceType::MakeRefPtr<GridLayoutComponent>(children);
    component->SetTextDirection(TextDirection::RTL);
    renderNode_->Update(component);
    EXPECT_EQ(component->GetTextDirection(), TextDirection::RTL);

    GTEST_LOG_(INFO) << "RenderGridLayoutTest rtl001 stop";
}
} // namespace OHOS::Ace
