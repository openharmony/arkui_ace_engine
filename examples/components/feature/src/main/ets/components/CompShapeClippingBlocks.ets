import { RadioBlock, ColorBlock, SliderBlock } from 'common';

@Component
export struct CompShapeClippingBlocks {
  @Link enableCompClip: boolean;
  @Link compClip: boolean;
  @Link enableCompClipShape: boolean;
  @Link enableCompClipShapeWidth: boolean;
  @Link compClipShapeWidth: number;
  @Link enableCompClipShapeHeight: boolean;
  @Link compClipShapeHeight: number;
  @Link enableCompMask: boolean;
  @Link enableCompMaskValue: boolean;
  @Link compMaskValue: number;
  @Link enableCompMaskColor: boolean;
  @Link compMaskColor: number;
  @Link enableCompMaskShape: boolean;
  @Link enableCompMaskShapeWidth: boolean;
  @Link compMaskShapeWidth: number;
  @Link enableCompMaskShapeHeight: boolean;
  @Link compMaskShapeHeight: number;

  build() {
    Column() {
      RadioBlock({
        title: 'clip',
        isEnabled: $enableCompClip,
        value: $compClip,
        dataSource: [
          { label: 'true', value: true },
          { label: 'false', value: false }
        ]
      })

      RadioBlock({
        title: 'clipShape',
        isEnabled: $enableCompClipShape,
        value: $enableCompClipShape,
        dataSource: [
          { label: 'true', value: true },
          { label: 'false', value: false }
        ]
      })

      if (this.enableCompClipShape) {
        SliderBlock({
          title: 'clipShape.width',
          isEnabled: $enableCompClipShapeWidth,
          value: $compClipShapeWidth,
          min: 0,
          max: 100
        })

        SliderBlock({
          title: 'clipShape.height',
          isEnabled: $enableCompClipShapeHeight,
          value: $compClipShapeHeight,
          min: 0,
          max: 100
        })
      }

      RadioBlock({
        title: 'mask',
        isEnabled: $enableCompMask,
        value: $enableCompMask,
        dataSource: [
          { label: 'true', value: true },
          { label: 'false', value: false }
        ]
      })

      if (this.enableCompMask) {

        SliderBlock({
          title: 'mask.value',
          isEnabled: $enableCompMaskValue,
          value: $compMaskValue,
          min: 0,
          max: 100
        })

        ColorBlock({
          title: 'mask.color',
          isEnabled: $enableCompMaskColor,
          color: $compMaskColor
        })
      }

      RadioBlock({
        title: 'maskShape',
        isEnabled: $enableCompMaskShape,
        value: $enableCompMaskShape,
        dataSource: [
          { label: 'true', value: true },
          { label: 'false', value: false }
        ]
      })

      if (this.enableCompMaskShape) {
        SliderBlock({
          title: 'maskShape.width',
          isEnabled: $enableCompMaskShapeWidth,
          value: $compMaskShapeWidth,
          min: 0,
          max: 100
        })

        SliderBlock({
          title: 'maskShape.height',
          isEnabled: $enableCompMaskShapeHeight,
          value: $compMaskShapeHeight,
          min: 0,
          max: 100
        })
      }
    }
  }
}