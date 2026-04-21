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

import { PathBounds, PathPoint, Point2D, Rect2D } from './ImageTypes';
import { ImageGeometryUtils } from './ImageGeometryUtils';

export interface MaskGrid {
  width: number;
  height: number;
  data: Uint8Array;
}

export interface RunLengthPair {
  value: number;
  count: number;
}

export class ImageMaskPathUtils {
  static readonly DEFAULT_EPSILON: number = 1e-3;

  private static clonePoint(point: PathPoint): PathPoint {
    return {
      x: point.x,
      y: point.y,
      pressure: point.pressure,
      width: point.width,
      timestamp: point.timestamp
    };
  }

  static clonePath(path: PathPoint[]): PathPoint[] {
    let out: PathPoint[] = [];
    for (let i = 0; i < path.length; i++) {
      out.push({
        x: path[i].x,
        y: path[i].y,
        pressure: path[i].pressure,
        width: path[i].width,
        timestamp: path[i].timestamp
      });
    }
    return out;
  }

  static sanitizePath(path: PathPoint[]): PathPoint[] {
    let out: PathPoint[] = [];
    for (let i = 0; i < path.length; i++) {
      let p = path[i];
      if (Number.isFinite(p.x) && Number.isFinite(p.y)) {
        out.push({
          x: p.x,
          y: p.y,
          pressure: p.pressure,
          width: p.width,
          timestamp: p.timestamp
        });
      }
    }
    return out;
  }

  static toPoints(path: PathPoint[]): Point2D[] {
    let out: Point2D[] = [];
    for (let i = 0; i < path.length; i++) {
      out.push({ x: path[i].x, y: path[i].y });
    }
    return out;
  }

  static fromPoints(points: Point2D[]): PathPoint[] {
    let out: PathPoint[] = [];
    for (let i = 0; i < points.length; i++) {
      out.push({ x: points[i].x, y: points[i].y });
    }
    return out;
  }

  static getBoundsAndLength(path: PathPoint[]): PathBounds {
    if (path.length === 0) {
      return {
        bounds: { left: 0, top: 0, right: 0, bottom: 0 },
        length: 0
      };
    }

    let bounds: Rect2D = {
      left: path[0].x,
      top: path[0].y,
      right: path[0].x,
      bottom: path[0].y
    };

    let length = 0;
    for (let i = 1; i < path.length; i++) {
      bounds.left = Math.min(bounds.left, path[i].x);
      bounds.top = Math.min(bounds.top, path[i].y);
      bounds.right = Math.max(bounds.right, path[i].x);
      bounds.bottom = Math.max(bounds.bottom, path[i].y);
      length += ImageGeometryUtils.distance(path[i - 1], path[i]);
    }

    return {
      bounds,
      length
    };
  }

  static closePathIfNear(path: PathPoint[], threshold: number = 4): PathPoint[] {
    if (path.length < 3) {
      return ImageMaskPathUtils.clonePath(path);
    }
    let first = path[0];
    let last = path[path.length - 1];
    if (ImageGeometryUtils.distance(first, last) <= threshold) {
      let out = ImageMaskPathUtils.clonePath(path);
      out[out.length - 1] = {
        x: first.x,
        y: first.y,
        pressure: first.pressure,
        width: first.width,
        timestamp: first.timestamp
      };
      return out;
    }
    return ImageMaskPathUtils.clonePath(path);
  }

  static removeDuplicatePoints(path: PathPoint[], epsilon: number = ImageMaskPathUtils.DEFAULT_EPSILON): PathPoint[] {
    if (path.length <= 1) {
      return ImageMaskPathUtils.clonePath(path);
    }

    let out: PathPoint[] = [path[0]];
    for (let i = 1; i < path.length; i++) {
      if (ImageGeometryUtils.distance(path[i], out[out.length - 1]) > epsilon) {
        out.push(path[i]);
      }
    }
    return ImageMaskPathUtils.clonePath(out);
  }

  static simplifyRadialDistance(path: PathPoint[], tolerance: number): PathPoint[] {
    if (path.length <= 2) {
      return ImageMaskPathUtils.clonePath(path);
    }

    let sqTolerance = tolerance * tolerance;
    let prev = path[0];
    let out: PathPoint[] = [prev];

    for (let i = 1; i < path.length; i++) {
      let p = path[i];
      let dx = p.x - prev.x;
      let dy = p.y - prev.y;
      if (dx * dx + dy * dy > sqTolerance) {
        out.push(p);
        prev = p;
      }
    }

    if (out[out.length - 1] !== path[path.length - 1]) {
      out.push(path[path.length - 1]);
    }

    return ImageMaskPathUtils.clonePath(out);
  }

