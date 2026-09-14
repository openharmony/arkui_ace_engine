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

#include <climits>
#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "gtest/gtest.h"

#include "adapter/ohos/entrance/ui_session/ui_session_batch_command.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {

class UISessionBatchCommandParserTest : public Test {};

HWTEST_F(UISessionBatchCommandParserTest, ParseNonBatchKeepsLegacyPath, TestSize.Level1)
{
    const auto result = UiSessionBatchCommand::Parse(R"({"cmd":"setText","params":{"value":"old"}})");
    const auto upperCase =
        UiSessionBatchCommand::Parse(R"({"Cmd":"batch","commands":{"1":{"cmd":"setText","params":{"value":"a"}}}})");
    const auto malformed = UiSessionBatchCommand::Parse(R"({"cmd":"batch"})garbage)");

    EXPECT_EQ(result.status, BatchParseStatus::NOT_BATCH);
    EXPECT_TRUE(result.items.empty());
    EXPECT_TRUE(result.diagnostics.empty());
    EXPECT_EQ(upperCase.status, BatchParseStatus::NOT_BATCH);
    EXPECT_EQ(malformed.status, BatchParseStatus::NOT_BATCH);
}

HWTEST_F(UISessionBatchCommandParserTest, ParseValidBatchBuildsCanonicalCommand, TestSize.Level1)
{
    const auto result = UiSessionBatchCommand::Parse(
        R"({"cmd":"batch","commands":{"101":{"cmd":"setText","params":{"value":"hello"}}}})");

    ASSERT_EQ(result.status, BatchParseStatus::VALID_BATCH);
    ASSERT_EQ(result.items.size(), 1u);
    EXPECT_EQ(result.items[0].nodeId, 101);
    EXPECT_EQ(result.items[0].semanticError, BatchDiagnosticReason::NONE);
    EXPECT_EQ(result.items[0].commandSummary, BatchCommandSummary::SET_TEXT);
    EXPECT_EQ(result.items[0].valueLength, 5);
    EXPECT_EQ(result.items[0].canonicalCommand, R"({"cmd":"setText","params":{"value":"hello"}})");
}

HWTEST_F(UISessionBatchCommandParserTest, ParseRejectsInvalidEnvelope, TestSize.Level1)
{
    const auto duplicateCmd = UiSessionBatchCommand::Parse(
        R"({"cmd":"batch","cmd":"batch","commands":{"1":{"cmd":"setText","params":{"value":"a"}}}})");
    const auto emptyCommands = UiSessionBatchCommand::Parse(R"({"cmd":"batch","commands":{}})");
    const auto missingCommands = UiSessionBatchCommand::Parse(R"({"cmd":"batch"})");

    EXPECT_EQ(duplicateCmd.status, BatchParseStatus::INVALID_BATCH);
    EXPECT_EQ(duplicateCmd.batchReason, BatchDiagnosticReason::INVALID_BATCH_ENVELOPE);
    EXPECT_EQ(emptyCommands.status, BatchParseStatus::INVALID_BATCH);
    EXPECT_EQ(emptyCommands.batchReason, BatchDiagnosticReason::EMPTY_COMMANDS);
    EXPECT_EQ(missingCommands.status, BatchParseStatus::INVALID_BATCH);
    EXPECT_EQ(missingCommands.batchReason, BatchDiagnosticReason::INVALID_BATCH_ENVELOPE);
}

HWTEST_F(UISessionBatchCommandParserTest, ParseCountsDuplicateMembersForLimit, TestSize.Level1)
{
    std::string commands;
    for (int32_t index = 0; index < 51; ++index) {
        if (!commands.empty()) {
            commands += ',';
        }
        commands += R"("1":{"cmd":"setText","params":{"value":"a"}})";
    }
    const auto result = UiSessionBatchCommand::Parse(R"({"cmd":"batch","commands":{)" + commands + "}}");

    EXPECT_EQ(result.status, BatchParseStatus::INVALID_BATCH);
    EXPECT_EQ(result.batchReason, BatchDiagnosticReason::TOO_MANY_COMMANDS);
    EXPECT_EQ(result.commandCount, 51u);
}

