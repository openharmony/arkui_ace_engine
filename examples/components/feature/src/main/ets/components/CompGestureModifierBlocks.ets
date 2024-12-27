import { RadioBlock } from 'common';


@Component
export struct CompGestureModifierBlocks {
  @Link enableCompGestureModifier: boolean;
  @Link compGestureModifier: boolean;

  build() {
    Column() {
      RadioBlock({
        title: 'gestureModifier',
        isEnabled: $enableCompGestureModifier,
        value: $compGestureModifier,
        dataSource: [
          { label: 'Two fingers double click', value: true },
          { label: 'none', value: false },
        ]
      })
    }
  }
}