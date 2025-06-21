import { memo,
  __memo_context_type,
  __memo_id_type,
  State,
  StateDecoratedVariable,
  MutableState,
  stateOf,
  observableProxy
} from '@ohos.arkui.stateManagement' // should be insert by ui-plugins

import {
  Text,
  TextAttribute,
  Column,
  Component,
  Button,
  ButtonAttribute,
  ClickEvent,
  UserView,
  BlendMode,
  SizeOptions,
  SizeChangeCallback,
  Stack,
  FocusDrawLevel,
  AccessibilitySamePageMode,
  AccessibilityFocusCallback,
  AccessibilityRoleType,
  AccessibilityCallback,
  AccessibilityHoverEvent,
  Builder,
  List,
  ForEach,
  ListItem,
  NavDestination,
  NavPathStack,
  NavDestinationContext,
  Callback
} from '@ohos.arkui.component'  // TextAttribute should be insert by ui-plugins

import hilog from '@ohos.hilog'
import { $r} from '@ohos.arkui.component';


@Component
export struct IndexAccessibilityTest {
  @State stateVar: string = 'state var';
  message: string = 'var';
  changeValue() {
    this.stateVar+='~'
  }

  build() {
    NavDestination() {
      Column(undefined) {
        Text('辅助功能已启用').fontSize(20)
          .accessibilityChecked(true)
          .accessibilityLevel('yes')
        Button('Accessibility False').backgroundColor('#FFFF00FF')
          .onClick((e: ClickEvent) => {
            hilog.info(0x0000, 'testTag', 'On Click');
          })
          .accessibilityLevel('yes')
          .accessibilityChecked(false)
        Text('辅助功能已选择').fontSize(20)
          .accessibilitySelected(true)
          .accessibilityLevel('yes')
        Button('辅助功能未选中').backgroundColor('#FFFF00FF')
          .onClick((e: ClickEvent) => {
            hilog.info(0x0000, 'testTag', 'On Click');
          })
          .accessibilityLevel('yes')
          .accessibilitySelected(false)
        Text('test1 nexfFocus suppose to be test3').fontSize(20)
          .accessibilityLevel('yes')
          .id('test1')
          .accessibilityNextFocusId('test3')
        Button('test2').backgroundColor('#FFFF00FF')
          .onClick((e: ClickEvent) => {
            hilog.info(0x0000, 'testTag', 'On Click');
            this.changeValue()
          })
          .id('test2')
        Text('test3').fontSize(20)
          .accessibilityLevel('yes')
          .id('test3')
          .accessibilityNextFocusId('test2')
      }
    }
    .title('NodeContainerTest')
  }
}

@Component
struct Child {
  @State stateVar: string = 'Child';
  build() {
    Text(this.stateVar).fontSize(50)
  }
}
