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

import { hilog } from '@kit.PerformanceAnalysisKit';
import { NodeContent } from '@kit.ArkUI';
import {
  attachImageAnimator,
  detachImageAnimator,
  getAnimatorSnapshot,
  getCoverageReport,
  getFrameInfoCaseReport,
  setAnimatorOptions,
  setAnimatorState,
} from 'libentry.so';

const LOG_DOMAIN = 0x0000;
const LOG_TAG = 'ImageAnimatorCapi';
const DEFAULT_DURATION = 1200;
const DEFAULT_ITERATION = -1;
const DETACHED_STATUS = 'Native ImageAnimator is not attached.';
const PAGE_PADDING = 16;
const SECTION_PADDING = 12;
const SECTION_RADIUS = 8;
const SECTION_GAP = 12;
const PREVIEW_WIDTH = 220;
const PREVIEW_HEIGHT = 180;
const PREVIEW_RADIUS = 6;
const TITLE_FONT_SIZE = 22;
const SECTION_TITLE_FONT_SIZE = 16;
const BODY_FONT_SIZE = 13;
const COVERAGE_FONT_SIZE = 12;
const COVERAGE_BADGE_FONT_SIZE = 11;
const MAIN_BUTTON_HEIGHT = 36;
const SMALL_BUTTON_HEIGHT = 32;
const TINY_BUTTON_HEIGHT = 30;
const REATTACH_BUTTON_HEIGHT = 34;
const ITERATION_BUTTON_WIDTH = 44;
const COVERAGE_BADGE_WIDTH = 42;
const COVERAGE_BADGE_HEIGHT = 22;
const CASE_BADGE_WIDTH = 54;
const CHECKBOX_GAP = 16;
const DURATION_MIN = 300;
const DURATION_MAX = 3000;
const DURATION_STEP = 100;
const SNAPSHOT_FALLBACK = -1;
const ITEM_GAP = 8;
const OPTION_ROW_VERTICAL_PADDING = 4;
const CHECKBOX_ROW_VERTICAL_PADDING = 6;

const PAGE_BACKGROUND = '#F1F4F8';
const PREVIEW_BACKGROUND = '#EEF2F6';
const PREVIEW_SECTION_BACKGROUND = '#F8FAFC';
const TITLE_COLOR = '#17212B';
const BODY_COLOR = '#4B5866';
const LABEL_COLOR = '#5C6670';
const VALUE_COLOR = '#18222D';
const COVERAGE_TEXT_COLOR = '#26313D';
const COVERAGE_OK_COLOR = '#0E7A43';
const COVERAGE_FAIL_COLOR = '#B42318';

enum NativeStatusValue {
  Initial = 0,
  Running = 1,
  Paused = 2,
  Stopped = 3,
}

enum NativeFillModeValue {
  None = 0,
  Forwards = 1,
  Backwards = 2,
  Both = 3,
}

interface AnimatorOptions {
  sources: string[];
  resources: Resource[];
  duration: number;
  reverse: boolean;
  fixedSize: boolean;
  fillMode: number;
  iteration: number;
}

interface AttachResult {
  attached: boolean;
  frameCount: number;
}

interface AnimatorSnapshot {
  attached: boolean;
  state?: number;
  duration?: number;
  reverse?: number;
  fixedSize?: number;
  fillMode?: number;
  iteration?: number;
  events?: object;
}

interface CoverageReport {
  nodeApiAvailable: boolean;
  items: string[];
  note: string;
}

interface MetricCheck {
  name: string;
  expected: number;
  actual: number;
  passed: boolean;
}

interface FrameInfoCase {
  group: string;
  name: string;
  api: string;
  note: string;
  passed: boolean;
  checks: MetricCheck[];
}

interface FrameInfoCaseReport {
  nodeApiAvailable: boolean;
  totalCases: number;
  passedCases: number;
  failedCases: number;
  totalChecks: number;
  passedChecks: number;
  failedChecks: number;
  cases: FrameInfoCase[];
}

