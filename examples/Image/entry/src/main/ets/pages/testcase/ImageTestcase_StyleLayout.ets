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
 * Image 样式与布局属性合集（由原 035/036/039/040/041/044 合并）
 * 覆盖：综合属性组合 / overlay 叠加 / 边框样式 / margin·padding / 背景色 / 宽高比
 */

/** 原 035：综合属性组合 */
@Component
struct ImageComprehensiveTestCase035 {
  @State imageWidth: number = 120
  @State imageHeight: number = 120
  @State objectFit: ImageFit = ImageFit.Cover
  @State borderRadius: number = 8
  @State opacity: number = 1.0
  @State rotateAngle: number = 0
  @State scaleValue: number = 1.0
  @State fillColor: ResourceColor = undefined
  @State renderMode: ImageRenderMode = ImageRenderMode.Original
  @State interpolation: ImageInterpolation = ImageInterpolation.High
  @State dynamicRange: DynamicRangeMode = DynamicRangeMode.STANDARD
  @State syncLoad: boolean = false
  @State autoResize: boolean = true
  @State privacySensitive: boolean = false
  @State analyzerEnabled: boolean = false
  @State draggable: boolean = false

  private readonly PRESET_COMBOS: Array<{
    name: string
    width: number; height: number; fit: ImageFit; radius: number; opacity: number
    angle: number; scale: number; fill: ResourceColor; mode: ImageRenderMode
  }> = [
    { name: '默认', width: 120, height: 120, fit: ImageFit.Cover, radius: 0, opacity: 1,
      angle: 0, scale: 1, fill: undefined, mode: ImageRenderMode.Original },
    { name: '圆角缩放', width: 100, height: 100, fit: ImageFit.Cover, radius: 20, opacity: 1,
      angle: 0, scale: 1.2, fill: undefined, mode: ImageRenderMode.Original },
    { name: '模板填充', width: 120, height: 120, fit: ImageFit.Contain, radius: 8, opacity: 1,
      angle: 0, scale: 1, fill: Color.Red, mode: ImageRenderMode.Template },
    { name: '旋转透明', width: 100, height: 100, fit: ImageFit.Cover, radius: 0, opacity: 0.5,
      angle: 45, scale: 1, fill: undefined, mode: ImageRenderMode.Original },
    { name: 'HDR高清', width: 150, height: 150, fit: ImageFit.Cover, radius: 12, opacity: 1,
      angle: 0, scale: 1, fill: undefined, mode: ImageRenderMode.Original },
    { name: '全属性组合', width: 100, height: 100, fit: ImageFit.ScaleDown, radius: 16, opacity: 0.8,
      angle: 30, scale: 1.1, fill: Color.Blue, mode: ImageRenderMode.Template }
  ]

  build() {
    Column() {
      Text('Image综合属性组合测试')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 16 })

      Image($r('app.media.startIcon'))
        .width(this.imageWidth)
        .height(this.imageHeight)
        .objectFit(this.objectFit)
        .borderRadius(this.borderRadius)
        .opacity(this.opacity)
        .rotate({ angle: this.rotateAngle })
        .scale({ x: this.scaleValue, y: this.scaleValue })
        .fillColor(this.fillColor)
        .renderMode(this.renderMode)
        .interpolation(this.interpolation)
        .dynamicRangeMode(this.dynamicRange)
        .syncLoad(this.syncLoad)
        .autoResize(this.autoResize)
        .privacySensitive(this.privacySensitive)
        .enableAnalyzer(this.analyzerEnabled)
        .draggable(this.draggable)
        .border({ width: 2, color: Color.Blue })
        .margin({ bottom: 16 })

      Text('属性预设组合')
        .fontSize(14)
        .fontWeight(FontWeight.Medium)
        .margin({ bottom: 8 })

      Grid() {
        ForEach(this.PRESET_COMBOS, (combo: {
          name: string
          width: number; height: number; fit: ImageFit; radius: number; opacity: number
          angle: number; scale: number; fill: ResourceColor; mode: ImageRenderMode
        }) => {
          GridItem() {
            Column() {
              Text(combo.name)
                .fontSize(12)
                .fontWeight(FontWeight.Medium)
            }
            .padding(12)
            .backgroundColor('#E3F2FD')
            .borderRadius(6)
            .onClick(() => {
              this.imageWidth = combo.width
              this.imageHeight = combo.height
              this.objectFit = combo.fit
              this.borderRadius = combo.radius
              this.opacity = combo.opacity
              this.rotateAngle = combo.angle
              this.scaleValue = combo.scale
              this.fillColor = combo.fill
              this.renderMode = combo.mode
              if (combo.name === 'HDR高清') {
                this.dynamicRange = DynamicRangeMode.HIGH
                this.interpolation = ImageInterpolation.High
              } else {
                this.dynamicRange = DynamicRangeMode.STANDARD
                this.interpolation = ImageInterpolation.None
              }
            })
          }
        })
      }
      .columnsTemplate('repeat(3, 1fr)')
      .rowsGap(8)
      .columnsGap(8)
      .padding(16)

