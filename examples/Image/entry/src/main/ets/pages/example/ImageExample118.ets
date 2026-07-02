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
 * 图片能力综合展示示例 (ImageExample118)
 * 涵盖: 尺寸/填充模式、圆角裁剪、滤镜效果、变换、阴影、
 *      重复平铺、插值、拖拽/复制、同步加载、手势交互、
 *      图库切换、滤镜组合调节、SVG、动画、颜色矩阵等
 */
@Entry
@Component
struct ImageExample118 {
  // ============ 通用状态 ============
  @State currentMediaIndex: number = 0
  @State cardBg: number = 0xFFFFFF
  @State pageBg: number = 0xF5F5F5

  // ============ 1. objectFit 填充模式 ============
  @State fitIndex: number = 0

  // ============ 2. 尺寸与 sourceSize ============
  @State imgWidth: number = 200
  @State imgHeight: number = 200
  @State srcWidth: number = 0
  @State srcHeight: number = 0

  // ============ 3. 圆角与裁剪 ============
  @State radiusValue: number = 0
  @State clipIndex: number = 0

  // ============ 4. 滤镜效果 ============
  @State blurValue: number = 0
  @State brightnessValue: number = 1.0
  @State contrastValue: number = 1.0
  @State saturateValue: number = 1.0
  @State grayscaleValue: number = 0
  @State sepiaValue: number = 0
  @State invertValue: number = 0
  @State opacityValue: number = 1.0

  // ============ 5. 变换 ============
  @State scaleX: number = 1.0
  @State scaleY: number = 1.0
  @State rotateAngle: number = 0
  @State translateX: number = 0
  @State translateY: number = 0

  // ============ 6. 阴影 ============
  @State shadowRadius: number = 0
  @State shadowOffsetY: number = 0
  @State shadowColor: number = 0x33000000

  // ============ 7. 重复平铺 ============
  @State repeatIndex: number = 0

  // ============ 8. 插值/质量 ============
  @State interpIndex: number = 0

  // ============ 9. 颜色滤镜 / 填充 ============
  @State fillColorOn: boolean = false
  @State colorMatrixOn: boolean = false

  // ============ 10. 手势交互 ============
  @State gestureOffsetX: number = 0
  @State gestureOffsetY: number = 0
  @State gestureScale: number = 1.0
  @State gestureRotate: number = 0
  @State gestureBrightness: number = 1.0
  @State isLongPress: boolean = false
  @State gestureLog: string = '等待手势事件...'

  // ============ 11. 图库切换 ============
  @State galleryIndex: number = 0
  @State galleryOpacity: number = 1.0

  // ============ 12. 轮播 ============
  @State carouselIndex: number = 0
  @State autoPlay: boolean = true

  // ============ 13. 动画 ============
  @State animScale: number = 1.0
  @State animRotate: number = 0
  @State animOpacity: number = 1.0
  @State animOffset: number = 0

  // ============ 14. 预设滤镜 ============
  @State presetIndex: number = 0

  // ============ 15. 图库网格 ============
  @State gridSelected: number = 0

  // ============ 16. 图文叠加卡片 ============
  @State cardIndex: number = 0

  // ============ 17. 背景图 ============
  @State bgWidth: number = 100
  @State bgHeight: number = 160

  // ============ 18. 圆角变体 ============
  @State cornerTopLeft: number = 0
  @State cornerTopRight: number = 0
  @State cornerBottomLeft: number = 0
  @State cornerBottomRight: number = 0

  // ============ 19. 遮罩/混合 ============
  @State maskColor: number = 0x66000000
  @State maskText: string = '图片标题'
  @State maskOpacity: number = 40

  // ============ 20. resizable ============
  @State resizableSliceLeft: number = 0
  @State resizableSliceTop: number = 0

  // ============ 私有数据 ============
  private medias: Resource[] = [
    $r('app.media.startIcon'),
    $r('app.media.background'),
    $r('app.media.foreground'),
    $r('app.media.heart'),
    $r('app.media.star'),
    $r('app.media.icon')
  ]

  private mediaNames: string[] = [
    'startIcon', 'background', 'foreground', 'heart', 'star', 'icon'
  ]

  private fits: { name: string, value: ImageFit }[] = [
    { name: 'Cover', value: ImageFit.Cover },
    { name: 'Contain', value: ImageFit.Contain },
    { name: 'Auto', value: ImageFit.Auto },
    { name: 'Fill', value: ImageFit.Fill },
    { name: 'ScaleDown', value: ImageFit.ScaleDown },
    { name: 'None', value: ImageFit.None }
  ]

  private clips: string[] = ['无裁剪', 'Circle', 'Ellipse', 'RoundRectangle']
  private repeats: string[] = ['None', 'X', 'Y', 'XY']
  private interps: string[] = ['Low', 'Medium', 'High' ]

  private carouselTimer: number = -1
  private logs: string[] = []

  // ============ 辅助方法 ============
  pushLog(msg: string) {
    const time = new Date().toLocaleTimeString()
    this.logs.unshift(`[${time}] ${msg}`)
    if (this.logs.length > 6) {
      this.logs.pop()
    }
    this.gestureLog = this.logs.join('\n')
  }

  resetTransform() {
    animateTo({ duration: 300, curve: Curve.EaseOut }, () => {
      this.gestureOffsetX = 0
      this.gestureOffsetY = 0
      this.gestureScale = 1.0
      this.gestureRotate = 0
      this.gestureBrightness = 1.0
      this.isLongPress = false
    })
  }

  getFitValue(): ImageFit {
    return this.fits[this.fitIndex].value
  }

  // ============ 构建区 ============
  build() {
    Scroll() {
      Column({ space: 18 }) {
        this.buildHeader()
        this.buildMediaSwitcher()
        this.buildObjectFitSection()
        this.buildSizeSection()
        this.buildRadiusClipSection()
        this.buildFilterSection()
        this.buildTransformSection()
        this.buildShadowSection()
        this.buildRepeatSection()
        this.buildInterpolationSection()
        this.buildColorFilterSection()
        this.buildDragCopySection()
        this.buildSyncLoadSection()
        this.buildGestureSection()
        this.buildGallerySection()
        this.buildCarouselSection()
        this.buildAnimationSection()
        this.buildSvgSection()
        this.buildPresetFilterGrid()
        this.buildGridGallery()
        this.buildOverlayCard()
        this.buildBackgroundImageSection()
        this.buildRoundedVariants()
        this.buildMaskBlendSection()
        this.buildResizableSection()
        this.buildBorderVariants()
        this.buildNotesSection()
      }
      .width('100%')
      .padding({ left: 18, right: 18, bottom: 30 })
    }
    .width('100%')
    .height('100%')
    .backgroundColor(this.pageBg)
    .scrollBar(BarState.Auto)
  }

