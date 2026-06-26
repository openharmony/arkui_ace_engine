# Implement Gate

| 检查项 | 结果 | 证据 |
|--------|------|------|
| TASK-001 实现完成 | 已完成 | ace_kit 基类 89 行 + frameworks 继承版 92 行 + .cpp ~30 处命名空间更新 + mock 更新 + CalcDimension include 修复 |
| TASK-002 声明和实现完成 | 已完成 | ui_context.h 4 个虚方法 + ui_context_impl.h 4 个 override + ui_context_impl.cpp 4 个实现 + 13 个单元测试用例 |
| TASK-003 声明和实现完成 | 已完成 | tabs.h 8 个重载声明 + tabs.cpp 8 个重载实现 + 16 个单元测试用例 |
| 174 个消费者文件零改动 | 通过 | 继承架构保证 `ResourceParseUtils::Xxx` 通过继承解析到基类方法 |
| 消费者改动为零（UIContext/Tabs） | 通过 | UIContext 纯新增虚方法；Tabs 纯新增重载，原方法不变 |
| 全量编译通过 | 通过（C++ 编译） | `./build.sh --product-name rk3568 --build-target ace_engine`：614/752 步骤，0 FAILED/error，error.log 未更新 |
| 单元测试编写完成 | 已完成 | TASK-002：13 个用例追加到 ui_context_impl_test.cpp；TASK-003：16 个用例新建 tabs_test.cpp |
| mock_ui_context_impl.cpp 更新 | 已完成 | 新增 GetConfigPerform/GetInstanceId/HasDarkResource/GetInvertFunc 4 个 stub 实现 |
| BUILD.gn 更新 | 已完成 | ace_kit_test 新增 tabs.cpp 源文件和 tabs_test.cpp 测试文件 |
| 设计文档已同步更新 | 通过 | design.md ADR-1、spec.md Delta/FR/AC、execution-plan.md 已更新 |

**决策:** In Progress（待编译验证测试 + 运行单元测试）
**审批人:** 待确认
**日期:** 2026-05-11
**阻塞项:** 编译验证新增测试文件 + 运行单元测试
