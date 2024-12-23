import { RadioBlock } from 'common';

@Component
export struct CompReuseIDBlocks {
  @Link enableCompReuseId: boolean;
  @Link compReuseId: string;

  build() {
    Column() {
      RadioBlock({
        title: 'reuseId',
        isEnabled: $enableCompReuseId,
        value: $compReuseId,
        dataSource: [
          { label: '1', value: '1' },
          { label: '2', value: '2' },
        ]
      })
    }
    .width('100%')
  }
}