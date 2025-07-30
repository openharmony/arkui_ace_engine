/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

@Entry
@Component
export struct MyNavigator {
    @State active: boolean = false
    @State other: number = 42

    build() {
        Column() {
         Navigator({ target: 'stack', type: NavigationType.Push }) {
             Text('搞定包包的头一口有机奶粉')
                              .fontSize(14)
                              .padding({ left: 5, right: 5 })
                              .margin({ top: 5 })
                              .textOverflow({ overflow: TextOverflow.Ellipsis })
        }.active(this.active)
          
        }.height(150).width(350).padding(35).backgroundColor('#3145AA')
        setTimeout(()=>{
            this.active = true
        }, 2000)
    }
}
