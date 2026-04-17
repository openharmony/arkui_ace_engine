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

@Entry
@Component
struct EventReportIndex {
  build() {
    Column({ space: 5 } as ColumnOptions) {

      Row() {
        Column() {
          Button('scroll单列').backgroundColor('#FFFF00FF')
            .onClick((e: ClickEvent) => {
              this.getUIContext().getRouter().pushUrl({ url: 'pages/scrollable/EventReport/scroll', })
            })
          Button('scroll-nestedScroll').backgroundColor('#FFFF00FF')
            .onClick((e: ClickEvent) => {
              this.getUIContext().getRouter().pushUrl({ url: 'pages/scrollable/EventReport/scroll-nestedScroll', })
            })
          Button('List单列').backgroundColor('#FFFF00FF')
            .onClick((e: ClickEvent) => {
              this.getUIContext().getRouter().pushUrl({ url: 'pages/scrollable/EventReport/list', })
            })
          Button('List单列-nestedScroll').backgroundColor('#FFFF00FF')
            .onClick((e: ClickEvent) => {
              this.getUIContext().getRouter().pushUrl({ url: 'pages/scrollable/EventReport/list-nestedScroll', })
            })
          Button('Grid单列').backgroundColor('#FFFF00FF')
            .onClick((e: ClickEvent) => {
              this.getUIContext().getRouter().pushUrl({ url: 'pages/scrollable/EventReport/grid', })
            })
          Button('Grid单列-nestedScroll').backgroundColor('#FFFF00FF')
            .onClick((e: ClickEvent) => {
              this.getUIContext().getRouter().pushUrl({ url: 'pages/scrollable/EventReport/grid-nestedScroll', })
            })
          Button('WaterFlow单列').backgroundColor('#FFFF00FF')
            .onClick((e: ClickEvent) => {
              this.getUIContext().getRouter().pushUrl({ url: 'pages/scrollable/EventReport/waterflow', })
            })
          Button('WaterFlow单列-nestedScroll').backgroundColor('#FFFF00FF')
            .onClick((e: ClickEvent) => {
              this.getUIContext().getRouter().pushUrl({ url: 'pages/scrollable/EventReport/waterflow-nestedScroll', })
            })
        }
      }
    }.width('100%')
  }
}