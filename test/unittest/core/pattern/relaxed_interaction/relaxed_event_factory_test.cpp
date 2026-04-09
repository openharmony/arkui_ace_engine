/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "gtest/gtest.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "base/geometry/ng/point_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/relaxed_interaction/utils/relaxed_event_factory.h"
#include "core/event/touch_event.h"
#include "core/pipeline_ng/pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

namespace {
class NullEventHubPattern : public Pattern {
    RefPtr<EventHub> CreateEventHub() override
    {
        return nullptr;
    }
};
} // namespace

class RelaxedEventFactoryTest : public testing::Test {
public:
    static void SetUpTestCase()
    {
        MockPipelineContext::SetUp();
        mockPipelineContext_ = MockPipelineContext::GetCurrent();
        ASSERT_NE(mockPipelineContext_, nullptr);
    }

    static void TearDownTestCase()
    {
        mockPipelineContext_.Reset();
        MockPipelineContext::TearDown();
    }

protected:
    inline static RefPtr<MockPipelineContext> mockPipelineContext_ = nullptr;
};

class RelaxedEventFactoryCreateTouchEventTest : public RelaxedEventFactoryTest {};
class RelaxedEventFactoryCreateClickGestureEventTest : public RelaxedEventFactoryTest {};

HWTEST_F(RelaxedEventFactoryCreateTouchEventTest, CreateTouchEvent_DownType, TestSize.Level1)
{
    PointF coordinates(100.0f, 200.0f);
    auto event = RelaxedEventFactory::CreateTouchEvent(coordinates, TouchType::DOWN);

    EXPECT_EQ(event.type, TouchType::DOWN);
    EXPECT_FLOAT_EQ(event.x, 100.0f);
    EXPECT_FLOAT_EQ(event.y, 200.0f);
    EXPECT_EQ(event.sourceType, SourceType::TOUCH);
    EXPECT_TRUE(event.isInjected);
    EXPECT_FALSE(event.pointers.empty());
}

HWTEST_F(RelaxedEventFactoryCreateTouchEventTest, CreateTouchEvent_UpType, TestSize.Level1)
{
    PointF coordinates(150.0f, 250.0f);
    auto event = RelaxedEventFactory::CreateTouchEvent(coordinates, TouchType::UP);

    EXPECT_EQ(event.type, TouchType::UP);
    EXPECT_FLOAT_EQ(event.x, 150.0f);
    EXPECT_FLOAT_EQ(event.y, 250.0f);
    EXPECT_FALSE(event.pointers.empty());
    EXPECT_EQ(event.pointers[0].isPressed, false);
}

HWTEST_F(RelaxedEventFactoryCreateTouchEventTest, CreateTouchEvent_MoveType, TestSize.Level1)
{
    PointF coordinates(300.0f, 400.0f);
    auto event = RelaxedEventFactory::CreateTouchEvent(coordinates, TouchType::MOVE);

    EXPECT_EQ(event.type, TouchType::MOVE);
    EXPECT_FLOAT_EQ(event.x, 300.0f);
    EXPECT_FLOAT_EQ(event.y, 400.0f);
    EXPECT_FALSE(event.pointers.empty());
    EXPECT_TRUE(event.pointers[0].isPressed);
}

HWTEST_F(RelaxedEventFactoryCreateTouchEventTest, CreateTouchEvent_CancelType, TestSize.Level1)
{
    PointF coordinates(0.0f, 0.0f);
    auto event = RelaxedEventFactory::CreateTouchEvent(coordinates, TouchType::CANCEL);

    EXPECT_EQ(event.type, TouchType::CANCEL);
    EXPECT_FALSE(event.pointers.empty());
    EXPECT_FALSE(event.pointers[0].isPressed);
}

HWTEST_F(RelaxedEventFactoryCreateTouchEventTest, CreateTouchEvent_UnknownType, TestSize.Level1)
{
    PointF coordinates(500.0f, 600.0f);
    auto event = RelaxedEventFactory::CreateTouchEvent(coordinates, TouchType::UNKNOWN);

    EXPECT_EQ(event.type, TouchType::UNKNOWN);
    EXPECT_FALSE(event.pointers.empty());
    EXPECT_FALSE(event.pointers[0].isPressed);
}

HWTEST_F(RelaxedEventFactoryCreateTouchEventTest, CreateTouchEvent_NegativeCoordinates, TestSize.Level1)
{
    PointF coordinates(-50.0f, -100.0f);
    auto event = RelaxedEventFactory::CreateTouchEvent(coordinates, TouchType::DOWN);

    EXPECT_FLOAT_EQ(event.x, -50.0f);
    EXPECT_FLOAT_EQ(event.y, -100.0f);
}

