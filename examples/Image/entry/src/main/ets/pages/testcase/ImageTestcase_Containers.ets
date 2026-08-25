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
 * Image 容器场景合集（由原 047/048/049/052/053 合并）
 * 覆盖：List 列表 / Grid 网格 / Stack 层叠 / Swiper 轮播 / WaterFlow 瀑布流
 */

/** 053 用到的瀑布流数据源 */
class WaterFlowDataSource implements IDataSource {
  private items: Array<number> = []
  private listeners: DataChangeListener[] = []

  constructor(count: number) {
    for (let i = 0; i < count; i++) {
      this.items.push(this.genHeight(i))
    }
  }

  private genHeight(idx: number): number {
    const heights = [120, 180, 240, 160, 200, 140, 220, 100, 260, 180]
    return heights[idx % heights.length]
  }

  totalCount(): number { return this.items.length }

  getData(idx: number): number { return this.items[idx] }

  registerDataChangeListener(listener: DataChangeListener): void {
    this.listeners.push(listener)
  }

  unregisterDataChangeListener(listener: DataChangeListener): void {
    this.listeners = this.listeners.filter(l => l !== listener)
  }

  append(count: number): void {
    const start = this.items.length
    for (let i = 0; i < count; i++) {
      this.items.push(this.genHeight(start + i))
    }
    this.listeners.forEach(l => l.onDataReloaded())
  }

  clear(): void {
    this.items = []
    this.listeners.forEach(l => l.onDataReloaded())
  }
}

/** 原 047：List 容器 */
@Component
struct ImageInListTestCase047 {
  @State itemCount: number = 30
  @State lazyLoadEnabled: boolean = true

  build() {
    Column() {
      Row() {
        Text('Image在List容器中测试')
          .fontSize(20)
          .fontWeight(FontWeight.Bold)
        Blank()
        Text(`条目数: ${this.itemCount}`)
          .fontSize(14)
          .fontColor(Color.Gray)
      }
      .width('100%')
      .padding(16)

      Row({ space: 12 }) {
        Button('增加10条')
          .onClick(() => { this.itemCount += 10 })
        Button('减少10条')
          .onClick(() => { this.itemCount = Math.max(5, this.itemCount - 10) })
        Button(`懒加载: ${this.lazyLoadEnabled ? '开' : '关'}`)
          .onClick(() => { this.lazyLoadEnabled = !this.lazyLoadEnabled })
      }
      .padding({ left: 16, right: 16, bottom: 8 })

      List({ space: 8 }) {
        ForEach(Array.from({ length: this.itemCount }, (_, i) => i), (index: number) => {
          ListItem() {
            Row() {
              Image($r('app.media.startIcon'))
                .width(60)
                .height(60)
                .objectFit(ImageFit.Cover)
                .borderRadius(8)
                .syncLoad(!this.lazyLoadEnabled)
                .border({ width: 1, color: Color.Gray })

              Column() {
                Text(`图片条目 ${index + 1}`)
                  .fontSize(16)
                  .fontWeight(FontWeight.Medium)
                Text('这是List容器中的图片测试项')
                  .fontSize(12)
                  .fontColor(Color.Gray)
                  .margin({ top: 4 })
              }
              .margin({ left: 12 })
              .layoutWeight(1)
            }
            .width('100%')
            .padding(12)
            .backgroundColor(Color.White)
            .borderRadius(8)
          }
        })
      }
      .layoutWeight(1)
      .padding({ left: 16, right: 16 })
      .edgeEffect(EdgeEffect.Spring)
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#F5F5F5')
  }
}

/** 原 048：Grid 容器 */
@Component
struct ImageInGridTestCase048 {
  @State columnsCount: number = 3
  @State objectFit: ImageFit = ImageFit.Cover
  @State borderRadius: number = 8
  @State imageCount: number = 12

  private readonly GRID_IMAGES: Resource[] = [
    $r('app.media.startIcon'),
    $r('app.media.background'),
    $r('app.media.foreground'),
    $r('app.media.startIcon'),
    $r('app.media.background'),
    $r('app.media.foreground'),
    $r('app.media.startIcon'),
    $r('app.media.background'),
    $r('app.media.foreground'),
    $r('app.media.startIcon'),
    $r('app.media.background'),
    $r('app.media.foreground')
  ]