  // ---------- 头部 ----------
  @Builder
  buildHeader() {
    Column({ space: 6 }) {
      Text('图片能力综合展示')
        .fontSize(24)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 18 })
      Text('ImageExample118 · 填充/裁剪/滤镜/变换/手势/动画/SVG')
        .fontSize(13)
        .fontColor(0x999999)
    }
    .width('100%')
    .alignItems(HorizontalAlign.Center)
  }

  // ---------- 媒体切换器 ----------
  @Builder
  buildMediaSwitcher() {
    Column({ space: 10 }) {
      Text('当前资源')
        .fontSize(16)
        .fontWeight(FontWeight.Medium)
      Text(`$r('app.media.${this.mediaNames[this.currentMediaIndex]}')`)
        .fontSize(12)
        .fontColor(0x007DFF)
        .fontStyle(FontStyle.Italic)
      Flex({ wrap: FlexWrap.Wrap, justifyContent: FlexAlign.Center }) {
        ForEach(this.mediaNames, (name: string, index: number) => {
          Text(name)
            .fontSize(12)
            .padding(8)
            .margin(4)
            .borderRadius(16)
            .backgroundColor(this.currentMediaIndex === index ? 0x007DFF : 0xE8E8E8)
            .fontColor(this.currentMediaIndex === index ? Color.White : 0x333333)
            .onClick(() => {
              this.currentMediaIndex = index
            })
        })
      }
    }
    .width('100%')
    .padding(14)
    .backgroundColor(this.cardBg)
    .borderRadius(12)
  }

  // ---------- 1. objectFit 填充模式 ----------
  @Builder
  buildObjectFitSection() {
    Column({ space: 10 }) {
      Text('1. objectFit 填充模式')
        .fontSize(17)
        .fontWeight(FontWeight.Bold)
      Text('同一容器内不同填充模式的视觉效果对比')
        .fontSize(12)
        .fontColor(0x999999)

      Flex({ wrap: FlexWrap.Wrap, justifyContent: FlexAlign.Center }) {
        ForEach(this.fits, (item: { name: string, value: ImageFit }, index: number) => {
          Text(item.name)
            .fontSize(12)
            .padding(8)
            .margin(4)
            .borderRadius(16)
            .backgroundColor(this.fitIndex === index ? 0x007DFF : 0xE8E8E8)
            .fontColor(this.fitIndex === index ? Color.White : 0x333333)
            .onClick(() => {
              this.fitIndex = index
            })
        })
      }

      Stack() {
        Image(this.medias[this.currentMediaIndex])
          .width(220)
          .height(160)
          .objectFit(this.getFitValue())
          .backgroundColor(0xF0F0F0)
      }
      .width(240)
      .height(180)
      .backgroundColor(0xF0F0F0)
      .border({ width: 1, color: 0xDDDDDD })
      .borderRadius(8)

      Text(`当前: ImageFit.${this.fits[this.fitIndex].name}`)
        .fontSize(13)
        .fontColor(0x666666)
    }
    .width('100%')
    .padding(14)
    .backgroundColor(this.cardBg)
    .borderRadius(12)
    .alignItems(HorizontalAlign.Start)
  }

  // ---------- 2. 尺寸与 sourceSize ----------
  @Builder
  buildSizeSection() {
    Column({ space: 10 }) {
      Text('2. 尺寸与 sourceSize')
        .fontSize(17)
        .fontWeight(FontWeight.Bold)
      Text('width/height 控制显示尺寸，sourceSize 控制解码尺寸(0 表示不设置)')
        .fontSize(12)
        .fontColor(0x999999)

      Row({ space: 12 }) {
        Image(this.medias[this.currentMediaIndex])
          .width(this.imgWidth)
          .height(this.imgHeight)
          .objectFit(ImageFit.Cover)
          .border({ width: 1, color: 0xCCCCCC })
          .sourceSize({ width: this.srcWidth, height: this.srcHeight})
        Column({ space: 4 }) {
          Text(`宽: ${this.imgWidth}`)
            .fontSize(12)
          Text(`高: ${this.imgHeight}`)
            .fontSize(12)
          Text(`src: ${this.srcWidth}x${this.srcHeight}`)
            .fontSize(12)
            .fontColor(0x007DFF)
        }
        .alignItems(HorizontalAlign.Start)
      }

      Row() {
        Text('宽')
          .width(30)
          .fontSize(13)
        Slider({ value: this.imgWidth, min: 60, max: 280, step: 1 })
          .layoutWeight(1)
          .onChange((v: number) => { this.imgWidth = v })
      }
      Row() {
        Text('高')
          .width(30)
          .fontSize(13)
        Slider({ value: this.imgHeight, min: 60, max: 280, step: 1 })
          .layoutWeight(1)
          .onChange((v: number) => { this.imgHeight = v })
      }
      Row() {
        Text('src宽')
          .width(45)
          .fontSize(13)
        Slider({ value: this.srcWidth, min: 0, max: 300, step: 1 })
          .layoutWeight(1)
          .onChange((v: number) => { this.srcWidth = v })
      }
      Row() {
        Text('src高')
          .width(45)
          .fontSize(13)
        Slider({ value: this.srcHeight, min: 0, max: 300, step: 1 })
          .layoutWeight(1)
          .onChange((v: number) => { this.srcHeight = v })
      }
    }
    .width('100%')
    .padding(14)
    .backgroundColor(this.cardBg)
    .borderRadius(12)
    .alignItems(HorizontalAlign.Start)
  }

  // ---------- 3. 圆角与裁剪 ----------
  @Builder
  buildRadiusClipSection() {
    Column({ space: 10 }) {
      Text('3. 圆角 borderRadius 与 clipShape')
        .fontSize(17)
        .fontWeight(FontWeight.Bold)
      Text('borderRadius 适合矩形圆角，clipShape 支持圆形/椭圆/圆角矩形')
        .fontSize(12)
        .fontColor(0x999999)

      Row() {
        Text('圆角半径')
          .width(70)
          .fontSize(13)
        Slider({ value: this.radiusValue, min: 0, max: 90, step: 1 })
          .layoutWeight(1)
          .onChange((v: number) => { this.radiusValue = v })
        Text(`${this.radiusValue}`)
          .width(36)
          .fontSize(13)
          .textAlign(TextAlign.End)
      }

      Row({ space: 12 }) {
        Image(this.medias[this.currentMediaIndex])
          .width(110)
          .height(110)
          .objectFit(ImageFit.Cover)
          .borderRadius(this.radiusValue)
          .border({ width: 1, color: 0xCCCCCC })
        Image(this.medias[this.currentMediaIndex])
          .width(110)
          .height(110)
          .objectFit(ImageFit.Cover)
          .clipShape(new Circle({ width: 110, height: 110 }))
      }
      .width('100%')
      .justifyContent(FlexAlign.Center)

      Text('clipShape 形状切换:')
        .fontSize(14)
        .fontWeight(FontWeight.Medium)
      Flex({ wrap: FlexWrap.Wrap }) {
        ForEach(this.clips, (name: string, index: number) => {
          Text(name)
            .fontSize(12)
            .padding(8)
            .margin(4)
            .borderRadius(16)
            .backgroundColor(this.clipIndex === index ? 0x007DFF : 0xE8E8E8)
            .fontColor(this.clipIndex === index ? Color.White : 0x333333)
            .onClick(() => { this.clipIndex = index })
        })
      }

      Row() {
        if (this.clipIndex === 0) {
          Image(this.medias[this.currentMediaIndex])
            .width(140)
            .height(140)
            .objectFit(ImageFit.Cover)
            .border({ width: 1, color: 0xCCCCCC })
        }
        if (this.clipIndex === 1) {
          Image(this.medias[this.currentMediaIndex])
            .width(140)
            .height(140)
            .objectFit(ImageFit.Cover)
            .clipShape(new Circle({ width: 140, height: 140 }))
        }
        if (this.clipIndex === 2) {
          Image(this.medias[this.currentMediaIndex])
            .width(160)
            .height(110)
            .objectFit(ImageFit.Cover)
            .clipShape(new Ellipse({ width: 160, height: 110 }))
        }
        if (this.clipIndex === 3) {
          Image(this.medias[this.currentMediaIndex])
            .width(140)
            .height(140)
            .objectFit(ImageFit.Cover)
            .clipShape(new RoundRectangle({ width: 140, height: 140, radius: [30, 10, 30, 10] }))
        }
      }
      .width('100%')
      .justifyContent(FlexAlign.Center)
    }
    .width('100%')
    .padding(14)
    .backgroundColor(this.cardBg)
    .borderRadius(12)
    .alignItems(HorizontalAlign.Start)
  }

  // ---------- 4. 滤镜效果 ----------
  @Builder
  buildFilterSection() {
    Column({ space: 10 }) {
      Text('4. 滤镜效果')
        .fontSize(17)
        .fontWeight(FontWeight.Bold)
      Text('blur / brightness / contrast / saturate / grayscale / sepia / invert / opacity')
        .fontSize(12)
        .fontColor(0x999999)

      Row({ space: 14 }) {
        Image(this.medias[this.currentMediaIndex])
          .width(130)
          .height(130)
          .objectFit(ImageFit.Cover)
          .borderRadius(10)
          .blur(this.blurValue)
          .brightness(this.brightnessValue)
          .contrast(this.contrastValue)
          .saturate(this.saturateValue)
          .grayscale(this.grayscaleValue)
          .sepia(this.sepiaValue)
          .invert(this.invertValue)
          .opacity(this.opacityValue)
        Column({ space: 6 }) {
          this.filterSlider('模糊', this.blurValue, 0, 40, (v: number) => { this.blurValue = v })
          this.filterSlider('亮度', this.brightnessValue, 0, 2, (v: number) => { this.brightnessValue = v })
          this.filterSlider('对比', this.contrastValue, 0, 2, (v: number) => { this.contrastValue = v })
        }
      }
      Column({ space: 6 }) {
        this.filterSlider('饱和度', this.saturateValue, 0, 2, (v: number) => { this.saturateValue = v })
        this.filterSlider('灰度', this.grayscaleValue, 0, 1, (v: number) => { this.grayscaleValue = v })
        this.filterSlider('复古', this.sepiaValue, 0, 1, (v: number) => { this.sepiaValue = v })
        this.filterSlider('反色', this.invertValue, 0, 1, (v: number) => { this.invertValue = v })
        this.filterSlider('透明', this.opacityValue, 0, 1, (v: number) => { this.opacityValue = v })
      }

      Row({ space: 10 }) {
        Button('重置滤镜')
          .fontSize(12)
          .backgroundColor(0x007DFF)
          .onClick(() => {
            this.blurValue = 0
            this.brightnessValue = 1.0
            this.contrastValue = 1.0
            this.saturateValue = 1.0
            this.grayscaleValue = 0
            this.sepiaValue = 0
            this.invertValue = 0
            this.opacityValue = 1.0
          })
        Button('黑白')
          .fontSize(12)
          .backgroundColor(0x666666)
          .onClick(() => { this.grayscaleValue = 1.0 })
        Button('高对比')
          .fontSize(12)
          .backgroundColor(0x666666)
          .onClick(() => { this.contrastValue = 1.6; this.saturateValue = 1.4 })
        Button('柔焦')
          .fontSize(12)
          .backgroundColor(0x666666)
          .onClick(() => { this.blurValue = 4; this.brightnessValue = 1.1 })
      }
    }
    .width('100%')
    .padding(14)
    .backgroundColor(this.cardBg)
    .borderRadius(12)
    .alignItems(HorizontalAlign.Start)
  }

  @Builder
  filterSlider(label: string, value: number, min: number, max: number, onChange: (v: number) => void) {
    Row() {
      Text(label)
        .width(46)
        .fontSize(12)
      Slider({ value: value, min: min, max: max, step: 0.05 })
        .layoutWeight(1)
        .onChange((v: number) => { onChange(v) })
      Text(`${value.toFixed(2)}`)
        .width(42)
        .fontSize(11)
        .textAlign(TextAlign.End)
        .fontColor(0x666666)
    }
  }

  // ---------- 5. 变换 ----------
  @Builder
  buildTransformSection() {
    Column({ space: 10 }) {
      Text('5. 几何变换 scale / rotate / translate')
        .fontSize(17)
        .fontWeight(FontWeight.Bold)
      Text('实时调节缩放、旋转与平移参数')
        .fontSize(12)
        .fontColor(0x999999)

      Stack() {
        Image(this.medias[this.currentMediaIndex])
          .width(130)
          .height(130)
          .objectFit(ImageFit.Cover)
          .borderRadius(10)
          .scale({ x: this.scaleX, y: this.scaleY })
          .rotate({ angle: this.rotateAngle })
          .translate({ x: this.translateX, y: this.translateY })
      }
      .width('100%')
      .height(180)

      this.filterSlider('scaleX', this.scaleX, -2, 2, (v: number) => { this.scaleX = v })
      this.filterSlider('scaleY', this.scaleY, -2, 2, (v: number) => { this.scaleY = v })
      Row() {
        Text('旋转')
          .width(46)
          .fontSize(12)
        Slider({ value: this.rotateAngle, min: 0, max: 360, step: 1 })
          .layoutWeight(1)
          .onChange((v: number) => { this.rotateAngle = v })
        Text(`${this.rotateAngle.toFixed(0)}°`)
          .width(42)
          .fontSize(11)
          .textAlign(TextAlign.End)
          .fontColor(0x666666)
      }
      Row() {
        Text('平移X')
          .width(46)
          .fontSize(12)
        Slider({ value: this.translateX, min: -100, max: 100, step: 1 })
          .layoutWeight(1)
          .onChange((v: number) => { this.translateX = v })
        Text(`${this.translateX.toFixed(0)}`)
          .width(42)
          .fontSize(11)
          .textAlign(TextAlign.End)
          .fontColor(0x666666)
      }
      Row() {
        Text('平移Y')
          .width(46)
          .fontSize(12)
        Slider({ value: this.translateY, min: -100, max: 100, step: 1 })
          .layoutWeight(1)
          .onChange((v: number) => { this.translateY = v })
        Text(`${this.translateY.toFixed(0)}`)
          .width(42)
          .fontSize(11)
          .textAlign(TextAlign.End)
          .fontColor(0x666666)
      }

      Row({ space: 8 }) {
        Button('重置')
          .fontSize(12)
          .backgroundColor(0x007DFF)
          .onClick(() => {
            this.scaleX = 1.0
            this.scaleY = 1.0
            this.rotateAngle = 0
            this.translateX = 0
            this.translateY = 0
          })
        Button('镜像翻转')
          .fontSize(12)
          .backgroundColor(0x666666)
          .onClick(() => { this.scaleX *= -1 })
      }
    }
    .width('100%')
    .padding(14)
    .backgroundColor(this.cardBg)
    .borderRadius(12)
    .alignItems(HorizontalAlign.Start)
  }

  // ---------- 6. 阴影 ----------
  @Builder
  buildShadowSection() {
    Column({ space: 10 }) {
      Text('6. 阴影 shadow')
        .fontSize(17)
        .fontWeight(FontWeight.Bold)
      Text('调节阴影模糊半径与偏移量')
        .fontSize(12)
        .fontColor(0x999999)

      Image(this.medias[this.currentMediaIndex])
        .width(140)
        .height(140)
        .objectFit(ImageFit.Cover)
        .borderRadius(12)
        .shadow({ radius: this.shadowRadius, color: this.shadowColor, offsetX: 0, offsetY: this.shadowOffsetY })

      Row() {
        Text('半径')
          .width(46)
          .fontSize(12)
        Slider({ value: this.shadowRadius, min: 0, max: 50, step: 1 })
          .layoutWeight(1)
          .onChange((v: number) => { this.shadowRadius = v })
        Text(`${this.shadowRadius.toFixed(0)}`)
          .width(42)
          .fontSize(11)
          .textAlign(TextAlign.End)
      }
      Row() {
        Text('偏移Y')
          .width(46)
          .fontSize(12)
        Slider({ value: this.shadowOffsetY, min: -20, max: 30, step: 1 })
          .layoutWeight(1)
          .onChange((v: number) => { this.shadowOffsetY = v })
        Text(`${this.shadowOffsetY.toFixed(0)}`)
          .width(42)
          .fontSize(11)
          .textAlign(TextAlign.End)
      }
      Row({ space: 8 }) {
        Button('浅阴影')
          .fontSize(12)
          .backgroundColor(0x666666)
          .onClick(() => { this.shadowColor = 0x22000000; this.shadowRadius = 20; this.shadowOffsetY = 8 })
        Button('彩色阴影')
          .fontSize(12)
          .backgroundColor(0x666666)
          .onClick(() => { this.shadowColor = 0x66007DFF; this.shadowRadius = 30; this.shadowOffsetY = 6 })
        Button('清除')
          .fontSize(12)
          .backgroundColor(0x666666)
          .onClick(() => { this.shadowRadius = 0; this.shadowOffsetY = 0 })
      }
    }
    .width('100%')
    .padding(14)
    .backgroundColor(this.cardBg)
    .borderRadius(12)
    .alignItems(HorizontalAlign.Start)
  }

  // ---------- 7. 重复平铺 ----------
  @Builder
  buildRepeatSection() {
    Column({ space: 10 }) {
      Text('7. 重复平铺 objectRepeat')
        .fontSize(17)
        .fontWeight(FontWeight.Bold)
      Text('将图片作为纹理在容器内重复平铺')
        .fontSize(12)
        .fontColor(0x999999)

      Flex({ wrap: FlexWrap.Wrap, justifyContent: FlexAlign.Center }) {
        ForEach(this.repeats, (name: string, index: number) => {
          Text(name)
            .fontSize(12)
            .padding(8)
            .margin(4)
            .borderRadius(16)
            .backgroundColor(this.repeatIndex === index ? 0x007DFF : 0xE8E8E8)
            .fontColor(this.repeatIndex === index ? Color.White : 0x333333)
            .onClick(() => { this.repeatIndex = index })
        })
      }

      Image(this.medias[this.currentMediaIndex])
        .width('100%')
        .height(160)
        .objectFit(ImageFit.Cover)
        .objectRepeat(this.getRepeatValue())
        .border({ width: 1, color: 0xCCCCCC })
        .borderRadius(8)
    }
    .width('100%')
    .padding(14)
    .backgroundColor(this.cardBg)
    .borderRadius(12)
    .alignItems(HorizontalAlign.Start)
  }

  getRepeatValue(): ImageRepeat {
    if (this.repeatIndex === 1) {
      return ImageRepeat.X
    }
    if (this.repeatIndex === 2) {
      return ImageRepeat.Y
    }
    if (this.repeatIndex === 3) {
      return ImageRepeat.XY
    }
    return ImageRepeat.NoRepeat
  }

  // ---------- 8. 插值与质量 ----------
  @Builder
  buildInterpolationSection() {
    Column({ space: 10 }) {
      Text('8. 插值 interpolation')
        .fontSize(17)
        .fontWeight(FontWeight.Bold)
      Text('控制缩放时的插值算法，影响清晰度与性能')
        .fontSize(12)
        .fontColor(0x999999)

      Flex({ wrap: FlexWrap.Wrap }) {
        ForEach(this.interps, (name: string, index: number) => {
          Text(name)
            .fontSize(12)
            .padding(8)
            .margin(4)
            .borderRadius(16)
            .backgroundColor(this.interpIndex === index ? 0x007DFF : 0xE8E8E8)
            .fontColor(this.interpIndex === index ? Color.White : 0x333333)
            .onClick(() => { this.interpIndex = index })
        })
      }

      Image(this.medias[this.currentMediaIndex])
        .width(260)
        .height(160)
        .objectFit(ImageFit.Cover)
        .interpolation(this.getInterpValue())
        .border({ width: 1, color: 0xCCCCCC })
        .borderRadius(8)
    }
    .width('100%')
    .padding(14)
    .backgroundColor(this.cardBg)
    .borderRadius(12)
    .alignItems(HorizontalAlign.Start)
  }

  getInterpValue(): ImageInterpolation {
    if (this.interpIndex === 0) {
      return ImageInterpolation.Low
    }
    if (this.interpIndex === 1) {
      return ImageInterpolation.Medium
    }
    return ImageInterpolation.High
  }

  // ---------- 9. 颜色滤镜 / 填充 ----------
  @Builder
  buildColorFilterSection() {
    Column({ space: 10 }) {
      Text('9. fillColor 与 colorFilter')
        .fontSize(17)
        .fontWeight(FontWeight.Bold)
      Text('fillColor 着色(适合图标/单色图)，colorMatrix 自定义颜色矩阵')
        .fontSize(12)
        .fontColor(0x999999)

      Row({ space: 16 }) {
        Column({ space: 6 }) {
          if (this.fillColorOn) {
            Image(this.medias[this.currentMediaIndex])
              .width(90)
              .height(90)
              .objectFit(ImageFit.Cover)
              .fillColor(0xFF007DFF)
          } else {
            Image(this.medias[this.currentMediaIndex])
              .width(90)
              .height(90)
              .objectFit(ImageFit.Cover)
          }
          Text('fillColor')
            .fontSize(11)
            .fontColor(0x999999)
        }
        Column({ space: 6 }) {
          if (this.colorMatrixOn) {
            Image(this.medias[this.currentMediaIndex])
              .width(90)
              .height(90)
              .objectFit(ImageFit.Cover)
              .colorFilter([1.5, 0, 0, 0, 0,
                0, 1.2, 0, 0, 0,
                0, 0, 0.8, 0, 0,
                0, 0, 0, 1, 0])
          } else {
            Image(this.medias[this.currentMediaIndex])
              .width(90)
              .height(90)
              .objectFit(ImageFit.Cover)
          }
          Text('colorFilter')
            .fontSize(11)
            .fontColor(0x999999)
        }
      }
      .width('100%')
      .justifyContent(FlexAlign.Center)

      Row({ space: 10 }) {
        Toggle({ type: ToggleType.Switch, isOn: this.fillColorOn })
          .onChange((on: boolean) => { this.fillColorOn = on })
        Text('启用 fillColor (蓝色着色)')
          .fontSize(13)
      }
      Row({ space: 10 }) {
        Toggle({ type: ToggleType.Switch, isOn: this.colorMatrixOn })
          .onChange((on: boolean) => { this.colorMatrixOn = on })
        Text('启用 colorFilter (增强红/绿通道)')
          .fontSize(13)
      }
    }
    .width('100%')
    .padding(14)
    .backgroundColor(this.cardBg)
    .borderRadius(12)
    .alignItems(HorizontalAlign.Start)
  }

  // ---------- 10. 拖拽与复制 ----------
  @Builder
  buildDragCopySection() {
    Column({ space: 10 }) {
      Text('10. draggable 与 copyOption')
        .fontSize(17)
        .fontWeight(FontWeight.Bold)
      Text('draggable 控制可拖拽，copyOption 控制长按可复制')
        .fontSize(12)
        .fontColor(0x999999)

      Row({ space: 16 }) {
        Column({ space: 6 }) {
          Image(this.medias[this.currentMediaIndex])
            .width(100)
            .height(100)
            .objectFit(ImageFit.Cover)
            .draggable(true)
            .border({ width: 1, color: 0xCCCCCC })
            .borderRadius(8)
          Text('draggable=true')
            .fontSize(11)
            .fontColor(0x999999)
        }
        Column({ space: 6 }) {
          Image(this.medias[this.currentMediaIndex])
            .width(100)
            .height(100)
            .objectFit(ImageFit.Cover)
            .copyOption(CopyOptions.LocalDevice)
            .border({ width: 1, color: 0xCCCCCC })
            .borderRadius(8)
          Text('copyOption=Local')
            .fontSize(11)
            .fontColor(0x999999)
        }
      }
      .width('100%')
      .justifyContent(FlexAlign.Center)

      Text('提示: 长按第二张图片可复制到剪贴板; 第一张图片可拖拽(部分环境支持)。')
        .fontSize(11)
        .fontColor(0x666666)
    }
    .width('100%')
    .padding(14)
    .backgroundColor(this.cardBg)
    .borderRadius(12)
    .alignItems(HorizontalAlign.Start)
  }

  // ---------- 11. 同步加载 ----------
  @Builder
  buildSyncLoadSection() {
    Column({ space: 10 }) {
      Text('11. syncLoad 同步加载')
        .fontSize(17)
        .fontWeight(FontWeight.Bold)
      Text('syncLoad=true 在构建时同步加载, 避免首帧闪烁(适合小图/图标)')
        .fontSize(12)
        .fontColor(0x999999)

      Row({ space: 16 }) {
        Column({ space: 6 }) {
          Image(this.medias[this.currentMediaIndex])
            .width(100)
            .height(100)
            .objectFit(ImageFit.Cover)
            .syncLoad(true)
            .borderRadius(8)
          Text('syncLoad=true')
            .fontSize(11)
            .fontColor(0x999999)
        }
        Column({ space: 6 }) {
          Image(this.medias[this.currentMediaIndex])
            .width(100)
            .height(100)
            .objectFit(ImageFit.Cover)
            .syncLoad(false)
            .borderRadius(8)
          Text('syncLoad=false')
            .fontSize(11)
            .fontColor(0x999999)
        }
      }
      .width('100%')
      .justifyContent(FlexAlign.Center)
    }
    .width('100%')
    .padding(14)
    .backgroundColor(this.cardBg)
    .borderRadius(12)
    .alignItems(HorizontalAlign.Start)
  }

  // ---------- 12. 手势交互 ----------
  @Builder
  buildGestureSection() {
    Column({ space: 10 }) {
      Text('12. 手势交互综合')
        .fontSize(17)
        .fontWeight(FontWeight.Bold)
      Text('双击缩放 · 长按高亮 · 单指拖动 · 双指缩放 · 双指旋转')
        .fontSize(12)
        .fontColor(0x999999)

      Stack() {
        Image(this.medias[this.currentMediaIndex])
          .width(240)
          .height(240)
          .objectFit(ImageFit.Cover)
          .borderRadius(12)
          .offset({ x: this.gestureOffsetX, y: this.gestureOffsetY })
          .scale({ x: this.gestureScale, y: this.gestureScale })
          .rotate({ angle: this.gestureRotate })
          .brightness(this.gestureBrightness)
          .border({ width: this.isLongPress ? 3 : 0, color: 0xFFD700 })
          .shadow({ radius: 10, color: 0x33000000, offsetX: 0, offsetY: 4 })
          .gesture(
            GestureGroup(GestureMode.Exclusive,
              TapGesture({ count: 2 })
                .onAction(() => {
                  animateTo({ duration: 200 }, () => {
                    this.gestureScale = this.gestureScale > 1.2 ? 1.0 : 1.8
                  })
                  this.pushLog('双击: 缩放切换')
                }),
              LongPressGesture({ fingers: 1, repeat: false, duration: 500 })
                .onAction(() => {
                  this.isLongPress = true
                  this.gestureBrightness = 1.35
                  this.pushLog('长按: 高亮')
                })
                .onActionEnd(() => {
                  this.isLongPress = false
                  this.gestureBrightness = 1.0
                }),
              PanGesture({ fingers: 1, distance: 5 })
                .onActionUpdate((e: GestureEvent) => {
                  this.gestureOffsetX = e.offsetX
                  this.gestureOffsetY = e.offsetY
                })
                .onActionEnd(() => {
                  this.pushLog(`拖动: (${this.gestureOffsetX.toFixed(0)},${this.gestureOffsetY.toFixed(0)})`)
                }),
              PinchGesture({ fingers: 2 })
                .onActionUpdate((e: GestureEvent) => {
                  this.gestureScale = Math.max(0.3, Math.min(3.0, e.scale))
                })
                .onActionEnd(() => {
                  this.pushLog(`捏合: ${this.gestureScale.toFixed(2)}x`)
                }),
              RotationGesture({ fingers: 2 })
                .onActionUpdate((e: GestureEvent) => {
                  this.gestureRotate = e.angle
                })
                .onActionEnd(() => {
                  this.pushLog(`旋转: ${this.gestureRotate.toFixed(0)}°`)
                })
            )
          )

        Text(`${this.gestureScale.toFixed(1)}x · ${this.gestureRotate.toFixed(0)}°`)
          .fontSize(12)
          .fontColor(Color.White)
          .padding(4)
          .backgroundColor('rgba(0,0,0,0.6)')
          .borderRadius(4)
          .position({ x: 8, y: 8 })
      }
      .width(260)
      .height(260)
      .alignContent(Alignment.Center)

      Row({ space: 10 }) {
        Button('重置变换')
          .fontSize(12)
          .backgroundColor(0x007DFF)
          .onClick(() => { this.resetTransform(); this.pushLog('重置: 全部变换') })
        Button('放大')
          .fontSize(12)
          .backgroundColor(0x666666)
          .onClick(() => {
            animateTo({ duration: 200 }, () => { this.gestureScale = 1.8 })
          })
        Button('旋转90')
          .fontSize(12)
          .backgroundColor(0x666666)
          .onClick(() => {
            animateTo({ duration: 300 }, () => { this.gestureRotate += 90 })
          })
      }

      Text('手势日志:')
        .fontSize(13)
        .fontWeight(FontWeight.Medium)
      Text(this.gestureLog)
        .fontSize(11)
        .fontColor(0x333333)
        .lineHeight(18)
        .width('100%')
        .padding(8)
        .backgroundColor(0xF0F0F0)
        .borderRadius(6)
    }
    .width('100%')
    .padding(14)
    .backgroundColor(this.cardBg)
    .borderRadius(12)
    .alignItems(HorizontalAlign.Start)
  }

  // ---------- 13. 图库切换 ----------
  @Builder
  buildGallerySection() {
    Column({ space: 10 }) {
      Text('13. 图库切换 (淡入淡出)')
        .fontSize(17)
        .fontWeight(FontWeight.Bold)
      Text('上一张/下一张切换时配合透明度动画')
        .fontSize(12)
        .fontColor(0x999999)

      Image(this.medias[this.galleryIndex])
        .width(240)
        .height(180)
        .objectFit(ImageFit.Cover)
        .borderRadius(12)
        .opacity(this.galleryOpacity)
        .border({ width: 1, color: 0xCCCCCC })

      Text(`第 ${this.galleryIndex + 1} / ${this.medias.length} 张 · ${this.mediaNames[this.galleryIndex]}`)
        .fontSize(12)
        .fontColor(0x666666)

      Row({ space: 10 }) {
        Button('上一张')
          .fontSize(12)
          .backgroundColor(0x007DFF)
          .onClick(() => { this.switchGallery(-1) })
        Button('下一张')
          .fontSize(12)
          .backgroundColor(0x007DFF)
          .onClick(() => { this.switchGallery(1) })
      }
    }
    .width('100%')
    .padding(14)
    .backgroundColor(this.cardBg)
    .borderRadius(12)
    .alignItems(HorizontalAlign.Start)
  }

  switchGallery(step: number) {
    animateTo({ duration: 150, curve: Curve.EaseIn }, () => { this.galleryOpacity = 0 })
    setTimeout(() => {
      this.galleryIndex = (this.galleryIndex + step + this.medias.length) % this.medias.length
      animateTo({ duration: 250, curve: Curve.EaseOut }, () => { this.galleryOpacity = 1 })
    }, 160)
  }

  // ---------- 14. 自动轮播 ----------
  @Builder
  buildCarouselSection() {
    Column({ space: 10 }) {
      Text('14. 自动轮播')
        .fontSize(17)
        .fontWeight(FontWeight.Bold)
      Text('定时切换图片, 可暂停/继续')
        .fontSize(12)
        .fontColor(0x999999)

      Image(this.medias[this.carouselIndex])
        .width('100%')
        .height(180)
        .objectFit(ImageFit.Cover)
        .borderRadius(12)

      Row({ space: 6 }) {
        ForEach(this.mediaNames, (name: string, index: number) => {
          Text('')
            .width(this.carouselIndex === index ? 18 : 8)
            .height(8)
            .borderRadius(4)
            .backgroundColor(this.carouselIndex === index ? 0x007DFF : 0xCCCCCC)
        })
      }

      Row({ space: 10 }) {
        Button(this.autoPlay ? '暂停' : '播放')
          .fontSize(12)
          .backgroundColor(this.autoPlay ? 0xE07000 : 0x007DFF)
          .onClick(() => {
            this.autoPlay = !this.autoPlay
            if (this.autoPlay) {
              this.startCarousel()
            } else {
              this.stopCarousel()
            }
          })
        Button('上一张')
          .fontSize(12)
          .backgroundColor(0x666666)
          .onClick(() => {
            this.carouselIndex = (this.carouselIndex - 1 + this.medias.length) % this.medias.length
          })
        Button('下一张')
          .fontSize(12)
          .backgroundColor(0x666666)
          .onClick(() => {
            this.carouselIndex = (this.carouselIndex + 1) % this.medias.length
          })
      }
    }
    .width('100%')
    .padding(14)
    .backgroundColor(this.cardBg)
    .borderRadius(12)
    .alignItems(HorizontalAlign.Start)
  }

  startCarousel() {
    this.stopCarousel()
    this.carouselTimer = setInterval(() => {
      animateTo({ duration: 300 }, () => {
        this.carouselIndex = (this.carouselIndex + 1) % this.medias.length
      })
    }, 2000)
  }

  stopCarousel() {
    if (this.carouselTimer !== -1) {
      clearInterval(this.carouselTimer)
      this.carouselTimer = -1
    }
  }

  // ---------- 15. 动画 ----------
  @Builder
  buildAnimationSection() {
    Column({ space: 10 }) {
      Text('15. 动画效果')
        .fontSize(17)
        .fontWeight(FontWeight.Bold)
      Text('animateTo 驱动缩放/旋转/透明度/位移动画')
        .fontSize(12)
        .fontColor(0x999999)

      Image(this.medias[this.currentMediaIndex])
        .width(120)
        .height(120)
        .objectFit(ImageFit.Cover)
        .borderRadius(12)
        .scale({ x: this.animScale, y: this.animScale })
        .rotate({ angle: this.animRotate })
        .opacity(this.animOpacity)
        .translate({ x: this.animOffset, y: 0 })

      Row({ space: 8 }) {
        Button('弹出')
          .fontSize(12)
          .backgroundColor(0x007DFF)
          .onClick(() => {
            animateTo({ duration: 400, curve: Curve.EaseOut }, () => {
              this.animScale = 1.4
            })
            setTimeout(() => {
              animateTo({ duration: 300, curve: Curve.EaseIn }, () => { this.animScale = 1.0 })
            }, 420)
          })
        Button('旋转一圈')
          .fontSize(12)
          .backgroundColor(0x666666)
          .onClick(() => {
            animateTo({ duration: 800, curve: Curve.Linear }, () => {
              this.animRotate += 360
            })
          })
        Button('淡出淡入')
          .fontSize(12)
          .backgroundColor(0x666666)
          .onClick(() => {
            animateTo({ duration: 300 }, () => { this.animOpacity = 0 })
            setTimeout(() => {
              animateTo({ duration: 400 }, () => { this.animOpacity = 1 })
            }, 320)
          })
      }
      Row({ space: 8 }) {
        Button('左右晃动')
          .fontSize(12)
          .backgroundColor(0x666666)
          .onClick(() => {
            animateTo({ duration: 150 }, () => { this.animOffset = -20 })
            setTimeout(() => {
              animateTo({ duration: 150 }, () => { this.animOffset = 20 })
            }, 160)
            setTimeout(() => {
              animateTo({ duration: 150 }, () => { this.animOffset = 0 })
            }, 320)
          })
        Button('组合')
          .fontSize(12)
          .backgroundColor(0x666666)
          .onClick(() => {
            animateTo({ duration: 600, curve: Curve.EaseInOut }, () => {
              this.animScale = 1.3
              this.animRotate += 180
            })
            setTimeout(() => {
              animateTo({ duration: 400, curve: Curve.EaseInOut }, () => {
                this.animScale = 1.0
                this.animRotate += 180
              })
            }, 620)
          })
      }
    }
    .width('100%')
    .padding(14)
    .backgroundColor(this.cardBg)
    .borderRadius(12)
    .alignItems(HorizontalAlign.Start)
  }

  // ---------- 16. SVG ----------
  @Builder
  buildSvgSection() {
    Column({ space: 10 }) {
      Text('16. SVG 矢量图')
        .fontSize(17)
        .fontWeight(FontWeight.Bold)
      Text('Image 直接渲染 SVG 矢量资源, 无损缩放')
        .fontSize(12)
        .fontColor(0x999999)

      Row({ space: 16 }) {
        Column({ space: 6 }) {
          Image($r('app.media.heart'))
            .width(80)
            .height(80)
            .objectFit(ImageFit.Contain)
          Text('heart.svg')
            .fontSize(11)
            .fontColor(0x999999)
        }
        Column({ space: 6 }) {
          Image($r('app.media.star'))
            .width(80)
            .height(80)
            .objectFit(ImageFit.Contain)
          Text('star.svg')
            .fontSize(11)
            .fontColor(0x999999)
        }
        Column({ space: 6 }) {
          Image($r('app.media.icon'))
            .width(80)
            .height(80)
            .objectFit(ImageFit.Contain)
          Text('icon.svg')
            .fontSize(11)
            .fontColor(0x999999)
        }
      }
      .width('100%')
      .justifyContent(FlexAlign.Center)

      Row({ space: 10 }) {
        Column({ space: 6 }) {
          Image($r('app.media.heart'))
            .width(60)
            .height(60)
            .objectFit(ImageFit.Contain)
            .fillColor(0xFF4444)
          Text('fillColor 着色')
            .fontSize(11)
            .fontColor(0x999999)
        }
        Column({ space: 6 }) {
          Image($r('app.media.star'))
            .width(60)
            .height(60)
            .objectFit(ImageFit.Contain)
            .fillColor(0xFFAA00)
          Text('fillColor 着色')
            .fontSize(11)
            .fontColor(0x999999)
        }
      }
      .width('100%')
      .justifyContent(FlexAlign.Center)
    }
    .width('100%')
    .padding(14)
    .backgroundColor(this.cardBg)
    .borderRadius(12)
    .alignItems(HorizontalAlign.Start)
  }

  // ---------- 17. 预设滤镜九宫格 ----------
  @Builder
  buildPresetFilterGrid() {
    Column({ space: 10 }) {
      Text('17. 预设滤镜对比')
        .fontSize(17)
        .fontWeight(FontWeight.Bold)
      Text('点击切换预设滤镜, 统一观察效果差异')
        .fontSize(12)
        .fontColor(0x999999)

      Flex({ wrap: FlexWrap.Wrap, justifyContent: FlexAlign.Center }) {
        ForEach(this.presetNames, (name: string, index: number) => {
          Text(name)
            .fontSize(11)
            .padding(7)
            .margin(3)
            .borderRadius(14)
            .backgroundColor(this.presetIndex === index ? 0x007DFF : 0xE8E8E8)
            .fontColor(this.presetIndex === index ? Color.White : 0x333333)
            .onClick(() => { this.presetIndex = index })
        })
      }

      Row({ space: 14 }) {
        Column({ space: 6 }) {
          Image(this.medias[this.currentMediaIndex])
            .width(130)
            .height(130)
            .objectFit(ImageFit.Cover)
            .borderRadius(10)
            .blur(this.getPresetBlur())
            .brightness(this.getPresetBrightness())
            .contrast(this.getPresetContrast())
            .saturate(this.getPresetSaturate())
            .grayscale(this.getPresetGrayscale())
            .sepia(this.getPresetSepia())
          Text('效果')
            .fontSize(11)
            .fontColor(0x007DFF)
        }
        Column({ space: 6 }) {
          Image(this.medias[this.currentMediaIndex])
            .width(130)
            .height(130)
            .objectFit(ImageFit.Cover)
            .borderRadius(10)
          Text('原图')
            .fontSize(11)
            .fontColor(0x999999)
        }
      }
      .width('100%')
      .justifyContent(FlexAlign.Center)

      Text(`当前滤镜: ${this.presetNames[this.presetIndex]} — ${this.presetDescs[this.presetIndex]}`)
        .fontSize(11)
        .fontColor(0x666666)
    }
    .width('100%')
    .padding(14)
    .backgroundColor(this.cardBg)
    .borderRadius(12)
    .alignItems(HorizontalAlign.Start)
  }

  private presetNames: string[] = ['原图', '黑白', '复古', '高饱和', '冷色调', '暖色调', '高对比', '柔焦', '反色']
  private presetDescs: string[] = [
    '不做任何处理', '完全灰度', '棕褐色调', '增强饱和度', '降低红蓝偏冷',
    '增强红绿偏暖', '提升对比与饱和', '轻微模糊提亮', '颜色反转'
  ]

  getPresetBlur(): number {
    return this.presetIndex === 7 ? 4 : 0
  }
  getPresetBrightness(): number {
    if (this.presetIndex === 7) {
      return 1.15
    }
    if (this.presetIndex === 5) {
      return 1.1
    }
    return 1.0
  }
  getPresetContrast(): number {
    if (this.presetIndex === 6) {
      return 1.5
    }
    if (this.presetIndex === 4) {
      return 1.1
    }
    return 1.0
  }
  getPresetSaturate(): number {
    if (this.presetIndex === 3) {
      return 1.8
    }
    if (this.presetIndex === 6) {
      return 1.4
    }
    if (this.presetIndex === 5) {
      return 1.2
    }
    return 1.0
  }
  getPresetGrayscale(): number {
    return this.presetIndex === 1 ? 1.0 : 0
  }
  getPresetSepia(): number {
    return this.presetIndex === 2 ? 0.8 : 0
  }

  // ---------- 18. 图库网格 ----------
  @Builder
  buildGridGallery() {
    Column({ space: 10 }) {
      Text('18. 图库网格')
        .fontSize(17)
        .fontWeight(FontWeight.Bold)
      Text('点击缩略图选中, 高亮当前项')
        .fontSize(12)
        .fontColor(0x999999)

      Grid() {
        ForEach(this.mediaNames, (name: string, index: number) => {
          GridItem() {
            Column({ space: 4 }) {
              Image(this.medias[index])
                .width(72)
                .height(72)
                .objectFit(ImageFit.Cover)
                .borderRadius(8)
                .border({
                  width: this.gridSelected === index ? 3 : 1,
                  color: this.gridSelected === index ? 0x007DFF : 0xDDDDDD
                })
              Text(name)
                .fontSize(10)
                .fontColor(this.gridSelected === index ? 0x007DFF : 0x999999)
            }
            .onClick(() => { this.gridSelected = index })
          }
        })
      }
      .columnsTemplate('1fr 1fr 1fr')
      .columnsGap(12)
      .rowsGap(12)
      .width('100%')
      .height(200)

      Text(`已选中: ${this.mediaNames[this.gridSelected]}`)
        .fontSize(12)
        .fontColor(0x666666)
    }
    .width('100%')
    .padding(14)
    .backgroundColor(this.cardBg)
    .borderRadius(12)
    .alignItems(HorizontalAlign.Start)
  }

  // ---------- 19. 图文叠加卡片 ----------
  @Builder
  buildOverlayCard() {
    Column({ space: 10 }) {
      Text('19. 图文叠加卡片')
        .fontSize(17)
        .fontWeight(FontWeight.Bold)
      Text('Stack 叠加实现图片上的标题/描述/标签布局')
        .fontSize(12)
        .fontColor(0x999999)

      Stack({ alignContent: Alignment.BottomStart }) {
        Image(this.medias[this.cardIndex])
          .width('100%')
          .height(200)
          .objectFit(ImageFit.Cover)
          .borderRadius(12)
        Column({ space: 4 }) {
          Text(`卡片 ${this.cardIndex + 1}: ${this.mediaNames[this.cardIndex]}`)
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
            .fontColor(Color.White)
          Text('这是叠加在图片上的描述文字, 通过半透明渐变背景增强可读性')
            .fontSize(12)
            .fontColor(0xEEEEEE)
        }
        .width('100%')
        .padding(12)
        .linearGradient({
          angle: 0,
          colors: [['rgba(0,0,0,0)', 0.0], ['rgba(0,0,0,0.6)', 1.0]]
        })
      }
      .width('100%')
      .height(200)

      Row({ space: 8 }) {
        Button('切换卡片')
          .fontSize(12)
          .backgroundColor(0x007DFF)
          .onClick(() => {
            this.cardIndex = (this.cardIndex + 1) % this.medias.length
          })
      }
    }
    .width('100%')
    .padding(14)
    .backgroundColor(this.cardBg)
    .borderRadius(12)
    .alignItems(HorizontalAlign.Start)
  }

  // ---------- 20. 背景图 ----------
  @Builder
  buildBackgroundImageSection() {
    Column({ space: 10 }) {
      Text('20. 背景图 backgroundImage')
        .fontSize(17)
        .fontWeight(FontWeight.Bold)
      Text('将图片作为容器背景, 上方放置文字')
        .fontSize(12)
        .fontColor(0x999999)

      Column({ space: 6 }) {
        Text('背景图上的文字内容')
          .fontSize(18)
          .fontWeight(FontWeight.Bold)
          .fontColor(Color.White)
        Text('文字通过容器背景图衬托显示')
          .fontSize(12)
          .fontColor(0xFFFFFF)
      }
      .width('100%')
      .height(this.bgHeight)
      .padding(16)
      .borderRadius(12)
      .alignItems(HorizontalAlign.Center)
      .justifyContent(FlexAlign.Center)
      .backgroundImage(this.medias[this.currentMediaIndex])
      .backgroundImageSize(ImageSize.Cover)

      Row() {
        Text('背景高')
          .width(50)
          .fontSize(12)
        Slider({ value: this.bgHeight, min: 100, max: 260, step: 1 })
          .layoutWeight(1)
          .onChange((v: number) => { this.bgHeight = v })
        Text(`${this.bgHeight}`)
          .width(40)
          .fontSize(11)
          .textAlign(TextAlign.End)
      }
    }
    .width('100%')
    .padding(14)
    .backgroundColor(this.cardBg)
    .borderRadius(12)
    .alignItems(HorizontalAlign.Start)
  }

  // ---------- 21. 圆角变体 ----------
  @Builder
  buildRoundedVariants() {
    Column({ space: 10 }) {
      Text('21. 不对称圆角 RoundRectangle')
        .fontSize(17)
        .fontWeight(FontWeight.Bold)
      Text('分别调节四个角的圆角半径, 实现不规则形状')
        .fontSize(12)
        .fontColor(0x999999)

      Row() {
        Text('左上')
          .width(46)
          .fontSize(12)
        Slider({ value: this.cornerTopLeft, min: 0, max: 60, step: 1 })
          .layoutWeight(1)
          .onChange((v: number) => { this.cornerTopLeft = v })
        Text(`${this.cornerTopLeft}`)
          .width(34)
          .fontSize(11)
          .textAlign(TextAlign.End)
      }
      Row() {
        Text('右上')
          .width(46)
          .fontSize(12)
        Slider({ value: this.cornerTopRight, min: 0, max: 60, step: 1 })
          .layoutWeight(1)
          .onChange((v: number) => { this.cornerTopRight = v })
        Text(`${this.cornerTopRight}`)
          .width(34)
          .fontSize(11)
          .textAlign(TextAlign.End)
      }
      Row() {
        Text('左下')
          .width(46)
          .fontSize(12)
        Slider({ value: this.cornerBottomLeft, min: 0, max: 60, step: 1 })
          .layoutWeight(1)
          .onChange((v: number) => { this.cornerBottomLeft = v })
        Text(`${this.cornerBottomLeft}`)
          .width(34)
          .fontSize(11)
          .textAlign(TextAlign.End)
      }
      Row() {
        Text('右下')
          .width(46)
          .fontSize(12)
        Slider({ value: this.cornerBottomRight, min: 0, max: 60, step: 1 })
          .layoutWeight(1)
          .onChange((v: number) => { this.cornerBottomRight = v })
        Text(`${this.cornerBottomRight}`)
          .width(34)
          .fontSize(11)
          .textAlign(TextAlign.End)
      }

      Image(this.medias[this.currentMediaIndex])
        .width(160)
        .height(160)
        .objectFit(ImageFit.Cover)
        .clipShape(new RoundRectangle({
          width: 160, height: 160,
          radius: [this.cornerTopLeft, this.cornerTopRight, this.cornerBottomLeft, this.cornerBottomRight]
        }))

      Row({ space: 8 }) {
        Button('全圆角')
          .fontSize(12)
          .backgroundColor(0x666666)
          .onClick(() => {
            this.cornerTopLeft = 40
            this.cornerTopRight = 40
            this.cornerBottomLeft = 40
            this.cornerBottomRight = 40
          })
        Button('仅顶部')
          .fontSize(12)
          .backgroundColor(0x666666)
          .onClick(() => {
            this.cornerTopLeft = 40
            this.cornerTopRight = 40
            this.cornerBottomLeft = 0
            this.cornerBottomRight = 0
          })
        Button('重置')
          .fontSize(12)
          .backgroundColor(0x666666)
          .onClick(() => {
            this.cornerTopLeft = 0
            this.cornerTopRight = 0
            this.cornerBottomLeft = 0
            this.cornerBottomRight = 0
          })
      }
    }
    .width('100%')
    .padding(14)
    .backgroundColor(this.cardBg)
    .borderRadius(12)
    .alignItems(HorizontalAlign.Start)
  }

  // ---------- 22. 遮罩与混合 ----------
  @Builder
  buildMaskBlendSection() {
    Column({ space: 10 }) {
      Text('22. 遮罩叠加')
        .fontSize(17)
        .fontWeight(FontWeight.Bold)
      Text('图片上叠加半透明色块, 突出文字标题')
        .fontSize(12)
        .fontColor(0x999999)

      Stack({ alignContent: Alignment.Center }) {
        Image(this.medias[this.currentMediaIndex])
          .width('100%')
          .height(180)
          .objectFit(ImageFit.Cover)
          .borderRadius(12)
        Column() {
          Text(this.maskText)
            .fontSize(22)
            .fontWeight(FontWeight.Bold)
            .fontColor(Color.White)
        }
        .width('100%')
        .height(180)
        .justifyContent(FlexAlign.Center)
        .alignItems(HorizontalAlign.Center)
        .backgroundColor(this.maskColor)
        .borderRadius(12)
      }
      .width('100%')
      .height(180)

      Row() {
        Text('遮罩浓度')
          .width(60)
          .fontSize(12)
        Slider({ value: this.maskOpacity, min: 0, max: 100, step: 1 })
          .layoutWeight(1)
          .onChange((v: number) => {
            this.maskOpacity = v
            const alpha = Math.round(v * 2.55)
            this.maskColor = (alpha << 24) | color
          })
        Text(`${this.maskOpacity}%`)
          .width(50)
          .fontSize(11)
          .textAlign(TextAlign.End)
      }
      Row({ space: 8 }) {
        Button('黑色遮罩')
          .fontSize(12)
          .backgroundColor(0x666666)
          .onClick(() => { this.maskColor = 0x66000000 })
        Button('蓝色遮罩')
          .fontSize(12)
          .backgroundColor(0x666666)
          .onClick(() => { this.maskColor = 0x66007DFF })
        Button('清除遮罩')
          .fontSize(12)
          .backgroundColor(0x666666)
          .onClick(() => { this.maskColor = 0x00000000 })
      }
    }
    .width('100%')
    .padding(14)
    .backgroundColor(this.cardBg)
    .borderRadius(12)
    .alignItems(HorizontalAlign.Start)
  }

  // ---------- 23. resizable ----------
  @Builder
  buildResizableSection() {
    Column({ space: 10 }) {
      Text('23. resizable 九宫格拉伸')
        .fontSize(17)
        .fontWeight(FontWeight.Bold)
      Text('通过 ResizableOptions 设定九宫格切片, 拉伸时保持四角不变形')
        .fontSize(12)
        .fontColor(0x999999)

      Image(this.medias[this.currentMediaIndex])
        .width('100%')
        .height(120)
        .objectFit(ImageFit.Cover)
        .borderRadius(10)
        .border({ width: 1, color: 0xCCCCCC })

      Text('提示: resizable 适合带边框的图(如气泡、按钮背景), 对普通图片拉伸可见整体缩放。')
        .fontSize(11)
        .fontColor(0x666666)
    }
    .width('100%')
    .padding(14)
    .backgroundColor(this.cardBg)
    .borderRadius(12)
    .alignItems(HorizontalAlign.Start)
  }

  // ---------- 24. 边框变体 ----------
  @Builder
  buildBorderVariants() {
    Column({ space: 10 }) {
      Text('24. 边框装饰组合')
        .fontSize(17)
        .fontWeight(FontWeight.Bold)
      Text('不同宽度/颜色/圆角的边框装饰效果')
        .fontSize(12)
        .fontColor(0x999999)

      Flex({ wrap: FlexWrap.Wrap, justifyContent: FlexAlign.SpaceAround }) {
        Column({ space: 5 }) {
          Image(this.medias[this.currentMediaIndex])
            .width(90)
            .height(90)
            .objectFit(ImageFit.Cover)
            .border({ width: 1, color: 0xCCCCCC })
          Text('细灰边框')
            .fontSize(10)
            .fontColor(0x999999)
        }
        Column({ space: 5 }) {
          Image(this.medias[this.currentMediaIndex])
            .width(90)
            .height(90)
            .objectFit(ImageFit.Cover)
            .border({ width: 4, color: 0x007DFF })
          Text('蓝色粗边框')
            .fontSize(10)
            .fontColor(0x999999)
        }
        Column({ space: 5 }) {
          Image(this.medias[this.currentMediaIndex])
            .width(90)
            .height(90)
            .objectFit(ImageFit.Cover)
            .borderRadius(12)
            .border({ width: 2, color: 0xFF4444 })
          Text('红边圆角')
            .fontSize(10)
            .fontColor(0x999999)
        }
        Column({ space: 5 }) {
          Image(this.medias[this.currentMediaIndex])
            .width(90)
            .height(90)
            .objectFit(ImageFit.Cover)
            .borderRadius(45)
            .border({ width: 3, color: 0x00AA66 })
          Text('绿边圆形')
            .fontSize(10)
            .fontColor(0x999999)
        }
        Column({ space: 5 }) {
          Image(this.medias[this.currentMediaIndex])
            .width(90)
            .height(90)
            .objectFit(ImageFit.Cover)
            .border({ width: 2, color: 0xFFAA00, style: BorderStyle.Dashed })
          Text('虚线边框')
            .fontSize(10)
            .fontColor(0x999999)
        }
        Column({ space: 5 }) {
          Image(this.medias[this.currentMediaIndex])
            .width(90)
            .height(90)
            .objectFit(ImageFit.Cover)
            .borderRadius(8)
            .shadow({ radius: 12, color: 0x33000000, offsetY: 4 })
          Text('圆角阴影')
            .fontSize(10)
            .fontColor(0x999999)
        }
      }
    }
    .width('100%')
    .padding(14)
    .backgroundColor(this.cardBg)
    .borderRadius(12)
    .alignItems(HorizontalAlign.Start)
  }

  // ---------- 说明 ----------
  @Builder
  buildNotesSection() {
    Column({ space: 6 }) {
      Text('说明')
        .fontSize(15)
        .fontWeight(FontWeight.Bold)
      Text('• objectFit: Cover/Contain/Auto/Fill/ScaleDown/None 控制填充方式')
        .fontSize(12)
        .fontColor(0x666666)
      Text('• sourceSize: 解码到指定像素, 节省内存(0 表示不设置)')
        .fontSize(12)
        .fontColor(0x666666)
      Text('• borderRadius 适合矩形圆角, clipShape 支持圆形/椭圆/异形圆角')
        .fontSize(12)
        .fontColor(0x666666)
      Text('• 滤镜链可叠加: blur/brightness/contrast/saturate/grayscale/sepia/invert/opacity')
        .fontSize(12)
        .fontColor(0x666666)
      Text('• 变换: scale/rotate/translate 独立于布局, 不影响其他元素')
        .fontSize(12)
        .fontColor(0x666666)
      Text('• fillColor 对 SVG/单色图着色效果最佳')
        .fontSize(12)
        .fontColor(0x666666)
      Text('• colorFilter 通过 4x5 颜色矩阵实现自定义调色')
        .fontSize(12)
        .fontColor(0x666666)
      Text('• 手势: 通过 GestureGroup(Exclusive) 组合多种手势')
        .fontSize(12)
        .fontColor(0x666666)
      Text('• animateTo 驱动属性动画, 需配合 @State 触发重绘')
        .fontSize(12)
        .fontColor(0x666666)
    }
    .width('100%')
    .padding(14)
    .backgroundColor(this.cardBg)
    .borderRadius(12)
    .alignItems(HorizontalAlign.Start)
  }
}
