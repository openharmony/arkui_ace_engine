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
  CircleStyleOptions
} from '@ohos.arkui.component'
import { State } from '@ohos.arkui.stateManagement'
import hilog from '@ohos.hilog'
import { forEachItems20, forEachItems100 } from '../Utils/Jarvis';
import { ParallelOption, ParallelizeUI } from '@ohos.arkui.Parallelize';

@Entry
@Component
struct PatternLockTest {
  @State passwords: number[] = [] as number[];
  @State message: string = 'please input password!';
  private patternLockController: PatternLockController = new PatternLockController();

  build() {
    Scroll() {
      Flex({ wrap: FlexWrap.Wrap, justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign.Center }) {
        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Text('1' + '-' + index + '>')
            PatternLock(this.patternLockController)
              .sideLength(200)
              .circleRadius(9)
              .pathStrokeWidth(5)
              .activeColor('#ffcf1e1e')
              .selectedColor('#ff98e30e')
              .pathColor('#ff1c1fe0')
              .regularColor('#ffe9de0e')
              .backgroundColor('#ff0ef1b1')
              .autoReset(true)
              .skipUnselectedPoint(false)
              .onDotConnect((index: number) => {
                console.info('onDotConnect index: ' + index);
              })
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Text('2' + '-' + index + '>')
            PatternLock(this.patternLockController)
              .sideLength(200)
              .circleRadius(9)
              .pathStrokeWidth(5)
              .activeColor('#ffcf1e1e')
              .selectedColor('#ff98e30e')
              .pathColor('#ff1c1fe0')
              .regularColor('#ffe9de0e')
              .backgroundColor('#ff0ef1b1')
              .autoReset(true)
              .activateCircleStyle({
                color: '#ffb009f8',
                enableWaveEffect: true
              } as CircleStyleOptions)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Text('3' + '-' + index + '>')
            PatternLock(this.patternLockController)
              .sideLength(undefined)
              .circleRadius(undefined)
              .pathStrokeWidth(undefined)
              .activeColor(undefined)
              .selectedColor(undefined)
              .pathColor(undefined)
              .regularColor(undefined)
              .backgroundColor(undefined)
              .autoReset(undefined)
              .skipUnselectedPoint(undefined)
              .onDotConnect((index: number) => {
                console.info('onDotConnect index: ' + index);
              })
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Text('4' + '-' + index + '>')
            PatternLock(this.patternLockController)
              .sideLength(undefined)
              .circleRadius(undefined)
              .pathStrokeWidth(undefined)
              .activeColor(undefined)
              .selectedColor(undefined)
              .pathColor(undefined)
              .backgroundColor(undefined)
              .autoReset(undefined)
              .activateCircleStyle(undefined)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Text('5' + '-' + index + '>')
            PatternLock(this.patternLockController)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Text('6' + '-' + index + '>')
            PatternLock(this.patternLockController)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Text('7' + '-' + index + '>')
            PatternLock(this.patternLockController)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Text('8' + '-' + index + '>')
            PatternLock(this.patternLockController)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Text('9' + '-' + index + '>')
            PatternLock(this.patternLockController)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Text('10' + '-' + index + '>')
            PatternLock(this.patternLockController)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Text('11' + '-' + index + '>')
            PatternLock(this.patternLockController)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Text('12' + '-' + index + '>')
            PatternLock(this.patternLockController)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Text('13' + '-' + index + '>')
            PatternLock(this.patternLockController)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Text('14' + '-' + index + '>')
            PatternLock(this.patternLockController)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Text('15' + '-' + index + '>')
            PatternLock(this.patternLockController)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Text('16' + '-' + index + '>')
            PatternLock(this.patternLockController)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Text('17' + '-' + index + '>')
            PatternLock(this.patternLockController)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Text('18' + '-' + index + '>')
            PatternLock(this.patternLockController)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Text('19' + '-' + index + '>')
            PatternLock(this.patternLockController)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Text('20' + '-' + index + '>')
            PatternLock(this.patternLockController)
          })
        }

        ParallelizeUI({ enable: true }) {
          ForEach(forEachItems100, (item: Int, index: Double) => {
            Text('21' + '-' + index + '>')
            PatternLock(this.patternLockController)
          })
        }
      }
    }
  }
}
