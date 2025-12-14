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
import matrix4 from '@ohos.matrix4';
import { Position } from '@ohos.arkui.node';
import { Vec2 } from '@kit.ArkGraphics3D';
import imageGeneration from '@ohos.arkui.intelligence.imageGeneration';

let PI = 3.14159265359

// 默认从(0, 0)开始变换
export function calcAABB(input: imageGeneration.ImageItem[], width: number, height: number) : number[][] {
  let xmin: number = 0;
  let xmax: number = 0;
  let ymin: number = 0;
  let ymax: number = 0;
  let tempRes: number[][] = []
  for (let index = 0; index < input.length; index++) {
    const item = input[index];
    let x = item.rect?.left ?? 0;
    let y = item.rect?.top?? 0;
    let w = (item.rect?.right ?? 0) - x;
    let h = (item.rect?.bottom ?? 0) - y;
    let rx = item.rotation?.centerX ?? 0.5 * w;
    let ry = item.rotation?.centerY ?? 0.5 * h;
    let roll = item.rotation?.angle ?? 0;
    let translateMat0: number[] = [
      1, 0, 0, -rx,
      0, 1, 0, -ry,
      0, 0, 1, 0,
      0, 0, 0, 1
    ]
    let rollMat: number[] = [
      Math.cos(roll), -Math.sin(roll), 0, 0,
      Math.sin(roll), Math.cos(roll), 0, 0,
      0, 0, 1, 0,
      0, 0, 0, 1
    ]
    let translateMat1: number[] = [
      1, 0, 0, x + rx,
      0, 1, 0, y + ry,
      0, 0, 1, 0,
      0, 0, 0, 1
    ]
    let tMat = combine(combine(translateMat0, rollMat), translateMat1)
    tempRes.push(tMat);
    let pos0: Position = { x: (0) * tMat[0] + (0) * tMat[1] + tMat[3], y: (0) * tMat[4] + (0) * tMat[5] + tMat[7] }
    let pos1: Position = { x: (0 + w) * tMat[0] + (0) * tMat[1] + tMat[3], y: (0 + w) * tMat[4] + (0) * tMat[5] + tMat[7] }
    let pos2: Position = { x: (0) * tMat[0] + (0 + h) * tMat[1] + tMat[3], y: (0) * tMat[4] + (0 + h) * tMat[5] + tMat[7] }
    let pos3: Position = { x: (0 + w) * tMat[0] + (0 + h) * tMat[1] + tMat[3], y: (0 + w) * tMat[4] + (0 + h) * tMat[5] + tMat[7] }
    if (index == 0) {
      xmin = Math.min(pos0.x, pos1.x, pos2.x, pos3.x)
      ymin = Math.min(pos0.y, pos1.y, pos2.y, pos3.y)
      xmax = Math.max(pos0.x, pos1.x, pos2.x, pos3.x)
      ymax = Math.max(pos0.y, pos1.y, pos2.y, pos3.y)
    } else {
      xmin = Math.min(xmin, pos0.x, pos1.x, pos2.x, pos3.x)
      ymin = Math.min(ymin, pos0.y, pos1.y, pos2.y, pos3.y)
      xmax = Math.max(xmax, pos0.x, pos1.x, pos2.x, pos3.x)
      ymax = Math.max(ymax, pos0.y, pos1.y, pos2.y, pos3.y)
    }
  }
  let w = xmax - xmin
  let h = ymax - ymin
  let scale: number = Math.abs(height / h) > Math.abs(width / w) ? (width / w) : (height / h)
  let res: number[][] = []
  for (let index = 0; index < input.length; index++) {

    const item = input[index];
    let x = item.rect?.left ?? 0;
    let y = item.rect?.top?? 0;
    let w = (item.rect?.right ?? 0) - x;
    let h = (item.rect?.bottom ?? 0) - y;
    let roll = item.rotation?.angle ?? 0;

    let mat4 = [
      1, 0, 0, 0,
      0, 1, 0, 0,
      0, 0, 1, 0,
      0, 0, 0, 1
    ]
    mat4 = combine(mat4, [
      Math.cos(roll), -Math.sin(roll), 0, 0,
      Math.sin(roll), Math.cos(roll), 0, 0,
      0, 0, 1, 0,
      0, 0, 0, 1
    ])
    mat4 = combine(mat4, [
      scale, 0, 0, 0,
      0, scale, 0, 0,
      0, 0, scale, 0,
      0, 0, 0, 1
    ])

    let tMat = tempRes[index]

    let pos0: Position = { x: (0) * tMat[0] + (0) * tMat[1] + tMat[3], y: (0) * tMat[4] + (0) * tMat[5] + tMat[7] }

    let pos0_: Position = { x: (-0.5 * w) * mat4[0] + (-0.5 * h) * mat4[1] + mat4[3], y: (-0.5 * w) * mat4[4] + (-0.5 * h) * mat4[5] + mat4[7] }
    mat4 = combine(mat4, [
      1, 0, 0, (pos0.x - xmin) * scale - 0.5 * w - pos0_.x,
      0, 1, 0, (pos0.y - ymin) * scale - 0.5 * h - pos0_.y,
      0, 0, 1, 0,
      0, 0, 0, 1
    ])
    res.push(mat4)
  }
  return res
}