  build() {
    Column() {
      Row() {
        Text('Image在Grid容器中测试')
          .fontSize(20)
          .fontWeight(FontWeight.Bold)
        Blank()
        Text(`${this.columnsCount}列 | ${this.imageCount}图`)
          .fontSize(14)
          .fontColor(Color.Gray)
      }
      .width('100%')
      .padding(16)

      Row({ space: 8 }) {
        Button('2列')
          .onClick(() => { this.columnsCount = 2 })
          .fontSize(11)
        Button('3列')
          .onClick(() => { this.columnsCount = 3 })
          .fontSize(11)
        Button('4列')
          .onClick(() => { this.columnsCount = 4 })
          .fontSize(11)
        Button('5列')
          .onClick(() => { this.columnsCount = 5 })
          .fontSize(11)
      }
      .padding({ left: 16, right: 16, bottom: 8 })

      Row({ space: 8 }) {
        Button('Cover')
          .onClick(() => { this.objectFit = ImageFit.Cover })
          .fontSize(11)
        Button('Contain')
          .onClick(() => { this.objectFit = ImageFit.Contain })
          .fontSize(11)
        Button('Fill')
          .onClick(() => { this.objectFit = ImageFit.Fill })
          .fontSize(11)
        Button('圆角0')
          .onClick(() => { this.borderRadius = 0 })
          .fontSize(11)
        Button('圆角12')
          .onClick(() => { this.borderRadius = 12 })
          .fontSize(11)
      }
      .padding({ left: 16, right: 16, bottom: 8 })

      Grid() {
        ForEach(this.GRID_IMAGES.slice(0, this.imageCount), (img: Resource, index: number) => {
          GridItem() {
            Column() {
              Image(img)
                .width('100%')
                .height(120)
                .objectFit(this.objectFit)
                .borderRadius(this.borderRadius)
                .border({ width: 1, color: Color.Gray })

              Text(`图${index + 1}`)
                .fontSize(12)
                .fontColor(Color.Gray)
                .margin({ top: 4 })
            }
            .padding(4)
          }
        })
      }
      .columnsTemplate(`repeat(${this.columnsCount}, 1fr)`)
      .rowsGap(8)
      .columnsGap(8)
      .padding(16)
      .layoutWeight(1)
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#F5F5F5')
  }
}

/** 原 049：Stack 容器层叠 */
@Component
struct ImageInStackTestCase049 {
  @State currentLayoutIndex: number = 0

  private readonly STACK_CONFIGS: Array<{ name: string; zOrders: number[] }> = [
    { name: '三图层叠(0,1,2)', zOrders: [0, 1, 2] },
    { name: '三图反转(2,1,0)', zOrders: [2, 1, 0] },
    { name: '等z序(0,0,0)', zOrders: [0, 0, 0] },
    { name: '中间突出(0,2,0)', zOrders: [0, 2, 0] }
  ]

  build() {
    Column() {
      Text('Image在Stack容器中测试')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 16 })

      Stack() {
        Image($r('app.media.startIcon'))
          .width(120)
          .height(120)
          .zIndex(this.STACK_CONFIGS[this.currentLayoutIndex].zOrders[0])
          .border({ width: 3, color: Color.Red })
          .borderRadius(8)

        Image($r('app.media.background'))
          .width(80)
          .height(80)
          .zIndex(this.STACK_CONFIGS[this.currentLayoutIndex].zOrders[1])
          .border({ width: 3, color: Color.Blue })
          .borderRadius(8)
          .position({ x: 20, y: 20 })

        Image($r('app.media.foreground'))
          .width(40)
          .height(40)
          .zIndex(this.STACK_CONFIGS[this.currentLayoutIndex].zOrders[2])
          .border({ width: 3, color: Color.Green })
          .borderRadius(8)
          .position({ x: 40, y: 40 })
      }
      .width(160)
      .height(160)
      .margin({ bottom: 16 })

      Text(`当前布局: ${this.STACK_CONFIGS[this.currentLayoutIndex].name}`)
        .fontSize(14)
        .fontColor(Color.Gray)
        .margin({ bottom: 8 })

      Row({ space: 12 }) {
        ForEach(this.STACK_CONFIGS, (config: { name: string; zOrders: number[] }, index: number) => {
          Button(config.name)
            .fontSize(10)
            .onClick(() => { this.currentLayoutIndex = index })
            .backgroundColor(index === this.currentLayoutIndex ? '#2196F3' : '#EEEEEE')
        })
      }

      Divider()
        .margin({ top: 16, bottom: 16 })

      Text('叠加透明度演示')
        .fontSize(14)
        .fontWeight(FontWeight.Medium)
        .margin({ bottom: 8 })

      Stack() {
        Image($r('app.media.startIcon'))
          .width(100)
          .height(100)
          .opacity(1)

        Image($r('app.media.background'))
          .width(100)
          .height(100)
          .opacity(0.7)
          .blendMode(BlendMode.SRC_OVER)
      }
      .width(100)
      .height(100)
    }
    .width('100%')
    .height('100%')
    .padding(16)
  }
}

/** 原 052：Swiper 轮播 */
@Component
struct ImageSwiperTestCase052 {
  @State autoPlay: boolean = true
  @State loop: boolean = true
  @State vertical: boolean = false
  @State currentIndex: number = 0
  @State interval: number = 2000

  private sources: Array<Resource> = [
    $r('app.media.startIcon'),
    $r('app.media.background'),
    $r('app.media.foreground')
  ]

