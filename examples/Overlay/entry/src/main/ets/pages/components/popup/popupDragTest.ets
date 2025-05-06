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

@Builder
export function PopupDragBuilder(name: string, param: Object) {
  PopupExample07()
}

@Entry
@Component
struct PopupExample07 {
  pathStack: NavPathStack = new NavPathStack()
  @State handlePopup1: boolean = false
  @State handlePopup2: boolean = false

  @Builder popupBuilder() {
    Row({ space: 2 }) {
      Text('Custom Popup').fontSize(20)
        .onDragStart(()=>{
          this.handlePopup1 = false
        })
        .borderWidth(2)
    }.height(50).padding(5)
  }

  build() {
    NavDestination() {
      Column({ space: 100 }) {
        Text('测试气泡内文本拖拽')
          .textAlign(TextAlign.Center)
          .fontSize(20)

        Button('验证气泡内组件拖拽')
          .onClick(() => {
            this.handlePopup1 = !this.handlePopup1
          })
          .bindPopup(this.handlePopup1!!, {
            builder: this.popupBuilder(),
            mask: {color: '#33ff0000'},
            popupColor: Color.Yellow,
            backgroundBlurStyle: BlurStyle.NONE,
            placement: Placement.Top,
            enableArrow: true,
            showInSubWindow: true,
            onStateChange: (e) => {
              console.info(JSON.stringify(e.isVisible))
              if (!e.isVisible) {
                this.handlePopup1 = false
              }
            }
          })
          .position({x: 80, y: 300})
      }
      .width('100%')
      .padding({top: 5})
    }
    .title('PopupDragTest')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}