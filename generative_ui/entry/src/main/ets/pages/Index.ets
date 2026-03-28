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
  @State message: string = '欢迎使用 A2UI 渲染引擎';

  build() {
    Column() {
      // 标题
      Text(this.message)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 50, bottom: 30 })

      // 说明文本
      Text('这是一个基于 C++ 的原生 UI 渲染框架')
        .fontSize(16)
        .fontColor('#666666')
        .margin({ bottom: 40 })

      // 功能按钮列表 - 使用 Scroll 组件使其可滚动
      Scroll() {
        Column({ space: 15 }) {
          // 渲染演示按钮
          Button('A2UI 渲染演示')
            .width('80%')
            .height(50)
            .fontSize(18)
            .backgroundColor('#007DFF')
            .onClick(() => {
              router.pushUrl({
                url: 'pages/A2UIRenderDemo'
              });
            })

          // 数据更新与绑定
          Button('数据更新与绑定')
            .width('80%')
            .height(50)
            .fontSize(18)
            .backgroundColor('#00CB87')
            .enabled(true)
            .onClick(() => {
              router.pushUrl({
                url: 'pages/DataBindDemo'
              });
            })

          // 基础功能演示
          Button('基础框架功能')
            .width('80%')
            .height(50)
            .fontSize(18)
            .backgroundColor('#FF9500')
            .enabled(true)
            .onClick(() => {
              router.pushUrl({
                url: 'pages/SurfaceShowcase'
              });
            })

          // 多 Surface 管理
          Button('多 Surface 管理')
            .width('80%')
            .height(50)
            .fontSize(18)
            .backgroundColor('#3CC673')
            .enabled(true)
            .onClick(() => {
              router.pushUrl({
                url: 'pages/MultiSurfaceDemo'
              });
            })

          Button('多 RenderComponent 测试')
            .width('80%')
            .height(50)
            .fontSize(18)
            .backgroundColor('#CDB45A')
            .enabled(true)
            .onClick(() => {
              router.pushUrl({
                url: 'pages/MultiRenderComponentDemo'
              });
            })

          Button('功能演示 6')
            .width('80%')
            .height(50)
            .fontSize(18)
            .backgroundColor('#3C3EC6')
            .enabled(false)
            .opacity(0.5)

          Button('功能演示 7')
            .width('80%')
            .height(50)
            .fontSize(18)
            .backgroundColor('#85D789')
            .enabled(false)
            .opacity(0.5)

          Button('功能演示 8')
            .width('80%')
            .height(50)
            .fontSize(18)
            .backgroundColor('#E39783')
            .enabled(false)
            .opacity(0.5)

          Button('本地 json 测试集')
            .width('80%')
            .height(50)
            .fontSize(18)
            .backgroundColor('#B861BE')
            .enabled(true)
            .onClick(() => {
              router.pushUrl({
                url: 'pages/ShowJsonFolder'
              });
            })
        }
        .width('100%')
        .padding({ left: 20, right: 20, top: 10, bottom: 10 })
      }
      .width('100%')
      .height(350) // 限制高度，使其可滚动
      .scrollBar(BarState.Auto)

      // 底部说明
      Column({ space: 10 }) {
        Text('功能特性：')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .margin({ top: 40 })

        Text('• 高性能 C++ 渲染引擎')
          .fontSize(14)
          .fontColor('#666666')

        Text('• 灵活的组件系统')
          .fontSize(14)
          .fontColor('#666666')

        Text('• 数据绑定支持')
          .fontSize(14)
          .fontColor('#666666')

        Text('• 动态组件更新')
          .fontSize(14)
          .fontColor('#666666')
      }
      .margin({ top: 20 })
    }
    .width('100%')
    .height('100%')
    .padding(20)
    .backgroundColor('#f5f5f5')
  }
}
