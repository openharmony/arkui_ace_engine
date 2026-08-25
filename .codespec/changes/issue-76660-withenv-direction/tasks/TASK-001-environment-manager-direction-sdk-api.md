# TASK-001：WithEnv direction 与显式 reader 主链

> 原 Tasks 1～4 由 Owner 合并实现。本卡按当前 `spec.md`/`design.md` 重述实际范围；tree-state 专项修正和验证分别在 execution-plan 的 TASK-002/TASK-003 管理。

## 任务元数据

| 字段 | 内容 |
|------|------|
| Task ID | TASK-001 |
| 关联 Feature | FEAT-04-03-01-01 |
| 目标仓库 | arkui_ace_engine |
| 优先级 | P0 |
| 复杂度 | 标准 |
| 实现状态 | 代码存在；运行验证未闭合 |
| 历史提交范围 | `3df5112f727..705e5d27151`，生命周期追加见 `46849cd852ab` |

## 任务目标

交付 direction 系统 env 的设置、最近祖先查值、更新通知、布局解析和 ArkTS API/bridge 主链，并保持 CustomEnv 的既有设置/查值/更新能力。

## AC 映射

| AC | 本 Task 职责 | 验证 |
|----|---------------|------|
| AC-1.1～AC-1.4 | direction 设置、Auto/全局 fallback | layout/WithEnv unittest + ArkTS/HAP |
| AC-2.1～AC-2.4 | `@Env` direct-query、更新与只读 | bridge/ArkTS/HAP |
| AC-3.1～AC-3.4 | 显式覆盖、最近祖先、焦点消费 | component/focus targeted test |
| AC-4.5 | CustomEnv 强类型 key 与行为兼容 | SDK 编译 + CustomEnv regression |

## 已实现范围

- WithEnvNode/Model 支持 system env 设置、移除和查询；
- EnvironmentManager 支持 system/custom 最近祖先解析、显式 reader 双向索引与 ADD/UPDATE/REMOVE 通知；
- layout direction 解析加入 WithEnv 默认值且保留显式 direction 优先；
- SystemEnvKey/WritableEnvKey 与 `WithEnvAttribute.env<T>()` 接线；
- `@Env(SystemEnvKey)`、`CustomEnvKey<T>`、`@CustomEnv(CustomEnvKey<T>)` 动态前端接线；
- direction native 值转换为动态前端可观察的 Ltr/Rtl/Auto。

## 明确非目标

- 不承诺 O(1) 查值缓存；当前最近祖先解析仍沿 parent 链；
- 不承诺全部 implicit 通知精准化；direction/fontScale implicit handler 当前使用 FULL 模式；
- 不交付 dump；
- 不定义 fontScale 默认值或用户可见生命周期；
- 不以“测试源码已存在”替代 fresh 构建和运行结果。

## 文件范围

| 模块 | 代表路径 | 职责 |
|------|----------|------|
| WithEnv syntax/model | `frameworks/core/components_ng/syntax/with_env_*` | system/custom env 存储和设置入口 |
| Pipeline | `frameworks/core/pipeline_ng/environment_manager.*` | 解析、索引、通知 |
| Layout | `frameworks/core/components_ng/layout/layout_property.*`、`layout_direction_env.cpp` | direction 优先级 |
| Dynamic ArkTS | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/env_base/system_env.ts`、`v2_decorators.ts` | key 类型和 decorator |
| WithEnv bridge | `frameworks/bridge/declarative_frontend/ark_with_env/src/WithEnv.ts`、`jsview/js_with_env.cpp` | `.env()`/`.customEnv()` 接线 |
| Test | `test/unittest/core/syntax/with_env_syntax_test_ng.cpp`、`test/unittest/core/pipeline/environment_manager_test_ng.cpp` | 主链与作用域规则 |

## 完成判据

- [x] 静态实现：`.env()` 从 ArkTS 到 native 的调用链存在；
- [x] 静态实现：layout direction 优先级为 explicit > env > Auto/global；
- [x] 静态实现：explicit reader 按最近 owner 登记并可在值变化时通知；
- [x] 静态实现：CustomEnv 泛型 key 接线存在；
- [ ] 完整 OHOS SDK 编译通过；
- [ ] direction/layout/Env/CustomEnv targeted test fresh PASS；
- [ ] ArkTS/HAP 验证 AC-1.*～AC-3.*。

## 验证命令

```bash
./build.sh --product-name ohos-sdk --build-target ace_engine
./build.sh --product-name rk3568 --build-target unittest
```

具体可执行文件和 gtest filter 按完整 OpenHarmony out 目录确认。fresh 日志写入 `evidence/reviews/spec-compliance.md` 后，才能将运行状态改为 PASS。
