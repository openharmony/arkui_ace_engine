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
import { MyComponent } from './MyComponenet'

@Builder
export function PopupBlurBuilder(name: string, param: Object) {
  PopupBlurExample()
}

@Extend(Column) function columnStyle() {
  .backgroundColor(Color.Pink)
  .width('100%')
  .padding(5)
  .borderWidth(1.0)
}

@Extend(Text) function paramTextStyle() {
  .fontSize(9)
  .width('100%')
}

@Extend(Text) function componentTextStyle() {
  .backgroundColor(Color.Orange)
  .fontSize(15)
  .margin(3)
  .padding(3)
  .borderWidth(1.0)
}

class BuilderOptions {
  public width?: number | string = 200
  public height?: number | string = 80
  public backgroundColor?: ResourceColor = Color.Grey
  public borderRadius?: number = 20
}

@Builder
function customPopupBuilder() {
  Row({ space: 2 }) {
    Column()
      .width(48)
      .height(48)
      .backgroundColor(Color.Green)
    Text('Custom Popup')
      .fontSize(10)
  }
  .padding(10)
  .margin(10)
  .borderWidth(1.0)
}

@Entry
@Component
struct PopupBlurExample {
  pathStack: NavPathStack = new NavPathStack()
  scroller: Scroller = new Scroller()
  @State index: number[] = [0, 0, 0]
  @State handlePopup: boolean = false
  @State handlePopup_1: boolean = false
  @State handlePopup_2: boolean = false
  @State customPopup_00: boolean = false
  @State customPopup_01: boolean = false
  @State customPopup_10: boolean = false
  @State customPopup_11: boolean = false
  @State showInSubwindow: boolean = false
  private popupOptionStyleList: PopupOptions[] = [
    //1
    {
      message: 'Popup message '.repeat(3),
      width: undefined,
      radius: undefined,
      shadow: undefined,
      popupColor: undefined,
      backgroundBlurStyle: undefined,
      mask: undefined,
      autoCancel: undefined
    },
    //2
    {
      message: 'Popup message '.repeat(3),
      width: -100,
      radius: -20,
      shadow: ShadowStyle.OUTER_DEFAULT_XS,
      popupColor: Color.Yellow,
      backgroundBlurStyle: BlurStyle.Thin,
      mask: true,
      autoCancel: undefined
    },
    //3
    {
      message: 'Popup message '.repeat(3),
      width: '0vp',
      radius: undefined,
      shadow: ShadowStyle.OUTER_DEFAULT_SM,
      popupColor: 0xfffff00,
      backgroundBlurStyle: BlurStyle.Regular,
      mask: false,
      autoCancel: undefined
    },
    //4
    {
      message: 'Popup message '.repeat(3),
      width: '300px',
      radius: 0,
      shadow: ShadowStyle.OUTER_DEFAULT_MD,
      popupColor: '#ffff8000',
      backgroundBlurStyle: BlurStyle.Thick,
      mask: { color: Color.Orange},
      autoCancel: true
    },
    //5
    {
      message: 'Popup message '.repeat(3),
      width: '240vp',
      radius: '35px',
      shadow: ShadowStyle.OUTER_DEFAULT_LG,
      popupColor: undefined,
      backgroundBlurStyle: BlurStyle.BACKGROUND_THIN,
      mask: { color: 0xffa500},
      autoCancel: false
    },
    //6
    {
      message: 'Popup message '.repeat(3),
      width: '1920fp',
      radius: '30fp',
      shadow: ShadowStyle.OUTER_FLOATING_SM,
      popupColor: 'color-red',
      backgroundBlurStyle: BlurStyle.BACKGROUND_REGULAR,
      mask: { color: '#ffffa500'},
      autoCancel: undefined
    },
    //7
    {
      message: 'Popup message '.repeat(3),
      width: '50%',
      radius: '120lpx',
      shadow: ShadowStyle.OUTER_FLOATING_MD,
      popupColor: undefined,
      backgroundBlurStyle: BlurStyle.BACKGROUND_THICK,
      mask: { color: '#color-orage'},
      autoCancel: undefined
    },
    //8
    {
      message: 'Popup message '.repeat(3),
      width: undefined,
      radius: '50%',
      shadow: {
        radius: 10
      },
      popupColor: '#354B47',
      backgroundBlurStyle: BlurStyle.COMPONENT_ULTRA_THICK,
      mask: undefined,
      autoCancel: undefined
    },
    //9
    {
      message: 'Popup message '.repeat(3),
      width: undefined,
      radius: undefined,
      shadow: {
        radius: 10,
        type: undefined,
        color: undefined,
        offsetX: undefined,
        offsetY: undefined,
        fill: undefined
      },
      popupColor: '#354B47',
      backgroundBlurStyle: BlurStyle.NONE,
      mask: undefined,
      autoCancel: undefined
    },
    //10
    {
      message: 'Popup message '.repeat(3),
      width: undefined,
      radius: undefined,
      shadow: { radius: 10 },
      popupColor: '#354B47',
      backgroundBlurStyle: BlurStyle.COMPONENT_THIN,
      mask: undefined,
      autoCancel: undefined
    },
    //11
    {
      message: 'Popup message '.repeat(3),
      width: undefined,
      radius: undefined,
      shadow: {
        radius: 0,
      },
      popupColor: '#354B47',
      backgroundBlurStyle: BlurStyle.COMPONENT_THICK,
      mask: undefined,
      autoCancel: undefined
    },
    //12
    {
      message: 'Popup message '.repeat(3),
      width: undefined,
      radius: undefined,
      shadow: {
        radius: 30,
        type: 7,
        color: Color.Orange,
        offsetX: -20,
        offsetY: -20,
        fill: true
      },
      popupColor: '#354B47',
      backgroundBlurStyle: BlurStyle.COMPONENT_THICK,
      mask: undefined,
      autoCancel: undefined
    },
    //13
    {
      message: 'Popup message '.repeat(3),
      width: undefined,
      radius: undefined,
      shadow: {
        radius: 30,
        color: Color.Orange,
        offsetX: -20,
        offsetY: -20,
      },
      popupColor: '#354B47',
      backgroundBlurStyle: BlurStyle.COMPONENT_THICK,
      mask: undefined,
      autoCancel: undefined
    },
    //14
    {
      message: 'Popup message '.repeat(3),
      width: undefined,
      radius: undefined,
      shadow: {
        radius: 10,
        type: ShadowType.BLUR,
        color: '#ED6F21',
        offsetX: -20,
        offsetY: -20,
      },
      popupColor: '#354B47',
      backgroundBlurStyle: BlurStyle.COMPONENT_THICK,
      mask: undefined,
      autoCancel: undefined
    },
    //15
    {
      message: 'Popup message '.repeat(3),
      width: undefined,
      radius: undefined,
      shadow: {
        radius: 10,
        type: ShadowType.COLOR,
        color: 'rgba(237, 111, 33, 1.0)',
        offsetX: 20,
        offsetY: 20,
        fill: true
      },
      popupColor: '#354B47',
      backgroundBlurStyle: 13,
      mask: undefined,
      autoCancel: undefined
    },
    //16
    {
      message: 'Popup message '.repeat(3),
      width: undefined,
      radius: undefined,
      shadow: {
        radius: 10,
        type: ShadowType.COLOR,
        color: 'rgba(237aa, 111aa, 33bb, 0.2cc)',
        offsetX: 100,
        offsetY: 100,
        fill: true
      },
      popupColor: '#354B47',
      backgroundBlurStyle: BlurStyle.COMPONENT_THICK,
      mask: undefined,
      autoCancel: undefined
    },
    //17
    {
      message: 'Popup message '.repeat(3),
      width: undefined,
      radius: undefined,
      shadow: {
        radius: 10,
        type: ShadowType.COLOR,
        color: 'rgba(237, 111, 33, 0.2)',
        offsetX: 100,
        offsetY: 100,
        fill: true
      },
      popupColor: '#354B47',
      backgroundBlurStyle: BlurStyle.COMPONENT_THICK,
      mask: undefined,
      autoCancel: undefined
    },
    //18
    {
      message: 'Popup message '.repeat(3),
      width: undefined,
      radius: undefined,
      shadow: {
        radius: 10,
        type: ShadowType.COLOR,
        color: Color.Orange,
        fill: true
      },
      popupColor: '#354B47',
      backgroundBlurStyle: BlurStyle.COMPONENT_THICK,
      mask: undefined,
      autoCancel: undefined
    },
    //19
    {
      message: 'Popup message '.repeat(3),
      width: undefined,
      radius: undefined,
      shadow: {
        radius: 30,
        type: 7,
        color: Color.Orange,
        offsetX: -20,
        offsetY: -20,
        fill: true
      },
      popupColor: 0xED6F21,
      backgroundBlurStyle: BlurStyle.COMPONENT_THICK,
      mask: undefined,
      autoCancel: undefined
    },
  ]

