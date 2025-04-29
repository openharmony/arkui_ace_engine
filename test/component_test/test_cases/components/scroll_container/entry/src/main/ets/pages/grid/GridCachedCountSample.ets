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
import gridCachedCountTest from '../MyTest/GridCachedCountTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

class MyDataSource implements IDataSource {
  private list: number[] = [1, 2, 3, 4, 5]

  constructor() {
  }

  totalCount(): number {
    return this.list.length
  }

  getData(index: number): number {
    return this.list[index]
  }

  registerDataChangeListener(): void {
  }

  unregisterDataChangeListener() {
  }
}

@Entry
@Component
struct GridCachedCountSample {
  private data: MyDataSource = new MyDataSource()

  aboutToAppear(): void {
    loadComponentTestEntry(gridCachedCountTest)
    this.data = new MyDataSource()
  }

  build() {
    Column() {
      Grid() {
        LazyForEach(this.data, (day: number) => {
          GridItem() {
            Text('gridCachedCountTest' + day.toString())
              .backgroundColor(0xF9CF93)
          }
        }, (day: string) => day)
      }.height('50%')
      .columnsTemplate('1fr')
      .cachedCount(3)
      .id('gridCachedCount1')

      Grid() {
        LazyForEach(this.data, (day: number) => {
          GridItem() {
            Text('gridCachedCountTest' + day.toString())
              .backgroundColor(0xF9CF93)
          }
        }, (day: string) => day)
      }.height('50%')
      .columnsTemplate('1fr')
      .cachedCount(-1)
      .id('gridCachedCount2')
    }.width('100%')
  }
}