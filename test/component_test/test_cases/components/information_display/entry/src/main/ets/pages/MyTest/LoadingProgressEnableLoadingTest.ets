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
import {
  assertFalse,
  assertTrue,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest'

export default async function loadingProgressEnableLoadingTest() {
  /*
   * LoadingProgress组件 EnableLoading属性
   * 找到画面id为loadingProgressEnableLoading的LoadingProgress组件
   * 找到画面文本为LoadingProgressEnableLoading的Button组件
   * 获取loadingProgress的EnableLoading属性与期待值false比对
   * 点击button，变更loadingProgress的EnableLoading属性值为true
   */
  defineTest('loadingProgressEnableLoadingTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('loadingProgressEnableLoadingTestDemo running')
    let driver: Tester = Tester.create()
    let loadingProgress: Component =
      await driver.findComponent(Matcher.create().id('loadingProgressEnableLoading').enabled(true))
    let button: Component =
      await driver.findComponent(Matcher.create().text('LoadingProgressEnableLoading').enabled(true))
    let progressEnableLoading1: string = await loadingProgress.getInspectorInfo()
    assertFalse(JSON.parse(progressEnableLoading1).$attrs.enableLoading)
    await button.tap()
    let progressEnableLoading2: string = await loadingProgress.getInspectorInfo()
    assertTrue(JSON.parse(progressEnableLoading2).$attrs.enableLoading)
  }, 0)
}