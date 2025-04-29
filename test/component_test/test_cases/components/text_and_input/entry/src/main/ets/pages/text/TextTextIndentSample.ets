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
import textTextIndentTest from '../MyTest/TextTextIndentTest'

@Entry
@Component
struct TextTextIndentSample {
  @State textIndentValue: Length = 100

  aboutToAppear(): void {
    loadComponentTestEntry(textTextIndentTest)
  }

  build() {
    Column() {
      Text('textIndent')
        .textIndent($r('app.string.fp_text'))
        .id('textTextIndent1')
      Text('textIndent')
        .textIndent(this.textIndentValue)
        .id('textTextIndent2')
      Button('TextTextIndent')
        .onClick(() => {
          this.textIndentValue = '200px'
        })
    }
  }
}