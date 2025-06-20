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
  ButtonAttribute,
  ClickEvent,
  UserView,
  animateTo,
  Curve,
  $r,
  Entry,
  NodeContainer,
  NavDestination,
  NavPathStack,
  NavDestinationContext,
  Callback
} from '@ohos.arkui.component' // TextAttribute should be insert by ui-plugins

import hilog from '@ohos.hilog'
import { UIContext } from '@ohos.arkui.UIContext'
import { NodeController, FrameNode } from '@ohos.arkui.node'

class MyNodeController extends NodeController {
  makeNode(uiContext: UIContext): FrameNode | null {
    let node = new FrameNode(uiContext);
    return node;
  }
  onWillBind(): void{
    console.log('kkk myButton aboutToAppear')
  }

  onWillUnbind(): void{
    console.log('kkk myButton onWillUnbind')
  }

  aboutToAppear(): void {
    console.log('kkk myButton aboutToAppear')
  }

  aboutToDisappear(): void {
    console.log('kkk myButton aboutToDisappear');
  }

  onBind(containerId: number): void {
    console.log('kkk myButton on bind: ' + containerId);
  }

  onUnbind(containerId: number): void {
    console.log('kkk myButton on unbind: ' + containerId);
  }

  onAttach(): void {
    console.log('kkk myButton on attach');
  }

  onDetach(): void {
    console.log('kkk myButton on detach');
  }
}

@Entry
@Component
export struct ResourceTest {
  @State isShow: boolean = true
  @State index_: number = 0
  private controller: MyNodeController = new MyNodeController()  // 运行正常
  private controllerNull: null = null;
  private controllerArray: Array<MyNodeController | null> = [this.controller, this.controllerNull]



  build() {
    NavDestination() {
      Column(undefined) {
        Text('Hello World').fontSize(60)
        Text($r('app.string.app_name'))
        Text('' + this.isShow)

        Button('切换上下树')
          .onClick((e: ClickEvent) => {
            this.isShow = !this.isShow
          })
        Button('上树')
          .onClick((e: ClickEvent) => {
            this.isShow = true
          })
        Button('下树')
          .onClick((e: ClickEvent) => {
            this.isShow = false
          })

        if (this.isShow) {
          NodeContainer(this.controller)
        }

      }
    }
    .title('$r使用资源测试')
  }
}