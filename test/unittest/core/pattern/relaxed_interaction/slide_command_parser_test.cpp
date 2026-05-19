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

#include "base/json/json_util.h"
#include "base/memory/ace_type.h"
#include "core/components_ng/relaxed_interaction/executors/scroll_touch_executor.h"
#include "core/components_ng/relaxed_interaction/executors/smart_gesture_executor.h"
#include "core/components_ng/relaxed_interaction/parsers/slide_command_parser.h"
#include "core/pipeline_ng/pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

namespace {
constexpr float ROOT_WIDTH = 720.0f;
constexpr float ROOT_HEIGHT = 1280.0f;

const std::string VALID_SLIDE_JSON = R"({
    "type": "slide",
    "mode": "auto"
})";

const std::string EMPTY_JSON = R"({})";
} // namespace

class SlideCommandParserTest : public testing::Test {
public:
    static void SetUpTestCase()
    {
        mockPipelineContext_ = AceType::MakeRefPtr<MockPipelineContext>();
        ASSERT_NE(mockPipelineContext_, nullptr);
        mockPipelineContext_->SetRootSize(ROOT_WIDTH, ROOT_HEIGHT);
        mockPipelineContext_->SetupRootElement();
        auto rootNode = mockPipelineContext_->GetRootElement();
        ASSERT_NE(rootNode, nullptr);
        rootNode->GetGeometryNode()->SetFrameSize(SizeF(ROOT_WIDTH, ROOT_HEIGHT));
    }

    static void TearDownTestCase()
    {
        mockPipelineContext_.Reset();
    }

protected:
    inline static RefPtr<MockPipelineContext> mockPipelineContext_ = nullptr;
};

class SlideCommandParserConstructorTest : public SlideCommandParserTest {};
class SlideCommandParserParseTest : public SlideCommandParserTest {};

// Constructor tests
HWTEST_F(SlideCommandParserConstructorTest, Constructor_SetsContext, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    SlideCommandParser parser(context);
    EXPECT_EQ(parser.context_, context);
}

HWTEST_F(SlideCommandParserConstructorTest, Constructor_NullContext, TestSize.Level1)
{
    WeakPtr<PipelineContext> nullContext;
    SlideCommandParser parser(nullContext);
    EXPECT_EQ(parser.context_, nullContext);
}

// Parse tests - with valid context (returns 2 executors: SmartGestureExecutor + ScrollTouchExecutor)
HWTEST_F(SlideCommandParserParseTest, Parse_ValidJson_ReturnsTwoExecutors, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    SlideCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(VALID_SLIDE_JSON);
    ASSERT_NE(json, nullptr);

    auto executors = parser.Parse(json);
    EXPECT_EQ(executors.size(), 2);
    ASSERT_NE(executors[0], nullptr);
    EXPECT_EQ(executors[0]->GetType(), "smart_gesture");
    EXPECT_TRUE(executors[0]->IsSingleStep());
    ASSERT_NE(executors[1], nullptr);
    EXPECT_EQ(executors[1]->GetType(), "scroll_touch");
    EXPECT_TRUE(executors[1]->IsSingleStep());
}

HWTEST_F(SlideCommandParserParseTest, Parse_EmptyJson_ReturnsTwoExecutors, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    SlideCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(EMPTY_JSON);
    ASSERT_NE(json, nullptr);

    auto executors = parser.Parse(json);
    EXPECT_EQ(executors.size(), 2);
    ASSERT_NE(executors[0], nullptr);
    EXPECT_EQ(executors[0]->GetType(), "smart_gesture");
    ASSERT_NE(executors[1], nullptr);
    EXPECT_EQ(executors[1]->GetType(), "scroll_touch");
}

HWTEST_F(SlideCommandParserParseTest, Parse_NullJson_ReturnsTwoExecutors, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    SlideCommandParser parser(context);
    std::unique_ptr<JsonValue> nullJson = nullptr;

    auto executors = parser.Parse(nullJson);
    EXPECT_EQ(executors.size(), 2);
    ASSERT_NE(executors[0], nullptr);
    EXPECT_EQ(executors[0]->GetType(), "smart_gesture");
    ASSERT_NE(executors[1], nullptr);
    EXPECT_EQ(executors[1]->GetType(), "scroll_touch");
}

HWTEST_F(SlideCommandParserParseTest, Parse_FirstExecutorContextMatches, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    SlideCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(VALID_SLIDE_JSON);
    ASSERT_NE(json, nullptr);

    auto executors = parser.Parse(json);
    ASSERT_GE(executors.size(), 1);
    ASSERT_NE(executors[0], nullptr);
    auto* smartGestureExecutor = static_cast<SmartGestureExecutor*>(executors[0].get());
    EXPECT_EQ(smartGestureExecutor->context_, context);
}

// Parse with null context - returns only 1 executor (SmartGestureExecutor), early return before ScrollTouchExecutor
HWTEST_F(SlideCommandParserParseTest, Parse_NullContext_ReturnsOneExecutor, TestSize.Level1)
{
    WeakPtr<PipelineContext> nullContext;
    SlideCommandParser parser(nullContext);
    auto json = JsonUtil::ParseJsonString(VALID_SLIDE_JSON);
    ASSERT_NE(json, nullptr);

    auto executors = parser.Parse(json);
    EXPECT_EQ(executors.size(), 1);
    ASSERT_NE(executors[0], nullptr);
    EXPECT_EQ(executors[0]->GetType(), "smart_gesture");
}

