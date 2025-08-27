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

#include "core/components_ng/pattern/scroll/scroll_layout_algorithm.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"

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
    FlushUITasks();
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
    FlushUITasks();
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
    FlushUITasks();
    EXPECT_EQ(model.GetOnScrollEdge(AceType::RawPtr(frameNode_)), ScrollEdgeType::SCROLL_LEFT);
    ScrollTo(ITEM_MAIN_SIZE);
    EXPECT_EQ(model.GetOnScrollEdge(AceType::RawPtr(frameNode_)), ScrollEdgeType::SCROLL_NONE);
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    EXPECT_EQ(model.GetOnScrollEdge(AceType::RawPtr(frameNode_)), ScrollEdgeType::SCROLL_RIGHT);

    pattern_->SetAxis(Axis::NONE);
    FlushUITasks();
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
    FlushUITasks();
    float centerPosition = (HEIGHT - ITEM_MAIN_SIZE) / 2;
    EXPECT_TRUE(IsEqual(GetChildOffset(frameNode_, 0), OffsetF(60, centerPosition)));

    layoutProperty_->UpdateAlignment(Alignment::TOP_LEFT);
    FlushUITasks();
    EXPECT_TRUE(IsEqual(GetChildOffset(frameNode_, 0), OffsetF(contentWidth, 0.f)));

    layoutProperty_->UpdateAlignment(Alignment::TOP_RIGHT);
    FlushUITasks();
    EXPECT_TRUE(IsEqual(GetChildOffset(frameNode_, 0), OffsetF()));

    layoutProperty_->UpdateAlignment(Alignment::BOTTOM_LEFT);
    FlushUITasks();
    EXPECT_TRUE(IsEqual(GetChildOffset(frameNode_, 0), OffsetF(contentWidth, HEIGHT - ITEM_MAIN_SIZE)));

    layoutProperty_->UpdateAlignment(Alignment::BOTTOM_RIGHT);
    FlushUITasks();
    EXPECT_TRUE(IsEqual(GetChildOffset(frameNode_, 0), OffsetF(0.f, HEIGHT - ITEM_MAIN_SIZE)));

    layoutProperty_->UpdateAlignment(Alignment::CENTER_RIGHT);
    FlushUITasks();
    EXPECT_TRUE(IsEqual(GetChildOffset(frameNode_, 0), OffsetF(0.f, centerPosition)));

    layoutProperty_->UpdateAlignment(Alignment::CENTER_LEFT);
    FlushUITasks();
    EXPECT_TRUE(IsEqual(GetChildOffset(frameNode_, 0), OffsetF(contentWidth, centerPosition)));

    layoutProperty_->UpdateAlignment(Alignment::CENTER);
    FlushUITasks();
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
    FlushUITasks();
    EXPECT_TRUE(IsEqual(GetChildOffset(frameNode_, 0), OffsetF(-240, 0)));

    layoutProperty_->UpdateAlignment(Alignment::TOP_LEFT);
    FlushUITasks();
    EXPECT_TRUE(IsEqual(GetChildOffset(frameNode_, 0), OffsetF(-WIDTH, 0.f)));

    layoutProperty_->UpdateAlignment(Alignment::TOP_RIGHT);
    FlushUITasks();
    EXPECT_TRUE(IsEqual(GetChildOffset(frameNode_, 0), OffsetF(-WIDTH, 0.f)));

    layoutProperty_->UpdateAlignment(Alignment::BOTTOM_LEFT);
    FlushUITasks();
    EXPECT_TRUE(IsEqual(GetChildOffset(frameNode_, 0), OffsetF(-WIDTH, 0.f)));

    layoutProperty_->UpdateAlignment(Alignment::BOTTOM_RIGHT);
    FlushUITasks();
    EXPECT_TRUE(IsEqual(GetChildOffset(frameNode_, 0), OffsetF(-WIDTH, 0.f)));

    layoutProperty_->UpdateAlignment(Alignment::CENTER_RIGHT);
    FlushUITasks();
    EXPECT_TRUE(IsEqual(GetChildOffset(frameNode_, 0), OffsetF(-WIDTH, 0.f)));

    layoutProperty_->UpdateAlignment(Alignment::CENTER_LEFT);
    FlushUITasks();
    EXPECT_TRUE(IsEqual(GetChildOffset(frameNode_, 0), OffsetF(-WIDTH, 0.f)));

    layoutProperty_->UpdateAlignment(Alignment::CENTER);
    FlushUITasks();
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
    FlushUITasks();
    EXPECT_TRUE(IsEqual(GetChildOffset(frameNode_, 0), OffsetF(WIDTH / 4, 0.f)));
}

