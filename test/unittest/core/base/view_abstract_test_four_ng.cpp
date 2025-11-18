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
void ViewAbstractTestFourNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->pipelineContext_ = PipelineBase::GetCurrentContext();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    PipelineBase::GetCurrentContext()->SetThemeManager(themeManager);
    PipelineBase::GetCurrentContext()->SetEventManager(AceType::MakeRefPtr<EventManager>());
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<PopupTheme>()));
}

void ViewAbstractTestFourNg::TearDownTestSuite()
{
    MockContainer::Current()->pipelineContext_ = nullptr;
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: SetMask
 * @tc.desc: Test SetMask of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFourNg, ViewAbstractTestNg0068, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<BasicShape> basicShape = AceType::MakeRefPtr<BasicShape>(BasicShapeType::CIRCLE);
    RefPtr<NG::ProgressMaskProperty> progressMaskProperty = AceType::MakeRefPtr<NG::ProgressMaskProperty>();
    progressMaskProperty->SetMaxValue(200.0f);
    progressMaskProperty->SetColor(Color(0xffff0000));
    progressMaskProperty->SetValue(1.0f);
    auto target = frameNode->GetRenderContext();
    ASSERT_NE(target, nullptr);
    ViewAbstract::SetProgressMask(frameNode, progressMaskProperty);
    g_isConfigChangePerform = true;

    ViewStackProcessor::GetInstance()->visualState_ = std::nullopt;
    ViewAbstract::SetMask(basicShape);
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    EXPECT_TRUE(result);

    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    g_isConfigChangePerform = false;
    std::string maskShape = pattern->GetResCacheMapByKey("maskShape");
    EXPECT_EQ(maskShape, "");
}

/**
 * @tc.name: ViewAbstractTest069
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFourNg, ViewAbstractTest069, TestSize.Level1)
{
    /**
     * @tc.steps: step1.Using static methods to set component properties
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern();
    ASSERT_NE(pattern, nullptr);

    std::string bundleName = "com.example.test";
    std::string moduleName = "entry";
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(bundleName, moduleName, 0);
    ViewAbstract::SetWidth(resObj);
    ViewAbstract::SetHeight(resObj);
    ViewAbstract::SetMinWidth(resObj);
    ViewAbstract::SetMinHeight(resObj);
    ViewAbstract::SetMaxWidth(resObj);
    ViewAbstract::SetMaxHeight(resObj);
    pattern->OnColorModeChange(1);
    ViewAbstract::ResetAspectRatio();
    ViewAbstract::SetDrawModifier(nullptr);

    /**
     * @tc.expected: Successfully set various properties of the top node on the stack
     */
    CalcDimension result;
    ResourceParseUtils::ParseResDimensionVpNG(resObj, result);
    EXPECT_EQ(pattern->GetResCacheMapByKey("width"), result.ToString());
    EXPECT_EQ(pattern->GetResCacheMapByKey("height"), result.ToString());
    EXPECT_EQ(pattern->GetResCacheMapByKey("constraintSize.minWidth"), result.ToString());
    EXPECT_EQ(pattern->GetResCacheMapByKey("constraintSize.minHeight"), result.ToString());
    EXPECT_EQ(pattern->GetResCacheMapByKey("constraintSize.maxWidth"), result.ToString());
    EXPECT_EQ(pattern->GetResCacheMapByKey("constraintSize.maxHeight"), result.ToString());
    pattern->RemoveResObj("width");
    pattern->RemoveResObj("height");
    pattern->RemoveResObj("constraintSize.minWidth");
    pattern->RemoveResObj("constraintSize.minHeight");
    pattern->RemoveResObj("constraintSize.maxWidth");
    pattern->RemoveResObj("constraintSize.maxHeight");
}

