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

#include "gtest/gtest.h"

#include "core/components/grid_layout/grid_layout_component.h"
#include "core/components/grid_layout/render_grid_layout_item.h"
#include "core/components/test/unittest/grid/grid_test_utils.h"
#include "core/components/test/unittest/mock/mock_render_common.h"
#include "core/components_v2/grid/render_grid_scroll.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::V2 {
namespace {
constexpr double DIM_SIZE_VALUE_TEST = 1080.0;
} // namespace

class MockRenderGridLayoutItem final : public RenderGridLayoutItem {
    DECLARE_ACE_TYPE(MockRenderGridLayoutItem, RenderGridLayoutItem);

public:
    MockRenderGridLayoutItem() = default;
    ~MockRenderGridLayoutItem() override = default;
};

class MockRenderGridScroll final : public RenderGridScroll {
    DECLARE_ACE_TYPE(MockRenderGridScroll, RenderGridScroll);

public:
    MockRenderGridScroll() = default;
    ~MockRenderGridScroll() override = default;

    enum class SCROLLABLE : uint32_t {
        NO_SCROLL = 0,
        VERTICAL,
        HORIZONTAL,
    };

    bool UpdateScrollPositionTest(double offset)
    {
        return UpdateScrollPosition(offset, SCROLL_FROM_UPDATE);
    }

    void SetChildPositionTest(const RefPtr<RenderNode>& child)
    {
        SetChildPosition(child, 0, 0, 0, 0);
    }

    void InitScrollBarTest()
    {
        InitScrollBar();
    }

    void SetDirection(bool rightToLeft)
    {
        rightToLeft_ = rightToLeft;
    }

    void SetUseScrollable(SCROLLABLE useScrollable)
    {
        useScrollable_ = (RenderGridScroll::SCROLLABLE)useScrollable;
    }

    void SetReachHead(bool reachHead)
    {
        reachHead_ = reachHead;
    }

    void SetReachTail(bool reachTail)
    {
        reachTail_ = reachTail;
    }

    void SetVertical(bool isVertical)
    {
        isVertical_ = isVertical;
    }

    bool GetDirection()
    {
        return rightToLeft_;
    }
};

class RenderGridTestV2 : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;

    RefPtr<PipelineContext> mockContext_;
    RefPtr<MockRenderGridScroll> renderGridScroll_;
};

void RenderGridTestV2::SetUpTestCase() {}
void RenderGridTestV2::TearDownTestCase() {}

void RenderGridTestV2::SetUp()
{
    mockContext_ = MockRenderCommon::GetMockContext();
    renderGridScroll_ = AceType::MakeRefPtr<MockRenderGridScroll>();
    renderGridScroll_->Attach(mockContext_);
}

void RenderGridTestV2::TearDown()
{
    mockContext_ = nullptr;
    renderGridScroll_ = nullptr;
}

/**
 * @tc.name: RenderGridRTL001
 * @tc.desc: Test whether function UpdateScrollPosition performs the expected action by
 * setting member variables to different values.
 * @tc.type: FUNC
 * @tc.require: issueI5NC7M
 */
HWTEST_F(RenderGridTestV2, RenderGridRTL001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RenderGridTestV2 rtl001 start";

    /**
     * @tc.steps: step1. Set the value of the member variable and call UpdateScrollPosition.
     * @tc.expected: step1. The return value of UpdateScrollPosition is false.
     */
    bool   result;
    double offset = -1.1;
    renderGridScroll_->SetDirection(true);
    renderGridScroll_->SetUseScrollable(MockRenderGridScroll::SCROLLABLE::HORIZONTAL);
    renderGridScroll_->SetReachHead(true);
    renderGridScroll_->SetReachTail(false);
    result = renderGridScroll_->UpdateScrollPositionTest(offset);
    EXPECT_EQ(result, false);

    GTEST_LOG_(INFO) << "RenderGridTestV2 rtl001 end";
}

