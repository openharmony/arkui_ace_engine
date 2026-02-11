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
 * @File: ImageMemoryRecycleMultiResource.ets
 * @Description: Multiple resource type background recovery test.
 * This demonstrates image memory recycling with different resource types:
 * - Resource: App resources ($r('app.media.xxx'))
 * - PixelMap: PixelMap objects created from raw file data
 * - Base64: Base64 encoded image strings
 * - Network: Images loaded from HTTP/HTTPS URLs
 */

import image from '@ohos.multimedia.image'

@Entry
@Component
struct ImageMemoryRecycleMultiResource {
  @State recycleEnabled: boolean = false
  @State currentType: string = 'resource'
  @State pixelMap: image.PixelMap | undefined = undefined

  aboutToAppear() {
    this.recycleEnabled = true
    const uiContext = this.getUIContext()
    if (uiContext) {
      uiContext.recycleInvisibleImageMemory(true)
    }
    this.loadPixelMap()
  }

  async loadPixelMap() {
    try {
      const resourceMgr = getContext(this).resourceManager
      const fileData = await resourceMgr.getRawFileContent('test1.png')
      const imageSource = image.createImageSource(fileData.buffer)
      this.pixelMap = await imageSource.createPixelMap()
    } catch (error) {
      console.error('Failed to create PixelMap:', JSON.stringify(error))
    }
  }

  build() {
    Column() {
      Text('多种资源类型退后台恢复测试')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 10 })

      Text('验证不同资源类型在退后台后能否正常恢复显示')
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
      }
      .width('100%')
      .padding(12)
      .backgroundColor('#f0f0f0')
      .borderRadius(8)

      Row() {
        Button('Resource').onClick(() => { this.currentType = 'resource' })
        Button('PixelMap').onClick(() => { this.currentType = 'pixelmap' })
        Button('Base64').onClick(() => { this.currentType = 'base64' })
        Button('Network').onClick(() => { this.currentType = 'network' })
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceEvenly)
      .padding(16)
      .margin({ top: 20 })

      Column() {
        if (this.currentType === 'resource') {
          Image($r('app.media.test1'))
            .width(200)
            .height(200)
        } else if (this.currentType === 'pixelmap' && this.pixelMap) {
          Image(this.pixelMap)
            .width(200)
            .height(200)
            .onComplete(() => {
              if (this.pixelMap) {
                this.pixelMap.release()
                this.pixelMap = undefined
              }
            })
        } else if (this.currentType === 'base64') {
          Image('data:image/png;base64,<BASE64_DATA>')
            .width(200)
            .height(200)
        } else if (this.currentType === 'network') {
          Image('https://www.example.com/test.png')
            .width(200)
            .height(200)
        }
      }
      .layoutWeight(1)
      .width('100%')
      .margin({ top: 20 })

      Text('说明: 只有上划退后台才会触发回收')
        .fontSize(12)
        .fontColor('#999999')
    }
    .width('100%')
    .height('100%')
    .padding(20)
  }
}
