/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 */

#include <algorithm>

#include "core/components_ng/manager/safe_area/safe_area_manager.h"

namespace OHOS::Ace::NG {
namespace {
bool NeedSkipCutoutUpdate(const SafeAreaInsets& safeArea)
{
    const bool allStartsZero = safeArea.left_.start == 0 && safeArea.top_.start == 0 && safeArea.right_.start == 0 &&
                               safeArea.bottom_.start == 0;
    const bool hasNonZeroEnd =
        safeArea.left_.end != 0 || safeArea.top_.end != 0 || safeArea.right_.end != 0 || safeArea.bottom_.end != 0;
    return allStartsZero && hasNonZeroEnd;
}
} // namespace

SafeAreaInsets SafeAreaManager::GetSystemSafeArea() const
{
    return systemSafeArea_;
}

SafeAreaInsets SafeAreaManager::GetSafeArea() const
{
    if (ignoreSafeArea_ || (!isFullScreen_ && !isNeedAvoidWindow_)) {
        return {};
    }
    auto safeArea = systemSafeArea_;
    safeArea = safeArea.Combine(cutoutSafeArea_);
    safeArea = safeArea.Combine(navSafeArea_);
    if (keyboardSafeAreaEnabled_) {
        safeArea = safeArea.Combine(SafeAreaInsets({}, {}, {}, keyboardInset_));
    }
    return safeArea;
}

SafeAreaInsets SafeAreaManager::GetSafeAreaWithoutProcess() const
{
    auto safeArea = systemSafeArea_;
    safeArea = safeArea.Combine(cutoutSafeArea_);
    safeArea = safeArea.Combine(navSafeArea_);
    if (keyboardSafeAreaEnabled_) {
        safeArea = safeArea.Combine(SafeAreaInsets({}, {}, {}, keyboardInset_));
    }
    return safeArea;
}

float SafeAreaManager::GetKeyboardOffset(bool withoutProcess) const
{
    if (keyboardInset_.Length() <= 1 && keyboardOffset_ > -1.1f && keyboardOffset_ < -0.9f) {
        const_cast<SafeAreaManager*>(this)->keyboardOffset_ = 0.0f;
        return 0.0f;
    }
    if (withoutProcess) {
        return keyboardOffset_;
    }
    if (keyboardAvoidMode_ == KeyBoardAvoidMode::RESIZE ||
        keyboardAvoidMode_ == KeyBoardAvoidMode::RESIZE_WITH_CARET ||
        keyboardAvoidMode_ == KeyBoardAvoidMode::NONE) {
        return 0.0f;
    }
    return keyboardOffset_;
}

bool SafeAreaManager::UpdateKeyboardSafeArea(float keyboardHeight, std::optional<uint32_t> rootHeight)
{
    auto keyboard = static_cast<uint32_t>(std::max(0.0f, keyboardHeight));
    auto bottom = rootHeight.value_or(keyboard);
    if (bottom < keyboard) {
        bottom = keyboard;
    }
    SafeAreaInsets::Inset inset { .start = bottom - keyboard, .end = bottom };
    if (inset == keyboardInset_) {
        return false;
    }
    keyboardInset_ = inset;
    return true;
}

bool SafeAreaManager::UpdateSystemSafeArea(const SafeAreaInsets& safeArea)
{
    if (systemSafeArea_ == safeArea) {
        return false;
    }
    systemSafeArea_ = safeArea;
    return true;
}

bool SafeAreaManager::UpdateNavSafeArea(const SafeAreaInsets& safeArea)
{
    if (navSafeArea_ == safeArea) {
        return false;
    }
    navSafeArea_ = safeArea;
    return true;
}

bool SafeAreaManager::UpdateCutoutSafeArea(
    const SafeAreaInsets& safeArea, OptionalSize<uint32_t> rootWidth)
{
    (void)rootWidth;
    if (NeedSkipCutoutUpdate(safeArea)) {
        return false;
    }
    if (cutoutSafeArea_ == safeArea) {
        return false;
    }
    cutoutSafeArea_ = safeArea;
    return true;
}

bool SafeAreaManager::UpdateScbSystemSafeArea(const SafeAreaInsets& safeArea)
{
    if (scbSystemSafeArea_.has_value() && scbSystemSafeArea_.value() == safeArea) {
        return false;
    }
    scbSystemSafeArea_ = safeArea;
    return true;
}

bool SafeAreaManager::UpdateScbCutoutSafeArea(const SafeAreaInsets& safeArea, OptionalSize<uint32_t> rootWidth)
{
    (void)rootWidth;
    if (NeedSkipCutoutUpdate(safeArea)) {
        return false;
    }
    if (scbCutoutSafeArea_.has_value() && scbCutoutSafeArea_.value() == safeArea) {
        return false;
    }
    scbCutoutSafeArea_ = safeArea;
    return true;
}

bool SafeAreaManager::UpdateScbNavSafeArea(const SafeAreaInsets& safeArea)
{
    if (scbNavSafeArea_.has_value() && scbNavSafeArea_.value() == safeArea) {
        return false;
    }
    scbNavSafeArea_ = safeArea;
    return true;
}

bool SafeAreaManager::SetIsFullScreen(bool value)
{
    if (isFullScreen_ == value) {
        return false;
    }
    isFullScreen_ = value;
    return true;
}

bool SafeAreaManager::SetIsNeedAvoidWindow(bool value)
{
    if (isNeedAvoidWindow_ == value) {
        return false;
    }
    isNeedAvoidWindow_ = value;
    return true;
}

bool SafeAreaManager::SetIgnoreSafeArea(bool value)
{
    if (ignoreSafeArea_ == value) {
        return false;
    }
    ignoreSafeArea_ = value;
    return true;
}

bool SafeAreaManager::SetKeyBoardAvoidMode(KeyBoardAvoidMode value)
{
    if (keyboardAvoidMode_ == value) {
        return false;
    }
    if (keyboardAvoidMode_ == KeyBoardAvoidMode::NONE || value == KeyBoardAvoidMode::NONE) {
        keyboardOffset_ = 0.0f;
    }
    keyboardAvoidMode_ = value;
    keyboardSafeAreaEnabled_ =
        (value == KeyBoardAvoidMode::RESIZE || value == KeyBoardAvoidMode::RESIZE_WITH_CARET);
    return true;
}

KeyBoardAvoidMode SafeAreaManager::GetKeyBoardAvoidMode()
{
    return keyboardAvoidMode_;
}
} // namespace OHOS::Ace::NG
