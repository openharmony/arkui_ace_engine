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

#include "arc_list_test_ng.h"

namespace OHOS::Ace::NG {

namespace {
const InspectorFilter filter;
} // namespace

class ArcListAttrTestNg : public ArcListTestNg {
public:
};

/**
 * @tc.name: ArcListLayoutProperty001
 * @tc.desc: Test Arc_list layout properties.
 * @tc.type: FUNC
 */
HWTEST_F(ArcListAttrTestNg, ArcListLayoutProperty001, TestSize.Level1)
{
    ListModelNG model = CreateList();
    model.SetSpace(Dimension(10));
    model.SetInitialIndex(1);
    model.SetScrollBar(DisplayMode::ON);
    model.SetChainAnimation(true);
    model.SetCachedCount(10);
    CreateDone();

    /**
     * @tc.steps: step1. Call ToJsonValue()
     * @tc.expected: The json value is correct
     */
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    EXPECT_EQ(Dimension::FromString(json->GetString("space")), Dimension(10));
    EXPECT_EQ(json->GetString("initialIndex"), "1");
    EXPECT_TRUE(json->GetBool("chainAnimation"));
    EXPECT_EQ(json->GetString("cachedCount"), "10");
}

/**
 * @tc.name: ArcListLayoutProperty002
 * @tc.desc: Test Arc_list layout properties.
 * @tc.type: FUNC
 */
HWTEST_F(ArcListAttrTestNg, ArcListLayoutProperty002, TestSize.Level1)
{
    ListModelNG model = CreateList();
    CreateDone();

    model.SetListFriction(AceType::RawPtr(frameNode_), BAR_FRICTION);
    // Set valid value.
    model.SetListScrollBar(AceType::RawPtr(frameNode_), 2);
    EXPECT_EQ(pattern_->friction_, BAR_FRICTION);
    EXPECT_EQ(paintProperty_->GetScrollBarModeValue(DisplayMode::OFF), DisplayMode::ON);

    // Set invalid value.
    model.SetListScrollBar(AceType::RawPtr(frameNode_), -1);
    EXPECT_EQ(paintProperty_->GetScrollBarModeValue(DisplayMode::OFF), DisplayMode::AUTO);
}

/**
 * @tc.name: ArcListLayoutProperty003
 * @tc.desc: Test Arc_list layout property function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcListAttrTestNg, ArcListLayoutProperty003, TestSize.Level1)
{
    ListModelNG model = CreateList();
    model.SetSpace(Dimension(10));
    model.SetInitialIndex(1);
    model.SetScrollBar(DisplayMode::ON);
    model.SetCachedCount(10);
    CreateDone();

    // Test ArcListLayoutProperty Clone interface.
    auto json = JsonUtil::Create(true);
    RefPtr<LayoutProperty> layoutProp = layoutProperty_->Clone();
    layoutProp->ToJsonValue(json, filter);
    EXPECT_EQ(Dimension::FromString(json->GetString("space")), Dimension(10));
    EXPECT_EQ(json->GetString("initialIndex"), "1");
    EXPECT_EQ(json->GetString("cachedCount"), "10");
}

/**
 * @tc.name: ArcListLayoutProperty004
 * @tc.desc: Test Arc_list layout property function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcListAttrTestNg, ArcListLayoutProperty004, TestSize.Level1)
{
    ListModelNG model = CreateList();
    model.SetSpace(Dimension(10));
    model.SetInitialIndex(1);
    model.SetScrollBar(DisplayMode::ON);
    model.SetChainAnimation(true);
    model.SetCachedCount(10);
    CreateDone();

    // Test ArcListLayoutProperty Reset interface.
    auto json = JsonUtil::Create(true);
    layoutProperty_->Reset();
    layoutProperty_->ToJsonValue(json, filter);
    EXPECT_EQ(Dimension::FromString(json->GetString("space")), Dimension(0.0, DimensionUnit::VP));
    EXPECT_EQ(json->GetString("initialIndex"), "0");
    EXPECT_TRUE(json->GetBool("chainAnimation"));
    EXPECT_EQ(json->GetString("cachedCount"), "0");
}

/**
 * @tc.name: ArcListLayoutProperty005
 * @tc.desc: Test Arc_list layout property function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcListAttrTestNg, ArcListLayoutProperty005, TestSize.Level1)
{
    ListModelNG model = CreateList();
    model.SetSpace(Dimension(10));
    model.SetInitialIndex(1);
    model.SetScrollBar(DisplayMode::ON);
    model.SetChainAnimation(true);
    model.SetCachedCount(10);
    CreateDone();

    /**
     * @tc.steps: step1. Call ToJsonValue()
     */
    auto json1 = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json1, filter);

    /**
     * @tc.steps: step2. Call FromJson()
     */
    layoutProperty_->Reset();
    layoutProperty_->FromJson(json1);

    /**
     * @tc.steps: step1. Call ToJsonValue()
     * @tc.expected: The json value is correct
     */
    auto json2 = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json2, filter);
    EXPECT_EQ(Dimension::FromString(json2->GetString("space")), Dimension(10));
    EXPECT_EQ(json2->GetString("initialIndex"), "1");
    EXPECT_TRUE(json2->GetBool("chainAnimation"));
}

/**
 * @tc.name: ArcListLayoutProperty006
 * @tc.desc: Test Arc_list layout property function.
 * @tc.type: FUNC
 */