/**
 * @tc.name: ViewAbstractTest070
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFourNg, ViewAbstractTest070, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern();
    ASSERT_NE(pattern, nullptr);
    std::string bundleName = "com.example.test";
    std::string moduleName = "entry";
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(bundleName, moduleName, 0);
    ViewAbstract::SetPadding(resObj);
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    EXPECT_EQ(pattern->GetResCacheMapByKey("padding"), "0.00px");
    pattern->RemoveResObj("padding");
    NG::PaddingProperty paddings;
    auto updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::PaddingProperty& paddings) {
        paddings.bottom = NG::CalcLength(BOTTOM);
    };
    paddings.AddResource("bottom", resObj, std::move(updateFunc));
    ViewStackProcessor::GetInstance()->visualState_ = std::nullopt;
    g_isConfigChangePerform = true;
    ViewAbstract::SetPadding(paddings);
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    g_isConfigChangePerform = false;
    pattern->RemoveResObj("padding");
    auto layoutProperty = frameNode->GetLayoutProperty<LayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto& padding = layoutProperty->GetPaddingProperty();
    ASSERT_NE(padding, nullptr);
    EXPECT_EQ(padding->bottom, NG::CalcLength(BOTTOM));
}

/**
 * @tc.name: ViewAbstractTest071
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFourNg, ViewAbstractTest071, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern();
    ASSERT_NE(pattern, nullptr);
    std::string bundleName = "com.example.test";
    std::string moduleName = "entry";
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(bundleName, moduleName, 0);
    ViewAbstract::SetMargin(resObj);
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    EXPECT_EQ(pattern->GetResCacheMapByKey("margin"), "0.00px");
    pattern->RemoveResObj("margin");
    NG::MarginProperty margins;
    auto updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::MarginProperty& margins) {
        margins.bottom = NG::CalcLength(BOTTOM);
    };
    margins.AddResource("margin.bottom", resObj, std::move(updateFunc));
    ViewStackProcessor::GetInstance()->visualState_ = std::nullopt;
    g_isConfigChangePerform = true;
    ViewAbstract::SetMargin(margins);
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    g_isConfigChangePerform = false;
    pattern->RemoveResObj("margin");
    auto layoutProperty = frameNode->GetLayoutProperty<LayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto& margin = layoutProperty->GetMarginProperty();
    ASSERT_NE(margin, nullptr);
    EXPECT_EQ(margin->bottom, NG::CalcLength(BOTTOM));
}

/**
 * @tc.name: ViewAbstractTest072
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFourNg, ViewAbstractTest072, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern();
    ASSERT_NE(pattern, nullptr);
    std::string bundleName = "com.example.test";
    std::string moduleName = "entry";
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(bundleName, moduleName, 0);
    ViewAbstract::SetBorderRadius(resObj);
    pattern->OnColorModeChange(1);
    EXPECT_EQ(pattern->GetResCacheMapByKey("borderRadius"), "0.00px");
    pattern->RemoveResObj("borderRadius");
    NG::BorderRadiusProperty borderRadius;
    auto updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::BorderRadiusProperty& borderRadius) {
        borderRadius.radiusBottomLeft = BOTTOM;
    };
    borderRadius.AddResource("borderRadius.radiusBottomLeft", resObj, std::move(updateFunc));
    ViewStackProcessor::GetInstance()->visualState_ = std::nullopt;
    g_isConfigChangePerform = true;
    ViewAbstract::SetBorderRadius(borderRadius);
    pattern->OnColorModeChange(1);
    g_isConfigChangePerform = false;
    pattern->RemoveResObj("borderRadius");
    auto context = frameNode->GetRenderContext();
    ASSERT_NE(context, nullptr);
    Dimension defaultDimension(0);
    BorderRadiusProperty defaultBorderRadius = { defaultDimension, defaultDimension, defaultDimension,
        defaultDimension };
    auto borderRadiusValue = context->GetBorderRadiusValue(defaultBorderRadius);
    EXPECT_EQ(borderRadiusValue.radiusBottomLeft, BOTTOM);
}


/**
 * @tc.name: ViewAbstractTest073
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFourNg, ViewAbstractTest073, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern();
    ASSERT_NE(pattern, nullptr);
    std::string bundleName = "com.example.test";
    std::string moduleName = "entry";
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(bundleName, moduleName, 0);
    ViewAbstract::SetBorderColor(resObj);
    pattern->OnColorModeChange(1);
    EXPECT_EQ(pattern->GetResCacheMapByKey("borderColor"), "#FF000000");
    pattern->RemoveResObj("borderColor");
    NG::BorderColorProperty borderColor;
    auto updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::BorderColorProperty& borderColor) {
        borderColor.bottomColor = BLUE;
    };
    borderColor.AddResource("borderColor.bottomColor", resObj, std::move(updateFunc));
    ViewStackProcessor::GetInstance()->visualState_ = std::nullopt;
    g_isConfigChangePerform = true;
    ViewAbstract::SetBorderColor(borderColor);
    pattern->OnColorModeChange(1);
    g_isConfigChangePerform = false;
    pattern->RemoveResObj("borderColor");
    auto context = frameNode->GetRenderContext();
    ASSERT_NE(context, nullptr);
    Color defaultColor(0xff000000);
    BorderColorProperty defaultBorderColor = { defaultColor, defaultColor, defaultColor, defaultColor, std::nullopt,
        std::nullopt };
    auto borderColorValue = context->GetBorderColorValue(defaultBorderColor);
    EXPECT_EQ(borderColorValue.bottomColor, BLUE);
}

/**
 * @tc.name: ViewAbstractTest074
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFourNg, ViewAbstractTest074, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern();
    ASSERT_NE(pattern, nullptr);
    std::string bundleName = "com.example.test";
    std::string moduleName = "entry";
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(bundleName, moduleName, 0);
    ViewAbstract::SetBorderWidth(resObj);
    pattern->OnColorModeChange(1);
    EXPECT_EQ(pattern->GetResCacheMapByKey("borderWidth"), "0.00px");
    pattern->RemoveResObj("borderWidth");
    NG::BorderWidthProperty borderWidth;
    auto updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::BorderWidthProperty& borderWidth) {
        borderWidth.bottomDimen = BOTTOM;
    };
    borderWidth.AddResource("borderWidth.bottomDimen", resObj, std::move(updateFunc));
    ViewStackProcessor::GetInstance()->visualState_ = std::nullopt;
    g_isConfigChangePerform = true;
    ViewAbstract::SetBorderWidth(borderWidth);
    pattern->OnColorModeChange(1);
    g_isConfigChangePerform = false;
    pattern->RemoveResObj("borderWidth");

    auto layoutProperty = frameNode->GetLayoutProperty<LayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto& layoutBorderWidth = layoutProperty->GetBorderWidthProperty();
    ASSERT_NE(layoutBorderWidth, nullptr);
    EXPECT_EQ(layoutBorderWidth->bottomDimen, BOTTOM);

    auto context = frameNode->GetRenderContext();
    ASSERT_NE(context, nullptr);
    Dimension defaultDimension(0);
    BorderWidthProperty defaultBorderWidth = { defaultDimension, defaultDimension, defaultDimension, defaultDimension };
    auto contextBorderWidth = context->GetBorderWidthValue(defaultBorderWidth);
    EXPECT_EQ(contextBorderWidth.bottomDimen, BOTTOM);
}

/**
 * @tc.name: ViewAbstractTest075
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFourNg, ViewAbstractTest075, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern();
    ASSERT_NE(pattern, nullptr);
    std::string bundleName = "com.example.test";
    std::string moduleName = "entry";
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(bundleName, moduleName, 0);
    NG::BorderWidthProperty borderWidth;
    auto updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::BorderWidthProperty& borderWidth) {
        borderWidth.bottomDimen = BOTTOM;
    };
    borderWidth.AddResource("borderWidth.bottomDimen", resObj, std::move(updateFunc));
    ViewStackProcessor::GetInstance()->visualState_ = std::nullopt;
    g_isConfigChangePerform = true;
    ViewAbstract::SetDashGap(borderWidth);
    pattern->OnColorModeChange(1);
    g_isConfigChangePerform = false;
    pattern->RemoveResObj("borderWidth");

    auto context = frameNode->GetRenderContext();
    ASSERT_NE(context, nullptr);
    Dimension defaultDimension(0);
    BorderWidthProperty defaultBorderWidth = { defaultDimension, defaultDimension, defaultDimension, defaultDimension };
    auto contextBorderWidth = context->GetDashGapValue(defaultBorderWidth);
    EXPECT_EQ(contextBorderWidth.bottomDimen, BOTTOM);
}

/**
 * @tc.name: ViewAbstractTest076
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFourNg, ViewAbstractTest076, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern();
    ASSERT_NE(pattern, nullptr);
    std::string bundleName = "com.example.test";
    std::string moduleName = "entry";
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(bundleName, moduleName, 0);
    NG::BorderWidthProperty borderWidth;
    borderWidth.bottomDimen = BOTTOM;
    ViewStackProcessor::GetInstance()->visualState_ = std::nullopt;
    g_isConfigChangePerform = true;
    ViewAbstract::SetDashWidth(borderWidth);
    pattern->OnColorModeChange(1);
    g_isConfigChangePerform = false;

    auto context = frameNode->GetRenderContext();
    ASSERT_NE(context, nullptr);
    Dimension defaultDimension(0);
    BorderWidthProperty defaultBorderWidth = { defaultDimension, defaultDimension, defaultDimension, defaultDimension };
    auto contextBorderWidth = context->GetDashWidthValue(defaultBorderWidth);
    EXPECT_EQ(contextBorderWidth.bottomDimen, BOTTOM);
}

/**
 * @tc.name: ViewAbstractTest077
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFourNg, ViewAbstractTest077, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern();
    ASSERT_NE(pattern, nullptr);
    std::string bundleName = "com.example.test";
    std::string moduleName = "entry";
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(bundleName, moduleName, 0);
    ViewAbstract::SetPosition(ZERO, ZERO, resObj, resObj);
    ViewStackProcessor::GetInstance()->visualState_ = std::nullopt;
    g_isConfigChangePerform = true;
    ViewAbstract::SetPosition(ZERO, ZERO, resObj, resObj);
    pattern->OnColorModeChange(1);
    g_isConfigChangePerform = false;

    auto context = frameNode->GetRenderContext();
    ASSERT_NE(context, nullptr);
    OffsetT<Dimension> defaultDimension = { WIDTH, HEIGHT };
    auto positionValue = context->GetPositionValue(OffsetT<Dimension>(defaultDimension));
    EXPECT_EQ(positionValue.GetX(), ZERO);
    EXPECT_EQ(positionValue.GetY(), ZERO);
}

/**
 * @tc.name: ViewAbstractTest078
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFourNg, ViewAbstractTest078, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern();
    ASSERT_NE(pattern, nullptr);
    std::string bundleName = "com.example.test";
    std::string moduleName = "entry";
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(bundleName, moduleName, 0);
    ViewAbstract::SetOffset(ZERO, ZERO, resObj, resObj);
    ViewStackProcessor::GetInstance()->visualState_ = std::nullopt;
    g_isConfigChangePerform = true;
    ViewAbstract::SetOffset(ZERO, ZERO, resObj, resObj);
    pattern->OnColorModeChange(1);
    g_isConfigChangePerform = false;

    auto context = frameNode->GetRenderContext();
    ASSERT_NE(context, nullptr);
    OffsetT<Dimension> defaultDimension = { WIDTH, HEIGHT };
    auto offsetValue = context->GetOffsetValue(OffsetT<Dimension>(defaultDimension));
    EXPECT_EQ(offsetValue.GetX(), ZERO);
    EXPECT_EQ(offsetValue.GetY(), ZERO);
}

/**
 * @tc.name: ViewAbstractTest079
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFourNg, ViewAbstractTest079, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern();
    ASSERT_NE(pattern, nullptr);
    std::string bundleName = "com.example.test";
    std::string moduleName = "entry";
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(bundleName, moduleName, 0);
    ViewAbstract::MarkAnchor(ZERO, ZERO, resObj, resObj);
    ViewStackProcessor::GetInstance()->visualState_ = std::nullopt;
    g_isConfigChangePerform = true;
    ViewAbstract::MarkAnchor(ZERO, ZERO, resObj, resObj);
    pattern->OnColorModeChange(1);
    g_isConfigChangePerform = false;

    auto context = frameNode->GetRenderContext();
    ASSERT_NE(context, nullptr);
    OffsetT<Dimension> defaultDimension = { WIDTH, HEIGHT };
    auto anchorValue = context->GetAnchorValue(OffsetT<Dimension>(defaultDimension));
    EXPECT_EQ(anchorValue.GetX(), ZERO);
    EXPECT_EQ(anchorValue.GetY(), ZERO);
}

/**
 * @tc.name: ViewAbstractTest080
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFourNg, ViewAbstractTest080, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern();
    ASSERT_NE(pattern, nullptr);
    std::string bundleName = "com.example.test";
    std::string moduleName = "entry";
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(bundleName, moduleName, 0);
    NG::PaddingProperty paddings;
    auto updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::PaddingProperty& paddings) {
        paddings.bottom = NG::CalcLength(BOTTOM);
    };
    paddings.AddResource("paddings.bottom", resObj, std::move(updateFunc));
    ViewStackProcessor::GetInstance()->visualState_ = std::nullopt;
    g_isConfigChangePerform = true;
    ViewAbstract::SetSafeAreaPadding(paddings);
    pattern->OnColorModeChange(1);
    g_isConfigChangePerform = false;
    pattern->RemoveResObj("paddings");

    auto layoutProperty = frameNode->GetLayoutProperty<LayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto& safeAreaPaddingProperty = layoutProperty->GetSafeAreaPaddingProperty();
    ASSERT_NE(safeAreaPaddingProperty, nullptr);
    EXPECT_EQ(safeAreaPaddingProperty->bottom, NG::CalcLength(BOTTOM));
}

/**
 * @tc.name: ViewAbstractTest081
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFourNg, ViewAbstractTest081, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern();
    ASSERT_NE(pattern, nullptr);
    std::string bundleName = "com.example.test";
    std::string moduleName = "entry";
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(bundleName, moduleName, 0);
    EdgesParam edgesParam;
    edgesParam.bottom = BOTTOM;

    ViewStackProcessor::GetInstance()->visualState_ = std::nullopt;
    g_isConfigChangePerform = true;
    ViewAbstract::SetPositionEdges(edgesParam);
    pattern->OnColorModeChange(1);
    g_isConfigChangePerform = false;
    pattern->RemoveResObj("edgesParam");

    auto context = frameNode->GetRenderContext();
    ASSERT_NE(context, nullptr);
    Dimension defaultDimension(0);
    EdgesParam defaultEdgesParam = { defaultDimension, defaultDimension, defaultDimension, defaultDimension,
        std::nullopt, std::nullopt };
    auto positionEdges = context->GetPositionEdgesValue(defaultEdgesParam);
    EXPECT_EQ(positionEdges.bottom, BOTTOM);
}

/**
 * @tc.name: ViewAbstractTest082
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFourNg, ViewAbstractTest082, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern();
    ASSERT_NE(pattern, nullptr);
    std::string bundleName = "com.example.test";
    std::string moduleName = "entry";
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(bundleName, moduleName, 0);
    EdgesParam edgesParam;
    edgesParam.bottom = BOTTOM;
    ViewStackProcessor::GetInstance()->visualState_ = std::nullopt;
    g_isConfigChangePerform = true;
    ViewAbstract::SetOffsetEdges(edgesParam);
    pattern->OnColorModeChange(1);
    g_isConfigChangePerform = false;

    auto context = frameNode->GetRenderContext();
    ASSERT_NE(context, nullptr);
    Dimension defaultDimension(0);
    EdgesParam defaultEdgesParam = { defaultDimension, defaultDimension, defaultDimension, defaultDimension,
        std::nullopt, std::nullopt };
    auto positionEdges = context->GetOffsetEdgesValue(defaultEdgesParam);
    EXPECT_EQ(positionEdges.bottom, BOTTOM);
}

/**
 * @tc.name: RemoveResObj
 * @tc.desc: Test RemoveResObj of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFourNg, ViewAbstractTestNg0083, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    g_isConfigChangePerform = false;
    std::string key = "clipShape";
    viewAbstractModelNG.RemoveResObj(key);
    g_isConfigChangePerform = true;
    viewAbstractModelNG.RemoveResObj(key);
    g_isConfigChangePerform = false;
    std::string maskShape = pattern->GetResCacheMapByKey("clipShape");
    EXPECT_EQ(maskShape, "");
}

/**
 * @tc.name: ViewAbstractTestNg0084
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFourNg, ViewAbstractTestNg0084, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern();
    ASSERT_NE(pattern, nullptr);
    std::string bundleName = "com.example.test";
    std::string moduleName = "entry";
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(bundleName, moduleName, 0);
    OffsetT<Dimension> value = { ZERO, ZERO };
    ViewAbstract::SetPosition(frameNode, value, resObj, resObj);
    ViewStackProcessor::GetInstance()->visualState_ = std::nullopt;
    g_isConfigChangePerform = true;
    ViewAbstract::SetPosition(frameNode, value, resObj, resObj);
    pattern->OnColorModeChange(1);
    g_isConfigChangePerform = false;

    auto context = frameNode->GetRenderContext();
    EXPECT_NE(context, nullptr);
    OffsetT<Dimension> defaultDimension = { WIDTH, HEIGHT };
    auto positionValue = context->GetPositionValue(OffsetT<Dimension>(defaultDimension));
    EXPECT_EQ(positionValue.GetX(), ZERO);
    EXPECT_EQ(positionValue.GetY(), ZERO);
}

/**
 * @tc.name: ViewAbstractSetClickFocusTest001
 * @tc.desc: Test that container node becomes focusable when click event is set and no focusable children exist.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFourNg, ViewAbstractSetClickFocusTest001, TestSize.Level1)
{
    /**
     * @tc.steps1: Create a FrameNode and set a native onClick event via SetOnClick.
     * @tc.expected: The FrameNode should be focusable after setting onClick.
     */
    auto frameNode1 = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(frameNode1, nullptr);

    GestureEventFunc onClick = [](GestureEvent&) {};
    ViewAbstract::SetOnClick(AceType::RawPtr(frameNode1), std::move(onClick), 10.0);

    auto focusHub1 = frameNode1->GetFocusHub();
    ASSERT_NE(focusHub1, nullptr);
    EXPECT_TRUE(focusHub1->IsFocusable());

    /**
     * @tc.steps2: Create another FrameNode and set a JS-based onClick event via SetFrameNodeCommonOnClick.
     * @tc.expected: The FrameNode should also become focusable after setting JS onClick.
     */
    auto frameNode2 = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(frameNode2, nullptr);

    GestureEventFunc jsOnClick = [](GestureEvent&) {};
    ViewAbstract::SetFrameNodeCommonOnClick(AceType::RawPtr(frameNode2), std::move(jsOnClick));

    auto focusHub2 = frameNode2->GetFocusHub();
    ASSERT_NE(focusHub2, nullptr);
    EXPECT_TRUE(focusHub2->IsFocusable());
}

