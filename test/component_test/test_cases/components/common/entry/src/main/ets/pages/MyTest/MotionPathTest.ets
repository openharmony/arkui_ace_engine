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

export default async function motionPathTest() {
  /*
 * motionPath 通用属性
 * 找到画面id为 radioMotionPath1 的 Radio 组件
 * 找到画面文本为 ButtonMotionPath1 按钮
 * 获取 radioMotionPath1 的 path 属性与期望值 'Mstart.x start.y L400 200 L200 500 Lend.x end.y' 比对
 * 获取 radioMotionPath1 的 from 属性与期望值 0.0 比对
 * 获取 radioMotionPath1 的 to 属性与期望值 1.0 比对
 * 获取 radioMotionPath1 的 rotatable 属性与期望值 true 比对
 * 点击 button1 变更 radioMotionPath1 的属性
 * 获取 radioMotionPath1 的 rotatable 属性与期望值 false 比对
 * */
  defineTest('motionPathTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('motionPathTestDemo running')
    let driver: Tester = Tester.create()
    let radioMotionPath1: Component = await driver.findComponent(Matcher.create().id('radioMotionPath1').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonMotionPath1').enabled(true))
    let motionPath1: string = await radioMotionPath1.getInspectorInfo()
    assertFalse(JSON.parse(motionPath1).$attrs.motionPath == undefined)

    assertEqual(JSON.parse(motionPath1)
      .$attrs
      .motionPath
      .path, 'Mstart.x start.y L400 200 L200 500 Lend.x end.y')
    assertEqual(JSON.parse(motionPath1)
      .$attrs
      .motionPath
      .from, 0.0)
    assertEqual(JSON.parse(motionPath1)
      .$attrs
      .motionPath
      .to, 1.0)
    assertTrue(JSON.parse(motionPath1)
      .$attrs
      .motionPath
      .rotatable)
    await button1.tap()
    let motionPath2: string = await radioMotionPath1.getInspectorInfo()
    assertFalse(JSON.parse(motionPath2)
      .$attrs
      .motionPath
      .rotatable)
  }, 0)
}