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
const Offset offsetGlobalDisplay(30, 30);
const FingerInfo fingerInfo = { 0, 0, offset, offsetLocal, offsetGlobal, offsetGlobalDisplay, SourceType::TOUCH,
    SourceTool::FINGER };
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
    std::string JsonUisessionStr1 = "{\"GestureType\":\"Swipe\",\"id\":1,\"upPoint\":[[10,10]],\"downPoint\":[[10,10]],"
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

/**
 * @tc.name: JsonReportTestNgTypeTest009
 * @tc.desc: Test TouchJsonReport with different properties
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(JsonReportTestNg, JsonReportTestNgTypeTest009, TestSize.Level1)
{
    TouchJsonReport touchReport;
    touchReport.SetPoint(globalPoint);
    touchReport.SetEventType("Touch");
    touchReport.SetAction("down");
    TimeStamp time(std::chrono::nanoseconds(1000000));
    touchReport.SetTime(time);
    touchReport.SetWindowID(100);
    auto value = touchReport.GetJsonData();
    std::string JsonStr = value->ToString().c_str();
    std::string JsonStr1 = "{\"type\":\"event\",\"eventType\":\"Touch\",\"action\":\"down\","
                           "\"time\":1000000,\"windowId\":100,\"data\":{\"point\":[100,100]}}";
    EXPECT_EQ(JsonStr, JsonStr1);

    touchReport.SetAction("");
    auto value2 = touchReport.GetJsonData();
    std::string JsonStr2 = value2->ToString().c_str();
    std::string JsonStr21 = "{\"type\":\"event\",\"eventType\":\"Touch\",\"action\":\"\",\"time\":1000000,"
                            "\"windowId\":100,\"data\":{\"point\":[100,100]}}";
    EXPECT_EQ(JsonStr2, JsonStr21);
}

/**
 * @tc.name: JsonReportTestNgTypeTest010
 * @tc.desc: Test MouseJsonReport with different properties
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(JsonReportTestNg, JsonReportTestNgTypeTest010, TestSize.Level1)
{
    MouseJsonReport mouseReport;
    mouseReport.SetPoint(globalPoint);
    mouseReport.SetWindowID(200);
    mouseReport.SetEventType("Mouse");
    TimeStamp time(std::chrono::nanoseconds(2000000));
    mouseReport.SetTime(time);
    mouseReport.SetAction("press");
    mouseReport.SetMouseButton("left");
    auto value = mouseReport.GetJsonData();
    std::string JsonStr = value->ToString().c_str();
    std::string JsonStr1 = "{\"type\":\"event\",\"eventType\":\"Mouse\",\"action\":\"press\","
                           "\"time\":2000000,\"windowId\":200,\"data\":{\"point\":[100,100],\"mouseButton\":\"left\"}}";
    EXPECT_EQ(JsonStr, JsonStr1);

    mouseReport.SetAction("release");
    mouseReport.SetMouseButton("right");
    auto value2 = mouseReport.GetJsonData();
    std::string JsonStr2 = value2->ToString().c_str();
    std::string JsonStr21 =
        "{\"type\":\"event\",\"eventType\":\"Mouse\",\"action\":\"release\","
        "\"time\":2000000,\"windowId\":200,\"data\":{\"point\":[100,100],\"mouseButton\":\"right\"}}";
    EXPECT_EQ(JsonStr2, JsonStr21);
}

/**
 * @tc.name: JsonReportTestNgTypeTest011
 * @tc.desc: Test KeyJsonReport with different key codes and actions
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(JsonReportTestNg, JsonReportTestNgTypeTest011, TestSize.Level1)
{
    KeyJsonReport keyReport;
    keyReport.SetWindowID(300);
    keyReport.SetEventType("Key");
    TimeStamp time(std::chrono::nanoseconds(3000000));
    keyReport.SetTime(time);
    keyReport.SetKeyCode(2042);
    keyReport.SetAction("down");
    auto value = keyReport.GetJsonData();
    std::string JsonStr = value->ToString().c_str();
    std::string JsonStr1 = "{\"type\":\"event\",\"eventType\":\"Key\",\"action\":\"down\","
                           "\"time\":3000000,\"windowId\":300,\"data\":{\"keyCode\":2042}}";
    EXPECT_EQ(JsonStr, JsonStr1);

    keyReport.SetAction("up");
    keyReport.SetKeyCode(2042);
    auto value2 = keyReport.GetJsonData();
    std::string JsonStr2 = value2->ToString().c_str();
    std::string JsonStr21 = "{\"type\":\"event\",\"eventType\":\"Key\",\"action\":\"up\","
                            "\"time\":3000000,\"windowId\":300,\"data\":{\"keyCode\":2042}}";
    EXPECT_EQ(JsonStr2, JsonStr21);
}

/**
 * @tc.name: JsonReportTestNgTypeTest012
 * @tc.desc: Test AxisJsonReport with different axis types and values
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(JsonReportTestNg, JsonReportTestNgTypeTest012, TestSize.Level1)
{
    AxisJsonReport axisReport;
    axisReport.SetPoint(globalPoint);
    axisReport.SetWindowID(400);
    axisReport.SetEventType("Axis");
    TimeStamp time(std::chrono::nanoseconds(4000000));
    axisReport.SetTime(time);
    axisReport.SetAction("Update");

    AxisValue axisValues1 = { 0.0f, 1.5f, 1.0f, 0.0f };
    axisReport.SetAxisValues(axisValues1);

    auto value = axisReport.GetJsonData();
    std::string JsonStr = value->ToString().c_str();
    std::string JsonStr1 = "{\"type\":\"event\",\"eventType\":\"Axis\",\"action\":\"Update\","
                           "\"time\":4000000,\"windowId\":400,\"data\":{\"point\":[100,100],"
                           "\"axisValues\":{\"horizontalAxis\":0,\"verticalAxis\":1.5,"
                           "\"pinchAxisScale\":1,\"rotateAxisAngle\":0}}}";
    EXPECT_EQ(JsonStr, JsonStr1);

    AxisValue axisValues2 = { -2.0f, 0.0f, 1.0f, 0.0f };
    axisReport.SetAxisValues(axisValues2);

    auto value2 = axisReport.GetJsonData();
    std::string JsonStr2 = value2->ToString().c_str();
    std::string JsonStr21 = "{\"type\":\"event\",\"eventType\":\"Axis\",\"action\":\"Update\","
                            "\"time\":4000000,\"windowId\":400,\"data\":{\"point\":[100,100],"
                            "\"axisValues\":{\"horizontalAxis\":-2,\"verticalAxis\":0,"
                            "\"pinchAxisScale\":1,\"rotateAxisAngle\":0}}}";
    EXPECT_EQ(JsonStr2, JsonStr21);
}

/**
 * @tc.name: JsonReportTestNgTypeTest013
 * @tc.desc: Test FocusJsonReport with focus and blur states
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(JsonReportTestNg, JsonReportTestNgTypeTest013, TestSize.Level1)
{
    FocusJsonReport focusReport;
    focusReport.SetWindowID(500);
    focusReport.SetEventType("WindowFocus");
    TimeStamp time(std::chrono::nanoseconds(5000000));
    focusReport.SetTime(time);
    focusReport.SetAction("Focus");
    focusReport.SetIsFocus(true);
    auto value = focusReport.GetJsonData();
    std::string JsonStr = value->ToString().c_str();
    std::string JsonStr1 = "{\"type\":\"event\",\"eventType\":\"WindowFocus\",\"action\":\"Focus\","
                           "\"windowId\":500,\"time\":5000000,\"data\":{\"isFocus\":true}}";
    EXPECT_EQ(JsonStr, JsonStr1);

    focusReport.SetAction("Blur");
    focusReport.SetIsFocus(false);
    auto value2 = focusReport.GetJsonData();
    std::string JsonStr2 = value2->ToString().c_str();
    std::string JsonStr21 = "{\"type\":\"event\",\"eventType\":\"WindowFocus\",\"action\":\"Blur\","
                            "\"windowId\":500,\"time\":5000000,\"data\":{\"isFocus\":false}}";
    EXPECT_EQ(JsonStr2, JsonStr21);
}

/**
 * @tc.name: JsonReportTestNgTypeTest014
 * @tc.desc: Test FocusJsonReport with focus and blur states
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(JsonReportTestNg, JsonReportTestNgTypeTest014, TestSize.Level1)
{
    TapJsonReport tapReport;
    tapReport.SetPoint(globalPoint);
    tapReport.SetCount(10);
    tapReport.SetId(id);
    tapReport.SetFingerList(fingerList);
    auto value = tapReport.GetJsonData();
    std::string JsonStr = value->ToString().c_str();
    std::string JsonStr1 = "{\"GestureType\":\"Tap\",\"id\":1,\"point\":[100,100],\"count\":10,\"fingers\":1}";
    EXPECT_EQ(JsonStr, JsonStr1);
}
} // namespace OHOS::Ace::NG
