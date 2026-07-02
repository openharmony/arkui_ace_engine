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
struct FocusOnTouch {
  @State focusOnTouchEnabled: boolean = true
  @State touchAreaColor: string = '#FFCCCCCC'
  @State logText: string = '点击下方区域体验触摸聚焦'

  private toggleFocusOnTouch(): void {
    this.focusOnTouchEnabled = !this.focusOnTouchEnabled
    this.logText = `focusOnTouch: ${this.focusOnTouchEnabled ? '开启' : '关闭'}`
  }

  private requestFocusToTarget(): void {
    try {
      this.getUIContext().getFocusController().requestFocus('targetTouchArea')
      this.logText = 'getFocusController().requestFocus 成功'
    } catch (err) {
      this.logText = `请求焦点失败: ${JSON.stringify(err)}`
    }
  }

  private requestFocusGlobal(): void {
    try {
      focusControl.requestFocus('targetTouchArea')
      this.logText = 'focusControl.requestFocus 成功'
    } catch (err) {
      this.logText = `请求焦点失败: ${JSON.stringify(err)}`
    }
  }

  build() {
    Column({ space: 20 }) {
      Text('触摸聚焦与命令式 API')
        .width('100%')
        .fontSize(22)
        .fontWeight(FontWeight.Bold)
        .textAlign(TextAlign.Center)
        .padding({ top: 16, bottom: 8 })

      Text('focusOnTouch 控制触摸是否聚焦，focusControl 命令式请求焦点')
        .fontSize(14)
        .fontColor('#666666')
        .padding({ left: 16, right: 16 })

      Column({ space: 8 }) {
        Text('点击此区域聚焦 (focusOnTouch)')
          .id('targetTouchArea')
          .width('80%')
          .height(80)
          .textAlign(TextAlign.Center)
          .backgroundColor(this.touchAreaColor)
          .borderRadius(8)
          .fontSize(15)
          .focusable(true)
          .focusOnTouch(this.focusOnTouchEnabled)
          .onFocus(() => {
            this.touchAreaColor = '#FF007DFF'
            this.logText = '触摸区域获焦'
          })
          .onBlur(() => {
            this.touchAreaColor = '#FFCCCCCC'
          })
      }
      .width('100%')
      .alignItems(HorizontalAlign.Center)

      Row({ space: 12 }) {
        Button(this.focusOnTouchEnabled ? '关闭 focusOnTouch' : '开启 focusOnTouch')
          .layoutWeight(1)
          .height(44)
          .fontSize(13)
          .onClick(() => {
            this.toggleFocusOnTouch()
          })

        Button('请求聚焦 (UIContext)')
          .layoutWeight(1)
          .height(44)
          .fontSize(13)
          .onClick(() => {
            this.requestFocusToTarget()
          })
      }
      .width('80%')

      Row({ space: 12 }) {
        Button('请求聚焦 (focusControl)')
          .layoutWeight(1)
          .height(44)
          .fontSize(13)
          .onClick(() => {
            this.requestFocusGlobal()
          })
      }
      .width('80%')

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

      Text('使用说明：\n1. 点击蓝色区域 → 获焦变色（focusOnTouch 开启时）\n2. 关闭 focusOnTouch 后点击 → 不获焦\n3. 点击按钮可命令式请求聚焦到目标区域')
        .fontSize(13)
        .fontColor('#999999')
        .padding({ left: 16, right: 16, bottom: 16 })
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#F5F5F5')
  }
}
