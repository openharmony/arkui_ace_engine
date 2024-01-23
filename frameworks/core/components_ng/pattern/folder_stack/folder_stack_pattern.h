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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_FOLDER_STACK_FOLDER_STACK_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_FOLDER_STACK_FOLDER_STACK_PATTERN_H

#include "base/thread/cancelable_callback.h"
#include "core/common/display_info.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/folder_stack/folder_stack_event_hub.h"
#include "core/components_ng/pattern/folder_stack/folder_stack_layout_algorithm.h"
#include "core/components_ng/pattern/folder_stack/folder_stack_layout_property.h"
#include "core/components_ng/pattern/stack/stack_layout_algorithm.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT FolderStackPattern : public StackPattern {
    DECLARE_ACE_TYPE(FolderStackPattern, Pattern);

public:
    FolderStackPattern() = default;
    ~FolderStackPattern() override = default;

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<FolderStackLayoutAlgorithm>();
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<FolderStackLayoutProperty>();
    }

    bool IsAtomicNode() const override
    {
        return false;
    }

    RefPtr<PaintProperty> CreatePaintProperty() override
    {
        return MakeRefPtr<PaintProperty>();
    }

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::SCOPE, true };
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<FolderStackEventHub>();
    }

    void BeforeCreateLayoutWrapper() override;

    void RefreshStack(FoldStatus foldStatus);

    void OnFolderStateChangeSend(FoldStatus foldStatus);

    void UpdateFoldStatusChangedCallbackId(std::optional<int32_t> id)
    {
        foldStatusChangedCallbackId_ = id;
    }

    bool HasFoldStatusChangedCallbackId()
    {
        return foldStatusChangedCallbackId_.has_value();
    }

    RefPtr<DisplayInfo> GetDisplayInfo()
    {
        return displayInfo_;
    }

    void DumpInfo() override;

    bool GetNeedCallBack()
    {
        return needCallBack_;
    }

    void SetNeedCallBack(bool needCallBack)
    {
        needCallBack_ = needCallBack;
    }

private:
    void OnDetachFromFrameNode(FrameNode* node) override;
    void RegisterFoldStatusListener();
    void OnAttachToFrameNode() override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, bool skipMeasure, bool skipLayout) override;
    void StartOffsetEnteringAnimation();
    RefPtr<RenderContext> GetRenderContext();
    void OnVisibleChange(bool isVisible) override;
    void OnModifyDone() override;
    void InitFolderStackPatternAppearCallback();
    void RestoreScreenState();
    void SetAutoRotate();
    void UpdateChildAlignment();
    std::optional<int32_t> foldStatusChangedCallbackId_;
    bool isScreenRotationLocked_ = false;
    Orientation lastOrientation_ = Orientation::UNSPECIFIED;
    bool isNeedRestoreScreenState_ = false;
    bool isAppearCallback_ = false;
    RefPtr<DisplayInfo> displayInfo_;
    bool hasInHoverMode_ = false;
    bool needCallBack_ = false;
    FoldStatus currentFoldStatus_ = FoldStatus::UNKNOWN;
    CancelableCallback<void()> foldStatusDelayTask_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_FOLDER_STACK_FOLDER_STACK_PATTERN_H
