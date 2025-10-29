/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "test/unittest/core/pattern/test_ng.h"

#define private public
#define protected public
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "ui/resource/resource_info.h"

#include "core/components/checkable/checkable_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/linear_layout/column_model_ng.h"
#include "core/components_ng/pattern/radio/radio_model_ng.h"
#include "core/components_ng/pattern/radio/radio_paint_property.h"
#include "core/components_ng/pattern/radio/radio_pattern.h"
#include "core/components_ng/pattern/stage/stage_manager.h"
#include "core/components_ng/pattern/stage/stage_pattern.h"
#include "core/components_ng/pattern/stage/page_event_hub.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "test/mock/core/common/mock_container.h"

using namespace testing;
using namespace testing::ext;
using RadioBuilderFunc = std::function<void()>;
namespace OHOS::Ace::NG {
namespace {
const std::string NAME = "radio";
const std::string VALUE = "radio";
const std::string NAME1 = "radio1";
const std::string GROUP_NAME = "radioGroup";
const std::string GROUP_NAME1 = "radioGroup1";
const std::string GROUP_NAME_CHANGE = "radioGroupChange";
constexpr bool CHECKED = true;
constexpr Dimension HORIZONTAL_PADDING = Dimension(5.0);
constexpr Dimension VERTICAL_PADDING = Dimension(4.0);
constexpr double DEFAULT_WIDTH = 100.0;
constexpr double DEFAULT_HEIGHT = 110.0;
constexpr Dimension DEFAULT_WIDTH_DIMENSION = Dimension(DEFAULT_WIDTH);
constexpr Dimension DEFAULT_HEIGHT_DIMENSION = Dimension(DEFAULT_HEIGHT);
const SizeF CONTENT_SIZE = SizeF(400.0, 500.0);
const OffsetF CONTENT_OFFSET = OffsetF(50.0, 60.0);
const std::optional<int32_t> INDICATOR_TYPE_TICK = 0;
const OHOS::Ace::NG::TouchHoverAnimationType INVALID_TOUCH_HOVER_ANIMARION_TYPE = TouchHoverAnimationType(100);
const SizeF CHILD_FRAME_SIZE = SizeF(50.0, 50.0);
const int32_t VERSION_TWELVE = 12;
const SizeF TEST_SIZE_0 = SizeF(0.0f, 0.0f);
const SizeF TEST_SIZE_100_200 = SizeF(100.0f, 200.0f);
const SizeF TEST_SIZE_100 = SizeF(100.0f, 100.0f);
const SizeF TEST_SIZE_200 = SizeF(200.0f, 200.0f);
const SizeF TEST_SIZE_50 = SizeF(50.0f, 50.0f);
const SizeF TEST_SIZE_60 = SizeF(60.0f, 60.0f);
constexpr float TEST_HEIGHT_60 = 60.0f;
constexpr float TEST_HORIZONPADDING = 5.0f;
} // namespace

class RadioTwoTestNg : public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    static RadioBuilderFunc RadioBuilder();
};

void RadioTwoTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        auto radioTheme = AceType::MakeRefPtr<RadioTheme>();
        radioTheme->hotZoneHorizontalPadding_ = HORIZONTAL_PADDING;
        radioTheme->hotZoneVerticalPadding_ = VERTICAL_PADDING;
        radioTheme->defaultWidth_ = DEFAULT_WIDTH_DIMENSION;
        radioTheme->defaultHeight_ = DEFAULT_HEIGHT_DIMENSION;
        return radioTheme;
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    MockContainer::SetUp();
}

void RadioTwoTestNg::TearDownTestSuite()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: RadioPaintMethodTest001
 * @tc.desc: Test Radio PaintMethod PaintRadio.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTwoTestNg, RadioPaintMethodTest001, TestSize.Level1)
{
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);
    auto radioPaintProperty = AceType::MakeRefPtr<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty, nullptr);
    PaintWrapper paintWrapper(nullptr, geometryNode, radioPaintProperty);
    auto radioModifier = AceType::MakeRefPtr<RadioModifier>();
    RadioPaintMethod radioPaintMethod(radioModifier);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(4);
    radioPaintMethod.radioModifier_->PaintRadio(canvas, false, CONTENT_SIZE, CONTENT_OFFSET);
}