export function mat4toImageItem(matrix: number[], width: number, height: number): imageGeneration.ImageItem {
  let scale: number = matrix[10]

  let mat4 = combine([
    1, 0, 0, vp2px(-0.5 * width),
    0, 1, 0, vp2px(-0.5 * height),
    0, 0, 1, 0,
    0, 0, 0, 1
  ], matrix)
  mat4 = combine(mat4, [
    1, 0, 0, vp2px(0.5 * width),
    0, 1, 0, vp2px(0.5 * height),
    0, 0, 1, 0,
    0, 0, 0, 1
  ])

  let pos: Position = { x: (0) * mat4[0] + (0) * mat4[1] + mat4[3], y: (0) * mat4[4] + (0) * mat4[5] + mat4[7] }
  mat4 = combine(mat4, [
    1, 0, 0, -pos.x,
    0, 1, 0, -pos.y,
    0, 0, 1, 0,
    0, 0, 0, 1
  ])
  mat4 = combine(mat4, [
    1 / scale, 0, 0, 0,
    0, 1 / scale, 0, 0,
    0, 0, 1 / scale, 0,
    0, 0, 0, 1
  ])
  let angle = 0;
  if (mat4[0] >= 0) {
    angle = Math.asin(mat4[4])
  } else if (mat4[0] < 0 && mat4[4] >= 0) {
    angle = Math.acos(mat4[0])
  } else {
    angle = -Math.acos(mat4[0])
  }
  let imageItem:  imageGeneration.ImageItem = {
    rect: {
      left: pos.x,
      right: pos.x + vp2px(width) * scale,
      top: pos.y,
      bottom: pos.y + vp2px(height) * scale
    },
    rotation: {
      centerX: 0,
      centerY: 0,
      angle: angle
    }
  };
  return imageItem;
}

function length(input: Vec2): number {
  return Math.sqrt(Math.pow(input.x, 2) + Math.pow(input.y, 2))
}

function vec4Multiple(v1: number[], v2: number[]): number[] {
  return [v1[0] * v2[0], v1[1] * v2[1], v1[2] * v2[2], v1[3] * v2[3]]
}

function vec4Add(v1: number[], v2: number[]): number[] {
  return [v1[0] + v2[0], v1[1] + v2[1], v1[2] + v2[2], v1[3] + v2[3]]
}

function vec4Sub(v1: number[], v2: number[]): number[] {
  return [v1[0] - v2[0], v1[1] - v2[1], v1[2] - v2[2], v1[3] - v2[3]]
}

function toMatrix(input: number[]): matrix4.Matrix4Transit {
  return matrix4.init(
    [
      input[0], input[4], input[8], input[12],
      input[1], input[5], input[9], input[13],
      input[2], input[6], input[10], input[14],
      input[3], input[7], input[11], input[15],
    ])
}

