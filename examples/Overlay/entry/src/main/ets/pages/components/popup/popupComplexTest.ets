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
import { DimensionUtil, MyInput, ShadowSelect, KeyboardAvoidModeSelect } from './DimensionUtil'

@Builder
export function PopupComplexBuilder(name: string, param: Object) {
  PopupExample09()
}

interface maskColor {
  color: ResourceColor
}

@Entry
@Component
struct PopupExample09 {
  pathStack: NavPathStack = new NavPathStack()
  @State aOffset: Dimension = 0
  @State showInSubwindow: boolean = false
  @State maskType: string = 'boolean'
  @State mMask: boolean | maskColor | undefined | null = false
  @State targetSpace: Dimension = 8
  @State placement: Placement | undefined = Placement.Bottom
  @State keyboardAvoidMode: KeyboardAvoidMode | undefined = KeyboardAvoidMode.DEFAULT
  @State offsetX: Dimension = 0
  @State offsetY: Dimension = 0
  @State enableArrow: boolean = true
  @State popupColor: Color | string | number | Resource | undefined | null = undefined
  @State autoCancel: boolean = false
  @State mWidth: Dimension = 200
  @State arrowPointPosition: ArrowPointPosition = ArrowPointPosition.CENTER
  @State arrowHeight: Dimension = 8
  @State arrowWidth: Dimension = 16
  @State mRadius: Dimension = 20

  @State blurStyle: BlurStyle = BlurStyle.COMPONENT_ULTRA_THIN
  @State mFocusable: boolean = false
  @State shadowType: string = 'ShadowStyle'
  @State shadowStyle: ShadowStyle = ShadowStyle.OUTER_DEFAULT_SM
  @State shadowOption: ShadowOptions | undefined | null = {
    radius: 50,
    type: ShadowType.COLOR,
    color: Color.Black,
    offsetX: 50,
    offsetY: 50,
    fill: true
  }

  @State show: boolean = false
  @State show1: boolean = false
  @State show2: boolean = false
  @State show3: boolean = false
  @State show4: boolean = false

  @Styles Card () {
    .width('80%')
    .padding(10)
    .shadow({
      radius: 10,
      offsetX: 5,
      offsetY: 5
    })
  }

  @Builder myBuilder() {
    Column() {
      TextInput()
      Button('change height 500')
        .margin(10)
        .fontSize(20)
        .onClick(() => {
        })
    }
  }

  @Builder myBuilder1() {
    Column() {
      TextInput()
      Button('111')
        .margin(10)
        .fontSize(20)
      Button('222')
        .margin(10)
        .fontSize(20)
      Button('333')
        .margin(10)
        .fontSize(20)
      Button('444')
        .margin(10)
        .fontSize(20)
      Button('555')
        .margin(10)
        .fontSize(20)
      Button('666')
        .margin(10)
        .fontSize(20)
      Button('777')
        .margin(10)
        .fontSize(20)
      Button('888')
        .margin(10)
        .fontSize(20)
      Button('999')
        .margin(10)
        .fontSize(20)
      Button('111')
        .margin(10)
        .fontSize(20)
      Button('222')
        .margin(10)
        .fontSize(20)
      Button('333')
        .margin(10)
        .fontSize(20)
    }
  }

