/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 */

#include "core/components_ng/event/touch_event.h"
#include "core/components_ng/manager/focus/focus_view.h"

namespace OHOS::Ace::NG {
RefPtr<FrameNode> FocusView::GetFrameNode()
{
    return nullptr;
}

std::string FocusView::GetFrameName()
{
    return {};
}

int32_t FocusView::GetFrameId()
{
    return -1;
}

void FocusView::FocusViewShow(bool isTriggerByStep)
{
    (void)isTriggerByStep;
}

void FocusView::FocusViewHide() {}

void FocusView::FocusViewClose(bool isDetachFromTree)
{
    (void)isDetachFromTree;
}

void FocusView::LostViewFocus() {}

RefPtr<FocusHub> FocusView::GetFocusHub()
{
    return nullptr;
}

RefPtr<FocusView> FocusView::GetCurrentFocusView()
{
    return nullptr;
}

RefPtr<FocusView> FocusView::GetEntryFocusView()
{
    return nullptr;
}

RefPtr<FocusHub> FocusView::GetViewRootScope()
{
    return nullptr;
}

bool FocusView::IsViewRootScopeHasLastFocus()
{
    return false;
}

bool FocusView::IsRootScopeCurrentFocus()
{
    return false;
}

bool FocusView::IsChildFocusViewOf(const RefPtr<FocusView>& parent)
{
    (void)parent;
    return false;
}

bool FocusView::HasParentFocusHub()
{
    return false;
}

bool FocusView::RequestDefaultFocus()
{
    return false;
}

bool FocusView::TriggerFocusMove()
{
    return false;
}

void FocusView::SetIsViewRootScopeFocused(bool isViewRootScopeFocused)
{
    isViewRootScopeFocused_ = isViewRootScopeFocused;
}

std::pair<bool, bool> FocusView::HandleDefaultFocusNode(
    const RefPtr<FocusHub>& defaultFocusNode, bool isViewRootScopeHasChildFocused)
{
    (void)defaultFocusNode;
    (void)isViewRootScopeHasChildFocused;
    return { false, false };
}

void FocusView::FocusViewDidShow(const RefPtr<FocusHub>& focusHub)
{
    (void)focusHub;
}
} // namespace OHOS::Ace::NG
