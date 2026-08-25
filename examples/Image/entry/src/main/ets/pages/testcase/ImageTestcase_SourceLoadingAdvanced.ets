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
 * Image 图源·混排·加载·重试综合合集
 * 合并自: ImageTestcaseSourceLoading / ImageTestcaseImageSpanInline /
 * ImageTestcaseLoadingStateSkeleton / ImageTestcaseRetryFallback
 */

import { image } from '@kit.ImageKit'

/**
 * Image 图源与加载合集（由原 037/042/043/051 合并）
 * 覆盖：多图源切换 / ImageAnimator 帧动画 / PixelMap 加载 / 占位图与 Fit·Repeat
 */

/** 原 037：多图源切换 */
@Component
struct ImageSourceSwitchTestCase037 {
  @State currentSourceType: string = 'resource'
  @State imageSource: ResourceStr | image.PixelMap | undefined = $r('app.media.startIcon')
  @State switchCount: number = 0

  private readonly SOURCE_LIST: Array<{ type: string; source: ResourceStr | Resource; label: string }> = [
    { type: 'resource', source: $r('app.media.startIcon'), label: 'startIcon' },
    { type: 'resource', source: $r('app.media.background'), label: 'background' },
    { type: 'resource', source: $r('app.media.foreground'), label: 'foreground' },
    { type: 'empty', source: '', label: '空字符串' },
    { type: 'invalid', source: 'invalid://url', label: '无效URL' }
  ]

  build() {
    Column() {
      Text('Image多图源切换测试')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 16 })

      Image(this.imageSource)
        .width(180)
        .height(180)
        .objectFit(ImageFit.Cover)
        .alt($r('app.media.startIcon'))
        .border({ width: 2, color: Color.Blue })
        .borderRadius(12)
        .margin({ bottom: 16 })

      Text(`当前源类型: ${this.currentSourceType}`)
        .fontSize(14)
        .fontColor(Color.Gray)
        .margin({ bottom: 4 })
      Text(`切换次数: ${this.switchCount}`)
        .fontSize(12)
        .fontColor(Color.Orange)

      Divider()
        .margin({ top: 16, bottom: 16 })

      Text('图源选择')
        .fontSize(14)
        .fontWeight(FontWeight.Medium)
        .margin({ bottom: 8 })

      Grid() {
        ForEach(this.SOURCE_LIST, (item: { type: string; source: ResourceStr | Resource; label: string }) => {
          GridItem() {
            Column() {
              Text(item.label)
                .fontSize(12)
                .fontColor(this.currentSourceType === item.type &&
                  this.currentSourceType !== 'resource' ? Color.Blue : Color.Gray)
            }
            .padding(10)
            .backgroundColor('#FAFAFA')
            .borderRadius(4)
            .onClick(() => {
              this.currentSourceType = item.type
              this.imageSource = item.source
              this.switchCount++
            })
          }
        })
      }
      .columnsTemplate('repeat(3, 1fr)')
      .rowsGap(8)
      .columnsGap(8)
      .padding(16)

      Divider()

      Text('快速循环切换')
        .fontSize(14)
        .fontWeight(FontWeight.Medium)
        .margin({ top: 16, bottom: 8 })

      Row({ space: 12 }) {
        Button('下一张')
          .onClick(() => {
            const nextIndex = this.switchCount % this.SOURCE_LIST.length
            this.currentSourceType = this.SOURCE_LIST[nextIndex].type
            this.imageSource = this.SOURCE_LIST[nextIndex].source
            this.switchCount++
          })
        Button('重置')
          .onClick(() => {
            this.currentSourceType = 'resource'
            this.imageSource = $r('app.media.startIcon')
            this.switchCount = 0
          })
          .backgroundColor('#FF6666')
      }
    }
    .width('100%')
    .height('100%')
    .padding(16)
  }
}

/** 原 042：ImageAnimator 帧动画 */
@Component
struct ImageAnimatorTestCase042 {
  @State currentFrameIndex: number = 0
  @State isPlaying: boolean = false
  @State iterationCount: number = 1
  @State animDuration: number = 1000
  @State animReverse: boolean = false
  @State fillMode: FillMode = FillMode.Forwards

