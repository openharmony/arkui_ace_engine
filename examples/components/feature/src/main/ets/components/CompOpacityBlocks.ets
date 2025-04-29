import { SliderBlock } from 'common';

@Component
export struct CompOpacityBlocks {
  @Link enableCompOpacity: boolean;
  @Link compOpacity: number;

  build() {
    Column() {
      SliderBlock({
        title: 'opacity',
        isEnabled: $enableCompOpacity,
        value: $compOpacity,
        min: 0,
        max: 1,
        step: 0.1
      })
    }
  }
}