HWTEST_F(SlideCommandParserParseTest, Parse_NullRootNode_ReturnsOneExecutor, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    SlideCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(VALID_SLIDE_JSON);
    ASSERT_NE(json, nullptr);

    auto rootBackup = mockPipelineContext_->rootNode_;
    mockPipelineContext_->rootNode_.Reset();

    auto executors = parser.Parse(json);
    EXPECT_EQ(executors.size(), 1);
    ASSERT_NE(executors[0], nullptr);
    EXPECT_EQ(executors[0]->GetType(), "smart_gesture");

    mockPipelineContext_->rootNode_ = rootBackup;
}

HWTEST_F(SlideCommandParserParseTest, Parse_EmptyRootRect_ReturnsOneExecutor, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    SlideCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(VALID_SLIDE_JSON);
    ASSERT_NE(json, nullptr);

    auto rootNode = mockPipelineContext_->GetRootElement();
    ASSERT_NE(rootNode, nullptr);
    auto geometryNode = rootNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto originalSize = geometryNode->GetFrameSize();
    geometryNode->SetFrameSize(SizeF(0.0f, 0.0f));

    auto executors = parser.Parse(json);
    EXPECT_EQ(executors.size(), 1);
    ASSERT_NE(executors[0], nullptr);
    EXPECT_EQ(executors[0]->GetType(), "smart_gesture");

    geometryNode->SetFrameSize(originalSize);
}

HWTEST_F(SlideCommandParserParseTest, Parse_InvalidRootRect_ReturnsOneExecutor, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    SlideCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(VALID_SLIDE_JSON);
    ASSERT_NE(json, nullptr);

    auto rootNode = mockPipelineContext_->GetRootElement();
    ASSERT_NE(rootNode, nullptr);
    auto geometryNode = rootNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto originalSize = geometryNode->GetFrameSize();
    geometryNode->SetFrameSize(SizeF(-1.0f, -1.0f));

    auto executors = parser.Parse(json);
    EXPECT_EQ(executors.size(), 1);
    ASSERT_NE(executors[0], nullptr);
    EXPECT_EQ(executors[0]->GetType(), "smart_gesture");

    geometryNode->SetFrameSize(originalSize);
}

HWTEST_F(SlideCommandParserParseTest, Parse_ZeroWidthRootRect_ReturnsOneExecutor, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    SlideCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(VALID_SLIDE_JSON);
    ASSERT_NE(json, nullptr);

    auto rootNode = mockPipelineContext_->GetRootElement();
    ASSERT_NE(rootNode, nullptr);
    auto geometryNode = rootNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto originalSize = geometryNode->GetFrameSize();
    geometryNode->SetFrameSize(SizeF(0.0f, ROOT_HEIGHT));

    auto executors = parser.Parse(json);
    EXPECT_EQ(executors.size(), 1);
    ASSERT_NE(executors[0], nullptr);
    EXPECT_EQ(executors[0]->GetType(), "smart_gesture");

    geometryNode->SetFrameSize(originalSize);
}

HWTEST_F(SlideCommandParserParseTest, Parse_ZeroHeightRootRect_ReturnsOneExecutor, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    SlideCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(VALID_SLIDE_JSON);
    ASSERT_NE(json, nullptr);

    auto rootNode = mockPipelineContext_->GetRootElement();
    ASSERT_NE(rootNode, nullptr);
    auto geometryNode = rootNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto originalSize = geometryNode->GetFrameSize();
    geometryNode->SetFrameSize(SizeF(ROOT_WIDTH, 0.0f));

    auto executors = parser.Parse(json);
    EXPECT_EQ(executors.size(), 1);
    ASSERT_NE(executors[0], nullptr);
    EXPECT_EQ(executors[0]->GetType(), "smart_gesture");

    geometryNode->SetFrameSize(originalSize);
}

HWTEST_F(SlideCommandParserParseTest, Parse_MultipleCalls_Success, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    SlideCommandParser parser(context);
    auto json1 = JsonUtil::ParseJsonString(VALID_SLIDE_JSON);
    auto json2 = JsonUtil::ParseJsonString(EMPTY_JSON);

    auto executors1 = parser.Parse(json1);
    auto executors2 = parser.Parse(json2);

    EXPECT_EQ(executors1.size(), 2);
    EXPECT_EQ(executors2.size(), 2);
    EXPECT_EQ(executors1[0]->GetType(), "smart_gesture");
    EXPECT_EQ(executors2[0]->GetType(), "smart_gesture");
}

HWTEST_F(SlideCommandParserParseTest, Parse_SmartGestureExecutorTriggerType, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    SlideCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(VALID_SLIDE_JSON);
    ASSERT_NE(json, nullptr);

    auto executors = parser.Parse(json);
    ASSERT_GE(executors.size(), 1);
    EXPECT_EQ(executors[0]->GetType(), "smart_gesture");
}

HWTEST_F(SlideCommandParserParseTest, Parse_ScrollTouchExecutorCommand, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    SlideCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(VALID_SLIDE_JSON);
    ASSERT_NE(json, nullptr);

    auto executors = parser.Parse(json);
    ASSERT_EQ(executors.size(), 2);
    ASSERT_NE(executors[1], nullptr);
    auto* scrollTouchExecutor = static_cast<ScrollTouchExecutor*>(executors[1].get());
    EXPECT_EQ(scrollTouchExecutor->GetType(), "scroll_touch");
}

} // namespace OHOS::Ace::NG
