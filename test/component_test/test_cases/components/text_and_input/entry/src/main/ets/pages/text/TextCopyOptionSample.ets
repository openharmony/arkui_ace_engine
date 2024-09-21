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
import textCopyOptionTest from '../MyTest/TextCopyOptionTest'

@Entry
@Component
struct TextCopyOptionSample {
  @State copyOptionsValue: CopyOptions = CopyOptions.CROSS_DEVICE

  aboutToAppear(): void {
    loadComponentTestEntry(textCopyOptionTest)
  }

  build() {
    Column() {
      Text('text')
        .copyOption(this.copyOptionsValue)
        .id('textCopyOption1')
      Text('text')
        .copyOption(CopyOptions.None)
        .id('textCopyOption2')
      Button('TextCopyOption1')
        .onClick(() => {
          this.copyOptionsValue = CopyOptions.InApp
        })
      Button('TextCopyOption2')
        .onClick(() => {
          this.copyOptionsValue = CopyOptions.LocalDevice
        })
      Divider().color('#000000')
    }
  }
}