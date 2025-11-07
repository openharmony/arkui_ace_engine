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
  GaugeOptions,
  FontWeight,
  TextAlign,
  Builder,
  $r,
  ContentModifier,
  GaugeConfiguration,
  WrappedBuilder,
  Color,
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
  Gauge,
  GaugeConfiguration,
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
  Gauge,
  GaugeConfiguration,
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


type GaugeBuilder =
@
Builder(config:
GaugeConfiguration
)
=>
void;

@Entry
@Component
struct GaugeTest {
  @Builder
  descriptionBuilder() {
    Text('说明文本')
      .maxFontSize('30sp')
      .minFontSize("10.0vp")
      .fontColor("#fffa2a2d")
      .fontWeight(FontWeight.Medium)
      .width('100%')
      .height("100%")
      .textAlign(TextAlign.Center)
  }

  build() {
    Scroll() {
      Flex({ wrap: FlexWrap.Wrap, justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign.Center }) {
        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Gauge({}) {
            }
            .value(50)
            .startAngle(210)
            .endAngle(150)
            .colors([[new LinearGradient([{ color: "#deb6fb", offset: 0 }, { color: "#ac49f5", offset: 1 }]), 9],
              [new LinearGradient([{ color: "#bbb7fc", offset: 0 }, { color: "#564af7", offset: 1 }]), 8],
              [new LinearGradient([{ color: "#f5b5c2", offset: 0 }, { color: "#e64566", offset: 1 }]), 7],
              [new LinearGradient([{ color: "#f8c5a6", offset: 0 }, { color: "#ed6f21", offset: 1 }]), 6],
              [new LinearGradient([{ color: "#fceb99", offset: 0 }, { color: "#f7ce00", offset: 1 }]), 5],
              [new LinearGradient([{ color: "#dbefa5", offset: 0 }, { color: "#a5d61d", offset: 1 }]), 4],
              [new LinearGradient([{ color: "#c1e4be", offset: 0 }, { color: "#64bb5c", offset: 1 }]), 3],
              [new LinearGradient([{ color: "#c0ece5", offset: 0 }, { color: "#61cfbe", offset: 1 }]), 2],
              [new LinearGradient([{ color: "#b5e0f4", offset: 0 }, { color: "#46b1e3", offset: 1 }]), 1]])
            .width(150)
            .height(150)
            .strokeWidth(18)
            .trackShadow({ radius: 7, offsetX: 7, offsetY: 7 })
            .description(this.descriptionBuilder)
            .indicator({ space: 10, icon: $r('app.media.background') })
            .padding(18)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Gauge({}) {
            }
            .value(50)
            .startAngle(210)
            .endAngle(150)
            .colors([[new LinearGradient([{ color: "#deb6fb", offset: 0 }, { color: "#ac49f5", offset: 1 }]), 9],
              [new LinearGradient([{ color: "#bbb7fc", offset: 0 }, { color: "#564af7", offset: 1 }]), 8],
              [new LinearGradient([{ color: "#f5b5c2", offset: 0 }, { color: "#e64566", offset: 1 }]), 7],
              [new LinearGradient([{ color: "#f8c5a6", offset: 0 }, { color: "#ed6f21", offset: 1 }]), 6],
              [new LinearGradient([{ color: "#fceb99", offset: 0 }, { color: "#f7ce00", offset: 1 }]), 5],
              [new LinearGradient([{ color: "#dbefa5", offset: 0 }, { color: "#a5d61d", offset: 1 }]), 4],
              [new LinearGradient([{ color: "#c1e4be", offset: 0 }, { color: "#64bb5c", offset: 1 }]), 3],
              [new LinearGradient([{ color: "#c0ece5", offset: 0 }, { color: "#61cfbe", offset: 1 }]), 2],
              [new LinearGradient([{ color: "#b5e0f4", offset: 0 }, { color: "#46b1e3", offset: 1 }]), 1]])
            .width(150)
            .height(150)
            .strokeWidth(18)
            .trackShadow({ radius: 7, offsetX: 7, offsetY: 7 })
            .description(this.descriptionBuilder)
            .indicator({ space: 10, icon: $r('app.media.background') })
            .padding(18)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Gauge({}) {
            }
            .value(50)
            .startAngle(210)
            .endAngle(150)
            .colors([[new LinearGradient([{ color: "#deb6fb", offset: 0 }, { color: "#ac49f5", offset: 1 }]), 9],
              [new LinearGradient([{ color: "#bbb7fc", offset: 0 }, { color: "#564af7", offset: 1 }]), 8],
              [new LinearGradient([{ color: "#f5b5c2", offset: 0 }, { color: "#e64566", offset: 1 }]), 7],
              [new LinearGradient([{ color: "#f8c5a6", offset: 0 }, { color: "#ed6f21", offset: 1 }]), 6],
              [new LinearGradient([{ color: "#fceb99", offset: 0 }, { color: "#f7ce00", offset: 1 }]), 5],
              [new LinearGradient([{ color: "#dbefa5", offset: 0 }, { color: "#a5d61d", offset: 1 }]), 4],
              [new LinearGradient([{ color: "#c1e4be", offset: 0 }, { color: "#64bb5c", offset: 1 }]), 3],
              [new LinearGradient([{ color: "#c0ece5", offset: 0 }, { color: "#61cfbe", offset: 1 }]), 2],
              [new LinearGradient([{ color: "#b5e0f4", offset: 0 }, { color: "#46b1e3", offset: 1 }]), 1]])
            .width(150)
            .height(150)
            .strokeWidth(18)
            .trackShadow({ radius: 7, offsetX: 7, offsetY: 7 })
            .description(this.descriptionBuilder)
            .indicator({ space: 10, icon: $r('app.media.background') })
            .padding(18)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Gauge({}) {
            }
            .value(50)
            .startAngle(210)
            .endAngle(150)
            .colors([[new LinearGradient([{ color: "#deb6fb", offset: 0 }, { color: "#ac49f5", offset: 1 }]), 9],
              [new LinearGradient([{ color: "#bbb7fc", offset: 0 }, { color: "#564af7", offset: 1 }]), 8],
              [new LinearGradient([{ color: "#f5b5c2", offset: 0 }, { color: "#e64566", offset: 1 }]), 7],
              [new LinearGradient([{ color: "#f8c5a6", offset: 0 }, { color: "#ed6f21", offset: 1 }]), 6],
              [new LinearGradient([{ color: "#fceb99", offset: 0 }, { color: "#f7ce00", offset: 1 }]), 5],
              [new LinearGradient([{ color: "#dbefa5", offset: 0 }, { color: "#a5d61d", offset: 1 }]), 4],
              [new LinearGradient([{ color: "#c1e4be", offset: 0 }, { color: "#64bb5c", offset: 1 }]), 3],
              [new LinearGradient([{ color: "#c0ece5", offset: 0 }, { color: "#61cfbe", offset: 1 }]), 2],
              [new LinearGradient([{ color: "#b5e0f4", offset: 0 }, { color: "#46b1e3", offset: 1 }]), 1]])
            .width(150)
            .height(150)
            .strokeWidth(18)
            .trackShadow({ radius: 7, offsetX: 7, offsetY: 7 })
            .description(this.descriptionBuilder)
            .indicator({ space: 10, icon: $r('app.media.background') })
            .padding(18)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Gauge({}) {
            }
            .value(50)
            .startAngle(210)
            .endAngle(150)
            .colors([[new LinearGradient([{ color: "#deb6fb", offset: 0 }, { color: "#ac49f5", offset: 1 }]), 9],
              [new LinearGradient([{ color: "#bbb7fc", offset: 0 }, { color: "#564af7", offset: 1 }]), 8],
              [new LinearGradient([{ color: "#f5b5c2", offset: 0 }, { color: "#e64566", offset: 1 }]), 7],
              [new LinearGradient([{ color: "#f8c5a6", offset: 0 }, { color: "#ed6f21", offset: 1 }]), 6],
              [new LinearGradient([{ color: "#fceb99", offset: 0 }, { color: "#f7ce00", offset: 1 }]), 5],
              [new LinearGradient([{ color: "#dbefa5", offset: 0 }, { color: "#a5d61d", offset: 1 }]), 4],
              [new LinearGradient([{ color: "#c1e4be", offset: 0 }, { color: "#64bb5c", offset: 1 }]), 3],
              [new LinearGradient([{ color: "#c0ece5", offset: 0 }, { color: "#61cfbe", offset: 1 }]), 2],
              [new LinearGradient([{ color: "#b5e0f4", offset: 0 }, { color: "#46b1e3", offset: 1 }]), 1]])
            .width(150)
            .height(150)
            .strokeWidth(18)
            .trackShadow({ radius: 7, offsetX: 7, offsetY: 7 })
            .description(this.descriptionBuilder)
            .indicator({ space: 10, icon: $r('app.media.background') })
            .padding(18)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Gauge({}) {
            }
            .value(50)
            .startAngle(210)
            .endAngle(150)
            .colors([[new LinearGradient([{ color: "#deb6fb", offset: 0 }, { color: "#ac49f5", offset: 1 }]), 9],
              [new LinearGradient([{ color: "#bbb7fc", offset: 0 }, { color: "#564af7", offset: 1 }]), 8],
              [new LinearGradient([{ color: "#f5b5c2", offset: 0 }, { color: "#e64566", offset: 1 }]), 7],
              [new LinearGradient([{ color: "#f8c5a6", offset: 0 }, { color: "#ed6f21", offset: 1 }]), 6],
              [new LinearGradient([{ color: "#fceb99", offset: 0 }, { color: "#f7ce00", offset: 1 }]), 5],
              [new LinearGradient([{ color: "#dbefa5", offset: 0 }, { color: "#a5d61d", offset: 1 }]), 4],
              [new LinearGradient([{ color: "#c1e4be", offset: 0 }, { color: "#64bb5c", offset: 1 }]), 3],
              [new LinearGradient([{ color: "#c0ece5", offset: 0 }, { color: "#61cfbe", offset: 1 }]), 2],
              [new LinearGradient([{ color: "#b5e0f4", offset: 0 }, { color: "#46b1e3", offset: 1 }]), 1]])
            .width(150)
            .height(150)
            .strokeWidth(18)
            .trackShadow({ radius: 7, offsetX: 7, offsetY: 7 })
            .description(this.descriptionBuilder)
            .indicator({ space: 10, icon: $r('app.media.background') })
            .padding(18)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Gauge({}) {
            }
            .value(50)
            .startAngle(210)
            .endAngle(150)
            .colors([[new LinearGradient([{ color: "#deb6fb", offset: 0 }, { color: "#ac49f5", offset: 1 }]), 9],
              [new LinearGradient([{ color: "#bbb7fc", offset: 0 }, { color: "#564af7", offset: 1 }]), 8],
              [new LinearGradient([{ color: "#f5b5c2", offset: 0 }, { color: "#e64566", offset: 1 }]), 7],
              [new LinearGradient([{ color: "#f8c5a6", offset: 0 }, { color: "#ed6f21", offset: 1 }]), 6],
              [new LinearGradient([{ color: "#fceb99", offset: 0 }, { color: "#f7ce00", offset: 1 }]), 5],
              [new LinearGradient([{ color: "#dbefa5", offset: 0 }, { color: "#a5d61d", offset: 1 }]), 4],
              [new LinearGradient([{ color: "#c1e4be", offset: 0 }, { color: "#64bb5c", offset: 1 }]), 3],
              [new LinearGradient([{ color: "#c0ece5", offset: 0 }, { color: "#61cfbe", offset: 1 }]), 2],
              [new LinearGradient([{ color: "#b5e0f4", offset: 0 }, { color: "#46b1e3", offset: 1 }]), 1]])
            .width(150)
            .height(150)
            .strokeWidth(18)
            .trackShadow({ radius: 7, offsetX: 7, offsetY: 7 })
            .description(this.descriptionBuilder)
            .indicator({ space: 10, icon: $r('app.media.background') })
            .padding(18)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Gauge({}) {
            }
            .value(50)
            .startAngle(210)
            .endAngle(150)
            .colors([[new LinearGradient([{ color: "#deb6fb", offset: 0 }, { color: "#ac49f5", offset: 1 }]), 9],
              [new LinearGradient([{ color: "#bbb7fc", offset: 0 }, { color: "#564af7", offset: 1 }]), 8],
              [new LinearGradient([{ color: "#f5b5c2", offset: 0 }, { color: "#e64566", offset: 1 }]), 7],
              [new LinearGradient([{ color: "#f8c5a6", offset: 0 }, { color: "#ed6f21", offset: 1 }]), 6],
              [new LinearGradient([{ color: "#fceb99", offset: 0 }, { color: "#f7ce00", offset: 1 }]), 5],
              [new LinearGradient([{ color: "#dbefa5", offset: 0 }, { color: "#a5d61d", offset: 1 }]), 4],
              [new LinearGradient([{ color: "#c1e4be", offset: 0 }, { color: "#64bb5c", offset: 1 }]), 3],
              [new LinearGradient([{ color: "#c0ece5", offset: 0 }, { color: "#61cfbe", offset: 1 }]), 2],
              [new LinearGradient([{ color: "#b5e0f4", offset: 0 }, { color: "#46b1e3", offset: 1 }]), 1]])
            .width(150)
            .height(150)
            .strokeWidth(18)
            .trackShadow({ radius: 7, offsetX: 7, offsetY: 7 })
            .description(this.descriptionBuilder)
            .indicator({ space: 10, icon: $r('app.media.background') })
            .padding(18)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Gauge({}) {
            }
            .value(50)
            .startAngle(210)
            .endAngle(150)
            .colors([[new LinearGradient([{ color: "#deb6fb", offset: 0 }, { color: "#ac49f5", offset: 1 }]), 9],
              [new LinearGradient([{ color: "#bbb7fc", offset: 0 }, { color: "#564af7", offset: 1 }]), 8],
              [new LinearGradient([{ color: "#f5b5c2", offset: 0 }, { color: "#e64566", offset: 1 }]), 7],
              [new LinearGradient([{ color: "#f8c5a6", offset: 0 }, { color: "#ed6f21", offset: 1 }]), 6],
              [new LinearGradient([{ color: "#fceb99", offset: 0 }, { color: "#f7ce00", offset: 1 }]), 5],
              [new LinearGradient([{ color: "#dbefa5", offset: 0 }, { color: "#a5d61d", offset: 1 }]), 4],
              [new LinearGradient([{ color: "#c1e4be", offset: 0 }, { color: "#64bb5c", offset: 1 }]), 3],
              [new LinearGradient([{ color: "#c0ece5", offset: 0 }, { color: "#61cfbe", offset: 1 }]), 2],
              [new LinearGradient([{ color: "#b5e0f4", offset: 0 }, { color: "#46b1e3", offset: 1 }]), 1]])
            .width(150)
            .height(150)
            .strokeWidth(18)
            .trackShadow({ radius: 7, offsetX: 7, offsetY: 7 })
            .description(this.descriptionBuilder)
            .indicator({ space: 10, icon: $r('app.media.background') })
            .padding(18)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Gauge({}) {
            }
            .value(50)
            .startAngle(210)
            .endAngle(150)
            .colors([[new LinearGradient([{ color: "#deb6fb", offset: 0 }, { color: "#ac49f5", offset: 1 }]), 9],
              [new LinearGradient([{ color: "#bbb7fc", offset: 0 }, { color: "#564af7", offset: 1 }]), 8],
              [new LinearGradient([{ color: "#f5b5c2", offset: 0 }, { color: "#e64566", offset: 1 }]), 7],
              [new LinearGradient([{ color: "#f8c5a6", offset: 0 }, { color: "#ed6f21", offset: 1 }]), 6],
              [new LinearGradient([{ color: "#fceb99", offset: 0 }, { color: "#f7ce00", offset: 1 }]), 5],
              [new LinearGradient([{ color: "#dbefa5", offset: 0 }, { color: "#a5d61d", offset: 1 }]), 4],
              [new LinearGradient([{ color: "#c1e4be", offset: 0 }, { color: "#64bb5c", offset: 1 }]), 3],
              [new LinearGradient([{ color: "#c0ece5", offset: 0 }, { color: "#61cfbe", offset: 1 }]), 2],
              [new LinearGradient([{ color: "#b5e0f4", offset: 0 }, { color: "#46b1e3", offset: 1 }]), 1]])
            .width(150)
            .height(150)
            .strokeWidth(18)
            .trackShadow({ radius: 7, offsetX: 7, offsetY: 7 })
            .description(this.descriptionBuilder)
            .indicator({ space: 10, icon: $r('app.media.background') })
            .padding(18)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Gauge({}) {
            }
            .value(50)
            .startAngle(210)
            .endAngle(150)
            .colors([[new LinearGradient([{ color: "#deb6fb", offset: 0 }, { color: "#ac49f5", offset: 1 }]), 9],
              [new LinearGradient([{ color: "#bbb7fc", offset: 0 }, { color: "#564af7", offset: 1 }]), 8],
              [new LinearGradient([{ color: "#f5b5c2", offset: 0 }, { color: "#e64566", offset: 1 }]), 7],
              [new LinearGradient([{ color: "#f8c5a6", offset: 0 }, { color: "#ed6f21", offset: 1 }]), 6],
              [new LinearGradient([{ color: "#fceb99", offset: 0 }, { color: "#f7ce00", offset: 1 }]), 5],
              [new LinearGradient([{ color: "#dbefa5", offset: 0 }, { color: "#a5d61d", offset: 1 }]), 4],
              [new LinearGradient([{ color: "#c1e4be", offset: 0 }, { color: "#64bb5c", offset: 1 }]), 3],
              [new LinearGradient([{ color: "#c0ece5", offset: 0 }, { color: "#61cfbe", offset: 1 }]), 2],
              [new LinearGradient([{ color: "#b5e0f4", offset: 0 }, { color: "#46b1e3", offset: 1 }]), 1]])
            .width(150)
            .height(150)
            .strokeWidth(18)
            .trackShadow({ radius: 7, offsetX: 7, offsetY: 7 })
            .description(this.descriptionBuilder)
            .indicator({ space: 10, icon: $r('app.media.background') })
            .padding(18)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Gauge({}) {
            }
            .value(50)
            .startAngle(210)
            .endAngle(150)
            .colors([[new LinearGradient([{ color: "#deb6fb", offset: 0 }, { color: "#ac49f5", offset: 1 }]), 9],
              [new LinearGradient([{ color: "#bbb7fc", offset: 0 }, { color: "#564af7", offset: 1 }]), 8],
              [new LinearGradient([{ color: "#f5b5c2", offset: 0 }, { color: "#e64566", offset: 1 }]), 7],
              [new LinearGradient([{ color: "#f8c5a6", offset: 0 }, { color: "#ed6f21", offset: 1 }]), 6],
              [new LinearGradient([{ color: "#fceb99", offset: 0 }, { color: "#f7ce00", offset: 1 }]), 5],
              [new LinearGradient([{ color: "#dbefa5", offset: 0 }, { color: "#a5d61d", offset: 1 }]), 4],
              [new LinearGradient([{ color: "#c1e4be", offset: 0 }, { color: "#64bb5c", offset: 1 }]), 3],
              [new LinearGradient([{ color: "#c0ece5", offset: 0 }, { color: "#61cfbe", offset: 1 }]), 2],
              [new LinearGradient([{ color: "#b5e0f4", offset: 0 }, { color: "#46b1e3", offset: 1 }]), 1]])
            .width(150)
            .height(150)
            .strokeWidth(18)
            .trackShadow({ radius: 7, offsetX: 7, offsetY: 7 })
            .description(this.descriptionBuilder)
            .indicator({ space: 10, icon: $r('app.media.background') })
            .padding(18)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Gauge({}) {
            }
            .value(50)
            .startAngle(210)
            .endAngle(150)
            .colors([[new LinearGradient([{ color: "#deb6fb", offset: 0 }, { color: "#ac49f5", offset: 1 }]), 9],
              [new LinearGradient([{ color: "#bbb7fc", offset: 0 }, { color: "#564af7", offset: 1 }]), 8],
              [new LinearGradient([{ color: "#f5b5c2", offset: 0 }, { color: "#e64566", offset: 1 }]), 7],
              [new LinearGradient([{ color: "#f8c5a6", offset: 0 }, { color: "#ed6f21", offset: 1 }]), 6],
              [new LinearGradient([{ color: "#fceb99", offset: 0 }, { color: "#f7ce00", offset: 1 }]), 5],
              [new LinearGradient([{ color: "#dbefa5", offset: 0 }, { color: "#a5d61d", offset: 1 }]), 4],
              [new LinearGradient([{ color: "#c1e4be", offset: 0 }, { color: "#64bb5c", offset: 1 }]), 3],
              [new LinearGradient([{ color: "#c0ece5", offset: 0 }, { color: "#61cfbe", offset: 1 }]), 2],
              [new LinearGradient([{ color: "#b5e0f4", offset: 0 }, { color: "#46b1e3", offset: 1 }]), 1]])
            .width(150)
            .height(150)
            .strokeWidth(18)
            .trackShadow({ radius: 7, offsetX: 7, offsetY: 7 })
            .description(this.descriptionBuilder)
            .indicator({ space: 10, icon: $r('app.media.background') })
            .padding(18)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Gauge({}) {
            }
            .value(50)
            .startAngle(210)
            .endAngle(150)
            .colors([[new LinearGradient([{ color: "#deb6fb", offset: 0 }, { color: "#ac49f5", offset: 1 }]), 9],
              [new LinearGradient([{ color: "#bbb7fc", offset: 0 }, { color: "#564af7", offset: 1 }]), 8],
              [new LinearGradient([{ color: "#f5b5c2", offset: 0 }, { color: "#e64566", offset: 1 }]), 7],
              [new LinearGradient([{ color: "#f8c5a6", offset: 0 }, { color: "#ed6f21", offset: 1 }]), 6],
              [new LinearGradient([{ color: "#fceb99", offset: 0 }, { color: "#f7ce00", offset: 1 }]), 5],
              [new LinearGradient([{ color: "#dbefa5", offset: 0 }, { color: "#a5d61d", offset: 1 }]), 4],
              [new LinearGradient([{ color: "#c1e4be", offset: 0 }, { color: "#64bb5c", offset: 1 }]), 3],
              [new LinearGradient([{ color: "#c0ece5", offset: 0 }, { color: "#61cfbe", offset: 1 }]), 2],
              [new LinearGradient([{ color: "#b5e0f4", offset: 0 }, { color: "#46b1e3", offset: 1 }]), 1]])
            .width(150)
            .height(150)
            .strokeWidth(18)
            .trackShadow({ radius: 7, offsetX: 7, offsetY: 7 })
            .description(this.descriptionBuilder)
            .indicator({ space: 10, icon: $r('app.media.background') })
            .padding(18)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Gauge({}) {
            }
            .value(50)
            .startAngle(210)
            .endAngle(150)
            .colors([[new LinearGradient([{ color: "#deb6fb", offset: 0 }, { color: "#ac49f5", offset: 1 }]), 9],
              [new LinearGradient([{ color: "#bbb7fc", offset: 0 }, { color: "#564af7", offset: 1 }]), 8],
              [new LinearGradient([{ color: "#f5b5c2", offset: 0 }, { color: "#e64566", offset: 1 }]), 7],
              [new LinearGradient([{ color: "#f8c5a6", offset: 0 }, { color: "#ed6f21", offset: 1 }]), 6],
              [new LinearGradient([{ color: "#fceb99", offset: 0 }, { color: "#f7ce00", offset: 1 }]), 5],
              [new LinearGradient([{ color: "#dbefa5", offset: 0 }, { color: "#a5d61d", offset: 1 }]), 4],
              [new LinearGradient([{ color: "#c1e4be", offset: 0 }, { color: "#64bb5c", offset: 1 }]), 3],
              [new LinearGradient([{ color: "#c0ece5", offset: 0 }, { color: "#61cfbe", offset: 1 }]), 2],
              [new LinearGradient([{ color: "#b5e0f4", offset: 0 }, { color: "#46b1e3", offset: 1 }]), 1]])
            .width(150)
            .height(150)
            .strokeWidth(18)
            .trackShadow({ radius: 7, offsetX: 7, offsetY: 7 })
            .description(this.descriptionBuilder)
            .indicator({ space: 10, icon: $r('app.media.background') })
            .padding(18)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Gauge({}) {
            }
            .value(50)
            .startAngle(210)
            .endAngle(150)
            .colors([[new LinearGradient([{ color: "#deb6fb", offset: 0 }, { color: "#ac49f5", offset: 1 }]), 9],
              [new LinearGradient([{ color: "#bbb7fc", offset: 0 }, { color: "#564af7", offset: 1 }]), 8],
              [new LinearGradient([{ color: "#f5b5c2", offset: 0 }, { color: "#e64566", offset: 1 }]), 7],
              [new LinearGradient([{ color: "#f8c5a6", offset: 0 }, { color: "#ed6f21", offset: 1 }]), 6],
              [new LinearGradient([{ color: "#fceb99", offset: 0 }, { color: "#f7ce00", offset: 1 }]), 5],
              [new LinearGradient([{ color: "#dbefa5", offset: 0 }, { color: "#a5d61d", offset: 1 }]), 4],
              [new LinearGradient([{ color: "#c1e4be", offset: 0 }, { color: "#64bb5c", offset: 1 }]), 3],
              [new LinearGradient([{ color: "#c0ece5", offset: 0 }, { color: "#61cfbe", offset: 1 }]), 2],
              [new LinearGradient([{ color: "#b5e0f4", offset: 0 }, { color: "#46b1e3", offset: 1 }]), 1]])
            .width(150)
            .height(150)
            .strokeWidth(18)
            .trackShadow({ radius: 7, offsetX: 7, offsetY: 7 })
            .description(this.descriptionBuilder)
            .indicator({ space: 10, icon: $r('app.media.background') })
            .padding(18)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Gauge({}) {
            }
            .value(50)
            .startAngle(210)
            .endAngle(150)
            .colors([[new LinearGradient([{ color: "#deb6fb", offset: 0 }, { color: "#ac49f5", offset: 1 }]), 9],
              [new LinearGradient([{ color: "#bbb7fc", offset: 0 }, { color: "#564af7", offset: 1 }]), 8],
              [new LinearGradient([{ color: "#f5b5c2", offset: 0 }, { color: "#e64566", offset: 1 }]), 7],
              [new LinearGradient([{ color: "#f8c5a6", offset: 0 }, { color: "#ed6f21", offset: 1 }]), 6],
              [new LinearGradient([{ color: "#fceb99", offset: 0 }, { color: "#f7ce00", offset: 1 }]), 5],
              [new LinearGradient([{ color: "#dbefa5", offset: 0 }, { color: "#a5d61d", offset: 1 }]), 4],
              [new LinearGradient([{ color: "#c1e4be", offset: 0 }, { color: "#64bb5c", offset: 1 }]), 3],
              [new LinearGradient([{ color: "#c0ece5", offset: 0 }, { color: "#61cfbe", offset: 1 }]), 2],
              [new LinearGradient([{ color: "#b5e0f4", offset: 0 }, { color: "#46b1e3", offset: 1 }]), 1]])
            .width(150)
            .height(150)
            .strokeWidth(18)
            .trackShadow({ radius: 7, offsetX: 7, offsetY: 7 })
            .description(this.descriptionBuilder)
            .indicator({ space: 10, icon: $r('app.media.background') })
            .padding(18)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Gauge({}) {
            }
            .value(50)
            .startAngle(210)
            .endAngle(150)
            .colors([[new LinearGradient([{ color: "#deb6fb", offset: 0 }, { color: "#ac49f5", offset: 1 }]), 9],
              [new LinearGradient([{ color: "#bbb7fc", offset: 0 }, { color: "#564af7", offset: 1 }]), 8],
              [new LinearGradient([{ color: "#f5b5c2", offset: 0 }, { color: "#e64566", offset: 1 }]), 7],
              [new LinearGradient([{ color: "#f8c5a6", offset: 0 }, { color: "#ed6f21", offset: 1 }]), 6],
              [new LinearGradient([{ color: "#fceb99", offset: 0 }, { color: "#f7ce00", offset: 1 }]), 5],
              [new LinearGradient([{ color: "#dbefa5", offset: 0 }, { color: "#a5d61d", offset: 1 }]), 4],
              [new LinearGradient([{ color: "#c1e4be", offset: 0 }, { color: "#64bb5c", offset: 1 }]), 3],
              [new LinearGradient([{ color: "#c0ece5", offset: 0 }, { color: "#61cfbe", offset: 1 }]), 2],
              [new LinearGradient([{ color: "#b5e0f4", offset: 0 }, { color: "#46b1e3", offset: 1 }]), 1]])
            .width(150)
            .height(150)
            .strokeWidth(18)
            .trackShadow({ radius: 7, offsetX: 7, offsetY: 7 })
            .description(this.descriptionBuilder)
            .indicator({ space: 10, icon: $r('app.media.background') })
            .padding(18)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Gauge({}) {
            }
            .value(50)
            .startAngle(210)
            .endAngle(150)
            .colors([[new LinearGradient([{ color: "#deb6fb", offset: 0 }, { color: "#ac49f5", offset: 1 }]), 9],
              [new LinearGradient([{ color: "#bbb7fc", offset: 0 }, { color: "#564af7", offset: 1 }]), 8],
              [new LinearGradient([{ color: "#f5b5c2", offset: 0 }, { color: "#e64566", offset: 1 }]), 7],
              [new LinearGradient([{ color: "#f8c5a6", offset: 0 }, { color: "#ed6f21", offset: 1 }]), 6],
              [new LinearGradient([{ color: "#fceb99", offset: 0 }, { color: "#f7ce00", offset: 1 }]), 5],
              [new LinearGradient([{ color: "#dbefa5", offset: 0 }, { color: "#a5d61d", offset: 1 }]), 4],
              [new LinearGradient([{ color: "#c1e4be", offset: 0 }, { color: "#64bb5c", offset: 1 }]), 3],
              [new LinearGradient([{ color: "#c0ece5", offset: 0 }, { color: "#61cfbe", offset: 1 }]), 2],
              [new LinearGradient([{ color: "#b5e0f4", offset: 0 }, { color: "#46b1e3", offset: 1 }]), 1]])
            .width(150)
            .height(150)
            .strokeWidth(18)
            .trackShadow({ radius: 7, offsetX: 7, offsetY: 7 })
            .description(this.descriptionBuilder)
            .indicator({ space: 10, icon: $r('app.media.background') })
            .padding(18)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Gauge({}) {
            }
            .value(undefined)
            .startAngle(undefined)
            .endAngle(undefined)
            .colors(undefined)
            .width(150)
            .height(150)
            .strokeWidth(undefined)
            .trackShadow(undefined)
            .description(undefined)
            .indicator(undefined)
          })
        }
      }
    }
  }
}