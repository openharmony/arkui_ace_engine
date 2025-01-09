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

#include "scroll_test_ng.h"

namespace OHOS::Ace::NG {
class ScrollLayoutTestNg : public ScrollTestNg {
public:
};

/**
 * @tc.name: ScrollSetFrictionTest001
 * @tc.desc: Test SetFriction
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, ScrollSetFrictionTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set friction less than 0
     * @tc.expected: should be more than 0.0,if out of range,should be default value.
     */
    auto pipelineContext = PipelineContext::GetCurrentContext();
    pipelineContext->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    double friction = -1;
    ScrollModelNG model = CreateScroll();
    model.SetFriction(friction);
    CreateScrollDone();
    EXPECT_DOUBLE_EQ(pattern_->GetFriction(), DEFAULT_FRICTION);

    /**
     * @tc.steps: step1. set friction more than 0
     * @tc.expected: friction should be more than 0.0,if out of range,should be default value.
     */
    friction = 10;
    model = CreateScroll();
    model.SetFriction(friction);
    CreateScrollDone();
    EXPECT_DOUBLE_EQ(pattern_->GetFriction(), friction);
}

/**
 * @tc.name: Distributed001
 * @tc.desc: Test the distributed capability of Scroll.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, Distributed001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize Scroll node
     */
    CreateScroll();
    CreateContent();
    CreateScrollDone();

    // need dpi to be 1
    /**
     * @tc.steps: step2. get pattern .
     * @tc.expected: function ProvideRestoreInfo is called.
     */
    pattern_->currentOffset_ = 1.0f;
    std::string ret = pattern_->ProvideRestoreInfo();

    /**
     * @tc.steps: step3. function OnRestoreInfo is called.
     * @tc.expected: Passing JSON format.
     */
    pattern_->OnRestoreInfo(ret);
    EXPECT_DOUBLE_EQ(pattern_->currentOffset_, 1.0f);
}

/**
 * @tc.name: ScrollGetItemRect001
 * @tc.desc: Test Scroll GetItemRect function.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, ScrollGetItemRect001, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    model.SetAxis(Axis::HORIZONTAL);
    CreateContent();
    CreateScrollDone();

    /**
     * @tc.steps: step1. Get invalid ScrollItem Rect.
     * @tc.expected: Return 0 when input invalid index.
     */
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(-1), Rect()));
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(1), Rect()));

    /**
     * @tc.steps: step2. Get valid ScrollItem Rect.
     * @tc.expected: Return actual Rect when input valid index.
     */
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(0), Rect(0, 0, CONTENT_MAIN_SIZE, HEIGHT)));
}

/**
 * @tc.name: ScrollWidth001
 * @tc.desc: Test the usability of scroll width property and its get and set function.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, ScrollWidth001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. verify the scroll width property
     * of scroll layout property.
     * @tc.expected: Default value is ought to be false.
     */
    CreateScroll();
    CreateContent();
    CreateScrollDone();
    float scrollWidth = 150.0f;
    EXPECT_FALSE(layoutProperty_->GetScrollWidth().has_value());
    layoutProperty_->UpdateScrollWidth(scrollWidth);
    EXPECT_EQ(layoutProperty_->GetScrollWidth().value(), scrollWidth);
}

/**
 * @tc.name: SelectScroll001
 * @tc.desc: Test the flags of select scroll that determines whether it belong to or be modified by a select
 * and their get and set functions.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, SelectScroll001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. verify the default value of the flags
     * which inform whether the scroll belongs to or is modified by a select.
     * @tc.expected: Default value is ought to be false.
     */
    CreateScroll();
    CreateContent();
    CreateScrollDone();
    EXPECT_FALSE(pattern_->IsWidthModifiedBySelect());
    EXPECT_FALSE(pattern_->IsSelectScroll());
    /**
     * @tc.steps: step2. Set both flags to be true and verify the usability of their get and set functions in
     * select pattern.
     * @tc.expected: After setting the value should be true.
     */
    pattern_->SetIsWidthModifiedBySelect(true);
    pattern_->SetIsSelectScroll(true);
    EXPECT_TRUE(pattern_->IsWidthModifiedBySelect());
    EXPECT_TRUE(pattern_->IsSelectScroll());
}

