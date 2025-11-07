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
  Resource,
  LinearGradient,
  FontWeight,
  TextAlign,
  Builder,
  $r,
  ContentModifier,
  GaugeConfiguration,
  WrappedBuilder,
  Color,
  DataPanel,
  DataPanelType,
  LinearGradient,
  ResourceColor,
  DataPanelConfiguration,
  DataPanelConfiguration,
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
  DataPanel,
  DataPanelConfiguration,
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
  DataPanel,
  DataPanelConfiguration,
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


type DataPanelBuilder =
@
Builder(config:
DataPanelConfiguration
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
struct DataPanelTest {
  public dataPanelValues: Double[] = [12.3, 21.1, 13.4, 35.2, 26.0, 32.0] as Double[]
  public valueArr: Double[] = [10, 10, 10, 10, 10, 10, 10, 10, 10] as Double[]
  public values1: Double[] = [20, 20, 20, 20] as Double[]
  public color1: LinearGradient =
    new LinearGradient([{ color: "#65EEC9A3", offset: 0 }, { color: "#FFEF629F", offset: 1 }])
  public color2: LinearGradient =
    new LinearGradient([{ color: "#FF67F9D4", offset: 0 }, { color: "#FFFF9554", offset: 1 }])
  public color3: LinearGradient =
    new LinearGradient([{ color: "#FF67F9D4", offset: 0 }, { color: "#FFFF9554", offset: 1 }])
  public color4: LinearGradient =
    new LinearGradient([{ color: "#FF67F9D4", offset: 0 }, { color: "#FFFF9554", offset: 1 }])
  public colorShadow1: LinearGradient =
    new LinearGradient([{ color: "#65EEC9A3", offset: 0 }, { color: "#65EF629F", offset: 1 }])
  public colorShadow2: LinearGradient =
    new LinearGradient([{ color: "#65e26709", offset: 0 }, { color: "#65efbd08", offset: 1 }])
  public colorShadow3: LinearGradient =
    new LinearGradient([{ color: "#6572B513", offset: 0 }, { color: "#6508efa6", offset: 1 }])
  public colorShadow4: LinearGradient =
    new LinearGradient([{ color: "#65ed08f5", offset: 0 }, { color: "#65ef0849", offset: 1 }])
  public colorArray: Array<LinearGradient | Color | Double | String | Resource> =
    [this.color1, this.color2, this.color3, this.color4] as Array<LinearGradient | Color | Double | String | Resource>
  public bgColor: string = '#08182431'
  public offsetX: number = 15
  public offsetY: number = 15
  public radius: number = 5
  public shadowColorArray: Array<LinearGradient | Color | Double | String | Resource> =
    [this.colorShadow1, this.colorShadow2, this.colorShadow3,
      this.colorShadow4] as Array<LinearGradient | Color | Double | String | Resource>;

  build() {
    Scroll() {
      Flex({ wrap: FlexWrap.Wrap, justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign.Center }) {
        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            DataPanel({ values: this.values1, max: 140, type: DataPanelType.Circle })
              .trackShadow({
                radius: this.radius,
                colors: this.shadowColorArray,
                offsetX: this.offsetX,
                offsetY: this.offsetY
              })
              .width(168)
              .height(168)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            DataPanel({ values: this.values1, max: 140, type: DataPanelType.Circle })
              .contentModifier(new MyDataPanelStyle([12.6, 21.1, 13.4, 35.2, 26.0, 68.0]))
              .width(168)
              .height(168)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            DataPanel({ values: this.values1, max: 140, type: DataPanelType.Circle })
              .closeEffect(true)
              .width(168)
              .height(168)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            DataPanel({ values: this.values1, max: 140, type: DataPanelType.Circle })
              .valueColors(this.colorArray)
              .strokeWidth(30)
              .width(168)
              .height(168)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            DataPanel({ values: this.values1, max: 140, type: DataPanelType.Circle })
              .trackBackgroundColor(this.bgColor)
              .strokeWidth(30)
              .width(168)
              .height(168)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            DataPanel({ values: this.values1, max: 140, type: DataPanelType.Circle })
              .trackShadow({
                radius: this.radius,
                colors: this.shadowColorArray,
                offsetX: this.offsetX,
                offsetY: this.offsetY
              })
              .closeEffect(true)
              .valueColors(this.colorArray)
              .trackBackgroundColor(this.bgColor)
              .strokeWidth(30)
              .width(168)
              .height(168)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            DataPanel({ values: this.values1, max: 140, type: DataPanelType.Circle })
              .trackShadow({
                radius: this.radius,
                colors: this.shadowColorArray,
                offsetX: this.offsetX,
                offsetY: this.offsetY
              })
              .closeEffect(true)
              .valueColors(this.colorArray)
              .trackBackgroundColor(this.bgColor)
              .strokeWidth(30)
              .width(168)
              .height(168)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            DataPanel({ values: this.values1, max: 140, type: DataPanelType.Circle })
              .trackShadow({
                radius: this.radius,
                colors: this.shadowColorArray,
                offsetX: this.offsetX,
                offsetY: this.offsetY
              })
              .closeEffect(true)
              .valueColors(this.colorArray)
              .trackBackgroundColor(this.bgColor)
              .strokeWidth(30)
              .width(168)
              .height(168)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            DataPanel({ values: this.values1, max: 140, type: DataPanelType.Circle })
              .trackShadow({
                radius: this.radius,
                colors: this.shadowColorArray,
                offsetX: this.offsetX,
                offsetY: this.offsetY
              })
              .closeEffect(true)
              .valueColors(this.colorArray)
              .trackBackgroundColor(this.bgColor)
              .strokeWidth(30)
              .width(168)
              .height(168)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            DataPanel({ values: this.values1, max: 140, type: DataPanelType.Circle })
              .trackShadow({
                radius: this.radius,
                colors: this.shadowColorArray,
                offsetX: this.offsetX,
                offsetY: this.offsetY
              })
              .closeEffect(true)
              .valueColors(this.colorArray)
              .trackBackgroundColor(this.bgColor)
              .strokeWidth(30)
              .width(168)
              .height(168)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            DataPanel({ values: this.values1, max: 140, type: DataPanelType.Circle })
              .trackShadow({
                radius: this.radius,
                colors: this.shadowColorArray,
                offsetX: this.offsetX,
                offsetY: this.offsetY
              })
              .closeEffect(true)
              .valueColors(this.colorArray)
              .trackBackgroundColor(this.bgColor)
              .strokeWidth(30)
              .width(168)
              .height(168)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            DataPanel({ values: this.values1, max: 140, type: DataPanelType.Circle })
              .trackShadow({
                radius: this.radius,
                colors: this.shadowColorArray,
                offsetX: this.offsetX,
                offsetY: this.offsetY
              })
              .closeEffect(true)
              .valueColors(this.colorArray)
              .trackBackgroundColor(this.bgColor)
              .strokeWidth(30)
              .width(168)
              .height(168)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            DataPanel({ values: this.values1, max: 140, type: DataPanelType.Circle })
              .trackShadow({
                radius: this.radius,
                colors: this.shadowColorArray,
                offsetX: this.offsetX,
                offsetY: this.offsetY
              })
              .closeEffect(true)
              .valueColors(this.colorArray)
              .trackBackgroundColor(this.bgColor)
              .strokeWidth(30)
              .width(168)
              .height(168)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            DataPanel({ values: this.values1, max: 140, type: DataPanelType.Circle })
              .trackShadow({
                radius: this.radius,
                colors: this.shadowColorArray,
                offsetX: this.offsetX,
                offsetY: this.offsetY
              })
              .closeEffect(true)
              .valueColors(this.colorArray)
              .trackBackgroundColor(this.bgColor)
              .strokeWidth(30)
              .width(168)
              .height(168)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            DataPanel({ values: this.values1, max: 140, type: DataPanelType.Circle })
              .trackShadow({
                radius: this.radius,
                colors: this.shadowColorArray,
                offsetX: this.offsetX,
                offsetY: this.offsetY
              })
              .closeEffect(true)
              .valueColors(this.colorArray)
              .trackBackgroundColor(this.bgColor)
              .strokeWidth(30)
              .width(168)
              .height(168)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            DataPanel({ values: this.values1, max: 140, type: DataPanelType.Circle })
              .trackShadow({
                radius: this.radius,
                colors: this.shadowColorArray,
                offsetX: this.offsetX,
                offsetY: this.offsetY
              })
              .closeEffect(true)
              .valueColors(this.colorArray)
              .trackBackgroundColor(this.bgColor)
              .strokeWidth(30)
              .width(168)
              .height(168)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            DataPanel({ values: this.values1, max: 140, type: DataPanelType.Circle })
              .trackShadow({
                radius: this.radius,
                colors: this.shadowColorArray,
                offsetX: this.offsetX,
                offsetY: this.offsetY
              })
              .closeEffect(true)
              .valueColors(this.colorArray)
              .trackBackgroundColor(this.bgColor)
              .strokeWidth(30)
              .width(168)
              .height(168)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            DataPanel({ values: this.values1, max: 140, type: DataPanelType.Circle })
              .trackShadow({
                radius: this.radius,
                colors: this.shadowColorArray,
                offsetX: this.offsetX,
                offsetY: this.offsetY
              })
              .closeEffect(true)
              .valueColors(this.colorArray)
              .trackBackgroundColor(this.bgColor)
              .strokeWidth(30)
              .width(168)
              .height(168)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            DataPanel({ values: this.values1, max: 140, type: DataPanelType.Circle })
              .trackShadow({
                radius: this.radius,
                colors: this.shadowColorArray,
                offsetX: this.offsetX,
                offsetY: this.offsetY
              })
              .closeEffect(true)
              .valueColors(this.colorArray)
              .trackBackgroundColor(this.bgColor)
              .strokeWidth(30)
              .width(168)
              .height(168)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            DataPanel({ values: this.values1, max: 140, type: DataPanelType.Circle })
              .trackShadow(undefined)
              .closeEffect(undefined)
              .valueColors(undefined)
              .trackBackgroundColor(undefined)
              .strokeWidth(undefined)
              .width(168)
              .height(168)
          })
        }
      }
    }
  }
}

class MyDataPanelStyle implements ContentModifier<DataPanelConfiguration> {
  values: number[] = {}

  constructor(values: number[]) {
    this.values = values
  }

  applyContent(): WrappedBuilder<DataPanelBuilder> {
    return wrapBuilder(buildDataPanel);
  }
}

@Builder
function buildDataPanel(config: DataPanelConfiguration): void {
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
