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
import GridColOrderTest from '../MyTest/GridColOrderTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct GridColOrderSample {
  @State gridColOrderStatus: number | GridColColumnOption = 1

  aboutToAppear(): void {
    loadComponentTestEntry(GridColOrderTest)
  }

  build() {
    Column() {
      GridRow() {
        GridCol() {
          Text('gridColOrder1')
        }
        .id('gridColOrder1')
        .order(this.gridColOrderStatus)
        .borderColor(Color.Orange)
        .borderWidth(2)
        .width("100%")
        .height("30%")

        GridCol() {
          Text('gridColOrder2')
        }
        .id('gridColOrder2')
        .order(2)
        .borderColor(Color.Orange)
        .borderWidth(2)
        .width("100%")
        .height("30%")
      }
      .height("15%")
      .alignItems(ItemAlign.Start)
      .backgroundColor(Color.Red)
      .width("100%")

      Button('GridColOrder').onClick(() => {
        this.gridColOrderStatus = {
          xs: 1,
          sm: 2,
          md: 3,
          lg: 4,
          xl: 5,
          xxl: 6
        }
      })

    }
  }
}