@Entry
@Component
struct Index {
  private nativeContent: NodeContent = new NodeContent();
  private readonly mediaResources: Resource[] = [
    $r('app.media.foreground'),
    $r('app.media.background'),
    $r('app.media.startIcon'),
  ];
  private readonly stringSources: string[] = [
    'resource://media/foreground.png',
    'resource://media/background.png',
    'resource://media/startIcon.png',
  ];

  @State private attached: boolean = false;
  @State private reverse: boolean = false;
  @State private fixedSize: boolean = false;
  @State private fillMode: number = NativeFillModeValue.Forwards;
  @State private iteration: number = DEFAULT_ITERATION;
  @State private duration: number = DEFAULT_DURATION;
  @State private statusText: string = DETACHED_STATUS;
  @State private snapshot: AnimatorSnapshot = { attached: false };
  @State private report: CoverageReport = {
    nodeApiAvailable: false,
    items: [],
    note: '',
  };
  @State private frameInfoReport: FrameInfoCaseReport = {
    nodeApiAvailable: false,
    totalCases: 0,
    passedCases: 0,
    failedCases: 0,
    totalChecks: 0,
    passedChecks: 0,
    failedChecks: 0,
    cases: [],
  };

  aboutToAppear(): void {
    this.attachAnimator();
    this.refreshReport();
    this.refreshFrameInfoReport();
  }

  aboutToDisappear(): void {
    detachImageAnimator(this.nativeContent);
  }

  private buildOptions(): AnimatorOptions {
    return {
      sources: this.stringSources,
      resources: this.mediaResources,
      duration: this.duration,
      reverse: this.reverse,
      fixedSize: this.fixedSize,
      fillMode: this.fillMode,
      iteration: this.iteration,
    };
  }

  private attachAnimator(): void {
    try {
      const result = attachImageAnimator(this.nativeContent, this.buildOptions()) as AttachResult;
      this.attached = result.attached;
      this.statusText = `Attached ${result.frameCount} native frames.`;
      this.refreshSnapshot();
    } catch (err) {
      this.attached = false;
      this.statusText = `Attach failed: ${JSON.stringify(err)}`;
      hilog.error(LOG_DOMAIN, LOG_TAG, 'Attach failed: %{public}s', JSON.stringify(err));
    }
  }

  private refreshReport(): void {
    try {
      this.report = getCoverageReport(this.buildOptions()) as CoverageReport;
    } catch (err) {
      this.statusText = `Coverage failed: ${JSON.stringify(err)}`;
      hilog.error(LOG_DOMAIN, LOG_TAG, 'Coverage failed: %{public}s', JSON.stringify(err));
    }
  }

  private refreshFrameInfoReport(): void {
    try {
      this.frameInfoReport = getFrameInfoCaseReport() as FrameInfoCaseReport;
    } catch (err) {
      this.statusText = `FrameInfo cases failed: ${JSON.stringify(err)}`;
      hilog.error(LOG_DOMAIN, LOG_TAG, 'FrameInfo cases failed: %{public}s', JSON.stringify(err));
    }
  }

  private refreshSnapshot(): void {
    try {
      this.snapshot = getAnimatorSnapshot(this.nativeContent) as AnimatorSnapshot;
    } catch (err) {
      this.snapshot = { attached: false };
      hilog.error(LOG_DOMAIN, LOG_TAG, 'Snapshot failed: %{public}s', JSON.stringify(err));
    }
  }

  private setState(state: number): void {
    if (!this.attached) {
      return;
    }
    const ok = setAnimatorState(this.nativeContent, state);
    this.statusText = ok ? `State set to ${state}.` : `State update failed: ${state}.`;
    this.refreshSnapshot();
  }

  private applyOptions(): void {
    if (!this.attached) {
      return;
    }
    const ok = setAnimatorOptions(this.nativeContent, this.buildOptions());
    this.statusText = ok ? 'Animator attributes updated from C API.' : 'Animator attribute update failed.';
    this.refreshSnapshot();
    this.refreshReport();
    this.refreshFrameInfoReport();
  }

  private formatCaseSummary(): string {
    return `${this.frameInfoReport.passedCases}/${this.frameInfoReport.totalCases} cases`;
  }

  private formatCheckSummary(): string {
    return `${this.frameInfoReport.passedChecks}/${this.frameInfoReport.totalChecks} checks`;
  }

