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
  NavDestination, 
  NavPathStack, 
  NavDestinationContext, 
  Callback
} from '@ohos.arkui.component' // TextAttribute should be insert by ui-plugins

import hilog from '@ohos.hilog'

@Component
export struct ButtonTest {
  @State stateVar: string = 'state var';
  message: string = 'var';

  changeValue() {
    this.stateVar += '~'
  }

  build() {
    NavDestination() {
      Column(undefined) {
      Text('Hello World').fontSize(20)
      Button('OK',
        {
          type: ButtonType.Normal,
          stateEffect: false,
        } as ButtonOptions).fontColor(Color.Pink).fontWeight(600).fontSize(30)
      Button(this.message)
        .backgroundColor('#FFFF00FF')
        .type(ButtonType.Circle)
        .stateEffect(false)
        .role(ButtonRole.ERROR)
        .onClick((e: ClickEvent) => {
          hilog.info(0x0000, 'testTag', 'On Click');
          this.changeValue()
        })
      Text(this.stateVar).fontSize(20)
      Child({ stateVar: this.stateVar } as __Options_Child)
    }
    }
    .title('Button基础功能测试')
  }
}

@Component
struct Child {
  @State stateVar: string = 'Child';

  build() {
    Text(this.stateVar).fontSize(50)
  }
}