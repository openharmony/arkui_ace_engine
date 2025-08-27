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

#include "test/unittest/core/pattern/test_ng.h"

#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_event_hub.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;

class ScrollableTestNg : public TestNG {
public:
};

/**
 * @tc.name: GetEdgeEffectDumpInfo001
 * @tc.desc: Test ScrollablePattern GetEdgeEffectDumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, GetEdgeEffectDumpInfo001, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    RefPtr<ScrollablePattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    scrollablePattern->edgeEffect_ = EdgeEffect::NONE;
    scrollablePattern->GetEdgeEffectDumpInfo();
    EXPECT_EQ(DumpLog::GetInstance().description_[0], "edgeEffect: NONE\n");
}

/**
 * @tc.name: GetEdgeEffectDumpInfo002
 * @tc.desc: Test ScrollablePattern GetEdgeEffectDumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, GetEdgeEffectDumpInfo002, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    RefPtr<ScrollablePattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    scrollablePattern->edgeEffect_ = EdgeEffect::SPRING;
    scrollablePattern->GetEdgeEffectDumpInfo();
    EXPECT_EQ(DumpLog::GetInstance().description_[0], "edgeEffect: SPRING\n");
}

/**
 * @tc.name: GetEdgeEffectDumpInfo003
 * @tc.desc: Test ScrollablePattern GetEdgeEffectDumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, GetEdgeEffectDumpInfo003, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    RefPtr<ScrollablePattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    scrollablePattern->edgeEffect_ = EdgeEffect::FADE;
    scrollablePattern->GetEdgeEffectDumpInfo();
    EXPECT_EQ(DumpLog::GetInstance().description_[0], "edgeEffect: FADE\n");
}

/**
 * @tc.name: GetEdgeEffectDumpInfo004
 * @tc.desc: Test ScrollablePattern GetEdgeEffectDumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, GetEdgeEffectDumpInfo004, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    RefPtr<ScrollablePattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    int32_t number = 6;
    scrollablePattern->edgeEffect_ = static_cast<EdgeEffect>(number);
    scrollablePattern->GetEdgeEffectDumpInfo();
    EXPECT_NE(DumpLog::GetInstance().description_[0], "edgeEffect: SPRING\n");
}

/**
 * @tc.name: GetAxisDumpInfo001
 * @tc.desc: Test ScrollablePattern GetAxisDumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, GetAxisDumpInfo001, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    RefPtr<ScrollablePattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    scrollablePattern->axis_ = Axis::NONE;
    scrollablePattern->GetAxisDumpInfo();
    EXPECT_EQ(DumpLog::GetInstance().description_[0], "Axis: NONE\n");
}

/**
 * @tc.name: GetAxisDumpInfo002
 * @tc.desc: Test ScrollablePattern GetAxisDumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, GetAxisDumpInfo002, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    RefPtr<ScrollablePattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    scrollablePattern->axis_ = Axis::VERTICAL;
    scrollablePattern->GetAxisDumpInfo();
    EXPECT_EQ(DumpLog::GetInstance().description_[0], "Axis: VERTICAL\n");
}

/**
 * @tc.name: GetAxisDumpInfo003
 * @tc.desc: Test ScrollablePattern GetAxisDumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, GetAxisDumpInfo003, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    RefPtr<ScrollablePattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    scrollablePattern->axis_ = Axis::HORIZONTAL;
    scrollablePattern->GetAxisDumpInfo();
    EXPECT_EQ(DumpLog::GetInstance().description_[0], "Axis: HORIZONTAL\n");
}

/**
 * @tc.name: GetAxisDumpInfo004
 * @tc.desc: Test ScrollablePattern GetAxisDumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, GetAxisDumpInfo004, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    RefPtr<ScrollablePattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    scrollablePattern->axis_ = Axis::FREE;
    scrollablePattern->GetAxisDumpInfo();
    EXPECT_EQ(DumpLog::GetInstance().description_[0], "Axis: FREE\n");
}

/**
 * @tc.name: GetAxisDumpInfo005
 * @tc.desc: Test ScrollablePattern GetAxisDumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, GetAxisDumpInfo005, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    RefPtr<ScrollablePattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    int32_t number = 6;
    scrollablePattern->axis_ = static_cast<Axis>(number);
    scrollablePattern->GetAxisDumpInfo();
    EXPECT_NE(DumpLog::GetInstance().description_[0], "Axis: VERTICAL\n");
}

/**
 * @tc.name: GetPanDirectionDumpInfo001
 * @tc.desc: Test ScrollablePattern GetPanDirectionDumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, GetPanDirectionDumpInfo001, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    RefPtr<ScrollablePattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    scrollablePattern->axis_ = Axis::NONE;
    RefPtr<ScrollableEvent> scrollableEvent = AceType::MakeRefPtr<ScrollableEvent>(Axis::NONE);
    scrollablePattern->scrollableEvent_ = scrollableEvent;
    ScrollPositionCallback callback = [](double value, int32_t source) {
        value = 2.F;
        source = 1;
        return false;
    };
    RefPtr<Scrollable> scrollable = AceType::MakeRefPtr<Scrollable>(callback, Axis::NONE);
    scrollablePattern->scrollableEvent_->scrollable_ = scrollable;
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<NG::PanRecognizer> panRecognizerNG = AceType::MakeRefPtr<NG::PanRecognizer>(panGestureOption);
    scrollable->panRecognizerNG_ = panRecognizerNG;
    panRecognizerNG->direction_.type = PanDirection::NONE;
    scrollablePattern->GetPanDirectionDumpInfo();
    EXPECT_EQ(DumpLog::GetInstance().description_[0], "ScrollablePanDirection:NONE\n");
}

/**
 * @tc.name: GetPanDirectionDumpInfo002
 * @tc.desc: Test ScrollablePattern GetPanDirectionDumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, GetPanDirectionDumpInfo002, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    RefPtr<ScrollablePattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    scrollablePattern->axis_ = Axis::NONE;
    RefPtr<ScrollableEvent> scrollableEvent = AceType::MakeRefPtr<ScrollableEvent>(Axis::NONE);
    scrollablePattern->scrollableEvent_ = scrollableEvent;
    ScrollPositionCallback callback = [](double value, int32_t source) {
        value = 2.F;
        source = 1;
        return false;
    };
    RefPtr<Scrollable> scrollable = AceType::MakeRefPtr<Scrollable>(callback, Axis::NONE);
    scrollablePattern->scrollableEvent_->scrollable_ = scrollable;
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<NG::PanRecognizer> panRecognizerNG = AceType::MakeRefPtr<NG::PanRecognizer>(panGestureOption);
    scrollable->panRecognizerNG_ = panRecognizerNG;
    panRecognizerNG->direction_.type = PanDirection::VERTICAL;
    scrollablePattern->GetPanDirectionDumpInfo();
    EXPECT_EQ(DumpLog::GetInstance().description_[0], "ScrollablePanDirection:VERTICAL\n");
}

/**
 * @tc.name: GetPanDirectionDumpInfo003
 * @tc.desc: Test ScrollablePattern GetPanDirectionDumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, GetPanDirectionDumpInfo003, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    RefPtr<ScrollablePattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    scrollablePattern->axis_ = Axis::NONE;
    RefPtr<ScrollableEvent> scrollableEvent = AceType::MakeRefPtr<ScrollableEvent>(Axis::NONE);
    scrollablePattern->scrollableEvent_ = scrollableEvent;
    ScrollPositionCallback callback = [](double value, int32_t source) {
        value = 2.F;
        source = 1;
        return false;
    };
    RefPtr<Scrollable> scrollable = AceType::MakeRefPtr<Scrollable>(callback, Axis::NONE);
    scrollablePattern->scrollableEvent_->scrollable_ = scrollable;
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<NG::PanRecognizer> panRecognizerNG = AceType::MakeRefPtr<NG::PanRecognizer>(panGestureOption);
    scrollable->panRecognizerNG_ = panRecognizerNG;
    panRecognizerNG->direction_.type = PanDirection::HORIZONTAL;
    scrollablePattern->GetPanDirectionDumpInfo();
    EXPECT_EQ(DumpLog::GetInstance().description_[0], "ScrollablePanDirection:HORIZONTAL\n");
}

/**
 * @tc.name: GetPanDirectionDumpInfo004
 * @tc.desc: Test ScrollablePattern GetPanDirectionDumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, GetPanDirectionDumpInfo004, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    RefPtr<ScrollablePattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    scrollablePattern->axis_ = Axis::NONE;
    RefPtr<ScrollableEvent> scrollableEvent = AceType::MakeRefPtr<ScrollableEvent>(Axis::NONE);
    scrollablePattern->scrollableEvent_ = scrollableEvent;
    ScrollPositionCallback callback = [](double value, int32_t source) {
        value = 2.F;
        source = 1;
        return false;
    };
    RefPtr<Scrollable> scrollable = AceType::MakeRefPtr<Scrollable>(callback, Axis::NONE);
    scrollablePattern->scrollableEvent_->scrollable_ = scrollable;
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<NG::PanRecognizer> panRecognizerNG = AceType::MakeRefPtr<NG::PanRecognizer>(panGestureOption);
    scrollable->panRecognizerNG_ = panRecognizerNG;
    panRecognizerNG->direction_.type = PanDirection::ALL;
    scrollablePattern->GetPanDirectionDumpInfo();
    EXPECT_EQ(DumpLog::GetInstance().description_[0], "ScrollablePanDirection:FREE\n");
}

/**
 * @tc.name: GetPaintPropertyDumpInfo001
 * @tc.desc: Test ScrollablePattern GetPaintPropertyDumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, GetPaintPropertyDumpInfo001, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    RefPtr<ScrollablePattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    ASSERT_NE(scrollablePattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, scrollablePattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<PaintProperty> paintProperty = AceType::MakeRefPtr<ScrollablePaintProperty>();
    frameNode->paintProperty_ = paintProperty;
    scrollablePattern->frameNode_ = frameNode;
    scrollablePattern->GetPaintPropertyDumpInfo();
    EXPECT_EQ(DumpLog::GetInstance().description_[0], "innerScrollBarState: OFF\n");
}

/**
 * @tc.name: GetPaintPropertyDumpInfo002
 * @tc.desc: Test ScrollablePattern GetPaintPropertyDumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, GetPaintPropertyDumpInfo002, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    RefPtr<ScrollablePattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    ASSERT_NE(scrollablePattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, scrollablePattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<PaintProperty> paintProperty = AceType::MakeRefPtr<ScrollablePaintProperty>();
    frameNode->paintProperty_ = paintProperty;
    scrollablePattern->frameNode_ = frameNode;
    scrollablePattern->GetPaintPropertyDumpInfo();
    EXPECT_EQ(DumpLog::GetInstance().description_.size(), 2);
    EXPECT_EQ(DumpLog::GetInstance().description_[0], "innerScrollBarState: OFF\n");
    EXPECT_EQ(DumpLog::GetInstance().description_[1], "scrollBarWidth: None\n");
}

/**
 * @tc.name: GetEventDumpInfo001
 * @tc.desc: Test ScrollBarPattern GetEventDumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, GetEventDumpInfo001, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    RefPtr<ScrollablePattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    ASSERT_NE(scrollablePattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, scrollablePattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<ScrollEventHub> eventHub = AceType::MakeRefPtr<ScrollEventHub>();
    eventHub->onScrollStartEvent_ = []() {};
    eventHub->onScrollStopEvent_ = []() {};
    frameNode->eventHub_ = eventHub;
    scrollablePattern->frameNode_ = frameNode;
    scrollablePattern->GetEventDumpInfo();
    EXPECT_EQ(DumpLog::GetInstance().description_[4], "hasOnWillScroll: false\n");
}

/**
 * @tc.name: GetEventDumpInfo002
 * @tc.desc: Test ScrollBarPattern GetEventDumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, GetEventDumpInfo002, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    RefPtr<ScrollablePattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    ASSERT_NE(scrollablePattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, scrollablePattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<ScrollableEventHub> eventHub = AceType::MakeRefPtr<ScrollableEventHub>();
    eventHub->onScrollStartEvent_ = []() {};
    eventHub->onScrollStopEvent_ = []() {};
    frameNode->eventHub_ = eventHub;
    scrollablePattern->frameNode_ = frameNode;
    scrollablePattern->GetEventDumpInfo();
    EXPECT_EQ(DumpLog::GetInstance().description_[4], "hasOnWillScroll: false\n");
}

/**
 * @tc.name: GetPaintPropertyDumpInfo_Parameter001
 * @tc.desc: Test ScrollablePattern GetPaintPropertyDumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, GetPaintPropertyDumpInfo_Parameter001, TestSize.Level1)
{
    RefPtr<ScrollablePattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    ASSERT_NE(scrollablePattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, scrollablePattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<PaintProperty> paintProperty = AceType::MakeRefPtr<ScrollablePaintProperty>();
    frameNode->paintProperty_ = paintProperty;
    scrollablePattern->frameNode_ = frameNode;
    auto json = JsonUtil::Create(true);
    scrollablePattern->GetPaintPropertyDumpInfo(json);
    EXPECT_EQ(json->GetString("innerScrollBarState"), "OFF");
}

/**
 * @tc.name: GetPaintPropertyDumpInfo_Parameter002
 * @tc.desc: Test ScrollablePattern GetPaintPropertyDumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, GetPaintPropertyDumpInfo_Parameter002, TestSize.Level1)
{
    RefPtr<ScrollablePattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    ASSERT_NE(scrollablePattern, nullptr);
    auto json = JsonUtil::Create(true);
    scrollablePattern->GetPaintPropertyDumpInfo(json);
    EXPECT_NE(json->GetString("innerScrollBarState"), "OFF");
}

/**
 * @tc.name: GetAxisDumpInfo_Parameter001
 * @tc.desc: Test ScrollablePattern GetAxisDumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, GetAxisDumpInfo_Parameter001, TestSize.Level1)
{
    RefPtr<ScrollablePattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    scrollablePattern->axis_ = Axis::NONE;
    auto json = JsonUtil::Create(true);
    scrollablePattern->GetAxisDumpInfo(json);
    EXPECT_EQ(json->GetString("Axis"), "NONE");
}

/**
 * @tc.name: GetAxisDumpInfo_Parameter002
 * @tc.desc: Test ScrollablePattern GetAxisDumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, GetAxisDumpInfo_Parameter002, TestSize.Level1)
{
    RefPtr<ScrollablePattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    scrollablePattern->axis_ = Axis::VERTICAL;
    auto json = JsonUtil::Create(true);
    scrollablePattern->GetAxisDumpInfo(json);
    EXPECT_EQ(json->GetString("Axis"), "VERTICAL");
}

/**
 * @tc.name: GetAxisDumpInfo_Parameter003
 * @tc.desc: Test ScrollablePattern GetAxisDumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, GetAxisDumpInfo_Parameter003, TestSize.Level1)
{
    RefPtr<ScrollablePattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    scrollablePattern->axis_ = Axis::HORIZONTAL;
    auto json = JsonUtil::Create(true);
    scrollablePattern->GetAxisDumpInfo(json);
    EXPECT_EQ(json->GetString("Axis"), "HORIZONTAL");
}

/**
 * @tc.name: GetAxisDumpInfo_Parameter004
 * @tc.desc: Test ScrollablePattern GetAxisDumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, GetAxisDumpInfo_Parameter004, TestSize.Level1)
{
    RefPtr<ScrollablePattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    scrollablePattern->axis_ = Axis::FREE;
    auto json = JsonUtil::Create(true);
    scrollablePattern->GetAxisDumpInfo(json);
    EXPECT_EQ(json->GetString("Axis"), "FREE");
}

/**
 * @tc.name: GetAxisDumpInfo_Parameter005
 * @tc.desc: Test ScrollablePattern GetAxisDumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, GetAxisDumpInfo_Parameter005, TestSize.Level1)
{
    RefPtr<ScrollablePattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    int32_t number = 6;
    scrollablePattern->axis_ = static_cast<Axis>(number);
    auto json = JsonUtil::Create(true);
    scrollablePattern->GetAxisDumpInfo(json);
    EXPECT_NE(json->GetString("Axis"), "VERTICAL");
}

/**
 * @tc.name: GetPanDirectionDumpInfo_Parameter001
 * @tc.desc: Test ScrollablePattern GetPanDirectionDumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, GetPanDirectionDumpInfo_Parameter001, TestSize.Level1)
{
    RefPtr<ScrollablePattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    scrollablePattern->axis_ = Axis::NONE;
    RefPtr<ScrollableEvent> scrollableEvent = AceType::MakeRefPtr<ScrollableEvent>(Axis::NONE);
    scrollablePattern->scrollableEvent_ = scrollableEvent;
    ScrollPositionCallback callback = [](double value, int32_t source) {
        value = 2.F;
        source = 1;
        return false;
    };
    RefPtr<Scrollable> scrollable = AceType::MakeRefPtr<Scrollable>(callback, Axis::NONE);
    scrollablePattern->scrollableEvent_->scrollable_ = scrollable;
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<NG::PanRecognizer> panRecognizerNG = AceType::MakeRefPtr<NG::PanRecognizer>(panGestureOption);
    scrollable->panRecognizerNG_ = panRecognizerNG;
    panRecognizerNG->direction_.type = PanDirection::NONE;
    auto json = JsonUtil::Create(true);
    scrollablePattern->GetPanDirectionDumpInfo(json);
    EXPECT_EQ(json->GetString("ScrollablePanDirection"), "NONE");
}

/**
 * @tc.name: GetPanDirectionDumpInfo_Parameter002
 * @tc.desc: Test ScrollablePattern GetPanDirectionDumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, GetPanDirectionDumpInfo_Parameter002, TestSize.Level1)
{
    RefPtr<ScrollablePattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    scrollablePattern->axis_ = Axis::NONE;
    RefPtr<ScrollableEvent> scrollableEvent = AceType::MakeRefPtr<ScrollableEvent>(Axis::NONE);
    scrollablePattern->scrollableEvent_ = scrollableEvent;
    ScrollPositionCallback callback = [](double value, int32_t source) {
        value = 2.F;
        source = 1;
        return false;
    };
    RefPtr<Scrollable> scrollable = AceType::MakeRefPtr<Scrollable>(callback, Axis::NONE);
    scrollablePattern->scrollableEvent_->scrollable_ = scrollable;
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<NG::PanRecognizer> panRecognizerNG = AceType::MakeRefPtr<NG::PanRecognizer>(panGestureOption);
    scrollable->panRecognizerNG_ = panRecognizerNG;
    panRecognizerNG->direction_.type = PanDirection::VERTICAL;
    auto json = JsonUtil::Create(true);
    scrollablePattern->GetPanDirectionDumpInfo(json);
    EXPECT_EQ(json->GetString("ScrollablePanDirection"), "VERTICAL");
}

/**
 * @tc.name: GetPanDirectionDumpInfo_Parameter003
 * @tc.desc: Test ScrollablePattern GetPanDirectionDumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, GetPanDirectionDumpInfo_Parameter003, TestSize.Level1)
{
    RefPtr<ScrollablePattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    scrollablePattern->axis_ = Axis::NONE;
    RefPtr<ScrollableEvent> scrollableEvent = AceType::MakeRefPtr<ScrollableEvent>(Axis::NONE);
    scrollablePattern->scrollableEvent_ = scrollableEvent;
    ScrollPositionCallback callback = [](double value, int32_t source) {
        value = 2.F;
        source = 1;
        return false;
    };
    RefPtr<Scrollable> scrollable = AceType::MakeRefPtr<Scrollable>(callback, Axis::NONE);
    scrollablePattern->scrollableEvent_->scrollable_ = scrollable;
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<NG::PanRecognizer> panRecognizerNG = AceType::MakeRefPtr<NG::PanRecognizer>(panGestureOption);
    scrollable->panRecognizerNG_ = panRecognizerNG;
    panRecognizerNG->direction_.type = PanDirection::HORIZONTAL;
    auto json = JsonUtil::Create(true);
    scrollablePattern->GetPanDirectionDumpInfo(json);
    EXPECT_EQ(json->GetString("ScrollablePanDirection"), "HORIZONTAL");
}

/**
 * @tc.name: GetPanDirectionDumpInfo_Parameter004
 * @tc.desc: Test ScrollablePattern GetPanDirectionDumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, GetPanDirectionDumpInfo_Parameter004, TestSize.Level1)
{
    RefPtr<ScrollablePattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    scrollablePattern->axis_ = Axis::NONE;
    RefPtr<ScrollableEvent> scrollableEvent = AceType::MakeRefPtr<ScrollableEvent>(Axis::NONE);
    scrollablePattern->scrollableEvent_ = scrollableEvent;
    ScrollPositionCallback callback = [](double value, int32_t source) {
        value = 2.F;
        source = 1;
        return false;
    };
    RefPtr<Scrollable> scrollable = AceType::MakeRefPtr<Scrollable>(callback, Axis::NONE);
    scrollablePattern->scrollableEvent_->scrollable_ = scrollable;
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<NG::PanRecognizer> panRecognizerNG = AceType::MakeRefPtr<NG::PanRecognizer>(panGestureOption);
    scrollable->panRecognizerNG_ = panRecognizerNG;
    panRecognizerNG->direction_.type = PanDirection::ALL;
    auto json = JsonUtil::Create(true);
    scrollablePattern->GetPanDirectionDumpInfo(json);
    EXPECT_EQ(json->GetString("ScrollablePanDirection"), "FREE");
}

/**
 * @tc.name: GetEventDumpInfo_Parameter001
 * @tc.desc: Test ScrollBarPattern GetEventDumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, GetEventDumpInfo_Parameter001, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    RefPtr<ScrollablePattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    ASSERT_NE(scrollablePattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, scrollablePattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<ScrollEventHub> eventHub = AceType::MakeRefPtr<ScrollEventHub>();
    eventHub->onScrollStartEvent_ = []() {};
    eventHub->onScrollStopEvent_ = []() {};
    frameNode->eventHub_ = eventHub;
    scrollablePattern->frameNode_ = frameNode;
    auto json = JsonUtil::Create(true);
    scrollablePattern->GetEventDumpInfo(json);
    EXPECT_EQ(json->GetString("hasOnWillScroll"), "false");
}

/**
 * @tc.name: GetEventDumpInfo_Parameter002
 * @tc.desc: Test ScrollBarPattern GetEventDumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, GetEventDumpInfo_Parameter002, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    RefPtr<ScrollablePattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    ASSERT_NE(scrollablePattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, scrollablePattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<ScrollableEventHub> eventHub = AceType::MakeRefPtr<ScrollableEventHub>();
    eventHub->onScrollStartEvent_ = []() {};
    eventHub->onScrollStopEvent_ = []() {};
    frameNode->eventHub_ = eventHub;
    scrollablePattern->frameNode_ = frameNode;
    auto json = JsonUtil::Create(true);
    scrollablePattern->GetEventDumpInfo(json);
    EXPECT_EQ(json->GetString("hasOnWillScroll"), "false");
}

/**
 * @tc.name: DumpAdvanceInfo_Parameter001
 * @tc.desc: Test ScrollBarPattern DumpAdvanceInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, DumpAdvanceInfo_Parameter001, TestSize.Level1)
{
    RefPtr<ScrollablePattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    ASSERT_NE(scrollablePattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, scrollablePattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->nodeId_ = 5;
    frameNode->tag_ = "tag";
    scrollablePattern->frameNode_ = frameNode;
    scrollablePattern->parent_ = scrollablePattern;
    auto json = JsonUtil::Create(true);
    scrollablePattern->DumpAdvanceInfo(json);
    EXPECT_EQ(json->GetString("nestedScrollParent"), "");
}

/**
 * @tc.name: DumpAdvanceInfo_Parameter002
 * @tc.desc: Test ScrollBarPattern DumpAdvanceInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, DumpAdvanceInfo_Parameter002, TestSize.Level1)
{
    RefPtr<ScrollablePattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    ASSERT_NE(scrollablePattern, nullptr);
    scrollablePattern->parent_ = scrollablePattern;
    auto json = JsonUtil::Create(true);
    scrollablePattern->DumpAdvanceInfo(json);
    EXPECT_EQ(json->GetString("nestedScrollParent"), "null");
}

/**
 * @tc.name: DumpAdvanceInfo_Parameter003
 * @tc.desc: Test ScrollBarPattern DumpAdvanceInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, DumpAdvanceInfo_Parameter003, TestSize.Level1)
{
    RefPtr<ScrollablePattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    ASSERT_NE(scrollablePattern, nullptr);
    auto json = JsonUtil::Create(true);
    scrollablePattern->DumpAdvanceInfo(json);
    EXPECT_EQ(json->GetString("nestedScrollParent"), "null");
}

/**
 * @tc.name: DumpAdvanceInfo_Parameter004
 * @tc.desc: Test ScrollBarPattern DumpAdvanceInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, DumpAdvanceInfo_Parameter004, TestSize.Level1)
{
    RefPtr<ScrollablePattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    ASSERT_NE(scrollablePattern, nullptr);
    auto json = JsonUtil::Create(true);
    auto scrollBar = AceType::MakeRefPtr<ScrollBar>();
    scrollablePattern->scrollBar_ = scrollBar;
    scrollablePattern->scrollBar_->activeRect_ = Rect(2, 6, 5, 10);
    scrollablePattern->DumpAdvanceInfo(json);
    EXPECT_EQ(json->GetString("activeRect"), "Rect (2.00, 6.00) - [5.00 x 10.00]");
}

/**
 * @tc.name: DumpAdvanceInfo_Parameter005
 * @tc.desc: Test ScrollBarPattern DumpAdvanceInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, DumpAdvanceInfo_Parameter005, TestSize.Level1)
{
    RefPtr<ScrollablePattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    ASSERT_NE(scrollablePattern, nullptr);
    auto json = JsonUtil::Create(true);
    scrollablePattern->DumpAdvanceInfo(json);
    EXPECT_EQ(json->GetString("inner ScrollBar"), "null");
}

/**
 * @tc.name: GetEdgeEffectDumpInfo_Parameter001
 * @tc.desc: Test ScrollablePattern GetEdgeEffectDumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, GetEdgeEffectDumpInfo_Parameter001, TestSize.Level1)
{
    RefPtr<ScrollablePattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    scrollablePattern->edgeEffect_ = EdgeEffect::NONE;
    auto json = JsonUtil::Create(true);
    scrollablePattern->GetEdgeEffectDumpInfo(json);
    EXPECT_EQ(json->GetString("edgeEffect"), "NONE");
}

/**
 * @tc.name: GetEdgeEffectDumpInfo_Parameter002
 * @tc.desc: Test ScrollablePattern GetEdgeEffectDumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, GetEdgeEffectDumpInfo_Parameter002, TestSize.Level1)
{
    RefPtr<ScrollablePattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    scrollablePattern->edgeEffect_ = EdgeEffect::SPRING;
    auto json = JsonUtil::Create(true);
    scrollablePattern->GetEdgeEffectDumpInfo(json);
    EXPECT_EQ(json->GetString("edgeEffect"), "SPRING");
}

/**
 * @tc.name: GetEdgeEffectDumpInfo_Parameter003
 * @tc.desc: Test ScrollablePattern GetEdgeEffectDumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, GetEdgeEffectDumpInfo_Parameter003, TestSize.Level1)
{
    RefPtr<ScrollablePattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    scrollablePattern->edgeEffect_ = EdgeEffect::FADE;
    auto json = JsonUtil::Create(true);
    scrollablePattern->GetEdgeEffectDumpInfo(json);
    EXPECT_EQ(json->GetString("edgeEffect"), "FADE");
}

/**
 * @tc.name: GetEdgeEffectDumpInfo_Parameter004
 * @tc.desc: Test ScrollablePattern GetEdgeEffectDumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, GetEdgeEffectDumpInfo_Parameter004, TestSize.Level1)
{
    RefPtr<ScrollablePattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    int32_t number = 6;
    scrollablePattern->edgeEffect_ = static_cast<EdgeEffect>(number);
    auto json = JsonUtil::Create(true);
    scrollablePattern->GetEdgeEffectDumpInfo(json);
    EXPECT_NE(json->GetString("edgeEffect"), "SPRING");
}
} // namespace OHOS::Ace::NG