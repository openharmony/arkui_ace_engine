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

namespace OHOS::Ace::NG {

namespace {} // namespace

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
    Create([](ListModelNG model) {
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
    });

    /**
     * @tc.steps: step1. Call ToJsonValue()
     * @tc.expected: The json value is correct
     */
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json);
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
    layoutProperty_->UpdateListDirection(Axis::HORIZONTAL);
    layoutProperty_->UpdateListItemAlign(V2::ListItemAlign::END);
    layoutProperty_->UpdateStickyStyle(V2::StickyStyle::FOOTER);
    layoutProperty_->UpdateScrollSnapAlign(V2::ScrollSnapAlign::CENTER);
    layoutProperty_->UpdateDivider(ITEM_DIVIDER);
    json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json);
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
    layoutProperty_->UpdateListItemAlign(V2::ListItemAlign::START);
    layoutProperty_->UpdateStickyStyle(V2::StickyStyle::BOTH);
    layoutProperty_->UpdateScrollSnapAlign(V2::ScrollSnapAlign::END);
    json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json);
    EXPECT_EQ(json->GetString("alignListItem"), "ListItemAlign.Start");
    EXPECT_EQ(json->GetString("sticky"), "StickyStyle.Header | StickyStyle.Footer");
    EXPECT_EQ(json->GetString("scrollSnapAlign"), "ScrollSnapAlign.END");

    /**
     * @tc.steps: step3. Change some property, Call ToJsonValue()
     * @tc.expected: The json value is changed
     */
    layoutProperty_->UpdateStickyStyle(V2::StickyStyle::NONE);
    layoutProperty_->UpdateScrollSnapAlign(V2::ScrollSnapAlign::NONE);
    json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json);
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
 * @tc.name: ListItemLayoutProperty001
 * @tc.desc: Test ListItem layout properties.
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, ListItemLayoutProperty001, TestSize.Level1)
{
    CreateWithItem([](ListModelNG model) {});
    auto layoutProperty = GetChildLayoutProperty<ListItemLayoutProperty>(frameNode_, 0);

    /**
     * @tc.steps: step1. Call ToJsonValue()
     * @tc.expected: The json value is correct
     */
    auto json = JsonUtil::Create(true);
    layoutProperty->ToJsonValue(json);
    EXPECT_EQ(static_cast<V2::StickyMode>(json->GetInt("sticky")), V2::StickyMode::NONE);
    EXPECT_FALSE(json->GetBool("editable"));
    EXPECT_EQ(Dimension::FromString(json->GetString("startDeleteAreaDistance")), Dimension(0, DimensionUnit::VP));
    EXPECT_EQ(Dimension::FromString(json->GetString("endDeleteAreaDistance")), Dimension(0, DimensionUnit::VP));

    /**
     * @tc.steps: step2. Change some property, Call ToJsonValue()
     * @tc.expected: The json value is correct
     */
    layoutProperty->UpdateStickyMode(V2::StickyMode::NORMAL);
    layoutProperty->UpdateEditMode(V2::EditMode::NONE);
    layoutProperty->UpdateEdgeEffect(V2::SwipeEdgeEffect::Spring);
    json = JsonUtil::Create(true);
    layoutProperty->ToJsonValue(json);
    EXPECT_EQ(json->GetString("sticky"), "Sticky.Normal");
    EXPECT_EQ(json->GetString("editable"), "EditMode.None");
    auto swipeAction = json->GetObject("swipeAction");
    EXPECT_EQ(static_cast<V2::SwipeEdgeEffect>(swipeAction->GetInt("edgeEffect")), V2::SwipeEdgeEffect::Spring);

    /**
     * @tc.steps: step3. Change some property, Call ToJsonValue()
     * @tc.expected: The json value is correct
     */
    layoutProperty->UpdateStickyMode(V2::StickyMode::OPACITY);
    layoutProperty->UpdateEditMode(V2::EditMode::MOVABLE);
    layoutProperty->UpdateEdgeEffect(V2::SwipeEdgeEffect::None);
    json = JsonUtil::Create(true);
    layoutProperty->ToJsonValue(json);
    EXPECT_EQ(json->GetString("sticky"), "Sticky.Opacity");
    EXPECT_EQ(json->GetString("editable"), "EditMode.Movable");
    swipeAction = json->GetObject("swipeAction");
    EXPECT_EQ(swipeAction->GetString("edgeEffect"), "SwipeEdgeEffect.Node");

    /**
     * @tc.steps: step4. Change some property, Call ToJsonValue()
     * @tc.expected: The json value is correct
     */
    layoutProperty->UpdateEditMode(V2::EditMode::DELETABLE);
    json = JsonUtil::Create(true);
    layoutProperty->ToJsonValue(json);
    EXPECT_EQ(json->GetString("editable"), "EditMode.Deletable");

    /**
     * @tc.steps: step5. Change some property, Call ToJsonValue()
     * @tc.expected: The json value is correct
     */
    layoutProperty->UpdateEditMode(V2::EditMode::DELETABLE | V2::EditMode::MOVABLE);
    json = JsonUtil::Create(true);
    layoutProperty->ToJsonValue(json);
    EXPECT_TRUE(json->GetBool("editable"));
}

