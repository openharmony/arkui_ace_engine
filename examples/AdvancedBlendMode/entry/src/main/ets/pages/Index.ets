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

import { router } from '@kit.ArkUI';

@Entry
@Component
struct Index {
  build() {
    Row() {
      Scroll() {
        Column() {
          Button("text")
            .width('90%')
            .fontSize('20vp')
            .margin({ bottom: 15 })
            .onClick(() => {
              router.pushUrl({ url: 'pages/text' })
            })
          Button('textInput')
            .width('90%')
            .fontSize('20vp')
            .margin({ bottom: 15 })
            .onClick(() => {
              router.pushUrl({ url: 'pages/textinput' })
            })
            .width('100%')
          Button('textArea')
            .width('90%')
            .fontSize('20vp')
            .margin({ bottom: 15 })
            .onClick(() => {
              router.pushUrl({ url: 'pages/textArea' })
            })
            .width('100%')
          Button('text_modifier')
            .width('90%')
            .fontSize('20vp')
            .margin({ bottom: 15 })
            .onClick(() => {
              router.pushUrl({ url: 'pages/text_modifier' })
            })
            .width('100%')
          Button('textInput_modifier')
            .width('90%')
            .fontSize('20vp')
            .margin({ bottom: 15 })
            .onClick(() => {
              router.pushUrl({ url: 'pages/textInput_modifier' })
            })
            .width('100%')
          Button('textArea_modifier')
            .width('90%')
            .fontSize('20vp')
            .margin({ bottom: 15 })
            .onClick(() => {
              router.pushUrl({ url: 'pages/textArea_modifier' })
            })
            .width('100%')
        }
        .height('100%')
      }
    }
  }
}
