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
struct Index {
  build() {
    Column(){
      Scroll(){
        Column({space:10} as ColumnOptions) {
          Text('【可见可说】滚动类')
            .fontColor(0xFFFFFF)
            .textAlign(TextAlign.Center)
            .width('100%')
            .backgroundColor(0x0000FF)
          Button("List")
            .margin(10)
            .width('80%')
            .onClick((e: ClickEvent) => {
              this.getUIContext().getRouter().pushUrl({url: 'pages/scrollable/ScrollSpeak/List/listIndex'});
            })
          Button("List水平")
            .margin(10)
            .width('80%')
            .onClick((e: ClickEvent) => {
              this.getUIContext().getRouter().pushUrl({url: 'pages/scrollable/ScrollSpeak/List/listHori'});
            })
          Button("List不可滚动")
            .margin(10)
            .width('80%')
            .onClick((e: ClickEvent) => {
              this.getUIContext().getRouter().pushUrl({url: 'pages/scrollable/ScrollSpeak/List/listNo'});
            })
          Button("Grid")
            .margin(10)
            .width('80%')
            .onClick((e: ClickEvent) => {
              this.getUIContext().getRouter().pushUrl({url: 'pages/scrollable/ScrollSpeak/Grid/gridIndex'});
            })
          Button("Grid水平")
            .margin(10)
            .width('80%')
            .onClick((e: ClickEvent) => {
              this.getUIContext().getRouter().pushUrl({url: 'pages/scrollable/ScrollSpeak/Grid/girdHori'});
            })
          Button("Grid不可滚动")
            .margin(10)
            .width('80%')
            .onClick((e: ClickEvent) => {
              this.getUIContext().getRouter().pushUrl({url: 'pages/scrollable/ScrollSpeak/Grid/gridNo'});
            })
          Button("Scroll")
            .margin(10)
            .width('80%')
            .onClick((e: ClickEvent) => {
              this.getUIContext().getRouter().pushUrl({url: 'pages/scrollable/ScrollSpeak/Scroll/scrollIndex'});
            })
          Button("Scroll水平")
            .margin(10)
            .width('80%')
            .onClick((e: ClickEvent) => {
              this.getUIContext().getRouter().pushUrl({url: 'pages/scrollable/ScrollSpeak/Scroll/scrollHori'});
            })
          Button("Scroll不可滚动")
            .margin(10)
            .width('80%')
            .onClick((e: ClickEvent) => {
              this.getUIContext().getRouter().pushUrl({url: 'pages/scrollable/ScrollSpeak/Scroll/scrollNo'});
            })
          Button("WaterFlow")
            .margin(10)
            .width('80%')
            .onClick((e: ClickEvent) => {
              this.getUIContext().getRouter().pushUrl({url: 'pages/scrollable/ScrollSpeak/WaterFlow/waterFlowIndex'});
            })
          Button("WaterFlow水平")
            .margin(10)
            .width('80%')
            .onClick((e: ClickEvent) => {
              this.getUIContext().getRouter().pushUrl({url: 'pages/scrollable/ScrollSpeak/WaterFlow/waterFlowHori'});
            })
          Button("WaterFlow不可滚动")
            .margin(10)
            .width('80%')
            .onClick((e: ClickEvent) => {
              this.getUIContext().getRouter().pushUrl({url: 'pages/scrollable/ScrollSpeak/WaterFlow/waterFlowNo'});
            })
        }
      }
    }
  }
}