/**
 * @tc.name: ViewAbstractTestNg0097
 * @tc.desc: test position attribute, use Edges type.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFourNg, ViewAbstractTestNg0097, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    std::string bundleName = "com.example.test";
    std::string moduleName = "entry";
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(bundleName, moduleName, 0);
    auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, EdgesParam& edges) {};
    EdgesParam edgesParam;
    edgesParam.AddResource("edges.top", resObj, std::move(updateFunc));
    EXPECT_EQ(edgesParam.resMap_.empty(), false);
    ViewAbstract::SetPositionEdges(frameNode, edgesParam);
    auto renderContext = frameNode->GetRenderContext();
    EXPECT_EQ(renderContext->HasPositionEdges(), true);
}

/**
 * @tc.name: ViewAbstractTest0098
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFourNg, ViewAbstractTestNg0098, TestSize.Level1)
{
    /**
     * @tc.steps: step1.Using static methods to set component properties
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern();
    ASSERT_NE(pattern, nullptr);

    std::string bundleName = "com.example.test";
    std::string moduleName = "entry";
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(bundleName, moduleName, 0);

    pattern->AddResCache("height", "0.00auto");
    pattern->AddResCache("width", "0.00auto");
    ViewAbstract::SetWidth(resObj);
    ViewAbstract::SetHeight(resObj);

    /**
     * @tc.expected: Successfully set various properties of the top node on the stack
     */
    CalcDimension result = Dimension(0.0f, DimensionUnit::AUTO);
    ResourceParseUtils::ParseResDimensionVpNG(resObj, result);
    EXPECT_EQ(pattern->GetResCacheMapByKey("width"), result.ToString());
    EXPECT_EQ(pattern->GetResCacheMapByKey("height"), result.ToString());
    pattern->RemoveResObj("width");
    pattern->RemoveResObj("height");
}

