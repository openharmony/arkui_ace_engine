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
 * This component demonstrates how to load and display a remote image with error and completion handling.
 * It uses the Image component to load an image from a URL, and listens for events such as onError and onComplete
 * to update the UI state and display the loading status or error message.
 */

@Entry
@Component
struct ImageNoAccessPage {
  @State renderMode: ImageRenderMode = ImageRenderMode.Original
  @State res: Resource | string = $r('app.media.app_icon')
  @State errorIf1: string = 'None'

  async aboutToAppear() {
    cacheDownload.download('xxx.jpg', {})// 填写具体网络图片地址
  }

  build() {
    Column() {
      Text('LoadUrl: ' + this.errorIf1)

      Image('xxx.jpg')// 填写具体网络图片地址
        .width(100)
        .height(100)
        .onError((e) => {
          this.errorIf1 = e?.message
          console.log('zlh error: ' + e.message)
        })
        .onComplete((e) => {
          if (e?.loadingStatus) {
            this.errorIf1 = 'LoadSuccess.'
          }
          console.log('AceImage onComplete1 status = ' + e?.loadingStatus)
        })
    }
    .height('100%')
    .width('100%')
  }
}