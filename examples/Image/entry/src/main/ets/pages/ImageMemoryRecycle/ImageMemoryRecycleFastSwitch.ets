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
 * @File: ImageMemoryRecycleFastSwitch.ets
 * @Description: Fast tab switching scenario test.
 * This demonstrates image memory recycling during rapid tab switching.
 * The test verifies that invisible images in inactive tabs are properly
 * recycled when switching between tabs quickly.
 */

class ImageItem {
  public id: string
  public index: number

  constructor(index: number) {
    this.id = `image_${index}`
    this.index = index
  }
}

@Entry
@Component
struct ImageMemoryRecycleFastSwitch {
  @State recycleEnabled: boolean = false
  @State tab1Items: ImageItem[] = []
  @State tab2Items: ImageItem[] = []
  @State tab3Items: ImageItem[] = []

  aboutToAppear() {
    this.recycleEnabled = true
    this.tab1Items = Array.from({ length: 4 }, (_, i) => new ImageItem(i + 1))
    this.tab2Items = Array.from({ length: 4 }, (_, i) => new ImageItem(i + 1))
    this.tab3Items = Array.from({ length: 4 }, (_, i) => new ImageItem(i + 1))
    const uiContext = this.getUIContext()
    if (uiContext) {
      uiContext.recycleInvisibleImageMemory(true)
    }
  }

  build() {
    Column() {
      Text('快速切换场景')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 10 })

      Text('验证快速切换时的图片回收')
        .fontSize(14)
        .fontColor('#666666')
        .margin({ bottom: 15 })

      Row() {
        Text('内存回收: ')
          .fontSize(16)
        Toggle({ type: ToggleType.Switch, isOn: this.recycleEnabled })
          .onChange((isOn: boolean) => {
            const uiContext = this.getUIContext()
            if (uiContext) {
              uiContext.recycleInvisibleImageMemory(isOn)
            }
          })
        Text(this.recycleEnabled ? '已开启' : '已关闭')
          .fontSize(14)
          .margin({ left: 10 })
          .fontColor(this.recycleEnabled ? '#ff0000' : '#00ff00')
      }
      .width('100%')
      .padding(12)
      .backgroundColor('#f0f0f0')
      .borderRadius(8)

      Text('说明: 快速切换标签页后上划退后台触发回收')
        .fontSize(12)
        .fontColor('#999999')
        .margin({ top: 10 })

      Tabs() {
        TabContent() {
          Column() {
            ForEach(this.tab1Items, (item: ImageItem) => {
              Image($r(`app.media.test${item.index % 3 + 1}`))
                .width(100)
                .height(100)
                .margin(10)
            }, (item: ImageItem) => item.id)
          }
          .width('100%')
          .height('100%')
          .justifyContent(FlexAlign.Center)
        }
        .tabBar('标签页1')

        TabContent() {
          Column() {
            ForEach(this.tab2Items, (item: ImageItem) => {
              Image($r(`app.media.test${item.index % 3 + 1}`))
                .width(100)
                .height(100)
                .margin(10)
            }, (item: ImageItem) => item.id)
          }
          .width('100%')
          .height('100%')
          .justifyContent(FlexAlign.Center)
        }
        .tabBar('标签页2')

        TabContent() {
          Column() {
            ForEach(this.tab3Items, (item: ImageItem) => {
              Image($r(`app.media.test${item.index % 3 + 1}`))
                .width(100)
                .height(100)
                .margin(10)
            }, (item: ImageItem) => item.id)
          }
          .width('100%')
          .height('100%')
          .justifyContent(FlexAlign.Center)
        }
        .tabBar('标签页3')
      }
      .width('100%')
      .layoutWeight(1)
      .margin({ top: 20 })
      .barMode(BarMode.Fixed)
    }
    .width('100%')
    .height('100%')
    .padding(20)
    .backgroundColor('#ffffff')
  }
}