/**
 * @tc.name: AttrSpaceDivider001
 * @tc.desc: Test property about space/divider with Axis::VERTICAL
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, AttrSpaceDivider001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set space
     */
    CreateWithItem([](ListModelNG model) { model.SetSpace(Dimension(SPACE)); });
    EXPECT_TRUE(VerifyPosition(frameNode_, VIEW_LINE_NUMBER, DEFAULT_LANES, SPACE, DEFAULT_STARTOFFSET));

    /**
     * @tc.steps: step2. Set divider
     */
    CreateWithItem([](ListModelNG model) { model.SetDivider(ITEM_DIVIDER); });
    EXPECT_TRUE(VerifyPosition(frameNode_, VIEW_LINE_NUMBER, DEFAULT_LANES, STROKE_WIDTH, DEFAULT_STARTOFFSET));

    /**
     * @tc.steps: step3. Set space less than divider's strokeWidth
     * @tc.expected: space was going to be strokeWidth
     */
    CreateWithItem([](ListModelNG model) {
        model.SetSpace(Dimension(STROKE_WIDTH - 1.f));
        model.SetDivider(ITEM_DIVIDER);
    });
    EXPECT_TRUE(VerifyPosition(frameNode_, VIEW_LINE_NUMBER, DEFAULT_LANES, STROKE_WIDTH, DEFAULT_STARTOFFSET));
}

/**
 * @tc.name: AttrSpaceDivider002
 * @tc.desc: Test property about space/divider with Axis::HORIZONTAL
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, AttrSpaceDivider002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set space
     */
    Create([](ListModelNG model) {
        model.SetListDirection(Axis::HORIZONTAL);
        model.SetSpace(Dimension(SPACE));
        CreateItem(TOTAL_LINE_NUMBER, Axis::HORIZONTAL);
    });
    EXPECT_TRUE(VerifyPosition(frameNode_, VIEW_LINE_NUMBER - 1, DEFAULT_LANES, SPACE, DEFAULT_STARTOFFSET));

    /**
     * @tc.steps: step2. Set divider
     */
    Create([](ListModelNG model) {
        model.SetListDirection(Axis::HORIZONTAL);
        model.SetDivider(ITEM_DIVIDER);
        CreateItem(TOTAL_LINE_NUMBER, Axis::HORIZONTAL);
    });
    EXPECT_TRUE(VerifyPosition(frameNode_, VIEW_LINE_NUMBER, DEFAULT_LANES, STROKE_WIDTH, DEFAULT_STARTOFFSET));

    /**
     * @tc.steps: step3. Set space less than divider's strokeWidth
     * @tc.expected: space was going to be strokeWidth
     */
    Create([](ListModelNG model) {
        model.SetListDirection(Axis::HORIZONTAL);
        model.SetSpace(Dimension(STROKE_WIDTH - 1.f));
        model.SetDivider(ITEM_DIVIDER);
        CreateItem(TOTAL_LINE_NUMBER, Axis::HORIZONTAL);
    });
    EXPECT_TRUE(VerifyPosition(frameNode_, VIEW_LINE_NUMBER, DEFAULT_LANES, STROKE_WIDTH, DEFAULT_STARTOFFSET));
}

/**
 * @tc.name: AttrSpaceDivider003
 * @tc.desc: Test property about space/divider with special value
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, AttrSpaceDivider003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set space to LIST_HEIGHT
     * @tc.expected: space was going to be zero
     */
    CreateWithItem([](ListModelNG model) { model.SetSpace(Dimension(LIST_HEIGHT)); });
    EXPECT_TRUE(VerifyPosition(frameNode_, VIEW_LINE_NUMBER, DEFAULT_LANES, DEFAULT_SPACE, DEFAULT_STARTOFFSET));

    /**
     * @tc.steps: step2. Set strokeWidth to LIST_HEIGHT
     * @tc.expected: strokeWidth was going to be zero
     */
    auto divider = ITEM_DIVIDER;
    divider.strokeWidth = Dimension(LIST_HEIGHT);
    CreateWithItem([divider](ListModelNG model) { model.SetDivider(divider); });
    EXPECT_TRUE(VerifyPosition(frameNode_, VIEW_LINE_NUMBER, DEFAULT_LANES, DEFAULT_SPACE, DEFAULT_STARTOFFSET));
}

/**
 * @tc.name: AttrInitIndex001
 * @tc.desc: Test property about initialIndex with Axis::VERTICAL
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, AttrInitIndex001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set initIndex to 1
     * @tc.expected: List layout starting from initialIndex
     */
    CreateWithItem([](ListModelNG model) { model.SetInitialIndex(1); });
    EXPECT_TRUE(VerifyPosition(frameNode_, VIEW_LINE_NUMBER, DEFAULT_LANES, DEFAULT_SPACE, ITEM_HEIGHT));

    /**
     * @tc.steps: step2. Total ListItem size less than viewport
     * @tc.expected: List layout starting from first ListItem
     */
    Create([](ListModelNG model) {
        model.SetInitialIndex(1);
        CreateItem(5);
    });
    EXPECT_TRUE(VerifyPosition(frameNode_, 5, DEFAULT_LANES, DEFAULT_SPACE, DEFAULT_STARTOFFSET));

    /**
     * @tc.steps: step3. The total size of ListItems after initialIndex is less than viewport
     * @tc.expected: ListItem bottom to viewport
     */
    CreateWithItem([](ListModelNG model) { model.SetInitialIndex(5); });
    EXPECT_TRUE(VerifyPosition(frameNode_, VIEW_LINE_NUMBER, DEFAULT_LANES, DEFAULT_SPACE, ITEM_HEIGHT * 2));

    /**
     * @tc.steps: step4. initialIndex out of range
     * @tc.expected: ignore initialIndex
     */
    CreateWithItem([](ListModelNG model) { model.SetInitialIndex(100); });
    EXPECT_TRUE(VerifyPosition(frameNode_, VIEW_LINE_NUMBER, DEFAULT_LANES, DEFAULT_SPACE, DEFAULT_STARTOFFSET));

    /**
     * @tc.steps: step5. initialIndex is not an integer multiple of the lanes
     * @tc.expected: List layout starting from an index integer multiple of the lanes
     */
    Create([](ListModelNG model) {
        model.SetInitialIndex(3);
        model.SetLanes(2);
        CreateItem(20);
    });
    EXPECT_TRUE(VerifyPosition(frameNode_, 16, 2, DEFAULT_SPACE, ITEM_HEIGHT));
}

