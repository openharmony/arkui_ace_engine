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
#include "core/components_ng/relaxed_interaction/base_command_parser.h"
#include "core/components_ng/relaxed_interaction/base_executor.h"
#include "core/components_ng/relaxed_interaction/executor_generator.h"
#include "core/components_ng/relaxed_interaction/relaxed_interaction_types.h"
#include "core/pipeline_ng/pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

namespace {
// Executor count per command type with auto mode
constexpr size_t EXPECTED_SINGLE_EXECUTOR_COUNT = 1u;
constexpr size_t CLICK_AUTO_EXECUTOR_COUNT = 2u;
constexpr size_t SCROLL_AUTO_EXECUTOR_COUNT = 2u;

const std::string VALID_BACKPRESS_JSON = R"({
    "cmd": {
        "type": "backpress"
    }
})";

const std::string VALID_CLICK_JSON = R"({
    "cmd": {
        "type": "click",
        "mode": "auto",
        "action_info": {
            "coordinates": {
                "x1": 100.0,
                "y1": 200.0
            }
        }
    }
})";

const std::string VALID_SCROLL_JSON = R"({
    "cmd": {
        "type": "scroll",
        "mode": "auto",
        "action_info": {
            "coordinates": {
                "x1": 100.0,
                "y1": 200.0,
                "x2": 100.0,
                "y2": 400.0
            }
        }
    }
})";

const std::string VALID_TAP_JSON = R"({
    "cmd": {
        "type": "tap",
        "mode": "auto",
        "action_info": {
            "coordinates": {
                "x1": 100.0,
                "y1": 200.0
            }
        }
    }
})";

const std::string VALID_SLIDE_JSON = R"({
    "cmd": {
        "type": "slide",
        "mode": "auto",
        "action_info": {
            "coordinates": {
                "x1": 100.0,
                "y1": 200.0,
                "x2": 100.0,
                "y2": 400.0
            }
        }
    }
})";

const std::string VALID_CONTENT_SWITCH_JSON = R"({
    "cmd": {
        "type": "content_switch",
        "mode": "target",
        "action_info": {
            "coordinates": {
                "pos": {
                    "x": 100.0,
                    "y": 200.0
                }
            },
            "direction": "forward"
        }
    }
})";

const std::string VALID_FALLBACK_JSON = R"({
    "fallback_cmd": {
        "identity": "test_id",
        "body": {
            "radio1": true,
            "radio2": false
        }
    }
})";

const std::string UNKNOWN_TYPE_JSON = R"({
    "cmd": {
        "type": "unknown_type"
    }
})";

const std::string MISSING_CMD_JSON = R"({
    "other_key": "value"
})";

const std::string INVALID_CMD_NOT_OBJECT_JSON = R"({
    "cmd": "not_an_object"
})";

const std::string MISSING_TYPE_JSON = R"({
    "cmd": {
        "other_key": "value"
    }
})";

const std::string FALLBACK_INVALID_JSON = R"({
    "fallback_cmd": "not_an_object"
})";

const std::string BOTH_CMD_AND_FALLBACK_JSON = R"({
    "fallback_cmd": {
        "identity": "test_id",
        "body": {
            "radio1": true
        }
    },
    "cmd": {
        "type": "backpress"
    }
})";
} // namespace

