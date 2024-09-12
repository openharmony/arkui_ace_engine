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
import GridColGridColOffsetTest from '../MyTest/GridColGridColOffsetTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct GridColGridColOffsetSample {
  @State gridColOffsetStatus: number | GridColColumnOption = 1

  aboutToAppear(): void {
    loadComponentTestEntry(GridColGridColOffsetTest)
  }

  build() {
    Column() {
      GridRow() {
        GridCol() {
          Text('gridColOffset')
        }
        .gridColOffset(this.gridColOffsetStatus)
        .borderColor(Color.Orange)
        .borderWidth(2)
        .width("100%")
        .height("30%")
      }
      .id('gridColOffset')
      .height("15%")
      .backgroundColor(Color.Red)
      .borderWidth(2)
      .width("100%")

      Button('GridColOffset').onClick(() => {
        this.gridColOffsetStatus = {
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

