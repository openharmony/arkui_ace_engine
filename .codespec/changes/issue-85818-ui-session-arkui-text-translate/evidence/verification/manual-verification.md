# Manual Verification

> TASK-006 真机 dump 验证记录模板。所有输出只记录安全摘要，不记录原文或译文正文。

## 环境

| 字段 | 记录 |
|------|------|
| 设备型号 | TBD |
| OpenHarmony 版本/commit | TBD |
| ace_engine commit | TBD |
| 构建产品 | rk3568 |
| 测试应用 | TBD |
| ui_session_sample 进程状态 | TBD |

## Dump 命令记录

| 场景 | 命令 | 预期 | 实际 | 结果 |
|------|------|------|------|------|
| Get ArkUI-only | TBD | 返回 ArkUI Text/Span/RichEditor 只读节点摘要：nodeId、version、textLength、scope、requestId | TBD | TBD |
| Get ARKUI_ARKWEB | TBD | 返回 ArkUI 节点摘要，并确认 ArkWeb 走现有脚本注入路径 | TBD | TBD |
| Start ArkUI-only | TBD | 初始节点摘要上报，后续实际绘制新增/内容变化节点增量上报 | TBD | TBD |
| End | TBD | 停止增量上报，ArkUI/Web 恢复原文展示 | TBD | TBD |
| Reset node | TBD | 指定 nodeId 恢复原文，其他节点不受影响 | TBD | TBD |
| Send result | TBD | 指定 nodeId/version 译文回填成功；version 不匹配时单条忽略 | TBD | TBD |
| Send result batch | TBD | 同一条 `SendPageTranslateResult` 使用 `{"results":[...]}` 批量发送至少 3 个节点，合法项按 nodeId/version/source hash 独立回填 | TBD | TBD |
| Send result invalid payload | TBD | 缺少 nodeId/version、`nodeId < 0`、译文为空或全批无合法项时返回 `PARAM_INVALID`；批量中合法项继续处理 | TBD | TBD |
| Send result unicode escaped | TBD | `translatedText` 传入 `\\u8be6\\u60c5\\u4e2d\\u6587` 等 unicode 转义字面量时，界面展示真实中文，不展示反斜杠字符码 | TBD | TBD |
| GetCurrentAbilityLanguageInfo | TBD | 同步返回当前 Ability 实例生效 language/region | TBD | TBD |
| Invalid scope bit | TBD | 返回参数错误，不注册 callback、不触发上报 | TBD | TBD |

## 异常与 DFX

| 场景 | 触发方式 | 预期日志摘要 | 实际日志摘要 | 结果 |
|------|----------|--------------|--------------|------|
| SA death | TBD | processId、activeSession、cleanupResult；不含正文；页面恢复原文 | TBD | TBD |
| 单次 Get 请求 timeout | TBD | requestId、scope、requestType、elapsedMs、cleanupResult；清 callback、snapshot cache 和调用方 pid，不触发连续 Start End/Reset | TBD | TBD |
| Start 初始无文本 | TBD | ownerPid、scope、started=true；不因初始无文本 timeout 自动 End，后续新增/变化节点仍可上报 | TBD | TBD |
| 译文等待 5s watchdog | TBD | requestId、nodeId、version、textLength、elapsedMs、saAlive；仅 `nodeId >= 0` 真实节点触发，只告警不结束会话 | TBD | TBD |
| empty/no-content 哨兵 | TBD | `nodeId < 0` 不启动译文等待 watchdog，也不能作为 SendPageTranslateResult 合法项 | TBD | TBD |
| 迟到 callback | TBD | requestId mismatch 或 expired；丢弃且不影响新会话 | TBD | TBD |

## Web 兼容

| 验证项 | 预期 | 实际 | 结果 |
|--------|------|------|------|
| 老 Web-only 获取接口 | 行为保持不变 | TBD | TBD |
| 老 Web-only Start/End | 行为保持不变 | TBD | TBD |
| 统一 ARKUI_ARKWEB | ArkUI 与 ArkWeb 同时覆盖，ArkWeb 仍走脚本注入 | TBD | TBD |