HWTEST_F(UISessionBatchCommandParserTest, ParseAcceptsFiftyMembers, TestSize.Level1)
{
    std::string commands;
    for (int32_t index = 0; index < 50; ++index) {
        if (!commands.empty()) {
            commands += ',';
        }
        commands += '"' + std::to_string(index) + R"(":{"cmd":"setText","params":{"value":"a"}})";
    }
    const auto result = UiSessionBatchCommand::Parse(R"({"cmd":"batch","commands":{)" + commands + "}}");

    EXPECT_EQ(result.status, BatchParseStatus::VALID_BATCH);
    EXPECT_EQ(result.items.size(), 50u);
    EXPECT_EQ(result.commandCount, 50u);
}

HWTEST_F(UISessionBatchCommandParserTest, ParseStopsAfterFirstExcessMember, TestSize.Level1)
{
    std::string commands;
    for (int32_t index = 0; index < 1024; ++index) {
        if (!commands.empty()) {
            commands += ',';
        }
        commands += R"("1":{"cmd":"setText","params":{"value":"a"}})";
    }
    const auto result = UiSessionBatchCommand::Parse(R"({"cmd":"batch","commands":{)" + commands + "}}");

    EXPECT_EQ(result.status, BatchParseStatus::INVALID_BATCH);
    EXPECT_EQ(result.batchReason, BatchDiagnosticReason::TOO_MANY_COMMANDS);
    EXPECT_EQ(result.commandCount, 51u);
    EXPECT_TRUE(result.items.empty());
    EXPECT_TRUE(result.diagnostics.empty());
}

HWTEST_F(UISessionBatchCommandParserTest, ParseValidatesNodeIdAndDuplicateFirstWins, TestSize.Level1)
{
    const auto result =
        UiSessionBatchCommand::Parse(R"({"cmd":"batch","commands":{"0":{"cmd":"setText","params":{"value":"zero"}},)"
            R"("2147483647":{"cmd":"setText","params":{"value":"max"}},)"
            R"("01":{"cmd":"setText","params":{"value":"bad"}},)"
            R"("1":{"cmd":"setText","params":{"value":"first"}},)"
            R"("1":{"cmd":"setText","params":{"value":"second"}}}})");

    ASSERT_EQ(result.status, BatchParseStatus::VALID_BATCH);
    ASSERT_EQ(result.items.size(), 3u);
    EXPECT_EQ(result.items[0].nodeId, 0);
    EXPECT_EQ(result.items[1].nodeId, INT32_MAX);
    EXPECT_EQ(result.items[2].canonicalCommand, R"({"cmd":"setText","params":{"value":"first"}})");
    ASSERT_EQ(result.diagnostics.size(), 2u);
    EXPECT_EQ(result.diagnostics[0].reason, BatchDiagnosticReason::INVALID_NODE_ID);
    EXPECT_FALSE(result.diagnostics[0].hasNodeId);
    EXPECT_EQ(result.diagnostics[0].ordinal, 3u);
    EXPECT_EQ(result.diagnostics[0].keyLength, 2u);
    EXPECT_EQ(result.diagnostics[1].reason, BatchDiagnosticReason::DUPLICATE_NODE_ID);
    EXPECT_TRUE(result.diagnostics[1].hasNodeId);
    EXPECT_EQ(result.diagnostics[1].nodeId, 1);
}

HWTEST_F(UISessionBatchCommandParserTest, ParseRejectsNonCanonicalNodeIds, TestSize.Level1)
{
    const auto result =
        UiSessionBatchCommand::Parse(R"({"cmd":"batch","commands":{"":{"cmd":"setText","params":{"value":"a"}},)"
            R"("-1":{"cmd":"setText","params":{"value":"b"}},)"
            R"("+1":{"cmd":"setText","params":{"value":"c"}},)"
            R"(" 1":{"cmd":"setText","params":{"value":"d"}},)"
            R"("2147483648":{"cmd":"setText","params":{"value":"e"}}}})");

    ASSERT_EQ(result.status, BatchParseStatus::VALID_BATCH);
    EXPECT_TRUE(result.items.empty());
    ASSERT_EQ(result.diagnostics.size(), 5u);
    for (const auto& diagnostic : result.diagnostics) {
        EXPECT_EQ(diagnostic.reason, BatchDiagnosticReason::INVALID_NODE_ID);
        EXPECT_FALSE(diagnostic.hasNodeId);
    }
}

