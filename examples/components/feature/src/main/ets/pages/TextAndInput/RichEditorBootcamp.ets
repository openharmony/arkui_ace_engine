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
import pasteboard from '@ohos.pasteboard';
import { BusinessError } from '@ohos.base';
import { Drawer } from 'common/src/main/ets/components/Drawer';
import { RadioBlock, useEnabled, ColorBlock, SliderBlock } from 'common';
import {
  matrix4,
  LengthMetrics,
  SelectionMenu,
  ExpandedMenuOptions,
  SelectionMenuOptions,
  ColorMetrics,
  promptAction,
  curves
} from '@kit.ArkUI';

import { common2D, uiEffect } from '@kit.ArkGraphics2D';
import { pointer } from '@kit.InputKit';
import { formatDate } from 'common/src/main/ets/utils/timeUtil';
import { BlockTag } from 'common/src/main/ets/model/BlockTag';
import { CompSizeBlocks } from './../../components/CompSizeBlocks'
import { CompLocationBlocks } from './../../components/CompLocationBlocks'
import { CompLayoutConstraintsBlocks } from './../../components/CompLayoutConstraintsBlocks'
import { CompBorderBlocks } from './../../components/CompBorderBlocks'
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
import { CompDragAndDropControlBlocks } from '../../components/CompDragAndDropControlBlocks';

class MyModifier implements AttributeModifier<RichEditorAttribute> {
  applyNormalAttribute(instance: RichEditorAttribute) {
    instance.backgroundColor('#0A59F7')
  }

  applyPressedAttribute(instance: RichEditorAttribute) {
    instance.backgroundColor('#ED6F21')
  }

  applyFocusedAttribute(instance: RichEditorAttribute) {
    instance.backgroundColor(Color.Gray)
  }

  applyDisabledAttribute(instance: RichEditorAttribute) {
    instance.backgroundColor('#E5E5E5')
  }

