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
  public uiContext: UIContext;
  public recyclePoolSize = 5;
  public builder: WrappedBuilder<[Object]>;
  public frameNode?: FrameNode;

  constructor(uiContext: UIContext, builder: WrappedBuilder<[Object]>) {
    this.uiContext = uiContext;
    this.builder = builder;
  }

  public childrenMap: Map<number, BuilderNode<[Object]>> = new Map<number, BuilderNode<[Object]>>();
  public recyclePool: BuilderNode<[Object]>[] = [];

  abstract getCount(): number;

  abstract getData(index: number): Object;

  getChild(index: number): FrameNode | null {
    if (index >= this.getCount() || index < 0) {
      return null;
    }
    let buildNode = this.childrenMap.get(index);
    if (buildNode) {
      return buildNode.getFrameNode();
    }
    buildNode = this.recyclePool.pop();
    if (buildNode) {
      buildNode.update(this.getData(index))
    } else {
      buildNode = new BuilderNode(this.uiContext);
      buildNode.build(this.builder, this.getData(index), { nestingBuilderSupported: true });
    }
    let frameNode = buildNode.getFrameNode();
    this.frameNode?.appendChild(frameNode);
    this.childrenMap.set(index, buildNode);
    return frameNode;
  }

  recycleChild(index: number): void {
    let node = this.childrenMap.get(index);
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
  private currentOffset: number = 0;
  private currentDelta: number = 0;
  private itemHeight = 200;
  private startIndex = -1;
  private endIndex = -1;

  SetItemHeight(itemHeight: number) {
    this.itemHeight = itemHeight;
  }

  onWillScroll(recycleNode: RecycleNode, currOffset: OffsetResult, delta: OffsetResult,
    scrollState: ScrollState, scrollSource: ScrollSource): OffsetResult | void {
    this.currentOffset = vp2px(currOffset.yOffset);
    this.currentDelta = vp2px(delta.yOffset);
    recycleNode.setNeedsLayout();
  }

  // 计算各个元素的大小和位置
  onMeasure(recycleNode: RecycleNode, constraint: LayoutConstraint): void {
    constraint.maxSize.height = constraint.percentReference.height;
    let sizeRes: Size =
      { width: constraint.percentReference.width, height: this.itemHeight * recycleNode.adapter.getCount() };
    let offset = this.currentOffset + this.currentDelta;
    let startIndex = Math.floor(offset / this.itemHeight);
    let endIndex = Math.floor((offset + constraint.percentReference.height) / this.itemHeight);
    for (let i = startIndex; i <= endIndex; i++) {
      let child = recycleNode.adapter.getChild(i);
      if (child) {
        child.measure(constraint);
      }
    }
    // recycle
    if (this.startIndex >= 0 && this.startIndex < startIndex) {
      for (let i = this.startIndex; i < startIndex; i++) {
        recycleNode.adapter.recycleChild(i);
      }
    }
    if (this.endIndex >= 0 && this.endIndex > endIndex) {
      for (let i = endIndex; i < this.endIndex; i++) {
        recycleNode.adapter.recycleChild(i + 1);
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

interface ItemPos {
  start: number;
  end: number;
}

declare interface LazyLayoutInfo {
  viewStart: number;
  viewEnd: number;
}

class ColumnLayoutAlgorithm {
  private itemArr: ItemPos[] = [];
  private itemArrStartIndex: number = -1;
  private estimateItemHeight: number = -1;
  private totalHeight: number = 0;
  private childCnt:number = 0;
  private startIndex: number = -1;
  private endIndex: number = -1;

  onMeasure(self: RecycleAdapter, constraint: LayoutConstraint, viewPos: LazyLayoutInfo): Size {
    constraint.maxSize.height = constraint.percentReference.height;
    this.childCnt = self.getCount();
    if (this.childCnt == 0) {
      this.itemArr.length = 0;
      this.totalHeight = 0;
      return { width: constraint.maxSize.width, height: 0 };
    }
    if (viewPos.viewStart > this.totalHeight || viewPos.viewEnd < 0) {
      this.startIndex = -1;
      this.endIndex = -1;
      return { width: constraint.maxSize.width, height: this.totalHeight };
    }
    let currIndex = 0;
    let currPos = 0;
    if (this.itemArrStartIndex >= 0) {
      // 使用二分查找优化查找起始索引
      currIndex = this.findStartIndex(viewPos.viewStart);
      currPos = this.itemArr[currIndex - this.itemArrStartIndex].start;
    }
    let startIndex = currIndex;
    let startPos = currPos;
    let tmpItemArr: ItemPos[] = [];
    let tmpItemArrStartIndex: number = Number.MAX_SAFE_INTEGER;
    for (; currIndex < this.childCnt; currIndex++) {
      let child = self.getChild(currIndex);
      if (child) {
        child.measure(constraint);
        let itemHeight = child.getMeasuredSize().height;
        tmpItemArrStartIndex = Math.min(currIndex, tmpItemArrStartIndex);
        tmpItemArr[currIndex - tmpItemArrStartIndex] = {
          start: currPos, end: currPos + itemHeight,
        };
        currPos += itemHeight;
      } else {
        console.error(`Get child[${currIndex}] error`);
      }
      if (currPos > viewPos.viewEnd) {
        break;
      }
    }
    if (startPos > viewPos.viewStart) {
      currPos = startPos;
      for (currIndex = startIndex - 1; currIndex >= 0; currIndex--) {
        let child = self.getChild(currIndex);
        if (child) {
          child.measure(constraint);
          let itemHeight = child.getMeasuredSize().height;
          tmpItemArrStartIndex = Math.min(currIndex, tmpItemArrStartIndex);
          tmpItemArr.unshift({
            start: currPos - itemHeight, end: currPos,
          });
          currPos -= itemHeight;
        } else {
          console.error(`Get child[${currIndex}] error`);
        }
        if (currPos < viewPos.viewStart) {
          break;
        }
      }
    }
    if (tmpItemArr.length <= 0) {
      console.error(`No Child measured`);
      return { width: constraint.maxSize.width, height: this.totalHeight };
    }
    // 保存旧的索引范围，用于回收子组件
    const oldStartIndex = this.startIndex;
    const oldEndIndex = this.endIndex;
    const newStartIndex = tmpItemArrStartIndex;
    const newEndIndex = tmpItemArrStartIndex + tmpItemArr.length;

    this.startIndex = newStartIndex;
    this.endIndex = newEndIndex;

    // 回收在老的startIndex和endIndex范围，但不在新的startIndex和endIndex的子组件
    if (oldStartIndex >= 0 && oldEndIndex >= 0) {
      for (let i = oldStartIndex; i < oldEndIndex; i++) {
        // 如果该索引不在新的范围内，则回收
        if (i < newStartIndex || i >= newEndIndex) {
          self.recycleChild(i);
        }
      }
    }

    this.merge(tmpItemArrStartIndex, tmpItemArr);
    let endIndex = this.itemArrStartIndex + this.itemArr.length;
    let endPos = this.itemArr[this.itemArr.length - 1].end;
    if (this.childCnt > endIndex) {
      this.totalHeight = (this.childCnt - endIndex) * this.estimateItemHeight + endPos;
    } else {
      this.totalHeight = endPos;
    }
    return { width: constraint.maxSize.width, height: this.totalHeight };
  }

  onLayout(self: RecycleAdapter): void {
    if (this.childCnt == 0) {
      return;
    }
    for (let i = this.startIndex; i < this.endIndex; i++) {
      let child = self.getChild(i);

      child?.layout({x: 0, y: this.itemArr[i - this.itemArrStartIndex].start });
    }
  }

  // 将增量数据更新到startIndex和itemArr中，deltaStartIndex表示deltaItemArr起始索引号
  // 更新完成后，确保itemArr中前一项数据的end和后一项数据的start相同。
  // 如果增量元素和已有元素有空隙，则生成大小为estimateSize的元素填充。
  merge(deltaStartIndex: number, deltaItemArr: ItemPos[]): void {
    // 如果没有增量数据，直接返回
    if (!deltaItemArr || deltaItemArr.length === 0) {
      return;
    }

    // 如果当前没有数据，直接使用增量数据
    if (this.itemArr.length === 0) {
      this.itemArrStartIndex = deltaStartIndex;
      this.itemArr = [...deltaItemArr];
      // 计算并设置平均元素大小
      if (deltaItemArr.length > 0) {
        let totalSize = 0;
        for (const item of deltaItemArr) {
          totalSize += (item.end - item.start);
        }
        this.estimateItemHeight = totalSize / deltaItemArr.length;
      }
      // 执行约束检查后返回
      this.enforceConstraint();
      return;
    }

    // 计算增量数据相对于当前数据的起始偏移
    const deltaOffset = deltaStartIndex - this.itemArrStartIndex;

    // 如果增量数据完全在当前数据之后
    if (deltaOffset >= this.itemArr.length) {
      const gapIndex = deltaOffset - this.itemArr.length; // 空隙的元素数量
      if (gapIndex > 0 && this.estimateItemHeight > 0) {
        // 填充空隙
        const lastItem = this.itemArr[this.itemArr.length - 1];
        let currentEnd = lastItem.end;
        for (let i = 0; i < gapIndex; i++) {
          this.itemArr.push({ start: currentEnd, end: currentEnd + this.estimateItemHeight });
          currentEnd += this.estimateItemHeight;
        }
      }
      // 追加增量数据
      this.itemArr = this.itemArr.concat(deltaItemArr);
      return;
    }

    // 如果增量数据完全在当前数据之前
    if (deltaOffset + deltaItemArr.length <= 0) {
      const gapIndex = -deltaOffset - deltaItemArr.length; // 空隙的元素数量
      if (gapIndex > 0 && this.estimateItemHeight > 0) {
        // 填充空隙
        const firstItem = this.itemArr[0];
        let currentStart = firstItem.start;
        const fillItems: ItemPos[] = [];
        for (let i = gapIndex - 1; i >= 0; i--) {
          currentStart -= this.estimateItemHeight;
          fillItems.unshift({ start: currentStart, end: currentStart + this.estimateItemHeight });
        }
        this.itemArr = fillItems.concat(deltaItemArr).concat(this.itemArr);
      } else {
        this.itemArr = deltaItemArr.concat(this.itemArr);
      }
      this.itemArrStartIndex = deltaStartIndex;
      return;
    }

    // 增量数据与当前数据有重叠，需要合并
    // 计算需要删除的范围
    const removeStart = Math.max(0, deltaOffset);
    const removeEnd = Math.min(this.itemArr.length, deltaOffset + deltaItemArr.length);

    // 删除重叠部分
    this.itemArr.splice(removeStart, removeEnd - removeStart);

    // 重新计算插入位置（因为splice改变了数组长度）
    const insertPos = Math.max(0, deltaOffset);

    // 检查并填充前面的空隙
    let actualInsertPos = insertPos;
    if (actualInsertPos > 0 && this.estimateItemHeight > 0) {
      const prevItem = this.itemArr[actualInsertPos - 1];
      const firstDeltaItem = deltaItemArr[0];
      if (prevItem.end < firstDeltaItem.start) {
        const gapSize = firstDeltaItem.start - prevItem.end;
        const gapCount = Math.round(gapSize / this.estimateItemHeight);
        if (gapCount > 0) {
          let currentEnd = prevItem.end;
          const fillItems: ItemPos[] = [];
          for (let i = 0; i < gapCount; i++) {
            fillItems.push({ start: currentEnd, end: currentEnd + this.estimateItemHeight });
            currentEnd += this.estimateItemHeight;
          }
          this.itemArr.splice(actualInsertPos, 0, ...fillItems);
          actualInsertPos += gapCount; // 更新插入位置
        }
      }
    }

    // 插入增量数据
    this.itemArr.splice(actualInsertPos, 0, ...deltaItemArr);

    // 检查并填充后面的空隙
    const afterInsertPos = actualInsertPos + deltaItemArr.length;
    if (afterInsertPos < this.itemArr.length && this.estimateItemHeight > 0) {
      const lastDeltaItem = deltaItemArr[deltaItemArr.length - 1];
      const nextItem = this.itemArr[afterInsertPos];
      // 如果下一个元素开始于当前结束之前，需要调整后续元素的start和end
      if (nextItem.start < lastDeltaItem.end) {
        // 计算需要移动的距离
        const shiftAmount = lastDeltaItem.end - nextItem.start;
        // 调整后续所有元素的start和end，保持元素大小不变
        for (let i = afterInsertPos; i < this.itemArr.length; i++) {
          this.itemArr[i].start += shiftAmount;
          this.itemArr[i].end += shiftAmount;
        }
      } else if (lastDeltaItem.end < nextItem.start) {
        // 如果下一个元素开始于当前结束之后，填充间隙
        const gapSize = nextItem.start - lastDeltaItem.end;
        const gapCount = Math.round(gapSize / this.estimateItemHeight);
        if (gapCount > 0) {
          let currentEnd = lastDeltaItem.end;
          const fillItems: ItemPos[] = [];
          for (let i = 0; i < gapCount; i++) {
            fillItems.push({ start: currentEnd, end: currentEnd + this.estimateItemHeight });
            currentEnd += this.estimateItemHeight;
          }
          this.itemArr.splice(afterInsertPos, 0, ...fillItems);
        }
      }
    } else if (afterInsertPos > this.itemArr.length && this.estimateItemHeight > 0) {
      // 如果插入位置超过了数组长度（有间隙），填充间隙元素
      const lastDeltaItem = deltaItemArr[deltaItemArr.length - 1];
      // 计算需要填充多少个元素
      const gapCount = afterInsertPos - this.itemArr.length;
      let currentEnd = lastDeltaItem.end;
      for (let i = 0; i < gapCount; i++) {
        this.itemArr.push({ start: currentEnd, end: currentEnd + this.estimateItemHeight });
        currentEnd += this.estimateItemHeight;
      }
    }

    // itemArrStartIndex（如果增量数据在当前数据之前）
    if (deltaOffset < 0) {
      this.itemArrStartIndex = deltaStartIndex;
    }

    // 执行约束检查
    this.enforceConstraint();
  }

  // 确保满足约束：estimateSize * itemArrStartIndex = itemArr[0].start
  // 如果不满足，保持元素大小不变，调整所有元素的start和end
  private enforceConstraint(): void {
    if (this.itemArr.length > 0 && this.estimateItemHeight > 0) {
      const expectedStart = this.estimateItemHeight * this.itemArrStartIndex;
      const actualStart = this.itemArr[0].start;
      if (expectedStart !== actualStart) {
        const shiftAmount = expectedStart - actualStart;
        // 调整所有元素的start和end
        for (let i = 0; i < this.itemArr.length; i++) {
          this.itemArr[i].start += shiftAmount;
          this.itemArr[i].end += shiftAmount;
        }
      }
    }
  }

  // 使用二分查找找到第一个end > viewStart的索引
  private findStartIndex(viewStart: number): number {
    if (this.itemArr.length === 0) {
      return this.itemArrStartIndex;
    }

    let left = 0;
    let right = this.itemArr.length - 1;
    let result = this.itemArr.length; // 默认返回最后一个索引+1

    // 二分查找第一个满足 itemArr[i].end > viewStart 的索引
    while (left <= right) {
      const mid = Math.floor((left + right) / 2);
      if (this.itemArr[mid].end > viewStart) {
        result = mid;
        right = mid - 1; // 继续向左查找更小的索引
      } else {
        left = mid + 1; // 向右查找
      }
    }

    // 返回实际的索引号
    return this.itemArrStartIndex + result;
  }
}

export class ColumnLayoutManager extends LayoutManager {
  private currentOffset: number = 0;
  private currentDelta: number = 0;
  private layout = new ColumnLayoutAlgorithm();

  onWillScroll(recycleNode: RecycleNode, currOffset: OffsetResult, delta: OffsetResult,
    scrollState: ScrollState, scrollSource: ScrollSource): OffsetResult | void {
    this.currentOffset = vp2px(currOffset.yOffset);
    this.currentDelta = vp2px(delta.yOffset);
    recycleNode.setNeedsLayout();
  }
  onMeasure(recycleNode: RecycleNode, constraint: LayoutConstraint): void {
    let viewHeight = constraint.percentReference.height;
    let viewPos: LazyLayoutInfo = {
      viewStart: this.currentOffset + this.currentDelta,
      viewEnd: this.currentOffset + this.currentDelta + viewHeight,
    };
    let size = this.layout.onMeasure(recycleNode.adapter, constraint, viewPos);
    recycleNode.setMeasuredSize(size);
  }
  onLayout(recycleNode: RecycleNode, position: Position): void {
    this.layout.onLayout(recycleNode.adapter);
  }
}

// 设置内容元素的布局方法
export class RecycleNode extends FrameNode {
  public layoutManager: LayoutManager;
  public adapter: RecycleAdapter;

  constructor(uiContext: UIContext, layoutManager: LayoutManager, adapter: RecycleAdapter) {
    super(uiContext);
    this.layoutManager = layoutManager;
    this.adapter = adapter;
  }

  onMeasure(constraint: LayoutConstraint): void {
    this.layoutManager.onMeasure(this, constraint);
  }

  onLayout(position: Position): void {
    this.layoutManager.onLayout(this, position);
  }
}

export class RecycleViewController extends NodeController {
  public rootNode: RecycleNode | null = null;
  public layoutManager?: LayoutManager;
  public adapter?: RecycleAdapter;

  makeNode(uiContext: UIContext): FrameNode | null {
    if (this.layoutManager && this.adapter) {
      this.rootNode = new RecycleNode(uiContext, this.layoutManager, this.adapter);
      this.adapter.frameNode = this.rootNode;
    }
    return this.rootNode;
  }
}

@Component
export struct RecycleView {
  modifier?: ScrollModifier;
  scroller: Scroller = new Scroller();
  adapterController: RecycleViewController = new RecycleViewController();

  build() {
    Scroll(this.scroller) {
      NodeContainer(this.adapterController)
    }.attributeModifier(this.modifier)
    .onWillScroll((xOffset: number, yOffset: number, scrollState: ScrollState, scrollSource: ScrollSource) => {
      if (this.adapterController.rootNode) {
        this.adapterController.rootNode.layoutManager.onWillScroll(this.adapterController.rootNode,
          this.scroller.currentOffset(), { xOffset: xOffset, yOffset: yOffset }, scrollState, scrollSource);
      }
    })
  }
}