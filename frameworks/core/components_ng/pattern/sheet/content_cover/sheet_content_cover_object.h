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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SHEET_CONTENT_COVER_SHEET_CONTENT_COVER_OBJECT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SHEET_CONTENT_COVER_SHEET_CONTENT_COVER_OBJECT_H

#include "core/components_ng/pattern/sheet/sheet_object.h"

namespace OHOS::Ace::NG {

class SheetContentCoverObject : public SheetObject {
    DECLARE_ACE_TYPE(SheetContentCoverObject, SheetObject);

public:
    SheetContentCoverObject(SheetType sheetType) : SheetObject(sheetType) {}
    NG::BorderWidthProperty PostProcessBorderWidth(const NG::BorderWidthProperty& borderWidth) override;
    void DirtyLayoutProcess(const RefPtr<LayoutAlgorithmWrapper>& layoutAlgorithmWrapper) override;
    void InitScrollProps() override;
    void ClipSheetNode() override;

    void SetFinishEventForAnimationOption(
        AnimationOption& option, bool isTransitionIn, bool isFirstTransition) override;
    AnimationOption GetAnimationOptionForOverlay(bool isTransitionIn, bool isFirstTransition) override;
    void InitAnimationForOverlay(bool isTransitionIn, bool isFirstTransition) override;
    std::function<void()> GetAnimationPropertyCallForOverlay(bool isTransitionIn) override;

    void SetSheetAnimationOption(AnimationOption& option) const override;
    RefPtr<InterpolatingSpring> GetSheetTransitionCurve(float dragVelocity) const override;
    std::function<void()> GetSheetTransitionFinishEvent(bool isTransitionIn) override;
    std::function<void()> GetSheetAnimationEvent(bool isTransitionIn, float offset) override;

    ScrollResult HandleScroll(float scrollOffset, int32_t source, NestedState state, float velocity = 0.f) override
    {
        return { 0.0f, true };
    }
    void OnScrollStartRecursive(float position, float dragVelocity = 0.0f) override {};
    void OnScrollEndRecursive(const std::optional<float>& velocity) override {};
    bool HandleScrollVelocity(float velocity) override
    {
        return false;
    }

    void HandleDragStart() override {};
    void HandleDragUpdate(const GestureEvent& info) override {};
    void HandleDragEnd(float dragVelocity) override {};

    void BeforeCreateLayoutWrapper() override {};
    SheetKeyboardAvoidMode GetAvoidKeyboardModeByDefault() const override
    {
        return SheetKeyboardAvoidMode::NONE;
    }
    void AvoidKeyboardInDirtyLayoutProcess() override {};
    void AvoidKeyboard(bool forceAvoid) override {};

    void FireHeightDidChange() override;

    bool CheckIfUpdateObject(SheetType newType) override
    {
        return newType != SheetType::SHEET_CONTENT_COVER;
    }

    bool IsSheetObjectBase() const override
    {
        return false;
    }

    bool CheckIfNeedSetOuterBorderProp() const override
    {
        return false;
    }

    bool CheckIfNeedShadowByDefault() const override
    {
        return false;
    }
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SHEET_CONTENT_COVER_SHEET_CONTENT_COVER_OBJECT_H

