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

@Component
export struct CheckboxGroupBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State enableCheckboxGroupShape: boolean = false;
  @State enableCheckboxGroup: boolean = false;
  @State enable: boolean = true;
  @State checkboxShape: number = CheckBoxShape.CIRCLE;
  @State checkboxGroupShape: number = CheckBoxShape.CIRCLE;
  @State enableSelectAll: boolean = false;
  @State selectAll: boolean = true;

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
    .hideTitleBar(true)
  }

  @Builder
  Content() {

    Column() {
      // 全选按钮
      Flex({ justifyContent: FlexAlign.Start, alignItems: ItemAlign.Center }) {
        CheckboxGroup({ group: 'checkboxGroup' })
          .checkboxShape(useEnabled(this.enableCheckboxGroupShape, this.checkboxGroupShape))
          .enabled(useEnabled(this.enableCheckboxGroup, this.enable))
          .selectAll(useEnabled(this.enableSelectAll, this.selectAll))
          .onChange((itemName: CheckboxGroupResult) => {
            console.info(`checkbox group content ${JSON.stringify(itemName)}`);
          })
        Text('CheckBoxGroup')
      }

      // 选项1
      Flex({ justifyContent: FlexAlign.Start, alignItems: ItemAlign.Center }) {
        Checkbox({ name: 'checkbox1', group: 'checkboxGroup' })
          .select(true)
          .onChange((value: boolean) => {
            console.info(`Checkbox1 change is ${value}`)
          })
        Text('CheckBox01')
      }

      // 选项2
      Flex({ justifyContent: FlexAlign.Start, alignItems: ItemAlign.Center }) {
        Checkbox({ name: 'checkbox2', group: 'checkboxGroup' })
          .onChange((value: boolean) => {
            console.info(`Checkbox2 change is ${value}`)
          })
        Text('CheckBox02')
      }
    }
    .width('100%')
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {
        RadioBlock({
          title: '组件形状',
          isEnabled: this.enableCheckboxGroupShape,
          value: this.checkboxGroupShape,
          dataSource: [
            { label: '圆形', value: CheckBoxShape.CIRCLE },
            { label: '圆角方形', value: CheckBoxShape.ROUNDED_SQUARE }
          ]
        })
        RadioBlock({
          title: '是否可操作',
          isEnabled: this.enableCheckboxGroup,
          value: this.enable,
          dataSource: [
            { label: '是', value: true },
            { label: '否', value: false }
          ]
        })
        RadioBlock({
          title: '是否全选',
          isEnabled: this.enableSelectAll,
          value: this.selectAll,
          dataSource: [
            { label: '是', value: true },
            { label: '否', value: false }
          ]
        })
      }.width('100%')
      .height('100%')
    }.height('50%')
  }
}

@Preview
@Component
struct ToastBootcampPreviewer {
  build() {
    CheckboxGroupBootcamp({
      title: '勾选文本/CheckboxGroup'
    })
  }
}