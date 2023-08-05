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
#include <cstdint>
#include <string>

#include "gtest/gtest.h"

#define protected public
#define private public
#include "core/components/select/select_theme.h"
#include "core/components/text_field/textfield_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/option/option_pattern.h"
#include "core/components_ng/pattern/select/select_pattern.h"
#include "core/components_ng/pattern/select/select_model_ng.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"
#include "core/components_ng/pattern/flex/flex_layout_property.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string OPTION_TEXT = "aaa";
const std::string OPTION_TEXT_2 = "BBB";
const std::string OPTION_TEXT_3 = "CCC";
const std::string INTERNAL_SOURCE = "$r('app.media.icon')";
const std::string FILE_SOURCE = "/common/icon.png";
const std::string DEFAULT_STR("2.0");
} // namespace

class SelectViewTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void SelectViewTestNg::SetUpTestCase()
{
    MockPipelineBase::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
}

void SelectViewTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
}

/**
 * @tc.name: SelectSetSpaceTest001
 * @tc.desc: setSpace
 * @tc.type: FUNC
 */
HWTEST_F(SelectViewTestNg, SelectSetSpaceTest001, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    
    auto select = FrameNode::GetOrCreateFrameNode(
        V2::SELECT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<SelectPattern>(); });
    ASSERT_NE(select, nullptr);

    auto row = FrameNode::GetOrCreateFrameNode(
        V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    ASSERT_NE(row, nullptr);

    auto text = FrameNode::GetOrCreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(text, nullptr);

    auto spinner = FrameNode::GetOrCreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(spinner, nullptr);

    text->MountToParent(row);
    spinner->MountToParent(row);
    row->MountToParent(select);
    ViewStackProcessor::GetInstance()->Push(select);

    selectModelInstance.SetSpace(Dimension(20.00, DimensionUnit::VP));
    ASSERT_FALSE(select->GetChildren().empty());
    row = FrameNode::GetFrameNode(select->GetFirstChild()->GetTag(), select->GetFirstChild()->GetId());
    ASSERT_NE(row, nullptr);
    auto rowProps = row->GetLayoutProperty<FlexLayoutProperty>();
    ASSERT_NE(rowProps, nullptr);
    ASSERT_TRUE(rowProps->GetSpace()->Value() == 20);
}

/**
 * @tc.name: SelectSetArrowPositionTest001
 * @tc.desc: Test SetArrowPosition
 * @tc.type: FUNC
 */
HWTEST_F(SelectViewTestNg, SelectSetArrowPositionTest001, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    
    auto select = FrameNode::GetOrCreateFrameNode(
        V2::SELECT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<SelectPattern>(); });
    ASSERT_NE(select, nullptr);

    auto row = FrameNode::GetOrCreateFrameNode(
        V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    ASSERT_NE(row, nullptr);

    auto text = FrameNode::GetOrCreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(text, nullptr);

    auto spinner = FrameNode::GetOrCreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(spinner, nullptr);

    text->MountToParent(row);
    spinner->MountToParent(row);
    row->MountToParent(select);
    ViewStackProcessor::GetInstance()->Push(select);

    selectModelInstance.SetArrowPosition(ArrowPosition::END);
    ASSERT_FALSE(select->GetChildren().empty());
    row = FrameNode::GetFrameNode(select->GetFirstChild()->GetTag(), select->GetFirstChild()->GetId());
    ASSERT_NE(row, nullptr);
    auto rowProps = row->GetLayoutProperty<FlexLayoutProperty>();
    ASSERT_STREQ(V2::ConvertFlexDirectionToStirng(rowProps->GetFlexDirection().value()).c_str(),
                    "FlexDirection.Row");

    selectModelInstance.SetArrowPosition(ArrowPosition::START);
    ASSERT_FALSE(select->GetChildren().empty());
    row = FrameNode::GetFrameNode(select->GetFirstChild()->GetTag(), select->GetFirstChild()->GetId());
    ASSERT_NE(row, nullptr);
    rowProps = row->GetLayoutProperty<FlexLayoutProperty>();
    ASSERT_STREQ(V2::ConvertFlexDirectionToStirng(rowProps->GetFlexDirection().value()).c_str(),
                    "FlexDirection.RowReverse");
}

