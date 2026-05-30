/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include <optional>
#include <string>

#include "gtest/gtest.h"

#define private public
#define protected public

#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/frameworks/core/components_ng/render/mock_render_context.h"

#include "core/common/ace_engine.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_style.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_ng/pattern/sheet/side/sheet_side_object.h"
#include "core/components_ng/pattern/sheet/side/sheet_presentation_side_layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper_node.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr float SHEET_WIDTH = 200.0f;
constexpr float SHEET_MAX_WIDTH = 400.0f;
constexpr float SHEET_HEIGHT = 500.0f;
constexpr float SHEET_MAX_HEIGHT = 800.0f;
} // namespace

class SheetSideObjectTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;

    RefPtr<SheetPresentationPattern> CreateSheetPattern();
    RefPtr<SheetSideObject> CreateSheetObject();
    RefPtr<FrameNode> sheetNode_;
};

void SheetSideObjectTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    auto safeAreaManager = AceType::MakeRefPtr<SafeAreaManager>();
    MockPipelineContext::GetCurrent()->safeAreaManager_ = safeAreaManager;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        if (type == SheetTheme::TypeId()) {
            return AceType::MakeRefPtr<SheetTheme>();
        }
        return nullptr;
    });
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly([](ThemeType type, int32_t) -> RefPtr<Theme> {
        if (type == SheetTheme::TypeId()) {
            return AceType::MakeRefPtr<SheetTheme>();
        }
        return nullptr;
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void SheetSideObjectTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void SheetSideObjectTestNg::SetUp() {}

void SheetSideObjectTestNg::TearDown()
{
    auto container = MockContainer::Current();
    if (container) {
        container->taskExecutor_ = nullptr;
    }
    AceEngine::Get().RemoveContainer(0);
    AceEngine::Get().RemoveContainer(1);
}

RefPtr<SheetPresentationPattern> SheetSideObjectTestNg::CreateSheetPattern()
{
    auto callback = [](const std::string&) {};
    sheetNode_ = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    EXPECT_NE(sheetNode_, nullptr);
    auto sheetPattern = sheetNode_->GetPattern<SheetPresentationPattern>();
    EXPECT_NE(sheetPattern, nullptr);
    sheetPattern->sheetType_ = SheetType::SHEET_SIDE;
    sheetPattern->InitSheetObject();
    return sheetPattern;
}

RefPtr<SheetSideObject> SheetSideObjectTestNg::CreateSheetObject()
{
    auto sheetPattern = CreateSheetPattern();
    EXPECT_NE(sheetPattern, nullptr);
    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    EXPECT_NE(object, nullptr);
    object->sheetWidth_ = SHEET_WIDTH;
    object->sheetMaxWidth_ = SHEET_MAX_WIDTH;
    return object;
}

/**
 * @tc.name: DirtyLayoutProcessMaxWidthPositive
 * @tc.desc: Test DirtyLayoutProcess when algorithm sheetMaxWidth is positive
 * @tc.type: FUNC
 */
HWTEST_F(SheetSideObjectTestNg, DirtyLayoutProcessMaxWidthPositive, TestSize.Level1)
{
    auto object = CreateSheetObject();
    auto algorithm = AceType::MakeRefPtr<SheetPresentationSideLayoutAlgorithm>();
    algorithm->sheetMaxWidth_ = SHEET_MAX_WIDTH;
    algorithm->sheetWidth_ = SHEET_WIDTH;
    algorithm->sheetMaxHeight_ = SHEET_MAX_HEIGHT;
    auto wrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        nullptr, nullptr, nullptr);
    auto layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(algorithm);
    object->DirtyLayoutProcess(layoutAlgorithmWrapper);
    EXPECT_EQ(object->sheetMaxWidth_, SHEET_MAX_WIDTH);
    EXPECT_EQ(object->sheetWidth_, SHEET_WIDTH);
}

/**
 * @tc.name: DirtyLayoutProcessMaxWidthZero
 * @tc.desc: Test DirtyLayoutProcess when algorithm sheetMaxWidth is zero
 * @tc.type: FUNC
 */
HWTEST_F(SheetSideObjectTestNg, DirtyLayoutProcessMaxWidthZero, TestSize.Level1)
{
    auto object = CreateSheetObject();
    auto algorithm = AceType::MakeRefPtr<SheetPresentationSideLayoutAlgorithm>();
    algorithm->sheetMaxWidth_ = 0.0f;
    algorithm->sheetWidth_ = SHEET_WIDTH;
    auto wrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        nullptr, nullptr, nullptr);
    auto layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(algorithm);
    object->DirtyLayoutProcess(layoutAlgorithmWrapper);
    EXPECT_EQ(object->sheetMaxWidth_, SHEET_MAX_WIDTH);
    EXPECT_EQ(object->sheetWidth_, SHEET_WIDTH);
}

/**
 * @tc.name: GetSheetTransitionCurveTest
 * @tc.desc: Test GetSheetTransitionCurve returns non-null curve
 * @tc.type: FUNC
 */
HWTEST_F(SheetSideObjectTestNg, GetSheetTransitionCurveTest, TestSize.Level1)
{
    auto object = CreateSheetObject();
    auto curve = object->GetSheetTransitionCurve(500.0f);
    EXPECT_NE(curve, nullptr);
}

