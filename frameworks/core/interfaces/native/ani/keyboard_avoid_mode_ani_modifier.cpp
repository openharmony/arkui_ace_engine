/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#include <memory>
#include "core/common/container.h"
#include "keyboard_avoid_mode_ani_modifier.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "frameworks/core/interfaces/ani/ani_api.h"
#include "frameworks/core/components/common/layout/constants.h"
#include "interfaces/inner_api/drawable_descriptor/base/log.h"

namespace OHOS::Ace::NG {
const std::vector<KeyBoardAvoidMode> KEYBOARD_AVOID_MODES = { KeyBoardAvoidMode::OFFSET, KeyBoardAvoidMode::RESIZE,
    KeyBoardAvoidMode::OFFSET_WITH_CARET, KeyBoardAvoidMode::RESIZE_WITH_CARET, KeyBoardAvoidMode::NONE };

void SetKeyboardAvoidMode(int32_t index)
{
    auto pipeline = PipelineBase::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    if (index < 0 || index >= static_cast<int32_t>(KEYBOARD_AVOID_MODES.size())) {
        HILOGE("Invalid Type, setKeyboardAvoid failed");
        return;
    }
    pipeline->SetEnableKeyBoardAvoidMode(KEYBOARD_AVOID_MODES[index]);
}

ArkUI_Int32 GetKeyboardAvoidMode()
{
    auto pipeline = PipelineBase::GetCurrentContextSafelyWithCheck();
    ArkUI_Int32 index = 0;
    CHECK_NULL_RETURN(pipeline, index);
    auto keyboardAvoidMode = pipeline->GetEnableKeyBoardAvoidMode();
    index = static_cast<ArkUI_Int32>(keyboardAvoidMode);
    return index;
}

const ArkUIAniKeyboardAvoidModeModifier* GetKeyboardAvoidModeAniModifier()
{
    static const ArkUIAniKeyboardAvoidModeModifier impl = {
        .getKeyboardAvoidMode = OHOS::Ace::NG::GetKeyboardAvoidMode,
        .setKeyboardAvoidMode = OHOS::Ace::NG::SetKeyboardAvoidMode
    };
    return &impl;
}
} // namespace OHOS::Ace::NG