/**
 * @tc.name: SelectSetArrowPositionTest002
 * @tc.desc: Test SetArrowPosition
 * @tc.type: FUNC
 */
HWTEST_F(SelectViewTestNg, SelectSetArrowPositionTest002, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE }, { OPTION_TEXT, INTERNAL_SOURCE },
        { OPTION_TEXT_2, INTERNAL_SOURCE } };
    selectModelInstance.Create(params);
    selectModelInstance.SetArrowPosition(ArrowPosition::END);
    selectModelInstance.SetSpace(Dimension(20.00, DimensionUnit::VP));
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_TRUE(select->GetChildren().empty());
}

/**
 * @tc.name: CreateMenu001
 * @tc.desc: Test create menu
 * @tc.type: FUNC
 */
HWTEST_F(SelectViewTestNg, CreateMenu001, TestSize.Level1)
{
    SelectModelNG selectModelInstance;

    std::vector<SelectParam> params = {{ OPTION_TEXT, FILE_SOURCE }};
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(100);
    selectModelInstance.Create(params);
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto pattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(pattern->GetMenuNode(), nullptr);

    // Create again
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(100);
    selectModelInstance.Create(params);
    select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    pattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(pattern->GetMenuNode(), nullptr);
}

/**
 * @tc.name: SelectSetMenuAlign001
 * @tc.desc: Test SetMenuAlign
 * @tc.type: FUNC
 */
HWTEST_F(SelectViewTestNg, SelectSetMenuAlign001, TestSize.Level1)
{
    SelectModelNG selectModelInstance;

    // create select
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE }, { OPTION_TEXT, INTERNAL_SOURCE },
        { OPTION_TEXT_2, INTERNAL_SOURCE } };
    selectModelInstance.Create(params);
    MenuAlign menuAlign;
    /**
     * @tc.cases: case1. verify the SetMenuAlign function.
     */
    selectModelInstance.SetMenuAlign(menuAlign);
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_TRUE(select->GetChildren().empty());
}

/**
 * @tc.name: SelectModel001
 * @tc.desc: Test Select Model
 * @tc.type: FUNC
 */
HWTEST_F(SelectViewTestNg, SelectModel001, TestSize.Level1)
{
    SelectModelNG selectModelInstance;

    std::vector<SelectParam> params = {{ OPTION_TEXT, FILE_SOURCE }};
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(100);
    selectModelInstance.Create(params);
    selectModelInstance.SetSelected(0);
    selectModelInstance.SetValue("select");
    selectModelInstance.SetFontSize(Dimension(20.00, DimensionUnit::VP));
    selectModelInstance.SetFontWeight(FontWeight::NORMAL);
    selectModelInstance.SetItalicFontStyle(Ace::FontStyle::NORMAL);
    selectModelInstance.SetFontColor(Color::BLACK);
    selectModelInstance.SetSelectedOptionBgColor(Color::BLACK);
    selectModelInstance.SetSelectedOptionFontSize(Dimension(20.00, DimensionUnit::VP));
    selectModelInstance.SetSelectedOptionFontWeight(FontWeight::NORMAL);
    selectModelInstance.SetSelectedOptionItalicFontStyle(Ace::FontStyle::NORMAL);
    selectModelInstance.SetSelectedOptionFontColor(Color::BLACK);
    selectModelInstance.SetOptionBgColor(Color::BLACK);
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto pattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(pattern->GetMenuNode(), nullptr);
}

/**
 * @tc.name: SelectModel002
 * @tc.desc: Test Select Model
 * @tc.type: FUNC
 */
