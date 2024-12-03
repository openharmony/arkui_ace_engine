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

#include "list_test_ng.h"
#include "test/mock/core/animation/mock_animation_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

namespace OHOS::Ace::NG {
class ListAttrTestNg : public ListTestNg {
public:
};

/**
 * @tc.name: ListLayoutProperty001
 * @tc.desc: Test List layout properties.
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, ListLayoutProperty001, TestSize.Level1)
{
    ListModelNG model = CreateList();
    model.SetSpace(Dimension(10));
    model.SetInitialIndex(1);
    model.SetListDirection(Axis::VERTICAL);
    model.SetScrollBar(DisplayMode::ON);
    model.SetEditMode(true);
    model.SetChainAnimation(true);
    model.SetEdgeEffect(EdgeEffect::NONE, false);
    model.SetLanes(3);
    model.SetLaneMinLength(Dimension(40));
    model.SetLaneMaxLength(Dimension(60));
    model.SetListItemAlign(V2::ListItemAlign::CENTER);
    model.SetCachedCount(10);
    model.SetSticky(V2::StickyStyle::HEADER);
    model.SetScrollSnapAlign(V2::ScrollSnapAlign::START);
    CreateDone();

    /**
     * @tc.steps: step1. Call ToJsonValue()
     * @tc.expected: The json value is correct
     */
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    EXPECT_EQ(Dimension::FromString(json->GetString("space")), Dimension(10));
    EXPECT_EQ(json->GetString("initialIndex"), "1");
    EXPECT_EQ(json->GetString("listDirection"), "Axis.Vertical");
    EXPECT_TRUE(json->GetBool("editMode"));
    EXPECT_TRUE(json->GetBool("chainAnimation"));
    EXPECT_EQ(json->GetString("divider"), "");
    EXPECT_EQ(json->GetString("lanes"), "3");
    EXPECT_EQ(Dimension::FromString(json->GetString("laneMinLength")), Dimension(40));
    EXPECT_EQ(Dimension::FromString(json->GetString("laneMaxLength")), Dimension(60));
    EXPECT_EQ(json->GetString("alignListItem"), "ListItemAlign.Center");
    EXPECT_EQ(json->GetString("cachedCount"), "10");
    EXPECT_EQ(json->GetString("sticky"), "StickyStyle.Header");
    EXPECT_EQ(json->GetString("scrollSnapAlign"), "ScrollSnapAlign.START");

    /**
     * @tc.steps: step2. Change some property, Call ToJsonValue()
     * @tc.expected: The json value is correct
     */
    model = CreateList();
    model.SetListDirection(Axis::HORIZONTAL);
    model.SetListItemAlign(V2::ListItemAlign::END);
    model.SetSticky(V2::StickyStyle::FOOTER);
    model.SetScrollSnapAlign(V2::ScrollSnapAlign::CENTER);
    model.SetDivider(ITEM_DIVIDER);
    CreateDone();
    json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("listDirection"), "Axis.Horizontal");
    EXPECT_EQ(json->GetString("alignListItem"), "ListItemAlign.End");
    EXPECT_EQ(json->GetString("sticky"), "StickyStyle.Footer");
    EXPECT_EQ(json->GetString("scrollSnapAlign"), "ScrollSnapAlign.CENTER");
    auto dividerJson = json->GetObject("divider");
    EXPECT_EQ(Dimension::FromString(dividerJson->GetString("strokeWidth")), Dimension(STROKE_WIDTH));
    EXPECT_EQ(Dimension::FromString(dividerJson->GetString("startMargin")), Dimension(10));
    EXPECT_EQ(Dimension::FromString(dividerJson->GetString("endMargin")), Dimension(20));
    EXPECT_EQ(Color::ColorFromString(dividerJson->GetString("color")), Color(0x000000));

    /**
     * @tc.steps: step3. Change some property, Call ToJsonValue()
     * @tc.expected: The json value is changed
     */
    model = CreateList();
    model.SetListItemAlign(V2::ListItemAlign::START);
    model.SetSticky(V2::StickyStyle::BOTH);
    model.SetScrollSnapAlign(V2::ScrollSnapAlign::END);
    CreateDone();
    json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("alignListItem"), "ListItemAlign.Start");
    EXPECT_EQ(json->GetString("sticky"), "StickyStyle.Header | StickyStyle.Footer");
    EXPECT_EQ(json->GetString("scrollSnapAlign"), "ScrollSnapAlign.END");

    /**
     * @tc.steps: step3. Change some property, Call ToJsonValue()
     * @tc.expected: The json value is changed
     */
    model = CreateList();
    model.SetSticky(V2::StickyStyle::NONE);
    model.SetScrollSnapAlign(V2::ScrollSnapAlign::NONE);
    CreateDone();
    json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("sticky"), "StickyStyle.None");
    EXPECT_EQ(json->GetString("scrollSnapAlign"), "ScrollSnapAlign.NONE");

    /**
     * @tc.steps: step4. The json include strokeWidth and Change it, call FromJson()
     * @tc.expected: The layoutProperty_->GetDividerValue().strokeWidth changed
     */
    dividerJson = json->GetObject("divider");
    dividerJson->Replace("strokeWidth", Dimension(20).ToString().c_str());
    layoutProperty_->FromJson(json);
    EXPECT_EQ(layoutProperty_->GetDividerValue().strokeWidth, Dimension(20));

    /**
     * @tc.steps: step5. The json not include strokeWidth, call FromJson()
     * @tc.expected: The layoutProperty_->GetDividerValue() not changed
     */
    dividerJson->Delete("strokeWidth");
    layoutProperty_->FromJson(json);
    EXPECT_EQ(layoutProperty_->GetDividerValue().strokeWidth, Dimension(20));
}

/**
 * @tc.name: ListLayoutProperty002
 * @tc.desc: Test List layout properties.
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, ListLayoutProperty002, TestSize.Level1)
{
    ListModelNG model = CreateList();
    CreateDone();

    /**
     * @tc.step1: set invalid values for LaneMinLength and LaneMaxLength
     * @tc.expected: default value
     */
    model.SetListFriction(AceType::RawPtr(frameNode_), 0);
    model.SetListScrollBar(AceType::RawPtr(frameNode_), 3);
    model.SetLaneConstrain(AceType::RawPtr(frameNode_), Dimension(0), Dimension(0));
    EXPECT_EQ(paintProperty_->GetScrollBarModeValue(DisplayMode::OFF), DisplayMode::AUTO);
    EXPECT_EQ(pattern_->friction_, FRICTION);
    EXPECT_FALSE(layoutProperty_->HasLaneMinLength());
    EXPECT_FALSE(layoutProperty_->HasLaneMaxLength());

    /**
     * @tc.step2: set valid values for LaneMinLength and LaneMaxLength
     * @tc.expected: the set value
     */
    model.SetListFriction(AceType::RawPtr(frameNode_), API12_FRICTION);
    model.SetLaneConstrain(AceType::RawPtr(frameNode_), Dimension(40), Dimension(60));
    model.SetListScrollBar(AceType::RawPtr(frameNode_), 2);
    EXPECT_EQ(paintProperty_->GetScrollBarModeValue(DisplayMode::OFF), DisplayMode::ON);
    EXPECT_EQ(pattern_->friction_, API12_FRICTION);
    EXPECT_EQ(layoutProperty_->GetLaneMinLengthValue(), Dimension(40));
    EXPECT_EQ(layoutProperty_->GetLaneMaxLengthValue(), Dimension(60));
    model.SetListScrollBar(AceType::RawPtr(frameNode_), -1);
    EXPECT_EQ(paintProperty_->GetScrollBarModeValue(DisplayMode::OFF), DisplayMode::AUTO);
}