/**
 * @tc.name: RadioPaintMethodTest002
 * @tc.desc: Test Radio PaintMethod PaintRadio.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTwoTestNg, RadioPaintMethodTest002, TestSize.Level1)
{
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);
    auto radioPaintProperty = AceType::MakeRefPtr<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty, nullptr);
    PaintWrapper paintWrapper(nullptr, geometryNode, radioPaintProperty);
    auto radioModifier = AceType::MakeRefPtr<RadioModifier>();
    RadioPaintMethod radioPaintMethod(radioModifier);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(4);
    radioPaintMethod.radioModifier_->enabled_ = AceType::MakeRefPtr<PropertyBool>(false);
    radioPaintMethod.radioModifier_->PaintRadio(canvas, false, CONTENT_SIZE, CONTENT_OFFSET);
    radioPaintMethod.radioModifier_->enabled_ = AceType::MakeRefPtr<PropertyBool>(true);
}

/**
 * @tc.name: RadioPaintMethodTest003
 * @tc.desc: Test Radio PaintMethod PaintRadio.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTwoTestNg, RadioPaintMethodTest003, TestSize.Level1)
{
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);
    auto radioPaintProperty = AceType::MakeRefPtr<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty, nullptr);
    PaintWrapper paintWrapper(nullptr, geometryNode, radioPaintProperty);
    auto radioModifier = AceType::MakeRefPtr<RadioModifier>();
    RadioPaintMethod radioPaintMethod(radioModifier);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(5);
    radioPaintMethod.radioModifier_->uiStatus_ =
        AceType::MakeRefPtr<PropertyInt>(static_cast<int32_t>(UIStatus::SELECTED));
    radioPaintMethod.radioModifier_->PaintRadio(canvas, false, CONTENT_SIZE, CONTENT_OFFSET);
    radioPaintMethod.radioModifier_->uiStatus_ =
        AceType::MakeRefPtr<PropertyInt>(static_cast<int32_t>(UIStatus::UNSELECTED));
}

/**
 * @tc.name: RadioPaintMethodTest004
 * @tc.desc: Test Radio PaintMethod PaintRadio.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTwoTestNg, RadioPaintMethodTest004, TestSize.Level1)
{
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);
    auto radioPaintProperty = AceType::MakeRefPtr<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty, nullptr);
    PaintWrapper paintWrapper(nullptr, geometryNode, radioPaintProperty);
    auto radioModifier = AceType::MakeRefPtr<RadioModifier>();
    RadioPaintMethod radioPaintMethod(radioModifier);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(5);
    radioPaintMethod.radioModifier_->enabled_ = AceType::MakeRefPtr<PropertyBool>(false);
    radioPaintMethod.radioModifier_->uiStatus_ =
        AceType::MakeRefPtr<PropertyInt>(static_cast<int32_t>(UIStatus::SELECTED));
    radioPaintMethod.radioModifier_->PaintRadio(canvas, false, CONTENT_SIZE, CONTENT_OFFSET);
    radioPaintMethod.radioModifier_->enabled_ = AceType::MakeRefPtr<PropertyBool>(true);
    radioPaintMethod.radioModifier_->uiStatus_ =
        AceType::MakeRefPtr<PropertyInt>(static_cast<int32_t>(UIStatus::UNSELECTED));
}

/**
 * @tc.name: RadioPaintMethodTest005
 * @tc.desc: Test Radio UpdateAnimatableProperty and SetBoardColor.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTwoTestNg, RadioPaintMethodTest005, TestSize.Level1)
{
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::RADIO_ETS_TAG, 0, []() { return AceType::MakeRefPtr<RadioPattern>(); });
    auto radioModifier = AceType::MakeRefPtr<RadioModifier>();
    radioModifier->hoverColor_ = Color::RED;
    radioModifier->clickEffectColor_ = Color::BLUE;
    radioModifier->touchHoverType_ = TouchHoverAnimationType::HOVER;
    radioModifier->UpdateAnimatableProperty(frameNode);
    radioModifier->animateTouchHoverColor_ =
        AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(Color::TRANSPARENT));
    radioModifier->touchHoverType_ = TouchHoverAnimationType::PRESS_TO_HOVER;
    radioModifier->UpdateAnimatableProperty(frameNode);
    EXPECT_EQ(radioModifier->animateTouchHoverColor_->Get(), LinearColor(Color::RED));
    radioModifier->touchHoverType_ = TouchHoverAnimationType::NONE;
    radioModifier->UpdateAnimatableProperty(frameNode);
    EXPECT_EQ(radioModifier->animateTouchHoverColor_->Get(), LinearColor(Color::RED.BlendOpacity(0)));
    radioModifier->touchHoverType_ = TouchHoverAnimationType::HOVER_TO_PRESS;
    radioModifier->UpdateAnimatableProperty(frameNode);
    EXPECT_EQ(radioModifier->animateTouchHoverColor_->Get(), LinearColor(Color::BLUE));
    radioModifier->touchHoverType_ = TouchHoverAnimationType::PRESS;
    radioModifier->UpdateAnimatableProperty(frameNode);
    EXPECT_EQ(radioModifier->animateTouchHoverColor_->Get(), LinearColor(Color::BLUE));

    /**
     * @tc.cases: case. cover branch default touchHoverType_.
     */
    radioModifier->touchHoverType_ = INVALID_TOUCH_HOVER_ANIMARION_TYPE;
    radioModifier->UpdateAnimatableProperty(frameNode);
    EXPECT_EQ(radioModifier->animateTouchHoverColor_->Get(), LinearColor(Color::BLUE));
}