/**
 * @tc.name: UpdateFrameSizeWithLayoutPolicy001
 * @tc.desc: test LayoutPolicy MATCH_PARENT
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, UpdateFrameSizeWithLayoutPolicy001, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    model.SetAxis(Axis::VERTICAL);
    CreateContent(HEIGHT);
    CreateScrollDone(frameNode_);
    ASSERT_NE(frameNode_, nullptr);;

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper(frameNode_, geometryNode, frameNode_->GetLayoutProperty());
    auto layoutAlgorithm = AceType::MakeRefPtr<ScrollLayoutAlgorithm>(1.0f);
    ASSERT_NE(layoutAlgorithm, nullptr);
    auto layoutProperty = layoutWrapper.GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    LayoutConstraintF parentLayoutConstraint;
    SizeF parentSize(300.0f, 300.0f);
    parentLayoutConstraint.maxSize = parentSize;
    parentLayoutConstraint.percentReference = parentSize;
    parentLayoutConstraint.selfIdealSize.SetSize(parentSize);
    layoutProperty->UpdateLayoutConstraint(parentLayoutConstraint);
    LayoutPolicyProperty layoutPolicyProperty;
    layoutPolicyProperty.widthLayoutPolicy_ = LayoutCalPolicy::FIX_AT_IDEAL_SIZE;
    layoutPolicyProperty.heightLayoutPolicy_ = LayoutCalPolicy::FIX_AT_IDEAL_SIZE;
    layoutProperty->layoutPolicy_ = layoutPolicyProperty;
    layoutProperty->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();

    layoutProperty->calcLayoutConstraint_->minSize = CalcSize{ CalcLength(0), CalcLength(0) };
    layoutProperty->calcLayoutConstraint_->maxSize = CalcSize{ CalcLength(200), CalcLength(200) };
    layoutAlgorithm->Measure(&layoutWrapper);
    auto frameSize = layoutWrapper.GetGeometryNode()->GetFrameSize();
    EXPECT_EQ(frameSize, SizeF(200, 200));
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
    FlushUITasks();
    EXPECT_FALSE(pattern_->IsAtBottom());
    EXPECT_NE(pattern_->scrollEdgeType_, ScrollEdgeType::SCROLL_NONE);
    MockAnimationManager::GetInstance().CancelAnimations();

    /**
     * @tc.steps: step2. change content height in scrollEdge animation
     * @tc.expected: trigger CheckScrollToEdge
     */
    auto contentNode = GetChildFrameNode(frameNode_, 0);
    ViewAbstract::SetHeight(AceType::RawPtr(contentNode), CalcLength(2000.f));
    FlushUITasks();
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
    FlushUITasks();
    EXPECT_FALSE(pattern_->IsAtBottom());
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_EQ(pattern_->scrollEdgeType_, ScrollEdgeType::SCROLL_NONE);
    EXPECT_TRUE(pattern_->IsAtBottom());
    pattern_->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, true);
    FlushUITasks();
    EXPECT_EQ(pattern_->scrollEdgeType_, ScrollEdgeType::SCROLL_NONE);
    EXPECT_FALSE(pattern_->AnimateRunning());

    /**
     * @tc.steps: step2. change content height without animation
     * @tc.expected: not trigger CheckScrollToEdge
     */
    auto contentNode = GetChildFrameNode(frameNode_, 0);
    ViewAbstract::SetHeight(AceType::RawPtr(contentNode), CalcLength(2000.f));
    FlushUITasks();
    EXPECT_EQ(pattern_->scrollEdgeType_, ScrollEdgeType::SCROLL_NONE);
    EXPECT_FALSE(pattern_->AnimateRunning());
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
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
    FlushUITasks();
    EXPECT_FALSE(pattern_->IsAtBottom());
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
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
    FlushUITasks();
    EXPECT_TRUE(pattern_->AnimateRunning());
    MockAnimationManager::GetInstance().Tick();
    MockAnimationManager::GetInstance().Tick();
    EXPECT_EQ(pattern_->scrollEdgeType_, ScrollEdgeType::SCROLL_NONE);
    FlushUITasks();
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
    FlushUITasks();
    EXPECT_EQ(pattern_->GetChildrenExpandedSize(), SizeF(WIDTH - padding, 100.f));

    auto contentNode = GetChildFrameNode(frameNode_, 0);
    ViewAbstract::SetHeight(AceType::RawPtr(contentNode), CalcLength(2000.f));
    FlushUITasks();
    EXPECT_EQ(pattern_->GetChildrenExpandedSize(), SizeF(WIDTH - padding, 2000.f));

    pattern_->SetAxis(Axis::HORIZONTAL);
    ViewAbstract::SetHeight(AceType::RawPtr(contentNode), CalcLength(HEIGHT));
    ViewAbstract::SetWidth(AceType::RawPtr(contentNode), CalcLength(100.f));
    FlushUITasks();
    EXPECT_EQ(pattern_->GetChildrenExpandedSize(), SizeF(100.f, HEIGHT - padding));

    ViewAbstract::SetWidth(AceType::RawPtr(contentNode), CalcLength(2000.f));
    FlushUITasks();
    EXPECT_EQ(pattern_->GetChildrenExpandedSize(), SizeF(2000.f, HEIGHT - padding));

    ViewAbstract::SetMargin(AceType::RawPtr(contentNode), CalcLength(5.f));
    FlushUITasks();
    EXPECT_EQ(pattern_->GetChildrenExpandedSize(), SizeF(2010.f, HEIGHT - padding));

    pattern_->SetAxis(Axis::NONE);
    FlushUITasks();
    EXPECT_EQ(pattern_->GetChildrenExpandedSize(), SizeF(0.f, 0.f));

    pattern_->SetAxis(Axis::FREE);
    FlushUITasks();
    EXPECT_EQ(pattern_->GetChildrenExpandedSize(), SizeF(2010.f, HEIGHT + 10.f));
}

