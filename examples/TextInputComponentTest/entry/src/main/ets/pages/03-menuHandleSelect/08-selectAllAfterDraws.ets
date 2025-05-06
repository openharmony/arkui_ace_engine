/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

@Entry
@Component
struct SelectAllAfterDrawsStruct {
  build() {
    Column() {
      Text('拖拽文本后，点击全选，需要展示菜单\n' +
        '=============操作步骤=============\n' +
        '1、在TextArea中输入任意文字；\n' +
        '2、全选TextArea的所有文字；\n' +
        '3、长按TextArea拖拽；\n' +
        '4、拖拽到TextInput中；\n' +
        '5、双击TextInput；\n' +
        '6、点击全选；\n' +
        '=============正确场景=============\n' +
        '1、展示菜单，只关心是否展示菜单，不关心菜单样式。\n')
        .height('80%')
      TextInput({ text: '这是TextInput；4、拖拽到TextInput中；5、双击TextInput；6、点击全选；' })
        .height(30)
        .width('100%')
      TextArea({ text: '这是TextArea；1、在TextArea中输入任意文字；2、全选TextArea的所有文字；3、长按TextArea拖拽；' })
        .width('100%')
        .height(30)
    }
    .width('100%')
  }
}