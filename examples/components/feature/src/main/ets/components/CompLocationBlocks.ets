import { RadioBlock, SliderBlock } from 'common';

@Component
export struct CompLocationBlocks {
  @Link enableCompPosition: boolean;
  @Link enableCompPositionTop: boolean;
  @Link compPositionTop: Dimension;
  @Link enableCompPositionBottom: boolean;
  @Link compPositionBottom: Dimension;
  @Link enableCompPositionLeft: boolean;
  @Link compPositionLeft: Dimension;
  @Link enableCompPositionRight: boolean;
  @Link compPositionRight: Dimension;
  @Link enableCompMarkAnchor: boolean;
  @Link enableCompMarkAnchorX: boolean;
  @Link compMarkAnchorX: Length;
  @Link enableCompMarkAnchorY: boolean;
  @Link compMarkAnchorY: Length;
  @Link enableCompOffset: boolean;
  @Link enableCompOffsetX: boolean;
  @Link compOffsetX: Length;
  @Link enableCompOffsetY: boolean;
  @Link compOffsetY: Length;

  build() {
    Column() {

      RadioBlock({
        title: 'position',
        isEnabled: $enableCompPosition,
        value: $enableCompPosition,
        dataSource: [
          { label: 'true', value: true },
          { label: 'false', value: false }
        ]
      })

      if (this.enableCompPosition) {

        SliderBlock({
          title: 'position.top',
          isEnabled: $enableCompPositionTop,
          value: $compPositionTop,
          min: 0,
          max: 500
        })

        SliderBlock({
          title: 'position.bottom',
          isEnabled: $enableCompPositionBottom,
          value: $compPositionBottom,
          min: 0,
          max: 500
        })

        SliderBlock({
          title: 'position.left',
          isEnabled: $enableCompPositionLeft,
          value: $compPositionLeft,
          min: 0,
          max: 500
        })

        SliderBlock({
          title: 'position.right',
          isEnabled: $enableCompPositionRight,
          value: $compPositionRight,
          min: 0,
          max: 500
        })

      }

      RadioBlock({
        title: 'markAnchor',
        isEnabled: $enableCompMarkAnchor,
        value: $enableCompMarkAnchor,
        dataSource: [
          { label: 'true', value: true },
          { label: 'false', value: false }
        ]
      })

      if (this.enableCompMarkAnchor) {
        SliderBlock({
          title: 'markAnchor.x',
          isEnabled: $enableCompMarkAnchorX,
          value: $compMarkAnchorX,
          min: 0,
          max: 500
        })

        SliderBlock({
          title: 'markAnchor.y',
          isEnabled: $enableCompMarkAnchorY,
          value: $compMarkAnchorY,
          min: 0,
          max: 500
        })
      }

      RadioBlock({
        title: 'offset',
        isEnabled: $enableCompOffset,
        value: $enableCompOffset,
        dataSource: [
          { label: 'true', value: true },
          { label: 'false', value: false }
        ]
      })

      if (this.enableCompOffset) {
        SliderBlock({
          title: 'offset.x',
          isEnabled: $enableCompOffsetX,
          value: $compOffsetX,
          min: 0,
          max: 500
        })

        SliderBlock({
          title: 'offset.y',
          isEnabled: $enableCompOffsetY,
          value: $compOffsetY,
          min: 0,
          max: 500
        })
      }
    }
  }
}