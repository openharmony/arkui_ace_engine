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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_STARTING_WINDOW_LAYOUT_HELPER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_STARTING_WINDOW_LAYOUT_HELPER_H

#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/frame_node.h"

#include "interfaces/include/ws_common.h"
#include "session/host/include/session.h"

namespace OHOS::Ace::NG {
struct LayoutParams {
    Dimension iconSize { 128.0_vp };
};

class StartingWindowLayoutHelper : public AceType {
    DECLARE_ACE_TYPE(StartingWindowLayoutHelper, AceType);

public:
    StartingWindowLayoutHelper() = default;
    ~StartingWindowLayoutHelper() = default;

    RefPtr<FrameNode> CreateStartingWindowNode(const Rosen::StartingWindowInfo& startingWindowInfo,
        const std::string& bundleName, const std::string& moduleName);
    void MeasureChildNode(const SizeF& parentSize);

private:
    void MeasureUpperAreaNode(
        const SizeF& parentSize, const RefPtr<FrameNode> upperAreaNode, bool needHideBrand);
    Rosen::StartingWindowInfo startingWindowInfo_;
    WeakPtr<FrameNode> upperAreaNode_;
    WeakPtr<FrameNode> brandNode_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_STARTING_WINDOW_LAYOUT_HELPER_H