/**
 * @tc.name: ViewAbstractTest0099
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFourNg, ViewAbstractTestNg0099, TestSize.Level1)
{
    /**
     * @tc.steps: step1.Using static methods to set component properties
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern();
    ASSERT_NE(pattern, nullptr);

    std::string bundleName = "com.example.test";
    std::string moduleName = "entry";
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(bundleName, moduleName, 0);

    pattern->AddResCache("width", "xxxxxx");
    ViewAbstract::SetWidth(resObj);
    pattern->AddResCache("height", "xxxxxx");
    ViewAbstract::SetHeight(resObj);
    pattern->AddResCache("constraintSize.minWidth", "xxxxxx");
    ViewAbstract::SetMinWidth(resObj);
    pattern->AddResCache("constraintSize.minHeight", "xxxxxx");
    ViewAbstract::SetMinHeight(resObj);
    pattern->AddResCache("constraintSize.maxWidth", "xxxxxx");
    ViewAbstract::SetMaxWidth(resObj);
    pattern->AddResCache("constraintSize.maxHeight", "xxxxxx");
    ViewAbstract::SetMaxHeight(resObj);
    pattern->OnColorModeChange(0);

    /**
     * @tc.expected: Successfully set various properties of the top node on the stack
     */
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto&& layoutConstraint = layoutProperty->GetCalcLayoutConstraint();
    CHECK_NULL_VOID(layoutConstraint);
    auto defaultValue = Dimension(0.00, DimensionUnit::PX);
    EXPECT_EQ(layoutConstraint->selfIdealSize->Height(), NG::CalcLength(defaultValue));
    EXPECT_EQ(layoutConstraint->selfIdealSize->Width(), NG::CalcLength(defaultValue));
    EXPECT_EQ(layoutConstraint->maxSize.value().Width(), NG::CalcLength(defaultValue));
    EXPECT_EQ(layoutConstraint->maxSize.value().Height(), NG::CalcLength(defaultValue));
    EXPECT_EQ(layoutConstraint->minSize.value().Width(), NG::CalcLength(defaultValue));
    EXPECT_EQ(layoutConstraint->minSize.value().Height(), NG::CalcLength(defaultValue));
    pattern->RemoveResObj("width");
    pattern->RemoveResObj("height");
    pattern->RemoveResObj("constraintSize.minWidth");
    pattern->RemoveResObj("constraintSize.minHeight");
    pattern->RemoveResObj("constraintSize.maxWidth");
    pattern->RemoveResObj("constraintSize.maxHeight");
}

/**
 * @tc.name: ViewAbstractTest0100
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFourNg, ViewAbstractTestNg0100, TestSize.Level1)
{
    /**
     * @tc.steps: step1.Using static methods to set component properties
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern();
    ASSERT_NE(pattern, nullptr);

    std::string bundleName = "com.example.test";
    std::string moduleName = "entry";
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(bundleName, moduleName, 0);

    pattern->AddResCache("width", "xxxxxx");
    ViewAbstract::SetWidth(frameNode, resObj);
    pattern->AddResCache("height", "xxxxxx");
    ViewAbstract::SetHeight(frameNode, resObj);
    pattern->AddResCache("constraintSize.minWidth", "xxxxxx");
    ViewAbstract::SetMinWidth(frameNode, resObj);
    pattern->AddResCache("constraintSize.minHeight", "xxxxxx");
    ViewAbstract::SetMinHeight(frameNode, resObj);
    pattern->AddResCache("constraintSize.maxWidth", "xxxxxx");
    ViewAbstract::SetMaxWidth(frameNode, resObj);
    pattern->AddResCache("constraintSize.maxHeight", "xxxxxx");
    ViewAbstract::SetMaxHeight(frameNode, resObj);
    pattern->OnColorModeChange(0);

    /**
     * @tc.expected: Successfully set various properties of the top node on the stack
     */
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto&& layoutConstraint = layoutProperty->GetCalcLayoutConstraint();
    CHECK_NULL_VOID(layoutConstraint);
    auto defaultValue = Dimension(0.00, DimensionUnit::PX);
    EXPECT_EQ(layoutConstraint->selfIdealSize->Height(), NG::CalcLength(defaultValue));
    EXPECT_EQ(layoutConstraint->selfIdealSize->Width(), NG::CalcLength(defaultValue));
    EXPECT_EQ(layoutConstraint->maxSize.value().Width(), NG::CalcLength(defaultValue));
    EXPECT_EQ(layoutConstraint->maxSize.value().Height(), NG::CalcLength(defaultValue));
    EXPECT_EQ(layoutConstraint->minSize.value().Width(), NG::CalcLength(defaultValue));
    EXPECT_EQ(layoutConstraint->minSize.value().Height(), NG::CalcLength(defaultValue));
    pattern->RemoveResObj("width");
    pattern->RemoveResObj("height");
    pattern->RemoveResObj("constraintSize.minWidth");
    pattern->RemoveResObj("constraintSize.minHeight");
    pattern->RemoveResObj("constraintSize.maxWidth");
    pattern->RemoveResObj("constraintSize.maxHeight");
}

/**
 * @tc.name: ViewAbstractTest0101
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFourNg, ViewAbstractTestNg0101, TestSize.Level1)
{
    /**
     * @tc.steps: step1.Using static methods to set component properties
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern();
    ASSERT_NE(pattern, nullptr);

    std::string bundleName = "com.example.test";
    std::string moduleName = "entry";
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(bundleName, moduleName, 0);

    auto dimensionResult = Dimension(-10.0, DimensionUnit::PX);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(20);
    pattern->AddResCache("width", dimensionResult.ToString());
    ViewAbstract::SetWidth(resObj);
    pattern->AddResCache("height", dimensionResult.ToString());
    ViewAbstract::SetHeight(resObj);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(0);

    /**
     * @tc.expected: Successfully set various properties of the top node on the stack
     */
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto&& layoutConstraint = layoutProperty->GetCalcLayoutConstraint();
    CHECK_NULL_VOID(layoutConstraint);
    auto defaultValue = Dimension(0.00, DimensionUnit::PX);
    EXPECT_EQ(layoutConstraint->selfIdealSize->Height(), NG::CalcLength(defaultValue));
    EXPECT_EQ(layoutConstraint->selfIdealSize->Width(), NG::CalcLength(defaultValue));
    pattern->RemoveResObj("width");
    pattern->RemoveResObj("height");
}

/**
 * @tc.name: ViewAbstractTest0102
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFourNg, ViewAbstractTestNg0102, TestSize.Level1)
{
    /**
     * @tc.steps: step1.Using static methods to set component properties
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern();
    ASSERT_NE(pattern, nullptr);

    std::string bundleName = "com.example.test";
    std::string moduleName = "entry";
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(bundleName, moduleName, 0);

    auto dimensionResult = Dimension(10.0, DimensionUnit::PX);
    pattern->AddResCache("width", dimensionResult.ToString());
    pattern->AddResCache("constraintSize.minWidth", dimensionResult.ToString());
    ViewAbstract::SetMinWidth(resObj);
    pattern->AddResCache("constraintSize.minHeight", dimensionResult.ToString());
    ViewAbstract::SetMinHeight(resObj);
    pattern->AddResCache("constraintSize.maxWidth", dimensionResult.ToString());
    ViewAbstract::SetMaxWidth(resObj);
    pattern->AddResCache("constraintSize.maxHeight", dimensionResult.ToString());
    ViewAbstract::SetMaxHeight(resObj);
    pattern->OnColorModeChange(0);

    /**
     * @tc.expected: Successfully set various properties of the top node on the stack
     */
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto&& layoutConstraint = layoutProperty->GetCalcLayoutConstraint();
    CHECK_NULL_VOID(layoutConstraint);
    auto defaultValue = Dimension(10.00, DimensionUnit::PX);
    EXPECT_EQ(layoutConstraint->maxSize.value().Width(), NG::CalcLength(defaultValue));
    EXPECT_EQ(layoutConstraint->maxSize.value().Height(), NG::CalcLength(defaultValue));
    EXPECT_EQ(layoutConstraint->minSize.value().Width(), NG::CalcLength(defaultValue));
    EXPECT_EQ(layoutConstraint->minSize.value().Height(), NG::CalcLength(defaultValue));
    pattern->RemoveResObj("constraintSize.minWidth");
    pattern->RemoveResObj("constraintSize.minHeight");
    pattern->RemoveResObj("constraintSize.maxWidth");
    pattern->RemoveResObj("constraintSize.maxHeight");
}

