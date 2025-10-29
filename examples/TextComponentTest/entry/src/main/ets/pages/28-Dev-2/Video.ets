/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

@Entry
@Component
struct VideoPage {
  @State text: string = ''
  controller: VideoController = new VideoController()
  types: Array<ImageAnalyzerType> = [ImageAnalyzerType.SUBJECT, ImageAnalyzerType.TEXT]
  aiController: ImageAnalyzerController = new ImageAnalyzerController();
  @State options: ImageAIOptions = { types: this.types, aiController: this.aiController }
  @State enableAnalyzer: boolean = true

  build() {
    Column() {
      Video({
        src: $rawfile('video1.mp4'),
        controller: this.controller,
        imageAIOptions: this.options
      })
        .enableAnalyzer(this.enableAnalyzer)
        .width(250)
        .height(250)

      Text(this.text)

      Row() {
        Button('start').onClick(() => {
          this.controller.start() // 开始播放
        }).margin(2)
        Button('pause').onClick(() => {
          this.controller.pause() // 暂停播放
        }).margin(2)
        Button('stop').onClick(() => {
          this.controller.stop() // 结束播放
        }).margin(2)
      }.width(300)

      Row() {
        Button('types: 空')
          .width(150)
          .onClick(() => {
            this.options = {
              types: [],
              aiController: this.aiController
            }
          })
        Button('types: SUBJECT')
          .width(150)
          .onClick(() => {
            this.options = {
              types: [ImageAnalyzerType.SUBJECT],
              aiController: this.aiController
            }
          })
      }.width(300)

      Row() {
        Button('types: TEXT')
          .width(150)
          .onClick(() => {
            this.options = {
              types: [ImageAnalyzerType.TEXT],
              aiController: this.aiController
            }
          })

        Button('types: [SUBJECT, TEXT]')
          .width(150)
          .onClick(() => {
            this.options = {
              types: [ImageAnalyzerType.SUBJECT, ImageAnalyzerType.TEXT],
              aiController: this.aiController
            }
          })
      }.width(300)

      Row() {
        Button('enableAnalyzer:' + this.enableAnalyzer)
          .width(150)
          .onClick(() => {
            this.enableAnalyzer = !this.enableAnalyzer
          })

        Button('getTypes')
          .width(150)
          .onClick(() => {
            this.text = JSON.stringify(this.aiController.getImageAnalyzerSupportTypes())
          })
      }.width(300)

    }
    .width('100%')
  }
}