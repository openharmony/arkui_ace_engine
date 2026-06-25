/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import { CommonDataSource } from './CommonDataSource'
import { ListCard } from './ListCard'

@Entry
@Component
struct TableDemo {
  @State scrollStart: number = 0
  @State scrollOffset: number = 0
  private arr1: string[] = []
  dataSource = new CommonDataSource<String>()

  aboutToAppear(): void {
    for (let i = 0; i < 100; i++) {
      this.arr1.push('1-' + i.toString())
    }
    this.dataSource.pushDataArray(...this.arr1)
  }

  build() {
    List() {
      LazyForEach(this.dataSource, (item: String) => {
        ListItem() {
          Row() {
            Text(item.toString())
              .width(60)
              .height(45)
              .backgroundColor('#ff9babdd')
            ListCard({
              itemText: item.toString(),
              scrollStart: this.scrollStart,
              scrollOffset: this.scrollOffset
            })
          }
        }
      })
    }
    // 纵向List使用较少的cachedCount，避免横滑时过多横向List响应联动导致卡顿
    .cachedCount(1)
    .width('100%')
    .height('100%')
  }
}