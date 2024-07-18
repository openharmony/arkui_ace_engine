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

#include "test/unittest/core/base/view_abstract_test_ng.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
/**
 * @tc.name: ViewAbstractTest031
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest031, TestSize.Level1)
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
    ViewAbstract::SetFlexShrink(RATIO);
    ViewAbstract::SetFlexGrow(RATIO);
    ViewAbstract::SetFlexBasis(WIDTH);
    ViewAbstract::SetFlexBasis(AceType::RawPtr(FRAME_NODE_REGISTER), WIDTH);
    ViewAbstract::SetDisplayIndex(TEN);
    ViewAbstract::SetZIndex(FOUF);

    Alignment alignment;
    ViewAbstract::SetAlign(std::move(alignment));
    auto visible = static_cast<VisibleType>(INDEX);
    ViewAbstract::SetVisibility(std::move(visible));
    ViewAbstract::SetOpacity(OPACITYS);

    /**
     * @tc.expected: Return expected results.
     */
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest032
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest032, TestSize.Level1)
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
    OffsetT<Dimension> values = { WIDTH, HEIGHT };
    ViewAbstract::SetPosition(values);
    ViewAbstract::SetOffset(values);
    ViewAbstract::MarkAnchor(values);

    ViewAbstract::SetPadding(NG::CalcLength(WIDTH));
    ViewAbstract::SetPadding(AceType::RawPtr(FRAME_NODE_REGISTER), NG::CalcLength(WIDTH));
    ViewAbstract::SetMargin(NG::CalcLength(WIDTH));
    ViewAbstract::SetMargin(AceType::RawPtr(FRAME_NODE_REGISTER), NG::CalcLength(WIDTH));
    ViewAbstract::SetBorderRadius(WIDTH);
    ViewAbstract::SetBorderRadius(nullptr, WIDTH);
    ViewAbstract::SetBorderColor(BLUE);
    ViewAbstract::SetBorderColor(nullptr, BLUE);
    ViewAbstract::SetBorderWidth(WIDTH);
    ViewAbstract::SetBorderWidth(nullptr, WIDTH);

    auto borderStyle = static_cast<BorderStyle>(INDEX);
    ViewAbstract::SetBorderStyle(borderStyle);
    ViewAbstract::SetBorderStyle(nullptr, borderStyle);

    /**
     * @tc.expected: Return expected results.
     */
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest033
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest033, TestSize.Level1)
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
    OffsetT<Dimension> values = { WIDTH, HEIGHT };
    ViewAbstract::SetPosition(values);
    ViewAbstract::SetOffset(values);
    ViewAbstract::MarkAnchor(values);

    NG::PaddingProperty paddings;
    ViewAbstract::SetPadding(paddings);
    ViewAbstract::SetPadding(AceType::RawPtr(FRAME_NODE_REGISTER), paddings);

    NG::MarginProperty margins;
    ViewAbstract::SetMargin(margins);
    ViewAbstract::SetMargin(AceType::RawPtr(FRAME_NODE_REGISTER), margins);

    NG::BorderRadiusProperty borderRadius;
    ViewAbstract::SetBorderRadius(borderRadius);

    NG::BorderColorProperty borderColors;
    ViewAbstract::SetBorderColor(borderColors);

    NG::BorderWidthProperty borderWidth;
    ViewAbstract::SetBorderWidth(borderWidth);

    NG::BorderStyleProperty borderStyles;
    ViewAbstract::SetBorderStyle(borderStyles);
    ViewAbstract::SetBorderStyle(nullptr, borderStyles);

    /**
     * @tc.expected: Return expected results.
     */
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest034
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest034, TestSize.Level1)
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
    BlurOption blurOption;
    ViewAbstract::SetBrightness(RADIUS);
    ViewAbstract::SetGrayScale(RADIUS);
    ViewAbstract::SetContrast(RADIUS);
    ViewAbstract::SetContrast(nullptr, RADIUS);
    ViewAbstract::SetSaturate(RADIUS);
    ViewAbstract::SetSepia(RADIUS);
    ViewAbstract::SetInvert(invert);
    ViewAbstract::SetHueRotate(RATIO);
    ViewAbstract::SetColorBlend(BLUE);
    ViewAbstract::SetBackdropBlur(RADIUS, blurOption);
    ViewAbstract::SetFrontBlur(RADIUS, blurOption);
    ViewAbstract::SetClipEdge(false);

    /**
     * @tc.expected: Return expected results.
     */
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest035
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest035, TestSize.Level1)
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
    viewAbstractModelNG.SetScale(1.0f, 1.0f, 0.0f);
    DimensionOffset value = { WIDTH, HEIGHT };
    viewAbstractModelNG.SetPivot(WIDTH, HEIGHT, ZERO);
    NG::TranslateOptions values;
    ViewAbstract::SetTranslate(std::move(values));
    Vector5F scales(1.0f, 1.0f, 2.0f, 2.0f, 0.0f);
    ViewAbstract::SetRotate(scales);
    Matrix4 matrix;
    ViewAbstract::SetTransformMatrix(std::move(matrix));

    ShadowStyle style { 1 };
    Shadow shadow { RATIO, OFFSET, BLUE, style };
    ViewAbstract::SetBackShadow(shadow);
    NG::Gradient gradient;
    ViewAbstract::SetLinearGradient(std::move(gradient));
    ViewAbstract::SetSweepGradient(std::move(gradient));
    ViewAbstract::SetRadialGradient(std::move(gradient));
    TransitionOptions options;
    ViewAbstract::SetTransition(std::move(options));
    ViewAbstract::SetTransition(AceType::RawPtr(FRAME_NODE_REGISTER), std::move(options));
    RefPtr<BasicShape> basicShape;
    ViewAbstract::SetClipShape(std::move(basicShape));
    ViewAbstract::SetMask(std::move(basicShape));
    ViewAbstract::SetMask(nullptr, std::move(basicShape));

    /**
     * @tc.expected: Return expected results.
     */
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest036
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest036, TestSize.Level1)
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
    ViewAbstract::SetBorderImageSource(srcimages);
    ViewAbstract::SetBorderImageSource(nullptr, srcimages);
    ViewAbstract::SetHasBorderImageSlice(false);
    ViewAbstract::SetHasBorderImageSlice(nullptr, false);
    ViewAbstract::SetHasBorderImageWidth(false);
    ViewAbstract::SetHasBorderImageWidth(nullptr, false);
    ViewAbstract::SetHasBorderImageOutset(false);
    ViewAbstract::SetHasBorderImageOutset(nullptr, false);
    ViewAbstract::SetHasBorderImageRepeat(false);
    ViewAbstract::SetSphericalEffect(RATIO);
    ViewAbstract::SetSphericalEffect(nullptr, RATIO);
    ViewAbstract::SetLightUpEffect(RATIO);
    ViewAbstract::SetLightUpEffect(nullptr, RATIO);
    ViewAbstract::SetForegroundColor(BLUE);
    ViewAbstract::SetForegroundColor(AceType::RawPtr(FRAME_NODE_REGISTER), BLUE);
    ViewAbstract::ClearWidthOrHeight(true);
    ViewAbstract::SetUseEffect(false);
    ViewAbstract::SetUseEffect(nullptr, false);
    ViewAbstract::SetRenderGroup(false);
    ViewAbstract::SetRenderGroup(nullptr, false);
    ViewAbstract::SetRenderFit(RenderFit::BOTTOM);
    ViewAbstract::SetRenderFit(nullptr, RenderFit::BOTTOM);
    ViewAbstract::UpdateSafeAreaExpandOpts(safeAreaExpandOpts);
    ViewAbstract::SetObscured(reasonsVector);

    PixStretchEffectOption option;
    option.bottom = BOTTOM;
    option.left = LEFT;
    option.right = RIGHT;
    option.top = TOP;
    ViewAbstract::SetPixelStretchEffect(option);

    /**
     * @tc.expected: Return expected results.
     */
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest037
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest037, TestSize.Level1)
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
    RefPtr<BorderImage> borderImage;
    ViewAbstract::SetBorderImage(std::move(borderImage));
    Gradient gradient;
    ViewAbstract::SetBorderImageGradient(std::move(gradient));
    RefPtr<NG::ChainedTransitionEffect> effect;
    ViewAbstract::SetChainedTransition(std::move(effect));
    ViewAbstract::SetChainedTransition(AceType::RawPtr(FRAME_NODE_REGISTER), std::move(effect));
    RefPtr<ProgressMaskProperty> progress;
    ViewAbstract::SetProgressMask(std::move(progress));
    ViewAbstract::SetProgressMask(nullptr, std::move(progress));
    auto strategy = static_cast<ForegroundColorStrategy>(INDEX);
    ViewAbstract::SetForegroundColorStrategy(std::move(strategy));
    ViewAbstract::SetForegroundColorStrategy(AceType::RawPtr(FRAME_NODE_REGISTER), std::move(strategy));
    OverlayOptions overlay;
    ViewAbstract::SetOverlay(std::move(overlay));

    /**
     * @tc.expected: Return expected results.
     */
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest038
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest038, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    constexpr char TAG_ROOT[] = "root";
    constexpr char TAG_CHILD[] = "child";
    const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
    const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
    const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    /**
     * @tc.steps: step2. callback SetClickEffectLevel.push FrameNode is not null.
     */
    viewAbstract.SetClickEffectLevel(ClickEffectLevel::LIGHT, 1.0f);
    viewAbstract.SetClickEffectLevel(AceType::RawPtr(FRAME_NODE_REGISTER), ClickEffectLevel::LIGHT, 1.0f);
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.expected: step3. Return expected results..
     */
    auto Node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(Node, nullptr);
    auto layoutProperty = Node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    viewStackProcessor.instance = nullptr;
}

