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

#include "arc_list_test_ng.h"

#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/arc_scroll/inner/arc_scroll_bar.h"
#include "core/components_ng/pattern/arc_scroll/inner/arc_scroll_bar_overlay_modifier.h"
#include "core/components_ng/pattern/scrollable/scrollable_model_ng.h"
#include "core/components_ng/pattern/arc_list/arc_list_item_pattern.h"
#include "core/components_ng/pattern/list/list_item_layout_property.h"
#include "core/components/list/arc_list_item_theme.h"

namespace OHOS::Ace::NG {

namespace {
constexpr float ARC_LIST_DRAG_OVER_RATES = 0.6f;
} // namespace

class ArcListPatternTestNg : public ArcListTestNg {
public:
};

/**
 * @tc.name: ArcListItemOnThemeScopeUpdate001
 * @tc.desc: Test ArcListItemPattern OnThemeScopeUpdate: API>=26 + CARD + UserNotSetBgColor
 * @tc.type: FUNC
 */
HWTEST_F(ArcListPatternTestNg, ArcListItemOnThemeScopeUpdate001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ArcList with CARD style ArcListItem
     */
    CreateList();
    CreateListItems(1, V2::ListItemStyle::CARD);
    CreateDone();

    /**
     * @tc.steps: step2. Get ArcListItem node and set theme color
     */
    auto arcListItem = GetChildFrameNode(frameNode_, 0);
    ASSERT_NE(arcListItem, nullptr);

    auto pattern = arcListItem->GetPattern<ArcListItemPattern>();
    ASSERT_NE(pattern, nullptr);

    auto renderContext = arcListItem->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdateBackgroundColor(Color::BLUE);

    // Set theme color to RED
    auto arcListItemTheme = MockPipelineContext::pipeline_->GetTheme<ArcListItemTheme>();
    auto originalColor = arcListItemTheme->itemDefaultColor_;
    arcListItemTheme->itemDefaultColor_ = Color::RED;

    /**
     * @tc.steps: step3. Set API version to VERSION_TWENTY_SIX and call OnThemeScopeUpdate
     * @tc.expected: Background color is updated to theme color (RED)
     */
    auto oriApiVersion = arcListItem->apiVersion_;
    arcListItem->apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX);
    pattern->OnThemeScopeUpdate(0);
    auto bgColor = renderContext->GetBackgroundColor();
    EXPECT_TRUE(bgColor.has_value());
    EXPECT_EQ(bgColor.value(), Color::RED);

    // Restore
    arcListItem->apiVersion_ = oriApiVersion;
    arcListItemTheme->itemDefaultColor_ = originalColor;
}

/**
 * @tc.name: ArcListItemOnThemeScopeUpdate002
 * @tc.desc: Test ArcListItemPattern OnThemeScopeUpdate: API>=26 + CARD + UserSetBgColor
 * @tc.type: FUNC
 */
HWTEST_F(ArcListPatternTestNg, ArcListItemOnThemeScopeUpdate002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ArcList with CARD style ArcListItem
     */
    CreateList();
    CreateListItems(1, V2::ListItemStyle::CARD);
    CreateDone();

    /**
     * @tc.steps: step2. Get ArcListItem node and set background color
     */
    auto arcListItem = GetChildFrameNode(frameNode_, 0);
    ASSERT_NE(arcListItem, nullptr);

    auto pattern = arcListItem->GetPattern<ArcListItemPattern>();
    ASSERT_NE(pattern, nullptr);

    auto renderContext = arcListItem->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdateBackgroundColor(Color::BLUE);

    auto layoutProperty = arcListItem->GetLayoutProperty<ListItemLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateIsUserSetBackgroundColor(true);

    /**
     * @tc.steps: step3. Set API version to VERSION_TWENTY_SIX and call OnThemeScopeUpdate
     * @tc.expected: Background color remains unchanged (equal to BLUE)
     */
    auto oriApiVersion = arcListItem->apiVersion_;
    arcListItem->apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX);
    pattern->OnThemeScopeUpdate(0);
    auto bgColor = renderContext->GetBackgroundColor();
    EXPECT_TRUE(bgColor.has_value());
    EXPECT_EQ(bgColor.value(), Color::BLUE);

    arcListItem->apiVersion_ = oriApiVersion;
}

/**
 * @tc.name: ArcListItemOnThemeScopeUpdate003
 * @tc.desc: Test ArcListItemPattern OnThemeScopeUpdate: API>=26 + NONE + UserNotSetBgColor
 * @tc.type: FUNC
 */
HWTEST_F(ArcListPatternTestNg, ArcListItemOnThemeScopeUpdate003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ArcList with NONE style ArcListItem
     */
    CreateList();
    CreateListItems(1, V2::ListItemStyle::NONE);
    CreateDone();

    /**
     * @tc.steps: step2. Get ArcListItem node and set API version
     */
    auto arcListItem = GetChildFrameNode(frameNode_, 0);
    ASSERT_NE(arcListItem, nullptr);

    auto pattern = arcListItem->GetPattern<ArcListItemPattern>();
    ASSERT_NE(pattern, nullptr);

    auto renderContext = arcListItem->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdateBackgroundColor(Color::BLUE);

    /**
     * @tc.steps: step3. Set API version to VERSION_TWENTY_SIX and call OnThemeScopeUpdate
     * @tc.expected: Background color remains unchanged due to NONE style
     */
    auto oriApiVersion = arcListItem->apiVersion_;
    arcListItem->apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX);
    pattern->OnThemeScopeUpdate(0);
    auto bgColor = arcListItem->GetRenderContext()->GetBackgroundColor();
    EXPECT_TRUE(bgColor.has_value());
    EXPECT_EQ(bgColor.value(), Color::BLUE);

    arcListItem->apiVersion_ = oriApiVersion;
}

