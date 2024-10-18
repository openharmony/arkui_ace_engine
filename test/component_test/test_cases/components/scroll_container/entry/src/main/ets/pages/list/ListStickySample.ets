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
import listStickyTest from '../MyTest/ListStickyTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ListStickySample {
  private timeTable: string[] = ['语文', '数学', '英语']
  @State title: string = '123'
  @State sticky: StickyStyle = StickyStyle.Footer
  @State sticky1: StickyStyle = StickyStyle.Footer | StickyStyle.Header

  @Builder
  itemHead(text: string) {
    Text(text)
      .backgroundColor(0xAABBCC)
      .width("100%")
  }

  @Builder
  itemFoot(num: number) {
    Text('共' + num + "节课")
      .backgroundColor(0xAABBCC)
      .width("100%")
  }

  aboutToAppear(): void {
    loadComponentTestEntry(listStickyTest)
  }

  build() {
    Scroll() {
      Column() {
        List({ space: 20 }) {
          ForEach(this.timeTable, (item: string) => {
            ListItemGroup({ header: this.itemHead(this.title), footer: this.itemFoot(3) }) {
              ForEach(this.timeTable, (project: string) => {
                ListItem() {
                  Text(project)
                    .width("100%")
                    .height(50)
                    .fontSize(20)
                }
                .border({ width: 2, color: Color.Green })
              })
            }
          })
        }
        .height("40%")
        .width("100%")
        .border({ width: 3, color: Color.Red })
        .sticky(this.sticky)
        .id('listSticky1')

        Button('ListSticky1')
          .margin('5vp')
          .onClick(() => {
            this.sticky = StickyStyle.Header;
          })

        List({ space: 20 }) {
          ForEach(this.timeTable, (item: string) => {
            ListItemGroup({ header: this.itemHead(this.title), footer: this.itemFoot(3) }) {
              ForEach(this.timeTable, (project: string) => {
                ListItem() {
                  Text(project)
                    .width("100%")
                    .height(50)
                    .fontSize(20)
                }
                .border({ width: 2, color: Color.Green })
              })
            }
          })
        }
        .height("40%")
        .width("100%")
        .border({ width: 3, color: Color.Red })
        .sticky(this.sticky1)
        .id('listSticky2')

        Button('ListSticky2')
          .margin('5vp')
          .onClick(() => {
            this.sticky1 = StickyStyle.None
          })
      }
    }
  }
}