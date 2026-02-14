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

/**
 * Image component dynamicRangeMode property examples
 */
@Entry
@Component
struct ImageDynamicRangeModeExample {
  @State currentMode: DynamicRangeMode = DynamicRangeMode.STANDARD

  build() {
    Column({ space: 20 }) {
      Text('DynamicRangeMode 属性示例')
        .fontSize(20)
        .fontColor(Color.Gray)

      // STANDARD - 标准动态范围
      Column({ space: 15 }) {
        Text('STANDARD (标准模式)')
          .fontSize(16)
        Image($r('app.media.app_icon'))
            .width(200)
            .height(200)
            .dynamicRangeMode(DynamicRangeMode.STANDARD)
            .border({ width: 2, color: this.currentMode === DynamicRangeMode.STANDARD ? Color.Green : Color.Transparent })
            .onClick(() => {
              this.currentMode = DynamicRangeMode.STANDARD
            })
        Text('标准动态范围，无特殊效果')
          .fontSize(14)
          .fontColor(Color.Gray)
      }

      // HIGH - 高动态范围
      Column({ space: 15 }) {
        Text('HIGH (高动态范围)')
          .fontSize(16)
        Image($r('app.media.app_icon'))
            .width(200)
            .height(200)
            .dynamicRangeMode(DynamicRangeMode.HIGH)
            .border({ width: 2, color: this.currentMode === DynamicRangeMode.HIGH ? Color.Green : Color.Transparent })
            .onClick(() => {
              this.currentMode = DynamicRangeMode.HIGH
            })
        Text('高动态范围，增强图片色彩表现')
          .fontSize(14)
          .fontColor(Color.Gray)
      }

      // CONSTRAINT - 约束动态范围
      Column({ space: 15 }) {
        Text('CONSTRAINT (约束模式)')
          .fontSize(16)
        Image($r('app.media.app_icon'))
            .width(200)
            .height(200)
            .dynamicRangeMode(DynamicRangeMode.CONSTRAINT)
            .border({ width: 2, color: this.currentMode === DynamicRangeMode.CONSTRAINT ? Color.Green : Color.Transparent })
            .onClick(() => {
              this.currentMode = DynamicRangeMode.CONSTRAINT
            })
        Text('约束动态范围，限制色彩范围以保护视觉')
          .fontSize(14)
          .fontColor(Color.Gray)
      }

      Divider().strokeWidth(2)

      Text('当前动态范围模式: ' + this.currentMode)
        .fontSize(18)
        .fontWeight(FontWeight.Medium)

      Text('dynamicRangeMode 属性用于HDR图片的动态范围显示')
        .fontSize(14)
        .fontColor(Color.Blue)
        .margin({ top: 10 })
    }
    .width('100%')
    .height('100%')
    .padding(20)
    .backgroundColor(Color.White)
  }
}
