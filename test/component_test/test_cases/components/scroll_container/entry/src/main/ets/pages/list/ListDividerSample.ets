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
import listDividerTest from '../MyTest/ListDividerTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ListDividerSample {
  private arr: string[] = ['英语', '数学']
  @State color: ResourceColor = 0xbbbbbb;
  @State color1: ResourceColor = $r('app.color.ListDivider_One_color');
  @State endMargin: Length = 10;
  @State strokeWidth: Length = 10;
  @State startMargin: Length = 10;

  aboutToAppear(): void {
    loadComponentTestEntry(listDividerTest)
  }

  build() {
    Scroll() {
      Column() {
        List({ space: 20, initialIndex: 0 }) {
          ForEach(this.arr, (item: number) => {
            ListItem() {
              Text('' + item)
            }
          })
        }
        .listDirection(Axis.Vertical)
        .divider({
          strokeWidth: this.strokeWidth,
          color: this.color,
          startMargin: this.startMargin,
          endMargin: this.endMargin
        })
        .id('listDivider1')

        Button('ListDivider1')
          .margin('5vp')
          .onClick(() => {
            this.strokeWidth = '20px'
            this.color = '#FFFF64FF'
            this.startMargin = '20px'
            this.endMargin = '20px'
          })
        List({ space: 20, initialIndex: 0 }) {
          ForEach(this.arr, (item: number) => {
            ListItem() {
              Text('' + item)
            }
          })
        }
        .listDirection(Axis.Vertical)
        .divider({
          strokeWidth: $r('app.float.ListDivider_float'),
          color: this.color1,
          startMargin: $r('app.float.ListDivider_float'),
          endMargin: $r('app.float.ListDivider_float')
        })
        .id('listDivider2')

        Button('ListDivider2')
          .margin('5vp')
          .onClick(() => {
            this.color1 = Color.Gray;
          })
      }
    }
  }
}