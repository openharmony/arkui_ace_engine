/*
 * TASK-0: content_controller.cpp 修改点
 * 将 FilterWithRegex 改为调用共享工具函数
 *
 * 原代码 (L314-324):
 *   std::u16string ContentController::FilterWithRegex(const std::u16string& filter, std::u16string& result)
 *   {
 *       std::wstring wFilter = ContentToWstring(filter);
 *       std::wstring wResult = ContentToWstring(result);
 *       std::wregex wFilterRegex(wFilter);
 *       std::wstring wErrorText = std::regex_replace(wResult, wFilterRegex, L"");
 *       std::u16string errorText = ContentToU16string(wErrorText);
 *       result = RemoveErrorTextFromValue(result, errorText);
 *       return errorText;
 *   }
 *
 * 替换为:
 *   #include "text_filter_utils.h"
 *
 *   std::u16string ContentController::FilterWithRegex(const std::u16string& filter, std::u16string& result)
 *   {
 *       return TextFilterUtils::FilterWithRegex(filter, result);
 *   }
 *
 * 注意: ContentToWstring, ContentToU16string, RemoveErrorTextFromValue
 *       已迁移到 text_filter_utils.h/.cpp，content_controller.cpp 中的原定义需删除
 *       (如果它们仅在 content_controller.cpp 内部使用，可以直接删除；
 *        如果有其他调用方，需检查并改为 TextFilterUtils:: 命名空间调用)
 */

// === BUILD.gn / 相关 gni 修改 ===
// 在 frameworks/core/components_ng/pattern/text_field/ 目录下的 BUILD.gn 或 gni 中
// 新增 text_filter_utils.cpp 到源文件列表:
//
//   sources += [ "text_filter_utils.cpp" ]
