import {
  memo,
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
  ButtonType,
  ButtonStyleMode,
  ButtonOptions,
  ButtonRole,
  Color,
  Toggle,
  ToggleAttribute,
  ToggleType,
  Checkbox,
  CheckboxAttribute,
  CheckBoxShape,
  OnCheckboxChangeCallback,
  OnCheckboxGroupChangeCallback,
  CheckboxGroup,
  CheckboxGroupAttribute,
  CheckboxGroupResult,
  MarkStyle,
  NavDestination, 
  NavPathStack,
  NavDestinationContext,
  Callback
} from '@ohos.arkui.component' // TextAttribute should be insert by ui-plugins

import hilog from '@ohos.hilog'

@Component
export struct CheckboxGroupTest {
  @State stateVar: string = 'state var';
  message: string = 'var';

  changeValue() {
    this.stateVar += '~'
  }
  build() {
    NavDestination() {
      Column(undefined) {
        Text('Hello World').fontSize(20)
        CheckboxGroup({ group: 'checkboxGroup' })
          .checkboxShape(CheckBoxShape.ROUNDED_SQUARE)
          .selectedColor('#007DFF')
          .unselectedColor('#007DFF')
          .mark({
            strokeColor: Color.Black,
            size: 50,
            strokeWidth: 5
          } as MarkStyle)
          .onChange((value: CheckboxGroupResult) => {
            hilog.info(0x0000, 'testTag', 'checkbox group content' + JSON.stringify(value));
          } as OnCheckboxGroupChangeCallback)

        Checkbox({ name: 'checkbox1', group: 'checkboxGroup' })
          .select(true)
          .selectedColor(0xed6f21)
          .unselectedColor(Color.Pink)
          .shape(CheckBoxShape.CIRCLE)
          .onChange((value: boolean) => {
            hilog.info(0x0000, 'testTag', 'yc--------------' + value);
          } as OnCheckboxChangeCallback)

        Checkbox({ name: 'checkbox2', group: 'checkboxGroup' })
          .select(true)
          .selectedColor(0xed6f21)
          .shape(CheckBoxShape.CIRCLE)
          .mark({
            strokeColor: Color.Black,
            size: 50,
            strokeWidth: 5
          } as MarkStyle)
          .onChange((value: boolean) => {
            hilog.info(0x0000, 'testTag', 'yc--------------' + value);
          } as OnCheckboxChangeCallback)
        Text(this.stateVar).fontSize(20)
        Child({ stateVar: this.stateVar } as __Options_Child)
      }
    }
    .title('CheckboxGroup基础功能测试')
  }
}

@Component
struct Child {
  @State stateVar: string = 'Child';

  build() {
    Text(this.stateVar).fontSize(50)
  }
}