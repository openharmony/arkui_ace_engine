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
  NavDestination,
  NavPathStack,
  NavDestinationContext,
  Callback
} from '@ohos.arkui.component'  // TextAttribute should be insert by ui-plugins

import hilog from '@ohos.hilog'
import pluginComponentManager from '@ohos.pluginComponent'
import Want from '@ohos.app.ability.Want'
import inspector from '@ohos.arkui.inspector'

@Component
export struct InspectorTest {
  @State stateVar: string = 'state var';
  message: string = '服务提供者';

  changeValue() {
    this.stateVar+='~'
  }
  build() {
    NavDestination() {
      Column(undefined) {
        Text('Hello World').fontSize(20)
        Button(this.message).backgroundColor('#FFFF00FF')
          .onClick((e: ClickEvent) => {
            hilog.info(0x0000, 'testTag', 'On Click');
            this.changeValue()
          })
        Button('button1').backgroundColor('#FFFF00F0')
          .onClick((e: ClickEvent) => {
          
          })
          .id('button1')
        Text(this.stateVar).fontSize(20)
        Child({ stateVar: this.stateVar } as __Options_Child)
      }
    }
    .title('InspectorTest')
  }
}

@Component
struct Child {
  @State stateVar: string = 'Child';
  build() {
    Text(this.stateVar).fontSize(50)
  }
}
