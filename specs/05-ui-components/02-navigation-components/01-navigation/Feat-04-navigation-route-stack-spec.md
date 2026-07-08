# 特性规格

> Func-05-02-01-Feat-04 Navigation 路由栈管理：固化 NavPathStack 全量方法（pushPath/pushDestination/pushPathByName/pushDestinationByName/replacePath/replaceDestination/replacePathByName/removeByIndexes/removeByName/removeByNavDestinationId/pop/popToName/popToIndex/moveToTop/moveIndexToTop/clear/getAllPathName/getParamByIndex/getParamByName/getIndexByName/getParent/size/disableAnimation/setInterception/getPathStack/setPathStack）、NavPathInfo、NavPathStack constructor、LaunchMode、NavigationOptions、PopInfo、NavigationOperation、NavigationInterception、InterceptionShowCallback、InterceptionCallback、InterceptionModeCallback 的行为规格。

## 概述

| 属性 | 值 |
|------|-----|
| 特性名称 | Navigation 路由栈管理 |
| 特性编号 | Func-05-02-01-Feat-04 |
| 所属 Epic | 无（已有能力补录） |
| 优先级 | P0 |
| 目标版本 | API 9 起支持 NavPathStack，核心方法 API 9-12，setInterception API 14，LaunchMode API 16 |
| SIG 归属 | ArkUI SIG |
| 状态 | Baselined |
| 复杂度 | 复杂 |

## 本次变更范围（Delta）

无新增变更，已有实现补录。

## 输入文档

| 文档 | 路径 | 状态 |
|------|------|------|
| Design | `specs/05-ui-components/02-navigation-components/01-navigation/design.md` | Baselined |
| SDK API | `interface/sdk-js/api/@internal/component/ets/navigation.d.ts` | — |
| Navigation Stack | `frameworks/core/components_ng/pattern/navigation/navigation_stack.cpp/.h` | — |
| Navigation Pattern | `frameworks/core/components_ng/pattern/navigation/navigation_pattern.cpp` | — |

---

## 用户故事

### US-1: Push 操作

**作为** 应用开发者,
**我想要** 通过 NavPathStack 的 push 系列方法将 NavDestination 推入路由栈,
**以便** 导航到新的页面目的地。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-1.1 | WHEN 调用 `navPathStack.pushPath({ name: 'pageA' })` THEN 将名为 pageA 的 NavDestination 推入栈顶 | 正常 |
| AC-1.2 | WHEN 调用 `navPathStack.pushPath({ name: 'pageA', param: data })` THEN 将 pageA 推入栈顶并携带参数 data | 正常 |
| AC-1.3 | WHEN 调用 `navPathStack.pushPath({ name: 'pageA', onPop: callback })` THEN 将 pageA 推入栈顶，pop 时触发 onPop 回调 | 正常 |
| AC-1.4 | WHEN 调用 `navPathStack.pushDestination('pageA')` THEN 将 pageA 作为 NavDestination 推入栈顶 | 正常 |
| AC-1.5 | WHEN 调用 `navPathStack.pushPathByName('pageA')` THEN 将名为 pageA 的 NavDestination 按名称推入栈顶 | 正常 |
| AC-1.6 | WHEN 调用 `navPathStack.pushPathByName('pageA', data)` THEN 将 pageA 按名称推入栈顶并携带参数 | 正常 |
| AC-1.7 | WHEN 调用 `navPathStack.pushDestinationByName('pageA')` THEN 将 pageA 按 NavDestination 名称推入栈顶 | 正常 |
| AC-1.8 | WHEN 调用 `navPathStack.pushPath({ name: 'pageA', launchMode: LaunchMode.STANDARD })` THEN 每次调用都推入新实例 | 正常 |
| AC-1.9 | WHEN 调用 `navPathStack.pushPath({ name: 'pageA', launchMode: LaunchMode.SINGLE })` THEN 若栈中已存在同名 NavDestination，则移至栈顶而非重复推入 | 边界 |

### US-2: Replace 操作

