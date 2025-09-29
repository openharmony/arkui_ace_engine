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
#include <mutex>
#include <optional>
#include <string>

#include "gtest/gtest.h"

#define private public
#define protected public

#include "test/mock/base/mock_foldable_window.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components/common/properties/shadow_config.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_drag_bar_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_view.h"
#include "core/components_ng/pattern/overlay/sheet_wrapper_pattern.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/stage/page_pattern.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
} // namespace

class SheetPresentationTestFourNg : public testing::Test {
public:
    static RefPtr<SheetTheme> sheetTheme_;
    static void SetUpTestCase();
    static void TearDownTestCase();
    static void SetSheetTheme(RefPtr<SheetTheme> sheetTheme);
    static void SetSheetType(RefPtr<SheetPresentationPattern> sheetPattern, SheetType sheetType);

    // static int32_t lastPlatformVersion_;
};

// int32_t SheetPresentationTestFourNg::lastPlatformVersion_ = 12;

RefPtr<SheetTheme> SheetPresentationTestFourNg::sheetTheme_ = nullptr;

void SheetPresentationTestFourNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    sheetTheme_ = AceType::MakeRefPtr<SheetTheme>();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        if (type == SheetTheme::TypeId()) {
            return sheetTheme_;
        } else {
            return nullptr;
        }
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void SheetPresentationTestFourNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void SheetPresentationTestFourNg::SetSheetType(RefPtr<SheetPresentationPattern> sheetPattern, SheetType sheetType)
{
    PipelineBase::GetCurrentContext()->minPlatformVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TWELVE);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    pipelineContext->displayWindowRectInfo_.width_ = SHEET_DEVICE_WIDTH_BREAKPOINT.ConvertToPx();
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    SheetStyle sheetStyle;
    sheetStyle.sheetType = sheetType;
    layoutProperty->propSheetStyle_ = sheetStyle;
    sheetPattern->sheetThemeType_ = "popup";
    Rect windowRect = { 0.0f, 0.0f, SHEET_PC_DEVICE_WIDTH_BREAKPOINT.ConvertToPx(), 0.0f };
    MockPipelineContext::SetCurrentWindowRect(windowRect);
    sheetPattern->sheetKey_.hasValidTargetNode = true;
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    sheetTheme->sheetType_ = "popup";
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    SheetPresentationTestFourNg::SetSheetTheme(sheetTheme);
}

void SheetPresentationTestFourNg::SetSheetTheme(RefPtr<SheetTheme> sheetTheme)
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
 * @tc.name: SetSheetBorderWidth001
 * @tc.desc: Branch:  else if (renderContext->GetBorderWidth().has_value() && !isPartialUpdate)
 *           Condition: (renderContext->GetBorderWidth().has_value() && !isPartialUpdate) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, SetSheetBorderWidth001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    sheetPattern->targetTag_ = "Sheet";
    sheetPattern->targetId_ = 101;
    auto targetNode = FrameNode::GetFrameNode(sheetPattern->targetTag_, sheetPattern->targetId_);
    ASSERT_NE(targetNode, nullptr);

    /**
     * @tc.steps: step2. create sheet object.
     */
    sheetPattern->InitSheetObject();
    ASSERT_NE(sheetPattern->sheetObject_, nullptr);

    /**
     * @tc.steps: step3. set borderWidth.
     */
    BorderWidthProperty borderWidthProperty = { 1.0_vp, 1.0_vp, 1.0_vp, 1.0_vp };
    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdateBorderWidth(borderWidthProperty);

    /**
     * @tc.steps: step4. test SetSheetBorderWidth.
     */
    sheetPattern->SetSheetBorderWidth(false);
    EXPECT_EQ(renderContext->GetBorderWidth().has_value(), true);
    SheetPresentationTestFourNg::TearDownTestCase();
}


/**
 * @tc.name: SetSheetBorderWidth001
 * @tc.desc: Branch:  else if (renderContext->GetBorderWidth().has_value() && !isPartialUpdate)
 *           Condition: (renderContext->GetBorderWidth().has_value() && !isPartialUpdate) = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, SetSheetBorderWidth002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    sheetPattern->targetTag_ = "Sheet";
    sheetPattern->targetId_ = 101;
    auto targetNode = FrameNode::GetFrameNode(sheetPattern->targetTag_, sheetPattern->targetId_);
    ASSERT_NE(targetNode, nullptr);

    /**
     * @tc.steps: step2. create sheet object.
     */
    sheetPattern->InitSheetObject();
    ASSERT_NE(sheetPattern->sheetObject_, nullptr);

    /**
     * @tc.steps: step3. set borderWidth.
     */
    BorderWidthProperty borderWidthProperty = { 1.0_vp, 1.0_vp, 1.0_vp, 1.0_vp };
    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdateBorderWidth(borderWidthProperty);

    /**
     * @tc.steps: step4. test SetSheetBorderWidth.
     */
    sheetPattern->SetSheetBorderWidth(true);
    EXPECT_EQ(renderContext->GetBorderWidth().has_value(), true);
    SheetPresentationTestFourNg::TearDownTestCase();
}