/**
 * @tc.name: AttrInitIndex002
 * @tc.desc: Test property about initialIndex with Axis::HORIZONTAL
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, AttrInitIndex002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set initIndex to 1
     * @tc.expected: List layout starting from initialIndex
     */
    Create([](ListModelNG model) {
        model.SetListDirection(Axis::HORIZONTAL);
        model.SetInitialIndex(1);
        CreateItem(TOTAL_LINE_NUMBER, Axis::HORIZONTAL);
    });
    EXPECT_TRUE(VerifyPosition(frameNode_, VIEW_LINE_NUMBER, DEFAULT_LANES, DEFAULT_SPACE, ITEM_WIDTH));

    /**
     * @tc.steps: step2. Total ListItem size less than viewport
     * @tc.expected: List layout starting from first ListItem
     */
    Create([](ListModelNG model) {
        model.SetListDirection(Axis::HORIZONTAL);
        model.SetInitialIndex(1);
        CreateItem(5, Axis::HORIZONTAL);
    });
    EXPECT_TRUE(VerifyPosition(frameNode_, 5, DEFAULT_LANES, DEFAULT_SPACE, DEFAULT_STARTOFFSET));

    /**
     * @tc.steps: step3. The total size of ListItems after initialIndex is less than viewport
     * @tc.expected: ListItem bottom to viewport
     */
    Create([](ListModelNG model) {
        model.SetListDirection(Axis::HORIZONTAL);
        model.SetInitialIndex(5);
        CreateItem(TOTAL_LINE_NUMBER, Axis::HORIZONTAL);
    });
    EXPECT_TRUE(VerifyPosition(frameNode_, VIEW_LINE_NUMBER, DEFAULT_LANES, DEFAULT_SPACE, ITEM_WIDTH * 2));

    /**
     * @tc.steps: step4. initialIndex out of range
     * @tc.expected: ignore initialIndex
     */
    Create([](ListModelNG model) {
        model.SetListDirection(Axis::HORIZONTAL);
        model.SetInitialIndex(100);
        CreateItem(TOTAL_LINE_NUMBER, Axis::HORIZONTAL);
    });
    EXPECT_TRUE(VerifyPosition(frameNode_, VIEW_LINE_NUMBER, DEFAULT_LANES, DEFAULT_SPACE, DEFAULT_STARTOFFSET));

    /**
     * @tc.steps: step5. initialIndex is not an integer multiple of the lanes
     * @tc.expected: List layout starting from an index integer multiple of the lanes
     */
    Create([](ListModelNG model) {
        model.SetListDirection(Axis::HORIZONTAL);
        model.SetInitialIndex(3);
        model.SetLanes(2);
        CreateItem(20, Axis::HORIZONTAL);
    });
    EXPECT_TRUE(VerifyPosition(frameNode_, 16, 2, DEFAULT_SPACE, ITEM_WIDTH));
}

/**
 * @tc.name: AttrScrollBar001
 * @tc.desc: Test property about scrollBar
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, AttrScrollBar001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set scrollBar
     */
    CreateWithItem([](ListModelNG model) { model.SetScrollBar(DisplayMode::ON); });
    EXPECT_EQ(pattern_->GetScrollBar()->GetDisplayMode(), DisplayMode::ON);

    /**
     * @tc.steps: step1. Set scrollBar, set api version >= 10
     * @tc.expected: the default value is auto
     */
    MockPipelineContext::pipeline_->SetMinPlatformVersion(PLATFORM_VERSION_TEN);
    CreateWithItem([](ListModelNG model) {});
    EXPECT_EQ(pattern_->GetScrollBar()->GetDisplayMode(), DisplayMode::AUTO);
}

/**
 * @tc.name: AttrLanes001
 * @tc.desc: Test property about lanes with VERTICAL
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, AttrLanes001, TestSize.Level1)
{
    Create([](ListModelNG model) {
        model.SetLanes(2);
        CreateItem(19);
    });
    EXPECT_TRUE(VerifyPosition(frameNode_, 16, 2, DEFAULT_SPACE, DEFAULT_STARTOFFSET));
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM);
    EXPECT_TRUE(VerifyPosition(frameNode_, 15, 2, DEFAULT_SPACE, ITEM_HEIGHT * 2));
}

/**
 * @tc.name: AttrLanes002
 * @tc.desc: Test property about lanes with HORIZONTAL
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, AttrLanes002, TestSize.Level1)
{
    Create([](ListModelNG model) {
        model.SetListDirection(Axis::HORIZONTAL);
        model.SetLanes(2);
        CreateItem(19, Axis::HORIZONTAL);
    });
    EXPECT_TRUE(VerifyPosition(frameNode_, 16, 2, DEFAULT_SPACE, DEFAULT_STARTOFFSET));
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM);
    EXPECT_TRUE(VerifyPosition(frameNode_, 15, 2, DEFAULT_SPACE, ITEM_WIDTH * 2));
}

/**
 * @tc.name: AttrLanes003
 * @tc.desc: Test LayoutProperty about minLaneLength/maxLaneLength with VERTICAL
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, AttrLanes003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. SetLaneMinLength half of LIST_WIDTH
     * @tc.expected: List would has 2 lanes
     */
    Create([](ListModelNG model) {
        model.SetLaneMinLength(Dimension(LIST_WIDTH / 2 - 1));
        model.SetLaneMaxLength(Dimension(LIST_WIDTH));
        CreateItem(19);
    });
    EXPECT_TRUE(VerifyPosition(frameNode_, 16, 2, DEFAULT_SPACE, DEFAULT_STARTOFFSET));
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM);
    EXPECT_TRUE(VerifyPosition(frameNode_, 15, 2, DEFAULT_SPACE, ITEM_HEIGHT * 2));

    /**
     * @tc.steps: step2. Check ListItem width.
     * @tc.expected: ListItem width would self-adaption.
     */
    for (int32_t index = 0; index < 15; index++) {
        EXPECT_FLOAT_EQ(GetChildRect(frameNode_, index).Width(), LIST_WIDTH / 2);
    }
}

