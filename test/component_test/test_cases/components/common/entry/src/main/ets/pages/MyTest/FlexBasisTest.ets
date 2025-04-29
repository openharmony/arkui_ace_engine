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

import { assertEqual, assertFalse, assertTrue } from '@ohos.arkui.componentTest'
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function flexBasisTest() {
  /*
   * flexBasis 通用属性
   * 找到画面id为 loadingProgressFlexBasis1 的 LoadingProgress 组件
   * 找到画面文本为 ButtonFlexBasis 按钮
   * 获取 loadingProgressFlexBasis1 的flexBasis属性与期望值'100.00vp'比对
   * 点击 LoadingProgress1 变更 loadingProgressFlexBasis1 的属性
   * 获取 loadingProgressFlexBasis1 的flexBasis属性与期望值'200.00vp'比对
   * */
  defineTest('flexBasisTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('flexBasisTestDemo running')
    let driver: Tester = Tester.create()
    let loadingProgressFlexBasis1: Component =
      await driver.findComponent(Matcher.create().id('loadingProgressFlexBasis1').enabled(true))
    let button1: Component =
      await driver.findComponent(Matcher.create().text('ButtonFlexBasis').enabled(true))
    let flexBasis1: string = await loadingProgressFlexBasis1.getInspectorInfo()
    assertEqual(JSON.parse(flexBasis1).$attrs.flexBasis, '100.00vp')

    await button1.tap()
    let flexBasis2: string = await loadingProgressFlexBasis1.getInspectorInfo()
    assertEqual(JSON.parse(flexBasis2).$attrs.flexBasis, '200.00vp')
  }, 0)
}