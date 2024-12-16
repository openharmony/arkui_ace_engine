import { RadioBlock } from 'common';


@Component
export struct CompHitTestControlBlocks {
  @Link enableCompHitTestBehavior: boolean;
  @Link compHitTestBehavior: HitTestMode;

  build() {
    Column() {
      RadioBlock({
        title: 'hitTestBehavior',
        isEnabled: $enableCompHitTestBehavior,
        value: $compHitTestBehavior,
        dataSource: [
          { label: 'Default', value: HitTestMode.Default },
          { label: 'Block', value: HitTestMode.Block },
          { label: 'Transparent', value: HitTestMode.Transparent },
          { label: 'None', value: HitTestMode.None }
        ]
      })
    }
  }
}