  private readonly ANIM_IMAGES: Resource[] = [
    $r('app.media.startIcon'),
    $r('app.media.background'),
    $r('app.media.foreground'),
    $r('app.media.startIcon'),
    $r('app.media.background')
  ]

  build() {
    Column() {
      Text('ImageAnimator图片帧动画测试')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 16 })

      ImageAnimator()
        .images(this.ANIM_IMAGES)
        .duration(this.animDuration)
        .iterations(this.iterationCount === -1 ? -1 : this.iterationCount)
        .reverse(this.animReverse)
        .fillMode(this.fillMode)
        .width(150)
        .height(150)
        .border({ width: 2, color: Color.Blue })
        .borderRadius(8)
        .margin({ bottom: 16 })

      Text(`帧数: ${this.ANIM_IMAGES.length}, 持续: ${this.animDuration}ms, ` +
        `循环: ${this.iterationCount === -1 ? '无限' : this.iterationCount}`)
        .fontSize(12)
        .fontColor(Color.Gray)
        .margin({ bottom: 4 })
      Text(`反转: ${this.animReverse}, fillMode: ${this.fillMode}`)
        .fontSize(12)
        .fontColor(Color.Gray)
        .margin({ bottom: 8 })

      Row({ space: 12 }) {
        Button('播放')
          .onClick(() => { this.isPlaying = true })
          .backgroundColor('#4CAF50')
        Button('停止')
          .onClick(() => { this.isPlaying = false })
          .backgroundColor('#F44336')
        Button('反转')
          .onClick(() => { this.animReverse = !this.animReverse })
      }
      .margin({ bottom: 16 })

      Divider()

      Text('参数调节')
        .fontSize(14)
        .fontWeight(FontWeight.Medium)
        .margin({ top: 8, bottom: 8 })

      Row({ space: 8 }) {
        Button('200ms')
          .onClick(() => { this.animDuration = 200 })
          .fontSize(11)
        Button('500ms')
          .onClick(() => { this.animDuration = 500 })
          .fontSize(11)
        Button('1000ms')
          .onClick(() => { this.animDuration = 1000 })
          .fontSize(11)
        Button('2000ms')
          .onClick(() => { this.animDuration = 2000 })
          .fontSize(11)
      }
      .margin({ bottom: 8 })

      Row({ space: 8 }) {
        Button('循环1次')
          .onClick(() => { this.iterationCount = 1 })
          .fontSize(11)
        Button('循环3次')
          .onClick(() => { this.iterationCount = 3 })
          .fontSize(11)
        Button('无限循环')
          .onClick(() => { this.iterationCount = -1 })
          .fontSize(11)
      }
      .margin({ bottom: 8 })

      Row({ space: 8 }) {
        Button('Forwards')
          .onClick(() => { this.fillMode = FillMode.Forwards })
          .fontSize(11)
        Button('Backwards')
          .onClick(() => { this.fillMode = FillMode.Backwards })
          .fontSize(11)
        Button('None')
          .onClick(() => { this.fillMode = FillMode.None })
          .fontSize(11)
      }
    }
    .width('100%')
    .height('100%')
    .padding(16)
  }
}

/** 原 043：PixelMap 加载模式 */
@Component
struct ImagePixelMapTestCase043 {
  @State pixelMap: image.PixelMap | undefined = undefined
  @State createResult: string = '未创建'
  @State pixelMapWidth: number = 100
  @State pixelMapHeight: number = 100
  @State loadCount: number = 0

  async aboutToAppear() {
    await this.createTestPixelMap()
  }

  private async createTestPixelMap(): Promise<void> {
    try {
      const buffer = new ArrayBuffer(this.pixelMapWidth * this.pixelMapHeight * 4)
      const options: image.InitializationOptions = {
        size: { width: this.pixelMapWidth, height: this.pixelMapHeight },
        pixelFormat: image.PixelMapFormat.RGBA_8888,
        editable: true
      }
      this.pixelMap = await image.createPixelMap(buffer, options)
      this.createResult = `创建成功 ${this.pixelMapWidth}x${this.pixelMapHeight}`
      this.loadCount++
    } catch (error) {
      this.createResult = `创建失败: ${(error as Error).message}`
    }
  }