  applySelectedAttribute(instance: RichEditorAttribute) {
    instance.backgroundColor('#ffedea21')
  }
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
export struct RichEditorBootcamp {
  @Require @Prop title: ResourceStr;
  @State message: string =
    '华为UX设计规范用于指导软件界面的设计，确保给用户提供清晰一致、简单易用的使用体验，在产品组织内对齐设计语言，拉通体验设计的方向，帮助设计师统一设计品质。';
  @State sliderShow: boolean = false;
  controller: RichEditorController = new RichEditorController();
  private iconArr: Array<string> = ['剪切', '复制', '粘贴', '分享'];
  @State enablePaste: boolean = false;
  @State selectionMenuVisibilityValue: Visibility = Visibility.Visible;
  @State showParameters: boolean = false;
  @State enableCustomSelectionMenu: boolean = true;
  @State customSelectionMenu: boolean = false;
  @State enableTextSelectionMenu: boolean = true;
  @State textSelectionMenu: boolean = true;
  @State systemSelectionMenu: boolean = true;
  @State enableSystemSelectionMenu: boolean = true;
  @State enableDirection: boolean = false;
  @State compDirection: Direction = Direction.Auto;
  @State enableCompBackgroundColor: boolean = false;
  @State compBackgroundColor: ResourceColor | undefined = undefined;
  @State enableCustomKeyboardOption: boolean = false;
  @State customKeyboardOption: boolean = false;
  @State enableBindSelectionMenuSpanType: boolean = false;
  @State bindSelectionMenuSpanType: RichEditorSpanType = RichEditorSpanType.TEXT;
  @State enableBindSelectionMenuResponseType: boolean = false;
  @State bindSelectionMenuResponseType: ResponseType = ResponseType.LongPress;
  @State enableCopyOptions: boolean = false;
  @State copyOptions: CopyOptions = CopyOptions.LocalDevice;
  @State enableEnableDataDetector: boolean = false;
  @State enableDataDetector: boolean = false;
  @State enableDataDetectorConfigTypes: boolean = false;
  @State dataDetectorConfigTypes: TextDataDetectorType | undefined = undefined
  @State enableEnablePreviewText: boolean = false;
  @State enablePreviewText: boolean = true;
  @State enablePlaceholderFontValue: boolean = true;
  @State placeholderFontValue: string | undefined = '请输入';
  @State enablePlaceholderStyleFontSize: boolean = false;
  @State placeholderStyleFontSize: number = 16.0;
  @State enablePlaceholderStyleFontWeight: boolean = false;
  @State placeholderStyleFontWeight: FontWeight | number | string = FontWeight.Normal;
  @State enablePlaceholderStyleFontStyle: boolean = false;
  @State placeholderStyleFontStyle: FontStyle = FontStyle.Normal;
  @State enablePlaceholderStyleFontColor: boolean = false
  @State placeholderStyleFontColor: ResourceColor | undefined = undefined;
  @State enableCaretColor: boolean = false;
  @State caretColor: ResourceColor | undefined = '#007DFF';
  @State enableSelectedBackgroundColor: boolean = false;
  @State selectedBackgroundColor: ResourceColor | undefined = '#007DFF';
  @State enableEnterKeyType: boolean = false;
  @State enterKeyType: EnterKeyType = EnterKeyType.NEW_LINE;
  @State enableBarState: boolean = false;
  @State barState: BarState = BarState.Auto;
  @State enableEnableHapticFeedback: boolean = false;
  @State enableHapticFeedback: boolean = true;
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
  @State enableCompBackgroundAlign: boolean = false;
  @State compBackgroundAlign: Alignment = Alignment.Center;
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
  @State enableCompOpacity: boolean = false;
  @State compOpacity: number = 1;
  @State enableCompVisibility: boolean = false;
  @State compVisibility: Visibility = Visibility.Visible;
  @State enableCompEnabled: boolean = false;
  @State compEnabled: boolean = false;
  @State enableCompOverlay: boolean = false;
  @State compOverlay: string = 'overlay';
  @State enableCompOverlayOptions: boolean = false;
  @State enableCompOverlayOptionsAlign: boolean = false;
  @State compOverlayOptionsAlign: Alignment = Alignment.TopStart;
  @State enableCompOverlayOptionsOffsetX: boolean = false;
  @State compOverlayOptionsOffsetX: number = 0;
  @State enableCompOverlayOptionsOffsetY: boolean = false;
  @State compOverlayOptionsOffsetY: number = 0;
  @State enableCompZIndex: boolean = false;
  @State compZIndex: number = 0;
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
  @State enableCompHoverEffect: boolean = false;
  @State compHoverEffect: HoverEffect = HoverEffect.Auto;
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
  @State enableCompMotionBlurRadius: boolean = false;
  @State compMotionBlurRadius: number = 0;
  @State enableCompMotionBlurAnchorX: boolean = false;
  @State compMotionBlurAnchorX: number = 0;
  @State enableCompMotionBlurAnchorY: boolean = false;
  @State compMotionBlurAnchorY: number = 0;
  @State enableCompClickEffect: boolean = false;
  @State compClickEffect: boolean = false;
  @State enableCompClickEffectLevel: boolean = false;
  @State compClickEffectLevel: ClickEffectLevel = ClickEffectLevel.LIGHT;
  @State enableCompClickEffectScale: boolean = false;
  @State compClickEffectScale: number = 0.9;
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
  @State enableCompGestureModifier: boolean = false
  @State compGestureModifier: boolean = false
  myGestureModifier1: MyGestureModifier1 = new MyGestureModifier1()
  myGestureModifier2: MyGestureModifier2 = new MyGestureModifier2()
  @State enableCompOutlineValueWidth: boolean = false
  @State compOutlineValueWidth: number = 0
  @State enableCompOutlineValueColor: boolean = false
  @State compOutlineValueColor: ResourceColor = Color.Black
  @State enableCompOutlineValueRadius: boolean = false
  @State compOutlineValueRadius: number = 0
  @State enableCompOutlineValueStyle: boolean = false
  @State compOutlineValueStyle: OutlineStyle = OutlineStyle.SOLID
  @State enableCompVisualEffect: boolean = false
  @State compVisualEffect: boolean = false
  @State enableCompBackgroundFilter: boolean = false
  @State compBackgroundFilter: boolean = false
  @State enableCompForegroundFilter: boolean = false
  @State compForegroundFilter: boolean = false
  @State enableCompCompositingFilter: boolean = false
  @State compCompositingFilter: boolean = false
  @State enableCompResponseRegionValueX: boolean = false
  @State compResponseRegionValueX: number = 0
  @State enableCompResponseRegionValueY: boolean = false
  @State compResponseRegionValueY: number = 0
  @State enableCompResponseRegionValueWidth: boolean = false
  @State compResponseRegionValueWidth: Length = '100%'
  @State enableCompResponseRegionValueHeight: boolean = false
  @State compResponseRegionValueHeight: Length = '100%'
  @State enableCompHitTestBehavior: boolean = false
  @State compHitTestBehavior: HitTestMode = HitTestMode.Default
  @State enableCompObscured: boolean = false
  @State compObscured: Array<ObscuredReasons> = []
  @State enableCompDraggable: boolean = false
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
  @State enableCompExpandSafeAreaTypes: boolean = false
  @State compExpandSafeAreaTypes: Array<SafeAreaType> =
    [SafeAreaType.SYSTEM, SafeAreaType.CUTOUT, SafeAreaType.KEYBOARD]
  @State enableCompExpandSafeAreaEdges: boolean = false
  @State compExpandSafeAreaEdges: Array<SafeAreaEdge> =
    [SafeAreaEdge.TOP, SafeAreaEdge.BOTTOM, SafeAreaEdge.START, SafeAreaEdge.END]
  @State enableCompRenderFit: boolean = false
  @State compRenderFit: RenderFit = RenderFit.TOP_LEFT
  @State enableCompMonopolizeEvents: boolean = false
  @State compMonopolizeEvents: boolean = false
  @State enableCompCursorControl: boolean = false
  @State compCursorControl: pointer.PointerStyle = pointer.PointerStyle.DEFAULT
  @State enableCompUseEffect: boolean = false
  @State compUseEffect: boolean = false
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
  MySelectionMenu() {
    Column() {
      if (this.textSelectionMenu) {
        this.TextSelectionMenu()
      }
      if (this.systemSelectionMenu) {
        this.SystemSelectionMenu()
      }
    }
  }

