import { RadioBlock } from 'common';

@Component
export struct CompHoverEffectBlocks {
  @Link enableCompHoverEffect: boolean;
  @Link compHoverEffect: HoverEffect;

  build() {
    Column() {

      RadioBlock({
        title: 'hoverEffect',
        isEnabled: $enableCompHoverEffect,
        value: $compHoverEffect,
        dataSource: [
          { label: 'Auto', value: HoverEffect.Auto },
          { label: 'Scale', value: HoverEffect.Scale },
          { label: 'Highlight', value: HoverEffect.Highlight },
          { label: 'None', value: HoverEffect.None },
        ]
      })

    }
    .width('100%')
  }
}