  build() {
    Column() {
      Text('Image PixelMap加载模式测试')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 16 })

      if (this.pixelMap) {
        Image(this.pixelMap)
          .width(150)
          .height(150)
          .objectFit(ImageFit.Contain)
          .border({ width: 2, color: Color.Blue })
          .borderRadius(8)
          .backgroundColor('#F0F0F0')
          .margin({ bottom: 16 })
      } else {
        Column() {
          Text('PixelMap未创建')
            .fontSize(14)
            .fontColor(Color.Red)
        }
        .width(150)
        .height(150)
        .backgroundColor('#F0F0F0')
        .border({ width: 2, color: Color.Red })
        .borderRadius(8)
        .justifyContent(FlexAlign.Center)
        .margin({ bottom: 16 })
      }

      Text(this.createResult)
        .fontSize(14)
        .fontColor(this.createResult.startsWith('创建成功') ? Color.Green : Color.Red)
        .margin({ bottom: 4 })
      Text(`加载次数: ${this.loadCount}`)
        .fontSize(12)
        .fontColor(Color.Gray)
        .margin({ bottom: 12 })

      Divider()

      Text('尺寸选择')
        .fontSize(14)
        .fontWeight(FontWeight.Medium)
        .margin({ top: 16, bottom: 8 })

      Row({ space: 8 }) {
        Button('50x50')
          .onClick(async () => {
            this.pixelMapWidth = 50; this.pixelMapHeight = 50
            await this.createTestPixelMap()
          })
          .fontSize(11)
        Button('100x100')
          .onClick(async () => {
            this.pixelMapWidth = 100; this.pixelMapHeight = 100
            await this.createTestPixelMap()
          })
          .fontSize(11)
        Button('200x200')
          .onClick(async () => {
            this.pixelMapWidth = 200; this.pixelMapHeight = 200
            await this.createTestPixelMap()
          })
          .fontSize(11)
        Button('200x100')
          .onClick(async () => {
            this.pixelMapWidth = 200; this.pixelMapHeight = 100
            await this.createTestPixelMap()
          })
          .fontSize(11)
      }

      Button('重新创建')
        .onClick(async () => { await this.createTestPixelMap() })
        .margin({ top: 16 })
    }
    .width('100%')
    .height('100%')
    .padding(16)
  }
}

/** 原 051：占位图与 objectFit/objectRepeat 切换 */
@Component
struct ImagePlaceholderFitTestCase051 {
  @State fitIndex: number = 0
  @State repeatIndex: number = 0
  @State useAlt: boolean = true
  @State sourceIndex: number = 0

  private fits: Array<ImageFit> = [
    ImageFit.Cover, ImageFit.Contain, ImageFit.Fill,
    ImageFit.Auto, ImageFit.ScaleDown, ImageFit.None
  ]
  private fitNames: Array<string> = ['Cover', 'Contain', 'Fill', 'Auto', 'ScaleDown', 'None']
  private repeats: Array<ImageRepeat> = [ImageRepeat.NoRepeat, ImageRepeat.X, ImageRepeat.Y, ImageRepeat.XY]
  private repeatNames: Array<string> = ['NoRepeat', 'X', 'Y', 'XY']
  private sources: Array<Resource> = [
    $r('app.media.startIcon'),
    $r('app.media.background'),
    $r('app.media.foreground')
  ]

