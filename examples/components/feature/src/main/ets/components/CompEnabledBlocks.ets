import { RadioBlock } from 'common';

@Component
export struct CompEnabledBlocks {
  @Link enableCompEnabled: boolean;
  @Link compEnabled: boolean;

  build() {
    RadioBlock({
      title: 'enabled',
      isEnabled: $enableCompEnabled,
      value: $compEnabled,
      dataSource: [
        { label: 'true', value: true },
        { label: 'false', value: false }
      ]
    })
  }
}