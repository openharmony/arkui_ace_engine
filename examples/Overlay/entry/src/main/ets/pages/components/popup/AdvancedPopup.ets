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


import {
  Popup,
  PopupOptions,
  PopupTextOptions,
  PopupButtonOptions,
  PopupIconOptions
} from '@ohos.arkui.advanced.Popup';
import { MyComponent } from './MyComponenet'

@Builder
export function AdvancePopupBuilder(name: string, param: Object) {
  AdvancedPopupExample()
}

@Extend(Text) function paramTextStyle() {
  .fontSize(9)
  .width('100%')
}
@Extend(Column) function columnStyle() {
  .borderWidth(1.0)
  .padding(5)
  .width('100%')
  .backgroundColor(Color.Pink)
}
@Extend(Text) function componentTextStyle() {
  .fontSize(15)
  .backgroundColor(Color.Orange)
  .margin(3).padding(3)
  .borderWidth(1.0)
}

@Entry
@Component
struct AdvancedPopupExample {
  pathStack: NavPathStack = new NavPathStack()
  @State index: number[] = [0, 0, 0]
  scroller: Scroller = new Scroller()

  //popup isShow
  @State popupIsShow: boolean[] = [false, false, false, false]
  //Popup的title和message测试点
  @State popupOptionsList: PopupOptions[] = [
  //1
    {
      title: {
        text: 'Popup title ',
        fontColor: Color.Red,
        fontWeight: -100
      } as PopupTextOptions,
      message: {
        text: 'Popup message ',
        fontColor: Color.Blue,
        fontWeight: -100
      } as PopupTextOptions,

      showClose: true,
      onClose: () => {
        this.popupIsShow[2] = false
        console.info('---LCG---  Popup showClose On')
      }
    },
    // 2预期无文本
    {
      title: {
        text: 'Popup title '.repeat(0)
      } as PopupTextOptions,
      message: {
        text: 'Popup message '.repeat(0)
      } as PopupTextOptions,

      showClose: false,
      onClose: () => {
        console.info('---LCG---  Popup showClose On')
      }
    },
    //3
    {
      title: {
        text: 'Popup title '.repeat(2),
        fontColor: 'rgb(255,0,0,1)',
        fontWeight: 0
      } as PopupTextOptions,
      message: {
        text: 'Popup message '.repeat(2),
        fontColor: 'rgb(0,0,255,1)',
        fontWeight: 0
      } as PopupTextOptions,

      showClose: undefined,
      onClose: () => {
        this.popupIsShow[2] = false
        console.info('---LCG---  Popup showClose On')
      }
    },
    //4
    {
      title: {
        text: 'Popup title '.repeat(10),
        fontColor: '#ffff0000',
        fontWeight: 100
      } as PopupTextOptions,
      message: {
        text: 'Popup message '.repeat(10),
        fontColor: '#ff0000ff',
        fontWeight: 100
      } as PopupTextOptions
    },
    //5
    {
      title: {
        text: 'Popup title \n'.repeat(3),
        fontColor: 0xFF0000,
        fontWeight: '300'
      } as PopupTextOptions,
      message: {
        text: 'Popup message \n'.repeat(3),
        fontColor: 0x0000FF,
        fontWeight: '300'
      } as PopupTextOptions
    },
    //6
    {
      title: {
        text: $r('app.string.EntryAbility_label'),
        fontColor: undefined,
        fontWeight: '600'
      } as PopupTextOptions,
      message: {
        text: $r('app.string.EntryAbility_label'),
        fontColor: undefined,
        fontWeight: '600'
      } as PopupTextOptions
    },
    //7
    {
      title: {
        text: $r('app.string.app_name')
      } as PopupTextOptions,
      message: {
        text: $r('app.string.app_name')
      } as PopupTextOptions
    },
    //8预期无文本
    {
      title: {
        text: ''
      } as PopupTextOptions,
      message: {
        text: ''
      } as PopupTextOptions
    },

    //9
    {
      title: {
        text: 'Popup title ',
        fontSize: -20,
        fontColor: 'rbg(123.1, 123.2, 123.4, 123)',
        fontWeight: 900
      } as PopupTextOptions,
      message: {
        text: 'Popup message ',
        fontSize: -20,
        fontColor: 'rbg(123.1, 123.2, 123.4, 123)',
        fontWeight: 900
      } as PopupTextOptions
    },
    //10
    {
      title: {
        text: 'Popup title ',
        fontSize: '0',
        fontWeight: 1200
      } as PopupTextOptions,
      message: {
        text: 'Popup message ',
        fontSize: '0',
        fontWeight: 1200
      } as PopupTextOptions
    },
    //11
    {
      title: {
        text: 'Popup title ',
        fontSize: 6,
        fontColor: $r('app.string.EntryAbility_label'),
        fontWeight: 450
      } as PopupTextOptions,
      message: {
        text: 'Popup message ',
        fontSize: 4,
        fontColor: $r('app.string.EntryAbility_label'),
        fontWeight: 450
      } as PopupTextOptions
    },
    //12
    {
      title: {
        text: 'Popup title ',
        fontSize: '16',
        fontWeight: undefined
      } as PopupTextOptions,
      message: {
        text: 'Popup message ',
        fontSize: '10',
        fontWeight: undefined
      } as PopupTextOptions
    },
    //13
    {
      title: {
        text: 'Popup title ',
        fontSize: 60,
        fontWeight: FontWeight.Lighter
      } as PopupTextOptions,
      message: {
        text: 'Popup message ',
        fontSize: 40,
        fontWeight: FontWeight.Lighter
      } as PopupTextOptions
    },
    //14
    {
      title: {
        text: 'Popup title ',
        fontSize: undefined,
        fontWeight: FontWeight.Normal
      } as PopupTextOptions,
      message: {
        text: 'Popup message ',
        fontSize: undefined,
        fontWeight: FontWeight.Normal
      } as PopupTextOptions
    },
    //15
    {
      title: {
        text: 'Popup title ',
        fontSize: '16aa',
        fontWeight: FontWeight.Regular
      } as PopupTextOptions,
      message: {
        text: 'Popup message ',
        fontSize: '10bb',
        fontWeight: FontWeight.Regular
      } as PopupTextOptions
    },
    //16
    {
      title: {
        text: 'Popup title ',
        fontSize: $r('app.string.EntryAbility_label'),
        fontWeight: FontWeight.Medium
      } as PopupTextOptions,
      message: {
        text: 'Popup message ',
        fontSize: $r('app.string.EntryAbility_label'),
        fontWeight: FontWeight.Medium
      } as PopupTextOptions
    },
    //17
    {
      title: {
        text: 'Popup title ',
        fontSize: undefined,
        fontColor: Color.Transparent
      } as PopupTextOptions,
      message: {
        text: 'Popup message ',
        fontSize: undefined,
        fontColor: Color.Transparent
      } as PopupTextOptions
    },
    //18
    {
      title: {
        text: 'Popup title ',
        fontWeight: FontWeight.Bold
      } as PopupTextOptions,
      message: {
        text: 'Popup message ',
        fontWeight: FontWeight.Bold
      } as PopupTextOptions
    },
    //19
    {
      title: {
        text: 'Popup title ',
        fontWeight: FontWeight.Bolder
      } as PopupTextOptions,
      message: {
        text: 'Popup message ',
        fontWeight: FontWeight.Bolder
      } as PopupTextOptions
    },
  ]

