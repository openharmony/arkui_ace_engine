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
import { ScrollBarBootcamp } from './ScrollBarBootcamp';

export const displaysRoute: RouteGroup = {
  name: 'displays',
  label: '展示类',
  children: [
    { name: 'bindpopup', label: '气泡/BindPopup' },
    { name: 'toast', label: '即时反馈/Toast' },
    { name: 'image', label: '图片/Image' },
    { name: 'scrollbar', label: '滚动条/ScrollBar' },
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
  } else if (name === 'displays/scrollbar') {
    ScrollBarBootcamp({ title: route.label })
  }
}

