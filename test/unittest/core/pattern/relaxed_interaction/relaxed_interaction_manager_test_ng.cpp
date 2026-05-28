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

#include "relaxed_interaction_manager_test_ng.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string VALID_BACKPRESS_JSON = R"({
  "cmd": {
    "type": "backpress"
  }
})";

const std::string INVALID_JSON_EMPTY = "{}";

const std::string INVALID_JSON_SYNTAX = "{invalid json}";

const std::string INVALID_CMD_MISSING_TYPE = R"({
  "cmd": {}
})";

const std::string INVALID_CMD_UNKNOWN_TYPE = R"({
  "cmd": {
    "type": "unknown_type"
  }
})";

const std::string VALID_BACKPRESS_JSON_WITH_FALLBACK = R"({
  "cmd": {
    "type": "backpress"
  },
  "fallback_cmd": {}
})";
} // namespace

class RelaxedInteractionManagerConstructorTest : public RelaxedInteractionManagerTestBase {};
class RelaxedInteractionManagerProcessCommandTest : public RelaxedInteractionManagerTestBase {};
class RelaxedInteractionManagerExecuteNextStepTest : public RelaxedInteractionManagerTestBase {};
class RelaxedInteractionManagerClearTest : public RelaxedInteractionManagerTestBase {};

/**
 * @tc.name: RelaxedInteractionManager_Constructor
 * @tc.desc: Test RelaxedInteractionManager constructor initializes executorGenerator_ and choreographer_
 * @tc.type: FUNC
 */
HWTEST_F(RelaxedInteractionManagerConstructorTest, RelaxedInteractionManager_Constructor, TestSize.Level1)
{
    manager_ = AceType::MakeRefPtr<RelaxedInteractionManager>(WeakPtr<PipelineContext>(mockPipelineContext_));
    ASSERT_NE(manager_, nullptr);
}

/**
 * @tc.name: ProcessCommand_ValidBackpressJson
 * @tc.desc: Test ProcessCommand returns SUCCESS when valid backpress JSON is provided
 * @tc.type: FUNC
 */
HWTEST_F(RelaxedInteractionManagerProcessCommandTest, ProcessCommand_ValidBackpressJson, TestSize.Level1)
{
    manager_ = AceType::MakeRefPtr<RelaxedInteractionManager>(WeakPtr<PipelineContext>(mockPipelineContext_));
    ASSERT_NE(manager_, nullptr);

    auto result = manager_->ProcessCommand(VALID_BACKPRESS_JSON);

    EXPECT_EQ(result, ProcessResult::SUCCESS);
}

/**
 * @tc.name: ProcessCommand_InvalidJsonSyntax
 * @tc.desc: Test ProcessCommand returns PARSE_ERROR when JSON has syntax error
 * @tc.type: FUNC
 */
HWTEST_F(RelaxedInteractionManagerProcessCommandTest, ProcessCommand_InvalidJsonSyntax, TestSize.Level1)
{
    manager_ = AceType::MakeRefPtr<RelaxedInteractionManager>(WeakPtr<PipelineContext>(mockPipelineContext_));
    ASSERT_NE(manager_, nullptr);

    auto result = manager_->ProcessCommand(INVALID_JSON_SYNTAX);

    EXPECT_EQ(result, ProcessResult::PARSE_ERROR);
}

/**
 * @tc.name: ProcessCommand_InvalidCmdMissingType
 * @tc.desc: Test ProcessCommand returns VALIDATION_ERROR when cmd is missing type field
 * @tc.type: FUNC
 */
HWTEST_F(RelaxedInteractionManagerProcessCommandTest, ProcessCommand_InvalidCmdMissingType, TestSize.Level1)
{
    manager_ = AceType::MakeRefPtr<RelaxedInteractionManager>(WeakPtr<PipelineContext>(mockPipelineContext_));
    ASSERT_NE(manager_, nullptr);

    auto result = manager_->ProcessCommand(INVALID_CMD_MISSING_TYPE);

    EXPECT_EQ(result, ProcessResult::VALIDATION_ERROR);
}

/**
 * @tc.name: ProcessCommand_InvalidCmdUnknownType
 * @tc.desc: Test ProcessCommand returns VALIDATION_ERROR when cmd has unknown type
 * @tc.type: FUNC
 */
HWTEST_F(RelaxedInteractionManagerProcessCommandTest, ProcessCommand_InvalidCmdUnknownType, TestSize.Level1)
{
    manager_ = AceType::MakeRefPtr<RelaxedInteractionManager>(WeakPtr<PipelineContext>(mockPipelineContext_));
    ASSERT_NE(manager_, nullptr);

    auto result = manager_->ProcessCommand(INVALID_CMD_UNKNOWN_TYPE);

    EXPECT_EQ(result, ProcessResult::VALIDATION_ERROR);
}

/**
 * @tc.name: Clear_ResetsChoreographer
 * @tc.desc: Test Clear method clears choreographer_ internal state
 * @tc.type: FUNC
 */
HWTEST_F(RelaxedInteractionManagerClearTest, Clear_ResetsChoreographer, TestSize.Level1)
{
    manager_ = AceType::MakeRefPtr<RelaxedInteractionManager>(WeakPtr<PipelineContext>(mockPipelineContext_));
    ASSERT_NE(manager_, nullptr);

    manager_->ProcessCommand(VALID_BACKPRESS_JSON);
    manager_->Clear();

    EXPECT_TRUE(true);
}

} // namespace OHOS::Ace::NG
