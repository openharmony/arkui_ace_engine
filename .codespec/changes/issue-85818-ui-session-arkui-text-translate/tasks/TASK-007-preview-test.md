# TASK007-preview test

## 任务元数据

| 字段 | 内容 |
|------|------|
| Task ID | TASK-007 |
| 标题 | Previewer 环境验证 ArkUI 页面文本提取 |
| 关联 Feature | FEAT-UISESSION-UNIFIED-TEXT-TRANSLATE |
| 目标仓库 | ace_engine, ide/tools/previewer |
| 目标模块 | adapter/preview/entrance, ide/tools/previewer, examples/UISessionTranslate/tools/host_preview |
| 分支 | dev |
| 优先级 | P0 |
| 复杂度 | 中 |
| 执行方式 | Host 预览环境验证 |

## 任务描述

### 做什么

1. 使用 SDK 编译产物中的 Previewer/PreviewerCLI，在 host 机器启动 UISessionTranslate HAP 的预览页面。
2. 通过 PreviewerCLI `remoteRequest` 命令模拟 uisession IPC 调用，触发 `pageTranslate/getText/start/collect/sendResult/reset/end/simulateTimeoutCleanup`。
3. 验证 ArkUI 文本提取结果只包含真实节点文本，例如 `nodeId=6, text="UISession Translate Hello", version=0`，并包含空内容 TextInput 当前实际展示的 placeholder 提示文本。
4. 验证当请求包含 ArkUI scope 且页面存在 ArkUI 文本时，不应混入 `nodeId=-1, text="empty", version=0`。
5. 验证当本次请求既没有 Web 文本，也没有 ArkUI 文本时，才返回单独一条 `nodeId=-1, text="empty", version=0`。
6. 使用 `inspector --business simpleTree` 抓取 uisession 可见控件树，辅助确认文本节点 ID 与 getText 返回的 `nodeId` 一致，并确认临时译文 DFX 字段进入 inspector 结果。
7. 验证用户已填充内容的 TextInput 不进入 getText/start 结果，回填译文也不得覆盖用户输入内容。
8. 验证 Start 后进入新页面时新上树渲染的 Text/List 文本能通过 `collect` 获取增量并回填译文。
9. 验证 Start 后 List 滚动导致 repeat 行进入屏幕时能通过 `collect` 获取新增可见文本，并能回填译文。
10. 验证指定 nodeId 的 `reset` 只恢复对应节点，全量 `reset` 和 `end` 恢复页面原文展示。
11. 验证 DFX 异常场景：Start 后已正常回填部分译文，后续译文长时间不返回时，Previewer 测试入口触发 timeout cleanup，并通过 `simpleTree` 确认临时译文清除、原文恢复。
12. 将验证过程固化到 `examples/UISessionTranslate/tools/host_preview/run_page_translate.sh`，方便回归。
13. `sendResult` 验证必须使用单次 `{"results":[...]}` 批量 payload 覆盖多个节点一起发送，不得以按节点循环多次发送替代批量能力。

### 不做什么

- 不依赖真机 SA dump。
- 不验证 OpenHarmony 设备侧 IPC binder 行为。
- 不打印页面正文以外的敏感业务数据；验证脚本只断言指定测试文本。
- 不把 Previewer 特有的模拟命令作为正式产品接口。

## 规格映射与边界

| AC | 来源 | 验证方式 |
|----|------|----------|
| AC-3, AC-4 | spec.md | Previewer getText/start/collect 验证 |
| AC-15 | spec.md | scope 包含 ArkUI/ArkWeb 时的兼容验证 |
| AC-18, AC-19, AC-20 | spec.md | remoteRequest 模拟 uisession 调用 |
| AC-23, AC-24, AC-25 | spec.md | Previewer getText/start/collect/sendResult/reset/end/simpleTree/screenshot 验证 |

