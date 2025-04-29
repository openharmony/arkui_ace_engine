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
import gridColumnsTemplateTest from '../MyTest/GridColumnsTemplateTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct GridColumnsTemplateSample {
  @State columnsTemplate: string = '1fr 1fr'

  aboutToAppear(): void {
    loadComponentTestEntry(gridColumnsTemplateTest)
  }

  build() {
    Column() {
      Grid() {
        GridItem() {
          Text('gridColumnsTemplateTest1')
            .backgroundColor(0xF9CF93)
        }

        GridItem() {
          Text('gridColumnsTemplateTest2')
            .backgroundColor(0xF9CF93)
        }
      }.columnsTemplate(this.columnsTemplate)
      .id('gridColumnsTemplate1')
      .height(60)

      Button('GridColumnsTemplate')
        .onClick(() => {
          this.columnsTemplate = '0fr'
        })
    }
  }
}