HWTEST_F(UISessionBatchCommandParserTest, ParseRejectsDuplicateRequiredItemFields, TestSize.Level1)
{
    const auto result = UiSessionBatchCommand::Parse(
        R"({"cmd":"batch","commands":{"1":{"cmd":"setText","cmd":"setText","params":{"value":"a"}},)"
        R"("2":{"cmd":"setText","params":{"value":"b"},"params":{"value":"b"}},)"
        R"("3":{"cmd":"setText","params":{"value":"c","value":"c"}}}})");

    ASSERT_EQ(result.status, BatchParseStatus::VALID_BATCH);
    ASSERT_EQ(result.items.size(), 3u);
    for (const auto& item : result.items) {
        EXPECT_EQ(item.semanticError, BatchDiagnosticReason::INVALID_PARAMS);
        EXPECT_TRUE(item.canonicalCommand.empty());
    }
}

HWTEST_F(UISessionBatchCommandParserTest, ParsePreservesSemanticErrorsWithoutSensitiveText, TestSize.Level1)
{
    const std::string secretCmd = "privateUnknownCommand";
    const std::string secretValue = "privateValue";
    const auto result = UiSessionBatchCommand::Parse(
        R"({"cmd":"batch","commands":{"1":{"cmd":")" + secretCmd +
        R"(","params":{"value":")" + secretValue +
        R"("}},"2":{"cmd":"setText","params":{}}}})");

    ASSERT_EQ(result.status, BatchParseStatus::VALID_BATCH);
    ASSERT_EQ(result.items.size(), 2u);
    EXPECT_EQ(result.items[0].semanticError, BatchDiagnosticReason::UNSUPPORTED_CMD);
    EXPECT_EQ(result.items[0].commandSummary, BatchCommandSummary::UNSUPPORTED);
    EXPECT_TRUE(result.items[0].canonicalCommand.empty());
    EXPECT_EQ(result.items[0].valueLength, static_cast<int32_t>(secretValue.size()));
    EXPECT_EQ(result.items[1].semanticError, BatchDiagnosticReason::INVALID_PARAMS);
    EXPECT_EQ(result.items[1].commandSummary, BatchCommandSummary::SET_TEXT);
    EXPECT_TRUE(result.items[1].canonicalCommand.empty());
    for (const auto& item : result.items) {
        EXPECT_EQ(item.canonicalCommand.find(secretCmd), std::string::npos);
        EXPECT_EQ(item.canonicalCommand.find(secretValue), std::string::npos);
    }
}

HWTEST_F(UISessionBatchCommandParserTest, ParseValidatesValueUtf8ByteLimit, TestSize.Level1)
{
    std::string allowedValue;
    for (int32_t index = 0; index < 128; ++index) {
        allowedValue += "文";
    }
    const std::string rejectedValue(385, 'b');
    const auto result = UiSessionBatchCommand::Parse(
        R"({"cmd":"batch","commands":{"1":{"cmd":"setText","params":{"value":")" + allowedValue +
        R"("}},"2":{"cmd":"setText","params":{"value":")" + rejectedValue + R"("}}}})");

    ASSERT_EQ(result.status, BatchParseStatus::VALID_BATCH);
    ASSERT_EQ(result.items.size(), 2u);
    EXPECT_EQ(result.items[0].semanticError, BatchDiagnosticReason::NONE);
    EXPECT_EQ(result.items[0].valueLength, 384);
    EXPECT_FALSE(result.items[0].canonicalCommand.empty());
    EXPECT_EQ(result.items[1].semanticError, BatchDiagnosticReason::VALUE_TOO_LONG);
    EXPECT_EQ(result.items[1].valueLength, 385);
    EXPECT_TRUE(result.items[1].canonicalCommand.empty());
}

HWTEST_F(UISessionBatchCommandParserTest, ParseRejectsNegativeZeroNodeIds, TestSize.Level1)
{
    const auto result =
        UiSessionBatchCommand::Parse(
            R"({"cmd":"batch","commands":{"-0":{"cmd":"setText","params":{"value":"bad"}},)"
            R"("-00":{"cmd":"setText","params":{"value":"bad"}},)"
            R"("0":{"cmd":"setText","params":{"value":"valid"}}}})");

    ASSERT_EQ(result.items.size(), 1u);
    EXPECT_EQ(result.items[0].nodeId, 0);
    EXPECT_EQ(result.items[0].canonicalCommand, R"({"cmd":"setText","params":{"value":"valid"}})");
    ASSERT_EQ(result.diagnostics.size(), 2u);
    for (const auto& diagnostic : result.diagnostics) {
        EXPECT_EQ(diagnostic.reason, BatchDiagnosticReason::INVALID_NODE_ID);
    }
}