/**
 * @tc.name: GetSheetTransitionFinishEventTransitionIn
 * @tc.desc: Test GetSheetTransitionFinishEvent for transition-in without animation break
 * @tc.type: FUNC
 */
HWTEST_F(SheetSideObjectTestNg, GetSheetTransitionFinishEventTransitionIn, TestSize.Level1)
{
    auto sheetPattern = CreateSheetPattern();
    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    object->BindPattern(AceType::WeakClaim(AceType::RawPtr(sheetPattern)));

    auto event = object->GetSheetTransitionFinishEvent(true);
    ASSERT_NE(event, nullptr);
    sheetPattern->isAnimationBreak_ = false;
    event();
    EXPECT_FALSE(sheetPattern->isAnimationProcess_);
    EXPECT_EQ(object->currentOffset_, 0.0f);
}

/**
 * @tc.name: GetSheetTransitionFinishEventTransitionInBreak
 * @tc.desc: Test GetSheetTransitionFinishEvent for transition-in with animation break
 * @tc.type: FUNC
 */
HWTEST_F(SheetSideObjectTestNg, GetSheetTransitionFinishEventTransitionInBreak, TestSize.Level1)
{
    auto sheetPattern = CreateSheetPattern();
    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    object->BindPattern(AceType::WeakClaim(AceType::RawPtr(sheetPattern)));

    auto event = object->GetSheetTransitionFinishEvent(true);
    ASSERT_NE(event, nullptr);
    sheetPattern->isAnimationBreak_ = true;
    event();
    EXPECT_FALSE(sheetPattern->isAnimationBreak_);
}

/**
 * @tc.name: GetSheetTransitionFinishEventTransitionOut
 * @tc.desc: Test GetSheetTransitionFinishEvent for transition-out
 * @tc.type: FUNC
 */
