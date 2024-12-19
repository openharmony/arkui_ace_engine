import { RadioBlock, SliderBlock } from 'common';

@Component
export struct CompOverlayBlocks {
  @Link enableCompOverlay: boolean;
  @Link compOverlay: string;
  @Link enableCompOverlayOptions: boolean;
  @Link enableCompOverlayOptionsAlign: boolean;
  @Link compOverlayOptionsAlign: Alignment;
  @Link enableCompOverlayOptionsOffsetX: boolean;
  @Link compOverlayOptionsOffsetX: number;
  @Link enableCompOverlayOptionsOffsetY: boolean;
  @Link compOverlayOptionsOffsetY: number;

  build() {
    Column() {
      RadioBlock({
        title: 'overlay',
        isEnabled: $enableCompOverlay,
        value: $enableCompOverlay,
        dataSource: [
          { label: 'true', value: true },
          { label: 'false', value: false }
        ]

      })
      if (this.enableCompOverlay) {
        RadioBlock({
          title: 'overlay.options',
          isEnabled: $enableCompOverlayOptions,
          value: $enableCompOverlayOptions,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })

        if (this.enableCompOverlayOptions) {
          RadioBlock({
            title: 'overlay.options.align',
            isEnabled: $enableCompOverlayOptionsAlign,
            value: $compOverlayOptionsAlign,
            dataSource: [
              { label: 'TopStart', value: Alignment.TopStart },
              { label: 'Top', value: Alignment.Top },
              { label: 'TopEnd', value: Alignment.TopEnd },
              { label: 'Start', value: Alignment.Start },
              { label: 'Center', value: Alignment.Center },
              { label: 'End', value: Alignment.End },
              { label: 'BottomStart', value: Alignment.BottomStart },
              { label: 'Bottom', value: Alignment.Bottom },
              { label: 'BottomEnd', value: Alignment.BottomEnd },
            ]
          })

          SliderBlock({
            title: 'overlay.options.offset.x',
            isEnabled: $enableCompOverlayOptionsOffsetX,
            value: $compOverlayOptionsOffsetX,
            min: 0,
            max: 100
          })

          SliderBlock({
            title: 'overlay.options.offset.y',
            isEnabled: $enableCompOverlayOptionsOffsetY,
            value: $compOverlayOptionsOffsetY,
            min: 0,
            max: 100
          })
        }
      }
    }
  }
}