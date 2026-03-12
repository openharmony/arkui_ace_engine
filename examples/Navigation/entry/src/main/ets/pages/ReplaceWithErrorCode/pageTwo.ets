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
export function PageTwoBuilder(name: string, param: Object) {
  PageTwo()
}

@Component
export struct PageTwo {

  @Consume('pageInfos') pageInfos: NavPathStack
  @State paramText:string = ''
  build() {
    NavDestination() {
      Text("Page Two")
      Text(this.paramText)
      Button('getparam').onClick(()=>{
        this.paramText=JSON.stringify(this.pageInfos.getParamByName("pageTwo"))
        console.log('-------------------')
        console.log('获取栈中所有NavDestination页面的名称', JSON.stringify(this.pageInfos.getAllPathName()))
        console.log('获取index指定的NavDestination页面的参数信息', JSON.stringify(this.pageInfos.getParamByIndex(1)))
        console.log('获取全部名为name的NavDestination页面的参数信息', JSON.stringify(this.pageInfos.getParamByName('pageTwo')))
        console.log('获取全部名为name的NavDestination页面的位置索引', JSON.stringify(this.pageInfos.getIndexByName('pageOne')))
        console.log('获取栈大小', JSON.stringify(this.pageInfos.size()))
      })
    }
    .backgroundColor("#33CCCC")
    .title("Page Two")
  }
}