| Rule ID | Must / Must Not |
|---------|-----------------|
| PREVIEW-IPC | PreviewerCLI 必须能通过统一 `remoteRequest` 扩展业务和方法，不为每个函数新增一个命令 |
| ARKUI-TEXT | ArkUI 文本返回真实 FrameNode ID、文本和 version |
| EMPTY-SENTINEL | 只有本次请求没有任何 Web/ArkUI 文本时，才返回单独一条 `-1/empty/0` |
| TEXTINPUT-PLACEHOLDER | 空内容 TextInput 的 placeholder 应被提取并可回填显示译文，用户填充值不应被提取或覆盖 |
| UNICODE-ESCAPED-RESULT | `sendResult` 使用 `\\uXXXX` 字面量发送首屏标题译文时，Preview 中应显示中文译文而不是反斜杠字符码 |
| CONTINUOUS-DELTA | Start 后新页面文本和 List 滚动进入视口的 repeat 文本必须作为连续翻译增量被 `collect` 收集 |
| RESET-SCOPE | 指定 nodeId reset 只恢复该节点，全量 reset/end 恢复全部临时译文 |
| DFX-TIMEOUT-CLEANUP | Previewer 测试入口 `simulateTimeoutCleanup` 仅用于 Host Preview 验证，模拟 SA 长时间不回填译文后的 timeout cleanup，必须进入恢复原文路径 |
| TREE-CHECK | 可通过 `inspector --business simpleTree` 触发 uisession manager 获取可见控件树，对照 getText 返回的 nodeId |
| BUILD-SDK | 修改 Previewer 或 preview adapter 后必须重新编译 ohos-sdk |

## 受影响文件

| 操作 | 文件路径 | 说明 |
|------|----------|------|
| 修改 | `OpenHarmony/ide/tools/previewer/PreviewerCLI.cpp` | 支持 `--timeout`，避免异步 getText 等待过短 |
| 修改 | `OpenHarmony/ide/tools/previewer/cli/CommandLineInterface.cpp` | `remoteRequest` 参数兼容处理 |
| 修改 | `OpenHarmony/ide/tools/previewer/cli/CommandLine.cpp` | `inspector --business simpleTree` 分支触发可见控件树获取 |
| 修改 | `OpenHarmony/ide/tools/previewer/jsapp/JsApp.h` | 增加可见控件树查询的通用 previewer 接口 |
| 修改 | `OpenHarmony/ide/tools/previewer/jsapp/rich/JsAppImpl.cpp` | `remoteRequest pageTranslate` 业务分发和 getText/start 结果组装 |
| 修改 | `OpenHarmony/ide/tools/previewer/jsapp/lite/JsAppImpl.cpp` | lite previewer 对 `simpleTree` 保持空实现，保证 SDK 多目标编译 |
| 修改 | `adapter/preview/entrance/ace_translate_manager.cpp` | 包含 ArkUI scope 时延后空结果判断，避免混入 Web 空哨兵 |
| 修改 | `adapter/preview/entrance/ui_session/ui_session_manager_preview.cpp` | preview 环境收集并返回 `GetVisibleInspectorTree` 结果 |
| 新增 | `examples/UISessionTranslate` | 独立 HostPreview 测试应用，包含稳定 ArkUI Text/Span、可翻译空 TextInput placeholder、用户输入排除、动态页面文本和 List 滚动 repeat 文本样例 |
| 新增/修改 | `examples/UISessionTranslate/tools/host_preview/run_page_translate.sh` | HostPreview getText/start/collect/sendResult/screenshot/reset/end/timeout cleanup 自动化验证脚本；sendResult 按阶段组装单次批量 `results` payload |

## 验证流程

### 1. 编译 SDK

从 OpenHarmony 根目录执行：

```bash
cd /home/l00441630/OpenHarmony
./build.sh --export-para PYCACHE_ENABLE:true --product-name ohos-sdk --ccache
```

通过标准：

- 构建输出包含 `ohos-sdk build success`。
- 最新 SDK 位于 `out/sdk/ohos-sdk/linux`。

### 2. 运行 HostPreview getText 验证脚本

```bash
cd /home/l00441630/OpenHarmony/foundation/arkui/ace_engine/examples/UISessionTranslate
./tools/host_preview/run_page_translate.sh
```

脚本会执行：

