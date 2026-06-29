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
struct FocusScope {
  @State focusId: string = '无'

  build() {
    Column({ space: 20 }) {
      Text('焦点域（分组与优先级）')
        .width('100%')
        .fontSize(22)
        .fontWeight(FontWeight.Bold)
        .textAlign(TextAlign.Center)
        .padding({ top: 16, bottom: 8 })

      Text('focusScopeId 定义焦点域，groupDefaultFocus 设置域内默认焦点，\nfocusScopePriority 设置域优先级')
        .fontSize(14)
        .fontColor('#666666')
        .padding({ left: 16, right: 16 })

      Row({ space: 16 }) {
        Column({ space: 12 }) {
          Text('Scope A')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .fontColor('#333333')

          Button('A1 (groupDefaultFocus)')
            .width('100%')
            .height(44)
            .fontSize(13)
            .groupDefaultFocus(true)
            .onFocus(() => { this.focusId = 'A1' })

          Button('A2')
            .width('100%')
            .height(44)
            .onFocus(() => { this.focusId = 'A2' })

          Button('A3')
            .width('100%')
            .height(44)
            .onFocus(() => { this.focusId = 'A3' })
        }
        .layoutWeight(1)
        .padding(12)
        .backgroundColor('#FFFFFF')
        .borderRadius(8)
        .focusScopeId('scopeA', false, false)

        Column({ space: 12 }) {
          Text('Scope B (PRIOR)')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .fontColor('#333333')

          Button('B1')
            .width('100%')
            .height(44)
            .onFocus(() => { this.focusId = 'B1' })

          Button('B2 (groupDefaultFocus)')
            .width('100%')
            .height(44)
            .fontSize(13)
            .groupDefaultFocus(true)
            .onFocus(() => { this.focusId = 'B2' })

          Button('B3')
            .width('100%')
            .height(44)
            .onFocus(() => { this.focusId = 'B3' })
        }
        .layoutWeight(1)
        .padding(12)
        .backgroundColor('#FFFFFF')
        .borderRadius(8)
        .focusScopeId('scopeB', false, false)
        .focusScopePriority('scopeB', FocusPriority.PRIOR)
      }
      .width('92%')

      Divider().width('80%').color('#EEEEEE')

      Row({ space: 8 }) {
        Text('当前焦点:')
          .fontSize(15)
          .fontColor('#333333')
        Text(this.focusId)
          .fontSize(15)
          .fontColor('#007DFF')
          .layoutWeight(1)
      }
      .width('80%')
      .padding({ top: 12, bottom: 12 })

      Text('使用说明：\n1. Scope A 内按 Tab 键在 A1→A2→A3 间循环\n2. 从 Scope A 按 Tab 跳到 Scope B，默认聚焦 B2（groupDefaultFocus）\n3. Scope B 设置了 PRIOR 优先级，进入时优先选中')
        .fontSize(13)
        .fontColor('#999999')
        .padding({ left: 16, right: 16, bottom: 16 })
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#F5F5F5')
  }
}