  build() {
    Column({ space: 12 }) {
      Text('Image占位图与Fit/Repeat测试')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)

      Image(this.sources[this.sourceIndex])
        .width(180)
        .height(180)
        .objectFit(this.fits[this.fitIndex])
        .objectRepeat(this.repeats[this.repeatIndex])
        .alt(this.useAlt ? $r('app.media.startIcon') : undefined)
        .border({ width: 2, color: Color.Blue })
        .borderRadius(12)
        .backgroundColor('#F5F5F5')

      Text(`Fit: ${this.fitNames[this.fitIndex]}  Repeat: ${this.repeatNames[this.repeatIndex]}`)
        .fontSize(13)
        .fontColor(Color.Gray)

      Row({ space: 8 }) {
        Button('切换Fit')
          .fontSize(11)
          .onClick(() => { this.fitIndex = (this.fitIndex + 1) % this.fits.length })
        Button('切换Repeat')
          .fontSize(11)
          .onClick(() => { this.repeatIndex = (this.repeatIndex + 1) % this.repeats.length })
        Button(this.useAlt ? '占位图:开' : '占位图:关')
          .fontSize(11)
          .onClick(() => { this.useAlt = !this.useAlt })
        Button('换源')
          .fontSize(11)
          .backgroundColor('#FF6666')
          .onClick(() => { this.sourceIndex = (this.sourceIndex + 1) % this.sources.length })
      }
    }
    .width('100%')
    .height('100%')
    .padding(16)
    .justifyContent(FlexAlign.Center)
  }
}

@Component
struct ImageTestcaseSourceLoading {
  @State currentIndex: number = 0

  build() {
    Column() {
      Tabs({ barPosition: BarPosition.Start, index: this.currentIndex }) {
        TabContent() { ImageSourceSwitchTestCase037() }
          .tabBar('多图源')
        TabContent() { ImageAnimatorTestCase042() }
          .tabBar('ImageAnimator')
        TabContent() { ImagePixelMapTestCase043() }
          .tabBar('PixelMap')
        TabContent() { ImagePlaceholderFitTestCase051() }
          .tabBar('占位图·Fit')
      }
      .barMode(BarMode.Scrollable)
      .scrollable(true)
      .onChange((index: number) => { this.currentIndex = index })
    }
    .width('100%')
    .height('100%')
  }
}

/**
 * Image 图片文字混排合集(ImageSpan)
 * 覆盖：内联图文 / 垂直对齐 / 多图样式
 */

/** 内联图文 */
@Component
struct ImageSpanInlineScene {
  build() {
    Column({ space: 16 }) {
      Text('ImageSpan 内联图文测试')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)

      Text() {
        Span('ImageSpan 可将图片嵌入文本流中,')
        ImageSpan($r('app.media.startIcon'))
          .width(24)
          .height(24)
          .verticalAlign(ImageSpanAlignment.CENTER)
        Span(' 实现图标与文字的对齐排列。')
        ImageSpan($r('app.media.background'))
          .width(20)
          .height(20)
          .verticalAlign(ImageSpanAlignment.CENTER)
        Span(' 也可连续插入多张图片。')
      }
      .fontSize(16)
      .border({ width: 1, color: Color.Gray })
      .borderRadius(8)
      .padding(12)

      Text() {
        Span('行内图片 ')
        ImageSpan($r('app.media.foreground')).width(40).height(40)
          .verticalAlign(ImageSpanAlignment.BOTTOM)
        Span(' 与文字混排,行高随图片撑开。')
      }
      .fontSize(16)
      .border({ width: 1, color: Color.Blue })
      .borderRadius(8)
      .padding(12)
    }
    .width('100%')
    .height('100%')
    .padding(16)
  }
}

/** 垂直对齐 */
@Component
struct ImageSpanVerticalAlignScene {
  @State alignIndex: number = 0
  private readonly ALIGNS: Array<{ label: string; value: ImageSpanAlignment }> = [
    { label: 'TOP', value: ImageSpanAlignment.TOP },
    { label: 'CENTER', value: ImageSpanAlignment.CENTER },
    { label: 'BOTTOM', value: ImageSpanAlignment.BOTTOM },
    { label: 'BASELINE', value: ImageSpanAlignment.BASELINE }
  ]

