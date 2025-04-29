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
import listFrictionTest from '../MyTest/ListFrictionTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ListFrictionSample {
  private arr: number[] = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
  @State friction: number | Resource = 0.1;
  @State friction1: number | Resource = -1;

  aboutToAppear(): void {
    loadComponentTestEntry(listFrictionTest)
  }

  build() {
    Column() {
      List({ space: 20, initialIndex: 0 }) {
        ForEach(this.arr, (item: string) => {
          ListItem() {
            Text('' + item)
              .width('100%')
              .height(70)
              .backgroundColor(0xFFFFFF)
          }
          .border({ width: 2, color: Color.Green })
        })
      }
      .height("40%")
      .width("100%")
      .border({ width: 3, color: Color.Red })
      .friction(this.friction)
      .id('listFriction1')

      Button('ListFriction1')
        .margin('5vp')
        .onClick(() => {
          this.friction = 1;
        })

      List({ space: 20, initialIndex: 0 }) {
        ForEach(this.arr, (item: string) => {
          ListItem() {
            Text('' + item)
              .width('100%')
              .height(70)
              .backgroundColor(0xFFFFFF)
          }
          .border({ width: 2, color: Color.Green })
        })
      }
      .height("40%")
      .width("100%")
      .border({ width: 3, color: Color.Red })
      .friction(this.friction1)
      .id('listFriction2')

      Button('ListFriction2')
        .margin('5vp')
        .onClick(() => {
          this.friction1 = $r('app.float.ListFriction_float');
        })
    }
    .backgroundColor(0xDCDCDC)
  }
}