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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TOGGLE_TOGGLE_MODEL_STATIC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TOGGLE_TOGGLE_MODEL_STATIC_H

#include "core/components_ng/base/common_configuration.h"
#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#include "core/components_ng/pattern/toggle/toggle_model.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT ToggleModelStatic {
public:
    static void SetPointRadius(FrameNode* frameNode, const std::optional<Dimension>& switchPointRadius);
    static void SetUnselectedColor(FrameNode* frameNode, const std::optional<Color>& unselectedColor);
    static void SetTrackBorderRadius(FrameNode* frameNode, const std::optional<Dimension>& borderRadius);
    static void OnChangeEvent(FrameNode* frameNode, ChangeEvent&& onChangeEvent);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TOGGLE_TOGGLE_MODEL_STATIC_H
