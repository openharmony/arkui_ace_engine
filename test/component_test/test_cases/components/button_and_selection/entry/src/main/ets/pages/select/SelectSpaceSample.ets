/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 // * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// 测试代码路径
import selectSpaceTest from '../MyTest/SelectSpaceTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct SelectSpaceSample {
  @State text: string = "Title"
  @State selectSpace: number | Resource = 50

  aboutToAppear(): void {
    loadComponentTestEntry(selectSpaceTest)
  }

  build() {
    Column() {
      Select([{ value: 'select1' },
        { value: 'select2' },])
        .value(this.text)
        .space('30px')
        .id('selectSpace1')
      Select([{ value: 'select1' },
        { value: 'select2' },])
        .value(this.text)
        .space(this.selectSpace)
        .id('selectSpace2')

      Button('SelectSpace').onClick(() => {
        this.selectSpace = $r('app.string.select_space')
      })
    }.width('100%')
  }
}