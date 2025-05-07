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
 RecycleView库文件
*/
/* 关键结构
 |-> Scroll
  |-> NodeContainer
*/
import { BuilderNode, FrameNode, LayoutConstraint, NodeController, ScrollModifier } from '@kit.ArkUI'

// 设置滚动内容数据源
export abstract class RecycleAdapter {
  public uiContext: UIContext
  public recyclePoolSize = 5
  public builder: WrappedBuilder<[Object]>
  public frameNode?: FrameNode;

  constructor(uiContext: UIContext, builder: WrappedBuilder<[Object]>) {
    this.uiContext = uiContext;
    this.builder = builder
  }

  public childrenMap: Map<number, BuilderNode<[Object]>> = new Map<number, BuilderNode<[Object]>>()
  public recyclePool: BuilderNode<[Object]>[] = []

  abstract getCount(): number;

  abstract getData(index: number): Object

  getChild(index: number): FrameNode | null {
    if (index >= this.getCount() || index < 0) {
      return null
    }
    let buildNode = this.childrenMap.get(index);
    if (buildNode) {
      return buildNode.getFrameNode();
    }
    buildNode = this.recyclePool.pop()
    if (buildNode) {
      buildNode.update(this.getData(index))
    } else {
      buildNode = new BuilderNode(this.uiContext);
      buildNode.build(this.builder, this.getData(index), { nestingBuilderSupported: true });
    }
    let frameNode = buildNode.getFrameNode();
    this.frameNode?.appendChild(frameNode);
    this.childrenMap.set(index, buildNode)
    return frameNode;
  }

  recycleChild(index: number): void {
    let node = this.childrenMap.get(index)
    if (node) {
      this.frameNode?.removeChild(node.getFrameNode());
      if (this.recyclePool.length < this.recyclePoolSize) {
        this.recyclePool.push(node);
      }
      this.childrenMap.delete(index);
    }
  }
}

// 设置scroll布局方法
export abstract class LayoutManager {
  abstract onWillScroll(recycleNode: RecycleNode, currOffset: OffsetResult, delta: OffsetResult,
    scrollState: ScrollState, scrollSource: ScrollSource): OffsetResult | void

  abstract onMeasure(recycleNode: RecycleNode, constraint: LayoutConstraint): void

  abstract onLayout(recycleNode: RecycleNode, position: Position): void
}

export class FixedHeightLayoutManager extends LayoutManager {
  private currentOffset: number = 0
  private currentDelta: number = 0
  private itemHeight = 200
  private startIndex = -1
  private endIndex = -1

  SetItemHeight(itemHeight: number) {
    this.itemHeight = itemHeight;
  }

  onWillScroll(recycleNode: RecycleNode, currOffset: OffsetResult, delta: OffsetResult,
    scrollState: ScrollState, scrollSource: ScrollSource): OffsetResult | void {
    this.currentOffset = vp2px(currOffset.yOffset);
    this.currentDelta = vp2px(delta.yOffset);
    recycleNode.setNeedsLayout()
  }

  // 计算各个元素的大小和位置
  onMeasure(recycleNode: RecycleNode, constraint: LayoutConstraint): void {
    constraint.maxSize.height = constraint.percentReference.height;
    let sizeRes: Size =
      { width: constraint.percentReference.width, height: this.itemHeight * recycleNode.adapter.getCount() };
    let offset = this.currentOffset + this.currentDelta;
    let startIndex = Math.floor(offset / this.itemHeight)
    let endIndex = Math.floor((offset + constraint.percentReference.height) / this.itemHeight)
    for (let i = startIndex; i <= endIndex; i++) {
      let child = recycleNode.adapter.getChild(i);
      if (child) {
        child.measure(constraint);
      }
    }
    // recycle
    if (this.startIndex >= 0 && this.startIndex < startIndex) {
      for (let i = this.startIndex; i < startIndex; i++) {
        recycleNode.adapter.recycleChild(i)
      }
    }
    if (this.endIndex >= 0 && this.endIndex > endIndex) {
      for (let i = endIndex; i < this.endIndex; i++) {
        recycleNode.adapter.recycleChild(i + 1)
      }
    }
    this.startIndex = startIndex;
    this.endIndex = endIndex;
    recycleNode.setMeasuredSize(sizeRes);
  }

  // 根据onMeasure中设置的大小进行布局
  onLayout(recycleNode: RecycleNode, position: Position): void {
    for (let i = this.startIndex; i <= this.endIndex; i++) {
      let child = recycleNode.adapter.getChild(i);
      if (child) {
        child.layout({
          x: 0,
          y: i * this.itemHeight
        });
      }
    }
  }
}

// 设置内容元素的布局方法
export class RecycleNode extends FrameNode {
  public layoutManager: LayoutManager
  public adapter: RecycleAdapter

  constructor(uiContext: UIContext, layoutManager: LayoutManager, adapter: RecycleAdapter) {
    super(uiContext)
    this.layoutManager = layoutManager;
    this.adapter = adapter
  }

  onMeasure(constraint: LayoutConstraint): void {
    this.layoutManager.onMeasure(this, constraint)
  }

  onLayout(position: Position): void {
    this.layoutManager.onLayout(this, position)
  }
}

export class RecycleViewController extends NodeController {
  public rootNode: RecycleNode | null = null;
  public layoutManager?: LayoutManager
  public adapter?: RecycleAdapter

  makeNode(uiContext: UIContext): FrameNode | null {
    if (this.layoutManager && this.adapter) {
      this.rootNode = new RecycleNode(uiContext, this.layoutManager, this.adapter);
      this.adapter.frameNode = this.rootNode
    }
    return this.rootNode;
  }
}

@Component
export struct RecycleView {
  modifier?: ScrollModifier
  scroller: Scroller = new Scroller()
  adapterController: RecycleViewController = new RecycleViewController();

  build() {
    Scroll(this.scroller) {
      NodeContainer(this.adapterController)
    }.attributeModifier(this.modifier)
    .onWillScroll((xOffset: number, yOffset: number, scrollState: ScrollState, scrollSource: ScrollSource) => {
      if (this.adapterController.rootNode) {
        this.adapterController.rootNode.layoutManager.onWillScroll(this.adapterController.rootNode,
          this.scroller.currentOffset(), { xOffset: xOffset, yOffset: yOffset }, scrollState, scrollSource)
      }
    })
  }
}