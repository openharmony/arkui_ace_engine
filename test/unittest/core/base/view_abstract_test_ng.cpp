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
void ViewAbstractTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->pipelineContext_ = PipelineBase::GetCurrentContext();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    PipelineBase::GetCurrentContext()->SetThemeManager(themeManager);
    PipelineBase::GetCurrentContext()->SetEventManager(AceType::MakeRefPtr<EventManager>());
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<PopupTheme>()));
}

void ViewAbstractTestNg::TearDownTestSuite()
{
    MockContainer::Current()->pipelineContext_ = nullptr;
    MockPipelineContext::TearDown();
}
/**
 * @tc.name: ViewAbstractTest001
 * @tc.desc: SetWidth、SetHeight、SetMinWidth、SetMinHeight、SetMaxWidth、SetMaxHeight、ClearWidthOrHeight
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1.Using static methods to set component properties
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    ViewAbstract::SetWidth(NG::CalcLength(WIDTH));
    ViewAbstract::SetHeight(NG::CalcLength(HEIGHT));
    ViewAbstract::SetMinWidth(NG::CalcLength(MIN_WIDTH));
    ViewAbstract::SetMinHeight(NG::CalcLength(MIN_HEIGHT));
    ViewAbstract::SetMaxWidth(NG::CalcLength(MIN_WIDTH));
    ViewAbstract::SetMaxHeight(NG::CalcLength(MIN_HEIGHT));
    ViewAbstract::ResetAspectRatio();
    ViewAbstract::SetDrawModifier(nullptr);

    /**
     * @tc.expected: Successfully set various properties of the top node on the stack
     */
    EXPECT_EQ(layoutProperty->calcLayoutConstraint_->selfIdealSize->Width(), NG::CalcLength(WIDTH));
    EXPECT_EQ(layoutProperty->calcLayoutConstraint_->selfIdealSize->Height(), NG::CalcLength(HEIGHT));
    EXPECT_EQ(layoutProperty->calcLayoutConstraint_->minSize->Width(), NG::CalcLength(MIN_WIDTH));
    EXPECT_EQ(layoutProperty->calcLayoutConstraint_->minSize->Height(), NG::CalcLength(MIN_HEIGHT));
    EXPECT_EQ(layoutProperty->calcLayoutConstraint_->maxSize->Width(), NG::CalcLength(MIN_WIDTH));
    EXPECT_EQ(layoutProperty->calcLayoutConstraint_->maxSize->Height(), NG::CalcLength(MIN_HEIGHT));

    /**
     * @tc.steps: step2.Static methods set properties for other nodes
     */
    auto newNode = FrameNode::GetOrCreateFrameNode("newframenode", 10, []() { return AceType::MakeRefPtr<Pattern>(); });
    ViewAbstract::SetWidth(AceType::RawPtr(newNode), NG::CalcLength(WIDTH));
    ViewAbstract::SetHeight(AceType::RawPtr(newNode), NG::CalcLength(HEIGHT));
    ViewAbstract::SetMinWidth(AceType::RawPtr(newNode), NG::CalcLength(MIN_WIDTH));
    ViewAbstract::SetMinHeight(AceType::RawPtr(newNode), NG::CalcLength(MIN_HEIGHT));
    ViewAbstract::SetMaxWidth(AceType::RawPtr(newNode), NG::CalcLength(MIN_WIDTH));
    ViewAbstract::SetMaxHeight(AceType::RawPtr(newNode), NG::CalcLength(MIN_HEIGHT));
    auto newProperty = frameNode->GetLayoutProperty();

    /**
     * @tc.expected: Successfully set various attributes of the new node
     */
    EXPECT_EQ(newProperty->calcLayoutConstraint_->selfIdealSize->Width(), NG::CalcLength(WIDTH));
    EXPECT_EQ(newProperty->calcLayoutConstraint_->selfIdealSize->Height(), NG::CalcLength(HEIGHT));
    EXPECT_EQ(newProperty->calcLayoutConstraint_->minSize->Width(), NG::CalcLength(MIN_WIDTH));
    EXPECT_EQ(newProperty->calcLayoutConstraint_->minSize->Height(), NG::CalcLength(MIN_HEIGHT));
    EXPECT_EQ(newProperty->calcLayoutConstraint_->maxSize->Width(), NG::CalcLength(MIN_WIDTH));
    EXPECT_EQ(newProperty->calcLayoutConstraint_->maxSize->Height(), NG::CalcLength(MIN_HEIGHT));

    ViewAbstract::ClearWidthOrHeight(true);
    ViewAbstract::ClearWidthOrHeight(AceType::RawPtr(newNode), true);
    EXPECT_EQ(layoutProperty->calcLayoutConstraint_->selfIdealSize->Width(), std::nullopt);
    EXPECT_EQ(newProperty->calcLayoutConstraint_->selfIdealSize->Width(), std::nullopt);
}

/**
 * @tc.name: ViewAbstractTest002
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1.push FrameNode is not null, related function is called.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);

    ViewAbstract::SetWidth(NG::CalcLength(WIDTH));
    ViewAbstract::SetHeight(NG::CalcLength(HEIGHT));
    ViewAbstract::SetMinWidth(NG::CalcLength(MIN_WIDTH));
    ViewAbstract::SetMinHeight(NG::CalcLength(MIN_HEIGHT));
    ViewAbstract::SetMaxWidth(NG::CalcLength(MIN_WIDTH));
    ViewAbstract::SetMaxHeight(NG::CalcLength(MIN_HEIGHT));
    ViewAbstract::ResetAspectRatio();
    ViewAbstract::ClearWidthOrHeight(true);

    /**
     * @tc.expected: Return expected results..
     */
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    ViewStackProcessor::GetInstance()->instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest003
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1.The FrameNode is null, related function is called.
     */
    ViewAbstract::SetAspectRatio(RATIO);
    ViewAbstract::SetBackgroundColor(BLUE);
    ViewAbstract::SetBackgroundColor(nullptr, BLUE);
    ViewAbstract::SetBackgroundImage(imageSourceInfo);
    ViewAbstract::SetBackgroundImage(nullptr, imageSourceInfo);
    ViewAbstract::SetBackgroundImageSize(BACKGROUNDSIZE);
    ViewAbstract::SetBackgroundImageSize(nullptr, BACKGROUNDSIZE);
    ViewAbstract::SetBackgroundImageSize(nullptr, BACKGROUNDSIZE, true);
    ViewAbstract::SetBackgroundImagePosition(BACKGROUNDPOSITION);
    ViewAbstract::SetBackgroundImagePosition(nullptr, BACKGROUNDPOSITION);
    ViewAbstract::SetBackgroundImagePosition(nullptr, BACKGROUNDPOSITION, true);
    ViewAbstract::SetPixelRound(0);
    ChainInfo chainInfo;
    chainInfo.direction = LineDirection::HORIZONTAL;
    chainInfo.style = ChainStyle::SPREAD;
    ViewAbstract::SetChainStyle(chainInfo);
    ViewAbstract::SetChainStyle(AceType::RawPtr(FRAME_NODE_REGISTER), chainInfo);
    ViewAbstract::SetLayoutWeight(TEN);
    ViewAbstract::SetLayoutWeight(AceType::RawPtr(FRAME_NODE_REGISTER), TEN);
    ViewAbstract::SetBias(biasPair);
    ViewAbstract::SetBias(nullptr, biasPair);
    ViewAbstract::SetOuterBorderRadius(ZERO);
    ViewAbstract::SetOuterBorderRadius(nullptr, ZERO);
    NG::BorderRadiusProperty borderRadius;
    ViewAbstract::SetOuterBorderRadius(borderRadius);
    ViewAbstract::SetOuterBorderRadius(nullptr, borderRadius);
    ViewAbstract::SetOuterBorderColor(BLUE);
    ViewAbstract::SetOuterBorderColor(nullptr, BLUE);
    NG::BorderColorProperty borderColor;
    ViewAbstract::SetOuterBorderColor(borderColor);
    ViewAbstract::SetOuterBorderColor(nullptr, borderColor);
    ViewAbstract::SetOuterBorderWidth(ZERO);
    ViewAbstract::SetOuterBorderWidth(nullptr, ZERO);
    NG::BorderWidthProperty borderWidth;
    ViewAbstract::SetOuterBorderWidth(borderWidth);
    ViewAbstract::SetOuterBorderWidth(nullptr, borderWidth);
    auto borderStyle = static_cast<BorderStyle>(INDEX);
    ViewAbstract::SetOuterBorderStyle(borderStyle);
    ViewAbstract::SetOuterBorderStyle(nullptr, borderStyle);
    NG::BorderStyleProperty borderStyleProperty;
    ViewAbstract::SetOuterBorderStyle(borderStyleProperty);
    ViewAbstract::SetOuterBorderStyle(nullptr, borderStyleProperty);
    BlendMode blendMode = BlendMode::NONE;
    ViewAbstract::SetBlendMode(blendMode);
    ViewAbstract::SetBlendMode(AceType::RawPtr(FRAME_NODE_REGISTER), blendMode);
    BlendApplyType blendApplyType = BlendApplyType::FAST;
    ViewAbstract::SetBlendApplyType(blendApplyType);
    ViewAbstract::SetBlendApplyType(AceType::RawPtr(FRAME_NODE_REGISTER), blendApplyType);

    BlurStyleOption blurStyleOption;
    blurStyleOption.blurStyle = BlurStyle::NO_MATERIAL;
    blurStyleOption.colorMode = ThemeColorMode::SYSTEM;
    blurStyleOption.adaptiveColor = AdaptiveColor::DEFAULT;
    ViewAbstract::SetBackgroundBlurStyle(blurStyleOption);
    ViewAbstract::SetBackgroundBlurStyle(AceType::RawPtr(FRAME_NODE_REGISTER), blurStyleOption);
    CalcDimension dimensionRadius(0.0);
    ViewAbstract::SetLightPosition(dimensionRadius, dimensionRadius, dimensionRadius);
    ViewAbstract::SetLightPosition(nullptr, dimensionRadius, dimensionRadius, dimensionRadius);
    ViewAbstract::SetLightIntensity(RATIO);
    ViewAbstract::SetLightIntensity(nullptr, RATIO);
    ViewAbstract::SetIlluminatedBorderWidth(ZERO);
    ViewAbstract::SetIlluminatedBorderWidth(nullptr, ZERO);
    ViewAbstract::SetBloom(RATIO);
    ViewAbstract::SetBloom(nullptr, RATIO);
    std::map<AlignDirection, AlignRule> alignRules;
    ViewAbstract::SetAlignRules(alignRules);
    ViewAbstract::SetAlignRules(AceType::RawPtr(FRAME_NODE_REGISTER), alignRules);
    auto repeat = static_cast<ImageRepeat>(INDEX);
    ViewAbstract::SetBackgroundImageRepeat(repeat);
    ViewAbstract::SetBackgroundImageRepeat(nullptr, repeat);
    auto direction = static_cast<TextDirection>(INDEX);
    ViewAbstract::SetLayoutDirection(direction);
    ViewAbstract::SetLayoutDirection(AceType::RawPtr(FRAME_NODE_REGISTER), direction);
    ViewAbstract::GetAlignRules(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::SetBackgroundImageSyncMode(true);

    /**
     * @tc.expected: Return expected results..
     */
    EXPECT_NE(ViewStackProcessor::GetInstance()->GetMainElementNode(), nullptr);
}