function combine(input0: number[], input1: number[]): number[] {
  return [
    input1[0] * input0[0] + input1[1] * input0[4] + input1[2] * input0[8]  + input1[3] * input0[12],
    input1[0] * input0[1] + input1[1] * input0[5] + input1[2] * input0[9]  + input1[3] * input0[13],
    input1[0] * input0[2] + input1[1] * input0[6] + input1[2] * input0[10] + input1[3] * input0[14],
    input1[0] * input0[3] + input1[1] * input0[7] + input1[2] * input0[11] + input1[3] * input0[15],

    input1[4] * input0[0] + input1[5] * input0[4] + input1[6] * input0[8]  + input1[7] * input0[12],
    input1[4] * input0[1] + input1[5] * input0[5] + input1[6] * input0[9]  + input1[7] * input0[13],
    input1[4] * input0[2] + input1[5] * input0[6] + input1[6] * input0[10] + input1[7] * input0[14],
    input1[4] * input0[3] + input1[5] * input0[7] + input1[6] * input0[11] + input1[7] * input0[15],

    input1[8] * input0[0] + input1[9] * input0[4] + input1[10] * input0[8]  + input1[11] * input0[12],
    input1[8] * input0[1] + input1[9] * input0[5] + input1[10] * input0[9]  + input1[11] * input0[13],
    input1[8] * input0[2] + input1[9] * input0[6] + input1[10] * input0[10] + input1[11] * input0[14],
    input1[8] * input0[3] + input1[9] * input0[7] + input1[10] * input0[11] + input1[11] * input0[15],

    input1[12] * input0[0] + input1[13] * input0[4] + input1[14] * input0[8]  + input1[15] * input0[12],
    input1[12] * input0[1] + input1[13] * input0[5] + input1[14] * input0[9]  + input1[15] * input0[13],
    input1[12] * input0[2] + input1[13] * input0[6] + input1[14] * input0[10] + input1[15] * input0[14],
    input1[12] * input0[3] + input1[13] * input0[7] + input1[14] * input0[11] + input1[15] * input0[15],
  ]
}

