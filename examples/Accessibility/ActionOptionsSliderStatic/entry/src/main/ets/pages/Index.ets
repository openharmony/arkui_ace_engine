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

import {
  Entry,
  TextAlign,
  Flex,
  Text,
  Column,
  Component,
  Button,
  ClickEvent,
  FlexDirection,
  FlexWrap,
  FlexAlign,
  Builder,ButtonType
} from '@ohos.arkui.component'
import { State } from '@ohos.arkui.stateManagement'
import hilog from '@ohos.hilog'

@Entry
@Component
struct Index {
  build() {
    Column() {
      Text("API20(非2+1)")
        .fontSize(20)
        .textAlign(TextAlign.Center)
        .width('100%')
        .margin(10)
      this.ViewBuilder('slider001', 'pages/slider001')
      this.ViewBuilder('slider002', 'pages/slider002')
      this.ViewBuilder('slider003', 'pages/slider003')
      this.ViewBuilder('slider004', 'pages/slider004')
      this.ViewBuilder('slider005', 'pages/slider005')
    }
  }

  @Builder
  ViewBuilder(name: string, routerUrl: string) {
    Button(name)
      .id(name)
      .fontSize(12)
      .margin(3)
      .onClick((e: ClickEvent) => {
        let uiContext = this.getUIContext();
        let router = uiContext.getRouter();
        router.pushUrl({
          url: routerUrl
        })
      })
  }
}