/**
 * @tc.name: SetSheetBorderWidth001
 * @tc.desc: Branch:  else if (renderContext->GetBorderWidth().has_value() && !isPartialUpdate)
 *           Condition: (renderContext->GetBorderWidth().has_value() && !isPartialUpdate) = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, SetSheetBorderWidth003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    sheetPattern->targetTag_ = "Sheet";
    sheetPattern->targetId_ = 101;
    auto targetNode = FrameNode::GetFrameNode(sheetPattern->targetTag_, sheetPattern->targetId_);
    ASSERT_NE(targetNode, nullptr);

    /**
     * @tc.steps: step2. create sheet object.
     */
    sheetPattern->InitSheetObject();
    ASSERT_NE(sheetPattern->sheetObject_, nullptr);

    // /**
    //  * @tc.steps: step3. set borderWidth.
    //  */
    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    /**
     * @tc.steps: step4. test SetSheetBorderWidth.
     */
    sheetPattern->SetSheetBorderWidth(true);
    EXPECT_EQ(renderContext->GetBorderWidth().has_value(), false);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: SetSheetBorderWidth001
 * @tc.desc: Branch:  else if (renderContext->GetBorderWidth().has_value() && !isPartialUpdate)
 *           Condition: (renderContext->GetBorderWidth().has_value() && !isPartialUpdate) = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, SetSheetBorderWidth004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    sheetPattern->targetTag_ = "Sheet";
    sheetPattern->targetId_ = 101;
    auto targetNode = FrameNode::GetFrameNode(sheetPattern->targetTag_, sheetPattern->targetId_);
    ASSERT_NE(targetNode, nullptr);

    /**
     * @tc.steps: step2. create sheet object.
     */
    sheetPattern->InitSheetObject();
    ASSERT_NE(sheetPattern->sheetObject_, nullptr);

    /**
     * @tc.steps: step3. set borderWidth.
     */
    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    /**
     * @tc.steps: step4. test SetSheetBorderWidth.
     */
    sheetPattern->SetSheetBorderWidth(false);
    EXPECT_EQ(renderContext->GetBorderWidth().has_value(), false);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: SetShadowStyle001
 * @tc.desc: Branch:  if (sheetStyle.shadow.has_value())
 *           Condition: if (sheetStyle.shadow.has_value()) = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, SetShadowStyle001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    sheetPattern->targetTag_ = "Sheet";
    sheetPattern->targetId_ = 101;
    auto targetNode = FrameNode::GetFrameNode(sheetPattern->targetTag_, sheetPattern->targetId_);
    ASSERT_NE(targetNode, nullptr);

    /**
     * @tc.steps: step2. set sheetStyle.
     */
    SheetStyle sheetStyle;
    layoutProperty->propSheetStyle_ = sheetStyle;

    /**
     * @tc.steps: step3. test SetShadowStyle.
     */
    sheetPattern->SetShadowStyle(false);
    EXPECT_EQ(layoutProperty->GetSheetStyleValue().shadow.has_value(), false);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: SetShadowStyle002
 * @tc.desc: Branch:  if (sheetStyle.shadow.has_value())
 *                    if (!isFocused)
 *           Condition: if (sheetStyle.shadow.has_value()) = true
 *                      if (!isFocused) = fasle
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, SetShadowStyle002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    sheetPattern->targetTag_ = "Sheet";
    sheetPattern->targetId_ = 101;
    auto targetNode = FrameNode::GetFrameNode(sheetPattern->targetTag_, sheetPattern->targetId_);
    ASSERT_NE(targetNode, nullptr);

    /**
     * @tc.steps: step2. set shadow.
     */
    Shadow shadow = ShadowConfig::DefaultShadowL;
    SheetStyle sheetStyle;
    sheetStyle.shadow = shadow;
    layoutProperty->propSheetStyle_ = sheetStyle;

    /**
     * @tc.steps: step3. test SetShadowStyle.
     */
    sheetPattern->SetShadowStyle(false);
    EXPECT_EQ(layoutProperty->GetSheetStyleValue().shadow.has_value(), true);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: SetShadowStyle003
 * @tc.desc: Branch:  if (sheetStyle.shadow.has_value())
 *                    if (!isFocused)
 *           Condition: if (sheetStyle.shadow.has_value()) = false
 *                      if (!isFocused) = fasle
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, SetShadowStyle003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    sheetPattern->targetTag_ = "Sheet";
    sheetPattern->targetId_ = 101;
    auto targetNode = FrameNode::GetFrameNode(sheetPattern->targetTag_, sheetPattern->targetId_);
    ASSERT_NE(targetNode, nullptr);

    /**
     * @tc.steps: step2. set shadow.
     */
    SheetStyle sheetStyle;
    sheetStyle.shadow.reset();
    layoutProperty->propSheetStyle_ = sheetStyle;

    /**
     * @tc.steps: step3. test SetShadowStyle.
     */
    sheetPattern->SetShadowStyle(true);
    EXPECT_EQ(layoutProperty->GetSheetStyleValue().shadow.has_value(), false);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: HandleFocusEvent001
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, HandleFocusEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    sheetPattern->targetTag_ = "Sheet";
    sheetPattern->targetId_ = 101;
    auto targetNode = FrameNode::GetFrameNode(sheetPattern->targetTag_, sheetPattern->targetId_);
    ASSERT_NE(targetNode, nullptr);

    /**
     * @tc.steps: step2. set shadow.
     */
    SheetStyle sheetStyle;
    sheetStyle.shadow.reset();
    layoutProperty->propSheetStyle_ = sheetStyle;

    /**
     * @tc.steps: step3. test HandleFocusEvent.
     */
    sheetPattern->HandleFocusEvent();
    EXPECT_EQ(sheetNode->GetId(), 101);
    EXPECT_EQ(layoutProperty->GetSheetStyleValue().shadow.has_value(), false);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: HandleBlurEvent001
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, HandleBlurEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    sheetPattern->targetTag_ = "Sheet";
    sheetPattern->targetId_ = 101;
    auto targetNode = FrameNode::GetFrameNode(sheetPattern->targetTag_, sheetPattern->targetId_);
    ASSERT_NE(targetNode, nullptr);

    /**
     * @tc.steps: step2. reset shadow.
     */
    SheetStyle sheetStyle;
    sheetStyle.shadow.reset();
    layoutProperty->propSheetStyle_ = sheetStyle;

    /**
     * @tc.steps: step3. test HandleFocusEvent.
     */
    sheetPattern->HandleBlurEvent();
    EXPECT_EQ(sheetPattern->keyboardHeight_, 0);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: SendTextUpdateEvent001
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, SendTextUpdateEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    sheetPattern->targetTag_ = "Sheet";
    sheetPattern->targetId_ = 101;
    auto targetNode = FrameNode::GetFrameNode(sheetPattern->targetTag_, sheetPattern->targetId_);
    ASSERT_NE(targetNode, nullptr);

    /**
     * @tc.steps: step2. test SendTextUpdateEvent.
     */
    sheetPattern->SendTextUpdateEvent();
    EXPECT_EQ(sheetPattern->keyboardHeight_, 0);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: UpdateAccessibilityDetents001
 * @tc.desc: Branch:  sheetDetentsSize < 2 || !IsSheetBottomStyle()
 *                    if (NearEqual(height, sheetDetentHeight_[i]))
 *           Condition: sheetDetentsSize < 2 || !IsSheetBottomStyle() = fasle
 *           if (NearEqual(height, sheetDetentHeight_[i])) = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, UpdateAccessibilityDetents001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. Init height and type.
     */
    SheetPresentationTestFourNg::SetSheetType(sheetPattern, SheetType::SHEET_BOTTOM);
    sheetPattern->sheetDetentHeight_.emplace_back(20);
    sheetPattern->sheetDetentHeight_.emplace_back(30);

    /**
     * @tc.steps: step3. test UpdateAccessibilityDetents.
     */
    auto ret = sheetPattern->UpdateAccessibilityDetents(10);
    EXPECT_EQ(ret, false);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: UpdateAccessibilityDetents002
 * @tc.desc: Branch:  sheetDetentsSize < 2 || !IsSheetBottomStyle()
 *           Condition: sheetDetentsSize < 2 || !IsSheetBottomStyle() = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, UpdateAccessibilityDetents002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. Init height and type.
     */
    sheetPattern->sheetDetentHeight_.emplace_back(20);

    /**
     * @tc.steps: step3. test UpdateAccessibilityDetents.
     */
    auto ret = sheetPattern->UpdateAccessibilityDetents(10);
    EXPECT_EQ(ret, false);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: UpdateAccessibilityDetents003
 * @tc.desc: Branch:  sheetDetentsSize < 2 || !IsSheetBottomStyle()
 *                    if (NearEqual(height, sheetDetentHeight_[i]))
 *           Condition: sheetDetentsSize < 2 || !IsSheetBottomStyle() = false
 *           if (NearEqual(height, sheetDetentHeight_[i])) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, UpdateAccessibilityDetents003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. Init height and type.
     */
    SheetPresentationTestFourNg::SetSheetType(sheetPattern, SheetType::SHEET_BOTTOM);
    sheetPattern->sheetDetentHeight_.emplace_back(10);
    sheetPattern->sheetDetentHeight_.emplace_back(20);
    sheetPattern->sheetDetentHeight_.emplace_back(30);

    /**
     * @tc.steps: step3. test UpdateAccessibilityDetents.
     */
    auto ret = sheetPattern->UpdateAccessibilityDetents(10);
    EXPECT_EQ(ret, true);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: GetCurrentBroadcastDetentsIndex001
 * @tc.desc: Branch:  sheetDetentsSize < 2 || !IsSheetBottomStyle()
 *                    if (it != sheetDetentHeight_.end())
 *           Condition: sheetDetentsSize < 2 || !IsSheetBottomStyle() = false
 *          if (it != sheetDetentHeight_.end()) = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, GetCurrentBroadcastDetentsIndex001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. Init height and type.
     */
    SheetPresentationTestFourNg::SetSheetType(sheetPattern, SheetType::SHEET_BOTTOM);
    sheetPattern->height_ = 30.0f;
    sheetPattern->sheetDetentHeight_.emplace_back(10);
    sheetPattern->sheetDetentHeight_.emplace_back(20);
    sheetPattern->sheetDetentHeight_.emplace_back(2);

    /**
     * @tc.steps: step3. test UpdateAccessibilityDetents.
     */
    auto ret = sheetPattern->GetCurrentBroadcastDetentsIndex();
    EXPECT_EQ(ret, 0);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: GetCurrentBroadcastDetentsIndex002
 * @tc.desc: Branch:  sheetDetentsSize < 2 || !IsSheetBottomStyle()
 *           Condition: sheetDetentsSize < 2 || !IsSheetBottomStyle() = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, GetCurrentBroadcastDetentsIndex002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. Init height and type.
     */
    SheetPresentationTestFourNg::SetSheetType(sheetPattern, SheetType::SHEET_BOTTOM);
    sheetPattern->height_ = 30.0f;
    sheetPattern->broadcastPreDetentsIndex_ = 30;
    sheetPattern->sheetDetentHeight_.emplace_back(10);

    /**
     * @tc.steps: step3. test UpdateAccessibilityDetents.
     */
    auto ret = sheetPattern->GetCurrentBroadcastDetentsIndex();
    EXPECT_EQ(ret, 30);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: GetCurrentBroadcastDetentsIndex003
 * @tc.desc: Branch:  sheetDetentsSize < 2 || !IsSheetBottomStyle()
 *                    if (it != sheetDetentHeight_.end())
 *           Condition: sheetDetentsSize < 2 || !IsSheetBottomStyle() = false
 *          if (it != sheetDetentHeight_.end()) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, GetCurrentBroadcastDetentsIndex003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. Init height and type.
     */
    SheetPresentationTestFourNg::SetSheetType(sheetPattern, SheetType::SHEET_BOTTOM);
    sheetPattern->height_ = 10.0f;
    sheetPattern->broadcastPreDetentsIndex_ = 30;
    sheetPattern->sheetDetentHeight_.emplace_back(10);
    sheetPattern->sheetDetentHeight_.emplace_back(20);
    sheetPattern->sheetDetentHeight_.emplace_back(30);

    /**
     * @tc.steps: step3. test UpdateAccessibilityDetents.
     */
    auto ret = sheetPattern->GetCurrentBroadcastDetentsIndex();
    EXPECT_EQ(ret, 0);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name:HandleFollowAccessibilityEvent001
 * @tc.desc: Branch: invalid
 *           Condition: invalid = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, HandleFollowAccessibilityEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. Init height and type.
     */
    SheetPresentationTestFourNg::SetSheetType(sheetPattern, SheetType::SHEET_CENTER);
    sheetPattern->sheetDetentHeight_.emplace_back(1);

    /**
     * @tc.steps: step3. test HandleFollowAccessibilityEvent.
     */
    sheetPattern->HandleFollowAccessibilityEvent(1.0f);
    EXPECT_EQ(sheetPattern->broadcastPreDetentsIndex_, 0);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name:HandleFollowAccessibilityEvent002
 * @tc.desc: Branch: invalid
 *                   if (currHeight < sheetDetentHeight_[0] || currHeight > sheetDetentHeight_[sheetDetentsSize - 1])
 *                      if (GreatNotEqual(std::abs(currHeight - upHeight), std::abs(currHeight - downHeight)))
 *           Condition: invalid = false
 *             (currHeight < sheetDetentHeight_[0] || currHeight > sheetDetentHeight_[sheetDetentsSize - 1]) = false
 *             GreatNotEqual(std::abs(currHeight - upHeight), std::abs(currHeight - downHeight)) == true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, HandleFollowAccessibilityEvent002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. Init height and type.
     */
    SheetPresentationTestFourNg::SetSheetType(sheetPattern, SheetType::SHEET_BOTTOM);
    sheetPattern->sheetDetentHeight_.emplace_back(100);
    sheetPattern->sheetDetentHeight_.emplace_back(300);
    sheetPattern->broadcastPreDetentsIndex_ = 30;

    /**
     * @tc.steps: step3. test HandleFollowAccessibilityEvent.
     */
    sheetPattern->HandleFollowAccessibilityEvent(150.0f);
    EXPECT_EQ(sheetPattern->broadcastPreDetentsIndex_, 0);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name:HandleFollowAccessibilityEvent003
 * @tc.desc: Branch: invalid
 *                   if (currHeight < sheetDetentHeight_[0] || currHeight > sheetDetentHeight_[sheetDetentsSize - 1])
 *                      else if (LessNotEqual(std::abs(currHeight - upHeight), std::abs(currHeight - downHeight)))
 *           Condition: invalid = false
 *             (currHeight < sheetDetentHeight_[0] || currHeight > sheetDetentHeight_[sheetDetentsSize - 1]) = false
 *             LessNotEqual(std::abs(currHeight - upHeight), std::abs(currHeight - downHeight)) == true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, HandleFollowAccessibilityEvent003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. Init height and type.
     */
    SheetPresentationTestFourNg::SetSheetType(sheetPattern, SheetType::SHEET_BOTTOM);
    sheetPattern->sheetDetentHeight_.emplace_back(100);
    sheetPattern->sheetDetentHeight_.emplace_back(300);
    sheetPattern->broadcastPreDetentsIndex_ = 30;

    /**
     * @tc.steps: step3. test HandleFollowAccessibilityEvent.
     */
    sheetPattern->HandleFollowAccessibilityEvent(250.0f);
    EXPECT_EQ(sheetPattern->broadcastPreDetentsIndex_, 1);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name:ChangeSheetPage001
 * @tc.desc: Branch: if (IsAvoidingKeyboard() && keyboardAvoidMode_ == SheetKeyboardAvoidMode::TRANSLATE_AND_SCROLL)
 *           Condition:
                IsAvoidingKeyboard() && keyboardAvoidMode_ == SheetKeyboardAvoidMode::TRANSLATE_AND_SCROLL = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, ChangeSheetPage001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. set keyboardHeight and keyboardAvoidMode_.
     */
    sheetPattern->SetKeyboardHeight(100);
    sheetPattern->keyboardAvoidMode_ = SheetKeyboardAvoidMode::TRANSLATE_AND_SCROLL;

    /**
     * @tc.steps: step3. test ChangeSheetPage.
     */
    sheetPattern->ChangeSheetPage(200.0f);
    EXPECT_EQ(sheetPattern->GetKeyboardHeight(), 100);
    EXPECT_EQ(sheetPattern->GetKeyboardAvoidMode(), SheetKeyboardAvoidMode::TRANSLATE_AND_SCROLL);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name:OnCoordScrollUpdate001
 * @tc.desc: Branch:  if (!GetShowState() || !IsScrollable())
 *           Condition:  if (!GetShowState() || !IsScrollable()) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, OnCoordScrollUpdate001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. set showState
     */
    sheetPattern->SetShowState(false);

    /**
     * @tc.steps: step3. test OnCoordScrollUpdate.
     */
    auto ret  = sheetPattern->OnCoordScrollUpdate(200.0f);
    EXPECT_EQ(ret, false);
    EXPECT_EQ(sheetPattern->GetShowState(), false);
    EXPECT_EQ(sheetPattern->IsScrollable(), false);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name:OnCoordScrollUpdate002
 * @tc.desc: Branch:  if (!GetShowState() || !IsScrollable())
 *           Condition:  if (!GetShowState() || !IsScrollable()) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, OnCoordScrollUpdate002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. set showState and scrollable
     */
    auto scrollNode = FrameNode::GetOrCreateFrameNode(
        V2::SCROLL_ETS_TAG, 1, []() { return AceType::MakeRefPtr<ScrollPattern>(); });
    ASSERT_NE(scrollNode, nullptr);
    auto scrollPattern = scrollNode->GetPattern<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    scrollPattern->scrollableDistance_ = 60.0f;
    sheetPattern->SetScrollNode(WeakPtr<FrameNode>(scrollNode));
    sheetPattern->SetShowState(false);

    /**
     * @tc.steps: step3. test OnCoordScrollUpdate.
     */
    auto ret  = sheetPattern->OnCoordScrollUpdate(200.0f);
    EXPECT_EQ(ret, false);
    EXPECT_EQ(sheetPattern->GetShowState(), false);
    EXPECT_EQ(sheetPattern->IsScrollable(), true);
    EXPECT_EQ(scrollPattern->IsPositiveScrollableDistance(), true);
    EXPECT_EQ(scrollPattern->GetScrollableDistance(), 60.0f);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name:OnCoordScrollUpdate003
 * @tc.desc: Branch:  if (!GetShowState() || !IsScrollable())
 *           Condition:  if (!GetShowState() || !IsScrollable()) = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, OnCoordScrollUpdate003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. set showState and scrollable
     */
    auto scrollNode = FrameNode::GetOrCreateFrameNode(
        V2::SCROLL_ETS_TAG, 1, []() { return AceType::MakeRefPtr<ScrollPattern>(); });
    ASSERT_NE(scrollNode, nullptr);
    auto scrollPattern = scrollNode->GetPattern<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    scrollPattern->scrollableDistance_ = 70.0f;
    sheetPattern->SetScrollNode(WeakPtr<FrameNode>(scrollNode));
    sheetPattern->SetShowState(true);

    /**
     * @tc.steps: step3. test OnCoordScrollUpdate.
     */
    auto ret  = sheetPattern->OnCoordScrollUpdate(200.0f);
    EXPECT_EQ(ret, false);
    EXPECT_EQ(sheetPattern->GetShowState(), true);
    EXPECT_EQ(sheetPattern->IsScrollable(), true);
    EXPECT_EQ(scrollPattern->IsPositiveScrollableDistance(), true);
    EXPECT_EQ(scrollPattern->GetScrollableDistance(), 70.0f);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name:OnCoordScrollUpdate004
 * @tc.desc: Branch:  if (!GetShowState() || !IsScrollable())
 *           Condition:  if (!GetShowState() || !IsScrollable()) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, OnCoordScrollUpdate004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. set showState
     */
    sheetPattern->SetShowState(true);

    /**
     * @tc.steps: step3. test OnCoordScrollUpdate.
     */
    auto ret  = sheetPattern->OnCoordScrollUpdate(200.0f);
    EXPECT_EQ(ret, false);
    EXPECT_EQ(sheetPattern->GetShowState(), true);
    EXPECT_EQ(sheetPattern->IsScrollable(), false);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name:OnCoordScrollUpdate005
 * @tc.desc: Branch:  if (!GetShowState() || !IsScrollable())
 *                    if ((sheetType == SheetType::SHEET_POPUP) || (sheetDetentsSize == 0))
 *           Condition:  if (!GetShowState() || !IsScrollable()) = false
 *           if ((sheetType == SheetType::SHEET_POPUP) || (sheetDetentsSize == 0)) = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, OnCoordScrollUpdate005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. set showState and scrollable
     */
    auto scrollNode = FrameNode::GetOrCreateFrameNode(
        V2::SCROLL_ETS_TAG, 1, []() { return AceType::MakeRefPtr<ScrollPattern>(); });
    ASSERT_NE(scrollNode, nullptr);
    auto scrollPattern = scrollNode->GetPattern<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    scrollPattern->scrollableDistance_ = 90.0f;
    sheetPattern->SetScrollNode(WeakPtr<FrameNode>(scrollNode));
    sheetPattern->SetShowState(true);
    
    /**
     * @tc.steps: step3. set sheetType and sheetDetentsSize = 1
     */
    SheetPresentationTestFourNg::SetSheetType(sheetPattern, SheetType::SHEET_BOTTOM);
    sheetPattern->sheetDetentHeight_.emplace_back(20);

    /**
     * @tc.steps: step4. test OnCoordScrollUpdate.
     */
    auto ret  = sheetPattern->OnCoordScrollUpdate(200.0f);
    EXPECT_EQ(ret, true);
    EXPECT_EQ(sheetPattern->GetSheetType(), SheetType::SHEET_BOTTOM);
    EXPECT_EQ(sheetPattern->sheetDetentHeight_.size(), 1);
    EXPECT_EQ(sheetPattern->GetShowState(), true);
    EXPECT_EQ(sheetPattern->IsScrollable(), true);
    EXPECT_EQ(scrollPattern->IsPositiveScrollableDistance(), true);
    EXPECT_EQ(scrollPattern->GetScrollableDistance(), 90.0f);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name:OnCoordScrollUpdate006
 * @tc.desc: Branch:  if (!GetShowState() || !IsScrollable())
 *                    if ((sheetType == SheetType::SHEET_POPUP) || (sheetDetentsSize == 0))
 *           Condition:  if (!GetShowState() || !IsScrollable()) = false
 *           if ((sheetType == SheetType::SHEET_POPUP) || (sheetDetentsSize == 0)) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, OnCoordScrollUpdate006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. set showState and scrollable
     */
    auto scrollNode = FrameNode::GetOrCreateFrameNode(
        V2::SCROLL_ETS_TAG, 1, []() { return AceType::MakeRefPtr<ScrollPattern>(); });
    ASSERT_NE(scrollNode, nullptr);
    auto scrollPattern = scrollNode->GetPattern<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    scrollPattern->scrollableDistance_ = 90.0f;
    sheetPattern->SetScrollNode(WeakPtr<FrameNode>(scrollNode));
    sheetPattern->SetShowState(true);
    
    /**
     * @tc.steps: step3. set sheetType and sheetDetentsSize = 0
     */
    SheetPresentationTestFourNg::SetSheetType(sheetPattern, SheetType::SHEET_BOTTOM);

    /**
     * @tc.steps: step4. test OnCoordScrollUpdate.
     */
    auto ret  = sheetPattern->OnCoordScrollUpdate(200.0f);
    EXPECT_EQ(ret, false);
    EXPECT_EQ(sheetPattern->GetSheetType(), SheetType::SHEET_BOTTOM);
    EXPECT_EQ(sheetPattern->sheetDetentHeight_.size(), 0);
    EXPECT_EQ(sheetPattern->GetShowState(), true);
    EXPECT_EQ(sheetPattern->IsScrollable(), true);
    EXPECT_EQ(scrollPattern->IsPositiveScrollableDistance(), true);
    EXPECT_EQ(scrollPattern->GetScrollableDistance(), 90.0f);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name:OnCoordScrollUpdate007
 * @tc.desc: Branch:  if (!GetShowState() || !IsScrollable())
 *                    if ((sheetType == SheetType::SHEET_POPUP) || (sheetDetentsSize == 0))
 *           Condition:  if (!GetShowState() || !IsScrollable()) = false
 *           if ((sheetType == SheetType::SHEET_POPUP) || (sheetDetentsSize == 0)) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, OnCoordScrollUpdate007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    PipelineBase::GetCurrentContext()->minPlatformVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TWELVE);

    /**
     * @tc.steps: step2. set showState and scrollable
     */
    auto scrollNode = FrameNode::GetOrCreateFrameNode(
        V2::SCROLL_ETS_TAG, 1, []() { return AceType::MakeRefPtr<ScrollPattern>(); });
    ASSERT_NE(scrollNode, nullptr);
    auto scrollPattern = scrollNode->GetPattern<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    scrollPattern->scrollableDistance_ = 90.0f;
    sheetPattern->SetScrollNode(WeakPtr<FrameNode>(scrollNode));
    sheetPattern->SetShowState(true);
    
    /**
     * @tc.steps: step3. set sheetType and sheetDetentsSize = 3
     */
    SheetPresentationTestFourNg::SetSheetType(sheetPattern, SheetType::SHEET_POPUP);
    sheetPattern->sheetDetentHeight_.emplace_back(10);
    sheetPattern->sheetDetentHeight_.emplace_back(20);
    sheetPattern->sheetDetentHeight_.emplace_back(30);

    /**
     * @tc.steps: step4. test OnCoordScrollUpdate.
     */
    auto ret  = sheetPattern->OnCoordScrollUpdate(200.0f);
    EXPECT_EQ(ret, false);
    EXPECT_EQ(sheetPattern->GetSheetType(), SheetType::SHEET_POPUP);
    EXPECT_EQ(sheetPattern->sheetDetentHeight_.size(), 3);
    EXPECT_EQ(sheetPattern->GetShowState(), true);
    EXPECT_EQ(sheetPattern->IsScrollable(), true);
    EXPECT_EQ(scrollPattern->IsPositiveScrollableDistance(), true);
    EXPECT_EQ(scrollPattern->GetScrollableDistance(), 90.0f);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name:OnCoordScrollUpdate008
 * @tc.desc: Branch:  if (!GetShowState() || !IsScrollable())
 *                    if ((sheetType == SheetType::SHEET_POPUP) || (sheetDetentsSize == 0))
 *           Condition:  if (!GetShowState() || !IsScrollable()) = false
 *           if ((sheetType == SheetType::SHEET_POPUP) || (sheetDetentsSize == 0)) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, OnCoordScrollUpdate008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. set showState and scrollable
     */
    auto scrollNode = FrameNode::GetOrCreateFrameNode(
        V2::SCROLL_ETS_TAG, 1, []() { return AceType::MakeRefPtr<ScrollPattern>(); });
    ASSERT_NE(scrollNode, nullptr);
    auto scrollPattern = scrollNode->GetPattern<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    scrollPattern->scrollableDistance_ = 90.0f;
    sheetPattern->SetScrollNode(WeakPtr<FrameNode>(scrollNode));
    sheetPattern->SetShowState(true);
    
    /**
     * @tc.steps: step3. set sheetType and sheetDetentsSize = 0
     */
    SheetPresentationTestFourNg::SetSheetType(sheetPattern, SheetType::SHEET_POPUP);

    /**
     * @tc.steps: step4. test OnCoordScrollUpdate.
     */
    auto ret  = sheetPattern->OnCoordScrollUpdate(200.0f);
    EXPECT_EQ(ret, false);
    EXPECT_EQ(sheetPattern->GetSheetType(), SheetType::SHEET_POPUP);
    EXPECT_EQ(sheetPattern->sheetDetentHeight_.size(), 0);
    EXPECT_EQ(sheetPattern->GetShowState(), true);
    EXPECT_EQ(sheetPattern->IsScrollable(), true);
    EXPECT_EQ(scrollPattern->IsPositiveScrollableDistance(), true);
    EXPECT_EQ(scrollPattern->GetScrollableDistance(), 90.0f);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name:OnCoordScrollUpdate009
 * @tc.desc: Branch:  if (!GetShowState() || !IsScrollable())
 *                    if ((sheetType == SheetType::SHEET_POPUP) || (sheetDetentsSize == 0))
 *                    if ((NearZero(currentOffset_)) && (LessNotEqual(scrollOffset, 0.0f)) &&
 *                    (GreatOrEqual(height, GetMaxSheetHeightBeforeDragUpdate())))
 *           Condition:  if (!GetShowState() || !IsScrollable()) = false
 *           if ((sheetType == SheetType::SHEET_POPUP) || (sheetDetentsSize == 0)) = false