/**
 * @tc.name: RadioPaintMethodTest006
 * @tc.desc: Test Radio UpdateIsOnAnimatableProperty.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTwoTestNg, RadioPaintMethodTest006, TestSize.Level1)
{
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::RADIO_ETS_TAG, 0, []() { return AceType::MakeRefPtr<RadioPattern>(); });
    auto radioModifier = AceType::MakeRefPtr<RadioModifier>();
    radioModifier->isOnAnimationFlag_->Set(true);
    radioModifier->UpdateIsOnAnimatableProperty(true, frameNode);
    EXPECT_EQ(radioModifier->pointScale_->Get(), 0.5);
    EXPECT_EQ(radioModifier->ringPointScale_->Get(), 0);
    radioModifier->isOnAnimationFlag_->Set(false);
    radioModifier->UpdateIsOnAnimatableProperty(true, frameNode);
    EXPECT_EQ(radioModifier->pointScale_->Get(), 0);
    EXPECT_EQ(radioModifier->ringPointScale_->Get(), 1);
}

/**
 * @tc.name: RadioPaintMethodTest007
 * @tc.desc: Test Radio PaintMethod UpdateContentModifier.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTwoTestNg, RadioPaintMethodTest007, TestSize.Level1)
{
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::RADIO_ETS_TAG, 0, []() { return AceType::MakeRefPtr<RadioPattern>(); });
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);
    auto radioPaintProperty = AceType::MakeRefPtr<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty, nullptr);
    PaintWrapper paintWrapper(frameNode->GetRenderContext(), geometryNode, radioPaintProperty);
    auto radioModifier = AceType::MakeRefPtr<RadioModifier>();
    RadioPaintMethod radioPaintMethod(radioModifier);

    radioPaintMethod.radioModifier_->SetIsCheck(true);
    radioPaintMethod.isFirstCreated_ = true;
    radioPaintMethod.UpdateContentModifier(&paintWrapper);
    EXPECT_EQ(radioPaintMethod.radioModifier_->uiStatus_->Get(), static_cast<int32_t>(UIStatus::SELECTED));
    radioPaintMethod.radioModifier_->SetIsCheck(true);
    radioPaintMethod.isFirstCreated_ = false;
    radioPaintMethod.UpdateContentModifier(&paintWrapper);
    EXPECT_EQ(radioPaintMethod.radioModifier_->uiStatus_->Get(), static_cast<int32_t>(UIStatus::UNSELECTED));

    auto paintProperty = AccessibilityManager::DynamicCast<RadioPaintProperty>(paintWrapper.GetPaintProperty());
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateRadioCheck(true);
    radioPaintMethod.UpdateContentModifier(&paintWrapper);
    EXPECT_EQ(radioPaintMethod.radioModifier_->uiStatus_->Get(), static_cast<int32_t>(UIStatus::SELECTED));
}

/**
 * @tc.name: RadioPaintMethodTest008
 * @tc.desc: Test Radio PaintMethod PaintIndicator.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTwoTestNg, RadioPaintMethodTest008, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);
    auto radioPaintProperty = AceType::MakeRefPtr<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty, nullptr);
    PaintWrapper paintWrapper(nullptr, geometryNode, radioPaintProperty);
    auto radioModifier = AceType::MakeRefPtr<RadioModifier>();
    RadioPaintMethod radioPaintMethod(radioModifier);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(5);
    radioPaintMethod.radioModifier_->enabled_ = AceType::MakeRefPtr<PropertyBool>(true);
    radioPaintMethod.radioModifier_->uiStatus_ =
        AceType::MakeRefPtr<PropertyInt>(static_cast<int32_t>(UIStatus::SELECTED));
    radioPaintMethod.radioModifier_->PaintIndicator(canvas, false, CONTENT_SIZE, CONTENT_OFFSET);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: RadioPaintMethodTest009
 * @tc.desc: Test Radio PaintMethod PaintIndicator.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTwoTestNg, RadioPaintMethodTest009, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);
    auto radioPaintProperty = AceType::MakeRefPtr<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty, nullptr);
    PaintWrapper paintWrapper(nullptr, geometryNode, radioPaintProperty);
    auto radioModifier = AceType::MakeRefPtr<RadioModifier>();
    RadioPaintMethod radioPaintMethod(radioModifier);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(5);
    radioPaintMethod.radioModifier_->enabled_ = AceType::MakeRefPtr<PropertyBool>(true);
    radioPaintMethod.radioModifier_->uiStatus_ =
        AceType::MakeRefPtr<PropertyInt>(static_cast<int32_t>(UIStatus::UNSELECTED));
    radioPaintMethod.radioModifier_->PaintIndicator(canvas, false, CONTENT_SIZE, CONTENT_OFFSET);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: RadioPaintMethodTest010
 * @tc.desc: Test Radio UpdateIndicatorAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTwoTestNg, RadioPaintMethodTest010, TestSize.Level1)
{
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::RADIO_ETS_TAG, 0, []() { return AceType::MakeRefPtr<RadioPattern>(); });
    int32_t settingApiVersion = 12;
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    auto radioModifier = AceType::MakeRefPtr<RadioModifier>();
    radioModifier->isOnAnimationFlag_->Set(true);
    radioModifier->UpdateIndicatorAnimation(true, frameNode);
    EXPECT_EQ(radioModifier->opacityScale_->Get(), 1);
    EXPECT_EQ(radioModifier->borderOpacityScale_->Get(), 0);
    radioModifier->isOnAnimationFlag_->Set(false);
    radioModifier->UpdateIndicatorAnimation(false, frameNode);
    EXPECT_EQ(radioModifier->opacityScale_->Get(), 0);
    EXPECT_EQ(radioModifier->borderOpacityScale_->Get(), 1);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: RadioPaintMethodTest011
 * @tc.desc: Test Radio PaintMethod DrawFocusBoard.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTwoTestNg, RadioPaintMethodTest011, TestSize.Level1)
{
    int32_t settingApiVersion = 11;
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(settingApiVersion);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);
    auto radioPaintProperty = AceType::MakeRefPtr<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty, nullptr);
    PaintWrapper paintWrapper(nullptr, geometryNode, radioPaintProperty);
    auto radioModifier = AceType::MakeRefPtr<RadioModifier>();
    RadioPaintMethod radioPaintMethod(radioModifier);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    radioModifier->SetIsFocused(true);
    radioPaintMethod.radioModifier_->DrawFocusBoard(canvas, CONTENT_SIZE, CONTENT_OFFSET);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: RadioPaintMethodTest012
 * @tc.desc: Test Radio PaintMethod DrawFocusBoard.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTwoTestNg, RadioPaintMethodTest012, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(settingApiVersion);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);
    auto radioPaintProperty = AceType::MakeRefPtr<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty, nullptr);
    PaintWrapper paintWrapper(nullptr, geometryNode, radioPaintProperty);
    auto radioModifier = AceType::MakeRefPtr<RadioModifier>();
    RadioPaintMethod radioPaintMethod(radioModifier);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    radioPaintMethod.radioModifier_->enabled_ = AceType::MakeRefPtr<PropertyBool>(true);
    radioModifier->SetIsFocused(true);
    radioPaintMethod.radioModifier_->DrawFocusBoard(canvas, CONTENT_SIZE, CONTENT_OFFSET);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: RadioPatternTest025
 * @tc.desc: Test Radio Events.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTwoTestNg, RadioPatternTest025, TestSize.Level1)
{
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();

    auto radioPattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(radioPattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    auto gesture = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gesture, nullptr);
    /**
     * fire click event
     */
    gesture->ActClick();
    /**
     * fire touch event
     */
    auto touchCallback = [](TouchEventInfo& info) {};
    auto touchEvent = AceType::MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    gesture->AddTouchEvent(touchEvent);
    auto touchEventActuator = gesture->touchEventActuator_;
    ASSERT_NE(touchEventActuator, nullptr);
    auto events = touchEventActuator->touchEvents_;
    TouchEventInfo info("onTouch");
    TouchLocationInfo touchInfo1(1);
    touchInfo1.SetTouchType(TouchType::DOWN);
    info.AddTouchLocationInfo(std::move(touchInfo1));
    EXPECT_NE(events.size(), 0);
    for (auto event : events) {
        event->callback_(info);
    }
    TouchEventInfo info2("onTouch");
    TouchLocationInfo touchInfo2(1);
    touchInfo2.SetTouchType(TouchType::UP);
    info2.AddTouchLocationInfo(std::move(touchInfo2));
    EXPECT_NE(events.size(), 0);
    for (auto event : events) {
        event->callback_(info2);
    }
    /**
     * fire mouse event
     */
    auto eventHub = frameNode->GetEventHub<RadioEventHub>();
    auto inputHub = eventHub->GetOrCreateInputEventHub();
    auto hoverEventActuator = inputHub->hoverEventActuator_;
    ASSERT_NE(hoverEventActuator, nullptr);
    auto mouseEvents = hoverEventActuator->inputEvents_;
    ASSERT_NE(mouseEvents.size(), 0);
    for (const auto& callback : mouseEvents) {
        (*callback)(false);
    }
}