HWTEST_F(SheetSideObjectTestNg, GetSheetTransitionFinishEventTransitionOut, TestSize.Level1)
{
    auto sheetPattern = CreateSheetPattern();
    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    object->BindPattern(AceType::WeakClaim(AceType::RawPtr(sheetPattern)));

    auto rootNode = FrameNode::CreateFrameNode("root", 0, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    sheetPattern->overlayManager_ = overlayManager;

    auto event = object->GetSheetTransitionFinishEvent(false);
    ASSERT_NE(event, nullptr);
    event();
    EXPECT_FALSE(sheetPattern->isAnimationProcess_);
}

/**
 * @tc.name: GetSheetAnimationEventNonInteractiveEnter
 * @tc.desc: Test GetSheetAnimationEvent for non-interactive enter transition
 * @tc.type: FUNC
 */
HWTEST_F(SheetSideObjectTestNg, GetSheetAnimationEventNonInteractiveEnter, TestSize.Level1)
{
    auto sheetPattern = CreateSheetPattern();
    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    object->BindPattern(AceType::WeakClaim(AceType::RawPtr(sheetPattern)));
    SheetStyle setSheetStyle;
    setSheetStyle.interactive = false;
    sheetNode_->GetLayoutProperty<SheetPresentationProperty>()->UpdateSheetStyle(setSheetStyle);

    auto event = object->GetSheetAnimationEvent(true, 0.0f);
    ASSERT_NE(event, nullptr);
    event();
    SUCCEED();
}

/**
 * @tc.name: GetSheetAnimationEventNonInteractiveExit
 * @tc.desc: Test GetSheetAnimationEvent for non-interactive exit transition
 * @tc.type: FUNC
 */
HWTEST_F(SheetSideObjectTestNg, GetSheetAnimationEventNonInteractiveExit, TestSize.Level1)
{
    auto sheetPattern = CreateSheetPattern();
    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    object->BindPattern(AceType::WeakClaim(AceType::RawPtr(sheetPattern)));
    SheetStyle setSheetStyle;
    setSheetStyle.interactive = false;
    sheetPattern->GetLayoutProperty<SheetPresentationProperty>()->UpdateSheetStyle(setSheetStyle);

    auto event = object->GetSheetAnimationEvent(false, 0.0f);
    ASSERT_NE(event, nullptr);
    event();
    SUCCEED();
}

/**
 * @tc.name: GetSheetAnimationEventInteractive
 * @tc.desc: Test GetSheetAnimationEvent for interactive mode enter transition
 * @tc.type: FUNC
 */
HWTEST_F(SheetSideObjectTestNg, GetSheetAnimationEventInteractive, TestSize.Level1)
{
    auto sheetPattern = CreateSheetPattern();
    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    object->BindPattern(AceType::WeakClaim(AceType::RawPtr(sheetPattern)));
    SheetStyle setSheetStyle;
    setSheetStyle.interactive = true;
    sheetPattern->GetLayoutProperty<SheetPresentationProperty>()->UpdateSheetStyle(setSheetStyle);
    object->CreatePropertyCallback();

    auto event = object->GetSheetAnimationEvent(true, 0.0f);
    ASSERT_NE(event, nullptr);
    EXPECT_NE(sheetPattern->GetProperty(), nullptr);
}

/**
 * @tc.name: ClipSheetNodeTest
 * @tc.desc: Test ClipSheetNode with radius render strategy set
 * @tc.type: FUNC
 */
HWTEST_F(SheetSideObjectTestNg, ClipSheetNodeTest, TestSize.Level1)
{
    auto sheetPattern = CreateSheetPattern();
    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    object->BindPattern(AceType::WeakClaim(AceType::RawPtr(sheetPattern)));
    auto host = sheetPattern->GetHost();
    ASSERT_NE(host, nullptr);
    host->GetGeometryNode()->SetFrameSize(SizeF(SHEET_WIDTH, SHEET_HEIGHT));
    SheetStyle setSheetStyle;
    setSheetStyle.radiusRenderStrategy = RenderStrategy::OFFSCREEN;
    sheetPattern->GetLayoutProperty<SheetPresentationProperty>()->UpdateSheetStyle(setSheetStyle);
    object->ClipSheetNode();
    SUCCEED();
}

/**
 * @tc.name: ClipSheetNodeNoStrategy
 * @tc.desc: Test ClipSheetNode when radius render strategy is empty
 * @tc.type: FUNC
 */
HWTEST_F(SheetSideObjectTestNg, ClipSheetNodeNoStrategy, TestSize.Level1)
{
    auto sheetPattern = CreateSheetPattern();
    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    object->BindPattern(AceType::WeakClaim(AceType::RawPtr(sheetPattern)));
    auto host = sheetPattern->GetHost();
    ASSERT_NE(host, nullptr);
    host->GetGeometryNode()->SetFrameSize(SizeF(SHEET_WIDTH, SHEET_HEIGHT));
    SheetStyle setSheetStyle;
    setSheetStyle.radiusRenderStrategy = std::nullopt;
    sheetPattern->GetLayoutProperty<SheetPresentationProperty>()->UpdateSheetStyle(setSheetStyle);
    object->ClipSheetNode();
    SUCCEED();
}

/**
 * @tc.name: InitAnimationForOverlayTransitionInFirst
 * @tc.desc: Test InitAnimationForOverlay for first transition-in with interactive mode
 * @tc.type: FUNC
 */
HWTEST_F(SheetSideObjectTestNg, InitAnimationForOverlayTransitionInFirst, TestSize.Level1)
{
    auto sheetPattern = CreateSheetPattern();
    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    object->BindPattern(AceType::WeakClaim(AceType::RawPtr(sheetPattern)));

    auto rootNode = FrameNode::CreateFrameNode("root", 0, AceType::MakeRefPtr<RootPattern>());
    sheetNode_->SetParent(rootNode);

    SheetStyle setSheetStyle;
    setSheetStyle.interactive = true;
    sheetNode_->GetLayoutProperty<SheetPresentationProperty>()->UpdateSheetStyle(setSheetStyle);
    object->InitAnimationForOverlay(true, true);
    EXPECT_TRUE(sheetPattern->isAnimationProcess_);
}

/**
 * @tc.name: InitAnimationForOverlayTransitionInNotFirst
 * @tc.desc: Test InitAnimationForOverlay for non-first transition-in with non-interactive mode
 * @tc.type: FUNC
 */
HWTEST_F(SheetSideObjectTestNg, InitAnimationForOverlayTransitionInNotFirst, TestSize.Level1)
{
    auto sheetPattern = CreateSheetPattern();
    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    object->BindPattern(AceType::WeakClaim(AceType::RawPtr(sheetPattern)));

    SheetStyle setSheetStyle;
    setSheetStyle.interactive = false;
    sheetNode_->GetLayoutProperty<SheetPresentationProperty>()->UpdateSheetStyle(setSheetStyle);
    object->InitAnimationForOverlay(true, false);
    SUCCEED();
}

/**
 * @tc.name: InitAnimationForOverlayTransitionOut
 * @tc.desc: Test InitAnimationForOverlay for transition-out with non-interactive mode
 * @tc.type: FUNC
 */
HWTEST_F(SheetSideObjectTestNg, InitAnimationForOverlayTransitionOut, TestSize.Level1)
{
    auto sheetPattern = CreateSheetPattern();
    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    object->BindPattern(AceType::WeakClaim(AceType::RawPtr(sheetPattern)));

    SheetStyle setSheetStyle;
    setSheetStyle.interactive = false;
    sheetPattern->GetLayoutProperty<SheetPresentationProperty>()->UpdateSheetStyle(setSheetStyle);
    object->InitAnimationForOverlay(false, false);
    EXPECT_FALSE(sheetPattern->isAnimationProcess_);
}

/**
 * @tc.name: SetFinishEventForAnimationOptionTransitionIn
 * @tc.desc: Test SetFinishEventForAnimationOption for transition-in with animation break
 * @tc.type: FUNC
 */
HWTEST_F(SheetSideObjectTestNg, SetFinishEventForAnimationOptionTransitionIn, TestSize.Level1)
{
    auto sheetPattern = CreateSheetPattern();
    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    object->BindPattern(AceType::WeakClaim(AceType::RawPtr(sheetPattern)));

    AnimationOption option;
    object->SetFinishEventForAnimationOption(option, true, true);
    auto finishEvent = option.GetOnFinishEvent();
    ASSERT_NE(finishEvent, nullptr);

    auto rootNode = FrameNode::CreateFrameNode("root", 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    sheetPattern->overlayManager_ = overlayManager;
    finishEvent();
    SUCCEED();
}

/**
 * @tc.name: SetFinishEventForAnimationOptionTransitionOut
 * @tc.desc: Test SetFinishEventForAnimationOption for transition-out without animation break
 * @tc.type: FUNC
 */
HWTEST_F(SheetSideObjectTestNg, SetFinishEventForAnimationOptionTransitionOut, TestSize.Level1)
{
    auto sheetPattern = CreateSheetPattern();
    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    object->BindPattern(AceType::WeakClaim(AceType::RawPtr(sheetPattern)));

    AnimationOption option;
    object->SetFinishEventForAnimationOption(option, false, false);

    auto rootNode = FrameNode::CreateFrameNode("root", 2, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    sheetPattern->overlayManager_ = overlayManager;
    auto finishEvent = option.GetOnFinishEvent();
    finishEvent();
    SUCCEED();
}

/**
 * @tc.name: GetAnimationOptionForOverlayTest
 * @tc.desc: Test GetAnimationOptionForOverlay returns option with correct duration
 * @tc.type: FUNC
 */
HWTEST_F(SheetSideObjectTestNg, GetAnimationOptionForOverlayTest, TestSize.Level1)
{
    auto sheetPattern = CreateSheetPattern();
    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    object->BindPattern(AceType::WeakClaim(AceType::RawPtr(sheetPattern)));

    auto option = object->GetAnimationOptionForOverlay(true, true);
    EXPECT_EQ(option.GetDuration(), SHEET_ANIMATION_DURATION);
}

/**
 * @tc.name: TransformTranslateExitTest
 * @tc.desc: Test TransformTranslateExit executes without crash
 * @tc.type: FUNC
 */
HWTEST_F(SheetSideObjectTestNg, TransformTranslateExitTest, TestSize.Level1)
{
    auto object = CreateSheetObject();
    object->TransformTranslateExit();
    SUCCEED();
}

/**
 * @tc.name: GetAnimationPropertyCallForOverlayNonInteractiveEnter
 * @tc.desc: Test GetAnimationPropertyCallForOverlay for non-interactive enter
 * @tc.type: FUNC
 */
HWTEST_F(SheetSideObjectTestNg, GetAnimationPropertyCallForOverlayNonInteractiveEnter, TestSize.Level1)
{
    auto sheetPattern = CreateSheetPattern();
    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    object->BindPattern(AceType::WeakClaim(AceType::RawPtr(sheetPattern)));
    SheetStyle setSheetStyle;
    setSheetStyle.interactive = false;
    sheetPattern->GetLayoutProperty<SheetPresentationProperty>()->UpdateSheetStyle(setSheetStyle);

    auto event = object->GetAnimationPropertyCallForOverlay(true);
    ASSERT_NE(event, nullptr);
    event();
    SUCCEED();
}

/**
 * @tc.name: GetAnimationPropertyCallForOverlayNonInteractiveExit
 * @tc.desc: Test GetAnimationPropertyCallForOverlay for non-interactive exit
 * @tc.type: FUNC
 */
HWTEST_F(SheetSideObjectTestNg, GetAnimationPropertyCallForOverlayNonInteractiveExit, TestSize.Level1)
{
    auto sheetPattern = CreateSheetPattern();
    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    object->BindPattern(AceType::WeakClaim(AceType::RawPtr(sheetPattern)));
    SheetStyle setSheetStyle;
    setSheetStyle.interactive = false;
    sheetPattern->GetLayoutProperty<SheetPresentationProperty>()->UpdateSheetStyle(setSheetStyle);

    auto event = object->GetAnimationPropertyCallForOverlay(false);
    ASSERT_NE(event, nullptr);
    event();
    SUCCEED();
}

/**
 * @tc.name: GetAnimationPropertyCallForOverlayInteractive
 * @tc.desc: Test GetAnimationPropertyCallForOverlay for interactive mode
 * @tc.type: FUNC
 */
HWTEST_F(SheetSideObjectTestNg, GetAnimationPropertyCallForOverlayInteractive, TestSize.Level1)
{
    auto sheetPattern = CreateSheetPattern();
    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    object->BindPattern(AceType::WeakClaim(AceType::RawPtr(sheetPattern)));
    SheetStyle setSheetStyle;
    setSheetStyle.interactive = true;
    sheetPattern->GetLayoutProperty<SheetPresentationProperty>()->UpdateSheetStyle(setSheetStyle);
    object->CreatePropertyCallback();

    auto event = object->GetAnimationPropertyCallForOverlay(true);
    ASSERT_NE(event, nullptr);
    event();
    SUCCEED();
}

/**
 * @tc.name: OnLanguageConfigurationUpdateTest
 * @tc.desc: Test OnLanguageConfigurationUpdate when sheet is shown and not playing transition
 * @tc.type: FUNC
 */
HWTEST_F(SheetSideObjectTestNg, OnLanguageConfigurationUpdateTest, TestSize.Level1)
{
    auto sheetPattern = CreateSheetPattern();
    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    object->BindPattern(AceType::WeakClaim(AceType::RawPtr(sheetPattern)));
    sheetPattern->show_ = true;
    sheetPattern->isPlayTransition_ = false;
    object->OnLanguageConfigurationUpdate();
    SUCCEED();
}

/**
 * @tc.name: GetSheetSafeAreaPaddingTest
 * @tc.desc: Test GetSheetSafeAreaPadding returns default zero padding
 * @tc.type: FUNC
 */
HWTEST_F(SheetSideObjectTestNg, GetSheetSafeAreaPaddingTest, TestSize.Level1)
{
    auto object = CreateSheetObject();
    auto padding = object->GetSheetSafeAreaPadding();
    EXPECT_EQ(padding.left, 0.0f);
    EXPECT_EQ(padding.right, 0.0f);
}

/**
 * @tc.name: HandleDragStartTest
 * @tc.desc: Test HandleDragStart resets currentOffset and sets drag flag
 * @tc.type: FUNC
 */
HWTEST_F(SheetSideObjectTestNg, HandleDragStartTest, TestSize.Level1)
{
    auto sheetPattern = CreateSheetPattern();
    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    object->BindPattern(AceType::WeakClaim(AceType::RawPtr(sheetPattern)));
    object->currentOffset_ = 10.0f;

    object->HandleDragStart();
    EXPECT_EQ(object->currentOffset_, 0.0f);
    EXPECT_TRUE(sheetPattern->isDrag_);
}

/**
 * @tc.name: HandleDragUpdateLTR
 * @tc.desc: Test HandleDragUpdateForLTR with positive delta
 * @tc.type: FUNC
 */
HWTEST_F(SheetSideObjectTestNg, HandleDragUpdateLTR, TestSize.Level1)
{
    auto sheetPattern = CreateSheetPattern();
    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    object->BindPattern(AceType::WeakClaim(AceType::RawPtr(sheetPattern)));
    object->sheetMaxWidth_ = SHEET_MAX_WIDTH;
    object->sheetWidth_ = SHEET_WIDTH;

    GestureEvent info;
    info.mainDelta_ = 50.0f;
    object->HandleDragUpdate(info);
    EXPECT_EQ(object->currentOffset_, 50.0f);
}

/**
 * @tc.name: HandleDragUpdateLTRNegative
 * @tc.desc: Test HandleDragUpdateForLTR with negative delta clamped to zero
 * @tc.type: FUNC
 */
HWTEST_F(SheetSideObjectTestNg, HandleDragUpdateLTRNegative, TestSize.Level1)
{
    auto sheetPattern = CreateSheetPattern();
    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    object->BindPattern(AceType::WeakClaim(AceType::RawPtr(sheetPattern)));
    object->sheetMaxWidth_ = SHEET_MAX_WIDTH;
    object->sheetWidth_ = SHEET_WIDTH;
    object->currentOffset_ = 0.0f;

    GestureEvent info;
    info.mainDelta_ = -10.0f;
    object->HandleDragUpdate(info);
    EXPECT_EQ(object->currentOffset_, 0.0f);
}

/**
 * @tc.name: HandleDragUpdateLTRNearEqual
 * @tc.desc: Test HandleDragUpdateForLTR with zero delta
 * @tc.type: FUNC
 */
HWTEST_F(SheetSideObjectTestNg, HandleDragUpdateLTRNearEqual, TestSize.Level1)
{
    auto sheetPattern = CreateSheetPattern();
    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    object->BindPattern(AceType::WeakClaim(AceType::RawPtr(sheetPattern)));
    object->sheetMaxWidth_ = SHEET_MAX_WIDTH;
    object->sheetWidth_ = SHEET_WIDTH;
    object->currentOffset_ = 0.0f;

    GestureEvent info;
    info.mainDelta_ = 0.0f;
    object->HandleDragUpdate(info);
    EXPECT_EQ(object->currentOffset_, 0.0f);
}

/**
 * @tc.name: HandleDragUpdateRTL
 * @tc.desc: Test HandleDragUpdateForRTL with negative delta
 * @tc.type: FUNC
 */
HWTEST_F(SheetSideObjectTestNg, HandleDragUpdateRTL, TestSize.Level1)
{
    auto sheetPattern = CreateSheetPattern();
    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    object->BindPattern(AceType::WeakClaim(AceType::RawPtr(sheetPattern)));
    object->sheetMaxWidth_ = SHEET_MAX_WIDTH;
    object->sheetWidth_ = SHEET_WIDTH;

    GestureEvent info;
    info.mainDelta_ = -50.0f;
    object->HandleDragUpdateForRTL(info);
    EXPECT_EQ(object->currentOffset_, -50.0f);
}

/**
 * @tc.name: HandleDragUpdateRTLPositive
 * @tc.desc: Test HandleDragUpdateForRTL with positive delta clamped to zero
 * @tc.type: FUNC
 */
HWTEST_F(SheetSideObjectTestNg, HandleDragUpdateRTLPositive, TestSize.Level1)
{
    auto sheetPattern = CreateSheetPattern();
    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    object->BindPattern(AceType::WeakClaim(AceType::RawPtr(sheetPattern)));
    object->sheetMaxWidth_ = SHEET_MAX_WIDTH;
    object->sheetWidth_ = SHEET_WIDTH;
    object->currentOffset_ = 0.0f;

    GestureEvent info;
    info.mainDelta_ = 10.0f;
    object->HandleDragUpdateForRTL(info);
    EXPECT_EQ(object->currentOffset_, 0.0f);
}

/**
 * @tc.name: HandleDragUpdateRTLNearEqual
 * @tc.desc: Test HandleDragUpdateForRTL with zero delta
 * @tc.type: FUNC
 */
HWTEST_F(SheetSideObjectTestNg, HandleDragUpdateRTLNearEqual, TestSize.Level1)
{
    auto sheetPattern = CreateSheetPattern();
    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    object->BindPattern(AceType::WeakClaim(AceType::RawPtr(sheetPattern)));
    object->sheetMaxWidth_ = SHEET_MAX_WIDTH;
    object->sheetWidth_ = SHEET_WIDTH;
    object->currentOffset_ = 0.0f;

    GestureEvent info;
    info.mainDelta_ = 0.0f;
    object->HandleDragUpdateForRTL(info);
    EXPECT_EQ(object->currentOffset_, 0.0f);
}

/**
 * @tc.name: HandleDragEndCurrentOffsetZero
 * @tc.desc: Test HandleDragEnd early return when currentOffset is zero
 * @tc.type: FUNC
 */
HWTEST_F(SheetSideObjectTestNg, HandleDragEndCurrentOffsetZero, TestSize.Level1)
{
    auto sheetPattern = CreateSheetPattern();
    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    object->BindPattern(AceType::WeakClaim(AceType::RawPtr(sheetPattern)));
    object->currentOffset_ = 0.0f;

    object->HandleDragEnd(0.0f);
    EXPECT_EQ(object->currentOffset_, 0.0f);
}

/**
 * @tc.name: HandleDragEndForLTRVelocityBelowThresholdOffsetBelowHalf
 * @tc.desc: Test HandleDragEndForLTR when velocity is below threshold and offset is below half width
 * @tc.type: FUNC
 */
HWTEST_F(SheetSideObjectTestNg, HandleDragEndForLTRVelocityBelowThresholdOffsetBelowHalf, TestSize.Level1)
{
    auto sheetPattern = CreateSheetPattern();
    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    object->BindPattern(AceType::WeakClaim(AceType::RawPtr(sheetPattern)));
    object->sheetWidth_ = SHEET_WIDTH;
    object->currentOffset_ = 30.0f;
    object->sheetMaxWidth_ = SHEET_MAX_WIDTH;

    object->HandleDragEnd(500.0f);
    EXPECT_TRUE(sheetPattern->isNeedProcessHeight_);
}

/**
 * @tc.name: HandleDragEndForLTRVelocityAboveThresholdDragNegative
 * @tc.desc: Test HandleDragEndForLTR when velocity exceeds threshold and dragging negative
 * @tc.type: FUNC
 */
HWTEST_F(SheetSideObjectTestNg, HandleDragEndForLTRVelocityAboveThresholdDragNegative, TestSize.Level1)
{
    auto sheetPattern = CreateSheetPattern();
    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    object->BindPattern(AceType::WeakClaim(AceType::RawPtr(sheetPattern)));
    object->sheetWidth_ = SHEET_WIDTH;
    object->currentOffset_ = 50.0f;
    object->sheetMaxWidth_ = SHEET_MAX_WIDTH;

    object->HandleDragEnd(-1500.0f);
    EXPECT_TRUE(sheetPattern->isNeedProcessHeight_);
}

/**
 * @tc.name: HandleDragEndForRTLVelocityBelowThresholdOffsetBelowHalf
 * @tc.desc: Test HandleDragEndForRTL when velocity is below threshold and offset is below half width
 * @tc.type: FUNC
 */
HWTEST_F(SheetSideObjectTestNg, HandleDragEndForRTLVelocityBelowThresholdOffsetBelowHalf, TestSize.Level1)
{
    auto sheetPattern = CreateSheetPattern();
    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    object->BindPattern(AceType::WeakClaim(AceType::RawPtr(sheetPattern)));
    object->sheetWidth_ = SHEET_WIDTH;
    object->currentOffset_ = -30.0f;
    object->sheetMaxWidth_ = SHEET_MAX_WIDTH;

    object->HandleDragEnd(500.0f);
    EXPECT_TRUE(sheetPattern->isNeedProcessHeight_);
}

/**
 * @tc.name: HandleDragEndForRTLVelocityAboveThresholdDragPositive
 * @tc.desc: Test HandleDragEndForRTL when velocity exceeds threshold and dragging positive
 * @tc.type: FUNC
 */
HWTEST_F(SheetSideObjectTestNg, HandleDragEndForRTLVelocityAboveThresholdDragPositive, TestSize.Level1)
{
    auto sheetPattern = CreateSheetPattern();
    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    object->BindPattern(AceType::WeakClaim(AceType::RawPtr(sheetPattern)));
    object->sheetWidth_ = SHEET_WIDTH;
    object->currentOffset_ = -50.0f;
    object->sheetMaxWidth_ = SHEET_MAX_WIDTH;

    object->HandleDragEnd(1500.0f);
    EXPECT_TRUE(sheetPattern->isNeedProcessHeight_);
}

/**
 * @tc.name: ModifyFireSheetTransitionTest
 * @tc.desc: Test ModifyFireSheetTransition starts animation and sets animation break
 * @tc.type: FUNC
 */
HWTEST_F(SheetSideObjectTestNg, ModifyFireSheetTransitionTest, TestSize.Level1)
{
    auto sheetPattern = CreateSheetPattern();
    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    object->BindPattern(AceType::WeakClaim(AceType::RawPtr(sheetPattern)));
    object->sheetMaxWidth_ = SHEET_MAX_WIDTH;
    object->sheetWidth_ = SHEET_WIDTH;
    sheetPattern->isAnimationBreak_ = true;

    object->CreatePropertyCallback();
    object->ModifyFireSheetTransition(500.0f);
    EXPECT_TRUE(sheetPattern->isAnimationProcess_);
    SUCCEED();
}

/**
 * @tc.name: CreatePropertyCallbackTest
 * @tc.desc: Test CreatePropertyCallback creates a new property when none exists
 * @tc.type: FUNC
 */
HWTEST_F(SheetSideObjectTestNg, CreatePropertyCallbackTest, TestSize.Level1)
{
    auto sheetPattern = CreateSheetPattern();
    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    object->BindPattern(AceType::WeakClaim(AceType::RawPtr(sheetPattern)));

    object->CreatePropertyCallback();
    EXPECT_NE(sheetPattern->GetProperty(), nullptr);
}

/**
 * @tc.name: CreatePropertyCallbackAlreadyHasProperty
 * @tc.desc: Test CreatePropertyCallback reuses existing property
 * @tc.type: FUNC
 */
HWTEST_F(SheetSideObjectTestNg, CreatePropertyCallbackAlreadyHasProperty, TestSize.Level1)
{
    auto sheetPattern = CreateSheetPattern();
    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    object->BindPattern(AceType::WeakClaim(AceType::RawPtr(sheetPattern)));

    auto prop = AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0f, [](float) {});
    sheetPattern->SetProperty(prop);

    object->CreatePropertyCallback();
    EXPECT_NE(sheetPattern->GetProperty(), nullptr);
}

/**
 * @tc.name: GetAvoidKeyboardModeByDefaultTest
 * @tc.desc: Test GetAvoidKeyboardModeByDefault returns TRANSLATE_AND_SCROLL
 * @tc.type: FUNC
 */
HWTEST_F(SheetSideObjectTestNg, GetAvoidKeyboardModeByDefaultTest, TestSize.Level1)
{
    auto object = CreateSheetObject();
    auto mode = object->GetAvoidKeyboardModeByDefault();
    EXPECT_EQ(mode, SheetKeyboardAvoidMode::TRANSLATE_AND_SCROLL);
}

/**
 * @tc.name: BeforeCreateLayoutWrapperTest
 * @tc.desc: Test BeforeCreateLayoutWrapper executes without crash
 * @tc.type: FUNC
 */
HWTEST_F(SheetSideObjectTestNg, BeforeCreateLayoutWrapperTest, TestSize.Level1)
{
    auto sheetPattern = CreateSheetPattern();
    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    object->BindPattern(AceType::WeakClaim(AceType::RawPtr(sheetPattern)));

    object->BeforeCreateLayoutWrapper();
    SUCCEED();
}

/**
 * @tc.name: AvoidKeyboardModeNone
 * @tc.desc: Test AvoidKeyboard with NONE mode does not resize
 * @tc.type: FUNC
 */
HWTEST_F(SheetSideObjectTestNg, AvoidKeyboardModeNone, TestSize.Level1)
{
    auto sheetPattern = CreateSheetPattern();
    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    object->BindPattern(AceType::WeakClaim(AceType::RawPtr(sheetPattern)));
    sheetPattern->keyboardAvoidMode_ = SheetKeyboardAvoidMode::NONE;

    object->AvoidKeyboard(false);
    EXPECT_EQ(object->resizeDecreasedHeight_, 0.0f);
}

/**
 * @tc.name: AvoidKeyboardKeyboardHeightSame
 * @tc.desc: Test AvoidKeyboard when keyboard height equals previous height
 * @tc.type: FUNC
 */
HWTEST_F(SheetSideObjectTestNg, AvoidKeyboardKeyboardHeightSame, TestSize.Level1)
{
    auto sheetPattern = CreateSheetPattern();
    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    object->BindPattern(AceType::WeakClaim(AceType::RawPtr(sheetPattern)));
    sheetPattern->keyboardAvoidMode_ = SheetKeyboardAvoidMode::TRANSLATE_AND_SCROLL;
    auto host = sheetPattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto focusHub = host->GetOrCreateFocusHub();
    focusHub->currentFocus_ = true;

    auto pipeline = MockPipelineContext::GetCurrent();
    pipeline->safeAreaManager_->keyboardInset_ = { 0.0f, 300.0f };
    sheetPattern->keyboardHeight_ = 300.0f;

    object->AvoidKeyboard(false);
    EXPECT_EQ(object->resizeDecreasedHeight_, 0.0f);
}

/**
 * @tc.name: AvoidKeyboardDismissProcess
 * @tc.desc: Test AvoidKeyboard when dismiss process is active
 * @tc.type: FUNC
 */
HWTEST_F(SheetSideObjectTestNg, AvoidKeyboardDismissProcess, TestSize.Level1)
{
    auto sheetPattern = CreateSheetPattern();
    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    object->BindPattern(AceType::WeakClaim(AceType::RawPtr(sheetPattern)));
    sheetPattern->keyboardAvoidMode_ = SheetKeyboardAvoidMode::TRANSLATE_AND_SCROLL;
    auto host = sheetPattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto focusHub = host->GetOrCreateFocusHub();
    focusHub->currentFocus_ = true;

    auto pipeline = MockPipelineContext::GetCurrent();
    pipeline->safeAreaManager_->keyboardInset_ = { 0.0f, 300.0f };
    sheetPattern->isDismissProcess_ = true;

    object->AvoidKeyboard(false);
    EXPECT_TRUE(sheetPattern->isDismissProcess_);
}

/**
 * @tc.name: AvoidKeyboardResizeOnly
 * @tc.desc: Test AvoidKeyboard with RESIZE_ONLY mode when keyboard height changes
 * @tc.type: FUNC
 */
HWTEST_F(SheetSideObjectTestNg, AvoidKeyboardResizeOnly, TestSize.Level1)
{
    auto sheetPattern = CreateSheetPattern();
    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    object->BindPattern(AceType::WeakClaim(AceType::RawPtr(sheetPattern)));
    sheetPattern->keyboardAvoidMode_ = SheetKeyboardAvoidMode::RESIZE_ONLY;
    auto host = sheetPattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto focusHub = host->GetOrCreateFocusHub();
    focusHub->currentFocus_ = true;

    auto pipeline = MockPipelineContext::GetCurrent();
    pipeline->safeAreaManager_->keyboardInset_ = { 0.0f, 300.0f };
    sheetPattern->keyboardHeight_ = 0.0f;

    object->AvoidKeyboard(false);
    EXPECT_EQ(object->resizeDecreasedHeight_, 300.0f);
}

/**
 * @tc.name: AvoidKeyboardTranslateAndResizeNonPositive
 * @tc.desc: Test AvoidKeyboard with TRANSLATE_AND_RESIZE when resize result is non-positive
 * @tc.type: FUNC
 */
HWTEST_F(SheetSideObjectTestNg, AvoidKeyboardTranslateAndResizeNonPositive, TestSize.Level1)
{
    auto sheetPattern = CreateSheetPattern();
    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    object->BindPattern(AceType::WeakClaim(AceType::RawPtr(sheetPattern)));
    sheetPattern->keyboardAvoidMode_ = SheetKeyboardAvoidMode::TRANSLATE_AND_RESIZE;
    auto host = sheetPattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto focusHub = host->GetOrCreateFocusHub();
    focusHub->currentFocus_ = true;

    auto pipeline = MockPipelineContext::GetCurrent();
    pipeline->safeAreaManager_->keyboardInset_ = { 0.0f, 300.0f };
    sheetPattern->keyboardHeight_ = 300.0f;

    object->AvoidKeyboard(false);
    EXPECT_EQ(object->resizeDecreasedHeight_, 0.0f);
}

/**
 * @tc.name: AvoidKeyboardTranslateAndScrollNonPositive
 * @tc.desc: Test AvoidKeyboard with TRANSLATE_AND_SCROLL when resize result is non-positive
 * @tc.type: FUNC
 */
HWTEST_F(SheetSideObjectTestNg, AvoidKeyboardTranslateAndScrollNonPositive, TestSize.Level1)
{
    auto sheetPattern = CreateSheetPattern();
    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    object->BindPattern(AceType::WeakClaim(AceType::RawPtr(sheetPattern)));
    sheetPattern->keyboardAvoidMode_ = SheetKeyboardAvoidMode::TRANSLATE_AND_SCROLL;
    auto host = sheetPattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto focusHub = host->GetOrCreateFocusHub();
    focusHub->currentFocus_ = true;

    auto pipeline = MockPipelineContext::GetCurrent();
    pipeline->safeAreaManager_->keyboardInset_ = { 0.0f, 300.0f };
    sheetPattern->keyboardHeight_ = 300.0f;

    object->AvoidKeyboard(false);
    EXPECT_EQ(object->resizeDecreasedHeight_, 0.0f);
}

/**
 * @tc.name: GetUpOffsetCaretNeedKeyboardHeightZero
 * @tc.desc: Test GetUpOffsetCaretNeed returns zero when keyboard height is zero
 * @tc.type: FUNC
 */
HWTEST_F(SheetSideObjectTestNg, GetUpOffsetCaretNeedKeyboardHeightZero, TestSize.Level1)
{
    auto sheetPattern = CreateSheetPattern();
    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    object->BindPattern(AceType::WeakClaim(AceType::RawPtr(sheetPattern)));

    auto pipeline = MockPipelineContext::GetCurrent();
    pipeline->safeAreaManager_->keyboardInset_ = { 0.0f, 0.0f };

    auto result = object->GetUpOffsetCaretNeed();
    EXPECT_EQ(result, 0.0f);
}

/**
 * @tc.name: FireHeightDidChangeTest
 * @tc.desc: Test FireHeightDidChange updates preDidHeight when sheet height changes
 * @tc.type: FUNC
 */
HWTEST_F(SheetSideObjectTestNg, FireHeightDidChangeTest, TestSize.Level1)
{
    auto sheetPattern = CreateSheetPattern();
    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    object->BindPattern(AceType::WeakClaim(AceType::RawPtr(sheetPattern)));
    object->sheetHeight_ = SHEET_HEIGHT;
    sheetPattern->preDidHeight_ = 0.0f;

    object->FireHeightDidChange();
    EXPECT_EQ(sheetPattern->preDidHeight_, SHEET_HEIGHT);
}

/**
 * @tc.name: FireHeightDidChangeNearEqual
 * @tc.desc: Test FireHeightDidChange skips update when sheet height equals preDidHeight
 * @tc.type: FUNC
 */
HWTEST_F(SheetSideObjectTestNg, FireHeightDidChangeNearEqual, TestSize.Level1)
{
    auto sheetPattern = CreateSheetPattern();
    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    object->BindPattern(AceType::WeakClaim(AceType::RawPtr(sheetPattern)));
    object->sheetHeight_ = SHEET_HEIGHT;
    sheetPattern->preDidHeight_ = SHEET_HEIGHT;

    object->FireHeightDidChange();
    EXPECT_EQ(sheetPattern->preDidHeight_, SHEET_HEIGHT);
}
} // namespace OHOS::Ace::NG
