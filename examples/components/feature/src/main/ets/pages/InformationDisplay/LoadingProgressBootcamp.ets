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
import { RadioBlock, SliderBlock, ColorBlock, useEnabled } from 'common';
import { curves, LengthUnit } from '@kit.ArkUI';
import {
  matrix4,
  LengthMetrics,
  SelectionMenu,
  ExpandedMenuOptions,
  SelectionMenuOptions,
  ColorMetrics,
  promptAction
} from '@kit.ArkUI';

import { common2D, uiEffect } from '@kit.ArkGraphics2D';
import { pointer } from '@kit.InputKit';
import { CompSizeBlocks } from './../../components/CompSizeBlocks'
import { CompLocationBlocks } from './../../components/CompLocationBlocks'
import { CompLayoutConstraintsBlocks } from './../../components/CompLayoutConstraintsBlocks'
import { CompBorderBlocks } from './../../components/CompBorderBlocks'
import { CompBorderImageBlocks } from './../../components/CompBorderImageBlocks'
import { CompBackgroundBlocks } from './../../components/CompBackgroundBlocks'
import { CompOpacityBlocks } from './../../components/CompOpacityBlocks'
import { CompVisibilityBlocks } from './../../components/CompVisibilityBlocks'
import { CompEnabledBlocks } from './../../components/CompEnabledBlocks'
import { CompOverlayBlocks } from './../../components/CompOverlayBlocks'
import { CompZOrderControlBlocks } from './../../components/CompZOrderControlBlocks'
import { CompTransformationBlocks } from './../../components/CompTransformationBlocks'
import { CompShapeClippingBlocks } from './../../components/CompShapeClippingBlocks'
import { CompImageEffectsBlocks } from './../../components/CompImageEffectsBlocks'
import { CompGestureModifierBlocks } from '../../components/CompGestureModifierBlocks'
import { CompOutlineBlocks } from '../../components/CompOutlineBlocks'
import { CompVisualEffectBlocks } from '../../components/CompVisualEffectBlocks'
import { CompTouchTargetBlocks } from '../../components/CompTouchTargetBlocks'
import { CompHitTestControlBlocks } from '../../components/CompHitTestControlBlocks'

import { CompObscuringBlocks } from '../../components/CompObscuringBlocks'
import { CompRenderFitBlocks } from '../../components/CompRenderFitBlocks'
import { CompEventMonopolizationBlocks } from '../../components/CompEventMonopolizationBlocks'
import { CompCursorControlBlocks } from '../../components/CompCursorControlBlocks'
import { CompGradientColorBlocks } from '../../components/CompGradientColorBlocks';

import { CompFocusControlBlocks } from '../../components/CompFocusControlBlocks';
import { CompHoverEffectBlocks } from '../../components/CompHoverEffectBlocks';
import { CompComponentIDBlocks } from '../../components/CompComponentIDBlocks';
import { CompReuseIDBlocks } from '../../components/CompReuseIDBlocks';
import { CompRestoreIdBlocks } from '../../components/CompRestoreIdBlocks';
import { CompForegroundEffectBlocks } from '../../components/CompForegroundEffectBlocks';
import { CompForegroundBlurBlocks } from '../../components/CompForegroundBlurBlocks';
import { CompMotionBlurBlocks } from '../../components/CompMotionBlurBlocks';
import { CompClickEffectBlocks } from '../../components/CompClickEffectBlocks';
import { CompAccessibilityBlocks } from '../../components/CompAccessibilityBlocks';
import { CompAttributeModifierBlocks } from '../../components/CompAttributeModifierBlocks';
import { formatDate } from 'common/src/main/ets/utils/timeUtil';
import { BlockTag } from 'common/src/main/ets/model/BlockTag';

class MyModifier implements AttributeModifier<TextAttribute> {
  applyNormalAttribute(instance: TextAttribute) {
    instance.backgroundColor('#0A59F7')
  }

  applyPressedAttribute(instance: TextAttribute) {
    instance.backgroundColor('#ED6F21')
  }

  applyFocusedAttribute(instance: TextAttribute) {
    instance.backgroundColor(Color.Gray)
  }

  applyDisabledAttribute(instance: TextAttribute) {
    instance.backgroundColor('#E5E5E5')
  }

  applySelectedAttribute(instance: TextAttribute) {
    instance.backgroundColor('#ffedea21')
  }
}

class MyLoadingProgressStyle implements ContentModifier<LoadingProgressConfiguration> {
  public  enableLoading: boolean = false

  constructor(enableLoading: boolean) {
    this.enableLoading = enableLoading
  }

  applyContent(): WrappedBuilder<[LoadingProgressConfiguration]> {
    return wrapBuilder(buildLoadingProgress)
  }
}

@Builder function buildLoadingProgress(config: LoadingProgressConfiguration) {
  Column() {
    Button('' + ((config.contentModifier as MyLoadingProgressStyle).enableLoading))
      .onClick((event: ClickEvent) => {
        promptAction.showToast({
          message: ((config.contentModifier as MyLoadingProgressStyle).enableLoading) + ''
        })
      })
      .fontColor(Color.White)
      .backgroundColor(((config.contentModifier as MyLoadingProgressStyle).enableLoading) ? Color.Grey : 0x2577e3)
  }.width('50%')
}
class MyGestureModifier1 implements GestureModifier {
  applyGesture(event: UIGestureEvent): void {
    event.addGesture(
      new TapGestureHandler({ count: 2, fingers: 2 })
        .tag('aaa')
        .onAction((event: GestureEvent) => {
          promptAction.showToast({
            message: 'Two fingers double click',
            duration: 2000,
            bottom: 300
          });
        })
    )
  }
}

class MyGestureModifier2 implements GestureModifier {
  applyGesture(event: UIGestureEvent): void {
  }
}

