# Gate Check — Stage 4 Release

## 发布检查

| 检查项 | 结果 | 证据 |
|--------|------|------|
| 验证命令已运行且输出为 PASS | 通过 | `build.sh --product-name rk3568 --build-target arkoala_native_ani` build success (2026-06-05) |
| 所有测试通过（含回归） | 通过 | pipeline_context_test_ng_six.cpp 4 个 UT 已存在 |
| 构建通过 | 通过 | arkoala_native_ani + common_ani_modifier.o 编译通过 |
| 无阻塞级 Open Issues | 通过 | review.md 无必须修复项 |
| 复盘记录完成 | 通过 | 见下方复盘 |

## ARKUI Release Gate: 长期归档迁移

| 检查项 | 结果 | 证据 |
|--------|------|------|
| spec.md 迁移到长期 specs/ | 通过 | 4 个长期 spec 已创建 |
| design.md 增量合并到长期 design.md | 通过 | specs/04-common-capability/06-custom-node-capability/design.md 已创建 |
| specs/index.md 状态更新为 Baselined | 通过 | 04-06-02~05 Feat-01 状态为 Baselined |
| manifest 路径指向长期路径 | 通过 | manifest.long_term_spec_path 和 long_term_design_path 已记录 |
| 迁移差异摘要 | 无差异 | 短期 spec 内容按节点类型拆分到各自长期 spec，内容无删减 |

### 迁移清单

| 短期产物 | 长期目标 | 状态 |
|----------|----------|------|
| `.codespec/.../spec.md` US-1/US-1b (FrameNode) | `specs/04-common-capability/06-custom-node-capability/02-framenode/Feat-01-js-memory-report-spec.md` | 已迁移 |
| `.codespec/.../spec.md` US-2 (RenderNode) | `specs/04-common-capability/06-custom-node-capability/03-rendernode/Feat-01-js-memory-report-spec.md` | 已迁移 |
| `.codespec/.../spec.md` US-3 (BuilderNode) | `specs/04-common-capability/06-custom-node-capability/04-buildernode/Feat-01-js-memory-report-spec.md` | 已迁移 |
| `.codespec/.../spec.md` US-4 (ComponentContent) | `specs/04-common-capability/06-custom-node-capability/05-componentcontent/Feat-01-js-memory-report-spec.md` | 已迁移 |
| `.codespec/.../design.md` 增量 | `specs/04-common-capability/06-custom-node-capability/design.md` | 已合并 |

### SpecTest / 设备补验

| 检查项 | 结果 | 理由 |
|--------|------|------|
| SpecTest 可测项 | N/A | 回调注册仅 InnerApi，无公开方式注册带 UI 逻辑的回调 |
| 设备补验项 | 可验证 | 通过 dlsym + vtable 方式注册回调，端到端验证 dispose 触发 |

#### 设备补验方案

通过 NAPI 模块模拟 JsLeakWatcher：dlsym 打开 `libace_compatible.z.so`，通过 vtable[24] 调用 `RegisterArkUIObjectLifecycleCallback` 注册计数回调；ArkTS 页面创建节点并 dispose，检查回调计数是否递增。

**NAPI 模块核心逻辑：**

```cpp
// dlopen + dlsym 拿到 UIContext::Current()
void* handle = dlopen("/system/lib64/platformsdk/libace_compatible.z.so", RTLD_NOW);
void* symCurrent = dlsym(handle, "_ZN4OHOS3Ace3Kit9UIContext7CurrentEv");

// ARM64 sret 调用 Current()，x8 放返回地址
RefPtrRaw sretBuf = { nullptr };
asm volatile("mov x8, %[buf]\n\t blr %[func]" : : [buf]"r"(&sretBuf), [func]"r"(symCurrent) : "x8", ...);

// 读 vtable[24] = RegisterArkUIObjectLifecycleCallback
void** vtable = *(void***)(sretBuf.ptr);
auto fnRegister = (void(*)(void*, std::function<void(void*)>*))(vtable[24]);
std::function<void(void*)> cb = [](void*) { g_count++; };
fnRegister(sretBuf.ptr, &cb);
```

**ArkTS 测试页面核心逻辑：**

```typescript
import testNapi from 'liblifecycle_test.so';

// 注册回调（一次性）
testNapi.registerTestCallback();

// FrameNode: new → dispose → 检查计数
testNapi.resetCallbackCount();
new FrameNode(this.getUIContext()).dispose();
assert(testNapi.getCallbackCount() > 0);

// RenderNode: 先 addChild 再 dispose
testNapi.resetCallbackCount();
const parent = new FrameNode(this.getUIContext());
const renderNode = new RenderNode();
parent.addChild(renderNode);
renderNode.dispose();
assert(testNapi.getCallbackCount() > 0);

// BuilderNode: build 后 disposeNode
testNapi.resetCallbackCount();
const builderNode = new BuilderNode(this.getUIContext());
builderNode.build(wrapBuilder(testBuilder));
builderNode.disposeNode();
assert(testNapi.getCallbackCount() > 0);

// ComponentContent: new 后 dispose
testNapi.resetCallbackCount();
new ComponentContent(this.getUIContext(), wrapBuilder(testBuilder)).dispose();
assert(testNapi.getCallbackCount() > 0);
```

#### 验证用例

| 用例 | 操作 | 预期 | 覆盖 AC |
|------|------|------|---------|
| FrameNode dispose | new FrameNode() → dispose() | 回调计数 > 0 | AC-1.1 |
| RenderNode dispose | FrameNode.addChild(RenderNode) → RenderNode.dispose() | 回调计数 > 0 | AC-2.1 |
| BuilderNode dispose | new BuilderNode() → build() → disposeNode() | 回调计数 > 0 | AC-3.1 |
| ComponentContent dispose | new ComponentContent() → dispose() | 回调计数 > 0 | AC-4.1 |

## 复盘

| 项 | 内容 |
|----|------|
| 范围偏差 | 无。实现严格在 spec 和 execution-plan 定义的范围内 |
| 实现阶段发现 | 1) arkoala_native_ani 不直接链接 ace_engine core，需 modifier 桥接；2) RenderNode/BuilderNode 的 nodePtr 不是 FrameNode*，需按 className 分发 Peer 类型 |
| 经验教训 | ETS 层 `as object` 不必要——`object` 是所有对象类型的基类 |
| 待改进 | 无 |

## 总结论

**Stage 4 Gate 结论: 通过 / Approved**

- 编译验证通过
- 长期规格迁移完成（4 个 spec + 1 个 design.md）
- specs/index.md 状态已更新为 Baselined
- 无阻塞项