HWTEST_F(ArcListAttrTestNg, ArcListLayoutProperty006, TestSize.Level1)
{
    ListModelNG model = CreateList();
    model.SetSpace(Dimension(10));
    model.SetInitialIndex(1);
    model.SetScrollBar(DisplayMode::ON);
    model.SetChainAnimation(true);
    model.SetCachedCount(10);
    CreateDone();

    // Test ArcListLayoutProperty ToJsonValue interface, expect to cover all branches.
    InspectorFilter filter2;
    filter2.AddFilterAttr("id");
    filter2.AddFilterAttr("content");

    auto json1 = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json1, filter2);

    layoutProperty_->Reset();
    layoutProperty_->FromJson(json1);

    auto json2 = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json2, filter2);
    EXPECT_EQ(Dimension::FromString(json2->GetString("space")), Dimension(0.0, DimensionUnit::FP));
    EXPECT_EQ(json2->GetString("initialIndex"), "");
    EXPECT_FALSE(json2->GetBool("chainAnimation"));
}

/**
 * @tc.name: ArcListItemLayoutProperty001
 * @tc.desc: Test ArcListItem layout properties.
 * @tc.type: FUNC
 */
HWTEST_F(ArcListAttrTestNg, ArcListItemLayoutProperty001, TestSize.Level1)
{
    CreateList();
    ListItemModelNG itemModel = CreateListItem();
    CreateDone();
    auto layoutProperty = GetChildLayoutProperty<ArcListItemLayoutProperty>(frameNode_, 0);

    /**
     * @tc.steps: step1. Call ToJsonValue()
     * @tc.expected: The json value is correct
     */
    auto json = JsonUtil::Create(true);
    layoutProperty->ToJsonValue(json, filter);
    EXPECT_EQ(Dimension::FromString(json->GetString("startDeleteAreaDistance")), Dimension(0, DimensionUnit::VP));
    EXPECT_EQ(Dimension::FromString(json->GetString("endDeleteAreaDistance")), Dimension(0, DimensionUnit::VP));

    /**
     * @tc.steps: step2. Change some property, Call ToJsonValue()
     * @tc.expected: The json value is correct
     */
    CreateList();
    itemModel = CreateListItem();
    itemModel.SetSwiperAction(nullptr, nullptr, nullptr, V2::SwipeEdgeEffect::Spring);
    CreateDone();
    json = JsonUtil::Create(true);
    layoutProperty->ToJsonValue(json, filter);
    auto swipeAction = json->GetObject("swipeAction");
    EXPECT_EQ(static_cast<V2::SwipeEdgeEffect>(swipeAction->GetInt("edgeEffect")), V2::SwipeEdgeEffect::Spring);

    /**
     * @tc.steps: step3. Change some property, Call ToJsonValue()
     * @tc.expected: The json value is correct
     */
    CreateList();
    itemModel = CreateListItem();
    itemModel.SetSwiperAction(nullptr, nullptr, nullptr, V2::SwipeEdgeEffect::None);
    CreateDone();
    json = JsonUtil::Create(true);
    layoutProperty->ToJsonValue(json, filter);
    swipeAction = json->GetObject("swipeAction");
    EXPECT_EQ(swipeAction->GetString("edgeEffect"), "SwipeEdgeEffect.Node");
}

/**
 * @tc.name: ArcListItemLayoutProperty002
 * @tc.desc: Test ArcListItem layout properties.
 * @tc.type: FUNC
 */
HWTEST_F(ArcListAttrTestNg, ArcListItemLayoutProperty002, TestSize.Level1)
{
    CreateList();
    ListItemModelNG itemModel = CreateListItem();
    CreateDone();

    // Test ArcListItemLayoutProperty Clone interface.
    auto json = JsonUtil::Create(true);
    auto layoutProperty = GetChildLayoutProperty<ArcListItemLayoutProperty>(frameNode_, 0);
    RefPtr<LayoutProperty> layoutProp = layoutProperty->Clone();
    layoutProp->ToJsonValue(json, filter);
    EXPECT_EQ(Dimension::FromString(json->GetString("startDeleteAreaDistance")), Dimension(0, DimensionUnit::VP));
    EXPECT_EQ(Dimension::FromString(json->GetString("endDeleteAreaDistance")), Dimension(0, DimensionUnit::VP));

    CreateList();
    itemModel = CreateListItem();
    itemModel.SetSwiperAction(nullptr, nullptr, nullptr, V2::SwipeEdgeEffect::Spring);
    CreateDone();
    json = JsonUtil::Create(true);
    layoutProperty = GetChildLayoutProperty<ArcListItemLayoutProperty>(frameNode_, 0);
    layoutProp = layoutProperty->Clone();
    layoutProp->ToJsonValue(json, filter);
    auto swipeAction = json->GetObject("swipeAction");
    EXPECT_EQ(static_cast<V2::SwipeEdgeEffect>(swipeAction->GetInt("edgeEffect")), V2::SwipeEdgeEffect::Spring);
}

/**
 * @tc.name: ArcListItemLayoutProperty003
 * @tc.desc: Test ArcListItem layout properties.
 * @tc.type: FUNC
 */
