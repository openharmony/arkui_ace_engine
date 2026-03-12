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
export function PopupLifecycleBuilder(name: string, param: Object) {
  PopupLifecycleExample()
}

@Entry
@Component
struct PopupLifecycleExample {
  pathStack: NavPathStack = new NavPathStack()
  
  @State showPopup: boolean = false
  @State lifecycleLog: string[] = []
  @State createCount: number = 0
  @State destroyCount: number = 0
  @State appearCount: number = 0
  @State disappearCount: number = 0
  
  @Builder
  popupContent() {
    Column({ space: 15 }) {
      Text('Popup Lifecycle')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)
      
      Divider()
      
      Text('Lifecycle Events')
        .fontSize(14)
        .fontColor(Color.Gray)
      
      Row() {
        Text('Created:')
        Blank()
        Text(this.createCount.toString())
          .fontColor(Color.Green)
      }
      .width('100%')
      .padding(5)
      
      Row() {
        Text('Destroyed:')
        Blank()
        Text(this.destroyCount.toString())
          .fontColor(Color.Red)
      }
      .width('100%')
      .padding(5)
      
      Row() {
        Text('Appear:')
        Blank()
        Text(this.appearCount.toString())
          .fontColor(Color.Blue)
      }
      .width('100%')
      .padding(5)
      
      Row() {
        Text('Disappear:')
        Blank()
        Text(this.disappearCount.toString())
          .fontColor(Color.Orange)
      }
      .width('100%')
      .padding(5)
      
      Divider()
      
      Button('Close')
        .width('100%')
        .onClick(() => {
          this.showPopup = false
          this.logLifecycle('Popup close requested')
        })
    }
    .width(280)
    .padding(20)
    .backgroundColor(Color.White)
    .borderRadius(10)
  }
  
  logLifecycle(event: string) {
    const timestamp = new Date().toLocaleTimeString()
    this.lifecycleLog.unshift(`${timestamp}: ${event}`)
    if (this.lifecycleLog.length > 15) {
      this.lifecycleLog.pop()
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
      Scroll() {
        Column() {
          Text('Popup Lifecycle Test')
            .fontSize(24)
            .fontWeight(FontWeight.Bold)
            .margin({ top: 20, bottom: 20 })

          Column() {
            Text('Lifecycle Statistics')
              .fontSize(18)
              .fontWeight(FontWeight.Bold)
              .margin({ bottom: 10 })

            Row() {
              Text('Create Count:')
              Blank()
              Text(this.createCount.toString())
                .fontSize(20)
                .fontWeight(FontWeight.Bold)
                .fontColor(Color.Green)
            }
            .width('100%')
            .padding(5)

            Row() {
              Text('Destroy Count:')
              Blank()
              Text(this.destroyCount.toString())
                .fontSize(20)
                .fontWeight(FontWeight.Bold)
                .fontColor(Color.Red)
            }
            .width('100%')
            .padding(5)

            Row() {
              Text('Appear Count:')
              Blank()
              Text(this.appearCount.toString())
                .fontSize(20)
                .fontWeight(FontWeight.Bold)
                .fontColor(Color.Blue)
            }
            .width('100%')
            .padding(5)

            Row() {
              Text('Disappear Count:')
              Blank()
              Text(this.disappearCount.toString())
                .fontSize(20)
                .fontWeight(FontWeight.Bold)
                .fontColor(Color.Orange)
            }
            .width('100%')
            .padding(5)
          }
          .cardStyle()

          Column() {
            Text('Lifecycle Log')
              .fontSize(18)
              .fontWeight(FontWeight.Bold)
              .margin({ bottom: 10 })

            List({ space: 5 }) {
              ForEach(this.lifecycleLog, (log: string) => {
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
                this.lifecycleLog = []
                this.createCount = 0
                this.destroyCount = 0
                this.appearCount = 0
                this.disappearCount = 0
                this.logLifecycle('Lifecycle log cleared')
              })
          }
          .cardStyle()

          Column() {
            Text('Show Popup')
              .fontSize(18)
              .fontWeight(FontWeight.Bold)
              .margin({ bottom: 10 })

            Button('Open Popup')
              .myButtonStyle()
              .onClick(() => {
                this.showPopup = true
                this.createCount++
                this.appearCount++
                this.logLifecycle('Popup created')
                this.logLifecycle('Popup appeared')
              })
              .bindPopup(this.showPopup, {
                builder: this.popupContent(),
                placement: Placement.Bottom,
                mask: true,
                onStateChange: (e) => {
                  if (e.isVisible) {
                    this.appearCount++
                    this.logLifecycle('Popup appeared')
                  } else {
                    this.disappearCount++
                    this.destroyCount++
                    this.logLifecycle('Popup disappeared')
                    this.logLifecycle('Popup destroyed')
                  }
                }
              })
          }
        }
        .width('100%')
        .padding(20)
      }
    }
    .title('Popup Lifecycle Test')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack
    })
  }
}
