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
import { BlockTag } from '../model/BlockTag';
import { tagDesRule } from '../utils';
import { formatDate } from '../utils/timeUtil';
import { Block } from './Block';

export interface RadioItem {
  label: ResourceStr;
  value: Object;
}

@Component
export struct RadioBlock {
  @Prop title: string;
  @Link isEnabled: boolean;
  @Link value: Object;
  @Prop dataSource: RadioItem[];
  @StorageLink('Block') listRadioBlockTags: Array<BlockTag> = [];
  @State listRadioBlockTagsTemp: Array<BlockTag> = [];

  build() {
    Column() {
      Block({ title: this.title, isEnabled: $isEnabled }) {
        Flex({ wrap: FlexWrap.Wrap }) {
          ForEach(this.dataSource, (item: RadioItem, index: number) => {
            Row({ space: 8 }) {
              Radio({ group: this.title, value: JSON.stringify(item.value) })
                .checked(JSON.stringify(this.value) === JSON.stringify(item.value))
                .enabled(this.isEnabled)
                .onChange((checked) => {
                  if (checked) {
                    this.value = item.value;
                    let time = formatDate(new Date(Date.now()))
                    this.listRadioBlockTagsTemp.push(new BlockTag(time, tagDesRule(this.title, item.label.toString())))
                  }
                })
                .onClick(() => {
                  setTimeout(() => {
                    if (AppStorage.get('Block')) {
                      this.listRadioBlockTags = this.listRadioBlockTags.concat(this.listRadioBlockTagsTemp);
                      this.listRadioBlockTagsTemp = [];
                    } else {
                      if (this.listRadioBlockTagsTemp) {
                        this.listRadioBlockTags = this.listRadioBlockTags.concat(this.listRadioBlockTagsTemp);
                      }
                      if (this.listRadioBlockTags) {
                        this.listRadioBlockTagsTemp = [];
                      }
                    }
                  }, 200)
                })

              Text(item.label)
                .fontSize($r('sys.float.Body_M'))
                .fontWeight(FontWeight.Regular)
                .fontColor($r('sys.color.font_primary'))
            }
            .margin(index % 3 !== 0 ? { left: 16 } : {})
          })
        }
        .width('100%')
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