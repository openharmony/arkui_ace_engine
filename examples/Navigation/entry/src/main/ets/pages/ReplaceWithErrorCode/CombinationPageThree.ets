/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
@Builder
export function CombinationPageThreeBuilder(name: string, param: Object) {
  CombinationPageThree()
}

@Component
export struct CombinationPageThree {

  @Consume('CombinationpageInfos') CombinationpageInfos: NavPathStack

  build() {
    NavDestination() {
      Button("对照组：pushPath pageOne").onClick(() => {
        this.CombinationpageInfos.pushPath({ name: 'pageOne' })
      })
      Button("对照组：pushPathByName pageOne").onClick(() => {
        this.CombinationpageInfos.pushPathByName('pageOne',null)
      })
      Button("对照组：replace pageTwo").onClick(() => {
        this.CombinationpageInfos.replacePath({ name: 'pageTwo' })
      })
      Button("对照组：replace pageOne+pushByName pageOne").onClick(() => {
        this.CombinationpageInfos.replacePath({ name: 'pageOne' })
        this.CombinationpageInfos.pushPathByName('pageOne', null)
      })
      Button("对照组：pushByName pageOne+replace pageOne").onClick(() => {
        this.CombinationpageInfos.pushPathByName('pageOne', null)
        this.CombinationpageInfos.replacePath({ name: 'pageOne' })
      })
      Button("对照组：push pageOne+replace pageTwo").onClick(() => {
        this.CombinationpageInfos.pushPath({ name: 'pageOne' })
        this.CombinationpageInfos.replacePath({ name: 'pageTwo' })
      })
    }
    .backgroundColor("#FF9999")
    .title("Page Three")
  }
}