/**
 * @tc.name: Measure002
 * @tc.desc: Test ScrollLayoutAlgorithm Measure when the scroll belongs to a select.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, Measure002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scroll model and set the width, height, axis of the scroll, create the content of
     * the scroll and get its instance.
     * @tc.expected: Objects are created successfully.
     */
    CreateScroll();
    CreateContent();
    CreateScrollDone();
    RefPtr<LayoutWrapperNode> layoutWrapper = frameNode_->CreateLayoutWrapper(false, false);
    pattern_->SetIsSelectScroll(true);
    FlushLayoutTask(frameNode_);
    layoutWrapper->MountToHostOnMainThread();

    RefPtr<GridColumnInfo> columnInfo = GridSystemManager::GetInstance().GetInfoByType(GridColumnType::MENU);
    columnInfo->GetParent()->BuildColumnWidth();
    auto defaultWidth = static_cast<float>(columnInfo->GetWidth(2));
    auto scrollSize = frameNode_->GetGeometryNode()->GetFrameSize();
    auto expectSize = SizeF(defaultWidth, 600.f);
    EXPECT_NE(scrollSize, expectSize) << "scrollSize: " << scrollSize.ToString()
                                      << " expectSize: " << expectSize.ToString();
}

/**
 * @tc.name: Measure003
 * @tc.desc: Test ScrollLayoutAlgorithm Measure.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, Measure003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scroll without children
     */
    CreateScroll();
    CreateScrollDone();
    auto scrollSize = frameNode_->GetGeometryNode()->GetFrameSize();
    auto expectSize = SizeF(WIDTH, HEIGHT);
    EXPECT_TRUE(IsEqual(scrollSize, expectSize));

    /**
     * @tc.steps: step1. set idealSize
     * @tc.expected: The frameSize would be idealSize
     */
    ViewAbstract::SetWidth(AceType::RawPtr(frameNode_), CalcLength(300.f));
    ViewAbstract::SetHeight(AceType::RawPtr(frameNode_), CalcLength(500.f));
    FlushLayoutTask(frameNode_);
    scrollSize = frameNode_->GetGeometryNode()->GetFrameSize();
    expectSize = SizeF(300.f, 500.f);
    EXPECT_TRUE(IsEqual(scrollSize, expectSize));
}

/**
 * @tc.name: SelectScroll002
 * @tc.desc: Test select scroll default width.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, SelectScroll002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get the width of select scroll without setting it, this case is meant to test the correctness
     * of its default value.
     * @tc.expected: Default width of select scroll should be 0.0.
     */
    CreateScroll();
    CreateContent();
    CreateScrollDone();
    auto ScrollWidth = pattern_->GetSelectScrollWidth();
    ASSERT_NE(ScrollWidth, 0.0);
}

