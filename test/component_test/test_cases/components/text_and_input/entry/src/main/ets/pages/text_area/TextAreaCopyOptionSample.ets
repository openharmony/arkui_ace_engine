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
//测试代码路径
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'
import textAreaCopyOptionTest from '../MyTest/TextAreaCopyOptionTest'

@Entry
@Component
struct TextAreaCopyOptionSample {
  @State copyOptionValue: CopyOptions = CopyOptions.InApp

  aboutToAppear(): void {
    loadComponentTestEntry(textAreaCopyOptionTest)
  }

  build() {
    Column() {
      TextArea()
        .copyOption(CopyOptions.None)
        .id('textAreaCopyOption1')
      TextArea()
        .copyOption(this.copyOptionValue)
        .id('textAreaCopyOption2')
      Button('TextAreaCopyOption1')
        .onClick(() => {
          this.copyOptionValue = CopyOptions.LocalDevice
        })
      Button('TextAreaCopyOption2')
        .onClick(() => {
          this.copyOptionValue = CopyOptions.CROSS_DEVICE
        })
    }
  }
}