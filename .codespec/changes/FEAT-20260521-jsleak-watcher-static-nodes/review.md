# 统一审查

## 审查元数据

| 项 | 内容 |
|----|------|
| Review ID | REV-20260526-01 |
| 审查阶段 | 代码质量 + 规范符合性 |
| 关联文档 | execution-plan.md / design.md / spec.md |
| 复杂度 | 标准 |
| 涉及仓 | ace_engine |
| Reviewer | sunbees |
| 日期 | 2026-05-26 |
| Base SHA | c74921c397b |
| Head SHA | 289651aa554c3c68ee568c107d36f103466d5d0a |

## 审查输入

| 输入 | 路径 | 说明 |
|------|------|------|
| Requirement | proposal.md | 需求基线 |
| Design | design.md | 设计文档 |
| Spec | spec.md | 特性规格 |
| Plan | execution-plan.md | 执行计划 |

---

## 一、架构设计审查（标准复杂度：关键决策）

### 分层合规检查

| 调用方 | 被调用方 | 合规？ | 说明 |
|--------|----------|--------|------|
| ETS FrameNode.ets | ANI Bridge (ArkUIAniModule) | 合规 | 通过 native static 调用，符合现有模式 |
| ANI Bridge common_module.cpp | Modifier Bridge (ani_api.h) | 合规 | 通过函数指针表调用，符合 arkoala_native_ani 不直接链接引擎 core 的架构约束 |
| Modifier Bridge common_ani_modifier.cpp | PipelineContext | 合规 | 在引擎 core 内部，从 FrameNode 获取 context |

### 设计决策

| 决策 | 选项 | 结论 | 理由 |
|------|------|------|------|
| C++ 调用路径 | A) 直接调用 PipelineContext / B) Modifier 桥接 | B | arkoala_native_ani 不链接 ace_engine core，需通过 dlsym 加载的 modifier 函数指针表间接调用 |
| PipelineContext 获取方式 | A) PipelineContext::GetCurrentContext() / B) frameNode->GetContext() | B | 从 FrameNode 获取更精确，避免多实例场景下取错 context |
| ANI 签名 | A) "ossl:" 显式签名 / B) nullptr 跳过运行时检查 | B | 代码库中无 o 前缀签名的参考用例，使用 nullptr 更安全 |

---

## 二、规范符合性审查

### 需求覆盖

| AC | 是否实现 | 证据 | 结论 |
|----|----------|------|------|
| AC-1.1 FrameNode dispose 回调 | 是 | FrameNode.ets dispose() 调用 _FireArkUIObjectLifecycleCallback；设备验证: lifecycle_test.ets | PASS |
| AC-1b.1 TypedFrameNode dispose | 是 | TypedFrameNode 继承 FrameNode.dispose()，getNodeType() 返回具体类型 | PASS |
| AC-2.1 RenderNode dispose 回调 | 是 | RenderNode.ets dispose() 调用 _FireArkUIObjectLifecycleCallback；设备验证: lifecycle_test.ets | PASS |
| AC-3.1 BuilderNode dispose 回调 | 是 | BuilderNode.ets disposeNode() 调用 _FireArkUIObjectLifecycleCallback；设备验证: lifecycle_test.ets | PASS |
| AC-4.1 ComponentContent dispose 回调 | 是 | ComponentContent.ets dispose() 调用 _FireArkUIObjectLifecycleCallback；设备验证: lifecycle_test.ets | PASS |
| AC-5.1 数据格式一致性 | 是 | 4 参数 (WeakRef, className, nodeType, nodePtr) 与动态语言一致 | PASS |
| AC-6.1 幂等性 | 是 | 各 dispose 均有 isDisposed guard | PASS |
| AC-6.2 指针无效跳过 | 是 | 各实现均检查 nodePtr/frameNodePtr 非 0 后才调用 | PASS |
| AC-6.3 无回调安全跳过 | 是 | PipelineContext::FireArkUIObjectLifecycleCallback 内部 CHECK_NULL_VOID(objectLifecycleCallback_) | PASS |

