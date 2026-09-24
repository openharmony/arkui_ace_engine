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

#include "adapter/ohos/entrance/ui_session/ui_session_batch_command.h"

#include <charconv>
#include <climits>
#include <cstring>
#include <deque>
#include <iterator>
#include <memory>
#include <unordered_set>

#include "cJSON.h"

namespace OHOS::Ace {
namespace {

constexpr size_t MAX_BATCH_COMMAND_COUNT = 50;
constexpr size_t MAX_SET_TEXT_VALUE_LENGTH = 384;
constexpr char ESCAPED_NULL_SEQUENCE[] = "\\u0000";
constexpr char BATCH_COMMAND[] = "batch";
constexpr char SET_TEXT_COMMAND[] = "setText";

using JsonOwner = std::unique_ptr<cJSON, decltype(&cJSON_Delete)>;
using JsonStringOwner = std::unique_ptr<char, decltype(&cJSON_free)>;

// cJSON decodes embedded NULs but exposes only zero-terminated strings. Track affected strings from
// the validated source so they cannot match truncated keys/commands or be written as truncated text.
class BatchJsonStrings {
public:
    BatchJsonStrings(const cJSON* root, const std::string& source)
    {
        if (source.find(ESCAPED_NULL_SEQUENCE) != std::string::npos) {
            size_t position = 0;
            CollectNullStrings(root, source, position);
        }
    }

    bool IsValid(const char* value) const
    {
        return value != nullptr && nullStrings_.count(value) == 0;
    }

    bool Equals(const char* value, const char* expected) const
    {
        return IsValid(value) && std::strcmp(value, expected) == 0;
    }

private:
    bool ReadStringHasNull(const std::string& source, size_t& position) const
    {
        position = source.find('"', position);
        if (position == std::string::npos) {
            return false;
        }
        bool hasNull = false;
        for (++position; position < source.size(); ++position) {
            if (source[position] == '"') {
                ++position;
                break;
            }
            if (source[position] == '\\') {
                hasNull = hasNull || source.compare(position, sizeof(ESCAPED_NULL_SEQUENCE) - 1,
                    ESCAPED_NULL_SEQUENCE) == 0;
                ++position; // Skip the escaped character, including escaped backslashes and quotes.
            }
        }
        return hasNull;
    }

    void CollectNullStrings(const cJSON* node, const std::string& source, size_t& position)
    {
        for (auto item = node; item != nullptr; item = item->next) {
            if (item->string && ReadStringHasNull(source, position)) {
                nullStrings_.emplace(item->string);
            }
            if (cJSON_IsString(item) && ReadStringHasNull(source, position)) {
                nullStrings_.emplace(item->valuestring);
            }
            CollectNullStrings(item->child, source, position);
        }
    }

