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
'use static'

import {
  Entry,
  FlexWrap,
  FontStyle,
  ForEach,
  FlexAlign,
  ItemAlign,
  Flex,
  Text,
  Column,
  Scroll,
  Component,
  Button,
  ClickEvent,
  Checkbox,
  Gauge,
  LinearGradient,
  FontWeight,
  TextAlign,
  Builder,
  Font,
  $r,
  ContentModifier,
  GaugeConfiguration,
  WrappedBuilder,
  Color,
  Progress,
  ProgressType,
  LengthMetrics,
  ProgressOptions,
  CapsuleStyleOptions,
  Entry,
  Text,
  Column,
  Component,
  Button,
  ClickEvent,
  Row,
  WrappedBuilder,
  wrapBuilder,
  Builder,
  ContentModifier,
  LoadingProgress,
  LoadingProgressConfiguration,
  Alignment,
  Line,
  ForEach,
  RelativeContainer,
  Rect,
  Color,
  Gauge,
  GaugeOptions,
  GaugeConfiguration,
  HorizontalAlign,
  FlexAlign,
  LoadingProgress,
  LoadingProgressConfiguration,
  Progress,
  ProgressType,
  ProgressConfiguration,
  Flex,
  Path,
  TextClock,
  TextClockConfiguration,
  TextClockController,
  TimePickerFormat,
  TimePicker,
  Date,
  TextTimer,
  TextTimerConfiguration,
  TextTimerController,
  Circle,
  Stack
} from '@ohos.arkui.component'
import { State } from '@ohos.arkui.stateManagement'
import hilog from '@ohos.hilog'
import { forEachItems20, forEachItems100 } from '../Utils/Jarvis';
import { ParallelOption, ParallelizeUI } from '@ohos.arkui.Parallelize';


type ProgressBuilder =
@
Builder(config:
ProgressConfiguration
)
=>
void;
type GaugeBuilder =
@
Builder(config:
GaugeConfiguration
)
=>
void;
type TextClockBuilder =
@
Builder(config:
TextClockConfiguration
)
=>
void;
type TextTimerBuilder =
@
Builder(config:
TextTimerConfiguration
)
=>
void;

@Entry
@Component
struct GaugeTest {
  build() {
    Scroll() {

      Flex({ wrap: FlexWrap.Wrap, justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign.Center }) {
        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Progress({ value: 88, total: 100, type: ProgressType.Capsule } as ProgressOptions)
              .width(300)
              .height(50)
              .value(88)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Progress({ value: 88, total: 100, type: ProgressType.Capsule } as ProgressOptions)
              .width(300)
              .height(50)
              .color(Color.Red)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Progress({ value: 88, total: 100, type: ProgressType.Capsule } as ProgressOptions)
              .contentModifier(new MyProgressStyle([12.6, 21.1, 13.4, 35.2, 26.0, 68.0]))
              .width(300)
              .height(50)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Progress({ value: 88, total: 100, type: ProgressType.Capsule } as ProgressOptions)
              .style({
                borderColor: Color.Blue,
                borderWidth: 1,
                font: { size: 13, style: FontStyle.Normal } as Font,
                fontColor: Color.Gray,
                enableScanEffect: false,
                showDefaultPercentage: false
              } as CapsuleStyleOptions)
              .width(100)
              .height(60)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Progress({ value: 88, total: 100, type: ProgressType.Capsule } as ProgressOptions)
              .width(300)
              .height(50)
              .privacySensitive(undefined)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Progress({ value: 88, total: 100, type: ProgressType.Capsule } as ProgressOptions)
              .width(300)
              .height(50)
              .color(undefined)
              .style(undefined)
              .privacySensitive(undefined)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Progress({ value: 88, total: 100, type: ProgressType.Capsule } as ProgressOptions)
              .width(300)
              .height(50)
              .value(88)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Progress({ value: 88, total: 100, type: ProgressType.Capsule } as ProgressOptions)
              .width(300)
              .height(50)
              .value(88)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Progress({ value: 88, total: 100, type: ProgressType.Capsule } as ProgressOptions)
              .width(300)
              .height(50)
              .value(88)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Progress({ value: 88, total: 100, type: ProgressType.Capsule } as ProgressOptions)
              .width(300)
              .height(50)
              .value(88)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Progress({ value: 88, total: 100, type: ProgressType.Capsule } as ProgressOptions)
              .width(300)
              .height(50)
              .value(88)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Progress({ value: 88, total: 100, type: ProgressType.Capsule } as ProgressOptions)
              .width(300)
              .height(50)
              .value(88)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Progress({ value: 88, total: 100, type: ProgressType.Capsule } as ProgressOptions)
              .width(300)
              .height(50)
              .value(88)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Progress({ value: 88, total: 100, type: ProgressType.Capsule } as ProgressOptions)
              .width(300)
              .height(50)
              .value(88)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Progress({ value: 88, total: 100, type: ProgressType.Capsule } as ProgressOptions)
              .width(300)
              .height(50)
              .value(88)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Progress({ value: 88, total: 100, type: ProgressType.Capsule } as ProgressOptions)
              .width(300)
              .height(50)
              .value(88)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Progress({ value: 88, total: 100, type: ProgressType.Capsule } as ProgressOptions)
              .width(300)
              .height(50)
              .value(88)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Progress({ value: 88, total: 100, type: ProgressType.Capsule } as ProgressOptions)
              .width(300)
              .height(50)
              .value(88)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Progress({ value: 88, total: 100, type: ProgressType.Capsule } as ProgressOptions)
              .width(300)
              .height(50)
              .value(88)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Progress({ value: 88, total: 100, type: ProgressType.Capsule } as ProgressOptions)
              .width(300)
              .height(50)
              .value(88)
          })
        }
      }
    }
  }
}

class MyProgressStyle implements ContentModifier<ProgressConfiguration> {
  values: number[] = {}

  constructor(values: number[]) {
    this.values = values
  }

  applyContent(): WrappedBuilder<ProgressBuilder> {
    return wrapBuilder(buildProgress);
  }
}

@Builder
function buildProgress(config: ProgressConfiguration): void {
  Column() {
    Column() {
    }

    Column() {
      Line().width('100%').backgroundColor('#ff373737')
    }

    Row() {
      Text('Length = ').align(Alignment.Start)
      Text('Max = ').align(Alignment.Start)
    }
  }
}
