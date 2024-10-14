/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "core/common/agingadapation/aging_adapation_dialog_theme.h"
#include "core/common/agingadapation/aging_adapation_dialog_util.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/navigation/bar_item_node.h"
#include "core/components_ng/pattern/navigation/tool_bar_layout_algorithm.h"
#include "core/components_ng/pattern/navigation/tool_bar_node.h"
#include "core/components_ng/pattern/navigation/tool_bar_pattern.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
    constexpr Color FRONT_COLOR = Color(0xff0000ff);
} // namespace
class ToolBarTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    static void MockPipelineContextGetTheme();
    void SetUp() override;
    void TearDown() override;
    RefPtr<NavToolbarPattern> toolBarPattern_;
    RefPtr<NavToolbarNode> toolBarNode_;
};

void ToolBarTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void ToolBarTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

void ToolBarTestNg::SetUp()
{
    toolBarPattern_ = AceType::MakeRefPtr<NavToolbarPattern>();
    toolBarNode_ = AceType::MakeRefPtr<NavToolbarNode>("tag", 1);
}

void ToolBarTestNg::TearDown()
{
    toolBarPattern_ = nullptr;
    toolBarNode_ = nullptr;
}

void ToolBarTestNg::MockPipelineContextGetTheme()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
}

/**
 * @tc.name: ToolBarPatternTest001
 * @tc.desc: Test the CreateLayoutAlgorithm and IsAtomicNode function.
 * @tc.type: FUNC
 */
HWTEST_F(ToolBarTestNg, ToolBarPatternTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test the CreateLayoutAlgorithm function.
     * @tc.expected: result is not empty.
     */
    auto result = toolBarPattern_->CreateLayoutAlgorithm();
    EXPECT_NE(result, nullptr);

    /**
     * @tc.steps: step2. Test the IsAtomicNode function.
     * @tc.expected: result is false.
     */
    auto atomicNode = toolBarPattern_->IsAtomicNode();
    EXPECT_FALSE(atomicNode);
}

/**
 * @tc.name: ToolbarNodeTest001
 * @tc.desc: Test the SetToolbarContainerNode, GetToolbarContainerNode and IsAtomicNode function.
 * @tc.type: FUNC
 */
HWTEST_F(ToolBarTestNg, ToolbarNodeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test the SetToolbarContainerNode and GetToolbarContainerNode function.
     * @tc.expected: result is empty.
     */
    RefPtr<UINode> customNode = nullptr;
    toolBarNode_->SetToolbarContainerNode(customNode);
    auto result = toolBarNode_->GetToolbarContainerNode();
    EXPECT_EQ(result, nullptr);

    /**
     * @tc.steps: step2. Test the IsAtomicNode function.
     * @tc.expected: result is false.
     */
    auto atomicNode = toolBarNode_->IsAtomicNode();
    EXPECT_FALSE(atomicNode);
}

/**
 * @tc.name: ToolbarNodeTest002
 * @tc.desc: Test the GetOrCreateToolbarNode function.
 * @tc.type: FUNC
 */
HWTEST_F(ToolBarTestNg, ToolbarNodeTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. initialization.
     */
    std::string tag = "tag";
    int32_t nodeId = 1;
    std::function<RefPtr<Pattern>(void)> patternCreator;

    /**
     * @tc.steps: step2. Test the GetOrCreateToolbarNode function.
     * @tc.expected: result is not empty.
     */
    auto result = toolBarNode_->GetOrCreateToolbarNode(tag, nodeId, patternCreator);
    EXPECT_NE(result, nullptr);
}

/**
 * @tc.name: ToolBarPatternTest002
 * @tc.desc: Test the SetToolbarOptions function.
 * @tc.type: FUNC
 */
HWTEST_F(ToolBarTestNg, ToolBarPatternTest002, TestSize.Level1)
{
    auto frameNode =
        FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<NavToolbarPattern>());
    EXPECT_NE(frameNode, nullptr);
    auto navToolbarPattern = frameNode->GetPattern<NavToolbarPattern>();
    EXPECT_NE(navToolbarPattern, nullptr);
    NavigationToolbarOptions opt;
    navToolbarPattern->SetToolbarOptions(std::move(opt));
}

