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
struct AdvancedUITestPage {
  @State currentPage: number = 0
  private pages: string[] = ['Components', 'Layouts', 'Animations', 'Gestures', 'Forms']

  build() {
    Tabs({ index: this.currentPage }) {
      TabContent() {
        ComponentsTestPage()
      }
      .tabBar('Components')

      TabContent() {
        LayoutsTestPage()
      }
      .tabBar('Layouts')

      TabContent() {
        AnimationsTestPage()
      }
      .tabBar('Animations')

      TabContent() {
        GesturesTestPage()
      }
      .tabBar('Gestures')

      TabContent() {
        FormsTestPage()
      }
      .tabBar('Forms')
    }
    .width('100%')
    .height('100%')
    .onChange((index: number) => {
      this.currentPage = index
    })
  }
}

@Component
struct ComponentsTestPage {
  @State showText: boolean = true
  @State showButton: boolean = true
  @State showImage: boolean = true
  @State showSwitch: boolean = true
  @State showProgress: boolean = true
  @State showSlider: boolean = true
  @State showRating: boolean = true
  @State showBadge: boolean = true

  build() {
    Scroll() {
      Column() {
        Text('Components Test Page')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 20 })

        if (this.showText) {
          TextComponentDemo()
        }

        if (this.showButton) {
          ButtonComponentDemo()
        }

        if (this.showImage) {
          ImageComponentDemo()
        }

        if (this.showSwitch) {
          SwitchComponentDemo()
        }

        if (this.showProgress) {
          ProgressComponentDemo()
        }

        if (this.showSlider) {
          SliderComponentDemo()
        }

        if (this.showRating) {
          RatingComponentDemo()
        }

        if (this.showBadge) {
          BadgeComponentDemo()
        }
      }
      .width('100%')
      .padding(20)
    }
    .width('100%')
    .height('100%')
  }
}

@Component
struct TextComponentDemo {
  @State fontSize: number = 16
  @State fontWeight: number = FontWeight.Normal
  @State textColor: string = '#000000'
  @State textContent: string = 'Hello World'