/**
 * @tc.name: ScrollAdjustOffset001
 * @tc.desc: Test Scroll AdjustOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, ScrollAdjustOffset001, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateContent(1000.f);
    CreateScrollDone();

    pattern_->currentOffset_ = 1000.f;
    pattern_->OnScrollCallback(-100.f, SCROLL_FROM_FOCUS_JUMP);
    EXPECT_EQ(pattern_->currentOffset_, 900.f);

    pattern_->currentOffset_ = 1000.f;
    pattern_->OnScrollCallback(-100.f, SCROLL_FROM_UPDATE);
    EXPECT_GT(pattern_->currentOffset_, 900.f);
    EXPECT_LT(pattern_->currentOffset_, 1000.f);

    pattern_->currentOffset_ = 1000.f;
    pattern_->OnScrollCallback(100.f, SCROLL_FROM_UPDATE);
    EXPECT_GT(pattern_->currentOffset_, 1000.f);
    EXPECT_LT(pattern_->currentOffset_, 1100.f);
}

/**
 * @tc.name: UseInitialOffset001
 * @tc.desc: Test Scroll UseInitialOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, UseInitialOffset001, TestSize.Level1)
{
    auto scrollLayoutAlgorithm = AceType::MakeRefPtr<ScrollLayoutAlgorithm>(1.0f);
    auto axis = Axis::VERTICAL;
    auto selfSize = SizeF(1.0f, 1.0f);
    frameNode_ = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ScrollPattern>(); });
    RefPtr<LayoutWrapperNode> layoutWrapper = frameNode_->CreateLayoutWrapper(false, false);
    ASSERT_NE(layoutWrapper, nullptr);
    auto scrollNode = layoutWrapper->GetHostNode();
    ASSERT_NE(scrollNode, nullptr);
    auto scrollPattern = scrollNode->GetPattern<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    scrollPattern->isInitialized_ = false;
    LayoutWrapper* rawPtr = &(*layoutWrapper);
    ASSERT_NE(rawPtr, nullptr);
    scrollLayoutAlgorithm->UseInitialOffset(axis, selfSize, rawPtr);
    EXPECT_EQ(scrollLayoutAlgorithm->GetCurrentOffset(), 1.0f);
}

/**
 * @tc.name: UseInitialOffset002
 * @tc.desc: Test Scroll UseInitialOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, UseInitialOffset002, TestSize.Level1)
{
    auto scrollLayoutAlgorithm = AceType::MakeRefPtr<ScrollLayoutAlgorithm>(1.0f);
    auto axis = Axis::NONE;
    auto selfSize = SizeF(1.0f, 1.0f);
    frameNode_ = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ScrollPattern>(); });
    RefPtr<LayoutWrapperNode> layoutWrapper = frameNode_->CreateLayoutWrapper(false, false);
    ASSERT_NE(layoutWrapper, nullptr);
    auto scrollNode = layoutWrapper->GetHostNode();
    ASSERT_NE(scrollNode, nullptr);
    auto scrollPattern = scrollNode->GetPattern<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    scrollPattern->isInitialized_ = false;
    LayoutWrapper* rawPtr = &(*layoutWrapper);
    ASSERT_NE(rawPtr, nullptr);
    scrollLayoutAlgorithm->UseInitialOffset(axis, selfSize, rawPtr);
    EXPECT_EQ(scrollLayoutAlgorithm->GetCurrentOffset(), 1.0f);
}

/**
 * @tc.name: UseInitialOffset003
 * @tc.desc: Test Scroll UseInitialOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, UseInitialOffset003, TestSize.Level1)
{
    auto scrollLayoutAlgorithm = AceType::MakeRefPtr<ScrollLayoutAlgorithm>(1.0f);
    auto axis = Axis::FREE;
    auto selfSize = SizeF(1.0f, 1.0f);
    frameNode_ = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ScrollPattern>(); });
    RefPtr<LayoutWrapperNode> layoutWrapper = frameNode_->CreateLayoutWrapper(false, false);
    ASSERT_NE(layoutWrapper, nullptr);
    auto scrollNode = layoutWrapper->GetHostNode();
    ASSERT_NE(scrollNode, nullptr);
    auto scrollPattern = scrollNode->GetPattern<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    scrollPattern->isInitialized_ = true;
    LayoutWrapper* rawPtr = &(*layoutWrapper);
    ASSERT_NE(rawPtr, nullptr);
    scrollLayoutAlgorithm->UseInitialOffset(axis, selfSize, rawPtr);
    EXPECT_EQ(scrollLayoutAlgorithm->GetCurrentOffset(), 1.0f);
}

/**
 * @tc.name: SuggestOpIncActivatedOnce001
 * @tc.desc: Test SuggestOpIncActivatedOnce
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, SuggestOpIncActivatedOnce001, TestSize.Level1)
{
    CreateScroll();
    CreateContent();
    CreateScrollDone();

    FlushUITasks();
    EXPECT_FALSE(frameNode_->GetSuggestOpIncActivatedOnce());
}

/**
 * @tc.name: UpdateScrollAlignment001
 * @tc.desc: Test ScrollLayoutAlgorithm UpdateScrollAlignment
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModelNGTestNg, UpdateScrollAlignment001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ScrollLayoutAlgorithm scrollLayoutAlgorithm(2.0f);

    /**
     * @tc.steps: step2. Set scrollAlignment to TOP_LEFT
     */
    Alignment scrollAlignment = Alignment::TOP_LEFT;

    /**
     * @tc.steps: step3. Calling the UpdateScrollAlignment function
     * @tc.expected: The scrollAlignment to be TOP_RIGHT
     */
    scrollLayoutAlgorithm.UpdateScrollAlignment(scrollAlignment);
    EXPECT_EQ(scrollAlignment, Alignment::TOP_RIGHT);
}

