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

#include <optional>
#include <string>

#include "gtest/gtest.h"
#include "ui/base/utils/utils.h"

#define private public
#define protected public

#include "test/mock/base/mock_foldable_window.h"
#include "test/mock/base/mock_subwindow.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"
#include "ui/base/ace_type.h"
#include "ui/base/geometry/dimension.h"

#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_layout_algorithm.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_property.h"
#include "core/components_ng/pattern/overlay/sheet_style.h"
#include "core/components_ng/pattern/overlay/sheet_view.h"
#include "core/components_ng/pattern/overlay/sheet_wrapper_layout_algorithm.h"
#include "core/components_ng/pattern/overlay/sheet_wrapper_pattern.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/sheet/content_cover/sheet_content_cover_layout_algorithm.h"
#include "core/components_ng/pattern/sheet/content_cover/sheet_content_cover_object.h"
#include "core/components_ng/pattern/sheet/sheet_mask_pattern.h"
#include "core/components_ng/pattern/sheet/sheet_object.h"
#include "core/components_ng/pattern/stage/stage_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class SheetContentCoverObjectTestNG : public testing::Test {
public:
    static int32_t lastPlatformVersion_;

    static void SetUpTestCase();
    static void TearDownTestCase();
    static void SetSheetTheme(RefPtr<SheetTheme> sheetTheme);
    void SetUp() override;
    void TearDown() override;
};

int32_t SheetContentCoverObjectTestNG::lastPlatformVersion_ = 0;

/**
 * @brief: Called once before executing the entire test suite
 * @note: All TEST_F shared.
 *        Initialize the global commons.
 */
void SheetContentCoverObjectTestNG::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    SheetContentCoverObjectTestNG::lastPlatformVersion_ = PipelineBase::GetCurrentContext()->GetMinPlatformVersion();
}

/**
 * @brief: Called once after executing the entire test suite
 * @note: All TEST_F shared.
 *        Clean up the global commons.
 */
void SheetContentCoverObjectTestNG::TearDownTestCase()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

// Before each TEST_F, the scope is a single test case
void SheetContentCoverObjectTestNG::SetUp() {}

// After each TEST_F, the scope is a single test case
void SheetContentCoverObjectTestNG::TearDown()
{
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(SheetContentCoverObjectTestNG::lastPlatformVersion_);
    MockPipelineContext::GetCurrent()->SetThemeManager(nullptr);
}

void SheetContentCoverObjectTestNG::SetSheetTheme(RefPtr<SheetTheme> sheetTheme)
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
 * @tc.name: InitScrollProps001
 * @tc.desc: Test SheetObject::InitScrollProps Function
 * @tc.type: FUNC
 */
