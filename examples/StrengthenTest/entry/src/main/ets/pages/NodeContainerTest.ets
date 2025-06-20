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
  ClickEvent,
  UserView,
  NodeContainer,
  ClickEvent,
  $r,
  TouchEvent,
  Margin,
  Scroll,
  ScrollAttribute,
  BorderStyle,
  NavDestination, NavPathStack, NavDestinationContext, Callback
} from '@ohos.arkui.component' // TextAttribute should be insert by ui-plugins

import hilog from '@ohos.hilog'
import {
  NodeController,
  FrameNode,
  RenderNode,
  DrawContext,
  Frame,
  ShapeMask,
  Rect,
  ShapeClip,
  Size
} from '@ohos.arkui.node'
import { UIContext } from '@ohos.arkui.UIContext'

class MyRenderNode extends RenderNode {
  draw(context: DrawContext) {
    hilog.info(0x0000, 'testTag', 'FZY MyRenderNode draw');
  }
}

class MyNodeController extends NodeController {
  private rootNode: FrameNode | null = null;

  makeNode(uiContext: UIContext): FrameNode | null {
    hilog.info(0x0000, 'testTag', 'FZY makeNode');
    this.rootNode = new FrameNode(uiContext);
    return this.rootNode;
  }

  aboutToAppear(): void {
    hilog.info(0x0000, 'testTag', 'FZY aboutToAppear');
  }

  aboutToDisappear(): void {
    hilog.info(0x0000, 'testTag', 'FZY aboutToDisappear');
  }

  onAttach(): void {
    hilog.info(0x0000, 'testTag', 'FZY onAttach');
  }

  onDetach(): void {
    hilog.info(0x0000, 'testTag', 'FZY onDetach');
  }

  onWillBind(containerId: number): void {
    hilog.info(0x0000, 'testTag', 'FZY onWillBind ' + JSON.stringify(containerId));
  }

  onWillUnbind(containerId: number): void {
    hilog.info(0x0000, 'testTag', 'FZY onWillUnbind ' + JSON.stringify(containerId));
  }

  onBind(containerId: number): void {
    hilog.info(0x0000, 'testTag', 'FZY onBind ' + JSON.stringify(containerId));
  }

  onUnbind(containerId: number): void {
    hilog.info(0x0000, 'testTag', 'FZY onUnbind ' + JSON.stringify(containerId));
  }

  onTouchEvent(event: TouchEvent) {
    hilog.info(0x0000, 'testTag', 'FZY onTouchEvent');
  }

  aboutToResize(size: Size) {
    hilog.info(0x0000, 'testTag', 'FZY aboutToResize ');
  }
}

@Entry
@Component
export struct NodeContainerTest {
  private controllerArray: Array<MyNodeController> = new Array<MyNodeController>()
  @State idx: number = 0
  @State flag: boolean = true

  aboutToAppear() {
    this.controllerArray.push(new MyNodeController())
    this.controllerArray.push(new MyNodeController())
  }

  build() {
    NavDestination() {
      Scroll() {
        Column() {
          Text($r('app.string.hello_world')).fontSize(24).fontColor('#ff0000').width($r('app.float.width')).backgroundColor('#0000ff')
          if (this.flag) {
            NodeContainer(this.controllerArray[this.idx])
              .width(100)
              .height(100)
              .backgroundColor('#ffff00')
          }

          Button('UpdateNodeController')
            .onClick((event: ClickEvent) => {
              hilog.info(0x0000, 'testTag', 'FZY UpdateNodeController onClick ');
              this.idx = (this.idx + 1) % this.controllerArray.length
            })
            .width('100%')
            .margin({ bottom: 8 } as Margin)
          Button('UpdateFlag')
            .onClick((event: ClickEvent) => {
              hilog.info(0x0000, 'testTag', 'FZY UpdateFlag onClick ');
              this.flag = !this.flag
            })
            .width('100%')
            .margin({ bottom: 8 } as Margin)
          Button('rebuild')
            .onClick((event: ClickEvent) => {
              this.controllerArray[this.idx].rebuild()
            })
        }
        .width('100%')
      }
      .padding(16)
      .width('100%')
      .height('100%')
    }
    .title('NodeContainerTest')
  }
}
