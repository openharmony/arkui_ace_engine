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
'use static'

import { Entry, Text, Column, Component, Button, ClickEvent,
  UIContext, ColumnOptions, TextAlign } from '@ohos.arkui.component'
import { State } from '@ohos.arkui.stateManagement'
import hilog from '@ohos.hilog'

@Entry
@Component
struct Index {
  message: string = 'var';
  uiContext: UIContext | undefined = undefined;
  aboutToAppear(): void {
    this.uiContext = this.getUIContext();
  }
  build() {
    Column({space:10} as ColumnOptions) {
      Text('Intercept')
        .fontColor(0xFFFFFF)
        .textAlign(TextAlign.Center)
        .width('100%')
        .backgroundColor(0x0000FF)
      Button("Toggle1_1")
        .margin(10)
        .width('80%')
        .onClick((e: ClickEvent) => {
          this.getUIContext().getRouter().pushUrl({url: 'pages/Toggle1_1'});
        })
      Button("Toggle1_2")
        .margin(10)
        .width('80%')
        .onClick((e: ClickEvent) => {
          this.getUIContext().getRouter().pushUrl({url: 'pages/Toggle1_2'});
        })
      Button("Toggle2")
        .margin(10)
        .width('80%')
        .onClick((e: ClickEvent) => {
          this.getUIContext().getRouter().pushUrl({url: 'pages/Toggle2'});
        })
    }
  }
}