/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BUTTON_TOGGLE_BUTTON_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BUTTON_TOGGLE_BUTTON_MODEL_H

#include <string>

#include "base/utils/macros.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT ToggleButtonModelNG {
public:
    static void Create(const std::string& tagName);
    static void SetSelectedColor(const Color& selectedColor);
    static void ResetSelectedColor();
    static void SetBackgroundColor(const Color& backgroundColor, bool flag);
    static void SetIsOn(bool isOn);
    static void SetSelectedColor(FrameNode* frameNode, const Color& selectedColor);
    static void ResetSelectedColor(FrameNode* frameNode);
    static void SetBackgroundColor(FrameNode* frameNode, const Color& backgroundColor);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BUTTON_TOGGLE_BUTTON_MODEL_H