## Host Preview 验证

| 场景 | 命令 | 预期 | 实际 | 结果 |
|------|------|------|------|------|
| UISessionTranslate getText/start/collect/sendResult/screenshot/reset/end | `examples/UISessionTranslate/tools/host_preview/run_page_translate.sh` | 脚本构建 HAP，启动 Previewer，通过 `remoteRequest pageTranslate/getText` 返回真实 ArkUI 文本节点；存在真实文本时不混入 `-1/empty/0`；`start` 返回正版本号初始节点；`collect` 覆盖动态新页面文本和 List 滚动 repeat 文本进入视口；随后 `sendResult --result {"results":[...]}` 单次批量回填多个中文译文，调用 `ScreenShot` 生成原文/译文截图，再执行单节点 reset、全量 reset 和 end | TBD | TBD |
| unicode 转义译文回填 | 同上，查看 `send_result_*`、`translated_simple_tree_output` 和 `translated_screenshot` | 首屏标题通过 `\\uXXXX` 字面量发送译文，Inspector 和截图展示 `UISession 标题已翻译` 中文，不展示字符码 | TBD | TBD |
| simpleTree nodeId 对照 | 同上，查看脚本输出的 `simple_tree_output` | `inspector --business simpleTree` 返回可见控件树，可用于对照 getText 真实文本节点 id | TBD | TBD |
| 非目标输入文本过滤 | 同上 | 空 TextInput placeholder 应被提取并翻译；`TextInput` 中的固定用户填充值不应出现在 getText/start 结果中，也不应被译文覆盖 | TBD | TBD |
| 连续翻译动态页面 | 同上，查看 `dynamic_collect_output` | Start 后进入 `pages/Dynamic`，新页面 Text 和可见 List repeat 行作为增量返回并可回填 | TBD | TBD |
| 连续翻译滚动 List | 同上，查看 `scroll_collect_output` | Start 后点击 `Scroll Repeat List`，滚动进入屏幕的后续 repeat 行作为增量返回并可回填 | TBD | TBD |
| reset/end 恢复 | 同上，查看 `reset_title_simple_tree_output`、`reset_all_simple_tree_output`、`end_simple_tree_output` | 指定 nodeId reset 只恢复该节点；全量 reset 和 end 后 simpleTree 中不再包含临时译文 | TBD | TBD |
| DFX result watchdog | 同上，查看 `dfx_result_watchdog_output`、`dfx_result_watchdog_simple_tree_output` | Start 后先正常回填部分可见文本译文，再模拟 SA 长时间不返回后续真实节点译文；watchdog 返回成功且仅告警、不自动 End/Reset；随后 reset/end 后 simpleTree 中不再包含临时译文且原文恢复 | TBD | TBD |

## 单元测试与编译记录

| 场景 | 命令 | 预期 | 实际 | 结果 |
|------|------|------|------|------|
| ui_content_stub_unittest_linux 编译 | `./build.sh --export-para PYCACHE_ENABLE:true --product-name rk3568 --build-target ui_content_stub_unittest_linux --ccache` | host unittest 目标编译通过 | 2026-06 已验证编译通过 | PASS |
| ui_content_stub_unittest 运行 | `./out/rk3568/clang_x64/tests/unittest/ace_engine/ace_engine/adapter/ui_content_stub_unittest` | IPC/result/DFX 相关用例全部通过 | 50/50 passed | PASS |
| content_change_manager_translate_test_ng 编译 | `./build.sh --export-para PYCACHE_ENABLE:true --product-name rk3568 --build-target content_change_manager_translate_test_ng --ccache` | ContentChangeManager translate 用例 host 目标编译通过 | 2026-06 已验证编译通过 | PASS |
| ui_session 目标编译 | `./build.sh --export-para PYCACHE_ENABLE:true --product-name rk3568 --build-target ui_session --ccache` | ui_session 相关库编译通过 | 2026-06 已验证编译通过 | PASS |

## 结论

| 项 | 结论 |
|----|------|
| 是否通过 | TBD |
| 阻塞问题 | TBD |
| 后续动作 | TBD |
