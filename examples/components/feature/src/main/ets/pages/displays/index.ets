/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

import { Route, RouteGroup } from 'common/src/main/ets/common/route';
import { BindPopupBootcamp } from './BindPopupBootcamp';
import { ToastBootcamp } from './ToastBootcamp';
import { ImageboxGroupBootcamp } from '../displays/ImageBootcamp';
import { LoadingProgressBootcamp } from '../displays/LoadingProgressBootcamp';
import { ScrollBarBootcamp } from './ScrollBarBootcamp';
import { TextBootcamp } from './TextBootcamp';
import { TextSpanUrlBootcamp } from './TextSpanUrlBootcamp';
import { AlphabetIndexerBootcamp } from './AlphabetIndexerBootcamp'
import { BadgeBootcamp } from './BadgeBootcamp'
import { ChipGroupBootcamp } from './ChipGroupBootcamp';
import { ChipBootcamp } from './ChipBootcamp';
import { CounterBootcamp } from './CounterBootcamp';
import { AdvancedCounterBootcamp } from './AdvancedCounterBootcamp';
import { DataPanelBootcamp } from './DataPanelBootcamp';
import { GaugeBootcamp } from './GaugeBootcamp';
import { PatternLockBootcamp } from './PatternLockBootcamp'
import { QRCodeBootcamp } from './QRCodeBootcamp'

import { TextTimerBootcamp } from './TextTimerBootcamp';
import { ProgressLockBootcamp } from './ProgressBootcamp';
import { PopupBootcamp } from './PopupBootcamp';

export const displaysRoute: RouteGroup = {
  name: 'displays',
  label: '展示类',
  children: [
    { name: 'text', label: '文本/Text' },
    { name: 'bindpopup', label: '气泡/BindPopup' },
    { name: 'toast', label: '即时反馈/Toast' },
    { name: 'image', label: '图片/Image' },
    { name: 'loading-progress', label: '加载进度/LoadingProgress' },
    { name: 'scrollbar', label: '滚动条/ScrollBar' },
    { name: 'spanurl', label: '超链接/text' },
    { name: 'badge', label: '信息标记/Badge' },
    { name: 'chipGroup', label: '操作块群组/ChipGroup' },
    { name: 'chip', label: '操作块/Chip' },
    { name: 'counter', label: '计数器/Counter' },
    { name: 'advancedCounter', label: '计数器/advanced.Counter' },
    { name: 'dataPanel', label: '数据面板/DataPanel' },
    { name: 'gauge', label: '数据量规图/gauge' },
    { name: 'textTimer', label: '文本计时器/TextTimer' },
    { name: 'textTimer', label: '文本计时器/TextTimer' },
    { name: 'alphabetIndexer', label: '索引条/AlphabetIndexer' },
    { name: 'badge', label: '信息标记/Badge' },
    { name: 'chipGroup', label: '操作块群组/ChipGroup' },
    { name: 'chip', label: '操作块/Chip' },
    { name: 'counter', label: '计数器/Counter'},
    { name: 'advancedCounter', label: '计数器/advanced.Counter'},
    { name: 'dataPanel', label: '数据面板/DataPanel'},
    { name: 'gauge', label: '数据量规图/gauge' },
    { name: 'PatternLock', label: '图案密码锁/PatternLock' },
    { name: 'popup', label: '气泡/Popup' },
    { name: 'QRCode', label: '二维码/QRCode' },
    { name: 'Progress', label: '进度条/Progress' },
  ]
};

@Builder
export function DisplaysDestination(name: string, route: Route) {
  if (name === 'displays/bindpopup') {
    BindPopupBootcamp({ title: route.label })
  } else if (name === 'displays/toast') {
    ToastBootcamp({ title: route.label })
  } else if (name === 'displays/image') {
    ImageboxGroupBootcamp({ title: route.label })
  } else if (name === 'displays/loading-progress') {
    LoadingProgressBootcamp({ title: route.label })
  } else if (name === 'displays/scrollbar') {
    ScrollBarBootcamp({ title: route.label })
  } else if (name === 'displays/text') {
    TextBootcamp({ title: route.label })
  } else if (name === 'displays/spanurl') {
    TextSpanUrlBootcamp({ title: route.label })
  } else if (name === 'displays/badge') {
  } else if (name === 'displays/alphabetIndexer'){
    AlphabetIndexerBootcamp({ title: route.label })
  } else if (name === 'displays/badge'){
    BadgeBootcamp({ title: route.label })
  } else if (name === 'displays/chipGroup') {
    ChipGroupBootcamp({ title: route.label })
  } else if (name === 'displays/chip') {
    ChipBootcamp({ title: route.label })
  } else if (name === 'displays/counter') {
    CounterBootcamp({ title: route.label })
  } else if (name === 'displays/advancedCounter') {
    AdvancedCounterBootcamp({ title: route.label })
  } else if (name === 'displays/dataPanel') {
    DataPanelBootcamp({ title: route.label })
  } else if (name === 'displays/gauge') {
    GaugeBootcamp({ title: route.label })
  } else if (name === 'displays/PatternLock') {
    PatternLockBootcamp({ title: route.label })
  } else if (name === 'displays/popup') {
    PopupBootcamp({ title: route.label })
  } else if (name === 'displays/QRCode') {
    QRCodeBootcamp({ title: route.label })
  } else if (name === 'displays/textTimer') {
    TextTimerBootcamp({ title: route.label })
  } else if (name === 'displays/Progress') {
    ProgressLockBootcamp({ title: route.label })
  }
}

