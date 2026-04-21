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
import { Entry, Text, Column, Component, Button, ClickEvent } from '@ohos.arkui.component'
import {  Text, TextAttribute,CommonAttribute, Column, Component, Button, ButtonAttribute, ClickEvent,
  $r, Row, Builder ,JSON } from '@ohos.arkui.component';
import { State } from "@ohos.arkui.stateManagement"
import AtomicServiceOptions from '@ohos.app.ability.AtomicServiceOptions';
import hilog from '@ohos.hilog'
import inspector from '@ohos.arkui.inspector'
import common from '@ohos.app.ability.common';
import router from '@ohos.router';

@Entry
@Component
struct MyStateSample {
  @State appId: string = '5765880207853275489';
  @State stateVar: string = 'state var';
  message: string = 'var';
  changeValue() {
    this.stateVar += '~'
  }
  build() {
    Column() {
      Button('1_单个组件')
        Column(){
        }.width('50%').height('10%')
        .borderWidth(1).margin(5).padding(5)
        .onAccessibilityHoverTransparent((event)=>{
          console.log('send access neuTest: event 1_单个组件_yes onAcces' + JSON.stringify(event))
        })
        .onTouch((event)=>{
          console.log('send access neuTest: event 1_单个组件_yes onTouch ' + JSON.stringify(event))
        })
      Text('父组件')
      Text('7_单个组件')
      Row(){
        Column(undefined){
          Column(){
          }.width('50%').height('10%')
          .borderWidth(1).margin(5).padding(5)
          .onAccessibilityHoverTransparent((event)=>{
            console.log('send access neuTest: event 7_子 ' +JSON.stringify(event) )
          })
        }.width('50%').height('10%').borderWidth(2)
        .onAccessibilityHoverTransparent((event)=>{
          console.log('send access neuTest: event 7_父 ' +JSON.stringify(event) )
        })
      }

      Button('testModifier').onClick((e: ClickEvent)=>{
        this.getUIContext().getRouter().pushUrl({url: 'pages/testModifier'});
      })
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