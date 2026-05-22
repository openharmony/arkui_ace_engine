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

#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_UTILITY_PREVIEW_PLACEHOLDER_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_UTILITY_PREVIEW_PLACEHOLDER_H

#include <string>

#include "base/memory/referenced.h"
#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {
#if defined(PREVIEW)
RefPtr<FrameNode> CreatePreviewPlaceholder(const std::string& tag, int32_t nodeId);
#endif
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_UTILITY_PREVIEW_PLACEHOLDER_H
