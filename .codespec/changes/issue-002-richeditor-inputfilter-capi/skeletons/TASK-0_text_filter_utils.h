/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * ...
 *
 * TASK-0: 从 content_controller.cpp 提取的共享过滤工具函数
 * 参考: content_controller.cpp FilterWithRegex (L314-324)
 *       content_controller.cpp ContentToWstring (L41-51)
 *       content_controller.cpp ContentToU16string (L53-62)
 *       content_controller.cpp RemoveErrorTextFromValue (L289-308)
 */

#ifndef FOUNDATION_ArkUI_AceEngine_Frameworks_Core_ComponentsNg_Pattern_TextField_TEXT_FILTER_UTILS_H
#define FOUNDATION_ArkUI_AceEngine_Frameworks_Core_ComponentsNg_Pattern_TextField_TEXT_FILTER_UTILS_H

#include <string>
#include <regex>

namespace OHOS::Ace::Ng::TextFilterUtils {

/**
 * @brief Convert u16string to wstring for regex processing (supports unicode).
 *
 * Migrated from content_controller.cpp L41-51.
 * Original: inline std::wstring ContentToWstring(const std::u16string& str)
 */
std::wstring ContentToWstring(const std::u16string& str);

/**
 * @brief Convert wstring back to u16string after regex processing.
 *
 * Migrated from content_controller.cpp L53-62.
 * Original: inline std::u16string ContentToU16string(const std::wstring& str)
 */
std::u16string ContentToU16string(const std::wstring& str);

/**
 * @brief Remove error text (filtered-out characters) from the original value,
 *        preserving the order of remaining characters.
 *
 * Migrated from content_controller.cpp L289-308.
 * Original: std::u16string ContentController::RemoveErrorTextFromValue(...)
 */
std::u16string RemoveErrorTextFromValue(const std::u16string& value, const std::u16string& errorText);

/**
 * @brief Filter input text with a regex whitelist pattern.
 *
 * Characters matching the regex are kept; non-matching characters are extracted as errorText.
 * The result parameter is modified in-place to remove error characters.
 *
 * Migrated from content_controller.cpp L314-324.
 * Original: std::u16string ContentController::FilterWithRegex(...)
 *
 * @param filter The regex pattern (u16string) — whitelist: matching chars are kept.
 * @param result The input text to filter. Modified in-place to remove non-matching chars.
 * @return The error text (filtered-out characters) as u16string.
 */
std::u16string FilterWithRegex(const std::u16string& filter, std::u16string& result);

} // namespace OHOS::Ace::Ng::TextFilterUtils

#endif // FOUNDATION_ArkUI_AceEngine_Frameworks_Core_ComponentsNg_Pattern_TextField_TEXT_FILTER_UTILS_H