  private static sqDistToSegment(point: PathPoint, a: PathPoint, b: PathPoint): number {
    let projected = ImageGeometryUtils.projectPointToSegment(point, a, b);
    let dx = point.x - projected.x;
    let dy = point.y - projected.y;
    return dx * dx + dy * dy;
  }

  static simplifyDouglasPeucker(path: PathPoint[], tolerance: number): PathPoint[] {
    if (path.length <= 2) {
      return ImageMaskPathUtils.clonePath(path);
    }

    let sqTolerance = tolerance * tolerance;
    let markers: number[] = new Array(path.length).fill(0);
    markers[0] = 1;
    markers[path.length - 1] = 1;

    let stack: number[] = [0, path.length - 1];
    while (stack.length > 0) {
      let end = stack.pop()!;
      let start = stack.pop()!;

      let maxSqDist = 0;
      let index = -1;

      for (let i = start + 1; i < end; i++) {
        let sqDist = ImageMaskPathUtils.sqDistToSegment(path[i], path[start], path[end]);
        if (sqDist > maxSqDist) {
          index = i;
          maxSqDist = sqDist;
        }
      }

      if (index !== -1 && maxSqDist > sqTolerance) {
        markers[index] = 1;
        stack.push(start, index);
        stack.push(index, end);
      }
    }

    let out: PathPoint[] = [];
    for (let i = 0; i < path.length; i++) {
      if (markers[i] === 1) {
        out.push(path[i]);
      }
    }
    return ImageMaskPathUtils.clonePath(out);
  }

  static simplifyPath(path: PathPoint[], tolerance: number): PathPoint[] {
    if (path.length <= 2) {
      return ImageMaskPathUtils.clonePath(path);
    }

    let cleaned = ImageMaskPathUtils.removeDuplicatePoints(path, tolerance * 0.1);
    let radial = ImageMaskPathUtils.simplifyRadialDistance(cleaned, tolerance);
    return ImageMaskPathUtils.simplifyDouglasPeucker(radial, tolerance);
  }

  static smoothMovingAverage(path: PathPoint[], radius: number = 2): PathPoint[] {
    if (path.length <= 2 || radius <= 0) {
      return ImageMaskPathUtils.clonePath(path);
    }

    let out: PathPoint[] = [];
    for (let i = 0; i < path.length; i++) {
      let start = Math.max(0, i - radius);
      let end = Math.min(path.length - 1, i + radius);
      let count = 0;
      let sumX = 0;
      let sumY = 0;
      let sumPressure = 0;
      let pressureCount = 0;

      for (let j = start; j <= end; j++) {
        count++;
        sumX += path[j].x;
        sumY += path[j].y;
        if (path[j].pressure !== undefined) {
          sumPressure += path[j].pressure!;
          pressureCount++;
        }
      }

      out.push({
        x: sumX / count,
        y: sumY / count,
        pressure: pressureCount > 0 ? sumPressure / pressureCount : path[i].pressure,
        width: path[i].width,
        timestamp: path[i].timestamp
      });
    }

    return out;
  }

  static smoothChaikin(path: PathPoint[], iterations: number = 1): PathPoint[] {
    if (path.length < 3 || iterations <= 0) {
      return ImageMaskPathUtils.clonePath(path);
    }

    let working = ImageMaskPathUtils.clonePath(path);

    for (let n = 0; n < iterations; n++) {
      let out: PathPoint[] = [working[0]];
      for (let i = 0; i < working.length - 1; i++) {
        let p0 = working[i];
        let p1 = working[i + 1];

        let q: PathPoint = {
          x: 0.75 * p0.x + 0.25 * p1.x,
          y: 0.75 * p0.y + 0.25 * p1.y,
          pressure: p0.pressure !== undefined && p1.pressure !== undefined
            ? 0.75 * p0.pressure + 0.25 * p1.pressure
            : p0.pressure,
          width: p0.width,
          timestamp: p0.timestamp
        };

        let r: PathPoint = {
          x: 0.25 * p0.x + 0.75 * p1.x,
          y: 0.25 * p0.y + 0.75 * p1.y,
          pressure: p0.pressure !== undefined && p1.pressure !== undefined
            ? 0.25 * p0.pressure + 0.75 * p1.pressure
            : p1.pressure,
          width: p1.width,
          timestamp: p1.timestamp
        };

        out.push(q);
        out.push(r);
      }
      out.push(working[working.length - 1]);
      working = out;
    }

    return working;
  }