/**
 * @tc.name: ViewAbstractTest004
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1.push FrameNode is not null, related function is called.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);

    ViewAbstract::SetAspectRatio(RATIO);
    ViewAbstract::SetBackgroundColor(BLUE);
    ViewAbstract::SetBackgroundColor(nullptr, BLUE);
    ViewAbstract::SetBackgroundImage(imageSourceInfo);
    ViewAbstract::SetBackgroundImage(nullptr, imageSourceInfo);
    ViewAbstract::SetBackgroundImageSize(BACKGROUNDSIZE);
    ViewAbstract::SetBackgroundImageSize(nullptr, BACKGROUNDSIZE);
    ViewAbstract::SetBackgroundImageSize(nullptr, BACKGROUNDSIZE, true);
    ViewAbstract::SetBackgroundImagePosition(BACKGROUNDPOSITION);
    ViewAbstract::SetBackgroundImagePosition(nullptr, BACKGROUNDPOSITION);
    ViewAbstract::SetBackgroundImagePosition(nullptr, BACKGROUNDPOSITION, true);
    ViewAbstract::SetPixelRound(0);

    ChainInfo chainInfo;
    chainInfo.direction = LineDirection::HORIZONTAL;
    chainInfo.style = ChainStyle::SPREAD;
    ViewAbstract::SetChainStyle(chainInfo);
    ViewAbstract::SetChainStyle(AceType::RawPtr(FRAME_NODE_REGISTER), chainInfo);
    ViewAbstract::SetBias(biasPair);
    ViewAbstract::SetBias(nullptr, biasPair);
    ViewAbstract::SetOuterBorderRadius(ZERO);
    ViewAbstract::SetOuterBorderRadius(nullptr, ZERO);
    NG::BorderRadiusProperty borderRadius;
    ViewAbstract::SetOuterBorderRadius(borderRadius);
    ViewAbstract::SetOuterBorderRadius(nullptr, borderRadius);
    ViewAbstract::SetOuterBorderColor(BLUE);
    ViewAbstract::SetOuterBorderColor(nullptr, BLUE);
    NG::BorderColorProperty borderColor;
    ViewAbstract::SetOuterBorderColor(borderColor);
    ViewAbstract::SetOuterBorderColor(nullptr, borderColor);
    ViewAbstract::SetOuterBorderWidth(ZERO);
    ViewAbstract::SetOuterBorderWidth(nullptr, ZERO);
    NG::BorderWidthProperty borderWidth;
    ViewAbstract::SetOuterBorderWidth(borderWidth);
    ViewAbstract::SetOuterBorderWidth(nullptr, borderWidth);
    auto borderStyle = static_cast<BorderStyle>(INDEX);
    ViewAbstract::SetOuterBorderStyle(borderStyle);
    ViewAbstract::SetOuterBorderStyle(nullptr, borderStyle);
    NG::BorderStyleProperty borderStyleProperty;
    ViewAbstract::SetOuterBorderStyle(borderStyleProperty);
    ViewAbstract::SetOuterBorderStyle(nullptr, borderStyleProperty);
    ViewAbstract::SetLayoutWeight(TEN);
    BlendMode blendMode = BlendMode::NONE;
    ViewAbstract::SetBlendMode(blendMode);
    BlendApplyType blendApplyType = BlendApplyType::FAST;
    ViewAbstract::SetBlendApplyType(blendApplyType);

    BlurStyleOption blurStyleOption;
    blurStyleOption.blurStyle = BlurStyle::NO_MATERIAL;
    blurStyleOption.colorMode = ThemeColorMode::SYSTEM;
    blurStyleOption.adaptiveColor = AdaptiveColor::DEFAULT;
    ViewAbstract::SetBackgroundBlurStyle(blurStyleOption);

    std::map<AlignDirection, AlignRule> alignRules;
    ViewAbstract::SetAlignRules(alignRules);
    auto repeat = static_cast<ImageRepeat>(INDEX);
    ViewAbstract::SetBackgroundImageRepeat(repeat);
    ViewAbstract::SetBackgroundImageRepeat(nullptr, repeat);
    auto direction = static_cast<TextDirection>(INDEX);
    ViewAbstract::SetLayoutDirection(direction);
    CalcDimension dimensionRadius(0.0);
    ViewAbstract::SetLightPosition(dimensionRadius, dimensionRadius, dimensionRadius);
    ViewAbstract::SetLightPosition(nullptr, dimensionRadius, dimensionRadius, dimensionRadius);
    ViewAbstract::SetLightIntensity(RATIO);
    ViewAbstract::SetLightIntensity(nullptr, RATIO);
    Color color = Color::TRANSPARENT;
    ViewAbstract::SetLightColor(color);
    ViewAbstract::SetLightColor(nullptr, color);
    ViewAbstract::SetIlluminatedBorderWidth(ZERO);
    ViewAbstract::SetIlluminatedBorderWidth(nullptr, ZERO);
    ViewAbstract::SetBloom(RATIO);
    ViewAbstract::SetBloom(nullptr, RATIO);

    /**
     * @tc.expected: Return expected results.
     */
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty<LayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    ViewStackProcessor::GetInstance()->instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest005
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1.The FrameNode is null, related function is called.
     */
    auto alignSelf = static_cast<FlexAlign>(INDEX);
    ViewAbstract::SetAlignSelf(alignSelf);
    ViewAbstract::SetFlexShrink(RATIO);
    ViewAbstract::SetFlexGrow(RATIO);
    ViewAbstract::SetFlexBasis(WIDTH);
    ViewAbstract::SetDisplayIndex(INDEX);
    ViewAbstract::SetDisplayIndex(nullptr, INDEX);

    ViewAbstract::SetPadding(NG::CalcLength(WIDTH));
    ViewAbstract::SetMargin(NG::CalcLength(WIDTH));
    ViewAbstract::SetBorderRadius(WIDTH);
    ViewAbstract::SetBorderColor(BLUE);
    ViewAbstract::SetBorderWidth(WIDTH);
    auto borderStyle = static_cast<BorderStyle>(INDEX);
    ViewAbstract::SetBorderStyle(borderStyle);
    ViewAbstract::SetBorderStyle(nullptr, borderStyle);
    ViewAbstract::SetAutoEventParam(VALUE_X);

    /**
     * @tc.expected: Return expected results..
     */
    EXPECT_NE(ViewStackProcessor::GetInstance()->GetMainElementNode(), nullptr);
}

/**
 * @tc.name: ViewAbstractTest006
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1.push FrameNode is not null, related function is called.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);

    auto alignSelf = static_cast<FlexAlign>(INDEX);
    ViewAbstract::SetAlignSelf(alignSelf);
    ViewAbstract::SetFlexShrink(RATIO);
    ViewAbstract::SetFlexShrink(AceType::RawPtr(FRAME_NODE_REGISTER), RATIO);
    ViewAbstract::SetFlexGrow(RATIO);
    ViewAbstract::SetFlexGrow(AceType::RawPtr(FRAME_NODE_REGISTER), RATIO);
    ViewAbstract::SetFlexBasis(WIDTH);
    ViewAbstract::SetDisplayIndex(INDEX);
    ViewAbstract::SetDisplayIndex(nullptr, INDEX);

    ViewAbstract::SetPadding(NG::CalcLength(WIDTH));
    ViewAbstract::SetMargin(NG::CalcLength(WIDTH));
    ViewAbstract::SetBorderRadius(WIDTH);
    ViewAbstract::SetBorderColor(BLUE);
    ViewAbstract::SetBorderWidth(WIDTH);
    auto borderStyle = static_cast<BorderStyle>(INDEX);
    ViewAbstract::SetBorderStyle(borderStyle);
    ViewAbstract::SetBorderStyle(nullptr, borderStyle);

    /**
     * @tc.expected: Return expected results.
     */
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty<LayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    ViewStackProcessor::GetInstance()->instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest007
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1.The FrameNode is null, related function is called.
     */
    NG::PaddingProperty paddings;
    ViewAbstract::SetPadding(paddings);

    NG::MarginProperty margins;
    ViewAbstract::SetMargin(margins);

    NG::BorderRadiusProperty borderRadius;
    ViewAbstract::SetBorderRadius(borderRadius);
    ViewAbstract::SetBorderRadius(nullptr, borderRadius);

    NG::BorderColorProperty borderColors;
    ViewAbstract::SetBorderColor(borderColors);

    NG::BorderWidthProperty borderWidth;
    ViewAbstract::SetBorderWidth(borderWidth);
    ViewAbstract::SetBorderWidth(nullptr, borderWidth);

    NG::BorderStyleProperty borderStyles;
    ViewAbstract::SetBorderStyle(borderStyles);
    ViewAbstract::SetBorderStyle(nullptr, borderStyles);

    /**
     * @tc.expected: Return expected results..
     */
    EXPECT_NE(ViewStackProcessor::GetInstance()->GetMainElementNode(), nullptr);
}

/**
 * @tc.name: ViewAbstractTest008
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1.push FrameNode is not null, related function is called.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);

    NG::PaddingProperty paddings;
    ViewAbstract::SetPadding(paddings);

    NG::MarginProperty margins;
    ViewAbstract::SetMargin(margins);

    NG::BorderRadiusProperty borderRadius;
    ViewAbstract::SetBorderRadius(borderRadius);

    NG::BorderColorProperty borderColors;
    ViewAbstract::SetBorderColor(borderColors);
    ViewAbstract::SetBorderColor(nullptr, borderColors);

    NG::BorderWidthProperty borderWidth;
    ViewAbstract::SetBorderWidth(borderWidth);

    NG::BorderStyleProperty borderStyles;
    ViewAbstract::SetBorderStyle(borderStyles);
    ViewAbstract::SetBorderStyle(nullptr, borderStyles);

    /**
     * @tc.expected: Return expected results.
     */
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty<LayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    ViewStackProcessor::GetInstance()->instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest009
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1.The FrameNode is null, related function is called.
     */
    GestureEventFunc tapEventFunc;
    ViewAbstract::SetOnClick(std::move(tapEventFunc));
    ViewAbstract::SetOnClick(AceType::RawPtr(FRAME_NODE_REGISTER), std::move(tapEventFunc));
    TouchEventFunc touchEventFunc;
    ViewAbstract::SetOnTouch(std::move(touchEventFunc));
    ViewAbstract::SetOnTouch(AceType::RawPtr(FRAME_NODE_REGISTER), std::move(touchEventFunc));
    OnMouseEventFunc onMouseEventFunc;
    ViewAbstract::SetOnMouse(std::move(onMouseEventFunc));
    OnHoverFunc onHoverEventFunc;
    ViewAbstract::SetOnHover(std::move(onHoverEventFunc));
    ViewAbstract::SetJSFrameNodeOnHover(AceType::RawPtr(FRAME_NODE_REGISTER), std::move(onHoverEventFunc));
    ViewAbstract::ClearJSFrameNodeOnHover(AceType::RawPtr(FRAME_NODE_REGISTER));
    OnKeyConsumeFunc onKeyCallback;
    ViewAbstract::SetOnKeyEvent(std::move(onKeyCallback));
    DragPreviewOption dragPreviewOption;
    ViewAbstract::SetDragPreviewOptions(dragPreviewOption);
    ViewAbstract::SetDragPreviewOptions(AceType::RawPtr(FRAME_NODE_REGISTER), dragPreviewOption);
    NG::DragDropInfo info;
    ViewAbstract::SetDragPreview(info);

    auto hoverEffect = static_cast<HoverEffectType>(INDEX);
    ViewAbstract::SetHoverEffect(hoverEffect);
    ViewAbstract::SetHoverEffect(AceType::RawPtr(FRAME_NODE_REGISTER), hoverEffect);

    ViewAbstract::SetFocusable(false);
    ViewAbstract::SetFocusable(AceType::RawPtr(FRAME_NODE_REGISTER), false);
    ViewAbstract::SetEnabled(false);
    ViewAbstract::SetEnabled(AceType::RawPtr(FRAME_NODE_REGISTER), false);
    ViewAbstract::SetOnFocus(callback);
    ViewAbstract::SetOnBlur(callback);

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_NE(ViewStackProcessor::GetInstance()->GetMainElementNode(), nullptr);
}