/**
 * @tc.name: RadioPatternTest026
 * @tc.desc: Test Radio OnDetachFromFrameNode.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTwoTestNg, RadioPatternTest026, TestSize.Level1)
{
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto stageManager = AceType::MakeRefPtr<StageManager>(frameNode);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->stageManager_ = stageManager;

    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnDetachFromFrameNode(AceType::RawPtr(frameNode));
}

/**
 * @tc.name: RadioPatternTest027
 * @tc.desc: Test Radio onModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTwoTestNg, RadioPatternTest027, TestSize.Level1)
{
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto stageManager = AceType::MakeRefPtr<StageManager>(frameNode);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->stageManager_ = stageManager;
    frameNode->MarkModifyDone();

    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<RadioPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    pattern->SetPreGroup(GROUP_NAME);
    paintProperty->UpdateRadioCheck(true);
    frameNode->MarkModifyDone();
    pattern->SetPreGroup(GROUP_NAME_CHANGE);
    paintProperty->UpdateRadioCheck(false);
    frameNode->MarkModifyDone();
}

/**
 * @tc.name: RadioEventHubChangeEventTest001
 * @tc.desc: Set Radio value into RadioEventHub and get it.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTwoTestNg, RadioEventHubChangeEventTest001, TestSize.Level1)
{
    RadioModelNG radioModelNG;
    radioModelNG.Create(std::nullopt, std::nullopt, std::nullopt);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::RadioEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto onChange = [](const bool check) { EXPECT_TRUE(check); };
    radioModelNG.SetOnChangeEvent(onChange);
    eventHub->SetOnChangeEvent(std::move(onChange));
    eventHub->UpdateChangeEvent(true);
}

/**
 * @tc.name: RadioPatternTest028
 * @tc.desc: Test the distributed capability of Radio.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTwoTestNg, RadioPatternTest028, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Radio node
     */
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();

    /**
     * @tc.steps: step2. Get pattern .
     * @tc.expected: Function ProvideRestoreInfo is called.
     */
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    auto radioPaintProperty = pattern->GetPaintProperty<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty, nullptr);
    radioPaintProperty->UpdateRadioCheck(false);
    std::string ret = pattern->ProvideRestoreInfo();
    EXPECT_TRUE(ret == R"({"checked":false})");

    /**
     * @tc.steps: step3. Function OnRestoreInfo is called.
     * @tc.expected: Passing invalid & valid JSON format.
     */
    std::string restoreInfo_ = R"({"checked":true})";
    pattern->OnRestoreInfo(restoreInfo_);
    EXPECT_TRUE(radioPaintProperty->GetRadioCheckValue(false));
    restoreInfo_ = "invalid_json_string";
    pattern->OnRestoreInfo(restoreInfo_);
    ASSERT_NE(radioPaintProperty, nullptr);
    EXPECT_TRUE(radioPaintProperty->GetRadioCheckValue(false));
}

/**
 * @tc.name: RadioPatternTest029
 * @tc.desc: Radio test Select and ClearSelection.
 */
HWTEST_F(RadioTwoTestNg, RadioPatternTest029, TestSize.Level1)
{
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->preCheck_ = false;
    pattern->SetAccessibilityAction();

    auto accessibilityProperty = frameNode->GetAccessibilityProperty<RadioAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_TRUE(accessibilityProperty->ActActionSelect());

    bool isSelected = true;
    pattern->preCheck_ = false;
    pattern->UpdateSelectStatus(isSelected);
    EXPECT_TRUE(accessibilityProperty->ActActionClearSelection());
}

RadioBuilderFunc RadioTwoTestNg::RadioBuilder()
{
    return []() {
        ColumnModelNG colModel;
        colModel.Create(Dimension(0), nullptr, "");
        ViewAbstract::SetWidth(CalcLength(10.f));
        ViewAbstract::SetHeight(CalcLength(10.f));
    };
}

/**
 * @tc.name: RadioPatternTest030
 * @tc.desc: Radio test SetBuilder.
 */
