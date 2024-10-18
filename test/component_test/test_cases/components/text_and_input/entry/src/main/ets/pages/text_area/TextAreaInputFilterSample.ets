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
import textAreaInputFilterTest from '../MyTest/TextAreaInputFilterTest'

@Entry
@Component
struct TextAreaInputFilterSample {
  @State value: ResourceStr = '^[a-z]$'

  aboutToAppear(): void {
    loadComponentTestEntry(textAreaInputFilterTest)
  }

  build() {
    Column() {
      TextArea()
        .inputFilter(this.value, (value: string) => {
        })
        .id('textAreaInputFilter')
      Button('TextAreaInputFilter')
        .onClick(() => {
          this.value = $r("app.string.value_resource_str")
        })
    }
  }
}