/**
 * @tc.name: ListLayoutProperty003
 * @tc.desc: Test List layout properties with fastFilter
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, ListLayoutProperty003, TestSize.Level1)
{
    CreateList();
    CreateDone();
    InspectorFilter filter;
    std::string attr = "editable";
    filter.AddFilterAttr(attr);
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    EXPECT_EQ(json->ToString(), "{}");
}

/**
 * @tc.name: ListItemLayoutProperty001
 * @tc.desc: Test ListItem layout properties.
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, ListItemLayoutProperty001, TestSize.Level1)
{
    CreateList();
    ListItemModelNG itemModel = CreateListItem();
    CreateDone();
    auto layoutProperty = GetChildLayoutProperty<ListItemLayoutProperty>(frameNode_, 0);

    /**
     * @tc.steps: step1. Call ToJsonValue()
     * @tc.expected: The json value is correct
     */
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    layoutProperty->ToJsonValue(json, filter);
    EXPECT_EQ(static_cast<V2::StickyMode>(json->GetInt("sticky")), V2::StickyMode::NONE);
    EXPECT_FALSE(json->GetBool("editable"));
    EXPECT_EQ(Dimension::FromString(json->GetString("startDeleteAreaDistance")), Dimension(0, DimensionUnit::VP));
    EXPECT_EQ(Dimension::FromString(json->GetString("endDeleteAreaDistance")), Dimension(0, DimensionUnit::VP));

    /**
     * @tc.steps: step2. Change some property, Call ToJsonValue()
     * @tc.expected: The json value is correct
     */
    CreateList();
    itemModel = CreateListItem();
    itemModel.SetSticky(V2::StickyMode::NORMAL);
    itemModel.SetEditMode(V2::EditMode::NONE);
    itemModel.SetSwiperAction(nullptr, nullptr, nullptr, V2::SwipeEdgeEffect::Spring);
    CreateDone();
    json = JsonUtil::Create(true);
    layoutProperty->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("sticky"), "Sticky.Normal");
    EXPECT_EQ(json->GetString("editable"), "EditMode.None");
    auto swipeAction = json->GetObject("swipeAction");
    EXPECT_EQ(static_cast<V2::SwipeEdgeEffect>(swipeAction->GetInt("edgeEffect")), V2::SwipeEdgeEffect::Spring);

    /**
     * @tc.steps: step3. Change some property, Call ToJsonValue()
     * @tc.expected: The json value is correct
     */
    CreateList();
    itemModel = CreateListItem();
    itemModel.SetSticky(V2::StickyMode::OPACITY);
    itemModel.SetEditMode(V2::EditMode::MOVABLE);
    itemModel.SetSwiperAction(nullptr, nullptr, nullptr, V2::SwipeEdgeEffect::None);
    CreateDone();
    json = JsonUtil::Create(true);
    layoutProperty->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("sticky"), "Sticky.Opacity");
    EXPECT_EQ(json->GetString("editable"), "EditMode.Movable");
    swipeAction = json->GetObject("swipeAction");
    EXPECT_EQ(swipeAction->GetString("edgeEffect"), "SwipeEdgeEffect.None");

    /**
     * @tc.steps: step4. Change some property, Call ToJsonValue()
     * @tc.expected: The json value is correct
     */
    CreateList();
    itemModel = CreateListItem();
    itemModel.SetEditMode(V2::EditMode::DELETABLE);
    CreateDone();
    json = JsonUtil::Create(true);
    layoutProperty->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("editable"), "EditMode.Deletable");

    /**
     * @tc.steps: step5. Change some property, Call ToJsonValue()
     * @tc.expected: The json value is correct
     */
    CreateList();
    itemModel = CreateListItem();
    itemModel.SetEditMode(V2::EditMode::DELETABLE | V2::EditMode::MOVABLE);
    CreateDone();
    json = JsonUtil::Create(true);
    layoutProperty->ToJsonValue(json, filter);
    EXPECT_TRUE(json->GetBool("editable"));
}

/**
 * @tc.name: ListItemLayoutProperty002
 * @tc.desc: Test ListItem layout properties with fastFilter
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, ListItemLayoutProperty002, TestSize.Level1)
{
    CreateList();
    ListItemModelNG itemModel = CreateListItem();
    CreateDone();
    auto layoutProperty = GetChildLayoutProperty<ListItemLayoutProperty>(frameNode_, 0);

    /**
     * @tc.steps: step1. IsFastFilter
     * @tc.expected: Test editable
     */
    InspectorFilter filter;
    std::string attr = "editable";
    filter.AddFilterAttr(attr);
    EXPECT_TRUE(filter.IsFastFilter());
    auto json = JsonUtil::Create(true);
    layoutProperty->ToJsonValue(json, filter);
    EXPECT_FALSE(json->GetBool("editable"));

    layoutProperty->UpdateEditMode(V2::EditMode::NONE);
    json = JsonUtil::Create(true);
    layoutProperty->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("editable"), "EditMode.None");

    layoutProperty->UpdateEditMode(V2::EditMode::MOVABLE);
    json = JsonUtil::Create(true);
    layoutProperty->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("editable"), "EditMode.Movable");

    layoutProperty->UpdateEditMode(V2::EditMode::DELETABLE);
    json = JsonUtil::Create(true);
    layoutProperty->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("editable"), "EditMode.Deletable");

    layoutProperty->UpdateEditMode(V2::EditMode::DELETABLE | V2::EditMode::MOVABLE);
    json = JsonUtil::Create(true);
    layoutProperty->ToJsonValue(json, filter);
    EXPECT_TRUE(json->GetBool("editable"));
}

/**
 * @tc.name: AttrSpace001
 * @tc.desc: Test property about space
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, AttrSpace001, TestSize.Level1)
{
    /**
     * @tc.cases: Set space
     * @tc.expected: Has space
     */
    ListModelNG model = CreateList();
    model.SetSpace(Dimension(SPACE));
    CreateListItems(2);
    CreateDone();
    EXPECT_EQ(GetChildY(frameNode_, 1), GetChildHeight(frameNode_, 0) + SPACE);
}

/**
 * @tc.name: AttrSpace002
 * @tc.desc: Test property about space with itemGroup in Horizontal layout
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, AttrSpace002, TestSize.Level1)
{
    /**
     * @tc.cases: Set space:SPACE, set Horizontal layout
     * @tc.expected: Has space
     */
    ListModelNG model = CreateList();
    model.SetListDirection(Axis::HORIZONTAL);
    model.SetSpace(Dimension(SPACE));
    CreateListItemGroups(2);
    CreateDone();
    EXPECT_EQ(pattern_->GetAxis(), Axis::HORIZONTAL);
    EXPECT_EQ(GetChildX(frameNode_, 1), GetChildWidth(frameNode_, 0) + SPACE);
}

/**
 * @tc.name: AttrSpace003
 * @tc.desc: Test property about space with invalid value
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, AttrSpace003, TestSize.Level1)
{
    /**
     * @tc.cases: Set invalid space:LIST_HEIGHT
     * @tc.expected: Space was going to be zero
     */
    ListModelNG model = CreateList();
    model.SetSpace(Dimension(LIST_HEIGHT));
    CreateListItems(2);
    CreateDone();
    EXPECT_EQ(GetChildY(frameNode_, 1), GetChildHeight(frameNode_, 0));

    /**
     * @tc.cases: Set invalid space: -1
     * @tc.expected: Space was going to be zero
     */
    model = CreateList();
    model.SetSpace(Dimension(-1));
    CreateListItems(2);
    CreateDone();
    EXPECT_EQ(GetChildY(frameNode_, 1), GetChildHeight(frameNode_, 0));
}

/**
 * @tc.name: AttrDivider001
 * @tc.desc: Test property about divider
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, AttrDivider001, TestSize.Level1)
{
    /**
     * @tc.cases: Set divider
     * @tc.expected: Has divider, the divider width is STROKE_WIDTH
     */
    ListModelNG model = CreateList();
    model.SetDivider(ITEM_DIVIDER);
    CreateListItems(2);
    CreateDone();
    EXPECT_EQ(GetChildY(frameNode_, 1), GetChildHeight(frameNode_, 0) + STROKE_WIDTH);
}