*            if ((NearZero(currentOffset_)) && (LessNotEqual(scrollOffset, 0.0f)) &&
 *            (GreatOrEqual(height, GetMaxSheetHeightBeforeDragUpdate()))) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, OnCoordScrollUpdate009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. set showState and scrollable
     */
    auto scrollNode = FrameNode::GetOrCreateFrameNode(
        V2::SCROLL_ETS_TAG, 1, []() { return AceType::MakeRefPtr<ScrollPattern>(); });
    ASSERT_NE(scrollNode, nullptr);
    auto scrollPattern = scrollNode->GetPattern<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    scrollPattern->scrollableDistance_ = 100.0f;
    sheetPattern->SetScrollNode(WeakPtr<FrameNode>(scrollNode));
    sheetPattern->SetShowState(true);
    
    /**
     * @tc.steps: step3. set sheetType and sheetDetentsSize = 1
     */
    SheetPresentationTestFourNg::SetSheetType(sheetPattern, SheetType::SHEET_BOTTOM_OFFSET);
    sheetPattern->sheetDetentHeight_.emplace_back(0);
    sheetPattern->currentOffset_ = 0.0f;

    /**
     * @tc.steps: step4. test OnCoordScrollUpdate.
     */
    auto ret  = sheetPattern->OnCoordScrollUpdate(-200.0f);
    EXPECT_EQ(ret, false);
    EXPECT_EQ(sheetPattern->GetSheetType(), SheetType::SHEET_BOTTOM_OFFSET);
    EXPECT_EQ(sheetPattern->sheetDetentHeight_.size(), 1);
    EXPECT_EQ(sheetPattern->GetShowState(), true);
    EXPECT_EQ(sheetPattern->IsScrollable(), true);
    EXPECT_EQ(scrollPattern->IsPositiveScrollableDistance(), true);
    EXPECT_EQ(scrollPattern->GetScrollableDistance(), 100.0f);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name:OnCoordScrollUpdate010
 * @tc.desc: Branch:  if (!GetShowState() || !IsScrollable())
 *                    if ((sheetType == SheetType::SHEET_POPUP) || (sheetDetentsSize == 0))
 *                    if ((NearZero(currentOffset_)) && (LessNotEqual(scrollOffset, 0.0f)) &&
 *                    (GreatOrEqual(height, GetMaxSheetHeightBeforeDragUpdate())))
 *           Condition:  if (!GetShowState() || !IsScrollable()) = false
 *           if ((sheetType == SheetType::SHEET_POPUP) || (sheetDetentsSize == 0)) = false
