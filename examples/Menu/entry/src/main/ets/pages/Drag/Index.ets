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
    Scroll() {
      Row() {
        Column() {
          Text('').fontSize(28).fontWeight(FontWeight.Bold)
          Button('Drag1')
            .margin(10)
            .height(60)
            .width(300)
            .onClick(() => {
              router.pushUrl({
                url: 'pages/Drag/Drag1',
              })
            })
          Button('Drag2')
            .margin(10)
            .height(60)
            .width(300)
            .onClick(() => {
              router.pushUrl({
                url: 'pages/Drag/Drag2',
              })
            })
          Button('Drag3')
            .margin(10)
            .height(60)
            .width(300)
            .onClick(() => {
              router.pushUrl({
                url: 'pages/Drag/Drag3',
              })
            })
          Button('Drag4')
            .margin(10)
            .height(60)
            .width(300)
            .onClick(() => {
              router.pushUrl({
                url: 'pages/Drag/Drag4',
              })
            })
          Button('Drag5')
            .margin(10)
            .height(60)
            .width(300)
            .onClick(() => {
              router.pushUrl({
                url: 'pages/Drag/Drag5',
              })
            })
          Button('Drag6')
            .margin(10)
            .height(60)
            .width(300)
            .onClick(() => {
              router.pushUrl({
                url: 'pages/Drag/Drag6',
              })
            })
          Button('Drag7')
            .margin(10)
            .height(60)
            .width(300)
            .onClick(() => {
              router.pushUrl({
                url: 'pages/Drag/Drag7',
              })
            })

        }
        .width('100%')
      }
      .height('100%')
    }
  }
}