HWTEST_F(SelectViewTestNg, SelectModel002, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    SelectEvent eventOnSelect = [](int32_t intValue, const std::string& isSelect) {};
    CalcDimension width = 20.0_vp;
    CalcDimension height = 20.0_vp;
    CalcDimension top = 20.0_vp;
    CalcDimension bottom = 20.0_vp;
    CalcDimension left = 20.0_vp;
    CalcDimension right = 20.0_vp;

    std::vector<SelectParam> params = {{ OPTION_TEXT, FILE_SOURCE }};
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(100);
    selectModelInstance.SetOptionFontSize(Dimension(20.00, DimensionUnit::VP));
    selectModelInstance.SetOptionFontWeight(FontWeight::NORMAL);
    selectModelInstance.SetOptionItalicFontStyle(Ace::FontStyle::NORMAL);
    selectModelInstance.SetOptionFontColor(Color::BLACK);
    selectModelInstance.SetOnSelect(std::move(eventOnSelect));
    selectModelInstance.SetWidth(width);
    selectModelInstance.SetHeight(height);
    selectModelInstance.SetSize(width, height);
    selectModelInstance.SetPaddings(top, bottom, left, right);
    selectModelInstance.SetPadding(CalcDimension(20.00, DimensionUnit::VP));
    selectModelInstance.SetPaddingLeft(CalcDimension(20.00, DimensionUnit::VP));
    selectModelInstance.SetPaddingTop(CalcDimension(20.00, DimensionUnit::VP));
    selectModelInstance.SetPaddingRight(CalcDimension(20.00, DimensionUnit::VP));
    selectModelInstance.SetPaddingBottom(CalcDimension(20.00, DimensionUnit::VP));
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto pattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(pattern->GetMenuNode(), nullptr);
}

/**
 * @tc.name: SelectModel003
 * @tc.desc: Test Select Model
 * @tc.type: FUNC
 */
HWTEST_F(SelectViewTestNg, SelectModel003, TestSize.Level1)
{
    SelectModelNG selectModelInstance;
    SelectEvent eventOnSelect = [](int32_t intValue, const std::string& isSelect) {};
    CalcDimension width = -20.0_vp;
    CalcDimension height = -20.0_vp;
    CalcDimension top = -20.0_vp;
    CalcDimension bottom = -20.0_vp;
    CalcDimension left = -20.0_vp;
    CalcDimension right = -20.0_vp;

    std::vector<SelectParam> params = {{ OPTION_TEXT, FILE_SOURCE }};
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(100);
    
    selectModelInstance.SetWidth(width);
    selectModelInstance.SetHeight(height);
    selectModelInstance.SetSize(width, height);
    selectModelInstance.SetPaddings(top, bottom, left, right);
    selectModelInstance.SetPadding(CalcDimension(20.00, DimensionUnit::VP));
    selectModelInstance.SetPaddingLeft(CalcDimension(20.00, DimensionUnit::VP));
    selectModelInstance.SetPaddingTop(CalcDimension(20.00, DimensionUnit::VP));
    selectModelInstance.SetPaddingRight(CalcDimension(20.00, DimensionUnit::VP));
    selectModelInstance.SetPaddingBottom(CalcDimension(20.00, DimensionUnit::VP));
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto pattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(pattern->GetMenuNode(), nullptr);
}
/**
 * @tc.name: SelectModel004
 * @tc.desc: Test Select Model
 * @tc.type: FUNC
 */
HWTEST_F(SelectViewTestNg, SelectModel004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectModelInstance.
     */
    SelectModelNG selectModelInstance;
    SelectEvent eventOnSelect = [](int32_t intValue, const std::string& isSelect) {};
    
    std::vector<SelectParam> params = {{ OPTION_TEXT, FILE_SOURCE }};
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(100);
    selectModelInstance.Create(params);
    /**
     * @tc.steps: step2. initialize paddings.
     * @tc.steps: the values of select which is setted successfully.
     */
    CalcDimension calcDimension(DEFAULT_STR);
    CalcDimension width = -20.0_vp;
    CalcDimension height = -20.0_vp;
    selectModelInstance.SetSize(width, height);
    selectModelInstance.SetPaddingLeft(CalcDimension(DEFAULT_STR));
    selectModelInstance.SetPaddingTop(CalcDimension(DEFAULT_STR));
    selectModelInstance.SetPaddingRight(CalcDimension(DEFAULT_STR));
    selectModelInstance.SetPaddingBottom(CalcDimension(DEFAULT_STR));
    selectModelInstance.SetPaddings(calcDimension, calcDimension, calcDimension, calcDimension);
    selectModelInstance.SetPadding(calcDimension);
    auto select = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(select, nullptr);
    auto pattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(pattern, nullptr);
    auto menu = pattern->GetMenuNode();
    ASSERT_NE(menu, nullptr);
    EXPECT_EQ(width.Value(), 0.0);
    EXPECT_EQ(height.Value(), 0.0);
}
} // namespace OHOS::Ace::NG