*            if ((NearZero(currentOffset_)) && (LessNotEqual(scrollOffset, 0.0f)) &&
 *            (GreatOrEqual(height, GetMaxSheetHeightBeforeDragUpdate()))) = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, OnCoordScrollUpdate010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. set showState and scrollable
     */
    auto scrollNode = FrameNode::GetOrCreateFrameNode(
        V2::SCROLL_ETS_TAG, 1, []() { return AceType::MakeRefPtr<ScrollPattern>(); });
    ASSERT_NE(scrollNode, nullptr);
    auto scrollPattern = scrollNode->GetPattern<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    scrollPattern->scrollableDistance_ = 110.0f;
    sheetPattern->SetScrollNode(WeakPtr<FrameNode>(scrollNode));
    sheetPattern->SetShowState(true);
    
    /**
     * @tc.steps: step3. set sheetType and sheetDetentsSize = 1
     */
    SheetPresentationTestFourNg::SetSheetType(sheetPattern, SheetType::SHEET_BOTTOM_OFFSET);
    sheetPattern->sheetDetentHeight_.emplace_back(1000);
    sheetPattern->currentOffset_ = 1.0f;

    /**
     * @tc.steps: step4. test OnCoordScrollUpdate.
     */
    auto ret  = sheetPattern->OnCoordScrollUpdate(200.0f);
    EXPECT_EQ(ret, true);
    EXPECT_EQ(sheetPattern->GetSheetType(), SheetType::SHEET_BOTTOM_OFFSET);
    EXPECT_EQ(sheetPattern->sheetDetentHeight_.size(), 1);
    EXPECT_EQ(scrollPattern->GetScrollableDistance(), 110.0f);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name:OnCoordScrollUpdate011
 * @tc.desc: Branch:  if (!GetShowState() || !IsScrollable())
 *                    if ((sheetType == SheetType::SHEET_POPUP) || (sheetDetentsSize == 0))
 *                    if ((NearZero(currentOffset_)) && (LessNotEqual(scrollOffset, 0.0f)) &&
 *                    (GreatOrEqual(height, GetMaxSheetHeightBeforeDragUpdate())))
 *           Condition:  if (!GetShowState() || !IsScrollable()) = false
 *           if ((sheetType == SheetType::SHEET_POPUP) || (sheetDetentsSize == 0)) = false