/**
 * @tc.name: UpdateScrollAlignment002
 * @tc.desc: Test ScrollLayoutAlgorithm UpdateScrollAlignment
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModelNGTestNg, UpdateScrollAlignment002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ScrollLayoutAlgorithm scrollLayoutAlgorithm(2.0f);

    /**
     * @tc.steps: step2. Set scrollAlignment to TOP_RIGHT
     */
    Alignment scrollAlignment = Alignment::TOP_RIGHT;

    /**
     * @tc.steps: step3. Calling the UpdateScrollAlignment function
     * @tc.expected: The scrollAlignment to be TOP_LEFT
     */
    scrollLayoutAlgorithm.UpdateScrollAlignment(scrollAlignment);
    EXPECT_EQ(scrollAlignment, Alignment::TOP_LEFT);
}

/**
 * @tc.name: UpdateScrollAlignment003
 * @tc.desc: Test ScrollLayoutAlgorithm UpdateScrollAlignment
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModelNGTestNg, UpdateScrollAlignment003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ScrollLayoutAlgorithm scrollLayoutAlgorithm(2.0f);

    /**
     * @tc.steps: step2. Set scrollAlignment to BOTTOM_LEFT
     */
    Alignment scrollAlignment = Alignment::BOTTOM_LEFT;

    /**
     * @tc.steps: step3. Calling the UpdateScrollAlignment function
     * @tc.expected: The scrollAlignment to be BOTTOM_RIGHT
     */
    scrollLayoutAlgorithm.UpdateScrollAlignment(scrollAlignment);
    EXPECT_EQ(scrollAlignment, Alignment::BOTTOM_RIGHT);
}

/**
 * @tc.name: UpdateScrollAlignment004
 * @tc.desc: Test ScrollLayoutAlgorithm UpdateScrollAlignment
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModelNGTestNg, UpdateScrollAlignment004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ScrollLayoutAlgorithm scrollLayoutAlgorithm(2.0f);

    /**
     * @tc.steps: step2. Set scrollAlignment to BOTTOM_RIGHT
     */
    Alignment scrollAlignment = Alignment::BOTTOM_RIGHT;

    /**
     * @tc.steps: step3. Calling the UpdateScrollAlignment function
     * @tc.expected: The scrollAlignment to be BOTTOM_LEFT
     */
    scrollLayoutAlgorithm.UpdateScrollAlignment(scrollAlignment);
    EXPECT_EQ(scrollAlignment, Alignment::BOTTOM_LEFT);
}

/**
 * @tc.name: UpdateScrollAlignment005
 * @tc.desc: Test ScrollLayoutAlgorithm UpdateScrollAlignment
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModelNGTestNg, UpdateScrollAlignment005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ScrollLayoutAlgorithm scrollLayoutAlgorithm(2.0f);

    /**
     * @tc.steps: step2. Set scrollAlignment to CENTER_RIGHT
     */
    Alignment scrollAlignment = Alignment::CENTER_RIGHT;

    /**
     * @tc.steps: step3. Calling the UpdateScrollAlignment function
     * @tc.expected: The scrollAlignment to be CENTER_LEFT
     */
    scrollLayoutAlgorithm.UpdateScrollAlignment(scrollAlignment);
    EXPECT_EQ(scrollAlignment, Alignment::CENTER_LEFT);
}

/**
 * @tc.name: UpdateScrollAlignment006
 * @tc.desc: Test ScrollLayoutAlgorithm UpdateScrollAlignment
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModelNGTestNg, UpdateScrollAlignment006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ScrollLayoutAlgorithm scrollLayoutAlgorithm(2.0f);

    /**
     * @tc.steps: step2. Set scrollAlignment to CENTER_LEFT
     */
    Alignment scrollAlignment = Alignment::CENTER_LEFT;

    /**
     * @tc.steps: step3. Calling the UpdateScrollAlignment function
     * @tc.expected: The scrollAlignment to be CENTER_RIGHT
     */
    scrollLayoutAlgorithm.UpdateScrollAlignment(scrollAlignment);
    EXPECT_EQ(scrollAlignment, Alignment::CENTER_RIGHT);
}