**作为** 应用开发者,
**我想要** 通过 NavPathStack 的 replace 系列方法替换栈顶 NavDestination,
**以便** 在当前位置替换页面而不保留历史记录。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-2.1 | WHEN 调用 `navPathStack.replacePath({ name: 'pageB' })` THEN 栈顶 NavDestination 被替换为 pageB | 正常 |
| AC-2.2 | WHEN 调用 `navPathStack.replacePath({ name: 'pageB', param: data })` THEN 栈顶被替换为 pageB 并携带参数 | 正常 |
| AC-2.3 | WHEN 调用 `navPathStack.replaceDestination('pageB')` THEN 栈顶 NavDestination 被替换为 pageB | 正常 |
| AC-2.4 | WHEN 调用 `navPathStack.replacePathByName('pageB')` THEN 栈顶按名称替换为 pageB | 正常 |
| AC-2.5 | WHEN 调用 `navPathStack.replacePathByName('pageB', data)` THEN 栈顶按名称替换为 pageB 并携带参数 | 正常 |

### US-3: Remove 操作

**作为** 应用开发者,
**我想要** 通过 NavPathStack 的 remove 系列方法按索引/名称/ID 移除指定 NavDestination,
**以便** 从路由栈中删除特定页面。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-3.1 | WHEN 调用 `navPathStack.removeByIndexes([1, 3])` THEN 指定索引位置的 NavDestination 被移除 | 正常 |
| AC-3.2 | WHEN 调用 `navPathStack.removeByName('pageA')` THEN 所有名为 pageA 的 NavDestination 被移除 | 正常 |
| AC-3.3 | WHEN 调用 `navPathStack.removeByNavDestinationId('destId1')` THEN 指定 NavDestinationId 的 NavDestination 被移除 | 正常 |
| AC-3.4 | WHEN removeByIndexes 索引超出栈范围 THEN 无操作，栈不变 | 边界 |
| AC-3.5 | WHEN removeByName 名称不存在 THEN 无操作，栈不变 | 边界 |

### US-4: Pop 操作

**作为** 应用开发者,
**我想要** 通过 NavPathStack 的 pop 系列方法弹出 NavDestination,
**以便** 返回到前一个页面或指定页面。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-4.1 | WHEN 调用 `navPathStack.pop()` THEN 弹出栈顶 NavDestination，显示栈中下一个页面 | 正常 |
| AC-4.2 | WHEN 调用 `navPathStack.pop(result: PopInfo)` THEN 弹出栈顶 NavDestination，并携带 PopInfo 结果回调 | 正常 |
| AC-4.3 | WHEN 调用 `navPathStack.popToName('pageA')` THEN 弹出到名为 pageA 的 NavDestination 为栈顶 | 正常 |
| AC-4.4 | WHEN 调用 `navPathStack.popToIndex(2)` THEN 弹出到索引 2 的 NavDestination 为栈顶 | 正常 |
| AC-4.5 | WHEN 栈为空时调用 pop THEN 无操作，栈不变 | 边界 |
| AC-4.6 | WHEN popToName 名称不存在 THEN 弹出到栈底（NavBar） | 边界 |

### US-5: Move/Clear/Query 操作