  //组件Popup的builder
  //必填入参属性
  @Builder
  PopupBuilder_RequiredOptions(){
    Popup({
      message: {
        text: 'Popup message'
      } as PopupTextOptions,
    })
  }
  //所有入参属性
  @Builder
  PopupBuilder_AllOptions(){
    Popup({
      icon: {
        image: $r('app.media.app_icon'),
      } as PopupIconOptions,

      title: {
        text: 'Popup title'
      } as PopupTextOptions,
      message: {
        text: 'Popup message'
      } as PopupTextOptions,

      showClose: true,
      onClose: () => {
        console.info('---LCG---  Popup onClose On')
      },

      buttons: [{ text: 'cancel' }, { text: 'confirm' }] as [PopupButtonOptions?, PopupButtonOptions?],
      direction: Direction.Auto
    })
  }
  //入参属性title和message
  @Builder
  PopupBuilder_Options_Msg_Title() {
    Popup({
      title: this.popupOptionsList[this.index[0]].title as PopupTextOptions,
      message: this.popupOptionsList[this.index[0]].message as PopupTextOptions,

      showClose: this.popupOptionsList[this.index[0]].showClose,
      onClose: this.popupOptionsList[this.index[0]].onClose,

      icon: {
        image: $r('app.media.app_icon'),
      } as PopupIconOptions,

      buttons: [{ text: 'cancel' }, { text: 'confirm' }] as [PopupButtonOptions?, PopupButtonOptions?],
      direction: Direction.Auto
    })
  }

