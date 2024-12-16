import { RadioBlock } from 'common';

@Component
export struct CompAccessibilityBlocks {
  @Link enableCompAccessibilityGroup: boolean;
  @Link compAccessibilityGroup: boolean;
  @Link enableCompAccessibilityText: boolean;
  @Link compAccessibilityText: string;
  @Link enableCompAccessibilityDescription: boolean;
  @Link compAccessibilityDescription: string;
  @Link enableCompAccessibilityLevel: boolean;
  @Link compAccessibilityLevel: string;

  build() {
    Column() {
      RadioBlock({
        title: 'accessibilityGroup',
        isEnabled: $enableCompAccessibilityGroup,
        value: $compAccessibilityGroup,
        dataSource: [
          { label: 'true', value: true },
          { label: 'false', value: false },
        ]
      })

      RadioBlock({
        title: 'accessibilityText',
        isEnabled: $enableCompAccessibilityText,
        value: $compAccessibilityText,
        dataSource: [
          { label: '无障碍文本', value: '无障碍文本' },
          { label: '组件被选中时，仅播报无障碍文本内容', value: '组件被选中时，仅播报无障碍文本内容' },
        ]
      })

      RadioBlock({
        title: 'accessibilityDescription',
        isEnabled: $enableCompAccessibilityDescription,
        value: $compAccessibilityDescription,
        dataSource: [
          { label: '无障碍说明', value: '无障碍说明' },
          { label: '用于为用户进一步说明当前组件', value: '用于为用户进一步说明当前组件' },
        ]
      })

      RadioBlock({
        title: 'accessibilityLevel',
        isEnabled: $enableCompAccessibilityLevel,
        value: $compAccessibilityLevel,
        dataSource: [
          { label: 'auto', value: 'auto' },
          { label: 'yes', value: 'yes' },
          { label: 'no', value: 'no' },
          { label: 'no-hide-descendants', value: 'no-hide-descendants' },
        ]
      })
    }
    .width('100%')
  }
}