/**
 * @tc.name: InitialOffset001
 * @tc.desc: Test initialOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, InitialOffset001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scroll.
     * @tc.expected: the value of currentOffset_ is 0
     */
    CreateScroll();
    CreateContent();
    CreateScrollDone();
    EXPECT_EQ(pattern_->currentOffset_, 0.f);

    /**
     * @tc.steps: step2. Create scroll and set initialOffset ITEM_MAIN_SIZE.
     * @tc.expected: the value of currentOffset_ is -ITEM_MAIN_SIZE
     */
    ScrollModelNG model = CreateScroll();
    model.SetInitialOffset(OffsetT(CalcDimension(0.f), CalcDimension(ITEM_MAIN_SIZE)));
    CreateContent();
    CreateScrollDone();
    EXPECT_EQ(pattern_->currentOffset_, -ITEM_MAIN_SIZE);

    /**
     * @tc.steps: step3. Create scroll , set axis HORIZONTAL and set initialOffset ITEM_MAIN_SIZE.
     * @tc.expected: the value of currentOffset_ is -ITEM_MAIN_SIZE
     */
    model = CreateScroll();
    model.SetInitialOffset(OffsetT(CalcDimension(ITEM_MAIN_SIZE), CalcDimension(0.f)));
    model.SetAxis(Axis::HORIZONTAL);
    CreateContent();
    CreateScrollDone();
    EXPECT_EQ(pattern_->currentOffset_, -ITEM_MAIN_SIZE);

    /**
     * @tc.steps: step4. Create scroll , set initialOffset 10%.
     * @tc.expected: the value of currentOffset_ is -ITEM_MAIN_SIZE
     */
    model = CreateScroll();
    auto offset = Dimension(0.1, DimensionUnit::PERCENT);
    model.SetInitialOffset(OffsetT(CalcDimension(0.f), CalcDimension(offset)));
    CreateContent();
    CreateScrollDone();
    EXPECT_EQ(pattern_->currentOffset_, -HEIGHT * 0.1f);

    /**
     * @tc.steps: step5. Create scroll , set axis HORIZONTAL and set initialOffset 10%.
     * @tc.expected: the value of currentOffset_ is -ITEM_MAIN_SIZE
     */
    model = CreateScroll();
    model.SetInitialOffset(OffsetT(CalcDimension(offset), CalcDimension(0.f)));
    model.SetAxis(Axis::HORIZONTAL);
    CreateContent();
    CreateScrollDone();
    EXPECT_EQ(pattern_->currentOffset_, -WIDTH * 0.1f);
}

/**
 * @tc.name: InitialOffset002
 * @tc.desc: Test initialOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, InitialOffset002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scroll and set initialOffset 2*ITEM_MAIN_SIZE.
     * @tc.expected: the value of currentOffset_ is -2*ITEM_MAIN_SIZE
     */
    ScrollModelNG model = CreateScroll();
    model.SetInitialOffset(OffsetT(CalcDimension(0.f), CalcDimension(2 * ITEM_MAIN_SIZE)));
    CreateContent();
    CreateScrollDone();
    EXPECT_EQ(pattern_->currentOffset_, -2 * ITEM_MAIN_SIZE);

    /**
     * @tc.steps: step2. Create scroll and set initialOffset 3*ITEM_MAIN_SIZE.
     * @tc.expected: the value of currentOffset_ is -2*ITEM_MAIN_SIZE
     */
    model = CreateScroll();
    model.SetInitialOffset(OffsetT(CalcDimension(0.f), CalcDimension(100 * ITEM_MAIN_SIZE)));
    CreateContent();
    CreateScrollDone();
    EXPECT_EQ(pattern_->currentOffset_, -VERTICAL_SCROLLABLE_DISTANCE);

    /**
     * @tc.steps: step3. Create scroll and set initialOffset -ITEM_MAIN_SIZE.
     * @tc.expected: the value of currentOffset_ is 0
     */
    model = CreateScroll();
    model.SetInitialOffset(OffsetT(CalcDimension(0.f), CalcDimension(-ITEM_MAIN_SIZE)));
    CreateContent();
    CreateScrollDone();
    EXPECT_EQ(pattern_->currentOffset_, 0.f);

    /**
     * @tc.steps: step4. Create scroll , set initialOffset 100%.
     * @tc.expected: the value of currentOffset_ is -2*ITEM_MAIN_SIZE
     */
    model = CreateScroll();
    auto offset = Dimension(100, DimensionUnit::PERCENT);
    model.SetInitialOffset(OffsetT(CalcDimension(0.f), CalcDimension(offset)));
    CreateContent();
    CreateScrollDone();
    EXPECT_EQ(pattern_->currentOffset_, -VERTICAL_SCROLLABLE_DISTANCE);
}