/**
 * @tc.name: ArcListItemOnThemeScopeUpdate004
 * @tc.desc: Test ArcListItemPattern OnThemeScopeUpdate: API>=26 + NONE + UserSetBgColor
 * @tc.type: FUNC
 */
HWTEST_F(ArcListPatternTestNg, ArcListItemOnThemeScopeUpdate004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ArcList with NONE style ArcListItem
     */
    CreateList();
    CreateListItems(1, V2::ListItemStyle::NONE);
    CreateDone();

    /**
     * @tc.steps: step2. Get ArcListItem node and set background color
     */
    auto arcListItem = GetChildFrameNode(frameNode_, 0);
    ASSERT_NE(arcListItem, nullptr);

    auto pattern = arcListItem->GetPattern<ArcListItemPattern>();
    ASSERT_NE(pattern, nullptr);

    auto renderContext = arcListItem->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdateBackgroundColor(Color::GREEN);

    auto layoutProperty = arcListItem->GetLayoutProperty<ListItemLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateIsUserSetBackgroundColor(true);

    /**
     * @tc.steps: step3. Set API version to VERSION_TWENTY_SIX and call OnThemeScopeUpdate
     * @tc.expected: Background color remains unchanged (equal to GREEN)
     */
    auto oriApiVersion = arcListItem->apiVersion_;
    arcListItem->apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX);
    pattern->OnThemeScopeUpdate(0);
    auto bgColor = renderContext->GetBackgroundColor();
    EXPECT_TRUE(bgColor.has_value());
    EXPECT_EQ(bgColor.value(), Color::GREEN);

    arcListItem->apiVersion_ = oriApiVersion;
}

/**
 * @tc.name: ArcListItemOnThemeScopeUpdate005
 * @tc.desc: Test ArcListItemPattern OnThemeScopeUpdate: API<26 + CARD + UserNotSetBgColor
 * @tc.type: FUNC
 */
HWTEST_F(ArcListPatternTestNg, ArcListItemOnThemeScopeUpdate005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ArcList with CARD style ArcListItem
     */
    CreateList();
    CreateListItems(1, V2::ListItemStyle::CARD);
    CreateDone();

    /**
     * @tc.steps: step2. Get ArcListItem node and set background color
     */
    auto arcListItem = GetChildFrameNode(frameNode_, 0);
    ASSERT_NE(arcListItem, nullptr);

    auto pattern = arcListItem->GetPattern<ArcListItemPattern>();
    ASSERT_NE(pattern, nullptr);

    auto renderContext = arcListItem->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdateBackgroundColor(Color::GRAY);

    auto layoutProperty = arcListItem->GetLayoutProperty<ListItemLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateIsUserSetBackgroundColor(false);

    /**
     * @tc.steps: step3. Set API version to VERSION_TWENTY_FIVE and call OnThemeScopeUpdate
     * @tc.expected: Background color remains unchanged (equal to GRAY) due to API < 26
     */
    auto oriApiVersion = arcListItem->apiVersion_;
    arcListItem->apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_FIVE);
    pattern->OnThemeScopeUpdate(0);
    auto bgColor = renderContext->GetBackgroundColor();
    EXPECT_TRUE(bgColor.has_value());
    EXPECT_EQ(bgColor.value(), Color::GRAY);

    arcListItem->apiVersion_ = oriApiVersion;
}

/**
 * @tc.name: ArcListItemOnThemeScopeUpdate006
 * @tc.desc: Test ArcListItemPattern OnThemeScopeUpdate: API<26 + CARD + UserSetBgColor
 * @tc.type: FUNC
 */
HWTEST_F(ArcListPatternTestNg, ArcListItemOnThemeScopeUpdate006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ArcList with CARD style ArcListItem
     */
    CreateList();
    CreateListItems(1, V2::ListItemStyle::CARD);
    CreateDone();

    /**
     * @tc.steps: step2. Get ArcListItem node and set background color
     */
    auto arcListItem = GetChildFrameNode(frameNode_, 0);
    ASSERT_NE(arcListItem, nullptr);

    auto pattern = arcListItem->GetPattern<ArcListItemPattern>();
    ASSERT_NE(pattern, nullptr);

    auto renderContext = arcListItem->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdateBackgroundColor(Color::BLACK);

    auto layoutProperty = arcListItem->GetLayoutProperty<ListItemLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateIsUserSetBackgroundColor(true);

    /**
     * @tc.steps: step3. Set API version to VERSION_TWENTY_FIVE and call OnThemeScopeUpdate
     * @tc.expected: Background color remains unchanged (equal to BLACK)
     */
    auto oriApiVersion = arcListItem->apiVersion_;
    arcListItem->apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_FIVE);
    pattern->OnThemeScopeUpdate(0);
    auto bgColor = renderContext->GetBackgroundColor();
    EXPECT_TRUE(bgColor.has_value());
    EXPECT_EQ(bgColor.value(), Color::BLACK);

    arcListItem->apiVersion_ = oriApiVersion;
}

