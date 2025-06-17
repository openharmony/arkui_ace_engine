import {
  Text,
  Column,
  Component,
  Entry,
  Button,
  ClickEvent ,
  NavDestination,
  NavPathStack,
  NavDestinationContext,
  Callback
} from '@ohos.arkui.component'

import {
  State,
  Link,
  Prop,
  StorageLink,
  StorageProp,
  AppStorage,
  LocalStorage
} from '@ohos.arkui.stateManagement'

import hilog from '@ohos.hilog'

@Entry
@Component
export struct StateLinkPropTest {
  @State stateVar: string = 'state var';
  message: string = `click to change state variable, add **`;
  changeValue() {
    this.stateVar+='**'
  }

  build() {
    NavDestination() {
      Column(undefined) {
        Button('clean variable').onClick((e: ClickEvent) => {
          this.stateVar = 'state var'
        })
        Text('Hello World').fontSize(20)
        Button(this.message).backgroundColor('#FFFF00FF')
          .onClick((e: ClickEvent) => {
            hilog.info(0x0000, 'testTag', 'On Click');
            this.changeValue()
          })
        Text(this.stateVar).fontSize(20)
        Child({ linkVar: this.stateVar, propVar: this.stateVar })
      }.margin(10)
    }
    .title('State/Prop/Link支持基础功能测试')
  }
}

@Component
struct Child {
  @Link linkVar: string = '';
  @Prop propVar: string = 'Prop';

  changeValue1() {
    this.linkVar+='!!'
  }

  changeValue2() {
    this.propVar+='~~'
  }

  build() {
    Column(undefined) {
      Button(`click to change Link variable, add symbol !!`)
        .backgroundColor('#4169E1')
        .onClick((e: ClickEvent) => {
          hilog.info(0x0000, 'testTag', 'On Click');
          this.changeValue1()
        })
      Button(`click to change Prop variable, add symbol ~~`)
        .backgroundColor('#3CB371')
        .onClick((e: ClickEvent) => {
          hilog.info(0x0000, 'testTag', 'On Click');
          this.changeValue2()
        })
      Text(`Link variable in child: ${this.linkVar}`).fontSize(30)
      Text(`Prop variable in child: ${this.propVar}`).fontSize(30)
    }
  }
}