/**
 * @tc.name: AttrDivider002
 * @tc.desc: Test property about divider and space in Horizontal layout
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, AttrDivider002, TestSize.Level1)
{
    /**
     * @tc.cases: Set space less than divider's STROKE_WIDTH
     * @tc.expected: Space was going to be STROKE_WIDTH
     */
    ListModelNG model = CreateList();
    model.SetListDirection(Axis::HORIZONTAL);
    model.SetSpace(Dimension(STROKE_WIDTH - 1.f));
    model.SetDivider(ITEM_DIVIDER);
    CreateListItems(2);
    CreateDone();
    EXPECT_EQ(GetChildX(frameNode_, 1), GetChildWidth(frameNode_, 0) + STROKE_WIDTH);
}

/**
 * @tc.name: AttrDivider003
 * @tc.desc: Test property about divider with invalid value
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, AttrDivider003, TestSize.Level1)
{
    /**
     * @tc.cases: Set invalid strokeWidth:LIST_HEIGHT
     * @tc.expected: strokeWidth was going to be zero
     */
    auto divider = ITEM_DIVIDER;
    divider.strokeWidth = Dimension(LIST_HEIGHT);
    ListModelNG model = CreateList();
    model.SetDivider(divider);
    CreateListItems(2);
    CreateDone();
    EXPECT_EQ(GetChildY(frameNode_, 1), GetChildHeight(frameNode_, 0));
}

/**
 * @tc.name: AttrInitIndex001
 * @tc.desc: Test property about initialIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, AttrInitIndex001, TestSize.Level1)
{
    /**
     * @tc.cases: Not set initialIndex
     * @tc.expected: List default at top
     */
    CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    EXPECT_TRUE(pattern_->IsAtTop());
    EXPECT_TRUE(Position(0));
}
/**
 * @tc.name: AttrInitIndex002
 * @tc.desc: Test property about initialIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, AttrInitIndex002, TestSize.Level1)
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
    EXPECT_EQ(GetChildY(frameNode_, 1), 0.f);
    EXPECT_TRUE(Position(-ITEM_MAIN_SIZE));
}

/**
 * @tc.name: AttrInitIndex003
 * @tc.desc: Test property about initialIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, AttrInitIndex003, TestSize.Level1)
{
    /**
     * @tc.cases: Set initialIndex:1, total ListItem size less than viewport
     * @tc.expected: List is unScrollable, list is at top
     */
    ListModelNG model = CreateList();
    model.SetInitialIndex(1);
    CreateListItems(2);
    CreateDone();
    EXPECT_FALSE(pattern_->IsScrollable());
    EXPECT_TRUE(pattern_->IsAtTop());
}

/**
 * @tc.name: AttrInitIndex004
 * @tc.desc: Test property about initialIndex in Horizontal layout
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, AttrInitIndex004, TestSize.Level1)
{
    /**
     * @tc.cases: Set Horizontal layout, set initialIndex:5, the initialIndex greater than scrollable distance
     * @tc.expected: List is at bottom
     */
    ListModelNG model = CreateList();
    model.SetListDirection(Axis::HORIZONTAL);
    model.SetInitialIndex(TOTAL_ITEM_NUMBER - 1);
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    EXPECT_TRUE(pattern_->IsAtBottom());
    EXPECT_TRUE(Position(-HORIZONTAL_SCROLLABLE_DISTANCE));
}

/**
 * @tc.name: AttrInitIndex005
 * @tc.desc: Test property about initialIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, AttrInitIndex005, TestSize.Level1)
{
    /**
     * @tc.cases: Set initialIndex:100, the initialIndex greater than max Index(itemSize-1)
     * @tc.expected: List is at top, ignore initialIndex
     */
    ListModelNG model = CreateList();
    model.SetInitialIndex(100);
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    EXPECT_TRUE(pattern_->IsAtTop());
}

/**
 * @tc.name: AttrInitIndex006
 * @tc.desc: Test property about initialIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, AttrInitIndex006, TestSize.Level1)
{
    /**
     * @tc.cases: Set initialIndex:3, the initialIndex is not an integer multiple of the lanes
     * @tc.expected: The item(index:2,3) is at top
     */
    const int32_t lanes = 2;
    ListModelNG model = CreateList();
    model.SetInitialIndex(3);
    model.SetLanes(lanes);
    CreateListItems(TOTAL_ITEM_NUMBER * lanes);
    CreateDone();
    EXPECT_EQ(GetChildY(frameNode_, 2), 0.f);
    EXPECT_EQ(GetChildY(frameNode_, 3), 0.f);
}

/**
 * @tc.name: AttrInitIndex007
 * @tc.desc: Test property about initialIndex with itemGroup
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, AttrInitIndex007, TestSize.Level1)
{
    /**
     * @tc.cases: Set initialIndex:1, create itemGroup
     * @tc.expected: The itemGroup(index:1) is at top
     */
    ListModelNG model = CreateList();
    model.SetInitialIndex(1);
    CreateListItemGroups(GROUP_NUMBER);
    CreateDone();
    EXPECT_EQ(GetChildY(frameNode_, 1), 0.f);
}

/**
 * @tc.name: AttrScrollBar001
 * @tc.desc: Test property about scrollBar
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, AttrScrollBar001, TestSize.Level1)
{
    /**
     * @tc.cases: Set scrollBar
     * @tc.expected: The itemGroup(index:1) is at top
     */
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
HWTEST_F(ListAttrTestNg, AttrScrollBar002, TestSize.Level1)
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
 * @tc.name: AttrLanes001
 * @tc.desc: Test property about lanes
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, AttrLanes001, TestSize.Level1)
{
    /**
     * @tc.cases: Set lanes:2
     * @tc.expected: Has two lanes
     */
    ListModelNG model = CreateList();
    model.SetLanes(2);
    CreateListItems();
    CreateDone();
    EXPECT_LT(GetChildX(frameNode_, 0), GetChildX(frameNode_, 1));
    EXPECT_EQ(GetChildX(frameNode_, 0), GetChildX(frameNode_, 2));
}

/**
 * @tc.name: AttrLanes002
 * @tc.desc: Test LayoutProperty about minLaneLength/maxLaneLength
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, AttrLanes002, TestSize.Level1)
{
    /**
     * @tc.cases: Set LaneMinLength half of LIST_WIDTH
     * @tc.expected: Has two lanes
     */
    ListModelNG model = CreateList();
    model.SetLaneMinLength(Dimension(LIST_WIDTH / 2 - 1));
    model.SetLaneMaxLength(Dimension(LIST_WIDTH));
    CreateListItems(4);
    CreateDone();
    EXPECT_LT(GetChildX(frameNode_, 0), GetChildX(frameNode_, 1));
    EXPECT_EQ(GetChildX(frameNode_, 0), GetChildX(frameNode_, 2));
}

/**
 * @tc.name: AttrLanes003
 * @tc.desc: Test LayoutProperty about minLaneLength, maxLaneLength,
 * when maxLaneLength less than minLaneLength, use minLaneLength
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, AttrLanes003, TestSize.Level1)
{
    /**
     * @tc.cases: Set LaneMinLength greater than LaneMaxLength
     * @tc.expected: Has two lanes, ignore LaneMaxLength
     */
    const float minLaneLength = LIST_WIDTH / 2 - 1;
    ListModelNG model = CreateList();
    model.SetLaneMinLength(Dimension(minLaneLength));
    model.SetLaneMaxLength(Dimension(minLaneLength - 1));
    CreateListItems(4);
    CreateDone();
    EXPECT_LT(GetChildX(frameNode_, 0), GetChildX(frameNode_, 1));
    EXPECT_EQ(GetChildX(frameNode_, 0), GetChildX(frameNode_, 2));
    EXPECT_EQ(GetChildWidth(frameNode_, 0), minLaneLength);
}

