import { ColorBlock, RadioBlock, SliderBlock } from 'common';

@Component
export struct CompGradientColorBlocks {
  @Link enableCompLinearGradientAngle: boolean;
  @Link compLinearGradientAngle: number;
  @Link enableCompLinearGradientDirection: boolean;
  @Link compLinearGradientDirection: GradientDirection;
  @Link enableCompLinearGradientColors1: boolean;
  @Link compLinearGradientColors1: ResourceStr;
  @Link enableCompLinearGradientColorsNumber1: boolean;
  @Link compLinearGradientColorsNumber1: number;
  @Link enableCompLinearGradientColors2: boolean;
  @Link compLinearGradientColors2: ResourceStr;
  @Link enableCompLinearGradientColorsNumber2: boolean;
  @Link compLinearGradientColorsNumber2: number;
  @Link enableCompLinearGradientRepeating: boolean;
  @Link compLinearGradientRepeating: boolean;

  build() {
    Column() {

      SliderBlock({
        title: 'linearGradient.angle',
        isEnabled: $enableCompLinearGradientAngle,
        value: $compLinearGradientAngle,
        min: 0,
        max: 360,
      })

      RadioBlock({
        title: 'linearGradient.direction',
        isEnabled: $enableCompLinearGradientDirection,
        value: $compLinearGradientDirection,
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

      ColorBlock({
        title: 'linearGradient.color1',
        isEnabled: $enableCompLinearGradientColors1,
        color: $compLinearGradientColors1
      })

      SliderBlock({
        title: 'linearGradient.number1',
        isEnabled: $enableCompLinearGradientColorsNumber1,
        value: $compLinearGradientColorsNumber1,
        step: 0.1,
        min: 0,
        max: 1,
      })

      ColorBlock({
        title: 'linearGradient.color2',
        isEnabled: $enableCompLinearGradientColors2,
        color: $compLinearGradientColors2
      })

      SliderBlock({
        title: 'linearGradient.number2',
        isEnabled: $enableCompLinearGradientColorsNumber2,
        value: $compLinearGradientColorsNumber2,
        step: 0.1,
        min: 0,
        max: 1,
      })

      RadioBlock({
        title: 'linearGradient.repeating',
        isEnabled: $enableCompLinearGradientRepeating,
        value: $compLinearGradientRepeating,
        dataSource: [
          { label: 'true', value: true },
          { label: 'false', value: false }
        ]
      })


    }
    .width('100%')

  }
}