/**
 * @tc.name: OnSurfaceChanged001
 * @tc.desc: Test ScrollLayoutAlgorithm OnSurfaceChanged
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, OnSurfaceChanged001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     * Set currentFocus_ of focusHub to false
     */
    auto scrollLayoutAlgorithm = AceType::MakeRefPtr<ScrollLayoutAlgorithm>(2.0f);
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    WeakPtr<FrameNode> hostNode = std::move(frameNode);
    RefPtr<FocusHub> focusHub = AceType::MakeRefPtr<FocusHub>(hostNode);
    frameNode->GetOrCreateFocusHub()->SetCurrentFocus(false);
    RefPtr<LayoutWrapperNode> layoutWrapper = frameNode->CreateLayoutWrapper(false, false);
    layoutWrapper->hostNode_ = hostNode;

    /**
     * @tc.steps: step2. Set currentOffset_ to 4
     */
    scrollLayoutAlgorithm->currentOffset_ = 4.0f;

    /**
     * @tc.steps: step3. Set contentMainSize to 2
     * @tc.expected: The currentOffset is unchanged
     */
    scrollLayoutAlgorithm->OnSurfaceChanged(AceType::RawPtr(layoutWrapper), 2.0f);
    EXPECT_EQ(scrollLayoutAlgorithm->currentOffset_, 4.0f);
}

/**
 * @tc.name: OnSurfaceChanged002
 * @tc.desc: Test ScrollLayoutAlgorithm OnSurfaceChanged
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, OnSurfaceChanged002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     * Set currentFocus_ of focusHub to true
     */
    auto scrollLayoutAlgorithm = AceType::MakeRefPtr<ScrollLayoutAlgorithm>(2.0f);
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<TextFieldPattern> textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    auto textFieldNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 3, textFieldPattern);
    ASSERT_NE(textFieldNode, nullptr);
    textFieldPattern->frameNode_ = textFieldNode;
    RefPtr<PipelineContext> pipe = AceType::MakeRefPtr<PipelineContext>();
    RefPtr<TextFieldManagerNG> manager = AceType::MakeRefPtr<TextFieldManagerNG>();
    manager->onFocusTextField_ = textFieldPattern;
    pipe->SetTextFieldManager(manager);
    auto context = AceType::RawPtr(pipe);
    frameNode->context_ = context;
    WeakPtr<FrameNode> hostNode = std::move(frameNode);
    RefPtr<FocusHub> focusHub = AceType::MakeRefPtr<FocusHub>(hostNode);
    frameNode->GetOrCreateFocusHub()->SetCurrentFocus(true);
    RefPtr<LayoutWrapperNode> layoutWrapper = frameNode->CreateLayoutWrapper(false, false);
    layoutWrapper->hostNode_ = hostNode;

    /**
     * @tc.steps: step2. Set currentOffset_ to 4
     */
    scrollLayoutAlgorithm->currentOffset_ = 4.0f;

    /**
     * @tc.steps: step3. Set contentMainSize to 10
     * @tc.expected: The currentOffset to be -10
     */
    scrollLayoutAlgorithm->OnSurfaceChanged(AceType::RawPtr(layoutWrapper), 10.0f);
    frameNode->context_ = nullptr;
    EXPECT_EQ(scrollLayoutAlgorithm->currentOffset_, -10.0f);
}

/**
 * @tc.name: OnSurfaceChanged003
 * @tc.desc: Test ScrollLayoutAlgorithm OnSurfaceChanged
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, OnSurfaceChanged003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     * Set currentFocus_ of focusHub to true
     */
    auto scrollLayoutAlgorithm = AceType::MakeRefPtr<ScrollLayoutAlgorithm>(2.0f);
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<TextFieldPattern> textFieldPattern = AceType::MakeRefPtr<TextFieldPattern>();
    auto textFieldNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 3, textFieldPattern);
    ASSERT_NE(textFieldNode, nullptr);
    textFieldPattern->frameNode_ = textFieldNode;
    RefPtr<PipelineContext> pipe = AceType::MakeRefPtr<PipelineContext>();
    RefPtr<TextFieldManagerNG> manager = AceType::MakeRefPtr<TextFieldManagerNG>();
    manager->onFocusTextField_ = textFieldPattern;
    pipe->SetTextFieldManager(manager);
    auto context = AceType::RawPtr(pipe);
    frameNode->context_ = context;
    WeakPtr<FrameNode> hostNode = std::move(frameNode);
    RefPtr<FocusHub> focusHub = AceType::MakeRefPtr<FocusHub>(hostNode);
    frameNode->GetOrCreateFocusHub()->SetCurrentFocus(true);
    RefPtr<LayoutWrapperNode> layoutWrapper = frameNode->CreateLayoutWrapper(false, false);
    layoutWrapper->hostNode_ = hostNode;

    /**
     * @tc.steps: step2. Set currentOffset_ to 4
     */
    scrollLayoutAlgorithm->currentOffset_ = 4.0f;

    /**
     * @tc.steps: step3. Set contentMainSize to 50
     * @tc.expected: The currentOffset is unchanged
     */
    scrollLayoutAlgorithm->OnSurfaceChanged(AceType::RawPtr(layoutWrapper), 50.0f);
    frameNode->context_ = nullptr;
    EXPECT_EQ(scrollLayoutAlgorithm->currentOffset_, 4.0f);
}