  build() {
    Column({ space: 16 }) {
      Text('ImageSpan 垂直对齐测试')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)

      Text() {
        Span('这是一段参考文字,观察图片相对文字的对齐位置 ')
        ImageSpan($r('app.media.startIcon'))
          .width(36)
          .height(36)
          .verticalAlign(this.ALIGNS[this.alignIndex].value)
        Span(' 对齐方式为 ')
        Span(this.ALIGNS[this.alignIndex].label).fontColor(Color.Blue)
        Span('。')
      }
      .fontSize(18)
      .border({ width: 1, color: Color.Gray })
      .borderRadius(8)
      .padding(12)

      Row({ space: 8 }) {
        ForEach(this.ALIGNS, (item: { label: string; value: ImageSpanAlignment }, idx: number) => {
          Button(item.label)
            .fontSize(11)
            .backgroundColor(idx === this.alignIndex ? '#007DFF' : '#E0E0E0')
            .onClick(() => { this.alignIndex = idx })
        })
      }
    }
    .width('100%')
    .height('100%')
    .padding(16)
  }
}

/** 多图样式 */
@Component
struct ImageSpanStylingScene {
  @State fitIndex: number = 0
  private readonly FITS: Array<ImageFit> = [
    ImageFit.Cover, ImageFit.Contain, ImageFit.Fill, ImageFit.ScaleDown
  ]
  private readonly FIT_NAMES: Array<string> = ['Cover', 'Contain', 'Fill', 'ScaleDown']

  build() {
    Column({ space: 16 }) {
      Text('ImageSpan 多图样式测试')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)

      Text() {
        Span('图标 ')
        ImageSpan($r('app.media.startIcon'))
          .width(28)
          .height(28)
          .objectFit(this.FITS[this.fitIndex])
          .verticalAlign(ImageSpanAlignment.CENTER)
        Span('  ')
        ImageSpan($r('app.media.background'))
          .width(40)
          .height(20)
          .objectFit(this.FITS[this.fitIndex])
          .verticalAlign(ImageSpanAlignment.CENTER)
        Span('  ')
        ImageSpan($r('app.media.foreground'))
          .width(20)
          .height(40)
          .objectFit(this.FITS[this.fitIndex])
          .verticalAlign(ImageSpanAlignment.CENTER)
        Span(' 不同尺寸的行内图片混排。')
      }
      .fontSize(16)
      .border({ width: 1, color: Color.Gray })
      .borderRadius(8)
      .padding(12)

      Text(`objectFit: ${this.FIT_NAMES[this.fitIndex]}`)
        .fontSize(13)
        .fontColor(Color.Orange)

      Row({ space: 8 }) {
        ForEach(this.FIT_NAMES, (name: string, idx: number) => {
          Button(name)
            .fontSize(11)
            .backgroundColor(idx === this.fitIndex ? '#007DFF' : '#E0E0E0')
            .onClick(() => { this.fitIndex = idx })
        })
      }
    }
    .width('100%')
    .height('100%')
    .padding(16)
  }
}

@Component
struct ImageTestcaseImageSpanInline {
  @State currentIndex: number = 0

  build() {
    Column() {
      Tabs({ barPosition: BarPosition.Start, index: this.currentIndex }) {
        TabContent() { ImageSpanInlineScene() }
          .tabBar('内联图文')
        TabContent() { ImageSpanVerticalAlignScene() }
          .tabBar('垂直对齐')
        TabContent() { ImageSpanStylingScene() }
          .tabBar('多图样式')
      }
      .barMode(BarMode.Scrollable)
      .scrollable(true)
      .onChange((index: number) => { this.currentIndex = index })
    }
    .width('100%')
    .height('100%')
  }
}

/**
 * Image 加载状态与骨架屏合集
 * 覆盖：alt+加载指示器 / 骨架屏占位 / 缩略图渐进加载
 */

/** alt + 加载指示器 */
@Component
struct LoadingIndicatorScene {
  @State loading: boolean = false
  @State srcToggle: boolean = false
  @State status: string = '空闲'

  private reload(): void {
    this.loading = true
    this.status = '加载中...'
    setTimeout(() => {
      this.srcToggle = !this.srcToggle
    }, 800)
  }

