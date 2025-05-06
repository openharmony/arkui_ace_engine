import { RadioBlock, SliderBlock } from 'common';

;

@Component
export struct CompClickEffectBlocks {
  @Link enableCompClickEffect: boolean;
  @Link compClickEffect: boolean;
  @Link enableCompClickEffectLevel: boolean;
  @Link compClickEffectLevel: ClickEffectLevel;
  @Link enableCompClickEffectScale: boolean;
  @Link compClickEffectScale: number;

  build() {
    Column() {

      RadioBlock({
        title: 'clickEffect',
        isEnabled: $enableCompClickEffect,
        value: $compClickEffect,
        dataSource: [
          { label: 'true', value: true },
          { label: 'false', value: false },
        ]
      })

      RadioBlock({
        title: 'clickEffect.level',
        isEnabled: $enableCompClickEffectLevel,
        value: $compClickEffectLevel,
        dataSource: [
          { label: 'LIGHT', value: ClickEffectLevel.LIGHT },
          { label: 'MIDDLE', value: ClickEffectLevel.MIDDLE },
          { label: 'HEAVY', value: ClickEffectLevel.HEAVY },
        ]
      })

      SliderBlock({
        title: 'clickEffect.scale',
        isEnabled: $enableCompClickEffectScale,
        value: $compClickEffectScale,
        step: 0.1,
        min: 0,
        max: 1
      })

    }
    .width('100%')
  }
}