HWTEST_F(SheetContentCoverObjectTestNG, InitScrollProps001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet pattern and scroll pattern.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 201,
        AceType::MakeRefPtr<SheetPresentationPattern>(301, "SheetObject", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto scrollNode =
        FrameNode::CreateFrameNode("Scroll", 501, AceType::MakeRefPtr<ScrollPattern>());
    ASSERT_NE(scrollNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto scrollPattern = scrollNode->GetPattern<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    sheetPattern->SetScrollNode(WeakPtr<FrameNode>(scrollNode));
    /**
     * @tc.steps: step2. initial and get sheet object and set sheetEffectEdge_ is SheetEffectEdge::NONE.
     */
    sheetPattern->InitSheetObject();
    auto sheetObject = sheetPattern->GetSheetObject();
    ASSERT_NE(sheetObject, nullptr);
    sheetPattern->sheetEffectEdge_ = SheetEffectEdge::NONE;
    /**
     * @tc.steps: step3. test initialization operation.
     * @tc.expected: edgeEffect_ = EdgeEffect::NONE, edgeEffectAlwaysEnabled_ = false
     *               and effectEdge_ = EffectEdge::ALL.
     */
    sheetObject->InitScrollProps();
    EXPECT_EQ(scrollPattern->edgeEffect_, EdgeEffect::NONE);
    EXPECT_FALSE(scrollPattern->edgeEffectAlwaysEnabled_);
    EXPECT_EQ(scrollPattern->effectEdge_, EffectEdge::ALL);
}

/**
 * @tc.name: InitScrollProps002
 * @tc.desc: Test SheetObject::InitScrollProps Function
 * @tc.type: FUNC
 */
HWTEST_F(SheetContentCoverObjectTestNG, InitScrollProps002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet pattern and scroll pattern.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 201,
        AceType::MakeRefPtr<SheetPresentationPattern>(301, "SheetObject", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto scrollNode =
        FrameNode::CreateFrameNode("Scroll", 501, AceType::MakeRefPtr<ScrollPattern>());
    ASSERT_NE(scrollNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto scrollPattern = scrollNode->GetPattern<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    sheetPattern->SetScrollNode(WeakPtr<FrameNode>(scrollNode));
    /**
     * @tc.steps: step2. initial and get sheet object and set sheetEffectEdge_ is SheetEffectEdge::ALL.
     */
    sheetPattern->InitSheetObject();
    auto sheetObject = sheetPattern->GetSheetObject();
    ASSERT_NE(sheetObject, nullptr);
    sheetPattern->sheetEffectEdge_ = SheetEffectEdge::ALL;
    /**
     * @tc.steps: step3. test initialization operation.
     * @tc.expected: edgeEffect_ = EdgeEffect::SPRING, edgeEffectAlwaysEnabled_ = false
     *               and effectEdge_ = EffectEdge::ALL.
     */
    sheetObject->InitScrollProps();
    EXPECT_EQ(scrollPattern->edgeEffect_, EdgeEffect::SPRING);
    EXPECT_FALSE(scrollPattern->edgeEffectAlwaysEnabled_);
    EXPECT_EQ(scrollPattern->effectEdge_, EffectEdge::ALL);
}

/**
 * @tc.name: InitScrollProps003
 * @tc.desc: Test SheetContentCoverObject::InitScrollProps Function
 * @tc.type: FUNC
 */
HWTEST_F(SheetContentCoverObjectTestNG, InitScrollProps003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet pattern and scroll pattern.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 201,
        AceType::MakeRefPtr<SheetPresentationPattern>(301, "SheetObject", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto scrollNode =
        FrameNode::CreateFrameNode("Scroll", 501, AceType::MakeRefPtr<ScrollPattern>());
    ASSERT_NE(scrollNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto scrollPattern = scrollNode->GetPattern<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    sheetPattern->SetScrollNode(WeakPtr<FrameNode>(scrollNode));
    /**
     * @tc.steps: step2. create scrollableEvent, initial and get sheet object,
     *                   set sheetType_ is SheetType::SHEET_CONTENT_COVER.
     */
    sheetPattern->sheetType_ = SheetType::SHEET_CONTENT_COVER;
    sheetPattern->InitSheetObject();
    auto object = AceType::DynamicCast<SheetContentCoverObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    auto scrollableEvent = AceType::MakeRefPtr<ScrollableEvent>(Axis::FREE);
    scrollPattern->scrollableEvent_ = scrollableEvent;
    /**
     * @tc.steps: step. InitScrollProps.
     * @tc.expected: scrollPattern->edgeEffect_ = EdgeEffect::NONE,
     *               scrollPattern->edgeEffectAlwaysEnabled_ = false,
     *               scrollPattern->effectEdge_ = EffectEdge::ALL,
     *               scrollPattern->scrollableEvent_->GetEnabled() = false.
     */
    object->InitScrollProps();
    EXPECT_EQ(scrollPattern->edgeEffect_, EdgeEffect::NONE);
    EXPECT_FALSE(scrollPattern->edgeEffectAlwaysEnabled_);
    EXPECT_EQ(scrollPattern->effectEdge_, EffectEdge::ALL);
    EXPECT_FALSE(scrollPattern->scrollableEvent_->GetEnabled());
}

/**
 * @tc.name: PostProcessBorderWidth001
 * @tc.desc: Test SheetContentCoverObject::PostProcessBorderWidth
 * @tc.type: FUNC
 */
HWTEST_F(SheetContentCoverObjectTestNG, PostProcessBorderWidth001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet pattern and object.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->sheetType_ = SheetType::SHEET_CONTENT_COVER;
    sheetPattern->InitSheetObject();
    auto object = AceType::DynamicCast<SheetContentCoverObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    /**
     * @tc.steps: step2. test the setting of border width.
     * @tc.expected: topDimen = 0.0_vp, bottomDimen = 0.0_vp, leftDimen = 0.0_vp
     *               and rightDimen = 0.0_vp.
     */
    auto result = object->PostProcessBorderWidth(NG::BorderWidthProperty());
    EXPECT_EQ(result.topDimen, 0.0_vp);
    EXPECT_EQ(result.bottomDimen, 0.0_vp);
    EXPECT_EQ(result.leftDimen, 0.0_vp);
    EXPECT_EQ(result.rightDimen, 0.0_vp);
}

/**
 * @tc.name: FireHeightDidChange001
 * @tc.desc: Test SheetContentCoverObject::FireHeightDidChange
 * @tc.type: FUNC
 */
HWTEST_F(SheetContentCoverObjectTestNG, FireHeightDidChange001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet pattern and object.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->sheetType_ = SheetType::SHEET_CONTENT_COVER;
    sheetPattern->InitSheetObject();
    auto object = AceType::DynamicCast<SheetContentCoverObject>(sheetPattern->GetSheetObject());
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
 * @tc.name: DirtyLayoutProcess001
 * @tc.desc: Test SheetContentCoverObject::DirtyLayoutProcess
 * @tc.type: FUNC
 */
HWTEST_F(SheetContentCoverObjectTestNG, DirtyLayoutProcess001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet pattern and object.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->sheetType_ = SheetType::SHEET_CONTENT_COVER;
    sheetPattern->InitSheetObject();
    auto object = AceType::DynamicCast<SheetContentCoverObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    /**
     * @tc.steps: step2. create renderContext, layoutAlgorithmT and layoutAlgorithmWrapper,
     *                   set sheetHeight_ is 1.0f.
     */
    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto layoutAlgorithmT = AceType::MakeRefPtr<SheetContentCoverLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithmT, nullptr);
    auto layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithmT);
    ASSERT_NE(layoutAlgorithmWrapper, nullptr);
    layoutAlgorithmT->sheetHeight_ = 1.0f;
    /**
     * @tc.steps: step. DirtyLayoutProcess.
     * @tc.expected: sheetHeight_ = 1.0f.
     */
    object->DirtyLayoutProcess(layoutAlgorithmWrapper);
    EXPECT_EQ(object->sheetHeight_, 1.0f);
}

/**
 * @tc.name: DirtyLayoutProcess002
 * @tc.desc: Test SheetContentCoverObject::DirtyLayoutProcess
 * @tc.type: FUNC
 */
HWTEST_F(SheetContentCoverObjectTestNG, DirtyLayoutProcess002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet pattern and object.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->sheetType_ = SheetType::SHEET_CONTENT_COVER;
    sheetPattern->InitSheetObject();
    auto object = AceType::DynamicCast<SheetContentCoverObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    /**
     * @tc.steps: step2. create renderContext, layoutAlgorithmT and layoutAlgorithmWrapper.
     */
    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto layoutAlgorithmT = AceType::MakeRefPtr<SheetContentCoverLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithmT, nullptr);
    auto layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithmT);
    ASSERT_NE(layoutAlgorithmWrapper, nullptr);
    /**
     * @tc.steps: step. DirtyLayoutProcess.
     * @tc.expected: GetTransformTranslate()->x.ConvertToPx() = 0.0f,
     *               GetTransformTranslate()->y.ConvertToPx() = 0.0f,
     *               GetTransformTranslate()->z.ConvertToPx() = 0.0f.
     */
    object->DirtyLayoutProcess(layoutAlgorithmWrapper);
    EXPECT_EQ(renderContext->GetTransformTranslate()->x.ConvertToPx(), 0.0f);
    EXPECT_EQ(renderContext->GetTransformTranslate()->y.ConvertToPx(), 0.0f);
    EXPECT_EQ(renderContext->GetTransformTranslate()->z.ConvertToPx(), 0.0f);
}

/**
 * @tc.name: ContentCoverClipSheetNode
 * @tc.desc: Test SheetContentCoverObject::ClipSheetNode
 * @tc.type: FUNC
 */
HWTEST_F(SheetContentCoverObjectTestNG, ContentCoverClipSheetNode, TestSize.Level1)
{
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    SheetContentCoverObjectTestNG::SetSheetTheme(sheetTheme);
    /**
     * @tc.steps: step1. create sheet pattern and layoutProperty.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    /**
     * @tc.steps: step2. create and initial borderRadius, create sheetStyle and set radius is borderRadius,
     *                   set sheetType_ is SheetType::SHEET_CONTENT_COVER.
     */
    BorderRadiusProperty borderRadius(5.0_vp);
    SheetStyle sheetStyle;
    sheetStyle.radius = borderRadius;
    layoutProperty->UpdateSheetStyle(sheetStyle);
    sheetPattern->sheetType_ = SheetType::SHEET_CONTENT_COVER;
    /**
     * @tc.steps: step3. create object and renderContext.
    * @tc.expected: GetBorderRadius is std::nullopt.
     */
    sheetPattern->InitSheetObject();
    auto object = AceType::DynamicCast<SheetContentCoverObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_TRUE(renderContext->GetBorderRadius() == std::nullopt);
    /**
     * @tc.steps: step4. set radius is 0.0_px and test BorderRadius.
     * @tc.expected: radiusTopLeft = 0.0_px, radiusTopRight = 0.0_px, radiusBottomLeft = 0.0_px,
     *               radiusBottomRight = 0.0_px, GetClipShape is nullptr and GetBackShadow is Shadow.
     */
    Dimension radius = 0.0_px;
    object->ClipSheetNode();
    EXPECT_FLOAT_EQ(renderContext->GetBorderRadius()->radiusTopLeft->ConvertToPx(), radius.ConvertToPx());
    EXPECT_FLOAT_EQ(renderContext->GetBorderRadius()->radiusTopRight->ConvertToPx(), radius.ConvertToPx());
    EXPECT_FLOAT_EQ(renderContext->GetBorderRadius()->radiusBottomLeft->ConvertToPx(), radius.ConvertToPx());
    EXPECT_FLOAT_EQ(renderContext->GetBorderRadius()->radiusBottomRight->ConvertToPx(), radius.ConvertToPx());
    EXPECT_FLOAT_EQ(renderContext->GetOuterBorderRadius()->radiusTopLeft->ConvertToPx(), radius.ConvertToPx());
    EXPECT_FLOAT_EQ(renderContext->GetOuterBorderRadius()->radiusTopRight->ConvertToPx(), radius.ConvertToPx());
    EXPECT_FLOAT_EQ(renderContext->GetOuterBorderRadius()->radiusBottomLeft->ConvertToPx(), radius.ConvertToPx());
    EXPECT_FLOAT_EQ(renderContext->GetOuterBorderRadius()->radiusBottomRight->ConvertToPx(), radius.ConvertToPx());
    EXPECT_EQ(renderContext->GetClipShape(), nullptr);
    EXPECT_EQ(renderContext->GetBackShadow(), Shadow());
}

/**
 * @tc.name: SetFinishEventForAnimationOption001
 * @tc.desc: Test SheetContentCoverObject::SetFinishEventForAnimationOption
 * @tc.type: FUNC
 */
HWTEST_F(SheetContentCoverObjectTestNG, SetFinishEventForAnimationOption001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet pattern and object.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->sheetType_ = SheetType::SHEET_CONTENT_COVER;
    sheetPattern->InitSheetObject();
    auto object = AceType::DynamicCast<SheetContentCoverObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    AnimationOption option;
    /**
     * @tc.steps: step2. parameter setting for test option.
     * @tc.expected: preWidth_ = 0.0f, preDidHeight_ = 0.0f, isOnAppearing_ is false.
     */
    object->SetFinishEventForAnimationOption(option, true, true);
    EXPECT_NE(option.GetOnFinishEvent(), nullptr);
}

/**
 * @tc.name: SetFinishEventForAnimationOption002
 * @tc.desc: Test SheetContentCoverObject::SetFinishEventForAnimationOption
 * @tc.type: FUNC
 */
HWTEST_F(SheetContentCoverObjectTestNG, SetFinishEventForAnimationOption002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet pattern, object and container.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->sheetType_ = SheetType::SHEET_CONTENT_COVER;
    sheetPattern->InitSheetObject();
    auto object = AceType::DynamicCast<SheetContentCoverObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    AnimationOption option;
    /**
     * @tc.steps: step2. parameter setting for test option.
     * @tc.expected: RequestAutoSave is false, isOnDisappearing_ is false.
     */
    object->SetFinishEventForAnimationOption(option, false, true);
    EXPECT_NE(option.GetOnFinishEvent(), nullptr);
}

/**
 * @tc.name: GetAnimationOptionForOverlay001
 * @tc.desc: Test SheetContentCoverObject::GetAnimationOptionForOverlay
 * @tc.type: FUNC
 */
HWTEST_F(SheetContentCoverObjectTestNG, GetAnimationOptionForOverlay001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet pattern and layoutProperty.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    /**
     * @tc.steps: step2. create sheetStyle, set modalTransition is ModalTransition::ALPHA,
     *                   set sheetType_ is SheetType::SHEET_CONTENT_COVER.
     */
    SheetStyle sheetStyle;
    sheetStyle.modalTransition = ModalTransition::ALPHA;
    layoutProperty->UpdateSheetStyle(sheetStyle);
    sheetPattern->sheetType_ = SheetType::SHEET_CONTENT_COVER;
    /**
     * @tc.steps: step3. InitSheetObject and create object.
     */
    sheetPattern->InitSheetObject();
    auto object = AceType::DynamicCast<SheetContentCoverObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    /**
     * @tc.steps: step4. parameter setting for test option.
     * @tc.expected: GetCurve is Curves::FRICTION, GetDuration is 200, GetFillMode is FillMode::FORWARDS.
     */
    auto option = object->GetAnimationOptionForOverlay(true, true);
    EXPECT_EQ(option.GetCurve(), Curves::FRICTION);
    EXPECT_EQ(option.GetDuration(), 200);
    EXPECT_EQ(option.GetFillMode(), FillMode::FORWARDS);
}

/**
 * @tc.name: GetAnimationOptionForOverlay002
 * @tc.desc: Test SheetContentCoverObject::GetAnimationOptionForOverlay
 * @tc.type: FUNC
 */
HWTEST_F(SheetContentCoverObjectTestNG, GetAnimationOptionForOverlay002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet pattern and layoutProperty.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    /**
     * @tc.steps: step2. create sheetStyle, set modalTransition is ModalTransition::NONE,
     *                   set sheetType_ is SheetType::SHEET_CONTENT_COVER.
     */
    SheetStyle sheetStyle;
    sheetStyle.modalTransition = ModalTransition::NONE;
    layoutProperty->UpdateSheetStyle(sheetStyle);
    sheetPattern->sheetType_ = SheetType::SHEET_CONTENT_COVER;
    /**
     * @tc.steps: step3. InitSheetObject and create object.
     */
    sheetPattern->InitSheetObject();
    auto object = AceType::DynamicCast<SheetContentCoverObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    /**
     * @tc.steps: step4. parameter setting for test option.
     * @tc.expected: GetDuration is 0.
     */
    auto option = object->GetAnimationOptionForOverlay(true, true);
    EXPECT_EQ(option.GetDuration(), 0);
}

/**
 * @tc.name: GetAnimationOptionForOverlay003
 * @tc.desc: Test SheetContentCoverObject::GetAnimationOptionForOverlay
 * @tc.type: FUNC
 */
HWTEST_F(SheetContentCoverObjectTestNG, GetAnimationOptionForOverlay003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet pattern and layoutProperty.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    /**
     * @tc.steps: step2. create sheetStyle, set modalTransition is ModalTransition::DEFAULT,
     *                   set sheetType_ is SheetType::SHEET_CONTENT_COVER.
     */
    SheetStyle sheetStyle;
    sheetStyle.modalTransition = ModalTransition::DEFAULT;
    layoutProperty->UpdateSheetStyle(sheetStyle);
    sheetPattern->sheetType_ = SheetType::SHEET_CONTENT_COVER;
    /**
     * @tc.steps: step3. InitSheetObject and create object.
     */
    sheetPattern->InitSheetObject();
    auto object = AceType::DynamicCast<SheetContentCoverObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    /**
     * @tc.steps: step4. parameter setting for test option, GetCurve and create springCurve.
     * @tc.expected: springCurve is not nullptr, velocity_ is 0.0f, mass_ is 1.0f, stiffness_ is 328.0f,
     *               damping_ is 36.0f, GetFillMode is FillMode::FORWARDS.
     */
    auto option = object->GetAnimationOptionForOverlay(true, true);
    auto curve = option.GetCurve();
    auto springCurve = AceType::DynamicCast<InterpolatingSpring>(curve);
    ASSERT_NE(springCurve, nullptr);
    EXPECT_EQ(springCurve->velocity_, 0.0f);
    EXPECT_EQ(springCurve->mass_, 1.0f);
    EXPECT_EQ(springCurve->stiffness_, 328.0f);
    EXPECT_EQ(springCurve->damping_, 36.0f);
    EXPECT_EQ(option.GetFillMode(), FillMode::FORWARDS);
}

/**
 * @tc.name: InitAnimationForOverlay001
 * @tc.desc: Test SheetContentCoverObject::InitAnimationForOverlay
 * @tc.type: FUNC
 */
HWTEST_F(SheetContentCoverObjectTestNG, InitAnimationForOverlay001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet pattern and layoutProperty.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    /**
     * @tc.steps: step2. create sheetStyle, set modalTransition is ModalTransition::ALPHA,
     *                   set sheetType_ is SheetType::SHEET_CONTENT_COVER.
     */
    SheetStyle sheetStyle;
    sheetStyle.modalTransition = ModalTransition::ALPHA;
    layoutProperty->UpdateSheetStyle(sheetStyle);
    sheetPattern->sheetType_ = SheetType::SHEET_CONTENT_COVER;
    /**
     * @tc.steps: step3. InitSheetObject, create object and renderContext.
     */
    sheetPattern->InitSheetObject();
    auto object = AceType::DynamicCast<SheetContentCoverObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    /**
     * @tc.steps: step4. set isTransition is true, set isFirstTransition is true, test the setting of opacity.
     * @tc.expected: the value of opacity is 0.0.
     */
    object->InitAnimationForOverlay(true, true);
    EXPECT_EQ(renderContext->GetOpacity().value(), 0.0);
}

/**
 * @tc.name: InitAnimationForOverlay002
 * @tc.desc: Test SheetContentCoverObject::InitAnimationForOverlay
 * @tc.type: FUNC
 */
HWTEST_F(SheetContentCoverObjectTestNG, InitAnimationForOverlay002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet pattern and layoutProperty.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    /**
     * @tc.steps: step2. create sheetStyle, set modalTransition is ModalTransition::ALPHA,
     *                   set sheetType_ is SheetType::SHEET_CONTENT_COVER.
     */
    SheetStyle sheetStyle;
    sheetStyle.modalTransition = ModalTransition::ALPHA;
    layoutProperty->UpdateSheetStyle(sheetStyle);
    sheetPattern->sheetType_ = SheetType::SHEET_CONTENT_COVER;
    /**
     * @tc.steps: step3. InitSheetObject, create object and renderContext.
     */
    sheetPattern->InitSheetObject();
    auto object = AceType::DynamicCast<SheetContentCoverObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    /**
     * @tc.steps: step4. set isTransition is false, set isFirstTransition is true, test the setting of opacity.
     * @tc.expected: the value of opacity is 1.0.
     */
    object->InitAnimationForOverlay(false, true);
    EXPECT_EQ(renderContext->GetOpacity().value(), 1.0);
}

/**
 * @tc.name: InitAnimationForOverlay003
 * @tc.desc: Test SheetContentCoverObject::InitAnimationForOverlay
 * @tc.type: FUNC
 */
HWTEST_F(SheetContentCoverObjectTestNG, InitAnimationForOverlay003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet pattern and layoutProperty.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    /**
     * @tc.steps: step2. create sheetStyle, set modalTransition is ModalTransition::NONE,
     *                   set sheetType_ is SheetType::SHEET_CONTENT_COVER.
     */
    SheetStyle sheetStyle;
    sheetStyle.modalTransition = ModalTransition::NONE;
    layoutProperty->UpdateSheetStyle(sheetStyle);
    sheetPattern->sheetType_ = SheetType::SHEET_CONTENT_COVER;
    /**
     * @tc.steps: step3. InitSheetObject, create object and renderContext.
     */
    sheetPattern->InitSheetObject();
    auto object = AceType::DynamicCast<SheetContentCoverObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    /**
     * @tc.steps: step4. set isTransition is true, set isFirstTransition is true, test the setting of opacity.
     * @tc.expected: the value of opacity is 1.0.
     */
    object->InitAnimationForOverlay(true, true);
    EXPECT_EQ(renderContext->GetOpacity().value(), 1.0);
}

/**
 * @tc.name: InitAnimationForOverlay004
 * @tc.desc: Test SheetContentCoverObject::InitAnimationForOverlay
 * @tc.type: FUNC
 */
HWTEST_F(SheetContentCoverObjectTestNG, InitAnimationForOverlay004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet pattern and layoutProperty.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    /**
     * @tc.steps: step2. create sheetStyle, set modalTransition is ModalTransition::NONE,
     *                   set sheetType_ is SheetType::SHEET_CONTENT_COVER.
     */
    SheetStyle sheetStyle;
    sheetStyle.modalTransition = ModalTransition::NONE;
    layoutProperty->UpdateSheetStyle(sheetStyle);
    sheetPattern->sheetType_ = SheetType::SHEET_CONTENT_COVER;
    /**
     * @tc.steps: step3. InitSheetObject, create object and renderContext.
     */
    sheetPattern->InitSheetObject();
    auto object = AceType::DynamicCast<SheetContentCoverObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    /**
     * @tc.steps: step4. set isTransition is false, set isFirstTransition is true, test the setting of opacity.
     * @tc.expected: the value of opacity is 0.0.
     */
    object->InitAnimationForOverlay(false, true);
    EXPECT_EQ(renderContext->GetOpacity().value(), 0.0);
}

/**
 * @tc.name: InitAnimationForOverlay005
 * @tc.desc: Test SheetContentCoverObject::InitAnimationForOverlay
 * @tc.type: FUNC
 */
HWTEST_F(SheetContentCoverObjectTestNG, InitAnimationForOverlay005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet pattern and layoutProperty.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    /**
     * @tc.steps: step2. create sheetStyle, set modalTransition is ModalTransition::DEFAULT,
     *                   set sheetType_ is SheetType::SHEET_CONTENT_COVER.
     */
    SheetStyle sheetStyle;
    sheetStyle.modalTransition = ModalTransition::DEFAULT;
    layoutProperty->UpdateSheetStyle(sheetStyle);
    sheetPattern->sheetType_ = SheetType::SHEET_CONTENT_COVER;
    /**
     * @tc.steps: step3. InitSheetObject, create object, renderContext and geometryNode, get height.
     */
    sheetPattern->InitSheetObject();
    auto object = AceType::DynamicCast<SheetContentCoverObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto geometryNode = sheetNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto height = geometryNode->GetFrameSize().Height();
    /**
     * @tc.steps: step4. set isTransition is true, set isFirstTransition is true, test the update function.
     * @tc.expected: x.ConvertToPx() is 0.0f, y.ConvertToPx() is height, z.ConvertToPx() is 0.0f.
     */
    object->InitAnimationForOverlay(true, true);
    EXPECT_EQ(renderContext->GetTransformTranslate()->x.ConvertToPx(), 0.0f);
    EXPECT_EQ(renderContext->GetTransformTranslate()->y.ConvertToPx(), height);
    EXPECT_EQ(renderContext->GetTransformTranslate()->z.ConvertToPx(), 0.0f);
}

/**
 * @tc.name: InitAnimationForOverlay006
 * @tc.desc: Test SheetContentCoverObject::InitAnimationForOverlay
 * @tc.type: FUNC
 */
HWTEST_F(SheetContentCoverObjectTestNG, InitAnimationForOverlay006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet pattern and layoutProperty.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    /**
     * @tc.steps: step2. create sheetStyle, set modalTransition is ModalTransition::DEFAULT,
     *                   set sheetType_ is SheetType::SHEET_CONTENT_COVER.
     */
    SheetStyle sheetStyle;
    sheetStyle.modalTransition = ModalTransition::DEFAULT;
    layoutProperty->UpdateSheetStyle(sheetStyle);
    sheetPattern->sheetType_ = SheetType::SHEET_CONTENT_COVER;
    /**
     * @tc.steps: step3. InitSheetObject, create object and renderContext.
     */
    sheetPattern->InitSheetObject();
    auto object = AceType::DynamicCast<SheetContentCoverObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    /**
     * @tc.steps: step4. set isTransition is true, set isFirstTransition is true, test the update function.
     * @tc.expected: x.ConvertToPx() is 0.0f, y.ConvertToPx() is 0.0f, z.ConvertToPx() is 0.0f.
     */
    object->InitAnimationForOverlay(false, true);
    EXPECT_EQ(renderContext->GetTransformTranslate()->x.ConvertToPx(), 0.0f);
    EXPECT_EQ(renderContext->GetTransformTranslate()->y.ConvertToPx(), 0.0f);
    EXPECT_EQ(renderContext->GetTransformTranslate()->z.ConvertToPx(), 0.0f);
}

/**
 * @tc.name: GetAnimationPropertyCallForOverlay001
 * @tc.desc: Test SheetContentCoverObject::GetAnimationPropertyCallForOverlay
 * @tc.type: FUNC
 */
HWTEST_F(SheetContentCoverObjectTestNG, GetAnimationPropertyCallForOverlay001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet pattern and layoutProperty.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    /**
     * @tc.steps: step2. create sheetStyle, set modalTransition is ModalTransition::ALPHA,
     *                   set sheetType_ is SheetType::SHEET_CONTENT_COVER.
     */
    SheetStyle sheetStyle;
    sheetStyle.modalTransition = ModalTransition::ALPHA;
    layoutProperty->UpdateSheetStyle(sheetStyle);
    sheetPattern->sheetType_ = SheetType::SHEET_CONTENT_COVER;
    /**
     * @tc.steps: step3. initial and create object.
     */
    sheetPattern->InitSheetObject();
    auto object = AceType::DynamicCast<SheetContentCoverObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    /**
     * @tc.steps: step4. set isTransitionIn is true, test the setting of opacity.
     * @tc.expected: the value of opacity is 1.0f.
     */
    auto callback1 = object->GetAnimationPropertyCallForOverlay(true);
    ASSERT_NE(callback1, nullptr);
    callback1();
    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetOpacity().value(), 1.0f);
}

/**
 * @tc.name: GetAnimationPropertyCallForOverlay002
 * @tc.desc: Test SheetContentCoverObject::GetAnimationPropertyCallForOverlay
 * @tc.type: FUNC
 */
HWTEST_F(SheetContentCoverObjectTestNG, GetAnimationPropertyCallForOverlay002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet pattern and layoutProperty.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    /**
     * @tc.steps: step2. create sheetStyle, set modalTransition is ModalTransition::ALPHA,
     *                   set sheetType_ is SheetType::SHEET_CONTENT_COVER.
     */
    SheetStyle sheetStyle;
    sheetStyle.modalTransition = ModalTransition::ALPHA;
    layoutProperty->UpdateSheetStyle(sheetStyle);
    sheetPattern->sheetType_ = SheetType::SHEET_CONTENT_COVER;
    /**
     * @tc.steps: step3. initial and create object.
     */
    sheetPattern->InitSheetObject();
    auto object = AceType::DynamicCast<SheetContentCoverObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    /**
     * @tc.steps: step4. set isTransitionIn is false, test the setting of opacity.
     * @tc.expected: the value of opacity is 0.0f.
     */
    auto callback1 = object->GetAnimationPropertyCallForOverlay(false);
    ASSERT_NE(callback1, nullptr);
    callback1();
    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetOpacity().value(), 0.0f);
}

/**
 * @tc.name: GetAnimationPropertyCallForOverlay003
 * @tc.desc: Test SheetContentCoverObject::GetAnimationPropertyCallForOverlay
 * @tc.type: FUNC
 */
HWTEST_F(SheetContentCoverObjectTestNG, GetAnimationPropertyCallForOverlay003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet pattern and layoutProperty.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    /**
     * @tc.steps: step2. create sheetStyle, set modalTransition is ModalTransition::NONE,
     *                   set sheetType_ is SheetType::SHEET_CONTENT_COVER.
     */
    SheetStyle sheetStyle;
    sheetStyle.modalTransition = ModalTransition::NONE;
    layoutProperty->UpdateSheetStyle(sheetStyle);
    sheetPattern->sheetType_ = SheetType::SHEET_CONTENT_COVER;
    /**
     * @tc.steps: step3. initial and create object.
     */
    sheetPattern->InitSheetObject();
    auto object = AceType::DynamicCast<SheetContentCoverObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    /**
     * @tc.steps: step4. set isTransitionIn is true, test the setting of opacity.
     * @tc.expected: the value of opacity is 1.0f.
     */
    auto callback1 = object->GetAnimationPropertyCallForOverlay(true);
    ASSERT_NE(callback1, nullptr);
    callback1();
    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetOpacity().value(), 1.0f);
}