/**
 * @tc.name: ViewAbstractTest0103
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFourNg, ViewAbstractTestNg0103, TestSize.Level1)
{
    /**
     * @tc.steps: step1.Using static methods to set component properties
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern();
    ASSERT_NE(pattern, nullptr);

    std::string bundleName = "com.example.test";
    std::string moduleName = "entry";
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(bundleName, moduleName, 0);

    auto dimensionResult = Dimension(-10.0, DimensionUnit::PX);
    pattern->AddResCache("constraintSize.minWidth", dimensionResult.ToString());
    ViewAbstract::SetMinWidth(frameNode, resObj);
    pattern->AddResCache("constraintSize.minHeight", dimensionResult.ToString());
    ViewAbstract::SetMinHeight(frameNode, resObj);
    pattern->AddResCache("constraintSize.maxWidth", dimensionResult.ToString());
    ViewAbstract::SetMaxWidth(frameNode, resObj);
    pattern->AddResCache("constraintSize.maxHeight", dimensionResult.ToString());
    ViewAbstract::SetMaxHeight(frameNode, resObj);
    pattern->OnColorModeChange(0);

    /**
     * @tc.expected: Successfully set various properties of the top node on the stack
     */
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto&& layoutConstraint = layoutProperty->GetCalcLayoutConstraint();
    CHECK_NULL_VOID(layoutConstraint);
    auto defaultValue = Dimension(-10.00, DimensionUnit::PX);
    EXPECT_EQ(layoutConstraint->maxSize.value().Width(), NG::CalcLength(defaultValue));
    EXPECT_EQ(layoutConstraint->maxSize.value().Height(), NG::CalcLength(defaultValue));
    EXPECT_EQ(layoutConstraint->minSize.value().Width(), NG::CalcLength(defaultValue));
    EXPECT_EQ(layoutConstraint->minSize.value().Height(), NG::CalcLength(defaultValue));
    pattern->RemoveResObj("constraintSize.minWidth");
    pattern->RemoveResObj("constraintSize.minHeight");
    pattern->RemoveResObj("constraintSize.maxWidth");
    pattern->RemoveResObj("constraintSize.maxHeight");
}

/**
 * @tc.name: ViewAbstractTest0104
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFourNg, ViewAbstractTestNg0104, TestSize.Level1)
{
    /**
     * @tc.steps: step1.Using static methods to set component properties
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern();
    ASSERT_NE(pattern, nullptr);

    std::string bundleName = "com.example.test";
    std::string moduleName = "entry";
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(bundleName, moduleName, 0);

    auto dimensionResult = Dimension(10.0, DimensionUnit::PX);
    pattern->AddResCache("margin", dimensionResult.ToString());
    ViewAbstract::SetMargin(resObj);
    pattern->AddResCache("padding", dimensionResult.ToString());
    ViewAbstract::SetPadding(resObj);

    /**
     * @tc.expected: Successfully set various properties of the top node on the stack
     */
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto defaultValue = Dimension(10.00, DimensionUnit::PX);
    EXPECT_EQ(layoutProperty->GetPaddingProperty()->top, NG::CalcLength(defaultValue));
    EXPECT_EQ(layoutProperty->GetMarginProperty()->top, NG::CalcLength(defaultValue));
    pattern->RemoveResObj("margin");
    pattern->RemoveResObj("padding");
}

/**
 * @tc.name: ViewAbstractTest0105
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFourNg, ViewAbstractTestNg0105, TestSize.Level1)
{
    /**
     * @tc.steps: step1.Using static methods to set component properties
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern();
    ASSERT_NE(pattern, nullptr);

    std::string bundleName = "com.example.test";
    std::string moduleName = "entry";
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(bundleName, moduleName, 0);

    pattern->AddResCache("margin", "xxxxxx");
    ViewAbstract::SetMargin(resObj);
    pattern->AddResCache("padding", "xxxxxx");
    ViewAbstract::SetPadding(resObj);

    /**
     * @tc.expected: Successfully set various properties of the top node on the stack
     */
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto defaultValue = Dimension(0.00, DimensionUnit::PX);
    EXPECT_EQ(layoutProperty->GetPaddingProperty()->top, NG::CalcLength(defaultValue));
    EXPECT_EQ(layoutProperty->GetMarginProperty()->top, NG::CalcLength(defaultValue));
    pattern->RemoveResObj("margin");
    pattern->RemoveResObj("padding");
}