HWTEST_F(UISessionBatchCommandParserTest, ParseDoesNotMatchNullSuffixedEnvelope, TestSize.Level1)
{
    EXPECT_EQ(UiSessionBatchCommand::Parse(
        R"({"cmd":"batch\u0000suffix","commands":{"1":{"cmd":"setText","params":{"value":"a"}}}})")
        .status,
        BatchParseStatus::NOT_BATCH);
    EXPECT_EQ(UiSessionBatchCommand::Parse(
        R"({"cmd\u0000suffix":"batch","commands":{"1":{"cmd":"setText","params":{"value":"a"}}}})")
        .status,
        BatchParseStatus::NOT_BATCH);
    EXPECT_EQ(UiSessionBatchCommand::Parse(
        R"({"cmd":"batch","commands\u0000suffix":{"1":{"cmd":"setText","params":{"value":"a"}}}})")
        .status,
        BatchParseStatus::INVALID_BATCH);
}

HWTEST_F(UISessionBatchCommandParserTest, ParseNullNodeIdDoesNotShadowValidNode, TestSize.Level1)
{
    const auto result = UiSessionBatchCommand::Parse(
        R"({"cmd":"batch","commands":{"123\u0000bad":{"cmd":"setText","params":{"value":"bad"}},)"
        R"("123":{"cmd":"setText","params":{"value":"valid"}}}})");

    ASSERT_EQ(result.items.size(), 1u);
    EXPECT_EQ(result.items[0].nodeId, 123);
    EXPECT_EQ(result.items[0].canonicalCommand, R"({"cmd":"setText","params":{"value":"valid"}})");
    ASSERT_EQ(result.diagnostics.size(), 1u);
    EXPECT_EQ(result.diagnostics[0].reason, BatchDiagnosticReason::INVALID_NODE_ID);
}

HWTEST_F(UISessionBatchCommandParserTest, ParseRejectsNullTextAndKeepsOtherItems, TestSize.Level1)
{
    const auto result = UiSessionBatchCommand::Parse(
        R"({"ignored":["x\u0000y",{"key\u0000suffix":"value"}],"cmd":"batch","commands":{)"
        R"("1":{"cmd":"setText","params":{"value":"a\u0000b"}},)"
        R"("2":{"cmd":"setText","params":{"value":"a\\u0000b"}},)"
        R"("3":{"cmd":"setText","params":{"value\u0000suffix":"bad"}},)"
        R"("4":{"cmd":"setText\u0000suffix","params":{"value":"bad"}},)"
        R"("5":{"cmd":"setText","ignored":"\u0000","params":{"value":"quote\"slash\\"}}}})");

    ASSERT_EQ(result.items.size(), 5u);
    EXPECT_EQ(result.items[0].semanticError, BatchDiagnosticReason::INVALID_PARAMS);
    EXPECT_TRUE(result.items[0].canonicalCommand.empty());
    EXPECT_EQ(result.items[1].semanticError, BatchDiagnosticReason::NONE);
    EXPECT_EQ(result.items[1].canonicalCommand, R"({"cmd":"setText","params":{"value":"a\\u0000b"}})");
    EXPECT_EQ(result.items[2].semanticError, BatchDiagnosticReason::INVALID_PARAMS);
    EXPECT_EQ(result.items[3].semanticError, BatchDiagnosticReason::UNSUPPORTED_CMD);
    EXPECT_EQ(result.items[4].semanticError, BatchDiagnosticReason::NONE);
    EXPECT_EQ(result.items[4].canonicalCommand, R"({"cmd":"setText","params":{"value":"quote\"slash\\"}})");
}

class UISessionBatchCommandDispatchTest : public Test {
public:
    void SetUp() override
    {
        callbacks_.postTask = [this](std::function<void()>&& task) {
            ++postCount_;
            task_ = std::move(task);
            return postResult_;
        };
        callbacks_.resolveTarget = [this](int32_t nodeId) {
            ++resolveCount_;
            resolvedIds_.emplace_back(nodeId);
            return BatchResolvedTarget { .status = BatchTargetStatus::READY,
                .execute = [this, nodeId](const std::string& command) {
                    ++executeCount_;
                    executedIds_.emplace_back(nodeId);
                    executedCommands_.emplace_back(command);
                    return executeResult_;
                } };
        };
        callbacks_.itemDiagnosticSink = [this](const BatchDiagnostic& diagnostic) {
            itemDiagnostics_.emplace_back(diagnostic);
        };
        callbacks_.batchDiagnosticSink = [this](const BatchLevelDiagnostic& diagnostic) {
            batchDiagnostics_.emplace_back(diagnostic);
        };
    }

protected:
    BatchDispatchCallbacks callbacks_;
    std::function<void()> task_;
    bool postResult_ = true;
    bool executeResult_ = true;
    int32_t postCount_ = 0;
    int32_t resolveCount_ = 0;
    int32_t executeCount_ = 0;
    std::vector<int32_t> resolvedIds_;
    std::vector<int32_t> executedIds_;
    std::vector<std::string> executedCommands_;
    std::vector<BatchDiagnostic> itemDiagnostics_;
    std::vector<BatchLevelDiagnostic> batchDiagnostics_;
};