function mat4Inverse(m: number[]): number[] {
  let Coef00 = m[2 + 4 * 2] * m[3 + 4 * 3] - m[3 + 4 * 2] * m[2 + 4 * 3];
  let Coef02 = m[1 + 4 * 2] * m[3 + 4 * 3] - m[3 + 4 * 2] * m[1 + 4 * 3];
  let Coef03 = m[1 + 4 * 2] * m[2 + 4 * 3] - m[2 + 4 * 2] * m[1 + 4 * 3];

  let Coef04 = m[2 + 4 * 1] * m[3 + 4 * 3] - m[3 + 4 * 1] * m[2 + 4 * 3];
  let Coef06 = m[1 + 4 * 1] * m[3 + 4 * 3] - m[3 + 4 * 1] * m[1 + 4 * 3];
  let Coef07 = m[1 + 4 * 1] * m[2 + 4 * 3] - m[2 + 4 * 1] * m[1 + 4 * 3];

  let Coef08 = m[2 + 4 * 1] * m[3 + 4 * 2] - m[3 + 4 * 1] * m[2 + 4 * 2];
  let Coef10 = m[1 + 4 * 1] * m[3 + 4 * 2] - m[3 + 4 * 1] * m[1 + 4 * 2];
  let Coef11 = m[1 + 4 * 1] * m[2 + 4 * 2] - m[2 + 4 * 1] * m[1 + 4 * 2];

  let Coef12 = m[2 + 4 * 0] * m[3 + 4 * 3] - m[3 + 4 * 0] * m[2 + 4 * 3];
  let Coef14 = m[1 + 4 * 0] * m[3 + 4 * 3] - m[3 + 4 * 0] * m[1 + 4 * 3];
  let Coef15 = m[1 + 4 * 0] * m[2 + 4 * 3] - m[2 + 4 * 0] * m[1 + 4 * 3];

  let Coef16 = m[2 + 4 * 0] * m[3 + 4 * 2] - m[3 + 4 * 0] * m[2 + 4 * 2];
  let Coef18 = m[1 + 4 * 0] * m[3 + 4 * 2] - m[3 + 4 * 0] * m[1 + 4 * 2];
  let Coef19 = m[1 + 4 * 0] * m[2 + 4 * 2] - m[2 + 4 * 0] * m[1 + 4 * 2];

  let Coef20 = m[2 + 4 * 0] * m[3 + 4 * 1] - m[3 + 4 * 0] * m[2 + 4 * 1];
  let Coef22 = m[1 + 4 * 0] * m[3 + 4 * 1] - m[3 + 4 * 0] * m[1 + 4 * 1];
  let Coef23 = m[1 + 4 * 0] * m[2 + 4 * 1] - m[2 + 4 * 0] * m[1 + 4 * 1];

  let Fac0 = [Coef00, Coef00, Coef02, Coef03];
  let Fac1 = [Coef04, Coef04, Coef06, Coef07];
  let Fac2 = [Coef08, Coef08, Coef10, Coef11];
  let Fac3 = [Coef12, Coef12, Coef14, Coef15];
  let Fac4 = [Coef16, Coef16, Coef18, Coef19];
  let Fac5 = [Coef20, Coef20, Coef22, Coef23];

  let Vec0 = [m[1 + 4 * 0], m[0 + 4 * 0], m[0 + 4 * 0], m[0 + 4 * 0]];
  let Vec1 = [m[1 + 4 * 1], m[0 + 4 * 1], m[0 + 4 * 1], m[0 + 4 * 1]];
  let Vec2 = [m[1 + 4 * 2], m[0 + 4 * 2], m[0 + 4 * 2], m[0 + 4 * 2]];
  let Vec3 = [m[1 + 4 * 3], m[0 + 4 * 3], m[0 + 4 * 3], m[0 + 4 * 3]];

  let Inv0 = vec4Add(vec4Sub(vec4Multiple(Vec1, Fac0), vec4Multiple(Vec2, Fac1)), vec4Multiple(Vec3, Fac2));
  let Inv1 = vec4Add(vec4Sub(vec4Multiple(Vec0, Fac0), vec4Multiple(Vec2, Fac3)), vec4Multiple(Vec3, Fac4));
  let Inv2 = vec4Add(vec4Sub(vec4Multiple(Vec0, Fac1), vec4Multiple(Vec1, Fac3)), vec4Multiple(Vec3, Fac5));
  let Inv3 = vec4Add(vec4Sub(vec4Multiple(Vec0, Fac2), vec4Multiple(Vec1, Fac4)), vec4Multiple(Vec2, Fac5));

  let SignA = [+1, -1, +1, -1];
  let SignB = [-1, +1, -1, +1];
  let Inverse = [
    Inv0[0] * SignA[0], Inv1[0] * SignB[0], Inv2[0] * SignA[0], Inv3[0] * SignB[0],
    Inv0[1] * SignA[1], Inv1[1] * SignB[1], Inv2[1] * SignA[1], Inv3[1] * SignB[1],
    Inv0[2] * SignA[2], Inv1[2] * SignB[2], Inv2[2] * SignA[2], Inv3[2] * SignB[2],
    Inv0[3] * SignA[3], Inv1[3] * SignB[3], Inv2[3] * SignA[3], Inv3[3] * SignB[3]
  ]

  let Row0 = [Inverse[0 + 4 * 0], Inverse[1 + 4 * 0], Inverse[2 + 4 * 0], Inverse[3 + 4 * 0]];

  let Dot0 = [m[0] * Row0[0], m[0] * Row0[1], m[0] * Row0[2], m[0] * Row0[3]];
  let Dot1 = (Dot0[0] + Dot0[1]) + (Dot0[2] + Dot0[3]);

  let OneOverDeterminant = 1 / Dot1;

  return [
    OneOverDeterminant * Inverse[0],  OneOverDeterminant * Inverse[1],  OneOverDeterminant * Inverse[2],  OneOverDeterminant * Inverse[3],
    OneOverDeterminant * Inverse[4],  OneOverDeterminant * Inverse[5],  OneOverDeterminant * Inverse[6],  OneOverDeterminant * Inverse[7],
    OneOverDeterminant * Inverse[8],  OneOverDeterminant * Inverse[9],  OneOverDeterminant * Inverse[10], OneOverDeterminant * Inverse[11],
    OneOverDeterminant * Inverse[12], OneOverDeterminant * Inverse[13], OneOverDeterminant * Inverse[14], OneOverDeterminant * Inverse[15]
  ]
}

class delegate<T extends (...argArray: ESObject[]) => void>
{
  public constructor() {
  }

  public add(other: T)
  public add(other: delegate<T>)

  public add(other: delegate<T> | T)
  {
    if (other instanceof Function) {
      this.functions.push(other as T)
    } else if (other instanceof delegate) {
      for (let index = 0; index < other.functions.length; index++) {
        const element = other.functions[index];
        this.functions.push(element)
      }
    }
  }

