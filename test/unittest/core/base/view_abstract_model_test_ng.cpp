/*
 * Copyright (c) 2024 iSoftStone Information Technology (Group) Co.,Ltd.
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
#define protected public
#define private public
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/memory/referenced.h"
#include "core/common/ace_engine.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_style.h"
#include "core/components_ng/pattern/stage/page_pattern.h"

#undef private
using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
    ViewAbstractModelNG viewAbstractModelNG;
    RefPtr<MockTaskExecutor> MOCK_TASK_EXECUTOR;
}; // namespace

class ViewAbstractModelTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestCase();
};

void ViewAbstractModelTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;
}
void ViewAbstractModelTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: ViewAbstractModelTestNg001
 * @tc.desc: Test the GetSheetContext of View_Abstract_model_ng
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelTestNg, ViewAbstractModelTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build sheetStyle instanceId is empty.
     */
    SheetStyle style;
    auto testContext1 = viewAbstractModelNG.GetSheetContext(style);
    EXPECT_NE(testContext1, nullptr);

    /**
     * @tc.steps: step2. Build sheetStyle instanceId is 100001.
     */
    style.instanceId = 100001;
    /**
     * @tc.steps: step3. Build an AceEngine.
     */
    AceEngine& aceEngine = AceEngine::Get();

    /**
     * @tc.steps: step4. Add Container.
     * @tc.expected: Add Container success.
     */
    aceEngine.AddContainer(style.instanceId.value(), MockContainer::container_);
    EXPECT_NE(aceEngine.GetContainer(style.instanceId.value()), nullptr);
    /**
     * @tc.expected: context is not nullptr.
     */
    auto testContext2 = viewAbstractModelNG.GetSheetContext(style);
    EXPECT_NE(testContext2, nullptr);
}

/**
 * @tc.name: BindSheetShowInPageTest1
 * @tc.desc: Test the composition of sheet parent nodes when page will show in page
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelTestNg, BindSheetShowInPageTest1, TestSize.Level1)
{
    // pagelevel Node is Page Node
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    auto column = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    auto targetNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    targetNode->MountToParent(column);
    column->MountToParent(pageNode);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    NG::SheetStyle sheetStyle;
    sheetStyle.showInPage = true;
    viewAbstractModelNG.BindSheet(false, nullptr, nullptr, nullptr, sheetStyle, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    auto pagePatern = pageNode->GetPattern<PagePattern>();
    ASSERT_NE(pagePatern, nullptr);
    auto overlay1 = pagePatern->GetOverlayManager();
    EXPECT_EQ(overlay1, nullptr);
    viewAbstractModelNG.BindSheet(true, nullptr, nullptr, nullptr, sheetStyle, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    auto overlay2 = pagePatern->GetOverlayManager();
    EXPECT_NE(overlay2, nullptr);
    EXPECT_FALSE(targetNode->PageLevelIsNavDestination());
    EXPECT_EQ(targetNode->GetPageLevelNodeId(), pageNode->GetId());
}

/**
 * @tc.name: BindSheetShowInPageTest2
 * @tc.desc: Test the composition of sheet parent nodes when page will show in navDestination page
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelTestNg, BindSheetShowInPageTest2, TestSize.Level1)
{
    // pagelevel Node is navDestination Node
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    auto column = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    auto navDestinaion = FrameNode::CreateFrameNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<NavDestinationPattern>());
    auto targetNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    targetNode->MountToParent(navDestinaion);
    navDestinaion->MountToParent(column);
    column->MountToParent(pageNode);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    NG::SheetStyle sheetStyle;
    sheetStyle.showInPage = true;
    viewAbstractModelNG.BindSheet(true, nullptr, nullptr, nullptr, sheetStyle, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    auto navPatern = navDestinaion->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navPatern, nullptr);
    auto overlay = navPatern->GetOverlayManager();
    EXPECT_NE(overlay, nullptr);
    EXPECT_TRUE(targetNode->PageLevelIsNavDestination());
    EXPECT_EQ(targetNode->GetPageLevelNodeId(), navDestinaion->GetId());
    EXPECT_TRUE(pageNode->PageLevelIsNavDestination());
    EXPECT_EQ(pageNode->GetPageLevelNodeId(), targetNode->GetPageLevelNodeId());
}
} // namespace OHOS::Ace::NG