class ExecutorGeneratorTest : public testing::Test {
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

class ExecutorGeneratorConstructorTest : public ExecutorGeneratorTest {};
class ExecutorGeneratorParseCommandTest : public ExecutorGeneratorTest {};
class ExecutorGeneratorParseFallbackCmdTest : public ExecutorGeneratorTest {};
class ExecutorGeneratorParseRegularCmdTest : public ExecutorGeneratorTest {};

// ============ Constructor Tests ============

HWTEST_F(ExecutorGeneratorConstructorTest, Constructor_NullContext, TestSize.Level1)
{
    ExecutorGenerator generator(nullptr);
    auto json = JsonUtil::ParseJsonString(VALID_BACKPRESS_JSON);
    auto result = generator.ParseCommand(json);
    // With null context, backpress executor is created but cannot execute
    EXPECT_EQ(result.size(), EXPECTED_SINGLE_EXECUTOR_COUNT);
    EXPECT_EQ(result[0]->GetType(), BACKPRESS);
}

HWTEST_F(ExecutorGeneratorConstructorTest, Constructor_ValidContext, TestSize.Level1)
{
    ExecutorGenerator generator(mockPipelineContext_);
    auto json = JsonUtil::ParseJsonString(VALID_BACKPRESS_JSON);
    auto result = generator.ParseCommand(json);
    EXPECT_EQ(result.size(), EXPECTED_SINGLE_EXECUTOR_COUNT);
    EXPECT_EQ(result[0]->GetType(), BACKPRESS);
}

// ============ ParseCommand Tests ============

HWTEST_F(ExecutorGeneratorParseCommandTest, ParseCommand_FallbackCommand, TestSize.Level1)
{
    ExecutorGenerator generator(mockPipelineContext_);
    auto json = JsonUtil::ParseJsonString(VALID_FALLBACK_JSON);
    auto result = generator.ParseCommand(json);
    EXPECT_EQ(result.size(), EXPECTED_SINGLE_EXECUTOR_COUNT);
    EXPECT_EQ(result[0]->GetType(), FALLBACK);
}

HWTEST_F(ExecutorGeneratorParseCommandTest, ParseCommand_RegularCommand, TestSize.Level1)
{
    ExecutorGenerator generator(mockPipelineContext_);
    auto json = JsonUtil::ParseJsonString(VALID_CLICK_JSON);
    auto result = generator.ParseCommand(json);
    EXPECT_EQ(result.size(), CLICK_AUTO_EXECUTOR_COUNT);
    EXPECT_EQ(result[0]->GetType(), "strict_click");
}

HWTEST_F(ExecutorGeneratorParseCommandTest, ParseCommand_FallbackPriorityOverCmd, TestSize.Level1)
{
    ExecutorGenerator generator(mockPipelineContext_);
    auto json = JsonUtil::ParseJsonString(BOTH_CMD_AND_FALLBACK_JSON);
    auto result = generator.ParseCommand(json);
    // When both fallback_cmd and cmd exist, fallback_cmd takes priority
    EXPECT_EQ(result.size(), EXPECTED_SINGLE_EXECUTOR_COUNT);
    EXPECT_EQ(result[0]->GetType(), FALLBACK);
}

// ============ ParseRegularCmd Tests ============

HWTEST_F(ExecutorGeneratorParseRegularCmdTest, ParseRegularCmd_BackpressType, TestSize.Level1)
{
    ExecutorGenerator generator(mockPipelineContext_);
    auto json = JsonUtil::ParseJsonString(VALID_BACKPRESS_JSON);
    auto result = generator.ParseCommand(json);
    EXPECT_EQ(result.size(), EXPECTED_SINGLE_EXECUTOR_COUNT);
    EXPECT_EQ(result[0]->GetType(), BACKPRESS);
}

HWTEST_F(ExecutorGeneratorParseRegularCmdTest, ParseRegularCmd_ClickType, TestSize.Level1)
{
    ExecutorGenerator generator(mockPipelineContext_);
    auto json = JsonUtil::ParseJsonString(VALID_CLICK_JSON);
    auto result = generator.ParseCommand(json);
    // Auto mode creates StrictClickExecutor + SimulateTouchExecutor
    EXPECT_EQ(result.size(), CLICK_AUTO_EXECUTOR_COUNT);
    EXPECT_EQ(result[0]->GetType(), "strict_click");
    EXPECT_EQ(result[1]->GetType(), "simulate_touch");
}

HWTEST_F(ExecutorGeneratorParseRegularCmdTest, ParseRegularCmd_ScrollType, TestSize.Level1)
{
    ExecutorGenerator generator(mockPipelineContext_);
    auto json = JsonUtil::ParseJsonString(VALID_SCROLL_JSON);
    auto result = generator.ParseCommand(json);
    // Auto mode creates ScrollTouchExecutor + ScrollSimulatingExecutor
    EXPECT_EQ(result.size(), SCROLL_AUTO_EXECUTOR_COUNT);
    EXPECT_EQ(result[0]->GetType(), "scroll_touch");
    EXPECT_EQ(result[1]->GetType(), "scroll_simulating");
}

HWTEST_F(ExecutorGeneratorParseRegularCmdTest, ParseRegularCmd_TapType, TestSize.Level1)
{
    ExecutorGenerator generator(mockPipelineContext_);
    auto json = JsonUtil::ParseJsonString(VALID_TAP_JSON);
    auto result = generator.ParseCommand(json);
    // Tap always creates SmartGestureExecutor, may add StrictClickExecutor depending on context
    EXPECT_GE(result.size(), EXPECTED_SINGLE_EXECUTOR_COUNT);
    EXPECT_EQ(result[0]->GetType(), "smart_gesture");
}

HWTEST_F(ExecutorGeneratorParseRegularCmdTest, ParseRegularCmd_SlideType, TestSize.Level1)
{
    ExecutorGenerator generator(mockPipelineContext_);
    auto json = JsonUtil::ParseJsonString(VALID_SLIDE_JSON);
    auto result = generator.ParseCommand(json);
    // Slide always creates SmartGestureExecutor, may add ScrollTouchExecutor depending on context
    EXPECT_GE(result.size(), EXPECTED_SINGLE_EXECUTOR_COUNT);
    EXPECT_EQ(result[0]->GetType(), "smart_gesture");
}

HWTEST_F(ExecutorGeneratorParseRegularCmdTest, ParseRegularCmd_ContentSwitchType, TestSize.Level1)
{
    ExecutorGenerator generator(mockPipelineContext_);
    auto json = JsonUtil::ParseJsonString(VALID_CONTENT_SWITCH_JSON);
    auto result = generator.ParseCommand(json);
    EXPECT_EQ(result.size(), EXPECTED_SINGLE_EXECUTOR_COUNT);
    EXPECT_EQ(result[0]->GetType(), "strict_content_switch");
}

HWTEST_F(ExecutorGeneratorParseRegularCmdTest, ParseRegularCmd_UnknownType, TestSize.Level1)
{
    ExecutorGenerator generator(mockPipelineContext_);
    auto json = JsonUtil::ParseJsonString(UNKNOWN_TYPE_JSON);
    auto result = generator.ParseCommand(json);
    EXPECT_TRUE(result.empty());
}

HWTEST_F(ExecutorGeneratorParseRegularCmdTest, ParseRegularCmd_MissingCmdKey, TestSize.Level1)
{
    ExecutorGenerator generator(mockPipelineContext_);
    auto json = JsonUtil::ParseJsonString(MISSING_CMD_JSON);
    auto result = generator.ParseCommand(json);
    EXPECT_TRUE(result.empty());
}

HWTEST_F(ExecutorGeneratorParseRegularCmdTest, ParseRegularCmd_CmdNotObject, TestSize.Level1)
{
    ExecutorGenerator generator(mockPipelineContext_);
    auto json = JsonUtil::ParseJsonString(INVALID_CMD_NOT_OBJECT_JSON);
    auto result = generator.ParseCommand(json);
    EXPECT_TRUE(result.empty());
}

HWTEST_F(ExecutorGeneratorParseRegularCmdTest, ParseRegularCmd_MissingTypeKey, TestSize.Level1)
{
    ExecutorGenerator generator(mockPipelineContext_);
    auto json = JsonUtil::ParseJsonString(MISSING_TYPE_JSON);
    auto result = generator.ParseCommand(json);
    // Empty type string not found in registry
    EXPECT_TRUE(result.empty());
}

// ============ ParseFallbackCmd Tests ============

HWTEST_F(ExecutorGeneratorParseFallbackCmdTest, ParseFallbackCmd_ValidFallback, TestSize.Level1)
{
    ExecutorGenerator generator(mockPipelineContext_);
    auto json = JsonUtil::ParseJsonString(VALID_FALLBACK_JSON);
    auto result = generator.ParseCommand(json);
    EXPECT_EQ(result.size(), EXPECTED_SINGLE_EXECUTOR_COUNT);
    EXPECT_EQ(result[0]->GetType(), FALLBACK);
}

HWTEST_F(ExecutorGeneratorParseFallbackCmdTest, ParseFallbackCmd_InvalidFallbackNotObject, TestSize.Level1)
{
    ExecutorGenerator generator(mockPipelineContext_);
    auto json = JsonUtil::ParseJsonString(FALLBACK_INVALID_JSON);
    auto result = generator.ParseCommand(json);
    // fallback_cmd value is not an object, returns empty
    EXPECT_TRUE(result.empty());
}

HWTEST_F(ExecutorGeneratorParseFallbackCmdTest, ParseFallbackCmd_MissingFallbackKey, TestSize.Level1)
{
    ExecutorGenerator generator(mockPipelineContext_);
    auto json = JsonUtil::ParseJsonString(VALID_CLICK_JSON);
    // No fallback_cmd key, falls through to ParseRegularCmd
    auto result = generator.ParseCommand(json);
    EXPECT_FALSE(result.empty());
}

// ============ Additional Tests for 100% Branch Coverage ============

HWTEST_F(ExecutorGeneratorParseCommandTest, ParseCommand_EmptyJson, TestSize.Level1)
{
    ExecutorGenerator generator(mockPipelineContext_);
    auto json = JsonUtil::ParseJsonString("{}");
    auto result = generator.ParseCommand(json);
    EXPECT_TRUE(result.empty());
}

HWTEST_F(ExecutorGeneratorParseFallbackCmdTest, ParseFallbackCmd_NotRegistered_ReturnsEmpty, TestSize.Level1)
{
    ExecutorGenerator generator(mockPipelineContext_);
    generator.parserRegistry_.erase(FALLBACK);
    auto json = JsonUtil::ParseJsonString(VALID_FALLBACK_JSON);
    auto result = generator.ParseCommand(json);
    EXPECT_TRUE(result.empty());
}

HWTEST_F(ExecutorGeneratorParseFallbackCmdTest, ParseFallbackCmd_JsonCmdNull_ReturnsEmpty, TestSize.Level1)
{
    ExecutorGenerator generator(mockPipelineContext_);
    auto json = JsonUtil::ParseJsonString(R"({
        "fallback_cmd": null
    })");
    auto result = generator.ParseCommand(json);
    EXPECT_TRUE(result.empty());
}

