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

@Builder
export function PopupTouchBuilder(name: string, param: Object) {
  PopupTouchExample()
}

@Entry
@Component
struct PopupTouchExample {
  pathStack: NavPathStack = new NavPathStack()
  
  @State showPopup: boolean = false
  @State touchLog: string[] = []
  @State touchCount: number = 0
  @State dragCount: number = 0
  @State swipeCount: number = 0
  
  @Builder
  popupContent() {
    Column({ space: 15 }) {
      Text('Popup Touch Test')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)
      
      Divider()
      
      Text('Touch Statistics')
        .fontSize(14)
        .fontColor(Color.Gray)
      
      Row() {
        Text('Touch Count:')
        Blank()
        Text(this.touchCount.toString())
          .fontColor(Color.Blue)
      }
      .width('100%')
      .padding(5)
      
      Row() {
        Text('Drag Count:')
        Blank()
        Text(this.dragCount.toString())
          .fontColor(Color.Green)
      }
      .width('100%')
      .padding(5)
      
      Row() {
        Text('Swipe Count:')
        Blank()
        Text(this.swipeCount.toString())
          .fontColor(Color.Orange)
      }
      .width('100%')
      .padding(5)
      
      Divider()
      
      Text('Touch Area')
        .fontSize(14)
        .fontColor(Color.Gray)
      
      Column({ space: 10 }) {
        Button('Tap Me')
          .width('100%')
          .height(50)
          .onClick(() => {
            this.touchCount++
            this.logTouch('Button tapped')
          })
        
        Button('Drag Me')
          .width('100%')
          .height(50)
          .onClick(() => {
            this.dragCount++
            this.logTouch('Button dragged')
          })
        
        Button('Swipe Me')
          .width('100%')
          .height(50)
          .onClick(() => {
            this.swipeCount++
            this.logTouch('Button swiped')
          })
      }
      .width('100%')
      .padding(10)
      .backgroundColor(Color.Gray)
      .borderRadius(5)
      
      Divider()
      
      Button('Close')
        .width('100%')
        .onClick(() => {
          this.showPopup = false
          this.logTouch('Popup closed')
        })
    }
    .width(300)
    .padding(20)
    .backgroundColor(Color.White)
    .borderRadius(10)
  }
  
  logTouch(event: string) {
    const timestamp = new Date().toLocaleTimeString()
    this.touchLog.unshift(`${timestamp}: ${event}`)
    if (this.touchLog.length > 15) {
      this.touchLog.pop()
    }
  }
  
  @Styles
  myButtonStyle() {
    .width('100%')
    .height(45)
    .borderRadius(8)
    .margin({ top: 5, bottom: 5 })
  }
  
  @Styles
  cardStyle() {
    .width('90%')
    .padding(15)
    .margin({ top: 10, bottom: 10 })
    .backgroundColor(Color.White)
    .borderRadius(10)
    .shadow({
      radius: 8,
      offsetX: 2,
      offsetY: 2,
      color: Color.Gray
    })
  }
  
  build() {
    NavDestination() {
      Column() {
        Text('Popup Touch Test')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 20 })
        
        Column() {
          Text('Touch Statistics')
            .fontSize(18)
            .fontWeight(FontWeight.Bold)
            .margin({ bottom: 10 })
          
          Row() {
            Text('Touch Count:')
            Blank()
            Text(this.touchCount.toString())
              .fontSize(20)
              .fontWeight(FontWeight.Bold)
              .fontColor(Color.Blue)
          }
          .width('100%')
          .padding(5)
          
          Row() {
            Text('Drag Count:')
            Blank()
            Text(this.dragCount.toString())
              .fontSize(20)
              .fontWeight(FontWeight.Bold)
              .fontColor(Color.Green)
          }
          .width('100%')
          .padding(5)
          
          Row() {
            Text('Swipe Count:')
            Blank()
            Text(this.swipeCount.toString())
              .fontSize(20)
              .fontWeight(FontWeight.Bold)
              .fontColor(Color.Orange)
          }
          .width('100%')
          .padding(5)
        }
        .cardStyle()
        
        Column() {
          Text('Touch Log')
            .fontSize(18)
            .fontWeight(FontWeight.Bold)
            .margin({ bottom: 10 })
          
          List({ space: 5 }) {
            ForEach(this.touchLog, (log: string) => {
              ListItem() {
                Text(log)
                  .fontSize(12)
                  .fontColor(Color.Gray)
              }
              .width('100%')
              .padding(5)
              .backgroundColor(Color.White)
              .borderRadius(5)
            })
          }
          .width('100%')
          .height(300)
          .padding(10)
          .backgroundColor(Color.White)
          .borderRadius(10)
          
          Button('Clear Log')
            .width('100%')
            .margin({ top: 10 })
            .onClick(() => {
              this.touchLog = []
              this.touchCount = 0
              this.dragCount = 0
              this.swipeCount = 0
              this.logTouch('Touch log cleared')
            })
        }
        .cardStyle()
        
        Column() {
          Text('Show Popup')
            .fontSize(18)
            .fontWeight(FontWeight.Bold)
            .margin({ bottom: 10 })
          
          Button('Open Touch Popup')
            .myButtonStyle()
            .onClick(() => {
              this.showPopup = true
              this.logTouch('Popup opened')
            })
            .bindPopup(this.showPopup, {
              builder: this.popupContent(),
              placement: Placement.Bottom,
              mask: true,
              onStateChange: (e) => {
                if (e.isVisible) {
                  this.logTouch('Popup became visible')
                } else {
                  this.logTouch('Popup became hidden')
                }
              }
            })
        }
        .cardStyle()
      }
      .width('100%')
      .padding(20)
    }
    .title('Popup Touch Test')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack
    })
  }
}