/**
 * @tc.name: ViewAbstractTest039
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest039, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object viewAbstract.
     */
    ViewStackProcessor viewStackProcessor;
    ViewAbstract viewAbstract;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    /**
     * @tc.steps: step2.ClearStack and callback SetScale.
     */
    viewStackProcessor.GetInstance()->ClearStack();
    /**
     * @tc.expected: step2. Return expected results..
     */
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    viewAbstract.SetClickEffectLevel(ClickEffectLevel::LIGHT, 1.0f);
    ViewAbstract::ResetMinSize(true);
    EXPECT_FALSE(result);
    /**
     * @tc.steps: step3. visualState_ is null.
     * @tc.expected: result is true.
     */
    ViewStackProcessor::GetInstance()->visualState_ = std::nullopt;
    result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    viewAbstract.SetClickEffectLevel(ClickEffectLevel::LIGHT, 1.0f);
    ViewAbstract::ResetMinSize(true);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: ViewAbstractTest040
 * @tc.desc: Test the BindMenu and BindContextMenu of ViewAbstractModelNG
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest040, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create and put mainNode, then build some necessary params.
     */
    const RefPtr<FrameNode> mainNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(mainNode);

    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);

    ASSERT_NE(SubwindowManager::GetInstance(), nullptr);
    std::function<void()> flagFunc = []() { flag++; };
    std::vector<NG::OptionParam> params = {};
    std::function<void()> buildFunc;
    MenuParam menuParam;
    std::function<void()> previewBuildFunc = nullptr;
    /**
     * @tc.steps: step2. call Bind and BindContextMenu multiple times with unless parameters
     * @tc.expected: The show or hide method will not call flagFunc.
     */
    viewAbstractModelNG.BindMenu(std::move(params), std::move(buildFunc), menuParam);
    buildFunc = []() {};
    viewAbstractModelNG.BindMenu(std::move(params), std::move(buildFunc), menuParam);
    params.push_back(OptionParam());
    viewAbstractModelNG.BindMenu(std::move(params), std::move(buildFunc), menuParam);
    menuParam.type = MenuType::CONTEXT_MENU;
    viewAbstractModelNG.BindContextMenu(ResponseType::LONG_PRESS, buildFunc, menuParam, previewBuildFunc);
    EXPECT_EQ(flag, 0);
    /**
     * @tc.steps: step3. set appear and disappear and recall BindMenu and BindContextMenu;
     * @tc.expected: The flagFunc call times meet expectations.
     */
    menuParam.onAppear = flagFunc;
    menuParam.onDisappear = flagFunc;
    menuParam.type = MenuType::MENU;
    viewAbstractModelNG.BindMenu(std::move(params), std::move(buildFunc), menuParam);
    menuParam.type = MenuType::CONTEXT_MENU;
    viewAbstractModelNG.BindContextMenu(ResponseType::RIGHT_CLICK, buildFunc, menuParam, previewBuildFunc);
    menuParam.contextMenuRegisterType = ContextMenuRegisterType::CUSTOM_TYPE;
    menuParam.isShow = true;
    viewAbstractModelNG.BindContextMenu(ResponseType::LONG_PRESS, buildFunc, menuParam, previewBuildFunc);
    EXPECT_EQ(flag, 0);
    auto subwindow = SubwindowManager::GetInstance()->GetSubwindow(container);
    EXPECT_EQ(subwindow, nullptr);

    /**
     * @tc.steps: step4. create mouseInfo, set some useless params and call onMouseCallback_;
     * @tc.expected: StopPropagation in mouseInfo is false.
     */
    auto inputHub = mainNode->GetOrCreateInputEventHub();
    ASSERT_NE(inputHub, nullptr);
    auto mouseCallback = [](MouseInfo& info){};
    inputHub->showMenu_ = AceType::MakeRefPtr<InputEvent>(mouseCallback);
    ASSERT_NE(inputHub->showMenu_, nullptr);
    MouseInfo mouseInfo;
    mouseInfo.SetButton(MouseButton::LEFT_BUTTON);
    mouseInfo.SetAction(MouseAction::NONE);
    inputHub->showMenu_->onMouseCallback_(mouseInfo);
    mouseInfo.SetButton(MouseButton::RIGHT_BUTTON);
    mouseInfo.SetAction(MouseAction::NONE);
    inputHub->showMenu_->onMouseCallback_(mouseInfo);
    EXPECT_FALSE(mouseInfo.IsStopPropagation());
    /**
     * @tc.steps: step4. create mouseInfo, set right param and call onMouseCallback_;
     * @tc.expected: StopPropagation in mouseInfo is false.
     */
    mouseInfo.SetButton(MouseButton::RIGHT_BUTTON);
    mouseInfo.SetAction(MouseAction::RELEASE);
    inputHub->showMenu_->onMouseCallback_(mouseInfo);
    EXPECT_FALSE(mouseInfo.IsStopPropagation());

    /**
     * @tc.steps: step5. create mouseInfo, set right param and call BindMenuWithCustomNode;
     * @tc.expected: StopPropagation in mouseInfo is true.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    PipelineBase::GetCurrentContext()->SetThemeManager(themeManager);
    PipelineBase::GetCurrentContext()->SetEventManager(AceType::MakeRefPtr<EventManager>());
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    int32_t nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    const RefPtr<FrameNode> targetNode =
        FrameNode::CreateFrameNode("targetNode", nodeId, AceType::MakeRefPtr<Pattern>(), true);
    std::vector<OptionParam> param;
    ViewAbstract::BindMenuWithItems(std::move(param), targetNode, OFFSETF, menuParam);
    menuParam.type = MenuType::MULTI_MENU;
    ViewAbstract::BindMenuWithCustomNode(std::move(buildFunc), targetNode, OFFSETF, menuParam,
        std::move(previewBuildFunc));
    EXPECT_FALSE(mouseInfo.IsStopPropagation());
    param.push_back(OptionParam());
    ViewAbstract::BindMenuWithItems(std::move(param), targetNode, OFFSETF, menuParam);
    menuParam.type = MenuType::CONTEXT_MENU;
    ViewAbstract::BindMenuWithCustomNode(std::move(buildFunc), targetNode, OFFSETF, menuParam,
        std::move(previewBuildFunc));
    EXPECT_FALSE(mouseInfo.IsStopPropagation());
}

/**
 * @tc.name: ViewAbstractTest041
 * @tc.desc: Test the BindMenu and BindContextMenu of ViewAbstractModelNG
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest041, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat frameNode and other creat.
     */
    int32_t nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    const RefPtr<FrameNode> frameNode =
        FrameNode::CreateFrameNode("frameNode", nodeId, AceType::MakeRefPtr<Pattern>(), true);

    auto layoutProperty = frameNode->GetLayoutProperty();
    CalcSize idealSize = { CalcLength(ZERO), CalcLength(ZERO) };
    layoutProperty->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    layoutProperty->calcLayoutConstraint_->minSize = idealSize;
    layoutProperty->calcLayoutConstraint_->maxSize = idealSize;
    EffectOption option;
    Color color = Color::TRANSPARENT;
    option.color = color;

    std::vector<std::pair<float, float>> fractionStops;
    fractionStops.push_back(std::pair<float, float>(0.0f, 1.0f));
    CalcDimension dimensionRadius(0.0);
    LinearGradientBlurPara blurPara(dimensionRadius, fractionStops, GradientDirection::LEFT);
    /**
     * @tc.steps: step2. ResetMinSize test, IsCurrentVisualStateProcess() == false
     * @tc.expected:call ResetMinSize(),calcLayoutConstraint_ not change
     */
    ViewStackProcessor::GetInstance()->SetVisualState(VisualState::DISABLED);
    ViewAbstract::ResetMinSize(true);
    ViewAbstract::ResetMinSize(AceType::RawPtr(FRAME_NODE_REGISTER), true);
    ViewAbstract::ResetMaxSize(true);
    ViewAbstract::ResetMaxSize(AceType::RawPtr(FRAME_NODE_REGISTER), true);
    ViewAbstract::SetBackgroundAlign(Alignment::TOP_LEFT);
    ViewAbstract::SetBackgroundEffect(option);
    ViewAbstract::SetBackgroundEffect(AceType::RawPtr(FRAME_NODE_REGISTER), option);
    ViewAbstract::SetDynamicLightUp(0, 0);
    ViewAbstract::SetDynamicLightUp(AceType::RawPtr(FRAME_NODE_REGISTER), 0, 0);
    ViewAbstract::SetLinearGradientBlur(blurPara);
    ViewAbstract::SetLinearGradientBlur(nullptr, blurPara);
    EXPECT_TRUE(layoutProperty->calcLayoutConstraint_->minSize.has_value());
    EXPECT_TRUE(layoutProperty->calcLayoutConstraint_->maxSize.has_value());

    /**
     * @tc.steps: step3. ResetMinSize test, IsCurrentVisualStateProcess() == true
     * @tc.expected:call ResetMinSize(),calcLayoutConstraint_->minSize.Width not change
     */
    ViewStackProcessor::GetInstance()->visualState_ = std::nullopt;
    ViewAbstract::ResetMinSize(true);
    ViewAbstract::ResetMaxSize(true);
    ViewAbstract::SetBackgroundAlign(Alignment::BOTTOM_RIGHT);
    ViewAbstract::SetBackgroundEffect(option);
    ViewAbstract::SetDynamicLightUp(0, 0);
    ViewAbstract::SetLinearGradientBlur(blurPara);
    ViewAbstract::DisableOnAppear();
    ViewAbstract::DisableOnAreaChange();
    ViewAbstract::DisableOnDisAppear();
    std::vector<DimensionRect> responseRegion;
    DimensionRect responseRect(Dimension(0), Dimension(0), DimensionOffset(OFFSETF));
    responseRegion.emplace_back(responseRect);
    ViewAbstract::SetMouseResponseRegion(responseRegion);
    ViewAbstract::SetMouseResponseRegion(AceType::RawPtr(FRAME_NODE_REGISTER), responseRegion);
    EXPECT_TRUE(layoutProperty->calcLayoutConstraint_->minSize.value().Width().has_value());
    EXPECT_TRUE(layoutProperty->calcLayoutConstraint_->maxSize.value().Width().has_value());
}

