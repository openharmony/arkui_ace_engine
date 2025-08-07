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

/*用例描述
 1、本用例通过FrameNode的getAttribute方法获取了Scroll节点的属性，从而修改Scroll节点的相关属性值，
 并通过FrameNode的bindController方法将滚动控制器Scroller绑定到Scroll节点上，用以控制Scroll节点的滚动。
*/
import { FrameNode, NodeController, typeNode, UIContext } from '@kit.ArkUI';

class MyNodeController extends NodeController {
  makeNode(uiContext: UIContext): FrameNode | null {
    const rootNode = typeNode.createNode(uiContext, 'Scroll');
    rootNode.attribute.id('typeNode')
      .width(200)
      .height(100)
      .backgroundColor(Color.Red)
      .scrollBarWidth(4);

    let column = typeNode.createNode(uiContext, 'Column');
    column.attribute.width(100).height(500).backgroundColor(Color.Yellow);
    rootNode.appendChild(column);

    rootNode.setCrossLanguageOptions({
      attributeSetting: true
    });
    return rootNode;
  }
}

@Entry
@Component
struct ScrollNode {
  private myNodeController: MyNodeController = new MyNodeController();
  controller: Scroller = new Scroller();

  build() {
    Column() {
      NodeContainer(this.myNodeController)

      Button('clickTypeNode').onClick(() => {
        const node = this.getUIContext().getFrameNodeById('typeNode');
        if (node) {
          console.info('typeNode is exist');
          const attribute = typeNode.getAttribute(node, 'Scroll');
          if (attribute) {
            console.info('get attribute success');
            attribute.scrollBarWidth(30);
            attribute.backgroundColor(Color.Blue);
          }

          try {
            typeNode.bindController(node, this.controller, 'Scroll');
            this.controller.fling(-1000);
          } catch (e) {
            console.error('typeNode error code:' + e.code + ', message:' + e.message);
          }
        } else {
          console.error('typeNode is null');
        }
      }).margin({ top: 10 })
    }
    .width('100%')
    .height('100%')
  }
}