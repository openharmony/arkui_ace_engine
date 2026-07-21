# check-execution-plan

> execution-plan.md 自检记录。

## 核验项

| 项 | 结论 | 依据 |
|----|------|------|
| spec 每 AC 在 plan 覆盖 | 是 | AC→Task 追溯表（AC-1.1~4.1 全覆盖） |
| 受影响文件全量清单 | 是 | 18 文件，逐层 + 归属 Task |
| 生成文件声明生成源 | 是 | 声明均手写（参照 Swiper 模式），非生成器；Arkoala 生成层不在范围 |
| 每 Task 有验证命令 | 是 | capi_all_modifiers_test / capi_unittest / linux_unittest_capi / ohos-sdk |
| 无 TBD/TODO/占位 | 是 | Owner 项以 Q-x 标注 |
| Task 自包含 | 是 | 3 张 Task 卡各有完整 Handoff 信息 |

## 长期资产回灌计划

FuncID/FeatID 待 Owner（Q-1）分配后，确定 `specs/<func-domain>/` 长期 spec/design 路径；当前 `.codespec` 短期产物完整，长期回灌在交付前安排（ArkUI profile 要求）。

## 设备最小矩阵（手表热路径）

- 手表（主目标）：表冠灵敏度属性 + ON_GESTURE_SWIPE 帧级事件，benchmark + 设备验证（Q-4 阈值）。
- 手机/平板/折叠屏：行为一致，回归。

## 结论

plan 与 spec/design 一致、可执行；Draft（上游 Blocked，不得启动实现）。
