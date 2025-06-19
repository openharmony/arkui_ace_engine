import {
  memo,
  __memo_context_type,
  __memo_id_type,
  Watch,
  Observed,
  Track,
  ObjectLink,
  State,
  Link,
  Prop,
  StorageLink,
  StorageProp,
  AppStorage,
  LocalStorage
} from '@ohos.arkui.stateManagement' // should be insert by ui-plugins

import {
  Text,
  Column,
  Component,
  Entry,
  Button,
  ClickEvent,
  NavDestination, 
  NavPathStack,
  NavDestinationContext,
  Callback
} from '@ohos.arkui.component'

import hilog from '@ohos.hilog'

@Observed
class Info {
  public id: number = 0;
  private name: string = '';

  constructor(id?: number) {
    this.id = id ?? 41;
  }
}

@Component
struct Child {
  @ObjectLink @Watch('onChange1') child: Info = new Info();
  message1: string = `change id refresh`;
  changeValue() {
    this.child.id += 5;
  }
  onChange1(propertyName: string) {
    hilog.info(0x0000, 'watchTag', `zzq onChange1 ${this.child.id}`)
  }
  build() {
    Column() {
      Text('child id: ' + this.child.id).fontSize(20)
      Button(this.message1).backgroundColor('#FFFF00FF')
        .onClick((e: ClickEvent) => {
          hilog.info(0x0000, 'testTag', 'On Click');
          this.changeValue()
        })
    }
  }
}

@Entry
@Component
export struct ObservedObjectLinkTest {
  @State info: Info = new Info();

  message1: string = `change name refresh`;
  message2: string = `change name not refresh`;
  changeValue() {
    this.info = new Info(30)
  }

  build() {
    NavDestination() {
      Column(undefined) {
      Text('id: ' + this.info.id).fontSize(20)
      Button(this.message1).backgroundColor('#FFFF00FF')
        .onClick((e: ClickEvent) => {
          hilog.info(0x0000, 'testTag', 'On Click');
          this.changeValue()
        })
      Child({child: this.info})
    }.margin(10)
    }
    .title('@Observed/@ObjectLink支持基础功能观测能力')
  }
}