/*
 * Copyright (c) 2025 iSoftStone Information Technology (Group) Co.,Ltd.
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
#include "test/unittest/core/base/view_abstract_test_ng.h"

#include "core/common/ace_engine.h"
#include "core/components_ng/base/view_abstract_model_static.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class ViewAbstractTestStatic : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override
    {
        auto* stack = ViewStackProcessor::GetInstance();
        auto nodeId = stack->ClaimNodeId();
        auto frameNode =
            FrameNode::GetOrCreateFrameNode("components", nodeId, []() { return AceType::MakeRefPtr<Pattern>(); });
        stack->Push(frameNode);
    }
    void TearDown() override {}
};

void ViewAbstractTestStatic::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->pipelineContext_ = PipelineBase::GetCurrentContext();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    PipelineBase::GetCurrentContext()->SetThemeManager(themeManager);
    PipelineBase::GetCurrentContext()->SetEventManager(AceType::MakeRefPtr<EventManager>());
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<PopupTheme>()));
}

void ViewAbstractTestStatic::TearDownTestSuite()
{
    MockContainer::Current()->pipelineContext_ = nullptr;
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: ViewAbstractTest001
 * @tc.desc: SetWidth、SetHeight、SetMinWidth、SetMinHeight、SetMaxWidth、SetMaxHeight、ClearWidthOrHeight
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestStatic, SetAccessibilityUseSamePage001, TestSize.Level1)
{
    /**
     * @tc.steps: step1.Using static methods to set component properties
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    std::string pageModeTest = "FULL_SILENT";
    std::string pageModeTest1 = "SIMI_SILENT";

    // set FULL_SILENT will change property
    ViewAbstractModelStatic::SetAccessibilityUseSamePage(frameNode, pageModeTest);
    EXPECT_EQ(accessibilityProperty->GetAccessibilitySamePage(), pageModeTest);
    // set FULL_SILENT will keep property
    ViewAbstractModelStatic::SetAccessibilityUseSamePage(frameNode, pageModeTest);
    EXPECT_EQ(accessibilityProperty->GetAccessibilitySamePage(), pageModeTest);
    // set SIMI_SILENT will change property again
    ViewAbstractModelStatic::SetAccessibilityUseSamePage(frameNode, pageModeTest1);
    EXPECT_EQ(accessibilityProperty->GetAccessibilitySamePage(), pageModeTest1);
}

/**
 * @tc.name: SetBackgroundImagePosition
 * @tc.desc: Test SetBackgroundImagePosition
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestStatic, SetBackgroundImagePosition, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get frameNode and renderContext
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    /**
     * @tc.steps: step2. set background image position and check renderContext's background image position
     * @tc.expected: renderContext's background image position is set correctly
     */
    BackgroundImagePosition bgImgPosition;
    ViewAbstractModelStatic::SetBackgroundImagePosition(frameNode, bgImgPosition, false);
    EXPECT_TRUE(renderContext->GetBackgroundImagePosition().has_value());
    EXPECT_EQ(renderContext->GetBackgroundImagePosition().value(), bgImgPosition);

    /**
     * @tc.steps: step2. reset background image position and check renderContext's background image position
     * @tc.expected: renderContext's background image position is reset correctly
     */
    ViewAbstractModelStatic::SetBackgroundImagePosition(frameNode, bgImgPosition, true);
    EXPECT_FALSE(renderContext->GetBackgroundImagePosition().has_value());
}

/**
 * @tc.name: BindContextMenuStatic001
 * @tc.desc: Test the BindContextMenuStatic
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestStatic, BindContextMenuStatic001, TestSize.Level1)
{
    const RefPtr<FrameNode> mainNode = FrameNode::CreateFrameNode("main", 6, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(mainNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(mainNode);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<SelectTheme>();
    theme->expandDisplay_ = true;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto containerId = pipelineContext->GetInstanceId();
    AceEngine& aceEngine = AceEngine::Get();
    aceEngine.AddContainer(containerId, MockContainer::container_);
    aceEngine.AddContainer(containerId, MockContainer::container_);
    std::function<void()> flagFunc = []() { flag++; };
    std::vector<NG::OptionParam> params = {};
    std::function<void()> buildFunc;
    MenuParam menuParam;
    std::function<void()> previewBuildFunc = nullptr;
    auto type = ResponseType::LONG_PRESS;
    menuParam.isShowInSubWindow = false;
    menuParam.previewMode = MenuPreviewMode::IMAGE;
    buildFunc = []() { flag++; };
    menuParam.isShowHoverImage = false;
    menuParam.contextMenuRegisterType = ContextMenuRegisterType::CUSTOM_TYPE;
    menuParam.isShow = true;

    ViewAbstractModelStatic::BindContextMenuStatic(
        mainNode, type, std::move(buildFunc), menuParam, std::move(previewBuildFunc));
    menuParam.previewMode = MenuPreviewMode::CUSTOM;
    ViewAbstractModelStatic::BindContextMenuStatic(
        mainNode, type, std::move(buildFunc), menuParam, std::move(previewBuildFunc));
    menuParam.isShow = false;
    ViewAbstractModelStatic::BindContextMenuStatic(
        mainNode, type, std::move(buildFunc), menuParam, std::move(previewBuildFunc));
    menuParam.isShow = true;
    buildFunc = nullptr;
    ViewAbstractModelStatic::BindContextMenuStatic(
        mainNode, type, std::move(buildFunc), menuParam, std::move(previewBuildFunc));
    EXPECT_NE(mainNode, nullptr);
}
} // namespace OHOS::Ace::NG