*            if ((NearZero(currentOffset_)) && (LessNotEqual(scrollOffset, 0.0f)) &&
 *            (GreatOrEqual(height, GetMaxSheetHeightBeforeDragUpdate()))) = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, OnCoordScrollUpdate011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. set showState and scrollable
     */
    auto scrollNode = FrameNode::GetOrCreateFrameNode(
        V2::SCROLL_ETS_TAG, 1, []() { return AceType::MakeRefPtr<ScrollPattern>(); });
    ASSERT_NE(scrollNode, nullptr);
    auto scrollPattern = scrollNode->GetPattern<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    scrollPattern->scrollableDistance_ = 120.0f;
    sheetPattern->SetScrollNode(WeakPtr<FrameNode>(scrollNode));
    sheetPattern->SetShowState(true);
    
    /**
     * @tc.steps: step3. set sheetType and sheetDetentsSize = 1
     */
    SheetPresentationTestFourNg::SetSheetType(sheetPattern, SheetType::SHEET_BOTTOM_OFFSET);
    sheetPattern->sheetDetentHeight_.emplace_back(0);
    sheetPattern->currentOffset_ = 1.0f;

    /**
     * @tc.steps: step4. test OnCoordScrollUpdate.
     */
    auto ret  = sheetPattern->OnCoordScrollUpdate(200.0f);
    EXPECT_EQ(ret, true);
    EXPECT_EQ(sheetPattern->GetSheetType(), SheetType::SHEET_BOTTOM_OFFSET);
    EXPECT_EQ(sheetPattern->sheetDetentHeight_.size(), 1);
    EXPECT_EQ(scrollPattern->GetScrollableDistance(), 120.0f);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name:OnCoordScrollUpdate012
 * @tc.desc: Branch:  if (!GetShowState() || !IsScrollable())
 *                    if ((sheetType == SheetType::SHEET_POPUP) || (sheetDetentsSize == 0))
 *                    if ((NearZero(currentOffset_)) && (LessNotEqual(scrollOffset, 0.0f)) &&
 *                    (GreatOrEqual(height, GetMaxSheetHeightBeforeDragUpdate())))
 *           Condition:  if (!GetShowState() || !IsScrollable()) = false
 *           if ((sheetType == SheetType::SHEET_POPUP) || (sheetDetentsSize == 0)) = false