HWTEST_F(ArcListAttrTestNg, ArcListItemLayoutProperty003, TestSize.Level1)
{
    CreateList();
    ListItemModelNG itemModel = CreateListItem();
    CreateDone();

    // Test ArcListItemLayoutProperty Reset interface.
    auto json = JsonUtil::Create(true);
    auto layoutProperty = GetChildLayoutProperty<ArcListItemLayoutProperty>(frameNode_, 0);
    layoutProperty->Reset();
    layoutProperty->ToJsonValue(json, filter);
    EXPECT_EQ(Dimension::FromString(json->GetString("startDeleteAreaDistance")), Dimension(0, DimensionUnit::VP));
    EXPECT_EQ(Dimension::FromString(json->GetString("endDeleteAreaDistance")), Dimension(0, DimensionUnit::VP));

    CreateList();
    itemModel = CreateListItem();
    itemModel.SetSwiperAction(nullptr, nullptr, nullptr, V2::SwipeEdgeEffect::Spring);
    CreateDone();
    json = JsonUtil::Create(true);
    layoutProperty = GetChildLayoutProperty<ArcListItemLayoutProperty>(frameNode_, 0);
    layoutProperty->Reset();
    layoutProperty->ToJsonValue(json, filter);
    auto swipeAction = json->GetObject("swipeAction");
    EXPECT_EQ(static_cast<V2::SwipeEdgeEffect>(swipeAction->GetInt("edgeEffect")), V2::SwipeEdgeEffect::Spring);

    CreateList();
    itemModel = CreateListItem();
    itemModel.SetSwiperAction(nullptr, nullptr, nullptr, V2::SwipeEdgeEffect::None);
    CreateDone();
    json = JsonUtil::Create(true);
    layoutProperty = GetChildLayoutProperty<ArcListItemLayoutProperty>(frameNode_, 0);
    layoutProperty->Reset();
    layoutProperty->ToJsonValue(json, filter);
    swipeAction = json->GetObject("swipeAction");
    EXPECT_EQ(swipeAction->GetString("edgeEffect"), "SwipeEdgeEffect.Node");
}

/**
 * @tc.name: AttrSpace001
 * @tc.desc: Test property about space
 * @tc.type: FUNC
 */
HWTEST_F(ArcListAttrTestNg, AttrSpace001, TestSize.Level1)
{
    /**
     * @tc.cases: Set space
     * @tc.expected: Has space
     */
    ListModelNG model = CreateList();
    model.SetSpace(Dimension(SPACE));
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    EXPECT_EQ(GetChildY(frameNode_, 1), 0);
}

/**
 * @tc.name: AttrSpace002
 * @tc.desc: Test property about space
 * @tc.type: FUNC
 */
HWTEST_F(ArcListAttrTestNg, AttrSpace002, TestSize.Level1)
{
    // Create list with header.
    ListModelNG model = CreateListWithHeader();
    AddHeader(&model);
    model.SetSpace(Dimension(SPACE));
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    // Now node 0 is header, there is no space between node 0 and node 1.
    EXPECT_EQ(GetChildY(frameNode_, 1), 0);
}

/**
 * @tc.name: AttrSpace003
 * @tc.desc: Test property about space with invalid value
 * @tc.type: FUNC
 */
HWTEST_F(ArcListAttrTestNg, AttrSpace003, TestSize.Level1)
{
    /**
     * @tc.cases: Set invalid space:LIST_HEIGHT
     * @tc.expected: Space was going to be zero
     */
    ListModelNG model = CreateList();
    model.SetSpace(Dimension(LIST_HEIGHT));
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    EXPECT_EQ(GetChildY(frameNode_, 1), 0);

    /**
     * @tc.cases: Set invalid space: -1
     * @tc.expected: Space was going to be zero
     */
    model = CreateList();
    model.SetSpace(Dimension(-1));
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    EXPECT_EQ(GetChildY(frameNode_, 1), 0);
}

/**
 * @tc.name: AttrInitIndex001
 * @tc.desc: Test property about initialIndex
 * @tc.type: FUNC
 */
HWTEST_F(ArcListAttrTestNg, AttrInitIndex001, TestSize.Level1)
{
    /**
     * @tc.cases: Not set initialIndex
     * @tc.expected: Arc_list default at top
     */
    CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    EXPECT_FALSE(pattern_->IsAtTop());
    EXPECT_EQ(pattern_->GetTotalOffset(), GetChildHeight(frameNode_, 0));
}

/**
 * @tc.name: AttrInitIndex002
 * @tc.desc: Test property about initialIndex
 * @tc.type: FUNC
 */
HWTEST_F(ArcListAttrTestNg, AttrInitIndex002, TestSize.Level1)
{
    /**
     * @tc.cases: Set initialIndex:1
     * @tc.expected: The item(index:1) is at top
     */
    ListModelNG model = CreateList();
    model.SetInitialIndex(1);
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    EXPECT_FALSE(pattern_->IsAtTop());
    EXPECT_EQ(GetChildY(frameNode_, 1), 0);
    EXPECT_EQ(pattern_->GetTotalOffset() + MID_OFFSET, GetChildHeight(frameNode_, 0) + MID_OFFSET);
}

/**
 * @tc.name: AttrInitIndex003
 * @tc.desc: Test property about initialIndex
 * @tc.type: FUNC
 */
HWTEST_F(ArcListAttrTestNg, AttrInitIndex003, TestSize.Level1)
{
    ListModelNG model = CreateList();
    model.SetInitialIndex(1);
    CreateListItems(VIEW_ITEM_NUMBER);
    CreateDone();
    EXPECT_TRUE(pattern_->IsScrollable());
    EXPECT_FALSE(pattern_->IsAtTop());
}

/**
 * @tc.name: AttrInitIndex004
 * @tc.desc: Test property about initialIndex
 * @tc.type: FUNC
 */
HWTEST_F(ArcListAttrTestNg, AttrInitIndex004, TestSize.Level1)
{
    ListModelNG model = CreateList();
    model.SetInitialIndex(5);
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    EXPECT_FALSE(pattern_->IsAtBottom());
    EXPECT_FALSE(NearEqual(GetChildX(frameNode_, 2), LIST_WIDTH * (1 - ARC_LIST_ITER_SCALE) / 2.0));
    EXPECT_EQ(pattern_->GetTotalOffset() + MID_OFFSET, ITEM_HEIGHT * 1.5);
}

