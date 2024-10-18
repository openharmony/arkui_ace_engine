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
import { assertEqual, Component, defineTest, Matcher, TestCaseLevel, Tester } from '@ohos.arkui.componentTest';

export default async function patternLockPathStrokeWidthTest() {
  /*
   * PatternLock组件 PathStrokeWidth属性
   * 找到画面id为patternLockPathStrokeWidth的PatternLock组件
   * 找到画面文本为PatternLockPathStrokeWidth的Button组件
   * 获取patternLock1的PathStrokeWidth属性与期待值200.00vp比对
   * 点击button，变更patternLock1的PathStrokeWidth属性值为'100px'
   * 获取patternLock1的PathStrokeWidth属性与期待值'100.00px'比对
   */
  defineTest('patternLockPathStrokeWidthTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("patternLockPathStrokeWidthTestDemo running")
    let driver: Tester = Tester.create()
    let patternLock1: Component =
      await driver.findComponent(Matcher.create().id('patternLockPathStrokeWidth').enabled(true))
    let button: Component =
      await driver.findComponent(Matcher.create().text('PatternLockPathStrokeWidth').enabled(true))

    let pathStrokeWidth1: string = await patternLock1.getInspectorInfo()
    assertEqual(JSON.parse(pathStrokeWidth1).$attrs.pathStrokeWidth, '200.00vp')

    await button.tap()
    let pathStrokeWidth2: string = await patternLock1.getInspectorInfo()
    assertEqual(JSON.parse(pathStrokeWidth2).$attrs.pathStrokeWidth, '100.00px')
  }, 0)
}