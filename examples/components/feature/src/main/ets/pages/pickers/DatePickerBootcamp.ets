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
import { ColorBlock, RadioBlock, SliderBlock, useEnabled } from 'common';
import { common2D, uiEffect } from '@kit.ArkGraphics2D';
import { formatDate } from 'common/src/main/ets/utils/timeUtil';
import { BlockTag } from 'common/src/main/ets/model/BlockTag';
import { pointer } from '@kit.InputKit';
import { ColorMetrics, LengthMetrics, matrix4, promptAction } from '@kit.ArkUI';
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
import { CompModalTransitionBlocks } from '../../components/CompModalTransitionBlocks'
import { CompSheetTransitionBlocks } from '../../components/CompSheetTransitionBlocks'
import { CompObscuringBlocks } from '../../components/CompObscuringBlocks'
import { CompRenderFitBlocks } from '../../components/CompRenderFitBlocks'
import { CompEventMonopolizationBlocks } from '../../components/CompEventMonopolizationBlocks'
import { CompCursorControlBlocks } from '../../components/CompCursorControlBlocks'
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
import { CompMotionBlurBlocks } from '../../components/CompMotionBlurBlocks';
import { CompClickEffectBlocks } from '../../components/CompClickEffectBlocks';
import { CompAccessibilityBlocks } from '../../components/CompAccessibilityBlocks';
import { CompAttributeModifierBlocks } from '../../components/CompAttributeModifierBlocks';



//part2
class MyModifier implements AttributeModifier<DatePickerAttribute> {
  applyNormalAttribute(instance: DatePickerAttribute) {
    instance.backgroundColor('#0A59F7')
  }
  applyPressedAttribute(instance: DatePickerAttribute) {
    instance.backgroundColor('#ED6F21')
  }
  applyFocusedAttribute(instance: DatePickerAttribute) {
    instance.backgroundColor(Color.Gray)
  }
  applyDisabledAttribute(instance: DatePickerAttribute) {
    instance.backgroundColor('#E5E5E5')
  }
  applySelectedAttribute(instance: DatePickerAttribute) {
    instance.backgroundColor('#ffedea21')
  }
}

