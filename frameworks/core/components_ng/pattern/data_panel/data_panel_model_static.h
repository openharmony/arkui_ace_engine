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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DATA_PANEL_MODEL_STATIC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DATA_PANEL_MODEL_STATIC_H

#include "core/components_ng/pattern/data_panel/data_panel_model.h"
#include "core/components_ng/base/common_configuration.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT DataPanelModelStatic {
public:
    static void SetValues(FrameNode* frameNode, const std::optional<std::vector<double>>& values);
    static void SetMax(FrameNode* frameNode, const std::optional<double>& max);
    static void SetType(FrameNode* frameNode, const std::optional<int32_t>& type);
    static void SetTrackBackground(FrameNode* frameNode, const std::optional<Color>& trackBackgroundColor);
    static void SetStrokeWidth(FrameNode* frameNode, const std::optional<Dimension>& strokeWidth);
    static void SetValueColors(FrameNode* frameNode, const std::optional<std::vector<Gradient>>& valueColors);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DATA_PANEL_MODEL_STATIC_H