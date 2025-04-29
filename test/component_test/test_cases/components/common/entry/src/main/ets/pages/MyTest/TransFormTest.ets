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

import { assertEqual, assertFalse } from '@ohos.arkui.componentTest'
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'
import M1 from '@ohos.matrix4'

let M2 = M1.init([1.000000, 0.000000, 0.000000, 0.000000,
  0.000000, 1.000000, 0.000000, 0.000000,
  0.000000, 0.000000, 1.000000, 0.000000,
  0.000000, 0.000000, 0.000000, 1.000000])

export default async function transFormTest() {
  /*
   * PatternLock组件 transform属性
   * 找到画面id为 patternLockTransform 的组件
   * 获取patternLock组件transform的属性矩阵：
   * [1.0, 0.0, 0.0, 0.0,
   *  0.0, 1.0, 0.0, 0.0,
   *  0.0, 0.0, 1.0, 0.0,
   *  0.0, 0.0, 0.0, 1.0]
   * 和矩阵 M2 进行比对
   * */
  defineTest('transFormTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('transFormTestDemo running')
    let driver: Tester = Tester.create()
    let patternLockTransform: Component =
      await driver.findComponent(Matcher.create().id('patternLockTransform').enabled(true))
    let transform1: string = await patternLockTransform.getInspectorInfo()
    assertEqual(JSON.parse(transform1)
      .$attrs
      .transform
      .matrix,
      '1.000000,0.000000,0.000000,' +
        '0.000000,0.000000,1.000000,' +
        '0.000000,0.000000,0.000000,' +
        '0.000000,1.000000,0.000000,' +
        '0.000000,0.000000,0.000000,' +
        '1.000000,')
  }, 0)
}