/**
 * @tc.name: RenderGridRTL002
 * @tc.desc: Test whether function UpdateScrollPosition performs the expected action by
 * setting member variables to different values.
 * @tc.type: FUNC
 * @tc.require: issueI5NC7M
 */
HWTEST_F(RenderGridTestV2, RenderGridRTL002, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RenderGridTestV2 rtl002 start";

    /**
     * @tc.steps: step1. Set the value of the member variable and call UpdateScrollPosition.
     * @tc.expected: step1. The return value of UpdateScrollPosition is true.
     */
    bool   result;
    double offset = -1.1;
    renderGridScroll_->SetDirection(true);
    renderGridScroll_->SetUseScrollable(MockRenderGridScroll::SCROLLABLE::HORIZONTAL);
    renderGridScroll_->SetReachHead(false);
    renderGridScroll_->SetReachTail(true);
    result = renderGridScroll_->UpdateScrollPositionTest(offset);
    EXPECT_EQ(result, true);

    GTEST_LOG_(INFO) << "RenderGridTestV2 rtl002 end";
}

/**
 * @tc.name: RenderGridRTL003
 * @tc.desc: Test whether function UpdateScrollPosition performs the expected action by
 * setting member variables to different values.
 * @tc.type: FUNC
 * @tc.require: issueI5NC7M
 */
HWTEST_F(RenderGridTestV2, RenderGridRTL003, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RenderGridTestV2 rtl003 start";

    /**
     * @tc.steps: step1. Set the value of the member variable and call UpdateScrollPosition.
     * @tc.expected: step1. The return value of UpdateScrollPosition is false.
     */
    bool   result;
    double offset = 1.1;
    renderGridScroll_->SetDirection(true);
    renderGridScroll_->SetUseScrollable(MockRenderGridScroll::SCROLLABLE::HORIZONTAL);
    renderGridScroll_->SetReachHead(false);
    renderGridScroll_->SetReachTail(true);
    result = renderGridScroll_->UpdateScrollPositionTest(offset);
    EXPECT_EQ(result, false);

    GTEST_LOG_(INFO) << "RenderGridTestV2 rtl003 end";
}

/**
 * @tc.name: RenderGridRTL004
 * @tc.desc: Test whether function UpdateScrollPosition performs the expected action by
 * setting member variables to different values.
 * @tc.type: FUNC
 * @tc.require: issueI5NC7M
 */
HWTEST_F(RenderGridTestV2, RenderGridRTL004, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RenderGridTestV2 rtl004 start";

    /**
     * @tc.steps: step1. Set the value of the member variable and call UpdateScrollPosition.
     * @tc.expected: step1. The return value of UpdateScrollPosition is true.
     */
    bool   result;
    double offset = 1.1;
    renderGridScroll_->SetDirection(true);
    renderGridScroll_->SetUseScrollable(MockRenderGridScroll::SCROLLABLE::HORIZONTAL);
    renderGridScroll_->SetReachHead(true);
    renderGridScroll_->SetReachTail(false);
    result = renderGridScroll_->UpdateScrollPositionTest(offset);
    EXPECT_EQ(result, true);

    GTEST_LOG_(INFO) << "RenderGridTestV2 rtl004 end";
}

/**
 * @tc.name: RenderGridRTL005
 * @tc.desc: Test whether function UpdateScrollPosition performs the expected action by
 * setting member variables to different values.
 * @tc.type: FUNC
 * @tc.require: issueI5NC7M
 */
HWTEST_F(RenderGridTestV2, RenderGridRTL005, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RenderGridTestV2 rtl001 start";

    /**
     * @tc.steps: step1. Set the value of the member variable and call UpdateScrollPosition.
     * @tc.expected: step1. The return value of UpdateScrollPosition is true.
     */
    bool   result;
    double offset = -1.1;
    renderGridScroll_->SetDirection(true);
    renderGridScroll_->SetUseScrollable(MockRenderGridScroll::SCROLLABLE::VERTICAL);
    renderGridScroll_->SetReachHead(true);
    renderGridScroll_->SetReachTail(false);
    result = renderGridScroll_->UpdateScrollPositionTest(offset);
    EXPECT_EQ(result, true);

    GTEST_LOG_(INFO) << "RenderGridTestV2 rtl005 end";
}