  build() {
    NavDestination() {
      Column() {
        Scroll() {
          Column() {
            TextInput()
            // ------------------------ keyboardAvoidMode ----------------------------
            Column() {
              KeyboardAvoidModeSelect({ keyboardAvoidMode: this.keyboardAvoidMode })
            }
            .Card()
            .alignItems(HorizontalAlign.Start)
            // ------------------------ arrowOffset ----------------------------
            Column() {
              Text('arrowOffset : ' + JSON.stringify(this.aOffset))
              DimensionUtil({ length: this.aOffset, lengthType: 'vp', lengthTypeLengthVal: 0 })
            }
            .Card()
            .alignItems(HorizontalAlign.Start)
            // ------------------------ placement ----------------------------
            Column() {
              Row() {
                Text('placement : ' + JSON.stringify(this.placement))
                Select([
                  { value: 'undefined' },
                  { value: 'Right' },
                  { value: 'Left' },
                  { value: 'Top' },
                  { value: 'Bottom' },
                  { value: 'RightTop' },
                  { value: 'RightBottom' },
                  { value: 'LeftTop' },
                  { value: 'LeftBottom' },
                  { value: 'TopLeft' },
                  { value: 'TopRight' },
                  { value: 'BottomLeft' },
                  { value: 'BottomRight' },

                ]).value(JSON.stringify(this.placement))
                  .onSelect((idx, value: String) => {
                    switch (value) {
                      case 'undefined':
                        this.placement = undefined
                        break
                      case 'Right':
                        this.placement = Placement.Right
                        break
                      case 'Left':
                        this.placement = Placement.Left
                        break
                      case 'Top':
                        this.placement = Placement.Top
                        break
                      case 'Bottom':
                        this.placement = Placement.Bottom
                        break
                      case 'RightTop':
                        this.placement = Placement.RightTop
                        break
                      case 'RightBottom':
                        this.placement = Placement.RightBottom
                        break
                      case 'LeftTop':
                        this.placement = Placement.LeftTop
                        break
                      case 'LeftBottom':
                        this.placement = Placement.LeftBottom
                        break
                      case 'TopLeft':
                        this.placement = Placement.TopLeft
                        break
                      case 'TopRight':
                        this.placement = Placement.TopRight
                        break
                      case 'BottomLeft':
                        this.placement = Placement.BottomLeft
                        break
                      case 'BottomRight':
                        this.placement = Placement.BottomRight
                        break
                    }
                  })
              }
            }
            .Card()
            .alignItems(HorizontalAlign.Start)
            // ------------------------ showInSubwindow ----------------------------
            Column() {
              Text('showInSubwindow : ' + JSON.stringify(this.showInSubwindow))
              Toggle({ type: ToggleType.Switch, isOn: this.showInSubwindow })
                .onChange((isOn: boolean) => {
                  this.showInSubwindow = isOn
                })
            }
            .Card()
            .alignItems(HorizontalAlign.Start)
            // ------------------------ mask ----------------------------
            Column() {
              Text('mask : ' + JSON.stringify(this.mMask))
              Row() {
                Text('蒙层类型 : ' + this.maskType)
                Select([
                  { value: 'boolean' },
                  { value: 'ResourceColor' }
                ])
                  .value(this.maskType)
                  .onSelect((index: number, val: string) => {
                    this.maskType = val
                  })
              }
              Row() {
                Text('蒙层')
                if (this.maskType == 'boolean') {
                  Select([
                    { value: 'true' },
                    { value: 'false' }
                  ])
                    .value(JSON.stringify(this.mMask))
                    .onSelect((index: number, val: string) => {
                      this.mMask = val == 'true' ? true : false
                    })
                } else {
                  Select([
                    { value: 'Color.Red' },
                    { value: 'rgb(255, 100, 255)' },
                    { value: '#ff000000' },
                    { value: '0x999999' },
                    { value: 'rgb(255, 100, 255, 0.5)' },
                    { value: 'undefined' },
                    { value: 'null' },
                  ])
                    .value(JSON.stringify(this.mMask))
                    .onSelect((index: number, val: string) => {
                      switch (val) {
                        case 'Color.Red':
                          this.mMask = { color: Color.Red }
                          break
                        case 'rgb(255, 100, 255)':
                          this.mMask = { color: 'rgb(255, 100, 255)' }
                          break
                        case '#ff000000':
                          this.mMask = { color: '#ff000000' }
                          break
                        case '0x999999':
                          this.mMask = { color: 0x999999 }
                          break
                        case 'rgb(255, 100, 255, 0.5)':
                          this.mMask = { color: 'rgb(255, 100, 255, 0.5)' }
                          break
                        case 'undefined':
                          this.mMask = undefined
                          break
                        case 'null':
                          this.mMask = null
                          break
                      }
                    })
                }
              }
            }
            .Card()
            .alignItems(HorizontalAlign.Start)
            // ------------------------ targetSpace ----------------------------
            Column() {
              Text('targetSpace : ' + JSON.stringify(this.targetSpace))
              DimensionUtil({ length: this.targetSpace, lengthType: 'vp', lengthTypeLengthVal: 8 })
                .id('targetSpace')
            }
            .Card()
            .alignItems(HorizontalAlign.Start)
            // ------------------------ offset ----------------------------
            Column() {
              Text(`offset : { x : ${this.offsetX}, y : ${this.offsetY}`)
              Row() {
                Text('x : ' + JSON.stringify(this.offsetX))
                DimensionUtil({ length: this.offsetX, lengthType: 'vp', lengthTypeLengthVal: 0 })
              }
              Row() {
                Text('y : ' + JSON.stringify(this.offsetY))
                DimensionUtil({ length: this.offsetY, lengthType: 'vp', lengthTypeLengthVal: 0 })
              }
            }
            .Card()
            .alignItems(HorizontalAlign.Start)
            // ------------------------ popupColor ----------------------------
            Column() {
              Text('popupColor : ' + JSON.stringify(this.popupColor))
              Select([
                { value: 'Color.Red' },
                { value: 'rgb(255, 100, 255)' },
                { value: '#ff000000' },
                { value: '0x999999' },
                { value: 'rgb(255, 100, 255, 0.5)' },
                { value: 'undefined' },
                { value: 'null' },
              ])
                .value(JSON.stringify(this.popupColor))
                .onSelect((index: number, val: string) => {
                  switch (val) {
                    case 'Color.Red':
                      this.popupColor = Color.Red
                      break
                    case 'rgb(255, 100, 255)':
                      this.popupColor = 'rgb(255, 100, 255)'
                      break
                    case '#ff000000':
                      this.popupColor = '#ff000000'
                      break
                    case '0x999999':
                      this.popupColor = 0x999999
                      break
                    case 'rgb(255, 100, 255, 0.5)':
                      this.popupColor = 'rgb(255, 100, 255, 0.5)'
                      break
                    case 'undefined':
                      this.popupColor = undefined
                      break
                    case 'null':
                      this.popupColor = null
                      break
                  }
                })
            }
            .Card()
            .alignItems(HorizontalAlign.Start)
            // ------------------------ autoCancel ----------------------------
            Column() {
              Row() {
                Text('autoCancel : ' + JSON.stringify(this.autoCancel))
                Toggle({ type: ToggleType.Switch, isOn: this.autoCancel })
                  .onChange((isOn: boolean) => {
                    this.autoCancel = isOn
                  })
              }
            }
            .Card()
            .alignItems(HorizontalAlign.Start)
            // ------------------------ focusable ----------------------------
            Column() {
              Row() {
                Text('focusable : ' + JSON.stringify(this.mFocusable))
                Toggle({ type: ToggleType.Switch, isOn: this.mFocusable })
                  .onChange((isOn: boolean) => {
                    this.mFocusable = isOn
                  })
              }
            }
            .Card()
            .alignItems(HorizontalAlign.Start)
            // ------------------------ width ----------------------------
            Column() {
              Row() {
                Text('width : ' + JSON.stringify(this.mWidth))
                DimensionUtil({ length: this.mWidth, lengthType: 'vp', lengthTypeLengthVal: 200, max: 600 })
              }
            }
            .Card()
            .alignItems(HorizontalAlign.Start)
            // ------------------------ 尖角位置 ----------------------------
            Column() {
              Row() {
                Text('arrowPointPosition : ' + JSON.stringify(this.arrowPointPosition))
                Select([
                  { value: 'START' },
                  { value: 'CENTER' },
                  { value: 'END' },
                ])
                  .value('CENTER')
                  .onSelect((index: number, val: string) => {
                    switch (val) {
                      case 'START':
                        this.arrowPointPosition = ArrowPointPosition.START
                        break
                      case 'CENTER':
                        this.arrowPointPosition = ArrowPointPosition.CENTER
                        break
                      case 'END':
                        this.arrowPointPosition = ArrowPointPosition.END
                        break
                    }
                  })
              }
            }
            .Card()
            .alignItems(HorizontalAlign.Start)
            // ------------------------ arrowWidth ----------------------------
            Column() {
              Row() {
                Text('arrowWidth : ' + JSON.stringify(this.arrowWidth))
                DimensionUtil({ length: this.arrowWidth, lengthType: 'vp', lengthTypeLengthVal: 16 })
              }
            }
            .Card()
            .alignItems(HorizontalAlign.Start)
            // ------------------------ arrowHeight ----------------------------
            Column() {
              Row() {
                Text('arrowHeight : ' + JSON.stringify(this.arrowHeight))
                DimensionUtil({ length: this.arrowHeight, lengthType: 'vp', lengthTypeLengthVal: 8 })
              }
            }
            .Card()
            .alignItems(HorizontalAlign.Start)
            // ------------------------ mRadius ----------------------------
            Column() {
              Row() {
                Text('mRadius : ' + JSON.stringify(this.mRadius))
                DimensionUtil({ length: this.mRadius, lengthType: 'vp', lengthTypeLengthVal: 20 })
              }
            }
            .Card()
            .alignItems(HorizontalAlign.Start)
            // ------------------------ 背景模糊 ----------------------------
            Column() {
              Row() {
                Text('blurStyle : ' + JSON.stringify(this.blurStyle))
                Select([
                  { value: 'NONE' },
                  { value: 'Thin' },
                  { value: 'Regular' },
                  { value: 'Thick' },
                  { value: 'BACKGROUND_THIN' },
                  { value: 'BACKGROUND_REGULAR' },
                  { value: 'BACKGROUND_THICK' },
                  { value: 'COMPONENT_ULTRA_THIN' },
                  { value: 'COMPONENT_THIN' },
                  { value: 'COMPONENT_REGULAR' },
                  { value: 'COMPONENT_THICK' },
                  { value: 'COMPONENT_ULTRA_THICK' },
                ])
                  .value('COMPONENT_ULTRA_THIN')
                  .onSelect((index: number, value: string) => {
                    switch (value) {
                      case 'NONE':
                        this.blurStyle = BlurStyle.NONE
                        break
                      case 'Thin':
                        this.blurStyle = BlurStyle.Thin
                        break
                      case 'Regular':
                        this.blurStyle = BlurStyle.Regular
                        break
                      case 'Thick':
                        this.blurStyle = BlurStyle.Thick
                        break
                      case 'BACKGROUND_THIN':
                        this.blurStyle = BlurStyle.BACKGROUND_THIN
                        break
                      case 'BACKGROUND_REGULAR':
                        this.blurStyle = BlurStyle.BACKGROUND_REGULAR
                        break
                      case 'BACKGROUND_THICK':
                        this.blurStyle = BlurStyle.BACKGROUND_THICK
                        break
                      case 'COMPONENT_ULTRA_THIN':
                        this.blurStyle = BlurStyle.COMPONENT_ULTRA_THIN
                        break
                      case 'COMPONENT_THIN':
                        this.blurStyle = BlurStyle.COMPONENT_THIN
                        break
                      case 'COMPONENT_REGULAR':
                        this.blurStyle = BlurStyle.COMPONENT_REGULAR
                        break
                      case 'COMPONENT_THICK':
                        this.blurStyle = BlurStyle.COMPONENT_THICK
                        break
                      case 'COMPONENT_ULTRA_THICK':
                        this.blurStyle = BlurStyle.COMPONENT_ULTRA_THICK
                        break
                    }
                  })
                  .id('select1')
              }
            }
            .Card()
            .alignItems(HorizontalAlign.Start)
            TextInput()
            // ------------------------ shadow ----------------------------
            ShadowSelect({
              shadowType: this.shadowType,
              shadowStyle: this.shadowStyle,
              shadowOption: this.shadowOption
            })
          }
        }
        .width('100%')
        .height('50%')
        Column({ space: 100 }) {
          Button('避让键盘，拉起弹窗')
            .onClick(() => {
              this.show = true
            })
            .bindPopup(this.show, {
              builder: this.myBuilder(),
              arrowOffset: this.aOffset,
              showInSubWindow: this.showInSubwindow,
              mask: this.mMask,
              targetSpace: this.targetSpace,
              placement: this.placement,
              offset: { x: this.offsetX, y: this.offsetY },
              enableArrow: this.enableArrow,
              popupColor: this.popupColor,
              autoCancel: this.autoCancel,
              arrowPointPosition: this.arrowPointPosition,
              keyboardAvoidMode: this.keyboardAvoidMode,
              width: this.mWidth,
              arrowWidth: this.arrowWidth,
              arrowHeight: this.arrowHeight,
              radius: this.mRadius,
              backgroundBlurStyle: this.blurStyle,
              focusable: this.mFocusable,
              shadow: this.shadowType == 'ShadowStyle' ? this.shadowStyle : this.shadowOption,
              onStateChange: (e) => {
                if (!e.isVisible) {
                  this.show = false
                }
              }
            })

          Button('不设置避让键盘，拉起弹窗')
            .onClick(() => {
              this.show1 = true
            })
            .bindPopup(this.show1, {
              builder: this.myBuilder(),
              arrowOffset: this.aOffset,
              showInSubWindow: this.showInSubwindow,
              mask: this.mMask,
              targetSpace: this.targetSpace,
              placement: this.placement,
              offset: { x: this.offsetX, y: this.offsetY },
              enableArrow: this.enableArrow,
              popupColor: this.popupColor,
              autoCancel: this.autoCancel,
              arrowPointPosition: this.arrowPointPosition,
              width: this.mWidth,
              arrowWidth: this.arrowWidth,
              arrowHeight: this.arrowHeight,
              radius: this.mRadius,
              backgroundBlurStyle: this.blurStyle,
              focusable: this.mFocusable,
              shadow: this.shadowType == 'ShadowStyle' ? this.shadowStyle : this.shadowOption,
              onStateChange: (e) => {
                if (!e.isVisible) {
                  this.show1 = false
                }
              }
            })
          Button('弹窗过大')
            .onClick(() => {
              this.show2 = true
            })
            .bindPopup(this.show2, {
              builder: this.myBuilder1(),
              arrowOffset: this.aOffset,
              showInSubWindow: this.showInSubwindow,
              mask: this.mMask,
              targetSpace: this.targetSpace,
              placement: this.placement,
              offset: { x: this.offsetX, y: this.offsetY },
              enableArrow: this.enableArrow,
              popupColor: this.popupColor,
              autoCancel: this.autoCancel,
              arrowPointPosition: this.arrowPointPosition,
              keyboardAvoidMode: this.keyboardAvoidMode,
              width: this.mWidth,
              arrowWidth: this.arrowWidth,
              arrowHeight: this.arrowHeight,
              radius: this.mRadius,
              backgroundBlurStyle: this.blurStyle,
              focusable: this.mFocusable,
              shadow: this.shadowType == 'ShadowStyle' ? this.shadowStyle : this.shadowOption,
              onStateChange: (e) => {
                if (!e.isVisible) {
                  this.show2 = false
                }
              }
            })
        }
      }
    }
    .title('Popup')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}