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

import { Entry, $$, Text, TextAttribute, TextAlign, Column, Scroll, Row,
  ForEach, Component, ScrollDirection, Button, ClickEvent, Color } from '@ohos.arkui.component'
import { State } from '@ohos.arkui.stateManagement'
import hilog from '@ohos.hilog'
import inspector from '@ohos.arkui.inspector'
@Entry
@Component
struct MyStateSample {
  @State Text_w_1: int = 100;
  @State Text_A_1: int = 0;
  @State Text_w_2: int = 100;
  @State Text_A_2: int = 1;
  @State Text_w_2a: int = 100;
  @State Text_A_2a: int = 0;
  @State Text_w_2b: int = 100;
  @State Text_A_2b: int = 0;
  @State Text_w_2c: int = 100;
  @State Text_A_2c: int = 0;
  @State Text_w_1a: int = 100;
  @State Text_A_1a: int = 0;
  @State isShow: boolean = true
  @State result: string = '';
  @State message1: string = '';
  @State stateVar: string = 'state var';
  message: string = 'var';

  @State flag:boolean = false;

  changeValue() {
    this.stateVar += '~'
  }

  build() {
    Scroll() {
      Scroll() {
        Column(undefined) {
          Text('测试结果: '+this.message1 + ' '+this.result)
          Row(){
            Button('尺寸_1').onClick((e: ClickEvent)=>{
              this.result = ''
              this.Text_w_1 += 10
              this.message1 = '尺寸_1'
            })
            Button('close_1').onClick((e: ClickEvent)=>{
              this.result = ''
              this.message1 = 'close_1'
            })
            Column(undefined){
              Text('一层子组件')
                .width(this.Text_w_1)
                .border({ width: 1 })
            }.id('COLUMN_ID_1_1').padding(3).borderWidth(1)
          }
          Text('一层子组件')
          Row(){
            Button('尺寸_2').onClick((e: ClickEvent)=>{
              this.result = ''
              this.Text_w_2 += 10
              this.message1 = '尺寸_2'
            })
            Button('缩放_2').onClick((e: ClickEvent)=>{
              this.result = ''
              this.Text_A_2 += 0.2
              this.message1 = '缩放_2'
            })
            Column(){
              Column() {
                Text('两层子组件')
                  .width(this.Text_w_2)
                  .border({ width: 1 })
                  .scale({
                    x: this.Text_A_2,
                    y: this.Text_A_2,
                    z: 1,
                    centerX:'50%',
                    centerY:'50%'
                  })
              }.id('COLUMN_ID_2_2').padding(3).borderWidth(1)
            }.id('COLUMN_ID_2_1').padding(3).borderWidth(1)
          }
          Text('两层子组件 每个父组件都注册监听')
          Row(){
            Button('尺寸_2a').onClick((e: ClickEvent)=>{
              this.result = ''
              this.Text_w_2a += 10
              this.message1 = '尺寸_2a'
            })
            Button('平移_2a').onClick((e: ClickEvent)=>{
              this.result = ''
              this.Text_A_2a += 10
              this.message1 = '平移_2a'
            })
            Column(){
              Column() {
                Text('两层子组件')
                  .width(this.Text_w_2a)
                  .border({ width: 1 })
                  .translate({
                    x: this.Text_A_2a,
                  })
                Text('2')
                  .width(100)
                  .border({ width: 1 })
              }.id('COLUMN_ID_2_2a').padding(3).borderWidth(1).borderColor(Color.Red)
            }.id('COLUMN_ID_2_1a').padding(3).borderWidth(1).borderColor(Color.Yellow)
          }
          Text('两层多个子组件，一个子组件变化')
          Row(){
            Button('尺寸_2b').onClick((e: ClickEvent)=>{
              this.result = ''
              this.Text_w_2b += 10
              this.message1 = '尺寸_2b'
            })
            Column(){
              Column() {
                Text('两层子组件')
                  .width(this.Text_w_2b)
                  .border({ width: 1 })
                Text('2')
                  .width(this.Text_w_2b)
                  .border({ width: 1 })
              }.id('COLUMN_ID_2_2b').padding(3).borderWidth(1).borderColor(Color.Red)
            }.id('COLUMN_ID_2_1b').padding(3).borderWidth(1).borderColor(Color.Yellow)
          }
          Text('两层多个子组件，多个子组件变化')
          Row(){
            Button('尺寸_2c').onClick((e: ClickEvent)=>{
              this.result = ''
              this.Text_w_2c += 10
              this.message1 = '尺寸_2c'
            })
            Column(){
              Column() {
                Text('两层子组件')
                  .width(this.Text_w_2c)
                  .border({ width: 1 })
              }.padding(3).borderWidth(1).borderColor(Color.Red)
            }.id('COLUMN_ID_2_1c').padding(3).borderWidth(1).borderColor(Color.Yellow)
          }
          Text('两层子组件 顶层父组件配置多个注册监听')
          Row(){
            Button('尺寸_1a').onClick((e: ClickEvent)=>{
              this.result = ''
              this.Text_w_1a += 10
              this.message1 = '尺寸_1a'
            })
            Text('组件自身')
              .width(this.Text_w_1a)
              .border({ width: 1 })
              .id('COLUMN_ID_1_1a')
          }
        }
      }.height('100%').width('100%').scrollable(ScrollDirection.Horizontal)
    }.height('100%').width('100%')
  }
  listener1_1:inspector.ComponentObserver =
    this.getUIContext().getUIInspector().createComponentObserver('COLUMN_ID_1_1') as inspector.ComponentObserver
  listener2_1:inspector.ComponentObserver =
    this.getUIContext().getUIInspector().createComponentObserver('COLUMN_ID_2_1') as inspector.ComponentObserver
  listener2_2:inspector.ComponentObserver =
    this.getUIContext().getUIInspector().createComponentObserver('COLUMN_ID_2_2') as inspector.ComponentObserver
  listener2_1a:inspector.ComponentObserver =
    this.getUIContext().getUIInspector().createComponentObserver('COLUMN_ID_2_1a') as inspector.ComponentObserver
  listener2_1b:inspector.ComponentObserver =
    this.getUIContext().getUIInspector().createComponentObserver('COLUMN_ID_2_1b') as inspector.ComponentObserver
  listener2_1c:inspector.ComponentObserver =
    this.getUIContext().getUIInspector().createComponentObserver('COLUMN_ID_2_1c') as inspector.ComponentObserver
  listener1_1a:inspector.ComponentObserver =
    this.getUIContext().getUIInspector().createComponentObserver('COLUMN_ID_1_1a') as inspector.ComponentObserver
  listener1_1b:inspector.ComponentObserver =
    this.getUIContext().getUIInspector().createComponentObserver('COLUMN_ID_1_1b') as inspector.ComponentObserver