/**
 * @tc.name: RenderGridRTL006
 * @tc.desc: Test whether function UpdateScrollPosition performs the expected action by
 * setting member variables to different values.
 * @tc.type: FUNC
 * @tc.require: issueI5NC7M
 */
HWTEST_F(RenderGridTestV2, RenderGridRTL006, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RenderGridTestV2 rtl006 start";

    /**
     * @tc.steps: step1. Set the value of the member variable and call UpdateScrollPosition.
     * @tc.expected: step1. The return value of UpdateScrollPosition is false.
     */
    bool   result;
    double offset = -1.1;
    renderGridScroll_->SetDirection(true);
    renderGridScroll_->SetUseScrollable(MockRenderGridScroll::SCROLLABLE::VERTICAL);
    renderGridScroll_->SetReachHead(false);
    renderGridScroll_->SetReachTail(true);
    result = renderGridScroll_->UpdateScrollPositionTest(offset);
    EXPECT_EQ(result, false);

    GTEST_LOG_(INFO) << "RenderGridTestV2 rtl006 end";
}

/**
 * @tc.name: RenderGridRTL007
 * @tc.desc: Test whether function UpdateScrollPosition performs the expected action by
 * setting member variables to different values.
 * @tc.type: FUNC
 * @tc.require: issueI5NC7M
 */
HWTEST_F(RenderGridTestV2, RenderGridRTL007, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RenderGridTestV2 rtl007 start";

    /**
     * @tc.steps: step1. Set the value of the member variable and call UpdateScrollPosition.
     * @tc.expected: step1. The return value of UpdateScrollPosition is true.
     */
    bool   result;
    double offset = 1.1;
    renderGridScroll_->SetDirection(true);
    renderGridScroll_->SetUseScrollable(MockRenderGridScroll::SCROLLABLE::VERTICAL);
    renderGridScroll_->SetReachHead(false);
    renderGridScroll_->SetReachTail(true);
    result = renderGridScroll_->UpdateScrollPositionTest(offset);
    EXPECT_EQ(result, true);

    GTEST_LOG_(INFO) << "RenderGridTestV2 rtl007 end";
}

/**
 * @tc.name: RenderGridRTL008
 * @tc.desc: Test whether function UpdateScrollPosition performs the expected action by
 * setting member variables to different values.
 * @tc.type: FUNC
 * @tc.require: issueI5NC7M
 */
HWTEST_F(RenderGridTestV2, RenderGridRTL008, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RenderGridTestV2 rtl008 start";

    /**
     * @tc.steps: step1. Set the value of the member variable and call UpdateScrollPosition.
     * @tc.expected: step1. The return value of UpdateScrollPosition is false.
     */
    bool   result;
    double offset = 1.1;
    renderGridScroll_->SetDirection(true);
    renderGridScroll_->SetUseScrollable(MockRenderGridScroll::SCROLLABLE::VERTICAL);
    renderGridScroll_->SetReachHead(true);
    renderGridScroll_->SetReachTail(false);
    result = renderGridScroll_->UpdateScrollPositionTest(offset);
    EXPECT_EQ(result, false);

    GTEST_LOG_(INFO) << "RenderGridTestV2 rtl008 end";
}

/**
 * @tc.name: RenderGridRTL009
 * @tc.desc: Test RTL of RenderGridScroll PerformLayout.
 * @tc.type: FUNC
 * @tc.require: issueI5NC7M
 */
