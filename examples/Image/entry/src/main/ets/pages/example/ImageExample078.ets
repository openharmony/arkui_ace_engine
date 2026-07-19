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
 * ImageExample078 - 图片视觉效果综合示例
 *
 * 功能说明：
 * 1. 演示 Image 组件与通用视觉效果属性的配合使用
 * 2. 通过 borderRadius、border、shadow 构建基础视觉风格
 * 3. 通过 blur、brightness、contrast、grayscale、saturate 等图像效果属性增强表现力
 * 4. 通过 opacity、scale、rotate、translate 等通用变换属性增强交互反馈
 *
 * 适用场景：
 * - 列表卡片配图
 * - 头像、缩略图、海报展示
 * - 视觉特效演示
 */

@Entry
@Component
struct ImageExample078 {
  @State currentRadius: number = 16
  @State currentBlur: number = 0
  @State currentBrightness: number = 1.0
  @State currentContrast: number = 1.0
  @State currentGrayscale: number = 0
  @State currentSaturate: number = 1.0
  @State currentScale: number = 1.0
  @State currentRotate: number = 0
  @State currentOpacity: number = 1.0
  @State imageIndex: number = 0

  private images: Resource[] = [
    $r('app.media.startIcon'),
    $r('app.media.foreground'),
    $r('app.media.background')
  ]

