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
export function PopupTabsBuilder(name: string, param: Object) {
  PopupTabsExample()
}

interface struct1 { position: BarPosition, label: string }

@Entry
@Component
struct PopupTabsExample {
  pathStack: NavPathStack = new NavPathStack()
  
  @State showPopup: boolean = false
  @State currentTab: number = 0
  @State barPosition: BarPosition = BarPosition.Start
  @State scrollable: boolean = true
  @State animationMode: boolean = true
  
  @Builder
  tabsPopupContent() {
    Column({ space: 15 }) {
      Text('Tabs Popup')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)
      
      Divider()
      
      Text('Tabs Configuration')
        .fontSize(14)
        .fontColor(Color.Gray)
      
      Row() {
        Text('Current Tab: ' + this.currentTab)
          .fontSize(16)
          .fontColor(Color.Blue)
      }
      .width('100%')
      .padding(5)
      
      Row() {
        Text('Bar Position: ' + this.barPosition.toString())
          .fontSize(16)
          .fontColor(Color.Blue)
      }
      .width('100%')
      .padding(5)
      
      Row() {
        Text('Scrollable: ' + this.scrollable.toString())
          .fontSize(16)
          .fontColor(Color.Blue)
      }
      .width('100%')
      .padding(5)
      
      Divider()
      
      Tabs({ barPosition: this.barPosition, index: this.currentTab }) {
        TabContent() {
          Column({ space: 10 }) {
            Text('Tab 1 Content')
              .fontSize(16)
              .fontWeight(FontWeight.Bold)
            
            ForEach([1, 2, 3], (item: number) => {
              Text('Item ' + item)
                .fontSize(14)
            })
          }
        }
        .tabBar(this.tabBarBuilder(0))
        
        TabContent() {
          Column({ space: 10 }) {
            Text('Tab 2 Content')
              .fontSize(16)
              .fontWeight(FontWeight.Bold)
            
            ForEach([1, 2, 3], (item: number) => {
              Text('Item ' + item)
                .fontSize(14)
            })
          }
        }
        .tabBar(this.tabBarBuilder(1))
        
        TabContent() {
          Column({ space: 10 }) {
            Text('Tab 3 Content')
              .fontSize(16)
              .fontWeight(FontWeight.Bold)
            
            ForEach([1, 2, 3], (item: number) => {
              Text('Item ' + item)
                .fontSize(14)
            })
          }
        }
        .tabBar(this.tabBarBuilder(2))
      }
      .width('100%')
      .height(300)
      .animationDuration(this.animationMode ? 300 : 0)
      .vertical(false)
      .scrollable(this.scrollable)
      .onChange((index: number) => {
        this.currentTab = index
      })
      
      Divider()
      
      Button('Close')
        .width('100%')
        .onClick(() => {
          this.showPopup = false
        })
    }
    .width(350)
    .padding(20)
    .backgroundColor(Color.White)
    .borderRadius(10)
  }
  
  @Builder
  tabBarBuilder(index: number) {
    Text('Tab ' + (index + 1))
      .fontSize(16)
      .fontColor(this.currentTab === index ? Color.White : Color.Black)
      .padding({ top: 8, bottom: 8 })
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
        Text('Popup Tabs Test')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 20 })
        
        Column() {
          Text('Tabs Configuration')
            .fontSize(18)
            .fontWeight(FontWeight.Bold)
            .margin({ bottom: 10 })
          
          Text('Bar Position')
            .fontSize(14)
            .margin({ top: 10 })
          
          Row({ space: 10 }) {
            ForEach([
              { position: BarPosition.Start, label: 'Start' },
              { position: BarPosition.End, label: 'End' }
            ], (item: struct1) => {
              Button(item.label)
                .width('31%')
                .height(40)
                .fontSize(12)
                .backgroundColor(this.barPosition === item.position ? Color.Blue : Color.Gray)
                .onClick(() => {
                  this.barPosition = item.position
                })
            })
          }
          .width('100%')
          
          Row() {
            Text('Scrollable: ' + this.scrollable.toString())
            Toggle({ type: ToggleType.Switch, isOn: this.scrollable })
              .onChange((isOn: boolean) => {
                this.scrollable = isOn
              })
          }
          .width('100%')
          .padding(5)
          
          Row() {
            Text('Animation Mode: ' + this.animationMode.toString())
            Toggle({ type: ToggleType.Switch, isOn: this.animationMode })
              .onChange((isOn: boolean) => {
                this.animationMode = isOn
              })
          }
          .width('100%')
          .padding(5)
        }
        .cardStyle()
        
        Column() {
          Text('Tabs Popup Demo')
            .fontSize(18)
            .fontWeight(FontWeight.Bold)
            .margin({ bottom: 10 })
          
          Text('Popup with Tabs component')
            .fontSize(14)
            .fontColor(Color.Gray)
            .margin({ bottom: 10 })
          
          Button('Show Tabs Popup')
            .myButtonStyle()
            .onClick(() => {
              this.showPopup = true
            })
            .bindPopup(this.showPopup, {
              builder: this.tabsPopupContent(),
              placement: Placement.Bottom,
              mask: true,
              onStateChange: (e) => {
                if (!e.isVisible) {
                  this.showPopup = false
                }
              }
            })
        }
        .cardStyle()
        
        Column() {
          Text('Tabs Information')
            .fontSize(18)
            .fontWeight(FontWeight.Bold)
            .margin({ bottom: 10 })
          
          Text('• Tabs support multiple tab content')
            .fontSize(14)
            .fontColor(Color.Gray)
          
          Text('• Bar position can be Start/Center/End')
            .fontSize(14)
            .fontColor(Color.Gray)
          
          Text('• Supports vertical and horizontal layout')
            .fontSize(14)
            .fontColor(Color.Gray)
          
          Text('• Scrollable content for large items')
            .fontSize(14)
            .fontColor(Color.Gray)
          
          Text('• Smooth animation between tabs')
            .fontSize(14)
            .fontColor(Color.Gray)
        }
        .cardStyle()
      }
      .width('100%')
      .padding(20)
    }
    .title('Popup Tabs Test')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack
    })
  }
}
