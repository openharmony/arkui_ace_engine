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

#include "core/components_ng/pattern/sheet/bridge/sheet_pattern_inner_modifier.h"

#include "ui/base/utils/utils.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/sheet/sheet_object.h"
#include "core/components_ng/pattern/sheet/sheet_presentation_pattern.h"
#include "core/components_ng/pattern/sheet/sheet_presentation_property.h"
#include "core/components_ng/render/render_context.h"

namespace OHOS::Ace::NG::InnerModifier {
namespace {
constexpr char EFFECT_COMPONENT_ETS_TAG[] = "EffectComponent";
void SheetInteractiveDismiss(const RefPtr<FrameNode>& sheetNode, BindSheetDismissReason reason)
{
    CHECK_NULL_VOID(sheetNode);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    sheetPattern->SheetInteractiveDismiss(reason);
}

void SheetOnWillDisappear(const RefPtr<FrameNode>& sheetNode)
{
    CHECK_NULL_VOID(sheetNode);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    sheetPattern->OnWillDisappear();
}

void SheetOnDisappear(const RefPtr<FrameNode>& sheetNode)
{
    CHECK_NULL_VOID(sheetNode);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    sheetPattern->OnDisappear();
}

void SheetDismissTransition(const RefPtr<FrameNode>& sheetNode, bool dismiss, float velocity)
{
    CHECK_NULL_VOID(sheetNode);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    sheetPattern->DismissTransition(dismiss, velocity);
}

void SheetSheetTransition(const RefPtr<FrameNode>& sheetNode, bool isTransitionIn, float velocity)
{
    CHECK_NULL_VOID(sheetNode);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    sheetPattern->SheetTransition(isTransitionIn, velocity);
}

int32_t SheetGetTargetId(const RefPtr<FrameNode>& sheetNode)
{
    CHECK_NULL_RETURN(sheetNode, -1);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_RETURN(sheetPattern, -1);
    return sheetPattern->GetTargetId();
}

std::string SheetGetTargetTag(const RefPtr<FrameNode>& sheetNode)
{
    CHECK_NULL_RETURN(sheetNode, "");
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_RETURN(sheetPattern, "");
    return sheetPattern->GetTargetTag();
}

void SheetFireCallback(const RefPtr<FrameNode>& sheetNode, const std::string& value)
{
    CHECK_NULL_VOID(sheetNode);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    sheetPattern->FireCallback(value);
}

SheetKey SheetGetSheetKey(const RefPtr<FrameNode>& sheetNode)
{
    CHECK_NULL_RETURN(sheetNode, SheetKey(-1));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_RETURN(sheetPattern, SheetKey(-1));
    return sheetPattern->GetSheetKey();
}

void SheetSetDismissProcess(const RefPtr<FrameNode>& sheetNode, bool isProcess)
{
    CHECK_NULL_VOID(sheetNode);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    sheetPattern->SetDismissProcess(isProcess);
}

void SheetSetSheetKey(const RefPtr<FrameNode>& sheetNode, const SheetKey& sheetKey)
{
    CHECK_NULL_VOID(sheetNode);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    sheetPattern->SetSheetKey(sheetKey);
}

void SheetSetOverlay(const RefPtr<FrameNode>& sheetNode, const WeakPtr<OverlayManager>& overlayManager)
{
    CHECK_NULL_VOID(sheetNode);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    sheetPattern->SetOverlay(overlayManager);
}

bool SheetIsShowInSubWindow(const RefPtr<FrameNode>& sheetNode)
{
    CHECK_NULL_RETURN(sheetNode, false);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_RETURN(sheetPattern, false);
    return sheetPattern->IsShowInSubWindow();
}

bool SheetHasInstanceId(const RefPtr<FrameNode>& sheetNode)
{
    CHECK_NULL_RETURN(sheetNode, false);
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    return layoutProperty->GetSheetStyleValue(SheetStyle()).instanceId.has_value();
}

bool SheetIsShowInPage(const RefPtr<FrameNode>& sheetNode)
{
    CHECK_NULL_RETURN(sheetNode, false);
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    return layoutProperty->GetSheetStyleValue(SheetStyle()).showInPage.value_or(false);
}

SheetType SheetGetSheetObjectType(const RefPtr<FrameNode>& sheetNode)
{
    CHECK_NULL_RETURN(sheetNode, SheetType::SHEET_BOTTOM);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_RETURN(sheetPattern, SheetType::SHEET_BOTTOM);
    auto sheetObject = sheetPattern->GetSheetObject();
    CHECK_NULL_RETURN(sheetObject, SheetType::SHEET_BOTTOM);
    return sheetObject->GetSheetType();
}

void SheetOnCoordScrollStart(const RefPtr<Pattern>& pattern)
{
    CHECK_NULL_VOID(pattern);
    auto sheetPattern = AceType::DynamicCast<SheetPresentationPattern>(pattern);
    CHECK_NULL_VOID(sheetPattern);
    sheetPattern->OnCoordScrollStart();
}

bool SheetOnCoordScrollUpdate(const RefPtr<Pattern>& pattern, float scrollOffset)
{
    CHECK_NULL_RETURN(pattern, false);
    auto sheetPattern = AceType::DynamicCast<SheetPresentationPattern>(pattern);
    CHECK_NULL_RETURN(sheetPattern, false);
    return sheetPattern->OnCoordScrollUpdate(scrollOffset);
}

void SheetOnCoordScrollEnd(const RefPtr<Pattern>& pattern, float dragVelocity)
{
    CHECK_NULL_VOID(pattern);
    auto sheetPattern = AceType::DynamicCast<SheetPresentationPattern>(pattern);
    CHECK_NULL_VOID(sheetPattern);
    sheetPattern->OnCoordScrollEnd(dragVelocity);
}

void SheetAvoidSafeArea(const RefPtr<FrameNode>& sheetNode, bool forceAvoid)
{
    CHECK_NULL_VOID(sheetNode);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    sheetPattern->AvoidSafeArea(forceAvoid);
}

RefPtr<FrameNode> SheetGetParentSkipEffectComponent(const RefPtr<FrameNode>& node)
{
    return SheetPresentationPattern::GetParentSkipEffectComponent(node);
}

bool SheetCheckIfUseEffectComponent(const RefPtr<FrameNode>& sheetNode, const SheetStyle& sheetStyle)
{
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_RETURN(sheetPattern, false);
    return sheetPattern->CheckIfUseEffectComponent(sheetStyle);
}

bool SheetIsPhoneInLandscape(const RefPtr<FrameNode>& sheetNode)
{
    CHECK_NULL_RETURN(sheetNode, false);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_RETURN(sheetPattern, false);
    return sheetPattern->IsPhoneInLandScape();
}

bool SheetIsDragging(const RefPtr<FrameNode>& sheetNode)
{
    CHECK_NULL_RETURN(sheetNode, false);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_RETURN(sheetPattern, false);
    return sheetPattern->IsDragging();
}

void SheetOnWillAppear(const RefPtr<FrameNode>& sheetNode)
{
    CHECK_NULL_VOID(sheetNode);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    sheetPattern->OnWillAppear();
}

void SheetOnAppear(const RefPtr<FrameNode>& sheetNode)
{
    CHECK_NULL_VOID(sheetNode);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    sheetPattern->OnAppear();
}

bool SheetIsExecuteOnDisappear(const RefPtr<FrameNode>& sheetNode)
{
    CHECK_NULL_RETURN(sheetNode, false);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_RETURN(sheetPattern, false);
    return sheetPattern->IsExecuteOnDisappear();
}

RefPtr<FrameNode> SheetGetFirstFrameNodeOfBuilder(const RefPtr<FrameNode>& sheetNode)
{
    CHECK_NULL_RETURN(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_RETURN(sheetPattern, nullptr);
    return sheetPattern->GetFirstFrameNodeOfBuilder();
}

void SheetIsNeedPlayTransition(const RefPtr<FrameNode>& sheetNode, const SheetStyle& sheetStyle)
{
    CHECK_NULL_VOID(sheetNode);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    sheetPattern->IsNeedPlayTransition(sheetStyle);
}

void SheetUpdateDragBarStatus(const RefPtr<FrameNode>& sheetNode)
{
    CHECK_NULL_VOID(sheetNode);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    sheetPattern->UpdateDragBarStatus();
}

void SheetUpdateTitleColumnSize(const RefPtr<FrameNode>& sheetNode)
{
    CHECK_NULL_VOID(sheetNode);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    sheetPattern->UpdateTitleColumnSize();
}

void SheetSetBottomOffset(const RefPtr<FrameNode>& sheetNode, const SheetStyle& sheetStyle)
{
    CHECK_NULL_VOID(sheetNode);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    sheetPattern->SetBottomOffset(sheetStyle);
}

Color SheetGetMaskBackgroundColor(const RefPtr<FrameNode>& sheetNode)
{
    CHECK_NULL_RETURN(sheetNode, Color::TRANSPARENT);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_RETURN(sheetPattern, Color::TRANSPARENT);
    return sheetPattern->GetMaskBackgroundColor();
}

bool SheetUpdateIndexByDetentSelection(
    const RefPtr<FrameNode>& sheetNode, const SheetStyle& sheetStyle, bool isFirstTransition)
{
    CHECK_NULL_RETURN(sheetNode, false);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_RETURN(sheetPattern, false);
    return sheetPattern->UpdateIndexByDetentSelection(sheetStyle, isFirstTransition);
}

std::function<void()> SheetHasOnWillAppear(const RefPtr<FrameNode>& sheetNode)
{
    CHECK_NULL_RETURN(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_RETURN(sheetPattern, nullptr);
    return sheetPattern->GetSheetOnWillAppear();
}

std::function<void()> SheetHasOnAppear(const RefPtr<FrameNode>& sheetNode)
{
    CHECK_NULL_RETURN(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_RETURN(sheetPattern, nullptr);
    return sheetPattern->GetSheetOnAppear();
}

void SheetUpdateSheetParamResource(const RefPtr<FrameNode>& sheetNode, NG::SheetStyle& sheetStyle)
{
    CHECK_NULL_VOID(sheetNode);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    sheetPattern->UpdateSheetParamResource(sheetNode, sheetStyle);
}

bool SheetUpdateThemeScopeUpdate(const RefPtr<FrameNode>& sheetNode, int32_t themeScopeId)
{
    CHECK_NULL_RETURN(sheetNode, false);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_RETURN(sheetPattern, false);
    return sheetPattern->OnThemeScopeUpdate(themeScopeId);
}

RefPtr<SheetObject> SheetGetSheetObject(const RefPtr<FrameNode>& sheetNode)
{
    CHECK_NULL_RETURN(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_RETURN(sheetPattern, nullptr);
    return sheetPattern->GetSheetObject();
}

bool SheetIsSheetObjectBase(const RefPtr<FrameNode>& sheetNode)
{
    CHECK_NULL_RETURN(sheetNode, false);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_RETURN(sheetPattern, false);
    auto sheetObject = sheetPattern->GetSheetObject();
    CHECK_NULL_RETURN(sheetObject, false);
    return sheetObject->IsSheetObjectBase();
}

float SheetGetSheetHeightForTranslate(const RefPtr<FrameNode>& sheetNode)
{
    CHECK_NULL_RETURN(sheetNode, 0.0f);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_RETURN(sheetPattern, 0.0f);
    return sheetPattern->GetSheetHeightForTranslate();
}

void SheetSheetTransitionForOverlay(const RefPtr<FrameNode>& sheetNode, bool isTransitionIn, bool isFirstTransition)
{
    CHECK_NULL_VOID(sheetNode);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    sheetPattern->SheetTransitionForOverlay(isTransitionIn, isFirstTransition);
}

void SheetResetToInvisible(const RefPtr<FrameNode>& sheetNode)
{
    CHECK_NULL_VOID(sheetNode);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    sheetPattern->ResetToInvisible();
}

void SheetStartOffsetEnteringAnimation(const RefPtr<FrameNode>& sheetNode)
{
    CHECK_NULL_VOID(sheetNode);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    sheetPattern->StartOffsetEnteringAnimation();
}

void SheetFireCommonCallback(const RefPtr<FrameNode>& sheetNode)
{
    CHECK_NULL_VOID(sheetNode);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    sheetPattern->FireCommonCallback();
}

void SheetStartAlphaEnteringAnimation(const RefPtr<FrameNode>& sheetNode, std::function<void()>&& finish)
{
    CHECK_NULL_VOID(sheetNode);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    sheetPattern->StartAlphaEnteringAnimation(std::move(finish));
}

void SheetStartOffsetExitingAnimation(const RefPtr<FrameNode>& sheetNode)
{
    CHECK_NULL_VOID(sheetNode);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    sheetPattern->StartOffsetExitingAnimation();
}

void SheetStartAlphaExitingAnimation(const RefPtr<FrameNode>& sheetNode, std::function<void()>&& finish)
{
    CHECK_NULL_VOID(sheetNode);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    sheetPattern->StartAlphaExitingAnimation(std::move(finish));
}

void SheetClearSheetRenderMaterial(const RefPtr<FrameNode>& sheetNode)
{
    CHECK_NULL_VOID(sheetNode);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    sheetPattern->ClearSheetRenderMaterial();
}

Shadow SheetGetShadowFromTheme(const RefPtr<FrameNode>& sheetNode, ShadowStyle shadowStyle)
{
    Shadow defaultShadow;
    CHECK_NULL_RETURN(sheetNode, defaultShadow);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_RETURN(sheetPattern, defaultShadow);
    return sheetPattern->GetShadowFromTheme(shadowStyle);
}

void SheetSetSheetBorderWidth(const RefPtr<FrameNode>& sheetNode)
{
    CHECK_NULL_VOID(sheetNode);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    sheetPattern->SetSheetBorderWidth();
}

void SheetUpdateMaskBackgroundColor(const RefPtr<FrameNode>& sheetNode)
{
    CHECK_NULL_VOID(sheetNode);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    sheetPattern->UpdateMaskBackgroundColor();
}

void SheetSetSheetRenderMaterial(const RefPtr<FrameNode>& sheetNode)
{
    CHECK_NULL_VOID(sheetNode);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    sheetPattern->SetSheetRenderMaterial();
}

void SheetSetEnableDragControl(const RefPtr<FrameNode>& sheetNode, bool enable)
{
    CHECK_NULL_VOID(sheetNode);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    sheetPattern->SetEnableDragControl(enable);
}

float SheetGetPageHeightWithoutOffset(const RefPtr<FrameNode>& sheetNode)
{
    CHECK_NULL_RETURN(sheetNode, 0.0f);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_RETURN(sheetPattern, 0.0f);
    return sheetPattern->GetPageHeightWithoutOffset();
}

float SheetGetSheetTopSafeArea(const RefPtr<FrameNode>& sheetNode)
{
    CHECK_NULL_RETURN(sheetNode, 0.0f);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_RETURN(sheetPattern, 0.0f);
    return sheetPattern->GetSheetTopSafeArea();
}

void SheetSetSheetHeightForTranslate(const RefPtr<FrameNode>& sheetNode, float height)
{
    CHECK_NULL_VOID(sheetNode);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    sheetPattern->SetSheetHeightForTranslate(height);
}

uint32_t SheetGetDetentsFinalIndex(const RefPtr<FrameNode>& sheetNode)
{
    CHECK_NULL_RETURN(sheetNode, 0);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_RETURN(sheetPattern, 0);
    return sheetPattern->GetDetentsFinalIndex();
}

float SheetGetFitContentHeight(const RefPtr<FrameNode>& sheetNode)
{
    CHECK_NULL_RETURN(sheetNode, 0.0f);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_RETURN(sheetPattern, 0.0f);
    return sheetPattern->GetFitContentHeight();
}

float SheetGetSheetOffset(const RefPtr<FrameNode>& sheetNode)
{
    CHECK_NULL_RETURN(sheetNode, 0.0f);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_RETURN(sheetPattern, 0.0f);
    return sheetPattern->GetSheetOffset();
}

SheetType SheetGetSheetTypeNoProcess(const RefPtr<FrameNode>& sheetNode)
{
    CHECK_NULL_RETURN(sheetNode, SheetType::SHEET_BOTTOM);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_RETURN(sheetPattern, SheetType::SHEET_BOTTOM);
    return sheetPattern->GetSheetTypeNoProcess();
}

SheetStyle SheetGetSheetStyleValue(const RefPtr<FrameNode>& sheetNode)
{
    SheetStyle style;
    CHECK_NULL_RETURN(sheetNode, style);
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_RETURN(layoutProperty, style);
    return layoutProperty->GetSheetStyleValue(SheetStyle());
}

void SheetLayoutPropUpdateSheetStyle(const RefPtr<FrameNode>& sheetNode, const SheetStyle& sheetStyle)
{
    CHECK_NULL_VOID(sheetNode);
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateSheetStyle(sheetStyle);
}

bool SheetGetIsPlayTransition(const RefPtr<FrameNode>& sheetNode)
{
    CHECK_NULL_RETURN(sheetNode, false);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_RETURN(sheetPattern, false);
    return sheetPattern->GetIsPlayTransition();
}

void SheetUpdateSheetCallbacks(const RefPtr<FrameNode>& sheetNode, std::function<void()>&& onAppear,
    std::function<void()>&& onDisappear, std::function<void()>&& shouldDismiss,
    std::function<void(const int32_t)>&& onWillDismiss, std::function<void()>&& onWillAppear,
    std::function<void()>&& onWillDisappear, std::function<void(const float)>&& onHeightDidChange,
    std::function<void(const float)>&& onDetentsDidChange, std::function<void(const float)>&& onWidthDidChange,
    std::function<void(const float)>&& onTypeDidChange, std::function<void()>&& sheetSpringBack)
{
    CHECK_NULL_VOID(sheetNode);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    sheetPattern->UpdateOnAppear(std::move(onAppear));
    sheetPattern->UpdateOnDisappear(std::move(onDisappear));
    sheetPattern->UpdateShouldDismiss(std::move(shouldDismiss));
    sheetPattern->UpdateOnWillDismiss(std::move(onWillDismiss));
    sheetPattern->UpdateOnWillAppear(std::move(onWillAppear));
    sheetPattern->UpdateOnWillDisappear(std::move(onWillDisappear));
    sheetPattern->UpdateOnHeightDidChange(std::move(onHeightDidChange));
    sheetPattern->UpdateOnDetentsDidChange(std::move(onDetentsDidChange));
    sheetPattern->UpdateOnWidthDidChange(std::move(onWidthDidChange));
    sheetPattern->UpdateOnTypeDidChange(std::move(onTypeDidChange));
    sheetPattern->UpdateSheetSpringBack(std::move(sheetSpringBack));
}

void SheetUpdateSheetTypeAndObject(const RefPtr<FrameNode>& sheetNode, const SheetStyle& sheetStyle)
{
    CHECK_NULL_VOID(sheetNode);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    sheetPattern->UpdateSheetType();
    sheetPattern->SetSheetEdgeLightMode(sheetStyle);
    sheetPattern->UpdateSheetObject(sheetPattern->GetSheetTypeNoProcess());
}

void SheetSetShowState(const RefPtr<FrameNode>& sheetNode, bool show)
{
    CHECK_NULL_VOID(sheetNode);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    sheetPattern->SetShowState(show);
}

void SheetOverlayDismissSheet(const RefPtr<FrameNode>& sheetNode)
{
    CHECK_NULL_VOID(sheetNode);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    sheetPattern->OverlayDismissSheet();
}

void SheetOverlaySheetSpringBack(const RefPtr<FrameNode>& sheetNode)
{
    CHECK_NULL_VOID(sheetNode);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    sheetPattern->OverlaySheetSpringBack();
}

void SheetSheetSpringBack(const RefPtr<FrameNode>& sheetNode)
{
    CHECK_NULL_VOID(sheetNode);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    sheetPattern->SheetSpringBack();
}

void SheetDismissSheetAction(const RefPtr<FrameNode>& sheetNode)
{
    CHECK_NULL_VOID(sheetNode);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    sheetPattern->DismissSheet();
}

bool SheetIsPresentationPattern(const RefPtr<Pattern>& pattern)
{
    return AceType::InstanceOf<SheetPresentationPattern>(pattern);
}

void SheetSetSheetBlurSnapshotFreeze(const RefPtr<FrameNode>& sheetPageNode, const SheetStyle& sheetStyle,
    bool isPartialUpdate)
{
    CHECK_NULL_VOID(sheetPageNode);
    auto sheetPattern = sheetPageNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    if (!sheetPattern->CheckIfUseEffectComponent(sheetStyle)) {
        return;
    }
    if (isPartialUpdate && !sheetStyle.blurSnapshotOptions.has_value()) {
        return;
    }
    auto sheetECNode = AceType::DynamicCast<FrameNode>(sheetPageNode->GetParent());
    CHECK_NULL_VOID(sheetECNode);
    if (sheetECNode->GetTag() == EFFECT_COMPONENT_ETS_TAG) {
        auto ecRSContext = sheetECNode->GetRenderContext();
        CHECK_NULL_VOID(ecRSContext);
        ecRSContext->UpdateFreeze(
            sheetStyle.blurSnapshotOptions.has_value() && sheetStyle.blurSnapshotOptions->enableFreeze.value_or(false));
    }
}
} // namespace

const ArkUISheetPatternInnerModifier* GetSheetPatternInnerModifier()
{
    static const ArkUISheetPatternInnerModifier modifier = {
        .sheetInteractiveDismiss = SheetInteractiveDismiss,
        .sheetOnWillDisappear = SheetOnWillDisappear,
        .sheetOnDisappear = SheetOnDisappear,
        .sheetDismissTransition = SheetDismissTransition,
        .sheetSheetTransition = SheetSheetTransition,
        .sheetGetTargetId = SheetGetTargetId,
        .sheetGetTargetTag = SheetGetTargetTag,
        .sheetFireCallback = SheetFireCallback,
        .sheetGetSheetKey = SheetGetSheetKey,
        .sheetSetDismissProcess = SheetSetDismissProcess,
        .sheetSetSheetKey = SheetSetSheetKey,
        .sheetSetOverlay = SheetSetOverlay,
        .sheetIsShowInSubWindow = SheetIsShowInSubWindow,
        .sheetHasInstanceId = SheetHasInstanceId,
        .sheetIsShowInPage = SheetIsShowInPage,
        .sheetGetSheetObjectType = SheetGetSheetObjectType,
        .sheetOnCoordScrollStart = SheetOnCoordScrollStart,
        .sheetOnCoordScrollUpdate = SheetOnCoordScrollUpdate,
        .sheetOnCoordScrollEnd = SheetOnCoordScrollEnd,
        .sheetAvoidSafeArea = SheetAvoidSafeArea,
        .sheetGetParentSkipEffectComponent = SheetGetParentSkipEffectComponent,
        .sheetCheckIfUseEffectComponent = SheetCheckIfUseEffectComponent,
        .sheetIsPhoneInLandscape = SheetIsPhoneInLandscape,
        .sheetIsDragging = SheetIsDragging,
        .sheetOnWillAppear = SheetOnWillAppear,
        .sheetOnAppear = SheetOnAppear,
        .sheetIsExecuteOnDisappear = SheetIsExecuteOnDisappear,
        .sheetGetFirstFrameNodeOfBuilder = SheetGetFirstFrameNodeOfBuilder,
        .sheetIsNeedPlayTransition = SheetIsNeedPlayTransition,
        .sheetUpdateDragBarStatus = SheetUpdateDragBarStatus,
        .sheetUpdateTitleColumnSize = SheetUpdateTitleColumnSize,
        .sheetSetBottomOffset = SheetSetBottomOffset,
        .sheetGetMaskBackgroundColor = SheetGetMaskBackgroundColor,
        .sheetUpdateIndexByDetentSelection = SheetUpdateIndexByDetentSelection,
        .sheetHasOnWillAppear = SheetHasOnWillAppear,
        .sheetHasOnAppear = SheetHasOnAppear,
        .sheetUpdateSheetParamResource = SheetUpdateSheetParamResource,
        .sheetUpdateThemeScopeUpdate = SheetUpdateThemeScopeUpdate,
        .sheetGetSheetObject = SheetGetSheetObject,
        .sheetIsSheetObjectBase = SheetIsSheetObjectBase,
        .sheetGetSheetHeightForTranslate = SheetGetSheetHeightForTranslate,
        .sheetSheetTransitionForOverlay = SheetSheetTransitionForOverlay,
        .sheetResetToInvisible = SheetResetToInvisible,
        .sheetStartOffsetEnteringAnimation = SheetStartOffsetEnteringAnimation,
        .sheetFireCommonCallback = SheetFireCommonCallback,
        .sheetStartAlphaEnteringAnimation = SheetStartAlphaEnteringAnimation,
        .sheetStartOffsetExitingAnimation = SheetStartOffsetExitingAnimation,
        .sheetStartAlphaExitingAnimation = SheetStartAlphaExitingAnimation,
        .sheetClearSheetRenderMaterial = SheetClearSheetRenderMaterial,
        .sheetGetShadowFromTheme = SheetGetShadowFromTheme,
        .sheetSetSheetBorderWidth = SheetSetSheetBorderWidth,
        .sheetUpdateMaskBackgroundColor = SheetUpdateMaskBackgroundColor,
        .sheetSetSheetRenderMaterial = SheetSetSheetRenderMaterial,
        .sheetSetEnableDragControl = SheetSetEnableDragControl,
        .sheetGetPageHeightWithoutOffset = SheetGetPageHeightWithoutOffset,
        .sheetGetSheetTopSafeArea = SheetGetSheetTopSafeArea,
        .sheetSetSheetHeightForTranslate = SheetSetSheetHeightForTranslate,
        .sheetGetDetentsFinalIndex = SheetGetDetentsFinalIndex,
        .sheetGetFitContentHeight = SheetGetFitContentHeight,
        .sheetGetSheetOffset = SheetGetSheetOffset,
        .sheetGetSheetTypeNoProcess = SheetGetSheetTypeNoProcess,
        .sheetGetSheetStyleValue = SheetGetSheetStyleValue,
        .sheetLayoutPropUpdateSheetStyle = SheetLayoutPropUpdateSheetStyle,
        .sheetGetIsPlayTransition = SheetGetIsPlayTransition,
        .sheetUpdateSheetCallbacks = SheetUpdateSheetCallbacks,
        .sheetUpdateSheetTypeAndObject = SheetUpdateSheetTypeAndObject,
        .sheetSetShowState = SheetSetShowState,
        .sheetOverlayDismissSheet = SheetOverlayDismissSheet,
        .sheetOverlaySheetSpringBack = SheetOverlaySheetSpringBack,
        .sheetSheetSpringBack = SheetSheetSpringBack,
        .sheetDismissSheetAction = SheetDismissSheetAction,
        .sheetIsPresentationPattern = SheetIsPresentationPattern,
        .sheetSetSheetBlurSnapshotFreeze = SheetSetSheetBlurSnapshotFreeze,
    };
    return &modifier;
}
} // namespace OHOS::Ace::NG::InnerModifier
