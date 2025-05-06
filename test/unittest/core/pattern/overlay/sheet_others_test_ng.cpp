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

#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_manager.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_view.h"
#include "core/components_ng/pattern/overlay/sheet_wrapper_pattern.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/sheet/sheet_mask_pattern.h"
#include "core/components_ng/pattern/stage/page_pattern.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr int32_t SHEET_DETENTS_TWO = 2;
constexpr int32_t SHEET_DETENTS_THREE = 3;
constexpr int32_t ERROR_CODE_NO_ERROR = 0;
constexpr int32_t ERROR_CODE_BIND_SHEET_CONTENT_NOT_FOUND = 120003;
constexpr int32_t NUM_0 = 0;

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
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void SheetOthersTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        if (type == SheetTheme::TypeId()) {
            return AceType::MakeRefPtr<SheetTheme>();
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
 * @tc.desc: Increase the coverage of SheetView::CreateOperationColumnNode function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, CreateOperationColumnNode001, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    auto titleBuilder = FrameNode::CreateFrameNode("Title", 101, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 201,
        AceType::MakeRefPtr<SheetPresentationPattern>(301, "SheetPresentation", std::move(callback)));
    auto sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(sheetLayoutProperty, nullptr);
    NG::SheetStyle sheetStyle;
    sheetLayoutProperty->UpdateSheetStyle(sheetStyle);
    EXPECT_FALSE(sheetStyle.isTitleBuilder.has_value());
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    EXPECT_NE(pipeline->GetFontScale(), pipeline->GetTheme<SheetTheme>()->GetSheetNormalScale());
    SheetView::CreateOperationColumnNode(titleBuilder, sheetStyle, sheetNode);

    pipeline->fontScale_ = pipeline->GetTheme<SheetTheme>()->GetSheetNormalScale();
    EXPECT_EQ(pipeline->GetFontScale(), pipeline->GetTheme<SheetTheme>()->GetSheetNormalScale());
    SheetView::CreateOperationColumnNode(titleBuilder, sheetStyle, sheetNode);

    sheetStyle.isTitleBuilder = true;
    pipeline->fontScale_ = pipeline->GetTheme<SheetTheme>()->GetSheetNormalScale();
    EXPECT_TRUE(sheetStyle.isTitleBuilder.has_value());
    EXPECT_FALSE(sheetStyle.sheetTitle.has_value());
    EXPECT_FALSE(sheetStyle.sheetSubtitle.has_value());
    SheetView::CreateOperationColumnNode(titleBuilder, sheetStyle, sheetNode);
    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: CreateOperationColumnNode002
 * @tc.desc: Increase the coverage of SheetView::CreateOperationColumnNode function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, CreateOperationColumnNode002, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    auto titleBuilder = FrameNode::CreateFrameNode("Title", 101, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 201,
        AceType::MakeRefPtr<SheetPresentationPattern>(301, "SheetPresentation", std::move(callback)));
    auto sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(sheetLayoutProperty, nullptr);
    NG::SheetStyle sheetStyle;
    sheetLayoutProperty->UpdateSheetStyle(sheetStyle);
    sheetStyle.isTitleBuilder = true;
    sheetStyle.sheetSubtitle = "sheetSubtitle";
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->fontScale_ = pipeline->GetTheme<SheetTheme>()->GetSheetNormalScale();
    EXPECT_TRUE(sheetStyle.isTitleBuilder.has_value());
    EXPECT_EQ(pipeline->GetFontScale(), pipeline->GetTheme<SheetTheme>()->GetSheetNormalScale());
    EXPECT_FALSE(sheetStyle.sheetTitle.has_value());
    EXPECT_TRUE(sheetStyle.sheetSubtitle.has_value());
    SheetView::CreateOperationColumnNode(titleBuilder, sheetStyle, sheetNode);

    sheetStyle.isTitleBuilder = true;
    sheetStyle.sheetTitle = "sheetTitle";
    sheetStyle.sheetSubtitle = "sheetSubtitle";
    pipeline->fontScale_ = pipeline->GetTheme<SheetTheme>()->GetSheetNormalScale();
    EXPECT_TRUE(sheetStyle.sheetTitle.has_value());
    SheetView::CreateOperationColumnNode(titleBuilder, sheetStyle, sheetNode);
    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: CreateDragBarNode001
 * @tc.desc: Increase the coverage of SheetView::CreateDragBarNode function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, CreateDragBarNode001, TestSize.Level1)
{
    auto titleBuilder = FrameNode::CreateFrameNode("Title", 101, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto operationColumn = FrameNode::CreateFrameNode("Column", 201, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 301,
        AceType::MakeRefPtr<SheetPresentationPattern>(401, "SheetPresentation", std::move(callback)));
    auto sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(sheetLayoutProperty, nullptr);
    NG::SheetStyle sheetStyle;
    sheetLayoutProperty->UpdateSheetStyle(sheetStyle);
    EXPECT_NE(sheetStyle.detents.size(), SHEET_DETENTS_TWO);
    EXPECT_NE(sheetStyle.detents.size(), SHEET_DETENTS_THREE);
    EXPECT_FALSE(sheetStyle.isTitleBuilder.has_value());
    SheetView::CreateDragBarNode(titleBuilder, operationColumn, sheetStyle, sheetNode);

    SheetHeight detent;
    detent.sheetMode = SheetMode::AUTO;
    sheetStyle.detents.emplace_back(detent);
    detent.sheetMode = SheetMode::MEDIUM;
    sheetStyle.detents.emplace_back(detent);
    detent.sheetMode = SheetMode::LARGE;
    sheetStyle.detents.emplace_back(detent);
    sheetStyle.showDragBar = false;
    sheetStyle.isTitleBuilder = false;
    EXPECT_NE(sheetStyle.detents.size(), SHEET_DETENTS_TWO);
    EXPECT_EQ(sheetStyle.detents.size(), SHEET_DETENTS_THREE);
    EXPECT_FALSE(sheetStyle.showDragBar.value_or(true));
    EXPECT_TRUE(sheetStyle.isTitleBuilder.has_value());
    EXPECT_EQ(SheetView::BuildTitleColumn(sheetNode, sheetStyle), nullptr);
    SheetView::CreateDragBarNode(titleBuilder, operationColumn, sheetStyle, sheetNode);

    sheetStyle.detents.pop_back();
    sheetStyle.showDragBar = true;
    EXPECT_EQ(sheetStyle.detents.size(), SHEET_DETENTS_TWO);
    EXPECT_NE(sheetStyle.detents.size(), SHEET_DETENTS_THREE);
    EXPECT_TRUE(sheetStyle.showDragBar.value_or(true));
    SheetView::CreateDragBarNode(nullptr, operationColumn, sheetStyle, sheetNode);
}

/**
 * @tc.name: CreateDragBarNode002
 * @tc.desc: Increase the coverage of SheetView::CreateDragBarNode function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, CreateDragBarNode002, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    auto operationColumn = FrameNode::CreateFrameNode("Column", 201, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 301,
        AceType::MakeRefPtr<SheetPresentationPattern>(401, "SheetPresentation", std::move(callback)));
    auto sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(sheetLayoutProperty, nullptr);
    NG::SheetStyle sheetStyle;
    sheetLayoutProperty->UpdateSheetStyle(sheetStyle);
    sheetStyle.isTitleBuilder = false;
    EXPECT_TRUE(sheetStyle.isTitleBuilder.has_value());
    EXPECT_NE(SheetView::BuildTitleColumn(sheetNode, sheetStyle), nullptr);
    SheetView::CreateDragBarNode(nullptr, operationColumn, sheetStyle, sheetNode);

    auto titleBuilder = FrameNode::CreateFrameNode("Title", 101, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    EXPECT_FALSE(sheetStyle.isTitleBuilder.value());
    SheetView::CreateDragBarNode(titleBuilder, operationColumn, sheetStyle, sheetNode);

    sheetStyle.isTitleBuilder = true;
    EXPECT_TRUE(sheetStyle.isTitleBuilder.value());
    SheetView::CreateDragBarNode(titleBuilder, operationColumn, sheetStyle, sheetNode);
    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: CreateCloseIconButtonNode001
 * @tc.desc: Increase the coverage of SheetView::CreateCloseIconButtonNode function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, CreateCloseIconButtonNode001, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    NG::SheetStyle sheetStyle;
    int32_t minPlatformVersion = PipelineBase::GetCurrentContext()->minPlatformVersion_;
    PipelineBase::GetCurrentContext()->minPlatformVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TWELVE);
    EXPECT_TRUE(Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN));
    SheetView::CreateCloseIconButtonNode(sheetNode, sheetStyle);

    PipelineBase::GetCurrentContext()->minPlatformVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TEN);
    EXPECT_FALSE(Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN));
    SheetView::CreateCloseIconButtonNode(sheetNode, sheetStyle);
    PipelineBase::GetCurrentContext()->minPlatformVersion_ = minPlatformVersion;
    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: BuildMainTitle001
 * @tc.desc: Increase the coverage of SheetView::BuildMainTitle function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, BuildMainTitle001, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    NG::SheetStyle sheetStyle;
    EXPECT_FALSE(sheetStyle.sheetTitle.has_value());
    SheetView::BuildMainTitle(sheetNode, sheetStyle);

    sheetStyle.sheetTitle = "sheetTitle";
    EXPECT_TRUE(sheetStyle.sheetTitle.has_value());
    SheetView::BuildMainTitle(sheetNode, sheetStyle);
    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: BuildSubTitle001
 * @tc.desc: Increase the coverage of SheetView::BuildSubTitle function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, BuildSubTitle001, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    NG::SheetStyle sheetStyle;
    EXPECT_FALSE(sheetStyle.sheetSubtitle.has_value());
    SheetView::BuildSubTitle(sheetNode, sheetStyle);

    sheetStyle.sheetSubtitle = "sheetSubtitle";
    EXPECT_TRUE(sheetStyle.sheetSubtitle.has_value());
    SheetView::BuildSubTitle(sheetNode, sheetStyle);
    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: BuildTitleColumn001
 * @tc.desc: Increase the coverage of SheetView::BuildTitleColumn function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, BuildTitleColumn001, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    NG::SheetStyle sheetStyle;
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateSheetStyle(sheetStyle);
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->fontScale_ = pipeline->GetTheme<SheetTheme>()->GetSheetNormalScale() + 1;
    sheetStyle.isTitleBuilder = false;

    EXPECT_NE(pipeline->GetFontScale(), pipeline->GetTheme<SheetTheme>()->GetSheetNormalScale());
    EXPECT_TRUE(sheetStyle.isTitleBuilder.has_value());
    EXPECT_FALSE(sheetStyle.isTitleBuilder.value());
    SheetView::BuildTitleColumn(sheetNode, sheetStyle);
    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: BuildTitleColumn002
 * @tc.desc: Increase the coverage of SheetView::BuildTitleColumn function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, BuildTitleColumn002, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    NG::SheetStyle sheetStyle;
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateSheetStyle(sheetStyle);
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->fontScale_ = pipeline->GetTheme<SheetTheme>()->GetSheetNormalScale() + 1;
    sheetStyle.isTitleBuilder = true;

    EXPECT_NE(pipeline->GetFontScale(), pipeline->GetTheme<SheetTheme>()->GetSheetNormalScale());
    EXPECT_TRUE(sheetStyle.isTitleBuilder.has_value());
    EXPECT_TRUE(sheetStyle.isTitleBuilder.value());
    SheetView::BuildTitleColumn(sheetNode, sheetStyle);
    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: BuildTitleColumn003
 * @tc.desc: Increase the coverage of SheetView::BuildTitleColumn function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, BuildTitleColumn003, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    NG::SheetStyle sheetStyle;
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateSheetStyle(sheetStyle);
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->fontScale_ = pipeline->GetTheme<SheetTheme>()->GetSheetNormalScale();

    EXPECT_EQ(pipeline->GetFontScale(), pipeline->GetTheme<SheetTheme>()->GetSheetNormalScale());
    SheetView::BuildTitleColumn(sheetNode, sheetStyle);
    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: BuildTitleColumn004
 * @tc.desc: Increase the coverage of SheetView::BuildTitleColumn function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, BuildTitleColumn004, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    NG::SheetStyle sheetStyle;
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateSheetStyle(sheetStyle);

    EXPECT_FALSE(sheetStyle.sheetTitle.has_value());
    EXPECT_FALSE(sheetStyle.isTitleBuilder.has_value());
    SheetView::BuildTitleColumn(sheetNode, sheetStyle);
    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: BuildTitleColumn005
 * @tc.desc: Increase the coverage of SheetView::BuildTitleColumn function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, BuildTitleColumn005, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    NG::SheetStyle sheetStyle;
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateSheetStyle(sheetStyle);
    sheetStyle.isTitleBuilder = false;

    EXPECT_FALSE(sheetStyle.sheetTitle.has_value());
    EXPECT_TRUE(sheetStyle.isTitleBuilder.has_value());
    EXPECT_FALSE(sheetStyle.isTitleBuilder.value());
    SheetView::BuildTitleColumn(sheetNode, sheetStyle);
    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: BuildTitleColumn006
 * @tc.desc: Increase the coverage of SheetView::BuildTitleColumn function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, BuildTitleColumn006, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    NG::SheetStyle sheetStyle;
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateSheetStyle(sheetStyle);
    sheetStyle.isTitleBuilder = true;

    EXPECT_FALSE(sheetStyle.sheetTitle.has_value());
    EXPECT_TRUE(sheetStyle.isTitleBuilder.has_value());
    EXPECT_TRUE(sheetStyle.isTitleBuilder.value());
    SheetView::BuildTitleColumn(sheetNode, sheetStyle);
    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: BuildTitleColumn007
 * @tc.desc: Increase the coverage of SheetView::BuildTitleColumn function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, BuildTitleColumn007, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    NG::SheetStyle sheetStyle;
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateSheetStyle(sheetStyle);
    sheetStyle.sheetTitle = "sheetTitle";

    EXPECT_TRUE(sheetStyle.sheetTitle.has_value());
    EXPECT_FALSE(sheetStyle.sheetSubtitle.has_value());
    SheetView::BuildTitleColumn(sheetNode, sheetStyle);
    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: BuildTitleColumn008
 * @tc.desc: Increase the coverage of SheetView::BuildTitleColumn function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, BuildTitleColumn008, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    NG::SheetStyle sheetStyle;
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateSheetStyle(sheetStyle);
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->fontScale_ = pipeline->GetTheme<SheetTheme>()->GetSheetNormalScale() + 1;
    sheetStyle.sheetTitle = "sheetTitle";
    sheetStyle.sheetSubtitle = "sheetSubtitle";

    EXPECT_TRUE(sheetStyle.sheetTitle.has_value());
    EXPECT_TRUE(sheetStyle.sheetSubtitle.has_value());
    EXPECT_NE(pipeline->GetFontScale(), pipeline->GetTheme<SheetTheme>()->GetSheetNormalScale());
    SheetView::BuildTitleColumn(sheetNode, sheetStyle);
    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: BuildTitleColumn009
 * @tc.desc: Increase the coverage of SheetView::BuildTitleColumn function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, BuildTitleColumn009, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    NG::SheetStyle sheetStyle;
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateSheetStyle(sheetStyle);
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->fontScale_ = pipeline->GetTheme<SheetTheme>()->GetSheetNormalScale();
    sheetStyle.sheetTitle = "sheetTitle";
    sheetStyle.sheetSubtitle = "sheetSubtitle";

    EXPECT_TRUE(sheetStyle.sheetTitle.has_value());
    EXPECT_TRUE(sheetStyle.sheetSubtitle.has_value());
    EXPECT_EQ(pipeline->GetFontScale(), pipeline->GetTheme<SheetTheme>()->GetSheetNormalScale());
    SheetView::BuildTitleColumn(sheetNode, sheetStyle);
    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: GetOverlayFromPage001
 * @tc.desc: Increase the coverage of SheetManager::GetOverlayFromPage function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, GetOverlayFromPage001, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    auto sheetNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 101,
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    RootNodeType rootNodeType = RootNodeType::PAGE_ETS_TAG;
    int32_t rootNodeId = -1;

    EXPECT_TRUE(rootNodeId <= 0);
    SheetManager sheetManager;
    sheetManager.GetOverlayFromPage(rootNodeId, rootNodeType);
    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: GetOverlayFromPage002
 * @tc.desc: Increase the coverage of SheetManager::GetOverlayFromPage function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, GetOverlayFromPage002, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    auto sheetNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 101,
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    RootNodeType rootNodeType = RootNodeType::PAGE_ETS_TAG;
    int32_t rootNodeId = 101;

    EXPECT_FALSE(rootNodeId <= 0);
    EXPECT_NE(FrameNode::GetFrameNode(sheetNode->tag_, rootNodeId), nullptr);
    SheetManager sheetManager;
    sheetManager.GetOverlayFromPage(rootNodeId, rootNodeType);
    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: GetOverlayFromPage003
 * @tc.desc: Increase the coverage of SheetManager::GetOverlayFromPage function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, GetOverlayFromPage003, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    auto sheetNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 101,
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    RootNodeType rootNodeType = RootNodeType::NAVDESTINATION_VIEW_ETS_TAG;
    int32_t rootNodeId = 101;
    sheetNode->tag_ = V2::NAVDESTINATION_VIEW_ETS_TAG;

    EXPECT_FALSE(rootNodeId <= 0);
    EXPECT_NE(FrameNode::GetFrameNode(sheetNode->tag_, rootNodeId), nullptr);
    SheetManager sheetManager;
    sheetManager.GetOverlayFromPage(rootNodeId, rootNodeType);
    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: GetOverlayFromPage004
 * @tc.desc: Increase the coverage of SheetManager::GetOverlayFromPage function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, GetOverlayFromPage004, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    auto sheetNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 101,
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    RootNodeType rootNodeType = RootNodeType::WINDOW_SCENE_ETS_TAG;
    int32_t rootNodeId = 101;
    sheetNode->tag_ = V2::WINDOW_SCENE_ETS_TAG;

    EXPECT_FALSE(rootNodeId <= 0);
    EXPECT_NE(FrameNode::GetFrameNode(sheetNode->tag_, rootNodeId), nullptr);
    SheetManager sheetManager;
    sheetManager.GetOverlayFromPage(rootNodeId, rootNodeType);
    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: UpdateBindSheetByUIContext001
 * @tc.desc: Increase the coverage of SheetManager::UpdateBindSheetByUIContext function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, UpdateBindSheetByUIContext001, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    auto scrollNode = FrameNode::CreateFrameNode("Scroll", 201, AceType::MakeRefPtr<ScrollPattern>());
    auto contentNode = FrameNode::GetOrCreateFrameNode("SheetContent", 301,
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
    ASSERT_EQ(sheetManager.overlayManagerMap_.find(sheetContentKey), sheetManager.overlayManagerMap_.end());
    int32_t ret = sheetManager.UpdateBindSheetByUIContext(contentNode, sheetStyle, isPartialUpdate, currentInstanceId);
    EXPECT_EQ(ret, ERROR_CODE_BIND_SHEET_CONTENT_NOT_FOUND);
    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: UpdateBindSheetByUIContext002
 * @tc.desc: Increase the coverage of SheetManager::UpdateBindSheetByUIContext function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, UpdateBindSheetByUIContext002, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    auto scrollNode = FrameNode::CreateFrameNode("Scroll", 201, AceType::MakeRefPtr<ScrollPattern>());
    auto contentNode = FrameNode::GetOrCreateFrameNode("SheetContent", 301,
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

    ASSERT_NE(sheetManager.overlayManagerMap_.find(sheetContentKey), sheetManager.overlayManagerMap_.end());
    ASSERT_EQ(sheetManager.targetIdMap_.find(sheetContentKey), sheetManager.targetIdMap_.end());
    int32_t ret = sheetManager.UpdateBindSheetByUIContext(contentNode, sheetStyle, isPartialUpdate, currentInstanceId);
    EXPECT_EQ(ret, ERROR_CODE_BIND_SHEET_CONTENT_NOT_FOUND);
    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: UpdateBindSheetByUIContext003
 * @tc.desc: Increase the coverage of SheetManager::UpdateBindSheetByUIContext function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, UpdateBindSheetByUIContext003, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    auto scrollNode = FrameNode::CreateFrameNode("Scroll", 201, AceType::MakeRefPtr<ScrollPattern>());
    auto contentNode = FrameNode::GetOrCreateFrameNode("SheetContent", 301,
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

    ASSERT_NE(sheetManager.overlayManagerMap_.find(sheetContentKey), sheetManager.overlayManagerMap_.end());
    ASSERT_NE(sheetManager.targetIdMap_.find(sheetContentKey), sheetManager.targetIdMap_.end());
    int32_t ret = sheetManager.UpdateBindSheetByUIContext(contentNode, sheetStyle, isPartialUpdate, currentInstanceId);
    EXPECT_EQ(ret, ERROR_CODE_NO_ERROR);
    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: CloseBindSheetByUIContext001
 * @tc.desc: Increase the coverage of SheetManager::CloseBindSheetByUIContext function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, CloseBindSheetByUIContext001, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    auto scrollNode = FrameNode::CreateFrameNode("Scroll", 201, AceType::MakeRefPtr<ScrollPattern>());
    auto contentNode = FrameNode::GetOrCreateFrameNode("SheetContent", 301,
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    contentNode->MountToParent(scrollNode);
    scrollNode->MountToParent(sheetNode);
    int32_t currentInstanceId = 0;
    SheetManager sheetManager;
    sheetManager.overlayManagerMap_.clear();
    sheetManager.targetIdMap_.clear();

    SheetManager::SheetContentKey sheetContentKey(currentInstanceId, contentNode->GetId());
    ASSERT_EQ(sheetManager.overlayManagerMap_.find(sheetContentKey), sheetManager.overlayManagerMap_.end());
    int32_t ret = sheetManager.CloseBindSheetByUIContext(contentNode, currentInstanceId);
    EXPECT_EQ(ret, ERROR_CODE_BIND_SHEET_CONTENT_NOT_FOUND);
    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: CloseBindSheetByUIContext002
 * @tc.desc: Increase the coverage of SheetManager::CloseBindSheetByUIContext function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, CloseBindSheetByUIContext002, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    auto scrollNode = FrameNode::CreateFrameNode("Scroll", 201, AceType::MakeRefPtr<ScrollPattern>());
    auto contentNode = FrameNode::GetOrCreateFrameNode("SheetContent", 301,
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    contentNode->MountToParent(scrollNode);
    scrollNode->MountToParent(sheetNode);
    int32_t currentInstanceId = 0;
    SheetManager sheetManager;
    sheetManager.overlayManagerMap_.clear();
    sheetManager.targetIdMap_.clear();
    SheetManager::SheetContentKey sheetContentKey(currentInstanceId, contentNode->GetId());
    sheetManager.overlayManagerMap_.emplace(sheetContentKey, nullptr);

    ASSERT_NE(sheetManager.overlayManagerMap_.find(sheetContentKey), sheetManager.overlayManagerMap_.end());
    ASSERT_EQ(sheetManager.targetIdMap_.find(sheetContentKey), sheetManager.targetIdMap_.end());
    int32_t ret = sheetManager.CloseBindSheetByUIContext(contentNode, currentInstanceId);
    EXPECT_EQ(ret, ERROR_CODE_BIND_SHEET_CONTENT_NOT_FOUND);
    SheetOthersTestNg::TearDownTestCase();
}

/**
 * @tc.name: CloseBindSheetByUIContext003
 * @tc.desc: Increase the coverage of SheetManager::CloseBindSheetByUIContext function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetOthersTestNg, CloseBindSheetByUIContext003, TestSize.Level1)
{
    SheetOthersTestNg::SetUpTestCase();
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    auto scrollNode = FrameNode::CreateFrameNode("Scroll", 201, AceType::MakeRefPtr<ScrollPattern>());
    auto contentNode = FrameNode::GetOrCreateFrameNode("SheetContent", 301,
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

    ASSERT_NE(sheetManager.overlayManagerMap_.find(sheetContentKey), sheetManager.overlayManagerMap_.end());
    ASSERT_NE(sheetManager.targetIdMap_.find(sheetContentKey), sheetManager.targetIdMap_.end());
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

    MockContainer::TearDown();
    SheetOthersTestNg::TearDownTestCase();
}
} // namespace OHOS::Ace::NG
