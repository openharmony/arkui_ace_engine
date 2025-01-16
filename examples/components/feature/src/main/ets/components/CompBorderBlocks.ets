import { RadioBlock, ColorBlock, SliderBlock } from 'common';

@Component
export struct CompBorderBlocks {
  @Link enableCompBorderWidth: boolean;
  @Link compBorderWidth: Length;
  @Link enableCompBorderColor: boolean;
  @Link compBorderColor: ResourceColor;
  @Link enableCompBorderRadius: boolean;
  @Link compBorderRadius: Length;
  @Link enableCompBorderStyle: boolean;
  @Link compBorderStyle: BorderStyle;
  @Link enableCompBorderDashGapLeft: boolean;
  @Link compBorderDashGapLeft: number;
  @Link enableCompBorderDashGapRight: boolean;
  @Link compBorderDashGapRight: number;
  @Link enableCompBorderDashGapTop: boolean;
  @Link compBorderDashGapTop: number;
  @Link enableCompBorderDashGapBottom: boolean;
  @Link compBorderDashGapBottom: number;
  @Link enableCompBorderDashWidthLeft: boolean;
  @Link compBorderDashWidthLeft: number;
  @Link enableCompBorderDashWidthRight: boolean;
  @Link compBorderDashWidthRight: number;
  @Link enableCompBorderDashWidthTop: boolean;
  @Link compBorderDashWidthTop: number;
  @Link enableCompBorderDashWidthBottom: boolean;
  @Link compBorderDashWidthBottom: number;

  build() {
    Column() {
      RadioBlock({
        title: 'borderStyle',
        isEnabled: $enableCompBorderStyle,
        value: $compBorderStyle,
        dataSource: [
          { label: 'Dotted', value: BorderStyle.Dotted },
          { label: 'Dashed', value: BorderStyle.Dashed },
          { label: 'Solid', value: BorderStyle.Solid }
        ]
      })

      SliderBlock({
        title: 'borderWidth',
        isEnabled: $enableCompBorderWidth,
        value: $compBorderWidth,
        min: 0,
        max: 20
      })

      ColorBlock({
        title: 'borderColor',
        isEnabled: $enableCompBorderColor,
        color: $compBorderColor
      })

      SliderBlock({
        title: 'borderRadius',
        isEnabled: $enableCompBorderRadius,
        value: $compBorderRadius,
        min: 0,
        max: 300
      })

      if (this.compBorderStyle === BorderStyle.Dashed) {
        SliderBlock({
          title: 'border.dashGap.left',
          isEnabled: $enableCompBorderDashGapLeft,
          value: $compBorderDashGapLeft,
          min: 0,
          max: 300
        })

        SliderBlock({
          title: 'border.dashGap.right',
          isEnabled: $enableCompBorderDashGapRight,
          value: $compBorderDashGapRight,
          min: 0,
          max: 300
        })

        SliderBlock({
          title: 'border.dashGap.top',
          isEnabled: $enableCompBorderDashGapTop,
          value: $compBorderDashGapTop,
          min: 0,
          max: 300
        })

        SliderBlock({
          title: 'border.dashGap.bottom',
          isEnabled: $enableCompBorderDashGapBottom,
          value: $compBorderDashGapBottom,
          min: 0,
          max: 300
        })

        SliderBlock({
          title: 'border.dashWidth.left',
          isEnabled: $enableCompBorderDashWidthLeft,
          value: $compBorderDashWidthLeft,
          min: 0,
          max: 300
        })

        SliderBlock({
          title: 'border.dashWidth.right',
          isEnabled: $enableCompBorderDashWidthRight,
          value: $compBorderDashWidthRight,
          min: 0,
          max: 300
        })

        SliderBlock({
          title: 'border.dashWidth.top',
          isEnabled: $enableCompBorderDashWidthTop,
          value: $compBorderDashWidthTop,
          min: 0,
          max: 300
        })

        SliderBlock({
          title: 'border.dashWidth.bottom',
          isEnabled: $enableCompBorderDashWidthBottom,
          value: $compBorderDashWidthBottom,
          min: 0,
          max: 300
        })
      }
    }
  }
}