/*
 * Copyright (c) 2025-2026 Huawei Device Co., Ltd.
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

import router from '@ohos.router';
@Entry
@Component
struct Index {

  build() {
    Row() {
      Column() {
        Text('').fontSize(28).fontWeight(FontWeight.Bold)
        Button('InterfaceTest_001')
          .margin(10)
          .height(60)
          .width(300)
          .onClick(() => {
            router.pushUrl({
              url: 'pages/PreviewAnimation/InterfaceTest_001',
            })
          })
        Button('InterfaceTest_002')
          .margin(10)
          .height(60)
          .width(300)
          .onClick(() => {
            router.pushUrl({
              url: 'pages/PreviewAnimation/InterfaceTest_002',
            })
          })
        Button('InterfaceTest_003')
          .margin(10)
          .height(60)
          .width(300)
          .onClick(() => {
            router.pushUrl({
              url: 'pages/PreviewAnimation/InterfaceTest_003',
            })
          })
        Button('InterfaceTest_004')
          .margin(10)
          .height(60)
          .width(300)
          .onClick(() => {
            router.pushUrl({
              url: 'pages/PreviewAnimation/InterfaceTest_004',
            })
          })

        Button('ScenariosTest_001')
          .margin(10)
          .height(60)
          .width(300)
          .onClick(() => {
            router.pushUrl({
              url: 'pages/PreviewAnimation/ScenariosTest_001',
            })
          })
        Button('ScenariosTest_002')
          .margin(10)
          .height(60)
          .width(300)
          .onClick(() => {
            router.pushUrl({
              url: 'pages/PreviewAnimation/ScenariosTest_002',
            })
          })
        Button('ScenariosTest_003')
          .margin(10)
          .height(60)
          .width(300)
          .onClick(() => {
            router.pushUrl({
              url: 'pages/PreviewAnimation/ScenariosTest_003',
            })
          })
        Button('ScenariosTest_004')
          .margin(10)
          .height(60)
          .width(300)
          .onClick(() => {
            router.pushUrl({
              url: 'pages/PreviewAnimation/ScenariosTest_004',
            })
          })
        Button('ScenariosTest_005')
          .margin(10)
          .height(60)
          .width(300)
          .onClick(() => {
            router.pushUrl({
              url: 'pages/PreviewAnimation/ScenariosTest_005',
            })
          })
      }
      .width('100%')
    }
    .height('100%')
  }
}