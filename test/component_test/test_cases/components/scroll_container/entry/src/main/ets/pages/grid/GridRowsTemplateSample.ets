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
// 测试代码路径
import gridRowsTemplateTest from '../MyTest/GridRowsTemplateTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct GridRowsTemplateSample {
  @State rowsTemplate: string = '1fr 1fr'

  aboutToAppear(): void {
    loadComponentTestEntry(gridRowsTemplateTest)
  }

  build() {
    Column() {
      Grid() {
        GridItem() {
          Text('gridRowsTemplateTest1')
            .backgroundColor(0xF9CF93)
        }

        GridItem() {
          Text('gridRowsTemplateTest2')
            .backgroundColor(0xF9CF93)
        }
      }.height('30%')
      .rowsTemplate(this.rowsTemplate)
      .id('gridRowsTemplate1')

      Button('GridRowsTemplate')
        .onClick(() => {
          this.rowsTemplate = '0fr'
        })

    }
  }
}