//part3
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
export struct DatePickerBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State enableLunar: boolean = false;
  @State lunar: boolean = false;
  @State enableDisappearTextStyleColor: boolean = false;
  @State disappearTextStyleColor: ResourceColor = '#ff182431';
  @State enableDisappearTextStyleFontSize: boolean = false;
  @State disappearTextStyleFontSize: Length = '14fp';
  @State enableDisappearTextStyleFontWeight: boolean = false;
  @State disappearTextStyleFontWeight: FontWeight = FontWeight.Regular;
  @State enableTextStyleColor: boolean = false;
  @State textStyleColor: ResourceColor = '#ff182431';
  @State enableTextStyleFontSize: boolean = false;
  @State textStyleFontSize: Length = '16fp';
  @State enableTextStyleFontWeight: boolean = false;
  @State textStyleFontWeight: FontWeight = FontWeight.Regular;
  @State enableSelectedTextStyleColor: boolean = false;
  @State selectedTextStyleColor: ResourceColor = '#ff007dff';
  @State enableSelectedTextStyleFontSize: boolean = false;
  @State selectedTextStyleFontSize: Length = '20vp';
  @State enableSelectedTextStyleFontWeight: boolean = false;
  @State selectedTextStyleFontWeight: FontWeight = FontWeight.Medium;
  @State compWidth: Length = 'auto';
  @State compHeight: Length = 'auto';
  @State enableCompFlexBasis: boolean = false;
  @State compFlexBasis: number | string = 'auto';
  @State enableCompDirection: boolean = false;
  @State compDirection: Direction = Direction.Auto;
  //part1
  // size
  @State enableCompWidth: boolean = false;
  @State enableCompHeight: boolean = false;
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
  @State compBackgroundColor: ResourceColor =  '#ff000000';
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
  //part2
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

  private selectedDate: Date = new Date();

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
    .backgroundColor($r('sys.color.ohos_id_color_sub_background'))
    .hideTitleBar(true)
  }

  //builder
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
    Column({ space: 8 }) {
      Column() {
        DatePicker({
          start: new Date('1970-1-1'),
          end: new Date('2100-1-1'),
          selected: this.selectedDate
        })
          .lunar(useEnabled(this.enableLunar, this.lunar))
          .disappearTextStyle({
            color: useEnabled(this.enableDisappearTextStyleColor, this.disappearTextStyleColor),
            font: {
              size: useEnabled(this.enableDisappearTextStyleFontSize, this.disappearTextStyleFontSize),
              weight: useEnabled(this.enableDisappearTextStyleFontWeight, this.disappearTextStyleFontWeight)
            }
          })
          .textStyle({
            color: useEnabled(this.enableTextStyleColor, this.textStyleColor),
            font: {
              size: useEnabled(this.enableTextStyleFontSize, this.textStyleFontSize),
              weight: useEnabled(this.enableTextStyleFontWeight, this.textStyleFontWeight)
            }
          })
          .selectedTextStyle({
            color: useEnabled(this.enableSelectedTextStyleColor, this.selectedTextStyleColor),
            font: {
              size: useEnabled(this.enableSelectedTextStyleFontSize, this.selectedTextStyleFontSize),
              weight: useEnabled(this.enableSelectedTextStyleFontWeight, this.selectedTextStyleFontWeight)
            }
          })
          .flexBasis(useEnabled(this.enableCompFlexBasis, this.compFlexBasis))
          .direction(useEnabled(this.enableCompDirection, this.compDirection))
            //part1
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
          .mask(this.progress)
          .maskShape(this.enableCompMaskShape ? new Circle({
            width: useEnabled(
              this.enableCompMaskShapeWidth,
              this.compMaskShapeWidth
            ) + 'px',
            height: useEnabled(
              this.enableCompMaskShapeHeight,
              this.compMaskShapeHeight
            ) + 'px'
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
          .freeze(useEnabled(this.enableCompFreeze, this.compFreeze))//part2
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
          .reuseId(useEnabled(this.enableCompReuseId, this.compReuseId) ?
          useEnabled(this.enableCompReuseId, this.compReuseId) : null)
          .restoreId(useEnabled(this.enableCompRestoreId, this.compRestoreId) ?
          useEnabled(this.enableCompRestoreId, this.compRestoreId) : null)
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
          .bindMenu(this.MyMenu)
          .attributeModifier(useEnabled(this.enableCompAttributeModifier, this.compAttributeModifier) ?
          this.modifier : null)//part3
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
          .obscured(useEnabled(this.enableCompObscured,
            this.compObscured))
          .renderFit(useEnabled(this.enableCompRenderFit, this.compRenderFit))
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
          .useEffect(useEnabled(this.enableCompUseEffect, this.compUseEffect))//compEvent
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
          .onDateChange((value: Date)=>{
            this.compEventTriggeredLog('选择日期onDateChange触发')
          })
      }
    }.width('100%').height('100%')
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {
        RadioBlock({
          title: 'lunar',
          isEnabled: $enableLunar,
          value: $lunar,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })

        ColorBlock({
          title: 'disappearTextStyle.color',
          isEnabled: $enableDisappearTextStyleColor,
          color: $disappearTextStyleColor
        })

        SliderBlock({
          title: 'disappearTextStyle.font.size',
          isEnabled: $enableDisappearTextStyleFontSize,
          value: $disappearTextStyleFontSize,
          min: 10,
          max: 30
        })

        RadioBlock({
          title: 'disappearTextStyle.font.weight',
          isEnabled: $enableDisappearTextStyleFontWeight,
          value: $disappearTextStyleFontWeight,
          dataSource: [
            { label: 'Regular', value: FontWeight.Regular },
            { label: 'Medium', value: FontWeight.Medium },
          ]
        })

        ColorBlock({
          title: 'textStyle.color',
          isEnabled: $enableTextStyleColor,
          color: $textStyleColor
        })

        SliderBlock({
          title: 'textStyle.font.size',
          isEnabled: $enableTextStyleFontSize,
          value: $textStyleFontSize,
          min: 10,
          max: 30
        })

        RadioBlock({
          title: 'textStyle.font.weight',
          isEnabled: $enableTextStyleFontWeight,
          value: $textStyleFontWeight,
          dataSource: [
            { label: 'Regular', value: FontWeight.Regular },
            { label: 'Medium', value: FontWeight.Medium },
          ]
        })

        ColorBlock({
          title: 'selectedTextStyle.color',
          isEnabled: $enableSelectedTextStyleColor,
          color: $selectedTextStyleColor
        })

        SliderBlock({
          title: 'selectedTextStyle.font.size',
          isEnabled: $enableSelectedTextStyleFontSize,
          value: $selectedTextStyleFontSize,
          min: 10,
          max: 30
        })

        RadioBlock({
          title: 'selectedTextStyle.font.weight',
          isEnabled: $enableSelectedTextStyleFontWeight,
          value: $selectedTextStyleFontWeight,
          dataSource: [
            { label: 'Regular', value: FontWeight.Regular },
            { label: 'Medium', value: FontWeight.Medium },
          ]
        })

        SliderBlock({
          title: 'flexBasis',
          isEnabled: $enableCompFlexBasis,
          value: $compFlexBasis,
          min: 120,
          max: 300
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

        //part1
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

        //part2
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

        //part3
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

        CompRenderFitBlocks({
          enableCompRenderFit: $enableCompRenderFit, compRenderFit: $compRenderFit
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
      }.width('100%')
    }.height('50%')
  }
}

@Preview
@Component
struct DatePickerBootcampPreviewer {
  build() {
    DatePickerBootcamp({
      title: '日期选择器/DatePicker'
    })
  }
}