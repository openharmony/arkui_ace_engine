/*
 * Copyright (c) 2023 iSoftStone Information Technology (Group) Co.,Ltd.
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

#include "core/common/resource/resource_parse_utils.h"
#include "core/components/select/select_theme.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_model_ng.h"
#include "test/mock/base/mock_system_properties.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
void ViewAbstractTestFiveNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->pipelineContext_ = PipelineBase::GetCurrentContext();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    PipelineBase::GetCurrentContext()->SetThemeManager(themeManager);
    PipelineBase::GetCurrentContext()->SetEventManager(AceType::MakeRefPtr<EventManager>());
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<PopupTheme>()));
}

void ViewAbstractTestFiveNg::TearDownTestSuite()
{
    MockContainer::Current()->pipelineContext_ = nullptr;
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: CreateWithDimensionResourceObj001
 * @tc.desc: Test CreateWithDimensionResourceObj of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFiveNg, CreateWithDimensionResourceObj001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frame node and initialize components.
     * @tc.expected: step1. Frame node and related components are created successfully.
     */
    const RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<BubblePattern>());
    ASSERT_NE(frameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(frameNode);

    auto pattern = frameNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create dimension resource object and configure popup parameters.
     * @tc.expected: step2. Dimension resource object and popup parameters are initialized correctly.
     */
    std::vector<ResourceObjectParams> params = { { "", ResourceObjectParamType::NONE } };
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(0, 10007, params, "", "", 0);
    ASSERT_NE(resObj, nullptr);

    RefPtr<PopupParam> param = AceType::MakeRefPtr<PopupParam>();
    ASSERT_NE(param, nullptr);

    param->SetWidthResourceObject(resObj);
    param->SetArrowWidthResourceObject(resObj);
    param->SetArrowHeightResourceObject(resObj);

    /**
     * @tc.steps: step3. Test CreateWithResourceObj for width dimension resource.
     * @tc.expected: step3. Width dimension resource is applied and type string is correct.
     */
    PopupOptionsType type = POPUP_OPTIONTYPE_WIDTH;
    auto widthResourceObject = param->GetWidthResourceObject();
    ASSERT_NE(widthResourceObject, nullptr);
    viewAbstractModelNG.CreateWithResourceObj(frameNode, widthResourceObject, type);
    pattern->OnColorModeChange(1);
    auto widthStr = viewAbstractModelNG.PopupOptionTypeStr(type);
    EXPECT_EQ(widthStr, "width");

    /**
     * @tc.steps: step4. Test CreateWithResourceObj for arrow width dimension resource.
     * @tc.expected: step4. Arrow width dimension resource is applied and type string is correct.
     */
    type = POPUP_OPTIONTYPE_ARROWWIDTH;
    auto arrowWidthResourceObject = param->GetArrowWidthResourceObject();
    ASSERT_NE(arrowWidthResourceObject, nullptr);
    viewAbstractModelNG.CreateWithResourceObj(frameNode, arrowWidthResourceObject, type);
    pattern->OnColorModeChange(1);
    auto arrowWidthStr = viewAbstractModelNG.PopupOptionTypeStr(type);
    EXPECT_EQ(arrowWidthStr, "arrowWidth");

    /**
     * @tc.steps: step5. Test CreateWithResourceObj for arrow height dimension resource.
     * @tc.expected: step5. Arrow height dimension resource is applied and type string is correct.
     */
    type = POPUP_OPTIONTYPE_ARROWHEIGHT;
    auto arrowHeighResourceObject = param->GetArrowHeightResourceObject();
    ASSERT_NE(arrowHeighResourceObject, nullptr);
    viewAbstractModelNG.CreateWithResourceObj(frameNode, arrowHeighResourceObject, type);
    pattern->OnColorModeChange(1);
    auto arrowHeighStr = viewAbstractModelNG.PopupOptionTypeStr(type);
    EXPECT_EQ(arrowHeighStr, "arrowHeight");
}

