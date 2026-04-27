/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
 * reloadKey example: demonstrates using reloadKey to force image reload from file path.
 * When reloadKey changes, the image is reloaded without using cache.
 * When file path changes, the image follows normal loading flow with cache.
 */
@Entry
@Component
struct ImageReloadKeyExample {
  @State reloadKey: string = 'initial'
  @State filePath: string = '/data/storage/el2/base/files/test.png'
  @State loadCount: number = 0

  build() {
    Scroll() {
      Column({ space: 15 }) {
        Text('Image reloadKey Example')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20 })

        Text('file: ' + this.filePath)
          .fontSize(12)
          .fontColor('#666666')
          .maxLines(2)
          .textOverflow({ overflow: TextOverflow.Ellipsis })

        Text('reloadKey: ' + this.reloadKey)
          .fontSize(14)
          .fontColor('#666666')

        Text('Load count: ' + this.loadCount)
          .fontSize(14)
          .fontColor('#666666')

        // Image with reloadKey - when reloadKey changes, image is reloaded bypassing cache
        Image('file://' + this.filePath, this.reloadKey)
          .width(200)
          .height(200)
          .objectFit(ImageFit.Cover)
          .border({ width: 1, color: '#cccccc' })
          .onComplete(() => {
            this.loadCount++
          })

        Button('Change reloadKey to force reload')
          .width('80%')
          .onClick(() => {
            this.reloadKey = 'reload_' + Date.now().toString()
          })

        Button('Change file path (normal flow with cache)')
          .width('80%')
          .onClick(() => {
            this.filePath = '/data/storage/el2/base/files/test_v2.png'
          })

        // Image without reloadKey - normal loading behavior
        Text('Image without reloadKey (normal behavior):')
          .fontSize(16)
          .margin({ top: 20 })

        Image($r('app.media.startIcon'))
          .width(200)
          .height(200)
          .objectFit(ImageFit.Cover)
          .border({ width: 1, color: '#cccccc' })
      }
      .width('100%')
      .padding(15)
    }
    .height('100%')
    .width('100%')
  }
}