@Component
export struct LoadingProgressBootcamp {

  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State enableColor: boolean = false;
  @State color: ResourceColor = '#ff666666';
  @State enableEnableLoading: boolean = false;
  @State enableLoading: boolean = true;
  @State enableContentModifier: boolean = false;
  @State contentModifier: boolean | null = null;
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
  @State enableCompBackgroundBrightnessRate: boolean = false;
  @State compBackgroundBrightnessRate: number = 0;
  @State enableCompBackgroundBrightnessLightUpDegree: boolean = false;
  @State compBackgroundBrightnessLightUpDegree: number = 0;
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
  @State enableCompClipShape: boolean = false;
  @State enableCompClipShapeWidth: boolean = false;
  @State compClipShapeWidth: number = 100;
  @State enableCompClipShapeHeight: boolean = false;
  @State compClipShapeHeight: number = 100;
  @State enableCompMask: boolean = false;
  @State enableCompMaskValue: boolean = false;
  @State @Watch('compMaskValueChange') compMaskValue: number = 0;
  @State enableCompMaskColor: boolean = false;
  @State @Watch('compMaskColorChange') compMaskColor: number = Color.Transparent;
  @State progress: ProgressMask = new ProgressMask(0, 100, Color.Transparent);
  @State enableCompMaskShape: boolean = false;
  @State enableCompMaskShapeWidth: boolean = false;
  @State compMaskShapeWidth: number = 0;
  @State enableCompMaskShapeHeight: boolean = false;
  @State compMaskShapeHeight: number = 0;
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
  @State enableCompLinearGradientBlurValue: boolean = false
  @State compLinearGradientBlurValue: number = 0
  @State enableCompLinearGradientBlurOptionsFractionStops: boolean = false
  @State compLinearGradientBlurOptionsFractionStops: Array<FractionStop> = [[0, 0]]
  @State enableCompLinearGradientBlurOptionsDirection: boolean = false
  @State compLinearGradientBlurOptionsDirection: GradientDirection = GradientDirection.Bottom
  @State enableCompRenderGroup: boolean = false
  @State compRenderGroup: boolean = false
  @State enableCompBlendModeValue: boolean = false
  @State compBlendModeValue: BlendMode = BlendMode.NONE
  @State enableCompBlendModeType: boolean = false
  @State compBlendModeType: BlendApplyType = BlendApplyType.FAST
  @State enableCompUseShadowBatching: boolean = false
  @State compUseShadowBatching: boolean = false
  @State enableCompSphericalEffect: boolean = false
  @State compSphericalEffect: number = 0
  @State enableCompLightUpEffect: boolean = false
  @State compLightUpEffect: number = 0
  @State enableCompPixelStretchEffectOptionsLeft: boolean = false
  @State compPixelStretchEffectOptionsLeft: number = 0
  @State enableCompPixelStretchEffectOptionsRight: boolean = false
  @State compPixelStretchEffectOptionsRight: number = 0
  @State enableCompPixelStretchEffectOptionsTop: boolean = false
  @State compPixelStretchEffectOptionsTop: number = 0
  @State enableCompPixelStretchEffectOptionsBottom: boolean = false
  @State compPixelStretchEffectOptionsBottom: number = 0
  @State enableCompFreeze: boolean = false
  @State compFreeze: boolean = false
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
  //sweepGradient
  @State enableCompSweepGradientCenterValue1: boolean = false;
  @State compSweepGradientCenterValue1: number = 0;
  @State enableCompSweepGradientCenterValue2: boolean = false;
  @State compSweepGradientCenterValue2: number = 0;
  @State enableCompSweepGradientStart: boolean = false;
  @State compSweepGradientStart: number = 0;
  @State enableCompSweepGradientEnd: boolean = false;
  @State compSweepGradientEnd: number = 0;
  @State enableCompSweepGradientRotation: boolean = false;
  @State compSweepGradientRotation: number = 0;
  @State enableCompSweepGradientColors1: boolean = false;
  @State compSweepGradientColors1: ResourceStr = '#ff000000';
  @State enableCompSweepGradientColorsNumber1: boolean = false;
  @State compSweepGradientColorsNumber1: number = 0;
  @State enableCompSweepGradientColors2: boolean = false;
  @State compSweepGradientColors2: ResourceStr = '#ff000000';
  @State enableCompSweepGradientColorsNumber2: boolean = false;
  @State compSweepGradientColorsNumber2: number = 0;
  @State enableCompSweepGradientRepeating: boolean = false;
  @State compSweepGradientRepeating: boolean = false;
  //RadialGradient
  @State enableCompRadialGradientCenterValue1: boolean = false;
  @State compRadialGradientCenterValue1: number = 0;
  @State enableCompRadialGradientCenterValue2: boolean = false;
  @State compRadialGradientCenterValue2: number = 0;
  @State enableCompRadialGradientRadius: boolean = false;
  @State compRadialGradientRadius: number = 0;
  @State enableCompRadialGradientColors1: boolean = false;
  @State compRadialGradientColors1: ResourceStr = '#ff000000';
  @State enableCompRadialGradientColorsNumber1: boolean = false;
  @State compRadialGradientColorsNumber1: number = 0;
  @State enableCompRadialGradientColors2: boolean = false;
  @State compRadialGradientColors2: ResourceStr = '#ff000000';
  @State enableCompRadialGradientColorsNumber2: boolean = false;
  @State compRadialGradientColorsNumber2: number = 0;
  @State enableCompRadialGradientRepeating: boolean = false;
  @State compRadialGradientRepeating: boolean = false;

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
  @State enableCompForegroundColor: boolean = false;
  @State compForegroundColor: ResourceColor = '#ff000000';
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
  //motionBlur
  @State enableCompMotionBlurRadius: boolean = false;
  @State compMotionBlurRadius: number = 0;
  @State enableCompMotionBlurAnchorX: boolean = false;
  @State compMotionBlurAnchorX: number = 0;
  @State enableCompMotionBlurAnchorY: boolean = false;
  @State compMotionBlurAnchorY: number = 0;
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