HWTEST_F(RenderGridTestV2, RenderGridRTL009, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RenderGridTestV2 rtl009 start";

    /**
     * @tc.steps: step1. construct component and render with 4 child.
     * @tc.expected: step1. properties and children are set correctly.
     */
    std::string rowArgs = "1fr 50%";
    std::list<RefPtr<Component>> children;
    RefPtr<GridLayoutComponent> component = AceType::MakeRefPtr<GridLayoutComponent>(children);
    RefPtr<RenderGridLayout> renderNode_ = AceType::MakeRefPtr<RenderGridLayout>();
    component->SetWidth(DIM_SIZE_VALUE_TEST);
    component->SetHeight(DIM_SIZE_VALUE_TEST);
    component->SetDirection(FlexDirection::ROW);
    component->SetRightToLeft(true);
    component->SetRowsArgs(rowArgs);
    renderGridScroll_->Update(component);
    int32_t count = 4;
    for (int32_t i = 0; i < count; ++i) {
        RefPtr<RenderBox> box = GridTestUtils::CreateRenderBox(400.0, 400.0);
        RefPtr<RenderGridLayoutItem> item = AceType::MakeRefPtr<MockRenderGridLayoutItem>();
        item->AddChild(box);
        item->GetChildren().front()->Attach(mockContext_);
        item->Attach(mockContext_);
        renderNode_->AddChild(item);
        renderGridScroll_->AddChild(item);
    }
    EXPECT_EQ(renderNode_->GetChildren().size(), 4);

    /**
     * @tc.steps: step2. Verify that the properties are calculated correctly.
     * @tc.expected: step2. Properties are calculated correctly.
     */
    renderGridScroll_->SetDirection(true);
    renderGridScroll_->SetUseScrollable(MockRenderGridScroll::SCROLLABLE::HORIZONTAL);
    renderGridScroll_->PerformLayout();
    EXPECT_TRUE(renderGridScroll_->GetLayoutSize() == Size(DIM_SIZE_VALUE_TEST, DIM_SIZE_VALUE_TEST));
    
    GTEST_LOG_(INFO) << "RenderGridTestV2 rtl009 end";
}

/**
 * @tc.name: RenderGridRTL010
 * @tc.desc: Test LTR of RenderGridScroll PerformLayout.
 * @tc.type: FUNC
 * @tc.require: issueI5NC7M
 */
HWTEST_F(RenderGridTestV2, RenderGridRTL010, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RenderGridTestV2 rtl010 start";

    /**
     * @tc.steps: step1. construct component and render with 4 child.
     * @tc.expected: step1. properties and children are set correctly.
     */
    std::string rowArgs = "1fr 50%";
    std::list<RefPtr<Component>> children;
    RefPtr<GridLayoutComponent> component = AceType::MakeRefPtr<GridLayoutComponent>(children);
    RefPtr<RenderGridLayout> renderNode_ = AceType::MakeRefPtr<RenderGridLayout>();
    component->SetWidth(DIM_SIZE_VALUE_TEST);
    component->SetHeight(DIM_SIZE_VALUE_TEST);
    component->SetDirection(FlexDirection::ROW);
    component->SetRowsArgs(rowArgs);
    component->SetRightToLeft(false);
    renderGridScroll_->Update(component);
    int32_t count = 4;
    for (int32_t i = 0; i < count; ++i) {
        RefPtr<RenderBox> box = GridTestUtils::CreateRenderBox(400.0, 400.0);
        RefPtr<RenderGridLayoutItem> item = AceType::MakeRefPtr<MockRenderGridLayoutItem>();
        item->AddChild(box);
        item->GetChildren().front()->Attach(mockContext_);
        item->Attach(mockContext_);
        renderNode_->AddChild(item);
        renderGridScroll_->AddChild(item);
    }
    EXPECT_EQ(renderNode_->GetChildren().size(), 4);

    /**
     * @tc.steps: step2. Verify that the properties are calculated correctly.
     * @tc.expected: step2. Properties are calculated correctly.
     */
    renderGridScroll_->SetDirection(false);
    renderGridScroll_->SetUseScrollable(MockRenderGridScroll::SCROLLABLE::HORIZONTAL);
    renderGridScroll_->PerformLayout();
    EXPECT_TRUE(renderGridScroll_->GetLayoutSize() == Size(DIM_SIZE_VALUE_TEST, DIM_SIZE_VALUE_TEST));
    
    GTEST_LOG_(INFO) << "RenderGridTestV2 rtl010 end";
}