      Button('重置所有属性')
        .onClick(() => {
          this.imageWidth = 120
          this.imageHeight = 120
          this.objectFit = ImageFit.Cover
          this.borderRadius = 0
          this.opacity = 1.0
          this.rotateAngle = 0
          this.scaleValue = 1.0
          this.fillColor = undefined
          this.renderMode = ImageRenderMode.Original
          this.interpolation = ImageInterpolation.High
          this.dynamicRange = DynamicRangeMode.STANDARD
          this.syncLoad = false
          this.autoResize = true
          this.privacySensitive = false
          this.analyzerEnabled = false
          this.draggable = false
        })
        .backgroundColor('#FF6666')
        .margin({ top: 16 })
    }
    .width('100%')
    .height('100%')
    .padding(16)
  }
}

/** 原 036：overlay 文字叠加 */
@Component
struct ImageOverlayTestCase036 {
  @State currentOverlayIndex: number = 0

  private readonly OVERLAY_CONFIGS: Array<{ text: string; align: Alignment; offsetX: number; offsetY: number }> = [
    { text: '顶部居中', align: Alignment.Top, offsetX: 0, offsetY: 10 },
    { text: '底部居中', align: Alignment.Bottom, offsetX: 0, offsetY: 10 },
    { text: '居中', align: Alignment.Center, offsetX: 0, offsetY: 0 },
    { text: '左上', align: Alignment.TopStart, offsetX: 10, offsetY: 10 },
    { text: '右上', align: Alignment.TopEnd, offsetX: -10, offsetY: 10 },
    { text: '左下', align: Alignment.BottomStart, offsetX: 10, offsetY: -10 },
    { text: '右下', align: Alignment.BottomEnd, offsetX: -10, offsetY: -10 },
    { text: '偏移大', align: Alignment.Center, offsetX: 50, offsetY: -30 }
  ]

  build() {
    Column() {
      Text('Image overlay属性测试')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 16 })

      Row() {
        Image($r('app.media.startIcon'))
          .width(200)
          .height(200)
          .overlay(
            this.OVERLAY_CONFIGS[this.currentOverlayIndex].text,
            {
              align: this.OVERLAY_CONFIGS[this.currentOverlayIndex].align,
              offset: {
                x: this.OVERLAY_CONFIGS[this.currentOverlayIndex].offsetX,
                y: this.OVERLAY_CONFIGS[this.currentOverlayIndex].offsetY
              }
            }
          )
          .objectFit(ImageFit.Cover)
          .border({ width: 2, color: Color.Blue })
          .borderRadius(8)

        Column() {
          Text('当前overlay配置')
            .fontSize(14)
            .fontWeight(FontWeight.Medium)
            .margin({ bottom: 8 })
          Text(`文字: ${this.OVERLAY_CONFIGS[this.currentOverlayIndex].text}`)
            .fontSize(12)
            .fontColor(Color.Gray)
          Text(`对齐: ${this.currentOverlayIndex}`)
            .fontSize(12)
            .fontColor(Color.Gray)
          Text('偏移: (' + this.OVERLAY_CONFIGS[this.currentOverlayIndex].offsetX + ', ' +
            this.OVERLAY_CONFIGS[this.currentOverlayIndex].offsetY + ')')
            .fontSize(12)
            .fontColor(Color.Gray)
        }
        .margin({ left: 16 })
      }
      .margin({ bottom: 16 })