/**
 * @tc.name: ViewAbstractTest042
 * @tc.desc: Test the SetKeyboardShortcut of View_Abstract for tab/Up arrow/Down arrow/Left arrow/Right arrow key.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest042, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode and get eventManager.
     */
    const RefPtr<FrameNode> targetNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto eventManager = PipelineContext::GetCurrentContext()->GetEventManager();
    /**
     * @tc.steps: step2. call SetKeyboardShortcut with tab and ModifierKey.
     * @tc.expected: add fail
     */
    std::vector<ModifierKey> keys;
    keys.push_back(ModifierKey::SHIFT);
    ViewAbstract::SetKeyboardShortcut(VALUE_TAB, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
    keys.clear();

    /**
     * @tc.steps: step3. call SetKeyboardShortcut with up arrow.
     * @tc.expected: add success
     */
    ViewAbstract::SetKeyboardShortcut(VALUE_DPAD_UP, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
    keys.clear();

    /**
     * @tc.steps: step4. call SetKeyboardShortcut with up arrow and ModifierKey.
     * @tc.expected: add success
     */
    keys.push_back(ModifierKey::ALT);
    ViewAbstract::SetKeyboardShortcut(VALUE_DPAD_UP, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
    keys.clear();

    /**
     * @tc.steps: step5. call SetKeyboardShortcut with tab.
     * @tc.expected: add success
     */

    ViewAbstract::SetKeyboardShortcut(VALUE_TAB, std::move(keys), callback);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
}

/**
 * @tc.name: ViewAbstractOffsetEdges001
 * @tc.desc: test offset attribute, use Edges type.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractOffset001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create and put mainNode, then build some necessary params.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);

    /**
     * @tc.steps: step2. get node in ViewStackProcessor.
     * @tc.expected: node is not null.
     */
    auto rootFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(rootFrameNode, nullptr);

    /**
     * @tc.steps: step3. use ViewAbstract::SetOffsetEdges.
     * @tc.expected: success set render property offsetEdges value.
     */
    EdgesParam edges;
    CalcDimension top(30, DimensionUnit::VP);
    CalcDimension left(20, DimensionUnit::VP);
    edges.SetTop(top);
    edges.SetLeft(left);
    ViewAbstract::SetOffsetEdges(edges);

    EXPECT_NE(FRAME_NODE_ROOT->GetRenderContext(), nullptr);
    EXPECT_EQ(FRAME_NODE_ROOT->GetRenderContext()
                  ->GetOffsetEdgesValue(EdgesParam {}).top.value_or(Dimension {}).ConvertToVp(), 30.0f);
    EXPECT_EQ(FRAME_NODE_ROOT->GetRenderContext()
                  ->GetOffsetEdgesValue(EdgesParam {}).left.value_or(Dimension {}).ConvertToVp(), 20.0f);

    /**
     * @tc.steps: step5. finish view stack.
     */
    ViewStackProcessor::GetInstance()->Finish();
}

/**
 * @tc.name: ViewAbstractPositionEdges001
 * @tc.desc: test position attribute, use Edges type.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractPositionEdges001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create and put mainNode, then build some necessary params.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);

    /**
     * @tc.steps: step2. get node in ViewStackProcessor.
     * @tc.expected: node is not null.
     */
    auto rootFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(rootFrameNode, nullptr);

    /**
     * @tc.steps: step3. use ViewAbstract::SetPositionEdges.
     * @tc.expected: success set render property PositionEdges value.
     */
    EdgesParam edges;
    CalcDimension bottom(30, DimensionUnit::VP);
    CalcDimension right(20, DimensionUnit::VP);
    edges.SetBottom(bottom);
    edges.SetRight(right);
    ViewAbstract::SetPositionEdges(edges);

    EXPECT_NE(FRAME_NODE_ROOT->GetRenderContext(), nullptr);
    EXPECT_EQ(FRAME_NODE_ROOT->GetRenderContext()
                  ->GetPositionEdgesValue(EdgesParam {}).bottom.value_or(Dimension {}).ConvertToVp(), 30.0f);
    EXPECT_EQ(FRAME_NODE_ROOT->GetRenderContext()
                  ->GetPositionEdgesValue(EdgesParam {}).right.value_or(Dimension {}).ConvertToVp(), 20.0f);

    /**
     * @tc.steps: step5. finish view stack.
     */
    ViewStackProcessor::GetInstance()->Finish();
}