    std::unordered_set<const char*> nullStrings_;
};

size_t CountNamedMembers(const cJSON* object, const char* name, const cJSON** first, const BatchJsonStrings& strings)
{
    size_t count = 0;
    for (auto child = object == nullptr ? nullptr : object->child; child != nullptr; child = child->next) {
        if (strings.Equals(child->string, name)) {
            if (count == 0 && first != nullptr) {
                *first = child;
            }
            ++count;
        }
    }
    return count;
}

bool ParseNodeId(const char* key, int32_t& nodeId, const BatchJsonStrings& strings)
{
    if (!strings.IsValid(key) || key[0] < '0' || key[0] > '9' || (key[0] == '0' && key[1] != '\0')) {
        return false;
    }
    const auto length = std::strlen(key);
    int64_t parsed = 0;
    const auto result = std::from_chars(key, key + length, parsed);
    if (result.ec != std::errc() || result.ptr != key + length || parsed < 0 || parsed > INT32_MAX) {
        return false;
    }
    nodeId = static_cast<int32_t>(parsed);
    return true;
}

int32_t GetValueLength(const cJSON* command, const BatchJsonStrings& strings)
{
    const cJSON* params = nullptr;
    if (!cJSON_IsObject(command) || CountNamedMembers(command, "params", &params, strings) != 1 ||
        !cJSON_IsObject(params)) {
        return -1;
    }
    const cJSON* value = nullptr;
    if (CountNamedMembers(params, "value", &value, strings) != 1 || !cJSON_IsString(value) ||
        !strings.IsValid(value->valuestring)) {
        return -1;
    }
    const auto length = std::strlen(value->valuestring);
    return length > static_cast<size_t>(INT32_MAX) ? -1 : static_cast<int32_t>(length);
}

std::string BuildCanonicalCommand(const char* value)
{
    JsonOwner root(cJSON_CreateObject(), cJSON_Delete);
    JsonOwner params(cJSON_CreateObject(), cJSON_Delete);
    if (!root || !params || !cJSON_AddStringToObject(root.get(), "cmd", SET_TEXT_COMMAND) ||
        !cJSON_AddStringToObject(params.get(), "value", value)) {
        return {};
    }
    if (!cJSON_AddItemToObject(root.get(), "params", params.get())) {
        return {};
    }
    params.release();
    JsonStringOwner text(cJSON_PrintUnformatted(root.get()), cJSON_free);
    return text ? text.get() : "";
}

BatchCommandItem AnalyzeCommand(const cJSON* command, int32_t nodeId, size_t ordinal, const BatchJsonStrings& strings)
{
    BatchCommandItem item { .nodeId = nodeId, .ordinal = ordinal };
    if (!cJSON_IsObject(command)) {
        item.semanticError = BatchDiagnosticReason::INVALID_PARAMS;
        return item;
    }
    const cJSON* cmd = nullptr;
    const auto cmdCount = CountNamedMembers(command, "cmd", &cmd, strings);
    if (cmdCount != 1 || !cJSON_IsString(cmd) || cmd->valuestring == nullptr) {
        item.semanticError = BatchDiagnosticReason::INVALID_PARAMS;
        item.commandSummary = BatchCommandSummary::MISSING_OR_NON_STRING;
        item.valueLength = GetValueLength(command, strings);
        return item;
    }
    item.valueLength = GetValueLength(command, strings);
    if (!strings.Equals(cmd->valuestring, SET_TEXT_COMMAND)) {
        item.semanticError = BatchDiagnosticReason::UNSUPPORTED_CMD;
        item.commandSummary = BatchCommandSummary::UNSUPPORTED;
        return item;
    }
    item.commandSummary = BatchCommandSummary::SET_TEXT;
    const cJSON* params = nullptr;
    const cJSON* value = nullptr;
    if (CountNamedMembers(command, "params", &params, strings) != 1 || !cJSON_IsObject(params) ||
        CountNamedMembers(params, "value", &value, strings) != 1 || !cJSON_IsString(value) ||
        !strings.IsValid(value->valuestring)) {
        item.semanticError = BatchDiagnosticReason::INVALID_PARAMS;
        return item;
    }
    if (static_cast<size_t>(item.valueLength) > MAX_SET_TEXT_VALUE_LENGTH) {
        item.semanticError = BatchDiagnosticReason::VALUE_TOO_LONG;
        return item;
    }
    item.canonicalCommand = BuildCanonicalCommand(value->valuestring);
    if (item.canonicalCommand.empty()) {
        item.semanticError = BatchDiagnosticReason::INVALID_PARAMS;
    }
    return item;
}

BatchDiagnostic MakePreDispatchDiagnostic(
    const BatchCommandItem& item, BatchDiagnosticReason reason, size_t keyLength, bool hasNodeId)
{
    return BatchDiagnostic { .hasNodeId = hasNodeId,
        .nodeId = item.nodeId,
        .ordinal = item.ordinal,
        .keyLength = keyLength,
        .reason = reason,
        .commandSummary = item.commandSummary,
        .valueLength = item.valueLength };
}

BatchParseResult ParseBatchCommands(const cJSON* commands, const BatchJsonStrings& strings)
{
    BatchParseResult result { .status = BatchParseStatus::VALID_BATCH };
    std::unordered_set<int32_t> nodeIds;
    for (auto child = commands->child; child != nullptr; child = child->next) {
        ++result.commandCount;
        if (result.commandCount > MAX_BATCH_COMMAND_COUNT) {
            result.status = BatchParseStatus::INVALID_BATCH;
            result.batchReason = BatchDiagnosticReason::TOO_MANY_COMMANDS;
            result.items.clear();
            result.diagnostics.clear();
            break;
        }
        int32_t nodeId = -1;
        const auto keyLength = child->string == nullptr ? 0 : std::strlen(child->string);
        if (!ParseNodeId(child->string, nodeId, strings)) {
            auto item = AnalyzeCommand(child, nodeId, result.commandCount, strings);
            result.diagnostics.emplace_back(
                MakePreDispatchDiagnostic(item, BatchDiagnosticReason::INVALID_NODE_ID, keyLength, false));
            continue;
        }
        auto item = AnalyzeCommand(child, nodeId, result.commandCount, strings);
        if (!nodeIds.emplace(nodeId).second) {
            result.diagnostics.emplace_back(
                MakePreDispatchDiagnostic(item, BatchDiagnosticReason::DUPLICATE_NODE_ID, keyLength, true));
            continue;
        }
        result.items.emplace_back(std::move(item));
    }
    return result;
}

struct BatchDispatchContext {
    std::deque<BatchCommandItem> items;
    std::function<BatchResolvedTarget(int32_t)> resolveTarget;
    std::function<void(const BatchDiagnostic&)> diagnosticSink;
};

void EmitItemDiagnostic(const BatchDispatchContext& context, const BatchCommandItem& item, BatchDiagnosticReason reason)
{
    if (!context.diagnosticSink) {
        return;
    }
    context.diagnosticSink(BatchDiagnostic { .hasNodeId = true,
        .nodeId = item.nodeId,
        .ordinal = item.ordinal,
        .reason = reason,
        .commandSummary = item.commandSummary,
        .valueLength = item.valueLength });
}

void ProcessItem(const BatchDispatchContext& context, const BatchCommandItem& item)
{
    const auto target = context.resolveTarget ? context.resolveTarget(item.nodeId) : BatchResolvedTarget {};
    if (target.status == BatchTargetStatus::NOT_FOUND) {
        EmitItemDiagnostic(context, item, BatchDiagnosticReason::NODE_NOT_FOUND);
        return;
    }
    if (target.status != BatchTargetStatus::READY || !target.execute) {
        EmitItemDiagnostic(context, item, BatchDiagnosticReason::UNSUPPORTED_NODE_TYPE);
        return;
    }
    if (item.semanticError != BatchDiagnosticReason::NONE) {
        EmitItemDiagnostic(context, item, item.semanticError);
        return;
    }
    if (!target.execute(item.canonicalCommand)) {
        EmitItemDiagnostic(context, item, BatchDiagnosticReason::COMMAND_EXECUTION_FAILED);
    }
}

void ProcessBatch(const std::shared_ptr<BatchDispatchContext>& context)
{
    while (!context->items.empty()) {
        ProcessItem(*context, context->items.front());
        context->items.pop_front();
    }
}

void EmitBatchDiagnostic(
    const BatchDispatchCallbacks& callbacks, BatchDiagnosticReason reason, size_t commandCount, size_t commandLength)
{
    if (callbacks.batchDiagnosticSink) {
        callbacks.batchDiagnosticSink(
            BatchLevelDiagnostic { .reason = reason, .commandCount = commandCount, .commandLength = commandLength });
    }
}

} // namespace

BatchParseResult UiSessionBatchCommand::Parse(const std::string& command)
{
    const char* parseEnd = nullptr;
    JsonOwner root(cJSON_ParseWithOpts(command.c_str(), &parseEnd, true), cJSON_Delete);
    if (!root || parseEnd != command.c_str() + command.size() || !cJSON_IsObject(root.get())) {
        return {};
    }
    const BatchJsonStrings strings(root.get(), command);
    const cJSON* cmd = nullptr;
    const auto cmdCount = CountNamedMembers(root.get(), "cmd", &cmd, strings);
    if (cmdCount == 0 || !cJSON_IsString(cmd) || cmd->valuestring == nullptr ||
        !strings.Equals(cmd->valuestring, BATCH_COMMAND)) {
        return {};
    }
    if (cmdCount != 1) {
        return { .status = BatchParseStatus::INVALID_BATCH,
            .batchReason = BatchDiagnosticReason::INVALID_BATCH_ENVELOPE };
    }
    const cJSON* commands = nullptr;
    if (CountNamedMembers(root.get(), "commands", &commands, strings) != 1 || !cJSON_IsObject(commands)) {
        return { .status = BatchParseStatus::INVALID_BATCH,
            .batchReason = BatchDiagnosticReason::INVALID_BATCH_ENVELOPE };
    }
    if (commands->child == nullptr) {
        return { .status = BatchParseStatus::INVALID_BATCH, .batchReason = BatchDiagnosticReason::EMPTY_COMMANDS };
    }
    return ParseBatchCommands(commands, strings);
}

bool UiSessionBatchCommand::Dispatch(const std::string& command, const BatchDispatchCallbacks& callbacks)
{
    auto result = Parse(command);
    if (result.status == BatchParseStatus::NOT_BATCH) {
        return false;
    }
    if (result.status == BatchParseStatus::INVALID_BATCH) {
        EmitBatchDiagnostic(callbacks, result.batchReason, result.commandCount, command.size());
        return true;
    }
    if (callbacks.itemDiagnosticSink) {
        for (const auto& diagnostic : result.diagnostics) {
            callbacks.itemDiagnosticSink(diagnostic);
        }
    }
    if (!callbacks.postTask) {
        EmitBatchDiagnostic(
            callbacks, BatchDiagnosticReason::TASK_EXECUTOR_UNAVAILABLE, result.commandCount, command.size());
        return true;
    }
    auto context = std::make_shared<BatchDispatchContext>();
    context->items = std::deque<BatchCommandItem>(
        std::make_move_iterator(result.items.begin()), std::make_move_iterator(result.items.end()));
    context->resolveTarget = callbacks.resolveTarget;
    context->diagnosticSink = callbacks.itemDiagnosticSink;
    if (!callbacks.postTask([context]() { ProcessBatch(context); })) {
        EmitBatchDiagnostic(callbacks, BatchDiagnosticReason::POST_TASK_FAILED, result.commandCount, command.size());
    }
    return true;
}

const char* UiSessionBatchCommand::GetReasonName(BatchDiagnosticReason reason)
{
    switch (reason) {
        case BatchDiagnosticReason::NONE:
            return "none";
        case BatchDiagnosticReason::INVALID_BATCH_ENVELOPE:
            return "invalid_batch_envelope";
        case BatchDiagnosticReason::EMPTY_COMMANDS:
            return "empty_commands";
        case BatchDiagnosticReason::TOO_MANY_COMMANDS:
            return "too_many_commands";
        case BatchDiagnosticReason::INVALID_NODE_ID:
            return "invalid_node_id";
        case BatchDiagnosticReason::DUPLICATE_NODE_ID:
            return "duplicate_node_id";
        case BatchDiagnosticReason::NODE_NOT_FOUND:
            return "node_not_found";
        case BatchDiagnosticReason::UNSUPPORTED_NODE_TYPE:
            return "unsupported_node_type";
        case BatchDiagnosticReason::UNSUPPORTED_CMD:
            return "unsupported_cmd";
        case BatchDiagnosticReason::INVALID_PARAMS:
            return "invalid_params";
        case BatchDiagnosticReason::VALUE_TOO_LONG:
            return "value_too_long";
        case BatchDiagnosticReason::COMMAND_EXECUTION_FAILED:
            return "command_execution_failed";
        case BatchDiagnosticReason::TASK_EXECUTOR_UNAVAILABLE:
            return "task_executor_unavailable";
        case BatchDiagnosticReason::POST_TASK_FAILED:
            return "post_task_failed";
        default:
            return "unknown";
    }
}

const char* UiSessionBatchCommand::GetSummaryName(BatchCommandSummary summary)
{
    switch (summary) {
        case BatchCommandSummary::SET_TEXT:
            return "setText";
        case BatchCommandSummary::UNSUPPORTED:
            return "unsupported";
        case BatchCommandSummary::MISSING_OR_NON_STRING:
            return "missing_or_non_string";
        case BatchCommandSummary::INVALID_OBJECT:
            return "invalid_object";
        default:
            return "invalid_object";
    }
}

} // namespace OHOS::Ace
