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

import {
  BenchmarkCase,
  BenchmarkResult,
  DebugLogRecord,
  ImagePlane,
  PerfSummary,
  Point2D,
  Rect2D,
  TimeMark
} from './ImageTypes';
import { ImageGeometryUtils } from './ImageGeometryUtils';
import { ImageProcessUtils } from './ImageProcessUtils';

interface FromTo {
  from: string;
  to: string;
  durationMs: number;
}

export class PerfStopwatch {
  private startTime: number = 0;
  private marks: TimeMark[] = [];

  start(): void {
    this.startTime = Date.now();
    this.marks = [{ name: 'start', timestamp: this.startTime }];
  }

  mark(name: string): number {
    let now = Date.now();
    this.marks.push({ name, timestamp: now });
    return now - this.startTime;
  }

  elapsedMs(): number {
    if (this.startTime <= 0) {
      return 0;
    }
    return Date.now() - this.startTime;
  }

  reset(): void {
    this.startTime = 0;
    this.marks = [];
  }

  timeline(): Array<FromTo> {
    let out: Array<FromTo> = [];
    if (this.marks.length < 2) {
      return out;
    }

    for (let i = 1; i < this.marks.length; i++) {
      out.push({
        from: this.marks[i - 1].name,
        to: this.marks[i].name,
        durationMs: this.marks[i].timestamp - this.marks[i - 1].timestamp
      });
    }

    return out;
  }
}

export class PerfWindowCounter {
  private values: number[] = [];
  private capacity: number;

  constructor(capacity: number = 120) {
    this.capacity = Math.max(4, Math.floor(capacity));
  }

  push(value: number): void {
    if (!Number.isFinite(value)) {
      return;
    }
    this.values.push(value);
    if (this.values.length > this.capacity) {
      this.values.shift();
    }
  }

  clear(): void {
    this.values = [];
  }

  size(): number {
    return this.values.length;
  }

  summary(): PerfSummary {
    if (this.values.length === 0) {
      return {
        count: 0,
        min: 0,
        max: 0,
        avg: 0,
        p50: 0,
        p90: 0,
        p99: 0
      };
    }

    let sorted = this.values.slice().sort((a, b) => a - b);
    let sum = 0;
    for (let i = 0; i < sorted.length; i++) {
      sum += sorted[i];
    }

    let pick = (q: number): number => {
      let index = Math.min(sorted.length - 1, Math.max(0, Math.floor((sorted.length - 1) * q)));
      return sorted[index];
    };

    return {
      count: sorted.length,
      min: sorted[0],
      max: sorted[sorted.length - 1],
      avg: sum / sorted.length,
      p50: pick(0.5),
      p90: pick(0.9),
      p99: pick(0.99)
    };
  }
}

export class RingLogBuffer {
  private capacity: number;
  private records: DebugLogRecord[] = [];

  constructor(capacity: number = 500) {
    this.capacity = Math.max(10, Math.floor(capacity));
  }

  push(level: 'debug' | 'info' | 'warn' | 'error', tag: string, message: string): void {
    let record: DebugLogRecord = {
      level,
      tag,
      message,
      timestamp: Date.now()
    };

    this.records.push(record);
    if (this.records.length > this.capacity) {
      this.records.shift();
    }
  }

  queryByLevel(level: 'debug' | 'info' | 'warn' | 'error'): DebugLogRecord[] {
    let out: DebugLogRecord[] = [];
    for (let i = 0; i < this.records.length; i++) {
      if (this.records[i].level === level) {
        out.push(this.records[i]);
      }
    }
    return out;
  }

  queryByTag(tag: string): DebugLogRecord[] {
    let out: DebugLogRecord[] = [];
    for (let i = 0; i < this.records.length; i++) {
      if (this.records[i].tag === tag) {
        out.push(this.records[i]);
      }
    }
    return out;
  }

  latest(limit: number = 50): DebugLogRecord[] {
    let n = Math.max(1, Math.floor(limit));
    if (this.records.length <= n) {
      return this.records.slice();
    }
    return this.records.slice(this.records.length - n);
  }

  clear(): void {
    this.records = [];
  }

  count(): number {
    return this.records.length;
  }
}

export class ImageMemoryEstimator {
  static estimateRawBytes(width: number, height: number, channels: number = 4): number {
    return Math.max(0, Math.floor(width)) * Math.max(0, Math.floor(height)) * Math.max(1, Math.floor(channels));
  }

  static estimateMipMapBytes(width: number, height: number, channels: number = 4): number {
    let w = Math.max(1, Math.floor(width));
    let h = Math.max(1, Math.floor(height));
    let total = 0;

    while (w > 1 || h > 1) {
      total += w * h * channels;
      w = Math.max(1, Math.floor(w / 2));
      h = Math.max(1, Math.floor(h / 2));
      if (w === 1 && h === 1) {
        total += channels;
        break;
      }
    }

    return total;
  }