  private static catmullRomInterpolate(p0: PathPoint, p1: PathPoint, p2: PathPoint, p3: PathPoint, t: number): PathPoint {
    let t2 = t * t;
    let t3 = t2 * t;

    let x = 0.5 * (
      2 * p1.x +
      (-p0.x + p2.x) * t +
      (2 * p0.x - 5 * p1.x + 4 * p2.x - p3.x) * t2 +
      (-p0.x + 3 * p1.x - 3 * p2.x + p3.x) * t3
    );

    let y = 0.5 * (
      2 * p1.y +
      (-p0.y + p2.y) * t +
      (2 * p0.y - 5 * p1.y + 4 * p2.y - p3.y) * t2 +
      (-p0.y + 3 * p1.y - 3 * p2.y + p3.y) * t3
    );

    let pressure = p1.pressure;
    if (p0.pressure !== undefined && p1.pressure !== undefined && p2.pressure !== undefined && p3.pressure !== undefined) {
      pressure = 0.5 * (
        2 * p1.pressure +
        (-p0.pressure + p2.pressure) * t +
        (2 * p0.pressure - 5 * p1.pressure + 4 * p2.pressure - p3.pressure) * t2 +
        (-p0.pressure + 3 * p1.pressure - 3 * p2.pressure + p3.pressure) * t3
      );
    }

    return {
      x,
      y,
      pressure,
      width: p1.width,
      timestamp: p1.timestamp
    };
  }

  static smoothCatmullRom(path: PathPoint[], samplesPerSegment: number = 8): PathPoint[] {
    if (path.length < 4 || samplesPerSegment < 1) {
      return ImageMaskPathUtils.clonePath(path);
    }

    let out: PathPoint[] = [];
    for (let i = 0; i < path.length - 1; i++) {
      let p0 = path[Math.max(0, i - 1)];
      let p1 = path[i];
      let p2 = path[i + 1];
      let p3 = path[Math.min(path.length - 1, i + 2)];

      if (i === 0) {
        out.push(ImageMaskPathUtils.clonePoint(p1));
      }

      for (let j = 1; j <= samplesPerSegment; j++) {
        let t = j / samplesPerSegment;
        out.push(ImageMaskPathUtils.catmullRomInterpolate(p0, p1, p2, p3, t));
      }
    }

    return out;
  }

  static cumulativeLengths(path: PathPoint[]): number[] {
    let sums: number[] = [];
    if (path.length === 0) {
      return sums;
    }
    sums.push(0);
    for (let i = 1; i < path.length; i++) {
      let prev = sums[sums.length - 1];
      sums.push(prev + ImageGeometryUtils.distance(path[i - 1], path[i]));
    }
    return sums;
  }

  private static interpolatePoint(a: PathPoint, b: PathPoint, t: number): PathPoint {
    let pressure: number | undefined = undefined;
    if (a.pressure !== undefined && b.pressure !== undefined) {
      pressure = ImageGeometryUtils.lerp(a.pressure, b.pressure, t);
    }

    let width: number | undefined = undefined;
    if (a.width !== undefined && b.width !== undefined) {
      width = ImageGeometryUtils.lerp(a.width, b.width, t);
    }

    let timestamp: number | undefined = undefined;
    if (a.timestamp !== undefined && b.timestamp !== undefined) {
      timestamp = Math.round(ImageGeometryUtils.lerp(a.timestamp, b.timestamp, t));
    }

    return {
      x: ImageGeometryUtils.lerp(a.x, b.x, t),
      y: ImageGeometryUtils.lerp(a.y, b.y, t),
      pressure,
      width,
      timestamp
    };
  }

