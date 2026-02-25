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
 * @File: ImageMemoryRecycleList.ets
 * @Description: List scrolling and background recovery test.
 * This demonstrates image memory recycling in a List component.
 * The test verifies that images can be properly restored after being
 * recycled when the app goes to background.
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
struct ImageMemoryRecycleList {
  @State recycleEnabled: boolean = false
  @State imageList: Array<ImageItem> = []

  aboutToAppear() {
    this.recycleEnabled = true
    const uiContext = this.getUIContext<UIContext>()
    if (uiContext) {
      uiContext.recycleInvisibleImageMemory(true)
    }
    // 初始化图片列表数据
    this.imageList = Array.from({ length: 50 }, (_, i) => new ImageItem(i))
  }

  build() {
    Column() {
      Text('List滚动退后台测试')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 10 })

      Text('验证List中的图片在退后台后能否正常恢复显示')
        .fontSize(14)
        .fontColor('#666666')
        .margin({ bottom: 15 })

      Row() {
        Text('内存回收: ')
          .fontSize(16)
        Toggle({ type: ToggleType.Switch, isOn: this.recycleEnabled })
          .onChange((isOn: boolean) => {
            const uiContext = this.getUIContext<UIContext>()
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

      Text('说明: 只有上划退后台才会触发回收')
        .fontSize(12)
        .fontColor('#999999')
        .margin({ top: 10 })

      List() {
        ForEach(this.imageList, (item: ImageItem) => {
          ListItem() {
            Row() {
              Image($r(`app.media.test${item.index % 3 + 1}`))
                .width(100)
                .height(100)
                .borderRadius(8)
                .margin({ right: 16 })
              Text(`图片 ${item.index + 1}`)
                .fontSize(16)
            }
            .width('100%')
            .padding(16)
          }
        }, (item: ImageItem) => item.id)
      }
      .width('100%')
      .layoutWeight(1)
      .margin({ top: 10 })
    }
    .width('100%')
    .height('100%')
    .padding(20)
    .backgroundColor('#ffffff')
  }
}
