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

#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "text_base.h"

#include "core/components/select/select_theme.h"
#include "core/components/text_overlay/text_overlay_theme.h"
#include "core/components_ng/pattern/rich_editor/paragraph_manager.h"
#include "core/components_ng/pattern/rich_editor_drag/preview_menu_controller.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const std::string APP_NAME_MAP = "app.name";
} // namespace
class PreviewMenuControllerTest : public testing::Test {
public:
    static void SetUpTestCase()
    {
        MockPipelineContext::SetUp();
    }

    static void TearDownTestCase()
    {
        MockPipelineContext::TearDown();
    }

    void SetUp() override
    {
        // Initialize test environment
    }

    void TearDown() override
    {
        // Clean up
    }
};

/**
 * @tc.name: PreviewMenuControllerConstructorTest
 * @tc.desc: Test PreviewMenuController constructor initializes correctly
 * @tc.type: FUNC
 */
HWTEST_F(PreviewMenuControllerTest, PreviewMenuControllerConstructorTest, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    PreviewMenuController controller(AceType::WeakClaim(AceType::RawPtr(pattern)));

    EXPECT_EQ(controller.menuParam_.type, MenuType::CONTEXT_MENU);
    EXPECT_EQ(controller.menuParam_.contextMenuRegisterType, ContextMenuRegisterType::CUSTOM_TYPE);
    EXPECT_EQ(controller.menuParam_.previewMode, MenuPreviewMode::CUSTOM);
    EXPECT_TRUE(controller.menuParam_.isShowHoverImage);
    EXPECT_NE(controller.menuParam_.onDisappear, nullptr);
}

/**
 * @tc.name: CreateAIEntityMenuTest
 * @tc.desc: Test CreateAIEntityMenu creates menu node correctly
 * @tc.type: FUNC
 */
HWTEST_F(PreviewMenuControllerTest, CreateAIEntityMenuTest, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    PreviewMenuController controller(AceType::WeakClaim(AceType::RawPtr(pattern)));
    controller.CreateAIEntityMenu();
    auto stack = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_NE(stack, nullptr);
    EXPECT_EQ(stack->GetTag(), V2::FLEX_ETS_TAG);
}

/**
 * @tc.name: GetDisappearCallbackTest
 * @tc.desc: Test GetDisappearCallback returns valid callback
 * @tc.type: FUNC
 */
HWTEST_F(PreviewMenuControllerTest, GetDisappearCallbackTest, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    // Mock target node
    auto targetNode = FrameNode::CreateFrameNode("Test", 1, AceType::MakeRefPtr<TextPattern>());
    pattern->dragNode_ = targetNode;
    PreviewMenuController controller(AceType::WeakClaim(AceType::RawPtr(pattern)));

    auto callback = controller.GetDisappearCallback();
    callback();
    EXPECT_NE(callback, nullptr);

    EXPECT_EQ(controller.menuParam_.isShow, false);
    EXPECT_EQ(controller.isShow_, false);
}

/**
 * @tc.name: GetLinkingCallbackTest
 * @tc.desc: Test GetLinkingCallback returns valid callback for different app names
 * @tc.type: FUNC
 */
HWTEST_F(PreviewMenuControllerTest, GetLinkingCallbackTest, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    PreviewMenuController controller(AceType::WeakClaim(AceType::RawPtr(pattern)));

    auto callback = controller.GetLinkingCallback(APP_NAME_MAP);
    EXPECT_NE(callback, nullptr);

    // Should test with mock PipelineContext to verify StartAbilityOnInstallAppInStore is called
}

/**
 * @tc.name: CreatePreviewMenuTest
 * @tc.desc: Test CreatePreviewMenu creates preview node correctly
 * @tc.type: FUNC
 */
HWTEST_F(PreviewMenuControllerTest, CreatePreviewMenuTest, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    PreviewMenuController controller(AceType::WeakClaim(AceType::RawPtr(pattern)));

    auto targetNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 1, AceType::MakeRefPtr<TextPattern>());
    auto* stack = ViewStackProcessor::GetInstance();
    auto beforeSize = stack->elementsStack_.size();

    // Test with different TextDataDetectType
    pattern->textSelector_.aiStart = 0;
    pattern->textSelector_.aiEnd = 5;

    std::map<int32_t, AISpan> aiSpanMap;
    AISpan aiSpan1;
    aiSpan1.start = 0;
    aiSpan1.end = 5;
    aiSpan1.content = SPAN_PHONE;
    aiSpan1.type = TextDataDetectType::PHONE_NUMBER;
    aiSpanMap[0] = aiSpan1;
    pattern->dataDetectorAdapter_->aiSpanMap_ = aiSpanMap;
    auto textForAI = u"Test1234";
    pattern->dataDetectorAdapter_->textForAI_ = textForAI;
    pattern->dataDetectorAdapter_->enablePreviewMenu_ = true;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto func = controller.GetDisappearCallback();
    controller.CreatePreviewMenu(aiSpan1.type, aiSpan1.content, std::move(func));

    auto afterSize = stack->elementsStack_.size();
    EXPECT_GT(afterSize, beforeSize);
    auto node = stack->Finish();
    EXPECT_NE(node, nullptr);
}

/**
 * @tc.name: CreateLinkingNodeTest
 * @tc.desc: Test CreateLinkingNode creates node with correct properties for different types
 * @tc.type: FUNC
 */
HWTEST_F(PreviewMenuControllerTest, CreateLinkingNodeTest, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    PreviewMenuController controller(AceType::WeakClaim(AceType::RawPtr(pattern)));

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));

    auto callback = []() {};
    // Test with URL type
    auto urlNode = controller.CreateLinkingNode(TextDataDetectType::URL, callback);
    EXPECT_NE(urlNode, nullptr);

    // Test with DATE_TIME type
    auto dateNode = controller.CreateLinkingNode(TextDataDetectType::DATE_TIME, callback);
    EXPECT_NE(dateNode, nullptr);

    // Test with ADDRESS type
    auto addrNode = controller.CreateLinkingNode(TextDataDetectType::ADDRESS, callback);
    EXPECT_NE(addrNode, nullptr);
}
} // namespace OHOS::Ace::NG