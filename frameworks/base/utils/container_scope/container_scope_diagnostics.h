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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_UTILS_CONTAINER_SCOPE_CONTAINER_SCOPE_DIAGNOSTICS_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_UTILS_CONTAINER_SCOPE_CONTAINER_SCOPE_DIAGNOSTICS_H

#include <cstdint>
#include <string>

namespace OHOS::Ace {

// Bitmask flags describing anomalies detected during PushCurrent/PopCurrent operations.
// Multiple anomalies can be combined via bitwise OR.
enum class FrameAnomaly : uint32_t {
    NONE = 0,
    UNPAIRED_PUSH = 1 << 0,    // Push without a corresponding Pop (e.g., Container::PushCurrent init)
    STACK_UNDERFLOW = 1 << 1,  // Pop called with uid not found in active stack
    VALUE_MISMATCH = 1 << 2,   // Pop restoreId differs from the oldValue saved at Push time
    OUT_OF_ORDER_POP = 1 << 3, // Pop uid is not the top of the active stack (nested scope violated)
};

// Bitwise operators for combining and testing FrameAnomaly flags.
inline FrameAnomaly operator|(FrameAnomaly a, FrameAnomaly b)
{
    return static_cast<FrameAnomaly>(static_cast<uint32_t>(a) | static_cast<uint32_t>(b));
}

inline uint32_t operator&(FrameAnomaly a, FrameAnomaly b)
{
    return static_cast<uint32_t>(a) & static_cast<uint32_t>(b);
}

inline FrameAnomaly& operator|=(FrameAnomaly& a, FrameAnomaly b)
{
    a = a | b;
    return a;
}

inline FrameAnomaly& operator&=(FrameAnomaly& a, FrameAnomaly b)
{
    a = static_cast<FrameAnomaly>(static_cast<uint32_t>(a) & static_cast<uint32_t>(b));
    return a;
}

inline FrameAnomaly operator~(FrameAnomaly a)
{
    return static_cast<FrameAnomaly>(~static_cast<uint32_t>(a));
}

// Detailed classification of anomaly causes, used to distinguish different root causes
// within the same FrameAnomaly category.
enum class AnomalyDetailKind : uint8_t {
    NONE = 0,
    CONTAINER_INIT_NO_POP,    // Container init via Container::PushCurrent, no matching Pop expected
    POP_UID_NO_MATCHING_PUSH, // Pop uid has no matching Push record in active stack
    POP_VALUE_MISMATCH,       // Pop restoreId differs from the oldValue saved during Push
    OUT_OF_ORDER_POP_DYNAMIC, // Pop uid is not the current stack top; intermediate frames were skipped
};

// Converts AnomalyDetailKind to a human-readable string for logging.
inline const char* AnomalyDetailKindToStr(AnomalyDetailKind kind)
{
    switch (kind) {
        case AnomalyDetailKind::CONTAINER_INIT_NO_POP:
            return "Container init, no POP expected";
        case AnomalyDetailKind::POP_UID_NO_MATCHING_PUSH:
            return "POP uid has no matching PUSH";
        case AnomalyDetailKind::POP_VALUE_MISMATCH:
            return "POP restore value differs from PUSH saved value";
        default:
            return "";
    }
}

// Represents a single Push/Pop cycle in the currentId_ stack.
// Records the full context of a PushCurrent operation and its corresponding PopCurrent,
// including timing, source location, value transitions, and any detected anomalies.
struct CurrentIdStackFrame {
    // Maximum number of skipped UIDs recorded during an out-of-order Pop.
    static constexpr size_t MAX_SKIPPED_UIDS = 4;

    uint64_t uid = 0;       // Unique identifier for this Push/Pop pair, assigned by PushCurrent
    uint64_t parentUid = 0; // UID of the enclosing stack frame (0 if root level)
    const char* pushFileId = nullptr; // Source file where PushCurrent was called
    int32_t pushLine = 0;                            // Source line number where PushCurrent was called
    int32_t oldValue = 0;                            // The currentId_ value before this Push (will be restored on Pop)
    int32_t newValue = 0;                            // The new currentId_ value set by this Push
    const char* popFileId = nullptr;  // Source file where PopCurrent was called
    int32_t popLine = 0;                             // Source line number where PopCurrent was called
    int32_t sourceType = 0;                          // Caller type, see CurrentIdSourceType enum
    FrameAnomaly anomalies = FrameAnomaly::NONE;     // Bitmask of detected anomalies
    AnomalyDetailKind anomalyDetailKind = AnomalyDetailKind::NONE; // Most recent anomaly detail
    uint32_t skippedCount = 0;                                     // Number of frames skipped during out-of-order Pop
    uint64_t skippedUids[MAX_SKIPPED_UIDS] = {}; // UIDs of the skipped frames (up to MAX_SKIPPED_UIDS)
    uint64_t expectedTopUid = 0;                 // The UID that was expected to be on top during out-of-order Pop

    // Returns a human-readable string representation of this frame for diagnostic output.
    std::string ToString() const;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_UTILS_CONTAINER_SCOPE_CONTAINER_SCOPE_DIAGNOSTICS_H