  @Builder
  TextSelectionMenu() {
    Column() {
      Row({ space: 2 }) {
        if (this.controller) {
          ForEach(this.iconArr, (item: string, index: number) => {

            Flex({ justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center }) {
              Text(item)
                .padding(6)
                .borderRadius($r('sys.float.ohos_id_corner_radius_default_m'))
            }
            .borderRadius($r('sys.float.ohos_id_corner_radius_default_m'))
            .width(50)
            .height(40)
            .onClick(() => {
              if (index as number == 0) {
                if (!this.controller) {
                  return;
                }
                let richEditorSelection = this.controller.getSelection();
                this.pushDataToPasteboard(richEditorSelection)
                this.controller.deleteSpans({
                  start: richEditorSelection.selection[0],
                  end: richEditorSelection.selection[1]
                })
              } else if (index as number == 1) {
                if (!this.controller) {
                  return
                }
                let richEditorSelection = this.controller.getSelection();
                this.pushDataToPasteboard(richEditorSelection)
                this.controller.closeSelectionMenu()
              } else if (index as number == 2) {
                if (!this.controller) {
                  return;
                }
                let richEditorSelection = this.controller.getSelection();
                this.popDataFromPasteboard(richEditorSelection)

              } else if (index as number == 3) {
                if (!this.controller) {
                  return
                }
                this.controller.setSelection(-1, -1)
                this.selectionMenuVisibilityValue = Visibility.None;
              } else if (index as number == 4) {

              }
            })
          })
        }
      }
    }
    .clip(true)
    .borderRadius($r('sys.float.ohos_id_corner_radius_card'))
    .backgroundColor($r('sys.color.ohos_id_color_dialog_bg'))
    .shadow(ShadowStyle.OUTER_DEFAULT_MD)
  }

