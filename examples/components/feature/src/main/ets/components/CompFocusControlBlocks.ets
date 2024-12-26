import { ColorBlock, RadioBlock, SliderBlock } from 'common';

@Component
export struct CompFocusControlBlocks {
  @Link enableCompFocusable: boolean;
  @Link compFocusable: boolean;
  @Link enableCompDefaultFocus: boolean;
  @Link compDefaultFocus: boolean;
  @Link enableCompGroupDefaultFocus: boolean;
  @Link compGroupDefaultFocus: boolean;
  @Link enableCompFocusOnTouch: boolean;
  @Link compFocusOnTouch: boolean;
  @Link enableCompFocusBoxMargin: boolean;
  @Link compFocusBoxMargin: number;
  @Link enableCompFocusBoxStrokeColor: boolean;
  @Link compFocusBoxStrokeColor: ResourceColor;
  @Link enableCompFocusBoxStrokeWidth: boolean;
  @Link compFocusBoxStrokeWidth: number;
  @Link enableCompFocusScopePriorityScopeId: boolean;
  @Link compFocusScopePriorityScopeId: string;
  @Link enableCompFocusScopePriorityPriority: boolean;
  @Link compFocusScopePriorityPriority: FocusPriority;
  @Link enableCompFocusScopeId: boolean;
  @Link compFocusScopeId: string;
  @Link enableCompFocusScopeIdIsGroup: boolean;
  @Link compFocusScopeIdIsGroup: boolean;

  build() {
    Column() {

      RadioBlock({
        title: 'focusable',
        isEnabled: $enableCompFocusable,
        value: $compFocusable,
        dataSource: [
          { label: 'true', value: true },
          { label: 'false', value: false },
        ]
      })


      RadioBlock({
        title: 'defaultFocus',
        isEnabled: $enableCompDefaultFocus,
        value: $compDefaultFocus,
        dataSource: [
          { label: 'true', value: true },
          { label: 'false', value: false },
        ]
      })

      RadioBlock({
        title: 'groupDefaultFocus',
        isEnabled: $enableCompGroupDefaultFocus,
        value: $compGroupDefaultFocus,
        dataSource: [
          { label: 'true', value: true },
          { label: 'false', value: false },
        ]
      })

      RadioBlock({
        title: 'focusOnTouch',
        isEnabled: $enableCompFocusOnTouch,
        value: $compFocusOnTouch,
        dataSource: [
          { label: 'true', value: true },
          { label: 'false', value: false },
        ]
      })

      SliderBlock({
        title: 'focusBox.margin',
        isEnabled: $enableCompFocusBoxMargin,
        value: $compFocusBoxMargin,
        min: 0,
        max: 100
      })

      ColorBlock({
        title: 'focusBox.strokeColor',
        isEnabled: $enableCompFocusBoxStrokeColor,
        color: $compFocusBoxStrokeColor,
      })

      SliderBlock({
        title: 'focusBox.strokeWidth',
        isEnabled: $enableCompFocusBoxStrokeWidth,
        value: $compFocusBoxStrokeWidth,
        min: 0,
        max: 100
      })
    }
    .width('100%')
  }
}