/**
 * @tc.name: ViewAbstractDisableClickTest
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractDisableClickTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create framenode and check callback;
     * @tc.expected: callback is not null.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    GestureEventFunc tapEventFunc;
    ViewAbstract::SetOnClick(std::move(tapEventFunc));

    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(node, nullptr);
    auto gestureHub = node->GetOrCreateGestureEventHub();
    auto& callback = gestureHub->clickEventActuator_->userCallback_;
    EXPECT_NE(callback, nullptr);

    /**
     * @tc.steps: step2. Disable callback.
     * @tc.expected: callback is null.
     */
    ViewAbstract::DisableOnClick();
    EXPECT_EQ(callback, nullptr);

    /**
     * @tc.steps: step3. Add callback again.
     * @tc.expected: callback is not null.
     */
    GestureEventFunc tapEventFunc2;
    ViewAbstract::SetOnClick(std::move(tapEventFunc2));
    EXPECT_NE(callback, nullptr);
    ViewStackProcessor::GetInstance()->instance = nullptr;
}

/**
 * @tc.name: ViewAbstractDisableTouchTest
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractDisableTouchTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create framenode and check callback;
     * @tc.expected: callback is not null.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    TouchEventFunc touchEventFunc;
    ViewAbstract::SetOnTouch(std::move(touchEventFunc));

    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(node, nullptr);
    auto gestureHub = node->GetOrCreateGestureEventHub();
    auto& callback = gestureHub->touchEventActuator_->userCallback_;
    EXPECT_NE(callback, nullptr);

    /**
     * @tc.steps: step2. Disable callback.
     * @tc.expected: callback is null.
     */
    ViewAbstract::DisableOnTouch();
    EXPECT_EQ(callback, nullptr);

    /**
     * @tc.steps: step3. Add callback again.
     * @tc.expected: callback is not null.
     */
    TouchEventFunc touchEventFunc2;
    ViewAbstract::SetOnTouch(std::move(touchEventFunc2));
    EXPECT_NE(callback, nullptr);
    ViewStackProcessor::GetInstance()->instance = nullptr;
}