1. 编译 UISessionTranslate HAP。
2. 使用 `xvfb-run` 启动 Previewer。
3. 通过 PreviewerCLI 发送 `remoteRequest pageTranslate/getText`。
4. 解析 `Response:` JSON。
5. 断言返回文本包含 `UISession Translate Hello`、Span 拼接文本、空 TextInput placeholder 和页面按钮文本。
6. 断言存在真实文本时不包含 `nodeId=-1, text="empty"`，且用户填充的 TextInput 内容不被收集。
7. 执行 `start` 获取初始连续翻译节点，断言返回 version 为正数。
8. 对初始节点执行 `sendResult`，其中首屏标题译文使用 `\\u0055\\u0049...\\u6807\\u9898\\u5df2\\u7ffb\\u8bd1` 字面量，用 `simpleTree` 断言展示为 `UISession 标题已翻译` 且译文字段已进入 inspector。
9. 执行单节点 `reset`，断言只恢复被指定的节点，其他节点译文仍保留。
10. 在 Start 会话内点击进入 `pages/Dynamic`，通过 `collect` 验证新页面文本和初始可见 List repeat 行作为增量返回，并执行译文回填。
11. 点击 `Scroll Repeat List`，通过 `collect` 验证滚动后进入屏幕的后续 repeat 行作为增量返回，并执行译文回填。
12. 调用 `ScreenShot` 保存译文状态截图，再执行全量 `reset` 和 `end`，用 `simpleTree` 确认临时译文清理。
13. 再次执行 `start`，对当前可见文本只发送部分译文，故意不对剩余文本发送译文；通过 `simulateTimeoutCleanup` 模拟等待超时后的异常清理，用 `simpleTree` 确认已回填的临时译文被清除、原文恢复。

核心命令格式：

```bash
./PreviewerCLI --timeout 6000 --name previewer -- \
  --type action \
  --command remoteRequest \
  --version 1.0.1 \
  --args \
  --business pageTranslate \
  --method getText \
  --request '{"scope":2}' \
  --timeoutMs 2000
```

预期结果：

```json
{
  "success": true,
  "code": 0,
  "texts": [
    {
      "nodeId": 6,
      "text": "UISession Translate Hello",
      "version": 0
    }
  ]
}
```

### 3. 连续翻译增量验证

`run_page_translate.sh` 使用 `pageTranslate/beginCollect` 和 `pageTranslate/collect` 在 Previewer 内部建立一次临时收集窗口，用于验证连续翻译 Start 后的异步增量上报：

1. Start 后先回填初始页面节点译文。
2. beginCollect 后点击 `Open Dynamic Translate Page`，动态页面的 `Dynamic Page Fresh Text`、`Dynamic Page Detail Text` 和可见 `Repeat List Row xx` 必须出现在 collect 结果中。
3. beginCollect 后点击 `Scroll Repeat List`，Demo 通过 `Scroller.scrollToIndex(12)` 让后续 repeat 行进入屏幕，collect 结果中必须包含行号较后的 `Repeat List Row xx`。
4. 对 collect 到的 nodeId/version 发送中文译文，再截图保存对比证据。

### 4. 抓取 uisession 可见控件树辅助定位

Previewer 启动并加载页面后执行：

```bash
./PreviewerCLI --timeout 6000 --name previewer -- \
  --type action \
  --command inspector \
  --version 1.0.1 \
  --args \
  --business simpleTree \
  --timeoutMs 3000
```

该命令复用 `inspector`，通过 `business=simpleTree` 选择业务分支，不新增单函数命令；previewer 内部会模拟调用 `UiSessionManager::GetVisibleInspectorTree(config)`，最终触发 `PipelineContext::GetInspectorTree(true, config)`。

`simpleTree` 的 `ParamConfig` 默认全 true：

```text
interactionInfo=true
accessibilityInfo=true
cacheNodes=true
withWeb=true
withUIExtension=true
```

需要覆盖配置时，可直接在 `--args` 下传同名参数：

```bash
./PreviewerCLI --timeout 6000 --name previewer -- \
  --type action \
  --command inspector \
  --version 1.0.1 \
  --args \
  --business simpleTree \
  --timeoutMs 3000 \
  --interactionInfo false \
  --accessibilityInfo false \
  --cacheNodes true \
  --withWeb false \
  --withUIExtension false
```