/**
 * @tc.name: AttrLanes004
 * @tc.desc: Test LayoutProperty about laneGutter
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, AttrLanes004, TestSize.Level1)
{
    /**
     * @tc.cases: Set lanes:2, set laneGutter:16.f
     * @tc.expected: Has laneGutter
     */
    const float laneGutter = 16.f;
    ListModelNG model = CreateList();
    model.SetLanes(2);
    model.SetLaneGutter(Dimension(laneGutter));
    CreateListItems(2);
    CreateDone();
    EXPECT_EQ(GetChildX(frameNode_, 1), GetChildWidth(frameNode_, 0) + laneGutter);
}

/**
 * @tc.name: AttrLanes005
 * @tc.desc: Test LaneGutter
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, AttrLanes005, TestSize.Level1)
{
    /**
     * @tc.cases: Set lanes:5, set laneGutter:"10%"
     * @tc.expected: Has laneGutter
     */
    Dimension laneGutter = Dimension::FromString("10%");
    ListModelNG model = CreateList();
    model.SetScrollBar(DisplayMode::OFF);
    model.SetLanes(5);
    model.SetLaneGutter(laneGutter);
    CreateListItems(2);
    CreateDone();
    double gutter = laneGutter.ConvertToPxWithSize(LIST_WIDTH);
    EXPECT_EQ(GetChildX(frameNode_, 1), GetChildWidth(frameNode_, 0) + gutter);
}

/**
 * @tc.name: AttrLanes006
 * @tc.desc: Test LayoutProperty about minLaneLength, maxLaneLength
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, AttrLanes006, TestSize.Level1)
{
    /**
     * @tc.cases: set invalid values for LaneMinLength and LaneMaxLength
     * @tc.expected: default value
     */
    ListModelNG model = CreateList();
    model.SetLaneMinLength(Dimension(0.f));
    model.SetLaneMaxLength(Dimension(0.f));
    CreateListItems(1);
    CreateDone();
    EXPECT_FALSE(layoutProperty_->HasLaneMinLength());
    EXPECT_FALSE(layoutProperty_->HasLaneMinLength());
}

/**
 * @tc.name: AttrAlignListItem001
 * @tc.desc: Test LayoutProperty about alignListItem
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, AttrAlignListItem001, TestSize.Level1)
{
    /**
     * @tc.cases: case1. Set item width smaller than LIST_WIDTH
     * @tc.expected: the item default is align to start
     */
    const float itemWidth = LIST_WIDTH / 2;
    ListModelNG model = CreateList();
    CreateListItem();
    ViewAbstract::SetWidth(CalcLength(itemWidth));
    CreateDone();
    EXPECT_EQ(GetChildX(frameNode_, 0), 0);

    /**
     * @tc.cases: case2. Set ListItemAlign::CENTER
     * @tc.expected: the item is align to center
     */
    layoutProperty_->UpdateListItemAlign(V2::ListItemAlign::CENTER);
    FlushUITasks();
    EXPECT_EQ(GetChildX(frameNode_, 0), (LIST_WIDTH - itemWidth) / 2);

    /**
     * @tc.cases: case3. Set ListItemAlign::END
     * @tc.expected: the item is align to end
     */
    layoutProperty_->UpdateListItemAlign(V2::ListItemAlign::END);
    FlushUITasks();
    EXPECT_EQ(GetChildX(frameNode_, 0), LIST_WIDTH - itemWidth);
}

/**
 * @tc.name: AttrAlignListItem002
 * @tc.desc: Test LayoutProperty about alignListItem in RTL Layout
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, AttrAlignListItem002, TestSize.Level1)
{
    /**
     * @tc.cases: case1. Set item width smaller than LIST_WIDTH
     * @tc.expected: the item default is align to start
     */
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    const float itemWidth = LIST_WIDTH / 2;
    CreateList();
    CreateListItem();
    ViewAbstract::SetWidth(CalcLength(itemWidth));
    CreateDone();
    EXPECT_EQ(GetChildX(frameNode_, 0), LIST_WIDTH - itemWidth);

    /**
     * @tc.cases: case2. Set ListItemAlign::CENTER
     * @tc.expected: the item is align to center
     */
    layoutProperty_->UpdateListItemAlign(V2::ListItemAlign::CENTER);
    FlushUITasks();
    EXPECT_EQ(GetChildX(frameNode_, 0), (LIST_WIDTH - itemWidth) / 2);

    /**
     * @tc.cases: case3. Set ListItemAlign::END
     * @tc.expected: the item is align to end
     */
    layoutProperty_->UpdateListItemAlign(V2::ListItemAlign::END);
    FlushUITasks();
    EXPECT_EQ(GetChildX(frameNode_, 0), 0);
}

/**
 * @tc.name: AttrEnableScrollInteraction001
 * @tc.desc: Test property about enableScrollInteraction.
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, AttrEnableScrollInteraction001, TestSize.Level1)
{
    /**
     * @tc.cases: Scrollable list, Not set ScrollEnabled
     * @tc.expected: Default by list isScrollable_
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
HWTEST_F(ListAttrTestNg, AttrEnableScrollInteraction002, TestSize.Level1)
{
    /**
     * @tc.cases: UnScrollable list, Not set ScrollEnabled
     * @tc.expected: Default by list isScrollable_
     */
    ListModelNG model = CreateList();
    model.SetScrollEnabled(true);
    model.SetScrollSnapAlign(V2::ScrollSnapAlign::CENTER);
    CreateDone();
    EXPECT_FALSE(pattern_->scrollableEvent_->GetEnabled());
    EXPECT_TRUE(pattern_->IsScrollSnapAlignCenter());
    EXPECT_FALSE(pattern_->IsAtTop());
    EXPECT_TRUE(pattern_->IsAtBottom());
}

/**
 * @tc.name: AttrEnableScrollInteraction003
 * @tc.desc: Test property about enableScrollInteraction.
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, AttrEnableScrollInteraction003, TestSize.Level1)
{
    /**
     * @tc.cases: Scrollable list, set ScrollEnabled:false
     * @tc.expected: Default by list isScrollable_
     */
    ListModelNG model = CreateList();
    model.SetScrollEnabled(false);
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    EXPECT_FALSE(pattern_->scrollableEvent_->GetEnabled());
}

/**
 * @tc.name: AttrEnableScrollInteraction004
 * @tc.desc: Test property about enableScrollInteraction.
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, AttrEnableScrollInteraction004, TestSize.Level1)
{
    /**
     * @tc.cases: UnScrollable list, Set ScrollEnabled:true
     * @tc.expected: Decided by list isScrollable_
     */
    ListModelNG model = CreateList();
    model.SetScrollEnabled(true);
    CreateListItems(1);
    CreateDone();
    EXPECT_FALSE(pattern_->scrollableEvent_->GetEnabled());
}

/**
 * @tc.name: AttrFriction001
 * @tc.desc: Test SetFriction:friction shouled be more than 0.0,if out of range,should be default value.
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, AttrFriction001, TestSize.Level1)
{
    /**
     * @tc.cases: Set invalid friction:0
     * @tc.expected: Friction is default
     */
    ListModelNG model = CreateList();
    model.SetFriction(0);
    CreateListItems(1);
    CreateDone();
    EXPECT_DOUBLE_EQ(pattern_->GetFriction(), FRICTION);
}

/**
 * @tc.name: AttrFriction002
 * @tc.desc: Test SetFriction:friction shouled be more than 0.0,if out of range,should be default value.
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, AttrFriction002, TestSize.Level1)
{
    /**
     * @tc.cases: Set invalid friction:-1
     * @tc.expected: Friction is default
     */
    ListModelNG model = CreateList();
    model.SetFriction(-1);
    CreateListItems(1);
    CreateDone();
    EXPECT_DOUBLE_EQ(pattern_->GetFriction(), FRICTION);
}