/**
 * @tc.name: ViewAbstractDisableMouseTest
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractDisableMouseTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create framenode and check callback;
     * @tc.expected: callback is not null.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    OnMouseEventFunc onMouseEventFunc;
    ViewAbstract::SetOnMouse(std::move(onMouseEventFunc));

    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(node, nullptr);
    auto eventHub = node->GetOrCreateInputEventHub();
    auto& callback = eventHub->mouseEventActuator_->userCallback_;
    EXPECT_NE(callback, nullptr);

    /**
     * @tc.steps: step2. Disable callback.
     * @tc.expected: callback is null.
     */
    ViewAbstract::DisableOnMouse();
    EXPECT_EQ(callback, nullptr);

    /**
     * @tc.steps: step3. Add callback again.
     * @tc.expected: callback is not null.
     */
    OnMouseEventFunc onMouseEventFunc2;
    ViewAbstract::SetOnMouse(std::move(onMouseEventFunc2));
    ViewAbstract::SetJSFrameNodeOnMouse(AceType::RawPtr(FRAME_NODE_REGISTER), std::move(onMouseEventFunc2));
    ViewAbstract::ClearJSFrameNodeOnMouse(AceType::RawPtr(FRAME_NODE_REGISTER));
    EXPECT_NE(callback, nullptr);
    ViewStackProcessor::GetInstance()->instance = nullptr;
}

/**
 * @tc.name: ViewAbstractDisableHoverTest
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractDisableHoverTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create framenode and check callback;
     * @tc.expected: callback is not null.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    OnHoverFunc onHoverEventFunc;
    ViewAbstract::SetOnHover(std::move(onHoverEventFunc));

    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(node, nullptr);
    auto eventHub = node->GetOrCreateInputEventHub();
    auto& callback = eventHub->hoverEventActuator_->userCallback_;
    EXPECT_NE(callback, nullptr);

    /**
     * @tc.steps: step2. Disable callback.
     * @tc.expected: callback is null.
     */
    ViewAbstract::DisableOnHover();
    EXPECT_EQ(callback, nullptr);

    /**
     * @tc.steps: step3. Add callback again.
     * @tc.expected: callback is not null.
     */
    OnHoverFunc onHoverEventFunc2;
    ViewAbstract::SetOnHover(std::move(onHoverEventFunc2));
    EXPECT_NE(callback, nullptr);
    ViewStackProcessor::GetInstance()->instance = nullptr;
}

/**
 * @tc.name: ViewAbstractDisableKeyTest
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractDisableKeyTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create framenode and check callback;
     * @tc.expected: callback is not null.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    OnKeyCallbackFunc onKeyCallback = [](KeyEventInfo& info) {};
    ViewAbstract::SetOnKeyEvent(std::move(onKeyCallback));

    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(node, nullptr);
    auto focusHub = node->GetOrCreateFocusHub();
    auto& callback = focusHub->focusCallbackEvents_->onKeyEventCallback_;
    EXPECT_TRUE(callback);

    /**
     * @tc.steps: step2. Disable callback.
     * @tc.expected: callback is null.
     */
    ViewAbstract::DisableOnKeyEvent();
    EXPECT_FALSE(callback);

    /**
     * @tc.steps: step3. Add callback again.
     * @tc.expected: callback is not null.
     */
    OnKeyCallbackFunc onKeyCallback2 = [](KeyEventInfo& info) {};
    ViewAbstract::SetOnKeyEvent(std::move(onKeyCallback2));
    EXPECT_TRUE(callback);
    ViewStackProcessor::GetInstance()->instance = nullptr;
}

/**
 * @tc.name: ViewAbstractDisableFocusTest
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractDisableFocusTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create framenode and check callback;
     * @tc.expected: callback is not null.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    OnFocusFunc onFocusCallback = []() {};
    ViewAbstract::SetOnFocus(std::move(onFocusCallback));
    ViewAbstract::SetOnFocus(AceType::RawPtr(FRAME_NODE_REGISTER), std::move(onFocusCallback));
    ViewAbstract::SetJSFrameNodeOnFocusCallback(AceType::RawPtr(FRAME_NODE_REGISTER), std::move(onFocusCallback));
    ViewAbstract::ClearJSFrameNodeOnFocusCallback(AceType::RawPtr(FRAME_NODE_REGISTER));

    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(node, nullptr);
    auto focusHub = node->GetOrCreateFocusHub();
    auto& callback = focusHub->focusCallbackEvents_->onFocusCallback_;
    EXPECT_NE(callback, nullptr);

    /**
     * @tc.steps: step2. Disable callback.
     * @tc.expected: callback is null.
     */
    ViewAbstract::DisableOnFocus();
    EXPECT_EQ(callback, nullptr);

    /**
     * @tc.steps: step3. Add callback again.
     * @tc.expected: callback is not null.
     */
    OnFocusFunc onFocusCallback2 = []() {};
    ViewAbstract::SetOnFocus(std::move(onFocusCallback2));
    EXPECT_NE(callback, nullptr);
    ViewStackProcessor::GetInstance()->instance = nullptr;
}

/**
 * @tc.name: ViewAbstractDisableBlurTest
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractDisableBlurTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create framenode and check callback;
     * @tc.expected: callback is not null.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    OnBlurFunc onBlurCallback = []() {};
    ViewAbstract::SetOnFocus(std::move(onBlurCallback));
    ViewAbstract::SetJSFrameNodeOnBlurCallback(AceType::RawPtr(FRAME_NODE_REGISTER), std::move(onBlurCallback));
    ViewAbstract::ClearJSFrameNodeOnBlurCallback(AceType::RawPtr(FRAME_NODE_REGISTER));

    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNodeOne = static_cast<FrameNode*>(ViewAbstract::GetFrameNode());
    EXPECT_EQ(strcmp(frameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(node, nullptr);
    auto focusHub = node->GetOrCreateFocusHub();
    auto& callback = focusHub->focusCallbackEvents_->onBlurCallback_;
    EXPECT_FALSE(callback);

    /**
     * @tc.steps: step2. Disable callback.
     * @tc.expected: callback is null.
     */
    ViewAbstract::DisableOnBlur();
    EXPECT_FALSE(callback);

    /**
     * @tc.steps: step3. Add callback again.
     * @tc.expected: callback is not null.
     */
    OnBlurFunc onBlurCallback2 = []() {};
    ViewAbstract::SetOnBlur(std::move(onBlurCallback2));
    ViewAbstract::SetOnBlur(AceType::RawPtr(FRAME_NODE_REGISTER), std::move(onBlurCallback2));
    EXPECT_TRUE(callback);
    ViewStackProcessor::GetInstance()->instance = nullptr;
}

/**
 * @tc.name: ViewAbstractMonopolizeEvent001
 * @tc.desc: View_Abstract set MonopolizeEvent true test
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractMonopolizeEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create and put mainNode, then build some necessary params.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);

    /**
     * @tc.steps: step2. set monopolize
     */
    ViewAbstract::SetMonopolizeEvents(true);
    ViewAbstract::SetMonopolizeEvents(AceType::RawPtr(FRAME_NODE_REGISTER), true);

    /**
     * @tc.steps: step3. get node in ViewStackProcessor.
     * @tc.expected: node is not null.
     */
    auto rootFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(rootFrameNode, nullptr);

    /**
     * @tc.steps: step4. get monopolizeEvents value of the node.
     * @tc.expected: value is equal to true.
     */
    EXPECT_EQ(rootFrameNode->GetMonopolizeEvents(), true);

    /**
     * @tc.steps: step5. finish view stack.
     */
    ViewStackProcessor::GetInstance()->Finish();
}

