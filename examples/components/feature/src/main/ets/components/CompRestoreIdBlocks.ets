import { RadioBlock } from 'common';

@Component
export struct CompRestoreIdBlocks {
  @Link enableCompRestoreId: boolean;
  @Link compRestoreId: number;

  build() {
    Column() {
      RadioBlock({
        title: 'restoreId',
        isEnabled: $enableCompRestoreId,
        value: $compRestoreId,
        dataSource: [
          { label: '1', value: 1 },
          { label: '2', value: 2 },
        ]
      })
    }
    .width('100%')
  }
}