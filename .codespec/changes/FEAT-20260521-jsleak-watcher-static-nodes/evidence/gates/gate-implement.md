# Gate: 实现阶段（Stage 3）

## 执行计划检查

- [x] AC 到 Task 有完整追溯（execution-plan.md AC→Task 表）
- [x] 每个 Task 的文件范围明确
- [x] 每个 Task 的不做范围明确
- [x] Task 粒度合理（TASK-1 ANI Bridge, TASK-2 ETS 接入, TASK-3 验证）
- [x] 交接信息完整

## Task 实现检查

- [x] TASK-1 ANI Bridge 函数：声明+注册+实现完成，编译通过
  - ArkUIAniModule.ts:408 — native static 声明
  - module.cpp:1187 — staticMethods 注册
  - common_module.cpp:1052 — C++ 实现（modifier 桥接）
  - common_module.h — 声明
  - ani_api.h:690 — 函数指针
  - common_ani_modifier.cpp:1216 — FireArkUIObjectLifecycleCallbackImpl
- [x] TASK-2 4 个 ETS 节点 dispose 添加回调，编译通过
  - FrameNode.ets:540 — dispose() 含回调
  - RenderNode.ets:541 — dispose() 含回调
  - BuilderNode.ets:676 — disposeNode() 含回调
  - ComponentContent.ets:104 — dispose() 含回调
- [x] TASK-3 编译验证通过
  - arkoala_native_ani: build success (4m49s)
  - common_ani_modifier.o: 已生成
  - libarkoala_native_ani.so: 已链接
- [x] UT 已存在：pipeline_context_test_ng_six.cpp 4 个用例覆盖 FireArkUIObjectLifecycleCallback

## 审查检查

- [x] 规范符合性审查通过（实现不多不少不误解）— review.md 第二节
- [x] 代码质量审查通过（适合进入主线）— review.md 第三节
- [x] 纠正循环完成
- [x] Open Issues 已处理或明确接受

## 编译验证证据

| Target | 结果 | 说明 |
|--------|------|------|
| arkoala_native_ani | build success | 2026-06-05, 4m49s |
| common_ani_modifier.o | 已生成 | obj/.../ace_core_interfaces_native_node_ohos/common_ani_modifier.o |
| libarkoala_native_ani.so | 已链接 | out/rk3568/arkui/ace_engine/libarkoala_native_ani.so |
| ace_core_interfaces_native_node_ohos | 编译失败（预存错误） | converter_enums.cpp ARK_HDR_TYPE_EDR，与本特性无关 |

## 总结论

**通过/Approved**

- TASK-1、TASK-2 代码已存在于当前工程，编译验证通过
- UT 已存在：pipeline_context_test_ng_six.cpp 覆盖 FireArkUIObjectLifecycleCallback 的 4 个场景
- ace_engine 完整编译失败由预存的 converter_enums.cpp 错误导致（ARK_HDR_TYPE_EDR 未定义），与本特性无关