/**
 * @tc.name: AttrLanes004
 * @tc.desc: Test LayoutProperty about minLaneLength/maxLaneLength with HORIZONTAL
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, AttrLanes004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. SetLaneMinLength half of LIST_HEIGHT
     * @tc.expected: List would has 2 lanes
     */
    Create([](ListModelNG model) {
        model.SetListDirection(Axis::HORIZONTAL);
        model.SetLaneMinLength(Dimension(LIST_HEIGHT / 2 - 1));
        model.SetLaneMaxLength(Dimension(LIST_HEIGHT));
        CreateItem(19, Axis::HORIZONTAL);
    });
    EXPECT_TRUE(VerifyPosition(frameNode_, 16, 2, DEFAULT_SPACE, DEFAULT_STARTOFFSET));
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM);
    EXPECT_TRUE(VerifyPosition(frameNode_, 15, 2, DEFAULT_SPACE, ITEM_WIDTH * 2));

    /**
     * @tc.steps: step2. Check ListItem height.
     * @tc.expected: ListItem height would self-adaption.
     */
    for (int32_t index = 0; index < 15; index++) {
        EXPECT_FLOAT_EQ(GetChildRect(frameNode_, index).Height(), LIST_HEIGHT / 2);
    }
}

/**
 * @tc.name: AttrLanes005
 * @tc.desc: Test LayoutProperty about minLaneLength, maxLaneLength,
 * when maxLaneLength less than minLaneLength, use minLaneLength
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, AttrLanes005, TestSize.Level1)
{
    const float minLaneLength = LIST_WIDTH / 2 - 1;
    Create([minLaneLength](ListModelNG model) {
        model.SetLaneMinLength(Dimension(minLaneLength));
        model.SetLaneMaxLength(Dimension(minLaneLength - 1));
        CreateItem(19);
    });
    EXPECT_TRUE(VerifyPosition(frameNode_, 16, 2, DEFAULT_SPACE, DEFAULT_STARTOFFSET));

    /**
     * @tc.steps: step1. Check ListItem width.
     * @tc.expected: ListItem width would be minLaneLength.
     */
    for (int32_t index = 0; index < 16; index++) {
        EXPECT_FLOAT_EQ(GetChildRect(frameNode_, index).Width(), minLaneLength);
    }
}

/**
 * @tc.name: AttrLanes006
 * @tc.desc: Test LayoutProperty about laneGutter with VERTICAL
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, AttrLanes006, TestSize.Level1)
{
    const float laneGutter = 16.f;
    const int32_t lanes = 2;
    CreateWithItem([lanes, laneGutter](ListModelNG model) {
        model.SetLanes(lanes);
        model.SetLaneGutter(Dimension(laneGutter));
    });
    float itemWidth = (LIST_WIDTH - laneGutter * (lanes - 1)) / lanes;
    for (int32_t index = 0; index < VIEW_LINE_NUMBER; index++) {
        RectF expectRect = RectF((itemWidth + laneGutter) * (index % lanes), ITEM_HEIGHT * std::floor(index / lanes),
            itemWidth, ITEM_HEIGHT);
        EXPECT_TRUE(IsEqual(GetChildRect(frameNode_, index), expectRect));
    }
}

/**
 * @tc.name: AttrLanes007
 * @tc.desc: Test LayoutProperty about laneGutter with HORIZONTAL
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, AttrLanes007, TestSize.Level1)
{
    const float laneGutter = 16.f;
    const int32_t lanes = 2;
    Create([lanes, laneGutter](ListModelNG model) {
        model.SetListDirection(Axis::HORIZONTAL);
        model.SetLanes(lanes);
        model.SetLaneGutter(Dimension(laneGutter));
        CreateItem(TOTAL_LINE_NUMBER, Axis::HORIZONTAL);
    });
    float itemHeight = (LIST_HEIGHT - laneGutter * (lanes - 1)) / lanes;
    for (int32_t index = 0; index < VIEW_LINE_NUMBER; index++) {
        RectF expectRect = RectF(ITEM_WIDTH * std::floor(index / lanes), (itemHeight + laneGutter) * (index % lanes),
            ITEM_WIDTH, itemHeight);
        EXPECT_TRUE(IsEqual(GetChildRect(frameNode_, index), expectRect));
    }
}

/**
 * @tc.name: AttrLanes008
 * @tc.desc: Test LaneGutter
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, AttrLanes008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create List and Set lanes
     */
    int32_t itemNumber = 20;
    int32_t lanes = 5;
    Dimension laneGutter = Dimension::FromString("10%");
    Create([=](ListModelNG model) {
        CreateItem(itemNumber);
        model.SetScrollBar(DisplayMode::OFF);
        model.SetLanes(lanes);
        model.SetLaneGutter(laneGutter);
    });
    EXPECT_TRUE(VerifyPosition(frameNode_, itemNumber, 5, DEFAULT_SPACE, DEFAULT_STARTOFFSET));

    double gutter = laneGutter.ConvertToPxWithSize(LIST_WIDTH);
    double itemWidth = (FILL_LENGTH.Value() - laneGutter.Value() * (lanes - 1)) * LIST_WIDTH / lanes;
    for (int32_t i = 0; i < itemNumber; ++i) {
        int32_t x = i % lanes;
        int32_t y = i / lanes;
        EXPECT_TRUE(
            IsEqual(pattern_->GetItemRect(i), Rect(x * (gutter + itemWidth), y * ITEM_HEIGHT, itemWidth, ITEM_HEIGHT)));
    }
}