/**
 * @tc.name: AttrInitIndex005
 * @tc.desc: Test property about initialIndex
 * @tc.type: FUNC
 */
HWTEST_F(ArcListAttrTestNg, AttrInitIndex005, TestSize.Level1)
{
    /**
     * @tc.cases: Set initialIndex:100, the initialIndex greater than max Index(itemSize-1)
     * @tc.expected: Arc_list is at top, ignore initialIndex
     */
    ListModelNG model = CreateList();
    model.SetInitialIndex(100);
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    EXPECT_FALSE(pattern_->IsAtTop());
}

/**
 * @tc.name: AttrInitIndex006
 * @tc.desc: Test property about initialIndex
 * @tc.type: FUNC
 */
HWTEST_F(ArcListAttrTestNg, AttrInitIndex006, TestSize.Level1)
{
    /**
     * @tc.cases: Set initialIndex:3, the initialIndex is snap to center
     */
    ListModelNG model = CreateList();
    model.SetInitialIndex(3);
    CreateListItems(TOTAL_ITEM_NUMBER * 2);
    CreateDone();
    EXPECT_EQ(GetChildY(frameNode_, 2), 0);
    EXPECT_EQ(GetChildY(frameNode_, 3), 0);
}

/**
 * @tc.name: AttrScrollBar001
 * @tc.desc: Test property about scrollBar
 * @tc.type: FUNC
 */
HWTEST_F(ArcListAttrTestNg, AttrScrollBar001, TestSize.Level1)
{
    ListModelNG model = CreateList();
    model.SetScrollBar(DisplayMode::ON);
    CreateListItems(1);
    CreateDone();
    EXPECT_EQ(pattern_->GetScrollBar()->GetDisplayMode(), DisplayMode::ON);
}

/**
 * @tc.name: AttrScrollBar002
 * @tc.desc: Test property about scrollBar
 * @tc.type: FUNC
 */
HWTEST_F(ArcListAttrTestNg, AttrScrollBar002, TestSize.Level1)
{
    /**
     * @tc.cases: Set scrollBar, set api version >= 10
     * @tc.expected: the default value is auto
     */
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TEN));
    ListModelNG model = CreateList();
    CreateListItems(1);
    CreateDone();
    EXPECT_EQ(pattern_->GetScrollBar()->GetDisplayMode(), DisplayMode::AUTO);
}

/**
 * @tc.name: AttrScrollSnapAlign001
 * @tc.desc: Test LayoutProperty about ScrollSnapAlign
 * @tc.type: FUNC
 */
HWTEST_F(ArcListAttrTestNg, AttrScrollSnapAlign001, TestSize.Level1)
{
    ListModelNG model = CreateList();
    ViewAbstract::SetHeight(CalcLength(LIST_HEIGHT));
    CreateListItems(2);
    CreateDone();
    float scrollableDistance = pattern_->GetScrollableDistance();
    EXPECT_EQ(scrollableDistance, 0);

    float offset = -10.f;
    ScrollSnapForEqualHeightItem(offset, -1000.f);

    // To take into account the item scaling of the arc list, adjust the value according to the scaling.
    ArcListLayoutAlgorithm algorithm(200, 100);
    float dis1 = 0.f;
    float dis2 = ITEM_HEIGHT;
    float scale = (2.0 / (algorithm.GetNearScale(dis1) +
        algorithm.GetNearScale(dis2)) - 1) * DRAG_FIX_OFFSET_RATIO + 1;
    float off = offset * scale;

    EXPECT_EQ(pattern_->GetTotalOffset(), static_cast<int>(trunc(-MID_OFFSET - off)));
}

/**
 * @tc.name: AttrScrollSnapAlign002
 * @tc.desc: Test LayoutProperty about ScrollSnapAlign
 * @tc.type: FUNC
 */
HWTEST_F(ArcListAttrTestNg, AttrScrollSnapAlign002, TestSize.Level1)
{
    ListModelNG model = CreateList();
    ViewAbstract::SetHeight(CalcLength(LIST_HEIGHT));
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    EXPECT_EQ(pattern_->GetTotalOffset(), 0);

    /**
     * @tc.steps: stpe2. Scroll delta less than half of ITEM_HEIGHT
     * @tc.expected: Meet the expectation of the limit algorithm
     */
    float endPos = ITEM_HEIGHT + ARC_LIST_ITEM_SNAP_SIZE / 2.0;
    ScrollSnap(-49.f, 1200.f);
    EXPECT_EQ(pattern_->GetTotalOffset(), -ITEM_HEIGHT - 1);

    /**
     * @tc.steps: stpe3. Scroll delta greater than half of ITEM_HEIGHT
     * @tc.expected: Meet the expectation of the limit algorithm
     */
    endPos -= ARC_LIST_ITEM_SNAP_SIZE;
    ScrollSnap(-51.f, 1200.f);
    EXPECT_EQ(pattern_->GetTotalOffset(), -ITEM_HEIGHT / 2);
}

/**
 * @tc.name: AttrScrollSnapAlign003
 * @tc.desc: Test LayoutProperty about ScrollSnapAlign
 * @tc.type: FUNC
 */