  static resampleBySpacing(path: PathPoint[], spacing: number): PathPoint[] {
    if (path.length < 2 || spacing <= 0) {
      return ImageMaskPathUtils.clonePath(path);
    }

    let sums = ImageMaskPathUtils.cumulativeLengths(path);
    let total = sums[sums.length - 1];
    if (total <= spacing) {
      return ImageMaskPathUtils.clonePath(path);
    }

    let out: PathPoint[] = [ImageMaskPathUtils.clonePoint(path[0])];
    let distanceCursor = spacing;
    let segmentIndex = 1;

    while (distanceCursor < total && segmentIndex < path.length) {
      while (segmentIndex < path.length && sums[segmentIndex] < distanceCursor) {
        segmentIndex++;
      }
      if (segmentIndex >= path.length) {
        break;
      }

      let leftDist = sums[segmentIndex - 1];
      let rightDist = sums[segmentIndex];
      let segmentLength = rightDist - leftDist;
      let t = segmentLength <= 1e-9 ? 0 : (distanceCursor - leftDist) / segmentLength;
      out.push(ImageMaskPathUtils.interpolatePoint(path[segmentIndex - 1], path[segmentIndex], t));
      distanceCursor += spacing;
    }

    out.push(ImageMaskPathUtils.clonePoint(path[path.length - 1]));
    return out;
  }

  static resampleByCount(path: PathPoint[], count: number): PathPoint[] {
    if (count <= 1 || path.length <= 1) {
      return path.length > 0 ? [ImageMaskPathUtils.clonePoint(path[0])] : [];
    }

    let info = ImageMaskPathUtils.getBoundsAndLength(path);
    if (info.length <= ImageMaskPathUtils.DEFAULT_EPSILON) {
      let ret: PathPoint[] = [];
      for (let i = 0; i < count; i++) {
        ret.push(ImageMaskPathUtils.clonePoint(path[0]));
      }
      return ret;
    }

    let spacing = info.length / (count - 1);
    let resampled = ImageMaskPathUtils.resampleBySpacing(path, spacing);

    if (resampled.length > count) {
      return resampled.slice(0, count);
    }

    while (resampled.length < count) {
      resampled.push(ImageMaskPathUtils.clonePoint(resampled[resampled.length - 1]));
    }
    return resampled;
  }

  static normalizePressure(path: PathPoint[], min: number = 0, max: number = 1): PathPoint[] {
    if (path.length === 0) {
      return [];
    }

    let pMin = Number.MAX_VALUE;
    let pMax = -Number.MAX_VALUE;

    for (let i = 0; i < path.length; i++) {
      if (path[i].pressure === undefined) {
        continue;
      }
      pMin = Math.min(pMin, path[i].pressure!);
      pMax = Math.max(pMax, path[i].pressure!);
    }

    if (!Number.isFinite(pMin) || !Number.isFinite(pMax) || Math.abs(pMax - pMin) < 1e-6) {
      return ImageMaskPathUtils.clonePath(path);
    }

    let out: PathPoint[] = [];
    for (let i = 0; i < path.length; i++) {
      if (path[i].pressure === undefined) {
        out.push(ImageMaskPathUtils.clonePoint(path[i]));
        continue;
      }
      let normalized = (path[i].pressure! - pMin) / (pMax - pMin);
      let updated = ImageMaskPathUtils.clonePoint(path[i]);
      updated.pressure = min + normalized * (max - min);
      out.push(updated);
    }
    return out;
  }

  static applyPressureCurve(path: PathPoint[], power: number = 1.5): PathPoint[] {
    let out: PathPoint[] = [];
    for (let i = 0; i < path.length; i++) {
      if (path[i].pressure === undefined) {
        out.push(ImageMaskPathUtils.clonePoint(path[i]));
      } else {
        let normalized = ImageGeometryUtils.saturate(path[i].pressure!);
        let updated = ImageMaskPathUtils.clonePoint(path[i]);
        updated.pressure = Math.pow(normalized, power);
        out.push(updated);
      }
    }
    return out;
  }

  static mergeNearbyPoints(path: PathPoint[], distanceThreshold: number): PathPoint[] {
    if (path.length < 2) {
      return ImageMaskPathUtils.clonePath(path);
    }

    let out: PathPoint[] = [ImageMaskPathUtils.clonePoint(path[0])];
    for (let i = 1; i < path.length; i++) {
      let prev = out[out.length - 1];
      if (ImageGeometryUtils.distance(prev, path[i]) <= distanceThreshold) {
        prev.x = (prev.x + path[i].x) * 0.5;
        prev.y = (prev.y + path[i].y) * 0.5;
        if (prev.pressure !== undefined && path[i].pressure !== undefined) {
          prev.pressure = (prev.pressure + path[i].pressure!) * 0.5;
        }
      } else {
        out.push(ImageMaskPathUtils.clonePoint(path[i]));
      }
    }

    return out;
  }

