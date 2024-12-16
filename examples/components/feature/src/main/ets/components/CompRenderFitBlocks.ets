import { RadioBlock } from 'common';


@Component
export struct CompRenderFitBlocks {
  @Link enableCompRenderFit: boolean;
  @Link compRenderFit: RenderFit;

  build() {
    Column() {
      RadioBlock({
        title: 'renderFit',
        isEnabled: $enableCompRenderFit,
        value: $compRenderFit,
        dataSource: [
          { label: 'CENTER', value: RenderFit.CENTER },
          { label: 'TOP', value: RenderFit.TOP },
          { label: 'BOTTOM', value: RenderFit.BOTTOM },
          { label: 'LEFT', value: RenderFit.LEFT },
          { label: 'RIGHT', value: RenderFit.RIGHT },
          { label: 'TOP_LEFT', value: RenderFit.TOP_LEFT },
          { label: 'TOP_RIGHT', value: RenderFit.TOP_RIGHT },
          { label: 'BOTTOM_LEFT', value: RenderFit.BOTTOM_LEFT },
          { label: 'BOTTOM_RIGHT', value: RenderFit.BOTTOM_RIGHT },
          { label: 'RESIZE_FILL', value: RenderFit.RESIZE_FILL },
          { label: 'RESIZE_CONTAIN', value: RenderFit.RESIZE_CONTAIN },
          { label: 'RESIZE_CONTAIN_TOP_LEFT', value: RenderFit.RESIZE_CONTAIN_TOP_LEFT },
          { label: 'RESIZE_CONTAIN_BOTTOM_RIGHT', value: RenderFit.RESIZE_CONTAIN_BOTTOM_RIGHT },
          { label: 'RESIZE_COVER', value: RenderFit.RESIZE_COVER },
          { label: 'RESIZE_COVER_TOP_LEFT', value: RenderFit.RESIZE_COVER_TOP_LEFT },
          { label: 'RESIZE_COVER_BOTTOM_RIGHT', value: RenderFit.RESIZE_COVER_BOTTOM_RIGHT },
        ]
      })
    }
  }
}