  build() {
    NavDestination() {
      Scroll(this.scroller){
        Column({ space: 5 }) {
          Text('验证Popup组件的入参属性：title/message')
            .paramTextStyle()

          Column({space: 5}) {
            Text('入参非必填项设置验证:')
              .paramTextStyle()
            //Popup只设置必填入参
            this.PopupBuilder_RequiredOptions()

            Text(`Ad_Popup: RequiredOptions`)
              .componentTextStyle()
              .bindPopup(this.popupIsShow[0], {
                builder: this.PopupBuilder_RequiredOptions(),
                onStateChange: (e) => {
                  this.popupIsShow[0] = e.isVisible
                }
              })
              .onClick( () => {
                if (this.popupIsShow[0] == false){
                  this.popupIsShow[0] = true
                }
              })
            Divider()

            //Popup设置全部入参
            this.PopupBuilder_AllOptions()
            Text(`Ad_Popup: AllOptions`)
              .componentTextStyle()
              .bindPopup(this.popupIsShow[1], {
                builder: this.PopupBuilder_AllOptions(),
                onStateChange: (e) => {
                  this.popupIsShow[1] = e.isVisible
                }
              })
              .onClick( () => {
                if (this.popupIsShow[1] == false){
                  this.popupIsShow[1] = true
                }
              })
          }
          .columnStyle()

          Column({space: 5}){
            Text('切换测试参数:')
              .paramTextStyle()
            Row({ space: 2 }) {
              Text(`${this.index[0] + 1}` + ' / ')
                .fontSize(9)
              Text(`${this.popupOptionsList.length}`)
                .key('paramSets_key_0')
                .fontSize(9)
              MyComponent({
                title: 'Test0+', func: () => {
                  this.index[0]++
                  if (this.index[0] == this.popupOptionsList.length) {
                    this.index[0] = 0
                  }
                }
              })
              MyComponent({
                title: 'Test0-', func: () => {
                  this.index[0]--
                  if (this.index[0] <= -1) {
                    this.index[0] = this.popupOptionsList.length - 1
                  }
                }
              })
            }
            this.PopupBuilder_Options_Msg_Title()
            Text(`Ad_Popup: Opt-msg/title`)
              .componentTextStyle()
              .bindPopup(this.popupIsShow[2], {
                builder: this.PopupBuilder_Options_Msg_Title(),
                onStateChange: (e) => {
                  this.popupIsShow[2] = e.isVisible
                }
              })
              .onClick( () => {
                if (this.popupIsShow[2] == false){
                  this.popupIsShow[2] = true
                }
              })

          }
          .columnStyle()
        }
        .width('100%')
      }
      .padding(12)
      .scrollBar(BarState.Off)
      .align(Alignment.TopStart)
      .width('100%').height('100%')
    }
    .title('AdvancedPopup')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
  pageTransition() {
    //进入该界面没有跳转延迟
    PageTransitionEnter({ type: RouteType.None, duration: 0 })
  }
}