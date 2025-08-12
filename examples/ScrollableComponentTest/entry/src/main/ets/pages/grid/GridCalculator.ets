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

@Entry
@Component
export struct GridCalculator {
  private buttonArray: string[] =
    ['CE', 'C', '/', 'X', '7', '8', '9', '-', '4', '5', '6', '+', '1', '2', '3', '=', '0', '.'];
  @State res: string = '0';
  layoutOptions: GridLayoutOptions = {
    regularSize: [1, 1],
    onGetRectByIndex: (index: number) => {
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
      } else if (index == 15) {
        return [5, 3, 2, 1];
      } else if (index == 16) {
        return [6, 0, 1, 2];
      } else if (index == 17) {
        return [6, 2, 1, 1];
      }
      return [0, 0, 2, 4];
    }
  }

  build() {
    NavDestination() {
      Column({ space: 12 }) {
          Grid(undefined, this.layoutOptions) {
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
          }
          .columnsTemplate('1fr 1fr 1fr 1fr')
          .rowsTemplate('1fr 1fr 1fr 1fr 1fr 1fr 1fr')
          .rowsGap(8)
          .columnsGap(5)
          .width('100%')
          .height('80%')
        }
      }
    }
}