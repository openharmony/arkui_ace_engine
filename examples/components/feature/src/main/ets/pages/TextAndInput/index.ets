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
import { ContainerSpanBootcamp } from './ContainerSpanBootcamp';
import { HyperlinkBootcamp } from './HyperlinkBootcamp';
import { ImageSpanBootcamp } from './ImageSpanBootcamp';
import { RichEditorBootcamp } from './RichEditorBootcamp';
import { RichEditorSpanUrlBootcamp } from './RichEditorSpanUrlBootcamp';
import { SearchBootcamp } from './SearchBootcamp';
import { SelectionMenuBootcamp } from './SelectionMenuBootcamp';
import { SpanBootcamp } from './SpanBootcamp';
import { SymbolGlyphBootcamp } from './SymbolGlyphBootcamp';
import { SymbolSpanBootcamp } from './SymbolSpanBootcamp';
import { TextAreaBootcamp } from './TextAreaBootcamp';
import { TextBootcamp } from './TextBootcamp';
import { TextInputBootcamp } from './TextInputBootcamp';
import { TextSpanUrlBootcamp } from './TextSpanUrlBootcamp';
import { TextInputLineBootcamp } from './TextInputLineBootcamp';
import { SearchCancelBootcamp } from './SearchCancelBootcamp';

export const textAndInputRoute: RouteGroup = {
  name: 'TextAndInput',
  label: '文本与输入',
  children: [
    { name: 'Text', label: '文本显示/Text' },
    { name: 'TextArea', label: '多行文本框/TextArea' },
    { name: 'TextInput', label: '单行文本框/TextInput' },
    { name: 'TextInputLine', label: '下划线文本/TextInputLine' },
    { name: 'RichEditor', label: '富文本/RichEditor' },
    { name: 'Search', label: '搜索框/Search' },
    { name: 'Span', label: 'Span' },
    { name: 'ImageSpan', label: 'ImageSpan' },
    { name: 'ContainerSpan', label: 'ContainerSpan' },
    { name: 'SymbolSpan', label: 'SymbolSpan' },
    { name: 'SymbolGlyph', label: 'SymbolGlyph' },
    { name: 'Hyperlink', label: '超链接/Hyperlink' },
    { name: 'SelectionMenu', label: '文本选择菜单/SelectionMenu'},
    { name: 'richeditorSpanurl', label: '富文本超链接/RichEditor' },
    { name: 'TextSpanUrl', label: '超链接/TextSpanUrl' },
    { name: 'SearchCancel', label: '搜索框关闭/SearchCancel' },
  ]
};

@Builder
export function textAndInputDestination(name: string, route: Route) {
  if (name === 'TextAndInput/Text') {
    TextBootcamp({title: route.label})
  }else if (name === 'TextAndInput/TextArea'){
    TextAreaBootcamp({title: route.label})
  }else if (name === 'TextAndInput/TextInput'){
    TextInputBootcamp({title: route.label})
  } else if (name === 'TextAndInput/TextInputLine') {
    TextInputLineBootcamp({title: route.label})
  }else if (name === 'TextAndInput/RichEditor'){
    RichEditorBootcamp({title: route.label})
  }else if (name === 'TextAndInput/Search'){
    SearchBootcamp({title: route.label})
  }else if (name === 'TextAndInput/Span'){
    SpanBootcamp({title: route.label})
  }else if (name === 'TextAndInput/ImageSpan'){
    ImageSpanBootcamp({title: route.label})
  }else if (name === 'TextAndInput/ContainerSpan'){
    ContainerSpanBootcamp({title: route.label})
  }else if (name === 'TextAndInput/SymbolSpan'){
    SymbolSpanBootcamp({title: route.label})
  }else if (name === 'TextAndInput/SymbolGlyph'){
    SymbolGlyphBootcamp({title: route.label})
  }else if (name === 'TextAndInput/Hyperlink'){
    HyperlinkBootcamp({title: route.label})
  }else if (name === 'TextAndInput/SelectionMenu'){
    SelectionMenuBootcamp({title: route.label})
  }else if (name === 'TextAndInput/richeditorSpanurl'){
    RichEditorSpanUrlBootcamp({title: route.label})
  }else if (name === 'TextAndInput/TextSpanUrl'){
    TextSpanUrlBootcamp({title: route.label})
  } else if (name === 'TextAndInput/SearchCancel') {
    SearchCancelBootcamp({ title: route.label })
  }

}