  @State modifier: MyModifier = new MyModifier()
  @State enableCompAttributeModifier: boolean = false;
  @State compAttributeModifier: boolean = false;
  // Gesture Modifier
  @State enableCompGestureModifier: boolean = false
  @State compGestureModifier: boolean = false
  myGestureModifier1: MyGestureModifier1 = new MyGestureModifier1()
  myGestureModifier2: MyGestureModifier2 = new MyGestureModifier2()
  // Outline
  @State enableCompOutlineValueWidth: boolean = false
  @State compOutlineValueWidth: number = 0
  @State enableCompOutlineValueColor: boolean = false
  @State compOutlineValueColor: ResourceColor = Color.Black
  @State enableCompOutlineValueRadius: boolean = false
  @State compOutlineValueRadius: number = 0
  @State enableCompOutlineValueStyle: boolean = false
  @State compOutlineValueStyle: OutlineStyle = OutlineStyle.SOLID
  // Visual Effect
  @State enableCompVisualEffect: boolean = false
  @State compVisualEffect: boolean = false
  @State enableCompBackgroundFilter: boolean = false
  @State compBackgroundFilter: boolean = false
  @State enableCompForegroundFilter: boolean = false
  @State compForegroundFilter: boolean = false
  @State enableCompCompositingFilter: boolean = false
  @State compCompositingFilter: boolean = false
  @State enableCompResponseRegionValueX: boolean = false
  // Touch Target
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

  // Obscuring
  @State enableCompObscured: boolean = false
  @State compObscured: Array<ObscuredReasons> = []
  // Universal Text Attributes
  @State enableCompLineHeight: boolean = false
  @State compLineHeight: number = 16
  // Drag and Drop Control
  @State compDraggable: boolean = false
  @State enableCompDragPreview: boolean = false
  @State compDragPreview: string = '默认'
  @State enableCompDragPreviewOptionsValueMode: boolean = false
  @State compDragPreviewOptionsValueMode: DragPreviewMode = DragPreviewMode.AUTO
  @State enableCompDragPreviewOptionsValueNumberBadge: boolean = false
  @State compDragPreviewOptionsValueNumberBadge: number = 1
  @State enableCompDragPreviewOptionsOptionsIsMultiSelectionEnabled: boolean = false
  @State compDragPreviewOptionsOptionsIsMultiSelectionEnabled: boolean = false
  @State enableCompDragPreviewOptionsOptionsDefaultAnimationBeforeLifting: boolean = false
  @State compDragPreviewOptionsOptionsDefaultAnimationBeforeLifting: boolean = false
  // Safe Area
  @State enableCompExpandSafeAreaTypes: boolean = false
  @State compExpandSafeAreaTypes: Array<SafeAreaType> =
    [SafeAreaType.SYSTEM, SafeAreaType.CUTOUT, SafeAreaType.KEYBOARD]
  @State enableCompExpandSafeAreaEdges: boolean = false
  @State compExpandSafeAreaEdges: Array<SafeAreaEdge> =
    [SafeAreaEdge.TOP, SafeAreaEdge.BOTTOM, SafeAreaEdge.START, SafeAreaEdge.END]
  // Render Fit
  @State enableCompRenderFit: boolean = false
  @State compRenderFit: RenderFit = RenderFit.TOP_LEFT
  // Event Monopolization
  @State enableCompMonopolizeEvents: boolean = false
  @State compMonopolizeEvents: boolean = false
  // Cursor Control
  @State enableCompCursorControl: boolean = false
  @State compCursorControl: pointer.PointerStyle = pointer.PointerStyle.DEFAULT
  // Special Effect Drawing Combination
  @State enableCompUseEffect: boolean = false
  @State compUseEffect: boolean = false
  //compEvent
  @StorageLink('Block') listEventTriggeredTags: Array<BlockTag> = [];
  @State listEventTriggeredTagsTemp: Array<BlockTag> = [];

  @State selection: string | null = null;
  scroller: Scroller = new Scroller()

  aboutToAppear(): void {
    AppStorage.setOrCreate('scroller', this.scroller)
  }

  compMaskColorChange() {
    this.progress.updateColor(this.compMaskColor);
  }

  compMaskValueChange() {
    this.progress.updateProgress(this.compMaskValue);
  }

