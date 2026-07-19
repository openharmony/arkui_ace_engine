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
 * 测试Image组件blendMode属性
 * 验证不同混合模式叠加在图片上的视觉效果
 */

@Entry
@Component
struct ImageBlendModeTestCase025 {
  @State currentBlendIndex: number = 0

  private readonly BLEND_MODES: Array<{ mode: BlendMode; label: string }> = [
    { mode: BlendMode.SRC_OVER, label: 'SRC_OVER' },
    { mode: BlendMode.MULTIPLY, label: 'MULTIPLY' },
    { mode: BlendMode.SCREEN, label: 'SCREEN' },
    { mode: BlendMode.OVERLAY, label: 'OVERLAY' },
    { mode: BlendMode.DARKEN, label: 'DARKEN' },
    { mode: BlendMode.LIGHTEN, label: 'LIGHTEN' },
    { mode: BlendMode.COLOR_DODGE, label: 'COLOR_DODGE' },
    { mode: BlendMode.COLOR_BURN, label: 'COLOR_BURN' },
    { mode: BlendMode.HARD_LIGHT, label: 'HARD_LIGHT' },
    { mode: BlendMode.SOFT_LIGHT, label: 'SOFT_LIGHT' },
    { mode: BlendMode.DIFFERENCE, label: 'DIFFERENCE' },
    { mode: BlendMode.EXCLUSION, label: 'EXCLUSION' }
  ]

  build() {
    Column() {
      Text('Image blendMode属性测试')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 16 })

      Stack() {
        Column()
          .width(150)
          .height(150)
          .backgroundColor('#FF6600')
          .borderRadius(8)

        Image($r('app.media.startIcon'))
          .width(150)
          .height(150)
          .blendMode(this.BLEND_MODES[this.currentBlendIndex].mode)
          .borderRadius(8)
      }
      .width(150)
      .height(150)
      .margin({ bottom: 16 })

      Text(`当前混合模式: ${this.BLEND_MODES[this.currentBlendIndex].label}`)
        .fontSize(14)
        .fontColor(Color.Gray)
        .margin({ bottom: 8 })

      Grid() {
        ForEach(this.BLEND_MODES, (config: { mode: BlendMode; label: string }, index: number) => {
          GridItem() {
            Stack() {
              Column()
                .width(50)
                .height(50)
                .backgroundColor('#FF6600')
                .borderRadius(4)

              Image($r('app.media.startIcon'))
                .width(50)
                .height(50)
                .blendMode(config.mode)
                .borderRadius(4)
                .border({
                  width: index === this.currentBlendIndex ? 2 : 0,
                  color: Color.Blue
                })
            }
            .width(50)
            .height(50)

            Text(config.label)
              .fontSize(9)
              .margin({ top: 2 })
              .fontColor(index === this.currentBlendIndex ? Color.Blue : Color.Gray)
          }
          .padding(6)
          .backgroundColor(index === this.currentBlendIndex ? '#E3F2FD' : '#FAFAFA')
          .borderRadius(4)
          .onClick(() => {
            this.currentBlendIndex = index
          })
        })
      }
      .columnsTemplate('repeat(4, 1fr)')
      .rowsGap(8)
      .columnsGap(8)
      .padding(16)
    }
    .width('100%')
    .height('100%')
    .padding(16)
  }
}
