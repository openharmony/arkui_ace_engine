import { RadioBlock, ColorBlock, SliderBlock } from 'common';

@Component
export struct CompImageEffectsBlocks {
  @Link enableCompBlurValue: boolean;
  @Link compBlurValue: number;
  @Link enableCompBlurOptionsNumber1: boolean;
  @Link compBlurOptionsNumber1: number;
  @Link enableCompBlurOptionsNumber2: boolean;
  @Link compBlurOptionsNumber2: number;
  @Link enableCompShadowValueRadius: boolean;
  @Link compShadowValueRadius: number;
  @Link enableCompShadowValueType: boolean;
  @Link compShadowValueType: ShadowType;
  @Link enableCompShadowValueColor: boolean;
  @Link compShadowValueColor: ResourceColor;
  @Link enableCompShadowValueOffsetX: boolean;
  @Link compShadowValueOffsetX: number;
  @Link enableCompShadowValueOffsetY: boolean;
  @Link compShadowValueOffsetY: number;
  @Link enableCompShadowValueFill: boolean;
  @Link compShadowValueFill: boolean;
  @Link enableCompGrayscale: boolean;
  @Link compGrayscale: number;
  @Link enableCompBrightness: boolean;
  @Link compBrightness: number;
  @Link enableCompSaturate: boolean;
  @Link compSaturate: number;
  @Link enableCompContrast: boolean;
  @Link compContrast: number;
  @Link enableCompInvert: boolean;
  @Link compInvert: number;
  @Link enableCompSepia: boolean;
  @Link compSepia: number;
  @Link enableCompHueRotate: boolean;
  @Link compHueRotate: number;
  @Link enableCompColorBlend: boolean;
  @Link compColorBlend: ResourceColor | undefined;
  @Link enableCompLinearGradientBlurValue: boolean;
  @Link compLinearGradientBlurValue: number;
  @Link enableCompLinearGradientBlurOptionsFractionStops: boolean;
  @Link compLinearGradientBlurOptionsFractionStops: Array<FractionStop>;
  @Link enableCompLinearGradientBlurOptionsDirection: boolean;
  @Link compLinearGradientBlurOptionsDirection: GradientDirection;
  @Link enableCompRenderGroup: boolean;
  @Link compRenderGroup: boolean;
  @Link enableCompBlendModeValue: boolean;
  @Link compBlendModeValue: BlendMode;
  @Link enableCompBlendModeType: boolean;
  @Link compBlendModeType: BlendApplyType;
  @Link enableCompUseShadowBatching: boolean;
  @Link compUseShadowBatching: boolean;
  @Link enableCompSphericalEffect: boolean;
  @Link compSphericalEffect: number;
  @Link enableCompLightUpEffect: boolean;
  @Link compLightUpEffect: number;
  @Link enableCompPixelStretchEffectOptionsLeft: boolean;
  @Link compPixelStretchEffectOptionsLeft: number;
  @Link enableCompPixelStretchEffectOptionsRight: boolean;
  @Link compPixelStretchEffectOptionsRight: number;
  @Link enableCompPixelStretchEffectOptionsTop: boolean;
  @Link compPixelStretchEffectOptionsTop: number;
  @Link enableCompPixelStretchEffectOptionsBottom: boolean;
  @Link compPixelStretchEffectOptionsBottom: number;
  @Link enableCompFreeze: boolean;
  @Link compFreeze: boolean;

