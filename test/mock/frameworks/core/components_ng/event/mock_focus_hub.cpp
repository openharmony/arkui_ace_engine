/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 */

#include "core/components_ng/event/focus_hub.h"

namespace OHOS::Ace::NG {
std::string FocusState::GetFrameName() const
{
    return {};
}

int32_t FocusState::GetFrameId() const
{
    return 0;
}

RefPtr<FrameNode> FocusState::GetFrameNode() const
{
    return nullptr;
}

bool FocusHub::RequestFocusImmediatelyById(const std::string& inspectorId, bool isSyncRequest)
{
    (void)inspectorId;
    (void)isSyncRequest;
    return false;
}

bool FocusHub::HandleFocusTravel(const FocusEvent& event)
{
    (void)event;
    return false;
}

bool FocusHub::IsEnabled() const
{
    return true;
}

bool FocusHub::IsShow() const
{
    return true;
}

bool FocusHub::IsFocusableNode()
{
    return false;
}

bool FocusHub::TriggerFocusScroll()
{
    return false;
}

bool FocusHub::RequestFocusImmediately(FocusReason reason)
{
    (void)reason;
    return false;
}

WeakPtr<FocusHub> FocusHub::GetUnfocusableParentFocusNode()
{
    return {};
}

void FocusHub::SetFocusable(bool focusable, bool isExplicit)
{
    (void)isExplicit;
    focusable_ = focusable;
}

RefPtr<FocusManager> FocusHub::GetFocusManager() const
{
    return nullptr;
}

void FocusHub::RemoveSelf(BlurReason reason)
{
    (void)reason;
}

void FocusHub::DumpFocusTree(int32_t depth, bool hasJson)
{
    (void)depth;
    (void)hasJson;
}

void FocusHub::LostFocus(BlurReason reason)
{
    (void)reason;
}
} // namespace OHOS::Ace::NG
