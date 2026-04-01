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

#include "../utils/matrix.h"
#include "nia_ls.h"
#define NLS_DEBUG
namespace niaOverall {
bool IsSameCls(const std::vector<int>& cl1, const std::vector<int>& cl2);

namespace {
bool IsBoolUnitClause(const clause& currentClause, const std::vector<lit>& lits)
{
    return !currentClause.isDelete && currentClause.literals.size() == 1 &&
           !lits[std::abs(currentClause.literals[0])].isNiaLit;
}

int FindBoolLiteralIndexForVar(const clause& currentClause, const std::vector<lit>& lits, uint64_t unitVar)
{
    for (uint64_t litIdx = 0; litIdx < currentClause.literals.size(); litIdx++) {
        const int litIdInClause = currentClause.literals[litIdx];
        const lit& currentLit = lits[std::abs(litIdInClause)];
        if (!currentLit.isNiaLit && currentLit.delta == unitVar) {
            return static_cast<int>(litIdx);
        }
    }
    return -1;
}

void RemoveClauseIdxFromVar(variable& currentVar, uint64_t clauseIdx)
{
    for (uint64_t deleteIdx = 0; deleteIdx < currentVar.clauseIdxs.size(); deleteIdx++) {
        if (currentVar.clauseIdxs[deleteIdx] != clauseIdx) {
            continue;
        }
        currentVar.clauseIdxs[deleteIdx] = currentVar.clauseIdxs.back();
        currentVar.clauseIdxs.pop_back();
        return;
    }
}

void DeleteSatisfiedClause(LsSolver& solver, clause& currentClause, uint64_t clauseIdx, uint64_t unitVar)
{
    currentClause.isDelete = true;
    for (int litIdxInClause : currentClause.literals) {
        lit& currentLit = solver._lits[std::abs(litIdxInClause)];
        if (currentLit.isNiaLit || currentLit.delta == unitVar) {
            continue;
        }
        RemoveClauseIdxFromVar(solver._vars[currentLit.delta.ToInt()], clauseIdx);
    }
}

void RemoveUnsatisfiedLiteral(
    LsSolver& solver, clause& currentClause, uint64_t literalIdx, uint64_t clauseIdx, std::stack<uint64_t>& unitClause)
{
    currentClause.literals[literalIdx] = currentClause.literals.back();
    currentClause.literals.pop_back();
    if (IsBoolUnitClause(currentClause, solver._lits)) {
        unitClause.push(clauseIdx);
    }
}

bool ClausesMatchExceptOppositeLits(
    const std::vector<int>& clausePreLits, const std::vector<int>& clausePosLits, int preIdx, int posIdx)
{
    if (clausePreLits.size() != clausePosLits.size()) {
        return false;
    }
    std::unordered_map<int, int> count;
    for (int litIdx : clausePreLits) {
        ++count[litIdx];
    }
    for (int litIdx : clausePosLits) {
        --count[litIdx];
    }
    count[preIdx]--;
    count[posIdx]++;
    for (const auto& [_, diff] : count) {
        if (diff != 0) {
            return false;
        }
    }
    return true;
}

void RemoveDuplicateClauses(std::vector<std::vector<int>>& clauseVec)
{
    std::sort(clauseVec.begin(), clauseVec.end());
    size_t uniqueClauseCount = 0;
    for (size_t clauseIdx = 0; clauseIdx < clauseVec.size(); clauseIdx++) {
        if (uniqueClauseCount > 0 && IsSameCls(clauseVec[clauseIdx], clauseVec[uniqueClauseCount - 1])) {
            continue;
        }
        clauseVec[uniqueClauseCount++] = clauseVec[clauseIdx];
    }
    clauseVec.resize(uniqueClauseCount);
}

void RemoveDuplicateClauseLiterals(std::vector<int>& clauseLits)
{
    size_t uniqueLiteralCount = 0;
    for (int litIdx : clauseLits) {
        if (uniqueLiteralCount > 0 && clauseLits[uniqueLiteralCount - 1] == litIdx) {
            continue;
        }
        clauseLits[uniqueLiteralCount++] = litIdx;
    }
    clauseLits.resize(uniqueLiteralCount);
}

void MarkUnitLiterals(const std::vector<std::vector<int>>& clauseVec, std::vector<bool>& unitLit, uint64_t numLits)
{
    for (const auto& clauseLits : clauseVec) {
        if (clauseLits.size() != 1) {
            continue;
        }
        unitLit[clauseLits[0] + numLits] = true;
    }
}

bool ClauseContainsUnitLiteral(const std::vector<int>& clauseLits, const std::vector<bool>& unitLit, uint64_t numLits)
{
    if (clauseLits.size() == 1) {
        return false;
    }
    for (int litIdx : clauseLits) {
        if (unitLit[litIdx + numLits]) {
            return true;
        }
    }
    return false;
}

void FilterClausesSatisfiedByUnitLiterals(
    std::vector<std::vector<int>>& clauseVec, const std::vector<bool>& unitLit, uint64_t numLits)
{
    size_t keptClauseCount = 0;
    for (const auto& clauseLits : clauseVec) {
        if (clauseLits.empty() || ClauseContainsUnitLiteral(clauseLits, unitLit, numLits)) {
            continue;
        }
        clauseVec[keptClauseCount++] = clauseLits;
    }
    clauseVec.resize(keptClauseCount);
}
} // namespace

// input transformation
void LsSolver::SplitString(std::string& inString, std::vector<std::string>& strVec, std::string pattern = " ")
{
    std::string::size_type pos;
    inString += pattern;
    std::string::size_type size = inString.size();
    std::string::size_type i = 0;
    while (i < size) {
        pos = inString.find(pattern, i);
        if (pos < size) {
            std::string s = inString.substr(i, pos - i);
            strVec.push_back(s);
            i = pos + pattern.size();
        }
    }
}

bool IsSameCls(const std::vector<int>& cl1, const std::vector<int>& cl2)
{
    if (cl1.size() != cl2.size()) {
        return false;
    } else {
        for (int lIdx = 0; lIdx < cl1.size(); lIdx++) {
            if (cl1[lIdx] != cl2[lIdx]) {
                return false;
            }
        }
    }
    return true;
}

void LsSolver::ReadFromFile(const std::string& fileName, const std::vector<std::string>& softCNames)
{
    std::string inString;
    uint64_t inputNumLits;
    FILE* fp = freopen(fileName.c_str(), "r", stdin);
    if (fp == nullptr) {
        perror("fopen failed");
        return;
    }
    std::cin >> inputNumLits;
    MakeLitsSpace(inputNumLits);
    getline(std::cin, inString);
    getline(std::cin, inString);
    while (inString != "0") {
        BuildLits(inString);
        getline(std::cin, inString);
    }
    int size;
    std::cin >> size;
    originalVec.resize(size);
    int sizeNow = 0;
    while (sizeNow < size) {
        std::cin >> inString;
        if (inString == "(") {
            continue;
        } else if (inString == ")") {
            sizeNow++;
        } else {
            originalVec[sizeNow].push_back(atoi(inString.c_str()));
        }
    }
    DeleteRedundantClauses(originalVec);
    basicComponentName = "BC";
    bcWidthIdx = static_cast<int>(TransferNameToVar(".w", true));
    bcHightIdx = static_cast<int>(TransferNameToVar("BC_hight", true));
    PrepareComponentsIdx();
    PrepareSoftComponentsIdx(softCNames);
    numVars = _vars.size();
    litAppear.resize(numLits);
    litsInCls = new Array((int)numLits);
    RecordInfoAfterReadFile();
}

void LsSolver::RecordInfoAfterReadFile()
{
    _litsAfterReadFile = _lits;
    _varsAfterReadFile = _vars;
}

// restore the vars/lits/clauses
void LsSolver::RestoreInforBeforeBuildOrigin()
{
    for (int idx = 0; idx < numLits; idx++) {
        litsInCls->InsertElement(idx);
    }
    std::fill(litAppear.begin(), litAppear.end(), true);
    _reconstructStack.clear();
    _clauses.clear();
    _lits = _litsAfterReadFile;
    _vars = _varsAfterReadFile;
}

void LsSolver::AddUnitClause(std::vector<std::vector<int>>& vec, const std::vector<int>& unitLits)
{
    size_t oriVecNum = vec.size();
    vec.resize(oriVecNum + unitLits.size());
    for (size_t idx = 0; idx < unitLits.size(); idx++) {
        vec[oriVecNum + idx].emplace_back(unitLits[idx]);
    }
}

namespace {
static const std::string K_TRUE_LITERAL_STR = "0";
static const std::string K_OPEN_PAREN = "(";
static const std::string K_CLOSE_PAREN = ")";
static const std::string K_EQUAL_OP = "=";
static const std::string K_GREATER_EQUAL_OP = ">=";
static const int K_DEFAULT_COFF = 1;

// 解析多项式/多项项表达式分支
void ParseMultiTerm(LsSolver& solver, lit* l, const std::vector<std::string>& vec)
{
    l->litsIndex = std::atoi(vec[0].c_str());
    int idx = K_VEC_COFF_START_IDX;
    if (vec[K_VEC_OP_IDX] == K_EQUAL_OP && vec[K_VEC_ARG1_IDX] != K_OPEN_PAREN) {
        idx++;
        l->key = -std::atoll(vec[K_VEC_ARG1_IDX].c_str());
    }
    l->isEqual = (vec[K_VEC_OP_IDX] == K_EQUAL_OP);
    for (; idx < vec.size(); ++idx) {
        if (vec[idx] == K_CLOSE_PAREN)
            break;
        if (vec[idx] == K_OPEN_PAREN) {
            idx += K_VEC_OP_IDX; // move to coefficient
            int coff = std::atoi(vec[idx].c_str());
            uint64_t vIdx = solver.TransferNameToVar(vec[++idx], true);
            l->coffVars.push_back(CoffVar((int)vIdx, RationNum(coff)));
            ++idx;
        } else {
            uint64_t vIdx = solver.TransferNameToVar(vec[idx], true);
            l->coffVars.push_back(CoffVar((int)vIdx, RationNum(K_DEFAULT_COFF)));
        }
        solver.numOpt += l->coffVars.size();
    }
    if (vec[K_VEC_OP_IDX] != K_EQUAL_OP || vec[K_VEC_ARG1_IDX] == K_OPEN_PAREN) {
        l->key = -std::atoi(vec[++idx].c_str());
    }
    if (vec[K_VEC_OP_IDX] == K_GREATER_EQUAL_OP) {
        l->key += RationNum(1);
        solver.InvertLit(*l);
    }
}

// 解析简单形式（两项或 bound 形式）
void ParseSimpleTerm(LsSolver& solver, lit* l, const std::vector<std::string>& vec)
{
    l->litsIndex = std::atoi(vec[0].c_str());
    bool isEqWithTwoNames = (vec[K_VEC_OP_IDX] == K_EQUAL_OP && vec.size() == K_VEC_MULTI_TERM_THRESHOLD &&
                             (vec[K_VEC_ARG1_IDX][0] < '0' || vec[K_VEC_ARG1_IDX][0] > '9') &&
                             (vec[K_VEC_ARG2_IDX][0] < '0' || vec[K_VEC_ARG2_IDX][0] > '9') &&
                             (vec[K_VEC_ARG1_IDX][0] != '-') && (vec[K_VEC_ARG2_IDX][0] != '-'));
    if (isEqWithTwoNames) {
        l->isEqual = true;
        l->key = 0;
        uint64_t v1 = solver.TransferNameToVar(vec[K_VEC_ARG1_IDX], true);
        uint64_t v2 = solver.TransferNameToVar(vec[K_VEC_ARG2_IDX], true);
        l->coffVars.push_back(CoffVar(static_cast<int>(v1), RationNum(1)));
        l->coffVars.push_back(CoffVar(static_cast<int>(v2), RationNum(-1)));
        return;
    }
    int bound = 0;
    uint64_t varIdx = 0;
    if ((vec[K_VEC_ARG1_IDX][0] < '0' || vec[K_VEC_ARG1_IDX][0] > '9') && (vec[K_VEC_ARG1_IDX][0] != '-')) {
        bound = std::atoi(vec[K_VEC_ARG2_IDX].c_str());
        varIdx = solver.TransferNameToVar(vec[K_VEC_ARG1_IDX], true);
    } else {
        bound = std::atoi(vec[K_VEC_ARG1_IDX].c_str());
        varIdx = solver.TransferNameToVar(vec[K_VEC_ARG2_IDX], true);
    }
    if (vec[K_VEC_OP_IDX] == K_GREATER_EQUAL_OP) {
        l->key = bound;
        l->coffVars.push_back(CoffVar(static_cast<int>(varIdx), RationNum(-1)));
    } else {
        l->key = -bound;
        l->coffVars.push_back(CoffVar(static_cast<int>(varIdx), RationNum(1)));
    }
    l->isEqual = (vec[K_VEC_OP_IDX] == K_EQUAL_OP);
}
} // namespace

void LsSolver::BuildLits(std::string& inString)
{
    std::vector<std::string> vec;
    SplitString(inString, vec);
    if (vec.empty()) {
        return;
    }
    if (vec[0] == K_TRUE_LITERAL_STR) {
        _lits[0].litsIndex = 0;
        return;
    }
    int litIndex = std::atoi(vec[0].c_str());
    lit* l = &(_lits[litIndex]);

    if (vec.size() > K_VEC_OP_IDX && (vec[1] == "or" || vec[1] == "if")) {
        l->delta = (int)TransferNameToVar(vec[K_VEC_OP_IDX], false);
        l->key = K_DEFAULT_COFF;
        l->isNiaLit = false;
        l->litsIndex = litIndex;
        return;
    }

    if (vec.size() > K_VEC_OP_IDX) {
        l->isNiaLit = true;
        if (vec.size() > K_VEC_MULTI_TERM_THRESHOLD) {
            ParseMultiTerm(*this, l, vec);
        } else {
            ParseSimpleTerm(*this, l, vec);
        }
    } else {
        l->delta = (int)TransferNameToVar(vec[1], false);
        if (vec[1].find("feasible") != std::string::npos || vec[1].find("softVar") != std::string::npos) {
            feasible2litidx[vec[1]] = litIndex;
        }
        l->key = K_DEFAULT_COFF;
        l->isNiaLit = false;
        l->litsIndex = litIndex;
    }
}

int LsSolver::Find(int varIdx)
{
    if (varIdx == fa[varIdx]) {
        faCoff[varIdx] = 1;
        faConst[varIdx] = 0;
        return varIdx;
    } else {
        int oldFa = fa[varIdx]; // var = oldFa * faCoff[var] + faConst[var] ->
                                // (newFa*faCoff[oldFa]+faConst[oldFa]) * faCoff[var] + faConst[var]
        int newFa = Find(fa[varIdx]);
        faConst[varIdx] += faCoff[varIdx] * faConst[oldFa];
        faCoff[varIdx] *= faCoff[oldFa];
        return fa[varIdx] = newFa;
    }
}

// var1 = coff*var2 + constTerm
// 基于该等式，和var_2的bound，更新var_1的bound
void LsSolver::UpdateBoundByMerge(int varIdx1, int varIdx2, RationNum coff, RationNum constTerm)
{
    variable& var1 = _vars[varIdx1];
    variable& var2 = _vars[varIdx2];
    if (var2.upper_bound != MAX_INT) {
        if (coff > 0 && var1.upper_bound > coff * var2.upper_bound + constTerm) {
            var1.upper_bound = coff * var2.upper_bound + constTerm;
        } else if (coff < 0 && var1.lowBound < coff * var2.upper_bound + constTerm) {
            var1.lowBound = coff * var2.upper_bound + constTerm;
        }
    }
    if (var2.lowBound != -MAX_INT) {
        if (coff > 0 && var1.lowBound < coff * var2.lowBound + constTerm) {
            var1.lowBound = coff * var2.lowBound + constTerm;
        } else if (coff < 0 && var1.upper_bound > coff * var2.lowBound + constTerm) {
            var1.upper_bound = coff * var2.lowBound + constTerm;
        }
    }
}

// return true if the faCoff and faConst have been modified
// 此处要把bound给传递过去
bool LsSolver::Merge(lit& l)
{ // coff1*var1==coff2*var2
    int varIdx1 = l.coffVars[0].varIdx;
    int varIdx2 = l.coffVars[1].varIdx;
    int fa1 = Find(varIdx1);
    int fa2 = Find(varIdx2);
    RationNum const1 = l.coffVars[0].coff * faConst[varIdx1];
    RationNum const2 = l.coffVars[1].coff * faConst[varIdx2];
    RationNum faCoff1 = l.coffVars[0].coff * faCoff[varIdx1];
    RationNum faCoff2 = l.coffVars[1].coff * faCoff[varIdx2];
    RationNum keyNew = l.key + const1 + const2;
    // faCoff1*fa1+faCoff2*fa2+key==0
    if (fa1 == fa2) {
        return false;
    }
    if (faCoff1.Abs() > faCoff2.Abs()) {
        fa[fa2] = fa1;
        faCoff[fa2] = -faCoff1 / faCoff2;
        faConst[fa2] = -keyNew / faCoff2;
        UpdateBoundByMerge(fa1, fa2, -faCoff2 / faCoff1,
            -keyNew / faCoff1); // 保留下来的是fa_1,fa2被从公式中删除了,因此要用fa_2的bound更新fa_1的bound
        return true;
    } else {
        fa[fa1] = fa2;
        faCoff[fa1] = -faCoff2 / faCoff1;
        faConst[fa1] = -keyNew / faCoff1;
        UpdateBoundByMerge(fa2, fa1, -faCoff1 / faCoff2, -keyNew / faCoff2);
        return true;
    } // fa1 = (-faCoff2/faCoff1)*fa2 + (-key/faCoff1)
    return false;
}
bool CmpCoffVar(const CoffVar& cv1, const CoffVar& cv2)
{
    return cv1.varIdx < cv2.varIdx;
}

// if a+b+...<=k and a+b+...>=k only exist in 2 clauses respectively, and these 2 clause have common literals, then
// convert them to a+b+...=k
void LsSolver::ConvertInequalToEqual(bool& modified)
{
    std::vector<std::vector<int>> inequalLitInClauses(numLits);
    for (size_t clauseIdx = 0; clauseIdx < _clauses.size(); clauseIdx++) {
        for (int litIdx : _clauses[clauseIdx].literals) {
            if (litIdx <= 0) {
                continue;
            }
            const lit& currentLit = _lits[litIdx];
            if (!currentLit.isNiaLit || currentLit.isEqual || currentLit.litsIndex == 0) {
                continue;
            }
            inequalLitInClauses[litIdx].push_back((int)clauseIdx);
        }
    }

    std::vector<int> inequals;
    for (uint64_t litIdx = 0; litIdx < numLits; litIdx++) {
        if (inequalLitInClauses[litIdx].size() == 1) {
            inequals.push_back((int)litIdx);
        }
    }

    for (size_t idx1 = 0; idx1 < inequals.size(); idx1++) {
        const int preIdx = inequals[idx1];
        if (_lits[preIdx].litsIndex == 0) {
            continue;
        }
        for (size_t idx2 = idx1 + 1; idx2 < inequals.size(); idx2++) {
            const int posIdx = inequals[idx2];
            if (!IsNegLit(_lits[preIdx], _lits[posIdx])) {
                continue;
            }
            const std::vector<int>& clausePreLits = _clauses[inequalLitInClauses[preIdx][0]].literals;
            const std::vector<int>& clausePosLits = _clauses[inequalLitInClauses[posIdx][0]].literals;
            if (!ClausesMatchExceptOppositeLits(clausePreLits, clausePosLits, preIdx, posIdx)) {
                continue;
            }
            modified = true;
            _lits[preIdx].isEqual = true;
            _lits[posIdx].litsIndex = 0;
            break;
        }
    }
}

void LsSolver::FindUnitEqualLits(std::vector<int>& unitEqualLitsAll)
{
    // find out all unit equal lits
    for (int clauseIdx = 0; clauseIdx < _clauses.size(); clauseIdx++) {
        if (_clauses[clauseIdx].literals.size() == 1 && _clauses[clauseIdx].literals[0] > 0) {
            int litIdx = _clauses[clauseIdx].literals[0];
            if (_lits[litIdx].isEqual) { // t1+t2+..+tn=0
                unitEqualLitsAll.push_back(litIdx);
            }
        }
    }
}

void LsSolver::FixValue(RationNum& bcWidth, RationNum& bcHight, RationNum& radius)
{
    if (bcWidth != 0) {
        int rootBcWidthIdx = Find(bcWidthIdx);
        bcWidth = (bcWidth - faConst[bcWidthIdx]) / faCoff[bcWidthIdx];
        presetValues[rootBcWidthIdx] = bcWidth;
        _vars[rootBcWidthIdx].upper_bound = bcWidth;
        _vars[rootBcWidthIdx].lowBound = bcWidth;
    }
    if (bcHight != 0) {
        int rootBcHightIdx = Find(bcHightIdx);
        bcHight = (bcHight - faConst[bcHightIdx]) / faCoff[bcHightIdx];
        presetValues[rootBcHightIdx] = bcHight;
        _vars[rootBcHightIdx].upper_bound = bcHight;
        _vars[rootBcHightIdx].lowBound = bcHight;
    }
    if (radius != 0) {
        int radiusIdx = static_cast<int>(TransferNameToVar("radius", true));
        int rootRadiusIdx = Find(radiusIdx);
        radius = (radius - faConst[radiusIdx]) / faCoff[radiusIdx];
        presetValues[rootRadiusIdx] = radius;
        _vars[rootRadiusIdx].upper_bound = radius;
        _vars[rootRadiusIdx].lowBound = radius;
    }
}

void LsSolver::PreprocessOnSize(RationNum bcWidth, RationNum bcHight, RationNum radius)
{
    FixValue(bcWidth, bcHight, radius);
    bool modified = true;
    while (modified && !buildUnsat) { // if the formula has been modified, it should try to update by equalities again
        modified = false;
        ReduceClause(modified);
        ConvertInequalToEqual(modified); // 将不等式转为等式
        UpdateByEquals(modified);        // 通过等式来更新文字
        ReduceClause(modified);
        FindBound(modified);
        if (unsatInPreprocess) { // 如果在预处理过程中已经发现unsat，则直接返回
            return;
        }
        EliminateMultipleInequalities(modified); // 删除多余的不等式
    }
    ReduceClause(modified);
}
// initialize the fa, faCoff, faConst, presetValues
void LsSolver::PrepareFaCoffs()
{
    fa.resize(_vars.size());
    for (int varIdx = 0; varIdx < _vars.size(); varIdx++) {
        fa[varIdx] = varIdx;
    }
    faCoff.resize(_vars.size());
    faConst.resize(_vars.size());
    presetValues.resize(_vars.size());
    std::fill(faCoff.begin(), faCoff.end(), 1);
    std::fill(faConst.begin(), faConst.end(), 0);
    std::fill(presetValues.begin(), presetValues.end(), INT32_MAX);
}

// return true if lits can be modified by equalities
// 通过等式来更新文字: 会尝试找a==k 或者 a+M*b==k的等式来更新文字，如果文字直接为真或假就可以直接删除了
void LsSolver::ProcessUnitEqualLitsMerge(std::vector<int>& unitEqualLitsAll, bool& findNewMerge, bool& modified)
{
    findNewMerge = false;
    for (int i = 0; i < unitEqualLitsAll.size(); i++) {
        lit* l = &(_lits[unitEqualLitsAll[i]]);
        if (l->litsIndex != 0 && l->coffVars.size() == 1) {
            int var1 = l->coffVars[0].varIdx;
            RationNum tempValue = (-l->key) / l->coffVars[0].coff;
            if (presetValues[var1] == INT32_MAX || presetValues[var1] == tempValue) {
                presetValues[var1] = tempValue;
                _vars[var1].upper_bound = presetValues[var1];
                _vars[var1].lowBound = presetValues[var1];
            } else {
                unsatInPreprocess = true;
            }
            findNewMerge = true;
            modified = true;
            l->litsIndex = 0;
        }
    }
    for (int i = 0; i < unitEqualLitsAll.size(); i++) {
        int lIdx = unitEqualLitsAll[i];
        UpdateLitPresetVar(lIdx);
    }
    for (int i = 0; i < unitEqualLitsAll.size(); i++) {
        lit* l = &(_lits[unitEqualLitsAll[i]]);
        if (l->litsIndex <= 0) {
            continue;
        }
        if (l->coffVars.size() == K_TWO_VAR_EQUALITY && Merge(*l)) {
            l->litsIndex = 0;
            findNewMerge = true;
            modified = true;
        }
    }
    for (int i = 0; i < unitEqualLitsAll.size(); i++) {
        UpdateLitEqual(unitEqualLitsAll[i]);
    }
    if (!modified) {
        std::vector<int> mLits;
        for (const auto& lIdx : unitEqualLitsAll) {
            if (_lits[lIdx].coffVars.size() > K_TWO_VAR_EQUALITY) {
                mLits.push_back(lIdx);
            }
        }
        if (ResolveMultipleEquals(mLits)) {
            modified = true;
        }
    }
}

void LsSolver::UpdateByEquals(bool& modifiedInThisCall)
{
    std::vector<int> unitEqualLitsAll;
    FindUnitEqualLits(unitEqualLitsAll);
    bool findNewMerge = true;
    bool modified = false;
    while (findNewMerge) {
        ProcessUnitEqualLitsMerge(unitEqualLitsAll, findNewMerge, modified);
    }
    for (int idx = 0; idx < litsInCls->GetSize(); idx++) {
        int litIdx = litsInCls->GetElementByIndex(idx);
        UpdateLitPresetVar(litIdx);
        UpdateLitEqual(litIdx);
    }
    if (modified) {
        modifiedInThisCall = true;
    }
}

void LsSolver::UpdateLitPresetVar(int litIdx)
{
    lit* l = &(_lits[litIdx]);
    if (l->litsIndex <= 0 || !l->isNiaLit) {
        return;
    }
    if (l->coffVars.size() == 1 && l->isEqual) {
        return;
    }
    unsigned totalCvSize = 0;
    for (unsigned cvIdx = 0; cvIdx < l->coffVars.size(); cvIdx++) {
        CoffVar& cv = l->coffVars[cvIdx];
        int varIdx = cv.varIdx;
        if (presetValues[varIdx] != INT32_MAX) {
            litsBeenModified = true;
            l->key += (cv.coff * presetValues[varIdx]);
            continue;
        }
        l->coffVars[totalCvSize++] = cv;
    }
    l->coffVars.resize(totalCvSize);
    if (l->coffVars.size() == 0) {
        if (l->key == 0 || (l->key < 0 && !l->isEqual)) {
            l->litsIndex = 0;
        } else {
            l->litsIndex = -1;
            l->isTrue = false;
        }
    }
    GcdForLit(*l);
}

void LsSolver::UpdateLitEqual(int litIdx)
{
    lit* l = &(_lits[litIdx]);
    if (l->litsIndex <= 0 || !l->isNiaLit) {
        return;
    }
    bool litModified = false;
    for (CoffVar& cv : l->coffVars) {
        int varIdx = cv.varIdx;
        int newVarIdx = Find(varIdx);
        if (newVarIdx != varIdx) { // modify the var
            litModified = true;
            l->key += cv.coff * faConst[varIdx];
            cv.varIdx = newVarIdx;
            cv.coff *= faCoff[varIdx];
        }
    }
    if (litModified) {
        litsBeenModified = true;
        std::sort(l->coffVars.begin(), l->coffVars.end(), CmpCoffVar);
        int currVarIdx = l->coffVars[0].varIdx;
        RationNum currCoff = RationNum(0);
        int litCoffVarIdx = 0;
        for (int cvIdx = 0; cvIdx < l->coffVars.size(); cvIdx++) {
            if (l->coffVars[cvIdx].varIdx != currVarIdx) {
                currVarIdx = l->coffVars[cvIdx].varIdx;
                currCoff = 0;
            } // enter a new var
            currCoff += l->coffVars[cvIdx].coff; // the same var
            if (currCoff != 0 && (cvIdx == l->coffVars.size() - 1 || l->coffVars[cvIdx + 1].varIdx != currVarIdx)) {
                l->coffVars[litCoffVarIdx].varIdx = currVarIdx;
                l->coffVars[litCoffVarIdx++].coff = currCoff;
            } // the last CoffVar of the current var
        }
        l->coffVars.resize(litCoffVarIdx);
        if (litCoffVarIdx == 0) {
            if (l->key == 0 || (l->key < 0 && !l->isEqual)) {
                l->litsIndex = 0;
            } else {
                l->litsIndex = -1;
                l->isTrue = false;
            }
        }
        GcdForLit(*l);
    }
}

void PrintVec(const std::vector<std::vector<int>>& cl)
{
    std::cout << "0\n" << cl.size() << '\n';
    for (auto c : cl) {
        std::cout << "(";
        for (auto l : c) {
            std::cout << " " << l;
        }
        std::cout << " )\n";
    }
}

// delete the duplicate clauses and clause containing unit lits
// 删除完全一样的子句（删除子句中重复的文字），以及包含单元文字的子句（因为以及包含单元文字，则该子句必定为满足）
void LsSolver::DeleteRedundantClauses(std::vector<std::vector<int>>& clauseVec)
{
#ifdef LS_DEBUG
    std::cout << "start build\n";
    PrintVec(clauseVec);
#endif

    RemoveDuplicateClauses(clauseVec);
    for (auto& clauseLits : clauseVec) {
        RemoveDuplicateClauseLiterals(clauseLits);
    }
#ifdef LS_DEBUG
    std::cout << "after delete redundant clauses\n";
    PrintVec(clauseVec);
#endif
    std::vector<bool> unitLit(K_DIR_COUNT * numLits + additionalLen, false);
    MarkUnitLiterals(clauseVec, unitLit, numLits);
    FilterClausesSatisfiedByUnitLiterals(clauseVec, unitLit, numLits);
#ifdef LS_DEBUG
    std::cout << "after delete unit clauses\n";
    PrintVec(clauseVec);
    std::cout.flush();
#endif
}

void LsSolver::BuildInstanceOriginal(const std::vector<std::string>& unitLits)
{
    RestoreInforBeforeBuildOrigin();
    std::vector<std::vector<int>> clauseVec = originalVec;
    std::vector<int> unitLitsInt;
    for (const auto& l : unitLits) {
        unitLitsInt.emplace_back(feasible2litidx[l]);
    }
    AddUnitClause(clauseVec, unitLitsInt);
    DeleteRedundantClauses(clauseVec);
    PrepareClauseForResolution(clauseVec);
    // now the vars are all in the resolution vars
    UnitProp();
    Resolution();
    UnitProp();
    bool modified = false;
    ReduceClause(modified);
    PrepareFaCoffs();
    PreprocessOnSize();
    if (unsatInPreprocess) {
        return;
    }
    RecordInfo(infoAfterOrigin);
    MakeSpace();
}

// record the lit/var/clause information after buildOrigin
void LsSolver::RecordInfo(tmpInfo& info)
{
    info._clausesInfo = _clauses;
    info._litsInfo = _lits;
    info._varsInfo = _vars;
    info.faInfo = fa;
    info.faCoffInfo = faCoff;
    info.faConstInfo = faConst;
    info.presetValuesInfo = presetValues;
    info.currentBuildUnsat = buildUnsat;
}

void LsSolver::RestoreInfo(const tmpInfo& info)
{
    _clauses = info._clausesInfo;
    _lits = info._litsInfo;
    _vars = info._varsInfo;
    fa = info.faInfo;
    faCoff = info.faCoffInfo;
    faConst = info.faConstInfo;
    presetValues = info.presetValuesInfo;
    numClauses = _clauses.size();
    buildUnsat = info.currentBuildUnsat;
}

void LsSolver::BuildInstanceNewWidth(int bcWidth, int bcHight, int radius)
{
    RestoreInfo(infoAfterOrigin);
    PreprocessOnSize(RationNum(bcWidth), RationNum(bcHight), RationNum(radius));
}

// 找到出现最多的变量
// 找到这个变量所在的形如x=100的文字
void LsSolver::FindMaxVarLit(std::vector<int>& litIdxs)
{
    // 找到出现最多的变量
    std::vector<int> varCount(numVars, 0);
    for (const auto& cls : _clauses) {
        for (const auto& litIdx : cls.literals) {
            int absLitIdx = std::abs(litIdx);
            lit& l = _lits[absLitIdx];
            if (!l.isNiaLit) {
                continue;
            }
            for (const auto& cv : l.coffVars) {
                varCount[cv.varIdx]++;
            }
        }
    }
    int maxCount = -1;
    int maxVarIdx = -1;
    for (int vIdx = 0; vIdx < numVars; vIdx++) {
        if (varCount[vIdx] > maxCount) {
            maxCount = varCount[vIdx];
            maxVarIdx = vIdx;
        }
    }
    // 找到这个变量所在的形如x=100的文字,从lits_in_cls中找
    for (int idx = 0; idx < litsInCls->GetSize(); idx++) {
        int lIdx = litsInCls->GetElementByIndex(idx);
        lit& l = _lits[lIdx];
        if (l.coffVars.size() == 1 && l.coffVars[0].varIdx == maxVarIdx) {
#ifdef LS_DEBUG
            PrintLiteral(l);
#endif
            litIdxs.push_back(lIdx);
        }
    }
}

bool LsSolver::AssumeOneLiteral(const std::map<std::string, double>& varInitial)
{
    std::vector<int> litIdxs;
    FindMaxVarLit(litIdxs);
    for (const auto& litIdx : litIdxs) {
        if (AssumeOneLiteral(litIdx, varInitial) || (!_lits[litIdx].isEqual && AssumeOneLiteral(-litIdx,
            varInitial))) {
            return true;
        }
    }
    return false;
}

// 尝试一个文字假设它为真
bool LsSolver::AssumeOneLiteral(int litIdx, const std::map<std::string, double>& varInitial)
{
    // 记录下原来的情况
    // 假设这个文字为真
    // 基于这个文字进行化简，并且局部搜索
    // 如果局部搜索不成功再恢复
    if (_clauses.size() == 0) {
        return LocalSearch(varInitial);
    }
    RecordInfo(infoBeforeTrial);
    clause newCls;
    newCls.literals.push_back(litIdx);
    _clauses.push_back(newCls);
    numClauses++;
    PreprocessOnSize();
    if (unsatInPreprocess) {
        unsatInPreprocess = false;
        RestoreInfo(infoBeforeTrial);
        return false;
    }
#ifdef LS_DEBUG
    PrintFormula();
#endif
    if (LocalSearch(varInitial)) {
        return true;
    } else {
        RestoreInfo(infoBeforeTrial);
        return false;
    }
}

void LsSolver::PrepareUpValueVars()
{
    upValueVars.resize(numVars);
    std::fill(upValueVars.begin(), upValueVars.end(), 0);
    for (size_t vIdx = 0; vIdx < numVars; vIdx++) {
        if (_vars[vIdx].upBool != 0) {
            upValueVars[vIdx] = _vars[vIdx].upBool;
        }
    }
}

bool LsSolver::HasSameCoffVars(const lit* l1, const lit* l2)
{
    if (l1->coffVars.size() != l2->coffVars.size()) {
        return false;
    }
    for (size_t i = 0; i < l1->coffVars.size(); i++) {
        if ((l1->coffVars[i].coff != l2->coffVars[i].coff) || (l1->coffVars[i].varIdx != l2->coffVars[i].varIdx)) {
            return false;
        }
    }
    return true;
}

// a+b<=10 and a+b<=0 --> a+b<=0
// 删除多余的等式
void LsSolver::EliminateMultipleInequalities(bool& modified)
{
    std::vector<int> unitIneqs;
    for (const auto& c : _clauses) {
        if (c.literals.size() == 1 && c.literals[0] > 0) {
            lit& l = _lits[c.literals[0]];
            if (l.litsIndex != 0 && l.isNiaLit && !l.isEqual) {
                unitIneqs.emplace_back(l.litsIndex);
            }
        }
    }
    size_t unitIneqsNum = unitIneqs.size();
    for (size_t idxPre = 0; idxPre < unitIneqsNum; idxPre++) {
        lit* l1 = &_lits[unitIneqs[idxPre]];
        if (l1->litsIndex == 0) {
            continue;
        }
        for (size_t idxPos = idxPre + 1; idxPos < unitIneqsNum; idxPos++) {
            lit* l2 = &_lits[unitIneqs[idxPos]];
            if (l2->litsIndex == 0) {
                continue;
            }
            if (!HasSameCoffVars(l1, l2)) {
                continue;
            }
            if (l1->key > l2->key) {
                l2->litsIndex = 0;
                modified = true;
            } else {
                l1->litsIndex = 0;
                modified = true;
                break;
            }
        }
    }
}

// 找到所有单元子句，并根据单元子句更新变量的上下界，会去除原来的单元子句
void LsSolver::FindBound(bool& modified)
{
    for (int clauseIdx = 0; clauseIdx < _clauses.size(); clauseIdx++) {
        if (_clauses[clauseIdx].literals.size() != 1) {
            continue;
        }

        int& lOnlyIdx = _clauses[clauseIdx].literals[0];
        lit* l = &(_lits[std::abs(lOnlyIdx)]);
        if (l->isEqual || !l->isNiaLit || l->litsIndex <= 0 || l->coffVars.size() != 1) {
            continue;
        } // equal lit is not bound lit
        RationNum newLowBound = RationNum(-MAX_INT);
        RationNum newUpperBound = RationNum(MAX_INT);
        int varIdx = l->coffVars[0].varIdx;
        if (lOnlyIdx > 0) {
            if (l->coffVars[0].coff > 0) {
                newUpperBound = (-l->key) / (l->coffVars[0].coff);
            } else if (l->coffVars[0].coff < 0) {
                newLowBound = (-l->key) / (l->coffVars[0].coff);
            }
            l->litsIndex = 0;
            l->isTrue = true;
        } else {
            if (l->coffVars[0].coff > 0) {
                newLowBound = (-l->key) / (l->coffVars[0].coff);
            } else if (l->coffVars[0].coff < 0) {
                newUpperBound = (-l->key) / (l->coffVars[0].coff);
            }
            l->litsIndex = -1;
            l->isTrue = false;
        }
        if (newLowBound > _vars[varIdx].lowBound) {
            _vars[varIdx].lowBound = newLowBound;
        } else if (newUpperBound < _vars[varIdx].upper_bound) {
            _vars[varIdx].upper_bound = newUpperBound;
        }
        const RationNum epsilon(1, 1000); // 用于精度控制
        if (_vars[varIdx].lowBound > (_vars[varIdx].upper_bound + epsilon)) {
            unsatInPreprocess = true;
            return;
        }
        modified = true;
    }
}

void LsSolver::PrepareClauseForResolution(const std::vector<std::vector<int>> clauseVec)
{
    _clauses.resize(clauseVec.size());
    numClauses = 0;
    for (auto clauseCurr : clauseVec) {
        bool isTautology = false;
        for (auto lIdx : clauseCurr) {
            if ((_lits[std::abs(lIdx)].litsIndex == 0 && lIdx > 0) ||
                (_lits[std::abs(lIdx)].litsIndex < 0 && lIdx < 0)) {
                isTautology = true;
                break;
            }
        }
        if (isTautology) {
            continue;
        }
        for (auto lIdx : clauseCurr) {
            _clauses[numClauses].literals.push_back(lIdx);
            lit* l = &(_lits[std::abs(lIdx)]);
            if (l->litsIndex <= 0) {
                continue;
            }
            if (!l->isNiaLit) {
                _vars[l->delta.ToInt()].clauseIdxs.push_back(static_cast<int>(numClauses));
            }
        }
        numClauses++;
    }
    _clauses.resize(numClauses);
}

uint64_t LsSolver::TransferNameToVar(const std::string& name, bool isNia)
{
    if (name2var.find(name) == name2var.end()) {
        name2var[name] = _vars.size();
        variable var;
        var.varName = name;
        var.isNia = isNia;
        _vars.push_back(var);
        if (isNia) {
            niaVarVec.push_back((int)_vars.size() - 1);
        } else {
            boolVarVec.push_back((int)_vars.size() - 1);
        }
        return _vars.size() - 1;
    } else {
        return name2var[name];
    }
}

void LsSolver::UnitProp()
{
    std::stack<uint64_t> unitClause; // the varIdx in the unit clause
    for (uint64_t clauseIdx = 0; clauseIdx < numClauses; clauseIdx++) {
        if (IsBoolUnitClause(_clauses[clauseIdx], _lits)) {
            unitClause.push(clauseIdx);
        }
    }
    while (!unitClause.empty()) {
        uint64_t unitClauseIdx = unitClause.top();
        unitClause.pop();
        if (_clauses[unitClauseIdx].isDelete) {
            continue;
        }
        const int unitLitIdx = _clauses[unitClauseIdx].literals[0];
        const int isPosLit = (unitLitIdx > 0) ? 1 : -1;
        const uint64_t unitVar = _lits[std::abs(unitLitIdx)].delta.ToInt();
        _vars[unitVar].isDelete = true;
        _vars[unitVar].upBool = isPosLit; // set the solution of a boolean var as its unit propogation value
        for (uint64_t clIdx : _vars[unitVar].clauseIdxs) {
            clause& currentClause = _clauses[clIdx];
            if (currentClause.isDelete) {
                continue;
            }
            const int literalIdx = FindBoolLiteralIndexForVar(currentClause, _lits, unitVar);
            if (literalIdx < 0) {
                continue;
            }
            const int litIdInClause = currentClause.literals[literalIdx];
            if ((isPosLit > 0 && litIdInClause > 0) || (isPosLit < 0 && litIdInClause < 0)) {
                DeleteSatisfiedClause(*this, currentClause, clIdx, unitVar);
                continue;
            }
            RemoveUnsatisfiedLiteral(*this, currentClause, literalIdx, clIdx, unitClause);
        }
    }
}
__int128_t LsSolver::HashLitsToNum(std::vector<int>& lits)
{
    std::sort(lits.begin(), lits.end());
    __int128_t hashNum = 0;
    for (int litIdx : lits) {
        hashNum = (__int128_t)hashNum * (__int128_t)(numLits) + (__int128_t)litIdx + (__int128_t)numLits;
    }
    return hashNum;
}
bool LsSolver::IsSameLits(std::vector<int>& lits1, std::vector<int>& lits2)
{
    if (lits1.size() != lits2.size()) {
        return false;
    }
    std::sort(lits1.begin(), lits1.end());
    std::sort(lits2.begin(), lits2.end());
    for (int lIdx = 0; lIdx < lits1.size(); lIdx++) {
        if (lits1[lIdx] != lits2[lIdx]) {
            return false;
        }
    }
    return true;
}

void LsSolver::Resolution()
{
    ResolveContext ctx;
    ctx.posClauses.resize(K_RES_CLAUSE_MULTIPLIER * numClauses);
    ctx.negClauses.resize(K_RES_CLAUSE_MULTIPLIER * numClauses);
    std::map<__int128_t, int>
        clauselitMap; // for the clause with literal {a,b,c}, sort the lit by its order, and hash the literals to a
                      // number, then map it to the clauseIdx, if deleted, set it to -1
    std::vector<__int128_t> clauselit(_clauses.size()); // hash the lits of clause to a number
    for (int clsIdx = 0; clsIdx < _clauses.size(); clsIdx++) {
        clauselit[clsIdx] = HashLitsToNum(_clauses[clsIdx].literals);
        clauselitMap[clauselit[clsIdx]] = clsIdx;
    }
    bool isImprove = true;
    while (isImprove) {
        isImprove = false;
        for (uint64_t boolVarIdx : boolVarVec) {
            if (_vars[boolVarIdx].isDelete) {
                continue;
            }
            // determine the positive and negative clauses of boolVar
            DeterminePosAndNegClauses(boolVarIdx, ctx);
            int tautologyNum = CountTautology(boolVarIdx, ctx);
            if ((ctx.posClauseSize * ctx.negClauseSize - tautologyNum) > (ctx.posClauseSize + ctx.negClauseSize)) {
                continue;
            }
            for (uint64_t clauseIdx : _vars[boolVarIdx].clauseIdxs) {
                DeleteClausesOfVar(clauseIdx, boolVarIdx); // delete the clauses of boolVar
            }
            isImprove = true;
            _vars[boolVarIdx].isDelete = true;
            if (ctx.posClauseSize == 0) {
                _vars[boolVarIdx].upBool = -1;
            } // if it is a false pure lit, the var is set to false
            if (ctx.negClauseSize == 0) {
                _vars[boolVarIdx].upBool = 1;
            } // if it is a true pure lit, the var is set to true
            if (ctx.posClauseSize == 0 || ctx.negClauseSize == 0) {
                continue;
            } // the clauses are SAT, cannot resolute
            ResolveClauses(boolVarIdx, ctx, clauselitMap, clauselit);
            PushClausesToReconstructStack(boolVarIdx, ctx);
        }
    }
}

void LsSolver::DeterminePosAndNegClauses(uint64_t boolVarIdx, ResolveContext& ctx)
{
    ctx.posClauseSize = 0;
    ctx.negClauseSize = 0;
    for (int i = 0; i < _vars[boolVarIdx].clauseIdxs.size(); i++) {
        uint64_t clauseIdx = _vars[boolVarIdx].clauseIdxs[i];
        if (_clauses[clauseIdx].isDelete) {
            continue;
        }
        for (int lVarSign : _clauses[clauseIdx].literals) {
            if (_lits[std::abs(lVarSign)].isNiaLit || _lits[std::abs(lVarSign)].delta != boolVarIdx) {
                continue;
            }
            // make sure that it is a boolean literal and is exactly the one containing the var
            if (lVarSign > 0) {
                ctx.posClauses[ctx.posClauseSize++] = clauseIdx;
            } else {
                ctx.negClauses[ctx.negClauseSize++] = clauseIdx;
            }
            break;
        }
    }
}

int LsSolver::CountNegClauseTautology(uint64_t posClauseIdx, uint64_t negClauseIdx, uint64_t boolVarIdx)
{
    for (int k = 0; k < _clauses[negClauseIdx].literals.size(); k++) {
        int lNegLit = _clauses[negClauseIdx].literals[k];
        if (_lits[std::abs(lNegLit)].delta == boolVarIdx && !_lits[std::abs(lNegLit)].isNiaLit) {
            // the bool_var for resolution is not considered
            continue;
        }
        for (int lPosLit : _clauses[posClauseIdx].literals) {
            if (-lNegLit == (lPosLit)) {
                return 1;
            } // if there exists (aVb)^(-aV-b), the new clause is tautology
        }
    }
    return 0;
}

int LsSolver::CountTautology(uint64_t boolVarIdx, const ResolveContext& ctx)
{
    int tautologyNum = 0;
    for (int i = 0; i < ctx.posClauseSize; i++) {
        uint64_t posClauseIdx = ctx.posClauses[i];
        for (int j = 0; j < ctx.negClauseSize; j++) {
            uint64_t negClauseIdx = ctx.negClauses[j];
            tautologyNum += CountNegClauseTautology(posClauseIdx, negClauseIdx, boolVarIdx);
        }
    }
    return tautologyNum;
}

void LsSolver::DeleteClausesOfVar(uint64_t clauseIdx, uint64_t boolVarIdx)
{
    _clauses[clauseIdx].isDelete = true;
    for (int lIdxSign : _clauses[clauseIdx].literals) {
        lit* l = &(_lits[std::abs(lIdxSign)]);
        if (l->isNiaLit || l->delta == boolVarIdx) {
            continue;
        }
        variable* varInner = &(_vars[l->delta.ToInt()]);
        for (uint64_t deleteIdx = 0; deleteIdx < varInner->clauseIdxs.size(); deleteIdx++) {
            if (varInner->clauseIdxs[deleteIdx] == clauseIdx) {
                varInner->clauseIdxs[deleteIdx] = varInner->clauseIdxs.back();
                varInner->clauseIdxs.pop_back();
                break;
            }
        }
    }
}

void LsSolver::ResolvePosAndNegClause(uint64_t posClauseIdx, uint64_t negClauseIdx, uint64_t boolVarIdx,
    std::map<__int128_t, int>& clauselitMap, std::vector<__int128_t>& clauselit)
{
    clause newClause;
    uint64_t posLitSize = _clauses[posClauseIdx].literals.size();
    uint64_t negLitSize = _clauses[negClauseIdx].literals.size();
    newClause.literals.reserve(posLitSize + negLitSize);
    bool isTautology = false;
    for (auto lSignIdx : _clauses[posClauseIdx].literals) {
        if (_lits[std::abs(lSignIdx)].isNiaLit || _lits[std::abs(lSignIdx)].delta != boolVarIdx) {
            newClause.literals.push_back(lSignIdx);
        }
    } // add the lits in pos clause to new clause
    for (auto lSignIdx : _clauses[negClauseIdx].literals) {
        if (!(_lits[std::abs(lSignIdx)].isNiaLit || _lits[std::abs(lSignIdx)].delta != boolVarIdx)) {
            continue;
        }
        bool isExistedLit = false;
        for (uint64_t i = 0; i < posLitSize - 1; i++) {
            if (lSignIdx == (newClause.literals[i])) {
                isExistedLit = true;
                break;
            }
            if (lSignIdx == (-newClause.literals[i])) {
                isTautology = true;
                break;
            }
        }
        if (isTautology) {
            break;
        }
        if (!isExistedLit) {
            newClause.literals.push_back(lSignIdx);
        }
    }
    if (isTautology) {
        return;
    }
    __int128_t clauseLitHash = HashLitsToNum(newClause.literals);
    auto it = clauselitMap.find(clauseLitHash);
    if (it != clauselitMap.end()) {
        clause* clOrigin = &(_clauses[it->second]);
        if (!clOrigin->isDelete && IsSameLits(clOrigin->literals, newClause.literals)) {
            return;
        } // the clause appeals and has not been deleted or is the same as the new clause, return
    }
    AddClauseToData(newClause, clauseLitHash, clauselitMap, clauselit);
}

void LsSolver::AddClauseToData(const clause& newClause, __int128_t clauseLitHash,
    std::map<__int128_t, int>& clauselitMap, std::vector<__int128_t>& clauselit)
{
    for (int lSignIdx : newClause.literals) {
        lit* lInner = &(_lits[std::abs(lSignIdx)]);
        if (!lInner->isNiaLit) {
            _vars[lInner->delta.ToInt()].clauseIdxs.push_back(static_cast<int>(numClauses));
        }
    }
    _clauses.push_back(newClause);
    clauselit.push_back(clauseLitHash);
    clauselitMap[clauseLitHash] = static_cast<int>(numClauses);
    numClauses++;
}

void LsSolver::ResolveClauses(uint64_t boolVarIdx, ResolveContext& ctx, std::map<__int128_t, int>& clauselitMap,
    std::vector<__int128_t>& clauselit)
{
    for (auto i = 0; i < ctx.posClauseSize; i++) {
        uint64_t posClauseIdx = ctx.posClauses[i];
        for (auto j = 0; j < ctx.negClauseSize; j++) {
            uint64_t negClauseIdx = ctx.negClauses[j];
            ResolvePosAndNegClause(posClauseIdx, negClauseIdx, boolVarIdx, clauselitMap, clauselit);
        }
    }
}

void LsSolver::PushClausesToReconstructStack(uint64_t boolVarIdx, const ResolveContext& ctx)
{
    for (int i = 0; i < ctx.posClauseSize; i++) {
        clause posCl = _clauses[ctx.posClauses[i]];
        for (int j = 0; j < posCl.literals.size(); j++) {
            int lIdx = posCl.literals[j];
            lit* l = &(_lits[std::abs(lIdx)]);
            if (!l->isNiaLit && l->delta == boolVarIdx) {
                posCl.literals[j] = posCl.literals[0];
                posCl.literals[0] = lIdx;
                break;
            }
        }
        _reconstructStack.push_back(posCl);
    }
    for (int i = 0; i < ctx.negClauseSize; i++) {
        clause negCl = _clauses[ctx.negClauses[i]];
        for (int j = 0; j < negCl.literals.size(); j++) {
            int lIdx = negCl.literals[j];
            lit* l = &(_lits[std::abs(lIdx)]);
            if (!l->isNiaLit && l->delta == boolVarIdx) {
                negCl.literals[j] = negCl.literals[0];
                negCl.literals[0] = lIdx;
                break;
            }
        }
        _reconstructStack.push_back(negCl);
    }
}

bool CmpVlByVar(const VarLit& vl1, const VarLit& vl2)
{
    return vl1.varIdx < vl2.varIdx;
}
bool CmpVlByLit(const VarLit& vl1, const VarLit& vl2)
{
    return vl1.litIdx < vl2.litIdx;
}

// prepare coff var, determine all faCoffs
void LsSolver::PrepareCoffVar()
{
    for (int idx = 0; idx < _vars.size(); idx++) {
        if (_vars[idx].isNia) {
            Find(idx);
        }
    }
}
// turn the coffs and key of the lit to integer value
void LsSolver::GcdForLit(lit& l)
{
    if (l.litsIndex <= 0 || !l.isNiaLit || l.coffVars.size() <= 1) {
        return;
    }
    int64_t result = l.coffVars[0].coff.n;
    for (const auto& cv : l.coffVars) {
        result = std::gcd(result, cv.coff.n);
        if (result == 1) {
            return;
        }
    }
    result = std::gcd(result, l.key.n);
    if (result != 1) {
        for (size_t idx = 0; idx < l.coffVars.size(); idx++) {
            l.coffVars[idx].coff /= result;
        }
        l.key /= result;
    }
}

void LsSolver::DetermineLitAppear()
{
    for (int idx = 0; idx < litAppear.size(); idx++) {
        litAppear[idx] = false;
    }
    litsInCls->Clear();
    for (const auto& c : _clauses) {
        for (const auto& l : c.literals) {
            int lIdx = std::abs(l);
            litAppear[lIdx] = true;
            litsInCls->InsertElement(lIdx);
        }
    }
}

void LsSolver::ReduceDuplicatedLits(bool& modified)
{
    if (!litsBeenModified) {
        return;
    }
    std::vector<int> sameLit(numLits, 0); // sameLit[i] = j means lit i and j are the same lit
    int litsInClsNum = litsInCls->GetSize();
    for (int currIdx = 1; currIdx < litsInClsNum; currIdx++) {
        int lIdxCurr = litsInCls->GetElementByIndex(currIdx);
        if (!_lits[lIdxCurr].isNiaLit) {
            continue;
        }
        for (int preIdx = 0; preIdx < currIdx; preIdx++) {
            int lIdxPre = litsInCls->GetElementByIndex(preIdx);
            if (sameLit[lIdxPre] != 0 || !_lits[lIdxPre].isNiaLit) {
                continue; // the pre lit is same to previous ones, no more consider it
            }
            if (IsSameLit(_lits[lIdxCurr], _lits[lIdxPre])) {
                sameLit[lIdxCurr] = lIdxPre;
                break;
            } // find the first same lit
        }
    }
    // replace the lits in clauses
    for (auto& c : _clauses) {
        if (c.isDelete) {
            continue;
        }
        for (auto& lIdx : c.literals) {
            lit* l = &_lits[std::abs(lIdx)];
            if (!l->isNiaLit || l->litsIndex == 0) {
                continue;
            }
            int absLIdx = std::abs(lIdx);
            if (sameLit[absLIdx] != 0) {
                modified = true;
                lIdx = lIdx > 0 ? sameLit[absLIdx] : -sameLit[absLIdx];
            }
        }
    }
    litsBeenModified = false;
}

// all lits in mLits are unit equalities with multiple items
bool LsSolver::ResolveMultipleEquals(const std::vector<int>& mLits)
{
    if (mLits.size() < K_MIN_RESOLVE_EQUALS) {
        return false;
    }
    std::map<int32_t, size_t> varHash;
    std::vector<int32_t> varIdxs;
    for (const auto& lIdx : mLits) {
        for (const auto& cv : _lits[lIdx].coffVars) {
            int32_t varIdx = cv.varIdx;
            if (varHash.find(varIdx) == varHash.end()) {
                varHash[varIdx] = varIdxs.size();
                varIdxs.push_back(varIdx);
            }
        }
    }
    size_t rowNum = mLits.size();
    size_t collomNum = varIdxs.size() + 1;
    std::vector<std::vector<RationNum>> matrix(rowNum);
    for (auto& row : matrix) {
        row.resize(collomNum, RationNum(0));
    }
    for (size_t lIdx = 0; lIdx < rowNum; lIdx++) {
        for (const auto& cv : _lits[mLits[lIdx]].coffVars) {
            size_t hashVal = varHash[cv.varIdx];
            matrix[lIdx][hashVal] = cv.coff;
        }
        matrix[lIdx][collomNum - 1] = _lits[mLits[lIdx]].key;
    }
    // now the lits has been converted to matrix, matrix[i][j]=c indicates that in iTh literal, the coff of terms[j] is
    // c, the last collom of the matrix indicates the key of literals
    GaussianElimination(matrix);
    if (!ContainsShortRow(matrix)) {
        return false; // if after the modification, there is still no lit with items less than 2
    }
    for (size_t rIdx = 0; rIdx < rowNum; rIdx++) {
        if (IsAllZeroRow(matrix[rIdx])) {
            _lits[mLits[rIdx]].litsIndex = 0;
            continue;
        }
        _lits[mLits[rIdx]].coffVars.clear();
        for (size_t cIdx = 0; cIdx < collomNum - 1; cIdx++) {
            if (matrix[rIdx][cIdx] != 0) {
                int32_t varIdx = varIdxs[cIdx];
                RationNum coff = matrix[rIdx][cIdx];
                _lits[mLits[rIdx]].coffVars.push_back(CoffVar(varIdx, coff));
            }
        }
        _lits[mLits[rIdx]].key = matrix[rIdx][collomNum - 1];
    }
    return true;
}

// 计算文字的上界
RationNum LsSolver::CalculateLitUpBound(const lit& l)
{
    RationNum litUpBound = l.key;
    for (const auto& cv : l.coffVars) {
        variable& var = _vars[cv.varIdx];
        if (cv.coff > 0 && var.upper_bound != MAX_INT) {
            litUpBound += cv.coff * var.upper_bound;
        } else if (cv.coff < 0 && var.lowBound != -MAX_INT) {
            litUpBound += cv.coff * var.lowBound;
        } else {
            litUpBound = MAX_INT;
            break;
        }
    }
    return litUpBound;
}

// 计算文字的下界
RationNum LsSolver::CalculateLitLowBound(const lit& l)
{
    RationNum litLowBound = l.key;
    for (const auto& cv : l.coffVars) {
        variable& var = _vars[cv.varIdx];
        if (cv.coff > 0 && var.lowBound != -MAX_INT) {
            litLowBound += cv.coff * var.lowBound;
        } else if (cv.coff < 0 && var.upper_bound != MAX_INT) {
            litLowBound += cv.coff * var.upper_bound;
        } else {
            litLowBound = -MAX_INT;
            break;
        }
    }
    return litLowBound;
}

// 处理非等式情况
void LsSolver::HandleNonEqualCase(lit& l, const RationNum& litUpBound, const RationNum& litLowBound, bool& modified)
{
    if (litUpBound < litLowBound || litLowBound > 0) {
        l.litsIndex = -1;
        l.isTrue = false;
        modified = true;
    } else if (litUpBound <= 0) {
        l.litsIndex = 0;
        modified = true;
    }
}

// 处理等式情况
void LsSolver::HandleEqualCase(lit& l, const RationNum& litUpBound, const RationNum& litLowBound, bool& modified)
{
    if (litUpBound == litLowBound) {
        if (litUpBound != 0) {
            l.litsIndex = -1;
            l.isTrue = false;
            modified = true;
        } else {
            l.litsIndex = 0;
            modified = true;
        }
    } else if (litUpBound < 0 || litLowBound > 0) {
        l.litsIndex = -1;
        l.isTrue = false;
        modified = true;
    }
}

// 判断文字是否可以因为变量的界而变为true或false
void LsSolver::DetermineLitsByBound(bool& modified)
{
    // 遍历所有文字，如果该文字是nia的，则看其中的各个变量是否都有界，如果都有界，则该文字也有界，看是否已经
    for (int idx = 0; idx < litsInCls->GetSize(); idx++) {
        lit& l = _lits[litsInCls->GetElementByIndex(idx)];
        if (!l.isNiaLit || l.litsIndex == 0 || l.litsIndex < 0) {
            continue;
        }
        RationNum litUpBound = CalculateLitUpBound(l);
        RationNum litLowBound = CalculateLitLowBound(l);
        if (!l.isEqual) {
            HandleNonEqualCase(l, litUpBound, litLowBound, modified);
        } else {
            HandleEqualCase(l, litUpBound, litLowBound, modified);
        }
    }
}

// 检查 clause 是否为重言式（永真）：如果包含正文字且其litsIndex为0，或包含负文字且其litsIndex为负，则为重言式
bool LsSolver::IsClauseTautology(const clause& c)
{
    for (const auto& lIdx : c.literals) {
        if ((_lits[std::abs(lIdx)].litsIndex == 0 && lIdx > 0) || (_lits[std::abs(lIdx)].litsIndex < 0 && lIdx < 0)) {
            return true;
        }
    }
    return false;
}

// 删除单个 clause 中的重复文字，并对文字排序，删除已确定为假的文字
void LsSolver::ReduceDuplicatedLitsInClause(clause& c, bool& modified)
{
    std::sort(c.literals.begin(), c.literals.end());
    unsigned clauseSz = 0;
    for (int l : c.literals) {
        if ((_lits[std::abs(l)].litsIndex == 0 && l < 0) || (_lits[std::abs(l)].litsIndex < 0 && l > 0)) {
            continue;
        }
        if (clauseSz == 0 || c.literals[clauseSz - 1] != l) {
            c.literals[clauseSz++] = l;
        }
    }
    if (c.literals.size() != clauseSz) {
        modified = true;
    }
    c.literals.resize(clauseSz);
    if (clauseSz == 0) {
        buildUnsat = true;
    }
}

// 删除多余的子句
// 1. 删除子句中的重复文字（这里的重复是指2个文字虽然编号不同，但是内容是一致的）
// 2. 某些子句已经包含true literal
// 3. 删除同一个子句中的重复文字，删除子句中的假文字
// 4. 删除重复的子句，以及其中包含出现于单元子句中文字的子句
void LsSolver::ReduceClause(bool& modified)
{
    ReduceDuplicatedLits(modified); // 删除重复的文字，即编号不同但是实际一样的
    DetermineLitsByBound(modified); // 根据var的bound确定文字是否已经为true或false
    int reducedClauseNum = 0;
    uint64_t originalClauseNum = numClauses;
    for (int i = 0; i < numClauses; i++) {
        if (!_clauses[i].isDelete && !IsClauseTautology(_clauses[i])) {
            _clauses[reducedClauseNum++] = _clauses[i];
        }
    }
    _clauses.resize(reducedClauseNum);
    numClauses = reducedClauseNum;
    for (auto& c : _clauses) {
        ReduceDuplicatedLitsInClause(c, modified);
    }
    std::vector<std::vector<int>> clauseVec(numClauses);
    for (size_t cIdx = 0; cIdx < _clauses.size(); cIdx++) {
        clauseVec[cIdx] = _clauses[cIdx].literals;
    }
    DeleteRedundantClauses(clauseVec);
    numClauses = clauseVec.size();
    _clauses.resize(numClauses);
    for (size_t cIdx = 0; cIdx < numClauses; cIdx++) {
        _clauses[cIdx].literals = clauseVec[cIdx];
    }
    if (originalClauseNum != numClauses) {
        modified = true;
    }
    DetermineLitAppear();
}

void LsSolver::PrepareClsLitIdxForVars()
{
    ClearPreparedClauseLitVarState();
    RecordClauseLiteralRelations();
    for (variable& currentVar : _vars) {
        DeduplicateClauseIdxs(currentVar);
    }
    BuildPreparedVarLitRelations();
    for (variable& currentVar : _vars) {
        CollectUniqueLiteralIdxs(currentVar);
    }
    PrepareCoffVar();
    PrepareUpValueVars();
    bWidthIdx = name2var[basicComponentName + "_width"];
    bHightIdx = name2var[basicComponentName + "_hight"];
}

void LsSolver::ClearPreparedClauseLitVarState()
{
    bestFoundCost = static_cast<int>(numClauses);
    std::fill(litAppear.begin(), litAppear.end(), false);
    varAppear.resize(_vars.size() + additionalLen);
    std::fill(varAppear.begin(), varAppear.end(), false);
    for (const auto& boolVIdx : boolVarVec) {
        _vars[boolVIdx].clauseIdxs.clear();
    }
}

void LsSolver::RecordNiaLiteralInClause(int clauseIdx, int litSignIdx, lit& currentLit)
{
    for (const auto& cv : currentLit.coffVars) {
        if (!varAppear[cv.varIdx]) {
            varAppear[cv.varIdx] = true;
        }
        _vars[cv.varIdx].clauseIdxs.push_back(clauseIdx);
    }
    _clauses[clauseIdx].niaLiterals.push_back(litSignIdx);
}

void LsSolver::RecordBoolLiteralInClause(int clauseIdx, int litSignIdx, lit& currentLit)
{
    const uint64_t varIdx = currentLit.delta.ToInt();
    if (!litAppear[std::abs(litSignIdx)]) {
        _vars[varIdx].literalIdxs.push_back(std::abs(litSignIdx));
    }
    _vars[varIdx].clauseIdxs.push_back(clauseIdx);
    _vars[varIdx].boolVarInPosClause.push_back(litSignIdx > 0);
    _clauses[clauseIdx].boolLiterals.push_back(litSignIdx);
    if (!varAppear[varIdx]) {
        varAppear[varIdx] = true;
    }
}

void LsSolver::RecordClauseLiteralRelations()
{
    const int reducedClauseNum = (int)_clauses.size();
    for (int clauseIdx = 0; clauseIdx < reducedClauseNum; clauseIdx++) {
        _clauses[clauseIdx].weight = 1;
        for (int litSignIdx : _clauses[clauseIdx].literals) {
            lit& currentLit = _lits[std::abs(litSignIdx)];
            if (currentLit.isNiaLit) {
                RecordNiaLiteralInClause(clauseIdx, litSignIdx, currentLit);
            } else {
                RecordBoolLiteralInClause(clauseIdx, litSignIdx, currentLit);
            }
            if (!litAppear[std::abs(litSignIdx)]) {
                litAppear[std::abs(litSignIdx)] = true;
            }
        }
    }
}

void LsSolver::DeduplicateClauseIdxs(variable& currentVar)
{
    uint64_t previousClauseIdx = INT64_MAX;
    int varClauseNum = 0;
    for (int clauseIdx : currentVar.clauseIdxs) {
        if (previousClauseIdx == (uint64_t)clauseIdx) {
            continue;
        }
        previousClauseIdx = clauseIdx;
        currentVar.clauseIdxs[varClauseNum++] = clauseIdx;
    }
    currentVar.clauseIdxs.resize(varClauseNum);
}

void LsSolver::BuildPreparedVarLitRelations()
{
    for (uint64_t litIdx = 0; litIdx < numLits; litIdx++) {
        lit& currentLit = _lits[litIdx];
        if (!litAppear[litIdx]) {
            continue;
        }
        for (const auto& coffVar : currentLit.coffVars) {
            VarLit varLit(coffVar.varIdx, litIdx, coffVar.coff);
            _vars[coffVar.varIdx].varLits.push_back(varLit);
            currentLit.varLits.push_back(varLit);
        }
        std::sort(currentLit.varLits.begin(), currentLit.varLits.end(), CmpVlByVar);
    }
}

void LsSolver::CollectUniqueLiteralIdxs(variable& currentVar)
{
    uint64_t previousLitIdx = INT64_MAX;
    int varLitNum = 0;
    for (int idx = 0; idx < currentVar.varLits.size(); idx++) {
        const uint64_t currentLitIdx = currentVar.varLits[idx].litIdx;
        if (previousLitIdx == currentLitIdx) {
            continue;
        }
        previousLitIdx = currentLitIdx;
        varLitNum++;
        currentVar.literalIdxs.push_back(previousLitIdx);
    }
    currentVar.literalIdxs.resize(varLitNum);
}

bool LsSolver::IsSameLit(const lit& l1, const lit& l2)
{
    if ((!l1.isNiaLit) || (!l2.isNiaLit) || (l1.isEqual != l2.isEqual) || (l1.key != l2.key) ||
        (l1.coffVars.size() != l2.coffVars.size())) {
        return false;
    }
    for (size_t idx = 0; idx < l1.coffVars.size(); idx++) {
        if ((l1.coffVars[idx].coff != l2.coffVars[idx].coff) || (l1.coffVars[idx].varIdx != l2.coffVars[idx].varIdx)) {
            return false;
        }
    }
    return true;
}

bool LsSolver::IsNegLit(const lit& l1, const lit& l2)
{
    if (l1.isEqual || l2.isEqual) {
        return false;
    }
    if (!l1.isNiaLit || !l2.isNiaLit) {
        return false;
    }
    if (l1.coffVars.size() != l2.coffVars.size() || l1.key != -l2.key) {
        return false;
    }
    for (size_t idx = 0; idx < l1.coffVars.size(); idx++) {
        if ((l1.coffVars[idx].coff != -l2.coffVars[idx].coff) || (l1.coffVars[idx].varIdx != l2.coffVars[idx].varIdx)) {
            return false;
        }
    }
    return true;
}

void LsSolver::PrepareComponentsIdx()
{
    std::string vName;
    std::string val;
    std::string vEnd;
    std::map<std::string, int> kidsNames2Fre;
    for (const auto& niaVIdx : niaVarVec) {
        vName = _vars[niaVIdx].varName;
        size_t pos = vName.find_last_of('.');
        if (pos != std::string::npos) {
            vEnd = vName.substr(pos + 1);
            vName = vName.substr(0, pos);
        }
        if ((vEnd == "x" || vEnd == "y" || vEnd == "w" || vEnd == "h") && (vName != basicComponentName)) {
            if (kidsNames2Fre.find(vName) != kidsNames2Fre.end()) {
                kidsNames2Fre[vName]++;
            } else {
                kidsNames2Fre[vName] = 1;
            }
        }
    }
    for (const auto& pair : kidsNames2Fre) {
        if (pair.second == K_COMPONENT_FIELDS) {
            AddComponent(pair.first);
        }
    }
    AddComponent(basicComponentName);
}

void LsSolver::AddComponent(const std::string& cName)
{
    componentsIdx.push_back(name2var[cName + ".w"]);
    componentsIdx.push_back(name2var[cName + ".h"]);
    componentsIdx.push_back(name2var[cName + ".x"]);
    componentsIdx.push_back(name2var[cName + ".y"]);
    componentNames.push_back(cName);
}

void LsSolver::PrepareSoftComponentsIdx(const std::vector<std::string>& softCNames)
{
    for (const auto& softCName : softCNames) {
        softComponentsIdx.push_back(name2var[softCName + ".w"]);
        softComponentsIdx.push_back(name2var[softCName + ".h"]);
        softComponentsIdx.push_back(name2var[softCName + ".x"]);
        softComponentsIdx.push_back(name2var[softCName + ".y"]);
    }
}

void LsSolver::MakeSpace()
{
    // about num lits (not change)
    _litMakeBreak.resize(numLits + additionalLen);
    isInUnsatClause.resize(numLits + additionalLen);
    litsInUnsatClause.resize(numLits + additionalLen);
    if (falseLitOccur == NULL) {
        falseLitOccur = new Array((int)numLits + (int)additionalLen);
    }

    // about NumOpt (not change)
    operationVarIdxVec.resize(K_OP_MULTIPLIER * numOpt + additionalLen);
    operationVarIdxBoolVec.resize(K_OP_MULTIPLIER * numOpt + additionalLen);
    operationChangeValueVec.resize(K_OP_MULTIPLIER * numOpt + additionalLen);

    // about num clause (change)
    if (unsatClauses != NULL) {
        delete unsatClauses;
    }
    unsatClauses = new Array(static_cast<int>(numClauses) + (int)additionalLen);
    if (satClauseWithFalseLiteral != NULL) {
        delete satClauseWithFalseLiteral;
    }
    satClauseWithFalseLiteral = new Array(static_cast<int>(numClauses) + (int)additionalLen);
    if (containBoolUnsatClauses != NULL) {
        delete containBoolUnsatClauses;
    }
    containBoolUnsatClauses = new Array(static_cast<int>(numClauses));

    // about num vars (not change)
    _solution.resize(K_DIR_COUNT * numVars + additionalLen);
    _bestSolutin.resize(numVars + additionalLen);
    tabulist.resize(K_DIR_COUNT * numVars + additionalLen);
    lastMove.resize(K_DIR_COUNT * numVars + additionalLen);
    isChosenBoolVar.resize(numVars + additionalLen);
}

void LsSolver::SetPreValue()
{
    _preValue1.resize(numVars + additionalLen);
    _preValue2.resize(numVars + additionalLen);
    std::fill(_preValue1.begin(), _preValue1.end(), INT32_MAX);
    std::fill(_preValue2.begin(), _preValue2.end(), INT32_MAX);
    for (clause& cl : _clauses) {
        if (cl.literals.size() == 1 && cl.literals[0] > 0 && _lits[cl.literals[0]].isEqual) {
            lit* l = &(_lits[cl.literals[0]]);
            if (l->coffVars.size() == 1) {
                int varIdx = l->coffVars[0].varIdx;
                _preValue1[varIdx] = (-l->key / l->coffVars[0].coff);
            }
        } else if (cl.literals.size() == K_TWO_LITERAL_CLAUSE && cl.literals[0] > 0 && _lits[cl.literals[0]].isEqual &&
                   cl.literals[1] > 0 && _lits[cl.literals[1]].isEqual) {
            lit* l1 = &(_lits[cl.literals[0]]);
            lit* l2 = &(_lits[cl.literals[1]]);
            if ((l1->coffVars.size() == 1) && (l2->coffVars.size() == 1) &&
                (l1->coffVars[0].varIdx == l2->coffVars[0].varIdx)) {
                int varIdx = l1->coffVars[0].varIdx;
                _preValue1[varIdx] = (-l1->key / l1->coffVars[0].coff);
                _preValue2[varIdx] = (-l2->key / l2->coffVars[0].coff);
            }
        } //(a==0 OR a==1)
    }
}
LsSolver::~LsSolver()
{
    if (unsatClauses != NULL) {
        delete unsatClauses;
    }
    if (satClauseWithFalseLiteral != NULL) {
        delete satClauseWithFalseLiteral; // clauses with 0<satNum<literalNum, from which swap operation are
                                          // choosen
    }
    if (containBoolUnsatClauses != NULL) {
        delete containBoolUnsatClauses; // unsat clause with at least one boolean var
    }
    if (falseLitOccur != NULL) {
        delete falseLitOccur; // the false lits for choosing critical move
    }
}
} // namespace niaOverall