  @Builder
  SystemSelectionMenu() {
    Column() {
      Menu() {
        if (this.controller) {
          MenuItemGroup() {
            MenuItem({
              startIcon: $r('sys.media.ohos_ic_public_cut'),
              content: '剪切',
              labelInfo: 'Ctrl+X'
            })
              .onClick(() => {
                if (!this.controller) {
                  return;
                }
                let richEditorSelection = this.controller.getSelection();
                this.pushDataToPasteboard(richEditorSelection);
                this.controller.deleteSpans({
                  start: richEditorSelection.selection[0],
                  end: richEditorSelection.selection[1]
                })
              })
            MenuItem({
              startIcon: $r('sys.media.ohos_ic_public_copy'),
              content: '复制',
              labelInfo: 'Ctrl+C'
            })
              .onClick(() => {
                if (!this.controller) {
                  return;
                }
                let richEditorSelection = this.controller.getSelection();
                this.pushDataToPasteboard(richEditorSelection);
                this.controller.closeSelectionMenu();
              })
            MenuItem({
              startIcon: $r('sys.media.ohos_ic_public_paste'),
              content: '粘贴',
              labelInfo: 'Ctrl+V'
            })
              .enabled(this.enablePaste)
              .onClick(() => {
                if (!this.controller) {
                  return;
                }
                let richEditorSelection = this.controller.getSelection();
                this.popDataFromPasteboard(richEditorSelection);
              })
            MenuItem({
              startIcon: $r('sys.media.ohos_ic_public_select_all'),
              content: '全选',
              labelInfo: 'Ctrl+A'
            })
              .visibility(this.selectionMenuVisibilityValue)
              .onClick(() => {
                if (!this.controller) {
                  return;
                }
                this.controller.setSelection(-1, -1);
                this.selectionMenuVisibilityValue = Visibility.None;
              })
            MenuItem({ startIcon: $r('sys.media.ohos_ic_public_share'), content: '分享', labelInfo: '' })
              .enabled(false)
            MenuItem({ startIcon: $r('sys.media.ohos_ic_public_translate_c2e'), content: '翻译', labelInfo: '' })
              .enabled(false)
            MenuItem({ startIcon: $r('sys.media.ohos_ic_public_search_filled'), content: '搜索', labelInfo: '' })
              .enabled(false)
          }
        }
      }
      .onVisibleAreaChange([0.0, 1.0], () => {
        if (!this.controller) {
          return;
        }
        let richEditorSelection = this.controller.getSelection();
        let start = richEditorSelection.selection[0];
        let end = richEditorSelection.selection[1];
        if (start === 0 && this.controller.getSpans({ start: end + 1, end: end + 1 }).length === 0) {
          this.selectionMenuVisibilityValue = Visibility.None;
        } else {
          this.selectionMenuVisibilityValue = Visibility.Visible;
        }
      })
      .radius($r('sys.float.ohos_id_corner_radius_card'))
      .backgroundColor(Color.White)
    }
    .margin({ top: 8 })
  }

  pushDataToPasteboard(richEditorSelection: RichEditorSelection) {
    let sysBoard = pasteboard.getSystemPasteboard();
    let pasteData = pasteboard.createData(pasteboard.MIMETYPE_TEXT_PLAIN, '');
    if (richEditorSelection.spans && richEditorSelection.spans.length > 0) {
      let count = richEditorSelection.spans.length;
      for (let i = count - 1; i >= 0; i--) {
        let item = richEditorSelection.spans[i];
        if ((item as RichEditorTextSpanResult)?.textStyle) {
          let span = item as RichEditorTextSpanResult;
          let style = span.textStyle;
          let data = pasteboard.createRecord(pasteboard.MIMETYPE_TEXT_PLAIN, span.value.substring(span.offsetInSpan[0],
            span.offsetInSpan[1]))
          let prop = pasteData.getProperty();
          let temp: Record<string, Object> = {
            'color': style.fontColor,
            'size': style.fontSize,
            'style': style.fontStyle,
            'fontFamily': style.fontFamily,
            'decorationType': style.decoration.type,
            'decorationColor': style.decoration.color
          }
          prop.additions[i] = temp;
          pasteData.addRecord(data);
          pasteData.setProperty(prop);
        }
      }
    }
    sysBoard.clearData()
    sysBoard.setData(pasteData).then(() => {
      console.info('SelectionMenu copy option, Succeeded in setting PasteData.');
      this.enablePaste = true;
    }).catch((err: BusinessError) => {
      console.error('SelectionMenu copy option, Failed to set PasteData. Cause:' + err.message);
    })
  }

