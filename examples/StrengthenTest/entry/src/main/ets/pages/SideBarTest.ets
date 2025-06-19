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
  Entry,
  Text,
  TextAttribute,
  Column,
  Component,
  Button,
  ButtonAttribute,
  Scroll,
  ClickEvent,
  UserView,
  animateTo,
  Curve,
  LaunchMode,
  SideBarContainer,
  SideBarContainerType,
  Resource,
  ButtonIconOptions,
  $r,
  SideBarPosition,
  NavDestination,
  NavPathStack,
  NavDestinationContext,
  Callback
} from '@ohos.arkui.component'  // TextAttribute should be insert by ui-plugins

import hilog from '@ohos.hilog'
import { UIContext } from '@ohos.arkui.UIContext'
import { DividerStyle } from 'arkui.component.sidebar'

@Entry
@Component
export struct SideBarTest {
  @State stateVar: string = 'state var';
  message: string = 'var';
  changeValue() {
    this.stateVar+='~'
  }

  @State hideTitleBar: boolean = false;
  @State hideNavBar: boolean = false;
  @State showControlButton: boolean = true;
  @State autoHide: boolean = true
  @State sideBarWidth: Double|undefined = 150.0
  @State type:SideBarContainerType = SideBarContainerType.Embed
  @State posi:SideBarPosition = SideBarPosition.Start
  @State showSideBar:boolean = false
  @State minContentWidth:Double|undefined = 0
  @State divider:DividerStyle = { strokeWidth: '3vp', startMargin: '16vp', endMargin: '28vp', color: '#18908900' } as DividerStyle

  build() {
    NavDestination() {
      SideBarContainer(this.type) {
        Column() {
          Text('Index0')
            .fontSize(25)
        }.width('100%')
        // .justifyContent(FlexAlign.SpaceEvenly)
        .backgroundColor('#19000000')

        Column() {
          Button('showSideBar=false').onClick((e: ClickEvent) => {
            this.showSideBar = false
          })
          Button('showSideBar=true').onClick((e: ClickEvent) => {
            this.showSideBar = true
          })
          Button('showControlButton=false').onClick((e: ClickEvent) => {
            this.showControlButton = false
          })
          Button('showControlButton=true').onClick((e: ClickEvent) => {
            this.showControlButton = true
          })
          Button('autoHide=false').onClick((e: ClickEvent) => {
            this.autoHide = false
          })
          Button('autoHide=true').onClick((e: ClickEvent) => {
            this.autoHide = true
          })
          Button('sideBarWidth length 280').onClick((e: ClickEvent) => {
            this.sideBarWidth = 280
          })
          Button('SideBarContainerType.Overlay').onClick((e: ClickEvent) => {
            this.type = SideBarContainerType.Overlay
          })
          Button('SideBarContainerType.AUTO').onClick((e: ClickEvent) => {
            this.type = SideBarContainerType.AUTO
          })

          Button('sideBarPosition.start').onClick((e: ClickEvent) => {
            this.posi = SideBarPosition.Start
          })
          Button('sideBarPosition.end').onClick((e: ClickEvent) => {
            this.posi = SideBarPosition.End
          })
          Button('minContentWidth 90').onClick((e: ClickEvent) => {
            this.minContentWidth = 90
            // .minContentWidth(100).minSideBarWidth(330)
          })
          Button('minContentWidth 550').onClick((e: ClickEvent) => {
            this.minContentWidth = 550
          })

        }.height(600)

      }
      .controlButton({
        icons: {
          hidden: $r('app.media.background'),
          shown: $r('app.media.foreground'),
          switching: $r('app.media.startIcon'),
        } as ButtonIconOptions,
        left: 100,
        top: 50,
        width: 50,
        height: 50
      })
      .showSideBar(this.showSideBar)
      .showControlButton(this.showControlButton)
      .autoHide(this.autoHide)
      .sideBarPosition(this.posi)
      .minSideBarWidth(150)
      .maxSideBarWidth(300)
      .minContentWidth(this.minContentWidth)
      .onChange((value: boolean) => {
        hilog.info(0x0000, '===status', JSON.stringify(value));
      })
      .divider({
        strokeWidth: '3vp',
        startMargin: '16vp',
        endMargin: '28vp',
        color: '#18908900'
      } as DividerStyle)
    }
    .title('导航类组件测试002')
  }
}

@Component
struct Child {
  @State stateVar: string = 'Child';
  build() {
    Text(this.stateVar).fontSize(50)
  }
}
