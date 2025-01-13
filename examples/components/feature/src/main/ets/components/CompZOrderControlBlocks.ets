import { SliderBlock } from 'common';

@Component
export struct CompZOrderControlBlocks {
  @Link enableCompZIndex: boolean;
  @Link compZIndex: number;

  build() {
    SliderBlock({
      title: 'zIndex',
      isEnabled: $enableCompZIndex,
      value: $compZIndex,
      min: -100,
      max: 100
    })
  }
}