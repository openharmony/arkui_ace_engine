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
#include <cstdint>
#include <optional>
#include <string>

#include "gtest/gtest.h"

#define protected public
#define private public
#include "core/components/select/select_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/option/option_pattern.h"
#include "core/components_ng/pattern/select/select_pattern.h"
#include "core/components_ng/pattern/select/select_view.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const int32_t OFFSETX = 10;
const int32_t OFFSETY = 20;
const std::string OPTION_TEXT = "aaa";
const std::string OPTION_TEXT_2 = "BBB";
const std::string OPTION_TEXT_3 = "CCC";
const std::string INTERNAL_SOURCE = "$r('app.media.icon')";
const std::string FILE_SOURCE = "/common/icon.png";
const std::string TEXT_VALUE = "test";
const CalcLength MARGIN_LENGTH = CalcLength("8vp");
const CalcSize TEXT_IDEAL_SIZE = CalcSize(CalcLength("50vp"), std::nullopt);
constexpr float FULL_SCREEN_WIDTH = 720.0f;
constexpr float FULL_SCREEN_HEIGHT = 1136.0f;
const SizeF FULL_SCREEN_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
} // namespace

class SelectPropertyTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void SelectPropertyTestNg::SetUpTestCase()
{
    MockPipelineBase::SetUp();
}

void SelectPropertyTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
}

/**
 * @tc.name: SelectLayoutPropertyTest001
 * @tc.desc: Create Select.
 * @tc.type: FUNC
 */
HWTEST_F(SelectPropertyTestNg, SelectLayoutPropertyTest001, TestSize.Level1)
{
    // set buttonTheme to themeManager before using themeManager to get buttonTheme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));

    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE }, { OPTION_TEXT, INTERNAL_SOURCE },
        { OPTION_TEXT_2, INTERNAL_SOURCE } };
    SelectView::Create(params);
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_TRUE(select && select->GetTag() == V2::SELECT_ETS_TAG);
    auto pattern = select->GetPattern<SelectPattern>();
    EXPECT_TRUE(pattern);

    auto options = pattern->GetOptions();
    EXPECT_EQ(options.size(), params.size());
    for (size_t i = 0; i < options.size(); ++i) {
        auto optionPattern = options[i]->GetPattern<OptionPattern>();
        EXPECT_EQ(optionPattern->GetText(), params[i].first);
    }
}

/**
 * @tc.name: SelectLayoutPropertyTest002
 * @tc.desc: Test Select OnDirtyLayoutWrapperSwap.
 * @tc.type: FUNC
 */
HWTEST_F(SelectPropertyTestNg, SelectLayoutPropertyTest002, TestSize.Level1)
{
    // set buttonTheme to themeManager before using themeManager to get buttonTheme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));

    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE }, { OPTION_TEXT, INTERNAL_SOURCE },
        { OPTION_TEXT_2, INTERNAL_SOURCE } };
    SelectView::Create(params);
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_TRUE(select && select->GetTag() == V2::SELECT_ETS_TAG);
    auto pattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(pattern, nullptr);

    DirtySwapConfig config;
    config.skipMeasure = true;
    auto layoutWrapper = select->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    EXPECT_FALSE(pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config));
}

/**
 * @tc.name: SelectLayoutPropertyTest003
 * @tc.desc: Test Select Layout Algorithm MeasureAndGetSize width.
 * @tc.type: FUNC
 */
HWTEST_F(SelectPropertyTestNg, SelectLayoutPropertyTest003, TestSize.Level1)
{
    auto text = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_TRUE(text);

    auto textProps = text->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_TRUE(textProps);
    MarginProperty margin;
    margin.left = MARGIN_LENGTH;
    textProps->UpdateMargin(margin);
    textProps->UpdateUserDefinedIdealSize(TEXT_IDEAL_SIZE);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(text, geometryNode, text->GetLayoutProperty());

    LayoutConstraintF constraint;
    constraint.maxSize = FULL_SCREEN_SIZE;
    constraint.percentReference = FULL_SCREEN_SIZE;

    auto layoutAlgorithm = AceType::MakeRefPtr<SelectLayoutAlgorithm>();
    auto size = layoutAlgorithm->MeasureAndGetSize(layoutWrapper, constraint);
    auto expectWidth =
        MARGIN_LENGTH.GetDimension().ConvertToPx() + TEXT_IDEAL_SIZE.Width()->GetDimension().ConvertToPx();
    EXPECT_EQ(size.Width(), static_cast<float>(expectWidth));
}

/**
 * @tc.name: SelectSetMenuAlign001
 * @tc.desc: Test SelectSetMenuAlign
 * @tc.type: FUNC
 */
HWTEST_F(SelectPropertyTestNg, SelectSetMenuAlign001, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));

    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE }, { OPTION_TEXT, INTERNAL_SOURCE },
        { OPTION_TEXT_2, INTERNAL_SOURCE } };
    SelectView::Create(params);
    MenuAlign menuAlign;
    menuAlign.alignType = MenuAlignType::END;
    menuAlign.offset = DimensionOffset(Dimension(OFFSETX, DimensionUnit::VP), Dimension(OFFSETY, DimensionUnit::VP));
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_TRUE(select && select->GetTag() == V2::SELECT_ETS_TAG);
    auto selectPattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    selectPattern->SetMenuAlign(menuAlign);
    auto menuAlign2 = selectPattern->menuAlign_.alignType;
    auto menuAlign3 = selectPattern->menuAlign_.offset;
    ASSERT_EQ(menuAlign.alignType, menuAlign2);
    ASSERT_EQ(menuAlign.offset, menuAlign3);
}
} // namespace OHOS::Ace::NG