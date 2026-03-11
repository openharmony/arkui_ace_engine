/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
//TestListOption
export class TestListOption {
  public title?: string = undefined
  public url?: string =undefined
  public key?: string = undefined
}

//extraParamsOption是通过Json.parse转换的Json对象获取如下属性
export class ExtraParamsOption {
  public selectedIndex?: number
  public insertIndex: number = 0
}

// 自定义窗口创建opt
export class WindowTestListOption {
  public title?: string = undefined
  public url?: string =undefined
  public key?: string = undefined
  public windowMode?: boolean = true
}

//系统窗口参数opt
export class  SystemWindowOptions {
  public decorVisible: boolean = true
  public decorHeight: number = 48
  public uiPath?: string = ''
}