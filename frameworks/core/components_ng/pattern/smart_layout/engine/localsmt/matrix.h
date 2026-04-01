/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once
#include <iostream>
#include <map>
#include <vector>

#include "ration_num.h"

void SwapRows(std::vector<std::vector<RationNum>>& matrix, size_t i, size_t j);

int FindPivot(const std::vector<std::vector<RationNum>>& matrix, size_t col, size_t startRow);

void TransferToInteger(std::vector<RationNum>& row);

void TransferToInteger(std::vector<std::vector<RationNum>>& matrix);

void MergeRows(std::vector<RationNum>& upperRow, const std::vector<RationNum>& lowRow);

void ToUpperTriangle(std::vector<std::vector<RationNum>>& matrix);

void ToDiagonal(std::vector<std::vector<RationNum>>& matrix);

void GaussianElimination(std::vector<std::vector<RationNum>>& matrix);

bool ContainsShortRow(const std::vector<std::vector<RationNum>>& matrix);

bool IsAllZeroRow(const std::vector<RationNum>& row);

