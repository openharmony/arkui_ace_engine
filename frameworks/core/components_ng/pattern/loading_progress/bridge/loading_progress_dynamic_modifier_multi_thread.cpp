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

#include "loading_progress_dynamic_modifier_multi_thread.h"

#include "core/common/resource/resource_parse_utils.h"
#include "core/components/progress/progress_theme.h"
#include "core/components_ng/pattern/loading_progress/loading_progress_model_ng.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
void ResetLoadingProgressColorMultiThread(ArkUINodeHandle node, bool isJsView)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN) && isJsView) {
        if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWENTY_SIX)) {
            LoadingProgressModelNG::ResetColor(frameNode);
            LoadingProgressModelNG::SetColorByUser(frameNode, false);
        } else {
            auto progressTheme = frameNode->GetTheme<ProgressTheme>();
            CHECK_NULL_VOID(progressTheme);
            Color progressColor = progressTheme->GetLoadingColor();
            LoadingProgressModelNG::SetColor(frameNode, progressColor);
            LoadingProgressModelNG::SetColorByUser(frameNode, false);
        }
    } else if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN) && !isJsView) {
        LoadingProgressModelNG::ResetColor(frameNode, isJsView);
    }
    if (SystemProperties::ConfigChangePerform()) {
        LoadingProgressModelNG::SetColorByUser(frameNode, false);
        LoadingProgressModelNG::CreateWithResourceObj(frameNode, LoadingProgressResourceType::COLOR, nullptr);
    }
}
} // namespace OHOS::Ace::NG