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

#include <optional>

#include "gtest/gtest.h"

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/manager/event/json_child_report.h"
#include "core/components_ng/manager/event/json_report.h"
#include "core/gestures/gesture_info.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const Point globalPoint { 100.0, 100.0 };
const int32_t id = 1;
const int32_t startId = 1;
const int32_t dropId = 2;
const Offset offset(10, 10);
const Offset offsetLocal(15, 15);
const Offset offsetGlobal(20, 20);
const FingerInfo fingerInfo = { 0, 0, offset, offsetLocal, offsetGlobal, SourceType::TOUCH, SourceTool::FINGER };
const std::list<FingerInfo> fingerList = { fingerInfo };
} // namespace

class JsonReportTestNg : public testing::Test {};
/**
 * @tc.name: JsonReportTestNgTypeTest001
 * @tc.desc: RequestJsonReport Successfully and then ExitFullScreen Successfully
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(JsonReportTestNg, JsonReportTestNgTypeTest001, TestSize.Level1)
{
    PanJsonReport panReport;
    panReport.SetPoint(globalPoint);
    panReport.SetCallbackType(GestureCallbackType::START);
    panReport.SetId(id);
    panReport.SetPanDirection(1);
    auto valueStart = panReport.GetJsonData();
    std::string JsonStrStart = valueStart->ToString().c_str();
    std::string JsonStrStart1 =
        "{\"GestureType\":\"Pan\",\"id\":1,\"action\":\"start\",\"point\":[100,100],\"direction\":1}";
    EXPECT_EQ(JsonStrStart, JsonStrStart1);
    panReport.SetCallbackType(GestureCallbackType::END);
    auto valueEnd = panReport.GetJsonData();
    std::string JsonStrEnd = valueEnd->ToString().c_str();
    std::string JsonStrEnd1 =
        "{\"GestureType\":\"Pan\",\"id\":1,\"action\":\"end\",\"point\":[100,100],\"direction\":1}";
    EXPECT_EQ(JsonStrEnd, JsonStrEnd1);
    panReport.SetCallbackType(GestureCallbackType::CANCEL);
    auto valueCancel = panReport.GetJsonData();
    std::string JsonStrCancel = valueCancel->ToString().c_str();
    std::string JsonStrCancel1 = "{\"GestureType\":\"Pan\",\"action\":\"cancel\"}";
    EXPECT_EQ(JsonStrCancel, JsonStrCancel1);
}

/**
 * @tc.name: JsonReportTestNgTypeTest002
 * @tc.desc: RequestJsonReport Successfully and then ExitFullScreen Successfully
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(JsonReportTestNg, JsonReportTestNgTypeTest002, TestSize.Level1)
{
    TapJsonReport tapReport;
    tapReport.SetPoint(globalPoint);
    tapReport.SetCount(0);
    tapReport.SetId(id);
    tapReport.SetFingerList(fingerList);
    auto value = tapReport.GetJsonData();
    std::string JsonStr = value->ToString().c_str();
    std::string JsonStr1 = "{\"GestureType\":\"Tap\",\"id\":1,\"point\":[100,100],\"count\":0,\"fingers\":1}";
    EXPECT_EQ(JsonStr, JsonStr1);
}

/**
 * @tc.name: JsonReportTestNgTypeTest003
 * @tc.desc: RequestJsonReport Successfully and then ExitFullScreen Successfully
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(JsonReportTestNg, JsonReportTestNgTypeTest003, TestSize.Level1)
{
    LongPressJsonReport longPressReport;
    longPressReport.SetPoint(globalPoint);
    longPressReport.SetId(id);
    longPressReport.SetDuration(100000000);
    auto value = longPressReport.GetJsonData();
    std::string JsonStr = value->ToString().c_str();
    std::string JsonStr1 =
        "{\"GestureType\":\"LongPress\",\"id\":1,\"action\":\"end\",\"point\":[100,100],\"actualDuration\":100}";
    EXPECT_EQ(JsonStr, JsonStr1);
}
/**
 * @tc.name: JsonReportTestNgTypeTest004
 * @tc.desc: RequestJsonReport Successfully and then ExitFullScreen Successfully
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(JsonReportTestNg, JsonReportTestNgTypeTest004, TestSize.Level1)
{
    PinchJsonReport pinchReport;
    pinchReport.SetPoint(globalPoint);
    pinchReport.SetCallbackType(GestureCallbackType::START);
    pinchReport.SetId(id);
    pinchReport.SetFingerList(fingerList);
    auto valueStart = pinchReport.GetJsonData();
    std::string JsonStrStart = valueStart->ToString().c_str();
    std::string JsonStrStart1 =
        "{\"GestureType\":\"Pinch\",\"id\":1,\"action\":\"start\",\"point\":[[10,10]],\"fingers\":1}";
    EXPECT_EQ(JsonStrStart, JsonStrStart1);
    pinchReport.SetCallbackType(GestureCallbackType::END);
    pinchReport.SetScale(1);
    auto valueEnd = pinchReport.GetJsonData();
    std::string JsonStrEnd = valueEnd->ToString().c_str();
    std::string JsonStrEnd1 =
        "{\"GestureType\":\"Pinch\",\"id\":1,\"action\":\"end\",\"point\":[[10,10]],\"fingers\":1,\"scale\":1}";
    EXPECT_EQ(JsonStrEnd, JsonStrEnd1);
    pinchReport.SetCallbackType(GestureCallbackType::CANCEL);
    auto valueCancel = pinchReport.GetJsonData();
    std::string JsonStrCancel = valueCancel->ToString().c_str();
    std::string JsonStrCancel1 = "{\"GestureType\":\"Pinch\",\"action\":\"cancel\"}";
    EXPECT_EQ(JsonStrCancel, JsonStrCancel1);
}

/**
 * @tc.name: JsonReportTestNgTypeTest005
 * @tc.desc: RequestJsonReport Successfully and then ExitFullScreen Successfully
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(JsonReportTestNg, JsonReportTestNgTypeTest005, TestSize.Level1)
{
    RotationJsonReport rotationReport;
    rotationReport.SetPoint(globalPoint);
    rotationReport.SetCallbackType(GestureCallbackType::START);
    rotationReport.SetId(id);
    rotationReport.SetFingerList(fingerList);
    auto valueStart = rotationReport.GetJsonData();
    std::string JsonStrStart = valueStart->ToString().c_str();
    std::string JsonStrStart1 =
        "{\"GestureType\":\"Rotation\",\"id\":1,\"action\":\"start\",\"point\":[[10,10]],\"fingers\":1}";
    EXPECT_EQ(JsonStrStart, JsonStrStart1);
    rotationReport.SetCallbackType(GestureCallbackType::END);
    rotationReport.SetAngle(1.0);
    auto valueEnd = rotationReport.GetJsonData();
    std::string JsonStrEnd = valueEnd->ToString().c_str();
    std::string JsonStrEnd1 =
        "{\"GestureType\":\"Rotation\",\"id\":1,\"action\":\"end\",\"point\":[[10,10]],\"fingers\":1,\"angle\":1}";
    EXPECT_EQ(JsonStrEnd, JsonStrEnd1);
    rotationReport.SetCallbackType(GestureCallbackType::CANCEL);
    auto valueCancel = rotationReport.GetJsonData();
    std::string JsonStrCancel = valueCancel->ToString().c_str();
    std::string JsonStrCancel1 = "{\"GestureType\":\"Rotation\",\"action\":\"cancel\"}";
    EXPECT_EQ(JsonStrCancel, JsonStrCancel1);
}
/**
 * @tc.name: JsonReportTestNgTypeTest006
 * @tc.desc: RequestJsonReport Successfully and then ExitFullScreen Successfully
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(JsonReportTestNg, JsonReportTestNgTypeTest006, TestSize.Level1)
{
    std::map<int32_t, TouchEvent> touchPoints_;
    std::map<int32_t, TouchEvent> touchPointsEmpty_;
    TouchEvent point;
    point.id = 1;
    point.x = 20;
    point.y = 20;
    touchPoints_[1] = point;
    SwipeJsonReport swipeReport;
    swipeReport.SetPoint(globalPoint);
    swipeReport.SetId(id);
    swipeReport.SetSwipeDirection(2);
    swipeReport.SetSpeed(1.0);
    swipeReport.SetActualSpeed(1.0);
    swipeReport.SetFingerList(fingerList);
    swipeReport.SetTouchEvents(touchPoints_);
    auto value = swipeReport.GetJsonData();
    std::string JsonStr = value->ToString().c_str();
    std::string JsonStr1 = "{\"GestureType\":\"Swipe\",\"id\":1,\"upPoint\":[[10,10]],\"downPoint\":[[20,20]],"
                           "\"direction\":2,\"speed\":0,\"actualSpeed\":0}";
    EXPECT_EQ(JsonStr, JsonStr1);
    swipeReport.SetTouchEvents(touchPointsEmpty_);
    auto value1 = swipeReport.GetJsonData();
    std::string JsonUisessionStr = value1->ToString().c_str();
    std::string JsonUisessionStr1 = "{\"GestureType\":\"Swipe\",\"id\":1,\"upPoint\":[10,10],\"downPoint\":[10,10],"
                           "\"direction\":2,\"speed\":0,\"actualSpeed\":0}";
    EXPECT_EQ(JsonUisessionStr, JsonUisessionStr1);
}
/**
 * @tc.name: JsonReportTestNgTypeTest007
 * @tc.desc: RequestJsonReport Successfully and then ExitFullScreen Successfully
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(JsonReportTestNg, JsonReportTestNgTypeTest007, TestSize.Level1)
{
    ClickJsonReport clickReport;
    clickReport.SetPoint(globalPoint);
    clickReport.SetId(id);
    clickReport.SetCount(12);
    clickReport.SetFingerList(fingerList);
    auto value = clickReport.GetJsonData();
    std::string JsonStr = value->ToString().c_str();
    std::string JsonStr1 = "{\"GestureType\":\"Click\",\"id\":1,\"point\":[100,100],\"count\":12,\"fingers\":1}";
    EXPECT_EQ(JsonStr, JsonStr1);
}
/**
 * @tc.name: JsonReportTestNgTypeTest008
 * @tc.desc: RequestJsonReport Successfully and then ExitFullScreen Successfully
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(JsonReportTestNg, JsonReportTestNgTypeTest008, TestSize.Level1)
{
    DragJsonReport dragReport;
    dragReport.SetPoint(globalPoint);
    dragReport.SetDragReporterPharse(DragReporterPharse::DRAG_START);
    dragReport.SetStartId(startId);
    dragReport.SetDropId(dropId);
    dragReport.SetHostName("test");
    dragReport.SetActualDuration(2);
    auto valueDragstart = dragReport.GetJsonData();
    std::string JsonStrDragstart = valueDragstart->ToString().c_str();
    std::string JsonStrDragstart1 =
        "{\"GestureType\":\"DragStart\",\"id\":1,\"point\":[0,0],\"hostName\":\"test\",\"actualDuration\":2}";
    EXPECT_EQ(JsonStrDragstart, JsonStrDragstart1);

    dragReport.SetDragReporterPharse(DragReporterPharse::DRAG_STOP);
    dragReport.SetDropResult(DropResult::DROP_SUCCESS);
    auto valueDropsuccess = dragReport.GetJsonData();
    std::string JsonStrDropsuccess = valueDropsuccess->ToString().c_str();
    std::string JsonStrDropsuccess1 =
        "{\"GestureType\":\"DrageEnd\",\"point\":[0,0],\"dropResult\":\"success\",\"id\":2,\"hostName\":\"test\"}";
    EXPECT_EQ(JsonStrDropsuccess, JsonStrDropsuccess1);

    dragReport.SetDragReporterPharse(DragReporterPharse::DRAG_STOP);
    dragReport.SetDropResult(DropResult::DROP_FAIL);
    auto valueDopfail = dragReport.GetJsonData();
    std::string JsonStrDopfail = valueDopfail->ToString().c_str();
    std::string JsonStrDopfail1 =
        "{\"GestureType\":\"DrageEnd\",\"point\":[0,0],\"dropResult\":\"fail\",\"hostName\":\"test\"}";
    EXPECT_EQ(JsonStrDopfail, JsonStrDopfail1);
}
} // namespace OHOS::Ace::NG
