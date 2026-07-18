# Lineage

| 字段 | 值 |
|----|----|
| Lineage | new-on-legacy（建立在两个已合并 PR 初版之上，本期做规格化 + 行为对齐） |
| Target Release | TBD（ArkUI-X weekly 跟随） |
| Source | 需求 Owner 提出 + 已合并实现 |
| Original Docs | `arkui_for_android` PR #770、`arkui_for_ios` PR #691 |
| Source Code Evidence | `arkui_for_android/entrance/java/jni/backtrace_handler.{h,cpp}`、`arkui_for_ios/osal/backtrace_handler.{h,cpp}` |
| Compatibility Boundary | 对外 API（`InitBacktraceHandler()` / `DumpBacktraceFromFp(fp)`）与输出整体结构不变；4 项对齐 deltas 属可观察行为细化，详见 spec.md §兼容性 |
| Migration Status | 登记于 `.codespec/changes/feat-arkuix-native-crash-backtrace`，2026-07-15 |
| Supersedes | 两 PR 各自隐含的、未对齐的初版规格（#0 语义、镜像名截断、帧格式、flush 策略） |
| Superseded By | — |

## 涉及仓与落点

| 仓 | 角色 | 落点 |
|----|------|------|
| `arkui_for_android` | adapter（独立仓，ace_engine 子目录 `adapter/android`） | `entrance/java/jni/backtrace_handler.{h,cpp}` + `jni_load.cpp` + `BUILD.gn` |
| `arkui_for_ios` | adapter（独立仓，ace_engine 子目录 `adapter/ios`） | `osal/backtrace_handler.{h,cpp}` + `stage/ability/StageApplication.mm` + `osal/BUILD.gn` |
| `ace_engine`（本仓） | umbrella / 规格基线 | `.codespec/changes/feat-arkuix-native-crash-backtrace/`（仅规格，不含实现代码） |

## 决策溯源

| 决策 | 结论 | 依据 |
|------|------|------|
| 代码落点 | 维持各 adapter 仓独立副本，不抽共享核心到 ace_engine | Owner 确认 2026-07-15（ADR-1） |
| 信号集合 | 5 个：SEGV/ABRT/BUS/ILL/FPE | 与两 PR 一致（ADR-2） |
| 注册时机 | 统一规则·各自实例化点 | Android=JNI_OnLoad 运行时拉起后；iOS=initApplication 起始（ADR-3） |
| 行为对齐 | 落实 iOS 2 项（镜像名完整 + 帧格式 `name +0x<off>` 加空格）+ Android Delta-1（#0=mcontext.pc，对齐 iOS）；flush 不统一（输出等价的内部细节） | Owner 确认 + 真实栈勘误之勘误（ADR-4） |
