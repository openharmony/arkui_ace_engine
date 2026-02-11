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
 * @File: ImageMemoryRecycleComprehensive.ets
 * @Description: Comprehensive scenario test for image memory recycling.
 * This demonstrates memory recycling with multiple resource types and complex interactions.
 * The test includes List, Grid, and large image scenarios within a Tab component.
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
struct ImageMemoryRecycleComprehensive {
  @State recycleEnabled: boolean = false
  @State listItems: ImageItem[] = []
  @State gridItems: ImageItem[] = []
  @State largeItems: ImageItem[] = []

  aboutToAppear() {
    this.recycleEnabled = true
    this.listItems = Array.from({ length: 20 }, (_, i) => new ImageItem(i + 1))
    this.gridItems = Array.from({ length: 30 }, (_, i) => new ImageItem(i + 1))
    this.largeItems = Array.from({ length: 5 }, (_, i) => new ImageItem(i + 1))
    const uiContext = this.getUIContext()
    if (uiContext) {
      uiContext.recycleInvisibleImageMemory(true)
    }
  }

  build() {
    Column() {
      Text('综合场景测试')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 10 })

      Text('多种资源类型和复杂交互场景')
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

      Text('说明: 切换标签页或滚动后上划退后台触发回收')
        .fontSize(12)
        .fontColor('#999999')
        .margin({ top: 10 })

      Tabs() {
        TabContent() {
          Scroll() {
            Column() {
              ForEach(this.listItems, (item: ImageItem) => {
                Row() {
                  Image($r(`app.media.test${item.index % 3 + 1}`))
                    .width(60)
                    .height(60)
                    .objectFit(ImageFit.Cover)
                    .borderRadius(8)
                    .margin({ right: 12 })
                  Text(`列表项 ${item.index + 1}`)
                    .fontSize(14)
                }
                .width('100%')
                .padding(12)
                .backgroundColor(item.index % 2 === 0 ? '#ffffff' : '#f9f9f9')
                .borderRadius(8)
                .margin({ bottom: 8 })
              }, (item: ImageItem) => item.id)
            }
            .width('100%')
            .padding(16)
          }
          .width('100%')
          .height('100%')
        }
        .tabBar('列表')

        TabContent() {
          Grid() {
            ForEach(this.gridItems, (item: ImageItem) => {
              GridItem() {
                Column() {
                  Image($r(`app.media.test${item.index % 3 + 1}`))
                    .width(80)
                    .height(80)
                    .objectFit(ImageFit.Cover)
                    .borderRadius(8)
                  Text(`图片${item.index + 1}`)
                    .fontSize(12)
                    .margin({ top: 8 })
                }
              }
            }, (item: ImageItem) => item.id)
          }
          .columnsTemplate('1fr 1fr 1fr')
          .rowsGap(10)
          .columnsGap(10)
          .width('100%')
          .height('100%')
          .padding(16)
        }
        .tabBar('网格')

        TabContent() {
          Scroll() {
            Column() {
              ForEach(this.largeItems, (item: ImageItem) => {
                Column() {
                  Image($r(`app.media.test${item.index % 3 + 1}`))
                    .width('100%')
                    .height(300)
                    .objectFit(ImageFit.Contain)
                    .borderRadius(8)
                  Text(`大图 ${item.index}`)
                    .fontSize(16)
                    .fontWeight(FontWeight.Bold)
                    .margin({ top: 10 })
                }
                .margin({ bottom: 30 })
              }, (item: ImageItem) => item.id)
            }
            .width('100%')
            .padding(16)
          }
          .width('100%')
          .height('100%')
        }
        .tabBar('大图')
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