HWTEST_F(RadioTwoTestNg, RadioPatternTest030, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    auto radioFunc = RadioBuilder();
    radioModelNG.SetBuilder(std::move(radioFunc));
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(pattern->builder_, nullptr);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: RadioPatternTest031
 * @tc.desc: Radio test CreatechildNode.
 */
HWTEST_F(RadioTwoTestNg, RadioPatternTest031, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    auto host = pattern->GetHost();
    pattern->OnModifyDone();
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: RadioPatternTest032
 * @tc.desc: SetRadioChecked and get value
 * @tc.type: FUNC
 */
HWTEST_F(RadioTwoTestNg, RadioPatternTest032, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Radio node
     */
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. Set parameters to pattern radioChecked
     */
    pattern->SetRadioChecked(true);
    /**
     * @tc.steps: step3. Get paint property
     * @tc.expected: Check the Radio property value
     */

    auto radioPaintProperty = frameNode->GetPaintProperty<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty, nullptr);
    bool isChecked = false;
    if (radioPaintProperty->HasRadioCheck()) {
        isChecked = radioPaintProperty->GetRadioCheckValue();
    } else {
        isChecked = false;
    }
    EXPECT_EQ(isChecked, true);
}

/**
 * @tc.name: RadioPatternTest033
 * @tc.desc: SetRadioChecked and get value
 * @tc.type: FUNC
 */
HWTEST_F(RadioTwoTestNg, RadioPatternTest033, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Radio node
     */
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. Set parameters to pattern radioChecked
     */
    pattern->SetRadioChecked(false);
    /**
     * @tc.steps: step3. Get paint property
     * @tc.expected: Check the Radio property value
     */

    auto radioPaintProperty = frameNode->GetPaintProperty<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty, nullptr);
    bool isChecked = false;
    if (radioPaintProperty->HasRadioCheck()) {
        isChecked = radioPaintProperty->GetRadioCheckValue();
    } else {
        isChecked = false;
    }
    EXPECT_EQ(isChecked, false);
}

/**
 * @tc.name: RadioPatternTest034
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(RadioTwoTestNg, RadioPatternTest034, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Radio node
     */
    RadioModelNG radioModelNG;
    radioModelNG.Create(VALUE, GROUP_NAME, INDICATOR_TYPE_TICK);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetRadioChecked(true);
    auto eventHub = frameNode->GetEventHub<NG::RadioEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetValue(VALUE);
    auto node = [](RadioConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(VALUE, config.value_);
                EXPECT_EQ(true, config.checked_);
                return nullptr;
            };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: RadioPatternTest035
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(RadioTwoTestNg, RadioPatternTest035, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Radio node
     */
    RadioModelNG radioModelNG;
    radioModelNG.Create(VALUE, GROUP_NAME, INDICATOR_TYPE_TICK);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetRadioChecked(false);
    auto eventHub = frameNode->GetEventHub<NG::RadioEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetValue(VALUE);

    auto node = [](RadioConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(VALUE, config.value_);
                EXPECT_EQ(false, config.checked_);
                return nullptr;
            };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: RadioPatternTest036
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(RadioTwoTestNg, RadioPatternTest036, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Radio node
     */
    RadioModelNG radioModelNG;
    radioModelNG.Create("", GROUP_NAME, INDICATOR_TYPE_TICK);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetRadioChecked(false);

    auto node = [](RadioConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ("", config.value_);
                EXPECT_EQ(false, config.checked_);
                return nullptr;
            };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: RadioPatternTest037
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(RadioTwoTestNg, RadioPatternTest037, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Radio node
     */
    RadioModelNG radioModelNG;
    radioModelNG.Create("", GROUP_NAME, INDICATOR_TYPE_TICK);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetRadioChecked(false);
    auto eventHub = frameNode->GetEventHub<NG::RadioEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetValue(VALUE);
    auto node = [](RadioConfiguration config) -> RefPtr<FrameNode> {
                EXPECT_EQ(VALUE, config.value_);
                EXPECT_EQ(false, config.checked_);
                return nullptr;
            };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    pattern->SetBuilderFunc(node);
    pattern->BuildContentModifierNode();
}

/**
 * @tc.name: RadioPatternTest038
 * @tc.desc: Test InitFocusEvent.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTwoTestNg, RadioPatternTest038, TestSize.Level1)
{
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto radioModifier = AceType::MakeRefPtr<RadioModifier>();
    RadioPaintMethod radioPaintMethod(radioModifier);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->InitFocusEvent();
    pattern->AddIsFocusActiveUpdateEvent();
    pattern->OnIsFocusActiveUpdate(true);
    EXPECT_TRUE(radioModifier->isFocused_);
}

/**
 * @tc.name: RadioPatternTest039
 * @tc.desc: Test InitFocusEvent.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTwoTestNg, RadioPatternTest039, TestSize.Level1)
{
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto radioModifier = AceType::MakeRefPtr<RadioModifier>();
    RadioPaintMethod radioPaintMethod(radioModifier);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->InitFocusEvent();
    pattern->RemoveIsFocusActiveUpdateEvent();
    pattern->OnIsFocusActiveUpdate(true);
    EXPECT_TRUE(radioModifier->isFocused_);
    int32_t settingApiVersion = 11;
    AceApplicationInfo::GetInstance().SetApiTargetVersion(settingApiVersion);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);
    auto radioPaintProperty = AceType::MakeRefPtr<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty, nullptr);
    PaintWrapper paintWrapper(nullptr, geometryNode, radioPaintProperty);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    radioModifier->SetIsFocused(true);
    pattern->OnIsFocusActiveUpdate(true);
    radioPaintMethod.radioModifier_->enabled_ = AceType::MakeRefPtr<PropertyBool>(false);
    radioPaintMethod.radioModifier_->uiStatus_ =
        AceType::MakeRefPtr<PropertyInt>(static_cast<int32_t>(UIStatus::UNSELECTED));
    radioPaintMethod.radioModifier_->PaintRadio(canvas, false, CONTENT_SIZE, CONTENT_OFFSET);
}

/**
 * @tc.name: RadioPatternTest040
 * @tc.desc: Test InitFocusEvent.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTwoTestNg, RadioPatternTest040, TestSize.Level1)
{
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto radioModifier = AceType::MakeRefPtr<RadioModifier>();
    RadioPaintMethod radioPaintMethod(radioModifier);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->InitFocusEvent();
    pattern->RemoveIsFocusActiveUpdateEvent();
    pattern->OnIsFocusActiveUpdate(true);
    EXPECT_TRUE(radioModifier->isFocused_);
    int32_t settingApiVersion = 11;
    AceApplicationInfo::GetInstance().SetApiTargetVersion(settingApiVersion);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(CONTENT_SIZE);
    geometryNode->SetContentOffset(CONTENT_OFFSET);
    auto radioPaintProperty = AceType::MakeRefPtr<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty, nullptr);
    PaintWrapper paintWrapper(nullptr, geometryNode, radioPaintProperty);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    radioModifier->SetIsFocused(true);
    pattern->OnIsFocusActiveUpdate(true);
    radioPaintMethod.radioModifier_->enabled_ = AceType::MakeRefPtr<PropertyBool>(true);
    radioPaintMethod.radioModifier_->uiStatus_ =
        AceType::MakeRefPtr<PropertyInt>(static_cast<int32_t>(UIStatus::UNSELECTED));
    radioPaintMethod.radioModifier_->PaintRadio(canvas, false, CONTENT_SIZE, CONTENT_OFFSET);
    radioPaintMethod.radioModifier_->PaintIndicator(canvas, false, CONTENT_SIZE, CONTENT_OFFSET);
}
/**
 * @tc.name: RadioPatternTest041
 * @tc.desc: Test InitFocusEvent.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTwoTestNg, RadioPatternTest041, TestSize.Level1)
{
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto radioModifier = AceType::MakeRefPtr<RadioModifier>();
    RadioPaintMethod radioPaintMethod(radioModifier);
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. Set radio focus and blur
     */
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->SetIsFocusActive(true);
    pattern->HandleFocusEvent();
    pattern->AddIsFocusActiveUpdateEvent();
    pattern->OnIsFocusActiveUpdate(true);
    EXPECT_TRUE(radioModifier->isFocused_);
    pattern->HandleBlurEvent();
    pattern->RemoveIsFocusActiveUpdateEvent();
}

/**
 * @tc.name: RadioPatternTest050
 * @tc.desc: Test Radio OnKeyEvent.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTwoTestNg, RadioPatternTest050, TestSize.Level1)
{
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();

    auto eventHub = frameNode->GetFocusHub();
    ASSERT_NE(eventHub, nullptr);
    /**
     * test event.action != KeyAction::DOWN
     */
    KeyEvent keyEventOne(KeyCode::KEY_FUNCTION, KeyAction::UP);
    EXPECT_FALSE(eventHub->ProcessOnKeyEventInternal(keyEventOne));
    /**
     * test event.action == KeyAction::DOWN and event.code == KeyCode::KEY_A
     */
    KeyEvent keyEventTwo(KeyCode::KEY_A, KeyAction::DOWN);
    EXPECT_FALSE(eventHub->ProcessOnKeyEventInternal(keyEventTwo));
    /**
     * test event.action == KeyAction::DOWN and event.code == KeyCode::KEY_FUNCTION
     */
    KeyEvent keyEventThr(KeyCode::KEY_FUNCTION, KeyAction::DOWN);
    EXPECT_TRUE(eventHub->ProcessOnKeyEventInternal(keyEventThr));
}