  //compEvent
  compEventTriggeredLog(value: string) {
    let time = formatDate(new Date(Date.now()))
    this.listEventTriggeredTagsTemp.push(
      new BlockTag(time, value)
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

  @Builder
  compBackground() {
    Text('123')
  }


  build() {
    NavDestination() {
      Drawer({
        title: this.title,
        showParameters: $showParameters,
        content: () => {
          this.Content()
        },
        generic: () => {
          this.Generic()
        },
        parameters: () => {
          this.Parameters()
        }
      })
    }
    .backgroundColor($r('sys.color.ohos_id_color_sub_background'))
    .hideTitleBar(true)
  }

  @Builder
  Content() {
    Column() {
      LoadingProgress()
        .color(useEnabled(this.enableColor, this.color))
        .enableLoading(useEnabled(this.enableEnableLoading,
          this.enableLoading))
        .contentModifier(this.enableContentModifier?new MyLoadingProgressStyle(this.contentModifier):null)
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
        } : null)
        .markAnchor(this.enableCompMarkAnchor ? {
          x: useEnabled(this.enableCompMarkAnchorX, this.compMarkAnchorX),
          y: useEnabled(this.enableCompMarkAnchorY, this.compMarkAnchorY)
        } : null)
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
        } : null)
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
        } : null)
        .background(this.enableCompBackgroundAlign ? this.compBackground() : null,
          this.enableCompBackgroundAlign ? {
            align: useEnabled(this.enableCompBackgroundAlign, this.compBackgroundAlign)
          }
            : null
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
        .backdropBlur(1, {
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
        .backgroundBrightness({
          rate: useEnabled(
            this.enableCompBackgroundBrightnessRate,
            this.compBackgroundBrightnessRate
          ),
          lightUpDegree: useEnabled(
            this.enableCompBackgroundBrightnessLightUpDegree,
            this.compBackgroundBrightnessLightUpDegree
          )
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
          } : null)
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
        } : null)
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
        } : null)
        .transform(this.enableCompTransform ?
        matrix4.identity().rotate({ z: 1, angle: 90 }) :
        matrix4.identity()
        )
        .clip(useEnabled(
          this.enableCompClip,
          this.compClip
        ))

        .clipShape(this.enableCompClipShape ?
          new Circle({
            width: useEnabled(
              this.enableCompClipShapeWidth,
              this.compClipShapeWidth
            ) + '%',
            height: useEnabled(
              this.enableCompClipShapeHeight,
              this.compClipShapeHeight
            ) + '%'
          }) : null
        )
        .mask(new ProgressMask(
          useEnabled(
            this.enableCompMaskValue,
            this.compMaskValue
          ),
          100,
          useEnabled(
            this.enableCompMaskColor,
            this.compMaskColor
          )
        ))
        .maskShape(this.enableCompMaskShape ? new Circle({
          width: useEnabled(
            this.enableCompMaskShapeWidth,
            this.compMaskShapeWidth
          ) + '%',
          height: useEnabled(
            this.enableCompMaskShapeHeight,
            this.compMaskShapeHeight
          ) + '%'
        }).fill(Color.Gray) : null
        )

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
        .linearGradientBlur(useEnabled(this.enableCompLinearGradientBlurValue, this.compLinearGradientBlurValue), {
          fractionStops: useEnabled(this.enableCompLinearGradientBlurOptionsFractionStops,
            this.compLinearGradientBlurOptionsFractionStops),
          direction: useEnabled(this.enableCompLinearGradientBlurOptionsDirection,
            this.compLinearGradientBlurOptionsDirection)
        })
        .renderGroup(useEnabled(this.enableCompRenderGroup, this.compRenderGroup))
        .blendMode(useEnabled(this.enableCompBlendModeValue, this.compBlendModeValue),
          useEnabled(this.enableCompBlendModeType, this.compBlendModeType))
        .useShadowBatching(useEnabled(this.enableCompUseShadowBatching, this.compUseShadowBatching))
        .sphericalEffect(useEnabled(this.enableCompSphericalEffect, this.compSphericalEffect))
        .lightUpEffect(useEnabled(this.enableCompLightUpEffect, this.compLightUpEffect))
        .pixelStretchEffect({
          left: useEnabled(this.enableCompPixelStretchEffectOptionsLeft, this.compPixelStretchEffectOptionsLeft),
          right: useEnabled(this.enableCompPixelStretchEffectOptionsRight, this.compPixelStretchEffectOptionsRight),
          top: useEnabled(this.enableCompPixelStretchEffectOptionsTop, this.compPixelStretchEffectOptionsTop),
          bottom: useEnabled(this.enableCompPixelStretchEffectOptionsBottom,
            this.compPixelStretchEffectOptionsBottom)
        })
        .freeze(useEnabled(this.enableCompFreeze, this.compFreeze))
        .sweepGradient(!this.enableCompLinearGradientColors1 && !this.enableCompRadialGradientColors1 ? {
          center: [
            useEnabled(this.enableCompSweepGradientCenterValue1, this.compSweepGradientCenterValue1),
            useEnabled(this.enableCompSweepGradientCenterValue2, this.compSweepGradientCenterValue2)
          ],
          start: useEnabled(this.enableCompSweepGradientStart, this.compSweepGradientStart),
          end: useEnabled(this.enableCompSweepGradientEnd, this.compSweepGradientEnd),
          rotation: useEnabled(this.enableCompSweepGradientRotation, this.compSweepGradientRotation),
          colors: [
            [
              useEnabled(this.enableCompSweepGradientColors1, this.compSweepGradientColors1),
              useEnabled(this.enableCompSweepGradientColorsNumber1, this.compSweepGradientColorsNumber1),
            ],
            [
              useEnabled(this.enableCompSweepGradientColors2, this.compSweepGradientColors2),
              useEnabled(this.enableCompSweepGradientColorsNumber2, this.compSweepGradientColorsNumber2),
            ]
          ],
          repeating: useEnabled(this.enableCompSweepGradientRepeating, this.compSweepGradientRepeating),
        } : {
          center: [0, 0],
          colors: [[0, 0], [0, 0]],
          start: 0,
          end: 0,
          rotation: 0,
          repeating: null
        })
        .radialGradient(!this.enableCompLinearGradientColors1 && !this.enableCompSweepGradientColors1 ? {
          center: [
            useEnabled(this.enableCompRadialGradientCenterValue1, this.compRadialGradientCenterValue1),
            useEnabled(this.enableCompRadialGradientCenterValue2, this.compRadialGradientCenterValue2)
          ],
          radius: useEnabled(this.enableCompRadialGradientRadius, this.compRadialGradientRadius),
          colors: [
            [
              useEnabled(this.enableCompRadialGradientColors1, this.compRadialGradientColors1),
              useEnabled(this.enableCompRadialGradientColorsNumber1, this.compRadialGradientColorsNumber1),
            ],
            [
              useEnabled(this.enableCompRadialGradientColors2, this.compRadialGradientColors2),
              useEnabled(this.enableCompRadialGradientColorsNumber2, this.compRadialGradientColorsNumber2),
            ]
          ],
          repeating: useEnabled(this.enableCompRadialGradientRepeating, this.compRadialGradientRepeating),
        } : {
          center: [0, 0],
          colors: [[0, 0], [0, 0]],
          radius: 0,
          repeating: null
        })
        .linearGradient(!this.enableCompRadialGradientColors1 && !this.enableCompSweepGradientColors1 ? {
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
        } : {
          angle: 0,
          direction: null,
          colors: null,
          repeating: null
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
        .key(useEnabled(this.enableCompKey, this.compKey) ? useEnabled(this.enableCompKey, this.compKey) : 'LoadingProgress')
        .focusScopePriority(
          useEnabled(this.enableCompFocusScopePriorityScopeId, this.compFocusScopePriorityScopeId),
          useEnabled(this.enableCompFocusScopePriorityPriority, this.compFocusScopePriorityPriority)
        )
        .focusScopeId(
          useEnabled(this.enableCompFocusScopeId, this.compFocusScopeId),
          useEnabled(this.enableCompFocusScopeIdIsGroup, this.compFocusScopeIdIsGroup)
        )
        .hoverEffect(useEnabled(this.enableCompHoverEffect, this.compHoverEffect))
        .reuseId(useEnabled(this.enableCompReuseId, this.compReuseId) ?
        useEnabled(this.enableCompReuseId, this.compReuseId) : null)
        .restoreId(useEnabled(this.enableCompRestoreId, this.compRestoreId) ?
        useEnabled(this.enableCompRestoreId, this.compRestoreId) : null)
        .foregroundColor(useEnabled(this.enableCompForegroundColor, this.compForegroundColor))
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
        .motionBlur({
          radius: useEnabled(this.enableCompMotionBlurRadius, this.compMotionBlurRadius),
          anchor: {
            x: useEnabled(this.enableCompMotionBlurAnchorX, this.compMotionBlurAnchorX),
            y: useEnabled(this.enableCompMotionBlurAnchorY, this.compMotionBlurAnchorY),
          }
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
        .gestureModifier(useEnabled(this.enableCompGestureModifier, this.compGestureModifier) ?
        this.myGestureModifier1 : this.myGestureModifier2)
        .outline({
          width: useEnabled(this.enableCompOutlineValueWidth, this.compOutlineValueWidth),
          color: useEnabled(this.enableCompOutlineValueColor, this.compOutlineValueColor),
          radius: useEnabled(this.enableCompOutlineValueRadius, this.compOutlineValueRadius),
          style: useEnabled(this.enableCompOutlineValueStyle, this.compOutlineValueStyle)
        })
        .visualEffect(useEnabled(this.enableCompVisualEffect, this.compVisualEffect) ? uiEffect.createEffect() :
          undefined)
        .backgroundFilter(useEnabled(this.enableCompBackgroundFilter, this.compBackgroundFilter) ?
        uiEffect.createFilter().blur(10) : uiEffect.createFilter().blur(0))
        .foregroundFilter(useEnabled(this.enableCompForegroundFilter, this.compForegroundFilter) ?
        uiEffect.createFilter().blur(10) : uiEffect.createFilter().blur(0))
        .compositingFilter(useEnabled(this.enableCompCompositingFilter, this.compCompositingFilter) ?
        uiEffect.createFilter().blur(10) : uiEffect.createFilter().blur(0))
        .responseRegion({
          x: useEnabled(this.enableCompResponseRegionValueX, this.compResponseRegionValueX),
          y: useEnabled(this.enableCompResponseRegionValueY, this.compResponseRegionValueY),
          width: useEnabled(this.enableCompResponseRegionValueWidth, this.compResponseRegionValueWidth),
          height: useEnabled(this.enableCompResponseRegionValueHeight, this.compResponseRegionValueHeight)
        })
        .hitTestBehavior(useEnabled(this.enableCompHitTestBehavior, this.compHitTestBehavior))
        .obscured(useEnabled(this.enableCompObscured, this.compObscured))
        .dragPreview(useEnabled(this.enableCompDragPreview, this.compDragPreview))
        .dragPreviewOptions({
          mode: useEnabled(this.enableCompDragPreviewOptionsValueMode, this.compDragPreviewOptionsValueMode),
          numberBadge: useEnabled(this.enableCompDragPreviewOptionsValueNumberBadge,
            this.compDragPreviewOptionsValueNumberBadge),
        }, {
          isMultiSelectionEnabled: useEnabled(
            this.enableCompDragPreviewOptionsOptionsIsMultiSelectionEnabled,
            this.compDragPreviewOptionsOptionsIsMultiSelectionEnabled),
          defaultAnimationBeforeLifting: useEnabled(
            this.enableCompDragPreviewOptionsOptionsDefaultAnimationBeforeLifting,
            this.compDragPreviewOptionsOptionsDefaultAnimationBeforeLifting)
        })
        .expandSafeArea(
          useEnabled(this.enableCompExpandSafeAreaTypes, this.compExpandSafeAreaTypes),
          useEnabled(this.enableCompExpandSafeAreaEdges, this.compExpandSafeAreaEdges))
        .renderFit(useEnabled(this.enableCompRenderFit, this.compRenderFit))
        .monopolizeEvents(useEnabled(this.enableCompMonopolizeEvents, this.compMonopolizeEvents))
        .useEffect(useEnabled(this.enableCompUseEffect, this.compUseEffect))
        .onClick((event?: ClickEvent) => {
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
        .onDragStart((event: DragEvent, extraParams?: string) => {
          this.compEventTriggeredLog('拖拽事件onDragStart触发');
        })
        .onDragEnter((event: DragEvent, extraParams?: string) => {
          this.compEventTriggeredLog('拖拽事件onDragEnter触发');
        })
        .onDragMove((event: DragEvent, extraParams?: string) => {
          this.compEventTriggeredLog('拖拽事件onDragMove触发');
        })
        .onDragLeave((event: DragEvent, extraParams?: string) => {
          this.compEventTriggeredLog('拖拽事件onDragLeave触发');
        })
        .onDrop((event: DragEvent, extraParams?: string) => {
          this.compEventTriggeredLog('拖拽事件onDrop触发');
        })
        .onDragEnd((event: DragEvent, extraParams?: string) => {
          this.compEventTriggeredLog('拖拽事件onDragEnd触发');
        })
        .onPreDrag((preDragStatus: PreDragStatus) => {
          this.compEventTriggeredLog('拖拽事件onPreDrag触发');
        })
        .onKeyEvent((event: KeyEvent) => {
          this.compEventTriggeredLog('按键事件onKeyEvent触发');
        })
        .onKeyPreIme((event?: KeyEvent) => {
          this.compEventTriggeredLog('按键事件onKeyPreIme触发');
          return true;
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
          if (isHover) {
            this.getUIContext()
              .getCursorController()
              .setCursor(useEnabled(this.enableCompCursorControl, this.compCursorControl))
          } else {
            this.getUIContext().getCursorController().restoreDefault()
          }
          this.compEventTriggeredLog('悬浮事件onHover触发');
        })
        .onAccessibilityHover((isHover: boolean, event: AccessibilityHoverEvent) => {
          if (isHover) {
            this.compEventTriggeredLog('无障碍悬浮事件onAccessibilityHover触发，手指进入悬浮')
          } else {
            this.compEventTriggeredLog('无障碍悬浮事件onAccessibilityHover触发，手指离开悬浮')
          }
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
    }
  }

  @Builder
  Parameters() {
    Scroll(this.scroller) {
      Column({ space: 8 }) {
        ColorBlock({
          title: 'color',
          isEnabled: $enableColor,
          color: $color
        })

        RadioBlock({
          title: 'enableLoading',
          isEnabled: $enableEnableLoading,
          value: $enableLoading,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })

        RadioBlock({
          title: 'contentModifier',
          isEnabled: $enableContentModifier,
          value: $contentModifier,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })
      }.width('100%')
    }
    .id('scroll')
    .height('50%')
  }

  @Builder
  Generic() {
    Scroll(this.scroller) {
      Column({ space: 8 }) {
        List({ space: 8 }) {
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
          CompBackgroundBlocks({
            enableCompBackgroundAlign: $enableCompBackgroundAlign,
            compBackgroundAlign: $compBackgroundAlign,
            enableCompBackgroundColor: $enableCompBackgroundColor,
            compBackgroundColor: $compBackgroundColor,
            enableCompBackgroundImageSrc: $enableCompBackgroundImageSrc,
            enableCompBackgroundImageRepeat: $enableCompBackgroundImageRepeat,
            compBackgroundImageRepeat: $compBackgroundImageRepeat,
            enableCompBackgroundImageSize: $enableCompBackgroundImageSize,
            compBackgroundImageSize: $compBackgroundImageSize,
            enableCompBackgroundImagePositionX: $enableCompBackgroundImagePositionX,
            compBackgroundImagePositionX: $compBackgroundImagePositionX,
            enableCompBackgroundImagePositionY: $enableCompBackgroundImagePositionY,
            compBackgroundImagePositionY: $compBackgroundImagePositionY,
            enableCompBackgroundBlurStyle: $enableCompBackgroundBlurStyle,
            compBackgroundBlurStyle: $compBackgroundBlurStyle,
            enableCompBackgroundBlurStyleParams: $enableCompBackgroundBlurStyleParams,
            enableCompBackgroundBlurStyleParamsColorMode: $enableCompBackgroundBlurStyleParamsColorMode,
            compBackgroundBlurStyleParamsColorMode: $compBackgroundBlurStyleParamsColorMode,
            enableCompBackgroundBlurStyleParamsAdaptiveColor: $enableCompBackgroundBlurStyleParamsAdaptiveColor,
            compBackgroundBlurStyleParamsAdaptiveColor: $compBackgroundBlurStyleParamsAdaptiveColor,
            enableCompBackgroundBlurStyleParamsBlurOptionsLeft: $enableCompBackgroundBlurStyleParamsBlurOptionsLeft,
            compBackgroundBlurStyleParamsBlurOptionsLeft: $compBackgroundBlurStyleParamsBlurOptionsLeft,
            enableCompBackgroundBlurStyleParamsBlurOptionsRight: $enableCompBackgroundBlurStyleParamsBlurOptionsRight,
            compBackgroundBlurStyleParamsBlurOptionsRight: $compBackgroundBlurStyleParamsBlurOptionsRight,
            enableCompBackgroundBlurStyleParamsScale: $enableCompBackgroundBlurStyleParamsScale,
            compBackgroundBlurStyleParamsScale: $compBackgroundBlurStyleParamsScale,
            enableCompBackdropBlur: $enableCompBackdropBlur,
            compBackdropBlur: $compBackdropBlur,
            enableCompBackdropBlurGrayscale: $enableCompBackdropBlurGrayscale,
            enableCompBackdropBlurGrayscaleLeft: $enableCompBackdropBlurGrayscaleLeft,
            compBackdropBlurGrayscaleLeft: $compBackdropBlurGrayscaleLeft,
            enableCompBackdropBlurGrayscaleRight: $enableCompBackdropBlurGrayscaleRight,
            compBackdropBlurGrayscaleRight: $compBackdropBlurGrayscaleRight,
            enableCompBackgroundEffect: $enableCompBackgroundEffect,
            enableCompBackgroundEffectRadius: $enableCompBackgroundEffectRadius,
            compBackgroundEffectRadius: $compBackgroundEffectRadius,
            enableCompBackgroundEffectSaturation: $enableCompBackgroundEffectSaturation,
            compBackgroundEffectSaturation: $compBackgroundEffectSaturation,
            enableCompBackgroundEffectBrightness: $enableCompBackgroundEffectBrightness,
            compBackgroundEffectBrightness: $compBackgroundEffectBrightness,
            enableCompBackgroundEffectColor: $enableCompBackgroundEffectColor,
            compBackgroundEffectColor: $compBackgroundEffectColor,
            enableCompBackgroundEffectAdaptiveColor: $enableCompBackgroundEffectAdaptiveColor,
            compBackgroundEffectAdaptiveColor: $compBackgroundEffectAdaptiveColor,
            enableCompBackgroundEffectBlurOptionsGrayscaleLeft: $enableCompBackgroundEffectBlurOptionsGrayscaleLeft,
            compBackgroundEffectBlurOptionsGrayscaleLeft: $compBackgroundEffectBlurOptionsGrayscaleLeft,
            enableCompBackgroundEffectBlurOptionsGrayscaleRight: $enableCompBackgroundEffectBlurOptionsGrayscaleRight,
            compBackgroundEffectBlurOptionsGrayscaleRight: $compBackgroundEffectBlurOptionsGrayscaleRight,
            enableCompBackgroundImageResizable: $enableCompBackgroundImageResizable,
            enableCompBackgroundImageResizableSliceTop: $enableCompBackgroundImageResizableSliceTop,
            compBackgroundImageResizableSliceTop: $compBackgroundImageResizableSliceTop,
            enableCompBackgroundImageResizableSliceBottom: $enableCompBackgroundImageResizableSliceBottom,
            compBackgroundImageResizableSliceBottom: $compBackgroundImageResizableSliceBottom,
            enableCompBackgroundImageResizableSliceLeft: $enableCompBackgroundImageResizableSliceLeft,
            compBackgroundImageResizableSliceLeft: $compBackgroundImageResizableSliceLeft,
            enableCompBackgroundImageResizableSliceRight: $enableCompBackgroundImageResizableSliceRight,
            compBackgroundImageResizableSliceRight: $compBackgroundImageResizableSliceRight,
            enableCompBackgroundImageResizableLattice: $enableCompBackgroundImageResizableLattice,
            enableCompBackgroundImageResizableLatticeXDivs: $enableCompBackgroundImageResizableLatticeXDivs,
            compBackgroundImageResizableLatticeXDivs: $compBackgroundImageResizableLatticeXDivs,
            enableCompBackgroundImageResizableLatticeYDivs: $enableCompBackgroundImageResizableLatticeYDivs,
            compBackgroundImageResizableLatticeYDivs: $compBackgroundImageResizableLatticeYDivs,
            enableCompBackgroundImageResizableLatticeFXCount: $enableCompBackgroundImageResizableLatticeFXCount,
            compBackgroundImageResizableLatticeFXCount: $compBackgroundImageResizableLatticeFXCount,
            enableCompBackgroundImageResizableLatticeFYCount: $enableCompBackgroundImageResizableLatticeFYCount,
            compBackgroundImageResizableLatticeFYCount: $compBackgroundImageResizableLatticeFYCount,
            enableCompBackgroundImageResizableLatticeFBounds: $enableCompBackgroundImageResizableLatticeFBounds,
            enableCompBackgroundImageResizableLatticeFBoundsLeft: $enableCompBackgroundImageResizableLatticeFBoundsLeft,
            compBackgroundImageResizableLatticeFBoundsLeft: $compBackgroundImageResizableLatticeFBoundsLeft,
            enableCompBackgroundImageResizableLatticeFBoundsTop: $enableCompBackgroundImageResizableLatticeFBoundsTop,
            compBackgroundImageResizableLatticeFBoundsTop: $compBackgroundImageResizableLatticeFBoundsTop,
            enableCompBackgroundImageResizableLatticeFBoundsRight:
            $enableCompBackgroundImageResizableLatticeFBoundsRight,
            compBackgroundImageResizableLatticeFBoundsRight: $compBackgroundImageResizableLatticeFBoundsRight,
            enableCompBackgroundImageResizableLatticeFBoundsBottom:
            $enableCompBackgroundImageResizableLatticeFBoundsBottom,
            compBackgroundImageResizableLatticeFBoundsBottom: $compBackgroundImageResizableLatticeFBoundsBottom,
            enableCompBackgroundImageResizableLatticeFColors: $enableCompBackgroundImageResizableLatticeFColors,
            compBackgroundImageResizableLatticeFColors: $compBackgroundImageResizableLatticeFColors,
            enableCompBackgroundBrightnessRate: $enableCompBackgroundBrightnessRate,
            compBackgroundBrightnessRate: $compBackgroundBrightnessRate,
            enableCompBackgroundBrightnessLightUpDegree: $enableCompBackgroundBrightnessLightUpDegree,
            compBackgroundBrightnessLightUpDegree: $compBackgroundBrightnessLightUpDegree
          })
          CompOpacityBlocks({
            enableCompOpacity: $enableCompOpacity,
            compOpacity: $compOpacity
          })
          ListItemGroup({
            header: this.ListItemGroupHeaders('通用属性1')
          }) {
            if (this.selection === '通用属性1') {
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
              CompShapeClippingBlocks({
                enableCompClip: $enableCompClip,
                compClip: $compClip,
                enableCompClipShape: $enableCompClipShape,
                enableCompClipShapeWidth: $enableCompClipShapeWidth,
                compClipShapeWidth: $compClipShapeWidth,
                enableCompClipShapeHeight: $enableCompClipShapeHeight,
                compClipShapeHeight: $compClipShapeHeight,
                enableCompMask: $enableCompMask,
                enableCompMaskValue: $enableCompMaskValue,
                compMaskValue: $compMaskValue,
                enableCompMaskColor: $enableCompMaskColor,
                compMaskColor: $compMaskColor,
                enableCompMaskShape: $enableCompMaskShape,
                enableCompMaskShapeWidth: $enableCompMaskShapeWidth,
                compMaskShapeWidth: $compMaskShapeWidth,
                enableCompMaskShapeHeight: $enableCompMaskShapeHeight,
                compMaskShapeHeight: $compMaskShapeHeight
              })
            }
          }

          ListItemGroup({
            header: this.ListItemGroupHeaders('通用属性2')
          }) {
            if (this.selection === '通用属性2') {
              CompImageEffectsBlocks({
                enableCompBlurValue: $enableCompBlurValue,
                compBlurValue: $compBlurValue,
                enableCompBlurOptionsNumber1: $enableCompBlurOptionsNumber1,
                compBlurOptionsNumber1: $compBlurOptionsNumber1,
                enableCompBlurOptionsNumber2: $enableCompBlurOptionsNumber2,
                compBlurOptionsNumber2: $compBlurOptionsNumber2,
                enableCompShadowValueRadius: $enableCompShadowValueRadius,
                compShadowValueRadius: $compShadowValueRadius,
                enableCompShadowValueType: $enableCompShadowValueType,
                compShadowValueType: $compShadowValueType,
                enableCompShadowValueColor: $enableCompShadowValueColor,
                compShadowValueColor: $compShadowValueColor,
                enableCompShadowValueOffsetX: $enableCompShadowValueOffsetX,
                compShadowValueOffsetX: $compShadowValueOffsetX,
                enableCompShadowValueOffsetY: $enableCompShadowValueOffsetY,
                compShadowValueOffsetY: $compShadowValueOffsetY,
                enableCompShadowValueFill: $enableCompShadowValueFill,
                compShadowValueFill: $compShadowValueFill,
                enableCompGrayscale: $enableCompGrayscale,
                compGrayscale: $compGrayscale,
                enableCompBrightness: $enableCompBrightness,
                compBrightness: $compBrightness,
                enableCompSaturate: $enableCompSaturate,
                compSaturate: $compSaturate,
                enableCompContrast: $enableCompContrast,
                compContrast: $compContrast,
                enableCompInvert: $enableCompInvert,
                compInvert: $compInvert,
                enableCompSepia: $enableCompSepia,
                compSepia: $compSepia,
                enableCompHueRotate: $enableCompHueRotate,
                compHueRotate: $compHueRotate,
                enableCompColorBlend: $enableCompColorBlend,
                compColorBlend: $compColorBlend,
                enableCompLinearGradientBlurValue: $enableCompLinearGradientBlurValue,
                compLinearGradientBlurValue: $compLinearGradientBlurValue,
                enableCompLinearGradientBlurOptionsFractionStops: $enableCompLinearGradientBlurOptionsFractionStops,
                compLinearGradientBlurOptionsFractionStops: $compLinearGradientBlurOptionsFractionStops,
                enableCompLinearGradientBlurOptionsDirection: $enableCompLinearGradientBlurOptionsDirection,
                compLinearGradientBlurOptionsDirection: $compLinearGradientBlurOptionsDirection,
                enableCompRenderGroup: $enableCompRenderGroup,
                compRenderGroup: $compRenderGroup,
                enableCompBlendModeValue: $enableCompBlendModeValue,
                compBlendModeValue: $compBlendModeValue,
                enableCompBlendModeType: $enableCompBlendModeType,
                compBlendModeType: $compBlendModeType,
                enableCompUseShadowBatching: $enableCompUseShadowBatching,
                compUseShadowBatching: $compUseShadowBatching,
                enableCompSphericalEffect: $enableCompSphericalEffect,
                compSphericalEffect: $compSphericalEffect,
                enableCompLightUpEffect: $enableCompLightUpEffect,
                compLightUpEffect: $compLightUpEffect,
                enableCompPixelStretchEffectOptionsLeft: $enableCompPixelStretchEffectOptionsLeft,
                compPixelStretchEffectOptionsLeft: $compPixelStretchEffectOptionsLeft,
                enableCompPixelStretchEffectOptionsRight: $enableCompPixelStretchEffectOptionsRight,
                compPixelStretchEffectOptionsRight: $compPixelStretchEffectOptionsRight,
                enableCompPixelStretchEffectOptionsTop: $enableCompPixelStretchEffectOptionsTop,
                compPixelStretchEffectOptionsTop: $compPixelStretchEffectOptionsTop,
                enableCompPixelStretchEffectOptionsBottom: $enableCompPixelStretchEffectOptionsBottom,
                compPixelStretchEffectOptionsBottom: $compPixelStretchEffectOptionsBottom,
                enableCompFreeze: $enableCompFreeze,
                compFreeze: $compFreeze
              })
            }
          }

          ListItemGroup({
            header: this.ListItemGroupHeaders('通用属性3')
          }) {
            if (this.selection === '通用属性3') {
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
            }
          }

          ListItemGroup({
            header: this.ListItemGroupHeaders('通用属性4')
          }) {
            if (this.selection === '通用属性4') {

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
            }
          }

          ListItemGroup({
            header: this.ListItemGroupHeaders('通用属性5')
          }) {
            if (this.selection === '通用属性5') {
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
              CompMotionBlurBlocks({
                enableCompMotionBlurRadius: $enableCompMotionBlurRadius,
                compMotionBlurRadius: $compMotionBlurRadius,
                enableCompMotionBlurAnchorX: $enableCompMotionBlurAnchorX,
                compMotionBlurAnchorX: $compMotionBlurAnchorX,
                enableCompMotionBlurAnchorY: $enableCompMotionBlurAnchorY,
                compMotionBlurAnchorY: $compMotionBlurAnchorY,
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
              CompAttributeModifierBlocks({
                enableCompAttributeModifier: $enableCompAttributeModifier,
                compAttributeModifier: $compAttributeModifier,
              })
            }
          }

          ListItemGroup({
            header: this.ListItemGroupHeaders('通用属性6')
          }) {
            if (this.selection === '通用属性6') {
              CompGestureModifierBlocks({
                enableCompGestureModifier: $enableCompGestureModifier,
                compGestureModifier: $compGestureModifier
              })

              CompOutlineBlocks({
                enableCompOutlineValueWidth: $enableCompOutlineValueWidth,
                compOutlineValueWidth: $compOutlineValueWidth,
                enableCompOutlineValueColor: $enableCompOutlineValueColor,
                compOutlineValueColor: $compOutlineValueColor,
                enableCompOutlineValueRadius: $enableCompOutlineValueRadius,
                compOutlineValueRadius: $compOutlineValueRadius,
                enableCompOutlineValueStyle: $enableCompOutlineValueStyle,
                compOutlineValueStyle: $compOutlineValueStyle
              })

              CompVisualEffectBlocks({
                enableCompVisualEffect: $enableCompVisualEffect,
                compVisualEffect: $compVisualEffect,
                enableCompBackgroundFilter: $enableCompBackgroundFilter,
                compBackgroundFilter: $compBackgroundFilter,
                enableCompForegroundFilter: $enableCompForegroundFilter,
                compForegroundFilter: $compForegroundFilter,
                enableCompCompositingFilter: $enableCompCompositingFilter,
                compCompositingFilter: $compCompositingFilter
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
            }
          }

          ListItemGroup({
            header: this.ListItemGroupHeaders('通用属性7')
          }) {
            if (this.selection === '通用属性7') {

              CompObscuringBlocks({
                enableCompObscured: $enableCompObscured, compObscured: $compObscured
              })

              CompRenderFitBlocks({
                enableCompRenderFit: $enableCompRenderFit, compRenderFit: $compRenderFit
              })

              CompEventMonopolizationBlocks({
                enableCompMonopolizeEvents: $enableCompMonopolizeEvents,
                compMonopolizeEvents: $compMonopolizeEvents
              })

              CompCursorControlBlocks({
                enableCompCursorControl: $enableCompCursorControl,
                compCursorControl: $compCursorControl
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
          }
        }
      }.width('100%')
    }
    .height('52%')
    .id('scroll')
  }


  @Builder
  ListItemGroupHeaders(str: string) {
    Row() {
      Text(str)
        .fontColor($r('sys.color.ohos_id_color_text_primary'))
        .fontWeight(FontWeight.Medium)
      Blank()
      Image($r('sys.media.ohos_ic_public_arrow_right'))
        .fillColor($r('sys.color.ohos_id_color_fourth'))
        .height(24)
        .width(24)
        .rotate({ angle: this.selection == str ? 90 : 0 })
        .animation({ curve: curves.interpolatingSpring(0, 1, 228, 30) })
    }
    .borderRadius(20)
    .width('100%')
    .padding({
      left: 8,
      right: 8,
      top: 18,
      bottom: 18
    })
    .onClick(() => {
      if (this.selection === str) {
        this.selection = null;
      } else {
        this.selection = str;
        AppStorage.setOrCreate('selection', this.selection)
      }
    })
  }
}

@Preview
@Component
struct LoadingProgressBootcampPreviewer {
  build() {
    LoadingProgressBootcamp({
      title: '加载进度/LoadingProgress'
    })
  }
}