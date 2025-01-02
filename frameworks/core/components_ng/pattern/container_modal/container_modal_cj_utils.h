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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_MODAL_CONTAINER_MODAL_CJ_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_MODAL_CONTAINER_MODAL_CJ_UTILS_H

#include "base/utils/macros.h"
#include "base/resource/internal_resource.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/container_modal/enhance/container_modal_pattern_enhance.h"
#include "core/components_ng/pattern/container_modal/container_modal_pattern.h"

namespace OHOS::Ace::NG {
    RefPtr<FrameNode> BuildControlButtonForCj(InternalResource::ResourceId icon, GestureEventFunc&& clickCallback,
        bool isCloseButton = false, bool canDrag = false);
    RefPtr<FrameNode> AddControlButtonsForCj(
        WeakPtr<ContainerModalPatternEnhance>& weakPattern, RefPtr<FrameNode>& containerTitleRow);  
    RefPtr<FrameNode> BuildTitleNodeForCj();
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_MODAL_CONTAINER_MODAL_CJ_UTILS_H
