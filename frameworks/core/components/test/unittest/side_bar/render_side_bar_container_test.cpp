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

#include "core/components/side_bar/side_bar_container_component.h"
#include "core/components/test/unittest/mock/mock_render_common.h"
#include "core/components/test/unittest/side_bar/side_bar_container_test_utils.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {
constexpr Dimension MAX_SIDEBAR_WIDTH = 250.0_vp;
constexpr Dimension MIN_SIDEBAR_WIDTH = 20.0_vp;
constexpr Dimension SIDEBAR_WIDTH = 150.0_vp;
constexpr double BOXDEFAULT = 300.0;
constexpr double RECT_WIDTH = 1080.0;
constexpr double RECT_HEIGHT = 2244.0;

constexpr double LOCATION_X = 130;
constexpr double LOCATION_Y = 150;
constexpr double GLOBAL_X = 140;
constexpr double GLOBAL_Y = 150;
} // namespace

class RenderSideBarContainerTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp();
    void TearDown();

protected:
    RefPtr<PipelineContext> mockContext_;
    RefPtr<RenderSideBarContainer> renderNode_;
};

void RenderSideBarContainerTest::SetUpTestCase() {}
void RenderSideBarContainerTest::TearDownTestCase() {}

void RenderSideBarContainerTest::SetUp()
{
    /**
     * @tc.desc: construct RenderSideBarContainer with 3 child.
     */
    mockContext_ = MockRenderCommon::GetMockContext();
    renderNode_ = AceType::MakeRefPtr<MockRenderSideBarContainer>();
    const Rect paintRect(0.0f, 0.0f, RECT_WIDTH, RECT_HEIGHT);
    renderNode_->SetPaintRect(paintRect);

    RefPtr<RenderBox> renderBox1 = SideBarContainerTestUtils::CreateRenderBox(BOXDEFAULT, BOXDEFAULT);
    renderBox1->Attach(mockContext_);
    renderBox1->SetLayoutSize(Size(BOXDEFAULT, BOXDEFAULT));
    renderNode_->AddChild(renderBox1);

    RefPtr<RenderBox> renderBox2 = SideBarContainerTestUtils::CreateRenderBox(BOXDEFAULT, BOXDEFAULT);
    renderBox2->Attach(mockContext_);
    renderBox2->SetLayoutSize(Size(BOXDEFAULT, BOXDEFAULT));
    renderNode_->AddChild(renderBox2);

    RefPtr<RenderDisplay> renderBox3 = SideBarContainerTestUtils::CreateRenderDisplay();
    renderBox3->Attach(mockContext_);
    renderNode_->AddChild(renderBox3);

    LayoutParam layoutParam;
    layoutParam.SetMinSize(Size(0.0, 0.0));
    layoutParam.SetMaxSize(Size(RECT_WIDTH, RECT_HEIGHT));
    renderNode_->SetLayoutParam(layoutParam);

    renderNode_->Attach(mockContext_);

    /**
     * @tc.desc: construct SideBarContainerComponent.
     */
    std::list<RefPtr<Component>> children;
    RefPtr<SideBarContainerComponent> sidebarcontainer = AceType::MakeRefPtr<SideBarContainerComponent>(children);
    sidebarcontainer->SetShowSideBar(true);
    sidebarcontainer->SetSideBarContainerType(SideBarContainerType::EMBED);
    sidebarcontainer->SetSideBarMaxWidth(MAX_SIDEBAR_WIDTH);
    sidebarcontainer->SetSideBarMinWidth(MIN_SIDEBAR_WIDTH);
    sidebarcontainer->SetSideBarWidth(SIDEBAR_WIDTH);
    sidebarcontainer->SetSideBarPosition(SideBarPosition::END);

    renderNode_->Update(sidebarcontainer);
}

void RenderSideBarContainerTest::TearDown()
{
    renderNode_ = nullptr;
    mockContext_ = nullptr;
}

