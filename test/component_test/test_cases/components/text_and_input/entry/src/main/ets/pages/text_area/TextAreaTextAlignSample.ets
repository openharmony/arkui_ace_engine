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
import textAreaTextAlignTest from '../MyTest/TextAreaTextAlignTest'

@Entry
@Component
struct TextAreaTextAlignSample {
  @State textAlign: TextAlign = TextAlign.Center

  aboutToAppear(): void {
    loadComponentTestEntry(textAreaTextAlignTest)
  }

  build() {
    Column() {
      TextArea()
        .textAlign(TextAlign.Start)
        .id('textAreaTextAlign1')
      TextArea()
        .textAlign(this.textAlign)
        .id('textAreaTextAlign2')
      Button('TextAreaTextAlign1')
        .onClick(() => {
          this.textAlign = TextAlign.End
        })
      Button('TextAreaTextAlign2')
        .onClick(() => {
          this.textAlign = TextAlign.JUSTIFY
        })
    }
  }
}