/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/*
import { FrameNode, NodeController, typeNode, UIContext } from '@kit.ArkUI';

class MyImageNodeController extends NodeController {
  public uiContext: UIContext | null = null;
  public rootNode: FrameNode | null = null;

  makeNode(uiContext: UIContext): FrameNode | null {
    this.uiContext = uiContext;
    this.rootNode = new FrameNode(uiContext);
    let node = typeNode.createNode(uiContext, 'Image');
    node.initialize($r('app.media.200both6'))
      .width(100)
      .height(100)
      .syncLoad(true)
    this!.rootNode!.appendChild(node);
    return this.rootNode;
  }
}

@Entry
@Component
struct Index {
  @State message: string = 'Hello World';
  @State list: number[] = []

  aboutToAppear(): void {
    this.list = new Array(50).fill(0)
  }

  build() {
    Column() {
      Scroll() {
        Row() {
          ContentSlot(new MyImageNodeController().rootNode)
          NodeContainer(new MyImageNodeController()).margin(5)
          ForEach(this.list, (item: number, index: number) => {
            Image($rawfile('zhujian.png'))
              .width(45)
              .height(117)
            if (index !== this.list.length - 1) {
              Image($rawfile('zhujianxian.png'))
                .height(107)
                .width(6)
            }
          })
        }
        .alignItems(VerticalAlign.Center)
      }
      .scrollable(ScrollDirection.Horizontal)
      .alignSelf(ItemAlign.Stretch)
      .scrollBar(BarState.Off)
    }
    .justifyContent(FlexAlign.Center)
    .height('100%')
    .width('100%')
  }
}*/
import { FrameNode, NodeContent, NodeController, typeNode, UIContext } from '@kit.ArkUI';

class NodeContentCtrl {
  content: NodeContent
  textNode: Array<typeNode.Image> = new Array();
  uiContext: UIContext
  width: number

  constructor(uiContext: UIContext) {
    this.content = new NodeContent();
    this.uiContext = uiContext;
    this.width = Infinity;
  }

  AddNode() {
    let node = typeNode.createNode(this.uiContext, "Image");
    node.initialize($r('app.media.200both6'))
      .width(100)
      .height(100)
      .syncLoad(true)
      .borderWidth(1);
    this.textNode.push(node);
    this.content.addFrameNode(node);
  }

  RemoveNode() {
    let node = this.textNode.pop();
    this.content.removeFrameNode(node);
  }

  RemoveFront() {
    let node = this.textNode.shift();
    this.content.removeFrameNode(node);
  }

  GetContent(): NodeContent {
    return this.content;
  }
}

class MyNodeController extends NodeController {
  public rootNode: FrameNode | null = null;
  textNode: Array<typeNode.Image> = new Array();

  makeNode(uiContext: UIContext): FrameNode {
    this.rootNode = new FrameNode(uiContext);
    return this.rootNode;
  }

  AddNode(frameNode: FrameNode | null, uiContext: UIContext) {
    let node = typeNode.createNode(uiContext, "Image");
    node.initialize($r('app.media.200both6'))
      .width(100)
      .height(100)
      .syncLoad(true)
      .borderWidth(1);
    this.textNode.push(node);
    frameNode?.appendChild(node);
  }

  RemoveNode(frameNode: FrameNode | null) {
    let node = this.textNode.pop();
    frameNode?.removeChild(node);
  }

  RemoveFront(frameNode: FrameNode | null) {
    let node = this.textNode.shift();
    frameNode?.removeChild(node);
  }
}

@Entry
@Component
struct Index {
  @State message: string = 'Hello World';
  controller = new NodeContentCtrl(this.getUIContext());
  myNodeController = new MyNodeController();

  aboutToAppear(): void {
    this.myNodeController.AddNode(this.myNodeController.rootNode, this.getUIContext());
  }

  build() {
    Row() {
      Column() {
        Image()
          .interpolation(ImageInterpolation.Medium)
          .height(50).width(50)
        ContentSlot(this.controller.GetContent())
        Button('AddToSlot')
          .onClick(() => {
            this.controller.AddNode();
          })
          .margin(10)
        Button('RemoveBack')
          .onClick(() => {
            this.controller.RemoveNode();
          })
          .margin(10)
        Button('RemoveFront')
          .onClick(() => {
            this.controller.RemoveFront();
          })
          .margin(10)
      }
      .width('50%')

      Column() {
        NodeContainer(this.myNodeController)
        Button('AddToNodeContainer')
          .onClick(() => {
            this.myNodeController.AddNode(this.myNodeController.rootNode, this.getUIContext());
          })
          .margin(10)
        Button('RemoveBack')
          .onClick(() => {
            this.myNodeController.RemoveNode(this.myNodeController.rootNode);
          })
          .margin(10)
        Button('RemoveFront')
          .onClick(() => {
            this.myNodeController.RemoveFront(this.myNodeController.rootNode);
          })
          .margin(10)
      }
      .width('50%')
    }
    .height('100%')
  }
}
