/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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
#include "core/common/ime/text_input_action.h"

#define protected public
#define private public
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"

#include "core/animation/curves.h"
#include "core/components/button/button_theme.h"
#include "core/components/common/properties/edge.h"
#include "core/components/search/search_theme.h"
#include "core/components/common/layout/constants.h"
#include "core/components/text_field/textfield_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_render_property.h"
#include "core/components_ng/pattern/search/search_event_hub.h"
#include "core/components_ng/pattern/search/search_layout_algorithm.h"
#include "core/components_ng/pattern/search/search_layout_property.h"
#include "core/components_ng/pattern/search/search_model_ng.h"
#include "core/components_ng/pattern/search/search_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text_field/text_field_event_hub.h"
#include "core/components_ng/pattern/text_field/text_field_layout_algorithm.h"
#include "core/components_ng/pattern/text_field/text_field_layout_property.h"
#include "core/components_ng/pattern/text_field/text_field_paint_property.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "core/components/common/properties/text_style_parser.h"
#undef protected
#undef private

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace;

namespace OHOS::Ace::NG {
namespace {
const InspectorFilter filter;
constexpr float COLUMN_HEIGHT = 200.0f;
constexpr float FULL_SCREEN_WIDTH = 720.0f;
constexpr float FULL_SCREEN_HEIGHT = 1136.0f;
constexpr float ZERO = 0.0f;
const SizeF CONTAINER_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
constexpr int32_t TEXTFIELD_INDEX = 0;
const std::string EMPTY_VALUE;
const std::u16string EMPTY_VALUE_U16;
const std::string PLACEHOLDER = "DEFAULT PLACEHOLDER";
const std::u16string PLACEHOLDER_U16 = u"DEFAULT PLACEHOLDER";
const std::string SEARCH_SVG = "resource:///ohos_search.svg";
const std::string DEFAULT_TEXT = "abcdefghijklmnopqrstuvwxyz";
} // namespace

class SearchDecorationTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
protected:
    std::pair<RefPtr<FrameNode>, RefPtr<LayoutWrapperNode>> CreateColumn();
    PaddingProperty CreatePadding(float left, float top, float right, float bottom);
};

void SearchDecorationTestNg::SetUpTestSuite()
{
    MockContainer::SetUp();
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    auto textFieldTheme = AceType::MakeRefPtr<TextFieldTheme>();
    auto searchTheme = AceType::MakeRefPtr<SearchTheme>();
    searchTheme->iconHeight_ = 24.0_px;
    searchTheme->height_ = 60.0_px;
    searchTheme->searchButtonTextColor_ = Color::RED;
    searchTheme->placeholderColor_ = Color::RED;
    textFieldTheme->bgColor_ = Color::RED;
    auto iconTheme = AceType::MakeRefPtr<IconTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([=](ThemeType type) -> RefPtr<Theme> {
        if (type == SearchTheme::TypeId()) {
            return searchTheme;
        }
        if (type == IconTheme::TypeId()) {
            return iconTheme;
        }
        return textFieldTheme;
    });
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly([=](ThemeType type, int id) -> RefPtr<Theme> {
        if (type == SearchTheme::TypeId()) {
            return searchTheme;
        }
        if (type == IconTheme::TypeId()) {
            return iconTheme;
        }
        return textFieldTheme;
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(EMPTY_VALUE_U16, PLACEHOLDER_U16, SEARCH_SVG);
}

void SearchDecorationTestNg::TearDownTestSuite()
{
    MockContainer::TearDown();
    MockPipelineContext::TearDown();
}

std::pair<RefPtr<FrameNode>, RefPtr<LayoutWrapperNode>> SearchDecorationTestNg::CreateColumn()
{
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto columnFrameNode =
        FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, nodeId, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    EXPECT_NE(columnFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(columnFrameNode, geometryNode, columnFrameNode->GetLayoutProperty());

    auto columnLayoutPattern = columnFrameNode->GetPattern<LinearLayoutPattern>();
    EXPECT_NE(columnLayoutPattern, nullptr);
    auto rowLayoutProperty = columnLayoutPattern->GetLayoutProperty<LinearLayoutProperty>();
    EXPECT_NE(rowLayoutProperty, nullptr);

    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FULL_SCREEN_WIDTH), CalcLength(COLUMN_HEIGHT)));
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;

    PaddingProperty noPadding = CreatePadding(ZERO, ZERO, ZERO, ZERO);
    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    return { columnFrameNode, layoutWrapper };
}

