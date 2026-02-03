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
 * @File: ImageMemoryRecycleNestedScroll.ets
 * @Description: Nested scrolling scenario test.
 * This demonstrates image memory recycling in nested scroll containers.
 * The test uses Scroll containing Grid components to verify memory
 * recycling in complex nested scrolling scenarios.
 */

class ImageItem {
  public id: string
  public index: number

  constructor(index: number) {
    this.id = `image_${index}`
    this.index = index
  }
}

class GroupItem {
  public id: string
  public groupIndex: number

  constructor(groupIndex: number) {
    this.id = `group_${groupIndex}`
    this.groupIndex = groupIndex
  }
}

@Entry
@Component
struct ImageMemoryRecycleNestedScroll {
  @State recycleEnabled: boolean = false
  @State groupItems: GroupItem[] = []
  @State imageItems: ImageItem[] = []

  aboutToAppear() {
    this.recycleEnabled = true
    this.groupItems = Array.from({ length: 3 }, (_, i) => new GroupItem(i + 1))
    this.imageItems = Array.from({ length: 12 }, (_, i) => new ImageItem(i + 1))
    const uiContext = this.getUIContext()
    if (uiContext) {
      uiContext.recycleInvisibleImageMemory(true)
    }
  }

  build() {
    Column() {
      Text('嵌套滚动场景')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 10 })

      Text('验证嵌套滚动时的图片回收')
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

      Text('说明: 向下滚动查看更多图片')
        .fontSize(12)
        .fontColor('#999999')
        .margin({ top: 10 })

      Scroll() {
        Column() {
          ForEach(this.groupItems, (group: GroupItem) => {
            Column() {
              Text(`第${group.groupIndex}组图片`)
                .fontSize(16)
                .fontWeight(FontWeight.Bold)
                .width('100%')
                .margin({ bottom: 10 })

              Grid() {
                ForEach(this.imageItems, (item: ImageItem) => {
                  GridItem() {
                    Column() {
                      Image($r(`app.media.test${item.index % 3 + 1}`))
                        .width(80)
                        .height(80)
                        .objectFit(ImageFit.Cover)
                        .borderRadius(8)
                      Text(`图${item.index + 1}`)
                        .fontSize(12)
                        .margin({ top: 4 })
                    }
                  }
                }, (item: ImageItem) => item.id)
              }
              .columnsTemplate('1fr 1fr 1fr')
              .rowsGap(10)
              .columnsGap(10)
              .width('100%')
              .height(350)
              .backgroundColor('#f9f9f9')
              .padding(10)
              .borderRadius(8)
              .margin({ bottom: 20 })
            }
          }, (group: GroupItem) => group.id)
        }
        .width('100%')
        .padding({ left: 16, right: 16 })
      }
      .width('100%')
      .layoutWeight(1)
      .scrollable(ScrollDirection.Vertical)
      .scrollBar(BarState.Auto)
    }
    .width('100%')
    .height('100%')
    .padding(20)
    .backgroundColor('#ffffff')
  }
}