/**
 * @tc.name: ArcListItemOnThemeScopeUpdate007
 * @tc.desc: Test ArcListItemPattern OnThemeScopeUpdate: API<26 + NONE + UserNotSetBgColor
 * @tc.type: FUNC
 */
HWTEST_F(ArcListPatternTestNg, ArcListItemOnThemeScopeUpdate007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ArcList with NONE style ArcListItem
     */
    CreateList();
    CreateListItems(1, V2::ListItemStyle::NONE);
    CreateDone();

    /**
     * @tc.steps: step2. Get ArcListItem node and set background color
     */
    auto arcListItem = GetChildFrameNode(frameNode_, 0);
    ASSERT_NE(arcListItem, nullptr);

    auto pattern = arcListItem->GetPattern<ArcListItemPattern>();
    ASSERT_NE(pattern, nullptr);

    auto renderContext = arcListItem->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdateBackgroundColor(Color::BLUE);

    auto layoutProperty = arcListItem->GetLayoutProperty<ListItemLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateIsUserSetBackgroundColor(false);

    /**
     * @tc.steps: step3. Set API version to VERSION_TWENTY_FIVE and call OnThemeScopeUpdate
     * @tc.expected: Background color remains unchanged due to API < 26
     */
    auto oriApiVersion = arcListItem->apiVersion_;
    arcListItem->apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_FIVE);
    pattern->OnThemeScopeUpdate(0);
    auto bgColor = renderContext->GetBackgroundColor();
    EXPECT_TRUE(bgColor.has_value());
    EXPECT_EQ(bgColor.value(), Color::BLUE);

    arcListItem->apiVersion_ = oriApiVersion;
}

/**
 * @tc.name: ArcListItemOnThemeScopeUpdate008
 * @tc.desc: Test ArcListItemPattern OnThemeScopeUpdate: API<26 + NONE + UserSetBgColor
 * @tc.type: FUNC
 */