  public invoke(...argArray: ESObject[])
  {
    for (let index = 0; index < this.functions.length; index++) {
      const element = this.functions[index];
      element(...argArray);
    }
  }
  functions: T[] = []
}

class ImageOperateGlobalThis{
  public static getInstance(): ImageOperateGlobalThis
  {
    return ImageOperateGlobalThis.instance
  }

  public getImageOperatorClickDelegate(): delegate<()=> void>
  {
    return this.imageOperatorClickDelegate
  }

  imageOperatorClickDelegate: delegate<()=> void> = new delegate<()=> void>()

  static instance: ImageOperateGlobalThis = new ImageOperateGlobalThis();
}

@ComponentV2
export struct ImageOperate {

  @Param @Require pixelMap: PixelMap | ImageContent;

  @Param @Require preTransform: number[] = [
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1
  ]
  @Param @Require  imageWidth: number | string = '100%';
  @Param @Require  imageAspectRito: number;

  @Local imageClick: boolean = false
  @Local to00: Position = { x:0, y: 0 }

  ImageW: number = 0
  ImageH: number = 0

  lockRotate: boolean = false;
  storeTouchPos: Position = { x:0, y: 0 }
  blockFatherTouch: boolean = false;
  @Local matrix: number[] = [
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1
  ]
  @Param setMatrixCallback: Function | undefined = undefined

  @Monitor('matrix')
  onMatrixChanged() {
    if (this.setMatrixCallback !== undefined) {
      this.setMatrixCallback(this.matrix)
    }
  }
  @Local storeMatrix: number[] =
    [
      1, 0, 0, 0,
      0, 1, 0, 0,
      0, 0, 1, 0,
      0, 0, 0, 1
    ]
  toWindowPos: Position = { x:0, y: 0 }
  traceId0: number = -1
  traceId1: number = -1
  store0Pos: Position = { x:0, y: 0 }
  store1Pos: Position = { x:0, y: 0 }

  touches: Map<number, Position> = new Map<number, Position>()

  aboutToAppear(): void {
    this.matrix = this.preTransform

    ImageOperateGlobalThis.getInstance().getImageOperatorClickDelegate().add(()=>{
      this.imageClick = false
    })
  }

  calcMatrix() {
    if (this.traceId0 == -1 && this.traceId1 == -1) {
      return;
    } else if (this.traceId0 == -1) {
      this.matrix = combine(this.storeMatrix, [
        1, 0, 0, vp2px(this.touches.get(this.traceId1)!.x - this.store1Pos.x),
        0, 1, 0, vp2px(this.touches.get(this.traceId1)!.y - this.store1Pos.y),
        0, 0, 1, 0,
        0, 0, 0, 1
      ])
    } else if (this.traceId1 == -1) {
      this.matrix = combine(this.storeMatrix, [
        1, 0, 0, vp2px(this.touches.get(this.traceId0)!.x - this.store0Pos.x),
        0, 1, 0, vp2px(this.touches.get(this.traceId0)!.y - this.store0Pos.y),
        0, 0, 1, 0,
        0, 0, 0, 1
      ])
    } else {
      let vec0: Vec2 = {x: this.store1Pos.x - this.store0Pos.x, y: this.store1Pos.y - this.store0Pos.y};
      let vec1: Vec2 = {x: this.touches.get(this.traceId1)!.x - this.touches.get(this.traceId0)!.x, y: this.touches.get(this.traceId1)!.y - this.touches.get(this.traceId0)!.y};

      let translate0: Vec2 = {x: this.to00.x - this.store0Pos.x, y: this.to00.y - this.store0Pos.y}
      let scaleX: number = length(vec1) / length(vec0)
      let scaleY: number = length(vec1) / length(vec0)
      let scaleZ: number = length(vec1) / length(vec0)
      let tempAngle0 = Math.atan(vec0.y / vec0.x) * 180 / PI + (vec0.x < 0 ? 180 : 0);
      let tempAngle1 = Math.atan(vec1.y / vec1.x) * 180 / PI + (vec1.x < 0 ? 180 : 0);

      let angle: number = tempAngle1 - tempAngle0;

      if (this.lockRotate) {
        scaleX = vec1.x / vec0.x
        scaleY = vec1.y / vec0.y

        scaleZ = Math.max(0.05 / this.storeMatrix[10], Math.min(scaleX, scaleY));

        scaleX = scaleZ
        scaleY = scaleZ
        angle = 0
      }


      let translate1: Vec2 = {x: this.touches.get(this.traceId0)!.x - this.to00.x, y: this.touches.get(this.traceId0)!.y - this.to00.y}

      this.matrix = combine(combine(combine(combine(this.storeMatrix, [
        1, 0, 0, vp2px(translate0.x),
        0, 1, 0, vp2px(translate0.y),
        0, 0, 1, 0,
        0, 0, 0, 1
      ]), [
        scaleX, 0, 0, 0,
        0, scaleY, 0, 0,
        0, 0, scaleZ, 0,
        0, 0, 0, 1
      ]), [
        Math.cos(angle / 180 * PI), -Math.sin(angle / 180 * PI), 0, 0,
        Math.sin(angle / 180 * PI), Math.cos(angle / 180 * PI), 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
      ]), [
        1, 0, 0, vp2px(translate1.x),
        0, 1, 0, vp2px(translate1.y),
        0, 0, 1, 0,
        0, 0, 0, 1
      ])
    }
  }