/**
 * @tc.name: SetLinearGradient
 * @tc.desc: Test SetLinearGradient of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFourNg, ViewAbstractResourceObjectTest001, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    g_isConfigChangePerform = true;
    NG::Gradient gradient;
    gradient.CreateGradientWithType(NG::GradientType::LINEAR);
    gradient.GetLinearGradient()->linearX = NG::GradientDirection::LEFT;
    ViewAbstract::SetLinearGradient(frameNode, gradient);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetLinearGradient().has_value(), true);
    EXPECT_EQ(renderContext->GetLinearGradient()->GetLinearGradient()->linearX, NG::GradientDirection::LEFT);
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SetSweepGradient
 * @tc.desc: Test SetSweepGradient of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFourNg, ViewAbstractResourceObjectTest002, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    g_isConfigChangePerform = true;
    NG::Gradient gradient;
    gradient.CreateGradientWithType(NG::GradientType::SWEEP);
    gradient.GetSweepGradient()->endAngle = CalcDimension(100.0f, DimensionUnit::PX);
    ViewAbstract::SetSweepGradient(frameNode, gradient);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetSweepGradient().has_value(), true);
    EXPECT_EQ(renderContext->GetSweepGradient()->GetSweepGradient()->endAngle,
      CalcDimension(100.0f, DimensionUnit::PX));
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SetRadialGradient
 * @tc.desc: Test SetRadialGradient of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFourNg, ViewAbstractResourceObjectTest003, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    g_isConfigChangePerform = true;
    NG::Gradient gradient;
    gradient.CreateGradientWithType(NG::GradientType::RADIAL);
    gradient.GetRadialGradient()->radialSizeType = std::make_optional(RadialSizeType::CLOSEST_CORNER);
    ViewAbstract::SetRadialGradient(frameNode, gradient);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetRadialGradient().has_value(), true);
    EXPECT_EQ(renderContext->GetRadialGradient()->GetRadialGradient()->radialSizeType, RadialSizeType::CLOSEST_CORNER);
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SetForegroundColor
 * @tc.desc: Test SetForegroundColor of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFourNg, ViewAbstractResourceObjectTest004, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    std::string foregroundColor = pattern->GetResCacheMapByKey("foregroundColor");
    EXPECT_EQ(foregroundColor, "");
    g_isConfigChangePerform = true;
    std::string bundleName = "com.example.test";
    std::string moduleName = "entry";
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(bundleName, moduleName, 0);
    Color color;
    ViewAbstract::SetForegroundColor(frameNode, color, resObj);
    Color result;
    ResourceParseUtils::ParseResColor(resObj, result);
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    g_isConfigChangePerform = false;
    foregroundColor = pattern->GetResCacheMapByKey("foregroundColor");
    EXPECT_EQ(foregroundColor, result.ColorToString());
}

/**
 * @tc.name: SetOpacity
 * @tc.desc: Test SetOpacity of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFourNg, ViewAbstractResourceObjectTest005, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    std::string opacityStr = pattern->GetResCacheMapByKey("viewAbstract.opacity");
    EXPECT_EQ(opacityStr, "");
    g_isConfigChangePerform = true;
    std::string bundleName = "com.example.test";
    std::string moduleName = "entry";
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(bundleName, moduleName, 0);
    double opacity = 0.0;
    ViewAbstract::SetOpacity(frameNode, opacity, resObj);
    double result;
    ResourceParseUtils::ParseResDouble(resObj, result);
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    g_isConfigChangePerform = false;
    opacityStr = pattern->GetResCacheMapByKey("viewAbstract.opacity");
    EXPECT_EQ(opacityStr, std::to_string(result));
}

/**
 * @tc.name: SetClipShape
 * @tc.desc: Test SetClipShape of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFourNg, ViewAbstractResourceObjectTest006, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    g_isConfigChangePerform = true;
    ViewAbstract::SetClipEdge(frameNode, true);
    auto basicShape = AceType::MakeRefPtr<Circle>();
    basicShape->SetBasicShapeType(BasicShapeType::CIRCLE);
    EXPECT_EQ(basicShape->GetBasicShapeType(), BasicShapeType::CIRCLE);
    ViewAbstract::SetClipShape(frameNode, basicShape);
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    g_isConfigChangePerform = false;
    std::string shapeStr = pattern->GetResCacheMapByKey("clipShape");
    EXPECT_EQ(shapeStr, "");
}

/**
 * @tc.name: SetBackgroundBlurStyle
 * @tc.desc: Test SetBackgroundBlurStyle of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFourNg, ViewAbstractResourceObjectTest007, TestSize.Level1)
{
    BlurStyleOption blurStyleOption;
    blurStyleOption.blurStyle = BlurStyle::NO_MATERIAL;
    blurStyleOption.colorMode = ThemeColorMode::SYSTEM;
    blurStyleOption.adaptiveColor = AdaptiveColor::DEFAULT;
    blurStyleOption.policy = BlurStyleActivePolicy::ALWAYS_INACTIVE;
    g_isConfigChangePerform = true;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    ViewAbstract::SetBackgroundBlurStyle(frameNode, blurStyleOption);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetBackBlurStyle().has_value(), true);
    EXPECT_EQ(renderContext->GetBackBlurStyle()->blurStyle, BlurStyle::NO_MATERIAL);
    EXPECT_EQ(renderContext->GetBackBlurStyle()->colorMode, ThemeColorMode::SYSTEM);
    EXPECT_EQ(renderContext->GetBackBlurStyle()->adaptiveColor, AdaptiveColor::DEFAULT);
    EXPECT_EQ(renderContext->GetBackBlurStyle()->policy, BlurStyleActivePolicy::ALWAYS_INACTIVE);
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: UpdateBackgroundBlurStyle
 * @tc.desc: Test UpdateBackgroundBlurStyle of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFourNg, ViewAbstractResourceObjectTest008, TestSize.Level1)
{
    BlurStyleOption blurStyleOption;
    blurStyleOption.blurStyle = BlurStyle::NO_MATERIAL;
    blurStyleOption.colorMode = ThemeColorMode::SYSTEM;
    blurStyleOption.adaptiveColor = AdaptiveColor::DEFAULT;
    blurStyleOption.policy = BlurStyleActivePolicy::ALWAYS_INACTIVE;
    g_isConfigChangePerform = true;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    auto target = frameNode->GetRenderContext();
    ASSERT_NE(target, nullptr);

    SysOptions sysOptions;
    EffectOption effectOption;
    Color effectOptionColor;
    effectOption.color = effectOptionColor;
    target->UpdateBackgroundEffect(effectOption, sysOptions);
    target->UpdateBackBlurRadius(Dimension(0.5f, DimensionUnit::PERCENT));
    ViewAbstract::UpdateBackgroundBlurStyle(frameNode, blurStyleOption, sysOptions);
    EXPECT_EQ(target->GetBackBlurStyle().has_value(), true);
    EXPECT_EQ(target->GetBackBlurStyle()->blurStyle, BlurStyle::NO_MATERIAL);
    EXPECT_EQ(target->GetBackBlurStyle()->colorMode, ThemeColorMode::SYSTEM);
    EXPECT_EQ(target->GetBackBlurStyle()->adaptiveColor, AdaptiveColor::DEFAULT);
    EXPECT_EQ(target->GetBackBlurStyle()->policy, BlurStyleActivePolicy::ALWAYS_INACTIVE);
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SetBackgroundEffect
 * @tc.desc: Test SetBackgroundEffect of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFourNg, ViewAbstractResourceObjectTest009, TestSize.Level1)
{
    EffectOption option;
    Color color = Color::TRANSPARENT;
    option.color = color;
    option.policy = BlurStyleActivePolicy::ALWAYS_INACTIVE;
    g_isConfigChangePerform = true;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    ViewAbstract::SetBackgroundEffect(frameNode, option);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetBackgroundEffect().has_value(), true);
    EXPECT_EQ(renderContext->GetBackgroundEffect()->color, Color::TRANSPARENT);
    EXPECT_EQ(renderContext->GetBackgroundEffect()->policy, BlurStyleActivePolicy::ALWAYS_INACTIVE);
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: UpdateBackgroundEffect
 * @tc.desc: Test UpdateBackgroundEffect of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFourNg, ViewAbstractResourceObjectTest010, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    auto target = frameNode->GetRenderContext();
    ASSERT_NE(target, nullptr);
    g_isConfigChangePerform = true;
    SysOptions sysOptions;
    EffectOption effectOption;
    effectOption.color = Color::TRANSPARENT;
    effectOption.policy = BlurStyleActivePolicy::FOLLOWS_WINDOW_ACTIVE_STATE;

    BlurStyleOption blurStyleOption;
    blurStyleOption.blurStyle = BlurStyle::NO_MATERIAL;
    blurStyleOption.colorMode = ThemeColorMode::SYSTEM;
    blurStyleOption.adaptiveColor = AdaptiveColor::DEFAULT;
    blurStyleOption.policy = BlurStyleActivePolicy::ALWAYS_INACTIVE;
    ViewAbstract::UpdateBackgroundBlurStyle(frameNode, blurStyleOption, sysOptions);
    target->UpdateBackBlurRadius(Dimension(0.5f, DimensionUnit::PERCENT));
    EXPECT_EQ(target->GetBackBlurStyle().has_value(), true);
    EXPECT_EQ(target->GetBackBlurStyle()->blurStyle, BlurStyle::NO_MATERIAL);
    EXPECT_EQ(target->GetBackBlurStyle()->colorMode, ThemeColorMode::SYSTEM);
    EXPECT_EQ(target->GetBackBlurStyle()->adaptiveColor, AdaptiveColor::DEFAULT);
    EXPECT_EQ(target->GetBackBlurStyle()->policy, BlurStyleActivePolicy::ALWAYS_INACTIVE);

    ViewAbstract::UpdateBackgroundEffect(frameNode, effectOption, sysOptions);
    EXPECT_EQ(target->GetBackgroundEffect().has_value(), true);
    EXPECT_EQ(target->GetBackgroundEffect()->color, Color::TRANSPARENT);
    EXPECT_EQ(target->GetBackgroundEffect()->policy, BlurStyleActivePolicy::FOLLOWS_WINDOW_ACTIVE_STATE);
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SetPixelStretchEffect
 * @tc.desc: Test SetPixelStretchEffect of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFourNg, ViewAbstractResourceObjectTest011, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    g_isConfigChangePerform = true;
    PixStretchEffectOption option;
    option.ResetValue();
    ViewAbstract::SetPixelStretchEffect(frameNode, option);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetPixelStretchEffect().has_value(), true);
    EXPECT_EQ(renderContext->GetPixelStretchEffect()->left, Dimension(0.0f));
    EXPECT_EQ(renderContext->GetPixelStretchEffect()->top, Dimension(0.0f));
    EXPECT_EQ(renderContext->GetPixelStretchEffect()->right, Dimension(0.0f));
    EXPECT_EQ(renderContext->GetPixelStretchEffect()->bottom, Dimension(0.0f));
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SetOuterBorderRadius
 * @tc.desc: Test SetOuterBorderRadius of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFourNg, ViewAbstractResourceObjectTest012, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    g_isConfigChangePerform = true;
    NG::BorderRadiusProperty borderRadius;
    borderRadius.radiusTopLeft = Dimension(1.0f, OHOS::Ace::DimensionUnit::VP);
    borderRadius.radiusTopRight = Dimension(2.0f, OHOS::Ace::DimensionUnit::VP);
    borderRadius.radiusBottomRight = Dimension(3.0f, OHOS::Ace::DimensionUnit::VP);
    borderRadius.radiusBottomLeft = Dimension(4.0f, OHOS::Ace::DimensionUnit::VP);
    borderRadius.radiusTopStart = Dimension(5.0f, OHOS::Ace::DimensionUnit::VP);
    borderRadius.radiusTopEnd = Dimension(6.0f, OHOS::Ace::DimensionUnit::VP);
    borderRadius.radiusBottomEnd = Dimension(7.0f, OHOS::Ace::DimensionUnit::VP);
    borderRadius.radiusBottomStart = Dimension(8.0f, OHOS::Ace::DimensionUnit::VP);
    borderRadius.multiValued = true;
    ViewAbstract::SetOuterBorderRadius(frameNode, borderRadius);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetOuterBorderRadius().has_value(), true);
    EXPECT_EQ(renderContext->GetOuterBorderRadius()->multiValued, true);
    EXPECT_EQ(renderContext->GetOuterBorderRadius()->radiusTopLeft, Dimension(1.0f, OHOS::Ace::DimensionUnit::VP));
    EXPECT_EQ(renderContext->GetOuterBorderRadius()->radiusTopRight, Dimension(2.0f, OHOS::Ace::DimensionUnit::VP));
    EXPECT_EQ(renderContext->GetOuterBorderRadius()->radiusBottomRight, Dimension(3.0f, OHOS::Ace::DimensionUnit::VP));
    EXPECT_EQ(renderContext->GetOuterBorderRadius()->radiusBottomLeft, Dimension(4.0f, OHOS::Ace::DimensionUnit::VP));
    EXPECT_EQ(renderContext->GetOuterBorderRadius()->radiusTopStart, Dimension(5.0f, OHOS::Ace::DimensionUnit::VP));
    EXPECT_EQ(renderContext->GetOuterBorderRadius()->radiusTopEnd, Dimension(6.0f, OHOS::Ace::DimensionUnit::VP));
    EXPECT_EQ(renderContext->GetOuterBorderRadius()->radiusBottomEnd, Dimension(7.0f, OHOS::Ace::DimensionUnit::VP));
    EXPECT_EQ(renderContext->GetOuterBorderRadius()->radiusBottomStart, Dimension(8.0f, OHOS::Ace::DimensionUnit::VP));
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SetOuterBorderColor
 * @tc.desc: Test SetOuterBorderColor of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFourNg, ViewAbstractResourceObjectTest013, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    g_isConfigChangePerform = true;
    BorderColorProperty borderColor;
    borderColor.leftColor = Color::BLUE;
    borderColor.rightColor = Color::BLACK;
    borderColor.topColor = Color::WHITE;
    borderColor.bottomColor = Color::RED;
    borderColor.startColor = Color::GRAY;
    borderColor.endColor = Color::GREEN;
    borderColor.multiValued = true;
    ViewAbstract::SetOuterBorderColor(frameNode, borderColor);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetOuterBorderColor().has_value(), true);
    EXPECT_EQ(renderContext->GetOuterBorderColor()->multiValued, true);
    EXPECT_EQ(renderContext->GetOuterBorderColor()->leftColor, Color::BLUE);
    EXPECT_EQ(renderContext->GetOuterBorderColor()->rightColor, Color::BLACK);
    EXPECT_EQ(renderContext->GetOuterBorderColor()->topColor, Color::WHITE);
    EXPECT_EQ(renderContext->GetOuterBorderColor()->bottomColor, Color::RED);
    EXPECT_EQ(renderContext->GetOuterBorderColor()->startColor, Color::GRAY);
    EXPECT_EQ(renderContext->GetOuterBorderColor()->endColor, Color::GREEN);
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SetOuterBorderWidth
 * @tc.desc: Test SetOuterBorderWidth of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFourNg, ViewAbstractResourceObjectTest014, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    g_isConfigChangePerform = true;
    BorderWidthProperty borderWidth;
    borderWidth.leftDimen = Dimension(1.0f, OHOS::Ace::DimensionUnit::VP);
    borderWidth.topDimen = Dimension(2.0f, OHOS::Ace::DimensionUnit::VP);
    borderWidth.rightDimen = Dimension(3.0f, OHOS::Ace::DimensionUnit::VP);
    borderWidth.bottomDimen = Dimension(4.0f, OHOS::Ace::DimensionUnit::VP);
    borderWidth.startDimen = Dimension(5.0f, OHOS::Ace::DimensionUnit::VP);
    borderWidth.endDimen = Dimension(6.0f, OHOS::Ace::DimensionUnit::VP);
    borderWidth.multiValued = true;
    ViewAbstract::SetOuterBorderWidth(frameNode, borderWidth);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetOuterBorderWidth().has_value(), true);
    EXPECT_EQ(renderContext->GetOuterBorderWidth()->multiValued, true);
    EXPECT_EQ(renderContext->GetOuterBorderWidth()->leftDimen, Dimension(1.0f, OHOS::Ace::DimensionUnit::VP));
    EXPECT_EQ(renderContext->GetOuterBorderWidth()->topDimen, Dimension(2.0f, OHOS::Ace::DimensionUnit::VP));
    EXPECT_EQ(renderContext->GetOuterBorderWidth()->rightDimen, Dimension(3.0f, OHOS::Ace::DimensionUnit::VP));
    EXPECT_EQ(renderContext->GetOuterBorderWidth()->bottomDimen, Dimension(4.0f, OHOS::Ace::DimensionUnit::VP));
    EXPECT_EQ(renderContext->GetOuterBorderWidth()->startDimen, Dimension(5.0f, OHOS::Ace::DimensionUnit::VP));
    EXPECT_EQ(renderContext->GetOuterBorderWidth()->endDimen, Dimension(6.0f, OHOS::Ace::DimensionUnit::VP));
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SetColorBlend
 * @tc.desc: Test SetColorBlend of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFourNg, ViewAbstractResourceObjectTest015, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    g_isConfigChangePerform = true;
    std::string colorStr = pattern->GetResCacheMapByKey("viewAbstract.colorBlend");
    EXPECT_EQ(colorStr, "");
    std::string bundleName = "com.example.test";
    std::string moduleName = "entry";
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(bundleName, moduleName, 0);
    Color colorBlend = Color::BLUE;
    ViewAbstract::SetColorBlend(frameNode, colorBlend, resObj);
    Color result;
    ResourceParseUtils::ParseResColor(resObj, result);
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    colorStr = pattern->GetResCacheMapByKey("viewAbstract.colorBlend");
    EXPECT_EQ(colorStr, result.ToString());
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SetMask
 * @tc.desc: Test SetMask of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFourNg, ViewAbstractResourceObjectTest016, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    g_isConfigChangePerform = true;
    RefPtr<BasicShape> basicShape = AceType::MakeRefPtr<BasicShape>(BasicShapeType::CIRCLE);
    RefPtr<NG::ProgressMaskProperty> progressMaskProperty = AceType::MakeRefPtr<NG::ProgressMaskProperty>();
    progressMaskProperty->SetMaxValue(200.0f);
    progressMaskProperty->SetColor(Color(0xffff0000));
    progressMaskProperty->SetValue(1.0f);
    auto target = frameNode->GetRenderContext();
    ASSERT_NE(target, nullptr);
    target->UpdateClipMask(basicShape);
    ViewAbstract::SetProgressMask(frameNode, progressMaskProperty);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetProgressMask().has_value(), true);
    g_isConfigChangePerform = true;
    
    ViewStackProcessor::GetInstance()->visualState_ = std::nullopt;
    ViewAbstract::SetMask(frameNode, basicShape);
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    EXPECT_TRUE(result);

    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SetProgressMask
 * @tc.desc: Test SetProgressMask of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFourNg, ViewAbstractResourceObjectTest017, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    g_isConfigChangePerform = true;
    RefPtr<BasicShape> basicShape = AceType::MakeRefPtr<BasicShape>(BasicShapeType::CIRCLE);
    RefPtr<NG::ProgressMaskProperty> progressMaskProperty = AceType::MakeRefPtr<NG::ProgressMaskProperty>();
    progressMaskProperty->SetMaxValue(200.0f);
    progressMaskProperty->SetColor(Color(0xffff0000));
    progressMaskProperty->SetValue(1.0f);
    auto target = frameNode->GetRenderContext();
    ASSERT_NE(target, nullptr);
    target->UpdateClipMask(basicShape);
    ViewAbstract::SetProgressMask(frameNode, progressMaskProperty);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetProgressMask().has_value(), true);
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SetLightPosition
 * @tc.desc: Test SetLightPosition of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFourNg, ViewAbstractResourceObjectTest018, TestSize.Level1)
{
    NG::TranslateOptions option;
    option.x = Dimension(30.0f, OHOS::Ace::DimensionUnit::VP);
    option.y = Dimension(20.0f, OHOS::Ace::DimensionUnit::VP);
    option.z = Dimension(10.0f, OHOS::Ace::DimensionUnit::VP);
    g_isConfigChangePerform = true;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    ViewAbstract::SetLightPosition(frameNode, option);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetLightPosition().has_value(), true);
    EXPECT_EQ(renderContext->GetLightPosition()->x, Dimension(30.0f, OHOS::Ace::DimensionUnit::VP));
    EXPECT_EQ(renderContext->GetLightPosition()->y, Dimension(20.0f, OHOS::Ace::DimensionUnit::VP));
    EXPECT_EQ(renderContext->GetLightPosition()->z, Dimension(10.0f, OHOS::Ace::DimensionUnit::VP));
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SetLightColor
 * @tc.desc: Test SetLightColor of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFourNg, ViewAbstractResourceObjectTest019, TestSize.Level1)
{
    Color color = Color::TRANSPARENT;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    g_isConfigChangePerform = true;
    std::string colorStr = pattern->GetResCacheMapByKey("LightColorRes");
    EXPECT_EQ(colorStr, "");
    std::string bundleName = "com.example.test";
    std::string moduleName = "entry";
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(bundleName, moduleName, 0);
    ViewAbstract::SetLightColor(frameNode, color, resObj);
    Color lightColor;
    ResourceParseUtils::ParseResColor(resObj, lightColor);
    colorStr = pattern->GetResCacheMapByKey("LightColorRes");
    EXPECT_EQ(colorStr, lightColor.ColorToString());
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    g_isConfigChangePerform = false;
    std::string lightSource = pattern->GetResCacheMapByKey("LightColorRes");
    EXPECT_EQ(lightSource, lightColor.ColorToString());
}

/**
 * @tc.name: SetBackShadow
 * @tc.desc: Test SetBackShadow of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFourNg, ViewAbstractResourceObjectTest020, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    g_isConfigChangePerform = true;
    Shadow shadow;
    shadow.SetBlurRadius(10);
    shadow.SetOffsetX(10.0);
    shadow.SetOffsetY(10.0);
    shadow.SetColor(Color(Color::RED));
    shadow.SetShadowType(ShadowType::COLOR);
    ViewAbstract::SetBackShadow(frameNode, shadow);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetBackShadow().has_value(), true);
    EXPECT_EQ(renderContext->GetBackShadow()->GetBlurRadius(), 10);
    EXPECT_EQ(renderContext->GetBackShadow()->GetOffset().GetX(), 10);
    EXPECT_EQ(renderContext->GetBackShadow()->GetOffset().GetY(), 10);
    EXPECT_EQ(renderContext->GetBackShadow()->GetColor(), Color(Color::RED));
    EXPECT_EQ(renderContext->GetBackShadow()->GetShadowType(), ShadowType::COLOR);
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SetForegroundColorStrategy
 * @tc.desc: Test SetForegroundColorStrategy of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFourNg, ViewAbstractResourceObjectTest021, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    g_isConfigChangePerform = true;
    ForegroundColorStrategy strategy = ForegroundColorStrategy::INVERT;
    ViewAbstract::SetForegroundColorStrategy(strategy);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetForegroundColorStrategy().has_value(), true);
    EXPECT_EQ(renderContext->GetForegroundColorStrategyValue(), strategy);
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    EXPECT_EQ(renderContext->GetForegroundColorStrategy().has_value(), true);
    EXPECT_EQ(renderContext->GetForegroundColorStrategyValue(), strategy);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SetForegroundColorStrategy
 * @tc.desc: Test SetForegroundColorStrategy of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFourNg, ViewAbstractResourceObjectTest022, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    g_isConfigChangePerform = true;
    ForegroundColorStrategy strategy = ForegroundColorStrategy::INVERT;
    ViewAbstract::SetForegroundColorStrategy(frameNode, strategy);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetForegroundColorStrategy().has_value(), true);
    EXPECT_EQ(renderContext->GetForegroundColorStrategyValue(), strategy);
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    EXPECT_EQ(renderContext->GetForegroundColorStrategy().has_value(), true);
    EXPECT_EQ(renderContext->GetForegroundColorStrategyValue(), strategy);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SetClipEdge
 * @tc.desc: Test SetClipEdge of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFourNg, ViewAbstract_SetClipEdge1, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    g_isConfigChangePerform = true;
    ViewAbstract::SetClipEdge(true);
    std::string shapeStr = pattern->GetResCacheMapByKey("clipShape");
    EXPECT_EQ(shapeStr, "");
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SetClipEdge
 * @tc.desc: Test SetClipEdge of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFourNg, ViewAbstract_SetClipEdge2, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    g_isConfigChangePerform = true;
    ViewAbstract::SetClipEdge(frameNode, true);
    std::string shapeStr = pattern->GetResCacheMapByKey("clipShape");
    EXPECT_EQ(shapeStr, "");
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: CreateWithColorResourceObj
 * @tc.desc: Test CreateWithColorResourceObj of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFourNg, CreateWithColorResourceObj, TestSize.Level1)
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
     * @tc.steps: step2. Create resource objects and configure popup parameters.
     * @tc.expected: step2. Resource objects and popup parameters are initialized correctly.
     */
    std::vector<ResourceObjectParams> params = { { "", ResourceObjectParamType::NONE } };
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(-1, 10003, params, "", "", 0);
    ASSERT_NE(resObj, nullptr);

    RefPtr<PopupParam> param = AceType::MakeRefPtr<PopupParam>();
    ASSERT_NE(param, nullptr);
    param->SetTextColorResourceObject(resObj);
    param->SetPopupColorResourceObject(resObj);
    param->SetMaskColorResourceObject(resObj);

    RefPtr<ResourceObject> boolResObj = AceType::MakeRefPtr<ResourceObject>(-1, 10005, params, "", "", 0);
    ASSERT_NE(resObj, nullptr);
    param->SetMaskResourceObject(boolResObj);

    RefPtr<ResourceObject> defaultResObj = AceType::MakeRefPtr<ResourceObject>("", "", 0);
    ASSERT_NE(defaultResObj, nullptr);

    /**
     * @tc.steps: step3. Test CreateWithResourceObj for text color resource.
     * @tc.expected: step3. Text color resource is applied and type string is correct.
     */
    PopupType type = POPUPTYPE_TEXTCOLOR;
    auto textColorResourceObject = param->GetTextColorResourceObject();
    ASSERT_NE(textColorResourceObject, nullptr);
    viewAbstractModelNG.CreateWithResourceObj(frameNode, textColorResourceObject, type);
    pattern->OnColorModeChange(1);
    auto textColorStr = viewAbstractModelNG.PopupTypeStr(type);
    EXPECT_EQ(textColorStr, "TextColor");

    /**
     * @tc.steps: step4. Test CreateWithResourceObj for popup color resource.
     * @tc.expected: step4. Popup color resource is applied and type string is correct.
     */
    type = POPUPTYPE_POPUPCOLOR;
    auto popupColorResourceObject = param->GetPopupColorResourceObject();
    ASSERT_NE(textColorResourceObject, nullptr);
    viewAbstractModelNG.CreateWithResourceObj(frameNode, popupColorResourceObject, type);
    pattern->OnColorModeChange(1);
    auto popupColorStr = viewAbstractModelNG.PopupTypeStr(type);
    EXPECT_EQ(popupColorStr, "PopupColor");

    /**
     * @tc.steps: step5. Test CreateWithResourceObj for mask color resource.
     * @tc.expected: step5. Mask color resource is applied and type string is correct.
     */
    type = POPUPTYPE_MASKCOLOR;
    auto maskColorResourceObject = param->GetMaskColorResourceObject();
    ASSERT_NE(textColorResourceObject, nullptr);
    viewAbstractModelNG.CreateWithResourceObj(frameNode, maskColorResourceObject, type);
    pattern->OnColorModeChange(1);
    auto maskColorStr = viewAbstractModelNG.PopupTypeStr(type);
    EXPECT_EQ(maskColorStr, "MaskColor");

    /**
     * @tc.steps: step6. Test CreateWithResourceObj for mask resource without type.
     * @tc.expected: step6. Mask resource is applied with correct instance ID.
     */
    auto maskResourceObject = param->GetMaskResourceObject();
    ASSERT_NE(textColorResourceObject, nullptr);
    viewAbstractModelNG.CreateWithResourceObj(frameNode, maskResourceObject);
    pattern->OnColorModeChange(1);
    EXPECT_EQ(maskResourceObject->GetInstanceId(), 0);

    /**
     * @tc.steps: step7. Test CreateWithResourceObj with invalid type.
     * @tc.expected: step7. Type string for invalid type is empty.
     */
    type = static_cast<PopupType>(POPUPTYPE_MASKCOLOR + 1);
    viewAbstractModelNG.CreateWithResourceObj(frameNode, defaultResObj, type);
    auto defaultStr = viewAbstractModelNG.PopupTypeStr(type);
    EXPECT_EQ(defaultStr, "");
}
} // namespace OHOS::Ace::NG