HWTEST_F(ArcListPatternTestNg, ArcListItemOnThemeScopeUpdate008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ArcList with NONE style ArcListItem
     */
    CreateList();
    CreateListItems(1, V2::ListItemStyle::NONE);
    CreateDone();

    /**
     * @tc.steps: step2. Get ArcListItem node and set background color
     */
    auto arcListItem = GetChildFrameNode(frameNode_, 0);
    ASSERT_NE(arcListItem, nullptr);

    auto pattern = arcListItem->GetPattern<ArcListItemPattern>();
    ASSERT_NE(pattern, nullptr);

    auto renderContext = arcListItem->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdateBackgroundColor(Color::GREEN);

    auto layoutProperty = arcListItem->GetLayoutProperty<ListItemLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateIsUserSetBackgroundColor(true);

    /**
     * @tc.steps: step3. Set API version to VERSION_TWENTY_FIVE and call OnThemeScopeUpdate
     * @tc.expected: Background color remains unchanged
     */
    auto oriApiVersion = arcListItem->apiVersion_;
    arcListItem->apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_FIVE);
    pattern->OnThemeScopeUpdate(0);
    auto bgColor = renderContext->GetBackgroundColor();
    EXPECT_TRUE(bgColor.has_value());
    EXPECT_EQ(bgColor.value(), Color::GREEN);

    arcListItem->apiVersion_ = oriApiVersion;
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap001
 * @tc.desc: Test ArcListPattern OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(ArcListPatternTestNg, OnDirtyLayoutWrapperSwap001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ListModelNG model = CreateList();
    CreateListItems(DEFAULT_ITEM_COUNT);
    CreateDone();
    pattern_->SetPredictSnapOffset(100.0);

    auto layoutWrapper = frameNode_->CreateLayoutWrapper(true, true);
    layoutWrapper->layoutAlgorithm_ = nullptr;

    /**
     * @tc.steps: step2. Set the dirtySwapConfig's skipMeasure and skipLayout to true
     */
    DirtySwapConfig dirtySwapConfig;
    dirtySwapConfig.skipMeasure = true;
    dirtySwapConfig.skipLayout = true;

    /**
     * @tc.steps: step3. Call the OnDirtyLayoutWrapperSwap
     * @tc.expected: The function result return false
     */
    auto result = pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap002
 * @tc.desc: Test ArcListPattern OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(ArcListPatternTestNg, OnDirtyLayoutWrapperSwap002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ListModelNG model = CreateList();
    CreateListItems(DEFAULT_ITEM_COUNT);
    CreateDone();
    pattern_->SetPredictSnapOffset(100.0);

    auto layoutWrapper = frameNode_->CreateLayoutWrapper(true, true);
    RefPtr<ArcListLayoutAlgorithm> arcListLayoutAlgorithm = AceType::MakeRefPtr<ArcListLayoutAlgorithm>(0, 2);
    ListItemInfo info = { 2, 2.0f, 4.0f, true };
    std::map<int32_t, ListItemInfo> itemPosition = { std::make_pair(0, info) };
    arcListLayoutAlgorithm->SetItemsPosition(itemPosition);
    arcListLayoutAlgorithm->SetStartHeaderPos(2.0f);
    arcListLayoutAlgorithm->SetHeaderOffset(1.0f);
    arcListLayoutAlgorithm->SetOldHeaderSize(3.0f);
    arcListLayoutAlgorithm->SetOldFirstItemSize(2.0f);
    arcListLayoutAlgorithm->SetHeaderStayNear(false);
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(arcListLayoutAlgorithm);
    layoutWrapper->layoutAlgorithm_ = layoutAlgorithmWrapper;

    /**
     * @tc.steps: step2. Set the dirtySwapConfig's skipMeasure and skipLayout to true
     */
    DirtySwapConfig dirtySwapConfig;
    dirtySwapConfig.skipMeasure = true;
    dirtySwapConfig.skipLayout = false;

    /**
     * @tc.steps: step3. Call the OnDirtyLayoutWrapperSwap
     * @tc.expected: The function result return true
     */
    auto result = pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: ScrollListForFocus
 * @tc.desc: Test ArcListPattern ScrollListForFocus
 * @tc.type: FUNC
 */
HWTEST_F(ArcListPatternTestNg, ScrollListForFocus, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ListModelNG model = CreateList();
    CreateListItems(DEFAULT_ITEM_COUNT);
    CreateDone();
    pattern_->SetPredictSnapOffset(100.0);
    RefPtr<PipelineContext> context = AceType::MakeRefPtr<PipelineContext>();
    frameNode_->context_ = AceType::RawPtr(context);

    /**
     * @tc.steps: step2. Set the isScrollEnd_ to false
     */
    pattern_->isScrollEnd_ = false;

    /**
     * @tc.steps: step3. Call the OnDirtyLayoutWrapperSwap
     * @tc.expected: The function result return true and the isScrollEnd_ to true
     */
    auto result = pattern_->ScrollListForFocus(2, 1, 2);
    frameNode_->context_ = nullptr;
    EXPECT_TRUE(pattern_->isScrollEnd_);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: ToJsonValue
 * @tc.desc: Test ArcListPattern ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(ArcListPatternTestNg, ToJsonValue, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ListModelNG model = CreateList();
    CreateListItems(DEFAULT_ITEM_COUNT);
    CreateDone();
    pattern_->SetPredictSnapOffset(100.0);

    auto json = JsonUtil::Create(true);
    InspectorFilter filter;

    /**
     * @tc.steps: step2. Set the itemPosition_ of pattern
     * and set startIndex_ to 10
     */
    ListItemInfo info = { 2, 2.0f, 4.0f, true };
    std::map<int32_t, ListItemInfo> itemPosition = { { 0, info } };
    pattern_->itemPosition_ = itemPosition;
    pattern_->startIndex_ = 10;

    /**
     * @tc.steps: step3. Call the ToJsonValue
     * @tc.expected: The value with the key "itemStartPos" becomes "3.0f"
     */
    pattern_->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetInt("startIndex"), 10);
    EXPECT_EQ(json->GetDouble("itemStartPos"), 2.0);
    EXPECT_EQ(json->GetString("digitalCrownSensitivity"), "CrownSensitivity.MEDIUM");
}

/**
 * @tc.name: GetItemDisplayInfo
 * @tc.desc: Test ArcListPattern GetItemDisplayInfo
 * @tc.type: FUNC
 */
HWTEST_F(ArcListPatternTestNg, GetItemDisplayInfo, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ListModelNG model = CreateList();
    CreateListItems(DEFAULT_ITEM_COUNT);
    CreateDone();
    pattern_->SetPredictSnapOffset(100.0);

    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    listLayoutProperty->UpdateSpace(Dimension(2.0f));
    LayoutConstraintF layoutConstraintF;
    layoutConstraintF.maxSize = { 6, 6 };
    listLayoutProperty->contentConstraint_ = layoutConstraintF;

    /**
     * @tc.steps: step2. Set the value of the second key of the itemPosition_
     */
    ListItemInfo info = { 2, 2.0f, 4.0f, true };
    pattern_->itemPosition_[2] = info;
    pattern_->SetFriction(FRICTION);
    pattern_->scrollStartMidIndex_ = 3;
    pattern_->contentMainSize_ = 8.0f;
    pattern_->spaceWidth_ = 4.0f;
    pattern_->itemStartIndex_ = -20;
    frameNode_->layoutProperty_ = listLayoutProperty;

    /**
     * @tc.steps: step3. Call the GetItemDisplayInfo
     * @tc.expected: The result of info is value of default
     */
    auto result = pattern_->GetItemDisplayInfo(3);
    EXPECT_EQ(result.offsetY, 0.0f);
}

/**
 * @tc.name: StartSnapAnimation
 * @tc.desc: Test ArcListPattern StartSnapAnimation
 * @tc.type: FUNC
 */
HWTEST_F(ArcListPatternTestNg, StartSnapAnimation, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ListModelNG model = CreateList();
    CreateListItems(DEFAULT_ITEM_COUNT);
    CreateDone();
    pattern_->SetPredictSnapOffset(100.0);

    /**
     * @tc.steps: step2. Set the needed values
     */
    pattern_->startIndex_ = 0;
    pattern_->startMainPos_ = 20.0f;
    pattern_->currentDelta_ = 2.0f;
    pattern_->endMainPos_ = 15.0f;
    pattern_->contentMainSize_ = 8.0f;
    pattern_->contentEndOffset_ = 4.0f;
    pattern_->contentStartOffset_ = 2.0f;
    pattern_->isStackFromEnd_ = false;

    /**
     * @tc.steps: step3. Call the StartSnapAnimation
     * @tc.expected: The result return false
     */
    SnapAnimationOptions snapAnimationOptions;
    auto result = pattern_->StartSnapAnimation(snapAnimationOptions);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: GetScrollUpdateFriction
 * @tc.desc: Test ArcListPattern GetScrollUpdateFriction
 * @tc.type: FUNC
 */
HWTEST_F(ArcListPatternTestNg, GetScrollUpdateFriction, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ListModelNG model = CreateList();
    CreateListItems(DEFAULT_ITEM_COUNT);
    CreateDone();
    pattern_->SetPredictSnapOffset(100.0);

    /**
     * @tc.steps: step2. Set the contentMainSize_ to 7.2f
     */
    pattern_->contentMainSize_ = 7.2f;

    /**
     * @tc.steps: step3. Call the StartSnapAnimation
     * @tc.expected: The result return ARC_LIST_DRAG_OVER_RATES
     */
    auto result = pattern_->GetScrollUpdateFriction(-6.0f);
    EXPECT_EQ(result, ARC_LIST_DRAG_OVER_RATES);
}

/**
 * @tc.name: HandleScrollBarOutBoundary001
 * @tc.desc: Test ArcListPattern HandleScrollBarOutBoundary
 * @tc.type: FUNC
 */
HWTEST_F(ArcListPatternTestNg, HandleScrollBarOutBoundary001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ListModelNG model = CreateList();
    CreateListItems(DEFAULT_ITEM_COUNT);
    CreateDone();
    pattern_->SetPredictSnapOffset(100.0);

    /**
     * @tc.steps: step2. Set the IsOutOfBoundary function to return true
     * and set isScrollable_ to false
     */
    ListItemGroupLayoutInfo itemGroupInfo = { true, true };
    ListItemInfo info = { 2, 2.0f, 4.0f, true, false, 1.0f, 2.0f, itemGroupInfo };
    std::map<int32_t, ListItemInfo> itemPosition = { { 0, info } };
    pattern_->itemPosition_ = itemPosition;
    pattern_->scrollBar_ = AceType::MakeRefPtr<ScrollBar>(DisplayMode::AUTO);
    pattern_->startIndex_ = 0;
    pattern_->endIndex_ = 6;
    pattern_->startMainPos_ = 20.0f;
    pattern_->endMainPos_ = 30.0f;
    pattern_->contentMainSize_ = 8.0f;
    pattern_->contentEndOffset_ = 4.0f;
    pattern_->contentStartOffset_ = 2.0f;
    pattern_->isStackFromEnd_ = false;
    pattern_->isScrollable_ = false;
    pattern_->scrollBarOutBoundaryExtent_ = 2.0f;

    /**
     * @tc.steps: step3. Call the HandleScrollBarOutBoundary
     * @tc.expected: The scrollBarOutBoundaryExtent_ be 0
     */
    pattern_->HandleScrollBarOutBoundary();
    EXPECT_EQ(pattern_->scrollBarOutBoundaryExtent_, 0);
}

/**
 * @tc.name: HandleScrollBarOutBoundary002
 * @tc.desc: Test ArcListPattern HandleScrollBarOutBoundary
 * @tc.type: FUNC
 */
HWTEST_F(ArcListPatternTestNg, HandleScrollBarOutBoundary002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ListModelNG model = CreateList();
    CreateListItems(DEFAULT_ITEM_COUNT);
    CreateDone();
    pattern_->SetPredictSnapOffset(100.0);

    /**
     * @tc.steps: step2. Set the IsOutOfBoundary function to return true
     * and set isScrollable_ to true and it's the else if branch of the function that goes in
     */
    ListItemGroupLayoutInfo itemGroupInfo = { true, true };
    ListItemInfo info = { 2, 2.0f, 4.0f, true, false, 1.0f, 2.0f, itemGroupInfo };
    std::map<int32_t, ListItemInfo> itemPosition = { { 0, info } };
    pattern_->itemPosition_ = itemPosition;
    pattern_->scrollBar_ = AceType::MakeRefPtr<ScrollBar>(DisplayMode::AUTO);
    pattern_->startIndex_ = 2;
    pattern_->endIndex_ = 6;
    pattern_->maxListItemIndex_ = 6;
    pattern_->startMainPos_ = 20.0f;
    pattern_->endMainPos_ = 25.0f;
    pattern_->contentMainSize_ = 50.0f;
    pattern_->contentEndOffset_ = 4.0f;
    pattern_->contentStartOffset_ = 2.0f;
    pattern_->centerIndex_ = 0;
    pattern_->isStackFromEnd_ = false;
    pattern_->isScrollable_ = true;
    pattern_->scrollBarOutBoundaryExtent_ = 1.0f;

    /**
     * @tc.steps: step3. Call the HandleScrollBarOutBoundary
     * @tc.expected: The scrollBarOutBoundaryExtent_ be -1
     */
    pattern_->HandleScrollBarOutBoundary();
    EXPECT_EQ(pattern_->scrollBarOutBoundaryExtent_, -1);
}

/**
 * @tc.name: CreateAnalyzerOverlay
 * @tc.desc: Test ArcListPattern CreateAnalyzerOverlay
 * @tc.type: FUNC
 */
HWTEST_F(ArcListPatternTestNg, CreateAnalyzerOverlay, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ListModelNG model = CreateList();
    CalcDimension fadingEdgeLength = Dimension(32.0, DimensionUnit::VP);
    NG::ScrollableModelNG::SetFadingEdge(true, fadingEdgeLength);
    paintProperty_->UpdateDefaultFadingEdge(true);
    CreateListItems(DEFAULT_ITEM_COUNT);
    CreateDone();
    auto host = pattern_->GetHost();
    ASSERT_NE(host, nullptr);
    auto overlayNode = host->GetOverlayNode();
    EXPECT_NE(overlayNode, nullptr);
}

/**
 * @tc.name: GetDefaultScrollingConfig001
 * @tc.desc: Test ArcListPattern GetDefaultScrollingConfig when IsScrollAble returns false due to isScrollable_ is false
 * @tc.type: FUNC
 */
HWTEST_F(ArcListPatternTestNg, GetDefaultScrollingConfig001, TestSize.Level1)
{
    ListModelNG model = CreateList();
    CreateListItems(DEFAULT_ITEM_COUNT);
    CreateDone();

    pattern_->isScrollable_ = false;
    auto result = pattern_->GetDefaultScrollingConfig(SmartGestureDirection::FORWARD);
    EXPECT_FALSE(result.has_value());
}

/**
 * @tc.name: GetDefaultScrollingConfig002
 * @tc.desc: Test ArcListPattern GetDefaultScrollingConfig when direction is not FORWARD or BACKWARD
 * @tc.type: FUNC
 */
HWTEST_F(ArcListPatternTestNg, GetDefaultScrollingConfig002, TestSize.Level1)
{
    ListModelNG model = CreateList();
    CreateListItems(DEFAULT_ITEM_COUNT);
    CreateDone();

    pattern_->isScrollable_ = true;
    ListItemInfo info = { 0, 0.0f, 100.0f, false };
    pattern_->itemPosition_[0] = info;
    pattern_->maxListItemIndex_ = 5;

    auto result = pattern_->GetDefaultScrollingConfig(SmartGestureDirection::LEFT);
    EXPECT_FALSE(result.has_value());
}

/**
 * @tc.name: GetDefaultScrollingConfig003
 * @tc.desc: Test ArcListPattern GetDefaultScrollingConfig when itemPosition_ is empty
 * @tc.type: FUNC
 */
HWTEST_F(ArcListPatternTestNg, GetDefaultScrollingConfig003, TestSize.Level1)
{
    ListModelNG model = CreateList();
    CreateListItems(DEFAULT_ITEM_COUNT);
    CreateDone();

    pattern_->isScrollable_ = true;
    pattern_->itemPosition_.clear();
    pattern_->maxListItemIndex_ = 5;

    auto result = pattern_->GetDefaultScrollingConfig(SmartGestureDirection::FORWARD);
    EXPECT_FALSE(result.has_value());
}

/**
 * @tc.name: GetDefaultScrollingConfig004
 * @tc.desc: Test ArcListPattern GetDefaultScrollingConfig when maxListItemIndex_ is negative
 * @tc.type: FUNC
 */
HWTEST_F(ArcListPatternTestNg, GetDefaultScrollingConfig004, TestSize.Level1)
{
    ListModelNG model = CreateList();
    CreateListItems(DEFAULT_ITEM_COUNT);
    CreateDone();

    pattern_->isScrollable_ = true;
    ListItemInfo info = { 0, 0.0f, 100.0f, false };
    pattern_->itemPosition_[0] = info;
    pattern_->maxListItemIndex_ = -1;

    auto result = pattern_->GetDefaultScrollingConfig(SmartGestureDirection::FORWARD);
    EXPECT_FALSE(result.has_value());
}

/**
 * @tc.name: GetDefaultScrollingConfig005
 * @tc.desc: Test ArcListPattern GetDefaultScrollingConfig when GetMidIndex returns negative
 * @tc.type: FUNC
 */
HWTEST_F(ArcListPatternTestNg, GetDefaultScrollingConfig005, TestSize.Level1)
{
    ListModelNG model = CreateList();
    CreateListItems(DEFAULT_ITEM_COUNT);
    CreateDone();

    pattern_->isScrollable_ = true;
    pattern_->itemPosition_.clear();
    pattern_->maxListItemIndex_ = 5;
    pattern_->contentMainSize_ = 400.0f;
    pattern_->spaceWidth_ = 0.0f;

    auto host = pattern_->GetHost();
    if (host) {
        host->children_ = {};
    }

    auto result = pattern_->GetDefaultScrollingConfig(SmartGestureDirection::FORWARD);
    EXPECT_FALSE(result.has_value());
}

/**
 * @tc.name: GetDefaultScrollingConfig006
 * @tc.desc: Test ArcListPattern GetDefaultScrollingConfig when targetIndex equals midIndex (FORWARD at boundary)
 * @tc.type: FUNC
 */
HWTEST_F(ArcListPatternTestNg, GetDefaultScrollingConfig006, TestSize.Level1)
{
    ListModelNG model = CreateList();
    CreateListItems(DEFAULT_ITEM_COUNT);
    CreateDone();

    pattern_->isScrollable_ = true;
    pattern_->maxListItemIndex_ = 0;
    pattern_->contentMainSize_ = 400.0f;
    pattern_->spaceWidth_ = 0.0f;

    ListItemInfo info0 = { 0, 0.0f, 200.0f, false };
    pattern_->itemPosition_[0] = info0;

    pattern_->startIndex_ = 0;
    pattern_->endIndex_ = 0;
    pattern_->startMainPos_ = 0.0f;
    pattern_->endMainPos_ = 200.0f;
    pattern_->currentDelta_ = 0.0f;
    pattern_->contentStartOffset_ = 0.0f;
    pattern_->contentEndOffset_ = 0.0f;
    pattern_->isStackFromEnd_ = false;

    auto result = pattern_->GetDefaultScrollingConfig(SmartGestureDirection::FORWARD);
    EXPECT_FALSE(result.has_value());
}

/**
 * @tc.name: GetDefaultScrollingConfig007
 * @tc.desc: Test ArcListPattern GetDefaultScrollingConfig when targetIndex equals midIndex (BACKWARD at boundary)
 * @tc.type: FUNC
 */
HWTEST_F(ArcListPatternTestNg, GetDefaultScrollingConfig007, TestSize.Level1)
{
    ListModelNG model = CreateList();
    CreateListItems(DEFAULT_ITEM_COUNT);
    CreateDone();

    pattern_->isScrollable_ = true;
    pattern_->maxListItemIndex_ = 5;
    pattern_->contentMainSize_ = 400.0f;
    pattern_->spaceWidth_ = 0.0f;

    ListItemInfo info0 = { 0, 0.0f, 200.0f, false };
    pattern_->itemPosition_[0] = info0;

    pattern_->startIndex_ = 0;
    pattern_->endIndex_ = 3;
    pattern_->startMainPos_ = 0.0f;
    pattern_->endMainPos_ = 300.0f;
    pattern_->currentDelta_ = 0.0f;
    pattern_->contentStartOffset_ = 0.0f;
    pattern_->contentEndOffset_ = 0.0f;
    pattern_->isStackFromEnd_ = false;
    pattern_->itemStartIndex_ = 0;

    auto result = pattern_->GetDefaultScrollingConfig(SmartGestureDirection::BACKWARD);
    EXPECT_FALSE(result.has_value());
}

/**
 * @tc.name: GetDefaultScrollingConfig008
 * @tc.desc: Test ArcListPattern GetDefaultScrollingConfig when CalculateScrollingDistanceToIndex returns false
 * @tc.type: FUNC
 */
HWTEST_F(ArcListPatternTestNg, GetDefaultScrollingConfig008, TestSize.Level1)
{
    ListModelNG model = CreateList();
    CreateListItems(DEFAULT_ITEM_COUNT);
    CreateDone();

    pattern_->isScrollable_ = true;
    pattern_->maxListItemIndex_ = 10;
    pattern_->contentMainSize_ = 400.0f;
    pattern_->spaceWidth_ = 0.0f;

    ListItemInfo info0 = { 0, 0.0f, 100.0f, false };
    ListItemInfo info1 = { 1, 100.0f, 200.0f, false };
    pattern_->itemPosition_[0] = info0;
    pattern_->itemPosition_[1] = info1;

    pattern_->startIndex_ = 0;
    pattern_->endIndex_ = 1;
    pattern_->startMainPos_ = 0.0f;
    pattern_->endMainPos_ = 200.0f;
    pattern_->currentDelta_ = 0.0f;
    pattern_->contentStartOffset_ = 0.0f;
    pattern_->contentEndOffset_ = 0.0f;
    pattern_->isStackFromEnd_ = false;

    auto result = pattern_->GetDefaultScrollingConfig(SmartGestureDirection::FORWARD);
    EXPECT_FALSE(result.has_value());
}

/**
 * @tc.name: GetDefaultScrollingConfig009
 * @tc.desc: Test ArcListPattern GetDefaultScrollingConfig when targetPos is near zero
 * @tc.type: FUNC
 */
HWTEST_F(ArcListPatternTestNg, GetDefaultScrollingConfig009, TestSize.Level1)
{
    ListModelNG model = CreateList();
    CreateListItems(DEFAULT_ITEM_COUNT);
    CreateDone();

    pattern_->isScrollable_ = true;
    pattern_->maxListItemIndex_ = 10;
    pattern_->contentMainSize_ = 400.0f;
    pattern_->spaceWidth_ = 0.0f;

    ListItemInfo info0 = { 0, 0.0f, 100.0f, false };
    ListItemInfo info1 = { 1, 100.0f, 200.0f, false };
    ListItemInfo info2 = { 2, 150.0f, 250.0f, false };
    pattern_->itemPosition_[0] = info0;
    pattern_->itemPosition_[1] = info1;
    pattern_->itemPosition_[2] = info2;

    pattern_->startIndex_ = 0;
    pattern_->endIndex_ = 2;
    pattern_->startMainPos_ = 0.0f;
    pattern_->endMainPos_ = 250.0f;
    pattern_->currentDelta_ = 0.0f;
    pattern_->contentStartOffset_ = 0.0f;
    pattern_->contentEndOffset_ = 0.0f;
    pattern_->isStackFromEnd_ = false;

    auto result = pattern_->GetDefaultScrollingConfig(SmartGestureDirection::FORWARD);
    EXPECT_FALSE(result.has_value());
}

/**
 * @tc.name: GetDefaultScrollingConfig010
 * @tc.desc: Test ArcListPattern GetDefaultScrollingConfig with FORWARD direction returns valid config
 * @tc.type: FUNC
 */
HWTEST_F(ArcListPatternTestNg, GetDefaultScrollingConfig010, TestSize.Level1)
{
    ListModelNG model = CreateList();
    CreateListItems(DEFAULT_ITEM_COUNT);
    CreateDone();

    pattern_->isScrollable_ = true;
    pattern_->maxListItemIndex_ = 10;
    pattern_->contentMainSize_ = 400.0f;
    pattern_->spaceWidth_ = 0.0f;

    ListItemInfo info0 = { 0, 0.0f, 100.0f, false };
    ListItemInfo info1 = { 1, 100.0f, 200.0f, false };
    ListItemInfo info2 = { 2, 200.0f, 300.0f, false };
    ListItemInfo info3 = { 3, 300.0f, 400.0f, false };
    ListItemInfo info4 = { 4, 400.0f, 500.0f, false };
    pattern_->itemPosition_[0] = info0;
    pattern_->itemPosition_[1] = info1;
    pattern_->itemPosition_[2] = info2;
    pattern_->itemPosition_[3] = info3;
    pattern_->itemPosition_[4] = info4;

    pattern_->startIndex_ = 0;
    pattern_->endIndex_ = 4;
    pattern_->startMainPos_ = 0.0f;
    pattern_->endMainPos_ = 500.0f;
    pattern_->currentDelta_ = 0.0f;
    pattern_->contentStartOffset_ = 0.0f;
    pattern_->contentEndOffset_ = 0.0f;
    pattern_->isStackFromEnd_ = false;

    auto result = pattern_->GetDefaultScrollingConfig(SmartGestureDirection::FORWARD);
    EXPECT_TRUE(result.has_value());
    EXPECT_EQ(result->direction, SmartGestureDirection::FORWARD);
    EXPECT_TRUE(result->distance.has_value());
}

/**
 * @tc.name: GetDefaultScrollingConfig011
 * @tc.desc: Test ArcListPattern GetDefaultScrollingConfig with BACKWARD direction returns valid config
 * @tc.type: FUNC
 */
HWTEST_F(ArcListPatternTestNg, GetDefaultScrollingConfig011, TestSize.Level1)
{
    ListModelNG model = CreateList();
    CreateListItems(DEFAULT_ITEM_COUNT);
    CreateDone();

    pattern_->isScrollable_ = true;
    pattern_->maxListItemIndex_ = 10;
    pattern_->contentMainSize_ = 400.0f;
    pattern_->spaceWidth_ = 0.0f;

    ListItemInfo info0 = { 0, 0.0f, 100.0f, false };
    ListItemInfo info1 = { 1, 100.0f, 200.0f, false };
    ListItemInfo info2 = { 2, 200.0f, 300.0f, false };
    ListItemInfo info3 = { 3, 300.0f, 400.0f, false };
    ListItemInfo info4 = { 4, 400.0f, 500.0f, false };
    pattern_->itemPosition_[0] = info0;
    pattern_->itemPosition_[1] = info1;
    pattern_->itemPosition_[2] = info2;
    pattern_->itemPosition_[3] = info3;
    pattern_->itemPosition_[4] = info4;

    pattern_->startIndex_ = 1;
    pattern_->endIndex_ = 4;
    pattern_->startMainPos_ = 100.0f;
    pattern_->endMainPos_ = 500.0f;
    pattern_->currentDelta_ = 0.0f;
    pattern_->contentStartOffset_ = 0.0f;
    pattern_->contentEndOffset_ = 0.0f;
    pattern_->isStackFromEnd_ = false;

    auto result = pattern_->GetDefaultScrollingConfig(SmartGestureDirection::BACKWARD);
    EXPECT_TRUE(result.has_value());
    EXPECT_EQ(result->direction, SmartGestureDirection::BACKWARD);
    EXPECT_TRUE(result->distance.has_value());
}
} // namespace OHOS::Ace::NG
