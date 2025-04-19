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
struct TabsSubTabBarStyle {
  @State nums: number[] = []
  @State barPosition: BarPosition = BarPosition.Start
  @State currentIndex: number = 0
  private controller: TabsController = new TabsController()
  @State selectedMode: SelectedMode = SelectedMode.INDICATOR
  @State vertical: boolean = false
  @State barMode: BarMode = BarMode.Fixed
  @State barModeOptions: ScrollableBarModeOptions = { margin: 0, nonScrollableLayoutStyle: LayoutStyle.ALWAYS_CENTER }
  @State tabsDirection: Direction = Direction.Auto
  @State fadingEdge: boolean = true
  @State inputIndex: number = 0

  aboutToAppear(): void {
    for (let i = 0; i < 3; i++) {
      this.nums.push(i)
    }
  }

  build() {
    Column() {
      Tabs({ barPosition: this.barPosition, index: this.currentIndex, controller: this.controller }) {
        ForEach(this.nums, (index: number) => {
          TabContent() {
            Text(index.toString()).fontSize(30)
          }.tabBar(SubTabBarStyle.of('测试' + index.toString()).selectedMode(this.selectedMode))
        })
      }
      .height(200)
      .backgroundColor('#F1F3F5')
      .onChange((index: number) => {
        console.info('onChange index:' + index)
        this.currentIndex = index
      })
      .vertical(this.vertical)
      .barMode(this.barMode, this.barModeOptions)
      .direction(this.tabsDirection)
      .fadingEdge(this.fadingEdge)

      Row() {
        TextInput({ placeholder: 'input index' })
          .width('30%')
          .margin({ right: 10 })
          .inputFilter('[0-9]', (e) => {
            console.info('inputFilter' + JSON.stringify(e))
          })
          .onChange((value: string) => {
            this.inputIndex = parseInt(value)
          })

        Button('changeIndex')
          .onClick(() => {
            if (this.inputIndex >= 0 && this.inputIndex < this.nums.length) {
              this.controller.changeIndex(this.inputIndex)
            }
          })

        Button('index')
          .onClick(() => {
            if (this.inputIndex >= 0 && this.inputIndex < this.nums.length) {
              this.currentIndex = this.inputIndex
            }
          })
      }.margin({ top: 5 })

      Row() {
        Button('first data++')
          .onClick(() => {
            this.nums.splice(0, 0, this.nums.length)
          })

        Button('center data++')
          .onClick(() => {
            this.nums.splice(Math.abs(Math.round(this.nums.length / 2)), 0, this.nums.length)
          })

        Button('last data++')
          .onClick(() => {
            this.nums.splice(this.nums.length, 0, this.nums.length)
          })
      }.margin({ top: 5 })

      Row() {
        Button('first data--')
          .onClick(() => {
            this.nums.splice(0, 1)
          })

        Button('center data--')
          .onClick(() => {
            this.nums.splice(Math.abs(Math.round(this.nums.length / 2)), 1)
          })

        Button('last data--')
          .onClick(() => {
            this.nums.splice(this.nums.length - 1, 1)
          })
      }.margin({ top: 5 })

      Row() {
        Button('BarPosition.Start')
          .onClick(() => {
            this.barPosition = BarPosition.Start
          })

        Button('End')
          .onClick(() => {
            this.barPosition = BarPosition.Start
          })
      }.margin({ top: 5 })

      Row() {
        Button('Horizontal')
          .onClick(() => {
            this.vertical = false
          })

        Button('Vertical')
          .onClick(() => {
            this.vertical = true
          })
      }.margin({ top: 5 })

      Row() {
        Button('BarMode.Fixed')
          .onClick(() => {
            this.barMode = BarMode.Fixed
          })

        Button('Scrollable')
          .onClick(() => {
            this.barMode = BarMode.Scrollable
          })
      }.margin({ top: 5 })

      Row() {
        Button('Margin:' + this.barModeOptions.margin)
          .onClick(() => {
            this.barModeOptions.margin = ((this.barModeOptions.margin as number) + 10) % 100
          })

        Button('LayoutStyle:' + JSON.stringify(this.barModeOptions.nonScrollableLayoutStyle))
          .onClick(() => {
            this.barModeOptions.nonScrollableLayoutStyle =
              ((this.barModeOptions.nonScrollableLayoutStyle as number) + 1) % 3
          })
      }.margin({ top: 5 })

      Row() {
        Button('Direction.Ltr')
          .onClick(() => {
            this.tabsDirection = Direction.Ltr
          })

        Button('Rtl')
          .onClick(() => {
            this.tabsDirection = Direction.Rtl
          })

        Button('Auto')
          .onClick(() => {
            this.tabsDirection = Direction.Auto
          })
      }.margin({ top: 5 })

      Row() {
        Button('fadingEdge:true')
          .onClick(() => {
            this.fadingEdge = true
          })

        Button('false')
          .onClick(() => {
            this.fadingEdge = false
          })
      }.margin({ top: 5 })

      Row() {
        Button('SelectedMode.INDICATOR')
          .onClick(() => {
            this.selectedMode = SelectedMode.INDICATOR
          })

        Button('BOARD')
          .onClick(() => {
            this.selectedMode = SelectedMode.BOARD
          })
      }.margin({ top: 5 })
    }
  }
}