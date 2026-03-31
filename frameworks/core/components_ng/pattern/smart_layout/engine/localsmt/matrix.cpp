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

#include "matrix.h"

#include <cstdint>

void SwapRows(std::vector<std::vector<RationNum>>& matrix, size_t i, size_t j)
{
    if (i < matrix.size() && j < matrix.size()) {
        swap(matrix[i], matrix[j]);
    }
}

int FindPivot(const std::vector<std::vector<RationNum>>& matrix, size_t col, size_t startRow)
{
    auto minRow = startRow;
    RationNum minAbs = RationNum(INT32_MAX);
    for (auto i = startRow; i < matrix.size(); ++i) {
        if (matrix[i][col].Abs() < minAbs && matrix[i][col] != 0) {
            minRow = i;
            minAbs = matrix[i][col].Abs();
        }
    }
    return minRow;
}

void TransferToInteger(std::vector<RationNum>& row)
{
    int64_t mTotal = 1;
    for (const auto& item : row) {
        mTotal *= item.m;
    }
    for (auto& item : row) {
        item *= mTotal;
    }
    int64_t result = row[0].n;
    for (const auto& item : row) {
        result = std::gcd(result, item.n);
        if (result == 1) {
            return;
        }
    }
    if (result != 1) {
        for (auto& item : row) {
            item /= result;
        }
    }
}

void TransferToInteger(std::vector<std::vector<RationNum>>& matrix)
{
    for (auto& row : matrix) {
        if (!IsAllZeroRow(row)) {
            TransferToInteger(row);
        }
    }
}

// update the upper row by low row
void MergeRows(std::vector<RationNum>& upperRow, const std::vector<RationNum>& lowRow)
{
    std::map<RationNum, int> portion2fre;
    int zeroFre = 0;
    for (size_t cIdx = 0; cIdx < lowRow.size() - 1; cIdx++) {
        if (lowRow[cIdx] == 0) {
            continue;
        }
        if (upperRow[cIdx] == 0) {
            zeroFre++;
        } else {
            RationNum p = upperRow[cIdx] / lowRow[cIdx];
            if (portion2fre.find(p) == portion2fre.end()) {
                portion2fre[p] = 1;
            } else {
                portion2fre[p]++;
            }
        }
    }
    RationNum maxP = RationNum(0);
    int maxPFre = 0;
    for (const auto& pair : portion2fre) {
        if (pair.second > maxPFre) {
            maxP = pair.first;
            maxPFre = pair.second;
        }
    }
    if (maxPFre > zeroFre) {
        for (size_t cIdx = 0; cIdx < lowRow.size(); cIdx++) {
            upperRow[cIdx] -= maxP * lowRow[cIdx];
        }
    }
}

void ToUpperTriangle(std::vector<std::vector<RationNum>>& matrix)
{
    int32_t rowNum = static_cast<int32_t>(matrix.size());
    int32_t collomNum = static_cast<int32_t>(matrix[0].size());

    // turn the matrix to upper matrix
    for (int32_t i = 0; i < rowNum && i < collomNum; ++i) {
        // find the pivot with min non-zero abs value, if cannot find, means the whole collom is zero
        int32_t minRow = FindPivot(matrix, i, i);
        if (matrix[minRow][i] == 0) {
            continue;
        }
        // swap row if the min non-zero abs row is not the current one
        if (minRow != i) {
            SwapRows(matrix, i, minRow);
        }
        // eleminate vars
        for (int32_t j = i + 1; j < rowNum; ++j) {
            if (matrix[j][i] == 0) {
                continue;
            }
            RationNum factor = matrix[j][i] / matrix[i][i];
            for (int32_t k = i; k < collomNum; ++k) {
                matrix[j][k] -= factor * matrix[i][k];
            }
        }
    }
}

void ToDiagonal(std::vector<std::vector<RationNum>>& matrix)
{
    int32_t rowNum = static_cast<int32_t>(matrix.size());
    if (rowNum == 0) {
        return;
    }
    int32_t collomNum = static_cast<int32_t>(matrix[0].size());
    
    // turn the upper triangle matrix to diagonal matrix
    for (int32_t i = rowNum - 1; i >= 0; i--) {
        bool nonZero = false;
        int32_t nonZeroIdx = i;
        for (; nonZeroIdx < collomNum - 1; nonZeroIdx++) {
            if (matrix[i][nonZeroIdx] != 0) {
                nonZero = true;
                break;
            }
        }
        // if the row are all zeros, continue, otherwise delete other rows by the non-zero one
        if (!nonZero) {
            continue;
        }
        for (int32_t j = i - 1; j >= 0; j--) {
            RationNum factor = matrix[j][nonZeroIdx] / matrix[i][nonZeroIdx];
            for (int32_t k = nonZeroIdx; k < collomNum; k++) {
                matrix[j][k] -= factor * matrix[i][k];
            }
        }
    }
}

void GaussianElimination(std::vector<std::vector<RationNum>>& matrix)
{
    int32_t rowNum = static_cast<int32_t>(matrix.size());
    if (rowNum == 0) {
        return;
    }
    
    ToUpperTriangle(matrix);
    ToDiagonal(matrix);
    
    for (int32_t i = rowNum - 1; i >= 0; i--) {
        for (int32_t j = i - 1; j >= 0; j--) {
            MergeRows(matrix[j], matrix[i]);
        }
    }
    TransferToInteger(matrix);
}

bool ContainsShortRow(const std::vector<std::vector<RationNum>>& matrix)
{
    if (matrix.empty() || matrix[0].empty()) {
        return false;
    }
    size_t collomNum = matrix[0].size();
    for (size_t rIdx = 0; rIdx < matrix.size(); rIdx++) {
        if (matrix[rIdx].size() != collomNum) {
            continue;
        }
        int nonZeroCnt = 0;
        for (size_t cIdx = 0; cIdx < collomNum - 1; cIdx++) {
            if (matrix[rIdx][cIdx] != 0) {
                nonZeroCnt++;
            }
        }
        if (nonZeroCnt <= 2) { // 2: means the row has at most 2 non-zero items, which is a short row
            return true;
        }
    }
    return false;
}

bool IsAllZeroRow(const std::vector<RationNum>& row)
{
    for (const auto& item : row) {
        if (item != 0) {
            return false;
        }
    }
    return true;
}