*            if ((NearZero(currentOffset_)) && (LessNotEqual(scrollOffset, 0.0f)) &&
 *            (GreatOrEqual(height, GetMaxSheetHeightBeforeDragUpdate()))) = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, OnCoordScrollUpdate012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. set showState and scrollable
     */
    auto scrollNode = FrameNode::GetOrCreateFrameNode(
        V2::SCROLL_ETS_TAG, 1, []() { return AceType::MakeRefPtr<ScrollPattern>(); });
    ASSERT_NE(scrollNode, nullptr);
    auto scrollPattern = scrollNode->GetPattern<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    scrollPattern->scrollableDistance_ = 130.0f;
    sheetPattern->SetScrollNode(WeakPtr<FrameNode>(scrollNode));
    sheetPattern->SetShowState(true);
    
    /**
     * @tc.steps: step3. set sheetType and sheetDetentsSize = 1
     */
    SheetPresentationTestFourNg::SetSheetType(sheetPattern, SheetType::SHEET_BOTTOM_OFFSET);
    sheetPattern->sheetDetentHeight_.emplace_back(150);
    sheetPattern->currentOffset_ = 1.0f;

    /**
     * @tc.steps: step4. test OnCoordScrollUpdate.
     */
    auto ret  = sheetPattern->OnCoordScrollUpdate(-100.0f);
    EXPECT_EQ(ret, true);
    EXPECT_EQ(sheetPattern->GetSheetType(), SheetType::SHEET_BOTTOM_OFFSET);
    EXPECT_EQ(sheetPattern->sheetDetentHeight_.size(), 1);
    EXPECT_EQ(scrollPattern->GetScrollableDistance(), 130.0f);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name:OnCoordScrollUpdate013
 * @tc.desc: Branch:  if (!GetShowState() || !IsScrollable())
 *                    if ((sheetType == SheetType::SHEET_POPUP) || (sheetDetentsSize == 0))
 *                    if ((NearZero(currentOffset_)) && (LessNotEqual(scrollOffset, 0.0f)) &&
 *                    (GreatOrEqual(height, GetMaxSheetHeightBeforeDragUpdate())))
 *           Condition:  if (!GetShowState() || !IsScrollable()) = false
 *           if ((sheetType == SheetType::SHEET_POPUP) || (sheetDetentsSize == 0)) = false
