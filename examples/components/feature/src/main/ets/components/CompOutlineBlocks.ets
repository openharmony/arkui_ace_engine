import { ColorBlock, RadioBlock, SliderBlock } from 'common';


@Component
export struct CompOutlineBlocks {
  @Link enableCompOutlineValueWidth: boolean;
  @Link compOutlineValueWidth: number;
  @Link enableCompOutlineValueColor: boolean;
  @Link compOutlineValueColor: ResourceColor;
  @Link enableCompOutlineValueRadius: boolean;
  @Link compOutlineValueRadius: number;
  @Link enableCompOutlineValueStyle: boolean;
  @Link compOutlineValueStyle: OutlineStyle;

  build() {
    Column() {
      SliderBlock({
        title: 'outline.value.width',
        isEnabled: $enableCompOutlineValueWidth,
        value: $compOutlineValueWidth,
        min: 0,
        max: 32
      })
      if (this.enableCompOutlineValueWidth) {
        ColorBlock({
          title: 'outline.value.color',
          isEnabled: $enableCompOutlineValueColor,
          color: $compOutlineValueColor
        })
        SliderBlock({
          title: 'outline.value.radius',
          isEnabled: $enableCompOutlineValueRadius,
          value: $compOutlineValueRadius,
          min: 0,
          max: 32
        })
        RadioBlock({
          title: 'outline.value.style',
          isEnabled: $enableCompOutlineValueStyle,
          value: $compOutlineValueStyle,
          dataSource: [
            { label: 'SOLID', value: OutlineStyle.SOLID },
            { label: 'DASHED', value: OutlineStyle.DASHED },
            { label: 'DOTTED', value: OutlineStyle.DOTTED },
          ]
        })
      }
    }
  }
}