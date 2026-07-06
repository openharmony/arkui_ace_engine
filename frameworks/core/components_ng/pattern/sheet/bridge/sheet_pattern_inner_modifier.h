/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SHEET_BRIDGE_SHEET_PATTERN_INNER_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SHEET_BRIDGE_SHEET_PATTERN_INNER_MODIFIER_H

#include <cstdint>
#include <functional>
#include <string>

#include "base/memory/referenced.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/shadow.h"
#include "core/components_ng/pattern/sheet/sheet_style.h"

namespace OHOS::Ace::NG {
class FrameNode;
class OverlayManager;
class SheetObject;

struct ArkUISheetPatternInnerModifier {
    void (*sheetInteractiveDismiss)(const RefPtr<FrameNode>& sheetNode, BindSheetDismissReason reason);
    void (*sheetOnWillDisappear)(const RefPtr<FrameNode>& sheetNode);
    void (*sheetOnDisappear)(const RefPtr<FrameNode>& sheetNode);
    void (*sheetDismissTransition)(const RefPtr<FrameNode>& sheetNode, bool dismiss, float velocity);
    void (*sheetSheetTransition)(const RefPtr<FrameNode>& sheetNode, bool isTransitionIn, float velocity);
    int32_t (*sheetGetTargetId)(const RefPtr<FrameNode>& sheetNode);
    std::string (*sheetGetTargetTag)(const RefPtr<FrameNode>& sheetNode);
    void (*sheetFireCallback)(const RefPtr<FrameNode>& sheetNode, const std::string& value);
    SheetKey (*sheetGetSheetKey)(const RefPtr<FrameNode>& sheetNode);
    void (*sheetSetDismissProcess)(const RefPtr<FrameNode>& sheetNode, bool isProcess);
    void (*sheetSetSheetKey)(const RefPtr<FrameNode>& sheetNode, const SheetKey& sheetKey);
    void (*sheetSetOverlay)(const RefPtr<FrameNode>& sheetNode, const WeakPtr<OverlayManager>& overlayManager);
    bool (*sheetIsShowInSubWindow)(const RefPtr<FrameNode>& sheetNode);
    bool (*sheetHasInstanceId)(const RefPtr<FrameNode>& sheetNode);
    bool (*sheetIsShowInPage)(const RefPtr<FrameNode>& sheetNode);
    SheetType (*sheetGetSheetObjectType)(const RefPtr<FrameNode>& sheetNode);
    void (*sheetOnCoordScrollStart)(const RefPtr<Pattern>& pattern);
    bool (*sheetOnCoordScrollUpdate)(const RefPtr<Pattern>& pattern, float scrollOffset);
    void (*sheetOnCoordScrollEnd)(const RefPtr<Pattern>& pattern, float dragVelocity);
    void (*sheetAvoidSafeArea)(const RefPtr<FrameNode>& sheetNode, bool forceAvoid);
    RefPtr<FrameNode> (*sheetGetParentSkipEffectComponent)(const RefPtr<FrameNode>& sheetNode);
    bool (*sheetCheckIfUseEffectComponent)(const RefPtr<FrameNode>& sheetNode, const SheetStyle& sheetStyle);
    bool (*sheetIsPhoneInLandscape)(const RefPtr<FrameNode>& sheetNode);

