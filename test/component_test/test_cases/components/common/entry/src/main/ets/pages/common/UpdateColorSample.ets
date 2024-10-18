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

import updateColorTest from '../MyTest/UpdateColorTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct UpdateColorSample {
  @State progressFlag1: boolean = true;
  @State progress: ProgressMask = new ProgressMask(10.0, 100.0, Color.Gray);
  @State updateColorValue: ResourceColor = 0x9fff0000

  aboutToAppear(): void {
    loadComponentTestEntry(updateColorTest)
  }

  build() {
    Column() {
      Image($r('app.media.app_icon'))
        .width('500px').height('280px')
        .id('progressUpdateColor1')
        .mask(this.progress)

      Button('ButtonUpdateColor1')
        .onClick((event?: ClickEvent) => {
          if (this.progressFlag1) {
            this.progress.updateColor(this.updateColorValue);
          } else {
            this.progress.updateColor(Color.Brown);
          }
          this.progressFlag1 = !this.progressFlag1
        }).width(200).height(50).margin(20)

      Button('ButtonUpdateColor2')
        .onClick(() => {
          this.progress.updateColor('#99182431');
        })
      Button('ButtonUpdateColor3')
        .onClick(() => {
          this.progress.updateColor($r('sys.color.ohos_id_color_text_hyperlink'))
        })
    }
  }
}

