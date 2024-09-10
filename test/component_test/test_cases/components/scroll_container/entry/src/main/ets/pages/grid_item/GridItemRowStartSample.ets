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
import gridItemRowStartTest from '../MyTest/GridItemRowStartTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct GridItemRowStartSample {
  aboutToAppear(): void {
    loadComponentTestEntry(gridItemRowStartTest)
  }

  build() {
    Column() {
      Grid() {
        GridItem() {
          Text('1')
            .backgroundColor(Color.Red)
        }.rowStart(1).rowEnd(2).id('gridItemRowStart')
      }
      .columnsTemplate('1fr 1fr 1fr')
      .rowsTemplate('1fr 1fr 1fr')
    }
  }
}