  build() {
    Column() {
      Text('Text Component Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })

      Text(this.textContent)
        .fontSize(this.fontSize)
        .fontWeight(this.fontWeight)
        .fontColor(this.textColor)
        .margin({ bottom: 15 })

      TextInput({ placeholder: 'Enter text' })
        .onChange((value: string) => {
          this.textContent = value
        })
        .margin({ bottom: 10 })

      Row() {
        Button('Size +')
          .onClick(() => {
            this.fontSize = Math.min(this.fontSize + 2, 32)
          })

        Button('Size -')
          .onClick(() => {
            this.fontSize = Math.max(this.fontSize - 2, 12)
          })

        Button('Bold')
          .onClick(() => {
            this.fontWeight = this.fontWeight === FontWeight.Bold ? FontWeight.Normal : FontWeight.Bold
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct ButtonComponentDemo {
  @State buttonType: string = 'Normal'
  @State buttonSize: string = 'Medium'
  @State clickCount: number = 0

  build() {
    Column() {
      Text('Button Component Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })

      Button('Click Me')
        .type(this.buttonType === 'Normal' ? ButtonType.Normal : 
              this.buttonType === 'Capsule' ? ButtonType.Capsule : ButtonType.Circle)
        .width(this.buttonSize === 'Medium' ? 150 : this.buttonSize === 'Large' ? 200 : 100)
        .onClick(() => {
          this.clickCount++
        })
        .margin({ bottom: 15 })

      Text('Click Count: ' + this.clickCount)
        .fontSize(16)
        .margin({ bottom: 10 })

      Row() {
        Button('Normal')
          .onClick(() => {
            this.buttonType = 'Normal'
          })

        Button('Capsule')
          .onClick(() => {
            this.buttonType = 'Capsule'
          })

        Button('Circle')
          .onClick(() => {
            this.buttonType = 'Circle'
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct ImageComponentDemo {
  @State imageWidth: number = 200
  @State imageHeight: number = 200
  @State borderRadius: number = 0
  @State opacity: number = 1.0

  build() {
    Column() {
      Text('Image Component Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })

      Image($r('app.media.icon'))
        .width(this.imageWidth)
        .height(this.imageHeight)
        .borderRadius(this.borderRadius)
        .opacity(this.opacity)
        .margin({ bottom: 15 })

      Row() {
        Button('Width +')
          .onClick(() => {
            this.imageWidth = Math.min(this.imageWidth + 20, 300)
          })

        Button('Width -')
          .onClick(() => {
            this.imageWidth = Math.max(this.imageWidth - 20, 100)
          })

        Button('Height +')
          .onClick(() => {
            this.imageHeight = Math.min(this.imageHeight + 20, 300)
          })

        Button('Height -')
          .onClick(() => {
            this.imageHeight = Math.max(this.imageHeight - 20, 100)
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct SwitchComponentDemo {
  @State switchState: boolean = false
  @State switchColor: string = '#007DFF'

  build() {
    Column() {
      Text('Switch Component Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })

      Switch({ type: SwitchType.Checkbox, name: 'switch1' })
        .selected(this.switchState)
        .selectedColor(this.switchColor)
        .onChange((value: boolean) => {
          this.switchState = value
        })
        .margin({ bottom: 15 })

      Text('Switch State: ' + (this.switchState ? 'ON' : 'OFF'))
        .fontSize(16)
        .margin({ bottom: 10 })

      Button('Toggle Switch')
        .onClick(() => {
          this.switchState = !this.switchState
        })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct ProgressComponentDemo {
  @State progressValue: number = 50
  @State progressType: string = 'Linear'

  build() {
    Column() {
      Text('Progress Component Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })

      if (this.progressType === 'Linear') {
        Progress({ value: this.progressValue, total: 100, type: ProgressType.Linear })
          .width('100%')
          .margin({ bottom: 15 })
      } else if (this.progressType === 'Ring') {
        Progress({ value: this.progressValue, total: 100, type: ProgressType.Ring })
          .width(100)
          .height(100)
          .margin({ bottom: 15 })
      } else {
        Progress({ value: this.progressValue, total: 100, type: ProgressType.ScaleRing })
          .width(100)
          .height(100)
          .margin({ bottom: 15 })
      }

      Text('Progress: ' + this.progressValue + '%')
        .fontSize(16)
        .margin({ bottom: 10 })

      Row() {
        Button('Linear')
          .onClick(() => {
            this.progressType = 'Linear'
          })

        Button('Ring')
          .onClick(() => {
            this.progressType = 'Ring'
          })

        Button('ScaleRing')
          .onClick(() => {
            this.progressType = 'ScaleRing'
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct SliderComponentDemo {
  @State sliderValue: number = 50
  @State sliderMin: number = 0
  @State sliderMax: number = 100

  build() {
    Column() {
      Text('Slider Component Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })

      Slider({ value: this.sliderValue, min: this.sliderMin, max: this.sliderMax, style: SliderStyle.OutSet })
        .blockColor('#007DFF')
        .trackColor('#E5E5E5')
        .selectedColor('#007DFF')
        .showSteps(true)
        .onChange((value: number) => {
          this.sliderValue = value
        })
        .margin({ bottom: 15 })

      Text('Slider Value: ' + this.sliderValue.toFixed(0))
        .fontSize(16)
        .margin({ bottom: 10 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct RatingComponentDemo {
  @State rating: number = 3
  @State maxRating: number = 5

  build() {
    Column() {
      Text('Rating Component Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })

      Row() {
        ForEach([0, 1, 2, 3, 4], (index: number) => {
          Text('★')
            .fontSize(30)
            .fontColor(index < this.rating ? '#FFD700' : '#CCCCCC')
            .onClick(() => {
              this.rating = index + 1
            })
        })
      }
      .justifyContent(FlexAlign.Center)
      .margin({ bottom: 15 })

      Text('Rating: ' + this.rating + ' / ' + this.maxRating)
        .fontSize(16)
        .margin({ bottom: 10 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct BadgeComponentDemo {
  @State badgeValue: number = 5
  @State showBadge: boolean = true

  build() {
    Column() {
      Text('Badge Component Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })

      if (this.showBadge) {
        Badge({
          value: this.badgeValue,
          position: { x: 16, y: 0 }
        }) {
          Text('Badge Demo')
            .fontSize(16)
            .padding(10)
            .backgroundColor('#E5E5E5')
            .borderRadius(5)
        }
        .margin({ bottom: 15 })
      }

      Text('Badge Value: ' + this.badgeValue)
        .fontSize(16)
        .margin({ bottom: 10 })

      Row() {
        Button('Value +')
          .onClick(() => {
            this.badgeValue++
          })

        Button('Value -')
          .onClick(() => {
            this.badgeValue = Math.max(this.badgeValue - 1, 0)
          })

        Button('Toggle')
          .onClick(() => {
            this.showBadge = !this.showBadge
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct LayoutsTestPage {
  @State showFlex: boolean = true
  @State showGrid: boolean = true
  @State showStack: boolean = true
  @State showList: boolean = true

  build() {
    Scroll() {
      Column() {
        Text('Layouts Test Page')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 20 })

        if (this.showFlex) {
          FlexLayoutDemo()
        }

        if (this.showGrid) {
          GridLayoutDemo()
        }

        if (this.showStack) {
          StackLayoutDemo()
        }

        if (this.showList) {
          ListLayoutDemo()
        }
      }
      .width('100%')
      .padding(20)
    }
    .width('100%')
    .height('100%')
  }
}

@Component
struct FlexLayoutDemo {
  @State flexDirection: string = 'Row'
  @State justifyContent: string = 'Start'
  @State alignItems: string = 'Center'

  build() {
    Column() {
      Text('Flex Layout Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })

      Flex({
        direction: this.flexDirection === 'Row' ? FlexDirection.Row : 
                   this.flexDirection === 'Column' ? FlexDirection.Column : FlexDirection.RowReverse,
        justifyContent: this.justifyContent === 'Start' ? FlexAlign.Start : 
                       this.justifyContent === 'Center' ? FlexAlign.Center : FlexAlign.End,
        alignItems: ItemAlign.Center
      }) {
        Text('Item 1')
          .width(80)
          .height(40)
          .backgroundColor('#FF6B6B')
          .margin(5)

        Text('Item 2')
          .width(80)
          .height(40)
          .backgroundColor('#4ECDC4')
          .margin(5)

        Text('Item 3')
          .width(80)
          .height(40)
          .backgroundColor('#45B7D1')
          .margin(5)
      }
      .width('100%')
      .height(100)
      .backgroundColor('#F0F0F0')
      .margin({ bottom: 15 })

      Text('Direction: ' + this.flexDirection + ', Justify: ' + this.justifyContent)
        .fontSize(14)
        .margin({ bottom: 10 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct GridLayoutDemo {
  @State columns: string = '1fr 1fr'
  @State rows: string = '1fr 1fr'

  build() {
    Column() {
      Text('Grid Layout Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })

      Grid() {
        GridItem() {
          Text('1')
            .fontSize(24)
            .width('100%')
            .height('100%')
            .textAlign(TextAlign.Center)
            .backgroundColor('#FF6B6B')
        }

        GridItem() {
          Text('2')
            .fontSize(24)
            .width('100%')
            .height('100%')
            .textAlign(TextAlign.Center)
            .backgroundColor('#4ECDC4')
        }

        GridItem() {
          Text('3')
            .fontSize(24)
            .width('100%')
            .height('100%')
            .textAlign(TextAlign.Center)
            .backgroundColor('#45B7D1')
        }

        GridItem() {
          Text('4')
            .fontSize(24)
            .width('100%')
            .height('100%')
            .textAlign(TextAlign.Center)
            .backgroundColor('#96CEB4')
        }
      }
      .columnsTemplate(this.columns)
      .rowsTemplate(this.rows)
      .width('100%')
      .height(200)
      .margin({ bottom: 15 })

      Text('Columns: ' + this.columns + ', Rows: ' + this.rows)
        .fontSize(14)
        .margin({ bottom: 10 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct StackLayoutDemo {
  @State alignContent: string = 'Center'

  build() {
    Column() {
      Text('Stack Layout Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })

      Stack({ alignContent: this.alignContent === 'Center' ? Alignment.Center : 
                                 this.alignContent === 'TopStart' ? Alignment.TopStart : Alignment.BottomEnd }) {
        Text('Bottom')
          .width(200)
          .height(200)
          .fontSize(20)
          .textAlign(TextAlign.Center)
          .backgroundColor('#FF6B6B')

        Text('Middle')
          .width(150)
          .height(150)
          .fontSize(20)
          .textAlign(TextAlign.Center)
          .backgroundColor('#4ECDC4')

        Text('Top')
          .width(100)
          .height(100)
          .fontSize(20)
          .textAlign(TextAlign.Center)
          .backgroundColor('#45B7D1')
      }
      .width('100%')
      .height(220)
      .margin({ bottom: 15 })

      Text('Align: ' + this.alignContent)
        .fontSize(14)
        .margin({ bottom: 10 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct ListLayoutDemo {
  private items: string[] = Array.from({ length: 10 }, (_, i) => 'Item ' + (i + 1))

  build() {
    Column() {
      Text('List Layout Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })

      List() {
        ForEach(this.items, (item: string) => {
          ListItem() {
            Text(item)
              .fontSize(16)
              .padding(15)
              .width('100%')
          }
        })
      }
      .width('100%')
      .height(300)
      .margin({ bottom: 15 })

      Text('Total Items: ' + this.items.length)
        .fontSize(14)
        .margin({ bottom: 10 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct AnimationsTestPage {
  @State showBasic: boolean = true
  @State showTransition: boolean = true
  @State showKeyframe: boolean = true

  build() {
    Scroll() {
      Column() {
        Text('Animations Test Page')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 20 })

        if (this.showBasic) {
          BasicAnimationDemo()
        }

        if (this.showTransition) {
          TransitionAnimationDemo()
        }

        if (this.showKeyframe) {
          KeyframeAnimationDemo()
        }
      }
      .width('100%')
      .padding(20)
    }
    .width('100%')
    .height('100%')
  }
}

@Component
struct BasicAnimationDemo {
  @State scale: number = 1.0
  @State opacity: number = 1.0
  @State rotation: number = 0

  build() {
    Column() {
      Text('Basic Animation Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })

      Text('Animated Box')
        .width(100)
        .height(100)
        .fontSize(16)
        .textAlign(TextAlign.Center)
        .backgroundColor('#FF6B6B')
        .scale({ x: this.scale, y: this.scale })
        .opacity(this.opacity)
        .rotate({ angle: this.rotation })
        .margin({ bottom: 15 })

      Row() {
        Button('Scale')
          .onClick(() => {
            this.scale = this.scale === 1.0 ? 1.5 : 1.0
          })

        Button('Opacity')
          .onClick(() => {
            this.opacity = this.opacity === 1.0 ? 0.5 : 1.0
          })

        Button('Rotate')
          .onClick(() => {
            this.rotation = this.rotation === 0 ? 45 : 0
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct KeyframeAnimationDemo {
  @State animate: boolean = false

  build() {
    Column() {
      Text('Keyframe Animation Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })

      Text('Keyframe Animation')
        .width(150)
        .height(50)
        .fontSize(16)
        .textAlign(TextAlign.Center)
        .backgroundColor('#45B7D1')
        .margin({ bottom: 15 })

      Button('Start Animation')
        .onClick(() => {
          this.animate = !this.animate
        })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct GesturesTestPage {
  @State showTap: boolean = true
  @State showLongPress: boolean = true
  @State showPan: boolean = true
  @State showPinch: boolean = true

  build() {
    Scroll() {
      Column() {
        Text('Gestures Test Page')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 20 })

        if (this.showTap) {
          TapGestureDemo()
        }

        if (this.showLongPress) {
          LongPressGestureDemo()
        }

        if (this.showPan) {
          PanGestureDemo()
        }

        if (this.showPinch) {
          PinchGestureDemo()
        }
      }
      .width('100%')
      .padding(20)
    }
    .width('100%')
    .height('100%')
  }
}

@Component
struct TapGestureDemo {
  @State tapCount: number = 0
  @State lastTapTime: string = ''

  build() {
    Column() {
      Text('Tap Gesture Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })

      Text('Tap Me')
        .width(200)
        .height(100)
        .fontSize(16)
        .textAlign(TextAlign.Center)
        .backgroundColor('#FF6B6B')
        .gesture(
          TapGesture()
            .onAction(() => {
              this.tapCount++
              this.lastTapTime = new Date().toLocaleTimeString()
            })
        )
        .margin({ bottom: 15 })

      Text('Tap Count: ' + this.tapCount)
        .fontSize(14)
        .margin({ bottom: 5 })

      Text('Last Tap: ' + this.lastTapTime)
        .fontSize(14)
        .margin({ bottom: 10 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct LongPressGestureDemo {
  @State longPressCount: number = 0
  @State pressDuration: number = 0

  build() {
    Column() {
      Text('Long Press Gesture Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })

      Text('Long Press Me')
        .width(200)
        .height(100)
        .fontSize(16)
        .textAlign(TextAlign.Center)
        .backgroundColor('#4ECDC4')
        .gesture(
          LongPressGesture({ repeat: false })
            .onAction(() => {
              this.longPressCount++
              this.pressDuration = 500
            })
        )
        .margin({ bottom: 15 })

      Text('Long Press Count: ' + this.longPressCount)
        .fontSize(14)
        .margin({ bottom: 5 })

      Text('Duration: ' + this.pressDuration + 'ms')
        .fontSize(14)
        .margin({ bottom: 10 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct PanGestureDemo {
  @State offsetX: number = 0
  @State offsetY: number = 0
  @State direction: string = 'None'

  build() {
    Column() {
      Text('Pan Gesture Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })

      Text('Drag Me')
        .width(200)
        .height(100)
        .fontSize(16)
        .textAlign(TextAlign.Center)
        .backgroundColor('#45B7D1')
        .translate({ x: this.offsetX, y: this.offsetY })
        .gesture(
          PanGesture({ direction: PanDirection.All })
            .onActionUpdate((event: GestureEvent) => {
              this.offsetX = event.offsetX
              this.offsetY = event.offsetY
            })
        )
        .margin({ bottom: 15 })
      Text('Offset: (' + this.offsetX.toFixed(0) + ', ' + this.offsetY.toFixed(0) + ')')
        .fontSize(14)
        .margin({ bottom: 5 })
      Text('Direction: ' + this.direction)
        .fontSize(14)
        .margin({ bottom: 10 })
      Button('Reset Position')
        .onClick(() => {
          this.offsetX = 0
          this.offsetY = 0
        })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct PinchGestureDemo {
  @State scale: number = 1.0
  @State pinchCenter: string = ''

  build() {
    Column() {
      Text('Pinch Gesture Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })

      Text('Pinch Me')
        .width(200)
        .height(100)
        .fontSize(16)
        .textAlign(TextAlign.Center)
        .backgroundColor('#96CEB4')
        .scale({ x: this.scale, y: this.scale })
        .gesture(
          PinchGesture({ fingers: 2 })
            .onActionUpdate((event: GestureEvent) => {
              this.scale = event.scale
            })
        )
        .margin({ bottom: 15 })

      Text('Scale: ' + this.scale.toFixed(2))
        .fontSize(14)
        .margin({ bottom: 5 })

      Text('Center: ' + this.pinchCenter)
        .fontSize(14)
        .margin({ bottom: 10 })

      Button('Reset Scale')
        .onClick(() => {
          this.scale = 1.0
        })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct FormsTestPage {
  @State showTextInput: boolean = true
  @State showTextArea: boolean = true
  @State showCheckbox: boolean = true
  @State showRadio: boolean = true
  @State showToggle: boolean = true

  build() {
    Scroll() {
      Column() {
        Text('Forms Test Page')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 20 })

        if (this.showTextInput) {
          TextInputDemo()
        }

        if (this.showTextArea) {
          TextAreaDemo()
        }

        if (this.showCheckbox) {
          CheckboxDemo()
        }

        if (this.showRadio) {
          RadioDemo()
        }

        if (this.showToggle) {
          ToggleDemo()
        }
      }
      .width('100%')
      .padding(20)
    }
    .width('100%')
    .height('100%')
  }
}

@Component
struct TextInputDemo {
  @State inputValue: string = ''
  @State placeholder: string = 'Enter text...'
  @State inputType: string = 'Normal'

  build() {
    Column() {
      Text('Text Input Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })

      TextInput({ placeholder: this.placeholder })
        .type(this.inputType === 'Normal' ? InputType.Normal : 
              this.inputType === 'Number' ? InputType.Number : InputType.Password)
        .onChange((value: string) => {
          this.inputValue = value
        })
        .margin({ bottom: 15 })

      Text('Input Value: ' + this.inputValue)
        .fontSize(14)
        .margin({ bottom: 10 })

      Row() {
        Button('Normal')
          .onClick(() => {
            this.inputType = 'Normal'
            this.placeholder = 'Enter text...'
          })

        Button('Number')
          .onClick(() => {
            this.inputType = 'Number'
            this.placeholder = 'Enter number...'
          })

        Button('Password')
          .onClick(() => {
            this.inputType = 'Password'
            this.placeholder = 'Enter password...'
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct TextAreaDemo {
  @State textValue: string = ''
  @State placeholder: string = 'Enter multi-line text...'

  build() {
    Column() {
      Text('Text Area Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })

      TextArea({ placeholder: this.placeholder })
        .width('100%')
        .height(100)
        .onChange((value: string) => {
          this.textValue = value
        })
        .margin({ bottom: 15 })

      Text('Text Value: ' + this.textValue)
        .fontSize(14)
        .margin({ bottom: 10 })

      Text('Character Count: ' + this.textValue.length)
        .fontSize(14)
        .margin({ bottom: 10 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct CheckboxDemo {
  @State checkbox1: boolean = false
  @State checkbox2: boolean = false
  @State checkbox3: boolean = false

  build() {
    Column() {
      Text('Checkbox Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })

      Row() {
        Checkbox({ name: 'checkbox1' })
          .select(this.checkbox1)
          .onChange((value: boolean) => {
            this.checkbox1 = value
          })

        Text('Option 1')
          .fontSize(16)
          .margin({ left: 10 })
      }
      .margin({ bottom: 10 })

      Row() {
        Checkbox({ name: 'checkbox2' })
          .select(this.checkbox2)
          .onChange((value: boolean) => {
            this.checkbox2 = value
          })

        Text('Option 2')
          .fontSize(16)
          .margin({ left: 10 })
      }
      .margin({ bottom: 10 })

      Row() {
        Checkbox({ name: 'checkbox3' })
          .select(this.checkbox3)
          .onChange((value: boolean) => {
            this.checkbox3 = value
          })

        Text('Option 3')
          .fontSize(16)
          .margin({ left: 10 })
      }
      .margin({ bottom: 15 })

      Text('Selected: ' + (this.checkbox1 ? '1 ' : ''))
        .fontSize(14)
      Text('Selected: ' + (this.checkbox2 ? '2 ' : ''))
        .fontSize(14)
      Text('Selected: ' + (this.checkbox3 ? '3' : ''))
        .fontSize(14)
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct RadioDemo {
  @State selectedRadio: string = 'option1'
  private radioGroup: string = 'radioGroup1'

  build() {
    Column() {
      Text('Radio Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })

      Row() {
        Radio({ value: 'option1', group: this.radioGroup })
          .checked(this.selectedRadio === 'option1')
          .onChange((isChecked: boolean) => {
            if (isChecked) {
              this.selectedRadio = 'option1'
            }
          })

        Text('Option 1')
          .fontSize(16)
          .margin({ left: 10 })
      }
      .margin({ bottom: 10 })

      Row() {
        Radio({ value: 'option2', group: this.radioGroup })
          .checked(this.selectedRadio === 'option2')
          .onChange((isChecked: boolean) => {
            if (isChecked) {
              this.selectedRadio = 'option2'
            }
          })

        Text('Option 2')
          .fontSize(16)
          .margin({ left: 10 })
      }
      .margin({ bottom: 10 })

      Row() {
        Radio({ value: 'option3', group: this.radioGroup })
          .checked(this.selectedRadio === 'option3')
          .onChange((isChecked: boolean) => {
            if (isChecked) {
              this.selectedRadio = 'option3'
            }
          })

        Text('Option 3')
          .fontSize(16)
          .margin({ left: 10 })
      }
      .margin({ bottom: 15 })

      Text('Selected: ' + this.selectedRadio)
        .fontSize(14)
        .margin({ bottom: 10 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct ToggleDemo {
  @State toggleState: boolean = false
  @State toggleType: string = 'Switch'

  build() {
    Column() {
      Text('Toggle Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })

      Toggle({ type: this.toggleType === 'Switch' ? ToggleType.Switch : ToggleType.Checkbox })
        .selected(this.toggleState)
        .onChange((value: boolean) => {
          this.toggleState = value
        })
        .margin({ bottom: 15 })

      Text('Toggle State: ' + (this.toggleState ? 'ON' : 'OFF'))
        .fontSize(14)
        .margin({ bottom: 10 })

      Row() {
        Button('Switch')
          .onClick(() => {
            this.toggleType = 'Switch'
          })

        Button('Checkbox')
          .onClick(() => {
            this.toggleType = 'Checkbox'
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

// Additional advanced components

@Component
struct DatePickerDemo {
  @State selectedDate: Date = new Date()

  build() {
    Column() {
      Text('Date Picker Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })

      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2100-12-31'),
        selected: this.selectedDate
      })
      .onChange((value: DatePickerResult) => {
        this.selectedDate = new Date(value.year, value.month, value.day)
      })
      .margin({ bottom: 15 })

      Text('Selected Date: ' + this.selectedDate.toLocaleDateString())
        .fontSize(14)
        .margin({ bottom: 10 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct TimePickerDemo {
  @State selectedTime: Time = { hour: 12, minute: 0 }

  build() {
    Column() {
      Text('Time Picker Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })

      TimePicker({
        selected: this.selectedTime
      })
      .onChange((value: TimePickerResult) => {
        if (value.hour !== undefined) {
          this.selectedTime = { hour: value.hour, minute: value.minute }
        }
      })
      .margin({ bottom: 15 })

      Text('Selected Time: ' + this.selectedTime.hour + ':' + 
           (this.selectedTime.minute < 10 ? '0' : '') + this.selectedTime.minute)
        .fontSize(14)
        .margin({ bottom: 10 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct SelectDemo {
  @State selectedIndex: number = 0
  private options: string[] = ['Option 1', 'Option 2', 'Option 3', 'Option 4', 'Option 5']

  build() {
    Column() {
      Text('Select Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })

      Select(this.options)
        .selected(this.selectedIndex)
        .value(this.options[this.selectedIndex])
        .onSelect((index: number) => {
          this.selectedIndex = index
        })
        .margin({ bottom: 15 })

      Text('Selected: ' + this.options[this.selectedIndex])
        .fontSize(14)
        .margin({ bottom: 10 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct BlankDemo {
  @State blankCount: number = 0

  build() {
    Column() {
      Text('Blank Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })

      Blank()
        .width('100%')
        .height(50)
        .backgroundColor('#FF6B6B')
        .margin({ bottom: 15 })

      Text('Blank Count: ' + this.blankCount)
        .fontSize(14)
        .margin({ bottom: 10 })

      Button('Add Blank')
        .onClick(() => {
          this.blankCount++
        })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct DividerDemo {
  @State dividerColor: string = '#E5E5E5'
  @State strokeWidth: number = 1

  build() {
    Column() {
      Text('Divider Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })

      Text('Content Above')
        .fontSize(16)
        .margin({ bottom: 10 })

      Divider()
        .color(this.dividerColor)
        .strokeWidth(this.strokeWidth)
        .margin({ bottom: 10 })

      Text('Content Below')
        .fontSize(16)
        .margin({ bottom: 15 })

      Text('Stroke Width: ' + this.strokeWidth)
        .fontSize(14)
        .margin({ bottom: 10 })

      Row() {
        Button('Width +')
          .onClick(() => {
            this.strokeWidth = Math.min(this.strokeWidth + 1, 5)
          })

        Button('Width -')
          .onClick(() => {
            this.strokeWidth = Math.max(this.strokeWidth - 1, 1)
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct PanelDemo {
  @State showPanel: boolean = false

  build() {
    Column() {
      Text('Panel Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })
      Button('Show Panel')
        .onClick(() => {
          this.showPanel = true
        })
        .margin({ bottom: 15 })
      if (this.showPanel) {
        Panel() {
          Column() {
            Text('Panel Content')
              .fontSize(16)
              .margin({ bottom: 10 })
            Button('Close')
              .onClick(() => {
                this.showPanel = false
              })
          }
          .width('100%')
          .padding(20)
        }
        .type(PanelType.Foldable)
        .mode(PanelMode.Half)
      }
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct PopupDemo {
  @State showPopup: boolean = false

  build() {
    Column() {
      Text('Popup Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })
      Button('Show Popup')
        .onClick(() => {
          this.showPopup = true
        })
        .margin({ bottom: 15 })
      if (this.showPopup) {
        Popup() {
          Column() {
          Text('Popup Content')
              .fontSize(16)
              .margin({ bottom: 10 })
            Button('Close')
              .onClick(() => {
                this.showPopup = false
              })
          }
          .width('100%')
          .padding(20)
        }
      }
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct NavigationDemo {
  @State currentPath: string = '/home'

  build() {
    Column() {
      Text('Navigation Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })

      Text('Current Path: ' + this.currentPath)
        .fontSize(14)
        .margin({ bottom: 15 })

      Row() {
        Button('Home')
          .onClick(() => {
            this.currentPath = '/home'
          })

        Button('Profile')
          .onClick(() => {
            this.currentPath = '/profile'
          })

        Button('Settings')
          .onClick(() => {
            this.currentPath = '/settings'
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct SearchDemo {
  @State searchText: string = ''
  @State searchResults: string[] = []

  build() {
    Column() {
      Text('Search Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })

      Search({ value: this.searchText, placeholder: 'Search...' })
        .searchButton('Search')
        .width('100%')
        .onChange((value: string) => {
          this.searchText = value
        })
        .onSubmit(() => {
          this.performSearch()
        })
        .margin({ bottom: 15 })

      if (this.searchResults.length > 0) {
        Column() {
          ForEach(this.searchResults, (result: string) => {
            Text(result)
              .fontSize(14)
              .padding(10)
              .width('100%')
          })
        }
        .width('100%')
        .backgroundColor('#FFFFFF')
        .borderRadius(5)
        .padding(10)
      }
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }

  private performSearch(): void {
    this.searchResults = [
      'Result 1 for ' + this.searchText,
      'Result 2 for ' + this.searchText,
      'Result 3 for ' + this.searchText
    ]
  }
}

@Component
struct RichTextDemo {
  @State richTextContent: string = 'Hello World'

  build() {
    Column() {
      Text('Rich Text Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })

      RichText(this.richTextContent)
        .width('100%')
        .height(100)
        .backgroundColor('#FFFFFF')
        .margin({ bottom: 15 })

      TextInput({ placeholder: 'Enter rich text...' })
        .onChange((value: string) => {
          this.richTextContent = value
        })
        .margin({ bottom: 10 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct SpanDemo {
  @State text: string = 'Hello'
  @State highlight: string = 'World'

  build() {
    Column() {
      Text('Span Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })

      Text() {
        Span(this.text)
          .fontSize(16)
          .fontColor('#000000')

        Span(' ')

        Span(this.highlight)
          .fontSize(16)
          .fontColor('#FF6B6B')
          .fontWeight(FontWeight.Bold)
      }
      .margin({ bottom: 15 })

      TextInput({ placeholder: 'Enter text...' })
        .onChange((value: string) => {
          this.text = value
        })
        .margin({ bottom: 10 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct MarqueeDemo {
  @State marqueeText: string = 'This is a scrolling marquee text demo'

  build() {
    Column() {
      Text('Marquee Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })

      Marquee() {
        Text(this.marqueeText)
          .fontSize(16)
      }
      .width('100%')
      .height(40)
      .backgroundColor('#FFFFFF')
      .margin({ bottom: 15 })

      TextInput({ placeholder: 'Enter marquee text...' })
        .onChange((value: string) => {
          this.marqueeText = value
        })
        .margin({ bottom: 10 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct DataPanelDemo {
  @State panelData: string[] = ['Data 1', 'Data 2', 'Data 3']

  build() {
    Column() {
      Text('Data Panel Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })

      DataPanel() {
        ForEach(this.panelData, (data: string) => {
          Text(data)
            .fontSize(14)
            .padding(10)
            .width('100%')
        })
      }
      .width('100%')
      .height(150)
      .backgroundColor('#FFFFFF')
      .margin({ bottom: 15 })

      Button('Add Data')
        .onClick(() => {
          this.panelData = [...this.panelData, 'Data ' + (this.panelData.length + 1)]
        })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct CircleDemo {
  @State circleRadius: number = 50
  @State circleColor: string = '#FF6B6B'

  build() {
    Column() {
      Text('Circle Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })

      Circle({ width: this.circleRadius * 2, height: this.circleRadius * 2 })
        .fill(this.circleColor)
        .margin({ bottom: 15 })

      Text('Radius: ' + this.circleRadius)
        .fontSize(14)
        .margin({ bottom: 10 })

      Row() {
        Button('Radius +')
          .onClick(() => {
            this.circleRadius = Math.min(this.circleRadius + 10, 100)
          })

        Button('Radius -')
          .onClick(() => {
            this.circleRadius = Math.max(this.circleRadius - 10, 20)
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct EllipseDemo {
  @State ellipseWidth: number = 100
  @State ellipseHeight: number = 60
  @State ellipseColor: string = '#4ECDC4'

  build() {
    Column() {
      Text('Ellipse Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })

      Ellipse({ width: this.ellipseWidth, height: this.ellipseHeight })
        .fill(this.ellipseColor)
        .margin({ bottom: 15 })

      Text('Size: ' + this.ellipseWidth + ' x ' + this.ellipseHeight)
        .fontSize(14)
        .margin({ bottom: 10 })

      Row() {
        Button('Width +')
          .onClick(() => {
            this.ellipseWidth = Math.min(this.ellipseWidth + 10, 200)
          })

        Button('Width -')
          .onClick(() => {
            this.ellipseWidth = Math.max(this.ellipseWidth - 10, 50)
          })

        Button('Height +')
          .onClick(() => {
            this.ellipseHeight = Math.min(this.ellipseHeight + 10, 150)
          })

        Button('Height -')
          .onClick(() => {
            this.ellipseHeight = Math.max(this.ellipseHeight - 10, 30)
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}