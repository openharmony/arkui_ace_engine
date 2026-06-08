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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_GESTURE_ACTIVE_RECOGNIZER_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_GESTURE_ACTIVE_RECOGNIZER_MANAGER_H

#include <map>
#include <list>
#include <string>
#include <unordered_set>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/gestures/recognizers/gesture_recognizer.h"

namespace OHOS::Ace::NG {

class ActiveRecognizerManager : public AceType {
    DECLARE_ACE_TYPE(ActiveRecognizerManager, AceType);

public:
    ActiveRecognizerManager() = default;
    ~ActiveRecognizerManager() override = default;

    struct RecognizerInfo {
        WeakPtr<NGGestureRecognizer> recognizer;
        TimeStamp lastUpdateTime;
        int32_t touchId = -1;
        std::string recognizerType;

        RecognizerInfo() = default;
        explicit RecognizerInfo(const WeakPtr<NGGestureRecognizer>& recognizer, int32_t id)
            : recognizer(recognizer), touchId(id)
        {
            auto strong = recognizer.Upgrade();
            if (strong) {
                recognizerType = AceType::TypeName(strong);
            }
        }
    };

    void RegisterRecognizer(const RefPtr<NGGestureRecognizer>& recognizer, int32_t touchId);

    void UpdateRecognizerState(const RefPtr<NGGestureRecognizer>& recognizer, RefereeState newState);

    void CheckAndCleanBeforeNewTouch(int32_t newTouchId);

    bool HasActiveRecognizers() const;

    size_t GetActiveRecognizerCount() const;

    void RemoveRecognizer(const RefPtr<NGGestureRecognizer>& recognizer);

    void ClearAllRecognizers();

    void DumpRecognizerStates() const;

private:
    bool CheckPendingTimeout(const RefPtr<NGGestureRecognizer>& recognizer, const RecognizerInfo& info);

    void SendCancelToRecognizer(const RefPtr<NGGestureRecognizer>& recognizer);

    std::map<WeakPtr<NGGestureRecognizer>, RecognizerInfo> activeRecognizers_;

    std::unordered_set<int32_t> activeTouchIds_;

    static constexpr int64_t DEFAULT_PENDING_TIMEOUT_MS = 300;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_GESTURE_ACTIVE_RECOGNIZER_MANAGER_H