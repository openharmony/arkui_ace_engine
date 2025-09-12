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
 * Demonstrates how to load images from URLs and handle errors or completion events.
 * It also includes functionality to clear the cache directory.
 */
import { fileIo, fileIo as fs, ListFileOptions } from '@kit.CoreFileKit';
import { BusinessError } from '@kit.BasicServicesKit';

@Entry
@Component
struct loadurlTest {
  @State renderMode: ImageRenderMode = ImageRenderMode.Original
  @State res: Resource | string = $r('app.media.app_icon_1')
  @State errorIf1: string = 'None'
  @State errorIf2: string = 'None'
  @State errorIf3: string = 'None'

  build() {
    Column() {
      Column() {
        Blank()
          .height(100)
        Text('LoadUrl: ' + this.errorIf1)
          .height(50)
          .width(300)
          .fontWeight(FontWeight.Bolder)
        Image('xxx.jpeg')//Please enter a specific URL for a network image.
          .width(100)
          .height(100)
          .onError((e) => {
            this.errorIf1 = e?.message
          })
          .onComplete((e) => {
            if (e?.loadingStatus) {
              this.errorIf1 = 'LoadSuccess.'
            }
            console.log('AceImage onComplete1 status = ' + e?.loadingStatus)
          })
        Divider()
        Text('Alt with $r resource: ' + this.errorIf2)
          .height(70)
          .width(300)
          .fontWeight(FontWeight.Bolder)
        Divider()
        Image('xxx.webp')//Please enter a specific URL for a network image.
          .alt($r('app.media.startIcon'))
          .height(100)
          .width(100)
          .onError((e) => {
            this.errorIf2 = e?.message
          })
          .onComplete((e) => {
            if (e?.loadingStatus) {
              this.errorIf2 = 'LoadSuccess.'
            }
            console.log('AceImage onComplete2 status = ' + e?.loadingStatus)
          })
        Divider()
        Text('svg?xxx : ' + this.errorIf3)
          .height(70)
          .width(300)
          .fontWeight(FontWeight.Bolder)
        Divider()
        Image('xxx.svg')//Please enter a specific URL for a network image.
          .height(100)
          .width(100)
          .onError((e) => {
            this.errorIf3 = e?.message
          })
          .onComplete((e) => {
            if (e?.loadingStatus) {
              this.errorIf3 = 'LoadSuccess.'
            }
            console.log('AceImage onComplete3 status = ' + e?.loadingStatus)
          })
        Divider()
        Button('ClearCache')
          .onClick(() => {
            try {
              let cacheDir = this.getUIContext().getHostContext()?.cacheDir;
              let fileNames = fs.listFileSync(cacheDir)
              console.info(`AceImage, fileName: ${cacheDir}`)
              for (let i = 0; i < fileNames.length; i++) {
                try {
                  fs.unlink(cacheDir + '/' + fileNames[i])
                  console.info(`AceImage, fileName: ${cacheDir}/${fileNames[i]}`)
                } catch (err) {
                  console.log('AceImage FileUtils deleteFile Method has error, err msg=' +
                  (err as BusinessError).message + ' err code=' +
                  (err as BusinessError).code);
                }
              }
            } catch (err) {
              console.log('AceImage FileUtils deleteFile Method has error, err msg=' +
              (err as BusinessError).message + ' err code=' +
              (err as BusinessError).code);
            }
          })
      }
    }
    .height('100%')
    .width('100%')
  }
}