/**
 * @tc.name: ViewAbstractMonopolizeEvent002
 * @tc.desc: View_Abstract set MonopolizeEvent false test
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractMonopolizeEvent002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create and put mainNode, then build some necessary params.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);

    /**
     * @tc.steps: step2. set monopolize
     */
    ViewAbstract::SetMonopolizeEvents(false);

    /**
     * @tc.steps: step3. get node in ViewStackProcessor.
     * @tc.expected: node is not null.
     */
    auto rootFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(rootFrameNode, nullptr);

    /**
     * @tc.steps: step4. get monopolizeEvents value of the node.
     * @tc.expected: value is equal to true.
     */
    EXPECT_EQ(rootFrameNode->GetMonopolizeEvents(), false);

    /**
     * @tc.steps: step5. finish view stack.
     */
    ViewStackProcessor::GetInstance()->Finish();
}

/**
 * @tc.name: ViewAbstractMonopolizeEvent003
 * @tc.desc: View_Abstract not set MonopolizeEvent test (use default)
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractMonopolizeEvent003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create and put mainNode, then build some necessary params.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);

    /**
     * @tc.steps: step2. get node in ViewStackProcessor.
     * @tc.expected: node is not null.
     */
    auto rootFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(rootFrameNode, nullptr);

    /**
     * @tc.steps: step3. get monopolizeEvents value of the node.
     * @tc.expected: value is equal to true.
     */
    EXPECT_EQ(rootFrameNode->GetMonopolizeEvents(), false);

    /**
     * @tc.steps: step5. finish view stack.
     */
    ViewStackProcessor::GetInstance()->Finish();
}

/**
 * @tc.name: ViewAbstractMenuTransition001
 * @tc.desc: Test the BindMenu and BindContextMenu of ViewAbstractModelNG (use dafault)
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractMenuTransition001, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    PipelineBase::GetCurrentContext()->SetThemeManager(themeManager);
    PipelineBase::GetCurrentContext()->SetEventManager(AceType::MakeRefPtr<EventManager>());
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    int32_t nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    const RefPtr<FrameNode> mainNode =
        FrameNode::CreateFrameNode("targetNode", nodeId, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(mainNode);
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);

    ASSERT_NE(SubwindowManager::GetInstance(), nullptr);
    std::function<void()> flagFunc = []() { flag++; };
    std::vector<NG::OptionParam> params = {};
    std::function<void()> buildFunc;
    MenuParam menuParam;
    std::function<void()> previewBuildFunc = nullptr;

    menuParam.type = MenuType::MENU;
    menuParam.isShow = true;

    auto targetNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(targetNode, nullptr);
    std::function<void()> action = [] {};
    params.emplace_back("MenuItem1", "", action);
    params.emplace_back("MenuItem2", "", action);
    viewAbstractModelNG.BindMenu(std::move(params), std::move(buildFunc), menuParam);
    auto targetId = targetNode->GetId();

    auto menu =
        FrameNode::CreateFrameNode("targetNode", targetId, AceType::MakeRefPtr<MenuWrapperPattern>(targetId), false);
    overlayManager->menuMap_[targetId] = menu;
    auto menuNode = overlayManager->GetMenuNode(targetId);
    ASSERT_NE(menuNode, nullptr);
    auto wrapperPattern = menuNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(wrapperPattern, nullptr);
    EXPECT_EQ(wrapperPattern->HasTransitionEffect(), false);
    EXPECT_EQ(wrapperPattern->HasPreviewTransitionEffect(), false);
}

/**
 * @tc.name: ViewAbstractMenuTransition002
 * @tc.desc: Test the BindMenu and BindContextMenu of ViewAbstractModelNG (use true)
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractMenuTransition002, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    PipelineBase::GetCurrentContext()->SetThemeManager(themeManager);
    PipelineBase::GetCurrentContext()->SetEventManager(AceType::MakeRefPtr<EventManager>());
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    int32_t nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    const RefPtr<FrameNode> mainNode =
        FrameNode::CreateFrameNode("targetNode", nodeId, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(mainNode);
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);

    ASSERT_NE(SubwindowManager::GetInstance(), nullptr);
    std::function<void()> flagFunc = []() { flag++; };
    std::vector<NG::OptionParam> params = {};
    std::function<void()> buildFunc;
    MenuParam menuParam;
    std::function<void()> previewBuildFunc = nullptr;

    NG::RotateOptions rotate(0.0f, 0.0f, 0.0f, 0.0f, 0.5_pct, 0.5_pct);

    menuParam.hasTransitionEffect = true;
    menuParam.hasPreviewTransitionEffect = true;
    menuParam.transition = AceType::MakeRefPtr<NG::ChainedRotateEffect>(rotate);
    menuParam.previewTransition = AceType::MakeRefPtr<NG::ChainedRotateEffect>(rotate);
    menuParam.type = MenuType::MENU;
    menuParam.isShow = true;

    auto targetNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(targetNode, nullptr);
    std::function<void()> action = [] {};
    params.emplace_back("MenuItem1", "", action);
    params.emplace_back("MenuItem2", "", action);
    viewAbstractModelNG.BindMenu(std::move(params), std::move(buildFunc), menuParam);
    auto targetId = targetNode->GetId();

    auto menu =
        FrameNode::CreateFrameNode("targetNode", targetId, AceType::MakeRefPtr<MenuWrapperPattern>(targetId), false);
    overlayManager->menuMap_[targetId] = menu;
    auto menuNode = overlayManager->GetMenuNode(targetId);
    ASSERT_NE(menuNode, nullptr);
    auto wrapperPattern = menuNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(wrapperPattern, nullptr);
    EXPECT_EQ(wrapperPattern->HasTransitionEffect(), false);
    EXPECT_EQ(wrapperPattern->HasPreviewTransitionEffect(), false);
}

/**
 * @tc.name: ViewAbstractMenuBorderRadius001
 * @tc.desc: Test the BindMenu and BindContextMenu of ViewAbstractModelNG (use true)
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractMenuBorderRadius001, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    PipelineBase::GetCurrentContext()->SetThemeManager(themeManager);
    PipelineBase::GetCurrentContext()->SetEventManager(AceType::MakeRefPtr<EventManager>());
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    int32_t nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    const RefPtr<FrameNode> mainNode =
        FrameNode::CreateFrameNode("targetNode", nodeId, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->Push(mainNode);
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    ASSERT_NE(SubwindowManager::GetInstance(), nullptr);
    std::vector<NG::OptionParam> params = {};
    std::function<void()> buildFunc;
    MenuParam menuParam;

    menuParam.type = MenuType::MENU;
    menuParam.isShow = true;
    BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(Dimension(16));
    menuParam.borderRadius = borderRadius;

    auto targetNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(targetNode, nullptr);
    std::function<void()> action = [] {};
    params.emplace_back("MenuItem1", "", action);
    params.emplace_back("MenuItem2", "", action);
    viewAbstractModelNG.BindMenu(std::move(params), std::move(buildFunc), menuParam);
    auto targetId = targetNode->GetId();

    auto menu =
        FrameNode::CreateFrameNode("targetNode", targetId, AceType::MakeRefPtr<MenuWrapperPattern>(targetId), false);
    overlayManager->menuMap_[targetId] = menu;
    auto menuNode = overlayManager->GetMenuNode(targetId);
    ASSERT_NE(menuNode, nullptr);
    auto wrapperPattern = menuNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(wrapperPattern, nullptr);
    EXPECT_EQ(wrapperPattern->GetHasCustomRadius(), false);
}

/**
 * @tc.name: ViewAbstractDisableClickByFrameNodeTest
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractDisableClickByFrameNodeTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create framenode and check callback;
     * @tc.expected: callback is not null.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);

    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(node, nullptr);
    GestureEventFunc tapEventFunc;
    ViewAbstract::SetOnClick(AceType::RawPtr(node), std::move(tapEventFunc));
    auto gestureHub = node->GetOrCreateGestureEventHub();
    auto& callback = gestureHub->clickEventActuator_->userCallback_;
    EXPECT_NE(callback, nullptr);

    /**
     * @tc.steps: step2. Disable callback.
     * @tc.expected: callback is null.
     */
    ViewAbstract::DisableOnClick(AceType::RawPtr(node));
    EXPECT_EQ(callback, nullptr);
}

