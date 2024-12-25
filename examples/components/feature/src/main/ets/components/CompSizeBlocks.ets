import { RadioBlock, SliderBlock } from 'common';

@Component
export struct CompSizeBlocks {
  @Link enableCompWidth: boolean;
  @Link compWidth: Length;
  @Link enableCompHeight: boolean;
  @Link compHeight: Length;
  @Link enableCompPadding: boolean;
  @Link compPadding: Padding | Length | LocalizedPadding;
  @Link enableCompMargin: boolean;
  @Link compMargin: Margin | Length | LocalizedPadding;
  @Link enableCompConstraintSize: boolean;
  @Link enableCompConstraintSizeMinWidth: boolean;
  @Link compConstraintSizeMinWidth: Length;
  @Link enableCompConstraintSizeMinHeight: boolean;
  @Link compConstraintSizeMinHeight: Length;
  @Link enableCompConstraintSizeMaxWidth: boolean;
  @Link compConstraintSizeMaxWidth: Length;
  @Link enableCompConstraintSizeMaxHeight: boolean;
  @Link compConstraintSizeMaxHeight: Length;

  build() {
    Column() {

      SliderBlock({
        title: 'width',
        isEnabled: $enableCompWidth,
        value: $compWidth,
        min: 100,
        max: 500
      })

      SliderBlock({
        title: 'height',
        isEnabled: $enableCompHeight,
        value: $compHeight,
        min: 100,
        max: 500
      })

      SliderBlock({
        title: 'padding',
        isEnabled: $enableCompPadding,
        value: $compPadding,
        min: 0,
        max: 100
      })

      SliderBlock({
        title: 'margin',
        isEnabled: $enableCompMargin,
        value: $compMargin,
        min: 0,
        max: 100
      })

      RadioBlock({
        title: 'constraintSize',
        isEnabled: $enableCompConstraintSize,
        value: $enableCompConstraintSize,
        dataSource: [
          { label: 'true', value: true },
          { label: 'false', value: false }
        ]
      })

      if (this.enableCompConstraintSize) {

        SliderBlock({
          title: 'constraintSize.minWidth',
          isEnabled: $enableCompConstraintSizeMinWidth,
          value: $compConstraintSizeMinWidth,
          min: 100,
          max: 500
        })

        SliderBlock({
          title: 'constraintSize.minHeight',
          isEnabled: $enableCompConstraintSizeMinHeight,
          value: $compConstraintSizeMinHeight,
          min: 100,
          max: 500
        })

        SliderBlock({
          title: 'constraintSize.maxWidth',
          isEnabled: $enableCompConstraintSizeMaxWidth,
          value: $compConstraintSizeMaxWidth,
          min: 100,
          max: 500
        })

        SliderBlock({
          title: 'constraintSize.maxHeight',
          isEnabled: $enableCompConstraintSizeMaxHeight,
          value: $compConstraintSizeMaxHeight,
          min: 100,
          max: 500
        })
      }
    }
  }
}