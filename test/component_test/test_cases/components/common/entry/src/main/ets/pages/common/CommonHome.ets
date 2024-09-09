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

import { CommonButton } from '../../util/CommonButton';

@Entry
@Component
struct OutlineColorSettingsHome {
  build() {
    Scroll() {
      Flex({ direction: FlexDirection.Row, wrap: FlexWrap.Wrap }) {
        Text('OutlineColorSettingsHome')
          .padding('15vp')
          .width('100%')
          .fontSize('25fp')
          .textAlign(TextAlign.Center)
        CommonButton({
          buttonName: 'AccessibilityDescriptionSample',
          buttonUrl: 'pages/common/AccessibilityDescriptionSample'
        });
        CommonButton({ buttonName: 'AccessibilityGroupSample', buttonUrl: 'pages/common/AccessibilityGroupSample' });
        CommonButton({ buttonName: 'AccessibilityLevelSample', buttonUrl: 'pages/common/AccessibilityLevelSample' });
        CommonButton({ buttonName: 'AccessibilityTextSample', buttonUrl: 'pages/common/AccessibilityTextSample' });
        CommonButton({
          buttonName: 'AccessibilityVirtualNodeSample',
          buttonUrl: 'pages/common/AccessibilityVirtualNodeSample'
        });
        CommonButton({ buttonName: 'AlignRulesSample', buttonUrl: 'pages/common/AlignRulesSample' });
        CommonButton({ buttonName: 'AspectRatioSample', buttonUrl: 'pages/common/AspectRatioSample' });
        CommonButton({ buttonName: 'AlignSample_one', buttonUrl: 'pages/common/AlignSample_one' });
        CommonButton({ buttonName: 'AlignSample_two', buttonUrl: 'pages/common/AlignSample_two' });
        CommonButton({ buttonName: 'AllowDropSample', buttonUrl: 'pages/common/AllowDropSample' });
        CommonButton({ buttonName: 'AttributeModifierSample', buttonUrl: 'pages/common/AttributeModifierSample' });
        CommonButton({ buttonName: 'AlignSelfSample', buttonUrl: 'pages/common/AlignSelfSample' });
        CommonButton({
          buttonName: 'BackGroundBrightnessSample',
          buttonUrl: 'pages/common/BackGroundBrightnessSample'
        });
        CommonButton({ buttonName: 'BindPopupSample_one', buttonUrl: 'pages/common/BindPopupSample_one' });
        CommonButton({ buttonName: 'BindPopupSample_two', buttonUrl: 'pages/common/BindPopupSample_two' });
        CommonButton({ buttonName: 'BindPopupSample_three', buttonUrl: 'pages/common/BindPopupSample_three' });
        CommonButton({ buttonName: 'BindPopupSample_four', buttonUrl: 'pages/common/BindPopupSample_four' });
        CommonButton({ buttonName: 'BindPopupSample_five', buttonUrl: 'pages/common/BindPopupSample_five' });
        CommonButton({ buttonName: 'BindPopupSample_six', buttonUrl: 'pages/common/BindPopupSample_six' });
        CommonButton({ buttonName: 'BindPopupSample_seven', buttonUrl: 'pages/common/BindPopupSample_seven' });
        CommonButton({ buttonName: 'BindPopupSample_eight', buttonUrl: 'pages/common/BindPopupSample_eight' });
        CommonButton({ buttonName: 'BindPopupSample_nine', buttonUrl: 'pages/common/BindPopupSample_nine' });
        CommonButton({ buttonName: 'BindSheetSample_one', buttonUrl: 'pages/common/BindSheetSample_one' });
        CommonButton({ buttonName: 'BindSheetSample_two', buttonUrl: 'pages/common/BindSheetSample_two' });
        CommonButton({ buttonName: 'BindSheetSample_three', buttonUrl: 'pages/common/BindSheetSample_three' });
        CommonButton({ buttonName: 'BorderRadiusSample', buttonUrl: 'pages/common/BorderRadiusSample' });
        CommonButton({ buttonName: 'BackGroundEffectSample', buttonUrl: 'pages/common/BackGroundEffectSample' });
        CommonButton({ buttonName: 'BackdropBlurSample', buttonUrl: 'pages/common/BackdropBlurSample' });
        CommonButton({ buttonName: 'BlurSample', buttonUrl: 'pages/common/BlurSample' });
        CommonButton({ buttonName: 'BrightnessSample', buttonUrl: 'pages/common/BrightnessSample' });
        CommonButton({ buttonName: 'BackgroundSample_one', buttonUrl: 'pages/common/BackgroundSample_one' });
        CommonButton({ buttonName: 'BackgroundSample_two', buttonUrl: 'pages/common/BackgroundSample_two' });
        CommonButton({ buttonName: 'BindContentCoverSample', buttonUrl: 'pages/common/BindContentCoverSample' });
        CommonButton({ buttonName: 'BindContextMenuSample_one', buttonUrl: 'pages/common/BindContextMenuSample_one' });
        CommonButton({ buttonName: 'BindContextMenuSample_two', buttonUrl: 'pages/common/BindContextMenuSample_two' });
        CommonButton({
          buttonName: 'BindContextMenuSample_three',
          buttonUrl: 'pages/common/BindContextMenuSample_three'
        });
        CommonButton({ buttonName: 'BindMenuSample', buttonUrl: 'pages/common/BindMenuSample' });
        CommonButton({ buttonName: 'BlendModeSample_one', buttonUrl: 'pages/common/BlendModeSample_one' });
        CommonButton({ buttonName: 'BlendModeSample_two', buttonUrl: 'pages/common/BlendModeSample_two' });
        CommonButton({ buttonName: 'BlendModeSample_three', buttonUrl: 'pages/common/BlendModeSample_three' });
        CommonButton({ buttonName: 'BlendModeSample_four', buttonUrl: 'pages/common/BlendModeSample_four' });
        CommonButton({ buttonName: 'BlendModeSample_five', buttonUrl: 'pages/common/BlendModeSample_five' });
        CommonButton({ buttonName: 'BackgroundImageSample', buttonUrl: 'pages/common/BackgroundImageSample' });
        CommonButton({ buttonName: 'BorderStyleSample', buttonUrl: 'pages/common/BorderStyleSample' });
        CommonButton({ buttonName: 'BorderColorSample_one', buttonUrl: 'pages/common/BorderColorSample_one' });
        CommonButton({ buttonName: 'BorderColorSample_two', buttonUrl: 'pages/common/BorderColorSample_two' });
        CommonButton({ buttonName: 'BorderImageSample_one', buttonUrl: 'pages/common/BorderImageSample_one' });
        CommonButton({ buttonName: 'BorderImageSample_two', buttonUrl: 'pages/common/BorderImageSample_two' });
        CommonButton({ buttonName: 'BorderImageSample_three', buttonUrl: 'pages/common/BorderImageSample_three' });
        CommonButton({ buttonName: 'BorderWidthSample', buttonUrl: 'pages/common/BorderWidthSample' });
        CommonButton({ buttonName: 'BackgroundColorSample', buttonUrl: 'pages/common/BackgroundColorSample' });
        CommonButton({ buttonName: 'BackgroundImageSizeSample', buttonUrl: 'pages/common/BackgroundImageSizeSample' });
        CommonButton({
          buttonName: 'BackgroundImagePositionSample',
          buttonUrl: 'pages/common/BackgroundImagePositionSample'
        });
        CommonButton({
          buttonName: 'BackgroundBlurStyleSample_one',
          buttonUrl: 'pages/common/BackgroundBlurStyleSample_one'
        });
        CommonButton({
          buttonName: 'BackgroundBlurStyleSample_two',
          buttonUrl: 'pages/common/BackgroundBlurStyleSample_two'
        });
        CommonButton({ buttonName: 'BorderSample', buttonUrl: 'pages/common/BorderSample' });
        CommonButton({ buttonName: 'ClickEffectSample', buttonUrl: 'pages/common/ClickEffectSample' });
        CommonButton({ buttonName: 'ColorBlendSample', buttonUrl: 'pages/common/ColorBlendSample' });
        CommonButton({ buttonName: 'ContrastSample', buttonUrl: 'pages/common/ContrastSample' });
        CommonButton({ buttonName: 'ConstraintSizeSample', buttonUrl: 'pages/common/ConstraintSizeSample' });
        CommonButton({ buttonName: 'ClipSample', buttonUrl: 'pages/common/ClipSample' });
        CommonButton({ buttonName: 'DefaultFocusSample', buttonUrl: 'pages/common/DefaultFocusSample' });
        CommonButton({ buttonName: 'DecorationSample', buttonUrl: 'pages/common/DecorationSample' });
        CommonButton({ buttonName: 'DirectionSample', buttonUrl: 'pages/common/DirectionSample' });
        CommonButton({ buttonName: 'DisplayPrioritySample', buttonUrl: 'pages/common/DisplayPrioritySample' });
        CommonButton({ buttonName: 'DraggableSample', buttonUrl: 'pages/common/DraggableSample' });
        CommonButton({ buttonName: 'DragPreviewSample', buttonUrl: 'pages/common/DragPreviewSample' });
        CommonButton({ buttonName: 'DragPreviewOptionsSample', buttonUrl: 'pages/common/DragPreviewOptionsSample' });
        CommonButton({ buttonName: 'EnabledSample', buttonUrl: 'pages/common/EnabledSample' });
        CommonButton({ buttonName: 'ExpandSafeAreaSample', buttonUrl: 'pages/common/ExpandSafeAreaSample' });
        CommonButton({ buttonName: 'FlexBasisSample', buttonUrl: 'pages/common/FlexBasisSample' });
        CommonButton({ buttonName: 'FontColorSample', buttonUrl: 'pages/common/FontColorSample' });
        CommonButton({ buttonName: 'FontSizeSample', buttonUrl: 'pages/common/FontSizeSample' });
        CommonButton({ buttonName: 'FontStyleSample', buttonUrl: 'pages/common/FontStyleSample' });
        CommonButton({ buttonName: 'FontWeightSample', buttonUrl: 'pages/common/FontWeightSample' });
        CommonButton({ buttonName: 'ForegroundColorSample', buttonUrl: 'pages/common/ForegroundColorSample' });
        CommonButton({ buttonName: 'FontFamilySample', buttonUrl: 'pages/common/FontFamilySample' });
        CommonButton({ buttonName: 'ForegroundBlurStyleSample', buttonUrl: 'pages/common/ForegroundBlurStyleSample' });
        CommonButton({ buttonName: 'FocusableSample', buttonUrl: 'pages/common/FocusableSample' });
        CommonButton({ buttonName: 'FocusOnTouchSample', buttonUrl: 'pages/common/FocusOnTouchSample' });
        CommonButton({ buttonName: 'FlexGrowSample', buttonUrl: 'pages/common/FlexGrowSample' });
        CommonButton({ buttonName: 'FlexShrinkSample', buttonUrl: 'pages/common/FlexShrinkSample' });
        CommonButton({ buttonName: 'GrayScaleSample', buttonUrl: 'pages/common/GrayScaleSample' });
        CommonButton({ buttonName: 'GeometryTransitionSample', buttonUrl: 'pages/common/GeometryTransitionSample' });
        CommonButton({ buttonName: 'GroupDefaultFocusSample', buttonUrl: 'pages/common/GroupDefaultFocusSample' });
        CommonButton({ buttonName: 'GridSpanSample', buttonUrl: 'pages/common/GridSpanSample' });
        CommonButton({ buttonName: 'GridOffsetSample', buttonUrl: 'pages/common/GridOffsetSample' });
        CommonButton({ buttonName: 'HitTestBehaviorSample', buttonUrl: 'pages/common/HitTestBehaviorSample' });
        CommonButton({ buttonName: 'HeightSample', buttonUrl: 'pages/common/HeightSample' });
        CommonButton({ buttonName: 'HoverEffectSample', buttonUrl: 'pages/common/HoverEffectSample' });
        CommonButton({ buttonName: 'HueRotateSample', buttonUrl: 'pages/common/HueRotateSample' });
        CommonButton({ buttonName: 'InvertSample', buttonUrl: 'pages/common/InvertSample' });
        CommonButton({ buttonName: 'IdSample', buttonUrl: 'pages/common/IdSample' });
        CommonButton({ buttonName: 'KeyboardShortcutSample', buttonUrl: 'pages/common/KeyboardShortcutSample' });
        CommonButton({ buttonName: 'LineHeightSample', buttonUrl: 'pages/common/LineHeightSample' });
        CommonButton({ buttonName: 'LinearGradientBlurSample', buttonUrl: 'pages/common/LinearGradientBlurSample' });
        CommonButton({ buttonName: 'LightUpEffectSample', buttonUrl: 'pages/common/LightUpEffectSample' });
        CommonButton({ buttonName: 'LayoutWeightSample', buttonUrl: 'pages/common/LayoutWeightSample' });
        CommonButton({ buttonName: 'LinearGradientSample_one', buttonUrl: 'pages/common/LinearGradientSample_one' });
        CommonButton({ buttonName: 'LinearGradientSample_two', buttonUrl: 'pages/common/LinearGradientSample_two' });
        CommonButton({ buttonName: 'MotionPathSample', buttonUrl: 'pages/common/MotionPathSample' });
        CommonButton({ buttonName: 'MonopolizeEventsSample', buttonUrl: 'pages/common/MonopolizeEventsSample' });
        CommonButton({ buttonName: 'MarginSample_one', buttonUrl: 'pages/common/MarginSample_one' });
        CommonButton({ buttonName: 'MarginSample_two', buttonUrl: 'pages/common/MarginSample_two' });
        CommonButton({ buttonName: 'MarkAnchorSample', buttonUrl: 'pages/common/MarkAnchorSample' });
        CommonButton({ buttonName: 'MaskSample', buttonUrl: 'pages/common/MaskSample' });
        CommonButton({ buttonName: 'OverlaySample', buttonUrl: 'pages/common/OverlaySample' });
        CommonButton({ buttonName: 'OffsetSample', buttonUrl: 'pages/common/OffsetSample' });
        CommonButton({ buttonName: 'OutlineSample_one', buttonUrl: 'pages/common/OutlineSample_one' });
        CommonButton({ buttonName: 'OutlineSample_two', buttonUrl: 'pages/common/OutlineSample_two' });
        CommonButton({ buttonName: 'OpacitySample', buttonUrl: 'pages/common/OpacitySample' });
        CommonButton({ buttonName: 'OutlineStyleSample_one', buttonUrl: 'pages/common/OutlineStyleSample_one' });
        CommonButton({ buttonName: 'OutlineStyleSample_two', buttonUrl: 'pages/common/OutlineStyleSample_two' });
        CommonButton({ buttonName: 'OutlineWidthSample', buttonUrl: 'pages/common/OutlineWidthSample' });
        CommonButton({ buttonName: 'OutlineColorSample_one', buttonUrl: 'pages/common/OutlineColorSample_one' });
        CommonButton({ buttonName: 'OutlineColorSample_two', buttonUrl: 'pages/common/OutlineColorSample_two' });
        CommonButton({ buttonName: 'OutlineRadiusSample', buttonUrl: 'pages/common/OutlineRadiusSample' });
        CommonButton({ buttonName: 'ObscuredSample', buttonUrl: 'pages/common/ObscuredSample' });
        CommonButton({ buttonName: 'PositionSample', buttonUrl: 'pages/common/PositionSample' });
        CommonButton({ buttonName: 'PixelStretchEffectSample', buttonUrl: 'pages/common/PixelStretchEffectSample' });
        CommonButton({ buttonName: 'PixelRoundSample', buttonUrl: 'pages/common/PixelRoundSample' });
        CommonButton({ buttonName: 'ProgressMaskSample', buttonUrl: 'pages/common/ProgressMaskSample' });
        CommonButton({ buttonName: 'PaddingSample', buttonUrl: 'pages/common/PaddingSample' });
        CommonButton({ buttonName: 'ResponseRegionSample', buttonUrl: 'pages/common/ResponseRegionSample' });
        CommonButton({ buttonName: 'RequestFocusSample', buttonUrl: 'pages/common/RequestFocusSample' });
        CommonButton({ buttonName: 'ReuseIdSample', buttonUrl: 'pages/common/ReuseIdSample' });
        CommonButton({ buttonName: 'RenderFitSample_one', buttonUrl: 'pages/common/RenderFitSample_one' });
        CommonButton({ buttonName: 'RenderFitSample_two', buttonUrl: 'pages/common/RenderFitSample_two' });
        CommonButton({ buttonName: 'RotateSample', buttonUrl: 'pages/common/RotateSample' });
        CommonButton({ buttonName: 'RenderFitSample_three', buttonUrl: 'pages/common/RenderFitSample_three' });
        CommonButton({ buttonName: 'RadialGradientSample_one', buttonUrl: 'pages/common/RadialGradientSample_one' });
        CommonButton({ buttonName: 'RestoreIdSample', buttonUrl: 'pages/common/RestoreIdSample' });
        CommonButton({ buttonName: 'RenderGroupSample', buttonUrl: 'pages/common/RenderGroupSample' });
        CommonButton({ buttonName: 'RadialGradientSample_two', buttonUrl: 'pages/common/RadialGradientSample_two' });
        CommonButton({ buttonName: 'SweepGradientSample', buttonUrl: 'pages/common/SweepGradientSample' });
        CommonButton({ buttonName: 'ShadowSample_one', buttonUrl: 'pages/common/ShadowSample_one' });
        CommonButton({ buttonName: 'ScaleSample', buttonUrl: 'pages/common/ScaleSample' });
        CommonButton({ buttonName: 'ShadowSample_two', buttonUrl: 'pages/common/ShadowSample_two' });
        CommonButton({ buttonName: 'SharedTransitionSample', buttonUrl: 'pages/common/SharedTransitionSample' });
        CommonButton({ buttonName: 'SepiaSample', buttonUrl: 'pages/common/SepiaSample' });
        CommonButton({
          buttonName: 'SetKeyboardAvoidModeSample',
          buttonUrl: 'pages/common/SetKeyboardAvoidModeSample'
        });
        CommonButton({ buttonName: 'StateStylesSample', buttonUrl: 'pages/common/StateStylesSample' });
        CommonButton({ buttonName: 'SaturateSample', buttonUrl: 'pages/common/SaturateSample' });
        CommonButton({ buttonName: 'SetCursorSample_one', buttonUrl: 'pages/common/SetCursorSample_one' });
        CommonButton({ buttonName: 'SetCursorSample_two', buttonUrl: 'pages/common/SetCursorSample_two' });
        CommonButton({ buttonName: 'SetCursorSample_three', buttonUrl: 'pages/common/SetCursorSample_three' });
        CommonButton({ buttonName: 'SetCursorSample_four', buttonUrl: 'pages/common/SetCursorSample_four' });
        CommonButton({ buttonName: 'SetCursorSample_five', buttonUrl: 'pages/common/SetCursorSample_five' });
        CommonButton({ buttonName: 'SetCursorSample_six', buttonUrl: 'pages/common/SetCursorSample_six' });
        CommonButton({ buttonName: 'SetCursorSample_seven', buttonUrl: 'pages/common/SetCursorSample_seven' });
        CommonButton({ buttonName: 'SetCursorSample_eight', buttonUrl: 'pages/common/SetCursorSample_eight' });
        CommonButton({ buttonName: 'SphericalEffectSample', buttonUrl: 'pages/common/SphericalEffectSample' });
        CommonButton({ buttonName: 'SizeSample', buttonUrl: 'pages/common/SizeSample' });
        CommonButton({ buttonName: 'TranslateSample', buttonUrl: 'pages/common/TranslateSample' });
        CommonButton({ buttonName: 'TabIndexSample', buttonUrl: 'pages/common/TabIndexSample' });
        CommonButton({ buttonName: 'TransFormSample', buttonUrl: 'pages/common/TransFormSample' });
        CommonButton({ buttonName: 'TransitionSample_one', buttonUrl: 'pages/common/TransitionSample_one' });
        CommonButton({ buttonName: 'TransitionSample_two', buttonUrl: 'pages/common/TransitionSample_two' });
        CommonButton({ buttonName: 'UpdateColorSample', buttonUrl: 'pages/common/UpdateColorSample' });
        CommonButton({ buttonName: 'UpdateProgressSample', buttonUrl: 'pages/common/UpdateProgressSample' });
        CommonButton({ buttonName: 'UseShadowBatchingSample', buttonUrl: 'pages/common/UseShadowBatchingSample' });
        CommonButton({ buttonName: 'UseEffectSample', buttonUrl: 'pages/common/UseEffectSample' });
        CommonButton({ buttonName: 'VisibilitySample', buttonUrl: 'pages/common/VisibilitySample' });
        CommonButton({ buttonName: 'WidthSample', buttonUrl: 'pages/common/WidthSample' });
        CommonButton({ buttonName: 'ZIndexSample', buttonUrl: 'pages/common/ZIndexSample' });
      }
      .padding('5vp')
      .width('100%')
    }.margin({ bottom: 60 })
    .width('100%')
  }
}