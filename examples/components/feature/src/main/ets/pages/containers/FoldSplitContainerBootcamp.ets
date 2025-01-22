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

import { Drawer } from 'common/src/main/ets/components/Drawer';
import { RadioBlock, ColorBlock, SliderBlock, useEnabled, useEnabledNumber } from 'common';
import { FoldSplitContainer, PresetSplitRatio, ExtraRegionPosition, matrix4, LengthMetrics,
  ColorMetrics,
  promptAction} from '@kit.ArkUI';
import { pointer } from '@kit.InputKit';
import { BlockTag } from 'common/src/main/ets/model/BlockTag';
import { formatDate } from 'common/src/main/ets/utils/timeUtil';
import { common2D, uiEffect } from '@kit.ArkGraphics2D';
import { CompSizeBlocks } from '../../components/CompSizeBlocks';
import { CompLocationBlocks } from '../../components/CompLocationBlocks';
import { CompLayoutConstraintsBlocks } from '../../components/CompLayoutConstraintsBlocks';
import { CompBorderBlocks } from '../../components/CompBorderBlocks';
import { CompBorderImageBlocks } from '../../components/CompBorderImageBlocks';
import { CompOpacityBlocks } from '../../components/CompOpacityBlocks';
import { CompVisibilityBlocks } from '../../components/CompVisibilityBlocks';
import { CompEnabledBlocks } from '../../components/CompEnabledBlocks';
import { CompOverlayBlocks } from '../../components/CompOverlayBlocks';
import { CompZOrderControlBlocks } from '../../components/CompZOrderControlBlocks';
import { CompTransformationBlocks } from '../../components/CompTransformationBlocks';
import { CompGradientColorBlocks } from '../../components/CompGradientColorBlocks';
import { CompPopupControlBlocks } from '../../components/CompBindPopupBlocks';
import { CompMenuControlBlocks } from '../../components/CompMenuControlBlocks';
import { CompFocusControlBlocks } from '../../components/CompFocusControlBlocks';
import { CompHoverEffectBlocks } from '../../components/CompHoverEffectBlocks';
import { CompComponentIDBlocks } from '../../components/CompComponentIDBlocks';
import { CompReuseIDBlocks } from '../../components/CompReuseIDBlocks';
import { CompRestoreIdBlocks } from '../../components/CompRestoreIdBlocks';
import { CompForegroundEffectBlocks } from '../../components/CompForegroundEffectBlocks';
import { CompForegroundBlurBlocks } from '../../components/CompForegroundBlurBlocks';
import { CompClickEffectBlocks } from '../../components/CompClickEffectBlocks';
import { CompAccessibilityBlocks } from '../../components/CompAccessibilityBlocks';
import { CompTouchTargetBlocks } from '../../components/CompTouchTargetBlocks';
import { CompHitTestControlBlocks } from '../../components/CompHitTestControlBlocks';
import { CompModalTransitionBlocks } from '../../components/CompModalTransitionBlocks';
import { CompSheetTransitionBlocks } from '../../components/CompSheetTransitionBlocks';
import { CompObscuringBlocks } from '../../components/CompObscuringBlocks';
import { CompEventMonopolizationBlocks } from '../../components/CompEventMonopolizationBlocks';
import { CompCursorControlBlocks } from '../../components/CompCursorControlBlocks';

