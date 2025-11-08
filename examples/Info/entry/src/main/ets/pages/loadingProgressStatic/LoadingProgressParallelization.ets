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
  Counter,
  PatternLockController,
  PatternLock,
  CircleStyleOptions,
  LoadingProgress,
  WrappedBuilder,
  wrapBuilder,
  LoadingProgressConfiguration,
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

type LoadingProgressBuilder =
@
Builder(config:
LoadingProgressConfiguration
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
type ProgressBuilder =
@
Builder(config:
ProgressConfiguration
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
struct LoadingProgressTest {
  @State passwords: number[] = [] as number[];
  @State message: string = 'please input password!';
  private patternLockController: PatternLockController = new PatternLockController();

  build() {
    Scroll() {
      Flex({ wrap: FlexWrap.Wrap, justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign.Center }) {
        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            LoadingProgress()
              .color('#fff1091b')
              .size({ width: '100%' })
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            LoadingProgress()
              .enableLoading(true)
              .color(Color.Blue)
              .layoutWeight(1)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            LoadingProgress()
              .contentModifier(new MyLoadingProgressStyle([12.6, 21.1, 13.4, 35.2, 26.0, 68.0]))
              .layoutWeight(1)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            LoadingProgress()
              .color(undefined)
              .size({ width: '100%' })
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            LoadingProgress()
              .color('#fff1091b')
              .size({ width: '100%' })
              .enableLoading(true)
              .layoutWeight(1)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            LoadingProgress()
              .color('#fff1091b')
              .size({ width: '100%' })
              .enableLoading(true)
              .layoutWeight(1)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            LoadingProgress()
              .color('#fff1091b')
              .size({ width: '100%' })
              .enableLoading(true)
              .layoutWeight(1)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            LoadingProgress()
              .enableLoading(undefined)
              .color(Color.Blue)
              .layoutWeight(1)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            LoadingProgress()
              .color('#fff1091b')
              .size({ width: '100%' })
              .enableLoading(true)
              .layoutWeight(1)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            LoadingProgress()
              .color('#fff1091b')
              .size({ width: '100%' })
              .enableLoading(false)
              .layoutWeight(1)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            LoadingProgress()
              .color('#fff1091b')
              .size({ width: '100%' })
              .enableLoading(true)
              .layoutWeight(1)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            LoadingProgress()
              .color('#fff1091b')
              .size({ width: '100%' })
              .enableLoading(true)
              .layoutWeight(1)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            LoadingProgress()
              .color('#fff1091b')
              .size({ width: '100%' })
              .enableLoading(true)
              .layoutWeight(1)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            LoadingProgress()
              .color('#fff1091b')
              .size({ width: '100%' })
              .enableLoading(true)
              .layoutWeight(1)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            LoadingProgress()
              .color('#fff1091b')
              .size({ width: '100%' })
              .enableLoading(true)
              .layoutWeight(1)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            LoadingProgress()
              .color('#fff1091b')
              .size({ width: '100%' })
              .enableLoading(true)
              .layoutWeight(1)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            LoadingProgress()
              .color('#fff1091b')
              .size({ width: '100%' })
              .enableLoading(true)
              .layoutWeight(1)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            LoadingProgress()
              .color('#fff1091b')
              .size({ width: '100%' })
              .enableLoading(true)
              .layoutWeight(1)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            LoadingProgress()
              .color('#fff1091b')
              .size({ width: '100%' })
              .enableLoading(true)
              .layoutWeight(1)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            LoadingProgress()
              .color('#fff1091b')
              .size({ width: '100%' })
              .enableLoading(true)
              .layoutWeight(1)
          })
        }
      }
    }
  }
}

class MyLoadingProgressStyle implements ContentModifier<LoadingProgressConfiguration> {
  values: number[] = {}

  constructor(values: number[]) {
    this.values = values
  }

  applyContent(): WrappedBuilder<LoadingProgressBuilder> {
    return wrapBuilder(buildLoadingProgress);
  }
}

@Builder
function buildLoadingProgress(config: LoadingProgressConfiguration): void {
  Column() {
    Column() {
    }

    Column() {
      Line().width("100%").backgroundColor("#ff373737")
    }

    Row() {
      Text('Length = ').align(Alignment.Start)
      Text('Max = ').align(Alignment.Start)
    }
  }
}
