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
//  CustomNavigationUtils.ts

const customTransitionMap: Map<string, (isPush: boolean, onFinish: () => void,isexit: boolean, isPop: boolean) => void> = new Map()

export class CustomTransition {
  private constructor() {}

  static delegate = new CustomTransition();

  static getInstance(): CustomTransition {
    return this.delegate;
  }

  // 注册转场动画
  registerNavParam(name: string, animatedParams: (isPush: boolean, onFinish: () => void,isexit: boolean, isPop: boolean) => void) {
    customTransitionMap.set(name, animatedParams)
  }
  // 删除转场动画
  unRegisterNavParam(name: string) {
    customTransitionMap.delete(name)
  }

  // 获取注册的转场动画
  getNavParam(name: string): (isPush: boolean, onFinish: () => void,isexit: boolean, isPop: boolean) => void {
    return customTransitionMap.get(name)
  }
}