/**
 * @tc.name: AttrAlignListItem001
 * @tc.desc: Test LayoutProperty about alignListItem with VERTICAL
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, AttrAlignListItem001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set item width smaller than LIST_WIDTH
     * @tc.expected: the item default is align to start
     */
    constexpr float itemWidth = 400.f;
    Create([itemWidth](ListModelNG model) {
        for (int32_t index = 0; index < TOTAL_LINE_NUMBER; index++) {
            ListItemModelNG itemModel;
            itemModel.Create();
            ViewAbstract::SetWidth(CalcLength(itemWidth));
            ViewStackProcessor::GetInstance()->Pop();
        }
    });
    for (int32_t index = 0; index < TOTAL_LINE_NUMBER; index++) {
        EXPECT_EQ(GetChildRect(frameNode_, index).GetX(), 0);
    }

    /**
     * @tc.steps: step2. Set ListItemAlign::CENTER
     * @tc.expected: the item is align to center
     */
    layoutProperty_->UpdateListItemAlign(V2::ListItemAlign::CENTER);
    FlushLayoutTask(frameNode_);
    for (int32_t index = 0; index < TOTAL_LINE_NUMBER; index++) {
        EXPECT_EQ(GetChildRect(frameNode_, index).GetX(), (LIST_WIDTH - itemWidth) / 2);
    }

    /**
     * @tc.steps: step3. Set ListItemAlign::END
     * @tc.expected: the item is align to end
     */
    layoutProperty_->UpdateListItemAlign(V2::ListItemAlign::END);
    FlushLayoutTask(frameNode_);
    for (int32_t index = 0; index < TOTAL_LINE_NUMBER; index++) {
        EXPECT_EQ(GetChildRect(frameNode_, index).GetX(), LIST_WIDTH - itemWidth);
    }
}

/**
 * @tc.name: AttrAlignListItem002
 * @tc.desc: Test LayoutProperty about alignListItem HORIZONTAL
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, AttrAlignListItem002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set item width smaller than LIST_WIDTH
     * @tc.expected: the item default is align to start
     */
    constexpr float itemHeight = 400.f;
    Create([itemHeight](ListModelNG model) {
        model.SetListDirection(Axis::HORIZONTAL);
        for (int32_t index = 0; index < TOTAL_LINE_NUMBER; index++) {
            ListItemModelNG itemModel;
            itemModel.Create();
            ViewAbstract::SetHeight(CalcLength(itemHeight));
            ViewStackProcessor::GetInstance()->Pop();
        }
    });
    for (int32_t index = 0; index < TOTAL_LINE_NUMBER; index++) {
        EXPECT_EQ(GetChildRect(frameNode_, index).GetY(), 0);
    }

    /**
     * @tc.steps: step2. Set ListItemAlign::CENTER
     * @tc.expected: the item is align to center
     */
    layoutProperty_->UpdateListItemAlign(V2::ListItemAlign::CENTER);
    FlushLayoutTask(frameNode_);
    for (int32_t index = 0; index < TOTAL_LINE_NUMBER; index++) {
        EXPECT_EQ(GetChildRect(frameNode_, index).GetY(), (LIST_HEIGHT - itemHeight) / 2);
    }

    /**
     * @tc.steps: step3. Set ListItemAlign::END
     * @tc.expected: the item is align to end
     */
    layoutProperty_->UpdateListItemAlign(V2::ListItemAlign::END);
    FlushLayoutTask(frameNode_);
    for (int32_t index = 0; index < TOTAL_LINE_NUMBER; index++) {
        EXPECT_EQ(GetChildRect(frameNode_, index).GetY(), LIST_HEIGHT - itemHeight);
    }
}

/**
 * @tc.name: AttrScrollSnapAlign001
 * @tc.desc: Test LayoutProperty about ScrollSnapAlign with VERTICAL
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, AttrScrollSnapAlign001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. V2::ScrollSnapAlign::START
     */
    const float halfItemHeight = ITEM_HEIGHT / 2;
    const float velocity = 1200.f;
    CreateWithItem([](ListModelNG model) { model.SetScrollSnapAlign(V2::ScrollSnapAlign::START); });
    ScrollDown(0.5);
    pattern_->OnScrollSnapCallback(-halfItemHeight, velocity);
    pattern_->HandleScroll(-halfItemHeight, SCROLL_FROM_ANIMATION, NestedState::GESTURE);
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_HEIGHT));
    ScrollDown(0.5);
    pattern_->OnScrollSnapCallback(-halfItemHeight, velocity);
    pattern_->HandleScroll(-halfItemHeight, SCROLL_FROM_ANIMATION, NestedState::GESTURE);
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_HEIGHT * 2));

    /**
     * @tc.steps: step2. V2::ScrollSnapAlign::END
     */
    CreateWithItem([](ListModelNG model) { model.SetScrollSnapAlign(V2::ScrollSnapAlign::END); });
    ScrollDown(0.5);
    pattern_->OnScrollSnapCallback(-halfItemHeight, velocity);
    pattern_->HandleScroll(-halfItemHeight, SCROLL_FROM_ANIMATION, NestedState::GESTURE);
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_HEIGHT));
    ScrollDown(0.5);
    pattern_->OnScrollSnapCallback(-halfItemHeight, velocity);
    pattern_->HandleScroll(-halfItemHeight, SCROLL_FROM_ANIMATION, NestedState::GESTURE);
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_HEIGHT * 2));

    /**
     * @tc.steps: step3. V2::ScrollSnapAlign::CENTER
     * @tc.expected: The first item is default at center
     */
    CreateWithItem([](ListModelNG model) { model.SetScrollSnapAlign(V2::ScrollSnapAlign::CENTER); });
    EXPECT_TRUE(IsEqualTotalOffset(-ITEM_HEIGHT * 3.5));
    ScrollDown(0.5);
    pattern_->OnScrollSnapCallback(-halfItemHeight, velocity);
    pattern_->HandleScroll(-halfItemHeight, SCROLL_FROM_ANIMATION, NestedState::GESTURE);
    EXPECT_TRUE(IsEqualTotalOffset(-ITEM_HEIGHT * 2.5));
    ScrollDown(0.5);
    pattern_->OnScrollSnapCallback(-halfItemHeight, velocity);
    pattern_->HandleScroll(-halfItemHeight, SCROLL_FROM_ANIMATION, NestedState::GESTURE);
    EXPECT_TRUE(IsEqualTotalOffset(-ITEM_HEIGHT * 1.5));
}