  private formatCaseDetail(item: FrameInfoCase): string {
    const note = item.note.length > 0 ? ` ${item.note}` : '';
    return `${item.group} - ${item.name} (${item.api}).${note}`;
  }

  private formatFailedChecks(item: FrameInfoCase): string {
    const failed = item.checks.filter((check: MetricCheck) => !check.passed);
    if (failed.length === 0) {
      return 'all metric checks passed';
    }
    return failed.map((check: MetricCheck) => `${check.name}: ${check.actual}/${check.expected}`).join(', ');
  }

  private updateDuration(value: number): void {
    this.duration = Math.round(value);
    this.applyOptions();
  }

  private updateReverse(value: boolean): void {
    this.reverse = value;
    this.applyOptions();
  }

  private updateFixedSize(value: boolean): void {
    this.fixedSize = value;
    this.applyOptions();
  }

  private decreaseIteration(): void {
    this.iteration = this.iteration <= DEFAULT_ITERATION ? DEFAULT_ITERATION : this.iteration - 1;
    this.applyOptions();
  }

  private increaseIteration(): void {
    this.iteration += 1;
    this.applyOptions();
  }

  private updateFillMode(fillMode: NativeFillModeValue): void {
    this.fillMode = fillMode;
    this.applyOptions();
  }

  private formatIteration(): string {
    return this.iteration < 0 ? 'infinite' : `${this.iteration}`;
  }

  @Builder
  private commandButton(label: string, state: number): void {
    Button(label)
      .height(MAIN_BUTTON_HEIGHT)
      .fontSize(BODY_FONT_SIZE)
      .onClick(() => this.setState(state))
  }

  @Builder
  private optionRow(label: string, value: string): void {
    Row() {
      Text(label)
        .fontSize(BODY_FONT_SIZE)
        .fontColor(LABEL_COLOR)
      Text(value)
        .fontSize(BODY_FONT_SIZE)
        .fontWeight(FontWeight.Medium)
        .fontColor(VALUE_COLOR)
    }
    .width('100%')
    .justifyContent(FlexAlign.SpaceBetween)
    .padding({ top: OPTION_ROW_VERTICAL_PADDING, bottom: OPTION_ROW_VERTICAL_PADDING })
  }

  @Builder
  private sectionTitle(title: string, action: string, handler: () => void): void {
    Row() {
      Text(title)
        .fontSize(SECTION_TITLE_FONT_SIZE)
        .fontWeight(FontWeight.Medium)
      Blank()
      Button(action)
        .height(TINY_BUTTON_HEIGHT)
        .fontSize(COVERAGE_FONT_SIZE)
        .onClick(() => handler())
    }
    .width('100%')
    .margin({ bottom: CHECKBOX_ROW_VERTICAL_PADDING })
  }

  @Builder
  private coverageLine(item: string): void {
    Row({ space: ITEM_GAP }) {
      Text(item.endsWith('OK') ? 'OK' : 'FAIL')
        .fontSize(COVERAGE_BADGE_FONT_SIZE)
        .fontColor(Color.White)
        .textAlign(TextAlign.Center)
        .width(COVERAGE_BADGE_WIDTH)
        .height(COVERAGE_BADGE_HEIGHT)
        .backgroundColor(item.endsWith('OK') ? COVERAGE_OK_COLOR : COVERAGE_FAIL_COLOR)
        .borderRadius(SECTION_RADIUS / 2)
      Text(item)
        .fontSize(COVERAGE_FONT_SIZE)
        .fontColor(COVERAGE_TEXT_COLOR)
        .layoutWeight(1)
        .maxLines(2)
    }
    .width('100%')
    .alignItems(VerticalAlign.Center)
    .padding({ top: OPTION_ROW_VERTICAL_PADDING, bottom: OPTION_ROW_VERTICAL_PADDING })
  }