**作为** 应用开发者,
**我想要** 通过 NavPathStack 的 move/clear/get 系列方法移动栈元素、清空栈和查询栈信息,
**以便** 灵活管理路由栈状态。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-5.1 | WHEN 调用 `navPathStack.moveToTop(index)` THEN 指定索引的 NavDestination 移到栈顶 | 正常 |
| AC-5.2 | WHEN 调用 `navPathStack.moveIndexToTop(index)` THEN 指定索引的 NavDestination 移到栈顶 | 正常 |
| AC-5.3 | WHEN 调用 `navPathStack.clear()` THEN 栈被清空，所有 NavDestination 移除 | 正常 |
| AC-5.4 | WHEN 调用 `navPathStack.getAllPathName()` THEN 返回栈中所有 NavDestination 名称数组 | 正常 |
| AC-5.5 | WHEN 调用 `navPathStack.getParamByIndex(index)` THEN 返回指定索引 NavDestination 的参数 | 正常 |
| AC-5.6 | WHEN 调用 `navPathStack.getParamByName('pageA')` THEN 返回名为 pageA 的 NavDestination 的参数 | 正常 |
| AC-5.7 | WHEN 调用 `navPathStack.getIndexByName('pageA')` THEN 返回名为 pageA 的 NavDestination 在栈中的索引 | 正常 |
| AC-5.8 | WHEN 调用 `navPathStack.getParent()` THEN 返回当前 NavDestination 的父级信息 | 正常 |
| AC-5.9 | WHEN 调用 `navPathStack.size()` THEN 返回栈中 NavDestination 数量 | 正常 |
| AC-5.10 | WHEN moveToTop 索引超出栈范围 THEN 无操作，栈不变 | 边界 |

### US-6: 拦截与动画控制

**作为** 应用开发者,
**我想要** 通过 NavPathStack 的 disableAnimation 和 setInterception 控制转场动画和拦截路由操作,
**以便** 禁用动画或拦截 push/pop/replace 等操作执行自定义逻辑。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-6.1 | WHEN 调用 `navPathStack.disableAnimation(true)` THEN push/pop/replace 操作不播放转场动画 | 正常 |
| AC-6.2 | WHEN 调用 `navPathStack.disableAnimation(false)` THEN push/pop/replace 操作恢复播放转场动画 | 正常 |
| AC-6.3 | WHEN 调用 `navPathStack.setInterception({ willShow: callback, didShow: callback, willHide: callback, didHide: callback })`（API 14 新增）THEN push/show 操作前触发 willShow 拦截回调，完成后触发 didShow 回调；pop/hide 操作前触发 willHide 拦截回调，完成后触发 didHide 回调 | 正常 |
| AC-6.4 | WHEN InterceptionShowCallback 返回 NavigationOperation 状态 THEN 可控制是否允许操作继续 | 正常 |
| AC-6.5 | WHEN InterceptionCallback 不返回 THEN 操作默认继续执行 | 边界 |
| AC-6.6 | WHEN 调用 `navPathStack.getPathStack()` THEN 返回 NavPathStack 实例 | 正常 |
| AC-6.7 | WHEN 调用 `navPathStack.setPathStack(stack)` THEN 设置当前 Navigation 使用的 NavPathStack | 正常 |

---

## 验收追溯