@Component
export struct FoldSplitContainerBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State enableExpandedLayoutOptionsIsExtraRegionPerpendicular: boolean = false;
  @State expandedLayoutOptionsIsExtraRegionPerpendicular: boolean = true;
  @State enableExpandedLayoutOptionsVerticalSplitRatio: boolean = false;
  @State expandedLayoutOptionsVerticalSplitRatio: number = PresetSplitRatio.LAYOUT_1V1;
  @State enableExpandedLayoutOptionsHorizontalSplitRatio: boolean = false;
  @State expandedLayoutOptionsHorizontalSplitRatio: number = PresetSplitRatio.LAYOUT_3V2;
  @State enableExpandedLayoutOptionsExtraRegionPosition: boolean = false;
  @State expandedLayoutOptionsExtraRegionPosition: ExtraRegionPosition = ExtraRegionPosition.TOP;
  @State enableHoverModeLayoutOptionsShowExtraRegion: boolean = false;
  @State hoverModeLayoutOptionsShowExtraRegion: boolean = false;
  @State enableHoverModeLayoutOptionsHorizontalSplitRatio: boolean = false;
  @State hoverModeLayoutOptionsHorizontalSplitRatio: number = PresetSplitRatio.LAYOUT_3V2;
  @State enableHoverModeLayoutOptionsExtraRegionPosition: boolean = false;
  @State hoverModeLayoutOptionsExtraRegionPosition: ExtraRegionPosition = ExtraRegionPosition.TOP;
  @State enableFoldedLayoutOptionsVerticalSplitRatio: boolean = false;
  @State foldedLayoutOptionsVerticalSplitRatio: number = PresetSplitRatio.LAYOUT_1V1;
  @State enableAnimationOptionsDuration: boolean = false;
  @State animationOptionsDuration: number = 1000;
  @State enableAnimationOptionsTempo: boolean = false;
  @State animationOptionsTempo: number = 1.0;
  @State enableAnimationOptionsCurve: boolean = false;
  @State animationOptionsCurve: Curve = Curve.EaseInOut;
  @State enableAnimationOptionsDelay: boolean = false;
  @State animationOptionsDelay: number = 0;
  @State enableAnimationOptionsIterations: boolean = false;
  @State animationOptionsIterations: number = 1;
  @State enableAnimationOptionsPlayMode: boolean = false;
  @State animationOptionsPlayMode: PlayMode = PlayMode.Normal;
  @State enableAnimationOptionsFinishCallbackType: boolean = false;
  @State animationOptionsFinishCallbackType: FinishCallbackType = FinishCallbackType.REMOVED;
  @State enableAnimationOptionsExpectedFrameRateRangeMin: boolean = false;
  @State animationOptionsExpectedFrameRateRangeMin: number = 10;
  @State enableAnimationOptionsExpectedFrameRateRangeMax: boolean = false;
  @State animationOptionsExpectedFrameRateRangeMax: number = 120;
  @State enableAnimationOptionsExpectedFrameRateRangeExpected: boolean = false;
  @State animationOptionsExpectedFrameRateRangeExpected: number = 60;
  @State enableCompFlexBasis: boolean = false;
  @State compFlexBasis: number | string = 'auto';
  @State enableCompDirection: boolean = false;
  @State compDirection: Direction = Direction.Auto;
  // size
  @State enableCompWidth: boolean = false;
  @State compWidth: Length = 300;
  @State enableCompHeight: boolean = false;
  @State compHeight: Length = 300;
  @State enableCompPadding: boolean = false;
  @State compPadding: Padding | Length | LocalizedPadding = 0;
  @State enableCompMargin: boolean = false;
  @State compMargin: Margin | Length | LocalizedPadding = 0;
  @State enableCompConstraintSize: boolean = false;
  @State enableCompConstraintSizeMinWidth: boolean = false;
  @State compConstraintSizeMinWidth: Length = 0;
  @State enableCompConstraintSizeMinHeight: boolean = false;
  @State compConstraintSizeMinHeight: Length = 0;
  @State enableCompConstraintSizeMaxWidth: boolean = false;
  @State compConstraintSizeMaxWidth: Length = Infinity;
  @State enableCompConstraintSizeMaxHeight: boolean = false;
  @State compConstraintSizeMaxHeight: Length = Infinity;
  // location
  @State enableCompPosition: boolean = false;
  @State enableCompPositionTop: boolean = false;
  @State compPositionTop: Dimension = 0;
  @State enableCompPositionBottom: boolean = false;
  @State compPositionBottom: Dimension = 0;
  @State enableCompPositionLeft: boolean = false;
  @State compPositionLeft: Dimension = 0;
  @State enableCompPositionRight: boolean = false;
  @State compPositionRight: Dimension = 0;
  @State enableCompMarkAnchor: boolean = false;
  @State enableCompMarkAnchorX: boolean = false;
  @State compMarkAnchorX: Length = 0;
  @State enableCompMarkAnchorY: boolean = false;
  @State compMarkAnchorY: Length = 0;
  @State enableCompOffset: boolean = false;
  @State enableCompOffsetX: boolean = false;
  @State compOffsetX: Length = 0;
  @State enableCompOffsetY: boolean = false;
  @State compOffsetY: Length = 0;
  // aspectRatio
  @State enableCompAspectRatio: boolean = false;
  @State compAspectRatio: number = 1;
  @State enableCompPixelRound: boolean = false;
  @State enableCompPixelRoundStart: boolean = false;
  @State compPixelRoundStart: PixelRoundCalcPolicy = PixelRoundCalcPolicy.NO_FORCE_ROUND;
  @State enableCompPixelRoundTop: boolean = false;
  @State compPixelRoundTop: PixelRoundCalcPolicy = PixelRoundCalcPolicy.NO_FORCE_ROUND;
  @State enableCompPixelRoundEnd: boolean = false;
  @State compPixelRoundEnd: PixelRoundCalcPolicy = PixelRoundCalcPolicy.NO_FORCE_ROUND;
  @State enableCompPixelRoundBottom: boolean = false;
  @State compPixelRoundBottom: PixelRoundCalcPolicy = PixelRoundCalcPolicy.NO_FORCE_ROUND;
  // border
  @State enableCompBorderWidth: boolean = false;
  @State compBorderWidth: Length = 0;
  @State enableCompBorderColor: boolean = false;
  @State compBorderColor: ResourceColor = Color.Black
  @State enableCompBorderRadius: boolean = false;
  @State compBorderRadius: Length = 0;
  @State enableCompBorderStyle: boolean = false;
  @State compBorderStyle: BorderStyle = BorderStyle.Solid
  @State enableCompBorderDashGapLeft: boolean = false;
  @State compBorderDashGapLeft: number = 0;
  @State enableCompBorderDashGapRight: boolean = false;
  @State compBorderDashGapRight: number = 0;
  @State enableCompBorderDashGapTop: boolean = false;
  @State compBorderDashGapTop: number = 0;
  @State enableCompBorderDashGapBottom: boolean = false;
  @State compBorderDashGapBottom: number = 0;
  @State enableCompBorderDashWidthLeft: boolean = false;
  @State compBorderDashWidthLeft: number = 0;
  @State enableCompBorderDashWidthRight: boolean = false;
  @State compBorderDashWidthRight: number = 0;
  @State enableCompBorderDashWidthTop: boolean = false;
  @State compBorderDashWidthTop: number = 0;
  @State enableCompBorderDashWidthBottom: boolean = false;
  @State compBorderDashWidthBottom: number = 0;
  // borderImage
  @State enableCompBorderImage: boolean = false;
  @State enableCompBorderImageSource: boolean = false;
  @State enableCompBorderImageSlice: boolean = false;
  @State enableCompBorderImageSliceTop: boolean = false;
  @State compBorderImageSliceTop: Length = 0;
  @State enableCompBorderImageSliceBottom: boolean = false;
  @State compBorderImageSliceBottom: Length = 0;
  @State enableCompBorderImageSliceLeft: boolean = false;
  @State compBorderImageSliceLeft: Length = 0;
  @State enableCompBorderImageSliceRight: boolean = false;
  @State compBorderImageSliceRight: Length = 0;
  @State enableCompBorderImageWidth: boolean = false;
  @State enableCompBorderImageWidthTop: boolean = false;
  @State compBorderImageWidthTop: Length = 0;
  @State enableCompBorderImageWidthBottom: boolean = false;
  @State compBorderImageWidthBottom: Length = 0;
  @State enableCompBorderImageWidthLeft: boolean = false;
  @State compBorderImageWidthLeft: Length = 0;
  @State enableCompBorderImageWidthRight: boolean = false;
  @State compBorderImageWidthRight: Length = 0;
  @State enableCompBorderImageOutset: boolean = false;
  @State enableCompBorderImageOutsetTop: boolean = false;
  @State compBorderImageOutsetTop: Length = 0;
  @State enableCompBorderImageOutsetBottom: boolean = false;
  @State compBorderImageOutsetBottom: Length = 0;
  @State enableCompBorderImageOutsetLeft: boolean = false;
  @State compBorderImageOutsetLeft: Length = 0;
  @State enableCompBorderImageOutsetRight: boolean = false;
  @State compBorderImageOutsetRight: Length = 0;
  @State enableCompBorderImageRepeat: boolean = false;
  @State compBorderImageRepeat: RepeatMode = RepeatMode.Stretch
  @State enableCompBorderImageFill: boolean = false;
  @State compBorderImageFill: boolean = false;
  // background
  @State enableCompBackgroundAlign: boolean = false;
  @State compBackgroundAlign: Alignment = Alignment.Center;
  @State enableCompBackgroundColor: boolean = false;
  @State compBackgroundColor: ResourceColor = Color.Transparent;
  @State enableCompBackgroundImageSrc: boolean = false;
  @State enableCompBackgroundImageRepeat: boolean = false;
  @State compBackgroundImageRepeat: ImageRepeat = ImageRepeat.NoRepeat;
  @State enableCompBackgroundImageSize: boolean = false;
  @State compBackgroundImageSize: ImageSize = ImageSize.Auto;
  @State enableCompBackgroundImagePositionX: boolean = false;
  @State compBackgroundImagePositionX: Length = 0;
  @State enableCompBackgroundImagePositionY: boolean = false;
  @State compBackgroundImagePositionY: Length = 0;
  @State enableCompBackgroundBlurStyle: boolean = false;
  @State compBackgroundBlurStyle: BlurStyle = BlurStyle.NONE;
  @State enableCompBackgroundBlurStyleParams: boolean = false;
  @State enableCompBackgroundBlurStyleParamsColorMode: boolean = false;
  @State compBackgroundBlurStyleParamsColorMode: ThemeColorMode = ThemeColorMode.SYSTEM;
  @State enableCompBackgroundBlurStyleParamsAdaptiveColor: boolean = false;
  @State compBackgroundBlurStyleParamsAdaptiveColor: AdaptiveColor = AdaptiveColor.DEFAULT;
  @State enableCompBackgroundBlurStyleParamsBlurOptionsLeft: boolean = false;
  @State compBackgroundBlurStyleParamsBlurOptionsLeft: number = 0;
  @State enableCompBackgroundBlurStyleParamsBlurOptionsRight: boolean = false;
  @State compBackgroundBlurStyleParamsBlurOptionsRight: number = 0;
  @State enableCompBackgroundBlurStyleParamsScale: boolean = false;
  @State compBackgroundBlurStyleParamsScale: number = 1;
  @State enableCompBackdropBlur: boolean = false;
  @State compBackdropBlur: number = 0;
  @State enableCompBackdropBlurGrayscale: boolean = false;
  @State enableCompBackdropBlurGrayscaleLeft: boolean = false;
  @State compBackdropBlurGrayscaleLeft: number = 0;
  @State enableCompBackdropBlurGrayscaleRight: boolean = false;
  @State compBackdropBlurGrayscaleRight: number = 0;
  @State enableCompBackgroundEffect: boolean = false;
  @State enableCompBackgroundEffectRadius: boolean = false;
  @State compBackgroundEffectRadius: number = 0;
  @State enableCompBackgroundEffectSaturation: boolean = false;
  @State compBackgroundEffectSaturation: number = 1;
  @State enableCompBackgroundEffectBrightness: boolean = false;
  @State compBackgroundEffectBrightness: number = 1;
  @State enableCompBackgroundEffectColor: boolean = false;
  @State compBackgroundEffectColor: ResourceColor = Color.Transparent;
  @State enableCompBackgroundEffectAdaptiveColor: boolean = false;
  @State compBackgroundEffectAdaptiveColor: AdaptiveColor = AdaptiveColor.DEFAULT;
  @State enableCompBackgroundEffectBlurOptionsGrayscaleLeft: boolean = false;
  @State compBackgroundEffectBlurOptionsGrayscaleLeft: number = 0;
  @State enableCompBackgroundEffectBlurOptionsGrayscaleRight: boolean = false;
  @State compBackgroundEffectBlurOptionsGrayscaleRight: number = 0;
  @State enableCompBackgroundImageResizable: boolean = false;
  @State enableCompBackgroundImageResizableSliceTop: boolean = false;
  @State compBackgroundImageResizableSliceTop: Length = 0;
  @State enableCompBackgroundImageResizableSliceBottom: boolean = false;
  @State compBackgroundImageResizableSliceBottom: Length = 0;
  @State enableCompBackgroundImageResizableSliceLeft: boolean = false;
  @State compBackgroundImageResizableSliceLeft: Length = 0;
  @State enableCompBackgroundImageResizableSliceRight: boolean = false;
  @State compBackgroundImageResizableSliceRight: Length = 0;
  @State enableCompBackgroundImageResizableLattice: boolean = false;
  @State enableCompBackgroundImageResizableLatticeXDivs: boolean = false;
  @State compBackgroundImageResizableLatticeXDivs: Array<number> = [];
  @State enableCompBackgroundImageResizableLatticeYDivs: boolean = false;
  @State compBackgroundImageResizableLatticeYDivs: Array<number> = [];
  @State enableCompBackgroundImageResizableLatticeFXCount: boolean = false;
  @State compBackgroundImageResizableLatticeFXCount: number = 0;
  @State enableCompBackgroundImageResizableLatticeFYCount: boolean = false;
  @State compBackgroundImageResizableLatticeFYCount: number = 0;
  @State enableCompBackgroundImageResizableLatticeFBounds: boolean = false;
  @State enableCompBackgroundImageResizableLatticeFBoundsLeft: boolean = false;
  @State compBackgroundImageResizableLatticeFBoundsLeft: number = 0;
  @State enableCompBackgroundImageResizableLatticeFBoundsTop: boolean = false;
  @State compBackgroundImageResizableLatticeFBoundsTop: number = 0;
  @State enableCompBackgroundImageResizableLatticeFBoundsRight: boolean = false;
  @State compBackgroundImageResizableLatticeFBoundsRight: number = 0;
  @State enableCompBackgroundImageResizableLatticeFBoundsBottom: boolean = false;
  @State compBackgroundImageResizableLatticeFBoundsBottom: number = 0;
  @State enableCompBackgroundImageResizableLatticeFColors: boolean = false;
  @State compBackgroundImageResizableLatticeFColors: Array<common2D.Color> | null = null;
  // opacity
  @State enableCompOpacity: boolean = false;
  @State compOpacity: number = 1;
  // visibility
  @State enableCompVisibility: boolean = false;
  @State compVisibility: Visibility = Visibility.Visible;
  // enabled:
  @State enableCompEnabled: boolean = false;
  @State compEnabled: boolean = false;
  // overlay
  @State enableCompOverlay: boolean = false;
  @State compOverlay: string = 'overlay';
  @State enableCompOverlayOptions: boolean = false;
  @State enableCompOverlayOptionsAlign: boolean = false;
  @State compOverlayOptionsAlign: Alignment = Alignment.TopStart;
  @State enableCompOverlayOptionsOffsetX: boolean = false;
  @State compOverlayOptionsOffsetX: number = 0;
  @State enableCompOverlayOptionsOffsetY: boolean = false;
  @State compOverlayOptionsOffsetY: number = 0;
  // zIndex
  @State enableCompZIndex: boolean = false;
  @State compZIndex: number = 0;
  // transformation
  @State enableCompRotate: boolean = false;
  @State enableCompRotateX: boolean = false;
  @State compRotateX: number = 0;
  @State enableCompRotateY: boolean = false;
  @State compRotateY: number = 0;
  @State enableCompRotateZ: boolean = false;
  @State compRotateZ: number = 0;
  @State enableCompRotateAngle: boolean = false;
  @State compRotateAngle: number = 0;
  @State enableCompRotateCenterX: boolean = false;
  @State compRotateCenterX: number = 0;
  @State enableCompRotateCenterY: boolean = false;
  @State compRotateCenterY: number = 0;
  @State enableCompRotateCenterZ: boolean = false;
  @State compRotateCenterZ: number = 0;
  @State enableCompRotatePerspective: boolean = false;
  @State compRotatePerspective: number = 0;
  @State enableCompTranslate: boolean = false;
  @State enableCompTranslateX: boolean = false;
  @State compTranslateX: number = 0;
  @State enableCompTranslateY: boolean = false;
  @State compTranslateY: number = 0;
  @State enableCompTranslateZ: boolean = false;
  @State compTranslateZ: number = 0;
  @State enableCompScale: boolean = false;
  @State enableCompScaleX: boolean = false;
  @State compScaleX: number = 1;
  @State enableCompScaleY: boolean = false;
  @State compScaleY: number = 1;
  @State enableCompScaleZ: boolean = false;
  @State compScaleZ: number = 1;
  @State enableCompScaleCenterX: boolean = false;
  @State compScaleCenterX: number = 0;
  @State enableCompScaleCenterY: boolean = false;
  @State compScaleCenterY: number = 0;
  @State enableCompTransform: boolean = false;
  // shapeClippingBlocks
  @State enableCompClip: boolean = false;
  @State compClip: boolean = false;
  @State enableCompMask: boolean = false;
  @State enableCompMaskValue: boolean = false;
  @State @Watch('compMaskValueChange') compMaskValue: number = 0;
  @State enableCompMaskColor: boolean = false;
  @State @Watch('compMaskColorChange') compMaskColor: number = Color.Transparent;
  @State progress: ProgressMask = new ProgressMask(0, 100, Color.Transparent);
  // imageEffects
  @State enableCompBlurValue: boolean = false
  @State compBlurValue: number = 0
  @State enableCompBlurOptionsNumber1: boolean = false
  @State compBlurOptionsNumber1: number = 0
  @State enableCompBlurOptionsNumber2: boolean = false
  @State compBlurOptionsNumber2: number = 0
  @State enableCompShadowValueRadius: boolean = false
  @State compShadowValueRadius: number = 0
  @State enableCompShadowValueType: boolean = false
  @State compShadowValueType: ShadowType = ShadowType.COLOR
  @State enableCompShadowValueColor: boolean = false
  @State compShadowValueColor: ResourceColor = Color.Black
  @State enableCompShadowValueOffsetX: boolean = false
  @State compShadowValueOffsetX: number = 0
  @State enableCompShadowValueOffsetY: boolean = false
  @State compShadowValueOffsetY: number = 0
  @State enableCompShadowValueFill: boolean = false
  @State compShadowValueFill: boolean = false
  @State enableCompGrayscale: boolean = false
  @State compGrayscale: number = 0.0
  @State enableCompBrightness: boolean = false
  @State compBrightness: number = 1.0
  @State enableCompSaturate: boolean = false
  @State compSaturate: number = 1.0
  @State enableCompContrast: boolean = false
  @State compContrast: number = 1.0
  @State enableCompInvert: boolean = false
  @State compInvert: number = 1.0
  @State enableCompSepia: boolean = false
  @State compSepia: number = 0
  @State enableCompHueRotate: boolean = false
  @State compHueRotate: number = 0
  @State enableCompColorBlend: boolean = false
  @State compColorBlend: ResourceColor | undefined = undefined
  //Gradient Color
  //linearGradient
  @State enableCompLinearGradientAngle: boolean = false;
  @State compLinearGradientAngle: number = 180;
  @State enableCompLinearGradientDirection: boolean = false;
  @State compLinearGradientDirection: GradientDirection = GradientDirection.Bottom;
  @State enableCompLinearGradientColors1: boolean = false;
  @State compLinearGradientColors1: ResourceStr = '#ff000000';
  @State enableCompLinearGradientColorsNumber1: boolean = false;
  @State compLinearGradientColorsNumber1: number = 0;
  @State enableCompLinearGradientColors2: boolean = false;
  @State compLinearGradientColors2: ResourceStr = '#ff000000';
  @State enableCompLinearGradientColorsNumber2: boolean = false;
  @State compLinearGradientColorsNumber2: number = 0;
  @State enableCompLinearGradientRepeating: boolean = false;
  @State compLinearGradientRepeating: boolean = false;
  //Popup Control
  //bindPopup
  @State enableCompBindPopupType: boolean = true;
  @State compBindPopupType: boolean = true;
  @State handlePopup: boolean = false;
  @State enableCompPopupType: boolean = true;
  @State compPopupType: number = 0;
  @State enableCompBindPopupArrowOffset: boolean = false;
  @State compBindPopupArrowOffset: number = 0;
  @State enableCompBindPopupShowInSubWindow: boolean = false;
  @State compBindPopupShowInSubWindow: boolean = true;
  @State enableCompBindPopupMaskType: boolean = false;
  @State compBindPopupMaskType: boolean = true;
  @State enableCompBindPopupMaskBoolean: boolean = false;
  @State compBindPopupMaskBoolean: boolean = true;
  @State enableCompBindPopupMaskColor: boolean = false;
  @State compBindPopupMaskColor: ResourceStr = '#ff000000';
  @State enableCompBindPopupMessageOptionsTextColor: boolean = false;
  @State compBindPopupMessageOptionsTextColor: ResourceStr = '#ff000000';
  @State enableCompBindPopupMessageOptionsFontSize: boolean = false;
  @State compBindPopupMessageOptionsFontSize: number = 16;
  @State enableCompBindPopupMessageOptionsFontWeight: boolean = false;
  @State compBindPopupMessageOptionsFontWeight: FontWeight = FontWeight.Normal;
  @State enableCompBindPopupMessageOptionsFontStyle: boolean = false;
  @State compBindPopupMessageOptionsFontStyle: FontStyle = FontStyle.Normal;
  @State enableCompBindPopupTargetSpace: boolean = false;
  @State compBindPopupTargetSpace: number = 0;
  @State enableCompBindPopupPlacement: boolean = false;
  @State compBindPopupPlacement: Placement = Placement.Bottom;
  @State enableCompBindPopupOffsetX: boolean = false;
  @State compBindPopupOffsetX: number = 0;
  @State enableCompBindPopupOffsetY: boolean = false;
  @State compBindPopupOffsetY: number = 0;
  @State enableCompBindPopupEnableArrow: boolean = false;
  @State compBindPopupEnableArrow: boolean = true;
  @State enableCompBindPopupPopupColor: boolean = false;
  @State compBindPopupPopupColor: ResourceStr = '#ff000000';
  @State enableCompBindPopupAutoCancel: boolean = false;
  @State compBindPopupAutoCancel: boolean = false;
  @State enableCompBindPopupWidth: boolean = false;
  @State compBindPopupWidth: number = 0;
  @State enableCompBindPopupArrowPointPosition: boolean = false;
  @State compBindPopupArrowPointPosition: ArrowPointPosition = ArrowPointPosition.CENTER;
  @State enableCompBindPopupArrowWidth: boolean = false;
  @State compBindPopupArrowWidth: number = 16;
  @State enableCompBindPopupArrowHeight: boolean = false;
  @State compBindPopupArrowHeight: number = 8;
  @State enableCompBindPopupRadius: boolean = false;
  @State compBindPopupRadius: number = 20;
  @State enableCompBindPopupShadowType: boolean = false;
  @State compBindPopupShadowType: boolean = true;
  @State enableCompBindPopupShadowStyle: boolean = false;
  @State compBindPopupShadowStyle: ShadowStyle = ShadowStyle.OUTER_DEFAULT_MD;
  @State enableCompBindPopupShadowOptionsRadius: boolean = false;
  @State compBindPopupShadowOptionsRadius: number = 0;
  @State enableCompBindPopupShadowOptionsType: boolean = false;
  @State compBindPopupShadowOptionsType: ShadowType = ShadowType.COLOR;
  @State enableCompBindPopupShadowOptionsColor: boolean = false;
  @State compBindPopupShadowOptionsColor: ResourceColor = '#ff000000';
  @State enableCompBindPopupShadowOptionsOffsetX: boolean = false;
  @State compBindPopupShadowOptionsOffsetX: number = 0;
  @State enableCompBindPopupShadowOptionsOffsetY: boolean = false;
  @State compBindPopupShadowOptionsOffsetY: number = 0;
  @State enableCompBindPopupShadowOptionsFill: boolean = false;
  @State compBindPopupShadowOptionsFill: boolean = false;
  @State enableCompBindPopupBackgroundBlurStyle: boolean = false;
  @State compBindPopupBackgroundBlurStyle: BlurStyle = BlurStyle.COMPONENT_ULTRA_THICK;
  @State enableTransitionTransitionEffect: boolean = false;
  @State transitionTransitionEffect: TransitionEffect = TransitionEffect.IDENTITY;
  @State enableCompBindPopupTransitionOpacity: boolean = false;
  @State compBindPopupTransitionOpacity: number = 0;
  @State enableCompBindPopupTransitionTranslateX: boolean = false;
  @State compBindPopupTransitionTranslateX: number = 0;
  @State enableCompBindPopupTransitionTranslateY: boolean = false;
  @State compBindPopupTransitionTranslateY: number = 0;
  @State enableCompBindPopupTransitionTranslateZ: boolean = false;
  @State compBindPopupTransitionTranslateZ: number = 0;
  @State enableCompBindPopupTransitionScaleX: boolean = false;
  @State compBindPopupTransitionScaleX: number = 0;
  @State enableCompBindPopupTransitionScaleY: boolean = false;
  @State compBindPopupTransitionScaleY: number = 0;
  @State enableCompBindPopupTransitionScaleZ: boolean = false;
  @State compBindPopupTransitionScaleZ: number = 0;
  @State enableCompBindPopupTransitionScaleCenterX: boolean = false;
  @State compBindPopupTransitionScaleCenterX: number = 0;
  @State enableCompBindPopupTransitionScaleCenterY: boolean = false;
  @State compBindPopupTransitionScaleCenterY: number = 0;
  @State enableCompBindPopupTransitionRotateX: boolean = false;
  @State compBindPopupTransitionRotateX: number = 0;
  @State enableCompBindPopupTransitionRotateY: boolean = false;
  @State compBindPopupTransitionRotateY: number = 0;
  @State enableCompBindPopupTransitionRotateZ: boolean = false;
  @State compBindPopupTransitionRotateZ: number = 0;
  @State enableCompBindPopupTransitionRotateAngle: boolean = false;
  @State compBindPopupTransitionRotateAngle: number = 0;
  @State enableCompBindPopupTransitionRotateCenterX: boolean = false;
  @State compBindPopupTransitionRotateCenterX: number = 0;
  @State enableCompBindPopupTransitionRotateCenterY: boolean = false;
  @State compBindPopupTransitionRotateCenterY: number = 0;
  @State enableCompBindPopupTransitionRotateCenterZ: boolean = false;
  @State compBindPopupTransitionRotateCenterZ: number = 0;
  @State enableCompBindPopupTransitionRotatePerspective: boolean = false;
  @State compBindPopupTransitionRotatePerspective: number = 0;
  @State enableCompBindPopupTransitionMove: boolean = false;
  @State compBindPopupTransitionMove: TransitionEdge = TransitionEdge.START;
  //Focus Control
  @State enableCompFocusable: boolean = false;
  @State compFocusable: boolean = false;
  @State enableCompDefaultFocus: boolean = false;
  @State compDefaultFocus: boolean = false;
  @State enableCompGroupDefaultFocus: boolean = false;
  @State compGroupDefaultFocus: boolean = false;
  @State enableCompFocusOnTouch: boolean = false;
  @State compFocusOnTouch: boolean = false;
  @State enableCompFocusBoxMargin: boolean = false;
  @State compFocusBoxMargin: number = 0;
  @State enableCompFocusBoxStrokeColor: boolean = false;
  @State compFocusBoxStrokeColor: ResourceColor = '#ff000000';
  @State enableCompFocusBoxStrokeWidth: boolean = false;
  @State compFocusBoxStrokeWidth: number = 0;
  @State enableCompFocusScopePriorityScopeId: boolean = false;
  @State compFocusScopePriorityScopeId: string = '1';
  @State enableCompFocusScopePriorityPriority: boolean = false;
  @State compFocusScopePriorityPriority: FocusPriority = FocusPriority.AUTO;
  @State enableCompFocusScopeId: boolean = false;
  @State compFocusScopeId: string = '1';
  @State enableCompFocusScopeIdIsGroup: boolean = false;
  @State compFocusScopeIdIsGroup: boolean = false;
  //hoverEffect
  @State enableCompHoverEffect: boolean = false;
  @State compHoverEffect: HoverEffect = HoverEffect.Auto;
  //id
  @State enableCompId: boolean = false;
  @State compId: string = '1';
  @State enableCompKey: boolean = false;
  @State compKey: string = '1';
  @State enableCompReuseId: boolean = false;
  @State compReuseId: string = '1';
  @State enableCompRestoreId: boolean = false;
  @State compRestoreId: number = 1;
  @State enableCompForegroundEffectRadius: boolean = false;
  @State compForegroundEffectRadius: number = 0;
  @State enableCompForegroundBlurStyleValue: boolean = false;
  @State compForegroundBlurStyleValue: BlurStyle = BlurStyle.NONE;
  @State enableCompForegroundBlurStyleOptionsColorMode: boolean = false;
  @State compForegroundBlurStyleOptionsColorMode: ThemeColorMode = ThemeColorMode.SYSTEM;
  @State enableCompForegroundBlurStyleOptionsAdaptiveColor: boolean = false;
  @State compForegroundBlurStyleOptionsAdaptiveColor: AdaptiveColor = AdaptiveColor.DEFAULT;
  @State enableCompForegroundBlurStyleOptionsBlurOptions: boolean = false;
  @State compForegroundBlurStyleOptionsBlurOptions: number = 0;
  @State enableCompForegroundBlurStyleOptionsScale: boolean = false;
  @State compForegroundBlurStyleOptionsScale: number = 0;
  //ClickEffect
  @State enableCompClickEffect: boolean = false;
  @State compClickEffect: boolean = false;
  @State enableCompClickEffectLevel: boolean = false;
  @State compClickEffectLevel: ClickEffectLevel = ClickEffectLevel.LIGHT;
  @State enableCompClickEffectScale: boolean = false;
  @State compClickEffectScale: number = 0.9;
  //accessibilityGroup
  @State enableCompAccessibilityGroup: boolean = false;
  @State compAccessibilityGroup: boolean = false;
  @State enableCompAccessibilityText: boolean = false;
  @State compAccessibilityText: string = `无障碍文本`;
  @State enableCompAccessibilityDescription: boolean = false;
  @State compAccessibilityDescription: string = `无障碍说明`;
  @State enableCompAccessibilityLevel: boolean = false;
  @State compAccessibilityLevel: string = 'auto';
  //Menu Control
  //bindMenu
  @State enableCompBindMenuStartIcon: boolean = false;
  @State compBindMenuStartIcon: boolean = false;
  @State compBindMenuStartIconStr: ResourceStr = $r('app.media.startIcon');
  @State enableCompBindMenuEndIcon: boolean = false;
  @State compBindMenuEndIcon: boolean = false;
  @State compBindMenuEndIconStr: ResourceStr = $r('sys.media.ohos_ic_public_arrow_right');
  @State enableCompBindMenuSelect: boolean = false;
  @State compBindMenuSelect: boolean = false;
  @State enableCompBindMenuSelect2: boolean = false;
  @State compBindMenuSelect2: boolean = false;
  @State enableCompBindMenuSelect3: boolean = false;
  @State compBindMenuSelect3: boolean = false;
  @State enableCompBindMenuSelect4: boolean = false;
  @State compBindMenuSelect4: boolean = false;
  @State enableCompBindMenuDirection: boolean = false;
  @State compBindMenuComDirection: Direction = Direction.Auto;
  @State enableCompBindMenuSelectIcon: boolean = false;
  @State compBindMenuSelectIcon: ResourceStr = $r('sys.media.ohos_ic_public_ok');
  @State enableCompBindMenuSelectIcon2: boolean = false;
  @State compBindMenuSelectIcon2: ResourceStr = $r('sys.media.ohos_ic_public_ok');
  @State enableCompBindMenuSelectIcon3: boolean = false;
  @State compBindMenuSelectIcon3: ResourceStr = $r('sys.media.ohos_ic_public_ok');
  @State enableCompBindMenuSelectIcon4: boolean = false;
  @State compBindMenuSelectIcon4: ResourceStr = $r('sys.media.ohos_ic_public_ok');
  @State enableCompBindMenuMenuFontSize: boolean = false;
  @State compBindMenuMenuFontSize: number = 16;
  @State enableCompBindMenuMenuFontWeight: boolean = false;
  @State compBindMenuMenuFontWeight: FontWeight = FontWeight.Medium;
  @State enableCompBindMenuMenuFontStyle: boolean = false;
  @State compBindMenuMenuFontStyle: FontStyle = FontStyle.Normal;
  @State enableCompBindMenuMenuFontColor: boolean = false;
  @State compBindMenuMenuFontColor: ResourceStr = '#E5000000';
  @State enableCompBindMenuMenuRadius: boolean = false;
  @State compBindMenuMenuRadius: number = 0;
  @State enableCompBindMenuMenuWidth: boolean = false;
  @State compBindMenuMenuWidth: number = 100;
  @State enableCompBindMenuMenuHeight: boolean = false;
  @State compBindMenuMenuHeight: number = 250;
  @State enableCompBindMenuMenuItemDividerStrokeWidth: boolean = false;
  @State compBindMenuMenuItemDividerStrokeWidth: number = 1;
  @State enableCompBindMenuMenuItemDividerColor: boolean = false;
  @State compBindMenuMenuItemDividerColor: ResourceStr = '#E5000000';
  @State enableCompBindMenuMenuItemDividerStartMargin: boolean = false;
  @State compBindMenuMenuItemDividerStartMargin: number = 16;
  @State enableCompBindMenuMenuItemDividerEndMargin: boolean = false;
  @State compBindMenuMenuItemDividerEndMargin: number = 16;
  @State enableCompBindMenuMenuItemGroupDividerStrokeWidth: boolean = false;
  @State compBindMenuMenuItemGroupDividerStrokeWidth: number = 1;
  @State enableCompBindMenuMenuItemGroupDividerColor: boolean = false;
  @State compBindMenuMenuItemGroupDividerColor: ResourceStr = '#E5000000';
  @State enableCompBindMenuMenuItemGroupDividerStartMargin: boolean = false;
  @State compBindMenuMenuItemGroupDividerStartMargin: number = 16;
  @State enableCompBindMenuMenuItemGroupDividerEndMargin: boolean = false;
  @State compBindMenuMenuItemGroupDividerEndMargin: number = 16;
  @State enableCompBindMenuSubMenuExpandingMode: boolean = false;
  @State compBindMenuSubMenuExpandingMode: SubMenuExpandingMode = SubMenuExpandingMode.SIDE_EXPAND;
  @State enableCompBindMenuMenuBackgroundColor: boolean = false;
  @State compBindMenuMenuBackgroundColor: ResourceStr = '#E5000000';
  @State enableCompBindMenuMenuOpacity: boolean = false;
  @State compBindMenuMenuOpacity: number = 1;
  @State enableCompBindMenuMenuVisibility: boolean = true;
  @State compBindMenuMenuVisibility: Visibility = Visibility.Visible;
  @State enableCompBindMenuMenuPadding: boolean = false;
  @State compBindMenuMenuPadding: number = 0;
  @State enableCompBindMenuMenuMargin: boolean = false;
  @State compBindMenuMenuMargin: number = 0;
  // Touch Target
  @State enableCompResponseRegionValueX: boolean = false
  @State compResponseRegionValueX: number = 0
  @State enableCompResponseRegionValueY: boolean = false
  @State compResponseRegionValueY: number = 0
  @State enableCompResponseRegionValueWidth: boolean = false
  @State compResponseRegionValueWidth: Length = '100%'
  @State enableCompResponseRegionValueHeight: boolean = false
  @State compResponseRegionValueHeight: Length = '100%'
  // Hit Test Control
  @State enableCompHitTestBehavior: boolean = false
  @State compHitTestBehavior: HitTestMode = HitTestMode.Default
  // Modal Transition
  @State enableCompBindContentCoverIsShow: boolean = false
  @State compBindContentCoverIsShow: boolean = false
  @State enableCompBindContentCoverOptionsModalTransition: boolean = false
  @State compBindContentCoverOptionsModalTransition: ModalTransition = ModalTransition.DEFAULT
  @State enableCompBindContentCoverOptionsTransitionOpacity: boolean = false
  @State compBindContentCoverOptionsTransitionOpacity: number = 1
  @State enableCompBindContentCoverOptionsTransitionTranslateX: boolean = false
  @State compBindContentCoverOptionsTransitionTranslateX: number = 0
  @State enableCompBindContentCoverOptionsTransitionTranslateY: boolean = false
  @State compBindContentCoverOptionsTransitionTranslateY: number = 0
  @State enableCompBindContentCoverOptionsTransitionTranslateZ: boolean = false
  @State compBindContentCoverOptionsTransitionTranslateZ: number = 0
  @State enableCompBindContentCoverOptionsTransitionScaleX: boolean = false
  @State compBindContentCoverOptionsTransitionScaleX: number = 0
  @State enableCompBindContentCoverOptionsTransitionScaleY: boolean = false
  @State compBindContentCoverOptionsTransitionScaleY: number = 0
  @State enableCompBindContentCoverOptionsTransitionScaleZ: boolean = false
  @State compBindContentCoverOptionsTransitionScaleZ: number = 0
  @State enableCompBindContentCoverOptionsTransitionScaleCenterX: boolean = false
  @State compBindContentCoverOptionsTransitionScaleCenterX: number = 50
  @State enableCompBindContentCoverOptionsTransitionScaleCenterY: boolean = false
  @State compBindContentCoverOptionsTransitionScaleCenterY: number = 50
  @State enableCompBindContentCoverOptionsTransitionRotateX: boolean = false
  @State compBindContentCoverOptionsTransitionRotateX: number = 0
  @State enableCompBindContentCoverOptionsTransitionRotateY: boolean = false
  @State compBindContentCoverOptionsTransitionRotateY: number = 0
  @State enableCompBindContentCoverOptionsTransitionRotateZ: boolean = false
  @State compBindContentCoverOptionsTransitionRotateZ: number = 0
  @State enableCompBindContentCoverOptionsTransitionRotateAngle: boolean = false
  @State compBindContentCoverOptionsTransitionRotateAngle: number = 0
  @State enableCompBindContentCoverOptionsTransitionRotateCenterX: boolean = false
  @State compBindContentCoverOptionsTransitionRotateCenterX: number = 50
  @State enableCompBindContentCoverOptionsTransitionRotateCenterY: boolean = false
  @State compBindContentCoverOptionsTransitionRotateCenterY: number = 50
  @State enableCompBindContentCoverOptionsTransitionRotateCenterZ: boolean = false
  @State compBindContentCoverOptionsTransitionRotateCenterZ: number = 0
  @State enableCompBindContentCoverOptionsTransitionRotatePerspective: boolean = false
  @State compBindContentCoverOptionsTransitionRotatePerspective: number = 0
  @State enableCompBindContentCoverOptionsTransitionMove: boolean = false
  @State compBindContentCoverOptionsTransitionMove: TransitionEdge = TransitionEdge.TOP
  @State enableCompBindContentCoverOptionsTransitionAnimationDuration: boolean = false
  @State compBindContentCoverOptionsTransitionAnimationDuration: number = 1000
  @State enableCompBindContentCoverOptionsTransitionAnimationTempo: boolean = false
  @State compBindContentCoverOptionsTransitionAnimationTempo: number = 1.0
  @State enableCompBindContentCoverOptionsTransitionAnimationCurve: boolean = false
  @State compBindContentCoverOptionsTransitionAnimationCurve: Curve = Curve.EaseInOut
  @State enableCompBindContentCoverOptionsTransitionAnimationDelay: boolean = false
  @State compBindContentCoverOptionsTransitionAnimationDelay: number = 0
  @State enableCompBindContentCoverOptionsTransitionAnimationIterations: boolean = false
  @State compBindContentCoverOptionsTransitionAnimationIterations: number = 1
  @State enableCompBindContentCoverOptionsTransitionAnimationPlayMode: boolean = false
  @State compBindContentCoverOptionsTransitionAnimationPlayMode: PlayMode = PlayMode.Normal
  @State enableCompBindContentCoverOptionsTransitionAnimationExpectedFrameRateRangeMin: boolean = false
  @State compBindContentCoverOptionsTransitionAnimationExpectedFrameRateRangeMin: number = 60
  @State enableCompBindContentCoverOptionsTransitionAnimationExpectedFrameRateRangeMax: boolean = false
  @State compBindContentCoverOptionsTransitionAnimationExpectedFrameRateRangeMax: number = 60
  @State enableCompBindContentCoverOptionsTransitionAnimationExpectedFrameRateRangeExpected: boolean = false
  @State compBindContentCoverOptionsTransitionAnimationExpectedFrameRateRangeExpected: number = 60
  // Sheet Transition
  @State enableCompBindSheetIsShow: boolean = false
  @State compBindSheetIsShow: boolean = false
  @State enableCompBindSheetOptionsHeight: boolean = false
  @State compBindSheetOptionsHeight: SheetSize = SheetSize.LARGE
  @State enableCompBindSheetOptionsDetents: boolean = false
  @State compBindSheetOptionsDetents: [(SheetSize | Length), (SheetSize | Length)?, (SheetSize | Length)?] =
    [SheetSize.LARGE]
  @State enableCompBindSheetOptionsPreferType: boolean = false
  @State compBindSheetOptionsPreferType: SheetType = SheetType.BOTTOM
  @State enableCompBindSheetOptionsShowClose: boolean = false
  @State compBindSheetOptionsShowClose: boolean = true
  @State enableCompBindSheetOptionsDragBar: boolean = false
  @State compBindSheetOptionsDragBar: boolean = false
  @State enableCompBindSheetOptionsBlurStyle: boolean = false
  @State compBindSheetOptionsBlurStyle: BlurStyle = BlurStyle.NONE
  @State enableCompBindSheetOptionsMaskColor: boolean = false
  @State compBindSheetOptionsMaskColor: ResourceColor | undefined = undefined
  @State enableCompBindSheetOptionsTitleTitle: boolean = false
  @State compBindSheetOptionsTitleTitle: boolean = false
  @State enableCompBindSheetOptionsTitleSubtitle: boolean = false
  @State compBindSheetOptionsTitleSubtitle: boolean = false
  @State enableCompBindSheetOptionsEnableOutsideInteractive: boolean = false
  @State compBindSheetOptionsEnableOutsideInteractive: boolean = false
  @State enableCompBindSheetOptionsBorderWidth: boolean = false
  @State compBindSheetOptionsBorderWidth: number = 0
  @State enableCompBindSheetOptionsBorderColor: boolean = false
  @State compBindSheetOptionsBorderColor: ResourceColor = Color.Black
  @State enableCompBindSheetOptionsBorderStyle: boolean = false
  @State compBindSheetOptionsBorderStyle: BorderStyle = BorderStyle.Solid
  @State enableCompBindSheetOptionWidth: boolean = false
  @State compBindSheetOptionsWidth: number = 200
  @State enableCompBindSheetOptionShadow: boolean = false
  @State compBindSheetOptionShadow: ShadowStyle = ShadowStyle.OUTER_DEFAULT_XS
  @State enableCompBindSheetOptionMode: boolean = false
  @State compBindSheetOptionMode: SheetMode = SheetMode.OVERLAY
  @State enableCompBindSheetOptionScrollSizeMode: boolean = false
  @State compBindSheetOptionScrollSizeMode: ScrollSizeMode = ScrollSizeMode.FOLLOW_DETENT
  // Obscuring
  @State enableCompObscured: boolean = false
  @State compObscured: Array<ObscuredReasons> = []
  // Event Monopolization
  @State enableCompMonopolizeEvents: boolean = false
  @State compMonopolizeEvents: boolean = false
  // Cursor Control
  @State enableCompCursorControl: boolean = false
  @State compCursorControl: pointer.PointerStyle = pointer.PointerStyle.DEFAULT
  // Special Effect Drawing Combination
  @State enableCompUseEffect: boolean = false
  @State compUseEffect: boolean = false

  @StorageLink('Block') listEventTriggeredTags: Array<BlockTag> = [];
  @State listEventTriggeredTagsTemp: Array<BlockTag> = [];

  compMaskColorChange() {
    this.progress.updateColor(this.compMaskColor);
  }

  compMaskValueChange() {
    this.progress.updateProgress(this.compMaskValue);
  }

  compEventTriggeredLog(value: string) {
    let time = formatDate(new Date(Date.now()))
    this.listEventTriggeredTagsTemp.push(
      new BlockTag(time,value)
    )
    setTimeout(() => {
      if (AppStorage.get('Block')) {
        this.listEventTriggeredTags = this.listEventTriggeredTags.concat(
          this.listEventTriggeredTagsTemp
        );
        this.listEventTriggeredTagsTemp = [];
      } else {
        if (this.listEventTriggeredTagsTemp) {
          this.listEventTriggeredTags = this.listEventTriggeredTags.concat(
            this.listEventTriggeredTagsTemp
          );
        }
        if (this.listEventTriggeredTags) {
          this.listEventTriggeredTagsTemp = [];
        }
      }
    }, 200)
  }

  build() {
    NavDestination() {
      Drawer({
        title: this.title,
        showParameters: $showParameters,
        content: () => {
          this.Content()
        },
        parameters: () => {
          this.Parameters()
        }
      })
    }
    .backgroundColor('#f1f3f5')
    .hideTitleBar(true)
  }

  @Builder
  privateRegion() {
    Text('Primary')
      .backgroundColor('rgba(255, 0, 0, 0.1)')
      .fontSize(28)
      .textAlign(TextAlign.Center)
      .height('100%')
      .width('100%')
  }

  @Builder
  secondaryRegion() {
    Text('Secondary')
      .backgroundColor('rgba(0, 255, 0, 0.1)')
      .fontSize(28)
      .textAlign(TextAlign.Center)
      .height('100%')
      .width('100%')
  }

  @Builder
  extraRegion() {
    Text('Extra')
      .backgroundColor('rgba(0, 0, 255, 0.1)')
      .fontSize(28)
      .textAlign(TextAlign.Center)
      .height('100%')
      .width('100%')
  }

  @Builder
  SubMenu() {
    Menu() {
      MenuItem({ content: '复制', labelInfo: 'Ctrl+C' })
        .direction(useEnabled(this.enableCompBindMenuDirection, this.compBindMenuComDirection))
      MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
        .direction(useEnabled(this.enableCompBindMenuDirection, this.compBindMenuComDirection))
    }
  }

  @Builder
  MyMenu() {
    Menu() {
      MenuItem({
        startIcon: useEnabled(this.compBindMenuStartIcon, this.compBindMenuStartIconStr),
        content: '菜单选项1',
        endIcon: useEnabled(this.compBindMenuEndIcon, this.compBindMenuEndIconStr),
        builder: () => {
          this.SubMenu()
        }
      })
        .selected(useEnabled(this.enableCompBindMenuSelect, this.compBindMenuSelect))
        .selectIcon(useEnabled(this.enableCompBindMenuSelectIcon, this.compBindMenuSelectIcon))
        .direction(useEnabled(this.enableCompBindMenuDirection, this.compBindMenuComDirection))

      MenuItem({
        startIcon: useEnabled(this.compBindMenuStartIcon, this.compBindMenuStartIconStr),
        content: '菜单选项2',
        endIcon: useEnabled(this.compBindMenuEndIcon, this.compBindMenuEndIconStr),
        builder: () => {
          this.SubMenu()
        }
      })
        .selected(useEnabled(this.enableCompBindMenuSelect2, this.compBindMenuSelect2))
        .selectIcon(useEnabled(this.enableCompBindMenuSelectIcon2, this.compBindMenuSelectIcon2))
        .direction(useEnabled(this.enableCompBindMenuDirection, this.compBindMenuComDirection))

      MenuItem({
        startIcon: useEnabled(this.compBindMenuStartIcon, this.compBindMenuStartIconStr),
        content: '菜单选项3',
        endIcon: useEnabled(this.compBindMenuEndIcon, this.compBindMenuEndIconStr),
      })
        .selected(useEnabled(this.enableCompBindMenuSelect3, this.compBindMenuSelect3))
        .selectIcon(useEnabled(this.enableCompBindMenuSelectIcon3, this.compBindMenuSelectIcon3))
        .direction(useEnabled(this.enableCompBindMenuDirection, this.compBindMenuComDirection))

      MenuItem({
        startIcon: useEnabled(this.compBindMenuStartIcon, this.compBindMenuStartIconStr),
        content: '菜单选项4',
        endIcon: useEnabled(this.compBindMenuEndIcon, this.compBindMenuEndIconStr),
      })
        .selected(useEnabled(this.enableCompBindMenuSelect4, this.compBindMenuSelect4))
        .selectIcon(useEnabled(this.enableCompBindMenuSelectIcon4, this.compBindMenuSelectIcon4))
        .direction(useEnabled(this.enableCompBindMenuDirection, this.compBindMenuComDirection))
    }
    .font({
      size: useEnabled(this.enableCompBindMenuMenuFontSize, this.compBindMenuMenuFontSize),
      weight: useEnabled(this.enableCompBindMenuMenuFontWeight, this.compBindMenuMenuFontWeight),
      style: useEnabled(this.enableCompBindMenuMenuFontStyle, this.compBindMenuMenuFontStyle)
    })
    .fontColor(useEnabled(this.enableCompBindMenuMenuFontColor, this.compBindMenuMenuFontColor))
    .radius(useEnabled(this.enableCompBindMenuMenuRadius, this.compBindMenuMenuRadius))
    .width(useEnabled(this.enableCompBindMenuMenuWidth, this.compBindMenuMenuWidth))
    .height(useEnabled(this.enableCompBindMenuMenuHeight, this.compBindMenuMenuHeight))
    .menuItemDivider({
      strokeWidth: useEnabled(this.enableCompBindMenuMenuItemDividerStrokeWidth,
        LengthMetrics.vp(this.compBindMenuMenuItemDividerStrokeWidth)),
      color: useEnabled(this.enableCompBindMenuMenuItemDividerColor, this.compBindMenuMenuItemDividerColor),
      startMargin: useEnabled(this.enableCompBindMenuMenuItemDividerStartMargin,
        LengthMetrics.vp(this.compBindMenuMenuItemDividerStartMargin)),
      endMargin: useEnabled(this.enableCompBindMenuMenuItemDividerEndMargin,
        LengthMetrics.vp(this.compBindMenuMenuItemDividerEndMargin))
    })
    .menuItemGroupDivider({
      strokeWidth: useEnabled(this.enableCompBindMenuMenuItemGroupDividerStrokeWidth,
        LengthMetrics.vp(this.compBindMenuMenuItemGroupDividerStrokeWidth)),
      color: useEnabled(this.enableCompBindMenuMenuItemGroupDividerColor,
        this.compBindMenuMenuItemGroupDividerColor),
      startMargin: useEnabled(this.enableCompBindMenuMenuItemGroupDividerStartMargin,
        LengthMetrics.vp(this.compBindMenuMenuItemGroupDividerStartMargin)),
      endMargin: useEnabled(this.enableCompBindMenuMenuItemGroupDividerEndMargin,
        LengthMetrics.vp(this.compBindMenuMenuItemGroupDividerEndMargin))
    })
    .subMenuExpandingMode(useEnabled(this.enableCompBindMenuSubMenuExpandingMode,
      this.compBindMenuSubMenuExpandingMode))
    .backgroundColor(useEnabled(this.enableCompBindMenuMenuBackgroundColor, this.compBindMenuMenuBackgroundColor))
    .opacity(useEnabled(this.enableCompBindMenuMenuOpacity, this.compBindMenuMenuOpacity))
    .visibility(useEnabled(this.enableCompBindMenuMenuVisibility, this.compBindMenuMenuVisibility))
    .padding(useEnabled(this.enableCompBindMenuMenuPadding, this.compBindMenuMenuPadding))
    .margin(useEnabled(this.enableCompBindMenuMenuMargin, this.compBindMenuMenuMargin))
  }

  @Builder
  popupBuilder() {
    Row() {
      Text('自定义气泡').fontSize(10)
    }.height(50).padding(5)
  }

  @Builder
  compBackground() {
    Text('123')
  }

  @Builder
  bindSheetBuilder() {
    Text('bindSheet')
  }

  @Builder
  bindContentCoverBuilder() {
    Column() {
      Button('close modal')
        .margin(10)
        .fontSize(20)
        .onClick(() => {
          this.compBindContentCoverIsShow = false;
        })
    }
    .width('100%')
    .height('100%')
    .justifyContent(FlexAlign.Center)
  }

  @Builder
  Content() {
    RelativeContainer() {
     FoldSplitContainer({
        primary: () => {
          this.privateRegion()
        },
        secondary: () => {
          this.secondaryRegion()
        },
        extra: () => {
          this.extraRegion()
        },
        expandedLayoutOptions: {
          isExtraRegionPerpendicular: useEnabled(
            this.enableExpandedLayoutOptionsIsExtraRegionPerpendicular,
            this.expandedLayoutOptionsIsExtraRegionPerpendicular
          ),
          verticalSplitRatio: useEnabled(
            this.enableExpandedLayoutOptionsVerticalSplitRatio,
            this.expandedLayoutOptionsVerticalSplitRatio
          ),
          horizontalSplitRatio: useEnabled(
            this.enableExpandedLayoutOptionsHorizontalSplitRatio,
            this.expandedLayoutOptionsHorizontalSplitRatio
          ),
          extraRegionPosition: useEnabled(
            this.enableExpandedLayoutOptionsExtraRegionPosition,
            this.expandedLayoutOptionsExtraRegionPosition
          )
        },
        hoverModeLayoutOptions: {
          showExtraRegion: useEnabled(
            this.enableHoverModeLayoutOptionsShowExtraRegion,
            this.hoverModeLayoutOptionsShowExtraRegion
          ),
          horizontalSplitRatio: useEnabled(
            this.enableHoverModeLayoutOptionsHorizontalSplitRatio,
            this.hoverModeLayoutOptionsHorizontalSplitRatio
          ),
          extraRegionPosition: useEnabled(
            this.enableHoverModeLayoutOptionsExtraRegionPosition,
            this.hoverModeLayoutOptionsExtraRegionPosition
          )
        },
        foldedLayoutOptions: {
          verticalSplitRatio: useEnabled(
            this.enableFoldedLayoutOptionsVerticalSplitRatio,
            this.foldedLayoutOptionsVerticalSplitRatio
          )
        },
        animationOptions: {
          duration: useEnabled(this.enableAnimationOptionsDuration, this.animationOptionsDuration),
          tempo: useEnabled(this.enableAnimationOptionsTempo, this.animationOptionsTempo),
          curve: useEnabled(this.enableAnimationOptionsCurve, this.animationOptionsCurve),
          delay: useEnabled(this.enableAnimationOptionsDelay, this.animationOptionsDelay),
          iterations: useEnabled(this.enableAnimationOptionsIterations, this.animationOptionsIterations),
          playMode: useEnabled(this.enableAnimationOptionsPlayMode, this.animationOptionsPlayMode),
          finishCallbackType: useEnabled(
            this.enableAnimationOptionsFinishCallbackType,
            this.animationOptionsFinishCallbackType
          ),
          expectedFrameRateRange: {
            min: useEnabledNumber(
              this.enableAnimationOptionsExpectedFrameRateRangeMin,
              this.animationOptionsExpectedFrameRateRangeMin,
              10
            ),
            max: useEnabledNumber(
              this.enableAnimationOptionsExpectedFrameRateRangeMax,
              this.animationOptionsExpectedFrameRateRangeMax,
              120
            ),
            expected: useEnabledNumber(
              this.enableAnimationOptionsExpectedFrameRateRangeExpected,
              this.animationOptionsExpectedFrameRateRangeExpected,
              60
            )
          }
        },
     })
       .flexBasis(useEnabled(this.enableCompFlexBasis, this.compFlexBasis))
       .direction(useEnabled(this.enableCompDirection, this.compDirection))
       .width(useEnabled(this.enableCompWidth, this.compWidth))
       .height(useEnabled(this.enableCompHeight, this.compHeight))
       .padding(useEnabled(this.enableCompPadding, this.compPadding))
       .margin(useEnabled(this.enableCompMargin, this.compMargin))
       .constraintSize({
         maxWidth: useEnabled(this.enableCompConstraintSizeMaxWidth, this.compConstraintSizeMaxWidth),
         maxHeight: useEnabled(this.enableCompConstraintSizeMaxHeight, this.compConstraintSizeMaxHeight),
         minWidth: useEnabled(this.enableCompConstraintSizeMinWidth, this.compConstraintSizeMinWidth),
         minHeight: useEnabled(this.enableCompConstraintSizeMinHeight, this.compConstraintSizeMinHeight)
       })
       .position(this.enableCompPosition ? {
         top: useEnabled(this.enableCompPositionTop, this.compPositionTop),
         bottom: useEnabled(this.enableCompPositionBottom, this.compPositionBottom),
         left: useEnabled(this.enableCompPositionBottom, this.compPositionBottom),
         right: useEnabled(this.enableCompPositionBottom, this.compPositionBottom)
       } : {})
       .markAnchor(this.enableCompMarkAnchor ? {
         x: useEnabled(this.enableCompMarkAnchorX, this.compMarkAnchorX),
         y: useEnabled(this.enableCompMarkAnchorY, this.compMarkAnchorY)
       } : {})
       .offset({
         x: useEnabled(this.enableCompOffsetX, this.compOffsetX),
         y: useEnabled(this.enableCompOffsetY, this.compOffsetY)
       })
       .aspectRatio(useEnabled(this.enableCompAspectRatio, this.compAspectRatio))
       .pixelRound(this.enableCompPixelRound ? {
         start: useEnabled(this.enableCompPixelRoundStart, this.compPixelRoundStart),
         end: useEnabled(this.enableCompPixelRoundEnd, this.compPixelRoundEnd),
         bottom: useEnabled(this.enableCompPixelRoundBottom, this.compPixelRoundBottom),
         top: useEnabled(this.enableCompPixelRoundTop, this.compPixelRoundTop)
       } : {})
       .border({
         width: useEnabled(this.enableCompBorderWidth, this.compBorderWidth),
         color: useEnabled(this.enableCompBorderColor, this.compBorderColor),
         radius: useEnabled(this.enableCompBorderRadius, this.compBorderRadius),
         style: useEnabled(this.enableCompBorderStyle, this.compBorderStyle),
         dashGap: {
           left: useEnabled(this.enableCompBorderDashGapLeft, this.compBorderDashGapLeft),
           right: useEnabled(this.enableCompBorderDashGapRight, this.compBorderDashGapRight),
           top: useEnabled(this.enableCompBorderDashGapTop, this.compBorderDashGapTop),
           bottom: useEnabled(this.enableCompBorderDashGapBottom, this.compBorderDashGapBottom)
         },
         dashWidth: {
           left: useEnabled(this.enableCompBorderDashWidthLeft, this.compBorderDashWidthLeft),
           right: useEnabled(this.enableCompBorderDashWidthRight, this.compBorderDashWidthRight),
           top: useEnabled(this.enableCompBorderDashWidthTop, this.compBorderDashWidthTop),
           bottom: useEnabled(this.enableCompBorderDashWidthBottom, this.compBorderDashWidthBottom)
         }
       })
       .borderRadius(useEnabled(this.enableCompBorderRadius, this.compBorderRadius))
       .borderStyle(useEnabled(this.enableCompBorderStyle, this.compBorderStyle))
       .borderColor(useEnabled(this.enableCompBorderColor, this.compBorderColor))
       .borderWidth(useEnabled(this.enableCompBorderWidth, this.compBorderWidth))
       .borderImage(this.enableCompBorderImage ? {
         source: this.enableCompBorderImageSource ? $r('app.media.startIcon') : '',
         slice: this.enableCompBorderImageSlice ? {
           top: useEnabled(this.enableCompBorderImageSliceTop, this.compBorderImageSliceTop),
           bottom: useEnabled(this.enableCompBorderImageSliceBottom, this.compBorderImageSliceBottom),
           left: useEnabled(this.enableCompBorderImageSliceLeft, this.compBorderImageSliceLeft),
           right: useEnabled(this.enableCompBorderImageSliceRight, this.compBorderImageSliceRight)
         } : 0,
         width: this.enableCompBorderImageWidth ? {
           top: useEnabled(this.enableCompBorderImageWidthTop, this.compBorderImageWidthTop),
           bottom: useEnabled(this.enableCompBorderImageWidthBottom, this.compBorderImageWidthBottom),
           left: useEnabled(this.enableCompBorderImageWidthLeft, this.compBorderImageWidthLeft),
           right: useEnabled(this.enableCompBorderImageWidthRight, this.compBorderImageWidthRight)
         } : 0,
         outset: this.enableCompBorderImageOutset ? {
           top: useEnabled(this.enableCompBorderImageOutsetTop, this.compBorderImageOutsetTop),
           bottom: useEnabled(this.enableCompBorderImageOutsetBottom, this.compBorderImageOutsetBottom),
           left: useEnabled(this.enableCompBorderImageOutsetLeft, this.compBorderImageOutsetLeft),
           right: useEnabled(this.enableCompBorderImageOutsetRight, this.compBorderImageOutsetRight)
         } : 0,
         repeat: useEnabled(this.enableCompBorderImageRepeat, this.compBorderImageRepeat),
         fill: useEnabled(this.enableCompBorderImageFill, this.compBorderImageFill)
       } : {})
       .background(this.enableCompBackgroundAlign ? this.compBackground() : null,
         this.enableCompBackgroundAlign ? {
           align: useEnabled(this.enableCompBackgroundAlign, this.compBackgroundAlign)
         }
           : {}
       )
       .backgroundColor(useEnabled(this.enableCompBackgroundColor, this.compBackgroundColor))
       .backgroundImage(this.enableCompBackgroundImageSrc ? $r('app.media.app_icon') : '',
         useEnabled(this.enableCompBackgroundImageRepeat, this.compBackgroundImageRepeat))
       .backgroundImageSize(useEnabled(this.enableCompBackgroundImageSize, this.compBackgroundImageSize))
       .backgroundImagePosition({
         x: useEnabled(this.enableCompBackgroundImagePositionX, this.compBackgroundImagePositionX),
         y: useEnabled(this.enableCompBackgroundImagePositionY, this.compBackgroundImagePositionY)
       })
       .backgroundBlurStyle(useEnabled(this.enableCompBackgroundBlurStyle, this.compBackgroundBlurStyle),
         this.enableCompBackgroundBlurStyleParams ? {
           colorMode: useEnabled(
             this.enableCompBackgroundBlurStyleParamsColorMode,
             this.compBackgroundBlurStyleParamsColorMode
           ),
           adaptiveColor: useEnabled(
             this.enableCompBackgroundBlurStyleParamsAdaptiveColor,
             this.compBackgroundBlurStyleParamsAdaptiveColor
           ),
           scale: useEnabled(
             this.enableCompBackgroundBlurStyleParamsScale,
             this.compBackgroundBlurStyleParamsScale
           ),
           blurOptions: {
             grayscale: [
               useEnabled(
                 this.enableCompBackgroundBlurStyleParamsBlurOptionsLeft,
                 this.compBackgroundBlurStyleParamsBlurOptionsLeft
               ),
               useEnabled(
                 this.enableCompBackgroundBlurStyleParamsBlurOptionsRight,
                 this.compBackgroundBlurStyleParamsBlurOptionsRight
               )
             ]
           }
         } : null)
       .backdropBlur(useEnabled(
         this.enableCompBackdropBlur,
         this.compBackdropBlur
       ), {
         grayscale:
         this.enableCompBackdropBlurGrayscale ? [
           useEnabled(
             this.enableCompBackdropBlurGrayscaleLeft,
             this.compBackdropBlurGrayscaleLeft
           ),
           useEnabled(
             this.enableCompBackdropBlurGrayscaleRight,
             this.compBackdropBlurGrayscaleRight
           )
         ] : [0, 0]
       })
       .backgroundEffect({
         radius: useEnabled(
           this.enableCompBackgroundEffectRadius,
           this.compBackgroundEffectRadius
         ),
         saturation: useEnabled(
           this.enableCompBackgroundEffectSaturation,
           this.compBackgroundEffectSaturation
         ),
         brightness: useEnabled(
           this.enableCompBackgroundEffectBrightness,
           this.compBackgroundEffectBrightness
         ),
         color: useEnabled(
           this.enableCompBackgroundEffectColor,
           this.compBackgroundEffectColor
         ),
         adaptiveColor: useEnabled(
           this.enableCompBackgroundEffectAdaptiveColor,
           this.compBackgroundEffectAdaptiveColor
         ),
         blurOptions: {
           grayscale: [
             useEnabled(
               this.enableCompBackgroundEffectBlurOptionsGrayscaleLeft,
               this.compBackgroundEffectBlurOptionsGrayscaleLeft
             ),
             useEnabled(
               this.enableCompBackgroundEffectBlurOptionsGrayscaleRight,
               this.compBackgroundEffectBlurOptionsGrayscaleRight
             )
           ]
         }
       })
       .backgroundImageResizable({
         slice: {
           top: useEnabled(
             this.enableCompBackgroundImageResizableSliceTop,
             this.compBackgroundImageResizableSliceTop
           ),
           bottom: useEnabled(
             this.enableCompBackgroundImageResizableSliceBottom,
             this.compBackgroundImageResizableSliceBottom
           ),
           left: useEnabled(
             this.enableCompBackgroundImageResizableSliceLeft,
             this.compBackgroundImageResizableSliceLeft
           ),
           right: useEnabled(
             this.enableCompBackgroundImageResizableSliceRight,
             this.compBackgroundImageResizableSliceRight
           )
         },
         lattice: {
           xDivs: useEnabled(
             this.enableCompBackgroundImageResizableLatticeXDivs,
             this.compBackgroundImageResizableLatticeXDivs
           ),
           yDivs: useEnabled(
             this.enableCompBackgroundImageResizableLatticeYDivs,
             this.compBackgroundImageResizableLatticeYDivs
           ),
           fXCount: useEnabled(
             this.enableCompBackgroundImageResizableLatticeFXCount,
             this.compBackgroundImageResizableLatticeFXCount
           ),
           fYCount: useEnabled(
             this.enableCompBackgroundImageResizableLatticeFYCount,
             this.compBackgroundImageResizableLatticeFYCount
           ),
           fBounds: this.enableCompBackgroundImageResizableLatticeFBounds ? {
             left: useEnabled(
               this.enableCompBackgroundImageResizableLatticeFBoundsLeft,
               this.compBackgroundImageResizableLatticeFBoundsLeft
             ),
             right: useEnabled(
               this.enableCompBackgroundImageResizableLatticeFBoundsRight,
               this.compBackgroundImageResizableLatticeFBoundsRight
             ),
             top: useEnabled(
               this.enableCompBackgroundImageResizableLatticeFBoundsTop,
               this.compBackgroundImageResizableLatticeFBoundsTop
             ),
             bottom: useEnabled(
               this.enableCompBackgroundImageResizableLatticeFBoundsBottom,
               this.compBackgroundImageResizableLatticeFBoundsBottom
             ),
           } as common2D.Rect : null,
           fRectTypes: null,
           fColors: useEnabled(
             this.enableCompBackgroundImageResizableLatticeFColors,
             this.compBackgroundImageResizableLatticeFColors
           )
         }
       })
       .opacity(useEnabled(
         this.enableCompOpacity,
         this.compOpacity
       ))
       .visibility(useEnabled(
         this.enableCompVisibility,
         this.compVisibility
       ))
       .enabled(useEnabled(
         this.enableCompEnabled,
         this.compEnabled
       ))
       .overlay(
         useEnabled(this.enableCompOverlay, this.compOverlay),
         this.enableCompOverlayOptions ? {
           align: useEnabled(
             this.enableCompOverlayOptionsAlign,
             this.compOverlayOptionsAlign
           ),
           offset: {
             x: useEnabled(
               this.enableCompOverlayOptionsOffsetX,
               this.compOverlayOptionsOffsetX
             ),
             y: useEnabled(
               this.enableCompOverlayOptionsOffsetY,
               this.compOverlayOptionsOffsetY
             ),
           }
         } : {})
       .zIndex(useEnabled(this.enableCompZIndex, this.compZIndex))
       .rotate(this.enableCompRotate ? {
         x: useEnabled(
           this.enableCompRotateX,
           this.compRotateX
         ),
         y: useEnabled(
           this.enableCompRotateY,
           this.compRotateY
         ),
         z: useEnabled(
           this.enableCompRotateZ,
           this.compRotateZ
         ),
         angle: useEnabled(
           this.enableCompRotateAngle,
           this.compRotateAngle
         ),
         centerX: useEnabled(
           this.enableCompRotateCenterX,
           this.compRotateCenterX
         ),
         centerY: useEnabled(
           this.enableCompRotateCenterY,
           this.compRotateCenterY
         ),
         centerZ: useEnabled(
           this.enableCompRotateCenterZ,
           this.compRotateCenterZ
         ),
         perspective: useEnabled(
           this.enableCompRotatePerspective,
           this.compRotatePerspective
         )
       } : {
         angle: useEnabled(
           this.enableCompRotateAngle,
           this.compRotateAngle
         )
       })
       .translate(this.enableCompTranslate ? {
         x: useEnabled(
           this.enableCompTranslateX,
           this.compTranslateX
         ),
         y: useEnabled(
           this.enableCompTranslateY,
           this.compTranslateY
         ),
         z: useEnabled(
           this.enableCompTranslateZ,
           this.compTranslateZ
         )
       } : {})
       .scale(this.enableCompScale ? {
         x: useEnabled(
           this.enableCompScaleX,
           this.compScaleX
         ),
         y: useEnabled(
           this.enableCompScaleY,
           this.compScaleY
         ),
         z: useEnabled(
           this.enableCompScaleZ,
           this.compScaleZ
         ),
         centerX: useEnabled(
           this.enableCompScaleCenterX,
           this.compScaleCenterX
         ),
         centerY: useEnabled(
           this.enableCompScaleCenterY,
           this.compScaleCenterY
         )
       } : {})
       .transform(this.enableCompTransform ?
       matrix4.identity().rotate({ z: 1, angle: 90 }) :
       matrix4.identity()
       )
       .clip(useEnabled(
         this.enableCompClip,
         this.compClip
       ))
       .mask(this.progress)
       .blur(useEnabled(this.enableCompBlurValue, this.compBlurValue), {
         grayscale: [
           useEnabled(this.enableCompBlurOptionsNumber1, this.compBlurOptionsNumber1),
           useEnabled(this.enableCompBlurOptionsNumber2, this.compBlurOptionsNumber2)
         ]
       })
       .shadow({
         radius: useEnabled(this.enableCompShadowValueRadius, this.compShadowValueRadius),
         type: useEnabled(this.enableCompShadowValueType, this.compShadowValueType),
         color: useEnabled(this.enableCompShadowValueColor, this.compShadowValueColor),
         offsetX: useEnabled(this.enableCompShadowValueOffsetX, this.compShadowValueOffsetX),
         offsetY: useEnabled(this.enableCompShadowValueOffsetY, this.compShadowValueOffsetY),
         fill: useEnabled(this.enableCompShadowValueFill, this.compShadowValueFill)
       })
       .grayscale(useEnabled(this.enableCompGrayscale, this.compGrayscale))
       .brightness(useEnabled(this.enableCompBrightness, this.compBrightness))
       .saturate(useEnabled(this.enableCompSaturate, this.compSaturate))
       .contrast(useEnabled(this.enableCompContrast, this.compContrast))
       .invert(useEnabled(this.enableCompInvert, this.compInvert))
       .sepia(useEnabled(this.enableCompSepia, this.compSepia))
       .hueRotate(useEnabled(this.enableCompHueRotate, this.compHueRotate))
       .colorBlend(useEnabled(this.enableCompColorBlend, this.compColorBlend))
       .linearGradient( {
         angle: useEnabled(this.enableCompLinearGradientAngle, this.compLinearGradientAngle),
         direction: useEnabled(this.enableCompLinearGradientDirection, this.compLinearGradientDirection),
         colors: [
           [
             useEnabled(this.enableCompLinearGradientColors1, this.compLinearGradientColors1),
             useEnabled(this.enableCompLinearGradientColorsNumber1, this.compLinearGradientColorsNumber1)
           ],
           [
             useEnabled(this.enableCompLinearGradientColors2, this.compLinearGradientColors2),
             useEnabled(this.enableCompLinearGradientColorsNumber2, this.compLinearGradientColorsNumber2)
           ]
         ],
         repeating: useEnabled(this.enableCompLinearGradientRepeating, this.compLinearGradientRepeating),
       })
       .bindPopup(this.handlePopup, {
         message: this.compPopupType === 0 ? 'This is a popup with button ' : 'This is a popup only Text ',
         arrowOffset: useEnabled(this.enableCompBindPopupArrowOffset, this.compBindPopupArrowOffset) ?
         useEnabled(this.enableCompBindPopupArrowOffset, this.compBindPopupArrowOffset) : null,
         showInSubWindow: useEnabled(this.enableCompBindPopupShowInSubWindow, this.compBindPopupShowInSubWindow),
         mask: useEnabled(this.enableCompBindPopupMaskType, this.compBindPopupMaskType) ?
         useEnabled(this.enableCompBindPopupMaskBoolean, this.compBindPopupMaskBoolean) :
           { color: useEnabled(this.enableCompBindPopupMaskColor, this.compBindPopupMaskColor) },
         messageOptions: {
           textColor: useEnabled(this.enableCompBindPopupMessageOptionsTextColor,
             this.compBindPopupMessageOptionsTextColor),
           font: {
             size: useEnabled(this.enableCompBindPopupMessageOptionsFontSize,
               this.compBindPopupMessageOptionsFontSize),
             weight: useEnabled(this.enableCompBindPopupMessageOptionsFontWeight,
               this.compBindPopupMessageOptionsFontWeight),
             style: useEnabled(this.enableCompBindPopupMessageOptionsFontStyle,
               this.compBindPopupMessageOptionsFontStyle),
           }
         },
         targetSpace: useEnabled(this.enableCompBindPopupTargetSpace, this.compBindPopupTargetSpace),
         placement:
         useEnabled(this.enableCompBindPopupPlacement, this.compBindPopupPlacement) ?
         useEnabled(this.enableCompBindPopupPlacement, this.compBindPopupPlacement) : Placement.Top,
         offset: {
           x: useEnabled(this.enableCompBindPopupOffsetX, this.compBindPopupOffsetX),
           y: useEnabled(this.enableCompBindPopupOffsetY, this.compBindPopupOffsetY),
         },
         enableArrow: useEnabled(this.enableCompBindPopupEnableArrow, this.compBindPopupEnableArrow),
         popupColor: useEnabled(this.enableCompBindPopupPopupColor, this.compBindPopupPopupColor),
         autoCancel: useEnabled(this.enableCompBindPopupAutoCancel, this.compBindPopupAutoCancel),
         width: useEnabled(this.enableCompBindPopupWidth, this.compBindPopupWidth),
         arrowPointPosition: useEnabled(this.enableCompBindPopupArrowPointPosition,
           this.compBindPopupArrowPointPosition),
         arrowWidth: useEnabled(this.enableCompBindPopupArrowWidth, this.compBindPopupArrowWidth),
         arrowHeight: useEnabled(this.enableCompBindPopupArrowHeight, this.compBindPopupArrowHeight),
         radius: useEnabled(this.enableCompBindPopupRadius, this.compBindPopupRadius),
         shadow: useEnabled(this.enableCompBindPopupShadowType, this.compBindPopupShadowType) ?
         useEnabled(this.enableCompBindPopupShadowStyle, this.compBindPopupShadowStyle) : {
             radius: useEnabled(this.enableCompBindPopupShadowOptionsRadius,
               this.compBindPopupShadowOptionsRadius),
             type: useEnabled(this.enableCompBindPopupShadowOptionsType, this.compBindPopupShadowOptionsType),
             color: useEnabled(this.enableCompBindPopupShadowOptionsColor, this.compBindPopupShadowOptionsColor),
             offsetX: useEnabled(this.enableCompBindPopupShadowOptionsOffsetX,
               this.compBindPopupShadowOptionsOffsetX),
             offsetY: useEnabled(this.enableCompBindPopupShadowOptionsOffsetY,
               this.compBindPopupShadowOptionsOffsetY),
             fill: useEnabled(this.enableCompBindPopupShadowOptionsFill, this.compBindPopupShadowOptionsFill),
           },
         backgroundBlurStyle: useEnabled(this.enableCompBindPopupBackgroundBlurStyle,
           this.compBindPopupBackgroundBlurStyle),
         transition: (this.enableTransitionTransitionEffect ?
         useEnabled(this.enableTransitionTransitionEffect, this.transitionTransitionEffect)
         ?.combine(
           TransitionEffect.opacity(useEnabled(this.enableCompBindPopupTransitionOpacity,
             this.compBindPopupTransitionOpacity))
         )
           :
         TransitionEffect.opacity(
           useEnabled(this.enableCompBindPopupTransitionOpacity, this.compBindPopupTransitionOpacity)
         )
         )
         ?.combine(TransitionEffect.translate({
           x: useEnabled(
             this.enableCompBindPopupTransitionTranslateX,
             this.compBindPopupTransitionTranslateX
           ),
           y: useEnabled(
             this.enableCompBindPopupTransitionTranslateY,
             this.compBindPopupTransitionTranslateY
           ),
           z: useEnabled(
             this.enableCompBindPopupTransitionTranslateZ,
             this.compBindPopupTransitionTranslateZ
           )
         }))
         ?.combine(TransitionEffect.scale({
           x: useEnabled(
             this.enableCompBindPopupTransitionScaleX,
             this.compBindPopupTransitionScaleX
           ),
           y: useEnabled(
             this.enableCompBindPopupTransitionScaleY,
             this.compBindPopupTransitionScaleY
           ),
           z: useEnabled(
             this.enableCompBindPopupTransitionScaleZ,
             this.compBindPopupTransitionScaleZ
           ),
           centerX: useEnabled(
             this.enableCompBindPopupTransitionScaleCenterX,
             this.compBindPopupTransitionScaleCenterX
           ),
           centerY: useEnabled(
             this.enableCompBindPopupTransitionScaleCenterY,
             this.compBindPopupTransitionScaleCenterY
           ),
         })
         )
         ?.combine(TransitionEffect.rotate({
           x: useEnabled(this.enableCompBindPopupTransitionRotateX, this.compBindPopupTransitionRotateX),
           y: useEnabled(this.enableCompBindPopupTransitionRotateY, this.compBindPopupTransitionRotateY),
           z: useEnabled(this.enableCompBindPopupTransitionRotateZ, this.compBindPopupTransitionRotateZ),
           angle: useEnabled(this.enableCompBindPopupTransitionRotateAngle,
             this.compBindPopupTransitionRotateAngle),
           centerX: useEnabled(this.enableCompBindPopupTransitionRotateCenterX,
             this.compBindPopupTransitionRotateCenterX),
           centerY: useEnabled(this.enableCompBindPopupTransitionRotateCenterY,
             this.compBindPopupTransitionRotateCenterY),
           centerZ: useEnabled(this.enableCompBindPopupTransitionRotateCenterZ,
             this.compBindPopupTransitionRotateCenterZ),
           perspective: useEnabled(this.enableCompBindPopupTransitionRotatePerspective,
             this.compBindPopupTransitionRotatePerspective),
         })
         )
         ?.combine(TransitionEffect.move(
           useEnabled(this.enableCompBindPopupTransitionMove, this.compBindPopupTransitionMove)
         ))
       ,
         onStateChange: (e) => {
           console.info('onStateChange', JSON.stringify(e.isVisible))
           this.handlePopup = e.isVisible
         },
         primaryButton: this.compPopupType === 0 ? {
           value: 'confirm ',
           action: () => {
             this.handlePopup = !this.handlePopup;
             console.info('confirm Button click');
           }
         } : null,
         secondaryButton: this.compPopupType === 0 ? {
           value: 'cancel ',
           action: () => {
             this.handlePopup = !this.handlePopup;
             console.info('cancel Button click')
           }
         } : null,
       })
       .focusable(useEnabled(this.enableCompFocusable,
         this.compFocusable))
       .defaultFocus(useEnabled(this.enableCompDefaultFocus, this.compDefaultFocus))
       .groupDefaultFocus(useEnabled(this.enableCompGroupDefaultFocus, this.compGroupDefaultFocus))
       .focusOnTouch(useEnabled(this.enableCompFocusOnTouch, this.compFocusOnTouch))
       .focusBox({
         margin: useEnabled(this.enableCompFocusBoxMargin, this.compFocusBoxMargin) ?
         LengthMetrics.vp(useEnabled(this.enableCompFocusBoxMargin, this.compFocusBoxMargin)) : null,
         strokeColor: useEnabled(this.enableCompFocusBoxStrokeColor, this.compFocusBoxStrokeColor) ?
         ColorMetrics.resourceColor(useEnabled(this.enableCompFocusBoxStrokeColor, this.compFocusBoxStrokeColor)) :
           null,
         strokeWidth: useEnabled(this.enableCompFocusBoxStrokeWidth, this.compFocusBoxStrokeWidth) ?
         LengthMetrics.vp(useEnabled(this.enableCompFocusBoxStrokeWidth,
           this.compFocusBoxStrokeWidth)) : null,
       })
       .id(useEnabled(this.enableCompId, this.compId) ? useEnabled(this.enableCompId, this.compId) : null)
       .key(useEnabled(this.enableCompKey, this.compKey) ? useEnabled(this.enableCompKey, this.compKey) : null)
       .focusScopePriority(
         useEnabled(this.enableCompFocusScopePriorityScopeId, this.compFocusScopePriorityScopeId),
         useEnabled(this.enableCompFocusScopePriorityPriority, this.compFocusScopePriorityPriority)
       )
       .focusScopeId(
         useEnabled(this.enableCompFocusScopeId, this.compFocusScopeId),
         useEnabled(this.enableCompFocusScopeIdIsGroup, this.compFocusScopeIdIsGroup)
       )
       .hoverEffect(useEnabled(this.enableCompHoverEffect, this.compHoverEffect))
       .reuseId(useEnabled(this.enableCompReuseId, this.compReuseId)
         ? useEnabled(this.enableCompReuseId, this.compReuseId) : null)
       .restoreId(useEnabled(this.enableCompRestoreId, this.compRestoreId)
         ? useEnabled(this.enableCompRestoreId, this.compRestoreId) : null)
       .foregroundEffect({
         radius: useEnabled(this.enableCompForegroundEffectRadius, this.compForegroundEffectRadius)
       })
       .foregroundBlurStyle(useEnabled(this.enableCompForegroundBlurStyleValue, this.compForegroundBlurStyleValue),
         {
           colorMode: useEnabled(this.enableCompForegroundBlurStyleOptionsColorMode,
             this.compForegroundBlurStyleOptionsColorMode),
           adaptiveColor: useEnabled(this.enableCompForegroundBlurStyleOptionsAdaptiveColor,
             this.compForegroundBlurStyleOptionsAdaptiveColor),
           blurOptions: {
             grayscale: [0, useEnabled(this.enableCompForegroundBlurStyleOptionsBlurOptions,
               this.compForegroundBlurStyleOptionsBlurOptions)]
           },
           scale: useEnabled(this.enableCompForegroundBlurStyleOptionsScale,
             this.compForegroundBlurStyleOptionsScale)
         })
       .clickEffect(useEnabled(this.enableCompClickEffect, this.compClickEffect) ? {
         level: useEnabled(this.enableCompClickEffectLevel, this.compClickEffectLevel),
         scale: useEnabled(this.enableCompClickEffectScale, this.compClickEffectScale)
       } : null)
       .accessibilityGroup(useEnabled(this.enableCompAccessibilityGroup, this.compAccessibilityGroup))
       .accessibilityText(useEnabled(this.enableCompAccessibilityText, this.compAccessibilityText))
       .accessibilityDescription(useEnabled(this.enableCompAccessibilityDescription,
         this.compAccessibilityDescription))
       .accessibilityLevel(useEnabled(this.enableCompAccessibilityLevel, this.compAccessibilityLevel))
       .bindMenu(this.MyMenu)
       .responseRegion({
         x: useEnabled(this.enableCompResponseRegionValueX, this.compResponseRegionValueX),
         y: useEnabled(this.enableCompResponseRegionValueY, this.compResponseRegionValueY),
         width: useEnabled(this.enableCompResponseRegionValueWidth, this.compResponseRegionValueWidth),
         height: useEnabled(this.enableCompResponseRegionValueHeight, this.compResponseRegionValueHeight)
       })
       .hitTestBehavior(useEnabled(this.enableCompHitTestBehavior, this.compHitTestBehavior))
       .bindSheet(
         useEnabled(this.enableCompBindSheetIsShow, this.compBindSheetIsShow) || this.compBindContentCoverIsShow,
         !this.compBindContentCoverIsShow ? this.bindSheetBuilder() : undefined,
         {
           shouldDismiss: () => {
             this.compBindSheetIsShow = false
           },
           height: useEnabled(this.enableCompBindSheetOptionsHeight, this.compBindSheetOptionsHeight),
           detents: useEnabled(this.enableCompBindSheetOptionsDetents, this.compBindSheetOptionsDetents),
           preferType: useEnabled(this.enableCompBindSheetOptionsPreferType, this.compBindSheetOptionsPreferType),
           showClose: useEnabled(this.enableCompBindSheetOptionsShowClose, this.compBindSheetOptionsShowClose),
           dragBar: useEnabled(this.enableCompBindSheetOptionsDragBar, this.compBindSheetOptionsDragBar),
           blurStyle: useEnabled(this.enableCompBindSheetOptionsBlurStyle, this.compBindSheetOptionsBlurStyle),
           maskColor: useEnabled(this.enableCompBindSheetOptionsMaskColor, this.compBindSheetOptionsMaskColor),
           title: {
             title: useEnabled(this.enableCompBindSheetOptionsTitleTitle, this.compBindSheetOptionsTitleTitle) ?
               'title' : '',
             subtitle: useEnabled(this.enableCompBindSheetOptionsTitleSubtitle,
               this.compBindSheetOptionsTitleSubtitle) ? 'subtitle' : ''
           },
           enableOutsideInteractive: useEnabled(this.enableCompBindSheetOptionsEnableOutsideInteractive,
             this.compBindSheetOptionsEnableOutsideInteractive),
           borderWidth: useEnabled(this.enableCompBindSheetOptionsBorderWidth,
             this.compBindSheetOptionsBorderWidth),
           borderColor: useEnabled(this.enableCompBindSheetOptionsBorderColor,
             this.compBindSheetOptionsBorderColor),
           borderStyle: useEnabled(this.enableCompBindSheetOptionsBorderStyle,
             this.compBindSheetOptionsBorderStyle),
           width: useEnabled(this.enableCompBindSheetOptionWidth, this.compBindSheetOptionsWidth),
           shadow: useEnabled(this.enableCompBindSheetOptionShadow, this.compBindSheetOptionShadow),
           mode: useEnabled(this.enableCompBindSheetOptionMode, this.compBindSheetOptionMode),
           scrollSizeMode: useEnabled(this.enableCompBindSheetOptionScrollSizeMode,
             this.compBindSheetOptionScrollSizeMode)
         }
       )
       .bindContentCover(useEnabled(this.enableCompBindContentCoverIsShow, this.compBindContentCoverIsShow),
         this.bindContentCoverBuilder(),
         {
           backgroundColor: Color.Orange,
           modalTransition: useEnabled(this.enableCompBindContentCoverOptionsModalTransition,
             this.compBindContentCoverOptionsModalTransition),
           transition: TransitionEffect.opacity(useEnabled(this.enableCompBindContentCoverOptionsTransitionOpacity,
             this.compBindContentCoverOptionsTransitionOpacity))
             .combine(TransitionEffect.translate({
               x: useEnabled(this.enableCompBindContentCoverOptionsTransitionTranslateX,
                 this.compBindContentCoverOptionsTransitionTranslateX),
               y: useEnabled(this.enableCompBindContentCoverOptionsTransitionTranslateY,
                 this.compBindContentCoverOptionsTransitionTranslateY),
               z: useEnabled(this.enableCompBindContentCoverOptionsTransitionTranslateZ,
                 this.compBindContentCoverOptionsTransitionTranslateZ),
             }))
             .combine(TransitionEffect.scale({
               x: useEnabled(this.enableCompBindContentCoverOptionsTransitionScaleX,
                 this.compBindContentCoverOptionsTransitionScaleX),
               y: useEnabled(this.enableCompBindContentCoverOptionsTransitionScaleY,
                 this.compBindContentCoverOptionsTransitionScaleY),
               z: useEnabled(this.enableCompBindContentCoverOptionsTransitionScaleZ,
                 this.compBindContentCoverOptionsTransitionScaleZ),
               centerX: useEnabled(this.enableCompBindContentCoverOptionsTransitionScaleCenterX,
                 this.compBindContentCoverOptionsTransitionScaleCenterX) + '%',
               centerY: useEnabled(this.enableCompBindContentCoverOptionsTransitionScaleCenterY,
                 this.compBindContentCoverOptionsTransitionScaleCenterY) + '%',
             }))
             .combine(TransitionEffect.rotate({
               x: useEnabled(this.enableCompBindContentCoverOptionsTransitionRotateX,
                 this.compBindContentCoverOptionsTransitionRotateX),
               y: useEnabled(this.enableCompBindContentCoverOptionsTransitionRotateY,
                 this.compBindContentCoverOptionsTransitionRotateY),
               z: useEnabled(this.enableCompBindContentCoverOptionsTransitionRotateZ,
                 this.compBindContentCoverOptionsTransitionRotateZ),
               angle:
               useEnabled(this.enableCompBindContentCoverOptionsTransitionRotateAngle,
                 this.compBindContentCoverOptionsTransitionRotateAngle),
               centerX:
               useEnabled(this.enableCompBindContentCoverOptionsTransitionRotateCenterX,
                 this.compBindContentCoverOptionsTransitionRotateCenterX) + '%',
               centerY:
               useEnabled(this.enableCompBindContentCoverOptionsTransitionRotateCenterY,
                 this.compBindContentCoverOptionsTransitionRotateCenterY) + '%',
               centerZ:
               useEnabled(this.enableCompBindContentCoverOptionsTransitionRotateCenterZ,
                 this.compBindContentCoverOptionsTransitionRotateCenterZ),
               perspective:
               useEnabled(this.enableCompBindContentCoverOptionsTransitionRotatePerspective,
                 this.compBindContentCoverOptionsTransitionRotatePerspective)
             }))
             .combine(TransitionEffect.move(
               useEnabled(this.enableCompBindContentCoverOptionsTransitionMove,
                 this.compBindContentCoverOptionsTransitionMove)))
             .animation({
               duration:
               useEnabled(this.enableCompBindContentCoverOptionsTransitionAnimationDuration,
                 this.compBindContentCoverOptionsTransitionAnimationDuration),
               tempo:
               useEnabled(this.enableCompBindContentCoverOptionsTransitionAnimationTempo,
                 this.compBindContentCoverOptionsTransitionAnimationTempo),
               curve:
               useEnabled(this.enableCompBindContentCoverOptionsTransitionAnimationCurve,
                 this.compBindContentCoverOptionsTransitionAnimationCurve),
               delay:
               useEnabled(this.enableCompBindContentCoverOptionsTransitionAnimationDelay,
                 this.compBindContentCoverOptionsTransitionAnimationDelay),
               iterations:
               useEnabled(this.enableCompBindContentCoverOptionsTransitionAnimationIterations,
                 this.compBindContentCoverOptionsTransitionAnimationIterations),
               playMode:
               useEnabled(this.enableCompBindContentCoverOptionsTransitionAnimationPlayMode,
                 this.compBindContentCoverOptionsTransitionAnimationPlayMode),
               expectedFrameRateRange: {
                 max:
                 useEnabled(this.enableCompBindContentCoverOptionsTransitionAnimationExpectedFrameRateRangeMax,
                   this.compBindContentCoverOptionsTransitionAnimationExpectedFrameRateRangeMax),
                 min:
                 useEnabled(this.enableCompBindContentCoverOptionsTransitionAnimationExpectedFrameRateRangeMin,
                   this.compBindContentCoverOptionsTransitionAnimationExpectedFrameRateRangeMin),
                 expected:
                 useEnabled(this.enableCompBindContentCoverOptionsTransitionAnimationExpectedFrameRateRangeExpected,
                   this.compBindContentCoverOptionsTransitionAnimationExpectedFrameRateRangeExpected),
               }
             })
         }
       )
       .obscured(useEnabled(this.enableCompObscured, this.compObscured))
       .monopolizeEvents(useEnabled(this.enableCompMonopolizeEvents, this.compMonopolizeEvents))
       .onHover((flag) => {
         if (flag) {
           this.getUIContext()
             .getCursorController()
             .setCursor(useEnabled(this.enableCompCursorControl, this.compCursorControl))
         } else {
           this.getUIContext().getCursorController().restoreDefault()
         }
       })
       .useEffect(useEnabled(this.enableCompUseEffect, this.compUseEffect))
       .onClick((event?: ClickEvent) => {
         this.handlePopup = !this.handlePopup
         this.compEventTriggeredLog('点击事件onClick触发');
       })
       .onTouch((event?: TouchEvent) => {
         this.compEventTriggeredLog('触摸事件onTouch触发');
       })
       .onAttach(() => {
         this.compEventTriggeredLog('挂载卸载事件onAttach触发');
       })
       .onDetach(() => {
         this.compEventTriggeredLog('挂载卸载事件onDetach触发');
       })
       .onAppear(() => {
         this.compEventTriggeredLog('挂载卸载事件onAppear触发');
       })
       .onDisAppear(() => {
         this.compEventTriggeredLog('挂载卸载事件onDisAppear触发');
       })
       .onKeyEvent((event: KeyEvent) => {
         this.compEventTriggeredLog('按键事件onKeyEvent触发');
       })
       .onFocus(() => {
         this.compEventTriggeredLog('焦点事件onFocus触发');
       })
       .onBlur(() => {
         this.compEventTriggeredLog('焦点事件onBlur触发');
       })
       .onMouse((event: MouseEvent) => {
         this.compEventTriggeredLog('鼠标事件onMouse触发');
       })
       .onHover((isHover: boolean, event: HoverEvent) => {
         this.compEventTriggeredLog('悬浮事件onHover触发');
       })
       .onAreaChange((oldValue: Area, newValue: Area) => {
         this.compEventTriggeredLog('组件区域变化事件onAreaChange触发')
       })
       .onSizeChange((oldValue: SizeOptions, newValue: SizeOptions) => {
         this.compEventTriggeredLog('组件尺寸变化事件onSizeChange触发')
       })
       .onVisibleAreaChange([0.0, 1.0], (isVisible: boolean, currentRatio: number) => {
         if (isVisible && currentRatio >= 1.0) {
           this.compEventTriggeredLog('组件可见区域变化事件onVisibleAreaChange触发,组件完全可见')
         } else if (!isVisible && currentRatio <= 0.0) {
           this.compEventTriggeredLog('组件可见区域变化事件onVisibleAreaChange触发,组件完全不可见')
         }
       })
       .keyboardShortcut('1', [ModifierKey.CTRL], () => {
         this.compEventTriggeredLog('组件快捷键事件keyboardShortcut触发,Ctrl+1')
       })
       .onChildTouchTest((touchInfo: Array<TouchTestInfo>) => {
         this.compEventTriggeredLog('自定义事件分发onChildTouchTest触发')
         return { strategy: TouchTestStrategy.DEFAULT };
       })
       .onTouchIntercept((event: TouchEvent) => {
         this.compEventTriggeredLog('自定义事件拦截onChildTouchTest触发')
         return HitTestMode.Default;
       })

   }.width('100%').height('100%')
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {
        RadioBlock({
          title: 'expandedLayoutOptions.isExtraRegionPerpendicular',
          isEnabled: $enableExpandedLayoutOptionsIsExtraRegionPerpendicular,
          value: $expandedLayoutOptionsIsExtraRegionPerpendicular,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })

        RadioBlock({
          title: 'expandedLayoutOptions.verticalSplitRatio',
          isEnabled: $enableExpandedLayoutOptionsVerticalSplitRatio,
          value: $expandedLayoutOptionsVerticalSplitRatio,
          dataSource: [
            { label: 'LAYOUT_1V1', value: PresetSplitRatio.LAYOUT_1V1 },
            { label: 'LAYOUT_2V3', value: PresetSplitRatio.LAYOUT_2V3 },
            { label: 'LAYOUT_3V2', value: PresetSplitRatio.LAYOUT_3V2 }
          ]
        })

        RadioBlock({
          title: 'expandedLayoutOptions.horizontalSplitRatio',
          isEnabled: $enableExpandedLayoutOptionsHorizontalSplitRatio,
          value: $expandedLayoutOptionsHorizontalSplitRatio,
          dataSource: [
            { label: 'LAYOUT_1V1', value: PresetSplitRatio.LAYOUT_1V1 },
            { label: 'LAYOUT_2V3', value: PresetSplitRatio.LAYOUT_2V3 },
            { label: 'LAYOUT_3V2', value: PresetSplitRatio.LAYOUT_3V2 }
          ]
        })

        RadioBlock({
          title: 'expandedLayoutOptions.extraRegionPosition',
          isEnabled: $enableExpandedLayoutOptionsExtraRegionPosition,
          value: $expandedLayoutOptionsExtraRegionPosition,
          dataSource: [
            { label: 'TOP', value: ExtraRegionPosition.TOP },
            { label: 'BOTTOM', value: ExtraRegionPosition.BOTTOM }
          ]
        })

        RadioBlock({
          title: 'hoverModeLayoutOptions.showExtraRegion',
          isEnabled: $enableHoverModeLayoutOptionsShowExtraRegion,
          value: $hoverModeLayoutOptionsShowExtraRegion,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })

        RadioBlock({
          title: 'hoverModeLayoutOptions.horizontalSplitRatio',
          isEnabled: $enableHoverModeLayoutOptionsHorizontalSplitRatio,
          value: $hoverModeLayoutOptionsHorizontalSplitRatio,
          dataSource: [
            { label: 'LAYOUT_1V1', value: PresetSplitRatio.LAYOUT_1V1 },
            { label: 'LAYOUT_2V3', value: PresetSplitRatio.LAYOUT_2V3 },
            { label: 'LAYOUT_3V2', value: PresetSplitRatio.LAYOUT_3V2 }
          ]
        })

        RadioBlock({
          title: 'hoverModeLayoutOptions.extraRegionPosition',
          isEnabled: $enableHoverModeLayoutOptionsExtraRegionPosition,
          value: $hoverModeLayoutOptionsExtraRegionPosition,
          dataSource: [
            { label: 'TOP', value: ExtraRegionPosition.TOP },
            { label: 'BOTTOM', value: ExtraRegionPosition.BOTTOM }
          ]
        })

        RadioBlock({
          title: 'foldedLayoutOptions.verticalSplitRatio',
          isEnabled: $enableFoldedLayoutOptionsVerticalSplitRatio,
          value: $foldedLayoutOptionsVerticalSplitRatio,
          dataSource: [
            { label: 'LAYOUT_1V1', value: PresetSplitRatio.LAYOUT_1V1 },
            { label: 'LAYOUT_2V3', value: PresetSplitRatio.LAYOUT_2V3 },
            { label: 'LAYOUT_3V2', value: PresetSplitRatio.LAYOUT_3V2 }
          ]
        })

        SliderBlock({
          title: 'animationOptions.duration',
          isEnabled: $enableAnimationOptionsDuration,
          value: $animationOptionsDuration,
          min: 0,
          max: 3000
        })

        SliderBlock({
          title: 'animationOptions.tempo',
          isEnabled: $enableAnimationOptionsTempo,
          value: $animationOptionsTempo,
          min: 0.5,
          max: 2.0,
          step: 0.1
        })

        RadioBlock({
          title: 'animationOptions.curve',
          isEnabled: $enableAnimationOptionsCurve,
          value: $animationOptionsCurve,
          dataSource: [
            { label: 'Linear', value: Curve.Linear },
            { label: 'Ease', value: Curve.Ease },
            { label: 'EaseIn', value: Curve.EaseIn },
            { label: 'EaseOut', value: Curve.EaseOut },
            { label: 'EaseInOut', value: Curve.EaseInOut },
            { label: 'FastOutSlowIn', value: Curve.FastOutSlowIn },
            { label: 'LinearOutSlowIn', value: Curve.LinearOutSlowIn },
            { label: 'FastOutLinearIn', value: Curve.FastOutLinearIn },
            { label: 'ExtremeDeceleration', value: Curve.ExtremeDeceleration },
            { label: 'Sharp', value: Curve.Sharp },
            { label: 'Rhythm', value: Curve.Rhythm },
            { label: 'Smooth', value: Curve.Smooth },
            { label: 'Friction', value: Curve.Friction }
          ]
        })

        SliderBlock({
          title: 'animationOptions.delay',
          isEnabled: $enableAnimationOptionsDelay,
          value: $animationOptionsDelay,
          min: -1000,
          max: 1000
        })

        SliderBlock({
          title: 'animationOptions.iterations',
          isEnabled: $enableAnimationOptionsIterations,
          value: $animationOptionsIterations,
          min: -1,
          max: 5
        })

        RadioBlock({
          title: 'animationOptions.playMode',
          isEnabled: $enableAnimationOptionsPlayMode,
          value: $animationOptionsPlayMode,
          dataSource: [
            { label: 'Normal', value: PlayMode.Normal },
            { label: 'Reverse', value: PlayMode.Reverse },
            { label: 'Alternate', value: PlayMode.Alternate },
            { label: 'AlternateReverse', value: PlayMode.AlternateReverse }
          ]
        })

        RadioBlock({
          title: 'animationOptions.finishCallbackType',
          isEnabled: $enableAnimationOptionsFinishCallbackType,
          value: $animationOptionsFinishCallbackType,
          dataSource: [
            { label: 'REMOVED', value: FinishCallbackType.REMOVED },
            { label: 'LOGICALLY', value: FinishCallbackType.LOGICALLY }
          ]
        })

        SliderBlock({
          title: 'animationOptions.expectedFrameRateRange.min',
          isEnabled: $enableAnimationOptionsExpectedFrameRateRangeMin,
          value: $animationOptionsExpectedFrameRateRangeMin,
          min: 10,
          max: 60
        })

        SliderBlock({
          title: 'animationOptions.expectedFrameRateRange.max',
          isEnabled: $enableAnimationOptionsExpectedFrameRateRangeMax,
          value: $animationOptionsExpectedFrameRateRangeMax,
          min: 60,
          max: 200
        })

        SliderBlock({
          title: 'animationOptions.expectedFrameRateRange.expected',
          isEnabled: $enableAnimationOptionsExpectedFrameRateRangeExpected,
          value: $animationOptionsExpectedFrameRateRangeExpected,
          min: 10,
          max: 200
        })

        SliderBlock({
          title: 'flexBasis',
          isEnabled: $enableCompFlexBasis,
          value: $compFlexBasis,
          min: 10,
          max: 200
        })

        RadioBlock({
          title: 'direction',
          isEnabled: $enableCompDirection,
          value: $compDirection,
          dataSource: [
            { label: 'Auto', value: Direction.Auto },
            { label: 'Ltr', value: Direction.Ltr },
            { label: 'Rtl', value: Direction.Rtl }
          ]
        })

        RadioBlock({
          title: 'background.align',
          isEnabled: $enableCompBackgroundAlign,
          value: $compBackgroundAlign,
          dataSource: [
            { label: 'TopStart', value: Alignment.TopStart },
            { label: 'Top', value: Alignment.Top },
            { label: 'TopEnd', value: Alignment.TopEnd },
            { label: 'Start', value: Alignment.Start },
            { label: 'Center', value: Alignment.Center },
            { label: 'End', value: Alignment.End },
            { label: 'BottomStart', value: Alignment.BottomStart },
            { label: 'Bottom', value: Alignment.Bottom },
            { label: 'BottomEnd', value: Alignment.BottomEnd }
          ]
        })

        ColorBlock({
          title: 'backgroundColor',
          isEnabled: $enableCompBackgroundColor,
          color: $compBackgroundColor
        })

        RadioBlock({
          title: 'backgroundImage.src',
          isEnabled: $enableCompBackgroundImageSrc,
          value: $enableCompBackgroundImageSrc,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })

        RadioBlock({
          title: 'backgroundImage.repeat',
          isEnabled: $enableCompBackgroundImageRepeat,
          value: $compBackgroundImageRepeat,
          dataSource: [
            { label: 'TopStart', value: ImageRepeat.NoRepeat },
            { label: 'TopStart', value: ImageRepeat.X },
            { label: 'TopStart', value: ImageRepeat.Y },
            { label: 'TopStart', value: ImageRepeat.XY },
          ]
        })

        RadioBlock({
          title: 'backgroundImageSize',
          isEnabled: $enableCompBackgroundImageSize,
          value: $compBackgroundImageSize,
          dataSource: [
            { label: 'Auto', value: ImageSize.Auto },
            { label: 'Cover', value: ImageSize.Cover },
            { label: 'Contain', value: ImageSize.Contain },
            { label: 'FILL', value: ImageSize.FILL }
          ]
        })

        SliderBlock({
          title: 'backgroundImagePosition.x',
          isEnabled: $enableCompBackgroundImagePositionX,
          value: $compBackgroundImagePositionX,
          min: 0,
          max: 300
        })

        SliderBlock({
          title: 'backgroundImagePosition.y',
          isEnabled: $enableCompBackgroundImagePositionY,
          value: $compBackgroundImagePositionY,
          min: 0,
          max: 300
        })

        RadioBlock({
          title: 'backgroundBlurStyle',
          isEnabled: $enableCompBackgroundBlurStyle,
          value: $compBackgroundBlurStyle,
          dataSource: [
            { label: 'Thin', value: BlurStyle.Thin },
            { label: 'Regular', value: BlurStyle.Regular },
            { label: 'Thick', value: BlurStyle.Thick },
            { label: 'BACKGROUND_THIN', value: BlurStyle.BACKGROUND_THIN },
            { label: 'BACKGROUND_REGULAR', value: BlurStyle.BACKGROUND_REGULAR },
            { label: 'BACKGROUND_THICK', value: BlurStyle.BACKGROUND_THICK },
            { label: 'BACKGROUND_ULTRA_THICK', value: BlurStyle.BACKGROUND_ULTRA_THICK },
            { label: 'NONE', value: BlurStyle.NONE },
            { label: 'COMPONENT_ULTRA_THIN', value: BlurStyle.COMPONENT_ULTRA_THIN },
            { label: 'COMPONENT_THIN', value: BlurStyle.COMPONENT_THIN },
            { label: 'COMPONENT_REGULAR', value: BlurStyle.COMPONENT_REGULAR },
            { label: 'COMPONENT_THICK', value: BlurStyle.COMPONENT_THICK },
            { label: 'COMPONENT_ULTRA_THICK', value: BlurStyle.COMPONENT_ULTRA_THICK }
          ]
        })

        RadioBlock({
          title: 'backgroundBlurStyleParams.options.params',
          isEnabled: $enableCompBackgroundBlurStyleParams,
          value: $enableCompBackgroundBlurStyleParams,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })

        if (this.enableCompBackgroundBlurStyleParams) {
          RadioBlock({
            title: 'backgroundBlurStyleParams.options.params.colorMode',
            isEnabled: $enableCompBackgroundBlurStyleParamsColorMode,
            value: $compBackgroundBlurStyleParamsColorMode,
            dataSource: [
              { label: 'SYSTEM', value: ThemeColorMode.SYSTEM },
              { label: 'LIGHT', value: ThemeColorMode.LIGHT },
              { label: 'DARK', value: ThemeColorMode.DARK }
            ]
          })

          RadioBlock({
            title: 'backgroundBlurStyleParams.options.params.adaptiveColor',
            isEnabled: $enableCompBackgroundBlurStyleParamsAdaptiveColor,
            value: $compBackgroundBlurStyleParamsAdaptiveColor,
            dataSource: [
              { label: 'DEFAULT', value: AdaptiveColor.DEFAULT },
              { label: 'AVERAGE', value: AdaptiveColor.AVERAGE }
            ]
          })

          SliderBlock({
            title: 'backgroundBlurStyleParams.options.params.blurOptions.left',
            isEnabled: $enableCompBackgroundBlurStyleParamsBlurOptionsLeft,
            value: $compBackgroundBlurStyleParamsBlurOptionsLeft,
            min: 0,
            max: 100
          })

          SliderBlock({
            title: 'backgroundBlurStyleParams.options.params.blurOptions.right',
            isEnabled: $enableCompBackgroundBlurStyleParamsBlurOptionsRight,
            value: $compBackgroundBlurStyleParamsBlurOptionsRight,
            min: 0,
            max: 100
          })

          SliderBlock({
            title: 'backgroundBlurStyleParams.options.params.scale',
            isEnabled: $enableCompBackgroundBlurStyleParamsScale,
            value: $compBackgroundBlurStyleParamsScale,
            step: 0.1,
            min: 0,
            max: 1
          })
        }

        SliderBlock({
          title: 'backdropBlur',
          isEnabled: $enableCompBackdropBlur,
          value: $compBackdropBlur,
          min: 0,
          max: 300
        })

        RadioBlock({
          title: 'backdropBlur.options.grayscale',
          isEnabled: $enableCompBackdropBlurGrayscale,
          value: $enableCompBackdropBlurGrayscale,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })

        if (this.enableCompBackdropBlurGrayscale) {
          SliderBlock({
            title: 'backdropBlur.options.grayscale.left',
            isEnabled: $enableCompBackdropBlurGrayscaleLeft,
            value: $compBackdropBlurGrayscaleLeft,
            min: 0,
            max: 127
          })

          SliderBlock({
            title: 'backdropBlur.options.grayscale.right',
            isEnabled: $enableCompBackdropBlurGrayscaleRight,
            value: $compBackdropBlurGrayscaleRight,
            min: 0,
            max: 127
          })
        }

        RadioBlock({
          title: 'backgroundEffect',
          isEnabled: $enableCompBackgroundEffect,
          value: $enableCompBackgroundEffect,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })

        if (this.enableCompBackgroundEffect) {
          SliderBlock({
            title: 'backgroundEffect.radius',
            isEnabled: $enableCompBackgroundEffectRadius,
            value: $compBackgroundEffectRadius,
            min: 0,
            max: 100
          })

          SliderBlock({
            title: 'backgroundEffect.saturation',
            isEnabled: $enableCompBackgroundEffectSaturation,
            value: $compBackgroundEffectSaturation,
            min: 0,
            max: 50
          })

          SliderBlock({
            title: 'backgroundEffect.brightness',
            isEnabled: $enableCompBackgroundEffectBrightness,
            value: $compBackgroundEffectBrightness,
            min: 0,
            max: 2
          })

          ColorBlock({
            title: 'backgroundEffect.color',
            isEnabled: $enableCompBackgroundEffectColor,
            color: $compBackgroundEffectColor,
          })

          RadioBlock({
            title: 'backgroundEffect.adaptiveColor',
            isEnabled: $enableCompBackgroundEffectAdaptiveColor,
            value: $compBackgroundEffectAdaptiveColor,
            dataSource: [
              { label: 'DEFAULT', value: AdaptiveColor.DEFAULT },
              { label: 'AVERAGE', value: AdaptiveColor.AVERAGE }
            ]
          })

          SliderBlock({
            title: 'backgroundEffect.blurOptions.grayscale.left',
            isEnabled: $enableCompBackgroundEffectBlurOptionsGrayscaleLeft,
            value: $compBackgroundEffectBlurOptionsGrayscaleLeft,
            min: 0,
            max: 127
          })

          SliderBlock({
            title: 'backgroundEffect.blurOptions.grayscale.right',
            isEnabled: $enableCompBackgroundEffectBlurOptionsGrayscaleRight,
            value: $compBackgroundEffectBlurOptionsGrayscaleRight,
            min: 0,
            max: 127
          })
        }

        RadioBlock({
          title: 'backgroundImageResizable',
          isEnabled: $enableCompBackgroundImageResizable,
          value: $enableCompBackgroundImageResizable,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })

        if (this.enableCompBackgroundImageResizable) {
          SliderBlock({
            title: 'backgroundImageResizable.slice.top',
            isEnabled: $enableCompBackgroundImageResizableSliceTop,
            value: $compBackgroundImageResizableSliceTop,
            min: 0,
            max: 300
          })

          SliderBlock({
            title: 'backgroundImageResizable.slice.bottom',
            isEnabled: $enableCompBackgroundImageResizableSliceBottom,
            value: $compBackgroundImageResizableSliceBottom,
            min: 0,
            max: 300
          })

          SliderBlock({
            title: 'backgroundImageResizable.slice.left',
            isEnabled: $enableCompBackgroundImageResizableSliceLeft,
            value: $compBackgroundImageResizableSliceLeft,
            min: 0,
            max: 300
          })

          SliderBlock({
            title: 'backgroundImageResizable.slice.right',
            isEnabled: $enableCompBackgroundImageResizableSliceRight,
            value: $compBackgroundImageResizableSliceRight,
            min: 0,
            max: 300
          })

          RadioBlock({
            title: 'backgroundImageResizable.lattice',
            isEnabled: $enableCompBackgroundImageResizableLattice,
            value: $enableCompBackgroundImageResizableLattice,
            dataSource: [
              { label: 'true', value: true },
              { label: 'false', value: false }
            ]
          })
          if (this.enableCompBackgroundImageResizableLattice) {
            RadioBlock({
              title: 'backgroundImageResizable.lattice.xDivs',
              isEnabled: $enableCompBackgroundImageResizableLatticeXDivs,
              value: $compBackgroundImageResizableLatticeXDivs,
              dataSource: [
                { label: '[1, 2, 3]', value: [1, 2, 3] },
                { label: '[3, 4, 5]', value: [3, 4, 5] },
                { label: '[5, 6, 3]', value: [5, 6, 3] },
              ]
            })

            RadioBlock({
              title: 'backgroundImageResizable.lattice.yDivs',
              isEnabled: $enableCompBackgroundImageResizableLatticeYDivs,
              value: $compBackgroundImageResizableLatticeYDivs,
              dataSource: [
                { label: '[1, 2, 3]', value: [1, 2, 3] },
                { label: '[3, 4, 5]', value: [3, 4, 5] },
                { label: '[5, 6, 3]', value: [5, 6, 3] },
              ]
            })

            SliderBlock({
              title: 'backgroundImageResizable.lattice.fXCount',
              isEnabled: $enableCompBackgroundImageResizableLatticeFXCount,
              value: $compBackgroundImageResizableLatticeFXCount,
              min: 0,
              max: 5
            })

            SliderBlock({
              title: 'backgroundImageResizable.lattice.fYCount',
              isEnabled: $enableCompBackgroundImageResizableLatticeFYCount,
              value: $compBackgroundImageResizableLatticeFYCount,
              min: 0,
              max: 5
            })

            RadioBlock({
              title: 'backgroundImageResizable.lattice.fBounds',
              isEnabled: $enableCompBackgroundImageResizableLatticeFBounds,
              value: $enableCompBackgroundImageResizableLatticeFBounds,
              dataSource: [
                { label: 'true', value: true },
                { label: 'false', value: false }
              ]
            })

            if (this.enableCompBackgroundImageResizableLatticeFBounds) {
              SliderBlock({
                title: 'backgroundImageResizable.lattice.fBounds.left',
                isEnabled: $enableCompBackgroundImageResizableLatticeFBoundsLeft,
                value: $compBackgroundImageResizableLatticeFBoundsLeft,
                min: 0,
                max: 100
              })

              SliderBlock({
                title: 'backgroundImageResizable.lattice.fBounds.top',
                isEnabled: $enableCompBackgroundImageResizableLatticeFBoundsTop,
                value: $compBackgroundImageResizableLatticeFBoundsTop,
                min: 0,
                max: 100
              })

              SliderBlock({
                title: 'backgroundImageResizable.lattice.fBounds.right',
                isEnabled: $enableCompBackgroundImageResizableLatticeFBoundsRight,
                value: $compBackgroundImageResizableLatticeFBoundsRight,
                min: 0,
                max: 100
              })

              SliderBlock({
                title: 'backgroundImageResizable.lattice.fBounds.bottom',
                isEnabled: $enableCompBackgroundImageResizableLatticeFBoundsBottom,
                value: $compBackgroundImageResizableLatticeFBoundsBottom,
                min: 0,
                max: 100
              })

            }

            RadioBlock({
              title: 'backgroundImageResizable.lattice.fColors',
              isEnabled: $enableCompBackgroundImageResizableLatticeFColors,
              value: $compBackgroundImageResizableLatticeFColors,
              dataSource: [
                { label: '[{alpha:0,red:0,green:0,blue:0}]', value: ['#00000000'] },
                { label: '[{alpha:100,red:100,green:100,blue:100}]', value: ['#64646464'] },
                { label: '[{alpha:255,red:255,green:255,blue:255}]', value: ['#ffffffff'] }
              ]
            })
          }
        }

        RadioBlock({
          title: 'clip',
          isEnabled: $enableCompClip,
          value: $compClip,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })

        RadioBlock({
          title: 'mask',
          isEnabled: $enableCompMask,
          value: $enableCompMask,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })

        if (this.enableCompMask) {

          SliderBlock({
            title: 'mask.value',
            isEnabled: $enableCompMaskValue,
            value: $compMaskValue,
            min: 0,
            max: 100
          })

          ColorBlock({
            title: 'mask.color',
            isEnabled: $enableCompMaskColor,
            color: $compMaskColor
          })
        }

        SliderBlock({
          title: 'blur.value',
          isEnabled: $enableCompBlurValue,
          value: $compBlurValue,
          min: 0,
          max: 5
        })

        SliderBlock({
          title: 'blur.options.grayscale.number1',
          isEnabled: $enableCompBlurOptionsNumber1,
          value: $compBlurOptionsNumber1,
          min: 0,
          max: 127
        })

        SliderBlock({
          title: 'blur.options.grayscale.number2',
          isEnabled: $enableCompBlurOptionsNumber2,
          value: $compBlurOptionsNumber2,
          min: 0,
          max: 127
        })

        SliderBlock({
          title: 'shadow.value.radius',
          isEnabled: $enableCompShadowValueRadius,
          value: $compShadowValueRadius,
          min: 0,
          max: 100
        })

        RadioBlock({
          title: 'shadow.value.type',
          isEnabled: $enableCompShadowValueType,
          value: $compShadowValueType,
          dataSource: [
            { label: 'COLOR', value: ShadowType.COLOR },
            { label: 'BLUR', value: ShadowType.BLUR },
          ]
        })

        ColorBlock({
          title: 'shadow.value.color',
          isEnabled: $enableCompShadowValueColor,
          color: $compShadowValueColor
        })

        SliderBlock({
          title: 'shadow.value.offsetX',
          isEnabled: $enableCompShadowValueOffsetX,
          value: $compShadowValueOffsetX,
          min: 0,
          max: 100
        })

        SliderBlock({
          title: 'shadow.value.offsetY',
          isEnabled: $enableCompShadowValueOffsetY,
          value: $compShadowValueOffsetY,
          min: 0,
          max: 100
        })

        RadioBlock({
          title: 'shadow.value.fill',
          isEnabled: $enableCompShadowValueFill,
          value: $compShadowValueFill,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false },
          ]
        })

        SliderBlock({
          title: 'grayscale',
          isEnabled: $enableCompGrayscale,
          value: $compGrayscale,
          min: 0,
          max: 1,
          step: 0.1
        })

        SliderBlock({
          title: 'brightness',
          isEnabled: $enableCompBrightness,
          value: $compBrightness,
          min: 0,
          max: 2,
          step: 0.1
        })

        SliderBlock({
          title: 'saturate',
          isEnabled: $enableCompSaturate,
          value: $compSaturate,
          min: 0,
          max: 50
        })

        SliderBlock({
          title: 'contrast',
          isEnabled: $enableCompContrast,
          value: $compContrast,
          min: 0,
          max: 10
        })

        SliderBlock({
          title: 'invert',
          isEnabled: $enableCompInvert,
          value: $compInvert,
          min: 0,
          max: 1,
          step: 0.1
        })

        SliderBlock({
          title: 'sepia',
          isEnabled: $enableCompSepia,
          value: $compSepia,
          min: 0,
          max: 1,
          step: 0.1
        })

        SliderBlock({
          title: 'hueRotate',
          isEnabled: $enableCompHueRotate,
          value: $compHueRotate,
          min: -180,
          max: 180
        })

        ColorBlock({
          title: 'colorBlend',
          isEnabled: $enableCompColorBlend,
          color: $compColorBlend
        })

        CompSizeBlocks({
          enableCompWidth: $enableCompWidth,
          compWidth: $compWidth,
          enableCompHeight: $enableCompHeight,
          compHeight: $compHeight,
          enableCompPadding: $enableCompPadding,
          compPadding: $compPadding,
          enableCompMargin: $enableCompMargin,
          compMargin: $compMargin,
          enableCompConstraintSize: $enableCompConstraintSize,
          enableCompConstraintSizeMinWidth: $enableCompConstraintSizeMinWidth,
          compConstraintSizeMinWidth: $compConstraintSizeMinWidth,
          enableCompConstraintSizeMinHeight: $enableCompConstraintSizeMinHeight,
          compConstraintSizeMinHeight: $compConstraintSizeMinHeight,
          enableCompConstraintSizeMaxWidth: $enableCompConstraintSizeMaxWidth,
          compConstraintSizeMaxWidth: $compConstraintSizeMaxWidth,
          enableCompConstraintSizeMaxHeight: $enableCompConstraintSizeMaxHeight,
          compConstraintSizeMaxHeight: $compConstraintSizeMaxHeight
        })

        CompLocationBlocks({
          enableCompPosition: $enableCompPosition,
          enableCompPositionTop: $enableCompPositionTop,
          compPositionTop: $compPositionTop,
          enableCompPositionBottom: $enableCompPositionBottom,
          compPositionBottom: $compPositionBottom,
          enableCompPositionLeft: $enableCompPositionLeft,
          compPositionLeft: $compPositionLeft,
          enableCompPositionRight: $enableCompPositionRight,
          compPositionRight: $compPositionRight,
          enableCompMarkAnchor: $enableCompMarkAnchor,
          enableCompMarkAnchorX: $enableCompMarkAnchorX,
          compMarkAnchorX: $compMarkAnchorX,
          enableCompMarkAnchorY: $enableCompMarkAnchorY,
          compMarkAnchorY: $compMarkAnchorY,
          enableCompOffset: $enableCompOffset,
          enableCompOffsetX: $enableCompOffsetX,
          compOffsetX: $compOffsetX,
          enableCompOffsetY: $enableCompOffsetY,
          compOffsetY: $compOffsetY
        })

        CompLayoutConstraintsBlocks({
          enableCompAspectRatio: $enableCompAspectRatio,
          compAspectRatio: $compAspectRatio,
          enableCompPixelRound: $enableCompPixelRound,
          enableCompPixelRoundStart: $enableCompPixelRoundStart,
          compPixelRoundStart: $compPixelRoundStart,
          enableCompPixelRoundTop: $enableCompPixelRoundTop,
          compPixelRoundTop: $compPixelRoundTop,
          enableCompPixelRoundEnd: $enableCompPixelRoundEnd,
          compPixelRoundEnd: $compPixelRoundEnd,
          enableCompPixelRoundBottom: $enableCompPixelRoundBottom,
          compPixelRoundBottom: $compPixelRoundBottom
        })

        CompBorderBlocks({
          enableCompBorderWidth: $enableCompBorderWidth,
          compBorderWidth: $compBorderWidth,
          enableCompBorderColor: $enableCompBorderColor,
          compBorderColor: $compBorderColor,
          enableCompBorderRadius: $enableCompBorderRadius,
          compBorderRadius: $compBorderRadius,
          enableCompBorderStyle: $enableCompBorderStyle,
          compBorderStyle: $compBorderStyle,
          enableCompBorderDashGapLeft: $enableCompBorderDashGapLeft,
          compBorderDashGapLeft: $compBorderDashGapLeft,
          enableCompBorderDashGapRight: $enableCompBorderDashGapRight,
          compBorderDashGapRight: $compBorderDashGapRight,
          enableCompBorderDashGapTop: $enableCompBorderDashGapTop,
          compBorderDashGapTop: $compBorderDashGapTop,
          enableCompBorderDashGapBottom: $enableCompBorderDashGapBottom,
          compBorderDashGapBottom: $compBorderDashGapBottom,
          enableCompBorderDashWidthLeft: $enableCompBorderDashWidthLeft,
          compBorderDashWidthLeft: $compBorderDashWidthLeft,
          enableCompBorderDashWidthRight: $enableCompBorderDashWidthRight,
          compBorderDashWidthRight: $compBorderDashWidthRight,
          enableCompBorderDashWidthTop: $enableCompBorderDashWidthTop,
          compBorderDashWidthTop: $compBorderDashWidthTop,
          enableCompBorderDashWidthBottom: $enableCompBorderDashWidthBottom,
          compBorderDashWidthBottom: $compBorderDashWidthBottom
        })

        CompBorderImageBlocks({
          enableCompBorderImage: $enableCompBorderImage,
          enableCompBorderImageSource: $enableCompBorderImageSource,
          enableCompBorderImageSlice: $enableCompBorderImageSlice,
          enableCompBorderImageSliceTop: $enableCompBorderImageSliceTop,
          compBorderImageSliceTop: $compBorderImageSliceTop,
          enableCompBorderImageSliceBottom: $enableCompBorderImageSliceBottom,
          compBorderImageSliceBottom: $compBorderImageSliceBottom,
          enableCompBorderImageSliceLeft: $enableCompBorderImageSliceLeft,
          compBorderImageSliceLeft: $compBorderImageSliceLeft,
          enableCompBorderImageSliceRight: $enableCompBorderImageSliceRight,
          compBorderImageSliceRight: $compBorderImageSliceRight,
          enableCompBorderImageWidth: $enableCompBorderImageWidth,
          enableCompBorderImageWidthTop: $enableCompBorderImageWidthTop,
          compBorderImageWidthTop: $compBorderImageWidthTop,
          enableCompBorderImageWidthBottom: $enableCompBorderImageWidthBottom,
          compBorderImageWidthBottom: $compBorderImageWidthBottom,
          enableCompBorderImageWidthLeft: $enableCompBorderImageWidthLeft,
          compBorderImageWidthLeft: $compBorderImageWidthLeft,
          enableCompBorderImageWidthRight: $enableCompBorderImageWidthRight,
          compBorderImageWidthRight: $compBorderImageWidthRight,
          enableCompBorderImageOutset: $enableCompBorderImageOutset,
          enableCompBorderImageOutsetTop: $enableCompBorderImageOutsetTop,
          compBorderImageOutsetTop: $compBorderImageOutsetTop,
          enableCompBorderImageOutsetBottom: $enableCompBorderImageOutsetBottom,
          compBorderImageOutsetBottom: $compBorderImageOutsetBottom,
          enableCompBorderImageOutsetLeft: $enableCompBorderImageOutsetLeft,
          compBorderImageOutsetLeft: $compBorderImageOutsetLeft,
          enableCompBorderImageOutsetRight: $enableCompBorderImageOutsetRight,
          compBorderImageOutsetRight: $compBorderImageOutsetRight,
          enableCompBorderImageRepeat: $enableCompBorderImageRepeat,
          compBorderImageRepeat: $compBorderImageRepeat,
          enableCompBorderImageFill: $enableCompBorderImageFill,
          compBorderImageFill: $compBorderImageFill
        })

        CompOpacityBlocks({
          enableCompOpacity: $enableCompOpacity,
          compOpacity: $compOpacity
        })

        CompVisibilityBlocks({
          enableCompVisibility: $enableCompVisibility,
          compVisibility: $compVisibility
        })

        CompEnabledBlocks({
          enableCompEnabled: $enableCompEnabled,
          compEnabled: $compEnabled
        })

        CompOverlayBlocks({
          enableCompOverlay: $enableCompOverlay,
          compOverlay: $compOverlay,
          enableCompOverlayOptions: $enableCompOverlayOptions,
          enableCompOverlayOptionsAlign: $enableCompOverlayOptionsAlign,
          compOverlayOptionsAlign: $compOverlayOptionsAlign,
          enableCompOverlayOptionsOffsetX: $enableCompOverlayOptionsOffsetX,
          compOverlayOptionsOffsetX: $compOverlayOptionsOffsetX,
          enableCompOverlayOptionsOffsetY: $enableCompOverlayOptionsOffsetY,
          compOverlayOptionsOffsetY: $compOverlayOptionsOffsetY
        })

        CompZOrderControlBlocks({
          enableCompZIndex: $enableCompZIndex,
          compZIndex: $compZIndex
        })

        CompTransformationBlocks({
          enableCompRotate: $enableCompRotate,
          enableCompRotateX: $enableCompRotateX,
          compRotateX: $compRotateX,
          enableCompRotateY: $enableCompRotateY,
          compRotateY: $compRotateY,
          enableCompRotateZ: $enableCompRotateZ,
          compRotateZ: $compRotateZ,
          enableCompRotateAngle: $enableCompRotateAngle,
          compRotateAngle: $compRotateAngle,
          enableCompRotateCenterX: $enableCompRotateCenterX,
          compRotateCenterX: $compRotateCenterX,
          enableCompRotateCenterY: $enableCompRotateCenterY,
          compRotateCenterY: $compRotateCenterY,
          enableCompRotateCenterZ: $enableCompRotateCenterZ,
          compRotateCenterZ: $compRotateCenterZ,
          enableCompRotatePerspective: $enableCompRotatePerspective,
          compRotatePerspective: $compRotatePerspective,
          enableCompTranslate: $enableCompTranslate,
          enableCompTranslateX: $enableCompTranslateX,
          compTranslateX: $compTranslateX,
          enableCompTranslateY: $enableCompTranslateY,
          compTranslateY: $compTranslateY,
          enableCompTranslateZ: $enableCompTranslateZ,
          compTranslateZ: $compTranslateZ,
          enableCompScale: $enableCompScale,
          enableCompScaleX: $enableCompScaleX,
          compScaleX: $compScaleX,
          enableCompScaleY: $enableCompScaleY,
          compScaleY: $compScaleY,
          enableCompScaleZ: $enableCompScaleZ,
          compScaleZ: $compScaleZ,
          enableCompScaleCenterX: $enableCompScaleCenterX,
          compScaleCenterX: $compScaleCenterX,
          enableCompScaleCenterY: $enableCompScaleCenterY,
          compScaleCenterY: $compScaleCenterY,
          enableCompTransform: $enableCompTransform
        })

        //linearGradient
        CompGradientColorBlocks({
          enableCompLinearGradientAngle: $enableCompLinearGradientAngle,
          compLinearGradientAngle: $compLinearGradientAngle,
          enableCompLinearGradientDirection: $enableCompLinearGradientDirection,
          compLinearGradientDirection: $compLinearGradientDirection,
          enableCompLinearGradientColors1: $enableCompLinearGradientColors1,
          compLinearGradientColors1: $compLinearGradientColors1,
          enableCompLinearGradientColorsNumber1: $enableCompLinearGradientColorsNumber1,
          compLinearGradientColorsNumber1: $compLinearGradientColorsNumber1,
          enableCompLinearGradientColors2: $enableCompLinearGradientColors2,
          compLinearGradientColors2: $compLinearGradientColors2,
          enableCompLinearGradientColorsNumber2: $enableCompLinearGradientColorsNumber2,
          compLinearGradientColorsNumber2: $compLinearGradientColorsNumber2,
          enableCompLinearGradientRepeating: $enableCompLinearGradientRepeating,
          compLinearGradientRepeating: $compLinearGradientRepeating,
        })

        CompPopupControlBlocks({
          enableCompBindPopupType: $enableCompBindPopupType,
          compBindPopupType: $compBindPopupType,
          handlePopup: $handlePopup,
          enableCompPopupType: $enableCompPopupType,
          compPopupType: $compPopupType,
          enableCompBindPopupArrowOffset: $enableCompBindPopupArrowOffset,
          compBindPopupArrowOffset: $compBindPopupArrowOffset,
          enableCompBindPopupShowInSubWindow: $enableCompBindPopupShowInSubWindow,
          compBindPopupShowInSubWindow: $compBindPopupShowInSubWindow,
          enableCompBindPopupMaskType: $enableCompBindPopupMaskType,
          compBindPopupMaskType: $compBindPopupMaskType,
          enableCompBindPopupMaskBoolean: $enableCompBindPopupMaskBoolean,
          compBindPopupMaskBoolean: $compBindPopupMaskBoolean,
          enableCompBindPopupMaskColor: $enableCompBindPopupMaskColor,
          compBindPopupMaskColor: $compBindPopupMaskColor,
          enableCompBindPopupMessageOptionsTextColor: $enableCompBindPopupMessageOptionsTextColor,
          compBindPopupMessageOptionsTextColor: $compBindPopupMessageOptionsTextColor,
          enableCompBindPopupMessageOptionsFontSize: $enableCompBindPopupMessageOptionsFontSize,
          compBindPopupMessageOptionsFontSize: $compBindPopupMessageOptionsFontSize,
          enableCompBindPopupMessageOptionsFontWeight: $enableCompBindPopupMessageOptionsFontWeight,
          compBindPopupMessageOptionsFontWeight: $compBindPopupMessageOptionsFontWeight,
          enableCompBindPopupMessageOptionsFontStyle: $enableCompBindPopupMessageOptionsFontStyle,
          compBindPopupMessageOptionsFontStyle: $compBindPopupMessageOptionsFontStyle,
          enableCompBindPopupTargetSpace: $enableCompBindPopupTargetSpace,
          compBindPopupTargetSpace: $compBindPopupTargetSpace,
          enableCompBindPopupPlacement: $enableCompBindPopupPlacement,
          compBindPopupPlacement: $compBindPopupPlacement,
          enableCompBindPopupOffsetX: $enableCompBindPopupOffsetX,
          compBindPopupOffsetX: $compBindPopupOffsetX,
          enableCompBindPopupOffsetY: $enableCompBindPopupOffsetY,
          compBindPopupOffsetY: $compBindPopupOffsetY,
          enableCompBindPopupEnableArrow: $enableCompBindPopupEnableArrow,
          compBindPopupEnableArrow: $compBindPopupEnableArrow,
          enableCompBindPopupPopupColor: $enableCompBindPopupPopupColor,
          compBindPopupPopupColor: $compBindPopupPopupColor,
          enableCompBindPopupAutoCancel: $enableCompBindPopupAutoCancel,
          compBindPopupAutoCancel: $compBindPopupAutoCancel,
          enableCompBindPopupWidth: $enableCompBindPopupWidth,
          compBindPopupWidth: $compBindPopupWidth,
          enableCompBindPopupArrowPointPosition: $enableCompBindPopupArrowPointPosition,
          compBindPopupArrowPointPosition: $compBindPopupArrowPointPosition,
          enableCompBindPopupArrowWidth: $enableCompBindPopupArrowWidth,
          compBindPopupArrowWidth: $compBindPopupArrowWidth,
          enableCompBindPopupArrowHeight: $enableCompBindPopupArrowHeight,
          compBindPopupArrowHeight: $compBindPopupArrowHeight,
          enableCompBindPopupRadius: $enableCompBindPopupRadius,
          compBindPopupRadius: $compBindPopupRadius,
          enableCompBindPopupShadowType: $enableCompBindPopupShadowType,
          compBindPopupShadowType: $compBindPopupShadowType,
          enableCompBindPopupShadowStyle: $enableCompBindPopupShadowStyle,
          compBindPopupShadowStyle: $compBindPopupShadowStyle,
          enableCompBindPopupShadowOptionsRadius: $enableCompBindPopupShadowOptionsRadius,
          compBindPopupShadowOptionsRadius: $compBindPopupShadowOptionsRadius,
          enableCompBindPopupShadowOptionsType: $enableCompBindPopupShadowOptionsType,
          compBindPopupShadowOptionsType: $compBindPopupShadowOptionsType,
          enableCompBindPopupShadowOptionsColor: $enableCompBindPopupShadowOptionsColor,
          compBindPopupShadowOptionsColor: $compBindPopupShadowOptionsColor,
          enableCompBindPopupShadowOptionsOffsetX: $enableCompBindPopupShadowOptionsOffsetX,
          compBindPopupShadowOptionsOffsetX: $compBindPopupShadowOptionsOffsetX,
          enableCompBindPopupShadowOptionsOffsetY: $enableCompBindPopupShadowOptionsOffsetY,
          compBindPopupShadowOptionsOffsetY: $compBindPopupShadowOptionsOffsetY,
          enableCompBindPopupShadowOptionsFill: $enableCompBindPopupShadowOptionsFill,
          compBindPopupShadowOptionsFill: $compBindPopupShadowOptionsFill,
          enableCompBindPopupBackgroundBlurStyle: $enableCompBindPopupBackgroundBlurStyle,
          compBindPopupBackgroundBlurStyle: $compBindPopupBackgroundBlurStyle,
          enableTransitionTransitionEffect: $enableTransitionTransitionEffect,
          transitionTransitionEffect: $transitionTransitionEffect,
          enableCompBindPopupTransitionOpacity: $enableCompBindPopupTransitionOpacity,
          compBindPopupTransitionOpacity: $compBindPopupTransitionOpacity,
          enableCompBindPopupTransitionTranslateX: $enableCompBindPopupTransitionTranslateX,
          compBindPopupTransitionTranslateX: $compBindPopupTransitionTranslateX,
          enableCompBindPopupTransitionTranslateY: $enableCompBindPopupTransitionTranslateY,
          compBindPopupTransitionTranslateY: $compBindPopupTransitionTranslateY,
          enableCompBindPopupTransitionTranslateZ: $enableCompBindPopupTransitionTranslateZ,
          compBindPopupTransitionTranslateZ: $compBindPopupTransitionTranslateZ,
          enableCompBindPopupTransitionScaleX: $enableCompBindPopupTransitionScaleX,
          compBindPopupTransitionScaleX: $compBindPopupTransitionScaleX,
          enableCompBindPopupTransitionScaleY: $enableCompBindPopupTransitionScaleY,
          compBindPopupTransitionScaleY: $compBindPopupTransitionScaleY,
          enableCompBindPopupTransitionScaleZ: $enableCompBindPopupTransitionScaleZ,
          compBindPopupTransitionScaleZ: $compBindPopupTransitionScaleZ,
          enableCompBindPopupTransitionScaleCenterX: $enableCompBindPopupTransitionScaleCenterX,
          compBindPopupTransitionScaleCenterX: $compBindPopupTransitionScaleCenterX,
          enableCompBindPopupTransitionScaleCenterY: $enableCompBindPopupTransitionScaleCenterY,
          compBindPopupTransitionScaleCenterY: $compBindPopupTransitionScaleCenterY,
          enableCompBindPopupTransitionRotateX: $enableCompBindPopupTransitionRotateX,
          compBindPopupTransitionRotateX: $compBindPopupTransitionRotateX,
          enableCompBindPopupTransitionRotateY: $enableCompBindPopupTransitionRotateY,
          compBindPopupTransitionRotateY: $compBindPopupTransitionRotateY,
          enableCompBindPopupTransitionRotateZ: $enableCompBindPopupTransitionRotateZ,
          compBindPopupTransitionRotateZ: $compBindPopupTransitionRotateZ,
          enableCompBindPopupTransitionRotateAngle: $enableCompBindPopupTransitionRotateAngle,
          compBindPopupTransitionRotateAngle: $compBindPopupTransitionRotateAngle,
          enableCompBindPopupTransitionRotateCenterX: $enableCompBindPopupTransitionRotateCenterX,
          compBindPopupTransitionRotateCenterX: $compBindPopupTransitionRotateCenterX,
          enableCompBindPopupTransitionRotateCenterY: $enableCompBindPopupTransitionRotateCenterY,
          compBindPopupTransitionRotateCenterY: $compBindPopupTransitionRotateCenterY,
          enableCompBindPopupTransitionRotateCenterZ: $enableCompBindPopupTransitionRotateCenterZ,
          compBindPopupTransitionRotateCenterZ: $compBindPopupTransitionRotateCenterZ,
          enableCompBindPopupTransitionRotatePerspective: $enableCompBindPopupTransitionRotatePerspective,
          compBindPopupTransitionRotatePerspective: $compBindPopupTransitionRotatePerspective,
          enableCompBindPopupTransitionMove: $enableCompBindPopupTransitionMove,
          compBindPopupTransitionMove: $compBindPopupTransitionMove,
        })

        //bindMenu
        CompMenuControlBlocks({
          enableCompBindMenuStartIcon: $enableCompBindMenuStartIcon,
          compBindMenuStartIcon: $compBindMenuStartIcon,
          compBindMenuStartIconStr: $compBindMenuStartIconStr,
          enableCompBindMenuEndIcon: $enableCompBindMenuEndIcon,
          compBindMenuEndIcon: $compBindMenuEndIcon,
          compBindMenuEndIconStr: $compBindMenuEndIconStr,
          enableCompBindMenuSelect: $enableCompBindMenuSelect,
          compBindMenuSelect: $compBindMenuSelect,
          enableCompBindMenuSelect2: $enableCompBindMenuSelect2,
          compBindMenuSelect2: $compBindMenuSelect2,
          enableCompBindMenuSelect3: $enableCompBindMenuSelect3,
          compBindMenuSelect3: $compBindMenuSelect3,
          enableCompBindMenuSelect4: $enableCompBindMenuSelect4,
          compBindMenuSelect4: $compBindMenuSelect4,
          enableCompBindMenuDirection: $enableCompBindMenuDirection,
          compBindMenuComDirection: $compBindMenuComDirection,
          enableCompBindMenuSelectIcon: $enableCompBindMenuSelectIcon,
          compBindMenuSelectIcon: $compBindMenuSelectIcon,
          enableCompBindMenuSelectIcon2: $enableCompBindMenuSelectIcon2,
          compBindMenuSelectIcon2: $compBindMenuSelectIcon2,
          enableCompBindMenuSelectIcon3: $enableCompBindMenuSelectIcon3,
          compBindMenuSelectIcon3: $compBindMenuSelectIcon3,
          enableCompBindMenuSelectIcon4: $enableCompBindMenuSelectIcon4,
          compBindMenuSelectIcon4: $compBindMenuSelectIcon4,
          enableCompBindMenuMenuFontSize: $enableCompBindMenuMenuFontSize,
          compBindMenuMenuFontSize: $compBindMenuMenuFontSize,
          enableCompBindMenuMenuFontWeight: $enableCompBindMenuMenuFontWeight,
          compBindMenuMenuFontWeight: $compBindMenuMenuFontWeight,
          enableCompBindMenuMenuFontStyle: $enableCompBindMenuMenuFontStyle,
          compBindMenuMenuFontStyle: $compBindMenuMenuFontStyle,
          enableCompBindMenuMenuFontColor: $enableCompBindMenuMenuFontColor,
          compBindMenuMenuFontColor: $compBindMenuMenuFontColor,
          enableCompBindMenuMenuRadius: $enableCompBindMenuMenuRadius,
          compBindMenuMenuRadius: $compBindMenuMenuRadius,
          enableCompBindMenuMenuWidth: $enableCompBindMenuMenuWidth,
          compBindMenuMenuWidth: $compBindMenuMenuWidth,
          enableCompBindMenuMenuHeight: $enableCompBindMenuMenuHeight,
          compBindMenuMenuHeight: $compBindMenuMenuHeight,
          enableCompBindMenuMenuItemDividerStrokeWidth: $enableCompBindMenuMenuItemDividerStrokeWidth,
          compBindMenuMenuItemDividerStrokeWidth: $compBindMenuMenuItemDividerStrokeWidth,
          enableCompBindMenuMenuItemDividerColor: $enableCompBindMenuMenuItemDividerColor,
          compBindMenuMenuItemDividerColor: $compBindMenuMenuItemDividerColor,
          enableCompBindMenuMenuItemDividerStartMargin: $enableCompBindMenuMenuItemDividerStartMargin,
          compBindMenuMenuItemDividerStartMargin: $compBindMenuMenuItemDividerStartMargin,
          enableCompBindMenuMenuItemDividerEndMargin: $enableCompBindMenuMenuItemDividerEndMargin,
          compBindMenuMenuItemDividerEndMargin: $compBindMenuMenuItemDividerEndMargin,
          enableCompBindMenuMenuItemGroupDividerStrokeWidth: $enableCompBindMenuMenuItemGroupDividerStrokeWidth,
          compBindMenuMenuItemGroupDividerStrokeWidth: $compBindMenuMenuItemGroupDividerStrokeWidth,
          enableCompBindMenuMenuItemGroupDividerColor: $enableCompBindMenuMenuItemGroupDividerColor,
          compBindMenuMenuItemGroupDividerColor: $compBindMenuMenuItemGroupDividerColor,
          enableCompBindMenuMenuItemGroupDividerStartMargin: $enableCompBindMenuMenuItemGroupDividerStartMargin,
          compBindMenuMenuItemGroupDividerStartMargin: $compBindMenuMenuItemGroupDividerStartMargin,
          enableCompBindMenuMenuItemGroupDividerEndMargin: $enableCompBindMenuMenuItemGroupDividerEndMargin,
          compBindMenuMenuItemGroupDividerEndMargin: $compBindMenuMenuItemGroupDividerEndMargin,
          enableCompBindMenuSubMenuExpandingMode: $enableCompBindMenuSubMenuExpandingMode,
          compBindMenuSubMenuExpandingMode: $compBindMenuSubMenuExpandingMode,
          enableCompBindMenuMenuBackgroundColor: $enableCompBindMenuMenuBackgroundColor,
          compBindMenuMenuBackgroundColor: $compBindMenuMenuBackgroundColor,
          enableCompBindMenuMenuOpacity: $enableCompBindMenuMenuOpacity,
          compBindMenuMenuOpacity: $compBindMenuMenuOpacity,
          enableCompBindMenuMenuVisibility: $enableCompBindMenuMenuVisibility,
          compBindMenuMenuVisibility: $compBindMenuMenuVisibility,
          enableCompBindMenuMenuPadding: $enableCompBindMenuMenuPadding,
          compBindMenuMenuPadding: $compBindMenuMenuPadding,
          enableCompBindMenuMenuMargin: $enableCompBindMenuMenuMargin,
          compBindMenuMenuMargin: $compBindMenuMenuMargin,
        })

        //focusable
        CompFocusControlBlocks({
          enableCompFocusable: $enableCompFocusable,
          compFocusable: $compFocusable,
          enableCompDefaultFocus: $compDefaultFocus,
          compDefaultFocus: $compDefaultFocus,
          enableCompGroupDefaultFocus: $enableCompGroupDefaultFocus,
          compGroupDefaultFocus: $compGroupDefaultFocus,
          enableCompFocusOnTouch: $enableCompFocusOnTouch,
          compFocusOnTouch: $compFocusOnTouch,
          enableCompFocusBoxMargin: $enableCompFocusBoxMargin,
          compFocusBoxMargin: $compFocusBoxMargin,
          enableCompFocusBoxStrokeColor: $enableCompFocusBoxStrokeColor,
          compFocusBoxStrokeColor: $compFocusBoxStrokeColor,
          enableCompFocusBoxStrokeWidth: $enableCompFocusBoxStrokeWidth,
          compFocusBoxStrokeWidth: $compFocusBoxStrokeWidth,
          enableCompFocusScopePriorityScopeId: $enableCompFocusScopePriorityScopeId,
          compFocusScopePriorityScopeId: $compFocusScopePriorityScopeId,
          enableCompFocusScopePriorityPriority: $enableCompFocusScopePriorityPriority,
          compFocusScopePriorityPriority: $compFocusScopePriorityPriority,
          enableCompFocusScopeId: $enableCompFocusScopeId,
          compFocusScopeId: $compFocusScopeId,
          enableCompFocusScopeIdIsGroup: $enableCompFocusScopeIdIsGroup,
          compFocusScopeIdIsGroup: $compFocusScopeIdIsGroup,
        })

        CompHoverEffectBlocks({
          enableCompHoverEffect: $enableCompHoverEffect,
          compHoverEffect: $compHoverEffect,
        })

        CompComponentIDBlocks({
          enableCompId: $enableCompId,
          compId: $compId,
          enableCompKey: $enableCompKey,
          compKey: $compKey,
        })

        CompReuseIDBlocks({
          enableCompReuseId: $enableCompReuseId,
          compReuseId: $compReuseId,
        })

        CompRestoreIdBlocks({
          enableCompRestoreId: $enableCompRestoreId,
          compRestoreId: $compRestoreId,
        })

        CompForegroundEffectBlocks({
          enableCompForegroundEffectRadius: $enableCompForegroundEffectRadius,
          compForegroundEffectRadius: $compForegroundEffectRadius
        })

        CompForegroundBlurBlocks({
          enableCompForegroundBlurStyleValue: $enableCompForegroundBlurStyleValue,
          compForegroundBlurStyleValue: $compForegroundBlurStyleValue,
          enableCompForegroundBlurStyleOptionsColorMode: $enableCompForegroundBlurStyleOptionsColorMode,
          compForegroundBlurStyleOptionsColorMode: $compForegroundBlurStyleOptionsColorMode,
          enableCompForegroundBlurStyleOptionsAdaptiveColor: $enableCompForegroundBlurStyleOptionsAdaptiveColor,
          compForegroundBlurStyleOptionsAdaptiveColor: $compForegroundBlurStyleOptionsAdaptiveColor,
          enableCompForegroundBlurStyleOptionsBlurOptions: $enableCompForegroundBlurStyleOptionsBlurOptions,
          compForegroundBlurStyleOptionsBlurOptions: $compForegroundBlurStyleOptionsBlurOptions,
          enableCompForegroundBlurStyleOptionsScale: $enableCompForegroundBlurStyleOptionsScale,
          compForegroundBlurStyleOptionsScale: $compForegroundBlurStyleOptionsScale,
        })

        CompClickEffectBlocks({
          enableCompClickEffect: $enableCompClickEffect,
          compClickEffect: $compClickEffect,
          enableCompClickEffectLevel: $enableCompClickEffectLevel,
          compClickEffectLevel: $compClickEffectLevel,
          enableCompClickEffectScale: $enableCompClickEffectScale,
          compClickEffectScale: $compClickEffectScale,
        })

        CompAccessibilityBlocks({
          enableCompAccessibilityGroup: $enableCompAccessibilityGroup,
          compAccessibilityGroup: $compAccessibilityGroup,
          enableCompAccessibilityText: $enableCompAccessibilityText,
          compAccessibilityText: $compAccessibilityText,
          enableCompAccessibilityDescription: $enableCompAccessibilityDescription,
          compAccessibilityDescription: $compAccessibilityDescription,
          enableCompAccessibilityLevel: $enableCompAccessibilityLevel,
          compAccessibilityLevel: $compAccessibilityLevel,
        })

        CompTouchTargetBlocks({
          enableCompResponseRegionValueX: $enableCompResponseRegionValueX,
          compResponseRegionValueX: $compResponseRegionValueX,
          enableCompResponseRegionValueY:
          $enableCompResponseRegionValueY,
          compResponseRegionValueY: $compResponseRegionValueY,
          enableCompResponseRegionValueWidth: $enableCompResponseRegionValueWidth,
          compResponseRegionValueWidth: $compResponseRegionValueWidth,
          enableCompResponseRegionValueHeight: $enableCompResponseRegionValueHeight,
          compResponseRegionValueHeight: $compResponseRegionValueHeight
        })

        CompHitTestControlBlocks({
          enableCompHitTestBehavior: $enableCompHitTestBehavior,
          compHitTestBehavior: $compHitTestBehavior
        })

        CompModalTransitionBlocks({
          enableCompBindContentCoverIsShow: $enableCompBindContentCoverIsShow,
          compBindContentCoverIsShow: $compBindContentCoverIsShow,
          enableCompBindContentCoverOptionsModalTransition: $enableCompBindContentCoverOptionsModalTransition,
          compBindContentCoverOptionsModalTransition: $compBindContentCoverOptionsModalTransition,
          enableCompBindContentCoverOptionsTransitionOpacity: $enableCompBindContentCoverOptionsTransitionOpacity,
          compBindContentCoverOptionsTransitionOpacity: $compBindContentCoverOptionsTransitionOpacity,
          enableCompBindContentCoverOptionsTransitionTranslateX:
          $enableCompBindContentCoverOptionsTransitionTranslateX,
          compBindContentCoverOptionsTransitionTranslateX: $compBindContentCoverOptionsTransitionTranslateX,
          enableCompBindContentCoverOptionsTransitionTranslateY:
          $enableCompBindContentCoverOptionsTransitionTranslateY,
          compBindContentCoverOptionsTransitionTranslateY: $compBindContentCoverOptionsTransitionTranslateY,
          enableCompBindContentCoverOptionsTransitionTranslateZ:
          $enableCompBindContentCoverOptionsTransitionTranslateZ,
          compBindContentCoverOptionsTransitionTranslateZ: $compBindContentCoverOptionsTransitionTranslateZ,
          enableCompBindContentCoverOptionsTransitionScaleX: $enableCompBindContentCoverOptionsTransitionScaleX,
          compBindContentCoverOptionsTransitionScaleX: $compBindContentCoverOptionsTransitionScaleX,
          enableCompBindContentCoverOptionsTransitionScaleY: $enableCompBindContentCoverOptionsTransitionScaleY,
          compBindContentCoverOptionsTransitionScaleY: $compBindContentCoverOptionsTransitionScaleY,
          enableCompBindContentCoverOptionsTransitionScaleZ: $enableCompBindContentCoverOptionsTransitionScaleZ,
          compBindContentCoverOptionsTransitionScaleZ: $compBindContentCoverOptionsTransitionScaleZ,
          enableCompBindContentCoverOptionsTransitionScaleCenterX:
          $enableCompBindContentCoverOptionsTransitionScaleCenterX,
          compBindContentCoverOptionsTransitionScaleCenterX: $compBindContentCoverOptionsTransitionScaleCenterX,
          enableCompBindContentCoverOptionsTransitionScaleCenterY:
          $enableCompBindContentCoverOptionsTransitionScaleCenterY,
          compBindContentCoverOptionsTransitionScaleCenterY: $compBindContentCoverOptionsTransitionScaleCenterY,
          enableCompBindContentCoverOptionsTransitionRotateX: $enableCompBindContentCoverOptionsTransitionRotateX,
          compBindContentCoverOptionsTransitionRotateX: $compBindContentCoverOptionsTransitionRotateX,
          enableCompBindContentCoverOptionsTransitionRotateY: $enableCompBindContentCoverOptionsTransitionRotateY,
          compBindContentCoverOptionsTransitionRotateY: $compBindContentCoverOptionsTransitionRotateY,
          enableCompBindContentCoverOptionsTransitionRotateZ: $enableCompBindContentCoverOptionsTransitionRotateZ,
          compBindContentCoverOptionsTransitionRotateZ: $compBindContentCoverOptionsTransitionRotateZ,
          enableCompBindContentCoverOptionsTransitionRotateAngle:
          $enableCompBindContentCoverOptionsTransitionRotateAngle,
          compBindContentCoverOptionsTransitionRotateAngle: $compBindContentCoverOptionsTransitionRotateAngle,
          enableCompBindContentCoverOptionsTransitionRotateCenterX:
          $enableCompBindContentCoverOptionsTransitionRotateCenterX,
          compBindContentCoverOptionsTransitionRotateCenterX: $compBindContentCoverOptionsTransitionRotateCenterX,
          enableCompBindContentCoverOptionsTransitionRotateCenterY:
          $enableCompBindContentCoverOptionsTransitionRotateCenterY,
          compBindContentCoverOptionsTransitionRotateCenterY: $compBindContentCoverOptionsTransitionRotateCenterY,
          enableCompBindContentCoverOptionsTransitionRotateCenterZ:
          $enableCompBindContentCoverOptionsTransitionRotateCenterZ,
          compBindContentCoverOptionsTransitionRotateCenterZ: $compBindContentCoverOptionsTransitionRotateCenterZ,
          enableCompBindContentCoverOptionsTransitionRotatePerspective:
          $enableCompBindContentCoverOptionsTransitionRotatePerspective,
          compBindContentCoverOptionsTransitionRotatePerspective:
          $compBindContentCoverOptionsTransitionRotatePerspective,
          enableCompBindContentCoverOptionsTransitionMove: $enableCompBindContentCoverOptionsTransitionMove,
          compBindContentCoverOptionsTransitionMove: $compBindContentCoverOptionsTransitionMove,
          enableCompBindContentCoverOptionsTransitionAnimationDuration:
          $enableCompBindContentCoverOptionsTransitionAnimationDuration,
          compBindContentCoverOptionsTransitionAnimationDuration:
          $compBindContentCoverOptionsTransitionAnimationDuration,
          enableCompBindContentCoverOptionsTransitionAnimationTempo:
          $enableCompBindContentCoverOptionsTransitionAnimationTempo,
          compBindContentCoverOptionsTransitionAnimationTempo:
          $compBindContentCoverOptionsTransitionAnimationTempo,
          enableCompBindContentCoverOptionsTransitionAnimationCurve:
          $enableCompBindContentCoverOptionsTransitionAnimationCurve,
          compBindContentCoverOptionsTransitionAnimationCurve:
          $compBindContentCoverOptionsTransitionAnimationCurve,
          enableCompBindContentCoverOptionsTransitionAnimationDelay:
          $enableCompBindContentCoverOptionsTransitionAnimationDelay,
          compBindContentCoverOptionsTransitionAnimationDelay:
          $compBindContentCoverOptionsTransitionAnimationDelay,
          enableCompBindContentCoverOptionsTransitionAnimationIterations:
          $enableCompBindContentCoverOptionsTransitionAnimationIterations,
          compBindContentCoverOptionsTransitionAnimationIterations:
          $compBindContentCoverOptionsTransitionAnimationIterations,
          enableCompBindContentCoverOptionsTransitionAnimationPlayMode:
          $enableCompBindContentCoverOptionsTransitionAnimationPlayMode,
          compBindContentCoverOptionsTransitionAnimationPlayMode:
          $compBindContentCoverOptionsTransitionAnimationPlayMode,
          enableCompBindContentCoverOptionsTransitionAnimationExpectedFrameRateRangeMin:
          $enableCompBindContentCoverOptionsTransitionAnimationExpectedFrameRateRangeMin,
          compBindContentCoverOptionsTransitionAnimationExpectedFrameRateRangeMin:
          $compBindContentCoverOptionsTransitionAnimationExpectedFrameRateRangeMin,
          enableCompBindContentCoverOptionsTransitionAnimationExpectedFrameRateRangeMax:
          $enableCompBindContentCoverOptionsTransitionAnimationExpectedFrameRateRangeMax,
          compBindContentCoverOptionsTransitionAnimationExpectedFrameRateRangeMax:
          $compBindContentCoverOptionsTransitionAnimationExpectedFrameRateRangeMax,
          enableCompBindContentCoverOptionsTransitionAnimationExpectedFrameRateRangeExpected:
          $enableCompBindContentCoverOptionsTransitionAnimationExpectedFrameRateRangeExpected,
          compBindContentCoverOptionsTransitionAnimationExpectedFrameRateRangeExpected:
          $compBindContentCoverOptionsTransitionAnimationExpectedFrameRateRangeExpected
        })

        CompSheetTransitionBlocks({
          enableCompBindSheetIsShow: $enableCompBindSheetIsShow,
          compBindSheetIsShow: $compBindSheetIsShow,
          enableCompBindSheetOptionsHeight: $enableCompBindSheetOptionsHeight,
          compBindSheetOptionsHeight: $compBindSheetOptionsHeight,
          enableCompBindSheetOptionsDetents: $enableCompBindSheetOptionsDetents,
          compBindSheetOptionsDetents: $compBindSheetOptionsDetents,
          enableCompBindSheetOptionsPreferType: $enableCompBindSheetOptionsPreferType,
          compBindSheetOptionsPreferType: $compBindSheetOptionsPreferType,
          enableCompBindSheetOptionsShowClose: $enableCompBindSheetOptionsShowClose,
          compBindSheetOptionsShowClose: $compBindSheetOptionsShowClose,
          enableCompBindSheetOptionsDragBar: $enableCompBindSheetOptionsDragBar,
          compBindSheetOptionsDragBar: $compBindSheetOptionsDragBar,
          enableCompBindSheetOptionsBlurStyle: $enableCompBindSheetOptionsBlurStyle,
          compBindSheetOptionsBlurStyle: $compBindSheetOptionsBlurStyle,
          enableCompBindSheetOptionsMaskColor: $enableCompBindSheetOptionsMaskColor,
          compBindSheetOptionsMaskColor: $compBindSheetOptionsMaskColor,
          enableCompBindSheetOptionsTitleTitle: $enableCompBindSheetOptionsTitleTitle,
          compBindSheetOptionsTitleTitle: $compBindSheetOptionsTitleTitle,
          enableCompBindSheetOptionsTitleSubtitle: $enableCompBindSheetOptionsTitleSubtitle,
          compBindSheetOptionsTitleSubtitle: $compBindSheetOptionsTitleSubtitle,
          enableCompBindSheetOptionsEnableOutsideInteractive: $enableCompBindSheetOptionsEnableOutsideInteractive,
          compBindSheetOptionsEnableOutsideInteractive: $compBindSheetOptionsEnableOutsideInteractive,
          enableCompBindSheetOptionsBorderWidth: $enableCompBindSheetOptionsBorderWidth,
          compBindSheetOptionsBorderWidth: $compBindSheetOptionsBorderWidth,
          enableCompBindSheetOptionsBorderColor: $enableCompBindSheetOptionsBorderColor,
          compBindSheetOptionsBorderColor: $compBindSheetOptionsBorderColor,
          enableCompBindSheetOptionsBorderStyle: $enableCompBindSheetOptionsBorderStyle,
          compBindSheetOptionsBorderStyle: $compBindSheetOptionsBorderStyle,
          enableCompBindSheetOptionWidth: $enableCompBindSheetOptionWidth,
          compBindSheetOptionsWidth: $compBindSheetOptionsWidth,
          enableCompBindSheetOptionShadow: $enableCompBindSheetOptionShadow,
          compBindSheetOptionShadow: $compBindSheetOptionShadow,
          enableCompBindSheetOptionMode: $enableCompBindSheetOptionMode,
          compBindSheetOptionMode: $compBindSheetOptionMode,
          enableCompBindSheetOptionScrollSizeMode: $enableCompBindSheetOptionScrollSizeMode,
          compBindSheetOptionScrollSizeMode: $compBindSheetOptionScrollSizeMode
        })

        CompObscuringBlocks({
          enableCompObscured: $enableCompObscured, compObscured: $compObscured
        })

        CompEventMonopolizationBlocks({
          enableCompMonopolizeEvents: $enableCompMonopolizeEvents, compMonopolizeEvents: $enableCompMonopolizeEvents
        })

        CompCursorControlBlocks({
          enableCompCursorControl: $enableCompCursorControl, compCursorControl: $compCursorControl
        })

        RadioBlock({
          title: 'useEffect',
          isEnabled: $enableCompUseEffect,
          value: $compUseEffect,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false },
          ]
        })

      }
      .width('100%')
    }
    .align(Alignment.Top)
    .height('50%')
  }
}

@Preview
@Component
struct FoldSplitContainerBootcampPreviewer {
  build() {
    FoldSplitContainerBootcamp({
      title: '折叠屏分栏组件/FoldSplitContainer'
    })
  }
}