也可以使用嵌套 `paramConfig`：

```bash
./PreviewerCLI --timeout 6000 --name previewer -- \
  --type action \
  --command inspector \
  --version 1.0.1 \
  --args \
  --business simpleTree \
  --paramConfig \
  --interactionInfo false \
  --accessibilityInfo true \
  --cacheNodes true \
  --withWeb false \
  --withUIExtension false
```

预期返回的 `result` 字符串是可见控件树 JSON，包含真实 Text 节点：

```text
root
  JsView id=3
    Column id=5
      Text id=6 content="UISession Translate Hello"
```

若 getText 返回 `nodeId=-1`，但 inspector 树中不存在对应节点，应优先检查是否为空结果哨兵逻辑误触发。

本地验证示例输出：

```text
simple_tree_ok=true
result_preview={"$type":"root","$children":[{"$type":"JsView", ... "Text" ... "UISession Translate Hello" ... }]}
```

### 5. 空结果场景验证

构造没有 Web 文本且没有 ArkUI 文本的页面，或请求不覆盖任何可提取文本后，再发 `pageTranslate/getText`。

预期只返回一条空结果：

```json
{
  "nodeId": -1,
  "text": "empty",
  "version": 0
}
```

如果同一响应中同时包含真实文本和 `-1/empty/0`，视为失败。

## 完成判据

- `remoteRequest` 支持通过 `business + method` 扩展调用 uisession 模拟能力。
- `getText` 在 Previewer 环境能提取 UISessionTranslate 页面 ArkUI 文本、Span 拼接文本和空 TextInput placeholder。
- 控件树中真实 Text 节点 ID 与 getText 返回的 `nodeId` 一致。
- 包含 ArkUI scope 且存在 ArkUI 文本时，不混入 `-1/empty/0`。
- 无任何可提取文本时，才返回单独一条 `-1/empty/0`。
- `sendResult` 能通过 PreviewerCLI 触发并返回成功，随后 `ScreenShot` 命令生成译文状态截图。
- `sendResult` 支持 unicode 转义字面量译文，首屏标题在 `simpleTree` 和截图中显示中文译文，不显示 `\\uXXXX` 字符码。
- Start 会话中动态页面新增文本、List 滚动进入视口 repeat 文本能通过 collect 返回并回填。
- 指定 nodeId 的 `reset`、全量 `reset` 和 `end` 能通过 PreviewerCLI 触发并返回成功，`simpleTree` 结果验证临时译文已按范围清理。
- DFX timeout cleanup 场景能通过 PreviewerCLI 触发并返回成功，`simpleTree` 结果验证临时译文清理和原文恢复。
- SDK 编译通过，HostPreview 脚本验证通过。

## 停止条件

- host 未安装 `xvfb`，Previewer 无法启动。
- SDK 编译失败，且失败与本任务改动无关，需要先记录构建环境问题。
- UISessionTranslate HAP 无法编译或 `pages/Index` 不再包含预期测试文本。
- Previewer `inspector` 无法返回控件树，需要先确认 Previewer 命令类型和加载状态。

## 验证检查清单

- [ ] `ohos-sdk` 编译成功
- [ ] `run_page_translate.sh` 运行成功
- [ ] 返回 `texts` 包含真实 ArkUI 文本节点
- [ ] 返回 `texts` 不混入 `nodeId=-1, text="empty"` 和真实文本
- [ ] `sendResult` remoteRequest 返回成功
- [ ] `sendResult` unicode 转义字面量译文解码后展示中文
- [ ] `start` 返回正版本号节点，`collect` 能获取动态页面和 List 滚动增量
- [ ] `ScreenShot` 命令生成译文状态截图
- [ ] `reset/end` remoteRequest 返回成功
- [ ] DFX timeout cleanup remoteRequest 返回成功，并验证译文清除、原文恢复
- [ ] `inspector --business simpleTree` 可抓取 uisession 可见控件树，并能对照真实 Text nodeId
- [ ] 空页面/无文本场景只返回单独一条 `-1/empty/0`