      Grid() {
        ForEach(this.OVERLAY_CONFIGS, (config: {
          text: string; align: Alignment; offsetX: number; offsetY: number
        }, index: number) => {
          GridItem() {
            Column() {
              Text(config.text)
                .fontSize(12)
                .fontColor(index === this.currentOverlayIndex ? Color.Blue : Color.Gray)
            }
            .padding(10)
            .backgroundColor(index === this.currentOverlayIndex ? '#E3F2FD' : '#FAFAFA')
            .borderRadius(4)
            .onClick(() => {
              this.currentOverlayIndex = index
            })
          }
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

/** 原 039：边框样式组合 */
@Component
struct ImageBorderStyleTestCase039 {
  @State currentBorderIndex: number = 0

  private readonly BORDER_CONFIGS: Array<{
    width: Length; color: ResourceColor; style: BorderStyle; radius: number; label: string
  }> = [
    { width: 0, color: Color.Gray, style: BorderStyle.Solid, radius: 0, label: '无边框' },
    { width: 1, color: Color.Black, style: BorderStyle.Solid, radius: 0, label: '细实线' },
    { width: 3, color: Color.Blue, style: BorderStyle.Solid, radius: 8, label: '蓝实线圆角' },
    { width: 5, color: Color.Red, style: BorderStyle.Dashed, radius: 12, label: '红虚线圆角' },
    { width: 2, color: Color.Green, style: BorderStyle.Dotted, radius: 4, label: '绿点线' },
    { width: 8, color: Color.Orange, style: BorderStyle.Solid, radius: 20, label: '橙粗线大圆角' },
    { width: 4, color: '#800080', style: BorderStyle.Dashed, radius: 0, label: '紫虚线方角' },
    { width: 6, color: Color.Pink, style: BorderStyle.Dotted, radius: 16, label: '粉点线中圆角' }
  ]

  build() {
    Column() {
      Text('Image边框样式组合测试')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 16 })

      Image($r('app.media.startIcon'))
        .width(150)
        .height(150)
        .objectFit(ImageFit.Cover)
        .border({
          width: this.BORDER_CONFIGS[this.currentBorderIndex].width,
          color: this.BORDER_CONFIGS[this.currentBorderIndex].color,
          style: this.BORDER_CONFIGS[this.currentBorderIndex].style,
          radius: this.BORDER_CONFIGS[this.currentBorderIndex].radius
        })
        .margin({ bottom: 16 })

      Text(`当前配置: ${this.BORDER_CONFIGS[this.currentBorderIndex].label}`)
        .fontSize(14)
        .fontColor(Color.Gray)
        .margin({ bottom: 8 })

      Text(`width=${this.BORDER_CONFIGS[this.currentBorderIndex].width} ` +
        `color=${this.BORDER_CONFIGS[this.currentBorderIndex].color} ` +
        `style=${this.BORDER_CONFIGS[this.currentBorderIndex].style} ` +
        `radius=${this.BORDER_CONFIGS[this.currentBorderIndex].radius}`)
        .fontSize(11)
        .fontColor(Color.Gray)
        .margin({ bottom: 12 })

      Grid() {
        ForEach(this.BORDER_CONFIGS, (config: {
          width: Length; color: ResourceColor; style: BorderStyle; radius: number; label: string
        }, index: number) => {
          GridItem() {
            Column() {
              Image($r('app.media.startIcon'))
                .width(60)
                .height(60)
                .border({
                  width: config.width,
                  color: config.color,
                  style: config.style,
                  radius: config.radius
                })

              Text(config.label)
                .fontSize(10)
                .margin({ top: 4 })
                .fontColor(index === this.currentBorderIndex ? Color.Blue : Color.Gray)
            }
            .padding(8)
            .backgroundColor(index === this.currentBorderIndex ? '#E3F2FD' : '#FAFAFA')
            .borderRadius(4)
            .onClick(() => {
              this.currentBorderIndex = index
            })
          }
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

/** 原 040：margin/padding 布局 */
@Component
struct ImageMarginPaddingTestCase040 {
  @State currentLayoutIndex: number = 0

  private readonly LAYOUT_CONFIGS: Array<{
    margin: Margin | number; padding: Padding | number; label: string
  }> = [
    { margin: 0, padding: 0, label: '无间距' },
    { margin: 10, padding: 10, label: '均匀10' },
    { margin: 20, padding: 5, label: 'margin大' },
    { margin: 5, padding: 20, label: 'padding大' },
    { margin: { left: 30, right: 10, top: 10, bottom: 10 }, padding: 10, label: '左偏margin' },
    { margin: { left: 10, right: 30, top: 10, bottom: 10 }, padding: 10, label: '右偏margin' },
    { margin: { left: 10, right: 10, top: 30, bottom: 10 }, padding: 10, label: '上偏margin' },
    { margin: { left: 10, right: 10, top: 10, bottom: 30 }, padding: 10, label: '下偏margin' },
    { margin: 15, padding: { left: 20, right: 5, top: 5, bottom: 20 }, label: '不对称padding' },
    { margin: { left: 0, right: 0, top: 0, bottom: 40 }, padding: 0, label: '仅底部margin' }
  ]

  build() {
    Column() {
      Text('Image margin/padding布局测试')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 16 })

      Row() {
        Column() {
          Text('应用间距')
            .fontSize(14)
            .margin({ bottom: 8 })
          Image($r('app.media.startIcon'))
            .width(100)
            .height(100)
            .margin(this.LAYOUT_CONFIGS[this.currentLayoutIndex].margin)
            .padding(this.LAYOUT_CONFIGS[this.currentLayoutIndex].padding)
            .objectFit(ImageFit.Cover)
            .backgroundColor('#F0F0F0')
            .border({ width: 2, color: Color.Blue })
        }

        Column() {
          Text('参考(无间距)')
            .fontSize(14)
            .margin({ bottom: 8 })
          Image($r('app.media.startIcon'))
            .width(100)
            .height(100)
            .objectFit(ImageFit.Cover)
            .backgroundColor('#F5F5F5')
            .border({ width: 1, color: Color.Gray })
        }
      }
      .margin({ bottom: 16 })

      Text(`当前配置: ${this.LAYOUT_CONFIGS[this.currentLayoutIndex].label}`)
        .fontSize(14)
        .fontColor(Color.Gray)
        .margin({ bottom: 8 })

      Grid() {
        ForEach(this.LAYOUT_CONFIGS, (config: {
          margin: Margin | number; padding: Padding | number; label: string
        }, index: number) => {
          GridItem() {
            Column() {
              Text(config.label)
                .fontSize(11)
                .fontColor(index === this.currentLayoutIndex ? Color.Blue : Color.Gray)
            }
            .padding(8)
            .backgroundColor(index === this.currentLayoutIndex ? '#E3F2FD' : '#FAFAFA')
            .borderRadius(4)
            .onClick(() => {
              this.currentLayoutIndex = index
            })
          }
        })
      }
      .columnsTemplate('repeat(5, 1fr)')
      .rowsGap(8)
      .columnsGap(8)
      .padding(16)
    }
    .width('100%')
    .height('100%')
    .padding(16)
  }
}

/** 原 041：backgroundColor 背景色 */
@Component
struct ImageBackgroundColorTestCase041 {
  @State currentBgIndex: number = 0

  private readonly BG_COLORS: Array<{ color: ResourceColor; label: string }> = [
    { color: Color.Transparent, label: '透明' },
    { color: '#F5F5F5', label: '浅灰' },
    { color: '#E0E0E0', label: '中灰' },
    { color: '#333333', label: '深灰' },
    { color: Color.White, label: '白色' },
    { color: Color.Black, label: '黑色' },
    { color: '#FF0000', label: '红色' },
    { color: '#0000FF', label: '蓝色' },
    { color: '#00FF00', label: '绿色' },
    { color: '#80008080', label: '半透明紫' }
  ]

  build() {
    Column() {
      Text('Image backgroundColor属性测试')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 16 })

      Row() {
        Column() {
          Text('Contain+背景色')
            .fontSize(14)
            .margin({ bottom: 8 })
          Image($r('app.media.startIcon'))
            .width(150)
            .height(150)
            .backgroundColor(this.BG_COLORS[this.currentBgIndex].color)
            .objectFit(ImageFit.Contain)
            .border({ width: 2, color: Color.Blue })
        }
        .margin({ right: 16 })

        Column() {
          Text('Cover+背景色')
            .fontSize(14)
            .margin({ bottom: 8 })
          Image($r('app.media.startIcon'))
            .width(150)
            .height(150)
            .backgroundColor(this.BG_COLORS[this.currentBgIndex].color)
            .objectFit(ImageFit.Cover)
            .border({ width: 2, color: Color.Gray })
        }
      }
      .margin({ bottom: 16 })

      Text(`当前背景色: ${this.BG_COLORS[this.currentBgIndex].label}`)
        .fontSize(14)
        .fontColor(Color.Gray)
        .margin({ bottom: 8 })

      Grid() {
        ForEach(this.BG_COLORS, (config: { color: ResourceColor; label: string }, index: number) => {
          GridItem() {
            Column() {
              Column()
                .width(30)
                .height(30)
                .backgroundColor(config.color)
                .borderRadius(4)
                .border({ width: 1, color: Color.Gray })

              Text(config.label)
                .fontSize(10)
                .margin({ top: 4 })
                .fontColor(index === this.currentBgIndex ? Color.Blue : Color.Gray)
            }
            .padding(8)
            .backgroundColor(index === this.currentBgIndex ? '#E3F2FD' : '#FAFAFA')
            .borderRadius(4)
            .onClick(() => {
              this.currentBgIndex = index
            })
          }
        })
      }
      .columnsTemplate('repeat(5, 1fr)')
      .rowsGap(8)
      .columnsGap(8)
      .padding(16)
    }
    .width('100%')
    .height('100%')
    .padding(16)
  }
}

/** 原 044：宽高比和比例约束 */
@Component
struct ImageAspectRatioTestCase044 {
  @State currentRatioIndex: number = 0

  private readonly RATIO_CONFIGS: Array<{ ratio: number | undefined; label: string }> = [
    { ratio: undefined, label: '不约束' },
    { ratio: 1, label: '1:1 正方形' },
    { ratio: 1.5, label: '3:2 横向' },
    { ratio: 0.667, label: '2:3 纵向' },
    { ratio: 1.778, label: '16:9 宽屏' },
    { ratio: 0.5625, label: '9:16 竖屏' },
    { ratio: 1.333, label: '4:3 标准' },
    { ratio: 0.75, label: '3:4 反向' },
    { ratio: 2, label: '2:1 超宽' },
    { ratio: 0.5, label: '1:2 超高' }
  ]

  build() {
    Column() {
      Text('Image aspectRatio属性测试')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 16 })

      Row() {
        Column() {
          Text('有aspectRatio约束')
            .fontSize(14)
            .margin({ bottom: 8 })
          Image($r('app.media.startIcon'))
            .width(200)
            .aspectRatio(this.RATIO_CONFIGS[this.currentRatioIndex].ratio)
            .objectFit(ImageFit.Cover)
            .border({ width: 2, color: Color.Blue })
            .borderRadius(8)
        }
        .margin({ right: 16 })

        Column() {
          Text('无约束(原始)')
            .fontSize(14)
            .margin({ bottom: 8 })
          Image($r('app.media.startIcon'))
            .width(200)
            .height(150)
            .objectFit(ImageFit.Cover)
            .border({ width: 1, color: Color.Gray })
            .borderRadius(8)
        }
      }
      .margin({ bottom: 16 })

      Text(`当前比例: ${this.RATIO_CONFIGS[this.currentRatioIndex].label} ` +
        `(ratio=${this.RATIO_CONFIGS[this.currentRatioIndex].ratio})`)
        .fontSize(14)
        .fontColor(Color.Gray)
        .margin({ bottom: 8 })

      Grid() {
        ForEach(this.RATIO_CONFIGS, (config: { ratio: number | undefined; label: string }, index: number) => {
          GridItem() {
            Column() {
              Text(config.label)
                .fontSize(11)
                .fontColor(index === this.currentRatioIndex ? Color.Blue : Color.Gray)
            }
            .padding(8)
            .backgroundColor(index === this.currentRatioIndex ? '#E3F2FD' : '#FAFAFA')
            .borderRadius(4)
            .onClick(() => {
              this.currentRatioIndex = index
            })
          }
        })
      }
      .columnsTemplate('repeat(5, 1fr)')
      .rowsGap(8)
      .columnsGap(8)
      .padding(16)
    }
    .width('100%')
    .height('100%')
    .padding(16)
  }
}

@Entry
@Component
struct ImageTestcaseStyleLayout {
  @State currentIndex: number = 0

  build() {
    Column() {
      Tabs({ barPosition: BarPosition.Start, index: this.currentIndex }) {
        TabContent() { ImageComprehensiveTestCase035() }
          .tabBar('综合属性')
        TabContent() { ImageOverlayTestCase036() }
          .tabBar('overlay')
        TabContent() { ImageBorderStyleTestCase039() }
          .tabBar('边框样式')
        TabContent() { ImageMarginPaddingTestCase040() }
          .tabBar('margin/padding')
        TabContent() { ImageBackgroundColorTestCase041() }
          .tabBar('背景色')
        TabContent() { ImageAspectRatioTestCase044() }
          .tabBar('宽高比')
      }
      .barMode(BarMode.Scrollable)
      .scrollable(true)
      .onChange((index: number) => { this.currentIndex = index })
    }
    .width('100%')
    .height('100%')
  }
}