  handleTouchOpt(id: number, type: TouchType, pos: Position) {
    this.touches.set(id, pos)
    if (type == TouchType.Down) {
      if (this.traceId0 == -1) {
        this.traceId0 = id
        this.store0Pos = pos
        this.storeMatrix = this.matrix
        if (this.touches.has(this.traceId1)) {
          this.store1Pos = this.touches.get(this.traceId1)!
        }
      } else if (this.traceId1 == -1) {
        this.traceId1 = id
        this.store1Pos = pos
        this.storeMatrix = this.matrix
        if (this.touches.has(this.traceId0)) {
          this.store0Pos = this.touches.get(this.traceId0)!
        }
      }
      return
    } else if (type == TouchType.Move) {
      this.calcMatrix()
    } else if (type == TouchType.Up) {
      this.touches.delete(id)
      if (id == this.traceId0) {
        if (this.touches.size >=2) {
          for (let item of this.touches) {
            if (item[0] != this.traceId1) {
              this.traceId0 = item[0]
              this.storeMatrix = this.matrix
              this.store0Pos = this.touches.get(this.traceId0)!
              this.store1Pos = this.touches.get(this.traceId1)!
              return;
            }
          }
        } else {
          this.traceId0 = -1
          this.storeMatrix = this.matrix
          this.store1Pos = this.touches.get(this.traceId1)!
        }
      } else if (id == this.traceId1) {
        if (this.touches.size >=2) {
          for (let item of this.touches) {
            if (item[0] != this.traceId0) {
              this.traceId1 = item[0]
              this.storeMatrix = this.matrix
              this.store0Pos = this.touches.get(this.traceId0)!
              this.store1Pos = this.touches.get(this.traceId1)!
              return;
            }
          }
        } else {
          this.traceId1 = -1
          this.storeMatrix = this.matrix
          this.store0Pos = this.touches.get(this.traceId0)!
        }
      } else {
        return;
      }
    }
  }

