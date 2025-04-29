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
import { assertEqual, Component, defineTest, Matcher, TestCaseLevel, Tester } from '@ohos.arkui.componentTest'

export default async function loadingProgressColorTest() {
  /*
   * LoadingProgress组件 Color属性
   * 找到画面id为loadingProgressColor1，loadingProgressColor2的LoadingProgress组件
   * 找到画面文本为LoadingProgressColor1,LoadingProgressColor2的Button组件
   * 获取progressColor1的Color属性与期待值Color.Pink比对
   * 获取progressColor2的Color属性与期待值0xFFFF00比对
   * 点击button1，变更progressColor3的Color属性值为#ff07f31d
   * 获取loadingProgress1的Color属性与期待值为#ff07f31d比对
   * 点击button2，变更progressColor4的Color属性值为$r('app.color.loadingProgress_color')
   * 获取loadingProgress1的Color属性与期待值$r('app.color.loadingProgress_color')比对
   */
  defineTest('loadingProgressColorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('loadingProgressColorTestDemo running')
    let driver: Tester = Tester.create()
    let loadingProgress1: Component =
      await driver.findComponent(Matcher.create().id('loadingProgressColor1').enabled(true))
    let loadingProgress2: Component =
      await driver.findComponent(Matcher.create().id('loadingProgressColor2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('LoadingProgressColor1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('LoadingProgressColor2').enabled(true))

    let progressColor1: string = await loadingProgress1.getInspectorInfo()
    assertEqual(JSON.parse(progressColor1).$attrs.color.toLowerCase(), Color.Pink)
    let progressColor2: string = await loadingProgress2.getInspectorInfo()
    assertEqual(JSON.parse(progressColor2).$attrs.color, '#FFFFFF00')
    await button1.tap()
    let progressColor3: string = await loadingProgress1.getInspectorInfo()
    assertEqual(JSON.parse(progressColor3).$attrs.color.toLowerCase(), "#ff07f31d")
    await button2.tap()
    let progressColor4: string = await loadingProgress1.getInspectorInfo()
    assertEqual(JSON.parse(progressColor4).$attrs.color, $r('app.color.loadingProgress_color'))
  }, 0)
}