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
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

@Builder
export function PopupAnimationBuilder(name: string, param: Object) {
  PopupAnimationExample()
}

interface struct1 { curve: Curve, label: string }

@Entry
@Component
struct PopupAnimationExample {
  pathStack: NavPathStack = new NavPathStack()
  
  @State showPopup1: boolean = false
  @State showPopup2: boolean = false
  @State showPopup3: boolean = false
  @State showPopup4: boolean = false
  @State showPopup5: boolean = false
  
  @State animationDuration: number = 300
  @State animationCurve: Curve = Curve.EaseInOut
  
  @Builder
  popupContent(title: string) {
    Column({ space: 15 }) {
      Text(title)
        .fontSize(18)
        .fontWeight(FontWeight.Bold)
      
      Divider()
      
      Text('Animation Settings')
        .fontSize(14)
        .fontColor(Color.Gray)
      
      Row() {
        Text('Duration:')
        Blank()
        Text(this.animationDuration + 'ms')
          .fontColor(Color.Blue)
      }
      .width('100%')
      .padding(5)
      
      Row() {
        Text('Curve:')
        Blank()
        Text(this.animationCurve.toString())
          .fontColor(Color.Blue)
      }
      .width('100%')
      .padding(5)
      
      Divider()
      
      Button('Close')
        .width('100%')
        .onClick(() => {
          this.closePopup(title)
        })
    }
    .width(280)
    .padding(20)
    .backgroundColor(Color.White)
    .borderRadius(10)
  }
  
  closePopup(title: string) {
    if (title === 'Fade In') {
      this.showPopup1 = false
    } else if (title === 'Scale In') {
      this.showPopup2 = false
    } else if (title === 'Slide Up') {
      this.showPopup3 = false
    } else if (title === 'Rotate In') {
      this.showPopup4 = false
    } else if (title === 'Custom') {
      this.showPopup5 = false
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
        Text('Popup Animation Test')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 20 })
        
        Column() {
          Text('Animation Configuration')
            .fontSize(18)
            .fontWeight(FontWeight.Bold)
            .margin({ bottom: 10 })
          
          Row() {
            Text('Duration: ' + this.animationDuration + 'ms')
            Slider({
              min: 100,
              max: 1000,
              value: this.animationDuration,
              step: 50
            })
              .width('60%')
              .onChange((value: number) => {
                this.animationDuration = value
              })
          }
          .width('100%')
          .padding(5)
          
          Text('Animation Curve')
            .fontSize(14)
            .margin({ top: 10 })
          
          Row({ space: 10 }) {
            ForEach([
              { curve: Curve.EaseIn, label: 'EaseIn' },
              { curve: Curve.EaseOut, label: 'EaseOut' },
              { curve: Curve.EaseInOut, label: 'EaseInOut' },
              { curve: Curve.FastOutSlowIn, label: 'FastOut' }
            ], (item: struct1) => {
              Button(item.label)
                .width('24%')
                .height(40)
                .fontSize(10)
                .backgroundColor(this.animationCurve === item.curve ? Color.Blue : Color.Gray)
                .onClick(() => {
                  this.animationCurve = item.curve
                })
            })
          }
          .width('100%')
        }
        .cardStyle()
        
        Column() {
          Text('Fade In Animation')
            .fontSize(18)
            .fontWeight(FontWeight.Bold)
            .margin({ bottom: 10 })
          
          Text('Popup fades in smoothly')
            .fontSize(14)
            .fontColor(Color.Gray)
            .margin({ bottom: 10 })
          
          Button('Show Fade In Popup')
            .myButtonStyle()
            .onClick(() => {
              this.showPopup1 = true
            })
            .bindPopup(this.showPopup1, {
              builder: this.popupContent('Fade In'),
              placement: Placement.Bottom,
              mask: true,
              onStateChange: (e) => {
                if (!e.isVisible) {
                  this.showPopup1 = false
                }
              }
            })
        }
        .cardStyle()
        
        Column() {
          Text('Scale In Animation')
            .fontSize(18)
            .fontWeight(FontWeight.Bold)
            .margin({ bottom: 10 })
          
          Text('Popup scales in from center')
            .fontSize(14)
            .fontColor(Color.Gray)
            .margin({ bottom: 10 })
          
          Button('Show Scale In Popup')
            .myButtonStyle()
            .onClick(() => {
              this.showPopup2 = true
            })
            .bindPopup(this.showPopup2, {
              builder: this.popupContent('Scale In'),
              placement: Placement.Bottom,
              mask: true,
              onStateChange: (e) => {
                if (!e.isVisible) {
                  this.showPopup2 = false
                }
              }
            })
        }
        .cardStyle()
        
        Column() {
          Text('Slide Up Animation')
            .fontSize(18)
            .fontWeight(FontWeight.Bold)
            .margin({ bottom: 10 })
          
          Text('Popup slides up from bottom')
            .fontSize(14)
            .fontColor(Color.Gray)
            .margin({ bottom: 10 })
          
          Button('Show Slide Up Popup')
            .myButtonStyle()
            .onClick(() => {
              this.showPopup3 = true
            })
            .bindPopup(this.showPopup3, {
              builder: this.popupContent('Slide Up'),
              placement: Placement.Bottom,
              mask: true,
              onStateChange: (e) => {
                if (!e.isVisible) {
                  this.showPopup3 = false
                }
              }
            })
        }
        .cardStyle()
        
        Column() {
          Text('Rotate In Animation')
            .fontSize(18)
            .fontWeight(FontWeight.Bold)
            .margin({ bottom: 10 })
          
          Text('Popup rotates in')
            .fontSize(14)
            .fontColor(Color.Gray)
            .margin({ bottom: 10 })
          
          Button('Show Rotate In Popup')
            .myButtonStyle()
            .onClick(() => {
              this.showPopup4 = true
            })
            .bindPopup(this.showPopup4, {
              builder: this.popupContent('Rotate In'),
              placement: Placement.Bottom,
              mask: true,
              onStateChange: (e) => {
                if (!e.isVisible) {
                  this.showPopup4 = false
                }
              }
            })
        }
        .cardStyle()
        
        Column() {
          Text('Custom Animation')
            .fontSize(18)
            .fontWeight(FontWeight.Bold)
            .margin({ bottom: 10 })
          
          Text('Popup with custom animation')
            .fontSize(14)
            .fontColor(Color.Gray)
            .margin({ bottom: 10 })
          
          Button('Show Custom Popup')
            .onClick(() => {
              this.showPopup5 = true
            })
            .bindPopup(this.showPopup5, {
              builder: this.popupContent('Custom'),
              placement: Placement.Bottom,
              mask: true,
              onStateChange: (e) => {
                if (!e.isVisible) {
                  this.showPopup5 = false
                }
              }
            })
        }
        .cardStyle()
      }
      .width('100%')
      .padding(20)
    }
    .title('Popup Animation Test')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack
    })
  }
}