/**
 * @tc.name: AttrFriction003
 * @tc.desc: Test SetFriction:friction shouled be more than 0.0,if out of range,should be default value.
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, AttrFriction003, TestSize.Level1)
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
 * @tc.name: EdgeEffectOption001
 * @tc.desc: Test EdgeEffectOption
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, EdgeEffectOption001, TestSize.Level1)
{
    ListModelNG model = CreateList();
    model.SetEdgeEffect(EdgeEffect::SPRING, false);
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
HWTEST_F(ListAttrTestNg, EdgeEffectOption002, TestSize.Level1)
{
    ListModelNG model = CreateList();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    EXPECT_TRUE(pattern_->GetAlwaysEnabled());
    EXPECT_TRUE(pattern_->isScrollable_);
}

/**
 * @tc.name: EdgeEffectOption003
 * @tc.desc: Test EdgeEffectOption
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, EdgeEffectOption003, TestSize.Level1)
{
    ListModelNG model = CreateList();
    model.SetEdgeEffect(EdgeEffect::SPRING, false);
    CreateListItems(1);
    CreateDone();
    EXPECT_FALSE(pattern_->GetAlwaysEnabled());
    EXPECT_FALSE(pattern_->isScrollable_);
}

/**
 * @tc.name: EdgeEffectOption004
 * @tc.desc: Test EdgeEffectOption
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, EdgeEffectOption004, TestSize.Level1)
{
    ListModelNG model = CreateList();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateListItems(1);
    CreateDone();
    EXPECT_TRUE(pattern_->GetAlwaysEnabled());
    EXPECT_TRUE(pattern_->isScrollable_);
}

/**
 * @tc.name: SetEdgeEffectCallback001
 * @tc.desc: Test SetEdgeEffectCallback
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, SetEdgeEffectCallback001, TestSize.Level1)
{
    ListModelNG model = CreateList();
    model.SetEdgeEffect(EdgeEffect::SPRING, false);
    CreateListItems(1);
    CreateDone();
    RefPtr<ScrollEdgeEffect> scrollEdgeEffect = pattern_->GetScrollEdgeEffect();
    EXPECT_EQ(scrollEdgeEffect->currentPositionCallback_(), 0);
    EXPECT_EQ(scrollEdgeEffect->leadingCallback_(), 0);
    EXPECT_EQ(scrollEdgeEffect->trailingCallback_(), 0.0);
    EXPECT_EQ(scrollEdgeEffect->initLeadingCallback_(), 0);
    EXPECT_EQ(scrollEdgeEffect->initTrailingCallback_(), 0.0);
}

/**
 * @tc.name: SetEdgeEffectCallback002
 * @tc.desc: Test SetEdgeEffectCallback
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, SetEdgeEffectCallback002, TestSize.Level1)
{
    ListModelNG model = CreateList();
    model.SetScrollSnapAlign(V2::ScrollSnapAlign::CENTER);
    model.SetEdgeEffect(EdgeEffect::SPRING, false);
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    RefPtr<ScrollEdgeEffect> scrollEdgeEffect = pattern_->GetScrollEdgeEffect();
    EXPECT_EQ(scrollEdgeEffect->currentPositionCallback_(), 150.0);
    EXPECT_EQ(scrollEdgeEffect->trailingCallback_(), 150.f);
    EXPECT_EQ(scrollEdgeEffect->initTrailingCallback_(), 150.f);
    EXPECT_TRUE(GreatNotEqual(150.0, scrollEdgeEffect->leadingCallback_()));

    ScrollToIndex(TOTAL_ITEM_NUMBER - 1, false, ScrollAlign::CENTER);
    EXPECT_EQ(scrollEdgeEffect->currentPositionCallback_(), -50.0);
    EXPECT_EQ(scrollEdgeEffect->leadingCallback_(), -50.0);
    EXPECT_EQ(scrollEdgeEffect->initLeadingCallback_(), -50.0);
    EXPECT_TRUE(LessNotEqual(-50, scrollEdgeEffect->trailingCallback_()));
}

/**
 * @tc.name: SetEdgeEffectCallback003
 * @tc.desc: Test SetEdgeEffectCallback
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, SetEdgeEffectCallback003, TestSize.Level1)
{
    ListModelNG model = CreateList();
    model.SetScrollSnapAlign(V2::ScrollSnapAlign::CENTER);
    model.SetEdgeEffect(EdgeEffect::SPRING, false);
    CreateDone();
    RefPtr<ScrollEdgeEffect> scrollEdgeEffect = pattern_->GetScrollEdgeEffect();
    EXPECT_EQ(scrollEdgeEffect->currentPositionCallback_(), 0);
    EXPECT_EQ(scrollEdgeEffect->leadingCallback_(), 400);
    EXPECT_EQ(scrollEdgeEffect->trailingCallback_(), 0.0);
    EXPECT_EQ(scrollEdgeEffect->initLeadingCallback_(), 400);
    EXPECT_EQ(scrollEdgeEffect->initTrailingCallback_(), 0.0);
}

/**
 * @tc.name: ChainAnimation001
 * @tc.desc: Test SetChainAnimationOptions
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, ChainAnimation001, TestSize.Level1)
{
    constexpr float minSpace = 10.f;
    constexpr float maxSpace = 2.f;
    constexpr float conductivity = 5.f;
    constexpr float intensity = 5.f;
    ChainAnimationOptions options = {
        .minSpace = Dimension(minSpace),
        .maxSpace = Dimension(maxSpace),
        .conductivity = conductivity,
        .intensity = intensity,
        .edgeEffect = 0,
        .stiffness = DEFAULT_STIFFNESS,
        .damping = DEFAULT_DAMPING,
    };
    ListModelNG model = CreateList();
    model.SetSpace(Dimension(SPACE));
    model.SetChainAnimation(true);
    model.SetChainAnimationOptions(options);
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();

    /**
     * @tc.steps: step1. When minSpace > maxSpace.
     * @tc.expected: minSpace and maxSpace would be SPACE.
     */
    auto chainAnimation = pattern_->chainAnimation_;
    EXPECT_FLOAT_EQ(chainAnimation->minSpace_, SPACE);
    EXPECT_FLOAT_EQ(chainAnimation->maxSpace_, SPACE);

    /**
     * @tc.steps: step2. When conductivity > 1, intensity > 1.
     * @tc.expected: conductivity/intensity would be default value.
     */
    EXPECT_FLOAT_EQ(chainAnimation->conductivity_, ChainAnimation::DEFAULT_CONDUCTIVITY);
    EXPECT_FLOAT_EQ(chainAnimation->intensity_, ChainAnimation::DEFAULT_INTENSITY);

    /**
     * @tc.steps: step3. SetChainAnimationOptions again
     */
    pattern_->SetChainAnimationOptions(options);
    chainAnimation = pattern_->chainAnimation_;
    EXPECT_FLOAT_EQ(chainAnimation->minSpace_, SPACE);
    EXPECT_FLOAT_EQ(chainAnimation->maxSpace_, SPACE);
    EXPECT_FLOAT_EQ(chainAnimation->conductivity_, ChainAnimation::DEFAULT_CONDUCTIVITY);
    EXPECT_FLOAT_EQ(chainAnimation->intensity_, ChainAnimation::DEFAULT_INTENSITY);
}