/**
 * @tc.name: GetAnimationPropertyCallForOverlay004
 * @tc.desc: Test SheetContentCoverObject::GetAnimationPropertyCallForOverlay
 * @tc.type: FUNC
 */
HWTEST_F(SheetContentCoverObjectTestNG, GetAnimationPropertyCallForOverlay004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet pattern and layoutProperty.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    /**
     * @tc.steps: step2. create sheetStyle, set modalTransition is ModalTransition::NONE,
     *                   set sheetType_ is SheetType::SHEET_CONTENT_COVER.
     */
    SheetStyle sheetStyle;
    sheetStyle.modalTransition = ModalTransition::NONE;
    layoutProperty->UpdateSheetStyle(sheetStyle);
    sheetPattern->sheetType_ = SheetType::SHEET_CONTENT_COVER;
    /**
     * @tc.steps: step3. initial and create object.
     */
    sheetPattern->InitSheetObject();
    auto object = AceType::DynamicCast<SheetContentCoverObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    /**
     * @tc.steps: step4. set isTransitionIn is false, test the setting of opacity.
     * @tc.expected: the value of opacity is 0.0f.
     */
    auto callback1 = object->GetAnimationPropertyCallForOverlay(false);
    ASSERT_NE(callback1, nullptr);
    callback1();
    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetOpacity().value(), 0.0f);
}