  build() {
    Column({ space: 12 }) {
      Text('Image 加载指示器测试')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)

      Stack() {
        Image(this.srcToggle ? $r('app.media.background') : $r('app.media.startIcon'))
          .width(160)
          .height(160)
          .objectFit(ImageFit.Cover)
          .alt($r('app.media.startIcon'))
          .border({ width: 2, color: Color.Blue })
          .borderRadius(8)
          .onComplete(() => {
            this.loading = false
            this.status = '加载完成'
          })
          .onError(() => {
            this.loading = false
            this.status = '加载失败'
          })

        if (this.loading) {
          Column() {
            LoadingProgress().width(48).height(48).color(Color.Blue)
          }
          .width(160)
          .height(160)
          .justifyContent(FlexAlign.Center)
          .backgroundColor('#80000000')
          .borderRadius(8)
        }
      }
      .width(160)
      .height(160)

      Text(this.status)
        .fontSize(13)
        .fontColor(this.loading ? Color.Orange : Color.Gray)

      Button('重新加载(模拟延迟)')
        .fontSize(11)
        .enabled(!this.loading)
        .onClick(() => this.reload())
    }
    .width('100%')
    .height('100%')
    .padding(16)
  }
}

/** 骨架屏占位 */
@Component
struct SkeletonPlaceholderScene {
  @State loading: boolean = true

  private simulate(): void {
    this.loading = true
    setTimeout(() => { this.loading = false }, 1500)
  }

  build() {
    Column({ space: 12 }) {
      Text('Image 骨架屏占位测试')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)

      if (this.loading) {
        Column({ space: 8 }) {
          Row({ space: 8 }) {
            Column().width(80).height(80).backgroundColor('#E0E0E0').borderRadius(8)
            Column({ space: 6 }) {
              Column().width('100%').height(16).backgroundColor('#E0E0E0').borderRadius(4)
              Column().width('60%').height(12).backgroundColor('#E8E8E8').borderRadius(4)
              Column().width('80%').height(12).backgroundColor('#E8E8E8').borderRadius(4)
            }.layoutWeight(1)
          }.width('100%')
        }
        .width('100%')
        .padding(12)
        .backgroundColor('#FAFAFA')
        .borderRadius(8)
      } else {
        Row({ space: 8 }) {
          Image($r('app.media.startIcon'))
            .width(80).height(80).objectFit(ImageFit.Cover).borderRadius(8)
          Column({ space: 6 }) {
            Text('图片加载完成').fontSize(16).fontWeight(FontWeight.Medium)
            Text('骨架屏已替换为真实内容').fontSize(12).fontColor(Color.Gray)
            Text('可点击下方按钮重新触发加载').fontSize(12).fontColor(Color.Gray)
          }.layoutWeight(1)
        }
        .width('100%')
        .padding(12)
        .backgroundColor('#FAFAFA')
        .borderRadius(8)
      }

      Text(this.loading ? '骨架屏显示中...' : '已加载真实图片')
        .fontSize(13)
        .fontColor(this.loading ? Color.Orange : Color.Green)

      Button(this.loading ? '加载中' : '重新加载')
        .fontSize(11)
        .enabled(!this.loading)
        .backgroundColor('#FF6666')
        .onClick(() => this.simulate())
    }
    .width('100%')
    .height('100%')
    .padding(16)
    .onAppear(() => this.simulate())
  }
}

/** 缩略图渐进加载 */
@Component
struct ProgressiveLoadScene {
  @State fullLoaded: boolean = false
  @State status: string = '缩略图'

