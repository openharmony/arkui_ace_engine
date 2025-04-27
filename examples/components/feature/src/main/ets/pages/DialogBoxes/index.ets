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
import { ActionMenuBootcamp } from './ActionMenuBootcamp';
import { ActionSheetBootcamp } from './ActionSheetBootcamp';
import { AlertDialogBootcamp } from './AlertDialogBootcamp';
import { BindContentCoverBootcamp } from './BindContentCoverBootcamp';
import { BindContextMenuBootcamp } from './BindContextMenuBootcamp';
import { BindMenuBootcamp } from './BindMenuBootcamp';
import { BindPopupBootcamp } from './BindPopupBootcamp';
import { BindSheetBootcamp } from './BindSheetBootcamp';
import { CalendarPickerDialogBootcamp } from './CalendarPickerDialogBootcamp';
import { CustomDialogBootcamp } from './CustomDialogBootcamp';
import { DatePickerDialogBootcamp } from './DatePickerDialogBootcamp';
import { DialogBootcamp } from './DialogBootcamp';
import { promptActionCustomDialogBootcamp } from './promptActionCustomDialogBootcamp';
import { TextPickerDialogBootcamp } from './TextPickerDialogBootcamp';
import { TimePickerDialogBootcamp } from './TimePickerDialogBootcamp';


export const dialogBoxesRoute: RouteGroup = {
  name: 'DialogBoxes',
  label: '弹窗',
  children: [
    { name: 'AlertDialog', label: '警告弹窗/AlertDialog' },
    { name: 'ActionSheet', label: '列表选择弹窗/ActionSheet' },
    { name: 'CustomDialog', label: '自定义弹窗/CustomDialog' },
    { name: 'CalendarpickerDialog', label: '日历选择器弹窗/CalendarpickerDialog' },
    { name: 'DatepickerDialog', label: '日期选择器弹窗/DatepickerDialog' },
    { name: 'TimePickerDialog', label: '时间选择器弹窗/TimePickerDialog' },
    { name: 'TextpickerDialog', label: '文本选择器弹窗/TextpickerDialog' },
    { name: 'BindContentCover', label: '全模态/BindContentCover' },
    { name: 'BindSheet', label: '半模态/BindSheet' },
    { name: 'promptActionCustomDialog', label: 'promptActionCustomDialog' },
    { name: 'BindContextMenu', label: '上下文菜单/BindContextMenu' },
    { name: 'ActionMenu', label: '菜单弹窗/ActionMenu' },
    { name: 'Menu', label: '菜单/Menu' },
    { name: 'Dialog', label: '对话框/Dialog' },
    { name: 'bindPopup', label: '气泡/bindPopup' }
  ]
};

@Builder
export function dialogBoxesDestination(name: string, route: Route) {
  if (name === 'DialogBoxes/AlertDialog') {
    AlertDialogBootcamp({ title: route.label })
  } else if (name === 'DialogBoxes/ActionSheet') {
    ActionSheetBootcamp({ title: route.label })
  } else if (name === 'DialogBoxes/CustomDialog') {
    CustomDialogBootcamp({ title: route.label })
  } else if (name === 'DialogBoxes/CalendarpickerDialog') {
    CalendarPickerDialogBootcamp({ title: route.label })
  } else if (name === 'DialogBoxes/DatepickerDialog') {
    DatePickerDialogBootcamp({ title: route.label })
  } else if (name === 'DialogBoxes/TimePickerDialog') {
    TimePickerDialogBootcamp({ title: route.label })
  } else if (name === 'DialogBoxes/TextpickerDialog') {
    TextPickerDialogBootcamp({ title: route.label })
  } else if (name === 'DialogBoxes/BindContentCover') {
    BindContentCoverBootcamp({ title: route.label })
  } else if (name === 'DialogBoxes/BindSheet') {
    BindSheetBootcamp({ title: route.label })
  } else if (name === 'DialogBoxes/promptActionCustomDialog') {
    promptActionCustomDialogBootcamp({ title: route.label })
  } else if (name === 'DialogBoxes/BindContextMenu') {
    BindContextMenuBootcamp({ title: route.label })
  } else if (name === 'DialogBoxes/ActionMenu') {
    ActionMenuBootcamp({ title: route.label })
  } else if (name === 'DialogBoxes/Menu') {
    BindMenuBootcamp({ title: route.label })
  } else if (name === 'DialogBoxes/Dialog') {
    DialogBootcamp({ title: route.label })
  } else if (name === 'DialogBoxes/bindPopup') {
    BindPopupBootcamp({ title: route.label })
  }
}
