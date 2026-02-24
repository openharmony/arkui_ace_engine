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
 * @File: ImageMemoryRecycleCustomComponent.ets
 * @Description: Image memory recycling test in custom components.
 * This demonstrates how images in custom components are recycled when the component
 * visibility is toggled. The test verifies memory recovery when custom components
 * are shown/hidden.
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
struct ImageMemoryRecycleCustomComponent {
  @State recycleEnabled: boolean = false
  @State showImages: boolean = true
  @State imageItems: ImageItem[] = []

  aboutToAppear() {
    this.recycleEnabled = true
    this.imageItems = Array.from({ length: 6 }, (_, i) => new ImageItem(i + 1))
    const uiContext = this.getUIContext()
    if (uiContext) {
      uiContext.recycleInvisibleImageMemory(true)
    }
  }

  build() {
    Column() {
      Text('自定义组件中的图片')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 10 })

      Text('验证自定义组件中图片的回收')
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

      Text('说明: 切换显示状态后上划退后台触发回收')
        .fontSize(12)
        .fontColor('#999999')
        .margin({ top: 10 })

      Button(this.showImages ? '隐藏组件' : '显示组件')
        .onClick(() => {
          this.showImages = !this.showImages
        })
        .margin({ top: 20, bottom: 20 })

      if (this.showImages) {
        Column() {
          Text('图片列表')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
            .margin({ bottom: 15 })

          Flex({ wrap: FlexWrap.Wrap }) {
            ForEach(this.imageItems, (item: ImageItem) => {
              Column() {
                Image($r(`app.media.test${item.index % 3 + 1}`))
                  .width(120)
                  .height(120)
                  .objectFit(ImageFit.Cover)
                  .borderRadius(8)
                Text(`图片 ${item.index}`)
                  .fontSize(14)
                  .fontWeight(FontWeight.Bold)
                  .margin({ top: 8 })
              }
              .padding(12)
              .backgroundColor('#ffffff')
              .borderRadius(8)
              .margin({ right: 10, bottom: 10 })
            }, (item: ImageItem) => item.id)
          }
        }
        .width('100%')
        .padding(20)
        .backgroundColor('#e8f5e9')
        .borderRadius(8)
        .layoutWeight(1)
      } else {
        Column() {
          Text('图片已隐藏')
            .fontSize(16)
            .fontColor('#999999')
        }
        .width('100%')
        .height(200)
        .justifyContent(FlexAlign.Center)
        .backgroundColor('#f5f5f5')
        .borderRadius(8)
        .layoutWeight(1)
      }
    }
    .width('100%')
    .height('100%')
    .padding(20)
    .backgroundColor('#ffffff')
  }
}
