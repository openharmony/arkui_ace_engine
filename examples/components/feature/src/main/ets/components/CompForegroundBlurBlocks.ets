import { RadioBlock, SliderBlock } from 'common';

@Component
export struct CompForegroundBlurBlocks {
  @Link enableCompForegroundBlurStyleValue: boolean;
  @Link compForegroundBlurStyleValue: BlurStyle;
  @Link enableCompForegroundBlurStyleOptionsColorMode: boolean;
  @Link compForegroundBlurStyleOptionsColorMode: ThemeColorMode;
  @Link enableCompForegroundBlurStyleOptionsAdaptiveColor: boolean;
  @Link compForegroundBlurStyleOptionsAdaptiveColor: AdaptiveColor;
  @Link enableCompForegroundBlurStyleOptionsBlurOptions: boolean;
  @Link compForegroundBlurStyleOptionsBlurOptions: number;
  @Link enableCompForegroundBlurStyleOptionsScale: boolean;
  @Link compForegroundBlurStyleOptionsScale: number;

  build() {
    Column() {

      RadioBlock({
        title: 'foregroundBlurStyle.value',
        isEnabled: $enableCompForegroundBlurStyleValue,
        value: $compForegroundBlurStyleValue,
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
          { label: 'COMPONENT_REGULAR', value: BlurStyle.COMPONENT_REGULAR },
          { label: 'COMPONENT_THICK', value: BlurStyle.COMPONENT_THICK },
          { label: 'COMPONENT_ULTRA_THICK', value: BlurStyle.COMPONENT_ULTRA_THICK },
        ]
      })

      RadioBlock({
        title: 'foregroundBlurStyle.options.colorMode',
        isEnabled: $enableCompForegroundBlurStyleOptionsColorMode,
        value: $compForegroundBlurStyleOptionsColorMode,
        dataSource: [
          { label: 'SYSTEM', value: ThemeColorMode.SYSTEM },
          { label: 'LIGHT', value: ThemeColorMode.LIGHT },
          { label: 'DARK', value: ThemeColorMode.DARK },
        ]
      })

      RadioBlock({
        title: 'foregroundBlurStyle.options.adaptiveColor',
        isEnabled: $enableCompForegroundBlurStyleOptionsAdaptiveColor,
        value: $compForegroundBlurStyleOptionsAdaptiveColor,
        dataSource: [
          { label: 'DEFAULT', value: AdaptiveColor.DEFAULT },
          { label: 'AVERAGE', value: AdaptiveColor.AVERAGE },
        ]
      })

      SliderBlock({
        title: 'foregroundBlurStyle.options.blurOptions',
        isEnabled: $enableCompForegroundBlurStyleOptionsBlurOptions,
        value: $compForegroundBlurStyleOptionsBlurOptions,
        min: 0,
        max: 100
      })

      SliderBlock({
        title: 'foregroundBlurStyle.options.scale',
        isEnabled: $enableCompForegroundBlurStyleOptionsScale,
        value: $compForegroundBlurStyleOptionsScale,
        min: 0,
        max: 100
      })


    }
    .width('100%')
  }
}