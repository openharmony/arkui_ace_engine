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
import dividerStrokeWidthTest from '../MyTest/DividerStrokeWidthTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct DividerStrokeWidthSample {
  @State dividerStrokeWidth: number | string = 50

  aboutToAppear(): void {
    loadComponentTestEntry(dividerStrokeWidthTest)
  }

  build() {
    Column() {
      Text('DividerVertical1')
      Divider().strokeWidth(this.dividerStrokeWidth).id('dividerStrokeWidth1')
      Text('DividerVertical2')
      Divider().strokeWidth(5000).height(20).id('dividerStrokeWidth2')
      Button('DividerStrokeWidth').onClick(() => {
        this.dividerStrokeWidth = '200vp'
      })
    }.width('100%')
  }
}