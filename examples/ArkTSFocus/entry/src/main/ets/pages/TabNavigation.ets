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
struct TabNavigation {
  @State focusId: string = '无'

  build() {
    Column({ space: 20 }) {
      Text('Tab 键导航')
        .width('100%')
        .fontSize(22)
        .fontWeight(FontWeight.Bold)
        .textAlign(TextAlign.Center)
        .padding({ top: 16, bottom: 8 })

      Text('tabIndex 控制 Tab 顺序（1→2→3），tabStop(false) 跳过节点')
        .fontSize(14)
        .fontColor('#666666')
        .padding({ left: 16, right: 16 })

      Column({ space: 12 }) {
        Button('Button 1 (tabIndex: 3)')
          .width('80%')
          .height(48)
          .tabIndex(3)
          .onFocus(() => { this.focusId = 'Button 1' })

        Button('Button 2 (tabIndex: 1)')
          .width('80%')
          .height(48)
          .tabIndex(1)
          .onFocus(() => { this.focusId = 'Button 2' })

        Button('Button 3 (tabIndex: 2)')
          .width('80%')
          .height(48)
          .tabIndex(2)
          .onFocus(() => { this.focusId = 'Button 3' })

        Button('Button 4 (tabStop: false)')
          .width('80%')
          .height(48)
          .tabIndex(4)
          .tabStop(false)
          .onFocus(() => { this.focusId = 'Button 4 (不应获焦)' })
      }
      .width('100%')
      .alignItems(HorizontalAlign.Center)

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

      Text('使用说明：\n1. 按 Tab 键，焦点顺序应为 Button 2 → Button 3 → Button 1\n2. Button 4 因 tabStop(false) 会被跳过\n3. tabIndex 值越小越优先')
        .fontSize(13)
        .fontColor('#999999')
        .padding({ left: 16, right: 16, bottom: 16 })
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#F5F5F5')
  }
}