  aboutToAppear() {
    let onDrawComplete: () => void = (): void => {
      this.result = 'onDrawComplete'
      hilog.info(0x0000, 'testTag:', 'neuTest: onDrawComplete');
    }
    let onDrawChildrenComplete: () => void = (): void => {
      this.result = 'onDrawChildrenComplete'
      hilog.info(0x0000, 'testTag:', 'neuTest: onDrawChildrenComplete');
    }
    let offDrawChildrenComplete: () => void = (): void => {
      this.result = 'offDrawChildrenComplete'
      hilog.info(0x0000, 'testTag:', 'neuTest: onDrawChildrenComplete');
    }
    let onDrawChildrenComplete_2_1: () => void = (): void => {
      this.result = 'onDrawChildrenComplete_2_1'
      hilog.info(0x0000, 'testTag:', 'neuTest: onDrawChildrenComplete_2_1');
    }
    let onDrawChildrenComplete_2_1_2: () => void = (): void => {
      this.result = 'onDrawChildrenComplete_2_1_2'
      hilog.info(0x0000, 'testTag:', 'neuTest: onDrawChildrenComplete_2_1_2');
    }
    let onDrawChildrenComplete_2_2: () => void = (): void => {
      this.result = 'onDrawChildrenComplete_2_2'
      hilog.info(0x0000, 'testTag:', 'neuTest: onDrawChildrenComplete_2_2');
    }
    let onDrawChildrenComplete_2_1a: () => void = (): void => {
      this.result = 'onDrawChildrenComplete_2_1a'
      console.info('neuTest: onDrawChildrenComplete_2_1a')
    }
    let onDrawChildrenComplete_2_1b: () => void = (): void => {
      this.result = 'onDrawChildrenComplete_2_1b'
      console.info('neuTest: onDrawChildrenComplete_2_1b')
    }
    let onDrawChildrenComplete_2_1c: () => void = (): void => {
      this.result = 'onDrawChildrenComplete_2_1c'
      console.info('neuTest: onDrawChildrenComplete_2_1c')
    }
    let onDrawChildrenComplete_2_1c2: () => void = (): void => {
      this.result += 'onDrawChildrenComplete_2_1c2'
      console.info('neuTest: onDrawChildrenComplete_2_1c2')
    }
    let onDrawChildrenComplete_1_1a: () => void = (): void => {
      this.result = 'onDrawChildrenComplete_1_1a'
      console.info('neuTest: onDrawChildrenComplete_1_1a')
    }
    let onDrawChildrenComplete_1_1b: () => void = (): void => {
      this.result = 'onDrawChildrenComplete_1_1b'
      console.info('neuTest: onDrawChildrenComplete_1_1b')
    }
    let onDrawComplete1: () => void = (): void => {
      this.result = 'onDrawComplete'
      hilog.info(0x0000, 'testTag:', 'neuTest: onDrawComplete');
    }
    let FuncLayout1 = onDrawComplete
    let FuncLayout2 = onDrawChildrenComplete
    let FuncLayout3 = onDrawChildrenComplete_2_1
    let FuncLayout4 = onDrawChildrenComplete_2_1_2
    let FuncLayout5 = onDrawChildrenComplete_2_2
    let FuncLayout6 = onDrawChildrenComplete_2_1a
    let FuncLayout7 = onDrawChildrenComplete_2_1b
    let FuncLayout8 = onDrawChildrenComplete_2_1c
    let FuncLayout9 = onDrawChildrenComplete_2_1c2
    let FuncLayout10 = onDrawChildrenComplete_1_1a
    let FuncLayout11 = onDrawChildrenComplete_1_1b

    let OffFuncLayout1 = onDrawComplete
    let OffFuncLayout2 = offDrawChildrenComplete
    let OffFuncLayout3 = onDrawChildrenComplete_2_1
    let OffFuncLayout4 = onDrawChildrenComplete_2_1_2
    let OffFuncLayout5 = onDrawChildrenComplete_2_2
    let OffFuncLayout6 = onDrawChildrenComplete_2_1a
    let OffFuncLayout7 = onDrawChildrenComplete_2_1b
    let OffFuncLayout8 = onDrawChildrenComplete_2_1c
    let OffFuncLayout9 = onDrawChildrenComplete_2_1c2
    let OffFuncLayout10 = onDrawChildrenComplete_1_1a
    let OffFuncLayout11 = onDrawChildrenComplete_1_1b

    this.listener1_1.onDrawChildren(FuncLayout1)
    this.listener2_1.onDrawChildren(FuncLayout2)
    this.listener2_2.onDrawChildren(FuncLayout3)
    this.listener2_1a.onDrawChildren(FuncLayout4)
    this.listener2_1b.onDrawChildren(FuncLayout5)
    this.listener2_1c.onDrawChildren(FuncLayout6)
    this.listener1_1a.onDrawChildren(FuncLayout7)
    this.listener1_1b.onDrawChildren(FuncLayout8)
  }
}