/**
 * @tc.name: ViewAbstractTest010
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1.push FrameNode is not null, related function is called.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);

    GestureEventFunc tapEventFunc;
    ViewAbstract::SetOnClick(std::move(tapEventFunc));
    TouchEventFunc touchEventFunc;
    ViewAbstract::SetOnTouch(std::move(touchEventFunc));
    OnMouseEventFunc onMouseEventFunc;
    ViewAbstract::SetOnMouse(std::move(onMouseEventFunc));
    OnHoverFunc onHoverEventFunc;
    ViewAbstract::SetOnHover(std::move(onHoverEventFunc));
    OnKeyConsumeFunc onKeyCallback;
    ViewAbstract::SetOnKeyEvent(std::move(onKeyCallback));

    auto hoverEffect = static_cast<HoverEffectType>(INDEX);
    ViewAbstract::SetHoverEffect(hoverEffect);

    ViewAbstract::SetFocusable(true);
    ViewAbstract::SetOnFocus(callback);
    ViewAbstract::SetOnBlur(callback);
    ViewAbstract::SetFlexBasis(VALUE);

    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    focusHub->focusable_ = true;
    focusHub->parentFocusable_ = true;
    ViewAbstract::SetVisibility(VisibleType::VISIBLE);
    ViewAbstract::SetEnabled(true);

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_FALSE(focusHub->IsFocusableScope());
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty<LayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    ViewStackProcessor::GetInstance()->instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest011
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1.The FrameNode is null, related function is called.
     */
    ViewAbstract::SetTabIndex(INDEX);
    ViewAbstract::SetTabIndex(AceType::RawPtr(FRAME_NODE_REGISTER), INDEX);
    ViewAbstract::SetFocusOnTouch(false);
    ViewAbstract::SetFocusOnTouch(AceType::RawPtr(FRAME_NODE_REGISTER), false);
    ViewAbstract::SetDefaultFocus(false);
    ViewAbstract::SetGroupDefaultFocus(false);
    ViewAbstract::SetGroupDefaultFocus(AceType::RawPtr(FRAME_NODE_REGISTER), false);
    ViewAbstract::SetTouchable(false);
    ViewAbstract::SetTouchable(AceType::RawPtr(FRAME_NODE_REGISTER), false);
    ViewAbstract::SetOnAppear(callback);
    ViewAbstract::SetOnAppear(AceType::RawPtr(FRAME_NODE_REGISTER), callback);
    ViewAbstract::SetOnDisappear(callback);
    ViewAbstract::SetOnDisappear(AceType::RawPtr(FRAME_NODE_REGISTER), callback);
    ViewAbstract::GetFocusable(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetDefaultFocus(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetResponseRegion(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetOverlay(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::SetNeedFocus(AceType::RawPtr(FRAME_NODE_REGISTER), false);
    ViewAbstract::GetNeedFocus(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetOpacity(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetBorderWidth(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetLayoutBorderWidth(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetBorderRadius(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetBorderColor(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetBorderStyle(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetZIndex(AceType::RawPtr(FRAME_NODE_REGISTER));

    auto hitTestMode = static_cast<HitTestMode>(INDEX);
    ViewAbstract::SetHitTestMode(hitTestMode);
    ViewAbstract::SetHitTestMode(AceType::RawPtr(FRAME_NODE_REGISTER), hitTestMode);

    std::vector<DimensionRect> responseRegion;
    ViewAbstract::SetResponseRegion(std::move(responseRegion));
    ViewAbstract::SetResponseRegion(AceType::RawPtr(FRAME_NODE_REGISTER), std::move(responseRegion));
    std::function<DragDropInfo(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&)> onDragStart;
    ViewAbstract::SetOnDragStart(std::move(onDragStart));
    std::function<void(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&)> onDragEnter;
    ViewAbstract::SetOnDragEnter(std::move(onDragEnter));
    std::function<void(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&)> onDragLeave;
    ViewAbstract::SetOnDragLeave(std::move(onDragLeave));
    std::function<void(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&)> onDragMove;
    ViewAbstract::SetOnDragMove(std::move(onDragMove));
    std::function<void(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&)> onDrop;
    ViewAbstract::SetOnDrop(std::move(onDrop));
    Alignment alignment;
    ViewAbstract::SetAlign(std::move(alignment));
    ViewAbstract::SetAlign(nullptr, std::move(alignment));

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_NE(ViewStackProcessor::GetInstance()->GetMainElementNode(), nullptr);
}

/**
 * @tc.name: ViewAbstractTest012
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1.push FrameNode is not null, related function is called.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);

    ViewAbstract::SetTabIndex(INDEX);
    ViewAbstract::SetFocusOnTouch(false);
    ViewAbstract::SetDefaultFocus(false);
    ViewAbstract::SetDefaultFocus(AceType::RawPtr(FRAME_NODE_REGISTER), false);
    ViewAbstract::SetGroupDefaultFocus(false);
    ViewAbstract::SetTouchable(false);
    ViewAbstract::SetOnAppear(callback);
    ViewAbstract::SetOnDisappear(callback);
    auto hitTestMode = static_cast<HitTestMode>(INDEX);
    ViewAbstract::SetHitTestMode(hitTestMode);

    std::vector<DimensionRect> responseRegion;
    ViewAbstract::SetResponseRegion(std::move(responseRegion));
    std::function<DragDropInfo(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&)> onDragStart;
    ViewAbstract::SetOnDragStart(std::move(onDragStart));
    std::function<void(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&)> onDragEnter;
    ViewAbstract::SetOnDragEnter(std::move(onDragEnter));
    std::function<void(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&)> onDragLeave;
    ViewAbstract::SetOnDragLeave(std::move(onDragLeave));
    std::function<void(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&)> onDragMove;
    ViewAbstract::SetOnDragMove(std::move(onDragMove));
    std::function<void(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&)> onDrop;
    ViewAbstract::SetOnDrop(std::move(onDrop));
    Alignment alignment;
    ViewAbstract::SetAlign(std::move(alignment));

    /**
     * @tc.expected: Return expected results.
     */
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty<LayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    ViewStackProcessor::GetInstance()->instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest013
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1.The FrameNode is null, related function is called.
     */
    auto visible = static_cast<VisibleType>(INDEX);
    ViewAbstract::SetVisibility(std::move(visible));
    ViewAbstract::SetVisibility(AceType::RawPtr(FRAME_NODE_REGISTER), std::move(visible));
    ViewAbstract::SetGeometryTransition(srcimages);
    ViewAbstract::SetGeometryTransition(AceType::RawPtr(FRAME_NODE_REGISTER), srcimages, false, true);
    ViewAbstract::SetOpacity(OPACITYS);
    ViewAbstract::SetOpacity(AceType::RawPtr(FRAME_NODE_REGISTER), OPACITYS);
    ViewAbstract::SetZIndex(FOUF);

    OffsetT<Dimension> value = { WIDTH, HEIGHT };
    ViewAbstract::SetPosition(value);
    ViewAbstract::SetPosition(AceType::RawPtr(FRAME_NODE_REGISTER), value);
    ViewAbstract::SetOffset(value);
    ViewAbstract::SetOffset(AceType::RawPtr(FRAME_NODE_REGISTER), value);
    ViewAbstract::MarkAnchor(value);
    ViewAbstract::MarkAnchor(AceType::RawPtr(FRAME_NODE_REGISTER), value);
    VectorF scale(1.0f, 1.0f);
    ViewAbstract::SetScale(scale);
    ViewAbstract::SetScale(AceType::RawPtr(FRAME_NODE_REGISTER), scale);
    DimensionOffset valueOffset = { WIDTH, HEIGHT };
    ViewAbstract::SetPivot(AceType::RawPtr(FRAME_NODE_REGISTER), valueOffset);
    ViewAbstract::GetVisibility(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetClip(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetClipShape(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetTransform(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetHitTestBehavior(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetPosition(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetShadow(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetSweepGradient(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetRadialGradient(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetMask(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetMaskProgress(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetBlendMode(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetDirection(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetAlignSelf(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetFlexGrow(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetFlexShrink(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetFlexBasis(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetMinWidth(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetMaxWidth(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetMinHeight(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetMaxHeight(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetGrayScale(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetInvert(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetSepia(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetContrast(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetForegroundColor(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetScale(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetRotate(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetBrightness(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetSaturate(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetBackgroundImagePosition(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetLinearGradient(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetAlign(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetWidth(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetHeight(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetBackgroundColor(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetBackgroundImageSrc(AceType::RawPtr(FRAME_NODE_REGISTER));
    auto repeat = static_cast<ImageRepeat>(INDEX);
    ViewAbstract::SetBackgroundImageRepeat(AceType::RawPtr(FRAME_NODE_REGISTER), repeat);
    ViewAbstract::GetBackgroundImageRepeat(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetPadding(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetConfigSize(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetEnabled(AceType::RawPtr(FRAME_NODE_REGISTER));

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_NE(ViewStackProcessor::GetInstance()->GetMainElementNode(), nullptr);
}

/**
 * @tc.name: ViewAbstractTest014
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1.push FrameNode is not null, related function is called.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);

    auto visible = static_cast<VisibleType>(INDEX);
    ViewAbstract::SetVisibility(std::move(visible));
    ViewAbstract::SetGeometryTransition(srcimages);
    ViewAbstract::SetOpacity(OPACITYS);
    ViewAbstract::SetZIndex(FOUF);
    ViewAbstract::SetZIndex(nullptr, FOUF);

    OffsetT<Dimension> value = { WIDTH, HEIGHT };
    ViewAbstract::SetPosition(value);
    ViewAbstract::SetOffset(value);
    ViewAbstract::MarkAnchor(value);
    viewAbstractModelNG.SetScale(-1.0f, -1.0f, 0.0f);
    ViewAbstract::GetMargin(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::GetTranslate(AceType::RawPtr(FRAME_NODE_REGISTER));
    GestureEventFunc tapEventFunc;
    ViewAbstract::SetJSFrameNodeOnClick(AceType::RawPtr(FRAME_NODE_REGISTER), std::move(tapEventFunc));
    ViewAbstract::ClearJSFrameNodeOnClick(AceType::RawPtr(FRAME_NODE_REGISTER));
    TouchEventFunc touchEventFunc;
    ViewAbstract::SetJSFrameNodeOnTouch(AceType::RawPtr(FRAME_NODE_REGISTER), std::move(touchEventFunc));
    ViewAbstract::ClearJSFrameNodeOnTouch(AceType::RawPtr(FRAME_NODE_REGISTER));
    std::function<void()> buildFunc;
    ViewAbstract::SetJSFrameNodeOnAppear(AceType::RawPtr(FRAME_NODE_REGISTER), std::move(buildFunc));
    ViewAbstract::ClearJSFrameNodeOnAppear(AceType::RawPtr(FRAME_NODE_REGISTER));
    ViewAbstract::SetJSFrameNodeOnDisappear(AceType::RawPtr(FRAME_NODE_REGISTER), std::move(buildFunc));
    ViewAbstract::ClearJSFrameNodeOnDisappear(AceType::RawPtr(FRAME_NODE_REGISTER));
    OnKeyCallbackFunc onKeyCallback = [](KeyEventInfo& info) {};
    ViewAbstract::SetJSFrameNodeOnKeyCallback(AceType::RawPtr(FRAME_NODE_REGISTER), std::move(onKeyCallback));
    ViewAbstract::ClearJSFrameNodeOnKeyCallback(AceType::RawPtr(FRAME_NODE_REGISTER));

    std::function<void(bool, double)> onVisibleChange;
    const std::vector<double> ratios;
    constexpr uint32_t minInterval = 100; // 100ms
    ViewAbstract::SetJSFrameNodeOnVisibleAreaApproximateChange(
        AceType::RawPtr(FRAME_NODE_REGISTER), std::move(onVisibleChange), ratios, minInterval);
    ViewAbstract::ClearJSFrameNodeOnVisibleAreaApproximateChange(AceType::RawPtr(FRAME_NODE_REGISTER));

    /**
     * @tc.expected: Return expected results.
     */
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty<LayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    ViewStackProcessor::GetInstance()->instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest015
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest015, TestSize.Level1)
{
    /**
     * @tc.steps: step1.The FrameNode is null, related function is called.
     */
    viewAbstractModelNG.SetPivot(WIDTH, HEIGHT, WIDTH);
    NG::TranslateOptions pttions;
    BlurOption blurOption;
    ViewAbstract::SetTranslate(std::move(pttions));
    ViewAbstract::SetTranslate(nullptr, std::move(pttions));
    Matrix4 matrix;
    ViewAbstract::SetTransformMatrix(std::move(matrix));
    ViewAbstract::SetTransformMatrix(AceType::RawPtr(FRAME_NODE_REGISTER), std::move(matrix));
    ViewAbstract::SetBackdropBlur(RADIUS, blurOption);
    ViewAbstract::SetBackdropBlur(nullptr, RADIUS, blurOption);
    ViewAbstract::SetFrontBlur(RADIUS, blurOption);
    ViewAbstract::SetFrontBlur(AceType::RawPtr(FRAME_NODE_REGISTER), RADIUS, blurOption);
    ViewAbstract::SetInspectorId(srcimages);
    ViewAbstract::SetInspectorId(AceType::RawPtr(FRAME_NODE_REGISTER), srcimages);

    Vector5F scale(1.0f, 1.0f, 2.0f, 2.0f, 0.0f);
    ViewAbstract::SetRotate(scale);
    ViewAbstract::SetRotate(nullptr, scale);
    ShadowStyle style { 1 };
    Shadow shadow { RATIO, OFFSET, BLUE, style };
    ViewAbstract::SetBackShadow(shadow);
    ViewAbstract::SetBackShadow(nullptr, shadow);

    NG::Gradient gradient;
    ViewAbstract::SetLinearGradient(std::move(gradient));
    ViewAbstract::SetLinearGradient(AceType::RawPtr(FRAME_NODE_REGISTER), std::move(gradient));
    ViewAbstract::SetSweepGradient(std::move(gradient));
    ViewAbstract::SetSweepGradient(AceType::RawPtr(FRAME_NODE_REGISTER), std::move(gradient));
    ViewAbstract::SetRadialGradient(std::move(gradient));
    ViewAbstract::SetRadialGradient(AceType::RawPtr(FRAME_NODE_REGISTER), std::move(gradient));
    ViewAbstract::SetSystemBarEffect(false);
    ViewAbstract::SetSystemBarEffect(nullptr, false);
    ViewAbstract::SetFreeze(false);
    ViewAbstract::SetUseShadowBatching(false);
    ViewAbstract::SetUseShadowBatching(AceType::RawPtr(FRAME_NODE_REGISTER), false);

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_NE(ViewStackProcessor::GetInstance()->GetMainElementNode(), nullptr);
}

/**
 * @tc.name: ViewAbstractTest016
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest016, TestSize.Level1)
{
    /**
     * @tc.steps: step1.push FrameNode is not null, related function is called.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);

    viewAbstractModelNG.SetPivot(WIDTH, HEIGHT, ZERO);
    NG::TranslateOptions pttions;
    ViewAbstract::SetTranslate(std::move(pttions));
    Matrix4 matrix;
    BlurOption blurOption;
    ViewAbstract::SetTransformMatrix(std::move(matrix));
    ViewAbstract::SetBackdropBlur(RADIUS, blurOption);
    ViewAbstract::SetFrontBlur(RADIUS, blurOption);
    ViewAbstract::SetInspectorId(srcimages);
    ViewAbstract::SetDebugLine(srcimages);

    Vector5F scale(1.0f, 1.0f, 2.0f, 2.0f, 0.0f);
    ViewAbstract::SetRotate(scale);
    ShadowStyle style { 1 };
    Shadow shadow { RATIO, OFFSET, BLUE, style };
    ViewAbstract::SetBackShadow(shadow);
    NG::Gradient gradient;
    ViewAbstract::SetLinearGradient(std::move(gradient));
    ViewAbstract::SetSweepGradient(std::move(gradient));
    ViewAbstract::SetRadialGradient(std::move(gradient));
    ViewAbstract::SetSystemBarEffect(false);
    ViewAbstract::SetSystemBarEffect(nullptr, false);
    ViewAbstract::SetFreeze(false);
    ViewAbstract::SetUseShadowBatching(false);
    ImageResizableSlice slice;
    ViewAbstract::SetBackgroundImageResizableSlice(slice);
    ViewAbstract::SetBackgroundImageResizableSlice(nullptr, slice);
    ViewAbstract::SetBackgroundImageResizableSlice(nullptr, slice, true);

    /**
     * @tc.expected: Return expected results.
     */
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty<LayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    ViewStackProcessor::GetInstance()->instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest017
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest017, TestSize.Level1)
{
    /**
     * @tc.steps: step1.The FrameNode is null, related function is called.
     */
    auto visible = static_cast<GridSizeType>(INDEX);
    ViewAbstract::SetGrid(FOUF, FOUF, std::move(visible));
    ViewAbstract::SetGrid(AceType::RawPtr(FRAME_NODE_REGISTER), FOUF, FOUF, std::move(visible));
    TransitionOptions options;
    ViewAbstract::SetTransition(std::move(options));
    RefPtr<BasicShape> basicShape;
    ViewAbstract::SetClipShape(std::move(basicShape));
    ViewAbstract::SetClipShape(nullptr, std::move(basicShape));
    ViewAbstract::SetMask(std::move(basicShape));
    ViewAbstract::SetClipEdge(false);
    ViewAbstract::SetGrayScale(RADIUS);
    ViewAbstract::SetGrayScale(nullptr, RADIUS);
    OHOS::Rosen::VisualEffect* visualEffect;
    ViewAbstract::SetVisualEffect(visualEffect);
    OHOS::Rosen::Filter* backgroundFilter;
    ViewAbstract::SetBackgroundFilter(backgroundFilter);
    OHOS::Rosen::Filter* foregroundFilter;
    ViewAbstract::SetForegroundFilter(foregroundFilter);
    OHOS::Rosen::Filter* compositingFilter;
    ViewAbstract::SetCompositingFilter(compositingFilter);
    ViewAbstract::SetDynamicDim(1.0f);
    ViewAbstract::SetContrast(RADIUS);
    ViewAbstract::SetSaturate(RADIUS);
    ViewAbstract::SetSaturate(nullptr, RADIUS);
    ViewAbstract::SetSepia(RADIUS);
    ViewAbstract::SetSepia(nullptr, RADIUS);
    ViewAbstract::SetInvert(invert);
    ViewAbstract::SetInvert(nullptr, invert);
    ViewAbstract::SetHueRotate(RATIO);
    ViewAbstract::SetHueRotate(nullptr, RATIO);
    ViewAbstract::SetBrightness(RADIUS);
    ViewAbstract::SetColorBlend(BLUE);
    ViewAbstract::SetBorderImageSource(srcimages);
    ViewAbstract::SetBlender(nullptr);

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_NE(ViewStackProcessor::GetInstance()->GetMainElementNode(), nullptr);
}

/**
 * @tc.name: ViewAbstractTest018
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest018, TestSize.Level1)
{
    /**
     * @tc.steps: step1.push FrameNode is not null, related function is called.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);

    auto visible = static_cast<GridSizeType>(INDEX);
    ViewAbstract::SetGrid(FOUF, FOUF, std::move(visible));
    TransitionOptions options;
    ViewAbstract::SetTransition(std::move(options));
    RefPtr<BasicShape> basicShape;
    ViewAbstract::SetClipShape(std::move(basicShape));
    ViewAbstract::SetMask(std::move(basicShape));
    ViewAbstract::SetClipEdge(false);
    ViewAbstract::SetClipEdge(nullptr, false);
    ViewAbstract::SetGrayScale(RADIUS);
    ViewAbstract::SetGrayScale(nullptr, RADIUS);
    OHOS::Rosen::VisualEffect* visualEffect;
    ViewAbstract::SetVisualEffect(visualEffect);
    OHOS::Rosen::Filter* backgroundFilter;
    ViewAbstract::SetBackgroundFilter(backgroundFilter);
    OHOS::Rosen::Filter* foregroundFilter;
    ViewAbstract::SetForegroundFilter(foregroundFilter);
    OHOS::Rosen::Filter* compositingFilter;
    ViewAbstract::SetCompositingFilter(compositingFilter);
    ViewAbstract::SetContrast(RADIUS);
    ViewAbstract::SetSaturate(RADIUS);
    ViewAbstract::SetSepia(RADIUS);
    ViewAbstract::SetInvert(invert);
    ViewAbstract::SetHueRotate(RATIO);
    ViewAbstract::SetBrightness(RADIUS);
    ViewAbstract::SetBrightness(nullptr, RADIUS);
    ViewAbstract::SetColorBlend(BLUE);
    ViewAbstract::SetColorBlend(nullptr, BLUE);
    ViewAbstract::SetBorderImageSource(srcimages);
    ViewAbstract::SetBlender(nullptr);

    /**
     * @tc.expected: Return expected results.
     */
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty<LayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    ViewStackProcessor::GetInstance()->instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest019
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest019, TestSize.Level1)
{
    /**
     * @tc.steps: step1.The FrameNode is null, related function is called.
     */
    RefPtr<BorderImage> borderImage;
    ViewAbstract::SetBorderImage(std::move(borderImage));
    ViewAbstract::SetHasBorderImageSlice(true);
    ViewAbstract::SetHasBorderImageWidth(true);
    ViewAbstract::SetHasBorderImageOutset(true);
    ViewAbstract::SetHasBorderImageRepeat(true);
    ViewAbstract::SetHasBorderImageRepeat(nullptr, true);
    Gradient gradient;
    ViewAbstract::SetBorderImageGradient(std::move(gradient));
    ViewAbstract::SetBorderImageGradient(nullptr, std::move(gradient));
    OverlayOptions overlay;
    ViewAbstract::SetOverlay(std::move(overlay));
    ViewAbstract::SetOverlay(nullptr, std::move(overlay));
    MotionPathOption motionPath;
    ViewAbstract::SetMotionPath(std::move(motionPath));
    ViewAbstract::SetMotionPath(nullptr, std::move(motionPath));
    ViewAbstract::SetSharedTransition("", nullptr);
    ViewAbstract::SetSharedTransition(AceType::RawPtr(FRAME_NODE_REGISTER), "", nullptr);
    ViewAbstract::SetSphericalEffect(RATIO);
    ViewAbstract::SetLightUpEffect(RATIO);
    ViewAbstract::SetUseEffect(false, EffectType::DEFAULT);
    ViewAbstract::SetRenderGroup(false);
    ViewAbstract::SetRenderFit(RenderFit::BOTTOM);
    ViewAbstract::UpdateSafeAreaExpandOpts(safeAreaExpandOpts);
    ViewAbstract::UpdateSafeAreaExpandOpts(AceType::RawPtr(FRAME_NODE_REGISTER), safeAreaExpandOpts);
    ViewAbstract::SetObscured(reasonsVector);
    ViewAbstract::SetObscured(AceType::RawPtr(FRAME_NODE_REGISTER), reasonsVector);

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_NE(ViewStackProcessor::GetInstance()->GetMainElementNode(), nullptr);
}

/**
 * @tc.name: ViewAbstractTest020
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest020, TestSize.Level1)
{
    /**
     * @tc.steps: step1.push FrameNode is not null, related function is called.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);

    RefPtr<BorderImage> borderImage;
    ViewAbstract::SetBorderImage(std::move(borderImage));
    ViewAbstract::SetBorderImage(nullptr, std::move(borderImage));
    ViewAbstract::SetHasBorderImageSlice(true);
    ViewAbstract::SetHasBorderImageWidth(true);
    ViewAbstract::SetHasBorderImageOutset(true);
    ViewAbstract::SetHasBorderImageRepeat(true);
    Gradient gradient;
    ViewAbstract::SetBorderImageGradient(std::move(gradient));
    OverlayOptions overlay;
    ViewAbstract::SetOverlay(std::move(overlay));
    MotionPathOption motionPath;
    ViewAbstract::SetMotionPath(std::move(motionPath));
    std::shared_ptr<SharedTransitionOption> option;
    ViewAbstract::SetSharedTransition(srcimages, std::move(option));
    ViewAbstract::SetSphericalEffect(RATIO);
    ViewAbstract::SetLightUpEffect(RATIO);
    ViewAbstract::SetDraggable(false);
    ViewAbstract::SetDraggable(AceType::RawPtr(FRAME_NODE_REGISTER), false);
    ViewAbstract::SetUseEffect(false, EffectType::DEFAULT);
    ViewAbstract::SetUseEffect(false, EffectType::WINDOW_EFFECT);
    ViewAbstract::SetUseEffect(true, EffectType::DEFAULT);
    ViewAbstract::SetUseEffect(true, EffectType::WINDOW_EFFECT);
    ViewAbstract::SetRenderGroup(false);
    ViewAbstract::SetRenderFit(RenderFit::BOTTOM);
    ViewAbstract::UpdateSafeAreaExpandOpts(safeAreaExpandOpts);
    ViewAbstract::SetObscured(reasonsVector);

    /**
     * @tc.expected: Return expected results.
     */
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty<LayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    ViewStackProcessor::GetInstance()->instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest021
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest021, TestSize.Level1)
{
    /**
     * @tc.steps: step1.The FrameNode is null, related function is called.
     */
    PixStretchEffectOption option;
    option.bottom = BOTTOM;
    option.left = LEFT;
    option.right = RIGHT;
    option.top = TOP;
    ViewAbstract::SetPixelStretchEffect(option);
    ViewAbstract::SetPixelStretchEffect(nullptr, option);
    RefPtr<NG::ChainedTransitionEffect> effect;
    ViewAbstract::SetChainedTransition(std::move(effect));
    RefPtr<ProgressMaskProperty> progress;
    ViewAbstract::SetProgressMask(std::move(progress));

    ViewAbstract::SetForegroundColor(BLUE);
    auto strategy = static_cast<ForegroundColorStrategy>(INDEX);
    ViewAbstract::SetForegroundColorStrategy(std::move(strategy));
    auto hoverEffect = static_cast<HoverEffectType>(INDEX);
    ViewAbstract::SetHoverEffectAuto(hoverEffect);
    ViewAbstract::SetDraggable(true);

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_NE(ViewStackProcessor::GetInstance()->GetMainElementNode(), nullptr);
}

/**
 * @tc.name: ViewAbstractTest022
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest022, TestSize.Level1)
{
    /**
     * @tc.steps: step1.push FrameNode is not null, related function is called.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);

    PixStretchEffectOption option;
    option.bottom = BOTTOM;
    option.left = LEFT;
    option.right = RIGHT;
    option.top = TOP;
    ViewAbstract::SetPixelStretchEffect(option);
    RefPtr<NG::ChainedTransitionEffect> effect;
    ViewAbstract::SetChainedTransition(std::move(effect));
    RefPtr<ProgressMaskProperty> progress;
    ViewAbstract::SetProgressMask(std::move(progress));
    ViewAbstract::SetForegroundColor(BLUE);
    auto strategy = static_cast<ForegroundColorStrategy>(INDEX);
    ViewAbstract::SetForegroundColorStrategy(std::move(strategy));
    ViewAbstract::SetBorderWidth(VALUE);
    ViewAbstract::SetHeight(NG::CalcLength(HEIGHT));
    ViewAbstract::SetWidth(NG::CalcLength(WIDTH));
    auto hoverEffect = static_cast<HoverEffectType>(INDEX);
    ViewAbstract::SetHoverEffectAuto(hoverEffect);
    ViewAbstract::SetDraggable(true);

    /**
     * @tc.expected: Return expected results.
     */
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty<LayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    ViewStackProcessor::GetInstance()->instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest023
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest023, TestSize.Level1)
{
    /**
     * @tc.steps: step1.The FrameNode is null, related function is called.
     */
    std::function<void(const RectF& oldRect, const OffsetF& oldOrigin, const RectF& rect, const OffsetF& origin)>
        onAreaChanged;
    ViewAbstract::SetOnAreaChanged(std::move(onAreaChanged));
    ViewAbstract::SetOnAreaChanged(AceType::RawPtr(FRAME_NODE_REGISTER), std::move(onAreaChanged));

    std::function<void(const RectF& oldRect, const RectF& rect)> onSizeChanged;
    ViewAbstract::SetOnSizeChanged(std::move(onSizeChanged));
    std::function<void(bool, double)> onVisibleChange;
    const std::vector<double> ratios;
    ViewAbstract::SetOnVisibleChange(std::move(onVisibleChange), ratios);

    std::function<void(const RefPtr<OHOS::Ace::DragEvent>&)> onDragEnd;
    ViewAbstract::SetOnDragEnd(std::move(onDragEnd));
    std::set<std::string> allowDrop;
    ViewAbstract::SetAllowDrop(std::move(allowDrop));
    ViewAbstract::SetAllowDrop(AceType::RawPtr(FRAME_NODE_REGISTER), std::move(allowDrop));
    ViewAbstract::CreateAnimatablePropertyFloat(srcimages, RATIO, nullptr);
    ViewAbstract::UpdateAnimatablePropertyFloat(srcimages, RATIO);
    ViewAbstract::SetRestoreId(TEN);
    ViewAbstract::SetRestoreId(AceType::RawPtr(FRAME_NODE_REGISTER), TEN);

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_NE(ViewStackProcessor::GetInstance()->GetMainElementNode(), nullptr);
}

/**
 * @tc.name: ViewAbstractTest024
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest024, TestSize.Level1)
{
    /**
     * @tc.steps: step1.push FrameNode is not null, related function is called.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);

    std::function<void(const RectF& oldRect, const OffsetF& oldOrigin, const RectF& rect, const OffsetF& origin)>
        onAreaChanged;
    ViewAbstract::SetOnAreaChanged(std::move(onAreaChanged));
    std::function<void(bool, double)> onVisibleChange;
    const std::vector<double> ratios;
    ViewAbstract::SetOnVisibleChange(std::move(onVisibleChange), ratios);
    std::function<void(const RefPtr<OHOS::Ace::DragEvent>&)> onDragEnd;
    ViewAbstract::SetOnDragEnd(std::move(onDragEnd));
    std::set<std::string> allowDrop;
    ViewAbstract::SetAllowDrop(std::move(allowDrop));
    ViewAbstract::CreateAnimatablePropertyFloat(srcimages, RATIO, nullptr);
    ViewAbstract::UpdateAnimatablePropertyFloat(srcimages, RATIO);
    ViewAbstract::SetRestoreId(TEN);

    /**
     * @tc.expected: Return expected results.
     */
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty<LayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    ViewStackProcessor::GetInstance()->instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest025
 * @tc.desc: Test the BindPopup of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest025, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create some FrameNode and params.
     */
    const RefPtr<FrameNode> customNode = FrameNode::CreateFrameNode("one", 1, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("two", 2, AceType::MakeRefPtr<Pattern>());
    const RefPtr<FrameNode> targetNode2 = FrameNode::CreateFrameNode("three", 3, AceType::MakeRefPtr<Pattern>());
    auto param = AceType::MakeRefPtr<PopupParam>();
    auto param2 = AceType::MakeRefPtr<PopupParam>();

    /**
     * @tc.steps: step2. get popupInfo and change some params.
     */
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto nodeId = targetNode->GetId();
    PopupInfo info = overlayManager->GetPopupInfo(nodeId);
    info.isCurrentOnShow = true;
    info.popupId = 1;
    auto popupNode1 = FrameNode::CreateFrameNode(
        V2::POPUP_ETS_TAG, info.popupId, AceType::MakeRefPtr<BubblePattern>(targetNode->GetId(), targetNode->GetTag()));
    info.popupNode = popupNode1;
    info.target = targetNode2;
    overlayManager->ShowPopup(targetNode->GetId(), info);

    /**
     * @tc.steps: step3. Call BindPopup many times.
     * @tc.expected: popupNode in overlayManager of targetNode not null
     */
    ViewAbstract::BindPopup(param, targetNode, customNode);
    ViewAbstract::BindPopup(param, targetNode, customNode);
    overlayManager->HidePopup(targetNode->GetId(), info);
    auto popupInfo = overlayManager->GetPopupInfo(targetNode->GetId());
    auto popupNode = popupInfo.popupNode;
    ASSERT_NE(popupNode, nullptr);
    popupNode->GetPattern<BubblePattern>()->transitionStatus_ = TransitionStatus::ENTERING;
    ViewAbstract::BindPopup(param, targetNode, customNode);
    param->SetIsShow(false);
    ViewAbstract::BindPopup(param, targetNode, customNode);
    param->SetShowInSubWindow(true);
    ViewAbstract::BindPopup(param, targetNode, customNode);
    EXPECT_NE(overlayManager->GetPopupInfo(targetNode->GetId()).popupNode, nullptr);

    /**
     * @tc.steps: step4. Call BindPopup with param use custom.
     * @tc.expected: popupNode in overlayManager of targetNode not null
     */
    param2->SetUseCustomComponent(true);
    ViewAbstract::BindPopup(param2, targetNode2, customNode);
    ViewAbstract::BindPopup(param2, targetNode2, customNode);
    param2->SetShowInSubWindow(true);
    ViewAbstract::BindPopup(param2, targetNode2, customNode);
    param2->SetIsShow(false);
    ViewAbstract::BindPopup(param2, targetNode2, customNode);
    EXPECT_NE(overlayManager->GetPopupInfo(targetNode->GetId()).popupNode, nullptr);
}

/**
 * @tc.name: ViewAbstractTest026
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest026, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    /**
     * @tc.steps: step2. call SetKeyboardShortcut with ctrl + x.
     * @tc.expected: add fail
     */
    std::vector<ModifierKey> keys;
    keys.push_back(ModifierKey::CTRL);
    ViewAbstract::SetKeyboardShortcut(VALUE_X, std::move(keys), callback);
    ViewAbstract::SetKeyboardShortcut(AceType::RawPtr(FRAME_NODE_REGISTER), VALUE_X, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
    keys.clear();
    /**
     * @tc.steps: step3. call SetKeyboardShortcut with other wrong type.
     * @tc.expected: add fail
     */
    ViewAbstract::SetKeyboardShortcut(VALUE_EMPTY, std::move(keys), callback);
    ViewAbstract::SetKeyboardShortcut(VALUE_CX, std::move(keys), callback);
    ViewAbstract::SetKeyboardShortcut(VALUE_X, std::move(keys), callback);
    ViewAbstract::SetKeyboardShortcut(AceType::RawPtr(FRAME_NODE_REGISTER), VALUE_EMPTY, std::move(keys), callback);
    ViewAbstract::SetKeyboardShortcut(AceType::RawPtr(FRAME_NODE_REGISTER), VALUE_CX, std::move(keys), callback);
    ViewAbstract::SetKeyboardShortcut(AceType::RawPtr(FRAME_NODE_REGISTER), VALUE_X, std::move(keys), callback);

    /**
     * @tc.steps: step4. and shift in keys and recall SetKeyboardShortcut .
     * @tc.expected: add success
     */
    keys.push_back(ModifierKey::ALT);
    ViewAbstract::SetKeyboardShortcut(VALUE_CX, std::move(keys), callback);
    ViewAbstract::SetKeyboardShortcut(AceType::RawPtr(FRAME_NODE_REGISTER), VALUE_CX, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);

    /**
     * @tc.steps: step5. make other key and recall SetKeyboardShortcut .
     * @tc.expected: add fail
     */
    keys.push_back(ModifierKey::SHIFT);
    ViewAbstract::SetKeyboardShortcut(VALUE_CX, std::move(keys), callback);
    ViewAbstract::SetKeyboardShortcut(AceType::RawPtr(FRAME_NODE_REGISTER), VALUE_CX, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
    keys.push_back(ModifierKey::ALT);
    ViewAbstract::SetKeyboardShortcut(VALUE_CX, std::move(keys), callback);
    ViewAbstract::SetKeyboardShortcut(AceType::RawPtr(FRAME_NODE_REGISTER), VALUE_CX, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
}

/**
 * @tc.name: ViewAbstractTest027
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest027, TestSize.Level1)
{
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    /**
     * @tc.steps: step1. callback ShowMenu with two condition.
     */
    ContainerScope sontainerScope(1);
    /**
     * @tc.steps: step2. callback SetForegroundBlurStyle and ResetFlexShrink.
     */
    BlurStyleOption bgBlurStyle;
    ViewAbstract::SetForegroundBlurStyle(bgBlurStyle);
    ViewAbstract::SetForegroundBlurStyle(AceType::RawPtr(FRAME_NODE_REGISTER), bgBlurStyle);
    ViewAbstract::ResetFlexShrink();
    ViewAbstract::ResetFlexShrink(AceType::RawPtr(FRAME_NODE_REGISTER));
    /**
     * @tc.steps: step3. SetVisualState in ViewStackProcessor and recall the two function.
     * @tc.expected: the blur radius in render context meet expectations.
     */
    ViewStackProcessor::GetInstance()->SetVisualState(VisualState::FOCUSED);
    ViewAbstract::SetForegroundBlurStyle(bgBlurStyle);
    ViewAbstract::SetForegroundBlurStyle(AceType::RawPtr(FRAME_NODE_REGISTER), bgBlurStyle);
    ViewAbstract::ResetFlexShrink();
    ASSERT_NE(FRAME_NODE_ROOT->GetRenderContext(), nullptr);
    EXPECT_FALSE(FRAME_NODE_ROOT->GetRenderContext()->GetFrontBlurRadius().has_value());
}

/**
 * @tc.name: ViewAbstractTest028
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest028, TestSize.Level1)
{
    /**
     * @tc.steps: step1.push FrameNode is not null, callback Pop function.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    ViewAbstract::Pop();

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_FALSE(ViewStackProcessor::GetInstance()->elementsStack_.empty());
    EXPECT_EQ(ViewStackProcessor::GetInstance()->elementsStack_.size(), INDEX);
}

/**
 * @tc.name: ViewAbstractTest029
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest029, TestSize.Level1)
{
    /**
     * @tc.steps: step1.ClearStack.
     */
    auto state = static_cast<VisualState>(INDEX);
    ViewStackProcessor::GetInstance()->SetVisualState(state);
    ViewStackProcessor::GetInstance()->ClearStack();

    /**
     * @tc.steps: step2. related function is called.
     */
    ViewAbstract::SetWidth(NG::CalcLength(WIDTH));
    ViewAbstract::SetHeight(NG::CalcLength(HEIGHT));
    ViewAbstract::SetMinWidth(NG::CalcLength(MIN_WIDTH));
    ViewAbstract::SetMinHeight(NG::CalcLength(MIN_HEIGHT));
    ViewAbstract::SetMaxWidth(NG::CalcLength(MIN_WIDTH));
    ViewAbstract::SetMaxHeight(NG::CalcLength(MIN_HEIGHT));
    ViewAbstract::SetAspectRatio(RATIO);
    ViewAbstract::SetAspectRatio(AceType::RawPtr(FRAME_NODE_REGISTER), RATIO);
    ViewAbstract::SetBackgroundColor(BLUE);
    ViewAbstract::SetBackgroundColor(nullptr, BLUE);
    ViewAbstract::SetBackgroundImage(imageSourceInfo);
    ViewAbstract::SetBackgroundImage(nullptr, imageSourceInfo);
    ViewAbstract::SetBackgroundImageSize(BACKGROUNDSIZE);
    ViewAbstract::SetBackgroundImageSize(nullptr, BACKGROUNDSIZE);
    ViewAbstract::SetBackgroundImageSize(nullptr, BACKGROUNDSIZE, true);
    ViewAbstract::SetBackgroundImagePosition(BACKGROUNDPOSITION);
    ViewAbstract::SetBackgroundImagePosition(nullptr, BACKGROUNDPOSITION);
    ViewAbstract::SetBackgroundImagePosition(nullptr, BACKGROUNDPOSITION, true);
    ViewAbstract::SetPixelRound(0);
    ChainInfo chainInfo;
    chainInfo.direction = LineDirection::HORIZONTAL;
    chainInfo.style = ChainStyle::SPREAD;
    ViewAbstract::SetChainStyle(chainInfo);
    ViewAbstract::SetChainStyle(AceType::RawPtr(FRAME_NODE_REGISTER), chainInfo);
    ViewAbstract::SetBias(biasPair);
    ViewAbstract::SetBias(nullptr, biasPair);
    ViewAbstract::SetOuterBorderRadius(ZERO);
    ViewAbstract::SetOuterBorderRadius(nullptr, ZERO);
    NG::BorderRadiusProperty borderRadius;
    ViewAbstract::SetOuterBorderRadius(borderRadius);
    ViewAbstract::SetOuterBorderRadius(nullptr, borderRadius);
    ViewAbstract::SetOuterBorderColor(BLUE);
    ViewAbstract::SetOuterBorderColor(nullptr, BLUE);
    NG::BorderColorProperty borderColor;
    ViewAbstract::SetOuterBorderColor(borderColor);
    ViewAbstract::SetOuterBorderColor(nullptr, borderColor);
    ViewAbstract::SetOuterBorderWidth(ZERO);
    ViewAbstract::SetOuterBorderWidth(nullptr, ZERO);
    NG::BorderWidthProperty borderWidth;
    ViewAbstract::SetOuterBorderWidth(borderWidth);
    ViewAbstract::SetOuterBorderWidth(nullptr, borderWidth);
    auto borderStyle = static_cast<BorderStyle>(INDEX);
    ViewAbstract::SetOuterBorderStyle(borderStyle);
    ViewAbstract::SetOuterBorderStyle(nullptr, borderStyle);
    NG::BorderStyleProperty borderStyleProperty;
    ViewAbstract::SetOuterBorderStyle(borderStyleProperty);
    ViewAbstract::SetOuterBorderStyle(nullptr, borderStyleProperty);
    ViewAbstract::ResetAspectRatio();
    ViewAbstract::ResetAspectRatio(AceType::RawPtr(FRAME_NODE_REGISTER));

    /**
     * @tc.expected: Return expected results.
     */
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest030
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest030, TestSize.Level1)
{
    /**
     * @tc.steps: step1.ClearStack.
     */
    auto state = static_cast<VisualState>(INDEX);
    ViewStackProcessor::GetInstance()->SetVisualState(state);
    ViewStackProcessor::GetInstance()->ClearStack();

    /**
     * @tc.steps: step2. related function is called.
     */
    MotionPathOption motionPath;
    ViewAbstract::SetMotionPath(std::move(motionPath));
    auto repeat = static_cast<ImageRepeat>(INDEX);
    ViewAbstract::SetBackgroundImageRepeat(repeat);
    GestureJudgeFunc tapEventFunc;
    ViewAbstract::SetOnGestureJudgeBegin(std::move(tapEventFunc));

    BlurStyleOption blurStyleOption;
    blurStyleOption.blurStyle = BlurStyle::NO_MATERIAL;
    blurStyleOption.colorMode = ThemeColorMode::SYSTEM;
    blurStyleOption.adaptiveColor = AdaptiveColor::DEFAULT;
    ViewAbstract::SetBackgroundBlurStyle(blurStyleOption);

    auto direction = static_cast<TextDirection>(INDEX);
    ViewAbstract::SetLayoutDirection(direction);
    std::map<AlignDirection, AlignRule> alignRules;
    ViewAbstract::SetAlignRules(alignRules);
    auto alignSelf = static_cast<FlexAlign>(INDEX);
    ViewAbstract::SetAlignSelf(alignSelf);
    ViewAbstract::SetAlignSelf(AceType::RawPtr(FRAME_NODE_REGISTER), alignSelf);

    /**
     * @tc.expected: Return expected results.
     */
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: OpenPopup
 * @tc.desc: Test OpenPopup of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, OpenPopup, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create some FrameNode and params.
     */
    auto pipelineContext = PipelineContext::GetCurrentContext();
    auto param = AceType::MakeRefPtr<PopupParam>();
    RefPtr<PopupParam> param2 = nullptr;
    auto contentNode =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    RefPtr<FrameNode> contentNode2 = nullptr;
    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });

    /**
     * @tc.steps: step2. Return expected results.
     */
    EXPECT_EQ(ViewAbstract::OpenPopup(param2, contentNode2), ERROR_CODE_INTERNAL_ERROR);
    EXPECT_EQ(ViewAbstract::OpenPopup(param, contentNode2), ERROR_CODE_DIALOG_CONTENT_ERROR);
    int32_t targetId = -1;
    param->SetTargetId(std::to_string(targetId));
    EXPECT_EQ(ViewAbstract::OpenPopup(param, contentNode), ERROR_CODE_TARGET_INFO_NOT_EXIST);
    targetId = 10000;
    param->SetTargetId(std::to_string(targetId));
    EXPECT_EQ(ViewAbstract::OpenPopup(param, contentNode), ERROR_CODE_TARGET_INFO_NOT_EXIST);
    param->SetTargetId(std::to_string(targetNode->GetId()));
    EXPECT_EQ(ViewAbstract::OpenPopup(param, contentNode), ERROR_CODE_TARGET_NOT_ON_COMPONENT_TREE);
    param->SetIsShow(true);
    param->SetUseCustomComponent(true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    targetNode->onMainTree_ = true;
    targetNode->AttachToMainTree(false, AceType::RawPtr(pipelineContext));
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();
    EXPECT_EQ(ViewAbstract::OpenPopup(param, contentNode), ERROR_CODE_NO_ERROR);
    EXPECT_EQ(ViewAbstract::OpenPopup(param, contentNode), ERROR_CODE_DIALOG_CONTENT_ALREADY_EXIST);
}

/**
 * @tc.name: UpdatePopup
 * @tc.desc: Test UpdatePopup of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, UpdatePopup, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create some FrameNode and params.
     */
    auto pipelineContext = PipelineContext::GetCurrentContext();
    auto param = AceType::MakeRefPtr<PopupParam>();
    auto contentNode =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ViewStackProcessor::GetInstance()->Push(targetNode);
    targetNode->onMainTree_ = true;
    targetNode->AttachToMainTree(false, AceType::RawPtr(pipelineContext));
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();
    param->SetIsShow(true);
    param->SetUseCustomComponent(true);
    param->SetShowInSubWindow(false);
    param->SetTargetId(std::to_string(targetNode->GetId()));

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(ViewAbstract::OpenPopup(param, contentNode), ERROR_CODE_NO_ERROR);
    auto context = contentNode->GetContextWithCheck();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->popupMap_[targetNode->GetId()].isCurrentOnShow = true;
    param->SetIsPartialUpdate(true);
    EXPECT_EQ(ViewAbstract::UpdatePopup(param, contentNode), ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name: ClosePopup
 * @tc.desc: Test ClosePopup of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ClosePopup, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create some FrameNode and params.
     */
    auto pipelineContext = PipelineContext::GetCurrentContext();
    auto param = AceType::MakeRefPtr<PopupParam>();
    auto contentNode =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });

    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ViewStackProcessor::GetInstance()->Push(targetNode);
    targetNode->onMainTree_ = true;
    targetNode->AttachToMainTree(false, AceType::RawPtr(pipelineContext));
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();
    param->SetIsShow(true);
    param->SetUseCustomComponent(true);
    param->SetTargetId(std::to_string(targetNode->GetId()));

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(ViewAbstract::OpenPopup(param, contentNode), ERROR_CODE_NO_ERROR);
    auto context = contentNode->GetContextWithCheck();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->popupMap_[targetNode->GetId()].isCurrentOnShow = true;
    EXPECT_EQ(ViewAbstract::ClosePopup(contentNode), ERROR_CODE_NO_ERROR);
    EXPECT_EQ(ViewAbstract::ClosePopup(contentNode), ERROR_CODE_DIALOG_CONTENT_NOT_FOUND);
}

/**
 * @tc.name: OpenMenu001
 * @tc.desc: Test OpenMenu of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, OpenMenu001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create some FrameNode and menuParam.
     */
    auto pipelineContext = PipelineContext::GetCurrentContext();
    MenuParam menuParam;
    menuParam.isShowInSubWindow = false;
    menuParam.previewMode = MenuPreviewMode::IMAGE;
    auto contentNode =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    RefPtr<FrameNode> contentNode2 = nullptr;
    auto contentNode3 =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    int32_t targetId = targetNode->GetId();
    /**
     * @tc.steps: step2. Return expected results.
     */
    EXPECT_EQ(ViewAbstract::OpenMenu(menuParam, contentNode2, targetId), ERROR_CODE_DIALOG_CONTENT_ERROR);
    targetId = -1;
    EXPECT_EQ(ViewAbstract::OpenMenu(menuParam, contentNode, targetId), ERROR_CODE_TARGET_INFO_NOT_EXIST);
    targetId = 10000;
    EXPECT_EQ(ViewAbstract::OpenMenu(menuParam, contentNode, targetId), ERROR_CODE_TARGET_INFO_NOT_EXIST);
    targetId = targetNode->GetId();
    EXPECT_EQ(ViewAbstract::OpenMenu(menuParam, contentNode, targetId), ERROR_CODE_TARGET_NOT_ON_COMPONENT_TREE);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    targetNode->onMainTree_ = true;
    targetNode->AttachToMainTree(false, AceType::RawPtr(pipelineContext));
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();
    targetId = targetNode->GetId();
    auto targetNodePipelineContext = targetNode->GetContextWithCheck();
    ASSERT_NE(targetNodePipelineContext, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    targetNodePipelineContext->SetThemeManager(themeManager);
    targetNodePipelineContext->SetEventManager(AceType::MakeRefPtr<EventManager>());
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));

    EXPECT_EQ(ViewAbstract::OpenMenu(menuParam, contentNode, targetId), ERROR_CODE_NO_ERROR);
    EXPECT_EQ(ViewAbstract::OpenMenu(menuParam, contentNode, targetId), ERROR_CODE_DIALOG_CONTENT_ALREADY_EXIST);
    EXPECT_EQ(ViewAbstract::OpenMenu(menuParam, contentNode3, targetId), ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name: UpdateMenu001
 * @tc.desc: Test UpdateMenu of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, UpdateMenu001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create some FrameNode and menuParam.
     */
    auto pipelineContext = PipelineContext::GetCurrentContext();
    MenuParam menuParam;
    menuParam.isShowInSubWindow = false;
    auto contentNode =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    RefPtr<FrameNode> contentNode2 = nullptr;
    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ViewStackProcessor::GetInstance()->Push(targetNode);
    targetNode->onMainTree_ = true;
    targetNode->AttachToMainTree(false, AceType::RawPtr(pipelineContext));
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();
    auto targetId = targetNode->GetId();
    auto targetNodePipelineContext = targetNode->GetContextWithCheck();
    ASSERT_NE(targetNodePipelineContext, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    targetNodePipelineContext->SetThemeManager(themeManager);
    targetNodePipelineContext->SetEventManager(AceType::MakeRefPtr<EventManager>());
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(ViewAbstract::OpenMenu(menuParam, contentNode, targetId), ERROR_CODE_NO_ERROR);
    auto overlayManager = ViewAbstract::GetCurOverlayManager(contentNode);
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->menuMap_[targetId];
    EXPECT_EQ(ViewAbstract::UpdateMenu(menuParam, contentNode), ERROR_CODE_NO_ERROR);
    EXPECT_EQ(ViewAbstract::UpdateMenu(menuParam, contentNode2), ERROR_CODE_DIALOG_CONTENT_ERROR);
    overlayManager->menuMap_.clear();
    EXPECT_EQ(ViewAbstract::UpdateMenu(menuParam, contentNode), ERROR_CODE_DIALOG_CONTENT_NOT_FOUND);
}

/**
 * @tc.name: UpdateMenu002
 * @tc.desc: Test UpdateMenu of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, UpdateMenu002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create some FrameNode and menuParam.
     */
    auto pipelineContext = PipelineContext::GetCurrentContext();
    MenuParam menuParam;
    menuParam.isShowInSubWindow = false;
    auto contentNode =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    RefPtr<FrameNode> contentNode2 = nullptr;
    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ViewStackProcessor::GetInstance()->Push(targetNode);
    targetNode->onMainTree_ = true;
    targetNode->AttachToMainTree(false, AceType::RawPtr(pipelineContext));
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();
    auto targetId = targetNode->GetId();
    auto targetNodePipelineContext = targetNode->GetContextWithCheck();
    ASSERT_NE(targetNodePipelineContext, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    targetNodePipelineContext->SetThemeManager(themeManager);
    targetNodePipelineContext->SetEventManager(AceType::MakeRefPtr<EventManager>());
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    selectTheme->expandDisplay_ = true;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(selectTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(selectTheme));

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(ViewAbstract::OpenMenu(menuParam, contentNode, targetId), ERROR_CODE_NO_ERROR);
    auto overlayManager = ViewAbstract::GetCurOverlayManager(contentNode);
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->menuMap_[targetId];
    auto contentNodePipelineContext = contentNode->GetContextWithCheck();
    contentNodePipelineContext->overlayManager_ = nullptr;
    EXPECT_EQ(ViewAbstract::UpdateMenu(menuParam, contentNode), ERROR_CODE_INTERNAL_ERROR);
    contentNodePipelineContext->overlayManager_ = overlayManager;
}

/**
 * @tc.name: UpdateMenu003
 * @tc.desc: Test UpdateMenu of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, UpdateMenu003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create some FrameNode and menuParam.
     */
    auto pipelineContext = PipelineContext::GetCurrentContext();
    MenuParam menuParam;
    menuParam.isShowInSubWindow = false;
    auto contentNode =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ViewStackProcessor::GetInstance()->Push(targetNode);
    targetNode->onMainTree_ = true;
    targetNode->AttachToMainTree(false, AceType::RawPtr(pipelineContext));
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();
    auto targetId = targetNode->GetId();
    auto targetNodePipelineContext = targetNode->GetContextWithCheck();
    ASSERT_NE(targetNodePipelineContext, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    targetNodePipelineContext->SetThemeManager(themeManager);
    targetNodePipelineContext->SetEventManager(AceType::MakeRefPtr<EventManager>());
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(ViewAbstract::OpenMenu(menuParam, contentNode, targetId), ERROR_CODE_NO_ERROR);
    auto overlayManager = ViewAbstract::GetCurOverlayManager(contentNode);
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->menuMap_[targetId];
    auto menuWrapperNode = overlayManager->GetMenuNodeWithExistContent(contentNode);
    ASSERT_NE(menuWrapperNode, nullptr);
    auto wrapperPattern = AceType::DynamicCast<MenuWrapperPattern>(menuWrapperNode->GetPattern());
    ASSERT_NE(wrapperPattern, nullptr);
    auto menu = wrapperPattern->GetMenu();
    ASSERT_NE(menu, nullptr);
    auto menuPattern = AceType::DynamicCast<MenuPattern>(menu->GetPattern());
    ASSERT_NE(menuPattern, nullptr);
    auto menuItem = FrameNode::GetOrCreateFrameNode(V2::MENU_ITEM_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<MenuItemPattern>(); });
    menuItem->MountToParent(menu);

    auto subMenu = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, V2::MENU_TAG, MenuType::SUB_MENU));
    subMenu->MountToParent(menuWrapperNode);
    menuPattern->SetShowedSubMenu(subMenu);
    auto menuItemPattern = menuItem->GetPattern<MenuItemPattern>();
    menuItemPattern->expandingMode_ = SubMenuExpandingMode::EMBEDDED;
    menuPattern->AddEmbeddedMenuItem(menuItem);

    EXPECT_EQ(ViewAbstract::UpdateMenu(menuParam, contentNode), ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name: UpdateMenu004
 * @tc.desc: Test UpdateMenu of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, UpdateMenu004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create some FrameNode and menuParam.
     */
    auto pipelineContext = PipelineContext::GetCurrentContext();
    MenuParam menuParam;
    menuParam.isShowInSubWindow = false;
    auto contentNode =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    RefPtr<FrameNode> contentNode2 = nullptr;
    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ViewStackProcessor::GetInstance()->Push(targetNode);
    targetNode->onMainTree_ = true;
    targetNode->AttachToMainTree(false, AceType::RawPtr(pipelineContext));
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();
    auto targetId = targetNode->GetId();
    auto targetNodePipelineContext = targetNode->GetContextWithCheck();
    ASSERT_NE(targetNodePipelineContext, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    targetNodePipelineContext->SetThemeManager(themeManager);
    targetNodePipelineContext->SetEventManager(AceType::MakeRefPtr<EventManager>());
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(ViewAbstract::OpenMenu(menuParam, contentNode, targetId), ERROR_CODE_NO_ERROR);
    auto overlayManager = ViewAbstract::GetCurOverlayManager(contentNode);
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->menuMap_[targetId];
    auto menuWrapperNode = overlayManager->GetMenuNodeWithExistContent(contentNode);
    ASSERT_NE(menuWrapperNode, nullptr);
    auto wrapperPattern = AceType::DynamicCast<MenuWrapperPattern>(menuWrapperNode->GetPattern());
    ASSERT_NE(wrapperPattern, nullptr);
    auto menu = wrapperPattern->GetMenu();
    ASSERT_NE(menu, nullptr);
    auto menuPattern = AceType::DynamicCast<MenuPattern>(menu->GetPattern());
    ASSERT_NE(menuPattern, nullptr);
    auto menuItem = FrameNode::GetOrCreateFrameNode(V2::MENU_ITEM_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<MenuItemPattern>(); });
    menuItem->MountToParent(menu);
    auto subMenu = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, V2::MENU_ETS_TAG, MenuType::SUB_MENU));
    subMenu->MountToParent(menuWrapperNode);
    menuPattern->SetShowedSubMenu(subMenu);
    auto menuItemPattern = menuItem->GetPattern<MenuItemPattern>();
    menuItemPattern->expandingMode_ = SubMenuExpandingMode::STACK;
    EXPECT_EQ(ViewAbstract::UpdateMenu(menuParam, contentNode), ERROR_CODE_NO_ERROR);

    menuParam.isAnchorPosition = true;
    menuParam.anchorPosition = {10.0, 10.0};
    EXPECT_EQ(ViewAbstract::UpdateMenu(menuParam, contentNode), ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name: CloseMenu001
 * @tc.desc: Test CloseMenu of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, CloseMenu001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create some FrameNode and menuParam.
     */
    auto pipelineContext = PipelineContext::GetCurrentContext();
    MenuParam menuParam;
    menuParam.isShowInSubWindow = false;
    auto contentNode =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    RefPtr<FrameNode> contentNode2 = nullptr;

    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ViewStackProcessor::GetInstance()->Push(targetNode);
    targetNode->onMainTree_ = true;
    targetNode->AttachToMainTree(false, AceType::RawPtr(pipelineContext));
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();
    auto targetId = targetNode->GetId();
    auto targetNodePipelineContext = targetNode->GetContextWithCheck();
    ASSERT_NE(targetNodePipelineContext, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    targetNodePipelineContext->SetThemeManager(themeManager);
    targetNodePipelineContext->SetEventManager(AceType::MakeRefPtr<EventManager>());
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(ViewAbstract::OpenMenu(menuParam, contentNode, targetId), ERROR_CODE_NO_ERROR);
    auto overlayManager = ViewAbstract::GetCurOverlayManager(contentNode);
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->menuMap_[targetId];
    EXPECT_EQ(ViewAbstract::CloseMenu(contentNode), ERROR_CODE_NO_ERROR);
    EXPECT_EQ(ViewAbstract::CloseMenu(contentNode2), ERROR_CODE_DIALOG_CONTENT_ERROR);
    overlayManager->menuMap_.clear();
    EXPECT_EQ(ViewAbstract::CloseMenu(contentNode), ERROR_CODE_DIALOG_CONTENT_NOT_FOUND);
}

/**
 * @tc.name: CloseMenu002
 * @tc.desc: Test CloseMenu of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, CloseMenu002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create some FrameNode and menuParam.
     */
    auto pipelineContext = PipelineContext::GetCurrentContext();
    MenuParam menuParam;
    menuParam.isShowInSubWindow = false;
    auto contentNode =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    RefPtr<FrameNode> contentNode2 = nullptr;

    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ViewStackProcessor::GetInstance()->Push(targetNode);
    targetNode->onMainTree_ = true;
    targetNode->AttachToMainTree(false, AceType::RawPtr(pipelineContext));
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();
    auto targetId = targetNode->GetId();
    auto targetNodePipelineContext = targetNode->GetContextWithCheck();
    ASSERT_NE(targetNodePipelineContext, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    targetNodePipelineContext->SetThemeManager(themeManager);
    targetNodePipelineContext->SetEventManager(AceType::MakeRefPtr<EventManager>());
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(ViewAbstract::OpenMenu(menuParam, contentNode, targetId), ERROR_CODE_NO_ERROR);
    auto overlayManager = ViewAbstract::GetCurOverlayManager(contentNode);
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->menuMap_[targetId];
    auto contentNodePipelineContext = contentNode->GetContextWithCheck();
    contentNodePipelineContext->overlayManager_ = nullptr;
    EXPECT_EQ(ViewAbstract::CloseMenu(contentNode), ERROR_CODE_INTERNAL_ERROR);
    contentNodePipelineContext->overlayManager_ = overlayManager;
}

/**
 * @tc.name: FreezeUINodeById
 * @tc.desc: Test FreezeUINodeById of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTestNg0037, TestSize.Level1)
{
    /**
     * @tc.steps:  Create some FrameNode.
     */
    const std::string& id = "test_id";
    auto targetNode =
        FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() {
                return AceType::MakeRefPtr<ButtonPattern>();
            }
        );
     /**
     * @tc.steps:  connect the FrameNode and id.
     */
    targetNode->UpdateInspectorId(id);

    /**
     * @tc.expected: call the function to freeze the node.
     */
    bool isFreeze = true;
    ViewAbstract::FreezeUINodeById(id, isFreeze);

    /**
     * @tc.expected: verify the pipeline's property is set.
     */
    auto pipeline = targetNode->GetContext();
    bool isOpenInvisibleFreeze = pipeline->IsOpenInvisibleFreeze();

    EXPECT_EQ(isOpenInvisibleFreeze, true);
    /**
     * @tc.expected: verify the node's freeze state.
     */
    bool res = targetNode->IsFreeze();
    EXPECT_EQ(res, isFreeze);
}

/**
 * @tc.name: FreezeUINodeById
 * @tc.desc: Test FreezeUINodeById of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTestNg0038, TestSize.Level1)
{
    /**
     * @tc.steps:  Create some FrameNode.
     */
    const std::string& id = "test_id";
    auto targetNode =
        FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() {
                return AceType::MakeRefPtr<ButtonPattern>();
            }
        );
     /**
     * @tc.steps:  connect the FrameNode and id.
     */
    targetNode->UpdateInspectorId(id);
    /**
     * @tc.steps:  set the FrameNode's  pipeline to null.
     */
    targetNode->context_ = nullptr;

    /**
     * @tc.expected: call the function to unfreeze the node.
     */
    bool isFreeze = false;
    ViewAbstract::FreezeUINodeById(id, isFreeze);

    /**
     * @tc.expected: verify the pipeline's property is set.
     */
    auto pipeline = targetNode->GetContext();
    bool isOpenInvisibleFreeze = pipeline->IsOpenInvisibleFreeze();
    EXPECT_EQ(isOpenInvisibleFreeze, true);

    /**
     * @tc.expected: verify the node's freeze state.
     */
    bool res = targetNode->IsFreeze();
    EXPECT_EQ(res, isFreeze);
}

/**
 * @tc.name: FreezeUINodeById
 * @tc.desc: Test FreezeUINodeById of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTestNg0039, TestSize.Level1)
{
     /**
     * @tc.expected: use a non_existing node id.
     */
    const std::string& non_existing_id = "non_existing_id";
    /**
     * @tc.expected: call the function with the non_existing_id.
     */
    bool isFreeze = true;
    ViewAbstract::FreezeUINodeById(non_existing_id, isFreeze);

    auto node = ElementRegister::GetInstance()->GetAttachedFrameNodeById(non_existing_id, true);
    EXPECT_EQ(node, nullptr);
}

/**
 * @tc.name: FreezeUINodeByUniqueId
 * @tc.desc: Test FreezeUINodeByUniqueId of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTestNg0040, TestSize.Level1)
{
    /**
     * @tc.steps:  Create some FrameNode.
     */
    const int32_t& uniqueId = 1111;
    auto targetNode =
        FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
            uniqueId, []() {
                return AceType::MakeRefPtr<ButtonPattern>();
            }
        );

    /**
     * @tc.expected: call the function to freeze the node.
     */
    bool isFreeze = true;
    ViewAbstract::FreezeUINodeByUniqueId(uniqueId, isFreeze);

    /**
     * @tc.expected: verify the pipeline's property is set.
     */
    auto pipeline = targetNode->GetContext();
    bool isOpenInvisibleFreeze = pipeline->IsOpenInvisibleFreeze();

    EXPECT_EQ(isOpenInvisibleFreeze, true);
    /**
     * @tc.expected: verify the node's freeze state.
     */
    bool res = targetNode->IsFreeze();
    EXPECT_EQ(res, isFreeze);
}

/**
 * @tc.name: FreezeUINodeByUniqueId
 * @tc.desc: Test FreezeUINodeByUniqueId of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTestNg0041, TestSize.Level1)
{
    /**
     * @tc.steps:  Create some FrameNode.
     */
    const int32_t& uniqueId = 222;
    auto targetNode =
        FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
            uniqueId, []() {
                return AceType::MakeRefPtr<ButtonPattern>();
            }
        );

    /**
     * @tc.steps:  set the FrameNode's  pipeline to null.
     */
    targetNode->context_ = nullptr;

    /**
     * @tc.expected: call the function to freeze the node.
     */
    bool isFreeze = false;
    ViewAbstract::FreezeUINodeByUniqueId(uniqueId, isFreeze);

    /**
     * @tc.expected: verify the pipeline's property is set.
     */
    auto pipeline = targetNode->GetContext();
    bool isOpenInvisibleFreeze = pipeline->IsOpenInvisibleFreeze();

    EXPECT_EQ(isOpenInvisibleFreeze, true);
    /**
     * @tc.expected: verify the node's freeze state.
     */
    bool res = targetNode->IsFreeze();
    EXPECT_EQ(res, isFreeze);
}

/**
 * @tc.name: FreezeUINodeByUniqueId
 * @tc.desc: Test FreezeUINodeByUniqueId of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTestNg0042, TestSize.Level1)
{
     /**
     * @tc.expected: use a non_existing node uniqueId.
     */
    const int32_t& non_existing_unique_id = 333;
    /**
     * @tc.expected: call the function with the non_existing_unique_id.
     */
    bool isFreeze = true;
    ViewAbstract::FreezeUINodeByUniqueId(non_existing_unique_id, isFreeze);

    auto node = ElementRegister::GetInstance()->GetNodeById(non_existing_unique_id);
    EXPECT_EQ(node, nullptr);
}

/**
 * @tc.name: SetPositionLocalizedEdges
 * @tc.desc: Test SetPositionLocalizedEdges of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTestNg0043, TestSize.Level1)
{
    auto targetNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
     /**
     * @tc.expected: call the function to Update the layout property.
     */
    bool needLocalized = true;
    ViewAbstract::SetPositionLocalizedEdges(needLocalized);

    auto layoutProperty = targetNode->GetLayoutProperty();

     /**
     * @tc.expected: verify layout property is updated.
     */
    auto positionLocalizedEdges = layoutProperty->IsPositionLocalizedEdges();
    EXPECT_EQ(positionLocalizedEdges, needLocalized);
}

/**
 * @tc.name: SetPositionLocalizedEdges
 * @tc.desc: Test SetPositionLocalizedEdges of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTestNg0044, TestSize.Level1)
{
    auto targetNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
     /**
     * @tc.expected: call the function to Update the layout property.
     */
    bool needLocalized = false;
    ViewAbstract::SetPositionLocalizedEdges(needLocalized);

    auto layoutProperty = targetNode->GetLayoutProperty();

     /**
     * @tc.expected: verify layout property is updated.
     */
    auto positionLocalizedEdges = layoutProperty->IsPositionLocalizedEdges();
    EXPECT_EQ(positionLocalizedEdges, needLocalized);
}

/**
 * @tc.name: CreateWithForegroundColorResourceObj
 * @tc.desc: Test CreateWithForegroundColorResourceObj of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTestNg0045, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<Pattern>();
    CHECK_NULL_VOID(pattern);
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    auto&& updateFunc = [weak = AceType::WeakClaim(frameNode)](const RefPtr<ResourceObject>& resObj) {};
    updateFunc(resObj);
    pattern->AddResObj("foregroundColor", resObj, std::move(updateFunc));
    std::string foregroundColor = pattern->GetResCacheMapByKey("foregroundColor");
    EXPECT_EQ(foregroundColor, "");
}

/**
 * @tc.name: SetBackgroundColor
 * @tc.desc: Test SetBackgroundColor of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTestNg0046, TestSize.Level1)
{
    Color p3Red;
    p3Red.SetValue(0xffff0000);
    p3Red.SetColorSpace(ColorSpace::DISPLAY_P3);
    ViewAbstract::SetBackgroundColor(AceType::RawPtr(FRAME_NODE_REGISTER), p3Red);
    Color result = ViewAbstract::GetBackgroundColor(AceType::RawPtr(FRAME_NODE_REGISTER));
    EXPECT_EQ(result.GetColorSpace(), p3Red.GetColorSpace());
}

/**
 * @tc.name: SetSweepGradient
 * @tc.desc: Test SetSweepGradient of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTestNg0047, TestSize.Level1)
{
    Color p3Red;
    p3Red.SetValue(0xffff0000);
    p3Red.SetColorSpace(ColorSpace::DISPLAY_P3);
    Color p3Green;
    p3Green.SetValue(0xff00ff00);
    p3Green.SetColorSpace(ColorSpace::DISPLAY_P3);
    Color p3Blue;
    p3Blue.SetValue(0xff0000ff);
    p3Blue.SetColorSpace(ColorSpace::DISPLAY_P3);
    GradientColor gradientColor;
    Gradient gradient;
    gradientColor.SetColor(p3Red);
    gradient.AddColor(gradientColor);
    gradientColor.SetColor(p3Green);
    gradient.AddColor(gradientColor);
    gradientColor.SetColor(p3Blue);
    gradient.AddColor(gradientColor);
    ViewAbstract::SetSweepGradient(AceType::RawPtr(FRAME_NODE_REGISTER), gradient);
    Gradient result = ViewAbstract::GetSweepGradient(AceType::RawPtr(FRAME_NODE_REGISTER));
    EXPECT_EQ(result.GetColors().front().GetColor().GetColorSpace(), p3Red.GetColorSpace());
    EXPECT_EQ(result.GetColors().back().GetColor().GetColorSpace(), p3Blue.GetColorSpace());
}

/**
 * @tc.name: SetLinearGradient
 * @tc.desc: Test SetLinearGradient of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTestNg0048, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);

    g_isConfigChangePerform = true;
    NG::Gradient gradient;
    ViewAbstract::SetLinearGradient(gradient);
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    g_isConfigChangePerform = false;
    std::string gradientStr = pattern->GetResCacheMapByKey("LinearGradient.gradient");
    EXPECT_EQ(gradientStr, "");
}

/**
 * @tc.name: CreateWithForegroundColorResourceObj
 * @tc.desc: Test CreateWithForegroundColorResourceObj of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTestNg0049, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    std::string foregroundColor = pattern->GetResCacheMapByKey("foregroundColor");
    EXPECT_EQ(foregroundColor, "");
    std::string bundleName = "com.example.test";
    std::string moduleName = "entry";
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(bundleName, moduleName, 0);
    ViewAbstract::CreateWithForegroundColorResourceObj(resObj);
    Color result;
    ResourceParseUtils::ParseResColor(resObj, result);
    foregroundColor = pattern->GetResCacheMapByKey("foregroundColor");
    EXPECT_EQ(foregroundColor, result.ColorToString());
}

/**
 * @tc.name: CreateWithOuterBorderColorResourceObj
 * @tc.desc: Test CreateWithOuterBorderColorResourceObj of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTestNg0050, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    std::string colorStr = pattern->GetResCacheMapByKey("outerBorderColorRes");
    EXPECT_EQ(colorStr, "");
    std::string bundleName = "com.example.test";
    std::string moduleName = "entry";
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(bundleName, moduleName, 0);
    ViewAbstract::CreateWithOuterBorderColorResourceObj(resObj);
    Color result;
    ResourceParseUtils::ParseResColor(resObj, result);
    colorStr = pattern->GetResCacheMapByKey("outerBorderColorRes");
    EXPECT_EQ(colorStr, result.ColorToString());
}

/**
 * @tc.name: CreateWithOuterBorderRadiusResourceObj
 * @tc.desc: Test CreateWithOuterBorderRadiusResourceObj of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTestNg0051, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    std::string radiusStr = pattern->GetResCacheMapByKey("outerBorderRadiusRes");
    EXPECT_EQ(radiusStr, "");
    std::string bundleName = "com.example.test";
    std::string moduleName = "entry";
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(bundleName, moduleName, 0);
    ViewAbstract::CreateWithOuterBorderRadiusResourceObj(resObj);
    CalcDimension result;
    ResourceParseUtils::ParseResDimensionVp(resObj, result);
    radiusStr = pattern->GetResCacheMapByKey("outerBorderRadiusRes");
    EXPECT_EQ(radiusStr, result.ToString());
}

/**
 * @tc.name: CreateWithLightColorResourceObj
 * @tc.desc: Test CreateWithLightColorResourceObj of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTestNg0052, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    std::string colorStr = pattern->GetResCacheMapByKey("LightColorRes");
    EXPECT_EQ(colorStr, "");
    std::string bundleName = "com.example.test";
    std::string moduleName = "entry";
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(bundleName, moduleName, 0);
    ViewAbstract::CreateWithLightColorResourceObj(resObj);
    Color result;
    ResourceParseUtils::ParseResColor(resObj, result);
    colorStr = pattern->GetResCacheMapByKey("LightColorRes");
    EXPECT_EQ(colorStr, result.ColorToString());
}

/**
 * @tc.name: CreateWithOuterBorderWidthResourceObj
 * @tc.desc: Test CreateWithOuterBorderWidthResourceObj of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTestNg0053, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    std::string widthStr = pattern->GetResCacheMapByKey("outerBorderWidthRes");
    EXPECT_EQ(widthStr, "");
    std::string bundleName = "com.example.test";
    std::string moduleName = "entry";
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(bundleName, moduleName, 0);
    ViewAbstract::CreateWithOuterBorderWidthResourceObj(resObj);
    CalcDimension result;
    ResourceParseUtils::ParseResDimensionVp(resObj, result);
    widthStr = pattern->GetResCacheMapByKey("outerBorderWidthRes");
    EXPECT_EQ(widthStr, result.ToString());
}

/**
 * @tc.name: CreateWithColorBlendResourceObj
 * @tc.desc: Test CreateWithColorBlendResourceObj of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTestNg0054, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    std::string colorStr = pattern->GetResCacheMapByKey("viewAbstract.colorBlend");
    EXPECT_EQ(colorStr, "");
    std::string bundleName = "com.example.test";
    std::string moduleName = "entry";
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(bundleName, moduleName, 0);
    ViewAbstract::CreateWithColorBlendResourceObj(resObj);
    Color result;
    ResourceParseUtils::ParseResColor(resObj, result);
    colorStr = pattern->GetResCacheMapByKey("viewAbstract.colorBlend");
    EXPECT_EQ(colorStr, result.ToString());
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
}

/**
 * @tc.name: CreateWithOpacityResourceObj
 * @tc.desc: Test CreateWithOpacityResourceObj of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTestNg0055, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    std::string opacityStr = pattern->GetResCacheMapByKey("viewAbstract.opacity");
    EXPECT_EQ(opacityStr, "");
    std::string bundleName = "app.float.test";
    std::string moduleName = "entry";
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(bundleName, moduleName, 0);

    g_isConfigChangePerform = true;
    ViewAbstract::CreateWithOpacityResourceObj(resObj);
    double result;
    ResourceParseUtils::ParseResDouble(resObj, result);
    opacityStr = pattern->GetResCacheMapByKey("viewAbstract.opacity");
    EXPECT_EQ(opacityStr, std::to_string(result));
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SetSweepGradient
 * @tc.desc: Test SetSweepGradient of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTestNg0056, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);

    g_isConfigChangePerform = true;
    NG::Gradient gradient;
    gradient.CreateGradientWithType(NG::GradientType::SWEEP);
    ViewAbstract::SetSweepGradient(gradient);
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    g_isConfigChangePerform = false;
    std::string gradientStr = pattern->GetResCacheMapByKey("SweepGradient.gradient");
    EXPECT_EQ(gradientStr, "");
}

/**
 * @tc.name: SetRadialGradient
 * @tc.desc: Test SetRadialGradient of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTestNg0057, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);

    g_isConfigChangePerform = true;
    NG::Gradient gradient;
    gradient.CreateGradientWithType(NG::GradientType::RADIAL);
    ViewAbstract::SetRadialGradient(gradient);
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    g_isConfigChangePerform = false;
    std::string gradientStr = pattern->GetResCacheMapByKey("RadialGradient.gradient");
    EXPECT_EQ(gradientStr, "");
}

/**
 * @tc.name: SetClipShape
 * @tc.desc: Test SetClipShape of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTestNg0058, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    g_isConfigChangePerform = true;
    ViewAbstract::SetClipEdge(frameNode, true);
    auto basicShape = AceType::MakeRefPtr<BasicShape>(BasicShapeType::CIRCLE);
    ViewAbstract::SetClipShape(basicShape);
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
HWTEST_F(ViewAbstractTestNg, ViewAbstractTestNg0059, TestSize.Level1)
{
    BlurStyleOption blurStyleOption;
    blurStyleOption.blurStyle = BlurStyle::NO_MATERIAL;
    blurStyleOption.colorMode = ThemeColorMode::SYSTEM;
    blurStyleOption.adaptiveColor = AdaptiveColor::DEFAULT;
    blurStyleOption.policy = BlurStyleActivePolicy::FOLLOWS_WINDOW_ACTIVE_STATE;
    g_isConfigChangePerform = true;
    ViewAbstract::SetBackgroundBlurStyle(blurStyleOption);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    g_isConfigChangePerform = false;
    
    std::string blurStyleStr = pattern->GetResCacheMapByKey("backgroundBlurStyle.backgroundBlurStyleOptions");
    EXPECT_EQ(blurStyleStr, "");
}

/**
 * @tc.name: SetBackgroundEffect
 * @tc.desc: Test SetBackgroundEffect of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTestNg0060, TestSize.Level1)
{
    EffectOption option;
    Color color = Color::TRANSPARENT;
    option.color = color;
    option.policy = BlurStyleActivePolicy::FOLLOWS_WINDOW_ACTIVE_STATE;
    g_isConfigChangePerform = true;
    ViewAbstract::SetBackgroundEffect(option);
    
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    g_isConfigChangePerform = false;
    std::string effectStr = pattern->GetResCacheMapByKey("backgroundEffect");
    EXPECT_EQ(effectStr, "");
}

/**
 * @tc.name: SetPixelStretchEffect
 * @tc.desc: Test SetPixelStretchEffect of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTestNg0061, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    g_isConfigChangePerform = true;
    PixStretchEffectOption option;
    option.ResetValue();
    ViewAbstract::SetPixelStretchEffect(option);
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    g_isConfigChangePerform = false;
    std::string effectStr = pattern->GetResCacheMapByKey("pixelStretchEffect");
    EXPECT_EQ(effectStr, "");
}

/**
 * @tc.name: SetOuterBorderRadius
 * @tc.desc: Test SetOuterBorderRadius of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTestNg0062, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    g_isConfigChangePerform = true;
    NG::BorderRadiusProperty borderRadius;
    borderRadius.multiValued = true;
    ViewAbstract::SetOuterBorderRadius(borderRadius);
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    g_isConfigChangePerform = false;
    std::string borderRadiusStr = pattern->GetResCacheMapByKey("outerBorderRadius");
    EXPECT_EQ(borderRadiusStr, "");
}

/**
 * @tc.name: SetOuterBorderColor
 * @tc.desc: Test SetOuterBorderColor of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTestNg0063, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    g_isConfigChangePerform = true;
    BorderColorProperty borderColor;
    ViewAbstract::SetOuterBorderColor(borderColor);
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    g_isConfigChangePerform = false;
    std::string borderColorStr = pattern->GetResCacheMapByKey("outerBorderColor");
    EXPECT_EQ(borderColorStr, "");
}

/**
 * @tc.name: SetOuterBorderWidth
 * @tc.desc: Test SetOuterBorderWidth of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTestNg0064, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    g_isConfigChangePerform = true;
    BorderWidthProperty borderWidth;
    ViewAbstract::SetOuterBorderWidth(borderWidth);
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    g_isConfigChangePerform = false;
    std::string borderWidthStr = pattern->GetResCacheMapByKey("outerBorderWidth");
    EXPECT_EQ(borderWidthStr, "");
}

/**
 * @tc.name: SetProgressMask
 * @tc.desc: Test SetProgressMask of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTestNg0065, TestSize.Level1)
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
    ViewAbstract::SetProgressMask(progressMaskProperty);

    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    g_isConfigChangePerform = false;
    std::string maskShape = pattern->GetResCacheMapByKey("ProgressMask");
    EXPECT_EQ(maskShape, "");
}

/**
 * @tc.name: SetLightPosition
 * @tc.desc: Test SetLightPosition of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTestNg0066, TestSize.Level1)
{
    NG::TranslateOptions option;
    CalcDimension dimPositionX(30, DimensionUnit::VP);
    CalcDimension dimPositionY(20, DimensionUnit::VP);
    CalcDimension dimPositionZ(10, DimensionUnit::VP);
    option.x = dimPositionX;
    option.y = dimPositionY;
    option.z = dimPositionZ;
    g_isConfigChangePerform = true;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<Pattern>();
    CHECK_NULL_VOID(pattern);

    ViewStackProcessor::GetInstance()->visualState_ = std::nullopt;
    ViewAbstract::SetLightPosition(option);
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    EXPECT_TRUE(result);

    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    std::string lightSource = pattern->GetResCacheMapByKey("pointLight.LightSource");
    EXPECT_EQ(lightSource, "");

    auto state = static_cast<VisualState>(INDEX);
    ViewStackProcessor::GetInstance()->SetVisualState(state);
    ViewStackProcessor::GetInstance()->ClearStack();
    ViewAbstract::SetLightPosition(option);
    g_isConfigChangePerform = false;
    result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: SetBackShadow
 * @tc.desc: Test SetBackShadow of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTestNg0067, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    g_isConfigChangePerform = true;
    Shadow shadow;
    ViewAbstract::SetBackShadow(shadow);
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    g_isConfigChangePerform = false;
    std::string shadowStr = pattern->GetResCacheMapByKey("shadow");
    EXPECT_EQ(shadowStr, "");
}

/**
 * @tc.name: SetMask
 * @tc.desc: Test SetMask of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTestNg0068, TestSize.Level1)
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
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest069, TestSize.Level1)
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
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest070, TestSize.Level1)
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
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest071, TestSize.Level1)
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
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest072, TestSize.Level1)
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
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest073, TestSize.Level1)
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
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest074, TestSize.Level1)
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
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest075, TestSize.Level1)
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
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest076, TestSize.Level1)
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
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest077, TestSize.Level1)
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
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest078, TestSize.Level1)
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
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest079, TestSize.Level1)
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
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest080, TestSize.Level1)
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
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest081, TestSize.Level1)
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
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest082, TestSize.Level1)
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
HWTEST_F(ViewAbstractTestNg, ViewAbstractTestNg0083, TestSize.Level1)
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
HWTEST_F(ViewAbstractTestNg, ViewAbstractTestNg0084, TestSize.Level1)
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
HWTEST_F(ViewAbstractTestNg, ViewAbstractSetClickFocusTest001, TestSize.Level1)
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
     * @tc.steps2: Create another FrameNode and set a JS-based onClick event via SetJSFrameNodeOnClick.
     * @tc.expected: The FrameNode should also become focusable after setting JS onClick.
     */
    auto frameNode2 = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(frameNode2, nullptr);

    GestureEventFunc jsOnClick = [](GestureEvent&) {};
    ViewAbstract::SetJSFrameNodeOnClick(AceType::RawPtr(frameNode2), std::move(jsOnClick));

    auto focusHub2 = frameNode2->GetFocusHub();
    ASSERT_NE(focusHub2, nullptr);
    EXPECT_TRUE(focusHub2->IsFocusable());
}

/**
 * @tc.name: ViewAbstractTestNg0097
 * @tc.desc: test position attribute, use Edges type.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTestNg0097, TestSize.Level1)
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
 * @tc.name: SetLinearGradient
 * @tc.desc: Test SetLinearGradient of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractResourceObjectTest001, TestSize.Level1)
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
HWTEST_F(ViewAbstractTestNg, ViewAbstractResourceObjectTest002, TestSize.Level1)
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
HWTEST_F(ViewAbstractTestNg, ViewAbstractResourceObjectTest003, TestSize.Level1)
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
HWTEST_F(ViewAbstractTestNg, ViewAbstractResourceObjectTest004, TestSize.Level1)
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
HWTEST_F(ViewAbstractTestNg, ViewAbstractResourceObjectTest005, TestSize.Level1)
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
HWTEST_F(ViewAbstractTestNg, ViewAbstractResourceObjectTest006, TestSize.Level1)
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
HWTEST_F(ViewAbstractTestNg, ViewAbstractResourceObjectTest007, TestSize.Level1)
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
HWTEST_F(ViewAbstractTestNg, ViewAbstractResourceObjectTest008, TestSize.Level1)
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
HWTEST_F(ViewAbstractTestNg, ViewAbstractResourceObjectTest009, TestSize.Level1)
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
HWTEST_F(ViewAbstractTestNg, ViewAbstractResourceObjectTest010, TestSize.Level1)
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
HWTEST_F(ViewAbstractTestNg, ViewAbstractResourceObjectTest011, TestSize.Level1)
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
HWTEST_F(ViewAbstractTestNg, ViewAbstractResourceObjectTest012, TestSize.Level1)
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
HWTEST_F(ViewAbstractTestNg, ViewAbstractResourceObjectTest013, TestSize.Level1)
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
HWTEST_F(ViewAbstractTestNg, ViewAbstractResourceObjectTest014, TestSize.Level1)
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
HWTEST_F(ViewAbstractTestNg, ViewAbstractResourceObjectTest015, TestSize.Level1)
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
    colorStr = pattern->GetResCacheMapByKey("viewAbstract.colorBlend");
    EXPECT_EQ(colorStr, result.ToString());
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SetMask
 * @tc.desc: Test SetMask of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractResourceObjectTest016, TestSize.Level1)
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
HWTEST_F(ViewAbstractTestNg, ViewAbstractResourceObjectTest017, TestSize.Level1)
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
HWTEST_F(ViewAbstractTestNg, ViewAbstractResourceObjectTest018, TestSize.Level1)
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
HWTEST_F(ViewAbstractTestNg, ViewAbstractResourceObjectTest019, TestSize.Level1)
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
HWTEST_F(ViewAbstractTestNg, ViewAbstractResourceObjectTest020, TestSize.Level1)
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
HWTEST_F(ViewAbstractTestNg, ViewAbstractResourceObjectTest021, TestSize.Level1)
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
HWTEST_F(ViewAbstractTestNg, ViewAbstractResourceObjectTest022, TestSize.Level1)
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

} // namespace OHOS::Ace::NG