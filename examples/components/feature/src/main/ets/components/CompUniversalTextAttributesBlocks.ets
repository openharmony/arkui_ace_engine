import { ColorBlock, RadioBlock, SliderBlock } from 'common';


@Component
export struct CompUniversalTextAttributesBlocks {
  @Link enableCompFontColor: boolean;
  @Link compFontColor: ResourceColor | undefined;
  @Link enableCompFontSize: boolean;
  @Link compFontSize: number;
  @Link enableCompFontStyle: boolean;
  @Link compFontStyle: FontStyle;
  @Link enableCompFontWeight: boolean;
  @Link compFontWeight: FontWeight;
  @Link enableCompLineHeight: boolean;
  @Link compLineHeight: number;
  @Link enableCompDecorationType: boolean;
  @Link compDecorationType: TextDecorationType;
  @Link enableCompDecorationColor: boolean;
  @Link compDecorationColor: ResourceColor;
  @Link enableCompDecorationStyle: boolean;
  @Link compDecorationStyle: TextDecorationStyle;

  build() {
    Column() {
      ColorBlock({
        title: 'fontColor',
        isEnabled: this.enableCompFontColor,
        color: this.compFontColor
      })

      SliderBlock({
        title: 'fontSize',
        isEnabled: this.enableCompFontSize,
        value: this.compFontSize,
        min: 0,
        max: 32
      })

      RadioBlock({
        title: 'fontStyle',
        isEnabled: this.enableCompFontStyle,
        value: this.compFontStyle,
        dataSource: [
          { label: 'Normal', value: FontStyle.Normal },
          { label: 'Italic', value: FontStyle.Italic },
        ]
      })

      RadioBlock({
        title: 'fontWeight',
        isEnabled: this.enableCompFontWeight,
        value: this.compFontWeight,
        dataSource: [
          { label: 'Lighter', value: FontWeight.Lighter },
          { label: 'Normal', value: FontWeight.Normal },
          { label: 'Regular', value: FontWeight.Regular },
          { label: 'Medium', value: FontWeight.Medium },
          { label: 'Bold', value: FontWeight.Bold },
          { label: 'Bolder', value: FontWeight.Bolder }
        ]
      })

      SliderBlock({
        title: 'lineHeight',
        isEnabled: this.enableCompLineHeight,
        value: this.compLineHeight,
        min: 0,
        max: 32
      })

      RadioBlock({
        title: 'decoration.value.type',
        isEnabled: this.enableCompDecorationType,
        value: this.compDecorationType,
        dataSource: [
          { label: 'None', value: TextDecorationType.None },
          { label: 'Underline', value: TextDecorationType.Underline },
          { label: 'Overline', value: TextDecorationType.Overline },
          { label: 'LineThrough', value: TextDecorationType.LineThrough },
        ]
      })

      ColorBlock({
        title: 'decoration.value.color',
        isEnabled: this.enableCompDecorationColor,
        color: this.compDecorationColor
      })

      RadioBlock({
        title: 'decoration.value.style',
        isEnabled: this.enableCompDecorationStyle,
        value: this.compDecorationStyle,
        dataSource: [
          { label: 'SOLID', value: TextDecorationStyle.SOLID },
          { label: 'DOUBLE', value: TextDecorationStyle.DOUBLE },
          { label: 'DOTTED', value: TextDecorationStyle.DOTTED },
          { label: 'DASHED', value: TextDecorationStyle.DASHED },
          { label: 'WAVY', value: TextDecorationStyle.WAVY },
        ]
      })
    }
  }
}