/**
 * @tc.name: RenderGridRTL011
 * @tc.desc: Test whether function SetChildPosition performs the expected action by
 * setting member variables to different values.
 * @tc.type: FUNC
 * @tc.require: issueI5NC7M
 */
HWTEST_F(RenderGridTestV2, RenderGridRTL011, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RenderGridTestV2 rtl011 start";

    /**
     * @tc.steps: step1. Set the value of the member variable and call SetChildPosition.
     * @tc.expected: step1. Direction is LTR.
     */
    RefPtr<RenderBox> box = GridTestUtils::CreateRenderBox(400.0, 400.0);
    RefPtr<RenderNode> item = AceType::MakeRefPtr<MockRenderGridLayoutItem>();
    item->AddChild(box);
    item->GetChildren().front()->Attach(mockContext_);
    item->Attach(mockContext_);
    renderGridScroll_->SetDirection(false);
    renderGridScroll_->SetUseScrollable(MockRenderGridScroll::SCROLLABLE::HORIZONTAL);
    renderGridScroll_->SetChildPositionTest(item);
    EXPECT_EQ(renderGridScroll_->GetDirection(), false);

    GTEST_LOG_(INFO) << "RenderGridTestV2 rtl011 end";
}

/**
 * @tc.name: RenderGridRTL012
 * @tc.desc: Test whether function SetChildPosition performs the expected action by
 * setting member variables to different values.
 * @tc.type: FUNC
 * @tc.require: issueI5NC7M
 */
HWTEST_F(RenderGridTestV2, RenderGridRTL012, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RenderGridTestV2 rtl012 start";

    /**
     * @tc.steps: step1. Set the value of the member variable and call SetChildPosition.
     * @tc.expected: step1. Direction is RTL.
     */
    RefPtr<RenderBox> box = GridTestUtils::CreateRenderBox(400.0, 400.0);
    RefPtr<RenderNode> item = AceType::MakeRefPtr<MockRenderGridLayoutItem>();
    item->AddChild(box);
    item->GetChildren().front()->Attach(mockContext_);
    item->Attach(mockContext_);
    renderGridScroll_->SetDirection(true);
    renderGridScroll_->SetUseScrollable(MockRenderGridScroll::SCROLLABLE::HORIZONTAL);
    renderGridScroll_->SetChildPositionTest(item);
    EXPECT_EQ(renderGridScroll_->GetDirection(), true);

    GTEST_LOG_(INFO) << "RenderGridTestV2 rtl012 end";
}

/**
 * @tc.name: RenderGridRTL013
 * @tc.desc: Test whether function InitScrollBar performs the expected action by
 * setting member variables to different values.
 * @tc.type: FUNC
 * @tc.require: issueI5NC7M
 */
HWTEST_F(RenderGridTestV2, RenderGridRTL013, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RenderGridTestV2 rtl013 start";

    /**
     * @tc.steps: step1. Set the value of the member variable and call InitScrollBar.
     * @tc.expected: step1. Direction is RTL.
     */
    std::list<RefPtr<Component>> children;
    RefPtr<GridLayoutComponent> component = AceType::MakeRefPtr<GridLayoutComponent>(children);
    component->SetWidth(DIM_SIZE_VALUE_TEST);
    component->SetHeight(DIM_SIZE_VALUE_TEST);
    component->SetDirection(FlexDirection::ROW);
    renderGridScroll_->SetDirection(true);
    renderGridScroll_->SetVertical(true);
    renderGridScroll_->InitScrollBarTest();
    EXPECT_EQ(renderGridScroll_->GetDirection(), true);

    GTEST_LOG_(INFO) << "RenderGridTestV2 rtl013 end";
}

} // namespace OHOS::Ace