HWTEST_F(UISessionBatchCommandDispatchTest, DispatchNonBatchKeepsLegacyPath, TestSize.Level1)
{
    const bool handled = UiSessionBatchCommand::Dispatch(R"({"cmd":"legacy"})", callbacks_);

    EXPECT_FALSE(handled);
    EXPECT_EQ(postCount_, 0);
    EXPECT_TRUE(batchDiagnostics_.empty());
}

HWTEST_F(UISessionBatchCommandDispatchTest, DispatchInvalidBatchDoesNotPostTask, TestSize.Level1)
{
    const bool handled = UiSessionBatchCommand::Dispatch(R"({"cmd":"batch","commands":{}})", callbacks_);

    EXPECT_TRUE(handled);
    EXPECT_EQ(postCount_, 0);
    ASSERT_EQ(batchDiagnostics_.size(), 1u);
    EXPECT_EQ(batchDiagnostics_[0].reason, BatchDiagnosticReason::EMPTY_COMMANDS);
}

HWTEST_F(UISessionBatchCommandDispatchTest, DispatchOversizedBatchDoesNotPostTask, TestSize.Level1)
{
    std::string commands;
    for (int32_t index = 0; index < 100; ++index) {
        if (!commands.empty()) {
            commands += ',';
        }
        commands += '"' + std::to_string(index) + R"(":{"cmd":"setText","params":{"value":"a"}})";
    }
    EXPECT_TRUE(UiSessionBatchCommand::Dispatch(R"({"cmd":"batch","commands":{)" + commands + "}}", callbacks_));

    EXPECT_EQ(postCount_, 0);
    EXPECT_EQ(resolveCount_, 0);
    EXPECT_EQ(executeCount_, 0);
    EXPECT_TRUE(itemDiagnostics_.empty());
    ASSERT_EQ(batchDiagnostics_.size(), 1u);
    EXPECT_EQ(batchDiagnostics_[0].reason, BatchDiagnosticReason::TOO_MANY_COMMANDS);
    EXPECT_EQ(batchDiagnostics_[0].commandCount, 51u);
}

HWTEST_F(UISessionBatchCommandDispatchTest, DispatchValidBatchPostsExactlyOneTask, TestSize.Level1)
{
    const bool handled =
        UiSessionBatchCommand::Dispatch(R"({"cmd":"batch","commands":{"1":{"cmd":"setText","params":{"value":"a"}},)"
                                        R"("bad":{"cmd":"setText","params":{"value":"b"}}}})",
            callbacks_);

    EXPECT_TRUE(handled);
    EXPECT_EQ(postCount_, 1);
    ASSERT_EQ(itemDiagnostics_.size(), 1u);
    EXPECT_EQ(itemDiagnostics_[0].reason, BatchDiagnosticReason::INVALID_NODE_ID);
    ASSERT_TRUE(task_);
    task_();
    EXPECT_EQ(resolveCount_, 1);
    EXPECT_EQ(executeCount_, 1);
}