/**
 * @tc.name: AttrScrollSnapAlign002
 * @tc.desc: Test LayoutProperty about ScrollSnapAlign with HORIZONTAL
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, AttrScrollSnapAlign002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. V2::ScrollSnapAlign::START
     */
    const float halfItemWidth = ITEM_WIDTH / 2;
    const float velocity = 1200.f;
    Create([](ListModelNG model) {
        model.SetListDirection(Axis::HORIZONTAL);
        model.SetScrollSnapAlign(V2::ScrollSnapAlign::START);
        CreateItem(TOTAL_LINE_NUMBER, Axis::HORIZONTAL);
    });
    ScrollDown(0.5);
    pattern_->OnScrollSnapCallback(-halfItemWidth, velocity);
    pattern_->HandleScroll(-halfItemWidth, SCROLL_FROM_ANIMATION, NestedState::GESTURE);
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_WIDTH));
    ScrollDown(0.5);
    pattern_->OnScrollSnapCallback(-halfItemWidth, velocity);
    pattern_->HandleScroll(-halfItemWidth, SCROLL_FROM_ANIMATION, NestedState::GESTURE);
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_WIDTH * 2));

    /**
     * @tc.steps: step2. V2::ScrollSnapAlign::END
     */
    Create([](ListModelNG model) {
        model.SetListDirection(Axis::HORIZONTAL);
        model.SetScrollSnapAlign(V2::ScrollSnapAlign::END);
        CreateItem(TOTAL_LINE_NUMBER, Axis::HORIZONTAL);
    });
    ScrollDown(0.5);
    pattern_->OnScrollSnapCallback(-halfItemWidth, velocity);
    pattern_->HandleScroll(-halfItemWidth, SCROLL_FROM_ANIMATION, NestedState::GESTURE);
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_WIDTH));
    ScrollDown(0.5);
    pattern_->OnScrollSnapCallback(-halfItemWidth, velocity);
    pattern_->HandleScroll(-halfItemWidth, SCROLL_FROM_ANIMATION, NestedState::GESTURE);
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_WIDTH * 2));

    /**
     * @tc.steps: step3. V2::ScrollSnapAlign::CENTER
     * @tc.expected: The first item is default at center
     */
    Create([](ListModelNG model) {
        model.SetListDirection(Axis::HORIZONTAL);
        model.SetScrollSnapAlign(V2::ScrollSnapAlign::CENTER);
        CreateItem(TOTAL_LINE_NUMBER, Axis::HORIZONTAL);
    });
    EXPECT_TRUE(IsEqualTotalOffset(-ITEM_WIDTH * 3.5));
    ScrollDown(0.5);
    pattern_->OnScrollSnapCallback(-halfItemWidth, velocity);
    pattern_->HandleScroll(-halfItemWidth, SCROLL_FROM_ANIMATION, NestedState::GESTURE);
    EXPECT_TRUE(IsEqualTotalOffset(-ITEM_WIDTH * 2.5));
    ScrollDown(0.5);
    pattern_->OnScrollSnapCallback(-halfItemWidth, velocity);
    pattern_->HandleScroll(-halfItemWidth, SCROLL_FROM_ANIMATION, NestedState::GESTURE);
    EXPECT_TRUE(IsEqualTotalOffset(-ITEM_WIDTH * 1.5));
}