/**
 * @tc.name: RadioPatternTest051
 * @tc.desc: Test UpdateGroupCheckStatus.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTwoTestNg, RadioPatternTest051, TestSize.Level1)
{
    /**
     * @tc.steps: step1. MockContainer.apiTargetVersion_ = VERSION_TWELVE.
     */
    MockContainer::SetUp();
    MockContainer::Current()->SetApiTargetVersion(VERSION_TWELVE);

    /**
     * @tc.steps: Get Radio pattern object and get
     */
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);
    auto radioPaintProperty = frameNode->GetPaintProperty<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty, nullptr);
    EXPECT_EQ(radioPaintProperty->GetRadioCheckValue(), CHECKED);

    /**
     * @tc.expected: Function UpdateUncheckStatus is called.
     */
    auto pageEventHub = AceType::MakeRefPtr<NG::PageEventHub>();
    auto groupManager = pageEventHub->GetGroupManager();
    pattern->isFirstCreated_ = false;
    pattern->UpdateGroupCheckStatus(frameNode, groupManager, true);
    pattern->UpdateUncheckStatus(frameNode);
    EXPECT_FALSE(radioPaintProperty->GetRadioCheckValue());
    MockContainer::TearDown();
}

/**
 * @tc.name: RadioPatternTest052
 * @tc.desc: Test UpdateUncheckStatus.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTwoTestNg, RadioPatternTest052, TestSize.Level1)
{
    /**
     * @tc.steps: MockContainer.apiTargetVersion_ = VERSION_TWELVE.
     * @tc.steps: set radio theme
     */
    MockContainer::SetUp();
    MockContainer::Current()->SetApiTargetVersion(VERSION_TWELVE);

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        auto radioTheme = AceType::MakeRefPtr<RadioTheme>();
        radioTheme->showCircleDial_ = true;
        return radioTheme;
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);

    /**
     * @tc.steps: Get Radio pattern object and get
     */
    RadioModelNG radioModelNG;
    radioModelNG.Create(NAME, GROUP_NAME, INDICATOR_TYPE_TICK);
    radioModelNG.SetChecked(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);

    auto radioPaintProperty = frameNode->GetPaintProperty<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty, nullptr);
    EXPECT_EQ(radioPaintProperty->GetRadioCheckValue(), CHECKED);

    /**
     * @tc.expected: Function UpdateGroupCheckStatus is called.
     */
    auto pageEventHub = AceType::MakeRefPtr<NG::PageEventHub>();
    auto groupManager = pageEventHub->GetGroupManager();
    pattern->isFirstCreated_ = false;
    pattern->UpdateGroupCheckStatus(frameNode, groupManager, true);
    pattern->UpdateUncheckStatus(frameNode);
    EXPECT_FALSE(radioPaintProperty->GetRadioCheckValue());
    MockContainer::TearDown();
}