/**
 * @tc.name: Model001
 * @tc.desc: Test scroll model
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, Model001, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    EXPECT_NE(model.GetOrCreateController(), nullptr);
    pattern_->positionController_ = nullptr;
    EXPECT_NE(model.GetOrCreateController(), nullptr);
    EXPECT_NE(model.GetOrCreateController(AceType::RawPtr(frameNode_)), nullptr);
    pattern_->positionController_ = nullptr;
    EXPECT_NE(model.GetOrCreateController(AceType::RawPtr(frameNode_)), nullptr);
    EXPECT_EQ(model.GetAxis(AceType::RawPtr(frameNode_)), 0);
    model.SetAxis(Axis::VERTICAL);
    EXPECT_EQ(model.GetAxis(AceType::RawPtr(frameNode_)), 0);
    EXPECT_EQ(model.GetScrollEnabled(AceType::RawPtr(frameNode_)), 1);
    model.SetScrollEnabled(AceType::RawPtr(frameNode_), false);
    EXPECT_EQ(model.GetScrollEnabled(AceType::RawPtr(frameNode_)), 0);
    model.SetEnablePaging(AceType::RawPtr(frameNode_), true);
    EXPECT_EQ(pattern_->GetEnablePaging(), ScrollPagingStatus::VALID);
    EXPECT_EQ(pattern_->IsEnablePagingValid(), true);
    model.SetEnablePaging(AceType::RawPtr(frameNode_), false);
    EXPECT_EQ(pattern_->GetEnablePaging(), ScrollPagingStatus::INVALID);
    EXPECT_EQ(pattern_->IsEnablePagingValid(), false);
    CreateContent();
    CreateScrollDone();

    EXPECT_EQ(model.GetOnScrollEdge(AceType::RawPtr(frameNode_)), ScrollEdgeType::SCROLL_TOP);
    ScrollTo(ITEM_MAIN_SIZE);
    EXPECT_EQ(model.GetOnScrollEdge(AceType::RawPtr(frameNode_)), ScrollEdgeType::SCROLL_NONE);
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    EXPECT_EQ(model.GetOnScrollEdge(AceType::RawPtr(frameNode_)), ScrollEdgeType::SCROLL_BOTTOM);

    ScrollTo(0.f);
    pattern_->SetAxis(Axis::HORIZONTAL);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(model.GetOnScrollEdge(AceType::RawPtr(frameNode_)), ScrollEdgeType::SCROLL_LEFT);
    ScrollTo(ITEM_MAIN_SIZE);
    EXPECT_EQ(model.GetOnScrollEdge(AceType::RawPtr(frameNode_)), ScrollEdgeType::SCROLL_NONE);
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    EXPECT_EQ(model.GetOnScrollEdge(AceType::RawPtr(frameNode_)), ScrollEdgeType::SCROLL_RIGHT);

    pattern_->SetAxis(Axis::NONE);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(model.GetOnScrollEdge(AceType::RawPtr(frameNode_)), ScrollEdgeType::SCROLL_NONE);
}

/**
 * @tc.name: Alignment001
 * @tc.desc: Test UpdateScrollAlignment in RTL Layout, content size less than scroll size
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, Alignment001, TestSize.Level1)
{
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    CreateScroll();
    CreateContent(100.f); // Set content height less than scroll height
    CreateScrollDone();

    /**
     * @tc.steps: step1. Set content width less than scroll width
     */
    float contentWidth = WIDTH / 2;
    auto contentNode = GetChildFrameNode(frameNode_, 0);
    ViewAbstract::SetWidth(AceType::RawPtr(contentNode), CalcLength(contentWidth));
    FlushLayoutTask(frameNode_);
    float centerPosition = (HEIGHT - ITEM_MAIN_SIZE) / 2;
    EXPECT_TRUE(IsEqual(GetChildOffset(frameNode_, 0), OffsetF(60, centerPosition)));

    layoutProperty_->UpdateAlignment(Alignment::TOP_LEFT);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(GetChildOffset(frameNode_, 0), OffsetF(contentWidth, 0.f)));

    layoutProperty_->UpdateAlignment(Alignment::TOP_RIGHT);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(GetChildOffset(frameNode_, 0), OffsetF()));

    layoutProperty_->UpdateAlignment(Alignment::BOTTOM_LEFT);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(GetChildOffset(frameNode_, 0), OffsetF(contentWidth, HEIGHT - ITEM_MAIN_SIZE)));

    layoutProperty_->UpdateAlignment(Alignment::BOTTOM_RIGHT);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(GetChildOffset(frameNode_, 0), OffsetF(0.f, HEIGHT - ITEM_MAIN_SIZE)));

    layoutProperty_->UpdateAlignment(Alignment::CENTER_RIGHT);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(GetChildOffset(frameNode_, 0), OffsetF(0.f, centerPosition)));

    layoutProperty_->UpdateAlignment(Alignment::CENTER_LEFT);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(GetChildOffset(frameNode_, 0), OffsetF(contentWidth, centerPosition)));

    layoutProperty_->UpdateAlignment(Alignment::CENTER);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(GetChildOffset(frameNode_, 0), OffsetF(contentWidth / 2, centerPosition)));
}