/**
 * @tc.name: AttrScrollSnapAlign003
 * @tc.desc: Test LayoutProperty about ScrollSnapAlign with VERTICAL and different itemHeight
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, AttrScrollSnapAlign003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. V2::ScrollSnapAlign::START
     */
    const float halfItemHeight = ITEM_HEIGHT / 2;
    const float velocity = 1200.f;
    CreateWithItem([](ListModelNG model) { model.SetScrollSnapAlign(V2::ScrollSnapAlign::START); });
    GetChildLayoutProperty<ListItemLayoutProperty>(frameNode_, 1)
        ->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(ITEM_HEIGHT * 1.5)));
    ScrollDown(0.5);
    pattern_->OnScrollSnapCallback(-halfItemHeight, velocity);
    pattern_->HandleScroll(-halfItemHeight, SCROLL_FROM_ANIMATION, NestedState::GESTURE);
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_HEIGHT));
    ScrollDown(1);
    pattern_->OnScrollSnapCallback(-halfItemHeight, velocity);
    pattern_->HandleScroll(-halfItemHeight, SCROLL_FROM_ANIMATION, NestedState::GESTURE);
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_HEIGHT * 2.5));

    /**
     * @tc.steps: step2. V2::ScrollSnapAlign::END
     */
    CreateWithItem([](ListModelNG model) { model.SetScrollSnapAlign(V2::ScrollSnapAlign::END); });
    GetChildLayoutProperty<ListItemLayoutProperty>(frameNode_, 1)
        ->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(ITEM_HEIGHT * 1.5)));
    ScrollDown(0.5);
    pattern_->OnScrollSnapCallback(-halfItemHeight, velocity);
    pattern_->HandleScroll(-halfItemHeight, SCROLL_FROM_ANIMATION, NestedState::GESTURE);
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_HEIGHT));
    ScrollDown(1);
    pattern_->OnScrollSnapCallback(-halfItemHeight, velocity);
    pattern_->HandleScroll(-halfItemHeight, SCROLL_FROM_ANIMATION, NestedState::GESTURE);
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_HEIGHT * 2.5));

    /**
     * @tc.steps: step3. V2::ScrollSnapAlign::CENTER
     * @tc.expected: The first item is default at center
     */
    CreateWithItem([](ListModelNG model) { model.SetScrollSnapAlign(V2::ScrollSnapAlign::CENTER); });
    GetChildLayoutProperty<ListItemLayoutProperty>(frameNode_, 1)
        ->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(ITEM_HEIGHT * 1.5)));
    EXPECT_TRUE(IsEqualTotalOffset(-ITEM_HEIGHT * 3.5));
    ScrollDown(0.5);
    pattern_->OnScrollSnapCallback(-halfItemHeight, velocity);
    pattern_->HandleScroll(-halfItemHeight, SCROLL_FROM_ANIMATION, NestedState::GESTURE);
    EXPECT_TRUE(IsEqualTotalOffset(-ITEM_HEIGHT * 2.5));
    ScrollDown(0.5);
    pattern_->OnScrollSnapCallback(-0.75 * ITEM_HEIGHT, velocity);
    pattern_->HandleScroll(-0.75 * ITEM_HEIGHT, SCROLL_FROM_ANIMATION, NestedState::GESTURE);
    EXPECT_TRUE(IsEqualTotalOffset(-ITEM_HEIGHT * 1.25));
}

/**
 * @tc.name: AttrScrollSnapAlign004
 * @tc.desc: Test LayoutProperty about ScrollSnapAlign FixPredictSnapOffsetAlignStart/Center
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, AttrScrollSnapAlign004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. V2::ScrollSnapAlign::START
     */
    float contentMainSize = TOTAL_LINE_NUMBER * ITEM_HEIGHT;
    const float halfItemHeight = ITEM_HEIGHT / 2;
    const float velocity = 1200.f;
    CreateWithItem([](ListModelNG model) { model.SetScrollSnapAlign(V2::ScrollSnapAlign::START); });
    ScrollUp(0.5);
    pattern_->OnScrollSnapCallback(halfItemHeight, velocity);
    pattern_->HandleScroll(halfItemHeight, SCROLL_FROM_ANIMATION, NestedState::GESTURE);
    CreateWithItem([](ListModelNG model) { model.SetScrollSnapAlign(V2::ScrollSnapAlign::START); });
    pattern_->OnScrollSnapCallback(-contentMainSize, velocity);
    pattern_->HandleScroll(-contentMainSize, SCROLL_FROM_ANIMATION, NestedState::GESTURE);
    EXPECT_TRUE(IsEqualTotalOffset(200));

    /**
     * @tc.steps: step2. V2::ScrollSnapAlign::END
     */
    CreateWithItem([](ListModelNG model) { model.SetScrollSnapAlign(V2::ScrollSnapAlign::END); });
    ScrollDown(0.5);
    pattern_->OnScrollSnapCallback(-halfItemHeight, velocity);
    pattern_->HandleScroll(-halfItemHeight, SCROLL_FROM_ANIMATION, NestedState::GESTURE);
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_HEIGHT));

    /**
     * @tc.steps: step3. V2::ScrollSnapAlign::CENTER
     * @tc.expected: The first item is default at center
     */
    CreateWithItem([](ListModelNG model) { model.SetScrollSnapAlign(V2::ScrollSnapAlign::CENTER); });
    EXPECT_TRUE(IsEqualTotalOffset(-ITEM_HEIGHT * 3.5));
    pattern_->OnScrollSnapCallback(contentMainSize / 2, velocity);
    pattern_->HandleScroll(contentMainSize / 2, SCROLL_FROM_ANIMATION, NestedState::GESTURE);
    EXPECT_TRUE(IsEqualTotalOffset(-ITEM_HEIGHT * 3.5));
}