| AC编号 | US ID | 关联规则 | 验证手段 |
|-------|-------|----------|----------|
| AC-1.1 | US-1 | R-1 | 单元测试 pushPath basic |
| AC-1.2 | US-1 | R-1 | 单元测试 pushPath with param |
| AC-1.3 | US-1 | R-1 | 单元测试 pushPath onPop callback |
| AC-1.4 | US-1 | R-1 | 单元测试 pushDestination |
| AC-1.5 | US-1 | R-2 | 单元测试 pushPathByName |
| AC-1.6 | US-1 | R-2 | 单元测试 pushPathByName with param |
| AC-1.7 | US-1 | R-2 | 单元测试 pushDestinationByName |
| AC-1.8 | US-1 | R-3 | 单元测试 LaunchMode STANDARD |
| AC-1.9 | US-1 | R-3 | 单元测试 LaunchMode SINGLE |
| AC-2.1 | US-2 | R-4 | 单元测试 replacePath basic |
| AC-2.2 | US-2 | R-4 | 单元测试 replacePath with param |
| AC-2.3 | US-2 | R-4 | 单元测试 replaceDestination |
| AC-2.4 | US-2 | R-5 | 单元测试 replacePathByName |
| AC-2.5 | US-2 | R-5 | 单元测试 replacePathByName with param |
| AC-3.1 | US-3 | R-6 | 单元测试 removeByIndexes |
| AC-3.2 | US-3 | R-7 | 单元测试 removeByName |
| AC-3.3 | US-3 | R-8 | 单元测试 removeByNavDestinationId |
| AC-3.4 | US-3 | R-6 | 单元测试 removeByIndexes out of range |
| AC-3.5 | US-3 | R-7 | 单元测试 removeByName not found |
| AC-4.1 | US-4 | R-9 | 单元测试 pop basic |
| AC-4.2 | US-4 | R-9 | 单元测试 pop with PopInfo |
| AC-4.3 | US-4 | R-10 | 单元测试 popToName |
| AC-4.4 | US-4 | R-10 | 单元测试 popToIndex |
| AC-4.5 | US-4 | R-9 | 单元测试 pop empty stack |
| AC-4.6 | US-4 | R-10 | 单元测试 popToName not found |
| AC-5.1 | US-5 | R-11 | 单元测试 moveToTop |
| AC-5.2 | US-5 | R-11 | 单元测试 moveIndexToTop |
| AC-5.3 | US-5 | R-12 | 单元测试 clear |
| AC-5.4 | US-5 | R-13 | 单元测试 getAllPathName |
| AC-5.5 | US-5 | R-13 | 单元测试 getParamByIndex |
| AC-5.6 | US-5 | R-13 | 单元测试 getParamByName |
| AC-5.7 | US-5 | R-13 | 单元测试 getIndexByName |
| AC-5.8 | US-5 | R-14 | 单元测试 getParent |
| AC-5.9 | US-5 | R-15 | 单元测试 size |
| AC-5.10 | US-5 | R-11 | 单元测试 moveToTop out of range |
| AC-6.1 | US-6 | R-16 | 单元测试 disableAnimation true |
| AC-6.2 | US-6 | R-16 | 单元测试 disableAnimation false |
| AC-6.3 | US-6 | R-17 | 单元测试 setInterception |
| AC-6.4 | US-6 | R-18 | 单元测试 InterceptionShowCallback |
| AC-6.5 | US-6 | R-17 | 代码审查 InterceptionCallback 默认行为 |
| AC-6.6 | US-6 | R-19 | 单元测试 getPathStack |
| AC-6.7 | US-6 | R-19 | 单元测试 setPathStack |

## 规则定义