HWTEST_F(ArcListAttrTestNg, AttrScrollSnapAlign003, TestSize.Level1)
{
    ListModelNG model = CreateList();
    CreateListItems(2);
    CreateDone();
    EXPECT_EQ(pattern_->GetTotalOffset(), 0);
    float scrollableDistance = pattern_->GetScrollableDistance();
    EXPECT_EQ(scrollableDistance, 0);

    /**
     * @tc.steps: stpe2. Scroll delta less than half of ITEM_HEIGHT
     * @tc.expected: Meet the expectation of the limit algorithm
     */
    float endPos = ITEM_HEIGHT + ARC_LIST_ITEM_SNAP_SIZE / 2.0;
    ScrollSnap(-49.f, 1200.f);
    EXPECT_EQ(pattern_->GetTotalOffset(), -ITEM_HEIGHT - 1);

    /**
     * @tc.steps: stpe3. Scroll delta greater than half of ITEM_HEIGHT
     * @tc.expected: Meet the expectation of the limit algorithm
     */
    endPos -= ARC_LIST_ITEM_SNAP_SIZE;
    ScrollSnap(-51.f, 1200.f);
    EXPECT_EQ(pattern_->GetTotalOffset(), -ITEM_HEIGHT / 2);

    /**
     * @tc.steps: stpe4. Scroll to over bottom
     * @tc.expected: Meet the expectation of the limit algorithm
     */
    ScrollSnapForEqualHeightItem(-1000.f, -1200.f);
    EXPECT_EQ(pattern_->GetTotalOffset(), -ITEM_HEIGHT / 2);
}

/**
 * @tc.name: AttrScrollSnapAlign004
 * @tc.desc: Test LayoutProperty about ScrollSnapAlign different itemHeight
 * @tc.type: FUNC
 */
HWTEST_F(ArcListAttrTestNg, AttrScrollSnapAlign004, TestSize.Level1)
{
    /**
     * @tc.steps: stpe1. set item(index:1) height:150.f
     */
    ListModelNG model = CreateList();
    CreateListItems(2);
    CreateDone();
    GetChildLayoutProperty<ArcListItemLayoutProperty>(frameNode_, 1)
        ->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(ITEM_HEIGHT * 1.5)));

    /**
     * @tc.steps: stpe3. Scroll delta greater than half of ITEM_HEIGHT
     * @tc.expected: Meet the expectation of the limit algorithm
     */
    float endPos = ITEM_HEIGHT + ARC_LIST_ITEM_SNAP_SIZE / 2.0;
    endPos -= ARC_LIST_ITEM_SNAP_SIZE;
    ScrollSnap(-51.f, 1200.f);
    EXPECT_EQ(pattern_->GetTotalOffset(), -ITEM_HEIGHT + 1); // 100.f
}

/**
 * @tc.name: AttrScrollSnapAlign005
 * @tc.desc: Test LayoutProperty about ScrollSnapAlign different itemHeight
 * @tc.type: FUNC
 */
HWTEST_F(ArcListAttrTestNg, AttrScrollSnapAlign005, TestSize.Level1)
{
    /**
     * @tc.steps: stpe1. set item(index:5) height:150.f
     */
    ListModelNG model = CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    GetChildLayoutProperty<ArcListItemLayoutProperty>(frameNode_, TOTAL_ITEM_NUMBER - 1)
        ->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(ITEM_HEIGHT * 1.5)));

    /**
     * @tc.steps: stpe3. Scroll delta greater than half of ITEM_HEIGHT
     * @tc.expected: Meet the expectation of the limit algorithm
     */
    float endPos = ITEM_HEIGHT + ARC_LIST_ITEM_SNAP_SIZE / 2.0;
    endPos -= ARC_LIST_ITEM_SNAP_SIZE;
    ScrollSnap(-51.f, 1200.f);
    EXPECT_EQ(pattern_->GetTotalOffset(), -ITEM_HEIGHT + 1); // 100.f
}

/**
 * @tc.name: AttrSLECM001
 * @tc.desc: Test property about edgeEffect/chainAnimation
 * @tc.type: FUNC
 */
HWTEST_F(ArcListAttrTestNg, AttrSLECM001, TestSize.Level1)
{
    ListModelNG model = CreateList();
    model.SetChainAnimation(true);
    CreateListItems(1);
    CreateDone();
    EXPECT_NE(pattern_->GetScrollEdgeEffect(), nullptr);
    EXPECT_NE(pattern_->chainAnimation_, nullptr);
}

/**
 * @tc.name: AttrEnableScrollInteraction001
 * @tc.desc: Test property about enableScrollInteraction.
 * @tc.type: FUNC
 */
HWTEST_F(ArcListAttrTestNg, AttrEnableScrollInteraction001, TestSize.Level1)
{
    /**
     * @tc.cases: Scrollable list, Not set ScrollEnabled
     * @tc.expected: Default by arc_list isScrollable_
     */
    ListModelNG model = CreateList();
    model.SetScrollEnabled(true);
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    EXPECT_TRUE(pattern_->scrollableEvent_->GetEnabled());
}

/**
 * @tc.name: AttrEnableScrollInteraction002
 * @tc.desc: Test property about enableScrollInteraction.
 * @tc.type: FUNC
 */
HWTEST_F(ArcListAttrTestNg, AttrEnableScrollInteraction002, TestSize.Level1)
{
    /**
     * @tc.cases: UnScrollable list, Not set ScrollEnabled, the items is empty
     */
    ListModelNG model = CreateList();
    model.SetScrollEnabled(true);
    CreateDone();
    EXPECT_TRUE(pattern_->scrollableEvent_->GetEnabled());
    EXPECT_FALSE(pattern_->IsAtTop());
    EXPECT_FALSE(pattern_->IsAtBottom());
}

/**
 * @tc.name: AttrEnableScrollInteraction003
 * @tc.desc: Test property about enableScrollInteraction.
 * @tc.type: FUNC
 */
HWTEST_F(ArcListAttrTestNg, AttrEnableScrollInteraction003, TestSize.Level1)
{
    /**
     * @tc.cases: Scrollable list, set ScrollEnabled:false
     * @tc.expected: Decided by arc_list isScrollable_
     */
    ListModelNG model = CreateList();
    model.SetScrollEnabled(false);
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    EXPECT_TRUE(pattern_->scrollableEvent_->GetEnabled());
}

