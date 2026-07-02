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
import { LengthMetrics, ColorMetrics } from '@kit.ArkUI';

@Entry
@Component
struct FocusBoxStylePage {
  private redBoxStyle: FocusBoxStyle = {
    strokeColor: ColorMetrics.resourceColor('#FFFF0000'),
    strokeWidth: LengthMetrics.vp(3),
    margin: LengthMetrics.vp(6)
  }

  private greenBoxStyle: FocusBoxStyle = {
    strokeColor: ColorMetrics.resourceColor('#FF00AA00'),
    strokeWidth: LengthMetrics.vp(2),
    margin: LengthMetrics.vp(4)
  }

  build() {
    Column({ space: 20 }) {
      Text('自定义焦点框样式')
        .width('100%')
        .fontSize(22)
        .fontWeight(FontWeight.Bold)
        .textAlign(TextAlign.Center)
        .padding({ top: 16, bottom: 8 })

      Text('focusBox(FocusBoxStyle) 自定义焦点框的边框颜色、宽度和边距')
        .fontSize(14)
        .fontColor('#666666')
        .padding({ left: 16, right: 16 })

      Column({ space: 24 }) {
        Text('默认焦点框样式')
          .fontSize(16)
          .fontColor('#333333')

        Button('Default Focus Box')
          .width('60%')
          .height(52)

        Divider().width('60%').color('#DDDDDD')

        Text('自定义焦点框样式（红色 3vp）')
          .fontSize(16)
          .fontColor('#333333')

        Button('Custom Focus Box')
          .width('60%')
          .height(52)
          .focusBox(this.redBoxStyle)

        Divider().width('60%').color('#DDDDDD')

        Text('绿色焦点框（2vp）')
          .fontSize(16)
          .fontColor('#333333')

        Button('Green Focus Box')
          .width('60%')
          .height(52)
          .focusBox(this.greenBoxStyle)
      }
      .width('100%')
      .alignItems(HorizontalAlign.Center)
      .padding({ top: 16 })

      Text('使用说明：\n1. 按 Tab 键在按钮间切换\n2. 第一个按钮显示系统默认焦点框\n3. 第二个按钮显示红色 3vp 自定义焦点框\n4. 第三个按钮显示绿色 2vp 焦点框')
        .fontSize(13)
        .fontColor('#999999')
        .padding({ left: 16, right: 16, bottom: 16 })
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#F5F5F5')
  }
}
