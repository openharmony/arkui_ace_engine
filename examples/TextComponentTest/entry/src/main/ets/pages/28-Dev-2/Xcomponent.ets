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

import { BusinessError } from '@ohos.base';
@Entry
@Component
struct ImageAnalyzerExample {
  @State text: string = ''
  @State enableAnalyzer: boolean = true
  controller: VideoController = new VideoController()
  xComponentController: XComponentController = new XComponentController()
  private config: ImageAnalyzerConfig = {
    types: [ImageAnalyzerType.SUBJECT, ImageAnalyzerType.TEXT]
  }
  private aiController: ImageAnalyzerController = new ImageAnalyzerController()
  private options: ImageAIOptions = {
    types: [ImageAnalyzerType.SUBJECT, ImageAnalyzerType.TEXT],
    aiController: this.aiController
  }

  build() {
    Column() {
      Text(this.text)
      XComponent({
        id: 'xcomponent',
        type: XComponentType.COMPONENT,
        imageAIOptions: this.options,
        controller: this.xComponentController
      }) {
        Video({
          src: $rawfile('video1.mp4'),
          controller: this.controller,
          imageAIOptions: this.options
        })
          .width(250)
          .height(250)
      }
      .enableAnalyzer(this.enableAnalyzer)
      .width(250)
      .height(250)

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

      Button('start')
        .width(150)
        .onClick(() => {
          this.xComponentController.startImageAnalyzer(this.config)
            .then(() => {
              console.log('analysis complete')
            })
            .catch((error: BusinessError) => {
              console.log('error code: ' + error.code)
            })
        })
      Button('stop')
        .width(150)
        .onClick(() => {
          this.xComponentController.stopImageAnalyzer()
        })
    }
    .width("100%")
  }
}