| 规则ID | 类型 | 触发条件 | 预期行为 | 边界/约束 | 关联AC |
|--------|------|----------|----------|-----------|--------|
| R-1 | 行为 | — | pushPath/pushDestination 将 NavDestination 推入栈顶：pushPath 接受 NavPathInfo（name/param/onPop），pushDestination 接受字符串名称 | NavPathInfo.name 为 NavDestination 名称 | AC-1.1~AC-1.4 |
| R-2 | 行为 | — | pushPathByName/pushDestinationByName 按名称推入 NavDestination：支持携带参数 | — | AC-1.5~AC-1.7 |
| R-3 | 行为 | — | LaunchMode 控制推入行为：STANDARD 每次推入新实例，SINGLE 若栈中已存在同名则移至栈顶 | API 16 新增 | AC-1.8, AC-1.9 |
| R-4 | 行为 | — | replacePath/replaceDestination 替换栈顶 NavDestination：replacePath 接受 NavPathInfo，replaceDestination 接受字符串名称 | — | AC-2.1~AC-2.3 |
| R-5 | 行为 | — | replacePathByName 按名称替换栈顶 NavDestination：支持携带参数 | — | AC-2.4, AC-2.5 |
| R-6 | 行为 | — | removeByIndexes 按索引数组移除 NavDestination：索引超出栈范围时无操作 | 索引需为正整数且在栈范围内 | AC-3.1, AC-3.4 |
| R-7 | 行为 | — | removeByName 按名称移除所有同名 NavDestination：名称不存在时无操作 | — | AC-3.2, AC-3.5 |
| R-8 | 行为 | — | removeByNavDestinationId 按 NavDestinationId 移除指定 NavDestination | — | AC-3.3 |
| R-9 | 行为 | — | pop 弹出栈顶 NavDestination：支持携带 PopInfo 结果回调；栈为空时无操作 | PopInfo 包含 name 和 result | AC-4.1, AC-4.2, AC-4.5 |
| R-10 | 行为 | — | popToName/popToIndex 弹出到指定位置：popToName 弹出到名为 name 的 NavDestination 为栈顶，popToIndex 弹出到指定索引为栈顶；名称不存在时弹出到栈底 | — | AC-4.3, AC-4.4, AC-4.6 |
| R-11 | 行为 | — | moveToTop/moveIndexToTop 将指定索引的 NavDestination 移到栈顶：索引超出栈范围时无操作 | — | AC-5.1, AC-5.2, AC-5.10 |
| R-12 | 行为 | — | clear 清空栈，移除所有 NavDestination，栈变为空 | — | AC-5.3 |
| R-13 | 行为 | — | getAllPathName/getParamByIndex/getParamByName/getIndexByName 查询栈信息：getAllPathName 返回名称数组，getParamByIndex/getParamByName 返回参数，getIndexByName 返回索引 | — | AC-5.4~AC-5.7 |
| R-14 | 行为 | — | getParent 返回当前 NavDestination 的父级信息 | — | AC-5.8 |
| R-15 | 行为 | — | size 返回栈中 NavDestination 数量 | — | AC-5.9 |
| R-16 | 行为 | — | disableAnimation 禁用/恢复转场动画：true 时 push/pop/replace 不播放动画，false 时恢复动画 | — | AC-6.1, AC-6.2 |
| R-17 | 行为 | — | setInterception 设置路由拦截（API 14 新增）：willShow/didShow 拦截 push/show 操作，willHide/didHide 拦截 pop/hide 操作 | API 14 新增 | AC-6.3, AC-6.5 |
| R-18 | 行为 | — | InterceptionShowCallback/InterceptionModeCallback 返回 NavigationOperation 状态控制是否允许操作继续 | NavigationOperation 定义操作类型 | AC-6.4 |
| R-19 | 行为 | — | getPathStack/setPathStack 获取/设置 NavPathStack 实例：getPathStack 返回当前栈实例，setPathStack 设置当前 Navigation 使用的栈 | — | AC-6.6, AC-6.7 |

---

## 验证映射