  build() {
    Column({ space: 12 }) {
      Text('Image 缩略图渐进加载测试')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)

      Stack() {
        if (this.fullLoaded) {
          Image($r('app.media.startIcon'))
            .width(180)
            .height(180)
            .objectFit(ImageFit.Cover)
            .border({ width: 2, color: Color.Blue })
            .borderRadius(8)
            .onComplete(() => { this.status = '原图加载完成' })
        } else {
          Image($r('app.media.startIcon'))
            .width(180)
            .height(180)
            .objectFit(ImageFit.Cover)
            .sourceSize({ width: 16, height: 16 })
            .interpolation(ImageInterpolation.Low)
            .border({ width: 2, color: Color.Gray })
            .borderRadius(8)
            .onComplete(() => { this.status = '缩略图已显示(低清)' })
        }
      }
      .width(180)
      .height(180)

      Text(this.status)
        .fontSize(13)
        .fontColor(this.fullLoaded ? Color.Green : Color.Orange)

      Text('先用 sourceSize 解码极小缩略图,再按需加载原图以节省内存')
        .fontSize(11)
        .fontColor(Color.Gray)

      Row({ space: 8 }) {
        Button('加载原图')
          .fontSize(11)
          .enabled(!this.fullLoaded)
          .onClick(() => { this.fullLoaded = true })
        Button('回到缩略图')
          .fontSize(11)
          .backgroundColor('#FF6666')
          .enabled(this.fullLoaded)
          .onClick(() => { this.fullLoaded = false })
      }
    }
    .width('100%')
    .height('100%')
    .padding(16)
  }
}

@Component
struct ImageTestcaseLoadingStateSkeleton {
  @State currentIndex: number = 0

  build() {
    Column() {
      Tabs({ barPosition: BarPosition.Start, index: this.currentIndex }) {
        TabContent() { LoadingIndicatorScene() }
          .tabBar('加载指示器')
        TabContent() { SkeletonPlaceholderScene() }
          .tabBar('骨架屏')
        TabContent() { ProgressiveLoadScene() }
          .tabBar('渐进加载')
      }
      .barMode(BarMode.Scrollable)
      .scrollable(true)
      .onChange((index: number) => { this.currentIndex = index })
    }
    .width('100%')
    .height('100%')
  }
}

/**
 * Image 错误重试与降级链合集
 * 覆盖：指数退避重试 / 多源降级链 / 错误降级兜底
 */

/** 指数退避重试 */
@Component
struct RetryScene {
  @State src: string = 'invalid://nonexistent_0.jpg'
  @State retryCount: number = 0
  @State status: string = '初始加载'
  private readonly MAX_RETRY: number = 3

  private reset(): void {
    this.retryCount = 0
    this.status = '初始加载'
    this.src = `invalid://nonexistent_0.jpg`
  }

  build() {
    Column({ space: 12 }) {
      Text('Image 指数退避重试测试')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)

      Image(this.src)
        .width(140)
        .height(140)
        .objectFit(ImageFit.Cover)
        .alt($r('app.media.startIcon'))
        .border({ width: 2, color: Color.Red })
        .borderRadius(8)
        .onError(() => {
          if (this.retryCount < this.MAX_RETRY) {
            this.retryCount++
            const delay = 500 * Math.pow(2, this.retryCount - 1)
            this.status = `第${this.retryCount}/${this.MAX_RETRY}次重试 等待${delay}ms`
            setTimeout(() => {
              this.src = `invalid://nonexistent_${this.retryCount}.jpg`
            }, delay)
          } else {
            this.status = `重试${this.MAX_RETRY}次后仍失败`
          }
        })

      Text(this.status)
        .fontSize(13)
        .fontColor(this.status.includes('失败') ? Color.Red : Color.Orange)

      Text(`最大重试次数: ${this.MAX_RETRY}  退避基数: 500ms * 2^n`)
        .fontSize(11)
        .fontColor(Color.Gray)

      Button('重置重试流程')
        .fontSize(11)
        .backgroundColor('#FF6666')
        .onClick(() => this.reset())
    }
    .width('100%')
    .height('100%')
    .padding(16)
  }
}

/** 多源降级链 */
@Component
struct FallbackChainScene {
  @State idx: number = 0
  @State status: string = '尝试第1个源'
  private readonly CHAIN: ResourceStr[] = [
    'invalid://primary.jpg',
    'invalid://secondary.jpg',
    'invalid://backup.jpg',
    $r('app.media.startIcon')
  ]

  private reset(): void {
    this.idx = 0
    this.status = '尝试第1个源'
  }