/**
 * @tc.name: ViewAbstractDisableTouchByFrameNodeTest
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractDisableTouchByFrameNodeTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create framenode and check callback;
     * @tc.expected: callback is not null.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);

    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(node, nullptr);
    TouchEventFunc touchEventFunc;
    ViewAbstract::SetOnTouch(AceType::RawPtr(node), std::move(touchEventFunc));
    auto gestureHub = node->GetOrCreateGestureEventHub();
    auto& callback = gestureHub->touchEventActuator_->userCallback_;
    EXPECT_NE(callback, nullptr);

    /**
     * @tc.steps: step2. Disable callback.
     * @tc.expected: callback is null.
     */
    ViewAbstract::DisableOnTouch(AceType::RawPtr(node));
    EXPECT_EQ(callback, nullptr);
}

/**
 * @tc.name: ViewAbstractDisableMouseByFrameNodeTest
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractDisableMouseByFrameNodeTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create framenode and check callback;
     * @tc.expected: callback is not null.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);

    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(node, nullptr);
    OnMouseEventFunc onMouseEventFunc;
    ViewAbstract::SetOnMouse(AceType::RawPtr(node), std::move(onMouseEventFunc));
    auto eventHub = node->GetOrCreateInputEventHub();
    auto& callback = eventHub->mouseEventActuator_->userCallback_;
    EXPECT_NE(callback, nullptr);

    /**
     * @tc.steps: step2. Disable callback.
     * @tc.expected: callback is null.
     */
    ViewAbstract::DisableOnMouse(AceType::RawPtr(node));
    EXPECT_EQ(callback, nullptr);
}

/**
 * @tc.name: ViewAbstractDisableHoverByFrameNodeTest
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractDisableHoverByFrameNodeTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create framenode and check callback;
     * @tc.expected: callback is not null.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);

    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(node, nullptr);
    OnHoverFunc onHoverEventFunc;
    ViewAbstract::SetOnHover(AceType::RawPtr(node), std::move(onHoverEventFunc));
    auto eventHub = node->GetOrCreateInputEventHub();
    auto& callback = eventHub->hoverEventActuator_->userCallback_;
    EXPECT_NE(callback, nullptr);

    /**
     * @tc.steps: step2. Disable callback.
     * @tc.expected: callback is null.
     */
    ViewAbstract::DisableOnHover(AceType::RawPtr(node));
    EXPECT_EQ(callback, nullptr);
}

/**
 * @tc.name: ViewAbstractDisableKeyByFrameNodeTest
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractDisableKeyByFrameNodeTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create framenode and check callback;
     * @tc.expected: callback is not null.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);

    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(node, nullptr);
    OnKeyCallbackFunc onKeyCallback = [](KeyEventInfo& info) {};
    ViewAbstract::SetOnKeyEvent(AceType::RawPtr(node), std::move(onKeyCallback));
    auto focusHub = node->GetOrCreateFocusHub();
    auto& callback = focusHub->focusCallbackEvents_->onKeyEventCallback_;
    EXPECT_TRUE(callback);

    /**
     * @tc.steps: step2. Disable callback.
     * @tc.expected: callback is null.
     */
    ViewAbstract::DisableOnKeyEvent(AceType::RawPtr(node));
    EXPECT_FALSE(callback);
}

/**
 * @tc.name: ViewAbstractDisableFocusByFrameNodeTest
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractDisableFocusByFrameNodeTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create framenode and check callback;
     * @tc.expected: callback is not null.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);

    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(node, nullptr);
    OnFocusFunc onFocusCallback = []() {};
    ViewAbstract::SetOnFocus(AceType::RawPtr(node), std::move(onFocusCallback));
    auto focusHub = node->GetOrCreateFocusHub();
    auto& callback = focusHub->focusCallbackEvents_->onFocusCallback_;
    EXPECT_NE(callback, nullptr);

    /**
     * @tc.steps: step2. Disable callback.
     * @tc.expected: callback is null.
     */
    ViewAbstract::DisableOnFocus(AceType::RawPtr(node));
    EXPECT_EQ(callback, nullptr);
}

/**
 * @tc.name: ViewAbstractDisableBlurByFrameNodeTest
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractDisableBlurByFrameNodeTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create framenode and check callback;
     * @tc.expected: callback is not null.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);

    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(node, nullptr);
    OnBlurFunc onBlurCallback = []() {};
    ViewAbstract::SetOnBlur(AceType::RawPtr(node), std::move(onBlurCallback));
    auto focusHub = node->GetOrCreateFocusHub();
    auto& callback = focusHub->focusCallbackEvents_->onBlurCallback_;
    EXPECT_TRUE(callback);

    /**
     * @tc.steps: step2. Disable callback.
     * @tc.expected: callback is null.
     */
    ViewAbstract::DisableOnBlur(AceType::RawPtr(node));
    EXPECT_FALSE(callback);
}

