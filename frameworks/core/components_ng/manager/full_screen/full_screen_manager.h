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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_FULL_SCREEN_FULL_SCREEN_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_FULL_SCREEN_FULL_SCREEN_MANAGER_H

#include <unordered_map>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/noncopyable.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/geometry_node.h"

namespace OHOS::Ace::NG {

// FullScreenManager is the base class to display full screen.
class ACE_EXPORT FullScreenManager : public virtual AceType {
    DECLARE_ACE_TYPE(FullScreenManager, AceType);

public:
    explicit FullScreenManager(const RefPtr<FrameNode>& rootNode) : rootNodeWeak_(rootNode) {}
    ~FullScreenManager() override = default;

    void RequestFullScreen(const RefPtr<FrameNode>& frameNode);
    void ExitFullScreen(const RefPtr<FrameNode>& frameNode);
    bool OnBackPressed();

private:
    WeakPtr<FrameNode> rootNodeWeak_;
    std::unordered_map<int32_t, std::pair<WeakPtr<UINode>, int32_t>> originalParent_;
    std::unordered_map<int32_t, RefPtr<GeometryNode>> originGeometryNode_;

    ACE_DISALLOW_COPY_AND_MOVE(FullScreenManager);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_FULL_SCREEN_FULL_SCREEN_MANAGER_H