/**
 * @tc.name: CreateWithDimensionResourceObj002
 * @tc.desc: Test CreateWithDimensionResourceObj of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFiveNg, CreateWithDimensionResourceObj002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frame node and initialize components.
     * @tc.expected: step1. Frame node and related components are created successfully.
     */
    const RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<BubblePattern>());
    ASSERT_NE(frameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(frameNode);

    auto pattern = frameNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create dimension resource object and configure popup parameters.
     * @tc.expected: step2. Dimension resource object and popup parameters are initialized correctly.
     */
    std::vector<ResourceObjectParams> params = { { "", ResourceObjectParamType::NONE } };
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(0, 10007, params, "", "", 0);
    ASSERT_NE(resObj, nullptr);

    RefPtr<PopupParam> param = AceType::MakeRefPtr<PopupParam>();
    ASSERT_NE(param, nullptr);

    param->SetRadiusResourceObject(resObj);
    param->SetOutlineWidthObject(resObj);
    param->SetBorderWidthObject(resObj);

    /**
     * @tc.steps: step3. Test CreateWithResourceObj for radius dimension resource.
     * @tc.expected: step3. Radius dimension resource is applied and type string is correct.
     */
    PopupOptionsType type = POPUP_OPTIONTYPE_RADIUS;
    auto radiusResourceObject = param->GetRadiusResourceObject();
    ASSERT_NE(radiusResourceObject, nullptr);
    viewAbstractModelNG.CreateWithResourceObj(frameNode, radiusResourceObject, type);
    pattern->OnColorModeChange(1);
    auto radiusStr = viewAbstractModelNG.PopupOptionTypeStr(type);
    EXPECT_EQ(radiusStr, "radius");

    /**
     * @tc.steps: step4. Test CreateWithResourceObj for outline width dimension resource.
     * @tc.expected: step4. Outline width dimension resource is applied and type string is correct.
     */
    type = POPUP_OPTIONTYPE_OUTLINEWIDTH;
    auto outlineWidthResourceObject = param->GetOutlineWidthResourceObject();
    ASSERT_NE(outlineWidthResourceObject, nullptr);
    viewAbstractModelNG.CreateWithResourceObj(frameNode, outlineWidthResourceObject, type);
    pattern->OnColorModeChange(1);
    auto outlineWidthStr = viewAbstractModelNG.PopupOptionTypeStr(type);
    EXPECT_EQ(outlineWidthStr, "outlineWidth");

    /**
     * @tc.steps: step5. Test CreateWithResourceObj for border width dimension resource.
     * @tc.expected: step5. Border width dimension resource is applied and type string is correct.
     */
    type = POPUP_OPTIONTYPE_BORDERWIDTH;
    auto borderWidthResourceObject = param->GetBorderWidthResourceObject();
    ASSERT_NE(borderWidthResourceObject, nullptr);
    viewAbstractModelNG.CreateWithResourceObj(frameNode, borderWidthResourceObject, type);
    pattern->OnColorModeChange(1);
    auto borderWidthStr = viewAbstractModelNG.PopupOptionTypeStr(type);
    EXPECT_EQ(borderWidthStr, "borderWidth");
}

/**
 * @tc.name: CreateWithDimensionResourceObj003
 * @tc.desc: Test CreateWithDimensionResourceObj of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFiveNg, CreateWithDimensionResourceObj003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frame node and initialize components.
     * @tc.expected: step1. Frame node and related components are created successfully.
     */
    const RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<BubblePattern>());
    ASSERT_NE(frameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(frameNode);

    auto pattern = frameNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create default resource object and configure popup parameters.
     * @tc.expected: step2. Default resource object and popup parameters are initialized correctly.
     */
    RefPtr<ResourceObject> defaultResObj = AceType::MakeRefPtr<ResourceObject>("", "", 0);
    ASSERT_NE(defaultResObj, nullptr);

    RefPtr<PopupParam> param = AceType::MakeRefPtr<PopupParam>();
    ASSERT_NE(param, nullptr);

    param->SetWidthResourceObject(defaultResObj);
    param->SetArrowWidthResourceObject(defaultResObj);
    param->SetArrowHeightResourceObject(defaultResObj);

    /**
     * @tc.steps: step3. Test CreateWithResourceObj for width dimension with default resource.
     * @tc.expected: step3. Width dimension resource is applied and type string is correct.
     */
    PopupOptionsType type = POPUP_OPTIONTYPE_WIDTH;
    auto defaultWidthResourceObject = param->GetWidthResourceObject();
    ASSERT_NE(defaultWidthResourceObject, nullptr);
    viewAbstractModelNG.CreateWithResourceObj(frameNode, defaultWidthResourceObject, type);
    pattern->OnColorModeChange(1);
    auto widthStr = viewAbstractModelNG.PopupOptionTypeStr(type);
    EXPECT_EQ(widthStr, "width");

    /**
     * @tc.steps: step4. Test CreateWithResourceObj for arrow width dimension with default resource.
     * @tc.expected: step4. Arrow width dimension resource is applied and type string is correct.
     */
    type = POPUP_OPTIONTYPE_ARROWWIDTH;
    auto defaultArrowWidthResourceObject = param->GetArrowWidthResourceObject();
    ASSERT_NE(defaultArrowWidthResourceObject, nullptr);
    viewAbstractModelNG.CreateWithResourceObj(frameNode, defaultArrowWidthResourceObject, type);
    pattern->OnColorModeChange(1);
    auto arrowWidthStr = viewAbstractModelNG.PopupOptionTypeStr(type);
    EXPECT_EQ(arrowWidthStr, "arrowWidth");

    /**
     * @tc.steps: step5. Test CreateWithResourceObj for arrow height dimension with default resource.
     * @tc.expected: step5. Arrow height dimension resource is applied and type string is correct.
     */
    type = POPUP_OPTIONTYPE_ARROWHEIGHT;
    auto defaultArrowHeightResourceObject = param->GetArrowHeightResourceObject();
    ASSERT_NE(defaultArrowHeightResourceObject, nullptr);
    viewAbstractModelNG.CreateWithResourceObj(frameNode, defaultArrowHeightResourceObject, type);
    pattern->OnColorModeChange(1);
    auto arrowHeighStr = viewAbstractModelNG.PopupOptionTypeStr(type);
    EXPECT_EQ(arrowHeighStr, "arrowHeight");
}

