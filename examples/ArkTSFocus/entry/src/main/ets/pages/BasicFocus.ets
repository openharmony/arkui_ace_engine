/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

@Entry
@Component
struct BasicFocus {
  @State focusA: boolean = false
  @State focusB: boolean = false
  @State logText: string = '等待焦点操作...'

  build() {
    Column({ space: 20 }) {
      Text('基础焦点能力')
        .width('100%')
        .fontSize(22)
        .fontWeight(FontWeight.Bold)
        .textAlign(TextAlign.Center)
        .padding({ top: 16, bottom: 8 })

      Text('defaultFocus(true) 的按钮在页面加载时自动获焦')
        .fontSize(14)
        .fontColor('#666666')
        .padding({ left: 16, right: 16 })

      Column({ space: 12 }) {
        Button('Button A (defaultFocus)')
          .width('80%')
          .height(48)
          .backgroundColor(this.focusA ? '#FF007DFF' : '#FFCCCCCC')
          .defaultFocus(true)
          .onFocus(() => {
            this.focusA = true
            this.logText = 'Button A 获焦 (onFocus)'
          })
          .onBlur(() => {
            this.focusA = false
          })

        Button('Button B (focusable)')
          .width('80%')
          .height(48)
          .backgroundColor(this.focusB ? '#FF007DFF' : '#FFCCCCCC')
          .focusable(true)
          .onFocus(() => {
            this.focusB = true
            this.logText = 'Button B 获焦 (onFocus)'
          })
          .onBlur(() => {
            this.focusB = false
            this.logText = 'Button B 失焦 (onBlur)'
          })

        Text('不可聚焦的 Text (focusable(false))')
          .width('80%')
          .height(48)
          .textAlign(TextAlign.Center)
          .backgroundColor('#FFEEEEEE')
          .borderRadius(8)
          .fontSize(14)
          .focusable(false)
      }
      .width('100%')
      .alignItems(HorizontalAlign.Center)

      Divider().width('80%').color('#EEEEEE')

      Row({ space: 8 }) {
        Text('状态:')
          .fontSize(15)
          .fontColor('#333333')
        Text(this.logText)
          .fontSize(15)
          .fontColor('#007DFF')
          .layoutWeight(1)
      }
      .width('80%')
      .padding({ top: 12, bottom: 12 })

      Text('使用说明：\n1. 页面加载时 Button A 自动获焦（蓝色）\n2. 按 Tab 键切换焦点到 Button B\n3. 再按 Tab 聚焦到下一个可聚焦节点，Button B 失焦变灰')
        .fontSize(13)
        .fontColor('#999999')
        .padding({ left: 16, right: 16, bottom: 16 })
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#F5F5F5')
  }
}