/**
 * @tc.name: ToolBarPatternTest003
 * @tc.desc: Test the SetToolbarOptions function.
 * @tc.type: FUNC
 */
HWTEST_F(ToolBarTestNg, ToolBarPatternTest003, TestSize.Level1)
{
    auto frameNode =
        FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<NavToolbarPattern>());
    EXPECT_NE(frameNode, nullptr);
    auto navToolbarPattern = frameNode->GetPattern<NavToolbarPattern>();
    EXPECT_NE(navToolbarPattern, nullptr);
    NavigationToolbarOptions opt;
    opt.bgOptions.color = std::make_optional(FRONT_COLOR);
    opt.bgOptions.blurStyle = std::make_optional(BlurStyle::NO_MATERIAL);
    navToolbarPattern->SetToolbarOptions(std::move(opt));
}

/**
 * @tc.name: ToolBarPatternTest004
 * @tc.desc: Test the SetToolbarOptions function.
 * @tc.type: FUNC
 */
HWTEST_F(ToolBarTestNg, ToolBarPatternTest004, TestSize.Level1)
{
    auto frameNode =
        FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<NavToolbarPattern>());
    EXPECT_NE(frameNode, nullptr);
    auto navToolbarPattern = frameNode->GetPattern<NavToolbarPattern>();
    EXPECT_NE(navToolbarPattern, nullptr);
    NavigationToolbarOptions opt;
    opt.bgOptions.blurStyle = std::make_optional(BlurStyle::NO_MATERIAL);
    navToolbarPattern->SetToolbarOptions(std::move(opt));
}

/**
 * @tc.name: ToolBarPatternTest005
 * @tc.desc: Test the SetToolbarOptions function.
 * @tc.type: FUNC
 */
HWTEST_F(ToolBarTestNg, ToolBarPatternTest005, TestSize.Level1)
{
    auto frameNode =
        FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<NavToolbarPattern>());
    EXPECT_NE(frameNode, nullptr);
    auto navToolbarPattern = frameNode->GetPattern<NavToolbarPattern>();
    EXPECT_NE(navToolbarPattern, nullptr);
    NavigationToolbarOptions opt;
    opt.bgOptions.color = std::make_optional(FRONT_COLOR);
    navToolbarPattern->SetToolbarOptions(std::move(opt));
}

/**
 * @tc.name: ToolBarPatternTest006
 * @tc.desc: Test the SetDefaultBackgroundColorIfNeeded function.
 * @tc.type: FUNC
 */
HWTEST_F(ToolBarTestNg, ToolBarPatternTest006, TestSize.Level1)
{
    auto frameNode =
        FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<NavToolbarPattern>());
    EXPECT_NE(frameNode, nullptr);
    auto navToolbarPattern = frameNode->GetPattern<NavToolbarPattern>();
    EXPECT_NE(navToolbarPattern, nullptr);
    navToolbarPattern->options_.bgOptions.color = std::make_optional(FRONT_COLOR);
    navToolbarPattern->SetDefaultBackgroundColorIfNeeded(frameNode);
}

/**
 * @tc.name: ToolBarPatternTest007
 * @tc.desc: Test the InitLongPressEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(ToolBarTestNg, ToolBarPatternTest007, TestSize.Level1)
{
    auto frameNode =
        FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<NavToolbarPattern>());
    EXPECT_NE(frameNode, nullptr);
    auto navToolbarPattern = frameNode->GetPattern<NavToolbarPattern>();
    EXPECT_NE(navToolbarPattern, nullptr);

    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    auto imageNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    ASSERT_NE(imageNode, nullptr);
    auto textNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textNode, nullptr);

    auto barItemNode = BarItemNode::GetOrCreateBarItemNode(
            V2::BAR_ITEM_ETS_TAG, 1000, []() { return AceType::MakeRefPtr<Pattern>(); });
    barItemNode->SetIconNode(imageNode);
    barItemNode->SetTextNode(textNode);

    navToolbarPattern->InitLongPressEvent(gestureHub);
    auto longPressRecognizer = gestureHub->GetLongPressRecognizer();
    EXPECT_NE(longPressRecognizer, nullptr);
    EXPECT_NE(longPressRecognizer->onActionEnd_, nullptr);
}

/**
 * @tc.name: ToolBarPatternTest008
 * @tc.desc: Test the HandleLongPressActionEnd function.
 * @tc.type: FUNC
 */