HWTEST_F(ExecutorGeneratorParseFallbackCmdTest, ParseFallbackCmd_JsonCmdInvalid_ReturnsEmpty, TestSize.Level1)
{
    ExecutorGenerator generator(mockPipelineContext_);
    auto json = JsonUtil::ParseJsonString(R"({
        "fallback_cmd": []
    })");
    auto result = generator.ParseCommand(json);
    EXPECT_TRUE(result.empty());
}

HWTEST_F(ExecutorGeneratorParseRegularCmdTest, ParseRegularCmd_JsonCmdNull_ReturnsEmpty, TestSize.Level1)
{
    ExecutorGenerator generator(mockPipelineContext_);
    auto json = JsonUtil::ParseJsonString(R"({
        "cmd": null
    })");
    auto result = generator.ParseCommand(json);
    EXPECT_TRUE(result.empty());
}

HWTEST_F(ExecutorGeneratorParseRegularCmdTest, ParseRegularCmd_JsonCmdInvalid_ReturnsEmpty, TestSize.Level1)
{
    ExecutorGenerator generator(mockPipelineContext_);
    auto json = JsonUtil::ParseJsonString(R"({
        "cmd": []
    })");
    auto result = generator.ParseCommand(json);
    EXPECT_TRUE(result.empty());
}

