import { RadioBlock } from 'common';

;

@Component
export struct CompComponentIDBlocks {
  @Link enableCompId: boolean;
  @Link compId: string;
  @Link enableCompKey: boolean;
  @Link compKey: string;

  build() {
    Column() {
      RadioBlock({
        title: 'id',
        isEnabled: $enableCompId,
        value: $compId,
        dataSource: [
          { label: '1', value: '1' },
          { label: '2', value: '2' },
        ]
      })

      RadioBlock({
        title: 'key',
        isEnabled: $enableCompKey,
        value: $compKey,
        dataSource: [
          { label: '1', value: '1' },
          { label: '2', value: '2' },
        ]
      })
    }
    .width('100%')
  }
}