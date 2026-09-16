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

#ifndef FOUNDATION_ARKUI_ACE_ENGINE_ADAPTER_OHOS_ENTRANCE_UI_SESSION_UI_SESSION_BATCH_COMMAND_H
#define FOUNDATION_ARKUI_ACE_ENGINE_ADAPTER_OHOS_ENTRANCE_UI_SESSION_UI_SESSION_BATCH_COMMAND_H

#include <cstddef>
#include <cstdint>
#include <functional>
#include <string>
#include <vector>

namespace OHOS::Ace {

enum class BatchParseStatus {
    NOT_BATCH = 0,
    INVALID_BATCH,
    VALID_BATCH,
};

enum class BatchDiagnosticReason {
    NONE = 0,
    INVALID_BATCH_ENVELOPE,
    EMPTY_COMMANDS,
    TOO_MANY_COMMANDS,
    INVALID_NODE_ID,
    DUPLICATE_NODE_ID,
    NODE_NOT_FOUND,
    UNSUPPORTED_NODE_TYPE,
    UNSUPPORTED_CMD,
    INVALID_PARAMS,
    VALUE_TOO_LONG,
    COMMAND_EXECUTION_FAILED,
    TASK_EXECUTOR_UNAVAILABLE,
    POST_TASK_FAILED,
};

enum class BatchCommandSummary {
    SET_TEXT = 0,
    UNSUPPORTED,
    MISSING_OR_NON_STRING,
    INVALID_OBJECT,
};

struct BatchDiagnostic {
    bool hasNodeId = false;
    int32_t nodeId = -1;
    size_t ordinal = 0;
    size_t keyLength = 0;
    BatchDiagnosticReason reason = BatchDiagnosticReason::NONE;
    BatchCommandSummary commandSummary = BatchCommandSummary::INVALID_OBJECT;
    int32_t valueLength = -1;
};

struct BatchCommandItem {
    int32_t nodeId = -1;
    size_t ordinal = 0;
    BatchDiagnosticReason semanticError = BatchDiagnosticReason::NONE;
    BatchCommandSummary commandSummary = BatchCommandSummary::INVALID_OBJECT;
    int32_t valueLength = -1;
    std::string canonicalCommand;
};

struct BatchParseResult {
    BatchParseStatus status = BatchParseStatus::NOT_BATCH;
    BatchDiagnosticReason batchReason = BatchDiagnosticReason::NONE;
    size_t commandCount = 0;
    std::vector<BatchCommandItem> items;
    std::vector<BatchDiagnostic> diagnostics;
};

enum class BatchTargetStatus {
    READY,
    NOT_FOUND,
    UNSUPPORTED_TYPE,
};

struct BatchResolvedTarget {
    BatchTargetStatus status = BatchTargetStatus::NOT_FOUND;
    std::function<bool(const std::string&)> execute;
};

struct BatchLevelDiagnostic {
    BatchDiagnosticReason reason = BatchDiagnosticReason::NONE;
    size_t commandCount = 0;
    size_t commandLength = 0;
};

struct BatchDispatchCallbacks {
    std::function<bool(std::function<void()>&&)> postTask;
    std::function<BatchResolvedTarget(int32_t)> resolveTarget;
    std::function<void(const BatchDiagnostic&)> itemDiagnosticSink;
    std::function<void(const BatchLevelDiagnostic&)> batchDiagnosticSink;
};

class UiSessionBatchCommand final {
public:
    static BatchParseResult Parse(const std::string& command);
    static bool Dispatch(const std::string& command, const BatchDispatchCallbacks& callbacks);
    static const char* GetReasonName(BatchDiagnosticReason reason);
    static const char* GetSummaryName(BatchCommandSummary summary);
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ARKUI_ACE_ENGINE_ADAPTER_OHOS_ENTRANCE_UI_SESSION_UI_SESSION_BATCH_COMMAND_H
