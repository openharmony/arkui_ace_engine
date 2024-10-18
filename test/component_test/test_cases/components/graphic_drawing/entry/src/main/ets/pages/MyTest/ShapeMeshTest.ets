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
  assertContain,
  assertEqual,
  assertFalse,
  assertTrue,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest';

export default async function shapeMeshTest() {
  /*
   * Shape组件 mesh属性
   * 找到画面id为shapeMesh的Shape组件
   * 获取shape的mesh属性的value与期待值[0, 0, 10, 0, 0, 10, 10, 10]比对
   * 获取shape的mesh属性的column与期待值2比对
   * 获取shape的mesh属性的row与期待值2比对
   */
  defineTest('shapeMeshTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("shapeMeshTestDemo running")
    let driver: Tester = Tester.create()
    let shape: Component = await driver.findComponent(Matcher.create().id('shapeMesh').enabled(true))

    let mesh: string = await shape.getInspectorInfo()
    assertEqual(JSON.parse(mesh).$attrs.mesh.value[0], '0.000000')
    assertEqual(JSON.parse(mesh).$attrs.mesh.value[1], '0.000000')
    assertEqual(JSON.parse(mesh).$attrs.mesh.value[2], '10.000000')
    assertEqual(JSON.parse(mesh).$attrs.mesh.value[3], '0.000000')
    assertEqual(JSON.parse(mesh).$attrs.mesh.value[4], '0.000000')
    assertEqual(JSON.parse(mesh).$attrs.mesh.value[5], '10.000000')
    assertEqual(JSON.parse(mesh).$attrs.mesh.value[6], '10.000000')
    assertEqual(JSON.parse(mesh).$attrs.mesh.value[7], '10.000000')
    assertEqual(JSON.parse(mesh).$attrs.mesh.value[8], '8.000000')
    assertEqual(JSON.parse(mesh).$attrs.mesh.column, 2)
    assertEqual(JSON.parse(mesh).$attrs.mesh.row, 2)
  }, 0)
}