/**
 * @tc.name: UseInitialOffset_001
 * @tc.desc: Test ScrollLayoutAlgorithm UseInitialOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, UseInitialOffset_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    auto scrollLayoutAlgorithm = AceType::MakeRefPtr<ScrollLayoutAlgorithm>(2.0f);
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    WeakPtr<FrameNode> hostNode = std::move(frameNode);
    RefPtr<LayoutWrapperNode> layoutWrapper = frameNode->CreateLayoutWrapper(false, false);
    layoutWrapper->hostNode_ = hostNode;

    /**
     * @tc.steps: step2. Set isInitialized_ to false and initialOffset_
     * set currentOffset_ to 2
     */
    scrollPattern->isInitialized_ = false;
    scrollPattern->initialOffset_ = OffsetT<CalcDimension>(CalcDimension(2.0), CalcDimension(4.0));
    scrollLayoutAlgorithm->currentOffset_ = 2.0f;

    /**
     * @tc.steps: step3. Set axis to VERTICAL and selfSize
     * @tc.expected: The currentOffset to be -4
     */
    auto axis = Axis::VERTICAL;
    auto selfSize = SizeF(1.0f, 2.0f);
    scrollLayoutAlgorithm->UseInitialOffset(axis, selfSize, AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(scrollLayoutAlgorithm->GetCurrentOffset(), -4.0f);
}

/**
 * @tc.name: UseInitialOffset_002
 * @tc.desc: Test ScrollLayoutAlgorithm UseInitialOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, UseInitialOffset_002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    auto scrollLayoutAlgorithm = AceType::MakeRefPtr<ScrollLayoutAlgorithm>(2.0f);
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    WeakPtr<FrameNode> hostNode = std::move(frameNode);
    RefPtr<LayoutWrapperNode> layoutWrapper = frameNode->CreateLayoutWrapper(false, false);
    layoutWrapper->hostNode_ = hostNode;

    /**
     * @tc.steps: step2. Set isInitialized_ to false and initialOffset_
     * set currentOffset_ to 4 and crossOffset_ to 3
     */
    scrollPattern->isInitialized_ = false;
    scrollPattern->initialOffset_ =
        OffsetT<CalcDimension>(CalcDimension(2.0, DimensionUnit::PERCENT), CalcDimension(4.0, DimensionUnit::PERCENT));
    scrollLayoutAlgorithm->currentOffset_ = 4.0f;
    scrollLayoutAlgorithm->crossOffset_ = 3.0f;

    /**
     * @tc.steps: step3. Set axis to FREE and selfSize
     * @tc.expected: The currentOffset to be -2 and crossOffset_ to be -8
     */
    auto axis = Axis::FREE;
    auto selfSize = SizeF(1.0f, 2.0f);
    scrollLayoutAlgorithm->UseInitialOffset(axis, selfSize, AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(scrollLayoutAlgorithm->GetCurrentOffset(), -2.0f);
    EXPECT_EQ(scrollLayoutAlgorithm->GetFreeOffset().GetY(), -8.0f);
}

/**
 * @tc.name: UseInitialOffset_003
 * @tc.desc: Test ScrollLayoutAlgorithm UseInitialOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, UseInitialOffset_003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    auto scrollLayoutAlgorithm = AceType::MakeRefPtr<ScrollLayoutAlgorithm>(2.0f);
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    WeakPtr<FrameNode> hostNode = std::move(frameNode);
    RefPtr<LayoutWrapperNode> layoutWrapper = frameNode->CreateLayoutWrapper(false, false);
    layoutWrapper->hostNode_ = hostNode;

    /**
     * @tc.steps: step2. Set isInitialized_ to false and initialOffset_
     * set currentOffset_ to 4
     */
    scrollPattern->isInitialized_ = false;
    scrollPattern->initialOffset_ =
        OffsetT<CalcDimension>(CalcDimension(2.0, DimensionUnit::PERCENT), CalcDimension(4.0, DimensionUnit::PERCENT));
    scrollLayoutAlgorithm->currentOffset_ = 4.0f;

    /**
     * @tc.steps: step3. Set axis to HORIZONTAL and selfSize
     * @tc.expected: The currentOffset to be -8
     */
    auto axis = Axis::HORIZONTAL;
    auto selfSize = SizeF(4.0f, 2.0f);
    scrollLayoutAlgorithm->UseInitialOffset(axis, selfSize, AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(scrollLayoutAlgorithm->GetCurrentOffset(), -8.0f);
}

