import { RadioBlock } from 'common';

@Component
export struct CompVisibilityBlocks {
  @Link enableCompVisibility: boolean;
  @Link compVisibility: Visibility;

  build() {
    RadioBlock({
      title: 'visibility',
      isEnabled: $enableCompVisibility,
      value: $compVisibility,
      dataSource: [
        { label: 'Visible', value: Visibility.Visible },
        { label: 'Hidden', value: Visibility.Hidden },
        { label: 'None', value: Visibility.None }
      ]
    })
  }
}