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
#include "core/components_ng/relaxed_interaction/executors/smart_gesture_executor.h"
#include "core/components_ng/relaxed_interaction/executors/strict_click_executor.h"
#include "core/components_ng/relaxed_interaction/parsers/tap_command_parser.h"
#include "core/pipeline_ng/pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

namespace {
constexpr float ROOT_WIDTH = 720.0f;
constexpr float ROOT_HEIGHT = 1280.0f;

const std::string VALID_TAP_JSON = R"({
    "type": "click",
    "mode": "auto"
})";

const std::string EMPTY_JSON = R"({})";
} // namespace

class TapCommandParserTest : public testing::Test {
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

class TapCommandParserConstructorTest : public TapCommandParserTest {};
class TapCommandParserParseTest : public TapCommandParserTest {};

// Constructor tests
HWTEST_F(TapCommandParserConstructorTest, Constructor_SetsContext, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    TapCommandParser parser(context);
    EXPECT_EQ(parser.context_, context);
}

HWTEST_F(TapCommandParserConstructorTest, Constructor_NullContext, TestSize.Level1)
{
    WeakPtr<PipelineContext> nullContext;
    TapCommandParser parser(nullContext);
    EXPECT_EQ(parser.context_, nullContext);
}

// Parse tests - with valid context (returns 2 executors: SmartGestureExecutor + StrictClickExecutor)
HWTEST_F(TapCommandParserParseTest, Parse_ValidJson_ReturnsTwoExecutors, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    TapCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(VALID_TAP_JSON);
    ASSERT_NE(json, nullptr);

    auto executors = parser.Parse(json);
    EXPECT_EQ(executors.size(), 2);
    ASSERT_NE(executors[0], nullptr);
    EXPECT_EQ(executors[0]->GetType(), "smart_gesture");
    EXPECT_TRUE(executors[0]->IsSingleStep());
    ASSERT_NE(executors[1], nullptr);
    EXPECT_EQ(executors[1]->GetType(), "strict_click");
    EXPECT_TRUE(executors[1]->IsSingleStep());
}

HWTEST_F(TapCommandParserParseTest, Parse_EmptyJson_ReturnsTwoExecutors, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    TapCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(EMPTY_JSON);
    ASSERT_NE(json, nullptr);

    auto executors = parser.Parse(json);
    EXPECT_EQ(executors.size(), 2);
    ASSERT_NE(executors[0], nullptr);
    EXPECT_EQ(executors[0]->GetType(), "smart_gesture");
    ASSERT_NE(executors[1], nullptr);
    EXPECT_EQ(executors[1]->GetType(), "strict_click");
}

HWTEST_F(TapCommandParserParseTest, Parse_NullJson_ReturnsTwoExecutors, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    TapCommandParser parser(context);
    std::unique_ptr<JsonValue> nullJson = nullptr;

    auto executors = parser.Parse(nullJson);
    EXPECT_EQ(executors.size(), 2);
    ASSERT_NE(executors[0], nullptr);
    EXPECT_EQ(executors[0]->GetType(), "smart_gesture");
    ASSERT_NE(executors[1], nullptr);
    EXPECT_EQ(executors[1]->GetType(), "strict_click");
}

HWTEST_F(TapCommandParserParseTest, Parse_FirstExecutorContextMatches, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    TapCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(VALID_TAP_JSON);
    ASSERT_NE(json, nullptr);

    auto executors = parser.Parse(json);
    ASSERT_GE(executors.size(), 1);
    ASSERT_NE(executors[0], nullptr);
    auto* smartGestureExecutor = static_cast<SmartGestureExecutor*>(executors[0].get());
    EXPECT_EQ(smartGestureExecutor->context_, context);
}

// Parse with null context - returns only 1 executor (SmartGestureExecutor), early return before StrictClickExecutor
HWTEST_F(TapCommandParserParseTest, Parse_NullContext_ReturnsOneExecutor, TestSize.Level1)
{
    WeakPtr<PipelineContext> nullContext;
    TapCommandParser parser(nullContext);
    auto json = JsonUtil::ParseJsonString(VALID_TAP_JSON);
    ASSERT_NE(json, nullptr);

    auto executors = parser.Parse(json);
    EXPECT_EQ(executors.size(), 1);
    ASSERT_NE(executors[0], nullptr);
    EXPECT_EQ(executors[0]->GetType(), "smart_gesture");
}

} // namespace OHOS::Ace::NG