/**
 * @tc.name: ChainAnimation002
 * @tc.desc: Test SetChainAnimationOptions
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, ChainAnimation002, TestSize.Level1)
{
    constexpr float minSpace = 2.f;
    constexpr float maxSpace = 10.f;
    constexpr float conductivity = -5.f;
    constexpr float intensity = -5.f;
    ChainAnimationOptions options = {
        .minSpace = Dimension(minSpace),
        .maxSpace = Dimension(maxSpace),
        .conductivity = conductivity,
        .intensity = intensity,
        .edgeEffect = 0,
        .stiffness = DEFAULT_STIFFNESS,
        .damping = DEFAULT_DAMPING,
    };
    ListModelNG model = CreateList();
    model.SetSpace(Dimension(SPACE));
    model.SetChainAnimation(true);
    model.SetChainAnimationOptions(options);
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();

    /**
     * @tc.steps: step1. When minSpace < maxSpace.
     * @tc.expected: minSpace and maxSpace would be itself.
     */
    auto chainAnimation = pattern_->chainAnimation_;
    EXPECT_FLOAT_EQ(chainAnimation->minSpace_, minSpace);
    EXPECT_FLOAT_EQ(chainAnimation->maxSpace_, maxSpace);

    /**
     * @tc.steps: step2. When conductivity < 0, intensity < 0
     * @tc.expected: conductivity/intensity would be default value.
     */
    EXPECT_FLOAT_EQ(chainAnimation->conductivity_, ChainAnimation::DEFAULT_CONDUCTIVITY);
    EXPECT_FLOAT_EQ(chainAnimation->intensity_, ChainAnimation::DEFAULT_INTENSITY);

    /**
     * @tc.steps: step3. SetChainAnimationOptions again
     */
    pattern_->SetChainAnimationOptions(options);
    chainAnimation = pattern_->chainAnimation_;
    EXPECT_FLOAT_EQ(chainAnimation->minSpace_, minSpace);
    EXPECT_FLOAT_EQ(chainAnimation->maxSpace_, maxSpace);
    EXPECT_FLOAT_EQ(chainAnimation->conductivity_, ChainAnimation::DEFAULT_CONDUCTIVITY);
    EXPECT_FLOAT_EQ(chainAnimation->intensity_, ChainAnimation::DEFAULT_INTENSITY);
}

/**
 * @tc.name: ChainAnimation003
 * @tc.desc: Test SetChainAnimationOptions
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, ChainAnimation003, TestSize.Level1)
{
    constexpr float minSpace = 2.f;
    constexpr float maxSpace = 10.f;
    constexpr float conductivity = 0;
    constexpr float intensity = 0;
    ChainAnimationOptions options = {
        .minSpace = Dimension(minSpace),
        .maxSpace = Dimension(maxSpace),
        .conductivity = conductivity,
        .intensity = intensity,
        .edgeEffect = 0,
        .stiffness = DEFAULT_STIFFNESS,
        .damping = DEFAULT_DAMPING,
    };
    ListModelNG model = CreateList();
    model.SetSpace(Dimension(SPACE));
    model.SetChainAnimation(true);
    model.SetChainAnimationOptions(options);
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();

    /**
     * @tc.steps: step1. When conductivity == 0, intensity == 0
     * @tc.expected: conductivity/intensity would be itself.
     */
    auto chainAnimation = pattern_->chainAnimation_;
    EXPECT_FLOAT_EQ(chainAnimation->conductivity_, conductivity);
    EXPECT_FLOAT_EQ(chainAnimation->intensity_, intensity);

    /**
     * @tc.steps: step2. SetChainAnimationOptions again
     */
    pattern_->SetChainAnimationOptions(options);
    chainAnimation = pattern_->chainAnimation_;
    EXPECT_FLOAT_EQ(chainAnimation->conductivity_, conductivity);
    EXPECT_FLOAT_EQ(chainAnimation->intensity_, intensity);
}

/**
 * @tc.name: GetOrCreateController001
 * @tc.desc: Test GetOrCreateController
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, GetOrCreateController001, TestSize.Level1)
{
    ListModelNG model;
    model.Create();
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    auto controller = model.GetOrCreateController(AceType::RawPtr(frameNode));
    EXPECT_NE(controller, nullptr);
    controller = model.GetOrCreateController(AceType::RawPtr(frameNode));
    EXPECT_NE(controller, nullptr);
    CreateDone();
}

/**
 * @tc.name: ListItemCreate001
 * @tc.desc: Test ListItemModelNG Create
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, ListItemCreate001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ListItem without or with deepRenderFunc
     * @tc.expected: Created successful
     */
    CreateList();
    ListItemModelNG itemModel;
    itemModel.Create(nullptr, V2::ListItemStyle::NONE);
    ViewStackProcessor::GetInstance()->Pop();
    itemModel.Create([](int32_t) {}, V2::ListItemStyle::NONE);
    ViewStackProcessor::GetInstance()->Pop();
    CreateDone();
    EXPECT_EQ(frameNode_->GetTotalChildCount(), 2);
}

/**
 * @tc.name: ListMaintainVisibleContentPosition001
 * @tc.desc: Test maintain visible content position
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, ListMaintainVisibleContentPosition001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ListItem LazyForEach
     * @tc.expected: Created successful
     */
    ListModelNG model = CreateList();
    model.SetMaintainVisibleContentPosition(true);
    CreateListItems(10);
    CreateDone();

    /**
     * @tc.steps: step1. Current start index is 2, insert Item in 0.
     * @tc.expected: Current index is 3.
     */
    ScrollToIndex(2, false, ScrollAlign::START);
    pattern_->NotifyDataChange(0, 1);
    FlushUITasks();
    EXPECT_EQ(pattern_->startIndex_, 3);
    EXPECT_EQ(pattern_->currentOffset_, 300);

    /**
     * @tc.steps: step2. Current start index is 3, insert Item in 3.
     * @tc.expected: Current index is 4.
     */
    pattern_->NotifyDataChange(3, 1);
    FlushUITasks();
    EXPECT_EQ(pattern_->startIndex_, 4);
    EXPECT_EQ(pattern_->currentOffset_, 400);

    /**
     * @tc.steps: step3. Current start index is 4, delete Item in 1.
     * @tc.expected: Current index is 3.
     */
    pattern_->NotifyDataChange(1, -1);
    FlushUITasks();
    EXPECT_EQ(pattern_->startIndex_, 3);
    EXPECT_EQ(pattern_->currentOffset_, 300);

    /**
     * @tc.steps: step4. Current start index is 3, delete 3 Item in 1.
     * @tc.expected: Current index is 1.
     */
    pattern_->NotifyDataChange(1, -3);
    FlushUITasks();
    EXPECT_EQ(pattern_->startIndex_, 1);
    EXPECT_EQ(pattern_->currentOffset_, 100);

    /**
     * @tc.steps: step5. Current start index is 1, delete 1 Item in 2.
     * @tc.expected: Current index is 1.
     */
    pattern_->NotifyDataChange(2, -1);
    FlushUITasks();
    EXPECT_EQ(pattern_->startIndex_, 1);
    EXPECT_EQ(pattern_->currentOffset_, 100);

    /**
     * @tc.steps: step6. Current start index is 1, add Item in 2.
     * @tc.expected: Current index is 1.
     */
    pattern_->NotifyDataChange(2, 1);
    FlushUITasks();
    EXPECT_EQ(pattern_->startIndex_, 1);
    EXPECT_EQ(pattern_->currentOffset_, 100);
}

