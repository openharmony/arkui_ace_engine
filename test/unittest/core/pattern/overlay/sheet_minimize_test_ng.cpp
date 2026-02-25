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
#include "ui/base/utils/utils.h"

#define private public
#define protected public

#include "test/mock/base/mock_foldable_window.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"

#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_property.h"
#include "core/components_ng/pattern/overlay/sheet_style.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/sheet/minimize/sheet_minimize_object.h"
#include "core/components_ng/pattern/sheet/minimize/sheet_presentation_minimize_layout_algorithm.h"
#include "core/components_ng/pattern/stage/stage_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class SheetMinimizeTestNG : public testing::Test {
public:
    static int32_t lastPlatformVersion_;

    static void SetUpTestCase();
    static void TearDownTestCase();
    static void SetSheetTheme(RefPtr<SheetTheme> sheetTheme);
    void SetUp() override;
    void TearDown() override;
};

int32_t SheetMinimizeTestNG::lastPlatformVersion_ = 0;

/**
 * @brief: Called once before executing the entire test suite
 * @note: All TEST_F shared.
 *        Initialize the global commons.
 */
void SheetMinimizeTestNG::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    SheetMinimizeTestNG::lastPlatformVersion_ = PipelineBase::GetCurrentContext()->GetMinPlatformVersion();
}

/**
 * @brief: Called once after executing the entire test suite
 * @note: All TEST_F shared.
 *        Clean up the global commons.
 */
void SheetMinimizeTestNG::TearDownTestCase()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

// Before each TEST_F, the scope is a single test case
void SheetMinimizeTestNG::SetUp() {}

// After each TEST_F, the scope is a single test case
void SheetMinimizeTestNG::TearDown()
{
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(SheetMinimizeTestNG::lastPlatformVersion_);
    MockPipelineContext::GetCurrent()->SetThemeManager(nullptr);
}

void SheetMinimizeTestNG::SetSheetTheme(RefPtr<SheetTheme> sheetTheme)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(
        [sheetTheme = AceType::WeakClaim(AceType::RawPtr(sheetTheme))](ThemeType type) -> RefPtr<Theme> {
        if (type == SheetTheme::TypeId()) {
            return sheetTheme.Upgrade();
        } else {
            return nullptr;
        }
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

/**
 * @tc.name: PostProcessBorderWidth001
 * @tc.desc: Test SheetMinimizeObject::PostProcessBorderWidth Function
 * @tc.type: FUNC
 */
HWTEST_F(SheetMinimizeTestNG, PostProcessBorderWidth001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet pattern and minimize object.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->sheetType_ = SheetType::SHEET_MINIMIZE;
    sheetPattern->InitSheetObject();
    auto object = AceType::DynamicCast<SheetMinimizeObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    /**
     * @tc.steps: step2. test the setting of border width.
     * @tc.expected: returns the same borderWidth.
     */
    NG::BorderWidthProperty borderWidth;
    borderWidth.leftDimen = 1.0_vp;
    borderWidth.rightDimen = 2.0_vp;
    borderWidth.topDimen = 3.0_vp;
    borderWidth.bottomDimen = 4.0_vp;
    auto result = object->PostProcessBorderWidth(borderWidth);
    EXPECT_EQ(result.leftDimen, 1.0_vp);
    EXPECT_EQ(result.rightDimen, 2.0_vp);
    EXPECT_EQ(result.topDimen, 3.0_vp);
    EXPECT_EQ(result.bottomDimen, 4.0_vp);
}

/**
 * @tc.name: DirtyLayoutProcess001
 * @tc.desc: Test SheetMinimizeObject::DirtyLayoutProcess Function
 * @tc.type: FUNC
 */
HWTEST_F(SheetMinimizeTestNG, DirtyLayoutProcess001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet pattern and minimize object.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->sheetType_ = SheetType::SHEET_MINIMIZE;
    sheetPattern->InitSheetObject();
    auto object = AceType::DynamicCast<SheetMinimizeObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    /**
     * @tc.steps: step2. create layoutAlgorithmT and layoutAlgorithmWrapper,
     *                   set minimize sheet dimensions.
     */
    auto layoutAlgorithmT = AceType::MakeRefPtr<SheetPresentationMinimizeLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithmT, nullptr);
    auto layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithmT);
    ASSERT_NE(layoutAlgorithmWrapper, nullptr);
    layoutAlgorithmT->sheetMaxWidth_ = 200.0f;
    layoutAlgorithmT->sheetWidth_ = 150.0f;
    layoutAlgorithmT->sheetMaxHeight_ = 300.0f;
    layoutAlgorithmT->sheetHeight_ = 125.0f;
    /**
     * @tc.steps: step3. call DirtyLayoutProcess and verify dimensions.
     * @tc.expected: sheetMaxWidth_, sheetWidth_, sheetHeight_ are updated.
     */
    object->DirtyLayoutProcess(layoutAlgorithmWrapper);
    EXPECT_EQ(object->sheetMaxWidth_, 200.0f);
    EXPECT_EQ(object->sheetWidth_, 150.0f);
    EXPECT_EQ(object->sheetHeight_, 125.0f);
    EXPECT_EQ(sheetPattern->GetSheetMaxHeight(), 300.0f);
}

