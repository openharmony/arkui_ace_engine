# execution-plan.md — Image 组件基础内存优化

## 概述

本执行计划将 design.md 中的 ADR 拆分为任务。ADR-4（Alt 状态合并）因 ROI 低已取消。

## 修正说明

1. ADR-1 原计划使用 `RefPtr<ImageSourceInfo>`，但源码确认 `ImageSourceInfo` 不继承 `AceType`，改为使用 `std::shared_ptr<ImageSourceInfo>`。
2. ADR-4（Alt 状态合并）取消：节省 64B 但需改动 ~70 处，ROI 低。

---

## 任务列表

| Task ID | 标题 | ADR | 状态 |
|---------|------|-----|------|
| TASK-01 | ImageDfxConfig 改为 shared_ptr 按需创建和共享 | ADR-2 | 完成 |
| TASK-02 | ImageSourceInfo 改为 shared_ptr 共享 | ADR-1 | 完成 |
| TASK-03 | ImageSourceInfo 内部字段精简 | ADR-3 | 完成 |
| TASK-04 | Alt/AltError 状态合并 | ADR-4 | 取消 |
| TASK-05 | Bool 位域合并 | ADR-6 | 待实现 |

## 已完成节省

| Task | 节省(结构体级) |
|------|---------------|
| TASK-03 | ~8B |
| TASK-01 | ~576B |
| TASK-02 | ~1,792B |
| **合计** | **~2,376B** |

## 编译验证命令

```bash
./build.sh --product-name rk3568 --build-target ace_engine --ccache --fast-rebuild
```
