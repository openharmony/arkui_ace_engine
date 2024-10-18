/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
//测试代码路径
import listCachedCountTest from '../MyTest/ListCachedCountTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

class MyDataSource1 implements IDataSource {
  private arr: number[] = [0, 1, 2, 3, 4]

  constructor() {
  }

  totalCount(): number {
    return this.arr.length
  }

  getData(index: number): number {
    return this.arr[index]
  }

  registerDataChangeListener(): void {
  }

  unregisterDataChangeListener() {
  }
}

class MyDataSource2 implements IDataSource {
  private brr: string[] = ['0', '1', '2', '3']

  constructor() {
  }

  totalCount(): number {
    return this.brr.length
  }

  getData(index: number): string {
    return this.brr[index]
  }

  registerDataChangeListener(): void {
  }

  unregisterDataChangeListener() {
  }
}

@Entry
@Component
struct ListCachedCountSample {
  private data1: MyDataSource1 = new MyDataSource1()
  private data2: MyDataSource2 = new MyDataSource2()

  aboutToAppear(): void {
    loadComponentTestEntry(listCachedCountTest)
    this.data1 = new MyDataSource1()
    this.data2 = new MyDataSource2()
  }

  build() {
    Scroll() {
      Column() {
        List({ space: 20, initialIndex: 0 }) {
          LazyForEach(this.data1, (item: number) => {
            ListItem() {
              Text('' + item)
                .width('50%')
                .height(100)
                .fontSize(16)
                .textAlign(TextAlign.Center)
                .borderRadius(10)
                .backgroundColor(0xFF0FFF)
            }
          }, (item: string) => item)
        }
        .cachedCount(10)
        .id('listCachedCount1')

        List({ space: 20, initialIndex: 0 }) {
          LazyForEach(this.data2, (item: string) => {
            ListItem() {
              Text('' + item)
                .width('100%')
                .height(70)
                .backgroundColor(0xFFFFFF)
            }
            .border({ width: 2, color: Color.Green })
          })
        }
        .height(160)
        .width('100%')
        .border({ width: 3, color: Color.Red })
        .cachedCount(1)
        .lanes(7)
        .id('listCachedCount2')
      }
      .backgroundColor(0xDCDCDC)
    }
  }
}