*            if ((NearZero(currentOffset_)) && (LessNotEqual(scrollOffset, 0.0f)) &&
 *            (GreatOrEqual(height, GetMaxSheetHeightBeforeDragUpdate()))) = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, OnCoordScrollUpdate013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. set showState and scrollable
     */
    auto scrollNode = FrameNode::GetOrCreateFrameNode(
        V2::SCROLL_ETS_TAG, 1, []() { return AceType::MakeRefPtr<ScrollPattern>(); });
    ASSERT_NE(scrollNode, nullptr);
    auto scrollPattern = scrollNode->GetPattern<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    scrollPattern->scrollableDistance_ = 140.0f;
    sheetPattern->SetScrollNode(WeakPtr<FrameNode>(scrollNode));
    sheetPattern->SetShowState(true);
    
    /**
     * @tc.steps: step3. set sheetType and sheetDetentsSize = 1
     */
    SheetPresentationTestFourNg::SetSheetType(sheetPattern, SheetType::SHEET_BOTTOM_OFFSET);
    sheetPattern->sheetDetentHeight_.emplace_back(0);
    sheetPattern->currentOffset_ = 123.0f;

    /**
     * @tc.steps: step4. test OnCoordScrollUpdate.
     */
    auto ret  = sheetPattern->OnCoordScrollUpdate(-100.0f);
    EXPECT_EQ(ret, true);
    EXPECT_EQ(sheetPattern->GetSheetType(), SheetType::SHEET_BOTTOM_OFFSET);
    EXPECT_EQ(sheetPattern->sheetDetentHeight_.size(), 1);
    EXPECT_EQ(scrollPattern->GetScrollableDistance(), 140.0f);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name:OnCoordScrollUpdate014
 * @tc.desc: Branch:  if (!GetShowState() || !IsScrollable())
 *                    if ((sheetType == SheetType::SHEET_POPUP) || (sheetDetentsSize == 0))
 *                    if ((NearZero(currentOffset_)) && (LessNotEqual(scrollOffset, 0.0f)) &&
 *                    (GreatOrEqual(height, GetMaxSheetHeightBeforeDragUpdate())))
 *           Condition:  if (!GetShowState() || !IsScrollable()) = false
 *           if ((sheetType == SheetType::SHEET_POPUP) || (sheetDetentsSize == 0)) = false
*            if ((NearZero(currentOffset_)) && (LessNotEqual(scrollOffset, 0.0f)) &&
 *            (GreatOrEqual(height, GetMaxSheetHeightBeforeDragUpdate()))) = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, OnCoordScrollUpdate014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. set showState and scrollable
     */
    auto scrollNode = FrameNode::GetOrCreateFrameNode(
        V2::SCROLL_ETS_TAG, 1, []() { return AceType::MakeRefPtr<ScrollPattern>(); });
    ASSERT_NE(scrollNode, nullptr);
    auto scrollPattern = scrollNode->GetPattern<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    scrollPattern->scrollableDistance_ = 150.0f;
    sheetPattern->SetScrollNode(WeakPtr<FrameNode>(scrollNode));
    sheetPattern->SetShowState(true);
    
    /**
     * @tc.steps: step3. set sheetType and sheetDetentsSize = 1
     */
    SheetPresentationTestFourNg::SetSheetType(sheetPattern, SheetType::SHEET_BOTTOM_OFFSET);
    sheetPattern->sheetDetentHeight_.emplace_back(456);
    sheetPattern->currentOffset_ = 0.0f;

    /**
     * @tc.steps: step4. test OnCoordScrollUpdate.
     */
    auto ret  = sheetPattern->OnCoordScrollUpdate(100.0f);
    EXPECT_EQ(ret, true);
    EXPECT_EQ(sheetPattern->GetSheetType(), SheetType::SHEET_BOTTOM_OFFSET);
    EXPECT_EQ(sheetPattern->sheetDetentHeight_.size(), 1);
    EXPECT_EQ(scrollPattern->GetScrollableDistance(), 150.0f);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name:OnCoordScrollUpdate015
 * @tc.desc: Branch:  if (!GetShowState() || !IsScrollable())
 *                    if ((sheetType == SheetType::SHEET_POPUP) || (sheetDetentsSize == 0))
 *                    if ((NearZero(currentOffset_)) && (LessNotEqual(scrollOffset, 0.0f)) &&
 *                    (GreatOrEqual(height, GetMaxSheetHeightBeforeDragUpdate())))
 *           Condition:  if (!GetShowState() || !IsScrollable()) = false
 *           if ((sheetType == SheetType::SHEET_POPUP) || (sheetDetentsSize == 0)) = false
*            if ((NearZero(currentOffset_)) && (LessNotEqual(scrollOffset, 0.0f)) &&
 *            (GreatOrEqual(height, GetMaxSheetHeightBeforeDragUpdate()))) = false
 * @tc.type: FUNC
 */

