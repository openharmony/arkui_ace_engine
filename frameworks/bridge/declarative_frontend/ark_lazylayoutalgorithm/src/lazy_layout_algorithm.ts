/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

type ConstructorV2 = {
  new (...args: any[]): any;
};
declare function ObservedV2<T extends ConstructorV2>(BaseClass: T): T;
interface LayoutConstraint {};
class FrameNode {};
interface Position {};

enum LazyLayoutDirection {
  FORWARD = 0,
  BACKWARD = 1,
}

enum Axis {
  Vertical = 0,
  Horizontal = 1,
}

interface LazyLayoutInfo {
  viewStart: number;
  viewEnd: number;
  lazyLayoutDirection: LazyLayoutDirection;
}

interface LazyLayoutResult {
  adjustedOffset: number;
  inActiveChildren: number[];
}

class LazyLayoutHelper {
  private info: LazyLayoutInfo;
  public result: LazyLayoutResult = { adjustedOffset: 0, inActiveChildren: [] };

  constructor(info: LazyLayoutInfo) {
    this.info = info;
  }

  getViewStart(): number {
    return this.info.viewStart;
  }

  getViewEnd(): number {
    return this.info.viewEnd;
  }

  getLazyLayoutDirection(): LazyLayoutDirection {
    return this.info.lazyLayoutDirection;
  }

  setAdjustedOffset(offset: number): void {
    this.result.adjustedOffset = offset;
  }

  setChildrenInactive(children: number[]): void {
    this.result.inActiveChildren = children;
  }

  getResult(): LazyLayoutResult {
    return this.result;
  }
}

interface LazyCustomLayoutAlgorithmOption {
  axis?: Axis;
}

function getOptionalVal<T>(defaultVal: T, arg?: T) : T{
  return arg !== undefined ? arg : defaultVal
}

@ObservedV2
class LazyCustomLayoutAlgorithm {
  constructor(option?: LazyCustomLayoutAlgorithmOption) {
    this.axis = Axis.Vertical
    if (option) {
      this.axis = getOptionalVal(Axis.Vertical, option.axis)
    }
  }
  private axis: Axis;

  onMeasure(self: FrameNode, constraint: LayoutConstraint, helper?: LazyLayoutHelper): void {}
  onLayout(self: FrameNode, position: Position): void {}

  __onMeasure__(self: FrameNode, constraint: LayoutConstraint, info: LazyLayoutInfo): LazyLayoutResult {
    let helper = new LazyLayoutHelper(info);
    this.onMeasure(self, constraint, helper);
    return helper.getResult();
  }
}

export default {
  LazyLayoutDirection, LazyLayoutHelper, LazyCustomLayoutAlgorithm
};