  @Builder
  private caseLine(item: FrameInfoCase): void {
    Row({ space: ITEM_GAP }) {
      Text(item.passed ? 'PASS' : 'FAIL')
        .fontSize(COVERAGE_BADGE_FONT_SIZE)
        .fontColor(Color.White)
        .textAlign(TextAlign.Center)
        .width(CASE_BADGE_WIDTH)
        .height(COVERAGE_BADGE_HEIGHT)
        .backgroundColor(item.passed ? COVERAGE_OK_COLOR : COVERAGE_FAIL_COLOR)
        .borderRadius(SECTION_RADIUS / 2)
      Column() {
        Text(this.formatCaseDetail(item))
          .fontSize(COVERAGE_FONT_SIZE)
          .fontColor(COVERAGE_TEXT_COLOR)
          .maxLines(3)
        Text(this.formatFailedChecks(item))
          .fontSize(COVERAGE_BADGE_FONT_SIZE)
          .fontColor(BODY_COLOR)
          .maxLines(2)
          .margin({ top: OPTION_ROW_VERTICAL_PADDING })
      }
      .layoutWeight(1)
    }
    .width('100%')
    .alignItems(VerticalAlign.Center)
    .padding({ top: OPTION_ROW_VERTICAL_PADDING, bottom: OPTION_ROW_VERTICAL_PADDING })
  }

  @Builder
  private headerBar(): void {
    Row() {
      Text('ImageAnimator C API')
        .fontSize(TITLE_FONT_SIZE)
        .fontWeight(FontWeight.Bold)
        .fontColor(TITLE_COLOR)
      Blank()
      Button('Reattach')
        .height(REATTACH_BUTTON_HEIGHT)
        .fontSize(BODY_FONT_SIZE)
        .onClick(() => this.attachAnimator())
    }
    .width('100%')
    .alignItems(VerticalAlign.Center)
  }

  @Builder
  private previewPanel(): void {
    Column() {
      Stack() {
        ContentSlot(this.nativeContent)
      }
      .width(PREVIEW_WIDTH)
      .height(PREVIEW_HEIGHT)
      .backgroundColor(PREVIEW_BACKGROUND)
      .borderRadius(PREVIEW_RADIUS)

      Text(this.statusText)
        .fontSize(BODY_FONT_SIZE)
        .fontColor(BODY_COLOR)
        .margin({ top: ITEM_GAP })
    }
    .width('100%')
    .alignItems(HorizontalAlign.Center)
    .padding({ top: SECTION_PADDING, bottom: SECTION_PADDING })
    .backgroundColor(PREVIEW_SECTION_BACKGROUND)
    .borderRadius(SECTION_RADIUS)
  }

  @Builder
  private commandBar(): void {
    Row({ space: ITEM_GAP }) {
      this.commandButton('Run', NativeStatusValue.Running)
      this.commandButton('Pause', NativeStatusValue.Paused)
      this.commandButton('Stop', NativeStatusValue.Stopped)
      this.commandButton('Initial', NativeStatusValue.Initial)
    }
    .width('100%')
    .margin({ top: SECTION_GAP })
  }

  @Builder
  private durationControl(): void {
    this.optionRow('duration', `${this.duration} ms`)
    Slider({ value: this.duration, min: DURATION_MIN, max: DURATION_MAX, step: DURATION_STEP })
      .width('100%')
      .onChange((value: number) => this.updateDuration(value))
  }

  @Builder
  private booleanOptions(): void {
    Row() {
      Checkbox({ name: 'reverse', group: 'options' })
        .select(this.reverse)
        .onChange((value: boolean) => this.updateReverse(value))
      Text('reverse')
        .fontSize(BODY_FONT_SIZE)
      Checkbox({ name: 'fixedSize', group: 'options' })
        .select(this.fixedSize)
        .margin({ left: CHECKBOX_GAP })
        .onChange((value: boolean) => this.updateFixedSize(value))
      Text('fixedSize')
        .fontSize(BODY_FONT_SIZE)
    }
    .width('100%')
    .alignItems(VerticalAlign.Center)
    .padding({ top: CHECKBOX_ROW_VERTICAL_PADDING, bottom: CHECKBOX_ROW_VERTICAL_PADDING })
  }

