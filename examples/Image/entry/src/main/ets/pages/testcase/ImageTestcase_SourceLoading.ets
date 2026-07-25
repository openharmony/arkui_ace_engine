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
 * Image 图源与加载合集（由原 037/042/043/051 合并）
 * 覆盖：多图源切换 / ImageAnimator 帧动画 / PixelMap 加载 / 占位图与 Fit·Repeat
 */

import { image } from '@kit.ImageKit'

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

@Entry
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
