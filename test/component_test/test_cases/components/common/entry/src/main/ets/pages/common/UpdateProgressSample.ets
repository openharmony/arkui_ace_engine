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

import updateProgressTest from '../MyTest/UpdateProgressTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct UpdateProgressSample {
  @State progressFlag1: boolean = true;
  @State progress: ProgressMask = new ProgressMask(10.0, 100.0, Color.Gray);
  @State value: number = 10.0;

  aboutToAppear(): void {
    loadComponentTestEntry(updateProgressTest)
  }

  build() {
    Column() {
      Image($r('app.media.app_icon'))
        .width('500px').height('280px')
        .id('imageUpdateProgress1')
        .mask(this.progress)

      Button('ButtonUpdateProgress')
        .onClick((event?: ClickEvent) => {
          this.value += 10;
          this.progress.updateProgress(this.value);
        }).width(200).height(50).margin(20)
    }
  }
}