HWTEST_F(RelaxedEventFactoryCreateTouchEventTest, CreateTouchEvent_LargeCoordinates, TestSize.Level1)
{
    PointF coordinates(10000.0f, 20000.0f);
    auto event = RelaxedEventFactory::CreateTouchEvent(coordinates, TouchType::DOWN);

    EXPECT_FLOAT_EQ(event.x, 10000.0f);
    EXPECT_FLOAT_EQ(event.y, 20000.0f);
}

HWTEST_F(RelaxedEventFactoryCreateClickGestureEventTest, CreateClickGestureEvent_ValidFrameNode, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>("TestButton", 0, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(200.0f, 200.0f));
    geometryNode->SetFrameOffset(OffsetF(100.0f, 100.0f));
    frameNode->geometryNode_ = geometryNode;

    auto event = RelaxedEventFactory::CreateClickGestureEvent(frameNode);

    EXPECT_EQ(event.GetInputEventType(), InputEventType::TOUCH_SCREEN);
}

HWTEST_F(RelaxedEventFactoryCreateClickGestureEventTest, CreateClickGestureEvent_WithContext, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>("TestNode", 0, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(100.0f, 100.0f));
    geometryNode->SetFrameOffset(OffsetF(0.0f, 0.0f));
    frameNode->geometryNode_ = geometryNode;

    MockPipelineContext::SetCurrentWindowRect({ 0, 0, 1920, 1080 });

    auto event = RelaxedEventFactory::CreateClickGestureEvent(frameNode);

    EXPECT_TRUE(event.GetLocalLocation().GetX() >= 0);
    EXPECT_TRUE(event.GetLocalLocation().GetY() >= 0);
}

HWTEST_F(RelaxedEventFactoryCreateClickGestureEventTest, CreateClickGestureEvent_NullGeometryNode, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>("TestButton", 0, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    frameNode->geometryNode_ = nullptr;

    auto event = RelaxedEventFactory::CreateClickGestureEvent(frameNode);

    EXPECT_EQ(event.GetLocalLocation().GetX(), 0.0f);
    EXPECT_EQ(event.GetLocalLocation().GetY(), 0.0f);
    EXPECT_EQ(event.GetGlobalLocation().GetX(), 0.0f);
    EXPECT_EQ(event.GetGlobalLocation().GetY(), 0.0f);
}

HWTEST_F(RelaxedEventFactoryCreateClickGestureEventTest, CreateClickGestureEvent_NullPipelineContext, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>("TestButton", 0, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(200.0f, 200.0f));
    geometryNode->SetFrameOffset(OffsetF(100.0f, 100.0f));
    frameNode->geometryNode_ = geometryNode;

    MockPipelineContext::TearDown();

    auto event = RelaxedEventFactory::CreateClickGestureEvent(frameNode);

    EXPECT_EQ(event.GetInputEventType(), InputEventType::TOUCH_SCREEN);
    EXPECT_TRUE(event.GetLocalLocation().GetX() > 0.0f);
    EXPECT_TRUE(event.GetLocalLocation().GetY() > 0.0f);
    EXPECT_EQ(event.GetScreenLocation().GetX(), 0.0f);
    EXPECT_EQ(event.GetScreenLocation().GetY(), 0.0f);

    MockPipelineContext::SetUp();
    mockPipelineContext_ = MockPipelineContext::GetCurrent();
}

HWTEST_F(RelaxedEventFactoryCreateClickGestureEventTest, CreateClickGestureEvent_NullEventHub, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>("TestButton", 0, AceType::MakeRefPtr<NullEventHubPattern>());
    ASSERT_NE(frameNode, nullptr);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(200.0f, 200.0f));
    geometryNode->SetFrameOffset(OffsetF(100.0f, 100.0f));
    frameNode->geometryNode_ = geometryNode;

    auto event = RelaxedEventFactory::CreateClickGestureEvent(frameNode);

    EXPECT_EQ(event.GetInputEventType(), InputEventType::TOUCH_SCREEN);
    EXPECT_TRUE(event.GetLocalLocation().GetX() > 0.0f);
    EXPECT_TRUE(event.GetLocalLocation().GetY() > 0.0f);
    EXPECT_TRUE(event.GetTarget().id.empty());
    EXPECT_TRUE(event.GetTarget().type.empty());
}

} // namespace OHOS::Ace::NG
