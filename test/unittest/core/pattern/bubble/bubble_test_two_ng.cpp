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
#include <string>

#include "gtest/gtest.h"

#include "base/geometry/ng/rect_t.h"

#define private public
#define protected public
#include "test/mock/base/mock_system_properties.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "test/mock/core/rosen/testing_canvas.h"
#include "test/mock/core/rosen/testing_path.h"

#include "base/geometry/ng/offset_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/common/ace_engine.h"
#include "core/components/button/button_theme.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/placement.h"
#include "core/components/popup/popup_theme.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/bubble/bubble_event_hub.h"
#include "core/components_ng/pattern/bubble/bubble_layout_property.h"
#include "core/components_ng/pattern/bubble/bubble_pattern.h"
#include "core/components_ng/pattern/bubble/bubble_render_property.h"
#include "core/components_ng/pattern/bubble/bubble_view.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class MockBubbleTheme : public PopupTheme, public ButtonTheme {
    DECLARE_ACE_TYPE(MockBubbleTheme, PopupTheme, ButtonTheme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;

        RefPtr<MockBubbleTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const
        {
            RefPtr<MockBubbleTheme> theme = AceType::MakeRefPtr<MockBubbleTheme>();
            return theme;
        }
    };

    ~MockBubbleTheme() override = default;

protected:
    MockBubbleTheme() = default;
};

class BubbleTestTwoNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void BubbleTestTwoNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void BubbleTestTwoNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: InitWrapperRect001
 * @tc.desc: Test InitWrapperRect
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestTwoNg, InitWrapperRect001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>("test1", 1, AceType::MakeRefPtr<BubblePattern>());
    ASSERT_NE(frameNode, nullptr);
    auto refLayoutWrapper = frameNode->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);
    ASSERT_NE(layoutWrapper, nullptr);
    BubbleLayoutAlgorithm bubbleLayoutAlgorithm;
    bubbleLayoutAlgorithm.targetNodeId_ = 1;
    bubbleLayoutAlgorithm.targetTag_ = "stage";
    RefPtr<BubbleLayoutProperty> layoutProp = AceType::MakeRefPtr<BubbleLayoutProperty>();
    ASSERT_NE(layoutProp, nullptr);
    bubbleLayoutAlgorithm.InitWrapperRect(layoutWrapper, layoutProp);
    bubbleLayoutAlgorithm.isHalfFoldHover_ = true;
    MockSystemProperties::g_isSuperFoldDisplayDevice = true;
    RefPtr<MockContainer> containerOne = AceType::MakeRefPtr<MockContainer>();
    RefPtr<MockContainer> containerTwo = AceType::MakeRefPtr<MockContainer>();
    MockContainer::Current()->GetMockDisplayInfo()->SetFoldStatus(FoldStatus::HALF_FOLD);
    layoutProp->UpdateEnableHoverMode(true);
    AceEngine::Get().AddContainer(0, containerOne);
    AceEngine::Get().AddContainer(1, containerTwo);
    bubbleLayoutAlgorithm.InitWrapperRect(layoutWrapper, layoutProp);
    EXPECT_FALSE(bubbleLayoutAlgorithm.isHalfFoldHover_);
    bubbleLayoutAlgorithm.foldCreaseBottom_ = -1;
    bubbleLayoutAlgorithm.InitWrapperRect(layoutWrapper, layoutProp);
    EXPECT_EQ(bubbleLayoutAlgorithm.wrapperRect_.y_, -1);
    bubbleLayoutAlgorithm.foldCreaseTop_ = 1;
    bubbleLayoutAlgorithm.InitWrapperRect(layoutWrapper, layoutProp);
    EXPECT_EQ(bubbleLayoutAlgorithm.wrapperRect_.y_, 0);
}

/**
 * @tc.name: CreateBubbleNode001
 * @tc.desc: Test CreateBubbleNode
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTestTwoNg, CreateBubbleNode001, TestSize.Level1)
{
    auto param = AceType::MakeRefPtr<PopupParam>();
    ASSERT_NE(param, nullptr);
    param->enableHoverMode_ = true;
    auto themeManagerOne = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManagerOne, nullptr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManagerOne);
    EXPECT_CALL(*themeManagerOne, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<PopupTheme>()));
    BubbleView::CreateBubbleNode("test1", 1, param);
    EXPECT_TRUE(param->HasEnableHoverMode());
}
} // namespace OHOS::Ace::NG
