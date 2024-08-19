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

import { Block } from './Block';

export interface RadioItem {
  label: ResourceStr;
  value: Object;
}

@Component
export struct RadioBlock {
  @Prop title: string
  @Link isEnabled: boolean
  @Link value: Object
  @Prop dataSource: RadioItem[]

  build() {
    Column({ space: 8 }) {
      Block({ title: this.title, isEnabled: $isEnabled }) {
        Flex({ wrap: FlexWrap.Wrap }) {
          ForEach(this.dataSource, (item: RadioItem) => {
            Row() {
              Radio({ group: this.title, value: JSON.stringify(item.value) })
                .checked(JSON.stringify(this.value) === JSON.stringify(item.value))
                .enabled(this.isEnabled)
                .onChange((checked) => {
                  if (checked) {
                    this.value = item.value;
                  }
                })
              Text(item.label)
              Text('  ')
            }
          })
        }.width('100%')
      }

    }
  }
}

@Preview
@Component
struct RadioBlockPreview {
  @State isEnabled: boolean = true
  @State value: ButtonType = ButtonType.Capsule

  build() {
    RadioBlock({
      title: 'RadioBlock',
      isEnabled: $isEnabled,
      value: $value,
      dataSource: [
        { label: '胶囊按钮', value: ButtonType.Capsule },
        { label: '普通按钮', value: ButtonType.Normal },
        { label: '圆形按钮', value: ButtonType.Circle },
      ]
    })
  }
}