/**
 * @tc.name: AttrEnableScrollInteraction004
 * @tc.desc: Test property about enableScrollInteraction.
 * @tc.type: FUNC
 */
HWTEST_F(ArcListAttrTestNg, AttrEnableScrollInteraction004, TestSize.Level1)
{
    /**
     * @tc.cases: UnScrollable list, Set ScrollEnabled:true
     * @tc.expected: Decided by arc_list isScrollable_
     */
    ListModelNG model = CreateList();
    model.SetScrollEnabled(true);
    CreateListItems(1);
    CreateDone();
    EXPECT_TRUE(pattern_->scrollableEvent_->GetEnabled());
}

/**
 * @tc.name: AttrFriction001
 * @tc.desc: Test SetFriction:friction shouled be more than 0.0,if out of range,should be default value.
 * @tc.type: FUNC
 */
HWTEST_F(ArcListAttrTestNg, AttrFriction001, TestSize.Level1)
{
    /**
     * @tc.cases: Set invalid friction:0
     * @tc.expected: Friction is default
     */
    ListModelNG model = CreateList();
    model.SetFriction(0.0);
    CreateListItems(1);
    CreateDone();
    EXPECT_DOUBLE_EQ(pattern_->GetFriction(), ARC_LIST_FRICTION);
}

/**
 * @tc.name: AttrFriction002
 * @tc.desc: Test SetFriction:friction shouled be more than 0.0,if out of range,should be default value.
 * @tc.type: FUNC
 */
HWTEST_F(ArcListAttrTestNg, AttrFriction002, TestSize.Level1)
{
    /**
     * @tc.cases: Set invalid friction:-1
     * @tc.expected: Friction is default
     */
    ListModelNG model = CreateList();
    model.SetFriction(-1);
    CreateListItems(1);
    CreateDone();
    EXPECT_DOUBLE_EQ(pattern_->GetFriction(), ARC_LIST_FRICTION);
}

/**
 * @tc.name: AttrFriction003
 * @tc.desc: Test SetFriction:friction shouled be more than 0.0,if out of range,should be default value.
 * @tc.type: FUNC
 */
HWTEST_F(ArcListAttrTestNg, AttrFriction003, TestSize.Level1)
{
    /**
     * @tc.cases: Set friction:1
     * @tc.expected: Friction is 1
     */
    ListModelNG model = CreateList();
    model.SetFriction(1);
    CreateListItems(1);
    CreateDone();
    EXPECT_DOUBLE_EQ(pattern_->GetFriction(), 1);
}

/**
 * @tc.name: ResetChildrenSize001
 * @tc.desc: Test ArcListPattern::ResetChildrenSize
 * @tc.type: FUNC
 */
HWTEST_F(ArcListAttrTestNg, ResetChildrenSize001, TestSize.Level1)
{
    int32_t count = 3;

    ListModelNG model = CreateList();
    CreateListItems(count);
    CreateDone();

    pattern_->ResetChildrenSize();
    RefPtr<ListChildrenMainSize> childrenSize = pattern_->GetOrCreateListChildrenMainSize();
    // After reset, the size of children are 0.f.
    for (int i = 0; i < count; ++i) {
        EXPECT_EQ(childrenSize->GetChildSize(i), 0.f);
    }
}

/**
 * @tc.name: GetMidIndex001
 * @tc.desc: Test ArcListPattern::GetMidIndex
 * @tc.type: FUNC
 */
HWTEST_F(ArcListAttrTestNg, GetMidIndex001, TestSize.Level1)
{
    ListModelNG model = CreateList();
    CreateDone();

    /**
     * @tc.cases: The List is empty
     * @tc.expected: mid index is -1
     */
    EXPECT_EQ(pattern_->GetMidIndex(), -1);
}

/**
 * @tc.name: GetMidIndex002
 * @tc.desc: Test ArcListPattern::GetMidIndex
 * @tc.type: FUNC
 */
HWTEST_F(ArcListAttrTestNg, GetMidIndex002, TestSize.Level1)
{
    int32_t count = 3;

    ListModelNG model = CreateList();
    CreateListItems(count);
    CreateDone();

    /**
     * @tc.cases: The List is not empty
     * @tc.expected: mid index is 2
     */
    EXPECT_EQ(pattern_->GetMidIndex(), 2);
}

/**
 * @tc.name: SetListChildrenMainSize001
 * @tc.desc: Test ArcListPattern::SetListChildrenMainSize
 * @tc.type: FUNC
 */
HWTEST_F(ArcListAttrTestNg, SetListChildrenMainSize001, TestSize.Level1)
{
    int32_t count = 3;

    ListModelNG model = CreateList();
    CreateListItems(count);
    CreateDone();

    std::vector<float> mainSize = { 10, 20, 30 };
    float defaultSize = 50;
    pattern_->SetListChildrenMainSize(defaultSize, mainSize);

    RefPtr<ListChildrenMainSize> childrenSize = pattern_->GetOrCreateListChildrenMainSize();
    for (int32_t i = 0; i < count; ++i) {
        EXPECT_EQ(childrenSize->GetChildSize(i), mainSize.at(i));
    }
}

/**
 * @tc.name: GetOneItemSnapPosByFinalPos001
 * @tc.desc: Test ArcListPattern::GetOneItemSnapPosByFinalPos
 * @tc.type: FUNC
 */
