import { SliderBlock } from 'common';

@Component
export struct CompForegroundEffectBlocks {
  @Link enableCompForegroundEffectRadius: boolean;
  @Link compForegroundEffectRadius: number;

  build() {
    Column() {

      SliderBlock({
        title: 'foregroundEffect.radius',
        isEnabled: $enableCompForegroundEffectRadius,
        value: $compForegroundEffectRadius,
        min: 0,
        max: 100
      })

    }
    .width('100%')
  }
}