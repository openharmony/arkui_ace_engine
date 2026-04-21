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
 * @File: ImageMemoryRecycleRecovery.ets
 * @Description: Image recovery display test.
 * This demonstrates that images are properly restored after being
 * recycled when the app goes to background. The test verifies that
 * there is no white screen or placeholder when returning to foreground.
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
struct ImageMemoryRecycleRecovery {
  @State recycleEnabled: boolean = false
  @State imageItems: ImageItem[] = []

  aboutToAppear() {
    this.recycleEnabled = true
    this.imageItems = Array.from({ length: 3 }, (_, i) => new ImageItem(i + 1))
    const uiContext = this.getUIContext()
    if (uiContext) {
      uiContext.recycleInvisibleImageMemory(true)
    }
  }

  build() {
    Column() {
      Text('图片恢复显示测试')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 10 })

      Text('验证退后台回收后，再次进入界面图片是否能正常显示')
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

      Text('说明: 上划退后台，再返回前台验证图片是否正常显示')
        .fontSize(12)
        .fontColor('#999999')
        .margin({ top: 10 })

      Column() {
        Text('测试图片')
          .fontSize(16)
          .fontWeight(FontWeight.Bold)
          .margin({ bottom: 15 })

        Row() {
          ForEach(this.imageItems, (item: ImageItem) => {
            Image($r(`app.media.test${item.index}`))
              .width(100)
              .height(100)
              .objectFit(ImageFit.Cover)
              .borderRadius(8)
              .margin({ right: 10 })
          }, (item: ImageItem) => item.id)
        }
      }
      .width('100%')
      .padding(20)
      .margin({ top: 20 })
      .backgroundColor('#e8f5e9')
      .borderRadius(8)
      .layoutWeight(1)
    }
    .width('100%')
    .height('100%')
    .padding(20)
    .backgroundColor('#ffffff')
  }
}