  build() {
    Column({ space: 12 }) {
      Text('Image Swiper轮播测试')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)

      Swiper() {
        ForEach(this.sources, (src: Resource, idx: number) => {
          Image(src)
            .width('100%')
            .height(220)
            .objectFit(ImageFit.Cover)
            .borderRadius(12)
        }, (src: Resource) => `${src.id}`)
      }
      .index(this.currentIndex)
      .indicator(this.vertical ? Indicator.dot().right(8) : Indicator.dot().bottom(8))
      .autoPlay(this.autoPlay)
      .interval(this.interval)
      .loop(this.loop)
      .vertical(this.vertical)
      .duration(400)
      .onChange((index: number) => { this.currentIndex = index })
      .width('100%')
      .height(240)

      Text(`当前第 ${this.currentIndex + 1} / ${this.sources.length} 张`)
        .fontSize(13)
        .fontColor(Color.Gray)

      Row({ space: 8 }) {
        Button(this.autoPlay ? '自动播放:开' : '自动播放:关')
          .fontSize(11)
          .onClick(() => { this.autoPlay = !this.autoPlay })
        Button(this.loop ? '循环:开' : '循环:关')
          .fontSize(11)
          .onClick(() => { this.loop = !this.loop })
        Button(this.vertical ? '方向:竖' : '方向:横')
          .fontSize(11)
          .onClick(() => { this.vertical = !this.vertical })
      }

      Row({ space: 8 }) {
        Button('上一张')
          .fontSize(11)
          .onClick(() => { this.currentIndex = (this.currentIndex - 1 + this.sources.length) % this.sources.length })
        Button('下一张')
          .fontSize(11)
          .onClick(() => { this.currentIndex = (this.currentIndex + 1) % this.sources.length })
        Button('加速')
          .fontSize(11)
          .onClick(() => { this.interval = Math.max(500, this.interval - 500) })
        Button('减速')
          .fontSize(11)
          .backgroundColor('#FF6666')
          .onClick(() => { this.interval = Math.min(6000, this.interval + 500) })
      }
    }
    .width('100%')
    .height('100%')
    .padding(16)
  }
}

/** 原 053：WaterFlow 瀑布流 */
@Component
struct ImageWaterFlowTestCase053 {
  @State columns: number = 2
  @State scrolledIndex: number = -1
  private data: WaterFlowDataSource = new WaterFlowDataSource(20)

  build() {
    Column({ space: 12 }) {
      Text('Image WaterFlow瀑布流测试')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)

      Row({ space: 8 }) {
        Button('2列')
          .fontSize(11)
          .backgroundColor(this.columns === 2 ? '#007DFF' : '#E0E0E0')
          .onClick(() => { this.columns = 2 })
        Button('3列')
          .fontSize(11)
          .backgroundColor(this.columns === 3 ? '#007DFF' : '#E0E0E0')
          .onClick(() => { this.columns = 3 })
        Button('追加10')
          .fontSize(11)
          .onClick(() => { this.data.append(10) })
        Button('清空')
          .fontSize(11)
          .backgroundColor('#FF6666')
          .onClick(() => { this.data.clear() })
      }

      WaterFlow() {
        LazyForEach(this.data, (height: number, idx: number) => {
          FlowItem() {
            Column() {
              Image($r('app.media.startIcon'))
                .width('100%')
                .height(height)
                .objectFit(ImageFit.Cover)
                .borderRadius(8)
              Text(`#${idx + 1}  高${height}`)
                .fontSize(10)
                .fontColor(Color.Gray)
                .margin({ top: 4 })
            }
          }
        }, (height: number) => `${height}`)
      }
      .columnsTemplate(this.columns === 2 ? '1fr 1fr' : '1fr 1fr 1fr')
      .columnsGap(8)
      .rowsGap(8)
      .padding(4)
      .layoutWeight(1)
      .onScrollIndex((first: number, last: number) => { this.scrolledIndex = first })
      .backgroundColor('#F5F5F5')

      Text(`可视起始项: ${this.scrolledIndex < 0 ? '-' : this.scrolledIndex + 1}`)
        .fontSize(12)
        .fontColor(Color.Gray)
    }
    .width('100%')
    .height('100%')
    .padding(12)
  }
}

@Entry
@Component
struct ImageTestcaseContainers {
  @State currentIndex: number = 0

  build() {
    Column() {
      Tabs({ barPosition: BarPosition.Start, index: this.currentIndex }) {
        TabContent() { ImageInListTestCase047() }
          .tabBar('List')
        TabContent() { ImageInGridTestCase048() }
          .tabBar('Grid')
        TabContent() { ImageInStackTestCase049() }
          .tabBar('Stack')
        TabContent() { ImageSwiperTestCase052() }
          .tabBar('Swiper')
        TabContent() { ImageWaterFlowTestCase053() }
          .tabBar('WaterFlow')
      }
      .barMode(BarMode.Scrollable)
      .scrollable(true)
      .onChange((index: number) => { this.currentIndex = index })
    }
    .width('100%')
    .height('100%')
  }
}
