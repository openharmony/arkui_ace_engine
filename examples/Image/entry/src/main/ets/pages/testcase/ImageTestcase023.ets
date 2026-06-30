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
 * 测试Image组件fillColor属性
 * 验证不同颜色填充在SVG和模板模式下的效果
 */

@Entry
@Component
struct ImageFillColorTestCase023 {
  @State currentColorIndex: number = 0
  @State currentRenderMode: ImageRenderMode = ImageRenderMode.Template

  private readonly FILL_COLORS: Array<{ color: ResourceColor; label: string }> = [
    { color: Color.Red, label: '红色' },
    { color: Color.Green, label: '绿色' },
    { color: Color.Blue, label: '蓝色' },
    { color: Color.Yellow, label: '黄色' },
    { color: Color.Pink, label: '粉色' },
    { color: Color.Orange, label: '橙色' },
    { color: '#800080', label: '紫色' },
    { color: '#00FFFF', label: '青色' },
    { color: Color.White, label: '白色' },
    { color: Color.Black, label: '黑色' },
    { color: Color.Transparent, label: '透明' },
    { color: undefined, label: 'undefined' }
  ]

  build() {
    Column() {
      Text('Image fillColor属性测试')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 16 })

      Row() {
        Column() {
          Text('Template模式')
            .fontSize(14)
            .margin({ bottom: 8 })
          Image($r('app.media.startIcon'))
            .width(100)
            .height(100)
            .renderMode(ImageRenderMode.Template)
            .fillColor(this.FILL_COLORS[this.currentColorIndex].color)
            .border({ width: 2, color: Color.Blue })
            .borderRadius(8)
        }
        .margin({ right: 16 })

        Column() {
          Text('Original模式')
            .fontSize(14)
            .margin({ bottom: 8 })
          Image($r('app.media.startIcon'))
            .width(100)
            .height(100)
            .renderMode(ImageRenderMode.Original)
            .fillColor(this.FILL_COLORS[this.currentColorIndex].color)
            .border({ width: 2, color: Color.Gray })
            .borderRadius(8)
        }
      }
      .margin({ bottom: 16 })

      Text(`当前颜色: ${this.FILL_COLORS[this.currentColorIndex].label}`)
        .fontSize(14)
        .fontColor(Color.Gray)
        .margin({ bottom: 8 })

      Grid() {
        ForEach(this.FILL_COLORS, (config: { color: ResourceColor; label: string }, index: number) => {
          GridItem() {
            Column() {
              Column()
                .width(24)
                .height(24)
                .backgroundColor(config.color ?? Color.Transparent)
                .borderRadius(4)
                .border({ width: 1, color: Color.Gray })
              Text(config.label)
                .fontSize(10)
                .margin({ top: 4 })
            }
            .padding(8)
            .backgroundColor(index === this.currentColorIndex ? '#E3F2FD' : '#FAFAFA')
            .borderRadius(4)
            .onClick(() => {
              this.currentColorIndex = index
            })
          }
        })
      }
      .columnsTemplate('repeat(6, 1fr)')
      .rowsGap(8)
      .columnsGap(8)
    }
    .width('100%')
    .height('100%')
    .padding(16)
  }
}
