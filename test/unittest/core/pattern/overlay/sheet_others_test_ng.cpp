/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#include "test/mock/base/mock_subwindow.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components/text/text_theme.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_manager.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_view.h"
#include "core/components_ng/pattern/overlay/sheet_wrapper_pattern.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/sheet/sheet_mask_pattern.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr int32_t ERROR_CODE_NO_ERROR = 0;
constexpr int32_t ERROR_CODE_BIND_SHEET_CONTENT_NOT_FOUND = 120003;
constexpr int32_t NUM_0 = 0;
const std::string TITLE = "title";
const std::string SUBTITLE = "subtitle";

class MockOverlayManager : public OverlayManager {
    DECLARE_ACE_TYPE(MockOverlayManager, OverlayManager);
public:
    explicit MockOverlayManager(const RefPtr<FrameNode>& rootNode) : OverlayManager(rootNode) {}
    bool RemoveModalInOverlay()
    {
        return true;
    }
};

class MockSheetPresentationPattern : public SheetPresentationPattern {
    DECLARE_ACE_TYPE(MockSheetPresentationPattern, SheetPresentationPattern);
public:
    MockSheetPresentationPattern(
        int32_t targetId, const std::string& targetTag, std::function<void(const std::string&)>&& callback)
        : SheetPresentationPattern(targetId, targetTag, std::move(callback)) {}
    RefPtr<MockOverlayManager> GetOverlayManager()
    {
        return AceType::DynamicCast<MockOverlayManager>(overlayManager_.Upgrade());
    }
    bool GetAnimationProcess()
    {
        return SheetPresentationPattern::GetAnimationProcess();
    }
};
} // namespace

class SheetOthersTestNg : public testing::Test {
public:
    static RefPtr<SheetTheme> sheetTheme_;
    static RefPtr<TextTheme> textTheme_;

    static void SetUpTestCase();
    static void TearDownTestCase();
};

RefPtr<SheetTheme> SheetOthersTestNg::sheetTheme_ = nullptr;
RefPtr<TextTheme> SheetOthersTestNg::textTheme_ = nullptr;

void SheetOthersTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    sheetTheme_ = AceType::MakeRefPtr<SheetTheme>();
    textTheme_ = AceType::MakeRefPtr<TextTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        if (type == SheetTheme::TypeId()) {
            return sheetTheme_;
        } else if (type == TextTheme::TypeId()) {
            return textTheme_;
        } else {
            return nullptr;
        }
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void SheetOthersTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: CreateOperationColumnNode001
 * @tc.desc: Branch: if (isTitleBuilder.has_value() && GetFontScale() == GetSheetNormalScale()) = false
 *           Condition: isTitleBuilder.has_value() = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, CreateOperationColumnNode001, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    auto titleBuilder = FrameNode::CreateFrameNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetPresentationPattern>(
        ElementRegister::GetInstance()->MakeUniqueId(), V2::SHEET_WRAPPER_TAG, std::move(callback)));
    auto sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(sheetLayoutProperty, nullptr);
    SheetStyle sheetStyle;
    sheetStyle.isTitleBuilder = std::nullopt;
    sheetLayoutProperty->UpdateSheetStyle(sheetStyle);

    auto operationColumn = SheetView::CreateOperationColumnNode(titleBuilder, sheetStyle, sheetNode);
    ASSERT_NE(operationColumn, nullptr);
    auto columnLayoutProperty = operationColumn->GetLayoutProperty<LinearLayoutProperty>();
    ASSERT_NE(columnLayoutProperty, nullptr);
    EXPECT_EQ(columnLayoutProperty->GetCalcLayoutConstraint(), nullptr);
    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: CreateOperationColumnNode002
 * @tc.desc: Branch: if (isTitleBuilder.has_value() && GetFontScale() == GetSheetNormalScale()) = false
 *           Condition: isTitleBuilder.has_value() = true, GetFontScale() == GetSheetNormalScale() = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, CreateOperationColumnNode002, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    auto titleBuilder = FrameNode::CreateFrameNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetPresentationPattern>(
        ElementRegister::GetInstance()->MakeUniqueId(), V2::SHEET_WRAPPER_TAG, std::move(callback)));
    auto sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(sheetLayoutProperty, nullptr);
    SheetStyle sheetStyle;
    sheetStyle.isTitleBuilder = true;
    sheetLayoutProperty->UpdateSheetStyle(sheetStyle);
    auto pipelineContext = sheetNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->fontScale_ = pipelineContext->GetTheme<SheetTheme>()->GetSheetNormalScale() + 5.0f;

    auto operationColumn = SheetView::CreateOperationColumnNode(titleBuilder, sheetStyle, sheetNode);
    ASSERT_NE(operationColumn, nullptr);
    auto columnLayoutProperty = operationColumn->GetLayoutProperty<LinearLayoutProperty>();
    ASSERT_NE(columnLayoutProperty, nullptr);
    EXPECT_EQ(columnLayoutProperty->GetCalcLayoutConstraint(), nullptr);
    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: CreateOperationColumnNode003
 * @tc.desc: Branch: if (isTitleBuilder.has_value() && GetFontScale() == GetSheetNormalScale()) = true
 *           Condition: isTitleBuilder.has_value() = true, GetFontScale() == GetSheetNormalScale() = true
 *           Branch: if (sheetTitle.has_value() && sheetSubtitle.has_value()) = false
 *           Condition: sheetTitle.has_value() = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, CreateOperationColumnNode003, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    auto titleBuilder = FrameNode::CreateFrameNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetPresentationPattern>(
        ElementRegister::GetInstance()->MakeUniqueId(), V2::SHEET_WRAPPER_TAG, std::move(callback)));
    auto sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(sheetLayoutProperty, nullptr);
    SheetStyle sheetStyle;
    sheetStyle.isTitleBuilder = true;
    sheetStyle.sheetTitle = std::nullopt;
    sheetLayoutProperty->UpdateSheetStyle(sheetStyle);
    auto pipelineContext = sheetNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->fontScale_ = pipelineContext->GetTheme<SheetTheme>()->GetSheetNormalScale();
    SheetOthersTestNg::sheetTheme_->operationAreaHeight_ = 16.0_vp;
    SheetOthersTestNg::sheetTheme_->sheetTitleAreaMargin_ = 0.0_vp;

    auto operationColumn = SheetView::CreateOperationColumnNode(titleBuilder, sheetStyle, sheetNode);
    ASSERT_NE(operationColumn, nullptr);
    auto columnLayoutProperty = operationColumn->GetLayoutProperty<LinearLayoutProperty>();
    ASSERT_NE(columnLayoutProperty, nullptr);
    ASSERT_NE(columnLayoutProperty->GetCalcLayoutConstraint(), nullptr);
    ASSERT_TRUE(columnLayoutProperty->GetCalcLayoutConstraint()->selfIdealSize.has_value());
    EXPECT_EQ(columnLayoutProperty->GetCalcLayoutConstraint()->selfIdealSize->Height(), CalcLength(0.0_vp));
    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: CreateOperationColumnNode004
 * @tc.desc: Branch: if (isTitleBuilder.has_value() && GetFontScale() == GetSheetNormalScale()) = true
 *           Condition: isTitleBuilder.has_value() = true, GetFontScale() == GetSheetNormalScale() = true
 *           Branch: if (sheetTitle.has_value() && sheetSubtitle.has_value()) = false
 *           Condition: sheetTitle.has_value() = true, sheetSubtitle.has_value() = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, CreateOperationColumnNode004, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    auto titleBuilder = FrameNode::CreateFrameNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetPresentationPattern>(
        ElementRegister::GetInstance()->MakeUniqueId(), V2::SHEET_WRAPPER_TAG, std::move(callback)));
    auto sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(sheetLayoutProperty, nullptr);
    SheetStyle sheetStyle;
    sheetStyle.isTitleBuilder = true;
    sheetStyle.sheetTitle = TITLE;
    sheetStyle.sheetSubtitle = std::nullopt;
    sheetLayoutProperty->UpdateSheetStyle(sheetStyle);
    auto pipelineContext = sheetNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->fontScale_ = pipelineContext->GetTheme<SheetTheme>()->GetSheetNormalScale();
    SheetOthersTestNg::sheetTheme_->operationAreaHeight_ = 16.0_vp;
    SheetOthersTestNg::sheetTheme_->sheetTitleAreaMargin_ = 0.0_vp;

    auto operationColumn = SheetView::CreateOperationColumnNode(titleBuilder, sheetStyle, sheetNode);
    ASSERT_NE(operationColumn, nullptr);
    auto columnLayoutProperty = operationColumn->GetLayoutProperty<LinearLayoutProperty>();
    ASSERT_NE(columnLayoutProperty, nullptr);
    ASSERT_NE(columnLayoutProperty->GetCalcLayoutConstraint(), nullptr);
    ASSERT_TRUE(columnLayoutProperty->GetCalcLayoutConstraint()->selfIdealSize.has_value());
    EXPECT_EQ(columnLayoutProperty->GetCalcLayoutConstraint()->selfIdealSize->Height(), CalcLength(0.0_vp));
    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: CreateOperationColumnNode005
 * @tc.desc: Branch: if (isTitleBuilder.has_value() && GetFontScale() == GetSheetNormalScale()) = true
 *           Condition: isTitleBuilder.has_value() = true, GetFontScale() == GetSheetNormalScale() = true
 *           Branch: if (sheetTitle.has_value() && sheetSubtitle.has_value()) = true
 *           Condition: sheetTitle.has_value() = true, sheetSubtitle.has_value() = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, CreateOperationColumnNode005, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    auto titleBuilder = FrameNode::CreateFrameNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetPresentationPattern>(
        ElementRegister::GetInstance()->MakeUniqueId(), V2::SHEET_WRAPPER_TAG, std::move(callback)));
    auto sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(sheetLayoutProperty, nullptr);
    SheetStyle sheetStyle;
    sheetStyle.isTitleBuilder = true;
    sheetStyle.sheetTitle = TITLE;
    sheetStyle.sheetSubtitle = SUBTITLE;
    sheetLayoutProperty->UpdateSheetStyle(sheetStyle);
    auto pipelineContext = sheetNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->fontScale_ = pipelineContext->GetTheme<SheetTheme>()->GetSheetNormalScale();

    auto operationColumn = SheetView::CreateOperationColumnNode(titleBuilder, sheetStyle, sheetNode);
    ASSERT_NE(operationColumn, nullptr);
    auto columnLayoutProperty = operationColumn->GetLayoutProperty<LinearLayoutProperty>();
    ASSERT_NE(columnLayoutProperty, nullptr);
    ASSERT_NE(columnLayoutProperty->GetCalcLayoutConstraint(), nullptr);
    ASSERT_TRUE(columnLayoutProperty->GetCalcLayoutConstraint()->selfIdealSize.has_value());
    EXPECT_EQ(columnLayoutProperty->GetCalcLayoutConstraint()->selfIdealSize->Height(), CalcLength(56.0_vp));
    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: CreateDragBarNode001
 * @tc.desc: Branch: if (sheetStyle.detents.size() == SHEET_DETENTS_TWO) = false
 *           Branch: else if (sheetStyle.detents.size() == SHEET_DETENTS_THREE) = false
 *           Branch: if ((!isSingleDetents && showDragIndicator && sheetPattern->IsSheetBottomStyle())
 *               || sheetStyle.isTitleBuilder.has_value()) = false
 *           Condition: !isSingleDetents = false, sheetStyle.isTitleBuilder.has_value() = false
 *           Branch: if (sheetStyle.isTitleBuilder.has_value()) = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, CreateDragBarNode001, TestSize.Level1)
{
    auto titleBuilder = FrameNode::CreateFrameNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto operationColumn = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetPresentationPattern>(
        ElementRegister::GetInstance()->MakeUniqueId(), V2::SHEET_WRAPPER_TAG, std::move(callback)));
    auto sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(sheetLayoutProperty, nullptr);
    SheetStyle sheetStyle;
    sheetStyle.detents = {};
    sheetStyle.isTitleBuilder = std::nullopt;
    sheetLayoutProperty->UpdateSheetStyle(sheetStyle);

    SheetView::CreateDragBarNode(titleBuilder, operationColumn, sheetStyle, sheetNode);
    ASSERT_EQ(operationColumn->children_.size(), 0);
}

