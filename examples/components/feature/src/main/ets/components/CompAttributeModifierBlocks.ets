import { RadioBlock } from 'common';

@Component
export struct CompAttributeModifierBlocks {
  @Link enableCompAttributeModifier: boolean;
  @Link compAttributeModifier: boolean;

  build() {
    Column() {
      RadioBlock({
        title: 'attributeModifier',
        isEnabled: $enableCompAttributeModifier,
        value: $compAttributeModifier,
        dataSource: [
          { label: 'true', value: true },
          { label: 'false', value: false }
        ]
      })
    }
    .width('100%')
  }
}