/**
 * @tc.name: RenderSideBarTestUpdate01
 * @tc.desc: Verify the Update Interface of RenderSideBarContainer work correctly with sidebarcontainer component.
 * @tc.type: FUNC
 * @tc.require: issueI5JQ4S
*/
HWTEST_F(RenderSideBarContainerTest, RenderSideBarTestUpdate01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. setup invoked before testcase.
     * @tc.expected: step1. properties and renderNode_ are set correctly.
     */
    ASSERT_TRUE(renderNode_);

    EXPECT_TRUE(renderNode_->GetChildren().size() == 3);

    EXPECT_TRUE(renderNode_->GetShowSideBarContainer());
    EXPECT_EQ(renderNode_->GetStyle(), "SideBarContainerType.Embed");
    EXPECT_EQ(renderNode_->GetSideBarMaxWidth(), MAX_SIDEBAR_WIDTH);
    EXPECT_EQ(renderNode_->GetSideBarMinWidth(), MIN_SIDEBAR_WIDTH);
    EXPECT_EQ(renderNode_->GetSideBarWidth(), SIDEBAR_WIDTH);
    EXPECT_EQ(renderNode_->GetSideBarPosition(), SideBarPosition::END);
}

/**
 * @tc.name: RenderSideBarPositionTest01
 * @tc.desc: Verify the sidebarcontainer component with embed sidebarcontainertype and end sidebarposition works fine.
 * @tc.type: FUNC
 * @tc.require: issueI5JQ4S
 */
HWTEST_F(RenderSideBarContainerTest, RenderSideBarPositionTest01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. setup invoked before testcase.
     */

    /**
     * @tc.steps: step2. call PerformLayout interface
     */
    renderNode_->PerformLayout();

    /**
     * @tc.steps: step3. calculate the actual position and layoutParam.
     * @tc.expected: step3. position and layoutparam of children is correct.
     */
    auto layoutSize = renderNode_->GetLayoutSize();
    auto layoutSizeWithVP =  Dimension(Dimension(layoutSize.Width()).ConvertToVp(), DimensionUnit::VP);
    auto sidebar_X = (layoutSizeWithVP - SIDEBAR_WIDTH).ConvertToPx();

    auto fixedSize = layoutSize.MinusWidth(SIDEBAR_WIDTH.ConvertToPx());

    auto renderchildren = renderNode_->GetChildren();
    auto begin = renderchildren.begin();
    RefPtr<RenderNode>& content = *begin;
    RefPtr<RenderNode>& sideBar = *(++begin);

    EXPECT_EQ(content->GetPosition(), Offset(0, 0));
    EXPECT_EQ(content->GetLayoutParam(), LayoutParam(fixedSize, Size()));

    fixedSize = Size(SIDEBAR_WIDTH.ConvertToPx(), layoutSize.Height());

    EXPECT_EQ(sideBar->GetPosition(), Offset(sidebar_X, 0));
    EXPECT_EQ(sideBar->GetLayoutParam(), LayoutParam(fixedSize, fixedSize));
}

/**
 * @tc.name: RenderSideBarPositionTest02
 * @tc.desc: Verify the sidebarcontainer component with embed sidebarcontainertype and start sidebarposition works fine.
 * @tc.type: FUNC
 * @tc.require: issueI5JQ4S
 */
HWTEST_F(RenderSideBarContainerTest, RenderSideBarPositionTest02, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct SideBarContainerComponent.
     */
    std::list<RefPtr<Component>> children;
    RefPtr<SideBarContainerComponent> sidebarcontainer = AceType::MakeRefPtr<SideBarContainerComponent>(children);
    sidebarcontainer->SetShowSideBar(true);
    sidebarcontainer->SetSideBarContainerType(SideBarContainerType::EMBED);
    sidebarcontainer->SetSideBarMaxWidth(MAX_SIDEBAR_WIDTH);
    sidebarcontainer->SetSideBarMinWidth(MIN_SIDEBAR_WIDTH);
    sidebarcontainer->SetSideBarWidth(SIDEBAR_WIDTH);
    sidebarcontainer->SetSideBarPosition(SideBarPosition::START);

    /**
     * @tc.steps: step2. call the Update interface of RenderSideBarContainer.
     */
    renderNode_->Update(sidebarcontainer);

    /**
     * @tc.steps: step3. call PerformLayout interface.
     * @tc.expected: step3. position and layoutparam of children is correct.
     */
    renderNode_->PerformLayout();
    
    auto layoutSize = renderNode_->GetLayoutSize();
    auto layoutSizeWithVP =  Dimension(Dimension(layoutSize.Width()).ConvertToVp(), DimensionUnit::VP);
    auto content_X = (layoutSizeWithVP - SIDEBAR_WIDTH).ConvertToPx();

    auto renderchildren = renderNode_->GetChildren();
    auto begin = renderchildren.begin();
    RefPtr<RenderNode>& content = *begin;
    RefPtr<RenderNode>& sideBar = *(++begin);

    auto fixedSize = layoutSize.MinusWidth((layoutSizeWithVP - SIDEBAR_WIDTH).ConvertToPx());

    EXPECT_EQ(content->GetPosition(), Offset(content_X, 0));
    EXPECT_EQ(content->GetLayoutParam(), LayoutParam(fixedSize, Size()));

    fixedSize = Size(SIDEBAR_WIDTH.ConvertToPx(), layoutSize.Height());

    EXPECT_EQ(sideBar->GetPosition(), Offset(0, 0));
    EXPECT_EQ(sideBar->GetLayoutParam(), LayoutParam(fixedSize, fixedSize));
}