  static estimateYuv420Bytes(width: number, height: number): number {
    let w = Math.max(1, Math.floor(width));
    let h = Math.max(1, Math.floor(height));
    return Math.floor(w * h * 1.5);
  }

  static prettyBytes(bytes: number): string {
    let value = Math.max(0, bytes);
    let units = ['B', 'KB', 'MB', 'GB'];
    let index = 0;

    while (value >= 1024 && index < units.length - 1) {
      value /= 1024;
      index++;
    }

    return `${value.toFixed(2)} ${units[index]}`;
  }
}

export class BenchmarkRunner {
  static run(cases: BenchmarkCase[]): BenchmarkResult[] {
    let results: BenchmarkResult[] = [];

    for (let i = 0; i < cases.length; i++) {
      let loops = Math.max(1, Math.floor(cases[i].loops));
      let start = Date.now();
      for (let n = 0; n < loops; n++) {
        cases[i].run();
      }
      let end = Date.now();
      let total = end - start;

      results.push({
        name: cases[i].name,
        loops,
        totalMs: total,
        avgMs: total / loops
      });
    }

    return results;
  }

  static format(results: BenchmarkResult[]): string {
    if (results.length === 0) {
      return 'No benchmark result.';
    }

    let lines: string[] = [];
    lines.push('name,loops,totalMs,avgMs');

    for (let i = 0; i < results.length; i++) {
      lines.push(`${results[i].name},${results[i].loops},${results[i].totalMs},${results[i].avgMs.toFixed(4)}`);
    }

    return lines.join('\n');
  }
}

export class RandomImageFactory {
  static solid(width: number, height: number, r: number, g: number, b: number, a: number = 255): ImagePlane {
    let image = ImageProcessUtils.createImage(width, height);
    ImageProcessUtils.fill(image, { r, g, b, a });
    return image;
  }

  static noise(width: number, height: number, withAlpha: boolean = false, seed: number = 12345): ImagePlane {
    let image = ImageProcessUtils.createImage(width, height);
    let random = RandomImageFactory.seeded(seed);

    for (let i = 0; i < image.data.length; i += 4) {
      image.data[i] = Math.floor(random() * 256);
      image.data[i + 1] = Math.floor(random() * 256);
      image.data[i + 2] = Math.floor(random() * 256);
      image.data[i + 3] = withAlpha ? Math.floor(random() * 256) : 255;
    }

    return image;
  }

  static gradient(width: number, height: number, horizontal: boolean = true): ImagePlane {
    let image = ImageProcessUtils.createImage(width, height);

    for (let y = 0; y < image.height; y++) {
      for (let x = 0; x < image.width; x++) {
        let t = horizontal
          ? x / Math.max(1, image.width - 1)
          : y / Math.max(1, image.height - 1);

        let idx = (y * image.width + x) * 4;
        image.data[idx] = Math.round(255 * t);
        image.data[idx + 1] = Math.round(255 * (1 - t));
        image.data[idx + 2] = Math.round(128 + 127 * Math.sin(t * Math.PI));
        image.data[idx + 3] = 255;
      }
    }

    return image;
  }

  static checkerboard(width: number, height: number, cellSize: number = 16): ImagePlane {
    let image = ImageProcessUtils.createImage(width, height);
    let size = Math.max(1, Math.floor(cellSize));

    for (let y = 0; y < image.height; y++) {
      for (let x = 0; x < image.width; x++) {
        let dark = ((Math.floor(x / size) + Math.floor(y / size)) % 2) === 0;
        let v = dark ? 64 : 192;
        let idx = (y * image.width + x) * 4;
        image.data[idx] = v;
        image.data[idx + 1] = v;
        image.data[idx + 2] = v;
        image.data[idx + 3] = 255;
      }
    }

    return image;
  }

  static randomPath(count: number, bounds: Rect2D, seed: number = 7): Point2D[] {
    let random = RandomImageFactory.seeded(seed);
    let out: Point2D[] = [];

    for (let i = 0; i < count; i++) {
      out.push({
        x: ImageGeometryUtils.lerp(bounds.left, bounds.right, random()),
        y: ImageGeometryUtils.lerp(bounds.top, bounds.bottom, random())
      });
    }

    return out;
  }

  private static seeded(seed: number): () => number {
    let state = seed >>> 0;
    return () => {
      state = (1664525 * state + 1013904223) >>> 0;
      return state / 0xFFFFFFFF;
    };
  }
}

