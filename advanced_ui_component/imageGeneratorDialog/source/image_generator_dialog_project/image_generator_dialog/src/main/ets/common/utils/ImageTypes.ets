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

export interface Point2D {
  x: number;
  y: number;
}

export interface Size2D {
  width: number;
  height: number;
}

export interface Rect2D {
  left: number;
  top: number;
  right: number;
  bottom: number;
}

export interface Rotation2D {
  centerX: number;
  centerY: number;
  angle: number;
}

export interface TransformImageItemLike {
  rect?: Rect2D;
  rotation?: Rotation2D;
  zIndex?: number;
}

export interface PathPoint extends Point2D {
  pressure?: number;
  width?: number;
  timestamp?: number;
}

export interface PathBounds {
  bounds: Rect2D;
  length: number;
}

export interface AnchorSnapResult {
  value: number;
  snapped: boolean;
  anchor: number;
}

export interface RectSnapResult {
  rect: Rect2D;
  leftSnapped: boolean;
  rightSnapped: boolean;
  topSnapped: boolean;
  bottomSnapped: boolean;
}

export interface MatrixDecomposition2D {
  translateX: number;
  translateY: number;
  scaleX: number;
  scaleY: number;
  rotation: number;
  skewX: number;
}

export interface ImagePlane {
  width: number;
  height: number;
  data: Uint8Array;
}

export interface HistogramChannel {
  bins: number[];
  min: number;
  max: number;
  mean: number;
}

export interface HistogramResult {
  r: HistogramChannel;
  g: HistogramChannel;
  b: HistogramChannel;
  a: HistogramChannel;
}

export interface RgbaColor {
  r: number;
  g: number;
  b: number;
  a: number;
}

export interface HsvColor {
  h: number;
  s: number;
  v: number;
  a: number;
}

export interface ResizePlan {
  src: Size2D;
  target: Size2D;
  scaleX: number;
  scaleY: number;
  mode: 'contain' | 'cover' | 'stretch';
}

export interface CompressionPlan {
  quality: number;
  level: 'low' | 'medium' | 'high';
  expectedBytes: number;
}

export interface TimeMark {
  name: string;
  timestamp: number;
}

export interface PerfSummary {
  count: number;
  min: number;
  max: number;
  avg: number;
  p50: number;
  p90: number;
  p99: number;
}

export interface DebugLogRecord {
  level: 'debug' | 'info' | 'warn' | 'error';
  tag: string;
  message: string;
  timestamp: number;
}

export interface BenchmarkCase {
  name: string;
  loops: number;
  run: () => void;
}

export interface BenchmarkResult {
  name: string;
  loops: number;
  totalMs: number;
  avgMs: number;
}

export class ImageTypeGuards {
  static isFiniteNumber(input: number): boolean {
    return Number.isFinite(input);
  }

  static isPoint2D(input: Point2D | undefined): boolean {
    return !!input && Number.isFinite(input.x) && Number.isFinite(input.y);
  }

  static isSize2D(input: Size2D | undefined): boolean {
    return !!input && input.width >= 0 && input.height >= 0;
  }

  static isRect2D(input: Rect2D | undefined): boolean {
    return !!input && Number.isFinite(input.left) && Number.isFinite(input.top) &&
      Number.isFinite(input.right) && Number.isFinite(input.bottom);
  }

  static isImagePlane(input: ImagePlane | undefined): boolean {
    return !!input && input.width > 0 && input.height > 0 &&
      input.data instanceof Uint8Array && input.data.length === input.width * input.height * 4;
  }
}
