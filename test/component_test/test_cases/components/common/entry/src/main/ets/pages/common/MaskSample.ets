/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
import maskTest from '../MyTest/MaskTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct MaskSample {
  @State progress: ProgressMask = new ProgressMask(10.0, 100.0, Color.Gray);
  @State maskType: CircleAttribute | PathAttribute | EllipseAttribute | RectAttribute = new Circle({
    width: '500px',
    height: '280px'
  }).fill(Color.Gray);

  aboutToAppear(): void {
    loadComponentTestEntry(maskTest)
  }

  build() {
    Column() {
      Text('progress mask')
        .fontSize(12)
        .width('75%')
        .fontColor(0x000000)
        .mask(this.progress)
        .id('textMask1')
      Button('ButtonTextMask1')
        .onClick(() => {
          this.progress = new ProgressMask(10.0, 100.0, 0xffffff)
        })
      Button('ButtonTextMask2')
        .onClick(() => {
          this.progress = new ProgressMask(10.0, 100.0, 'rgb(255, 100, 255)')
        })
      Button('ButtonTextMask3')
        .onClick(() => {
          this.progress = new ProgressMask(10.0, 100.0, $r('app.color.start_window_background'))
        })
      Image($r('app.media.app_icon'))
        .width('500px')
        .height('280px')
        .margin({ bottom: 30 })
        .mask(this.maskType)
        .id('imageMask1')
      Button('ButtonTextMask4')
        .onClick(() => {
          this.maskType = new Rect({ width: '500px', height: '280px' }).fill(Color.Gray)
        })
      Button('ButtonTextMask5')
        .onClick(() => {
          this.maskType = new Path({ width: '50px', height: '280px' }).fill(Color.Gray)
        })
      TextArea({ text: 'test' })
        .width('500px')
        .height('280px')
        .margin({ bottom: 10 })
        .mask(new Ellipse({ width: '250px', height: '280px' }).fill(Color.Gray))
        .id('textAreaMask1')
    }
  }
}