HWTEST_F(ExecutorGeneratorParseRegularCmdTest, ParseRegularCmd_JsonCmdNotObject_ReturnsEmpty, TestSize.Level1)
{
    ExecutorGenerator generator(mockPipelineContext_);
    auto json = JsonUtil::ParseJsonString(R"({
        "cmd": 123
    })");
    auto result = generator.ParseCommand(json);
    EXPECT_TRUE(result.empty());
}

HWTEST_F(ExecutorGeneratorParseRegularCmdTest, ParseRegularCmd_TypeStringEmpty_ReturnsEmpty, TestSize.Level1)
{
    ExecutorGenerator generator(mockPipelineContext_);
    auto json = JsonUtil::ParseJsonString(R"({
        "cmd": {
            "type": ""
        }
    })");
    auto result = generator.ParseCommand(json);
    EXPECT_TRUE(result.empty());
}

HWTEST_F(ExecutorGeneratorParseRegularCmdTest, ParseRegularCmd_TypeNotString_ReturnsEmpty, TestSize.Level1)
{
    ExecutorGenerator generator(mockPipelineContext_);
    auto json = JsonUtil::ParseJsonString(R"({
        "cmd": {
            "type": 123
        }
    })");
    auto result = generator.ParseCommand(json);
    EXPECT_TRUE(result.empty());
}