  private builderOptions: BuilderOptions[] = [
    {
      width: 200,
      height: 80,
      backgroundColor: '#F7CE00',
      borderRadius: 20
    },
    {
      width: 600,
      height: 80,
      backgroundColor: '#F7CE00',
      borderRadius: 40
    },
    {
      width: 160,
      height: 120,
      backgroundColor: '#F7CE00',
      borderRadius: 20
    },
    {
      width: '50%',
      height: 60,
      backgroundColor: '#F7CE00',
      borderRadius: 20
    },
    {
      width: 240,
      height: 80,
      backgroundColor: '#F7CE00',
      borderRadius: 40
    },
    {
      width: 240,
      height: 80,
      backgroundColor: '#F7CE00',
      borderRadius: 10
    },
  ]

  @Builder
  PopupBuilder($$: BuilderOptions) {
    Row({ space: 2 }) {
      Column()
        .width(48)
        .height(48)
        .backgroundColor(Color.Green)
      Text('CustomPopup')
    }
    .padding(10)
    .margin(10)
    .borderWidth(1.0)
    .width($$.width)
    .height($$.height)
    .backgroundColor($$.backgroundColor)
    .borderRadius($$.borderRadius)
  }

  // popup构造器定义弹框内容
  @Builder popupBuilder() {
    Row({ space: 2 }) {
      Image($r('app.media.app_icon'))
        .width(24)
        .height(24)
        .margin({ left: -5 })

      Text('Custom Popup')
        .fontSize(10)
    }
    .width(100)
    .height(50)
    .padding(5)
  }