/**
 * @tc.name: ColorTypeToString
 * @tc.desc: Test RadioModelNG ColorTypeToString function.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTwoTestNg, ColorTypeToString, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Define test cases for all RadioColorType values and an unknown value.
     * @tc.expected: step1. Test cases cover all possible enum values and edge case.
     */
    std::vector<std::pair<RadioColorType, std::string>> types = {
        { RadioColorType::CHECKED_BACKGROUND_COLOR, "CheckedBackgroundColor" },
        { RadioColorType::UNCHECKED_BORDER_COLOR, "UncheckedBorderColor" },
        { RadioColorType::INDICATOR_COLOR, "IndicatorColor" },
        { static_cast<RadioColorType>(999), "" }
    };

    /**
     * @tc.steps: step2. Iterate through test cases and verify string conversion.
     * @tc.expected: step2. All enum values are converted to their correct string representations.
     */
    for (const auto& [type, expected] : types) {
        auto result = RadioModelNG::ColorTypeToString(type);
        EXPECT_EQ(result, expected);
    }
}

/**
 * @tc.name: MeasureContentTest001
 * @tc.desc: Test Radio MeasureContent.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTwoTestNg, MeasureContentTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set widthLayoutPolicy_ and heightLayoutPolicy_ to MATCH_PARENT.
     * @tc.expected: ret is equal to TEST_SIZE_100.
     */
    RadioModelNG radioModelNG;
    radioModelNG.Create(std::nullopt, std::nullopt, std::nullopt);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(frameNode, nullptr, AccessibilityManager::MakeRefPtr<LayoutProperty>());
    RadioLayoutAlgorithm radioLayoutAlgorithm;
    LayoutConstraintF contentConstraint;
    contentConstraint.parentIdealSize.SetSize(TEST_SIZE_100_200);
    auto layoutProperty = layoutWrapper.GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    LayoutPolicyProperty layoutPolicyProperty;
    layoutPolicyProperty.widthLayoutPolicy_ = LayoutCalPolicy::MATCH_PARENT;
    layoutPolicyProperty.heightLayoutPolicy_ = LayoutCalPolicy::MATCH_PARENT;
    layoutProperty->layoutPolicy_ = layoutPolicyProperty;
    auto ret = radioLayoutAlgorithm.MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_EQ(ret, TEST_SIZE_100);
}

/**
 * @tc.name: MeasureContentTest002
 * @tc.desc: Test Radio MeasureContent.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTwoTestNg, MeasureContentTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set widthLayoutPolicy_ and heightLayoutPolicy_ to FIX_AT_IDEAL_SIZE.
     * @tc.expected: ret is equal to TEST_SIZE_100.
     */
    RadioModelNG radioModelNG;
    radioModelNG.Create(std::nullopt, std::nullopt, std::nullopt);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(frameNode, nullptr, AccessibilityManager::MakeRefPtr<LayoutProperty>());

    /**
     * @tc.steps: create mock theme manager, set radioTheme
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    auto pipeline = MockPipelineContext::GetCurrent();
    pipeline->SetThemeManager(themeManager);
    auto radioTheme = AceType::MakeRefPtr<RadioTheme>();
    radioTheme->width_ = Dimension(TEST_HEIGHT_60);
    radioTheme->defaultPaddingSize_ = Dimension(TEST_HORIZONPADDING);
    radioTheme->hotZoneHorizontalPadding_ = Dimension(TEST_HORIZONPADDING);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(radioTheme));

    RadioLayoutAlgorithm radioLayoutAlgorithm;
    LayoutConstraintF contentConstraint;
    contentConstraint.parentIdealSize.SetSize(TEST_SIZE_100_200);
    auto layoutProperty = layoutWrapper.GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    LayoutPolicyProperty layoutPolicyProperty;
    layoutPolicyProperty.widthLayoutPolicy_ = LayoutCalPolicy::FIX_AT_IDEAL_SIZE;
    layoutPolicyProperty.heightLayoutPolicy_ = LayoutCalPolicy::FIX_AT_IDEAL_SIZE;
    layoutProperty->layoutPolicy_ = layoutPolicyProperty;
    auto ret = radioLayoutAlgorithm.MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_EQ(ret, TEST_SIZE_50);

    layoutPolicyProperty.widthLayoutPolicy_ = LayoutCalPolicy::FIX_AT_IDEAL_SIZE;
    layoutPolicyProperty.heightLayoutPolicy_ = LayoutCalPolicy::NO_MATCH;
    layoutProperty->layoutPolicy_ = layoutPolicyProperty;
    ret = radioLayoutAlgorithm.MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_EQ(ret, TEST_SIZE_50);

    contentConstraint.selfIdealSize.SetSize(TEST_SIZE_100_200);
    ret = radioLayoutAlgorithm.MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_EQ(ret, TEST_SIZE_200);
}

/**
 * @tc.name: MeasureContentTest003
 * @tc.desc: Test Radio MeasureContent.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTwoTestNg, MeasureContentTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set widthLayoutPolicy_ and heightLayoutPolicy_ to FIX_AT_IDEAL_SIZE.
     * @tc.expected: ret is equal to TEST_SIZE_100.
     */
    RadioModelNG radioModelNG;
    radioModelNG.Create(std::nullopt, std::nullopt, std::nullopt);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(frameNode, nullptr, AccessibilityManager::MakeRefPtr<LayoutProperty>());

    /**
     * @tc.steps: create mock theme manager, set radioTheme
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    auto pipeline = MockPipelineContext::GetCurrent();
    pipeline->SetThemeManager(themeManager);
    auto radioTheme = AceType::MakeRefPtr<RadioTheme>();
    radioTheme->width_ = Dimension(TEST_HEIGHT_60);
    radioTheme->defaultPaddingSize_ = Dimension(TEST_HORIZONPADDING);
    radioTheme->hotZoneHorizontalPadding_ = Dimension(TEST_HORIZONPADDING);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(radioTheme));

    RadioLayoutAlgorithm radioLayoutAlgorithm;
    LayoutConstraintF contentConstraint;
    contentConstraint.parentIdealSize.SetSize(TEST_SIZE_100_200);
    auto layoutProperty = layoutWrapper.GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    LayoutPolicyProperty layoutPolicyProperty;
    layoutPolicyProperty.widthLayoutPolicy_ = LayoutCalPolicy::NO_MATCH;
    layoutPolicyProperty.heightLayoutPolicy_ = LayoutCalPolicy::FIX_AT_IDEAL_SIZE;
    layoutProperty->layoutPolicy_ = layoutPolicyProperty;
    auto ret = radioLayoutAlgorithm.MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_EQ(ret, TEST_SIZE_50);

    contentConstraint.selfIdealSize.SetSize(TEST_SIZE_100_200);
    ret = radioLayoutAlgorithm.MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_EQ(ret, TEST_SIZE_100);

    layoutPolicyProperty.widthLayoutPolicy_ = LayoutCalPolicy::NO_MATCH;
    layoutPolicyProperty.heightLayoutPolicy_ = LayoutCalPolicy::NO_MATCH;
    layoutProperty->layoutPolicy_ = layoutPolicyProperty;
    ret = radioLayoutAlgorithm.LayoutPolicyIsFixAtIdelSize(contentConstraint, layoutPolicyProperty);
    EXPECT_EQ(ret, TEST_SIZE_0);
}

/**
 * @tc.name: MeasureContentTest004
 * @tc.desc: Test Radio MeasureContent.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTwoTestNg, MeasureContentTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set widthLayoutPolicy_ and heightLayoutPolicy_ to MATCH_PARENT.
     * @tc.expected: ret is equal to TEST_SIZE_100.
     */
    RadioModelNG radioModelNG;
    radioModelNG.Create(std::nullopt, std::nullopt, std::nullopt);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(frameNode, nullptr, AccessibilityManager::MakeRefPtr<LayoutProperty>());

    /**
     * @tc.steps: create mock theme manager, set radioTheme
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    auto pipeline = MockPipelineContext::GetCurrent();
    pipeline->SetThemeManager(themeManager);
    auto radioTheme = AceType::MakeRefPtr<RadioTheme>();
    radioTheme->width_ = Dimension(TEST_HEIGHT_60);
    radioTheme->defaultPaddingSize_ = Dimension(TEST_HORIZONPADDING);
    radioTheme->hotZoneHorizontalPadding_ = Dimension(TEST_HORIZONPADDING);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(radioTheme));

    RadioLayoutAlgorithm radioLayoutAlgorithm;
    LayoutConstraintF contentConstraint;
    contentConstraint.parentIdealSize.SetSize(TEST_SIZE_100_200);
    auto layoutProperty = layoutWrapper.GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    LayoutPolicyProperty layoutPolicyProperty;
    layoutPolicyProperty.widthLayoutPolicy_ = LayoutCalPolicy::WRAP_CONTENT;
    layoutPolicyProperty.heightLayoutPolicy_ = LayoutCalPolicy::WRAP_CONTENT;
    layoutProperty->layoutPolicy_ = layoutPolicyProperty;
    auto ret = radioLayoutAlgorithm.MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_EQ(ret, TEST_SIZE_50);

    layoutPolicyProperty.widthLayoutPolicy_ = LayoutCalPolicy::WRAP_CONTENT;
    layoutPolicyProperty.heightLayoutPolicy_ = LayoutCalPolicy::NO_MATCH;
    layoutProperty->layoutPolicy_ = layoutPolicyProperty;
    ret = radioLayoutAlgorithm.MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_EQ(ret, TEST_SIZE_50);

    contentConstraint.selfIdealSize.SetSize(TEST_SIZE_60);
    ret = radioLayoutAlgorithm.MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_EQ(ret, TEST_SIZE_60);
}

/**
 * @tc.name: MeasureContentTest005
 * @tc.desc: Test Radio MeasureContent.
 * @tc.type: FUNC
 */