  static splitByGap(path: PathPoint[], maxGap: number): PathPoint[][] {
    if (path.length === 0) {
      return [];
    }

    let groups: PathPoint[][] = [];
    let current: PathPoint[] = [ImageMaskPathUtils.clonePoint(path[0])];

    for (let i = 1; i < path.length; i++) {
      if (ImageGeometryUtils.distance(path[i - 1], path[i]) > maxGap) {
        groups.push(current);
        current = [];
      }
      current.push(ImageMaskPathUtils.clonePoint(path[i]));
    }

    if (current.length > 0) {
      groups.push(current);
    }
    return groups;
  }

  static interpolateAt(path: PathPoint[], t: number): PathPoint | undefined {
    if (path.length === 0) {
      return undefined;
    }

    if (path.length === 1) {
      return ImageMaskPathUtils.clonePoint(path[0]);
    }

    let clampedT = ImageGeometryUtils.clamp(t, 0, 1);
    let sums = ImageMaskPathUtils.cumulativeLengths(path);
    let total = sums[sums.length - 1];
    let target = total * clampedT;

    for (let i = 1; i < sums.length; i++) {
      if (sums[i] >= target) {
        let segmentLength = sums[i] - sums[i - 1];
        let localT = segmentLength <= 1e-9 ? 0 : (target - sums[i - 1]) / segmentLength;
        return ImageMaskPathUtils.interpolatePoint(path[i - 1], path[i], localT);
      }
    }

    return ImageMaskPathUtils.clonePoint(path[path.length - 1]);
  }

  static tangentAt(path: PathPoint[], t: number): Point2D {
    if (path.length < 2) {
      return { x: 1, y: 0 };
    }

    let delta = 0.01;
    let prev = ImageMaskPathUtils.interpolateAt(path, Math.max(0, t - delta))!;
    let next = ImageMaskPathUtils.interpolateAt(path, Math.min(1, t + delta))!;
    return ImageGeometryUtils.normalize2({ x: next.x - prev.x, y: next.y - prev.y });
  }

  static calculateNormals(path: PathPoint[], closed: boolean = false): Point2D[] {
    if (path.length === 0) {
      return [];
    }

    let normals: Point2D[] = [];
    for (let i = 0; i < path.length; i++) {
      let prev = i === 0 ? (closed ? path[path.length - 1] : path[0]) : path[i - 1];
      let next = i === path.length - 1 ? (closed ? path[0] : path[path.length - 1]) : path[i + 1];

      let tangent = ImageGeometryUtils.normalize2({ x: next.x - prev.x, y: next.y - prev.y });
      normals.push({ x: -tangent.y, y: tangent.x });
    }

    return normals;
  }

  static offsetPolyline(path: PathPoint[], offset: number, closed: boolean = false): PathPoint[] {
    if (path.length === 0) {
      return [];
    }

    let normals = ImageMaskPathUtils.calculateNormals(path, closed);
    let out: PathPoint[] = [];

    for (let i = 0; i < path.length; i++) {
      out.push({
        x: path[i].x + normals[i].x * offset,
        y: path[i].y + normals[i].y * offset,
        pressure: path[i].pressure,
        width: path[i].width,
        timestamp: path[i].timestamp
      });
    }

    return out;
  }

  static buildStrokePolygon(path: PathPoint[], baseWidth: number): Point2D[] {
    if (path.length < 2 || baseWidth <= 0) {
      return ImageMaskPathUtils.toPoints(path);
    }

    let normals = ImageMaskPathUtils.calculateNormals(path, false);
    let left: Point2D[] = [];
    let right: Point2D[] = [];

    for (let i = 0; i < path.length; i++) {
      let pressure = path[i].pressure !== undefined ? path[i].pressure! : 1;
      let width = path[i].width !== undefined ? path[i].width! : baseWidth;
      let half = width * pressure * 0.5;

      left.push({
        x: path[i].x + normals[i].x * half,
        y: path[i].y + normals[i].y * half
      });

      right.push({
        x: path[i].x - normals[i].x * half,
        y: path[i].y - normals[i].y * half
      });
    }

    right.reverse();
    return left.concat(right);
  }