/**
 * @tc.name: CreateWithDimensionResourceObj004
 * @tc.desc: Test CreateWithDimensionResourceObj of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFiveNg, CreateWithDimensionResourceObj004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frame node and initialize components.
     * @tc.expected: step1. Frame node and related components are created successfully.
     */
    const RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<BubblePattern>());
    ASSERT_NE(frameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(frameNode);

    auto pattern = frameNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create default resource object and configure popup parameters.
     * @tc.expected: step2. Default resource object and popup parameters are initialized correctly.
     */
    RefPtr<ResourceObject> defaultResObj = AceType::MakeRefPtr<ResourceObject>("", "", 0);
    ASSERT_NE(defaultResObj, nullptr);

    RefPtr<PopupParam> param = AceType::MakeRefPtr<PopupParam>();
    ASSERT_NE(param, nullptr);

    param->SetRadiusResourceObject(defaultResObj);
    param->SetOutlineWidthObject(defaultResObj);
    param->SetBorderWidthObject(defaultResObj);

    /**
     * @tc.steps: step3. Test CreateWithResourceObj for radius dimension with default resource.
     * @tc.expected: step3. Radius dimension resource is applied and type string is correct.
     */
    PopupOptionsType type = POPUP_OPTIONTYPE_RADIUS;
    auto defaultRadiusResourceObject = param->GetRadiusResourceObject();
    ASSERT_NE(defaultRadiusResourceObject, nullptr);
    viewAbstractModelNG.CreateWithResourceObj(frameNode, defaultRadiusResourceObject, type);
    pattern->OnColorModeChange(1);
    auto radiusStr = viewAbstractModelNG.PopupOptionTypeStr(type);
    EXPECT_EQ(radiusStr, "radius");

    /**
     * @tc.steps: step4. Test CreateWithResourceObj for outline width dimension with default resource.
     * @tc.expected: step4. Outline width dimension resource is applied and type string is correct.
     */
    type = POPUP_OPTIONTYPE_OUTLINEWIDTH;
    auto defaultOutlineWidthObject = param->GetOutlineWidthResourceObject();
    ASSERT_NE(defaultOutlineWidthObject, nullptr);
    viewAbstractModelNG.CreateWithResourceObj(frameNode, defaultOutlineWidthObject, type);
    pattern->OnColorModeChange(1);
    auto outlineWidthStr = viewAbstractModelNG.PopupOptionTypeStr(type);
    EXPECT_EQ(outlineWidthStr, "outlineWidth");

    /**
     * @tc.steps: step5. Test CreateWithResourceObj for border width dimension with default resource.
     * @tc.expected: step5. Border width dimension resource is applied and type string is correct.
     */
    type = POPUP_OPTIONTYPE_BORDERWIDTH;
    auto defaultBorderWidthObject = param->GetBorderWidthResourceObject();
    ASSERT_NE(defaultBorderWidthObject, nullptr);
    viewAbstractModelNG.CreateWithResourceObj(frameNode, defaultBorderWidthObject, type);
    pattern->OnColorModeChange(1);
    auto borderWidthStr = viewAbstractModelNG.PopupOptionTypeStr(type);
    EXPECT_EQ(borderWidthStr, "borderWidth");

    /**
     * @tc.steps: step6. Test CreateWithResourceObj with invalid type using default resource.
     * @tc.expected: step6. Type string for invalid type is empty.
     */
    type = POPUP_OPTIONTYPE_OFFSETDX;
    viewAbstractModelNG.CreateWithResourceObj(frameNode, defaultResObj, type);
    pattern->OnColorModeChange(1);
    auto defaultStr = viewAbstractModelNG.PopupOptionTypeStr(type);
    EXPECT_EQ(defaultStr, "");
}
} // namespace OHOS::Ace::NG