  calcPointPos(input: Position): Position {
    let p = [vp2px(input.x), vp2px(input.y), 1, 1]
    let m0 = [
      1, 0, 0, -vp2px(this.to00.x),
      0, 1, 0, -vp2px(this.to00.y),
      0, 0, 1, 0,
      0, 0, 0, 1
    ]
    let m1 = this.storeMatrix
    let m2 = [
      1, 0, 0, vp2px(this.to00.x),
      0, 1, 0, vp2px(this.to00.y),
      0, 0, 1, 0,
      0, 0, 0, 1
    ]
    let m = combine(m0, m1)
    m = combine(m, m2)
    let pT = [
      p[0] * m[0] + p[1] * m[1] + p[2] * m[2] + p[3] * m[3],
      p[0] * m[4] + p[1] * m[5] + p[2] * m[6] + p[3] * m[7],
      p[0] * m[8] + p[1] * m[9] + p[2] * m[10] + p[3] * m[11],
      p[0] * m[12] + p[1] * m[13] + p[2] * m[14] + p[3] * m[15]
    ]
    return {x: px2vp(pT[0] / pT[3]) , y: px2vp(pT[1] / pT[3]) }
  }
  build() {
    Stack() {

      RelativeContainer() {
        Image(this.pixelMap)
          .syncLoad(true)
          .width('100%')
          .height('100%')
          .alignRules({
            left: {anchor: "__container__", align: HorizontalAlign.Start},
            top: {anchor: "__container__", align: VerticalAlign.Top}
          })
          .objectFit(ImageFit.Fill)
          .draggable(false)
          .syncLoad(true)
        if (this.imageClick) {
          Circle()
            .stroke(Color.Blue)
            .strokeWidth(1/this.matrix[10])
            .fillOpacity(0)
            .width(15/this.matrix[10])
            .height(15/this.matrix[10])
            .alignRules({
              middle: {anchor: "__container__", align: HorizontalAlign.Start},
              center: {anchor: "__container__", align: VerticalAlign.Top}
            })
            .onTouch((event: TouchEvent)=>{
              event.stopPropagation();
              if (event.touches.length == 1) {
                let center = this.calcPointPos(this.to00)
                if (event.touches[0].type == TouchType.Down) {
                  this.lockRotate = true
                  this.blockFatherTouch = true
                  this.storeTouchPos = {x: event.touches[0].windowX - this.toWindowPos.x, y: event.touches[0].windowY - this.toWindowPos.y}

                  this.handleTouchOpt(event.touches[0].id + 1, TouchType.Down, center)
                  this.handleTouchOpt(event.touches[0].id, TouchType.Down, this.storeTouchPos)
                } else if (event.touches[0].type == TouchType.Move) {
                  this.handleTouchOpt(event.touches[0].id, TouchType.Move, {x: event.touches[0].windowX - this.toWindowPos.x, y: event.touches[0].windowY - this.toWindowPos.y})

                } else {
                  this.handleTouchOpt(event.touches[0].id + 1, TouchType.Up, center)
                  this.handleTouchOpt(event.touches[0].id, TouchType.Up, {x: event.touches[0].windowX - this.toWindowPos.x, y: event.touches[0].windowY - this.toWindowPos.y})
                  this.lockRotate = false
                  this.blockFatherTouch = false
                }
              }
            })

          Circle()
            .stroke(Color.Blue)
            .strokeWidth(1/this.matrix[10])
            .fillOpacity(0)
            .width(15/this.matrix[10])
            .height(15/this.matrix[10])
            .alignRules({
              middle: {anchor: "__container__", align: HorizontalAlign.End},
              center: {anchor: "__container__", align: VerticalAlign.Top}
            })
            .onTouch((event: TouchEvent)=>{
              event.stopPropagation();
              if (event.touches.length == 1) {
                let center = this.calcPointPos(this.to00)
                if (event.touches[0].type == TouchType.Down) {
                  this.lockRotate = true
                  this.blockFatherTouch = true
                  this.storeTouchPos = {x: event.touches[0].windowX - this.toWindowPos.x, y: event.touches[0].windowY - this.toWindowPos.y}

                  this.handleTouchOpt(event.touches[0].id + 1, TouchType.Down, center)
                  this.handleTouchOpt(event.touches[0].id, TouchType.Down, this.storeTouchPos)
                } else if (event.touches[0].type == TouchType.Move) {
                  this.handleTouchOpt(event.touches[0].id, TouchType.Move, {x: event.touches[0].windowX - this.toWindowPos.x, y: event.touches[0].windowY - this.toWindowPos.y})

                } else {
                  this.handleTouchOpt(event.touches[0].id + 1, TouchType.Up, center)
                  this.handleTouchOpt(event.touches[0].id, TouchType.Up, {x: event.touches[0].windowX - this.toWindowPos.x, y: event.touches[0].windowY - this.toWindowPos.y})
                  this.lockRotate = false
                  this.blockFatherTouch = false
                }
              }
            })

          Circle()
            .stroke(Color.Blue)
            .strokeWidth(1/this.matrix[10])
            .fillOpacity(0)
            .width(15/this.matrix[10])
            .height(15/this.matrix[10])
            .alignRules({
              middle: {anchor: "__container__", align: HorizontalAlign.Start},
              center: {anchor: "__container__", align: VerticalAlign.Bottom}
            })
            .onTouch((event: TouchEvent)=>{
              event.stopPropagation();
              if (event.touches.length == 1) {
                let center = this.calcPointPos(this.to00)
                if (event.touches[0].type == TouchType.Down) {
                  this.lockRotate = true
                  this.blockFatherTouch = true
                  this.storeTouchPos = {x: event.touches[0].windowX - this.toWindowPos.x, y: event.touches[0].windowY - this.toWindowPos.y}

                  this.handleTouchOpt(event.touches[0].id + 1, TouchType.Down, center)
                  this.handleTouchOpt(event.touches[0].id, TouchType.Down, this.storeTouchPos)
                } else if (event.touches[0].type == TouchType.Move) {
                  this.handleTouchOpt(event.touches[0].id, TouchType.Move, {x: event.touches[0].windowX - this.toWindowPos.x, y: event.touches[0].windowY - this.toWindowPos.y})

                } else {
                  this.handleTouchOpt(event.touches[0].id + 1, TouchType.Up, center)
                  this.handleTouchOpt(event.touches[0].id, TouchType.Up, {x: event.touches[0].windowX - this.toWindowPos.x, y: event.touches[0].windowY - this.toWindowPos.y})
                  this.lockRotate = false
                  this.blockFatherTouch = false
                }
              }
            })

          Circle()
            .stroke(Color.Blue)
            .strokeWidth(1/this.matrix[10])
            .fillOpacity(0)
            .width(15/this.matrix[10])
            .height(15/this.matrix[10])
            .alignRules({
              middle: {anchor: "__container__", align: HorizontalAlign.End},
              center: {anchor: "__container__", align: VerticalAlign.Bottom}
            })
            .onTouch((event: TouchEvent)=>{
              event.stopPropagation();
              if (event.touches.length == 1) {
                let center = this.calcPointPos(this.to00)
                if (event.touches[0].type == TouchType.Down) {
                  this.lockRotate = true
                  this.blockFatherTouch = true
                  this.storeTouchPos = {x: event.touches[0].windowX - this.toWindowPos.x, y: event.touches[0].windowY - this.toWindowPos.y}

                  this.handleTouchOpt(event.touches[0].id + 1, TouchType.Down, center)
                  this.handleTouchOpt(event.touches[0].id, TouchType.Down, this.storeTouchPos)
                } else if (event.touches[0].type == TouchType.Move) {
                  this.handleTouchOpt(event.touches[0].id, TouchType.Move, {x: event.touches[0].windowX - this.toWindowPos.x, y: event.touches[0].windowY - this.toWindowPos.y})

                } else {
                  this.handleTouchOpt(event.touches[0].id + 1, TouchType.Up, center)
                  this.handleTouchOpt(event.touches[0].id, TouchType.Up, {x: event.touches[0].windowX - this.toWindowPos.x, y: event.touches[0].windowY - this.toWindowPos.y})
                  this.lockRotate = false
                  this.blockFatherTouch = false
                }
              }
            })
        }
      }
      .position({x:0, y: 0})
      .width(this.imageWidth)
      .aspectRatio(this.imageAspectRito)
      .transform3D(toMatrix(this.matrix))
      .onAreaChange((oldValue: Area, newValue: Area) => {
        let width = newValue.width as number
        let height = newValue.height as number
        this.to00 = {x: 0.5 * width, y: 0.5 * height}
        this.toWindowPos = { x: newValue.globalPosition.x as number ?? 0, y: newValue.globalPosition.y as number ?? 0 }
      })
      .onClick(()=>{
        ImageOperateGlobalThis.getInstance().getImageOperatorClickDelegate().invoke()
        this.imageClick = !this.imageClick
      })
      .onTouch((event: TouchEvent)=>{
        event.stopPropagation();
        if (this.blockFatherTouch) {
          return
        }
        for (let i = 0; i < event.touches.length; i++) {
          this.handleTouchOpt(event.touches[i].id, event.touches[i].type, {x: event.touches[i].displayX - this.toWindowPos.x, y: event.touches[i].displayY - this.toWindowPos.y})
        }
      })
      .hitTestBehavior(HitTestMode.BLOCK_HIERARCHY)
      .borderColor(Color.Red)
    }
  }
}