HWTEST_F(ArcListAttrTestNg, GetOneItemSnapPosByFinalPos001, TestSize.Level1)
{
    int32_t count = 1;

    /**
     * @tc.steps: Create arc list with item height greater than ARC_LIST_ITEM_SNAP_SIZE(72.5f)
     * @tc.expected: ArcListPattern::GetOneItemSnapPosByFinalPos call return true.
     */
    ListModelNG model = CreateList();
    CreateListItems(count);
    CreateDone();

    float mainPos = 20.0;
    float finalPos = 10.0;
    float snapPos = 0.0;
    LayoutConstraintF parentConstraint;
    SizeF size(400.0, 400.0);
    parentConstraint.UpdateMaxSizeWithCheck(size);
    layoutProperty_->UpdateLayoutConstraint(parentConstraint);
    layoutProperty_->UpdateSpace(Dimension(1000.0));

    EXPECT_FALSE(pattern_->GetOneItemSnapPosByFinalPos(mainPos, finalPos, snapPos));
}

/**
 * @tc.name: GetOneItemSnapPosByFinalPos002
 * @tc.desc: Test ArcListPattern::GetOneItemSnapPosByFinalPos
 * @tc.type: FUNC
 */
HWTEST_F(ArcListAttrTestNg, GetOneItemSnapPosByFinalPos002, TestSize.Level1)
{
    int32_t count = 2;

    /**
     * @tc.steps: Create arc list with item height less than ARC_LIST_ITEM_SNAP_SIZE(72.5f)
     * @tc.expected: ArcListPattern::GetOneItemSnapPosByFinalPos call return false.
     */
    ListModelNG model = CreateList();
    CreateListItemsWithSize(count, SizeT<Dimension>(FILL_LENGTH, Dimension(70.f)));
    CreateDone();

    float mainPos = 20.0;
    float finalPos = 10.0;
    float snapPos = 0.0;
    LayoutConstraintF parentConstraint;
    SizeF size(400.0, 400.0);
    parentConstraint.UpdateMaxSizeWithCheck(size);
    layoutProperty_->UpdateLayoutConstraint(parentConstraint);
    layoutProperty_->UpdateSpace(Dimension(1000.0));

    EXPECT_FALSE(pattern_->GetOneItemSnapPosByFinalPos(mainPos, finalPos, snapPos));
}

/**
 * @tc.name: GetScrollIndexAbility001
 * @tc.desc: Test ArcListPattern::GetScrollIndexAbility
 * @tc.type: FUNC
 */
HWTEST_F(ArcListAttrTestNg, GetScrollIndexAbility001, TestSize.Level1)
{
    ListModelNG model = CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();

    auto scrollIndexAbility = pattern_->GetScrollIndexAbility();
    if (scrollIndexAbility) {
        scrollIndexAbility(0);
        EXPECT_EQ(pattern_->GetTotalOffset(), 0);

        scrollIndexAbility(FocusHub::SCROLL_TO_HEAD);
        EXPECT_EQ(pattern_->GetTotalOffset(), 0);

        scrollIndexAbility(FocusHub::SCROLL_TO_TAIL);
        EXPECT_EQ(pattern_->GetTotalOffset(), 0);
    }
}

/**
 * @tc.name: GetItemSnapPosition001
 * @tc.desc: Test ArcListPattern::GetItemSnapPosition
 * @tc.type: FUNC
 */
HWTEST_F(ArcListAttrTestNg, GetItemSnapPosition001, TestSize.Level1)
{
    int32_t count = 3;

    // Create list item height greater than ARC_LIST_ITEM_SNAP_SIZE(72.5).
    ListModelNG model = CreateList();
    CreateListItems(count);
    CreateDone();

    ItemSnapInfo snapInfo;
    for (int32_t i = 0; i < count; ++i) {
        pattern_->GetItemSnapPosition(i, snapInfo);
        EXPECT_EQ(snapInfo.snapLow, 0);
        EXPECT_EQ(snapInfo.snapHigh, 0);
        EXPECT_EQ(snapInfo.moveThreshold, 0);
    }
}

/**
 * @tc.name: GetItemSnapPosition002
 * @tc.desc: Test ArcListPattern::GetItemSnapPosition
 * @tc.type: FUNC
 */
HWTEST_F(ArcListAttrTestNg, GetItemSnapPosition002, TestSize.Level1)
{
    int32_t count = 3;

    ListModelNG model = CreateList();
    ViewAbstract::SetWidth(CalcLength(LIST_WIDTH));
    ViewAbstract::SetHeight(CalcLength(LIST_HEIGHT));

    float itemHeight = 70.f;
    // Create list item height less than ARC_LIST_ITEM_SNAP_SIZE(72.5).
    CreateListItemsWithSize(count, SizeT<Dimension>(FILL_LENGTH, Dimension(itemHeight)));
    CreateDone();

    ItemSnapInfo snapInfo;
    for (int32_t i = 0; i < count; ++i) {
        pattern_->GetItemSnapPosition(i, snapInfo);
        EXPECT_EQ(snapInfo.snapLow, 0);
        EXPECT_EQ(snapInfo.snapHigh, 0);
        EXPECT_EQ(snapInfo.moveThreshold, 0);
    }
}

/**
 * @tc.name: ToJsonValue001
 * @tc.desc: Test ArcListPattern::ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(ArcListAttrTestNg, ToJsonValue001, TestSize.Level1)
{
    int32_t count = 3;

    ListModelNG model = CreateList();
    CreateListItems(count);
    CreateDone();

    auto json = JsonUtil::Create(true);
    InspectorFilter filter2;

    // Call first.
    pattern_->ToJsonValue(json, filter2);
    EXPECT_EQ(json->GetString("digitalCrownSensitivity"), "CrownSensitivity.MEDIUM");

    // Change filter then call second to cover more switch.
    filter2.AddFilterAttr("id");
    filter2.AddFilterAttr("content");

    pattern_->ToJsonValue(json, filter2);
    EXPECT_EQ(json->GetString("digitalCrownSensitivity"), "CrownSensitivity.MEDIUM");
}

/**
 * @tc.name: EdgeEffectOption001
 * @tc.desc: Test EdgeEffectOption
 * @tc.type: FUNC
 */
