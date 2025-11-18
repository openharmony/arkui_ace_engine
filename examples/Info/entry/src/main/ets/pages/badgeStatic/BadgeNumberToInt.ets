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
  Text,
  TextAttribute,
  Column,
  Component,
  Button,
  ButtonAttribute,
  ClickEvent,
  Color,
  ImageSpan,
  TextAlign,
  Entry,
  AttributeModifier,
  Image,
  ImageAttribute,
  Progress,
  ProgressAttribute,
  PatternLock,
  LoadingProgress,
  TextClock,
  TextTimer,
  Counter,
  QRCode,
  DataPanel,
  Gauge,
  ProgressType,
  ProgressStyleOptions,
  CapsuleStyleOptions,
  ResourceColor,
  Scroll,
  VoidCallback,
  ImageRenderMode,
  Badge,
  BadgeStyle,
  BadgeParamWithNumber ,
  $r
} from '@ohos.arkui.component' // TextAttribute should be insert by ui-plugins
import { State } from '@ohos.arkui.stateManagement'
import hilog from '@ohos.hilog'
import { LengthMetrics } from "arkui.Graphics";

import {
  AttributeUpdater,
  CommonModifier,
  ButtonModifier,
  TextModifier,
  ImageModifier,
  ProgressModifier,
  PatternLockModifier,
  LoadingProgressModifier,
  TextClockModifier,
  CounterModifier,
  TextTimerModifier,
  QRCodeModifier,
  DataPanelModifier,
  GaugeModifier
} from '@ohos.arkui.modifier'

@Entry
@Component
struct MyStateSample {

  build() {
    Scroll() {
      Column(undefined) {
        Text("123")
        Badge({
          count: 10,
          style: {
            fontSize: 20,
            badgeSize: 30
          } as BadgeStyle
        } as BadgeParamWithNumber ) {
          Text("123")
        }

        Badge({
          count: 10,
          style: {
            fontSize: 25,
            badgeSize: 35
          } as BadgeStyle
        } as BadgeParamWithNumber ) {
          Text("123")
        }
      }
    }
  }
}
