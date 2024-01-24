/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

interface Frame {
  x: number;
  y: number;
  width: number;
  height: number;
}

interface Vector2 {
  x: number
  y: number
}

interface Vector3 {
  x: number;
  y: number;
  z: number;
}

type Transform = [
  number,
  number,
  number,
  number,
  number,
  number,
  number,
  number,
  number,
  number,
  number,
  number,
  number,
  number,
  number,
  number
];

enum BorderStyle {
  SOLID = 0,
  DASHED,
  DOTTED,
  NONE
}

type EdgeStyles = {
  top?: BorderStyle;
  right?: BorderStyle;
  bottom?: BorderStyle;
  left?: BorderStyle;
};

interface Edges {
  left: number,
  right: number,
  top: number,
  bottom: number,
}

type EdgeWidths = Edges;

type EdgeColors = Edges;

interface Corners {
  topLeft: number,
  topRight: number,
  bottomLeft: number,
  bottomRight: number
}

type BorderRadiuses = Corners;

interface Rect {
  left: number,
  right: number,
  top: number,
  bottom: number
}

interface CornerRadius {
  topLeft: Vector2,
  topRight: Vector2,
  bottomLeft: Vector2,
  bottomRight: Vector2
}

interface RoundRect {
  rect: Rect,
  corners: CornerRadius
}

interface Circle {
  centerX: number,
  centerY: number,
  radius: number
}

interface CommandPath {
  commands: string
}

class ShapeMask {
  public rect: Rect | null = null;
  public roundRect: RoundRect | null = null;
  public circle: Circle | null = null;
  public oval: Rect | null = null;
  public path: CommandPath | null = null;
  public fillColor: number = 0XFF000000;
  public strokeColor: number = 0XFF000000;
  public strokeWidth: number = 0;
  setRectShape(rect: Rect) {
    this.rect = rect;
    this.roundRect = null;
    this.circle = null;
    this.oval = null;
    this.path = null;
  }
  setRoundRectShape(roundRect: RoundRect) {
    this.roundRect = roundRect;
    this.rect = null;
    this.circle = null;
    this.oval = null;
    this.path = null;
  }
  setCircleShape(circle: Circle) {
    this.circle = circle;
    this.rect = null;
    this.roundRect = null;
    this.oval = null;
    this.path = null;
  }
  setOvalShape(oval: Rect) {
    this.oval = oval;
    this.rect = null;
    this.circle = null;
    this.roundRect = null;
    this.path = null;
  }
  setCommandPath(path: CommandPath) {
    this.path = path;
    this.oval = null;
    this.rect = null;
    this.circle = null;
    this.roundRect = null;
  }
}

class RenderNode {
  private childrenList: Array<RenderNode>;
  private nodePtr: number | null;
  private parentRenderNode: RenderNode | null;
  private backgroundColorValue: number;
  private clipToFrameValue: boolean;
  private frameValue: Frame;
  private opacityValue: number;
  private pivotValue: Vector2;
  private rotationValue: Vector3;
  private scaleValue: Vector2;
  private shadowColorValue: number;
  private shadowOffsetValue: Vector2;
  private shadowAlphaValue: number;
  private shadowElevationValue: number;
  private shadowRadiusValue: number;
  private transformValue: Transform;
  private translationValue: Vector2;
  private baseNode_ : __JSBaseNode__;
  private borderStyleValue: EdgeStyles;
  private borderWidthValue: EdgeWidths;
  private borderColorValue: EdgeColors;
  private borderRadiusValue: BorderRadiuses;
  private shapeMaskValue: ShapeMask;

  constructor(type: string) {
    this.nodePtr = null;
    this.childrenList = [];
    this.parentRenderNode = null;
    this.backgroundColorValue = 0;
    this.clipToFrameValue = false;
    this.frameValue = { x: 0, y: 0, width: 0, height: 0 };
    this.opacityValue = 1.0;
    this.pivotValue = { x: 0.5, y: 0.5 };
    this.rotationValue = { x: 0, y: 0, z: 0 };
    this.scaleValue = { x: 1.0, y: 1.0 };
    this.shadowColorValue = 0;
    this.shadowOffsetValue = { x: 0, y: 0 };
    this.shadowAlphaValue = 0;
    this.shadowElevationValue = 0;
    this.shadowRadiusValue = 0;
    this.transformValue = [1, 0, 0, 0,
      0, 1, 0, 0,
      0, 0, 1, 0,
      0, 0, 0, 1];
    this.translationValue = { x: 0, y: 0 };
    if (type === 'FrameNode') {
      return;
    }
    this.baseNode_ = new __JSBaseNode__();
    this.baseNode_.draw = this.draw;
    this.nodePtr = this.baseNode_.createRenderNode(this);
  }