/**
 * @tc.name: ListMaintainVisibleContentPosition002
 * @tc.desc: Test Test maintain visible content position with lanes
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, ListMaintainVisibleContentPosition002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ListItem LazyForEach
     * @tc.expected: Created successful
     */
    ListModelNG model = CreateList();
    model.SetMaintainVisibleContentPosition(true);
    model.SetLanes(2);
    CreateListItems(20);
    CreateDone();

    /**
     * @tc.steps: step1. Current start index is 4, insert Item in 0.
     * @tc.expected: Current start index is 4.
     */
    ScrollToIndex(4, false, ScrollAlign::START);
    pattern_->NotifyDataChange(0, 1);
    FlushUITasks();
    EXPECT_EQ(pattern_->startIndex_, 4);
    EXPECT_EQ(pattern_->currentOffset_, 200);

    /**
     * @tc.steps: step2. Current start index is 4, insert 2 Item in 0.
     * @tc.expected: Current index is 6.
     */
    pattern_->NotifyDataChange(0, 2);
    FlushUITasks();
    EXPECT_EQ(pattern_->startIndex_, 6);
    EXPECT_EQ(pattern_->currentOffset_, 300);

    /**
     * @tc.steps: step3. Current start index is 6, delete Item in 0.
     * @tc.expected: Current index is 4.
     */
    pattern_->NotifyDataChange(0, -1);
    FlushUITasks();
    EXPECT_EQ(pattern_->startIndex_, 6);
    EXPECT_EQ(pattern_->currentOffset_, 300);

    /**
     * @tc.steps: step4. Current start index is 6, delete 2 Item in 0.
     * @tc.expected: Current index is 2.
     */
    pattern_->NotifyDataChange(0, -2);
    FlushUITasks();
    EXPECT_EQ(pattern_->startIndex_, 4);
    EXPECT_EQ(pattern_->currentOffset_, 200);

    /**
     * @tc.steps: step5. Current start index is 4, delete 2 Item in 4.
     * @tc.expected: Current index is 2.
     */
    pattern_->NotifyDataChange(4, -1);
    FlushUITasks();
    EXPECT_EQ(pattern_->startIndex_, 4);
    EXPECT_EQ(pattern_->currentOffset_, 200);

    /**
     * @tc.steps: step6. Current start index is 4, add Item in 2.
     * @tc.expected: Current index is 6.
     */
    pattern_->NotifyDataChange(4, 2);
    FlushUITasks();
    EXPECT_EQ(pattern_->startIndex_, 6);
    EXPECT_EQ(pattern_->currentOffset_, 300);
}

/**
 * @tc.name: ListMaintainVisibleContentPosition003
 * @tc.desc: Test Test maintain visible content position with ListItemGroup
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, ListMaintainVisibleContentPosition003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ListItem LazyForEach
     * @tc.expected: Created successful
     */
    ListModelNG model = CreateList();
    model.SetMaintainVisibleContentPosition(true);
    CreateListItemGroup();
    CreateListItems(10);
    CreateDone();

    /**
     * @tc.steps: step1. Current start index is 2, insert Item in 0.
     * @tc.expected: Current index is 3.
     */
    JumpToItemInGroup(0, 2, false, ScrollAlign::START);
    EXPECT_EQ(pattern_->currentOffset_, 200);
    auto groupNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(0));
    auto groupPattern = groupNode->GetPattern<ListItemGroupPattern>();
    groupPattern->NotifyDataChange(0, 1);
    FlushUITasks();
    EXPECT_EQ(groupPattern->itemDisplayStartIndex_, 3);
    EXPECT_EQ(pattern_->currentOffset_, 300);

    /**
     * @tc.steps: step2. Current start index is 3, insert Item in 3.
     * @tc.expected: Current index is 4.
     */
    groupPattern->NotifyDataChange(3, 1);
    FlushUITasks();
    EXPECT_EQ(groupPattern->itemDisplayStartIndex_, 4);
    EXPECT_EQ(pattern_->currentOffset_, 400);

    /**
     * @tc.steps: step3. Current start index is 4, delete Item in 1.
     * @tc.expected: Current index is 3.
     */
    groupPattern->NotifyDataChange(1, -1);
    FlushUITasks();
    EXPECT_EQ(groupPattern->itemDisplayStartIndex_, 3);
    EXPECT_EQ(pattern_->currentOffset_, 300);

    /**
     * @tc.steps: step4. Current start index is 3, delete 3 Item in 1.
     * @tc.expected: Current index is 1.
     */
    groupPattern->NotifyDataChange(1, -3);
    FlushUITasks();
    EXPECT_EQ(groupPattern->itemDisplayStartIndex_, 1);
    EXPECT_EQ(pattern_->currentOffset_, 100);

    /**
     * @tc.steps: step5. Current start index is 1, delete 1 Item in 2.
     * @tc.expected: Current index is 1.
     */
    groupPattern->NotifyDataChange(2, -1);
    FlushUITasks();
    EXPECT_EQ(groupPattern->itemDisplayStartIndex_, 1);
    EXPECT_EQ(pattern_->currentOffset_, 100);

    /**
     * @tc.steps: step6. Current start index is 1, add Item in 2.
     * @tc.expected: Current index is 1.
     */
    groupPattern->NotifyDataChange(2, 1);
    FlushUITasks();
    EXPECT_EQ(groupPattern->itemDisplayStartIndex_, 1);
    EXPECT_EQ(pattern_->currentOffset_, 100);
}

/**
 * @tc.name: ListMaintainVisibleContentPosition004
 * @tc.desc: Test Test maintain visible content position with ListItemGroup
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, ListMaintainVisibleContentPosition004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ListItem LazyForEach
     * @tc.expected: Created successful
     */
    ListModelNG model = CreateList();
    model.SetLanes(2);
    model.SetMaintainVisibleContentPosition(true);
    CreateListItemGroup();
    CreateListItems(20);
    CreateDone();

    /**
     * @tc.steps: step1. Current start index is 2, insert Item in 0.
     * @tc.expected: Current index is 3.
     */
    JumpToItemInGroup(0, 4, false, ScrollAlign::START);
    auto groupNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(0));
    auto groupPattern = groupNode->GetPattern<ListItemGroupPattern>();
    groupPattern->NotifyDataChange(0, 1);
    FlushUITasks();
    EXPECT_EQ(groupPattern->itemDisplayStartIndex_, 4);
    EXPECT_EQ(pattern_->currentOffset_, 200);

    /**
     * @tc.steps: step2. Current start index is 4, insert 2 Item in 0.
     * @tc.expected: Current index is 6.
     */
    groupPattern->NotifyDataChange(0, 2);
    FlushUITasks();
    EXPECT_EQ(groupPattern->itemDisplayStartIndex_, 6);
    EXPECT_EQ(pattern_->currentOffset_, 300);

    /**
     * @tc.steps: step3. Current start index is 6, delete Item in 0.
     * @tc.expected: Current index is 4.
     */
    groupPattern->NotifyDataChange(0, -1);
    FlushUITasks();
    EXPECT_EQ(groupPattern->itemDisplayStartIndex_, 6);
    EXPECT_EQ(pattern_->currentOffset_, 300);

    /**
     * @tc.steps: step4. Current start index is 6, delete 2 Item in 0.
     * @tc.expected: Current index is 2.
     */
    groupPattern->NotifyDataChange(0, -2);
    FlushUITasks();
    EXPECT_EQ(groupPattern->itemDisplayStartIndex_, 4);
    EXPECT_EQ(pattern_->currentOffset_, 200);

    /**
     * @tc.steps: step5. Current start index is 4, delete 2 Item in 4.
     * @tc.expected: Current index is 2.
     */
    groupPattern->NotifyDataChange(4, -1);
    FlushUITasks();
    EXPECT_EQ(groupPattern->itemDisplayStartIndex_, 4);
    EXPECT_EQ(pattern_->currentOffset_, 200);

    /**
     * @tc.steps: step6. Current start index is 4, add Item in 4.
     * @tc.expected: Current index is 4.
     */
    groupPattern->NotifyDataChange(4, 2);
    FlushUITasks();
    EXPECT_EQ(groupPattern->itemDisplayStartIndex_, 6);
    EXPECT_EQ(pattern_->currentOffset_, 300);
}