PaddingProperty SearchDecorationTestNg::CreatePadding(float left, float top, float right, float bottom)
{
    PaddingProperty padding;
    padding.left = CalcLength(left);
    padding.right = CalcLength(right);
    padding.top = CalcLength(top);
    padding.bottom = CalcLength(bottom);
    return padding;
}

/**
 * @tc.name: LetterSpacingPattern002
 * @tc.desc: test search letterSpacing dump
 * @tc.type: FUNC
 */
HWTEST_F(SearchDecorationTestNg, LetterSpacingPattern002, TestSize.Level1)
{
    /**
     * @tc.step: step1. create frameNode and pattern.
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.SetCancelButtonStyle(CancelButtonStyle::CONSTANT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    ASSERT_NE(textFieldFrameNode, nullptr);
    auto textFieldLayoutProperty = textFieldFrameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SearchLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    pattern->UpdateChangeEvent(u"search");
    pattern->ToJsonValue(json, filter);
    EXPECT_EQ(layoutProperty->GetCancelButtonStyle(), CancelButtonStyle::CONSTANT);

    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    /**
     * @tc.step: step2.  set letterSpacing 1.0_fp.
     */
    searchModelInstance.SetLetterSpacing(1.0_fp);
    frameNode->MarkModifyDone();
    /**
     * @tc.step: step3. test letterSpacing
     */
    pattern->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    EXPECT_EQ(textFieldLayoutProperty->GetLetterSpacing(), 1.0_fp);
}

/**
 * @tc.name: LineHeightPattern002
 * @tc.desc: test search lineHeight dump
 * @tc.type: FUNC
 */
HWTEST_F(SearchDecorationTestNg, LineHeightPattern002, TestSize.Level1)
{
    /**
     * @tc.step: step1. create frameNode and pattern.
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.SetCancelButtonStyle(CancelButtonStyle::CONSTANT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    ASSERT_NE(textFieldFrameNode, nullptr);
    auto textFieldLayoutProperty = textFieldFrameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SearchLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    pattern->UpdateChangeEvent(u"search");
    pattern->ToJsonValue(json, filter);
    EXPECT_EQ(layoutProperty->GetCancelButtonStyle(), CancelButtonStyle::CONSTANT);

    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    /**
     * @tc.step: step2.  set lineHeight 2.0_fp.
     */
    searchModelInstance.SetLineHeight(2.0_fp);
    frameNode->MarkModifyDone();
    /**
     * @tc.step: step3. test lineHeight
     */
    pattern->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    EXPECT_EQ(textFieldLayoutProperty->GetLineHeight(), 2.0_fp);
}

/**
 * @tc.name: TextDecorationPattern002
 * @tc.desc: test search decoration dump
 * @tc.type: FUNC
 */
HWTEST_F(SearchDecorationTestNg, TextDecorationPattern002, TestSize.Level1)
{
    /**
     * @tc.step: step1. create frameNode and pattern.
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.SetCancelButtonStyle(CancelButtonStyle::CONSTANT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    ASSERT_NE(textFieldFrameNode, nullptr);
    auto textFieldLayoutProperty = textFieldFrameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SearchLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    pattern->UpdateChangeEvent(u"search");
    pattern->ToJsonValue(json, filter);
    EXPECT_EQ(layoutProperty->GetCancelButtonStyle(), CancelButtonStyle::CONSTANT);

    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    /**
     * @tc.step: step2.  set decoration.
     */
    searchModelInstance.SetTextDecoration(Ace::TextDecoration::UNDERLINE);
    frameNode->MarkModifyDone();
    searchModelInstance.SetTextDecorationColor(Color::BLUE);
    frameNode->MarkModifyDone();
    searchModelInstance.SetTextDecorationStyle(Ace::TextDecorationStyle::DASHED);
    frameNode->MarkModifyDone();
    /**
     * @tc.step: step3. test decoration
     */
    pattern->ToJsonValue(json, filter);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    EXPECT_EQ(textFieldLayoutProperty->GetTextDecoration(), Ace::TextDecoration::UNDERLINE);
    EXPECT_EQ(textFieldLayoutProperty->GetTextDecorationColor(), Color::BLUE);
    EXPECT_EQ(textFieldLayoutProperty->GetTextDecorationStyle(), Ace::TextDecorationStyle::DASHED);
}
} // namespace OHOS::Ace::NG