/**
 * @tc.name: GetAnimationPropertyCallForOverlay005
 * @tc.desc: Test SheetContentCoverObject::GetAnimationPropertyCallForOverlay
 * @tc.type: FUNC
 */
HWTEST_F(SheetContentCoverObjectTestNG, GetAnimationPropertyCallForOverlay005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet pattern and layoutProperty.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    /**
     * @tc.steps: step2. create sheetStyle, set modalTransition is ModalTransition::DEFAULT,
     *                   set sheetType_ is SheetType::SHEET_CONTENT_COVER.
     */
    SheetStyle sheetStyle;
    sheetStyle.modalTransition = ModalTransition::DEFAULT;
    layoutProperty->UpdateSheetStyle(sheetStyle);
    sheetPattern->sheetType_ = SheetType::SHEET_CONTENT_COVER;
    /**
     * @tc.steps: step3. initial and create object.
     */
    sheetPattern->InitSheetObject();
    auto object = AceType::DynamicCast<SheetContentCoverObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    /**
     * @tc.steps: step4. set isTransitionIn is true, test the update function.
     * @tc.expected: x.ConvertToPx() is 0.0f, y.ConvertToPx() is 0.0f, z.ConvertToPx() is 0.0f.
     */
    auto callback1 = object->GetAnimationPropertyCallForOverlay(true);
    ASSERT_NE(callback1, nullptr);
    callback1();
    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetTransformTranslate()->x.ConvertToPx(), 0.0f);
    EXPECT_EQ(renderContext->GetTransformTranslate()->y.ConvertToPx(), 0.0f);
    EXPECT_EQ(renderContext->GetTransformTranslate()->z.ConvertToPx(), 0.0f);
}

