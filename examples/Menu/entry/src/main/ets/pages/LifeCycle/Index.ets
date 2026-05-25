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
          Button('右击')
            .margin(10)
            .height(60)
            .width(300)
            .onClick(() => {
              router.pushUrl({
                url: 'pages/LifeCycle/aboutToAppear/RightClick',
              })
            })
          Button('长按')
            .margin(10)
            .height(60)
            .width(300)
            .onClick(() => {
              router.pushUrl({
                url: 'pages/LifeCycle/aboutToAppear/LongPress',
              })
            })
          Button('aboutToAppear_BindMenu_编译失败_onAppear()')
            .margin(10)
            .height(60)
            .width(300)
            .onClick(() => {
              router.pushUrl({
                url: 'pages/LifeCycle/aboutToAppear/BindMenu',
              })
            })
          Button('aboutToDisappear_右击')
            .margin(10)
            .height(60)
            .width(300)
            .onClick(() => {
              router.pushUrl({
                url: 'pages/LifeCycle/aboutToDisappear/Dis_RightClick',
              })
            })
          Button('aboutToDisappear_长按')
            .margin(10)
            .height(60)
            .width(300)
            .onClick(() => {
              router.pushUrl({
                url: 'pages/LifeCycle/aboutToDisappear/Dis_LongPress',
              })
            })
            Button('aboutToDisappear_BindMenu_编译失败_onDisappear')
            .margin(10)
            .height(60)
            .width(300)
            .onClick(() => {
              router.pushUrl({
                url: 'pages/LifeCycle/aboutToDisappear/Dis_BindMenu',
              })
            })


        }
        .width('100%')
      }
      .height('100%')
    }
  }
}