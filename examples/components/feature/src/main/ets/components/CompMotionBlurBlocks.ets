import { SliderBlock } from 'common';

@Component
export struct CompMotionBlurBlocks {
  @Link enableCompMotionBlurRadius: boolean;
  @Link compMotionBlurRadius: number;
  @Link enableCompMotionBlurAnchorX: boolean;
  @Link compMotionBlurAnchorX: number;
  @Link enableCompMotionBlurAnchorY: boolean;
  @Link compMotionBlurAnchorY: number;

  build() {
    Column() {
      SliderBlock({
        title: 'motionBlur.radius',
        isEnabled: $enableCompMotionBlurRadius,
        value: $compMotionBlurRadius,
        min: 0,
        max: 100
      })

      SliderBlock({
        title: 'motionBlur.anchorX',
        isEnabled: $enableCompMotionBlurAnchorX,
        value: $compMotionBlurAnchorX,
        min: 0,
        max: 100
      })

      SliderBlock({
        title: 'motionBlur.anchorY',
        isEnabled: $enableCompMotionBlurAnchorY,
        value: $compMotionBlurAnchorY,
        min: 0,
        max: 100
      })

    }
    .width('100%')
  }
}