/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_FOCUS_FOCUS_VIEW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_FOCUS_FOCUS_VIEW_H

#include <list>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components_ng/event/focus_hub.h"

namespace OHOS::Ace::NG {

const char ENTRY_ANY_FOCUSVIEW[] = "entry_any_view";

class FocusView : public virtual AceType {
    DECLARE_ACE_TYPE(FocusView, AceType);

public:
    FocusView() = default;
    ~FocusView() override = default;

    virtual std::list<int32_t> GetRouteOfFirstScope() = 0;
    virtual bool IsEntryFocusView()
    {
        return true;
    }
    virtual bool IsFocusViewLegal()
    {
        return true;
    }

    RefPtr<FrameNode> GetFrameNode();
    std::string GetFrameName();
    int32_t GetFrameId();

    void FocusViewShow(bool isTriggerByStep = false);
    void FocusViewHide();
    void FocusViewClose(bool isDetachFromTree = false);

    virtual void LostViewFocus();

    RefPtr<FocusHub> GetFocusHub();

    static RefPtr<FocusView> GetCurrentFocusView();
    RefPtr<FocusView> GetEntryFocusView();
    RefPtr<FocusHub> GetViewRootScope();
    bool IsViewRootScopeHasLastFocus();
    bool IsRootScopeCurrentFocus();
    bool IsChildFocusViewOf(const RefPtr<FocusView>& parent);
    bool HasParentFocusHub();

    bool RequestDefaultFocus();
    bool TriggerFocusMove();

    void SetIsViewRootScopeFocused(bool isViewRootScopeFocused);
    bool GetIsViewRootScopeFocused() const
    {
        return isViewRootScopeFocused_;
    }

    void SetIsViewHasFocused(bool isViewHasFocused)
    {
        isViewHasFocused_ = isViewHasFocused;
    }
    bool GetIsViewHasFocused() const
    {
        return isViewHasFocused_;
    }

    void SetViewRootScope(const RefPtr<FocusHub>& viewRootScope)
    {
        if (!viewRootScope) {
            rootScopeSpecified_ = nullptr;
            return;
        }
        rootScopeSpecified_ = AceType::WeakClaim(AceType::RawPtr(viewRootScope));
    }

    void SetIsViewHasShow(bool isViewHasShow)
    {
        isViewHasShow_ = isViewHasShow;
    }

    bool GetIsViewHasShow() const
    {
        return isViewHasShow_;
    }

    std::pair<bool, bool> HandleDefaultFocusNode(
        const RefPtr<FocusHub>& defaultFocusNode, bool isViewRootScopeHasChildFocused);

    void FocusViewDidShow(const RefPtr<FocusHub>& focusHub);

private:
    bool neverShown_ = true;
    bool isViewRootScopeFocused_ = true;
    bool isViewHasFocused_ = false;
    bool isViewHasShow_ = false;

    WeakPtr<FocusHub> rootScopeSpecified_;
    bool GetFocusViewFocusable();

    ACE_DISALLOW_COPY_AND_MOVE(FocusView);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_FOCUS_FOCUS_VIEW_H
