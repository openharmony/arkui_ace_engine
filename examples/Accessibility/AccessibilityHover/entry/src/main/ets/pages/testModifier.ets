/*
* Copyright (c) 2026 Huawei Device Co., Ltd.
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/
"use static"
import { Entry,ColumnAttribute, Text, TextAttribute,CommonAttribute, Column,
  Component, Column, ColumnAttribute, ClickEvent, $r, Row, Builder,
  AttributeModifier, Button, ButtonAttribute, JSON } from '@ohos.arkui.component';
import { State} from "@ohos.arkui.stateManagement"
import AtomicServiceOptions from '@ohos.app.ability.AtomicServiceOptions';
import hilog from '@ohos.hilog'
import inspector from '@ohos.arkui.inspector'
import router from '@ohos.router'
import common from '@ohos.app.ability.common';

@Entry
@Component
struct MyStateSample {
  @State appId: string = '5765880207853275489';
  @State modifier: MyColumnModifier = new MyColumnModifier('1_单个组件_yes')
  @State modifier2: MyColumnModifier = new MyColumnModifier('2_单个组件_no')
  @State modifier3: MyColumnModifier = new MyColumnModifier('3_单个组件_auto')
  @State modifier4: MyColumnModifier2 = new MyColumnModifier2('4_单个组件_auto')
  @State modifier7: MyColumnModifier = new MyColumnModifier('7_单个组件_yes')
  @State modifier8: MyColumnModifier = new MyColumnModifier('8_单个组件_no')
  @State modifier9: MyColumnModifier = new MyColumnModifier('9_单个组件_yes')
  @State modifier10: MyColumnModifier = new MyColumnModifier('10_单个组件_no')
  @State modifier11: MyColumnModifier = new MyColumnModifier('11_单个组件_yes')
  @State modifier12: MyColumnModifier = new MyColumnModifier('12_单个组件_no')
  @State modifier13: MyColumnModifier = new MyColumnModifier('13_单个组件_yes')
  @State modifier14: MyColumnModifier = new MyColumnModifier('14_单个组件_no')
  @State modifier15: MyColumnModifier = new MyColumnModifier('15_单个组件_no')
  @State modifier16: MyColumnModifier = new MyColumnModifier('16_单个组件_yes')
  @State modifier17: MyColumnModifier = new MyColumnModifier('17_单个组件_no')
  @State modifier18: MyColumnModifier = new MyColumnModifier('18_单个组件_yes')
  @State modifier01: MyColumnModifier3 = new MyColumnModifier3('父组件1')
  @State modifier02: MyColumnModifier3 = new MyColumnModifier3('父组件2')
  @State modifier03: MyColumnModifier3 = new MyColumnModifier3('父组件3')
  @State modifier04: MyColumnModifier3 = new MyColumnModifier3('父组件4')
  @State modifier05: MyColumnModifier3 = new MyColumnModifier3('父组件5')
  @State modifier06: MyColumnModifier3 = new MyColumnModifier3('父组件6')
  @State modifier07: MyColumnModifier3 = new MyColumnModifier3('父组件7')
  @State modifier08: MyColumnModifier3 = new MyColumnModifier3('父组件8')
  @State modifier09: MyColumnModifier3 = new MyColumnModifier3('父组件9')
  @State stateVar: string = 'state var';
  message: string = 'var';
  changeValue() {
    this.stateVar+='~'
  }

build() {
    Column() {
      Button('1_单个组件')
      Column(){

      }.width('50%').height('10%').borderWidth(2)
      .borderWidth(1).margin(5).padding(5)
      .attributeModifier(this.modifier)

      Text('父组件')
      Text('7_单个组件')
        Column(undefined){
          Column(){

          }
          .borderWidth(1).margin(5).padding(5)
          .width('30%').height('10%').borderWidth(2)
          .attributeModifier(this.modifier7)
        }.width('50%').height('50%').borderWidth(2)
        .attributeModifier(this.modifier01)
    }
  }
}
@Component
struct Child {
  @State stateVar: string = 'Child';
  build() {
    Text(this.stateVar).fontSize(50)
  }
}
export class MyColumnModifier implements AttributeModifier<ColumnAttribute> {
  n: string = ''
  constructor(n:string) {
    this.n = n
  }
  applyNormalAttribute(instance: ColumnAttribute): void {
    instance.onAccessibilityHoverTransparent((event)=>{
      console.log('send access neuTest: event Modifier ' + this.n + JSON.stringify(event))
    })
  }
}
export class MyColumnModifier2 implements AttributeModifier<ColumnAttribute> {
  n: string = ''
  constructor(n:string) {
    this.n = n
  }
  applyNormalAttribute(instance: ColumnAttribute): void {
    instance.onAccessibilityHoverTransparent((event)=>{
      console.log('send access neuTest: event Modifier ' + this.n + JSON.stringify(event))
    })
  }
}
export class MyColumnModifier3 implements AttributeModifier<ColumnAttribute> {
  n: string = ''
  constructor(n:string) {
    this.n = n
  }
  applyNormalAttribute(instance: ColumnAttribute): void {
    instance.onAccessibilityHoverTransparent((event)=>{
      console.log('send access neuTest: event Modifier ' + this.n + JSON.stringify(event))
    })
  }
}