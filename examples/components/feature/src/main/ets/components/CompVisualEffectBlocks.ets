import { RadioBlock } from 'common';


@Component
export struct CompVisualEffectBlocks {
  @Link enableCompVisualEffect: boolean;
  @Link compVisualEffect: boolean;
  @Link enableCompBackgroundFilter: boolean;
  @Link compBackgroundFilter: boolean;
  @Link enableCompForegroundFilter: boolean;
  @Link compForegroundFilter: boolean;
  @Link enableCompCompositingFilter: boolean;
  @Link compCompositingFilter: boolean;

  build() {
    Column() {
      RadioBlock({
        title: 'visualEffect',
        isEnabled: $enableCompVisualEffect,
        value: $compVisualEffect,
        dataSource: [
          { label: 'true', value: true },
          { label: 'false', value: false },
        ]
      })
      RadioBlock({
        title: 'backgroundFilter',
        isEnabled: $enableCompBackgroundFilter,
        value: $compBackgroundFilter,
        dataSource: [
          { label: 'true', value: true },
          { label: 'false', value: false },
        ]
      })
      RadioBlock({
        title: 'foregroundFilter',
        isEnabled: $enableCompForegroundFilter,
        value: $compForegroundFilter,
        dataSource: [
          { label: 'true', value: true },
          { label: 'false', value: false },
        ]
      })
      RadioBlock({
        title: 'compositingFilter',
        isEnabled: $enableCompCompositingFilter,
        value: $compCompositingFilter,
        dataSource: [
          { label: 'true', value: true },
          { label: 'false', value: false },
        ]
      })
    }
  }
}