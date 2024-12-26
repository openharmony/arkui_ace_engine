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
import { TextInputBootcamp } from './TextInputBootcamp';
import { TextAreaBootcamp } from './TextAreaBootcamp';
import { RichEditorBootcamp } from './RichEditorBootcamp';
import { ContainerSpanBootcamp } from './ContainerSpanBootcamp';

import { RichEditorSpanUrlBootcamp } from './RichEditorSpanUrlBootcamp';
import { SelectionMenuBootcamp } from './SelectionMenuBootcamp';
import { SearchBootcamp } from './SearchBootcamp';

export const inputsRoute: RouteGroup = {
  name: 'inputs',
  label: '输入类',
  children: [
    { name: 'textInput', label: '单行文本框/TextInput' },
    { name: 'textArea', label: '多行文本框/TextArea' },
    { name: 'richEditor', label: '富文本/RichEditor' },
    { name: 'containerSpan', label: 'ContainerSpan/ContainerSpan' },
    { name: 'richeditor', label: '富文本/RichEditor' },
    { name: 'richeditorSpanurl', label: '富文本超链接/RichEditor' },
    { name: 'SelectionMenu', label: '文本选择菜单/SelectionMenu'},
    { name: 'search', label: '搜索框/Search' }
  ]
};

@Builder
export function InputsDestination(name: string, route: Route) {
  if (name === 'inputs/textInput') {
    TextInputBootcamp({ title: route.label })
  } else if (name === 'inputs/textArea') {
    TextAreaBootcamp({ title: route.label })
  } else if (name === 'inputs/richEditor') {
    RichEditorBootcamp({ title: route.label })
  }else if (name === 'inputs/containerSpan') {
    ContainerSpanBootcamp({ title: route.label })
  } else if (name === 'inputs/richeditorSpanurl') {
    RichEditorSpanUrlBootcamp({ title: route.label })
  } else if (name === 'inputs/SelectionMenu'){
    SelectionMenuBootcamp({ title: route.label})
  } else if (name === 'inputs/search') {
    SearchBootcamp({ title: route.label })
  }
}