  build() {
    NavDestination() {
      Scroll(this.scroller) {
        Column({ space: 5 }) {
          Text('验证PopupOption设置style属性')
            .paramTextStyle()
          Column({ space: 5 }) {
            Text(`切换subwindow参数: ${this.showInSubwindow}`)
              .paramTextStyle()
            Row({ space: 2 }) {
              MyComponent({
                title: 'subwindow: true',
                func: () => {
                  this.showInSubwindow = true
                }
              })
              MyComponent({
                title: 'subwindow: false',
                func: () => {
                  this.showInSubwindow = false
                }
              })
            }
          }
          .columnStyle()
          Column({ space: 5 }) {
            Text(`切换style参数`)
              .paramTextStyle()
            Row({ space: 2 }) {
              Text(`${this.index[2] + 1}` + '/')
                .fontSize(9)
              Text(`${this.popupOptionStyleList.length}`)
                .key('paramSets_key_2')
                .fontSize(9)
              MyComponent({
                title: 'Test2+',
                func: () => {
                  this.index[2]++
                  if (this.index[2] == this.popupOptionStyleList.length) {
                    this.index[2] = 0
                  }
                }
              })
              MyComponent({
                title: 'Test2-',
                func: () => {
                  this.index[2]--
                  if (this.index[2] <= -1) {
                    this.index[2] = this.popupOptionStyleList.length -1
                  }
                }
              })
              Text('popup style')
                .componentTextStyle()
                .onClick(() => {
                  this.handlePopup_2 = !this.handlePopup_2
                })
                .bindPopup(this.handlePopup_2, {
                  message: 'Popup message',
                  width: this.popupOptionStyleList[this.index[2]].width,
                  radius: this.popupOptionStyleList[this.index[2]].radius,
                  shadow: this.popupOptionStyleList[this.index[2]].shadow,
                  popupColor: this.popupOptionStyleList[this.index[2]].popupColor,
                  autoCancel: this.popupOptionStyleList[this.index[2]].autoCancel,
                  mask: this.popupOptionStyleList[this.index[2]].mask,
                  showInSubWindow: this.showInSubwindow,
                  onStateChange: (e) => {
                    console.log(JSON.stringify(e.isVisible))
                    if (!e.isVisible) {
                      this.handlePopup_2 = false
                    }
                  }
                })
            }
          }
          .columnStyle()

          Column({ space: 5 }) {
            Text(`切换builder属性参数`)
              .paramTextStyle()
            Row({ space: 2 }) {
              Text(`${this.index[0] + 1}` + '/')
                .fontSize(9)
              Text(`${this.builderOptions.length}`)
                .key('paramSets_key_0')
                .fontSize(9)
              MyComponent({
                title: 'Test0+',
                func: () => {
                  this.index[0]++
                  if (this.index[0] == this.builderOptions.length) {
                    this.index[0] = 0
                  }
                }
              })
              MyComponent({
                title: 'Test0-',
                func: () => {
                  this.index[0]--
                  if (this.index[0] <= -1) {
                    this.index[0] = this.builderOptions.length -1
                  }
                }
              })
            }
            Text('Popup未设置style属性')
              .paramTextStyle()
            Column({ space: 3 }) {
              Text('popup builder')
                .componentTextStyle()
                .onClick(() => {
                  this.customPopup_01 = !this.customPopup_01
                })
                .bindPopup(this.customPopup_01, {
                  builder: this.PopupBuilder({
                    width: this.builderOptions[this.index[0]].width,
                    height: this.builderOptions[this.index[0]].height,
                    backgroundColor: this.builderOptions[this.index[0]].backgroundColor,
                    borderRadius: this.builderOptions[this.index[0]].borderRadius
                  }),
                  showInSubWindow: this.showInSubwindow,
                  placement: Placement.Bottom,
                  onStateChange: (e) => {
                    console.log(JSON.stringify(e.isVisible))
                    if (!e.isVisible) {
                      this.customPopup_01 = false
                    }
                  }
                })
              Text('popup customBuilder')
                .componentTextStyle()
                .onClick(() => {
                  this.customPopup_00 = !this.customPopup_00
                })
                .bindPopup(this.customPopup_00, {
                  builder: customPopupBuilder(),
                  showInSubWindow: this.showInSubwindow,
                  placement: Placement.Bottom,
                  onStateChange: (e) => {
                    console.log(JSON.stringify(e.isVisible))
                    if (!e.isVisible) {
                      this.customPopup_00 = false
                    }
                  }
                })
            }

            Text('Popup设置style属性')
              .paramTextStyle()
            Column({ space: 3 }) {
              Text('popup builder11')
                .componentTextStyle()
                .onClick(() => {
                  this.customPopup_11 = !this.customPopup_11
                })
                .bindPopup(this.customPopup_11, {
                  builder: this.PopupBuilder({
                    width: this.builderOptions[this.index[0]].width,
                    height: this.builderOptions[this.index[0]].height,
                    backgroundColor: this.builderOptions[this.index[0]].backgroundColor,
                    borderRadius: this.builderOptions[this.index[0]].borderRadius
                  }),
                  width: 240,
                  radius: 20,
                  popupColor: Color.Orange,
                  backgroundBlurStyle: BlurStyle.NONE,
                  showInSubWindow: this.showInSubwindow,
                  placement: Placement.Bottom,
                  onStateChange: (e) => {
                    console.log(JSON.stringify(e.isVisible))
                    if (!e.isVisible) {
                      this.customPopup_11 = false
                    }
                  }
                })
              Text('popup customBuilder10')
                .componentTextStyle()
                .onClick(() => {
                  this.customPopup_10 = !this.customPopup_10
                })
                .bindPopup(this.customPopup_10, {
                  builder: customPopupBuilder(),
                  width: 240,
                  radius: 20,
                  popupColor: Color.Orange,
                  backgroundBlurStyle: BlurStyle.NONE,
                  showInSubWindow: this.showInSubwindow,
                  placement: Placement.Bottom,
                  onStateChange: (e) => {
                    console.log(JSON.stringify(e.isVisible))
                    if (!e.isVisible) {
                      this.customPopup_10 = false
                    }
                  }
                })
            }
          }
          .columnStyle()
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