/**
 * @tc.name: RenderSideBarPositionTest03
 * @tc.desc: Verify the sidebarcontainer component with overlay sidebarcontainertype and end sidebarposition works fine.
 * @tc.type: FUNC
 * @tc.require: issueI5JQ4S
 */
HWTEST_F(RenderSideBarContainerTest, RenderSideBarPositionTest03, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct SideBarContainerComponent.
     */
    std::list<RefPtr<Component>> children;
    RefPtr<SideBarContainerComponent> sidebarcontainer = AceType::MakeRefPtr<SideBarContainerComponent>(children);
    sidebarcontainer->SetShowSideBar(true);
    sidebarcontainer->SetSideBarContainerType(SideBarContainerType::OVERLAY);
    sidebarcontainer->SetSideBarMaxWidth(MAX_SIDEBAR_WIDTH);
    sidebarcontainer->SetSideBarMinWidth(MIN_SIDEBAR_WIDTH);
    sidebarcontainer->SetSideBarWidth(SIDEBAR_WIDTH);
    sidebarcontainer->SetSideBarPosition(SideBarPosition::END);

    /**
     * @tc.steps: step2. call the Update interface of RenderSideBarContainer.
     */
    renderNode_->Update(sidebarcontainer);

    /**
     * @tc.steps: step3. call PerformLayout interface.
     * @tc.expected: step3. position and layoutparam of children is correct.
     */
    renderNode_->PerformLayout();

    auto layoutSize = renderNode_->GetLayoutSize();
    auto layoutSizeWithVP =  Dimension(Dimension(layoutSize.Width()).ConvertToVp(), DimensionUnit::VP);
    auto sidebar_X = (layoutSizeWithVP - SIDEBAR_WIDTH).ConvertToPx();

    auto renderchildren = renderNode_->GetChildren();
    auto begin = renderchildren.begin();
    RefPtr<RenderNode>& content = *begin;
    RefPtr<RenderNode>& sideBar = *(++begin);

    EXPECT_EQ(content->GetPosition(), Offset(0, 0));
    EXPECT_EQ(content->GetLayoutParam(), LayoutParam(layoutSize, Size()));
    
    auto fixedSize = Size(SIDEBAR_WIDTH.ConvertToPx(), layoutSize.Height());

    EXPECT_EQ(sideBar->GetPosition(), Offset(sidebar_X, 0));
    EXPECT_EQ(sideBar->GetLayoutParam(), LayoutParam(fixedSize, fixedSize));
}

/**
 * @tc.name: RenderSideBarTouchTest01
 * @tc.desc: Verify the TouchTest Interface of RenderSideBarContainer work correctly.
 * @tc.type: FUNC
 * @tc.require: issueI5JQ4S
 */
HWTEST_F(RenderSideBarContainerTest, RenderSideBarTouchTest01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call PerformLayout interface.
     */
    renderNode_->PerformLayout();
    
    /**
     * @tc.steps: step2. Touch Test.
     * @tc.expected: step2. Touch Test correctly.
     */
    Point localpoint { LOCATION_X, LOCATION_Y };
    Point globalpoint { GLOBAL_X, GLOBAL_Y };
    TouchTestResult result;
    renderNode_->TouchTest(localpoint, globalpoint, { TouchRestrict::NONE }, result);
    EXPECT_EQ(result.size(), 1);
}
} // namespace OHOS::Ace