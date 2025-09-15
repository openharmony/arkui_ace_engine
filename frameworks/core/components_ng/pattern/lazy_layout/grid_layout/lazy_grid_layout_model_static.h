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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LAZY_LAYOUT_LAZY_GRID_LAYOUT_MODEL_STATIC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LAZY_LAYOUT_LAZY_GRID_LAYOUT_MODEL_STATIC_H

#include <functional>
#include <memory>

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT LazyGridLayoutModelStatic {
public:
    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static void SetRowGap(FrameNode* frameNode, const std::optional<Dimension>& space);
    static void SetColumnGap(FrameNode* frameNode, const std::optional<Dimension>& space);
};

class ACE_EXPORT LazyVGridLayoutModelStatic : public LazyGridLayoutModelStatic {
public:
    static void SetColumnsTemplate(FrameNode* frameNode, const std::string& value);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LAZY_LAYOUT_LAZY_GRID_LAYOUT_MODEL_STATIC_H