  static pointInStroke(point: Point2D, path: PathPoint[], width: number): boolean {
    if (path.length < 2) {
      return false;
    }

    let radius = width * 0.5;
    for (let i = 1; i < path.length; i++) {
      if (ImageGeometryUtils.distancePointToSegment(point, path[i - 1], path[i]) <= radius) {
        return true;
      }
    }
    return false;
  }

  static rasterizePolygon(polygon: Point2D[], width: number, height: number): MaskGrid {
    let data = new Uint8Array(width * height);
    if (polygon.length < 3) {
      return { width, height, data };
    }

    for (let y = 0; y < height; y++) {
      for (let x = 0; x < width; x++) {
        let inside = ImageGeometryUtils.isPointInPolygon({ x: x + 0.5, y: y + 0.5 }, polygon);
        if (inside) {
          data[y * width + x] = 255;
        }
      }
    }

    return { width, height, data };
  }

  static rasterizeStroke(path: PathPoint[], width: number, maskWidth: number, maskHeight: number): MaskGrid {
    let data = new Uint8Array(maskWidth * maskHeight);

    for (let y = 0; y < maskHeight; y++) {
      for (let x = 0; x < maskWidth; x++) {
        if (ImageMaskPathUtils.pointInStroke({ x: x + 0.5, y: y + 0.5 }, path, width)) {
          data[y * maskWidth + x] = 255;
        }
      }
    }

    return {
      width: maskWidth,
      height: maskHeight,
      data
    };
  }

  static dilateMask(mask: MaskGrid, radius: number): MaskGrid {
    if (radius <= 0) {
      return {
        width: mask.width,
        height: mask.height,
        data: new Uint8Array(mask.data)
      };
    }

    let out = new Uint8Array(mask.width * mask.height);
    let rr = radius * radius;

    for (let y = 0; y < mask.height; y++) {
      for (let x = 0; x < mask.width; x++) {
        let filled = false;
        for (let dy = -radius; dy <= radius && !filled; dy++) {
          for (let dx = -radius; dx <= radius; dx++) {
            if (dx * dx + dy * dy > rr) {
              continue;
            }
            let nx = x + dx;
            let ny = y + dy;
            if (nx < 0 || ny < 0 || nx >= mask.width || ny >= mask.height) {
              continue;
            }
            if (mask.data[ny * mask.width + nx] > 0) {
              filled = true;
              break;
            }
          }
        }
        out[y * mask.width + x] = filled ? 255 : 0;
      }
    }

    return {
      width: mask.width,
      height: mask.height,
      data: out
    };
  }

  static erodeMask(mask: MaskGrid, radius: number): MaskGrid {
    if (radius <= 0) {
      return {
        width: mask.width,
        height: mask.height,
        data: new Uint8Array(mask.data)
      };
    }

    let out = new Uint8Array(mask.width * mask.height);
    let rr = radius * radius;

    for (let y = 0; y < mask.height; y++) {
      for (let x = 0; x < mask.width; x++) {
        let keep = true;
        for (let dy = -radius; dy <= radius && keep; dy++) {
          for (let dx = -radius; dx <= radius; dx++) {
            if (dx * dx + dy * dy > rr) {
              continue;
            }
            let nx = x + dx;
            let ny = y + dy;
            if (nx < 0 || ny < 0 || nx >= mask.width || ny >= mask.height) {
              keep = false;
              break;
            }
            if (mask.data[ny * mask.width + nx] === 0) {
              keep = false;
              break;
            }
          }
        }
        out[y * mask.width + x] = keep ? 255 : 0;
      }
    }

    return {
      width: mask.width,
      height: mask.height,
      data: out
    };
  }

  static blurMask(mask: MaskGrid, radius: number): MaskGrid {
    if (radius <= 0) {
      return {
        width: mask.width,
        height: mask.height,
        data: new Uint8Array(mask.data)
      };
    }

    let out = new Uint8Array(mask.width * mask.height);
    let kernelSize = radius * 2 + 1;
    let area = kernelSize * kernelSize;

    for (let y = 0; y < mask.height; y++) {
      for (let x = 0; x < mask.width; x++) {
        let sum = 0;
        for (let dy = -radius; dy <= radius; dy++) {
          for (let dx = -radius; dx <= radius; dx++) {
            let nx = ImageGeometryUtils.clamp(x + dx, 0, mask.width - 1);
            let ny = ImageGeometryUtils.clamp(y + dy, 0, mask.height - 1);
            sum += mask.data[ny * mask.width + nx];
          }
        }
        out[y * mask.width + x] = Math.round(sum / area);
      }
    }

    return {
      width: mask.width,
      height: mask.height,
      data: out
    };
  }

