'use static'

/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

import { ComponentCard } from '../../common/Card';
import {
  Entry,
  Component,
  State,
  NavDestination,
  Column,
  Grid,
  GridItem,
  Button,
  Text,
  ForEach,
  ColumnOptions,
  FontWeight,
  TextAlign,
  GridLayoutOptions,
  $r
} from '@kit.ArkUI';

@Entry
@Component
export struct GridCalculator {
  private buttonArray: string[] =
    ['CE', 'C', '/', 'X', '7', '8', '9', '-', '4', '5', '6', '+', '1', '2', '3', '=', '0', '.'];
  @State
  res: string = '0';
  // [Start Set_numberrows_columns]
  layoutOptions: GridLayoutOptions = {
    regularSize: [1, 1],
    onGetRectByIndex: (index: int) => {
      // [StartExclude Set_numberrows_columns]
      let key1: int = 16;
      let key2: int = 15;
      // [EndExclude Set_numberrows_columns]

      if (index == key1) { // key1是"0"按键对应的index
        return [6, 0, 1, 2];
      } else if (index == key2) { // key2是"="按键对应的index
        return [5, 3, 2, 1];
      }
      // [StartExclude Set_numberrows_columns]
      if (index == 0) {
        return [2, 0, 1, 1];
      } else if (index == 1) {
        return [2, 1, 1, 1];
      } else if (index == 2) {
        return [2, 2, 1, 1];
      } else if (index == 3) {
        return [2, 3, 1, 1];
      } else if (index == 4) {
        return [3, 0, 1, 1];
      } else if (index == 5) {
        return [3, 1, 1, 1];
      } else if (index == 6) {
        return [3, 2, 1, 1];
      } else if (index == 7) {
        return [3, 3, 1, 1];
      } else if (index == 8) {
        return [4, 0, 1, 1];
      } else if (index == 9) {
        return [4, 1, 1, 1];
      } else if (index == 10) {
        return [4, 2, 1, 1];
      } else if (index == 11) {
        return [4, 3, 1, 1];
      } else if (index == 12) {
        return [5, 0, 1, 1];
      } else if (index == 13) {
        return [5, 1, 1, 1];
      } else if (index == 14) {
        return [5, 2, 1, 1];
      } else if (index == 17) {
        return [6, 2, 1, 1];
      }
      return [0, 0, 2, 4];
      // [EndExclude Set_numberrows_columns]
      // 这里需要根据具体布局返回其他item的位置
    }
  }
  // [StartExclude Set_numberrows_columns]
  build(): void {
    NavDestination() {
      Column({ space: 12 } as ColumnOptions) {
        // app.string.GridCalculator_title资源文件中的value值为'计算器的按键布局'
        ComponentCard({ title: $r('app.string.GridCalculator_title') }) {
          // [EndExclude Set_numberrows_columns]
          Grid(undefined, this.layoutOptions) {
            // [StartExclude Set_numberrows_columns]
            ForEach(this.buttonArray, (item: string) => {
              GridItem() {
                Button(item)
                  .width('100%')
                  .height('100%')
                  .borderRadius(10)
                  .backgroundColor(0x55555555)
                  .fontWeight(FontWeight.Bold)
                  .onClick(() => {
                    // 按钮功能实现
                    // ...
                  })
              }
            })
            GridItem() {
              Text(this.res).width('100%').height('100%').textAlign(TextAlign.End).fontSize(30)
            }.backgroundColor(0x55555555).borderRadius(10)
            // [EndExclude Set_numberrows_columns]
          }
          .columnsTemplate('1fr 1fr 1fr 1fr')
          .rowsTemplate('1fr 1fr 1fr 1fr 1fr 1fr 1fr')
          // [End Set_numberrows_columns]

          .rowsGap(8)
          .columnsGap(5)
          .width('100%')
          .height('80%')
        }
      }
    }
  }
}