HWTEST_F(UISessionBatchCommandDispatchTest, DispatchChecksTargetBeforeCommandSemanticError, TestSize.Level1)
{
    callbacks_.resolveTarget = [this](int32_t nodeId) {
        ++resolveCount_;
        if (nodeId == 1) {
            return BatchResolvedTarget { .status = BatchTargetStatus::NOT_FOUND };
        }
        if (nodeId == 2) {
            return BatchResolvedTarget { .status = BatchTargetStatus::UNSUPPORTED_TYPE };
        }
        return BatchResolvedTarget { .status = BatchTargetStatus::READY, .execute = [this, nodeId](const std::string&) {
                                        ++executeCount_;
                                        return nodeId != 4;
                                    } };
    };
    const std::string tooLong(385, 'x');
    const std::string command = R"({"cmd":"batch","commands":{"1":{"cmd":"other","params":{"value":"a"}},)"
                                R"("2":{"cmd":"setText","params":{}},)"
                                R"("3":{"cmd":"setText","params":{"value":")" +
                                tooLong +
                                R"("}},"4":{"cmd":"setText","params":{"value":"d"}},)"
                                R"("5":{"cmd":"setText","params":{"value":"e"}}}})";

    EXPECT_TRUE(UiSessionBatchCommand::Dispatch(command, callbacks_));
    ASSERT_TRUE(task_);
    task_();

    EXPECT_EQ(resolveCount_, 5);
    EXPECT_EQ(executeCount_, 2);
    ASSERT_EQ(itemDiagnostics_.size(), 4u);
    EXPECT_EQ(itemDiagnostics_[0].reason, BatchDiagnosticReason::NODE_NOT_FOUND);
    EXPECT_EQ(itemDiagnostics_[1].reason, BatchDiagnosticReason::UNSUPPORTED_NODE_TYPE);
    EXPECT_EQ(itemDiagnostics_[2].reason, BatchDiagnosticReason::VALUE_TOO_LONG);
    EXPECT_EQ(itemDiagnostics_[3].reason, BatchDiagnosticReason::COMMAND_EXECUTION_FAILED);
    EXPECT_EQ(itemDiagnostics_[3].nodeId, 4);
}

HWTEST_F(UISessionBatchCommandDispatchTest, DispatchReportsUnavailableExecutor, TestSize.Level1)
{
    callbacks_.postTask = nullptr;

    EXPECT_TRUE(UiSessionBatchCommand::Dispatch(
        R"({"cmd":"batch","commands":{"1":{"cmd":"setText","params":{"value":"a"}}}})", callbacks_));
    ASSERT_EQ(batchDiagnostics_.size(), 1u);
    EXPECT_EQ(batchDiagnostics_[0].reason, BatchDiagnosticReason::TASK_EXECUTOR_UNAVAILABLE);
    EXPECT_EQ(resolveCount_, 0);
}

HWTEST_F(UISessionBatchCommandDispatchTest, DispatchReportsPostTaskFailure, TestSize.Level1)
{
    postResult_ = false;

    EXPECT_TRUE(UiSessionBatchCommand::Dispatch(
        R"({"cmd":"batch","commands":{"1":{"cmd":"setText","params":{"value":"a"}}}})", callbacks_));
    EXPECT_EQ(postCount_, 1);
    ASSERT_EQ(batchDiagnostics_.size(), 1u);
    EXPECT_EQ(batchDiagnostics_[0].reason, BatchDiagnosticReason::POST_TASK_FAILED);
    EXPECT_EQ(resolveCount_, 0);
}

HWTEST_F(UISessionBatchCommandDispatchTest, DispatchReleasesContextAfterTask, TestSize.Level1)
{
    std::weak_ptr<int32_t> weakLifetime;
    auto lifetime = std::make_shared<int32_t>(1);
    weakLifetime = lifetime;
    callbacks_.resolveTarget = [lifetime](int32_t) {
        return BatchResolvedTarget { .status = BatchTargetStatus::READY,
            .execute = [](const std::string&) { return true; } };
    };
    lifetime.reset();

    EXPECT_TRUE(UiSessionBatchCommand::Dispatch(
        R"({"cmd":"batch","commands":{"1":{"cmd":"setText","params":{"value":"a"}}}})", callbacks_));
    callbacks_.resolveTarget = nullptr;
    EXPECT_FALSE(weakLifetime.expired());
    ASSERT_TRUE(task_);
    task_();
    task_ = nullptr;
    EXPECT_TRUE(weakLifetime.expired());
}

HWTEST_F(UISessionBatchCommandDispatchTest, DispatchSuccessDoesNotReportFailure, TestSize.Level1)
{
    EXPECT_TRUE(UiSessionBatchCommand::Dispatch(
        R"({"cmd":"batch","commands":{"1":{"cmd":"setText","params":{"value":"a"}}}})", callbacks_));
    ASSERT_TRUE(task_);
    task_();
    EXPECT_EQ(executeCount_, 1);
    EXPECT_TRUE(itemDiagnostics_.empty());
}

} // namespace
} // namespace OHOS::Ace
