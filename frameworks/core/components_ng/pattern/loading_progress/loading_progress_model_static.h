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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LOADING_PROGRESS_LOADING_PROGRESS_MODEL_STATIC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LOADING_PROGRESS_LOADING_PROGRESS_MODEL_STATIC_H

#include "core/components_ng/base/common_configuration.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/loading_progress/loading_progress_model.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT LoadingProgressModelStatic {
public:
    static void SetColor(FrameNode* frameNode, const std::optional<Color>& valueOpt);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LOADING_PROGRESS_LOADING_PROGRESS_MODEL_STATIC_H
