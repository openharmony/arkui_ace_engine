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
import restoreIdTest from '../MyTest/RestoreIdTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct RestoreIdSample {
  private arr: number[] = [0, 1]

  aboutToAppear(): void {
    loadComponentTestEntry(restoreIdTest)
  }

  build() {
    Column() {
      List({ space: 20 }) {
        ForEach(this.arr, (item: number) => {
          ListItem() {
            Text('' + item)
              .width('100%')
              .height(100)
              .backgroundColor(Color.Pink)
          }
        }, (item: number) => (item.toString()))
      }
      .id('listRestoreId1')
      .restoreId(1)
    }
  }
}