/**
 * @tc.name: Alignment002
 * @tc.desc: Test UpdateScrollAlignment in RTL Layout, content size greater than scroll size
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, Alignment002, TestSize.Level1)
{
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    CreateScroll();
    CreateContent(); // Set content height less than scroll height
    CreateScrollDone();

    /**
     * @tc.steps: step1. Set content width greater than scroll width
     */
    float contentWidth = WIDTH * 2;
    auto contentNode = GetChildFrameNode(frameNode_, 0);
    ViewAbstract::SetWidth(AceType::RawPtr(contentNode), CalcLength(contentWidth));
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(GetChildOffset(frameNode_, 0), OffsetF(-240, 0)));

    layoutProperty_->UpdateAlignment(Alignment::TOP_LEFT);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(GetChildOffset(frameNode_, 0), OffsetF(-WIDTH, 0.f)));

    layoutProperty_->UpdateAlignment(Alignment::TOP_RIGHT);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(GetChildOffset(frameNode_, 0), OffsetF(-WIDTH, 0.f)));

    layoutProperty_->UpdateAlignment(Alignment::BOTTOM_LEFT);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(GetChildOffset(frameNode_, 0), OffsetF(-WIDTH, 0.f)));

    layoutProperty_->UpdateAlignment(Alignment::BOTTOM_RIGHT);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(GetChildOffset(frameNode_, 0), OffsetF(-WIDTH, 0.f)));

    layoutProperty_->UpdateAlignment(Alignment::CENTER_RIGHT);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(GetChildOffset(frameNode_, 0), OffsetF(-WIDTH, 0.f)));

    layoutProperty_->UpdateAlignment(Alignment::CENTER_LEFT);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(GetChildOffset(frameNode_, 0), OffsetF(-WIDTH, 0.f)));

    layoutProperty_->UpdateAlignment(Alignment::CENTER);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(GetChildOffset(frameNode_, 0), OffsetF(-WIDTH, 0.f)));
}

/**
 * @tc.name: ToJsonValue001
 * @tc.desc: Test ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, ToJsonValue001, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    model.SetInitialOffset(OffsetT(CalcDimension(10.f), CalcDimension(20.f)));
    CreateContent();
    CreateScrollDone();
    EXPECT_EQ(pattern_->GetInitialOffset().GetX().ToString(), "10.00px");
    EXPECT_EQ(pattern_->GetInitialOffset().GetY().ToString(), "20.00px");

    /**
     * @tc.steps: step1. !IsFastFilter
     */
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    pattern_->ToJsonValue(json, filter);
    auto initialOffset = json->GetObject("initialOffset");
    EXPECT_EQ(initialOffset->GetString("xOffset"), "10.00px");
    EXPECT_EQ(initialOffset->GetString("yOffset"), "20.00px");

    /**
     * @tc.steps: step2. IsFastFilter
     */
    std::string attr = "id";
    filter.AddFilterAttr(attr);
    json = JsonUtil::Create(true);
    pattern_->ToJsonValue(json, filter);
    initialOffset = json->GetObject("initialOffset");
    EXPECT_EQ(initialOffset->GetString("xOffset"), "");
    EXPECT_EQ(initialOffset->GetString("yOffset"), "");
}

