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

import progressMaskTest from '../MyTest/ProgressMaskTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ProgressMaskSample {
  index: number = 0
  progressArr: ProgressMask[] = [new ProgressMask(10.0, 100.0, 'rgb(72 61 139)'),
    new ProgressMask(10.0, 100.0, 0X528B8B),
    new ProgressMask(10.0, 100.0, Color.Red),
    new ProgressMask(10.0, 100.0, $r('sys.color.ohos_id_color_text_hyperlink'))]
  @State progress: ProgressMask = this.progressArr[this.index]

  aboutToAppear(): void {
    loadComponentTestEntry(progressMaskTest)
  }

  build() {
    Column({ space: 15 }) {
      Image($r('app.media.app_icon'))
        .id('imageProgressMask')
        .width(100)
        .height(100)
        .mask(this.progress)
        .animation({
          duration: 2000,
          curve: Curve.Linear,
          delay: 0,
          iterations: 1,
          playMode: PlayMode.Normal
        })

      Button('ButtonProgressMask')
        .onClick(() => {
          this.index++
          this.progress = this.progressArr[this.index % 4]
        })
    }
  }
}