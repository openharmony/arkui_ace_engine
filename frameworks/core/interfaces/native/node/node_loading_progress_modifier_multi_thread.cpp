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

#include "node_loading_progress_modifier.h"

#include "core/common/resource/resource_parse_utils.h"
#include "core/components/progress/progress_theme.h"
#include "core/components_ng/pattern/loading_progress/loading_progress_model_ng.h"
#include "core/interfaces/native/node/node_loading_progress_modifier_multi_thread.h"

namespace OHOS::Ace::NG {
void ResetLoadingProgressColorMultiThread(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
        auto pipelineContext = frameNode->GetContext();
        CHECK_NULL_VOID(pipelineContext);
        auto theme = pipelineContext->GetTheme<ProgressTheme>();
        CHECK_NULL_VOID(theme);
        LoadingProgressModelNG::SetColorParseFailed(frameNode, true);
        LoadingProgressModelNG::SetColor(frameNode, theme->GetLoadingParseFailedColor());
    }
    if (SystemProperties::ConfigChangePerform()) {
        LoadingProgressModelNG::SetColorByUser(frameNode, false);
        LoadingProgressModelNG::CreateWithResourceObj(frameNode, LoadingProgressResourceType::COLOR, nullptr);
    }
}
} // namespace OHOS::Ace::NG