  build() {
    Column() {
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

      SliderBlock({
        title: 'linearGradientBlur.value',
        isEnabled: $enableCompLinearGradientBlurValue,
        value: $compLinearGradientBlurValue,
        min: 0,
        max: 60
      })

      RadioBlock({
        title: 'linearGradientBlur.options.fractionStops',
        isEnabled: $enableCompLinearGradientBlurOptionsFractionStops,
        value: $compLinearGradientBlurOptionsFractionStops,
        dataSource: [
          { label: '[[0.1,0,5],[0.2,1]]', value: [[0.1, 0, 5], [0.2, 1]] },
          { label: '[[0.1,0.33],[0.2,0.66],[0.3,1]]', value: [[0.1, 0.33], [0.2, 0.66], [0.3, 1]] },
          {
            label: '[[0.4,0.25],[0.3,0.5],[0.2,0.75],[0.1,1]]',
            value: [[0.4, 0.25], [0.3, 0.5], [0.2, 0.75], [0.1, 1]]
          },
        ]
      })

      RadioBlock({
        title: 'linearGradientBlur.options.direction',
        isEnabled: $enableCompLinearGradientBlurOptionsDirection,
        value: $compLinearGradientBlurOptionsDirection,
        dataSource: [
          { label: 'Left', value: GradientDirection.Left },
          { label: 'Top', value: GradientDirection.Top },
          { label: 'Right', value: GradientDirection.Right },
          { label: 'Bottom', value: GradientDirection.Bottom },
          { label: 'LeftTop', value: GradientDirection.LeftTop },
          { label: 'LeftBottom', value: GradientDirection.LeftBottom },
          { label: 'RightTop', value: GradientDirection.RightTop },
          { label: 'RightBottom', value: GradientDirection.RightBottom },
          { label: 'None', value: GradientDirection.None },
        ]
      })

      RadioBlock({
        title: 'renderGroup',
        isEnabled: $enableCompRenderGroup,
        value: $compRenderGroup,
        dataSource: [
          { label: 'true', value: true },
          { label: 'false', value: false },
        ]
      })

      RadioBlock({
        title: 'blendMode.value',
        isEnabled: $enableCompBlendModeValue,
        value: $compBlendModeValue,
        dataSource: [
          { label: 'NONE', value: BlendMode.NONE },
          { label: 'CLEAR', value: BlendMode.CLEAR },
          { label: 'SRC', value: BlendMode.SRC },
          { label: 'DST', value: BlendMode.DST },
          { label: 'SRC_OVER', value: BlendMode.SRC_OVER },
          { label: 'DST_OVER', value: BlendMode.DST_OVER },
          { label: 'SRC_IN', value: BlendMode.SRC_IN },
          { label: 'DST_IN', value: BlendMode.DST_IN },
          { label: 'SRC_OUT', value: BlendMode.SRC_OUT },
          { label: 'DST_OUT', value: BlendMode.DST_OUT },
          { label: 'SRC_ATOP', value: BlendMode.SRC_ATOP },
          { label: 'DST_ATOP', value: BlendMode.DST_ATOP },
          { label: 'XOR', value: BlendMode.XOR },
          { label: 'PLUS', value: BlendMode.PLUS },
          { label: 'MODULATE', value: BlendMode.MODULATE },
          { label: 'SCREEN', value: BlendMode.SCREEN },
          { label: 'OVERLAY', value: BlendMode.OVERLAY },
          { label: 'DARKEN', value: BlendMode.DARKEN },
          { label: 'LIGHTEN', value: BlendMode.LIGHTEN },
          { label: 'COLOR_DODGE', value: BlendMode.COLOR_DODGE },
          { label: 'COLOR_BURN', value: BlendMode.COLOR_BURN },
          { label: 'HARD_LIGHT', value: BlendMode.HARD_LIGHT },
          { label: 'SOFT_LIGHT', value: BlendMode.SOFT_LIGHT },
          { label: 'DIFFERENCE', value: BlendMode.DIFFERENCE },
          { label: 'EXCLUSION', value: BlendMode.EXCLUSION },
          { label: 'MULTIPLY', value: BlendMode.MULTIPLY },
          { label: 'HUE', value: BlendMode.HUE },
          { label: 'SATURATION', value: BlendMode.SATURATION },
          { label: 'COLOR', value: BlendMode.COLOR },
          { label: 'LUMINOSITY', value: BlendMode.LUMINOSITY },
        ]
      })

      RadioBlock({
        title: 'blendMode.type',
        isEnabled: $enableCompBlendModeType,
        value: $compBlendModeType,
        dataSource: [
          { label: 'FAST', value: BlendApplyType.FAST },
          { label: 'OFFSCREEN', value: BlendApplyType.OFFSCREEN },
        ]
      })

      RadioBlock({
        title: 'useShadowBatching',
        isEnabled: $enableCompUseShadowBatching,
        value: $compUseShadowBatching,
        dataSource: [
          { label: 'true', value: true },
          { label: 'false', value: false },
        ]
      })

      SliderBlock({
        title: 'sphericalEffect',
        isEnabled: $enableCompSphericalEffect,
        value: $compSphericalEffect,
        min: 0,
        max: 1,
        step: 0.1
      })

      SliderBlock({
        title: 'lightUpEffect',
        isEnabled: $enableCompLightUpEffect,
        value: $compLightUpEffect,
        min: 0,
        max: 1,
        step: 0.1
      })

      SliderBlock({
        title: 'pixelStretchEffect.options.left',
        isEnabled: $enableCompPixelStretchEffectOptionsLeft,
        value: $compPixelStretchEffectOptionsLeft,
        min: 0,
        max: 20
      })

      SliderBlock({
        title: 'pixelStretchEffect.options.right',
        isEnabled: $enableCompPixelStretchEffectOptionsRight,
        value: $compPixelStretchEffectOptionsRight,
        min: 0,
        max: 20
      })

      SliderBlock({
        title: 'pixelStretchEffect.options.top',
        isEnabled: $enableCompPixelStretchEffectOptionsTop,
        value: $compPixelStretchEffectOptionsTop,
        min: 0,
        max: 20
      })

      SliderBlock({
        title: 'pixelStretchEffect.options.bottom',
        isEnabled: $enableCompPixelStretchEffectOptionsBottom,
        value: $compPixelStretchEffectOptionsBottom,
        min: 0,
        max: 20
      })

      RadioBlock({
        title: 'freeze',
        isEnabled: $enableCompFreeze,
        value: $compFreeze,
        dataSource: [
          { label: 'true', value: true },
          { label: 'false', value: false },
        ]
      })
    }
  }
}