/**
 * @tc.name: RTL001
 * @tc.desc: Test horizontal scroll in RTL Layout, content size less than scroll size
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, RTL001, TestSize.Level1)
{
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    ScrollModelNG model = CreateScroll();
    model.SetAxis(Axis::HORIZONTAL);
    CreateContent(WIDTH / 2);
    CreateScrollDone(frameNode_);

    /**
     * @tc.steps: step1. Set content width less than scroll width
     */
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(GetChildOffset(frameNode_, 0), OffsetF(WIDTH / 4, 0.f)));
}

/**
 * @tc.name: ScrollEdge001
 * @tc.desc: Test ScrollEdge CheckScrollToEdge
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, ScrollEdge001, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    MockAnimationManager::GetInstance().SetTicks(TICK);

    /**
     * @tc.steps: step1. scrollEdge to bottom
     */
    CreateContent();
    CreateScrollDone();
    pattern_->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, true);
    EXPECT_EQ(pattern_->scrollEdgeType_, ScrollEdgeType::SCROLL_BOTTOM);
    MockAnimationManager::GetInstance().Tick();
    FlushLayoutTask(frameNode_);
    EXPECT_FALSE(pattern_->IsAtBottom());
    EXPECT_NE(pattern_->scrollEdgeType_, ScrollEdgeType::SCROLL_NONE);
    MockAnimationManager::GetInstance().CancelAnimations();

    /**
     * @tc.steps: step2. change content height in scrollEdge animation
     * @tc.expected: trigger CheckScrollToEdge
     */
    auto contentNode = GetChildFrameNode(frameNode_, 0);
    ViewAbstract::SetHeight(AceType::RawPtr(contentNode), CalcLength(2000.f));
    FlushLayoutTask(frameNode_, true);
    EXPECT_TRUE(pattern_->AnimateRunning());
    MockAnimationManager::GetInstance().Tick();
    EXPECT_FALSE(pattern_->IsAtBottom());
    MockAnimationManager::GetInstance().Tick();
    EXPECT_TRUE(pattern_->IsAtBottom());
    EXPECT_EQ(pattern_->scrollEdgeType_, ScrollEdgeType::SCROLL_NONE);
}

/**
 * @tc.name: ScrollEdge002
 * @tc.desc: Test ScrollEdge CheckScrollToEdge
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, ScrollEdge002, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    MockAnimationManager::GetInstance().SetTicks(TICK);

    /**
     * @tc.steps: step1. scrollEdge to bottom
     */
    CreateContent();
    CreateScrollDone();
    pattern_->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, true);
    EXPECT_EQ(pattern_->scrollEdgeType_, ScrollEdgeType::SCROLL_BOTTOM);
    MockAnimationManager::GetInstance().Tick();
    FlushLayoutTask(frameNode_);
    EXPECT_FALSE(pattern_->IsAtBottom());
    MockAnimationManager::GetInstance().Tick();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->scrollEdgeType_, ScrollEdgeType::SCROLL_NONE);
    EXPECT_TRUE(pattern_->IsAtBottom());
    pattern_->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, true);
    FlushLayoutTask(frameNode_, true);
    EXPECT_EQ(pattern_->scrollEdgeType_, ScrollEdgeType::SCROLL_NONE);
    EXPECT_FALSE(pattern_->AnimateRunning());

    /**
     * @tc.steps: step2. change content height without animation
     * @tc.expected: not trigger CheckScrollToEdge
     */
    auto contentNode = GetChildFrameNode(frameNode_, 0);
    ViewAbstract::SetHeight(AceType::RawPtr(contentNode), CalcLength(2000.f));
    FlushLayoutTask(frameNode_, true);
    EXPECT_EQ(pattern_->scrollEdgeType_, ScrollEdgeType::SCROLL_NONE);
    EXPECT_FALSE(pattern_->AnimateRunning());
    MockAnimationManager::GetInstance().Tick();
    FlushLayoutTask(frameNode_);
    EXPECT_FALSE(pattern_->IsAtBottom());
}

