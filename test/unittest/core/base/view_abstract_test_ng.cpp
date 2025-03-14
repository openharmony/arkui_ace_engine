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

#include "core/components/select/select_theme.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_model_ng.h"

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
    ViewAbstract::SetBackgroundImagePosition(BACKGROUNDPOSITION);
    ViewAbstract::SetBackgroundImagePosition(nullptr, BACKGROUNDPOSITION);
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
    ViewAbstract::SetBackgroundImagePosition(BACKGROUNDPOSITION);
    ViewAbstract::SetBackgroundImagePosition(nullptr, BACKGROUNDPOSITION);
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
    ViewAbstract::SetBrightnessBlender(nullptr);

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
    ViewAbstract::SetBrightnessBlender(nullptr);

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
    ViewAbstract::SetBackgroundImagePosition(BACKGROUNDPOSITION);
    ViewAbstract::SetBackgroundImagePosition(nullptr, BACKGROUNDPOSITION);
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

} // namespace OHOS::Ace::NG