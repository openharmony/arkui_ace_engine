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

/*
 * This component demonstrates how to preload and display various types of image resources from the network,
 * including PNG, JPG, JPEG, WEBP, SVG, and GIF formats. It also includes error handling for each image type and 
 * displays the loading status or error message accordingly.
 * Additionally, it shows how to use a cache download mechanism to pre-cache images before they are displayed.
 */

import cacheDownload from '@ohos.request.cacheDownload';

interface ImageCompleteData {
  width: number,
  height: number
}

@Entry
@Component
struct ImagePreLoadAllTypesPage {
  @State renderMode: ImageRenderMode = ImageRenderMode.Original
  @State res: Resource | string = $r('app.media.app_icon')
  @State errorIf1: string = 'None'
  @State errorIf2: string = 'None'
  @State errorIf3: string = 'None'
  @State errorIf4: string = 'None'
  @State errorIf5: string = 'None'
  @State errorIf6: string = 'None'
  @State errorIf7: string = 'None'
  @State errorIf8: string = 'None'

  async aboutToAppear() {
    cacheDownload.download('xxx.png', {})// 填写具体网络图片地址
    cacheDownload.download('xxx.jpg', {})// 填写具体网络图片地址
    cacheDownload.download('xxx.jpeg', {})// 填写具体网络图片地址
    cacheDownload.download('xxx.webp', {})// 填写具体网络图片地址
    cacheDownload.download('xxx.svg', {})// 填写具体网络图片地址
    cacheDownload.download('xxx.gif', {})// 填写具体网络图片地址
    cacheDownload.download('xxx.com', {})// 填写具体网络地址
  }

  build() {
    Column() {
      Text('网络图片资源png，可以显示：' + this.errorIf1)
      Image('xxx.png').width(50).height(50)// png
        .onError((e) => {
          this.errorIf1 = e?.message
        })
        .onComplete((e) => {
          if (e?.loadingStatus) {
            this.errorIf1 = 'LoadSuccess width:' + e?.width + ' height:' + e?.height
          }
          console.log('AceImage onComplete2 status = ' + e?.loadingStatus)
        })

      Text('网络图片资源jpg，可以显示：' + this.errorIf2)
      Image('xxx.jpg')
        .width(50)
        .height(50)// jpg
        .onError((e) => {
          this.errorIf2 = e?.message
        })
        .onComplete((e) => {
          if (e?.loadingStatus) {
            this.errorIf2 = 'LoadSuccess width:' + e?.width + ' height:' + e?.height
          }
          console.log('AceImage onComplete2 status = ' + e?.loadingStatus)
        })

      Text('网络图片资源jpeg，可以显示：' + this.errorIf3)
      Image('xxx.jpeg')
        .width(50)
        .height(50)// jpeg
        .onError((e) => {
          this.errorIf3 = e?.message
        })
        .onComplete((e) => {
          if (e?.loadingStatus) {
            this.errorIf3 = 'LoadSuccess width:' + e?.width + ' height:' + e?.height
          }
          console.log('AceImage onComplete2 status = ' + e?.loadingStatus)
        })

      Text('网络图片资源webp，可以显示：' + this.errorIf4)
      Image('xxx.webp')
        .width(50)
        .height(50)// webp
        .onError((e) => {
          this.errorIf4 = e?.message
        })
        .onComplete((e) => {
          if (e?.loadingStatus) {
            this.errorIf4 = 'LoadSuccess width:' + e?.width + ' height:' + e?.height
          }
          console.log('AceImage onComplete2 status = ' + e?.loadingStatus)
        })

      Text('网络图片资源gif，可以显示：' + this.errorIf5)
      Image('xxx.gif').width(50).height(50)// gif
        .onError((e) => {
          this.errorIf5 = e?.message
        })
        .onComplete((e) => {
          if (e?.loadingStatus) {
            this.errorIf5 = 'LoadSuccess width:' + e?.width + ' height:' + e?.height
          }
          console.log('AceImage onComplete2 status = ' + e?.loadingStatus)
        })

      Text('网络svg图片资源，可以显示：' + this.errorIf6)
      Image('xxx.svg').width(50)
        .onError((e) => {
          this.errorIf6 = e?.message
        })
        .onComplete((e) => {
          if (e?.loadingStatus) {
            this.errorIf6 = 'LoadSuccess width:' + e?.width + ' height:' + e?.height
          }
          console.log('AceImage onComplete2 status = ' + e?.loadingStatus)
        })

      Text('Alt with $r resource: ' + this.errorIf7)
      Image('xxx.webp')
        .alt($r('app.media.icon'))
        .height(50)
        .width(50)
        .onError((e) => {
          this.errorIf7 = e?.message
        })
        .onComplete((e) => {
          if (e?.loadingStatus) {
            this.errorIf7 = 'LoadSuccess width:' + e?.width + ' height:' + e?.height
          }
          console.log('AceImage onComplete2 status = ' + e?.loadingStatus)
        })

      Text('错误size《=0' + this.errorIf8)
      Image('xxx.com')
        .alt($r('app.media.icon'))
        .height(50)
        .width(50)
        .onError((e) => {
          this.errorIf8 = e?.message
        })
        .onComplete((e) => {
          if (e?.loadingStatus) {
            this.errorIf8 = 'LoadSuccess width:' + e?.width + ' height:' + e?.height
          }
          console.log('AceImage onComplete2 status = ' + e?.loadingStatus)
        })
    }
    .height('100%')
    .width('100%')
  }
}