HWTEST_F(ExecutorGeneratorConstructorTest, Constructor_RegisterDefaultParsers_AllRegistered, TestSize.Level1)
{
    ExecutorGenerator generator(mockPipelineContext_);
    EXPECT_EQ(generator.parserRegistry_.size(), 7u);
    EXPECT_NE(generator.parserRegistry_.find(BACKPRESS), generator.parserRegistry_.end());
    EXPECT_NE(generator.parserRegistry_.find(FALLBACK), generator.parserRegistry_.end());
    EXPECT_NE(generator.parserRegistry_.find(CLICK), generator.parserRegistry_.end());
    EXPECT_NE(generator.parserRegistry_.find(CONTENT_SWITCH), generator.parserRegistry_.end());
    EXPECT_NE(generator.parserRegistry_.find(SCROLL), generator.parserRegistry_.end());
    EXPECT_NE(generator.parserRegistry_.find(TAP), generator.parserRegistry_.end());
    EXPECT_NE(generator.parserRegistry_.find(SLIDE), generator.parserRegistry_.end());
}

HWTEST_F(ExecutorGeneratorConstructorTest, Destructor_Cleanup_Success, TestSize.Level1)
{
    auto* generator = new ExecutorGenerator(mockPipelineContext_);
    EXPECT_NE(generator, nullptr);
    delete generator;
    EXPECT_TRUE(true);
}

HWTEST_F(ExecutorGeneratorParseCommandTest, ParseCommand_MultipleCalls_Success, TestSize.Level1)
{
    ExecutorGenerator generator(mockPipelineContext_);
    auto json1 = JsonUtil::ParseJsonString(VALID_BACKPRESS_JSON);
    auto json2 = JsonUtil::ParseJsonString(VALID_CLICK_JSON);
    auto json3 = JsonUtil::ParseJsonString(VALID_SCROLL_JSON);

    auto result1 = generator.ParseCommand(json1);
    auto result2 = generator.ParseCommand(json2);
    auto result3 = generator.ParseCommand(json3);

    EXPECT_EQ(result1.size(), EXPECTED_SINGLE_EXECUTOR_COUNT);
    EXPECT_EQ(result2.size(), CLICK_AUTO_EXECUTOR_COUNT);
    EXPECT_EQ(result3.size(), SCROLL_AUTO_EXECUTOR_COUNT);
}

HWTEST_F(ExecutorGeneratorParseRegularCmdTest, ParseRegularCmd_AllTypes_CoverageCheck, TestSize.Level1)
{
    ExecutorGenerator generator(mockPipelineContext_);

    auto backpressResult = generator.ParseCommand(JsonUtil::ParseJsonString(VALID_BACKPRESS_JSON));
    EXPECT_EQ(backpressResult.size(), EXPECTED_SINGLE_EXECUTOR_COUNT);
    EXPECT_EQ(backpressResult[0]->GetType(), BACKPRESS);

    auto clickResult = generator.ParseCommand(JsonUtil::ParseJsonString(VALID_CLICK_JSON));
    EXPECT_EQ(clickResult.size(), CLICK_AUTO_EXECUTOR_COUNT);

    auto scrollResult = generator.ParseCommand(JsonUtil::ParseJsonString(VALID_SCROLL_JSON));
    EXPECT_EQ(scrollResult.size(), SCROLL_AUTO_EXECUTOR_COUNT);

    auto tapResult = generator.ParseCommand(JsonUtil::ParseJsonString(VALID_TAP_JSON));
    EXPECT_GE(tapResult.size(), EXPECTED_SINGLE_EXECUTOR_COUNT);

    auto slideResult = generator.ParseCommand(JsonUtil::ParseJsonString(VALID_SLIDE_JSON));
    EXPECT_GE(slideResult.size(), EXPECTED_SINGLE_EXECUTOR_COUNT);

    auto contentSwitchResult = generator.ParseCommand(JsonUtil::ParseJsonString(VALID_CONTENT_SWITCH_JSON));
    EXPECT_EQ(contentSwitchResult.size(), EXPECTED_SINGLE_EXECUTOR_COUNT);

    auto fallbackResult = generator.ParseCommand(JsonUtil::ParseJsonString(VALID_FALLBACK_JSON));
    EXPECT_EQ(fallbackResult.size(), EXPECTED_SINGLE_EXECUTOR_COUNT);
    EXPECT_EQ(fallbackResult[0]->GetType(), FALLBACK);
}

} // namespace OHOS::Ace::NG