  build() {
    Scroll() {
      Column({ space: 16 }) {
        Text('图片视觉效果综合示例')
          .fontSize(22)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 8 })
          .fontColor(0x222222)

        this.buildPreviewCard()
        this.buildStyleControls()
        this.buildEffectControls()
        this.buildTransformControls()
        this.buildPresetGallery()
        this.buildUseCaseGallery()
        this.buildPropertyTable()
        this.buildResetButton()
      }
      .width('100%')
      .padding({ left: 16, right: 16, bottom: 24 })
    }
    .width('100%')
    .height('100%')
    .backgroundColor(0xF5F5F5)
  }

  @Builder
  buildPreviewCard() {
    Column({ space: 8 }) {
      Text('实时预览')
        .fontSize(16)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x333333)
        .alignSelf(ItemAlign.Start)

      Stack() {
        Image(this.images[this.imageIndex])
          .width(240)
          .height(240)
          .objectFit(ImageFit.Cover)
          .borderRadius(this.currentRadius)
          .border({ width: 2, color: 0x3388CCFF })
          .shadow({ radius: 16, color: 0x33000000, offsetX: 0, offsetY: 6 })
          .blur(this.currentBlur)
          .brightness(this.currentBrightness)
          .contrast(this.currentContrast)
          .grayscale(this.currentGrayscale)
          .saturate(this.currentSaturate)
          .opacity(this.currentOpacity)
          .scale({ x: this.currentScale, y: this.currentScale })
          .rotate({ angle: this.currentRotate })

        Text(`${this.currentScale.toFixed(2)}x | ${this.currentRotate.toFixed(0)}°`)
          .fontSize(12)
          .fontColor(Color.White)
          .padding({ left: 8, right: 8, top: 4, bottom: 4 })
          .backgroundColor('rgba(0,0,0,0.5)')
          .borderRadius(10)
          .position({ x: 8, y: 8 })
      }
      .width(260)
      .height(260)
      .alignContent(Alignment.Center)
    }
    .width('100%')
    .padding(16)
    .backgroundColor(0xFFFFFF)
    .borderRadius(12)
  }

  @Builder
  buildStyleControls() {
    Column({ space: 12 }) {
      Text('基础样式')
        .fontSize(16)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x333333)
        .alignSelf(ItemAlign.Start)

      Row({ space: 8 }) {
        Text('圆角')
          .fontSize(13)
          .fontColor(0x666666)
          .width(60)
        Slider(value: this.currentRadius, min: 0, max: 120, step: 2)
          .layoutWeight(1)
          .onChange((value: number) => {
            this.currentRadius = value
          })
        Text(`${this.currentRadius.toFixed(0)} vp`)
          .fontSize(12)
          .fontColor(0x666666)
          .width(64)
          .textAlign(TextAlign.End)
      }

      Row({ space: 8 }) {
        Button('切换图片')
          .layoutWeight(1)
          .fontSize(13)
          .onClick(() => {
            this.imageIndex = (this.imageIndex + 1) % this.images.length
          })
        Button('直角')
          .layoutWeight(1)
          .fontSize(13)
          .onClick(() => {
            this.currentRadius = 0
          })
        Button('圆形')
          .layoutWeight(1)
          .fontSize(13)
          .onClick(() => {
            this.currentRadius = 120
          })
      }
    }
    .width('100%')
    .padding(16)
    .backgroundColor(0xFFFFFF)
    .borderRadius(12)
  }

  @Builder
  buildEffectControls() {
    Column({ space: 10 }) {
      Text('图像效果')
        .fontSize(16)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x333333)
        .alignSelf(ItemAlign.Start)

      this.buildEffectSlider('模糊', this.currentBlur, 0, 30, 1,
        (v: number) => this.currentBlur = v, (v: number) => `${v.toFixed(0)} vp`)
      this.buildEffectSlider('亮度', this.currentBrightness, 0.3, 2.0, 0.05,
        (v: number) => this.currentBrightness = v, (v: number) => v.toFixed(2))
      this.buildEffectSlider('对比度', this.currentContrast, 0.3, 2.0, 0.05,
        (v: number) => this.currentContrast = v, (v: number) => v.toFixed(2))
      this.buildEffectSlider('灰度', this.currentGrayscale, 0, 1, 0.05,
        (v: number) => this.currentGrayscale = v, (v: number) => v.toFixed(2))
      this.buildEffectSlider('饱和度', this.currentSaturate, 0, 2, 0.05,
        (v: number) => this.currentSaturate = v, (v: number) => v.toFixed(2))
    }
    .width('100%')
    .padding(16)
    .backgroundColor(0xFFFFFF)
    .borderRadius(12)
  }

  @Builder
  buildEffectSlider(label: string, value: number, min: number, max: number, step: number,
    onChange: (v: number) => void, format: (v: number) => string) {
    Row({ space: 8 }) {
      Text(label)
        .fontSize(13)
        .fontColor(0x666666)
        .width(56)
      Slider(value: value, min: min, max: max, step: step)
        .layoutWeight(1)
        .onChange((v: number) => onChange(v))
      Text(format(value))
        .fontSize(12)
        .fontColor(0x666666)
        .width(64)
        .textAlign(TextAlign.End)
    }
  }

  @Builder
  buildTransformControls() {
    Column({ space: 10 }) {
      Text('通用变换')
        .fontSize(16)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x333333)
        .alignSelf(ItemAlign.Start)

      this.buildEffectSlider('缩放', this.currentScale, 0.5, 1.8, 0.05,
        (v: number) => this.currentScale = v, (v: number) => `${v.toFixed(2)}x`)
      this.buildEffectSlider('旋转', this.currentRotate, -180, 180, 5,
        (v: number) => this.currentRotate = v, (v: number) => `${v.toFixed(0)}°`)
      this.buildEffectSlider('透明度', this.currentOpacity, 0, 1, 0.05,
        (v: number) => this.currentOpacity = v, (v: number) => v.toFixed(2))
    }
    .width('100%')
    .padding(16)
    .backgroundColor(0xFFFFFF)
    .borderRadius(12)
  }

  @Builder
  buildPresetGallery() {
    Column({ space: 12 }) {
      Text('预设效果画廊')
        .fontSize(16)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x333333)
        .alignSelf(ItemAlign.Start)

      Text('点击预设可快速套用到上方预览图')
        .fontSize(12)
        .fontColor(0x888888)
        .alignSelf(ItemAlign.Start)

      Grid() {
        GridItem() {
          this.buildPresetItem('原图', 0, 1.0, 1.0, 0, 1.0, 0)
        }
        GridItem() {
          this.buildPresetItem('高亮', 0, 1.4, 1.1, 0, 1.2, 0)
        }
        GridItem() {
          this.buildPresetItem('怀旧', 2, 1.05, 0.9, 0.6, 0.7, 0)
        }
        GridItem() {
          this.buildPresetItem('黑白', 0, 1.1, 1.2, 1.0, 0, 0)
        }
        GridItem() {
          this.buildPresetItem('柔和', 4, 1.1, 0.95, 0.2, 0.85, 0)
        }
        GridItem() {
          this.buildPresetItem('鲜艳', 0, 1.05, 1.15, 0, 1.6, 0)
        }
        GridItem() {
          this.buildPresetItem('虚化', 10, 1.05, 1.0, 0, 1.0, 0)
        }
        GridItem() {
          this.buildPresetItem('复古', 1, 1.05, 0.95, 0.4, 0.6, 0)
        }
        GridItem() {
          this.buildPresetItem('旋转', 0, 1.0, 1.0, 0, 1.0, 15)
        }
      }
      .columnsTemplate('1fr 1fr 1fr')
      .rowsGap(12)
      .columnsGap(12)
      .height(420)
    }
    .width('100%')
    .padding(16)
    .backgroundColor(0xFFFFFF)
    .borderRadius(12)
  }

  @Builder
  buildPresetItem(label: string, blur: number, brightness: number, contrast: number,
    grayscale: number, saturate: number, rotate: number) {
    Column({ space: 6 }) {
      Image(this.images[this.imageIndex])
        .width(96)
        .height(96)
        .objectFit(ImageFit.Cover)
        .borderRadius(10)
        .blur(blur)
        .brightness(brightness)
        .contrast(contrast)
        .grayscale(grayscale)
        .saturate(saturate)
        .rotate({ angle: rotate })
        .border({ width: 1, color: 0x22888888 })
      Text(label)
        .fontSize(12)
        .fontColor(0x333333)
    }
    .width('100%')
    .padding({ top: 6, bottom: 6 })
    .backgroundColor(0xF8F8F8)
    .borderRadius(10)
    .onClick(() => {
      animateTo({ duration: 240, curve: Curve.EaseOut }, () => {
        this.currentBlur = blur;
        this.currentBrightness = brightness;
        this.currentContrast = contrast;
        this.currentGrayscale = grayscale;
        this.currentSaturate = saturate;
        this.currentRotate = rotate;
      });
    })
  }

  @Builder
  buildResetButton() {
    Column({ space: 12 }) {
      Button('重置所有效果')
        .width('100%')
        .fontSize(14)
        .backgroundColor(0xFF7070)
        .onClick(() => {
          animateTo({ duration: 240, curve: Curve.EaseOut }, () => {
            this.currentRadius = 16
            this.currentBlur = 0
            this.currentBrightness = 1.0
            this.currentContrast = 1.0
            this.currentGrayscale = 0
            this.currentSaturate = 1.0
            this.currentScale = 1.0
            this.currentRotate = 0
            this.currentOpacity = 1.0
          })
        })

      this.buildTipsCard()
    }
  }

  @Builder
  buildTipsCard() {
    Column({ space: 8 }) {
      Text('使用提示')
        .fontSize(14)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x333333)
        .alignSelf(ItemAlign.Start)
      Text('• blur 可用于背景虚化，建议数值 ≤ 20')
        .fontSize(12)
        .fontColor(0x666666)
        .alignSelf(ItemAlign.Start)
      Text('• brightness/contrast 配合可调节曝光与对比')
        .fontSize(12)
        .fontColor(0x666666)
        .alignSelf(ItemAlign.Start)
      Text('• grayscale = 1 即可得到黑白图，0 ~ 1 渐变')
        .fontSize(12)
        .fontColor(0x666666)
        .alignSelf(ItemAlign.Start)
      Text('• saturate > 1 可提升鲜艳度，< 1 则趋于灰冷')
        .fontSize(12)
        .fontColor(0x666666)
        .alignSelf(ItemAlign.Start)
      Text('• 多种属性可叠加使用，注意性能消耗')
        .fontSize(12)
        .fontColor(0x666666)
        .alignSelf(ItemAlign.Start)
    }
    .width('100%')
    .padding(16)
    .backgroundColor(0xFFFFFF)
    .borderRadius(12)
  }

  @Builder
  buildPropertyTable() {
    Column({ space: 10 }) {
      Text('属性参数说明')
        .fontSize(14)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x333333)
        .alignSelf(ItemAlign.Start)

      this.buildPropertyRow('blur(number)', '0 ~ 70', '应用高斯模糊，数值越大越模糊')
      this.buildPropertyRow('brightness(number)', '推荐 0.5 ~ 2.0', '1.0 为原始亮度，>1 提亮，<1 变暗')
      this.buildPropertyRow('contrast(number)', '推荐 0.5 ~ 2.0', '1.0 为原始对比度，调节图像对比')
      this.buildPropertyRow('grayscale(number)', '0 ~ 1', '0 为彩色，1 为完全黑白')
      this.buildPropertyRow('saturate(number)', '推荐 0 ~ 2', '颜色饱和度，0 为灰度，>1 鲜艳')
      this.buildPropertyRow('invert(number)', '0 ~ 1', '反色效果，0 不反色，1 完全反色')
      this.buildPropertyRow('sepia(number)', '0 ~ 1', '棕褐色滤镜，模拟复古照片效果')
      this.buildPropertyRow('hueRotate(number)', '0 ~ 360', '色相旋转角度')
      this.buildPropertyRow('opacity(number)', '0 ~ 1', '不透明度，影响整体可见度')
      this.buildPropertyRow('scale({x,y})', '推荐 0.5 ~ 2.0', '缩放变换，可制作放大动画')
      this.buildPropertyRow('rotate({angle})', '-360 ~ 360', '旋转，单位为度')
      this.buildPropertyRow('translate({x,y})', 'number', '平移变换，常配合手势使用')
    }
    .width('100%')
    .padding(16)
    .backgroundColor(0xFFFFFF)
    .borderRadius(12)
    .alignItems(HorizontalAlign.Start)
  }

  @Builder
  buildPropertyRow(api: string, range: string, description: string) {
    Row({ space: 10 }) {
      Column({ space: 2 }) {
        Text(api)
          .fontSize(12)
          .fontColor(0x3388FF)
          .fontWeight(FontWeight.Medium)
        Text(`取值：${range}`)
          .fontSize(11)
          .fontColor(0x888888)
      }
      .width(140)
      .alignItems(HorizontalAlign.Start)

      Text(description)
        .fontSize(12)
        .fontColor(0x555555)
        .layoutWeight(1)
    }
    .width('100%')
    .padding({ top: 6, bottom: 6 })
    .border({ width: { bottom: 1 }, color: 0xF0F0F0 })
  }

  @Builder
  buildUseCaseGallery() {
    Column({ space: 12 }) {
      Text('典型用例')
        .fontSize(16)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x333333)
        .alignSelf(ItemAlign.Start)

      Row({ space: 12 }) {
        this.buildUseCaseItem('头像', 60, 60, 30, 0, 1.0, 1.0, 0, 1.0)
        this.buildUseCaseItem('缩略图', 80, 80, 8, 0, 1.0, 1.0, 0, 1.0)
        this.buildUseCaseItem('卡片封面', 100, 70, 8, 0, 1.05, 1.05, 0, 1.15)
        this.buildUseCaseItem('Banner', 110, 60, 0, 0, 1.05, 1.05, 0, 1.1)
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceEvenly)

      Row({ space: 12 }) {
        this.buildUseCaseItem('黑白海报', 80, 100, 8, 0, 1.0, 1.1, 1.0, 0)
        this.buildUseCaseItem('柔焦', 80, 80, 40, 6, 1.0, 1.0, 0, 1.0)
        this.buildUseCaseItem('冷调', 80, 80, 8, 0, 0.9, 1.1, 0, 0.7)
        this.buildUseCaseItem('高光', 80, 80, 8, 0, 1.3, 1.1, 0, 1.3)
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceEvenly)
    }
    .width('100%')
    .padding(16)
    .backgroundColor(0xFFFFFF)
    .borderRadius(12)
  }

  @Builder
  buildUseCaseItem(label: string, w: number, h: number, radius: number,
    blur: number, brightness: number, contrast: number,
    grayscale: number, saturate: number) {
    Column({ space: 4 }) {
      Image(this.images[this.imageIndex])
        .width(w)
        .height(h)
        .objectFit(ImageFit.Cover)
        .borderRadius(radius)
        .blur(blur)
        .brightness(brightness)
        .contrast(contrast)
        .grayscale(grayscale)
        .saturate(saturate)
        .shadow({ radius: 4, color: 0x22000000, offsetX: 0, offsetY: 2 })
      Text(label)
        .fontSize(11)
        .fontColor(0x555555)
    }
    .alignItems(HorizontalAlign.Center)
  }
}