export class ImageDebugFormatUtils {
  static point(point: Point2D): string {
    return `(${point.x.toFixed(2)}, ${point.y.toFixed(2)})`;
  }

  static rect(rect: Rect2D): string {
    let width = rect.right - rect.left;
    let height = rect.bottom - rect.top;
    return `[${rect.left.toFixed(2)}, ${rect.top.toFixed(2)} -> ${rect.right.toFixed(2)}, ${rect.bottom.toFixed(2)}] (${width.toFixed(2)}x${height.toFixed(2)})`;
  }

  static matrix4(matrix: number[]): string {
    if (matrix.length !== 16) {
      return 'Invalid 4x4 matrix';
    }

    let rows: string[] = [];
    for (let r = 0; r < 4; r++) {
      rows.push(
        `[${matrix[r * 4].toFixed(3)}, ${matrix[r * 4 + 1].toFixed(3)}, ${matrix[r * 4 + 2].toFixed(3)}, ${matrix[r * 4 + 3].toFixed(3)}]`
      );
    }
    return rows.join('\n');
  }

  static path(points: Point2D[], maxItems: number = 12): string {
    if (points.length === 0) {
      return '[]';
    }

    let count = Math.min(maxItems, points.length);
    let values: string[] = [];
    for (let i = 0; i < count; i++) {
      values.push(ImageDebugFormatUtils.point(points[i]));
    }

    if (count < points.length) {
      values.push(`... (+${points.length - count} points)`);
    }

    return `[${values.join(', ')}]`;
  }
}

interface GeneratedTypeLiteralInterface_3 {
  ok: boolean;
  errors: string[];
}

interface GeneratedTypeLiteralInterface_4 {
  psnr: number;
  alphaCoverageDiff: number;
  meanColorDiff: number;
}

export class ImageDiagnostics {
  static checkImage(image: ImagePlane): GeneratedTypeLiteralInterface_3 {
    let errors: string[] = [];

    if (image.width <= 0 || image.height <= 0) {
      errors.push('Invalid width or height.');
    }

    if (image.data.length !== image.width * image.height * 4) {
      errors.push('Data length does not match width*height*4.');
    }

    for (let i = 0; i < image.data.length; i++) {
      if (!Number.isFinite(image.data[i])) {
        errors.push(`Found invalid value at index ${i}.`);
        break;
      }
    }

    return {
      ok: errors.length === 0,
      errors
    };
  }

  static compareImageSimilarity(a: ImagePlane, b: ImagePlane): GeneratedTypeLiteralInterface_4 {
    let psnr = ImageProcessUtils.estimatePsnr(a, b);

    let coverageA = ImageProcessUtils.alphaCoverage(a);
    let coverageB = ImageProcessUtils.alphaCoverage(b);
    let alphaCoverageDiff = Math.abs(coverageA - coverageB);

    let meanA = ImageProcessUtils.meanColor(a);
    let meanB = ImageProcessUtils.meanColor(b);
    let meanColorDiff = Math.sqrt(
      Math.pow(meanA.r - meanB.r, 2) +
      Math.pow(meanA.g - meanB.g, 2) +
      Math.pow(meanA.b - meanB.b, 2)
    );

    return {
      psnr,
      alphaCoverageDiff,
      meanColorDiff
    };
  }

  static diffHeatMap(a: ImagePlane, b: ImagePlane): ImagePlane {
    let width = Math.min(a.width, b.width);
    let height = Math.min(a.height, b.height);
    let out = ImageProcessUtils.createImage(width, height);

    for (let y = 0; y < height; y++) {
      for (let x = 0; x < width; x++) {
        let idxA = (y * a.width + x) * 4;
        let idxB = (y * b.width + x) * 4;
        let idx = (y * out.width + x) * 4;

        let dr = Math.abs(a.data[idxA] - b.data[idxB]);
        let dg = Math.abs(a.data[idxA + 1] - b.data[idxB + 1]);
        let db = Math.abs(a.data[idxA + 2] - b.data[idxB + 2]);

        let diff = Math.round((dr + dg + db) / 3);
        out.data[idx] = diff;
        out.data[idx + 1] = Math.max(0, 255 - diff);
        out.data[idx + 2] = 0;
        out.data[idx + 3] = 255;
      }
    }

    return out;
  }

  static profileOperation(operationName: string, fn: () => void, samples: number = 20): PerfSummary {
    let counter = new PerfWindowCounter(samples);

    for (let i = 0; i < samples; i++) {
      let start = Date.now();
      fn();
      let end = Date.now();
      counter.push(end - start);
    }

    let summary = counter.summary();
    console.info('[ImageDiagnostics]', `${operationName}: avg=${summary.avg.toFixed(2)}ms p90=${summary.p90.toFixed(2)}ms`);
    return summary;
  }
}
