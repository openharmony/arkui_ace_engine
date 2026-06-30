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
struct CustomNextFocus {
  @State focusId: string = '无'

  build() {
    Column({ space: 20 }) {
      Text('自定义焦点路径')
        .width('100%')
        .fontSize(22)
        .fontWeight(FontWeight.Bold)
        .textAlign(TextAlign.Center)
        .padding({ top: 16, bottom: 8 })

      Text('nextFocus 配置方向键跳转目标，覆盖默认导航')
        .fontSize(14)
        .fontColor('#666666')
        .padding({ left: 16, right: 16 })

      Column({ space: 12 }) {
        Row({ space: 12 }) {
          Column().width(120).height(48)

          Button('B1')
            .id('btnB1')
            .width(120)
            .height(48)
            .nextFocus({ down: 'btnB3' })
            .onFocus(() => { this.focusId = 'B1' })
        }

        Row({ space: 12 }) {
          Button('B2')
            .id('btnB2')
            .width(120)
            .height(48)
            .nextFocus({ right: 'btnB3', up: 'btnB1', down: 'btnB5' })
            .onFocus(() => { this.focusId = 'B2' })

          Button('B3')
            .id('btnB3')
            .width(120)
            .height(48)
            .nextFocus({ left: 'btnB2', right: 'btnB4', up: 'btnB1', down: 'btnB5' })
            .onFocus(() => { this.focusId = 'B3' })

          Button('B4')
            .id('btnB4')
            .width(120)
            .height(48)
            .nextFocus({ left: 'btnB3', up: 'btnB1', down: 'btnB5' })
            .onFocus(() => { this.focusId = 'B4' })
        }

        Row({ space: 12 }) {
          Column().width(120).height(48)

          Button('B5')
            .id('btnB5')
            .width(120)
            .height(48)
            .nextFocus({ up: 'btnB3' })
            .onFocus(() => { this.focusId = 'B5' })
        }
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

      Text('使用说明：\n1. 使用方向键（↑↓←→）在按钮间导航\n2. B3 右键 → B4，B3 下键 → B5（自定义路径）\n3. B2 左键无配置，使用默认行为')
        .fontSize(13)
        .fontColor('#999999')
        .padding({ left: 16, right: 16, bottom: 16 })
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#F5F5F5')
  }
}