  static maskToRle(mask: MaskGrid): RunLengthPair[] {
    let out: RunLengthPair[] = [];
    if (mask.data.length === 0) {
      return out;
    }

    let currentValue = mask.data[0];
    let count = 1;

    for (let i = 1; i < mask.data.length; i++) {
      let val = mask.data[i];
      if (val === currentValue) {
        count++;
      } else {
        out.push({ value: currentValue, count });
        currentValue = val;
        count = 1;
      }
    }

    out.push({ value: currentValue, count });
    return out;
  }

  static rleToMask(width: number, height: number, rle: RunLengthPair[]): MaskGrid {
    let total = width * height;
    let data = new Uint8Array(total);
    let cursor = 0;

    for (let i = 0; i < rle.length && cursor < total; i++) {
      let value = ImageGeometryUtils.clamp(rle[i].value, 0, 255);
      let count = Math.max(0, Math.floor(rle[i].count));
      for (let j = 0; j < count && cursor < total; j++) {
        data[cursor++] = value;
      }
    }

    return {
      width,
      height,
      data
    };
  }

  static mergeMasks(maskA: MaskGrid, maskB: MaskGrid): MaskGrid {
    let width = Math.min(maskA.width, maskB.width);
    let height = Math.min(maskA.height, maskB.height);
    let data = new Uint8Array(width * height);

    for (let y = 0; y < height; y++) {
      for (let x = 0; x < width; x++) {
        let idxA = y * maskA.width + x;
        let idxB = y * maskB.width + x;
        let idxOut = y * width + x;
        data[idxOut] = Math.max(maskA.data[idxA], maskB.data[idxB]);
      }
    }

    return { width, height, data };
  }

  static subtractMasks(baseMask: MaskGrid, cutMask: MaskGrid): MaskGrid {
    let width = Math.min(baseMask.width, cutMask.width);
    let height = Math.min(baseMask.height, cutMask.height);
    let data = new Uint8Array(width * height);

    for (let y = 0; y < height; y++) {
      for (let x = 0; x < width; x++) {
        let idxA = y * baseMask.width + x;
        let idxB = y * cutMask.width + x;
        let idxOut = y * width + x;
        data[idxOut] = cutMask.data[idxB] > 0 ? 0 : baseMask.data[idxA];
      }
    }

    return { width, height, data };
  }

  static invertMask(mask: MaskGrid): MaskGrid {
    let data = new Uint8Array(mask.width * mask.height);
    for (let i = 0; i < data.length; i++) {
      data[i] = 255 - mask.data[i];
    }
    return {
      width: mask.width,
      height: mask.height,
      data
    };
  }

  static thresholdMask(mask: MaskGrid, threshold: number): MaskGrid {
    let data = new Uint8Array(mask.width * mask.height);
    for (let i = 0; i < data.length; i++) {
      data[i] = mask.data[i] >= threshold ? 255 : 0;
    }
    return {
      width: mask.width,
      height: mask.height,
      data
    };
  }

  static maskBounds(mask: MaskGrid, threshold: number = 1): Rect2D | undefined {
    let found = false;
    let left = mask.width;
    let top = mask.height;
    let right = -1;
    let bottom = -1;

    for (let y = 0; y < mask.height; y++) {
      for (let x = 0; x < mask.width; x++) {
        let value = mask.data[y * mask.width + x];
        if (value >= threshold) {
          found = true;
          left = Math.min(left, x);
          top = Math.min(top, y);
          right = Math.max(right, x);
          bottom = Math.max(bottom, y);
        }
      }
    }

    if (!found) {
      return undefined;
    }

    return {
      left,
      top,
      right: right + 1,
      bottom: bottom + 1
    };
  }

  static toSvgPath(path: PathPoint[]): string {
    if (path.length === 0) {
      return '';
    }

    let parts: string[] = [`M ${path[0].x} ${path[0].y}`];
    for (let i = 1; i < path.length; i++) {
      parts.push(`L ${path[i].x} ${path[i].y}`);
    }
    return parts.join(' ');
  }
}