  build() {
    Column({ space: 12 }) {
      Text('Image 多源降级链测试')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)

      Image(this.CHAIN[this.idx])
        .width(140)
        .height(140)
        .objectFit(ImageFit.Cover)
        .alt($r('app.media.startIcon'))
        .border({ width: 2, color: Color.Blue })
        .borderRadius(8)
        .onError(() => {
          if (this.idx < this.CHAIN.length - 1) {
            this.idx++
            this.status = `第${this.idx + 1}个源失败,降级到下一个`
          } else {
            this.status = '所有源均失败'
          }
        })
        .onComplete(() => {
          this.status = `第${this.idx + 1}个源加载成功(兜底资源)`
        })

      Text(this.status)
        .fontSize(13)
        .fontColor(this.status.includes('成功') ? Color.Green : Color.Orange)

      Text(`当前源索引: ${this.idx} / ${this.CHAIN.length - 1} (最后为兜底资源)`)
        .fontSize(11)
        .fontColor(Color.Gray)

      Button('重置降级链')
        .fontSize(11)
        .backgroundColor('#FF6666')
        .onClick(() => this.reset())
    }
    .width('100%')
    .height('100%')
    .padding(16)
  }
}

/** 错误降级兜底 */
@Component
struct DegradeScene {
  @State src: ResourceStr = 'invalid://nonexistent.jpg'
  @State degraded: boolean = false
  @State msg: string = '使用无效源'

  build() {
    Column({ space: 12 }) {
      Text('Image 错误降级兜底测试')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)

      Image(this.src)
        .width(140)
        .height(140)
        .objectFit(ImageFit.Cover)
        .alt($r('app.media.startIcon'))
        .border({ width: 2, color: this.degraded ? Color.Green : Color.Red })
        .borderRadius(8)
        .onError(() => {
          if (!this.degraded) {
            this.degraded = true
            this.src = $r('app.media.startIcon')
            this.msg = '主源失败,已降级到本地兜底图'
          }
        })
        .onComplete(() => {
          if (this.degraded) {
            this.msg = '降级兜底图加载成功'
          }
        })

      Text(this.msg)
        .fontSize(13)
        .fontColor(this.degraded ? Color.Green : Color.Red)

      Text(`已降级: ${this.degraded ? '是' : '否'}`)
        .fontSize(12)
        .fontColor(Color.Gray)

      Button('恢复为无效源')
        .fontSize(11)
        .backgroundColor('#FF6666')
        .onClick(() => {
          this.degraded = false
          this.msg = '使用无效源'
          this.src = 'invalid://nonexistent.jpg'
        })
    }
    .width('100%')
    .height('100%')
    .padding(16)
  }
}

@Component
struct ImageTestcaseRetryFallback {
  @State currentIndex: number = 0

  build() {
    Column() {
      Tabs({ barPosition: BarPosition.Start, index: this.currentIndex }) {
        TabContent() { RetryScene() }
          .tabBar('指数退避')
        TabContent() { FallbackChainScene() }
          .tabBar('降级链')
        TabContent() { DegradeScene() }
          .tabBar('降级兜底')
      }
      .barMode(BarMode.Scrollable)
      .scrollable(true)
      .onChange((index: number) => { this.currentIndex = index })
    }
    .width('100%')
    .height('100%')
  }
}

@Entry
@Component
struct ImageTestCategorySourceLoading {
  @State currentIndex: number = 0

  build() {
    Column() {
      Tabs({ barPosition: BarPosition.Start, index: this.currentIndex }) {
        TabContent() { ImageTestcaseSourceLoading() }
          .tabBar('图源加载')
        TabContent() { ImageTestcaseImageSpanInline() }
          .tabBar('图文混排')
        TabContent() { ImageTestcaseLoadingStateSkeleton() }
          .tabBar('加载状态')
        TabContent() { ImageTestcaseRetryFallback() }
          .tabBar('重试降级')
      }
      .barMode(BarMode.Scrollable)
      .scrollable(true)
      .onChange((index: number) => { this.currentIndex = index })
    }
    .width('100%')
    .height('100%')
  }
}
