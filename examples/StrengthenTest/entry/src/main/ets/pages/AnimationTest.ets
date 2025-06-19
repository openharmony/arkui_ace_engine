import {
  memo,
  __memo_context_type,
  __memo_id_type,
  State,
  StateDecoratedVariable,
  MutableState,
  stateOf,
  observableProxy
} from '@ohos.arkui.stateManagement' // should be insert by ui-plugins

import {
  Text,
  TextAttribute,
  Column,
  Row,
  Component,
  Button,
  AnimateParam,
  FinishCallbackType,
  ButtonAttribute,
  PlayMode,
  Scroll,
  Entry,
  ClickEvent,
  UserView,
  animateTo,
  ICurve,
  ExpectedFrameRateRange,
  Curve,
  NavPathStack,
  Navigation,
  LaunchMode,
  NavPathInfo,
  NavDestination,
  NavigationMode,
  NavigationOptions,
  NavigationTitleMode,
  NavigationCommonTitle,
  NavigationMenuItem,
  NavDestinationMode,
  LayoutSafeAreaType,
  LayoutSafeAreaEdge,
  Callback,
  NavDestinationContext
} from '@ohos.arkui.component'  // TextAttribute should be insert by ui-plugins

import hilog from '@ohos.hilog'
import { UIContext } from '@ohos.arkui.UIContext'
import router from '@ohos.router'

@Entry
@Component
export struct AnimationTest {
  private TAG: string = 'testTag'
  @State fsize:number = 14
  @State flag: boolean = true;
  @State duration:number = 2000
  @State curve: Curve | string | ICurve = 'linear'
  @State tempo: number = 1
  @State delay: number = 500
  @State iterations: number = 1
  @State playMode: PlayMode = PlayMode.Normal
  @State finishCallbackType:FinishCallbackType = FinishCallbackType.REMOVED

  build() {
    NavDestination() {
      Column() {
        Row() {
          Button('delay-1').onClick((e: ClickEvent) => {
            this.delay = -1
          })
          Button('delay:2000.55').onClick((e: ClickEvent) => {
            this.delay = 2000.55
          })
          Button('delay:0').onClick((e: ClickEvent) => {
            this.delay = 0
          })
        }

        Row() {
          Button('duration 1000.98').onClick((e: ClickEvent) => {
            this.duration = 1000.98
          })
          Button('duration:0').onClick((e: ClickEvent) => {
            this.duration = 0
          })
          Button('duration:-1').onClick((e: ClickEvent) => {
            this.duration = -1
          })
        }

        Row() {
          Button('iterations-55').onClick((e: ClickEvent) => {
            this.iterations = -55
          })
          Button('iterations:0').onClick((e: ClickEvent) => {
            this.iterations = 0
          })
          Button('iterations:5.42').onClick((e: ClickEvent) => {
            this.iterations = 5.42
          })
        }

        Row() {
          Button('iterations-1').onClick((e: ClickEvent) => {
            this.iterations = -1
          })
          Button('tempo:0').onClick((e: ClickEvent) => {
            this.tempo = 0
          })
          Button('Reverse').onClick((e: ClickEvent) => {
            this.playMode = PlayMode.Reverse
          })
        }

        Row() {
          Button('Alternate').onClick((e: ClickEvent) => {
            this.playMode = PlayMode.Alternate
          })
        }

        Row() {
          Button('LOGICALLY').onClick((e: ClickEvent) => {
            this.finishCallbackType = FinishCallbackType.LOGICALLY
          })
          Button('Curve.EaseOut').onClick((e: ClickEvent) => {
            this.curve = Curve.EaseOut
          })
        }

        Button('change size')
          .onClick((e: ClickEvent) => {
            this.getUIContext()?.animateTo({
              duration: this.duration,
              curve: this.curve,
              iterations: this.iterations,
              tempo: this.tempo,
              delay: this.delay,
              playMode: this.playMode,
              finishCallbackType: this.finishCallbackType,
              onFinish: () => {
                hilog.info(0x0000, 'xhq', 'play end');
              }
            }, () => {
              this.fsize = 50;
            })
          })

        Text('test api')
          .onClick((e: ClickEvent) => {
            hilog.info(0x0000, '===click', '222');
            if (this.flag) {
              this.fsize = 50;
            } else {
              this.fsize = 14; // 改变this.space动画不生效
            }
            this.flag = !this.flag;
          })
          .fontSize(this.fsize)
          .animation({
            duration: this.duration,
            curve: this.curve,
            delay: this.delay,
            tempo: this.tempo,
            iterations: this.iterations,
            playMode: this.playMode,
            expectedFrameRateRange: { min: 10, max: 120, expected: 30, } as ExpectedFrameRateRange,
            onFinish: () => {
              hilog.info(0x0000, '===onFinish', '222');
            },
            finishCallbackType: this.finishCallbackType
          } as AnimateParam)
      }
    }
    .title('动效测试001'  )
  }
}

@Component
struct Child {
  @State stateVar: string = 'Child';
  build() {
    Text(this.stateVar).fontSize(50)
  }
}