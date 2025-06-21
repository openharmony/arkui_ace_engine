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
  EmbeddedComponent,
  EmbeddedComponentAttribute,
  EmbeddedType,
  TerminationInfo,
  NavDestination,
  NavPathStack,
  NavDestinationContext,
  Callback
} from '@ohos.arkui.component'  // TextAttribute should be insert by ui-plugins

import hilog from '@ohos.hilog'

@Component
export struct EmbeddedComponentTest {

  build() {
    NavDestination() {
      Column(undefined) {
        Text('embeddedComponent功能测试').fontSize(20)
        EmbeddedComponent({
          bundleName: 'com.example.myapplication',
          abilityName: 'ApplicationEmbeddedUIExtAbility',
        }, EmbeddedType.EMBEDDED_UI_EXTENSION)
          .width(300)
          .height(300)
      }
    }
    .title('embeddedComponent功能测试')
  }
}

@Component
struct Child {
  @State stateVar: string = 'Child';
  build() {
    Text(this.stateVar).fontSize(50)
  }
}