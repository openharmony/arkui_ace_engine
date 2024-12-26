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

import { Drawer } from 'common/src/main/ets/components/Drawer';
import { RadioBlock, useEnabled } from 'common';
import UTD from '@ohos.data.uniformTypeDescriptor';


@Component
export struct SearchBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State changeValue: string = '';
  @State submitValue: string = '';
  @State searchColor: ResourceColor = Color.Blue;
  @State enableAutoDisable: boolean = false;
  @State autoDisable: boolean = false;
  @State enablechangeValue: boolean = false;
  build() {
    NavDestination() {
      Drawer({
        title: this.title,
        showParameters: $showParameters,
        content: () => {
          this.Content()
        },
        parameters: () => {
          this.Parameters()
        }
      })
    }
    .backgroundColor($r('sys.color.ohos_id_color_sub_background'))
    .hideTitleBar(true)
  }
  @Builder
  Content() {
    Column() {
      Text('onSubmit1:' + this.submitValue).fontSize(18).margin(15)
      Search({ value: $$this.changeValue, placeholder: 'Type to search...' })
        .searchButton('SEARCH', { autoDisable: useEnabled(this.enableAutoDisable, this.autoDisable) })
        .enterKeyType(EnterKeyType.Go)
        .textAlign(TextAlign.Center)
        .width('95%')
        .height(40)
        .backgroundColor('#F5F5F5')
        .placeholderColor(Color.Grey)
        .textIndent('20px')
        .allowDrop([UTD.UniformDataType.TEXT, UTD.UniformDataType.PLAIN_TEXT])
        .draggable(true)
        .onSubmit((value: string) => {
          this.submitValue = value;
        })
    }
  }
  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {
        RadioBlock({
          title: 'autoDisable',
          isEnabled: this.enableAutoDisable,
          value: this.autoDisable,
          dataSource: [
            { label: '开启', value: true },
            { label: '关闭', value: false }
          ]
        })
      }
    }
  }
}

@Preview
@Component
struct SearchBootcampPreviewer {
  build() {
    SearchBootcamp({
      title: '搜索框/Search'
    })
  }
}