HWTEST_F(SheetPresentationTestFourNg, OnCoordScrollUpdate015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. set showState and scrollable
     */
    auto scrollNode = FrameNode::GetOrCreateFrameNode(
        V2::SCROLL_ETS_TAG, 1, []() { return AceType::MakeRefPtr<ScrollPattern>(); });
    ASSERT_NE(scrollNode, nullptr);
    auto scrollPattern = scrollNode->GetPattern<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    scrollPattern->scrollableDistance_ = 150.0f;
    sheetPattern->SetScrollNode(WeakPtr<FrameNode>(scrollNode));
    sheetPattern->SetShowState(true);
    
    /**
     * @tc.steps: step3. set sheetType and sheetDetentsSize = 1
     */
    SheetPresentationTestFourNg::SetSheetType(sheetPattern, SheetType::SHEET_BOTTOM_OFFSET);
    sheetPattern->sheetDetentHeight_.emplace_back(0);
    sheetPattern->currentOffset_ = 0.0f;

    /**
     * @tc.steps: step4. test OnCoordScrollUpdate.
     */
    auto ret  = sheetPattern->OnCoordScrollUpdate(789.0f);
    EXPECT_EQ(ret, true);
    EXPECT_EQ(sheetPattern->GetSheetType(), SheetType::SHEET_BOTTOM_OFFSET);
    EXPECT_EQ(sheetPattern->sheetDetentHeight_.size(), 1);
    EXPECT_EQ(scrollPattern->GetScrollableDistance(), 150.0f);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name:OnCoordScrollUpdate016
 * @tc.desc: Branch:  if (!GetShowState() || !IsScrollable())
 *                    if ((sheetType == SheetType::SHEET_POPUP) || (sheetDetentsSize == 0))
 *                    if ((NearZero(currentOffset_)) && (LessNotEqual(scrollOffset, 0.0f)) &&
 *                    (GreatOrEqual(height, GetMaxSheetHeightBeforeDragUpdate())))
 *           Condition:  if (!GetShowState() || !IsScrollable()) = false
 *           if ((sheetType == SheetType::SHEET_POPUP) || (sheetDetentsSize == 0)) = false
*            if ((NearZero(currentOffset_)) && (LessNotEqual(scrollOffset, 0.0f)) &&
 *            (GreatOrEqual(height, GetMaxSheetHeightBeforeDragUpdate()))) = false
 * @tc.type: FUNC
 */

HWTEST_F(SheetPresentationTestFourNg, OnCoordScrollUpdate016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. set showState and scrollable
     */
    auto scrollNode = FrameNode::GetOrCreateFrameNode(
        V2::SCROLL_ETS_TAG, 1, []() { return AceType::MakeRefPtr<ScrollPattern>(); });
    ASSERT_NE(scrollNode, nullptr);
    auto scrollPattern = scrollNode->GetPattern<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    scrollPattern->scrollableDistance_ = 160.0f;
    sheetPattern->SetScrollNode(WeakPtr<FrameNode>(scrollNode));
    sheetPattern->SetShowState(true);
    
    /**
     * @tc.steps: step3. set sheetType and sheetDetentsSize = 1
     */
    SheetPresentationTestFourNg::SetSheetType(sheetPattern, SheetType::SHEET_BOTTOM_OFFSET);
    sheetPattern->sheetDetentHeight_.emplace_back(135);
    sheetPattern->currentOffset_ = 0.0f;

    /**
     * @tc.steps: step4. test OnCoordScrollUpdate.
     */
    auto ret  = sheetPattern->OnCoordScrollUpdate(-246.0f);
    EXPECT_EQ(ret, true);
    EXPECT_EQ(sheetPattern->GetSheetType(), SheetType::SHEET_BOTTOM_OFFSET);
    EXPECT_EQ(sheetPattern->sheetDetentHeight_.size(), 1);
    EXPECT_EQ(scrollPattern->GetScrollableDistance(), 160.0f);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name:GetWindowButtonRectForAllAPI001
 * @tc.desc: Branch:  if (avoidInfoMgr->NeedAvoidContainerModal() &&
        avoidInfoMgr->GetContainerModalButtonsRect(floatContainerModal, floatButtons))
 *           Condition:  avoidInfoMgr->NeedAvoidContainerModal() = false
        avoidInfoMgr->GetContainerModalButtonsRect(floatContainerModal, floatButtons) = true
 * @tc.type: FUNC
 */

HWTEST_F(SheetPresentationTestFourNg, GetWindowButtonRectForAllAPI001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. init avoidInfoManager
     */
    auto mockContainer = MockContainer::Current();
    ASSERT_NE(mockContainer, nullptr);
    auto pipelineContext = MockPipelineContext::GetCurrent();
    mockContainer->pipelineContext_ = pipelineContext;
    pipelineContext->SetContainerModalButtonsRect(true);
    AceEngine::Get().containerMap_.emplace(1, mockContainer);
    AceEngine::Get().containerMap_.emplace(2, MockContainer::Current());
    auto avoidInfoMgr = pipelineContext->GetAvoidInfoManager();
    ASSERT_NE(avoidInfoMgr, nullptr);
    avoidInfoMgr->avoidInfo_.needAvoid = true;

    /**
     * @tc.steps: step4. test OnCoordScrollUpdate.
     */
    auto rect = RectF(0.0f, 0.0f, 1800.0f, 1020.0f);
    auto ret  = sheetPattern->GetWindowButtonRectForAllAPI(rect);
    EXPECT_EQ(ret, true);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name:GetWindowButtonRectForAllAPI002
 * @tc.desc: Branch:  if (avoidInfoMgr->NeedAvoidContainerModal() &&
        avoidInfoMgr->GetContainerModalButtonsRect(floatContainerModal, floatButtons))
 *           Condition:  avoidInfoMgr->NeedAvoidContainerModal() =false
        avoidInfoMgr->GetContainerModalButtonsRect(floatContainerModal, floatButtons) = false
 * @tc.type: FUNC
 */

HWTEST_F(SheetPresentationTestFourNg, GetWindowButtonRectForAllAPI002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. init avoidInfoManager
     */
    auto mockContainer = MockContainer::Current();
    ASSERT_NE(mockContainer, nullptr);
    auto pipelineContext = MockPipelineContext::GetCurrent();
    mockContainer->pipelineContext_ = pipelineContext;
    pipelineContext->SetContainerModalButtonsRect(true);
    AceEngine::Get().containerMap_.emplace(1, mockContainer);
    AceEngine::Get().containerMap_.emplace(2, MockContainer::Current());
    auto avoidInfoMgr = pipelineContext->GetAvoidInfoManager();
    ASSERT_NE(avoidInfoMgr, nullptr);
    avoidInfoMgr->avoidInfo_.needAvoid = false;

    /**
     * @tc.steps: step4. test OnCoordScrollUpdate.
     */
    auto rect = RectF(0.0f, 0.0f, 1000.0f, 500.0f);
    auto ret  = sheetPattern->GetWindowButtonRectForAllAPI(rect);
    EXPECT_EQ(ret, false);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: ChangeScrollHeight001
 * @tc.desc: Branch: if (sheetType == SheetType::SHEET_POPUP || sheetType == SheetType::SHEET_CENTER ||
 *       sheetType == SheetType::SHEET_BOTTOM_OFFSET)
 *           Condition:  sheetType == SheetType::SHEET_POPUP =true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, ChangeScrollHeight001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFourNg::SetUpTestCase();
    auto rootNode = FrameNode::CreateFrameNode("Root", 11, AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 12,
        AceType::MakeRefPtr<SheetPresentationPattern>(13, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    sheetNode->MountToParent(rootNode);
    auto operationColumn =
        FrameNode::CreateFrameNode("Column", 14, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(operationColumn, nullptr);
    operationColumn->MountToParent(sheetNode);
    auto dragBarNode =
        FrameNode::CreateFrameNode("SheetDragBar", 15, AceType::MakeRefPtr<SheetDragBarPattern>());
    ASSERT_NE(dragBarNode, nullptr);
    dragBarNode->MountToParent(sheetNode);
    auto scrollNode = FrameNode::CreateFrameNode("Scroll", 16, AceType::MakeRefPtr<ScrollPattern>());
    ASSERT_NE(scrollNode, nullptr);
    auto contentNode = FrameNode::GetOrCreateFrameNode("SheetContent", 17,
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(contentNode, nullptr);
    contentNode->MountToParent(scrollNode);
    scrollNode->MountToParent(sheetNode);
    
    /**
     * @tc.steps: step2. Get sheetPattern and set scroll node.
     */
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    sheetPattern->SetScrollNode(WeakPtr<FrameNode>(scrollNode));
    sheetPattern->SetTitleBuilderNode(WeakPtr<FrameNode>(operationColumn));

    /**
     * @tc.steps: step3. init sheetStyle.
     */
    SheetPresentationTestFourNg::SetSheetType(sheetPattern, SheetType::SHEET_POPUP);
    SheetStyle sheetStyle;
    sheetStyle.isTitleBuilder = false;
    layoutProperty->propSheetStyle_ = sheetStyle;
    
    /**
     * @tc.steps: step4. test "ChangeScrollHeight".
     */
    sheetPattern->ChangeScrollHeight(300);
    sheetPattern->resizeDecreasedHeight_ = 200.0f;
    auto scrollLayoutProperty = scrollNode->GetLayoutProperty<ScrollLayoutProperty>();
    ASSERT_NE(scrollLayoutProperty, nullptr);
    EXPECT_EQ(scrollLayoutProperty->GetCalcLayoutConstraint()->selfIdealSize,
        CalcSize(std::nullopt, CalcLength(0)));
    SheetPresentationTestFourNg::TearDownTestCase();
}
}