/**
 * @tc.name: ScrollEdge003
 * @tc.desc: Test ScrollEdge CheckScrollToEdge
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, ScrollEdge003, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    MockAnimationManager::GetInstance().SetTicks(TICK);

    /**
     * @tc.steps: step1. scrollEdge to bottom
     */
    CreateContent();
    CreateScrollDone();
    pattern_->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, true);
    EXPECT_EQ(pattern_->scrollEdgeType_, ScrollEdgeType::SCROLL_BOTTOM);
    MockAnimationManager::GetInstance().Tick();
    FlushLayoutTask(frameNode_);
    EXPECT_FALSE(pattern_->IsAtBottom());
    MockAnimationManager::GetInstance().Tick();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->scrollEdgeType_, ScrollEdgeType::SCROLL_NONE);
    EXPECT_TRUE(pattern_->IsAtBottom());
    pattern_->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, true);
    EXPECT_EQ(pattern_->scrollEdgeType_, ScrollEdgeType::SCROLL_BOTTOM);
    EXPECT_FALSE(pattern_->AnimateRunning());

    /**
     * @tc.steps: step2. change content height without animation
     * @tc.expected: trigger CheckScrollToEdge
     */
    auto contentNode = GetChildFrameNode(frameNode_, 0);
    ViewAbstract::SetHeight(AceType::RawPtr(contentNode), CalcLength(2000.f));
    FlushLayoutTask(frameNode_, true);
    EXPECT_TRUE(pattern_->AnimateRunning());
    MockAnimationManager::GetInstance().Tick();
    MockAnimationManager::GetInstance().Tick();
    EXPECT_EQ(pattern_->scrollEdgeType_, ScrollEdgeType::SCROLL_NONE);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(pattern_->IsAtBottom());
}

/**
 * @tc.name: ScrollGetChildrenExpandedSize001
 * @tc.desc: Test Scroll GetChildrenExpandedSize
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, ScrollGetChildrenExpandedSize001, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    CreateContent(100.f);
    CreateScrollDone();
    EXPECT_EQ(pattern_->GetChildrenExpandedSize(), SizeF(WIDTH, 100.f));

    auto padding = 2 * 5.f;
    ViewAbstract::SetPadding(AceType::RawPtr(frameNode_), CalcLength(5.f));
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetChildrenExpandedSize(), SizeF(WIDTH - padding, 100.f));

    auto contentNode = GetChildFrameNode(frameNode_, 0);
    ViewAbstract::SetHeight(AceType::RawPtr(contentNode), CalcLength(2000.f));
    FlushLayoutTask(frameNode_, true);
    EXPECT_EQ(pattern_->GetChildrenExpandedSize(), SizeF(WIDTH - padding, 2000.f));

    pattern_->SetAxis(Axis::HORIZONTAL);
    ViewAbstract::SetHeight(AceType::RawPtr(contentNode), CalcLength(HEIGHT));
    ViewAbstract::SetWidth(AceType::RawPtr(contentNode), CalcLength(100.f));
    FlushLayoutTask(frameNode_, true);
    EXPECT_EQ(pattern_->GetChildrenExpandedSize(), SizeF(100.f, HEIGHT - padding));

    ViewAbstract::SetWidth(AceType::RawPtr(contentNode), CalcLength(2000.f));
    FlushLayoutTask(frameNode_, true);
    EXPECT_EQ(pattern_->GetChildrenExpandedSize(), SizeF(2000.f, HEIGHT - padding));

    ViewAbstract::SetMargin(AceType::RawPtr(contentNode), CalcLength(5.f));
    FlushLayoutTask(frameNode_, true);
    EXPECT_EQ(pattern_->GetChildrenExpandedSize(), SizeF(2010.f, HEIGHT - padding));

    pattern_->SetAxis(Axis::NONE);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetChildrenExpandedSize(), SizeF(0.f, 0.f));

    pattern_->SetAxis(Axis::FREE);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetChildrenExpandedSize(), SizeF(0.f, 0.f));
}
} // namespace OHOS::Ace::NG
