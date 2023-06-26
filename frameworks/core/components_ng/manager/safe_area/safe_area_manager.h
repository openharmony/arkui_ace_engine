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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SAFE_AREA_SAFE_AREA_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SAFE_AREA_SAFE_AREA_MANAGER_H

#include "base/memory/ace_type.h"
#include "base/utils/noncopyable.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/property/safe_area_insets.h"

namespace OHOS::Ace::NG {
// SafeAreaManager stores layout information to apply SafeArea correctly.
class SafeAreaManager : public virtual AceType {
    DECLARE_ACE_TYPE(SafeAreaManager, AceType);

public:
    SafeAreaManager() = default;
    ~SafeAreaManager() override = default;

    bool UpdateSystemSafeArea(const SafeAreaInsets& safeArea);

    SafeAreaInsets GetSystemSafeArea() const
    {
        return systemSafeArea_;
    }

    bool UpdateCutoutSafeArea(const SafeAreaInsets& safeArea);

    SafeAreaInsets GetCutoutSafeArea() const
    {
        return cutoutSafeArea_;
    }

    void UpdateKeyboardOffset(float offset)
    {
        keyboardOffset_ = offset;
    }

    float GetKeyboardOffset() const
    {
        return keyboardOffset_;
    }

    SafeAreaInsets GetCombinedSafeArea(const SafeAreaExpandOpts& opts) const;

    // Add during Layout traversal
    void AddWrapper(const WeakPtr<LayoutWrapper>& wrapper)
    {
        wrappersToAdjust_.emplace_back(wrapper);
    }

    // Reset after ExpandSafeArea and AvoidKeyboard
    void ResetWrappers()
    {
        wrappersToAdjust_.clear();
    }

    const std::vector<WeakPtr<LayoutWrapper>>& GetWrappers() const
    {
        return wrappersToAdjust_;
    }

    const std::vector<WeakPtr<FrameNode>>& GetGeoRestoreNodes()
    {
        return geoRestoreNodes_;
    }

    void AddGeoRestoreNode(const WeakPtr<FrameNode>& node)
    {
        geoRestoreNodes_.emplace_back(node);
    }

    void SwapGeoRestoreNodes(std::vector<WeakPtr<FrameNode>>& nodes)
    {
        geoRestoreNodes_.swap(nodes);
    }

private:
    SafeAreaInsets systemSafeArea_;
    SafeAreaInsets cutoutSafeArea_;
    std::vector<WeakPtr<FrameNode>> geoRestoreNodes_;
    std::vector<WeakPtr<LayoutWrapper>> wrappersToAdjust_;
    float keyboardOffset_ = 0.0f;

    ACE_DISALLOW_COPY_AND_MOVE(SafeAreaManager);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SAFE_AREA_SAFE_AREA_MANAGER_H
