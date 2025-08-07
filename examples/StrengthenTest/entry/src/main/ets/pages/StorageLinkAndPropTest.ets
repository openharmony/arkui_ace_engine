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

import {
  State,
  Link,
  Prop,
  StorageLink,
  StorageProp,
  AppStorage,
  LocalStorage,
  LocalStorageLink
} from '@ohos.arkui.stateManagement'

import hilog from '@ohos.hilog'

@Entry
@Component
export struct StorageLinkAndPropTest {

  @StorageLink('aPropA') aPropA: string  = 'A';
  @StorageLink('Count') aPropB: number | null | undefined = undefined;

  changeValue1() {
    this.aPropA+='A'
  }
  changeValue2() {
    if (this.aPropB=== undefined) {
      this.aPropB = null;
    } else if (this.aPropB === null) {
      this.aPropB = 5;
    } else {
      this.aPropB = undefined
    }
  }
  build() {
    NavDestination() {
      Column(undefined) {
        Button(`click to change parent aPropA`)
          .backgroundColor('#3CB371')
          .onClick((e: ClickEvent) => {
            hilog.info(0x0000, 'testTag', 'On Click');
            this.changeValue1()
          })
        Button(`click to change parent aPropA`)
          .backgroundColor('#3CB371')
          .onClick((e: ClickEvent) => {
            hilog.info(0x0000, 'testTag', 'On Click');
            this.changeValue2()
          })
        Text('aPropA:' + this.aPropA).fontSize(20)
        Text('aPropB:' + this.aPropB).fontSize(20)
        Child()
      }.margin(10)
    }
    .title('StorageLink/StorageProp支持基础功能观测')
  }
}

@Component
struct Child {
  build() {
    Column() {
      Text('this is middle level');
      GrandSon()
    }

  }
}

@Component
struct GrandSon {
  @StorageProp('aPropA') aPropA: string  = 'B';
  @StorageProp('Count') aPropB: number | null | undefined = null;

  changeValue1() {
    this.aPropA+='B'
  }
  changeValue2() {
    if (this.aPropB=== undefined) {
      this.aPropB = null;
    } else if (this.aPropB === null) {
      this.aPropB = 10;
    } else {
      this.aPropB = undefined
    }
  }
  build() {
    Column(undefined) {
      Button(`click to change aPropA`)
        .backgroundColor('#4169E1')
        .onClick((e: ClickEvent) => {
          hilog.info(0x0000, 'testTag', 'On Click');
          this.changeValue1()
        })
      Button(`click to change parent aPropB`)
        .backgroundColor('#3CB371')
        .onClick((e: ClickEvent) => {
          hilog.info(0x0000, 'testTag', 'On Click');
          this.changeValue2()
        })
      Text('aPropA:' + this.aPropA).fontSize(20)
      Text('aPropB:' + this.aPropB).fontSize(20)
    }
  }
}