### 多余实现

| 实现内容 | 是否在 Spec/Plan 中 | 风险 | 处理 |
|----------|---------------------|------|------|
| ani_api.h 新增 fireArkUIObjectLifecycleCallback 函数指针 | 是（实现阶段发现的架构约束） | 无 | 保留 |
| common_ani_modifier.cpp 新增 FireArkUIObjectLifecycleCallbackImpl | 是（实现阶段发现的架构约束） | 无 | 保留 |

### 理解偏差

| 检查项 | 结论 | 证据 |
|--------|------|------|
| AC 理解是否正确 | PASS | 4 参数与动态语言完全一致 |
| 边界和不做范围是否遵守 | PASS | 未修改 ComponentContent 的 isDisposed 逻辑（不在需求范围内） |
| 适用规则是否遵守 | PASS | 通过 modifier 桥接解决架构约束 |

---

## 三、代码质量审查

### Owner/Committer 视角

| 检查项 | 结论 | 证据 |
|--------|------|------|
| 模块边界是否合适 | PASS | ANI 函数在 common_module，modifier 桥接在 common_ani_modifier，ETS 在各节点文件 |
| 抽象层次是否合理 | PASS | 复用现有 modifier 函数指针表模式 |
| 是否符合仓内既有模式 | PASS | 注册模式同 _CheckThreadValid，modifier 桥接同其他 ANI 函数 |
| 是否引入难维护结构 | PASS | 仅新增一个函数指针和一个实现函数 |

### 工程质量检查

| 检查项 | 结论 | 证据 |
|--------|------|------|
| 架构/分层规则 | PASS | ETS → ANI Bridge → Modifier Bridge → PipelineContext，单向依赖 |
| API/兼容性规则 | PASS | 新增 Internal API（ani_api.h 函数指针），不影响 Public API |
| 构建与部件规则 | PASS | 未修改 BUILD.gn 依赖，编译通过 |
| 静态质量与风格 | PASS | 无新增 clang-tidy warning（已有 warning 为预存代码） |
| 测试质量与可测试性 | PASS | 4 个 UT 用例覆盖 FrameNode→GetContext→FireCallback 路径，编译通过；设备验证: lifecycle_test.ets + lifecycle_callback_test.cpp |
| 性能/安全/并发风险 | PASS | 同步调用，栈上分配结构体，无堆分配/锁/异步 |
| 多余实现或过度抽象 | PASS | 无 |

---

## 四、编译验证证据

| Target | 结果 | 时间 |
|--------|------|------|
| arkoala_native_ani (module.cpp, common_module.cpp) | build success | 2026-05-26 10:43 |
| ace_core_interfaces_native_node_ohos (common_ani_modifier.cpp) | 编译通过（.o 生成，无 error/warning） | 2026-05-26 15:35 |
| ace_core_interfaces_native_ohos (text_modifier.cpp) | 预存错误（与本 feature 无关） | — |

---

## 五、纠正循环

| 轮次 | 结论 | 处理动作 | 复检范围 |
|------|------|----------|----------|
| Review-1 | Approved | 用户已批准 Stage 3 | 全部 |

---

## 六、Open Issues

| 类型 | 问题 | 处理方式 | Owner | 状态 |
|------|------|----------|-------|------|
| follow-up | design.md 更新反映 modifier 桥接架构 | 长期 design.md 已迁移至 specs/04-common-capability/06-custom-node-capability/design.md，包含 modifier 桥接架构描述 | Claude | 已关闭 |

---

## 七、审查决策

| 项 | 内容 |
|----|------|
| Decision | Approved |
| 下一阶段 | Stage 4 发布 |
| Recheck Scope | — |
| 修改意见 | — |

**审查摘要：**
- 结论：实现覆盖全部 AC，架构通过 modifier 桥接解决链接约束，编译验证通过
- 必须修复项：无
- 可接受风险：text_modifier.cpp 预存错误阻塞完整 ace_engine target 编译，不影响本 feature
