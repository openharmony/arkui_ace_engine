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
import { Drawer, RadioBlock, useEnabled } from 'common';


@Component
export struct CounterBootcamp{
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State enableEnableInc: boolean = false;
  @State enableEnableDec: boolean = false;
  @State isEnableDec: boolean = true;
  @State isEnableInc: boolean = true;
  @State value: number = 0;


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
      Counter() {
        Text(this.value.toString())
      }
      .margin(100)
      .onInc(() => {
        this.value++;

      })
      .onDec(() => {
        this.value--
      })
      .enableDec(useEnabled(this.enableEnableDec,this.isEnableDec))
      .enableInc(useEnabled(this.enableEnableInc,this.isEnableInc))
    }.width('100%')
  }
  @Builder
  Parameters() {
    Scroll(){
      Column({ space: 8 }) {
        RadioBlock({
          title: 'enableInc',
          isEnabled: $enableEnableInc,
          value: $isEnableInc,
          dataSource: [
            {label: 'false', value: false},
            {label: 'true', value: true}
          ]
        })
        RadioBlock({
          title: 'enableDec',
          isEnabled: $enableEnableDec,
          value: $isEnableDec,
          dataSource: [
            {label: 'false', value: false},
            {label: 'true', value: true}
          ]
        })
      }
    }
    .height('52%')
  }



}

@Preview
@Component
struct CounterBootcampPreviewer{
  build() {
    CounterBootcamp({
      title: '计数器/counter'
    })
  }
}