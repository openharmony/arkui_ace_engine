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
declare const Trace: (target: Object, propertyKey: string) => void;
interface LayoutConstraint {};
class FrameNode {};
interface Position {};

enum LocalizedAlignment {
  TOP_START = 'top_start',
  TOP = 'top',
  TOP_END = 'top_end',
  START = 'start',
  CENTER = 'center',
  END = 'end',
  BOTTOM_START = 'bottom_start',
  BOTTOM = 'bottom',
  BOTTOM_END = 'bottom_end',
};

enum LayoutType {
  DEFAULT_LAYOUT = 0,
  CUSTOM_LAYOUT = 1,
  COLUMN_LAYOUT = 2,
  ROW_LAYOUT = 3,
  STACK_LAYOUT = 4,
}

enum FlexAlign {
  Start = 1,
  Center = 2,
  End = 3,
  SpaceBetween = 6,
  SpaceAround = 7,
  SpaceEvenly = 8
}

enum VerticalAlign {
  Top = 1,
  Center = 2,
  Bottom = 3
}

enum HorizontalAlign {
  Start = 1,
  Center = 2,
  End = 3
}

interface Resource {}
declare type SpaceType = number | string | Resource;

interface StackLayoutAlgorithmOption {
  alignContent?: LocalizedAlignment;
}

interface RowLayoutAlgorithmOption {
  space?: SpaceType;
  alignItems?: VerticalAlign;
  justifyContent?: FlexAlign;
  isReverse?: boolean;
}

interface ColumnLayoutAlgorithmOption {
  space?: SpaceType;
  alignItems?: HorizontalAlign;
  justifyContent?: FlexAlign;
  isReverse?: boolean;
}

function getOptionalVal<T>(defaultVal: T, arg?: T) : T{
  return arg !== undefined ? arg : defaultVal
}

class BaseLayoutAlgorithm {
  constructor() {
    this.layoutType = LayoutType.DEFAULT_LAYOUT
  }
  public layoutType: LayoutType;
}

@ObservedV2
class StackLayoutAlgorithm extends BaseLayoutAlgorithm {
  constructor(option?: StackLayoutAlgorithmOption) {
    super()
    this.alignContent = LocalizedAlignment.CENTER
    if (option) {
      this.alignContent = getOptionalVal(LocalizedAlignment.CENTER, option.alignContent)
    }
    this.layoutType = LayoutType.STACK_LAYOUT;
  }
  @Trace public alignContent: LocalizedAlignment;
}

@ObservedV2
class ColumnLayoutAlgorithm extends BaseLayoutAlgorithm {
  constructor(option?: ColumnLayoutAlgorithmOption) {
    super()
    this.space = 0
    this.alignItems = HorizontalAlign.Center
    this.justifyContent = FlexAlign.Start
    this.isReverse = false
    if (option) {
      this.space = getOptionalVal(0, option.space)
      this.alignItems = getOptionalVal(HorizontalAlign.Center, option.alignItems)
      this.justifyContent = getOptionalVal(FlexAlign.Start, option.justifyContent)
      this.isReverse = getOptionalVal(false, option.isReverse)
    }
    this.layoutType = LayoutType.COLUMN_LAYOUT;
  }
  @Trace public space: SpaceType;
  @Trace public alignItems: HorizontalAlign;
  @Trace public justifyContent: FlexAlign;
  @Trace public isReverse: boolean;
}

@ObservedV2
class RowLayoutAlgorithm extends BaseLayoutAlgorithm {
  constructor(option?: RowLayoutAlgorithmOption) {
    super()
    this.space = 0
    this.alignItems = VerticalAlign.Center
    this.justifyContent = FlexAlign.Start
    this.isReverse = false
    if (option) {
      this.space = getOptionalVal(0, option.space)
      this.alignItems = getOptionalVal(VerticalAlign.Center, option.alignItems)
      this.justifyContent = getOptionalVal(FlexAlign.Start, option.justifyContent)
      this.isReverse = getOptionalVal(false, option.isReverse)
    }
    this.layoutType = LayoutType.ROW_LAYOUT;
  }
  @Trace public space?: SpaceType;
  @Trace public alignItems?: VerticalAlign;
  @Trace public justifyContent?: FlexAlign;
  @Trace public isReverse?: boolean;
}

class CustomLayoutAlgorithm extends BaseLayoutAlgorithm {
  constructor() {
    super()
    this.layoutType = LayoutType.CUSTOM_LAYOUT;
  }
  onMeasure(self: FrameNode, constraint: LayoutConstraint): void {}
  onLayout(self: FrameNode, position: Position): void {}
}

export default {
  StackLayoutAlgorithm, ColumnLayoutAlgorithm, RowLayoutAlgorithm, CustomLayoutAlgorithm
};