/**
 * @tc.name: AttrSLECM001
 * @tc.desc: Test property about scroller/listDirection/edgeEffect/chainAnimation/multiSelectable
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, AttrSLECM001, TestSize.Level1)
{
    CreateWithItem([](ListModelNG model) {
        model.SetListDirection(Axis::HORIZONTAL);
        model.SetEdgeEffect(EdgeEffect::SPRING, false);
        model.SetChainAnimation(true);
        model.SetMultiSelectable(true);
    });

    EXPECT_NE(pattern_->positionController_, nullptr);
    EXPECT_EQ(pattern_->GetAxis(), Axis::HORIZONTAL);
    EXPECT_NE(pattern_->GetScrollEdgeEffect(), nullptr);
    EXPECT_NE(pattern_->chainAnimation_, nullptr);
    EXPECT_TRUE(pattern_->multiSelectable_);
}

/**
 * @tc.name: AttrEnableScrollInteraction001
 * @tc.desc: Test property about enableScrollInteraction.
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, AttrEnableScrollInteraction001, TestSize.Level1)
{
    CreateWithItem([](ListModelNG model) { model.SetScrollEnabled(true); });
    EXPECT_TRUE(layoutProperty_->GetScrollEnabledValue());
    CreateWithItem([](ListModelNG model) { model.SetScrollEnabled(false); });
    EXPECT_FALSE(layoutProperty_->GetScrollEnabledValue());
}

/**
 * @tc.name: AttrFriction001
 * @tc.desc: Test SetFriction:friction shouled be more than 0.0,if out of range,should be default value.
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, AttrFriction001, TestSize.Level1)
{
    CreateWithItem([](ListModelNG model) { model.SetFriction(0); });
    EXPECT_DOUBLE_EQ(pattern_->GetFriction(), DEFAULT_FRICTION);
    CreateWithItem([](ListModelNG model) { model.SetFriction(-1); });
    EXPECT_DOUBLE_EQ(pattern_->GetFriction(), DEFAULT_FRICTION);
    CreateWithItem([](ListModelNG model) { model.SetFriction(1); });
    EXPECT_DOUBLE_EQ(pattern_->GetFriction(), 1);
}

/**
 * @tc.name: EdgeEffectOption001
 * @tc.desc: Test EdgeEffectOption
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, EdgeEffectOption001, TestSize.Level1)
{
    Create([](ListModelNG model) {
        CreateItem(TOTAL_LINE_NUMBER);
        model.SetEdgeEffect(EdgeEffect::SPRING, false);
    });
    EXPECT_FALSE(pattern_->GetAlwaysEnabled());
    EXPECT_TRUE(pattern_->scrollable_);
}

/**
 * @tc.name: EdgeEffectOption002
 * @tc.desc: Test EdgeEffectOption
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, EdgeEffectOption002, TestSize.Level1)
{
    Create([](ListModelNG model) {
        CreateItem(TOTAL_LINE_NUMBER);
        model.SetEdgeEffect(EdgeEffect::SPRING, true);
    });
    EXPECT_TRUE(pattern_->GetAlwaysEnabled());
    EXPECT_TRUE(pattern_->scrollable_);
}

/**
 * @tc.name: EdgeEffectOption003
 * @tc.desc: Test EdgeEffectOption
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, EdgeEffectOption003, TestSize.Level1)
{
    Create([](ListModelNG model) {
        CreateItem(1); // 1 is item count.
        model.SetEdgeEffect(EdgeEffect::SPRING, false);
    });
    EXPECT_FALSE(pattern_->GetAlwaysEnabled());
    EXPECT_FALSE(pattern_->scrollable_);
}

/**
 * @tc.name: EdgeEffectOption004
 * @tc.desc: Test EdgeEffectOption
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, EdgeEffectOption004, TestSize.Level1)
{
    Create([](ListModelNG model) {
        CreateItem(1); // 1 is item count.
        model.SetEdgeEffect(EdgeEffect::SPRING, true);
    });
    EXPECT_TRUE(pattern_->GetAlwaysEnabled());
    EXPECT_TRUE(pattern_->scrollable_);
}

/**
 * @tc.name: SetEdgeEffectCallback001
 * @tc.desc: Test SetEdgeEffectCallback
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestNg, SetEdgeEffectCallback001, TestSize.Level1)
{
    CreateWithItem([](ListModelNG model) { model.SetEdgeEffect(EdgeEffect::SPRING, false); });
    RefPtr<ScrollEdgeEffect> scrollEdgeEffect = pattern_->GetScrollEdgeEffect();
    EXPECT_EQ(scrollEdgeEffect->currentPositionCallback_(), 0);
    EXPECT_EQ(scrollEdgeEffect->leadingCallback_(), 0);
    EXPECT_EQ(scrollEdgeEffect->trailingCallback_(), 0.0);
    EXPECT_EQ(scrollEdgeEffect->initLeadingCallback_(), 0);
    EXPECT_EQ(scrollEdgeEffect->initTrailingCallback_(), 0.0);

    CreateWithItem([](ListModelNG model) {
        model.SetScrollSnapAlign(V2::ScrollSnapAlign::CENTER);
        model.SetEdgeEffect(EdgeEffect::SPRING, false);
    });
    scrollEdgeEffect = pattern_->GetScrollEdgeEffect();
    EXPECT_EQ(scrollEdgeEffect->currentPositionCallback_(), 350.0);
    EXPECT_EQ(scrollEdgeEffect->leadingCallback_(), -50.0);
    EXPECT_EQ(scrollEdgeEffect->trailingCallback_(), 350.f);
    EXPECT_EQ(scrollEdgeEffect->initLeadingCallback_(), -50.0);
    EXPECT_EQ(scrollEdgeEffect->initTrailingCallback_(), 350.f);

    Create([](ListModelNG model) {
        model.SetScrollSnapAlign(V2::ScrollSnapAlign::CENTER);
        model.SetEdgeEffect(EdgeEffect::SPRING, false);
    });
    scrollEdgeEffect = pattern_->GetScrollEdgeEffect();
    EXPECT_EQ(scrollEdgeEffect->currentPositionCallback_(), 0);
    EXPECT_EQ(scrollEdgeEffect->leadingCallback_(), 800);
    EXPECT_EQ(scrollEdgeEffect->trailingCallback_(), 0.0);
    EXPECT_EQ(scrollEdgeEffect->initLeadingCallback_(), 800);
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
    CreateWithItem([options](ListModelNG model) {
        model.SetSpace(Dimension(SPACE));
        model.SetChainAnimation(true);
        model.SetChainAnimationOptions(options);
    });

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
    CreateWithItem([options](ListModelNG model) {
        model.SetSpace(Dimension(SPACE));
        model.SetChainAnimation(true);
        model.SetChainAnimationOptions(options);
    });

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
    CreateWithItem([options](ListModelNG model) {
        model.SetSpace(Dimension(SPACE));
        model.SetChainAnimation(true);
        model.SetChainAnimationOptions(options);
    });

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
} // namespace OHOS::Ace::NG