  @Builder
  private iterationControls(): void {
    this.optionRow('iteration', this.formatIteration())
    Row({ space: ITEM_GAP }) {
      Button('-')
        .height(SMALL_BUTTON_HEIGHT)
        .width(ITERATION_BUTTON_WIDTH)
        .onClick(() => this.decreaseIteration())
      Button('+')
        .height(SMALL_BUTTON_HEIGHT)
        .width(ITERATION_BUTTON_WIDTH)
        .onClick(() => this.increaseIteration())
      Button('Fill: Forwards')
        .height(SMALL_BUTTON_HEIGHT)
        .fontSize(COVERAGE_FONT_SIZE)
        .onClick(() => this.updateFillMode(NativeFillModeValue.Forwards))
      Button('Fill: Both')
        .height(SMALL_BUTTON_HEIGHT)
        .fontSize(COVERAGE_FONT_SIZE)
        .onClick(() => this.updateFillMode(NativeFillModeValue.Both))
    }
    .width('100%')
  }

  @Builder
  private optionsPanel(): void {
    Column() {
      this.durationControl()
      this.booleanOptions()
      this.iterationControls()
    }
    .width('100%')
    .padding(SECTION_PADDING)
    .backgroundColor($r('sys.color.comp_background_list_card'))
    .borderRadius(SECTION_RADIUS)
    .margin({ top: SECTION_GAP })
  }

  @Builder
  private snapshotPanel(): void {
    Column() {
      this.sectionTitle('Native Snapshot', 'Refresh', () => this.refreshSnapshot())
      this.optionRow('state', `${this.snapshot.state ?? SNAPSHOT_FALLBACK}`)
      this.optionRow('duration', `${this.snapshot.duration ?? SNAPSHOT_FALLBACK}`)
      this.optionRow('reverse', `${this.snapshot.reverse ?? SNAPSHOT_FALLBACK}`)
      this.optionRow('fixedSize', `${this.snapshot.fixedSize ?? SNAPSHOT_FALLBACK}`)
      this.optionRow('fillMode', `${this.snapshot.fillMode ?? SNAPSHOT_FALLBACK}`)
      this.optionRow('iteration', `${this.snapshot.iteration ?? SNAPSHOT_FALLBACK}`)
      this.optionRow('events', JSON.stringify(this.snapshot.events ?? {}))
    }
    .width('100%')
    .padding(SECTION_PADDING)
    .backgroundColor($r('sys.color.comp_background_list_card'))
    .borderRadius(SECTION_RADIUS)
    .margin({ top: SECTION_GAP })
  }

  @Builder
  private coveragePanel(): void {
    Column() {
      this.sectionTitle('Interface Coverage', 'Run', () => this.refreshReport())
      ForEach(this.report.items, (item: string) => {
        this.coverageLine(item)
      }, (item: string) => item)
    }
    .width('100%')
    .padding(SECTION_PADDING)
    .backgroundColor($r('sys.color.comp_background_list_card'))
    .borderRadius(SECTION_RADIUS)
    .margin({ top: SECTION_GAP })
  }

  @Builder
  private frameInfoCasePanel(): void {
    Column() {
      this.sectionTitle('FrameInfo Cases', 'Run', () => this.refreshFrameInfoReport())
      this.optionRow('nodeApi', `${this.frameInfoReport.nodeApiAvailable}`)
      this.optionRow('cases', this.formatCaseSummary())
      this.optionRow('checks', this.formatCheckSummary())
      ForEach(this.frameInfoReport.cases, (item: FrameInfoCase) => {
        this.caseLine(item)
      }, (item: FrameInfoCase) => `${item.group}-${item.name}`)
    }
    .width('100%')
    .padding(SECTION_PADDING)
    .backgroundColor($r('sys.color.comp_background_list_card'))
    .borderRadius(SECTION_RADIUS)
    .margin({ top: SECTION_GAP })
  }

  build() {
    Column() {
      this.headerBar()
      this.previewPanel()
      this.commandBar()
      this.optionsPanel()
      this.snapshotPanel()
      this.coveragePanel()
      this.frameInfoCasePanel()
    }
    .width('100%')
    .height('100%')
    .padding(PAGE_PADDING)
    .backgroundColor(PAGE_BACKGROUND)
  }
}