  popDataFromPasteboard(richEditorSeletion: RichEditorSelection) {
    let start = richEditorSeletion.selection[0];
    let end = richEditorSeletion.selection[1];

    if (start == end && this.controller) {
      start = this.controller.getCaretOffset();
      end = this.controller.getCaretOffset();
    }
  }
  @Builder
  Content() {
    Column() {
      Column() {
        RichEditor({ controller: this.controller })
          .onReady(() => {
            this.controller.addTextSpan(this.message)
          })
          .onSelect((value?: RichEditorSelection) => {
            this.compEventTriggeredLog('选中事件onSelect触发');
          })
          .onDidIMEInput((value?: TextRange) => {
            this.compEventTriggeredLog('输入法完成输入时事件onDidIMEInput触发');
          })
          .onIMEInputComplete((value: RichEditorTextSpanResult) => {
            this.compEventTriggeredLog('输入法完成输入后事件onIMEInputComplete触发');
          })
          .aboutToIMEInput((value: RichEditorInsertValue) => {
            this.compEventTriggeredLog('输入法输入内容前事件aboutToIMEInput触发');
            return true;
          })
          .aboutToDelete((value: RichEditorDeleteValue) => {
            this.compEventTriggeredLog('输入法删除内容前事件aboutToDelete触发');
            return true
          })
          .onDeleteComplete(() => {
            this.compEventTriggeredLog('输入法完成删除后事件onDeleteComplete触发');
          })
          .onPaste((event?: PasteEvent) => {
            this.compEventTriggeredLog('完成粘贴前事件onPaste触发');
          })
          .onSelectionChange((value?: RichEditorRange) => {
            this.compEventTriggeredLog('组件内所有内容选择区域发生变化或编辑状态下光标位置发生变化时触发事件onSelectionChange触发');
          })
          .onEditingChange((isEditing?: boolean) => {
            this.compEventTriggeredLog('组件内所有内容的编辑状态发生改变时事件onEditingChange触发');
          })
          .onSubmit((enterKey?: EnterKeyType, event?: SubmitEvent) => {
            this.compEventTriggeredLog('按下软键盘输入法回车键事件onSubmit触发');
          })
          .onWillChange((value: RichEditorChangeValue) => {
            this.compEventTriggeredLog('组件执行增删操作前事件onWillChange触发');
            return true;
          })
          .onDidChange((rangeBefore?: TextRange, rangeAfter?: TextRange) => {
            this.compEventTriggeredLog('组件执行增删操作后事件onDidChange触发');
          })
          .onCut((event?: CutEvent) => {
            this.compEventTriggeredLog('完成剪切前事件onCut触发');
          })
          .onCopy((event?: CopyEvent) => {
            this.compEventTriggeredLog('完成复制前事件onCopy触发');
          })
          .bindSelectionMenu(
            useEnabled(this.customSelectionMenu, RichEditorSpanType.TEXT),
            this.customSelectionMenu ? this.MySelectionMenu() : undefined,
            useEnabled(this.customSelectionMenu, RichEditorResponseType.RIGHT_CLICK),
            this.customSelectionMenu ? {
              onDisappear: () => {
                this.sliderShow = false;
              }
            } : undefined)
          .customKeyboard((result: void) => {
          },
            { supportAvoidance: useEnabled(this.enableCustomKeyboardOption, this.customKeyboardOption) })
          .bindSelectionMenu(
            useEnabled(this.customSelectionMenu, RichEditorSpanType.TEXT),
            this.customSelectionMenu ? this.MySelectionMenu() : undefined,
            useEnabled(this.customSelectionMenu, RichEditorResponseType.LONG_PRESS),
            this.customSelectionMenu ? {
              onDisappear: () => {
                this.sliderShow = false;
              }
            } : undefined)
          .direction(useEnabled(this.enableDirection, this.compDirection))
          .backgroundColor(useEnabled(this.enableCompBackgroundColor, this.compBackgroundColor))
          .bindSelectionMenu(useEnabled(this.enableBindSelectionMenuSpanType, this.bindSelectionMenuSpanType),
            this.compBackground(),
            useEnabled(this.enableBindSelectionMenuResponseType, this.bindSelectionMenuResponseType), {
              onDisappear: () => {
                this.compEventTriggeredLog(`自定义选择菜单关闭时回调`);
              },
              onAppear: () => {
                this.compEventTriggeredLog(`自定义选择菜单弹出时回调`);
              }
            }
          )
          .copyOptions(useEnabled(this.enableCopyOptions, this.copyOptions))
          .enableDataDetector(useEnabled(this.enableEnableDataDetector, this.enableDataDetector))
          .dataDetectorConfig({
            types: [useEnabled(this.enableDataDetectorConfigTypes, this.dataDetectorConfigTypes)],
            onDetectResultUpdate: (result: string) => {
            }
          })
          .enablePreviewText(useEnabled(this.enableEnablePreviewText, this.enablePreviewText))
          .placeholder(useEnabled(this.enablePlaceholderFontValue, this.placeholderFontValue),
            {
              font: {
                size: useEnabled(this.enablePlaceholderStyleFontSize, this.placeholderStyleFontSize),
                weight: useEnabled(this.enablePlaceholderStyleFontWeight, this.placeholderStyleFontWeight),
                style: useEnabled(this.enablePlaceholderStyleFontStyle, this.placeholderStyleFontStyle)
              },
              fontColor: useEnabled(this.enablePlaceholderStyleFontColor, this.placeholderStyleFontColor)
            })
          .caretColor(useEnabled(this.enableCaretColor, this.caretColor))
          .selectedBackgroundColor(useEnabled(this.enableSelectedBackgroundColor, this.selectedBackgroundColor))
          .enterKeyType(useEnabled(this.enableEnterKeyType, this.enterKeyType))
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
          .background(this.enableCompBackgroundAlign ? this.compBackground() : null,
            this.enableCompBackgroundAlign ? {
              align: useEnabled(this.enableCompBackgroundAlign, this.compBackgroundAlign)
            }
              : {}
          )
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
          .freeze(useEnabled(this.enableCompFreeze, this.compFreeze))
          .linearGradient({
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
          .key(useEnabled(this.enableCompKey, this.compKey) ? useEnabled(this.enableCompKey, this.compKey) : 'RichEditor')
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
          .attributeModifier(useEnabled(this.enableCompAttributeModifier, this.compAttributeModifier) ?
          this.modifier : null)
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
          .obscured(useEnabled(this.enableCompObscured,
            this.compObscured))
          .draggable(useEnabled(this.enableCompDraggable, this.compDraggable))
          .dragPreview(useEnabled(this.enableCompDragPreview, this.compDragPreview))
          .dragPreviewOptions({
            mode: useEnabled(this.enableCompDragPreviewOptionsValueMode, this.compDragPreviewOptionsValueMode),
            numberBadge: useEnabled(this.enableCompDragPreviewOptionsValueNumberBadge,
              this.compDragPreviewOptionsValueNumberBadge),
          }, {
            isMultiSelectionEnabled:
            useEnabled(this.enableCompDragPreviewOptionsOptionsIsMultiSelectionEnabled,
              this.compDragPreviewOptionsOptionsIsMultiSelectionEnabled),
            defaultAnimationBeforeLifting:
            useEnabled(this.enableCompDragPreviewOptionsOptionsDefaultAnimationBeforeLifting,
              this.compDragPreviewOptionsOptionsDefaultAnimationBeforeLifting)
          })
          .expandSafeArea(
            useEnabled(this.enableCompExpandSafeAreaTypes, this.compExpandSafeAreaTypes),
            useEnabled(this.enableCompExpandSafeAreaEdges, this.compExpandSafeAreaEdges))
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
  }
  @Builder
  Parameters() {
    Scroll(this.scroller) {
      Column({ space: 8 }) {
        RadioBlock({
          title: 'Direction',
          isEnabled: this.enableDirection,
          value: this.compDirection,
          dataSource: [
            { label: 'Auto', value: Direction.Auto },
            { label: 'Rtl', value: Direction.Rtl },
            { label: 'Ltr', value: Direction.Ltr }
          ]
        })
        RadioBlock({
          title: 'customSelectionMenu',
          isEnabled: this.enableCustomSelectionMenu,
          value: this.customSelectionMenu,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })
        if (this.customSelectionMenu) {
          RadioBlock({
            title: 'textSelectionMenu',
            isEnabled: this.enableTextSelectionMenu,
            value: this.textSelectionMenu,
            dataSource: [
              { label: 'true', value: true },
              { label: 'false', value: false }
            ]
          })
          RadioBlock({
            title: 'systemSelectionMenu',
            isEnabled: this.enableSystemSelectionMenu,
            value: this.systemSelectionMenu,
            dataSource: [
              { label: 'true', value: true },
              { label: 'false', value: false }
            ]
          })
        }

        ColorBlock({
          title: 'selectedBackgroundColor',
          isEnabled: this.enableSelectedBackgroundColor,
          color: this.selectedBackgroundColor,
        })
        ColorBlock({
          title: 'BackgroundColor',
          isEnabled: this.enableCompBackgroundColor,
          color: this.compBackgroundColor,
        })

        RadioBlock({
          title: 'customKeyboard.option',
          isEnabled: this.enableCustomKeyboardOption,
          value: this.customKeyboardOption,
          dataSource: [
            { label: 'false', value: false },
            { label: 'true', value: true },
          ]
        })

        RadioBlock({
          title: 'bindSelectionMenu.spanType',
          isEnabled: this.enableBindSelectionMenuSpanType,
          value: this.bindSelectionMenuSpanType,
          dataSource: [
            { label: 'TEXT', value: TextSpanType.TEXT },
            { label: 'IMAGE', value: TextSpanType.IMAGE },
            { label: 'MIXED', value: TextSpanType.MIXED },
          ]
        })

        RadioBlock({
          title: 'bindSelectionMenu.responseType',
          isEnabled: this.enableBindSelectionMenuResponseType,
          value: this.bindSelectionMenuResponseType,
          dataSource: [
            { label: 'RIGHT_CLICK', value: TextResponseType.RIGHT_CLICK },
            { label: 'LONG_PRESS', value: TextResponseType.LONG_PRESS },
            { label: 'SELECT', value: TextResponseType.SELECT },
          ]
        })

        RadioBlock({
          title: 'copyOptions',
          isEnabled: this.enableCopyOptions,
          value: this.copyOptions,
          dataSource: [
            { label: 'None', value: CopyOptions.None },
            { label: 'InApp', value: CopyOptions.InApp },
            { label: 'LocalDevice', value: CopyOptions.LocalDevice },
          ]
        })

        RadioBlock({
          title: 'enableDataDetector',
          isEnabled: this.enableEnableDataDetector,
          value: this.enableDataDetector,
          dataSource: [
            { label: 'false', value: false },
            { label: 'true', value: true },
          ]
        })

        RadioBlock({
          title: 'textDataDetectorConfig.types',
          isEnabled: this.enableDataDetectorConfigTypes,
          value: this.dataDetectorConfigTypes,
          dataSource: [
            { label: 'NULL', value: [] },
            { label: 'PHONE_NUMBER', value: TextDataDetectorType.PHONE_NUMBER },
            { label: 'URL', value: TextDataDetectorType.URL },
            { label: 'EMAIL', value: TextDataDetectorType.EMAIL },
            { label: 'ADDRESS', value: TextDataDetectorType.ADDRESS },
            { label: 'DATE_TIME', value: TextDataDetectorType.DATE_TIME },
          ]
        })

        RadioBlock({
          title: 'enablePreviewText',
          isEnabled: this.enableEnablePreviewText,
          value: this.enablePreviewText,
          dataSource: [
            { label: 'false', value: false },
            { label: 'true', value: true },
          ]
        })


        SliderBlock({
          title: 'placeholderStyle.font.size',
          isEnabled: this.enablePlaceholderStyleFontSize,
          value: this.placeholderStyleFontSize,
          min: 1,
          max: 200
        })

        RadioBlock({
          title: 'placeholderStyle.font.weight',
          isEnabled: this.enablePlaceholderStyleFontWeight,
          value: this.placeholderStyleFontWeight,
          dataSource: [
            { label: '100', value: 100 },
            { label: '200', value: 200 },
            { label: '300', value: 300 },
            { label: '400', value: 400 },
            { label: '500', value: 500 },
            { label: '600', value: 600 },
            { label: '700', value: 700 },
            { label: '800', value: 800 },
            { label: '900', value: 900 },
            { label: 'Lighter', value: FontWeight.Lighter },
            { label: 'Normal', value: FontWeight.Normal },
            { label: 'Regular', value: FontWeight.Regular },
            { label: 'Medium', value: FontWeight.Medium },
            { label: 'Bold', value: FontWeight.Bold },
            { label: 'Bolder', value: FontWeight.Bolder },
          ]
        })

        RadioBlock({
          title: 'placeholderStyle.font.style',
          isEnabled: this.enablePlaceholderStyleFontStyle,
          value: this.placeholderStyleFontStyle,
          dataSource: [
            { label: 'Normal', value: FontStyle.Normal },
            { label: 'Italic', value: FontStyle.Italic },
          ]
        })

        ColorBlock({
          title: 'placeholderStyle.fontColor',
          isEnabled: this.enablePlaceholderStyleFontColor,
          color: this.placeholderStyleFontColor,
        })

        ColorBlock({
          title: 'caretColor',
          isEnabled: this.enableCaretColor,
          color: this.caretColor,
        })


        RadioBlock({
          title: 'enterKeyType',
          isEnabled: this.enableEnterKeyType,
          value: this.enterKeyType,
          dataSource: [
            { label: 'Go', value: EnterKeyType.Go },
            { label: 'Search', value: EnterKeyType.Search },
            { label: 'Send', value: EnterKeyType.Send },
            { label: 'Next', value: EnterKeyType.Next },
            { label: 'Done', value: EnterKeyType.Done },
            { label: 'PREVIOUS', value: EnterKeyType.PREVIOUS },
            { label: 'NEW_LINE', value: EnterKeyType.NEW_LINE },
          ]
        })
      }
    }
    .height('52%')
    .id('scroll')
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
              CompDragAndDropControlBlocks({
                enableCompDraggable: $enableCompDraggable,
                compDraggable: $compDraggable,
                enableCompDragPreview: $enableCompDragPreview,
                compDragPreview: $compDragPreview,
                enableCompDragPreviewOptionsValueMode:
                $enableCompDragPreviewOptionsValueMode,
                compDragPreviewOptionsValueMode:
                $compDragPreviewOptionsValueMode,
                enableCompDragPreviewOptionsValueNumberBadge:
                $enableCompDragPreviewOptionsValueNumberBadge,
                compDragPreviewOptionsValueNumberBadge:
                $compDragPreviewOptionsValueNumberBadge,
                enableCompDragPreviewOptionsOptionsIsMultiSelectionEnabled:
                $enableCompDragPreviewOptionsOptionsIsMultiSelectionEnabled,
                compDragPreviewOptionsOptionsIsMultiSelectionEnabled:
                $compDragPreviewOptionsOptionsIsMultiSelectionEnabled,
                enableCompDragPreviewOptionsOptionsDefaultAnimationBeforeLifting:
                $enableCompDragPreviewOptionsOptionsDefaultAnimationBeforeLifting,
                compDragPreviewOptionsOptionsDefaultAnimationBeforeLifting:
                $compDragPreviewOptionsOptionsDefaultAnimationBeforeLifting
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
}

@Preview
@Component
struct RichEditorBootcampPreviewer {
  build() {
    RichEditorBootcamp({
      title: '富文本/RichEditor'
    })
  }
}