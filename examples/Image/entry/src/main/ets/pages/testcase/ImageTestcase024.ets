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
 * 测试Image组件borderRadius属性
 * 验证圆角在不同数值和方向配置下的表现
 */

@Entry
@Component
struct ImageBorderRadiusTestCase024 {
  @State currentRadiusIndex: number = 0

  private readonly RADIUS_CONFIGS: Array<{ radius: BorderRadiuses | number; label: string }> = [
    { radius: 0, label: '0' },
    { radius: 4, label: '4' },
    { radius: 8, label: '8' },
    { radius: 16, label: '16' },
    { radius: 32, label: '32' },
    { radius: 50, label: '50' },
    { radius: 75, label: '75' },
    { radius: { topLeft: 0, topRight: 20, bottomLeft: 20, bottomRight: 0 }, label: '对角圆角' },
    { radius: { topLeft: 30, topRight: 30, bottomLeft: 0, bottomRight: 0 }, label: '上半圆角' },
    { radius: { topLeft: 0, topRight: 0, bottomLeft: 30, bottomRight: 30 }, label: '下半圆角' }
  ]

  build() {
    Column() {
      Text('Image borderRadius属性测试')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 16 })

      Row() {
        Image($r('app.media.startIcon'))
          .width(150)
          .height(150)
          .borderRadius(this.RADIUS_CONFIGS[this.currentRadiusIndex].radius)
          .objectFit(ImageFit.Cover)
          .border({ width: 2, color: Color.Blue })
      }
      .margin({ bottom: 16 })

      Text(`当前配置: ${this.RADIUS_CONFIGS[this.currentRadiusIndex].label}`)
        .fontSize(14)
        .fontColor(Color.Gray)
        .margin({ bottom: 8 })

      Grid() {
        ForEach(this.RADIUS_CONFIGS, (config: { radius: BorderRadiuses | number; label: string }, index: number) => {
          GridItem() {
            Column() {
              Image($r('app.media.startIcon'))
                .width(50)
                .height(50)
                .borderRadius(config.radius)
                .border({ width: 1, color: Color.Gray })

              Text(config.label)
                .fontSize(10)
                .margin({ top: 4 })
                .fontColor(index === this.currentRadiusIndex ? Color.Blue : Color.Gray)
            }
            .padding(6)
            .backgroundColor(index === this.currentRadiusIndex ? '#E3F2FD' : '#FAFAFA')
            .borderRadius(4)
            .onClick(() => {
              this.currentRadiusIndex = index
            })
          }
        })
      }
      .columnsTemplate('repeat(5, 1fr)')
      .rowsGap(8)
      .columnsGap(6)
      .padding(16)
    }
    .width('100%')
    .height('100%')
    .padding(16)
  }
}