HWTEST_F(RadioTwoTestNg, MeasureContentTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set widthLayoutPolicy_ and heightLayoutPolicy_ to MATCH_PARENT.
     * @tc.expected: ret is equal to TEST_SIZE_100.
     */
    RadioModelNG radioModelNG;
    radioModelNG.Create(std::nullopt, std::nullopt, std::nullopt);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(frameNode, nullptr, AccessibilityManager::MakeRefPtr<LayoutProperty>());

    /**
     * @tc.steps: create mock theme manager, set radioTheme
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    auto pipeline = MockPipelineContext::GetCurrent();
    pipeline->SetThemeManager(themeManager);
    auto radioTheme = AceType::MakeRefPtr<RadioTheme>();
    radioTheme->width_ = Dimension(TEST_HEIGHT_60);
    radioTheme->defaultPaddingSize_ = Dimension(TEST_HORIZONPADDING);
    radioTheme->hotZoneHorizontalPadding_ = Dimension(TEST_HORIZONPADDING);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(radioTheme));

    RadioLayoutAlgorithm radioLayoutAlgorithm;
    LayoutConstraintF contentConstraint;
    contentConstraint.parentIdealSize.SetSize(TEST_SIZE_100_200);
    auto layoutProperty = layoutWrapper.GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    LayoutPolicyProperty layoutPolicyProperty;
    layoutPolicyProperty.widthLayoutPolicy_ = LayoutCalPolicy::NO_MATCH;
    layoutPolicyProperty.heightLayoutPolicy_ = LayoutCalPolicy::WRAP_CONTENT;
    layoutProperty->layoutPolicy_ = layoutPolicyProperty;
    auto ret = radioLayoutAlgorithm.MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_EQ(ret, TEST_SIZE_50);

    contentConstraint.selfIdealSize.SetSize(TEST_SIZE_60);
    ret = radioLayoutAlgorithm.MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_EQ(ret, TEST_SIZE_60);

    layoutPolicyProperty.widthLayoutPolicy_ = LayoutCalPolicy::NO_MATCH;
    layoutPolicyProperty.heightLayoutPolicy_ = LayoutCalPolicy::NO_MATCH;
    layoutProperty->layoutPolicy_ = layoutPolicyProperty;
    ret = radioLayoutAlgorithm.LayoutPolicyIsFixAtIdelSize(contentConstraint, layoutPolicyProperty);
    EXPECT_EQ(ret, TEST_SIZE_0);
}
} // namespace OHOS::Ace::NG