/**
 * @tc.name: CreateDragBarNode002
 * @tc.desc: Branch: if (sheetStyle.detents.size() == SHEET_DETENTS_TWO) = true
 *           Branch: if ((!isSingleDetents && showDragIndicator && sheetPattern->IsSheetBottomStyle())
 *               || sheetStyle.isTitleBuilder.has_value()) = false
 *           Condition: !isSingleDetents = true, showDragIndicator = false,
 *               sheetStyle.isTitleBuilder.has_value() = true
 *           Branch: if (sheetStyle.isTitleBuilder.has_value()) = true
 *           Branch: if (titleColumn) = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, CreateDragBarNode002, TestSize.Level1)
{
    SheetOthersTestNg::TearDownTestCase();
    auto titleBuilder = FrameNode::CreateFrameNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto operationColumn = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetPresentationPattern>(
        ElementRegister::GetInstance()->MakeUniqueId(), V2::SHEET_WRAPPER_TAG, std::move(callback)));
    auto sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(sheetLayoutProperty, nullptr);
    SheetStyle sheetStyle;
    sheetStyle.detents = {SheetHeight({ 300.0_vp }), SheetHeight({ 700.0_vp })};
    sheetStyle.isTitleBuilder = true;
    sheetStyle.showDragBar = false;
    sheetLayoutProperty->UpdateSheetStyle(sheetStyle);

    SheetView::CreateDragBarNode(titleBuilder, operationColumn, sheetStyle, sheetNode);
    ASSERT_EQ(operationColumn->children_.size(), 0);
}

/**
 * @tc.name: CreateDragBarNode003
 * @tc.desc: Branch: if (sheetStyle.detents.size() == SHEET_DETENTS_TWO) = false
 *           Branch: else if (sheetStyle.detents.size() == SHEET_DETENTS_THREE) = true
 *           Branch: if ((!isSingleDetents && showDragIndicator && sheetPattern->IsSheetBottomStyle())
 *               || sheetStyle.isTitleBuilder.has_value()) = false
 *           Condition: !isSingleDetents = true, showDragIndicator = true,
 *               sheetPattern->IsSheetBottomStyle() = false, sheetStyle.isTitleBuilder.has_value() = true
 *           Branch: if (sheetStyle.isTitleBuilder.has_value()) = true
 *           Branch: if (titleColumn) = true
 *           Branch: if ((titleBuilder) && (sheetStyle.isTitleBuilder.value())) = false
 *           Condition: (titleBuilder) = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, CreateDragBarNode003, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    auto operationColumn = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetPresentationPattern>(
        ElementRegister::GetInstance()->MakeUniqueId(), V2::SHEET_WRAPPER_TAG, std::move(callback)));
    auto sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(sheetLayoutProperty, nullptr);
    SheetStyle sheetStyle;
    sheetStyle.detents = {SheetHeight({ 300.0_vp }), SheetHeight({ 700.0_vp }), SheetHeight({ 1000.0_vp })};
    sheetStyle.isTitleBuilder = true;
    sheetStyle.showDragBar = true;
    sheetLayoutProperty->UpdateSheetStyle(sheetStyle);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->sheetType_ = SheetType::SHEET_CENTER;

    SheetView::CreateDragBarNode(nullptr, operationColumn, sheetStyle, sheetNode);
    ASSERT_EQ(operationColumn->children_.size(), 1);
    auto childIterator = sheetNode->children_.begin();
    auto dragBarNode = AceType::DynamicCast<FrameNode>(*childIterator);
    ASSERT_NE(dragBarNode, nullptr);
    auto dragBarLayoutProperty = dragBarNode->GetLayoutProperty();
    EXPECT_EQ(dragBarLayoutProperty->propVisibility_, VisibleType::INVISIBLE);
    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: CreateDragBarNode004
 * @tc.desc: Branch: if (sheetStyle.detents.size() == SHEET_DETENTS_TWO) = true
 *           Branch: if ((!isSingleDetents && showDragIndicator && sheetPattern->IsSheetBottomStyle())
 *               || sheetStyle.isTitleBuilder.has_value()) = false
 *           Condition: !isSingleDetents = true, showDragIndicator = true,
 *               sheetPattern->IsSheetBottomStyle() = true
 *           Branch: if (sheetStyle.isTitleBuilder.has_value()) = true
 *           Branch: if (titleColumn) = true
 *           Branch: if ((titleBuilder) && (sheetStyle.isTitleBuilder.value())) = true
 *           Condition: (titleBuilder) = true, (sheetStyle.isTitleBuilder.value()) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, CreateDragBarNode004, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    auto titleBuilder = FrameNode::CreateFrameNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto operationColumn = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetPresentationPattern>(
        ElementRegister::GetInstance()->MakeUniqueId(), V2::SHEET_WRAPPER_TAG, std::move(callback)));
    auto sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(sheetLayoutProperty, nullptr);
    SheetStyle sheetStyle;
    sheetStyle.detents = {SheetHeight({ 300.0_vp }), SheetHeight({ 700.0_vp })};
    sheetStyle.isTitleBuilder = true;
    sheetLayoutProperty->UpdateSheetStyle(sheetStyle);

    SheetView::CreateDragBarNode(titleBuilder, operationColumn, sheetStyle, sheetNode);
    ASSERT_EQ(operationColumn->children_.size(), 1);
    auto childIterator = sheetNode->children_.begin();
    auto dragBarNode = AceType::DynamicCast<FrameNode>(*childIterator);
    ASSERT_NE(dragBarNode, nullptr);
    auto dragBarLayoutProperty = dragBarNode->GetLayoutProperty();
    EXPECT_EQ(dragBarLayoutProperty->propVisibility_, VisibleType::INVISIBLE);
    auto operationColumnChildIterator = operationColumn->children_.begin();
    auto titleColumnNode = AceType::DynamicCast<FrameNode>(*operationColumnChildIterator);
    ASSERT_NE(titleColumnNode, nullptr);
    EXPECT_EQ(titleColumnNode->children_.size(), 1);
    EXPECT_EQ(titleColumnNode->children_.front(), titleBuilder);
    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: CreateCloseIconButtonNode001
 * @tc.desc: Branch: if (!Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, CreateCloseIconButtonNode001, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetPresentationPattern>(
        ElementRegister::GetInstance()->MakeUniqueId(), V2::SHEET_WRAPPER_TAG, std::move(callback)));
    SheetStyle sheetStyle;
    auto pipelineContext = sheetNode->GetContext();
    int32_t minPlatformVersion = pipelineContext->minPlatformVersion_;
    pipelineContext->minPlatformVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TWELVE);

    SheetView::CreateCloseIconButtonNode(sheetNode, sheetStyle);
    EXPECT_EQ(sheetNode->children_.size(), 1);
    pipelineContext->minPlatformVersion_ = minPlatformVersion;
    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: CreateCloseIconButtonNode002
 * @tc.desc: Branch: if (!Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, CreateCloseIconButtonNode002, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetPresentationPattern>(
        ElementRegister::GetInstance()->MakeUniqueId(), V2::SHEET_WRAPPER_TAG, std::move(callback)));
    SheetStyle sheetStyle;
    auto pipelineContext = sheetNode->GetContext();
    int32_t minPlatformVersion = pipelineContext->minPlatformVersion_;
    pipelineContext->minPlatformVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TEN);

    SheetView::CreateCloseIconButtonNode(sheetNode, sheetStyle);
    EXPECT_EQ(sheetNode->children_.size(), 0);
    pipelineContext->minPlatformVersion_ = minPlatformVersion;
    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: BuildMainTitle001
 * @tc.desc: Branch: if (textTheme && textTheme->GetIsTextFadeout()) = false
 *           Condition: textTheme = false
 *           Branch: if (sheetStyle.sheetTitle.has_value()) = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, BuildMainTitle001, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetPresentationPattern>(
        ElementRegister::GetInstance()->MakeUniqueId(), V2::SHEET_WRAPPER_TAG, std::move(callback)));
    SheetStyle sheetStyle;
    SheetOthersTestNg::textTheme_ = nullptr;

    auto titleRow = SheetView::BuildMainTitle(sheetNode, sheetStyle);
    ASSERT_NE(titleRow, nullptr);
    ASSERT_EQ(titleRow->children_.size(), 1);
    auto sheetTitleNode = AceType::DynamicCast<FrameNode>(titleRow->children_.front());
    ASSERT_NE(sheetTitleNode, nullptr);
    auto titleLayoutProperty = sheetTitleNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(titleLayoutProperty, nullptr);
    EXPECT_EQ(titleLayoutProperty->GetMaxLines(), SHEET_TITLE_MAX_LINES);
    EXPECT_EQ(titleLayoutProperty->GetTextOverflow(), TextOverflow::ELLIPSIS);
    EXPECT_EQ(titleLayoutProperty->GetContent(), std::nullopt);
    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: BuildMainTitle002
 * @tc.desc: Branch: if (textTheme && textTheme->GetIsTextFadeout()) = false
 *           Condition: textTheme = true, textTheme->GetIsTextFadeout() = false
 *           Branch: if (sheetStyle.sheetTitle.has_value()) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, BuildMainTitle002, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetPresentationPattern>(
        ElementRegister::GetInstance()->MakeUniqueId(), V2::SHEET_WRAPPER_TAG, std::move(callback)));
    SheetStyle sheetStyle;
    sheetStyle.sheetTitle = "sheetTitle";
    SheetOthersTestNg::textTheme_->isTextFadeout_ = false;

    auto titleRow = SheetView::BuildMainTitle(sheetNode, sheetStyle);
    ASSERT_NE(titleRow, nullptr);
    ASSERT_EQ(titleRow->children_.size(), 1);
    auto sheetTitleNode = AceType::DynamicCast<FrameNode>(titleRow->children_.front());
    ASSERT_NE(sheetTitleNode, nullptr);
    auto titleLayoutProperty = sheetTitleNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(titleLayoutProperty, nullptr);
    EXPECT_EQ(titleLayoutProperty->GetMaxLines(), SHEET_TITLE_MAX_LINES);
    EXPECT_EQ(titleLayoutProperty->GetTextOverflow(), TextOverflow::ELLIPSIS);
    auto titleContent = titleLayoutProperty->GetContent();
    ASSERT_TRUE(titleContent.has_value());
    EXPECT_EQ(titleContent.value(), u"sheetTitle");
    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: BuildMainTitle003
 * @tc.desc: Branch: if (textTheme && textTheme->GetIsTextFadeout()) = true
 *           Condition: textTheme = true, textTheme->GetIsTextFadeout() = true
 *           Branch: if (sheetStyle.sheetTitle.has_value()) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, BuildMainTitle003, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetPresentationPattern>(
        ElementRegister::GetInstance()->MakeUniqueId(), V2::SHEET_WRAPPER_TAG, std::move(callback)));
    SheetStyle sheetStyle;
    sheetStyle.sheetTitle = "sheetTitle";
    SheetOthersTestNg::textTheme_->isTextFadeout_ = true;

    auto titleRow = SheetView::BuildMainTitle(sheetNode, sheetStyle);
    ASSERT_NE(titleRow, nullptr);
    ASSERT_EQ(titleRow->children_.size(), 1);
    auto sheetTitleNode = AceType::DynamicCast<FrameNode>(titleRow->children_.front());
    ASSERT_NE(sheetTitleNode, nullptr);
    auto titleLayoutProperty = sheetTitleNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(titleLayoutProperty, nullptr);
    EXPECT_EQ(titleLayoutProperty->GetTextOverflow(), TextOverflow::MARQUEE);
    EXPECT_EQ(titleLayoutProperty->GetTextMarqueeStartPolicy(), MarqueeStartPolicy::ON_FOCUS);
    auto titleContent = titleLayoutProperty->GetContent();
    ASSERT_TRUE(titleContent.has_value());
    EXPECT_EQ(titleContent.value(), u"sheetTitle");
    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: BuildSubTitle001
 * @tc.desc: Branch: if (textTheme && textTheme->GetIsTextFadeout()) = false
 *           Condition: textTheme = false
 *           Branch: if (sheetStyle.sheetSubtitle.has_value()) = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, BuildSubTitle001, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetPresentationPattern>(
        ElementRegister::GetInstance()->MakeUniqueId(), V2::SHEET_WRAPPER_TAG, std::move(callback)));
    SheetStyle sheetStyle;
    SheetOthersTestNg::textTheme_ = nullptr;

    auto subtitleRow = SheetView::BuildSubTitle(sheetNode, sheetStyle);
    ASSERT_NE(subtitleRow, nullptr);
    ASSERT_EQ(subtitleRow->children_.size(), 1);
    auto sheetSubtitleNode = AceType::DynamicCast<FrameNode>(subtitleRow->children_.front());
    ASSERT_NE(sheetSubtitleNode, nullptr);
    auto subtitleLayoutProperty = sheetSubtitleNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(subtitleLayoutProperty, nullptr);
    EXPECT_EQ(subtitleLayoutProperty->GetMaxLines(), SHEET_TITLE_MAX_LINES);
    EXPECT_EQ(subtitleLayoutProperty->GetTextOverflow(), TextOverflow::ELLIPSIS);
    EXPECT_EQ(subtitleLayoutProperty->GetContent(), std::nullopt);
    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: BuildSubTitle002
 * @tc.desc: Branch: if (textTheme && textTheme->GetIsTextFadeout()) = false
 *           Condition: textTheme = true, textTheme->GetIsTextFadeout() = false
 *           Branch: if (sheetStyle.sheetSubtitle.has_value()) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, BuildSubTitle002, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetPresentationPattern>(
        ElementRegister::GetInstance()->MakeUniqueId(), V2::SHEET_WRAPPER_TAG, std::move(callback)));
    SheetStyle sheetStyle;
    sheetStyle.sheetSubtitle = "sheetSubtitle";
    SheetOthersTestNg::textTheme_->isTextFadeout_ = false;

    auto subtitleRow = SheetView::BuildSubTitle(sheetNode, sheetStyle);
    ASSERT_NE(subtitleRow, nullptr);
    ASSERT_EQ(subtitleRow->children_.size(), 1);
    auto sheetSubtitleNode = AceType::DynamicCast<FrameNode>(subtitleRow->children_.front());
    ASSERT_NE(sheetSubtitleNode, nullptr);
    auto subtitleLayoutProperty = sheetSubtitleNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(subtitleLayoutProperty, nullptr);
    EXPECT_EQ(subtitleLayoutProperty->GetMaxLines(), SHEET_TITLE_MAX_LINES);
    EXPECT_EQ(subtitleLayoutProperty->GetTextOverflow(), TextOverflow::ELLIPSIS);
    auto subtitleContent = subtitleLayoutProperty->GetContent();
    ASSERT_TRUE(subtitleContent.has_value());
    EXPECT_EQ(subtitleContent.value(), u"sheetSubtitle");
    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: BuildSubTitle003
 * @tc.desc: Branch: if (textTheme && textTheme->GetIsTextFadeout()) = true
 *           Condition: textTheme = true, textTheme->GetIsTextFadeout() = true
 *           Branch: if (sheetStyle.sheetSubtitle.has_value()) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, BuildSubTitle003, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetPresentationPattern>(
        ElementRegister::GetInstance()->MakeUniqueId(), V2::SHEET_WRAPPER_TAG, std::move(callback)));
    SheetStyle sheetStyle;
    sheetStyle.sheetSubtitle = "sheetSubtitle";
    SheetOthersTestNg::textTheme_->isTextFadeout_ = true;

    auto subtitleRow = SheetView::BuildSubTitle(sheetNode, sheetStyle);
    ASSERT_NE(subtitleRow, nullptr);
    ASSERT_EQ(subtitleRow->children_.size(), 1);
    auto sheetSubtitleNode = AceType::DynamicCast<FrameNode>(subtitleRow->children_.front());
    ASSERT_NE(sheetSubtitleNode, nullptr);
    auto subtitleLayoutProperty = sheetSubtitleNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(subtitleLayoutProperty, nullptr);
    EXPECT_EQ(subtitleLayoutProperty->GetTextOverflow(), TextOverflow::MARQUEE);
    EXPECT_EQ(subtitleLayoutProperty->GetTextMarqueeStartPolicy(), MarqueeStartPolicy::ON_FOCUS);
    auto subtitleContent = subtitleLayoutProperty->GetContent();
    ASSERT_TRUE(subtitleContent.has_value());
    EXPECT_EQ(subtitleContent.value(), u"sheetSubtitle");
    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: BuildTitleColumn001
 * @tc.desc: Branch: if (GetFontScale() == GetSheetNormalScale() || isTitleCustombuilder) = true
 *           Condition: GetFontScale() == GetSheetNormalScale() = true
 *           Branch: if (sheetStyle.sheetTitle.has_value()) = false
 *           Branch: else if (sheetStyle.isTitleBuilder.has_value()) = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, BuildTitleColumn001, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetPresentationPattern>(
        ElementRegister::GetInstance()->MakeUniqueId(), V2::SHEET_WRAPPER_TAG, std::move(callback)));
    SheetStyle sheetStyle;
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateSheetStyle(sheetStyle);
    auto pipelineContext = sheetNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->fontScale_ = pipelineContext->GetTheme<SheetTheme>()->GetSheetNormalScale();
    SheetOthersTestNg::sheetTheme_->operationAreaHeight_ = 50.0_vp;

    auto titleColumn = SheetView::BuildTitleColumn(sheetNode, sheetStyle);
    ASSERT_NE(titleColumn, nullptr);
    auto titleLayoutProperty = titleColumn->GetLayoutProperty<LinearLayoutProperty>();
    ASSERT_NE(titleLayoutProperty, nullptr);
    ASSERT_NE(titleLayoutProperty->GetCalcLayoutConstraint(), nullptr);
    ASSERT_TRUE(titleLayoutProperty->GetCalcLayoutConstraint()->selfIdealSize.has_value());
    EXPECT_EQ(titleLayoutProperty->GetCalcLayoutConstraint()->selfIdealSize->Height(), CalcLength(50.0_vp));
    EXPECT_EQ(titleColumn->children_.size(), 0);
    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: BuildTitleColumn002
 * @tc.desc: Branch: if (GetFontScale() == GetSheetNormalScale() || isTitleCustombuilder) = true
 *           Condition: GetFontScale() == GetSheetNormalScale() = false, isTitleCustombuilder = true
 *           Branch: if (sheetStyle.sheetTitle.has_value()) = true
 *           Branch: if (sheetStyle.sheetSubtitle.has_value()) = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, BuildTitleColumn002, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetPresentationPattern>(
        ElementRegister::GetInstance()->MakeUniqueId(), V2::SHEET_WRAPPER_TAG, std::move(callback)));
    SheetStyle sheetStyle;
    sheetStyle.sheetTitle = "sheetTitle";
    sheetStyle.isTitleBuilder = true;
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateSheetStyle(sheetStyle);
    auto pipelineContext = sheetNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->fontScale_ = pipelineContext->GetTheme<SheetTheme>()->GetSheetNormalScale() + 10.0f;
    SheetOthersTestNg::sheetTheme_->operationAreaHeight_ = 50.0_vp;

    auto titleColumn = SheetView::BuildTitleColumn(sheetNode, sheetStyle);
    ASSERT_NE(titleColumn, nullptr);
    auto titleLayoutProperty = titleColumn->GetLayoutProperty<LinearLayoutProperty>();
    ASSERT_NE(titleLayoutProperty, nullptr);
    ASSERT_NE(titleLayoutProperty->GetCalcLayoutConstraint(), nullptr);
    ASSERT_TRUE(titleLayoutProperty->GetCalcLayoutConstraint()->selfIdealSize.has_value());
    EXPECT_EQ(titleLayoutProperty->GetCalcLayoutConstraint()->selfIdealSize->Height(), CalcLength(50.0_vp));
    EXPECT_EQ(titleColumn->children_.size(), 1);
    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: BuildTitleColumn003
 * @tc.desc: Branch: if (GetFontScale() == GetSheetNormalScale() || isTitleCustombuilder) = false
 *           Condition: GetFontScale() == GetSheetNormalScale() = false, isTitleCustombuilder = false
 *           Branch: if (sheetStyle.sheetTitle.has_value()) = true
 *           Branch: if (sheetStyle.sheetSubtitle.has_value()) = true
 *           Branch: if (pipeline->GetFontScale() == sheetTheme->GetSheetNormalScale()) = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, BuildTitleColumn003, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetPresentationPattern>(
        ElementRegister::GetInstance()->MakeUniqueId(), V2::SHEET_WRAPPER_TAG, std::move(callback)));
    SheetStyle sheetStyle;
    sheetStyle.sheetTitle = "sheetTitle";
    sheetStyle.sheetSubtitle = "sheetSubtitle";
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateSheetStyle(sheetStyle);
    auto pipelineContext = sheetNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->fontScale_ = pipelineContext->GetTheme<SheetTheme>()->GetSheetNormalScale() + 10.0f;
    SheetOthersTestNg::sheetTheme_->operationAreaHeight_ = 50.0_vp;

    auto titleColumn = SheetView::BuildTitleColumn(sheetNode, sheetStyle);
    ASSERT_NE(titleColumn, nullptr);
    auto titleLayoutProperty = titleColumn->GetLayoutProperty<LinearLayoutProperty>();
    ASSERT_NE(titleLayoutProperty, nullptr);
    ASSERT_NE(titleLayoutProperty->GetCalcLayoutConstraint(), nullptr);
    EXPECT_FALSE(titleLayoutProperty->GetCalcLayoutConstraint()->selfIdealSize.has_value());
    EXPECT_EQ(titleColumn->children_.size(), 2);
    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: BuildTitleColumn004
 * @tc.desc: Branch: if (GetFontScale() == GetSheetNormalScale() || isTitleCustombuilder) = true
 *           Condition: GetFontScale() == GetSheetNormalScale() = true
 *           Branch: if (sheetStyle.sheetTitle.has_value()) = true
 *           Branch: if (sheetStyle.sheetSubtitle.has_value()) = true
 *           Branch: if (pipeline->GetFontScale() == sheetTheme->GetSheetNormalScale()) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, BuildTitleColumn004, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetPresentationPattern>(
        ElementRegister::GetInstance()->MakeUniqueId(), V2::SHEET_WRAPPER_TAG, std::move(callback)));
    SheetStyle sheetStyle;
    sheetStyle.sheetTitle = "sheetTitle";
    sheetStyle.sheetSubtitle = "sheetSubtitle";
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateSheetStyle(sheetStyle);
    auto pipelineContext = sheetNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->fontScale_ = pipelineContext->GetTheme<SheetTheme>()->GetSheetNormalScale();
    SheetOthersTestNg::sheetTheme_->operationAreaHeight_ = 50.0_vp;

    auto titleColumn = SheetView::BuildTitleColumn(sheetNode, sheetStyle);
    ASSERT_NE(titleColumn, nullptr);
    auto titleLayoutProperty = titleColumn->GetLayoutProperty<LinearLayoutProperty>();
    ASSERT_NE(titleLayoutProperty, nullptr);
    ASSERT_NE(titleLayoutProperty->GetCalcLayoutConstraint(), nullptr);
    ASSERT_TRUE(titleLayoutProperty->GetCalcLayoutConstraint()->selfIdealSize.has_value());
    EXPECT_EQ(titleLayoutProperty->GetCalcLayoutConstraint()->selfIdealSize->Height(), CalcLength(68.0_vp));
    EXPECT_EQ(titleColumn->children_.size(), 2);
    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: BuildTitleColumn005
 * @tc.desc: Branch: if (GetFontScale() == GetSheetNormalScale() || isTitleCustombuilder) = true
 *           Condition: GetFontScale() == GetSheetNormalScale() = true
 *           Branch: if (sheetStyle.sheetTitle.has_value()) = false
 *           Branch: else if (sheetStyle.isTitleBuilder.has_value()) = true
 *           Branch: if (isCustomBuilder) = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, BuildTitleColumn005, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetPresentationPattern>(
        ElementRegister::GetInstance()->MakeUniqueId(), V2::SHEET_WRAPPER_TAG, std::move(callback)));
    SheetStyle sheetStyle;
    sheetStyle.isTitleBuilder = false;
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateSheetStyle(sheetStyle);
    auto pipelineContext = sheetNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->fontScale_ = pipelineContext->GetTheme<SheetTheme>()->GetSheetNormalScale();
    SheetOthersTestNg::sheetTheme_->operationAreaHeight_ = 50.0_vp;

    auto titleColumn = SheetView::BuildTitleColumn(sheetNode, sheetStyle);
    ASSERT_NE(titleColumn, nullptr);
    auto titleLayoutProperty = titleColumn->GetLayoutProperty<LinearLayoutProperty>();
    ASSERT_NE(titleLayoutProperty, nullptr);
    ASSERT_NE(titleLayoutProperty->GetCalcLayoutConstraint(), nullptr);
    ASSERT_TRUE(titleLayoutProperty->GetCalcLayoutConstraint()->selfIdealSize.has_value());
    EXPECT_EQ(titleLayoutProperty->GetCalcLayoutConstraint()->selfIdealSize->Height(), CalcLength(50.0_vp));
    EXPECT_EQ(titleColumn->children_.size(), 0);
    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: BuildTitleColumn006
 * @tc.desc: Branch: if (GetFontScale() == GetSheetNormalScale() || isTitleCustombuilder) = true
 *           Condition: GetFontScale() == GetSheetNormalScale() = true
 *           Branch: if (sheetStyle.sheetTitle.has_value()) = false
 *           Branch: else if (sheetStyle.isTitleBuilder.has_value()) = true
 *           Branch: if (isCustomBuilder) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, BuildTitleColumn006, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetPresentationPattern>(
        ElementRegister::GetInstance()->MakeUniqueId(), V2::SHEET_WRAPPER_TAG, std::move(callback)));
    SheetStyle sheetStyle;
    sheetStyle.isTitleBuilder = true;
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateSheetStyle(sheetStyle);
    auto pipelineContext = sheetNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->fontScale_ = pipelineContext->GetTheme<SheetTheme>()->GetSheetNormalScale();
    SheetOthersTestNg::sheetTheme_->operationAreaHeight_ = 50.0_vp;

    auto titleColumn = SheetView::BuildTitleColumn(sheetNode, sheetStyle);
    ASSERT_NE(titleColumn, nullptr);
    auto titleLayoutProperty = titleColumn->GetLayoutProperty<LinearLayoutProperty>();
    ASSERT_NE(titleLayoutProperty, nullptr);
    ASSERT_NE(titleLayoutProperty->GetCalcLayoutConstraint(), nullptr);
    ASSERT_TRUE(titleLayoutProperty->GetCalcLayoutConstraint()->selfIdealSize.has_value());
    EXPECT_EQ(titleLayoutProperty->GetCalcLayoutConstraint()->selfIdealSize->Height(), CalcLength(50.0_vp));
    EXPECT_EQ(titleLayoutProperty->GetMainAxisAlign(), FlexAlign::CENTER);
    EXPECT_EQ(titleColumn->children_.size(), 0);
    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: GetOverlayFromPage001
 * @tc.desc: Branch: if (rootNodeId <= 0) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, GetOverlayFromPage001, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();

    auto overlayManager = SheetManager::GetOverlayFromPage(-1, RootNodeType::PAGE_ETS_TAG);
    EXPECT_EQ(overlayManager, nullptr);
    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: GetOverlayFromPage002
 * @tc.desc: Branch: if (rootNodeId <= 0) = false
 *           Branch: if (tag == V2::PAGE_ETS_TAG) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, GetOverlayFromPage002, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    int32_t rootNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto sheetNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, rootNodeId,
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    auto sheetPattern = sheetNode->GetPattern<PagePattern>();
    sheetPattern->CreateOverlayManager(true);

    auto overlayManager = SheetManager::GetOverlayFromPage(rootNodeId, RootNodeType::PAGE_ETS_TAG);
    EXPECT_NE(overlayManager, nullptr);
    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: GetOverlayFromPage003
 * @tc.desc: Branch: if (rootNodeId <= 0) = false
 *           Branch: if (tag == V2::PAGE_ETS_TAG) = false
 *           Branch: if (tag == V2::NAVDESTINATION_VIEW_ETS_TAG) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, GetOverlayFromPage003, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    int32_t rootNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        rootNodeId, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    navDestinationPattern->CreateOverlayManager(true);

    auto overlayManager = SheetManager::GetOverlayFromPage(rootNodeId, RootNodeType::NAVDESTINATION_VIEW_ETS_TAG);
    EXPECT_NE(overlayManager, nullptr);
    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: GetOverlayFromPage004
 * @tc.desc: Branch: if (rootNodeId <= 0) = false
 *           Branch: if (tag == V2::PAGE_ETS_TAG) = false
 *           Branch: if (tag == V2::NAVDESTINATION_VIEW_ETS_TAG) = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, GetOverlayFromPage004, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    int32_t rootNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto windowSceneNode = FrameNode::CreateFrameNode(V2::WINDOW_SCENE_ETS_TAG, rootNodeId,
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    auto windowScenePattern = windowSceneNode->GetPattern<PagePattern>();
    windowScenePattern->CreateOverlayManager(true);

    auto overlayManager = SheetManager::GetOverlayFromPage(rootNodeId, RootNodeType::WINDOW_SCENE_ETS_TAG);
    EXPECT_EQ(overlayManager, nullptr);
    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: UpdateBindSheetByUIContext001
 * @tc.desc: Branch: if (iter != overlayManagerMap_.end() &&
 *               targetIdMap_.find(sheetContentKey) != targetIdMap_.end()) = false
 *           Condition: iter != overlayManagerMap_.end() = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, UpdateBindSheetByUIContext001, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetPresentationPattern>(
        ElementRegister::GetInstance()->MakeUniqueId(), V2::SHEET_WRAPPER_TAG, std::move(callback)));
    auto scrollNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ScrollPattern>());
    auto contentNode = FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    contentNode->MountToParent(scrollNode);
    scrollNode->MountToParent(sheetNode);
    SheetStyle sheetStyle;
    bool isPartialUpdate = true;
    int32_t currentInstanceId = 0;
    SheetManager sheetManager;
    sheetManager.overlayManagerMap_.clear();
    sheetManager.targetIdMap_.clear();

    SheetManager::SheetContentKey sheetContentKey(currentInstanceId, contentNode->GetId());
    int32_t ret = sheetManager.UpdateBindSheetByUIContext(contentNode, sheetStyle, isPartialUpdate, currentInstanceId);
    EXPECT_EQ(ret, ERROR_CODE_BIND_SHEET_CONTENT_NOT_FOUND);
    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: UpdateBindSheetByUIContext002
 * @tc.desc: Branch: if (iter != overlayManagerMap_.end() &&
 *               targetIdMap_.find(sheetContentKey) != targetIdMap_.end()) = false
 *           Condition: iter != overlayManagerMap_.end() = true,
 *               targetIdMap_.find(sheetContentKey) != targetIdMap_.end() = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, UpdateBindSheetByUIContext002, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetPresentationPattern>(
        ElementRegister::GetInstance()->MakeUniqueId(), V2::SHEET_WRAPPER_TAG, std::move(callback)));
    auto scrollNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ScrollPattern>());
    auto contentNode = FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    contentNode->MountToParent(scrollNode);
    scrollNode->MountToParent(sheetNode);
    SheetStyle sheetStyle;
    bool isPartialUpdate = true;
    int32_t currentInstanceId = 0;
    SheetManager sheetManager;
    sheetManager.overlayManagerMap_.clear();
    sheetManager.targetIdMap_.clear();
    SheetManager::SheetContentKey sheetContentKey(currentInstanceId, contentNode->GetId());
    sheetManager.overlayManagerMap_.emplace(sheetContentKey, nullptr);

    int32_t ret = sheetManager.UpdateBindSheetByUIContext(contentNode, sheetStyle, isPartialUpdate, currentInstanceId);
    EXPECT_EQ(ret, ERROR_CODE_BIND_SHEET_CONTENT_NOT_FOUND);
    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: UpdateBindSheetByUIContext003
 * @tc.desc: Branch: if (iter != overlayManagerMap_.end() &&
 *               targetIdMap_.find(sheetContentKey) != targetIdMap_.end()) = true
 *           Condition: iter != overlayManagerMap_.end() = true,
 *               targetIdMap_.find(sheetContentKey) != targetIdMap_.end() = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, UpdateBindSheetByUIContext003, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetPresentationPattern>(
        ElementRegister::GetInstance()->MakeUniqueId(), V2::SHEET_WRAPPER_TAG, std::move(callback)));
    auto scrollNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ScrollPattern>());
    auto contentNode = FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    contentNode->MountToParent(scrollNode);
    scrollNode->MountToParent(sheetNode);
    SheetStyle sheetStyle;
    bool isPartialUpdate = true;
    int32_t currentInstanceId = 0;
    SheetManager sheetManager;
    sheetManager.overlayManagerMap_.clear();
    sheetManager.targetIdMap_.clear();
    SheetManager::SheetContentKey sheetContentKey(currentInstanceId, contentNode->GetId());
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    auto overlayManager = PipelineContext::GetCurrentContext()->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    sheetManager.overlayManagerMap_.emplace(sheetContentKey, overlayManager);
    sheetManager.targetIdMap_.emplace(sheetContentKey, 0);

    int32_t ret = sheetManager.UpdateBindSheetByUIContext(contentNode, sheetStyle, isPartialUpdate, currentInstanceId);
    EXPECT_EQ(ret, ERROR_CODE_NO_ERROR);
    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: CloseBindSheetByUIContext001
 * @tc.desc: Branch: if (iter != overlayManagerMap_.end() &&
 *               targetIdMap_.find(sheetContentKey) != targetIdMap_.end()) = false
 *           Condition: iter != overlayManagerMap_.end() = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, CloseBindSheetByUIContext001, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetPresentationPattern>(
        ElementRegister::GetInstance()->MakeUniqueId(), V2::SHEET_WRAPPER_TAG, std::move(callback)));
    auto scrollNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ScrollPattern>());
    auto contentNode = FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    contentNode->MountToParent(scrollNode);
    scrollNode->MountToParent(sheetNode);
    int32_t currentInstanceId = 0;
    SheetManager sheetManager;
    sheetManager.overlayManagerMap_.clear();
    sheetManager.targetIdMap_.clear();

    SheetManager::SheetContentKey sheetContentKey(currentInstanceId, contentNode->GetId());
    int32_t ret = sheetManager.CloseBindSheetByUIContext(contentNode, currentInstanceId);
    EXPECT_EQ(ret, ERROR_CODE_BIND_SHEET_CONTENT_NOT_FOUND);
    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: CloseBindSheetByUIContext002
 * @tc.desc: Branch: if (iter != overlayManagerMap_.end() &&
 *               targetIdMap_.find(sheetContentKey) != targetIdMap_.end()) = false
 *           Condition: iter != overlayManagerMap_.end() = true,
 *               targetIdMap_.find(sheetContentKey) != targetIdMap_.end() = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, CloseBindSheetByUIContext002, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetPresentationPattern>(
        ElementRegister::GetInstance()->MakeUniqueId(), V2::SHEET_WRAPPER_TAG, std::move(callback)));
    auto scrollNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ScrollPattern>());
    auto contentNode = FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    contentNode->MountToParent(scrollNode);
    scrollNode->MountToParent(sheetNode);
    int32_t currentInstanceId = 0;
    SheetManager sheetManager;
    sheetManager.overlayManagerMap_.clear();
    sheetManager.targetIdMap_.clear();
    SheetManager::SheetContentKey sheetContentKey(currentInstanceId, contentNode->GetId());
    sheetManager.overlayManagerMap_.emplace(sheetContentKey, nullptr);

    int32_t ret = sheetManager.CloseBindSheetByUIContext(contentNode, currentInstanceId);
    EXPECT_EQ(ret, ERROR_CODE_BIND_SHEET_CONTENT_NOT_FOUND);
    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: CloseBindSheetByUIContext003
 * @tc.desc: Branch: if (iter != overlayManagerMap_.end() &&
 *               targetIdMap_.find(sheetContentKey) != targetIdMap_.end()) = true
 *           Condition: iter != overlayManagerMap_.end() = true,
 *               targetIdMap_.find(sheetContentKey) != targetIdMap_.end() = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, CloseBindSheetByUIContext003, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetPresentationPattern>(
        ElementRegister::GetInstance()->MakeUniqueId(), V2::SHEET_WRAPPER_TAG, std::move(callback)));
    auto scrollNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ScrollPattern>());
    auto contentNode = FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    contentNode->MountToParent(scrollNode);
    scrollNode->MountToParent(sheetNode);
    int32_t currentInstanceId = 0;
    SheetManager sheetManager;
    sheetManager.overlayManagerMap_.clear();
    sheetManager.targetIdMap_.clear();
    SheetManager::SheetContentKey sheetContentKey(currentInstanceId, contentNode->GetId());
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    auto overlayManager = PipelineContext::GetCurrentContext()->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    sheetManager.overlayManagerMap_.emplace(sheetContentKey, overlayManager);
    sheetManager.targetIdMap_.emplace(sheetContentKey, 0);

    int32_t ret = sheetManager.CloseBindSheetByUIContext(contentNode, currentInstanceId);
    EXPECT_EQ(ret, ERROR_CODE_NO_ERROR);
    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: RemoveSheetByESCTest001
 * @tc.desc: Test RemoveSheetByESC return false when sheetFocusId_ is null.
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, RemoveSheetByESCTest001, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();

    SheetManager sheetManager;
    sheetManager.SetFocusSheetId(std::nullopt);
    auto focusId = sheetManager.GetFocusSheetId();
    EXPECT_FALSE(focusId.has_value());
    auto ret = sheetManager.RemoveSheetByESC();
    EXPECT_FALSE(ret);

    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: RemoveSheetByESCTest002
 * @tc.desc: Test RemoveSheetByESC return false when sheetNode is null.
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, RemoveSheetByESCTest002, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    
    SheetManager sheetManager;
    sheetManager.SetFocusSheetId(NUM_0);
    auto focusId = sheetManager.GetFocusSheetId();
    EXPECT_TRUE(focusId.has_value());
    auto ret = sheetManager.RemoveSheetByESC();
    EXPECT_FALSE(ret);

    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: RemoveSheetByESCTest003
 * @tc.desc: Test RemoveSheetByESC return false when sheetPattern is null.
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, RemoveSheetByESCTest003, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    
    SheetManager sheetManager;
    auto uniqueId = ElementRegister::GetInstance()->MakeUniqueId();
    sheetManager.SetFocusSheetId(uniqueId);
    auto focusId = sheetManager.GetFocusSheetId();
    EXPECT_TRUE(focusId.has_value());

    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, uniqueId,
        AceType::MakeRefPtr<Pattern>());
    auto ret = sheetManager.RemoveSheetByESC();
    EXPECT_FALSE(ret);

    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: RemoveSheetByESCTest004
 * @tc.desc: Test RemoveSheetByESC return false when GetAnimationProcess return true.
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, RemoveSheetByESCTest004, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    
    SheetManager sheetManager;
    auto uniqueId = ElementRegister::GetInstance()->MakeUniqueId();
    sheetManager.SetFocusSheetId(uniqueId);
    auto focusId = sheetManager.GetFocusSheetId();
    EXPECT_TRUE(focusId.has_value());

    auto targetId = NUM_0;
    auto targetTag = "";
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, uniqueId,
        AceType::MakeRefPtr<SheetPresentationPattern>(targetId, targetTag, std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->SetAnimationProcess(true);
    EXPECT_TRUE(sheetPattern->GetAnimationProcess());
    
    auto ret = sheetManager.RemoveSheetByESC();
    EXPECT_FALSE(ret);

    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: RemoveSheetByESCTest005
 * @tc.desc: Test RemoveSheetByESC return false when overlayManager is null.
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, RemoveSheetByESCTest005, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    
    SheetManager sheetManager;
    auto uniqueId = ElementRegister::GetInstance()->MakeUniqueId();
    sheetManager.SetFocusSheetId(uniqueId);
    auto focusId = sheetManager.GetFocusSheetId();
    EXPECT_TRUE(focusId.has_value());

    auto targetId = NUM_0;
    auto targetTag = "";
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, uniqueId,
        AceType::MakeRefPtr<MockSheetPresentationPattern>(targetId, targetTag, std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<MockSheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->SetAnimationProcess(false);
    EXPECT_FALSE(sheetPattern->GetAnimationProcess());
    sheetPattern->SetOverlay(nullptr);
    EXPECT_EQ(sheetPattern->GetOverlayManager(), nullptr);
    
    auto ret = sheetManager.RemoveSheetByESC();
    EXPECT_FALSE(ret);

    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: RemoveSheetByESCTest006
 * @tc.desc: Test RemoveSheetByESC return true.
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, RemoveSheetByESCTest006, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    
    SheetManager sheetManager;
    auto uniqueId = ElementRegister::GetInstance()->MakeUniqueId();
    sheetManager.SetFocusSheetId(uniqueId);
    auto focusId = sheetManager.GetFocusSheetId();
    EXPECT_TRUE(focusId.has_value());
    EXPECT_EQ(uniqueId, focusId.value());

    auto targetId = ElementRegister::GetInstance()->MakeUniqueId();
    auto targetTag = "TargetNode";
    auto pattern = AceType::MakeRefPtr<Pattern>();
    ASSERT_NE(pattern, nullptr);
    auto targetNode = FrameNode::CreateFrameNode(targetTag, targetId, pattern);
    ASSERT_NE(targetNode, nullptr);
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, focusId.value(),
        AceType::MakeRefPtr<MockSheetPresentationPattern>(targetId, targetTag, std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<MockSheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    sheetPattern->SetAnimationProcess(false);
    EXPECT_FALSE(sheetPattern->GetAnimationProcess());
    auto overlay = AceType::MakeRefPtr<MockOverlayManager>(nullptr);
    sheetPattern->SetOverlay(overlay);
    overlay->modalStack_.push(sheetNode);
    overlay->isAttachToCustomNode_ = true;
    overlay->rootNodeWeak_ = nullptr;

    EXPECT_NE(sheetPattern->GetOverlayManager(), nullptr);
    EXPECT_TRUE(sheetPattern->GetOverlayManager()->RemoveModalInOverlay());
    auto ret = sheetManager.RemoveSheetByESC();
    EXPECT_FALSE(ret);

    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: SetMaskInteractiveTest001
 * @tc.desc: Test SetMaskInteractive if input is true.
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, SetMaskInteractiveTest001, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    
    SheetManager sheetManager;
    auto uniqueId = ElementRegister::GetInstance()->MakeUniqueId();
    auto targetId = NUM_0;
    auto targetTag = "";

    auto maskPattern = AceType::MakeRefPtr<SheetMaskPattern>(targetId, targetTag);
    auto maskNode = FrameNode::CreateFrameNode("SheetMask", uniqueId, maskPattern);
    ASSERT_NE(maskPattern, nullptr);
    ASSERT_NE(maskNode, nullptr);
    ASSERT_NE(maskNode->GetPattern(), nullptr);
    
    sheetManager.SetMaskInteractive(maskNode, true);
    auto ret = maskPattern->GetIsMaskInteractive();
    EXPECT_TRUE(ret);

    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: SetMaskInteractiveTest002
 * @tc.desc: Test SetMaskInteractive if input is false.
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, SetMaskInteractiveTest002, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    
    SheetManager sheetManager;
    auto uniqueId = ElementRegister::GetInstance()->MakeUniqueId();
    auto targetId = NUM_0;
    auto targetTag = "";

    auto maskPattern = AceType::MakeRefPtr<SheetMaskPattern>(targetId, targetTag);
    auto maskNode = FrameNode::CreateFrameNode("SheetMask", uniqueId, maskPattern);
    ASSERT_NE(maskPattern, nullptr);
    ASSERT_NE(maskNode, nullptr);
    ASSERT_NE(maskNode->GetPattern(), nullptr);
    
    sheetManager.SetMaskInteractive(maskNode, false);
    auto ret = maskPattern->GetIsMaskInteractive();
    EXPECT_FALSE(ret);

    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: CreateSheetMaskShowInSubwindowTest001
 * @tc.desc: Test CreateSheetMaskShowInSubwindow return null if container is null.
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, CreateSheetMaskShowInSubwindowTest001, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    
    // create targetNode
    auto targetId = ElementRegister::GetInstance()->MakeUniqueId();
    auto targetTag = "TargetNode";
    auto pattern = AceType::MakeRefPtr<Pattern>();
    ASSERT_NE(pattern, nullptr);
    auto targetNode = FrameNode::CreateFrameNode(targetTag, targetId, pattern);
    ASSERT_NE(targetNode, nullptr);

    // create sheetNode
    auto sheetNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto callback = [](const std::string&) {};
    auto sheetPattern = AceType::MakeRefPtr<MockSheetPresentationPattern>(targetId, targetTag, std::move(callback));
    ASSERT_NE(sheetPattern, nullptr);
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, sheetNodeId, sheetPattern);
    ASSERT_NE(sheetNode, nullptr);

    // create sheetWrapperNode
    auto sheetWrapperId = ElementRegister::GetInstance()->MakeUniqueId();
    auto sheetWrapperPattern = AceType::MakeRefPtr<SheetWrapperPattern>(targetId, targetTag);
    ASSERT_NE(sheetWrapperPattern, nullptr);
    auto sheetWrapperNode = FrameNode::CreateFrameNode(V2::SHEET_WRAPPER_TAG, sheetWrapperId, sheetWrapperPattern);
    ASSERT_NE(sheetWrapperNode, nullptr);

    // make sure the container is null
    MockContainer::TearDown();

    NG::SheetStyle sheetStyle;
    auto ret = SheetView::CreateSheetMaskShowInSubwindow(sheetNode, sheetWrapperNode, targetNode, sheetStyle);
    EXPECT_EQ(ret, nullptr);
    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: CreateSheetMaskShowInSubwindowTest002
 * @tc.desc: Test CreateSheetMaskShowInSubwindow return null if container is not subContainer.
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, CreateSheetMaskShowInSubwindowTest002, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    
    // create targetNode
    auto targetId = ElementRegister::GetInstance()->MakeUniqueId();
    auto targetTag = "TargetNode";
    auto pattern = AceType::MakeRefPtr<Pattern>();
    ASSERT_NE(pattern, nullptr);
    auto targetNode = FrameNode::CreateFrameNode(targetTag, targetId, pattern);
    ASSERT_NE(targetNode, nullptr);

    // create sheetNode
    auto sheetNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto callback = [](const std::string&) {};
    auto sheetPattern = AceType::MakeRefPtr<MockSheetPresentationPattern>(targetId, targetTag, std::move(callback));
    ASSERT_NE(sheetPattern, nullptr);
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, sheetNodeId, sheetPattern);
    ASSERT_NE(sheetNode, nullptr);

    // create sheetWrapperNode
    auto sheetWrapperId = ElementRegister::GetInstance()->MakeUniqueId();
    auto sheetWrapperPattern = AceType::MakeRefPtr<SheetWrapperPattern>(targetId, targetTag);
    ASSERT_NE(sheetWrapperPattern, nullptr);
    auto sheetWrapperNode = FrameNode::CreateFrameNode(V2::SHEET_WRAPPER_TAG, sheetWrapperId, sheetWrapperPattern);
    ASSERT_NE(sheetWrapperNode, nullptr);

    MockContainer::SetUp();
    NG::SheetStyle sheetStyle;
    auto ret = SheetView::CreateSheetMaskShowInSubwindow(sheetNode, sheetWrapperNode, targetNode, sheetStyle);
    EXPECT_EQ(ret, nullptr);

    MockContainer::TearDown();
    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: CreateSheetMaskShowInSubwindowTest003
 * @tc.desc: Test CreateSheetMaskShowInSubwindow return null if sheetWrapperPattern is null.
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, CreateSheetMaskShowInSubwindowTest003, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    
    // create targetNode
    auto targetId = ElementRegister::GetInstance()->MakeUniqueId();
    auto targetTag = "TargetNode";
    auto pattern = AceType::MakeRefPtr<Pattern>();
    ASSERT_NE(pattern, nullptr);
    auto targetNode = FrameNode::CreateFrameNode(targetTag, targetId, pattern);
    ASSERT_NE(targetNode, nullptr);

    // create sheetNode
    auto sheetNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto callback = [](const std::string&) {};
    auto sheetPattern = AceType::MakeRefPtr<MockSheetPresentationPattern>(targetId, targetTag, std::move(callback));
    ASSERT_NE(sheetPattern, nullptr);
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, sheetNodeId, sheetPattern);
    ASSERT_NE(sheetNode, nullptr);

    // create sheetWrapperNode
    auto sheetWrapperId = ElementRegister::GetInstance()->MakeUniqueId();
    auto sheetWrapperPattern = AceType::MakeRefPtr<SheetWrapperPattern>(targetId, targetTag);
    ASSERT_NE(sheetWrapperPattern, nullptr);
    auto sheetWrapperNode = FrameNode::CreateFrameNode(V2::SHEET_WRAPPER_TAG, sheetWrapperId, sheetWrapperPattern);
    ASSERT_NE(sheetWrapperNode, nullptr);

    MockContainer::SetUp();
    auto container = AceType::DynamicCast<MockContainer>(Container::Current());
    ASSERT_NE(container, nullptr);
    container->isSubContainer_ = false;
    EXPECT_FALSE(container->IsSubContainer());

    NG::SheetStyle sheetStyle;
    auto ret = SheetView::CreateSheetMaskShowInSubwindow(sheetNode, sheetWrapperNode, targetNode, sheetStyle);
    EXPECT_EQ(ret, nullptr);

    MockContainer::TearDown();
    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: CreateSheetMaskShowInSubwindowTest004
 * @tc.desc: Test maskNode save success after CreateSheetMaskShowInSubwindow.
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, CreateSheetMaskShowInSubwindowTest004, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    
    // create targetNode
    auto targetId = ElementRegister::GetInstance()->MakeUniqueId();
    auto targetTag = "TargetNode";
    auto pattern = AceType::MakeRefPtr<Pattern>();
    ASSERT_NE(pattern, nullptr);
    auto targetNode = FrameNode::CreateFrameNode(targetTag, targetId, pattern);
    ASSERT_NE(targetNode, nullptr);

    // create sheetNode
    auto sheetNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto callback = [](const std::string&) {};
    auto sheetPattern = AceType::MakeRefPtr<MockSheetPresentationPattern>(targetId, targetTag, std::move(callback));
    ASSERT_NE(sheetPattern, nullptr);
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, sheetNodeId, sheetPattern);
    ASSERT_NE(sheetNode, nullptr);

    // create sheetWrapperNode
    auto sheetWrapperId = ElementRegister::GetInstance()->MakeUniqueId();
    auto sheetWrapperPattern = AceType::MakeRefPtr<SheetWrapperPattern>(targetId, targetTag);
    ASSERT_NE(sheetWrapperPattern, nullptr);
    auto sheetWrapperNode = FrameNode::CreateFrameNode(V2::SHEET_WRAPPER_TAG, sheetWrapperId, sheetWrapperPattern);
    ASSERT_NE(sheetWrapperNode, nullptr);

    MockContainer::SetUp();
    auto container = AceType::DynamicCast<MockContainer>(Container::Current());
    ASSERT_NE(container, nullptr);
    container->isSubContainer_ = true;
    EXPECT_TRUE(container->IsSubContainer());

    NG::SheetStyle sheetStyle;
    sheetWrapperPattern->isShowInUEC_ = true;
    EXPECT_TRUE(sheetWrapperPattern->ShowInUEC());
    auto maskNode = SheetView::CreateSheetMaskShowInSubwindow(sheetNode, sheetWrapperNode, targetNode, sheetStyle);
    ASSERT_NE(maskNode, nullptr);
    // Test maskNode mount success
    auto parentOfMaskNode = maskNode->GetParentFrameNode();
    EXPECT_NE(parentOfMaskNode, nullptr);
    EXPECT_EQ(parentOfMaskNode->GetId(), sheetWrapperNode->GetId());
    EXPECT_EQ(parentOfMaskNode->GetTag(), sheetWrapperNode->GetTag());
    // Test sheetPageNode mount success
    auto parentOfSheetNode = sheetNode->GetParentFrameNode();
    EXPECT_NE(parentOfSheetNode, nullptr);
    EXPECT_EQ(parentOfSheetNode->GetId(), sheetWrapperNode->GetId());
    EXPECT_EQ(parentOfSheetNode->GetTag(), sheetWrapperNode->GetTag());
    // Test targetNode save success
    auto maskPattern = maskNode->GetPattern<SheetMaskPattern>();
    EXPECT_NE(maskPattern, nullptr);
    auto targetNodeFromMask = maskPattern->GetTargetNode();
    EXPECT_NE(targetNodeFromMask, nullptr);
    EXPECT_EQ(targetNodeFromMask->GetId(), targetNode->GetId());
    EXPECT_EQ(targetNodeFromMask->GetTag(), targetNode->GetTag());
    // Test maskNode save success
    auto maskNodeFromWrapper = sheetWrapperPattern->GetSheetMaskNode();
    EXPECT_NE(maskNodeFromWrapper, nullptr);
    EXPECT_EQ(maskNodeFromWrapper->GetId(), maskNode->GetId());
    EXPECT_EQ(maskNodeFromWrapper->GetTag(), maskNode->GetTag());
    // Test sheetPageNode save success
    auto sheetPageNodeFromWrapper = sheetWrapperPattern->GetSheetPageNode();
    EXPECT_NE(sheetPageNodeFromWrapper, nullptr);
    EXPECT_EQ(sheetPageNodeFromWrapper->GetId(), sheetNode->GetId());
    EXPECT_EQ(sheetPageNodeFromWrapper->GetTag(), sheetNode->GetTag());

    MockContainer::TearDown();
    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: CreateSheetMaskShowInSubwindowTest005
 * @tc.desc: Test maskNode save success after CreateSheetMaskShowInSubwindow.
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, CreateSheetMaskShowInSubwindowTest005, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    
    // create targetNode
    auto targetId = ElementRegister::GetInstance()->MakeUniqueId();
    auto targetTag = "TargetNode";
    auto pattern = AceType::MakeRefPtr<Pattern>();
    ASSERT_NE(pattern, nullptr);
    auto targetNode = FrameNode::CreateFrameNode(targetTag, targetId, pattern);
    ASSERT_NE(targetNode, nullptr);

    // create sheetNode
    auto sheetNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto callback = [](const std::string&) {};
    auto sheetPattern = AceType::MakeRefPtr<MockSheetPresentationPattern>(targetId, targetTag, std::move(callback));
    ASSERT_NE(sheetPattern, nullptr);
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, sheetNodeId, sheetPattern);
    ASSERT_NE(sheetNode, nullptr);

    // create sheetWrapperNode
    auto sheetWrapperId = ElementRegister::GetInstance()->MakeUniqueId();
    auto sheetWrapperPattern = AceType::MakeRefPtr<SheetWrapperPattern>(targetId, targetTag);
    ASSERT_NE(sheetWrapperPattern, nullptr);
    auto sheetWrapperNode = FrameNode::CreateFrameNode(V2::SHEET_WRAPPER_TAG, sheetWrapperId, sheetWrapperPattern);
    ASSERT_NE(sheetWrapperNode, nullptr);

    MockContainer::SetUp();
    auto container = AceType::DynamicCast<MockContainer>(Container::Current());
    ASSERT_NE(container, nullptr);
    container->isSubContainer_ = true;
    EXPECT_TRUE(container->IsSubContainer());

    NG::SheetStyle sheetStyle;
    sheetWrapperPattern->isShowInUEC_ = false;
    EXPECT_FALSE(sheetWrapperPattern->ShowInUEC());

    container->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(container->pipelineContext_, nullptr);
    auto maskNode = SheetView::CreateSheetMaskShowInSubwindow(sheetNode, sheetWrapperNode, targetNode, sheetStyle);
    ASSERT_NE(maskNode, nullptr);

    // Test maskNode mount to rootNode success
    auto pipeline = AceType::DynamicCast<MockPipelineContext>(container->pipelineContext_);
    ASSERT_NE(pipeline, nullptr);
    auto overlayManager = pipeline->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto rootNode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootNode, nullptr);
    auto parentOfMaskNode = maskNode->GetParentFrameNode();
    ASSERT_NE(parentOfMaskNode, nullptr);
    EXPECT_EQ(parentOfMaskNode->GetId(), rootNode->GetId());
    EXPECT_EQ(parentOfMaskNode->GetTag(), rootNode->GetTag());
    // Test sheetPageNode mount success
    auto parentOfSheetNode = sheetNode->GetParentFrameNode();
    ASSERT_NE(parentOfSheetNode, nullptr);
    EXPECT_EQ(parentOfSheetNode->GetId(), sheetWrapperNode->GetId());
    EXPECT_EQ(parentOfSheetNode->GetTag(), sheetWrapperNode->GetTag());
    // Test targetNode save success
    auto maskPattern = maskNode->GetPattern<SheetMaskPattern>();
    ASSERT_NE(maskPattern, nullptr);
    auto targetNodeFromMask = maskPattern->GetTargetNode();
    EXPECT_NE(targetNodeFromMask, nullptr);
    EXPECT_EQ(targetNodeFromMask->GetId(), targetNode->GetId());
    EXPECT_EQ(targetNodeFromMask->GetTag(), targetNode->GetTag());
    // Test maskNode save success
    auto maskNodeFromWrapper = sheetWrapperPattern->GetSheetMaskNode();
    ASSERT_NE(maskNodeFromWrapper, nullptr);
    EXPECT_EQ(maskNodeFromWrapper->GetId(), maskNode->GetId());
    EXPECT_EQ(maskNodeFromWrapper->GetTag(), maskNode->GetTag());
    // Test sheetPageNode save success
    auto sheetPageNodeFromWrapper = sheetWrapperPattern->GetSheetPageNode();
    ASSERT_NE(sheetPageNodeFromWrapper, nullptr);
    EXPECT_EQ(sheetPageNodeFromWrapper->GetId(), sheetNode->GetId());
    EXPECT_EQ(sheetPageNodeFromWrapper->GetTag(), sheetNode->GetTag());

    // Set nullptr in advance, otherwise it will become a wild pointer and cause a crash.
    maskNode->context_ = nullptr;
    MockContainer::TearDown();
    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: OnBindSheet001
 * @tc.desc: Branch: if (sheetStyle.enableFloatingDragBar.value_or(false))
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, OnBindSheet001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node.
     */
    SheetOthersTestNg::SetUpTestCase();
    auto targetNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    /**
     * @tc.steps: step2. create builder.
     */
    auto builderFunc = []() -> RefPtr<UINode> {
        auto frameNode =
            FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
                []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        auto childFrameNode =
            FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
                []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        frameNode->AddChild(childFrameNode);
        return frameNode;
    };

    auto buildTitleNodeFunc = []() -> RefPtr<UINode> { return nullptr; };

    /**
     * @tc.steps: step3. create sheet node, set showDragBar false.
     * @tc.expected: enableFloatingDragBar is false.
     */
    SheetStyle sheetStyle;
    sheetStyle.enableFloatingDragBar = true;
    sheetStyle.showDragBar = false;
    bool isShow = true;
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    pipelineContext->overlayManager_ = overlayManager;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc), std::move(buildTitleNodeFunc), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    EXPECT_EQ(sheetStyle.enableFloatingDragBar, false);

    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: GetDragBarHeight001
 * @tc.desc: Branch: (dragBarLayoutProperty->GetVisibility() == VisibleType::GONE)
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, GetDragBarHeight001, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    auto titleBuilder = FrameNode::CreateFrameNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto builder = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto operationColumn = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto callback = [](const std::string&) {};
    SheetStyle sheetStyle;
    sheetStyle.detents = { SheetHeight({ 300.0_vp }), SheetHeight({ 700.0_vp }) };
    sheetStyle.isTitleBuilder = true;
    sheetStyle.enableFloatingDragBar = false;
    auto sheetNode = SheetView::CreateSheetPage(0, "", builder, titleBuilder, std::move(callback), sheetStyle);
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();

    SheetView::CreateDragBarNode(titleBuilder, operationColumn, sheetStyle, sheetNode);
    auto childIterator = sheetNode->children_.begin();
    auto dragBarNode = AceType::DynamicCast<FrameNode>(*childIterator);
    ASSERT_NE(dragBarNode, nullptr);

    auto dragBarLayoutProperty = dragBarNode->GetLayoutProperty();
    ASSERT_NE(dragBarLayoutProperty, nullptr);

    dragBarLayoutProperty->UpdateVisibility(VisibleType::GONE);
    EXPECT_EQ(sheetPattern->GetDragBarHeight(dragBarNode), 0.0_vp);

    dragBarLayoutProperty->UpdateVisibility(VisibleType::INVISIBLE);
    EXPECT_EQ(sheetPattern->GetDragBarHeight(dragBarNode), 16.0_vp);
    SheetOthersTestNg::TearDownTestCase();
}
} // namespace OHOS::Ace::NG