HWTEST_F(ToolBarTestNg, ToolBarPatternTest008, TestSize.Level1)
{
    auto frameNode =
        FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<NavToolbarPattern>());
    EXPECT_NE(frameNode, nullptr);
    auto navToolbarPattern = frameNode->GetPattern<NavToolbarPattern>();
    EXPECT_NE(navToolbarPattern, nullptr);

    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    auto imageNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    ASSERT_NE(imageNode, nullptr);
    auto textNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textNode, nullptr);

    navToolbarPattern->dialogNode_ =
        FrameNode::CreateFrameNode(V2::DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<NavToolbarPattern>());
    ASSERT_NE(navToolbarPattern->dialogNode_, nullptr);
    navToolbarPattern->HandleLongPressActionEnd();
    EXPECT_EQ(navToolbarPattern->dialogNode_, nullptr);
}

/**
 * @tc.name: NavToolbarPatternOnModifyDone001
 * @tc.desc: Increase the coverage of NavToolbarPattern::OnModifyDone function.
 * @tc.type: FUNC
 */
HWTEST_F(ToolBarTestNg, NavToolbarPatternOnModifyDone001, TestSize.Level1)
{
    auto containerNode = FrameNode::GetOrCreateFrameNode(
        "Container", 101, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    ASSERT_NE(containerNode, nullptr);
    auto toolbarNode = NavToolbarNode::GetOrCreateToolbarNode(
        "Toolbar", 201, []() { return AceType::MakeRefPtr<NavToolbarPattern>(); });
    ASSERT_NE(toolbarNode, nullptr);
    toolbarNode->SetToolbarContainerNode(containerNode);
    auto navToolbarPattern = toolbarNode->GetPattern<NavToolbarPattern>();
    ASSERT_NE(navToolbarPattern, nullptr);
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    context->fontScale_ = AgingAdapationDialogUtil::GetDialogBigFontSizeScale() - 1.0f;
    EXPECT_TRUE(LessNotEqual(context->fontScale_, AgingAdapationDialogUtil::GetDialogBigFontSizeScale()));
    navToolbarPattern->OnModifyDone();

    context->fontScale_ = AgingAdapationDialogUtil::GetDialogBigFontSizeScale() + 1.0f;
    EXPECT_FALSE(LessNotEqual(context->fontScale_, AgingAdapationDialogUtil::GetDialogBigFontSizeScale()));
    navToolbarPattern->OnModifyDone();
}

/**
 * @tc.name: NavToolbarPatternInitDragEvent001
 * @tc.desc: Increase the coverage of NavToolbarPattern::InitDragEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(ToolBarTestNg, NavToolbarPatternInitDragEvent001, TestSize.Level1)
{
    auto containerNode = FrameNode::GetOrCreateFrameNode(
        "Container", 101, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    auto gestureHub = containerNode->GetOrCreateGestureEventHub();
    auto toolbarNode = NavToolbarNode::GetOrCreateToolbarNode(
        "Toolbar", 301, []() { return AceType::MakeRefPtr<NavToolbarPattern>(); });
    toolbarNode->SetToolbarContainerNode(containerNode);
    auto toolbarPattern = toolbarNode->GetPattern<NavToolbarPattern>();
    ASSERT_NE(toolbarPattern, nullptr);
    toolbarPattern->InitDragEvent(gestureHub);
    ASSERT_NE(gestureHub->GetDragEventActuator(), nullptr);
    ASSERT_NE(gestureHub->GetDragEventActuator()->userCallback_, nullptr);
    auto actionUpdate = gestureHub->GetDragEventActuator()->userCallback_->GetActionUpdateEventFunc();
    ASSERT_NE(actionUpdate, nullptr);
    GestureEvent info;
    auto barItem1 = BarItemNode::GetOrCreateBarItemNode(
        "BarItem", 201, []() { return AceType::MakeRefPtr<Pattern>(); });
    auto geometryNode = barItem1->GetGeometryNode();
    geometryNode->SetFrameWidth(100);
    geometryNode->SetFrameHeight(50);
    containerNode->children_.emplace_front(barItem1);
    EXPECT_EQ(toolbarPattern->dialogNode_, nullptr);
    actionUpdate(info);
    
    auto dialogNode = FrameNode::GetOrCreateFrameNode(
        "Dailog", 401, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    toolbarPattern->dialogNode_ = dialogNode;
    toolbarPattern->moveIndex_ = -1;
    EXPECT_NE(toolbarPattern->dialogNode_, nullptr);
    EXPECT_TRUE(toolbarPattern->moveIndex_.has_value());
    actionUpdate(info);

    toolbarPattern->dialogNode_ = dialogNode;
    toolbarPattern->moveIndex_ = std::nullopt;
    EXPECT_NE(toolbarPattern->dialogNode_, nullptr);
    EXPECT_FALSE(toolbarPattern->moveIndex_.has_value());
    actionUpdate(info);
}

/**
 * @tc.name: NavToolbarPatternShowDialogWithNode001
 * @tc.desc: Increase the coverage of NavToolbarPattern::ShowDialogWithNode function.
 * @tc.type: FUNC
 */
HWTEST_F(ToolBarTestNg, NavToolbarPatternShowDialogWithNode001, TestSize.Level1)
{
    ToolBarTestNg::MockPipelineContextGetTheme();
    auto toolbarNode = NavToolbarNode::GetOrCreateToolbarNode(
        "Toolbar", 301, []() { return AceType::MakeRefPtr<NavToolbarPattern>(); });
    auto toolbarPattern = toolbarNode->GetPattern<NavToolbarPattern>();
    ASSERT_NE(toolbarPattern, nullptr);
    auto barItem1 = BarItemNode::GetOrCreateBarItemNode(
        "BarItem", 201, []() { return AceType::MakeRefPtr<Pattern>(); });
    EXPECT_FALSE(barItem1->IsMoreItemNode());
    EXPECT_EQ(AceType::DynamicCast<FrameNode>(barItem1->GetTextNode()), nullptr);
    EXPECT_EQ(AceType::DynamicCast<FrameNode>(barItem1->GetIconNode()), nullptr);
    toolbarPattern->ShowDialogWithNode(barItem1);

    auto textNode = FrameNode::CreateFrameNode("Text", 0, AceType::MakeRefPtr<TextPattern>());
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    textLayoutProperty->propContent_ = "";
    barItem1->SetTextNode(textNode);
    auto imageNode = FrameNode::GetOrCreateFrameNode(
        "Image", 1, []() { return AceType::MakeRefPtr<ImagePattern>(); });
    barItem1->SetIconNode(imageNode);
    EXPECT_NE(AceType::DynamicCast<FrameNode>(barItem1->GetTextNode()), nullptr);
    ASSERT_TRUE(textLayoutProperty->GetContent().has_value());
    EXPECT_TRUE(textLayoutProperty->GetContent().value().empty());
    EXPECT_NE(AceType::DynamicCast<FrameNode>(barItem1->GetIconNode()), nullptr);
    EXPECT_NE(imageNode->GetTag(), V2::SYMBOL_ETS_TAG);
    toolbarPattern->ShowDialogWithNode(barItem1);

    textLayoutProperty->propContent_ = "test";
    imageNode->tag_ = V2::SYMBOL_ETS_TAG;
    ASSERT_TRUE(textLayoutProperty->GetContent().has_value());
    EXPECT_FALSE(textLayoutProperty->GetContent().value().empty());
    EXPECT_EQ(imageNode->GetTag(), V2::SYMBOL_ETS_TAG);
    toolbarPattern->ShowDialogWithNode(barItem1);

    barItem1->isMoreItemNode_ = true;
    AceApplicationInfo& applicationInfo = AceApplicationInfo::GetInstance();
    applicationInfo.apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TEN);
    EXPECT_TRUE(barItem1->IsMoreItemNode());
    EXPECT_FALSE(applicationInfo.GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE));
    toolbarPattern->ShowDialogWithNode(barItem1);

    applicationInfo.apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TWELVE);
    EXPECT_TRUE(applicationInfo.GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE));
    toolbarPattern->ShowDialogWithNode(barItem1);
}
} // namespace OHOS::Ace::NG