HWTEST_F(ArcListAttrTestNg, EdgeEffectOption001, TestSize.Level1)
{
    ListModelNG model = CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    EXPECT_FALSE(pattern_->GetAlwaysEnabled());
    EXPECT_TRUE(pattern_->isScrollable_);
}

/**
 * @tc.name: EdgeEffectOption002
 * @tc.desc: Test EdgeEffectOption
 * @tc.type: FUNC
 */
HWTEST_F(ArcListAttrTestNg, EdgeEffectOption002, TestSize.Level1)
{
    ListModelNG model = CreateList();
    CreateListItems(1);
    CreateDone();
    EXPECT_FALSE(pattern_->GetAlwaysEnabled());
    EXPECT_TRUE(pattern_->isScrollable_);
}

/**
 * @tc.name: SetEdgeEffectCallback003
 * @tc.desc: Test GetScrollEdgeEffect
 * @tc.type: FUNC
 */
HWTEST_F(ArcListAttrTestNg, SetEdgeEffectCallback003, TestSize.Level1)
{
    ListModelNG model = CreateList();
    CreateDone();
    RefPtr<ScrollEdgeEffect> scrollEdgeEffect = pattern_->GetScrollEdgeEffect();
    EXPECT_EQ(scrollEdgeEffect->currentPositionCallback_(), 0);
    EXPECT_EQ(scrollEdgeEffect->leadingCallback_(), 0);
    EXPECT_EQ(scrollEdgeEffect->trailingCallback_(), 0.0);
    EXPECT_EQ(scrollEdgeEffect->initLeadingCallback_(), 0);
    EXPECT_EQ(scrollEdgeEffect->initTrailingCallback_(), 0.0);
}

/**
 * @tc.name: FadingEdge001
 * @tc.desc: Test SetFadingEdge
 * @tc.type: FUNC
 */
HWTEST_F(ArcListAttrTestNg, FadingEdge001, TestSize.Level1)
{
    /**
     * @tc.cases: SetFadingEdge false
     * @tc.expected: FadingEdge false
     */
    ListModelNG model = CreateList();
    model.SetEditMode(false);
    CreateListItems(1);
    CreateDone();
    EXPECT_FALSE(layoutProperty_->GetEditModeValue(true));

    /**
     * @tc.cases: SetFadingEdge true
     * @tc.expected: FadingEdge true
     */
    model = CreateList();
    model.SetEditMode(true);
    CreateListItems(1);
    CreateDone();
    EXPECT_TRUE(layoutProperty_->GetEditModeValue(true));
}

/**
 * @tc.name: FadingEdge002
 * @tc.desc: Test SetFadingEdge
 * @tc.type: FUNC
 */
HWTEST_F(ArcListAttrTestNg, FadingEdge002, TestSize.Level1)
{
    /**
     * @tc.cases: ContentStartOffset 50.f and Space 10.f
     * @tc.expected: startMainPos_ >= 0 and endMainPos_ > contentMainSize_
     */
    ListModelNG model = CreateList();
    model.SetEditMode(true);
    model.SetSpace(Dimension(10.f));
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    EXPECT_EQ(pattern_->GetTotalOffset(), 0);
    EXPECT_EQ(pattern_->startMainPos_, 0);
    EXPECT_EQ(pattern_->endMainPos_, 0);

    /**
     * @tc.cases: ScrollTo 0.f
     * @tc.expected: startMainPos_ >= 0 and endMainPos_ > contentMainSize_
     */
    pattern_->ScrollTo(0);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->startMainPos_, 150.f);
    EXPECT_EQ(pattern_->endMainPos_, 480.f);
    EXPECT_EQ(pattern_->GetTotalOffset(), -150.f);

    /**
     * @tc.cases: ScrollTo 50.f
     * @tc.expected: startMainPos_ < 0
     */
    pattern_->ScrollTo(50);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->startMainPos_, -50.f);
    EXPECT_EQ(pattern_->endMainPos_, 500.f);
    EXPECT_EQ(pattern_->GetTotalOffset(), 50.f);
}

/**
 * @tc.name: InitDisableEvent001
 * @tc.desc: Test ArcListItemPattern::InitDisableEvent, to cover more switch
 * @tc.type: FUNC
 */
HWTEST_F(ArcListAttrTestNg, InitDisableEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ArcListItem in card mode.
     */
    ListItemModelNG itemModel;
    itemModel.Create([](int32_t) {}, V2::ListItemStyle::CARD, true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ArcListItemPattern>();
    ASSERT_NE(pattern, nullptr);

    auto eventHub = frameNode->GetEventHub<ListItemEventHub>();
    eventHub->SetEnabled(false);
    pattern->InitDisableEvent();

    auto opacity = frameNode->GetRenderContext()->GetOpacity();
    // var disabledAlpha define in arc_list_item_theme.h.
    double disabledAlpha = 0.4;
    EXPECT_EQ(opacity.value_or(-0.001), disabledAlpha);

    eventHub->SetEnabled(true);
    pattern->InitDisableEvent();

    opacity = frameNode->GetRenderContext()->GetOpacity();
    // 1.0 is default value.
    EXPECT_EQ(opacity.value_or(-0.001), 1.0);
}
} // namespace OHOS::Ace::NG
