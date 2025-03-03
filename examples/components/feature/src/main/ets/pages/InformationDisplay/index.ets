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
import { AdvancedCounterBootcamp } from './AdvancedCounterBootcamp';
import { AlphabetIndexerBootcamp } from './AlphabetIndexerBootcamp';
import { BadgeBootcamp } from './BadgeBootcamp';
import { ChipBootcamp } from './ChipBootcamp';
import { ChipGroupBootcamp } from './ChipGroupBootcamp';
import { CounterBootcamp } from './CounterBootcamp';
import { DataPanelBootcamp } from './DataPanelBootcamp';
import { GaugeBootcamp } from './GaugeBootcamp';
import { LoadingProgressBootcamp } from './LoadingProgressBootcamp';
import { PatternLockBootcamp } from './PatternLockBootcamp';
import { PopupBootcamp } from './PopupBootcamp';
import { ProgressLockBootcamp } from './ProgressBootcamp';
import { QRCodeBootcamp } from './QRCodeBootcamp';
import { TextClockBootcamp } from './TextClockBootcamp';
import { TextTimerBootcamp } from './TextTimerBootcamp';
import { ToastBootcamp } from './ToastBootcamp';


export const informationDisplayRoute: RouteGroup = {
  name: 'InformationDisplay',
  label: '信息展示',
  children: [
    { name: 'AlphabetIndexer', label: '索引条/AlphabetIndexer' },
    { name: 'Badge', label: '信息标记/Badge' },
    { name: 'Chip', label: '操作块/Chip' },
    { name: 'ChipGroup', label: '操作块群组/ChipGroup' },
    { name: 'counter', label: '计数器/counter' },
    { name: 'DataPanel', label: '数据面板/DataPanel' },
    { name: 'Gauge', label: '数据量规图/Gauge' },
    { name: 'LoadingProgress', label: '加载进度/LoadingProgress' },
    { name: 'PatternLock', label: '图案密码锁/PatternLock' },
    { name: 'Progress', label: '进度条/Progress' },
    { name: 'Popup', label: '气泡/Popup' },
    { name: 'QRCode', label: '二维码/QRCode' },
    { name: 'TextClock', label: '文本时钟/TextClock' },
    { name: 'TextTimer', label: '文本计时器/TextTimer' },
    { name: 'AdvancedCounter', label: '计数器/AdvancedCounter' },
    { name: 'Toast', label: '即时反馈/Toast' }

  ]
};

@Builder
export function informationDisplayDestination(name: string, route: Route) {
  if (name === 'InformationDisplay/AlphabetIndexer') {
    AlphabetIndexerBootcamp({title: route.label})
  }else if (name === 'InformationDisplay/Badge'){
    BadgeBootcamp({title: route.label})
  }else if (name === 'InformationDisplay/Chip'){
    ChipBootcamp({title: route.label})
  }else if (name === 'InformationDisplay/ChipGroup'){
    ChipGroupBootcamp({title: route.label})
  }else if (name === 'InformationDisplay/counter'){
    CounterBootcamp({title: route.label})
  }else if (name === 'InformationDisplay/DataPanel'){
    DataPanelBootcamp({title: route.label})
  }else if (name === 'InformationDisplay/Gauge'){
    GaugeBootcamp({title: route.label})
  }else if (name === 'InformationDisplay/LoadingProgress'){
    LoadingProgressBootcamp({title: route.label})
  }else if (name === 'InformationDisplay/PatternLock'){
    PatternLockBootcamp({title: route.label})
  }else if (name === 'InformationDisplay/Progress'){
    ProgressLockBootcamp({title: route.label})
  }else if (name === 'InformationDisplay/Popup'){
    PopupBootcamp({title: route.label})
  }else if (name === 'InformationDisplay/QRCode'){
    QRCodeBootcamp({title: route.label})
  }else if (name === 'InformationDisplay/TextClock'){
    TextClockBootcamp({title: route.label})
  }else if (name === 'InformationDisplay/TextTimer'){
    TextTimerBootcamp({title: route.label})
  }else if (name === 'InformationDisplay/AdvancedCounter'){
    AdvancedCounterBootcamp({title: route.label})
  }else if (name === 'InformationDisplay/Toast'){
    ToastBootcamp({title:route.label})
  }

}