/**
 * @tc.name: GetAnimationPropertyCallForOverlay006
 * @tc.desc: Test SheetContentCoverObject::GetAnimationPropertyCallForOverlay
 * @tc.type: FUNC
 */
HWTEST_F(SheetContentCoverObjectTestNG, GetAnimationPropertyCallForOverlay006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet pattern and layoutProperty.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    /**
     * @tc.steps: step2. create sheetStyle, set modalTransition is ModalTransition::DEFAULT,
     *                   set sheetType_ is SheetType::SHEET_CONTENT_COVER.
     */
    SheetStyle sheetStyle;
    sheetStyle.modalTransition = ModalTransition::DEFAULT;
    layoutProperty->UpdateSheetStyle(sheetStyle);
    sheetPattern->sheetType_ = SheetType::SHEET_CONTENT_COVER;
    /**
     * @tc.steps: step3. InitSheetObject, create object and geometryNode,get height.
     */
    sheetPattern->InitSheetObject();
    auto object = AceType::DynamicCast<SheetContentCoverObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    auto geometryNode = sheetNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto height = geometryNode->GetFrameSize().Height();
    /**
     * @tc.steps: step4. set isTransitionIn is false, test the update function.
     * @tc.expected: x.ConvertToPx() is 0.0f, y.ConvertToPx() is height, z.ConvertToPx() is 0.0f.
     */
    auto callback1 = object->GetAnimationPropertyCallForOverlay(false);
    ASSERT_NE(callback1, nullptr);
    callback1();
    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetTransformTranslate()->x.ConvertToPx(), 0.0f);
    EXPECT_EQ(renderContext->GetTransformTranslate()->y.ConvertToPx(), height);
    EXPECT_EQ(renderContext->GetTransformTranslate()->z.ConvertToPx(), 0.0f);
}

