# Spec Compliance Evidence — issue-76660-withenv-direction

> 日期：2026-08-05
>
> 输入实现：`46849cd852ab` 及其完整祖先实现
>
> 证据纪律：`PASS-STATIC` 只表示源码与规格一致；无 fresh 构建/运行日志时一律标记 `UNVERIFIED-RUNTIME`。

## 逐 AC 证据

| AC | 静态证据 | 静态结论 | 运行结论 |
|----|----------|----------|----------|
| AC-1.1 | direction system handler 与 layout env 解析链 | PASS-STATIC | UNVERIFIED-RUNTIME |
| AC-1.2 | 同 AC-1.1，值域含 LTR | PASS-STATIC | UNVERIFIED-RUNTIME |
| AC-1.3 | direction bridge/系统值含 Auto，layout 无显式值时进入 env/Auto 链 | PASS-STATIC | UNVERIFIED-RUNTIME |
| AC-1.4 | `ResolveSystemValue` miss 返回空，layout 保留原 fallback | PASS-STATIC | UNVERIFIED-RUNTIME |
| AC-2.1 | direct-query getter 调 native find；EnvironmentManager 沿最近 ancestor 解析 | PASS-STATIC | UNVERIFIED-RUNTIME |
| AC-2.2 | owner reverse index 派发 system update，JSView system callback 转交状态管理 | PASS-STATIC | UNVERIFIED-RUNTIME |
| AC-2.3 | EnvironmentManager miss 后，native `MakeSystemEnvValue(direction, nullopt)` 返回 `Auto`；TS getter直接保存 native 结果 | PASS-STATIC | UNVERIFIED-RUNTIME |
| AC-2.4 | Env setter 抛只读错误 | PASS-STATIC | UNVERIFIED-RUNTIME |
| AC-3.1 | layout 显式 direction 判断先于 env 查询 | PASS-STATIC | UNVERIFIED-RUNTIME |
| AC-3.2 | 同 AC-3.1 | PASS-STATIC | UNVERIFIED-RUNTIME |
| AC-3.3 | parent walk 取最近包含 key 的 WithEnv；内层 key 截断外层通知 | PASS-STATIC | UNVERIFIED-RUNTIME |
| AC-3.4 | focus 使用最终 layout direction 的既有消费链 | PASS-STATIC | UNVERIFIED-RUNTIME |
| AC-4.1 | CustomNode detach 先 Unregister；TS detach 对 initialized system/custom 直接写 default/local default | PASS-STATIC | UNVERIFIED-RUNTIME |
| AC-4.2 | attach 时新 parent/context 已就绪；同/跨 context reparent gtest 已编写 | PASS-STATIC | UNVERIFIED-RUNTIME |
| AC-4.3 | CreateViewNode 仅在 initialized backing 存在时 Ensure；tree handler 再按 own backing 过滤 | PASS-STATIC | UNVERIFIED-RUNTIME |
| AC-4.4 | native find 在获取 manager 前 Ensure；off-tree miss 后保留 attach callback | PASS-STATIC | UNVERIFIED-RUNTIME |
| AC-4.5 | CustomEnv initializer 写 `CUSTOM_ENV_LOCAL_PREFIX`，WithEnv 值写独立 current backing | PASS-STATIC | UNVERIFIED-RUNTIME |
| AC-4.6 | Ensure 幂等且不触发 handler；真实 tree-state 事件单次回调，每个实际变化变量各 fireChange/Watch 一次 | PASS-STATIC | UNVERIFIED-RUNTIME |

## 源码定位

| 主题 | 路径 |
|------|------|
| direction 查询默认值 | `frameworks/bridge/declarative_frontend/jsview/js_view.cpp:114`、`:1611` |
| direct-query key 与 tree-state lifecycle fallback helper | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/v2/v2_env.ts:158` |
| Env 查询分支 / CustomEnv local default | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/v2/v2_decorators.ts:385`、`:445` |
| tree-state handler | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/puv2_common/puv2_view_base.ts:569` |
| callback eligibility 与预初始化 Ensure | `frameworks/bridge/declarative_frontend/jsview/js_view.cpp:1006` |
| Ensure 幂等与 find 前安装 | `frameworks/bridge/declarative_frontend/jsview/js_view.cpp:1544`、`:1581`、`:1611` |
| CustomNode attach/detach | `frameworks/core/components_ng/pattern/custom/custom_node.cpp:52`、`:66` |
| reader 双向索引与注销 | `frameworks/core/pipeline_ng/environment_manager.h:99`、`:107`、`:161`；`environment_manager.cpp:399` |
| parent/context 生命周期顺序 | `frameworks/core/components_ng/base/ui_node.cpp:793`、`:1020`、`:1077`、`:604` |
| lifecycle test code | `test/unittest/core/pipeline/environment_manager_test_ng.cpp:760`、`:866`、`:945`、`:988` |

## 运行验证状态

| 检查 | 结果 | 说明 |
|------|------|------|
| C++ product/unit-test build | NOT RUN | 当前 checkout 是 ace_engine 子仓，无 OpenHarmony 根目录 `build.sh` 和 out 产物 |
| 4 个 lifecycle gtest | NOT RUN | 测试代码存在不等于测试通过 |
| ArkTS/HAP HAP-1～HAP-4 | NOT RUN | 原 ETS 文档仅为草稿，无设备/构建/日志证据 |
| TypeScript standalone no-emit | NOT USED AS PASS | 既有 standalone 配置/runtime stub 诊断不能证明产品 SDK 编译；应在完整 OHOS SDK 构建验证 |
| `git diff --check` | PASS | 2026-08-05 本轮归并后 fresh 执行，无 whitespace error |
| `ohos-sdd validate --level all --json` | PASS | 35 checks，0 broken，0 warning；首轮发现 execution-plan 文件清单不可机读，按 ohos-plan 补列表后复检通过 |

## 审查结论

实现具有逐 AC 的静态对应关系，但所有用户可见 lifecycle 行为仍缺 fresh runtime 证据。当前合规结论为：

- Spec compliance（静态）：PASS-STATIC；
- Spec compliance（运行）：UNVERIFIED-RUNTIME；
- GC：ChangesRequested。

fontScale 默认值未被本规格定义；任何验证不得期望 `1.0` 或其他新增默认值。