/**
 * @tc.name: UseInitialOffset_004
 * @tc.desc: Test ScrollLayoutAlgorithm UseInitialOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, UseInitialOffset_004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    auto scrollLayoutAlgorithm = AceType::MakeRefPtr<ScrollLayoutAlgorithm>(2.0f);
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    WeakPtr<FrameNode> hostNode = std::move(frameNode);
    RefPtr<LayoutWrapperNode> layoutWrapper = frameNode->CreateLayoutWrapper(false, false);
    layoutWrapper->hostNode_ = hostNode;

    /**
     * @tc.steps: step2. Set isInitialized_ to true and initialOffset_
     * set currentOffset_ to 4
     */
    scrollPattern->isInitialized_ = true;
    scrollPattern->initialOffset_ =
        OffsetT<CalcDimension>(CalcDimension(2.0, DimensionUnit::PERCENT), CalcDimension(4.0, DimensionUnit::PERCENT));
    scrollLayoutAlgorithm->currentOffset_ = 4.0f;

    /**
     * @tc.steps: step3. Set axis to NONE and selfSize
     * @tc.expected: The currentOffset is unchanged
     */
    auto axis = Axis::NONE;
    auto selfSize = SizeF(4.0f, 2.0f);
    scrollLayoutAlgorithm->UseInitialOffset(axis, selfSize, AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(scrollLayoutAlgorithm->GetCurrentOffset(), 4.0f);
}

/**
 * @tc.name: AdjustCurrentOffset_001
 * @tc.desc: Test adjusting currentOffset when scrollable distance changes
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, AdjustCurrentOffset_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    CreateScroll();
    CreateContent(500.f);
    CreateScrollDone();
    auto contentNode = GetChildFrameNode(frameNode_, 0);
    RefPtr<LayoutWrapperNode> layoutWrapper = frameNode_->CreateLayoutWrapper(false, false);
    layoutWrapper->hostNode_ = frameNode_;
    pattern_->currentOffset_ = -80.0f;
    auto scrollLayoutAlgorithm = pattern_->CreateLayoutAlgorithm();

    /**
     * @tc.steps: step2. initial layout
     */
    FlushUITasks();
    EXPECT_EQ(pattern_->currentOffset_, -80.0f);
    EXPECT_EQ(pattern_->scrollableDistance_, 100.0f);

    /**
     * @tc.steps: step3. reduce content main size, but current offset is still less than scrollable distance
     * @tc.expected: current offset doesn't change
     */
    ViewAbstract::SetHeight(AceType::RawPtr(contentNode), CalcLength(490.0f));
    FlushUITasks();
    EXPECT_EQ(pattern_->currentOffset_, -80.0f);
    EXPECT_EQ(pattern_->scrollableDistance_, 90.0f);

    /**
     * @tc.steps: step4. reduce content main size, but current offset is greater than scrollable distance
     * @tc.expected: current offset change to be equal scrollable distance
     */
    ViewAbstract::SetHeight(AceType::RawPtr(contentNode), CalcLength(450.0f));
    FlushUITasks();
    EXPECT_EQ(pattern_->currentOffset_, -50.0f);
    EXPECT_EQ(pattern_->scrollableDistance_, 50.0f);
}

