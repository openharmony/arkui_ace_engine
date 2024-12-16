import { RadioBlock, SliderBlock } from 'common';


@Component
export struct CompTouchTargetBlocks {
  @Link enableCompResponseRegionValueX: boolean;
  @Link compResponseRegionValueX: number;
  @Link enableCompResponseRegionValueY: boolean;
  @Link compResponseRegionValueY: number;
  @Link enableCompResponseRegionValueWidth: boolean;
  @Link compResponseRegionValueWidth: Length;
  @Link enableCompResponseRegionValueHeight: boolean;
  @Link compResponseRegionValueHeight: Length;

  build() {
    Column() {
      SliderBlock({
        title: 'responseRegion.value.x',
        isEnabled: $enableCompResponseRegionValueX,
        value: $compResponseRegionValueX,
        min: -200,
        max: 200
      })
      SliderBlock({
        title: 'responseRegion.value.y',
        isEnabled: $enableCompResponseRegionValueY,
        value: $compResponseRegionValueY,
        min: -200,
        max: 200
      })
      RadioBlock({
        title: 'responseRegion.value.width',
        isEnabled: $enableCompResponseRegionValueWidth,
        value: $compResponseRegionValueWidth,
        dataSource: [
          { label: '0%', value: '0%' },
          { label: '30%', value: '30%' },
          { label: '60%', value: '60%' },
          { label: '90%', value: '90%' },
          { label: '100%', value: '100%' },
        ]
      })
      RadioBlock({
        title: 'responseRegion.value.height',
        isEnabled: $enableCompResponseRegionValueHeight,
        value: $compResponseRegionValueHeight,
        dataSource: [
          { label: '0%', value: '0%' },
          { label: '30%', value: '30%' },
          { label: '60%', value: '60%' },
          { label: '90%', value: '90%' },
          { label: '100%', value: '100%' },
        ]
      })
    }
  }
}