    bool (*sheetIsDragging)(const RefPtr<FrameNode>& sheetNode);
    void (*sheetOnWillAppear)(const RefPtr<FrameNode>& sheetNode);
    void (*sheetOnAppear)(const RefPtr<FrameNode>& sheetNode);
    bool (*sheetIsExecuteOnDisappear)(const RefPtr<FrameNode>& sheetNode);
    RefPtr<FrameNode> (*sheetGetFirstFrameNodeOfBuilder)(const RefPtr<FrameNode>& sheetNode);
    void (*sheetIsNeedPlayTransition)(const RefPtr<FrameNode>& sheetNode, const SheetStyle& sheetStyle);
    void (*sheetUpdateDragBarStatus)(const RefPtr<FrameNode>& sheetNode);
    void (*sheetUpdateTitleColumnSize)(const RefPtr<FrameNode>& sheetNode);
    void (*sheetSetBottomOffset)(const RefPtr<FrameNode>& sheetNode, const SheetStyle& sheetStyle);
    Color (*sheetGetMaskBackgroundColor)(const RefPtr<FrameNode>& sheetNode);
    bool (*sheetUpdateIndexByDetentSelection)(
        const RefPtr<FrameNode>& sheetNode, const SheetStyle& sheetStyle, bool isFirstTransition);
    std::function<void()> (*sheetHasOnWillAppear)(const RefPtr<FrameNode>& sheetNode);
    std::function<void()> (*sheetHasOnAppear)(const RefPtr<FrameNode>& sheetNode);
    void (*sheetUpdateSheetParamResource)(const RefPtr<FrameNode>& sheetNode, NG::SheetStyle& sheetStyle);
    bool (*sheetUpdateThemeScopeUpdate)(const RefPtr<FrameNode>& sheetNode, int32_t themeScopeId);
    RefPtr<SheetObject> (*sheetGetSheetObject)(const RefPtr<FrameNode>& sheetNode);
    bool (*sheetIsSheetObjectBase)(const RefPtr<FrameNode>& sheetNode);
    float (*sheetGetSheetHeightForTranslate)(const RefPtr<FrameNode>& sheetNode);
    void (*sheetSheetTransitionForOverlay)(
        const RefPtr<FrameNode>& sheetNode, bool isTransitionIn, bool isFirstTransition);
    void (*sheetResetToInvisible)(const RefPtr<FrameNode>& sheetNode);
    void (*sheetStartOffsetEnteringAnimation)(const RefPtr<FrameNode>& sheetNode);
    void (*sheetFireCommonCallback)(const RefPtr<FrameNode>& sheetNode);
    void (*sheetStartAlphaEnteringAnimation)(const RefPtr<FrameNode>& sheetNode, std::function<void()>&& finish);
    void (*sheetStartOffsetExitingAnimation)(const RefPtr<FrameNode>& sheetNode);
    void (*sheetStartAlphaExitingAnimation)(const RefPtr<FrameNode>& sheetNode, std::function<void()>&& finish);
    void (*sheetClearSheetRenderMaterial)(const RefPtr<FrameNode>& sheetNode);
    Shadow (*sheetGetShadowFromTheme)(const RefPtr<FrameNode>& sheetNode, ShadowStyle shadowStyle);
    void (*sheetSetSheetBorderWidth)(const RefPtr<FrameNode>& sheetNode);
    void (*sheetUpdateMaskBackgroundColor)(const RefPtr<FrameNode>& sheetNode);
    void (*sheetSetSheetRenderMaterial)(const RefPtr<FrameNode>& sheetNode);
    void (*sheetSetEnableDragControl)(const RefPtr<FrameNode>& sheetNode, bool enable);
    float (*sheetGetPageHeightWithoutOffset)(const RefPtr<FrameNode>& sheetNode);
    float (*sheetGetSheetTopSafeArea)(const RefPtr<FrameNode>& sheetNode);
    void (*sheetSetSheetHeightForTranslate)(const RefPtr<FrameNode>& sheetNode, float height);
    uint32_t (*sheetGetDetentsFinalIndex)(const RefPtr<FrameNode>& sheetNode);
    float (*sheetGetFitContentHeight)(const RefPtr<FrameNode>& sheetNode);
    float (*sheetGetSheetOffset)(const RefPtr<FrameNode>& sheetNode);
    SheetType (*sheetGetSheetTypeNoProcess)(const RefPtr<FrameNode>& sheetNode);
    SheetStyle (*sheetGetSheetStyleValue)(const RefPtr<FrameNode>& sheetNode);
    void (*sheetLayoutPropUpdateSheetStyle)(const RefPtr<FrameNode>& sheetNode, const SheetStyle& sheetStyle);
    bool (*sheetGetIsPlayTransition)(const RefPtr<FrameNode>& sheetNode);
    void (*sheetUpdateSheetCallbacks)(const RefPtr<FrameNode>& sheetNode, std::function<void()>&& onAppear,
        std::function<void()>&& onDisappear, std::function<void()>&& shouldDismiss,
        std::function<void(const int32_t)>&& onWillDismiss, std::function<void()>&& onWillAppear,
        std::function<void()>&& onWillDisappear, std::function<void(const float)>&& onHeightDidChange,
        std::function<void(const float)>&& onDetentsDidChange, std::function<void(const float)>&& onWidthDidChange,
        std::function<void(const float)>&& onTypeDidChange, std::function<void()>&& sheetSpringBack);
    void (*sheetUpdateSheetTypeAndObject)(const RefPtr<FrameNode>& sheetNode, const SheetStyle& sheetStyle);
    void (*sheetSetShowState)(const RefPtr<FrameNode>& sheetNode, bool show);
    void (*sheetOverlayDismissSheet)(const RefPtr<FrameNode>& sheetNode);
    void (*sheetOverlaySheetSpringBack)(const RefPtr<FrameNode>& sheetNode);
    void (*sheetSheetSpringBack)(const RefPtr<FrameNode>& sheetNode);
    void (*sheetDismissSheetAction)(const RefPtr<FrameNode>& sheetNode);
    bool (*sheetIsPresentationPattern)(const RefPtr<Pattern>& pattern);
};

namespace InnerModifier {
constexpr const char* SHEET_PATTERN_INNER_MODIFIER = "sheetPatternInnerModifier";
const ArkUISheetPatternInnerModifier* GetSheetPatternInnerModifier();
} // namespace InnerModifier
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SHEET_BRIDGE_SHEET_PATTERN_INNER_MODIFIER_H
