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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SHEET_SHEET_OBJECT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SHEET_SHEET_OBJECT_H

#include "base/memory/ace_type.h"

#include "core/common/window_animation_config.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/pattern/overlay/sheet_style.h"
#include "core/components_ng/pattern/scrollable/scrollable.h"

namespace OHOS::Ace::NG {

class SheetPresentationPattern;
enum class BindSheetDismissReason;

class SheetObject : public virtual AceType {
    DECLARE_ACE_TYPE(SheetObject, AceType);

public:
    SheetObject(SheetType sheetType) : sheetType_(sheetType) {}
    virtual BorderWidthProperty PostProcessBorderWidth(const BorderWidthProperty& borderWidth);
    virtual void DirtyLayoutProcess(const RefPtr<LayoutAlgorithmWrapper>& layoutAlgorithmWrapper);
    virtual RefPtr<InterpolatingSpring> GetSheetTransitionCurve(float dragVelocity) const;
    virtual std::function<void()> GetSheetTransitionFinishEvent(bool isTransitionIn);
    virtual std::function<void()> GetSheetAnimationEvent(bool isTransitionIn, float offset);
    virtual void ClipSheetNode();
    virtual void InitAnimationForOverlay(bool isTransitionIn, bool isFirstTransition);
    virtual void SetFinishEventForAnimationOption(
        AnimationOption& option, bool isTransitionIn, bool isFirstTransition);
    virtual AnimationOption GetAnimationOptionForOverlay(bool isTransitionIn, bool isFirstTransition);
    virtual std::function<void()> GetAnimationPropertyCallForOverlay(bool isTransitionIn);
    virtual void OnLanguageConfigurationUpdate() {};
    virtual PaddingPropertyF GetSheetSafeAreaPadding() const { return PaddingPropertyF(); };
    virtual void HandleDragStart();
    virtual void HandleDragUpdate(const GestureEvent& info);
    virtual void HandleDragEnd(float dragVelocity);
    virtual void ModifyFireSheetTransition(float dragVelocity);
    virtual void CreatePropertyCallback();
    virtual void BeforeCreateLayoutWrapper() {};
    virtual SheetKeyboardAvoidMode GetAvoidKeyboardModeByDefault() const;
    virtual void AvoidKeyboardInDirtyLayoutProcess();
    virtual void AvoidKeyboard(bool forceAvoid);

    virtual ScrollResult HandleScroll(float scrollOffset, int32_t source,
        NestedState state, float velocity = 0.f);
    virtual void OnScrollStartRecursive(float position, float dragVelocity = 0.0f);
    virtual void OnScrollEndRecursive (const std::optional<float>& velocity);
    virtual bool HandleScrollVelocity(float velocity);
    virtual void InitScrollProps();
    ScrollResult HandleScrollWithSheet(float scrollOffset);

    virtual uint32_t GetPanDirection() const
    {
        return PanDirection::VERTICAL;
    }

    virtual bool CheckIfNeedSetOuterBorderProp() const
    {
        return sheetType_ != SheetType::SHEET_POPUP;
    }

    virtual bool CheckIfNeedShadowByDefault() const
    {
        return true;
    }

    void BindPattern(const WeakPtr<SheetPresentationPattern>& pattern)
    {
        auto patternPtr = pattern.Upgrade();
        if (patternPtr) {
            pattern_ = WeakPtr<SheetPresentationPattern>(pattern);
        }
    }

    RefPtr<SheetPresentationPattern> GetPattern() const
    {
        auto pattern = pattern_.Upgrade();
        return pattern;
    }

    float GetSheetHeight() const
    {
        return sheetHeight_;
    }

    void SetSheetHeight(float height)
    {
        sheetHeight_ = height;
    }

    SheetType GetSheetType() const
    {
        return sheetType_;
    }

    void UpdateSheetType(SheetType type)
    {
        sheetType_ = type;
    }

    void CopyData(const RefPtr<SheetObject>& other)
    {
        sheetWidth_ = other->sheetWidth_;
        sheetHeight_ = other->sheetHeight_;
    }
    
    virtual bool CheckIfUpdateObject(SheetType newType)
    {
        return (newType == SheetType::SHEET_SIDE) || (newType == SheetType::SHEET_CONTENT_COVER);
    }

    virtual bool IsSheetObjectBase() const
    {
        return true;
    }

    virtual void FireHeightDidChange();

    void SetCurrentOffset(float value)
    {
        currentOffset_ = value;
    }

protected:
    float sheetWidth_ = 0.0f; // sheet frameSize Width
    float sheetHeight_ = 0.0f; // sheet frameSize Height
    float sheetMaxWidth_ = 0.0f;
    float currentOffset_ = 0.0f;
    SheetType sheetType_;
    WeakPtr<SheetPresentationPattern> pattern_;
    // not need copy. Data that is not unique to the side style
    bool isSheetNeedScroll_ = false; // true if Sheet is ready to receive scroll offset.
    bool isSheetPosChanged_ = false; // UpdateTransformTranslate end
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SHEET_SHEET_OBJECT_H
