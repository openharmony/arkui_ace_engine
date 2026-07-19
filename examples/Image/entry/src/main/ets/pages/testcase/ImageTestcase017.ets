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

/**
 * 测试Image组件syncLoad和autoResize属性
 * 验证同步/异步加载模式和自动缩放行为
 */

@Entry
@Component
struct ImageSyncLoadTestCase017 {
  @State syncLoadEnabled: boolean = false
  @State autoResizeEnabled: boolean = true
  @State loadModeLabel: string = '异步加载'

  build() {
    Column() {
      Text('Image syncLoad/autoResize测试')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 16 })

      Row() {
        Column() {
          Text('同步加载模式')
            .fontSize(14)
            .margin({ bottom: 8 })
          Image($r('app.media.startIcon'))
            .width(120)
            .height(120)
            .syncLoad(true)
            .autoResize(this.autoResizeEnabled)
            .border({ width: 2, color: Color.Red })
            .borderRadius(8)
        }
        .margin({ right: 16 })

        Column() {
          Text('异步加载模式')
            .fontSize(14)
            .margin({ bottom: 8 })
          Image($r('app.media.startIcon'))
            .width(120)
            .height(120)
            .syncLoad(false)
            .autoResize(this.autoResizeEnabled)
            .border({ width: 2, color: Color.Blue })
            .borderRadius(8)
        }
      }
      .margin({ bottom: 16 })

      Column() {
        Text(`当前模式: ${this.loadModeLabel}`)
          .fontSize(14)
          .fontColor(Color.Gray)
          .margin({ bottom: 8 })

        Row({ space: 12 }) {
          Button('切换syncLoad')
            .onClick(() => {
              this.syncLoadEnabled = !this.syncLoadEnabled
              this.loadModeLabel = this.syncLoadEnabled ? '同步加载' : '异步加载'
            })
          Button('切换autoResize')
            .onClick(() => {
              this.autoResizeEnabled = !this.autoResizeEnabled
            })
          Button('重置')
            .onClick(() => {
              this.syncLoadEnabled = false
              this.autoResizeEnabled = true
              this.loadModeLabel = '异步加载'
            })
            .backgroundColor('#FF6666')
        }
      }

      Divider()
        .margin({ top: 16, bottom: 16 })

      Column() {
        Text('混合测试: syncLoad + autoResize')
          .fontSize(14)
          .fontWeight(FontWeight.Medium)
          .margin({ bottom: 8 })

        Image($r('app.media.background'))
          .width(150)
          .height(150)
          .syncLoad(this.syncLoadEnabled)
          .autoResize(this.autoResizeEnabled)
          .objectFit(ImageFit.Cover)
          .border({ width: 2, color: Color.Orange })
      }
    }
    .width('100%')
    .height('100%')
    .padding(16)
  }
}
