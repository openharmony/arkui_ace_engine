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
import listLanesTest from '../MyTest/ListLanesTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ListLanesSample {
  @State arr: string[] = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '16']
  @State lanes: number | LengthConstrain = 20;
  @State lanes1: number | LengthConstrain =
    { minLength: $r('app.float.ListLanes_float'), maxLength: $r('app.float.ListLanes_float') };
  @State dimension: Dimension = '10px';
  @State dimension1: Dimension = '10fp';
  @State dimension2: Dimension = '10%';

  aboutToAppear(): void {
    loadComponentTestEntry(listLanesTest)
  }

  build() {
    Scroll() {
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
        .height(160)
        .width("100%")
        .border({ width: 3, color: Color.Red })
        .lanes(this.lanes, this.dimension)
        .id('listLanes1')

        Button('ListLanes1')
          .margin('5vp')
          .onClick(() => {
            this.lanes = { minLength: '5px', maxLength: '5px' }
            this.dimension = '10vp'
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
        .height(160)
        .width("100%")
        .border({ width: 3, color: Color.Red })
        .lanes(this.lanes1, this.dimension1)
        .id('listLanes2')

        Button('ListLanes2')
          .margin('5vp')
          .onClick(() => {
            this.lanes1 = { minLength: 5, maxLength: 5 }
            this.dimension1 = '10lpx'
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
        .height(160)
        .width("100%")
        .border({ width: 3, color: Color.Red })
        .lanes(this.lanes1, this.dimension2)
        .id('listLanes3')

        Button('ListLanes3')
          .margin('5vp')
          .onClick(() => {
            this.dimension2 = $r('app.float.ListLanes_float')
          })

      }.backgroundColor(0xDCDCDC)
    }
    .scrollBar(BarState.On)
  }
}