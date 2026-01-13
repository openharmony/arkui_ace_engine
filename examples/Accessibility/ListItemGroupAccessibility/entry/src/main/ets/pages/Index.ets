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

import { router } from '@kit.ArkUI'

@Extend(Button)
function ButtonStyle() {
  .width('80%')
  .height(40)
  .backgroundColor('#007aff')
  .fontColor('#FFFFFF')
  .borderRadius(10)
  .fontSize(16)
  .fontWeight(FontWeight.Medium)
  .stateEffect(true)
  .margin(5)
  .alignRules({
    center: { anchor: '__container__', align: VerticalAlign.Center },
    middle: { anchor: '__container__', align: HorizontalAlign.Center }
  })
}

@Entry
@Component
struct Index {
  @State width_: string = '200'

  build() {
    Column() {
      Button("吸顶/吸底绿框聚焦")
        .onClick(() => {
          router.pushUrl({
            url: 'pages/itemHead'
          })
        })
        .ButtonStyle()
      Button("吸顶/吸底绿框聚焦-横屏")
        .onClick(() => {
          router.pushUrl({
            url: 'pages/itemHeadwight'
          })
        })
        .ButtonStyle()
      Button("吸顶/吸底绿框不聚焦")
        .onClick(() => {
          router.pushUrl({
            url: 'pages/notFocused'
          })
        })
        .ButtonStyle()
      Button("吸顶/吸底绿框不聚焦_header高度高于item")
        .onClick(() => {
          router.pushUrl({
            url: 'pages/notFocusedHeight'
          })
        })
        .ButtonStyle()
      Button("不吸顶/不吸底绿框不聚焦")
        .onClick(() => {
          router.pushUrl({
            url: 'pages/notStickyAndNotFocused'
          })
        })
        .ButtonStyle()
      Button("不吸顶/不吸底绿框聚焦")
        .onClick(() => {
          router.pushUrl({
            url: 'pages/notStickyAndFoucused'
          })
        })
        .ButtonStyle()
      Button("卡片_吸顶/吸底绿框聚焦")
        .onClick(() => {
          router.pushUrl({
            url: 'pages/Card'
          })
        })
        .ButtonStyle()
      Button("ComponentContent_吸顶/吸底绿框聚焦")
        .onClick(() => {
          router.pushUrl({
            url: 'pages/ComponentContent'
          })
        })
        .ButtonStyle()
      Button("多列布局_吸顶/吸底绿框聚焦")
        .onClick(() => {
          router.pushUrl({
            url: 'pages/lanes'
          })
        })
        .ButtonStyle()
      Button("uec")
        .onClick(() => {
          router.pushUrl({
            url: 'pages/UecPage'
          })
        })
        .ButtonStyle()
      Button("适老化")
        .onClick(() => {
          router.pushUrl({
            url: 'pages/fontScale'
          })
        })
        .ButtonStyle()
    }.width('100%').backgroundColor(0xDCDCDC).padding({ top: 5 })
  }
}