/**
 * @tc.name: ViewAbstractDisableOnAppearByFrameNodeTest
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractDisableOnAppearByFrameNodeTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create framenode and check callback;
     * @tc.expected: callback is not null.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);

    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(node, nullptr);
    std::function<void()> onAppearCallback = []() {};
    ViewAbstract::SetOnAppear(AceType::RawPtr(node), std::move(onAppearCallback));
    auto eventHub = node->GetEventHub<EventHub>();
    auto& callback = eventHub->onAppear_;
    EXPECT_NE(callback, nullptr);

    /**
     * @tc.steps: step2. Disable callback.
     * @tc.expected: callback is null.
     */
    ViewAbstract::DisableOnAppear(AceType::RawPtr(node));
    EXPECT_EQ(callback, nullptr);
}

/**
 * @tc.name: ViewAbstractDisableOnDisAppearByFrameNodeTest
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractDisableOnDisAppearByFrameNodeTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create framenode and check callback;
     * @tc.expected: callback is not null.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);

    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(node, nullptr);
    std::function<void()> onDiaAppearCallback = []() {};
    ViewAbstract::SetOnDisappear(AceType::RawPtr(node), std::move(onDiaAppearCallback));
    auto eventHub = node->GetEventHub<EventHub>();
    auto& callback = eventHub->onDisappear_;
    EXPECT_NE(callback, nullptr);

    /**
     * @tc.steps: step2. Disable callback.
     * @tc.expected: callback is null.
     */
    ViewAbstract::DisableOnDisappear(AceType::RawPtr(node));
    EXPECT_EQ(callback, nullptr);
}

/**
 * @tc.name: ViewAbstractDisableOnAreaChangeByFrameNodeTest
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractDisableOnAreaChangeByFrameNodeTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create framenode and check callback;
     * @tc.expected: callback is not null.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);

    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(node, nullptr);
    std::function<void(const RectF& oldRect, const OffsetF& oldOrigin, const RectF& rect, const OffsetF& origin)>
        onAreaChangeCallback =
            [](const RectF& oldRect, const OffsetF& oldOrigin, const RectF& rect, const OffsetF& origin) {};
    ViewAbstract::SetOnAreaChanged(AceType::RawPtr(node), std::move(onAreaChangeCallback));
    auto eventHub = node->GetEventHub<EventHub>();
    auto& callback = eventHub->onAreaChanged_;
    EXPECT_NE(callback, nullptr);

    /**
     * @tc.steps: step2. Disable callback.
     * @tc.expected: callback is null.
     */
    ViewAbstract::DisableOnAreaChange(AceType::RawPtr(node));
    EXPECT_EQ(callback, nullptr);
}

/**
 * @tc.name: ViewAbstractSetOnGestureJudgeBeiginByFrameNodeTest
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractSetOnGestureJudgeBeiginByFrameNodeTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create framenode and check callback;
     * @tc.expected: callback is not null.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);

    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(node, nullptr);
    GestureJudgeFunc onGestureJudgeCallback = [](const RefPtr<GestureInfo>& gestureInfo,
                                                  const std::shared_ptr<BaseGestureEvent>& info) {
        return GestureJudgeResult::REJECT;
    };
    ViewAbstract::SetOnGestureJudgeBegin(AceType::RawPtr(node), std::move(onGestureJudgeCallback));
    auto gestureHub = node->GetOrCreateGestureEventHub();
    auto& callback = gestureHub->gestureJudgeFunc_;
    EXPECT_NE(callback, nullptr);
}

/**
 * @tc.name: ViewAbstractSetOnSizeChangeByFrameNodeTest
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractSetOnSizeChangeByFrameNodeTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create framenode and check callback;
     * @tc.expected: callback is not null.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);

    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(node, nullptr);
    std::function<void(const RectF& oldRect, const RectF& rect)> onSizeChangeCallback = [](const RectF& oldRect,
                                                                                            const RectF& rect) {};
    ViewAbstract::SetOnSizeChanged(AceType::RawPtr(node), std::move(onSizeChangeCallback));
    auto eventHub = node->GetEventHub<EventHub>();
    auto& callback = eventHub->onSizeChanged_;
    EXPECT_NE(callback, nullptr);
}

/**
 * @tc.name: MotionBlur001
 * @tc.desc: SetMotionBlur.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, MotionBlur001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create and put mainNode, then build some necessary params.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);

    /**
     * @tc.steps: step2. get node in ViewStackProcessor.
     * @tc.expected: node is not null.
     */
    auto rootFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(rootFrameNode, nullptr);

    /**
     * @tc.steps: step3. use ViewAbstract::SetMotionBlur.
     * @tc.expected: success set render property motionBlur value.
     */
    MotionBlurOption motionBlurOption;
    motionBlurOption.radius = 5;
    motionBlurOption.anchor.x = 0.5;
    motionBlurOption.anchor.y = 0.5;
    ViewAbstract::SetMotionBlur(motionBlurOption);
    /**
     * @tc.steps: step4. get propMotionBlur value of the node.
     * @tc.expected: anchor.x = 0.5, anchor.y = 0.5, radius = 5.
     */
    EXPECT_NE(FRAME_NODE_ROOT->GetRenderContext(), nullptr);
    EXPECT_EQ(FRAME_NODE_ROOT->GetRenderContext()
                  ->GetOrCreateForeground()->propMotionBlur->anchor.x, 0.5);
    EXPECT_EQ(FRAME_NODE_ROOT->GetRenderContext()
                  ->GetOrCreateForeground()->propMotionBlur->anchor.y, 0.5);
    EXPECT_EQ(FRAME_NODE_ROOT->GetRenderContext()
                  ->GetOrCreateForeground()->propMotionBlur->radius, 5);

    /**
     * @tc.steps: step5. finish view stack.
     */
    ViewStackProcessor::GetInstance()->Finish();
}

/**
 * @tc.name: SetForegroundEffectTest
 * @tc.desc: Test the operation of setting foreground effect with different conditions.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, SetForegroundEffectTest, TestSize.Level1)
{
    /**
     * @tc.steps: Build a object viewAbstract and set visual state.
     */
    ViewStackProcessor viewStackProcessor;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: Build a object viewAbstract and set visual state.
     * @tc.expected: The foreground effect is not changed.
     */
    auto originValue = frameNode->GetRenderContext()->GetForegroundEffect();
    ViewAbstract::SetForegroundEffect(1.1f);
    ASSERT_NE(frameNode->GetRenderContext()->GetForegroundEffect(), 1.1f);
    ASSERT_EQ(frameNode->GetRenderContext()->GetForegroundEffect(), originValue);

    /**
     * @tc.steps: Set visual state to null and check the current visual state process
     * @tc.expected: The foreground effect is changed as expected.
     */
    ViewStackProcessor::GetInstance()->visualState_ = std::nullopt;
    ViewAbstract::SetForegroundEffect(1.1f);
    ASSERT_EQ(frameNode->GetRenderContext()->GetForegroundEffect(), 1.1f);
}
} // namespace OHOS::Ace::NG