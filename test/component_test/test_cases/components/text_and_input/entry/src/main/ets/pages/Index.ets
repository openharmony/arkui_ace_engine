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

import { CommonButton } from '../util/CommonButton';

@Entry
@Component
struct Index {
  build() {
    Scroll() {
      Flex({ direction: FlexDirection.Row, wrap: FlexWrap.Wrap }) {
        Text('text_and_input')
          .padding('15vp')
          .width('100%')
          .fontSize('25fp')
          .textAlign(TextAlign.Center)

        CommonButton({ buttonName: 'Text', buttonUrl: 'pages/text/TextHome' });
        CommonButton({ buttonName: 'TextArea', buttonUrl: 'pages/text_area/TextAreaHome' });
        CommonButton({ buttonName: 'Search', buttonUrl: 'pages/search/SearchHome' });
        CommonButton({ buttonName: 'Span', buttonUrl: 'pages/span/SpanHome' });
        CommonButton({ buttonName: 'TextInput', buttonUrl: 'pages/text_input/TextInputHome' });
        CommonButton({ buttonName: 'PatternLock', buttonUrl: 'pages/pattern_lock/PatternLockHome' });
        CommonButton({ buttonName: 'RichEditor', buttonUrl: 'pages/rich_editor/RichEditorHome' });
        CommonButton({ buttonName: 'RichText', buttonUrl: 'pages/rich_text/RichTextHome' });
        CommonButton({ buttonName: 'ImageSpan', buttonUrl: 'pages/image_span/ImageSpanHome' });

      }
      .padding('20vp')
      .width('100%')
    }.margin({ bottom: 60 })
    .width('100%')
  }
}