/**
 * @tc.name: ContentOffset001
 * @tc.desc: Test Scroll ContentStartOffset and ContentEndOffset.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, ContentOffset001, TestSize.Level1)
{
    CreateScroll();
    ScrollableModelNG::SetContentStartOffset(20);
    ScrollableModelNG::SetContentEndOffset(20);
    CreateContent();
    CreateScrollDone();

    EXPECT_EQ(layoutProperty_->GetContentStartOffset(), 20);
    EXPECT_EQ(layoutProperty_->GetContentEndOffset(), 20);
}

/**
 * @tc.name: ContentOffset002
 * @tc.desc: Test Scroll scrollableDistance with ContentStartOffset and ContentEndOffset.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, ContentOffset002, TestSize.Level1)
{
    CreateScroll();
    ScrollableModelNG::SetContentStartOffset(20);
    ScrollableModelNG::SetContentEndOffset(20);
    CreateContent();
    CreateScrollDone();

    EXPECT_EQ(layoutProperty_->GetContentStartOffset(), 20);
    EXPECT_EQ(layoutProperty_->GetContentEndOffset(), 20);
    EXPECT_EQ(pattern_->scrollableDistance_, CONTENT_MAIN_SIZE - HEIGHT + 20 + 20);
}

/**
 * @tc.name: ContentOffset003
 * @tc.desc: Test Scroll ContentStartOffset and ContentEndOffset with illegle value
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, ContentOffset003, TestSize.Level1)
{
    CreateScroll();
    ScrollableModelNG::SetContentStartOffset(HEIGHT/2);
    ScrollableModelNG::SetContentEndOffset(HEIGHT/2);
    CreateContent();
    CreateScrollDone();

    EXPECT_EQ(pattern_->contentEndOffset_, 0);
    EXPECT_EQ(pattern_->contentStartOffset_, 0);
    EXPECT_EQ(pattern_->scrollableDistance_, CONTENT_MAIN_SIZE - HEIGHT);
}

/**
 * @tc.name: ContentOffset004
 * @tc.desc: Test Scroll ContentStartOffset and ContentEndOffset with ReachStart
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, ContentOffset004, TestSize.Level1)
{
    CreateScroll();
    float contentOffset = 20;
    ScrollableModelNG::SetContentStartOffset(contentOffset);
    ScrollableModelNG::SetContentEndOffset(contentOffset);
    CreateContent();
    CreateScrollDone();

    EXPECT_EQ(pattern_->currentOffset_, 0.0f);
    EXPECT_EQ(pattern_->GetTotalOffset(), -20.f);
    EXPECT_TRUE(pattern_->IsAtTop());
    EXPECT_FALSE(pattern_->IsAtBottom());

    pattern_->ScrollBy(0, -640, false);
    FlushUITasks();
    EXPECT_EQ(pattern_->currentOffset_, -640.f);
    EXPECT_EQ(pattern_->GetTotalOffset(), 620.f);
    EXPECT_FALSE(pattern_->IsAtTop());
    EXPECT_TRUE(pattern_->IsAtBottom());
}

/**
 * @tc.name: ContentOffset005
 * @tc.desc: Test Scroll ContentStartOffset and ContentEndOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, ContentOffset005, TestSize.Level1)
{
    CreateScroll();
    ScrollableModelNG::SetContentStartOffset(HEIGHT/2);
    ScrollableModelNG::SetContentEndOffset(HEIGHT/2);
    CreateContent();
    CreateScrollDone();

    EXPECT_EQ(pattern_->contentEndOffset_, 0);
    EXPECT_EQ(pattern_->contentStartOffset_, 0);
    EXPECT_EQ(pattern_->scrollableDistance_, CONTENT_MAIN_SIZE - HEIGHT);
}

/**
 * @tc.name: ContentOffset005
 * @tc.desc: Test Scroll ContentStartOffset and ContentEndOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollLayoutTestNg, ContentOffset006, TestSize.Level1)
{
    int32_t isToEdge = 0;
    int32_t isReachStart = 0;
    int32_t isReachEnd = 0;
    NG::ScrollEdgeEvent scrollEdgeEvent = [&isToEdge](ScrollEdge) { isToEdge++; };
    auto reachStartEvent = [&isReachStart]() { isReachStart++; };
    auto reachEndEvent = [&isReachEnd]() { isReachEnd++; };
    ScrollModelNG model = CreateScroll();
    model.SetAxis(Axis::VERTICAL);
    model.SetOnScrollEdge(std::move(scrollEdgeEvent));
    model.SetOnReachStart(std::move(reachStartEvent));
    model.SetOnReachEnd(std::move(reachEndEvent));
    float contentOffset = 20;
    ScrollableModelNG::SetContentStartOffset(contentOffset);
    ScrollableModelNG::SetContentEndOffset(contentOffset * 1.5);
    CreateContent();
    CreateScrollDone();

    /**
     * @tc.steps: step1. Trigger reachStartEvent init
     */
    EXPECT_EQ(isReachStart, 1);
    EXPECT_EQ(isReachEnd, 0);
    EXPECT_EQ(isToEdge, 0);
    EXPECT_EQ(pattern_->GetTotalOffset(), -20.0f);
    EXPECT_EQ(pattern_->currentOffset_, 0.0f);
    EXPECT_EQ(isReachStart, 1);

    /**
     * @tc.steps: step2. ScrollTo 0
     * @tc.expected: totalOffset and currentOffset is correct
     */
    ScrollTo(0);
    FlushUITasks();
    EXPECT_EQ(pattern_->GetTotalOffset(), -20.0f);
    EXPECT_EQ(pattern_->currentOffset_, 0.0f);

    /**
     * @tc.steps: step2. ScrollTo bottom
     * @tc.expected: Trigger scrollEdgeEvent/reachEndEvent
     */
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    EXPECT_EQ(pattern_->GetTotalOffset(), 630.0f);
    EXPECT_EQ(isReachEnd, 1);
    EXPECT_EQ(isToEdge, 1);

    ScrollBy(0, 10);
    EXPECT_EQ(pattern_->GetTotalOffset(), 620.0f);

    ScrollBy(0, -10);
    EXPECT_EQ(pattern_->GetTotalOffset(), 630.0f);
    EXPECT_EQ(isReachEnd, 2);
    EXPECT_EQ(isToEdge, 2);

    /**
     * @tc.steps: step3. ScrollTo top
     * @tc.expected: Trigger onScrollEvent/scrollEdgeEvent/reachStartEvent
     */
    ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);
    EXPECT_EQ(isReachStart, 2);
    EXPECT_EQ(isReachEnd, 2);
    EXPECT_EQ(isToEdge, 3);
}
} // namespace OHOS::Ace::NG