/**
 * @tc.name: ContentCoverSheetLayoutAlgorithm1
 * @tc.desc: ContentCoverSheetLayoutAlgorithm Width Measure
 * @tc.type: FUNC
 */
HWTEST_F(SheetContentCoverObjectTestNG, ContentCoverSheetLayoutAlgorithm1, TestSize.Level1)
{
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    SheetContentCoverObjectTestNG::SetSheetTheme(sheetTheme);
    /**
     * @tc.steps: step1: create sheetNode, init builder func
     * @tc.expected: targetNode != nullptr
     */
    SheetStyle style;
    auto builder = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto callback = [](const std::string&) {};
    auto sheetNode = SheetView::CreateSheetPage(0, "", builder, builder, std::move(callback), style);
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = AceType::DynamicCast<SheetPresentationProperty>(sheetNode->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = { 1000, 1000 };
    sheetNode->GetGeometryNode()->SetParentLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();
    /**
     * @tc.steps: step2. test sheet width and height are equal to 1000.
     * @tc.expected: sheetWidth_ is 1000, sheetHeight_ is 1000.
     */
    auto algorithm = AceType::MakeRefPtr<SheetContentCoverLayoutAlgorithm>();
    ASSERT_NE(algorithm, nullptr);
    algorithm->Measure(AceType::RawPtr(sheetNode));
    EXPECT_FLOAT_EQ(algorithm->sheetWidth_, 1000);
    EXPECT_FLOAT_EQ(algorithm->sheetHeight_, 1000);
}
} // namespace OHOS::Ace::NG