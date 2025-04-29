/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_KEYBOARD_BASE_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_KEYBOARD_BASE_PATTERN_H

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT KeyboardPattern : public LinearLayoutPattern {
    DECLARE_ACE_TYPE(KeyboardPattern, LinearLayoutPattern);

public:
    KeyboardPattern(int32_t targetId) : LinearLayoutPattern(true)
    {
        targetId_ = targetId;
    }

    ~KeyboardPattern() override = default;

    void BeforeCreateLayoutWrapper() override;

    bool CheckChildPosition(const RefPtr<FrameNode>& frameNode);

    int32_t GetTargetId()
    {
        return targetId_;
    }
    void DumpInfo() override;
    void DumpSimplifyInfo(std::unique_ptr<JsonValue>& json) override {}
    void DumpInfo(std::unique_ptr<JsonValue>& json) override;
    void OnModifyDone() override;
    void OnAreaChangedInner() override;
    void SetKeyboardAreaChange(bool keyboardAvoidance = false);
    void OnDetachFromFrameNode(FrameNode* node) override;

    void SetKeyboardOption(bool keyboardAvoidance)
    {
        supportAvoidance_ = keyboardAvoidance;
    }

    void SetKeyboardSafeHeight(const float safeHeight)
    {
        safeHeight_ = safeHeight;
    }

    float GetKeyboardHeight();

private:
    int32_t targetId_ = -1;
    float keyboardHeight_ = 0.0f;
    bool supportAvoidance_ = false;
    float safeHeight_ = 0.0f;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_KEYBOARD_BASE_PATTERN_H