| VM编号 | AC编号 | 验证类型 | 位置/用例 |
|-------|-------|----------|-----------|
| VM-1 | AC-1.1 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_stack_test.cpp` pushPath basic |
| VM-2 | AC-1.2 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_stack_test.cpp` pushPath param |
| VM-3 | AC-1.3 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_stack_test.cpp` pushPath onPop |
| VM-4 | AC-1.4 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_stack_test.cpp` pushDestination |
| VM-5 | AC-1.5 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_stack_test.cpp` pushPathByName |
| VM-6 | AC-1.6 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_stack_test.cpp` pushPathByName param |
| VM-7 | AC-1.7 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_stack_test.cpp` pushDestinationByName |
| VM-8 | AC-1.8 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_stack_test.cpp` LaunchMode STANDARD |
| VM-9 | AC-1.9 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_stack_test.cpp` LaunchMode SINGLE |
| VM-10 | AC-2.1 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_stack_test.cpp` replacePath |
| VM-11 | AC-2.2 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_stack_test.cpp` replacePath param |
| VM-12 | AC-2.3 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_stack_test.cpp` replaceDestination |
| VM-13 | AC-2.4 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_stack_test.cpp` replacePathByName |
| VM-14 | AC-2.5 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_stack_test.cpp` replacePathByName param |
| VM-15 | AC-3.1 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_stack_test.cpp` removeByIndexes |
| VM-16 | AC-3.2 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_stack_test.cpp` removeByName |
| VM-17 | AC-3.3 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_stack_test.cpp` removeByNavDestinationId |
| VM-18 | AC-3.4 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_stack_test.cpp` removeByIndexes out of range |
| VM-19 | AC-3.5 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_stack_test.cpp` removeByName not found |
| VM-20 | AC-4.1 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_stack_test.cpp` pop basic |
| VM-21 | AC-4.2 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_stack_test.cpp` pop PopInfo |
| VM-22 | AC-4.3 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_stack_test.cpp` popToName |
| VM-23 | AC-4.4 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_stack_test.cpp` popToIndex |
| VM-24 | AC-4.5 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_stack_test.cpp` pop empty |
| VM-25 | AC-4.6 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_stack_test.cpp` popToName not found |
| VM-26 | AC-5.1 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_stack_test.cpp` moveToTop |
| VM-27 | AC-5.2 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_stack_test.cpp` moveIndexToTop |
| VM-28 | AC-5.3 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_stack_test.cpp` clear |
| VM-29 | AC-5.4 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_stack_test.cpp` getAllPathName |
| VM-30 | AC-5.5 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_stack_test.cpp` getParamByIndex |
| VM-31 | AC-5.6 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_stack_test.cpp` getParamByName |
| VM-32 | AC-5.7 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_stack_test.cpp` getIndexByName |
| VM-33 | AC-5.8 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_stack_test.cpp` getParent |
| VM-34 | AC-5.9 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_stack_test.cpp` size |
| VM-35 | AC-5.10 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_stack_test.cpp` moveToTop out of range |
| VM-36 | AC-6.1 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_stack_test.cpp` disableAnimation true |
| VM-37 | AC-6.2 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_stack_test.cpp` disableAnimation false |
| VM-38 | AC-6.3 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_stack_test.cpp` setInterception |
| VM-39 | AC-6.4 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_stack_test.cpp` InterceptionShowCallback |
| VM-40 | AC-6.5 | 代码审查 | `frameworks/core/components_ng/pattern/navigation/navigation_stack.cpp` InterceptionCallback 默认行为 |
| VM-41 | AC-6.6 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_stack_test.cpp` getPathStack |
| VM-42 | AC-6.7 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_stack_test.cpp` setPathStack |

---

## API 变更分析

### 新增 API

> 本特性为已有实现补录，以下 API 均为 Public 开放范围。

| API 签名 | 类型 | d.ts 位置 | @since | 开放范围 | 功能描述 |
|----------|------|-----------|--------|----------|----------|
| `new NavPathStack()` | Public | navigation.d.ts | API 9 | Public | 创建空路由栈 |
| `new NavPathStack(options: NavigationOptions)` | Public | navigation.d.ts | API 10 | Public | 创建带选项的路由栈 |
| `NavPathStack.pushPath(info: NavPathInfo): void` | Public | navigation.d.ts | API 9 | Public | 推入 NavDestination |
| `NavPathStack.pushDestination(name: string): void` | Public | navigation.d.ts | API 9 | Public | 按 name 推入 NavDestination |
| `NavPathStack.pushPathByName(name: string): void` | Public | navigation.d.ts | API 9 | Public | 按名称推入 NavDestination |
| `NavPathStack.pushPathByName(name: string, param: Object): void` | Public | navigation.d.ts | API 9 | Public | 按名称推入并携带参数 |
| `NavPathStack.pushDestinationByName(name: string): void` | Public | navigation.d.ts | API 9 | Public | 按 NavDestination name 推入 |
| `NavPathStack.replacePath(info: NavPathInfo): void` | Public | navigation.d.ts | API 9 | Public | 替换栈顶 NavDestination |
| `NavPathStack.replaceDestination(name: string): void` | Public | navigation.d.ts | API 9 | Public | 按 name 替换栈顶 |
| `NavPathStack.replacePathByName(name: string): void` | Public | navigation.d.ts | API 9 | Public | 按名称替换栈顶 |
| `NavPathStack.replacePathByName(name: string, param: Object): void` | Public | navigation.d.ts | API 9 | Public | 按名称替换栈顶并携带参数 |
| `NavPathStack.removeByIndexes(indexes: Array<number>): void` | Public | navigation.d.ts | API 9 | Public | 按索引数组移除 |
| `NavPathStack.removeByName(name: string): void` | Public | navigation.d.ts | API 9 | Public | 按名称移除所有同名 |
| `NavPathStack.removeByNavDestinationId(navDestinationId: string): void` | Public | navigation.d.ts | API 10 | Public | 按 NavDestinationId 移除 |
| `NavPathStack.pop(): boolean` | Public | navigation.d.ts | API 9 | Public | 弹出栈顶 |
| `NavPathStack.pop(result: PopInfo): boolean` | Public | navigation.d.ts | API 9 | Public | 弹出栈顶携带结果 |
| `NavPathStack.popToName(name: string): boolean` | Public | navigation.d.ts | API 9 | Public | 弹出到指定名称 |
| `NavPathStack.popToIndex(index: number): boolean` | Public | navigation.d.ts | API 9 | Public | 弹出到指定索引 |
| `NavPathStack.moveToTop(index: number): void` | Public | navigation.d.ts | API 9 | Public | 将指定索引移到栈顶 |
| `NavPathStack.moveIndexToTop(index: number): void` | Public | navigation.d.ts | API 9 | Public | 将指定索引移到栈顶 |
| `NavPathStack.clear(): void` | Public | navigation.d.ts | API 9 | Public | 清空栈 |
| `NavPathStack.getAllPathName(): Array<string>` | Public | navigation.d.ts | API 9 | Public | 获取所有路径名称 |
| `NavPathStack.getParamByIndex(index: number): Object \| undefined` | Public | navigation.d.ts | API 9 | Public | 按索引获取参数 |
| `NavPathStack.getParamByName(name: string): Object \| undefined` | Public | navigation.d.ts | API 9 | Public | 按名称获取参数 |
| `NavPathStack.getIndexByName(name: string): number` | Public | navigation.d.ts | API 9 | Public | 按名称获取索引 |
| `NavPathStack.getParent(): NavPathInfo \| undefined` | Public | navigation.d.ts | API 9 | Public | 获取父级信息 |
| `NavPathStack.size(): number` | Public | navigation.d.ts | API 9 | Public | 获取栈大小 |
| `NavPathStack.disableAnimation(value: boolean): void` | Public | navigation.d.ts | API 9 | Public | 禁用/恢复转场动画 |
| `NavPathStack.setInterception(interception: NavigationInterception): void` | Public | navigation.d.ts | API 14 | Public | 设置路由拦截 |
| `NavPathStack.getPathStack(): NavPathStack` | Public | navigation.d.ts | API 9 | Public | 获取栈实例 |
| `NavPathStack.setPathStack(stack: NavPathStack): void` | Public | navigation.d.ts | API 9 | Public | 设置栈实例 |

**关联类型定义**：

| 类型 | 定义 | @since |
|------|------|--------|
| `NavPathInfo` | `{ name: string, param?: Object, onPop?: (info: PopInfo) => void, launchMode?: LaunchMode }` | API 9 |
| `LaunchMode` | `{ STANDARD=0, SINGLE=1 }` | API 16 |
| `NavigationOptions` | 导航选项 | API 10 |
| `PopInfo` | `{ name: string, result: Object }` | API 9 |
| `NavigationOperation` | 导航操作类型枚举 | API 14 |
| `NavigationInterception` | `{ willShow?: InterceptionShowCallback, didShow?: InterceptionCallback, willHide?: InterceptionCallback, didHide?: InterceptionCallback }` | API 14 |
| `InterceptionShowCallback` | `(from: NavContentInfo, to: NavContentInfo) => NavigationOperation` | API 14 |
| `InterceptionCallback` | `(from: NavContentInfo, to: NavContentInfo) => void` | API 14 |
| `InterceptionModeCallback` | `(from: NavContentInfo, to: NavContentInfo, mode: NavigationOperation) => NavigationOperation` | API 14 |

## 接口规格

### 接口定义

> 本特性为已有实现补录，接口行为定义详见上方规则定义和用户故事。

无新增接口规格。

---

## 兼容性声明

| API 版本 | 行为差异 | 影响 | 迁移指导 |
|----------|----------|------|----------|
| API 9 | NavPathStack 基础方法（push/pop/replace/clear/move/get） | 路由栈管理核心 | 无需迁移 |
| API 10 | NavigationOptions 构造参数、removeByNavDestinationId | 新增栈操作和构造选项 | 无需迁移 |
| API 14 | setInterception 路由拦截 | 新增拦截回调机制 | 未设置拦截时默认允许所有操作 |
| API 16 | LaunchMode（STANDARD/SINGLE） | 控制推入行为 | 默认为 STANDARD 模式 |

---

## 架构约束

| 约束 | 描述 |
|------|------|
| NavPathStack 生命周期 | NavPathStack 与 NavigationPattern 生命周期绑定，栈变更需通知 Pattern 驱动 UI 更新 |
| 栈操作线程安全 | push/pop/replace 等栈操作在 UI 线程执行 |
| 拦截回调时序 | setInterception 拦截回调在栈操作执行前/后触发，willShow/willHide 在操作前，didShow/didHide 在操作后 |
| LaunchMode 门控 | STANDARD 每次推入新实例，SINGLE 需遍历栈检查同名 NavDestination |
| 空栈保护 | pop/remove 等操作在栈为空或索引/名称无效时无操作 |

---

## 非功能性需求

| 维度 | 要求 |
|------|------|
| 性能 | push/pop 为 O(1) 操作；removeByName/getAllPathName 为 O(n) 遍历；SINGLE LaunchMode 需额外栈遍历 |
| 可调试性 | NavPathStack 支持 DumpInfo 输出栈内容和参数信息供 Inspector 检查 |
| 可靠性 | 栈操作异常时（空栈/无效索引）不崩溃，返回 false 或无操作 |

---

## 多设备适配声明

| 设备类型 | 行为差异 | 规格/约束 | 验证方式 | 证据 |
|----------|----------|-----------|----------|------|
| 手机 | Stack 模式为主，pop 操作频繁 | — | 单元测试 | — |
| 平板 | Split 模式下 NavBar 与 Content 并列，push/pop 仅影响 Content 区域 | — | 单元测试 | — |
| 折叠屏 | 模式切换时栈内容不变，仅布局变化 | — | 单元测试 | — |

---

## 全局特性影响

| 影响维度 | 说明 |
|----------|------|
| NavPathStack 跨组件引用 | NavPathStack 可能被多个 Navigation 或其他组件引用，栈变更需全局通知 |
| 拦截回调 | setInterception 拦截回调影响全局路由操作流程 |
| 转场动画联动 | disableAnimation 影响所有 push/pop/replace 的转场动画 |

---

## Spec 自审清单

- [x] 所有 US 以 "作为/我想要/以便" 格式描述
- [x] 所有 AC 编号格式正确（AC-X.Y），且在验收追溯中引用
- [x] 验证映射覆盖全部 AC，每个 AC 至少有一种验证手段
- [x] 规则编号连续且可追溯到源码
- [x] API 变更分析基于真实 SDK 定义文件（navigation.d.ts）
- [x] 兼容性声明标注 API 版本差异（setInterception API 14、LaunchMode API 16）
- [x] 所有源码引用包含 file 信息
- [x] 无 TBD/TODO 占位符
- [x] 变更范围 Delta 明确标注为已有实现补录

---

## context-references

### 源码文件

| 文件 | 说明 |
|------|------|
| `frameworks/core/components_ng/pattern/navigation/navigation_stack.cpp/.h` | NavPathStack 路由栈核心实现 |
| `frameworks/core/components_ng/pattern/navigation/navigation_pattern.cpp/.h` | Pattern 层，栈协调和拦截回调 |
| `frameworks/core/components_ng/pattern/navigation/navigation_model_ng.cpp/.h` | NG Model 层 |
| `frameworks/bridge/declarative_frontend/jsview/js_navigation.cpp/.h` | JS 桥接层 |
| `interface/sdk-js/api/@internal/component/ets/navigation.d.ts` | SDK 公开 API 定义 |

### 测试文件

| 文件 | 说明 |
|------|------|
| `test/unittest/core/pattern/navigation/` | Navigation 单元测试目录
