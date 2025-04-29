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
import listItemGroupDividerTest from '../MyTest/ListItemGroupDividerTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ListItemGroupDividerSample {
  private timeTable: string[] = ['strokeWidth', 'Number']
  @State buttonStrokeWidth: Length = 5
  @State buttonColor1: ResourceColor = Color.Blue
  @State buttonColor2: ResourceColor = '#FFF000'
  @State buttonStartMargin: Length = $r('app.string.listItemGroup_startMargin')
  @State buttonEndMargin: Length = '50px'

  aboutToAppear(): void {
    loadComponentTestEntry(listItemGroupDividerTest);
  }

  build() {
    Scroll() {
      Column({ space: 20 }) {
        List({ space: 10 }) {
          ListItemGroup() {
            ForEach(this.timeTable, (project: string) => {
              ListItem() {
                Text(project)
              }
            })
          }
          .divider({
            strokeWidth: this.buttonStrokeWidth,
            color: this.buttonColor1,
            startMargin: '100px',
            endMargin: 20
          })
          .id('listItemGroupDivider1')
        }

        Button('ListItemGroup1')
          .onClick(() => {
            this.buttonStrokeWidth = '50px'
            this.buttonColor1 = 0xff00ff
          })
        List({ space: 10 }) {
          ListItemGroup() {
            ForEach(this.timeTable, (project: string) => {
              ListItem() {
                Text(project)
              }
            })
          }
          .divider({
            strokeWidth: $r('app.string.listItemGroup_strokeWidth'),
            color: this.buttonColor2,
            startMargin: this.buttonStartMargin,
            endMargin: this.buttonEndMargin
          })
          .id('listItemGroupDivider2')
        }

        Button('ListItemGroup2')
          .onClick(() => {
            this.buttonColor2 = $r('app.color.listItemGroup_color')
            this.buttonEndMargin = 50
            this.buttonStartMargin = $r('app.string.listItemGroup_endMargin')
          })
        List({ space: 10 }) {
          ListItemGroup() {
            ForEach(this.timeTable, (project: string) => {
              ListItem() {
                Text(project)
              }
            })
          }
          .divider(null)
          .id('listItemGroupDivider3')
        }
      }
    }
  }
}