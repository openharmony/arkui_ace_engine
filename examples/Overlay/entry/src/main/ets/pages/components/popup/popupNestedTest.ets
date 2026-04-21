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
export function PopupNestedBuilder(name: string, param: Object) {
  PopupNestedExample()
}

@Entry
@Component
struct PopupNestedExample {
  pathStack: NavPathStack = new NavPathStack()
  
  @State showPopup1: boolean = false
  @State showPopup2: boolean = false
  @State showPopup3: boolean = false
  @State showPopup4: boolean = false
  
  @State nestedLevel: number = 0
  @State maxLevel: number = 3
  
  @Builder
  level1Popup() {
    Column({ space: 15 }) {
      Text('Level 1 Popup')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)
      
      Divider()
      
      Text('Current Level: 1')
        .fontSize(14)
        .fontColor(Color.Blue)
      
      Text('Max Level: ' + this.maxLevel)
        .fontSize(14)
        .fontColor(Color.Gray)
      
      if (this.nestedLevel < this.maxLevel) {
        Button('Show Level 2')
          .width('100%')
          .onClick(() => {
            this.showPopup2 = true
            this.nestedLevel = 2
          })
          .bindPopup(this.showPopup2, {
            builder: this.level2Popup(),
            placement: Placement.Right,
            onStateChange: (e) => {
              if (!e.isVisible) {
                this.showPopup2 = false
                this.nestedLevel = 1
              }
            }
          })
      }
      
      Divider()
      
      Button('Close')
        .width('100%')
        .onClick(() => {
          this.showPopup1 = false
          this.nestedLevel = 0
        })
    }
    .width(280)
    .padding(20)
    .backgroundColor(Color.White)
    .borderRadius(10)
  }
  
  @Builder
  level2Popup() {
    Column({ space: 15 }) {
      Text('Level 2 Popup')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)
      
      Divider()
      
      Text('Current Level: 2')
        .fontSize(14)
        .fontColor(Color.Blue)
      
      Text('Max Level: ' + this.maxLevel)
        .fontSize(14)
        .fontColor(Color.Gray)
      
      if (this.nestedLevel < this.maxLevel) {
        Button('Show Level 3')
          .width('100%')
          .onClick(() => {
            this.showPopup3 = true
            this.nestedLevel = 3
          })
          .bindPopup(this.showPopup3, {
            builder: this.level3Popup(),
            placement: Placement.Right,
            onStateChange: (e) => {
              if (!e.isVisible) {
                this.showPopup3 = false
                this.nestedLevel = 2
              }
            }
          })
      }
      
      Button('Back to Level 1')
        .width('100%')
        .onClick(() => {
          this.showPopup2 = false
          this.nestedLevel = 1
        })
    }
    .width(280)
    .padding(20)
    .backgroundColor(Color.White)
    .borderRadius(10)
  }
  
  @Builder
  level3Popup() {
    Column({ space: 15 }) {
      Text('Level 3 Popup')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)
      
      Divider()
      
      Text('Current Level: 3')
        .fontSize(14)
        .fontColor(Color.Blue)
      
      Text('Max Level: ' + this.maxLevel)
        .fontSize(14)
        .fontColor(Color.Gray)
      
      if (this.nestedLevel < this.maxLevel) {
        Button('Show Level 4')
          .width('100%')
          .onClick(() => {
            this.showPopup4 = true
            this.nestedLevel = 4
          })
          .bindPopup(this.showPopup4, {
            builder: this.level4Popup(),
            placement: Placement.Right,
            onStateChange: (e) => {
              if (!e.isVisible) {
                this.showPopup4 = false
                this.nestedLevel = 3
              }
            }
          })
      }
      
      Button('Back to Level 2')
        .width('100%')
        .onClick(() => {
          this.showPopup3 = false
          this.nestedLevel = 2
        })
    }
    .width(280)
    .padding(20)
    .backgroundColor(Color.White)
    .borderRadius(10)
  }
  
  @Builder
  level4Popup() {
    Column({ space: 15 }) {
      Text('Level 4 Popup')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)
      
      Divider()
      

      
      Text('Current Level: 4')
        .fontSize(14)
        .fontColor(Color.Blue)
      
      Text('Max Level: ' + this.maxLevel)
        .fontSize(14)
        .fontColor(Color.Gray)
      
      Text('Maximum nesting level reached')
        .fontSize(14)
        .fontColor(Color.Red)
      
      Button('Back to Level 3')
        .width('100%')
        .onClick(() => {
          this.showPopup4 = false
          this.nestedLevel = 3
        })
    }
    .width(280)
    .padding(20)
    .backgroundColor(Color.White)
    .borderRadius(10)
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
        Text('Popup Nested Test')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 20 })
        
        Column() {
          Text('Nested Configuration')
            .fontSize(18)
            .fontWeight(FontWeight.Bold)
            .margin({ bottom: 10 })
          
          Row() {
            Text('Max Nesting Level: ' + this.maxLevel)
            Slider({
              min: 1,
              max: 5,
              value: this.maxLevel,
              step: 1
            })
              .width('60%')
              .onChange((value: number) => {
                this.maxLevel = value
              })
          }
          .width('100%')
          .padding(5)
          
          Row() {
            Text('Current Level: ' + this.nestedLevel)
            Blank()
            Text(this.nestedLevel + ' / ' + this.maxLevel)
              .fontSize(16)
              .fontWeight(FontWeight.Bold)
              .fontColor(Color.Blue)
          }
          .width('100%')
          .padding(5)
        }
        .cardStyle()
        
        Column() {
          Text('Nested Popup Demo')
            .fontSize(18)
            .fontWeight(FontWeight.Bold)
            .margin({ bottom: 10 })
          
          Text('Click to open nested popups')
            .fontSize(14)
            .fontColor(Color.Gray)
            .margin({ bottom: 10 })
          
          Button('Start Nested Popup')
            .myButtonStyle()
            .onClick(() => {
              this.showPopup1 = true
              this.nestedLevel = 1
            })
            .bindPopup(this.showPopup1, {
              builder: this.level1Popup(),
              placement: Placement.Bottom,
              onStateChange: (e) => {
                if (!e.isVisible) {
                  this.showPopup1 = false
                  this.nestedLevel = 0
                }
              }
            })
        }
        .cardStyle()
        
        Column() {
          Text('Nesting Information')
            .fontSize(18)
            .fontWeight(FontWeight.Bold)
            .margin({ bottom: 10 })
          
          Text('Maximum nesting level: ' + this.maxLevel)
            .fontSize(14)
            .fontColor(Color.Gray)
          
          Text('Each popup opens to the right')
            .fontSize(14)
            .fontColor(Color.Gray)
          
          Text('Click back to return to previous level')
            .fontSize(14)
            .fontColor(Color.Gray)
        }
        .cardStyle()
      }
      .width('100%')
      .padding(20)
    }
    .title('Popup Nested Test')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack
    })
  }
}