  set backgroundColor(color: number) {
    this.backgroundColorValue = this.checkUndefinedOrNullWithDefaultValue<number>(color, 0);
    GetUINativeModule().renderNode.setBackgroundColor(this.nodePtr, this.backgroundColorValue);
  }
  set clipToFrame(useClip: boolean) {
    this.clipToFrameValue = this.checkUndefinedOrNullWithDefaultValue<boolean>(useClip, false);
    GetUINativeModule().renderNode.setClipToFrame(this.nodePtr, this.clipToFrameValue);
  }
  set frame(frame: Frame) {
    if (frame === undefined || frame === null) {
      this.frameValue = { x: 0, y: 0, width: 0, height: 0 };
    } else {
      this.size = { width: frame.width, height: frame.height };
      this.position = { x: frame.x, y: frame.y };
    }
  }
  set opacity(value: number) {
    this.opacityValue = this.checkUndefinedOrNullWithDefaultValue<number>(value, 1.0);
    GetUINativeModule().common.setOpacity(this.nodePtr, this.opacityValue);
  }
  set pivot(pivot: Vector2) {
    if (pivot === undefined || pivot === null) {
      this.pivotValue = { x: 0.5, y: 0.5 };
    } else {
      this.pivotValue.x = this.checkUndefinedOrNullWithDefaultValue<number>(pivot.x, 0.5);
      this.pivotValue.y = this.checkUndefinedOrNullWithDefaultValue<number>(pivot.y, 0.5);
    }
    GetUINativeModule().renderNode.setPivot(this.nodePtr, this.pivotValue.x, this.pivotValue.y);
  }
  set position(position: Vector2) {
    if (position === undefined || position === null) {
      this.frameValue.x = 0;
      this.frameValue.y = 0;
    } else {
      this.frameValue.x = this.checkUndefinedOrNullWithDefaultValue<number>(position.x, 0);
      this.frameValue.y = this.checkUndefinedOrNullWithDefaultValue<number>(position.y, 0);
    }
    GetUINativeModule().common.setPosition(this.nodePtr, this.frameValue.x, this.frameValue.y);
  }
  set rotation(rotation: Vector3) {
    if (rotation === undefined || rotation === null) {
      this.rotationValue = { x: 0, y: 0, z: 0 };
    } else {
      this.rotationValue.x = this.checkUndefinedOrNullWithDefaultValue<number>(rotation.x, 0);
      this.rotationValue.y = this.checkUndefinedOrNullWithDefaultValue<number>(rotation.y, 0);
      this.rotationValue.z = this.checkUndefinedOrNullWithDefaultValue<number>(rotation.z, 0);
    }
    GetUINativeModule().renderNode.setRotation(this.nodePtr, this.rotationValue.x, this.rotationValue.y, this.rotationValue.z);
  }
  set scale(scale: Vector2) {
    if (scale === undefined || scale === null) {
      this.scaleValue = { x: 1.0, y: 1.0 };
    } else {
      this.scaleValue.x = this.checkUndefinedOrNullWithDefaultValue<number>(scale.x, 1.0);
      this.scaleValue.y = this.checkUndefinedOrNullWithDefaultValue<number>(scale.y, 1.0);
    }
    GetUINativeModule().renderNode.setScale(this.nodePtr, this.scaleValue.x, this.scaleValue.y);
  }
  set shadowColor(color: number) {
    this.shadowColorValue = this.checkUndefinedOrNullWithDefaultValue<number>(color, 0);
    GetUINativeModule().renderNode.setShadowColor(this.nodePtr, this.shadowColorValue);
  }
  set shadowOffset(offset: Vector2) {
    if (offset === undefined || offset === null) {
      this.shadowOffsetValue = { x: 0, y: 0 };
    } else {
      this.shadowOffsetValue.x = this.checkUndefinedOrNullWithDefaultValue<number>(offset.x, 0);
      this.shadowOffsetValue.y = this.checkUndefinedOrNullWithDefaultValue<number>(offset.y, 0);
    }
    GetUINativeModule().renderNode.setShadowOffset(this.nodePtr, this.shadowOffsetValue.x, this.shadowOffsetValue.y);
  }
  set shadowAlpha(alpha: number) {
    this.shadowAlphaValue = this.checkUndefinedOrNullWithDefaultValue<number>(alpha, 0);
    GetUINativeModule().renderNode.setShadowAlpha(this.nodePtr, this.shadowAlphaValue);
  }
  set shadowElevation(elevation: number) {
    this.shadowElevationValue = this.checkUndefinedOrNullWithDefaultValue<number>(elevation, 0);
    GetUINativeModule().renderNode.setShadowElevation(this.nodePtr, this.shadowElevationValue);
  }
  set shadowRadius(radius: number) {
    this.shadowRadiusValue = this.checkUndefinedOrNullWithDefaultValue<number>(radius, 0);
    GetUINativeModule().renderNode.setShadowRadius(this.nodePtr, this.shadowRadiusValue);
  }
  set size(size: Size) {
    if (size === undefined || size === null) {
      this.frameValue.width = 0;
      this.frameValue.height = 0;
    } else {
      this.frameValue.width = this.checkUndefinedOrNullWithDefaultValue<number>(size.width, 0);
      this.frameValue.height = this.checkUndefinedOrNullWithDefaultValue<number>(size.height, 0);
    }
    GetUINativeModule().renderNode.setSize(this.nodePtr, this.frameValue.width, this.frameValue.height);
  }
  set transform(transform: Transform) {
    if (transform === undefined || transform === null) {
      this.transformValue = [1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1];
    } else {
      let i: number = 0;
      while (i < transform.length && i < 16) {
        if (i % 5 === 0) {
          this.transformValue[i] = this.checkUndefinedOrNullWithDefaultValue<number>(transform[i], 1);
        } else {
          this.transformValue[i] = this.checkUndefinedOrNullWithDefaultValue<number>(transform[i], 0);
        }
        i = i + 1;
      }
    }
    GetUINativeModule().common.setTransform(this.nodePtr, this.transformValue);
  }
  set translation(translation: Vector2) {
    if (translation === undefined || translation === null) {
      this.translationValue = { x: 0, y: 0 };
    } else {
      this.translationValue.x = this.checkUndefinedOrNullWithDefaultValue<number>(translation.x, 0);
      this.translationValue.y = this.checkUndefinedOrNullWithDefaultValue<number>(translation.y, 0);
    }
    GetUINativeModule().renderNode.setTranslate(this.nodePtr, this.translationValue.x, this.translationValue.y, 0);
  }
  get backgroundColor(): number {
    return this.backgroundColorValue;
  }
  get clipToFrame(): boolean {
    return this.clipToFrameValue;
  }
  get opacity(): number {
    return this.opacityValue;
  }
  get frame(): Frame {
    return this.frameValue;
  }
  get pivot(): Vector2 {
    return this.pivotValue;
  }
  get position(): Vector2 {
    return { x: this.frameValue.x, y: this.frameValue.y };
  }
  get rotation(): Vector3 {
    return this.rotationValue;
  }
  get scale(): Vector2 {
    return this.scaleValue;
  }
  get shadowColor(): number {
    return this.shadowColorValue;
  }
  get shadowOffset(): Vector2 {
    return this.shadowOffsetValue;
  }
  get shadowAlpha(): number {
    return this.shadowAlphaValue;
  }
  get shadowElevation(): number {
    return this.shadowElevationValue;
  }
  get shadowRadius(): number {
    return this.shadowRadiusValue;
  }
  get size(): Size {
    return { width: this.frameValue.width, height: this.frameValue.height };
  }
  get transform(): Transform {
    return this.transformValue;
  }
  get translation(): Vector2 {
    return this.translationValue;
  }
  checkUndefinedOrNullWithDefaultValue<T>(arg: T, defaultValue: T): T {
    if (arg === undefined || arg === null) {
      return defaultValue;
    } else {
      return arg;
    }
  }
  appendChild(node: RenderNode) {
    if (node === undefined || node === null) {
      return;
    }
    if (this.childrenList.findIndex(element => element === node) !== -1) {
      return;
    }
    this.childrenList.push(node);
    node.parentRenderNode = this;
    GetUINativeModule().renderNode.appendChild(this.nodePtr, node.nodePtr);
  }
  insertChildAfter(child: RenderNode, sibling: RenderNode | null) {
    if (child === undefined || child === null) {
      return;
    }
    let indexOfNode: number = this.childrenList.findIndex(element => element === child);
    if (indexOfNode !== -1) {
      return;
    }
    child.parentRenderNode = this;
    let indexOfSibling = this.childrenList.findIndex(element => element === sibling);
    if (indexOfSibling === -1) {
      sibling === null;
    }
    if (sibling === undefined || sibling === null) {
      this.childrenList.splice(0, 0, child);
      GetUINativeModule().renderNode.insertChildAfter(this.nodePtr, child.nodePtr, null);
    } else {
      this.childrenList.splice(indexOfSibling + 1, 0, child);
      GetUINativeModule().renderNode.insertChildAfter(this.nodePtr, child.nodePtr, sibling.nodePtr);
    }
  }
  removeChild(node: RenderNode) {
    if (node === undefined || node === null) {
      return;
    }
    const index = this.childrenList.findIndex(element => element === node);
    if (index === -1) {
      return;
    }
    const child = this.childrenList[index];
    child.parentRenderNode = null;
    this.childrenList.splice(index, 1);
    GetUINativeModule().renderNode.removeChild(this.nodePtr, node.nodePtr);
  }
  clearChildren() {
    this.childrenList = new Array<RenderNode>();
    GetUINativeModule().renderNode.clearChildren(this.nodePtr);
  }
  getChild(index: number): RenderNode | null {
    if (this.childrenList.length > index && index >= 0) {
      return this.childrenList[index];
    }
    return null;
  }
  getFirstChild(): RenderNode | null {
    if (this.childrenList.length > 0) {
      return this.childrenList[0];
    }
    return null;
  }
  getNextSibling(): RenderNode | null {
    if (this.parentRenderNode === undefined || this.parentRenderNode === null) {
      return null;
    }
    let siblingList = this.parentRenderNode.childrenList;
    const index = siblingList.findIndex(element => element === this);
    if (index === -1) {
      return null;
    }
    return this.parentRenderNode.getChild(index + 1);
  }
  getPreviousSibling(): RenderNode | null {
    if (this.parentRenderNode === undefined || this.parentRenderNode === null) {
      return null;
    }
    let siblingList = this.parentRenderNode.childrenList;
    const index = siblingList.findIndex(element => element === this);
    if (index === -1) {
      return null;
    }
    return this.parentRenderNode.getChild(index - 1);
  }
  setNodePtr(nodePtr: number | null) {
    this.nodePtr = nodePtr;
  }
  setBaseNode(baseNode: BaseNode | null) {
    this.baseNode_ = baseNode;
  }
  dispose() {
    this.baseNode_.dispose()
  }
  getNodePtr(): number | null {
    return this.nodePtr;
  }
  draw(context) {
  }
  invalidate() {
    GetUINativeModule().renderNode.invalidate(this.nodePtr);
  }
  set borderStyle(style: EdgeStyles) {
    if (style === undefined || style === null) {
      this.borderStyleValue = { left: BorderStyle.NONE, top: BorderStyle.NONE, right: BorderStyle.NONE, bottom: BorderStyle.NONE };
    } else {
      this.borderStyleValue = style;
    }
    GetUINativeModule().renderNode.setBorderStyle(this.nodePtr, this.borderStyleValue.left, this.borderStyleValue.top, this.borderStyleValue.right, this.borderStyleValue.bottom);
  }
  get borderStyle(): EdgeStyles {
    return this.borderStyleValue;
  }
  set borderWidth(width: EdgeWidths) {
    if (width === undefined || width === null) {
      this.borderWidthValue = { left: 0, top: 0, right: 0, bottom: 0 };
    } else {
      this.borderWidthValue = width;
    }
    GetUINativeModule().renderNode.setBorderWidth(this.nodePtr, this.borderWidthValue.left, this.borderWidthValue.top, this.borderWidthValue.right, this.borderWidthValue.bottom);
  }
  get borderWidth(): EdgeWidths {
    return this.borderWidthValue;
  }
  set borderColor(color: EdgeColors) {
    if (color === undefined || color === null) {
      this.borderColorValue = { left: 0XFF000000, top: 0XFF000000, right: 0XFF000000, bottom: 0XFF000000 };
    } else {
      this.borderColorValue = color;
    }
    GetUINativeModule().renderNode.setBorderColor(this.nodePtr, this.borderColorValue.left, this.borderColorValue.top, this.borderColorValue.right, this.borderColorValue.bottom);
  }
  get borderColor(): EdgeColors {
    return this.borderColorValue;
  }
  set borderRadius(radius: BorderRadiuses) {
    if (radius === undefined || radius === null) {
      this.borderRadiusValue = { topLeft: 0, topRight: 0, bottomLeft: 0, bottomRight: 0 };
    } else {
      this.borderRadiusValue = radius;
    }
    GetUINativeModule().renderNode.setBorderRadius(this.nodePtr, this.borderRadiusValue.topLeft, this.borderRadiusValue.topRight, this.borderRadiusValue.bottomLeft, this.borderRadiusValue.bottomRight);
  }
  get borderRadius(): BorderRadiuses {
    return this.borderRadiusValue;
  }
  set shapeMask(shapeMask: ShapeMask) {
    if (shapeMask === undefined || shapeMask === null) {
      this.shapeMaskValue = new ShapeMask();
    } else {
      this.shapeMaskValue = shapeMask;
    }
    if (this.shapeMaskValue.rect !== null) {
      const rectMask = this.shapeMaskValue.rect;
      GetUINativeModule().renderNode.setRectMask(this.nodePtr, rectMask.left, rectMask.top, rectMask.right, rectMask.bottom, this.shapeMaskValue.fillColor, this.shapeMaskValue.strokeColor, this.shapeMaskValue.strokeWidth);
    } else if (this.shapeMaskValue.circle !== null) {
      const circle = this.shapeMaskValue.circle;
      GetUINativeModule().renderNode.setCircleMask(this.nodePtr, circle.centerX, circle.centerY, circle.radius, this.shapeMaskValue.fillColor, this.shapeMaskValue.strokeColor, this.shapeMaskValue.strokeWidth);
    } else if (this.shapeMaskValue.roundRect !== null) {
      const reoundRect = this.shapeMask.roundRect;
      const corners = reoundRect.corners;
      const rect = reoundRect.rect;
      GetUINativeModule().renderNode.setRoundRectMask(
        this.nodePtr, 
        corners.topLeft.x,
        corners.topLeft.y, 
        corners.topRight.x,
        corners.topRight.y, 
        corners.bottomLeft.x,
        corners.bottomLeft.y, 
        corners.bottomRight.x,
        corners.bottomRight.y,
        rect.left,
        rect.top,
        rect.right,
        rect.bottom,
        this.shapeMaskValue.fillColor,
        this.shapeMaskValue.strokeColor,
        this.shapeMaskValue.strokeWidth);
    } else if (this.shapeMaskValue.oval !== null) {
      const oval = this.shapeMaskValue.oval;
      GetUINativeModule().renderNode.setOvalMask(this.nodePtr, oval.left, oval.top, oval.right, oval.bottom, this.shapeMaskValue.fillColor, this.shapeMaskValue.strokeColor, this.shapeMaskValue.strokeWidth);
    } else if (this.shapeMaskValue.path !== null) {
      const path = this.shapeMaskValue.path;
      GetUINativeModule().renderNode.setPath(this.nodePtr, path.commands, this.shapeMaskValue.fillColor, this.shapeMaskValue.strokeColor, this.shapeMaskValue.strokeWidth);
    }
  }
  get shapeMask(): ShapeMask {
    return this.shapeMaskValue;
  }
}

function edgeColors(all: number): EdgeColors {
  return { left: all, top: all, right: all, bottom: all };
}

function edgeWidths(all: number): EdgeWidths {
  return { left: all, top: all, right: all, bottom: all };
}

function borderStyles(all: BorderStyle): EdgeStyles {
  return { left: all, top: all, right: all, bottom: all };
}

function borderRadiuses(all: number): BorderRadiuses {
  return { topLeft: all, topRight: all, bottomLeft: all, bottomRight: all };
}