/**
 * @tc.name: UpdateDragBarStatus001
 * @tc.desc: Test SheetMinimizeObject::UpdateDragBarStatus Function
 * @tc.type: FUNC
 */
HWTEST_F(SheetMinimizeTestNG, UpdateDragBarStatus001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet pattern, scroll pattern and minimize object.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 201,
        AceType::MakeRefPtr<SheetPresentationPattern>(301, "SheetMinimizeObject", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto scrollNode =
        FrameNode::CreateFrameNode("Scroll", 501, AceType::MakeRefPtr<ScrollPattern>());
    ASSERT_NE(scrollNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->SetScrollNode(WeakPtr<FrameNode>(scrollNode));
    sheetPattern->sheetType_ = SheetType::SHEET_MINIMIZE;
    sheetPattern->InitSheetObject();
    auto object = AceType::DynamicCast<SheetMinimizeObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    /**
     * @tc.steps: step2. call UpdateDragBarStatus.
     * @tc.expected: dragBar visibility should be set to INVISIBLE.
     */
    object->UpdateDragBarStatus();
    auto dragBarNode = sheetPattern->GetDragBarNode();
    if (dragBarNode) {
        auto dragBarLayoutProperty = dragBarNode->GetLayoutProperty();
        if (dragBarLayoutProperty) {
            auto visibility = dragBarLayoutProperty->GetVisibility();
            EXPECT_TRUE(visibility.has_value());
            EXPECT_EQ(visibility.value(), VisibleType::INVISIBLE);
        }
    }
}

/**
 * @tc.name: UpdateMinimizePosition001
 * @tc.desc: Test SheetMinimizeObject::UpdateMinimizePosition Function
 * @tc.type: FUNC
 */
HWTEST_F(SheetMinimizeTestNG, UpdateMinimizePosition001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet pattern and minimize object.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->sheetType_ = SheetType::SHEET_MINIMIZE;
    sheetPattern->InitSheetObject();
    auto object = AceType::DynamicCast<SheetMinimizeObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    /**
     * @tc.steps: step2. call UpdateMinimizePosition.
     * @tc.expected: transform translate should be (0.0f, 0.0f, 0.0f).
     */
    object->UpdateMinimizePosition();
    EXPECT_TRUE(NearZero(renderContext->GetTransformTranslate()->x.ConvertToPx()));
    EXPECT_TRUE(NearZero(renderContext->GetTransformTranslate()->y.ConvertToPx()));
    EXPECT_TRUE(NearZero(renderContext->GetTransformTranslate()->z.ConvertToPx()));
}

/**
 * @tc.name: GetSheetTransitionCurve001
 * @tc.desc: Test SheetMinimizeObject::GetSheetTransitionCurve Function
 * @tc.type: FUNC
 */
HWTEST_F(SheetMinimizeTestNG, GetSheetTransitionCurve001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet pattern and minimize object.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->sheetType_ = SheetType::SHEET_MINIMIZE;
    sheetPattern->InitSheetObject();
    auto object = AceType::DynamicCast<SheetMinimizeObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    /**
     * @tc.steps: step2. call GetSheetTransitionCurve.
     * @tc.expected: curve = (0.0f, CURVE_MASS, CURVE_STIFFNESS, CURVE_DAMPING).
     */
    auto curve = object->GetSheetTransitionCurve(0.0f);
    ASSERT_NE(curve, nullptr);
    auto springCurve = AceType::DynamicCast<InterpolatingSpring>(curve);
    ASSERT_NE(springCurve, nullptr);
    EXPECT_EQ(springCurve->velocity_, 0.0f);
    EXPECT_EQ(springCurve->mass_, CURVE_MASS);
    EXPECT_EQ(springCurve->stiffness_, CURVE_STIFFNESS);
    EXPECT_EQ(springCurve->damping_, CURVE_DAMPING);
}

/**
 * @tc.name: GetSheetTransitionFinishEvent001
 * @tc.desc: Test SheetMinimizeObject::GetSheetTransitionFinishEvent Function - Transition In
 * @tc.type: FUNC
 */
HWTEST_F(SheetMinimizeTestNG, GetSheetTransitionFinishEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet pattern and minimize object.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->sheetType_ = SheetType::SHEET_MINIMIZE;
    sheetPattern->InitSheetObject();
    auto object = AceType::DynamicCast<SheetMinimizeObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    /**
     * @tc.steps: step2. get finish event for transition in.
     * @tc.expected: func is not nullptr.
     */
    auto func = object->GetSheetTransitionFinishEvent(true);
    ASSERT_NE(func, nullptr);
    /**
     * @tc.steps: step3. call func to verify it executes normally.
     * @tc.expected: animationProcess is false.
     */
    sheetPattern->SetAnimationProcess(true);
    func();
    EXPECT_EQ(sheetPattern->GetAnimationProcess(), false);
}

/**
 * @tc.name: GetSheetTransitionFinishEvent002
 * @tc.desc: Test SheetMinimizeObject::GetSheetTransitionFinishEvent Function - Transition Out
 * @tc.type: FUNC
 */
HWTEST_F(SheetMinimizeTestNG, GetSheetTransitionFinishEvent002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet pattern and minimize object.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->sheetType_ = SheetType::SHEET_MINIMIZE;
    sheetPattern->InitSheetObject();
    auto object = AceType::DynamicCast<SheetMinimizeObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    /**
     * @tc.steps: step2. get finish event for transition out.
     * @tc.expected: func is not nullptr.
     */
    auto func = object->GetSheetTransitionFinishEvent(false);
    ASSERT_NE(func, nullptr);
    /**
     * @tc.steps: step3. call func to verify it executes normally.
     * @tc.expected: animationProcess is false.
     */
    sheetPattern->SetAnimationProcess(true);
    func();
    EXPECT_EQ(sheetPattern->GetAnimationProcess(), false);
}

/**
 * @tc.name: InitAnimationForOverlay001
 * @tc.desc: Test SheetMinimizeObject::InitAnimationForOverlay Function - Transition In First
 * @tc.type: FUNC
 */
HWTEST_F(SheetMinimizeTestNG, InitAnimationForOverlay001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet pattern and minimize object.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->sheetType_ = SheetType::SHEET_MINIMIZE;
    sheetPattern->InitSheetObject();
    auto object = AceType::DynamicCast<SheetMinimizeObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    /**
     * @tc.steps: step2. call InitAnimationForOverlay with isTransitionIn=true, isFirstTransition=true.
     * @tc.expected: transform translate should be (0.0f, 0.0f, 0.0f).
     */
    object->InitAnimationForOverlay(true, true);
    EXPECT_TRUE(NearZero(renderContext->GetTransformTranslate()->x.ConvertToPx()));
    EXPECT_TRUE(NearZero(renderContext->GetTransformTranslate()->y.ConvertToPx()));
    EXPECT_TRUE(NearZero(renderContext->GetTransformTranslate()->z.ConvertToPx()));
}

/**
 * @tc.name: InitAnimationForOverlay002
 * @tc.desc: Test SheetMinimizeObject::InitAnimationForOverlay Function - Transition In Not First
 * @tc.type: FUNC
 */
HWTEST_F(SheetMinimizeTestNG, InitAnimationForOverlay002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet pattern and minimize object.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->sheetType_ = SheetType::SHEET_MINIMIZE;
    sheetPattern->InitSheetObject();
    auto object = AceType::DynamicCast<SheetMinimizeObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    /**
     * @tc.steps: step2. call InitAnimationForOverlay with isTransitionIn=true, isFirstTransition=false.
     * @tc.expected: transform translate should be (0.0f, 0.0f, 0.0f).
     */
    object->InitAnimationForOverlay(true, false);
    EXPECT_TRUE(NearZero(renderContext->GetTransformTranslate()->x.ConvertToPx()));
    EXPECT_TRUE(NearZero(renderContext->GetTransformTranslate()->y.ConvertToPx()));
    EXPECT_TRUE(NearZero(renderContext->GetTransformTranslate()->z.ConvertToPx()));
}

/**
 * @tc.name: SetFinishEventForAnimationOption001
 * @tc.desc: Test SheetMinimizeObject::SetFinishEventForAnimationOption Function - Transition In
 * @tc.type: FUNC
 */
HWTEST_F(SheetMinimizeTestNG, SetFinishEventForAnimationOption001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet pattern and minimize object.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->sheetType_ = SheetType::SHEET_MINIMIZE;
    sheetPattern->InitSheetObject();
    auto object = AceType::DynamicCast<SheetMinimizeObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    AnimationOption option;
    /**
     * @tc.steps: step2. call SetFinishEventForAnimationOption with isTransitionIn=true.
     * @tc.expected: option should have finish event.
     */
    object->SetFinishEventForAnimationOption(option, true, true);
    EXPECT_NE(option.GetOnFinishEvent(), nullptr);
}

/**
 * @tc.name: SetFinishEventForAnimationOption002
 * @tc.desc: Test SheetMinimizeObject::SetFinishEventForAnimationOption Function - Transition Out
 * @tc.type: FUNC
 */
HWTEST_F(SheetMinimizeTestNG, SetFinishEventForAnimationOption002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet pattern and minimize object.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->sheetType_ = SheetType::SHEET_MINIMIZE;
    sheetPattern->InitSheetObject();
    auto object = AceType::DynamicCast<SheetMinimizeObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    AnimationOption option;
    /**
     * @tc.steps: step2. call SetFinishEventForAnimationOption with isTransitionIn=false.
     * @tc.expected: option should have finish event.
     */
    object->SetFinishEventForAnimationOption(option, false, true);
    EXPECT_NE(option.GetOnFinishEvent(), nullptr);
}

/**
 * @tc.name: GetAnimationOptionForOverlay001
 * @tc.desc: Test SheetMinimizeObject::GetAnimationOptionForOverlay Function
 * @tc.type: FUNC
 */
HWTEST_F(SheetMinimizeTestNG, GetAnimationOptionForOverlay001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet pattern and minimize object.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->sheetType_ = SheetType::SHEET_MINIMIZE;
    sheetPattern->InitSheetObject();
    auto object = AceType::DynamicCast<SheetMinimizeObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    /**
     * @tc.steps: step2. call GetAnimationOptionForOverlay.
     * @tc.expected: curve should match, duration should be SHEET_ANIMATION_DURATION, fill mode should be FORWARDS.
     */
    auto option = object->GetAnimationOptionForOverlay(true, true);
    auto curve = option.GetCurve();
    auto springCurve = AceType::DynamicCast<InterpolatingSpring>(curve);
    ASSERT_NE(springCurve, nullptr);
    EXPECT_EQ(springCurve->velocity_, 0.0f);
    EXPECT_EQ(springCurve->mass_, CURVE_MASS);
    EXPECT_EQ(springCurve->stiffness_, CURVE_STIFFNESS);
    EXPECT_EQ(springCurve->damping_, CURVE_DAMPING);
    EXPECT_EQ(option.GetDuration(), SHEET_ANIMATION_DURATION);
    EXPECT_EQ(option.GetFillMode(), FillMode::FORWARDS);
}

/**
 * @tc.name: TransformTranslateEnter001
 * @tc.desc: Test SheetMinimizeObject::TransformTranslateEnter Function
 * @tc.type: FUNC
 */
HWTEST_F(SheetMinimizeTestNG, TransformTranslateEnter001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet pattern and minimize object.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->sheetType_ = SheetType::SHEET_MINIMIZE;
    sheetPattern->InitSheetObject();
    auto object = AceType::DynamicCast<SheetMinimizeObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    /**
     * @tc.steps: step2. call TransformTranslateEnter.
     * @tc.expected: transform translate should be (0.0f, 0.0f, 0.0f).
     */
    object->TransformTranslateEnter();
    EXPECT_TRUE(NearZero(renderContext->GetTransformTranslate()->x.ConvertToPx()));
    EXPECT_TRUE(NearZero(renderContext->GetTransformTranslate()->y.ConvertToPx()));
    EXPECT_TRUE(NearZero(renderContext->GetTransformTranslate()->z.ConvertToPx()));
}

/**
 * @tc.name: TransformTranslateExit001
 * @tc.desc: Test SheetMinimizeObject::TransformTranslateExit Function
 * @tc.type: FUNC
 */
HWTEST_F(SheetMinimizeTestNG, TransformTranslateExit001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet pattern and minimize object.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->sheetType_ = SheetType::SHEET_MINIMIZE;
    sheetPattern->InitSheetObject();
    auto object = AceType::DynamicCast<SheetMinimizeObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    /**
     * @tc.steps: step2. call TransformTranslateExit.
     * @tc.expected: transform translate should be (0.0f, 0.0f, 0.0f).
     */
    object->TransformTranslateExit();
    EXPECT_TRUE(NearZero(renderContext->GetTransformTranslate()->x.ConvertToPx()));
    EXPECT_TRUE(NearZero(renderContext->GetTransformTranslate()->y.ConvertToPx()));
    EXPECT_TRUE(NearZero(renderContext->GetTransformTranslate()->z.ConvertToPx()));
}

/**
 * @tc.name: GetAnimationPropertyCallForOverlay001
 * @tc.desc: Test SheetMinimizeObject::GetAnimationPropertyCallForOverlay Function - Non-Interactive Transition In
 * @tc.type: FUNC
 */
HWTEST_F(SheetMinimizeTestNG, GetAnimationPropertyCallForOverlay001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet pattern, layoutProperty and minimize object.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    SheetStyle sheetStyle;
    sheetStyle.interactive = false;
    layoutProperty->UpdateSheetStyle(sheetStyle);
    sheetPattern->sheetType_ = SheetType::SHEET_MINIMIZE;
    sheetPattern->InitSheetObject();
    auto object = AceType::DynamicCast<SheetMinimizeObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    /**
     * @tc.steps: step2. get animation property call for overlay with isTransitionIn=true.
     * @tc.expected: callback is not nullptr.
     */
    auto callback1 = object->GetAnimationPropertyCallForOverlay(true);
    ASSERT_NE(callback1, nullptr);
    /**
     * @tc.steps: step3. call callback to verify it executes normally.
     * @tc.expected: transform translate should be (0.0f, 0.0f, 0.0f).
     */
    callback1();
    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_TRUE(NearZero(renderContext->GetTransformTranslate()->x.ConvertToPx()));
    EXPECT_TRUE(NearZero(renderContext->GetTransformTranslate()->y.ConvertToPx()));
    EXPECT_TRUE(NearZero(renderContext->GetTransformTranslate()->z.ConvertToPx()));
}

/**
 * @tc.name: GetAnimationPropertyCallForOverlay002
 * @tc.desc: Test SheetMinimizeObject::GetAnimationPropertyCallForOverlay Function - Non-Interactive Transition Out
 * @tc.type: FUNC
 */
HWTEST_F(SheetMinimizeTestNG, GetAnimationPropertyCallForOverlay002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet pattern, layoutProperty and minimize object.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    SheetStyle sheetStyle;
    sheetStyle.interactive = false;
    layoutProperty->UpdateSheetStyle(sheetStyle);
    sheetPattern->sheetType_ = SheetType::SHEET_MINIMIZE;
    sheetPattern->InitSheetObject();
    auto object = AceType::DynamicCast<SheetMinimizeObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    /**
     * @tc.steps: step2. get animation property call for overlay with isTransitionIn=false.
     * @tc.expected: callback is not nullptr.
     */
    auto callback1 = object->GetAnimationPropertyCallForOverlay(false);
    ASSERT_NE(callback1, nullptr);
    /**
     * @tc.steps: step3. call callback to verify it executes normally.
     * @tc.expected: transform translate should be (0.0f, 0.0f, 0.0f).
     */
    callback1();
    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_TRUE(NearZero(renderContext->GetTransformTranslate()->x.ConvertToPx()));
    EXPECT_TRUE(NearZero(renderContext->GetTransformTranslate()->y.ConvertToPx()));
    EXPECT_TRUE(NearZero(renderContext->GetTransformTranslate()->z.ConvertToPx()));
}

/**
 * @tc.name: OnLanguageConfigurationUpdate001
 * @tc.desc: Test SheetMinimizeObject::OnLanguageConfigurationUpdate Function
 * @tc.type: FUNC
 */
HWTEST_F(SheetMinimizeTestNG, OnLanguageConfigurationUpdate001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet pattern and minimize object.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->sheetType_ = SheetType::SHEET_MINIMIZE;
    sheetPattern->InitSheetObject();
    auto object = AceType::DynamicCast<SheetMinimizeObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    /**
     * @tc.steps: step2. call OnLanguageConfigurationUpdate.
     * @tc.expected: transform translate should be (0.0f, 0.0f, 0.0f).
     */
    object->OnLanguageConfigurationUpdate();
    EXPECT_TRUE(NearZero(renderContext->GetTransformTranslate()->x.ConvertToPx()));
    EXPECT_TRUE(NearZero(renderContext->GetTransformTranslate()->y.ConvertToPx()));
    EXPECT_TRUE(NearZero(renderContext->GetTransformTranslate()->z.ConvertToPx()));
}

/**
 * @tc.name: GetSheetSafeAreaPadding001
 * @tc.desc: Test SheetMinimizeObject::GetSheetSafeAreaPadding Function
 * @tc.type: FUNC
 */
HWTEST_F(SheetMinimizeTestNG, GetSheetSafeAreaPadding001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet pattern and minimize object.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->sheetType_ = SheetType::SHEET_MINIMIZE;
    sheetPattern->InitSheetObject();
    auto object = AceType::DynamicCast<SheetMinimizeObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    /**
     * @tc.steps: step2. call GetSheetSafeAreaPadding.
     * @tc.expected: all paddings should be 0.0f.
     */
    auto padding = object->GetSheetSafeAreaPadding();
    EXPECT_EQ(padding.left, 0.0f);
    EXPECT_EQ(padding.right, 0.0f);
    EXPECT_EQ(padding.top, 0.0f);
    EXPECT_EQ(padding.bottom, 0.0f);
}

/**
 * @tc.name: HandleDragStart001
 * @tc.desc: Test SheetMinimizeObject::HandleDragStart Function
 * @tc.type: FUNC
 */
HWTEST_F(SheetMinimizeTestNG, HandleDragStart001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet pattern and minimize object.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 201,
        AceType::MakeRefPtr<SheetPresentationPattern>(301, "SheetMinimizeObject", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto scrollNode =
        FrameNode::CreateFrameNode("Scroll", 501, AceType::MakeRefPtr<ScrollPattern>());
    ASSERT_NE(scrollNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->SetScrollNode(WeakPtr<FrameNode>(scrollNode));
    sheetPattern->sheetType_ = SheetType::SHEET_MINIMIZE;
    sheetPattern->InitSheetObject();
    auto object = AceType::DynamicCast<SheetMinimizeObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    /**
     * @tc.steps: step2. call HandleDragStart.
     * @tc.expected: isDragging should be false, currentOffset_ should be 0.0f.
     */
    object->HandleDragStart();
    EXPECT_EQ(sheetPattern->IsDragging(), false);
    EXPECT_EQ(object->currentOffset_, 0.0f);
}

/**
 * @tc.name: FireHeightDidChange001
 * @tc.desc: Test SheetMinimizeObject::FireHeightDidChange Function
 * @tc.type: FUNC
 */
HWTEST_F(SheetMinimizeTestNG, FireHeightDidChange001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet pattern and minimize object.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->sheetType_ = SheetType::SHEET_MINIMIZE;
    sheetPattern->InitSheetObject();
    auto object = AceType::DynamicCast<SheetMinimizeObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    /**
     * @tc.steps: step2. set preDidHeight and sheetHeight_, call FireHeightDidChange and check result.
     * @tc.expected: preDidHeight_ is updated to match sheetHeight_.
     */
    sheetPattern->SetPreDidHeight(1.0f);
    object->sheetHeight_ = 1.0f;
    object->FireHeightDidChange();
    EXPECT_EQ(sheetPattern->GetPreDidHeight(), 1.0f);
    object->sheetHeight_ = 5.0f;
    object->FireHeightDidChange();
    EXPECT_EQ(sheetPattern->GetPreDidHeight(), 5.0f);
}

/**
 * @tc.name: MinimizeSheetMeasure001
 * @tc.desc: Test SheetPresentationMinimizeLayoutAlgorithm::Measure Function
 * @tc.type: FUNC
 */
HWTEST_F(SheetMinimizeTestNG, MinimizeSheetMeasure001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet pattern, layoutProperty and algorithm.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(1000.0f, 2000.0f);
    auto geometryNode = sheetNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetParentLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();
    sheetPattern->sheetType_ = SheetType::SHEET_MINIMIZE;
    sheetPattern->InitSheetObject();
    auto algorithm = AceType::MakeRefPtr<SheetPresentationMinimizeLayoutAlgorithm>();
    ASSERT_NE(algorithm, nullptr);
    /**
     * @tc.steps: step2. call Measure.
     * @tc.expected: sheetWidth_, sheetHeight_, sheetMaxWidth_, sheetMaxHeight_ should be set.
     */
    algorithm->Measure(AceType::RawPtr(sheetNode));
    EXPECT_FLOAT_EQ(algorithm->sheetMaxWidth_, 1000.0f);
    EXPECT_FLOAT_EQ(algorithm->sheetMaxHeight_, 2000.0f);
    EXPECT_GT(algorithm->sheetWidth_, 0.0f);
    EXPECT_GT(algorithm->sheetHeight_, 0.0f);
}

/**
 * @tc.name: GetAvoidKeyboardModeByDefault001
 * @tc.desc: Test SheetMinimizeObject::GetAvoidKeyboardModeByDefault Function
 * @tc.type: FUNC
 */
HWTEST_F(SheetMinimizeTestNG, GetAvoidKeyboardModeByDefault001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet pattern and minimize object.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->sheetType_ = SheetType::SHEET_MINIMIZE;
    sheetPattern->InitSheetObject();
    auto object = AceType::DynamicCast<SheetMinimizeObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    /**
     * @tc.steps: step2. call GetAvoidKeyboardModeByDefault.
     * @tc.expected: should return SheetKeyboardAvoidMode::NONE.
     */
    auto mode = object->GetAvoidKeyboardModeByDefault();
    EXPECT_EQ(mode, SheetKeyboardAvoidMode::NONE);
}

/**
 * @tc.name: GetPanDirection001
 * @tc.desc: Test SheetMinimizeObject::GetPanDirection Function
 * @tc.type: FUNC
 */
HWTEST_F(SheetMinimizeTestNG, GetPanDirection001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet pattern and minimize object.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->sheetType_ = SheetType::SHEET_MINIMIZE;
    sheetPattern->InitSheetObject();
    auto object = AceType::DynamicCast<SheetMinimizeObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    /**
     * @tc.steps: step2. call GetPanDirection.
     * @tc.expected: should return PanDirection::HORIZONTAL.
     */
    auto direction = object->GetPanDirection();
    EXPECT_EQ(direction, PanDirection::HORIZONTAL);
}

/**
 * @tc.name: CheckIfNeedSetOuterBorderProp001
 * @tc.desc: Test SheetMinimizeObject::CheckIfNeedSetOuterBorderProp Function
 * @tc.type: FUNC
 */
HWTEST_F(SheetMinimizeTestNG, CheckIfNeedSetOuterBorderProp001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet pattern and minimize object.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->sheetType_ = SheetType::SHEET_MINIMIZE;
    sheetPattern->InitSheetObject();
    auto object = AceType::DynamicCast<SheetMinimizeObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    /**
     * @tc.steps: step2. call CheckIfNeedSetOuterBorderProp.
     * @tc.expected: should return false.
     */
    auto needSet = object->CheckIfNeedSetOuterBorderProp();
    EXPECT_EQ(needSet, false);
}

/**
 * @tc.name: CheckIfNeedShadowByDefault001
 * @tc.desc: Test SheetMinimizeObject::CheckIfNeedShadowByDefault Function
 * @tc.type: FUNC
 */
HWTEST_F(SheetMinimizeTestNG, CheckIfNeedShadowByDefault001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet pattern and minimize object.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->sheetType_ = SheetType::SHEET_MINIMIZE;
    sheetPattern->InitSheetObject();
    auto object = AceType::DynamicCast<SheetMinimizeObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    /**
     * @tc.steps: step2. call CheckIfNeedShadowByDefault.
     * @tc.expected: should return false.
     */
    auto needShadow = object->CheckIfNeedShadowByDefault();
    EXPECT_EQ(needShadow, false);
}

/**
 * @tc.name: CheckIfUpdateObject001
 * @tc.desc: Test SheetMinimizeObject::CheckIfUpdateObject Function
 * @tc.type: FUNC
 */
HWTEST_F(SheetMinimizeTestNG, CheckIfUpdateObject001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet pattern and minimize object.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->sheetType_ = SheetType::SHEET_MINIMIZE;
    sheetPattern->InitSheetObject();
    auto object = AceType::DynamicCast<SheetMinimizeObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    /**
     * @tc.steps: step2. call CheckIfUpdateObject with SHEET_MINIMIZE type.
     * @tc.expected: should return false (same type).
     */
    auto needUpdate = object->CheckIfUpdateObject(SheetType::SHEET_MINIMIZE);
    EXPECT_EQ(needUpdate, false);
}

/**
 * @tc.name: CheckIfUpdateObject002
 * @tc.desc: Test SheetMinimizeObject::CheckIfUpdateObject Function
 * @tc.type: FUNC
 */
HWTEST_F(SheetMinimizeTestNG, CheckIfUpdateObject002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet pattern and minimize object.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->sheetType_ = SheetType::SHEET_MINIMIZE;
    sheetPattern->InitSheetObject();
    auto object = AceType::DynamicCast<SheetMinimizeObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    /**
     * @tc.steps: step2. call CheckIfUpdateObject with SHEET_POPUP type.
     * @tc.expected: should return true (different type).
     */
    auto needUpdate = object->CheckIfUpdateObject(SheetType::SHEET_POPUP);
    EXPECT_EQ(needUpdate, true);
}

/**
 * @tc.name: IsSheetObjectBase001
 * @tc.desc: Test SheetMinimizeObject::IsSheetObjectBase Function
 * @tc.type: FUNC
 */
HWTEST_F(SheetMinimizeTestNG, IsSheetObjectBase001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet pattern and minimize object.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->sheetType_ = SheetType::SHEET_MINIMIZE;
    sheetPattern->InitSheetObject();
    auto object = AceType::DynamicCast<SheetMinimizeObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    /**
     * @tc.steps: step2. call IsSheetObjectBase.
     * @tc.expected: should return false.
     */
    auto isBase = object->IsSheetObjectBase();
    EXPECT_EQ(isBase, false);
}

/**
 * @tc.name: HandleScroll001
 * @tc.desc: Test SheetMinimizeObject::HandleScroll Function
 * @tc.type: FUNC
 */
HWTEST_F(SheetMinimizeTestNG, HandleScroll001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet pattern and minimize object.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->sheetType_ = SheetType::SHEET_MINIMIZE;
    sheetPattern->InitSheetObject();
    auto object = AceType::DynamicCast<SheetMinimizeObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    /**
     * @tc.steps: step2. call HandleScroll.
     * @tc.expected: should return scrollOffset with true.
     */
    auto result = object->HandleScroll(10.0f, 1, NestedState::GESTURE, 100.0f);
    EXPECT_FLOAT_EQ(result.remain, 10.0f);
    EXPECT_EQ(result.reachEdge, true);
}

/**
 * @tc.name: HandleScrollVelocity001
 * @tc.desc: Test SheetMinimizeObject::HandleScrollVelocity Function
 * @tc.type: FUNC
 */
HWTEST_F(SheetMinimizeTestNG, HandleScrollVelocity001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet pattern and minimize object.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->sheetType_ = SheetType::SHEET_MINIMIZE;
    sheetPattern->InitSheetObject();
    auto object = AceType::DynamicCast<SheetMinimizeObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    /**
     * @tc.steps: step2. call HandleScrollVelocity.
     * @tc.expected: should return false.
     */
    auto handled = object->HandleScrollVelocity(100.0f);
    EXPECT_EQ(handled, false);
}

} // namespace OHOS::Ace::NG