/**
 * @tc.name: ListMaintainVisibleContentPosition005
 * @tc.desc: Test Test maintain visible content position with ListItemGroup
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, ListMaintainVisibleContentPosition005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ListItem LazyForEach
     * @tc.expected: Created successful
     */
    ListModelNG model = CreateList();
    model.SetLanes(2);
    model.SetMaintainVisibleContentPosition(true);
    CreateListItemGroups(10);
    CreateDone();

    /**
     * @tc.steps: step1. Current start index is 2, insert Item in 0.
     * @tc.expected: Current index is 3.
     */
    ScrollToIndex(2, false, ScrollAlign::START);
    pattern_->NotifyDataChange(0, 1);
    FlushUITasks();
    EXPECT_EQ(pattern_->startIndex_, 3);
    EXPECT_EQ(pattern_->currentOffset_, 300);

    /**
     * @tc.steps: step2. Current start index is 3, insert Item in 3.
     * @tc.expected: Current index is 4.
     */
    pattern_->NotifyDataChange(3, 1);
    FlushUITasks();
    EXPECT_EQ(pattern_->startIndex_, 4);
    EXPECT_EQ(pattern_->currentOffset_, 400);

    /**
     * @tc.steps: step3. Current start index is 4, delete Item in 1.
     * @tc.expected: Current index is 3.
     */
    pattern_->NotifyDataChange(1, -1);
    FlushUITasks();
    EXPECT_EQ(pattern_->startIndex_, 3);
    EXPECT_EQ(pattern_->currentOffset_, 300);

    /**
     * @tc.steps: step4. Current start index is 3, delete 3 Item in 1.
     * @tc.expected: Current index is 1.
     */
    pattern_->NotifyDataChange(1, -3);
    FlushUITasks();
    EXPECT_EQ(pattern_->startIndex_, 1);
    EXPECT_EQ(pattern_->currentOffset_, 100);

    /**
     * @tc.steps: step5. Current start index is 1, delete 1 Item in 2.
     * @tc.expected: Current index is 1.
     */
    pattern_->NotifyDataChange(2, -1);
    FlushUITasks();
    EXPECT_EQ(pattern_->startIndex_, 1);
    EXPECT_EQ(pattern_->currentOffset_, 100);

    /**
     * @tc.steps: step6. Current start index is 1, add Item in 2.
     * @tc.expected: Current index is 1.
     */
    pattern_->NotifyDataChange(2, 1);
    FlushUITasks();
    EXPECT_EQ(pattern_->startIndex_, 1);
    EXPECT_EQ(pattern_->currentOffset_, 100);
}

/**
 * @tc.name: ListMaintainVisibleContentPosition006
 * @tc.desc: Test Test maintain visible content position with ListItemGroup and space
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, ListMaintainVisibleContentPosition006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ListItem LazyForEach
     * @tc.expected: Created successful
     */
    ListModelNG model = CreateList();
    model.SetMaintainVisibleContentPosition(true);
    auto groupModel = CreateListItemGroup();
    groupModel.SetSpace(Dimension(10));
    CreateListItems(10);
    CreateDone();

    /**
     * @tc.steps: step1. Current start index is 0, insert 2 Item in 0.
     * @tc.expected: Current index is 2, currentOffset = 220
     */
    auto groupNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(0));
    auto groupPattern = groupNode->GetPattern<ListItemGroupPattern>();
    groupPattern->NotifyDataChange(0, 2);
    FlushUITasks();
    EXPECT_EQ(groupPattern->itemDisplayStartIndex_, 2);
    EXPECT_EQ(pattern_->currentOffset_, 220);

    /**
     * @tc.steps: step2. Current start index is 2, insert Item in 1 two times.
     * @tc.expected: Current index is 1, currentOffset = 110
     */
    groupPattern->NotifyDataChange(1, -1);
    groupPattern->NotifyDataChange(1, -1);
    FlushUITasks();
    EXPECT_EQ(groupPattern->itemDisplayStartIndex_, 1);
    EXPECT_EQ(pattern_->currentOffset_, 110);
    EXPECT_EQ(groupPattern->layoutedItemInfo_.value().startIndex, 1);

    /**
     * @tc.steps: step2. Current start index is 0, insert Item in 0 two times.
     * @tc.expected: Current index is 0, currentOffset = 0
     */
    groupPattern->NotifyDataChange(0, -1);
    groupPattern->NotifyDataChange(0, -1);
    FlushUITasks();
    EXPECT_EQ(groupPattern->itemDisplayStartIndex_, 0);
    EXPECT_EQ(pattern_->currentOffset_, 0);
    EXPECT_EQ(groupPattern->layoutedItemInfo_.value().startIndex, 0);
}

/**
 * @tc.name: ListMaintainVisibleContentPosition007
 * @tc.desc: Test Test maintain visible content position with ListItemGroup with header/footer
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, ListMaintainVisibleContentPosition007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ListItem LazyForEach
     * @tc.expected: Created successful
     */
    ListModelNG model = CreateList();
    model.SetMaintainVisibleContentPosition(true);
    auto groupModel = CreateListItemGroup();
    groupModel.SetSpace(Dimension(10));
    auto header = GetRowOrColBuilder(FILL_LENGTH, Dimension(GROUP_HEADER_LEN));
    groupModel.SetHeader(std::move(header));
    auto footer = GetRowOrColBuilder(FILL_LENGTH, Dimension(GROUP_HEADER_LEN));
    groupModel.SetFooter(std::move(footer));
    CreateListItems(10);
    CreateDone();

    /**
     * @tc.steps: step1. Current start index is 0, insert 1 Item in 0.
     * @tc.expected: Current index is 0, currentOffset = 0
     */
    auto groupNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(0));
    auto groupPattern = groupNode->GetPattern<ListItemGroupPattern>();
    groupPattern->NotifyDataChange(2, 1);
    FlushUITasks();
    EXPECT_EQ(groupPattern->itemDisplayStartIndex_, 0);
    EXPECT_EQ(pattern_->currentOffset_, 0);

    /**
     * @tc.steps: step2. Scroll to listItem1, insert 1 Item in 0.
     * @tc.expected: Current index is 2, currentOffset = 260
     */
    UpdateCurrentOffset(-160);
    EXPECT_EQ(pattern_->currentOffset_, 160);
    groupPattern->NotifyDataChange(2, 1);
    FlushUITasks();
    EXPECT_EQ(groupPattern->itemDisplayStartIndex_, 2);
    EXPECT_EQ(pattern_->currentOffset_, 260);

    /**
     * @tc.steps: step3. Scroll to listItem1, delete 1 Item in 0.
     * @tc.expected: Current index is 1, currentOffset = 260
     */
    groupPattern->NotifyDataChange(2, -1);
    FlushUITasks();
    EXPECT_EQ(groupPattern->itemDisplayStartIndex_, 1);
    EXPECT_EQ(pattern_->currentOffset_, 160);
}

/**
 * @tc.name: ListMaintainVisibleContentPosition008
 * @tc.desc: Test Test maintain visible content position with ListItemGroup with header/footer, delete all item in Group
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, ListMaintainVisibleContentPosition008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ListItem LazyForEach
     * @tc.expected: Created successful
     */
    ListModelNG model = CreateList();
    model.SetMaintainVisibleContentPosition(true);
    for (int32_t i = 0; i < 4; i++) {
        auto groupModel = CreateListItemGroup();
        auto header = GetRowOrColBuilder(FILL_LENGTH, Dimension(GROUP_HEADER_LEN));
        groupModel.SetHeader(std::move(header));
        auto footer = GetRowOrColBuilder(FILL_LENGTH, Dimension(GROUP_HEADER_LEN));
        groupModel.SetFooter(std::move(footer));
        CreateListItems(1);
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
    CreateDone();

    /**
     * @tc.steps: step1. Scroll To first Group footer.
     * @tc.expected: Current offset is 175
     */
    UpdateCurrentOffset(-175);
    EXPECT_EQ(pattern_->currentOffset_, 175);

    /**
     * @tc.steps: step2. Current start index is 0, insert 1 Item in 0.
     * @tc.expected: Current index is 0, currentOffset = 0
     */
    auto groupNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(0));
    auto groupPattern = groupNode->GetPattern<ListItemGroupPattern>();
    groupPattern->NotifyDataChange(2, -1);
    groupNode->RemoveChildAtIndex(2);
    FlushUITasks();
    EXPECT_EQ(pattern_->currentOffset_, 75);
}
} // namespace OHOS::Ace::NG
